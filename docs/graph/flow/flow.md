---
title: Flow
documentation_of: ../../../graph/flow/flow.hpp
---

## Overview

`graph/flow/flow.hpp` includes flow-network algorithms. Flow networks are
directed: an edge `u -> v` only sends flow from `u` to `v`.

For an undirected capacity between `u` and `v`, `MaxFlow` provides
`add_undirected_edge(u, v, cap)`, which stores one shared-capacity residual
pair. Other directed-flow classes represent it with two directed edges.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/flow/bounded_flow.hpp` | Directed flow network | Feasible flow with lower/upper bounds, balances, and negative flow intervals. |
| `graph/flow/bounded_min_cost_flow.hpp` | Directed flow network | Minimum-cost feasible flow with lower/upper bounds, balances, and negative flow intervals. |
| `graph/flow/gomory_hu.hpp` | Undirected capacitated graph | Gomory-Hu cut tree and pairwise minimum-cut queries. |
| `graph/flow/max_flow.hpp` | Directed or shared-capacity undirected network | Optimized Dinic maximum flow and minimum cut. |
| `graph/flow/min_cost_flow.hpp` | Directed flow network | Minimum-cost flow with potentials. |

## Complexity

This header is an include bundle and provides no runtime operation by itself.
See the included algorithm pages for public interfaces and complexities.
