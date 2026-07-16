---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/incremental_scc.test.cpp
    title: verify/graph/incremental_scc.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/incremental_scc.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using\
    \ cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n   \
    \ bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true)\
    \ {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ =\
    \ true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\
    \n    int other(int v) const {\n        assert(v == from || v == to);\n      \
    \  return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph\
    \ {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>> _g;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n   public:\n\
    \    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
    \ _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int edge_count() const {\n        return _edge_count;\n    }\n\n    int add_vertex()\
    \ {\n        _g.emplace_back();\n        return _n++;\n    }\n\n    int add_directed_edge(int\
    \ from, int to, T cost = T(1)) {\n        assert(0 <= from && from < _n);\n  \
    \      assert(0 <= to && to < _n);\n        int id = _edge_count++;\n        int\
    \ idx = int(_g[from].size());\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({from,\
    \ idx});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost =\
    \ T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     _g[u].push_back(edge_type(u, v, cost, id));\n        int v_idx = int(_g[v].size());\n\
    \        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({u, u_idx});\n        _edge_positions.back().push_back({v,\
    \ v_idx});\n        return id;\n    }\n\n    void set_edge_alive(int id, bool\
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (auto [v,\
    \ idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n     \
    \   }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < _edge_count);\n        assert(!_edge_positions[id].empty());\n        auto\
    \ [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n    }\n\
    \n    const std::vector<edge_type>& operator[](int v) const {\n        assert(0\
    \ <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 11 \"graph/incremental_scc.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nnamespace incremental_scc_detail {\n\nstruct EdgeEvent {\n    int\
    \ id;\n    int from;\n    int to;\n};\n\ninline std::vector<int> component_ids(\n\
    \    int vertex_count,\n    const std::vector<EdgeEvent>& edges,\n    int time\n\
    ) {\n    std::vector<int> begin(vertex_count + 1, 0);\n    std::vector<int> reverse_begin(vertex_count\
    \ + 1, 0);\n    int edge_count = 0;\n    for (const EdgeEvent& edge : edges) {\n\
    \        if (edge.id >= time) continue;\n        begin[edge.from + 1]++;\n   \
    \     reverse_begin[edge.to + 1]++;\n        edge_count++;\n    }\n    for (int\
    \ vertex = 0; vertex < vertex_count; vertex++) {\n        begin[vertex + 1] +=\
    \ begin[vertex];\n        reverse_begin[vertex + 1] += reverse_begin[vertex];\n\
    \    }\n\n    std::vector<int> adjacency(edge_count);\n    std::vector<int> reverse_adjacency(edge_count);\n\
    \    std::vector<int> cursor = begin;\n    std::vector<int> reverse_cursor = reverse_begin;\n\
    \    for (const EdgeEvent& edge : edges) {\n        if (edge.id >= time) continue;\n\
    \        adjacency[cursor[edge.from]++] = edge.to;\n        reverse_adjacency[reverse_cursor[edge.to]++]\
    \ = edge.from;\n    }\n    std::vector<int>().swap(cursor);\n    std::vector<int>().swap(reverse_cursor);\n\
    \n    std::vector<char> visited(vertex_count, false);\n    std::vector<int> next_position(begin.begin(),\
    \ begin.end() - 1);\n    std::vector<int> order;\n    order.reserve(vertex_count);\n\
    \    std::vector<int> stack;\n    for (int start = 0; start < vertex_count; start++)\
    \ {\n        if (visited[start]) continue;\n        visited[start] = true;\n \
    \       stack.push_back(start);\n        while (!stack.empty()) {\n          \
    \  const int vertex = stack.back();\n            int& position = next_position[vertex];\n\
    \            if (position < begin[vertex + 1]) {\n                const int to\
    \ = adjacency[position++];\n                if (!visited[to]) {\n            \
    \        visited[to] = true;\n                    stack.push_back(to);\n     \
    \           }\n            } else {\n                order.push_back(vertex);\n\
    \                stack.pop_back();\n            }\n        }\n    }\n\n    std::vector<int>\
    \ component(vertex_count, -1);\n    int component_count = 0;\n    for (auto iterator\
    \ = order.rbegin(); iterator != order.rend(); ++iterator) {\n        const int\
    \ start = *iterator;\n        if (component[start] != -1) continue;\n        component[start]\
    \ = component_count;\n        stack.push_back(start);\n        while (!stack.empty())\
    \ {\n            const int vertex = stack.back();\n            stack.pop_back();\n\
    \            for (int position = reverse_begin[vertex];\n                 position\
    \ < reverse_begin[vertex + 1]; position++) {\n                const int to = reverse_adjacency[position];\n\
    \                if (component[to] != -1) continue;\n                component[to]\
    \ = component_count;\n                stack.push_back(to);\n            }\n  \
    \      }\n        component_count++;\n    }\n    return component;\n}\n\n}  //\
    \ namespace incremental_scc_detail\n\n// For every directed edge e, returns the\
    \ first time t after e is inserted such\n// that its endpoints are in the same\
    \ SCC. At time t, edges with IDs less than\n// t have been inserted. edge_count()\
    \ + 1 means this never happens.\ntemplate <class T>\nstd::vector<int> incremental_scc(const\
    \ Graph<T>& graph) {\n    using incremental_scc_detail::EdgeEvent;\n    using\
    \ incremental_scc_detail::component_ids;\n\n    const int vertex_count = graph.size();\n\
    \    const int edge_count = graph.edge_count();\n    const int never = edge_count\
    \ + 1;\n    std::vector<int> merge_time(edge_count, never);\n    if (edge_count\
    \ == 0) return merge_time;\n\n    std::vector<EdgeEvent> edges_by_id(edge_count);\n\
    \    std::vector<char> initialized(edge_count, false);\n    for (int vertex =\
    \ 0; vertex < vertex_count; vertex++) {\n        for (const Edge<T>& edge : graph[vertex])\
    \ {\n            assert(0 <= edge.id && edge.id < edge_count);\n            assert(!initialized[edge.id]);\n\
    \            if (initialized[edge.id]) continue;\n            initialized[edge.id]\
    \ = true;\n            edges_by_id[edge.id] = EdgeEvent{edge.id, edge.from, edge.to};\n\
    \        }\n    }\n\n    std::vector<EdgeEvent> events;\n    events.reserve(edge_count);\n\
    \    for (int edge_id = 0; edge_id < edge_count; edge_id++) {\n        assert(initialized[edge_id]);\n\
    \        if (graph.is_edge_alive(edge_id)) {\n            events.push_back(edges_by_id[edge_id]);\n\
    \        }\n    }\n    std::vector<EdgeEvent>().swap(edges_by_id);\n    std::vector<char>().swap(initialized);\n\
    \n    std::vector<int> new_index(vertex_count, -1);\n    auto divide = [&](\n\
    \        auto&& self,\n        std::vector<EdgeEvent> current,\n        int left,\n\
    \        int right\n    ) -> void {\n        if (current.empty() || right == left\
    \ + 1) return;\n        const int middle = left + (right - left) / 2;\n\n    \
    \    std::vector<int> touched;\n        touched.reserve(std::min(\n          \
    \  std::size_t(vertex_count),\n            current.size() * 2\n        ));\n \
    \       int compressed_count = 0;\n        for (const EdgeEvent& edge : current)\
    \ {\n            if (new_index[edge.from] == -1) {\n                new_index[edge.from]\
    \ = compressed_count++;\n                touched.push_back(edge.from);\n     \
    \       }\n            if (new_index[edge.to] == -1) {\n                new_index[edge.to]\
    \ = compressed_count++;\n                touched.push_back(edge.to);\n       \
    \     }\n        }\n        for (EdgeEvent& edge : current) {\n            edge.from\
    \ = new_index[edge.from];\n            edge.to = new_index[edge.to];\n       \
    \ }\n        for (int vertex : touched) new_index[vertex] = -1;\n\n        std::vector<EdgeEvent>\
    \ earlier;\n        std::vector<EdgeEvent> later;\n        earlier.reserve(current.size()\
    \ / 2);\n        later.reserve(current.size() / 2);\n        {\n            std::vector<int>\
    \ component =\n                component_ids(compressed_count, current, middle);\n\
    \            for (const EdgeEvent& edge : current) {\n                const int\
    \ from_component = component[edge.from];\n                const int to_component\
    \ = component[edge.to];\n                if (edge.id < middle &&\n           \
    \         from_component == to_component) {\n                    merge_time[edge.id]\
    \ =\n                        std::min(merge_time[edge.id], middle);\n        \
    \            earlier.push_back(edge);\n                } else {\n            \
    \        later.push_back(EdgeEvent{\n                        edge.id,\n      \
    \                  from_component,\n                        to_component\n   \
    \                 });\n                }\n            }\n        }\n\n       \
    \ std::vector<EdgeEvent>().swap(current);\n        self(self, std::move(earlier),\
    \ left, middle);\n        self(self, std::move(later), middle, right);\n    };\n\
    \    divide(divide, std::move(events), 0, edge_count + 1);\n    return merge_time;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_INCREMENTAL_SCC_HPP\n#define M1UNE_GRAPH_INCREMENTAL_SCC_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"graph.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nnamespace incremental_scc_detail {\n\nstruct EdgeEvent {\n\
    \    int id;\n    int from;\n    int to;\n};\n\ninline std::vector<int> component_ids(\n\
    \    int vertex_count,\n    const std::vector<EdgeEvent>& edges,\n    int time\n\
    ) {\n    std::vector<int> begin(vertex_count + 1, 0);\n    std::vector<int> reverse_begin(vertex_count\
    \ + 1, 0);\n    int edge_count = 0;\n    for (const EdgeEvent& edge : edges) {\n\
    \        if (edge.id >= time) continue;\n        begin[edge.from + 1]++;\n   \
    \     reverse_begin[edge.to + 1]++;\n        edge_count++;\n    }\n    for (int\
    \ vertex = 0; vertex < vertex_count; vertex++) {\n        begin[vertex + 1] +=\
    \ begin[vertex];\n        reverse_begin[vertex + 1] += reverse_begin[vertex];\n\
    \    }\n\n    std::vector<int> adjacency(edge_count);\n    std::vector<int> reverse_adjacency(edge_count);\n\
    \    std::vector<int> cursor = begin;\n    std::vector<int> reverse_cursor = reverse_begin;\n\
    \    for (const EdgeEvent& edge : edges) {\n        if (edge.id >= time) continue;\n\
    \        adjacency[cursor[edge.from]++] = edge.to;\n        reverse_adjacency[reverse_cursor[edge.to]++]\
    \ = edge.from;\n    }\n    std::vector<int>().swap(cursor);\n    std::vector<int>().swap(reverse_cursor);\n\
    \n    std::vector<char> visited(vertex_count, false);\n    std::vector<int> next_position(begin.begin(),\
    \ begin.end() - 1);\n    std::vector<int> order;\n    order.reserve(vertex_count);\n\
    \    std::vector<int> stack;\n    for (int start = 0; start < vertex_count; start++)\
    \ {\n        if (visited[start]) continue;\n        visited[start] = true;\n \
    \       stack.push_back(start);\n        while (!stack.empty()) {\n          \
    \  const int vertex = stack.back();\n            int& position = next_position[vertex];\n\
    \            if (position < begin[vertex + 1]) {\n                const int to\
    \ = adjacency[position++];\n                if (!visited[to]) {\n            \
    \        visited[to] = true;\n                    stack.push_back(to);\n     \
    \           }\n            } else {\n                order.push_back(vertex);\n\
    \                stack.pop_back();\n            }\n        }\n    }\n\n    std::vector<int>\
    \ component(vertex_count, -1);\n    int component_count = 0;\n    for (auto iterator\
    \ = order.rbegin(); iterator != order.rend(); ++iterator) {\n        const int\
    \ start = *iterator;\n        if (component[start] != -1) continue;\n        component[start]\
    \ = component_count;\n        stack.push_back(start);\n        while (!stack.empty())\
    \ {\n            const int vertex = stack.back();\n            stack.pop_back();\n\
    \            for (int position = reverse_begin[vertex];\n                 position\
    \ < reverse_begin[vertex + 1]; position++) {\n                const int to = reverse_adjacency[position];\n\
    \                if (component[to] != -1) continue;\n                component[to]\
    \ = component_count;\n                stack.push_back(to);\n            }\n  \
    \      }\n        component_count++;\n    }\n    return component;\n}\n\n}  //\
    \ namespace incremental_scc_detail\n\n// For every directed edge e, returns the\
    \ first time t after e is inserted such\n// that its endpoints are in the same\
    \ SCC. At time t, edges with IDs less than\n// t have been inserted. edge_count()\
    \ + 1 means this never happens.\ntemplate <class T>\nstd::vector<int> incremental_scc(const\
    \ Graph<T>& graph) {\n    using incremental_scc_detail::EdgeEvent;\n    using\
    \ incremental_scc_detail::component_ids;\n\n    const int vertex_count = graph.size();\n\
    \    const int edge_count = graph.edge_count();\n    const int never = edge_count\
    \ + 1;\n    std::vector<int> merge_time(edge_count, never);\n    if (edge_count\
    \ == 0) return merge_time;\n\n    std::vector<EdgeEvent> edges_by_id(edge_count);\n\
    \    std::vector<char> initialized(edge_count, false);\n    for (int vertex =\
    \ 0; vertex < vertex_count; vertex++) {\n        for (const Edge<T>& edge : graph[vertex])\
    \ {\n            assert(0 <= edge.id && edge.id < edge_count);\n            assert(!initialized[edge.id]);\n\
    \            if (initialized[edge.id]) continue;\n            initialized[edge.id]\
    \ = true;\n            edges_by_id[edge.id] = EdgeEvent{edge.id, edge.from, edge.to};\n\
    \        }\n    }\n\n    std::vector<EdgeEvent> events;\n    events.reserve(edge_count);\n\
    \    for (int edge_id = 0; edge_id < edge_count; edge_id++) {\n        assert(initialized[edge_id]);\n\
    \        if (graph.is_edge_alive(edge_id)) {\n            events.push_back(edges_by_id[edge_id]);\n\
    \        }\n    }\n    std::vector<EdgeEvent>().swap(edges_by_id);\n    std::vector<char>().swap(initialized);\n\
    \n    std::vector<int> new_index(vertex_count, -1);\n    auto divide = [&](\n\
    \        auto&& self,\n        std::vector<EdgeEvent> current,\n        int left,\n\
    \        int right\n    ) -> void {\n        if (current.empty() || right == left\
    \ + 1) return;\n        const int middle = left + (right - left) / 2;\n\n    \
    \    std::vector<int> touched;\n        touched.reserve(std::min(\n          \
    \  std::size_t(vertex_count),\n            current.size() * 2\n        ));\n \
    \       int compressed_count = 0;\n        for (const EdgeEvent& edge : current)\
    \ {\n            if (new_index[edge.from] == -1) {\n                new_index[edge.from]\
    \ = compressed_count++;\n                touched.push_back(edge.from);\n     \
    \       }\n            if (new_index[edge.to] == -1) {\n                new_index[edge.to]\
    \ = compressed_count++;\n                touched.push_back(edge.to);\n       \
    \     }\n        }\n        for (EdgeEvent& edge : current) {\n            edge.from\
    \ = new_index[edge.from];\n            edge.to = new_index[edge.to];\n       \
    \ }\n        for (int vertex : touched) new_index[vertex] = -1;\n\n        std::vector<EdgeEvent>\
    \ earlier;\n        std::vector<EdgeEvent> later;\n        earlier.reserve(current.size()\
    \ / 2);\n        later.reserve(current.size() / 2);\n        {\n            std::vector<int>\
    \ component =\n                component_ids(compressed_count, current, middle);\n\
    \            for (const EdgeEvent& edge : current) {\n                const int\
    \ from_component = component[edge.from];\n                const int to_component\
    \ = component[edge.to];\n                if (edge.id < middle &&\n           \
    \         from_component == to_component) {\n                    merge_time[edge.id]\
    \ =\n                        std::min(merge_time[edge.id], middle);\n        \
    \            earlier.push_back(edge);\n                } else {\n            \
    \        later.push_back(EdgeEvent{\n                        edge.id,\n      \
    \                  from_component,\n                        to_component\n   \
    \                 });\n                }\n            }\n        }\n\n       \
    \ std::vector<EdgeEvent>().swap(current);\n        self(self, std::move(earlier),\
    \ left, middle);\n        self(self, std::move(later), middle, right);\n    };\n\
    \    divide(divide, std::move(events), 0, edge_count + 1);\n    return merge_time;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_INCREMENTAL_SCC_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/incremental_scc.hpp
  requiredBy:
  - graph/directed.hpp
  - graph/all.hpp
  timestamp: '2026-07-16 23:38:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/incremental_scc.test.cpp
documentation_of: graph/incremental_scc.hpp
layout: document
title: Incremental Strongly Connected Components
---

## Overview

`incremental_scc(graph)` processes a known sequence of directed edge
insertions offline. Edge IDs are their insertion positions.

For an edge with ID `e`, the returned value `merge_time[e]` is the smallest
time `t` satisfying `e < t <= M` such that its endpoints belong to the same SCC
after inserting all active edges with IDs less than `t`. The value `M + 1`
means this never happens.

These times describe every SCC merge. Starting with a DSU of singleton
vertices, at each time `t`, merge the endpoints of all edges satisfying
`merge_time[e] == t`. The resulting DSU groups are exactly the SCCs after the
first `t` insertion positions.

## Graph Requirements

Build the graph with `Graph<T>::add_directed_edge`. Parallel edges and
self-loops are supported. Inactive edges are treated as no-op insertion
positions and receive merge time `M + 1`.

The SCC traversals are iterative; only the divide-and-conquer recursion remains,
and its depth is `O(log(M + 1))`. The function does not mutate the graph.

## API

```cpp
template <class T>
std::vector<int> incremental_scc(const Graph<T>& graph);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `incremental_scc(graph)` | Returns the first same-SCC time for every edge ID. | `O((N + M) log(M + 1))` time and `O(N + M)` auxiliary memory |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/incremental_scc.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(3);
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(1, 2);
    graph.add_directed_edge(2, 0);

    auto merge_time = m1une::graph::incremental_scc(graph);
    for (int time : merge_time) {
        std::cout << time << "\n"; // all three values are 3
    }
}
```
