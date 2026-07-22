---
title: Manhattan Segment Intersections
documentation_of: ../../geometry/manhattan_segment_intersections.hpp
---

## Overview

`manhattan_segment_intersections` counts pairs formed by one horizontal and one
vertical closed segment that intersect. `manhattan_segment_intersection_points`
returns their exact integral intersection points. Segment endpoints are
included, so a perpendicular pair touching at an endpoint contributes one.

The implementation sweeps upward through the endpoint and query events. A
Fenwick tree over compressed x-coordinates stores the active vertical segments.
At the same y-coordinate, vertical segments are added before horizontal queries
and removed afterward, which gives the closed-endpoint behavior.

If parallel segments do not overlap or touch, the result is the total number of
intersections among the input segments. This is the condition used by AOJ
CGL_6_A. Otherwise, the function still counts all horizontal-vertical pairs but
does not count parallel pairs.

## Interface

```cpp
template <std::integral T>
long long manhattan_segment_intersections(
    const std::vector<Segment<T>>& segments
);

template <std::integral T>
std::vector<Point<T>> manhattan_segment_intersection_points(
    const std::vector<Segment<T>>& segments
);
```

| Function | Complexity | Description |
| --- | --- | --- |
| `manhattan_segment_intersections(segments)` | $O(N\log N)$ time and $O(N)$ memory | Returns the number of intersecting horizontal-vertical pairs without modifying the input. |
| `manhattan_segment_intersection_points(segments)` | $O(N\log N+K)$ time and $O(N+K)$ memory | Returns one exact point for each of the $K$ intersecting horizontal-vertical pairs. |

Every segment must be nondegenerate and parallel to one coordinate axis. These
requirements and the conversion of the input size to `int` are checked by
assertions. Coordinates must be integral. The count is returned as `long long`.
The point order follows the sweep and should not be treated as sorted. If
several segment pairs meet at the same coordinate, that point occurs once per
pair, so the point-vector size always equals the counting result.

## Example

```cpp
#include "geometry/manhattan_segment_intersections.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    using Segment = m1une::geometry::Segment<long long>;

    std::vector<Segment> segments;
    segments.push_back(Segment{Point(0, 0), Point(0, 4)});
    segments.push_back(Segment{Point(-2, 2), Point(3, 2)});
    segments.push_back(Segment{Point(2, 1), Point(2, 3)});

    auto intersections =
        m1une::geometry::manhattan_segment_intersection_points(segments);
    for (const Point& point : intersections) {
        std::cout << point.x << " " << point.y << "\n";
    }
}
```
