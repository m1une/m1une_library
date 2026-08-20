---
title: Lines and Segments
documentation_of: ../../geometry/line.hpp
---

## Overview

This header provides `Line<T>` and `Segment<T>` together with projection,
reflection, distances, intersection tests, segment centroids, and constructed
intersections.

Segment predicates are exact for integral coordinates through 128-bit cross
products. Constructed coordinates are returned as `Point<long double>`.

## Types

```cpp
template <Coordinate T>
struct Line {
    Point<T> a;
    Point<T> b;
};

template <Coordinate T>
struct Segment {
    Point<T> a;
    Point<T> b;
};
```

A line requires distinct endpoints. A segment may be degenerate.

Segment intersections are classified explicitly:

```cpp
enum class SegmentIntersectionKind {
    Empty,
    Point,
    Overlap,
};

struct SegmentIntersection {
    SegmentIntersectionKind kind;
    Point<long double> first;
    Point<long double> second;
};

template <Coordinate T>
SegmentIntersection segment_intersection(
    const Segment<T>& first,
    const Segment<T>& second,
    long double eps = 1e-12L
);
```

For `Point`, both result points equal the unique intersection. For `Overlap`,
they are the endpoints of the common closed segment, ordered from `first.a`
toward `first.b` in the function call. The point values in an `Empty` result
have no meaning and should not be inspected.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `centroid(segment)` | Returns the midpoint, which is the centroid under uniform length. | $O(1)$ |
| `on_line(line, point, eps)` | Tests whether a point lies on an infinite line. | $O(1)$ |
| `parallel(first, second, eps)` | Tests whether two lines are parallel. | $O(1)$ |
| `orthogonal(first, second, eps)` | Tests whether two lines are perpendicular. | $O(1)$ |
| `projection(line, point)` | Returns the orthogonal projection. | $O(1)$ |
| `reflection(line, point)` | Reflects a point across a line. | $O(1)$ |
| `intersects(first, second, eps)` | Tests whether two infinite lines share a point, including coincidence. | $O(1)$ |
| `distance(line, point)` | Point-to-line distance. Both argument orders are supported. | $O(1)$ |
| `distance(first, second)` | Distance between two infinite lines. | $O(1)$ |
| `on_segment(segment, point, eps)` | Tests whether a point lies on a closed segment. | $O(1)$ |
| `intersects(first, second, eps)` | Tests whether two closed segments intersect, including overlap. | $O(1)$ |
| `intersects(line, segment, eps)` | Tests whether an infinite line and a closed segment intersect. Both argument orders are supported. | $O(1)$ |
| `distance(segment, point)` | Point-to-segment distance. Both argument orders are supported. | $O(1)$ |
| `distance(first, second)` | Segment-to-segment distance. | $O(1)$ |
| `distance(line, segment)` | Line-to-segment distance. Both argument orders are supported. | $O(1)$ |
| `line_intersection(first, second, eps)` | Returns the unique line intersection, or `nullopt` for parallel/coincident lines. | $O(1)$ |
| `segment_intersection(first, second, eps)` | Classifies the intersection of two closed segments and returns its unique point or overlap endpoints. | $O(1)$ |
| `line_segment_intersection(line, segment, eps)` | Returns the unique intersection, or `nullopt` for no intersection or collinear overlap. Both argument orders are supported. | $O(1)$ |

For a degenerate segment, `line_segment_intersection` returns its endpoint when
that point lies on the line. Its centroid is also that endpoint. Infinite lines
have no centroid overload.

## Example

```cpp
#include "geometry/line.hpp"

#include <iostream>

int main() {
    using namespace m1une::geometry;
    Segment<long long> first;
    first.a = Point<long long>(0, 0);
    first.b = Point<long long>(2, 2);

    Segment<long long> second;
    second.a = Point<long long>(0, 2);
    second.b = Point<long long>(2, 0);

    SegmentIntersection result = segment_intersection(first, second);
    if (result.kind == SegmentIntersectionKind::Point) {
        std::cout << result.first.x << " " << result.first.y << "\n";
    }
}
```
