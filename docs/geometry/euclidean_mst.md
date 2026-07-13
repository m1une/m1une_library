---
title: Euclidean Minimum Spanning Tree
documentation_of: ../../geometry/euclidean_mst.hpp
---

## Overview

This header constructs a minimum spanning tree of two-dimensional integral
points under Euclidean distance. It first builds a Delaunay triangulation by
divide and conquer, then applies Kruskal's algorithm to its $O(N)$ edges.

Duplicate points are connected to one representative by zero-length edges.
Collinear and cocircular point sets are supported.

## Types

```cpp
template <class T>
struct EuclideanMstEdge {
    int from;
    int to;
    T squared_distance;
};

template <class T>
struct EuclideanMst {
    long double cost;
    std::vector<EuclideanMstEdge<T>> edges;
};
```

For integral input coordinates, `T` in the returned types is `wide_type<T>`,
which is `__int128_t`. Edge selection compares `squared_distance` exactly.
`EuclideanMst::cost` is the sum of the selected Euclidean lengths and is stored
as `long double`.

All orientation, squared-distance, and degree-four incircle expressions must
fit in signed 128-bit arithmetic. This condition holds for the Library Checker
constraints.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `template <std::integral T> std::vector<EuclideanMstEdge<wide_type<T>>> euclidean_mst_edges(const std::vector<Point<T>>& points)` | Returns the $O(N)$ Delaunay and duplicate edges containing a Euclidean MST. | $O(N\log N)$ time and $O(N)$ memory |
| `template <std::integral T> EuclideanMst<wide_type<T>> euclidean_mst(const std::vector<Point<T>>& points)` | Returns the MST length and its selected edges. | $O(N\log N)$ time and $O(N)$ memory |

Vertices are identified by their zero-based indices in `points`. For zero or
one point, the result has cost zero and no edges. For $N$ points with $N>0$,
`euclidean_mst(points).edges` contains exactly $N-1$ edges.

## Example

```cpp
#include "geometry/euclidean_mst.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(3, 0);
    points.emplace_back(0, 4);

    auto mst = m1une::geometry::euclidean_mst(points);
    std::cout << static_cast<double>(mst.cost) << "\n";
    for (const auto& edge : mst.edges) {
        std::cout << edge.from << ' ' << edge.to << "\n";
    }
}
```
