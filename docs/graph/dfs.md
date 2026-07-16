---
title: DFS
documentation_of: ../../graph/dfs.hpp
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
