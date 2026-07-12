---
title: Graph All
documentation_of: ../../graph/all.hpp
---

## Overview

`graph/all.hpp` includes the general graph bundle plus the tree and flow
subcategories. It is convenient when writing quickly during a contest and you do
not want to manage individual graph includes.

Public namespaces stay flat and short: general graph helpers use
`m1une::graph`, tree helpers use `m1une::tree`, and flow helpers use
`m1une::flow`.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/graph.hpp` | Container | `Graph<T>` and `Edge<T>` adjacency-list container. |
| `graph/tree/all.hpp` | Tree algorithms | Euler tours, rooted-tree metadata, LCA, HLD, Cartesian tree construction, virtual trees, tree hashing, rerooting DP, static top trees, and centroid decomposition. |
| `graph/flow/flow.hpp` | Flow networks | Max flow, min-cost flow, bounded flow, bounded min-cost flow, and Gomory-Hu trees. |
| `graph/counting.hpp` | Counting formulas | Counts common labeled graph classes, tournaments, DAGs, and unlabeled trees by vertex number. |
| `graph/range_edge_graph.hpp` | Directed graph builder | Compact point-to-range, range-to-point, and range-to-range edges using segment trees. |
| `graph/shortest_path.hpp` | Direction-respecting / DAG-specific | Cow game difference constraints, BFS, 0-1 BFS, DAG shortest path, Dijkstra, k-shortest walk, Bellman-Ford, and Warshall-Floyd. |
| `graph/directed.hpp` | Directed-oriented bundle | Directed algorithms plus shortest paths. |
| `graph/undirected.hpp` | Undirected-oriented bundle | Undirected algorithms plus shortest paths and grid helpers. |
| `graph/bfs.hpp` | Direction-respecting | Unweighted shortest paths. |
| `graph/zero_one_bfs.hpp` | Direction-respecting | Shortest paths with edge costs `0` or `1`. |
| `graph/dag_shortest_path.hpp` | Directed DAG only | Shortest paths in a DAG, including negative edge costs. |
| `graph/dijkstra.hpp` | Direction-respecting | Non-negative weighted shortest paths. |
| `graph/k_shortest_walk.hpp` | Direction-respecting | The first `k` walk lengths with non-negative edge costs. |
| `graph/bellman_ford.hpp` | Direction-respecting | Shortest paths with negative edges and negative-cycle marking. |
| `graph/cow_game.hpp` | Difference constraints | Feasibility, assignments, and tight bounds for systems of difference inequalities. |
| `graph/warshall_floyd.hpp` | Direction-respecting | All-pairs shortest paths. |
| `graph/grid.hpp` | Undirected graph builder | Helper for converting 2D grid cells to graph vertex ids. |
| `graph/topological_sort.hpp` | Directed only | DAG ordering and cycle check. |
| `graph/dominator_tree.hpp` | Directed rooted graph | Lengauer-Tarjan immediate dominators and dominator tree. |
| `graph/directed_mst.hpp` | Directed rooted graph | Minimum-cost spanning arborescence with edge reconstruction. |
| `graph/scc.hpp` | Directed only | Strongly connected components and condensation DAG. |
| `graph/two_sat.hpp` | Implication graph | 2-SAT clauses, satisfiability, and one assignment. |
| `graph/lowlink.hpp` | Undirected only | Articulation points and bridges. |
| `graph/biconnected_components.hpp` | Undirected only | Vertex-biconnected blocks, articulation points, and block incidence. |
| `graph/block_cut_tree.hpp` | Undirected only | Block-cut forest and original-vertex-to-node mappings. |
| `graph/two_edge_connected_components.hpp` | Undirected only | Two-edge-connected components, bridges, and the contracted bridge forest. |
| `graph/bipartite.hpp` | Direction ignored / explicit bipartite sides | Two-colorability, maximum matching, minimum vertex cover, maximum independent set, and minimum edge cover. |
| `graph/general_matching.hpp` | Undirected only | Maximum-cardinality matching and minimum edge cover in general undirected graphs. |
| `graph/maximum_clique.hpp` | Direction ignored | Exact maximum clique, maximum independent set, and minimum vertex cover with bitset branch-and-bound. |
| `graph/chromatic_number.hpp` | Direction ignored | Exact chromatic number for graphs with at most 20 vertices. |
| `graph/minimum_steiner_tree.hpp` | Undirected only | Exact edge- and vertex-weighted minimum Steiner-tree costs and reconstruction for a small terminal set. |
| `graph/replacement_paths.hpp` | Undirected positive-weight graphs | Edge- and vertex-failure replacement distances along one fixed shortest path. |
| `graph/namori.hpp` | Undirected Namori graph | Decomposes each unicyclic component into its cycle and attached rooted trees. |
| `graph/connected_components.hpp` | Direction ignored | Weak/ordinary connected components. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Finds one cycle with the matching function. |
| `graph/eulerian_trail.hpp` | Directed and undirected variants | Hierholzer Eulerian trails with original edge IDs. |
| `graph/kruskal.hpp` | Undirected only | Minimum spanning forest. |

## Example

```cpp
#include "graph/all.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 10);
    auto dist = m1une::graph::dijkstra(g, 0).dist;
    std::cout << dist[1] << "\n";
}
```
