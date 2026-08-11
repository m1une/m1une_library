---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/persistent_binary_node_pool.hpp
    title: ds/detail/persistent_binary_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_persistent_base.hpp
    title: ds/detail/rollback_persistent_base.hpp
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_array.hpp
    title: Persistent Dynamic Array
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
  bundledCode: "#line 1 \"ds/dynamic_array/rollback_dynamic_array.hpp\"\n\n\n\n#include\
    \ <initializer_list>\n#include <utility>\n#include <vector>\n\n#line 1 \"ds/detail/rollback_persistent_base.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#include <limits>\n#line 9 \"\
    ds/detail/rollback_persistent_base.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    namespace detail {\n\ntemplate <class Persistent>\nstruct RollbackPersistentBase\
    \ : Persistent {\n   private:\n    std::vector<Persistent> _history;\n\n   protected:\n\
    \    using Persistent::Persistent;\n\n    const Persistent& persistent() const\
    \ {\n        return *this;\n    }\n\n    void commit(Persistent next) {\n    \
    \    assert(_history.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _history.emplace_back(persistent());\n        Persistent::operator=(std::move(next));\n\
    \    }\n\n   public:\n    RollbackPersistentBase() = default;\n\n    explicit\
    \ RollbackPersistentBase(Persistent initial)\n        : Persistent(std::move(initial))\
    \ {}\n\n    int history_size() const {\n        return int(_history.size());\n\
    \    }\n\n    void reserve_history(int count) {\n        assert(0 <= count);\n\
    \        _history.reserve(count);\n    }\n\n    bool undo() {\n        if (_history.empty())\
    \ return false;\n        Persistent::operator=(std::move(_history.back()));\n\
    \        _history.pop_back();\n        return true;\n    }\n\n    int snapshot()\
    \ const {\n        return history_size();\n    }\n\n    void rollback(int state)\
    \ {\n        assert(0 <= state && state <= history_size());\n        while (history_size()\
    \ > state) undo();\n    }\n\n    void clear_history() {\n        _history.clear();\n\
    \    }\n\n    void release() {\n        _history.clear();\n        Persistent::release();\n\
    \    }\n\n    const Persistent& current_version() const {\n        return persistent();\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\n\n\n\n#line 5 \"\
    ds/dynamic_array/persistent_dynamic_array.hpp\"\n#include <chrono>\n#line 7 \"\
    ds/dynamic_array/persistent_dynamic_array.hpp\"\n#include <cstdint>\n#include\
    \ <deque>\n#line 10 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\n#include\
    \ <memory>\n#line 13 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\n\n#line\
    \ 1 \"ds/detail/persistent_binary_node_pool.hpp\"\n\n\n\n#line 8 \"ds/detail/persistent_binary_node_pool.hpp\"\
    \n#include <optional>\n#line 11 \"ds/detail/persistent_binary_node_pool.hpp\"\n\
    \nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\n// Node must have integer\
    \ `l` and `r` members. New nodes initially have no\n// owner; discard_unreferenced()\
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
    \ 15 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <typename T>\nstruct PersistentDynamicArray {\n   private:\n\
    \    struct Node {\n        T val;\n        int priority;\n        int count;\n\
    \        int l, r;\n        bool rev;\n\n        Node(T value, int node_priority,\
    \ int node_count, int left, int right, bool reversed)\n            : val(std::move(value)),\n\
    \              priority(node_priority),\n              count(node_count),\n  \
    \            l(left),\n              r(right),\n              rev(reversed) {}\n\
    \    };\n\n    struct BuildNode {\n        T val;\n        int priority;\n   \
    \     int l, r;\n\n        BuildNode(T value, int node_priority) : val(std::move(value)),\
    \ priority(node_priority), l(-1), r(-1) {}\n    };\n\n    int root;\n    std::uint32_t\
    \ rng_state;\n    using Pool = detail::PersistentBinaryNodePool<Node>;\n\n   \
    \ std::shared_ptr<Pool> pool;\n\n    int subtree_size(int t) const {\n       \
    \ return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    static std::uint32_t next_state(std::uint32_t\
    \ state) {\n        state ^= state << 13;\n        state ^= state >> 17;\n   \
    \     state ^= state << 5;\n        return state == 0 ? 1 : state;\n    }\n\n\
    \    static int next_priority(std::uint32_t& state) {\n        state = next_state(state);\n\
    \        return int(state);\n    }\n\n    int make_node(T val, int priority, bool\
    \ rev, int l, int r) const {\n        int count = 1 + subtree_size(l) + subtree_size(r);\n\
    \        return pool->emplace(std::move(val), priority, count, l, r, rev);\n \
    \   }\n\n    int reversed_node(int t) const {\n        if (t == -1) return -1;\n\
    \        const Node& node = (*pool)[t];\n        return make_node(node.val, node.priority,\
    \ !node.rev, node.l, node.r);\n    }\n\n    int push(int t) const {\n        if\
    \ (t == -1 || !(*pool)[t].rev) return t;\n        Node node = (*pool)[t];\n  \
    \      int l = reversed_node(node.r);\n        int r = reversed_node(node.l);\n\
    \        return make_node(std::move(node.val), node.priority, false, l, r);\n\
    \    }\n\n    int merge(int l, int r) const {\n        if (l == -1 || r == -1)\
    \ return l == -1 ? r : l;\n        if ((*pool)[l].priority > (*pool)[r].priority)\
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
    \  }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 10 \"ds/dynamic_array/rollback_dynamic_array.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct RollbackDynamicArray\n\
    \    : detail::RollbackPersistentBase<PersistentDynamicArray<T>> {\n   private:\n\
    \    using Persistent = PersistentDynamicArray<T>;\n    using Base = detail::RollbackPersistentBase<Persistent>;\n\
    \n   public:\n    using Base::Base;\n\n    void clear() { Base::commit(Base::persistent().clear());\
    \ }\n\n    void insert(int pos, T value) {\n        Base::commit(Base::persistent().insert(pos,\
    \ std::move(value)));\n    }\n    void insert(int pos, const std::vector<T>& values)\
    \ {\n        Base::commit(Base::persistent().insert(pos, values));\n    }\n  \
    \  void insert(int pos, std::vector<T>&& values) {\n        Base::commit(Base::persistent().insert(pos,\
    \ std::move(values)));\n    }\n    void insert(int pos, std::initializer_list<T>\
    \ values) {\n        Base::commit(Base::persistent().insert(pos, values));\n \
    \   }\n    void insert(int pos, const RollbackDynamicArray& other) {\n       \
    \ Base::commit(Base::persistent().insert(pos, other.current_version()));\n   \
    \ }\n    void insert(int pos, const Persistent& other) {\n        Base::commit(Base::persistent().insert(pos,\
    \ other));\n    }\n\n    void push_back(T value) { insert(this->size(), std::move(value));\
    \ }\n    void push_front(T value) { insert(0, std::move(value)); }\n    void append(const\
    \ std::vector<T>& values) { insert(this->size(), values); }\n    void append(std::vector<T>&&\
    \ values) { insert(this->size(), std::move(values)); }\n    void append(const\
    \ RollbackDynamicArray& other) { insert(this->size(), other); }\n    void append(const\
    \ Persistent& other) { insert(this->size(), other); }\n\n    void erase(int pos)\
    \ { Base::commit(Base::persistent().erase(pos)); }\n    void erase(int left, int\
    \ right) { Base::commit(Base::persistent().erase(left, right)); }\n    void pop_back()\
    \ { Base::commit(Base::persistent().pop_back()); }\n    void pop_front() { Base::commit(Base::persistent().pop_front());\
    \ }\n\n    void set(int pos, T value) {\n        Base::commit(Base::persistent().set(pos,\
    \ std::move(value)));\n    }\n    void set_inplace(int pos, T value) { set(pos,\
    \ std::move(value)); }\n\n    void reverse(int left, int right) {\n        Base::commit(Base::persistent().reverse(left,\
    \ right));\n    }\n    void reverse() { Base::commit(Base::persistent().reverse());\
    \ }\n    void rotate(int left, int middle, int right) {\n        Base::commit(Base::persistent().rotate(left,\
    \ middle, right));\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_ARRAY_HPP\n#define M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_ARRAY_HPP\
    \ 1\n\n#include <initializer_list>\n#include <utility>\n#include <vector>\n\n\
    #include \"../detail/rollback_persistent_base.hpp\"\n#include \"persistent_dynamic_array.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct RollbackDynamicArray\n\
    \    : detail::RollbackPersistentBase<PersistentDynamicArray<T>> {\n   private:\n\
    \    using Persistent = PersistentDynamicArray<T>;\n    using Base = detail::RollbackPersistentBase<Persistent>;\n\
    \n   public:\n    using Base::Base;\n\n    void clear() { Base::commit(Base::persistent().clear());\
    \ }\n\n    void insert(int pos, T value) {\n        Base::commit(Base::persistent().insert(pos,\
    \ std::move(value)));\n    }\n    void insert(int pos, const std::vector<T>& values)\
    \ {\n        Base::commit(Base::persistent().insert(pos, values));\n    }\n  \
    \  void insert(int pos, std::vector<T>&& values) {\n        Base::commit(Base::persistent().insert(pos,\
    \ std::move(values)));\n    }\n    void insert(int pos, std::initializer_list<T>\
    \ values) {\n        Base::commit(Base::persistent().insert(pos, values));\n \
    \   }\n    void insert(int pos, const RollbackDynamicArray& other) {\n       \
    \ Base::commit(Base::persistent().insert(pos, other.current_version()));\n   \
    \ }\n    void insert(int pos, const Persistent& other) {\n        Base::commit(Base::persistent().insert(pos,\
    \ other));\n    }\n\n    void push_back(T value) { insert(this->size(), std::move(value));\
    \ }\n    void push_front(T value) { insert(0, std::move(value)); }\n    void append(const\
    \ std::vector<T>& values) { insert(this->size(), values); }\n    void append(std::vector<T>&&\
    \ values) { insert(this->size(), std::move(values)); }\n    void append(const\
    \ RollbackDynamicArray& other) { insert(this->size(), other); }\n    void append(const\
    \ Persistent& other) { insert(this->size(), other); }\n\n    void erase(int pos)\
    \ { Base::commit(Base::persistent().erase(pos)); }\n    void erase(int left, int\
    \ right) { Base::commit(Base::persistent().erase(left, right)); }\n    void pop_back()\
    \ { Base::commit(Base::persistent().pop_back()); }\n    void pop_front() { Base::commit(Base::persistent().pop_front());\
    \ }\n\n    void set(int pos, T value) {\n        Base::commit(Base::persistent().set(pos,\
    \ std::move(value)));\n    }\n    void set_inplace(int pos, T value) { set(pos,\
    \ std::move(value)); }\n\n    void reverse(int left, int right) {\n        Base::commit(Base::persistent().reverse(left,\
    \ right));\n    }\n    void reverse() { Base::commit(Base::persistent().reverse());\
    \ }\n    void rotate(int left, int middle, int right) {\n        Base::commit(Base::persistent().rotate(left,\
    \ middle, right));\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    #endif  // M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_ARRAY_HPP\n"
  dependsOn:
  - ds/detail/rollback_persistent_base.hpp
  - ds/dynamic_array/persistent_dynamic_array.hpp
  - ds/detail/persistent_binary_node_pool.hpp
  isVerificationFile: false
  path: ds/dynamic_array/rollback_dynamic_array.hpp
  requiredBy: []
  timestamp: '2026-08-12 04:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/dynamic_array/rollback_dynamic_array.hpp
layout: document
title: Rollback Dynamic Array
---

## Overview

`RollbackDynamicArray<T>` is a mutable implicit-treap sequence with linear
history. Saved states share persistent nodes; insertions, erasures, assignments,
reversals, and rotations can be undone.

## Methods

Its constructors and read-only methods (`size`, `empty`, element access,
`to_vector`, `split`, `split_off`, and `node_count`) match
`PersistentDynamicArray<T>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the sequence and advances history. | $O(1)$ |
| `void insert(int pos, T value)` | Inserts one value. | Expected $O(\log N)$ |
| `void insert(int pos, const std::vector<T>& values)`, `void insert(int pos, std::vector<T>&& values)`, `void insert(int pos, std::initializer_list<T> values)` | Inserts $M$ values. | Expected $O(M + \log N)$ |
| `void insert(int pos, const RollbackDynamicArray& other)`, `void insert(int pos, const PersistentDynamicArray<T>& other)` | Inserts another sequence. | Expected $O(\log N)$ with a shared pool; $O(M + \log N)$ otherwise |
| `void push_back(T value)`, `void push_front(T value)` | Inserts at one end. | Expected $O(\log N)$ |
| `void append(...)` | Appends a vector, rollback array, or persistent array. | Same as `insert` |
| `void erase(int pos)`, `void erase(int left, int right)` | Erases one value or `[left, right)`. | Expected $O(\log N)$ |
| `void pop_back()`, `void pop_front()` | Erases one end. | Expected $O(\log N)$ |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Replaces one value. | Expected $O(\log N)$ |
| `void reverse(int left, int right)` | Reverses `[left, right)`. | Expected $O(\log N)$ |
| `void reverse()` | Reverses the entire sequence. | $O(1)$ |
| `void rotate(int left, int middle, int right)` | Applies `std::rotate` semantics to the range. | Expected $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentDynamicArray<T>& current_version() const` | Returns the current persistent state. | $O(1)$ |

Each update call advances history once, including empty-range updates. $F$
counts nodes whose final reference is released.

## Example

```cpp
#include "ds/dynamic_array/rollback_dynamic_array.hpp"

m1une::ds::RollbackDynamicArray<int> a({1, 2, 3});
int state = a.snapshot();
a.insert(1, 7);
a.reverse();
a.rollback(state);
assert(a.to_vector() == std::vector<int>({1, 2, 3}));
```
