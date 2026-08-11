---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_persistent_base.hpp
    title: ds/detail/rollback_persistent_base.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_lazy_segtree.hpp
    title: Persistent Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_node_pool.hpp
    title: ds/segtree/persistent_node_pool.hpp
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
  bundledCode: "#line 1 \"ds/segtree/rollback_lazy_segtree.hpp\"\n\n\n\n#include <utility>\n\
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
    \n\n#line 1 \"ds/segtree/persistent_lazy_segtree.hpp\"\n\n\n\n#line 5 \"ds/segtree/persistent_lazy_segtree.hpp\"\
    \n#include <concepts>\n#include <memory>\n#line 9 \"ds/segtree/persistent_lazy_segtree.hpp\"\
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
    \n\n#line 1 \"ds/segtree/persistent_node_pool.hpp\"\n\n\n\n#line 9 \"ds/segtree/persistent_node_pool.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\n// Node must have\
    \ integer `left`, `right`, and `references` members.\ntemplate <class Node>\n\
    struct PersistentNodePool {\n    std::vector<Node> nodes;\n    int first_free\
    \ = 0;\n    std::size_t live_nodes = 0;\n\n   private:\n    void release_zero(int\
    \ node) {\n        int left = nodes[node].left;\n        int right = nodes[node].right;\n\
    \        nodes[node] = Node();\n        nodes[node].left = first_free;\n     \
    \   first_free = node;\n        --live_nodes;\n        if (left && --nodes[left].references\
    \ == 0) release_zero(left);\n        if (right && --nodes[right].references ==\
    \ 0) release_zero(right);\n    }\n\n   public:\n    PersistentNodePool() { nodes.emplace_back();\
    \ }\n\n    void reserve(std::size_t capacity) { nodes.reserve(capacity + 1); }\n\
    \n    Node& operator[](int node) { return nodes[node]; }\n\n    const Node& operator[](int\
    \ node) const { return nodes[node]; }\n\n    void retain(int node) {\n       \
    \ if (node) ++nodes[node].references;\n    }\n\n    void release(int node) {\n\
    \        if (!node) return;\n        assert(nodes[node].references > 0);\n   \
    \     if (--nodes[node].references == 0) release_zero(node);\n    }\n\n    template\
    \ <class... Args>\n    int emplace(Args&&... args) {\n        int result;\n  \
    \      if (!first_free) {\n            assert(nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
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
    #line 12 \"ds/segtree/persistent_lazy_segtree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid>\nstruct PersistentLazySegtree\
    \ {\n    using T = typename ActedMonoid::value_type;\n    using F = typename ActedMonoid::operator_type;\n\
    \n   private:\n    struct Node {\n        T val;\n        F lazy;\n        int\
    \ left, right;\n        int references;\n        bool has_lazy;\n\n        Node()\n\
    \            : val(ActedMonoid::id()), lazy(ActedMonoid::op_id()), left(0), right(0),\
    \ references(0), has_lazy(false) {}\n        explicit Node(T value)\n        \
    \    : val(std::move(value)), lazy(ActedMonoid::op_id()), left(0), right(0), references(0),\
    \ has_lazy(false) {}\n        Node(T value, int left_child, int right_child)\n\
    \            : val(std::move(value)),\n              lazy(ActedMonoid::op_id()),\n\
    \              left(left_child),\n              right(right_child),\n        \
    \      references(0),\n              has_lazy(false) {}\n    };\n\n    using Pool\
    \ = detail::PersistentNodePool<Node>;\n\n    int _n;\n    int _root;\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    explicit PersistentLazySegtree(int n, int root, std::shared_ptr<Pool>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {\n        _pool->retain(_root);\n\
    \    }\n\n    int new_node(const Node& node) const { return _pool->emplace(node);\
    \ }\n\n    int new_node(Node&& node) const { return _pool->emplace(std::move(node));\
    \ }\n\n    int clone_node(int t) const { return _pool->clone(t); }\n\n    template\
    \ <typename U>\n    static T make_value(const U& value, int index) {\n       \
    \ if constexpr (requires(U x) { ActedMonoid::make(x); }) {\n            return\
    \ ActedMonoid::make(value);\n        } else if constexpr (requires(U x, int i)\
    \ { ActedMonoid::make(x, i); }) {\n            return ActedMonoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n    static T mapping_at(const F& f, const T& value, long long\
    \ ord) {\n        if constexpr (requires(F g, T x, long long i) { ActedMonoid::mapping(g,\
    \ x, i); }) {\n            return ActedMonoid::mapping(f, value, ord);\n     \
    \   } else {\n            return ActedMonoid::mapping(f, value);\n        }\n\
    \    }\n\n    static F shift_operator(const F& f, long long ord) {\n        if\
    \ constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g, i); }) {\n\
    \            return ActedMonoid::op_shift(f, ord);\n        } else {\n       \
    \     return f;\n        }\n    }\n\n    F compose_for_child(const F& inherited,\
    \ const Node& node, long long ord) const {\n        F shifted = shift_operator(inherited,\
    \ ord);\n        if (!node.has_lazy) return shifted;\n        return ActedMonoid::op_comp(shifted,\
    \ shift_operator(node.lazy, ord));\n    }\n\n    int build(int l, int r, const\
    \ std::vector<T>& v) const {\n        if (l == r) return 0;\n        if (r - l\
    \ == 1) return new_node(Node(v[l]));\n        int m = (l + r) >> 1;\n        int\
    \ left = build(l, m, v);\n        int right = build(m, r, v);\n        return\
    \ new_node(Node(ActedMonoid::op((*_pool)[left].val, (*_pool)[right].val), left,\
    \ right));\n    }\n\n    int build(int l, int r, std::vector<T>& v) const {\n\
    \        if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(std::move(v[l])));\n\
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
    \ F& f, bool copy_on_write = false) const {\n        int res = copy_on_write ?\
    \ _pool->clone_if_shared(t) : clone_node(t);\n        all_apply_to_node(res, f);\n\
    \        return res;\n    }\n\n    void push(int t, int l, int r, bool copy_on_write\
    \ = false) const {\n        if (!(*_pool)[t].has_lazy) return;\n        F lazy\
    \ = (*_pool)[t].lazy;\n        int left = (*_pool)[t].left;\n        int right\
    \ = (*_pool)[t].right;\n        int m = (l + r) >> 1;\n        left = all_apply_clone(left,\
    \ lazy, copy_on_write);\n        right = all_apply_clone(right, shift_operator(lazy,\
    \ m - l), copy_on_write);\n        Node& node = (*_pool)[t];\n        _pool->replace(node.left,\
    \ left);\n        _pool->replace(node.right, right);\n        node.lazy = ActedMonoid::op_id();\n\
    \        node.has_lazy = false;\n    }\n\n    void update(int t) const {\n   \
    \     Node& node = (*_pool)[t];\n        node.val = ActedMonoid::op((*_pool)[node.left].val,\
    \ (*_pool)[node.right].val);\n    }\n\n    int set_node(int t, int l, int r, int\
    \ p, T value, bool copy_on_write = false) const {\n        t = copy_on_write ?\
    \ _pool->clone_if_shared(t) : clone_node(t);\n        if (r - l == 1) {\n    \
    \        Node& node = (*_pool)[t];\n            node.val = std::move(value);\n\
    \            node.lazy = ActedMonoid::op_id();\n            node.has_lazy = false;\n\
    \            return t;\n        }\n        push(t, l, r, copy_on_write);\n   \
    \     int m = (l + r) >> 1;\n        if (p < m) {\n            int child = set_node((*_pool)[t].left,\
    \ l, m, p, std::move(value), copy_on_write);\n            _pool->replace((*_pool)[t].left,\
    \ child);\n        } else {\n            int child = set_node((*_pool)[t].right,\
    \ m, r, p, std::move(value), copy_on_write);\n            _pool->replace((*_pool)[t].right,\
    \ child);\n        }\n        update(t);\n        return t;\n    }\n\n    int\
    \ apply_node(int t, int l, int r, int ql, int qr, const F& f, bool copy_on_write\
    \ = false) const {\n        if (qr <= l || r <= ql) return t;\n        t = copy_on_write\
    \ ? _pool->clone_if_shared(t) : clone_node(t);\n        if (ql <= l && r <= qr)\
    \ {\n            all_apply_to_node(t, shift_operator(f, l - ql));\n          \
    \  return t;\n        }\n        push(t, l, r, copy_on_write);\n        int m\
    \ = (l + r) >> 1;\n        int left = apply_node((*_pool)[t].left, l, m, ql, qr,\
    \ f, copy_on_write);\n        int right = apply_node((*_pool)[t].right, m, r,\
    \ ql, qr, f, copy_on_write);\n        _pool->replace((*_pool)[t].left, left);\n\
    \        _pool->replace((*_pool)[t].right, right);\n        update(t);\n     \
    \   return t;\n    }\n\n    int copy_range_node(int target, int source, int l,\
    \ int r, int ql, int qr) const {\n        if (qr <= l || r <= ql) return target;\n\
    \        if (ql <= l && r <= qr) return source;\n\n        target = clone_node(target);\n\
    \        source = clone_node(source);\n        _pool->retain(source);\n      \
    \  push(target, l, r);\n        push(source, l, r);\n\n        int m = (l + r)\
    \ >> 1;\n        int left = copy_range_node((*_pool)[target].left, (*_pool)[source].left,\
    \ l, m, ql, qr);\n        int right = copy_range_node((*_pool)[target].right,\
    \ (*_pool)[source].right, m, r, ql, qr);\n        _pool->replace((*_pool)[target].left,\
    \ left);\n        _pool->replace((*_pool)[target].right, right);\n        update(target);\n\
    \        _pool->release(source);\n        return target;\n    }\n\n    T prod_node(int\
    \ t, int l, int r, int ql, int qr, const F& inherited) const {\n        if (!t\
    \ || qr <= l || r <= ql) return ActedMonoid::id();\n        const Node& node =\
    \ (*_pool)[t];\n        if (ql <= l && r <= qr) return mapping_at(inherited, node.val,\
    \ 0);\n        int m = (l + r) >> 1;\n        return ActedMonoid::op(prod_node(node.left,\
    \ l, m, ql, qr, compose_for_child(inherited, node, 0)),\n                    \
    \           prod_node(node.right, m, r, ql, qr, compose_for_child(inherited, node,\
    \ m - l)));\n    }\n\n    void collect_node(int t, int l, int r, int ql, int qr,\
    \ const F& inherited, std::vector<T>& res) const {\n        if (!t || qr <= l\
    \ || r <= ql) return;\n        const Node& node = (*_pool)[t];\n        if (r\
    \ - l == 1) {\n            res.push_back(mapping_at(inherited, node.val, 0));\n\
    \            return;\n        }\n        int m = (l + r) >> 1;\n        collect_node(node.left,\
    \ l, m, ql, qr, compose_for_child(inherited, node, 0), res);\n        collect_node(node.right,\
    \ m, r, ql, qr, compose_for_child(inherited, node, m - l), res);\n    }\n\n  \
    \  template <class G>\n    int max_right_node(int t, int l, int r, int ql, T&\
    \ sm, const F& inherited, G& g) const {\n        if (r <= ql) return r;\n    \
    \    const Node& node = (*_pool)[t];\n        if (ql <= l) {\n            T nxt\
    \ = ActedMonoid::op(sm, mapping_at(inherited, node.val, 0));\n            if (g(nxt))\
    \ {\n                sm = std::move(nxt);\n                return r;\n       \
    \     }\n            if (r - l == 1) return l;\n        }\n        int m = (l\
    \ + r) >> 1;\n        int res = max_right_node(node.left, l, m, ql, sm, compose_for_child(inherited,\
    \ node, 0), g);\n        if (res < m) return res;\n        return max_right_node(node.right,\
    \ m, r, ql, sm, compose_for_child(inherited, node, m - l), g);\n    }\n\n    template\
    \ <class G>\n    int min_left_node(int t, int l, int r, int qr, T& sm, const F&\
    \ inherited, G& g) const {\n        if (qr <= l) return l;\n        const Node&\
    \ node = (*_pool)[t];\n        if (r <= qr) {\n            T nxt = ActedMonoid::op(mapping_at(inherited,\
    \ node.val, 0), sm);\n            if (g(nxt)) {\n                sm = std::move(nxt);\n\
    \                return l;\n            }\n            if (r - l == 1) return\
    \ r;\n        }\n        int m = (l + r) >> 1;\n        int res = min_left_node(node.right,\
    \ m, r, qr, sm, compose_for_child(inherited, node, m - l), g);\n        if (m\
    \ < res) return res;\n        return min_left_node(node.left, l, m, qr, sm, compose_for_child(inherited,\
    \ node, 0), g);\n    }\n\n   public:\n    PersistentLazySegtree() : PersistentLazySegtree(0)\
    \ {}\n\n    explicit PersistentLazySegtree(int n) : _n(n), _root(0), _pool(std::make_shared<Pool>())\
    \ {\n        assert(0 <= n);\n        if (_n > 0) _root = build(0, _n, std::vector<T>(_n,\
    \ ActedMonoid::id()));\n        _pool->retain(_root);\n    }\n\n    explicit PersistentLazySegtree(const\
    \ std::vector<T>& v)\n        : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>())\
    \ {\n        _pool->reserve(v.size() * 2);\n        if (_n > 0) _root = build(0,\
    \ _n, v);\n        _pool->retain(_root);\n    }\n\n    explicit PersistentLazySegtree(std::vector<T>&&\
    \ v) : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {\n      \
    \  _pool->reserve(v.size() * 2);\n        if (_n > 0) _root = build(0, _n, v);\n\
    \        _pool->retain(_root);\n    }\n\n    template <typename U>\n        requires(!std::same_as<U,\
    \ T>) &&\n                (requires(U x) { ActedMonoid::make(x); } || requires(U\
    \ x, int i) { ActedMonoid::make(x, i); } ||\n                 std::convertible_to<U,\
    \ T>)\n    explicit PersistentLazySegtree(const std::vector<U>& v)\n        :\
    \ _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {\n        _pool->reserve(v.size()\
    \ * 2);\n        if (_n > 0) _root = build_from_values(0, _n, v);\n        _pool->retain(_root);\n\
    \    }\n\n    PersistentLazySegtree(const PersistentLazySegtree& other) : _n(other._n),\
    \ _root(other._root), _pool(other._pool) {\n        if (_pool) _pool->retain(_root);\n\
    \    }\n\n    PersistentLazySegtree(PersistentLazySegtree&& other) noexcept\n\
    \        : _n(other._n), _root(other._root), _pool(std::move(other._pool)) {\n\
    \        other._n = 0;\n        other._root = 0;\n    }\n\n    PersistentLazySegtree&\
    \ operator=(const PersistentLazySegtree& other) {\n        if (this == &other)\
    \ return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _n = other._n;\n        _root\
    \ = other._root;\n        _pool = other._pool;\n        return *this;\n    }\n\
    \n    PersistentLazySegtree& operator=(PersistentLazySegtree&& other) noexcept\
    \ {\n        if (this == &other) return *this;\n        if (_pool) _pool->release(_root);\n\
    \        _n = other._n;\n        _root = other._root;\n        _pool = std::move(other._pool);\n\
    \        other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\
    \n    ~PersistentLazySegtree() {\n        if (_pool) _pool->release(_root);\n\
    \    }\n\n    int size() const { return _n; }\n\n    bool empty() const { return\
    \ _n == 0; }\n\n    void release() {\n        if (_pool) _pool->release(_root);\n\
    \        _pool = std::make_shared<Pool>();\n        _root = 0;\n        _n = 0;\n\
    \    }\n\n    std::size_t node_count() const { return _pool ? _pool->size() :\
    \ 0; }\n\n    PersistentLazySegtree set(int p, T x) const {\n        assert(0\
    \ <= p && p < _n);\n        return PersistentLazySegtree(_n, set_node(_root, 0,\
    \ _n, p, std::move(x)), _pool);\n    }\n\n    void set_inplace(int p, T x) {\n\
    \        assert(0 <= p && p < _n);\n        int root = set_node(_root, 0, _n,\
    \ p, std::move(x), true);\n        _pool->replace(_root, root);\n    }\n\n   \
    \ T get(int p) const {\n        assert(0 <= p && p < _n);\n        return prod(p,\
    \ p + 1);\n    }\n\n    T operator[](int p) const { return get(p); }\n\n    T\
    \ prod(int l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n \
    \       if (l == r) return ActedMonoid::id();\n        return prod_node(_root,\
    \ 0, _n, l, r, ActedMonoid::op_id());\n    }\n\n    T all_prod() const { return\
    \ _root ? (*_pool)[_root].val : ActedMonoid::id(); }\n\n    std::vector<T> to_vector()\
    \ const { return to_vector(0, _n); }\n\n    std::vector<T> to_vector(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        collect_node(_root, 0, _n, l, r,\
    \ ActedMonoid::op_id(), res);\n        return res;\n    }\n\n    PersistentLazySegtree\
    \ apply(int p, const F& f) const {\n        assert(0 <= p && p < _n);\n      \
    \  return apply(p, p + 1, f);\n    }\n\n    PersistentLazySegtree apply(int l,\
    \ int r, const F& f) const {\n        assert(0 <= l && l <= r && r <= _n);\n \
    \       if (l == r) return *this;\n        return PersistentLazySegtree(_n, apply_node(_root,\
    \ 0, _n, l, r, f), _pool);\n    }\n\n    void apply_inplace(int p, const F& f)\
    \ {\n        assert(0 <= p && p < _n);\n        apply_inplace(p, p + 1, f);\n\
    \    }\n\n    void apply_inplace(int l, int r, const F& f) {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        if (l == r) return;\n        int root =\
    \ apply_node(_root, 0, _n, l, r, f, true);\n        _pool->replace(_root, root);\n\
    \    }\n\n    PersistentLazySegtree copy_range_from(const PersistentLazySegtree&\
    \ source, int l, int r) const {\n        assert(_n == source._n);\n        assert(_pool\
    \ == source._pool);\n        assert(0 <= l && l <= r && r <= _n);\n        if\
    \ (l == r) return *this;\n        int root = copy_range_node(_root, source._root,\
    \ 0, _n, l, r);\n        return PersistentLazySegtree(_n, root, _pool);\n    }\n\
    \n    template <class G>\n    int max_right(int l, G g) const {\n        assert(0\
    \ <= l && l <= _n);\n        assert(g(ActedMonoid::id()));\n        if (l == _n)\
    \ return _n;\n        T sm = ActedMonoid::id();\n        return max_right_node(_root,\
    \ 0, _n, l, sm, ActedMonoid::op_id(), g);\n    }\n\n    template <class G>\n \
    \   int min_left(int r, G g) const {\n        assert(0 <= r && r <= _n);\n   \
    \     assert(g(ActedMonoid::id()));\n        if (r == 0) return 0;\n        T\
    \ sm = ActedMonoid::id();\n        return min_left_node(_root, 0, _n, r, sm, ActedMonoid::op_id(),\
    \ g);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 8 \"\
    ds/segtree/rollback_lazy_segtree.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <m1une::acted_monoid::IsActedMonoid ActedMonoid>\nstruct RollbackLazySegtree\n\
    \    : detail::RollbackPersistentBase<PersistentLazySegtree<ActedMonoid>> {\n\
    \    using T = typename ActedMonoid::value_type;\n    using F = typename ActedMonoid::operator_type;\n\
    \n   private:\n    using Persistent = PersistentLazySegtree<ActedMonoid>;\n  \
    \  using Base = detail::RollbackPersistentBase<Persistent>;\n\n   public:\n  \
    \  using Base::Base;\n\n    void set(int pos, T value) {\n        Base::commit(Base::persistent().set(pos,\
    \ std::move(value)));\n    }\n    void set_inplace(int pos, T value) { set(pos,\
    \ std::move(value)); }\n\n    void apply(int pos, const F& f) {\n        Base::commit(Base::persistent().apply(pos,\
    \ f));\n    }\n    void apply(int left, int right, const F& f) {\n        Base::commit(Base::persistent().apply(left,\
    \ right, f));\n    }\n    void apply_inplace(int pos, const F& f) { apply(pos,\
    \ f); }\n    void apply_inplace(int left, int right, const F& f) { apply(left,\
    \ right, f); }\n\n    void copy_range_from(const RollbackLazySegtree& source,\
    \ int left, int right) {\n        Base::commit(Base::persistent().copy_range_from(source.current_version(),\
    \ left, right));\n    }\n    void copy_range_from(const Persistent& source, int\
    \ left, int right) {\n        Base::commit(Base::persistent().copy_range_from(source,\
    \ left, right));\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP\
    \ 1\n\n#include <utility>\n\n#include \"../detail/rollback_persistent_base.hpp\"\
    \n#include \"persistent_lazy_segtree.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\n\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid>\nstruct RollbackLazySegtree\n\
    \    : detail::RollbackPersistentBase<PersistentLazySegtree<ActedMonoid>> {\n\
    \    using T = typename ActedMonoid::value_type;\n    using F = typename ActedMonoid::operator_type;\n\
    \n   private:\n    using Persistent = PersistentLazySegtree<ActedMonoid>;\n  \
    \  using Base = detail::RollbackPersistentBase<Persistent>;\n\n   public:\n  \
    \  using Base::Base;\n\n    void set(int pos, T value) {\n        Base::commit(Base::persistent().set(pos,\
    \ std::move(value)));\n    }\n    void set_inplace(int pos, T value) { set(pos,\
    \ std::move(value)); }\n\n    void apply(int pos, const F& f) {\n        Base::commit(Base::persistent().apply(pos,\
    \ f));\n    }\n    void apply(int left, int right, const F& f) {\n        Base::commit(Base::persistent().apply(left,\
    \ right, f));\n    }\n    void apply_inplace(int pos, const F& f) { apply(pos,\
    \ f); }\n    void apply_inplace(int left, int right, const F& f) { apply(left,\
    \ right, f); }\n\n    void copy_range_from(const RollbackLazySegtree& source,\
    \ int left, int right) {\n        Base::commit(Base::persistent().copy_range_from(source.current_version(),\
    \ left, right));\n    }\n    void copy_range_from(const Persistent& source, int\
    \ left, int right) {\n        Base::commit(Base::persistent().copy_range_from(source,\
    \ left, right));\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP\n"
  dependsOn:
  - ds/detail/rollback_persistent_base.hpp
  - ds/segtree/persistent_lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - ds/segtree/persistent_node_pool.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_lazy_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 04:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/segtree/rollback_lazy_segtree.hpp
layout: document
title: Rollback Lazy Segment Tree
---

## Overview

`RollbackLazySegtree<ActedMonoid>` provides point assignment, range actions,
range products, and linear-history rollback. `ActedMonoid` must satisfy
`m1une::acted_monoid::IsActedMonoid`.

## Methods

Constructors and read-only methods match
`PersistentLazySegtree<ActedMonoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const F& f)`, `void apply(int left, int right, const F& f)` | Applies an action to a point or `[left, right)`. | $O(\log N)$ |
| `void apply_inplace(...)` | Rollback-recording aliases of `apply`. | $O(\log N)$ |
| `void copy_range_from(const RollbackLazySegtree& source, int left, int right)` | Copies a range from a version in the same pool. | $O(\log N)$ |
| `void copy_range_from(const PersistentLazySegtree<ActedMonoid>& source, int left, int right)` | Persistent-handle overload. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentLazySegtree<ActedMonoid>& current_version() const` | Returns the current persistent state. | $O(1)$ |

Each update call advances history, including an empty-range action. $F$ is at
most the number of nodes created by the undone updates.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/rollback_lazy_segtree.hpp"

#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::ds::RollbackLazySegtree<AM> seg(std::vector<long long>{1, 2, 3});
int state = seg.snapshot();
seg.apply(0, 2, 5);
seg.rollback(state);
assert(seg.all_prod().sum == 6);
```
