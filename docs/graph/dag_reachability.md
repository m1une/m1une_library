---
title: DAG Reachability and Transitive Reduction
documentation_of: ../../graph/dag_reachability.hpp
---

## Overview

This header provides batched reachability queries and transitive reduction for
a directed acyclic graph. Both use dynamic bitsets propagated in reverse
topological order. A cyclic graph returns `std::nullopt`.

`dag_reachability` includes every zero-edge path, so `reachable(v, v)` is true.
The table is most appropriate when many reachability queries justify quadratic
memory.

`dag_transitive_reduction` removes every edge whose endpoints remain connected
by another directed path. It also reduces parallel edges to one representative.
The returned graph has the same reachability relation as the active input graph;
inactive edges are omitted. Costs do not affect reduction.

## Types

| Type | Member / method | Meaning | Complexity |
| --- | --- | --- | --- |
| `DagReachability` | `reachable_vertices` | Bitset of vertices reachable from each vertex. | Access to a bitset: $O(1)$ |
| `DagReachability` | `topological_order` | Topological order used to build the table. | Access: $O(1)$ |
| `DagReachability` | `int size() const` | Number of vertices. | $O(1)$ |
| `DagReachability` | `bool reachable(int from, int to) const` | Tests directed reachability, including `from == to`. | $O(1)$ |
| `DagTransitiveReductionResult<T>` | `graph` | Reduced graph. Its edge ids are newly assigned. | Access: $O(1)$ |
| `DagTransitiveReductionResult<T>` | `original_edge_ids` | Maps each new edge id to the retained input edge id. | Access: $O(1)$ |

## Functions

| Function | Signature | Complexity |
| --- | --- | --- |
| `dag_reachability` | `template <class T> std::optional<DagReachability> dag_reachability(const Graph<T>& g)` | $O((N + M)\lceil N / 64\rceil)$ time and $O(N\lceil N / 64\rceil)$ memory |
| `dag_transitive_reduction` | `template <class T> std::optional<DagTransitiveReductionResult<T>> dag_transitive_reduction(const Graph<T>& g)` | $O((N + M)\lceil N / 64\rceil + M\log M)$ time and $O(N\lceil N / 64\rceil + M)$ memory |

The sorting term is the sum of sorting outgoing edges at each vertex and is at
most $O(M\log M)$.

## Example

```cpp
#include "graph/dag_reachability.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(3);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(1, 2);
    g.add_directed_edge(0, 2);  // Redundant.

    auto reach = m1une::graph::dag_reachability(g);
    if (reach) std::cout << reach->reachable(0, 2) << '\n';

    auto reduction = m1une::graph::dag_transitive_reduction(g);
    if (reduction) std::cout << reduction->graph.edge_count() << '\n';  // 2
}
```
