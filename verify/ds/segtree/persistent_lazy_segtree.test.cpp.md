---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_add_range_sum.hpp
    title: Range Add Range Sum
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_affine_range_sum.hpp
    title: Range Affine Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_lazy_segtree.hpp
    title: Persistent Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
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
    PROBLEM: https://judge.yosupo.jp/problem/persistent_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/persistent_range_affine_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/persistent_lazy_segtree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/persistent_range_affine_range_sum\"\
    \n\n#line 1 \"ds/segtree/persistent_lazy_segtree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
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
    \n\n#line 11 \"ds/segtree/persistent_lazy_segtree.hpp\"\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid>\n\
    struct PersistentLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        F lazy;\n        int l, r;\n        bool has_lazy;\n\
    \n        Node() : val(ActedMonoid::id()), lazy(ActedMonoid::op_id()), l(0), r(0),\
    \ has_lazy(false) {}\n        explicit Node(T value)\n            : val(std::move(value)),\
    \ lazy(ActedMonoid::op_id()), l(0), r(0), has_lazy(false) {}\n        Node(T value,\
    \ int left, int right)\n            : val(std::move(value)), lazy(ActedMonoid::op_id()),\
    \ l(left), r(right), has_lazy(false) {}\n    };\n\n    int _n;\n    int _root;\n\
    \    std::shared_ptr<std::vector<Node>> _pool;\n\n    explicit PersistentLazySegtree(int\
    \ n, int root, std::shared_ptr<std::vector<Node>> pool)\n        : _n(n), _root(root),\
    \ _pool(std::move(pool)) {}\n\n    int new_node(const Node& node) const {\n  \
    \      _pool->push_back(node);\n        return int(_pool->size()) - 1;\n    }\n\
    \n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
    \        return int(_pool->size()) - 1;\n    }\n\n    int clone_node(int t) const\
    \ {\n        return new_node((*_pool)[t]);\n    }\n\n    template <typename U>\n\
    \    static T make_value(const U& value, int index) {\n        if constexpr (requires(U\
    \ x) { ActedMonoid::make(x); }) {\n            return ActedMonoid::make(value);\n\
    \        } else if constexpr (requires(U x, int i) { ActedMonoid::make(x, i);\
    \ }) {\n            return ActedMonoid::make(value, index);\n        } else {\n\
    \            return static_cast<T>(value);\n        }\n    }\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ord) {\n        if constexpr (requires(F g,\
    \ T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n            return\
    \ ActedMonoid::mapping(f, value, ord);\n        } else {\n            return ActedMonoid::mapping(f,\
    \ value);\n        }\n    }\n\n    static F shift_operator(const F& f, long long\
    \ ord) {\n        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g,\
    \ i); }) {\n            return ActedMonoid::op_shift(f, ord);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    F compose_for_child(const\
    \ F& inherited, const Node& node, long long ord) const {\n        F shifted =\
    \ shift_operator(inherited, ord);\n        if (!node.has_lazy) return shifted;\n\
    \        return ActedMonoid::op_comp(shifted, shift_operator(node.lazy, ord));\n\
    \    }\n\n    int build(int l, int r, const std::vector<T>& v) const {\n     \
    \   if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(v[l]));\n\
    \        int m = (l + r) >> 1;\n        int left = build(l, m, v);\n        int\
    \ right = build(m, r, v);\n        return new_node(Node(ActedMonoid::op((*_pool)[left].val,\
    \ (*_pool)[right].val), left, right));\n    }\n\n    int build(int l, int r, std::vector<T>&\
    \ v) const {\n        if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(std::move(v[l])));\n\
    \        int m = (l + r) >> 1;\n        int left = build(l, m, v);\n        int\
    \ right = build(m, r, v);\n        return new_node(Node(ActedMonoid::op((*_pool)[left].val,\
    \ (*_pool)[right].val), left, right));\n    }\n\n    template <typename U>\n \
    \   int build_from_values(int l, int r, const std::vector<U>& v) const {\n   \
    \     if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(make_value(v[l],\
    \ l)));\n        int m = (l + r) >> 1;\n        int left = build_from_values(l,\
    \ m, v);\n        int right = build_from_values(m, r, v);\n        return new_node(Node(ActedMonoid::op((*_pool)[left].val,\
    \ (*_pool)[right].val), left, right));\n    }\n\n    void all_apply_to_node(int\
    \ t, const F& f) const {\n        Node& node = (*_pool)[t];\n        node.val\
    \ = mapping_at(f, node.val, 0);\n        node.lazy = ActedMonoid::op_comp(f, node.lazy);\n\
    \        node.has_lazy = true;\n    }\n\n    int all_apply_clone(int t, const\
    \ F& f) const {\n        int res = clone_node(t);\n        all_apply_to_node(res,\
    \ f);\n        return res;\n    }\n\n    void push(int t, int l, int r) const\
    \ {\n        if (!(*_pool)[t].has_lazy) return;\n        F lazy = (*_pool)[t].lazy;\n\
    \        int left = (*_pool)[t].l;\n        int right = (*_pool)[t].r;\n     \
    \   int m = (l + r) >> 1;\n        left = all_apply_clone(left, lazy);\n     \
    \   right = all_apply_clone(right, shift_operator(lazy, m - l));\n        Node&\
    \ node = (*_pool)[t];\n        node.l = left;\n        node.r = right;\n     \
    \   node.lazy = ActedMonoid::op_id();\n        node.has_lazy = false;\n    }\n\
    \n    void update(int t) const {\n        Node& node = (*_pool)[t];\n        node.val\
    \ = ActedMonoid::op((*_pool)[node.l].val, (*_pool)[node.r].val);\n    }\n\n  \
    \  int set_node(int t, int l, int r, int p, T value) const {\n        t = clone_node(t);\n\
    \        if (r - l == 1) {\n            Node& node = (*_pool)[t];\n          \
    \  node.val = std::move(value);\n            node.lazy = ActedMonoid::op_id();\n\
    \            node.has_lazy = false;\n            return t;\n        }\n      \
    \  push(t, l, r);\n        int m = (l + r) >> 1;\n        if (p < m) {\n     \
    \       (*_pool)[t].l = set_node((*_pool)[t].l, l, m, p, std::move(value));\n\
    \        } else {\n            (*_pool)[t].r = set_node((*_pool)[t].r, m, r, p,\
    \ std::move(value));\n        }\n        update(t);\n        return t;\n    }\n\
    \n    int apply_node(int t, int l, int r, int ql, int qr, const F& f) const {\n\
    \        if (qr <= l || r <= ql) return t;\n        t = clone_node(t);\n     \
    \   if (ql <= l && r <= qr) {\n            all_apply_to_node(t, shift_operator(f,\
    \ l - ql));\n            return t;\n        }\n        push(t, l, r);\n      \
    \  int m = (l + r) >> 1;\n        (*_pool)[t].l = apply_node((*_pool)[t].l, l,\
    \ m, ql, qr, f);\n        (*_pool)[t].r = apply_node((*_pool)[t].r, m, r, ql,\
    \ qr, f);\n        update(t);\n        return t;\n    }\n\n    int copy_range_node(int\
    \ target, int source, int l, int r, int ql, int qr) const {\n        if (qr <=\
    \ l || r <= ql) return target;\n        if (ql <= l && r <= qr) return source;\n\
    \n        target = clone_node(target);\n        source = clone_node(source);\n\
    \        push(target, l, r);\n        push(source, l, r);\n\n        int m = (l\
    \ + r) >> 1;\n        int left = copy_range_node(\n            (*_pool)[target].l,\n\
    \            (*_pool)[source].l,\n            l,\n            m,\n           \
    \ ql,\n            qr\n        );\n        int right = copy_range_node(\n    \
    \        (*_pool)[target].r,\n            (*_pool)[source].r,\n            m,\n\
    \            r,\n            ql,\n            qr\n        );\n        (*_pool)[target].l\
    \ = left;\n        (*_pool)[target].r = right;\n        update(target);\n    \
    \    return target;\n    }\n\n    T prod_node(int t, int l, int r, int ql, int\
    \ qr, const F& inherited) const {\n        if (!t || qr <= l || r <= ql) return\
    \ ActedMonoid::id();\n        const Node& node = (*_pool)[t];\n        if (ql\
    \ <= l && r <= qr) return mapping_at(inherited, node.val, 0);\n        int m =\
    \ (l + r) >> 1;\n        return ActedMonoid::op(prod_node(node.l, l, m, ql, qr,\
    \ compose_for_child(inherited, node, 0)),\n                               prod_node(node.r,\
    \ m, r, ql, qr, compose_for_child(inherited, node, m - l)));\n    }\n\n    void\
    \ collect_node(int t, int l, int r, int ql, int qr, const F& inherited, std::vector<T>&\
    \ res) const {\n        if (!t || qr <= l || r <= ql) return;\n        const Node&\
    \ node = (*_pool)[t];\n        if (r - l == 1) {\n            res.push_back(mapping_at(inherited,\
    \ node.val, 0));\n            return;\n        }\n        int m = (l + r) >> 1;\n\
    \        collect_node(node.l, l, m, ql, qr, compose_for_child(inherited, node,\
    \ 0), res);\n        collect_node(node.r, m, r, ql, qr, compose_for_child(inherited,\
    \ node, m - l), res);\n    }\n\n    template <class G>\n    int max_right_node(int\
    \ t, int l, int r, int ql, T& sm, const F& inherited, G& g) const {\n        if\
    \ (r <= ql) return r;\n        const Node& node = (*_pool)[t];\n        if (ql\
    \ <= l) {\n            T nxt = ActedMonoid::op(sm, mapping_at(inherited, node.val,\
    \ 0));\n            if (g(nxt)) {\n                sm = std::move(nxt);\n    \
    \            return r;\n            }\n            if (r - l == 1) return l;\n\
    \        }\n        int m = (l + r) >> 1;\n        int res = max_right_node(node.l,\
    \ l, m, ql, sm, compose_for_child(inherited, node, 0), g);\n        if (res <\
    \ m) return res;\n        return max_right_node(node.r, m, r, ql, sm, compose_for_child(inherited,\
    \ node, m - l), g);\n    }\n\n    template <class G>\n    int min_left_node(int\
    \ t, int l, int r, int qr, T& sm, const F& inherited, G& g) const {\n        if\
    \ (qr <= l) return l;\n        const Node& node = (*_pool)[t];\n        if (r\
    \ <= qr) {\n            T nxt = ActedMonoid::op(mapping_at(inherited, node.val,\
    \ 0), sm);\n            if (g(nxt)) {\n                sm = std::move(nxt);\n\
    \                return l;\n            }\n            if (r - l == 1) return\
    \ r;\n        }\n        int m = (l + r) >> 1;\n        int res = min_left_node(node.r,\
    \ m, r, qr, sm, compose_for_child(inherited, node, m - l), g);\n        if (m\
    \ < res) return res;\n        return min_left_node(node.l, l, m, qr, sm, compose_for_child(inherited,\
    \ node, 0), g);\n    }\n\n   public:\n    PersistentLazySegtree() : PersistentLazySegtree(0)\
    \ {}\n\n    explicit PersistentLazySegtree(int n)\n        : _n(n), _root(0),\
    \ _pool(std::make_shared<std::vector<Node>>()) {\n        assert(0 <= n);\n  \
    \      _pool->push_back(Node());\n        if (_n > 0) _root = build(0, _n, std::vector<T>(_n,\
    \ ActedMonoid::id()));\n    }\n\n    explicit PersistentLazySegtree(const std::vector<T>&\
    \ v)\n        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        _pool->reserve(v.size() * 2 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build(0, _n, v);\n    }\n\n    explicit PersistentLazySegtree(std::vector<T>&&\
    \ v)\n        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        _pool->reserve(v.size() * 2 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build(0, _n, v);\n    }\n\n    template <typename\
    \ U>\n        requires(!std::same_as<U, T>) &&\n                (requires(U x)\
    \ { ActedMonoid::make(x); } || requires(U x, int i) { ActedMonoid::make(x, i);\
    \ } ||\n                 std::convertible_to<U, T>)\n    explicit PersistentLazySegtree(const\
    \ std::vector<U>& v)\n        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        _pool->reserve(v.size() * 2 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build_from_values(0, _n, v);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    PersistentLazySegtree set(int p, T x) const {\n     \
    \   assert(0 <= p && p < _n);\n        return PersistentLazySegtree(_n, set_node(_root,\
    \ 0, _n, p, std::move(x)), _pool);\n    }\n\n    T get(int p) const {\n      \
    \  assert(0 <= p && p < _n);\n        return prod(p, p + 1);\n    }\n\n    T operator[](int\
    \ p) const {\n        return get(p);\n    }\n\n    T prod(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return\
    \ ActedMonoid::id();\n        return prod_node(_root, 0, _n, l, r, ActedMonoid::op_id());\n\
    \    }\n\n    T all_prod() const {\n        return _root ? (*_pool)[_root].val\
    \ : ActedMonoid::id();\n    }\n\n    std::vector<T> to_vector() const {\n    \
    \    return to_vector(0, _n);\n    }\n\n    std::vector<T> to_vector(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        collect_node(_root, 0, _n, l, r,\
    \ ActedMonoid::op_id(), res);\n        return res;\n    }\n\n    PersistentLazySegtree\
    \ apply(int p, const F& f) const {\n        assert(0 <= p && p < _n);\n      \
    \  return apply(p, p + 1, f);\n    }\n\n    PersistentLazySegtree apply(int l,\
    \ int r, const F& f) const {\n        assert(0 <= l && l <= r && r <= _n);\n \
    \       if (l == r) return *this;\n        return PersistentLazySegtree(_n, apply_node(_root,\
    \ 0, _n, l, r, f), _pool);\n    }\n\n    PersistentLazySegtree copy_range_from(\n\
    \        const PersistentLazySegtree& source,\n        int l,\n        int r\n\
    \    ) const {\n        assert(_n == source._n);\n        assert(_pool == source._pool);\n\
    \        assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return *this;\n\
    \        int root = copy_range_node(_root, source._root, 0, _n, l, r);\n     \
    \   return PersistentLazySegtree(_n, root, _pool);\n    }\n\n    template <class\
    \ G>\n    int max_right(int l, G g) const {\n        assert(0 <= l && l <= _n);\n\
    \        assert(g(ActedMonoid::id()));\n        if (l == _n) return _n;\n    \
    \    T sm = ActedMonoid::id();\n        return max_right_node(_root, 0, _n, l,\
    \ sm, ActedMonoid::op_id(), g);\n    }\n\n    template <class G>\n    int min_left(int\
    \ r, G g) const {\n        assert(0 <= r && r <= _n);\n        assert(g(ActedMonoid::id()));\n\
    \        if (r == 0) return 0;\n        T sm = ActedMonoid::id();\n        return\
    \ min_left_node(_root, 0, _n, r, sm, ActedMonoid::op_id(), g);\n    }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/segtree/persistent_lazy_segtree.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n\
    #include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
    #line 15 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\n\
    namespace utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
    template <class T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate\
    \ <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \    int _position;\n    int _length;\n    bool _terminal;\n\n    bool refill()\
    \ {\n        _position = 0;\n        if (_terminal) {\n            if (std::fgets(_buffer,\
    \ buffer_size, _stream) == nullptr) {\n                _length = 0;\n        \
    \        return false;\n            }\n            _length = int(std::strlen(_buffer));\n\
    \        } else {\n            _length = int(std::fread(_buffer, 1, buffer_size,\
    \ _stream));\n        }\n        return _length != 0;\n    }\n\n    template <class\
    \ T>\n    bool read_integer_from_terminal(T& value) {\n        if (!skip_spaces())\
    \ return false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
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
    \          _terminal(::isatty(::fileno(stream)) != 0) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_terminal) return read_integer_from_terminal(value);\n\
    \        if (!prepare_number()) return false;\n        int c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        while (c <= ' ') c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n\n        bool negative = false;\n        if (c\
    \ == '-') {\n            negative = true;\n            c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        }\n\n        if constexpr (internal::is_signed_v<T>)\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               const int first = c - '0';\n                const int second =\
    \ static_cast<unsigned char>(_buffer[_position]) - '0';\n                if (0\
    \ <= second && second <= 9) {\n                    result = negative ? result\
    \ * 100 - (first * 10 + second)\n                                      : result\
    \ * 100 + (first * 10 + second);\n                    ++_position;\n         \
    \       } else {\n                    result = negative ? result * 10 - first\
    \ : result * 10 + first;\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = result;\n \
    \       } else {\n            T result = 0;\n            while ('0' <= c && c\
    \ <= '9') {\n                const unsigned first = unsigned(c - '0');\n     \
    \           const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = result * 100 + T(first * 10 + unsigned(second));\n             \
    \       ++_position;\n                } else {\n                    result = result\
    \ * 10 + T(first);\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = negative ?\
    \ T(0) - result : result;\n        }\n        if (_position > _length) _position\
    \ = _length;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ bool>\n    read(T& value) {\n        if (!skip_spaces()) return false;\n   \
    \     int c = read_char_raw();\n        bool negative = false;\n        if (c\
    \ == '-' || c == '+') {\n            negative = c == '-';\n            c = read_char_raw();\n\
    \        }\n\n        long double result = 0;\n        while ('0' <= c && c <=\
    \ '9') {\n            result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
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
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position == 0) return;\n\
    \        std::fwrite(_buffer, 1, _position, _stream);\n        _position = 0;\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<std::is_floating_point_v<T>>\n    write(T value) {\n   \
    \     char digits[128];\n        auto [end, error] = std::to_chars(\n        \
    \    digits,\n            digits + sizeof(digits),\n            value,\n     \
    \       _float_format,\n            _precision\n        );\n        if (error\
    \ != std::errc()) std::abort();\n        for (const char* pointer = digits; pointer\
    \ != end; pointer++) {\n            write_char(*pointer);\n        }\n    }\n\n\
    \    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 7 \"verify/ds/segtree/persistent_lazy_segtree.test.cpp\"\
    \n#include <optional>\n#line 10 \"verify/ds/segtree/persistent_lazy_segtree.test.cpp\"\
    \n\n#line 1 \"acted_monoid/range_add_range_sum.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAddRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\ntemplate <typename T>\nstruct RangeAddRangeSum\
    \ {\n    using value_type = RangeAddRangeSumNode<T>;\n    using operator_type\
    \ = T;\n\n    // Value Monoid (Sum)\n    static constexpr value_type id() {\n\
    \        return {T(0), 0};\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {a.sum + b.sum, a.size + b.size};\n\
    \    }\n    static constexpr value_type inv(const value_type& x) {\n        return\
    \ {-x.sum, -x.size};\n    }\n\n    // Operator Monoid (Add)\n    static constexpr\
    \ operator_type op_id() {\n        return 0;\n    }\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return f\
    \ + g;\n    }\n\n    // Mapping (sum + f * size)\n    static constexpr value_type\
    \ mapping(const operator_type& f, const value_type& x) {\n        return {x.sum\
    \ + f * x.size, x.size};\n    }\n\n    // Helper for initializing a leaf node\n\
    \    static constexpr value_type make(const T& val) {\n        return {val, 1};\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1\
    \ \"acted_monoid/range_affine_range_sum.hpp\"\n\n\n\n#line 5 \"acted_monoid/range_affine_range_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct\
    \ RangeAffineRangeSumNode {\n    T sum;\n    long long size;\n};\n\n// Designed\
    \ to accept Modint or similar types as T\ntemplate <typename T>\nstruct RangeAffineRangeSum\
    \ {\n    using value_type = RangeAffineRangeSumNode<T>;\n    using operator_type\
    \ = std::pair<T, T>;  // {a, b} for ax + b\n\n    // Value Monoid\n    static\
    \ constexpr value_type id() {\n        return {T(0), 0};\n    }\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        return {a.sum\
    \ + b.sum, a.size + b.size};\n    }\n\n    // Operator Monoid (Affine Composition)\n\
    \    // f(x) = a1*x + b1, g(x) = a2*x + b2\n    // f(g(x)) = a1*(a2*x + b2) +\
    \ b1 = (a1*a2)*x + (a1*b2 + b1)\n    static constexpr operator_type op_id() {\n\
    \        return {T(1), T(0)};\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return {f.first * g.first,\
    \ f.first * g.second + f.second};\n    }\n\n    // Mapping\n    // \\sum (a*x_i\
    \ + b) = a * \\sum x_i + b * size\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        return {f.first * x.sum +\
    \ f.second * T(x.size), x.size};\n    }\n\n    // Helper for initializing a leaf\
    \ node\n    static constexpr value_type make(const T& val) {\n        return {val,\
    \ 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n\
    #line 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n\
    #line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
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
    \ res = raw(1 % Modulus);\n        ModInt x = n < 0 ? inv() : *this;\n       \
    \ uint64_t exponent = n < 0 ? uint64_t(-(n + 1)) + 1 : uint64_t(n);\n        while\
    \ (exponent > 0) {\n            if (exponent & 1) res *= x;\n            x *=\
    \ x;\n            exponent >>= 1;\n        }\n        return res;\n    }\n\n \
    \   constexpr ModInt inv() const noexcept {\n        int64_t a = _v, b = Modulus,\
    \ u = 1, v = 0;\n        while (b) {\n            int64_t t = a / b;\n       \
    \     a -= t * b;\n            std::swap(a, b);\n            u -= t * v;\n   \
    \         std::swap(u, v);\n        }\n        assert(a == 1);\n        u %= Modulus;\n\
    \        if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\ntemplate <int Id = 0>\nstruct\
    \ DynamicModInt {\n   private:\n    uint32_t _v;\n    inline static uint32_t _mod\
    \ = 1;\n\n   public:\n    static uint32_t mod() noexcept {\n        return _mod;\n\
    \    }\n\n    static void set_mod(uint32_t modulus) noexcept {\n        assert(modulus\
    \ > 0);\n        assert(modulus <= uint32_t(1) << 31);\n        _mod = modulus;\n\
    \    }\n\n    static DynamicModInt raw(uint32_t v) noexcept {\n        assert(v\
    \ < _mod);\n        DynamicModInt x;\n        x._v = v;\n        return x;\n \
    \   }\n\n    DynamicModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    DynamicModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(_mod);\n     \
    \       if (x < 0) x += _mod;\n            _v = static_cast<uint32_t>(x);\n  \
    \      } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % _mod);\n        }\n    }\n\n    uint32_t val() const noexcept {\n        return\
    \ _v;\n    }\n\n    DynamicModInt& operator++() noexcept {\n        _v++;\n  \
    \      if (_v == _mod) _v = 0;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator--() noexcept {\n        if (_v == 0) _v = _mod;\n        _v--;\n  \
    \      return *this;\n    }\n\n    DynamicModInt operator++(int) noexcept {\n\
    \        DynamicModInt result = *this;\n        ++*this;\n        return result;\n\
    \    }\n\n    DynamicModInt operator--(int) noexcept {\n        DynamicModInt\
    \ result = *this;\n        --*this;\n        return result;\n    }\n\n    DynamicModInt&\
    \ operator+=(const DynamicModInt& rhs) noexcept {\n        _v += rhs._v;\n   \
    \     if (_v >= _mod) _v -= _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator-=(const DynamicModInt& rhs) noexcept {\n        _v -= rhs._v;\n   \
    \     if (_v >= _mod) _v += _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator*=(const DynamicModInt& rhs) noexcept {\n        _v = static_cast<uint32_t>(uint64_t(_v)\
    \ * rhs._v % _mod);\n        return *this;\n    }\n\n    DynamicModInt& operator/=(const\
    \ DynamicModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n\
    \    DynamicModInt operator+(const DynamicModInt& rhs) const noexcept {\n    \
    \    return DynamicModInt(*this) += rhs;\n    }\n\n    DynamicModInt operator-(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) -=\
    \ rhs;\n    }\n\n    DynamicModInt operator*(const DynamicModInt& rhs) const noexcept\
    \ {\n        return DynamicModInt(*this) *= rhs;\n    }\n\n    DynamicModInt operator/(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) /=\
    \ rhs;\n    }\n\n    bool operator==(const DynamicModInt& rhs) const noexcept\
    \ {\n        return _v == rhs._v;\n    }\n\n    bool operator!=(const DynamicModInt&\
    \ rhs) const noexcept {\n        return _v != rhs._v;\n    }\n\n    DynamicModInt\
    \ pow(long long exponent) const noexcept {\n        DynamicModInt result = raw(1\
    \ % _mod);\n        DynamicModInt base = exponent < 0 ? inv() : *this;\n     \
    \   uint64_t magnitude =\n            exponent < 0 ? uint64_t(-(exponent + 1))\
    \ + 1 : uint64_t(exponent);\n        while (magnitude > 0) {\n            if (magnitude\
    \ & 1) result *= base;\n            base *= base;\n            magnitude >>= 1;\n\
    \        }\n        return result;\n    }\n\n    DynamicModInt inv() const noexcept\
    \ {\n        int64_t a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n  \
    \          int64_t quotient = a / b;\n            a -= quotient * b;\n       \
    \     std::swap(a, b);\n            u -= quotient * v;\n            std::swap(u,\
    \ v);\n        }\n        assert(a == 1);\n        u %= _mod;\n        if (u <\
    \ 0) u += _mod;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const DynamicModInt& rhs) {\n   \
    \     return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, DynamicModInt& rhs) {\n        long long value;\n        is >> value;\n\
    \        rhs = DynamicModInt(value);\n        return is;\n    }\n};\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 14 \"verify/ds/segtree/persistent_lazy_segtree.test.cpp\"\
    \n\nnamespace {\n\nvoid test_range_add() {\n    using AM = m1une::acted_monoid::RangeAddRangeSum<long\
    \ long>;\n    using Seg = m1une::ds::PersistentLazySegtree<AM>;\n\n    Seg seg(std::vector<long\
    \ long>{1, 2, 3, 4, 5});\n    Seg seg1 = seg.apply(1, 4, 10);\n    Seg seg2 =\
    \ seg1.set(2, AM::make(100));\n    Seg seg3 = seg2.apply(0, 5, -1);\n\n    auto\
    \ check = [](const Seg& tree, const std::vector<long long>& a) {\n        assert(tree.size()\
    \ == int(a.size()));\n        assert(tree.empty() == a.empty());\n        auto\
    \ values = tree.to_vector();\n        assert(int(values.size()) == int(a.size()));\n\
    \        auto middle = tree.to_vector(1, 4);\n        assert(int(middle.size())\
    \ == 3);\n        long long total = 0;\n        for (long long x : a) total +=\
    \ x;\n        assert(tree.all_prod().sum == total);\n        for (int l = 0; l\
    \ <= int(a.size()); l++) {\n            long long sum = 0;\n            for (int\
    \ r = l; r <= int(a.size()); r++) {\n                assert(tree.prod(l, r).sum\
    \ == sum);\n                if (r < int(a.size())) sum += a[r];\n            }\n\
    \        }\n        for (int i = 0; i < int(a.size()); i++) {\n            assert(tree.get(i).sum\
    \ == a[i]);\n            assert(tree[i].sum == a[i]);\n            assert(values[i].sum\
    \ == a[i]);\n            if (1 <= i && i < 4) assert(middle[i - 1].sum == a[i]);\n\
    \        }\n    };\n\n    check(seg, {1, 2, 3, 4, 5});\n    check(seg1, {1, 12,\
    \ 13, 14, 5});\n    check(seg2, {1, 12, 100, 14, 5});\n    check(seg3, {0, 11,\
    \ 99, 13, 4});\n\n    assert(seg.prod(0, 5).sum == 15);\n    assert(seg1.prod(0,\
    \ 5).sum == 45);\n    assert(seg2.prod(0, 5).sum == 132);\n    assert(seg3.prod(0,\
    \ 5).sum == 127);\n    assert(seg.get(2).sum == 3);\n    assert(seg1.get(2).sum\
    \ == 13);\n    assert(seg2.get(2).sum == 100);\n    assert(seg3.get(2).sum ==\
    \ 99);\n    assert(seg1.max_right(0, [](const AM::value_type& x) { return x.sum\
    \ <= 26; }) == 3);\n    assert(seg1.min_left(5, [](const AM::value_type& x) {\
    \ return x.sum <= 19; }) == 3);\n\n    Seg mixed = seg.copy_range_from(seg2, 1,\
    \ 4);\n    check(mixed, {1, 12, 100, 14, 5});\n    assert(seg.prod(0, 5).sum ==\
    \ 15);\n    assert(seg2.prod(0, 5).sum == 132);\n}\n\n}  // namespace\n\nint main()\
    \ {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_range_add();\n\n    using mint = m1une::math::modint998244353;\n\
    \    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n    using Seg\
    \ = m1une::ds::PersistentLazySegtree<AM>;\n\n    int size, query_count;\n    fast_input\
    \ >> size >> query_count;\n    std::vector<mint> initial(size);\n    for (mint&\
    \ value : initial) fast_input >> value;\n\n    std::vector<std::optional<Seg>>\
    \ versions(query_count + 1);\n    versions[0].emplace(initial);\n    for (int\
    \ query = 0; query < query_count; query++) {\n        int type, version, left,\
    \ right;\n        fast_input >> type >> version;\n        version++;\n       \
    \ if (type == 0) {\n            mint multiplier, addition;\n            fast_input\
    \ >> left >> right >> multiplier >> addition;\n            versions[query + 1]\
    \ = versions[version]->apply(\n                left,\n                right,\n\
    \                std::pair<mint, mint>(multiplier, addition)\n            );\n\
    \        } else if (type == 1) {\n            int source;\n            fast_input\
    \ >> source >> left >> right;\n            source++;\n            versions[query\
    \ + 1] = versions[version]->copy_range_from(\n                *versions[source],\n\
    \                left,\n                right\n            );\n        } else\
    \ {\n            fast_input >> left >> right;\n            fast_output << versions[version]->prod(left,\
    \ right).sum << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_range_affine_range_sum\"\
    \n\n#include \"../../../ds/segtree/persistent_lazy_segtree.hpp\"\n\n#include <cassert>\n\
    #include \"../../../utilities/fast_io.hpp\"\n#include <optional>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../../acted_monoid/range_add_range_sum.hpp\"\
    \n#include \"../../../acted_monoid/range_affine_range_sum.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n\nnamespace {\n\nvoid test_range_add() {\n    using AM = m1une::acted_monoid::RangeAddRangeSum<long\
    \ long>;\n    using Seg = m1une::ds::PersistentLazySegtree<AM>;\n\n    Seg seg(std::vector<long\
    \ long>{1, 2, 3, 4, 5});\n    Seg seg1 = seg.apply(1, 4, 10);\n    Seg seg2 =\
    \ seg1.set(2, AM::make(100));\n    Seg seg3 = seg2.apply(0, 5, -1);\n\n    auto\
    \ check = [](const Seg& tree, const std::vector<long long>& a) {\n        assert(tree.size()\
    \ == int(a.size()));\n        assert(tree.empty() == a.empty());\n        auto\
    \ values = tree.to_vector();\n        assert(int(values.size()) == int(a.size()));\n\
    \        auto middle = tree.to_vector(1, 4);\n        assert(int(middle.size())\
    \ == 3);\n        long long total = 0;\n        for (long long x : a) total +=\
    \ x;\n        assert(tree.all_prod().sum == total);\n        for (int l = 0; l\
    \ <= int(a.size()); l++) {\n            long long sum = 0;\n            for (int\
    \ r = l; r <= int(a.size()); r++) {\n                assert(tree.prod(l, r).sum\
    \ == sum);\n                if (r < int(a.size())) sum += a[r];\n            }\n\
    \        }\n        for (int i = 0; i < int(a.size()); i++) {\n            assert(tree.get(i).sum\
    \ == a[i]);\n            assert(tree[i].sum == a[i]);\n            assert(values[i].sum\
    \ == a[i]);\n            if (1 <= i && i < 4) assert(middle[i - 1].sum == a[i]);\n\
    \        }\n    };\n\n    check(seg, {1, 2, 3, 4, 5});\n    check(seg1, {1, 12,\
    \ 13, 14, 5});\n    check(seg2, {1, 12, 100, 14, 5});\n    check(seg3, {0, 11,\
    \ 99, 13, 4});\n\n    assert(seg.prod(0, 5).sum == 15);\n    assert(seg1.prod(0,\
    \ 5).sum == 45);\n    assert(seg2.prod(0, 5).sum == 132);\n    assert(seg3.prod(0,\
    \ 5).sum == 127);\n    assert(seg.get(2).sum == 3);\n    assert(seg1.get(2).sum\
    \ == 13);\n    assert(seg2.get(2).sum == 100);\n    assert(seg3.get(2).sum ==\
    \ 99);\n    assert(seg1.max_right(0, [](const AM::value_type& x) { return x.sum\
    \ <= 26; }) == 3);\n    assert(seg1.min_left(5, [](const AM::value_type& x) {\
    \ return x.sum <= 19; }) == 3);\n\n    Seg mixed = seg.copy_range_from(seg2, 1,\
    \ 4);\n    check(mixed, {1, 12, 100, 14, 5});\n    assert(seg.prod(0, 5).sum ==\
    \ 15);\n    assert(seg2.prod(0, 5).sum == 132);\n}\n\n}  // namespace\n\nint main()\
    \ {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_range_add();\n\n    using mint = m1une::math::modint998244353;\n\
    \    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n    using Seg\
    \ = m1une::ds::PersistentLazySegtree<AM>;\n\n    int size, query_count;\n    fast_input\
    \ >> size >> query_count;\n    std::vector<mint> initial(size);\n    for (mint&\
    \ value : initial) fast_input >> value;\n\n    std::vector<std::optional<Seg>>\
    \ versions(query_count + 1);\n    versions[0].emplace(initial);\n    for (int\
    \ query = 0; query < query_count; query++) {\n        int type, version, left,\
    \ right;\n        fast_input >> type >> version;\n        version++;\n       \
    \ if (type == 0) {\n            mint multiplier, addition;\n            fast_input\
    \ >> left >> right >> multiplier >> addition;\n            versions[query + 1]\
    \ = versions[version]->apply(\n                left,\n                right,\n\
    \                std::pair<mint, mint>(multiplier, addition)\n            );\n\
    \        } else if (type == 1) {\n            int source;\n            fast_input\
    \ >> source >> left >> right;\n            source++;\n            versions[query\
    \ + 1] = versions[version]->copy_range_from(\n                *versions[source],\n\
    \                left,\n                right\n            );\n        } else\
    \ {\n            fast_input >> left >> right;\n            fast_output << versions[version]->prod(left,\
    \ right).sum << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/segtree/persistent_lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - utilities/fast_io.hpp
  - acted_monoid/range_add_range_sum.hpp
  - acted_monoid/range_affine_range_sum.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/ds/segtree/persistent_lazy_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 04:56:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/persistent_lazy_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/persistent_lazy_segtree.test.cpp
- /verify/verify/ds/segtree/persistent_lazy_segtree.test.cpp.html
title: verify/ds/segtree/persistent_lazy_segtree.test.cpp
---
