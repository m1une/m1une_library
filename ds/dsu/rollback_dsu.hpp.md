---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_connectivity/all.hpp
    title: Dynamic Connectivity
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_connectivity/offline_dynamic_connectivity.hpp
    title: Offline Dynamic Connectivity
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/rollback_dsu.test.cpp
    title: verify/ds/dsu/rollback_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
    title: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/rollback_dsu.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    struct RollbackDsu {\n   private:\n    struct HistoryEntry {\n        int first;\n\
    \        int first_value;\n        int second;\n        int second_value;\n  \
    \  };\n\n    int _n;\n    int _component_count;\n    std::vector<int> parent_or_size;\n\
    \    std::vector<HistoryEntry> history;\n\n    static int check_size(int n) {\n\
    \        assert(0 <= n);\n        return n;\n    }\n\n   public:\n    RollbackDsu()\
    \ : RollbackDsu(0) {}\n\n    explicit RollbackDsu(int n)\n        : _n(check_size(n)),\
    \ _component_count(_n), parent_or_size(_n, -1) {}\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    int component_count() const {\n        return _component_count;\n\
    \    }\n\n    int history_size() const {\n        return int(history.size());\n\
    \    }\n\n    void reserve_history(int count) {\n        assert(0 <= count);\n\
    \        history.reserve(count);\n    }\n\n    int leader(int vertex) const {\n\
    \        assert(0 <= vertex && vertex < _n);\n        while (parent_or_size[vertex]\
    \ >= 0) vertex = parent_or_size[vertex];\n        return vertex;\n    }\n\n  \
    \  bool same(int first, int second) const {\n        return leader(first) == leader(second);\n\
    \    }\n\n    int group_size(int vertex) const {\n        return -parent_or_size[leader(vertex)];\n\
    \    }\n\n    int size(int vertex) const {\n        return group_size(vertex);\n\
    \    }\n\n    bool merge(int first, int second) {\n        first = leader(first);\n\
    \        second = leader(second);\n        if (first == second) {\n          \
    \  history.push_back(HistoryEntry{-1, 0, -1, 0});\n            return false;\n\
    \        }\n        if (-parent_or_size[first] < -parent_or_size[second]) {\n\
    \            std::swap(first, second);\n        }\n        history.push_back(HistoryEntry{\n\
    \            first, parent_or_size[first], second, parent_or_size[second]\n  \
    \      });\n        parent_or_size[first] += parent_or_size[second];\n       \
    \ parent_or_size[second] = first;\n        _component_count--;\n        return\
    \ true;\n    }\n\n    bool undo() {\n        if (history.empty()) return false;\n\
    \        const HistoryEntry entry = history.back();\n        history.pop_back();\n\
    \        if (entry.first == -1) return true;\n        parent_or_size[entry.first]\
    \ = entry.first_value;\n        parent_or_size[entry.second] = entry.second_value;\n\
    \        _component_count++;\n        return true;\n    }\n\n    int snapshot()\
    \ const {\n        return history_size();\n    }\n\n    void rollback(int state)\
    \ {\n        assert(0 <= state && state <= history_size());\n        while (history_size()\
    \ > state) undo();\n    }\n\n    std::vector<std::vector<int>> groups() const\
    \ {\n        std::vector<int> leader_buffer(_n);\n        std::vector<int> group_sizes(_n,\
    \ 0);\n        for (int vertex = 0; vertex < _n; vertex++) {\n            leader_buffer[vertex]\
    \ = leader(vertex);\n            group_sizes[leader_buffer[vertex]]++;\n     \
    \   }\n        std::vector<std::vector<int>> result(_n);\n        for (int vertex\
    \ = 0; vertex < _n; vertex++) {\n            result[vertex].reserve(group_sizes[vertex]);\n\
    \        }\n        for (int vertex = 0; vertex < _n; vertex++) {\n          \
    \  result[leader_buffer[vertex]].push_back(vertex);\n        }\n        result.erase(\n\
    \            std::remove_if(\n                result.begin(), result.end(),\n\
    \                [](const std::vector<int>& group) { return group.empty(); }\n\
    \            ),\n            result.end()\n        );\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ROLLBACK_DSU_HPP\n#define M1UNE_ROLLBACK_DSU_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ ds {\n\nstruct RollbackDsu {\n   private:\n    struct HistoryEntry {\n     \
    \   int first;\n        int first_value;\n        int second;\n        int second_value;\n\
    \    };\n\n    int _n;\n    int _component_count;\n    std::vector<int> parent_or_size;\n\
    \    std::vector<HistoryEntry> history;\n\n    static int check_size(int n) {\n\
    \        assert(0 <= n);\n        return n;\n    }\n\n   public:\n    RollbackDsu()\
    \ : RollbackDsu(0) {}\n\n    explicit RollbackDsu(int n)\n        : _n(check_size(n)),\
    \ _component_count(_n), parent_or_size(_n, -1) {}\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    int component_count() const {\n        return _component_count;\n\
    \    }\n\n    int history_size() const {\n        return int(history.size());\n\
    \    }\n\n    void reserve_history(int count) {\n        assert(0 <= count);\n\
    \        history.reserve(count);\n    }\n\n    int leader(int vertex) const {\n\
    \        assert(0 <= vertex && vertex < _n);\n        while (parent_or_size[vertex]\
    \ >= 0) vertex = parent_or_size[vertex];\n        return vertex;\n    }\n\n  \
    \  bool same(int first, int second) const {\n        return leader(first) == leader(second);\n\
    \    }\n\n    int group_size(int vertex) const {\n        return -parent_or_size[leader(vertex)];\n\
    \    }\n\n    int size(int vertex) const {\n        return group_size(vertex);\n\
    \    }\n\n    bool merge(int first, int second) {\n        first = leader(first);\n\
    \        second = leader(second);\n        if (first == second) {\n          \
    \  history.push_back(HistoryEntry{-1, 0, -1, 0});\n            return false;\n\
    \        }\n        if (-parent_or_size[first] < -parent_or_size[second]) {\n\
    \            std::swap(first, second);\n        }\n        history.push_back(HistoryEntry{\n\
    \            first, parent_or_size[first], second, parent_or_size[second]\n  \
    \      });\n        parent_or_size[first] += parent_or_size[second];\n       \
    \ parent_or_size[second] = first;\n        _component_count--;\n        return\
    \ true;\n    }\n\n    bool undo() {\n        if (history.empty()) return false;\n\
    \        const HistoryEntry entry = history.back();\n        history.pop_back();\n\
    \        if (entry.first == -1) return true;\n        parent_or_size[entry.first]\
    \ = entry.first_value;\n        parent_or_size[entry.second] = entry.second_value;\n\
    \        _component_count++;\n        return true;\n    }\n\n    int snapshot()\
    \ const {\n        return history_size();\n    }\n\n    void rollback(int state)\
    \ {\n        assert(0 <= state && state <= history_size());\n        while (history_size()\
    \ > state) undo();\n    }\n\n    std::vector<std::vector<int>> groups() const\
    \ {\n        std::vector<int> leader_buffer(_n);\n        std::vector<int> group_sizes(_n,\
    \ 0);\n        for (int vertex = 0; vertex < _n; vertex++) {\n            leader_buffer[vertex]\
    \ = leader(vertex);\n            group_sizes[leader_buffer[vertex]]++;\n     \
    \   }\n        std::vector<std::vector<int>> result(_n);\n        for (int vertex\
    \ = 0; vertex < _n; vertex++) {\n            result[vertex].reserve(group_sizes[vertex]);\n\
    \        }\n        for (int vertex = 0; vertex < _n; vertex++) {\n          \
    \  result[leader_buffer[vertex]].push_back(vertex);\n        }\n        result.erase(\n\
    \            std::remove_if(\n                result.begin(), result.end(),\n\
    \                [](const std::vector<int>& group) { return group.empty(); }\n\
    \            ),\n            result.end()\n        );\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_ROLLBACK_DSU_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/dsu/rollback_dsu.hpp
  requiredBy:
  - ds/dynamic_connectivity/offline_dynamic_connectivity.hpp
  - ds/dynamic_connectivity/all.hpp
  timestamp: '2026-07-11 19:52:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
  - verify/ds/dsu/rollback_dsu.test.cpp
documentation_of: ds/dsu/rollback_dsu.hpp
layout: document
title: Rollback DSU
---

## Overview

`RollbackDsu` maintains a partition under merges and can restore any earlier
snapshot on the current history path. It is useful for divide-and-conquer over
time, segment trees over query intervals, version trees, and offline dynamic
connectivity.

Union by size keeps each parent chain logarithmic. Path compression is
intentionally omitted because it would mutate an unbounded number of entries
that then need to be logged.

Every `merge` call appends exactly one history entry. A redundant merge appends
a no-op entry and returns `false`, so one call to `undo()` always reverses one
call to `merge()`.

## API

```cpp
struct RollbackDsu {
    RollbackDsu();
    explicit RollbackDsu(int n);

    int size() const;
    bool empty() const;
    int component_count() const;
    int history_size() const;
    void reserve_history(int count);

    int leader(int vertex) const;
    bool same(int first, int second) const;
    int group_size(int vertex) const;
    int size(int vertex) const;
    bool merge(int first, int second);

    bool undo();
    int snapshot() const;
    void rollback(int state);
    std::vector<std::vector<int>> groups() const;
};
```

| Method | Description | Complexity |
| --- | --- | --- |
| `RollbackDsu()` | Creates an empty DSU. | $O(1)$ |
| `RollbackDsu(n)` | Creates `n` singleton sets. | $O(N)$ |
| `size()` | Returns the number of elements. | $O(1)$ |
| `empty()` | Returns whether there are no elements. | $O(1)$ |
| `component_count()` | Returns the current number of sets. | $O(1)$ |
| `history_size()` | Returns the number of recorded merge calls. | $O(1)$ |
| `reserve_history(count)` | Reserves history capacity. | $O(H)$ if reallocation occurs |
| `leader(v)` | Returns the representative containing `v`. | $O(\log N)$ |
| `same(u, v)` | Returns whether `u` and `v` are connected. | $O(\log N)$ |
| `group_size(v)`, `size(v)` | Returns the size of the set containing `v`. | $O(\log N)$ |
| `merge(u, v)` | Records one operation and merges the sets if distinct; returns whether the partition changed. | $O(\log N)$ amortized for history growth |
| `undo()` | Reverses the most recent merge call; returns `false` when history is empty. | $O(1)$ |
| `snapshot()` | Returns the current history position. | $O(1)$ |
| `rollback(state)` | Restores a previously returned snapshot on the current history path. | $O(H - state)$ |
| `groups()` | Materializes every current set. | $O(N \log N)$ |

Indices must lie in `[0, size())`. A rollback state must lie between `0` and
the current `history_size()`. Rolling forward to a discarded state is not
supported. Query methods are `const` and never change the represented state.

The DSU stores $O(N + H)$ integers, where `H` is the current history length.

## Example

```cpp
#include "ds/dsu/rollback_dsu.hpp"

#include <iostream>

int main() {
    m1une::ds::RollbackDsu dsu(4);
    dsu.merge(0, 1);
    int checkpoint = dsu.snapshot();

    dsu.merge(1, 2);
    std::cout << dsu.same(0, 2) << "\n";  // 1

    dsu.rollback(checkpoint);
    std::cout << dsu.same(0, 2) << "\n";  // 0
    std::cout << dsu.component_count() << "\n";  // 3
}
```
