---
title: Biconnected Components
documentation_of: ../../graph/biconnected_components.hpp
---

## Overview

This header decomposes an undirected graph into maximal vertex-biconnected
blocks. Every active edge belongs to exactly one block. An articulation vertex
belongs to two or more blocks, while an isolated vertex forms a singleton
block with no edges.

Pass the result to `block_cut_tree` from `graph/block_cut_tree.hpp` to build the
block-cut forest and original-vertex-to-node mappings.

## Graph Requirements

Build the graph with `Graph<T>::add_edge`. Directed edges and self-loops are not
supported. Parallel edges are supported because traversal identifies edges by
their shared edge IDs. Inactive edges are ignored; a vertex incident only to
inactive edges is treated as isolated.

The traversal is iterative, so a path with hundreds of thousands of vertices
does not consume the call stack.

## API

```cpp
struct BiconnectedComponentsResult {
    std::vector<std::vector<int>> components;
    std::vector<std::vector<int>> edge_components;
    std::vector<int> component_of_edge;
    std::vector<std::vector<int>> vertex_components;
    std::vector<int> articulation;
    std::vector<int> ord;
    std::vector<int> low;

    int component_count() const;
    bool is_articulation(int vertex) const;
};

template <class T>
BiconnectedComponentsResult biconnected_components(const Graph<T>& graph);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `components[c]` | Vertices belonging to block `c`; their order is unspecified. | -- |
| `edge_components[c]` | Active edge IDs belonging to block `c`. Singleton blocks have no edges. | -- |
| `component_of_edge[e]` | Block containing edge `e`, or `-1` when edge `e` is inactive. | $O(1)$ |
| `vertex_components[v]` | All blocks containing vertex `v`. | -- |
| `articulation` | Articulation vertices in increasing vertex order. | -- |
| `ord[v]`, `low[v]` | DFS order and lowlink value of vertex `v`. | $O(1)$ |
| `component_count()` | Number of blocks, including isolated singleton blocks. | $O(1)$ |
| `is_articulation(v)` | Whether `v` belongs to at least two blocks. | $O(1)$ |
| `biconnected_components(graph)` | Computes the complete decomposition. | $O(N + M)$ |

The result owns all returned vectors and does not mutate the graph. Across all
components, vertex incidences and stored edge IDs use $O(N + M)$ memory.

## Example

```cpp
#include "graph/biconnected_components.hpp"
#include "graph/graph.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(5);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);
    graph.add_edge(1, 3);
    graph.add_edge(3, 4);

    auto result = m1une::graph::biconnected_components(graph);
    std::cout << result.component_count() << "\n";  // 3
    std::cout << result.is_articulation(1) << "\n";  // 1
    std::cout << result.is_articulation(3) << "\n";  // 1
}
```
