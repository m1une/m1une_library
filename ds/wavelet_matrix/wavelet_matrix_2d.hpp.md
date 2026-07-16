---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/wavelet_matrix/wavelet_matrix_2d.test.cpp
    title: verify/ds/wavelet_matrix/wavelet_matrix_2d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/wavelet_matrix/wavelet_matrix_2d.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// A static\
    \ wavelet matrix for a sequence of pairs.\n//\n// Besides the index range, queries\
    \ can restrict the first component and count\n// or select by the second component.\
    \ This corresponds to orthogonal queries in\n// the three dimensions (index, first,\
    \ second).\ntemplate <class X, class Y = X>\nclass WaveletMatrix2D {\n   public:\n\
    \    using first_type = X;\n    using second_type = Y;\n    using value_type =\
    \ std::pair<X, Y>;\n\n   private:\n    struct BitVector {\n        std::vector<std::uint64_t>\
    \ bits;\n        std::vector<int> prefix;\n\n        BitVector() = default;\n\n\
    \        explicit BitVector(int n)\n            : bits((std::size_t(n) + 63) >>\
    \ 6, 0),\n              prefix(bits.size() + 1, 0) {}\n\n        void set(int\
    \ p) {\n            bits[std::size_t(p) >> 6] |= std::uint64_t(1) << (p & 63);\n\
    \        }\n\n        void build() {\n            for (std::size_t i = 0; i <\
    \ bits.size(); i++) {\n                prefix[i + 1] = prefix[i] + std::popcount(bits[i]);\n\
    \            }\n        }\n\n        int rank1(int r) const {\n            std::size_t\
    \ word = std::size_t(r) >> 6;\n            int offset = r & 63;\n            int\
    \ result = prefix[word];\n            if (offset != 0) {\n                result\
    \ += std::popcount(\n                    bits[word] & ((std::uint64_t(1) << offset)\
    \ - 1)\n                );\n            }\n            return result;\n      \
    \  }\n    };\n\n    class RankWaveletMatrix {\n       private:\n        int _n\
    \ = 0;\n        int _alphabet_size = 0;\n        int _log = 0;\n        std::vector<BitVector>\
    \ _matrix;\n        std::vector<int> _zero_count;\n\n        bool bit(int value,\
    \ int level) const {\n            return (value >> (_log - 1 - level)) & 1;\n\
    \        }\n\n        int count_less(int l, int r, int upper) const {\n      \
    \      if (upper <= 0) return 0;\n            if (upper >= _alphabet_size) return\
    \ r - l;\n\n            int result = 0;\n            for (int level = 0; level\
    \ < _log; level++) {\n                int l1 = _matrix[level].rank1(l);\n    \
    \            int r1 = _matrix[level].rank1(r);\n                if (bit(upper,\
    \ level)) {\n                    result += (r - l) - (r1 - l1);\n            \
    \        l = _zero_count[level] + l1;\n                    r = _zero_count[level]\
    \ + r1;\n                } else {\n                    l -= l1;\n            \
    \        r -= r1;\n                }\n            }\n            return result;\n\
    \        }\n\n       public:\n        RankWaveletMatrix() = default;\n\n     \
    \   RankWaveletMatrix(\n            const std::vector<int>& values,\n        \
    \    int alphabet_size\n        ) {\n            build(values, alphabet_size);\n\
    \        }\n\n        void build(const std::vector<int>& values, int alphabet_size)\
    \ {\n            assert(alphabet_size >= 0);\n            _n = int(values.size());\n\
    \            _alphabet_size = alphabet_size;\n            _log = alphabet_size\
    \ == 0\n                       ? 0\n                       : std::max(\n     \
    \                        1,\n                             int(std::bit_width(unsigned(alphabet_size\
    \ - 1)))\n                         );\n\n            _matrix.clear();\n      \
    \      _matrix.reserve(_log);\n            _zero_count.assign(_log, 0);\n    \
    \        std::vector<int> current(values);\n            std::vector<int> next(_n);\n\
    \            for (int value : values) {\n                assert(0 <= value &&\
    \ value < alphabet_size);\n                (void)value;\n            }\n\n   \
    \         for (int level = 0; level < _log; level++) {\n                _matrix.emplace_back(_n);\n\
    \                int zeros = 0;\n                for (int i = 0; i < _n; i++)\
    \ {\n                    if (bit(current[i], level)) {\n                     \
    \   _matrix.back().set(i);\n                    } else {\n                   \
    \     zeros++;\n                    }\n                }\n                _matrix.back().build();\n\
    \n                _zero_count[level] = zeros;\n                int zero_position\
    \ = 0;\n                int one_position = zeros;\n                for (int value\
    \ : current) {\n                    if (bit(value, level)) {\n               \
    \         next[one_position++] = value;\n                    } else {\n      \
    \                  next[zero_position++] = value;\n                    }\n   \
    \             }\n                current.swap(next);\n            }\n        }\n\
    \n        int range_freq(int l, int r, int lower, int upper) const {\n       \
    \     assert(0 <= l && l <= r && r <= _n);\n            if (upper <= lower) return\
    \ 0;\n            return count_less(l, r, upper) - count_less(l, r, lower);\n\
    \        }\n    };\n\n    int _n = 0;\n    int _log = 0;\n    std::vector<value_type>\
    \ _values;\n    std::vector<X> _first_coordinates;\n    std::vector<Y> _second_coordinates;\n\
    \    RankWaveletMatrix _first_matrix;\n    std::vector<BitVector> _matrix;\n \
    \   std::vector<int> _zero_count;\n    std::vector<RankWaveletMatrix> _zero_first_matrix;\n\
    \n    template <class T>\n    static bool equal(const T& first, const T& second)\
    \ {\n        return !(first < second) && !(second < first);\n    }\n\n    template\
    \ <class T>\n    static void sort_unique(std::vector<T>& values) {\n        std::sort(values.begin(),\
    \ values.end());\n        values.erase(\n            std::unique(\n          \
    \      values.begin(),\n                values.end(),\n                [](const\
    \ T& first, const T& second) {\n                    return equal(first, second);\n\
    \                }\n            ),\n            values.end()\n        );\n   \
    \ }\n\n    bool bit(int value, int level) const {\n        return (value >> (_log\
    \ - 1 - level)) & 1;\n    }\n\n    int first_lower_bound(const X& value) const\
    \ {\n        return int(\n            std::lower_bound(\n                _first_coordinates.begin(),\n\
    \                _first_coordinates.end(),\n                value\n          \
    \  ) - _first_coordinates.begin()\n        );\n    }\n\n    int second_lower_bound(const\
    \ Y& value) const {\n        return int(\n            std::lower_bound(\n    \
    \            _second_coordinates.begin(),\n                _second_coordinates.end(),\n\
    \                value\n            ) - _second_coordinates.begin()\n        );\n\
    \    }\n\n    int count_first_rank(\n        int l,\n        int r,\n        int\
    \ first_lower,\n        int first_upper\n    ) const {\n        return _first_matrix.range_freq(l,\
    \ r, first_lower, first_upper);\n    }\n\n    int count_second_less(\n       \
    \ int l,\n        int r,\n        int first_lower,\n        int first_upper,\n\
    \        int second_upper\n    ) const {\n        if (second_upper <= 0) return\
    \ 0;\n        if (second_upper >= int(_second_coordinates.size())) {\n       \
    \     return count_first_rank(l, r, first_lower, first_upper);\n        }\n\n\
    \        int result = 0;\n        for (int level = 0; level < _log; level++) {\n\
    \            int l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            int l0 = l - l1;\n            int r0 = r - r1;\n            if (bit(second_upper,\
    \ level)) {\n                result += _zero_first_matrix[level].range_freq(\n\
    \                    l0,\n                    r0,\n                    first_lower,\n\
    \                    first_upper\n                );\n                l = _zero_count[level]\
    \ + l1;\n                r = _zero_count[level] + r1;\n            } else {\n\
    \                l = l0;\n                r = r0;\n            }\n        }\n\
    \        return result;\n    }\n\n   public:\n    WaveletMatrix2D() = default;\n\
    \n    explicit WaveletMatrix2D(const std::vector<value_type>& values) {\n    \
    \    build(values);\n    }\n\n    explicit WaveletMatrix2D(std::vector<value_type>&&\
    \ values) {\n        build(std::move(values));\n    }\n\n    WaveletMatrix2D(\n\
    \        const std::vector<X>& first,\n        const std::vector<Y>& second\n\
    \    ) {\n        build(first, second);\n    }\n\n    void build(std::vector<value_type>\
    \ values) {\n        _values = std::move(values);\n        _n = int(_values.size());\n\
    \n        _first_coordinates.clear();\n        _second_coordinates.clear();\n\
    \        _first_coordinates.reserve(_n);\n        _second_coordinates.reserve(_n);\n\
    \        for (const auto& value : _values) {\n            _first_coordinates.push_back(value.first);\n\
    \            _second_coordinates.push_back(value.second);\n        }\n       \
    \ sort_unique(_first_coordinates);\n        sort_unique(_second_coordinates);\n\
    \n        if (_n == 0) {\n            _log = 0;\n            _first_matrix = RankWaveletMatrix();\n\
    \            _matrix.clear();\n            _zero_count.clear();\n            _zero_first_matrix.clear();\n\
    \            return;\n        }\n\n        std::vector<int> current_first(_n);\n\
    \        std::vector<int> current_second(_n);\n        std::vector<int> next_first(_n);\n\
    \        std::vector<int> next_second(_n);\n        for (int i = 0; i < _n; i++)\
    \ {\n            current_first[i] = first_lower_bound(_values[i].first);\n   \
    \         current_second[i] = second_lower_bound(_values[i].second);\n       \
    \ }\n\n        int first_size = int(_first_coordinates.size());\n        int second_size\
    \ = int(_second_coordinates.size());\n        _first_matrix.build(current_first,\
    \ first_size);\n        _log = std::max(\n            1,\n            int(std::bit_width(unsigned(second_size\
    \ - 1)))\n        );\n        _matrix.clear();\n        _matrix.reserve(_log);\n\
    \        _zero_count.assign(_log, 0);\n        _zero_first_matrix.clear();\n \
    \       _zero_first_matrix.reserve(_log);\n\n        for (int level = 0; level\
    \ < _log; level++) {\n            _matrix.emplace_back(_n);\n            int zeros\
    \ = 0;\n            for (int i = 0; i < _n; i++) {\n                if (bit(current_second[i],\
    \ level)) {\n                    _matrix.back().set(i);\n                } else\
    \ {\n                    zeros++;\n                }\n            }\n        \
    \    _matrix.back().build();\n\n            _zero_count[level] = zeros;\n    \
    \        int zero_position = 0;\n            int one_position = zeros;\n     \
    \       for (int i = 0; i < _n; i++) {\n                int position;\n      \
    \          if (bit(current_second[i], level)) {\n                    position\
    \ = one_position++;\n                } else {\n                    position =\
    \ zero_position++;\n                }\n                next_first[position] =\
    \ current_first[i];\n                next_second[position] = current_second[i];\n\
    \            }\n\n            std::vector<int> zero_first(\n                next_first.begin(),\n\
    \                next_first.begin() + zeros\n            );\n            _zero_first_matrix.emplace_back(zero_first,\
    \ first_size);\n            current_first.swap(next_first);\n            current_second.swap(next_second);\n\
    \        }\n    }\n\n    void build(\n        const std::vector<X>& first,\n \
    \       const std::vector<Y>& second\n    ) {\n        assert(first.size() ==\
    \ second.size());\n        std::vector<value_type> values;\n        values.reserve(first.size());\n\
    \        for (int i = 0; i < int(first.size()); i++) {\n            values.emplace_back(first[i],\
    \ second[i]);\n        }\n        build(std::move(values));\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    const value_type& access(int p) const {\n \
    \       assert(0 <= p && p < _n);\n        return _values[p];\n    }\n\n    const\
    \ value_type& operator[](int p) const {\n        return access(p);\n    }\n\n\
    \    int count(\n        int l,\n        int r,\n        const X& first_lower,\n\
    \        const X& first_upper,\n        const Y& second_lower,\n        const\
    \ Y& second_upper\n    ) const {\n        assert(0 <= l && l <= r && r <= _n);\n\
    \        assert(!(first_upper < first_lower));\n        assert(!(second_upper\
    \ < second_lower));\n        int first_l = first_lower_bound(first_lower);\n \
    \       int first_r = first_lower_bound(first_upper);\n        int second_l =\
    \ second_lower_bound(second_lower);\n        int second_r = second_lower_bound(second_upper);\n\
    \        return count_second_less(l, r, first_l, first_r, second_r) -\n      \
    \         count_second_less(l, r, first_l, first_r, second_l);\n    }\n\n    Y\
    \ quantile(\n        int l,\n        int r,\n        const X& first_lower,\n \
    \       const X& first_upper,\n        int k\n    ) const {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        assert(!(first_upper < first_lower));\n\
    \        int first_l = first_lower_bound(first_lower);\n        int first_r =\
    \ first_lower_bound(first_upper);\n        int candidates = count_first_rank(l,\
    \ r, first_l, first_r);\n        assert(0 <= k && k < candidates);\n        (void)candidates;\n\
    \n        int second_rank = 0;\n        for (int level = 0; level < _log; level++)\
    \ {\n            int l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            int l0 = l - l1;\n            int r0 = r - r1;\n            int zeros\
    \ = _zero_first_matrix[level].range_freq(\n                l0,\n             \
    \   r0,\n                first_l,\n                first_r\n            );\n \
    \           if (k < zeros) {\n                l = l0;\n                r = r0;\n\
    \            } else {\n                k -= zeros;\n                second_rank\
    \ |= 1 << (_log - 1 - level);\n                l = _zero_count[level] + l1;\n\
    \                r = _zero_count[level] + r1;\n            }\n        }\n    \
    \    return _second_coordinates[second_rank];\n    }\n};\n\n}  // namespace ds\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_2D_HPP\n#define M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_2D_HPP\
    \ 1\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstdint>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    // A static wavelet matrix for a sequence of pairs.\n//\n// Besides the index\
    \ range, queries can restrict the first component and count\n// or select by the\
    \ second component. This corresponds to orthogonal queries in\n// the three dimensions\
    \ (index, first, second).\ntemplate <class X, class Y = X>\nclass WaveletMatrix2D\
    \ {\n   public:\n    using first_type = X;\n    using second_type = Y;\n    using\
    \ value_type = std::pair<X, Y>;\n\n   private:\n    struct BitVector {\n     \
    \   std::vector<std::uint64_t> bits;\n        std::vector<int> prefix;\n\n   \
    \     BitVector() = default;\n\n        explicit BitVector(int n)\n          \
    \  : bits((std::size_t(n) + 63) >> 6, 0),\n              prefix(bits.size() +\
    \ 1, 0) {}\n\n        void set(int p) {\n            bits[std::size_t(p) >> 6]\
    \ |= std::uint64_t(1) << (p & 63);\n        }\n\n        void build() {\n    \
    \        for (std::size_t i = 0; i < bits.size(); i++) {\n                prefix[i\
    \ + 1] = prefix[i] + std::popcount(bits[i]);\n            }\n        }\n\n   \
    \     int rank1(int r) const {\n            std::size_t word = std::size_t(r)\
    \ >> 6;\n            int offset = r & 63;\n            int result = prefix[word];\n\
    \            if (offset != 0) {\n                result += std::popcount(\n  \
    \                  bits[word] & ((std::uint64_t(1) << offset) - 1)\n         \
    \       );\n            }\n            return result;\n        }\n    };\n\n \
    \   class RankWaveletMatrix {\n       private:\n        int _n = 0;\n        int\
    \ _alphabet_size = 0;\n        int _log = 0;\n        std::vector<BitVector> _matrix;\n\
    \        std::vector<int> _zero_count;\n\n        bool bit(int value, int level)\
    \ const {\n            return (value >> (_log - 1 - level)) & 1;\n        }\n\n\
    \        int count_less(int l, int r, int upper) const {\n            if (upper\
    \ <= 0) return 0;\n            if (upper >= _alphabet_size) return r - l;\n\n\
    \            int result = 0;\n            for (int level = 0; level < _log; level++)\
    \ {\n                int l1 = _matrix[level].rank1(l);\n                int r1\
    \ = _matrix[level].rank1(r);\n                if (bit(upper, level)) {\n     \
    \               result += (r - l) - (r1 - l1);\n                    l = _zero_count[level]\
    \ + l1;\n                    r = _zero_count[level] + r1;\n                } else\
    \ {\n                    l -= l1;\n                    r -= r1;\n            \
    \    }\n            }\n            return result;\n        }\n\n       public:\n\
    \        RankWaveletMatrix() = default;\n\n        RankWaveletMatrix(\n      \
    \      const std::vector<int>& values,\n            int alphabet_size\n      \
    \  ) {\n            build(values, alphabet_size);\n        }\n\n        void build(const\
    \ std::vector<int>& values, int alphabet_size) {\n            assert(alphabet_size\
    \ >= 0);\n            _n = int(values.size());\n            _alphabet_size = alphabet_size;\n\
    \            _log = alphabet_size == 0\n                       ? 0\n         \
    \              : std::max(\n                             1,\n                \
    \             int(std::bit_width(unsigned(alphabet_size - 1)))\n             \
    \            );\n\n            _matrix.clear();\n            _matrix.reserve(_log);\n\
    \            _zero_count.assign(_log, 0);\n            std::vector<int> current(values);\n\
    \            std::vector<int> next(_n);\n            for (int value : values)\
    \ {\n                assert(0 <= value && value < alphabet_size);\n          \
    \      (void)value;\n            }\n\n            for (int level = 0; level <\
    \ _log; level++) {\n                _matrix.emplace_back(_n);\n              \
    \  int zeros = 0;\n                for (int i = 0; i < _n; i++) {\n          \
    \          if (bit(current[i], level)) {\n                        _matrix.back().set(i);\n\
    \                    } else {\n                        zeros++;\n            \
    \        }\n                }\n                _matrix.back().build();\n\n   \
    \             _zero_count[level] = zeros;\n                int zero_position =\
    \ 0;\n                int one_position = zeros;\n                for (int value\
    \ : current) {\n                    if (bit(value, level)) {\n               \
    \         next[one_position++] = value;\n                    } else {\n      \
    \                  next[zero_position++] = value;\n                    }\n   \
    \             }\n                current.swap(next);\n            }\n        }\n\
    \n        int range_freq(int l, int r, int lower, int upper) const {\n       \
    \     assert(0 <= l && l <= r && r <= _n);\n            if (upper <= lower) return\
    \ 0;\n            return count_less(l, r, upper) - count_less(l, r, lower);\n\
    \        }\n    };\n\n    int _n = 0;\n    int _log = 0;\n    std::vector<value_type>\
    \ _values;\n    std::vector<X> _first_coordinates;\n    std::vector<Y> _second_coordinates;\n\
    \    RankWaveletMatrix _first_matrix;\n    std::vector<BitVector> _matrix;\n \
    \   std::vector<int> _zero_count;\n    std::vector<RankWaveletMatrix> _zero_first_matrix;\n\
    \n    template <class T>\n    static bool equal(const T& first, const T& second)\
    \ {\n        return !(first < second) && !(second < first);\n    }\n\n    template\
    \ <class T>\n    static void sort_unique(std::vector<T>& values) {\n        std::sort(values.begin(),\
    \ values.end());\n        values.erase(\n            std::unique(\n          \
    \      values.begin(),\n                values.end(),\n                [](const\
    \ T& first, const T& second) {\n                    return equal(first, second);\n\
    \                }\n            ),\n            values.end()\n        );\n   \
    \ }\n\n    bool bit(int value, int level) const {\n        return (value >> (_log\
    \ - 1 - level)) & 1;\n    }\n\n    int first_lower_bound(const X& value) const\
    \ {\n        return int(\n            std::lower_bound(\n                _first_coordinates.begin(),\n\
    \                _first_coordinates.end(),\n                value\n          \
    \  ) - _first_coordinates.begin()\n        );\n    }\n\n    int second_lower_bound(const\
    \ Y& value) const {\n        return int(\n            std::lower_bound(\n    \
    \            _second_coordinates.begin(),\n                _second_coordinates.end(),\n\
    \                value\n            ) - _second_coordinates.begin()\n        );\n\
    \    }\n\n    int count_first_rank(\n        int l,\n        int r,\n        int\
    \ first_lower,\n        int first_upper\n    ) const {\n        return _first_matrix.range_freq(l,\
    \ r, first_lower, first_upper);\n    }\n\n    int count_second_less(\n       \
    \ int l,\n        int r,\n        int first_lower,\n        int first_upper,\n\
    \        int second_upper\n    ) const {\n        if (second_upper <= 0) return\
    \ 0;\n        if (second_upper >= int(_second_coordinates.size())) {\n       \
    \     return count_first_rank(l, r, first_lower, first_upper);\n        }\n\n\
    \        int result = 0;\n        for (int level = 0; level < _log; level++) {\n\
    \            int l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            int l0 = l - l1;\n            int r0 = r - r1;\n            if (bit(second_upper,\
    \ level)) {\n                result += _zero_first_matrix[level].range_freq(\n\
    \                    l0,\n                    r0,\n                    first_lower,\n\
    \                    first_upper\n                );\n                l = _zero_count[level]\
    \ + l1;\n                r = _zero_count[level] + r1;\n            } else {\n\
    \                l = l0;\n                r = r0;\n            }\n        }\n\
    \        return result;\n    }\n\n   public:\n    WaveletMatrix2D() = default;\n\
    \n    explicit WaveletMatrix2D(const std::vector<value_type>& values) {\n    \
    \    build(values);\n    }\n\n    explicit WaveletMatrix2D(std::vector<value_type>&&\
    \ values) {\n        build(std::move(values));\n    }\n\n    WaveletMatrix2D(\n\
    \        const std::vector<X>& first,\n        const std::vector<Y>& second\n\
    \    ) {\n        build(first, second);\n    }\n\n    void build(std::vector<value_type>\
    \ values) {\n        _values = std::move(values);\n        _n = int(_values.size());\n\
    \n        _first_coordinates.clear();\n        _second_coordinates.clear();\n\
    \        _first_coordinates.reserve(_n);\n        _second_coordinates.reserve(_n);\n\
    \        for (const auto& value : _values) {\n            _first_coordinates.push_back(value.first);\n\
    \            _second_coordinates.push_back(value.second);\n        }\n       \
    \ sort_unique(_first_coordinates);\n        sort_unique(_second_coordinates);\n\
    \n        if (_n == 0) {\n            _log = 0;\n            _first_matrix = RankWaveletMatrix();\n\
    \            _matrix.clear();\n            _zero_count.clear();\n            _zero_first_matrix.clear();\n\
    \            return;\n        }\n\n        std::vector<int> current_first(_n);\n\
    \        std::vector<int> current_second(_n);\n        std::vector<int> next_first(_n);\n\
    \        std::vector<int> next_second(_n);\n        for (int i = 0; i < _n; i++)\
    \ {\n            current_first[i] = first_lower_bound(_values[i].first);\n   \
    \         current_second[i] = second_lower_bound(_values[i].second);\n       \
    \ }\n\n        int first_size = int(_first_coordinates.size());\n        int second_size\
    \ = int(_second_coordinates.size());\n        _first_matrix.build(current_first,\
    \ first_size);\n        _log = std::max(\n            1,\n            int(std::bit_width(unsigned(second_size\
    \ - 1)))\n        );\n        _matrix.clear();\n        _matrix.reserve(_log);\n\
    \        _zero_count.assign(_log, 0);\n        _zero_first_matrix.clear();\n \
    \       _zero_first_matrix.reserve(_log);\n\n        for (int level = 0; level\
    \ < _log; level++) {\n            _matrix.emplace_back(_n);\n            int zeros\
    \ = 0;\n            for (int i = 0; i < _n; i++) {\n                if (bit(current_second[i],\
    \ level)) {\n                    _matrix.back().set(i);\n                } else\
    \ {\n                    zeros++;\n                }\n            }\n        \
    \    _matrix.back().build();\n\n            _zero_count[level] = zeros;\n    \
    \        int zero_position = 0;\n            int one_position = zeros;\n     \
    \       for (int i = 0; i < _n; i++) {\n                int position;\n      \
    \          if (bit(current_second[i], level)) {\n                    position\
    \ = one_position++;\n                } else {\n                    position =\
    \ zero_position++;\n                }\n                next_first[position] =\
    \ current_first[i];\n                next_second[position] = current_second[i];\n\
    \            }\n\n            std::vector<int> zero_first(\n                next_first.begin(),\n\
    \                next_first.begin() + zeros\n            );\n            _zero_first_matrix.emplace_back(zero_first,\
    \ first_size);\n            current_first.swap(next_first);\n            current_second.swap(next_second);\n\
    \        }\n    }\n\n    void build(\n        const std::vector<X>& first,\n \
    \       const std::vector<Y>& second\n    ) {\n        assert(first.size() ==\
    \ second.size());\n        std::vector<value_type> values;\n        values.reserve(first.size());\n\
    \        for (int i = 0; i < int(first.size()); i++) {\n            values.emplace_back(first[i],\
    \ second[i]);\n        }\n        build(std::move(values));\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    const value_type& access(int p) const {\n \
    \       assert(0 <= p && p < _n);\n        return _values[p];\n    }\n\n    const\
    \ value_type& operator[](int p) const {\n        return access(p);\n    }\n\n\
    \    int count(\n        int l,\n        int r,\n        const X& first_lower,\n\
    \        const X& first_upper,\n        const Y& second_lower,\n        const\
    \ Y& second_upper\n    ) const {\n        assert(0 <= l && l <= r && r <= _n);\n\
    \        assert(!(first_upper < first_lower));\n        assert(!(second_upper\
    \ < second_lower));\n        int first_l = first_lower_bound(first_lower);\n \
    \       int first_r = first_lower_bound(first_upper);\n        int second_l =\
    \ second_lower_bound(second_lower);\n        int second_r = second_lower_bound(second_upper);\n\
    \        return count_second_less(l, r, first_l, first_r, second_r) -\n      \
    \         count_second_less(l, r, first_l, first_r, second_l);\n    }\n\n    Y\
    \ quantile(\n        int l,\n        int r,\n        const X& first_lower,\n \
    \       const X& first_upper,\n        int k\n    ) const {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        assert(!(first_upper < first_lower));\n\
    \        int first_l = first_lower_bound(first_lower);\n        int first_r =\
    \ first_lower_bound(first_upper);\n        int candidates = count_first_rank(l,\
    \ r, first_l, first_r);\n        assert(0 <= k && k < candidates);\n        (void)candidates;\n\
    \n        int second_rank = 0;\n        for (int level = 0; level < _log; level++)\
    \ {\n            int l1 = _matrix[level].rank1(l);\n            int r1 = _matrix[level].rank1(r);\n\
    \            int l0 = l - l1;\n            int r0 = r - r1;\n            int zeros\
    \ = _zero_first_matrix[level].range_freq(\n                l0,\n             \
    \   r0,\n                first_l,\n                first_r\n            );\n \
    \           if (k < zeros) {\n                l = l0;\n                r = r0;\n\
    \            } else {\n                k -= zeros;\n                second_rank\
    \ |= 1 << (_log - 1 - level);\n                l = _zero_count[level] + l1;\n\
    \                r = _zero_count[level] + r1;\n            }\n        }\n    \
    \    return _second_coordinates[second_rank];\n    }\n};\n\n}  // namespace ds\n\
    }  // namespace m1une\n\n#endif  // M1UNE_DS_WAVELET_MATRIX_WAVELET_MATRIX_2D_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/wavelet_matrix/wavelet_matrix_2d.hpp
  requiredBy: []
  timestamp: '2026-07-16 18:16:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/wavelet_matrix/wavelet_matrix_2d.test.cpp
documentation_of: ds/wavelet_matrix/wavelet_matrix_2d.hpp
layout: document
title: Wavelet Matrix 2D
---

## Overview

`m1une::ds::WaveletMatrix2D` is a static multidimensional wavelet matrix for a
sequence of pairs:

$$
A_i=(x_i,y_i).
$$

It supports the following queries:

* count indices `i` satisfying simultaneous half-open bounds on `i`, `x_i`,
  and `y_i`, and
* among indices satisfying bounds on `i` and `x_i`, find the `k`-th smallest
  `y_i`.

Thus the structure handles orthogonal count and quantile queries in the three
dimensions `(index, first component, second component)`. This is the
construction described in
[3 次元空間のクエリを処理する Wavelet Matrix](https://noshi91.hatenablog.com/entry/2021/06/02/165408).

An outer wavelet matrix is built on the second components. At every outer
level, the elements routed to the zero side form another wavelet matrix over
their first components. These inner matrices restrict each outer rank step to
the requested first-component interval.

The sequence is immutable after construction.

## Template Parameters and Types

```cpp
template <class X, class Y = X>
class WaveletMatrix2D;
```

* `X`: first-component type.
* `Y`: second-component type.

Both types must provide a strict weak ordering through `<`. Coordinates are
compressed internally, so signed values and non-integral orderable types are
supported.

The public aliases are:

```cpp
using first_type = X;
using second_type = Y;
using value_type = std::pair<X, Y>;
```

## Construction

```cpp
WaveletMatrix2D();

explicit WaveletMatrix2D(const std::vector<value_type>& values);
explicit WaveletMatrix2D(std::vector<value_type>&& values);

WaveletMatrix2D(
    const std::vector<X>& first,
    const std::vector<Y>& second
);

void build(std::vector<value_type> values);

void build(
    const std::vector<X>& first,
    const std::vector<Y>& second
);
```

The parallel vectors must have equal lengths. Unlike a geometric point-set
structure, equal pairs are not merged: every sequence position remains a
separate element.

Let $N$ be the sequence length, $H_x$ the bit width of the compressed first
component, and $H_y$ the bit width of the compressed second component.
Construction takes $O(N\log N+NH_xH_y)$ time. The packed bitvectors and their
rank metadata use $O(NH_xH_y/w)$ machine words, where $w$ is the word size,
plus $O(N)$ coordinate and sequence storage.

## Methods

All index and component intervals are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the sequence length. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `const value_type& access(int p) const` | Returns `A[p]`. | $O(1)$ |
| `const value_type& operator[](int p) const` | Equivalent to `access(p)`. | $O(1)$ |
| `int count(int l, int r, const X& d, const X& u, const Y& s, const Y& t) const` | Counts `i` with `l <= i < r`, `d <= A[i].first < u`, and `s <= A[i].second < t`. | $O(H_xH_y)$ |
| `Y quantile(int l, int r, const X& d, const X& u, int k) const` | Returns the zero-based `k`-th smallest second component among `i` with `l <= i < r` and `d <= A[i].first < u`. | $O(H_xH_y)$ |

`quantile` requires `0 <= k < c`, where `c` is the number of elements meeting
its index and first-component restrictions. All methods are `const`; queries do
not mutate the structure.

## Example

```cpp
#include "ds/wavelet_matrix/wavelet_matrix_2d.hpp"

#include <cassert>
#include <utility>
#include <vector>

int main() {
    using Matrix = m1une::ds::WaveletMatrix2D<int>;
    std::vector<Matrix::value_type> values;
    values.emplace_back(3, 8);
    values.emplace_back(1, 5);
    values.emplace_back(4, 2);
    values.emplace_back(2, 7);
    values.emplace_back(3, 1);

    Matrix matrix(values);

    // Indices [1, 5), first component [2, 4), second component [1, 8).
    assert(matrix.count(1, 5, 2, 4, 1, 8) == 2);

    // Second components selected by index [0, 5) and first component [2, 4)
    // are 8, 7, 1. Their sorted order is 1, 7, 8.
    assert(matrix.quantile(0, 5, 2, 4, 1) == 7);
}
```
