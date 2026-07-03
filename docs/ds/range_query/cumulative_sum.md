---
title: Cumulative Sum (1D, 2D, 3D)
documentation_of: ../../../ds/range_query/cumulative_sum.hpp
---

## Overview

`CumulativeSum1D`, `CumulativeSum2D`, and `CumulativeSum3D` preprocess static
arrays so that interval, rectangle, and cuboid sums can be answered in constant
time. Indices are zero-based and every range is half-open.

`CumulativeSum<T>` is an alias for `CumulativeSum1D<T>`.

The multidimensional classes store their prefix tables in contiguous memory.
The input is interpreted as row-major `values[y][x]` in 2D and
`values[z][y][x]` in 3D. Input rows and planes must form a rectangular grid.

## Template Requirements

* `T{}` must be the additive identity.
* `T` must support addition and subtraction, with the usual additive-group
  laws. Integer, floating-point, and modular-number types are typical choices.

As with any cumulative sum, choose `T` large enough to hold every prefix sum.

## Methods

### `CumulativeSum1D<T>`

| Method | Description | Complexity |
| --- | --- | --- |
| `CumulativeSum1D()` | Constructs an empty array. | $O(1)$ |
| `CumulativeSum1D(const std::vector<T>& values)` | Builds cumulative sums for `values`. | $O(N)$ time and space |
| `int size() const` | Returns $N$. | $O(1)$ |
| `bool empty() const` | Returns whether $N = 0$. | $O(1)$ |
| `T sum(int r) const` | Returns the sum of `[0, r)`. | $O(1)$ |
| `T sum(int l, int r) const` | Returns the sum of `[l, r)`. | $O(1)$ |

### `CumulativeSum2D<T>`

| Method | Description | Complexity |
| --- | --- | --- |
| `CumulativeSum2D()` | Constructs an empty grid. | $O(1)$ |
| `CumulativeSum2D(const std::vector<std::vector<T>>& values)` | Builds cumulative sums for an $H \times W$ grid. | $O(HW)$ time and space |
| `int height() const` | Returns $H$. | $O(1)$ |
| `int width() const` | Returns $W$. | $O(1)$ |
| `bool empty() const` | Returns whether any dimension is zero. | $O(1)$ |
| `T sum(int y, int x) const` | Returns the sum of `[0, y) x [0, x)`. | $O(1)$ |
| `T sum(int y1, int y2, int x1, int x2) const` | Returns the sum of `[y1, y2) x [x1, x2)`. | $O(1)$ |

### `CumulativeSum3D<T>`

| Method | Description | Complexity |
| --- | --- | --- |
| `CumulativeSum3D()` | Constructs an empty grid. | $O(1)$ |
| `CumulativeSum3D(const std::vector<std::vector<std::vector<T>>>& values)` | Builds cumulative sums for a $D \times H \times W$ grid. | $O(DHW)$ time and space |
| `int depth() const` | Returns $D$. | $O(1)$ |
| `int height() const` | Returns $H$. | $O(1)$ |
| `int width() const` | Returns $W$. | $O(1)$ |
| `bool empty() const` | Returns whether any dimension is zero. | $O(1)$ |
| `T sum(int z, int y, int x) const` | Returns the sum of `[0, z) x [0, y) x [0, x)`. | $O(1)$ |
| `T sum(int z1, int z2, int y1, int y2, int x1, int x2) const` | Returns the sum of `[z1, z2) x [y1, y2) x [x1, x2)`. | $O(1)$ |

All query bounds are checked with assertions.

## Example

```cpp
#include "ds/range_query/cumulative_sum.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> grid(2, std::vector<int>(3));
    grid[0][0] = 1;
    grid[0][1] = 2;
    grid[0][2] = 3;
    grid[1][0] = 4;
    grid[1][1] = 5;
    grid[1][2] = 6;

    m1une::ds::CumulativeSum2D<int> sums(grid);

    // Rows [0, 2), columns [1, 3): 2 + 3 + 5 + 6 = 16.
    std::cout << sums.sum(0, 2, 1, 3) << '\n';
}
```
