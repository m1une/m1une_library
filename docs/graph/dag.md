---
title: DAG Algorithms
documentation_of: ../../graph/dag.hpp
---

## Overview

`graph/dag.hpp` is the contest-oriented include bundle for directed acyclic
graphs. It combines ordering, weighted paths, path counting, reachability,
transitive reduction, and minimum path cover without introducing a second graph
container.

All algorithms use `Graph<T>` and ignore inactive edges. Operations that require
acyclic input return `std::nullopt` when a directed cycle exists.

## Included Headers

| Header | Contents |
| --- | --- |
| `graph/topological_sort.hpp` | Topological ordering and DAG recognition. |
| `graph/dag_shortest_path.hpp` | Minimum-cost paths, including negative edge costs. |
| `graph/dag_longest_path.hpp` | Maximum-cost paths and reconstruction. |
| `graph/dag_path_count.hpp` | Counts paths from one or more sources. |
| `graph/dag_reachability.hpp` | Batched reachability and transitive reduction. |
| `graph/dag_path_cover.hpp` | Minimum vertex-disjoint path cover. |

This header provides no additional runtime operation. See the individual pages
for exact signatures, assumptions, and complexities.

## Example

```cpp
#include "graph/dag.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_directed_edge(0, 1, 4);
    g.add_directed_edge(1, 2, 5);

    auto longest = m1une::graph::dag_longest_path(g, 0);
    auto ways = m1une::graph::dag_path_count(g, 0);
    if (longest && ways) {
        std::cout << longest->dist[2] << ' ' << (*ways)[2] << '\n';
    }
}
```
