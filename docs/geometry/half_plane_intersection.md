---
title: Half-Plane Intersection
documentation_of: ../../geometry/half_plane_intersection.hpp
---

## Overview

`half_plane_intersection` constructs the bounded convex polygon common to a
collection of closed half-planes. A half-plane is represented by a directed
`Line<T>`: the legal side is the boundary line and everything to its left.

For a line from `a` to `b`, a point `p` is legal exactly when

$$
\operatorname{cross}(b-a,p-a) \geq 0.
$$

The result uses `long double` because intersections need not have integral
coordinates.

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `half_plane_intersection(half_planes, eps)` | Returns the bounded positive-area intersection polygon in counterclockwise order. | $O(N\log N)$ time and $O(N)$ memory |

The exact signature is:

```cpp
template <Coordinate T>
std::vector<Point<long double>> half_plane_intersection(
    const std::vector<Line<T>>& half_planes,
    long double eps = 1e-12L
);
```

Every boundary line must have distinct endpoints. The returned polygon starts
at its lexicographically smallest vertex and does not repeat that vertex at the
end. Closed boundaries are included.

An empty vector is returned when the common region is empty, unbounded, or has
zero area. Add a sufficiently large counterclockwise bounding rectangle when a
problem needs to turn an otherwise unbounded feasible region into a polygon.
The tolerance is applied after boundary directions are normalized, so it acts
as both an angular and a signed-distance tolerance.

## Example

```cpp
#include "geometry/half_plane_intersection.hpp"

#include <iostream>
#include <vector>

int main() {
    using namespace m1une::geometry;
    using P = Point<long double>;

    std::vector<Line<long double>> half_planes;
    half_planes.push_back(Line<long double>{P(0, 0), P(2, 0)});
    half_planes.push_back(Line<long double>{P(2, 0), P(2, 2)});
    half_planes.push_back(Line<long double>{P(2, 2), P(0, 2)});
    half_planes.push_back(Line<long double>{P(0, 2), P(0, 0)});

    auto polygon = half_plane_intersection(half_planes);
    std::cout << polygon.size() << "\n";  // 4
}
```
