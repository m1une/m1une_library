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
    path: verify/graph/three_edge_connected_components.test.cpp
    title: verify/graph/three_edge_connected_components.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/three_edge_connected_components.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <numeric>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
    \ {\n    using cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n   \
    \ int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1),\
    \ alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool\
    \ alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_)\
    \ {}\n\n    int other(int v) const {\n        assert(v == from || v == to);\n\
    \        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
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
    \ m1une\n\n\n#line 11 \"graph/three_edge_connected_components.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct ThreeEdgeConnectedComponentsResult {\n\
    \    std::vector<std::vector<int>> components;\n    std::vector<int> component_of_vertex;\n\
    \n    int component_count() const {\n        return int(components.size());\n\
    \    }\n\n    bool same(int first, int second) const {\n        assert(0 <= first\
    \ && first < int(component_of_vertex.size()));\n        assert(0 <= second &&\
    \ second < int(component_of_vertex.size()));\n        return component_of_vertex[first]\
    \ == component_of_vertex[second];\n    }\n};\n\nnamespace internal {\n\n// Maintains\
    \ every component as a circular linked list. Swapping two successors\n// concatenates\
    \ two different lists in O(1) time.\nstruct ThreeEdgeComponentCycles {\n    std::vector<int>\
    \ next;\n\n    explicit ThreeEdgeComponentCycles(int n) : next(n) {\n        std::iota(next.begin(),\
    \ next.end(), 0);\n    }\n\n    void unite(int first, int second) {\n        std::swap(next[first],\
    \ next[second]);\n    }\n\n    ThreeEdgeConnectedComponentsResult build_result()\
    \ const {\n        const int n = int(next.size());\n        ThreeEdgeConnectedComponentsResult\
    \ result;\n        result.component_of_vertex.assign(n, -1);\n        for (int\
    \ first = 0; first < n; first++) {\n            if (result.component_of_vertex[first]\
    \ != -1) continue;\n            const int component = result.component_count();\n\
    \            result.components.emplace_back();\n            int vertex = first;\n\
    \            do {\n                result.component_of_vertex[vertex] = component;\n\
    \                result.components.back().push_back(vertex);\n               \
    \ vertex = next[vertex];\n            } while (vertex != first);\n        }\n\
    \        return result;\n    }\n};\n\n}  // namespace internal\n\n// Decomposes\
    \ an undirected multigraph into maximal vertex sets joined by at\n// least three\
    \ edge-disjoint paths. This is an iterative form of Tsin's\n// one-pass contraction\
    \ algorithm.\ntemplate <class T>\nThreeEdgeConnectedComponentsResult three_edge_connected_components(\n\
    \    const Graph<T>& graph\n) {\n    const int n = graph.size();\n    const int\
    \ edge_count = graph.edge_count();\n\n#ifndef NDEBUG\n    std::vector<int> incidence_count(edge_count,\
    \ 0);\n    for (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>&\
    \ edge : graph[vertex]) {\n            if (!edge.alive) continue;\n          \
    \  assert(edge.from == vertex);\n            assert(0 <= edge.to && edge.to <\
    \ n);\n            assert(0 <= edge.id && edge.id < edge_count);\n           \
    \ incidence_count[edge.id]++;\n        }\n    }\n    for (int edge_id = 0; edge_id\
    \ < edge_count; edge_id++) {\n        if (incidence_count[edge_id] != 0) assert(incidence_count[edge_id]\
    \ == 2);\n    }\n#endif\n\n    const int none = n;\n    std::vector<int> enter(n,\
    \ -1);\n    std::vector<int> leave(n, 0);\n    std::vector<int> low(n, none);\n\
    \    std::vector<int> degree(n, 0);\n    std::vector<int> path(n, none);\n   \
    \ std::vector<int> parent(n, -1);\n    std::vector<int> parent_edge(n, -1);\n\
    \    std::vector<int> next_edge(n, 0);\n    std::vector<int> dfs_stack;\n    internal::ThreeEdgeComponentCycles\
    \ component_cycles(n);\n    int timer = 0;\n\n    auto absorb = [&](int vertex,\
    \ int other) {\n        component_cycles.unite(vertex, other);\n        degree[vertex]\
    \ += degree[other];\n    };\n\n    auto process_visited_edge = [&](int vertex,\
    \ int to) {\n        if (enter[to] < enter[vertex]) {\n            degree[vertex]++;\n\
    \            low[vertex] = std::min(low[vertex], enter[to]);\n            return;\n\
    \        }\n\n        degree[vertex]--;\n        int current = path[vertex];\n\
    \        while (current != none && enter[current] <= enter[to] && enter[to] <\
    \ leave[current]) {\n            absorb(vertex, current);\n            current\
    \ = path[current];\n        }\n        path[vertex] = current;\n    };\n\n   \
    \ auto process_child = [&](int vertex, int child) {\n        if (path[child] ==\
    \ none && degree[child] <= 1) {\n            degree[vertex] += degree[child];\n\
    \            low[vertex] = std::min(low[vertex], low[child]);\n            return;\n\
    \        }\n\n        int current = child;\n        if (degree[child] == 0) current\
    \ = path[child];\n        assert(current != none);\n        if (low[current] <\
    \ low[vertex]) {\n            low[vertex] = low[current];\n            std::swap(current,\
    \ path[vertex]);\n        }\n        while (current != none) {\n            absorb(vertex,\
    \ current);\n            current = path[current];\n        }\n    };\n\n    for\
    \ (int root = 0; root < n; root++) {\n        if (enter[root] != -1) continue;\n\
    \        enter[root] = timer++;\n        dfs_stack.push_back(root);\n\n      \
    \  while (!dfs_stack.empty()) {\n            const int vertex = dfs_stack.back();\n\
    \            if (next_edge[vertex] < int(graph[vertex].size())) {\n          \
    \      const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n           \
    \     if (!edge.alive || edge.from == edge.to || edge.id == parent_edge[vertex])\
    \ continue;\n                const int to = edge.to;\n                if (enter[to]\
    \ == -1) {\n                    parent[to] = vertex;\n                    parent_edge[to]\
    \ = edge.id;\n                    enter[to] = timer++;\n                    dfs_stack.push_back(to);\n\
    \                } else {\n                    process_visited_edge(vertex, to);\n\
    \                }\n                continue;\n            }\n\n            leave[vertex]\
    \ = timer;\n            dfs_stack.pop_back();\n            if (parent[vertex]\
    \ != -1) process_child(parent[vertex], vertex);\n        }\n    }\n\n    return\
    \ component_cycles.build_result();\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_THREE_EDGE_CONNECTED_COMPONENTS_HPP\n#define M1UNE_GRAPH_THREE_EDGE_CONNECTED_COMPONENTS_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"graph.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nstruct ThreeEdgeConnectedComponentsResult {\n    std::vector<std::vector<int>>\
    \ components;\n    std::vector<int> component_of_vertex;\n\n    int component_count()\
    \ const {\n        return int(components.size());\n    }\n\n    bool same(int\
    \ first, int second) const {\n        assert(0 <= first && first < int(component_of_vertex.size()));\n\
    \        assert(0 <= second && second < int(component_of_vertex.size()));\n  \
    \      return component_of_vertex[first] == component_of_vertex[second];\n   \
    \ }\n};\n\nnamespace internal {\n\n// Maintains every component as a circular\
    \ linked list. Swapping two successors\n// concatenates two different lists in\
    \ O(1) time.\nstruct ThreeEdgeComponentCycles {\n    std::vector<int> next;\n\n\
    \    explicit ThreeEdgeComponentCycles(int n) : next(n) {\n        std::iota(next.begin(),\
    \ next.end(), 0);\n    }\n\n    void unite(int first, int second) {\n        std::swap(next[first],\
    \ next[second]);\n    }\n\n    ThreeEdgeConnectedComponentsResult build_result()\
    \ const {\n        const int n = int(next.size());\n        ThreeEdgeConnectedComponentsResult\
    \ result;\n        result.component_of_vertex.assign(n, -1);\n        for (int\
    \ first = 0; first < n; first++) {\n            if (result.component_of_vertex[first]\
    \ != -1) continue;\n            const int component = result.component_count();\n\
    \            result.components.emplace_back();\n            int vertex = first;\n\
    \            do {\n                result.component_of_vertex[vertex] = component;\n\
    \                result.components.back().push_back(vertex);\n               \
    \ vertex = next[vertex];\n            } while (vertex != first);\n        }\n\
    \        return result;\n    }\n};\n\n}  // namespace internal\n\n// Decomposes\
    \ an undirected multigraph into maximal vertex sets joined by at\n// least three\
    \ edge-disjoint paths. This is an iterative form of Tsin's\n// one-pass contraction\
    \ algorithm.\ntemplate <class T>\nThreeEdgeConnectedComponentsResult three_edge_connected_components(\n\
    \    const Graph<T>& graph\n) {\n    const int n = graph.size();\n    const int\
    \ edge_count = graph.edge_count();\n\n#ifndef NDEBUG\n    std::vector<int> incidence_count(edge_count,\
    \ 0);\n    for (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>&\
    \ edge : graph[vertex]) {\n            if (!edge.alive) continue;\n          \
    \  assert(edge.from == vertex);\n            assert(0 <= edge.to && edge.to <\
    \ n);\n            assert(0 <= edge.id && edge.id < edge_count);\n           \
    \ incidence_count[edge.id]++;\n        }\n    }\n    for (int edge_id = 0; edge_id\
    \ < edge_count; edge_id++) {\n        if (incidence_count[edge_id] != 0) assert(incidence_count[edge_id]\
    \ == 2);\n    }\n#endif\n\n    const int none = n;\n    std::vector<int> enter(n,\
    \ -1);\n    std::vector<int> leave(n, 0);\n    std::vector<int> low(n, none);\n\
    \    std::vector<int> degree(n, 0);\n    std::vector<int> path(n, none);\n   \
    \ std::vector<int> parent(n, -1);\n    std::vector<int> parent_edge(n, -1);\n\
    \    std::vector<int> next_edge(n, 0);\n    std::vector<int> dfs_stack;\n    internal::ThreeEdgeComponentCycles\
    \ component_cycles(n);\n    int timer = 0;\n\n    auto absorb = [&](int vertex,\
    \ int other) {\n        component_cycles.unite(vertex, other);\n        degree[vertex]\
    \ += degree[other];\n    };\n\n    auto process_visited_edge = [&](int vertex,\
    \ int to) {\n        if (enter[to] < enter[vertex]) {\n            degree[vertex]++;\n\
    \            low[vertex] = std::min(low[vertex], enter[to]);\n            return;\n\
    \        }\n\n        degree[vertex]--;\n        int current = path[vertex];\n\
    \        while (current != none && enter[current] <= enter[to] && enter[to] <\
    \ leave[current]) {\n            absorb(vertex, current);\n            current\
    \ = path[current];\n        }\n        path[vertex] = current;\n    };\n\n   \
    \ auto process_child = [&](int vertex, int child) {\n        if (path[child] ==\
    \ none && degree[child] <= 1) {\n            degree[vertex] += degree[child];\n\
    \            low[vertex] = std::min(low[vertex], low[child]);\n            return;\n\
    \        }\n\n        int current = child;\n        if (degree[child] == 0) current\
    \ = path[child];\n        assert(current != none);\n        if (low[current] <\
    \ low[vertex]) {\n            low[vertex] = low[current];\n            std::swap(current,\
    \ path[vertex]);\n        }\n        while (current != none) {\n            absorb(vertex,\
    \ current);\n            current = path[current];\n        }\n    };\n\n    for\
    \ (int root = 0; root < n; root++) {\n        if (enter[root] != -1) continue;\n\
    \        enter[root] = timer++;\n        dfs_stack.push_back(root);\n\n      \
    \  while (!dfs_stack.empty()) {\n            const int vertex = dfs_stack.back();\n\
    \            if (next_edge[vertex] < int(graph[vertex].size())) {\n          \
    \      const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n           \
    \     if (!edge.alive || edge.from == edge.to || edge.id == parent_edge[vertex])\
    \ continue;\n                const int to = edge.to;\n                if (enter[to]\
    \ == -1) {\n                    parent[to] = vertex;\n                    parent_edge[to]\
    \ = edge.id;\n                    enter[to] = timer++;\n                    dfs_stack.push_back(to);\n\
    \                } else {\n                    process_visited_edge(vertex, to);\n\
    \                }\n                continue;\n            }\n\n            leave[vertex]\
    \ = timer;\n            dfs_stack.pop_back();\n            if (parent[vertex]\
    \ != -1) process_child(parent[vertex], vertex);\n        }\n    }\n\n    return\
    \ component_cycles.build_result();\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GRAPH_THREE_EDGE_CONNECTED_COMPONENTS_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/three_edge_connected_components.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-14 02:26:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/three_edge_connected_components.test.cpp
documentation_of: graph/three_edge_connected_components.hpp
layout: document
title: Three-Edge-Connected Components
---

## Overview

Two vertices are three-edge-connected when at least three edge-disjoint paths
join them. Equivalently, deleting any two edges cannot separate them.

`three_edge_connected_components` partitions the vertices into the maximal sets
defined by this relation. It uses the linear-time one-pass contraction algorithm
of Tsin.

## Graph Requirements

Build the undirected graph with `Graph<T>::add_edge`. Directed edges are not
supported. The graph may be disconnected.

Parallel edges are distinct and therefore contribute separately to edge
connectivity. Self-loops do not join different vertices and are ignored.
Inactive edges are also ignored.

The DFS is iterative, so a path or cycle with many vertices does not consume
the call stack.

## API

```cpp
struct ThreeEdgeConnectedComponentsResult {
    std::vector<std::vector<int>> components;
    std::vector<int> component_of_vertex;

    int component_count() const;
    bool same(int first, int second) const;
};

template <class T>
ThreeEdgeConnectedComponentsResult three_edge_connected_components(
    const Graph<T>& graph
);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `components[c]` | Vertices in component `c`; their order is unspecified. | -- |
| `component_of_vertex[v]` | Component containing vertex `v`. | $O(1)$ |
| `component_count()` | Number of three-edge-connected components. | $O(1)$ |
| `same(u, v)` | Whether `u` and `v` are three-edge-connected. | $O(1)$ |
| `three_edge_connected_components(graph)` | Computes the complete decomposition. | $O(N+M)$ |

The function uses $O(N+M)$ memory including the input graph and does not mutate
the graph.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/three_edge_connected_components.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(3);
    graph.add_edge(0, 1);
    graph.add_edge(0, 1);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    auto result = m1une::graph::three_edge_connected_components(graph);
    std::cout << result.same(0, 1) << "\n";  // 1
    std::cout << result.same(1, 2) << "\n";  // 0
}
```
