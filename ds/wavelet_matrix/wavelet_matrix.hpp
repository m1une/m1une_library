#ifndef M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_HPP
#define M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_HPP 1

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

// A static wavelet matrix for integral values.
template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
struct WaveletMatrix {
    using value_type = T;
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

   public:
    WaveletMatrix()
        : _n(0),
          _log(0),
          _key_prefix(0),
          _min_key(0),
          _max_key(0) {}

    explicit WaveletMatrix(const std::vector<T>& values)
        : _n(int(values.size())),
          _log(0),
          _key_prefix(0),
          _min_key(0),
          _max_key(0) {
        std::vector<unsigned_type> current(_n);
        std::vector<unsigned_type> next(_n);
        for (int i = 0; i < _n; i++) current[i] = encode(values[i]);
        if (_n == 0) return;

        _min_key = current[0];
        _max_key = current[0];
        for (unsigned_type key : current) {
            if (key < _min_key) _min_key = key;
            if (_max_key < key) _max_key = key;
        }
        _log = int(std::bit_width(unsigned_type(_min_key ^ _max_key)));
        if (_log != value_bit_width) {
            _key_prefix = unsigned_type((_min_key >> _log) << _log);
        }
        _zero_count.assign(_log, 0);

        _matrix.reserve(_log);
        for (int level = 0; level < _log; level++) {
            _matrix.emplace_back(_n);
            BitVector& bit_vector = _matrix.back();
            int shift = _log - 1 - level;
            int zeros = 0;
            for (int base = 0; base < _n; base += 64) {
                int count = std::min(64, _n - base);
                std::uint64_t word = extract_bits(
                    current.data() + base,
                    count,
                    shift
                );
                bit_vector.bits[std::size_t(base) >> 6] = word;
                zeros += count - std::popcount(word);
            }
            bit_vector.build();

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
                    next[zero_pos++] = current[base + offset];
                    zeroes &= zeroes - 1;
                }
                while (ones != 0) {
                    int offset = std::countr_zero(ones);
                    next[one_pos++] = current[base + offset];
                    ones &= ones - 1;
                }
            }
            current.swap(next);
        }
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
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_HPP
