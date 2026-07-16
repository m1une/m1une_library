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
    path: verify/graph/chordal_graph_recognition.test.cpp
    title: verify/graph/chordal_graph_recognition.test.cpp
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
  bundledCode: "#line 1 \"graph/chordal_graph_recognition.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <queue>\n#include <utility>\n#include <vector>\n\n\
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
    \ m1une\n\n\n#line 11 \"graph/chordal_graph_recognition.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\nstruct ChordalGraphResult {\n    bool is_chordal;\n\
    \    std::vector<int> perfect_elimination_order;\n    std::vector<int> induced_cycle;\n\
    };\n\nnamespace internal {\n\nclass MaximumCardinalitySearch {\n    std::vector<int>\
    \ _head;\n    std::vector<int> _next;\n    std::vector<int> _previous;\n    std::vector<int>\
    \ _weight;\n\n    void erase(int vertex) {\n        const int weight = _weight[vertex];\n\
    \        if (_previous[vertex] == -1) {\n            _head[weight] = _next[vertex];\n\
    \        } else {\n            _next[_previous[vertex]] = _next[vertex];\n   \
    \     }\n        if (_next[vertex] != -1) _previous[_next[vertex]] = _previous[vertex];\n\
    \    }\n\n    void insert(int vertex) {\n        const int weight = _weight[vertex];\n\
    \        _previous[vertex] = -1;\n        _next[vertex] = _head[weight];\n   \
    \     if (_head[weight] != -1) _previous[_head[weight]] = vertex;\n        _head[weight]\
    \ = vertex;\n    }\n\n   public:\n    explicit MaximumCardinalitySearch(int size)\n\
    \        : _head(size + 1, -1),\n          _next(size, -1),\n          _previous(size,\
    \ -1),\n          _weight(size, 0) {\n        for (int vertex = 0; vertex < size;\
    \ vertex++) insert(vertex);\n    }\n\n    std::vector<int> run(const std::vector<std::vector<int>>&\
    \ adjacency) {\n        const int size = int(adjacency.size());\n        std::vector<int>\
    \ order;\n        order.reserve(size);\n        std::vector<char> selected(size,\
    \ false);\n        std::vector<int> seen_neighbor(size, -1);\n        int maximum_weight\
    \ = 0;\n\n        while (int(order.size()) < size) {\n            while (_head[maximum_weight]\
    \ == -1) maximum_weight--;\n            const int vertex = _head[maximum_weight];\n\
    \            erase(vertex);\n            selected[vertex] = true;\n          \
    \  order.push_back(vertex);\n\n            for (int to : adjacency[vertex]) {\n\
    \                if (to == vertex || selected[to] || seen_neighbor[to] == vertex)\
    \ continue;\n                seen_neighbor[to] = vertex;\n                erase(to);\n\
    \                _weight[to]++;\n                insert(to);\n               \
    \ maximum_weight = std::max(maximum_weight, _weight[to]);\n            }\n   \
    \     }\n        return order;\n    }\n};\n\ninline std::vector<int> chordless_cycle(\n\
    \    const std::vector<std::vector<int>>& adjacency, int vertex, int first,\n\
    \    int second\n) {\n    const int size = int(adjacency.size());\n    std::vector<char>\
    \ forbidden(size, false);\n    for (int to : adjacency[vertex]) forbidden[to]\
    \ = true;\n    forbidden[vertex] = true;\n    forbidden[first] = false;\n    forbidden[second]\
    \ = false;\n\n    std::vector<int> parent(size, -1);\n    std::queue<int> queue;\n\
    \    parent[first] = first;\n    queue.push(first);\n    while (!queue.empty()\
    \ && parent[second] == -1) {\n        const int current = queue.front();\n   \
    \     queue.pop();\n        for (int to : adjacency[current]) {\n            if\
    \ (forbidden[to] || parent[to] != -1) continue;\n            parent[to] = current;\n\
    \            queue.push(to);\n        }\n    }\n    assert(parent[second] != -1);\n\
    \n    std::vector<int> path;\n    for (int current = second; current != first;\
    \ current = parent[current]) {\n        path.push_back(current);\n    }\n    path.push_back(first);\n\
    \    std::reverse(path.begin(), path.end());\n\n    std::vector<int> cycle;\n\
    \    cycle.reserve(path.size() + 1);\n    cycle.push_back(vertex);\n    cycle.insert(cycle.end(),\
    \ path.begin(), path.end());\n    return cycle;\n}\n\n}  // namespace internal\n\
    \n// Recognizes a chordal graph. On success, returns a perfect elimination\n//\
    \ ordering; on failure, returns an induced cycle of length at least four.\ntemplate\
    \ <class T>\nChordalGraphResult chordal_graph_recognition(const Graph<T>& graph)\
    \ {\n    const int size = graph.size();\n    std::vector<std::vector<int>> adjacency(size);\n\
    \    for (const Edge<T>& edge : graph.edges()) {\n        if (edge.from == edge.to)\
    \ continue;\n        adjacency[edge.from].push_back(edge.to);\n        adjacency[edge.to].push_back(edge.from);\n\
    \    }\n\n    std::vector<int> order = internal::MaximumCardinalitySearch(size).run(adjacency);\n\
    \    std::vector<int> position(size);\n    for (int index = 0; index < size; index++)\
    \ position[order[index]] = index;\n\n    std::vector<int> parent(size, -1);\n\
    \    std::vector<std::vector<int>> children(size);\n    for (int vertex = 0; vertex\
    \ < size; vertex++) {\n        for (int to : adjacency[vertex]) {\n          \
    \  if (position[to] < position[vertex] &&\n                (parent[vertex] ==\
    \ -1 || position[parent[vertex]] < position[to])) {\n                parent[vertex]\
    \ = to;\n            }\n        }\n        if (parent[vertex] != -1) children[parent[vertex]].push_back(vertex);\n\
    \    }\n\n    std::vector<int> adjacent_stamp(size, -1);\n    for (int center\
    \ = 0; center < size; center++) {\n        for (int to : adjacency[center]) adjacent_stamp[to]\
    \ = center;\n        for (int vertex : children[center]) {\n            for (int\
    \ to : adjacency[vertex]) {\n                if (position[to] >= position[center]\
    \ || adjacent_stamp[to] == center) continue;\n                return ChordalGraphResult{\n\
    \                    false,\n                    {},\n                    internal::chordless_cycle(adjacency,\
    \ vertex, to, center),\n                };\n            }\n        }\n    }\n\n\
    \    std::reverse(order.begin(), order.end());\n    return ChordalGraphResult{true,\
    \ std::move(order), {}};\n}\n\ntemplate <class T>\nbool is_chordal(const Graph<T>&\
    \ graph) {\n    return chordal_graph_recognition(graph).is_chordal;\n}\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_CHORDAL_GRAPH_RECOGNITION_HPP\n#define M1UNE_GRAPH_CHORDAL_GRAPH_RECOGNITION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <queue>\n#include <utility>\n\
    #include <vector>\n\n#include \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct ChordalGraphResult {\n    bool is_chordal;\n    std::vector<int>\
    \ perfect_elimination_order;\n    std::vector<int> induced_cycle;\n};\n\nnamespace\
    \ internal {\n\nclass MaximumCardinalitySearch {\n    std::vector<int> _head;\n\
    \    std::vector<int> _next;\n    std::vector<int> _previous;\n    std::vector<int>\
    \ _weight;\n\n    void erase(int vertex) {\n        const int weight = _weight[vertex];\n\
    \        if (_previous[vertex] == -1) {\n            _head[weight] = _next[vertex];\n\
    \        } else {\n            _next[_previous[vertex]] = _next[vertex];\n   \
    \     }\n        if (_next[vertex] != -1) _previous[_next[vertex]] = _previous[vertex];\n\
    \    }\n\n    void insert(int vertex) {\n        const int weight = _weight[vertex];\n\
    \        _previous[vertex] = -1;\n        _next[vertex] = _head[weight];\n   \
    \     if (_head[weight] != -1) _previous[_head[weight]] = vertex;\n        _head[weight]\
    \ = vertex;\n    }\n\n   public:\n    explicit MaximumCardinalitySearch(int size)\n\
    \        : _head(size + 1, -1),\n          _next(size, -1),\n          _previous(size,\
    \ -1),\n          _weight(size, 0) {\n        for (int vertex = 0; vertex < size;\
    \ vertex++) insert(vertex);\n    }\n\n    std::vector<int> run(const std::vector<std::vector<int>>&\
    \ adjacency) {\n        const int size = int(adjacency.size());\n        std::vector<int>\
    \ order;\n        order.reserve(size);\n        std::vector<char> selected(size,\
    \ false);\n        std::vector<int> seen_neighbor(size, -1);\n        int maximum_weight\
    \ = 0;\n\n        while (int(order.size()) < size) {\n            while (_head[maximum_weight]\
    \ == -1) maximum_weight--;\n            const int vertex = _head[maximum_weight];\n\
    \            erase(vertex);\n            selected[vertex] = true;\n          \
    \  order.push_back(vertex);\n\n            for (int to : adjacency[vertex]) {\n\
    \                if (to == vertex || selected[to] || seen_neighbor[to] == vertex)\
    \ continue;\n                seen_neighbor[to] = vertex;\n                erase(to);\n\
    \                _weight[to]++;\n                insert(to);\n               \
    \ maximum_weight = std::max(maximum_weight, _weight[to]);\n            }\n   \
    \     }\n        return order;\n    }\n};\n\ninline std::vector<int> chordless_cycle(\n\
    \    const std::vector<std::vector<int>>& adjacency, int vertex, int first,\n\
    \    int second\n) {\n    const int size = int(adjacency.size());\n    std::vector<char>\
    \ forbidden(size, false);\n    for (int to : adjacency[vertex]) forbidden[to]\
    \ = true;\n    forbidden[vertex] = true;\n    forbidden[first] = false;\n    forbidden[second]\
    \ = false;\n\n    std::vector<int> parent(size, -1);\n    std::queue<int> queue;\n\
    \    parent[first] = first;\n    queue.push(first);\n    while (!queue.empty()\
    \ && parent[second] == -1) {\n        const int current = queue.front();\n   \
    \     queue.pop();\n        for (int to : adjacency[current]) {\n            if\
    \ (forbidden[to] || parent[to] != -1) continue;\n            parent[to] = current;\n\
    \            queue.push(to);\n        }\n    }\n    assert(parent[second] != -1);\n\
    \n    std::vector<int> path;\n    for (int current = second; current != first;\
    \ current = parent[current]) {\n        path.push_back(current);\n    }\n    path.push_back(first);\n\
    \    std::reverse(path.begin(), path.end());\n\n    std::vector<int> cycle;\n\
    \    cycle.reserve(path.size() + 1);\n    cycle.push_back(vertex);\n    cycle.insert(cycle.end(),\
    \ path.begin(), path.end());\n    return cycle;\n}\n\n}  // namespace internal\n\
    \n// Recognizes a chordal graph. On success, returns a perfect elimination\n//\
    \ ordering; on failure, returns an induced cycle of length at least four.\ntemplate\
    \ <class T>\nChordalGraphResult chordal_graph_recognition(const Graph<T>& graph)\
    \ {\n    const int size = graph.size();\n    std::vector<std::vector<int>> adjacency(size);\n\
    \    for (const Edge<T>& edge : graph.edges()) {\n        if (edge.from == edge.to)\
    \ continue;\n        adjacency[edge.from].push_back(edge.to);\n        adjacency[edge.to].push_back(edge.from);\n\
    \    }\n\n    std::vector<int> order = internal::MaximumCardinalitySearch(size).run(adjacency);\n\
    \    std::vector<int> position(size);\n    for (int index = 0; index < size; index++)\
    \ position[order[index]] = index;\n\n    std::vector<int> parent(size, -1);\n\
    \    std::vector<std::vector<int>> children(size);\n    for (int vertex = 0; vertex\
    \ < size; vertex++) {\n        for (int to : adjacency[vertex]) {\n          \
    \  if (position[to] < position[vertex] &&\n                (parent[vertex] ==\
    \ -1 || position[parent[vertex]] < position[to])) {\n                parent[vertex]\
    \ = to;\n            }\n        }\n        if (parent[vertex] != -1) children[parent[vertex]].push_back(vertex);\n\
    \    }\n\n    std::vector<int> adjacent_stamp(size, -1);\n    for (int center\
    \ = 0; center < size; center++) {\n        for (int to : adjacency[center]) adjacent_stamp[to]\
    \ = center;\n        for (int vertex : children[center]) {\n            for (int\
    \ to : adjacency[vertex]) {\n                if (position[to] >= position[center]\
    \ || adjacent_stamp[to] == center) continue;\n                return ChordalGraphResult{\n\
    \                    false,\n                    {},\n                    internal::chordless_cycle(adjacency,\
    \ vertex, to, center),\n                };\n            }\n        }\n    }\n\n\
    \    std::reverse(order.begin(), order.end());\n    return ChordalGraphResult{true,\
    \ std::move(order), {}};\n}\n\ntemplate <class T>\nbool is_chordal(const Graph<T>&\
    \ graph) {\n    return chordal_graph_recognition(graph).is_chordal;\n}\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_CHORDAL_GRAPH_RECOGNITION_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/chordal_graph_recognition.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-14 02:59:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/chordal_graph_recognition.test.cpp
documentation_of: graph/chordal_graph_recognition.hpp
layout: document
title: Chordal Graph Recognition
---

## Overview

A graph is chordal when every cycle of length at least four has a chord.
Equivalently, it has a perfect elimination ordering: for each vertex, its
neighbors appearing later in the ordering form a clique.

`chordal_graph_recognition` recognizes a chordal graph and returns a certificate
in either case. A chordal graph gets a perfect elimination ordering; a
non-chordal graph gets an induced cycle of length at least four.

The implementation uses bucketed maximum-cardinality search, verifies the
resulting ordering, and performs one BFS only when it must construct a cycle.

## Returned Certificates

### Perfect Elimination Ordering

Let `order` be a permutation of all vertices. For each vertex `order[i]`, look
at only its neighbors in the suffix
`order[i + 1], order[i + 2], ..., order[N - 1]`. The ordering is a perfect
elimination ordering when those later neighbors are pairwise adjacent, and
therefore form a clique, for every `i`.

The name comes from eliminating the vertices from left to right. Removing
`order[i]` cannot create a missing connection between its remaining neighbors,
because those neighbors already form a clique.

For example, consider the path `0 - 1 - 2`. The ordering `[0, 2, 1]` is a
perfect elimination ordering:

* The only later neighbor of `0` is `1`.
* The only later neighbor of `2` is `1`.
* Vertex `1` has no later neighbors.

A set with zero or one vertex is always a clique, so all three conditions hold.
Every chordal graph has such an ordering, and every graph with such an ordering
is chordal.

### Induced Cycle

An induced cycle is a sequence of distinct vertices
`cycle[0], cycle[1], ..., cycle[K - 1]`, with `K >= 4`, satisfying both of the
following:

* Consecutive vertices are adjacent, including `cycle[K - 1]` and `cycle[0]`.
* No other pair of vertices in the sequence is adjacent.

The second condition says that the cycle has no chord: an edge joining two
non-consecutive cycle vertices. For example, the four-cycle
`0 - 1 - 2 - 3 - 0` is induced if neither `0 - 2` nor `1 - 3` is an edge.
Adding either edge gives the cycle a chord, so that four-vertex sequence is no
longer an induced cycle.

An induced cycle of length at least four is a direct certificate that the graph
is not chordal. The returned vector does not repeat its first vertex at the end;
the closing edge from `cycle.back()` to `cycle.front()` is implicit.

## Graph Interpretation

Every active edge of `Graph<T>` is treated as an undirected edge, regardless of
how it was inserted. Self-loops are ignored. Parallel edges are treated as one
edge, so they do not change the result.

Edge costs are ignored. The graph is not mutated.

## API

```cpp
struct ChordalGraphResult {
    bool is_chordal;
    std::vector<int> perfect_elimination_order;
    std::vector<int> induced_cycle;
};

template <class T>
ChordalGraphResult chordal_graph_recognition(const Graph<T>& graph);

template <class T>
bool is_chordal(const Graph<T>& graph);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `is_chordal` | Whether the input graph is chordal. | -- |
| `perfect_elimination_order` | A permutation in which the later neighbors of every vertex form a clique when the graph is chordal; empty otherwise. | -- |
| `induced_cycle` | Distinct vertices of a chordless cycle in cyclic order when the graph is not chordal; empty otherwise. The first vertex is not repeated. | -- |
| `chordal_graph_recognition(graph)` | Recognizes the graph and constructs the appropriate certificate. | $O(N+M)$ time and memory |
| `is_chordal(graph)` | Returns only whether the graph is chordal. | $O(N+M)$ time and memory |

## Example

```cpp
#include "graph/chordal_graph_recognition.hpp"
#include "graph/graph.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 0);

    auto result = m1une::graph::chordal_graph_recognition(graph);
    std::cout << result.is_chordal << "\n";         // 0
    std::cout << result.induced_cycle.size() << "\n";  // 4
}
```
