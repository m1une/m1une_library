---
title: Circle Coverage Areas
documentation_of: ../../geometry/circle_coverage_areas.hpp
---

## Overview

`circle_coverage_areas` calculates the area covered by exactly $k$ enclosed
circle regions for every $k$, regardless of each `Circle::filled` flag. Circles
may be disjoint, tangent, nested, or coincident, and radius-zero circles do not
affect any area.

The implementation sweeps the intersection angles around every circumference.
Each arc is assigned its coverage multiplicity, then integrated with Green's
theorem.

## Interface

```cpp
template <Coordinate T>
std::vector<long double> circle_coverage_areas(
    const std::vector<Circle<T>>& circles,
    long double eps = 1e-12L
);
```

| Function | Complexity | Description |
| --- | --- | --- |
| `circle_coverage_areas(circles, eps)` | $O(N^2\log N)$ time and $O(N)$ auxiliary memory besides the result | Returns a vector `area` of size `N + 1`, where `area[k]` is covered by exactly `k` circles. |

`area[0]` is defined as zero because the uncovered plane has infinite area.
Summing `area[1]` through `area[N]` gives the union area. Every radius and
`eps` must be nonnegative. The tolerance is scaled to the radii and pairwise
center distance for geometric classifications.

## Example

```cpp
#include "geometry/circle_coverage_areas.hpp"

#include <iostream>
#include <vector>

int main() {
    using namespace m1une::geometry;
    std::vector<Circle<long double>> circles(2);
    circles[0] = Circle<long double>{Point<long double>(0, 0), 1};
    circles[1] = Circle<long double>{Point<long double>(1, 0), 1};

    std::vector<long double> area = circle_coverage_areas(circles);
    std::cout << area[1] << " " << area[2] << "\n";
}
```
