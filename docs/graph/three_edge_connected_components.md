---
title: Three-Edge-Connected Components
documentation_of: ../../graph/three_edge_connected_components.hpp
---

## Overview

Two vertices are three-edge-connected when at least three edge-disjoint paths
join them. Equivalently, deleting any two edges cannot separate them.

`three_edge_connected_components` partitions the vertices into the maximal sets
defined by this relation. It uses the linear-time one-pass contraction algorithm
of Tsin.

## Graph Requirements

Build the undirected graph with `Graph<T>::add_edge`. Directed edges are not
supported. The graph may be disconnected.

Parallel edges are distinct and therefore contribute separately to edge
connectivity. Self-loops do not join different vertices and are ignored.
Inactive edges are also ignored.

The DFS is iterative, so a path or cycle with many vertices does not consume
the call stack.

## API

```cpp
struct ThreeEdgeConnectedComponentsResult {
    std::vector<std::vector<int>> components;
    std::vector<int> component_of_vertex;

    int component_count() const;
    bool same(int first, int second) const;
};

template <class T>
ThreeEdgeConnectedComponentsResult three_edge_connected_components(
    const Graph<T>& graph
);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `components[c]` | Vertices in component `c`; their order is unspecified. | -- |
| `component_of_vertex[v]` | Component containing vertex `v`. | $O(1)$ |
| `component_count()` | Number of three-edge-connected components. | $O(1)$ |
| `same(u, v)` | Whether `u` and `v` are three-edge-connected. | $O(1)$ |
| `three_edge_connected_components(graph)` | Computes the complete decomposition. | $O(N+M)$ |

The function uses $O(N+M)$ memory including the input graph and does not mutate
the graph.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/three_edge_connected_components.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(3);
    graph.add_edge(0, 1);
    graph.add_edge(0, 1);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    auto result = m1une::graph::three_edge_connected_components(graph);
    std::cout << result.same(0, 1) << "\n";  // 1
    std::cout << result.same(1, 2) << "\n";  // 0
}
```
