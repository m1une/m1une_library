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
    path: ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
    title: Persistent Dynamic Lazy Monoid Array
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
  bundledCode: "#line 1 \"verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\
    \n\n\n\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n\
    #include <initializer_list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
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
    \n\n#line 14 \"ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\n\n\
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
    \ rng_state;\n    std::shared_ptr<std::vector<Node>> pool;\n\n    int subtree_size(int\
    \ t) const {\n        return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    T node_prod(int\
    \ t) const {\n        return t == -1 ? ActedMonoid::id() : (*pool)[t].prod;\n\
    \    }\n\n    T node_rprod(int t) const {\n        return t == -1 ? ActedMonoid::id()\
    \ : (*pool)[t].rprod;\n    }\n\n    static std::uint32_t next_state(std::uint32_t\
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
    \ {\n        pool->emplace_back(std::move(val), std::move(prod), std::move(rprod),\
    \ std::move(lazy), priority, count, l,\n                           r, rev, has_lazy);\n\
    \        return int(pool->size()) - 1;\n    }\n\n    int make_node(T val, int\
    \ priority, bool rev, int l, int r) const {\n        T prod = ActedMonoid::op(ActedMonoid::op(node_prod(l),\
    \ val), node_prod(r));\n        T rprod = ActedMonoid::op(ActedMonoid::op(node_rprod(r),\
    \ val), node_rprod(l));\n        if (rev) std::swap(prod, rprod);\n        int\
    \ count = 1 + subtree_size(l) + subtree_size(r);\n        return make_raw_node(std::move(val),\
    \ std::move(prod), std::move(rprod), ActedMonoid::op_id(), priority,\n       \
    \                      count, rev, false, l, r);\n    }\n\n    int reversed_node(int\
    \ t) const {\n        if (t == -1) return -1;\n        Node node = (*pool)[t];\n\
    \        F lazy = node.has_lazy ? reverse_operator(node.lazy, node.count) : node.lazy;\n\
    \        return make_raw_node(std::move(node.val), std::move(node.rprod), std::move(node.prod),\
    \ std::move(lazy),\n                             node.priority, node.count, !node.rev,\
    \ node.has_lazy, node.l, node.r);\n    }\n\n    int all_apply(int t, const F&\
    \ f) const {\n        if (t == -1) return -1;\n        Node node = (*pool)[t];\n\
    \        int left_count = node.rev ? subtree_size(node.r) : subtree_size(node.l);\n\
    \        return make_raw_node(mapping_at(f, node.val, left_count), mapping_at(f,\
    \ node.prod, 0),\n                             mapping_at(reverse_operator(f,\
    \ node.count), node.rprod, 0),\n                             ActedMonoid::op_comp(f,\
    \ node.lazy), node.priority, node.count, node.rev, true, node.l,\n           \
    \                  node.r);\n    }\n\n    int push(int t) const {\n        if\
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
    \ node.priority, false, node.l, r);\n    }\n\n    T get_value(int t, int pos,\
    \ F inherited, bool reversed = false) const {\n        while (t != -1) {\n   \
    \         const Node& node = (*pool)[t];\n            bool cur_reversed = reversed\
    \ ^ node.rev;\n            int l = cur_reversed ? node.r : node.l;\n         \
    \   int r = cur_reversed ? node.l : node.r;\n            int left_count = subtree_size(l);\n\
    \            if (pos < left_count) {\n                inherited = compose_for_child(inherited,\
    \ t, 0);\n                t = l;\n                reversed = cur_reversed;\n \
    \           } else if (pos == left_count) {\n                return mapping_at(inherited,\
    \ node.val, left_count);\n            } else {\n                pos -= left_count\
    \ + 1;\n                inherited = compose_for_child(inherited, t, left_count\
    \ + 1);\n                t = r;\n                reversed = cur_reversed;\n  \
    \          }\n        }\n        return ActedMonoid::id();\n    }\n\n    T prod_dfs(int\
    \ t, int ql, int qr, int offset, const F& inherited, bool reversed = false) const\
    \ {\n        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return\
    \ ActedMonoid::id();\n        const Node& node = (*pool)[t];\n        bool cur_reversed\
    \ = reversed ^ node.rev;\n        if (ql <= offset && offset + node.count <= qr)\
    \ {\n            return mapping_at(inherited, reversed ? node.rprod : node.prod,\
    \ 0);\n        }\n        int l = cur_reversed ? node.r : node.l;\n        int\
    \ r = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        T res = prod_dfs(l, ql,\
    \ qr, offset, compose_for_child(inherited, t, 0), cur_reversed);\n        if (ql\
    \ <= node_pos && node_pos < qr) res = ActedMonoid::op(res, mapping_at(inherited,\
    \ node.val, left_count));\n        return ActedMonoid::op(\n            res, prod_dfs(r,\
    \ ql, qr, node_pos + 1, compose_for_child(inherited, t, left_count + 1),\n   \
    \                       cur_reversed));\n    }\n\n    void dump_dfs(int t, std::vector<T>&\
    \ res, const F& inherited, bool reversed = false) const {\n        if (t == -1)\
    \ return;\n        const Node& node = (*pool)[t];\n        bool cur_reversed =\
    \ reversed ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n    \
    \    int r = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        dump_dfs(l, res, compose_for_child(inherited, t, 0), cur_reversed);\n\
    \        res.push_back(mapping_at(inherited, node.val, left_count));\n       \
    \ dump_dfs(r, res, compose_for_child(inherited, t, left_count + 1), cur_reversed);\n\
    \    }\n\n    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>&\
    \ res, const F& inherited,\n                        bool reversed = false) const\
    \ {\n        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return;\n\
    \        const Node& node = (*pool)[t];\n        bool cur_reversed = reversed\
    \ ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n        int r\
    \ = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(l, ql, qr,\
    \ offset, res, compose_for_child(inherited, t, 0), cur_reversed);\n        if\
    \ (ql <= node_pos && node_pos < qr) res.push_back(mapping_at(inherited, node.val,\
    \ left_count));\n        dump_range_dfs(r, ql, qr, node_pos + 1, res, compose_for_child(inherited,\
    \ t, left_count + 1),\n                       cur_reversed);\n    }\n\n    int\
    \ build_from_nodes(std::vector<BuildNode>& nodes, int t) const {\n        if (t\
    \ == -1) return -1;\n        int l = build_from_nodes(nodes, nodes[t].l);\n  \
    \      int r = build_from_nodes(nodes, nodes[t].r);\n        return make_node(std::move(nodes[t].val),\
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
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicLazyMonoidArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_raw_node(node.val, node.prod, node.rprod, node.lazy, node.priority,\
    \ node.count, node.rev,\n                             node.has_lazy, l, r);\n\
    \    }\n\n    explicit PersistentDynamicLazyMonoidArray(int node, std::uint32_t\
    \ state,\n                                              std::shared_ptr<std::vector<Node>>\
    \ node_pool)\n        : root(node), rng_state(state), pool(std::move(node_pool))\
    \ {}\n\n   public:\n    PersistentDynamicLazyMonoidArray()\n        : root(-1),\n\
    \          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<std::vector<Node>>()) {\n        if (rng_state\
    \ == 0) rng_state = 1;\n    }\n\n    explicit PersistentDynamicLazyMonoidArray(int\
    \ n)\n        : PersistentDynamicLazyMonoidArray(n, ActedMonoid::id()) {}\n\n\
    \    PersistentDynamicLazyMonoidArray(int n, const T& value) : PersistentDynamicLazyMonoidArray()\
    \ {\n        assert(0 <= n);\n        pool->reserve(n);\n        std::vector<T>\
    \ v(n, value);\n        root = build_from_vector(std::move(v), rng_state);\n \
    \   }\n\n    explicit PersistentDynamicLazyMonoidArray(const std::vector<T>& v)\n\
    \        : PersistentDynamicLazyMonoidArray() {\n        pool->reserve(v.size());\n\
    \        root = build_from_vector(v, rng_state);\n    }\n\n    explicit PersistentDynamicLazyMonoidArray(std::vector<T>&&\
    \ v) : PersistentDynamicLazyMonoidArray() {\n        pool->reserve(v.size());\n\
    \        root = build_from_vector(std::move(v), rng_state);\n    }\n\n    template\
    \ <typename U>\n        requires(!std::same_as<U, T>) &&\n                (requires(U\
    \ x) { ActedMonoid::make(x); } || std::convertible_to<U, T>)\n    explicit PersistentDynamicLazyMonoidArray(const\
    \ std::vector<U>& v)\n        : PersistentDynamicLazyMonoidArray() {\n       \
    \ pool->reserve(v.size());\n        root = build_from_values(v, rng_state);\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray(std::initializer_list<T> init)\n\
    \        : PersistentDynamicLazyMonoidArray(std::vector<T>(init)) {}\n\n    int\
    \ size() const {\n        return subtree_size(root);\n    }\n\n    bool empty()\
    \ const {\n        return size() == 0;\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ clear() const {\n        return PersistentDynamicLazyMonoidArray(-1, rng_state,\
    \ pool);\n    }\n\n    PersistentDynamicLazyMonoidArray insert(int pos, T value)\
    \ const {\n        assert(0 <= pos && pos <= size());\n        std::uint32_t next\
    \ = next_state(rng_state);\n        int node = make_node(std::move(value), int(next),\
    \ false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n        return\
    \ PersistentDynamicLazyMonoidArray(merge(merge(l, node), r), next, pool);\n  \
    \  }\n\n    PersistentDynamicLazyMonoidArray insert(int pos, const std::vector<T>&\
    \ v) const {\n        assert(0 <= pos && pos <= size());\n        if (v.empty())\
    \ return *this;\n        std::uint32_t next = rng_state;\n        int mid = build_from_vector(v,\
    \ next);\n        auto [l, r] = split_node(root, pos);\n        return PersistentDynamicLazyMonoidArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray insert(int\
    \ pos, std::vector<T>&& v) const {\n        assert(0 <= pos && pos <= size());\n\
    \        if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        int mid = build_from_vector(std::move(v), next);\n        auto [l, r]\
    \ = split_node(root, pos);\n        return PersistentDynamicLazyMonoidArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray insert(int\
    \ pos, std::initializer_list<T> init) const {\n        return insert(pos, std::vector<T>(init));\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray insert(int pos, const PersistentDynamicLazyMonoidArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return PersistentDynamicLazyMonoidArray(merge(merge(l,\
    \ mid), r), rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray push_back(T\
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
    \  (void)mid;\n        return PersistentDynamicLazyMonoidArray(merge(a, c), rng_state,\
    \ pool);\n    }\n\n    PersistentDynamicLazyMonoidArray erase(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        if (l == r) return\
    \ *this;\n        auto [a, b] = split_node(root, l);\n        auto [mid, c] =\
    \ split_node(b, r - l);\n        (void)mid;\n        return PersistentDynamicLazyMonoidArray(merge(a,\
    \ c), rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray pop_back()\
    \ const {\n        assert(!empty());\n        return erase(size() - 1);\n    }\n\
    \n    PersistentDynamicLazyMonoidArray pop_front() const {\n        assert(!empty());\n\
    \        return erase(0);\n    }\n\n    T get(int pos) const {\n        assert(0\
    \ <= pos && pos < size());\n        return get_value(root, pos, ActedMonoid::op_id());\n\
    \    }\n\n    T operator[](int pos) const {\n        return get(pos);\n    }\n\
    \n    T front() const {\n        assert(!empty());\n        return get(0);\n \
    \   }\n\n    T back() const {\n        assert(!empty());\n        return get(size()\
    \ - 1);\n    }\n\n    PersistentDynamicLazyMonoidArray set(int pos, T value) const\
    \ {\n        assert(0 <= pos && pos < size());\n        return PersistentDynamicLazyMonoidArray(set_node(root,\
    \ pos, std::move(value)), rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ reverse(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        return PersistentDynamicLazyMonoidArray(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ reverse() const {\n        return PersistentDynamicLazyMonoidArray(reversed_node(root),\
    \ rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray rotate(int\
    \ l, int m, int r) const {\n        assert(0 <= l && l <= m && m <= r && r <=\
    \ size());\n        if (l == m || m == r) return *this;\n        auto [a, b] =\
    \ split_node(root, l);\n        auto [c, d] = split_node(b, m - l);\n        auto\
    \ [e, f] = split_node(d, r - m);\n        return PersistentDynamicLazyMonoidArray(merge(merge(a,\
    \ e), merge(c, f)), rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ apply(int pos, const F& f) const {\n        assert(0 <= pos && pos < size());\n\
    \        return apply(pos, pos + 1, f);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ apply(int l, int r, const F& f) const {\n        assert(0 <= l && l <= r &&\
    \ r <= size());\n        if (l == r) return *this;\n        auto [a, b] = split_node(root,\
    \ l);\n        auto [mid, c] = split_node(b, r - l);\n        return PersistentDynamicLazyMonoidArray(merge(merge(a,\
    \ all_apply(mid, f)), c), rng_state, pool);\n    }\n\n    T prod(int l, int r)\
    \ const {\n        assert(0 <= l && l <= r && r <= size());\n        if (l ==\
    \ r) return ActedMonoid::id();\n        return prod_dfs(root, l, r, 0, ActedMonoid::op_id());\n\
    \    }\n\n    T all_prod() const {\n        return root == -1 ? ActedMonoid::id()\
    \ : (*pool)[root].prod;\n    }\n\n    std::pair<PersistentDynamicLazyMonoidArray,\
    \ PersistentDynamicLazyMonoidArray> split(int pos) const {\n        assert(0 <=\
    \ pos && pos <= size());\n        auto [l, r] = split_node(root, pos);\n     \
    \   return {PersistentDynamicLazyMonoidArray(l, rng_state, pool),\n          \
    \      PersistentDynamicLazyMonoidArray(r, rng_state, pool)};\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ split_off(int pos) const {\n        assert(0 <= pos && pos <= size());\n   \
    \     return PersistentDynamicLazyMonoidArray(split_node(root, pos).second, rng_state,\
    \ pool);\n    }\n\n    std::vector<T> to_vector() const {\n        std::vector<T>\
    \ res;\n        res.reserve(size());\n        dump_dfs(root, res, ActedMonoid::op_id());\n\
    \        return res;\n    }\n\n    std::vector<T> to_vector(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res,\
    \ ActedMonoid::op_id());\n        return res;\n    }\n};\n\n}  // namespace ds\n\
    }  // namespace m1une\n\n\n#line 4 \"verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp\"\
    \n\n#include <algorithm>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n\
    #include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #line 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <type_traits>\n#line 15 \"utilities/fast_io.hpp\"\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \    int _position;\n    int _length;\n\n    bool prepare_number() {\n       \
    \ if (_length - _position >= 64) return true;\n        const int remaining = _length\
    \ - _position;\n        if (remaining > 0) std::memmove(_buffer, _buffer + _position,\
    \ remaining);\n        const int added = int(std::fread(_buffer + remaining, 1,\
    \ buffer_size - remaining, _stream));\n        _position = 0;\n        _length\
    \ = remaining + added;\n        if (_length < buffer_size) _buffer[_length] =\
    \ '\\0';\n        return _length != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE*\
    \ stream = stdin)\n        : _stream(stream), _position(0), _length(0) {}\n\n\
    \    FastInput(const FastInput&) = delete;\n    FastInput& operator=(const FastInput&)\
    \ = delete;\n\n    int read_char_raw() {\n        if (_position == _length) {\n\
    \            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n  \
    \          _position = 0;\n            if (_length == 0) return EOF;\n       \
    \ }\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces() {\n\
    \        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c = read_char_raw();\n\
    \        if (c == EOF) return false;\n        --_position;\n        return true;\n\
    \    }\n\n    bool read(char& value) {\n        if (!skip_spaces()) return false;\n\
    \        value = char(read_char_raw());\n        return true;\n    }\n\n    bool\
    \ read(std::string& value) {\n        if (!skip_spaces()) return false;\n    \
    \    value.clear();\n        int c = read_char_raw();\n        while (c != EOF\
    \ && c > ' ') {\n            value.push_back(char(c));\n            c = read_char_raw();\n\
    \        }\n        return true;\n    }\n\n    bool read(bool& value) {\n    \
    \    int x;\n        if (!read(x)) return false;\n        value = x != 0;\n  \
    \      return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
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
    \ template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
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
    \n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\n\
    \          _position(0),\n          _precision(6),\n          _float_format(std::chars_format::general)\
    \ {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput& operator=(const\
    \ FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n    }\n\n \
    \   void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \        write(value.val());\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>\n\
    \    >\n    write(const Range& range) {\n        using StoredValue = internal::range_stored_value_t<const\
    \ Range>;\n        constexpr bool nested = internal::is_range_v<StoredValue>\n\
    \                                && !internal::is_string_like_v<StoredValue>;\n\
    \n        bool first = true;\n        for (const auto& value : range) {\n    \
    \        if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void set_precision(int\
    \ precision) {\n        _precision = precision;\n    }\n\n    void set_fixed(int\
    \ precision = 6) {\n        _float_format = std::chars_format::fixed;\n      \
    \  _precision = precision;\n    }\n\n    void set_general(int precision = 6) {\n\
    \        _float_format = std::chars_format::general;\n        _precision = precision;\n\
    \    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n\n    template\
    \ <class T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n\
    \        return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 8 \"verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp\"\
    \n#include <numeric>\n#include <random>\n#line 13 \"verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp\"\
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
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 15\
    \ \"verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp\"\n\n\
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;\nusing Node = AM::value_type;\n\
    using Array = m1une::ds::PersistentDynamicLazyMonoidArray<AM>;\n\nstruct StringNoopActedMonoid\
    \ {\n    using value_type = std::string;\n    using operator_type = int;\n\n \
    \   static std::string id() {\n        return \"\";\n    }\n\n    static std::string\
    \ op(const std::string& a, const std::string& b) {\n        return a + b;\n  \
    \  }\n\n    static int op_id() {\n        return 0;\n    }\n\n    static int op_comp(int\
    \ f, int g) {\n        return f + g;\n    }\n\n    static std::string mapping(int,\
    \ const std::string& x) {\n        return x;\n    }\n};\n\nstd::vector<Node> make_nodes(const\
    \ std::vector<long long>& a) {\n    std::vector<Node> res;\n    res.reserve(a.size());\n\
    \    for (long long x : a) res.push_back(AM::make(x));\n    return res;\n}\n\n\
    std::vector<long long> sums(const std::vector<Node>& a) {\n    std::vector<long\
    \ long> res;\n    res.reserve(a.size());\n    for (Node x : a) res.push_back(x.sum);\n\
    \    return res;\n}\n\nlong long sum_range(const std::vector<long long>& a, int\
    \ l, int r) {\n    return std::accumulate(a.begin() + l, a.begin() + r, 0LL);\n\
    }\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    using StringArray = m1une::ds::PersistentDynamicLazyMonoidArray<StringNoopActedMonoid>;\n\
    \    StringArray s = {\"a\", \"b\", \"c\", \"d\"};\n    StringArray sr = s.reverse(1,\
    \ 4);\n    assert(s.prod(0, 4) == \"abcd\");\n    assert(sr.to_vector() == (std::vector<std::string>{\"\
    a\", \"d\", \"c\", \"b\"}));\n    assert(sr.prod(1, 4) == \"dcb\");\n\n    Array\
    \ a(std::vector<long long>{1, 2, 3, 4, 5});\n    Array b = a.apply(1, 4, 10);\n\
    \    Array c = b.reverse(1, 5);\n    Array d = c.insert(2, AM::make(100));\n \
    \   Array e = d.set(0, AM::make(-1));\n    Array f = e.erase(3);\n\n    assert(sums(a.to_vector())\
    \ == (std::vector<long long>{1, 2, 3, 4, 5}));\n    assert(sums(b.to_vector())\
    \ == (std::vector<long long>{1, 12, 13, 14, 5}));\n    assert(sums(c.to_vector())\
    \ == (std::vector<long long>{1, 5, 14, 13, 12}));\n    assert(sums(d.to_vector())\
    \ == (std::vector<long long>{1, 5, 100, 14, 13, 12}));\n    assert(sums(e.to_vector())\
    \ == (std::vector<long long>{-1, 5, 100, 14, 13, 12}));\n    assert(sums(f.to_vector())\
    \ == (std::vector<long long>{-1, 5, 100, 13, 12}));\n    assert(b.prod(0, 5).sum\
    \ == 45);\n    assert(c.prod(1, 4).sum == 32);\n    assert(f.all_prod().sum ==\
    \ 129);\n    assert(f.get(2).sum == 100);\n    assert(f.front().sum == -1);\n\
    \    assert(f.back().sum == 12);\n\n    auto [left, right] = f.split(3);\n   \
    \ assert(sums(left.to_vector()) == (std::vector<long long>{-1, 5, 100}));\n  \
    \  assert(sums(right.to_vector()) == (std::vector<long long>{13, 12}));\n    assert(sums(left.append(right).to_vector())\
    \ == sums(f.to_vector()));\n    assert(sums(f.split_off(4).to_vector()) == (std::vector<long\
    \ long>{12}));\n    assert(f.clear().empty());\n\n    std::mt19937 rng(2);\n \
    \   std::vector<std::pair<Array, std::vector<long long>>> versions;\n    versions.push_back({Array(),\
    \ {}});\n    for (int step = 0; step < 300; step++) {\n        int id = int(rng()\
    \ % versions.size());\n        Array cur = versions[id].first;\n        std::vector<long\
    \ long> expected = versions[id].second;\n        assert(sums(cur.to_vector())\
    \ == expected);\n\n        Array next = cur;\n        std::vector<long long> next_expected\
    \ = expected;\n        int op = int(rng() % 9);\n        if (op == 0 || next_expected.empty())\
    \ {\n            int pos = int(rng() % (next_expected.size() + 1));\n        \
    \    long long value = int(rng() % 100) - 50;\n            next = cur.insert(pos,\
    \ AM::make(value));\n            next_expected.insert(next_expected.begin() +\
    \ pos, value);\n        } else if (op == 1) {\n            int pos = int(rng()\
    \ % next_expected.size());\n            next = cur.erase(pos);\n            next_expected.erase(next_expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int r = int(rng() % (next_expected.size() + 1));\n     \
    \       if (l > r) std::swap(l, r);\n            next = cur.erase(l, r);\n   \
    \         next_expected.erase(next_expected.begin() + l, next_expected.begin()\
    \ + r);\n        } else if (op == 3) {\n            int pos = int(rng() % next_expected.size());\n\
    \            long long value = int(rng() % 100) - 50;\n            next = cur.set(pos,\
    \ AM::make(value));\n            next_expected[pos] = value;\n        } else if\
    \ (op == 4) {\n            int l = int(rng() % (next_expected.size() + 1));\n\
    \            int r = int(rng() % (next_expected.size() + 1));\n            if\
    \ (l > r) std::swap(l, r);\n            long long add = int(rng() % 41) - 20;\n\
    \            next = cur.apply(l, r, add);\n            for (int i = l; i < r;\
    \ i++) next_expected[i] += add;\n        } else if (op == 5) {\n            int\
    \ l = int(rng() % (next_expected.size() + 1));\n            int r = int(rng()\
    \ % (next_expected.size() + 1));\n            if (l > r) std::swap(l, r);\n  \
    \          next = cur.reverse(l, r);\n            std::reverse(next_expected.begin()\
    \ + l, next_expected.begin() + r);\n        } else if (op == 6) {\n          \
    \  int l = int(rng() % (next_expected.size() + 1));\n            int m = int(rng()\
    \ % (next_expected.size() + 1));\n            int r = int(rng() % (next_expected.size()\
    \ + 1));\n            if (l > m) std::swap(l, m);\n            if (m > r) std::swap(m,\
    \ r);\n            if (l > m) std::swap(l, m);\n            next = cur.rotate(l,\
    \ m, r);\n            std::rotate(next_expected.begin() + l, next_expected.begin()\
    \ + m, next_expected.begin() + r);\n        } else if (op == 7 && next_expected.size()\
    \ < 80) {\n            int other_id = int(rng() % versions.size());\n        \
    \    next = cur.append(versions[other_id].first);\n            next_expected.insert(next_expected.end(),\
    \ versions[other_id].second.begin(), versions[other_id].second.end());\n     \
    \   } else {\n            next = cur.reverse();\n            std::reverse(next_expected.begin(),\
    \ next_expected.end());\n        }\n\n        assert(sums(cur.to_vector()) ==\
    \ expected);\n        assert(sums(next.to_vector()) == next_expected);\n     \
    \   assert(next.all_prod().sum == sum_range(next_expected, 0, int(next_expected.size())));\n\
    \        for (int l = 0; l <= int(next_expected.size()); l++) {\n            for\
    \ (int r = l; r <= int(next_expected.size()); r++) {\n                assert(next.prod(l,\
    \ r).sum == sum_range(next_expected, l, r));\n            }\n        }\n     \
    \   if (!next_expected.empty()) {\n            int pos = int(rng() % next_expected.size());\n\
    \            assert(next[pos].sum == next_expected[pos]);\n        }\n       \
    \ int split_pos = int(rng() % (next_expected.size() + 1));\n        auto [prefix,\
    \ suffix] = next.split(split_pos);\n        assert(sums(prefix.to_vector()) ==\
    \ std::vector<long long>(next_expected.begin(), next_expected.begin() + split_pos));\n\
    \        assert(sums(suffix.to_vector()) == std::vector<long long>(next_expected.begin()\
    \ + split_pos, next_expected.end()));\n\n        if (next_expected.size() <= 100)\
    \ versions.push_back({next, next_expected});\n    }\n\n    long long x, y;\n \
    \   fast_input >> x >> y;\n    fast_output << x + y << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <numeric>\n#include <random>\n#include <string>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../../acted_monoid/range_add_range_sum.hpp\"\
    \n\nusing AM = m1une::acted_monoid::RangeAddRangeSum<long long>;\nusing Node =\
    \ AM::value_type;\nusing Array = m1une::ds::PersistentDynamicLazyMonoidArray<AM>;\n\
    \nstruct StringNoopActedMonoid {\n    using value_type = std::string;\n    using\
    \ operator_type = int;\n\n    static std::string id() {\n        return \"\";\n\
    \    }\n\n    static std::string op(const std::string& a, const std::string& b)\
    \ {\n        return a + b;\n    }\n\n    static int op_id() {\n        return\
    \ 0;\n    }\n\n    static int op_comp(int f, int g) {\n        return f + g;\n\
    \    }\n\n    static std::string mapping(int, const std::string& x) {\n      \
    \  return x;\n    }\n};\n\nstd::vector<Node> make_nodes(const std::vector<long\
    \ long>& a) {\n    std::vector<Node> res;\n    res.reserve(a.size());\n    for\
    \ (long long x : a) res.push_back(AM::make(x));\n    return res;\n}\n\nstd::vector<long\
    \ long> sums(const std::vector<Node>& a) {\n    std::vector<long long> res;\n\
    \    res.reserve(a.size());\n    for (Node x : a) res.push_back(x.sum);\n    return\
    \ res;\n}\n\nlong long sum_range(const std::vector<long long>& a, int l, int r)\
    \ {\n    return std::accumulate(a.begin() + l, a.begin() + r, 0LL);\n}\n\nint\
    \ main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    using StringArray = m1une::ds::PersistentDynamicLazyMonoidArray<StringNoopActedMonoid>;\n\
    \    StringArray s = {\"a\", \"b\", \"c\", \"d\"};\n    StringArray sr = s.reverse(1,\
    \ 4);\n    assert(s.prod(0, 4) == \"abcd\");\n    assert(sr.to_vector() == (std::vector<std::string>{\"\
    a\", \"d\", \"c\", \"b\"}));\n    assert(sr.prod(1, 4) == \"dcb\");\n\n    Array\
    \ a(std::vector<long long>{1, 2, 3, 4, 5});\n    Array b = a.apply(1, 4, 10);\n\
    \    Array c = b.reverse(1, 5);\n    Array d = c.insert(2, AM::make(100));\n \
    \   Array e = d.set(0, AM::make(-1));\n    Array f = e.erase(3);\n\n    assert(sums(a.to_vector())\
    \ == (std::vector<long long>{1, 2, 3, 4, 5}));\n    assert(sums(b.to_vector())\
    \ == (std::vector<long long>{1, 12, 13, 14, 5}));\n    assert(sums(c.to_vector())\
    \ == (std::vector<long long>{1, 5, 14, 13, 12}));\n    assert(sums(d.to_vector())\
    \ == (std::vector<long long>{1, 5, 100, 14, 13, 12}));\n    assert(sums(e.to_vector())\
    \ == (std::vector<long long>{-1, 5, 100, 14, 13, 12}));\n    assert(sums(f.to_vector())\
    \ == (std::vector<long long>{-1, 5, 100, 13, 12}));\n    assert(b.prod(0, 5).sum\
    \ == 45);\n    assert(c.prod(1, 4).sum == 32);\n    assert(f.all_prod().sum ==\
    \ 129);\n    assert(f.get(2).sum == 100);\n    assert(f.front().sum == -1);\n\
    \    assert(f.back().sum == 12);\n\n    auto [left, right] = f.split(3);\n   \
    \ assert(sums(left.to_vector()) == (std::vector<long long>{-1, 5, 100}));\n  \
    \  assert(sums(right.to_vector()) == (std::vector<long long>{13, 12}));\n    assert(sums(left.append(right).to_vector())\
    \ == sums(f.to_vector()));\n    assert(sums(f.split_off(4).to_vector()) == (std::vector<long\
    \ long>{12}));\n    assert(f.clear().empty());\n\n    std::mt19937 rng(2);\n \
    \   std::vector<std::pair<Array, std::vector<long long>>> versions;\n    versions.push_back({Array(),\
    \ {}});\n    for (int step = 0; step < 300; step++) {\n        int id = int(rng()\
    \ % versions.size());\n        Array cur = versions[id].first;\n        std::vector<long\
    \ long> expected = versions[id].second;\n        assert(sums(cur.to_vector())\
    \ == expected);\n\n        Array next = cur;\n        std::vector<long long> next_expected\
    \ = expected;\n        int op = int(rng() % 9);\n        if (op == 0 || next_expected.empty())\
    \ {\n            int pos = int(rng() % (next_expected.size() + 1));\n        \
    \    long long value = int(rng() % 100) - 50;\n            next = cur.insert(pos,\
    \ AM::make(value));\n            next_expected.insert(next_expected.begin() +\
    \ pos, value);\n        } else if (op == 1) {\n            int pos = int(rng()\
    \ % next_expected.size());\n            next = cur.erase(pos);\n            next_expected.erase(next_expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int r = int(rng() % (next_expected.size() + 1));\n     \
    \       if (l > r) std::swap(l, r);\n            next = cur.erase(l, r);\n   \
    \         next_expected.erase(next_expected.begin() + l, next_expected.begin()\
    \ + r);\n        } else if (op == 3) {\n            int pos = int(rng() % next_expected.size());\n\
    \            long long value = int(rng() % 100) - 50;\n            next = cur.set(pos,\
    \ AM::make(value));\n            next_expected[pos] = value;\n        } else if\
    \ (op == 4) {\n            int l = int(rng() % (next_expected.size() + 1));\n\
    \            int r = int(rng() % (next_expected.size() + 1));\n            if\
    \ (l > r) std::swap(l, r);\n            long long add = int(rng() % 41) - 20;\n\
    \            next = cur.apply(l, r, add);\n            for (int i = l; i < r;\
    \ i++) next_expected[i] += add;\n        } else if (op == 5) {\n            int\
    \ l = int(rng() % (next_expected.size() + 1));\n            int r = int(rng()\
    \ % (next_expected.size() + 1));\n            if (l > r) std::swap(l, r);\n  \
    \          next = cur.reverse(l, r);\n            std::reverse(next_expected.begin()\
    \ + l, next_expected.begin() + r);\n        } else if (op == 6) {\n          \
    \  int l = int(rng() % (next_expected.size() + 1));\n            int m = int(rng()\
    \ % (next_expected.size() + 1));\n            int r = int(rng() % (next_expected.size()\
    \ + 1));\n            if (l > m) std::swap(l, m);\n            if (m > r) std::swap(m,\
    \ r);\n            if (l > m) std::swap(l, m);\n            next = cur.rotate(l,\
    \ m, r);\n            std::rotate(next_expected.begin() + l, next_expected.begin()\
    \ + m, next_expected.begin() + r);\n        } else if (op == 7 && next_expected.size()\
    \ < 80) {\n            int other_id = int(rng() % versions.size());\n        \
    \    next = cur.append(versions[other_id].first);\n            next_expected.insert(next_expected.end(),\
    \ versions[other_id].second.begin(), versions[other_id].second.end());\n     \
    \   } else {\n            next = cur.reverse();\n            std::reverse(next_expected.begin(),\
    \ next_expected.end());\n        }\n\n        assert(sums(cur.to_vector()) ==\
    \ expected);\n        assert(sums(next.to_vector()) == next_expected);\n     \
    \   assert(next.all_prod().sum == sum_range(next_expected, 0, int(next_expected.size())));\n\
    \        for (int l = 0; l <= int(next_expected.size()); l++) {\n            for\
    \ (int r = l; r <= int(next_expected.size()); r++) {\n                assert(next.prod(l,\
    \ r).sum == sum_range(next_expected, l, r));\n            }\n        }\n     \
    \   if (!next_expected.empty()) {\n            int pos = int(rng() % next_expected.size());\n\
    \            assert(next[pos].sum == next_expected[pos]);\n        }\n       \
    \ int split_pos = int(rng() % (next_expected.size() + 1));\n        auto [prefix,\
    \ suffix] = next.split(split_pos);\n        assert(sums(prefix.to_vector()) ==\
    \ std::vector<long long>(next_expected.begin(), next_expected.begin() + split_pos));\n\
    \        assert(sums(suffix.to_vector()) == std::vector<long long>(next_expected.begin()\
    \ + split_pos, next_expected.end()));\n\n        if (next_expected.size() <= 100)\
    \ versions.push_back({next, next_expected});\n    }\n\n    long long x, y;\n \
    \   fast_input >> x >> y;\n    fast_output << x + y << '\\n';\n}\n"
  dependsOn:
  - ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
  - acted_monoid/concept.hpp
  - utilities/fast_io.hpp
  - acted_monoid/range_add_range_sum.hpp
  isVerificationFile: true
  path: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp
- /verify/verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp.html
title: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp
---
