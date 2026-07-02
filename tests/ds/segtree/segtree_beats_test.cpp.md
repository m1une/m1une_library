---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/beats_concept.hpp
    title: Beats Acted Monoid Concept
  - icon: ':warning:'
    path: acted_monoid/beats_wrapper.hpp
    title: Beats Acted Monoid Wrapper
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
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
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/segtree_beats.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <utility>\n#include <vector>\n\n#line 1 \"acted_monoid/beats_concept.hpp\"\
    \n\n\n\n#line 5 \"acted_monoid/beats_concept.hpp\"\n\n#line 1 \"acted_monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace acted_monoid\
    \ {\n\n// Concept defining the requirements for an Acted Monoid.\ntemplate <typename\
    \ AM>\nconcept IsActedMonoid = requires(typename AM::value_type a, typename AM::value_type\
    \ b, typename AM::operator_type f,\n                                 typename\
    \ AM::operator_type g) {\n    // 1. Value Monoid\n    typename AM::value_type;\n\
    \    { AM::id() } -> std::same_as<typename AM::value_type>;\n    { AM::op(a, b)\
    \ } -> std::same_as<typename AM::value_type>;\n\n    // 2. Operator Monoid\n \
    \   typename AM::operator_type;\n    { AM::op_id() } -> std::same_as<typename\
    \ AM::operator_type>;\n    { AM::op_comp(f, g) } -> std::same_as<typename AM::operator_type>;\
    \  // Composition order: f(g(x))\n\n    // 3. Mapping: Operator x Value -> Value\n\
    \    { AM::mapping(f, a) } -> std::same_as<typename AM::value_type>;\n};\n\n//\
    \ Concept for acted monoids whose value monoid is a commutative group.\n// The\
    \ value operation must obey commutativity and inverse laws.\ntemplate <typename\
    \ AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM> && requires(typename\
    \ AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename AM::value_type>;\n\
    };\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 7 \"acted_monoid/beats_concept.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// An acted monoid whose action\
    \ may require descent before it can be applied.\ntemplate <typename AM>\nconcept\
    \ IsBeatsActedMonoid = IsActedMonoid<AM> &&\n    requires(typename AM::value_type\
    \ x, typename AM::operator_type f) {\n        { AM::can_apply(f, x) } -> std::same_as<bool>;\n\
    \    };\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"\
    math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\ntemplate <typename\
    \ T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n \
    \   while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 11 \"ds/segtree/segtree_beats.hpp\"\n\nnamespace m1une {\n\
    namespace ds {\n\n// Generic Segment Tree Beats for actions that may require recursive\
    \ descent.\ntemplate <m1une::acted_monoid::IsBeatsActedMonoid ActedMonoid>\nstruct\
    \ SegtreeBeats {\n    using value_type = typename ActedMonoid::value_type;\n \
    \   using operator_type = typename ActedMonoid::operator_type;\n    using T =\
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
    \ ds\n}  // namespace m1une\n\n\n#line 2 \"tests/ds/segtree/segtree_beats_test.cpp\"\
    \n\n#include <algorithm>\n#line 5 \"tests/ds/segtree/segtree_beats_test.cpp\"\n\
    #include <cstdint>\n#include <limits>\n#include <numeric>\n#line 10 \"tests/ds/segtree/segtree_beats_test.cpp\"\
    \n\n#line 1 \"acted_monoid/beats_wrapper.hpp\"\n\n\n\n#line 5 \"acted_monoid/beats_wrapper.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Wrapper for defining a Beats\
    \ acted monoid with functions or constexpr lambdas.\ntemplate <\n    typename\
    \ T,\n    typename E,\n    auto Op,\n    auto Id,\n    auto OpComp,\n    auto\
    \ OpId,\n    auto Mapping,\n    auto CanApply,\n    auto Make = nullptr,\n   \
    \ auto MakeAt = nullptr,\n    auto MappingAt = nullptr,\n    auto CanApplyAt =\
    \ nullptr,\n    auto OpShift = nullptr\n>\nstruct BeatsWrapper {\n    using value_type\
    \ = T;\n    using operator_type = E;\n\n    static constexpr T id() {\n      \
    \  return Id();\n    }\n\n    static constexpr T op(const T& lhs, const T& rhs)\
    \ {\n        return Op(lhs, rhs);\n    }\n\n    static constexpr E op_id() {\n\
    \        return OpId();\n    }\n\n    static constexpr E op_comp(const E& f, const\
    \ E& g) {\n        return OpComp(f, g);\n    }\n\n    static constexpr T mapping(const\
    \ E& f, const T& x) {\n        return Mapping(f, x);\n    }\n\n    static constexpr\
    \ bool can_apply(const E& f, const T& x) {\n        return CanApply(f, x);\n \
    \   }\n\n    template <typename U>\n    requires requires(const U& value) {\n\
    \        { Make(value) } -> std::convertible_to<T>;\n    }\n    static constexpr\
    \ T make(const U& value) {\n        return Make(value);\n    }\n\n    template\
    \ <typename U>\n    requires requires(const U& value, int index) {\n        {\
    \ MakeAt(value, index) } -> std::convertible_to<T>;\n    }\n    static constexpr\
    \ T make(const U& value, int index) {\n        return MakeAt(value, index);\n\
    \    }\n\n    static constexpr T mapping(const E& f, const T& x, long long ordinal)\n\
    \    requires requires {\n        { MappingAt(f, x, ordinal) } -> std::convertible_to<T>;\n\
    \    }\n    {\n        return MappingAt(f, x, ordinal);\n    }\n\n    static constexpr\
    \ bool can_apply(\n        const E& f,\n        const T& x,\n        long long\
    \ ordinal\n    )\n    requires requires {\n        { CanApplyAt(f, x, ordinal)\
    \ } -> std::convertible_to<bool>;\n    }\n    {\n        return CanApplyAt(f,\
    \ x, ordinal);\n    }\n\n    static constexpr E op_shift(const E& f, long long\
    \ ordinal)\n    requires requires {\n        { OpShift(f, ordinal) } -> std::convertible_to<E>;\n\
    \    }\n    {\n        return OpShift(f, ordinal);\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n\n#line 12 \"tests/ds/segtree/segtree_beats_test.cpp\"\
    \n\nnamespace {\n\nstruct SumNode {\n    long long sum;\n    int length;\n\n \
    \   friend bool operator==(const SumNode&, const SumNode&) = default;\n};\n\n\
    struct ConservativeRangeAdd {\n    using value_type = SumNode;\n    using operator_type\
    \ = long long;\n\n    static value_type id() {\n        return SumNode{0, 0};\n\
    \    }\n\n    static value_type op(const value_type& lhs, const value_type& rhs)\
    \ {\n        return SumNode{lhs.sum + rhs.sum, lhs.length + rhs.length};\n   \
    \ }\n\n    static operator_type op_id() {\n        return 0;\n    }\n\n    static\
    \ operator_type op_comp(operator_type f, operator_type g) {\n        return f\
    \ + g;\n    }\n\n    static value_type mapping(operator_type f, const value_type&\
    \ x) {\n        return SumNode{x.sum + f * x.length, x.length};\n    }\n\n   \
    \ static bool can_apply(operator_type f, const value_type& x) {\n        return\
    \ f == 0 || x.length == 0 || x.length == 1 ||\n            (4 <= x.length && -1\
    \ <= f && f <= 1);\n    }\n\n    static value_type make(long long value) {\n \
    \       return SumNode{value, 1};\n    }\n};\n\nstruct IndexedRangeAdd {\n   \
    \ using value_type = SumNode;\n\n    struct operator_type {\n        long long\
    \ slope;\n        long long constant;\n    };\n\n    static value_type id() {\n\
    \        return SumNode{0, 0};\n    }\n\n    static value_type op(const value_type&\
    \ lhs, const value_type& rhs) {\n        return SumNode{lhs.sum + rhs.sum, lhs.length\
    \ + rhs.length};\n    }\n\n    static operator_type op_id() {\n        return\
    \ operator_type{0, 0};\n    }\n\n    static operator_type op_comp(\n        const\
    \ operator_type& f,\n        const operator_type& g\n    ) {\n        return operator_type{f.slope\
    \ + g.slope, f.constant + g.constant};\n    }\n\n    static value_type mapping(const\
    \ operator_type&, const value_type& x) {\n        return x;\n    }\n\n    static\
    \ value_type mapping(\n        const operator_type& f,\n        const value_type&\
    \ x,\n        long long ordinal\n    ) {\n        long long local_sum = 1LL *\
    \ x.length * (x.length - 1) / 2;\n        return SumNode{\n            x.sum +\
    \ f.slope * (local_sum + ordinal * x.length) +\n                f.constant * x.length,\n\
    \            x.length\n        };\n    }\n\n    static bool can_apply(const operator_type&,\
    \ const value_type&) {\n        return false;\n    }\n\n    static bool can_apply(\n\
    \        const operator_type&,\n        const value_type&,\n        long long\n\
    \    ) {\n        return true;\n    }\n\n    static operator_type op_shift(\n\
    \        const operator_type& f,\n        long long ordinal\n    ) {\n       \
    \ return operator_type{f.slope, f.constant + f.slope * ordinal};\n    }\n\n  \
    \  static value_type make(long long value, int index) {\n        return SumNode{value\
    \ + index, 1};\n    }\n};\n\nconstexpr auto wrapper_op = [](const SumNode& lhs,\
    \ const SumNode& rhs) {\n    return SumNode{lhs.sum + rhs.sum, lhs.length + rhs.length};\n\
    };\nconstexpr auto wrapper_id = [] { return SumNode{0, 0}; };\nconstexpr auto\
    \ wrapper_comp = [](long long f, long long g) { return f + g; };\nconstexpr auto\
    \ wrapper_op_id = [] { return 0LL; };\nconstexpr auto wrapper_mapping = [](long\
    \ long f, const SumNode& x) {\n    return SumNode{x.sum + f * x.length, x.length};\n\
    };\nconstexpr auto wrapper_can_apply = [](long long, const SumNode&) {\n    return\
    \ true;\n};\nconstexpr auto wrapper_make = [](long long value) {\n    return SumNode{value,\
    \ 1};\n};\n\nusing WrappedRangeAdd = m1une::acted_monoid::BeatsWrapper<\n    SumNode,\n\
    \    long long,\n    wrapper_op,\n    wrapper_id,\n    wrapper_comp,\n    wrapper_op_id,\n\
    \    wrapper_mapping,\n    wrapper_can_apply,\n    wrapper_make\n>;\n\nstruct\
    \ ReactorNode {\n    long long min_remaining;\n    long long vent_count;\n   \
    \ int terminal_count;\n    int length;\n    long long current_limit;\n};\n\nstruct\
    \ ReactorOperator {\n    long long pressure_add;\n    long long operation_count;\n\
    };\n\nstruct ReactorActedMonoid {\n    using value_type = ReactorNode;\n    using\
    \ operator_type = ReactorOperator;\n\n    static constexpr long long infinity\
    \ =\n        std::numeric_limits<long long>::max() / 4;\n\n    static value_type\
    \ id() {\n        return value_type{infinity, 0, 0, 0, 0};\n    }\n\n    static\
    \ value_type op(const value_type& lhs, const value_type& rhs) {\n        return\
    \ value_type{\n            std::min(lhs.min_remaining, rhs.min_remaining),\n \
    \           lhs.vent_count + rhs.vent_count,\n            lhs.terminal_count +\
    \ rhs.terminal_count,\n            lhs.length + rhs.length,\n            0\n \
    \       };\n    }\n\n    static operator_type op_id() {\n        return operator_type{0,\
    \ 0};\n    }\n\n    static operator_type op_comp(\n        const operator_type&\
    \ f,\n        const operator_type& g\n    ) {\n        return operator_type{\n\
    \            f.pressure_add + g.pressure_add,\n            f.operation_count +\
    \ g.operation_count\n        };\n    }\n\n    static bool can_apply(const operator_type&\
    \ f, const value_type& x) {\n        return x.length == 0 || x.terminal_count\
    \ == x.length ||\n            f.pressure_add < x.min_remaining || x.length ==\
    \ 1;\n    }\n\n    static value_type mapping(const operator_type& f, value_type\
    \ x) {\n        assert(can_apply(f, x));\n        assert(0 <= f.pressure_add);\n\
    \        assert(0 <= f.operation_count);\n        if (x.length == 0) return x;\n\
    \        if (x.terminal_count == x.length) {\n            x.vent_count += 1LL\
    \ * x.terminal_count * f.operation_count;\n            return x;\n        }\n\
    \        if (f.pressure_add < x.min_remaining) {\n            x.min_remaining\
    \ -= f.pressure_add;\n            x.vent_count += 1LL * x.terminal_count * f.operation_count;\n\
    \            return x;\n        }\n\n        assert(x.length == 1);\n        assert(x.terminal_count\
    \ == 0);\n        assert(1 < x.current_limit);\n        assert(0 < f.operation_count);\n\
    \        ++x.vent_count;\n        x.current_limit = std::max(x.current_limit /\
    \ 2, 1LL);\n        if (x.current_limit == 1) {\n            x.terminal_count\
    \ = 1;\n            x.min_remaining = infinity;\n        } else {\n          \
    \  x.min_remaining = x.current_limit;\n        }\n        return x;\n    }\n\n\
    \    static value_type make(long long limit) {\n        assert(1 <= limit);\n\
    \        if (limit == 1) return value_type{infinity, 0, 1, 1, 1};\n        return\
    \ value_type{limit, 0, 0, 1, limit};\n    }\n};\n\nvoid test_public_api_and_failure_paths()\
    \ {\n    m1une::ds::SegtreeBeats<ConservativeRangeAdd> empty;\n    assert(empty.size()\
    \ == 0);\n    assert(empty.empty());\n    assert(empty.prod(0, 0) == ConservativeRangeAdd::id());\n\
    \    assert(empty.all_prod() == ConservativeRangeAdd::id());\n    assert(empty.to_vector().empty());\n\
    \    assert(empty.max_right(0, [](const SumNode&) { return true; }) == 0);\n \
    \   assert(empty.min_left(0, [](const SumNode&) { return true; }) == 0);\n\n \
    \   m1une::ds::SegtreeBeats<ConservativeRangeAdd> zero(0);\n    assert(zero.empty());\n\
    \    m1une::ds::SegtreeBeats<ConservativeRangeAdd> identities(5);\n    assert(identities.size()\
    \ == 5);\n\n    std::vector<SumNode> nodes;\n    for (long long value = 1; value\
    \ <= 5; ++value) {\n        nodes.push_back(SumNode{value, 1});\n    }\n    std::vector<SumNode>\
    \ moved_nodes(nodes);\n    m1une::ds::SegtreeBeats<ConservativeRangeAdd> moved(\n\
    \        std::move(moved_nodes)\n    );\n    assert(moved.all_prod().sum == 15);\n\
    \n    std::vector<long long> four = {1, 2, 3, 4};\n    m1une::ds::SegtreeBeats<ConservativeRangeAdd>\
    \ root(four);\n    root.apply(0, 4, 1);\n    root.apply(0, 4, 2);\n    assert(root.all_prod().sum\
    \ == 22);\n    assert(root.get(0).sum == 4);\n\n    m1une::ds::SegtreeBeats<ConservativeRangeAdd>\
    \ seg(nodes);\n    seg.apply(0, 4, 1);\n    seg.apply(0, 4, 2);\n    seg.apply(1,\
    \ 5, -3);\n    seg.apply(2, 10);\n    seg.set(4, SumNode{20, 1});\n\n    std::vector<long\
    \ long> expected = {4, 2, 13, 4, 20};\n    auto materialized = seg.to_vector();\n\
    \    for (int i = 0; i < 5; ++i) {\n        assert(materialized[i].sum == expected[i]);\n\
    \        assert(seg.get(i).sum == expected[i]);\n        assert(seg[i].sum ==\
    \ expected[i]);\n    }\n    assert(seg.prod(1, 4).sum == 19);\n    assert(seg.prod(2,\
    \ 2) == ConservativeRangeAdd::id());\n    assert(seg.all_prod().sum == 43);\n\
    \    auto middle = seg.to_vector(1, 4);\n    assert(middle.size() == 3);\n   \
    \ assert(middle[0].sum == 2 && middle[2].sum == 4);\n    assert(seg.max_right(0,\
    \ [](const SumNode& x) { return x.sum <= 19; }) == 3);\n    assert(seg.min_left(5,\
    \ [](const SumNode& x) { return x.sum <= 24; }) == 3);\n\n    std::vector<long\
    \ long> raw = {1, 2, 3};\n    m1une::ds::SegtreeBeats<WrappedRangeAdd> wrapped(raw);\n\
    \    wrapped.apply(0, 3, 4);\n    assert(wrapped.all_prod().sum == 18);\n}\n\n\
    void test_index_aware_operations() {\n    std::vector<long long> raw = {10, 10,\
    \ 10, 10, 10};\n    m1une::ds::SegtreeBeats<IndexedRangeAdd> seg(raw);\n    std::vector<long\
    \ long> expected = {10, 11, 12, 13, 14};\n\n    seg.apply(1, 5, IndexedRangeAdd::operator_type{2,\
    \ 3});\n    for (int i = 1; i < 5; ++i) expected[i] += 2 * (i - 1) + 3;\n    seg.apply(2,\
    \ IndexedRangeAdd::operator_type{5, -1});\n    expected[2] += -1;\n\n    auto\
    \ values = seg.to_vector();\n    for (int i = 0; i < 5; ++i) assert(values[i].sum\
    \ == expected[i]);\n    assert(\n        seg.all_prod().sum ==\n        std::accumulate(expected.begin(),\
    \ expected.end(), 0LL)\n    );\n}\n\nstruct NaiveReactor {\n    long long limit;\n\
    \    long long pressure;\n    long long vents;\n};\n\nvoid apply_naive(NaiveReactor&\
    \ reactor, long long pressure_add) {\n    if (reactor.limit == 1) {\n        ++reactor.vents;\n\
    \        return;\n    }\n    reactor.pressure += pressure_add;\n    if (reactor.limit\
    \ <= reactor.pressure) {\n        ++reactor.vents;\n        reactor.limit = std::max(reactor.limit\
    \ / 2, 1LL);\n        reactor.pressure = 0;\n    }\n}\n\nvoid check_reactors(\n\
    \    m1une::ds::SegtreeBeats<ReactorActedMonoid>& seg,\n    const std::vector<NaiveReactor>&\
    \ naive\n) {\n    auto values = seg.to_vector();\n    long long total = 0;\n \
    \   for (int i = 0; i < int(naive.size()); ++i) {\n        total += naive[i].vents;\n\
    \        assert(values[i].vent_count == naive[i].vents);\n        assert(values[i].current_limit\
    \ == naive[i].limit);\n        assert(values[i].terminal_count == (naive[i].limit\
    \ == 1));\n        if (naive[i].limit == 1) {\n            assert(values[i].min_remaining\
    \ == ReactorActedMonoid::infinity);\n        } else {\n            assert(\n \
    \               values[i].min_remaining ==\n                naive[i].limit - naive[i].pressure\n\
    \            );\n        }\n    }\n    assert(seg.all_prod().vent_count == total);\n\
    }\n\nvoid test_reactor_randomized() {\n    std::uint64_t state = 0x106084123456789ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 300; ++trial) {\n        int n = 1 + int(random() % 12);\n        std::vector<long\
    \ long> limits(n);\n        std::vector<NaiveReactor> naive(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            limits[i] = 1 + static_cast<long long>(random()\
    \ % 24);\n            naive[i] = NaiveReactor{limits[i], 0, 0};\n        }\n \
    \       m1une::ds::SegtreeBeats<ReactorActedMonoid> seg(limits);\n\n        for\
    \ (int operation = 0; operation < 500; ++operation) {\n            int left =\
    \ int(random() % (n + 1));\n            int right = int(random() % (n + 1));\n\
    \            if (right < left) std::swap(left, right);\n            if (random()\
    \ % 4 != 0) {\n                long long pressure_add =\n                    static_cast<long\
    \ long>(random() % 20);\n                seg.apply(\n                    left,\n\
    \                    right,\n                    ReactorOperator{pressure_add,\
    \ 1}\n                );\n                for (int i = left; i < right; ++i) {\n\
    \                    apply_naive(naive[i], pressure_add);\n                }\n\
    \            } else {\n                long long expected = 0;\n             \
    \   for (int i = left; i < right; ++i) {\n                    expected += naive[i].vents;\n\
    \                }\n                assert(seg.prod(left, right).vent_count ==\
    \ expected);\n            }\n            if (operation % 17 == 0) check_reactors(seg,\
    \ naive);\n        }\n        check_reactors(seg, naive);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_public_api_and_failure_paths();\n    test_index_aware_operations();\n\
    \    test_reactor_randomized();\n}\n"
  code: "#include \"ds/segtree/segtree_beats.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <limits>\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"acted_monoid/beats_wrapper.hpp\"\n\
    \nnamespace {\n\nstruct SumNode {\n    long long sum;\n    int length;\n\n   \
    \ friend bool operator==(const SumNode&, const SumNode&) = default;\n};\n\nstruct\
    \ ConservativeRangeAdd {\n    using value_type = SumNode;\n    using operator_type\
    \ = long long;\n\n    static value_type id() {\n        return SumNode{0, 0};\n\
    \    }\n\n    static value_type op(const value_type& lhs, const value_type& rhs)\
    \ {\n        return SumNode{lhs.sum + rhs.sum, lhs.length + rhs.length};\n   \
    \ }\n\n    static operator_type op_id() {\n        return 0;\n    }\n\n    static\
    \ operator_type op_comp(operator_type f, operator_type g) {\n        return f\
    \ + g;\n    }\n\n    static value_type mapping(operator_type f, const value_type&\
    \ x) {\n        return SumNode{x.sum + f * x.length, x.length};\n    }\n\n   \
    \ static bool can_apply(operator_type f, const value_type& x) {\n        return\
    \ f == 0 || x.length == 0 || x.length == 1 ||\n            (4 <= x.length && -1\
    \ <= f && f <= 1);\n    }\n\n    static value_type make(long long value) {\n \
    \       return SumNode{value, 1};\n    }\n};\n\nstruct IndexedRangeAdd {\n   \
    \ using value_type = SumNode;\n\n    struct operator_type {\n        long long\
    \ slope;\n        long long constant;\n    };\n\n    static value_type id() {\n\
    \        return SumNode{0, 0};\n    }\n\n    static value_type op(const value_type&\
    \ lhs, const value_type& rhs) {\n        return SumNode{lhs.sum + rhs.sum, lhs.length\
    \ + rhs.length};\n    }\n\n    static operator_type op_id() {\n        return\
    \ operator_type{0, 0};\n    }\n\n    static operator_type op_comp(\n        const\
    \ operator_type& f,\n        const operator_type& g\n    ) {\n        return operator_type{f.slope\
    \ + g.slope, f.constant + g.constant};\n    }\n\n    static value_type mapping(const\
    \ operator_type&, const value_type& x) {\n        return x;\n    }\n\n    static\
    \ value_type mapping(\n        const operator_type& f,\n        const value_type&\
    \ x,\n        long long ordinal\n    ) {\n        long long local_sum = 1LL *\
    \ x.length * (x.length - 1) / 2;\n        return SumNode{\n            x.sum +\
    \ f.slope * (local_sum + ordinal * x.length) +\n                f.constant * x.length,\n\
    \            x.length\n        };\n    }\n\n    static bool can_apply(const operator_type&,\
    \ const value_type&) {\n        return false;\n    }\n\n    static bool can_apply(\n\
    \        const operator_type&,\n        const value_type&,\n        long long\n\
    \    ) {\n        return true;\n    }\n\n    static operator_type op_shift(\n\
    \        const operator_type& f,\n        long long ordinal\n    ) {\n       \
    \ return operator_type{f.slope, f.constant + f.slope * ordinal};\n    }\n\n  \
    \  static value_type make(long long value, int index) {\n        return SumNode{value\
    \ + index, 1};\n    }\n};\n\nconstexpr auto wrapper_op = [](const SumNode& lhs,\
    \ const SumNode& rhs) {\n    return SumNode{lhs.sum + rhs.sum, lhs.length + rhs.length};\n\
    };\nconstexpr auto wrapper_id = [] { return SumNode{0, 0}; };\nconstexpr auto\
    \ wrapper_comp = [](long long f, long long g) { return f + g; };\nconstexpr auto\
    \ wrapper_op_id = [] { return 0LL; };\nconstexpr auto wrapper_mapping = [](long\
    \ long f, const SumNode& x) {\n    return SumNode{x.sum + f * x.length, x.length};\n\
    };\nconstexpr auto wrapper_can_apply = [](long long, const SumNode&) {\n    return\
    \ true;\n};\nconstexpr auto wrapper_make = [](long long value) {\n    return SumNode{value,\
    \ 1};\n};\n\nusing WrappedRangeAdd = m1une::acted_monoid::BeatsWrapper<\n    SumNode,\n\
    \    long long,\n    wrapper_op,\n    wrapper_id,\n    wrapper_comp,\n    wrapper_op_id,\n\
    \    wrapper_mapping,\n    wrapper_can_apply,\n    wrapper_make\n>;\n\nstruct\
    \ ReactorNode {\n    long long min_remaining;\n    long long vent_count;\n   \
    \ int terminal_count;\n    int length;\n    long long current_limit;\n};\n\nstruct\
    \ ReactorOperator {\n    long long pressure_add;\n    long long operation_count;\n\
    };\n\nstruct ReactorActedMonoid {\n    using value_type = ReactorNode;\n    using\
    \ operator_type = ReactorOperator;\n\n    static constexpr long long infinity\
    \ =\n        std::numeric_limits<long long>::max() / 4;\n\n    static value_type\
    \ id() {\n        return value_type{infinity, 0, 0, 0, 0};\n    }\n\n    static\
    \ value_type op(const value_type& lhs, const value_type& rhs) {\n        return\
    \ value_type{\n            std::min(lhs.min_remaining, rhs.min_remaining),\n \
    \           lhs.vent_count + rhs.vent_count,\n            lhs.terminal_count +\
    \ rhs.terminal_count,\n            lhs.length + rhs.length,\n            0\n \
    \       };\n    }\n\n    static operator_type op_id() {\n        return operator_type{0,\
    \ 0};\n    }\n\n    static operator_type op_comp(\n        const operator_type&\
    \ f,\n        const operator_type& g\n    ) {\n        return operator_type{\n\
    \            f.pressure_add + g.pressure_add,\n            f.operation_count +\
    \ g.operation_count\n        };\n    }\n\n    static bool can_apply(const operator_type&\
    \ f, const value_type& x) {\n        return x.length == 0 || x.terminal_count\
    \ == x.length ||\n            f.pressure_add < x.min_remaining || x.length ==\
    \ 1;\n    }\n\n    static value_type mapping(const operator_type& f, value_type\
    \ x) {\n        assert(can_apply(f, x));\n        assert(0 <= f.pressure_add);\n\
    \        assert(0 <= f.operation_count);\n        if (x.length == 0) return x;\n\
    \        if (x.terminal_count == x.length) {\n            x.vent_count += 1LL\
    \ * x.terminal_count * f.operation_count;\n            return x;\n        }\n\
    \        if (f.pressure_add < x.min_remaining) {\n            x.min_remaining\
    \ -= f.pressure_add;\n            x.vent_count += 1LL * x.terminal_count * f.operation_count;\n\
    \            return x;\n        }\n\n        assert(x.length == 1);\n        assert(x.terminal_count\
    \ == 0);\n        assert(1 < x.current_limit);\n        assert(0 < f.operation_count);\n\
    \        ++x.vent_count;\n        x.current_limit = std::max(x.current_limit /\
    \ 2, 1LL);\n        if (x.current_limit == 1) {\n            x.terminal_count\
    \ = 1;\n            x.min_remaining = infinity;\n        } else {\n          \
    \  x.min_remaining = x.current_limit;\n        }\n        return x;\n    }\n\n\
    \    static value_type make(long long limit) {\n        assert(1 <= limit);\n\
    \        if (limit == 1) return value_type{infinity, 0, 1, 1, 1};\n        return\
    \ value_type{limit, 0, 0, 1, limit};\n    }\n};\n\nvoid test_public_api_and_failure_paths()\
    \ {\n    m1une::ds::SegtreeBeats<ConservativeRangeAdd> empty;\n    assert(empty.size()\
    \ == 0);\n    assert(empty.empty());\n    assert(empty.prod(0, 0) == ConservativeRangeAdd::id());\n\
    \    assert(empty.all_prod() == ConservativeRangeAdd::id());\n    assert(empty.to_vector().empty());\n\
    \    assert(empty.max_right(0, [](const SumNode&) { return true; }) == 0);\n \
    \   assert(empty.min_left(0, [](const SumNode&) { return true; }) == 0);\n\n \
    \   m1une::ds::SegtreeBeats<ConservativeRangeAdd> zero(0);\n    assert(zero.empty());\n\
    \    m1une::ds::SegtreeBeats<ConservativeRangeAdd> identities(5);\n    assert(identities.size()\
    \ == 5);\n\n    std::vector<SumNode> nodes;\n    for (long long value = 1; value\
    \ <= 5; ++value) {\n        nodes.push_back(SumNode{value, 1});\n    }\n    std::vector<SumNode>\
    \ moved_nodes(nodes);\n    m1une::ds::SegtreeBeats<ConservativeRangeAdd> moved(\n\
    \        std::move(moved_nodes)\n    );\n    assert(moved.all_prod().sum == 15);\n\
    \n    std::vector<long long> four = {1, 2, 3, 4};\n    m1une::ds::SegtreeBeats<ConservativeRangeAdd>\
    \ root(four);\n    root.apply(0, 4, 1);\n    root.apply(0, 4, 2);\n    assert(root.all_prod().sum\
    \ == 22);\n    assert(root.get(0).sum == 4);\n\n    m1une::ds::SegtreeBeats<ConservativeRangeAdd>\
    \ seg(nodes);\n    seg.apply(0, 4, 1);\n    seg.apply(0, 4, 2);\n    seg.apply(1,\
    \ 5, -3);\n    seg.apply(2, 10);\n    seg.set(4, SumNode{20, 1});\n\n    std::vector<long\
    \ long> expected = {4, 2, 13, 4, 20};\n    auto materialized = seg.to_vector();\n\
    \    for (int i = 0; i < 5; ++i) {\n        assert(materialized[i].sum == expected[i]);\n\
    \        assert(seg.get(i).sum == expected[i]);\n        assert(seg[i].sum ==\
    \ expected[i]);\n    }\n    assert(seg.prod(1, 4).sum == 19);\n    assert(seg.prod(2,\
    \ 2) == ConservativeRangeAdd::id());\n    assert(seg.all_prod().sum == 43);\n\
    \    auto middle = seg.to_vector(1, 4);\n    assert(middle.size() == 3);\n   \
    \ assert(middle[0].sum == 2 && middle[2].sum == 4);\n    assert(seg.max_right(0,\
    \ [](const SumNode& x) { return x.sum <= 19; }) == 3);\n    assert(seg.min_left(5,\
    \ [](const SumNode& x) { return x.sum <= 24; }) == 3);\n\n    std::vector<long\
    \ long> raw = {1, 2, 3};\n    m1une::ds::SegtreeBeats<WrappedRangeAdd> wrapped(raw);\n\
    \    wrapped.apply(0, 3, 4);\n    assert(wrapped.all_prod().sum == 18);\n}\n\n\
    void test_index_aware_operations() {\n    std::vector<long long> raw = {10, 10,\
    \ 10, 10, 10};\n    m1une::ds::SegtreeBeats<IndexedRangeAdd> seg(raw);\n    std::vector<long\
    \ long> expected = {10, 11, 12, 13, 14};\n\n    seg.apply(1, 5, IndexedRangeAdd::operator_type{2,\
    \ 3});\n    for (int i = 1; i < 5; ++i) expected[i] += 2 * (i - 1) + 3;\n    seg.apply(2,\
    \ IndexedRangeAdd::operator_type{5, -1});\n    expected[2] += -1;\n\n    auto\
    \ values = seg.to_vector();\n    for (int i = 0; i < 5; ++i) assert(values[i].sum\
    \ == expected[i]);\n    assert(\n        seg.all_prod().sum ==\n        std::accumulate(expected.begin(),\
    \ expected.end(), 0LL)\n    );\n}\n\nstruct NaiveReactor {\n    long long limit;\n\
    \    long long pressure;\n    long long vents;\n};\n\nvoid apply_naive(NaiveReactor&\
    \ reactor, long long pressure_add) {\n    if (reactor.limit == 1) {\n        ++reactor.vents;\n\
    \        return;\n    }\n    reactor.pressure += pressure_add;\n    if (reactor.limit\
    \ <= reactor.pressure) {\n        ++reactor.vents;\n        reactor.limit = std::max(reactor.limit\
    \ / 2, 1LL);\n        reactor.pressure = 0;\n    }\n}\n\nvoid check_reactors(\n\
    \    m1une::ds::SegtreeBeats<ReactorActedMonoid>& seg,\n    const std::vector<NaiveReactor>&\
    \ naive\n) {\n    auto values = seg.to_vector();\n    long long total = 0;\n \
    \   for (int i = 0; i < int(naive.size()); ++i) {\n        total += naive[i].vents;\n\
    \        assert(values[i].vent_count == naive[i].vents);\n        assert(values[i].current_limit\
    \ == naive[i].limit);\n        assert(values[i].terminal_count == (naive[i].limit\
    \ == 1));\n        if (naive[i].limit == 1) {\n            assert(values[i].min_remaining\
    \ == ReactorActedMonoid::infinity);\n        } else {\n            assert(\n \
    \               values[i].min_remaining ==\n                naive[i].limit - naive[i].pressure\n\
    \            );\n        }\n    }\n    assert(seg.all_prod().vent_count == total);\n\
    }\n\nvoid test_reactor_randomized() {\n    std::uint64_t state = 0x106084123456789ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 300; ++trial) {\n        int n = 1 + int(random() % 12);\n        std::vector<long\
    \ long> limits(n);\n        std::vector<NaiveReactor> naive(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            limits[i] = 1 + static_cast<long long>(random()\
    \ % 24);\n            naive[i] = NaiveReactor{limits[i], 0, 0};\n        }\n \
    \       m1une::ds::SegtreeBeats<ReactorActedMonoid> seg(limits);\n\n        for\
    \ (int operation = 0; operation < 500; ++operation) {\n            int left =\
    \ int(random() % (n + 1));\n            int right = int(random() % (n + 1));\n\
    \            if (right < left) std::swap(left, right);\n            if (random()\
    \ % 4 != 0) {\n                long long pressure_add =\n                    static_cast<long\
    \ long>(random() % 20);\n                seg.apply(\n                    left,\n\
    \                    right,\n                    ReactorOperator{pressure_add,\
    \ 1}\n                );\n                for (int i = left; i < right; ++i) {\n\
    \                    apply_naive(naive[i], pressure_add);\n                }\n\
    \            } else {\n                long long expected = 0;\n             \
    \   for (int i = left; i < right; ++i) {\n                    expected += naive[i].vents;\n\
    \                }\n                assert(seg.prod(left, right).vent_count ==\
    \ expected);\n            }\n            if (operation % 17 == 0) check_reactors(seg,\
    \ naive);\n        }\n        check_reactors(seg, naive);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_public_api_and_failure_paths();\n    test_index_aware_operations();\n\
    \    test_reactor_randomized();\n}\n"
  dependsOn:
  - ds/segtree/segtree_beats.hpp
  - acted_monoid/beats_concept.hpp
  - acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  - acted_monoid/beats_wrapper.hpp
  isVerificationFile: false
  path: tests/ds/segtree/segtree_beats_test.cpp
  requiredBy: []
  timestamp: '2026-07-02 21:23:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tests/ds/segtree/segtree_beats_test.cpp
layout: document
redirect_from:
- /library/tests/ds/segtree/segtree_beats_test.cpp
- /library/tests/ds/segtree/segtree_beats_test.cpp.html
title: tests/ds/segtree/segtree_beats_test.cpp
---
