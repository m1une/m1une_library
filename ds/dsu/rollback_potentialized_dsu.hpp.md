---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/rollback_potentialized_dsu.test.cpp
    title: verify/ds/dsu/rollback_potentialized_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/rollback_potentialized_dsu.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <concepts>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
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
    \ namespace m1une\n\n\n#line 11 \"ds/dsu/rollback_potentialized_dsu.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsGroup Group>\n\
    \    requires std::equality_comparable<typename Group::value_type>\nstruct RollbackPotentializedDsu\
    \ {\n    using T = typename Group::value_type;\n\n   private:\n    struct HistoryEntry\
    \ {\n        int first;\n        int first_value;\n        int second;\n     \
    \   int second_value;\n        T second_diff;\n\n        HistoryEntry(int first_index,\
    \ int first_parent, int second_index,\n                     int second_parent,\
    \ T diff)\n            : first(first_index),\n              first_value(first_parent),\n\
    \              second(second_index),\n              second_value(second_parent),\n\
    \              second_diff(std::move(diff)) {}\n    };\n\n    int _n;\n    int\
    \ _component_count;\n    std::vector<int> _parent_or_size;\n    std::vector<T>\
    \ _diff_to_parent;\n    std::vector<HistoryEntry> _history;\n\n    static int\
    \ check_size(int n) {\n        assert(0 <= n);\n        return n;\n    }\n\n \
    \   std::pair<int, T> leader_and_potential(int vertex) const {\n        assert(0\
    \ <= vertex && vertex < _n);\n        T result = Group::id();\n        while (_parent_or_size[vertex]\
    \ >= 0) {\n            result = Group::op(_diff_to_parent[vertex], result);\n\
    \            vertex = _parent_or_size[vertex];\n        }\n        return {vertex,\
    \ std::move(result)};\n    }\n\n   public:\n    RollbackPotentializedDsu() : RollbackPotentializedDsu(0)\
    \ {}\n\n    explicit RollbackPotentializedDsu(int n)\n        : _n(check_size(n)),\n\
    \          _component_count(_n),\n          _parent_or_size(_n, -1),\n       \
    \   _diff_to_parent(_n, Group::id()) {}\n\n    int size() const { return _n; }\n\
    \    bool empty() const { return _n == 0; }\n    int component_count() const {\
    \ return _component_count; }\n    int history_size() const { return int(_history.size());\
    \ }\n\n    void reserve_history(int count) {\n        assert(0 <= count);\n  \
    \      _history.reserve(count);\n    }\n\n    int leader(int vertex) const {\n\
    \        return leader_and_potential(vertex).first;\n    }\n\n    bool same(int\
    \ first, int second) const {\n        return leader(first) == leader(second);\n\
    \    }\n\n    int group_size(int vertex) const {\n        return -_parent_or_size[leader(vertex)];\n\
    \    }\n\n    int size(int vertex) const { return group_size(vertex); }\n\n  \
    \  T potential(int vertex) const {\n        return leader_and_potential(vertex).second;\n\
    \    }\n\n    T diff(int first, int second) const {\n        assert(same(first,\
    \ second));\n        return Group::op(Group::inv(potential(first)), potential(second));\n\
    \    }\n\n    int parent_or_size(int vertex) const {\n        assert(0 <= vertex\
    \ && vertex < _n);\n        return _parent_or_size[vertex];\n    }\n\n    bool\
    \ merge(int first, int second, const T& difference) {\n        auto [first_root,\
    \ first_potential] = leader_and_potential(first);\n        auto [second_root,\
    \ second_potential] = leader_and_potential(second);\n        if (first_root ==\
    \ second_root) {\n            _history.emplace_back(-1, 0, -1, 0, Group::id());\n\
    \            return Group::op(Group::inv(first_potential), second_potential) ==\
    \ difference;\n        }\n\n        T second_from_first = Group::op(\n       \
    \     Group::op(first_potential, difference),\n            Group::inv(second_potential)\n\
    \        );\n        if (-_parent_or_size[first_root] < -_parent_or_size[second_root])\
    \ {\n            std::swap(first_root, second_root);\n            second_from_first\
    \ = Group::inv(second_from_first);\n        }\n\n        _history.emplace_back(\n\
    \            first_root, _parent_or_size[first_root], second_root,\n         \
    \   _parent_or_size[second_root], _diff_to_parent[second_root]\n        );\n \
    \       _parent_or_size[first_root] += _parent_or_size[second_root];\n       \
    \ _parent_or_size[second_root] = first_root;\n        _diff_to_parent[second_root]\
    \ = std::move(second_from_first);\n        --_component_count;\n        return\
    \ true;\n    }\n\n    bool undo() {\n        if (_history.empty()) return false;\n\
    \        HistoryEntry entry = std::move(_history.back());\n        _history.pop_back();\n\
    \        if (entry.first == -1) return true;\n        _parent_or_size[entry.first]\
    \ = entry.first_value;\n        _parent_or_size[entry.second] = entry.second_value;\n\
    \        _diff_to_parent[entry.second] = std::move(entry.second_diff);\n     \
    \   ++_component_count;\n        return true;\n    }\n\n    int snapshot() const\
    \ { return history_size(); }\n\n    void rollback(int state) {\n        assert(0\
    \ <= state && state <= history_size());\n        while (history_size() > state)\
    \ undo();\n    }\n\n    std::vector<std::vector<int>> groups() const {\n     \
    \   std::vector<int> leaders(_n);\n        std::vector<int> sizes(_n);\n     \
    \   for (int vertex = 0; vertex < _n; ++vertex) {\n            leaders[vertex]\
    \ = leader(vertex);\n            ++sizes[leaders[vertex]];\n        }\n      \
    \  std::vector<std::vector<int>> result(_n);\n        for (int vertex = 0; vertex\
    \ < _n; ++vertex) {\n            result[vertex].reserve(sizes[vertex]);\n    \
    \    }\n        for (int vertex = 0; vertex < _n; ++vertex) {\n            result[leaders[vertex]].push_back(vertex);\n\
    \        }\n        result.erase(\n            std::remove_if(\n             \
    \   result.begin(), result.end(),\n                [](const std::vector<int>&\
    \ group) { return group.empty(); }\n            ),\n            result.end()\n\
    \        );\n        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_DS_DSU_ROLLBACK_POTENTIALIZED_DSU_HPP\n#define M1UNE_DS_DSU_ROLLBACK_POTENTIALIZED_DSU_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"../../monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsGroup Group>\n    requires\
    \ std::equality_comparable<typename Group::value_type>\nstruct RollbackPotentializedDsu\
    \ {\n    using T = typename Group::value_type;\n\n   private:\n    struct HistoryEntry\
    \ {\n        int first;\n        int first_value;\n        int second;\n     \
    \   int second_value;\n        T second_diff;\n\n        HistoryEntry(int first_index,\
    \ int first_parent, int second_index,\n                     int second_parent,\
    \ T diff)\n            : first(first_index),\n              first_value(first_parent),\n\
    \              second(second_index),\n              second_value(second_parent),\n\
    \              second_diff(std::move(diff)) {}\n    };\n\n    int _n;\n    int\
    \ _component_count;\n    std::vector<int> _parent_or_size;\n    std::vector<T>\
    \ _diff_to_parent;\n    std::vector<HistoryEntry> _history;\n\n    static int\
    \ check_size(int n) {\n        assert(0 <= n);\n        return n;\n    }\n\n \
    \   std::pair<int, T> leader_and_potential(int vertex) const {\n        assert(0\
    \ <= vertex && vertex < _n);\n        T result = Group::id();\n        while (_parent_or_size[vertex]\
    \ >= 0) {\n            result = Group::op(_diff_to_parent[vertex], result);\n\
    \            vertex = _parent_or_size[vertex];\n        }\n        return {vertex,\
    \ std::move(result)};\n    }\n\n   public:\n    RollbackPotentializedDsu() : RollbackPotentializedDsu(0)\
    \ {}\n\n    explicit RollbackPotentializedDsu(int n)\n        : _n(check_size(n)),\n\
    \          _component_count(_n),\n          _parent_or_size(_n, -1),\n       \
    \   _diff_to_parent(_n, Group::id()) {}\n\n    int size() const { return _n; }\n\
    \    bool empty() const { return _n == 0; }\n    int component_count() const {\
    \ return _component_count; }\n    int history_size() const { return int(_history.size());\
    \ }\n\n    void reserve_history(int count) {\n        assert(0 <= count);\n  \
    \      _history.reserve(count);\n    }\n\n    int leader(int vertex) const {\n\
    \        return leader_and_potential(vertex).first;\n    }\n\n    bool same(int\
    \ first, int second) const {\n        return leader(first) == leader(second);\n\
    \    }\n\n    int group_size(int vertex) const {\n        return -_parent_or_size[leader(vertex)];\n\
    \    }\n\n    int size(int vertex) const { return group_size(vertex); }\n\n  \
    \  T potential(int vertex) const {\n        return leader_and_potential(vertex).second;\n\
    \    }\n\n    T diff(int first, int second) const {\n        assert(same(first,\
    \ second));\n        return Group::op(Group::inv(potential(first)), potential(second));\n\
    \    }\n\n    int parent_or_size(int vertex) const {\n        assert(0 <= vertex\
    \ && vertex < _n);\n        return _parent_or_size[vertex];\n    }\n\n    bool\
    \ merge(int first, int second, const T& difference) {\n        auto [first_root,\
    \ first_potential] = leader_and_potential(first);\n        auto [second_root,\
    \ second_potential] = leader_and_potential(second);\n        if (first_root ==\
    \ second_root) {\n            _history.emplace_back(-1, 0, -1, 0, Group::id());\n\
    \            return Group::op(Group::inv(first_potential), second_potential) ==\
    \ difference;\n        }\n\n        T second_from_first = Group::op(\n       \
    \     Group::op(first_potential, difference),\n            Group::inv(second_potential)\n\
    \        );\n        if (-_parent_or_size[first_root] < -_parent_or_size[second_root])\
    \ {\n            std::swap(first_root, second_root);\n            second_from_first\
    \ = Group::inv(second_from_first);\n        }\n\n        _history.emplace_back(\n\
    \            first_root, _parent_or_size[first_root], second_root,\n         \
    \   _parent_or_size[second_root], _diff_to_parent[second_root]\n        );\n \
    \       _parent_or_size[first_root] += _parent_or_size[second_root];\n       \
    \ _parent_or_size[second_root] = first_root;\n        _diff_to_parent[second_root]\
    \ = std::move(second_from_first);\n        --_component_count;\n        return\
    \ true;\n    }\n\n    bool undo() {\n        if (_history.empty()) return false;\n\
    \        HistoryEntry entry = std::move(_history.back());\n        _history.pop_back();\n\
    \        if (entry.first == -1) return true;\n        _parent_or_size[entry.first]\
    \ = entry.first_value;\n        _parent_or_size[entry.second] = entry.second_value;\n\
    \        _diff_to_parent[entry.second] = std::move(entry.second_diff);\n     \
    \   ++_component_count;\n        return true;\n    }\n\n    int snapshot() const\
    \ { return history_size(); }\n\n    void rollback(int state) {\n        assert(0\
    \ <= state && state <= history_size());\n        while (history_size() > state)\
    \ undo();\n    }\n\n    std::vector<std::vector<int>> groups() const {\n     \
    \   std::vector<int> leaders(_n);\n        std::vector<int> sizes(_n);\n     \
    \   for (int vertex = 0; vertex < _n; ++vertex) {\n            leaders[vertex]\
    \ = leader(vertex);\n            ++sizes[leaders[vertex]];\n        }\n      \
    \  std::vector<std::vector<int>> result(_n);\n        for (int vertex = 0; vertex\
    \ < _n; ++vertex) {\n            result[vertex].reserve(sizes[vertex]);\n    \
    \    }\n        for (int vertex = 0; vertex < _n; ++vertex) {\n            result[leaders[vertex]].push_back(vertex);\n\
    \        }\n        result.erase(\n            std::remove_if(\n             \
    \   result.begin(), result.end(),\n                [](const std::vector<int>&\
    \ group) { return group.empty(); }\n            ),\n            result.end()\n\
    \        );\n        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_DS_DSU_ROLLBACK_POTENTIALIZED_DSU_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/dsu/rollback_potentialized_dsu.hpp
  requiredBy: []
  timestamp: '2026-08-12 04:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dsu/rollback_potentialized_dsu.test.cpp
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/dsu/rollback_potentialized_dsu.hpp
layout: document
title: Rollback Potentialized DSU
---

## Overview

`RollbackPotentializedDsu<Group>` is a weighted Union-Find that can undo merge
constraints. It supports possibly noncommutative groups and uses union by size
without path compression, so every tree has logarithmic depth and undo is
constant time.

For `merge(a, b, w)`, the stored constraint is
`diff(a, b) == w`, where
`diff(a, b) = Group::op(Group::inv(potential(a)), potential(b))`.
The group value type must be equality comparable so a constraint inside an
existing component can be checked.

Every merge call adds one history entry, including a redundant or contradictory
constraint. Thus one `undo()` always corresponds to one `merge()` call.
Snapshots are valid only on the current history path.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `RollbackPotentializedDsu()` | Constructs an empty DSU. | $O(1)$ |
| `explicit RollbackPotentializedDsu(int n)` | Constructs `n` singleton components. | $O(N)$ |
| `int size() const`, `bool empty() const` | Returns the element count or whether it is zero. | $O(1)$ |
| `int component_count() const` | Returns the current component count. | $O(1)$ |
| `int leader(int vertex) const` | Returns the component representative. | $O(\log N)$ |
| `bool same(int first, int second) const` | Tests connectivity. | $O(\log N)$ |
| `int group_size(int vertex) const`, `int size(int vertex) const` | Returns the component size. | $O(\log N)$ |
| `T potential(int vertex) const` | Returns the root-relative potential. | $O(\log N)$ |
| `T diff(int first, int second) const` | Returns the potential difference; requires connectivity. | $O(\log N)$ |
| `int parent_or_size(int vertex) const` | Returns the internal parent-or-negative-size entry. | $O(1)$ |
| `bool merge(int first, int second, const T& difference)` | Adds `diff(first, second) == difference`; returns whether the constraints are consistent. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the current history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves merge history. | $O(H)$ |
| `bool undo()` | Undoes the latest merge call. | $O(1)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(H - state)$ |
| `std::vector<std::vector<int>> groups() const` | Materializes all components. | $O(N \log N)$ |

Indices must lie in `[0, size())`; rollback states must lie in
`[0, history_size()]`.

## Example

```cpp
#include "ds/dsu/rollback_potentialized_dsu.hpp"
#include "monoid/add.hpp"

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackPotentializedDsu<Add> dsu(3);
dsu.merge(0, 1, 3);
int state = dsu.snapshot();
dsu.merge(1, 2, 4);
assert(dsu.diff(0, 2) == 7);
dsu.rollback(state);
assert(!dsu.same(0, 2));
```
