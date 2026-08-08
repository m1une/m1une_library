---
title: Minkowski Sum
documentation_of: ../../geometry/minkowski_sum.hpp
---

## Overview

`minkowski_sum` constructs the Minkowski sum of two ordered convex polygons:
the set of all points `a + b` for a point `a` in the first polygon and a point
`b` in the second polygon.

The input boundaries may be clockwise or counterclockwise and may contain a
repeated closing point, consecutive duplicates, or redundant collinear
vertices. Points and segments are supported as degenerate convex polygons.

## Function

```cpp
template <Coordinate T>
std::vector<Point<T>> minkowski_sum(
    std::vector<Point<T>> first,
    std::vector<Point<T>> second,
    long double eps = 1e-12L
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `minkowski_sum(first, second, eps)` | Returns the normalized boundary of the Minkowski sum. | $O(N+M)$ time and memory |

Both inputs must be nonempty and must describe convex boundaries in cyclic
order. The result is counterclockwise, starts at its lowest `(y, x)` vertex,
has no repeated closing point, and omits redundant collinear vertices.

The return type keeps the input coordinate type. Coordinate addition and edge
subtraction must therefore fit `T`. Geometric predicates use `wide_type<T>`;
integral coordinates consequently use signed 128-bit cross products. For
floating-point coordinates, `eps` controls normalization of collinear points.

## Example

```cpp
#include "geometry/minkowski_sum.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> square;
    square.emplace_back(0, 0);
    square.emplace_back(2, 0);
    square.emplace_back(2, 2);
    square.emplace_back(0, 2);

    std::vector<Point> segment;
    segment.emplace_back(0, 0);
    segment.emplace_back(3, 0);

    const auto sum = m1une::geometry::minkowski_sum(square, segment);
    for (const Point& point : sum) {
        std::cout << point.x << " " << point.y << "\n";
    }
}
```
