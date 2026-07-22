---
title: Steiner Convex Decomposition
documentation_of: ../../geometry/steiner_convex_decomposition.hpp
---

## Overview

`steiner_convex_decomposition` partitions a simple polygon without holes into
non-strictly convex polygons. It may introduce Steiner vertices on the input
boundary or on cuts made earlier in the construction.

The returned geometry is an exact partition in the geometric sense: the pieces
have disjoint interiors and their union is the input polygon. The approximation
guarantee concerns only the number of pieces. This distinction is important;
the polygon itself is not approximated.

The routine applies the reflex-ray decomposition of Chazelle and Dobkin. Each
cut starts at one reflex vertex, lies strictly inside its admissible angular
wedge, and stops at the first edge of the current subdivision. Convex-chain
preprocessing makes ray intersections sensitive to the number of reflex
vertices rather than requiring a scan of the full boundary for every cut.

## Function

```cpp
template <std::floating_point T>
std::optional<std::vector<std::vector<Point<long double>>>>
steiner_convex_decomposition(
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
);
```

| Function | Result | Time | Memory |
| --- | --- | --- | --- |
| `steiner_convex_decomposition(polygon, eps)` | An exact partition into $R+1$ convex pieces. | $O(N + R^2\log(2N/R))$ | $O(N+R)$ |

Here $N$ is the number of vertices after cleanup and $R$ is the number of
reflex vertices. For $R=0$, the function returns the cleaned polygon as its
only piece in $O(N)$ time; the logarithmic expression in the table applies
when $R>0$.

## Piece-count guarantee

Each cut removes one remaining reflex angle and increases the number of pieces
by one, so the result contains exactly $R+1$ pieces unless $R=0$.

Any convex decomposition in the unrestricted Steiner-point model contains at
least $\lceil R/2\rceil+1$ pieces: one new convex piece can remove at most two
reflex angles. Consequently this routine returns strictly fewer than twice the
minimum possible number of pieces.

This is not a minimum-cardinality routine. In particular, it does not implement
the much more involved X/Y-pattern dynamic program required for the optimal
$O(N+R^3)$ Chazelle--Dobkin algorithm. Use
[`minimum_convex_decomposition`](convex_decomposition.md) when minimum
cardinality is required and Steiner points are forbidden.

## Input and output rules

Only floating-point coordinate types are supported. Steiner intersections need
not be integral even when all input coordinates are integers, so an integral
overload is intentionally not provided. All output coordinates use
`long double`.

The input may be clockwise or counterclockwise. A repeated closing point,
consecutive duplicates, and redundant collinear boundary vertices are removed.
The polygon must be simple, have nonzero area, and have no holes. Simplicity is
a precondition so that validation does not add an $O(N^2)$ term to the stated
bound.

The return value is `nullopt` when fewer than three effective vertices remain,
the signed area is zero, or the floating-point construction cannot be completed
consistently. Every returned polygon is counterclockwise and convex in the
non-strict sense. `eps` controls floating-point predicates and degeneracy
handling.

## Example

```cpp
#include "geometry/steiner_convex_decomposition.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<double>;
    std::vector<Point> polygon;
    polygon.emplace_back(0, 0);
    polygon.emplace_back(5, 0);
    polygon.emplace_back(5, 2);
    polygon.emplace_back(2, 2);
    polygon.emplace_back(2, 5);
    polygon.emplace_back(0, 5);

    auto parts =
        m1une::geometry::steiner_convex_decomposition(polygon);
    if (!parts.has_value()) return 0;
    std::cout << parts->size() << "\n";  // 2
}
```
