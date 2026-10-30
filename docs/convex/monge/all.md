---
title: Monge Matrix Primitives and Algorithm Guide
documentation_of: ../../../convex/monge/all.hpp
---

All APIs here use `m1une::convex`, zero-based indices, and half-open ranges.
`convex/monge/all.hpp` includes **only matrix primitives**. Use
`convex/all.hpp` to include the applications too.

## Choose the abstraction

| Problem / assumption | Header and API | Time |
| --- | --- | --- |
| Fixed rectangle, totally monotone optima | [smawk.hpp](https://m1une.github.io/m1une_library/convex/monge/smawk.hpp): `smawk_row_argmin`, `smawk_row_argmax`, `smawk_row_select` | $O(H+W)$ |
| Fixed rectangle, only leftmost argmins are nondecreasing | [monotone_minima.hpp](https://m1une.github.io/m1une_library/convex/monge/monotone_minima.hpp): `monotone_row_argmin` | $O(H+W\log(H+1))$ |
| Online lower-triangular totally monotone matrix | [larsch.hpp](https://m1une.github.io/m1une_library/convex/monge/larsch.hpp): `Larsch` | $O(N)$ total |
| Check Monge / anti-Monge inequalities | [check.hpp](https://m1une.github.io/m1une_library/convex/monge/check.hpp): `is_monge`, `is_anti_monge` | $O(HW)$ |
| Finalized previous layer, monotone minimizing sources | [monge_transition.hpp](https://m1une.github.io/m1une_library/convex/monge_transition.hpp): `monotone_transition` | $O(H+W\log(H+1))$ |
| Finalized previous layer, Monge / anti-Monge costs | Same header: `monge_transition`, `anti_monge_transition` | $O(H+W)$ |
| Same-array forward recurrence, Monge costs, minimum step $D$ | [monge_shortest_path.hpp](https://m1une.github.io/m1une_library/convex/monge_shortest_path.hpp): `monge_shortest_path` | $O(N)$ for every $D$ |
| Same-array forward recurrence, anti-Monge costs, minimum step $D$ | Same header: `anti_monge_shortest_path` | $O(N\log N+ND)$ |
| Structured sequence min-plus / max-plus convolution | [min_plus_convolution.hpp](https://m1une.github.io/m1une_library/convex/min_plus_convolution.hpp) | $O(N+M)$ |
| Interval DP with monotone optimal splits | [algo/dp/knuth_optimization.hpp](https://m1une.github.io/m1une_library/algo/dp/knuth_optimization.hpp), namespace `m1une::algo` | $O(N^2)$ |

All bounds assume constant-time callbacks and arithmetic. See each page for
memory bounds, numeric requirements, and exact signatures.

## Property, ordering, and ties

For ordered rows $r<s$ and columns $c<d$, Monge means
$A(r,c)+A(s,d)\le A(r,d)+A(s,c)$; anti-Monge reverses this inequality.
A Monge matrix is totally monotone for leftmost minima: every submatrix has
nondecreasing leftmost minimizing column positions. Monotonicity of the minima
of the whole matrix alone is weaker; use monotone minima for that case.

Matrix primitives accept either dimensions or explicit `std::span<const int>`
row/column lists (vectors and arrays convert). The virtual matrix is
`value(rows[r], columns[c])`. Lists may be arbitrary permutations or subsets
of distinct nonnegative IDs. Answers are original column IDs, stored compactly
in **row list order**; `-1` means there are no columns. Ties choose the first
column in the supplied order. The library neither discovers nor sorts an order.

Reversing one axis turns anti-Monge into Monge. The public anti-Monge checks,
transitions, and shortest paths do this internally where appropriate. Their
minimization APIs select the **largest natural source ID** on ties. Ordered
Monge calls can describe other known permutations without a policy class or
an allocated matrix. An order describes the matrix, not a new graph topology.

## Offline transitions versus same-array shortest paths

For `g[j] = min_i(previous[i] + cost(i,j))`, all `previous` entries are final.
The matrix has **targets as rows**, **sources as columns**. Source constants
preserve Monge, so SMAWK can query any entry in any order.

For `dp[j] = min_{i <= j-D}(dp[i] + cost(i,j))`, the source distances are being
computed. Calling ordinary SMAWK on a callback reading that same unfinished
array is invalid. Use the shortest-path APIs, which enforce the dependency
order. LARSCH is the advanced primitive for managing that order yourself.

Both transition and shortest-path callbacks receive `(source, target)` and
return **only the cost**; the algorithms add the source value. Matrix callbacks
receive `(row, column)` and return the **entire entry**.

## Validity masks

SMAWK searches a complete rectangle. Arbitrary missing edges, triangular masks,
and padding with an infinity sentinel do not automatically preserve total
monotonicity, especially with a specified tie rule. The online primitive handles
its particular lower triangle; the anti-Monge shortest-path solver decomposes
legal edges into complete rectangles and a directly scanned boundary. The
convolution implementation uses a symbolic comparison oracle for its band.

## Migration

`larsch_shortest_path` becomes `monge_shortest_path` in
`convex/monge_shortest_path.hpp`, now with explicit `infinity` and optional
`minimum_step`. Both shortest paths return `MongeShortestPathResult<T>`.
`Larsch` stores the callback type; write `Larsch search(n, value)` using CTAD
instead of `Larsch<T>`.

`divide_and_conquer_transition` becomes `monotone_transition`;
`DivideAndConquerDpResult` becomes `MatrixTransitionResult`. The redundant
`divide_and_conquer_dp` value-and-choice wrapper is removed: call
`monotone_row_argmin` for a raw matrix. All application headers moved out of
`convex/monge/`; Knuth also moved to `m1une::algo`. No forwarding headers remain.
