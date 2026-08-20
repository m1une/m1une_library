---
title: Circles
documentation_of: ../../geometry/circle.hpp
---

## Overview

This header represents both a filled circular region and its circumference.
It provides constant-time containment, intersections, closest points,
distances, triangle-circle construction, tangents, reflection, and overlap
areas.

`Circle<T>` stores a center, a nonnegative radius, and a set-semantics flag:

```cpp
template <Coordinate T>
struct Circle {
    Point<T> center;
    T radius;
    bool filled = true;
};
```

When `filled` is `true`, the object is the closed disk. When it is `false`, the
object is only the circumference. General set operations such as `contains`,
`intersects`, `closest_points`, and `distance` honor the flag. Explicitly named
boundary operations such as `on_circle` and `circle_segment_intersections`
always use the circumference. Explicit area operations always use the enclosed
region, independent of the flag.

`PointInCircle` classifies a point against that enclosed region as `Outside`,
`Boundary`, or `Inside`; it is also independent of `filled`.

Functions may use different coordinate types for different arguments. All
constructed coordinates and all measurements return `long double`.

`CircleRelation` classifies the two circumferences:

* `Separate`
* `ExternallyTangent`
* `Intersecting`
* `InternallyTangent`
* `Contained`
* `Coincident`

`Contained` means that the smaller circumference is strictly inside the larger
disk. It does not record which input circle is smaller.

## Public interface

The following signatures omit the repeated default `eps = 1e-12L` where it is
clear from the table.

```cpp
template <Coordinate T>
constexpr Point<long double> centroid(const Circle<T>& circle);

template <Coordinate T>
constexpr long double circle_circumference(const Circle<T>& circle);

template <Coordinate T>
constexpr long double circle_area(const Circle<T>& circle);

template <Coordinate C, Coordinate P>
PointInCircle point_in_circle(
    const Circle<C>& circle,
    const Point<P>& point,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate P>
bool contains(
    const Circle<C>& circle,
    const Point<P>& point,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate P>
bool on_circle(
    const Circle<C>& circle,
    const Point<P>& point,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate P>
bool intersects(
    const Circle<C>& circle,
    const Point<P>& point,
    long double eps = 1e-12L
);

template <Coordinate P, Coordinate C>
bool intersects(
    const Point<P>& point,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate A, Coordinate B>
Circle<long double> circle_from_diameter(
    const Point<A>& first,
    const Point<B>& second
);

template <Coordinate T>
std::optional<Circle<long double>> incircle(
    const Point<T>& first,
    const Point<T>& second,
    const Point<T>& third,
    long double eps = 1e-12L
);

template <Coordinate T>
std::optional<Circle<long double>> circumcircle(
    const Point<T>& first,
    const Point<T>& second,
    const Point<T>& third,
    long double eps = 1e-12L
);

template <Coordinate A, Coordinate B>
CircleRelation circle_relation(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate L>
std::vector<Point<long double>> circle_line_intersections(
    const Circle<C>& circle,
    const Line<L>& line,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate L>
std::vector<Point<long double>> circle_line_intersections(
    const Line<L>& line,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate R>
std::vector<Point<long double>> circle_ray_intersections(
    const Circle<C>& circle,
    const Ray<R>& ray,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate R>
std::vector<Point<long double>> circle_ray_intersections(
    const Ray<R>& ray,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate S>
std::vector<Point<long double>> circle_segment_intersections(
    const Circle<C>& circle,
    const Segment<S>& segment,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate S>
std::vector<Point<long double>> circle_segment_intersections(
    const Segment<S>& segment,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate A, Coordinate B>
std::vector<Point<long double>> circle_intersections(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate R>
std::optional<Point<long double>> first_circle_ray_intersection(
    const Circle<C>& circle,
    const Ray<R>& ray,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate L>
bool intersects(
    const Circle<C>& circle,
    const Line<L>& line,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate L>
bool intersects(
    const Line<L>& line,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate R>
bool intersects(
    const Circle<C>& circle,
    const Ray<R>& ray,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate R>
bool intersects(
    const Ray<R>& ray,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate S>
bool intersects(
    const Circle<C>& circle,
    const Segment<S>& segment,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate S>
bool intersects(
    const Segment<S>& segment,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate A, Coordinate B>
bool intersects(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
);

template <Coordinate R, Coordinate H, Coordinate C>
Ray<long double> reflected_ray(
    const Ray<R>& incoming,
    const Point<H>& hit,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate P>
std::vector<Point<long double>> tangent_points(
    const Circle<C>& circle,
    const Point<P>& point,
    long double eps = 1e-12L
);

template <Coordinate A, Coordinate B>
std::vector<Line<long double>> common_tangents(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
);

template <Coordinate A, Coordinate B>
std::vector<Point<long double>> common_tangent_points(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
);

template <Coordinate A, Coordinate B>
long double circle_circle_intersection_area(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate P>
long double circle_polygon_intersection_area(
    const Circle<C>& circle,
    const std::vector<Point<P>>& polygon,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate P>
ClosestPoints closest_points(
    const Circle<C>& circle,
    const Point<P>& point,
    long double eps = 1e-12L
);
template <Coordinate P, Coordinate C>
ClosestPoints closest_points(
    const Point<P>& point,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate L>
ClosestPoints closest_points(
    const Circle<C>& circle,
    const Line<L>& line,
    long double eps = 1e-12L
);
template <Coordinate L, Coordinate C>
ClosestPoints closest_points(
    const Line<L>& line,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate S>
ClosestPoints closest_points(
    const Circle<C>& circle,
    const Segment<S>& segment,
    long double eps = 1e-12L
);
template <Coordinate S, Coordinate C>
ClosestPoints closest_points(
    const Segment<S>& segment,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate R>
ClosestPoints closest_points(
    const Circle<C>& circle,
    const Ray<R>& ray,
    long double eps = 1e-12L
);
template <Coordinate R, Coordinate C>
ClosestPoints closest_points(
    const Ray<R>& ray,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate A, Coordinate B>
ClosestPoints closest_points(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate P>
long double distance(const Circle<C>& circle, const Point<P>& point);
template <Coordinate P, Coordinate C>
long double distance(const Point<P>& point, const Circle<C>& circle);
template <Coordinate C, Coordinate L>
long double distance(const Circle<C>& circle, const Line<L>& line);
template <Coordinate L, Coordinate C>
long double distance(const Line<L>& line, const Circle<C>& circle);
template <Coordinate C, Coordinate S>
long double distance(const Circle<C>& circle, const Segment<S>& segment);
template <Coordinate S, Coordinate C>
long double distance(const Segment<S>& segment, const Circle<C>& circle);
template <Coordinate C, Coordinate R>
long double distance(const Circle<C>& circle, const Ray<R>& ray);
template <Coordinate R, Coordinate C>
long double distance(const Ray<R>& ray, const Circle<C>& circle);
template <Coordinate A, Coordinate B>
long double distance(const Circle<A>& first, const Circle<B>& second);
```

The linear intersection, `closest_points`, and `distance` overloads support
both argument orders. Reversing a closest-point query returns the same
witnesses in reversed fields.

## Complexity and behavior

| Function | Behavior | Complexity |
| --- | --- | --- |
| `centroid(circle)` | Returns the center of the circumference. | $O(1)$ |
| `circle_circumference(circle)` | Returns the circumference length. | $O(1)$ |
| `circle_area(circle)` | Returns the enclosed area, regardless of `filled`. | $O(1)$ |
| `point_in_circle(circle, point, eps)` | Classifies the point against the enclosed region, regardless of `filled`. | $O(1)$ |
| `contains(circle, point, eps)` | Tests membership in the set selected by `filled`. | $O(1)$ |
| `on_circle(circle, point, eps)` | Tests whether the point is on the circumference. | $O(1)$ |
| `circle_from_diameter(first, second)` | Constructs the circle having the two points as opposite diameter endpoints. Equal points produce a zero-radius circle. | $O(1)$ |
| `incircle(first, second, third, eps)` | Constructs the triangle's incircle, or returns `nullopt` for collinear points. | $O(1)$ |
| `circumcircle(first, second, third, eps)` | Constructs the triangle's circumcircle, or returns `nullopt` for collinear points. | $O(1)$ |
| `circle_relation(first, second, eps)` | Classifies two circumferences. | $O(1)$ |
| `circle_line_intersections(circle, line, eps)` | Returns zero, one, or two circumference intersections in lexicographic order. | $O(1)$ |
| `circle_ray_intersections(circle, ray, eps)` | Returns circumference intersections ordered from the ray origin. | $O(1)$ |
| `circle_segment_intersections(circle, segment, eps)` | Returns circumference intersections ordered from `segment.a` to `segment.b`. A point segment is accepted. | $O(1)$ |
| `circle_intersections(first, second, eps)` | Returns zero, one, or two circumference intersections in lexicographic order. | $O(1)$ |
| `first_circle_ray_intersection(circle, ray, eps)` | Returns the first forward circumference intersection, or `nullopt`. | $O(1)$ |
| `intersects(circle, object, eps)` | Tests whether the sets selected by `filled` intersect. | $O(1)$ |
| `reflected_ray(incoming, hit, circle, eps)` | Reflects the incoming direction across the tangent at `hit`. | $O(1)$ |
| `tangent_points(circle, point, eps)` | Returns the contact points of tangents through the point in lexicographic order. | $O(1)$ |
| `common_tangents(first, second, eps)` | Returns all distinct finite common tangent lines. | $O(1)$ |
| `common_tangent_points(first, second, eps)` | Returns the distinct contact points on `first`, in lexicographic order. | $O(1)$ |
| `circle_circle_intersection_area(first, second, eps)` | Returns the common enclosed area, regardless of either flag. | $O(1)$ |
| `circle_polygon_intersection_area(circle, polygon, eps)` | Returns the common enclosed area of the circle and polygon boundary. | $O(N)$ |
| `closest_points(circle, object, eps)` | Returns witnesses minimizing distance between the sets selected by `filled`. | $O(1)$ |
| `distance(circle, object)` | Returns the distance between the corresponding closest-point witnesses. | $O(1)$ |

With `filled == true`, a segment strictly inside the circle intersects it and
has distance zero. With `filled == false`, that segment does not intersect the
circle and its distance is measured to the circumference. Likewise, nested
unfilled circles are disjoint, while nested filled circles intersect.

Coincident circles have infinitely many circumference intersections and common
tangents, so `circle_intersections` and `common_tangents` return empty vectors.
Concentric circles with different radii have no common tangent. A zero-radius
circle is accepted: `tangent_points` returns its center as the only distinct
contact point.

`common_tangents` represents each line by a contact point on `first` and a
second point one unit along the tangent direction. This keeps the `Line`
nondegenerate even when internally tangent circles share their contact point.

For two integral circles, `circle_relation` uses exact signed 128-bit squared
comparisons, and integral `on_circle` queries are exact. As with the rest of
the integral geometry module, intermediate expressions must fit signed 128-bit
arithmetic. Other comparisons use `eps` as an absolute distance tolerance.

## Example

```cpp
#include "geometry/circle.hpp"

#include <iostream>

int main() {
    using namespace m1une::geometry;

    Circle<long long> region{Point<long long>(0, 0), 5};
    Circle<long long> boundary{Point<long long>(0, 0), 5, false};

    auto contacts = tangent_points(boundary, Point<long long>(13, 0));
    std::cout << contacts.size() << "\n"; // 2

    Segment<long long> segment;
    segment.a = Point<long long>(-10, 0);
    segment.b = Point<long long>(10, 0);
    auto crossings = circle_segment_intersections(region, segment);
    std::cout << crossings[0].x << " " << crossings[1].x << "\n"; // -5 5
    std::cout << intersects(region, Point<long long>(0, 0)) << "\n"; // 1
    std::cout << intersects(boundary, Point<long long>(0, 0)) << "\n"; // 0
}
```
