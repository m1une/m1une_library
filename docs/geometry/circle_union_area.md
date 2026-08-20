---
title: Area of Union of Circles
documentation_of: ../../geometry/circle_union_area.hpp
---

## Overview

`circle_union_area` returns the area covered by at least one circle's enclosed
region, regardless of each `Circle::filled` flag.
Overlaps are counted once. Circles may be disjoint, tangent, nested, or
coincident, and radius-zero circles contribute no area.

For each circle, the implementation finds and merges the angular intervals of
its circumference covered by other circles. It integrates the remaining exposed
arcs using Green's theorem.

## Interface

```cpp
template <Coordinate T>
long double circle_union_area(
    const std::vector<Circle<T>>& circles,
    long double eps = 1e-12L
);
```

| Function | Complexity | Description |
| --- | --- | --- |
| `circle_union_area(circles, eps)` | $O(N^2\log N)$ time and $O(N)$ auxiliary memory | Returns the union area without modifying the input. |

Every radius and `eps` must be nonnegative. The result is a `long double`.
The tolerance is scaled to the radii and pairwise center distance when deciding
whether circles are tangent, contained, or coincident.

## Example

```cpp
#include "geometry/circle_union_area.hpp"

#include <iostream>
#include <vector>

int main() {
    using namespace m1une::geometry;
    std::vector<Circle<long double>> circles(2);
    circles[0] = Circle<long double>{Point<long double>(0, 0), 1};
    circles[1] = Circle<long double>{Point<long double>(2, 0), 1};

    std::cout << circle_union_area(circles) << "\n";
}
```
