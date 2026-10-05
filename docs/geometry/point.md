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
