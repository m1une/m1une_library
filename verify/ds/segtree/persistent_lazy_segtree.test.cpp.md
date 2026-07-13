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
    \n\n#line 6 \"verify/ds/segtree/persistent_lazy_segtree.test.cpp\"\n#include <iostream>\n\
    #include <optional>\n#line 10 \"verify/ds/segtree/persistent_lazy_segtree.test.cpp\"\
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
    #line 1 \"math/modint.hpp\"\n\n\n\n#line 5 \"math/modint.hpp\"\n#include <cstdint>\n\
    #line 7 \"math/modint.hpp\"\n#include <type_traits>\n#line 9 \"math/modint.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct\
    \ ModInt {\n    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n\
    \   private:\n    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod()\
    \ {\n        return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t\
    \ v) noexcept {\n        ModInt x;\n        x._v = v;\n        return x;\n   \
    \ }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    constexpr ModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n  \
    \          if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
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
    \ pow(long long exponent) const noexcept {\n        assert(exponent >= 0);\n \
    \       DynamicModInt result = raw(1 % _mod);\n        DynamicModInt base = *this;\n\
    \        while (exponent > 0) {\n            if (exponent & 1) result *= base;\n\
    \            base *= base;\n            exponent >>= 1;\n        }\n        return\
    \ result;\n    }\n\n    DynamicModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n            int64_t quotient\
    \ = a / b;\n            a -= quotient * b;\n            std::swap(a, b);\n   \
    \         u -= quotient * v;\n            std::swap(u, v);\n        }\n      \
    \  assert(a == 1);\n        u %= _mod;\n        if (u < 0) u += _mod;\n      \
    \  return raw(static_cast<uint32_t>(u));\n    }\n\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const DynamicModInt& rhs) {\n        return os << rhs._v;\n    }\n\n   \
    \ friend std::istream& operator>>(std::istream& is, DynamicModInt& rhs) {\n  \
    \      long long value;\n        is >> value;\n        rhs = DynamicModInt(value);\n\
    \        return is;\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 14 \"verify/ds/segtree/persistent_lazy_segtree.test.cpp\"\n\nnamespace\
    \ {\n\nvoid test_range_add() {\n    using AM = m1une::acted_monoid::RangeAddRangeSum<long\
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
    \ {\n    test_range_add();\n\n    using mint = m1une::math::modint998244353;\n\
    \    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n    using Seg\
    \ = m1une::ds::PersistentLazySegtree<AM>;\n\n    int size, query_count;\n    std::cin\
    \ >> size >> query_count;\n    std::vector<mint> initial(size);\n    for (mint&\
    \ value : initial) std::cin >> value;\n\n    std::vector<std::optional<Seg>> versions(query_count\
    \ + 1);\n    versions[0].emplace(initial);\n    for (int query = 0; query < query_count;\
    \ query++) {\n        int type, version, left, right;\n        std::cin >> type\
    \ >> version;\n        version++;\n        if (type == 0) {\n            mint\
    \ multiplier, addition;\n            std::cin >> left >> right >> multiplier >>\
    \ addition;\n            versions[query + 1] = versions[version]->apply(\n   \
    \             left,\n                right,\n                std::pair<mint, mint>(multiplier,\
    \ addition)\n            );\n        } else if (type == 1) {\n            int\
    \ source;\n            std::cin >> source >> left >> right;\n            source++;\n\
    \            versions[query + 1] = versions[version]->copy_range_from(\n     \
    \           *versions[source],\n                left,\n                right\n\
    \            );\n        } else {\n            std::cin >> left >> right;\n  \
    \          std::cout << versions[version]->prod(left, right).sum << '\\n';\n \
    \       }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_range_affine_range_sum\"\
    \n\n#include \"../../../ds/segtree/persistent_lazy_segtree.hpp\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \n#include \"../../../acted_monoid/range_add_range_sum.hpp\"\n#include \"../../../acted_monoid/range_affine_range_sum.hpp\"\
    \n#include \"../../../math/modint.hpp\"\n\nnamespace {\n\nvoid test_range_add()\
    \ {\n    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;\n    using\
    \ Seg = m1une::ds::PersistentLazySegtree<AM>;\n\n    Seg seg(std::vector<long\
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
    \ {\n    test_range_add();\n\n    using mint = m1une::math::modint998244353;\n\
    \    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n    using Seg\
    \ = m1une::ds::PersistentLazySegtree<AM>;\n\n    int size, query_count;\n    std::cin\
    \ >> size >> query_count;\n    std::vector<mint> initial(size);\n    for (mint&\
    \ value : initial) std::cin >> value;\n\n    std::vector<std::optional<Seg>> versions(query_count\
    \ + 1);\n    versions[0].emplace(initial);\n    for (int query = 0; query < query_count;\
    \ query++) {\n        int type, version, left, right;\n        std::cin >> type\
    \ >> version;\n        version++;\n        if (type == 0) {\n            mint\
    \ multiplier, addition;\n            std::cin >> left >> right >> multiplier >>\
    \ addition;\n            versions[query + 1] = versions[version]->apply(\n   \
    \             left,\n                right,\n                std::pair<mint, mint>(multiplier,\
    \ addition)\n            );\n        } else if (type == 1) {\n            int\
    \ source;\n            std::cin >> source >> left >> right;\n            source++;\n\
    \            versions[query + 1] = versions[version]->copy_range_from(\n     \
    \           *versions[source],\n                left,\n                right\n\
    \            );\n        } else {\n            std::cin >> left >> right;\n  \
    \          std::cout << versions[version]->prod(left, right).sum << '\\n';\n \
    \       }\n    }\n}\n"
  dependsOn:
  - ds/segtree/persistent_lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - acted_monoid/range_add_range_sum.hpp
  - acted_monoid/range_affine_range_sum.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/ds/segtree/persistent_lazy_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 03:22:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/persistent_lazy_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/persistent_lazy_segtree.test.cpp
- /verify/verify/ds/segtree/persistent_lazy_segtree.test.cpp.html
title: verify/ds/segtree/persistent_lazy_segtree.test.cpp
---
