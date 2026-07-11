---
title: Minimum Enclosing Circle
documentation_of: ../../geometry/minimum_enclosing_circle.hpp
---

## Overview

`minimum_enclosing_circle(points)` finds the unique smallest circle containing
every input point. It uses the randomized incremental algorithm and returns the
circle together with one support set of at most three original points that
defines it.

Duplicate and collinear points are supported.

## Interface

```cpp
struct MinimumEnclosingCircle {
    Circle<long double> circle;
    std::vector<int> support;
};

template <Coordinate T>
std::optional<MinimumEnclosingCircle> minimum_enclosing_circle(
    const std::vector<Point<T>>& points,
    long double eps = 1e-12L
);
```

## Result

| Member | Description |
| --- | --- |
| `circle` | The minimum enclosing `Circle<long double>`. |
| `support` | One to three sorted original indices whose points define the circle. |

The function returns `std::nullopt` for an empty input. For one or more points,
`support` is nonempty. It may omit other input points that also lie on the
boundary.

For integral coordinates, containment decisions use signed 128-bit arithmetic;
all predicate intermediates must fit in that type. The returned center and
radius are still `long double`. For floating-point coordinates, `eps` controls
containment comparisons relative to the squared radius.

The shuffle is deterministic, so repeated calls on the same input produce the
same support set.

## Operations

| Function | Description | Complexity |
| --- | --- | --- |
| `minimum_enclosing_circle(points, eps)` | Returns the smallest circle containing all points without modifying the input. | Expected $O(N)$ time and $O(N)$ memory |

## Example

```cpp
#include "geometry/minimum_enclosing_circle.hpp"

#include <cassert>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(4, 0);
    points.emplace_back(2, 1);

    auto answer = m1une::geometry::minimum_enclosing_circle(points);
    assert(answer.has_value());
    assert(answer->circle.center.x == 2.0L);
    assert(answer->circle.center.y == 0.0L);
    assert(answer->circle.radius == 2.0L);
}
```
