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
    path: verify/graph/enumerate_cliques.test.cpp
    title: verify/graph/enumerate_cliques.test.cpp
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
  bundledCode: "#line 1 \"graph/enumerate_cliques.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    template <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
    \    int to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1),\
    \ to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_\
    \ = T(1), int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
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
    \ m1une\n\n\n#line 10 \"graph/enumerate_cliques.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\n// Invokes callback once for every nonempty clique. The callback\
    \ receives a\n// const reference to a temporary vector that is reused after it\
    \ returns.\ntemplate <class T, class Callback>\nvoid enumerate_cliques(const Graph<T>&\
    \ graph, Callback&& callback) {\n    const int n = graph.size();\n    std::vector<std::vector<int>>\
    \ adjacency(n);\n    for (const Edge<T>& edge : graph.edges()) {\n        assert(edge.from\
    \ != edge.to);\n        if (edge.from == edge.to) continue;\n        adjacency[edge.from].push_back(edge.to);\n\
    \        adjacency[edge.to].push_back(edge.from);\n    }\n\n    for (std::vector<int>&\
    \ neighbors : adjacency) {\n        std::sort(neighbors.begin(), neighbors.end());\n\
    #ifndef NDEBUG\n        for (int i = 1; i < int(neighbors.size()); i++) {\n  \
    \          assert(neighbors[i - 1] != neighbors[i]);\n        }\n#endif\n    \
    \    neighbors.erase(\n            std::unique(neighbors.begin(), neighbors.end()),\n\
    \            neighbors.end()\n        );\n    }\n\n    int maximum_degree = 0;\n\
    \    std::vector<int> degree(n);\n    for (int vertex = 0; vertex < n; vertex++)\
    \ {\n        degree[vertex] = int(adjacency[vertex].size());\n        maximum_degree\
    \ = std::max(maximum_degree, degree[vertex]);\n    }\n\n    // Compute a degeneracy\
    \ ordering in linear time. A clique is assigned to\n    // its first vertex in\
    \ this ordering, and all its other vertices are among\n    // that vertex's forward\
    \ neighbors.\n    std::vector<std::vector<int>> bucket(maximum_degree + 1);\n\
    \    for (int vertex = 0; vertex < n; vertex++) {\n        bucket[degree[vertex]].push_back(vertex);\n\
    \    }\n    std::vector<char> active(n, true);\n    std::vector<std::vector<int>>\
    \ forward(n);\n    int minimum_degree = 0;\n    int degeneracy = 0;\n    for (int\
    \ removed = 0; removed < n; removed++) {\n        while (true) {\n           \
    \ while (bucket[minimum_degree].empty()) minimum_degree++;\n            int vertex\
    \ = bucket[minimum_degree].back();\n            if (active[vertex] && degree[vertex]\
    \ == minimum_degree) break;\n            bucket[minimum_degree].pop_back();\n\
    \        }\n\n        int vertex = bucket[minimum_degree].back();\n        bucket[minimum_degree].pop_back();\n\
    \        active[vertex] = false;\n        degeneracy = std::max(degeneracy, minimum_degree);\n\
    \        forward[vertex].reserve(minimum_degree);\n        for (int to : adjacency[vertex])\
    \ {\n            if (!active[to]) continue;\n            forward[vertex].push_back(to);\n\
    \            degree[to]--;\n            bucket[degree[to]].push_back(to);\n  \
    \          minimum_degree = std::min(minimum_degree, degree[to]);\n        }\n\
    \    }\n\n    std::vector<int> clique;\n    clique.reserve(degeneracy + 1);\n\
    \    std::vector<std::vector<int>> candidates(degeneracy + 1);\n    for (int vertex\
    \ = 0; vertex < n; vertex++) {\n        const std::vector<int>& neighbors = forward[vertex];\n\
    \        const int neighbor_count = int(neighbors.size());\n\n        clique.clear();\n\
    \        clique.push_back(vertex);\n        callback(std::as_const(clique));\n\
    \        if (neighbor_count == 0) continue;\n\n        std::vector<char> connected(\n\
    \            std::size_t(neighbor_count) * neighbor_count,\n            false\n\
    \        );\n        for (int first = 0; first < neighbor_count; first++) {\n\
    \            for (int second = first + 1; second < neighbor_count; second++) {\n\
    \                bool adjacent = std::binary_search(\n                    adjacency[neighbors[first]].begin(),\n\
    \                    adjacency[neighbors[first]].end(),\n                    neighbors[second]\n\
    \                );\n                connected[std::size_t(first) * neighbor_count\
    \ + second] =\n                    adjacent;\n                connected[std::size_t(second)\
    \ * neighbor_count + first] =\n                    adjacent;\n            }\n\
    \        }\n\n        candidates[0].resize(neighbor_count);\n        for (int\
    \ i = 0; i < neighbor_count; i++) candidates[0][i] = i;\n        auto enumerate\
    \ = [&](auto&& self, int depth) -> void {\n            const std::vector<int>&\
    \ current = candidates[depth];\n            for (int position = 0; position <\
    \ int(current.size()); position++) {\n                int chosen = current[position];\n\
    \                clique.push_back(neighbors[chosen]);\n                callback(std::as_const(clique));\n\
    \n                std::vector<int>& next = candidates[depth + 1];\n          \
    \      next.clear();\n                for (int next_position = position + 1;\n\
    \                     next_position < int(current.size());\n                 \
    \    next_position++) {\n                    int candidate = current[next_position];\n\
    \                    if (connected[\n                            std::size_t(chosen)\
    \ * neighbor_count + candidate\n                        ]) {\n               \
    \         next.push_back(candidate);\n                    }\n                }\n\
    \                if (!next.empty()) self(self, depth + 1);\n                clique.pop_back();\n\
    \            }\n        };\n        enumerate(enumerate, 0);\n    }\n}\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_ENUMERATE_CLIQUES_HPP\n#define M1UNE_GRAPH_ENUMERATE_CLIQUES_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\
    \n// Invokes callback once for every nonempty clique. The callback receives a\n\
    // const reference to a temporary vector that is reused after it returns.\ntemplate\
    \ <class T, class Callback>\nvoid enumerate_cliques(const Graph<T>& graph, Callback&&\
    \ callback) {\n    const int n = graph.size();\n    std::vector<std::vector<int>>\
    \ adjacency(n);\n    for (const Edge<T>& edge : graph.edges()) {\n        assert(edge.from\
    \ != edge.to);\n        if (edge.from == edge.to) continue;\n        adjacency[edge.from].push_back(edge.to);\n\
    \        adjacency[edge.to].push_back(edge.from);\n    }\n\n    for (std::vector<int>&\
    \ neighbors : adjacency) {\n        std::sort(neighbors.begin(), neighbors.end());\n\
    #ifndef NDEBUG\n        for (int i = 1; i < int(neighbors.size()); i++) {\n  \
    \          assert(neighbors[i - 1] != neighbors[i]);\n        }\n#endif\n    \
    \    neighbors.erase(\n            std::unique(neighbors.begin(), neighbors.end()),\n\
    \            neighbors.end()\n        );\n    }\n\n    int maximum_degree = 0;\n\
    \    std::vector<int> degree(n);\n    for (int vertex = 0; vertex < n; vertex++)\
    \ {\n        degree[vertex] = int(adjacency[vertex].size());\n        maximum_degree\
    \ = std::max(maximum_degree, degree[vertex]);\n    }\n\n    // Compute a degeneracy\
    \ ordering in linear time. A clique is assigned to\n    // its first vertex in\
    \ this ordering, and all its other vertices are among\n    // that vertex's forward\
    \ neighbors.\n    std::vector<std::vector<int>> bucket(maximum_degree + 1);\n\
    \    for (int vertex = 0; vertex < n; vertex++) {\n        bucket[degree[vertex]].push_back(vertex);\n\
    \    }\n    std::vector<char> active(n, true);\n    std::vector<std::vector<int>>\
    \ forward(n);\n    int minimum_degree = 0;\n    int degeneracy = 0;\n    for (int\
    \ removed = 0; removed < n; removed++) {\n        while (true) {\n           \
    \ while (bucket[minimum_degree].empty()) minimum_degree++;\n            int vertex\
    \ = bucket[minimum_degree].back();\n            if (active[vertex] && degree[vertex]\
    \ == minimum_degree) break;\n            bucket[minimum_degree].pop_back();\n\
    \        }\n\n        int vertex = bucket[minimum_degree].back();\n        bucket[minimum_degree].pop_back();\n\
    \        active[vertex] = false;\n        degeneracy = std::max(degeneracy, minimum_degree);\n\
    \        forward[vertex].reserve(minimum_degree);\n        for (int to : adjacency[vertex])\
    \ {\n            if (!active[to]) continue;\n            forward[vertex].push_back(to);\n\
    \            degree[to]--;\n            bucket[degree[to]].push_back(to);\n  \
    \          minimum_degree = std::min(minimum_degree, degree[to]);\n        }\n\
    \    }\n\n    std::vector<int> clique;\n    clique.reserve(degeneracy + 1);\n\
    \    std::vector<std::vector<int>> candidates(degeneracy + 1);\n    for (int vertex\
    \ = 0; vertex < n; vertex++) {\n        const std::vector<int>& neighbors = forward[vertex];\n\
    \        const int neighbor_count = int(neighbors.size());\n\n        clique.clear();\n\
    \        clique.push_back(vertex);\n        callback(std::as_const(clique));\n\
    \        if (neighbor_count == 0) continue;\n\n        std::vector<char> connected(\n\
    \            std::size_t(neighbor_count) * neighbor_count,\n            false\n\
    \        );\n        for (int first = 0; first < neighbor_count; first++) {\n\
    \            for (int second = first + 1; second < neighbor_count; second++) {\n\
    \                bool adjacent = std::binary_search(\n                    adjacency[neighbors[first]].begin(),\n\
    \                    adjacency[neighbors[first]].end(),\n                    neighbors[second]\n\
    \                );\n                connected[std::size_t(first) * neighbor_count\
    \ + second] =\n                    adjacent;\n                connected[std::size_t(second)\
    \ * neighbor_count + first] =\n                    adjacent;\n            }\n\
    \        }\n\n        candidates[0].resize(neighbor_count);\n        for (int\
    \ i = 0; i < neighbor_count; i++) candidates[0][i] = i;\n        auto enumerate\
    \ = [&](auto&& self, int depth) -> void {\n            const std::vector<int>&\
    \ current = candidates[depth];\n            for (int position = 0; position <\
    \ int(current.size()); position++) {\n                int chosen = current[position];\n\
    \                clique.push_back(neighbors[chosen]);\n                callback(std::as_const(clique));\n\
    \n                std::vector<int>& next = candidates[depth + 1];\n          \
    \      next.clear();\n                for (int next_position = position + 1;\n\
    \                     next_position < int(current.size());\n                 \
    \    next_position++) {\n                    int candidate = current[next_position];\n\
    \                    if (connected[\n                            std::size_t(chosen)\
    \ * neighbor_count + candidate\n                        ]) {\n               \
    \         next.push_back(candidate);\n                    }\n                }\n\
    \                if (!next.empty()) self(self, depth + 1);\n                clique.pop_back();\n\
    \            }\n        };\n        enumerate(enumerate, 0);\n    }\n}\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_ENUMERATE_CLIQUES_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/enumerate_cliques.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-16 19:22:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/enumerate_cliques.test.cpp
  - verify/graph/range_edge_graph.test.cpp
documentation_of: graph/enumerate_cliques.hpp
layout: document
title: Enumerate Cliques
---

## Overview

`enumerate_cliques` visits every nonempty clique of a simple graph exactly once.
Cliques are reported through a callback, allowing their values to be aggregated
without storing every result.

The implementation computes a degeneracy ordering and assigns each clique to
its first vertex in that ordering. It then enumerates cliques inside that
vertex's forward neighborhood. This limits the exponential part to the graph's
degeneracy rather than its total vertex count.

## Graph Requirements

The active edges must form a simple graph: self-loops and parallel edges are not
supported. Each active edge is interpreted as undirected, including edges added
with `add_directed_edge`. Edge costs are ignored and inactive edges are ignored.

## Callback

The callback signature is:

```cpp
callback(const std::vector<int>& clique);
```

It is invoked exactly once for every nonempty clique, including single-vertex
cliques. Vertex and clique order are unspecified. The vector is reused by the
enumerator, so copy it if it must remain available after the callback returns.
The callback must not mutate the graph.

## Function

| Function | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| `enumerate_cliques` | `template <class T, class Callback> void enumerate_cliques(const Graph<T>& graph, Callback&& callback)` | Invokes `callback` once for every nonempty clique without mutating `graph`. | $O(N + M + Md\log N + K(d + F))$ time and $O(N + M + d^2)$ memory |

Here, `d` is the graph degeneracy, `K` is the number of nonempty cliques, and
`F` is the cost of one callback. Since $d = O(\sqrt M)$ for a simple graph, the
bound is practical for sparse graphs whose clique output is manageable.

## Example

```cpp
#include "graph/enumerate_cliques.hpp"
#include "graph/graph.hpp"

#include <cassert>
#include <vector>

int main() {
    m1une::graph::Graph<> graph(3);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);

    int count = 0;
    m1une::graph::enumerate_cliques(
        graph,
        [&](const std::vector<int>&) { count++; }
    );
    assert(count == 7);
}
```
