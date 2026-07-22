---
title: Convex Decomposition
documentation_of: ../../geometry/convex_decomposition.hpp
---

## Overview

This header partitions a simple polygon without holes into convex polygons. It
provides two choices:

* `convex_decomposition` triangulates the polygon and applies the
  Hertel--Mehlhorn diagonal-removal algorithm. It is the routine to use under
  ordinary contest constraints.
* `minimum_convex_decomposition` uses Keil--Snoeyink dynamic programming over
  visible diagonals and narrowest-pair stacks. It returns the smallest possible
  number of pieces. Its running time is sensitive to the number of reflex
  vertices rather than being quartic in the total vertex count.

Both algorithms return an exact geometric partition: the pieces have disjoint
interiors and their union is exactly the input polygon. The approximation
guarantee of `convex_decomposition` concerns only how many pieces it returns
compared with the minimum possible number.

Both algorithms use the **no-Steiner-point model**: every output vertex is an
input vertex, apart from removing redundant boundary vertices. This restriction
is important when interpreting the piece-count guarantee and the word
"minimum."

## Functions

```cpp
template <Coordinate T>
std::optional<std::vector<std::vector<Point<T>>>>
convex_decomposition(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
);

template <Coordinate T>
std::optional<std::vector<std::vector<Point<T>>>>
minimum_convex_decomposition(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
);
```

| Function | Result | Time | Memory |
| --- | --- | --- | --- |
| `convex_decomposition(polygon, eps)` | An exact partition containing at most four times the minimum number of convex pieces. | $O(N^2)$ | $O(N)$ |
| `minimum_convex_decomposition(polygon, eps)` | A decomposition with the minimum possible number of pieces. | $O(N + \min\lbrace NR^2, R^4 \rbrace)$ | $O(N + \min\lbrace NR^2, R^4 \rbrace)$ |

Here $N$ is the number of vertices after cleanup and $R$ is the number of
reflex vertices (vertices whose interior angle is greater than $\pi$).

The bound for the exact routine is easy to misread. The implementation chooses
between these two Keil--Snoeyink paths:

* The direct narrowest-pair DP stores only subproblems with at least one reflex
  endpoint and takes $O(NR^2)$ time and memory.
* When $R^2 < N$, biased-decomposition reduction retains the $O(R^2)$ vertices
  that can be endpoints of reflex extensions and diagonal extensions, and runs
  the same DP on that reduced polygon. Including reduction and reconstruction,
  this path takes $O(N + R^4)$ time and memory.

The minimum of those paths is therefore
$O(N + \min\lbrace NR^2, R^4 \rbrace)$. The reduction is internal: output pieces still
contain the original polygon boundary, including vertices omitted from the DP
instance. $R$ is not the number of vertices in the reduced polygon.

## Input and output rules

The input may be clockwise or counterclockwise. A repeated closing point,
consecutive duplicates, and redundant collinear boundary vertices are removed.
The polygon must be simple and have no holes. The exact routine treats
simplicity as a precondition so that it does not add an $O(N^2)$ validation step
to its reflex-sensitive bound. `convex_decomposition` validates simplicity.
The return value is `nullopt` when fewer than three effective vertices remain,
the area is zero, validation fails where performed, or construction fails.

Every returned polygon is counterclockwise, does not repeat its first point at
the end, and is convex in the non-strict sense. The pieces have disjoint
interiors and their union is the original closed polygon.

"Minimum" means the minimum **number of non-strictly convex pieces**, not that
each piece is strictly convex. Collinear vertices can therefore occur on an
output boundary. The approximation factor compares against the same
no-Steiner-point optimum.

For standard integral coordinate types up to 64 bits, the exact routine
performs no floating-point conversion. It scans the cleaned polygon once and
selects the smallest integer type that is provably wide enough for its
projective visibility predicates and rational ray-intersection comparisons:

| Largest coordinate magnitude | Predicate type |
| --- | --- |
| Fewer than $2^{30}$ | built-in `__int128_t` |
| Fewer than $2^{62}$ | [`Int256`](../utilities/int256.md) |
| Otherwise | [`Int512`](../utilities/int512.md) |

The largest intermediate has magnitude below $2^{4k+6}$ when coordinate
magnitudes use at most $k$ bits. Thus full-range 32-bit coordinates are not
dispatched to `__int128_t`, while the common bound
$|x|,|y|\le 10^9$ is.
Selection uses absolute coordinates rather than edge lengths because
homogeneous line coefficients are formed before translation-dependent terms
cancel; translating a polygon far from the origin can therefore select a wider
type. The scan costs $O(N)$ and does not change the overall bound.

Input turns still use the geometry module's ordinary widened integer type, so
results are exact as long as those ordinary predicates do not overflow. `eps`
has no effect on integral predicates.

For floating-point coordinates, visibility and ray shooting use `long double`,
and `eps` controls predicate tolerance.

## Example

```cpp
#include "geometry/convex_decomposition.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> polygon;
    polygon.emplace_back(0, 0);
    polygon.emplace_back(5, 0);
    polygon.emplace_back(5, 2);
    polygon.emplace_back(2, 2);
    polygon.emplace_back(2, 5);
    polygon.emplace_back(0, 5);

    auto parts = m1une::geometry::convex_decomposition(polygon);
    if (!parts.has_value()) return 0;
    std::cout << parts->size() << "\n";  // 2
}
```
