---
title: Count Four Cycles
documentation_of: ../../graph/count_four_cycles.hpp
---

## Overview

This header counts subgraphs isomorphic to the four-edge cycle $C_4$. It can
return either the total number of four-cycles or, for every graph edge id, the
number of four-cycles containing that particular edge.

The implementation compresses parallel edges into multiplicities, orders
vertices by degree, and counts pairs of oriented length-two paths. This avoids
enumerating vertex quadruples.

## Graph Behavior

Every active edge is interpreted as undirected, including an edge inserted with
`add_directed_edge`. Inactive edges are ignored and receive a per-edge count of
zero. Parallel edges are supported and remain distinct choices: replacing one
side of a four-cycle by `k` parallel edges creates `k` different four-edge
subgraphs. Self-loops are not supported.

The per-edge result has `graph.edge_count()` entries indexed by original edge
id. Each count refers to one particular edge copy, not its whole parallel-edge
group.

## Functions

| Function | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| `count_four_cycles_per_edge` | `template <class T> std::vector<long long> count_four_cycles_per_edge(const Graph<T>& graph)` | Returns the number of four-cycles containing every edge id. | $O(N + M\sqrt M)$ time and $O(N + M)$ memory |
| `count_four_cycles` | `template <class T> long long count_four_cycles(const Graph<T>& graph)` | Returns the total number of four-cycles. | $O(N + M\sqrt M)$ time and $O(N + M)$ memory |

`M` denotes the number of active edges, including parallel copies. Counts must
fit in `long long`.

## Example

```cpp
#include "graph/count_four_cycles.hpp"
#include "graph/graph.hpp"

#include <cassert>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 0);
    graph.add_edge(0, 2);

    assert(m1une::graph::count_four_cycles(graph) == 1);
    auto per_edge = m1une::graph::count_four_cycles_per_edge(graph);
    assert(per_edge[4] == 0);  // The diagonal is not in the four-cycle.
}
```
