---
title: Half-Plane Intersection
documentation_of: ../../geometry/half_plane_intersection.hpp
---

## Overview

`half_plane_intersection` constructs the bounded convex polygon common to a
collection of closed half-planes. A half-plane is represented by a directed
`Line<T>`: the legal side is the boundary line and everything to its left.

For a line from `a` to `b`, a point `p` is legal exactly when

$$
\operatorname{cross}(b-a,p-a) \geq 0.
$$

The result reports whether the intersection is empty, unbounded, bounded with
zero area, or a bounded positive-area polygon. Polygon vertices use
`long double` because intersections need not have integral coordinates.

## Result

```cpp
enum class HalfPlaneIntersectionStatus {
    Empty,
    Unbounded,
    Degenerate,
    Bounded,
};

struct HalfPlaneIntersectionResult {
    HalfPlaneIntersectionStatus status;
    std::vector<Point<long double>> polygon;
};
```

| Status | Meaning |
| --- | --- |
| `Empty` | No point satisfies every half-plane. |
| `Unbounded` | The intersection is nonempty and unbounded, including an unbounded line or ray. |
| `Degenerate` | The intersection is bounded but has zero area, so it is a point or segment. |
| `Bounded` | The intersection has positive area; `polygon` contains its boundary. |

`polygon` is empty for every status except `Bounded`.

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `half_plane_intersection(half_planes, eps)` | Classifies the intersection and returns its polygon when it is bounded with positive area. | Expected $O(N\log N)$ time, $O(N^2)$ worst-case time, and $O(N)$ memory |

The exact signature is:

```cpp
template <Coordinate T>
HalfPlaneIntersectionResult half_plane_intersection(
    const std::vector<Line<T>>& half_planes,
    long double eps = 1e-12L
);
```

Every boundary line must have distinct endpoints. For `Bounded`, the returned
polygon is counterclockwise, starts at its lexicographically smallest vertex,
and does not repeat that vertex at the end. Closed boundaries are included.
The empty collection of constraints has status `Unbounded` because its
intersection is the entire plane.

Feasibility is checked by randomized incremental two-dimensional linear
programming, which gives the expected time bound above. The tolerance is
applied after boundary directions are normalized, so it acts as both an
angular and a signed-distance tolerance.

## Example

```cpp
#include "geometry/half_plane_intersection.hpp"

#include <iostream>
#include <vector>

int main() {
    using namespace m1une::geometry;
    using P = Point<long double>;

    std::vector<Line<long double>> half_planes;
    half_planes.push_back(Line<long double>{P(0, 0), P(2, 0)});
    half_planes.push_back(Line<long double>{P(2, 0), P(2, 2)});
    half_planes.push_back(Line<long double>{P(2, 2), P(0, 2)});
    half_planes.push_back(Line<long double>{P(0, 2), P(0, 0)});

    auto result = half_plane_intersection(half_planes);
    if (result.status == HalfPlaneIntersectionStatus::Bounded) {
        std::cout << result.polygon.size() << "\n";  // 4
    }
}
```
