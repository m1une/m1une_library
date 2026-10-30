---
title: Monge and Anti-Monge Forward DAG Shortest Paths
documentation_of: ../../convex/monge_shortest_path.hpp
---

Compute a **same-array recurrence**, starting at vertex `0`:

$$
dp[0]=0,\qquad dp[j]=\min_{0\le i\le j-D}(dp[i]+cost(i,j)),
\qquad D=minimum\_step\ge1.
$$

Vertices are natural indices in `[0,vertex_count)`; **every** edge with
`to-from >= D` exists and has finite cost. Negative costs are allowed in this
forward DAG. `cost(from,to)` returns only the edge cost. Distances are finalized
by the solver, unlike an [offline layer transition](https://m1une.github.io/m1une_library/convex/monge_transition.hpp).
For prefix partitioning, use `vertex_count = sequence_length+1`.

## Interface

Both functions use `m1une::convex` and return the same result type.

| Signature | Time | Memory |
| --- | --- | --- |
| `template<class T, class Cost> MongeShortestPathResult<T> monge_shortest_path(int vertex_count, Cost cost, T infinity, int minimum_step = 1)` | $O(N)$ for every $D$ | $O(N)$ |
| `template<class T, class Cost> MongeShortestPathResult<T> anti_monge_shortest_path(int vertex_count, Cost cost, T infinity, int minimum_step = 1)` | $O(N\log(N+1)+ND)$ | $O(N)$ |

For anti-Monge, $D=1$ or $D=2$ gives $O(N\log(N+1))$. If $D\ge N$,
both routines return after $O(N)$ initialization. Counts and minimum steps
are asserted nonnegative and positive respectively. Arithmetic and cost
evaluation are assumed constant time. Inputs are not modified.

`MongeShortestPathResult<T>` contains `std::vector<T> distance` and
`std::vector<int> parent`. `distance[0]=T()` and `parent[0]=-1`.
Unreachable vertices have `distance=infinity` and `parent=-1`. Among optimal
parents, Monge chooses the **smallest** source ID; anti-Monge chooses the
**largest**. Empty graphs return empty vectors. Vertices `1..D-1` are
unreachable; every vertex `>=D` in the graph is reachable directly from `0`.

`T()` must represent zero. `T` supports addition and comparisons, and cost
values are convertible to `T`. Choose `infinity > T()` strictly larger than
every finite path value and transition sum encountered. All such sums must
fit in `T`. Neither algorithm adds infinity or calls the cost for an
unreachable source or invalid edge. Other missing edges, infinite edge costs,
and maximum-step restrictions are unsupported.

## Monge assumptions

For `a<b`, `c<d`, and `b+D<=c`, require

$$
cost(a,c)+cost(b,d)\le cost(a,d)+cost(b,c).
$$

For anti-Monge reverse the inequality. These conditions apply to **all fully
valid rectangles**, not just adjacent entries of a triangularly masked table.
The cost is fixed across calls; evaluations can occur in arbitrary order on
legal pairs. Properties are not checked. Adding source or target fees preserves
either inequality.

## Why Monge supports arbitrary minimum steps in linear time

Use [LARSCH](https://m1une.github.io/m1une_library/convex/monge/larsch.hpp) with
`N-D` rows. Row `r` targets vertex `r+D`. Its legal reachable sources are `0`
and `D..r`. Map virtual column `c` to `0` when `c<D`, otherwise to `c`.
The columns are now a **nondecreasing** list with duplicates of `0` replacing
permanently unreachable vertices. The lower triangle `c<=r` represents exactly
the needed candidates, including harmless duplicates. Every queried edge is
legal. Duplicating an ordered source preserves Monge; adding its finalized
distance as a column constant preserves Monge too.

Before answering row `r`, LARSCH accesses only virtual columns `<=r`, though it
may query future rows. Their sources are at most `r`, whose distances are already
finalized since the destination is `r+D`. Leftmost virtual ties map to the
smallest original parent. The construction and all row searches take $O(N)$
time and memory, independently of `D`; no numeric padding is used.

The early return for `D>=N` precedes construction of LARSCH or evaluation of
`r+D`. Otherwise `0<=r<N-D`, hence `r+D<=N-1`; the addition fits in `int`.
This also covers `minimum_step=INT_MAX`, which always takes the early return
for an `int` vertex count. In every case, existing vertices in `[1,min(D,N))`
retain `distance=infinity` and `parent=-1`, and their costs are never queried.

## Anti-Monge CDQ and boundary handling

For `[l,r)`, split at `m`, **solve the left half**, relax all legal left-to-right
edges, then **solve the right half**. All source distances in a cross rectangle
are finalized. Put targets in increasing row order and reachable sources in
**decreasing column order**. This transforms the anti-Monge rectangle to Monge;
SMAWK with source-distance constants computes its minima. Leftmost in this
virtual order is the largest original parent. Transposition alone would not
change anti-Monge to Monge.

Let `p=max(l,m-D+1)` and `q=min(r,m+D-1)`. Partition cross edges into complete
rectangles `[l,m) -> [q,r)` and `[l,p) -> [m,q)`, and scan legal pairs in the
small corner `[p,m) -> [m,q)` directly. Stop recursion at blocks of size `<=D`.
Rectangle work totals $O(N\log(N+1))$. There are $O(N/D)$ larger blocks and
$O(D^2)$ corner pairs per block, hence $O(ND)$ boundary work. For `D=1,2`,
the corner contains no legal pairs. Arbitrary reordering is safe **inside a
complete rectangle**, where every source-target pair exists; it cannot be
applied blindly to the online triangle.

## Example and parent reconstruction

```cpp
#include "convex/monge_shortest_path.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

int main() {
    std::vector<long long> x = {0, 2, 5, 9};
    constexpr long long inf = 1LL << 60;
    auto result = m1une::convex::monge_shortest_path(4, [&](int i, int j) {
        long long gap = x[j]-x[i];
        return gap*gap+3;
    }, inf);
    assert(result.distance == std::vector<long long>({0, 7, 19, 38}));
    std::vector<int> path;
    if (result.distance[3] != inf) {
        for (int v = 3; v != -1; v = result.parent[v]) path.push_back(v);
        std::reverse(path.begin(), path.end());
    }
    assert(path == std::vector<int>({0, 1, 2, 3}));

    auto anti = m1une::convex::anti_monge_shortest_path(4, [&](int i, int j) {
        long long gap = x[j]-x[i];
        return -gap*gap-20;
    }, inf, 2);
    assert(anti.distance == std::vector<long long>({0, inf, -45, -101}));
    assert(anti.parent == std::vector<int>({-1, -1, 0, 0}));
}
```

Known permutations belong to the offline matrix/transition APIs. These graph
solvers intentionally retain the natural topological order and index-step
constraint. A permutation that makes the cost matrix Monge does not by itself
preserve online source availability (`i<j`), or the edge-legality constraint
`j-i>=D`. A reordered column can require a distance that is still unfinished,
or describe a forbidden edge. General source availability after arbitrary
permutations is a different problem, and is not silently inferred from matrix
ordering.
