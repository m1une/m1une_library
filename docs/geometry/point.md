---
title: 2D Point and Predicates
documentation_of: ../../geometry/point.hpp
---

## Overview

`Point<T>` is the base type for the 2D geometry library. It provides vector
arithmetic, lexicographic comparison, dot and cross products, distances,
orientation, rotation, normalization, and its trivial centroid.

For integral coordinates, dot products, cross products, squared norms, and
orientation calculations use signed 128-bit arithmetic. For floating-point
coordinates, predicates use `long double` and accept a scale-aware epsilon.

`Coordinate<T>` also accepts exact numeric classes such as
[`math::Rational`](../math/rational.md), including `Rational<utilities::BigInt>`.
A custom coordinate type must be copyable, totally ordered, constructible from
`0` and `1`, support unary signs and closed `+`, `-`, `*`, `/`, `+=`, and `-=`,
and provide an explicit conversion to `long double`. Its arithmetic and ordering
must be exact. `bool` is excluded.

`ExactCoordinate<T>` means `Coordinate<T> && !std::floating_point<T>`.
`wide_type<T>` is `__int128_t` for built-in integers, `long double` for built-in
floating-point types, and `T` for custom exact types. Rational dot products,
cross products, squared distances, and predicates therefore stay rational.
Exact predicates ignore `eps`.

Inputs and intermediate results must fit the chosen arithmetic type. For
`Rational<long long>`, every normalized intermediate fraction must fit its
underlying integer type; use `Rational<BigInt>` when that is insufficient.
Complexities below count scalar operations as constant time. Rational operations
add the arithmetic and gcd costs described on the rational documentation page.

## Point

```cpp
template <Coordinate T>
struct Point {
    T x;
    T y;
};
```

`Point` supports equality, lexicographic `<`, unary signs, addition,
subtraction, scalar multiplication, and scalar division. Scalar operations
return `Point<std::common_type_t<T, Scalar>>`. Integer or rational scalars keep
rational coordinates exact; a floating-point scalar mixed with rational
coordinates produces `Point<long double>`.

Conversions to other point types are explicit. Functions whose signatures return
`long double` or `Point<long double>` still return approximations with rational
input, including distances, projections, intersection coordinates, rotation,
normalization, centroids, and division points.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `int sign(wide_type<T> value, long double eps = 1e-12L)` | Returns the scalar sign; exact types ignore `eps`. | $O(1)$ |
| `Point<long double> centroid(const Point<T>& point)` | Returns the point itself as `Point<long double>`. | $O(1)$ |
| `wide_type<T> dot(const Point<T>& a, const Point<T>& b)` | Dot product. | $O(1)$ |
| `wide_type<T> cross(const Point<T>& a, const Point<T>& b)` | Cross product of two vectors. | $O(1)$ |
| `wide_type<T> cross(const Point<T>& origin, const Point<T>& a, const Point<T>& b)` | Cross product of vectors `a - origin` and `b - origin`. | $O(1)$ |
| `wide_type<T> norm2(const Point<T>& point)` | Squared Euclidean norm. | $O(1)$ |
| `wide_type<T> distance2(const Point<T>& a, const Point<T>& b)` | Squared Euclidean distance. | $O(1)$ |
| `long double norm(const Point<T>& point)` | Euclidean norm as `long double`. | $O(1)$ |
| `long double distance(const Point<T>& a, const Point<T>& b)` | Euclidean distance as `long double`. | $O(1)$ |
| `Point<long double> internal_division_point(const Point<T>& a, const Point<T>& b, M m, N n)` | Returns the point internally dividing `AB` in ratio `AP:PB = m:n`. | $O(1)$ |
| `Point<long double> external_division_point(const Point<T>& a, const Point<T>& b, M m, N n)` | Returns the point externally dividing `AB` in ratio `AP:PB = m:n`. | $O(1)$ |
| `int orientation(const Point<T>& a, const Point<T>& b, const Point<T>& c, long double eps = 1e-12L)` | Returns `1` for counterclockwise, `-1` for clockwise, and `0` for collinear. | $O(1)$ |
| `bool collinear(const Point<T>& a, const Point<T>& b, const Point<T>& c, long double eps = 1e-12L)` | Returns whether three points are collinear. | $O(1)$ |
| `Point<long double> rotate(const Point<T>& point, long double angle)` | Rotates `p` counterclockwise by radians. | $O(1)$ |
| `Point<long double> normalized(const Point<T>& point)` | Returns a unit vector in `p`'s direction. | $O(1)$ |

`normalized` requires a nonzero vector.

## Floating-point tolerance

For floating-point `orientation` and `collinear`, `eps` is a dimensionless
relative tolerance. If `u = b - a`, `v = c - a`, and
`s(w) = max(abs(w.x), abs(w.y))`, their determinant is treated as zero when

$$
|u_xv_y-u_yv_x|
\leq \mathtt{eps}\,s(u)\max(s(u),s(v)).
$$

Consequently, uniformly scaling all coordinates does not change the result.
The `s(u)^2` floor also absorbs roundoff near either endpoint of the directed
baseline `a`--`b`.
Passing `eps = 0` requests a strict comparison of the computed `long double`
determinant. Integral and custom exact predicates ignore `eps`.

The lower-level `sign(value, eps)` function retains absolute-tolerance
semantics because it has no operands from which to derive a scale.

## Internal and external division

For `internal_division_point(a, b, m, n)`, the returned point $P$ satisfies
$AP:PB=m:n$ and is computed as

$$
P = A + \frac{m}{m+n}(B-A).
$$

For positive `m` and `n`, `P` lies between `a` and `b`. The function requires
`m + n != 0`.

`external_division_point` uses the same ratio convention:

$$
P = A + \frac{m}{m-n}(B-A).
$$

For positive unequal ratios, the point lies outside the segment. It is beyond
`b` when `m > n` and beyond `a` when `m < n`. The function requires
`m != n`. Both functions return `Point<long double>`.

## Example

```cpp
#include "geometry/point.hpp"

#include <iostream>

int main() {
    using Point = m1une::geometry::Point<long long>;
    Point a(0, 0);
    Point b(3, 0);
    Point c(1, 2);

    std::cout << m1une::geometry::orientation(a, b, c) << "\n"; // 1
    std::cout << m1une::geometry::cross(a, b, c) << "\n";       // 6
}
```

## Rational coordinates

```cpp
#include "geometry/convex_hull.hpp"
#include "math/rational.hpp"

using Fraction = m1une::math::Rational<>;
using Point = m1une::geometry::Point<Fraction>;

Point a(0, 0);
Point b(Fraction(1, 2), 0);
Point c(0, Fraction(1, 3));
auto twice_b = b * 2;                    // Point<Fraction>(1, 0)
auto area2 = m1une::geometry::cross(a, b, c); // Fraction(1, 6)
auto hull = m1une::geometry::convex_hull(std::vector<Point>{a, b, c});
```

## Points with metadata

Use `PointWithData<T, Data>` to attach an index, color, or any other payload.
It publicly derives from `Point<T>` and adds a public `Data data` member.
`Point<T>` itself keeps its original layout and behavior. Both expose
`using coordinate_type = T`.

```cpp
#include "geometry/convex_hull.hpp"
#include <string>
#include <vector>

struct Info {
    int index;
    std::string color;
};

using Vertex = m1une::geometry::PointWithData<long long, Info>;
std::vector<Vertex> vertices;
vertices.emplace_back(0, 0, Info{4, "red"});
vertices.emplace_back(2, 0, Info{7, "blue"});
vertices.emplace_back(0, 2, Info{9, "green"});
auto hull = m1une::geometry::convex_hull(vertices); // vector<Vertex>
int original_index = hull[0].data.index;           // 4
```

`PointRecord<P>` accepts `Point<T>` and public, unambiguous subclasses of
`Point<T>` with the inherited `coordinate_type`. You can instead define your
own record with directly accessible fields:

```cpp
struct Vertex : m1une::geometry::Point<long long> {
    int index;
    int color;
    Vertex(long long x, long long y, int index, int color)
        : Point(x, y), index(index), color(color) {}
};
```

Do not hide the base's coordinates or change its `coordinate_type`. Metadata
needs no equality, ordering, or arithmetic operations. Algorithms that return
or reorder records require copyable records. Read-only queries do not copy the
payload. Payloads do not need default constructors when supplied explicitly.

| Interface | Behavior | Complexity |
| --- | --- | --- |
| `PointWithData<T, Data>()` | Zero coordinates and value-initialized data; requires default-initializable `Data`. | $O(1)$ coordinate work plus data initialization |
| `PointWithData<T, Data>(T x, T y)` | Coordinates and value-initialized data; requires default-initializable `Data`. | $O(1)$ coordinate work plus data initialization |
| `PointWithData<T, Data>(T x, T y, Data value)` | Coordinates and the supplied data. | $O(1)$ coordinate work plus data construction |
| `PointWithData<T, Data>(Point<T> point, Data value)` | Copies the coordinates and takes the supplied data. | $O(1)$ coordinate work plus data construction |
| `template <PointRecord P> std::vector<Point<typename P::coordinate_type>> to_points(const std::vector<P>& records)` | Explicitly copies only coordinates, preserving input order. Does not mutate the records. | $O(N)$ time and memory |

Equality and ordering inherited from `Point<T>` compare coordinates only.
Single-point predicates such as `dot`, `cross`, `orientation`, and `distance2`
accept these records through their base type. Arithmetic, coordinate
conversions, rotations, centroids, and other constructions of new points return
ordinary `Point` values: no metadata is assigned to a synthesized point.
In-place `+=` and `-=` update coordinates and retain the existing data.

These collection APIs also accept `std::vector<P>` with `PointRecord<P>`:

| APIs | Metadata behavior |
| --- | --- |
| `convex_hull` | Returns `std::vector<P>` with complete input records. Duplicate coordinates retain the first input record. |
| `sort_by_angle`, `angle_sorted` | Reorder complete records. Geometrically tied records can appear in either order. |
| `normalize_convex_polygon` | Retains records for surviving vertices; consecutive duplicate coordinates retain the first record. |
| `closest_pair`, `farthest_pair`, `furthest_pair`, `convex_layers` | Results refer to positions in the original vector, independently of metadata indices. |
| `manhattan_mst_edges`, `manhattan_mst`, `euclidean_mst_edges`, `euclidean_mst`, `delaunay_triangulation`, `minimum_enclosing_circle` | Edge, triangle, and support indices refer to the original vector. Existing coordinate restrictions still apply. |
| `polygon_area2`, `polygon_area`, `polygon_centroid`, `centroid`, `polygon_center_of_gravity`, `is_simple_polygon`, `point_in_polygon`, `is_convex_polygon`, `point_in_convex_polygon`, `convex_diameter2` | Use coordinates only and keep their original result types and complexities. |

Algorithms use the coordinate base for geometric comparisons even when a custom
record defines its own comparison operators. Costs retain the bounds documented
on each algorithm's page, plus the cost of copying or moving records where
applicable. Use small payloads or store an index into an external table for
large metadata.

Existing `Point<T>` calls, including explicit coordinate template arguments such
as `convex_hull<long long>(points)`, remain supported. Other collection APIs,
including polygon decomposition, Minkowski sums, and Voronoi diagrams, take
ordinary points; pass `to_points(records)` explicitly when using those APIs.
