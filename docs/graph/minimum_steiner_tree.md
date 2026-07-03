---
title: Minimum Steiner Tree
documentation_of: ../../graph/minimum_steiner_tree.hpp
---

## Overview

Finds the minimum cost of a connected subgraph containing every specified
terminal. Non-terminal vertices may be used as Steiner vertices. The objective
can include edge costs alone or both edge and vertex costs. Each selected edge
and each selected vertex is charged exactly once.

Use `minimum_steiner_tree` when only the optimum cost is needed. Use
`build_minimum_steiner_tree` to also obtain the vertices and logical edge ids of
one optimum tree. The corresponding `_unweighted` functions ignore stored edge
costs and charge one per selected edge.

All overloads use the Dreyfus--Wagner subset DP. Stored edge weights or vertex
weights require a multi-source Dijkstra step for each terminal subset. When all
edges have unit cost and no vertex weights are supplied, a bucketed
multi-source BFS removes the logarithmic factor.

## Requirements and Behavior

The graph must be undirected and should be built with `add_edge`.

* Weighted edge and vertex costs must be non-negative.
* A supplied `vertex_cost` vector must have exactly $N$ elements. Its value for
  every terminal and every selected Steiner vertex is included once.
* `minimum_steiner_tree_unweighted` treats every active edge as having cost one.
* Inactive edges are ignored.
* Duplicate terminals are removed internally.
* An empty terminal set has cost zero. A one-vertex terminal set costs that
  vertex's weight when `vertex_cost` is supplied, and zero otherwise.
* The result is `std::nullopt` when no connected subgraph contains every
  terminal.
* Build functions return an actual acyclic tree. Their `edge_ids` and `vertices`
  are sorted and contain no duplicates.
* Build functions remove redundant zero-cost cycles and non-terminal leaves
  without changing the optimum cost.

The default `inf` for weighted overloads is
`std::numeric_limits<Cost>::max() / Cost(4)`. Pass a larger safe value when a
valid answer can reach that sentinel.

## Result Type

`MinimumSteinerTreeResult<Cost>` contains:

| Member | Type | Description |
| --- | --- | --- |
| `cost` | `Cost` | Total cost of the returned tree. |
| `edge_ids` | `std::vector<int>` | Sorted logical edge ids in the tree. |
| `vertices` | `std::vector<int>` | Sorted vertices in the tree, including every terminal. |

## Functions

Let $N$ be the number of vertices, $M$ the number of undirected edges, and $K$
the number of distinct terminals.

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `minimum_steiner_tree` | `template <class T> std::optional<T> minimum_steiner_tree(const Graph<T>& g, std::vector<int> terminals, T inf = std::numeric_limits<T>::max() / T(4))` | Returns the minimum total stored edge cost. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |
| `minimum_steiner_tree` | `template <class T> std::optional<T> minimum_steiner_tree(const Graph<T>& g, std::vector<int> terminals, const std::vector<T>& vertex_cost, T inf = std::numeric_limits<T>::max() / T(4))` | Returns the minimum total stored edge cost plus selected vertex costs. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |
| `minimum_steiner_tree_unweighted` | `template <class T> std::optional<int> minimum_steiner_tree_unweighted(const Graph<T>& g, std::vector<int> terminals)` | Returns the minimum number of edges, ignoring stored costs. | $O(3^K N + 2^K (N+M))$ time, $O(2^K N + N + M)$ memory. |
| `minimum_steiner_tree_unweighted` | `template <class GraphCost, class Cost> std::optional<Cost> minimum_steiner_tree_unweighted(const Graph<GraphCost>& g, std::vector<int> terminals, const std::vector<Cost>& vertex_cost, Cost inf = std::numeric_limits<Cost>::max() / Cost(4))` | Returns the number of selected edges plus selected vertex costs, ignoring stored edge costs. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |
| `build_minimum_steiner_tree` | `template <class T> std::optional<MinimumSteinerTreeResult<T>> build_minimum_steiner_tree(const Graph<T>& g, std::vector<int> terminals, T inf = std::numeric_limits<T>::max() / T(4))` | Returns one optimum tree using stored edge costs. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |
| `build_minimum_steiner_tree` | `template <class T> std::optional<MinimumSteinerTreeResult<T>> build_minimum_steiner_tree(const Graph<T>& g, std::vector<int> terminals, const std::vector<T>& vertex_cost, T inf = std::numeric_limits<T>::max() / T(4))` | Returns one optimum tree using stored edge and vertex costs. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |
| `build_minimum_steiner_tree_unweighted` | `template <class T> std::optional<MinimumSteinerTreeResult<int>> build_minimum_steiner_tree_unweighted(const Graph<T>& g, std::vector<int> terminals)` | Returns one optimum unit-edge tree. | $O(3^K N + 2^K (N+M))$ time, $O(2^K N + N + M)$ memory. |
| `build_minimum_steiner_tree_unweighted` | `template <class GraphCost, class Cost> std::optional<MinimumSteinerTreeResult<Cost>> build_minimum_steiner_tree_unweighted(const Graph<GraphCost>& g, std::vector<int> terminals, const std::vector<Cost>& vertex_cost, Cost inf = std::numeric_limits<Cost>::max() / Cost(4))` | Returns one optimum tree using unit edge costs and supplied vertex costs. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |

The problem is NP-hard in general, so these functions are intended for small
$K$ (often around 15 terminals, depending on $N$ and the time limit).

## Example

```cpp
#include "graph/minimum_steiner_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<long long> g(5);
    g.add_edge(0, 1, 4);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(3, 4, 3);
    g.add_edge(0, 4, 20);

    std::vector<int> terminals = {0, 2, 4};
    std::vector<long long> vertex_cost = {2, 3, 7, 5, 11};
    auto answer = m1une::graph::build_minimum_steiner_tree(g, terminals, vertex_cost);
    if (answer) {
        std::cout << answer->cost << "\n";  // 38
        for (int edge_id : answer->edge_ids) std::cout << edge_id << " ";
        std::cout << "\n";
    }
}
```
