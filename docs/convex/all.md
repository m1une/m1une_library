---
title: Convex All
documentation_of: ../../convex/all.hpp
---

## Overview

`convex/all.hpp` includes convex data structures and convex optimization
helpers. The public namespace is `m1une::convex`.

## Included Headers

| Header | Contents |
| --- | --- |
| `convex/alien_trick.hpp` | Exact-count optimization through Lagrangian relaxation. |
| `convex/convex_hull_trick.hpp` | Monotone-slope CHT for minimum or maximum line queries. |
| `convex/li_chao_tree.hpp` | Dynamic Li Chao tree for arbitrary line and line-segment insertion. |
| `convex/monge/all.hpp` | SMAWK, monotone minima, online LARSCH, and ordered Monge/anti-Monge checks. |
| `convex/slope_trick.hpp` | Heap-based slope trick for convex piecewise-linear functions. |
| `convex/monge_transition.hpp` | Finalized-layer monotone, Monge, anti-Monge, and ordered transitions. |
| `convex/monge_shortest_path.hpp` | Same-array Monge and anti-Monge forward DAG recurrences with minimum step. |
| `convex/min_plus_convolution.hpp` | Structured sequence min-plus/max-plus convolution. |
