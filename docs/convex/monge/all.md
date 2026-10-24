---
title: Monge Optimization Guide
documentation_of: ../../../convex/monge/all.hpp
---

## What these algorithms solve

Monge optimization avoids checking every candidate for every state when the
cost matrix has an ordered structure. You provide a callback for a matrix
entry or edge cost; the library evaluates only selected entries. You do not
need to construct the full matrix.

All APIs use `m1une::convex`, zero-based indices, and half-open intervals.
Start with the recurrence and its dependency order, then prove the required
matrix property. The word "Monge" alone does not determine which API to use.

## Start here: what does a library call replace?

Suppose each row is a request and each column is one possible choice. You
want the cheapest choice for each request:

| Request | Choice 0 | Choice 1 | Choice 2 | Choice 3 |
| --- | --- | --- | --- | --- |
| 0 | 5 | 9 | 21 | 41 |
| 1 | 6 | 2 | 6 | 18 |
| 2 | 23 | 11 | 7 | 11 |

Normally, you scan all four choices for each of the three requests. SMAWK
performs that search with fewer cost evaluations when its matrix condition
holds. Here is the complete input-to-answer workflow:

```cpp
#include "convex/monge/smawk.hpp"
#include <cassert>
#include <vector>

int main() {
    std::vector<std::vector<long long>> cost = {
        {5, 9, 21, 41},
        {6, 2, 6, 18},
        {23, 11, 7, 11}
    };
    // Explicit-table overload: returns the best column index for each row.
    auto best = m1une::convex::smawk_row_argmin(cost);
    assert(best == std::vector<int>({0, 1, 2}));
    long long minimum_for_request_1 = cost[1][best[1]];
    assert(minimum_for_request_1 == 2);

    // Callback overload: same table, supplied one entry at a time.
    auto same = m1une::convex::smawk_row_argmin(3, 4,
        [&](int request, int choice) { return cost[request][choice]; });
    assert(same == best);
}
```

The callback is just a way to look up **one candidate's cost**. It does not
search for the best choice. The library performs that search and returns an
index; you use the index to read the minimum value. To avoid storing a large
table, replace the lookup with your formula or range query.

This example is Monge: its entries equal `base[row] + 4*(row-column)^2`,
with `base={5,2,7}`. Your own cost needs the documented ordering property
before you use this optimization. The [SMAWK worked example](smawk.md)
shows the original nested loop, exact output, and argument meanings.

For other recurrences, start with the corresponding worked example:

| What your straightforward code does | Worked example |
| --- | --- |
| Scans all choices independently for each answer | [SMAWK](smawk.md) or [monotone minima](monotone_minima.md). |
| Builds a new cost array from a known previous array | [One more move from known costs](divide_and_conquer_optimization.md). |
| Computes later DP values from earlier values in the same array | [Forward jumps with Monge costs](larsch.md) or [anti-Monge costs](anti_monge_shortest_path.md). |
| Tries every split of an interval | [Merging adjacent piles](knuth_optimization.md). |
| Tries every pair of quantities whose sum is a requested total | [Two-supplier convolution](min_plus_convolution.md). |

Each page starts with a small task and its straightforward implementation,
then a complete library-based program, expected answers, and the condition
that permits the optimization. The reference tables below help adapt those
examples once the basic call is clear.

## Choose by recurrence and dependencies

| Task | API | Required structure | Work, for constant-time callbacks |
| --- | --- | --- | --- |
| `answer[r] = min_c M(r,c)`, all entries fixed | [smawk_row_argmin](smawk.md) | Total monotonicity for leftmost minima; Monge suffices. | $O(H+W)$ |
| Same, but only the full matrix's argmins are known to be nondecreasing | [monotone_row_argmin](monotone_minima.md) | Nondecreasing leftmost argmins. | $O((H+W)\log(H+1))$ |
| `next[j] = min_i(previous[i] + cost(i,j))` | [divide_and_conquer_transition](divide_and_conquer_optimization.md) | Previous layer fixed; nondecreasing minimizing candidates. | $O((H+W)\log(H+1))$ per layer |
| `dp[j] = min_{i<j}(dp[i] + cost(i,j))`, Monge costs | [larsch_shortest_path](larsch.md) | Triangular total monotonicity for minima. | $O(V)$ |
| Same forward DP, anti-Monge costs, optionally `j-i >= D` | [anti_monge_shortest_path](anti_monge_shortest_path.md) | Anti-Monge on valid rectangles. | $O(V\log V+VD)$; $O(V\log V)$ for fixed `D`. |
| `dp[l][r] = cost(l,r) + min_k(dp[l][k]+dp[k][r])` | [knuth_optimization](knuth_optimization.md) | Knuth's split monotonicity. | $O(N^2)$ |
| `answer[k] = min_{i+j=k}(a[i]+b[j])`, or the maximum analogue | [structured convolution](min_plus_convolution.md) | Convex or concave input sequences as documented. | $O(N+M)$ |

`divide_and_conquer_dp` is a value-and-choice wrapper around monotone minima;
it does not imply that the recurrence has a segment-count dimension.
If a fixed transition matrix is Monge, you can also use SMAWK directly to
compute one previous-layer transition in $O(H+W)$ work.

For maxima, the matrix-search APIs have `row_argmax` variants and strict
comparator overloads. The shortest-path helpers minimize; their documented
cost direction still applies.

## Map the recurrence to rows and columns

For a minimization over candidates, use **one row per answer/state** and
**one column per candidate**. For a previous-layer recurrence, the matrix is

$$
M(j,i)=previous[i]+cost(i,j).
$$

The callback and return values depend on the interface:

| API | Callback receives | Callback returns | Result |
| --- | --- | --- | --- |
| `smawk_row_argmin(H,W,value)` | `(state, candidate)` | Entire matrix entry, including `previous[candidate]` if needed. | Column index for each state. |
| `divide_and_conquer_dp(H,W,value)` | `(state, candidate)` | Entire matrix entry. | `.value[state]` and `.argmin[state]`. |
| `divide_and_conquer_transition(previous,H,cost)` | `(candidate, state)` | Edge/transition cost only; the helper adds the previous value. | `.value[state]` and `.argmin[state]`. |
| `larsch_shortest_path(V,cost)` | `(from, to)` | Edge cost only; the helper adds the source distance. | `.distance[to]` and `.parent[to]`. |
| `anti_monge_shortest_path(V,cost,INF,D)` | `(from, to)` | Edge cost only. | `.distance[to]` and `.parent[to]`. |

The dimensions are counts, not largest indices. `H` states use indices
`0..H-1`; a sequence-prefix DP over lengths `0..N` needs `N+1` vertices.
Matrix-search results are column positions in the order you supplied. If
columns index a filtered or reordered candidate list, map positions through
that list before using them as original indices.

## Establish the inequality and its direction

For row indices `a < b` and column indices `c < d`, Monge means

$$
M(a,c)+M(b,d)\le M(a,d)+M(b,c).
$$

Anti-Monge reverses the inequality. Some sources use different naming
conventions; compare their inequality with this one.

A useful general model is squared distance between sorted coordinates:
`M(r,c) = (x[r]-y[c])^2`. Its quadrangle difference is
`-2*(x[b]-x[a])*(y[d]-y[c]) <= 0`, so it is Monge. Negated squared distance
is anti-Monge. More generally, convex functions of coordinate differences
give Monge costs, while concave functions give anti-Monge costs.

These transformations are useful when adapting a recurrence:

| Transformation | Effect |
| --- | --- |
| Add an arbitrary constant to each row or column | Preserves Monge / anti-Monge, since constants cancel in the inequality. |
| Keep a subset of rows or columns in their original order | Preserves the property. |
| Transpose | Preserves the inequality's direction. |
| Reverse columns, or reverse rows | Exchanges Monge and anti-Monge. |
| Negate entries | Exchanges Monge and anti-Monge, and exchanges minima with maxima. |

In particular, adding known `previous[i]` values as column constants preserves
Monge. This does **not** hold for arbitrary column constants if all you know
is total monotonicity; check the resulting transition matrix in that case.

Both search algorithms expect optimal column indices to be nondecreasing in
the supplied row order. For Monge matrices this holds for minima; for
anti-Monge matrices it holds for maxima. Use this orientation table:

| Matrix | Row minima | Row maxima |
| --- | --- | --- |
| Monge | Original column order. | Reverse columns first. |
| Anti-Monge | Reverse columns first. | Original column order. |

Reversing columns preserves the values being optimized. Map the result back:

```cpp
auto argmin = m1une::convex::smawk_row_argmin(H, W,
    [&](int row, int column) { return value(row, W - 1 - column); });
for (int row = 0; row < H; ++row) {
    if (argmin[row] != -1) argmin[row] = W - 1 - argmin[row];
}
```

Matrix-search APIs break ties toward the leftmost supplied column. Reversal
therefore chooses the rightmost original optimum. For `W=0`, every answer is
`-1`; for `H=0`, the result is empty. Never index a candidate array with `-1`.

## Applying the examples to your own recurrence

First write the candidate-search loop without optimization. Identify which
array entries are already known, what one candidate's transition value is,
and whether the output is a value or an index. Then match that loop to the
callback table above.

For a previous-layer recurrence, follow the
[known-costs example](divide_and_conquer_optimization.md): provide the previous
array and a transition-cost callback, then read `.value` and `.argmin`.
For multiple layers, finish each layer before replacing `previous`. Layer
count multiplies the work; the library does not decide whether your problem
needs an exact number of transitions or an unrestricted optimal path.

## Forward DP requires a different evaluation order

In `dp[j] = min_{i<j}(dp[i]+cost(i,j))`, predecessor values belong to the same
array you are computing. Fixed-matrix search may query rows out of order;
a callback reading unfinished `dp[i]` values does not define a fixed matrix.

Use `larsch_shortest_path` for the documented Monge case, or
`anti_monge_shortest_path` for the anti-Monge case. Both accept **edge costs**;
they manage source distances and dependency order internally. Their pages
contain standalone examples and exact graph restrictions.

For a custom divide-and-conquer forward DP, the dependency order is:

1. Solve the left block so its source distances are final.
2. Relax all valid transitions from the left block to the right block.
3. Solve the right block with those incoming distances.

At the cross step, distances on the left are fixed column constants, so
matrix search is valid on a fully defined rectangle of cross transitions.
Each edge is handled at the unique recursive split that separates its
endpoints. A generic recursion that solves both halves before invoking the
cross callback does not provide this dependency order.

## Invalid candidates, infinity, and checking your model

The public matrix-search routines search **full rectangles**. A restriction
such as `i < j`, a minimum interval length, or a maximum interval length is a
separate condition; Monge on valid cells alone does not justify searching a
padded rectangle.

For example, after reversing a triangular candidate set, a zero-cost matrix
may become:

| | Column 0 | Column 1 |
| --- | --- | --- |
| Row 0 | INF | 0 |
| Row 1 | 0 | 0 |

The leftmost minima are `1,0`, violating the required monotonicity. This can
happen even when the original finite cost is both Monge and anti-Monge.

For state-independent exclusions, filter out invalid candidates and retain
the index mapping. For state-dependent exclusions, use a helper that explicitly
supports the restriction, split transitions into valid rectangles, or prove
that your particular padding preserves the algorithm's precondition.
`anti_monge_shortest_path` supports a minimum index step `D`; it does not
support arbitrary forbidden edges or a maximum step.

For a previous-layer matrix, avoid adding edge costs to an unreachable-value
sentinel. Remove unreachable candidate columns before searching. Choose a
numeric type and sentinel that can represent all finite transition sums;
see each helper's numeric contract.

During development, compare optimized answers with exhaustive candidate
search on small instances, including ties and empty candidate sets.
`is_monge` and `is_anti_monge` check a finite rectangle in $O(HW)$ time;
they are useful diagnostics, but checking a few instances is not a proof for
all inputs. Test the **actual callback matrix**, including previous-layer
costs and any reordering or validity mask.

## Included Headers

| Header | Contents |
| --- | --- |
| `convex/monge/smawk.hpp` | Linear-time row optima for implicit totally monotone matrices. |
| `convex/monge/monotone_minima.hpp` | Divide-and-conquer row optima under monotone argmins. |
| `convex/monge/divide_and_conquer_optimization.hpp` | DP-facing matrix search returning values and choices. |
| `convex/monge/knuth_optimization.hpp` | Quadratic Knuth optimization for interval DP. |
| `convex/monge/larsch.hpp` | Linear-time online minima and Monge DAG shortest paths. |
| `convex/monge/anti_monge_shortest_path.hpp` | Anti-Monge forward DP with a minimum index step. |
| `convex/monge/check.hpp` | Monge and anti-Monge inequality checks. |
| `convex/monge/min_plus_convolution.hpp` | Structured min-plus/max-plus convolution. |
