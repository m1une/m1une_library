---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_journal.hpp
    title: ds/detail/rollback_journal.hpp
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
  bundledCode: "#line 1 \"ds/segtree/rollback_dual_segtree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
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
    \ namespace m1une\n\n\n#line 1 \"ds/detail/rollback_journal.hpp\"\n\n\n\n#line\
    \ 6 \"ds/detail/rollback_journal.hpp\"\n#include <cstddef>\n#include <cstdint>\n\
    #include <limits>\n#line 11 \"ds/detail/rollback_journal.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\nnamespace detail {\n\ntemplate <class Node>\nstruct RollbackJournal\
    \ {\n    struct Change {\n        int index;\n        Node value;\n    };\n\n\
    \    struct Checkpoint {\n        std::size_t change_size;\n        std::size_t\
    \ node_size;\n        std::uint64_t epoch;\n    };\n\n    std::vector<Node> nodes;\n\
    \    std::vector<Change> changes;\n    std::vector<Checkpoint> checkpoints;\n\
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
    \ ds\n}  // namespace m1une\n\n\n#line 12 \"ds/segtree/rollback_dual_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct RollbackDualSegtree {\n    using T = typename Monoid::value_type;\n\n \
    \  private:\n    struct Node {\n        T value = Monoid::id();\n        bool\
    \ has_value = false;\n    };\n\n    int _n = 0;\n    detail::RollbackJournal<Node>\
    \ _journal;\n\n    template <class U>\n    static T make_value(const U& value,\
    \ int index) {\n        if constexpr (requires(U x) { Monoid::make(x); }) {\n\
    \            return Monoid::make(value);\n        } else if constexpr (requires(U\
    \ x, int i) { Monoid::make(x, i); }) {\n            return Monoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n    void initialize(int n) {\n        assert(0 <= n);\n      \
    \  _n = n;\n        _journal.nodes.assign(std::max(1, 4 * n), Node());\n     \
    \   _journal.saved_epoch.assign(_journal.nodes.size(), 0);\n    }\n\n    template\
    \ <class U>\n    void build(int node, int left, int right, const std::vector<U>&\
    \ values) {\n        if (right - left == 1) {\n            _journal[node].value\
    \ = make_value(values[left], left);\n            _journal[node].has_value = true;\n\
    \            return;\n        }\n        int middle = (left + right) >> 1;\n \
    \       build(node << 1, left, middle, values);\n        build(node << 1 | 1,\
    \ middle, right, values);\n    }\n\n    void all_apply(int node, const T& value)\
    \ {\n        _journal.touch(node);\n        Node& current = _journal[node];\n\
    \        current.value = current.has_value\n            ? Monoid::op(value, current.value)\n\
    \            : value;\n        current.has_value = true;\n    }\n\n    void push(int\
    \ node) {\n        if (!_journal[node].has_value) return;\n        T value = _journal[node].value;\n\
    \        all_apply(node << 1, value);\n        all_apply(node << 1 | 1, value);\n\
    \        _journal.touch(node);\n        _journal[node].value = Monoid::id();\n\
    \        _journal[node].has_value = false;\n    }\n\n    void set_node(int node,\
    \ int left, int right, int pos, T value) {\n        if (right - left == 1) {\n\
    \            _journal.touch(node);\n            _journal[node].value = std::move(value);\n\
    \            _journal[node].has_value = true;\n            return;\n        }\n\
    \        push(node);\n        int middle = (left + right) >> 1;\n        if (pos\
    \ < middle) set_node(node << 1, left, middle, pos, std::move(value));\n      \
    \  else set_node(node << 1 | 1, middle, right, pos, std::move(value));\n    }\n\
    \n    void apply_node(int node, int left, int right, int query_left, int query_right,\
    \ const T& value) {\n        if (query_right <= left || right <= query_left) return;\n\
    \        if (query_left <= left && right <= query_right) {\n            all_apply(node,\
    \ value);\n            return;\n        }\n        push(node);\n        int middle\
    \ = (left + right) >> 1;\n        apply_node(node << 1, left, middle, query_left,\
    \ query_right, value);\n        apply_node(node << 1 | 1, middle, right, query_left,\
    \ query_right, value);\n    }\n\n    T get_node(int node, int left, int right,\
    \ int pos, T inherited) const {\n        const Node& current = _journal[node];\n\
    \        if (right - left == 1) {\n            assert(current.has_value);\n  \
    \          return Monoid::op(inherited, current.value);\n        }\n        if\
    \ (current.has_value) inherited = Monoid::op(inherited, current.value);\n    \
    \    int middle = (left + right) >> 1;\n        if (pos < middle) return get_node(node\
    \ << 1, left, middle, pos, std::move(inherited));\n        return get_node(node\
    \ << 1 | 1, middle, right, pos, std::move(inherited));\n    }\n\n   public:\n\
    \    RollbackDualSegtree() { initialize(0); }\n    explicit RollbackDualSegtree(int\
    \ n) {\n        initialize(n);\n        if (n > 0) {\n            std::vector<T>\
    \ values(n, Monoid::id());\n            build(1, 0, n, values);\n        }\n \
    \   }\n\n    explicit RollbackDualSegtree(const std::vector<T>& values) {\n  \
    \      initialize(int(values.size()));\n        if (_n > 0) build(1, 0, _n, values);\n\
    \    }\n\n    template <class U>\n        requires(!std::same_as<U, T>)\n    explicit\
    \ RollbackDualSegtree(const std::vector<U>& values) {\n        initialize(int(values.size()));\n\
    \        if (_n > 0) build(1, 0, _n, values);\n    }\n\n    int size() const {\
    \ return _n; }\n    bool empty() const { return _n == 0; }\n    std::size_t node_count()\
    \ const { return _journal.nodes.size(); }\n\n    void set(int pos, T value) {\n\
    \        assert(0 <= pos && pos < _n);\n        set_node(1, 0, _n, pos, std::move(value));\n\
    \    }\n    void set_inplace(int pos, T value) { set(pos, std::move(value)); }\n\
    \n    T get(int pos) const {\n        assert(0 <= pos && pos < _n);\n        return\
    \ get_node(1, 0, _n, pos, Monoid::id());\n    }\n    T operator[](int pos) const\
    \ { return get(pos); }\n\n    void apply(int pos, const T& value) { apply(pos,\
    \ pos + 1, value); }\n    void apply(int left, int right, const T& value) {\n\
    \        assert(0 <= left && left <= right && right <= _n);\n        if (left\
    \ != right) apply_node(1, 0, _n, left, right, value);\n    }\n    void apply_inplace(int\
    \ pos, const T& value) { apply(pos, value); }\n    void apply_inplace(int left,\
    \ int right, const T& value) { apply(left, right, value); }\n\n    int snapshot()\
    \ { return _journal.snapshot(); }\n    int snapshot_count() const { return _journal.snapshot_count();\
    \ }\n    void reserve_snapshots(int count) { _journal.reserve_snapshots(count);\
    \ }\n    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _n = 0; _journal.clear();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"../../monoid/concept.hpp\"\n#include\
    \ \"../detail/rollback_journal.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <m1une::monoid::IsMonoid Monoid>\nstruct RollbackDualSegtree {\n    using\
    \ T = typename Monoid::value_type;\n\n   private:\n    struct Node {\n       \
    \ T value = Monoid::id();\n        bool has_value = false;\n    };\n\n    int\
    \ _n = 0;\n    detail::RollbackJournal<Node> _journal;\n\n    template <class\
    \ U>\n    static T make_value(const U& value, int index) {\n        if constexpr\
    \ (requires(U x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n\
    \        } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n\
    \            return Monoid::make(value, index);\n        } else {\n          \
    \  return static_cast<T>(value);\n        }\n    }\n\n    void initialize(int\
    \ n) {\n        assert(0 <= n);\n        _n = n;\n        _journal.nodes.assign(std::max(1,\
    \ 4 * n), Node());\n        _journal.saved_epoch.assign(_journal.nodes.size(),\
    \ 0);\n    }\n\n    template <class U>\n    void build(int node, int left, int\
    \ right, const std::vector<U>& values) {\n        if (right - left == 1) {\n \
    \           _journal[node].value = make_value(values[left], left);\n         \
    \   _journal[node].has_value = true;\n            return;\n        }\n       \
    \ int middle = (left + right) >> 1;\n        build(node << 1, left, middle, values);\n\
    \        build(node << 1 | 1, middle, right, values);\n    }\n\n    void all_apply(int\
    \ node, const T& value) {\n        _journal.touch(node);\n        Node& current\
    \ = _journal[node];\n        current.value = current.has_value\n            ?\
    \ Monoid::op(value, current.value)\n            : value;\n        current.has_value\
    \ = true;\n    }\n\n    void push(int node) {\n        if (!_journal[node].has_value)\
    \ return;\n        T value = _journal[node].value;\n        all_apply(node <<\
    \ 1, value);\n        all_apply(node << 1 | 1, value);\n        _journal.touch(node);\n\
    \        _journal[node].value = Monoid::id();\n        _journal[node].has_value\
    \ = false;\n    }\n\n    void set_node(int node, int left, int right, int pos,\
    \ T value) {\n        if (right - left == 1) {\n            _journal.touch(node);\n\
    \            _journal[node].value = std::move(value);\n            _journal[node].has_value\
    \ = true;\n            return;\n        }\n        push(node);\n        int middle\
    \ = (left + right) >> 1;\n        if (pos < middle) set_node(node << 1, left,\
    \ middle, pos, std::move(value));\n        else set_node(node << 1 | 1, middle,\
    \ right, pos, std::move(value));\n    }\n\n    void apply_node(int node, int left,\
    \ int right, int query_left, int query_right, const T& value) {\n        if (query_right\
    \ <= left || right <= query_left) return;\n        if (query_left <= left && right\
    \ <= query_right) {\n            all_apply(node, value);\n            return;\n\
    \        }\n        push(node);\n        int middle = (left + right) >> 1;\n \
    \       apply_node(node << 1, left, middle, query_left, query_right, value);\n\
    \        apply_node(node << 1 | 1, middle, right, query_left, query_right, value);\n\
    \    }\n\n    T get_node(int node, int left, int right, int pos, T inherited)\
    \ const {\n        const Node& current = _journal[node];\n        if (right -\
    \ left == 1) {\n            assert(current.has_value);\n            return Monoid::op(inherited,\
    \ current.value);\n        }\n        if (current.has_value) inherited = Monoid::op(inherited,\
    \ current.value);\n        int middle = (left + right) >> 1;\n        if (pos\
    \ < middle) return get_node(node << 1, left, middle, pos, std::move(inherited));\n\
    \        return get_node(node << 1 | 1, middle, right, pos, std::move(inherited));\n\
    \    }\n\n   public:\n    RollbackDualSegtree() { initialize(0); }\n    explicit\
    \ RollbackDualSegtree(int n) {\n        initialize(n);\n        if (n > 0) {\n\
    \            std::vector<T> values(n, Monoid::id());\n            build(1, 0,\
    \ n, values);\n        }\n    }\n\n    explicit RollbackDualSegtree(const std::vector<T>&\
    \ values) {\n        initialize(int(values.size()));\n        if (_n > 0) build(1,\
    \ 0, _n, values);\n    }\n\n    template <class U>\n        requires(!std::same_as<U,\
    \ T>)\n    explicit RollbackDualSegtree(const std::vector<U>& values) {\n    \
    \    initialize(int(values.size()));\n        if (_n > 0) build(1, 0, _n, values);\n\
    \    }\n\n    int size() const { return _n; }\n    bool empty() const { return\
    \ _n == 0; }\n    std::size_t node_count() const { return _journal.nodes.size();\
    \ }\n\n    void set(int pos, T value) {\n        assert(0 <= pos && pos < _n);\n\
    \        set_node(1, 0, _n, pos, std::move(value));\n    }\n    void set_inplace(int\
    \ pos, T value) { set(pos, std::move(value)); }\n\n    T get(int pos) const {\n\
    \        assert(0 <= pos && pos < _n);\n        return get_node(1, 0, _n, pos,\
    \ Monoid::id());\n    }\n    T operator[](int pos) const { return get(pos); }\n\
    \n    void apply(int pos, const T& value) { apply(pos, pos + 1, value); }\n  \
    \  void apply(int left, int right, const T& value) {\n        assert(0 <= left\
    \ && left <= right && right <= _n);\n        if (left != right) apply_node(1,\
    \ 0, _n, left, right, value);\n    }\n    void apply_inplace(int pos, const T&\
    \ value) { apply(pos, value); }\n    void apply_inplace(int left, int right, const\
    \ T& value) { apply(left, right, value); }\n\n    int snapshot() { return _journal.snapshot();\
    \ }\n    int snapshot_count() const { return _journal.snapshot_count(); }\n  \
    \  void reserve_snapshots(int count) { _journal.reserve_snapshots(count); }\n\
    \    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _n = 0; _journal.clear();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  - ds/detail/rollback_journal.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_dual_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
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
`m1une::monoid::IsMonoid`; composition order matches `DualSegtree`.

## Methods

Constructors and read-only methods follow `DualSegtree<Monoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const T& value)`, `void apply(int left, int right, const T& value)` | Composes an action at a point or on `[left, right)`. | $O(\log N)$ |
| `void apply_inplace(...)` | Aliases of `apply`. | $O(\log N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a tree node is saved only before its first mutation.

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
