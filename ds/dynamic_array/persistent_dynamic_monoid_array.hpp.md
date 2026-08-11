---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/persistent_binary_node_pool.hpp
    title: ds/detail/persistent_binary_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/rollback_dynamic_monoid_array.hpp
    title: Rollback Dynamic Monoid Array
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp
    title: verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_cow.test.cpp
    title: verify/ds/persistent_cow.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_release.test.cpp
    title: verify/ds/persistent_release.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\n\
    \n\n\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstddef>\n\
    #include <cstdint>\n#include <initializer_list>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 1 \"ds/detail/persistent_binary_node_pool.hpp\"\n\
    \n\n\n#line 6 \"ds/detail/persistent_binary_node_pool.hpp\"\n#include <deque>\n\
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
    \ 16 \"ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct PersistentDynamicMonoidArray\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    struct Node\
    \ {\n        T val, prod, rprod;\n        int priority;\n        int count;\n\
    \        int l, r;\n        bool rev;\n\n        Node(T value, T product, T reverse_product,\
    \ int node_priority, int node_count, int left, int right,\n             bool reversed)\n\
    \            : val(std::move(value)),\n              prod(std::move(product)),\n\
    \              rprod(std::move(reverse_product)),\n              priority(node_priority),\n\
    \              count(node_count),\n              l(left),\n              r(right),\n\
    \              rev(reversed) {}\n    };\n\n    struct BuildNode {\n        T val;\n\
    \        int priority;\n        int l, r;\n\n        BuildNode(T value, int node_priority)\
    \ : val(std::move(value)), priority(node_priority), l(-1), r(-1) {}\n    };\n\n\
    \    int root;\n    std::uint32_t rng_state;\n    using Pool = detail::PersistentBinaryNodePool<Node>;\n\
    \n    std::shared_ptr<Pool> pool;\n\n    int subtree_size(int t) const {\n   \
    \     return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    T node_prod(int t)\
    \ const {\n        return t == -1 ? Monoid::id() : (*pool)[t].prod;\n    }\n\n\
    \    T node_rprod(int t) const {\n        return t == -1 ? Monoid::id() : (*pool)[t].rprod;\n\
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
    \n\n"
  code: "#ifndef M1UNE_PERSISTENT_DYNAMIC_MONOID_ARRAY_HPP\n#define M1UNE_PERSISTENT_DYNAMIC_MONOID_ARRAY_HPP\
    \ 1\n\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstddef>\n\
    #include <cstdint>\n#include <initializer_list>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../monoid/concept.hpp\"\n#include \"../detail/persistent_binary_node_pool.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct PersistentDynamicMonoidArray {\n    using T = typename Monoid::value_type;\n\
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
    \n#endif  // M1UNE_PERSISTENT_DYNAMIC_MONOID_ARRAY_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  - ds/detail/persistent_binary_node_pool.hpp
  isVerificationFile: false
  path: ds/dynamic_array/persistent_dynamic_monoid_array.hpp
  requiredBy:
  - ds/dynamic_array/rollback_dynamic_monoid_array.hpp
  timestamp: '2026-08-12 03:11:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp
  - verify/ds/rollback_counterparts.test.cpp
  - verify/ds/persistent_release.test.cpp
  - verify/ds/persistent_cow.test.cpp
documentation_of: ds/dynamic_array/persistent_dynamic_monoid_array.hpp
layout: document
title: Persistent Dynamic Monoid Array
---

## Overview

`PersistentDynamicMonoidArray` is a path-copying implicit treap for dynamic sequences with range product queries. Updates return a new sequence and leave older versions available.

Nodes live in a shared stable-slot pool and store integer child indices. Intrusive reference counts reclaim nodes after their final dependent version or parent is released, and later updates reuse their slots.

Each node stores both forward and reversed products, so range reversal works for non-commutative monoids.

`set_inplace` is a copy-on-write point assignment for a mutable working
version. It preserves other versions, clones shared search-path nodes, and
updates unique nodes directly. Other update methods retain their
persistent-returning semantics.

## Template Parameters

* `Monoid`: A monoid satisfying `m1une::monoid::IsMonoid`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const`, `bool empty() const` | Returns the sequence size or whether it is empty. | $O(1)$ |
| `void release()` | Releases this version immediately and makes this handle empty. | $O(F)$ |
| `std::size_t node_count() const` | Returns live nodes in the shared version family. | $O(1)$ |
| `insert`, `push_back`, `push_front`, `append` | Return a version with values inserted. Another version sharing the pool reuses its nodes; an independently constructed array is copied into this pool. | Expected $O(\log N)$ for one value or a shared-pool version; $O(M + \log N)$ for a vector or independent array |
| `erase`, `pop_back`, `pop_front` | Return a version with values removed. | Expected $O(\log N)$ |
| `set` | Returns a version with one value replaced. | Expected $O(\log N)$ |
| `set_inplace(int pos, T value)` | Replaces one value in this version using copy-on-write. | Expected $O(\log N)$ |
| `reverse`, `rotate` | Return versions with sequence order changed. | Expected $O(\log N)$; whole-sequence `reverse()` is $O(1)$ |
| `prod`, `all_prod` | Return monoid products over a range or the whole sequence. | Expected $O(\log N)$ for `prod`; $O(1)$ for `all_prod` |
| `split`, `split_off` | Return persistent split versions. | Expected $O(\log N)$ |
| `to_vector` | Dumps a range or the whole sequence. | $O(K + \log N)$ for a range; $O(N)$ for all values |

Here $F$ is the number of nodes that become unreachable. Destruction and
assignment release roots automatically.

## Notes

Order-aware monoids should store relative order information such as `size` and `ord`, not immutable global indices. For example, `monoid::ArgMin` returns `ord` relative to the queried range, so it remains valid after insertions, deletions, and reversals.

## Example

```cpp
#include "ds/dynamic_array/persistent_dynamic_monoid_array.hpp"
#include "monoid/add.hpp"
#include <iostream>

using Monoid = m1une::monoid::Add<long long>;
using Array = m1une::ds::PersistentDynamicMonoidArray<Monoid>;

int main() {
    Array a = {1, 2, 3, 4, 5};
    auto b = a.reverse(1, 5);
    auto c = b.set(2, 10);

    // a is still {1, 2, 3, 4, 5}
    // c is {1, 5, 10, 3, 2}
    long long sum = c.prod(0, 4);
    std::cout << sum << "\n";
}
```
