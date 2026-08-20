---
title: Polygons
documentation_of: ../../geometry/polygon.hpp
---

## Overview

This header provides polygon area, point containment, path clipping, polygon
intersection and distance, triangulation, and centroids for general simple
polygons.

Algorithms accept the traditional `std::vector<Point<T>>` boundary. The
`Polygon<T>` object adds explicit set semantics:

```cpp
template <Coordinate T>
struct Polygon {
    std::vector<Point<T>> vertices;
    bool filled = true;
};
```

When `filled` is `true`, the object is the closed polygonal region. When it is
`false`, it is only the boundary. General `contains`, `intersects`,
`closest_points`, and `distance` overloads honor the flag. Area, centroid,
triangulation, and explicitly named boundary-event functions use `vertices`
independently of the flag. The first vertex must not be repeated at the end.

## Point Containment

`point_in_polygon` returns:

* `PointInPolygon::Outside`
* `PointInPolygon::Boundary`
* `PointInPolygon::Inside`

The polygon may be clockwise or counterclockwise and may be non-convex.

## Polygon object interface

The query families below support both argument orders.

```cpp
template <Coordinate T, Coordinate P>
PointInPolygon point_in_polygon(
    const Polygon<T>& polygon,
    const Point<P>& point,
    long double eps = 1e-12L
);

template <Coordinate T, Coordinate P>
bool contains(
    const Polygon<T>& polygon,
    const Point<P>& point,
    long double eps = 1e-12L
);

template <Coordinate T, Coordinate P>
ClosestPoints closest_points(
    const Polygon<T>& polygon,
    const Point<P>& point,
    long double eps = 1e-12L
);

template <Coordinate T, Coordinate S>
ClosestPoints closest_points(
    const Polygon<T>& polygon,
    const Segment<S>& segment,
    long double eps = 1e-12L
);

template <Coordinate T, Coordinate R>
ClosestPoints closest_points(
    const Polygon<T>& polygon,
    const Ray<R>& ray,
    long double eps = 1e-12L
);

template <Coordinate A, Coordinate B>
ClosestPoints closest_points(
    const Polygon<A>& first,
    const Polygon<B>& second,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate T>
ClosestPoints closest_points(
    const Circle<C>& circle,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
);
```

`intersects` has the same five pairs and `eps`; `distance` has the same pairs
without `eps`. Reverse overloads swap the two returned witnesses for
`closest_points`.

## Clipping interface

`clip` returns the parts of its first argument contained in the set selected by
`polygon.filled`. A filled polygon clips against its closed enclosed region; a
boundary-only polygon retains only isolated contacts and collinear overlaps.
The first argument is always treated as a path, independently of
`circle.filled`.

```cpp
struct ParameterInterval {
    long double begin;
    long double end;
};

template <Coordinate L, Coordinate T>
std::vector<ParameterInterval> clip(
    const Line<L>& line,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
);

template <Coordinate R, Coordinate T>
std::vector<ParameterInterval> clip(
    const Ray<R>& ray,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
);

template <Coordinate S, Coordinate T>
std::vector<ParameterInterval> clip(
    const Segment<S>& segment,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate T>
std::vector<AngularCoverage> clip(
    const Circle<C>& circle,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
);
```

For every linear object, parameter `t` denotes
`origin + t * direction`. A line uses `origin = a` and
`direction = b - a`; a ray uses `origin` and `through - origin`; a segment
uses `a` and `b - a`. Line parameters are unrestricted, ray parameters are
nonnegative, and segment parameters lie in `[0, 1]`.

Linear results are sorted, disjoint, closed intervals. `begin == end` denotes
an isolated contact such as a tangency. A degenerate segment returns `[0, 0]`
exactly when its point belongs to the selected polygon set.

Circle results use the `AngularCoverage` representation documented in
[`geometry/circle.hpp`](circle.md): `Point` denotes an isolated contact, `Arc`
denotes a counterclockwise interval, and `Full` denotes the complete
circumference. Results are sorted by normalized `begin`; a wrapping arc has an
`end` greater than $2\pi$. An empty vector denotes empty clipping.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `centroid(triangle)` | Returns the filled triangle's centroid. The triangle is a `std::array<Point<T>, 3>`. | $O(1)$ |
| `centroid(polygon, eps)` | Returns the uniformly filled polygon's centroid, or `nullopt` for zero area. | $O(N)$ |
| `polygon_area2(polygon)` | Returns signed twice-area. Positive means counterclockwise. | $O(N)$ |
| `polygon_area(polygon)` | Returns absolute area as `long double`. | $O(N)$ |
| `polygon_centroid(polygon, eps)` | Returns the centroid of a uniformly filled polygon, or `nullopt` for zero area. | $O(N)$ |
| `polygon_center_of_gravity(polygon, eps)` | Alias of `polygon_centroid`. | $O(N)$ |
| `is_simple_polygon(polygon, eps)` | Tests whether polygon edges only meet at adjacent endpoints. | $O(N^2)$ |
| `triangulate_polygon(polygon, eps)` | Ear-clips a simple polygon, or returns `nullopt` when triangulation fails. | $O(N^2)$ |
| `point_in_polygon(polygon, point, eps)` | Classifies a point against any simple polygon. | $O(N)$ |
| `clip(line/ray/segment, Polygon, eps)` | Returns parameter intervals belonging to the selected polygon set. | $O(N \log N)$ |
| `clip(circle, Polygon, eps)` | Returns angular points and arcs belonging to the selected polygon set. | $O(N \log N)$ |
| `intersects(ray, polygon, eps)` | Tests intersection with the closed filled polygon. Both argument orders are supported. | $O(N \log N)$ |
| `distance(ray, polygon)` | Minimum distance to the closed filled polygon. Both argument orders are supported. | $O(N \log N)$ |
| `intersects(first, second, eps)` | Tests whether two closed filled simple polygons intersect. | $O(NM)$ |
| `distance(first, second)` | Minimum distance between two closed filled simple polygons. | $O(NM)$ |
| `point_in_polygon(Polygon, point, eps)` | Classifies against the enclosed region, regardless of `filled`. | $O(N)$ |
| `contains(Polygon, point, eps)` | Tests membership in the set selected by `filled`. | $O(N)$ |
| `closest_points(Polygon, point/segment/ray, eps)` | Returns minimum-distance witnesses for the selected set. | $O(N)$ |
| `closest_points(first_polygon, second_polygon, eps)` | Returns witnesses for the selected polygon sets. | $O(NM)$ |
| `closest_points(circle, polygon, eps)` | Returns witnesses while honoring both `filled` flags. | $O(N)$ |
| `intersects(Polygon, object, eps)` | Tests whether the selected sets overlap. | Same as `closest_points` |
| `distance(Polygon, object)` | Returns the distance between the selected sets. | Same as `closest_points` |

Polygon queries require at least three vertices unless stated otherwise.

## Centroid and center of gravity

`centroid(polygon)` and `polygon_centroid` compute the center of gravity of a
lamina with uniform density over the polygon's filled area.
`centroid(polygon)` is the geometry-wide overload and `polygon_centroid` is its
explicitly named equivalent. Both accept clockwise or counterclockwise simple
polygons and return `std::optional<Point<long double>>`.

A polygon with zero signed area has no area centroid, so the function returns
`std::nullopt`. This is different from the arithmetic mean of the vertices,
which generally is not the polygon's center of gravity.

For a triangle represented by `std::array<Point<T>, 3>`, `centroid(triangle)`
returns the arithmetic mean of its three vertices. This formula is also the
usual filled-area centroid for every nondegenerate triangle.

## Triangulation

`triangulate_polygon` uses ear clipping and accepts clockwise or
counterclockwise simple polygons. It removes a repeated closing point,
consecutive duplicate points, and redundant collinear boundary vertices before
triangulation. The result contains counterclockwise triangles whose interiors
are disjoint and whose union is the polygon. An input with $K$ remaining
vertices produces $K-2$ triangles.

The return value is `std::nullopt` for fewer than three effective vertices,
zero area, self-intersection, or another failure to find a valid ear.

## Clipping behavior

Clipping a path against a concave polygon may produce multiple components. For
example, a ray can produce intervals `[2, 4]` and `[7, 9]`; these directly
describe the two pieces of the ray inside the polygon. Shared polygon vertices
are counted once, tangencies become point intervals, and travel along a polygon
edge becomes one continuous interval.

Unlike `intersects`, `clip` intentionally has no reverse argument overload:
the first argument determines the parameter system and the type of the result.

## Polygon intersection and distance

`intersects(first, second)` and `distance(first, second)` accept any simple
polygons, in clockwise or counterclockwise order.

For optimized containment, cuts, diameter, intersection construction,
Minkowski sums, and other convex-only operations, include
[`geometry/convex_polygon.hpp`](convex_polygon.md).

To partition a simple polygon into convex pieces, include
[`geometry/convex_decomposition.hpp`](convex_decomposition.md). It provides a
fast exact partition with a four-approximation guarantee on the piece count,
and an exact minimum-piece dynamic program.

## Example

```cpp
#include "geometry/polygon.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    m1une::geometry::Polygon<long long> polygon;
    polygon.vertices.emplace_back(0, 0);
    polygon.vertices.emplace_back(2, 0);
    polygon.vertices.emplace_back(0, 2);

    std::cout << m1une::geometry::polygon_area(polygon) << "\n"; // 2
    std::cout << m1une::geometry::contains(polygon, Point(1, 0)) << "\n"; // 1

    m1une::geometry::Segment<long long> path{
        Point(-1, 1),
        Point(3, 1)
    };
    auto parts = m1une::geometry::clip(path, polygon);
    std::cout << parts[0].begin << " " << parts[0].end << "\n"; // 0.25 0.5

    polygon.filled = false;
    std::cout << m1une::geometry::contains(polygon, Point(1, 1)) << "\n"; // 1
}
```
