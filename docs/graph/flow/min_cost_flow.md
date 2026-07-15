---
title: Min Cost Flow
documentation_of: ../../../graph/flow/min_cost_flow.hpp
---

## Overview

`MinCostFlow<Cap, Cost>` sends flow from a source `s` to a sink `t` while
minimizing total cost. Each edge has a capacity and a cost per unit of flow.

`flow` uses an adaptive one-shot solver. Small flows and graphs whose terminal
capacity can be carried by only a few arcs use successive shortest augmenting
paths. When a non-negative-cost instance necessarily uses many terminal arcs,
`flow` instead solves an exact residual flow with network simplex. The simplex
path has a pivot threshold and falls back to a polynomial capacity-scaling
solver. If the terminal-capacity upper bound is infeasible because of an
internal bottleneck, a maximum-flow pass finds the exact sendable value first.
When that upper bound saturates both terminal cuts, those forced terminal arcs
are contracted directly into vertex balances before the exact solve.

`slope` always uses successive shortest augmenting paths because it must retain
every flow-cost breakpoint. Its shortest-path implementation uses potentials,
early sink termination, and a radix heap for fixed-width integer costs. A
binary heap is used for other cost types. Initial Bellman-Ford work is skipped
on the first call when all added costs are non-negative.

## Graph Orientation

Directed flow network. An edge added by `add_edge(from, to, cap, cost)` can
send flow only from `from` to `to`. For an undirected capacity, add both
directions with the desired costs.

The graph is stateful. Running `flow` or `slope` changes residual capacities and
stores the chosen flow. Use `get_edge` or `edges` afterward to inspect the
result.

## How to Use It

Create `MinCostFlow<Cap, Cost> mcf(n)`, add directed edges with capacity and
cost, and call `mcf.flow(s, t, flow_limit)`.

The returned pair is `{sent_flow, minimum_cost}`. If the requested
`flow_limit` cannot be fully sent, `sent_flow` will be smaller.

Use `slope(s, t, flow_limit)` when you need the minimum cost for every
breakpoint of the amount of flow. The returned vector starts with `{0, 0}` and
then adds one entry after each augmentation.

When the edge count is known, call `reserve_edges(m)` before adding edges. It
reserves edge metadata and adjacency capacity with average-degree headroom.
If every endpoint degree is known, `reserve_edges(m, degrees)` reserves exact
adjacency capacities. Each original edge contributes one to both endpoint
degrees, and a self-loop contributes two to its endpoint.

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Original edge source. |
| `to` | `int` | Original edge destination. |
| `cap` | `Cap` | Original capacity currently assigned to this edge. |
| `flow` | `Cap` | Flow currently sent through this edge. |
| `cost` | `Cost` | Cost per unit of flow on this edge. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `MinCostFlow()` | Creates an empty flow graph. | $O(1)$ |
| Constructor | `explicit MinCostFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of original edges. | $O(1)$ |
| `reserve_edges` | `void reserve_edges(int edge_count)` | Reserves edge metadata and average-degree adjacency headroom. | $O(N + M)$ when reallocation occurs |
| `reserve_edges` | `void reserve_edges(int edge_count, const std::vector<int>& degrees)` | Reserves edge metadata and exact residual adjacency capacities. | $O(N + M)$ when reallocation occurs |
| `add_edge` | `int add_edge(int from, int to, Cap cap, Cost cost)` | Adds a directed edge and returns its edge id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int i) const` | Returns the current state of original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges with current flow. | $O(M)$ |
| `flow` | `std::pair<Cap, Cost> flow(int s, int t)` | Sends as much flow as possible with the adaptive one-shot solver. | See below |
| `flow` | `std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit)` | Sends at most `flow_limit` flow with the adaptive one-shot solver. | See below |
| `slope` | `std::vector<std::pair<Cap, Cost>> slope(int s, int t)` | Returns flow-cost breakpoints using successive shortest paths. | See below |
| `slope` | `std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit)` | Returns flow-cost breakpoints up to `flow_limit`. | See below |

## Time Complexity

Let $F$ be the number of shortest-path augmentations, $U$ the maximum residual
capacity, and $W$ the number of bits in the integer distance key.

The successive-shortest-path path performs initial Bellman-Ford in $O(NM)$
when negative residual costs need it. Each binary-heap shortest path takes
$O(M\log N)$. For fixed-width integer `Cost`, the radix-heap bound is
$O((N+M)W)$ per augmentation instead. Thus `slope`, and `flow` when it selects
this path, take

$$
O(NM + FM\log N)
$$

with the binary heap, or $O(NM + F(N+M)W)$ with the radix heap. The $O(NM)$
term is skipped on a fresh graph whose original costs are all non-negative.

The network-simplex path is guarded by at most a constant number of simplex
attempts, a polynomial capacity-scaling fallback, and, when necessary, one
maximum-flow computation. Its conservative worst-case bound is

$$
O\left(
N^2M + (N+M)^2 + M\log U\,(M+N\log N)
\right).
$$

If the requested value or the terminal-capacity upper bound is feasible, the
$O(N^2M)$ maximum-flow term is skipped. The dispatch examines only the two
terminal adjacency lists: the simplex path is considered only for signed
integer capacities, signed costs, non-negative original costs, at least 64
edges, and a requested value that requires at least eight arcs at both
terminals. These are performance heuristics and do not affect correctness.

## Notes

Costs may be negative, but the residual graph must not contain a reachable
negative-cost cycle. If such a cycle exists, the minimum cost is not
well-defined. Adding any negative-cost edge keeps `flow` on the
successive-shortest-path path.

Calling `flow` or `slope` a second time continues from the current residual
state and sends additional flow.

## Example

```cpp
#include "graph/flow/min_cost_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::MinCostFlow<long long, long long> mcf(4);
    mcf.add_edge(0, 1, 2, 1);
    mcf.add_edge(0, 2, 1, 2);
    mcf.add_edge(1, 2, 1, 0);
    mcf.add_edge(1, 3, 1, 3);
    mcf.add_edge(2, 3, 2, 1);

    auto [flow, cost] = mcf.flow(0, 3, 2);
    std::cout << flow << " " << cost << "\n";  // 2 5
}
```
