---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_add_range_sum.hpp
    title: Range Add Range Sum
  - icon: ':heavy_check_mark:'
    path: beats_acted_monoid/concept.hpp
    title: Beats Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_multiset.hpp
    title: Persistent Ordered Multiset
  - icon: ':heavy_check_mark:'
    path: ds/detail/persistent_binary_node_pool.hpp
    title: ds/detail/persistent_binary_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: ds/detail/persistent_binary_node_pool.hpp
    title: ds/detail/persistent_binary_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: ds/detail/persistent_binary_node_pool.hpp
    title: ds/detail/persistent_binary_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: ds/dsu/persistent_dsu.hpp
    title: Persistent DSU
  - icon: ':heavy_check_mark:'
    path: ds/dsu/persistent_potentialized_dsu.hpp
    title: Persistent Potentialized DSU
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_array.hpp
    title: Persistent Dynamic Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
    title: Persistent Dynamic Lazy Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_monoid_array.hpp
    title: Persistent Dynamic Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dual_segtree.hpp
    title: Persistent Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dynamic_dual_segtree.hpp
    title: Persistent Dynamic Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dynamic_lazy_segtree.hpp
    title: Persistent Dynamic Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dynamic_segtree.hpp
    title: Persistent Dynamic Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_lazy_segtree.hpp
    title: Persistent Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_node_pool.hpp
    title: ds/segtree/persistent_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_segtree.hpp
    title: Persistent Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_segtree_beats.hpp
    title: ds/segtree/persistent_segtree_beats.hpp
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/ds/persistent_cow.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"acted_monoid/range_add_range_sum.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\n\
    struct RangeAddRangeSumNode {\n    T sum;\n    long long size;\n};\n\ntemplate\
    \ <typename T>\nstruct RangeAddRangeSum {\n    using value_type = RangeAddRangeSumNode<T>;\n\
    \    using operator_type = T;\n    static constexpr bool commutative = true;\n\
    \    static constexpr bool operator_commutative = true;\n\n    // Value Monoid\
    \ (Sum)\n    static constexpr value_type id() {\n        return {T(0), 0};\n \
    \   }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {a.sum + b.sum, a.size + b.size};\n    }\n    static constexpr\
    \ value_type inv(const value_type& x) {\n        return {-x.sum, -x.size};\n \
    \   }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type op_id()\
    \ {\n        return 0;\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f + g;\n    }\n\n\
    \    // Mapping (sum + f * size)\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        return {x.sum + f * x.size,\
    \ x.size};\n    }\n\n    // Helper for initializing a leaf node\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1};\n    }\n};\n\n}  //\
    \ namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"ds/dsu/persistent_dsu.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <memory>\n#include <utility>\n#include <vector>\n\n#line 1 \"ds/detail/persistent_binary_node_pool.hpp\"\
    \n\n\n\n#line 6 \"ds/detail/persistent_binary_node_pool.hpp\"\n#include <deque>\n\
    #include <limits>\n#include <optional>\n#line 11 \"ds/detail/persistent_binary_node_pool.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\n// Node must have\
    \ integer `l` and `r` members. New nodes initially have no\n// owner; discard_unreferenced()\
    \ removes temporary path-copy nodes after the\n// result roots have been retained.\n\
    template <class Node, int null_node = -1>\nstruct PersistentBinaryNodePool {\n\
    \   private:\n    std::deque<std::optional<Node>> _nodes;\n    std::vector<int>\
    \ _references;\n    std::vector<int> _next_free;\n    std::vector<int> _unowned;\n\
    \    int _first_free = -1;\n    std::size_t _live_nodes = 0;\n\n    void release_zero(int\
    \ node) {\n        assert(node != null_node && _nodes[node].has_value());\n  \
    \      int left = (*_nodes[node]).l;\n        int right = (*_nodes[node]).r;\n\
    \        _nodes[node].reset();\n        _next_free[node] = _first_free;\n    \
    \    _first_free = node;\n        --_live_nodes;\n        if (left != null_node\
    \ && --_references[left] == 0) release_zero(left);\n        if (right != null_node\
    \ && --_references[right] == 0) release_zero(right);\n    }\n\n   public:\n  \
    \  PersistentBinaryNodePool() {\n        if constexpr (null_node == 0) {\n   \
    \         _nodes.emplace_back();\n            _references.push_back(0);\n    \
    \        _next_free.push_back(-1);\n        }\n    }\n\n    Node& operator[](int\
    \ node) {\n        assert(node != null_node && _nodes[node].has_value());\n  \
    \      return *_nodes[node];\n    }\n\n    const Node& operator[](int node) const\
    \ {\n        assert(node != null_node && _nodes[node].has_value());\n        return\
    \ *_nodes[node];\n    }\n\n    template <class... Args>\n    int emplace(Args&&...\
    \ args) {\n        int result;\n        if (_first_free == -1) {\n           \
    \ assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n    \
    \        result = int(_nodes.size());\n            _nodes.emplace_back(std::in_place,\
    \ std::forward<Args>(args)...);\n            _references.push_back(0);\n     \
    \       _next_free.push_back(-1);\n        } else {\n            result = _first_free;\n\
    \            _first_free = _next_free[result];\n            _nodes[result].emplace(std::forward<Args>(args)...);\n\
    \            _references[result] = 0;\n        }\n        retain((*_nodes[result]).l);\n\
    \        retain((*_nodes[result]).r);\n        _unowned.push_back(result);\n \
    \       ++_live_nodes;\n        return result;\n    }\n\n    void retain(int node)\
    \ {\n        if (node != null_node) {\n            assert(_nodes[node].has_value());\n\
    \            ++_references[node];\n        }\n    }\n\n    void release(int node)\
    \ {\n        if (node == null_node) return;\n        assert(_nodes[node].has_value()\
    \ && _references[node] > 0);\n        if (--_references[node] == 0) release_zero(node);\n\
    \    }\n\n    bool unique(int node) const {\n        return node == null_node\
    \ || _references[node] == 1;\n    }\n\n    int clone(int node) {\n        assert(node\
    \ != null_node && _nodes[node].has_value());\n        return emplace(*_nodes[node]);\n\
    \    }\n\n    // Returns node itself when it has one owner, otherwise an unowned\
    \ clone.\n    // A returned clone becomes owned when a root or parent edge retains\
    \ it.\n    int clone_if_shared(int node) {\n        if (unique(node)) return node;\n\
    \        return clone(node);\n    }\n\n    void replace(int& edge, int node) {\n\
    \        if (edge == node) return;\n        retain(node);\n        int old = edge;\n\
    \        edge = node;\n        release(old);\n    }\n\n    void discard_unreferenced()\
    \ {\n        while (!_unowned.empty()) {\n            int node = _unowned.back();\n\
    \            _unowned.pop_back();\n            if (_nodes[node].has_value() &&\
    \ _references[node] == 0) release_zero(node);\n        }\n    }\n\n    void reserve(std::size_t)\
    \ {}\n\n    int next_index() const { return _first_free == -1 ? int(_nodes.size())\
    \ : _first_free; }\n\n    std::size_t size() const { return _live_nodes; }\n};\n\
    \n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\n\n#line\
    \ 12 \"ds/dsu/persistent_dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\nstruct\
    \ PersistentDsu {\n   private:\n    struct Node {\n        int val;\n        int\
    \ l, r;\n\n        Node() : val(0), l(0), r(0) {}\n        explicit Node(int value)\
    \ : val(value), l(0), r(0) {}\n        Node(int value, int left, int right) :\
    \ val(value), l(left), r(right) {}\n    };\n\n    int _n;\n    int _root;\n  \
    \  using Pool = detail::PersistentBinaryNodePool<Node, 0>;\n\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    explicit PersistentDsu(int n, int root, std::shared_ptr<Pool>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {\n        _pool->retain(_root);\n\
    \    }\n\n    int new_node(const Node& node) const {\n        return _pool->emplace(node);\n\
    \    }\n\n    int new_node(Node&& node) const {\n        return _pool->emplace(std::move(node));\n\
    \    }\n\n    int build(int l, int r) const {\n        if (l == r) return 0;\n\
    \        if (r - l == 1) return new_node(Node(-1));\n        int m = (l + r) >>\
    \ 1;\n        int left = build(l, m);\n        int right = build(m, r);\n    \
    \    return new_node(Node(0, left, right));\n    }\n\n    int set_node(int t,\
    \ int l, int r, int p, int value, bool copy_on_write = false) const {\n      \
    \  if (copy_on_write) t = _pool->clone_if_shared(t);\n        if (r - l == 1)\
    \ {\n            if (copy_on_write) {\n                (*_pool)[t].val = value;\n\
    \                return t;\n            }\n            return new_node(Node(value));\n\
    \        }\n        int m = (l + r) >> 1;\n        int left = (*_pool)[t].l;\n\
    \        int right = (*_pool)[t].r;\n        if (p < m) {\n            left =\
    \ set_node(left, l, m, p, value, copy_on_write);\n        } else {\n         \
    \   right = set_node(right, m, r, p, value, copy_on_write);\n        }\n     \
    \   if (copy_on_write) {\n            _pool->replace((*_pool)[t].l, left);\n \
    \           _pool->replace((*_pool)[t].r, right);\n            return t;\n   \
    \     }\n        return new_node(Node(0, left, right));\n    }\n\n    PersistentDsu\
    \ make_version(int root) const {\n        PersistentDsu result(_n, root, _pool);\n\
    \        _pool->discard_unreferenced();\n        return result;\n    }\n\n   \
    \ int get_node(int t, int l, int r, int p) const {\n        while (r - l > 1)\
    \ {\n            int m = (l + r) >> 1;\n            if (p < m) {\n           \
    \     t = (*_pool)[t].l;\n                r = m;\n            } else {\n     \
    \           t = (*_pool)[t].r;\n                l = m;\n            }\n      \
    \  }\n        return (*_pool)[t].val;\n    }\n\n   public:\n    PersistentDsu()\
    \ : PersistentDsu(0) {}\n\n    explicit PersistentDsu(int n) : _n(n), _root(0),\
    \ _pool(std::make_shared<Pool>()) {\n        assert(0 <= n);\n        _pool->reserve(n\
    \ * 2 + 1);\n        if (_n > 0) _root = build(0, _n);\n        _pool->retain(_root);\n\
    \        _pool->discard_unreferenced();\n    }\n\n    PersistentDsu(const PersistentDsu&\
    \ other) : _n(other._n), _root(other._root), _pool(other._pool) {\n        if\
    \ (_pool) _pool->retain(_root);\n    }\n\n    PersistentDsu(PersistentDsu&& other)\
    \ noexcept\n        : _n(other._n), _root(other._root), _pool(std::move(other._pool))\
    \ {\n        other._n = 0;\n        other._root = 0;\n    }\n\n    PersistentDsu&\
    \ operator=(const PersistentDsu& other) {\n        if (this == &other) return\
    \ *this;\n        if (other._pool) other._pool->retain(other._root);\n       \
    \ if (_pool) _pool->release(_root);\n        _n = other._n;\n        _root = other._root;\n\
    \        _pool = other._pool;\n        return *this;\n    }\n\n    PersistentDsu&\
    \ operator=(PersistentDsu&& other) noexcept {\n        if (this == &other) return\
    \ *this;\n        if (_pool) _pool->release(_root);\n        _n = other._n;\n\
    \        _root = other._root;\n        _pool = std::move(other._pool);\n     \
    \   other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\n\
    \    ~PersistentDsu() {\n        if (_pool) _pool->release(_root);\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    void release() {\n        if (_pool) _pool->release(_root);\n\
    \        _n = 0;\n        _root = 0;\n        _pool = std::make_shared<Pool>();\n\
    \    }\n\n    std::size_t node_count() const { return _pool ? _pool->size() :\
    \ 0; }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       int x = a;\n        int p = get(x);\n        while (p >= 0) {\n      \
    \      x = p;\n            p = get(x);\n        }\n        return x;\n    }\n\n\
    \    bool same(int a, int b) const {\n        assert(0 <= a && a < _n);\n    \
    \    assert(0 <= b && b < _n);\n        return leader(a) == leader(b);\n    }\n\
    \n    int group_size(int a) const {\n        assert(0 <= a && a < _n);\n     \
    \   return -get(leader(a));\n    }\n\n    int size(int a) const {\n        return\
    \ group_size(a);\n    }\n\n    int get(int p) const {\n        assert(0 <= p &&\
    \ p < _n);\n        return get_node(_root, 0, _n, p);\n    }\n\n    PersistentDsu\
    \ merge(int a, int b) const {\n        assert(0 <= a && a < _n);\n        assert(0\
    \ <= b && b < _n);\n        int x = leader(a), y = leader(b);\n        if (x ==\
    \ y) return *this;\n        int sx = -get(x), sy = -get(y);\n        if (sx <\
    \ sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n      \
    \  }\n        int root = set_node(_root, 0, _n, x, -(sx + sy));\n        root\
    \ = set_node(root, 0, _n, y, x);\n        return make_version(root);\n    }\n\n\
    \    bool merge_inplace(int a, int b) {\n        assert(0 <= a && a < _n);\n \
    \       assert(0 <= b && b < _n);\n        int x = leader(a), y = leader(b);\n\
    \        if (x == y) return false;\n        int sx = -get(x), sy = -get(y);\n\
    \        if (sx < sy) {\n            std::swap(x, y);\n            std::swap(sx,\
    \ sy);\n        }\n        int root = set_node(_root, 0, _n, x, -(sx + sy), true);\n\
    \        _pool->replace(_root, root);\n        root = set_node(_root, 0, _n, y,\
    \ x, true);\n        _pool->replace(_root, root);\n        _pool->discard_unreferenced();\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups() const\
    \ {\n        std::vector<int> leader_buf(_n), group_size(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"ds/dsu/persistent_potentialized_dsu.hpp\"\
    \n\n\n\n#line 6 \"ds/dsu/persistent_potentialized_dsu.hpp\"\n#include <concepts>\n\
    #line 11 \"ds/dsu/persistent_potentialized_dsu.hpp\"\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for groups.\
    \ A type satisfying this concept must also obey the group\n// laws; concepts can\
    \ check the interface but not the algebraic properties.\ntemplate <typename M>\n\
    concept IsGroup = IsMonoid<M> && requires(typename M::value_type a) {\n    { M::inv(a)\
    \ } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ groups. Commutativity is a semantic requirement and\n// cannot be checked by\
    \ a C++ concept.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\
    \n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 14 \"ds/dsu/persistent_potentialized_dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsGroup Group>\n\
    \    requires std::equality_comparable<typename Group::value_type>\nstruct PersistentPotentializedDsu\
    \ {\n    using T = typename Group::value_type;\n\n    struct Value {\n       \
    \ int parent_or_size;\n        T diff_to_parent;\n\n        Value() : parent_or_size(0),\
    \ diff_to_parent(Group::id()) {}\n        Value(int parent_or_size_, const T&\
    \ diff_to_parent_)\n            : parent_or_size(parent_or_size_), diff_to_parent(diff_to_parent_)\
    \ {}\n        Value(int parent_or_size_, T&& diff_to_parent_)\n            : parent_or_size(parent_or_size_),\
    \ diff_to_parent(std::move(diff_to_parent_)) {}\n    };\n\n   private:\n    struct\
    \ Node {\n        Value val;\n        int l, r;\n\n        Node() : val(), l(0),\
    \ r(0) {}\n        explicit Node(const Value& value) : val(value), l(0), r(0)\
    \ {}\n        explicit Node(Value&& value) : val(std::move(value)), l(0), r(0)\
    \ {}\n        Node(const Value& value, int left, int right) : val(value), l(left),\
    \ r(right) {}\n        Node(Value&& value, int left, int right) : val(std::move(value)),\
    \ l(left), r(right) {}\n    };\n\n    int _n;\n    int _root;\n    using Pool\
    \ = detail::PersistentBinaryNodePool<Node, 0>;\n\n    std::shared_ptr<Pool> _pool;\n\
    \n    explicit PersistentPotentializedDsu(int n, int root, std::shared_ptr<Pool>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {\n        _pool->retain(_root);\n\
    \    }\n\n    int new_node(const Node& node) const {\n        return _pool->emplace(node);\n\
    \    }\n\n    int new_node(Node&& node) const {\n        return _pool->emplace(std::move(node));\n\
    \    }\n\n    int build(int l, int r) const {\n        if (l == r) return 0;\n\
    \        if (r - l == 1) return new_node(Node(Value(-1, Group::id())));\n    \
    \    int m = (l + r) >> 1;\n        int left = build(l, m);\n        int right\
    \ = build(m, r);\n        return new_node(Node(Value(), left, right));\n    }\n\
    \n    int set_node(int t, int l, int r, int p, Value value, bool copy_on_write\
    \ = false) const {\n        if (copy_on_write) t = _pool->clone_if_shared(t);\n\
    \        if (r - l == 1) {\n            if (copy_on_write) {\n               \
    \ (*_pool)[t].val = std::move(value);\n                return t;\n           \
    \ }\n            return new_node(Node(std::move(value)));\n        }\n       \
    \ int m = (l + r) >> 1;\n        int left = (*_pool)[t].l;\n        int right\
    \ = (*_pool)[t].r;\n        if (p < m) {\n            left = set_node(left, l,\
    \ m, p, std::move(value), copy_on_write);\n        } else {\n            right\
    \ = set_node(right, m, r, p, std::move(value), copy_on_write);\n        }\n  \
    \      if (copy_on_write) {\n            _pool->replace((*_pool)[t].l, left);\n\
    \            _pool->replace((*_pool)[t].r, right);\n            return t;\n  \
    \      }\n        return new_node(Node(Value(), left, right));\n    }\n\n    Value\
    \ get_value(int t, int l, int r, int p) const {\n        while (r - l > 1) {\n\
    \            int m = (l + r) >> 1;\n            if (p < m) {\n               \
    \ t = (*_pool)[t].l;\n                r = m;\n            } else {\n         \
    \       t = (*_pool)[t].r;\n                l = m;\n            }\n        }\n\
    \        return (*_pool)[t].val;\n    }\n\n    std::pair<int, T> leader_and_potential(int\
    \ a) const {\n        T res = Group::id();\n        while (true) {\n         \
    \   Value cur = get(a);\n            if (cur.parent_or_size < 0) return {a, res};\n\
    \            res = Group::op(cur.diff_to_parent, res);\n            a = cur.parent_or_size;\n\
    \        }\n    }\n\n    PersistentPotentializedDsu make_version(int root) const\
    \ {\n        PersistentPotentializedDsu result(_n, root, _pool);\n        _pool->discard_unreferenced();\n\
    \        return result;\n    }\n\n   public:\n    PersistentPotentializedDsu()\
    \ : PersistentPotentializedDsu(0) {}\n\n    explicit PersistentPotentializedDsu(int\
    \ n) : _n(n), _root(0), _pool(std::make_shared<Pool>()) {\n        assert(0 <=\
    \ n);\n        _pool->reserve(n * 4 + 1);\n        if (_n > 0) _root = build(0,\
    \ _n);\n        _pool->retain(_root);\n        _pool->discard_unreferenced();\n\
    \    }\n\n    PersistentPotentializedDsu(const PersistentPotentializedDsu& other)\n\
    \        : _n(other._n), _root(other._root), _pool(other._pool) {\n        if\
    \ (_pool) _pool->retain(_root);\n    }\n\n    PersistentPotentializedDsu(PersistentPotentializedDsu&&\
    \ other) noexcept\n        : _n(other._n), _root(other._root), _pool(std::move(other._pool))\
    \ {\n        other._n = 0;\n        other._root = 0;\n    }\n\n    PersistentPotentializedDsu&\
    \ operator=(const PersistentPotentializedDsu& other) {\n        if (this == &other)\
    \ return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _n = other._n;\n        _root\
    \ = other._root;\n        _pool = other._pool;\n        return *this;\n    }\n\
    \n    PersistentPotentializedDsu& operator=(PersistentPotentializedDsu&& other)\
    \ noexcept {\n        if (this == &other) return *this;\n        if (_pool) _pool->release(_root);\n\
    \        _n = other._n;\n        _root = other._root;\n        _pool = std::move(other._pool);\n\
    \        other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\
    \n    ~PersistentPotentializedDsu() {\n        if (_pool) _pool->release(_root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    void release() {\n        if\
    \ (_pool) _pool->release(_root);\n        _n = 0;\n        _root = 0;\n      \
    \  _pool = std::make_shared<Pool>();\n    }\n\n    std::size_t node_count() const\
    \ { return _pool ? _pool->size() : 0; }\n\n    int leader(int a) const {\n   \
    \     assert(0 <= a && a < _n);\n        return leader_and_potential(a).first;\n\
    \    }\n\n    bool same(int a, int b) const {\n        assert(0 <= a && a < _n);\n\
    \        assert(0 <= b && b < _n);\n        return leader(a) == leader(b);\n \
    \   }\n\n    int group_size(int a) const {\n        assert(0 <= a && a < _n);\n\
    \        return -get(leader(a)).parent_or_size;\n    }\n\n    int size(int a)\
    \ const {\n        return group_size(a);\n    }\n\n    T potential(int a) const\
    \ {\n        assert(0 <= a && a < _n);\n        return leader_and_potential(a).second;\n\
    \    }\n\n    T diff(int a, int b) const {\n        assert(same(a, b));\n    \
    \    return Group::op(Group::inv(potential(a)), potential(b));\n    }\n\n    Value\
    \ get(int p) const {\n        assert(0 <= p && p < _n);\n        return get_value(_root,\
    \ 0, _n, p);\n    }\n\n    int parent_or_size(int p) const {\n        return get(p).parent_or_size;\n\
    \    }\n\n    std::pair<PersistentPotentializedDsu, bool> merge(int a, int b,\
    \ const T& w) const {\n        assert(0 <= a && a < _n);\n        assert(0 <=\
    \ b && b < _n);\n        auto [x, pa] = leader_and_potential(a);\n        auto\
    \ [y, pb] = leader_and_potential(b);\n        if (x == y) return {*this, Group::op(Group::inv(pa),\
    \ pb) == w};\n\n        int sx = -get(x).parent_or_size;\n        int sy = -get(y).parent_or_size;\n\
    \        T y_from_x = Group::op(Group::op(pa, w), Group::inv(pb));\n        if\
    \ (sx < sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n\
    \            y_from_x = Group::inv(y_from_x);\n        }\n        int root = set_node(_root,\
    \ 0, _n, x, Value(-(sx + sy), Group::id()));\n        root = set_node(root, 0,\
    \ _n, y, Value(x, std::move(y_from_x)));\n        return {make_version(root),\
    \ true};\n    }\n\n    bool merge_inplace(int a, int b, const T& w) {\n      \
    \  assert(0 <= a && a < _n);\n        assert(0 <= b && b < _n);\n        auto\
    \ [x, pa] = leader_and_potential(a);\n        auto [y, pb] = leader_and_potential(b);\n\
    \        if (x == y) return Group::op(Group::inv(pa), pb) == w;\n\n        int\
    \ sx = -get(x).parent_or_size;\n        int sy = -get(y).parent_or_size;\n   \
    \     T y_from_x = Group::op(Group::op(pa, w), Group::inv(pb));\n        if (sx\
    \ < sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n    \
    \        y_from_x = Group::inv(y_from_x);\n        }\n        int root = set_node(_root,\
    \ 0, _n, x, Value(-(sx + sy), Group::id()), true);\n        _pool->replace(_root,\
    \ root);\n        root = set_node(_root, 0, _n, y, Value(x, std::move(y_from_x)),\
    \ true);\n        _pool->replace(_root, root);\n        _pool->discard_unreferenced();\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups() const\
    \ {\n        std::vector<int> leader_buf(_n), group_size(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"ds/bst/persistent_ordered_multiset.hpp\"\n\
    \n\n\n#line 6 \"ds/bst/persistent_ordered_multiset.hpp\"\n#include <functional>\n\
    #include <initializer_list>\n#line 10 \"ds/bst/persistent_ordered_multiset.hpp\"\
    \n\n#line 12 \"ds/bst/persistent_ordered_multiset.hpp\"\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <typename T, typename Compare>\nstruct PersistentOrderedSet;\n\
    \ntemplate <typename T, typename Compare = std::less<T>>\nstruct PersistentOrderedMultiset\
    \ {\n   private:\n    friend struct PersistentOrderedSet<T, Compare>;\n    struct\
    \ Node {\n        T key;\n        int count;\n        int size;\n        int distinct_size;\n\
    \        int rank_color;\n        int l;\n        int r;\n        int min_leaf;\n\
    \        int max_leaf;\n\n        Node(T value, int multiplicity, int maximum)\n\
    \            : key(std::move(value)),\n              count(multiplicity),\n  \
    \            size(multiplicity),\n              distinct_size(1),\n          \
    \    rank_color(1),\n              l(-1),\n              r(-1),\n            \
    \  min_leaf(maximum),\n              max_leaf(maximum) {}\n\n        Node(T separator,\
    \ int subtree_size, int left_size, int unique_count, int node_rank,\n        \
    \     int left, int right, int minimum, int maximum, bool is_black)\n        \
    \    : key(std::move(separator)),\n              count(left_size),\n         \
    \     size(subtree_size),\n              distinct_size(unique_count),\n      \
    \        rank_color(node_rank * 2 + int(is_black)),\n              l(left),\n\
    \              r(right),\n              min_leaf(minimum),\n              max_leaf(maximum)\
    \ {}\n    };\n\n    using Pool = detail::PersistentBinaryNodePool<Node>;\n\n \
    \   inline static Pool pool;\n\n    int root;\n    Compare comp;\n\n    static\
    \ int subtree_size(int t) { return t == -1 ? 0 : pool[t].size; }\n    static int\
    \ subtree_distinct_size(int t) { return t == -1 ? 0 : pool[t].distinct_size; }\n\
    \    static int node_rank(int t) { return pool[t].rank_color >> 1; }\n    static\
    \ bool is_black(int t) { return (pool[t].rank_color & 1) != 0; }\n    static bool\
    \ is_leaf(int t) { return pool[t].l == -1; }\n\n    bool equal(const T& a, const\
    \ T& b) const {\n        return !comp(a, b) && !comp(b, a);\n    }\n\n    static\
    \ int make_leaf(T key, int count) {\n        const int id = pool.next_index();\n\
    \        return pool.emplace(std::move(key), count, id);\n    }\n\n    static\
    \ int make_node(int l, int r, bool black) {\n        assert(l != -1 && r != -1);\n\
    \        const int rank = node_rank(l) + int(is_black(l));\n        assert(rank\
    \ == node_rank(r) + int(is_black(r)));\n        return pool.emplace(pool[pool[l].max_leaf].key,\n\
    \                            subtree_size(l) + subtree_size(r),\n            \
    \                subtree_size(l),\n                            subtree_distinct_size(l)\
    \ + subtree_distinct_size(r),\n                            rank, l, r, pool[l].min_leaf,\
    \ pool[r].max_leaf,\n                            black);\n    }\n\n    static\
    \ int as_root(int t) {\n        if (t == -1 || is_black(t)) return t;\n      \
    \  return make_node(pool[t].l, pool[t].r, true);\n    }\n\n    static int merge_sub(int\
    \ a, int b) {\n        assert(a != -1 && b != -1);\n        if (node_rank(a) <\
    \ node_rank(b)) {\n            const Node& right = pool[b];\n            int c\
    \ = merge_sub(a, right.l);\n            if (is_black(b) && !is_black(c) && !is_black(pool[c].l))\
    \ {\n                const Node& middle = pool[c];\n                if (is_black(right.r))\
    \ {\n                    return make_node(middle.l,\n                        \
    \             make_node(middle.r, right.r, false),\n                         \
    \            true);\n                }\n                const Node& far = pool[right.r];\n\
    \                return make_node(make_node(middle.l, middle.r, true),\n     \
    \                            make_node(far.l, far.r, true),\n                \
    \                 false);\n            }\n            return make_node(c, right.r,\
    \ is_black(b));\n        }\n        if (node_rank(a) > node_rank(b)) {\n     \
    \       const Node& left = pool[a];\n            int c = merge_sub(left.r, b);\n\
    \            if (is_black(a) && !is_black(c) && !is_black(pool[c].r)) {\n    \
    \            const Node& middle = pool[c];\n                if (is_black(left.l))\
    \ {\n                    return make_node(make_node(left.l, middle.l, false),\n\
    \                                     middle.r, true);\n                }\n  \
    \              const Node& far = pool[left.l];\n                return make_node(make_node(far.l,\
    \ far.r, true),\n                                 make_node(middle.l, middle.r,\
    \ true),\n                                 false);\n            }\n          \
    \  return make_node(left.l, c, is_black(a));\n        }\n        return make_node(a,\
    \ b, false);\n    }\n\n    static int merge_nodes(int a, int b) {\n        if\
    \ (a == -1 || b == -1) return a == -1 ? b : a;\n        return as_root(merge_sub(as_root(a),\
    \ as_root(b)));\n    }\n\n    std::pair<int, int> split_nodes(int t, const T&\
    \ key) const {\n        if (t == -1) return {-1, -1};\n        const Node& node\
    \ = pool[t];\n        if (is_leaf(t)) return comp(node.key, key) ? std::pair{t,\
    \ -1} : std::pair{-1, t};\n        if (comp(node.key, key)) {\n            auto\
    \ [l, r] = split_nodes(node.r, key);\n            return {merge_nodes(as_root(node.l),\
    \ l), r};\n        }\n        auto [l, r] = split_nodes(node.l, key);\n      \
    \  return {l, merge_nodes(r, as_root(node.r))};\n    }\n\n    int change_count_impl(int\
    \ t, const T& key, int delta, int& old_count) const {\n        if (t == -1) return\
    \ -1;\n        const Node& node = pool[t];\n        if (is_leaf(t)) {\n      \
    \      if (!equal(node.key, key)) return t;\n            old_count = node.count;\n\
    \            return node.count + delta == 0 ? t : make_leaf(node.key, node.count\
    \ + delta);\n        }\n        int child;\n        if (!comp(node.key, key))\
    \ {\n            child = change_count_impl(node.l, key, delta, old_count);\n \
    \           if (old_count == 0 || old_count + delta == 0) return t;\n        \
    \    return make_node(child, node.r, is_black(t));\n        }\n        child =\
    \ change_count_impl(node.r, key, delta, old_count);\n        if (old_count ==\
    \ 0 || old_count + delta == 0) return t;\n        return make_node(node.l, child,\
    \ is_black(t));\n    }\n\n    int change_count_inplace(int t, const T& key, int\
    \ delta) const {\n        t = pool.clone_if_shared(t);\n        if (is_leaf(t))\
    \ {\n            assert(equal(pool[t].key, key));\n            assert(pool[t].count\
    \ + delta > 0);\n            pool[t].count += delta;\n            pool[t].size\
    \ += delta;\n            return t;\n        }\n        if (!comp(pool[t].key,\
    \ key)) {\n            int child = change_count_inplace(pool[t].l, key, delta);\n\
    \            pool.replace(pool[t].l, child);\n        } else {\n            int\
    \ child = change_count_inplace(pool[t].r, key, delta);\n            pool.replace(pool[t].r,\
    \ child);\n        }\n        Node& node = pool[t];\n        node.count = subtree_size(node.l);\n\
    \        node.size = node.count + subtree_size(node.r);\n        return t;\n \
    \   }\n\n    int count_impl(int t, const T& key) const {\n        if (t == -1)\
    \ return 0;\n        while (!is_leaf(t)) {\n            t = !comp(pool[t].key,\
    \ key) ? pool[t].l : pool[t].r;\n        }\n        return equal(pool[t].key,\
    \ key) ? pool[t].count : 0;\n    }\n\n    const T* kth_impl(int t, int k) const\
    \ {\n        while (!is_leaf(t)) {\n            const int left_size = pool[t].count;\n\
    \            if (k < left_size) {\n                t = pool[t].l;\n          \
    \  } else {\n                k -= left_size;\n                t = pool[t].r;\n\
    \            }\n        }\n        return &pool[t].key;\n    }\n\n    int order_of_key_impl(int\
    \ t, const T& key, bool upper) const {\n        int result = 0;\n        while\
    \ (t != -1 && !is_leaf(t)) {\n            const Node& node = pool[t];\n      \
    \      const T& separator = node.key;\n            const bool take_left = upper\
    \ ? !comp(key, separator) : comp(separator, key);\n            if (take_left)\
    \ {\n                result += node.count;\n                t = node.r;\n    \
    \        } else {\n                t = node.l;\n            }\n        }\n   \
    \     if (t != -1) {\n            const bool take_leaf = upper ? !comp(key, pool[t].key)\
    \ : comp(pool[t].key, key);\n            if (take_leaf) result += pool[t].count;\n\
    \        }\n        return result;\n    }\n\n    const T* lower_bound_impl(int\
    \ t, const T& key, bool strict) const {\n        const T* result = nullptr;\n\
    \        while (t != -1) {\n            const Node& node = pool[t];\n        \
    \    if (is_leaf(t)) {\n                const bool candidate = strict ? comp(key,\
    \ node.key) : !comp(node.key, key);\n                return candidate ? &node.key\
    \ : result;\n            }\n            const T& separator = node.key;\n     \
    \       const bool go_left = strict ? comp(key, separator) : !comp(separator,\
    \ key);\n            if (go_left) {\n                result = &pool[pool[node.r].min_leaf].key;\n\
    \                t = node.l;\n            } else {\n                t = node.r;\n\
    \            }\n        }\n        return result;\n    }\n\n    const T* max_less_impl(int\
    \ t, const T& key, bool strict) const {\n        const T* result = nullptr;\n\
    \        while (t != -1) {\n            const Node& node = pool[t];\n        \
    \    if (is_leaf(t)) {\n                const bool candidate = strict ? comp(node.key,\
    \ key) : !comp(key, node.key);\n                return candidate ? &node.key :\
    \ result;\n            }\n            const T& separator = node.key;\n       \
    \     const bool take_left = strict ? comp(separator, key) : !comp(key, separator);\n\
    \            if (take_left) {\n                result = &separator;\n        \
    \        t = node.r;\n            } else {\n                t = node.l;\n    \
    \        }\n        }\n        return result;\n    }\n\n    static void dump_impl(int\
    \ t, std::vector<T>& result) {\n        if (t == -1) return;\n        const Node&\
    \ node = pool[t];\n        if (is_leaf(t)) {\n            for (int i = 0; i <\
    \ node.count; ++i) result.push_back(node.key);\n            return;\n        }\n\
    \        dump_impl(node.l, result);\n        dump_impl(node.r, result);\n    }\n\
    \n    static std::pair<int, int> pop_min(int t) {\n        assert(t != -1);\n\
    \        const Node& node = pool[t];\n        if (is_leaf(t)) return {t, -1};\n\
    \        auto [minimum, rest] = pop_min(node.l);\n        return {minimum, merge_nodes(rest,\
    \ as_root(node.r))};\n    }\n\n    PersistentOrderedMultiset(int node, Compare\
    \ compare) : root(node), comp(std::move(compare)) {\n        pool.retain(root);\n\
    \    }\n\n    PersistentOrderedMultiset make_version(int node) const {\n     \
    \   PersistentOrderedMultiset result(node, comp);\n        pool.discard_unreferenced();\n\
    \        return result;\n    }\n\n   public:\n    explicit PersistentOrderedMultiset(Compare\
    \ compare) : root(-1), comp(std::move(compare)) {}\n    PersistentOrderedMultiset()\
    \ : PersistentOrderedMultiset(Compare()) {}\n\n    PersistentOrderedMultiset(std::initializer_list<T>\
    \ init, Compare compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        for (const T& x : init) *this = insert(x);\n    }\n\n    template\
    \ <typename Iterator>\n    PersistentOrderedMultiset(Iterator first, Iterator\
    \ last, Compare compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        while (first != last) *this = insert(*first++);\n    }\n\n    PersistentOrderedMultiset(const\
    \ PersistentOrderedMultiset& other)\n        : root(other.root), comp(other.comp)\
    \ {\n        pool.retain(root);\n    }\n\n    PersistentOrderedMultiset(PersistentOrderedMultiset&&\
    \ other)\n        : root(other.root), comp(std::move(other.comp)) {\n        other.root\
    \ = -1;\n    }\n\n    PersistentOrderedMultiset& operator=(const PersistentOrderedMultiset&\
    \ other) {\n        if (this == &other) return *this;\n        pool.retain(other.root);\n\
    \        pool.release(root);\n        root = other.root;\n        comp = other.comp;\n\
    \        return *this;\n    }\n\n    PersistentOrderedMultiset& operator=(PersistentOrderedMultiset&&\
    \ other) {\n        if (this == &other) return *this;\n        pool.release(root);\n\
    \        root = other.root;\n        comp = std::move(other.comp);\n        other.root\
    \ = -1;\n        return *this;\n    }\n\n    ~PersistentOrderedMultiset() { pool.release(root);\
    \ }\n\n    int size() const { return subtree_size(root); }\n    int unique_size()\
    \ const { return subtree_distinct_size(root); }\n    bool empty() const { return\
    \ root == -1; }\n    void release() { pool.release(std::exchange(root, -1)); }\n\
    \    std::size_t node_count() const { return pool.size(); }\n    PersistentOrderedMultiset\
    \ clear() const { return make_version(-1); }\n\n    PersistentOrderedMultiset\
    \ insert(T key, int multiplicity = 1) const {\n        assert(multiplicity > 0);\n\
    \        int old_count = 0;\n        const int changed_root = change_count_impl(root,\
    \ key, multiplicity, old_count);\n        if (old_count != 0) {\n            return\
    \ make_version(changed_root);\n        }\n        auto [l, r] = split_nodes(root,\
    \ key);\n        return make_version(merge_nodes(merge_nodes(l, make_leaf(std::move(key),\
    \ multiplicity)), r));\n    }\n\n    void insert_inplace(T key, int multiplicity\
    \ = 1) {\n        assert(multiplicity > 0);\n        if (!contains(key)) {\n \
    \           *this = insert(std::move(key), multiplicity);\n            return;\n\
    \        }\n        int next_root = change_count_inplace(root, key, multiplicity);\n\
    \        pool.replace(root, next_root);\n        pool.discard_unreferenced();\n\
    \    }\n\n   private:\n    PersistentOrderedMultiset insert_unique(T key) const\
    \ {\n        if (contains(key)) return *this;\n        auto [l, r] = split_nodes(root,\
    \ key);\n        return make_version(merge_nodes(merge_nodes(l, make_leaf(std::move(key),\
    \ 1)), r));\n    }\n\n   public:\n    PersistentOrderedMultiset erase_one(const\
    \ T& key) const {\n        int old_count = 0;\n        const int changed_root\
    \ = change_count_impl(root, key, -1, old_count);\n        if (old_count == 0)\
    \ return *this;\n        if (old_count > 1) return make_version(changed_root);\n\
    \        auto [l, r] = split_nodes(root, key);\n        auto [discarded, rest]\
    \ = pop_min(r);\n        assert(equal(pool[discarded].key, key));\n        return\
    \ make_version(merge_nodes(l, rest));\n    }\n\n    PersistentOrderedMultiset\
    \ erase(const T& key) const { return erase_one(key); }\n\n    bool erase_one_inplace(const\
    \ T& key) {\n        int old_count = count(key);\n        if (old_count == 0)\
    \ return false;\n        if (old_count == 1) {\n            *this = erase_one(key);\n\
    \            return true;\n        }\n        int next_root = change_count_inplace(root,\
    \ key, -1);\n        pool.replace(root, next_root);\n        pool.discard_unreferenced();\n\
    \        return true;\n    }\n\n    bool erase_inplace(const T& key) { return\
    \ erase_one_inplace(key); }\n\n    PersistentOrderedMultiset erase_all(const T&\
    \ key) const {\n        const int old_count = count(key);\n        if (old_count\
    \ == 0) return *this;\n        auto [l, r] = split_nodes(root, key);\n       \
    \ auto [discarded, rest] = pop_min(r);\n        assert(equal(pool[discarded].key,\
    \ key));\n        return make_version(merge_nodes(l, rest));\n    }\n\n    bool\
    \ erase_all_inplace(const T& key) {\n        if (!contains(key)) return false;\n\
    \        *this = erase_all(key);\n        return true;\n    }\n\n    bool contains(const\
    \ T& key) const { return count(key) > 0; }\n    int count(const T& key) const\
    \ { return count_impl(root, key); }\n\n    const T* find_by_order(int k) const\
    \ {\n        assert(0 <= k && k < size());\n        return kth_impl(root, k);\n\
    \    }\n\n    T kth(int k) const { return *find_by_order(k); }\n    int order_of_key(const\
    \ T& key) const { return order_of_key_impl(root, key, false); }\n    int count_less(const\
    \ T& key) const { return order_of_key(key); }\n    int count_less_equal(const\
    \ T& key) const { return order_of_key_impl(root, key, true); }\n    int count_greater(const\
    \ T& key) const { return size() - count_less_equal(key); }\n    int count_greater_equal(const\
    \ T& key) const { return size() - count_less(key); }\n    const T* lower_bound(const\
    \ T& key) const { return lower_bound_impl(root, key, false); }\n    const T* upper_bound(const\
    \ T& key) const { return lower_bound_impl(root, key, true); }\n    const T* min_ge(const\
    \ T& key) const { return lower_bound(key); }\n    const T* min_gt(const T& key)\
    \ const { return upper_bound(key); }\n    const T* max_le(const T& key) const\
    \ { return max_less_impl(root, key, false); }\n    const T* max_lt(const T& key)\
    \ const { return max_less_impl(root, key, true); }\n    const T* min() const {\
    \ return empty() ? nullptr : &pool[pool[root].min_leaf].key; }\n    const T* max()\
    \ const { return empty() ? nullptr : &pool[pool[root].max_leaf].key; }\n\n   \
    \ std::pair<PersistentOrderedMultiset, PersistentOrderedMultiset> split(const\
    \ T& key) const {\n        auto [l, r] = split_nodes(root, key);\n        PersistentOrderedMultiset\
    \ left(l, comp);\n        PersistentOrderedMultiset right(r, comp);\n        pool.discard_unreferenced();\n\
    \        return {std::move(left), std::move(right)};\n    }\n\n    PersistentOrderedMultiset\
    \ merge(const PersistentOrderedMultiset& other) const {\n        assert(empty()\
    \ || other.empty() || comp(*max(), *other.min()));\n        return make_version(merge_nodes(root,\
    \ other.root));\n    }\n\n    std::vector<T> to_vector() const {\n        std::vector<T>\
    \ result;\n        result.reserve(size());\n        dump_impl(root, result);\n\
    \        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\n\n\n\n#line 5 \"\
    ds/dynamic_array/persistent_dynamic_array.hpp\"\n#include <chrono>\n#line 7 \"\
    ds/dynamic_array/persistent_dynamic_array.hpp\"\n#include <cstdint>\n#line 13\
    \ \"ds/dynamic_array/persistent_dynamic_array.hpp\"\n\n#line 15 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct PersistentDynamicArray\
    \ {\n   private:\n    struct Node {\n        T val;\n        int priority;\n \
    \       int count;\n        int l, r;\n        bool rev;\n\n        Node(T value,\
    \ int node_priority, int node_count, int left, int right, bool reversed)\n   \
    \         : val(std::move(value)),\n              priority(node_priority),\n \
    \             count(node_count),\n              l(left),\n              r(right),\n\
    \              rev(reversed) {}\n    };\n\n    struct BuildNode {\n        T val;\n\
    \        int priority;\n        int l, r;\n\n        BuildNode(T value, int node_priority)\
    \ : val(std::move(value)), priority(node_priority), l(-1), r(-1) {}\n    };\n\n\
    \    int root;\n    std::uint32_t rng_state;\n    using Pool = detail::PersistentBinaryNodePool<Node>;\n\
    \n    std::shared_ptr<Pool> pool;\n\n    int subtree_size(int t) const {\n   \
    \     return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    static std::uint32_t\
    \ next_state(std::uint32_t state) {\n        state ^= state << 13;\n        state\
    \ ^= state >> 17;\n        state ^= state << 5;\n        return state == 0 ? 1\
    \ : state;\n    }\n\n    static int next_priority(std::uint32_t& state) {\n  \
    \      state = next_state(state);\n        return int(state);\n    }\n\n    int\
    \ make_node(T val, int priority, bool rev, int l, int r) const {\n        int\
    \ count = 1 + subtree_size(l) + subtree_size(r);\n        return pool->emplace(std::move(val),\
    \ priority, count, l, r, rev);\n    }\n\n    int reversed_node(int t) const {\n\
    \        if (t == -1) return -1;\n        const Node& node = (*pool)[t];\n   \
    \     return make_node(node.val, node.priority, !node.rev, node.l, node.r);\n\
    \    }\n\n    int push(int t) const {\n        if (t == -1 || !(*pool)[t].rev)\
    \ return t;\n        Node node = (*pool)[t];\n        int l = reversed_node(node.r);\n\
    \        int r = reversed_node(node.l);\n        return make_node(std::move(node.val),\
    \ node.priority, false, l, r);\n    }\n\n    int merge(int l, int r) const {\n\
    \        if (l == -1 || r == -1) return l == -1 ? r : l;\n        if ((*pool)[l].priority\
    \ > (*pool)[r].priority) {\n            Node node = (*pool)[push(l)];\n      \
    \      int right = merge(node.r, r);\n            return make_node(std::move(node.val),\
    \ node.priority, false, node.l, right);\n        }\n        Node node = (*pool)[push(r)];\n\
    \        int left = merge(l, node.l);\n        return make_node(std::move(node.val),\
    \ node.priority, false, left, node.r);\n    }\n\n    std::pair<int, int> split_node(int\
    \ t, int pos) const {\n        if (t == -1) return {-1, -1};\n        Node node\
    \ = (*pool)[push(t)];\n        int left_count = subtree_size(node.l);\n      \
    \  if (pos <= left_count) {\n            auto [a, b] = split_node(node.l, pos);\n\
    \            return {a, make_node(std::move(node.val), node.priority, false, b,\
    \ node.r)};\n        }\n        auto [a, b] = split_node(node.r, pos - left_count\
    \ - 1);\n        return {make_node(std::move(node.val), node.priority, false,\
    \ node.l, a), b};\n    }\n\n    int set_node(int t, int pos, T val) const {\n\
    \        Node node = (*pool)[push(t)];\n        int left_count = subtree_size(node.l);\n\
    \        if (pos < left_count) {\n            int l = set_node(node.l, pos, std::move(val));\n\
    \            return make_node(std::move(node.val), node.priority, false, l, node.r);\n\
    \        }\n        if (pos == left_count) {\n            return make_node(std::move(val),\
    \ node.priority, false, node.l, node.r);\n        }\n        int r = set_node(node.r,\
    \ pos - left_count - 1, std::move(val));\n        return make_node(std::move(node.val),\
    \ node.priority, false, node.l, r);\n    }\n\n    int set_node_inplace(int t,\
    \ int pos, T val, bool inherited_reversed = false) const {\n        t = pool->clone_if_shared(t);\n\
    \        const bool reversed = inherited_reversed ^ (*pool)[t].rev;\n        const\
    \ int logical_left = reversed ? (*pool)[t].r : (*pool)[t].l;\n        const int\
    \ left_count = subtree_size(logical_left);\n        if (pos < left_count) {\n\
    \            int child = set_node_inplace(logical_left, pos, std::move(val), reversed);\n\
    \            if (reversed) {\n                pool->replace((*pool)[t].r, child);\n\
    \            } else {\n                pool->replace((*pool)[t].l, child);\n \
    \           }\n        } else if (pos == left_count) {\n            (*pool)[t].val\
    \ = std::move(val);\n        } else {\n            const int logical_right = reversed\
    \ ? (*pool)[t].l : (*pool)[t].r;\n            int child = set_node_inplace(logical_right,\
    \ pos - left_count - 1, std::move(val), reversed);\n            if (reversed)\
    \ {\n                pool->replace((*pool)[t].l, child);\n            } else {\n\
    \                pool->replace((*pool)[t].r, child);\n            }\n        }\n\
    \        return t;\n    }\n\n    int find_node(int t, int pos) const {\n     \
    \   bool reversed = false;\n        while (t != -1) {\n            const Node&\
    \ node = (*pool)[t];\n            bool cur_reversed = reversed ^ node.rev;\n \
    \           int l = cur_reversed ? node.r : node.l;\n            int r = cur_reversed\
    \ ? node.l : node.r;\n            int left_count = subtree_size(l);\n        \
    \    if (pos < left_count) {\n                t = l;\n                reversed\
    \ = cur_reversed;\n            } else if (pos == left_count) {\n             \
    \   return t;\n            } else {\n                pos -= left_count + 1;\n\
    \                t = r;\n                reversed = cur_reversed;\n          \
    \  }\n        }\n        return -1;\n    }\n\n    void dump_dfs(int t, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (t == -1) return;\n        const\
    \ Node& node = (*pool)[t];\n        bool cur_reversed = reversed ^ node.rev;\n\
    \        int l = cur_reversed ? node.r : node.l;\n        int r = cur_reversed\
    \ ? node.l : node.r;\n        dump_dfs(l, res, cur_reversed);\n        res.push_back(node.val);\n\
    \        dump_dfs(r, res, cur_reversed);\n    }\n\n    void dump_range_dfs(int\
    \ t, int ql, int qr, int offset, std::vector<T>& res, bool reversed = false) const\
    \ {\n        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return;\n\
    \        const Node& node = (*pool)[t];\n        bool cur_reversed = reversed\
    \ ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n        int r\
    \ = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(l, ql, qr,\
    \ offset, res, cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res.push_back(node.val);\n\
    \        dump_range_dfs(r, ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n\
    \    int build_from_nodes(std::vector<BuildNode>& nodes, int t) const {\n    \
    \    if (t == -1) return -1;\n        int l = build_from_nodes(nodes, nodes[t].l);\n\
    \        int r = build_from_nodes(nodes, nodes[t].r);\n        return make_node(std::move(nodes[t].val),\
    \ nodes[t].priority, false, l, r);\n    }\n\n    int build_cartesian(std::vector<BuildNode>&\
    \ nodes) const {\n        if (nodes.empty()) return -1;\n        std::vector<int>\
    \ stack;\n        stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
    \ i++) {\n            int left_child = -1;\n            while (!stack.empty()\
    \ && nodes[stack.back()].priority < nodes[i].priority) {\n                left_child\
    \ = stack.back();\n                stack.pop_back();\n            }\n        \
    \    nodes[i].l = left_child;\n            if (!stack.empty()) nodes[stack.back()].r\
    \ = i;\n            stack.push_back(i);\n        }\n        return build_from_nodes(nodes,\
    \ stack.front());\n    }\n\n    int build_from_vector(const std::vector<T>& v,\
    \ std::uint32_t& state) const {\n        std::vector<BuildNode> nodes;\n     \
    \   nodes.reserve(v.size());\n        for (const T& x : v) nodes.emplace_back(x,\
    \ next_priority(state));\n        return build_cartesian(nodes);\n    }\n\n  \
    \  int build_from_vector(std::vector<T>&& v, std::uint32_t& state) const {\n \
    \       std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n    \
    \    for (T& x : v) nodes.emplace_back(std::move(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_node(node.val, node.priority, node.rev, l, r);\n    }\n\n\
    \    explicit PersistentDynamicArray(int node, std::uint32_t state, std::shared_ptr<Pool>\
    \ node_pool)\n        : root(node), rng_state(state), pool(std::move(node_pool))\
    \ {\n        pool->retain(root);\n    }\n\n    PersistentDynamicArray make_version(int\
    \ node, std::uint32_t state) const {\n        PersistentDynamicArray result(node,\
    \ state, pool);\n        pool->discard_unreferenced();\n        return result;\n\
    \    }\n\n   public:\n    PersistentDynamicArray()\n        : root(-1),\n    \
    \      rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<Pool>()) {\n        if (rng_state == 0) rng_state\
    \ = 1;\n    }\n\n    explicit PersistentDynamicArray(int n) : PersistentDynamicArray(n,\
    \ T()) {}\n\n    PersistentDynamicArray(int n, const T& value) : PersistentDynamicArray()\
    \ {\n        assert(0 <= n);\n        std::vector<T> v(n, value);\n        root\
    \ = build_from_vector(std::move(v), rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    explicit PersistentDynamicArray(const\
    \ std::vector<T>& v) : PersistentDynamicArray() {\n        root = build_from_vector(v,\
    \ rng_state);\n        pool->retain(root);\n        pool->discard_unreferenced();\n\
    \    }\n\n    explicit PersistentDynamicArray(std::vector<T>&& v) : PersistentDynamicArray()\
    \ {\n        root = build_from_vector(std::move(v), rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    PersistentDynamicArray(std::initializer_list<T>\
    \ init) : PersistentDynamicArray(std::vector<T>(init)) {}\n\n    PersistentDynamicArray(const\
    \ PersistentDynamicArray& other)\n        : root(other.root), rng_state(other.rng_state),\
    \ pool(other.pool) {\n        if (pool) pool->retain(root);\n    }\n\n    PersistentDynamicArray(PersistentDynamicArray&&\
    \ other) noexcept\n        : root(other.root), rng_state(other.rng_state), pool(std::move(other.pool))\
    \ {\n        other.root = -1;\n    }\n\n    PersistentDynamicArray& operator=(const\
    \ PersistentDynamicArray& other) {\n        if (this == &other) return *this;\n\
    \        if (other.pool) other.pool->retain(other.root);\n        if (pool) pool->release(root);\n\
    \        root = other.root;\n        rng_state = other.rng_state;\n        pool\
    \ = other.pool;\n        return *this;\n    }\n\n    PersistentDynamicArray& operator=(PersistentDynamicArray&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (pool)\
    \ pool->release(root);\n        root = other.root;\n        rng_state = other.rng_state;\n\
    \        pool = std::move(other.pool);\n        other.root = -1;\n        return\
    \ *this;\n    }\n\n    ~PersistentDynamicArray() {\n        if (pool) pool->release(root);\n\
    \    }\n\n    int size() const {\n        return subtree_size(root);\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void release()\
    \ {\n        if (pool) pool->release(root);\n        root = -1;\n        pool\
    \ = std::make_shared<Pool>();\n    }\n\n    std::size_t node_count() const { return\
    \ pool ? pool->size() : 0; }\n\n    PersistentDynamicArray clear() const {\n \
    \       return make_version(-1, rng_state);\n    }\n\n    PersistentDynamicArray\
    \ insert(int pos, T val) const {\n        assert(0 <= pos && pos <= size());\n\
    \        std::uint32_t next = next_state(rng_state);\n        int node = make_node(std::move(val),\
    \ int(next), false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n \
    \       return make_version(merge(merge(l, node), r), next);\n    }\n\n    PersistentDynamicArray\
    \ insert(int pos, const std::vector<T>& v) const {\n        assert(0 <= pos &&\
    \ pos <= size());\n        if (v.empty()) return *this;\n        std::uint32_t\
    \ next = rng_state;\n        int mid = build_from_vector(v, next);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), next);\n    }\n\n    PersistentDynamicArray insert(int pos, std::vector<T>&&\
    \ v) const {\n        assert(0 <= pos && pos <= size());\n        if (v.empty())\
    \ return *this;\n        std::uint32_t next = rng_state;\n        int mid = build_from_vector(std::move(v),\
    \ next);\n        auto [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), next);\n    }\n\n    PersistentDynamicArray insert(int pos, std::initializer_list<T>\
    \ init) const {\n        return insert(pos, std::vector<T>(init));\n    }\n\n\
    \    PersistentDynamicArray insert(int pos, const PersistentDynamicArray& other)\
    \ const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), rng_state);\n    }\n\n    PersistentDynamicArray push_back(T val)\
    \ const {\n        return insert(size(), std::move(val));\n    }\n\n    PersistentDynamicArray\
    \ push_front(T val) const {\n        return insert(0, std::move(val));\n    }\n\
    \n    PersistentDynamicArray append(const std::vector<T>& v) const {\n       \
    \ return insert(size(), v);\n    }\n\n    PersistentDynamicArray append(std::vector<T>&&\
    \ v) const {\n        return insert(size(), std::move(v));\n    }\n\n    PersistentDynamicArray\
    \ append(const PersistentDynamicArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicArray erase(int pos) const {\n      \
    \  assert(0 <= pos && pos < size());\n        auto [a, b] = split_node(root, pos);\n\
    \        auto [mid, c] = split_node(b, 1);\n        (void)mid;\n        return\
    \ make_version(merge(a, c), rng_state);\n    }\n\n    PersistentDynamicArray erase(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n      \
    \  if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n   \
    \     auto [mid, c] = split_node(b, r - l);\n        (void)mid;\n        return\
    \ make_version(merge(a, c), rng_state);\n    }\n\n    PersistentDynamicArray pop_back()\
    \ const {\n        assert(!empty());\n        return erase(size() - 1);\n    }\n\
    \n    PersistentDynamicArray pop_front() const {\n        assert(!empty());\n\
    \        return erase(0);\n    }\n\n    const T& at(int pos) const {\n       \
    \ assert(0 <= pos && pos < size());\n        return (*pool)[find_node(root, pos)].val;\n\
    \    }\n\n    const T& operator[](int pos) const {\n        return at(pos);\n\
    \    }\n\n    const T& front() const {\n        assert(!empty());\n        return\
    \ at(0);\n    }\n\n    const T& back() const {\n        assert(!empty());\n  \
    \      return at(size() - 1);\n    }\n\n    T get(int pos) const {\n        return\
    \ at(pos);\n    }\n\n    PersistentDynamicArray set(int pos, T val) const {\n\
    \        assert(0 <= pos && pos < size());\n        return make_version(set_node(root,\
    \ pos, std::move(val)), rng_state);\n    }\n\n    void set_inplace(int pos, T\
    \ val) {\n        assert(0 <= pos && pos < size());\n        int next_root = set_node_inplace(root,\
    \ pos, std::move(val));\n        pool->replace(root, next_root);\n        pool->discard_unreferenced();\n\
    \    }\n\n    PersistentDynamicArray reverse(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return *this;\n       \
    \ auto [a, b] = split_node(root, l);\n        auto [mid, c] = split_node(b, r\
    \ - l);\n        return make_version(merge(merge(a, reversed_node(mid)), c), rng_state);\n\
    \    }\n\n    PersistentDynamicArray reverse() const {\n        return make_version(reversed_node(root),\
    \ rng_state);\n    }\n\n    PersistentDynamicArray rotate(int l, int m, int r)\
    \ const {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n      \
    \  if (l == m || m == r) return *this;\n        auto [a, b] = split_node(root,\
    \ l);\n        auto [c, d] = split_node(b, m - l);\n        auto [e, f] = split_node(d,\
    \ r - m);\n        return make_version(merge(merge(a, e), merge(c, f)), rng_state);\n\
    \    }\n\n    std::pair<PersistentDynamicArray, PersistentDynamicArray> split(int\
    \ pos) const {\n        assert(0 <= pos && pos <= size());\n        auto [l, r]\
    \ = split_node(root, pos);\n        PersistentDynamicArray left(l, rng_state,\
    \ pool);\n        PersistentDynamicArray right(r, rng_state, pool);\n        pool->discard_unreferenced();\n\
    \        return {std::move(left), std::move(right)};\n    }\n\n    PersistentDynamicArray\
    \ split_off(int pos) const {\n        assert(0 <= pos && pos <= size());\n   \
    \     return make_version(split_node(root, pos).second, rng_state);\n    }\n\n\
    \    std::vector<T> to_vector() const {\n        std::vector<T> res;\n       \
    \ res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n  \
    \  }\n\n    std::vector<T> to_vector(int l, int r) const {\n        assert(0 <=\
    \ l && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\
    \n\n\n\n#line 13 \"ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\
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
    \n\n#line 16 \"ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct PersistentDynamicLazyMonoidArray {\n    using T = typename\
    \ ActedMonoid::value_type;\n    using F = typename ActedMonoid::operator_type;\n\
    \n   private:\n    struct Node {\n        T val, prod, rprod;\n        F lazy;\n\
    \        int priority;\n        int count;\n        int l, r;\n        bool rev;\n\
    \        bool has_lazy;\n\n        Node(T value, T product, T reverse_product,\
    \ F lazy_value, int node_priority, int node_count, int left,\n             int\
    \ right, bool reversed, bool lazy_flag)\n            : val(std::move(value)),\n\
    \              prod(std::move(product)),\n              rprod(std::move(reverse_product)),\n\
    \              lazy(std::move(lazy_value)),\n              priority(node_priority),\n\
    \              count(node_count),\n              l(left),\n              r(right),\n\
    \              rev(reversed),\n              has_lazy(lazy_flag) {}\n    };\n\n\
    \    struct BuildNode {\n        T val;\n        int priority;\n        int l,\
    \ r;\n\n        BuildNode(T value, int node_priority) : val(std::move(value)),\
    \ priority(node_priority), l(-1), r(-1) {}\n    };\n\n    int root;\n    std::uint32_t\
    \ rng_state;\n    using Pool = detail::PersistentBinaryNodePool<Node>;\n\n   \
    \ std::shared_ptr<Pool> pool;\n\n    int subtree_size(int t) const {\n       \
    \ return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    T node_prod(int t) const\
    \ {\n        return t == -1 ? ActedMonoid::id() : (*pool)[t].prod;\n    }\n\n\
    \    T node_rprod(int t) const {\n        return t == -1 ? ActedMonoid::id() :\
    \ (*pool)[t].rprod;\n    }\n\n    static std::uint32_t next_state(std::uint32_t\
    \ state) {\n        state ^= state << 13;\n        state ^= state >> 17;\n   \
    \     state ^= state << 5;\n        return state == 0 ? 1 : state;\n    }\n\n\
    \    static int next_priority(std::uint32_t& state) {\n        state = next_state(state);\n\
    \        return int(state);\n    }\n\n    template <typename U>\n    static T\
    \ make_value(const U& value) {\n        if constexpr (requires(U x) { ActedMonoid::make(x);\
    \ }) {\n            return ActedMonoid::make(value);\n        } else {\n     \
    \       return static_cast<T>(value);\n        }\n    }\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ord) {\n        if constexpr (requires(F g,\
    \ T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n            return\
    \ ActedMonoid::mapping(f, value, ord);\n        } else {\n            return ActedMonoid::mapping(f,\
    \ value);\n        }\n    }\n\n    static F shift_operator(const F& f, long long\
    \ ord) {\n        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g,\
    \ i); }) {\n            return ActedMonoid::op_shift(f, ord);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    static F reverse_operator(const\
    \ F& f, long long size) {\n        if constexpr (requires(F g, long long n) {\
    \ ActedMonoid::op_reverse(g, n); }) {\n            return ActedMonoid::op_reverse(f,\
    \ size);\n        } else {\n            return f;\n        }\n    }\n\n    F compose_for_child(const\
    \ F& inherited, int t, long long ord) const {\n        F shifted = shift_operator(inherited,\
    \ ord);\n        const Node& node = (*pool)[t];\n        if (!node.has_lazy) return\
    \ shifted;\n        return ActedMonoid::op_comp(shifted, shift_operator(node.lazy,\
    \ ord));\n    }\n\n    int make_raw_node(T val, T prod, T rprod, F lazy, int priority,\
    \ int count, bool rev, bool has_lazy, int l,\n                      int r) const\
    \ {\n        return pool->emplace(std::move(val), std::move(prod), std::move(rprod),\
    \ std::move(lazy), priority, count,\n                             l, r, rev, has_lazy);\n\
    \    }\n\n    int make_node(T val, int priority, bool rev, int l, int r) const\
    \ {\n        T prod = ActedMonoid::op(ActedMonoid::op(node_prod(l), val), node_prod(r));\n\
    \        T rprod = ActedMonoid::op(ActedMonoid::op(node_rprod(r), val), node_rprod(l));\n\
    \        if (rev) std::swap(prod, rprod);\n        int count = 1 + subtree_size(l)\
    \ + subtree_size(r);\n        return make_raw_node(std::move(val), std::move(prod),\
    \ std::move(rprod), ActedMonoid::op_id(), priority,\n                        \
    \     count, rev, false, l, r);\n    }\n\n    int reversed_node(int t) const {\n\
    \        if (t == -1) return -1;\n        Node node = (*pool)[t];\n        F lazy\
    \ = node.has_lazy ? reverse_operator(node.lazy, node.count) : node.lazy;\n   \
    \     return make_raw_node(std::move(node.val), std::move(node.rprod), std::move(node.prod),\
    \ std::move(lazy),\n                             node.priority, node.count, !node.rev,\
    \ node.has_lazy, node.l, node.r);\n    }\n\n    void all_apply_to_node(int t,\
    \ const F& f) const {\n        Node& node = (*pool)[t];\n        int left_count\
    \ = node.rev ? subtree_size(node.r) : subtree_size(node.l);\n        node.val\
    \ = mapping_at(f, node.val, left_count);\n        node.prod = mapping_at(f, node.prod,\
    \ 0);\n        node.rprod = mapping_at(reverse_operator(f, node.count), node.rprod,\
    \ 0);\n        node.lazy = ActedMonoid::op_comp(f, node.lazy);\n        node.has_lazy\
    \ = true;\n    }\n\n    int all_apply(int t, const F& f) const {\n        if (t\
    \ == -1) return -1;\n        int result = pool->clone(t);\n        all_apply_to_node(result,\
    \ f);\n        return result;\n    }\n\n    int push(int t) const {\n        if\
    \ (t == -1) return -1;\n        const Node& stored = (*pool)[t];\n        if (!stored.rev\
    \ && !stored.has_lazy) return t;\n        Node node = stored;\n        int l =\
    \ node.l;\n        int r = node.r;\n        if (node.rev) {\n            std::swap(l,\
    \ r);\n            l = reversed_node(l);\n            r = reversed_node(r);\n\
    \        }\n        if (node.has_lazy) {\n            l = all_apply(l, node.lazy);\n\
    \            r = all_apply(r, shift_operator(node.lazy, subtree_size(l) + 1));\n\
    \        }\n        return make_node(std::move(node.val), node.priority, false,\
    \ l, r);\n    }\n\n    int merge(int l, int r) const {\n        if (l == -1 ||\
    \ r == -1) return l == -1 ? r : l;\n        if ((*pool)[l].priority > (*pool)[r].priority)\
    \ {\n            Node node = (*pool)[push(l)];\n            int right = merge(node.r,\
    \ r);\n            return make_node(std::move(node.val), node.priority, false,\
    \ node.l, right);\n        }\n        Node node = (*pool)[push(r)];\n        int\
    \ left = merge(l, node.l);\n        return make_node(std::move(node.val), node.priority,\
    \ false, left, node.r);\n    }\n\n    std::pair<int, int> split_node(int t, int\
    \ pos) const {\n        if (t == -1) return {-1, -1};\n        Node node = (*pool)[push(t)];\n\
    \        int left_count = subtree_size(node.l);\n        if (pos <= left_count)\
    \ {\n            auto [a, b] = split_node(node.l, pos);\n            return {a,\
    \ make_node(std::move(node.val), node.priority, false, b, node.r)};\n        }\n\
    \        auto [a, b] = split_node(node.r, pos - left_count - 1);\n        return\
    \ {make_node(std::move(node.val), node.priority, false, node.l, a), b};\n    }\n\
    \n    int set_node(int t, int pos, T val) const {\n        Node node = (*pool)[push(t)];\n\
    \        int left_count = subtree_size(node.l);\n        if (pos < left_count)\
    \ {\n            int l = set_node(node.l, pos, std::move(val));\n            return\
    \ make_node(std::move(node.val), node.priority, false, l, node.r);\n        }\n\
    \        if (pos == left_count) {\n            return make_node(std::move(val),\
    \ node.priority, false, node.l, node.r);\n        }\n        int r = set_node(node.r,\
    \ pos - left_count - 1, std::move(val));\n        return make_node(std::move(node.val),\
    \ node.priority, false, node.l, r);\n    }\n\n    void reverse_node_inplace(int\
    \ t) const {\n        Node& node = (*pool)[t];\n        std::swap(node.prod, node.rprod);\n\
    \        if (node.has_lazy) node.lazy = reverse_operator(node.lazy, node.count);\n\
    \        node.rev = !node.rev;\n    }\n\n    int reverse_node_cow(int t) const\
    \ {\n        if (t == -1) return -1;\n        t = pool->clone_if_shared(t);\n\
    \        reverse_node_inplace(t);\n        return t;\n    }\n\n    int all_apply_cow(int\
    \ t, const F& f) const {\n        if (t == -1) return -1;\n        t = pool->clone_if_shared(t);\n\
    \        all_apply_to_node(t, f);\n        return t;\n    }\n\n    void pull(int\
    \ t) const {\n        Node& node = (*pool)[t];\n        node.prod = ActedMonoid::op(ActedMonoid::op(node_prod(node.l),\
    \ node.val), node_prod(node.r));\n        node.rprod = ActedMonoid::op(ActedMonoid::op(node_rprod(node.r),\
    \ node.val), node_rprod(node.l));\n    }\n\n    void push_inplace(int t) const\
    \ {\n        if (!(*pool)[t].rev && !(*pool)[t].has_lazy) return;\n        const\
    \ bool reversed = (*pool)[t].rev;\n        const bool has_lazy = (*pool)[t].has_lazy;\n\
    \        F lazy = (*pool)[t].lazy;\n        int left = (*pool)[t].l;\n       \
    \ int right = (*pool)[t].r;\n        if (reversed) {\n            int new_left\
    \ = reverse_node_cow(right);\n            int new_right = reverse_node_cow(left);\n\
    \            // Keep both children alive while the two owning edges are swapped.\n\
    \            pool->retain(new_left);\n            pool->retain(new_right);\n \
    \           pool->replace((*pool)[t].l, new_left);\n            pool->replace((*pool)[t].r,\
    \ new_right);\n            pool->release(new_left);\n            pool->release(new_right);\n\
    \        }\n        if (has_lazy) {\n            left = all_apply_cow((*pool)[t].l,\
    \ lazy);\n            pool->replace((*pool)[t].l, left);\n            right =\
    \ all_apply_cow((*pool)[t].r, shift_operator(lazy, subtree_size(left) + 1));\n\
    \            pool->replace((*pool)[t].r, right);\n        }\n        Node& node\
    \ = (*pool)[t];\n        node.lazy = ActedMonoid::op_id();\n        node.rev =\
    \ false;\n        node.has_lazy = false;\n        pull(t);\n    }\n\n    int set_node_inplace(int\
    \ t, int pos, T val) const {\n        t = pool->clone_if_shared(t);\n        push_inplace(t);\n\
    \        int left_count = subtree_size((*pool)[t].l);\n        if (pos < left_count)\
    \ {\n            int child = set_node_inplace((*pool)[t].l, pos, std::move(val));\n\
    \            pool->replace((*pool)[t].l, child);\n        } else if (pos == left_count)\
    \ {\n            (*pool)[t].val = std::move(val);\n        } else {\n        \
    \    int child = set_node_inplace((*pool)[t].r, pos - left_count - 1, std::move(val));\n\
    \            pool->replace((*pool)[t].r, child);\n        }\n        pull(t);\n\
    \        return t;\n    }\n\n    int apply_node_inplace(int t, int offset, int\
    \ query_left, int query_right, const F& f) const {\n        if (t == -1 || query_right\
    \ <= offset || offset + subtree_size(t) <= query_left) return t;\n        t =\
    \ pool->clone_if_shared(t);\n        if (query_left <= offset && offset + subtree_size(t)\
    \ <= query_right) {\n            all_apply_to_node(t, shift_operator(f, offset\
    \ - query_left));\n            return t;\n        }\n        push_inplace(t);\n\
    \        int left_count = subtree_size((*pool)[t].l);\n        int child = apply_node_inplace((*pool)[t].l,\
    \ offset, query_left, query_right, f);\n        pool->replace((*pool)[t].l, child);\n\
    \        int position = offset + left_count;\n        if (query_left <= position\
    \ && position < query_right) {\n            (*pool)[t].val = mapping_at(shift_operator(f,\
    \ position - query_left), (*pool)[t].val, 0);\n        }\n        child = apply_node_inplace((*pool)[t].r,\
    \ position + 1, query_left, query_right, f);\n        pool->replace((*pool)[t].r,\
    \ child);\n        pull(t);\n        return t;\n    }\n\n    T get_value(int t,\
    \ int pos, F inherited, bool reversed = false) const {\n        while (t != -1)\
    \ {\n            const Node& node = (*pool)[t];\n            bool cur_reversed\
    \ = reversed ^ node.rev;\n            int l = cur_reversed ? node.r : node.l;\n\
    \            int r = cur_reversed ? node.l : node.r;\n            int left_count\
    \ = subtree_size(l);\n            if (pos < left_count) {\n                inherited\
    \ = compose_for_child(inherited, t, 0);\n                t = l;\n            \
    \    reversed = cur_reversed;\n            } else if (pos == left_count) {\n \
    \               return mapping_at(inherited, node.val, left_count);\n        \
    \    } else {\n                pos -= left_count + 1;\n                inherited\
    \ = compose_for_child(inherited, t, left_count + 1);\n                t = r;\n\
    \                reversed = cur_reversed;\n            }\n        }\n        return\
    \ ActedMonoid::id();\n    }\n\n    T prod_dfs(int t, int ql, int qr, int offset,\
    \ const F& inherited, bool reversed = false) const {\n        if (t == -1 || qr\
    \ <= offset || offset + (*pool)[t].count <= ql) return ActedMonoid::id();\n  \
    \      const Node& node = (*pool)[t];\n        bool cur_reversed = reversed ^\
    \ node.rev;\n        if (ql <= offset && offset + node.count <= qr) {\n      \
    \      return mapping_at(inherited, reversed ? node.rprod : node.prod, 0);\n \
    \       }\n        int l = cur_reversed ? node.r : node.l;\n        int r = cur_reversed\
    \ ? node.l : node.r;\n        int left_count = subtree_size(l);\n        int node_pos\
    \ = offset + left_count;\n        T res = prod_dfs(l, ql, qr, offset, compose_for_child(inherited,\
    \ t, 0), cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res = ActedMonoid::op(res,\
    \ mapping_at(inherited, node.val, left_count));\n        return ActedMonoid::op(\n\
    \            res, prod_dfs(r, ql, qr, node_pos + 1, compose_for_child(inherited,\
    \ t, left_count + 1),\n                          cur_reversed));\n    }\n\n  \
    \  void dump_dfs(int t, std::vector<T>& res, const F& inherited, bool reversed\
    \ = false) const {\n        if (t == -1) return;\n        const Node& node = (*pool)[t];\n\
    \        bool cur_reversed = reversed ^ node.rev;\n        int l = cur_reversed\
    \ ? node.r : node.l;\n        int r = cur_reversed ? node.l : node.r;\n      \
    \  int left_count = subtree_size(l);\n        dump_dfs(l, res, compose_for_child(inherited,\
    \ t, 0), cur_reversed);\n        res.push_back(mapping_at(inherited, node.val,\
    \ left_count));\n        dump_dfs(r, res, compose_for_child(inherited, t, left_count\
    \ + 1), cur_reversed);\n    }\n\n    void dump_range_dfs(int t, int ql, int qr,\
    \ int offset, std::vector<T>& res, const F& inherited,\n                     \
    \   bool reversed = false) const {\n        if (t == -1 || qr <= offset || offset\
    \ + (*pool)[t].count <= ql) return;\n        const Node& node = (*pool)[t];\n\
    \        bool cur_reversed = reversed ^ node.rev;\n        int l = cur_reversed\
    \ ? node.r : node.l;\n        int r = cur_reversed ? node.l : node.r;\n      \
    \  int left_count = subtree_size(l);\n        int node_pos = offset + left_count;\n\
    \        dump_range_dfs(l, ql, qr, offset, res, compose_for_child(inherited, t,\
    \ 0), cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res.push_back(mapping_at(inherited,\
    \ node.val, left_count));\n        dump_range_dfs(r, ql, qr, node_pos + 1, res,\
    \ compose_for_child(inherited, t, left_count + 1),\n                       cur_reversed);\n\
    \    }\n\n    int build_from_nodes(std::vector<BuildNode>& nodes, int t) const\
    \ {\n        if (t == -1) return -1;\n        int l = build_from_nodes(nodes,\
    \ nodes[t].l);\n        int r = build_from_nodes(nodes, nodes[t].r);\n       \
    \ return make_node(std::move(nodes[t].val), nodes[t].priority, false, l, r);\n\
    \    }\n\n    int build_cartesian(std::vector<BuildNode>& nodes) const {\n   \
    \     if (nodes.empty()) return -1;\n        std::vector<int> stack;\n       \
    \ stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
    \ i++) {\n            int left_child = -1;\n            while (!stack.empty()\
    \ && nodes[stack.back()].priority < nodes[i].priority) {\n                left_child\
    \ = stack.back();\n                stack.pop_back();\n            }\n        \
    \    nodes[i].l = left_child;\n            if (!stack.empty()) nodes[stack.back()].r\
    \ = i;\n            stack.push_back(i);\n        }\n        return build_from_nodes(nodes,\
    \ stack.front());\n    }\n\n    int build_from_vector(const std::vector<T>& v,\
    \ std::uint32_t& state) const {\n        std::vector<BuildNode> nodes;\n     \
    \   nodes.reserve(v.size());\n        for (const T& x : v) nodes.emplace_back(x,\
    \ next_priority(state));\n        return build_cartesian(nodes);\n    }\n\n  \
    \  int build_from_vector(std::vector<T>&& v, std::uint32_t& state) const {\n \
    \       std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n    \
    \    for (T& x : v) nodes.emplace_back(std::move(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    template <typename U>\n\
    \    int build_from_values(const std::vector<U>& v, std::uint32_t& state) const\
    \ {\n        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n\
    \        for (const U& x : v) nodes.emplace_back(make_value(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicLazyMonoidArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_raw_node(node.val, node.prod, node.rprod, node.lazy, node.priority,\
    \ node.count, node.rev,\n                             node.has_lazy, l, r);\n\
    \    }\n\n    explicit PersistentDynamicLazyMonoidArray(int node, std::uint32_t\
    \ state,\n                                              std::shared_ptr<Pool>\
    \ node_pool)\n        : root(node), rng_state(state), pool(std::move(node_pool))\
    \ {\n        pool->retain(root);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ make_version(int node, std::uint32_t state) const {\n        PersistentDynamicLazyMonoidArray\
    \ result(node, state, pool);\n        pool->discard_unreferenced();\n        return\
    \ result;\n    }\n\n   public:\n    PersistentDynamicLazyMonoidArray()\n     \
    \   : root(-1),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<Pool>()) {\n        if (rng_state == 0) rng_state\
    \ = 1;\n    }\n\n    explicit PersistentDynamicLazyMonoidArray(int n)\n      \
    \  : PersistentDynamicLazyMonoidArray(n, ActedMonoid::id()) {}\n\n    PersistentDynamicLazyMonoidArray(int\
    \ n, const T& value) : PersistentDynamicLazyMonoidArray() {\n        assert(0\
    \ <= n);\n        pool->reserve(n);\n        std::vector<T> v(n, value);\n   \
    \     root = build_from_vector(std::move(v), rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    explicit PersistentDynamicLazyMonoidArray(const\
    \ std::vector<T>& v)\n        : PersistentDynamicLazyMonoidArray() {\n       \
    \ pool->reserve(v.size());\n        root = build_from_vector(v, rng_state);\n\
    \        pool->retain(root);\n        pool->discard_unreferenced();\n    }\n\n\
    \    explicit PersistentDynamicLazyMonoidArray(std::vector<T>&& v) : PersistentDynamicLazyMonoidArray()\
    \ {\n        pool->reserve(v.size());\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n        pool->retain(root);\n        pool->discard_unreferenced();\n\
    \    }\n\n    template <typename U>\n        requires(!std::same_as<U, T>) &&\n\
    \                (requires(U x) { ActedMonoid::make(x); } || std::convertible_to<U,\
    \ T>)\n    explicit PersistentDynamicLazyMonoidArray(const std::vector<U>& v)\n\
    \        : PersistentDynamicLazyMonoidArray() {\n        pool->reserve(v.size());\n\
    \        root = build_from_values(v, rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    PersistentDynamicLazyMonoidArray(std::initializer_list<T>\
    \ init)\n        : PersistentDynamicLazyMonoidArray(std::vector<T>(init)) {}\n\
    \n    PersistentDynamicLazyMonoidArray(const PersistentDynamicLazyMonoidArray&\
    \ other)\n        : root(other.root), rng_state(other.rng_state), pool(other.pool)\
    \ {\n        if (pool) pool->retain(root);\n    }\n\n    PersistentDynamicLazyMonoidArray(PersistentDynamicLazyMonoidArray&&\
    \ other) noexcept\n        : root(other.root), rng_state(other.rng_state), pool(std::move(other.pool))\
    \ {\n        other.root = -1;\n    }\n\n    PersistentDynamicLazyMonoidArray&\
    \ operator=(const PersistentDynamicLazyMonoidArray& other) {\n        if (this\
    \ == &other) return *this;\n        if (other.pool) other.pool->retain(other.root);\n\
    \        if (pool) pool->release(root);\n        root = other.root;\n        rng_state\
    \ = other.rng_state;\n        pool = other.pool;\n        return *this;\n    }\n\
    \n    PersistentDynamicLazyMonoidArray& operator=(PersistentDynamicLazyMonoidArray&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (pool)\
    \ pool->release(root);\n        root = other.root;\n        rng_state = other.rng_state;\n\
    \        pool = std::move(other.pool);\n        other.root = -1;\n        return\
    \ *this;\n    }\n\n    ~PersistentDynamicLazyMonoidArray() {\n        if (pool)\
    \ pool->release(root);\n    }\n\n    int size() const {\n        return subtree_size(root);\n\
    \    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\n   \
    \ void release() {\n        if (pool) pool->release(root);\n        root = -1;\n\
    \        pool = std::make_shared<Pool>();\n    }\n\n    std::size_t node_count()\
    \ const { return pool ? pool->size() : 0; }\n\n    PersistentDynamicLazyMonoidArray\
    \ clear() const {\n        return make_version(-1, rng_state);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ insert(int pos, T value) const {\n        assert(0 <= pos && pos <= size());\n\
    \        std::uint32_t next = next_state(rng_state);\n        int node = make_node(std::move(value),\
    \ int(next), false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n \
    \       return make_version(merge(merge(l, node), r), next);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ insert(int pos, const std::vector<T>& v) const {\n        assert(0 <= pos &&\
    \ pos <= size());\n        if (v.empty()) return *this;\n        std::uint32_t\
    \ next = rng_state;\n        int mid = build_from_vector(v, next);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), next);\n    }\n\n    PersistentDynamicLazyMonoidArray insert(int pos,\
    \ std::vector<T>&& v) const {\n        assert(0 <= pos && pos <= size());\n  \
    \      if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        int mid = build_from_vector(std::move(v), next);\n        auto [l, r]\
    \ = split_node(root, pos);\n        return make_version(merge(merge(l, mid), r),\
    \ next);\n    }\n\n    PersistentDynamicLazyMonoidArray insert(int pos, std::initializer_list<T>\
    \ init) const {\n        return insert(pos, std::vector<T>(init));\n    }\n\n\
    \    PersistentDynamicLazyMonoidArray insert(int pos, const PersistentDynamicLazyMonoidArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), rng_state);\n    }\n\n    PersistentDynamicLazyMonoidArray push_back(T\
    \ value) const {\n        return insert(size(), std::move(value));\n    }\n\n\
    \    PersistentDynamicLazyMonoidArray push_front(T value) const {\n        return\
    \ insert(0, std::move(value));\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ append(const std::vector<T>& v) const {\n        return insert(size(), v);\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray append(std::vector<T>&& v) const\
    \ {\n        return insert(size(), std::move(v));\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ append(const PersistentDynamicLazyMonoidArray& other) const {\n        return\
    \ insert(size(), other);\n    }\n\n    PersistentDynamicLazyMonoidArray erase(int\
    \ pos) const {\n        assert(0 <= pos && pos < size());\n        auto [a, b]\
    \ = split_node(root, pos);\n        auto [mid, c] = split_node(b, 1);\n      \
    \  (void)mid;\n        return make_version(merge(a, c), rng_state);\n    }\n\n\
    \    PersistentDynamicLazyMonoidArray erase(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return *this;\n       \
    \ auto [a, b] = split_node(root, l);\n        auto [mid, c] = split_node(b, r\
    \ - l);\n        (void)mid;\n        return make_version(merge(a, c), rng_state);\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray pop_back() const {\n        assert(!empty());\n\
    \        return erase(size() - 1);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ pop_front() const {\n        assert(!empty());\n        return erase(0);\n \
    \   }\n\n    T get(int pos) const {\n        assert(0 <= pos && pos < size());\n\
    \        return get_value(root, pos, ActedMonoid::op_id());\n    }\n\n    T operator[](int\
    \ pos) const {\n        return get(pos);\n    }\n\n    T front() const {\n   \
    \     assert(!empty());\n        return get(0);\n    }\n\n    T back() const {\n\
    \        assert(!empty());\n        return get(size() - 1);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ set(int pos, T value) const {\n        assert(0 <= pos && pos < size());\n \
    \       return make_version(set_node(root, pos, std::move(value)), rng_state);\n\
    \    }\n\n    void set_inplace(int pos, T value) {\n        assert(0 <= pos &&\
    \ pos < size());\n        int next_root = set_node_inplace(root, pos, std::move(value));\n\
    \        pool->replace(root, next_root);\n        pool->discard_unreferenced();\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray reverse(int l, int r) const {\n\
    \        assert(0 <= l && l <= r && r <= size());\n        if (l == r) return\
    \ *this;\n        auto [a, b] = split_node(root, l);\n        auto [mid, c] =\
    \ split_node(b, r - l);\n        return make_version(merge(merge(a, reversed_node(mid)),\
    \ c), rng_state);\n    }\n\n    PersistentDynamicLazyMonoidArray reverse() const\
    \ {\n        return make_version(reversed_node(root), rng_state);\n    }\n\n \
    \   PersistentDynamicLazyMonoidArray rotate(int l, int m, int r) const {\n   \
    \     assert(0 <= l && l <= m && m <= r && r <= size());\n        if (l == m ||\
    \ m == r) return *this;\n        auto [a, b] = split_node(root, l);\n        auto\
    \ [c, d] = split_node(b, m - l);\n        auto [e, f] = split_node(d, r - m);\n\
    \        return make_version(merge(merge(a, e), merge(c, f)), rng_state);\n  \
    \  }\n\n    PersistentDynamicLazyMonoidArray apply(int pos, const F& f) const\
    \ {\n        assert(0 <= pos && pos < size());\n        return apply(pos, pos\
    \ + 1, f);\n    }\n\n    PersistentDynamicLazyMonoidArray apply(int l, int r,\
    \ const F& f) const {\n        assert(0 <= l && l <= r && r <= size());\n    \
    \    if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n \
    \       auto [mid, c] = split_node(b, r - l);\n        return make_version(merge(merge(a,\
    \ all_apply(mid, f)), c), rng_state);\n    }\n\n    void apply_inplace(int pos,\
    \ const F& f) {\n        assert(0 <= pos && pos < size());\n        apply_inplace(pos,\
    \ pos + 1, f);\n    }\n\n    void apply_inplace(int l, int r, const F& f) {\n\
    \        assert(0 <= l && l <= r && r <= size());\n        if (l == r) return;\n\
    \        int next_root = apply_node_inplace(root, 0, l, r, f);\n        pool->replace(root,\
    \ next_root);\n        pool->discard_unreferenced();\n    }\n\n    T prod(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n      \
    \  if (l == r) return ActedMonoid::id();\n        return prod_dfs(root, l, r,\
    \ 0, ActedMonoid::op_id());\n    }\n\n    T all_prod() const {\n        return\
    \ root == -1 ? ActedMonoid::id() : (*pool)[root].prod;\n    }\n\n    std::pair<PersistentDynamicLazyMonoidArray,\
    \ PersistentDynamicLazyMonoidArray> split(int pos) const {\n        assert(0 <=\
    \ pos && pos <= size());\n        auto [l, r] = split_node(root, pos);\n     \
    \   PersistentDynamicLazyMonoidArray left(l, rng_state, pool);\n        PersistentDynamicLazyMonoidArray\
    \ right(r, rng_state, pool);\n        pool->discard_unreferenced();\n        return\
    \ {std::move(left), std::move(right)};\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ split_off(int pos) const {\n        assert(0 <= pos && pos <= size());\n   \
    \     return make_version(split_node(root, pos).second, rng_state);\n    }\n\n\
    \    std::vector<T> to_vector() const {\n        std::vector<T> res;\n       \
    \ res.reserve(size());\n        dump_dfs(root, res, ActedMonoid::op_id());\n \
    \       return res;\n    }\n\n    std::vector<T> to_vector(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res,\
    \ ActedMonoid::op_id());\n        return res;\n    }\n};\n\n}  // namespace ds\n\
    }  // namespace m1une\n\n\n#line 1 \"ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\
    \n\n\n\n#line 13 \"ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\n\n\
    #line 16 \"ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct\
    \ PersistentDynamicMonoidArray {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Node {\n        T val, prod, rprod;\n        int priority;\n\
    \        int count;\n        int l, r;\n        bool rev;\n\n        Node(T value,\
    \ T product, T reverse_product, int node_priority, int node_count, int left, int\
    \ right,\n             bool reversed)\n            : val(std::move(value)),\n\
    \              prod(std::move(product)),\n              rprod(std::move(reverse_product)),\n\
    \              priority(node_priority),\n              count(node_count),\n  \
    \            l(left),\n              r(right),\n              rev(reversed) {}\n\
    \    };\n\n    struct BuildNode {\n        T val;\n        int priority;\n   \
    \     int l, r;\n\n        BuildNode(T value, int node_priority) : val(std::move(value)),\
    \ priority(node_priority), l(-1), r(-1) {}\n    };\n\n    int root;\n    std::uint32_t\
    \ rng_state;\n    using Pool = detail::PersistentBinaryNodePool<Node>;\n\n   \
    \ std::shared_ptr<Pool> pool;\n\n    int subtree_size(int t) const {\n       \
    \ return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    T node_prod(int t) const\
    \ {\n        return t == -1 ? Monoid::id() : (*pool)[t].prod;\n    }\n\n    T\
    \ node_rprod(int t) const {\n        return t == -1 ? Monoid::id() : (*pool)[t].rprod;\n\
    \    }\n\n    static std::uint32_t next_state(std::uint32_t state) {\n       \
    \ state ^= state << 13;\n        state ^= state >> 17;\n        state ^= state\
    \ << 5;\n        return state == 0 ? 1 : state;\n    }\n\n    static int next_priority(std::uint32_t&\
    \ state) {\n        state = next_state(state);\n        return int(state);\n \
    \   }\n\n    template <typename U>\n    static T make_value(const U& value) {\n\
    \        if constexpr (requires(U x) { Monoid::make(x); }) {\n            return\
    \ Monoid::make(value);\n        } else {\n            return static_cast<T>(value);\n\
    \        }\n    }\n\n    int make_node(T val, int priority, bool rev, int l, int\
    \ r) const {\n        T prod = Monoid::op(Monoid::op(node_prod(l), val), node_prod(r));\n\
    \        T rprod = Monoid::op(Monoid::op(node_rprod(r), val), node_rprod(l));\n\
    \        if (rev) std::swap(prod, rprod);\n        int count = 1 + subtree_size(l)\
    \ + subtree_size(r);\n        return pool->emplace(std::move(val), std::move(prod),\
    \ std::move(rprod), priority, count, l, r, rev);\n    }\n\n    int reversed_node(int\
    \ t) const {\n        if (t == -1) return -1;\n        Node node = (*pool)[t];\n\
    \        return make_node(std::move(node.val), node.priority, !node.rev, node.l,\
    \ node.r);\n    }\n\n    int push(int t) const {\n        if (t == -1 || !(*pool)[t].rev)\
    \ return t;\n        Node node = (*pool)[t];\n        int l = reversed_node(node.r);\n\
    \        int r = reversed_node(node.l);\n        return make_node(std::move(node.val),\
    \ node.priority, false, l, r);\n    }\n\n    int merge(int l, int r) const {\n\
    \        if (l == -1 || r == -1) return l == -1 ? r : l;\n        if ((*pool)[l].priority\
    \ > (*pool)[r].priority) {\n            Node node = (*pool)[push(l)];\n      \
    \      int right = merge(node.r, r);\n            return make_node(std::move(node.val),\
    \ node.priority, false, node.l, right);\n        }\n        Node node = (*pool)[push(r)];\n\
    \        int left = merge(l, node.l);\n        return make_node(std::move(node.val),\
    \ node.priority, false, left, node.r);\n    }\n\n    std::pair<int, int> split_node(int\
    \ t, int pos) const {\n        if (t == -1) return {-1, -1};\n        Node node\
    \ = (*pool)[push(t)];\n        int left_count = subtree_size(node.l);\n      \
    \  if (pos <= left_count) {\n            auto [a, b] = split_node(node.l, pos);\n\
    \            return {a, make_node(std::move(node.val), node.priority, false, b,\
    \ node.r)};\n        }\n        auto [a, b] = split_node(node.r, pos - left_count\
    \ - 1);\n        return {make_node(std::move(node.val), node.priority, false,\
    \ node.l, a), b};\n    }\n\n    int set_node(int t, int pos, T val) const {\n\
    \        Node node = (*pool)[push(t)];\n        int left_count = subtree_size(node.l);\n\
    \        if (pos < left_count) {\n            int l = set_node(node.l, pos, std::move(val));\n\
    \            return make_node(std::move(node.val), node.priority, false, l, node.r);\n\
    \        }\n        if (pos == left_count) {\n            return make_node(std::move(val),\
    \ node.priority, false, node.l, node.r);\n        }\n        int r = set_node(node.r,\
    \ pos - left_count - 1, std::move(val));\n        return make_node(std::move(node.val),\
    \ node.priority, false, node.l, r);\n    }\n\n    void pull(int t) const {\n \
    \       Node& node = (*pool)[t];\n        node.prod = Monoid::op(Monoid::op(node_prod(node.l),\
    \ node.val), node_prod(node.r));\n        node.rprod = Monoid::op(Monoid::op(node_rprod(node.r),\
    \ node.val), node_rprod(node.l));\n        if (node.rev) std::swap(node.prod,\
    \ node.rprod);\n    }\n\n    int set_node_inplace(int t, int pos, T val, bool\
    \ inherited_reversed = false) const {\n        t = pool->clone_if_shared(t);\n\
    \        const bool reversed = inherited_reversed ^ (*pool)[t].rev;\n        const\
    \ int logical_left = reversed ? (*pool)[t].r : (*pool)[t].l;\n        const int\
    \ left_count = subtree_size(logical_left);\n        if (pos < left_count) {\n\
    \            int child = set_node_inplace(logical_left, pos, std::move(val), reversed);\n\
    \            if (reversed) {\n                pool->replace((*pool)[t].r, child);\n\
    \            } else {\n                pool->replace((*pool)[t].l, child);\n \
    \           }\n        } else if (pos == left_count) {\n            (*pool)[t].val\
    \ = std::move(val);\n        } else {\n            const int logical_right = reversed\
    \ ? (*pool)[t].l : (*pool)[t].r;\n            int child = set_node_inplace(logical_right,\
    \ pos - left_count - 1, std::move(val), reversed);\n            if (reversed)\
    \ {\n                pool->replace((*pool)[t].l, child);\n            } else {\n\
    \                pool->replace((*pool)[t].r, child);\n            }\n        }\n\
    \        pull(t);\n        return t;\n    }\n\n    int find_node(int t, int pos)\
    \ const {\n        bool reversed = false;\n        while (t != -1) {\n       \
    \     const Node& node = (*pool)[t];\n            bool cur_reversed = reversed\
    \ ^ node.rev;\n            int l = cur_reversed ? node.r : node.l;\n         \
    \   int r = cur_reversed ? node.l : node.r;\n            int left_count = subtree_size(l);\n\
    \            if (pos < left_count) {\n                t = l;\n               \
    \ reversed = cur_reversed;\n            } else if (pos == left_count) {\n    \
    \            return t;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = r;\n                reversed = cur_reversed;\n   \
    \         }\n        }\n        return -1;\n    }\n\n    T prod_dfs(int t, int\
    \ ql, int qr, int offset, bool reversed = false) const {\n        if (t == -1\
    \ || qr <= offset || offset + (*pool)[t].count <= ql) return Monoid::id();\n \
    \       const Node& node = (*pool)[t];\n        if (ql <= offset && offset + node.count\
    \ <= qr) return reversed ? node.rprod : node.prod;\n        bool cur_reversed\
    \ = reversed ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n  \
    \      int r = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        T res = prod_dfs(l, ql,\
    \ qr, offset, cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res\
    \ = Monoid::op(res, node.val);\n        return Monoid::op(res, prod_dfs(r, ql,\
    \ qr, node_pos + 1, cur_reversed));\n    }\n\n    void dump_dfs(int t, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (t == -1) return;\n        const\
    \ Node& node = (*pool)[t];\n        bool cur_reversed = reversed ^ node.rev;\n\
    \        int l = cur_reversed ? node.r : node.l;\n        int r = cur_reversed\
    \ ? node.l : node.r;\n        dump_dfs(l, res, cur_reversed);\n        res.push_back(node.val);\n\
    \        dump_dfs(r, res, cur_reversed);\n    }\n\n    void dump_range_dfs(int\
    \ t, int ql, int qr, int offset, std::vector<T>& res, bool reversed = false) const\
    \ {\n        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return;\n\
    \        const Node& node = (*pool)[t];\n        bool cur_reversed = reversed\
    \ ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n        int r\
    \ = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(l, ql, qr,\
    \ offset, res, cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res.push_back(node.val);\n\
    \        dump_range_dfs(r, ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n\
    \    int build_from_nodes(std::vector<BuildNode>& nodes, int t) const {\n    \
    \    if (t == -1) return -1;\n        int l = build_from_nodes(nodes, nodes[t].l);\n\
    \        int r = build_from_nodes(nodes, nodes[t].r);\n        return make_node(std::move(nodes[t].val),\
    \ nodes[t].priority, false, l, r);\n    }\n\n    int build_cartesian(std::vector<BuildNode>&\
    \ nodes) const {\n        if (nodes.empty()) return -1;\n        std::vector<int>\
    \ stack;\n        stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
    \ i++) {\n            int left_child = -1;\n            while (!stack.empty()\
    \ && nodes[stack.back()].priority < nodes[i].priority) {\n                left_child\
    \ = stack.back();\n                stack.pop_back();\n            }\n        \
    \    nodes[i].l = left_child;\n            if (!stack.empty()) nodes[stack.back()].r\
    \ = i;\n            stack.push_back(i);\n        }\n        return build_from_nodes(nodes,\
    \ stack.front());\n    }\n\n    int build_from_vector(const std::vector<T>& v,\
    \ std::uint32_t& state) const {\n        std::vector<BuildNode> nodes;\n     \
    \   nodes.reserve(v.size());\n        for (const T& x : v) nodes.emplace_back(x,\
    \ next_priority(state));\n        return build_cartesian(nodes);\n    }\n\n  \
    \  int build_from_vector(std::vector<T>&& v, std::uint32_t& state) const {\n \
    \       std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n    \
    \    for (T& x : v) nodes.emplace_back(std::move(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    template <typename U>\n\
    \    int build_from_values(const std::vector<U>& v, std::uint32_t& state) const\
    \ {\n        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n\
    \        for (const U& x : v) nodes.emplace_back(make_value(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicMonoidArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_node(node.val, node.priority, node.rev, l, r);\n    }\n\n\
    \    explicit PersistentDynamicMonoidArray(int node, std::uint32_t state,\n  \
    \                                        std::shared_ptr<Pool> node_pool)\n  \
    \      : root(node), rng_state(state), pool(std::move(node_pool)) {\n        pool->retain(root);\n\
    \    }\n\n    PersistentDynamicMonoidArray make_version(int node, std::uint32_t\
    \ state) const {\n        PersistentDynamicMonoidArray result(node, state, pool);\n\
    \        pool->discard_unreferenced();\n        return result;\n    }\n\n   public:\n\
    \    PersistentDynamicMonoidArray()\n        : root(-1),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<Pool>()) {\n        if (rng_state == 0) rng_state\
    \ = 1;\n    }\n\n    explicit PersistentDynamicMonoidArray(int n) : PersistentDynamicMonoidArray(n,\
    \ Monoid::id()) {}\n\n    PersistentDynamicMonoidArray(int n, const T& value)\
    \ : PersistentDynamicMonoidArray() {\n        assert(0 <= n);\n        pool->reserve(n);\n\
    \        std::vector<T> v(n, value);\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n        pool->retain(root);\n        pool->discard_unreferenced();\n\
    \    }\n\n    explicit PersistentDynamicMonoidArray(const std::vector<T>& v) :\
    \ PersistentDynamicMonoidArray() {\n        pool->reserve(v.size());\n       \
    \ root = build_from_vector(v, rng_state);\n        pool->retain(root);\n     \
    \   pool->discard_unreferenced();\n    }\n\n    explicit PersistentDynamicMonoidArray(std::vector<T>&&\
    \ v) : PersistentDynamicMonoidArray() {\n        pool->reserve(v.size());\n  \
    \      root = build_from_vector(std::move(v), rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    template <typename U>\n \
    \       requires(!std::same_as<U, T>) && (requires(U x) { Monoid::make(x); } ||\
    \ std::convertible_to<U, T>)\n    explicit PersistentDynamicMonoidArray(const\
    \ std::vector<U>& v) : PersistentDynamicMonoidArray() {\n        pool->reserve(v.size());\n\
    \        root = build_from_values(v, rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    PersistentDynamicMonoidArray(std::initializer_list<T>\
    \ init)\n        : PersistentDynamicMonoidArray(std::vector<T>(init)) {}\n\n \
    \   PersistentDynamicMonoidArray(const PersistentDynamicMonoidArray& other)\n\
    \        : root(other.root), rng_state(other.rng_state), pool(other.pool) {\n\
    \        if (pool) pool->retain(root);\n    }\n\n    PersistentDynamicMonoidArray(PersistentDynamicMonoidArray&&\
    \ other) noexcept\n        : root(other.root), rng_state(other.rng_state), pool(std::move(other.pool))\
    \ {\n        other.root = -1;\n    }\n\n    PersistentDynamicMonoidArray& operator=(const\
    \ PersistentDynamicMonoidArray& other) {\n        if (this == &other) return *this;\n\
    \        if (other.pool) other.pool->retain(other.root);\n        if (pool) pool->release(root);\n\
    \        root = other.root;\n        rng_state = other.rng_state;\n        pool\
    \ = other.pool;\n        return *this;\n    }\n\n    PersistentDynamicMonoidArray&\
    \ operator=(PersistentDynamicMonoidArray&& other) noexcept {\n        if (this\
    \ == &other) return *this;\n        if (pool) pool->release(root);\n        root\
    \ = other.root;\n        rng_state = other.rng_state;\n        pool = std::move(other.pool);\n\
    \        other.root = -1;\n        return *this;\n    }\n\n    ~PersistentDynamicMonoidArray()\
    \ {\n        if (pool) pool->release(root);\n    }\n\n    int size() const {\n\
    \        return subtree_size(root);\n    }\n\n    bool empty() const {\n     \
    \   return size() == 0;\n    }\n\n    void release() {\n        if (pool) pool->release(root);\n\
    \        root = -1;\n        pool = std::make_shared<Pool>();\n    }\n\n    std::size_t\
    \ node_count() const { return pool ? pool->size() : 0; }\n\n    PersistentDynamicMonoidArray\
    \ clear() const {\n        return make_version(-1, rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ insert(int pos, T value) const {\n        assert(0 <= pos && pos <= size());\n\
    \        std::uint32_t next = next_state(rng_state);\n        int node = make_node(std::move(value),\
    \ int(next), false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n \
    \       return make_version(merge(merge(l, node), r), next);\n    }\n\n    PersistentDynamicMonoidArray\
    \ insert(int pos, const std::vector<T>& v) const {\n        assert(0 <= pos &&\
    \ pos <= size());\n        if (v.empty()) return *this;\n        std::uint32_t\
    \ next = rng_state;\n        int mid = build_from_vector(v, next);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), next);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos,\
    \ std::vector<T>&& v) const {\n        assert(0 <= pos && pos <= size());\n  \
    \      if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        int mid = build_from_vector(std::move(v), next);\n        auto [l, r]\
    \ = split_node(root, pos);\n        return make_version(merge(merge(l, mid), r),\
    \ next);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos, std::initializer_list<T>\
    \ init) const {\n        return insert(pos, std::vector<T>(init));\n    }\n\n\
    \    PersistentDynamicMonoidArray insert(int pos, const PersistentDynamicMonoidArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), rng_state);\n    }\n\n    PersistentDynamicMonoidArray push_back(T\
    \ value) const {\n        return insert(size(), std::move(value));\n    }\n\n\
    \    PersistentDynamicMonoidArray push_front(T value) const {\n        return\
    \ insert(0, std::move(value));\n    }\n\n    PersistentDynamicMonoidArray append(const\
    \ std::vector<T>& v) const {\n        return insert(size(), v);\n    }\n\n   \
    \ PersistentDynamicMonoidArray append(std::vector<T>&& v) const {\n        return\
    \ insert(size(), std::move(v));\n    }\n\n    PersistentDynamicMonoidArray append(const\
    \ PersistentDynamicMonoidArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicMonoidArray erase(int pos) const {\n\
    \        assert(0 <= pos && pos < size());\n        auto [a, b] = split_node(root,\
    \ pos);\n        auto [mid, c] = split_node(b, 1);\n        (void)mid;\n     \
    \   return make_version(merge(a, c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ erase(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        (void)mid;\n        return\
    \ make_version(merge(a, c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ pop_back() const {\n        assert(!empty());\n        return erase(size() -\
    \ 1);\n    }\n\n    PersistentDynamicMonoidArray pop_front() const {\n       \
    \ assert(!empty());\n        return erase(0);\n    }\n\n    T get(int pos) const\
    \ {\n        assert(0 <= pos && pos < size());\n        return (*pool)[find_node(root,\
    \ pos)].val;\n    }\n\n    T operator[](int pos) const {\n        return get(pos);\n\
    \    }\n\n    T front() const {\n        assert(!empty());\n        return get(0);\n\
    \    }\n\n    T back() const {\n        assert(!empty());\n        return get(size()\
    \ - 1);\n    }\n\n    PersistentDynamicMonoidArray set(int pos, T value) const\
    \ {\n        assert(0 <= pos && pos < size());\n        return make_version(set_node(root,\
    \ pos, std::move(value)), rng_state);\n    }\n\n    void set_inplace(int pos,\
    \ T value) {\n        assert(0 <= pos && pos < size());\n        int next_root\
    \ = set_node_inplace(root, pos, std::move(value));\n        pool->replace(root,\
    \ next_root);\n        pool->discard_unreferenced();\n    }\n\n    PersistentDynamicMonoidArray\
    \ reverse(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        return make_version(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ reverse() const {\n        return make_version(reversed_node(root), rng_state);\n\
    \    }\n\n    PersistentDynamicMonoidArray rotate(int l, int m, int r) const {\n\
    \        assert(0 <= l && l <= m && m <= r && r <= size());\n        if (l ==\
    \ m || m == r) return *this;\n        auto [a, b] = split_node(root, l);\n   \
    \     auto [c, d] = split_node(b, m - l);\n        auto [e, f] = split_node(d,\
    \ r - m);\n        return make_version(merge(merge(a, e), merge(c, f)), rng_state);\n\
    \    }\n\n    T prod(int l, int r) const {\n        assert(0 <= l && l <= r &&\
    \ r <= size());\n        if (l == r) return Monoid::id();\n        return prod_dfs(root,\
    \ l, r, 0);\n    }\n\n    T all_prod() const {\n        return root == -1 ? Monoid::id()\
    \ : (*pool)[root].prod;\n    }\n\n    std::pair<PersistentDynamicMonoidArray,\
    \ PersistentDynamicMonoidArray> split(int pos) const {\n        assert(0 <= pos\
    \ && pos <= size());\n        auto [l, r] = split_node(root, pos);\n        PersistentDynamicMonoidArray\
    \ left(l, rng_state, pool);\n        PersistentDynamicMonoidArray right(r, rng_state,\
    \ pool);\n        pool->discard_unreferenced();\n        return {std::move(left),\
    \ std::move(right)};\n    }\n\n    PersistentDynamicMonoidArray split_off(int\
    \ pos) const {\n        assert(0 <= pos && pos <= size());\n        return make_version(split_node(root,\
    \ pos).second, rng_state);\n    }\n\n    std::vector<T> to_vector() const {\n\
    \        std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root,\
    \ res);\n        return res;\n    }\n\n    std::vector<T> to_vector(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/segtree/persistent_dual_segtree.hpp\"\n\n\n\n#line 9 \"ds/segtree/persistent_dual_segtree.hpp\"\
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
    \ 1 \"ds/segtree/persistent_dynamic_dual_segtree.hpp\"\n\n\n\n#line 9 \"ds/segtree/persistent_dynamic_dual_segtree.hpp\"\
    \n#include <numeric>\n#include <type_traits>\n#line 13 \"ds/segtree/persistent_dynamic_dual_segtree.hpp\"\
    \n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\n\n\n\n#line 11 \"ds/segtree/dynamic_segtree_common.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\ntemplate <std::integral\
    \ Index>\nusing dynamic_size_type = std::make_unsigned_t<Index>;\n\ntemplate <std::integral\
    \ Index>\nconstexpr dynamic_size_type<Index> dynamic_distance(Index left, Index\
    \ right) {\n    return static_cast<dynamic_size_type<Index>>(right) - static_cast<dynamic_size_type<Index>>(left);\n\
    }\n\ntemplate <class Monoid, class Size>\ntypename Monoid::value_type monoid_repeat(typename\
    \ Monoid::value_type value, Size count) {\n    typename Monoid::value_type result\
    \ = Monoid::id();\n    while (count != 0) {\n        if (count & 1) result = Monoid::op(result,\
    \ value);\n        count >>= 1;\n        if (count != 0) value = Monoid::op(value,\
    \ value);\n    }\n    return result;\n}\n\ntemplate <class ActedMonoid>\ntypename\
    \ ActedMonoid::value_type dynamic_mapping(\n    const typename ActedMonoid::operator_type&\
    \ f,\n    const typename ActedMonoid::value_type& value\n) {\n    using F = typename\
    \ ActedMonoid::operator_type;\n    using T = typename ActedMonoid::value_type;\n\
    \    if constexpr (requires(F g, T x, long long ord) { ActedMonoid::mapping(g,\
    \ x, ord); }) {\n        return ActedMonoid::mapping(f, value, 0);\n    } else\
    \ {\n        return ActedMonoid::mapping(f, value);\n    }\n}\n\ntemplate <class\
    \ ActedMonoid, class Size>\ntypename ActedMonoid::operator_type dynamic_shift(\n\
    \    const typename ActedMonoid::operator_type& f,\n    Size offset\n) {\n   \
    \ using F = typename ActedMonoid::operator_type;\n    if constexpr (requires(F\
    \ g, long long ord) { ActedMonoid::op_shift(g, ord); }) {\n        assert(offset\
    \ <= static_cast<Size>(std::numeric_limits<long long>::max()));\n        return\
    \ ActedMonoid::op_shift(f, static_cast<long long>(offset));\n    } else {\n  \
    \      return f;\n    }\n}\n\ntemplate <class Monoid, std::integral Index>\nclass\
    \ UniformMonoidDomain {\n   public:\n    using T = typename Monoid::value_type;\n\
    \    using size_type = dynamic_size_type<Index>;\n\n   private:\n    struct Level\
    \ {\n        size_type small_length;\n        T small_value;\n        T large_value;\n\
    \    };\n\n    Index _left;\n    Index _right;\n    T _initial_value;\n    std::vector<Level>\
    \ _levels;\n\n   public:\n    UniformMonoidDomain(Index left, Index right, T initial_value)\n\
    \        : _left(left), _right(right), _initial_value(std::move(initial_value))\
    \ {\n        assert(left <= right);\n        size_type n = size();\n        constexpr\
    \ int digits = std::numeric_limits<size_type>::digits;\n        _levels.reserve(digits\
    \ + 1);\n        for (int depth = 0; depth <= digits; depth++) {\n           \
    \ size_type small = depth == digits ? 0 : n >> depth;\n            size_type large\
    \ = small;\n            if (depth != 0) {\n                bool has_remainder;\n\
    \                if (depth == digits) {\n                    has_remainder = n\
    \ != 0;\n                } else {\n                    size_type mask = (size_type(1)\
    \ << depth) - 1;\n                    has_remainder = (n & mask) != 0;\n     \
    \           }\n                if (has_remainder) large++;\n            }\n  \
    \          _levels.push_back(Level{\n                small,\n                monoid_repeat<Monoid>(_initial_value,\
    \ small),\n                monoid_repeat<Monoid>(_initial_value, large),\n   \
    \         });\n        }\n    }\n\n    Index left_bound() const {\n        return\
    \ _left;\n    }\n\n    Index right_bound() const {\n        return _right;\n \
    \   }\n\n    size_type size() const {\n        return dynamic_distance(_left,\
    \ _right);\n    }\n\n    bool empty() const {\n        return _left == _right;\n\
    \    }\n\n    const T& initial_value() const {\n        return _initial_value;\n\
    \    }\n\n    const T& default_product(int depth, Index left, Index right) const\
    \ {\n        assert(0 <= depth && depth < int(_levels.size()));\n        const\
    \ Level& level = _levels[depth];\n        size_type length = dynamic_distance(left,\
    \ right);\n        if (length == level.small_length) return level.small_value;\n\
    \        assert(length == level.small_length + 1);\n        return level.large_value;\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 17 \"ds/segtree/persistent_dynamic_dual_segtree.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A persistent sparse dual segment tree over an integral\
    \ half-open interval.\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral\
    \ Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>, bool>)\n\
    struct PersistentDynamicDualSegtree {\n    using T = typename Monoid::value_type;\n\
    \    using index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T val;\n        int left;\n        int\
    \ right;\n        int references;\n        bool has_lazy;\n\n        Node() :\
    \ val(Monoid::id()), left(0), right(0), references(0), has_lazy(false) {}\n  \
    \  };\n\n    struct Config {\n        Index left;\n        Index right;\n    \
    \    T initial_value;\n\n        Config(Index left_bound, Index right_bound, T\
    \ value)\n            : left(left_bound), right(right_bound), initial_value(std::move(value))\
    \ {\n            assert(left <= right);\n        }\n    };\n\n    std::shared_ptr<const\
    \ Config> _config;\n    using Pool = detail::PersistentNodePool<Node>;\n    std::shared_ptr<Pool>\
    \ _pool;\n    int _root;\n\n    PersistentDynamicDualSegtree(std::shared_ptr<const\
    \ Config> config, std::shared_ptr<Pool> pool, int root)\n        : _config(std::move(config)),\
    \ _pool(std::move(pool)), _root(root) {\n        _pool->retain(_root);\n    }\n\
    \n    int new_node() const { return _pool->emplace(); }\n\n    int clone_or_new(int\
    \ t, bool copy_on_write = false) const {\n        if (!t) return new_node();\n\
    \        return copy_on_write ? _pool->clone_if_shared(t) : _pool->clone(t);\n\
    \    }\n\n    void all_apply_to_node(int t, Index left, Index right, const T&\
    \ x) const {\n        Node& node = (*_pool)[t];\n        if (std::midpoint(left,\
    \ right) == left) {\n            T value = node.has_lazy ? node.val : _config->initial_value;\n\
    \            node.val = Monoid::op(x, value);\n            node.has_lazy = true;\n\
    \        } else {\n            node.val = node.has_lazy ? Monoid::op(x, node.val)\
    \ : x;\n            node.has_lazy = true;\n        }\n    }\n\n    int all_apply_clone(int\
    \ t, Index left, Index right, const T& x, bool copy_on_write = false) const {\n\
    \        int result = clone_or_new(t, copy_on_write);\n        all_apply_to_node(result,\
    \ left, right, x);\n        return result;\n    }\n\n    void push(int t, Index\
    \ left, Index right, bool copy_on_write = false) const {\n        if (!(*_pool)[t].has_lazy)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n\n        T lazy = (*_pool)[t].val;\n        int left_child\
    \ = all_apply_clone((*_pool)[t].left, left, middle, lazy, copy_on_write);\n  \
    \      int right_child = all_apply_clone((*_pool)[t].right, middle, right, lazy,\
    \ copy_on_write);\n\n        Node& node = (*_pool)[t];\n        _pool->replace(node.left,\
    \ left_child);\n        _pool->replace(node.right, right_child);\n        node.val\
    \ = Monoid::id();\n        node.has_lazy = false;\n    }\n\n    int set_node(int\
    \ t, Index left, Index right, Index p, T x, bool copy_on_write = false) const\
    \ {\n        t = clone_or_new(t, copy_on_write);\n        Index middle = std::midpoint(left,\
    \ right);\n        if (middle == left) {\n            Node& node = (*_pool)[t];\n\
    \            node.val = std::move(x);\n            node.has_lazy = true;\n   \
    \         return t;\n        }\n\n        push(t, left, right, copy_on_write);\n\
    \        if (p < middle) {\n            int child = set_node((*_pool)[t].left,\
    \ left, middle, p, std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].left,\
    \ child);\n        } else {\n            int child = set_node((*_pool)[t].right,\
    \ middle, right, p, std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].right,\
    \ child);\n        }\n        return t;\n    }\n\n    int apply_node(int t, Index\
    \ left, Index right, Index query_left, Index query_right, const T& x,\n      \
    \             bool copy_on_write = false) const {\n        if (query_right <=\
    \ left || right <= query_left) return t;\n        if (query_left <= left && right\
    \ <= query_right) {\n            return all_apply_clone(t, left, right, x, copy_on_write);\n\
    \        }\n\n        t = clone_or_new(t, copy_on_write);\n        push(t, left,\
    \ right, copy_on_write);\n        Index middle = std::midpoint(left, right);\n\
    \        int left_child = apply_node((*_pool)[t].left, left, middle, query_left,\
    \ query_right, x, copy_on_write);\n        int right_child = apply_node((*_pool)[t].right,\
    \ middle, right, query_left, query_right, x, copy_on_write);\n        _pool->replace((*_pool)[t].left,\
    \ left_child);\n        _pool->replace((*_pool)[t].right, right_child);\n    \
    \    return t;\n    }\n\n    T compose(const T& inherited, int t) const {\n  \
    \      if (!t || !(*_pool)[t].has_lazy) return inherited;\n        return Monoid::op(inherited,\
    \ (*_pool)[t].val);\n    }\n\n   public:\n    PersistentDynamicDualSegtree() :\
    \ PersistentDynamicDualSegtree(Index(0), Index(0), Monoid::id()) {}\n\n    explicit\
    \ PersistentDynamicDualSegtree(Index n) : PersistentDynamicDualSegtree(Index(0),\
    \ n, Monoid::id()) {\n        if constexpr (std::signed_integral<Index>) assert(Index(0)\
    \ <= n);\n    }\n\n    PersistentDynamicDualSegtree(Index left, Index right) :\
    \ PersistentDynamicDualSegtree(left, right, Monoid::id()) {}\n\n    PersistentDynamicDualSegtree(Index\
    \ left, Index right, T initial_value)\n        : _config(std::make_shared<Config>(left,\
    \ right, std::move(initial_value))),\n          _pool(std::make_shared<Pool>()),\n\
    \          _root(0) {}\n\n    PersistentDynamicDualSegtree(const PersistentDynamicDualSegtree&\
    \ other)\n        : _config(other._config), _pool(other._pool), _root(other._root)\
    \ {\n        if (_pool) _pool->retain(_root);\n    }\n    PersistentDynamicDualSegtree(PersistentDynamicDualSegtree&&\
    \ other) noexcept\n        : _config(std::move(other._config)), _pool(std::move(other._pool)),\
    \ _root(other._root) {\n        other._root = 0;\n    }\n    PersistentDynamicDualSegtree&\
    \ operator=(const PersistentDynamicDualSegtree& other) {\n        if (this ==\
    \ &other) return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _config = other._config;\n\
    \        _pool = other._pool;\n        _root = other._root;\n        return *this;\n\
    \    }\n    PersistentDynamicDualSegtree& operator=(PersistentDynamicDualSegtree&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ _pool->release(_root);\n        _config = std::move(other._config);\n      \
    \  _pool = std::move(other._pool);\n        _root = other._root;\n        other._root\
    \ = 0;\n        return *this;\n    }\n    ~PersistentDynamicDualSegtree() {\n\
    \        if (_pool) _pool->release(_root);\n    }\n\n    size_type size() const\
    \ { return detail::dynamic_distance(_config->left, _config->right); }\n\n    bool\
    \ empty() const { return _config->left == _config->right; }\n\n    Index left_bound()\
    \ const { return _config->left; }\n\n    Index right_bound() const { return _config->right;\
    \ }\n\n    const T& initial_value() const { return _config->initial_value; }\n\
    \n    void reserve(std::size_t node_capacity) const {\n        assert(node_capacity\
    \ < std::numeric_limits<std::size_t>::max());\n        _pool->reserve(node_capacity);\n\
    \    }\n\n    std::size_t node_count() const { return _pool->size(); }\n\n   \
    \ void release() {\n        if (_pool) _pool->release(_root);\n        _pool =\
    \ std::make_shared<Pool>();\n        _root = 0;\n    }\n\n    PersistentDynamicDualSegtree\
    \ set(Index p, T x) const {\n        assert(left_bound() <= p && p < right_bound());\n\
    \        return PersistentDynamicDualSegtree(_config, _pool,\n               \
    \                             set_node(_root, left_bound(), right_bound(), p,\
    \ std::move(x)));\n    }\n\n    void set_inplace(Index p, T x) {\n        assert(left_bound()\
    \ <= p && p < right_bound());\n        int root = set_node(_root, left_bound(),\
    \ right_bound(), p, std::move(x), true);\n        _pool->replace(_root, root);\n\
    \    }\n\n    T get(Index p) const {\n        assert(left_bound() <= p && p <\
    \ right_bound());\n        int t = _root;\n        Index left = left_bound();\n\
    \        Index right = right_bound();\n        T inherited = Monoid::id();\n\n\
    \        while (t) {\n            Index middle = std::midpoint(left, right);\n\
    \            if (middle == left) {\n                T value = (*_pool)[t].has_lazy\
    \ ? (*_pool)[t].val : initial_value();\n                return Monoid::op(inherited,\
    \ value);\n            }\n            inherited = compose(inherited, t);\n   \
    \         if (p < middle) {\n                t = (*_pool)[t].left;\n         \
    \       right = middle;\n            } else {\n                t = (*_pool)[t].right;\n\
    \                left = middle;\n            }\n        }\n        return Monoid::op(inherited,\
    \ initial_value());\n    }\n\n    T operator[](Index p) const { return get(p);\
    \ }\n\n    PersistentDynamicDualSegtree apply(Index p, const T& x) const {\n \
    \       assert(left_bound() <= p && p < right_bound());\n        return apply(p,\
    \ p + 1, x);\n    }\n\n    PersistentDynamicDualSegtree apply(Index left, Index\
    \ right, const T& x) const {\n        assert(left_bound() <= left && left <= right\
    \ && right <= right_bound());\n        if (left == right) return *this;\n    \
    \    return PersistentDynamicDualSegtree(_config, _pool,\n                   \
    \                         apply_node(_root, left_bound(), right_bound(), left,\
    \ right, x));\n    }\n\n    void apply_inplace(Index p, const T& x) {\n      \
    \  assert(left_bound() <= p && p < right_bound());\n        apply_inplace(p, p\
    \ + 1, x);\n    }\n\n    void apply_inplace(Index left, Index right, const T&\
    \ x) {\n        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return;\n        int root = apply_node(_root, left_bound(),\
    \ right_bound(), left, right, x, true);\n        _pool->replace(_root, root);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/persistent_dynamic_lazy_segtree.hpp\"\
    \n\n\n\n#line 13 \"ds/segtree/persistent_dynamic_lazy_segtree.hpp\"\n\n#line 17\
    \ \"ds/segtree/persistent_dynamic_lazy_segtree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\n// A persistent sparse lazy segment tree over an integral half-open\
    \ interval.\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid, std::integral\
    \ Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>, bool>)\n\
    struct PersistentDynamicLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n    using index_type = Index;\n\
    \    using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        F lazy;\n        int left;\n        int right;\n\
    \        int references;\n        bool has_lazy;\n\n        Node()\n         \
    \   : val(ActedMonoid::id()), lazy(ActedMonoid::op_id()), left(0), right(0), references(0),\
    \ has_lazy(false) {}\n        explicit Node(T value)\n            : val(std::move(value)),\
    \ lazy(ActedMonoid::op_id()), left(0), right(0), references(0), has_lazy(false)\
    \ {}\n    };\n\n    struct Config {\n        detail::UniformMonoidDomain<ActedMonoid,\
    \ Index> domain;\n\n        Config(Index left, Index right, T initial_value) :\
    \ domain(left, right, std::move(initial_value)) {}\n    };\n\n    std::shared_ptr<const\
    \ Config> _config;\n    using Pool = detail::PersistentNodePool<Node>;\n    std::shared_ptr<Pool>\
    \ _pool;\n    int _root;\n\n    PersistentDynamicLazySegtree(std::shared_ptr<const\
    \ Config> config, std::shared_ptr<Pool> pool, int root)\n        : _config(std::move(config)),\
    \ _pool(std::move(pool)), _root(root) {\n        _pool->retain(_root);\n    }\n\
    \n    int new_node(Index left, Index right, int depth) const {\n        return\
    \ _pool->emplace(_config->domain.default_product(depth, left, right));\n    }\n\
    \n    int clone_or_new(int t, Index left, Index right, int depth, bool copy_on_write\
    \ = false) const {\n        if (!t) return new_node(left, right, depth);\n   \
    \     return copy_on_write ? _pool->clone_if_shared(t) : _pool->clone(t);\n  \
    \  }\n\n    const T& value(int t, Index left, Index right, int depth) const {\n\
    \        if (t) return (*_pool)[t].val;\n        return _config->domain.default_product(depth,\
    \ left, right);\n    }\n\n    void all_apply_to_node(int t, Index left, Index\
    \ right, const F& f) const {\n        Node& node = (*_pool)[t];\n        node.val\
    \ = detail::dynamic_mapping<ActedMonoid>(f, node.val);\n        if (std::midpoint(left,\
    \ right) != left) {\n            node.lazy = ActedMonoid::op_comp(f, node.lazy);\n\
    \            node.has_lazy = true;\n        }\n    }\n\n    int all_apply_clone(int\
    \ t, Index left, Index right, int depth, const F& f,\n                       \
    \ bool copy_on_write = false) const {\n        int result = clone_or_new(t, left,\
    \ right, depth, copy_on_write);\n        all_apply_to_node(result, left, right,\
    \ f);\n        return result;\n    }\n\n    void push(int t, Index left, Index\
    \ right, int depth, bool copy_on_write = false) const {\n        if (!(*_pool)[t].has_lazy)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n\n        F lazy = (*_pool)[t].lazy;\n        int left_child\
    \ = all_apply_clone((*_pool)[t].left, left, middle, depth + 1, lazy, copy_on_write);\n\
    \        int right_child =\n            all_apply_clone((*_pool)[t].right, middle,\
    \ right, depth + 1,\n                            detail::dynamic_shift<ActedMonoid>(lazy,\
    \ detail::dynamic_distance(left, middle)),\n                            copy_on_write);\n\
    \n        Node& node = (*_pool)[t];\n        _pool->replace(node.left, left_child);\n\
    \        _pool->replace(node.right, right_child);\n        node.lazy = ActedMonoid::op_id();\n\
    \        node.has_lazy = false;\n    }\n\n    void update(int t, Index left, Index\
    \ right, int depth) const {\n        Index middle = std::midpoint(left, right);\n\
    \        Node& node = (*_pool)[t];\n        node.val =\n            ActedMonoid::op(value(node.left,\
    \ left, middle, depth + 1), value(node.right, middle, right, depth + 1));\n  \
    \  }\n\n    int set_node(int t, Index left, Index right, int depth, Index p, T\
    \ x,\n                 bool copy_on_write = false) const {\n        t = clone_or_new(t,\
    \ left, right, depth, copy_on_write);\n        Index middle = std::midpoint(left,\
    \ right);\n        if (middle == left) {\n            Node& node = (*_pool)[t];\n\
    \            node.val = std::move(x);\n            node.lazy = ActedMonoid::op_id();\n\
    \            node.has_lazy = false;\n            return t;\n        }\n\n    \
    \    push(t, left, right, depth, copy_on_write);\n        if (p < middle) {\n\
    \            int child = set_node((*_pool)[t].left, left, middle, depth + 1, p,\
    \ std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].left,\
    \ child);\n        } else {\n            int child = set_node((*_pool)[t].right,\
    \ middle, right, depth + 1, p, std::move(x), copy_on_write);\n            _pool->replace((*_pool)[t].right,\
    \ child);\n        }\n        update(t, left, right, depth);\n        return t;\n\
    \    }\n\n    int apply_node(int t, Index left, Index right, int depth, Index\
    \ query_left, Index query_right, const F& f,\n                   bool copy_on_write\
    \ = false) const {\n        if (query_right <= left || right <= query_left) return\
    \ t;\n        if (query_left <= left && right <= query_right) {\n            return\
    \ all_apply_clone(t, left, right, depth,\n                                   detail::dynamic_shift<ActedMonoid>(f,\
    \ detail::dynamic_distance(query_left, left)),\n                             \
    \      copy_on_write);\n        }\n\n        t = clone_or_new(t, left, right,\
    \ depth, copy_on_write);\n        push(t, left, right, depth, copy_on_write);\n\
    \        Index middle = std::midpoint(left, right);\n        int left_child =\
    \ apply_node((*_pool)[t].left, left, middle, depth + 1, query_left, query_right,\
    \ f,\n                                    copy_on_write);\n        int right_child\
    \ = apply_node((*_pool)[t].right, middle, right, depth + 1, query_left, query_right,\
    \ f,\n                                     copy_on_write);\n        _pool->replace((*_pool)[t].left,\
    \ left_child);\n        _pool->replace((*_pool)[t].right, right_child);\n    \
    \    update(t, left, right, depth);\n        return t;\n    }\n\n    F compose_for_child(const\
    \ F& inherited, int t, size_type offset) const {\n        F shifted = detail::dynamic_shift<ActedMonoid>(inherited,\
    \ offset);\n        if (!t || !(*_pool)[t].has_lazy) return shifted;\n       \
    \ return ActedMonoid::op_comp(shifted, detail::dynamic_shift<ActedMonoid>((*_pool)[t].lazy,\
    \ offset));\n    }\n\n    T prod_node(int t, Index left, Index right, int depth,\
    \ Index query_left, Index query_right,\n                const F& inherited) const\
    \ {\n        if (query_right <= left || right <= query_left) return ActedMonoid::id();\n\
    \        if (query_left <= left && right <= query_right) {\n            return\
    \ detail::dynamic_mapping<ActedMonoid>(inherited, value(t, left, right, depth));\n\
    \        }\n        Index middle = std::midpoint(left, right);\n        return\
    \ ActedMonoid::op(prod_node(t ? (*_pool)[t].left : 0, left, middle, depth + 1,\
    \ query_left, query_right,\n                                         compose_for_child(inherited,\
    \ t, 0)),\n                               prod_node(t ? (*_pool)[t].right : 0,\
    \ middle, right, depth + 1, query_left, query_right,\n                       \
    \                  compose_for_child(inherited, t, detail::dynamic_distance(left,\
    \ middle))));\n    }\n\n    template <class G>\n    Index max_right_node(int t,\
    \ Index left, Index right, int depth, Index query_left, T& product, const F& inherited,\n\
    \                         G& predicate) const {\n        if (right <= query_left)\
    \ return right;\n        if (query_left <= left) {\n            T next =\n   \
    \             ActedMonoid::op(product, detail::dynamic_mapping<ActedMonoid>(inherited,\
    \ value(t, left, right, depth)));\n            if (predicate(next)) {\n      \
    \          product = std::move(next);\n                return right;\n       \
    \     }\n            Index middle = std::midpoint(left, right);\n            if\
    \ (middle == left) return left;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = max_right_node(t ? (*_pool)[t].left : 0, left,\
    \ middle, depth + 1, query_left, product,\n                                  \
    \    compose_for_child(inherited, t, 0), predicate);\n        if (result < middle)\
    \ return result;\n        return max_right_node(t ? (*_pool)[t].right : 0, middle,\
    \ right, depth + 1, query_left, product,\n                              compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)), predicate);\n    }\n\n    template\
    \ <class G>\n    Index min_left_node(int t, Index left, Index right, int depth,\
    \ Index query_right, T& product, const F& inherited,\n                       \
    \ G& predicate) const {\n        if (query_right <= left) return left;\n     \
    \   if (right <= query_right) {\n            T next =\n                ActedMonoid::op(detail::dynamic_mapping<ActedMonoid>(inherited,\
    \ value(t, left, right, depth)), product);\n            if (predicate(next)) {\n\
    \                product = std::move(next);\n                return left;\n  \
    \          }\n            Index middle = std::midpoint(left, right);\n       \
    \     if (middle == left) return right;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result =\n            min_left_node(t ? (*_pool)[t].right\
    \ : 0, middle, right, depth + 1, query_right, product,\n                     \
    \     compose_for_child(inherited, t, detail::dynamic_distance(left, middle)),\
    \ predicate);\n        if (middle < result) return result;\n        return min_left_node(t\
    \ ? (*_pool)[t].left : 0, left, middle, depth + 1, query_right, product,\n   \
    \                          compose_for_child(inherited, t, 0), predicate);\n \
    \   }\n\n   public:\n    PersistentDynamicLazySegtree() : PersistentDynamicLazySegtree(Index(0),\
    \ Index(0), ActedMonoid::id()) {}\n\n    explicit PersistentDynamicLazySegtree(Index\
    \ n) : PersistentDynamicLazySegtree(Index(0), n, ActedMonoid::id()) {\n      \
    \  if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n    }\n\n\
    \    PersistentDynamicLazySegtree(Index left, Index right)\n        : PersistentDynamicLazySegtree(left,\
    \ right, ActedMonoid::id()) {}\n\n    PersistentDynamicLazySegtree(Index left,\
    \ Index right, T initial_value)\n        : _config(std::make_shared<Config>(left,\
    \ right, std::move(initial_value))),\n          _pool(std::make_shared<Pool>()),\n\
    \          _root(0) {}\n\n    PersistentDynamicLazySegtree(const PersistentDynamicLazySegtree&\
    \ other)\n        : _config(other._config), _pool(other._pool), _root(other._root)\
    \ {\n        if (_pool) _pool->retain(_root);\n    }\n    PersistentDynamicLazySegtree(PersistentDynamicLazySegtree&&\
    \ other) noexcept\n        : _config(std::move(other._config)), _pool(std::move(other._pool)),\
    \ _root(other._root) {\n        other._root = 0;\n    }\n    PersistentDynamicLazySegtree&\
    \ operator=(const PersistentDynamicLazySegtree& other) {\n        if (this ==\
    \ &other) return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _config = other._config;\n\
    \        _pool = other._pool;\n        _root = other._root;\n        return *this;\n\
    \    }\n    PersistentDynamicLazySegtree& operator=(PersistentDynamicLazySegtree&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ _pool->release(_root);\n        _config = std::move(other._config);\n      \
    \  _pool = std::move(other._pool);\n        _root = other._root;\n        other._root\
    \ = 0;\n        return *this;\n    }\n    ~PersistentDynamicLazySegtree() {\n\
    \        if (_pool) _pool->release(_root);\n    }\n\n    size_type size() const\
    \ { return _config->domain.size(); }\n\n    bool empty() const { return _config->domain.empty();\
    \ }\n\n    Index left_bound() const { return _config->domain.left_bound(); }\n\
    \n    Index right_bound() const { return _config->domain.right_bound(); }\n\n\
    \    const T& initial_value() const { return _config->domain.initial_value();\
    \ }\n\n    void reserve(std::size_t node_capacity) const {\n        assert(node_capacity\
    \ < std::numeric_limits<std::size_t>::max());\n        _pool->reserve(node_capacity);\n\
    \    }\n\n    std::size_t node_count() const { return _pool->size(); }\n\n   \
    \ void release() {\n        if (_pool) _pool->release(_root);\n        _pool =\
    \ std::make_shared<Pool>();\n        _root = 0;\n    }\n\n    PersistentDynamicLazySegtree\
    \ set(Index p, T x) const {\n        assert(left_bound() <= p && p < right_bound());\n\
    \        return PersistentDynamicLazySegtree(_config, _pool,\n               \
    \                             set_node(_root, left_bound(), right_bound(), 0,\
    \ p, std::move(x)));\n    }\n\n    void set_inplace(Index p, T x) {\n        assert(left_bound()\
    \ <= p && p < right_bound());\n        int root = set_node(_root, left_bound(),\
    \ right_bound(), 0, p, std::move(x), true);\n        _pool->replace(_root, root);\n\
    \    }\n\n    T get(Index p) const {\n        assert(left_bound() <= p && p <\
    \ right_bound());\n        return prod(p, p + 1);\n    }\n\n    T operator[](Index\
    \ p) const { return get(p); }\n\n    T prod(Index left, Index right) const {\n\
    \        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return ActedMonoid::id();\n        return prod_node(_root,\
    \ left_bound(), right_bound(), 0, left, right, ActedMonoid::op_id());\n    }\n\
    \n    T all_prod() const { return value(_root, left_bound(), right_bound(), 0);\
    \ }\n\n    PersistentDynamicLazySegtree apply(Index p, const F& f) const {\n \
    \       assert(left_bound() <= p && p < right_bound());\n        return apply(p,\
    \ p + 1, f);\n    }\n\n    PersistentDynamicLazySegtree apply(Index left, Index\
    \ right, const F& f) const {\n        assert(left_bound() <= left && left <= right\
    \ && right <= right_bound());\n        if (left == right) return *this;\n    \
    \    return PersistentDynamicLazySegtree(_config, _pool,\n                   \
    \                         apply_node(_root, left_bound(), right_bound(), 0, left,\
    \ right, f));\n    }\n\n    void apply_inplace(Index p, const F& f) {\n      \
    \  assert(left_bound() <= p && p < right_bound());\n        apply_inplace(p, p\
    \ + 1, f);\n    }\n\n    void apply_inplace(Index left, Index right, const F&\
    \ f) {\n        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return;\n        int root = apply_node(_root, left_bound(),\
    \ right_bound(), 0, left, right, f, true);\n        _pool->replace(_root, root);\n\
    \    }\n\n    template <class G>\n    Index max_right(Index left, G predicate)\
    \ const {\n        assert(left_bound() <= left && left <= right_bound());\n  \
    \      assert(predicate(ActedMonoid::id()));\n        if (left == right_bound())\
    \ return right_bound();\n        T product = ActedMonoid::id();\n        return\
    \ max_right_node(_root, left_bound(), right_bound(), 0, left, product, ActedMonoid::op_id(),\
    \ predicate);\n    }\n\n    template <class G>\n    Index min_left(Index right,\
    \ G predicate) const {\n        assert(left_bound() <= right && right <= right_bound());\n\
    \        assert(predicate(ActedMonoid::id()));\n        if (right == left_bound())\
    \ return left_bound();\n        T product = ActedMonoid::id();\n        return\
    \ min_left_node(_root, left_bound(), right_bound(), 0, right, product, ActedMonoid::op_id(),\
    \ predicate);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line\
    \ 1 \"ds/segtree/persistent_dynamic_segtree.hpp\"\n\n\n\n#line 13 \"ds/segtree/persistent_dynamic_segtree.hpp\"\
    \n\n#line 17 \"ds/segtree/persistent_dynamic_segtree.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A persistent sparse segment tree over an integral half-open\
    \ interval.\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral Index = long\
    \ long>\n    requires(!std::same_as<std::remove_cv_t<Index>, bool>)\nstruct PersistentDynamicSegtree\
    \ {\n    using T = typename Monoid::value_type;\n    using index_type = Index;\n\
    \    using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        int left;\n        int right;\n        int references;\n\
    \n        Node() : val(Monoid::id()), left(0), right(0), references(0) {}\n  \
    \      explicit Node(T value) : val(std::move(value)), left(0), right(0), references(0)\
    \ {}\n    };\n\n    struct Config {\n        detail::UniformMonoidDomain<Monoid,\
    \ Index> domain;\n\n        Config(Index left, Index right, T initial_value) :\
    \ domain(left, right, std::move(initial_value)) {}\n    };\n\n    std::shared_ptr<const\
    \ Config> _config;\n    using Pool = detail::PersistentNodePool<Node>;\n    std::shared_ptr<Pool>\
    \ _pool;\n    int _root;\n\n    PersistentDynamicSegtree(std::shared_ptr<const\
    \ Config> config, std::shared_ptr<Pool> pool, int root)\n        : _config(std::move(config)),\
    \ _pool(std::move(pool)), _root(root) {\n        _pool->retain(_root);\n    }\n\
    \n    int new_node(T value) const { return _pool->emplace(std::move(value)); }\n\
    \n    const T& value(int t, Index left, Index right, int depth) const {\n    \
    \    if (t) return (*_pool)[t].val;\n        return _config->domain.default_product(depth,\
    \ left, right);\n    }\n\n    int set_node(int t, Index left, Index right, int\
    \ depth, Index p, T x, bool copy_on_write = false) const {\n        Index middle\
    \ = std::midpoint(left, right);\n        if (copy_on_write) {\n            int\
    \ result = t ? _pool->clone_if_shared(t) : new_node(value(0, left, right, depth));\n\
    \            if (middle == left) {\n                (*_pool)[result].val = std::move(x);\n\
    \                return result;\n            }\n            int child;\n     \
    \       if (p < middle) {\n                child = set_node((*_pool)[result].left,\
    \ left, middle, depth + 1, p, std::move(x), true);\n                _pool->replace((*_pool)[result].left,\
    \ child);\n            } else {\n                child = set_node((*_pool)[result].right,\
    \ middle, right, depth + 1, p, std::move(x), true);\n                _pool->replace((*_pool)[result].right,\
    \ child);\n            }\n            Node& node = (*_pool)[result];\n       \
    \     node.val = Monoid::op(value(node.left, left, middle, depth + 1),\n     \
    \                             value(node.right, middle, right, depth + 1));\n\
    \            return result;\n        }\n        if (middle == left) return new_node(std::move(x));\n\
    \n        int left_child = t ? (*_pool)[t].left : 0;\n        int right_child\
    \ = t ? (*_pool)[t].right : 0;\n        if (p < middle) {\n            left_child\
    \ = set_node(left_child, left, middle, depth + 1, p, std::move(x));\n        }\
    \ else {\n            right_child = set_node(right_child, middle, right, depth\
    \ + 1, p, std::move(x));\n        }\n\n        int result = new_node(\n      \
    \      Monoid::op(value(left_child, left, middle, depth + 1), value(right_child,\
    \ middle, right, depth + 1)));\n        _pool->replace((*_pool)[result].left,\
    \ left_child);\n        _pool->replace((*_pool)[result].right, right_child);\n\
    \        return result;\n    }\n\n    T prod_node(int t, Index left, Index right,\
    \ int depth, Index query_left, Index query_right) const {\n        if (query_right\
    \ <= left || right <= query_left) return Monoid::id();\n        if (query_left\
    \ <= left && right <= query_right) {\n            return value(t, left, right,\
    \ depth);\n        }\n        Index middle = std::midpoint(left, right);\n   \
    \     return Monoid::op(prod_node(t ? (*_pool)[t].left : 0, left, middle, depth\
    \ + 1, query_left, query_right),\n                          prod_node(t ? (*_pool)[t].right\
    \ : 0, middle, right, depth + 1, query_left, query_right));\n    }\n\n    template\
    \ <class F>\n    Index max_right_node(int t, Index left, Index right, int depth,\
    \ Index query_left, T& product, F& predicate) const {\n        if (right <= query_left)\
    \ return right;\n        if (query_left <= left) {\n            T next = Monoid::op(product,\
    \ value(t, left, right, depth));\n            if (predicate(next)) {\n       \
    \         product = std::move(next);\n                return right;\n        \
    \    }\n            Index middle = std::midpoint(left, right);\n            if\
    \ (middle == left) return left;\n        }\n\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result =\n            max_right_node(t ? (*_pool)[t].left\
    \ : 0, left, middle, depth + 1, query_left, product, predicate);\n        if (result\
    \ < middle) return result;\n        return max_right_node(t ? (*_pool)[t].right\
    \ : 0, middle, right, depth + 1, query_left, product, predicate);\n    }\n\n \
    \   template <class F>\n    Index min_left_node(int t, Index left, Index right,\
    \ int depth, Index query_right, T& product, F& predicate) const {\n        if\
    \ (query_right <= left) return left;\n        if (right <= query_right) {\n  \
    \          T next = Monoid::op(value(t, left, right, depth), product);\n     \
    \       if (predicate(next)) {\n                product = std::move(next);\n \
    \               return left;\n            }\n            Index middle = std::midpoint(left,\
    \ right);\n            if (middle == left) return right;\n        }\n\n      \
    \  Index middle = std::midpoint(left, right);\n        Index result =\n      \
    \      min_left_node(t ? (*_pool)[t].right : 0, middle, right, depth + 1, query_right,\
    \ product, predicate);\n        if (middle < result) return result;\n        return\
    \ min_left_node(t ? (*_pool)[t].left : 0, left, middle, depth + 1, query_right,\
    \ product, predicate);\n    }\n\n   public:\n    PersistentDynamicSegtree() :\
    \ PersistentDynamicSegtree(Index(0), Index(0), Monoid::id()) {}\n\n    explicit\
    \ PersistentDynamicSegtree(Index n) : PersistentDynamicSegtree(Index(0), n, Monoid::id())\
    \ {\n        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n\
    \    }\n\n    PersistentDynamicSegtree(Index left, Index right) : PersistentDynamicSegtree(left,\
    \ right, Monoid::id()) {}\n\n    PersistentDynamicSegtree(Index left, Index right,\
    \ T initial_value)\n        : _config(std::make_shared<Config>(left, right, std::move(initial_value))),\n\
    \          _pool(std::make_shared<Pool>()),\n          _root(0) {}\n\n    PersistentDynamicSegtree(const\
    \ PersistentDynamicSegtree& other)\n        : _config(other._config), _pool(other._pool),\
    \ _root(other._root) {\n        if (_pool) _pool->retain(_root);\n    }\n    PersistentDynamicSegtree(PersistentDynamicSegtree&&\
    \ other) noexcept\n        : _config(std::move(other._config)), _pool(std::move(other._pool)),\
    \ _root(other._root) {\n        other._root = 0;\n    }\n    PersistentDynamicSegtree&\
    \ operator=(const PersistentDynamicSegtree& other) {\n        if (this == &other)\
    \ return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _config = other._config;\n\
    \        _pool = other._pool;\n        _root = other._root;\n        return *this;\n\
    \    }\n    PersistentDynamicSegtree& operator=(PersistentDynamicSegtree&& other)\
    \ noexcept {\n        if (this == &other) return *this;\n        if (_pool) _pool->release(_root);\n\
    \        _config = std::move(other._config);\n        _pool = std::move(other._pool);\n\
    \        _root = other._root;\n        other._root = 0;\n        return *this;\n\
    \    }\n    ~PersistentDynamicSegtree() {\n        if (_pool) _pool->release(_root);\n\
    \    }\n\n    size_type size() const { return _config->domain.size(); }\n\n  \
    \  bool empty() const { return _config->domain.empty(); }\n\n    Index left_bound()\
    \ const { return _config->domain.left_bound(); }\n\n    Index right_bound() const\
    \ { return _config->domain.right_bound(); }\n\n    const T& initial_value() const\
    \ { return _config->domain.initial_value(); }\n\n    void reserve(std::size_t\
    \ node_capacity) const {\n        assert(node_capacity < std::numeric_limits<std::size_t>::max());\n\
    \        _pool->reserve(node_capacity);\n    }\n\n    std::size_t node_count()\
    \ const { return _pool->size(); }\n\n    void release() {\n        if (_pool)\
    \ _pool->release(_root);\n        _pool = std::make_shared<Pool>();\n        _root\
    \ = 0;\n    }\n\n    PersistentDynamicSegtree set(Index p, T x) const {\n    \
    \    assert(left_bound() <= p && p < right_bound());\n        return PersistentDynamicSegtree(_config,\
    \ _pool,\n                                        set_node(_root, left_bound(),\
    \ right_bound(), 0, p, std::move(x)));\n    }\n\n    void set_inplace(Index p,\
    \ T x) {\n        assert(left_bound() <= p && p < right_bound());\n        int\
    \ root = set_node(_root, left_bound(), right_bound(), 0, p, std::move(x), true);\n\
    \        _pool->replace(_root, root);\n    }\n\n    T get(Index p) const {\n \
    \       assert(left_bound() <= p && p < right_bound());\n        int t = _root;\n\
    \        Index left = left_bound();\n        Index right = right_bound();\n\n\
    \        while (t) {\n            Index middle = std::midpoint(left, right);\n\
    \            if (middle == left) return (*_pool)[t].val;\n            if (p <\
    \ middle) {\n                t = (*_pool)[t].left;\n                right = middle;\n\
    \            } else {\n                t = (*_pool)[t].right;\n              \
    \  left = middle;\n            }\n        }\n        return initial_value();\n\
    \    }\n\n    T operator[](Index p) const { return get(p); }\n\n    T prod(Index\
    \ left, Index right) const {\n        assert(left_bound() <= left && left <= right\
    \ && right <= right_bound());\n        if (left == right) return Monoid::id();\n\
    \        return prod_node(_root, left_bound(), right_bound(), 0, left, right);\n\
    \    }\n\n    T all_prod() const { return value(_root, left_bound(), right_bound(),\
    \ 0); }\n\n    template <class F>\n    Index max_right(Index left, F predicate)\
    \ const {\n        assert(left_bound() <= left && left <= right_bound());\n  \
    \      assert(predicate(Monoid::id()));\n        if (left == right_bound()) return\
    \ right_bound();\n        T product = Monoid::id();\n        return max_right_node(_root,\
    \ left_bound(), right_bound(), 0, left, product, predicate);\n    }\n\n    template\
    \ <class F>\n    Index min_left(Index right, F predicate) const {\n        assert(left_bound()\
    \ <= right && right <= right_bound());\n        assert(predicate(Monoid::id()));\n\
    \        if (right == left_bound()) return left_bound();\n        T product =\
    \ Monoid::id();\n        return min_left_node(_root, left_bound(), right_bound(),\
    \ 0, right, product, predicate);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 1 \"ds/segtree/persistent_lazy_segtree.hpp\"\n\n\n\n#line 9\
    \ \"ds/segtree/persistent_lazy_segtree.hpp\"\n\n#line 12 \"ds/segtree/persistent_lazy_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct PersistentLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        F lazy;\n        int left, right;\n        int\
    \ references;\n        bool has_lazy;\n\n        Node()\n            : val(ActedMonoid::id()),\
    \ lazy(ActedMonoid::op_id()), left(0), right(0), references(0), has_lazy(false)\
    \ {}\n        explicit Node(T value)\n            : val(std::move(value)), lazy(ActedMonoid::op_id()),\
    \ left(0), right(0), references(0), has_lazy(false) {}\n        Node(T value,\
    \ int left_child, int right_child)\n            : val(std::move(value)),\n   \
    \           lazy(ActedMonoid::op_id()),\n              left(left_child),\n   \
    \           right(right_child),\n              references(0),\n              has_lazy(false)\
    \ {}\n    };\n\n    using Pool = detail::PersistentNodePool<Node>;\n\n    int\
    \ _n;\n    int _root;\n    std::shared_ptr<Pool> _pool;\n\n    explicit PersistentLazySegtree(int\
    \ n, int root, std::shared_ptr<Pool> pool)\n        : _n(n), _root(root), _pool(std::move(pool))\
    \ {\n        _pool->retain(_root);\n    }\n\n    int new_node(const Node& node)\
    \ const { return _pool->emplace(node); }\n\n    int new_node(Node&& node) const\
    \ { return _pool->emplace(std::move(node)); }\n\n    int clone_node(int t) const\
    \ { return _pool->clone(t); }\n\n    template <typename U>\n    static T make_value(const\
    \ U& value, int index) {\n        if constexpr (requires(U x) { ActedMonoid::make(x);\
    \ }) {\n            return ActedMonoid::make(value);\n        } else if constexpr\
    \ (requires(U x, int i) { ActedMonoid::make(x, i); }) {\n            return ActedMonoid::make(value,\
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
    \ g);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"\
    ds/segtree/persistent_segtree.hpp\"\n\n\n\n#line 9 \"ds/segtree/persistent_segtree.hpp\"\
    \n\n#line 12 \"ds/segtree/persistent_segtree.hpp\"\n\nnamespace m1une {\nnamespace\
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
    \n#line 1 \"ds/segtree/persistent_segtree_beats.hpp\"\n\n\n\n#line 10 \"ds/segtree/persistent_segtree_beats.hpp\"\
    \n\n#line 1 \"beats_acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"beats_acted_monoid/concept.hpp\"\
    \n\n#line 7 \"beats_acted_monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace\
    \ beats_acted_monoid {\n\n// An acted monoid whose action may require descent\
    \ before it can be applied.\ntemplate <typename AM>\nconcept IsBeatsActedMonoid\
    \ = m1une::acted_monoid::IsActedMonoid<AM> &&\n    requires(typename AM::value_type\
    \ x, typename AM::operator_type f) {\n        { AM::can_apply(f, x) } -> std::same_as<bool>;\n\
    \    };\n\n}  // namespace beats_acted_monoid\n}  // namespace m1une\n\n\n#line\
    \ 13 \"ds/segtree/persistent_segtree_beats.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\n// A persistent Segment Tree Beats for fallible monoid actions.\ntemplate\
    \ <m1une::beats_acted_monoid::IsBeatsActedMonoid ActedMonoid>\nstruct PersistentSegtreeBeats\
    \ {\n    using value_type = typename ActedMonoid::value_type;\n    using operator_type\
    \ = typename ActedMonoid::operator_type;\n    using T = value_type;\n    using\
    \ F = operator_type;\n\n   private:\n    struct Node {\n        T val;\n     \
    \   F lazy;\n        int left;\n        int right;\n        int references;\n\
    \        bool has_lazy;\n\n        Node()\n            : val(ActedMonoid::id()),\n\
    \              lazy(ActedMonoid::op_id()),\n              left(0),\n         \
    \     right(0),\n              references(0),\n              has_lazy(false) {}\n\
    \n        explicit Node(T value)\n            : val(std::move(value)),\n     \
    \         lazy(ActedMonoid::op_id()),\n              left(0),\n              right(0),\n\
    \              references(0),\n              has_lazy(false) {}\n\n        Node(T\
    \ value, int left_child, int right_child)\n            : val(std::move(value)),\n\
    \              lazy(ActedMonoid::op_id()),\n              left(left_child),\n\
    \              right(right_child),\n              references(0),\n           \
    \   has_lazy(false) {}\n    };\n\n    using Pool = detail::PersistentNodePool<Node>;\n\
    \n    int _n;\n    int _root;\n    std::shared_ptr<Pool> _pool;\n\n    explicit\
    \ PersistentSegtreeBeats(\n        int n,\n        int root,\n        std::shared_ptr<Pool>\
    \ pool\n    ) : _n(n), _root(root), _pool(std::move(pool)) {\n        _pool->retain(_root);\n\
    \    }\n\n    int new_node(const Node& node) const {\n        return _pool->emplace(node);\n\
    \    }\n\n    int new_node(Node&& node) const {\n        return _pool->emplace(std::move(node));\n\
    \    }\n\n    int clone_node(int node) const {\n        return _pool->clone(node);\n\
    \    }\n\n    template <typename U>\n    static T make_value(const U& value, int\
    \ index) {\n        if constexpr (requires(U x) { ActedMonoid::make(x); }) {\n\
    \            return ActedMonoid::make(value);\n        } else if constexpr (requires(U\
    \ x, int i) {\n            ActedMonoid::make(x, i);\n        }) {\n          \
    \  return ActedMonoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n    static T mapping_at(const F&\
    \ f, const T& value, long long ordinal) {\n        if constexpr (requires(F g,\
    \ T x, long long i) {\n            ActedMonoid::mapping(g, x, i);\n        })\
    \ {\n            return ActedMonoid::mapping(f, value, ordinal);\n        } else\
    \ {\n            return ActedMonoid::mapping(f, value);\n        }\n    }\n\n\
    \    static bool can_apply_at(\n        const F& f,\n        const T& value,\n\
    \        long long ordinal\n    ) {\n        if constexpr (requires(F g, T x,\
    \ long long i) {\n            ActedMonoid::can_apply(g, x, i);\n        }) {\n\
    \            return ActedMonoid::can_apply(f, value, ordinal);\n        } else\
    \ {\n            return ActedMonoid::can_apply(f, value);\n        }\n    }\n\n\
    \    static F shift_operator(const F& f, long long ordinal) {\n        if constexpr\
    \ (requires(F g, long long i) {\n            ActedMonoid::op_shift(g, i);\n  \
    \      }) {\n            return ActedMonoid::op_shift(f, ordinal);\n        }\
    \ else {\n            return f;\n        }\n    }\n\n    int build(int left, int\
    \ right, const std::vector<T>& values) const {\n        if (left == right) return\
    \ 0;\n        if (right - left == 1) return new_node(Node(values[left]));\n  \
    \      int middle = left + (right - left) / 2;\n        int left_child = build(left,\
    \ middle, values);\n        int right_child = build(middle, right, values);\n\
    \        return new_node(Node(\n            ActedMonoid::op(\n               \
    \ (*_pool)[left_child].val,\n                (*_pool)[right_child].val\n     \
    \       ),\n            left_child,\n            right_child\n        ));\n  \
    \  }\n\n    int build(int left, int right, std::vector<T>& values) const {\n \
    \       if (left == right) return 0;\n        if (right - left == 1) {\n     \
    \       return new_node(Node(std::move(values[left])));\n        }\n        int\
    \ middle = left + (right - left) / 2;\n        int left_child = build(left, middle,\
    \ values);\n        int right_child = build(middle, right, values);\n        return\
    \ new_node(Node(\n            ActedMonoid::op(\n                (*_pool)[left_child].val,\n\
    \                (*_pool)[right_child].val\n            ),\n            left_child,\n\
    \            right_child\n        ));\n    }\n\n    template <typename U>\n  \
    \  int build_from_values(\n        int left,\n        int right,\n        const\
    \ std::vector<U>& values\n    ) const {\n        if (left == right) return 0;\n\
    \        if (right - left == 1) {\n            return new_node(Node(make_value(values[left],\
    \ left)));\n        }\n        int middle = left + (right - left) / 2;\n     \
    \   int left_child = build_from_values(left, middle, values);\n        int right_child\
    \ = build_from_values(middle, right, values);\n        return new_node(Node(\n\
    \            ActedMonoid::op(\n                (*_pool)[left_child].val,\n   \
    \             (*_pool)[right_child].val\n            ),\n            left_child,\n\
    \            right_child\n        ));\n    }\n\n    void update(int node) const\
    \ {\n        Node& current = (*_pool)[node];\n        current.val = ActedMonoid::op(\n\
    \            (*_pool)[current.left].val,\n            (*_pool)[current.right].val\n\
    \        );\n    }\n\n    int all_apply_clone(\n        int node,\n        int\
    \ left,\n        int right,\n        const F& f,\n        bool copy_on_write =\
    \ false\n    ) const {\n        int result = copy_on_write ? _pool->clone_if_shared(node)\
    \ : clone_node(node);\n        Node& current = (*_pool)[result];\n        if (can_apply_at(f,\
    \ current.val, 0)) {\n            current.val = mapping_at(f, current.val, 0);\n\
    \            if (right - left > 1) {\n                current.lazy = ActedMonoid::op_comp(f,\
    \ current.lazy);\n                current.has_lazy = true;\n            }\n  \
    \          return result;\n        }\n\n        assert(right - left > 1);\n  \
    \      push(result, left, right, copy_on_write);\n        int middle = left +\
    \ (right - left) / 2;\n        int left_child = all_apply_clone(\n           \
    \ (*_pool)[result].left,\n            left,\n            middle,\n           \
    \ f,\n            copy_on_write\n        );\n        int right_child = all_apply_clone(\n\
    \            (*_pool)[result].right,\n            middle,\n            right,\n\
    \            shift_operator(f, middle - left),\n            copy_on_write\n  \
    \      );\n        _pool->replace((*_pool)[result].left, left_child);\n      \
    \  _pool->replace((*_pool)[result].right, right_child);\n        update(result);\n\
    \        return result;\n    }\n\n    void push(\n        int node,\n        int\
    \ left,\n        int right,\n        bool copy_on_write = false\n    ) const {\n\
    \        if (!(*_pool)[node].has_lazy) return;\n        assert(right - left >\
    \ 1);\n\n        F lazy = (*_pool)[node].lazy;\n        int middle = left + (right\
    \ - left) / 2;\n        int left_child = all_apply_clone(\n            (*_pool)[node].left,\n\
    \            left,\n            middle,\n            lazy,\n            copy_on_write\n\
    \        );\n        int right_child = all_apply_clone(\n            (*_pool)[node].right,\n\
    \            middle,\n            right,\n            shift_operator(lazy, middle\
    \ - left),\n            copy_on_write\n        );\n        _pool->replace((*_pool)[node].left,\
    \ left_child);\n        _pool->replace((*_pool)[node].right, right_child);\n \
    \       Node& current = (*_pool)[node];\n        current.lazy = ActedMonoid::op_id();\n\
    \        current.has_lazy = false;\n    }\n\n    int set_node(\n        int node,\n\
    \        int left,\n        int right,\n        int index,\n        T value,\n\
    \        bool copy_on_write = false\n    ) const {\n        int result = copy_on_write\
    \ ? _pool->clone_if_shared(node) : clone_node(node);\n        if (right - left\
    \ == 1) {\n            Node& current = (*_pool)[result];\n            current.val\
    \ = std::move(value);\n            current.lazy = ActedMonoid::op_id();\n    \
    \        current.has_lazy = false;\n            return result;\n        }\n\n\
    \        push(result, left, right, copy_on_write);\n        int middle = left\
    \ + (right - left) / 2;\n        if (index < middle) {\n            int child\
    \ = set_node(\n                (*_pool)[result].left,\n                left,\n\
    \                middle,\n                index,\n                std::move(value),\n\
    \                copy_on_write\n            );\n            _pool->replace((*_pool)[result].left,\
    \ child);\n        } else {\n            int child = set_node(\n             \
    \   (*_pool)[result].right,\n                middle,\n                right,\n\
    \                index,\n                std::move(value),\n                copy_on_write\n\
    \            );\n            _pool->replace((*_pool)[result].right, child);\n\
    \        }\n        update(result);\n        return result;\n    }\n\n    int\
    \ apply_node(\n        int node,\n        int left,\n        int right,\n    \
    \    int query_left,\n        int query_right,\n        const F& f,\n        bool\
    \ copy_on_write = false\n    ) const {\n        if (query_right <= left || right\
    \ <= query_left) return node;\n        if (query_left <= left && right <= query_right)\
    \ {\n            return all_apply_clone(\n                node,\n            \
    \    left,\n                right,\n                shift_operator(f, left - query_left),\n\
    \                copy_on_write\n            );\n        }\n\n        int result\
    \ = copy_on_write ? _pool->clone_if_shared(node) : clone_node(node);\n       \
    \ push(result, left, right, copy_on_write);\n        int middle = left + (right\
    \ - left) / 2;\n        int left_child = apply_node(\n            (*_pool)[result].left,\n\
    \            left,\n            middle,\n            query_left,\n           \
    \ query_right,\n            f,\n            copy_on_write\n        );\n      \
    \  int right_child = apply_node(\n            (*_pool)[result].right,\n      \
    \      middle,\n            right,\n            query_left,\n            query_right,\n\
    \            f,\n            copy_on_write\n        );\n        _pool->replace((*_pool)[result].left,\
    \ left_child);\n        _pool->replace((*_pool)[result].right, right_child);\n\
    \        update(result);\n        return result;\n    }\n\n    int copy_range_node(\n\
    \        int target,\n        int source,\n        int left,\n        int right,\n\
    \        int query_left,\n        int query_right\n    ) const {\n        if (query_right\
    \ <= left || right <= query_left) return target;\n        if (query_left <= left\
    \ && right <= query_right) return source;\n\n        int result = clone_node(target);\n\
    \        int materialized_source = clone_node(source);\n        _pool->retain(materialized_source);\n\
    \        push(result, left, right);\n        push(materialized_source, left, right);\n\
    \n        int middle = left + (right - left) / 2;\n        int left_child = copy_range_node(\n\
    \            (*_pool)[result].left,\n            (*_pool)[materialized_source].left,\n\
    \            left,\n            middle,\n            query_left,\n           \
    \ query_right\n        );\n        int right_child = copy_range_node(\n      \
    \      (*_pool)[result].right,\n            (*_pool)[materialized_source].right,\n\
    \            middle,\n            right,\n            query_left,\n          \
    \  query_right\n        );\n        _pool->replace((*_pool)[result].left, left_child);\n\
    \        _pool->replace((*_pool)[result].right, right_child);\n        update(result);\n\
    \        _pool->release(materialized_source);\n        return result;\n    }\n\
    \n    F compose_for_child(\n        const F& inherited,\n        const Node& node,\n\
    \        long long ordinal\n    ) const {\n        F shifted = shift_operator(inherited,\
    \ ordinal);\n        if (!node.has_lazy) return shifted;\n        return ActedMonoid::op_comp(\n\
    \            shifted,\n            shift_operator(node.lazy, ordinal)\n      \
    \  );\n    }\n\n    T evaluate_node(\n        int node,\n        int left,\n \
    \       int right,\n        const F& inherited\n    ) const {\n        const Node&\
    \ current = (*_pool)[node];\n        if (can_apply_at(inherited, current.val,\
    \ 0)) {\n            return mapping_at(inherited, current.val, 0);\n        }\n\
    \n        assert(right - left > 1);\n        int middle = left + (right - left)\
    \ / 2;\n        return ActedMonoid::op(\n            evaluate_node(\n        \
    \        current.left,\n                left,\n                middle,\n     \
    \           compose_for_child(inherited, current, 0)\n            ),\n       \
    \     evaluate_node(\n                current.right,\n                middle,\n\
    \                right,\n                compose_for_child(inherited, current,\
    \ middle - left)\n            )\n        );\n    }\n\n    T prod_node(\n     \
    \   int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        const F& inherited\n    ) const {\n       \
    \ if (query_right <= left || right <= query_left) {\n            return ActedMonoid::id();\n\
    \        }\n        if (query_left <= left && right <= query_right) {\n      \
    \      return evaluate_node(node, left, right, inherited);\n        }\n\n    \
    \    const Node& current = (*_pool)[node];\n        int middle = left + (right\
    \ - left) / 2;\n        return ActedMonoid::op(\n            prod_node(\n    \
    \            current.left,\n                left,\n                middle,\n \
    \               query_left,\n                query_right,\n                compose_for_child(inherited,\
    \ current, 0)\n            ),\n            prod_node(\n                current.right,\n\
    \                middle,\n                right,\n                query_left,\n\
    \                query_right,\n                compose_for_child(inherited, current,\
    \ middle - left)\n            )\n        );\n    }\n\n    void collect_node(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        const F& inherited,\n        std::vector<T>&\
    \ result\n    ) const {\n        if (query_right <= left || right <= query_left)\
    \ return;\n        const Node& current = (*_pool)[node];\n        if (right -\
    \ left == 1) {\n            result.push_back(mapping_at(inherited, current.val,\
    \ 0));\n            return;\n        }\n\n        int middle = left + (right -\
    \ left) / 2;\n        collect_node(\n            current.left,\n            left,\n\
    \            middle,\n            query_left,\n            query_right,\n    \
    \        compose_for_child(inherited, current, 0),\n            result\n     \
    \   );\n        collect_node(\n            current.right,\n            middle,\n\
    \            right,\n            query_left,\n            query_right,\n     \
    \       compose_for_child(inherited, current, middle - left),\n            result\n\
    \        );\n    }\n\n    template <class Predicate>\n    int max_right_node(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        T& product,\n        const F& inherited,\n        Predicate& predicate\n\
    \    ) const {\n        if (right <= query_left) return right;\n        if (query_left\
    \ <= left) {\n            T next = ActedMonoid::op(\n                product,\n\
    \                evaluate_node(node, left, right, inherited)\n            );\n\
    \            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return right;\n            }\n            if (right - left ==\
    \ 1) return left;\n        }\n\n        const Node& current = (*_pool)[node];\n\
    \        int middle = left + (right - left) / 2;\n        int result = max_right_node(\n\
    \            current.left,\n            left,\n            middle,\n         \
    \   query_left,\n            product,\n            compose_for_child(inherited,\
    \ current, 0),\n            predicate\n        );\n        if (result < middle)\
    \ return result;\n        return max_right_node(\n            current.right,\n\
    \            middle,\n            right,\n            query_left,\n          \
    \  product,\n            compose_for_child(inherited, current, middle - left),\n\
    \            predicate\n        );\n    }\n\n    template <class Predicate>\n\
    \    int min_left_node(\n        int node,\n        int left,\n        int right,\n\
    \        int query_right,\n        T& product,\n        const F& inherited,\n\
    \        Predicate& predicate\n    ) const {\n        if (query_right <= left)\
    \ return left;\n        if (right <= query_right) {\n            T next = ActedMonoid::op(\n\
    \                evaluate_node(node, left, right, inherited),\n              \
    \  product\n            );\n            if (predicate(next)) {\n             \
    \   product = std::move(next);\n                return left;\n            }\n\
    \            if (right - left == 1) return right;\n        }\n\n        const\
    \ Node& current = (*_pool)[node];\n        int middle = left + (right - left)\
    \ / 2;\n        int result = min_left_node(\n            current.right,\n    \
    \        middle,\n            right,\n            query_right,\n            product,\n\
    \            compose_for_child(inherited, current, middle - left),\n         \
    \   predicate\n        );\n        if (middle < result) return result;\n     \
    \   return min_left_node(\n            current.left,\n            left,\n    \
    \        middle,\n            query_right,\n            product,\n           \
    \ compose_for_child(inherited, current, 0),\n            predicate\n        );\n\
    \    }\n\n   public:\n    PersistentSegtreeBeats() : PersistentSegtreeBeats(0)\
    \ {}\n\n    explicit PersistentSegtreeBeats(int n)\n        : _n(n), _root(0),\
    \ _pool(std::make_shared<Pool>()) {\n        assert(0 <= n);\n        if (_n >\
    \ 0) {\n            std::vector<T> values(_n, ActedMonoid::id());\n          \
    \  _root = build(0, _n, values);\n        }\n        _pool->retain(_root);\n \
    \   }\n\n    explicit PersistentSegtreeBeats(const std::vector<T>& values)\n \
    \       : _n(int(values.size())),\n          _root(0),\n          _pool(std::make_shared<Pool>())\
    \ {\n        _pool->reserve(values.size() * 2);\n        if (_n > 0) _root = build(0,\
    \ _n, values);\n        _pool->retain(_root);\n    }\n\n    explicit PersistentSegtreeBeats(std::vector<T>&&\
    \ values)\n        : _n(int(values.size())),\n          _root(0),\n          _pool(std::make_shared<Pool>())\
    \ {\n        _pool->reserve(values.size() * 2);\n        if (_n > 0) _root = build(0,\
    \ _n, values);\n        _pool->retain(_root);\n    }\n\n    template <typename\
    \ U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x);\
    \ } ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n       \
    \ std::convertible_to<U, T>\n    )\n    explicit PersistentSegtreeBeats(const\
    \ std::vector<U>& values)\n        : _n(int(values.size())),\n          _root(0),\n\
    \          _pool(std::make_shared<Pool>()) {\n        _pool->reserve(values.size()\
    \ * 2);\n        if (_n > 0) _root = build_from_values(0, _n, values);\n     \
    \   _pool->retain(_root);\n    }\n\n    PersistentSegtreeBeats(const PersistentSegtreeBeats&\
    \ other)\n        : _n(other._n), _root(other._root), _pool(other._pool) {\n \
    \       if (_pool) _pool->retain(_root);\n    }\n\n    PersistentSegtreeBeats(PersistentSegtreeBeats&&\
    \ other) noexcept\n        : _n(other._n),\n          _root(other._root),\n  \
    \        _pool(std::move(other._pool)) {\n        other._n = 0;\n        other._root\
    \ = 0;\n    }\n\n    PersistentSegtreeBeats& operator=(\n        const PersistentSegtreeBeats&\
    \ other\n    ) {\n        if (this == &other) return *this;\n        if (other._pool)\
    \ other._pool->retain(other._root);\n        if (_pool) _pool->release(_root);\n\
    \        _n = other._n;\n        _root = other._root;\n        _pool = other._pool;\n\
    \        return *this;\n    }\n\n    PersistentSegtreeBeats& operator=(\n    \
    \    PersistentSegtreeBeats&& other\n    ) noexcept {\n        if (this == &other)\
    \ return *this;\n        if (_pool) _pool->release(_root);\n        _n = other._n;\n\
    \        _root = other._root;\n        _pool = std::move(other._pool);\n     \
    \   other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\n\
    \    ~PersistentSegtreeBeats() {\n        if (_pool) _pool->release(_root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    void release() {\n        if\
    \ (_pool) _pool->release(_root);\n        _pool = std::make_shared<Pool>();\n\
    \        _root = 0;\n        _n = 0;\n    }\n\n    std::size_t node_count() const\
    \ {\n        return _pool ? _pool->size() : 0;\n    }\n\n    PersistentSegtreeBeats\
    \ set(int index, T value) const {\n        assert(0 <= index && index < _n);\n\
    \        return PersistentSegtreeBeats(\n            _n,\n            set_node(_root,\
    \ 0, _n, index, std::move(value)),\n            _pool\n        );\n    }\n\n \
    \   void set_inplace(int index, T value) {\n        assert(0 <= index && index\
    \ < _n);\n        int root = set_node(\n            _root,\n            0,\n \
    \           _n,\n            index,\n            std::move(value),\n         \
    \   true\n        );\n        _pool->replace(_root, root);\n    }\n\n    T get(int\
    \ index) const {\n        assert(0 <= index && index < _n);\n        return prod(index,\
    \ index + 1);\n    }\n\n    T operator[](int index) const {\n        return get(index);\n\
    \    }\n\n    T prod(int left, int right) const {\n        assert(0 <= left &&\
    \ left <= right && right <= _n);\n        if (left == right) return ActedMonoid::id();\n\
    \        return prod_node(\n            _root,\n            0,\n            _n,\n\
    \            left,\n            right,\n            ActedMonoid::op_id()\n   \
    \     );\n    }\n\n    T all_prod() const {\n        return _root ? (*_pool)[_root].val\
    \ : ActedMonoid::id();\n    }\n\n    PersistentSegtreeBeats apply(int index, const\
    \ F& f) const {\n        assert(0 <= index && index < _n);\n        return apply(index,\
    \ index + 1, f);\n    }\n\n    PersistentSegtreeBeats apply(\n        int left,\n\
    \        int right,\n        const F& f\n    ) const {\n        assert(0 <= left\
    \ && left <= right && right <= _n);\n        if (left == right) return *this;\n\
    \        return PersistentSegtreeBeats(\n            _n,\n            apply_node(_root,\
    \ 0, _n, left, right, f),\n            _pool\n        );\n    }\n\n    void apply_inplace(int\
    \ index, const F& f) {\n        assert(0 <= index && index < _n);\n        apply_inplace(index,\
    \ index + 1, f);\n    }\n\n    void apply_inplace(int left, int right, const F&\
    \ f) {\n        assert(0 <= left && left <= right && right <= _n);\n        if\
    \ (left == right) return;\n        int root = apply_node(\n            _root,\n\
    \            0,\n            _n,\n            left,\n            right,\n    \
    \        f,\n            true\n        );\n        _pool->replace(_root, root);\n\
    \    }\n\n    PersistentSegtreeBeats copy_range_from(\n        const PersistentSegtreeBeats&\
    \ source,\n        int left,\n        int right\n    ) const {\n        assert(_n\
    \ == source._n);\n        assert(_pool == source._pool);\n        assert(0 <=\
    \ left && left <= right && right <= _n);\n        if (left == right) return *this;\n\
    \        return PersistentSegtreeBeats(\n            _n,\n            copy_range_node(\n\
    \                _root,\n                source._root,\n                0,\n \
    \               _n,\n                left,\n                right\n          \
    \  ),\n            _pool\n        );\n    }\n\n    std::vector<T> to_vector()\
    \ const {\n        return to_vector(0, _n);\n    }\n\n    std::vector<T> to_vector(int\
    \ left, int right) const {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        std::vector<T> result;\n        result.reserve(right - left);\n\
    \        if (left != right) {\n            collect_node(\n                _root,\n\
    \                0,\n                _n,\n                left,\n            \
    \    right,\n                ActedMonoid::op_id(),\n                result\n \
    \           );\n        }\n        return result;\n    }\n\n    template <class\
    \ Predicate>\n    int max_right(int left, Predicate predicate) const {\n     \
    \   assert(0 <= left && left <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (left == _n) return _n;\n        T product = ActedMonoid::id();\n\
    \        return max_right_node(\n            _root,\n            0,\n        \
    \    _n,\n            left,\n            product,\n            ActedMonoid::op_id(),\n\
    \            predicate\n        );\n    }\n\n    template <class Predicate>\n\
    \    int min_left(int right, Predicate predicate) const {\n        assert(0 <=\
    \ right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n    \
    \    if (right == 0) return 0;\n        T product = ActedMonoid::id();\n     \
    \   return min_left_node(\n            _root,\n            0,\n            _n,\n\
    \            right,\n            product,\n            ActedMonoid::op_id(),\n\
    \            predicate\n        );\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add\
    \ {\n    using value_type = T;\n    static constexpr bool commutative = true;\n\
    \n    // Returns the identity element for addition, which is 0.\n    static constexpr\
    \ T id() {\n        return T(0);\n    }\n\n    // Returns the sum of a and b.\n\
    \    static constexpr T op(const T& a, const T& b) {\n        return a + b;\n\
    \    }\n\n    static constexpr T inv(const T& x) {\n        return -x;\n    }\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include <array>\n#include <cerrno>\n\
    #include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include\
    \ <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 19 \"verify/ds/persistent_cow.test.cpp\"\
    \n\n#line 24 \"verify/ds/persistent_cow.test.cpp\"\n\nnamespace {\n\nusing Add\
    \ = m1une::monoid::Add<long long>;\nusing RangeAdd = m1une::acted_monoid::RangeAddRangeSum<long\
    \ long>;\n\nstruct RangeAddBeats : RangeAdd {\n    static bool can_apply(const\
    \ operator_type&, const value_type&) {\n        return true;\n    }\n};\n\ntemplate\
    \ <class Structure, class Update, class Get>\nvoid check_copy_move_and_reuse(Structure\
    \ base, Update update, Get get) {\n    const std::size_t base_nodes = base.node_count();\n\
    \    Structure current = base;\n    Structure sibling = current;\n\n    update(current,\
    \ 0);\n    assert(get(base) == 0);\n    assert(get(sibling) == 0);\n    assert(get(current)\
    \ == 1);\n\n    update(sibling, 9);\n    assert(get(base) == 0);\n    assert(get(current)\
    \ == 1);\n    assert(get(sibling) == 10);\n\n    const std::size_t after_first_write\
    \ = current.node_count();\n    update(current, 1);\n    assert(get(current) ==\
    \ 2);\n    assert(current.node_count() == after_first_write);\n\n    Structure\
    \ snapshot = current;\n    update(current, 2);\n    assert(get(snapshot) == 2);\n\
    \    assert(get(current) == 3);\n    const std::size_t after_reshare = current.node_count();\n\
    \    update(current, 3);\n    assert(get(snapshot) == 2);\n    assert(get(current)\
    \ == 4);\n    assert(current.node_count() == after_reshare);\n\n    Structure\
    \ moved(std::move(current));\n    update(moved, 4);\n    assert(get(moved) ==\
    \ 5);\n    Structure assigned = base;\n    assigned = std::move(moved);\n    update(assigned,\
    \ 5);\n    assert(get(assigned) == 6);\n    assert(get(base) == 0);\n\n    sibling.release();\n\
    \    snapshot.release();\n    assigned.release();\n    assert(base.node_count()\
    \ == base_nodes);\n\n    Structure reused = base;\n    update(reused, 6);\n  \
    \  assert(get(reused) == 7);\n    reused.release();\n    assert(base.node_count()\
    \ == base_nodes);\n}\n\nvoid test_segment_trees() {\n    using Seg = m1une::ds::PersistentSegtree<Add>;\n\
    \    check_copy_move_and_reuse(\n        Seg(std::vector<long long>(8, 0)),\n\
    \        [](Seg& seg, int step) { seg.set_inplace(3, step + 1); },\n        [](const\
    \ Seg& seg) { return seg.get(3); }\n    );\n\n    using Lazy = m1une::ds::PersistentLazySegtree<RangeAdd>;\n\
    \    check_copy_move_and_reuse(\n        Lazy(std::vector<long long>(8, 0)),\n\
    \        [](Lazy& seg, int step) { seg.set_inplace(3, RangeAdd::make(step + 1));\
    \ },\n        [](const Lazy& seg) { return seg.get(3).sum; }\n    );\n\n    Lazy\
    \ base(std::vector<long long>(8, 0));\n    Lazy current = base;\n    current.apply_inplace(0,\
    \ 8, 10);\n    const std::size_t after_full_cover = current.node_count();\n  \
    \  current.apply_inplace(0, 8, 1);\n    assert(current.node_count() == after_full_cover);\n\
    \    Lazy snapshot = current;\n    current.apply_inplace(2, 6, 5);\n    current.set_inplace(3,\
    \ RangeAdd::make(100));\n    assert(base.all_prod().sum == 0);\n    assert(snapshot.all_prod().sum\
    \ == 88);\n    assert(snapshot.get(3).sum == 11);\n    assert(current.get(2).sum\
    \ == 16);\n    assert(current.get(3).sum == 100);\n\n    Lazy persistent = base;\n\
    \    Lazy inplace = base;\n    std::uint64_t state = 1;\n    for (int operation\
    \ = 0; operation < 500; ++operation) {\n        state = state * 6364136223846793005ULL\
    \ + 1;\n        int left = int(state % 9);\n        state = state * 6364136223846793005ULL\
    \ + 1;\n        int right = int(state % 9);\n        if (left > right) std::swap(left,\
    \ right);\n        long long add = static_cast<long long>(operation % 13) - 6;\n\
    \        persistent = persistent.apply(left, right, add);\n        inplace.apply_inplace(left,\
    \ right, add);\n        if (operation % 17 == 0) {\n            int index = operation\
    \ % 8;\n            auto value = RangeAdd::make(operation);\n            persistent\
    \ = persistent.set(index, value);\n            inplace.set_inplace(index, value);\n\
    \        }\n        auto inplace_values = inplace.to_vector();\n        auto persistent_values\
    \ = persistent.to_vector();\n        assert(inplace_values.size() == persistent_values.size());\n\
    \        for (int i = 0; i < int(inplace_values.size()); ++i) {\n            assert(inplace_values[i].sum\
    \ == persistent_values[i].sum);\n        }\n    }\n    assert(base.all_prod().sum\
    \ == 0);\n\n    using Dual = m1une::ds::PersistentDualSegtree<Add>;\n    Dual\
    \ dual_base(std::vector<long long>(8, 0));\n    Dual dual = dual_base;\n    dual.apply_inplace(1,\
    \ 7, 4);\n    dual.apply_inplace(3, 6);\n    dual.set_inplace(5, 20);\n    assert(dual_base.get(5)\
    \ == 0);\n    assert(dual.get(3) == 10);\n    assert(dual.get(5) == 20);\n\n \
    \   using Beats = m1une::ds::PersistentSegtreeBeats<RangeAddBeats>;\n    Beats\
    \ beats_base(std::vector<long long>(8, 0));\n    Beats beats = beats_base;\n \
    \   beats.apply_inplace(1, 7, 4);\n    const std::size_t beats_nodes = beats.node_count();\n\
    \    beats.apply_inplace(1, 7, 3);\n    assert(beats.node_count() == beats_nodes);\n\
    \    Beats beats_copy = beats;\n    beats.set_inplace(3, RangeAddBeats::make(50));\n\
    \    assert(beats_base.all_prod().sum == 0);\n    assert(beats_copy.get(3).sum\
    \ == 7);\n    assert(beats.get(3).sum == 50);\n}\n\nvoid test_dynamic_segment_trees()\
    \ {\n    using Seg = m1une::ds::PersistentDynamicSegtree<Add>;\n    Seg base(-100,\
    \ 100);\n    Seg current = base;\n    current.set_inplace(17, 1);\n    const std::size_t\
    \ nodes = current.node_count();\n    current.set_inplace(17, 2);\n    assert(current.node_count()\
    \ == nodes);\n    Seg copy = current;\n    current.set_inplace(17, 3);\n    assert(base.get(17)\
    \ == 0);\n    assert(copy.get(17) == 2);\n    assert(current.get(17) == 3);\n\n\
    \    using Lazy = m1une::ds::PersistentDynamicLazySegtree<RangeAdd>;\n    Lazy\
    \ lazy_base(-64, 64, RangeAdd::make(0));\n    Lazy lazy = lazy_base;\n    lazy.apply_inplace(-20,\
    \ 30, 5);\n    Lazy lazy_copy = lazy;\n    lazy.apply_inplace(-5, 10, 7);\n  \
    \  lazy.set_inplace(0, RangeAdd::make(100));\n    assert(lazy_base.get(0).sum\
    \ == 0);\n    assert(lazy_copy.get(0).sum == 5);\n    assert(lazy.get(-6).sum\
    \ == 5);\n    assert(lazy.get(-5).sum == 12);\n    assert(lazy.get(0).sum == 100);\n\
    \n    using Dual = m1une::ds::PersistentDynamicDualSegtree<Add>;\n    Dual dual_base(-64,\
    \ 64, 0);\n    Dual dual = dual_base;\n    dual.apply_inplace(-20, 30, 5);\n \
    \   Dual dual_copy = dual;\n    dual.apply_inplace(-5, 10, 7);\n    dual.set_inplace(0,\
    \ 100);\n    assert(dual_base.get(0) == 0);\n    assert(dual_copy.get(0) == 5);\n\
    \    assert(dual.get(-5) == 12);\n    assert(dual.get(0) == 100);\n}\n\nvoid test_dynamic_arrays()\
    \ {\n    using Array = m1une::ds::PersistentDynamicArray<int>;\n    Array base\
    \ = {0, 1, 2, 3, 4, 5};\n    Array reversed = base.reverse(1, 6);\n    Array copy\
    \ = reversed;\n    reversed.set_inplace(1, 20);\n    const std::size_t nodes =\
    \ reversed.node_count();\n    reversed.set_inplace(1, 21);\n    assert(reversed.node_count()\
    \ == nodes);\n    assert(base.to_vector() == (std::vector<int>{0, 1, 2, 3, 4,\
    \ 5}));\n    assert(copy.to_vector() == (std::vector<int>{0, 5, 4, 3, 2, 1}));\n\
    \    assert(reversed.to_vector() == (std::vector<int>{0, 21, 4, 3, 2, 1}));\n\n\
    \    using MonoidArray = m1une::ds::PersistentDynamicMonoidArray<Add>;\n    MonoidArray\
    \ monoid(std::vector<long long>{1, 2, 3, 4});\n    MonoidArray monoid_copy = monoid;\n\
    \    monoid.set_inplace(2, 30);\n    assert(monoid_copy.all_prod() == 10);\n \
    \   assert(monoid.all_prod() == 37);\n\n    using LazyArray = m1une::ds::PersistentDynamicLazyMonoidArray<RangeAdd>;\n\
    \    LazyArray lazy_base(std::vector<long long>{1, 2, 3, 4, 5, 6});\n    LazyArray\
    \ lazy = lazy_base.apply(1, 6, 10).reverse(0, 5);\n    LazyArray lazy_copy = lazy;\n\
    \    lazy.apply_inplace(1, 5, 7);\n    lazy.set_inplace(2, RangeAdd::make(100));\n\
    \    assert(lazy_base.all_prod().sum == 21);\n    std::vector<long long> copy_expected\
    \ = {15, 14, 13, 12, 1, 16};\n    auto copy_values = lazy_copy.to_vector();\n\
    \    for (int i = 0; i < int(copy_expected.size()); ++i) {\n        assert(copy_values[i].sum\
    \ == copy_expected[i]);\n    }\n    std::vector<long long> expected = {15, 21,\
    \ 100, 19, 8, 16};\n    auto values = lazy.to_vector();\n    for (int i = 0; i\
    \ < int(expected.size()); ++i) assert(values[i].sum == expected[i]);\n    assert(lazy.all_prod().sum\
    \ == 179);\n}\n\nvoid test_dsu() {\n    m1une::ds::PersistentDsu base(8);\n  \
    \  auto current = base;\n    assert(current.merge_inplace(0, 1));\n    const std::size_t\
    \ after_merge = current.node_count();\n    assert(!current.merge_inplace(0, 1));\n\
    \    assert(current.node_count() == after_merge);\n    auto copy = current;\n\
    \    assert(current.merge_inplace(1, 2));\n    assert(!base.same(0, 1));\n   \
    \ assert(!copy.same(0, 2));\n    assert(current.same(0, 2));\n\n    using PotentialDsu\
    \ = m1une::ds::PersistentPotentializedDsu<Add>;\n    PotentialDsu potential_base(8);\n\
    \    PotentialDsu potential = potential_base;\n    assert(potential.merge_inplace(0,\
    \ 1, 3));\n    PotentialDsu potential_copy = potential;\n    assert(potential.merge_inplace(1,\
    \ 2, 4));\n    assert(!potential.merge_inplace(0, 2, 8));\n    assert(potential.diff(0,\
    \ 2) == 7);\n    assert(!potential_base.same(0, 1));\n    assert(!potential_copy.same(0,\
    \ 2));\n}\n\nvoid test_ordered_multiset() {\n    using Multiset = m1une::ds::PersistentOrderedMultiset<int>;\n\
    \    Multiset base = {1, 2, 2, 3};\n    Multiset current = base;\n    current.insert_inplace(2,\
    \ 3);\n    const std::size_t after_first_write = current.node_count();\n    current.insert_inplace(2);\n\
    \    assert(current.node_count() == after_first_write);\n    Multiset copy = current;\n\
    \    assert(current.erase_inplace(2));\n    assert(base.count(2) == 2);\n    assert(copy.count(2)\
    \ == 6);\n    assert(current.count(2) == 5);\n    current.insert_inplace(4);\n\
    \    assert(!base.contains(4));\n    assert(current.contains(4));\n    assert(current.erase_all_inplace(4));\n\
    \    assert(!current.contains(4));\n    assert(!current.erase_inplace(9));\n}\n\
    \n}  // namespace\n\nint main() {\n    test_segment_trees();\n    test_dynamic_segment_trees();\n\
    \    test_dynamic_arrays();\n    test_dsu();\n    test_ordered_multiset();\n\n\
    \    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \    long long a, b;\n    input >> a >> b;\n    output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../acted_monoid/range_add_range_sum.hpp\"\n#include \"../../ds/dsu/persistent_dsu.hpp\"\
    \n#include \"../../ds/dsu/persistent_potentialized_dsu.hpp\"\n#include \"../../ds/bst/persistent_ordered_multiset.hpp\"\
    \n#include \"../../ds/dynamic_array/persistent_dynamic_array.hpp\"\n#include \"\
    ../../ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\n#include \"\
    ../../ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\n#include \"../../ds/segtree/persistent_dual_segtree.hpp\"\
    \n#include \"../../ds/segtree/persistent_dynamic_dual_segtree.hpp\"\n#include\
    \ \"../../ds/segtree/persistent_dynamic_lazy_segtree.hpp\"\n#include \"../../ds/segtree/persistent_dynamic_segtree.hpp\"\
    \n#include \"../../ds/segtree/persistent_lazy_segtree.hpp\"\n#include \"../../ds/segtree/persistent_segtree.hpp\"\
    \n#include \"../../ds/segtree/persistent_segtree_beats.hpp\"\n#include \"../../monoid/add.hpp\"\
    \n#include \"../../utilities/fast_io.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <utility>\n#include <vector>\n\nnamespace {\n\nusing Add = m1une::monoid::Add<long\
    \ long>;\nusing RangeAdd = m1une::acted_monoid::RangeAddRangeSum<long long>;\n\
    \nstruct RangeAddBeats : RangeAdd {\n    static bool can_apply(const operator_type&,\
    \ const value_type&) {\n        return true;\n    }\n};\n\ntemplate <class Structure,\
    \ class Update, class Get>\nvoid check_copy_move_and_reuse(Structure base, Update\
    \ update, Get get) {\n    const std::size_t base_nodes = base.node_count();\n\
    \    Structure current = base;\n    Structure sibling = current;\n\n    update(current,\
    \ 0);\n    assert(get(base) == 0);\n    assert(get(sibling) == 0);\n    assert(get(current)\
    \ == 1);\n\n    update(sibling, 9);\n    assert(get(base) == 0);\n    assert(get(current)\
    \ == 1);\n    assert(get(sibling) == 10);\n\n    const std::size_t after_first_write\
    \ = current.node_count();\n    update(current, 1);\n    assert(get(current) ==\
    \ 2);\n    assert(current.node_count() == after_first_write);\n\n    Structure\
    \ snapshot = current;\n    update(current, 2);\n    assert(get(snapshot) == 2);\n\
    \    assert(get(current) == 3);\n    const std::size_t after_reshare = current.node_count();\n\
    \    update(current, 3);\n    assert(get(snapshot) == 2);\n    assert(get(current)\
    \ == 4);\n    assert(current.node_count() == after_reshare);\n\n    Structure\
    \ moved(std::move(current));\n    update(moved, 4);\n    assert(get(moved) ==\
    \ 5);\n    Structure assigned = base;\n    assigned = std::move(moved);\n    update(assigned,\
    \ 5);\n    assert(get(assigned) == 6);\n    assert(get(base) == 0);\n\n    sibling.release();\n\
    \    snapshot.release();\n    assigned.release();\n    assert(base.node_count()\
    \ == base_nodes);\n\n    Structure reused = base;\n    update(reused, 6);\n  \
    \  assert(get(reused) == 7);\n    reused.release();\n    assert(base.node_count()\
    \ == base_nodes);\n}\n\nvoid test_segment_trees() {\n    using Seg = m1une::ds::PersistentSegtree<Add>;\n\
    \    check_copy_move_and_reuse(\n        Seg(std::vector<long long>(8, 0)),\n\
    \        [](Seg& seg, int step) { seg.set_inplace(3, step + 1); },\n        [](const\
    \ Seg& seg) { return seg.get(3); }\n    );\n\n    using Lazy = m1une::ds::PersistentLazySegtree<RangeAdd>;\n\
    \    check_copy_move_and_reuse(\n        Lazy(std::vector<long long>(8, 0)),\n\
    \        [](Lazy& seg, int step) { seg.set_inplace(3, RangeAdd::make(step + 1));\
    \ },\n        [](const Lazy& seg) { return seg.get(3).sum; }\n    );\n\n    Lazy\
    \ base(std::vector<long long>(8, 0));\n    Lazy current = base;\n    current.apply_inplace(0,\
    \ 8, 10);\n    const std::size_t after_full_cover = current.node_count();\n  \
    \  current.apply_inplace(0, 8, 1);\n    assert(current.node_count() == after_full_cover);\n\
    \    Lazy snapshot = current;\n    current.apply_inplace(2, 6, 5);\n    current.set_inplace(3,\
    \ RangeAdd::make(100));\n    assert(base.all_prod().sum == 0);\n    assert(snapshot.all_prod().sum\
    \ == 88);\n    assert(snapshot.get(3).sum == 11);\n    assert(current.get(2).sum\
    \ == 16);\n    assert(current.get(3).sum == 100);\n\n    Lazy persistent = base;\n\
    \    Lazy inplace = base;\n    std::uint64_t state = 1;\n    for (int operation\
    \ = 0; operation < 500; ++operation) {\n        state = state * 6364136223846793005ULL\
    \ + 1;\n        int left = int(state % 9);\n        state = state * 6364136223846793005ULL\
    \ + 1;\n        int right = int(state % 9);\n        if (left > right) std::swap(left,\
    \ right);\n        long long add = static_cast<long long>(operation % 13) - 6;\n\
    \        persistent = persistent.apply(left, right, add);\n        inplace.apply_inplace(left,\
    \ right, add);\n        if (operation % 17 == 0) {\n            int index = operation\
    \ % 8;\n            auto value = RangeAdd::make(operation);\n            persistent\
    \ = persistent.set(index, value);\n            inplace.set_inplace(index, value);\n\
    \        }\n        auto inplace_values = inplace.to_vector();\n        auto persistent_values\
    \ = persistent.to_vector();\n        assert(inplace_values.size() == persistent_values.size());\n\
    \        for (int i = 0; i < int(inplace_values.size()); ++i) {\n            assert(inplace_values[i].sum\
    \ == persistent_values[i].sum);\n        }\n    }\n    assert(base.all_prod().sum\
    \ == 0);\n\n    using Dual = m1une::ds::PersistentDualSegtree<Add>;\n    Dual\
    \ dual_base(std::vector<long long>(8, 0));\n    Dual dual = dual_base;\n    dual.apply_inplace(1,\
    \ 7, 4);\n    dual.apply_inplace(3, 6);\n    dual.set_inplace(5, 20);\n    assert(dual_base.get(5)\
    \ == 0);\n    assert(dual.get(3) == 10);\n    assert(dual.get(5) == 20);\n\n \
    \   using Beats = m1une::ds::PersistentSegtreeBeats<RangeAddBeats>;\n    Beats\
    \ beats_base(std::vector<long long>(8, 0));\n    Beats beats = beats_base;\n \
    \   beats.apply_inplace(1, 7, 4);\n    const std::size_t beats_nodes = beats.node_count();\n\
    \    beats.apply_inplace(1, 7, 3);\n    assert(beats.node_count() == beats_nodes);\n\
    \    Beats beats_copy = beats;\n    beats.set_inplace(3, RangeAddBeats::make(50));\n\
    \    assert(beats_base.all_prod().sum == 0);\n    assert(beats_copy.get(3).sum\
    \ == 7);\n    assert(beats.get(3).sum == 50);\n}\n\nvoid test_dynamic_segment_trees()\
    \ {\n    using Seg = m1une::ds::PersistentDynamicSegtree<Add>;\n    Seg base(-100,\
    \ 100);\n    Seg current = base;\n    current.set_inplace(17, 1);\n    const std::size_t\
    \ nodes = current.node_count();\n    current.set_inplace(17, 2);\n    assert(current.node_count()\
    \ == nodes);\n    Seg copy = current;\n    current.set_inplace(17, 3);\n    assert(base.get(17)\
    \ == 0);\n    assert(copy.get(17) == 2);\n    assert(current.get(17) == 3);\n\n\
    \    using Lazy = m1une::ds::PersistentDynamicLazySegtree<RangeAdd>;\n    Lazy\
    \ lazy_base(-64, 64, RangeAdd::make(0));\n    Lazy lazy = lazy_base;\n    lazy.apply_inplace(-20,\
    \ 30, 5);\n    Lazy lazy_copy = lazy;\n    lazy.apply_inplace(-5, 10, 7);\n  \
    \  lazy.set_inplace(0, RangeAdd::make(100));\n    assert(lazy_base.get(0).sum\
    \ == 0);\n    assert(lazy_copy.get(0).sum == 5);\n    assert(lazy.get(-6).sum\
    \ == 5);\n    assert(lazy.get(-5).sum == 12);\n    assert(lazy.get(0).sum == 100);\n\
    \n    using Dual = m1une::ds::PersistentDynamicDualSegtree<Add>;\n    Dual dual_base(-64,\
    \ 64, 0);\n    Dual dual = dual_base;\n    dual.apply_inplace(-20, 30, 5);\n \
    \   Dual dual_copy = dual;\n    dual.apply_inplace(-5, 10, 7);\n    dual.set_inplace(0,\
    \ 100);\n    assert(dual_base.get(0) == 0);\n    assert(dual_copy.get(0) == 5);\n\
    \    assert(dual.get(-5) == 12);\n    assert(dual.get(0) == 100);\n}\n\nvoid test_dynamic_arrays()\
    \ {\n    using Array = m1une::ds::PersistentDynamicArray<int>;\n    Array base\
    \ = {0, 1, 2, 3, 4, 5};\n    Array reversed = base.reverse(1, 6);\n    Array copy\
    \ = reversed;\n    reversed.set_inplace(1, 20);\n    const std::size_t nodes =\
    \ reversed.node_count();\n    reversed.set_inplace(1, 21);\n    assert(reversed.node_count()\
    \ == nodes);\n    assert(base.to_vector() == (std::vector<int>{0, 1, 2, 3, 4,\
    \ 5}));\n    assert(copy.to_vector() == (std::vector<int>{0, 5, 4, 3, 2, 1}));\n\
    \    assert(reversed.to_vector() == (std::vector<int>{0, 21, 4, 3, 2, 1}));\n\n\
    \    using MonoidArray = m1une::ds::PersistentDynamicMonoidArray<Add>;\n    MonoidArray\
    \ monoid(std::vector<long long>{1, 2, 3, 4});\n    MonoidArray monoid_copy = monoid;\n\
    \    monoid.set_inplace(2, 30);\n    assert(monoid_copy.all_prod() == 10);\n \
    \   assert(monoid.all_prod() == 37);\n\n    using LazyArray = m1une::ds::PersistentDynamicLazyMonoidArray<RangeAdd>;\n\
    \    LazyArray lazy_base(std::vector<long long>{1, 2, 3, 4, 5, 6});\n    LazyArray\
    \ lazy = lazy_base.apply(1, 6, 10).reverse(0, 5);\n    LazyArray lazy_copy = lazy;\n\
    \    lazy.apply_inplace(1, 5, 7);\n    lazy.set_inplace(2, RangeAdd::make(100));\n\
    \    assert(lazy_base.all_prod().sum == 21);\n    std::vector<long long> copy_expected\
    \ = {15, 14, 13, 12, 1, 16};\n    auto copy_values = lazy_copy.to_vector();\n\
    \    for (int i = 0; i < int(copy_expected.size()); ++i) {\n        assert(copy_values[i].sum\
    \ == copy_expected[i]);\n    }\n    std::vector<long long> expected = {15, 21,\
    \ 100, 19, 8, 16};\n    auto values = lazy.to_vector();\n    for (int i = 0; i\
    \ < int(expected.size()); ++i) assert(values[i].sum == expected[i]);\n    assert(lazy.all_prod().sum\
    \ == 179);\n}\n\nvoid test_dsu() {\n    m1une::ds::PersistentDsu base(8);\n  \
    \  auto current = base;\n    assert(current.merge_inplace(0, 1));\n    const std::size_t\
    \ after_merge = current.node_count();\n    assert(!current.merge_inplace(0, 1));\n\
    \    assert(current.node_count() == after_merge);\n    auto copy = current;\n\
    \    assert(current.merge_inplace(1, 2));\n    assert(!base.same(0, 1));\n   \
    \ assert(!copy.same(0, 2));\n    assert(current.same(0, 2));\n\n    using PotentialDsu\
    \ = m1une::ds::PersistentPotentializedDsu<Add>;\n    PotentialDsu potential_base(8);\n\
    \    PotentialDsu potential = potential_base;\n    assert(potential.merge_inplace(0,\
    \ 1, 3));\n    PotentialDsu potential_copy = potential;\n    assert(potential.merge_inplace(1,\
    \ 2, 4));\n    assert(!potential.merge_inplace(0, 2, 8));\n    assert(potential.diff(0,\
    \ 2) == 7);\n    assert(!potential_base.same(0, 1));\n    assert(!potential_copy.same(0,\
    \ 2));\n}\n\nvoid test_ordered_multiset() {\n    using Multiset = m1une::ds::PersistentOrderedMultiset<int>;\n\
    \    Multiset base = {1, 2, 2, 3};\n    Multiset current = base;\n    current.insert_inplace(2,\
    \ 3);\n    const std::size_t after_first_write = current.node_count();\n    current.insert_inplace(2);\n\
    \    assert(current.node_count() == after_first_write);\n    Multiset copy = current;\n\
    \    assert(current.erase_inplace(2));\n    assert(base.count(2) == 2);\n    assert(copy.count(2)\
    \ == 6);\n    assert(current.count(2) == 5);\n    current.insert_inplace(4);\n\
    \    assert(!base.contains(4));\n    assert(current.contains(4));\n    assert(current.erase_all_inplace(4));\n\
    \    assert(!current.contains(4));\n    assert(!current.erase_inplace(9));\n}\n\
    \n}  // namespace\n\nint main() {\n    test_segment_trees();\n    test_dynamic_segment_trees();\n\
    \    test_dynamic_arrays();\n    test_dsu();\n    test_ordered_multiset();\n\n\
    \    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \    long long a, b;\n    input >> a >> b;\n    output << a + b << '\\n';\n}\n"
  dependsOn:
  - acted_monoid/range_add_range_sum.hpp
  - ds/dsu/persistent_dsu.hpp
  - ds/detail/persistent_binary_node_pool.hpp
  - ds/dsu/persistent_potentialized_dsu.hpp
  - monoid/concept.hpp
  - ds/bst/persistent_ordered_multiset.hpp
  - ds/detail/persistent_binary_node_pool.hpp
  - ds/dynamic_array/persistent_dynamic_array.hpp
  - ds/detail/persistent_binary_node_pool.hpp
  - ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
  - acted_monoid/concept.hpp
  - ds/dynamic_array/persistent_dynamic_monoid_array.hpp
  - monoid/concept.hpp
  - ds/segtree/persistent_dual_segtree.hpp
  - monoid/concept.hpp
  - ds/segtree/persistent_node_pool.hpp
  - ds/segtree/persistent_dynamic_dual_segtree.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - ds/segtree/persistent_dynamic_lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - ds/segtree/persistent_dynamic_segtree.hpp
  - ds/segtree/persistent_lazy_segtree.hpp
  - ds/segtree/persistent_segtree.hpp
  - ds/segtree/persistent_segtree_beats.hpp
  - beats_acted_monoid/concept.hpp
  - acted_monoid/concept.hpp
  - monoid/add.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/persistent_cow.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 03:11:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/persistent_cow.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/persistent_cow.test.cpp
- /verify/verify/ds/persistent_cow.test.cpp.html
title: verify/ds/persistent_cow.test.cpp
---
