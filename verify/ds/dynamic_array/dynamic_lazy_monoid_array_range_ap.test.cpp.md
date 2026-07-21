---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_ap_add_range_sum.hpp
    title: Range AP Add Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/dynamic_lazy_monoid_array.hpp
    title: Dynamic Lazy Monoid Array
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
  bundledCode: "#line 1 \"verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/dynamic_array/dynamic_lazy_monoid_array.hpp\"\
    \n\n\n\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n\
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
    \ res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"\
    verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp\"\n\n#include\
    \ <algorithm>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n\
    #include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include\
    \ <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n#line\
    \ 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\nnamespace\
    \ utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
    template <class T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate\
    \ <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 8 \"verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp\"\
    \n#include <numeric>\n#include <random>\n#line 12 \"verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp\"\
    \n\n#line 1 \"acted_monoid/range_ap_add_range_sum.hpp\"\n\n\n\n#line 5 \"acted_monoid/range_ap_add_range_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct\
    \ RangeApAddRangeSumNode {\n    T sum;\n    long long size;\n    T ord_sum;\n\
    };\n\ntemplate <typename T>\nstruct RangeApAddRangeSum {\n    using value_type\
    \ = RangeApAddRangeSumNode<T>;\n    using operator_type = std::pair<T, T>;  //\
    \ {a, b} for adding a * i + b\n    static constexpr bool commutative = false;\n\
    \    static constexpr bool operator_commutative = true;\n\n    // Value Monoid\
    \ (Sum)\n    static constexpr value_type id() {\n        return {T(0), 0, T(0)};\n\
    \    }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {a.sum + b.sum, a.size + b.size, a.ord_sum + b.ord_sum\
    \ + T(a.size) * T(b.size)};\n    }\n\n    // Operator Monoid (Add)\n    static\
    \ constexpr operator_type op_id() {\n        return {T(0), T(0)};\n    }\n   \
    \ static constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return {f.first + g.first, f.second + g.second};\n    }\n\n  \
    \  static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        return mapping(f, x, 0);\n    }\n\n    static constexpr value_type\
    \ mapping(const operator_type& f, const value_type& x, long long ord) {\n    \
    \    return {x.sum + f.first * (x.ord_sum + T(ord) * T(x.size)) + f.second * T(x.size),\
    \ x.size, x.ord_sum};\n    }\n\n    static constexpr operator_type op_shift(const\
    \ operator_type& f, long long ord) {\n        return {f.first, f.second + f.first\
    \ * T(ord)};\n    }\n\n    static constexpr operator_type op_reverse(const operator_type&\
    \ f, long long size) {\n        return {-f.first, f.second + f.first * T(size\
    \ - 1)};\n    }\n\n    static constexpr value_type make(const T& val) {\n    \
    \    return {val, 1, T(0)};\n    }\n};\n\n}  // namespace acted_monoid\n}  //\
    \ namespace m1une\n\n\n#line 14 \"verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp\"\
    \n\nusing AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;\nusing Node\
    \ = AM::value_type;\nusing Array = m1une::ds::DynamicLazyMonoidArray<AM>;\n\n\
    std::vector<long long> sums(std::vector<Node> a) {\n    std::vector<long long>\
    \ res;\n    res.reserve(a.size());\n    for (Node x : a) res.push_back(x.sum);\n\
    \    return res;\n}\n\nlong long sum_range(const std::vector<long long>& a, int\
    \ l, int r) {\n    return std::accumulate(a.begin() + l, a.begin() + r, 0LL);\n\
    }\n\nvoid assert_all_ranges(Array& a, const std::vector<long long>& expected)\
    \ {\n    assert(sums(a.to_vector()) == expected);\n    assert(a.all_prod().sum\
    \ == sum_range(expected, 0, int(expected.size())));\n    for (int l = 0; l <=\
    \ int(expected.size()); l++) {\n        for (int r = l; r <= int(expected.size());\
    \ r++) {\n            assert(a.prod(l, r).sum == sum_range(expected, l, r));\n\
    \        }\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    {\n        Array a(std::vector<long\
    \ long>{0, 0, 0, 0});\n        a.apply(1, 4, {2, 3});\n        a.insert(2, AM::make(100));\n\
    \        assert_all_ranges(a, {0, 3, 100, 5, 7});\n\n        a.apply(1, 5, {10,\
    \ 0});\n        assert_all_ranges(a, {0, 3, 110, 25, 37});\n    }\n    {\n   \
    \     Array a(std::vector<long long>{0, 0, 0, 0, 0});\n        a.apply(0, 5, {1,\
    \ 0});\n        a.insert(2, AM::make(100));\n        assert_all_ranges(a, {0,\
    \ 1, 100, 2, 3, 4});\n    }\n    {\n        Array a(std::vector<long long>{0,\
    \ 0, 0, 0});\n        a.apply(0, 4, {1, 0});\n        a.reverse();\n        a.insert(1,\
    \ AM::make(9));\n        a.apply(1, 4, {2, 1});\n        assert_all_ranges(a,\
    \ {3, 10, 5, 6, 0});\n    }\n    {\n        Array a(std::vector<long long>{1,\
    \ 2, 3});\n        a.erase(1);\n        Array copied = a;\n        a.insert(1,\
    \ AM::make(9));\n        copied.insert(1, AM::make(8));\n        assert_all_ranges(a,\
    \ {1, 9, 3});\n        assert_all_ranges(copied, {1, 8, 3});\n\n        copied.erase(1);\n\
    \        Array moved = std::move(copied);\n        moved.insert(1, AM::make(7));\n\
    \        assert(copied.empty());\n        assert_all_ranges(moved, {1, 7, 3});\n\
    \    }\n\n    std::mt19937 rng(3);\n    Array a;\n    std::vector<long long> expected;\n\
    \    for (int step = 0; step < 500; step++) {\n        int op = int(rng() % 6);\n\
    \        if (op == 0 || expected.empty()) {\n            int pos = int(rng() %\
    \ (expected.size() + 1));\n            long long value = int(rng() % 101) - 50;\n\
    \            a.insert(pos, AM::make(value));\n            expected.insert(expected.begin()\
    \ + pos, value);\n        } else if (op == 1) {\n            int pos = int(rng()\
    \ % expected.size());\n            a.erase(pos);\n            expected.erase(expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (expected.size()\
    \ + 1));\n            int r = int(rng() % (expected.size() + 1));\n          \
    \  if (l > r) std::swap(l, r);\n            long long coef = int(rng() % 11) -\
    \ 5;\n            long long add = int(rng() % 21) - 10;\n            a.apply(l,\
    \ r, {coef, add});\n            for (int i = l; i < r; i++) expected[i] += coef\
    \ * (i - l) + add;\n        } else if (op == 3) {\n            int l = int(rng()\
    \ % (expected.size() + 1));\n            int r = int(rng() % (expected.size()\
    \ + 1));\n            if (l > r) std::swap(l, r);\n            a.reverse(l, r);\n\
    \            std::reverse(expected.begin() + l, expected.begin() + r);\n     \
    \   } else if (op == 4) {\n            int l = int(rng() % (expected.size() +\
    \ 1));\n            int m = int(rng() % (expected.size() + 1));\n            int\
    \ r = int(rng() % (expected.size() + 1));\n            if (l > m) std::swap(l,\
    \ m);\n            if (m > r) std::swap(m, r);\n            if (l > m) std::swap(l,\
    \ m);\n            a.rotate(l, m, r);\n            std::rotate(expected.begin()\
    \ + l, expected.begin() + m, expected.begin() + r);\n        } else {\n      \
    \      int pos = int(rng() % expected.size());\n            long long value =\
    \ int(rng() % 101) - 50;\n            a.set(pos, AM::make(value));\n         \
    \   expected[pos] = value;\n        }\n        assert_all_ranges(a, expected);\n\
    \    }\n\n    long long x, y;\n    fast_input >> x >> y;\n    fast_output << x\
    \ + y << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/dynamic_array/dynamic_lazy_monoid_array.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include \"../../../utilities/fast_io.hpp\"\n#include <numeric>\n\
    #include <random>\n#include <utility>\n#include <vector>\n\n#include \"../../../acted_monoid/range_ap_add_range_sum.hpp\"\
    \n\nusing AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;\nusing Node\
    \ = AM::value_type;\nusing Array = m1une::ds::DynamicLazyMonoidArray<AM>;\n\n\
    std::vector<long long> sums(std::vector<Node> a) {\n    std::vector<long long>\
    \ res;\n    res.reserve(a.size());\n    for (Node x : a) res.push_back(x.sum);\n\
    \    return res;\n}\n\nlong long sum_range(const std::vector<long long>& a, int\
    \ l, int r) {\n    return std::accumulate(a.begin() + l, a.begin() + r, 0LL);\n\
    }\n\nvoid assert_all_ranges(Array& a, const std::vector<long long>& expected)\
    \ {\n    assert(sums(a.to_vector()) == expected);\n    assert(a.all_prod().sum\
    \ == sum_range(expected, 0, int(expected.size())));\n    for (int l = 0; l <=\
    \ int(expected.size()); l++) {\n        for (int r = l; r <= int(expected.size());\
    \ r++) {\n            assert(a.prod(l, r).sum == sum_range(expected, l, r));\n\
    \        }\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    {\n        Array a(std::vector<long\
    \ long>{0, 0, 0, 0});\n        a.apply(1, 4, {2, 3});\n        a.insert(2, AM::make(100));\n\
    \        assert_all_ranges(a, {0, 3, 100, 5, 7});\n\n        a.apply(1, 5, {10,\
    \ 0});\n        assert_all_ranges(a, {0, 3, 110, 25, 37});\n    }\n    {\n   \
    \     Array a(std::vector<long long>{0, 0, 0, 0, 0});\n        a.apply(0, 5, {1,\
    \ 0});\n        a.insert(2, AM::make(100));\n        assert_all_ranges(a, {0,\
    \ 1, 100, 2, 3, 4});\n    }\n    {\n        Array a(std::vector<long long>{0,\
    \ 0, 0, 0});\n        a.apply(0, 4, {1, 0});\n        a.reverse();\n        a.insert(1,\
    \ AM::make(9));\n        a.apply(1, 4, {2, 1});\n        assert_all_ranges(a,\
    \ {3, 10, 5, 6, 0});\n    }\n    {\n        Array a(std::vector<long long>{1,\
    \ 2, 3});\n        a.erase(1);\n        Array copied = a;\n        a.insert(1,\
    \ AM::make(9));\n        copied.insert(1, AM::make(8));\n        assert_all_ranges(a,\
    \ {1, 9, 3});\n        assert_all_ranges(copied, {1, 8, 3});\n\n        copied.erase(1);\n\
    \        Array moved = std::move(copied);\n        moved.insert(1, AM::make(7));\n\
    \        assert(copied.empty());\n        assert_all_ranges(moved, {1, 7, 3});\n\
    \    }\n\n    std::mt19937 rng(3);\n    Array a;\n    std::vector<long long> expected;\n\
    \    for (int step = 0; step < 500; step++) {\n        int op = int(rng() % 6);\n\
    \        if (op == 0 || expected.empty()) {\n            int pos = int(rng() %\
    \ (expected.size() + 1));\n            long long value = int(rng() % 101) - 50;\n\
    \            a.insert(pos, AM::make(value));\n            expected.insert(expected.begin()\
    \ + pos, value);\n        } else if (op == 1) {\n            int pos = int(rng()\
    \ % expected.size());\n            a.erase(pos);\n            expected.erase(expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (expected.size()\
    \ + 1));\n            int r = int(rng() % (expected.size() + 1));\n          \
    \  if (l > r) std::swap(l, r);\n            long long coef = int(rng() % 11) -\
    \ 5;\n            long long add = int(rng() % 21) - 10;\n            a.apply(l,\
    \ r, {coef, add});\n            for (int i = l; i < r; i++) expected[i] += coef\
    \ * (i - l) + add;\n        } else if (op == 3) {\n            int l = int(rng()\
    \ % (expected.size() + 1));\n            int r = int(rng() % (expected.size()\
    \ + 1));\n            if (l > r) std::swap(l, r);\n            a.reverse(l, r);\n\
    \            std::reverse(expected.begin() + l, expected.begin() + r);\n     \
    \   } else if (op == 4) {\n            int l = int(rng() % (expected.size() +\
    \ 1));\n            int m = int(rng() % (expected.size() + 1));\n            int\
    \ r = int(rng() % (expected.size() + 1));\n            if (l > m) std::swap(l,\
    \ m);\n            if (m > r) std::swap(m, r);\n            if (l > m) std::swap(l,\
    \ m);\n            a.rotate(l, m, r);\n            std::rotate(expected.begin()\
    \ + l, expected.begin() + m, expected.begin() + r);\n        } else {\n      \
    \      int pos = int(rng() % expected.size());\n            long long value =\
    \ int(rng() % 101) - 50;\n            a.set(pos, AM::make(value));\n         \
    \   expected[pos] = value;\n        }\n        assert_all_ranges(a, expected);\n\
    \    }\n\n    long long x, y;\n    fast_input >> x >> y;\n    fast_output << x\
    \ + y << '\\n';\n}\n"
  dependsOn:
  - ds/dynamic_array/dynamic_lazy_monoid_array.hpp
  - acted_monoid/concept.hpp
  - utilities/fast_io.hpp
  - acted_monoid/range_ap_add_range_sum.hpp
  isVerificationFile: true
  path: verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp
- /verify/verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp.html
title: verify/ds/dynamic_array/dynamic_lazy_monoid_array_range_ap.test.cpp
---
