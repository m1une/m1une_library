---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/persistent_binary_node_pool.hpp
    title: ds/detail/persistent_binary_node_pool.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
    title: verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_cow.test.cpp
    title: verify/ds/persistent_cow.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_release.test.cpp
    title: verify/ds/persistent_release.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\n\n\n\n\
    #include <cassert>\n#include <chrono>\n#include <cstddef>\n#include <cstdint>\n\
    #include <deque>\n#include <initializer_list>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"ds/detail/persistent_binary_node_pool.hpp\"\n\n\
    \n\n#line 7 \"ds/detail/persistent_binary_node_pool.hpp\"\n#include <limits>\n\
    #include <optional>\n#line 11 \"ds/detail/persistent_binary_node_pool.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\nnamespace detail {\n\n// Node must have integer\
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
    \  }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP\n#define M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP\
    \ 1\n\n#include <cassert>\n#include <chrono>\n#include <cstddef>\n#include <cstdint>\n\
    #include <deque>\n#include <initializer_list>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\n#include \"../detail/persistent_binary_node_pool.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct PersistentDynamicArray\
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
    \  }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP\n"
  dependsOn:
  - ds/detail/persistent_binary_node_pool.hpp
  isVerificationFile: false
  path: ds/dynamic_array/persistent_dynamic_array.hpp
  requiredBy: []
  timestamp: '2026-08-12 03:11:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/persistent_cow.test.cpp
  - verify/ds/persistent_release.test.cpp
  - verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
documentation_of: ds/dynamic_array/persistent_dynamic_array.hpp
layout: document
title: Persistent Dynamic Array
---

## Overview

`PersistentDynamicArray` is a path-copying implicit treap. It acts like a persistent version of `DynamicArray`: update operations return a new array and leave the old version available.

Nodes are stored in a shared stable-slot pool and refer to children by integer index. Intrusive reference counts reclaim a node once no version or parent node depends on it, and reclaimed slots are reused by later updates. References returned by `at`, `front`, and `back` remain valid only while a live version depends on their node.

The structure supports index-based insertion, deletion, point assignment, reversal, rotation, splitting, and concatenation. Untouched subtrees are shared between versions.

`set` returns a new persistent version. `set_inplace` mutates this handle with
copy-on-write: it clones shared nodes on the search path and reuses unique ones,
while every other live version remains unchanged. Structural treap operations
continue to use the persistent-returning interface.

## Complexity Notation

* `N` is the current number of elements in the array.
* `M` is the number of inserted or appended elements.
* `K` is the number of elements returned by `to_vector`.

## Template Parameters

* `T`: The underlying data type of the elements.

## Constructors

* `PersistentDynamicArray()`
  Constructs an empty array. ($O(1)$)

* `PersistentDynamicArray(int n)`
  Constructs an array with `n` value-initialized elements. ($O(N)$)

* `PersistentDynamicArray(int n, const T& value)`
  Constructs an array with `n` copies of `value`. ($O(N)$)

* `PersistentDynamicArray(const std::vector<T>& v)`
  Constructs an array initialized with elements from `v`. ($O(N)$)

* `PersistentDynamicArray(std::vector<T>&& v)`
  Constructs an array by moving elements from `v`. ($O(N)$)

* `PersistentDynamicArray(std::initializer_list<T> init)`
  Constructs an array initialized with an initializer list. ($O(N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the array is empty. | $O(1)$ |
| `void release()` | Releases this version immediately and makes this handle empty. | $O(F)$ |
| `std::size_t node_count() const` | Returns live nodes in the shared version family. | $O(1)$ |
| `PersistentDynamicArray clear() const` | Returns an empty version. | $O(1)$ |
| `PersistentDynamicArray insert(int pos, T val) const` | Returns a version with `val` inserted before index `pos`. | Expected $O(\log N)$ |
| `PersistentDynamicArray insert(int pos, const std::vector<T>& v) const` | Returns a version with all elements of `v` inserted before index `pos`. | Expected $O(M + \log N)$ |
| `PersistentDynamicArray insert(int pos, const PersistentDynamicArray& other) const` | Returns a version with `other` inserted before index `pos`. Versions sharing a pool reuse its nodes; an independently constructed array is copied into this pool. | Expected $O(\log N)$ with a shared pool; $O(M + \log N)$ otherwise |
| `PersistentDynamicArray push_back(T val) const`, `push_front(T val) const` | Returns a version with one element added. | Expected $O(\log N)$ |
| `PersistentDynamicArray append(...) const` | Appends a vector or another persistent dynamic array. | Expected $O(M + \log N)$ for a vector or independent array; $O(\log N)$ for a version sharing the pool |
| `PersistentDynamicArray erase(int pos) const` | Returns a version with the element at `pos` removed. | Expected $O(\log N)$ |
| `PersistentDynamicArray erase(int l, int r) const` | Returns a version with `[l, r)` removed. | Expected $O(\log N)$ |
| `PersistentDynamicArray pop_back() const`, `pop_front() const` | Returns a version with one element removed. | Expected $O(\log N)$ |
| `const T& at(int pos) const`, `operator[]` | Returns the element at `pos`. | Expected $O(\log N)$ |
| `T get(int pos) const` | Returns a copy of the element at `pos`. | Expected $O(\log N)$ |
| `const T& front() const`, `back() const` | Returns the first or last element. | Expected $O(\log N)$ |
| `PersistentDynamicArray set(int pos, T val) const` | Returns a version where index `pos` is overwritten by `val`. | Expected $O(\log N)$ |
| `void set_inplace(int pos, T val)` | Overwrites index `pos` in this version using copy-on-write. | Expected $O(\log N)$ |
| `PersistentDynamicArray reverse(int l, int r) const` | Returns a version with `[l, r)` reversed. | Expected $O(\log N)$ |
| `PersistentDynamicArray reverse() const` | Returns a version with the whole array reversed. | $O(1)$ |
| `PersistentDynamicArray rotate(int l, int m, int r) const` | Returns a version where `[m, r)` is moved before `[l, m)`, like `std::rotate`. | Expected $O(\log N)$ |
| `std::pair<PersistentDynamicArray, PersistentDynamicArray> split(int pos) const` | Returns `{prefix, suffix}` split at `pos`. | Expected $O(\log N)$ |
| `PersistentDynamicArray split_off(int pos) const` | Returns the suffix `[pos, N)` while leaving the current version unchanged. | Expected $O(\log N)$ |
| `std::vector<T> to_vector() const` | Dumps the entire array. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r) const` | Dumps `[l, r)`, where `K = r - l`. | $O(K + \log N)$ |

Here $F$ is the number of nodes that become unreachable. Destruction and
assignment release roots automatically.

## Example

```cpp
#include "ds/dynamic_array/persistent_dynamic_array.hpp"

#include <iostream>

using namespace m1une::ds;

int main() {
    PersistentDynamicArray<int> a = {1, 2, 3, 4, 5};
    auto b = a.insert(2, 10);      // {1, 2, 10, 3, 4, 5}
    auto c = b.reverse(1, 5);      // {1, 4, 3, 10, 2, 5}
    auto d = c.erase(2).set(0, 7); // {7, 4, 10, 2, 5}

    for (int x : a.to_vector()) std::cout << x << " ";
    std::cout << "\n";
    for (int x : d.to_vector()) std::cout << x << " ";
    std::cout << "\n";
}
```
