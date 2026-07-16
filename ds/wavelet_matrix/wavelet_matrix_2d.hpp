#ifndef M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_2D_HPP
#define M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_2D_HPP 1

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// A static wavelet matrix for a sequence of pairs.
//
// Besides the index range, queries can restrict the first component and count
// or select by the second component. This corresponds to orthogonal queries in
// the three dimensions (index, first, second).
template <class X, class Y = X>
class WaveletMatrix2D {
   public:
    using first_type = X;
    using second_type = Y;
    using value_type = std::pair<X, Y>;

   private:
    struct BitVector {
        std::vector<std::uint64_t> bits;
        std::vector<int> prefix;

        BitVector() = default;

        explicit BitVector(int n)
            : bits((std::size_t(n) + 63) >> 6, 0),
              prefix(bits.size() + 1, 0) {}

        void set(int p) {
            bits[std::size_t(p) >> 6] |= std::uint64_t(1) << (p & 63);
        }

        void build() {
            for (std::size_t i = 0; i < bits.size(); i++) {
                prefix[i + 1] = prefix[i] + std::popcount(bits[i]);
            }
        }

        int rank1(int r) const {
            std::size_t word = std::size_t(r) >> 6;
            int offset = r & 63;
            int result = prefix[word];
            if (offset != 0) {
                result += std::popcount(
                    bits[word] & ((std::uint64_t(1) << offset) - 1)
                );
            }
            return result;
        }
    };

    class RankWaveletMatrix {
       private:
        int _n = 0;
        int _alphabet_size = 0;
        int _log = 0;
        std::vector<BitVector> _matrix;
        std::vector<int> _zero_count;

        bool bit(int value, int level) const {
            return (value >> (_log - 1 - level)) & 1;
        }

        int count_less(int l, int r, int upper) const {
            if (upper <= 0) return 0;
            if (upper >= _alphabet_size) return r - l;

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
        RankWaveletMatrix() = default;

        RankWaveletMatrix(
            const std::vector<int>& values,
            int alphabet_size
        ) {
            build(values, alphabet_size);
        }

        void build(const std::vector<int>& values, int alphabet_size) {
            assert(alphabet_size >= 0);
            _n = int(values.size());
            _alphabet_size = alphabet_size;
            _log = alphabet_size == 0
                       ? 0
                       : std::max(
                             1,
                             int(std::bit_width(unsigned(alphabet_size - 1)))
                         );

            _matrix.clear();
            _matrix.reserve(_log);
            _zero_count.assign(_log, 0);
            std::vector<int> current(values);
            std::vector<int> next(_n);
            for (int value : values) {
                assert(0 <= value && value < alphabet_size);
                (void)value;
            }

            for (int level = 0; level < _log; level++) {
                _matrix.emplace_back(_n);
                int zeros = 0;
                for (int i = 0; i < _n; i++) {
                    if (bit(current[i], level)) {
                        _matrix.back().set(i);
                    } else {
                        zeros++;
                    }
                }
                _matrix.back().build();

                _zero_count[level] = zeros;
                int zero_position = 0;
                int one_position = zeros;
                for (int value : current) {
                    if (bit(value, level)) {
                        next[one_position++] = value;
                    } else {
                        next[zero_position++] = value;
                    }
                }
                current.swap(next);
            }
        }

        int range_freq(int l, int r, int lower, int upper) const {
            assert(0 <= l && l <= r && r <= _n);
            if (upper <= lower) return 0;
            return count_less(l, r, upper) - count_less(l, r, lower);
        }
    };

    int _n = 0;
    int _log = 0;
    std::vector<value_type> _values;
    std::vector<X> _first_coordinates;
    std::vector<Y> _second_coordinates;
    RankWaveletMatrix _first_matrix;
    std::vector<BitVector> _matrix;
    std::vector<int> _zero_count;
    std::vector<RankWaveletMatrix> _zero_first_matrix;

    template <class T>
    static bool equal(const T& first, const T& second) {
        return !(first < second) && !(second < first);
    }

    template <class T>
    static void sort_unique(std::vector<T>& values) {
        std::sort(values.begin(), values.end());
        values.erase(
            std::unique(
                values.begin(),
                values.end(),
                [](const T& first, const T& second) {
                    return equal(first, second);
                }
            ),
            values.end()
        );
    }

    bool bit(int value, int level) const {
        return (value >> (_log - 1 - level)) & 1;
    }

    int first_lower_bound(const X& value) const {
        return int(
            std::lower_bound(
                _first_coordinates.begin(),
                _first_coordinates.end(),
                value
            ) - _first_coordinates.begin()
        );
    }

    int second_lower_bound(const Y& value) const {
        return int(
            std::lower_bound(
                _second_coordinates.begin(),
                _second_coordinates.end(),
                value
            ) - _second_coordinates.begin()
        );
    }

    int count_first_rank(
        int l,
        int r,
        int first_lower,
        int first_upper
    ) const {
        return _first_matrix.range_freq(l, r, first_lower, first_upper);
    }

    int count_second_less(
        int l,
        int r,
        int first_lower,
        int first_upper,
        int second_upper
    ) const {
        if (second_upper <= 0) return 0;
        if (second_upper >= int(_second_coordinates.size())) {
            return count_first_rank(l, r, first_lower, first_upper);
        }

        int result = 0;
        for (int level = 0; level < _log; level++) {
            int l1 = _matrix[level].rank1(l);
            int r1 = _matrix[level].rank1(r);
            int l0 = l - l1;
            int r0 = r - r1;
            if (bit(second_upper, level)) {
                result += _zero_first_matrix[level].range_freq(
                    l0,
                    r0,
                    first_lower,
                    first_upper
                );
                l = _zero_count[level] + l1;
                r = _zero_count[level] + r1;
            } else {
                l = l0;
                r = r0;
            }
        }
        return result;
    }

   public:
    WaveletMatrix2D() = default;

    explicit WaveletMatrix2D(const std::vector<value_type>& values) {
        build(values);
    }

    explicit WaveletMatrix2D(std::vector<value_type>&& values) {
        build(std::move(values));
    }

    WaveletMatrix2D(
        const std::vector<X>& first,
        const std::vector<Y>& second
    ) {
        build(first, second);
    }

    void build(std::vector<value_type> values) {
        _values = std::move(values);
        _n = int(_values.size());

        _first_coordinates.clear();
        _second_coordinates.clear();
        _first_coordinates.reserve(_n);
        _second_coordinates.reserve(_n);
        for (const auto& value : _values) {
            _first_coordinates.push_back(value.first);
            _second_coordinates.push_back(value.second);
        }
        sort_unique(_first_coordinates);
        sort_unique(_second_coordinates);

        if (_n == 0) {
            _log = 0;
            _first_matrix = RankWaveletMatrix();
            _matrix.clear();
            _zero_count.clear();
            _zero_first_matrix.clear();
            return;
        }

        std::vector<int> current_first(_n);
        std::vector<int> current_second(_n);
        std::vector<int> next_first(_n);
        std::vector<int> next_second(_n);
        for (int i = 0; i < _n; i++) {
            current_first[i] = first_lower_bound(_values[i].first);
            current_second[i] = second_lower_bound(_values[i].second);
        }

        int first_size = int(_first_coordinates.size());
        int second_size = int(_second_coordinates.size());
        _first_matrix.build(current_first, first_size);
        _log = std::max(
            1,
            int(std::bit_width(unsigned(second_size - 1)))
        );
        _matrix.clear();
        _matrix.reserve(_log);
        _zero_count.assign(_log, 0);
        _zero_first_matrix.clear();
        _zero_first_matrix.reserve(_log);

        for (int level = 0; level < _log; level++) {
            _matrix.emplace_back(_n);
            int zeros = 0;
            for (int i = 0; i < _n; i++) {
                if (bit(current_second[i], level)) {
                    _matrix.back().set(i);
                } else {
                    zeros++;
                }
            }
            _matrix.back().build();

            _zero_count[level] = zeros;
            int zero_position = 0;
            int one_position = zeros;
            for (int i = 0; i < _n; i++) {
                int position;
                if (bit(current_second[i], level)) {
                    position = one_position++;
                } else {
                    position = zero_position++;
                }
                next_first[position] = current_first[i];
                next_second[position] = current_second[i];
            }

            std::vector<int> zero_first(
                next_first.begin(),
                next_first.begin() + zeros
            );
            _zero_first_matrix.emplace_back(zero_first, first_size);
            current_first.swap(next_first);
            current_second.swap(next_second);
        }
    }

    void build(
        const std::vector<X>& first,
        const std::vector<Y>& second
    ) {
        assert(first.size() == second.size());
        std::vector<value_type> values;
        values.reserve(first.size());
        for (int i = 0; i < int(first.size()); i++) {
            values.emplace_back(first[i], second[i]);
        }
        build(std::move(values));
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    const value_type& access(int p) const {
        assert(0 <= p && p < _n);
        return _values[p];
    }

    const value_type& operator[](int p) const {
        return access(p);
    }

    int count(
        int l,
        int r,
        const X& first_lower,
        const X& first_upper,
        const Y& second_lower,
        const Y& second_upper
    ) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(!(first_upper < first_lower));
        assert(!(second_upper < second_lower));
        int first_l = first_lower_bound(first_lower);
        int first_r = first_lower_bound(first_upper);
        int second_l = second_lower_bound(second_lower);
        int second_r = second_lower_bound(second_upper);
        return count_second_less(l, r, first_l, first_r, second_r) -
               count_second_less(l, r, first_l, first_r, second_l);
    }

    Y quantile(
        int l,
        int r,
        const X& first_lower,
        const X& first_upper,
        int k
    ) const {
        assert(0 <= l && l <= r && r <= _n);
        assert(!(first_upper < first_lower));
        int first_l = first_lower_bound(first_lower);
        int first_r = first_lower_bound(first_upper);
        int candidates = count_first_rank(l, r, first_l, first_r);
        assert(0 <= k && k < candidates);
        (void)candidates;

        int second_rank = 0;
        for (int level = 0; level < _log; level++) {
            int l1 = _matrix[level].rank1(l);
            int r1 = _matrix[level].rank1(r);
            int l0 = l - l1;
            int r0 = r - r1;
            int zeros = _zero_first_matrix[level].range_freq(
                l0,
                r0,
                first_l,
                first_r
            );
            if (k < zeros) {
                l = l0;
                r = r0;
            } else {
                k -= zeros;
                second_rank |= 1 << (_log - 1 - level);
                l = _zero_count[level] + l1;
                r = _zero_count[level] + r1;
            }
        }
        return _second_coordinates[second_rank];
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_2D_HPP
