---
title: Tree
documentation_of: ../../../graph/tree/tree.hpp
---

## Overview

`graph/tree/tree.hpp` is a small tree bundle containing the core rooted-tree
helpers, the sparse-table LCA helper, and the diameter routine.

For the full tree toolbox, include `graph/tree/all.hpp`.

## Included Headers

| Header | Contents |
| --- | --- |
| `graph/tree/euler_tour.hpp` | Lightweight rooted-tree preorder, subtree ranges, and parent/depth metadata. |
| `graph/tree/rooted_tree.hpp` | Rooted metadata, Euler intervals, LCA, jumps, paths, and distances. |
| `graph/tree/sparse_table_lca.hpp` | Euler-tour sparse-table LCA with $O(1)$ queries. |
| `graph/tree/diameter.hpp` | Weighted tree/forest diameter path. |

## Complexity

This header is an include bundle and provides no runtime operation by itself.
See the included helper pages for public interfaces and complexities.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/tree/tree.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    m1une::tree::RootedTree tree(g, 0);
    std::cout << tree.lca(0, 2) << "\n";
}
```
