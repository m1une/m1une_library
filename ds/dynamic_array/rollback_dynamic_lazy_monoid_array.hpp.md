---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_journal.hpp
    title: ds/detail/rollback_journal.hpp
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
  bundledCode: "#line 1 \"ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp\"\
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
    \n\n#line 1 \"ds/detail/rollback_journal.hpp\"\n\n\n\n#include <algorithm>\n#line\
    \ 6 \"ds/detail/rollback_journal.hpp\"\n#include <cstddef>\n#line 8 \"ds/detail/rollback_journal.hpp\"\
    \n#include <limits>\n#line 11 \"ds/detail/rollback_journal.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\nnamespace detail {\n\ntemplate <class Node>\nstruct\
    \ RollbackJournal {\n    struct Change {\n        int index;\n        Node value;\n\
    \    };\n\n    struct Checkpoint {\n        std::size_t change_size;\n       \
    \ std::size_t node_size;\n        std::uint64_t epoch;\n    };\n\n    std::vector<Node>\
    \ nodes;\n    std::vector<Change> changes;\n    std::vector<Checkpoint> checkpoints;\n\
    \    std::vector<std::uint64_t> saved_epoch;\n    std::uint64_t next_epoch = 1;\n\
    \n    std::uint64_t new_epoch() {\n        if (next_epoch == 0) {\n          \
    \  std::fill(saved_epoch.begin(), saved_epoch.end(), 0);\n            next_epoch\
    \ = 1;\n        }\n        return next_epoch++;\n    }\n\n    int size() const\
    \ { return int(nodes.size()); }\n\n    Node& operator[](int index) { return nodes[index];\
    \ }\n    const Node& operator[](int index) const { return nodes[index]; }\n\n\
    \    template <class... Args>\n    int emplace(Args&&... args) {\n        assert(nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        int index = int(nodes.size());\n\
    \        nodes.emplace_back(std::forward<Args>(args)...);\n        saved_epoch.push_back(0);\n\
    \        return index;\n    }\n\n    int snapshot() {\n        assert(checkpoints.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        checkpoints.push_back(Checkpoint{changes.size(),\
    \ nodes.size(), new_epoch()});\n        return int(checkpoints.size());\n    }\n\
    \n    void touch(int index) {\n        assert(0 <= index && index < size());\n\
    \        if (checkpoints.empty()) return;\n        const Checkpoint& checkpoint\
    \ = checkpoints.back();\n        if (std::size_t(index) >= checkpoint.node_size)\
    \ return;\n        if (saved_epoch[index] == checkpoint.epoch) return;\n     \
    \   saved_epoch[index] = checkpoint.epoch;\n        changes.push_back(Change{index,\
    \ nodes[index]});\n    }\n\n    int snapshot_count() const { return int(checkpoints.size());\
    \ }\n\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n\
    \        checkpoints.reserve(count);\n    }\n\n    void reserve_changes(std::size_t\
    \ count) { changes.reserve(count); }\n\n    void rollback(int state) {\n     \
    \   assert(1 <= state && state <= snapshot_count());\n        Checkpoint checkpoint\
    \ = checkpoints[state - 1];\n        while (changes.size() > checkpoint.change_size)\
    \ {\n            Change change = std::move(changes.back());\n            changes.pop_back();\n\
    \            nodes[change.index] = std::move(change.value);\n        }\n     \
    \   nodes.erase(nodes.begin() + checkpoint.node_size, nodes.end());\n        saved_epoch.resize(checkpoint.node_size);\n\
    \        checkpoints.resize(state);\n        checkpoints.back().change_size =\
    \ changes.size();\n        checkpoints.back().node_size = nodes.size();\n    \
    \    checkpoints.back().epoch = new_epoch();\n    }\n\n    void clear_history()\
    \ {\n        changes.clear();\n        checkpoints.clear();\n        std::fill(saved_epoch.begin(),\
    \ saved_epoch.end(), 0);\n    }\n\n    void clear() {\n        nodes.clear();\n\
    \        changes.clear();\n        checkpoints.clear();\n        saved_epoch.clear();\n\
    \        next_epoch = 1;\n    }\n};\n\n}  // namespace detail\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 15 \"ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct RollbackDynamicLazyMonoidArray {\n    using T = typename\
    \ ActedMonoid::value_type;\n    using F = typename ActedMonoid::operator_type;\n\
    \n   private:\n    static constexpr bool value_commutative = [] {\n        if\
    \ constexpr (requires { ActedMonoid::commutative; }) {\n            return bool(ActedMonoid::commutative);\n\
    \        } else {\n            return false;\n        }\n    }();\n\n    struct\
    \ EmptyReverseProduct {};\n    using ReverseProduct = std::conditional_t<value_commutative,\
    \ EmptyReverseProduct, T>;\n\n    static constexpr bool count_stored_in_value\
    \ = requires(const T& value) {\n        { ActedMonoid::size(value) } -> std::convertible_to<int>;\n\
    \    };\n\n    struct EmptyCount {};\n    using Count = std::conditional_t<count_stored_in_value,\
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
    \              l(0),\n              r(0) {}\n    };\n\n    detail::RollbackJournal<Node>\
    \ _journal;\n    struct StateCheckpoint { int root; int free_head; };\n    std::vector<StateCheckpoint>\
    \ _state_checkpoints;\n    int root;\n    int free_head;\n    std::uint32_t rng_state;\n\
    \n    int node_count(int t) const {\n        if constexpr (count_stored_in_value)\
    \ {\n            return int(ActedMonoid::size(_journal[t].prod));\n        } else\
    \ {\n            return _journal[t].count;\n        }\n    }\n\n    void set_node_count(int\
    \ t, int count) {\n        _journal.touch(t);\n        if constexpr (!count_stored_in_value)\
    \ {\n            _journal[t].count = count;\n        }\n    }\n\n    template\
    \ <typename U>\n    static T make_value(const U& value) {\n        if constexpr\
    \ (requires(U x) { ActedMonoid::make(x); }) {\n            return ActedMonoid::make(value);\n\
    \        } else {\n            return static_cast<T>(value);\n        }\n    }\n\
    \n    static T mapping_at(const F& f, const T& value, long long ord) {\n     \
    \   if constexpr (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x,\
    \ i); }) {\n            return ActedMonoid::mapping(f, value, ord);\n        }\
    \ else {\n            return ActedMonoid::mapping(f, value);\n        }\n    }\n\
    \n    static F shift_operator(const F& f, long long ord) {\n        if constexpr\
    \ (requires(F g, long long i) { ActedMonoid::op_shift(g, i); }) {\n          \
    \  return ActedMonoid::op_shift(f, ord);\n        } else {\n            return\
    \ f;\n        }\n    }\n\n    static F reverse_operator(const F& f, long long\
    \ size) {\n        if constexpr (requires(F g, long long n) { ActedMonoid::op_reverse(g,\
    \ n); }) {\n            return ActedMonoid::op_reverse(f, size);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    int new_node(T value) {\n\
    \        int priority = next_priority();\n        if (free_head) {\n         \
    \   int res = free_head;\n            _journal.touch(res);\n            free_head\
    \ = _journal[res].l;\n            _journal[res] = Node(std::move(value), priority);\n\
    \            return res;\n        }\n        _journal.emplace(std::move(value),\
    \ priority);\n        return int(_journal.nodes.size()) - 1;\n    }\n\n    void\
    \ release_node(int t) {\n        _journal.touch(t);\n        _journal[t].l = free_head;\n\
    \        free_head = t;\n    }\n\n    int next_priority() {\n        rng_state\
    \ ^= rng_state << 13;\n        rng_state ^= rng_state >> 17;\n        rng_state\
    \ ^= rng_state << 5;\n        return int(rng_state);\n    }\n\n    void update(int\
    \ t) {\n        if (!t) return;\n        _journal.touch(t);\n        int l = _journal[t].l;\n\
    \        int r = _journal[t].r;\n        set_node_count(t, 1 + node_count(l) +\
    \ node_count(r));\n        _journal[t].prod = ActedMonoid::op(ActedMonoid::op(_journal[l].prod,\
    \ _journal[t].val), _journal[r].prod);\n        if constexpr (!value_commutative)\
    \ {\n            _journal[t].rprod = ActedMonoid::op(ActedMonoid::op(_journal[r].rprod,\
    \ _journal[t].val), _journal[l].rprod);\n        }\n    }\n\n    void all_apply(int\
    \ t, const F& f) {\n        if (!t) return;\n        _journal.touch(t);\n    \
    \    int left_count = node_count(_journal[t].l);\n        _journal[t].val = mapping_at(f,\
    \ _journal[t].val, left_count);\n        _journal[t].prod = mapping_at(f, _journal[t].prod,\
    \ 0);\n        if constexpr (!value_commutative) {\n            _journal[t].rprod\
    \ = mapping_at(reverse_operator(f, node_count(t)), _journal[t].rprod, 0);\n  \
    \      }\n        _journal[t].lazy = ActedMonoid::op_comp(f, _journal[t].lazy);\n\
    \        _journal[t].has_lazy = true;\n    }\n\n    void apply_reverse(int t)\
    \ {\n        if (!t) return;\n        _journal.touch(t);\n        std::swap(_journal[t].l,\
    \ _journal[t].r);\n        _journal[t].rev = !_journal[t].rev;\n        if constexpr\
    \ (!value_commutative) {\n            std::swap(_journal[t].prod, _journal[t].rprod);\n\
    \        }\n        if (_journal[t].has_lazy) {\n            _journal[t].lazy\
    \ = reverse_operator(_journal[t].lazy, node_count(t));\n        }\n    }\n\n \
    \   void push(int t) {\n        if (!t) return;\n        _journal.touch(t);\n\
    \        if (_journal[t].rev) {\n            apply_reverse(_journal[t].l);\n \
    \           apply_reverse(_journal[t].r);\n            _journal[t].rev = false;\n\
    \        }\n        if (_journal[t].has_lazy) {\n            all_apply(_journal[t].l,\
    \ _journal[t].lazy);\n            all_apply(_journal[t].r, shift_operator(_journal[t].lazy,\
    \ node_count(_journal[t].l) + 1));\n            _journal[t].lazy = ActedMonoid::op_id();\n\
    \            _journal[t].has_lazy = false;\n        }\n    }\n\n    void split(int\
    \ t, int pos, int& l, int& r) {\n        if (!t) {\n            l = r = 0;\n \
    \           return;\n        }\n        if (pos == 0) {\n            l = 0;\n\
    \            r = t;\n            return;\n        }\n        if (pos == node_count(t))\
    \ {\n            l = t;\n            r = 0;\n            return;\n        }\n\
    \        _journal.touch(t);\n        push(t);\n        int left_count = node_count(_journal[t].l);\n\
    \        if (pos == left_count) {\n            l = _journal[t].l;\n          \
    \  _journal[t].l = 0;\n            update(t);\n            r = t;\n          \
    \  return;\n        }\n        if (pos == left_count + 1) {\n            r = _journal[t].r;\n\
    \            _journal[t].r = 0;\n            update(t);\n            l = t;\n\
    \            return;\n        }\n        if (pos <= left_count) {\n          \
    \  split(_journal[t].l, pos, l, _journal[t].l);\n            r = t;\n        }\
    \ else {\n            split(_journal[t].r, pos - left_count - 1, _journal[t].r,\
    \ r);\n            l = t;\n        }\n        update(t);\n    }\n\n    int merge(int\
    \ l, int r) {\n        if (!l || !r) return l ? l : r;\n        if (_journal[l].priority\
    \ > _journal[r].priority) {\n            push(l);\n            _journal.touch(l);\n\
    \            if (_journal[l].r) {\n                _journal[l].r = merge(_journal[l].r,\
    \ r);\n            } else {\n                _journal[l].r = r;\n            }\n\
    \            update(l);\n            return l;\n        } else {\n           \
    \ push(r);\n            _journal.touch(r);\n            if (_journal[r].l) {\n\
    \                _journal[r].l = merge(l, _journal[r].l);\n            } else\
    \ {\n                _journal[r].l = l;\n            }\n            update(r);\n\
    \            return r;\n        }\n    }\n\n    void split_three(int t, int ql,\
    \ int qr, int& a, int& b, int& c) {\n        if (ql == qr) {\n            split(t,\
    \ ql, a, c);\n            b = 0;\n            return;\n        }\n        if (ql\
    \ == 0 && qr == node_count(t)) {\n            a = c = 0;\n            b = t;\n\
    \            return;\n        }\n        _journal.touch(t);\n        push(t);\n\
    \        int left_count = node_count(_journal[t].l);\n        if (qr <= left_count)\
    \ {\n            split_three(_journal[t].l, ql, qr, a, b, _journal[t].l);\n  \
    \          c = t;\n            update(t);\n        } else if (left_count < ql)\
    \ {\n            split_three(_journal[t].r, ql - left_count - 1, qr - left_count\
    \ - 1, _journal[t].r, b, c);\n            a = t;\n            update(t);\n   \
    \     } else {\n            split(_journal[t].l, ql, a, _journal[t].l);\n    \
    \        split(_journal[t].r, qr - left_count - 1, _journal[t].r, c);\n      \
    \      b = t;\n            update(t);\n        }\n    }\n\n    int merge_three(int\
    \ a, int b, int c) {\n        if (!a) return merge(b, c);\n        if (!b) return\
    \ merge(a, c);\n        if (!c) return merge(a, b);\n        std::uint32_t pa\
    \ = _journal[a].priority;\n        std::uint32_t pb = _journal[b].priority;\n\
    \        std::uint32_t pc = _journal[c].priority;\n        if (pb >= pa && pb\
    \ >= pc) {\n            push(b);\n            _journal.touch(b);\n           \
    \ _journal[b].l = merge(a, _journal[b].l);\n            _journal[b].r = merge(_journal[b].r,\
    \ c);\n            update(b);\n            return b;\n        }\n        if (pa\
    \ >= pc) {\n            push(a);\n            _journal.touch(a);\n           \
    \ _journal[a].r = merge_three(_journal[a].r, b, c);\n            update(a);\n\
    \            return a;\n        }\n        push(c);\n        _journal.touch(c);\n\
    \        _journal[c].l = merge_three(a, b, _journal[c].l);\n        update(c);\n\
    \        return c;\n    }\n\n    int insert_node(int t, int pos, int node) {\n\
    \        if (!t) return node;\n        if (_journal[node].priority > _journal[t].priority)\
    \ {\n            _journal.touch(node);\n            split(t, pos, _journal[node].l,\
    \ _journal[node].r);\n            update(node);\n            return node;\n  \
    \      }\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (pos <= left_count) {\n           \
    \ _journal[t].l = insert_node(_journal[t].l, pos, node);\n        } else {\n \
    \           _journal[t].r = insert_node(_journal[t].r, pos - left_count - 1, node);\n\
    \        }\n        update(t);\n        return t;\n    }\n\n    int erase_node(int\
    \ t, int pos) {\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (pos < left_count) {\n            _journal[t].l\
    \ = erase_node(_journal[t].l, pos);\n            update(t);\n            return\
    \ t;\n        }\n        if (pos == left_count) {\n            int res = merge(_journal[t].l,\
    \ _journal[t].r);\n            release_node(t);\n            return res;\n   \
    \     }\n        _journal[t].r = erase_node(_journal[t].r, pos - left_count -\
    \ 1);\n        update(t);\n        return t;\n    }\n\n    void set_node(int t,\
    \ int pos, T value) {\n        push(t);\n        _journal.touch(t);\n        int\
    \ left_count = node_count(_journal[t].l);\n        if (pos < left_count) {\n \
    \           set_node(_journal[t].l, pos, std::move(value));\n        } else if\
    \ (pos == left_count) {\n            _journal[t].val = std::move(value);\n   \
    \     } else {\n            set_node(_journal[t].r, pos - left_count - 1, std::move(value));\n\
    \        }\n        update(t);\n    }\n\n    void apply_node(int t, int pos, const\
    \ F& f) {\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (pos < left_count) {\n            apply_node(_journal[t].l,\
    \ pos, f);\n        } else if (pos == left_count) {\n            _journal[t].val\
    \ = mapping_at(f, _journal[t].val, 0);\n        } else {\n            apply_node(_journal[t].r,\
    \ pos - left_count - 1, f);\n        }\n        update(t);\n    }\n\n    void\
    \ apply_range(int t, int ql, int qr, const F& f) {\n        if (ql == 0 && qr\
    \ == node_count(t)) {\n            all_apply(t, f);\n            return;\n   \
    \     }\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (qr <= left_count) {\n            apply_range(_journal[t].l,\
    \ ql, qr, f);\n        } else if (left_count < ql) {\n            apply_range(_journal[t].r,\
    \ ql - left_count - 1, qr - left_count - 1, f);\n        } else {\n          \
    \  if (ql < left_count) {\n                apply_range(_journal[t].l, ql, left_count,\
    \ f);\n            }\n            _journal[t].val = mapping_at(f, _journal[t].val,\
    \ left_count - ql);\n            if (left_count + 1 < qr) {\n                apply_range(_journal[t].r,\
    \ 0, qr - left_count - 1,\n                            shift_operator(f, left_count\
    \ + 1 - ql));\n            }\n        }\n        update(t);\n    }\n\n    T prod_range(int\
    \ t, int ql, int qr) {\n        if (ql == 0 && qr == node_count(t)) return _journal[t].prod;\n\
    \        push(t);\n        int left_count = node_count(_journal[t].l);\n     \
    \   if (qr <= left_count) {\n            return prod_range(_journal[t].l, ql,\
    \ qr);\n        }\n        if (left_count < ql) {\n            return prod_range(_journal[t].r,\
    \ ql - left_count - 1, qr - left_count - 1);\n        }\n        T res = _journal[t].val;\n\
    \        if (ql < left_count) {\n            res = ActedMonoid::op(prod_range(_journal[t].l,\
    \ ql, left_count), res);\n        }\n        if (left_count + 1 < qr) {\n    \
    \        res = ActedMonoid::op(res, prod_range(_journal[t].r, 0, qr - left_count\
    \ - 1));\n        }\n        return res;\n    }\n\n    int find_node(int t, int\
    \ pos) {\n        while (t) {\n            push(t);\n            int left_count\
    \ = node_count(_journal[t].l);\n            if (pos < left_count) {\n        \
    \        t = _journal[t].l;\n            } else if (pos == left_count) {\n   \
    \             return t;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = _journal[t].r;\n            }\n        }\n       \
    \ return 0;\n    }\n\n    void dump_dfs(int t, std::vector<T>& res) {\n      \
    \  if (!t) return;\n        push(t);\n        dump_dfs(_journal[t].l, res);\n\
    \        res.push_back(_journal[t].val);\n        dump_dfs(_journal[t].r, res);\n\
    \        update(t);\n    }\n\n    void dump_range_dfs(int t, int ql, int qr, int\
    \ offset, std::vector<T>& res) {\n        if (!t || qr <= offset || offset + node_count(t)\
    \ <= ql) return;\n        push(t);\n        int left_count = node_count(_journal[t].l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(_journal[t].l,\
    \ ql, qr, offset, res);\n        if (ql <= node_pos && node_pos < qr) {\n    \
    \        res.push_back(_journal[t].val);\n        }\n        dump_range_dfs(_journal[t].r,\
    \ ql, qr, node_pos + 1, res);\n        update(t);\n    }\n\n    int clone_subtree_from(const\
    \ RollbackDynamicLazyMonoidArray& other, int t) {\n        if (!t) return 0;\n\
    \        Node source = other._journal[t];\n        int res = int(_journal.nodes.size());\n\
    \        _journal.emplace(std::move(source));\n        _journal[res].l = clone_subtree_from(other,\
    \ other._journal[t].l);\n        _journal[res].r = clone_subtree_from(other, other._journal[t].r);\n\
    \        return res;\n    }\n\n    void update_dfs(int t) {\n        if (!t) return;\n\
    \        update_dfs(_journal[t].l);\n        update_dfs(_journal[t].r);\n    \
    \    update(t);\n    }\n\n    int build_cartesian(int first, int last) {\n   \
    \     if (first == last) return 0;\n        std::vector<int> stack;\n        stack.reserve(last\
    \ - first);\n        for (int i = first; i < last; i++) {\n            int left_child\
    \ = 0;\n            while (!stack.empty() && _journal[stack.back()].priority <\
    \ _journal[i].priority) {\n                left_child = stack.back();\n      \
    \          stack.pop_back();\n            }\n            _journal[i].l = left_child;\n\
    \            if (!stack.empty()) {\n                _journal[stack.back()].r =\
    \ i;\n            }\n            stack.push_back(i);\n        }\n        int res\
    \ = stack.front();\n        update_dfs(res);\n        return res;\n    }\n\n \
    \   int build_from_vector(const std::vector<T>& v) {\n        int saved_free_head\
    \ = std::exchange(free_head, 0);\n        int first = int(_journal.nodes.size());\n\
    \        _journal.nodes.reserve(_journal.nodes.size() + v.size());\n        for\
    \ (const T& x : v) {\n            new_node(x);\n        }\n        int result\
    \ = build_cartesian(first, int(_journal.nodes.size()));\n        free_head = saved_free_head;\n\
    \        return result;\n    }\n\n    int build_from_vector(std::vector<T>&& v)\
    \ {\n        int saved_free_head = std::exchange(free_head, 0);\n        int first\
    \ = int(_journal.nodes.size());\n        _journal.nodes.reserve(_journal.nodes.size()\
    \ + v.size());\n        for (T& x : v) {\n            new_node(std::move(x));\n\
    \        }\n        int result = build_cartesian(first, int(_journal.nodes.size()));\n\
    \        free_head = saved_free_head;\n        return result;\n    }\n\n    template\
    \ <typename U>\n    int build_from_values(const std::vector<U>& v) {\n       \
    \ int saved_free_head = std::exchange(free_head, 0);\n        int first = int(_journal.nodes.size());\n\
    \        _journal.nodes.reserve(_journal.nodes.size() + v.size());\n        for\
    \ (const U& x : v) {\n            new_node(make_value(x));\n        }\n      \
    \  int result = build_cartesian(first, int(_journal.nodes.size()));\n        free_head\
    \ = saved_free_head;\n        return result;\n    }\n\n    void release_subtree(int\
    \ t) {\n        if (!t) return;\n        std::vector<int> stack(1, t);\n     \
    \   while (!stack.empty()) {\n            int node = stack.back();\n         \
    \   stack.pop_back();\n            int left = _journal[node].l;\n            int\
    \ right = _journal[node].r;\n            if (left) stack.push_back(left);\n  \
    \          if (right) stack.push_back(right);\n            release_node(node);\n\
    \        }\n    }\n\n    void reset_to_empty() {\n        _journal.clear();\n\
    \        _journal.emplace();\n        root = 0;\n        _state_checkpoints.clear();\n\
    \        free_head = 0;\n    }\n\n   public:\n    RollbackDynamicLazyMonoidArray()\n\
    \        : root(0),\n          free_head(0),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        _journal.emplace();\n        if (rng_state == 0) rng_state = 1;\n\
    \    }\n\n    RollbackDynamicLazyMonoidArray(const RollbackDynamicLazyMonoidArray&\
    \ other)\n        : root(other.root), free_head(other.free_head), rng_state(other.rng_state)\
    \ {\n        _journal.nodes = other._journal.nodes;\n        _journal.saved_epoch.assign(_journal.nodes.size(),\
    \ 0);\n    }\n\n    RollbackDynamicLazyMonoidArray(RollbackDynamicLazyMonoidArray&&\
    \ other) noexcept\n        : _journal(std::move(other._journal)),\n          _state_checkpoints(std::move(other._state_checkpoints)),\n\
    \          root(other.root),\n          free_head(other.free_head),\n        \
    \  rng_state(other.rng_state) {\n        other.reset_to_empty();\n    }\n\n  \
    \  RollbackDynamicLazyMonoidArray& operator=(const RollbackDynamicLazyMonoidArray&\
    \ other) {\n        if (this != &other) {\n            _journal.nodes = other._journal.nodes;\n\
    \            _journal.saved_epoch.assign(_journal.nodes.size(), 0);\n        \
    \    _journal.changes.clear();\n            _journal.checkpoints.clear();\n  \
    \          _state_checkpoints.clear();\n            root = other.root;\n     \
    \       free_head = other.free_head;\n            rng_state = other.rng_state;\n\
    \        }\n        return *this;\n    }\n\n    RollbackDynamicLazyMonoidArray&\
    \ operator=(RollbackDynamicLazyMonoidArray&& other) noexcept {\n        if (this\
    \ != &other) {\n            _journal = std::move(other._journal);\n          \
    \  _state_checkpoints = std::move(other._state_checkpoints);\n            root\
    \ = other.root;\n            free_head = other.free_head;\n            rng_state\
    \ = other.rng_state;\n            other.reset_to_empty();\n        }\n       \
    \ return *this;\n    }\n\n    explicit RollbackDynamicLazyMonoidArray(int n)\n\
    \        : RollbackDynamicLazyMonoidArray(n, ActedMonoid::id()) {}\n\n    RollbackDynamicLazyMonoidArray(int\
    \ n, const T& value) : RollbackDynamicLazyMonoidArray() {\n        assert(0 <=\
    \ n);\n        _journal.nodes.reserve(n + 1);\n        int first = int(_journal.nodes.size());\n\
    \        for (int i = 0; i < n; i++) {\n            new_node(value);\n       \
    \ }\n        root = build_cartesian(first, int(_journal.nodes.size()));\n    }\n\
    \n    explicit RollbackDynamicLazyMonoidArray(const std::vector<T>& v) : RollbackDynamicLazyMonoidArray()\
    \ {\n        _journal.nodes.reserve(v.size() + 1);\n        root = build_from_vector(v);\n\
    \    }\n\n    explicit RollbackDynamicLazyMonoidArray(std::vector<T>&& v) : RollbackDynamicLazyMonoidArray()\
    \ {\n        _journal.nodes.reserve(v.size() + 1);\n        root = build_from_vector(std::move(v));\n\
    \    }\n\n    template <typename U>\n        requires(!std::same_as<U, T>) &&\
    \ (requires(U x) { ActedMonoid::make(x); } || std::convertible_to<U, T>)\n   \
    \ explicit RollbackDynamicLazyMonoidArray(const std::vector<U>& v) : RollbackDynamicLazyMonoidArray()\
    \ {\n        _journal.nodes.reserve(v.size() + 1);\n        root = build_from_values(v);\n\
    \    }\n\n    RollbackDynamicLazyMonoidArray(std::initializer_list<T> init) :\
    \ RollbackDynamicLazyMonoidArray() {\n        _journal.nodes.reserve(init.size()\
    \ + 1);\n        for (const T& x : init) push_back(x);\n    }\n\n    int size()\
    \ const {\n        return node_count(root);\n    }\n\n    std::size_t node_count()\
    \ const { return _journal.nodes.size() - 1; }\n\n    void reserve(std::size_t\
    \ capacity) {\n        _journal.nodes.reserve(capacity + 1);\n        _journal.saved_epoch.reserve(capacity\
    \ + 1);\n    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\
    \n    void clear() {\n        release_subtree(root);\n        root = 0;\n    }\n\
    \n    void insert(int pos, T value) {\n        assert(0 <= pos && pos <= size());\n\
    \        root = insert_node(root, pos, new_node(std::move(value)));\n    }\n\n\
    \    void insert(int pos, const std::vector<T>& v) {\n        assert(0 <= pos\
    \ && pos <= size());\n        _journal.nodes.reserve(_journal.nodes.size() + v.size());\n\
    \        int mid = build_from_vector(v);\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::vector<T>&& v) {\n        assert(0 <= pos && pos <= size());\n   \
    \     _journal.nodes.reserve(_journal.nodes.size() + v.size());\n        int mid\
    \ = build_from_vector(std::move(v));\n        int l, r;\n        split(root, pos,\
    \ l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::initializer_list<T> init) {\n        insert(pos, std::vector<T>(init));\n\
    \    }\n\n    void insert(int pos, const RollbackDynamicLazyMonoidArray& other)\
    \ {\n        assert(0 <= pos && pos <= size());\n        if (other.empty()) return;\n\
    \        _journal.nodes.reserve(_journal.nodes.size() + other.size());\n     \
    \   int mid = clone_subtree_from(other, other.root);\n        int l, r;\n    \
    \    split(root, pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\
    \n    void push_back(T value) {\n        insert(size(), std::move(value));\n \
    \   }\n\n    void push_front(T value) {\n        insert(0, std::move(value));\n\
    \    }\n\n    void append(const std::vector<T>& v) {\n        insert(size(), v);\n\
    \    }\n\n    void append(std::vector<T>&& v) {\n        insert(size(), std::move(v));\n\
    \    }\n\n    void append(const RollbackDynamicLazyMonoidArray& other) {\n   \
    \     insert(size(), other);\n    }\n\n    void erase(int pos) {\n        assert(0\
    \ <= pos && pos < size());\n        root = erase_node(root, pos);\n    }\n\n \
    \   void erase(int l, int r) {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return;\n        int a, b, c;\n        split_three(root,\
    \ l, r, a, b, c);\n        release_subtree(b);\n        root = merge(a, c);\n\
    \    }\n\n    void pop_back() {\n        assert(!empty());\n        erase(size()\
    \ - 1);\n    }\n\n    void pop_front() {\n        assert(!empty());\n        erase(0);\n\
    \    }\n\n    T get(int pos) {\n        assert(0 <= pos && pos < size());\n  \
    \      int t = find_node(root, pos);\n        return _journal[t].val;\n    }\n\
    \n    T operator[](int pos) {\n        return get(pos);\n    }\n\n    T front()\
    \ {\n        assert(!empty());\n        return get(0);\n    }\n\n    T back()\
    \ {\n        assert(!empty());\n        return get(size() - 1);\n    }\n\n   \
    \ void set(int pos, T value) {\n        assert(0 <= pos && pos < size());\n  \
    \      set_node(root, pos, std::move(value));\n    }\n\n    void reverse(int l,\
    \ int r) {\n        assert(0 <= l && l <= r && r <= size());\n        if (l ==\
    \ r) return;\n        int a, b, c;\n        split_three(root, l, r, a, b, c);\n\
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
    \ prod_range(root, l, r);\n    }\n\n    T all_prod() const {\n        return _journal[root].prod;\n\
    \    }\n\n    std::vector<T> to_vector() {\n        std::vector<T> res;\n    \
    \    res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n\
    \    }\n\n    std::vector<T> to_vector(int l, int r) {\n        assert(0 <= l\
    \ && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n\n    RollbackDynamicLazyMonoidArray split_off(int pos) {\n        assert(0\
    \ <= pos && pos <= size());\n        int l, r;\n        split(root, pos, l, r);\n\
    \        root = l;\n\n        RollbackDynamicLazyMonoidArray res;\n        res._journal.nodes.reserve(node_count(r)\
    \ + 1);\n        res.root = res.clone_subtree_from(*this, r);\n        release_subtree(r);\n\
    \        return res;\n    }\n\n    void set_inplace(int pos, T value) { set(pos,\
    \ std::move(value)); }\n    void apply_inplace(int pos, const F& f) { apply(pos,\
    \ f); }\n    void apply_inplace(int left, int right, const F& f) { apply(left,\
    \ right, f); }\n\n    int snapshot() {\n        int state = _journal.snapshot();\n\
    \        _state_checkpoints.push_back(StateCheckpoint{root, free_head});\n   \
    \     assert(state == int(_state_checkpoints.size()));\n        return state;\n\
    \    }\n    int snapshot_count() const { return int(_state_checkpoints.size());\
    \ }\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n  \
    \      _journal.reserve_snapshots(count);\n        _state_checkpoints.reserve(count);\n\
    \    }\n    void rollback(int state) {\n        assert(1 <= state && state <=\
    \ snapshot_count());\n        StateCheckpoint checkpoint = _state_checkpoints[state\
    \ - 1];\n        _journal.rollback(state);\n        root = checkpoint.root;\n\
    \        free_head = checkpoint.free_head;\n        _state_checkpoints.resize(state);\n\
    \    }\n    void clear_history() {\n        _journal.clear_history();\n      \
    \  _state_checkpoints.clear();\n    }\n    void release() { reset_to_empty();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_LAZY_MONOID_ARRAY_HPP\n#define\
    \ M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_LAZY_MONOID_ARRAY_HPP 1\n\n#include\
    \ <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n#include\
    \ <initializer_list>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#include \"../../acted_monoid/concept.hpp\"\n#include \"../detail/rollback_journal.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct RollbackDynamicLazyMonoidArray {\n    using T = typename\
    \ ActedMonoid::value_type;\n    using F = typename ActedMonoid::operator_type;\n\
    \n   private:\n    static constexpr bool value_commutative = [] {\n        if\
    \ constexpr (requires { ActedMonoid::commutative; }) {\n            return bool(ActedMonoid::commutative);\n\
    \        } else {\n            return false;\n        }\n    }();\n\n    struct\
    \ EmptyReverseProduct {};\n    using ReverseProduct = std::conditional_t<value_commutative,\
    \ EmptyReverseProduct, T>;\n\n    static constexpr bool count_stored_in_value\
    \ = requires(const T& value) {\n        { ActedMonoid::size(value) } -> std::convertible_to<int>;\n\
    \    };\n\n    struct EmptyCount {};\n    using Count = std::conditional_t<count_stored_in_value,\
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
    \              l(0),\n              r(0) {}\n    };\n\n    detail::RollbackJournal<Node>\
    \ _journal;\n    struct StateCheckpoint { int root; int free_head; };\n    std::vector<StateCheckpoint>\
    \ _state_checkpoints;\n    int root;\n    int free_head;\n    std::uint32_t rng_state;\n\
    \n    int node_count(int t) const {\n        if constexpr (count_stored_in_value)\
    \ {\n            return int(ActedMonoid::size(_journal[t].prod));\n        } else\
    \ {\n            return _journal[t].count;\n        }\n    }\n\n    void set_node_count(int\
    \ t, int count) {\n        _journal.touch(t);\n        if constexpr (!count_stored_in_value)\
    \ {\n            _journal[t].count = count;\n        }\n    }\n\n    template\
    \ <typename U>\n    static T make_value(const U& value) {\n        if constexpr\
    \ (requires(U x) { ActedMonoid::make(x); }) {\n            return ActedMonoid::make(value);\n\
    \        } else {\n            return static_cast<T>(value);\n        }\n    }\n\
    \n    static T mapping_at(const F& f, const T& value, long long ord) {\n     \
    \   if constexpr (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x,\
    \ i); }) {\n            return ActedMonoid::mapping(f, value, ord);\n        }\
    \ else {\n            return ActedMonoid::mapping(f, value);\n        }\n    }\n\
    \n    static F shift_operator(const F& f, long long ord) {\n        if constexpr\
    \ (requires(F g, long long i) { ActedMonoid::op_shift(g, i); }) {\n          \
    \  return ActedMonoid::op_shift(f, ord);\n        } else {\n            return\
    \ f;\n        }\n    }\n\n    static F reverse_operator(const F& f, long long\
    \ size) {\n        if constexpr (requires(F g, long long n) { ActedMonoid::op_reverse(g,\
    \ n); }) {\n            return ActedMonoid::op_reverse(f, size);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    int new_node(T value) {\n\
    \        int priority = next_priority();\n        if (free_head) {\n         \
    \   int res = free_head;\n            _journal.touch(res);\n            free_head\
    \ = _journal[res].l;\n            _journal[res] = Node(std::move(value), priority);\n\
    \            return res;\n        }\n        _journal.emplace(std::move(value),\
    \ priority);\n        return int(_journal.nodes.size()) - 1;\n    }\n\n    void\
    \ release_node(int t) {\n        _journal.touch(t);\n        _journal[t].l = free_head;\n\
    \        free_head = t;\n    }\n\n    int next_priority() {\n        rng_state\
    \ ^= rng_state << 13;\n        rng_state ^= rng_state >> 17;\n        rng_state\
    \ ^= rng_state << 5;\n        return int(rng_state);\n    }\n\n    void update(int\
    \ t) {\n        if (!t) return;\n        _journal.touch(t);\n        int l = _journal[t].l;\n\
    \        int r = _journal[t].r;\n        set_node_count(t, 1 + node_count(l) +\
    \ node_count(r));\n        _journal[t].prod = ActedMonoid::op(ActedMonoid::op(_journal[l].prod,\
    \ _journal[t].val), _journal[r].prod);\n        if constexpr (!value_commutative)\
    \ {\n            _journal[t].rprod = ActedMonoid::op(ActedMonoid::op(_journal[r].rprod,\
    \ _journal[t].val), _journal[l].rprod);\n        }\n    }\n\n    void all_apply(int\
    \ t, const F& f) {\n        if (!t) return;\n        _journal.touch(t);\n    \
    \    int left_count = node_count(_journal[t].l);\n        _journal[t].val = mapping_at(f,\
    \ _journal[t].val, left_count);\n        _journal[t].prod = mapping_at(f, _journal[t].prod,\
    \ 0);\n        if constexpr (!value_commutative) {\n            _journal[t].rprod\
    \ = mapping_at(reverse_operator(f, node_count(t)), _journal[t].rprod, 0);\n  \
    \      }\n        _journal[t].lazy = ActedMonoid::op_comp(f, _journal[t].lazy);\n\
    \        _journal[t].has_lazy = true;\n    }\n\n    void apply_reverse(int t)\
    \ {\n        if (!t) return;\n        _journal.touch(t);\n        std::swap(_journal[t].l,\
    \ _journal[t].r);\n        _journal[t].rev = !_journal[t].rev;\n        if constexpr\
    \ (!value_commutative) {\n            std::swap(_journal[t].prod, _journal[t].rprod);\n\
    \        }\n        if (_journal[t].has_lazy) {\n            _journal[t].lazy\
    \ = reverse_operator(_journal[t].lazy, node_count(t));\n        }\n    }\n\n \
    \   void push(int t) {\n        if (!t) return;\n        _journal.touch(t);\n\
    \        if (_journal[t].rev) {\n            apply_reverse(_journal[t].l);\n \
    \           apply_reverse(_journal[t].r);\n            _journal[t].rev = false;\n\
    \        }\n        if (_journal[t].has_lazy) {\n            all_apply(_journal[t].l,\
    \ _journal[t].lazy);\n            all_apply(_journal[t].r, shift_operator(_journal[t].lazy,\
    \ node_count(_journal[t].l) + 1));\n            _journal[t].lazy = ActedMonoid::op_id();\n\
    \            _journal[t].has_lazy = false;\n        }\n    }\n\n    void split(int\
    \ t, int pos, int& l, int& r) {\n        if (!t) {\n            l = r = 0;\n \
    \           return;\n        }\n        if (pos == 0) {\n            l = 0;\n\
    \            r = t;\n            return;\n        }\n        if (pos == node_count(t))\
    \ {\n            l = t;\n            r = 0;\n            return;\n        }\n\
    \        _journal.touch(t);\n        push(t);\n        int left_count = node_count(_journal[t].l);\n\
    \        if (pos == left_count) {\n            l = _journal[t].l;\n          \
    \  _journal[t].l = 0;\n            update(t);\n            r = t;\n          \
    \  return;\n        }\n        if (pos == left_count + 1) {\n            r = _journal[t].r;\n\
    \            _journal[t].r = 0;\n            update(t);\n            l = t;\n\
    \            return;\n        }\n        if (pos <= left_count) {\n          \
    \  split(_journal[t].l, pos, l, _journal[t].l);\n            r = t;\n        }\
    \ else {\n            split(_journal[t].r, pos - left_count - 1, _journal[t].r,\
    \ r);\n            l = t;\n        }\n        update(t);\n    }\n\n    int merge(int\
    \ l, int r) {\n        if (!l || !r) return l ? l : r;\n        if (_journal[l].priority\
    \ > _journal[r].priority) {\n            push(l);\n            _journal.touch(l);\n\
    \            if (_journal[l].r) {\n                _journal[l].r = merge(_journal[l].r,\
    \ r);\n            } else {\n                _journal[l].r = r;\n            }\n\
    \            update(l);\n            return l;\n        } else {\n           \
    \ push(r);\n            _journal.touch(r);\n            if (_journal[r].l) {\n\
    \                _journal[r].l = merge(l, _journal[r].l);\n            } else\
    \ {\n                _journal[r].l = l;\n            }\n            update(r);\n\
    \            return r;\n        }\n    }\n\n    void split_three(int t, int ql,\
    \ int qr, int& a, int& b, int& c) {\n        if (ql == qr) {\n            split(t,\
    \ ql, a, c);\n            b = 0;\n            return;\n        }\n        if (ql\
    \ == 0 && qr == node_count(t)) {\n            a = c = 0;\n            b = t;\n\
    \            return;\n        }\n        _journal.touch(t);\n        push(t);\n\
    \        int left_count = node_count(_journal[t].l);\n        if (qr <= left_count)\
    \ {\n            split_three(_journal[t].l, ql, qr, a, b, _journal[t].l);\n  \
    \          c = t;\n            update(t);\n        } else if (left_count < ql)\
    \ {\n            split_three(_journal[t].r, ql - left_count - 1, qr - left_count\
    \ - 1, _journal[t].r, b, c);\n            a = t;\n            update(t);\n   \
    \     } else {\n            split(_journal[t].l, ql, a, _journal[t].l);\n    \
    \        split(_journal[t].r, qr - left_count - 1, _journal[t].r, c);\n      \
    \      b = t;\n            update(t);\n        }\n    }\n\n    int merge_three(int\
    \ a, int b, int c) {\n        if (!a) return merge(b, c);\n        if (!b) return\
    \ merge(a, c);\n        if (!c) return merge(a, b);\n        std::uint32_t pa\
    \ = _journal[a].priority;\n        std::uint32_t pb = _journal[b].priority;\n\
    \        std::uint32_t pc = _journal[c].priority;\n        if (pb >= pa && pb\
    \ >= pc) {\n            push(b);\n            _journal.touch(b);\n           \
    \ _journal[b].l = merge(a, _journal[b].l);\n            _journal[b].r = merge(_journal[b].r,\
    \ c);\n            update(b);\n            return b;\n        }\n        if (pa\
    \ >= pc) {\n            push(a);\n            _journal.touch(a);\n           \
    \ _journal[a].r = merge_three(_journal[a].r, b, c);\n            update(a);\n\
    \            return a;\n        }\n        push(c);\n        _journal.touch(c);\n\
    \        _journal[c].l = merge_three(a, b, _journal[c].l);\n        update(c);\n\
    \        return c;\n    }\n\n    int insert_node(int t, int pos, int node) {\n\
    \        if (!t) return node;\n        if (_journal[node].priority > _journal[t].priority)\
    \ {\n            _journal.touch(node);\n            split(t, pos, _journal[node].l,\
    \ _journal[node].r);\n            update(node);\n            return node;\n  \
    \      }\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (pos <= left_count) {\n           \
    \ _journal[t].l = insert_node(_journal[t].l, pos, node);\n        } else {\n \
    \           _journal[t].r = insert_node(_journal[t].r, pos - left_count - 1, node);\n\
    \        }\n        update(t);\n        return t;\n    }\n\n    int erase_node(int\
    \ t, int pos) {\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (pos < left_count) {\n            _journal[t].l\
    \ = erase_node(_journal[t].l, pos);\n            update(t);\n            return\
    \ t;\n        }\n        if (pos == left_count) {\n            int res = merge(_journal[t].l,\
    \ _journal[t].r);\n            release_node(t);\n            return res;\n   \
    \     }\n        _journal[t].r = erase_node(_journal[t].r, pos - left_count -\
    \ 1);\n        update(t);\n        return t;\n    }\n\n    void set_node(int t,\
    \ int pos, T value) {\n        push(t);\n        _journal.touch(t);\n        int\
    \ left_count = node_count(_journal[t].l);\n        if (pos < left_count) {\n \
    \           set_node(_journal[t].l, pos, std::move(value));\n        } else if\
    \ (pos == left_count) {\n            _journal[t].val = std::move(value);\n   \
    \     } else {\n            set_node(_journal[t].r, pos - left_count - 1, std::move(value));\n\
    \        }\n        update(t);\n    }\n\n    void apply_node(int t, int pos, const\
    \ F& f) {\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (pos < left_count) {\n            apply_node(_journal[t].l,\
    \ pos, f);\n        } else if (pos == left_count) {\n            _journal[t].val\
    \ = mapping_at(f, _journal[t].val, 0);\n        } else {\n            apply_node(_journal[t].r,\
    \ pos - left_count - 1, f);\n        }\n        update(t);\n    }\n\n    void\
    \ apply_range(int t, int ql, int qr, const F& f) {\n        if (ql == 0 && qr\
    \ == node_count(t)) {\n            all_apply(t, f);\n            return;\n   \
    \     }\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (qr <= left_count) {\n            apply_range(_journal[t].l,\
    \ ql, qr, f);\n        } else if (left_count < ql) {\n            apply_range(_journal[t].r,\
    \ ql - left_count - 1, qr - left_count - 1, f);\n        } else {\n          \
    \  if (ql < left_count) {\n                apply_range(_journal[t].l, ql, left_count,\
    \ f);\n            }\n            _journal[t].val = mapping_at(f, _journal[t].val,\
    \ left_count - ql);\n            if (left_count + 1 < qr) {\n                apply_range(_journal[t].r,\
    \ 0, qr - left_count - 1,\n                            shift_operator(f, left_count\
    \ + 1 - ql));\n            }\n        }\n        update(t);\n    }\n\n    T prod_range(int\
    \ t, int ql, int qr) {\n        if (ql == 0 && qr == node_count(t)) return _journal[t].prod;\n\
    \        push(t);\n        int left_count = node_count(_journal[t].l);\n     \
    \   if (qr <= left_count) {\n            return prod_range(_journal[t].l, ql,\
    \ qr);\n        }\n        if (left_count < ql) {\n            return prod_range(_journal[t].r,\
    \ ql - left_count - 1, qr - left_count - 1);\n        }\n        T res = _journal[t].val;\n\
    \        if (ql < left_count) {\n            res = ActedMonoid::op(prod_range(_journal[t].l,\
    \ ql, left_count), res);\n        }\n        if (left_count + 1 < qr) {\n    \
    \        res = ActedMonoid::op(res, prod_range(_journal[t].r, 0, qr - left_count\
    \ - 1));\n        }\n        return res;\n    }\n\n    int find_node(int t, int\
    \ pos) {\n        while (t) {\n            push(t);\n            int left_count\
    \ = node_count(_journal[t].l);\n            if (pos < left_count) {\n        \
    \        t = _journal[t].l;\n            } else if (pos == left_count) {\n   \
    \             return t;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = _journal[t].r;\n            }\n        }\n       \
    \ return 0;\n    }\n\n    void dump_dfs(int t, std::vector<T>& res) {\n      \
    \  if (!t) return;\n        push(t);\n        dump_dfs(_journal[t].l, res);\n\
    \        res.push_back(_journal[t].val);\n        dump_dfs(_journal[t].r, res);\n\
    \        update(t);\n    }\n\n    void dump_range_dfs(int t, int ql, int qr, int\
    \ offset, std::vector<T>& res) {\n        if (!t || qr <= offset || offset + node_count(t)\
    \ <= ql) return;\n        push(t);\n        int left_count = node_count(_journal[t].l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(_journal[t].l,\
    \ ql, qr, offset, res);\n        if (ql <= node_pos && node_pos < qr) {\n    \
    \        res.push_back(_journal[t].val);\n        }\n        dump_range_dfs(_journal[t].r,\
    \ ql, qr, node_pos + 1, res);\n        update(t);\n    }\n\n    int clone_subtree_from(const\
    \ RollbackDynamicLazyMonoidArray& other, int t) {\n        if (!t) return 0;\n\
    \        Node source = other._journal[t];\n        int res = int(_journal.nodes.size());\n\
    \        _journal.emplace(std::move(source));\n        _journal[res].l = clone_subtree_from(other,\
    \ other._journal[t].l);\n        _journal[res].r = clone_subtree_from(other, other._journal[t].r);\n\
    \        return res;\n    }\n\n    void update_dfs(int t) {\n        if (!t) return;\n\
    \        update_dfs(_journal[t].l);\n        update_dfs(_journal[t].r);\n    \
    \    update(t);\n    }\n\n    int build_cartesian(int first, int last) {\n   \
    \     if (first == last) return 0;\n        std::vector<int> stack;\n        stack.reserve(last\
    \ - first);\n        for (int i = first; i < last; i++) {\n            int left_child\
    \ = 0;\n            while (!stack.empty() && _journal[stack.back()].priority <\
    \ _journal[i].priority) {\n                left_child = stack.back();\n      \
    \          stack.pop_back();\n            }\n            _journal[i].l = left_child;\n\
    \            if (!stack.empty()) {\n                _journal[stack.back()].r =\
    \ i;\n            }\n            stack.push_back(i);\n        }\n        int res\
    \ = stack.front();\n        update_dfs(res);\n        return res;\n    }\n\n \
    \   int build_from_vector(const std::vector<T>& v) {\n        int saved_free_head\
    \ = std::exchange(free_head, 0);\n        int first = int(_journal.nodes.size());\n\
    \        _journal.nodes.reserve(_journal.nodes.size() + v.size());\n        for\
    \ (const T& x : v) {\n            new_node(x);\n        }\n        int result\
    \ = build_cartesian(first, int(_journal.nodes.size()));\n        free_head = saved_free_head;\n\
    \        return result;\n    }\n\n    int build_from_vector(std::vector<T>&& v)\
    \ {\n        int saved_free_head = std::exchange(free_head, 0);\n        int first\
    \ = int(_journal.nodes.size());\n        _journal.nodes.reserve(_journal.nodes.size()\
    \ + v.size());\n        for (T& x : v) {\n            new_node(std::move(x));\n\
    \        }\n        int result = build_cartesian(first, int(_journal.nodes.size()));\n\
    \        free_head = saved_free_head;\n        return result;\n    }\n\n    template\
    \ <typename U>\n    int build_from_values(const std::vector<U>& v) {\n       \
    \ int saved_free_head = std::exchange(free_head, 0);\n        int first = int(_journal.nodes.size());\n\
    \        _journal.nodes.reserve(_journal.nodes.size() + v.size());\n        for\
    \ (const U& x : v) {\n            new_node(make_value(x));\n        }\n      \
    \  int result = build_cartesian(first, int(_journal.nodes.size()));\n        free_head\
    \ = saved_free_head;\n        return result;\n    }\n\n    void release_subtree(int\
    \ t) {\n        if (!t) return;\n        std::vector<int> stack(1, t);\n     \
    \   while (!stack.empty()) {\n            int node = stack.back();\n         \
    \   stack.pop_back();\n            int left = _journal[node].l;\n            int\
    \ right = _journal[node].r;\n            if (left) stack.push_back(left);\n  \
    \          if (right) stack.push_back(right);\n            release_node(node);\n\
    \        }\n    }\n\n    void reset_to_empty() {\n        _journal.clear();\n\
    \        _journal.emplace();\n        root = 0;\n        _state_checkpoints.clear();\n\
    \        free_head = 0;\n    }\n\n   public:\n    RollbackDynamicLazyMonoidArray()\n\
    \        : root(0),\n          free_head(0),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        _journal.emplace();\n        if (rng_state == 0) rng_state = 1;\n\
    \    }\n\n    RollbackDynamicLazyMonoidArray(const RollbackDynamicLazyMonoidArray&\
    \ other)\n        : root(other.root), free_head(other.free_head), rng_state(other.rng_state)\
    \ {\n        _journal.nodes = other._journal.nodes;\n        _journal.saved_epoch.assign(_journal.nodes.size(),\
    \ 0);\n    }\n\n    RollbackDynamicLazyMonoidArray(RollbackDynamicLazyMonoidArray&&\
    \ other) noexcept\n        : _journal(std::move(other._journal)),\n          _state_checkpoints(std::move(other._state_checkpoints)),\n\
    \          root(other.root),\n          free_head(other.free_head),\n        \
    \  rng_state(other.rng_state) {\n        other.reset_to_empty();\n    }\n\n  \
    \  RollbackDynamicLazyMonoidArray& operator=(const RollbackDynamicLazyMonoidArray&\
    \ other) {\n        if (this != &other) {\n            _journal.nodes = other._journal.nodes;\n\
    \            _journal.saved_epoch.assign(_journal.nodes.size(), 0);\n        \
    \    _journal.changes.clear();\n            _journal.checkpoints.clear();\n  \
    \          _state_checkpoints.clear();\n            root = other.root;\n     \
    \       free_head = other.free_head;\n            rng_state = other.rng_state;\n\
    \        }\n        return *this;\n    }\n\n    RollbackDynamicLazyMonoidArray&\
    \ operator=(RollbackDynamicLazyMonoidArray&& other) noexcept {\n        if (this\
    \ != &other) {\n            _journal = std::move(other._journal);\n          \
    \  _state_checkpoints = std::move(other._state_checkpoints);\n            root\
    \ = other.root;\n            free_head = other.free_head;\n            rng_state\
    \ = other.rng_state;\n            other.reset_to_empty();\n        }\n       \
    \ return *this;\n    }\n\n    explicit RollbackDynamicLazyMonoidArray(int n)\n\
    \        : RollbackDynamicLazyMonoidArray(n, ActedMonoid::id()) {}\n\n    RollbackDynamicLazyMonoidArray(int\
    \ n, const T& value) : RollbackDynamicLazyMonoidArray() {\n        assert(0 <=\
    \ n);\n        _journal.nodes.reserve(n + 1);\n        int first = int(_journal.nodes.size());\n\
    \        for (int i = 0; i < n; i++) {\n            new_node(value);\n       \
    \ }\n        root = build_cartesian(first, int(_journal.nodes.size()));\n    }\n\
    \n    explicit RollbackDynamicLazyMonoidArray(const std::vector<T>& v) : RollbackDynamicLazyMonoidArray()\
    \ {\n        _journal.nodes.reserve(v.size() + 1);\n        root = build_from_vector(v);\n\
    \    }\n\n    explicit RollbackDynamicLazyMonoidArray(std::vector<T>&& v) : RollbackDynamicLazyMonoidArray()\
    \ {\n        _journal.nodes.reserve(v.size() + 1);\n        root = build_from_vector(std::move(v));\n\
    \    }\n\n    template <typename U>\n        requires(!std::same_as<U, T>) &&\
    \ (requires(U x) { ActedMonoid::make(x); } || std::convertible_to<U, T>)\n   \
    \ explicit RollbackDynamicLazyMonoidArray(const std::vector<U>& v) : RollbackDynamicLazyMonoidArray()\
    \ {\n        _journal.nodes.reserve(v.size() + 1);\n        root = build_from_values(v);\n\
    \    }\n\n    RollbackDynamicLazyMonoidArray(std::initializer_list<T> init) :\
    \ RollbackDynamicLazyMonoidArray() {\n        _journal.nodes.reserve(init.size()\
    \ + 1);\n        for (const T& x : init) push_back(x);\n    }\n\n    int size()\
    \ const {\n        return node_count(root);\n    }\n\n    std::size_t node_count()\
    \ const { return _journal.nodes.size() - 1; }\n\n    void reserve(std::size_t\
    \ capacity) {\n        _journal.nodes.reserve(capacity + 1);\n        _journal.saved_epoch.reserve(capacity\
    \ + 1);\n    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\
    \n    void clear() {\n        release_subtree(root);\n        root = 0;\n    }\n\
    \n    void insert(int pos, T value) {\n        assert(0 <= pos && pos <= size());\n\
    \        root = insert_node(root, pos, new_node(std::move(value)));\n    }\n\n\
    \    void insert(int pos, const std::vector<T>& v) {\n        assert(0 <= pos\
    \ && pos <= size());\n        _journal.nodes.reserve(_journal.nodes.size() + v.size());\n\
    \        int mid = build_from_vector(v);\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::vector<T>&& v) {\n        assert(0 <= pos && pos <= size());\n   \
    \     _journal.nodes.reserve(_journal.nodes.size() + v.size());\n        int mid\
    \ = build_from_vector(std::move(v));\n        int l, r;\n        split(root, pos,\
    \ l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::initializer_list<T> init) {\n        insert(pos, std::vector<T>(init));\n\
    \    }\n\n    void insert(int pos, const RollbackDynamicLazyMonoidArray& other)\
    \ {\n        assert(0 <= pos && pos <= size());\n        if (other.empty()) return;\n\
    \        _journal.nodes.reserve(_journal.nodes.size() + other.size());\n     \
    \   int mid = clone_subtree_from(other, other.root);\n        int l, r;\n    \
    \    split(root, pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\
    \n    void push_back(T value) {\n        insert(size(), std::move(value));\n \
    \   }\n\n    void push_front(T value) {\n        insert(0, std::move(value));\n\
    \    }\n\n    void append(const std::vector<T>& v) {\n        insert(size(), v);\n\
    \    }\n\n    void append(std::vector<T>&& v) {\n        insert(size(), std::move(v));\n\
    \    }\n\n    void append(const RollbackDynamicLazyMonoidArray& other) {\n   \
    \     insert(size(), other);\n    }\n\n    void erase(int pos) {\n        assert(0\
    \ <= pos && pos < size());\n        root = erase_node(root, pos);\n    }\n\n \
    \   void erase(int l, int r) {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return;\n        int a, b, c;\n        split_three(root,\
    \ l, r, a, b, c);\n        release_subtree(b);\n        root = merge(a, c);\n\
    \    }\n\n    void pop_back() {\n        assert(!empty());\n        erase(size()\
    \ - 1);\n    }\n\n    void pop_front() {\n        assert(!empty());\n        erase(0);\n\
    \    }\n\n    T get(int pos) {\n        assert(0 <= pos && pos < size());\n  \
    \      int t = find_node(root, pos);\n        return _journal[t].val;\n    }\n\
    \n    T operator[](int pos) {\n        return get(pos);\n    }\n\n    T front()\
    \ {\n        assert(!empty());\n        return get(0);\n    }\n\n    T back()\
    \ {\n        assert(!empty());\n        return get(size() - 1);\n    }\n\n   \
    \ void set(int pos, T value) {\n        assert(0 <= pos && pos < size());\n  \
    \      set_node(root, pos, std::move(value));\n    }\n\n    void reverse(int l,\
    \ int r) {\n        assert(0 <= l && l <= r && r <= size());\n        if (l ==\
    \ r) return;\n        int a, b, c;\n        split_three(root, l, r, a, b, c);\n\
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
    \ prod_range(root, l, r);\n    }\n\n    T all_prod() const {\n        return _journal[root].prod;\n\
    \    }\n\n    std::vector<T> to_vector() {\n        std::vector<T> res;\n    \
    \    res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n\
    \    }\n\n    std::vector<T> to_vector(int l, int r) {\n        assert(0 <= l\
    \ && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n\n    RollbackDynamicLazyMonoidArray split_off(int pos) {\n        assert(0\
    \ <= pos && pos <= size());\n        int l, r;\n        split(root, pos, l, r);\n\
    \        root = l;\n\n        RollbackDynamicLazyMonoidArray res;\n        res._journal.nodes.reserve(node_count(r)\
    \ + 1);\n        res.root = res.clone_subtree_from(*this, r);\n        release_subtree(r);\n\
    \        return res;\n    }\n\n    void set_inplace(int pos, T value) { set(pos,\
    \ std::move(value)); }\n    void apply_inplace(int pos, const F& f) { apply(pos,\
    \ f); }\n    void apply_inplace(int left, int right, const F& f) { apply(left,\
    \ right, f); }\n\n    int snapshot() {\n        int state = _journal.snapshot();\n\
    \        _state_checkpoints.push_back(StateCheckpoint{root, free_head});\n   \
    \     assert(state == int(_state_checkpoints.size()));\n        return state;\n\
    \    }\n    int snapshot_count() const { return int(_state_checkpoints.size());\
    \ }\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n  \
    \      _journal.reserve_snapshots(count);\n        _state_checkpoints.reserve(count);\n\
    \    }\n    void rollback(int state) {\n        assert(1 <= state && state <=\
    \ snapshot_count());\n        StateCheckpoint checkpoint = _state_checkpoints[state\
    \ - 1];\n        _journal.rollback(state);\n        root = checkpoint.root;\n\
    \        free_head = checkpoint.free_head;\n        _state_checkpoints.resize(state);\n\
    \    }\n    void clear_history() {\n        _journal.clear_history();\n      \
    \  _state_checkpoints.clear();\n    }\n    void release() { reset_to_empty();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_LAZY_MONOID_ARRAY_HPP\n"
  dependsOn:
  - acted_monoid/concept.hpp
  - ds/detail/rollback_journal.hpp
  isVerificationFile: false
  path: ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp
layout: document
title: Rollback Dynamic Lazy Monoid Array
---

## Overview

`RollbackDynamicLazyMonoidArray<ActedMonoid>` is a rollback implicit treap with
range actions and range products. `ActedMonoid` must satisfy
`m1une::acted_monoid::IsActedMonoid`. Saved states preserve lazy and reversal
tags without mutating earlier history.

## Methods

Constructors and read-only methods follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the sequence and recycles its nodes. | $O(N)$ |
| `void insert(...)`, `void push_back(T value)`, `void push_front(T value)`, `void append(...)` | Inserts values. | Expected $O(\log N)$ for one/shared input; $O(M + \log N)$ for a vector or independent input |
| `void erase(int pos)`, `void erase(int left, int right)`, `void pop_back()`, `void pop_front()` | Erases values. | Expected $O(\log N)$ |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Replaces one value. | Expected $O(\log N)$ |
| `void apply(int pos, const F& f)`, `void apply(int left, int right, const F& f)` | Applies an action to one value or `[left, right)`. | Expected $O(\log N)$ |
| `void apply_inplace(...)` | Aliases of the `apply` overloads. | Expected $O(\log N)$ |
| `void reverse(int left, int right)`, `void reverse()` | Reverses a range or the whole sequence. | Expected $O(\log N)$; whole range is $O(1)$ |
| `void rotate(int left, int middle, int right)` | Rotates a range. | Expected $O(\log N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a treap node is saved only before its first mutation; newly allocated nodes are truncated directly by rollback.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp"

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::ds::RollbackDynamicLazyMonoidArray<AM> a({1, 2, 3});
int state = a.snapshot();
a.apply(0, 2, 5);
a.rollback(state);
assert(a.all_prod().sum == 6);
```
