---
title: Grid Transform
documentation_of: ../../utilities/grid_transform.hpp
---

## Overview

`grid_transform.hpp` provides small helpers for rectangular 2D arrays:
transpose, 90-degree rotations, flips, and all rotations/reflections. It is
intended for grid problems where the state is stored as
`std::vector<std::vector<T>>` or a row-like type such as `std::vector<std::string>`.

```cpp
#include "utilities/grid_transform.hpp"
```

All names are in `m1une::utilities`.

## Requirements

The input grid must be rectangular: every row has the same length.
Transformation functions check this with `assert(is_rectangular(grid))`.

The `Row` type must support:

- `row.size()` and `row[i]`.
- default construction and `row.push_back(value)` for transpose/rotation.
- copying and reversible iterators for flips.

`std::vector<T>` and `std::string` satisfy these requirements. The alias
`Vector2D<T>` is provided for `std::vector<std::vector<T>>`.

For grids with positive height and zero width, rotations that should have zero
rows are represented by an empty outer vector, because `std::vector<Row>` does
not store width separately.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `template <class T> using Vector2D = std::vector<std::vector<T>>` | Alias for an ordinary 2D vector. | - |
| `template <class Row> bool is_rectangular(const std::vector<Row>& grid)` | Returns whether all rows have the same length. | $O(H)$ |
| `template <class Row> std::size_t height(const std::vector<Row>& grid)` | Returns the number of rows. | $O(1)$ |
| `template <class Row> std::size_t width(const std::vector<Row>& grid)` | Returns the number of columns, or `0` for an empty grid. | $O(H)$ |
| `template <class Row> std::vector<Row> transpose(const std::vector<Row>& grid)` | Swaps rows and columns. | $O(HW)$ |
| `template <class Row> std::vector<Row> flip_horizontal(const std::vector<Row>& grid)` | Mirrors left and right, reversing every row. | $O(HW)$ |
| `template <class Row> std::vector<Row> flip_vertical(const std::vector<Row>& grid)` | Mirrors top and bottom, reversing row order. | $O(HW)$ |
| `template <class Row> std::vector<Row> rotate90(const std::vector<Row>& grid)` | Rotates clockwise by 90 degrees. | $O(HW)$ |
| `template <class Row> std::vector<Row> rotate180(const std::vector<Row>& grid)` | Rotates by 180 degrees. | $O(HW)$ |
| `template <class Row> std::vector<Row> rotate270(const std::vector<Row>& grid)` | Rotates clockwise by 270 degrees, equivalently counterclockwise by 90 degrees. | $O(HW)$ |
| `template <class Row> std::vector<Row> rotate_clockwise(const std::vector<Row>& grid)` | Alias of `rotate90`. | $O(HW)$ |
| `template <class Row> std::vector<Row> rotate_counterclockwise(const std::vector<Row>& grid)` | Alias of `rotate270`. | $O(HW)$ |
| `template <class Row> std::vector<Row> rotate(const std::vector<Row>& grid, int clockwise_quarter_turns)` | Rotates by `clockwise_quarter_turns` quarter turns; negative values rotate counterclockwise. | $O(HW)$ |
| `template <class Row> std::array<std::vector<Row>, 4> rotations(const std::vector<Row>& grid)` | Returns `0`, `90`, `180`, and `270` degree clockwise rotations. | $O(HW)$ |
| `template <class Row> std::array<std::vector<Row>, 8> dihedral_transforms(const std::vector<Row>& grid)` | Returns four rotations, then four rotations of the horizontally flipped grid. | $O(HW)$ |

All transformation functions return a new grid and do not mutate the input.

## Example

```cpp
#include "utilities/grid_transform.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> grid;
    grid.emplace_back("abc");
    grid.emplace_back("def");

    auto rotated = m1une::utilities::rotate90(grid);
    for (const std::string& row : rotated) {
        std::cout << row << "\n";
    }

    auto transposed = m1une::utilities::transpose(grid);
    auto mirrored = m1une::utilities::flip_horizontal(grid);
    (void)transposed;
    (void)mirrored;
}
```

The printed grid is:

```text
da
eb
fc
```
