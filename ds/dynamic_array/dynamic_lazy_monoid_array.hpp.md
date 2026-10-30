---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/dynamic_lazy_monoid_array.test.cpp
    title: verify/ds/dynamic_array/dynamic_lazy_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp
    title: verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dynamic_array/dynamic_lazy_monoid_array.hpp\"\n\n\n\n\
    #include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n\
    #include <initializer_list>\n#include <type_traits>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
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
    \n\n#line 14 \"ds/dynamic_array/dynamic_lazy_monoid_array.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid>\n\
    struct DynamicLazyMonoidArray {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    static\
    \ constexpr bool value_commutative = [] {\n        if constexpr (requires { ActedMonoid::commutative;\
    \ }) {\n            return bool(ActedMonoid::commutative);\n        } else {\n\
    \            return false;\n        }\n    }();\n\n    struct EmptyReverseProduct\
    \ {};\n    using ReverseProduct = std::conditional_t<value_commutative, EmptyReverseProduct,\
    \ T>;\n\n    static constexpr bool count_stored_in_value = requires(const T& value)\
    \ {\n        { ActedMonoid::size(value) } -> std::convertible_to<int>;\n    };\n\
    \n    struct EmptyCount {};\n    using Count = std::conditional_t<count_stored_in_value,\
    \ EmptyCount, int>;\n\n    static ReverseProduct make_reverse_product(const T&\
    \ value) {\n        if constexpr (value_commutative) {\n            return {};\n\
    \        } else {\n            return value;\n        }\n    }\n\n    static Count\
    \ make_count(int count) {\n        if constexpr (count_stored_in_value) {\n  \
    \          return {};\n        } else {\n            return count;\n        }\n\
    \    }\n\n    struct Node {\n        T val;\n        T prod;\n        [[no_unique_address]]\
    \ ReverseProduct rprod;\n        F lazy;\n        std::uint32_t priority : 30;\n\
    \        std::uint32_t rev : 1;\n        std::uint32_t has_lazy : 1;\n       \
    \ [[no_unique_address]] Count count;\n        int l, r;\n\n        Node()\n  \
    \          : val(ActedMonoid::id()),\n              prod(ActedMonoid::id()),\n\
    \              rprod(make_reverse_product(prod)),\n              lazy(ActedMonoid::op_id()),\n\
    \              priority(0),\n              rev(false),\n              has_lazy(false),\n\
    \              count(make_count(0)),\n              l(0),\n              r(0)\
    \ {}\n\n        Node(T value, int node_priority)\n            : val(std::move(value)),\n\
    \              prod(val),\n              rprod(make_reverse_product(val)),\n \
    \             lazy(ActedMonoid::op_id()),\n              priority(std::uint32_t(node_priority)),\n\
    \              rev(false),\n              has_lazy(false),\n              count(make_count(1)),\n\
    \              l(0),\n              r(0) {}\n    };\n\n    std::vector<Node> pool;\n\
    \    int root;\n    int free_head;\n    std::uint32_t rng_state;\n\n    int node_count(int\
    \ t) const {\n        if constexpr (count_stored_in_value) {\n            return\
    \ int(ActedMonoid::size(pool[t].prod));\n        } else {\n            return\
    \ pool[t].count;\n        }\n    }\n\n    void set_node_count(int t, int count)\
    \ {\n        if constexpr (!count_stored_in_value) {\n            pool[t].count\
    \ = count;\n        }\n    }\n\n    template <typename U>\n    static T make_value(const\
    \ U& value) {\n        if constexpr (requires(U x) { ActedMonoid::make(x); })\
    \ {\n            return ActedMonoid::make(value);\n        } else {\n        \
    \    return static_cast<T>(value);\n        }\n    }\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ord) {\n        if constexpr (requires(F g,\
    \ T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n            return\
    \ ActedMonoid::mapping(f, value, ord);\n        } else {\n            return ActedMonoid::mapping(f,\
    \ value);\n        }\n    }\n\n    static F shift_operator(const F& f, long long\
    \ ord) {\n        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g,\
    \ i); }) {\n            return ActedMonoid::op_shift(f, ord);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    static F reverse_operator(const\
    \ F& f, long long size) {\n        if constexpr (requires(F g, long long n) {\
    \ ActedMonoid::op_reverse(g, n); }) {\n            return ActedMonoid::op_reverse(f,\
    \ size);\n        } else {\n            return f;\n        }\n    }\n\n    int\
    \ new_node(T value) {\n        int priority = next_priority();\n        if (free_head)\
    \ {\n            int res = free_head;\n            free_head = pool[res].l;\n\
    \            pool[res] = Node(std::move(value), priority);\n            return\
    \ res;\n        }\n        pool.push_back(Node(std::move(value), priority));\n\
    \        return int(pool.size()) - 1;\n    }\n\n    void release_node(int t) {\n\
    \        pool[t].l = free_head;\n        free_head = t;\n    }\n\n    int next_priority()\
    \ {\n        rng_state ^= rng_state << 13;\n        rng_state ^= rng_state >>\
    \ 17;\n        rng_state ^= rng_state << 5;\n        return int(rng_state);\n\
    \    }\n\n    void update(int t) {\n        if (!t) return;\n        int l = pool[t].l;\n\
    \        int r = pool[t].r;\n        set_node_count(t, 1 + node_count(l) + node_count(r));\n\
    \        pool[t].prod = ActedMonoid::op(ActedMonoid::op(pool[l].prod, pool[t].val),\
    \ pool[r].prod);\n        if constexpr (!value_commutative) {\n            pool[t].rprod\
    \ = ActedMonoid::op(ActedMonoid::op(pool[r].rprod, pool[t].val), pool[l].rprod);\n\
    \        }\n    }\n\n    void all_apply(int t, const F& f) {\n        if (!t)\
    \ return;\n        int left_count = node_count(pool[t].l);\n        pool[t].val\
    \ = mapping_at(f, pool[t].val, left_count);\n        pool[t].prod = mapping_at(f,\
    \ pool[t].prod, 0);\n        if constexpr (!value_commutative) {\n           \
    \ pool[t].rprod = mapping_at(reverse_operator(f, node_count(t)), pool[t].rprod,\
    \ 0);\n        }\n        pool[t].lazy = ActedMonoid::op_comp(f, pool[t].lazy);\n\
    \        pool[t].has_lazy = true;\n    }\n\n    void apply_reverse(int t) {\n\
    \        if (!t) return;\n        std::swap(pool[t].l, pool[t].r);\n        pool[t].rev\
    \ = !pool[t].rev;\n        if constexpr (!value_commutative) {\n            std::swap(pool[t].prod,\
    \ pool[t].rprod);\n        }\n        if (pool[t].has_lazy) {\n            pool[t].lazy\
    \ = reverse_operator(pool[t].lazy, node_count(t));\n        }\n    }\n\n    void\
    \ push(int t) {\n        if (!t) return;\n        if (pool[t].rev) {\n       \
    \     apply_reverse(pool[t].l);\n            apply_reverse(pool[t].r);\n     \
    \       pool[t].rev = false;\n        }\n        if (pool[t].has_lazy) {\n   \
    \         all_apply(pool[t].l, pool[t].lazy);\n            all_apply(pool[t].r,\
    \ shift_operator(pool[t].lazy, node_count(pool[t].l) + 1));\n            pool[t].lazy\
    \ = ActedMonoid::op_id();\n            pool[t].has_lazy = false;\n        }\n\
    \    }\n\n    void split(int t, int pos, int& l, int& r) {\n        if (!t) {\n\
    \            l = r = 0;\n            return;\n        }\n        if (pos == 0)\
    \ {\n            l = 0;\n            r = t;\n            return;\n        }\n\
    \        if (pos == node_count(t)) {\n            l = t;\n            r = 0;\n\
    \            return;\n        }\n        push(t);\n        int left_count = node_count(pool[t].l);\n\
    \        if (pos == left_count) {\n            l = pool[t].l;\n            pool[t].l\
    \ = 0;\n            update(t);\n            r = t;\n            return;\n    \
    \    }\n        if (pos == left_count + 1) {\n            r = pool[t].r;\n   \
    \         pool[t].r = 0;\n            update(t);\n            l = t;\n       \
    \     return;\n        }\n        if (pos <= left_count) {\n            split(pool[t].l,\
    \ pos, l, pool[t].l);\n            r = t;\n        } else {\n            split(pool[t].r,\
    \ pos - left_count - 1, pool[t].r, r);\n            l = t;\n        }\n      \
    \  update(t);\n    }\n\n    int merge(int l, int r) {\n        if (!l || !r) return\
    \ l ? l : r;\n        if (pool[l].priority > pool[r].priority) {\n           \
    \ push(l);\n            if (pool[l].r) {\n                pool[l].r = merge(pool[l].r,\
    \ r);\n            } else {\n                pool[l].r = r;\n            }\n \
    \           update(l);\n            return l;\n        } else {\n            push(r);\n\
    \            if (pool[r].l) {\n                pool[r].l = merge(l, pool[r].l);\n\
    \            } else {\n                pool[r].l = l;\n            }\n       \
    \     update(r);\n            return r;\n        }\n    }\n\n    void split_three(int\
    \ t, int ql, int qr, int& a, int& b, int& c) {\n        if (ql == qr) {\n    \
    \        split(t, ql, a, c);\n            b = 0;\n            return;\n      \
    \  }\n        if (ql == 0 && qr == node_count(t)) {\n            a = c = 0;\n\
    \            b = t;\n            return;\n        }\n        push(t);\n      \
    \  int left_count = node_count(pool[t].l);\n        if (qr <= left_count) {\n\
    \            split_three(pool[t].l, ql, qr, a, b, pool[t].l);\n            c =\
    \ t;\n            update(t);\n        } else if (left_count < ql) {\n        \
    \    split_three(pool[t].r, ql - left_count - 1, qr - left_count - 1, pool[t].r,\
    \ b, c);\n            a = t;\n            update(t);\n        } else {\n     \
    \       split(pool[t].l, ql, a, pool[t].l);\n            split(pool[t].r, qr -\
    \ left_count - 1, pool[t].r, c);\n            b = t;\n            update(t);\n\
    \        }\n    }\n\n    int merge_three(int a, int b, int c) {\n        if (!a)\
    \ return merge(b, c);\n        if (!b) return merge(a, c);\n        if (!c) return\
    \ merge(a, b);\n        std::uint32_t pa = pool[a].priority;\n        std::uint32_t\
    \ pb = pool[b].priority;\n        std::uint32_t pc = pool[c].priority;\n     \
    \   if (pb >= pa && pb >= pc) {\n            push(b);\n            pool[b].l =\
    \ merge(a, pool[b].l);\n            pool[b].r = merge(pool[b].r, c);\n       \
    \     update(b);\n            return b;\n        }\n        if (pa >= pc) {\n\
    \            push(a);\n            pool[a].r = merge_three(pool[a].r, b, c);\n\
    \            update(a);\n            return a;\n        }\n        push(c);\n\
    \        pool[c].l = merge_three(a, b, pool[c].l);\n        update(c);\n     \
    \   return c;\n    }\n\n    int insert_node(int t, int pos, int node) {\n    \
    \    if (!t) return node;\n        if (pool[node].priority > pool[t].priority)\
    \ {\n            split(t, pos, pool[node].l, pool[node].r);\n            update(node);\n\
    \            return node;\n        }\n        push(t);\n        int left_count\
    \ = node_count(pool[t].l);\n        if (pos <= left_count) {\n            pool[t].l\
    \ = insert_node(pool[t].l, pos, node);\n        } else {\n            pool[t].r\
    \ = insert_node(pool[t].r, pos - left_count - 1, node);\n        }\n        update(t);\n\
    \        return t;\n    }\n\n    int erase_node(int t, int pos) {\n        push(t);\n\
    \        int left_count = node_count(pool[t].l);\n        if (pos < left_count)\
    \ {\n            pool[t].l = erase_node(pool[t].l, pos);\n            update(t);\n\
    \            return t;\n        }\n        if (pos == left_count) {\n        \
    \    int res = merge(pool[t].l, pool[t].r);\n            release_node(t);\n  \
    \          return res;\n        }\n        pool[t].r = erase_node(pool[t].r, pos\
    \ - left_count - 1);\n        update(t);\n        return t;\n    }\n\n    void\
    \ set_node(int t, int pos, T value) {\n        push(t);\n        int left_count\
    \ = node_count(pool[t].l);\n        if (pos < left_count) {\n            set_node(pool[t].l,\
    \ pos, std::move(value));\n        } else if (pos == left_count) {\n         \
    \   pool[t].val = std::move(value);\n        } else {\n            set_node(pool[t].r,\
    \ pos - left_count - 1, std::move(value));\n        }\n        update(t);\n  \
    \  }\n\n    void apply_node(int t, int pos, const F& f) {\n        push(t);\n\
    \        int left_count = node_count(pool[t].l);\n        if (pos < left_count)\
    \ {\n            apply_node(pool[t].l, pos, f);\n        } else if (pos == left_count)\
    \ {\n            pool[t].val = mapping_at(f, pool[t].val, 0);\n        } else\
    \ {\n            apply_node(pool[t].r, pos - left_count - 1, f);\n        }\n\
    \        update(t);\n    }\n\n    void apply_range(int t, int ql, int qr, const\
    \ F& f) {\n        if (ql == 0 && qr == node_count(t)) {\n            all_apply(t,\
    \ f);\n            return;\n        }\n        push(t);\n        int left_count\
    \ = node_count(pool[t].l);\n        if (qr <= left_count) {\n            apply_range(pool[t].l,\
    \ ql, qr, f);\n        } else if (left_count < ql) {\n            apply_range(pool[t].r,\
    \ ql - left_count - 1, qr - left_count - 1, f);\n        } else {\n          \
    \  if (ql < left_count) {\n                apply_range(pool[t].l, ql, left_count,\
    \ f);\n            }\n            pool[t].val = mapping_at(f, pool[t].val, left_count\
    \ - ql);\n            if (left_count + 1 < qr) {\n                apply_range(pool[t].r,\
    \ 0, qr - left_count - 1,\n                            shift_operator(f, left_count\
    \ + 1 - ql));\n            }\n        }\n        update(t);\n    }\n\n    T prod_range(int\
    \ t, int ql, int qr) {\n        if (ql == 0 && qr == node_count(t)) return pool[t].prod;\n\
    \        push(t);\n        int left_count = node_count(pool[t].l);\n        if\
    \ (qr <= left_count) {\n            return prod_range(pool[t].l, ql, qr);\n  \
    \      }\n        if (left_count < ql) {\n            return prod_range(pool[t].r,\
    \ ql - left_count - 1, qr - left_count - 1);\n        }\n        T res = pool[t].val;\n\
    \        if (ql < left_count) {\n            res = ActedMonoid::op(prod_range(pool[t].l,\
    \ ql, left_count), res);\n        }\n        if (left_count + 1 < qr) {\n    \
    \        res = ActedMonoid::op(res, prod_range(pool[t].r, 0, qr - left_count -\
    \ 1));\n        }\n        return res;\n    }\n\n    int find_node(int t, int\
    \ pos) {\n        while (t) {\n            push(t);\n            int left_count\
    \ = node_count(pool[t].l);\n            if (pos < left_count) {\n            \
    \    t = pool[t].l;\n            } else if (pos == left_count) {\n           \
    \     return t;\n            } else {\n                pos -= left_count + 1;\n\
    \                t = pool[t].r;\n            }\n        }\n        return 0;\n\
    \    }\n\n    void dump_dfs(int t, std::vector<T>& res) {\n        if (!t) return;\n\
    \        push(t);\n        dump_dfs(pool[t].l, res);\n        res.push_back(pool[t].val);\n\
    \        dump_dfs(pool[t].r, res);\n        update(t);\n    }\n\n    void dump_range_dfs(int\
    \ t, int ql, int qr, int offset, std::vector<T>& res) {\n        if (!t || qr\
    \ <= offset || offset + node_count(t) <= ql) return;\n        push(t);\n     \
    \   int left_count = node_count(pool[t].l);\n        int node_pos = offset + left_count;\n\
    \        dump_range_dfs(pool[t].l, ql, qr, offset, res);\n        if (ql <= node_pos\
    \ && node_pos < qr) {\n            res.push_back(pool[t].val);\n        }\n  \
    \      dump_range_dfs(pool[t].r, ql, qr, node_pos + 1, res);\n        update(t);\n\
    \    }\n\n    int clone_subtree_from(const DynamicLazyMonoidArray& other, int\
    \ t) {\n        if (!t) return 0;\n        int res = int(pool.size());\n     \
    \   pool.push_back(other.pool[t]);\n        pool[res].l = clone_subtree_from(other,\
    \ other.pool[t].l);\n        pool[res].r = clone_subtree_from(other, other.pool[t].r);\n\
    \        return res;\n    }\n\n    void update_dfs(int t) {\n        if (!t) return;\n\
    \        update_dfs(pool[t].l);\n        update_dfs(pool[t].r);\n        update(t);\n\
    \    }\n\n    int build_cartesian(int first, int last) {\n        if (first ==\
    \ last) return 0;\n        std::vector<int> stack;\n        stack.reserve(last\
    \ - first);\n        for (int i = first; i < last; i++) {\n            int left_child\
    \ = 0;\n            while (!stack.empty() && pool[stack.back()].priority < pool[i].priority)\
    \ {\n                left_child = stack.back();\n                stack.pop_back();\n\
    \            }\n            pool[i].l = left_child;\n            if (!stack.empty())\
    \ {\n                pool[stack.back()].r = i;\n            }\n            stack.push_back(i);\n\
    \        }\n        int res = stack.front();\n        update_dfs(res);\n     \
    \   return res;\n    }\n\n    int build_from_vector(const std::vector<T>& v) {\n\
    \        int first = int(pool.size());\n        pool.reserve(pool.size() + v.size());\n\
    \        for (const T& x : v) {\n            new_node(x);\n        }\n       \
    \ return build_cartesian(first, int(pool.size()));\n    }\n\n    int build_from_vector(std::vector<T>&&\
    \ v) {\n        int first = int(pool.size());\n        pool.reserve(pool.size()\
    \ + v.size());\n        for (T& x : v) {\n            new_node(std::move(x));\n\
    \        }\n        return build_cartesian(first, int(pool.size()));\n    }\n\n\
    \    template <typename U>\n    int build_from_values(const std::vector<U>& v)\
    \ {\n        int first = int(pool.size());\n        pool.reserve(pool.size() +\
    \ v.size());\n        for (const U& x : v) {\n            new_node(make_value(x));\n\
    \        }\n        return build_cartesian(first, int(pool.size()));\n    }\n\n\
    \    void reset_to_empty() {\n        pool.clear();\n        pool.push_back(Node());\n\
    \        root = 0;\n        free_head = 0;\n    }\n\n   public:\n    DynamicLazyMonoidArray()\n\
    \        : root(0),\n          free_head(0),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        pool.push_back(Node());\n        if (rng_state == 0) rng_state =\
    \ 1;\n    }\n\n    DynamicLazyMonoidArray(const DynamicLazyMonoidArray& other)\n\
    \        : pool(other.pool), root(other.root), free_head(other.free_head), rng_state(other.rng_state)\
    \ {}\n\n    DynamicLazyMonoidArray(DynamicLazyMonoidArray&& other) noexcept\n\
    \        : pool(std::move(other.pool)), root(other.root), free_head(other.free_head),\
    \ rng_state(other.rng_state) {\n        other.reset_to_empty();\n    }\n\n   \
    \ DynamicLazyMonoidArray& operator=(const DynamicLazyMonoidArray& other) {\n \
    \       if (this != &other) {\n            pool = other.pool;\n            root\
    \ = other.root;\n            free_head = other.free_head;\n            rng_state\
    \ = other.rng_state;\n        }\n        return *this;\n    }\n\n    DynamicLazyMonoidArray&\
    \ operator=(DynamicLazyMonoidArray&& other) noexcept {\n        if (this != &other)\
    \ {\n            pool = std::move(other.pool);\n            root = other.root;\n\
    \            free_head = other.free_head;\n            rng_state = other.rng_state;\n\
    \            other.reset_to_empty();\n        }\n        return *this;\n    }\n\
    \n    explicit DynamicLazyMonoidArray(int n) : DynamicLazyMonoidArray(n, ActedMonoid::id())\
    \ {}\n\n    DynamicLazyMonoidArray(int n, const T& value) : DynamicLazyMonoidArray()\
    \ {\n        assert(0 <= n);\n        pool.reserve(n + 1);\n        int first\
    \ = int(pool.size());\n        for (int i = 0; i < n; i++) {\n            new_node(value);\n\
    \        }\n        root = build_cartesian(first, int(pool.size()));\n    }\n\n\
    \    explicit DynamicLazyMonoidArray(const std::vector<T>& v) : DynamicLazyMonoidArray()\
    \ {\n        pool.reserve(v.size() + 1);\n        root = build_from_vector(v);\n\
    \    }\n\n    explicit DynamicLazyMonoidArray(std::vector<T>&& v) : DynamicLazyMonoidArray()\
    \ {\n        pool.reserve(v.size() + 1);\n        root = build_from_vector(std::move(v));\n\
    \    }\n\n    template <typename U>\n        requires(!std::same_as<U, T>) &&\
    \ (requires(U x) { ActedMonoid::make(x); } || std::convertible_to<U, T>)\n   \
    \ explicit DynamicLazyMonoidArray(const std::vector<U>& v) : DynamicLazyMonoidArray()\
    \ {\n        pool.reserve(v.size() + 1);\n        root = build_from_values(v);\n\
    \    }\n\n    DynamicLazyMonoidArray(std::initializer_list<T> init) : DynamicLazyMonoidArray()\
    \ {\n        pool.reserve(init.size() + 1);\n        for (const T& x : init) push_back(x);\n\
    \    }\n\n    int size() const {\n        return node_count(root);\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void clear()\
    \ {\n        reset_to_empty();\n    }\n\n    void insert(int pos, T value) {\n\
    \        assert(0 <= pos && pos <= size());\n        root = insert_node(root,\
    \ pos, new_node(std::move(value)));\n    }\n\n    void insert(int pos, const std::vector<T>&\
    \ v) {\n        assert(0 <= pos && pos <= size());\n        pool.reserve(pool.size()\
    \ + v.size());\n        int mid = build_from_vector(v);\n        int l, r;\n \
    \       split(root, pos, l, r);\n        root = merge(merge(l, mid), r);\n   \
    \ }\n\n    void insert(int pos, std::vector<T>&& v) {\n        assert(0 <= pos\
    \ && pos <= size());\n        pool.reserve(pool.size() + v.size());\n        int\
    \ mid = build_from_vector(std::move(v));\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::initializer_list<T> init) {\n        insert(pos, std::vector<T>(init));\n\
    \    }\n\n    void insert(int pos, const DynamicLazyMonoidArray& other) {\n  \
    \      assert(0 <= pos && pos <= size());\n        if (other.empty()) return;\n\
    \        pool.reserve(pool.size() + other.size());\n        int mid = clone_subtree_from(other,\
    \ other.root);\n        int l, r;\n        split(root, pos, l, r);\n        root\
    \ = merge(merge(l, mid), r);\n    }\n\n    void push_back(T value) {\n       \
    \ insert(size(), std::move(value));\n    }\n\n    void push_front(T value) {\n\
    \        insert(0, std::move(value));\n    }\n\n    void append(const std::vector<T>&\
    \ v) {\n        insert(size(), v);\n    }\n\n    void append(std::vector<T>&&\
    \ v) {\n        insert(size(), std::move(v));\n    }\n\n    void append(const\
    \ DynamicLazyMonoidArray& other) {\n        insert(size(), other);\n    }\n\n\
    \    void erase(int pos) {\n        assert(0 <= pos && pos < size());\n      \
    \  root = erase_node(root, pos);\n    }\n\n    void erase(int l, int r) {\n  \
    \      assert(0 <= l && l <= r && r <= size());\n        if (l == r) return;\n\
    \        int a, b, c;\n        split_three(root, l, r, a, b, c);\n        root\
    \ = merge(a, c);\n    }\n\n    void pop_back() {\n        assert(!empty());\n\
    \        erase(size() - 1);\n    }\n\n    void pop_front() {\n        assert(!empty());\n\
    \        erase(0);\n    }\n\n    T get(int pos) {\n        assert(0 <= pos &&\
    \ pos < size());\n        int t = find_node(root, pos);\n        return pool[t].val;\n\
    \    }\n\n    T operator[](int pos) {\n        return get(pos);\n    }\n\n   \
    \ T front() {\n        assert(!empty());\n        return get(0);\n    }\n\n  \
    \  T back() {\n        assert(!empty());\n        return get(size() - 1);\n  \
    \  }\n\n    void set(int pos, T value) {\n        assert(0 <= pos && pos < size());\n\
    \        set_node(root, pos, std::move(value));\n    }\n\n    void reverse(int\
    \ l, int r) {\n        assert(0 <= l && l <= r && r <= size());\n        if (l\
    \ == r) return;\n        int a, b, c;\n        split_three(root, l, r, a, b, c);\n\
    \        apply_reverse(b);\n        root = merge_three(a, b, c);\n    }\n\n  \
    \  void reverse() {\n        apply_reverse(root);\n    }\n\n    void rotate(int\
    \ l, int m, int r) {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n\
    \        if (l == m || m == r) return;\n        int a, b, c, d;\n        split(root,\
    \ l, a, b);\n        split(b, m - l, b, c);\n        split(c, r - m, c, d);\n\
    \        root = merge(merge(a, c), merge(b, d));\n    }\n\n    void apply(int\
    \ pos, const F& f) {\n        assert(0 <= pos && pos < size());\n        apply_node(root,\
    \ pos, f);\n    }\n\n    void apply(int l, int r, const F& f) {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return;\n        apply_range(root,\
    \ l, r, f);\n    }\n\n    T prod(int l, int r) {\n        assert(0 <= l && l <=\
    \ r && r <= size());\n        if (l == r) return ActedMonoid::id();\n        return\
    \ prod_range(root, l, r);\n    }\n\n    T all_prod() const {\n        return pool[root].prod;\n\
    \    }\n\n    std::vector<T> to_vector() {\n        std::vector<T> res;\n    \
    \    res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n\
    \    }\n\n    std::vector<T> to_vector(int l, int r) {\n        assert(0 <= l\
    \ && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n\n    DynamicLazyMonoidArray split_off(int pos) {\n        assert(0 <= pos\
    \ && pos <= size());\n        int l, r;\n        split(root, pos, l, r);\n   \
    \     root = l;\n\n        DynamicLazyMonoidArray res;\n        res.pool.reserve(node_count(r)\
    \ + 1);\n        res.root = res.clone_subtree_from(*this, r);\n        return\
    \ res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DYNAMIC_LAZY_MONOID_ARRAY_HPP\n#define M1UNE_DYNAMIC_LAZY_MONOID_ARRAY_HPP\
    \ 1\n\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n\
    #include <initializer_list>\n#include <type_traits>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"../../acted_monoid/concept.hpp\"\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid>\n\
    struct DynamicLazyMonoidArray {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    static\
    \ constexpr bool value_commutative = [] {\n        if constexpr (requires { ActedMonoid::commutative;\
    \ }) {\n            return bool(ActedMonoid::commutative);\n        } else {\n\
    \            return false;\n        }\n    }();\n\n    struct EmptyReverseProduct\
    \ {};\n    using ReverseProduct = std::conditional_t<value_commutative, EmptyReverseProduct,\
    \ T>;\n\n    static constexpr bool count_stored_in_value = requires(const T& value)\
    \ {\n        { ActedMonoid::size(value) } -> std::convertible_to<int>;\n    };\n\
    \n    struct EmptyCount {};\n    using Count = std::conditional_t<count_stored_in_value,\
    \ EmptyCount, int>;\n\n    static ReverseProduct make_reverse_product(const T&\
    \ value) {\n        if constexpr (value_commutative) {\n            return {};\n\
    \        } else {\n            return value;\n        }\n    }\n\n    static Count\
    \ make_count(int count) {\n        if constexpr (count_stored_in_value) {\n  \
    \          return {};\n        } else {\n            return count;\n        }\n\
    \    }\n\n    struct Node {\n        T val;\n        T prod;\n        [[no_unique_address]]\
    \ ReverseProduct rprod;\n        F lazy;\n        std::uint32_t priority : 30;\n\
    \        std::uint32_t rev : 1;\n        std::uint32_t has_lazy : 1;\n       \
    \ [[no_unique_address]] Count count;\n        int l, r;\n\n        Node()\n  \
    \          : val(ActedMonoid::id()),\n              prod(ActedMonoid::id()),\n\
    \              rprod(make_reverse_product(prod)),\n              lazy(ActedMonoid::op_id()),\n\
    \              priority(0),\n              rev(false),\n              has_lazy(false),\n\
    \              count(make_count(0)),\n              l(0),\n              r(0)\
    \ {}\n\n        Node(T value, int node_priority)\n            : val(std::move(value)),\n\
    \              prod(val),\n              rprod(make_reverse_product(val)),\n \
    \             lazy(ActedMonoid::op_id()),\n              priority(std::uint32_t(node_priority)),\n\
    \              rev(false),\n              has_lazy(false),\n              count(make_count(1)),\n\
    \              l(0),\n              r(0) {}\n    };\n\n    std::vector<Node> pool;\n\
    \    int root;\n    int free_head;\n    std::uint32_t rng_state;\n\n    int node_count(int\
    \ t) const {\n        if constexpr (count_stored_in_value) {\n            return\
    \ int(ActedMonoid::size(pool[t].prod));\n        } else {\n            return\
    \ pool[t].count;\n        }\n    }\n\n    void set_node_count(int t, int count)\
    \ {\n        if constexpr (!count_stored_in_value) {\n            pool[t].count\
    \ = count;\n        }\n    }\n\n    template <typename U>\n    static T make_value(const\
    \ U& value) {\n        if constexpr (requires(U x) { ActedMonoid::make(x); })\
    \ {\n            return ActedMonoid::make(value);\n        } else {\n        \
    \    return static_cast<T>(value);\n        }\n    }\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ord) {\n        if constexpr (requires(F g,\
    \ T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n            return\
    \ ActedMonoid::mapping(f, value, ord);\n        } else {\n            return ActedMonoid::mapping(f,\
    \ value);\n        }\n    }\n\n    static F shift_operator(const F& f, long long\
    \ ord) {\n        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g,\
    \ i); }) {\n            return ActedMonoid::op_shift(f, ord);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    static F reverse_operator(const\
    \ F& f, long long size) {\n        if constexpr (requires(F g, long long n) {\
    \ ActedMonoid::op_reverse(g, n); }) {\n            return ActedMonoid::op_reverse(f,\
    \ size);\n        } else {\n            return f;\n        }\n    }\n\n    int\
    \ new_node(T value) {\n        int priority = next_priority();\n        if (free_head)\
    \ {\n            int res = free_head;\n            free_head = pool[res].l;\n\
    \            pool[res] = Node(std::move(value), priority);\n            return\
    \ res;\n        }\n        pool.push_back(Node(std::move(value), priority));\n\
    \        return int(pool.size()) - 1;\n    }\n\n    void release_node(int t) {\n\
    \        pool[t].l = free_head;\n        free_head = t;\n    }\n\n    int next_priority()\
    \ {\n        rng_state ^= rng_state << 13;\n        rng_state ^= rng_state >>\
    \ 17;\n        rng_state ^= rng_state << 5;\n        return int(rng_state);\n\
    \    }\n\n    void update(int t) {\n        if (!t) return;\n        int l = pool[t].l;\n\
    \        int r = pool[t].r;\n        set_node_count(t, 1 + node_count(l) + node_count(r));\n\
    \        pool[t].prod = ActedMonoid::op(ActedMonoid::op(pool[l].prod, pool[t].val),\
    \ pool[r].prod);\n        if constexpr (!value_commutative) {\n            pool[t].rprod\
    \ = ActedMonoid::op(ActedMonoid::op(pool[r].rprod, pool[t].val), pool[l].rprod);\n\
    \        }\n    }\n\n    void all_apply(int t, const F& f) {\n        if (!t)\
    \ return;\n        int left_count = node_count(pool[t].l);\n        pool[t].val\
    \ = mapping_at(f, pool[t].val, left_count);\n        pool[t].prod = mapping_at(f,\
    \ pool[t].prod, 0);\n        if constexpr (!value_commutative) {\n           \
    \ pool[t].rprod = mapping_at(reverse_operator(f, node_count(t)), pool[t].rprod,\
    \ 0);\n        }\n        pool[t].lazy = ActedMonoid::op_comp(f, pool[t].lazy);\n\
    \        pool[t].has_lazy = true;\n    }\n\n    void apply_reverse(int t) {\n\
    \        if (!t) return;\n        std::swap(pool[t].l, pool[t].r);\n        pool[t].rev\
    \ = !pool[t].rev;\n        if constexpr (!value_commutative) {\n            std::swap(pool[t].prod,\
    \ pool[t].rprod);\n        }\n        if (pool[t].has_lazy) {\n            pool[t].lazy\
    \ = reverse_operator(pool[t].lazy, node_count(t));\n        }\n    }\n\n    void\
    \ push(int t) {\n        if (!t) return;\n        if (pool[t].rev) {\n       \
    \     apply_reverse(pool[t].l);\n            apply_reverse(pool[t].r);\n     \
    \       pool[t].rev = false;\n        }\n        if (pool[t].has_lazy) {\n   \
    \         all_apply(pool[t].l, pool[t].lazy);\n            all_apply(pool[t].r,\
    \ shift_operator(pool[t].lazy, node_count(pool[t].l) + 1));\n            pool[t].lazy\
    \ = ActedMonoid::op_id();\n            pool[t].has_lazy = false;\n        }\n\
    \    }\n\n    void split(int t, int pos, int& l, int& r) {\n        if (!t) {\n\
    \            l = r = 0;\n            return;\n        }\n        if (pos == 0)\
    \ {\n            l = 0;\n            r = t;\n            return;\n        }\n\
    \        if (pos == node_count(t)) {\n            l = t;\n            r = 0;\n\
    \            return;\n        }\n        push(t);\n        int left_count = node_count(pool[t].l);\n\
    \        if (pos == left_count) {\n            l = pool[t].l;\n            pool[t].l\
    \ = 0;\n            update(t);\n            r = t;\n            return;\n    \
    \    }\n        if (pos == left_count + 1) {\n            r = pool[t].r;\n   \
    \         pool[t].r = 0;\n            update(t);\n            l = t;\n       \
    \     return;\n        }\n        if (pos <= left_count) {\n            split(pool[t].l,\
    \ pos, l, pool[t].l);\n            r = t;\n        } else {\n            split(pool[t].r,\
    \ pos - left_count - 1, pool[t].r, r);\n            l = t;\n        }\n      \
    \  update(t);\n    }\n\n    int merge(int l, int r) {\n        if (!l || !r) return\
    \ l ? l : r;\n        if (pool[l].priority > pool[r].priority) {\n           \
    \ push(l);\n            if (pool[l].r) {\n                pool[l].r = merge(pool[l].r,\
    \ r);\n            } else {\n                pool[l].r = r;\n            }\n \
    \           update(l);\n            return l;\n        } else {\n            push(r);\n\
    \            if (pool[r].l) {\n                pool[r].l = merge(l, pool[r].l);\n\
    \            } else {\n                pool[r].l = l;\n            }\n       \
    \     update(r);\n            return r;\n        }\n    }\n\n    void split_three(int\
    \ t, int ql, int qr, int& a, int& b, int& c) {\n        if (ql == qr) {\n    \
    \        split(t, ql, a, c);\n            b = 0;\n            return;\n      \
    \  }\n        if (ql == 0 && qr == node_count(t)) {\n            a = c = 0;\n\
    \            b = t;\n            return;\n        }\n        push(t);\n      \
    \  int left_count = node_count(pool[t].l);\n        if (qr <= left_count) {\n\
    \            split_three(pool[t].l, ql, qr, a, b, pool[t].l);\n            c =\
    \ t;\n            update(t);\n        } else if (left_count < ql) {\n        \
    \    split_three(pool[t].r, ql - left_count - 1, qr - left_count - 1, pool[t].r,\
    \ b, c);\n            a = t;\n            update(t);\n        } else {\n     \
    \       split(pool[t].l, ql, a, pool[t].l);\n            split(pool[t].r, qr -\
    \ left_count - 1, pool[t].r, c);\n            b = t;\n            update(t);\n\
    \        }\n    }\n\n    int merge_three(int a, int b, int c) {\n        if (!a)\
    \ return merge(b, c);\n        if (!b) return merge(a, c);\n        if (!c) return\
    \ merge(a, b);\n        std::uint32_t pa = pool[a].priority;\n        std::uint32_t\
    \ pb = pool[b].priority;\n        std::uint32_t pc = pool[c].priority;\n     \
    \   if (pb >= pa && pb >= pc) {\n            push(b);\n            pool[b].l =\
    \ merge(a, pool[b].l);\n            pool[b].r = merge(pool[b].r, c);\n       \
    \     update(b);\n            return b;\n        }\n        if (pa >= pc) {\n\
    \            push(a);\n            pool[a].r = merge_three(pool[a].r, b, c);\n\
    \            update(a);\n            return a;\n        }\n        push(c);\n\
    \        pool[c].l = merge_three(a, b, pool[c].l);\n        update(c);\n     \
    \   return c;\n    }\n\n    int insert_node(int t, int pos, int node) {\n    \
    \    if (!t) return node;\n        if (pool[node].priority > pool[t].priority)\
    \ {\n            split(t, pos, pool[node].l, pool[node].r);\n            update(node);\n\
    \            return node;\n        }\n        push(t);\n        int left_count\
    \ = node_count(pool[t].l);\n        if (pos <= left_count) {\n            pool[t].l\
    \ = insert_node(pool[t].l, pos, node);\n        } else {\n            pool[t].r\
    \ = insert_node(pool[t].r, pos - left_count - 1, node);\n        }\n        update(t);\n\
    \        return t;\n    }\n\n    int erase_node(int t, int pos) {\n        push(t);\n\
    \        int left_count = node_count(pool[t].l);\n        if (pos < left_count)\
    \ {\n            pool[t].l = erase_node(pool[t].l, pos);\n            update(t);\n\
    \            return t;\n        }\n        if (pos == left_count) {\n        \
    \    int res = merge(pool[t].l, pool[t].r);\n            release_node(t);\n  \
    \          return res;\n        }\n        pool[t].r = erase_node(pool[t].r, pos\
    \ - left_count - 1);\n        update(t);\n        return t;\n    }\n\n    void\
    \ set_node(int t, int pos, T value) {\n        push(t);\n        int left_count\
    \ = node_count(pool[t].l);\n        if (pos < left_count) {\n            set_node(pool[t].l,\
    \ pos, std::move(value));\n        } else if (pos == left_count) {\n         \
    \   pool[t].val = std::move(value);\n        } else {\n            set_node(pool[t].r,\
    \ pos - left_count - 1, std::move(value));\n        }\n        update(t);\n  \
    \  }\n\n    void apply_node(int t, int pos, const F& f) {\n        push(t);\n\
    \        int left_count = node_count(pool[t].l);\n        if (pos < left_count)\
    \ {\n            apply_node(pool[t].l, pos, f);\n        } else if (pos == left_count)\
    \ {\n            pool[t].val = mapping_at(f, pool[t].val, 0);\n        } else\
    \ {\n            apply_node(pool[t].r, pos - left_count - 1, f);\n        }\n\
    \        update(t);\n    }\n\n    void apply_range(int t, int ql, int qr, const\
    \ F& f) {\n        if (ql == 0 && qr == node_count(t)) {\n            all_apply(t,\
    \ f);\n            return;\n        }\n        push(t);\n        int left_count\
    \ = node_count(pool[t].l);\n        if (qr <= left_count) {\n            apply_range(pool[t].l,\
    \ ql, qr, f);\n        } else if (left_count < ql) {\n            apply_range(pool[t].r,\
    \ ql - left_count - 1, qr - left_count - 1, f);\n        } else {\n          \
    \  if (ql < left_count) {\n                apply_range(pool[t].l, ql, left_count,\
    \ f);\n            }\n            pool[t].val = mapping_at(f, pool[t].val, left_count\
    \ - ql);\n            if (left_count + 1 < qr) {\n                apply_range(pool[t].r,\
    \ 0, qr - left_count - 1,\n                            shift_operator(f, left_count\
    \ + 1 - ql));\n            }\n        }\n        update(t);\n    }\n\n    T prod_range(int\
    \ t, int ql, int qr) {\n        if (ql == 0 && qr == node_count(t)) return pool[t].prod;\n\
    \        push(t);\n        int left_count = node_count(pool[t].l);\n        if\
    \ (qr <= left_count) {\n            return prod_range(pool[t].l, ql, qr);\n  \
    \      }\n        if (left_count < ql) {\n            return prod_range(pool[t].r,\
    \ ql - left_count - 1, qr - left_count - 1);\n        }\n        T res = pool[t].val;\n\
    \        if (ql < left_count) {\n            res = ActedMonoid::op(prod_range(pool[t].l,\
    \ ql, left_count), res);\n        }\n        if (left_count + 1 < qr) {\n    \
    \        res = ActedMonoid::op(res, prod_range(pool[t].r, 0, qr - left_count -\
    \ 1));\n        }\n        return res;\n    }\n\n    int find_node(int t, int\
    \ pos) {\n        while (t) {\n            push(t);\n            int left_count\
    \ = node_count(pool[t].l);\n            if (pos < left_count) {\n            \
    \    t = pool[t].l;\n            } else if (pos == left_count) {\n           \
    \     return t;\n            } else {\n                pos -= left_count + 1;\n\
    \                t = pool[t].r;\n            }\n        }\n        return 0;\n\
    \    }\n\n    void dump_dfs(int t, std::vector<T>& res) {\n        if (!t) return;\n\
    \        push(t);\n        dump_dfs(pool[t].l, res);\n        res.push_back(pool[t].val);\n\
    \        dump_dfs(pool[t].r, res);\n        update(t);\n    }\n\n    void dump_range_dfs(int\
    \ t, int ql, int qr, int offset, std::vector<T>& res) {\n        if (!t || qr\
    \ <= offset || offset + node_count(t) <= ql) return;\n        push(t);\n     \
    \   int left_count = node_count(pool[t].l);\n        int node_pos = offset + left_count;\n\
    \        dump_range_dfs(pool[t].l, ql, qr, offset, res);\n        if (ql <= node_pos\
    \ && node_pos < qr) {\n            res.push_back(pool[t].val);\n        }\n  \
    \      dump_range_dfs(pool[t].r, ql, qr, node_pos + 1, res);\n        update(t);\n\
    \    }\n\n    int clone_subtree_from(const DynamicLazyMonoidArray& other, int\
    \ t) {\n        if (!t) return 0;\n        int res = int(pool.size());\n     \
    \   pool.push_back(other.pool[t]);\n        pool[res].l = clone_subtree_from(other,\
    \ other.pool[t].l);\n        pool[res].r = clone_subtree_from(other, other.pool[t].r);\n\
    \        return res;\n    }\n\n    void update_dfs(int t) {\n        if (!t) return;\n\
    \        update_dfs(pool[t].l);\n        update_dfs(pool[t].r);\n        update(t);\n\
    \    }\n\n    int build_cartesian(int first, int last) {\n        if (first ==\
    \ last) return 0;\n        std::vector<int> stack;\n        stack.reserve(last\
    \ - first);\n        for (int i = first; i < last; i++) {\n            int left_child\
    \ = 0;\n            while (!stack.empty() && pool[stack.back()].priority < pool[i].priority)\
    \ {\n                left_child = stack.back();\n                stack.pop_back();\n\
    \            }\n            pool[i].l = left_child;\n            if (!stack.empty())\
    \ {\n                pool[stack.back()].r = i;\n            }\n            stack.push_back(i);\n\
    \        }\n        int res = stack.front();\n        update_dfs(res);\n     \
    \   return res;\n    }\n\n    int build_from_vector(const std::vector<T>& v) {\n\
    \        int first = int(pool.size());\n        pool.reserve(pool.size() + v.size());\n\
    \        for (const T& x : v) {\n            new_node(x);\n        }\n       \
    \ return build_cartesian(first, int(pool.size()));\n    }\n\n    int build_from_vector(std::vector<T>&&\
    \ v) {\n        int first = int(pool.size());\n        pool.reserve(pool.size()\
    \ + v.size());\n        for (T& x : v) {\n            new_node(std::move(x));\n\
    \        }\n        return build_cartesian(first, int(pool.size()));\n    }\n\n\
    \    template <typename U>\n    int build_from_values(const std::vector<U>& v)\
    \ {\n        int first = int(pool.size());\n        pool.reserve(pool.size() +\
    \ v.size());\n        for (const U& x : v) {\n            new_node(make_value(x));\n\
    \        }\n        return build_cartesian(first, int(pool.size()));\n    }\n\n\
    \    void reset_to_empty() {\n        pool.clear();\n        pool.push_back(Node());\n\
    \        root = 0;\n        free_head = 0;\n    }\n\n   public:\n    DynamicLazyMonoidArray()\n\
    \        : root(0),\n          free_head(0),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        pool.push_back(Node());\n        if (rng_state == 0) rng_state =\
    \ 1;\n    }\n\n    DynamicLazyMonoidArray(const DynamicLazyMonoidArray& other)\n\
    \        : pool(other.pool), root(other.root), free_head(other.free_head), rng_state(other.rng_state)\
    \ {}\n\n    DynamicLazyMonoidArray(DynamicLazyMonoidArray&& other) noexcept\n\
    \        : pool(std::move(other.pool)), root(other.root), free_head(other.free_head),\
    \ rng_state(other.rng_state) {\n        other.reset_to_empty();\n    }\n\n   \
    \ DynamicLazyMonoidArray& operator=(const DynamicLazyMonoidArray& other) {\n \
    \       if (this != &other) {\n            pool = other.pool;\n            root\
    \ = other.root;\n            free_head = other.free_head;\n            rng_state\
    \ = other.rng_state;\n        }\n        return *this;\n    }\n\n    DynamicLazyMonoidArray&\
    \ operator=(DynamicLazyMonoidArray&& other) noexcept {\n        if (this != &other)\
    \ {\n            pool = std::move(other.pool);\n            root = other.root;\n\
    \            free_head = other.free_head;\n            rng_state = other.rng_state;\n\
    \            other.reset_to_empty();\n        }\n        return *this;\n    }\n\
    \n    explicit DynamicLazyMonoidArray(int n) : DynamicLazyMonoidArray(n, ActedMonoid::id())\
    \ {}\n\n    DynamicLazyMonoidArray(int n, const T& value) : DynamicLazyMonoidArray()\
    \ {\n        assert(0 <= n);\n        pool.reserve(n + 1);\n        int first\
    \ = int(pool.size());\n        for (int i = 0; i < n; i++) {\n            new_node(value);\n\
    \        }\n        root = build_cartesian(first, int(pool.size()));\n    }\n\n\
    \    explicit DynamicLazyMonoidArray(const std::vector<T>& v) : DynamicLazyMonoidArray()\
    \ {\n        pool.reserve(v.size() + 1);\n        root = build_from_vector(v);\n\
    \    }\n\n    explicit DynamicLazyMonoidArray(std::vector<T>&& v) : DynamicLazyMonoidArray()\
    \ {\n        pool.reserve(v.size() + 1);\n        root = build_from_vector(std::move(v));\n\
    \    }\n\n    template <typename U>\n        requires(!std::same_as<U, T>) &&\
    \ (requires(U x) { ActedMonoid::make(x); } || std::convertible_to<U, T>)\n   \
    \ explicit DynamicLazyMonoidArray(const std::vector<U>& v) : DynamicLazyMonoidArray()\
    \ {\n        pool.reserve(v.size() + 1);\n        root = build_from_values(v);\n\
    \    }\n\n    DynamicLazyMonoidArray(std::initializer_list<T> init) : DynamicLazyMonoidArray()\
    \ {\n        pool.reserve(init.size() + 1);\n        for (const T& x : init) push_back(x);\n\
    \    }\n\n    int size() const {\n        return node_count(root);\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void clear()\
    \ {\n        reset_to_empty();\n    }\n\n    void insert(int pos, T value) {\n\
    \        assert(0 <= pos && pos <= size());\n        root = insert_node(root,\
    \ pos, new_node(std::move(value)));\n    }\n\n    void insert(int pos, const std::vector<T>&\
    \ v) {\n        assert(0 <= pos && pos <= size());\n        pool.reserve(pool.size()\
    \ + v.size());\n        int mid = build_from_vector(v);\n        int l, r;\n \
    \       split(root, pos, l, r);\n        root = merge(merge(l, mid), r);\n   \
    \ }\n\n    void insert(int pos, std::vector<T>&& v) {\n        assert(0 <= pos\
    \ && pos <= size());\n        pool.reserve(pool.size() + v.size());\n        int\
    \ mid = build_from_vector(std::move(v));\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::initializer_list<T> init) {\n        insert(pos, std::vector<T>(init));\n\
    \    }\n\n    void insert(int pos, const DynamicLazyMonoidArray& other) {\n  \
    \      assert(0 <= pos && pos <= size());\n        if (other.empty()) return;\n\
    \        pool.reserve(pool.size() + other.size());\n        int mid = clone_subtree_from(other,\
    \ other.root);\n        int l, r;\n        split(root, pos, l, r);\n        root\
    \ = merge(merge(l, mid), r);\n    }\n\n    void push_back(T value) {\n       \
    \ insert(size(), std::move(value));\n    }\n\n    void push_front(T value) {\n\
    \        insert(0, std::move(value));\n    }\n\n    void append(const std::vector<T>&\
    \ v) {\n        insert(size(), v);\n    }\n\n    void append(std::vector<T>&&\
    \ v) {\n        insert(size(), std::move(v));\n    }\n\n    void append(const\
    \ DynamicLazyMonoidArray& other) {\n        insert(size(), other);\n    }\n\n\
    \    void erase(int pos) {\n        assert(0 <= pos && pos < size());\n      \
    \  root = erase_node(root, pos);\n    }\n\n    void erase(int l, int r) {\n  \
    \      assert(0 <= l && l <= r && r <= size());\n        if (l == r) return;\n\
    \        int a, b, c;\n        split_three(root, l, r, a, b, c);\n        root\
    \ = merge(a, c);\n    }\n\n    void pop_back() {\n        assert(!empty());\n\
    \        erase(size() - 1);\n    }\n\n    void pop_front() {\n        assert(!empty());\n\
    \        erase(0);\n    }\n\n    T get(int pos) {\n        assert(0 <= pos &&\
    \ pos < size());\n        int t = find_node(root, pos);\n        return pool[t].val;\n\
    \    }\n\n    T operator[](int pos) {\n        return get(pos);\n    }\n\n   \
    \ T front() {\n        assert(!empty());\n        return get(0);\n    }\n\n  \
    \  T back() {\n        assert(!empty());\n        return get(size() - 1);\n  \
    \  }\n\n    void set(int pos, T value) {\n        assert(0 <= pos && pos < size());\n\
    \        set_node(root, pos, std::move(value));\n    }\n\n    void reverse(int\
    \ l, int r) {\n        assert(0 <= l && l <= r && r <= size());\n        if (l\
    \ == r) return;\n        int a, b, c;\n        split_three(root, l, r, a, b, c);\n\
    \        apply_reverse(b);\n        root = merge_three(a, b, c);\n    }\n\n  \
    \  void reverse() {\n        apply_reverse(root);\n    }\n\n    void rotate(int\
    \ l, int m, int r) {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n\
    \        if (l == m || m == r) return;\n        int a, b, c, d;\n        split(root,\
    \ l, a, b);\n        split(b, m - l, b, c);\n        split(c, r - m, c, d);\n\
    \        root = merge(merge(a, c), merge(b, d));\n    }\n\n    void apply(int\
    \ pos, const F& f) {\n        assert(0 <= pos && pos < size());\n        apply_node(root,\
    \ pos, f);\n    }\n\n    void apply(int l, int r, const F& f) {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return;\n        apply_range(root,\
    \ l, r, f);\n    }\n\n    T prod(int l, int r) {\n        assert(0 <= l && l <=\
    \ r && r <= size());\n        if (l == r) return ActedMonoid::id();\n        return\
    \ prod_range(root, l, r);\n    }\n\n    T all_prod() const {\n        return pool[root].prod;\n\
    \    }\n\n    std::vector<T> to_vector() {\n        std::vector<T> res;\n    \
    \    res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n\
    \    }\n\n    std::vector<T> to_vector(int l, int r) {\n        assert(0 <= l\
    \ && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n\n    DynamicLazyMonoidArray split_off(int pos) {\n        assert(0 <= pos\
    \ && pos <= size());\n        int l, r;\n        split(root, pos, l, r);\n   \
    \     root = l;\n\n        DynamicLazyMonoidArray res;\n        res.pool.reserve(node_count(r)\
    \ + 1);\n        res.root = res.clone_subtree_from(*this, r);\n        return\
    \ res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DYNAMIC_LAZY_MONOID_ARRAY_HPP\n"
  dependsOn:
  - acted_monoid/concept.hpp
  isVerificationFile: false
  path: ds/dynamic_array/dynamic_lazy_monoid_array.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dynamic_array/dynamic_lazy_monoid_array.test.cpp
  - verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp
documentation_of: ds/dynamic_array/dynamic_lazy_monoid_array.hpp
layout: document
title: Dynamic Lazy Monoid Array
---

## Overview

`DynamicLazyMonoidArray` is an implicit treap for dynamic sequences with range products and lazy range actions. It supports indexed insertion, deletion, reversal, rotation, splitting, concatenation, range updates, and range product queries.

By default, each node stores both forward and reversed products, so `reverse(l, r)` works correctly for non-commutative value monoids when the acted monoid action is compatible with the value operation. If `ActedMonoid::commutative` is a static constant equal to `true`, the redundant reversed product is omitted.

## Complexity Notation

In this document:

* `N` is the current number of elements in the sequence.
* `M` is the number of elements inserted or appended from another container.
* `K` is the number of elements returned or moved into a newly returned sequence.

## Template Parameters

* `ActedMonoid`: An acted monoid satisfying `m1une::acted_monoid::IsActedMonoid`. The optional static constant `commutative = true` lets the array omit the reversed product. The optional `static int size(const T&)` lets it use size metadata already stored in `T` instead of storing a duplicate node count.

## Constructors

* `DynamicLazyMonoidArray()`
  Constructs an empty sequence. ($O(1)$)

* `DynamicLazyMonoidArray(int n)`
  Constructs a sequence with `n` copies of `ActedMonoid::id()`. ($O(N)$)

* `DynamicLazyMonoidArray(int n, const T& value)`
  Constructs a sequence with `n` copies of `value`. ($O(N)$)

* `DynamicLazyMonoidArray(const std::vector<T>& v)`
  Constructs the sequence from acted-monoid values. ($O(N)$)

* `DynamicLazyMonoidArray(std::vector<T>&& v)`
  Constructs the sequence by moving acted-monoid values. ($O(N)$)

* `DynamicLazyMonoidArray(const std::vector<U>& v)`
  Constructs the sequence from another type using `ActedMonoid::make(x)` if available, otherwise `static_cast<T>(x)`. ($O(N)$)

* `DynamicLazyMonoidArray(std::initializer_list<T> init)`
  Constructs the sequence from an initializer list of acted-monoid values. ($O(N \log N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `void clear()` | Removes all elements. | $O(1)$ |
| `void insert(int pos, T value)` | Inserts `value` before index `pos`. | $O(\log N)$ |
| `void insert(int pos, const std::vector<T>& v)` | Inserts every value in `v` before index `pos`. | $O(M + \log N)$ |
| `void insert(int pos, const DynamicLazyMonoidArray& other)` | Inserts a copy of `other` before index `pos`. | $O(M + \log N)$ |
| `void push_back(T value)`, `void push_front(T value)` | Inserts one value at the end or beginning. | $O(\log N)$ |
| `void append(const std::vector<T>& v)` | Appends all values in `v`. | $O(M + \log N)$ |
| `void append(const DynamicLazyMonoidArray& other)` | Appends a copy of `other`. | $O(M + \log N)$ |
| `void erase(int pos)` | Removes the value at index `pos`. | $O(\log N)$ |
| `void erase(int l, int r)` | Removes the half-open range `[l, r)`. | $O(\log N)$ |
| `void pop_back()`, `void pop_front()` | Removes one value from the end or beginning. | $O(\log N)$ |
| `T get(int pos)` | Pushes lazy tags on the path and returns the value at `pos`. | $O(\log N)$ |
| `void set(int pos, T value)` | Replaces index `pos` and rebuilds affected products. | $O(\log N)$ |
| `void reverse(int l, int r)` | Reverses the half-open range `[l, r)`. | $O(\log N)$ |
| `void reverse()` | Reverses the entire sequence. | $O(1)$ |
| `void rotate(int l, int m, int r)` | Moves `[m, r)` before `[l, m)`, like `std::rotate`. | $O(\log N)$ |
| `void apply(int pos, const F& f)` | Applies lazy operator `f` to the value at index `pos`. | $O(\log N)$ |
| `void apply(int l, int r, const F& f)` | Applies lazy operator `f` to every value in `[l, r)`. | $O(\log N)$ |
| `T prod(int l, int r)` | Returns the acted-monoid product over `[l, r)`. | $O(\log N)$ |
| `T all_prod() const` | Returns the acted-monoid product over the whole sequence. | $O(1)$ |
| `std::vector<T> to_vector()` | Pushes lazy tags and dumps the sequence to `std::vector`. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Dumps `[l, r)` to `std::vector`, where `K = r - l`. | $O(K + \log N)$ |
| `DynamicLazyMonoidArray split_off(int pos)` | Removes `[pos, N)` and returns it as a new sequence with its own pool, where `K = N - pos`. | $O(K + \log N)$ |

## Notes

`get`, `prod`, and `to_vector` are non-const because they may push pending lazy tags while walking the treap.

For size-aware acted monoids such as `RangeAddRangeSum`, `ActedMonoid::id()` often has size `0`. In that case, prefer constructing from raw values or from explicit leaf values:

```cpp
using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
using Array = m1une::ds::DynamicLazyMonoidArray<AM>;

Array a(std::vector<long long>(n, 0)); // uses AM::make(x)
Array b(n, AM::make(0));               // explicit leaf value
```

Order-aware acted monoids should store relative order information such as `size`, `ord`, or `ord_sum`, not immutable global indices. Arithmetic-progression acted monoids use range-local order; to apply a global formula on `[l, r)`, shift the constant term by `a * l`.

## Example

```cpp
#include "ds/dynamic_array/dynamic_lazy_monoid_array.hpp"
#include "acted_monoid/range_add_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
using Array = m1une::ds::DynamicLazyMonoidArray<AM>;

int main() {
    Array a(std::vector<long long>{1, 2, 3, 4, 5});

    a.apply(1, 4, 10);                 // {1, 12, 13, 14, 5}
    std::cout << a.prod(0, 5).sum << "\n";

    a.reverse(1, 5);                   // {1, 5, 14, 13, 12}
    a.set(2, AM::make(100));           // {1, 5, 100, 13, 12}

    std::cout << a.prod(1, 4).sum << "\n";

    return 0;
}
```
