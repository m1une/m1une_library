---
title: Incremental Strongly Connected Components
documentation_of: ../../graph/incremental_scc.hpp
---

## Overview

`incremental_scc(graph)` processes a known sequence of directed edge
insertions offline. Edge IDs are their insertion positions.

For an edge with ID `e`, the returned value `merge_time[e]` is the smallest
time `t` satisfying `e < t <= M` such that its endpoints belong to the same SCC
after inserting all active edges with IDs less than `t`. The value `M + 1`
means this never happens.

These times describe every SCC merge. Starting with a DSU of singleton
vertices, at each time `t`, merge the endpoints of all edges satisfying
`merge_time[e] == t`. The resulting DSU groups are exactly the SCCs after the
first `t` insertion positions.

## Graph Requirements

Build the graph with `Graph<T>::add_directed_edge`. Parallel edges and
self-loops are supported. Inactive edges are treated as no-op insertion
positions and receive merge time `M + 1`.

The SCC traversals are iterative; only the divide-and-conquer recursion remains,
and its depth is `O(log(M + 1))`. The function does not mutate the graph.

## API

```cpp
template <class T>
std::vector<int> incremental_scc(const Graph<T>& graph);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `incremental_scc(graph)` | Returns the first same-SCC time for every edge ID. | `O((N + M) log(M + 1))` time and `O(N + M)` auxiliary memory |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/incremental_scc.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(3);
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(1, 2);
    graph.add_directed_edge(2, 0);

    auto merge_time = m1une::graph::incremental_scc(graph);
    for (int time : merge_time) {
        std::cout << time << "\n"; // all three values are 3
    }
}
```
