#ifndef M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_SUM_HPP
#define M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_SUM_HPP 1

#include <algorithm>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#if defined(__AVX2__) || defined(__BMI2__)
#include <immintrin.h>
#endif

namespace m1une {
namespace ds {

// A static wavelet matrix with additive weights.
// By default, each value is also used as its weight.
template <std::integral T, typename Sum = T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
struct WaveletMatrixSum {
    using value_type = T;
    using sum_type = Sum;
    using unsigned_type = std::make_unsigned_t<T>;

   private:
    static constexpr int value_bit_width =
        std::numeric_limits<unsigned_type>::digits;
    static constexpr unsigned_type sign_mask = [] {
        if constexpr (std::signed_integral<T>) {
            return unsigned_type(1) << (value_bit_width - 1);
        } else {
            return unsigned_type(0);
        }
    }();

    struct BitVector {
        std::vector<std::uint64_t> bits;
        std::vector<int> prefix;

        BitVector() = default;

        explicit BitVector(int n)
            : bits(((std::size_t(n) + 63) >> 6) + 1, 0),
              prefix(bits.size(), 0) {}

        void build() {
            for (std::size_t i = 0; i + 1 < bits.size(); i++) {
                prefix[i + 1] = prefix[i] + std::popcount(bits[i]);
            }
        }

        bool get(int p) const {
            return (bits[std::size_t(p) >> 6] >> (p & 63)) & 1;
        }

        int rank1(int r) const {
            std::size_t word = std::size_t(r) >> 6;
            int offset = r & 63;
            int result = prefix[word];
#if defined(__BMI2__)
            result += std::popcount(
                _bzhi_u64(bits[word], static_cast<unsigned int>(offset))
            );
#else
            if (offset != 0) {
                result += std::popcount(
                    bits[word] & ((std::uint64_t(1) << offset) - 1)
                );
            }
#endif
            return result;
        }
    };

    int _n;
    int _log;
    unsigned_type _key_prefix;
    unsigned_type _min_key;
    unsigned_type _max_key;
    std::vector<BitVector> _matrix;
    std::vector<int> _zero_count;
    std::vector<std::vector<Sum>> _zero_prefix;
    std::vector<Sum> _original_prefix;
    std::vector<Sum> _final_prefix;

    static unsigned_type encode(T value) {
        unsigned_type bits;
        if constexpr (std::signed_integral<T>) {
            bits = std::bit_cast<unsigned_type>(value);
        } else {
            bits = value;
        }
        return bits ^ sign_mask;
    }

    static T decode(unsigned_type key) {
        unsigned_type bits = key ^ sign_mask;
        if constexpr (std::signed_integral<T>) {
            return std::bit_cast<T>(bits);
        } else {
            return bits;
        }
    }

    bool bit(unsigned_type value, int level) const {
        return (value >> (_log - 1 - level)) & unsigned_type(1);
    }

    static std::uint64_t extract_bits(
        const unsigned_type* values,
        int count,
        int shift
    ) {
        std::uint64_t result = 0;
        int i = 0;
#if defined(__AVX2__)
        if constexpr (sizeof(unsigned_type) == 8) {
            __m128i left = _mm_cvtsi32_si128(63 - shift);
            for (; i + 4 <= count; i += 4) {
                __m256i data = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i*>(values + i)
                );
                data = _mm256_sll_epi64(data, left);
                int mask = _mm256_movemask_pd(_mm256_castsi256_pd(data));
                result |= std::uint64_t(mask) << i;
            }
        } else if constexpr (sizeof(unsigned_type) == 4) {
            __m128i left = _mm_cvtsi32_si128(31 - shift);
            for (; i + 8 <= count; i += 8) {
                __m256i data = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i*>(values + i)
                );
                data = _mm256_sll_epi32(data, left);
                int mask = _mm256_movemask_ps(_mm256_castsi256_ps(data));
                result |= std::uint64_t(mask) << i;
            }
        }
#endif
        for (; i < count; i++) {
            result |= std::uint64_t((values[i] >> shift) & unsigned_type(1))
                      << i;
        }
        return result;
    }

    Sum zero_sum(int level, int l, int r) const {
        return _zero_prefix[level][r] - _zero_prefix[level][l];
    }

    Sum sum_less_encoded(int l, int r, unsigned_type upper) const {
        if (_n == 0 || upper <= _min_key) return Sum{};
        if (upper > _max_key) {
            return _original_prefix[r] - _original_prefix[l];
        }

        Sum result{};
        for (int level = 0; level < _log; level++) {
            int l1 = _matrix[level].rank1(l);
            int r1 = _matrix[level].rank1(r);
            if (bit(upper, level)) {
                result = result + zero_sum(level, l, r);
                l = _zero_count[level] + l1;
                r = _zero_count[level] + r1;
            } else {
                l -= l1;
                r -= r1;
            }
        }
        return result;
    }

    int count_less_encoded(int l, int r, unsigned_type upper) const {
        if (_n == 0 || upper <= _min_key) return 0;
        if (upper > _max_key) return r - l;

        int result = 0;
        for (int level = 0; level < _log; level++) {
            int l1 = _matrix[level].rank1(l);
            int r1 = _matrix[level].rank1(r);
            if (bit(upper, level)) {
                result += (r - l) - (r1 - l1);
                l = _zero_count[level] + l1;
                r = _zero_count[level] + r1;
            } else {
                l -= l1;
                r -= r1;
            }
        }
        return result;
    }

    void build(const std::vector<T>& values, const std::vector<Sum>& weights) {
        assert(values.size() == weights.size());

        std::vector<unsigned_type> current_keys(_n);
        std::vector<unsigned_type> next_keys(_n);
        std::vector<Sum> current_weights(weights);
        std::vector<Sum> next_weights(_n);
        for (int i = 0; i < _n; i++) current_keys[i] = encode(values[i]);

        _original_prefix.assign(std::size_t(_n) + 1, Sum{});
        for (int i = 0; i < _n; i++) {
            _original_prefix[i + 1] = _original_prefix[i] + weights[i];
        }
        if (_n == 0) {
            _final_prefix.assign(1, Sum{});
            return;
        }

        _min_key = current_keys[0];
        _max_key = current_keys[0];
        for (unsigned_type key : current_keys) {
            if (key < _min_key) _min_key = key;
            if (_max_key < key) _max_key = key;
        }
        _log = int(std::bit_width(unsigned_type(_min_key ^ _max_key)));
        if (_log != value_bit_width) {
            _key_prefix = unsigned_type((_min_key >> _log) << _log);
        }
        _zero_count.assign(_log, 0);

        _matrix.reserve(_log);
        _zero_prefix.reserve(_log);
        for (int level = 0; level < _log; level++) {
            _matrix.emplace_back(_n);
            _zero_prefix.emplace_back(std::size_t(_n) + 1, Sum{});
            BitVector& bit_vector = _matrix.back();
            int shift = _log - 1 - level;
            int zeros = 0;
            for (int base = 0; base < _n; base += 64) {
                int count = std::min(64, _n - base);
                std::uint64_t word = extract_bits(
                    current_keys.data() + base,
                    count,
                    shift
                );
                bit_vector.bits[std::size_t(base) >> 6] = word;
                zeros += count - std::popcount(word);
            }
            bit_vector.build();

            std::vector<Sum>& prefix = _zero_prefix.back();
            for (int base = 0; base < _n; base += 64) {
                int count = std::min(64, _n - base);
                std::uint64_t ones = bit_vector.bits[std::size_t(base) >> 6];
                for (int offset = 0; offset < count; offset++) {
                    int i = base + offset;
                    prefix[i + 1] = prefix[i];
                    if (((ones >> offset) & 1) == 0) {
                        prefix[i + 1] = prefix[i + 1] + current_weights[i];
                    }
                }
            }

            _zero_count[level] = zeros;
            int zero_pos = 0;
            int one_pos = zeros;
            for (int base = 0; base < _n; base += 64) {
                int count = std::min(64, _n - base);
                std::uint64_t ones = bit_vector.bits[std::size_t(base) >> 6];
                std::uint64_t valid = count == 64
                                          ? ~std::uint64_t(0)
                                          : (std::uint64_t(1) << count) - 1;
                std::uint64_t zeroes = (~ones) & valid;
                while (zeroes != 0) {
                    int offset = std::countr_zero(zeroes);
                    next_keys[zero_pos] = current_keys[base + offset];
                    next_weights[zero_pos] = current_weights[base + offset];
                    zero_pos++;
                    zeroes &= zeroes - 1;
                }
                while (ones != 0) {
                    int offset = std::countr_zero(ones);
                    next_keys[one_pos] = current_keys[base + offset];
                    next_weights[one_pos] = current_weights[base + offset];
                    one_pos++;
                    ones &= ones - 1;
                }
            }
            current_keys.swap(next_keys);
            current_weights.swap(next_weights);
        }

        _final_prefix.assign(std::size_t(_n) + 1, Sum{});
        for (int i = 0; i < _n; i++) {
            _final_prefix[i + 1] = _final_prefix[i] + current_weights[i];
        }
    }

   public:
    WaveletMatrixSum()
        : _n(0),
          _log(0),
          _key_prefix(0),
          _min_key(0),
          _max_key(0),
          _original_prefix(1, Sum{}),
          _final_prefix(1, Sum{}) {}

    explicit WaveletMatrixSum(const std::vector<T>& values)
        requires std::convertible_to<T, Sum>
        : _n(int(values.size())),
          _log(0),
          _key_prefix(0),
          _min_key(0),
          _max_key(0) {
        std::vector<Sum> weights;
        weights.reserve(values.size());
        for (T value : values) weights.push_back(static_cast<Sum>(value));
        build(values, weights);
    }

    WaveletMatrixSum(
        const std::vector<T>& values,
        const std::vector<Sum>& weights
    ) : _n(int(values.size())),
        _log(0),
        _key_prefix(0),
        _min_key(0),
        _max_key(0) {
        build(values, weights);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    T access(int p) const {
        assert(0 <= p && p < _n);
        unsigned_type key = _key_prefix;
        for (int level = 0; level < _log; level++) {
            int ones_before = _matrix[level].rank1(p);
            bool one = _matrix[level].get(p);
            if (one) {
                key |= unsigned_type(1) << (_log - 1 - level);
                p = _zero_count[level] + ones_before;
            } else {
                p -= ones_before;
            }
        }
        return decode(key);
    }

    T operator[](int p) const {
        return access(p);
    }

    int rank(T value, int r) const {
        assert(0 <= r && r <= _n);
        return rank(value, 0, r);
    }

    int rank(T value, int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        unsigned_type key = encode(value);
        if (_n == 0 || key < _min_key || _max_key < key) return 0;
        for (int level = 0; level < _log; level++) {
            int l1 = _matrix[level].rank1(l);
            int r1 = _matrix[level].rank1(r);
            if (bit(key, level)) {
                l = _zero_count[level] + l1;
                r = _zero_count[level] + r1;
            } else {
                l -= l1;
                r -= r1;
            }
        }
        return r - l;
    }

    T kth_smallest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(0 <= k && k < r - l);
        unsigned_type key = _key_prefix;
        for (int level = 0; level < _log; level++) {
            int l1 = _matrix[level].rank1(l);
            int r1 = _matrix[level].rank1(r);
            int l0 = l - l1;
            int r0 = r - r1;
            int zeros = r0 - l0;
            if (k < zeros) {
                l = l0;
                r = r0;
            } else {
                k -= zeros;
                key |= unsigned_type(1) << (_log - 1 - level);
                l = _zero_count[level] + l1;
                r = _zero_count[level] + r1;
            }
        }
        return decode(key);
    }

    T kth_largest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(0 <= k && k < r - l);
        return kth_smallest(l, r, r - l - 1 - k);
    }

    int range_freq(int l, int r, T upper) const {
        assert(0 <= l && l <= r && r <= _n);
        return count_less_encoded(l, r, encode(upper));
    }

    int range_freq(int l, int r, T lower, T upper) const {
        assert(0 <= l && l <= r && r <= _n);
        if (upper <= lower) return 0;
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }

    std::optional<T> prev_value(int l, int r, T upper) const {
        assert(0 <= l && l <= r && r <= _n);
        int count = range_freq(l, r, upper);
        if (count == 0) return std::nullopt;
        return kth_smallest(l, r, count - 1);
    }

    std::optional<T> next_value(int l, int r, T lower) const {
        assert(0 <= l && l <= r && r <= _n);
        int count = range_freq(l, r, lower);
        if (count == r - l) return std::nullopt;
        return kth_smallest(l, r, count);
    }

    Sum range_sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        return _original_prefix[r] - _original_prefix[l];
    }

    Sum range_sum(int l, int r, T upper) const {
        assert(0 <= l && l <= r && r <= _n);
        return sum_less_encoded(l, r, encode(upper));
    }

    Sum range_sum(int l, int r, T lower, T upper) const {
        assert(0 <= l && l <= r && r <= _n);
        if (upper <= lower) return Sum{};
        return range_sum(l, r, upper) - range_sum(l, r, lower);
    }

    Sum sum_k_smallest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(0 <= k && k <= r - l);
        Sum result{};
        for (int level = 0; level < _log; level++) {
            int l1 = _matrix[level].rank1(l);
            int r1 = _matrix[level].rank1(r);
            int l0 = l - l1;
            int r0 = r - r1;
            int zeros = r0 - l0;
            if (k < zeros) {
                l = l0;
                r = r0;
            } else {
                result = result + zero_sum(level, l, r);
                k -= zeros;
                l = _zero_count[level] + l1;
                r = _zero_count[level] + r1;
            }
        }
        return result + (_final_prefix[l + k] - _final_prefix[l]);
    }

    Sum sum_k_largest(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(0 <= k && k <= r - l);
        return range_sum(l, r) - sum_k_smallest(l, r, r - l - k);
    }

    template <class Predicate>
    int max_count_smallest(int l, int r, Predicate predicate) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(predicate(Sum{}));
        Sum result{};
        int count = 0;
        for (int level = 0; level < _log; level++) {
            int l1 = _matrix[level].rank1(l);
            int r1 = _matrix[level].rank1(r);
            int l0 = l - l1;
            int r0 = r - r1;
            int zeros = r0 - l0;
            Sum zero_result = result + zero_sum(level, l, r);
            if (predicate(zero_result)) {
                result = zero_result;
                count += zeros;
                l = _zero_count[level] + l1;
                r = _zero_count[level] + r1;
            } else {
                l = l0;
                r = r0;
            }
        }

        int low = 0;
        int high = r - l;
        while (low < high) {
            int middle = low + (high - low + 1) / 2;
            Sum candidate =
                result + (_final_prefix[l + middle] - _final_prefix[l]);
            if (predicate(candidate)) {
                low = middle;
            } else {
                high = middle - 1;
            }
        }
        return count + low;
    }

    template <class Predicate>
    int max_count_largest(int l, int r, Predicate predicate) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(predicate(Sum{}));
        Sum result{};
        Sum current_sum = range_sum(l, r);
        int count = 0;
        for (int level = 0; level < _log; level++) {
            int l1 = _matrix[level].rank1(l);
            int r1 = _matrix[level].rank1(r);
            int l0 = l - l1;
            int r0 = r - r1;
            int ones = r1 - l1;
            Sum zero_result = zero_sum(level, l, r);
            Sum one_result = current_sum - zero_result;
            Sum candidate = result + one_result;
            if (predicate(candidate)) {
                result = candidate;
                count += ones;
                current_sum = zero_result;
                l = l0;
                r = r0;
            } else {
                current_sum = one_result;
                l = _zero_count[level] + l1;
                r = _zero_count[level] + r1;
            }
        }

        int low = 0;
        int high = r - l;
        while (low < high) {
            int middle = low + (high - low + 1) / 2;
            Sum candidate =
                result + (_final_prefix[r] - _final_prefix[r - middle]);
            if (predicate(candidate)) {
                low = middle;
            } else {
                high = middle - 1;
            }
        }
        return count + low;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_SUM_HPP
