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
boundary operations such as `on_circle` and `circle_boundary_intersection`
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

Boundary intersections return fixed-size structured results instead of raw
point vectors. Each contact includes its Cartesian point and its argument on
the circle. Circle-circle results additionally describe the counterclockwise
part of each circumference inside the other circle's enclosure.

```cpp
enum class AngularCoverageKind { Empty, Point, Arc, Full };

struct AngularCoverage {
    AngularCoverageKind kind;
    long double begin;
    long double end;
};

struct CircleContact {
    Point<long double> point;
    long double first_argument;
    long double second_argument;
};

enum class CircleContactKind { Empty, Point, TwoPoints, Coincident };

struct CircleCircleIntersection {
    CircleRelation relation;
    CircleContactKind contact_kind;
    std::array<CircleContact, 2> contacts;
    AngularCoverage first_inside_second;
    AngularCoverage second_inside_first;

    constexpr int contact_count() const noexcept;
};

struct CircleLinearContact {
    Point<long double> point;
    long double circle_argument;
    long double linear_parameter;
};

struct CircleLinearIntersection {
    int contact_count;
    std::array<CircleLinearContact, 2> contacts;
};
```

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

long double normalize_circle_argument(long double argument);

template <Coordinate T>
Point<long double> circle_point_at(
    const Circle<T>& circle,
    long double argument
);

template <Coordinate C, Coordinate P>
long double circle_argument(
    const Circle<C>& circle,
    const Point<P>& point
);

long double angular_measure(const AngularCoverage& coverage);

template <Coordinate T>
long double circle_arc_length(
    const Circle<T>& circle,
    const AngularCoverage& coverage
);

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
CircleLinearIntersection circle_boundary_intersection(
    const Circle<C>& circle,
    const Line<L>& line,
    long double eps = 1e-12L
);

template <Coordinate L, Coordinate C>
CircleLinearIntersection circle_boundary_intersection(
    const Line<L>& line,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate R>
CircleLinearIntersection circle_boundary_intersection(
    const Circle<C>& circle,
    const Ray<R>& ray,
    long double eps = 1e-12L
);

template <Coordinate R, Coordinate C>
CircleLinearIntersection circle_boundary_intersection(
    const Ray<R>& ray,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate C, Coordinate S>
CircleLinearIntersection circle_boundary_intersection(
    const Circle<C>& circle,
    const Segment<S>& segment,
    long double eps = 1e-12L
);

template <Coordinate S, Coordinate C>
CircleLinearIntersection circle_boundary_intersection(
    const Segment<S>& segment,
    const Circle<C>& circle,
    long double eps = 1e-12L
);

template <Coordinate A, Coordinate B>
CircleCircleIntersection circle_boundary_intersection(
    const Circle<A>& first,
    const Circle<B>& second,
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
| `normalize_circle_argument(argument)` | Normalizes an angle into $[0, 2\pi)$. | $O(1)$ |
| `circle_point_at(circle, argument)` | Evaluates the circumference parameterization. | $O(1)$ |
| `circle_argument(circle, point)` | Returns the normalized polar argument of `point` relative to the center. The center maps to zero. | $O(1)$ |
| `angular_measure(coverage)` | Returns zero, `end - begin`, or $2\pi$ according to the coverage kind. | $O(1)$ |
| `circle_arc_length(circle, coverage)` | Returns radius times angular measure. | $O(1)$ |
| `point_in_circle(circle, point, eps)` | Classifies the point against the enclosed region, regardless of `filled`. | $O(1)$ |
| `contains(circle, point, eps)` | Tests membership in the set selected by `filled`. | $O(1)$ |
| `on_circle(circle, point, eps)` | Tests whether the point is on the circumference. | $O(1)$ |
| `circle_from_diameter(first, second)` | Constructs the circle having the two points as opposite diameter endpoints. Equal points produce a zero-radius circle. | $O(1)$ |
| `incircle(first, second, third, eps)` | Constructs the triangle's incircle, or returns `nullopt` for collinear points. | $O(1)$ |
| `circumcircle(first, second, third, eps)` | Constructs the triangle's circumcircle, or returns `nullopt` for collinear points. | $O(1)$ |
| `circle_relation(first, second, eps)` | Classifies two circumferences. | $O(1)$ |
| `circle_boundary_intersection(circle, line/ray/segment, eps)` | Returns parameterized contacts ordered by the linear parameter. A point segment is accepted. | $O(1)$ |
| `circle_boundary_intersection(first, second, eps)` | Returns the relation, parameterized contacts, and directed boundary coverage for both circles. | $O(1)$ |
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

For `AngularCoverageKind::Arc`, `begin` is normalized into $[0,2\pi)$ and
`end` is unwrapped into $(begin, begin+2\pi)$. Thus `end - begin` directly
gives the counterclockwise angle. `Full` always has range $[0,2\pi]`, while
`Point` has `begin == end`. For proper circle crossings, `contacts[0]` and
`contacts[1]` are respectively the endpoints of `first_inside_second`.
The second circle's inside arc runs from `contacts[1]` to `contacts[0]`.

For a line or segment, `linear_parameter` satisfies
`point = a + (b - a) * linear_parameter`. For a ray, replace `a` and `b` with
`origin` and `through`. Line contacts are ordered by this parameter; ray
parameters are nonnegative and segment parameters lie in $[0,1]$.

Coincident positive-radius circles use `CircleContactKind::Coincident` because
their finite contacts cannot be enumerated, and both coverage values are
`Full`. Coincident zero-radius circles instead return their single geometric
point. Concentric circles with different radii have no common tangent. A
zero-radius circle is otherwise accepted throughout the API.

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

    Circle<long long> other{Point<long long>(6, 0), 5};
    auto crossing = circle_boundary_intersection(boundary, other);
    auto arc = crossing.first_inside_second;
    std::cout << circle_arc_length(boundary, arc) << "\n";

    Segment<long long> segment;
    segment.a = Point<long long>(-10, 0);
    segment.b = Point<long long>(10, 0);
    auto contacts_on_segment =
        circle_boundary_intersection(region, segment);
    std::cout << contacts_on_segment.contacts[0].linear_parameter << "\n";
    std::cout << intersects(region, Point<long long>(0, 0)) << "\n"; // 1
    std::cout << intersects(boundary, Point<long long>(0, 0)) << "\n"; // 0
}
```
