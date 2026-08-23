---
title: Minimum DAG Path Cover
documentation_of: ../../graph/dag_path_cover.hpp
---

## Overview

`minimum_dag_path_cover` partitions all vertices of a DAG into the minimum
number of vertex-disjoint directed paths. Every consecutive pair in a returned
path is joined by an active input edge; paths do not jump through intermediate
vertices. Isolated vertices become one-vertex paths.

The implementation reduces the problem to maximum bipartite matching. Parallel
edges are allowed and inactive edges are ignored. A cyclic graph returns
`std::nullopt`.

## Result

| Member / method | Type / signature | Meaning | Complexity |
| --- | --- | --- | --- |
| `paths` | `std::vector<std::vector<int>>` | Minimum path partition as vertex sequences. | Access: $O(1)$ |
| `path_edge_ids` | `std::vector<std::vector<int>>` | Original edge ids between consecutive vertices of each path. | Access: $O(1)$ |
| `predecessor` | `std::vector<int>` | Previous vertex in the cover, or `-1`. | Access: $O(1)$ |
| `successor` | `std::vector<int>` | Next vertex in the cover, or `-1`. | Access: $O(1)$ |
| `predecessor_edge` | `std::vector<int>` | Input edge from the predecessor, or `-1`. | Access: $O(1)$ |
| `successor_edge` | `std::vector<int>` | Input edge to the successor, or `-1`. | Access: $O(1)$ |
| `size` | `int size() const` | Number of paths in the cover. | $O(1)$ |

## Function

| Function | Signature | Complexity |
| --- | --- | --- |
| `minimum_dag_path_cover` | `template <class T> std::optional<DagPathCoverResult> minimum_dag_path_cover(const Graph<T>& g)` | $O(N + M\sqrt N)$ time and $O(N + M)$ memory |

## Example

```cpp
#include "graph/dag_path_cover.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(5);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(1, 2);
    g.add_directed_edge(3, 4);

    auto cover = m1une::graph::minimum_dag_path_cover(g);
    if (cover) std::cout << cover->size() << '\n';  // 2
}
```
