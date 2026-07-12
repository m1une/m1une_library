---
title: Block-Cut Tree
documentation_of: ../../graph/block_cut_tree.hpp
---

## Overview

This header converts a vertex-biconnected-components decomposition into its
block-cut forest. Each block becomes one node, each articulation vertex becomes
one node, and an edge joins a block to every articulation vertex it contains.
For a connected input graph the result is a tree; for a disconnected graph it
is a forest.

Every original vertex has a canonical node. An articulation vertex maps to its
articulation node, while any other vertex maps to its unique block node. This is
useful for reducing vertex-separator path queries to ordinary tree queries.

## Graph Requirements

The same requirements as `biconnected_components` apply: build an undirected
graph with `Graph<T>::add_edge`; self-loops are unsupported, parallel edges are
supported, and inactive edges are ignored. Isolated vertices become isolated
block nodes.

## Node Numbering

Block nodes have IDs in `[0, block_count())`, in the same order as
`BiconnectedComponentsResult::components`. Articulation nodes follow block
nodes, in increasing order of the original vertex ID.

## API

```cpp
struct BlockCutTreeResult {
    std::vector<std::vector<int>> forest;
    std::vector<int> node_of_block;
    std::vector<int> node_of_articulation;
    std::vector<int> node_of_vertex;
    std::vector<int> block_of_node;
    std::vector<int> articulation_of_node;

    int node_count() const;
    int block_count() const;
    bool is_block_node(int node) const;
    bool is_articulation_node(int node) const;
};

BlockCutTreeResult block_cut_tree(
    const BiconnectedComponentsResult& biconnected
);

template <class T>
BlockCutTreeResult block_cut_tree(const Graph<T>& graph);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `forest[node]` | Adjacent nodes in the block-cut forest. | -- |
| `node_of_block[block]` | Forest node representing `block`. | $O(1)$ |
| `node_of_articulation[v]` | Articulation node for original vertex `v`, or `-1` if `v` is not an articulation. | $O(1)$ |
| `node_of_vertex[v]` | Canonical forest node representing original vertex `v`. | $O(1)$ |
| `block_of_node[node]` | Original block ID, or `-1` for an articulation node. | $O(1)$ |
| `articulation_of_node[node]` | Original articulation vertex, or `-1` for a block node. | $O(1)$ |
| `node_count()` | Number of block and articulation nodes. | $O(1)$ |
| `block_count()` | Number of block nodes. | $O(1)$ |
| `is_block_node(node)` | Whether `node` represents a block. | $O(1)$ |
| `is_articulation_node(node)` | Whether `node` represents an articulation vertex. | $O(1)$ |
| `block_cut_tree(biconnected)` | Builds the forest from an existing decomposition. | $O(N + M)$ |
| `block_cut_tree(graph)` | Computes the decomposition and builds the forest. | $O(N + M)$ |

The graph overload does not mutate the input. The result owns its vectors and
uses $O(N + M)$ memory. Use the decomposition overload when the blocks are also
needed, so they are not computed twice.

## Example

```cpp
#include "graph/block_cut_tree.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(5);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);
    graph.add_edge(1, 3);
    graph.add_edge(3, 4);

    auto biconnected = m1une::graph::biconnected_components(graph);
    auto block_cut = m1une::graph::block_cut_tree(biconnected);
    std::cout << block_cut.node_count() << "\n";  // 5
    std::cout << block_cut.node_of_articulation[1] << "\n";
    std::cout << block_cut.node_of_vertex[0] << "\n";
}
```
