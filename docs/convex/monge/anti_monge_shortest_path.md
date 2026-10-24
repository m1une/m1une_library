---
title: Anti-Monge DAG Shortest Paths
documentation_of: ../../../convex/monge/anti_monge_shortest_path.hpp
---

## Overview

Compute a single forward DP with a minimum edge length `D = minimum_step`:

$$
dist[0]=0,\qquad dist[j]=\min_{0\le i\le j-D}(dist[i]+cost(i,j)).
$$

For sequence partitioning, vertex `j` represents prefix `[0,j)`; use
`vertex_count = sequence_length + 1`. The cost must be **anti-Monge**.
For Monge costs, see [LARSCH](https://m1une.github.io/m1une_library/convex/monge/larsch.hpp). For transitions from a known
previous DP layer, see [divide-and-conquer optimization](https://m1une.github.io/m1une_library/convex/monge/divide_and_conquer_optimization.hpp).
The [Monge guide](https://m1une.github.io/m1une_library/convex/monge/all.hpp) explains how to identify the recurrence and choose
between matrix search, previous-layer transitions, and forward DP.

All names are in `m1une::convex`.

## Worked example: forward jumps with an anti-Monge cost

Use four ordered stations `x={0,2,5,9}` and start at station 0. A forward jump
has the signed cost `-(x[to]-x[from])^2 - 20`. Find the minimum total cost
to each station. Negative costs are permitted because every jump moves
forward; there are no cycles.

Write the ordinary quadratic DP first:

```cpp
std::vector<long long> dp(x.size(), infinity);
dp[0] = 0;
for (int to = 1; to < int(x.size()); ++to) {
    for (int from = 0; from < to; ++from) {
        dp[to] = std::min(dp[to], dp[from] + jump_cost(from, to));
    }
}
```

For these inputs it computes:

| Destination `to` | Total costs through earlier stations | Minimum | Parent |
| --- | --- | --- | --- |
| 0 | Starting station | 0 | -1 |
| 1 | Through 0: `0-24=-24` | -24 | 0 |
| 2 | Through 0: `0-45=-45`; through 1: `-24-29=-53` | -53 | 1 |
| 3 | Through 0: `0-101=-101`; through 1: `-24-69=-93`; through 2: `-53-36=-89` | -101 | 0 |

Negated squared gap is anti-Monge. Use the helper to compute the same DP:

```cpp
#include "convex/monge/anti_monge_shortest_path.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> x = {0, 2, 5, 9};
    auto jump_cost = [&](int from, int to) {
        long long gap = x[to] - x[from];
        return -gap * gap - 20;
    };
    constexpr long long infinity = 1LL << 60;
    auto result = m1une::convex::anti_monge_shortest_path(
        int(x.size()), jump_cost, infinity);
    assert(result.distance == std::vector<long long>({0, -24, -53, -101}));
    assert(result.parent == std::vector<int>({-1, 0, 1, 0}));
    for (int to = 0; to < int(x.size()); ++to) {
        std::cout << result.distance[to] << ' ' << result.parent[to] << '\n';
    }

    // To recover a path, first check that the destination is reachable.
    if (result.distance[3] != infinity) {
        std::vector<int> path;
        for (int v = 3; v != -1; v = result.parent[v]) path.push_back(v);
        std::reverse(path.begin(), path.end());
        assert(path == std::vector<int>({0, 3}));
    }

    // Optional fourth argument: allow only jumps advancing >=2 station indices.
    auto restricted = m1une::convex::anti_monge_shortest_path(
        int(x.size()), jump_cost, infinity, 2);
    assert(restricted.distance ==
           std::vector<long long>({0, infinity, -45, -101}));
    assert(restricted.parent[1] == -1);  // Station 1 is unreachable.
}
```

Output (minimum cost, previous station on an optimal path):

```text
0 -1
-24 0
-53 1
-101 0
```

Pass the number of vertices, an **edge-cost** callback, and an unreachable
sentinel. The callback receives source and destination **indices**, and
returns only their edge cost. The helper manages all source distances. Read
`.distance[to]` for the minimum and `.parent[to]` for a chosen predecessor.

For your own problem, replace `jump_cost` after proving it is anti-Monge on
valid rectangles. Adding source- or destination-dependent costs preserves
that inequality. The optional minimum step is measured in **indices**;
it is unrelated to coordinate distance. The default `1` permits every forward
edge. The helper's time is $O(V\log V+VD)$ and memory is $O(V)$, where `D`
is the minimum step. Exact graph and numeric restrictions follow below.

## Interface

| Signature | Meaning | Complexity |
| --- | --- | --- |
| `template <class T, class Cost> AntiMongeShortestPathResult<T> anti_monge_shortest_path(int vertex_count, Cost cost, T infinity, int minimum_step = 1)` | Compute distances from vertex `0` and optimal predecessors. | $O(V\log V + VD)$ time, $O(V)$ additional memory, for constant-time cost evaluations. |

`AntiMongeShortestPathResult<T>` contains:

| Member | Meaning |
| --- | --- |
| `std::vector<T> distance` | Distances; unreachable vertices have value `infinity`. |
| `std::vector<int> parent` | Largest predecessor attaining the minimum, or `-1` for the source and unreachable vertices. |

Inputs are not modified. An empty graph returns empty vectors; one vertex
returns distance `0` and parent `-1`. If `D >= V`, only vertex `0` is
reachable. Preconditions: `vertex_count >= 0`, `minimum_step >= 1`.

## Requirements

For `a < b`, `c < d`, and `b + D <= c`, require

$$
cost(a,c)+cost(b,d)\ge cost(a,d)+cost(b,c).
$$

Every fully valid rectangle of the source/destination matrix must be
anti-Monge. The implementation does not check this. All edges satisfying
`to - from >= D` exist and have finite costs. Other missing edges or a maximum
edge length are not supported.

`cost(from,to)` is called only for a reachable source and
`0 <= from < to < vertex_count`, `to - from >= D`. It must return a fixed
cost convertible to `T`; repeated evaluations in arbitrary order are allowed.
Negative costs are allowed because edges always go forward.

`T()` represents zero. `T` must support addition, equality, and ordering.
Choose `infinity > 0` strictly larger than every finite path value and
transition sum encountered. Those sums must fit in `T`. The helper never
adds to `infinity`: it removes unreachable sources before matrix search.
The sentinel does not permit infinite edge costs.

## Algorithm and complexity

For a block `[l,r)`, split at `m`: solve `[l,m)`, relax all valid cross edges,
then solve `[m,r)`. Incoming transitions must precede solving the right half.
The generic `algo::cdq_divide_and_conquer` uses a different callback order
and cannot replace this recursion directly.

For each valid cross rectangle, rows are destinations and columns are reachable
sources **in decreasing order**. Transposing preserves anti-Monge, reversing
columns makes it Monge, and adding finalized source distances as column
constants preserves Monge. SMAWK finds all row minima with linear work.
Its leftmost tie rule selects the largest original source index.

Let `p = max(l,m-D+1)` and `q = min(r,m+D-1)`. The cross edges partition into
two valid rectangles, `[l,m) -> [q,r)` and `[l,p) -> [m,q)`, and valid pairs
in the small corner `[p,m) -> [m,q)`. Scan the corner directly. No invalid
cells are padded with infinity.

Rectangle work totals $O(V\log V)$. Recursion stops at blocks of size at most
`D`; there are $O(V/D)$ larger blocks, each with at most $O(D^2)$ corner
pairs, giving $O(VD)$ corner work. For `D = 1` or `2`, the corner has no
valid edges and total time is $O(V\log V)$. For large `D`, the $VD$ term
matters: this interface does not guarantee $O(V\log V)$ independently of `D`.
