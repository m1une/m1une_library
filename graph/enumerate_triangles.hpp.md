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
    path: verify/graph/enumerate_triangles.test.cpp
    title: verify/graph/enumerate_triangles.test.cpp
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
  bundledCode: "#line 1 \"graph/enumerate_triangles.hpp\"\n\n\n\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line\
    \ 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
    \ T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int\
    \ to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1),\
    \ cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1),\
    \ int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        _g[u].push_back(edge_type(u,\
    \ v, cost, id));\n        int v_idx = int(_g[v].size());\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
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
    \ m1une\n\n\n#line 9 \"graph/enumerate_triangles.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\ntemplate <class T, class Callback>\nvoid enumerate_triangles(const\
    \ Graph<T>& graph, Callback&& callback) {\n    const int n = graph.size();\n \
    \   const std::vector<Edge<T>> edges = graph.edges();\n\n    std::vector<int>\
    \ degree(n, 0);\n    for (const Edge<T>& edge : edges) {\n        assert(edge.from\
    \ != edge.to);\n        degree[edge.from]++;\n        degree[edge.to]++;\n   \
    \ }\n\n    std::vector<std::vector<int>> oriented(n);\n    for (const Edge<T>&\
    \ edge : edges) {\n        int from = edge.from;\n        int to = edge.to;\n\
    \        if (degree[from] > degree[to] ||\n            (degree[from] == degree[to]\
    \ && from > to)) {\n            std::swap(from, to);\n        }\n        oriented[from].push_back(to);\n\
    \    }\n\n    std::vector<int> marked(n, -1);\n    for (int vertex = 0; vertex\
    \ < n; vertex++) {\n        for (int to : oriented[vertex]) marked[to] = vertex;\n\
    \        for (int middle : oriented[vertex]) {\n            for (int to : oriented[middle])\
    \ {\n                if (marked[to] != vertex) continue;\n                int\
    \ first = vertex;\n                int second = middle;\n                int third\
    \ = to;\n                if (first > second) std::swap(first, second);\n     \
    \           if (second > third) std::swap(second, third);\n                if\
    \ (first > second) std::swap(first, second);\n                callback(first,\
    \ second, third);\n            }\n        }\n    }\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_ENUMERATE_TRIANGLES_HPP\n#define M1UNE_GRAPH_ENUMERATE_TRIANGLES_HPP\
    \ 1\n\n#include <cassert>\n#include <utility>\n#include <vector>\n\n#include \"\
    graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T, class\
    \ Callback>\nvoid enumerate_triangles(const Graph<T>& graph, Callback&& callback)\
    \ {\n    const int n = graph.size();\n    const std::vector<Edge<T>> edges = graph.edges();\n\
    \n    std::vector<int> degree(n, 0);\n    for (const Edge<T>& edge : edges) {\n\
    \        assert(edge.from != edge.to);\n        degree[edge.from]++;\n       \
    \ degree[edge.to]++;\n    }\n\n    std::vector<std::vector<int>> oriented(n);\n\
    \    for (const Edge<T>& edge : edges) {\n        int from = edge.from;\n    \
    \    int to = edge.to;\n        if (degree[from] > degree[to] ||\n           \
    \ (degree[from] == degree[to] && from > to)) {\n            std::swap(from, to);\n\
    \        }\n        oriented[from].push_back(to);\n    }\n\n    std::vector<int>\
    \ marked(n, -1);\n    for (int vertex = 0; vertex < n; vertex++) {\n        for\
    \ (int to : oriented[vertex]) marked[to] = vertex;\n        for (int middle :\
    \ oriented[vertex]) {\n            for (int to : oriented[middle]) {\n       \
    \         if (marked[to] != vertex) continue;\n                int first = vertex;\n\
    \                int second = middle;\n                int third = to;\n     \
    \           if (first > second) std::swap(first, second);\n                if\
    \ (second > third) std::swap(second, third);\n                if (first > second)\
    \ std::swap(first, second);\n                callback(first, second, third);\n\
    \            }\n        }\n    }\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GRAPH_ENUMERATE_TRIANGLES_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/enumerate_triangles.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-13 20:21:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/enumerate_triangles.test.cpp
documentation_of: graph/enumerate_triangles.hpp
layout: document
title: Enumerate Triangles
---

## Overview

`enumerate_triangles` visits every triangle in a simple graph exactly once.
Triangles are reported through a callback, so you can count them, aggregate
vertex values, or process them online without storing every triple.

The implementation orients edges by `(degree, vertex)` and intersects the
resulting forward neighborhoods. This avoids the cubic scan over all vertex
triples.

## Graph Requirements

The active edges must form a simple graph: self-loops and parallel edges are not
supported. Each active edge is interpreted as undirected, regardless of whether
it was inserted with `add_edge` or `add_directed_edge`. Edge costs are ignored,
and inactive edges are ignored.

## Callback

The callback signature is:

```cpp
callback(int first, int second, int third);
```

It is invoked exactly once per triangle. The vertex indices are always ordered
as `first < second < third`. The order in which different triangles are visited
is unspecified.

## Function

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `enumerate_triangles` | `template <class T, class Callback> void enumerate_triangles(const Graph<T>& graph, Callback&& callback)` | Invokes the callback once for every triangle. Does not mutate `graph`. | $O(N + M\sqrt M + K F)$ time and $O(N + M)$ memory, where $M$ is the number of active edges, $K$ is the number of triangles, and $F$ is the cost of one callback. |

## Example

```cpp
#include "graph/enumerate_triangles.hpp"
#include "graph/graph.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);
    graph.add_edge(2, 3);

    std::vector<long long> value = {2, 3, 5, 7};
    long long sum = 0;
    m1une::graph::enumerate_triangles(
        graph,
        [&](int first, int second, int third) {
            sum += value[first] * value[second] * value[third];
        }
    );
    std::cout << sum << "\n";  // 30
}
```
