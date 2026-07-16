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
    path: verify/graph/count_four_cycles.test.cpp
    title: verify/graph/count_four_cycles.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
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
  bundledCode: "#line 1 \"graph/count_four_cycles.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    #line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type\
    \ = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\
    \n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int\
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
    \ m1une\n\n\n#line 11 \"graph/count_four_cycles.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nnamespace four_cycle_detail {\n\n// Counts C4s containing one particular\
    \ copy of each edge in a simple graph\n// whose edge weights represent parallel-edge\
    \ multiplicities.\ninline std::vector<long long> count_simple_per_edge(\n    int\
    \ vertex_count,\n    std::vector<int> first,\n    std::vector<int> second,\n \
    \   const std::vector<long long>& multiplicity\n) {\n    const int edge_count\
    \ = int(first.size());\n    assert(second.size() == first.size());\n    assert(multiplicity.size()\
    \ == first.size());\n\n    std::vector<int> degree(vertex_count, 0);\n    for\
    \ (int edge = 0; edge < edge_count; edge++) {\n        degree[first[edge]]++;\n\
    \        degree[second[edge]]++;\n    }\n\n    int maximum_degree = 0;\n    for\
    \ (int value : degree) maximum_degree = std::max(maximum_degree, value);\n   \
    \ std::vector<int> degree_start(maximum_degree + 2, 0);\n    for (int value :\
    \ degree) degree_start[value + 1]++;\n    for (int value = 0; value <= maximum_degree;\
    \ value++) {\n        degree_start[value + 1] += degree_start[value];\n    }\n\
    \    std::vector<int> cursor = degree_start;\n    std::vector<int> order(vertex_count);\n\
    \    for (int vertex = 0; vertex < vertex_count; vertex++) {\n        order[cursor[degree[vertex]]++]\
    \ = vertex;\n    }\n    std::vector<int> rank(vertex_count);\n    for (int i =\
    \ 0; i < vertex_count; i++) rank[order[i]] = i;\n    for (int edge = 0; edge <\
    \ edge_count; edge++) {\n        first[edge] = rank[first[edge]];\n        second[edge]\
    \ = rank[second[edge]];\n        if (first[edge] < second[edge]) {\n         \
    \   std::swap(first[edge], second[edge]);\n        }\n    }\n\n    std::vector<int>\
    \ start(vertex_count + 1, 0);\n    for (int vertex = 0; vertex < vertex_count;\
    \ vertex++) {\n        start[vertex + 1] = start[vertex] + degree[order[vertex]];\n\
    \    }\n    std::vector<int> end = start;\n    std::vector<int> edge_at(2 * edge_count);\n\
    \    std::vector<int> to(2 * edge_count);\n    for (int edge = 0; edge < edge_count;\
    \ edge++) {\n        int position = end[first[edge]]++;\n        edge_at[position]\
    \ = edge;\n        to[position] = second[edge];\n    }\n\n    std::vector<int>\
    \ downward_end = end;\n    for (int vertex = 0; vertex < vertex_count; vertex++)\
    \ {\n        for (int i = start[vertex]; i < downward_end[vertex]; i++) {\n  \
    \          int edge = edge_at[i];\n            int neighbor = to[i];\n       \
    \     int position = end[neighbor]++;\n            edge_at[position] = edge;\n\
    \            to[position] = vertex;\n        }\n    }\n\n    std::vector<long\
    \ long> path_count(vertex_count, 0);\n    std::vector<long long> result(edge_count,\
    \ 0);\n    for (int vertex = vertex_count - 1; vertex >= 0; vertex--) {\n    \
    \    for (int i = start[vertex]; i < end[vertex]; i++) {\n            int first_edge\
    \ = edge_at[i];\n            int middle = to[i];\n            end[middle]--;\n\
    \            for (int j = start[middle]; j < end[middle]; j++) {\n           \
    \     int second_edge = edge_at[j];\n                int opposite = to[j];\n \
    \               path_count[opposite] +=\n                    multiplicity[first_edge]\
    \ * multiplicity[second_edge];\n            }\n        }\n\n        for (int i\
    \ = start[vertex]; i < end[vertex]; i++) {\n            int first_edge = edge_at[i];\n\
    \            int middle = to[i];\n            for (int j = start[middle]; j <\
    \ end[middle]; j++) {\n                int second_edge = edge_at[j];\n       \
    \         int opposite = to[j];\n                long long other_paths =\n   \
    \                 path_count[opposite] -\n                    multiplicity[first_edge]\
    \ * multiplicity[second_edge];\n                result[first_edge] +=\n      \
    \              other_paths * multiplicity[second_edge];\n                result[second_edge]\
    \ +=\n                    other_paths * multiplicity[first_edge];\n          \
    \  }\n        }\n\n        for (int i = start[vertex]; i < end[vertex]; i++) {\n\
    \            int middle = to[i];\n            for (int j = start[middle]; j <\
    \ end[middle]; j++) {\n                path_count[to[j]] = 0;\n            }\n\
    \        }\n    }\n    return result;\n}\n\n}  // namespace four_cycle_detail\n\
    \n// Returns, for every graph edge id, the number of C4 subgraphs containing it.\n\
    // Parallel active edges are distinct choices; inactive edges receive zero.\n\
    template <class T>\nstd::vector<long long> count_four_cycles_per_edge(const Graph<T>&\
    \ graph) {\n    struct ActiveEdge {\n        int first;\n        int second;\n\
    \        int id;\n    };\n\n    std::vector<ActiveEdge> active_edges;\n    active_edges.reserve(graph.edge_count());\n\
    \    for (const Edge<T>& edge : graph.edges()) {\n        assert(edge.from !=\
    \ edge.to);\n        assert(0 <= edge.id && edge.id < graph.edge_count());\n \
    \       if (edge.from == edge.to) continue;\n        active_edges.push_back(ActiveEdge{\n\
    \            std::min(edge.from, edge.to),\n            std::max(edge.from, edge.to),\n\
    \            edge.id\n        });\n    }\n    std::sort(\n        active_edges.begin(),\n\
    \        active_edges.end(),\n        [](const ActiveEdge& left, const ActiveEdge&\
    \ right) {\n            return std::tie(left.first, left.second) <\n         \
    \          std::tie(right.first, right.second);\n        }\n    );\n\n    std::vector<int>\
    \ first;\n    std::vector<int> second;\n    std::vector<long long> multiplicity;\n\
    \    std::vector<int> group_of_edge(graph.edge_count(), -1);\n    first.reserve(active_edges.size());\n\
    \    second.reserve(active_edges.size());\n    multiplicity.reserve(active_edges.size());\n\
    \    for (const ActiveEdge& edge : active_edges) {\n        if (first.empty()\
    \ || first.back() != edge.first ||\n            second.back() != edge.second)\
    \ {\n            first.push_back(edge.first);\n            second.push_back(edge.second);\n\
    \            multiplicity.push_back(0);\n        }\n        multiplicity.back()++;\n\
    \        group_of_edge[edge.id] = int(first.size()) - 1;\n    }\n\n    std::vector<long\
    \ long> simple_result =\n        four_cycle_detail::count_simple_per_edge(\n \
    \           graph.size(),\n            std::move(first),\n            std::move(second),\n\
    \            multiplicity\n        );\n    std::vector<long long> result(graph.edge_count(),\
    \ 0);\n    for (const ActiveEdge& edge : active_edges) {\n        result[edge.id]\
    \ = simple_result[group_of_edge[edge.id]];\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nlong long count_four_cycles(const Graph<T>& graph) {\n    std::vector<long\
    \ long> per_edge = count_four_cycles_per_edge(graph);\n    long long incidence_count\
    \ = 0;\n    for (long long count : per_edge) incidence_count += count;\n    assert(incidence_count\
    \ % 4 == 0);\n    return incidence_count / 4;\n}\n\n}  // namespace graph\n} \
    \ // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_COUNT_FOUR_CYCLES_HPP\n#define M1UNE_GRAPH_COUNT_FOUR_CYCLES_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n#include \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nnamespace four_cycle_detail {\n\n// Counts C4s containing one particular\
    \ copy of each edge in a simple graph\n// whose edge weights represent parallel-edge\
    \ multiplicities.\ninline std::vector<long long> count_simple_per_edge(\n    int\
    \ vertex_count,\n    std::vector<int> first,\n    std::vector<int> second,\n \
    \   const std::vector<long long>& multiplicity\n) {\n    const int edge_count\
    \ = int(first.size());\n    assert(second.size() == first.size());\n    assert(multiplicity.size()\
    \ == first.size());\n\n    std::vector<int> degree(vertex_count, 0);\n    for\
    \ (int edge = 0; edge < edge_count; edge++) {\n        degree[first[edge]]++;\n\
    \        degree[second[edge]]++;\n    }\n\n    int maximum_degree = 0;\n    for\
    \ (int value : degree) maximum_degree = std::max(maximum_degree, value);\n   \
    \ std::vector<int> degree_start(maximum_degree + 2, 0);\n    for (int value :\
    \ degree) degree_start[value + 1]++;\n    for (int value = 0; value <= maximum_degree;\
    \ value++) {\n        degree_start[value + 1] += degree_start[value];\n    }\n\
    \    std::vector<int> cursor = degree_start;\n    std::vector<int> order(vertex_count);\n\
    \    for (int vertex = 0; vertex < vertex_count; vertex++) {\n        order[cursor[degree[vertex]]++]\
    \ = vertex;\n    }\n    std::vector<int> rank(vertex_count);\n    for (int i =\
    \ 0; i < vertex_count; i++) rank[order[i]] = i;\n    for (int edge = 0; edge <\
    \ edge_count; edge++) {\n        first[edge] = rank[first[edge]];\n        second[edge]\
    \ = rank[second[edge]];\n        if (first[edge] < second[edge]) {\n         \
    \   std::swap(first[edge], second[edge]);\n        }\n    }\n\n    std::vector<int>\
    \ start(vertex_count + 1, 0);\n    for (int vertex = 0; vertex < vertex_count;\
    \ vertex++) {\n        start[vertex + 1] = start[vertex] + degree[order[vertex]];\n\
    \    }\n    std::vector<int> end = start;\n    std::vector<int> edge_at(2 * edge_count);\n\
    \    std::vector<int> to(2 * edge_count);\n    for (int edge = 0; edge < edge_count;\
    \ edge++) {\n        int position = end[first[edge]]++;\n        edge_at[position]\
    \ = edge;\n        to[position] = second[edge];\n    }\n\n    std::vector<int>\
    \ downward_end = end;\n    for (int vertex = 0; vertex < vertex_count; vertex++)\
    \ {\n        for (int i = start[vertex]; i < downward_end[vertex]; i++) {\n  \
    \          int edge = edge_at[i];\n            int neighbor = to[i];\n       \
    \     int position = end[neighbor]++;\n            edge_at[position] = edge;\n\
    \            to[position] = vertex;\n        }\n    }\n\n    std::vector<long\
    \ long> path_count(vertex_count, 0);\n    std::vector<long long> result(edge_count,\
    \ 0);\n    for (int vertex = vertex_count - 1; vertex >= 0; vertex--) {\n    \
    \    for (int i = start[vertex]; i < end[vertex]; i++) {\n            int first_edge\
    \ = edge_at[i];\n            int middle = to[i];\n            end[middle]--;\n\
    \            for (int j = start[middle]; j < end[middle]; j++) {\n           \
    \     int second_edge = edge_at[j];\n                int opposite = to[j];\n \
    \               path_count[opposite] +=\n                    multiplicity[first_edge]\
    \ * multiplicity[second_edge];\n            }\n        }\n\n        for (int i\
    \ = start[vertex]; i < end[vertex]; i++) {\n            int first_edge = edge_at[i];\n\
    \            int middle = to[i];\n            for (int j = start[middle]; j <\
    \ end[middle]; j++) {\n                int second_edge = edge_at[j];\n       \
    \         int opposite = to[j];\n                long long other_paths =\n   \
    \                 path_count[opposite] -\n                    multiplicity[first_edge]\
    \ * multiplicity[second_edge];\n                result[first_edge] +=\n      \
    \              other_paths * multiplicity[second_edge];\n                result[second_edge]\
    \ +=\n                    other_paths * multiplicity[first_edge];\n          \
    \  }\n        }\n\n        for (int i = start[vertex]; i < end[vertex]; i++) {\n\
    \            int middle = to[i];\n            for (int j = start[middle]; j <\
    \ end[middle]; j++) {\n                path_count[to[j]] = 0;\n            }\n\
    \        }\n    }\n    return result;\n}\n\n}  // namespace four_cycle_detail\n\
    \n// Returns, for every graph edge id, the number of C4 subgraphs containing it.\n\
    // Parallel active edges are distinct choices; inactive edges receive zero.\n\
    template <class T>\nstd::vector<long long> count_four_cycles_per_edge(const Graph<T>&\
    \ graph) {\n    struct ActiveEdge {\n        int first;\n        int second;\n\
    \        int id;\n    };\n\n    std::vector<ActiveEdge> active_edges;\n    active_edges.reserve(graph.edge_count());\n\
    \    for (const Edge<T>& edge : graph.edges()) {\n        assert(edge.from !=\
    \ edge.to);\n        assert(0 <= edge.id && edge.id < graph.edge_count());\n \
    \       if (edge.from == edge.to) continue;\n        active_edges.push_back(ActiveEdge{\n\
    \            std::min(edge.from, edge.to),\n            std::max(edge.from, edge.to),\n\
    \            edge.id\n        });\n    }\n    std::sort(\n        active_edges.begin(),\n\
    \        active_edges.end(),\n        [](const ActiveEdge& left, const ActiveEdge&\
    \ right) {\n            return std::tie(left.first, left.second) <\n         \
    \          std::tie(right.first, right.second);\n        }\n    );\n\n    std::vector<int>\
    \ first;\n    std::vector<int> second;\n    std::vector<long long> multiplicity;\n\
    \    std::vector<int> group_of_edge(graph.edge_count(), -1);\n    first.reserve(active_edges.size());\n\
    \    second.reserve(active_edges.size());\n    multiplicity.reserve(active_edges.size());\n\
    \    for (const ActiveEdge& edge : active_edges) {\n        if (first.empty()\
    \ || first.back() != edge.first ||\n            second.back() != edge.second)\
    \ {\n            first.push_back(edge.first);\n            second.push_back(edge.second);\n\
    \            multiplicity.push_back(0);\n        }\n        multiplicity.back()++;\n\
    \        group_of_edge[edge.id] = int(first.size()) - 1;\n    }\n\n    std::vector<long\
    \ long> simple_result =\n        four_cycle_detail::count_simple_per_edge(\n \
    \           graph.size(),\n            std::move(first),\n            std::move(second),\n\
    \            multiplicity\n        );\n    std::vector<long long> result(graph.edge_count(),\
    \ 0);\n    for (const ActiveEdge& edge : active_edges) {\n        result[edge.id]\
    \ = simple_result[group_of_edge[edge.id]];\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nlong long count_four_cycles(const Graph<T>& graph) {\n    std::vector<long\
    \ long> per_edge = count_four_cycles_per_edge(graph);\n    long long incidence_count\
    \ = 0;\n    for (long long count : per_edge) incidence_count += count;\n    assert(incidence_count\
    \ % 4 == 0);\n    return incidence_count / 4;\n}\n\n}  // namespace graph\n} \
    \ // namespace m1une\n\n#endif  // M1UNE_GRAPH_COUNT_FOUR_CYCLES_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/count_four_cycles.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-16 19:49:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/count_four_cycles.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/count_four_cycles.hpp
layout: document
title: Count Four Cycles
---

## Overview

This header counts subgraphs isomorphic to the four-edge cycle $C_4$. It can
return either the total number of four-cycles or, for every graph edge id, the
number of four-cycles containing that particular edge.

The implementation compresses parallel edges into multiplicities, orders
vertices by degree, and counts pairs of oriented length-two paths. This avoids
enumerating vertex quadruples.

## Graph Behavior

Every active edge is interpreted as undirected, including an edge inserted with
`add_directed_edge`. Inactive edges are ignored and receive a per-edge count of
zero. Parallel edges are supported and remain distinct choices: replacing one
side of a four-cycle by `k` parallel edges creates `k` different four-edge
subgraphs. Self-loops are not supported.

The per-edge result has `graph.edge_count()` entries indexed by original edge
id. Each count refers to one particular edge copy, not its whole parallel-edge
group.

## Functions

| Function | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| `count_four_cycles_per_edge` | `template <class T> std::vector<long long> count_four_cycles_per_edge(const Graph<T>& graph)` | Returns the number of four-cycles containing every edge id. | $O(N + M\sqrt M)$ time and $O(N + M)$ memory |
| `count_four_cycles` | `template <class T> long long count_four_cycles(const Graph<T>& graph)` | Returns the total number of four-cycles. | $O(N + M\sqrt M)$ time and $O(N + M)$ memory |

`M` denotes the number of active edges, including parallel copies. Counts must
fit in `long long`.

## Example

```cpp
#include "graph/count_four_cycles.hpp"
#include "graph/graph.hpp"

#include <cassert>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 0);
    graph.add_edge(0, 2);

    assert(m1une::graph::count_four_cycles(graph) == 1);
    auto per_edge = m1une::graph::count_four_cycles_per_edge(graph);
    assert(per_edge[4] == 0);  // The diagonal is not in the four-cycle.
}
```
