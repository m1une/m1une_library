---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/rollback_dsu.hpp
    title: Rollback DSU
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_connectivity/all.hpp
    title: Dynamic Connectivity
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
    title: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dynamic_connectivity/offline_dynamic_connectivity.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"ds/dsu/rollback_dsu.hpp\"\n\n\n\n#line 7 \"ds/dsu/rollback_dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct RollbackDsu {\n   private:\n \
    \   struct HistoryEntry {\n        int first;\n        int first_value;\n    \
    \    int second;\n        int second_value;\n    };\n\n    int _n;\n    int _component_count;\n\
    \    std::vector<int> parent_or_size;\n    std::vector<HistoryEntry> history;\n\
    \n    static int check_size(int n) {\n        assert(0 <= n);\n        return\
    \ n;\n    }\n\n   public:\n    RollbackDsu() : RollbackDsu(0) {}\n\n    explicit\
    \ RollbackDsu(int n)\n        : _n(check_size(n)), _component_count(_n), parent_or_size(_n,\
    \ -1) {}\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int component_count() const {\n\
    \        return _component_count;\n    }\n\n    int history_size() const {\n \
    \       return int(history.size());\n    }\n\n    void reserve_history(int count)\
    \ {\n        assert(0 <= count);\n        history.reserve(count);\n    }\n\n \
    \   int leader(int vertex) const {\n        assert(0 <= vertex && vertex < _n);\n\
    \        while (parent_or_size[vertex] >= 0) vertex = parent_or_size[vertex];\n\
    \        return vertex;\n    }\n\n    bool same(int first, int second) const {\n\
    \        return leader(first) == leader(second);\n    }\n\n    int group_size(int\
    \ vertex) const {\n        return -parent_or_size[leader(vertex)];\n    }\n\n\
    \    int size(int vertex) const {\n        return group_size(vertex);\n    }\n\
    \n    bool merge(int first, int second) {\n        first = leader(first);\n  \
    \      second = leader(second);\n        if (first == second) {\n            history.push_back(HistoryEntry{-1,\
    \ 0, -1, 0});\n            return false;\n        }\n        if (-parent_or_size[first]\
    \ < -parent_or_size[second]) {\n            std::swap(first, second);\n      \
    \  }\n        history.push_back(HistoryEntry{\n            first, parent_or_size[first],\
    \ second, parent_or_size[second]\n        });\n        parent_or_size[first] +=\
    \ parent_or_size[second];\n        parent_or_size[second] = first;\n        _component_count--;\n\
    \        return true;\n    }\n\n    bool undo() {\n        if (history.empty())\
    \ return false;\n        const HistoryEntry entry = history.back();\n        history.pop_back();\n\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 10 \"ds/dynamic_connectivity/offline_dynamic_connectivity.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct OfflineDynamicConnectivity {\n\
    \   private:\n    struct Edge {\n        int u;\n        int v;\n        int begin;\n\
    \        int end;\n        bool alive;\n    };\n\n    struct Query {\n       \
    \ int u;\n        int v;\n        int time;\n    };\n\n    int _n;\n    int _time\
    \ = 0;\n    std::vector<Edge> _edges;\n    std::vector<Query> _queries;\n\n  \
    \  void dfs(\n        const std::vector<int>& offset,\n        const std::vector<std::pair<int,\
    \ int>>& stored_edges,\n        const std::vector<int>& query_at,\n        std::vector<bool>&\
    \ answer,\n        RollbackDsu& dsu,\n        int node,\n        int base\n  \
    \  ) const {\n        int snapshot = dsu.snapshot();\n        for (int i = offset[node];\
    \ i < offset[node + 1]; i++) {\n            auto [u, v] = stored_edges[i];\n \
    \           dsu.merge(u, v);\n        }\n        if (node >= base) {\n       \
    \     int query_id = query_at[node - base];\n            if (query_id != -1) {\n\
    \                const Query& query = _queries[query_id];\n                answer[query_id]\
    \ = dsu.same(query.u, query.v);\n            }\n        } else {\n           \
    \ dfs(offset, stored_edges, query_at, answer, dsu, 2 * node, base);\n        \
    \    dfs(offset, stored_edges, query_at, answer, dsu, 2 * node + 1, base);\n \
    \       }\n        dsu.rollback(snapshot);\n    }\n\n   public:\n    OfflineDynamicConnectivity()\
    \ : OfflineDynamicConnectivity(0) {}\n\n    explicit OfflineDynamicConnectivity(int\
    \ n) : _n(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n   \
    \     return _n;\n    }\n\n    int edge_count() const {\n        return int(_edges.size());\n\
    \    }\n\n    int query_count() const {\n        return int(_queries.size());\n\
    \    }\n\n    int operation_count() const {\n        return _time;\n    }\n\n\
    \    void reserve_edges(int count) {\n        assert(0 <= count);\n        _edges.reserve(count);\n\
    \    }\n\n    void reserve_queries(int count) {\n        assert(0 <= count);\n\
    \        _queries.reserve(count);\n    }\n\n    bool edge_alive(int edge_id) const\
    \ {\n        assert(0 <= edge_id && edge_id < int(_edges.size()));\n        return\
    \ _edges[edge_id].alive;\n    }\n\n    int add_edge(int u, int v) {\n        assert(0\
    \ <= u && u < _n);\n        assert(0 <= v && v < _n);\n        int edge_id = int(_edges.size());\n\
    \        _edges.push_back(Edge{u, v, _time, -1, true});\n        _time++;\n  \
    \      return edge_id;\n    }\n\n    bool erase_edge(int edge_id) {\n        assert(0\
    \ <= edge_id && edge_id < int(_edges.size()));\n        Edge& edge = _edges[edge_id];\n\
    \        if (!edge.alive) return false;\n        edge.end = _time;\n        edge.alive\
    \ = false;\n        _time++;\n        return true;\n    }\n\n    int add_query(int\
    \ u, int v) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v <\
    \ _n);\n        int query_id = int(_queries.size());\n        _queries.push_back(Query{u,\
    \ v, _time});\n        _time++;\n        return query_id;\n    }\n\n    std::vector<bool>\
    \ solve() const {\n        std::vector<bool> answer(_queries.size(), false);\n\
    \        if (_queries.empty()) return answer;\n        if (_edges.empty()) {\n\
    \            for (int query_id = 0; query_id < int(_queries.size()); query_id++)\
    \ {\n                answer[query_id] = _queries[query_id].u == _queries[query_id].v;\n\
    \            }\n            return answer;\n        }\n\n        int base = 1;\n\
    \        while (base < _time) base *= 2;\n        int node_count = 2 * base;\n\
    \        std::vector<int> count(node_count, 0);\n        for (const Edge& edge\
    \ : _edges) {\n            int end = edge.alive ? _time : edge.end;\n        \
    \    if (edge.begin < end && edge.u != edge.v) {\n                int left = edge.begin\
    \ + base;\n                int right = end + base;\n                while (left\
    \ < right) {\n                    if (left & 1) count[left++]++;\n           \
    \         if (right & 1) count[--right]++;\n                    left /= 2;\n \
    \                   right /= 2;\n                }\n            }\n        }\n\
    \        std::vector<int> offset(node_count + 1, 0);\n        for (int node =\
    \ 1; node < node_count; node++) offset[node + 1] = offset[node] + count[node];\n\
    \        std::vector<int> cursor = offset;\n        std::vector<std::pair<int,\
    \ int>> stored_edges(offset[node_count]);\n        for (const Edge& edge : _edges)\
    \ {\n            int end = edge.alive ? _time : edge.end;\n            if (edge.begin\
    \ >= end || edge.u == edge.v) continue;\n            int left = edge.begin + base;\n\
    \            int right = end + base;\n            while (left < right) {\n   \
    \             if (left & 1) stored_edges[cursor[left]++] = {edge.u, edge.v}, left++;\n\
    \                if (right & 1) --right, stored_edges[cursor[right]++] = {edge.u,\
    \ edge.v};\n                left /= 2;\n                right /= 2;\n        \
    \    }\n        }\n        std::vector<int> query_at(base, -1);\n        for (int\
    \ query_id = 0; query_id < int(_queries.size()); query_id++) {\n            query_at[_queries[query_id].time]\
    \ = query_id;\n        }\n        RollbackDsu dsu(_n);\n        dsu.reserve_history(int(std::min<std::size_t>(_n,\
    \ stored_edges.size())));\n        dfs(offset, stored_edges, query_at, answer,\
    \ dsu, 1, base);\n        return answer;\n    }\n};\n\n}  // namespace ds\n} \
    \ // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_OFFLINE_DYNAMIC_CONNECTIVITY_HPP\n#define M1UNE_OFFLINE_DYNAMIC_CONNECTIVITY_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"../dsu/rollback_dsu.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\nstruct OfflineDynamicConnectivity {\n   private:\n    struct Edge {\n\
    \        int u;\n        int v;\n        int begin;\n        int end;\n      \
    \  bool alive;\n    };\n\n    struct Query {\n        int u;\n        int v;\n\
    \        int time;\n    };\n\n    int _n;\n    int _time = 0;\n    std::vector<Edge>\
    \ _edges;\n    std::vector<Query> _queries;\n\n    void dfs(\n        const std::vector<int>&\
    \ offset,\n        const std::vector<std::pair<int, int>>& stored_edges,\n   \
    \     const std::vector<int>& query_at,\n        std::vector<bool>& answer,\n\
    \        RollbackDsu& dsu,\n        int node,\n        int base\n    ) const {\n\
    \        int snapshot = dsu.snapshot();\n        for (int i = offset[node]; i\
    \ < offset[node + 1]; i++) {\n            auto [u, v] = stored_edges[i];\n   \
    \         dsu.merge(u, v);\n        }\n        if (node >= base) {\n         \
    \   int query_id = query_at[node - base];\n            if (query_id != -1) {\n\
    \                const Query& query = _queries[query_id];\n                answer[query_id]\
    \ = dsu.same(query.u, query.v);\n            }\n        } else {\n           \
    \ dfs(offset, stored_edges, query_at, answer, dsu, 2 * node, base);\n        \
    \    dfs(offset, stored_edges, query_at, answer, dsu, 2 * node + 1, base);\n \
    \       }\n        dsu.rollback(snapshot);\n    }\n\n   public:\n    OfflineDynamicConnectivity()\
    \ : OfflineDynamicConnectivity(0) {}\n\n    explicit OfflineDynamicConnectivity(int\
    \ n) : _n(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n   \
    \     return _n;\n    }\n\n    int edge_count() const {\n        return int(_edges.size());\n\
    \    }\n\n    int query_count() const {\n        return int(_queries.size());\n\
    \    }\n\n    int operation_count() const {\n        return _time;\n    }\n\n\
    \    void reserve_edges(int count) {\n        assert(0 <= count);\n        _edges.reserve(count);\n\
    \    }\n\n    void reserve_queries(int count) {\n        assert(0 <= count);\n\
    \        _queries.reserve(count);\n    }\n\n    bool edge_alive(int edge_id) const\
    \ {\n        assert(0 <= edge_id && edge_id < int(_edges.size()));\n        return\
    \ _edges[edge_id].alive;\n    }\n\n    int add_edge(int u, int v) {\n        assert(0\
    \ <= u && u < _n);\n        assert(0 <= v && v < _n);\n        int edge_id = int(_edges.size());\n\
    \        _edges.push_back(Edge{u, v, _time, -1, true});\n        _time++;\n  \
    \      return edge_id;\n    }\n\n    bool erase_edge(int edge_id) {\n        assert(0\
    \ <= edge_id && edge_id < int(_edges.size()));\n        Edge& edge = _edges[edge_id];\n\
    \        if (!edge.alive) return false;\n        edge.end = _time;\n        edge.alive\
    \ = false;\n        _time++;\n        return true;\n    }\n\n    int add_query(int\
    \ u, int v) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v <\
    \ _n);\n        int query_id = int(_queries.size());\n        _queries.push_back(Query{u,\
    \ v, _time});\n        _time++;\n        return query_id;\n    }\n\n    std::vector<bool>\
    \ solve() const {\n        std::vector<bool> answer(_queries.size(), false);\n\
    \        if (_queries.empty()) return answer;\n        if (_edges.empty()) {\n\
    \            for (int query_id = 0; query_id < int(_queries.size()); query_id++)\
    \ {\n                answer[query_id] = _queries[query_id].u == _queries[query_id].v;\n\
    \            }\n            return answer;\n        }\n\n        int base = 1;\n\
    \        while (base < _time) base *= 2;\n        int node_count = 2 * base;\n\
    \        std::vector<int> count(node_count, 0);\n        for (const Edge& edge\
    \ : _edges) {\n            int end = edge.alive ? _time : edge.end;\n        \
    \    if (edge.begin < end && edge.u != edge.v) {\n                int left = edge.begin\
    \ + base;\n                int right = end + base;\n                while (left\
    \ < right) {\n                    if (left & 1) count[left++]++;\n           \
    \         if (right & 1) count[--right]++;\n                    left /= 2;\n \
    \                   right /= 2;\n                }\n            }\n        }\n\
    \        std::vector<int> offset(node_count + 1, 0);\n        for (int node =\
    \ 1; node < node_count; node++) offset[node + 1] = offset[node] + count[node];\n\
    \        std::vector<int> cursor = offset;\n        std::vector<std::pair<int,\
    \ int>> stored_edges(offset[node_count]);\n        for (const Edge& edge : _edges)\
    \ {\n            int end = edge.alive ? _time : edge.end;\n            if (edge.begin\
    \ >= end || edge.u == edge.v) continue;\n            int left = edge.begin + base;\n\
    \            int right = end + base;\n            while (left < right) {\n   \
    \             if (left & 1) stored_edges[cursor[left]++] = {edge.u, edge.v}, left++;\n\
    \                if (right & 1) --right, stored_edges[cursor[right]++] = {edge.u,\
    \ edge.v};\n                left /= 2;\n                right /= 2;\n        \
    \    }\n        }\n        std::vector<int> query_at(base, -1);\n        for (int\
    \ query_id = 0; query_id < int(_queries.size()); query_id++) {\n            query_at[_queries[query_id].time]\
    \ = query_id;\n        }\n        RollbackDsu dsu(_n);\n        dsu.reserve_history(int(std::min<std::size_t>(_n,\
    \ stored_edges.size())));\n        dfs(offset, stored_edges, query_at, answer,\
    \ dsu, 1, base);\n        return answer;\n    }\n};\n\n}  // namespace ds\n} \
    \ // namespace m1une\n\n#endif  // M1UNE_OFFLINE_DYNAMIC_CONNECTIVITY_HPP\n"
  dependsOn:
  - ds/dsu/rollback_dsu.hpp
  isVerificationFile: false
  path: ds/dynamic_connectivity/offline_dynamic_connectivity.hpp
  requiredBy:
  - ds/dynamic_connectivity/all.hpp
  timestamp: '2026-07-11 19:52:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
documentation_of: ds/dynamic_connectivity/offline_dynamic_connectivity.hpp
layout: document
title: Offline Dynamic Connectivity
---

## Overview

`OfflineDynamicConnectivity` records edge insertions, edge deletions, and
connectivity queries in chronological order, then answers every query together
with `solve()`.

Each edge lifetime is inserted into a segment tree over time. `RollbackDsu`
traverses that tree, adding exactly the edges active at each query and restoring
its previous state when leaving a segment. Segment-tree edge lists use one
compact contiguous allocation instead of one allocation per node.

Parallel edges and self-loops are supported. Every insertion returns a distinct
edge id, and deletion refers to that id.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `OfflineDynamicConnectivity()` | Creates an empty graph. | `O(1)` |
| `OfflineDynamicConnectivity(int n)` | Creates `n` vertices. | `O(1)` |
| `int size() const` | Returns the number of vertices. | `O(1)` |
| `int edge_count() const` | Returns the number of inserted edge ids. | `O(1)` |
| `int query_count() const` | Returns the number of recorded queries. | `O(1)` |
| `int operation_count() const` | Returns the number of recorded operations. | `O(1)` |
| `void reserve_edges(int count)` | Reserves storage for inserted edges. | `O(L)` when reallocation occurs |
| `void reserve_queries(int count)` | Reserves storage for connectivity queries. | `O(K)` when reallocation occurs |
| `bool edge_alive(int id) const` | Returns whether edge `id` is active at the end of the log. | `O(1)` |
| `int add_edge(int u, int v)` | Records an insertion and returns its edge id. | Amortized `O(1)` |
| `bool erase_edge(int id)` | Records deletion of an active edge. Returns false if already erased. | `O(1)` |
| `int add_query(int u, int v)` | Records a query and returns its query id. | Amortized `O(1)` |
| `vector<bool> solve() const` | Returns answers in query-id order. | `O((Q + L log Q) log N)` |

Here `Q` is the number of recorded operations and `L` is the number of inserted
edges. The segment-tree storage uses `O(Q + L log Q)` memory. The extra
`log N` factor comes from rollback DSU leaders, which use union by size without
path compression.

Calling `solve()` does not modify the recorded log, so it may be called again.
More operations can also be appended afterward and solved as a longer log.

## Example

```cpp
#include "ds/dynamic_connectivity/offline_dynamic_connectivity.hpp"
#include <iostream>

int main() {
    m1une::ds::OfflineDynamicConnectivity graph(3);
    int e01 = graph.add_edge(0, 1);
    int first = graph.add_query(0, 2);
    int e12 = graph.add_edge(1, 2);
    int second = graph.add_query(0, 2);
    graph.erase_edge(e01);
    int third = graph.add_query(0, 2);

    std::vector<bool> answer = graph.solve();
    std::cout << answer[first] << '\n';   // 0
    std::cout << answer[second] << '\n';  // 1
    std::cout << answer[third] << '\n';   // 0

    (void)e12;
}
```
