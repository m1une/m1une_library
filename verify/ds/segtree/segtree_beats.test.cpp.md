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
    path: acted_monoid/range_affine_range_sum.hpp
    title: Range Affine Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree_beats.hpp
    title: Generic Segment Tree Beats!
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/segtree_beats.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n\n#line 1 \"ds/segtree/segtree_beats.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"acted_monoid/beats_concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/beats_concept.hpp\"\
    \n\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
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
    \n\n#line 7 \"acted_monoid/beats_concept.hpp\"\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\n// An acted monoid whose action may require descent before\
    \ it can be applied.\ntemplate <typename AM>\nconcept IsBeatsActedMonoid = IsActedMonoid<AM>\
    \ &&\n    requires(typename AM::value_type x, typename AM::operator_type f) {\n\
    \        { AM::can_apply(f, x) } -> std::same_as<bool>;\n    };\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\
    \nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nconstexpr T bit_ceil(T\
    \ n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n\
    \    return x;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 11\
    \ \"ds/segtree/segtree_beats.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n//\
    \ Generic Segment Tree Beats for actions that may require recursive descent.\n\
    template <m1une::acted_monoid::IsBeatsActedMonoid ActedMonoid>\nstruct SegtreeBeats\
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
    \ ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/segtree/segtree_beats.test.cpp\"\
    \n\n#line 6 \"verify/ds/segtree/segtree_beats.test.cpp\"\n#include <iostream>\n\
    #line 9 \"verify/ds/segtree/segtree_beats.test.cpp\"\n\n#line 1 \"acted_monoid/range_affine_range_sum.hpp\"\
    \n\n\n\n#line 5 \"acted_monoid/range_affine_range_sum.hpp\"\n\nnamespace m1une\
    \ {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAffineRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\n// Designed to accept Modint or similar\
    \ types as T\ntemplate <typename T>\nstruct RangeAffineRangeSum {\n    using value_type\
    \ = RangeAffineRangeSumNode<T>;\n    using operator_type = std::pair<T, T>;  //\
    \ {a, b} for ax + b\n\n    // Value Monoid\n    static constexpr value_type id()\
    \ {\n        return {T(0), 0};\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return {a.sum + b.sum, a.size\
    \ + b.size};\n    }\n\n    // Operator Monoid (Affine Composition)\n    // f(x)\
    \ = a1*x + b1, g(x) = a2*x + b2\n    // f(g(x)) = a1*(a2*x + b2) + b1 = (a1*a2)*x\
    \ + (a1*b2 + b1)\n    static constexpr operator_type op_id() {\n        return\
    \ {T(1), T(0)};\n    }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return {f.first * g.first, f.first * g.second\
    \ + f.second};\n    }\n\n    // Mapping\n    // \\sum (a*x_i + b) = a * \\sum\
    \ x_i + b * size\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        return {f.first * x.sum + f.second * T(x.size),\
    \ x.size};\n    }\n\n    // Helper for initializing a leaf node\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1};\n    }\n};\n\n}  //\
    \ namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#include <cstdint>\n#line 6 \"math/modint.hpp\"\n#include <type_traits>\n\
    #line 8 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"Modulus\
    \ must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n    static\
    \ constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr\
    \ ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n  \
    \      return x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template\
    \ <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n  \
    \  constexpr ModInt(Integer v) noexcept {\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n\
    \            if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 12 \"verify/ds/segtree/segtree_beats.test.cpp\"\n\nusing mint\
    \ = m1une::math::modint998244353;\n\nstruct RangeAffineRangeSumBeats\n    : m1une::acted_monoid::RangeAffineRangeSum<mint>\
    \ {\n    static bool can_apply(\n        const operator_type&,\n        const\
    \ value_type&\n    ) {\n        return true;\n    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> values(n);\n    for (long long& value : values) std::cin >> value;\n\n\
    \    m1une::ds::SegtreeBeats<RangeAffineRangeSumBeats> seg(values);\n    assert(seg.size()\
    \ == n);\n    assert(seg.empty() == (n == 0));\n\n    while (q--) {\n        int\
    \ type, left, right;\n        std::cin >> type >> left >> right;\n        if (type\
    \ == 0) {\n            long long b, c;\n            std::cin >> b >> c;\n    \
    \        seg.apply(left, right, std::pair<mint, mint>(b, c));\n        } else\
    \ {\n            std::cout << seg.prod(left, right).sum << '\\n';\n        }\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#include \"../../../ds/segtree/segtree_beats.hpp\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <utility>\n#include <vector>\n\n#include \"../../../acted_monoid/range_affine_range_sum.hpp\"\
    \n#include \"../../../math/modint.hpp\"\n\nusing mint = m1une::math::modint998244353;\n\
    \nstruct RangeAffineRangeSumBeats\n    : m1une::acted_monoid::RangeAffineRangeSum<mint>\
    \ {\n    static bool can_apply(\n        const operator_type&,\n        const\
    \ value_type&\n    ) {\n        return true;\n    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> values(n);\n    for (long long& value : values) std::cin >> value;\n\n\
    \    m1une::ds::SegtreeBeats<RangeAffineRangeSumBeats> seg(values);\n    assert(seg.size()\
    \ == n);\n    assert(seg.empty() == (n == 0));\n\n    while (q--) {\n        int\
    \ type, left, right;\n        std::cin >> type >> left >> right;\n        if (type\
    \ == 0) {\n            long long b, c;\n            std::cin >> b >> c;\n    \
    \        seg.apply(left, right, std::pair<mint, mint>(b, c));\n        } else\
    \ {\n            std::cout << seg.prod(left, right).sum << '\\n';\n        }\n\
    \    }\n}\n"
  dependsOn:
  - ds/segtree/segtree_beats.hpp
  - acted_monoid/beats_concept.hpp
  - acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  - acted_monoid/range_affine_range_sum.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/ds/segtree/segtree_beats.test.cpp
  requiredBy: []
  timestamp: '2026-07-02 21:23:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/segtree_beats.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/segtree_beats.test.cpp
- /verify/verify/ds/segtree/segtree_beats.test.cpp.html
title: verify/ds/segtree/segtree_beats.test.cpp
---
