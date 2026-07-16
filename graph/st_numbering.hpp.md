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
    path: verify/graph/st_numbering.test.cpp
    title: verify/graph/st_numbering.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/st_numbering.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 5 \"graph/graph.hpp\"\n\
    #include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type = T;\n\
    \n    int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\n  \
    \  Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int\
    \ from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ = true)\n        :\
    \ from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\n    int other(int\
    \ v) const {\n        assert(v == from || v == to);\n        return from ^ to\
    \ ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph {\n    using edge_type\
    \ = Edge<T>;\n    using cost_type = T;\n\n   private:\n    int _n;\n    int _edge_count;\n\
    \    std::vector<std::vector<edge_type>> _g;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _edge_positions;\n\n   public:\n    Graph() : _n(0), _edge_count(0) {}\n\
    \    explicit Graph(int n) : _n(n), _edge_count(0), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int edge_count() const\
    \ {\n        return _edge_count;\n    }\n\n    int add_vertex() {\n        _g.emplace_back();\n\
    \        return _n++;\n    }\n\n    int add_directed_edge(int from, int to, T\
    \ cost = T(1)) {\n        assert(0 <= from && from < _n);\n        assert(0 <=\
    \ to && to < _n);\n        int id = _edge_count++;\n        int idx = int(_g[from].size());\n\
    \        _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
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
    \ m1une\n\n\n#line 8 \"graph/st_numbering.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\n// Returns ranks p with p[source] = 0 and p[sink] = n - 1 such that\
    \ every\n// other vertex has neighbors of both smaller and larger rank. Returns\
    \ an empty\n// vector when no such numbering exists.\ntemplate <class T>\nstd::vector<int>\
    \ st_numbering(\n    const Graph<T>& graph,\n    int source,\n    int sink\n)\
    \ {\n    const int n = graph.size();\n    assert(0 < n);\n    assert(0 <= source\
    \ && source < n);\n    assert(0 <= sink && sink < n);\n    assert(source != sink);\n\
    \n#ifndef NDEBUG\n    std::vector<int> incidence_count(graph.edge_count(), 0);\n\
    \    for (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>&\
    \ edge : graph[vertex]) {\n            if (!edge.alive) continue;\n          \
    \  assert(0 <= edge.id && edge.id < graph.edge_count());\n            incidence_count[edge.id]++;\n\
    \        }\n    }\n    for (int edge_id = 0; edge_id < graph.edge_count(); edge_id++)\
    \ {\n        if (graph.is_edge_alive(edge_id)) {\n            assert(incidence_count[edge_id]\
    \ == 2);\n        }\n    }\n#endif\n\n    std::vector<int> parent(n, -1);\n  \
    \  std::vector<int> preorder(n, -1);\n    std::vector<int> low_vertex(n, -1);\n\
    \    std::vector<int> next_edge(n, 0);\n    std::vector<int> traversal;\n    traversal.reserve(n);\n\
    \n    preorder[source] = 0;\n    low_vertex[source] = source;\n    traversal.push_back(source);\n\
    \    preorder[sink] = 1;\n    low_vertex[sink] = sink;\n    traversal.push_back(sink);\n\
    \n    std::vector<int> stack(1, sink);\n    while (!stack.empty()) {\n       \
    \ const int vertex = stack.back();\n        if (next_edge[vertex] < int(graph[vertex].size()))\
    \ {\n            const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n \
    \           if (!edge.alive || edge.to == vertex) continue;\n            const\
    \ int to = edge.to;\n            if (preorder[to] == -1) {\n                parent[to]\
    \ = vertex;\n                preorder[to] = int(traversal.size());\n         \
    \       low_vertex[to] = to;\n                traversal.push_back(to);\n     \
    \           stack.push_back(to);\n            } else if (preorder[to] < preorder[low_vertex[vertex]])\
    \ {\n                low_vertex[vertex] = to;\n            }\n            continue;\n\
    \        }\n\n        stack.pop_back();\n        const int parent_vertex = parent[vertex];\n\
    \        if (parent_vertex != -1 &&\n            preorder[low_vertex[vertex]]\
    \ <\n                preorder[low_vertex[parent_vertex]]) {\n            low_vertex[parent_vertex]\
    \ = low_vertex[vertex];\n        }\n    }\n    if (int(traversal.size()) != n)\
    \ return {};\n\n    std::vector<int> next(n, -1);\n    std::vector<int> previous(n,\
    \ -1);\n    std::vector<int> sign(n, 0);\n    next[source] = sink;\n    previous[sink]\
    \ = source;\n    sign[source] = -1;\n\n    for (int index = 2; index < n; index++)\
    \ {\n        const int vertex = traversal[index];\n        const int parent_vertex\
    \ = parent[vertex];\n        assert(parent_vertex != -1);\n        if (sign[low_vertex[vertex]]\
    \ == -1) {\n            const int before = previous[parent_vertex];\n        \
    \    if (before == -1) return {};\n            next[before] = vertex;\n      \
    \      next[vertex] = parent_vertex;\n            previous[vertex] = before;\n\
    \            previous[parent_vertex] = vertex;\n            sign[parent_vertex]\
    \ = 1;\n        } else {\n            const int after = next[parent_vertex];\n\
    \            if (after == -1) return {};\n            next[parent_vertex] = vertex;\n\
    \            next[vertex] = after;\n            previous[vertex] = parent_vertex;\n\
    \            previous[after] = vertex;\n            sign[parent_vertex] = -1;\n\
    \        }\n    }\n\n    std::vector<int> order;\n    order.reserve(n);\n    int\
    \ vertex = source;\n    while (vertex != -1 && int(order.size()) <= n) {\n   \
    \     order.push_back(vertex);\n        if (vertex == sink) break;\n        vertex\
    \ = next[vertex];\n    }\n    if (int(order.size()) != n || order.back() != sink)\
    \ return {};\n\n    std::vector<int> rank(n, -1);\n    for (int index = 0; index\
    \ < n; index++) rank[order[index]] = index;\n\n    for (int index = 0; index <\
    \ n; index++) {\n        const int current = order[index];\n        bool has_smaller\
    \ = false;\n        bool has_larger = false;\n        for (const Edge<T>& edge\
    \ : graph[current]) {\n            if (!edge.alive || edge.to == current) continue;\n\
    \            has_smaller = has_smaller || rank[edge.to] < index;\n           \
    \ has_larger = has_larger || index < rank[edge.to];\n        }\n        if (index\
    \ > 0 && !has_smaller) return {};\n        if (index + 1 < n && !has_larger) return\
    \ {};\n    }\n    return rank;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_GRAPH_ST_NUMBERING_HPP\n#define M1UNE_GRAPH_ST_NUMBERING_HPP\
    \ 1\n\n#include <cassert>\n#include <vector>\n\n#include \"graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\n// Returns ranks p with p[source] = 0 and p[sink]\
    \ = n - 1 such that every\n// other vertex has neighbors of both smaller and larger\
    \ rank. Returns an empty\n// vector when no such numbering exists.\ntemplate <class\
    \ T>\nstd::vector<int> st_numbering(\n    const Graph<T>& graph,\n    int source,\n\
    \    int sink\n) {\n    const int n = graph.size();\n    assert(0 < n);\n    assert(0\
    \ <= source && source < n);\n    assert(0 <= sink && sink < n);\n    assert(source\
    \ != sink);\n\n#ifndef NDEBUG\n    std::vector<int> incidence_count(graph.edge_count(),\
    \ 0);\n    for (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>&\
    \ edge : graph[vertex]) {\n            if (!edge.alive) continue;\n          \
    \  assert(0 <= edge.id && edge.id < graph.edge_count());\n            incidence_count[edge.id]++;\n\
    \        }\n    }\n    for (int edge_id = 0; edge_id < graph.edge_count(); edge_id++)\
    \ {\n        if (graph.is_edge_alive(edge_id)) {\n            assert(incidence_count[edge_id]\
    \ == 2);\n        }\n    }\n#endif\n\n    std::vector<int> parent(n, -1);\n  \
    \  std::vector<int> preorder(n, -1);\n    std::vector<int> low_vertex(n, -1);\n\
    \    std::vector<int> next_edge(n, 0);\n    std::vector<int> traversal;\n    traversal.reserve(n);\n\
    \n    preorder[source] = 0;\n    low_vertex[source] = source;\n    traversal.push_back(source);\n\
    \    preorder[sink] = 1;\n    low_vertex[sink] = sink;\n    traversal.push_back(sink);\n\
    \n    std::vector<int> stack(1, sink);\n    while (!stack.empty()) {\n       \
    \ const int vertex = stack.back();\n        if (next_edge[vertex] < int(graph[vertex].size()))\
    \ {\n            const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n \
    \           if (!edge.alive || edge.to == vertex) continue;\n            const\
    \ int to = edge.to;\n            if (preorder[to] == -1) {\n                parent[to]\
    \ = vertex;\n                preorder[to] = int(traversal.size());\n         \
    \       low_vertex[to] = to;\n                traversal.push_back(to);\n     \
    \           stack.push_back(to);\n            } else if (preorder[to] < preorder[low_vertex[vertex]])\
    \ {\n                low_vertex[vertex] = to;\n            }\n            continue;\n\
    \        }\n\n        stack.pop_back();\n        const int parent_vertex = parent[vertex];\n\
    \        if (parent_vertex != -1 &&\n            preorder[low_vertex[vertex]]\
    \ <\n                preorder[low_vertex[parent_vertex]]) {\n            low_vertex[parent_vertex]\
    \ = low_vertex[vertex];\n        }\n    }\n    if (int(traversal.size()) != n)\
    \ return {};\n\n    std::vector<int> next(n, -1);\n    std::vector<int> previous(n,\
    \ -1);\n    std::vector<int> sign(n, 0);\n    next[source] = sink;\n    previous[sink]\
    \ = source;\n    sign[source] = -1;\n\n    for (int index = 2; index < n; index++)\
    \ {\n        const int vertex = traversal[index];\n        const int parent_vertex\
    \ = parent[vertex];\n        assert(parent_vertex != -1);\n        if (sign[low_vertex[vertex]]\
    \ == -1) {\n            const int before = previous[parent_vertex];\n        \
    \    if (before == -1) return {};\n            next[before] = vertex;\n      \
    \      next[vertex] = parent_vertex;\n            previous[vertex] = before;\n\
    \            previous[parent_vertex] = vertex;\n            sign[parent_vertex]\
    \ = 1;\n        } else {\n            const int after = next[parent_vertex];\n\
    \            if (after == -1) return {};\n            next[parent_vertex] = vertex;\n\
    \            next[vertex] = after;\n            previous[vertex] = parent_vertex;\n\
    \            previous[after] = vertex;\n            sign[parent_vertex] = -1;\n\
    \        }\n    }\n\n    std::vector<int> order;\n    order.reserve(n);\n    int\
    \ vertex = source;\n    while (vertex != -1 && int(order.size()) <= n) {\n   \
    \     order.push_back(vertex);\n        if (vertex == sink) break;\n        vertex\
    \ = next[vertex];\n    }\n    if (int(order.size()) != n || order.back() != sink)\
    \ return {};\n\n    std::vector<int> rank(n, -1);\n    for (int index = 0; index\
    \ < n; index++) rank[order[index]] = index;\n\n    for (int index = 0; index <\
    \ n; index++) {\n        const int current = order[index];\n        bool has_smaller\
    \ = false;\n        bool has_larger = false;\n        for (const Edge<T>& edge\
    \ : graph[current]) {\n            if (!edge.alive || edge.to == current) continue;\n\
    \            has_smaller = has_smaller || rank[edge.to] < index;\n           \
    \ has_larger = has_larger || index < rank[edge.to];\n        }\n        if (index\
    \ > 0 && !has_smaller) return {};\n        if (index + 1 < n && !has_larger) return\
    \ {};\n    }\n    return rank;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n#endif  // M1UNE_GRAPH_ST_NUMBERING_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/st_numbering.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-16 23:38:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/st_numbering.test.cpp
documentation_of: graph/st_numbering.hpp
layout: document
title: st-Numbering
---

## Overview

`st_numbering(graph, source, sink)` finds a bipolar numbering of an undirected
graph. It returns a rank `p[v]` for every vertex such that:

- `p` is a permutation of `0, ..., N - 1`;
- `p[source] = 0` and `p[sink] = N - 1`;
- every other vertex has an active neighbor of smaller rank and an active
  neighbor of larger rank.

Orienting every edge from smaller to larger rank then gives, for every vertex,
a directed path from `source` through that vertex to `sink`. If no such
numbering exists, the function returns an empty vector.

## Graph Requirements

Build the undirected graph with `Graph<T>::add_edge`. The graph must contain at
least two vertices, and `source` and `sink` must be distinct valid vertices.

Parallel edges are supported. Inactive edges and self-loops are ignored. The
algorithm is iterative and does not mutate the graph.

## API

```cpp
template <class T>
std::vector<int> st_numbering(
    const Graph<T>& graph,
    int source,
    int sink
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `st_numbering(graph, source, sink)` | Returns vertex ranks, or an empty vector when impossible. | `O(N + M)` time and `O(N)` auxiliary memory |

Here `M` is the number of active undirected edges. The returned vector is indexed by
vertex, not by rank: `result[v]` is the number assigned to `v`.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/st_numbering.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    auto rank = m1une::graph::st_numbering(graph, 0, 3);
    for (int vertex = 0; vertex < graph.size(); vertex++) {
        std::cout << rank[vertex] << "\n";
    }
}
```
