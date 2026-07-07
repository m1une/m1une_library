---
title: Max Flow
documentation_of: ../../../graph/flow/max_flow.hpp
---

## Overview

`MaxFlow<Cap>` computes the maximum amount of flow that can be sent from a
source vertex `s` to a sink vertex `t` in a directed capacitated graph.

This implementation uses Dinic's algorithm. It repeatedly builds a level graph
with BFS and sends blocking flow with DFS. It is the standard choice for many
competitive programming max-flow tasks, including bipartite matching,
edge-disjoint paths, and minimum `s-t` cut problems.

## Graph Orientation

Directed flow network. An edge added by `add_edge(from, to, cap)` can send flow
only from `from` to `to`. For an undirected capacity, add both directions.

The graph is stateful. Running `max_flow` changes residual capacities and
stores the resulting flow. Use `get_edge` or `edges` after running it to inspect
how much flow passed through each original edge.

## How to Use It

Create `MaxFlow<Cap> mf(n)`, add directed edges with capacities, and call
`mf.max_flow(s, t)`.

Capacities must be non-negative. If you want an undirected capacity between
`u` and `v`, add two directed edges.

You can call `max_flow(s, t, flow_limit)` when only up to `flow_limit` units are
needed.

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Original edge source. |
| `to` | `int` | Original edge destination. |
| `cap` | `Cap` | Original capacity currently assigned to this edge. |
| `flow` | `Cap` | Flow currently sent through this edge. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `MaxFlow()` | Creates an empty flow graph. | $O(1)$ |
| Constructor | `explicit MaxFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of original edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cap cap)` | Adds a directed edge and returns its edge id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int i) const` | Returns the current state of original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges with current flow. | $O(M)$ |
| `change_edge` | `void change_edge(int i, Cap new_cap, Cap new_flow)` | Replaces edge `i`'s capacity and current flow. | $O(1)$ |
| `max_flow` | `Cap max_flow(int s, int t)` | Sends maximum flow from `s` to `t`. | $O(N^2 M)$ in general; see below |
| `max_flow` | `Cap max_flow(int s, int t, Cap flow_limit)` | Sends at most `flow_limit` additional flow. | $O(N^2 M)$ in general; see below |
| `min_cut` | `std::vector<bool> min_cut(int s) const` | Returns vertices reachable from `s` in the residual graph. | $O(N + M)$ |

## Time Complexity of `max_flow`

Here, $N$ is the number of vertices and $M$ is the number of original edges.
The residual graph stores two directed residual edges for each original edge,
which changes only constant factors.

Dinic's algorithm works in phases. Each phase first uses BFS to construct a
level graph in $O(N + M)$ time, then uses DFS with current-edge pointers to
find a blocking flow. A blocking-flow computation takes $O(NM)$ time in the
general case. After a blocking flow is found, the shortest residual distance
from `s` to `t` strictly increases, so there are fewer than $N$ phases. This
gives the general bound

$$
O(N^2 M).
$$

This bound counts each `Cap` arithmetic or comparison operation as $O(1)$ and
does not depend on the numerical size of the capacities.

### Bounds for Integer Capacities

When every capacity is an integer, several additional bounds hold for this
current-edge implementation. Let $u_e$ be the capacity of edge $e$, and define

$$
\bar{u} = \frac{1}{M}\sum_e u_e,
\qquad
U = \max_e u_e,
$$

and

$$
\bar{c} = \frac{1}{N}\sum_v
\min\left(\sum_{e\text{ enters }v}u_e,
          \sum_{e\text{ leaves }v}u_e\right).
$$

If $F$ is the amount of flow still sendable from `s` to `t` in the current
residual graph, the following are alternative upper bounds:

| Condition | Complexity |
| --- | --- |
| Integer capacities | $O(FM)$ |
| Average edge capacity $\bar{u}$ | $O(\bar{u}M^{3/2})$ |
| Maximum edge capacity $U$, with no parallel edges | $O(UN^{2/3}M)$ |
| Average vertex throughput $\bar{c}$ as defined above | $O(\bar{c}\sqrt{N}M)$ |

These bounds hold at the same time as the general $O(N^2M)$ bound, so use the
smallest applicable one. As usual, zero-capacity edges and isolated vertices
can be omitted when applying the specialized bounds; if they are retained,
include the $O(N+M)$ initialization and scanning cost.

The $O(FM)$ bound follows because each successful augmentation increases an
integer flow by at least one. The other bounds combine this observation with a
small residual cut after sufficiently many level-graph phases.

If every residual capacity at the start of a call has greatest common divisor
$g$, divide the capacity-dependent quantities $F$, $\bar{u}$, $U$, and
$\bar{c}$ by $g$ in these bounds. When using `flow_limit`, it must be scaled as
well. Scaling all these values by $g$ does not change which paths and edges
Dinic's algorithm processes.

For unit-capacity graphs, $\bar{u}=U=1$. Combining the two edge-capacity bounds
gives the standard result

$$
O\left(M \min\left(N^{2/3}, \sqrt{M}\right)\right).
$$

On unit networks, where every non-terminal vertex has either one incoming edge
or one outgoing edge, $\bar{c}=O(1)$ and the bound improves further to
$O(M\sqrt{N})$. Bipartite matching networks are a common example.

For a detailed derivation of these bounds, see
[Dinic's Algorithm and Its Time Complexity](https://misawa.github.io/others/flow/dinic_time_complexity.html).

The `flow_limit` overload may stop before a complete maximum flow is found, so
it can be faster in practice, but its general worst-case bound remains
$O(N^2 M)$. With integer capacities, let $F_{call}$ be the amount returned by
the call. Its flow-dependent work is $O(F_{call}M)$, and the exact bound
including initialization and a final unsuccessful search is
$O(N+(F_{call}+1)M)$. Here, $F_{call}$ is at most `flow_limit`. Every call
returns only the **additional** flow sent during that call. Since the residual
graph is preserved, calling `max_flow` again continues from the current flow
rather than recomputing it from scratch.

## Minimum Cut

After running max flow, `min_cut(s)` returns the source side of a minimum
`s-t` cut. An original edge crossing from `cut[u] == true` to
`cut[v] == false` is saturated and belongs to some minimum cut boundary.

## Example

```cpp
#include "graph/flow/max_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::MaxFlow<long long> mf(4);
    mf.add_edge(0, 1, 2);
    mf.add_edge(0, 2, 1);
    mf.add_edge(1, 2, 1);
    mf.add_edge(1, 3, 1);
    mf.add_edge(2, 3, 2);

    std::cout << mf.max_flow(0, 3) << "\n";  // 3

    for (const auto& e : mf.edges()) {
        std::cout << e.from << " -> " << e.to << ": " << e.flow << "/" << e.cap << "\n";
    }
}
```
