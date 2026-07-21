---
title: Count Points in Triangle
documentation_of: ../../geometry/count_points_in_triangle.hpp
---

## Overview

`CountPointsInTriangle` preprocesses two integral point sets. Each query chooses
three points from the first set and returns how many points from the second set
lie strictly inside their triangle.

Queries take constant time after preprocessing, making the structure useful
when the same candidate vertices are used for many triangles. Counted points on
an edge or vertex are excluded.

## Interface

```cpp
template <std::integral T>
class CountPointsInTriangle {
public:
    CountPointsInTriangle(
        const std::vector<Point<T>>& triangle_vertices,
        const std::vector<Point<T>>& counted_points
    );

    int query(int first, int second, int third) const;
};
```

| Member | Description | Complexity |
| --- | --- | --- |
| `CountPointsInTriangle(triangle_vertices, counted_points)` | Precomputes the counts needed by every triangle. Neither input is mutated. | $O(N(N+M)\log(N+M))$ time and $O(N^2+N+M)$ memory |
| `query(first, second, third)` | Counts points strictly inside the triangle formed by the three indexed vertices. | $O(1)$ |

Here, $N$ is the number of `triangle_vertices` and $M$ is the number of
`counted_points`.

## Behavior and Requirements

* `T` must be an integral coordinate type.
* Query indices are zero-based and must refer to `triangle_vertices`.
* The order of the three query indices does not matter.
* A query with repeated or collinear triangle vertices returns `0`.
* Duplicate counted points are counted with multiplicity. Duplicate triangle
  vertices are also allowed.
* The triangle boundary is excluded exactly; no floating-point tolerance is
  used.
* Coordinate differences and products used by orientation tests must fit
  signed `__int128`.

## Algorithm

For every candidate vertex, the constructor performs an angular sweep of the
other candidate vertices and counted points above it. A Fenwick tree records
how many counted points lie strictly to one side of each upward edge and how
many lie on the edge. Counts on the same horizontal line are stored separately.

A query orders its three vertices by y-coordinate and expresses the open
triangle as a signed combination of these precomputed edge regions. Separate
strict and collinear counts ensure that every boundary point is excluded.

## Example

```cpp
#include "geometry/count_points_in_triangle.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;

    std::vector<Point> vertices;
    vertices.emplace_back(0, 0);
    vertices.emplace_back(4, 0);
    vertices.emplace_back(0, 4);

    std::vector<Point> points;
    points.emplace_back(1, 1);
    points.emplace_back(2, 1);
    points.emplace_back(0, 1);  // Boundary: excluded.
    points.emplace_back(4, 4);
    points.emplace_back(1, 1);  // Duplicate: counted again.

    m1une::geometry::CountPointsInTriangle<long long> counter(
        vertices,
        points
    );
    std::cout << counter.query(0, 1, 2) << "\n";  // 3
}
```
