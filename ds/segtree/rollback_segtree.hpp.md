---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_persistent_base.hpp
    title: ds/detail/rollback_persistent_base.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_node_pool.hpp
    title: ds/segtree/persistent_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_segtree.hpp
    title: Persistent Segment Tree
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/rollback_segtree.hpp\"\n\n\n\n#include <utility>\n\
    \n#line 1 \"ds/detail/rollback_persistent_base.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <limits>\n#line 8 \"ds/detail/rollback_persistent_base.hpp\"\
    \n#include <vector>\n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\
    \ntemplate <class Persistent>\nstruct RollbackPersistentBase : Persistent {\n\
    \   private:\n    std::vector<Persistent> _history;\n\n   protected:\n    using\
    \ Persistent::Persistent;\n\n    const Persistent& persistent() const {\n    \
    \    return *this;\n    }\n\n    void commit(Persistent next) {\n        assert(_history.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _history.emplace_back(persistent());\n\
    \        Persistent::operator=(std::move(next));\n    }\n\n   public:\n    RollbackPersistentBase()\
    \ = default;\n\n    explicit RollbackPersistentBase(Persistent initial)\n    \
    \    : Persistent(std::move(initial)) {}\n\n    int history_size() const {\n \
    \       return int(_history.size());\n    }\n\n    void reserve_history(int count)\
    \ {\n        assert(0 <= count);\n        _history.reserve(count);\n    }\n\n\
    \    bool undo() {\n        if (_history.empty()) return false;\n        Persistent::operator=(std::move(_history.back()));\n\
    \        _history.pop_back();\n        return true;\n    }\n\n    int snapshot()\
    \ const {\n        return history_size();\n    }\n\n    void rollback(int state)\
    \ {\n        assert(0 <= state && state <= history_size());\n        while (history_size()\
    \ > state) undo();\n    }\n\n    void clear_history() {\n        _history.clear();\n\
    \    }\n\n    void release() {\n        _history.clear();\n        Persistent::release();\n\
    \    }\n\n    const Persistent& current_version() const {\n        return persistent();\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/segtree/persistent_segtree.hpp\"\n\n\n\n#line 5 \"ds/segtree/persistent_segtree.hpp\"\
    \n#include <concepts>\n#include <memory>\n#line 9 \"ds/segtree/persistent_segtree.hpp\"\
    \n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 1 \"ds/segtree/persistent_node_pool.hpp\"\n\n\n\n\
    #line 9 \"ds/segtree/persistent_node_pool.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\nnamespace detail {\n\n// Node must have integer `left`, `right`, and `references`\
    \ members.\ntemplate <class Node>\nstruct PersistentNodePool {\n    std::vector<Node>\
    \ nodes;\n    int first_free = 0;\n    std::size_t live_nodes = 0;\n\n   private:\n\
    \    void release_zero(int node) {\n        int left = nodes[node].left;\n   \
    \     int right = nodes[node].right;\n        nodes[node] = Node();\n        nodes[node].left\
    \ = first_free;\n        first_free = node;\n        --live_nodes;\n        if\
    \ (left && --nodes[left].references == 0) release_zero(left);\n        if (right\
    \ && --nodes[right].references == 0) release_zero(right);\n    }\n\n   public:\n\
    \    PersistentNodePool() { nodes.emplace_back(); }\n\n    void reserve(std::size_t\
    \ capacity) { nodes.reserve(capacity + 1); }\n\n    Node& operator[](int node)\
    \ { return nodes[node]; }\n\n    const Node& operator[](int node) const { return\
    \ nodes[node]; }\n\n    void retain(int node) {\n        if (node) ++nodes[node].references;\n\
    \    }\n\n    void release(int node) {\n        if (!node) return;\n        assert(nodes[node].references\
    \ > 0);\n        if (--nodes[node].references == 0) release_zero(node);\n    }\n\
    \n    template <class... Args>\n    int emplace(Args&&... args) {\n        int\
    \ result;\n        if (!first_free) {\n            assert(nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \            nodes.emplace_back(std::forward<Args>(args)...);\n            result\
    \ = int(nodes.size()) - 1;\n        } else {\n            result = first_free;\n\
    \            first_free = nodes[result].left;\n            nodes[result] = Node(std::forward<Args>(args)...);\n\
    \        }\n        Node& node = nodes[result];\n        node.references = 0;\n\
    \        retain(node.left);\n        retain(node.right);\n        ++live_nodes;\n\
    \        return result;\n    }\n\n    int clone(int node) {\n        assert(node);\n\
    \        Node copy = nodes[node];\n        return emplace(std::move(copy));\n\
    \    }\n\n    bool unique(int node) const {\n        return !node || nodes[node].references\
    \ == 1;\n    }\n\n    // Returns node itself when it has one owner, otherwise\
    \ an unowned clone.\n    // The caller must attach a returned clone with replace()\
    \ before it can be\n    // released or exposed as a root.\n    int clone_if_shared(int\
    \ node) {\n        if (unique(node)) return node;\n        return clone(node);\n\
    \    }\n\n    void replace(int& edge, int node) {\n        if (edge == node) return;\n\
    \        retain(node);\n        int old = edge;\n        edge = node;\n      \
    \  release(old);\n    }\n\n    std::size_t size() const { return live_nodes; }\n\
    };\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\n\n\
    #line 12 \"ds/segtree/persistent_segtree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct PersistentSegtree\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    struct Node\
    \ {\n        T val;\n        int left, right;\n        int references;\n\n   \
    \     Node() : val(Monoid::id()), left(0), right(0), references(0) {}\n      \
    \  explicit Node(T value) : val(std::move(value)), left(0), right(0), references(0)\
    \ {}\n        Node(T value, int left_child, int right_child)\n            : val(std::move(value)),\
    \ left(left_child), right(right_child), references(0) {}\n    };\n\n    using\
    \ Pool = detail::PersistentNodePool<Node>;\n\n    int _n;\n    int _root;\n  \
    \  std::shared_ptr<Pool> _pool;\n\n    explicit PersistentSegtree(int n, int root,\
    \ std::shared_ptr<Pool> pool)\n        : _n(n), _root(root), _pool(std::move(pool))\
    \ {\n        _pool->retain(_root);\n    }\n\n    int new_node(const Node& node)\
    \ const { return _pool->emplace(node); }\n\n    int new_node(Node&& node) const\
    \ { return _pool->emplace(std::move(node)); }\n\n    template <typename U>\n \
    \   static T make_value(const U& value, int index) {\n        if constexpr (requires(U\
    \ x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n      \
    \  } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n    \
    \        return Monoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n    int build(int l, int r, const\
    \ std::vector<T>& v) const {\n        if (l == r) return 0;\n        if (r - l\
    \ == 1) return new_node(Node(v[l]));\n        int m = (l + r) >> 1;\n        int\
    \ left = build(l, m, v);\n        int right = build(m, r, v);\n        return\
    \ new_node(Node(Monoid::op(_pool->nodes[left].val, _pool->nodes[right].val), left,\
    \ right));\n    }\n\n    int build(int l, int r, std::vector<T>& v) const {\n\
    \        if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(std::move(v[l])));\n\
    \        int m = (l + r) >> 1;\n        int left = build(l, m, v);\n        int\
    \ right = build(m, r, v);\n        return new_node(Node(Monoid::op(_pool->nodes[left].val,\
    \ _pool->nodes[right].val), left, right));\n    }\n\n    template <typename U>\n\
    \    int build_from_values(int l, int r, const std::vector<U>& v) const {\n  \
    \      if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(make_value(v[l],\
    \ l)));\n        int m = (l + r) >> 1;\n        int left = build_from_values(l,\
    \ m, v);\n        int right = build_from_values(m, r, v);\n        return new_node(Node(Monoid::op(_pool->nodes[left].val,\
    \ _pool->nodes[right].val), left, right));\n    }\n\n    int set_node(int t, int\
    \ l, int r, int p, T value, bool copy_on_write = false) const {\n        if (copy_on_write)\
    \ t = _pool->clone_if_shared(t);\n        if (r - l == 1) {\n            if (copy_on_write)\
    \ {\n                _pool->nodes[t].val = std::move(value);\n               \
    \ return t;\n            }\n            return new_node(Node(std::move(value)));\n\
    \        }\n        int m = (l + r) >> 1;\n        int left = _pool->nodes[t].left;\n\
    \        int right = _pool->nodes[t].right;\n        if (p < m) {\n          \
    \  left = set_node(left, l, m, p, std::move(value), copy_on_write);\n        }\
    \ else {\n            right = set_node(right, m, r, p, std::move(value), copy_on_write);\n\
    \        }\n        T product = Monoid::op(_pool->nodes[left].val, _pool->nodes[right].val);\n\
    \        if (copy_on_write) {\n            _pool->replace(_pool->nodes[t].left,\
    \ left);\n            _pool->replace(_pool->nodes[t].right, right);\n        \
    \    _pool->nodes[t].val = std::move(product);\n            return t;\n      \
    \  }\n        return new_node(Node(std::move(product), left, right));\n    }\n\
    \n    T prod_node(int t, int l, int r, int ql, int qr) const {\n        if (!t\
    \ || qr <= l || r <= ql) return Monoid::id();\n        if (ql <= l && r <= qr)\
    \ return _pool->nodes[t].val;\n        int m = (l + r) >> 1;\n        return Monoid::op(prod_node(_pool->nodes[t].left,\
    \ l, m, ql, qr),\n                          prod_node(_pool->nodes[t].right, m,\
    \ r, ql, qr));\n    }\n\n    void collect_node(int t, int l, int r, int ql, int\
    \ qr, std::vector<T>& res) const {\n        if (!t || qr <= l || r <= ql) return;\n\
    \        if (r - l == 1) {\n            res.push_back(_pool->nodes[t].val);\n\
    \            return;\n        }\n        int m = (l + r) >> 1;\n        collect_node(_pool->nodes[t].left,\
    \ l, m, ql, qr, res);\n        collect_node(_pool->nodes[t].right, m, r, ql, qr,\
    \ res);\n    }\n\n    template <class F>\n    int max_right_node(int t, int l,\
    \ int r, int ql, T& sm, F& f) const {\n        if (r <= ql) return r;\n      \
    \  if (ql <= l) {\n            T nxt = Monoid::op(sm, _pool->nodes[t].val);\n\
    \            if (f(nxt)) {\n                sm = std::move(nxt);\n           \
    \     return r;\n            }\n            if (r - l == 1) return l;\n      \
    \  }\n        int m = (l + r) >> 1;\n        int res = max_right_node(_pool->nodes[t].left,\
    \ l, m, ql, sm, f);\n        if (res < m) return res;\n        return max_right_node(_pool->nodes[t].right,\
    \ m, r, ql, sm, f);\n    }\n\n    template <class F>\n    int min_left_node(int\
    \ t, int l, int r, int qr, T& sm, F& f) const {\n        if (qr <= l) return l;\n\
    \        if (r <= qr) {\n            T nxt = Monoid::op(_pool->nodes[t].val, sm);\n\
    \            if (f(nxt)) {\n                sm = std::move(nxt);\n           \
    \     return l;\n            }\n            if (r - l == 1) return r;\n      \
    \  }\n        int m = (l + r) >> 1;\n        int res = min_left_node(_pool->nodes[t].right,\
    \ m, r, qr, sm, f);\n        if (m < res) return res;\n        return min_left_node(_pool->nodes[t].left,\
    \ l, m, qr, sm, f);\n    }\n\n   public:\n    PersistentSegtree() : PersistentSegtree(0)\
    \ {}\n\n    explicit PersistentSegtree(int n) : _n(n), _root(0), _pool(std::make_shared<Pool>())\
    \ {\n        assert(0 <= n);\n        if (_n > 0) _root = build(0, _n, std::vector<T>(_n,\
    \ Monoid::id()));\n        _pool->retain(_root);\n    }\n\n    explicit PersistentSegtree(const\
    \ std::vector<T>& v) : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>())\
    \ {\n        _pool->reserve(v.size() * 2);\n        if (_n > 0) _root = build(0,\
    \ _n, v);\n        _pool->retain(_root);\n    }\n\n    explicit PersistentSegtree(std::vector<T>&&\
    \ v) : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {\n      \
    \  _pool->reserve(v.size() * 2);\n        if (_n > 0) _root = build(0, _n, v);\n\
    \        _pool->retain(_root);\n    }\n\n    template <typename U>\n        requires(!std::same_as<U,\
    \ T>) &&\n                (requires(U x) { Monoid::make(x); } || requires(U x,\
    \ int i) { Monoid::make(x, i); } ||\n                 std::convertible_to<U, T>)\n\
    \    explicit PersistentSegtree(const std::vector<U>& v)\n        : _n(int(v.size())),\
    \ _root(0), _pool(std::make_shared<Pool>()) {\n        _pool->reserve(v.size()\
    \ * 2);\n        if (_n > 0) _root = build_from_values(0, _n, v);\n        _pool->retain(_root);\n\
    \    }\n\n    PersistentSegtree(const PersistentSegtree& other) : _n(other._n),\
    \ _root(other._root), _pool(other._pool) {\n        if (_pool) _pool->retain(_root);\n\
    \    }\n\n    PersistentSegtree(PersistentSegtree&& other) noexcept\n        :\
    \ _n(other._n), _root(other._root), _pool(std::move(other._pool)) {\n        other._n\
    \ = 0;\n        other._root = 0;\n    }\n\n    PersistentSegtree& operator=(const\
    \ PersistentSegtree& other) {\n        if (this == &other) return *this;\n   \
    \     if (other._pool) other._pool->retain(other._root);\n        if (_pool) _pool->release(_root);\n\
    \        _n = other._n;\n        _root = other._root;\n        _pool = other._pool;\n\
    \        return *this;\n    }\n\n    PersistentSegtree& operator=(PersistentSegtree&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ _pool->release(_root);\n        _n = other._n;\n        _root = other._root;\n\
    \        _pool = std::move(other._pool);\n        other._n = 0;\n        other._root\
    \ = 0;\n        return *this;\n    }\n\n    ~PersistentSegtree() {\n        if\
    \ (_pool) _pool->release(_root);\n    }\n\n    int size() const { return _n; }\n\
    \n    bool empty() const { return _n == 0; }\n\n    // Drops this version immediately.\
    \ Other versions and shared nodes stay valid.\n    void release() {\n        if\
    \ (_pool) _pool->release(_root);\n        _pool = std::make_shared<Pool>();\n\
    \        _root = 0;\n        _n = 0;\n    }\n\n    std::size_t node_count() const\
    \ { return _pool ? _pool->size() : 0; }\n\n    PersistentSegtree set(int p, T\
    \ x) const {\n        assert(0 <= p && p < _n);\n        return PersistentSegtree(_n,\
    \ set_node(_root, 0, _n, p, std::move(x)), _pool);\n    }\n\n    void set_inplace(int\
    \ p, T x) {\n        assert(0 <= p && p < _n);\n        int root = set_node(_root,\
    \ 0, _n, p, std::move(x), true);\n        _pool->replace(_root, root);\n    }\n\
    \n    T get(int p) const {\n        assert(0 <= p && p < _n);\n        int t =\
    \ _root;\n        int l = 0, r = _n;\n        while (r - l > 1) {\n          \
    \  int m = (l + r) >> 1;\n            if (p < m) {\n                t = _pool->nodes[t].left;\n\
    \                r = m;\n            } else {\n                t = _pool->nodes[t].right;\n\
    \                l = m;\n            }\n        }\n        return _pool->nodes[t].val;\n\
    \    }\n\n    T operator[](int p) const { return get(p); }\n\n    T prod(int l,\
    \ int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l\
    \ == r) return Monoid::id();\n        return prod_node(_root, 0, _n, l, r);\n\
    \    }\n\n    T all_prod() const { return _root ? _pool->nodes[_root].val : Monoid::id();\
    \ }\n\n    std::vector<T> to_vector() const { return to_vector(0, _n); }\n\n \
    \   std::vector<T> to_vector(int l, int r) const {\n        assert(0 <= l && l\
    \ <= r && r <= _n);\n        std::vector<T> res;\n        res.reserve(r - l);\n\
    \        collect_node(_root, 0, _n, l, r, res);\n        return res;\n    }\n\n\
    \    template <class F>\n    int max_right(int l, F f) const {\n        assert(0\
    \ <= l && l <= _n);\n        assert(f(Monoid::id()));\n        if (l == _n) return\
    \ _n;\n        T sm = Monoid::id();\n        return max_right_node(_root, 0, _n,\
    \ l, sm, f);\n    }\n\n    template <class F>\n    int min_left(int r, F f) const\
    \ {\n        assert(0 <= r && r <= _n);\n        assert(f(Monoid::id()));\n  \
    \      if (r == 0) return 0;\n        T sm = Monoid::id();\n        return min_left_node(_root,\
    \ 0, _n, r, sm, f);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    \n#line 8 \"ds/segtree/rollback_segtree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct RollbackSegtree\n\
    \    : detail::RollbackPersistentBase<PersistentSegtree<Monoid>> {\n    using\
    \ T = typename Monoid::value_type;\n\n   private:\n    using Persistent = PersistentSegtree<Monoid>;\n\
    \    using Base = detail::RollbackPersistentBase<Persistent>;\n\n   public:\n\
    \    using Base::Base;\n\n    void set(int pos, T value) {\n        Base::commit(Base::persistent().set(pos,\
    \ std::move(value)));\n    }\n    void set_inplace(int pos, T value) { set(pos,\
    \ std::move(value)); }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP\
    \ 1\n\n#include <utility>\n\n#include \"../detail/rollback_persistent_base.hpp\"\
    \n#include \"persistent_segtree.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <m1une::monoid::IsMonoid Monoid>\nstruct RollbackSegtree\n    : detail::RollbackPersistentBase<PersistentSegtree<Monoid>>\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    using Persistent\
    \ = PersistentSegtree<Monoid>;\n    using Base = detail::RollbackPersistentBase<Persistent>;\n\
    \n   public:\n    using Base::Base;\n\n    void set(int pos, T value) {\n    \
    \    Base::commit(Base::persistent().set(pos, std::move(value)));\n    }\n   \
    \ void set_inplace(int pos, T value) { set(pos, std::move(value)); }\n};\n\n}\
    \  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP\n"
  dependsOn:
  - ds/detail/rollback_persistent_base.hpp
  - ds/segtree/persistent_segtree.hpp
  - monoid/concept.hpp
  - ds/segtree/persistent_node_pool.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 04:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/segtree/rollback_segtree.hpp
layout: document
title: Rollback Segment Tree
---

## Overview

`RollbackSegtree<Monoid>` is a mutable segment tree with point assignment,
range products, and linear-history rollback. `Monoid` must satisfy
`m1une::monoid::IsMonoid`. Saved roots share persistent nodes.

## Methods

Constructors and read-only methods (`size`, `empty`, `get`, `operator[]`,
`prod`, `all_prod`, `to_vector`, `max_right`, `min_left`, and `node_count`)
match `PersistentSegtree<Monoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point and advances history. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one assignment. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentSegtree<Monoid>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$F = O(\log N)$ per undone assignment and counts nodes released.

## Example

```cpp
#include "ds/segtree/rollback_segtree.hpp"
#include "monoid/add.hpp"

#include <vector>

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackSegtree<Add> seg(std::vector<long long>{1, 2, 3});
int state = seg.snapshot();
seg.set(1, 8);
seg.rollback(state);
assert(seg.all_prod() == 6);
```
