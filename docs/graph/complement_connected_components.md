---
title: Complement-Graph Connected Components
documentation_of: ../../graph/complement_connected_components.hpp
---

## Overview

`complement_connected_components` partitions the vertices into connected
components of the complement graph. Two distinct vertices are adjacent in the
complement exactly when they are not adjacent in the input graph.

The complement can have quadratically many edges. This implementation scans an
intrusive list of unassigned vertices and never constructs those edges, keeping
the running time and memory linear in the input size.

## Graph Interpretation

Every active edge of `Graph<T>` is treated as an undirected edge, regardless of
how it was inserted. Self-loops are ignored. Parallel edges are treated as one
edge, so they do not change the result.

Edge costs are ignored. The graph is not mutated.

## API

The function reuses `ConnectedComponents`, the result type of the ordinary
`connected_components` function.

```cpp
struct ConnectedComponents {
    int count;
    std::vector<int> comp;
    std::vector<std::vector<int>> groups;

    bool same(int first, int second) const;
};

template <class T>
ConnectedComponents complement_connected_components(const Graph<T>& graph);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `count` | Number of complement-graph components. | $O(1)$ |
| `comp[v]` | Component containing vertex `v`. | $O(1)$ |
| `groups[c]` | Vertices in component `c`; their order is unspecified. | -- |
| `same(first, second)` | Whether two vertices belong to the same complement-graph component. | $O(1)$ |
| `complement_connected_components(graph)` | Computes the complete partition without building the complement. | $O(N+M)$ time and memory |

For an empty graph, `count` is `0` and both vectors are empty.

## Example

```cpp
#include "graph/complement_connected_components.hpp"
#include "graph/graph.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(0, 3);

    auto result = m1une::graph::complement_connected_components(graph);
    std::cout << result.count << "\n";      // 2
    std::cout << result.same(1, 3) << "\n";  // 1
    std::cout << result.same(0, 1) << "\n";  // 0
}
```
