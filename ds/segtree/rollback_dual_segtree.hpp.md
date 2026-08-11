---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_persistent_base.hpp
    title: ds/detail/rollback_persistent_base.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dual_segtree.hpp
    title: Persistent Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_node_pool.hpp
    title: ds/segtree/persistent_node_pool.hpp
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
  bundledCode: "#line 1 \"ds/segtree/rollback_dual_segtree.hpp\"\n\n\n\n#include <utility>\n\
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
    \n\n#line 1 \"ds/segtree/persistent_dual_segtree.hpp\"\n\n\n\n#line 5 \"ds/segtree/persistent_dual_segtree.hpp\"\
    \n#include <concepts>\n#include <memory>\n#line 9 \"ds/segtree/persistent_dual_segtree.hpp\"\
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
    #line 12 \"ds/segtree/persistent_dual_segtree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct PersistentDualSegtree\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    struct Node\
    \ {\n        T val;\n        int left, right;\n        int references;\n     \
    \   bool has_lazy;\n\n        Node() : val(Monoid::id()), left(0), right(0), references(0),\
    \ has_lazy(false) {}\n        explicit Node(T value) : val(std::move(value)),\
    \ left(0), right(0), references(0), has_lazy(false) {}\n        Node(int left_child,\
    \ int right_child)\n            : val(Monoid::id()), left(left_child), right(right_child),\
    \ references(0), has_lazy(false) {}\n    };\n\n    using Pool = detail::PersistentNodePool<Node>;\n\
    \n    int _n;\n    int _root;\n    std::shared_ptr<Pool> _pool;\n\n    explicit\
    \ PersistentDualSegtree(int n, int root, std::shared_ptr<Pool> pool)\n       \
    \ : _n(n), _root(root), _pool(std::move(pool)) {\n        _pool->retain(_root);\n\
    \    }\n\n    int new_node(const Node& node) const { return _pool->emplace(node);\
    \ }\n\n    int new_node(Node&& node) const { return _pool->emplace(std::move(node));\
    \ }\n\n    int clone_node(int t) const { return _pool->clone(t); }\n\n    template\
    \ <typename U>\n    static T make_value(const U& value, int index) {\n       \
    \ if constexpr (requires(U x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n\
    \        } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n\
    \            return Monoid::make(value, index);\n        } else {\n          \
    \  return static_cast<T>(value);\n        }\n    }\n\n    T compose_for_child(const\
    \ T& inherited, const Node& node) const {\n        if (!node.has_lazy) return\
    \ inherited;\n        return Monoid::op(inherited, node.val);\n    }\n\n    int\
    \ build(int l, int r, const std::vector<T>& v) const {\n        if (l == r) return\
    \ 0;\n        if (r - l == 1) return new_node(Node(v[l]));\n        int m = (l\
    \ + r) >> 1;\n        return new_node(Node(build(l, m, v), build(m, r, v)));\n\
    \    }\n\n    int build(int l, int r, std::vector<T>& v) const {\n        if (l\
    \ == r) return 0;\n        if (r - l == 1) return new_node(Node(std::move(v[l])));\n\
    \        int m = (l + r) >> 1;\n        return new_node(Node(build(l, m, v), build(m,\
    \ r, v)));\n    }\n\n    template <typename U>\n    int build_from_values(int\
    \ l, int r, const std::vector<U>& v) const {\n        if (l == r) return 0;\n\
    \        if (r - l == 1) return new_node(Node(make_value(v[l], l)));\n       \
    \ int m = (l + r) >> 1;\n        return new_node(Node(build_from_values(l, m,\
    \ v), build_from_values(m, r, v)));\n    }\n\n    void all_apply_to_node(int t,\
    \ const T& x, int l, int r) const {\n        Node& node = (*_pool)[t];\n     \
    \   if (r - l == 1) {\n            node.val = Monoid::op(x, node.val);\n     \
    \   } else {\n            node.val = node.has_lazy ? Monoid::op(x, node.val) :\
    \ x;\n            node.has_lazy = true;\n        }\n    }\n\n    int all_apply_clone(int\
    \ t, const T& x, int l, int r, bool copy_on_write = false) const {\n        int\
    \ res = copy_on_write ? _pool->clone_if_shared(t) : clone_node(t);\n        all_apply_to_node(res,\
    \ x, l, r);\n        return res;\n    }\n\n    void push(int t, int l, int r,\
    \ bool copy_on_write = false) const {\n        Node node = (*_pool)[t];\n    \
    \    if (!node.has_lazy || r - l == 1) return;\n        int m = (l + r) >> 1;\n\
    \        int left = all_apply_clone(node.left, node.val, l, m, copy_on_write);\n\
    \        int right = all_apply_clone(node.right, node.val, m, r, copy_on_write);\n\
    \        Node& target = (*_pool)[t];\n        _pool->replace(target.left, left);\n\
    \        _pool->replace(target.right, right);\n        target.val = Monoid::id();\n\
    \        target.has_lazy = false;\n    }\n\n    int set_node(int t, int l, int\
    \ r, int p, T value, bool copy_on_write = false) const {\n        t = copy_on_write\
    \ ? _pool->clone_if_shared(t) : clone_node(t);\n        if (r - l == 1) {\n  \
    \          Node& node = (*_pool)[t];\n            node.val = std::move(value);\n\
    \            node.has_lazy = false;\n            return t;\n        }\n      \
    \  push(t, l, r, copy_on_write);\n        int m = (l + r) >> 1;\n        if (p\
    \ < m) {\n            int child = set_node((*_pool)[t].left, l, m, p, std::move(value),\
    \ copy_on_write);\n            _pool->replace((*_pool)[t].left, child);\n    \
    \    } else {\n            int child = set_node((*_pool)[t].right, m, r, p, std::move(value),\
    \ copy_on_write);\n            _pool->replace((*_pool)[t].right, child);\n   \
    \     }\n        return t;\n    }\n\n    int apply_node(int t, int l, int r, int\
    \ ql, int qr, const T& x, bool copy_on_write = false) const {\n        if (qr\
    \ <= l || r <= ql) return t;\n        t = copy_on_write ? _pool->clone_if_shared(t)\
    \ : clone_node(t);\n        if (ql <= l && r <= qr) {\n            all_apply_to_node(t,\
    \ x, l, r);\n            return t;\n        }\n        push(t, l, r, copy_on_write);\n\
    \        int m = (l + r) >> 1;\n        int left = apply_node((*_pool)[t].left,\
    \ l, m, ql, qr, x, copy_on_write);\n        int right = apply_node((*_pool)[t].right,\
    \ m, r, ql, qr, x, copy_on_write);\n        _pool->replace((*_pool)[t].left, left);\n\
    \        _pool->replace((*_pool)[t].right, right);\n        return t;\n    }\n\
    \n    T get_node(int t, int l, int r, int p, const T& inherited) const {\n   \
    \     const Node& node = (*_pool)[t];\n        if (r - l == 1) return Monoid::op(inherited,\
    \ node.val);\n        int m = (l + r) >> 1;\n        if (p < m) return get_node(node.left,\
    \ l, m, p, compose_for_child(inherited, node));\n        return get_node(node.right,\
    \ m, r, p, compose_for_child(inherited, node));\n    }\n\n    void collect_node(int\
    \ t, int l, int r, int ql, int qr, const T& inherited, std::vector<T>& res) const\
    \ {\n        if (!t || qr <= l || r <= ql) return;\n        const Node& node =\
    \ (*_pool)[t];\n        if (r - l == 1) {\n            res.push_back(Monoid::op(inherited,\
    \ node.val));\n            return;\n        }\n        int m = (l + r) >> 1;\n\
    \        T next = compose_for_child(inherited, node);\n        collect_node(node.left,\
    \ l, m, ql, qr, next, res);\n        collect_node(node.right, m, r, ql, qr, next,\
    \ res);\n    }\n\n   public:\n    PersistentDualSegtree() : PersistentDualSegtree(0)\
    \ {}\n\n    explicit PersistentDualSegtree(int n) : _n(n), _root(0), _pool(std::make_shared<Pool>())\
    \ {\n        assert(0 <= n);\n        if (_n > 0) _root = build(0, _n, std::vector<T>(_n,\
    \ Monoid::id()));\n        _pool->retain(_root);\n    }\n\n    explicit PersistentDualSegtree(const\
    \ std::vector<T>& v)\n        : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>())\
    \ {\n        _pool->reserve(v.size() * 2);\n        if (_n > 0) _root = build(0,\
    \ _n, v);\n        _pool->retain(_root);\n    }\n\n    explicit PersistentDualSegtree(std::vector<T>&&\
    \ v) : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {\n      \
    \  _pool->reserve(v.size() * 2);\n        if (_n > 0) _root = build(0, _n, v);\n\
    \        _pool->retain(_root);\n    }\n\n    template <typename U>\n        requires(!std::same_as<U,\
    \ T>) &&\n                (requires(U x) { Monoid::make(x); } || requires(U x,\
    \ int i) { Monoid::make(x, i); } ||\n                 std::convertible_to<U, T>)\n\
    \    explicit PersistentDualSegtree(const std::vector<U>& v)\n        : _n(int(v.size())),\
    \ _root(0), _pool(std::make_shared<Pool>()) {\n        _pool->reserve(v.size()\
    \ * 2);\n        if (_n > 0) _root = build_from_values(0, _n, v);\n        _pool->retain(_root);\n\
    \    }\n\n    PersistentDualSegtree(const PersistentDualSegtree& other) : _n(other._n),\
    \ _root(other._root), _pool(other._pool) {\n        if (_pool) _pool->retain(_root);\n\
    \    }\n    PersistentDualSegtree(PersistentDualSegtree&& other) noexcept\n  \
    \      : _n(other._n), _root(other._root), _pool(std::move(other._pool)) {\n \
    \       other._n = 0;\n        other._root = 0;\n    }\n    PersistentDualSegtree&\
    \ operator=(const PersistentDualSegtree& other) {\n        if (this == &other)\
    \ return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _n = other._n;\n        _root\
    \ = other._root;\n        _pool = other._pool;\n        return *this;\n    }\n\
    \    PersistentDualSegtree& operator=(PersistentDualSegtree&& other) noexcept\
    \ {\n        if (this == &other) return *this;\n        if (_pool) _pool->release(_root);\n\
    \        _n = other._n;\n        _root = other._root;\n        _pool = std::move(other._pool);\n\
    \        other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\
    \    ~PersistentDualSegtree() {\n        if (_pool) _pool->release(_root);\n \
    \   }\n\n    int size() const { return _n; }\n\n    bool empty() const { return\
    \ _n == 0; }\n\n    void release() {\n        if (_pool) _pool->release(_root);\n\
    \        _pool = std::make_shared<Pool>();\n        _root = 0;\n        _n = 0;\n\
    \    }\n\n    std::size_t node_count() const { return _pool ? _pool->size() :\
    \ 0; }\n\n    PersistentDualSegtree set(int p, T x) const {\n        assert(0\
    \ <= p && p < _n);\n        return PersistentDualSegtree(_n, set_node(_root, 0,\
    \ _n, p, std::move(x)), _pool);\n    }\n\n    void set_inplace(int p, T x) {\n\
    \        assert(0 <= p && p < _n);\n        int root = set_node(_root, 0, _n,\
    \ p, std::move(x), true);\n        _pool->replace(_root, root);\n    }\n\n   \
    \ T get(int p) const {\n        assert(0 <= p && p < _n);\n        return get_node(_root,\
    \ 0, _n, p, Monoid::id());\n    }\n\n    T operator[](int p) const { return get(p);\
    \ }\n\n    PersistentDualSegtree apply(int p, const T& x) const {\n        assert(0\
    \ <= p && p < _n);\n        return apply(p, p + 1, x);\n    }\n\n    PersistentDualSegtree\
    \ apply(int l, int r, const T& x) const {\n        assert(0 <= l && l <= r &&\
    \ r <= _n);\n        if (l == r) return *this;\n        return PersistentDualSegtree(_n,\
    \ apply_node(_root, 0, _n, l, r, x), _pool);\n    }\n\n    void apply_inplace(int\
    \ p, const T& x) {\n        assert(0 <= p && p < _n);\n        apply_inplace(p,\
    \ p + 1, x);\n    }\n\n    void apply_inplace(int l, int r, const T& x) {\n  \
    \      assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return;\n   \
    \     int root = apply_node(_root, 0, _n, l, r, x, true);\n        _pool->replace(_root,\
    \ root);\n    }\n\n    std::vector<T> to_vector() const { return to_vector(0,\
    \ _n); }\n\n    std::vector<T> to_vector(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        collect_node(_root, 0, _n, l, r, Monoid::id(), res);\n      \
    \  return res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line\
    \ 8 \"ds/segtree/rollback_dual_segtree.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct RollbackDualSegtree\n\
    \    : detail::RollbackPersistentBase<PersistentDualSegtree<Monoid>> {\n    using\
    \ T = typename Monoid::value_type;\n\n   private:\n    using Persistent = PersistentDualSegtree<Monoid>;\n\
    \    using Base = detail::RollbackPersistentBase<Persistent>;\n\n   public:\n\
    \    using Base::Base;\n\n    void set(int pos, T value) {\n        Base::commit(Base::persistent().set(pos,\
    \ std::move(value)));\n    }\n    void set_inplace(int pos, T value) { set(pos,\
    \ std::move(value)); }\n\n    void apply(int pos, const T& value) {\n        Base::commit(Base::persistent().apply(pos,\
    \ value));\n    }\n    void apply(int left, int right, const T& value) {\n   \
    \     Base::commit(Base::persistent().apply(left, right, value));\n    }\n   \
    \ void apply_inplace(int pos, const T& value) { apply(pos, value); }\n    void\
    \ apply_inplace(int left, int right, const T& value) { apply(left, right, value);\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP\
    \ 1\n\n#include <utility>\n\n#include \"../detail/rollback_persistent_base.hpp\"\
    \n#include \"persistent_dual_segtree.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct RollbackDualSegtree\n\
    \    : detail::RollbackPersistentBase<PersistentDualSegtree<Monoid>> {\n    using\
    \ T = typename Monoid::value_type;\n\n   private:\n    using Persistent = PersistentDualSegtree<Monoid>;\n\
    \    using Base = detail::RollbackPersistentBase<Persistent>;\n\n   public:\n\
    \    using Base::Base;\n\n    void set(int pos, T value) {\n        Base::commit(Base::persistent().set(pos,\
    \ std::move(value)));\n    }\n    void set_inplace(int pos, T value) { set(pos,\
    \ std::move(value)); }\n\n    void apply(int pos, const T& value) {\n        Base::commit(Base::persistent().apply(pos,\
    \ value));\n    }\n    void apply(int left, int right, const T& value) {\n   \
    \     Base::commit(Base::persistent().apply(left, right, value));\n    }\n   \
    \ void apply_inplace(int pos, const T& value) { apply(pos, value); }\n    void\
    \ apply_inplace(int left, int right, const T& value) { apply(left, right, value);\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP\n"
  dependsOn:
  - ds/detail/rollback_persistent_base.hpp
  - ds/segtree/persistent_dual_segtree.hpp
  - monoid/concept.hpp
  - ds/segtree/persistent_node_pool.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_dual_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 04:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/segtree/rollback_dual_segtree.hpp
layout: document
title: Rollback Dual Segment Tree
---

## Overview

`RollbackDualSegtree<Monoid>` supports range monoid actions, point assignment,
point queries, and rollback. `Monoid` must satisfy
`m1une::monoid::IsMonoid`; composition order matches `PersistentDualSegtree`.

## Methods

Constructors and read-only methods (`size`, `empty`, `get`, `operator[]`, and
`node_count`) match `PersistentDualSegtree<Monoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const T& value)`, `void apply(int left, int right, const T& value)` | Composes an action at a point or on `[left, right)`. | $O(\log N)$ |
| `void apply_inplace(...)` | Rollback-recording aliases of `apply`. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentDualSegtree<Monoid>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$F$ counts nodes released.

## Example

```cpp
#include "ds/segtree/rollback_dual_segtree.hpp"
#include "monoid/add.hpp"

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackDualSegtree<Add> seg(4);
int state = seg.snapshot();
seg.apply(0, 3, 5);
seg.rollback(state);
assert(seg.get(1) == 0);
```
