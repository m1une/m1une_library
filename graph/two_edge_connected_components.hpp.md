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
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/two_edge_connected_components.test.cpp
    title: verify/graph/two_edge_connected_components.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/two_edge_connected_components.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 5 \"\
    graph/graph.hpp\"\n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
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
    \ m1une\n\n\n#line 8 \"graph/two_edge_connected_components.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct TwoEdgeConnectedBridge {\n    int from;\n\
    \    int to;\n    int edge_id;\n};\n\nstruct TwoEdgeConnectedComponentsResult\
    \ {\n    std::vector<std::vector<int>> components;\n    std::vector<int> component_of_vertex;\n\
    \    std::vector<int> bridge_ids;\n    std::vector<char> bridge;\n    std::vector<TwoEdgeConnectedBridge>\
    \ bridge_forest_edges;\n    std::vector<int> ord;\n    std::vector<int> low;\n\
    \n    int component_count() const {\n        return int(components.size());\n\
    \    }\n\n    bool same(int first, int second) const {\n        assert(0 <= first\
    \ && first < int(component_of_vertex.size()));\n        assert(0 <= second &&\
    \ second < int(component_of_vertex.size()));\n        return component_of_vertex[first]\
    \ == component_of_vertex[second];\n    }\n\n    bool is_bridge(int edge_id) const\
    \ {\n        assert(0 <= edge_id && edge_id < int(bridge.size()));\n        return\
    \ bridge[edge_id];\n    }\n};\n\n// Removes every active bridge and returns the\
    \ remaining connected components.\n// The first lowlink traversal and the component\
    \ traversal are both iterative.\ntemplate <class T>\nTwoEdgeConnectedComponentsResult\
    \ two_edge_connected_components(\n    const Graph<T>& graph\n) {\n    const int\
    \ n = graph.size();\n    const int edge_count = graph.edge_count();\n\n    TwoEdgeConnectedComponentsResult\
    \ result;\n    result.component_of_vertex.assign(n, -1);\n    result.bridge.assign(edge_count,\
    \ false);\n    result.ord.assign(n, -1);\n    result.low.assign(n, -1);\n\n  \
    \  std::vector<int> edge_from(edge_count, -1);\n    std::vector<int> edge_to(edge_count,\
    \ -1);\n    std::vector<int> incidence_count(edge_count, 0);\n    for (int vertex\
    \ = 0; vertex < n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex])\
    \ {\n            if (!edge.alive) continue;\n            assert(0 <= edge.id &&\
    \ edge.id < edge_count);\n            if (incidence_count[edge.id] == 0) {\n \
    \               edge_from[edge.id] = edge.from;\n                edge_to[edge.id]\
    \ = edge.to;\n            }\n            incidence_count[edge.id]++;\n       \
    \ }\n    }\n#ifndef NDEBUG\n    for (int edge_id = 0; edge_id < edge_count; edge_id++)\
    \ {\n        if (incidence_count[edge_id] != 0) assert(incidence_count[edge_id]\
    \ == 2);\n    }\n#endif\n\n    std::vector<int> parent(n, -1);\n    std::vector<int>\
    \ parent_edge(n, -1);\n    std::vector<int> next_edge(n, 0);\n    std::vector<int>\
    \ stack;\n    int timer = 0;\n\n    for (int root = 0; root < n; root++) {\n \
    \       if (result.ord[root] != -1) continue;\n        result.ord[root] = result.low[root]\
    \ = timer++;\n        stack.push_back(root);\n        while (!stack.empty()) {\n\
    \            const int vertex = stack.back();\n            if (next_edge[vertex]\
    \ < int(graph[vertex].size())) {\n                const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n\
    \                if (!edge.alive || edge.id == parent_edge[vertex]) continue;\n\
    \                const int to = edge.to;\n                if (result.ord[to] ==\
    \ -1) {\n                    parent[to] = vertex;\n                    parent_edge[to]\
    \ = edge.id;\n                    result.ord[to] = result.low[to] = timer++;\n\
    \                    stack.push_back(to);\n                } else if (result.ord[to]\
    \ < result.low[vertex]) {\n                    result.low[vertex] = result.ord[to];\n\
    \                }\n                continue;\n            }\n\n            stack.pop_back();\n\
    \            const int parent_vertex = parent[vertex];\n            if (parent_vertex\
    \ == -1) continue;\n            if (result.low[vertex] < result.low[parent_vertex])\
    \ {\n                result.low[parent_vertex] = result.low[vertex];\n       \
    \     }\n            if (result.ord[parent_vertex] < result.low[vertex]) {\n \
    \               result.bridge[parent_edge[vertex]] = true;\n            }\n  \
    \      }\n    }\n\n    for (int root = 0; root < n; root++) {\n        if (result.component_of_vertex[root]\
    \ != -1) continue;\n        const int component = result.component_count();\n\
    \        result.components.emplace_back();\n        result.component_of_vertex[root]\
    \ = component;\n        stack.push_back(root);\n        while (!stack.empty())\
    \ {\n            const int vertex = stack.back();\n            stack.pop_back();\n\
    \            result.components.back().push_back(vertex);\n            for (const\
    \ Edge<T>& edge : graph[vertex]) {\n                if (!edge.alive || result.bridge[edge.id])\
    \ continue;\n                if (result.component_of_vertex[edge.to] != -1) continue;\n\
    \                result.component_of_vertex[edge.to] = component;\n          \
    \      stack.push_back(edge.to);\n            }\n        }\n    }\n\n    for (int\
    \ edge_id = 0; edge_id < edge_count; edge_id++) {\n        if (!result.bridge[edge_id])\
    \ continue;\n        result.bridge_ids.push_back(edge_id);\n        const int\
    \ first_component = result.component_of_vertex[edge_from[edge_id]];\n        const\
    \ int second_component = result.component_of_vertex[edge_to[edge_id]];\n     \
    \   assert(first_component != second_component);\n        result.bridge_forest_edges.push_back(\n\
    \            TwoEdgeConnectedBridge{first_component, second_component, edge_id});\n\
    \    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_GRAPH_TWO_EDGE_CONNECTED_COMPONENTS_HPP\n#define M1UNE_GRAPH_TWO_EDGE_CONNECTED_COMPONENTS_HPP\
    \ 1\n\n#include <cassert>\n#include <vector>\n\n#include \"graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct TwoEdgeConnectedBridge {\n    int from;\n\
    \    int to;\n    int edge_id;\n};\n\nstruct TwoEdgeConnectedComponentsResult\
    \ {\n    std::vector<std::vector<int>> components;\n    std::vector<int> component_of_vertex;\n\
    \    std::vector<int> bridge_ids;\n    std::vector<char> bridge;\n    std::vector<TwoEdgeConnectedBridge>\
    \ bridge_forest_edges;\n    std::vector<int> ord;\n    std::vector<int> low;\n\
    \n    int component_count() const {\n        return int(components.size());\n\
    \    }\n\n    bool same(int first, int second) const {\n        assert(0 <= first\
    \ && first < int(component_of_vertex.size()));\n        assert(0 <= second &&\
    \ second < int(component_of_vertex.size()));\n        return component_of_vertex[first]\
    \ == component_of_vertex[second];\n    }\n\n    bool is_bridge(int edge_id) const\
    \ {\n        assert(0 <= edge_id && edge_id < int(bridge.size()));\n        return\
    \ bridge[edge_id];\n    }\n};\n\n// Removes every active bridge and returns the\
    \ remaining connected components.\n// The first lowlink traversal and the component\
    \ traversal are both iterative.\ntemplate <class T>\nTwoEdgeConnectedComponentsResult\
    \ two_edge_connected_components(\n    const Graph<T>& graph\n) {\n    const int\
    \ n = graph.size();\n    const int edge_count = graph.edge_count();\n\n    TwoEdgeConnectedComponentsResult\
    \ result;\n    result.component_of_vertex.assign(n, -1);\n    result.bridge.assign(edge_count,\
    \ false);\n    result.ord.assign(n, -1);\n    result.low.assign(n, -1);\n\n  \
    \  std::vector<int> edge_from(edge_count, -1);\n    std::vector<int> edge_to(edge_count,\
    \ -1);\n    std::vector<int> incidence_count(edge_count, 0);\n    for (int vertex\
    \ = 0; vertex < n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex])\
    \ {\n            if (!edge.alive) continue;\n            assert(0 <= edge.id &&\
    \ edge.id < edge_count);\n            if (incidence_count[edge.id] == 0) {\n \
    \               edge_from[edge.id] = edge.from;\n                edge_to[edge.id]\
    \ = edge.to;\n            }\n            incidence_count[edge.id]++;\n       \
    \ }\n    }\n#ifndef NDEBUG\n    for (int edge_id = 0; edge_id < edge_count; edge_id++)\
    \ {\n        if (incidence_count[edge_id] != 0) assert(incidence_count[edge_id]\
    \ == 2);\n    }\n#endif\n\n    std::vector<int> parent(n, -1);\n    std::vector<int>\
    \ parent_edge(n, -1);\n    std::vector<int> next_edge(n, 0);\n    std::vector<int>\
    \ stack;\n    int timer = 0;\n\n    for (int root = 0; root < n; root++) {\n \
    \       if (result.ord[root] != -1) continue;\n        result.ord[root] = result.low[root]\
    \ = timer++;\n        stack.push_back(root);\n        while (!stack.empty()) {\n\
    \            const int vertex = stack.back();\n            if (next_edge[vertex]\
    \ < int(graph[vertex].size())) {\n                const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n\
    \                if (!edge.alive || edge.id == parent_edge[vertex]) continue;\n\
    \                const int to = edge.to;\n                if (result.ord[to] ==\
    \ -1) {\n                    parent[to] = vertex;\n                    parent_edge[to]\
    \ = edge.id;\n                    result.ord[to] = result.low[to] = timer++;\n\
    \                    stack.push_back(to);\n                } else if (result.ord[to]\
    \ < result.low[vertex]) {\n                    result.low[vertex] = result.ord[to];\n\
    \                }\n                continue;\n            }\n\n            stack.pop_back();\n\
    \            const int parent_vertex = parent[vertex];\n            if (parent_vertex\
    \ == -1) continue;\n            if (result.low[vertex] < result.low[parent_vertex])\
    \ {\n                result.low[parent_vertex] = result.low[vertex];\n       \
    \     }\n            if (result.ord[parent_vertex] < result.low[vertex]) {\n \
    \               result.bridge[parent_edge[vertex]] = true;\n            }\n  \
    \      }\n    }\n\n    for (int root = 0; root < n; root++) {\n        if (result.component_of_vertex[root]\
    \ != -1) continue;\n        const int component = result.component_count();\n\
    \        result.components.emplace_back();\n        result.component_of_vertex[root]\
    \ = component;\n        stack.push_back(root);\n        while (!stack.empty())\
    \ {\n            const int vertex = stack.back();\n            stack.pop_back();\n\
    \            result.components.back().push_back(vertex);\n            for (const\
    \ Edge<T>& edge : graph[vertex]) {\n                if (!edge.alive || result.bridge[edge.id])\
    \ continue;\n                if (result.component_of_vertex[edge.to] != -1) continue;\n\
    \                result.component_of_vertex[edge.to] = component;\n          \
    \      stack.push_back(edge.to);\n            }\n        }\n    }\n\n    for (int\
    \ edge_id = 0; edge_id < edge_count; edge_id++) {\n        if (!result.bridge[edge_id])\
    \ continue;\n        result.bridge_ids.push_back(edge_id);\n        const int\
    \ first_component = result.component_of_vertex[edge_from[edge_id]];\n        const\
    \ int second_component = result.component_of_vertex[edge_to[edge_id]];\n     \
    \   assert(first_component != second_component);\n        result.bridge_forest_edges.push_back(\n\
    \            TwoEdgeConnectedBridge{first_component, second_component, edge_id});\n\
    \    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n#endif  // M1UNE_GRAPH_TWO_EDGE_CONNECTED_COMPONENTS_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/two_edge_connected_components.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-11 19:47:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/two_edge_connected_components.test.cpp
documentation_of: graph/two_edge_connected_components.hpp
layout: document
title: Two-Edge-Connected Components
---

## Overview

Two connected vertices are in the same two-edge-connected component when
deleting any single edge cannot separate them. Equivalently, remove every
bridge and take the connected components that remain.

This header returns that decomposition, all bridge IDs, and the forest obtained
by contracting every component. Each contracted edge remembers the ID of its
original bridge.

## Graph Requirements

Build the undirected graph with `Graph<T>::add_edge`. Directed edges are not
supported. Parallel edges and self-loops are supported: parallel edges prevent
each other from being bridges, and a self-loop is never a bridge.

Inactive edges are ignored. They are not reported as bridges and do not connect
components.

Both traversals are iterative, so deep paths do not consume the call stack.

## API

```cpp
struct TwoEdgeConnectedBridge {
    int from;
    int to;
    int edge_id;
};

struct TwoEdgeConnectedComponentsResult {
    std::vector<std::vector<int>> components;
    std::vector<int> component_of_vertex;
    std::vector<int> bridge_ids;
    std::vector<char> bridge;
    std::vector<TwoEdgeConnectedBridge> bridge_forest_edges;
    std::vector<int> ord;
    std::vector<int> low;

    int component_count() const;
    bool same(int first, int second) const;
    bool is_bridge(int edge_id) const;
};

template <class T>
TwoEdgeConnectedComponentsResult two_edge_connected_components(
    const Graph<T>& graph
);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `components[c]` | Vertices in component `c`; their order is unspecified. | -- |
| `component_of_vertex[v]` | Component containing vertex `v`. | $O(1)$ |
| `bridge_ids` | Active bridge IDs in increasing edge-ID order. | -- |
| `bridge[e]` | Nonzero exactly when active edge `e` is a bridge. | $O(1)$ |
| `bridge_forest_edges` | Component-to-component edges after contraction, with original bridge IDs. | -- |
| `ord[v]`, `low[v]` | DFS order and lowlink value of vertex `v`. | $O(1)$ |
| `component_count()` | Number of two-edge-connected components. | $O(1)$ |
| `same(u, v)` | Whether `u` and `v` belong to the same component. | $O(1)$ |
| `is_bridge(edge_id)` | Whether the active edge is a bridge; inactive edges return false. | $O(1)$ |
| `two_edge_connected_components(graph)` | Computes the decomposition and bridge forest. | $O(N + M)$ |

The function does not mutate the graph and uses $O(N + M)$ memory.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/two_edge_connected_components.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);
    int bridge = graph.add_edge(2, 3);

    auto result = m1une::graph::two_edge_connected_components(graph);
    std::cout << result.component_count() << "\n";  // 2
    std::cout << result.same(0, 2) << "\n";          // 1
    std::cout << result.is_bridge(bridge) << "\n";   // 1
}
```
