---
title: Undirected Graph Algorithms
documentation_of: ../../graph/undirected.hpp
---

## Overview

`graph/undirected.hpp` includes algorithms whose main interpretation is
undirected, plus the shortest-path bundle. In that bundle, use the
direction-respecting algorithms on graphs built with `add_edge`; the DAG
shortest-path helper is directed-only.

Use this header when edges represent two-way movement or an endpoint constraint
where direction should not matter.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/shortest_path.hpp` | Mixed shortest-path bundle | Use BFS, 0-1 BFS, Dijkstra, Bellman-Ford, and Warshall-Floyd on undirected graphs built with `add_edge`; DAG shortest path is directed-only. |
| `graph/lowlink.hpp` | Undirected only | Articulation points and bridges. |
| `graph/biconnected_components.hpp` | Undirected only | Vertex-biconnected blocks, articulation points, and block incidence. |
| `graph/block_cut_tree.hpp` | Undirected only | Block-cut forest and original-vertex-to-node mappings. |
| `graph/two_edge_connected_components.hpp` | Undirected only | Two-edge-connected components, bridges, and the contracted bridge forest. |
| `graph/kruskal.hpp` | Undirected only | Minimum spanning forest. |
| `graph/bipartite.hpp` | Direction ignored / explicit bipartite sides | Two-colorability, maximum matching, minimum vertex cover, maximum independent set, and minimum edge cover. |
| `graph/general_matching.hpp` | Undirected only | Maximum-cardinality matching and minimum edge cover in general undirected graphs. |
| `graph/general_weighted_matching.hpp` | Undirected only | Maximum-total-weight matching in general undirected graphs. |
| `graph/maximum_clique.hpp` | Direction ignored | Exact maximum clique, maximum independent set, and minimum vertex cover with bitset branch-and-bound. |
| `graph/chromatic_number.hpp` | Direction ignored | Exact chromatic number for graphs with at most 20 vertices. |
| `graph/minimum_steiner_tree.hpp` | Undirected only | Exact edge- and vertex-weighted minimum Steiner-tree costs and reconstruction for a small terminal set. |
| `graph/replacement_paths.hpp` | Undirected positive-weight graphs | Edge- and vertex-failure replacement distances along one fixed shortest path. |
| `graph/namori.hpp` | Undirected Namori graph | Ordered cycles and the trees attached to them. |
| `graph/connected_components.hpp` | Direction ignored | Weak/ordinary connected components. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Use `find_undirected_cycle(g)` for undirected graphs. |
| `graph/enumerate_triangles.hpp` | Direction ignored | Enumerates every triangle through a callback. |
| `graph/eulerian_trail.hpp` | Directed and undirected variants | Use `undirected_eulerian_trail(g)` for undirected graphs. |
| `graph/grid.hpp` | Undirected graph builder | Builds 4/8-neighbor grid graphs. |

## Complexity

This header is an include bundle and provides no runtime operation by itself.
See the included algorithm pages for public interfaces and complexities.
