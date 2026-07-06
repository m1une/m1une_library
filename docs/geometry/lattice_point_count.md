---
title: Lattice-Point Count
documentation_of: ../../geometry/lattice_point_count.hpp
---

## Overview

`count_lattice_points` counts the integer grid points in a bounded region
described by closed linear inequalities. Each constraint has the form

$$
a x + b y \leq c,
$$

where all three coefficients are signed integers. The calculation is exact:
rational boundary intersections and points on the boundary do not involve
floating-point tolerances.

The implementation constructs the piecewise-rational lower and upper envelopes
of the constraints. It finds the feasible projection onto the x-axis, then
sums each envelope piece with Euclidean floor-sum. It does not iterate over the
coordinate range.

## Interface

```cpp
template <class T>
struct LinearInequality {
    T a;
    T b;
    T c;
};

template <class T>
__int128_t count_lattice_points(
    const std::vector<LinearInequality<T>>& inequalities
);
```

| Member / Function | Description | Complexity |
| --- | --- | --- |
| `LinearInequality<T>{a, b, c}` | Represents the closed constraint $ax+by\leq c$. | $O(1)$ |
| `count_lattice_points(inequalities)` | Returns the number of integer pairs satisfying every constraint. | $O(N\log N+N\log C)$ time and $O(N)$ memory |

Here $N$ is `inequalities.size()`, and $C$ is the magnitude of the coefficients
and feasible coordinates. The logarithmic factor after envelope construction
comes from floor-sum.

`T` must be a signed integer type of at most 64 bits. The real feasible region
must be bounded, even when it is empty, a point, or a segment. In particular,
a bounded nonempty region has both a lower and an upper y-envelope. The integer
x-coordinates in its projection must fit `long long`, and the returned count
must fit signed `__int128`. These conditions are checked by assertions where
possible.

All inequalities are closed, so boundary grid points are included. A
constraint with `a == 0` and `b == 0` is either redundant when `c >= 0` or
makes the result zero when `c < 0`. The function does not mutate its input.

## Example

```cpp
#include "geometry/lattice_point_count.hpp"

#include <iostream>
#include <vector>

int main() {
    using m1une::geometry::LinearInequality;
    using m1une::geometry::count_lattice_points;

    // x >= 0, y >= 0, and x + y <= 2.
    std::vector<LinearInequality<long long>> constraints;
    constraints.push_back(LinearInequality<long long>{-1, 0, 0});
    constraints.push_back(LinearInequality<long long>{0, -1, 0});
    constraints.push_back(LinearInequality<long long>{1, 1, 2});

    long long answer = static_cast<long long>(
        count_lattice_points(constraints)
    );
    std::cout << answer << "\n";  // 6
}
```
