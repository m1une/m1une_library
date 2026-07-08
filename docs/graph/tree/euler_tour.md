---
title: Euler Tour
documentation_of: ../../../graph/tree/euler_tour.hpp
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
