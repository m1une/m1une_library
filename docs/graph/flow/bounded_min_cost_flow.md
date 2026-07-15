---
title: Bounded Min Cost Flow
documentation_of: ../../../graph/flow/bounded_min_cost_flow.hpp
---

## Overview

`BoundedMinCostFlow<Cap, Cost, TotalCost = Cost, PivotLimitFactor = 8>` finds
a minimum-cost feasible flow with lower and upper bounds on each edge. It is
the costed version of `BoundedFlow<Cap>`. `BMinCostFlow` is an alias of the
same type.

For this library, vertex balance means:

```cpp
outgoing_flow(v) - incoming_flow(v) = balance[v]
```

Positive balance is supply. Negative balance is demand.

Each edge may have any interval `lower <= flow <= upper`. The lower bound may
be negative, so an edge can allow negative flow. For example, an edge
`u -> v` with bounds `[-3, 5]` may carry `-2`, which behaves like sending `2`
units from `v` to `u`. The cost is still `flow * cost`, so a negative flow can
contribute a negative or positive value depending on `cost`.

## Graph Orientation

Directed flow network. An edge added by
`add_edge(from, to, lower, upper, cost)` has the signed direction
`from -> to`.

## How It Works

The solver first uses the network simplex method with an artificial-root
initial basis. It repeatedly pivots a negative reduced-cost residual edge into
the spanning-tree basis and removes a saturated tree edge. A candidate-list
pivot rule reuses promising edges for several minor iterations before scanning
the residual edges again. This approach has very small constants and is
especially fast on the sparse and medium-sized flow networks common in
contests.

Network simplex alone has no polynomial pivot bound. Therefore, after
`PivotLimitFactor * (N + M + 1)` pivots, `min_cost_flow` discards the partial
basis and restarts from the original instance with a polynomial capacity-scaling
solver. The default factor is `8`. Because the pivot budget is linear in the
input graph size, the hybrid algorithm retains a polynomial worst-case bound.

`min_cost_flow_polynomial` skips network simplex and directly uses capacity
scaling. It is useful for inputs known to be adversarial to simplex. Setting
`PivotLimitFactor` to `0` also makes the hybrid fall back as soon as its first
pivot would be required.

On the simplex path, the artificial edges determine feasibility and the tree
potentials provide the returned dual certificate. On the capacity-scaling path,
the certificate is reconstructed from the final residual graph.

The returned `Result::cost` is the total cost on the original edges:

```cpp
sum(edge.flow * edge.cost)
```

If the balance constraints cannot be satisfied, the solver returns
`std::nullopt`.

`Cap` must be a signed integer type. `Cost` must support signed exact
arithmetic, ordering, and `std::numeric_limits<Cost>::max()`. `TotalCost` is
the accumulator type for the final
`sum(flow * cost)` and defaults to `Cost`. All capacities must fit `Cap`;
intermediate potential values and the artificial cost
`1 + sum(abs(edge.cost))`, as well as reduced-cost arithmetic, must fit `Cost`;
the total must fit `TotalCost`.

When only the total may overflow the unit-cost type, use a wider third template
argument. For example, `BoundedMinCostFlow<long long, long long, __int128_t>`
keeps the network-simplex hot path in 64-bit arithmetic and accumulates the
answer in 128 bits.

## How to Use It

Use `add_edge(from, to, lower, upper, cost)` to add bounded directed edges.

Use these balance helpers for `b`-flow:

* `add_supply(v, x)` adds `x` to `balance[v]`;
* `add_demand(v, x)` subtracts `x` from `balance[v]`;
* `set_balance(v, b)` sets the balance directly;
* `add_balance(v, b)` adds signed balance directly.

Then call `min_cost_flow()`. It returns `std::nullopt` if no feasible flow
exists.

Call `min_cost_flow_polynomial()` instead to bypass the simplex fast path.

For an exact `s-t` flow of value `F`, call `min_cost_st_flow(s, t, F)`. This
adds temporary balances `balance[s] += F` and `balance[t] -= F`, then minimizes
the total cost among feasible flows with that exact value. The direct
capacity-scaling version is `min_cost_st_flow_polynomial(s, t, F)`.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `edges` | `std::vector<ResultEdge>` | Original edges with selected minimum-cost flow. |
| `balance` | `std::vector<Cap>` | Vertex balances used for this solve. |
| `potential` | `std::vector<Cost>` | A dual potential certificate for the selected flow. |
| `cost` | `TotalCost` | Total cost `sum(flow * cost)` of the selected flow. |
| `get_edge` | `ResultEdge get_edge(int i) const` | Returns result edge `i`. |
| `flow` | `Cap flow(int i) const` | Returns selected flow on edge `i`. |

For every returned edge `e`, `potential` satisfies the residual reduced-cost
conditions:

* if `e.flow < e.upper`, then
  `e.cost + potential[e.from] - potential[e.to] >= 0`;
* if `e.lower < e.flow`, then
  `e.cost + potential[e.from] - potential[e.to] <= 0`.

Together with feasibility, these inequalities certify that the returned flow
has minimum cost.

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Edge source. |
| `to` | `int` | Edge destination. |
| `lower` | `Cap` | Lower bound on flow. |
| `upper` | `Cap` | Upper bound on flow. |
| `flow` | `Cap` | Present only in `ResultEdge`; selected minimum-cost flow. |
| `cost` | `Cost` | Cost per unit of flow. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `BoundedMinCostFlow()` | Creates an empty bounded min-cost-flow graph. | $O(1)$ |
| Constructor | `explicit BoundedMinCostFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of edges. | $O(1)$ |
| `reserve_edges` | `void reserve_edges(int edge_count)` | Reserves storage when the number of edges is known in advance. | $O(M)$ when reallocation occurs |
| `add_edge` | `int add_edge(int from, int to, Cap lower, Cap upper, Cost cost)` | Adds an edge with bounds and cost, then returns its id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int i) const` | Returns original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges. | $O(M)$ |
| `set_balance` | `void set_balance(int v, Cap b)` | Sets `balance[v] = b`. | $O(1)$ |
| `add_balance` | `void add_balance(int v, Cap b)` | Adds signed balance to vertex `v`. | $O(1)$ |
| `add_supply` | `void add_supply(int v, Cap supply)` | Adds non-negative supply to vertex `v`. | $O(1)$ |
| `add_demand` | `void add_demand(int v, Cap demand)` | Adds non-negative demand to vertex `v`. | $O(1)$ |
| `balance` | `Cap balance(int v) const` | Returns `balance[v]`. | $O(1)$ |
| `balances` | `const std::vector<Cap>& balances() const` | Returns all balances. | $O(1)$ |
| `min_cost_flow` | `std::optional<Result> min_cost_flow() const` | Solves stored balances with simplex and polynomial fallback. | $O((N + M)^2 + M \log U (M + N \log N))$ worst case |
| `min_cost_flow` | `std::optional<Result> min_cost_flow(const std::vector<Cap>& balance) const` | Solves explicit balances with simplex and polynomial fallback. | $O((N + M)^2 + M \log U (M + N \log N))$ worst case |
| `min_cost_flow_polynomial` | `std::optional<Result> min_cost_flow_polynomial() const` | Solves stored balances directly with capacity scaling. | $O(M \log U (M + N \log N) + NM)$ |
| `min_cost_flow_polynomial` | `std::optional<Result> min_cost_flow_polynomial(const std::vector<Cap>& balance) const` | Solves explicit balances directly with capacity scaling. | $O(M \log U (M + N \log N) + NM)$ |
| `min_cost_st_flow` | `std::optional<Result> min_cost_st_flow(int s, int t, Cap flow_value) const` | Solves exact `s-t` flow with value `flow_value`. | $O((N + M)^2 + M \log U (M + N \log N))$ worst case |
| `min_cost_st_flow_polynomial` | `std::optional<Result> min_cost_st_flow_polynomial(int s, int t, Cap flow_value) const` | Solves exact `s-t` flow directly with capacity scaling. | $O(M \log U (M + N \log N) + NM)$ |

Here, `P <= PivotLimitFactor * (N + M + 1)` is the number of network-simplex
pivots completed before termination or fallback. `U` is the maximum absolute
capacity or balance, with a minimum value of two. Without fallback, the actual
time is $O(N + M + P(N + M))$. Thus the default hybrid keeps the simplex fast
path while having the polynomial worst-case bounds shown above.

Average-case complexity depends on the input distribution. Let $\bar P$ be the
expected number of simplex pivots and let $q$ be the probability that the pivot
limit is reached. The expected time is

$$
O\left(
N + M + \bar P(N + M)
+ q\left(M \log U (M + N \log N) + NM\right)
\right).
$$

For typical contest inputs the fallback is rare, so the practical average is
$O(N + M + \bar P(N + M))$.

As empirical intuition, with the current candidate-list rule on the 54 official
Library Checker `min_cost_b_flow` cases, the pivot count had median `16.5`, mean
`627`, and maximum `2104`. On the ten 1000-edge `large_random` cases the mean
was `1924` pivots, while the ten 1000-edge `goto` cases averaged `968`. Thus a
useful practical estimate on the larger cases is $\bar P \approx M$ to $2M$,
giving the coarse average bound $O(M(N + M))$. For comparison, the default
budget is `8808` pivots when `N = 100` and `M = 1000`.

The observed running time is usually better than that coarse bound suggests:
candidate lists avoid a full edge scan before every pivot, and a pivot normally
touches only a short tree path and a small rerooted subtree. The theoretical
$O(N + M)$ work per pivot is therefore rarely fully realized. These figures are
measurements, not a distribution-independent guarantee on $\bar P$.

## Alias

| Alias | Type |
| --- | --- |
| `BMinCostFlow<Cap, Cost, TotalCost, PivotLimitFactor>` | `BoundedMinCostFlow<Cap, Cost, TotalCost, PivotLimitFactor>` |

## Example

```cpp
#include "graph/flow/bounded_min_cost_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::BoundedMinCostFlow<long long, long long> mcf(3);
    int e0 = mcf.add_edge(0, 1, 1, 3, 2);
    int e1 = mcf.add_edge(1, 2, 1, 3, 1);
    int e2 = mcf.add_edge(0, 2, 0, 3, 10);

    auto res = mcf.min_cost_st_flow(0, 2, 3);
    if (!res) return 0;

    std::cout << res->cost << "\n";     // 9
    std::cout << res->flow(e0) << "\n"; // 3
    std::cout << res->flow(e1) << "\n"; // 3
    std::cout << res->flow(e2) << "\n"; // 0
}
```
