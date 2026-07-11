---
title: Closest Pair of Points
documentation_of: ../../geometry/closest_pair.hpp
---

## Overview

`closest_pair(points)` returns two distinct input points whose Euclidean
distance is minimum. It uses divide and conquer after sorting the points by
their x-coordinate.

Duplicate points are supported and produce squared distance zero.

## Interface

```cpp
template <Coordinate T>
struct ClosestPair {
    int first;
    int second;
    wide_type<T> distance_squared;
};

template <Coordinate T>
std::optional<ClosestPair<T>> closest_pair(
    const std::vector<Point<T>>& points
);
```

## Result

| Member | Description |
| --- | --- |
| `first` | Smaller original index of the selected pair. |
| `second` | Larger original index of the selected pair. |
| `distance_squared` | Squared Euclidean distance in `wide_type<T>`. |

The function returns `std::nullopt` when fewer than two points are supplied.
When several pairs have the same minimum distance, the lexicographically
smallest index pair is returned.

For integral `T`, squared distances are calculated with signed 128-bit
arithmetic. They must fit in `wide_type<T>`. Floating-point coordinates are
compared without an epsilon.

## Operations

| Function | Description | Complexity |
| --- | --- | --- |
| `closest_pair(const std::vector<Point<T>>& points)` | Finds the closest pair without modifying `points`. | $O(N\log N)$ time and $O(N)$ memory |

## Example

```cpp
#include "geometry/closest_pair.hpp"

#include <cassert>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(5, 0);
    points.emplace_back(2, 1);

    auto answer = m1une::geometry::closest_pair(points);
    assert(answer.has_value());
    assert(answer->first == 0);
    assert(answer->second == 2);
    assert(answer->distance_squared == 5);
}
```
