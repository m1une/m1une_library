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
    path: verify/graph/dfs.test.cpp
    title: verify/graph/dfs.test.cpp
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
  bundledCode: "#line 1 \"graph/dfs.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <concepts>\n#include <functional>\n#include <utility>\n#include <vector>\n\
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
    \ m1une\n\n\n#line 12 \"graph/dfs.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct DfsResult {\n    std::vector<int> depth;\n    std::vector<int> parent;\n\
    \    std::vector<int> parent_edge;\n    std::vector<int> root;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> preorder;\n    std::vector<int>\
    \ postorder;\n    std::vector<int> roots;\n\n    bool reachable(int vertex) const\
    \ {\n        assert(0 <= vertex && vertex < int(depth.size()));\n        return\
    \ depth[vertex] != -1;\n    }\n\n    int component_count() const {\n        return\
    \ int(roots.size());\n    }\n\n    std::vector<int> path(int target) const {\n\
    \        assert(reachable(target));\n        std::vector<int> result;\n      \
    \  for (int vertex = target; vertex != -1; vertex = parent[vertex]) {\n      \
    \      result.push_back(vertex);\n        }\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n\n    bool is_ancestor(int ancestor,\
    \ int vertex) const {\n        assert(0 <= ancestor && ancestor < int(depth.size()));\n\
    \        assert(0 <= vertex && vertex < int(depth.size()));\n        if (!reachable(ancestor)\
    \ || !reachable(vertex)) return false;\n        return tin[ancestor] <= tin[vertex]\
    \ && tout[vertex] <= tout[ancestor];\n    }\n};\n\nnamespace dfs_detail {\n\n\
    template <class Callback>\nconcept DfsCallback =\n    std::invocable<Callback&,\
    \ int, int> ||\n    std::invocable<Callback&, int>;\n\ntemplate <DfsCallback Callback>\n\
    void invoke_callback(Callback& callback, int vertex, int parent) {\n    if constexpr\
    \ (std::invocable<Callback&, int, int>) {\n        std::invoke(callback, vertex,\
    \ parent);\n    } else {\n        std::invoke(callback, vertex);\n    }\n}\n\n\
    template <class T, class Callback>\nDfsResult run_dfs(\n    const Graph<T>& graph,\n\
    \    const std::vector<int>& sources,\n    bool complete_forest,\n    Callback&\
    \ callback\n) {\n    const int n = graph.size();\n    DfsResult result;\n    result.depth.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.root.assign(n, -1);\n    result.tin.assign(n, -1);\n    result.tout.assign(n,\
    \ -1);\n    result.preorder.reserve(n);\n    result.postorder.reserve(n);\n  \
    \  result.roots.reserve(n);\n\n    struct Frame {\n        int vertex;\n     \
    \   int next_edge;\n    };\n    std::vector<Frame> stack;\n    stack.reserve(n);\n\
    \    int timer = 0;\n\n    auto traverse = [&](int source) {\n        assert(0\
    \ <= source && source < n);\n        if (result.reachable(source)) return;\n\n\
    \        result.depth[source] = 0;\n        result.root[source] = source;\n  \
    \      result.tin[source] = ++timer;\n        result.preorder.push_back(source);\n\
    \        result.roots.push_back(source);\n        invoke_callback(callback, source,\
    \ -1);\n        stack.push_back(Frame{source, 0});\n\n        while (!stack.empty())\
    \ {\n            Frame& frame = stack.back();\n            int vertex = frame.vertex;\n\
    \            if (frame.next_edge == int(graph[vertex].size())) {\n           \
    \     result.tout[vertex] = ++timer;\n                result.postorder.push_back(vertex);\n\
    \                stack.pop_back();\n                continue;\n            }\n\
    \n            const Edge<T>& edge = graph[vertex][frame.next_edge++];\n      \
    \      if (!edge.alive || result.reachable(edge.to)) continue;\n            result.depth[edge.to]\
    \ = result.depth[vertex] + 1;\n            result.parent[edge.to] = vertex;\n\
    \            result.parent_edge[edge.to] = edge.id;\n            result.root[edge.to]\
    \ = result.root[vertex];\n            result.tin[edge.to] = ++timer;\n       \
    \     result.preorder.push_back(edge.to);\n            invoke_callback(callback,\
    \ edge.to, vertex);\n            stack.push_back(Frame{edge.to, 0});\n       \
    \ }\n    };\n\n    for (int source : sources) traverse(source);\n    if (complete_forest)\
    \ {\n        for (int vertex = 0; vertex < n; vertex++) traverse(vertex);\n  \
    \  }\n    return result;\n}\n\n}  // namespace dfs_detail\n\ntemplate <class T>\n\
    DfsResult dfs(const Graph<T>& graph, const std::vector<int>& sources) {\n    auto\
    \ callback = [](int) {};\n    return dfs_detail::run_dfs(graph, sources, false,\
    \ callback);\n}\n\ntemplate <class T>\nDfsResult dfs(const Graph<T>& graph, int\
    \ source) {\n    return dfs(graph, std::vector<int>{source});\n}\n\ntemplate <class\
    \ T>\nDfsResult dfs(const Graph<T>& graph) {\n    auto callback = [](int) {};\n\
    \    return dfs_detail::run_dfs(\n        graph,\n        std::vector<int>(),\n\
    \        true,\n        callback\n    );\n}\n\ntemplate <class T, class Callback>\n\
    requires dfs_detail::DfsCallback<Callback>\nDfsResult dfs(\n    const Graph<T>&\
    \ graph,\n    const std::vector<int>& sources,\n    Callback&& callback\n) {\n\
    \    return dfs_detail::run_dfs(graph, sources, false, callback);\n}\n\ntemplate\
    \ <class T, class Callback>\nrequires dfs_detail::DfsCallback<Callback>\nDfsResult\
    \ dfs(const Graph<T>& graph, int source, Callback&& callback) {\n    return dfs(\n\
    \        graph,\n        std::vector<int>{source},\n        std::forward<Callback>(callback)\n\
    \    );\n}\n\ntemplate <class T, class Callback>\nrequires dfs_detail::DfsCallback<Callback>\n\
    DfsResult dfs(const Graph<T>& graph, Callback&& callback) {\n    return dfs_detail::run_dfs(\n\
    \        graph,\n        std::vector<int>(),\n        true,\n        callback\n\
    \    );\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_DFS_HPP\n#define M1UNE_GRAPH_DFS_HPP 1\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <functional>\n#include <utility>\n\
    #include <vector>\n\n#include \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct DfsResult {\n    std::vector<int> depth;\n    std::vector<int> parent;\n\
    \    std::vector<int> parent_edge;\n    std::vector<int> root;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> preorder;\n    std::vector<int>\
    \ postorder;\n    std::vector<int> roots;\n\n    bool reachable(int vertex) const\
    \ {\n        assert(0 <= vertex && vertex < int(depth.size()));\n        return\
    \ depth[vertex] != -1;\n    }\n\n    int component_count() const {\n        return\
    \ int(roots.size());\n    }\n\n    std::vector<int> path(int target) const {\n\
    \        assert(reachable(target));\n        std::vector<int> result;\n      \
    \  for (int vertex = target; vertex != -1; vertex = parent[vertex]) {\n      \
    \      result.push_back(vertex);\n        }\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n\n    bool is_ancestor(int ancestor,\
    \ int vertex) const {\n        assert(0 <= ancestor && ancestor < int(depth.size()));\n\
    \        assert(0 <= vertex && vertex < int(depth.size()));\n        if (!reachable(ancestor)\
    \ || !reachable(vertex)) return false;\n        return tin[ancestor] <= tin[vertex]\
    \ && tout[vertex] <= tout[ancestor];\n    }\n};\n\nnamespace dfs_detail {\n\n\
    template <class Callback>\nconcept DfsCallback =\n    std::invocable<Callback&,\
    \ int, int> ||\n    std::invocable<Callback&, int>;\n\ntemplate <DfsCallback Callback>\n\
    void invoke_callback(Callback& callback, int vertex, int parent) {\n    if constexpr\
    \ (std::invocable<Callback&, int, int>) {\n        std::invoke(callback, vertex,\
    \ parent);\n    } else {\n        std::invoke(callback, vertex);\n    }\n}\n\n\
    template <class T, class Callback>\nDfsResult run_dfs(\n    const Graph<T>& graph,\n\
    \    const std::vector<int>& sources,\n    bool complete_forest,\n    Callback&\
    \ callback\n) {\n    const int n = graph.size();\n    DfsResult result;\n    result.depth.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.root.assign(n, -1);\n    result.tin.assign(n, -1);\n    result.tout.assign(n,\
    \ -1);\n    result.preorder.reserve(n);\n    result.postorder.reserve(n);\n  \
    \  result.roots.reserve(n);\n\n    struct Frame {\n        int vertex;\n     \
    \   int next_edge;\n    };\n    std::vector<Frame> stack;\n    stack.reserve(n);\n\
    \    int timer = 0;\n\n    auto traverse = [&](int source) {\n        assert(0\
    \ <= source && source < n);\n        if (result.reachable(source)) return;\n\n\
    \        result.depth[source] = 0;\n        result.root[source] = source;\n  \
    \      result.tin[source] = ++timer;\n        result.preorder.push_back(source);\n\
    \        result.roots.push_back(source);\n        invoke_callback(callback, source,\
    \ -1);\n        stack.push_back(Frame{source, 0});\n\n        while (!stack.empty())\
    \ {\n            Frame& frame = stack.back();\n            int vertex = frame.vertex;\n\
    \            if (frame.next_edge == int(graph[vertex].size())) {\n           \
    \     result.tout[vertex] = ++timer;\n                result.postorder.push_back(vertex);\n\
    \                stack.pop_back();\n                continue;\n            }\n\
    \n            const Edge<T>& edge = graph[vertex][frame.next_edge++];\n      \
    \      if (!edge.alive || result.reachable(edge.to)) continue;\n            result.depth[edge.to]\
    \ = result.depth[vertex] + 1;\n            result.parent[edge.to] = vertex;\n\
    \            result.parent_edge[edge.to] = edge.id;\n            result.root[edge.to]\
    \ = result.root[vertex];\n            result.tin[edge.to] = ++timer;\n       \
    \     result.preorder.push_back(edge.to);\n            invoke_callback(callback,\
    \ edge.to, vertex);\n            stack.push_back(Frame{edge.to, 0});\n       \
    \ }\n    };\n\n    for (int source : sources) traverse(source);\n    if (complete_forest)\
    \ {\n        for (int vertex = 0; vertex < n; vertex++) traverse(vertex);\n  \
    \  }\n    return result;\n}\n\n}  // namespace dfs_detail\n\ntemplate <class T>\n\
    DfsResult dfs(const Graph<T>& graph, const std::vector<int>& sources) {\n    auto\
    \ callback = [](int) {};\n    return dfs_detail::run_dfs(graph, sources, false,\
    \ callback);\n}\n\ntemplate <class T>\nDfsResult dfs(const Graph<T>& graph, int\
    \ source) {\n    return dfs(graph, std::vector<int>{source});\n}\n\ntemplate <class\
    \ T>\nDfsResult dfs(const Graph<T>& graph) {\n    auto callback = [](int) {};\n\
    \    return dfs_detail::run_dfs(\n        graph,\n        std::vector<int>(),\n\
    \        true,\n        callback\n    );\n}\n\ntemplate <class T, class Callback>\n\
    requires dfs_detail::DfsCallback<Callback>\nDfsResult dfs(\n    const Graph<T>&\
    \ graph,\n    const std::vector<int>& sources,\n    Callback&& callback\n) {\n\
    \    return dfs_detail::run_dfs(graph, sources, false, callback);\n}\n\ntemplate\
    \ <class T, class Callback>\nrequires dfs_detail::DfsCallback<Callback>\nDfsResult\
    \ dfs(const Graph<T>& graph, int source, Callback&& callback) {\n    return dfs(\n\
    \        graph,\n        std::vector<int>{source},\n        std::forward<Callback>(callback)\n\
    \    );\n}\n\ntemplate <class T, class Callback>\nrequires dfs_detail::DfsCallback<Callback>\n\
    DfsResult dfs(const Graph<T>& graph, Callback&& callback) {\n    return dfs_detail::run_dfs(\n\
    \        graph,\n        std::vector<int>(),\n        true,\n        callback\n\
    \    );\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_DFS_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/dfs.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  - graph/directed.hpp
  timestamp: '2026-07-16 19:40:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/dfs.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/dfs.hpp
layout: document
title: DFS
---

## Overview

`dfs` performs iterative depth-first search and returns the DFS forest rather
than recursing through the call stack. It provides parent paths, depths,
discovery and finish times, preorder, postorder, and component roots.

Callback overloads additionally invoke a callback once when each vertex is
discovered. They still return the complete `DfsResult`, and callback order is
exactly `result.preorder`.

Use DFS when traversal nesting or finish order matters. The returned path is a
DFS-tree path and is not necessarily shortest; use `bfs` for unweighted shortest
paths.

## Graph Orientation and Roots

Edge direction is respected. The helper works on directed graphs as written and
on undirected graphs built with `add_edge`. Inactive edges are ignored, and
adjacency-list order determines which DFS tree is produced.

`dfs(graph, source)` traverses one source. The multi-source overload completely
traverses each source in the supplied order, skipping sources already reached
by an earlier tree. `dfs(graph)` constructs a complete forest, choosing the
smallest still-unvisited vertex as each new root.

Callbacks must not mutate the graph. They may safely update captured state.

## Callback Signature

The primary callback signature is:

```cpp
callback(int vertex, int parent);
```

`parent` is the DFS-tree parent of `vertex`. It is `-1` when `vertex` is a
single source or a root of the complete forest. For convenience, a callback
with signature `callback(int vertex)` is also accepted when parent information
is not needed.

## Result

| Member or method | Exact type or signature | Meaning |
| --- | --- | --- |
| `depth` | `std::vector<int>` | DFS-tree depth, or `-1` when unreachable. |
| `parent` | `std::vector<int>` | Parent vertex, or `-1` for roots and unreachable vertices. |
| `parent_edge` | `std::vector<int>` | Edge used to enter each non-root vertex, or `-1`. |
| `root` | `std::vector<int>` | Root of each reached vertex's DFS tree, or `-1`. |
| `tin`, `tout` | `std::vector<int>` | One-based discovery and finish timestamps, or `-1`. Every timestamp is distinct. |
| `preorder` | `std::vector<int>` | Vertices in discovery order. |
| `postorder` | `std::vector<int>` | Vertices in finish order. |
| `roots` | `std::vector<int>` | DFS-tree roots in traversal order. |
| `reachable` | `bool reachable(int vertex) const` | Tests whether `vertex` was reached. |
| `component_count` | `int component_count() const` | Returns `roots.size()`. |
| `path` | `std::vector<int> path(int target) const` | Restores the root-to-`target` DFS-tree path. |
| `is_ancestor` | `bool is_ancestor(int ancestor, int vertex) const` | Tests ancestry through timestamp containment; returns false if either vertex is unreachable. |

## Functions

| Function | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| `dfs` | `template <class T> DfsResult dfs(const Graph<T>& graph, int source)` | Traverses vertices reachable from one source. | $O(N + M)$ time and $O(N)$ memory |
| `dfs` | `template <class T> DfsResult dfs(const Graph<T>& graph, const std::vector<int>& sources)` | Traverses ordered source trees. | $O(N + M)$ time and $O(N)$ memory |
| `dfs` | `template <class T> DfsResult dfs(const Graph<T>& graph)` | Traverses the complete DFS forest. | $O(N + M)$ time and $O(N)$ memory |
| `dfs` | `template <class T, class Callback> DfsResult dfs(const Graph<T>& graph, int source, Callback&& callback)` | Single-source DFS with one callback per discovered vertex. | $O(N + M + RF)$ time and $O(N)$ memory |
| `dfs` | `template <class T, class Callback> DfsResult dfs(const Graph<T>& graph, const std::vector<int>& sources, Callback&& callback)` | Ordered multi-source DFS with discovery callbacks. | $O(N + M + RF)$ time and $O(N)$ memory |
| `dfs` | `template <class T, class Callback> DfsResult dfs(const Graph<T>& graph, Callback&& callback)` | Complete DFS forest with discovery callbacks. | $O(N + M + NF)$ time and $O(N)$ memory |

Here, `R` is the number of reached vertices and `F` is the cost of one callback.

## Example

```cpp
#include "graph/dfs.hpp"
#include "graph/graph.hpp"

#include <cassert>
#include <vector>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(0, 3);

    std::vector<int> discovered;
    auto result = m1une::graph::dfs(
        graph,
        0,
        [&](int vertex, int parent) {
            discovered.push_back(vertex);
            if (vertex == 0) assert(parent == -1);
        }
    );
    assert(result.reachable(2));
    assert(result.is_ancestor(0, 2));
    assert(result.path(2).front() == 0);
    assert(discovered == result.preorder);
}
```
