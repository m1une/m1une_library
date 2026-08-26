---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: beats_acted_monoid/concept.hpp
    title: Beats Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: beats_acted_monoid/concept.hpp
    title: Beats Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp
    title: Range Chmin/Chmax/Add Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree_beats.hpp
    title: Generic Segment Tree Beats!
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
  bundledCode: "#line 1 \"verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <numeric>\n\
    #include <vector>\n\n#line 1 \"beats_acted_monoid/concept.hpp\"\n\n\n\n#include\
    \ <concepts>\n\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(typename\
    \ AM::value_type a, typename AM::value_type b, typename AM::operator_type f,\n\
    \                                 typename AM::operator_type g) {\n    // 1. Value\
    \ Monoid\n    typename AM::value_type;\n    { AM::id() } -> std::same_as<typename\
    \ AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;\n\
    \n    // 2. Operator Monoid\n    typename AM::operator_type;\n    { AM::op_id()\
    \ } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f, g) } ->\
    \ std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))\n\n\
    \    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n// Concept for acted monoids whose value monoid is a\
    \ commutative group.\n// The value operation must obey commutativity and inverse\
    \ laws.\ntemplate <typename AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM>\
    \ && requires(typename AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 7 \"beats_acted_monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace\
    \ beats_acted_monoid {\n\n// An acted monoid whose action may require descent\
    \ before it can be applied.\ntemplate <typename AM>\nconcept IsBeatsActedMonoid\
    \ = m1une::acted_monoid::IsActedMonoid<AM> &&\n    requires(typename AM::value_type\
    \ x, typename AM::operator_type f) {\n        { AM::can_apply(f, x) } -> std::same_as<bool>;\n\
    \    };\n\n}  // namespace beats_acted_monoid\n}  // namespace m1une\n\n\n#line\
    \ 1 \"beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp\"\n\n\n\n#line 7\
    \ \"beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp\"\n#include <limits>\n\
    \nnamespace m1une {\nnamespace beats_acted_monoid {\n\ntemplate <std::signed_integral\
    \ T>\nstruct RangeChminChmaxAddRangeSumNode {\n    T sum;\n    T maximum;\n  \
    \  T second_maximum;\n    T minimum;\n    T second_minimum;\n    int maximum_count;\n\
    \    int minimum_count;\n    int length;\n};\n\n// Beats acted monoid for range\
    \ chmin/chmax/add updates and range sum queries.\ntemplate <std::signed_integral\
    \ T = long long>\nstruct RangeChminChmaxAddRangeSum {\n    using value_type =\
    \ RangeChminChmaxAddRangeSumNode<T>;\n\n    // Represents f(x) = clamp(x + add,\
    \ lower, upper).\n    struct operator_type {\n        T add;\n        T lower;\n\
    \        T upper;\n    };\n\n    static constexpr bool commutative = true;\n \
    \   static constexpr bool operator_commutative = false;\n    static constexpr\
    \ T negative_infinity = std::numeric_limits<T>::lowest();\n    static constexpr\
    \ T positive_infinity = std::numeric_limits<T>::max();\n\n   private:\n    static\
    \ constexpr T shift_lower_bound(T bound, T add) {\n        return bound == negative_infinity\
    \ ? bound : bound + add;\n    }\n\n    static constexpr T shift_upper_bound(T\
    \ bound, T add) {\n        return bound == positive_infinity ? bound : bound +\
    \ add;\n    }\n\n    static constexpr void apply_add(value_type& value, T add)\
    \ {\n        if (value.length == 0 || add == T(0)) return;\n        value.sum\
    \ += add * T(value.length);\n        value.maximum += add;\n        value.minimum\
    \ += add;\n        if (value.maximum_count != value.length) {\n            value.second_maximum\
    \ += add;\n        }\n        if (value.minimum_count != value.length) {\n   \
    \         value.second_minimum += add;\n        }\n    }\n\n    static constexpr\
    \ bool can_apply_chmin(\n        const value_type& value,\n        T upper\n \
    \   ) {\n        return value.maximum <= upper ||\n            value.maximum_count\
    \ == value.length ||\n            value.second_maximum < upper;\n    }\n\n   \
    \ static constexpr void apply_chmin(value_type& value, T upper) {\n        if\
    \ (value.maximum <= upper) return;\n        assert(can_apply_chmin(value, upper));\n\
    \        value.sum +=\n            (upper - value.maximum) * T(value.maximum_count);\n\
    \        if (value.minimum == value.maximum) {\n            value.minimum = upper;\n\
    \        } else if (value.second_minimum == value.maximum) {\n            value.second_minimum\
    \ = upper;\n        }\n        value.maximum = upper;\n    }\n\n    static constexpr\
    \ bool can_apply_chmax(\n        const value_type& value,\n        T lower\n \
    \   ) {\n        return lower <= value.minimum ||\n            value.minimum_count\
    \ == value.length ||\n            lower < value.second_minimum;\n    }\n\n   \
    \ static constexpr void apply_chmax(value_type& value, T lower) {\n        if\
    \ (lower <= value.minimum) return;\n        assert(can_apply_chmax(value, lower));\n\
    \        value.sum +=\n            (lower - value.minimum) * T(value.minimum_count);\n\
    \        if (value.maximum == value.minimum) {\n            value.maximum = lower;\n\
    \        } else if (value.second_maximum == value.minimum) {\n            value.second_maximum\
    \ = lower;\n        }\n        value.minimum = lower;\n    }\n\n    static constexpr\
    \ value_type constant_value(T value, int length) {\n        return {\n       \
    \     value * T(length),\n            value,\n            negative_infinity,\n\
    \            value,\n            positive_infinity,\n            length,\n   \
    \         length,\n            length\n        };\n    }\n\n   public:\n    static\
    \ constexpr value_type id() {\n        return {\n            T(0),\n         \
    \   negative_infinity,\n            negative_infinity,\n            positive_infinity,\n\
    \            positive_infinity,\n            0,\n            0,\n            0\n\
    \        };\n    }\n\n    static constexpr value_type op(\n        const value_type&\
    \ left,\n        const value_type& right\n    ) {\n        if (left.length ==\
    \ 0) return right;\n        if (right.length == 0) return left;\n\n        value_type\
    \ result;\n        result.sum = left.sum + right.sum;\n        result.length =\
    \ left.length + right.length;\n\n        result.maximum = std::max(left.maximum,\
    \ right.maximum);\n        result.maximum_count = 0;\n        result.second_maximum\
    \ = negative_infinity;\n        if (left.maximum == result.maximum) {\n      \
    \      result.maximum_count += left.maximum_count;\n            result.second_maximum\
    \ = std::max(\n                result.second_maximum,\n                left.second_maximum\n\
    \            );\n        } else {\n            result.second_maximum = std::max(\n\
    \                result.second_maximum,\n                left.maximum\n      \
    \      );\n        }\n        if (right.maximum == result.maximum) {\n       \
    \     result.maximum_count += right.maximum_count;\n            result.second_maximum\
    \ = std::max(\n                result.second_maximum,\n                right.second_maximum\n\
    \            );\n        } else {\n            result.second_maximum = std::max(\n\
    \                result.second_maximum,\n                right.maximum\n     \
    \       );\n        }\n\n        result.minimum = std::min(left.minimum, right.minimum);\n\
    \        result.minimum_count = 0;\n        result.second_minimum = positive_infinity;\n\
    \        if (left.minimum == result.minimum) {\n            result.minimum_count\
    \ += left.minimum_count;\n            result.second_minimum = std::min(\n    \
    \            result.second_minimum,\n                left.second_minimum\n   \
    \         );\n        } else {\n            result.second_minimum = std::min(\n\
    \                result.second_minimum,\n                left.minimum\n      \
    \      );\n        }\n        if (right.minimum == result.minimum) {\n       \
    \     result.minimum_count += right.minimum_count;\n            result.second_minimum\
    \ = std::min(\n                result.second_minimum,\n                right.second_minimum\n\
    \            );\n        } else {\n            result.second_minimum = std::min(\n\
    \                result.second_minimum,\n                right.minimum\n     \
    \       );\n        }\n        return result;\n    }\n\n    static constexpr operator_type\
    \ op_id() {\n        return {T(0), negative_infinity, positive_infinity};\n  \
    \  }\n\n    // Returns f(g(x)).\n    static constexpr operator_type op_comp(\n\
    \        const operator_type& f,\n        const operator_type& g\n    ) {\n  \
    \      T lower = shift_lower_bound(g.lower, f.add);\n        T upper = shift_upper_bound(g.upper,\
    \ f.add);\n        return {\n            g.add + f.add,\n            std::clamp(lower,\
    \ f.lower, f.upper),\n            std::clamp(upper, f.lower, f.upper)\n      \
    \  };\n    }\n\n    static constexpr bool can_apply(\n        const operator_type&\
    \ f,\n        const value_type& value\n    ) {\n        if (value.length == 0\
    \ || f.lower == f.upper) return true;\n        value_type mapped = value;\n  \
    \      apply_add(mapped, f.add);\n        if (\n            mapped.maximum <=\
    \ f.lower ||\n            f.upper <= mapped.minimum\n        ) {\n           \
    \ return true;\n        }\n        if (!can_apply_chmax(mapped, f.lower)) return\
    \ false;\n        apply_chmax(mapped, f.lower);\n        return can_apply_chmin(mapped,\
    \ f.upper);\n    }\n\n    static constexpr value_type mapping(\n        const\
    \ operator_type& f,\n        const value_type& value\n    ) {\n        assert(can_apply(f,\
    \ value));\n        if (value.length == 0) return value;\n        if (f.lower\
    \ == f.upper) {\n            return constant_value(f.lower, value.length);\n \
    \       }\n        value_type result = value;\n        apply_add(result, f.add);\n\
    \        if (result.maximum <= f.lower) {\n            return constant_value(f.lower,\
    \ result.length);\n        }\n        if (f.upper <= result.minimum) {\n     \
    \       return constant_value(f.upper, result.length);\n        }\n        apply_chmax(result,\
    \ f.lower);\n        apply_chmin(result, f.upper);\n        return result;\n \
    \   }\n\n    static constexpr value_type make(const T& value) {\n        return\
    \ constant_value(value, 1);\n    }\n\n    static constexpr operator_type make_chmin(const\
    \ T& upper) {\n        return {T(0), negative_infinity, upper};\n    }\n\n   \
    \ static constexpr operator_type make_chmax(const T& lower) {\n        return\
    \ {T(0), lower, positive_infinity};\n    }\n\n    static constexpr operator_type\
    \ make_add(const T& add) {\n        return {add, negative_infinity, positive_infinity};\n\
    \    }\n};\n\n}  // namespace beats_acted_monoid\n}  // namespace m1une\n\n\n\
    #line 1 \"ds/segtree/segtree_beats.hpp\"\n\n\n\n#line 6 \"ds/segtree/segtree_beats.hpp\"\
    \n#include <utility>\n#line 8 \"ds/segtree/segtree_beats.hpp\"\n\n#line 1 \"math/bit_ceil.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nconstexpr\
    \ T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n)\
    \ x <<= 1;\n    return x;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 11 \"ds/segtree/segtree_beats.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\n\n// Generic Segment Tree Beats for actions that may require recursive descent.\n\
    template <m1une::beats_acted_monoid::IsBeatsActedMonoid ActedMonoid>\nstruct SegtreeBeats\
    \ {\n    using value_type = typename ActedMonoid::value_type;\n    using operator_type\
    \ = typename ActedMonoid::operator_type;\n    using T = value_type;\n    using\
    \ F = operator_type;\n\n   private:\n    int _n = 0;\n    int _size = 1;\n   \
    \ std::vector<T> _data;\n    std::vector<F> _lazy;\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ordinal) {\n        if constexpr (requires(F\
    \ g, T x, long long i) {\n            ActedMonoid::mapping(g, x, i);\n       \
    \ }) {\n            return ActedMonoid::mapping(f, value, ordinal);\n        }\
    \ else {\n            return ActedMonoid::mapping(f, value);\n        }\n    }\n\
    \n    static bool can_apply_at(const F& f, const T& value, long long ordinal)\
    \ {\n        if constexpr (requires(F g, T x, long long i) {\n            ActedMonoid::can_apply(g,\
    \ x, i);\n        }) {\n            return ActedMonoid::can_apply(f, value, ordinal);\n\
    \        } else {\n            return ActedMonoid::can_apply(f, value);\n    \
    \    }\n    }\n\n    static F shift_operator(const F& f, long long ordinal) {\n\
    \        if constexpr (requires(F g, long long i) {\n            ActedMonoid::op_shift(g,\
    \ i);\n        }) {\n            return ActedMonoid::op_shift(f, ordinal);\n \
    \       } else {\n            return f;\n        }\n    }\n\n    void initialize(std::vector<T>&&\
    \ values) {\n        _n = int(values.size());\n        _size = int(m1une::math::bit_ceil((unsigned\
    \ int)_n));\n        _data.assign(2 * _size, ActedMonoid::id());\n        _lazy.assign(_size,\
    \ ActedMonoid::op_id());\n        for (int i = 0; i < _n; ++i) {\n           \
    \ _data[_size + i] = std::move(values[i]);\n        }\n        for (int k = _size\
    \ - 1; k >= 1; --k) update(k);\n    }\n\n    void update(int node) {\n       \
    \ _data[node] = ActedMonoid::op(\n            _data[node * 2],\n            _data[node\
    \ * 2 + 1]\n        );\n    }\n\n    void all_apply(int node, int left, int right,\
    \ const F& f) {\n        if (_n <= left) return;\n        if (can_apply_at(f,\
    \ _data[node], 0)) {\n            _data[node] = mapping_at(f, _data[node], 0);\n\
    \            if (node < _size) {\n                _lazy[node] = ActedMonoid::op_comp(f,\
    \ _lazy[node]);\n            }\n            return;\n        }\n\n        assert(right\
    \ - left > 1);\n        push(node, left, right);\n        int middle = left +\
    \ (right - left) / 2;\n        all_apply(node * 2, left, middle, f);\n       \
    \ all_apply(\n            node * 2 + 1,\n            middle,\n            right,\n\
    \            shift_operator(f, middle - left)\n        );\n        update(node);\n\
    \    }\n\n    void push(int node, int left, int right) {\n        assert(right\
    \ - left > 1);\n        int middle = left + (right - left) / 2;\n        F f =\
    \ _lazy[node];\n        _lazy[node] = ActedMonoid::op_id();\n        all_apply(node\
    \ * 2, left, middle, f);\n        all_apply(\n            node * 2 + 1,\n    \
    \        middle,\n            right,\n            shift_operator(f, middle - left)\n\
    \        );\n    }\n\n    void set_impl(\n        int node,\n        int left,\n\
    \        int right,\n        int index,\n        T value\n    ) {\n        if\
    \ (right - left == 1) {\n            _data[node] = std::move(value);\n       \
    \     return;\n        }\n        push(node, left, right);\n        int middle\
    \ = left + (right - left) / 2;\n        if (index < middle) {\n            set_impl(node\
    \ * 2, left, middle, index, std::move(value));\n        } else {\n           \
    \ set_impl(\n                node * 2 + 1,\n                middle,\n        \
    \        right,\n                index,\n                std::move(value)\n  \
    \          );\n        }\n        update(node);\n    }\n\n    T get_impl(int node,\
    \ int left, int right, int index) {\n        if (right - left == 1) return _data[node];\n\
    \        push(node, left, right);\n        int middle = left + (right - left)\
    \ / 2;\n        if (index < middle) {\n            return get_impl(node * 2, left,\
    \ middle, index);\n        }\n        return get_impl(node * 2 + 1, middle, right,\
    \ index);\n    }\n\n    T prod_impl(\n        int node,\n        int left,\n \
    \       int right,\n        int query_left,\n        int query_right\n    ) {\n\
    \        if (\n            query_right <= left || right <= query_left || _n <=\
    \ left\n        ) {\n            return ActedMonoid::id();\n        }\n      \
    \  if (query_left <= left && right <= query_right) {\n            return _data[node];\n\
    \        }\n        push(node, left, right);\n        int middle = left + (right\
    \ - left) / 2;\n        return ActedMonoid::op(\n            prod_impl(\n    \
    \            node * 2,\n                left,\n                middle,\n     \
    \           query_left,\n                query_right\n            ),\n       \
    \     prod_impl(\n                node * 2 + 1,\n                middle,\n   \
    \             right,\n                query_left,\n                query_right\n\
    \            )\n        );\n    }\n\n    void apply_impl(\n        int node,\n\
    \        int left,\n        int right,\n        int query_left,\n        int query_right,\n\
    \        int base_left,\n        const F& f\n    ) {\n        if (\n         \
    \   query_right <= left || right <= query_left || _n <= left\n        ) {\n  \
    \          return;\n        }\n        if (query_left <= left && right <= query_right)\
    \ {\n            all_apply(\n                node,\n                left,\n  \
    \              right,\n                shift_operator(f, left - base_left)\n \
    \           );\n            return;\n        }\n        push(node, left, right);\n\
    \        int middle = left + (right - left) / 2;\n        apply_impl(\n      \
    \      node * 2,\n            left,\n            middle,\n            query_left,\n\
    \            query_right,\n            base_left,\n            f\n        );\n\
    \        apply_impl(\n            node * 2 + 1,\n            middle,\n       \
    \     right,\n            query_left,\n            query_right,\n            base_left,\n\
    \            f\n        );\n        update(node);\n    }\n\n    void collect_impl(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        std::vector<T>& result\n    ) {\n        if\
    \ (\n            query_right <= left || right <= query_left || _n <= left\n  \
    \      ) {\n            return;\n        }\n        if (right - left == 1) {\n\
    \            result.push_back(_data[node]);\n            return;\n        }\n\
    \        push(node, left, right);\n        int middle = left + (right - left)\
    \ / 2;\n        collect_impl(\n            node * 2,\n            left,\n    \
    \        middle,\n            query_left,\n            query_right,\n        \
    \    result\n        );\n        collect_impl(\n            node * 2 + 1,\n  \
    \          middle,\n            right,\n            query_left,\n            query_right,\n\
    \            result\n        );\n    }\n\n    template <class Predicate>\n   \
    \ bool max_right_impl(\n        int node,\n        int left,\n        int right,\n\
    \        int query_left,\n        Predicate& predicate,\n        T& product,\n\
    \        int& answer\n    ) {\n        if (right <= query_left || _n <= left)\
    \ return true;\n        if (query_left <= left) {\n            T next = ActedMonoid::op(product,\
    \ _data[node]);\n            if (predicate(next)) {\n                product =\
    \ std::move(next);\n                return true;\n            }\n            if\
    \ (right - left == 1) {\n                answer = left;\n                return\
    \ false;\n            }\n        }\n        push(node, left, right);\n       \
    \ int middle = left + (right - left) / 2;\n        if (!max_right_impl(\n    \
    \            node * 2,\n                left,\n                middle,\n     \
    \           query_left,\n                predicate,\n                product,\n\
    \                answer\n            )) {\n            return false;\n       \
    \ }\n        return max_right_impl(\n            node * 2 + 1,\n            middle,\n\
    \            right,\n            query_left,\n            predicate,\n       \
    \     product,\n            answer\n        );\n    }\n\n    template <class Predicate>\n\
    \    bool min_left_impl(\n        int node,\n        int left,\n        int right,\n\
    \        int query_right,\n        Predicate& predicate,\n        T& product,\n\
    \        int& answer\n    ) {\n        if (query_right <= left || _n <= left)\
    \ return true;\n        if (right <= query_right) {\n            T next = ActedMonoid::op(_data[node],\
    \ product);\n            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return true;\n            }\n            if (right - left ==\
    \ 1) {\n                answer = right;\n                return false;\n     \
    \       }\n        }\n        push(node, left, right);\n        int middle = left\
    \ + (right - left) / 2;\n        if (!min_left_impl(\n                node * 2\
    \ + 1,\n                middle,\n                right,\n                query_right,\n\
    \                predicate,\n                product,\n                answer\n\
    \            )) {\n            return false;\n        }\n        return min_left_impl(\n\
    \            node * 2,\n            left,\n            middle,\n            query_right,\n\
    \            predicate,\n            product,\n            answer\n        );\n\
    \    }\n\n   public:\n    SegtreeBeats() {\n        initialize({});\n    }\n\n\
    \    explicit SegtreeBeats(int n) {\n        assert(0 <= n);\n        initialize(std::vector<T>(n,\
    \ ActedMonoid::id()));\n    }\n\n    explicit SegtreeBeats(const std::vector<T>&\
    \ values) {\n        initialize(std::vector<T>(values));\n    }\n\n    explicit\
    \ SegtreeBeats(std::vector<T>&& values) {\n        initialize(std::move(values));\n\
    \    }\n\n    template <typename U>\n    requires (!std::same_as<U, T>) && (\n\
    \        requires(U x) { ActedMonoid::make(x); } ||\n        requires(U x, int\
    \ i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n\
    \    explicit SegtreeBeats(const std::vector<U>& values) {\n        std::vector<T>\
    \ converted;\n        converted.reserve(values.size());\n        for (int i =\
    \ 0; i < int(values.size()); ++i) {\n            if constexpr (requires(U x) {\
    \ ActedMonoid::make(x); }) {\n                converted.push_back(ActedMonoid::make(values[i]));\n\
    \            } else if constexpr (requires(U x, int index) {\n               \
    \ ActedMonoid::make(x, index);\n            }) {\n                converted.push_back(ActedMonoid::make(values[i],\
    \ i));\n            } else {\n                converted.push_back(static_cast<T>(values[i]));\n\
    \            }\n        }\n        initialize(std::move(converted));\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    void set(int index, T value) {\n      \
    \  assert(0 <= index && index < _n);\n        set_impl(1, 0, _size, index, std::move(value));\n\
    \    }\n\n    T get(int index) {\n        assert(0 <= index && index < _n);\n\
    \        return get_impl(1, 0, _size, index);\n    }\n\n    T operator[](int index)\
    \ {\n        return get(index);\n    }\n\n    T prod(int left, int right) {\n\
    \        assert(0 <= left && left <= right && right <= _n);\n        if (left\
    \ == right) return ActedMonoid::id();\n        return prod_impl(1, 0, _size, left,\
    \ right);\n    }\n\n    T all_prod() const {\n        return _data[1];\n    }\n\
    \n    void apply(int index, F f) {\n        assert(0 <= index && index < _n);\n\
    \        apply_impl(1, 0, _size, index, index + 1, index, f);\n    }\n\n    void\
    \ apply(int left, int right, F f) {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        if (left == right) return;\n        apply_impl(1,\
    \ 0, _size, left, right, left, f);\n    }\n\n    std::vector<T> to_vector() {\n\
    \        return to_vector(0, _n);\n    }\n\n    std::vector<T> to_vector(int left,\
    \ int right) {\n        assert(0 <= left && left <= right && right <= _n);\n \
    \       std::vector<T> result;\n        result.reserve(right - left);\n      \
    \  collect_impl(1, 0, _size, left, right, result);\n        return result;\n \
    \   }\n\n    template <class Predicate>\n    int max_right(int left, Predicate\
    \ predicate) {\n        assert(0 <= left && left <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (left == _n) return _n;\n        T product = ActedMonoid::id();\n\
    \        int answer = _n;\n        max_right_impl(\n            1,\n         \
    \   0,\n            _size,\n            left,\n            predicate,\n      \
    \      product,\n            answer\n        );\n        return answer;\n    }\n\
    \n    template <class Predicate>\n    int min_left(int right, Predicate predicate)\
    \ {\n        assert(0 <= right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == 0) return 0;\n        T product = ActedMonoid::id();\n \
    \       int answer = 0;\n        min_left_impl(\n            1,\n            0,\n\
    \            _size,\n            right,\n            predicate,\n            product,\n\
    \            answer\n        );\n        return answer;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line\
    \ 5 \"utilities/fast_io.hpp\"\n#include <array>\n#include <cerrno>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n\
    #include <type_traits>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\
    \nnamespace m1une {\nnamespace utilities {\n\nstruct FastOutput;\n\nnamespace\
    \ internal {\n\n// Shared with the convenience helpers in template.hpp.\ninline\
    \ FastOutput* standard_output_instance = nullptr;\n\n// Detect std::begin(x),\
    \ std::end(x).\ntemplate <class T, class = void>\nstruct is_range : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {\n        if (_stream == stdout\n          \
    \  && internal::standard_output_instance == nullptr) {\n            internal::standard_output_instance\
    \ = this;\n        }\n    }\n\n    FastOutput(const FastOutput&) = delete;\n \
    \   FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n        if (internal::standard_output_instance == this) {\n\
    \            internal::standard_output_instance = nullptr;\n        }\n    }\n\
    \n    void flush() {\n        if (_position != 0) {\n            std::fwrite(_buffer,\
    \ 1, _position, _stream);\n            _position = 0;\n        }\n        std::fflush(_stream);\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        std::size_t position = 0;\n        while (position\
    \ < s.size()) {\n            if (_position == buffer_size) flush();\n        \
    \    const std::size_t copied =\n                std::min<std::size_t>(buffer_size\
    \ - _position, s.size() - position);\n            std::memcpy(_buffer + _position,\
    \ s.data() + position, copied);\n            _position += int(copied);\n     \
    \       position += copied;\n        }\n    }\n\n    void write(char c) {\n  \
    \      write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 13 \"verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp\"\
    \n\nnamespace {\n\nusing AM =\n    m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long\
    \ long>;\n\nlong long apply_scalar(const AM::operator_type& f, long long value)\
    \ {\n    return std::clamp(value + f.add, f.lower, f.upper);\n}\n\nvoid test_composition()\
    \ {\n    std::vector<AM::operator_type> operators;\n    for (long long value =\
    \ -10; value <= 10; ++value) {\n        operators.emplace_back(AM::make_chmin(value));\n\
    \        operators.emplace_back(AM::make_chmax(value));\n        operators.emplace_back(AM::make_add(value));\n\
    \    }\n\n    for (const auto& f : operators) {\n        for (const auto& g :\
    \ operators) {\n            auto composition = AM::op_comp(f, g);\n          \
    \  for (long long value = -20; value <= 20; ++value) {\n                assert(\n\
    \                    apply_scalar(composition, value) ==\n                   \
    \ apply_scalar(f, apply_scalar(g, value))\n                );\n            }\n\
    \        }\n    }\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0x123456789abcdef0ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 300; ++trial) {\n        int size = int(random() % 80);\n        std::vector<long\
    \ long> values(size);\n        for (long long& value : values) {\n           \
    \ value = static_cast<long long>(random() % 201) - 100;\n        }\n        m1une::ds::SegtreeBeats<AM>\
    \ seg(values);\n\n        for (int operation = 0; operation < 500; ++operation)\
    \ {\n            int left = int(random() % (size + 1));\n            int right\
    \ = int(random() % (size + 1));\n            if (right < left) std::swap(left,\
    \ right);\n            int type = int(random() % 5);\n            long long value\
    \ =\n                static_cast<long long>(random() % 101) - 50;\n\n        \
    \    if (type == 0) {\n                seg.apply(left, right, AM::make_chmin(value));\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] = std::min(values[index], value);\n                }\n\
    \            } else if (type == 1) {\n                seg.apply(left, right, AM::make_chmax(value));\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] = std::max(values[index], value);\n                }\n\
    \            } else if (type == 2) {\n                seg.apply(left, right, AM::make_add(value));\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] += value;\n                }\n            } else {\n\
    \                long long expected = std::accumulate(\n                    values.begin()\
    \ + left,\n                    values.begin() + right,\n                    0LL\n\
    \                );\n                assert(seg.prod(left, right).sum == expected);\n\
    \            }\n\n            if (operation % 31 == 0) {\n                auto\
    \ actual = seg.to_vector();\n                for (int index = 0; index < size;\
    \ ++index) {\n                    assert(actual[index].sum == values[index]);\n\
    \                }\n            }\n        }\n    }\n}\n\nstatic_assert(m1une::beats_acted_monoid::IsBeatsActedMonoid<AM>);\n\
    static_assert(AM::commutative);\nstatic_assert(!AM::operator_commutative);\n\n\
    }  // namespace\n\nint main() {\n    test_composition();\n    test_randomized();\n\
    \n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int n, q;\n    fast_input >> n >> q;\n    std::vector<long\
    \ long> values(n);\n    for (long long& value : values) fast_input >> value;\n\
    \    m1une::ds::SegtreeBeats<AM> seg(values);\n\n    while (q--) {\n        int\
    \ type, left, right;\n        fast_input >> type >> left >> right;\n        if\
    \ (type == 0) {\n            long long value;\n            fast_input >> value;\n\
    \            seg.apply(left, right, AM::make_chmin(value));\n        } else if\
    \ (type == 1) {\n            long long value;\n            fast_input >> value;\n\
    \            seg.apply(left, right, AM::make_chmax(value));\n        } else if\
    \ (type == 2) {\n            long long value;\n            fast_input >> value;\n\
    \            seg.apply(left, right, AM::make_add(value));\n        } else {\n\
    \            fast_output << seg.prod(left, right).sum << '\\n';\n        }\n \
    \   }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <numeric>\n\
    #include <vector>\n\n#include \"../../beats_acted_monoid/concept.hpp\"\n#include\
    \ \"../../beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp\"\n#include \"\
    ../../ds/segtree/segtree_beats.hpp\"\n#include \"../../utilities/fast_io.hpp\"\
    \n\nnamespace {\n\nusing AM =\n    m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long\
    \ long>;\n\nlong long apply_scalar(const AM::operator_type& f, long long value)\
    \ {\n    return std::clamp(value + f.add, f.lower, f.upper);\n}\n\nvoid test_composition()\
    \ {\n    std::vector<AM::operator_type> operators;\n    for (long long value =\
    \ -10; value <= 10; ++value) {\n        operators.emplace_back(AM::make_chmin(value));\n\
    \        operators.emplace_back(AM::make_chmax(value));\n        operators.emplace_back(AM::make_add(value));\n\
    \    }\n\n    for (const auto& f : operators) {\n        for (const auto& g :\
    \ operators) {\n            auto composition = AM::op_comp(f, g);\n          \
    \  for (long long value = -20; value <= 20; ++value) {\n                assert(\n\
    \                    apply_scalar(composition, value) ==\n                   \
    \ apply_scalar(f, apply_scalar(g, value))\n                );\n            }\n\
    \        }\n    }\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0x123456789abcdef0ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 300; ++trial) {\n        int size = int(random() % 80);\n        std::vector<long\
    \ long> values(size);\n        for (long long& value : values) {\n           \
    \ value = static_cast<long long>(random() % 201) - 100;\n        }\n        m1une::ds::SegtreeBeats<AM>\
    \ seg(values);\n\n        for (int operation = 0; operation < 500; ++operation)\
    \ {\n            int left = int(random() % (size + 1));\n            int right\
    \ = int(random() % (size + 1));\n            if (right < left) std::swap(left,\
    \ right);\n            int type = int(random() % 5);\n            long long value\
    \ =\n                static_cast<long long>(random() % 101) - 50;\n\n        \
    \    if (type == 0) {\n                seg.apply(left, right, AM::make_chmin(value));\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] = std::min(values[index], value);\n                }\n\
    \            } else if (type == 1) {\n                seg.apply(left, right, AM::make_chmax(value));\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] = std::max(values[index], value);\n                }\n\
    \            } else if (type == 2) {\n                seg.apply(left, right, AM::make_add(value));\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] += value;\n                }\n            } else {\n\
    \                long long expected = std::accumulate(\n                    values.begin()\
    \ + left,\n                    values.begin() + right,\n                    0LL\n\
    \                );\n                assert(seg.prod(left, right).sum == expected);\n\
    \            }\n\n            if (operation % 31 == 0) {\n                auto\
    \ actual = seg.to_vector();\n                for (int index = 0; index < size;\
    \ ++index) {\n                    assert(actual[index].sum == values[index]);\n\
    \                }\n            }\n        }\n    }\n}\n\nstatic_assert(m1une::beats_acted_monoid::IsBeatsActedMonoid<AM>);\n\
    static_assert(AM::commutative);\nstatic_assert(!AM::operator_commutative);\n\n\
    }  // namespace\n\nint main() {\n    test_composition();\n    test_randomized();\n\
    \n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int n, q;\n    fast_input >> n >> q;\n    std::vector<long\
    \ long> values(n);\n    for (long long& value : values) fast_input >> value;\n\
    \    m1une::ds::SegtreeBeats<AM> seg(values);\n\n    while (q--) {\n        int\
    \ type, left, right;\n        fast_input >> type >> left >> right;\n        if\
    \ (type == 0) {\n            long long value;\n            fast_input >> value;\n\
    \            seg.apply(left, right, AM::make_chmin(value));\n        } else if\
    \ (type == 1) {\n            long long value;\n            fast_input >> value;\n\
    \            seg.apply(left, right, AM::make_chmax(value));\n        } else if\
    \ (type == 2) {\n            long long value;\n            fast_input >> value;\n\
    \            seg.apply(left, right, AM::make_add(value));\n        } else {\n\
    \            fast_output << seg.prod(left, right).sum << '\\n';\n        }\n \
    \   }\n}\n"
  dependsOn:
  - beats_acted_monoid/concept.hpp
  - acted_monoid/concept.hpp
  - beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp
  - ds/segtree/segtree_beats.hpp
  - beats_acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
  requiredBy: []
  timestamp: '2026-08-26 23:16:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
- /verify/verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp.html
title: verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
---
