---
title: Angle Sort
documentation_of: ../../geometry/angle_sort.hpp
---

## Overview

This header sorts points counterclockwise by their angle around a chosen
origin, without calling `atan2`.

```cpp
sort_by_angle(points, origin, start);
auto sorted = angle_sorted(points, origin, start);
```

`sort_by_angle` modifies its argument. `angle_sorted` returns a sorted copy.
Both take $O(N\log N)$ time.

## Complexity Notation

* `N` is the number of points being sorted.

`sort_by_angle` and `angle_sorted` take $O(N\log N)$ time. The comparator uses
$O(1)$ additional memory per comparison.

## Ordering Convention

The default, `AngleSortStart::NegativeXAxis`, sorts by the usual `atan2(y, x)`
value from $-\pi$ to $\pi$. Imagine starting just below the negative x-axis
and rotating counterclockwise:

| Order | Direction | Angle |
| --- | --- | --- |
| 1 | down-left | close to $-\pi$ |
| 2 | down | $-\pi/2$ |
| 3 | right | $0$ |
| 4 | up | $\pi/2$ |
| 5 | left | $\pi$ |

In short:

```text
down-left -> down -> right -> up -> up-left -> left
```

The origin is treated as having angle zero, so it appears with points pointing
right. This convention matches Library Checker's Sort Points by Argument
problem.

`AngleSortStart::PositiveXAxis` uses the more common circular ordering that
starts on the positive x-axis:

```text
right -> up -> left -> down -> back to right
```

Points on the same ray are ordered by increasing distance from `origin`.
Equivalent duplicate points may appear in either relative order.

## Comparator

`AngleLess<T>` is the comparator used by the helpers:

```cpp
m1une::geometry::AngleLess<long long> less(origin);
std::sort(points.begin(), points.end(), less);
```

For integral coordinates, comparisons use signed 128-bit arithmetic. As with
the other exact geometry predicates, coordinate differences and products must
fit that type.

## Example

```cpp
#include "geometry/angle_sort.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(1, 0);
    points.emplace_back(0, 1);
    points.emplace_back(-1, 0);
    points.emplace_back(0, -1);

    m1une::geometry::sort_by_angle(
        points,
        Point(0, 0),
        m1une::geometry::AngleSortStart::PositiveXAxis
    );

    for (const Point& point : points) {
        std::cout << point.x << ' ' << point.y << "\n";
    }
}
```

## Point records

```cpp
template <PointRecord P>
requires (!std::same_as<P, Point<typename P::coordinate_type>>)
void sort_by_angle(
    std::vector<P>& points,
    Point<typename P::coordinate_type> origin = {},
    AngleSortStart start = AngleSortStart::NegativeXAxis
);

template <PointRecord P>
requires (!std::same_as<P, Point<typename P::coordinate_type>>)
std::vector<P> angle_sorted(
    std::vector<P> points,
    Point<typename P::coordinate_type> origin = {},
    AngleSortStart start = AngleSortStart::NegativeXAxis
);
```

These overloads accept records described in
[points with metadata](https://m1une.github.io/m1une_library/geometry/point.hpp#points-with-metadata).
They retain their documented complexities. Comparisons use coordinates only;
sorting and convex-boundary normalization retain complete records for surviving
vertices. Queries return the same geometric result types as the ordinary-point
versions.
