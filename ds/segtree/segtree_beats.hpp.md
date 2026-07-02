---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/beats_concept.hpp
    title: Beats Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/segtree_beats.test.cpp
    title: verify/ds/segtree/segtree_beats.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
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
    \ ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_BEATS_HPP\n#define M1UNE_DS_SEGTREE_BEATS_HPP 1\n\
    \n#include <cassert>\n#include <concepts>\n#include <utility>\n#include <vector>\n\
    \n#include \"../../acted_monoid/beats_concept.hpp\"\n#include \"../../math/bit_ceil.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Generic Segment Tree Beats for actions\
    \ that may require recursive descent.\ntemplate <m1une::acted_monoid::IsBeatsActedMonoid\
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
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_SEGTREE_BEATS_HPP\n"
  dependsOn:
  - acted_monoid/beats_concept.hpp
  - acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  isVerificationFile: false
  path: ds/segtree/segtree_beats.hpp
  requiredBy: []
  timestamp: '2026-07-02 21:23:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/segtree_beats.test.cpp
documentation_of: ds/segtree/segtree_beats.hpp
layout: document
title: Generic Segment Tree Beats!
---

## Overview

`m1une::ds::SegtreeBeats<ActedMonoid>` is a generic lazy segment tree for
actions that cannot always be applied to an aggregated node. When
`can_apply(f, x)` is false, the tree pushes any older lazy operator, descends to
the children, applies `f` there, and rebuilds the node.

This is the library's generic meaning of Segment Tree Beats. It is not tied to
`chmin` or `chmax`. For the ready-made numeric structure supporting range
`chmin`, range `chmax`, range addition, and sum/min/max queries, use
`ChminChmaxAddSegtree<T>`.

Use `LazySegtree<ActedMonoid>` when every valid action always maps an aggregate
directly. Its simpler contract gives the usual $O(\log N)$ update bound.

## Beats acted monoid

`ActedMonoid` must satisfy `m1une::acted_monoid::IsBeatsActedMonoid` and provide:

```cpp
using value_type = T;
using operator_type = F;

static T id();
static T op(const T& lhs, const T& rhs);

static F op_id();
static F op_comp(const F& f, const F& g);

static T mapping(const F& f, const T& x);
static bool can_apply(const F& f, const T& x);
```

`op_comp(f, g)` represents applying `g` first and then `f`.

The exact applicability contract is:

* If `can_apply(f, x)` is true, `mapping(f, x)` must return the correct updated
  aggregate without inspecting children.
* If it is false, `mapping` is not called and `f` is not composed into that
  node's lazy tag.
* A failed internal application pushes the node's existing lazy tag first,
  recursively applies `f` to both children, and rebuilds the aggregate with
  `op`.
* Pushing a stored operator uses the same fallible procedure. It may itself
  descend multiple levels before propagation finishes.
* Every valid operator must be applicable at every real leaf. Reaching a real
  leaf for which `can_apply` is false triggers an assertion.
* `op_id()` must always be applicable and `mapping(op_id(), x)` must equal `x`.

Padded leaves are excluded by the data structure and do not impose an
application-specific `can_apply` requirement.

## Optional index-aware operations

The following overloads are detected automatically:

```cpp
static T mapping(const F& f, const T& x, long long ordinal);
static bool can_apply(const F& f, const T& x, long long ordinal);
static F op_shift(const F& f, long long offset);
```

An operator passed to `apply(l, r, f)` is relative to index `l`. A covered node
starting at `p` receives `op_shift(f, p - l)`. On descent, the left child keeps
offset zero relative to its parent and the right child receives the operator
shifted by the left child's interval length. The index-aware mapping and
applicability overloads receive the ordinal relative to the already shifted
operator; the current implementation calls them with zero at a node.

Construction from `std::vector<U>` uses `ActedMonoid::make(value)` when
available, then `ActedMonoid::make(value, index)`, then conversion to
`value_type`.

`acted_monoid/beats_wrapper.hpp` provides `BeatsWrapper` for assembling the
required functions from `constexpr` lambdas or function objects. It can also
forward optional `make`, index-aware mapping/applicability, and shifting
functions.

## Public interface

All indices are zero-based and all ranges are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `SegtreeBeats()` | Constructs an empty tree. | $O(1)$ |
| `SegtreeBeats(int n)` | Constructs `n` identity values. | $O(N)$ |
| `SegtreeBeats(const std::vector<T>& v)` | Copies and builds from acted-monoid values. | $O(N)$ |
| `SegtreeBeats(std::vector<T>&& v)` | Moves and builds from acted-monoid values. | $O(N)$ |
| `SegtreeBeats(const std::vector<U>& v)` | Converts with `make` or conversion and builds. | $O(N)$ |
| `int size() const` | Returns the number of real elements. | $O(1)$ |
| `bool empty() const` | Returns whether there are no elements. | $O(1)$ |
| `void set(int p, T x)` | Assigns element `p`. | $O(\log N + D)$ |
| `T get(int p)` | Returns element `p`. | $O(\log N + D)$ |
| `T operator[](int p)` | Returns element `p`. | $O(\log N + D)$ |
| `T prod(int l, int r)` | Returns the monoid product of `[l, r)`. | $O(\log N + D)$ |
| `T all_prod() const` | Returns the whole-array product. | $O(1)$ |
| `void apply(int p, F f)` | Applies `f` to element `p`. | $O(\log N + D)$ |
| `void apply(int l, int r, F f)` | Applies `f` to `[l, r)`. | $O(\log N + D)$ |
| `std::vector<T> to_vector()` | Materializes every element. | $O(N + D)$ |
| `std::vector<T> to_vector(int l, int r)` | Materializes `[l, r)`. | $O((r-l)+\log N+D)$ |
| `int max_right(int l, Predicate g)` | Finds the largest `r` for which `g(prod(l, r))` is true. | $O(\log N + D)$ |
| `int min_left(int r, Predicate g)` | Finds the smallest `l` for which `g(prod(l, r))` is true. | $O(\log N + D)$ |

Here, $D$ is the number of additional nodes visited because direct application
of a new or stored operator fails. Empty products return `id()`. Boundary-search
predicates must accept `id()`.

A generic update is therefore $O(\log N + D)$, not automatically amortized
$O(\log N)$. A stronger bound must be proved for the particular acted monoid,
usually with a potential argument or a bound on exceptional state transitions.
Because queries may push stored operators, their $D$ can also be nonzero.

## Non-chmin/chmax example

Consider reactors with a pressure threshold. A value stores the minimum
remaining pressure before any active reactor vents, the total number of vents,
and the number and length of terminal reactors. An update stores both the added
pressure and one operation count.

The update is directly applicable when all reactors are terminal, no active
reactor reaches its threshold, or the node is a leaf. Otherwise
`can_apply(update, node)` returns false. The generic tree descends only through
segments containing exceptional transitions; a leaf that vents can halve its
threshold and reset its pressure. This is a Beats action even though it uses no
`chmin` or `chmax` operation.
