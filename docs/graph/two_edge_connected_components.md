---
title: Two-Edge-Connected Components
documentation_of: ../../graph/two_edge_connected_components.hpp
---

## Overview

Two connected vertices are in the same two-edge-connected component when
deleting any single edge cannot separate them. Equivalently, remove every
bridge and take the connected components that remain.

This header returns that decomposition, all bridge IDs, and the forest obtained
by contracting every component. Each contracted edge remembers the ID of its
original bridge.

## Graph Requirements

Build the undirected graph with `Graph<T>::add_edge`. Directed edges are not
supported. Parallel edges and self-loops are supported: parallel edges prevent
each other from being bridges, and a self-loop is never a bridge.

Inactive edges are ignored. They are not reported as bridges and do not connect
components.

Both traversals are iterative, so deep paths do not consume the call stack.

## API

```cpp
struct TwoEdgeConnectedBridge {
    int from;
    int to;
    int edge_id;
};

struct TwoEdgeConnectedComponentsResult {
    std::vector<std::vector<int>> components;
    std::vector<int> component_of_vertex;
    std::vector<int> bridge_ids;
    std::vector<char> bridge;
    std::vector<TwoEdgeConnectedBridge> bridge_forest_edges;
    std::vector<int> ord;
    std::vector<int> low;

    int component_count() const;
    bool same(int first, int second) const;
    bool is_bridge(int edge_id) const;
};

template <class T>
TwoEdgeConnectedComponentsResult two_edge_connected_components(
    const Graph<T>& graph
);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `components[c]` | Vertices in component `c`; their order is unspecified. | -- |
| `component_of_vertex[v]` | Component containing vertex `v`. | $O(1)$ |
| `bridge_ids` | Active bridge IDs in increasing edge-ID order. | -- |
| `bridge[e]` | Nonzero exactly when active edge `e` is a bridge. | $O(1)$ |
| `bridge_forest_edges` | Component-to-component edges after contraction, with original bridge IDs. | -- |
| `ord[v]`, `low[v]` | DFS order and lowlink value of vertex `v`. | $O(1)$ |
| `component_count()` | Number of two-edge-connected components. | $O(1)$ |
| `same(u, v)` | Whether `u` and `v` belong to the same component. | $O(1)$ |
| `is_bridge(edge_id)` | Whether the active edge is a bridge; inactive edges return false. | $O(1)$ |
| `two_edge_connected_components(graph)` | Computes the decomposition and bridge forest. | $O(N + M)$ |

The function does not mutate the graph and uses $O(N + M)$ memory.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/two_edge_connected_components.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);
    int bridge = graph.add_edge(2, 3);

    auto result = m1une::graph::two_edge_connected_components(graph);
    std::cout << result.component_count() << "\n";  // 2
    std::cout << result.same(0, 2) << "\n";          // 1
    std::cout << result.is_bridge(bridge) << "\n";   // 1
}
```
