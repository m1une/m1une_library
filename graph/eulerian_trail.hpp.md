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
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/eulerian_trail_directed.test.cpp
    title: verify/graph/eulerian_trail_directed.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/eulerian_trail_undirected.test.cpp
    title: verify/graph/eulerian_trail_undirected.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/eulerian_trail.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <optional>\n#include <utility>\n#include <vector>\n\
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
    \ m1une\n\n\n#line 11 \"graph/eulerian_trail.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct EulerianTrail {\n    std::vector<int> vertices;\n    std::vector<int>\
    \ edge_ids;\n\n    int edge_count() const {\n        return int(edge_ids.size());\n\
    \    }\n\n    bool is_circuit() const {\n        return vertices.empty() || vertices.front()\
    \ == vertices.back();\n    }\n};\n\nnamespace internal {\n\ntemplate <class T>\n\
    std::optional<EulerianTrail> hierholzer(\n    const Graph<T>& graph,\n    int\
    \ start,\n    int active_edge_count\n) {\n    EulerianTrail result;\n    if (active_edge_count\
    \ == 0) {\n        if (start != -1) result.vertices.push_back(start);\n      \
    \  return result;\n    }\n\n    assert(0 <= start && start < graph.size());\n\
    \    std::vector<char> used(graph.edge_count(), false);\n    std::vector<int>\
    \ cursor(graph.size(), 0);\n    std::vector<int> vertex_stack(1, start);\n   \
    \ std::vector<int> incoming_edge_stack(1, -1);\n    std::vector<int> reversed_vertices;\n\
    \    std::vector<int> reversed_edges;\n    reversed_vertices.reserve(active_edge_count\
    \ + 1);\n    reversed_edges.reserve(active_edge_count);\n\n    while (!vertex_stack.empty())\
    \ {\n        const int vertex = vertex_stack.back();\n        while (cursor[vertex]\
    \ < int(graph[vertex].size())) {\n            const Edge<T>& edge = graph[vertex][cursor[vertex]];\n\
    \            if (edge.alive && !used[edge.id]) break;\n            cursor[vertex]++;\n\
    \        }\n\n        if (cursor[vertex] < int(graph[vertex].size())) {\n    \
    \        const Edge<T>& edge = graph[vertex][cursor[vertex]++];\n            used[edge.id]\
    \ = true;\n            vertex_stack.push_back(edge.to);\n            incoming_edge_stack.push_back(edge.id);\n\
    \            continue;\n        }\n\n        reversed_vertices.push_back(vertex);\n\
    \        const int incoming_edge = incoming_edge_stack.back();\n        if (incoming_edge\
    \ != -1) reversed_edges.push_back(incoming_edge);\n        vertex_stack.pop_back();\n\
    \        incoming_edge_stack.pop_back();\n    }\n\n    if (int(reversed_edges.size())\
    \ != active_edge_count) return std::nullopt;\n    std::reverse(reversed_vertices.begin(),\
    \ reversed_vertices.end());\n    std::reverse(reversed_edges.begin(), reversed_edges.end());\n\
    \    result.vertices = std::move(reversed_vertices);\n    result.edge_ids = std::move(reversed_edges);\n\
    \    return result;\n}\n\ntemplate <class T>\nstd::vector<int> edge_incidence_count(const\
    \ Graph<T>& graph) {\n    std::vector<int> count(graph.edge_count(), 0);\n   \
    \ for (int vertex = 0; vertex < graph.size(); vertex++) {\n        for (const\
    \ Edge<T>& edge : graph[vertex]) {\n            if (!edge.alive) continue;\n \
    \           assert(0 <= edge.id && edge.id < graph.edge_count());\n          \
    \  count[edge.id]++;\n        }\n    }\n    return count;\n}\n\n}  // namespace\
    \ internal\n\ntemplate <class T>\nstd::optional<EulerianTrail> directed_eulerian_trail(\n\
    \    const Graph<T>& graph,\n    int start = -1\n) {\n    assert(start == -1 ||\
    \ (0 <= start && start < graph.size()));\n    const int n = graph.size();\n  \
    \  std::vector<int> incidence = internal::edge_incidence_count(graph);\n    std::vector<int>\
    \ in_degree(n, 0);\n    std::vector<int> out_degree(n, 0);\n    int active_edge_count\
    \ = 0;\n    for (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>&\
    \ edge : graph[vertex]) {\n            if (!edge.alive) continue;\n          \
    \  out_degree[vertex]++;\n            in_degree[edge.to]++;\n        }\n    }\n\
    \    for (int count : incidence) {\n        if (count == 0) continue;\n      \
    \  assert(count == 1);\n        active_edge_count++;\n    }\n\n    int required_start\
    \ = -1;\n    int required_end = -1;\n    for (int vertex = 0; vertex < n; vertex++)\
    \ {\n        const int difference = out_degree[vertex] - in_degree[vertex];\n\
    \        if (difference == 1) {\n            if (required_start != -1) return\
    \ std::nullopt;\n            required_start = vertex;\n        } else if (difference\
    \ == -1) {\n            if (required_end != -1) return std::nullopt;\n       \
    \     required_end = vertex;\n        } else if (difference != 0) {\n        \
    \    return std::nullopt;\n        }\n    }\n    if ((required_start == -1) !=\
    \ (required_end == -1)) return std::nullopt;\n\n    int chosen_start = start;\n\
    \    if (active_edge_count == 0) {\n        if (chosen_start == -1 && n > 0) chosen_start\
    \ = 0;\n        return internal::hierholzer(graph, chosen_start, 0);\n    }\n\
    \    if (required_start != -1) {\n        if (chosen_start != -1 && chosen_start\
    \ != required_start) return std::nullopt;\n        chosen_start = required_start;\n\
    \    } else if (chosen_start == -1) {\n        for (int vertex = 0; vertex < n;\
    \ vertex++) {\n            if (out_degree[vertex] > 0) {\n                chosen_start\
    \ = vertex;\n                break;\n            }\n        }\n    } else if (out_degree[chosen_start]\
    \ == 0) {\n        return std::nullopt;\n    }\n    return internal::hierholzer(graph,\
    \ chosen_start, active_edge_count);\n}\n\ntemplate <class T>\nstd::optional<EulerianTrail>\
    \ undirected_eulerian_trail(\n    const Graph<T>& graph,\n    int start = -1\n\
    ) {\n    assert(start == -1 || (0 <= start && start < graph.size()));\n    const\
    \ int n = graph.size();\n    std::vector<int> incidence = internal::edge_incidence_count(graph);\n\
    \    std::vector<int> degree(n, 0);\n    int active_edge_count = 0;\n    for (int\
    \ vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex])\
    \ {\n            if (edge.alive) degree[vertex]++;\n        }\n    }\n    for\
    \ (int count : incidence) {\n        if (count == 0) continue;\n        assert(count\
    \ == 2);\n        active_edge_count++;\n    }\n\n    std::vector<int> odd;\n \
    \   for (int vertex = 0; vertex < n; vertex++) {\n        if (degree[vertex] &\
    \ 1) odd.push_back(vertex);\n    }\n    if (!odd.empty() && odd.size() != 2) return\
    \ std::nullopt;\n\n    int chosen_start = start;\n    if (active_edge_count ==\
    \ 0) {\n        if (chosen_start == -1 && n > 0) chosen_start = 0;\n        return\
    \ internal::hierholzer(graph, chosen_start, 0);\n    }\n    if (odd.size() ==\
    \ 2) {\n        if (chosen_start != -1 && chosen_start != odd[0] && chosen_start\
    \ != odd[1]) {\n            return std::nullopt;\n        }\n        if (chosen_start\
    \ == -1) chosen_start = odd[0];\n    } else if (chosen_start == -1) {\n      \
    \  for (int vertex = 0; vertex < n; vertex++) {\n            if (degree[vertex]\
    \ > 0) {\n                chosen_start = vertex;\n                break;\n   \
    \         }\n        }\n    } else if (degree[chosen_start] == 0) {\n        return\
    \ std::nullopt;\n    }\n    return internal::hierholzer(graph, chosen_start, active_edge_count);\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_EULERIAN_TRAIL_HPP\n#define M1UNE_GRAPH_EULERIAN_TRAIL_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"graph.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nstruct EulerianTrail {\n    std::vector<int> vertices;\n\
    \    std::vector<int> edge_ids;\n\n    int edge_count() const {\n        return\
    \ int(edge_ids.size());\n    }\n\n    bool is_circuit() const {\n        return\
    \ vertices.empty() || vertices.front() == vertices.back();\n    }\n};\n\nnamespace\
    \ internal {\n\ntemplate <class T>\nstd::optional<EulerianTrail> hierholzer(\n\
    \    const Graph<T>& graph,\n    int start,\n    int active_edge_count\n) {\n\
    \    EulerianTrail result;\n    if (active_edge_count == 0) {\n        if (start\
    \ != -1) result.vertices.push_back(start);\n        return result;\n    }\n\n\
    \    assert(0 <= start && start < graph.size());\n    std::vector<char> used(graph.edge_count(),\
    \ false);\n    std::vector<int> cursor(graph.size(), 0);\n    std::vector<int>\
    \ vertex_stack(1, start);\n    std::vector<int> incoming_edge_stack(1, -1);\n\
    \    std::vector<int> reversed_vertices;\n    std::vector<int> reversed_edges;\n\
    \    reversed_vertices.reserve(active_edge_count + 1);\n    reversed_edges.reserve(active_edge_count);\n\
    \n    while (!vertex_stack.empty()) {\n        const int vertex = vertex_stack.back();\n\
    \        while (cursor[vertex] < int(graph[vertex].size())) {\n            const\
    \ Edge<T>& edge = graph[vertex][cursor[vertex]];\n            if (edge.alive &&\
    \ !used[edge.id]) break;\n            cursor[vertex]++;\n        }\n\n       \
    \ if (cursor[vertex] < int(graph[vertex].size())) {\n            const Edge<T>&\
    \ edge = graph[vertex][cursor[vertex]++];\n            used[edge.id] = true;\n\
    \            vertex_stack.push_back(edge.to);\n            incoming_edge_stack.push_back(edge.id);\n\
    \            continue;\n        }\n\n        reversed_vertices.push_back(vertex);\n\
    \        const int incoming_edge = incoming_edge_stack.back();\n        if (incoming_edge\
    \ != -1) reversed_edges.push_back(incoming_edge);\n        vertex_stack.pop_back();\n\
    \        incoming_edge_stack.pop_back();\n    }\n\n    if (int(reversed_edges.size())\
    \ != active_edge_count) return std::nullopt;\n    std::reverse(reversed_vertices.begin(),\
    \ reversed_vertices.end());\n    std::reverse(reversed_edges.begin(), reversed_edges.end());\n\
    \    result.vertices = std::move(reversed_vertices);\n    result.edge_ids = std::move(reversed_edges);\n\
    \    return result;\n}\n\ntemplate <class T>\nstd::vector<int> edge_incidence_count(const\
    \ Graph<T>& graph) {\n    std::vector<int> count(graph.edge_count(), 0);\n   \
    \ for (int vertex = 0; vertex < graph.size(); vertex++) {\n        for (const\
    \ Edge<T>& edge : graph[vertex]) {\n            if (!edge.alive) continue;\n \
    \           assert(0 <= edge.id && edge.id < graph.edge_count());\n          \
    \  count[edge.id]++;\n        }\n    }\n    return count;\n}\n\n}  // namespace\
    \ internal\n\ntemplate <class T>\nstd::optional<EulerianTrail> directed_eulerian_trail(\n\
    \    const Graph<T>& graph,\n    int start = -1\n) {\n    assert(start == -1 ||\
    \ (0 <= start && start < graph.size()));\n    const int n = graph.size();\n  \
    \  std::vector<int> incidence = internal::edge_incidence_count(graph);\n    std::vector<int>\
    \ in_degree(n, 0);\n    std::vector<int> out_degree(n, 0);\n    int active_edge_count\
    \ = 0;\n    for (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>&\
    \ edge : graph[vertex]) {\n            if (!edge.alive) continue;\n          \
    \  out_degree[vertex]++;\n            in_degree[edge.to]++;\n        }\n    }\n\
    \    for (int count : incidence) {\n        if (count == 0) continue;\n      \
    \  assert(count == 1);\n        active_edge_count++;\n    }\n\n    int required_start\
    \ = -1;\n    int required_end = -1;\n    for (int vertex = 0; vertex < n; vertex++)\
    \ {\n        const int difference = out_degree[vertex] - in_degree[vertex];\n\
    \        if (difference == 1) {\n            if (required_start != -1) return\
    \ std::nullopt;\n            required_start = vertex;\n        } else if (difference\
    \ == -1) {\n            if (required_end != -1) return std::nullopt;\n       \
    \     required_end = vertex;\n        } else if (difference != 0) {\n        \
    \    return std::nullopt;\n        }\n    }\n    if ((required_start == -1) !=\
    \ (required_end == -1)) return std::nullopt;\n\n    int chosen_start = start;\n\
    \    if (active_edge_count == 0) {\n        if (chosen_start == -1 && n > 0) chosen_start\
    \ = 0;\n        return internal::hierholzer(graph, chosen_start, 0);\n    }\n\
    \    if (required_start != -1) {\n        if (chosen_start != -1 && chosen_start\
    \ != required_start) return std::nullopt;\n        chosen_start = required_start;\n\
    \    } else if (chosen_start == -1) {\n        for (int vertex = 0; vertex < n;\
    \ vertex++) {\n            if (out_degree[vertex] > 0) {\n                chosen_start\
    \ = vertex;\n                break;\n            }\n        }\n    } else if (out_degree[chosen_start]\
    \ == 0) {\n        return std::nullopt;\n    }\n    return internal::hierholzer(graph,\
    \ chosen_start, active_edge_count);\n}\n\ntemplate <class T>\nstd::optional<EulerianTrail>\
    \ undirected_eulerian_trail(\n    const Graph<T>& graph,\n    int start = -1\n\
    ) {\n    assert(start == -1 || (0 <= start && start < graph.size()));\n    const\
    \ int n = graph.size();\n    std::vector<int> incidence = internal::edge_incidence_count(graph);\n\
    \    std::vector<int> degree(n, 0);\n    int active_edge_count = 0;\n    for (int\
    \ vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex])\
    \ {\n            if (edge.alive) degree[vertex]++;\n        }\n    }\n    for\
    \ (int count : incidence) {\n        if (count == 0) continue;\n        assert(count\
    \ == 2);\n        active_edge_count++;\n    }\n\n    std::vector<int> odd;\n \
    \   for (int vertex = 0; vertex < n; vertex++) {\n        if (degree[vertex] &\
    \ 1) odd.push_back(vertex);\n    }\n    if (!odd.empty() && odd.size() != 2) return\
    \ std::nullopt;\n\n    int chosen_start = start;\n    if (active_edge_count ==\
    \ 0) {\n        if (chosen_start == -1 && n > 0) chosen_start = 0;\n        return\
    \ internal::hierholzer(graph, chosen_start, 0);\n    }\n    if (odd.size() ==\
    \ 2) {\n        if (chosen_start != -1 && chosen_start != odd[0] && chosen_start\
    \ != odd[1]) {\n            return std::nullopt;\n        }\n        if (chosen_start\
    \ == -1) chosen_start = odd[0];\n    } else if (chosen_start == -1) {\n      \
    \  for (int vertex = 0; vertex < n; vertex++) {\n            if (degree[vertex]\
    \ > 0) {\n                chosen_start = vertex;\n                break;\n   \
    \         }\n        }\n    } else if (degree[chosen_start] == 0) {\n        return\
    \ std::nullopt;\n    }\n    return internal::hierholzer(graph, chosen_start, active_edge_count);\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_EULERIAN_TRAIL_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/eulerian_trail.hpp
  requiredBy:
  - graph/directed.hpp
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-11 20:05:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/eulerian_trail_undirected.test.cpp
  - verify/graph/eulerian_trail_directed.test.cpp
documentation_of: graph/eulerian_trail.hpp
layout: document
title: Eulerian Trail
---

## Overview

An Eulerian trail uses every active edge exactly once. This header implements
iterative Hierholzer traversals for both directed and undirected graphs and
returns the original edge IDs alongside the visited vertices.

Parallel edges and self-loops are supported. Inactive edges are ignored.

## Graph Orientation

Use `directed_eulerian_trail` with graphs built by `add_directed_edge`, and
`undirected_eulerian_trail` with graphs built by `add_edge`. Mixing directed and
undirected edge representations in one call is not supported.

## API

```cpp
struct EulerianTrail {
    std::vector<int> vertices;
    std::vector<int> edge_ids;

    int edge_count() const;
    bool is_circuit() const;
};

template <class T>
std::optional<EulerianTrail> directed_eulerian_trail(
    const Graph<T>& graph,
    int start = -1
);

template <class T>
std::optional<EulerianTrail> undirected_eulerian_trail(
    const Graph<T>& graph,
    int start = -1
);
```

| Interface | Description | Complexity |
| --- | --- | --- |
| `vertices` | Trail vertices; for `M` used edges, contains `M + 1` vertices unless the graph itself has no vertices. | -- |
| `edge_ids` | Active edge IDs in traversal order. | -- |
| `edge_count()` | Number of edges in the trail. | $O(1)$ |
| `is_circuit()` | Whether the trail is closed. An empty-graph trail is considered closed. | $O(1)$ |
| `directed_eulerian_trail(graph, start)` | Finds a direction-respecting trail, if one exists. | $O(N + M)$ |
| `undirected_eulerian_trail(graph, start)` | Finds an undirected trail, if one exists. | $O(N + M)$ |

The default `start == -1` chooses a valid start automatically. Supplying a
vertex forces the trail to start there; the function returns `std::nullopt` if
an Eulerian trail exists only from another vertex. Invalid nonnegative start
indices are rejected by an assertion.

For a graph with vertices but no active edges, the automatically selected trail
contains vertex `0` and no edges. A forced start produces that one-vertex trail
instead. For a graph with no vertices, both returned sequences are empty.

The functions check degree conditions and confirm that Hierholzer's traversal
used every active edge, which also detects disconnected edge-bearing parts.
The graph is not mutated.

## Example

```cpp
#include "graph/eulerian_trail.hpp"
#include "graph/graph.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(3);
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(1, 2);
    graph.add_directed_edge(2, 0);

    auto trail = m1une::graph::directed_eulerian_trail(graph);
    std::cout << trail->is_circuit() << "\n";  // 1
    for (int edge_id : trail->edge_ids) std::cout << edge_id << " ";
    std::cout << "\n";
}
```
