---
title: Perpendicular Bisector
documentation_of: ../../geometry/perpendicular_bisector.hpp
---

## Overview

This header constructs the perpendicular bisector of two distinct 2D points.
It returns an infinite `Line<T>` through two points of the same coordinate type
as the input. Floating-point and integral coordinate types are both supported.

For integral coordinates, the returned endpoints are lattice points and all
calculations used to construct them are integral.

## Function

```cpp
template <Coordinate T>
constexpr Line<T> perpendicular_bisector(
    const Point<T>& first,
    const Point<T>& second
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `perpendicular_bisector(first, second)` | Returns the perpendicular bisector using coordinate type `T`. | $O(\log C)$ for integral `T`; $O(1)$ otherwise |

Here $C$ is the magnitude of the coordinate differences. The logarithmic term
comes from computing their greatest common divisor.

The two input points must be distinct. For integral `T`, the bisector must
contain lattice points and two distinct such points must be representable by
`T`. These preconditions are checked with assertions. The lattice-point
condition is exactly

$$
\gcd(2\Delta x,2\Delta y)\mid
x_2^2+y_2^2-x_1^2-y_1^2.
$$

For example, `(0, 0)` and `(1, 0)` do not satisfy the condition because their
bisector is $x=1/2$. Intermediate integral calculations use `wide_type<T>` and
must fit that type. The function does not mutate either input point.

## Example

```cpp
#include "geometry/perpendicular_bisector.hpp"

#include <iostream>

int main() {
    using namespace m1une::geometry;

    Point<long long> first(0, 0);
    Point<long long> second(1, 1);
    Line<long long> bisector = perpendicular_bisector(first, second);

    std::cout << bisector.a.x << ' ' << bisector.a.y << '\n'; // 1 0
    std::cout << bisector.b.x << ' ' << bisector.b.y << '\n'; // 0 1
}
```
