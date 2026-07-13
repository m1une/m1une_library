---
title: General Weighted Matching
documentation_of: ../../graph/general_weighted_matching.hpp
---

## Overview

`GeneralWeightedMatching<Cost, TotalCost>` finds a matching of maximum total
edge weight in a general undirected graph. Odd cycles and parallel edges are
supported; self-loops are not.

The implementation is a primal-dual weighted blossom algorithm with Gabow's
data structures. It is intended for exact integer-weight matching and runs in
$O(NM\log N)$ time and $O(N+M)$ memory.

## Template Requirements

`Cost` is the edge-weight type and `TotalCost` is the accumulated answer type.
Both must be signed integer types. `TotalCost` defaults to `Cost`; choose a
wider type when the sum can overflow, for example
`GeneralWeightedMatching<int, long long>`.

Positive input weights must not exceed `numeric_limits<Cost>::max() / 2`
because the internal primal-dual representation doubles them.

Only active edges with positive weight are passed to the solver. Omitting zero
and negative edges does not change the maximum possible weight. Consequently,
the algorithm does not promise maximum cardinality among equally weighted
optimal matchings.

## Edge and Pair Fields

`GeneralWeightedMatching::Edge` contains:

| Field / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `from` | `int` | One endpoint. |
| `to` | `int` | The other endpoint. |
| `cost` | `Cost` | Edge weight. |
| `id` | `int` | Edge id returned by `add_edge`. |
| `alive` | `bool` | Whether the edge is currently usable. |
| `other` | `int other(int vertex) const` | Returns the opposite endpoint. |

`GeneralWeightedMatching::Pair` contains:

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | One matched endpoint. |
| `to` | `int` | The other matched endpoint. |
| `cost` | `Cost` | Weight of the selected edge. |
| `edge_id` | `int` | Selected edge id. |

## Methods

All vertex and edge ids are zero-based. Mutating the edge set invalidates the
cached answer; the next matching query recomputes it.

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `GeneralWeightedMatching()` | Constructs an empty graph. | $O(1)$ |
| Constructor | `explicit GeneralWeightedMatching(int n)` | Constructs a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the vertex count. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the registered edge count. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cost cost)` | Adds an active undirected edge and returns its id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int id) const` | Returns edge `id`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges(bool include_inactive = false) const` | Returns active edges, or all registered edges. | $O(M)$ |
| `set_edge_alive` | `void set_edge_alive(int id, bool alive)` | Changes whether an edge is usable. | $O(1)$ |
| `erase_edge` | `void erase_edge(int id)` | Marks an edge inactive. | $O(1)$ |
| `revive_edge` | `void revive_edge(int id)` | Marks an edge active. | $O(1)$ |
| `is_edge_alive` | `bool is_edge_alive(int id) const` | Returns whether an edge is active. | $O(1)$ |
| `max_weight_matching` | `TotalCost max_weight_matching()` | Computes, stores, and returns the maximum weight. | $O(NM\log N)$ |
| `matching_weight` | `TotalCost matching_weight()` | Returns the optimum weight, computing it if needed. | $O(NM\log N)$ if invalidated, otherwise $O(1)$ |
| `matching_size` | `int matching_size()` | Returns the number of selected edges. | $O(NM\log N)$ if invalidated, otherwise $O(N)$ |
| `mate` | `std::vector<int> mate()` | Returns every vertex's mate, or `-1`. | $O(NM\log N)$ if invalidated, otherwise $O(N)$ |
| `mate_edge` | `std::vector<int> mate_edge()` | Returns every vertex's selected edge id, or `-1`. | $O(NM\log N)$ if invalidated, otherwise $O(N)$ |
| `matching` | `std::vector<Pair> matching()` | Returns the selected weighted edges. | $O(NM\log N)$ if invalidated, otherwise $O(N)$ |

`make_general_weighted_matching(const Graph<T>& graph)` copies every active
edge into a `GeneralWeightedMatching<T>` in $O(N+M)$ time. Its returned
`GeneralWeightedMatchingGraph<T>` stores `original_edge_id`, and
`original_edge(edge_id)` maps a matching edge id back to the source graph.
Edge direction in the source `Graph<T>` is ignored.

## Example

```cpp
#include "graph/general_weighted_matching.hpp"

#include <iostream>

int main() {
    m1une::graph::GeneralWeightedMatching<int, long long> matching(4);
    matching.add_edge(0, 1, 8);
    matching.add_edge(1, 2, 10);
    matching.add_edge(2, 3, 7);
    matching.add_edge(3, 0, 9);

    std::cout << matching.max_weight_matching() << "\n";  // 17
    for (auto pair : matching.matching()) {
        std::cout << pair.from << " " << pair.to << "\n";
    }
}
```
