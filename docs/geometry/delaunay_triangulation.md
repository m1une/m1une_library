---
title: Delaunay Triangulation
documentation_of: ../../geometry/delaunay_triangulation.hpp
---

## Overview

`delaunay_triangulation` constructs one Delaunay triangulation of distinct
two-dimensional integral points. It returns both the undirected edges and the
counterclockwise triangular faces, using the original zero-based point indices.

The implementation uses divide and conquer. All topological decisions are made
with exact integral orientation and incircle predicates.

## Type

```cpp
struct DelaunayTriangulation {
    std::vector<std::pair<int, int>> edges;
    std::vector<std::array<int, 3>> triangles;
};
```

Every edge is stored as `(first, second)` with `first < second`, and `edges` is
lexicographically sorted without duplicates.

Every triangle is counterclockwise. Its smallest vertex index is stored first,
and `triangles` is lexicographically sorted without duplicates. Every side of a
triangle appears in `edges`.

## Function

The exact signature is:

```cpp
template <std::integral T>
DelaunayTriangulation delaunay_triangulation(
    const std::vector<Point<T>>& points
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `delaunay_triangulation(points)` | Returns one Delaunay triangulation of the indexed points. | $O(N\log N)$ time and $O(N)$ memory |

The input points must be pairwise distinct. Empty and one-point inputs have no
edges or triangles. Two points produce one edge. A larger collinear input has
no triangles and connects consecutive points in lexicographic order.

When four or more points are cocircular, the Delaunay triangulation is not
unique. The function returns one valid choice of diagonals; callers should not
depend on which valid choice is selected.

The degree-four incircle expressions must fit in signed 128-bit arithmetic.
This is satisfied by the coordinate constraints of Library Checker's Euclidean
MST problem.

## Example

```cpp
#include "geometry/delaunay_triangulation.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(4, 0);
    points.emplace_back(0, 3);
    points.emplace_back(1, 1);

    auto triangulation =
        m1une::geometry::delaunay_triangulation(points);
    for (const auto& triangle : triangulation.triangles) {
        std::cout << triangle[0] << ' '
                  << triangle[1] << ' '
                  << triangle[2] << '\n';
    }
}
```
