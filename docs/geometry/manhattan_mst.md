---
title: Manhattan Minimum Spanning Tree
documentation_of: ../../geometry/manhattan_mst.hpp
---

## Overview

`T` may be a built-in integer or an exact coordinate class such as
`math::Rational<long long>` or `math::Rational<utilities::BigInt>`.
Rational intermediate arithmetic uses `T` without floating-point conversion.
All intermediate fractions must be representable. Listed complexities count
scalar operations; rational arithmetic adds its gcd and integer arithmetic costs.

This header constructs a minimum spanning tree of two-dimensional exact-coordinate
points under Manhattan distance:

$$
d(i,j)=|x_i-x_j|+|y_i-y_j|.
$$

It uses four coordinate sweeps to generate only $O(N)$ candidate edges, then
applies Kruskal's algorithm.

## Types

```cpp
template <class T>
struct ManhattanMstEdge {
    int from;
    int to;
    T cost;
};

template <class T>
struct ManhattanMst {
    T cost;
    std::vector<ManhattanMstEdge<T>> edges;
};
```

For integral input coordinates, the result uses `wide_type<T>`, which is
`__int128_t`. This prevents overflow during coordinate transformations and
distance calculations when the input type is a standard integer type.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `manhattan_mst_edges(points)` | Returns $O(N)$ candidate edges containing at least one Manhattan MST. | $O(N\log N)$ |
| `manhattan_mst(points)` | Returns the MST cost and its selected edges. | $O(N\log N)$ |

Vertices are identified by their indices in `points`. Duplicate points are
supported and may be joined by zero-cost edges. For zero or one point, the
result has cost zero and no edges.

## Example

```cpp
#include "geometry/manhattan_mst.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(2, 1);
    points.emplace_back(-1, 3);

    auto mst = m1une::geometry::manhattan_mst(points);
    long long cost = static_cast<long long>(mst.cost);
    std::cout << cost << "\n";
}
```
