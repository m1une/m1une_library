---
title: Convex Layers
documentation_of: ../../geometry/convex_layers.hpp
---

## Overview

`convex_layers` computes the onion decomposition of a point set. Layer `1`
contains every point on the boundary of the original convex hull. After removing
that boundary, layer `2` contains the next convex-hull boundary, and so on until
no points remain.

The implementation maintains both sides of the convex hull under deletions with
segment-tree-shaped bridge structures. This is substantially faster than
rebuilding a convex hull for every layer when the input has many nested layers.

## Function

```cpp
template <Coordinate T>
std::vector<int> convex_layers(const std::vector<Point<T>>& points);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `convex_layers(points)` | Returns the 1-based removal layer of every point in original input order. Does not mutate `points`. | $O(N\log^2 N)$ time and $O(N)$ memory. |

All collinear points on a hull edge belong to the same layer. An empty input
returns an empty vector. Duplicate coordinates are allowed and receive the same
layer.

Integral calculations use `wide_type<T>`, which is signed 128-bit arithmetic.
Coordinate differences, cross products, and the bridge-comparison intermediate
products must fit that type. Floating-point coordinates use the geometry
module's default orientation tolerance.

## Example

```cpp
#include "geometry/convex_layers.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(4, 0);
    points.emplace_back(4, 4);
    points.emplace_back(0, 4);
    points.emplace_back(2, 2);

    std::vector<int> layer = m1une::geometry::convex_layers(points);
    for (int value : layer) std::cout << value << "\n";
    // 1, 1, 1, 1, 2
}
```
