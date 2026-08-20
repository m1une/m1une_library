---
title: Linear Objects
documentation_of: ../../geometry/linear.hpp
---

## Overview

This header provides `Line<T>`, `Segment<T>`, and `Ray<T>` together with
projection, reflection, distances, intersection predicates, segment centroids,
classified intersections, and closest-point witnesses.

Integral predicates use signed 128-bit arithmetic. Constructed coordinates and
distances are returned using `long double`.

For floating-point coordinates, `eps` is relative to the directions or segment
lengths involved. Parallelism, orthogonality, and collinearity use scale-aware
determinant or dot-product tests. Segment endpoint checks allow a normalized
parameter error of `eps`, so uniformly scaling the complete configuration does
not change the result. Ray direction comparisons use the same scale-aware
rules. A degenerate segment has no length scale; its point test therefore uses
`eps` as an absolute coordinate tolerance.

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

template <Coordinate T>
struct Ray {
    Point<T> origin;
    Point<T> through;
};
```

A line requires distinct endpoints. A segment may be degenerate. A ray starts
at `origin`, contains `through`, and continues indefinitely in the direction
`through - origin`; these two points must be distinct.

Intersections among lines, segments, and rays use one common result type:

```cpp
enum class LinearIntersectionKind {
    Empty,
    Point,
    Segment,
    Ray,
    Line,
};

struct LinearIntersection {
    LinearIntersectionKind kind;
    Point<long double> first;
    Point<long double> second;
};
```

The kind describes the complete intersection set. For `Point`, `first` and
`second` are equal. For `Segment`, they are its two endpoints. For `Ray`,
`first` is the origin and `second` is a distinct point in its forward
direction. For `Line`, the two points are distinct representatives of the
line. An `Empty` result has no meaningful point values. Segment endpoints do
not have a canonical order.

`linear.hpp` provides these overloads:

```cpp
template <Coordinate T>
LinearIntersection linear_intersection(
    const Line<T>& first,
    const Line<T>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
LinearIntersection linear_intersection(
    const Line<T>& line,
    const Segment<T>& segment,
    long double eps = 1e-12L
);

template <Coordinate T>
LinearIntersection linear_intersection(
    const Segment<T>& segment,
    const Line<T>& line,
    long double eps = 1e-12L
);

template <Coordinate T>
LinearIntersection linear_intersection(
    const Segment<T>& first,
    const Segment<T>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
LinearIntersection linear_intersection(
    const Ray<T>& ray,
    const Line<T>& line,
    long double eps = 1e-12L
);

template <Coordinate T>
LinearIntersection linear_intersection(
    const Line<T>& line,
    const Ray<T>& ray,
    long double eps = 1e-12L
);

template <Coordinate T>
LinearIntersection linear_intersection(
    const Ray<T>& ray,
    const Segment<T>& segment,
    long double eps = 1e-12L
);

template <Coordinate T>
LinearIntersection linear_intersection(
    const Segment<T>& segment,
    const Ray<T>& ray,
    long double eps = 1e-12L
);

template <Coordinate T>
LinearIntersection linear_intersection(
    const Ray<T>& first,
    const Ray<T>& second,
    long double eps = 1e-12L
);
```

Every overload runs in $O(1)$.

All overloads share one parametric kernel. Internally an object is written as
$P(t)=O+tD$ with one of three parameter domains: every real value for a line,
$[0,1]$ for a segment, or $[0,+\infty)$ for a ray. Nonparallel objects test
the unique crossing parameter against both domains. Collinear objects
intersect their one-dimensional parameter intervals and translate the result
back into `Empty`, `Point`, `Segment`, `Ray`, or `Line`. Degenerate segments
are handled as singleton points before a supporting direction is required.

## Closest points

```cpp
struct ClosestPoints {
    Point<long double> first;
    Point<long double> second;
};

template <Coordinate T>
ClosestPoints closest_points(
    const Point<T>& first,
    const Point<T>& second
);

template <Coordinate T>
ClosestPoints closest_points(const Line<T>& line, const Point<T>& point);

template <Coordinate T>
ClosestPoints closest_points(const Point<T>& point, const Line<T>& line);

template <Coordinate T>
ClosestPoints closest_points(
    const Segment<T>& segment,
    const Point<T>& point
);

template <Coordinate T>
ClosestPoints closest_points(
    const Point<T>& point,
    const Segment<T>& segment
);

template <Coordinate T>
ClosestPoints closest_points(const Ray<T>& ray, const Point<T>& point);

template <Coordinate T>
ClosestPoints closest_points(const Point<T>& point, const Ray<T>& ray);

template <Coordinate T>
ClosestPoints closest_points(
    const Line<T>& first,
    const Line<T>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
ClosestPoints closest_points(
    const Line<T>& line,
    const Segment<T>& segment,
    long double eps = 1e-12L
);

template <Coordinate T>
ClosestPoints closest_points(
    const Segment<T>& segment,
    const Line<T>& line,
    long double eps = 1e-12L
);

template <Coordinate T>
ClosestPoints closest_points(
    const Segment<T>& first,
    const Segment<T>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
ClosestPoints closest_points(
    const Line<T>& line,
    const Ray<T>& ray,
    long double eps = 1e-12L
);

template <Coordinate T>
ClosestPoints closest_points(
    const Ray<T>& ray,
    const Line<T>& line,
    long double eps = 1e-12L
);

template <Coordinate T>
ClosestPoints closest_points(
    const Ray<T>& ray,
    const Segment<T>& segment,
    long double eps = 1e-12L
);

template <Coordinate T>
ClosestPoints closest_points(
    const Segment<T>& segment,
    const Ray<T>& ray,
    long double eps = 1e-12L
);

template <Coordinate T>
ClosestPoints closest_points(
    const Ray<T>& first,
    const Ray<T>& second,
    long double eps = 1e-12L
);
```

`first` belongs to the first argument and `second` belongs to the second. Their
distance is minimal. Intersecting objects return the same point twice.
Reversing the arguments swaps the witnesses; when several minimizing pairs
exist, a deterministic coordinate-based tie-break is used. Every overload
runs in $O(1)$. The linear-object `distance` overloads return the distance
between these witnesses.

## Line and segment operations

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
| `projection(segment, point)` | Returns the closest point on the closed segment, including for a degenerate segment. | $O(1)$ |
| `intersects(first, second, eps)` | Tests whether two closed segments intersect, including overlap. | $O(1)$ |
| `intersects(line, segment, eps)` | Tests whether an infinite line and a closed segment intersect. Both argument orders are supported. | $O(1)$ |
| `distance(segment, point)` | Point-to-segment distance. Both argument orders are supported. | $O(1)$ |
| `distance(first, second)` | Segment-to-segment distance. | $O(1)$ |
| `distance(line, segment)` | Line-to-segment distance. Both argument orders are supported. | $O(1)$ |
| `linear_intersection(first, second, eps)` | Classifies the complete intersection as empty, a point, a segment, a ray, or a line. Every line/segment/ray pairing is supported. | $O(1)$ |

For a degenerate segment, `linear_intersection` treats it as a point. Its
centroid is also that endpoint. Infinite lines have no centroid overload.

## Ray operations

| Function | Description | Complexity |
| --- | --- | --- |
| `on_ray(ray, point, eps)` | Tests whether `point` belongs to the closed ray. The origin is included. | $O(1)$ |
| `projection(ray, point)` | Returns the closest point on the ray, clamped to its origin. | $O(1)$ |
| `distance(ray, point)` | Returns the point-to-ray distance. Both argument orders are supported. | $O(1)$ |
| `reflection(line, ray)` | Reflects the complete ray across an infinite line. | $O(1)$ |
| `reflected_ray(incoming, hit, mirror, eps)` | Creates the outgoing ray after `incoming` hits `mirror` at `hit`. | $O(1)$ |
| `intersects(ray, line, eps)` | Tests whether a ray and an infinite line share a point. Both argument orders are supported. | $O(1)$ |
| `intersects(ray, segment, eps)` | Tests whether a ray and a closed segment share a point. Both argument orders are supported. | $O(1)$ |
| `intersects(first, second, eps)` | Tests whether two closed rays share a point. | $O(1)$ |
| `distance(ray, line)` | Minimum ray-to-line distance. Both argument orders are supported. | $O(1)$ |
| `distance(ray, segment)` | Minimum ray-to-segment distance. Both argument orders are supported. | $O(1)$ |
| `distance(first, second)` | Minimum distance between two rays. | $O(1)$ |

`reflected_ray` requires `hit` to lie on `mirror`. Its result starts at `hit`;
the angle of incidence equals the angle of reflection. Collinear overlap counts
as an intersection. A line and ray can intersect in an empty set, a point, or
a ray. A segment and ray can intersect in an empty set, a point, or a segment.
Two rays can intersect in an empty set, a point, a segment, or a ray.

## Closest-points example

```cpp
Segment<long long> segment;
segment.a = Point<long long>(0, 0);
segment.b = Point<long long>(2, 0);

Ray<long long> ray;
ray.origin = Point<long long>(5, 3);
ray.through = Point<long long>(6, 3);

ClosestPoints result = closest_points(segment, ray);
// result.first == (2, 0), result.second == (5, 3)
```

## Example

```cpp
#include "geometry/linear.hpp"

#include <iostream>

int main() {
    using namespace m1une::geometry;
    Segment<long long> first;
    first.a = Point<long long>(0, 0);
    first.b = Point<long long>(2, 2);

    Segment<long long> second;
    second.a = Point<long long>(0, 2);
    second.b = Point<long long>(2, 0);

    LinearIntersection result = linear_intersection(first, second);
    if (result.kind == LinearIntersectionKind::Point) {
        std::cout << result.first.x << " " << result.first.y << "\n";
    }
}
```
