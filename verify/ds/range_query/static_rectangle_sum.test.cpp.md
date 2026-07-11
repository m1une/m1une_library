---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/static_rectangle_sum.hpp
    title: Static Rectangle Sum
  - icon: ':heavy_check_mark:'
    path: ds/range_query/wavelet_matrix_sum.hpp
    title: Wavelet Matrix with Sums
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/rectangle_sum
  bundledCode: "#line 1 \"verify/ds/range_query/static_rectangle_sum.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#line 1 \"\
    ds/range_query/static_rectangle_sum.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"ds/range_query/wavelet_matrix_sum.hpp\"\n\n\n\n#include <bit>\n#line 6 \"\
    ds/range_query/wavelet_matrix_sum.hpp\"\n#include <concepts>\n#include <cstdint>\n\
    #include <limits>\n#include <optional>\n#include <type_traits>\n#line 13 \"ds/range_query/wavelet_matrix_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A static wavelet matrix with additive\
    \ weights.\n// By default, each value is also used as its weight.\ntemplate <std::integral\
    \ T, typename Sum = T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nstruct\
    \ WaveletMatrixSum {\n    using value_type = T;\n    using sum_type = Sum;\n \
    \   using unsigned_type = std::make_unsigned_t<T>;\n\n   private:\n    static\
    \ constexpr int bit_width = std::numeric_limits<unsigned_type>::digits;\n    static\
    \ constexpr unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
    \ {\n            return unsigned_type(1) << (bit_width - 1);\n        } else {\n\
    \            return unsigned_type(0);\n        }\n    }();\n\n    struct BitVector\
    \ {\n        std::vector<std::uint64_t> bits;\n        std::vector<int> prefix;\n\
    \n        BitVector() = default;\n\n        explicit BitVector(int n)\n      \
    \      : bits((std::size_t(n) + 63) >> 6, 0),\n              prefix(bits.size()\
    \ + 1, 0) {}\n\n        void set(int p) {\n            bits[std::size_t(p) >>\
    \ 6] |= std::uint64_t(1) << (p & 63);\n        }\n\n        void build() {\n \
    \           for (std::size_t i = 0; i < bits.size(); i++) {\n                prefix[i\
    \ + 1] = prefix[i] + std::popcount(bits[i]);\n            }\n        }\n\n   \
    \     bool get(int p) const {\n            return (bits[std::size_t(p) >> 6] >>\
    \ (p & 63)) & 1;\n        }\n\n        int rank1(int r) const {\n            std::size_t\
    \ word = std::size_t(r) >> 6;\n            int offset = r & 63;\n            int\
    \ result = prefix[word];\n            if (offset != 0) {\n                result\
    \ += std::popcount(\n                    bits[word] & ((std::uint64_t(1) << offset)\
    \ - 1)\n                );\n            }\n            return result;\n      \
    \  }\n\n        int rank0(int r) const {\n            return r - rank1(r);\n \
    \       }\n    };\n\n    int _n;\n    std::vector<BitVector> _matrix;\n    std::vector<int>\
    \ _zero_count;\n    std::vector<std::vector<Sum>> _zero_prefix;\n    std::vector<Sum>\
    \ _original_prefix;\n    std::vector<Sum> _final_prefix;\n\n    static unsigned_type\
    \ encode(T value) {\n        unsigned_type bits;\n        if constexpr (std::signed_integral<T>)\
    \ {\n            bits = std::bit_cast<unsigned_type>(value);\n        } else {\n\
    \            bits = value;\n        }\n        return bits ^ sign_mask;\n    }\n\
    \n    static T decode(unsigned_type key) {\n        unsigned_type bits = key ^\
    \ sign_mask;\n        if constexpr (std::signed_integral<T>) {\n            return\
    \ std::bit_cast<T>(bits);\n        } else {\n            return bits;\n      \
    \  }\n    }\n\n    static bool bit(unsigned_type value, int level) {\n       \
    \ return (value >> (bit_width - 1 - level)) & unsigned_type(1);\n    }\n\n   \
    \ Sum zero_sum(int level, int l, int r) const {\n        return _zero_prefix[level][r]\
    \ - _zero_prefix[level][l];\n    }\n\n    Sum sum_less_encoded(int l, int r, unsigned_type\
    \ upper) const {\n        Sum result{};\n        for (int level = 0; level < bit_width;\
    \ level++) {\n            int l0 = _matrix[level].rank0(l);\n            int r0\
    \ = _matrix[level].rank0(r);\n            if (bit(upper, level)) {\n         \
    \       result = result + zero_sum(level, l, r);\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            } else {\n                l = l0;\n                r = r0;\n    \
    \        }\n        }\n        return result;\n    }\n\n    int count_less_encoded(int\
    \ l, int r, unsigned_type upper) const {\n        int result = 0;\n        for\
    \ (int level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            if (bit(upper, level))\
    \ {\n                result += r0 - l0;\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            } else {\n                l = l0;\n                r = r0;\n    \
    \        }\n        }\n        return result;\n    }\n\n    void build(const std::vector<T>&\
    \ values, const std::vector<Sum>& weights) {\n        assert(values.size() ==\
    \ weights.size());\n\n        std::vector<unsigned_type> current_keys(_n);\n \
    \       std::vector<unsigned_type> next_keys(_n);\n        std::vector<Sum> current_weights(weights);\n\
    \        std::vector<Sum> next_weights(_n);\n        for (int i = 0; i < _n; i++)\
    \ current_keys[i] = encode(values[i]);\n\n        _original_prefix.assign(std::size_t(_n)\
    \ + 1, Sum{});\n        for (int i = 0; i < _n; i++) {\n            _original_prefix[i\
    \ + 1] = _original_prefix[i] + weights[i];\n        }\n\n        _matrix.reserve(bit_width);\n\
    \        _zero_prefix.reserve(bit_width);\n        for (int level = 0; level <\
    \ bit_width; level++) {\n            _matrix.emplace_back(_n);\n            _zero_prefix.emplace_back(std::size_t(_n)\
    \ + 1, Sum{});\n            for (int i = 0; i < _n; i++) {\n                bool\
    \ one = bit(current_keys[i], level);\n                if (one) _matrix.back().set(i);\n\
    \                _zero_prefix.back()[i + 1] = _zero_prefix.back()[i];\n      \
    \          if (!one) {\n                    _zero_prefix.back()[i + 1] =\n   \
    \                     _zero_prefix.back()[i + 1] + current_weights[i];\n     \
    \           }\n            }\n            _matrix.back().build();\n\n        \
    \    int zeros = _matrix.back().rank0(_n);\n            _zero_count[level] = zeros;\n\
    \            int zero_pos = 0;\n            int one_pos = zeros;\n           \
    \ for (int i = 0; i < _n; i++) {\n                if (bit(current_keys[i], level))\
    \ {\n                    next_keys[one_pos] = current_keys[i];\n             \
    \       next_weights[one_pos] = current_weights[i];\n                    one_pos++;\n\
    \                } else {\n                    next_keys[zero_pos] = current_keys[i];\n\
    \                    next_weights[zero_pos] = current_weights[i];\n          \
    \          zero_pos++;\n                }\n            }\n            current_keys.swap(next_keys);\n\
    \            current_weights.swap(next_weights);\n        }\n\n        _final_prefix.assign(std::size_t(_n)\
    \ + 1, Sum{});\n        for (int i = 0; i < _n; i++) {\n            _final_prefix[i\
    \ + 1] = _final_prefix[i] + current_weights[i];\n        }\n    }\n\n   public:\n\
    \    WaveletMatrixSum()\n        : _n(0),\n          _matrix(bit_width),\n   \
    \       _zero_count(bit_width, 0),\n          _zero_prefix(bit_width, std::vector<Sum>(1,\
    \ Sum{})),\n          _original_prefix(1, Sum{}),\n          _final_prefix(1,\
    \ Sum{}) {}\n\n    explicit WaveletMatrixSum(const std::vector<T>& values)\n \
    \       requires std::convertible_to<T, Sum>\n        : _n(int(values.size())),\n\
    \          _matrix(),\n          _zero_count(bit_width, 0) {\n        std::vector<Sum>\
    \ weights;\n        weights.reserve(values.size());\n        for (T value : values)\
    \ weights.push_back(static_cast<Sum>(value));\n        build(values, weights);\n\
    \    }\n\n    WaveletMatrixSum(\n        const std::vector<T>& values,\n     \
    \   const std::vector<Sum>& weights\n    ) : _n(int(values.size())),\n       \
    \ _matrix(),\n        _zero_count(bit_width, 0) {\n        build(values, weights);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    T access(int p) const {\n   \
    \     assert(0 <= p && p < _n);\n        unsigned_type key = 0;\n        for (int\
    \ level = 0; level < bit_width; level++) {\n            bool one = _matrix[level].get(p);\n\
    \            if (one) {\n                key |= unsigned_type(1) << (bit_width\
    \ - 1 - level);\n                p = _zero_count[level] + _matrix[level].rank1(p);\n\
    \            } else {\n                p = _matrix[level].rank0(p);\n        \
    \    }\n        }\n        return decode(key);\n    }\n\n    T operator[](int\
    \ p) const {\n        return access(p);\n    }\n\n    int rank(T value, int r)\
    \ const {\n        assert(0 <= r && r <= _n);\n        return rank(value, 0, r);\n\
    \    }\n\n    int rank(T value, int l, int r) const {\n        assert(0 <= l &&\
    \ l <= r && r <= _n);\n        unsigned_type key = encode(value);\n        for\
    \ (int level = 0; level < bit_width; level++) {\n            if (bit(key, level))\
    \ {\n                l = _zero_count[level] + _matrix[level].rank1(l);\n     \
    \           r = _zero_count[level] + _matrix[level].rank1(r);\n            } else\
    \ {\n                l = _matrix[level].rank0(l);\n                r = _matrix[level].rank0(r);\n\
    \            }\n        }\n        return r - l;\n    }\n\n    T kth_smallest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        unsigned_type key = 0;\n        for\
    \ (int level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            int zeros = r0 - l0;\n\
    \            if (k < zeros) {\n                l = l0;\n                r = r0;\n\
    \            } else {\n                k -= zeros;\n                key |= unsigned_type(1)\
    \ << (bit_width - 1 - level);\n                l = _zero_count[level] + _matrix[level].rank1(l);\n\
    \                r = _zero_count[level] + _matrix[level].rank1(r);\n         \
    \   }\n        }\n        return decode(key);\n    }\n\n    T kth_largest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        return kth_smallest(l, r, r - l -\
    \ 1 - k);\n    }\n\n    int range_freq(int l, int r, T upper) const {\n      \
    \  assert(0 <= l && l <= r && r <= _n);\n        return count_less_encoded(l,\
    \ r, encode(upper));\n    }\n\n    int range_freq(int l, int r, T lower, T upper)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        if (upper <=\
    \ lower) return 0;\n        return range_freq(l, r, upper) - range_freq(l, r,\
    \ lower);\n    }\n\n    std::optional<T> prev_value(int l, int r, T upper) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        int count = range_freq(l,\
    \ r, upper);\n        if (count == 0) return std::nullopt;\n        return kth_smallest(l,\
    \ r, count - 1);\n    }\n\n    std::optional<T> next_value(int l, int r, T lower)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        int count = range_freq(l,\
    \ r, lower);\n        if (count == r - l) return std::nullopt;\n        return\
    \ kth_smallest(l, r, count);\n    }\n\n    Sum range_sum(int l, int r) const {\n\
    \        assert(0 <= l && l <= r && r <= _n);\n        return _original_prefix[r]\
    \ - _original_prefix[l];\n    }\n\n    Sum range_sum(int l, int r, T upper) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        return sum_less_encoded(l,\
    \ r, encode(upper));\n    }\n\n    Sum range_sum(int l, int r, T lower, T upper)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        if (upper <=\
    \ lower) return Sum{};\n        return range_sum(l, r, upper) - range_sum(l, r,\
    \ lower);\n    }\n\n    Sum sum_k_smallest(int l, int r, int k) const {\n    \
    \    assert(0 <= l && l <= r && r <= _n);\n        assert(0 <= k && k <= r - l);\n\
    \        Sum result{};\n        for (int level = 0; level < bit_width; level++)\
    \ {\n            int l0 = _matrix[level].rank0(l);\n            int r0 = _matrix[level].rank0(r);\n\
    \            int zeros = r0 - l0;\n            if (k < zeros) {\n            \
    \    l = l0;\n                r = r0;\n            } else {\n                result\
    \ = result + zero_sum(level, l, r);\n                k -= zeros;\n           \
    \     l = _zero_count[level] + _matrix[level].rank1(l);\n                r = _zero_count[level]\
    \ + _matrix[level].rank1(r);\n            }\n        }\n        return result\
    \ + (_final_prefix[l + k] - _final_prefix[l]);\n    }\n\n    Sum sum_k_largest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k <= r - l);\n        return range_sum(l, r) - sum_k_smallest(l,\
    \ r, r - l - k);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n\
    #line 11 \"ds/range_query/static_rectangle_sum.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <class X, class Y = X, class Sum = long long>\nclass StaticRectangleSum\
    \ {\n   public:\n    using x_type = X;\n    using y_type = Y;\n    using sum_type\
    \ = Sum;\n    using weighted_point_type = std::tuple<X, Y, Sum>;\n\n   private:\n\
    \    std::vector<X> _x_coordinates;\n    std::vector<Y> _y_coordinates;\n    WaveletMatrixSum<int,\
    \ Sum> _matrix;\n\n   public:\n    StaticRectangleSum() = default;\n\n    explicit\
    \ StaticRectangleSum(\n        const std::vector<weighted_point_type>& points\n\
    \    ) {\n        build(points);\n    }\n\n    StaticRectangleSum(\n        const\
    \ std::vector<X>& x_coordinates,\n        const std::vector<Y>& y_coordinates,\n\
    \        const std::vector<Sum>& weights\n    ) {\n        build(x_coordinates,\
    \ y_coordinates, weights);\n    }\n\n    void build(std::vector<weighted_point_type>\
    \ points) {\n        std::sort(\n            points.begin(),\n            points.end(),\n\
    \            [](const weighted_point_type& first,\n               const weighted_point_type&\
    \ second) {\n                if (std::get<0>(first) < std::get<0>(second)) return\
    \ true;\n                if (std::get<0>(second) < std::get<0>(first)) return\
    \ false;\n                return std::get<1>(first) < std::get<1>(second);\n \
    \           }\n        );\n\n        const int n = int(points.size());\n     \
    \   _x_coordinates.resize(n);\n        _y_coordinates.clear();\n        _y_coordinates.reserve(n);\n\
    \        for (const auto& point : points) {\n            _y_coordinates.push_back(std::get<1>(point));\n\
    \        }\n        std::sort(_y_coordinates.begin(), _y_coordinates.end());\n\
    \        _y_coordinates.erase(\n            std::unique(\n                _y_coordinates.begin(),\n\
    \                _y_coordinates.end(),\n                [](const Y& first, const\
    \ Y& second) {\n                    return !(first < second) && !(second < first);\n\
    \                }\n            ),\n            _y_coordinates.end()\n       \
    \ );\n\n        std::vector<int> y_rank(n);\n        std::vector<Sum> weights(n);\n\
    \        for (int index = 0; index < n; index++) {\n            _x_coordinates[index]\
    \ = std::get<0>(points[index]);\n            y_rank[index] = int(\n          \
    \      std::lower_bound(\n                    _y_coordinates.begin(),\n      \
    \              _y_coordinates.end(),\n                    std::get<1>(points[index])\n\
    \                ) - _y_coordinates.begin()\n            );\n            weights[index]\
    \ = std::get<2>(points[index]);\n        }\n        _matrix = WaveletMatrixSum<int,\
    \ Sum>(y_rank, weights);\n    }\n\n    void build(\n        const std::vector<X>&\
    \ x_coordinates,\n        const std::vector<Y>& y_coordinates,\n        const\
    \ std::vector<Sum>& weights\n    ) {\n        assert(x_coordinates.size() == y_coordinates.size());\n\
    \        assert(x_coordinates.size() == weights.size());\n        std::vector<weighted_point_type>\
    \ points;\n        points.reserve(x_coordinates.size());\n        for (int index\
    \ = 0; index < int(x_coordinates.size()); index++) {\n            points.emplace_back(\n\
    \                x_coordinates[index],\n                y_coordinates[index],\n\
    \                weights[index]\n            );\n        }\n        build(std::move(points));\n\
    \    }\n\n    int size() const {\n        return int(_x_coordinates.size());\n\
    \    }\n\n    bool empty() const {\n        return _x_coordinates.empty();\n \
    \   }\n\n    Sum sum(\n        const X& left,\n        const X& right,\n     \
    \   const Y& lower,\n        const Y& upper\n    ) const {\n        assert(!(right\
    \ < left));\n        assert(!(upper < lower));\n        int x_left = int(\n  \
    \          std::lower_bound(\n                _x_coordinates.begin(),\n      \
    \          _x_coordinates.end(),\n                left\n            ) - _x_coordinates.begin()\n\
    \        );\n        int x_right = int(\n            std::lower_bound(\n     \
    \           _x_coordinates.begin(),\n                _x_coordinates.end(),\n \
    \               right\n            ) - _x_coordinates.begin()\n        );\n  \
    \      int y_lower = int(\n            std::lower_bound(\n                _y_coordinates.begin(),\n\
    \                _y_coordinates.end(),\n                lower\n            ) -\
    \ _y_coordinates.begin()\n        );\n        int y_upper = int(\n           \
    \ std::lower_bound(\n                _y_coordinates.begin(),\n               \
    \ _y_coordinates.end(),\n                upper\n            ) - _y_coordinates.begin()\n\
    \        );\n        return _matrix.range_sum(x_left, x_right, y_lower, y_upper);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/static_rectangle_sum.test.cpp\"\
    \n\n#line 8 \"verify/ds/range_query/static_rectangle_sum.test.cpp\"\n#include\
    \ <iostream>\n#line 11 \"verify/ds/range_query/static_rectangle_sum.test.cpp\"\
    \n\nnamespace {\n\nusing Query = m1une::ds::StaticRectangleSum<int, int, long\
    \ long>;\nusing Point = Query::weighted_point_type;\n\nvoid randomized_test()\
    \ {\n    Query empty;\n    assert(empty.empty());\n    assert(empty.size() ==\
    \ 0);\n    assert(empty.sum(-10, 10, -10, 10) == 0);\n\n    std::uint64_t state\
    \ = 941;\n    auto random = [&state]() {\n        state ^= state << 7;\n     \
    \   state ^= state >> 9;\n        return state;\n    };\n\n    for (int trial\
    \ = 0; trial < 500; trial++) {\n        int n = int(random() % 50);\n        std::vector<Point>\
    \ points;\n        std::vector<int> xs;\n        std::vector<int> ys;\n      \
    \  std::vector<long long> weights;\n        points.reserve(n);\n        xs.reserve(n);\n\
    \        ys.reserve(n);\n        weights.reserve(n);\n        for (int index =\
    \ 0; index < n; index++) {\n            int x = int(random() % 31) - 15;\n   \
    \         int y = int(random() % 31) - 15;\n            long long weight = static_cast<long\
    \ long>(random() % 41) - 20;\n            points.emplace_back(x, y, weight);\n\
    \            xs.push_back(x);\n            ys.push_back(y);\n            weights.push_back(weight);\n\
    \        }\n\n        Query tuple_query(points);\n        Query vector_query(xs,\
    \ ys, weights);\n        assert(tuple_query.size() == n);\n        assert(vector_query.size()\
    \ == n);\n\n        for (int query_index = 0; query_index < 300; query_index++)\
    \ {\n            int left = int(random() % 41) - 20;\n            int right =\
    \ int(random() % 41) - 20;\n            int lower = int(random() % 41) - 20;\n\
    \            int upper = int(random() % 41) - 20;\n            if (right < left)\
    \ std::swap(left, right);\n            if (upper < lower) std::swap(lower, upper);\n\
    \n            long long expected = 0;\n            for (const auto& point : points)\
    \ {\n                auto [x, y, weight] = point;\n                if (left <=\
    \ x && x < right && lower <= y && y < upper) {\n                    expected +=\
    \ weight;\n                }\n            }\n            assert(tuple_query.sum(left,\
    \ right, lower, upper) == expected);\n            assert(vector_query.sum(left,\
    \ right, lower, upper) == expected);\n        }\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    randomized_test();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, query_count;\n    std::cin >> n >> query_count;\n\
    \    std::vector<Point> points;\n    points.reserve(n);\n    for (int index =\
    \ 0; index < n; index++) {\n        int x, y;\n        long long weight;\n   \
    \     std::cin >> x >> y >> weight;\n        points.emplace_back(x, y, weight);\n\
    \    }\n\n    Query rectangle_sum(points);\n    while (query_count--) {\n    \
    \    int left, lower, right, upper;\n        std::cin >> left >> lower >> right\
    \ >> upper;\n        std::cout << rectangle_sum.sum(left, right, lower, upper)\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n\n#include\
    \ \"../../../ds/range_query/static_rectangle_sum.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <tuple>\n\
    #include <vector>\n\nnamespace {\n\nusing Query = m1une::ds::StaticRectangleSum<int,\
    \ int, long long>;\nusing Point = Query::weighted_point_type;\n\nvoid randomized_test()\
    \ {\n    Query empty;\n    assert(empty.empty());\n    assert(empty.size() ==\
    \ 0);\n    assert(empty.sum(-10, 10, -10, 10) == 0);\n\n    std::uint64_t state\
    \ = 941;\n    auto random = [&state]() {\n        state ^= state << 7;\n     \
    \   state ^= state >> 9;\n        return state;\n    };\n\n    for (int trial\
    \ = 0; trial < 500; trial++) {\n        int n = int(random() % 50);\n        std::vector<Point>\
    \ points;\n        std::vector<int> xs;\n        std::vector<int> ys;\n      \
    \  std::vector<long long> weights;\n        points.reserve(n);\n        xs.reserve(n);\n\
    \        ys.reserve(n);\n        weights.reserve(n);\n        for (int index =\
    \ 0; index < n; index++) {\n            int x = int(random() % 31) - 15;\n   \
    \         int y = int(random() % 31) - 15;\n            long long weight = static_cast<long\
    \ long>(random() % 41) - 20;\n            points.emplace_back(x, y, weight);\n\
    \            xs.push_back(x);\n            ys.push_back(y);\n            weights.push_back(weight);\n\
    \        }\n\n        Query tuple_query(points);\n        Query vector_query(xs,\
    \ ys, weights);\n        assert(tuple_query.size() == n);\n        assert(vector_query.size()\
    \ == n);\n\n        for (int query_index = 0; query_index < 300; query_index++)\
    \ {\n            int left = int(random() % 41) - 20;\n            int right =\
    \ int(random() % 41) - 20;\n            int lower = int(random() % 41) - 20;\n\
    \            int upper = int(random() % 41) - 20;\n            if (right < left)\
    \ std::swap(left, right);\n            if (upper < lower) std::swap(lower, upper);\n\
    \n            long long expected = 0;\n            for (const auto& point : points)\
    \ {\n                auto [x, y, weight] = point;\n                if (left <=\
    \ x && x < right && lower <= y && y < upper) {\n                    expected +=\
    \ weight;\n                }\n            }\n            assert(tuple_query.sum(left,\
    \ right, lower, upper) == expected);\n            assert(vector_query.sum(left,\
    \ right, lower, upper) == expected);\n        }\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    randomized_test();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, query_count;\n    std::cin >> n >> query_count;\n\
    \    std::vector<Point> points;\n    points.reserve(n);\n    for (int index =\
    \ 0; index < n; index++) {\n        int x, y;\n        long long weight;\n   \
    \     std::cin >> x >> y >> weight;\n        points.emplace_back(x, y, weight);\n\
    \    }\n\n    Query rectangle_sum(points);\n    while (query_count--) {\n    \
    \    int left, lower, right, upper;\n        std::cin >> left >> lower >> right\
    \ >> upper;\n        std::cout << rectangle_sum.sum(left, right, lower, upper)\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/static_rectangle_sum.hpp
  - ds/range_query/wavelet_matrix_sum.hpp
  isVerificationFile: true
  path: verify/ds/range_query/static_rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2026-07-12 04:19:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/static_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/static_rectangle_sum.test.cpp
- /verify/verify/ds/range_query/static_rectangle_sum.test.cpp.html
title: verify/ds/range_query/static_rectangle_sum.test.cpp
---
