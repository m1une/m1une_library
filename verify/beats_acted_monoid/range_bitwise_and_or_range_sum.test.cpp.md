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
    path: beats_acted_monoid/range_bitwise_and_or_range_sum.hpp
    title: Range Bitwise AND/OR Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree_beats.hpp
    title: Generic Segment Tree Beats!
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n\
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
    \ 1 \"beats_acted_monoid/range_bitwise_and_or_range_sum.hpp\"\n\n\n\n#line 6 \"\
    beats_acted_monoid/range_bitwise_and_or_range_sum.hpp\"\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace beats_acted_monoid {\n\ntemplate <typename T>\n\
    struct RangeBitwiseAndOrRangeSumNode {\n    T sum;\n    T bitwise_and;\n    T\
    \ bitwise_or;\n    long long length;\n};\n\n// Beats acted monoid for range bitwise\
    \ AND/OR updates and range sum queries.\ntemplate <typename T, int BITS = 30>\n\
    struct RangeBitwiseAndOrRangeSum {\n    static_assert(\n        std::is_integral_v<T>\
    \ &&\n        !std::is_same_v<std::remove_cv_t<T>, bool>\n    );\n    static_assert(0\
    \ < BITS && BITS <= std::numeric_limits<T>::digits);\n\n    using value_type =\
    \ RangeBitwiseAndOrRangeSumNode<T>;\n\n    // Represents f(x) = (x & and_mask)\
    \ | or_mask.\n    struct operator_type {\n        T and_mask;\n        T or_mask;\n\
    \    };\n\n    static constexpr bool commutative = true;\n    static constexpr\
    \ bool operator_commutative = false;\n\n    static constexpr T bit_mask() {\n\
    \        if constexpr (\n            std::is_unsigned_v<T> &&\n            BITS\
    \ == std::numeric_limits<T>::digits\n        ) {\n            return ~T(0);\n\
    \        } else {\n            return\n                (T(1) << (BITS - 1)) |\n\
    \                ((T(1) << (BITS - 1)) - 1);\n        }\n    }\n\n    static constexpr\
    \ value_type id() {\n        return {T(0), bit_mask(), T(0), 0};\n    }\n\n  \
    \  static constexpr value_type op(\n        const value_type& left,\n        const\
    \ value_type& right\n    ) {\n        return {\n            left.sum + right.sum,\n\
    \            left.bitwise_and & right.bitwise_and,\n            left.bitwise_or\
    \ | right.bitwise_or,\n            left.length + right.length\n        };\n  \
    \  }\n\n    static constexpr operator_type op_id() {\n        return {bit_mask(),\
    \ T(0)};\n    }\n\n    // Returns f(g(x)).\n    static constexpr operator_type\
    \ op_comp(\n        const operator_type& f,\n        const operator_type& g\n\
    \    ) {\n        return {\n            (f.and_mask & g.and_mask) & bit_mask(),\n\
    \            ((g.or_mask & f.and_mask) | f.or_mask) & bit_mask()\n        };\n\
    \    }\n\n    static constexpr bool can_apply(\n        const operator_type& f,\n\
    \        const value_type& value\n    ) {\n        if (value.length == 0) return\
    \ true;\n        T changed = ((~f.and_mask) | f.or_mask) & bit_mask();\n     \
    \   T mixed = value.bitwise_and ^ value.bitwise_or;\n        return (changed &\
    \ mixed) == T(0);\n    }\n\n    static constexpr value_type mapping(\n       \
    \ const operator_type& f,\n        const value_type& value\n    ) {\n        assert(can_apply(f,\
    \ value));\n        if (value.length == 0) return value;\n        T changed =\
    \ ((~f.and_mask) | f.or_mask) & bit_mask();\n        T old_uniform = value.bitwise_and\
    \ & changed;\n        T new_uniform =\n            ((old_uniform & f.and_mask)\
    \ | f.or_mask) & changed;\n\n        value_type result = value;\n        result.sum\
    \ +=\n            (new_uniform - old_uniform) * T(value.length);\n        result.bitwise_and\
    \ =\n            ((value.bitwise_and & f.and_mask) | f.or_mask) & bit_mask();\n\
    \        result.bitwise_or =\n            ((value.bitwise_or & f.and_mask) | f.or_mask)\
    \ & bit_mask();\n        return result;\n    }\n\n    static constexpr value_type\
    \ make(const T& value) {\n        assert((value & ~bit_mask()) == T(0));\n   \
    \     return {value, value, value, 1};\n    }\n\n    static constexpr operator_type\
    \ make_and(const T& mask) {\n        return {mask & bit_mask(), T(0)};\n    }\n\
    \n    static constexpr operator_type make_or(const T& mask) {\n        return\
    \ {bit_mask(), mask & bit_mask()};\n    }\n};\n\n}  // namespace beats_acted_monoid\n\
    }  // namespace m1une\n\n\n#line 1 \"ds/segtree/segtree_beats.hpp\"\n\n\n\n#line\
    \ 6 \"ds/segtree/segtree_beats.hpp\"\n#include <utility>\n#line 8 \"ds/segtree/segtree_beats.hpp\"\
    \n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\
    \ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n\
    \    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 11 \"ds/segtree/segtree_beats.hpp\"\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Generic Segment Tree Beats for actions\
    \ that may require recursive descent.\ntemplate <m1une::beats_acted_monoid::IsBeatsActedMonoid\
    \ ActedMonoid>\nstruct SegtreeBeats {\n    using value_type = typename ActedMonoid::value_type;\n\
    \    using operator_type = typename ActedMonoid::operator_type;\n    using T =\
    \ value_type;\n    using F = operator_type;\n\n   private:\n    int _n = 0;\n\
    \    int _size = 1;\n    std::vector<T> _data;\n    std::vector<F> _lazy;\n\n\
    \    static T mapping_at(const F& f, const T& value, long long ordinal) {\n  \
    \      if constexpr (requires(F g, T x, long long i) {\n            ActedMonoid::mapping(g,\
    \ x, i);\n        }) {\n            return ActedMonoid::mapping(f, value, ordinal);\n\
    \        } else {\n            return ActedMonoid::mapping(f, value);\n      \
    \  }\n    }\n\n    static bool can_apply_at(const F& f, const T& value, long long\
    \ ordinal) {\n        if constexpr (requires(F g, T x, long long i) {\n      \
    \      ActedMonoid::can_apply(g, x, i);\n        }) {\n            return ActedMonoid::can_apply(f,\
    \ value, ordinal);\n        } else {\n            return ActedMonoid::can_apply(f,\
    \ value);\n        }\n    }\n\n    static F shift_operator(const F& f, long long\
    \ ordinal) {\n        if constexpr (requires(F g, long long i) {\n           \
    \ ActedMonoid::op_shift(g, i);\n        }) {\n            return ActedMonoid::op_shift(f,\
    \ ordinal);\n        } else {\n            return f;\n        }\n    }\n\n   \
    \ void initialize(std::vector<T>&& values) {\n        _n = int(values.size());\n\
    \        _size = int(m1une::math::bit_ceil((unsigned int)_n));\n        _data.assign(2\
    \ * _size, ActedMonoid::id());\n        _lazy.assign(_size, ActedMonoid::op_id());\n\
    \        for (int i = 0; i < _n; ++i) {\n            _data[_size + i] = std::move(values[i]);\n\
    \        }\n        for (int k = _size - 1; k >= 1; --k) update(k);\n    }\n\n\
    \    void update(int node) {\n        _data[node] = ActedMonoid::op(\n       \
    \     _data[node * 2],\n            _data[node * 2 + 1]\n        );\n    }\n\n\
    \    void all_apply(int node, int left, int right, const F& f) {\n        if (_n\
    \ <= left) return;\n        if (can_apply_at(f, _data[node], 0)) {\n         \
    \   _data[node] = mapping_at(f, _data[node], 0);\n            if (node < _size)\
    \ {\n                _lazy[node] = ActedMonoid::op_comp(f, _lazy[node]);\n   \
    \         }\n            return;\n        }\n\n        assert(right - left > 1);\n\
    \        push(node, left, right);\n        int middle = left + (right - left)\
    \ / 2;\n        all_apply(node * 2, left, middle, f);\n        all_apply(\n  \
    \          node * 2 + 1,\n            middle,\n            right,\n          \
    \  shift_operator(f, middle - left)\n        );\n        update(node);\n    }\n\
    \n    void push(int node, int left, int right) {\n        assert(right - left\
    \ > 1);\n        int middle = left + (right - left) / 2;\n        F f = _lazy[node];\n\
    \        _lazy[node] = ActedMonoid::op_id();\n        all_apply(node * 2, left,\
    \ middle, f);\n        all_apply(\n            node * 2 + 1,\n            middle,\n\
    \            right,\n            shift_operator(f, middle - left)\n        );\n\
    \    }\n\n    void set_impl(\n        int node,\n        int left,\n        int\
    \ right,\n        int index,\n        T value\n    ) {\n        if (right - left\
    \ == 1) {\n            _data[node] = std::move(value);\n            return;\n\
    \        }\n        push(node, left, right);\n        int middle = left + (right\
    \ - left) / 2;\n        if (index < middle) {\n            set_impl(node * 2,\
    \ left, middle, index, std::move(value));\n        } else {\n            set_impl(\n\
    \                node * 2 + 1,\n                middle,\n                right,\n\
    \                index,\n                std::move(value)\n            );\n  \
    \      }\n        update(node);\n    }\n\n    T get_impl(int node, int left, int\
    \ right, int index) {\n        if (right - left == 1) return _data[node];\n  \
    \      push(node, left, right);\n        int middle = left + (right - left) /\
    \ 2;\n        if (index < middle) {\n            return get_impl(node * 2, left,\
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
    \ ds\n}  // namespace m1une\n\n\n#line 13 \"verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp\"\
    \n\nnamespace {\n\nusing AM =\n    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<long\
    \ long, 10>;\nusing SignedFullWidth =\n    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<long\
    \ long, 63>;\nusing UnsignedFullWidth =\n    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<\n\
    \        unsigned long long,\n        64\n    >;\n\nlong long apply_scalar(const\
    \ AM::operator_type& f, long long value) {\n    return (value & f.and_mask) |\
    \ f.or_mask;\n}\n\nvoid test_composition() {\n    std::vector<AM::operator_type>\
    \ operators;\n    for (long long mask = 0; mask < 32; ++mask) {\n        operators.emplace_back(AM::make_and(mask));\n\
    \        operators.emplace_back(AM::make_or(mask));\n    }\n\n    for (const auto&\
    \ f : operators) {\n        for (const auto& g : operators) {\n            auto\
    \ composition = AM::op_comp(f, g);\n            for (long long value = 0; value\
    \ < 32; ++value) {\n                assert(\n                    apply_scalar(composition,\
    \ value) ==\n                    apply_scalar(f, apply_scalar(g, value))\n   \
    \             );\n            }\n        }\n    }\n}\n\nvoid test_randomized()\
    \ {\n    constexpr int size = 73;\n    constexpr long long mask = (1LL << 10)\
    \ - 1;\n    std::uint64_t state = 0x3141592653589793ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    std::vector<long long> values(size);\n    for (long long&\
    \ value : values) {\n        value = static_cast<long long>(random() & mask);\n\
    \    }\n    m1une::ds::SegtreeBeats<AM> seg(values);\n\n    for (int step = 0;\
    \ step < 10000; ++step) {\n        int left = int(random() % (size + 1));\n  \
    \      int right = int(random() % (size + 1));\n        if (right < left) std::swap(left,\
    \ right);\n\n        if (random() % 3 != 0) {\n            long long operand =\
    \ static_cast<long long>(random() & mask);\n            if (random() & 1) {\n\
    \                seg.apply(left, right, AM::make_and(operand));\n            \
    \    for (int index = left; index < right; ++index) {\n                    values[index]\
    \ &= operand;\n                }\n            } else {\n                seg.apply(left,\
    \ right, AM::make_or(operand));\n                for (int index = left; index\
    \ < right; ++index) {\n                    values[index] |= operand;\n       \
    \         }\n            }\n        } else {\n            long long expected =\
    \ 0;\n            for (int index = left; index < right; ++index) {\n         \
    \       expected += values[index];\n            }\n            assert(seg.prod(left,\
    \ right).sum == expected);\n        }\n\n        int index = int(random() % size);\n\
    \        assert(seg.get(index).sum == values[index]);\n    }\n}\n\nstatic_assert(m1une::beats_acted_monoid::IsBeatsActedMonoid<AM>);\n\
    static_assert(AM::commutative);\nstatic_assert(!AM::operator_commutative);\nstatic_assert(\n\
    \    SignedFullWidth::bit_mask() ==\n    std::numeric_limits<long long>::max()\n\
    );\nstatic_assert(\n    UnsignedFullWidth::bit_mask() ==\n    std::numeric_limits<unsigned\
    \ long long>::max()\n);\n\n}  // namespace\n\nint main() {\n    test_composition();\n\
    \    test_randomized();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n\
    #include <vector>\n\n#include \"../../beats_acted_monoid/concept.hpp\"\n#include\
    \ \"../../beats_acted_monoid/range_bitwise_and_or_range_sum.hpp\"\n#include \"\
    ../../ds/segtree/segtree_beats.hpp\"\n\nnamespace {\n\nusing AM =\n    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<long\
    \ long, 10>;\nusing SignedFullWidth =\n    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<long\
    \ long, 63>;\nusing UnsignedFullWidth =\n    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<\n\
    \        unsigned long long,\n        64\n    >;\n\nlong long apply_scalar(const\
    \ AM::operator_type& f, long long value) {\n    return (value & f.and_mask) |\
    \ f.or_mask;\n}\n\nvoid test_composition() {\n    std::vector<AM::operator_type>\
    \ operators;\n    for (long long mask = 0; mask < 32; ++mask) {\n        operators.emplace_back(AM::make_and(mask));\n\
    \        operators.emplace_back(AM::make_or(mask));\n    }\n\n    for (const auto&\
    \ f : operators) {\n        for (const auto& g : operators) {\n            auto\
    \ composition = AM::op_comp(f, g);\n            for (long long value = 0; value\
    \ < 32; ++value) {\n                assert(\n                    apply_scalar(composition,\
    \ value) ==\n                    apply_scalar(f, apply_scalar(g, value))\n   \
    \             );\n            }\n        }\n    }\n}\n\nvoid test_randomized()\
    \ {\n    constexpr int size = 73;\n    constexpr long long mask = (1LL << 10)\
    \ - 1;\n    std::uint64_t state = 0x3141592653589793ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    std::vector<long long> values(size);\n    for (long long&\
    \ value : values) {\n        value = static_cast<long long>(random() & mask);\n\
    \    }\n    m1une::ds::SegtreeBeats<AM> seg(values);\n\n    for (int step = 0;\
    \ step < 10000; ++step) {\n        int left = int(random() % (size + 1));\n  \
    \      int right = int(random() % (size + 1));\n        if (right < left) std::swap(left,\
    \ right);\n\n        if (random() % 3 != 0) {\n            long long operand =\
    \ static_cast<long long>(random() & mask);\n            if (random() & 1) {\n\
    \                seg.apply(left, right, AM::make_and(operand));\n            \
    \    for (int index = left; index < right; ++index) {\n                    values[index]\
    \ &= operand;\n                }\n            } else {\n                seg.apply(left,\
    \ right, AM::make_or(operand));\n                for (int index = left; index\
    \ < right; ++index) {\n                    values[index] |= operand;\n       \
    \         }\n            }\n        } else {\n            long long expected =\
    \ 0;\n            for (int index = left; index < right; ++index) {\n         \
    \       expected += values[index];\n            }\n            assert(seg.prod(left,\
    \ right).sum == expected);\n        }\n\n        int index = int(random() % size);\n\
    \        assert(seg.get(index).sum == values[index]);\n    }\n}\n\nstatic_assert(m1une::beats_acted_monoid::IsBeatsActedMonoid<AM>);\n\
    static_assert(AM::commutative);\nstatic_assert(!AM::operator_commutative);\nstatic_assert(\n\
    \    SignedFullWidth::bit_mask() ==\n    std::numeric_limits<long long>::max()\n\
    );\nstatic_assert(\n    UnsignedFullWidth::bit_mask() ==\n    std::numeric_limits<unsigned\
    \ long long>::max()\n);\n\n}  // namespace\n\nint main() {\n    test_composition();\n\
    \    test_randomized();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  dependsOn:
  - beats_acted_monoid/concept.hpp
  - acted_monoid/concept.hpp
  - beats_acted_monoid/range_bitwise_and_or_range_sum.hpp
  - ds/segtree/segtree_beats.hpp
  - beats_acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  isVerificationFile: true
  path: verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 01:20:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
- /verify/verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp.html
title: verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
---
