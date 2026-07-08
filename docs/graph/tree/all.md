---
title: Tree All
documentation_of: ../../../graph/tree/all.hpp
---

## Overview

`graph/tree/all.hpp` includes every tree header in this directory. Most
algorithms use `m1une::graph::Graph<T>` as their input container, and
sequence-derived helpers such as Cartesian tree can convert their result to the
same graph container.

## Included Headers

| Header | Contents |
| --- | --- |
| `graph/tree/cartesian_tree.hpp` | Cartesian tree construction from an array. |
| `graph/tree/tree.hpp` | Core rooted tree and diameter bundle. |
| `graph/tree/rooted_tree.hpp` | Rooted metadata, Euler intervals, LCA, jumps, paths, and distances. |
| `graph/tree/sparse_table_lca.hpp` | Euler-tour sparse-table LCA with $O(1)$ queries. |
| `graph/tree/heavy_light_decomposition.hpp` | HLD order, path segments, subtree ranges, LCA, and jumps. |
| `graph/tree/diameter.hpp` | Weighted tree/forest diameter path. |
| `graph/tree/tree_hash.hpp` | Probabilistic rooted-subtree and unrooted-tree isomorphism hashes. |
| `graph/tree/dsu_on_tree.hpp` | Iterative small-to-large subtree processing with user callbacks. |
| `graph/tree/rerooting_dp.hpp` | Generic rerooting DP helper. |
| `graph/tree/static_top_tree.hpp` | Dynamic one-root tree DP on a fixed tree using static top-tree clusters. |
| `graph/tree/rerooting_static_top_tree.hpp` | Bidirectional static top-tree clusters for dynamic rerooting-DP solutions. |
| `graph/tree/centroid_decomposition.hpp` | Centroid decomposition for trees and forests. |
| `graph/tree/virtual_tree.hpp` | Virtual-tree compression for a selected vertex set. |
| `graph/tree/zero_one_on_tree.hpp` | Minimum inversions in an ancestor-respecting order of binary-labeled vertices. |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/tree/all.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    auto diameter = m1une::tree::tree_diameter(g);
    std::cout << diameter.edge_count << "\n";
}
```
