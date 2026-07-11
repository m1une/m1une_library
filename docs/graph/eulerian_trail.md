---
title: Eulerian Trail
documentation_of: ../../graph/eulerian_trail.hpp
---

## Overview

An Eulerian trail uses every active edge exactly once. This header implements
iterative Hierholzer traversals for both directed and undirected graphs and
returns the original edge IDs alongside the visited vertices.

Parallel edges and self-loops are supported. Inactive edges are ignored.

## Graph Orientation

Use `directed_eulerian_trail` with graphs built by `add_directed_edge`, and
`undirected_eulerian_trail` with graphs built by `add_edge`. Mixing directed and
undirected edge representations in one call is not supported.

## API

```cpp
struct EulerianTrail {
    std::vector<int> vertices;
    std::vector<int> edge_ids;

    int edge_count() const;
    bool is_circuit() const;
};

template <class T>
std::optional<EulerianTrail> directed_eulerian_trail(
    const Graph<T>& graph,
    int start = -1
);

template <class T>
std::optional<EulerianTrail> undirected_eulerian_trail(
    const Graph<T>& graph,
    int start = -1
);
```

| Interface | Description | Complexity |
| --- | --- | --- |
| `vertices` | Trail vertices; for `M` used edges, contains `M + 1` vertices unless the graph itself has no vertices. | -- |
| `edge_ids` | Active edge IDs in traversal order. | -- |
| `edge_count()` | Number of edges in the trail. | $O(1)$ |
| `is_circuit()` | Whether the trail is closed. An empty-graph trail is considered closed. | $O(1)$ |
| `directed_eulerian_trail(graph, start)` | Finds a direction-respecting trail, if one exists. | $O(N + M)$ |
| `undirected_eulerian_trail(graph, start)` | Finds an undirected trail, if one exists. | $O(N + M)$ |

The default `start == -1` chooses a valid start automatically. Supplying a
vertex forces the trail to start there; the function returns `std::nullopt` if
an Eulerian trail exists only from another vertex. Invalid nonnegative start
indices are rejected by an assertion.

For a graph with vertices but no active edges, the automatically selected trail
contains vertex `0` and no edges. A forced start produces that one-vertex trail
instead. For a graph with no vertices, both returned sequences are empty.

The functions check degree conditions and confirm that Hierholzer's traversal
used every active edge, which also detects disconnected edge-bearing parts.
The graph is not mutated.

## Example

```cpp
#include "graph/eulerian_trail.hpp"
#include "graph/graph.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(3);
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(1, 2);
    graph.add_directed_edge(2, 0);

    auto trail = m1une::graph::directed_eulerian_trail(graph);
    std::cout << trail->is_circuit() << "\n";  // 1
    for (int edge_id : trail->edge_ids) std::cout << edge_id << " ";
    std::cout << "\n";
}
```
