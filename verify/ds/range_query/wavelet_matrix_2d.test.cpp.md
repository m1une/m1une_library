---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/wavelet_matrix_2d.hpp
    title: Wavelet Matrix 2D
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"verify/ds/range_query/wavelet_matrix_2d.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#line 1 \"\
    ds/range_query/wavelet_matrix_2d.hpp\"\n\n\n\n#include <algorithm>\n#include <bit>\n\
    #include <cassert>\n#include <cstdint>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// A static wavelet matrix for a sequence\
    \ of pairs.\n//\n// Besides the index range, queries can restrict the first component\
    \ and count\n// or select by the second component. This corresponds to orthogonal\
    \ queries in\n// the three dimensions (index, first, second).\ntemplate <class\
    \ X, class Y = X>\nclass WaveletMatrix2D {\n   public:\n    using first_type =\
    \ X;\n    using second_type = Y;\n    using value_type = std::pair<X, Y>;\n\n\
    \   private:\n    struct BitVector {\n        std::vector<std::uint64_t> bits;\n\
    \        std::vector<int> prefix;\n\n        BitVector() = default;\n\n      \
    \  explicit BitVector(int n)\n            : bits((std::size_t(n) + 63) >> 6, 0),\n\
    \              prefix(bits.size() + 1, 0) {}\n\n        void set(int p) {\n  \
    \          bits[std::size_t(p) >> 6] |= std::uint64_t(1) << (p & 63);\n      \
    \  }\n\n        void build() {\n            for (std::size_t i = 0; i < bits.size();\
    \ i++) {\n                prefix[i + 1] = prefix[i] + std::popcount(bits[i]);\n\
    \            }\n        }\n\n        int rank1(int r) const {\n            std::size_t\
    \ word = std::size_t(r) >> 6;\n            int offset = r & 63;\n            int\
    \ result = prefix[word];\n            if (offset != 0) {\n                result\
    \ += std::popcount(\n                    bits[word] & ((std::uint64_t(1) << offset)\
    \ - 1)\n                );\n            }\n            return result;\n      \
    \  }\n\n        int rank0(int r) const {\n            return r - rank1(r);\n \
    \       }\n    };\n\n    class RankWaveletMatrix {\n       private:\n        int\
    \ _n = 0;\n        int _alphabet_size = 0;\n        int _log = 0;\n        std::vector<BitVector>\
    \ _matrix;\n        std::vector<int> _zero_count;\n\n        bool bit(int value,\
    \ int level) const {\n            return (value >> (_log - 1 - level)) & 1;\n\
    \        }\n\n        int count_less(int l, int r, int upper) const {\n      \
    \      if (upper <= 0) return 0;\n            if (upper >= _alphabet_size) return\
    \ r - l;\n\n            int result = 0;\n            for (int level = 0; level\
    \ < _log; level++) {\n                int l0 = _matrix[level].rank0(l);\n    \
    \            int r0 = _matrix[level].rank0(r);\n                if (bit(upper,\
    \ level)) {\n                    result += r0 - l0;\n                    l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                    r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \                } else {\n                    l = l0;\n                    r\
    \ = r0;\n                }\n            }\n            return result;\n      \
    \  }\n\n       public:\n        RankWaveletMatrix() = default;\n\n        RankWaveletMatrix(\n\
    \            const std::vector<int>& values,\n            int alphabet_size\n\
    \        ) {\n            build(values, alphabet_size);\n        }\n\n       \
    \ void build(const std::vector<int>& values, int alphabet_size) {\n          \
    \  assert(alphabet_size >= 0);\n            _n = int(values.size());\n       \
    \     _alphabet_size = alphabet_size;\n            _log = alphabet_size == 0\n\
    \                       ? 0\n                       : std::max(\n            \
    \                 1,\n                             int(std::bit_width(unsigned(alphabet_size\
    \ - 1)))\n                         );\n\n            _matrix.clear();\n      \
    \      _matrix.reserve(_log);\n            _zero_count.assign(_log, 0);\n    \
    \        std::vector<int> current(values);\n            std::vector<int> next(_n);\n\
    \            for (int value : values) {\n                assert(0 <= value &&\
    \ value < alphabet_size);\n                (void)value;\n            }\n\n   \
    \         for (int level = 0; level < _log; level++) {\n                _matrix.emplace_back(_n);\n\
    \                for (int i = 0; i < _n; i++) {\n                    if (bit(current[i],\
    \ level)) _matrix.back().set(i);\n                }\n                _matrix.back().build();\n\
    \n                int zeros = _matrix.back().rank0(_n);\n                _zero_count[level]\
    \ = zeros;\n                int zero_position = 0;\n                int one_position\
    \ = zeros;\n                for (int value : current) {\n                    if\
    \ (bit(value, level)) {\n                        next[one_position++] = value;\n\
    \                    } else {\n                        next[zero_position++] =\
    \ value;\n                    }\n                }\n                current.swap(next);\n\
    \            }\n        }\n\n        int range_freq(int l, int r, int lower, int\
    \ upper) const {\n            assert(0 <= l && l <= r && r <= _n);\n         \
    \   if (upper <= lower) return 0;\n            return count_less(l, r, upper)\
    \ - count_less(l, r, lower);\n        }\n    };\n\n    int _n = 0;\n    int _log\
    \ = 0;\n    std::vector<value_type> _values;\n    std::vector<X> _first_coordinates;\n\
    \    std::vector<Y> _second_coordinates;\n    RankWaveletMatrix _first_matrix;\n\
    \    std::vector<BitVector> _matrix;\n    std::vector<int> _zero_count;\n    std::vector<RankWaveletMatrix>\
    \ _zero_first_matrix;\n\n    template <class T>\n    static bool equal(const T&\
    \ first, const T& second) {\n        return !(first < second) && !(second < first);\n\
    \    }\n\n    template <class T>\n    static void sort_unique(std::vector<T>&\
    \ values) {\n        std::sort(values.begin(), values.end());\n        values.erase(\n\
    \            std::unique(\n                values.begin(),\n                values.end(),\n\
    \                [](const T& first, const T& second) {\n                    return\
    \ equal(first, second);\n                }\n            ),\n            values.end()\n\
    \        );\n    }\n\n    bool bit(int value, int level) const {\n        return\
    \ (value >> (_log - 1 - level)) & 1;\n    }\n\n    int first_lower_bound(const\
    \ X& value) const {\n        return int(\n            std::lower_bound(\n    \
    \            _first_coordinates.begin(),\n                _first_coordinates.end(),\n\
    \                value\n            ) - _first_coordinates.begin()\n        );\n\
    \    }\n\n    int second_lower_bound(const Y& value) const {\n        return int(\n\
    \            std::lower_bound(\n                _second_coordinates.begin(),\n\
    \                _second_coordinates.end(),\n                value\n         \
    \   ) - _second_coordinates.begin()\n        );\n    }\n\n    int count_first_rank(\n\
    \        int l,\n        int r,\n        int first_lower,\n        int first_upper\n\
    \    ) const {\n        return _first_matrix.range_freq(l, r, first_lower, first_upper);\n\
    \    }\n\n    int count_second_less(\n        int l,\n        int r,\n       \
    \ int first_lower,\n        int first_upper,\n        int second_upper\n    )\
    \ const {\n        if (second_upper <= 0) return 0;\n        if (second_upper\
    \ >= int(_second_coordinates.size())) {\n            return count_first_rank(l,\
    \ r, first_lower, first_upper);\n        }\n\n        int result = 0;\n      \
    \  for (int level = 0; level < _log; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            if (bit(second_upper,\
    \ level)) {\n                result += _zero_first_matrix[level].range_freq(\n\
    \                    l0,\n                    r0,\n                    first_lower,\n\
    \                    first_upper\n                );\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            } else {\n                l = l0;\n                r = r0;\n    \
    \        }\n        }\n        return result;\n    }\n\n   public:\n    WaveletMatrix2D()\
    \ = default;\n\n    explicit WaveletMatrix2D(const std::vector<value_type>& values)\
    \ {\n        build(values);\n    }\n\n    explicit WaveletMatrix2D(std::vector<value_type>&&\
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
    \ < _log; level++) {\n            _matrix.emplace_back(_n);\n            for (int\
    \ i = 0; i < _n; i++) {\n                if (bit(current_second[i], level)) _matrix.back().set(i);\n\
    \            }\n            _matrix.back().build();\n\n            int zeros =\
    \ _matrix.back().rank0(_n);\n            _zero_count[level] = zeros;\n       \
    \     int zero_position = 0;\n            int one_position = zeros;\n        \
    \    for (int i = 0; i < _n; i++) {\n                int position;\n         \
    \       if (bit(current_second[i], level)) {\n                    position = one_position++;\n\
    \                } else {\n                    position = zero_position++;\n \
    \               }\n                next_first[position] = current_first[i];\n\
    \                next_second[position] = current_second[i];\n            }\n\n\
    \            std::vector<int> zero_first(\n                next_first.begin(),\n\
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
    \ {\n            int l0 = _matrix[level].rank0(l);\n            int r0 = _matrix[level].rank0(r);\n\
    \            int zeros = _zero_first_matrix[level].range_freq(\n             \
    \   l0,\n                r0,\n                first_l,\n                first_r\n\
    \            );\n            if (k < zeros) {\n                l = l0;\n     \
    \           r = r0;\n            } else {\n                k -= zeros;\n     \
    \           second_rank |= 1 << (_log - 1 - level);\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            }\n        }\n        return _second_coordinates[second_rank];\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/wavelet_matrix_2d.test.cpp\"\
    \n\n#line 8 \"verify/ds/range_query/wavelet_matrix_2d.test.cpp\"\n#include <iostream>\n\
    #line 11 \"verify/ds/range_query/wavelet_matrix_2d.test.cpp\"\n\nnamespace {\n\
    \nusing Matrix = m1une::ds::WaveletMatrix2D<int, int>;\n\n#ifndef NDEBUG\nvoid\
    \ randomized_test() {\n    Matrix empty;\n    assert(empty.empty());\n    assert(empty.size()\
    \ == 0);\n    assert(empty.count(0, 0, -10, 10, -10, 10) == 0);\n\n    std::uint64_t\
    \ state = 20260713;\n    auto random = [&state]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 80; trial++) {\n        int n = int(random() % 40);\n   \
    \     std::vector<Matrix::value_type> values;\n        std::vector<int> first;\n\
    \        std::vector<int> second;\n        values.reserve(n);\n        first.reserve(n);\n\
    \        second.reserve(n);\n        for (int i = 0; i < n; i++) {\n         \
    \   int x = int(random() % 21) - 10;\n            int y = int(random() % 21) -\
    \ 10;\n            values.emplace_back(x, y);\n            first.push_back(x);\n\
    \            second.push_back(y);\n        }\n\n        Matrix matrix(values);\n\
    \        Matrix parallel(first, second);\n        assert(matrix.size() == n);\n\
    \        assert(matrix.empty() == (n == 0));\n        for (int i = 0; i < n; i++)\
    \ {\n            assert(matrix[i] == values[i]);\n            assert(parallel.access(i)\
    \ == values[i]);\n        }\n\n        for (int query = 0; query < 150; query++)\
    \ {\n            int l = int(random() % std::uint64_t(n + 1));\n            int\
    \ r = int(random() % std::uint64_t(n + 1));\n            if (r < l) std::swap(l,\
    \ r);\n            int first_lower = int(random() % 31) - 15;\n            int\
    \ first_upper = int(random() % 31) - 15;\n            int second_lower = int(random()\
    \ % 31) - 15;\n            int second_upper = int(random() % 31) - 15;\n     \
    \       if (first_upper < first_lower) {\n                std::swap(first_lower,\
    \ first_upper);\n            }\n            if (second_upper < second_lower) {\n\
    \                std::swap(second_lower, second_upper);\n            }\n\n   \
    \         int expected_count = 0;\n            std::vector<int> selected;\n  \
    \          for (int i = l; i < r; i++) {\n                if (first_lower <= values[i].first\
    \ &&\n                    values[i].first < first_upper) {\n                 \
    \   selected.push_back(values[i].second);\n                    if (second_lower\
    \ <= values[i].second &&\n                        values[i].second < second_upper)\
    \ {\n                        expected_count++;\n                    }\n      \
    \          }\n            }\n            std::sort(selected.begin(), selected.end());\n\
    \n            assert(\n                matrix.count(\n                    l,\n\
    \                    r,\n                    first_lower,\n                  \
    \  first_upper,\n                    second_lower,\n                    second_upper\n\
    \                ) == expected_count\n            );\n            assert(\n  \
    \              parallel.count(\n                    l,\n                    r,\n\
    \                    first_lower,\n                    first_upper,\n        \
    \            second_lower,\n                    second_upper\n               \
    \ ) == expected_count\n            );\n            for (int k = 0; k < int(selected.size());\
    \ k++) {\n                assert(\n                    matrix.quantile(\n    \
    \                    l,\n                        r,\n                        first_lower,\n\
    \                        first_upper,\n                        k\n           \
    \         ) == selected[k]\n                );\n            }\n        }\n   \
    \ }\n\n    std::vector<Matrix::value_type> equal_values(20, Matrix::value_type(4,\
    \ 7));\n    Matrix equal_matrix(equal_values);\n    assert(equal_matrix.count(3,\
    \ 18, 4, 5, 7, 8) == 15);\n    assert(equal_matrix.quantile(3, 18, 4, 5, 14) ==\
    \ 7);\n}\n#endif\n\n}  // namespace\n\nint main() {\n#ifndef NDEBUG\n    randomized_test();\n\
    #endif\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n\
    \    int n, query_count;\n    std::cin >> n >> query_count;\n    std::vector<std::pair<int,\
    \ long long>> values(n);\n    for (auto& value : values) {\n        value.first\
    \ = 0;\n        std::cin >> value.second;\n    }\n\n    m1une::ds::WaveletMatrix2D<int,\
    \ long long> matrix(values);\n    while (query_count--) {\n        int l, r, k;\n\
    \        std::cin >> l >> r >> k;\n        std::cout << matrix.quantile(l, r,\
    \ 0, 1, k) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"../../../ds/range_query/wavelet_matrix_2d.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <utility>\n\
    #include <vector>\n\nnamespace {\n\nusing Matrix = m1une::ds::WaveletMatrix2D<int,\
    \ int>;\n\n#ifndef NDEBUG\nvoid randomized_test() {\n    Matrix empty;\n    assert(empty.empty());\n\
    \    assert(empty.size() == 0);\n    assert(empty.count(0, 0, -10, 10, -10, 10)\
    \ == 0);\n\n    std::uint64_t state = 20260713;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 80; trial++) {\n        int\
    \ n = int(random() % 40);\n        std::vector<Matrix::value_type> values;\n \
    \       std::vector<int> first;\n        std::vector<int> second;\n        values.reserve(n);\n\
    \        first.reserve(n);\n        second.reserve(n);\n        for (int i = 0;\
    \ i < n; i++) {\n            int x = int(random() % 21) - 10;\n            int\
    \ y = int(random() % 21) - 10;\n            values.emplace_back(x, y);\n     \
    \       first.push_back(x);\n            second.push_back(y);\n        }\n\n \
    \       Matrix matrix(values);\n        Matrix parallel(first, second);\n    \
    \    assert(matrix.size() == n);\n        assert(matrix.empty() == (n == 0));\n\
    \        for (int i = 0; i < n; i++) {\n            assert(matrix[i] == values[i]);\n\
    \            assert(parallel.access(i) == values[i]);\n        }\n\n        for\
    \ (int query = 0; query < 150; query++) {\n            int l = int(random() %\
    \ std::uint64_t(n + 1));\n            int r = int(random() % std::uint64_t(n +\
    \ 1));\n            if (r < l) std::swap(l, r);\n            int first_lower =\
    \ int(random() % 31) - 15;\n            int first_upper = int(random() % 31) -\
    \ 15;\n            int second_lower = int(random() % 31) - 15;\n            int\
    \ second_upper = int(random() % 31) - 15;\n            if (first_upper < first_lower)\
    \ {\n                std::swap(first_lower, first_upper);\n            }\n   \
    \         if (second_upper < second_lower) {\n                std::swap(second_lower,\
    \ second_upper);\n            }\n\n            int expected_count = 0;\n     \
    \       std::vector<int> selected;\n            for (int i = l; i < r; i++) {\n\
    \                if (first_lower <= values[i].first &&\n                    values[i].first\
    \ < first_upper) {\n                    selected.push_back(values[i].second);\n\
    \                    if (second_lower <= values[i].second &&\n               \
    \         values[i].second < second_upper) {\n                        expected_count++;\n\
    \                    }\n                }\n            }\n            std::sort(selected.begin(),\
    \ selected.end());\n\n            assert(\n                matrix.count(\n   \
    \                 l,\n                    r,\n                    first_lower,\n\
    \                    first_upper,\n                    second_lower,\n       \
    \             second_upper\n                ) == expected_count\n            );\n\
    \            assert(\n                parallel.count(\n                    l,\n\
    \                    r,\n                    first_lower,\n                  \
    \  first_upper,\n                    second_lower,\n                    second_upper\n\
    \                ) == expected_count\n            );\n            for (int k =\
    \ 0; k < int(selected.size()); k++) {\n                assert(\n             \
    \       matrix.quantile(\n                        l,\n                       \
    \ r,\n                        first_lower,\n                        first_upper,\n\
    \                        k\n                    ) == selected[k]\n           \
    \     );\n            }\n        }\n    }\n\n    std::vector<Matrix::value_type>\
    \ equal_values(20, Matrix::value_type(4, 7));\n    Matrix equal_matrix(equal_values);\n\
    \    assert(equal_matrix.count(3, 18, 4, 5, 7, 8) == 15);\n    assert(equal_matrix.quantile(3,\
    \ 18, 4, 5, 14) == 7);\n}\n#endif\n\n}  // namespace\n\nint main() {\n#ifndef\
    \ NDEBUG\n    randomized_test();\n#endif\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, query_count;\n    std::cin >> n >> query_count;\n\
    \    std::vector<std::pair<int, long long>> values(n);\n    for (auto& value :\
    \ values) {\n        value.first = 0;\n        std::cin >> value.second;\n   \
    \ }\n\n    m1une::ds::WaveletMatrix2D<int, long long> matrix(values);\n    while\
    \ (query_count--) {\n        int l, r, k;\n        std::cin >> l >> r >> k;\n\
    \        std::cout << matrix.quantile(l, r, 0, 1, k) << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/wavelet_matrix_2d.hpp
  isVerificationFile: true
  path: verify/ds/range_query/wavelet_matrix_2d.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 03:27:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/wavelet_matrix_2d.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/wavelet_matrix_2d.test.cpp
- /verify/verify/ds/range_query/wavelet_matrix_2d.test.cpp.html
title: verify/ds/range_query/wavelet_matrix_2d.test.cpp
---
