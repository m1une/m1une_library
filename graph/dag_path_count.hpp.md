---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/dag.hpp
    title: DAG Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/dag_algorithms.test.cpp
    title: verify/graph/dag_algorithms.test.cpp
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
  bundledCode: "#line 1 \"graph/dag_path_count.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <optional>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include\
    \ <array>\n#line 6 \"graph/graph.hpp\"\n#include <utility>\n#line 8 \"graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
    \ {\n    using cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n   \
    \ int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1),\
    \ alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool\
    \ alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_)\
    \ {}\n\n    int other(int v) const {\n        assert(v == from || v == to);\n\
    \        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    struct EdgePositions {\n        std::array<std::pair<int, int>, 2> value{};\n\
    \        int size = 0;\n\n        void push_back(std::pair<int, int> position)\
    \ {\n            assert(size < 2);\n            value[size++] = position;\n  \
    \      }\n    };\n\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<EdgePositions> _edge_positions;\n\n   public:\n    Graph()\
    \ : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
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
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (int i =\
    \ 0; i < _edge_positions[id].size; ++i) {\n            auto [v, idx] = _edge_positions[id].value[i];\n\
    \            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(_edge_positions[id].size\
    \ != 0);\n        auto [v, idx] = _edge_positions[id].value[0];\n        return\
    \ _g[v][idx].alive;\n    }\n\n    const std::vector<edge_type>& operator[](int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\
    \n    std::vector<edge_type>& operator[](int v) {\n        assert(0 <= v && v\
    \ < _n);\n        return _g[v];\n    }\n\n    const std::vector<std::vector<edge_type>>&\
    \ adjacency() const {\n        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>&\
    \ adjacency() {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool\
    \ include_inactive = false) const {\n        std::vector<edge_type> result;\n\
    \        result.reserve(_edge_count);\n        std::vector<char> used(_edge_count,\
    \ false);\n        for (int v = 0; v < _n; v++) {\n            for (const auto&\
    \ e : _g[v]) {\n                if (!include_inactive && !e.alive) continue;\n\
    \                if (0 <= e.id && e.id < _edge_count) {\n                    if\
    \ (used[e.id]) continue;\n                    used[e.id] = true;\n           \
    \     }\n                result.push_back(e);\n            }\n        }\n    \
    \    return result;\n    }\n\n    Graph reversed() const {\n        Graph result(_n);\n\
    \        result._edge_count = _edge_count;\n        result._edge_positions.assign(_edge_count,\
    \ {});\n        for (int v = 0; v < _n; v++) {\n            for (const auto& e\
    \ : _g[v]) {\n                int idx = int(result._g[e.to].size());\n       \
    \         result._g[e.to].push_back(edge_type(e.to, e.from, e.cost, e.id, e.alive));\n\
    \                if (0 <= e.id && e.id < _edge_count) result._edge_positions[e.id].push_back({e.to,\
    \ idx});\n            }\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/topological_sort.hpp\"\
    \n\n\n\n#line 5 \"graph/topological_sort.hpp\"\n#include <queue>\n#line 7 \"graph/topological_sort.hpp\"\
    \n\n#line 9 \"graph/topological_sort.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstd::optional<std::vector<int>> topological_sort(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> indeg(n, 0);\n \
    \   for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v]) {\n    \
    \        if (!e.alive) continue;\n            indeg[e.to]++;\n        }\n    }\n\
    \n    std::queue<int> que;\n    for (int v = 0; v < n; v++) {\n        if (indeg[v]\
    \ == 0) que.push(v);\n    }\n\n    std::vector<int> order;\n    order.reserve(n);\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        order.push_back(v);\n        for (const auto& e : g[v]) {\n         \
    \   if (!e.alive) continue;\n            indeg[e.to]--;\n            if (indeg[e.to]\
    \ == 0) que.push(e.to);\n        }\n    }\n\n    if (int(order.size()) != n) return\
    \ std::nullopt;\n    return order;\n}\n\ntemplate <class T>\nbool is_dag(const\
    \ Graph<T>& g) {\n    return topological_sort(g).has_value();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 10 \"graph/dag_path_count.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\ntemplate <class Count = long long, class\
    \ T>\nstd::optional<std::vector<Count>> dag_path_count(\n    const Graph<T>& g,\n\
    \    const std::vector<int>& sources\n) {\n    const int n = g.size();\n    auto\
    \ order = topological_sort(g);\n    if (!order) return std::nullopt;\n\n    std::vector<Count>\
    \ ways(n, Count(0));\n    std::vector<char> used_source(n, false);\n    for (int\
    \ s : sources) {\n        assert(0 <= s && s < n);\n        if (used_source[s])\
    \ continue;\n        used_source[s] = true;\n        ways[s] += Count(1);\n  \
    \  }\n\n    for (int v : *order) {\n        for (const auto& e : g[v]) {\n   \
    \         if (e.alive) ways[e.to] += ways[v];\n        }\n    }\n    return ways;\n\
    }\n\ntemplate <class Count = long long, class T>\nstd::optional<std::vector<Count>>\
    \ dag_path_count(const Graph<T>& g, int s) {\n    return dag_path_count<Count>(g,\
    \ std::vector<int>{s});\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_GRAPH_DAG_PATH_COUNT_HPP\n#define M1UNE_GRAPH_DAG_PATH_COUNT_HPP\
    \ 1\n\n#include <cassert>\n#include <optional>\n#include <vector>\n\n#include\
    \ \"graph.hpp\"\n#include \"topological_sort.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\ntemplate <class Count = long long, class T>\nstd::optional<std::vector<Count>>\
    \ dag_path_count(\n    const Graph<T>& g,\n    const std::vector<int>& sources\n\
    ) {\n    const int n = g.size();\n    auto order = topological_sort(g);\n    if\
    \ (!order) return std::nullopt;\n\n    std::vector<Count> ways(n, Count(0));\n\
    \    std::vector<char> used_source(n, false);\n    for (int s : sources) {\n \
    \       assert(0 <= s && s < n);\n        if (used_source[s]) continue;\n    \
    \    used_source[s] = true;\n        ways[s] += Count(1);\n    }\n\n    for (int\
    \ v : *order) {\n        for (const auto& e : g[v]) {\n            if (e.alive)\
    \ ways[e.to] += ways[v];\n        }\n    }\n    return ways;\n}\n\ntemplate <class\
    \ Count = long long, class T>\nstd::optional<std::vector<Count>> dag_path_count(const\
    \ Graph<T>& g, int s) {\n    return dag_path_count<Count>(g, std::vector<int>{s});\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_DAG_PATH_COUNT_HPP\n"
  dependsOn:
  - graph/graph.hpp
  - graph/topological_sort.hpp
  isVerificationFile: false
  path: graph/dag_path_count.hpp
  requiredBy:
  - graph/all.hpp
  - graph/dag.hpp
  - graph/directed.hpp
  timestamp: '2026-08-24 00:41:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/dag_algorithms.test.cpp
  - verify/graph/range_edge_graph.test.cpp
documentation_of: graph/dag_path_count.hpp
layout: document
title: DAG Path Count
---

## Overview

`dag_path_count` counts directed paths from one or more sources to every vertex
of a DAG. It is useful for dependency counting and standard DAG dynamic
programming.

Each source contributes one zero-edge path to itself. Parallel active edges
describe distinct paths, inactive edges are ignored, and duplicate source
indices are counted once. A cyclic graph returns `std::nullopt`.

`Count` defaults to `long long`. It only needs construction from `0` and `1`
and addition, so a modular integer type can be supplied when counts are large.
Overflow follows the behavior of `Count`.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `dag_path_count` | `template <class Count = long long, class T> std::optional<std::vector<Count>> dag_path_count(const Graph<T>& g, int s)` | Counts paths beginning at `s`. | $O(N + M)$ time and $O(N)$ memory |
| `dag_path_count` | `template <class Count = long long, class T> std::optional<std::vector<Count>> dag_path_count(const Graph<T>& g, const std::vector<int>& sources)` | Counts paths beginning at any source. | $O(N + M)$ time and $O(N)$ memory |

## Example

```cpp
#include "graph/dag_path_count.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(0, 2);
    g.add_directed_edge(1, 3);
    g.add_directed_edge(2, 3);

    auto ways = m1une::graph::dag_path_count(g, 0);
    if (ways) std::cout << (*ways)[3] << '\n';  // 2
}
```
