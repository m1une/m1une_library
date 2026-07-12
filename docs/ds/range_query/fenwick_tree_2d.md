---
title: Fenwick Tree 2D
documentation_of: ../../../ds/range_query/fenwick_tree_2d.hpp
---

## Overview

`FenwickTree2D` is a coordinate-compressed two-dimensional Fenwick tree. It
supports additive point updates and rectangle-sum queries while storing only
coordinates that may be updated.

```cpp
#include "ds/range_query/fenwick_tree_2d.hpp"
```

All points that may be updated must be registered during construction or the
last call to `build`.

## Template Parameters

```cpp
template <class T, class X = int, class Y = X>
class FenwickTree2D;
```

* `T` is the stored sum type. It must support default construction, addition,
  and subtraction.
* `X` and `Y` are the coordinate types and must be sortable and
  equality-comparable.

The class is in `m1une::ds` and provides these aliases:

```cpp
using value_type = T;
using point_type = std::pair<X, Y>;
using weighted_point_type = std::tuple<X, Y, T>;
```

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `FenwickTree2D()` | Constructs an empty tree. | $O(1)$ |
| `FenwickTree2D(std::vector<point_type> points)` | Registers the points with initial value zero. Duplicate coordinates are removed. | $O(N\log^2 N)$ |
| `FenwickTree2D(const std::vector<weighted_point_type>& points)` | Registers the coordinates and adds every supplied weight. Weights at duplicate coordinates are summed. | $O(N\log^2 N)$ |
| `void build(std::vector<point_type> points)` | Rebuilds from registered coordinates and resets all values to zero. | $O(N\log^2 N)$ |
| `void build(const std::vector<weighted_point_type>& points)` | Rebuilds and adds all supplied weights. | $O(N\log^2 N)$ |
| `int size() const` | Returns the number of distinct registered points. | $O(1)$ |
| `bool empty() const` | Returns whether no points are registered. | $O(1)$ |
| `int x_size() const` | Returns the number of distinct registered x-coordinates. | $O(1)$ |
| `const std::vector<X>& xs() const` | Returns the sorted distinct x-coordinates. | $O(1)$ |
| `bool contains_point(x, y) const` | Tests whether `(x, y)` is registered. | $O(\log N)$ |
| `void add(x, y, value)` | Adds `value` at a registered point. | $O(\log^2 N)$ |
| `T sum(x_upper, y_upper) const` | Returns the sum over `x < x_upper` and `y < y_upper`. | $O(\log^2 N)$ |
| `T sum(x_lower, x_upper, y_lower, y_upper) const` | Returns the sum in `[x_lower, x_upper) × [y_lower, y_upper)`. | $O(\log^2 N)$ |

The structure uses $O(N\log N)$ memory. Query boundaries do not need to be
registered coordinates. Calling `add` for an unregistered point is invalid.

Unlike `Segtree2D`, this structure only supports additive updates and sums. In
return, its nodes are Fenwick arrays rather than segment trees, giving smaller
memory use and constants for this operation set.

## Example

```cpp
#include "ds/range_query/fenwick_tree_2d.hpp"

#include <cassert>
#include <utility>
#include <vector>

int main() {
    std::vector<std::pair<int, int>> points{
        {1, 2},
        {3, 4},
        {5, 1}
    };
    m1une::ds::FenwickTree2D<long long> fenwick(points);

    fenwick.add(1, 2, 10);
    fenwick.add(3, 4, 20);
    fenwick.add(5, 1, 30);

    assert(fenwick.sum(0, 4, 0, 5) == 30);
    assert(fenwick.sum(4, 3) == 10);
}
```
