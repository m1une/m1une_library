---
title: st-Numbering
documentation_of: ../../graph/st_numbering.hpp
---

## Overview

`st_numbering(graph, source, sink)` finds a bipolar numbering of an undirected
graph. It returns a rank `p[v]` for every vertex such that:

- `p` is a permutation of `0, ..., N - 1`;
- `p[source] = 0` and `p[sink] = N - 1`;
- every other vertex has an active neighbor of smaller rank and an active
  neighbor of larger rank.

Orienting every edge from smaller to larger rank then gives, for every vertex,
a directed path from `source` through that vertex to `sink`. If no such
numbering exists, the function returns an empty vector.

## Graph Requirements

Build the undirected graph with `Graph<T>::add_edge`. The graph must contain at
least two vertices, and `source` and `sink` must be distinct valid vertices.

Parallel edges are supported. Inactive edges and self-loops are ignored. The
algorithm is iterative and does not mutate the graph.

## API

```cpp
template <class T>
std::vector<int> st_numbering(
    const Graph<T>& graph,
    int source,
    int sink
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `st_numbering(graph, source, sink)` | Returns vertex ranks, or an empty vector when impossible. | `O(N + M)` time and `O(N)` auxiliary memory |

Here `M` is the number of active undirected edges. The returned vector is indexed by
vertex, not by rank: `result[v]` is the number assigned to `v`.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/st_numbering.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    auto rank = m1une::graph::st_numbering(graph, 0, 3);
    for (int vertex = 0; vertex < graph.size(); vertex++) {
        std::cout << rank[vertex] << "\n";
    }
}
```
