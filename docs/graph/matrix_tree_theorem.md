---
title: Matrix-Tree Theorem
documentation_of: ../../graph/matrix_tree_theorem.hpp
---

## Overview

`matrix_tree_theorem.hpp` counts spanning trees with a determinant of a
Laplacian cofactor. It supports undirected spanning trees and both orientations
of rooted directed spanning trees.

The functions are weighted. The weight of one tree is the product of its edge
weights, and the answer is the sum of those products over every valid tree.
Using the default graph edge weight `1` gives the ordinary number of trees.

Parallel edges are distinct choices and are supported. Self-loops never belong
to a spanning tree and are ignored. Inactive edges are also ignored. A
disconnected graph, or a directed graph with no valid rooted arborescence,
returns `0`.

## Requirements

`Field` must provide exact field arithmetic: construction from an edge weight,
addition, subtraction, multiplication, division by a nonzero value, and exact
comparison with zero. A modular integer with a prime modulus, such as
`m1une::math::modint998244353`, is the usual choice. Plain integer types are not
suitable because Gaussian elimination divides by pivot values.

The graph must contain at least one vertex. `count_spanning_trees` expects edges
created with `Graph::add_edge`. The directed functions expect edges created with
`Graph::add_directed_edge`. Debug builds assert these storage conventions and
the validity of `root`.

All intermediate field values and the result must be representable by `Field`.

## Directed Orientation

`count_out_arborescences(graph, root)` counts directed spanning trees whose
edges point away from `root`. Every vertex is reachable from `root`, and every
non-root vertex has exactly one selected incoming edge.

`count_in_arborescences(graph, root)` counts directed spanning trees whose edges
point toward `root`. The root is reachable from every vertex, and every non-root
vertex has exactly one selected outgoing edge.

Reversing every edge swaps these two answers.

## Interface

All functions are in namespace `m1une::graph`.

| Function | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| `count_spanning_trees` | `template <class Field, class Weight> Field count_spanning_trees(const Graph<Weight>& graph)` | Returns the total weight of all undirected spanning trees. | $O(N^3 + M)$ time, $O(N^2 + M)$ auxiliary memory in debug builds and $O(N^2)$ in release builds. |
| `count_out_arborescences` | `template <class Field, class Weight> Field count_out_arborescences(const Graph<Weight>& graph, int root)` | Returns the total weight of all directed spanning trees rooted outward at `root`. | $O(N^3 + M)$ time, $O(N^2 + M)$ auxiliary memory in debug builds and $O(N^2)$ in release builds. |
| `count_in_arborescences` | `template <class Field, class Weight> Field count_in_arborescences(const Graph<Weight>& graph, int root)` | Returns the total weight of all directed spanning trees rooted inward at `root`. | $O(N^3 + M)$ time, $O(N^2 + M)$ auxiliary memory in debug builds and $O(N^2)$ in release builds. |

The functions do not mutate the graph. For a one-vertex graph, each function
returns `1`: the empty edge set is the unique spanning tree.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/matrix_tree_theorem.hpp"
#include "math/modint.hpp"

#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;

    m1une::graph::Graph<int> graph(3);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);

    mint answer = m1une::graph::count_spanning_trees<mint>(graph);
    std::cout << answer << '\n';  // 3
}
```
