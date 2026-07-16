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
    path: graph/tree/all.hpp
    title: Tree All
  - icon: ':heavy_check_mark:'
    path: graph/tree/tree.hpp
    title: Tree
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
    path: verify/graph/tree/tree_algorithms.test.cpp
    title: verify/graph/tree/tree_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/vertex_add_subtree_sum.test.cpp
    title: verify/graph/tree/vertex_add_subtree_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/tree/euler_tour.hpp\"\n\n\n\n#include <algorithm>\n\
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
    \ m1une\n\n\n#line 10 \"graph/tree/euler_tour.hpp\"\n\nnamespace m1une {\nnamespace\
    \ tree {\n\ntemplate <class T = int>\nstruct EulerTour {\n    using cost_type\
    \ = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n    int root;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    std::vector<int> depth;\n  \
    \  std::vector<T> dist;\n    std::vector<int> subtree_size;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n    std::vector<std::vector<int>>\
    \ children;\n\n   private:\n    int _n;\n\n    void check_vertex(int v) const\
    \ {\n        assert(0 <= v && v < _n);\n        assert(tin[v] != -1);\n    }\n\
    \n   public:\n    EulerTour() : root(-1), _n(0) {}\n    explicit EulerTour(const\
    \ m1une::graph::Graph<T>& g, int root_ = 0) {\n        build(g, root_);\n    }\n\
    \n    void build(const m1une::graph::Graph<T>& g, int root_ = 0) {\n        _n\
    \ = g.size();\n        root = _n == 0 ? -1 : root_;\n        parent.assign(_n,\
    \ -2);\n        parent_edge.assign(_n, -1);\n        depth.assign(_n, 0);\n  \
    \      dist.assign(_n, T(0));\n        subtree_size.assign(_n, 0);\n        tin.assign(_n,\
    \ -1);\n        tout.assign(_n, -1);\n        order.clear();\n        order.reserve(_n);\n\
    \        children.assign(_n, {});\n\n        if (_n == 0) return;\n        assert(0\
    \ <= root && root < _n);\n\n        struct Frame {\n            int v;\n     \
    \       int state;\n        };\n\n        std::vector<Frame> stack;\n        stack.push_back({root,\
    \ 0});\n        parent[root] = -1;\n\n        while (!stack.empty()) {\n     \
    \       Frame frame = stack.back();\n            stack.pop_back();\n         \
    \   int v = frame.v;\n            if (frame.state == 0) {\n                tin[v]\
    \ = int(order.size());\n                order.push_back(v);\n                stack.push_back({v,\
    \ 1});\n                const auto& adj = g[v];\n                for (int i =\
    \ int(adj.size()) - 1; i >= 0; --i) {\n                    const auto& e = adj[i];\n\
    \                    if (!e.alive) continue;\n                    if (parent[e.to]\
    \ != -2) continue;\n                    parent[e.to] = v;\n                  \
    \  parent_edge[e.to] = e.id;\n                    depth[e.to] = depth[v] + 1;\n\
    \                    dist[e.to] = dist[v] + e.cost;\n                    children[v].push_back(e.to);\n\
    \                    stack.push_back({e.to, 0});\n                }\n        \
    \        std::reverse(children[v].begin(), children[v].end());\n            }\
    \ else {\n                subtree_size[v] = 1;\n                for (int child\
    \ : children[v]) subtree_size[v] += subtree_size[child];\n                tout[v]\
    \ = int(order.size());\n            }\n        }\n    }\n\n    int size() const\
    \ {\n        return _n;\n    }\n\n    int visited_size() const {\n        return\
    \ int(order.size());\n    }\n\n    bool empty() const {\n        return _n ==\
    \ 0;\n    }\n\n    bool is_ancestor(int u, int v) const {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        return tin[u] <= tin[v] && tout[v] <= tout[u];\n\
    \    }\n\n    bool in_subtree(int v, int u) const {\n        return is_ancestor(u,\
    \ v);\n    }\n\n    std::pair<int, int> subtree_range(int v, bool edge = false)\
    \ const {\n        check_vertex(v);\n        return {tin[v] + (edge ? 1 : 0),\
    \ tout[v]};\n    }\n\n    std::vector<int> subtree_vertices(int v) const {\n \
    \       check_vertex(v);\n        return std::vector<int>(order.begin() + tin[v],\
    \ order.begin() + tout[v]);\n    }\n\n    template <class F>\n    void for_each_subtree(int\
    \ v, F f) const {\n        auto [l, r] = subtree_range(v);\n        for (int i\
    \ = l; i < r; ++i) f(order[i]);\n    }\n};\n\n}  // namespace tree\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_EULER_TOUR_HPP\n#define M1UNE_TREE_EULER_TOUR_HPP 1\n\n\
    #include <algorithm>\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n#include \"../graph.hpp\"\n\nnamespace m1une {\nnamespace tree {\n\ntemplate\
    \ <class T = int>\nstruct EulerTour {\n    using cost_type = T;\n    using edge_type\
    \ = m1une::graph::Edge<T>;\n\n    int root;\n    std::vector<int> parent;\n  \
    \  std::vector<int> parent_edge;\n    std::vector<int> depth;\n    std::vector<T>\
    \ dist;\n    std::vector<int> subtree_size;\n    std::vector<int> tin;\n    std::vector<int>\
    \ tout;\n    std::vector<int> order;\n    std::vector<std::vector<int>> children;\n\
    \n   private:\n    int _n;\n\n    void check_vertex(int v) const {\n        assert(0\
    \ <= v && v < _n);\n        assert(tin[v] != -1);\n    }\n\n   public:\n    EulerTour()\
    \ : root(-1), _n(0) {}\n    explicit EulerTour(const m1une::graph::Graph<T>& g,\
    \ int root_ = 0) {\n        build(g, root_);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        _n = g.size();\n        root = _n == 0 ? -1 : root_;\n\
    \        parent.assign(_n, -2);\n        parent_edge.assign(_n, -1);\n       \
    \ depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n        subtree_size.assign(_n,\
    \ 0);\n        tin.assign(_n, -1);\n        tout.assign(_n, -1);\n        order.clear();\n\
    \        order.reserve(_n);\n        children.assign(_n, {});\n\n        if (_n\
    \ == 0) return;\n        assert(0 <= root && root < _n);\n\n        struct Frame\
    \ {\n            int v;\n            int state;\n        };\n\n        std::vector<Frame>\
    \ stack;\n        stack.push_back({root, 0});\n        parent[root] = -1;\n\n\
    \        while (!stack.empty()) {\n            Frame frame = stack.back();\n \
    \           stack.pop_back();\n            int v = frame.v;\n            if (frame.state\
    \ == 0) {\n                tin[v] = int(order.size());\n                order.push_back(v);\n\
    \                stack.push_back({v, 1});\n                const auto& adj = g[v];\n\
    \                for (int i = int(adj.size()) - 1; i >= 0; --i) {\n          \
    \          const auto& e = adj[i];\n                    if (!e.alive) continue;\n\
    \                    if (parent[e.to] != -2) continue;\n                    parent[e.to]\
    \ = v;\n                    parent_edge[e.to] = e.id;\n                    depth[e.to]\
    \ = depth[v] + 1;\n                    dist[e.to] = dist[v] + e.cost;\n      \
    \              children[v].push_back(e.to);\n                    stack.push_back({e.to,\
    \ 0});\n                }\n                std::reverse(children[v].begin(), children[v].end());\n\
    \            } else {\n                subtree_size[v] = 1;\n                for\
    \ (int child : children[v]) subtree_size[v] += subtree_size[child];\n        \
    \        tout[v] = int(order.size());\n            }\n        }\n    }\n\n   \
    \ int size() const {\n        return _n;\n    }\n\n    int visited_size() const\
    \ {\n        return int(order.size());\n    }\n\n    bool empty() const {\n  \
    \      return _n == 0;\n    }\n\n    bool is_ancestor(int u, int v) const {\n\
    \        check_vertex(u);\n        check_vertex(v);\n        return tin[u] <=\
    \ tin[v] && tout[v] <= tout[u];\n    }\n\n    bool in_subtree(int v, int u) const\
    \ {\n        return is_ancestor(u, v);\n    }\n\n    std::pair<int, int> subtree_range(int\
    \ v, bool edge = false) const {\n        check_vertex(v);\n        return {tin[v]\
    \ + (edge ? 1 : 0), tout[v]};\n    }\n\n    std::vector<int> subtree_vertices(int\
    \ v) const {\n        check_vertex(v);\n        return std::vector<int>(order.begin()\
    \ + tin[v], order.begin() + tout[v]);\n    }\n\n    template <class F>\n    void\
    \ for_each_subtree(int v, F f) const {\n        auto [l, r] = subtree_range(v);\n\
    \        for (int i = l; i < r; ++i) f(order[i]);\n    }\n};\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n#endif  // M1UNE_TREE_EULER_TOUR_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/tree/euler_tour.hpp
  requiredBy:
  - graph/tree/all.hpp
  - graph/tree/tree.hpp
  - graph/all.hpp
  timestamp: '2026-07-11 19:47:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/tree/vertex_add_subtree_sum.test.cpp
  - verify/graph/tree/tree_algorithms.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/tree/euler_tour.hpp
layout: document
title: Euler Tour
---

## Overview

`m1une::tree::EulerTour<T>` roots an undirected tree and flattens each rooted
subtree into one contiguous interval. It is the lightweight choice when you only
need parent/depth metadata and subtree ranges for a Fenwick tree, segment tree,
or direct iteration.

The input uses `m1une::graph::Graph<T>` and should be built with `add_edge`.
Inactive graph edges are ignored.

## Construction

```cpp
m1une::graph::Graph<int> g(n);
g.add_edge(u, v);

m1une::tree::EulerTour<int> tour(g, 0);
```

The graph is expected to be an undirected tree. If the graph is disconnected,
only the component reachable from the selected root is represented; unreachable
vertices keep `tin[v] == -1`.

## Public Members

For a connected tree, all arrays have size `N`, and `order` also contains `N`
vertices.

| Member | Type | Description |
| --- | --- | --- |
| `root` | `int` | Root vertex, or `-1` for an empty tree. |
| `parent` | `std::vector<int>` | Parent vertex, or `-1` at the root. |
| `parent_edge` | `std::vector<int>` | Edge id connecting the vertex to its parent, or `-1`. |
| `depth` | `std::vector<int>` | Number of edges from the root. |
| `dist` | `std::vector<T>` | Sum of edge costs from the root. |
| `subtree_size` | `std::vector<int>` | Number of vertices in each rooted subtree. |
| `tin`, `tout` | `std::vector<int>` | Subtree interval `[tin[v], tout[v])` in preorder. |
| `order` | `std::vector<int>` | Vertices in DFS preorder. |
| `children` | `std::vector<std::vector<int>>` | Children in the rooted tree. |

Important relationships:

* Vertex `v` is stored at base-array index `tin[v]`.
* `order[i]` converts a base-array index back to the original vertex.
* The rooted subtree of `v` is exactly `order[tin[v]..tout[v])`.
* If edge values are stored at the child vertex position, the subtree edge
  interval is `[tin[v] + 1, tout[v])`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `EulerTour(const Graph<T>& g, int root = 0)` | Builds Euler-tour metadata. | $O(N)$ |
| `void build(const Graph<T>& g, int root = 0)` | Rebuilds the structure. | $O(N)$ |
| `int size() const` | Returns the number of vertices in the source graph. | $O(1)$ |
| `int visited_size() const` | Returns the number of vertices reached from `root`. | $O(1)$ |
| `bool empty() const` | Returns whether the source graph is empty. | $O(1)$ |
| `bool is_ancestor(int u, int v) const` | Returns whether `u` is an ancestor of `v`. | $O(1)$ |
| `bool in_subtree(int v, int u) const` | Returns whether `v` is in the subtree of `u`. | $O(1)$ |
| `std::pair<int, int> subtree_range(int v, bool edge = false) const` | Returns `[tin[v], tout[v])`; with `edge=true`, excludes `v`. | $O(1)$ |
| `std::vector<int> subtree_vertices(int v) const` | Returns vertices in the rooted subtree of `v`. | $O(\text{subtree size})$ |
| `template <class F> void for_each_subtree(int v, F f) const` | Calls `f(vertex)` for each vertex in the subtree. | $O(\text{subtree size})$ |

`T` must be default-constructible and support addition with edge costs if
`dist` is used.

## Example

```cpp
#include "ds/range_query/fenwick_tree.hpp"
#include "graph/graph.hpp"
#include "graph/tree/euler_tour.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<int> g(4);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);

    std::vector<long long> value = {10, 20, 30, 40};
    m1une::tree::EulerTour<int> tour(g, 0);

    std::vector<long long> base(4);
    for (int v = 0; v < 4; ++v) {
        base[tour.tin[v]] = value[v];
    }
    m1une::ds::FenwickTree<long long> fenwick(base);

    auto [l, r] = tour.subtree_range(1);
    std::cout << fenwick.sum(l, r) << "\n"; // 60
}
```
