---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/grid_transform.test.cpp
    title: verify/utilities/grid_transform.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/grid_transform.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <cstddef>\n#include <vector>\n\n\
    namespace m1une {\nnamespace utilities {\n\ntemplate <class T>\nusing Vector2D\
    \ = std::vector<std::vector<T>>;\n\nnamespace grid_transform_detail {\n\ntemplate\
    \ <class Row>\nvoid reserve_if_possible(Row& row, std::size_t size) {\n    if\
    \ constexpr (requires { row.reserve(size); }) {\n        row.reserve(size);\n\
    \    }\n}\n\ntemplate <class Row>\nstd::vector<Row> make_rows(std::size_t row_count,\
    \ std::size_t row_size) {\n    std::vector<Row> result(row_count);\n    for (Row&\
    \ row : result) reserve_if_possible(row, row_size);\n    return result;\n}\n\n\
    }  // namespace grid_transform_detail\n\ntemplate <class Row>\nbool is_rectangular(const\
    \ std::vector<Row>& grid) {\n    if (grid.empty()) return true;\n    const std::size_t\
    \ row_size = grid[0].size();\n    for (const Row& row : grid) {\n        if (row.size()\
    \ != row_size) return false;\n    }\n    return true;\n}\n\ntemplate <class Row>\n\
    std::size_t height(const std::vector<Row>& grid) {\n    return grid.size();\n\
    }\n\ntemplate <class Row>\nstd::size_t width(const std::vector<Row>& grid) {\n\
    \    assert(is_rectangular(grid));\n    return grid.empty() ? 0 : grid[0].size();\n\
    }\n\ntemplate <class Row>\nstd::vector<Row> transpose(const std::vector<Row>&\
    \ grid) {\n    assert(is_rectangular(grid));\n    const std::size_t h = height(grid);\n\
    \    const std::size_t w = width(grid);\n\n    std::vector<Row> result =\n   \
    \     grid_transform_detail::make_rows<Row>(w, h);\n    for (std::size_t y = 0;\
    \ y < h; y++) {\n        for (std::size_t x = 0; x < w; x++) {\n            result[x].push_back(grid[y][x]);\n\
    \        }\n    }\n    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row>\
    \ flip_horizontal(const std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n\
    \    std::vector<Row> result = grid;\n    for (Row& row : result) {\n        std::reverse(row.begin(),\
    \ row.end());\n    }\n    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row>\
    \ flip_vertical(const std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n\
    \    std::vector<Row> result = grid;\n    std::reverse(result.begin(), result.end());\n\
    \    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row> rotate90(const\
    \ std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n    const std::size_t\
    \ h = height(grid);\n    const std::size_t w = width(grid);\n\n    std::vector<Row>\
    \ result =\n        grid_transform_detail::make_rows<Row>(w, h);\n    for (std::size_t\
    \ x = 0; x < w; x++) {\n        for (std::size_t y = h; y > 0; y--) {\n      \
    \      result[x].push_back(grid[y - 1][x]);\n        }\n    }\n    return result;\n\
    }\n\ntemplate <class Row>\nstd::vector<Row> rotate180(const std::vector<Row>&\
    \ grid) {\n    assert(is_rectangular(grid));\n    std::vector<Row> result = flip_vertical(grid);\n\
    \    for (Row& row : result) {\n        std::reverse(row.begin(), row.end());\n\
    \    }\n    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row> rotate270(const\
    \ std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n    const std::size_t\
    \ h = height(grid);\n    const std::size_t w = width(grid);\n\n    std::vector<Row>\
    \ result =\n        grid_transform_detail::make_rows<Row>(w, h);\n    for (std::size_t\
    \ x = 0; x < w; x++) {\n        for (std::size_t y = 0; y < h; y++) {\n      \
    \      result[w - 1 - x].push_back(grid[y][x]);\n        }\n    }\n    return\
    \ result;\n}\n\ntemplate <class Row>\nstd::vector<Row> rotate_clockwise(const\
    \ std::vector<Row>& grid) {\n    return rotate90(grid);\n}\n\ntemplate <class\
    \ Row>\nstd::vector<Row> rotate_counterclockwise(const std::vector<Row>& grid)\
    \ {\n    return rotate270(grid);\n}\n\ntemplate <class Row>\nstd::vector<Row>\
    \ rotate(const std::vector<Row>& grid, int clockwise_quarter_turns) {\n    assert(is_rectangular(grid));\n\
    \    int turns = clockwise_quarter_turns % 4;\n    if (turns < 0) turns += 4;\n\
    \    if (turns == 0) return grid;\n    if (turns == 1) return rotate90(grid);\n\
    \    if (turns == 2) return rotate180(grid);\n    return rotate270(grid);\n}\n\
    \ntemplate <class Row>\nstd::array<std::vector<Row>, 4> rotations(const std::vector<Row>&\
    \ grid) {\n    assert(is_rectangular(grid));\n    return std::array<std::vector<Row>,\
    \ 4>{\n        grid,\n        rotate90(grid),\n        rotate180(grid),\n    \
    \    rotate270(grid)\n    };\n}\n\ntemplate <class Row>\nstd::array<std::vector<Row>,\
    \ 8> dihedral_transforms(\n    const std::vector<Row>& grid\n) {\n    assert(is_rectangular(grid));\n\
    \    const std::vector<Row> mirrored = flip_horizontal(grid);\n    return std::array<std::vector<Row>,\
    \ 8>{\n        grid,\n        rotate90(grid),\n        rotate180(grid),\n    \
    \    rotate270(grid),\n        mirrored,\n        rotate90(mirrored),\n      \
    \  rotate180(mirrored),\n        rotate270(mirrored)\n    };\n}\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRID_TRANSFORM_HPP\n#define M1UNE_GRID_TRANSFORM_HPP 1\n\n\
    #include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstddef>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\ntemplate <class\
    \ T>\nusing Vector2D = std::vector<std::vector<T>>;\n\nnamespace grid_transform_detail\
    \ {\n\ntemplate <class Row>\nvoid reserve_if_possible(Row& row, std::size_t size)\
    \ {\n    if constexpr (requires { row.reserve(size); }) {\n        row.reserve(size);\n\
    \    }\n}\n\ntemplate <class Row>\nstd::vector<Row> make_rows(std::size_t row_count,\
    \ std::size_t row_size) {\n    std::vector<Row> result(row_count);\n    for (Row&\
    \ row : result) reserve_if_possible(row, row_size);\n    return result;\n}\n\n\
    }  // namespace grid_transform_detail\n\ntemplate <class Row>\nbool is_rectangular(const\
    \ std::vector<Row>& grid) {\n    if (grid.empty()) return true;\n    const std::size_t\
    \ row_size = grid[0].size();\n    for (const Row& row : grid) {\n        if (row.size()\
    \ != row_size) return false;\n    }\n    return true;\n}\n\ntemplate <class Row>\n\
    std::size_t height(const std::vector<Row>& grid) {\n    return grid.size();\n\
    }\n\ntemplate <class Row>\nstd::size_t width(const std::vector<Row>& grid) {\n\
    \    assert(is_rectangular(grid));\n    return grid.empty() ? 0 : grid[0].size();\n\
    }\n\ntemplate <class Row>\nstd::vector<Row> transpose(const std::vector<Row>&\
    \ grid) {\n    assert(is_rectangular(grid));\n    const std::size_t h = height(grid);\n\
    \    const std::size_t w = width(grid);\n\n    std::vector<Row> result =\n   \
    \     grid_transform_detail::make_rows<Row>(w, h);\n    for (std::size_t y = 0;\
    \ y < h; y++) {\n        for (std::size_t x = 0; x < w; x++) {\n            result[x].push_back(grid[y][x]);\n\
    \        }\n    }\n    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row>\
    \ flip_horizontal(const std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n\
    \    std::vector<Row> result = grid;\n    for (Row& row : result) {\n        std::reverse(row.begin(),\
    \ row.end());\n    }\n    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row>\
    \ flip_vertical(const std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n\
    \    std::vector<Row> result = grid;\n    std::reverse(result.begin(), result.end());\n\
    \    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row> rotate90(const\
    \ std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n    const std::size_t\
    \ h = height(grid);\n    const std::size_t w = width(grid);\n\n    std::vector<Row>\
    \ result =\n        grid_transform_detail::make_rows<Row>(w, h);\n    for (std::size_t\
    \ x = 0; x < w; x++) {\n        for (std::size_t y = h; y > 0; y--) {\n      \
    \      result[x].push_back(grid[y - 1][x]);\n        }\n    }\n    return result;\n\
    }\n\ntemplate <class Row>\nstd::vector<Row> rotate180(const std::vector<Row>&\
    \ grid) {\n    assert(is_rectangular(grid));\n    std::vector<Row> result = flip_vertical(grid);\n\
    \    for (Row& row : result) {\n        std::reverse(row.begin(), row.end());\n\
    \    }\n    return result;\n}\n\ntemplate <class Row>\nstd::vector<Row> rotate270(const\
    \ std::vector<Row>& grid) {\n    assert(is_rectangular(grid));\n    const std::size_t\
    \ h = height(grid);\n    const std::size_t w = width(grid);\n\n    std::vector<Row>\
    \ result =\n        grid_transform_detail::make_rows<Row>(w, h);\n    for (std::size_t\
    \ x = 0; x < w; x++) {\n        for (std::size_t y = 0; y < h; y++) {\n      \
    \      result[w - 1 - x].push_back(grid[y][x]);\n        }\n    }\n    return\
    \ result;\n}\n\ntemplate <class Row>\nstd::vector<Row> rotate_clockwise(const\
    \ std::vector<Row>& grid) {\n    return rotate90(grid);\n}\n\ntemplate <class\
    \ Row>\nstd::vector<Row> rotate_counterclockwise(const std::vector<Row>& grid)\
    \ {\n    return rotate270(grid);\n}\n\ntemplate <class Row>\nstd::vector<Row>\
    \ rotate(const std::vector<Row>& grid, int clockwise_quarter_turns) {\n    assert(is_rectangular(grid));\n\
    \    int turns = clockwise_quarter_turns % 4;\n    if (turns < 0) turns += 4;\n\
    \    if (turns == 0) return grid;\n    if (turns == 1) return rotate90(grid);\n\
    \    if (turns == 2) return rotate180(grid);\n    return rotate270(grid);\n}\n\
    \ntemplate <class Row>\nstd::array<std::vector<Row>, 4> rotations(const std::vector<Row>&\
    \ grid) {\n    assert(is_rectangular(grid));\n    return std::array<std::vector<Row>,\
    \ 4>{\n        grid,\n        rotate90(grid),\n        rotate180(grid),\n    \
    \    rotate270(grid)\n    };\n}\n\ntemplate <class Row>\nstd::array<std::vector<Row>,\
    \ 8> dihedral_transforms(\n    const std::vector<Row>& grid\n) {\n    assert(is_rectangular(grid));\n\
    \    const std::vector<Row> mirrored = flip_horizontal(grid);\n    return std::array<std::vector<Row>,\
    \ 8>{\n        grid,\n        rotate90(grid),\n        rotate180(grid),\n    \
    \    rotate270(grid),\n        mirrored,\n        rotate90(mirrored),\n      \
    \  rotate180(mirrored),\n        rotate270(mirrored)\n    };\n}\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n#endif  // M1UNE_GRID_TRANSFORM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/grid_transform.hpp
  requiredBy: []
  timestamp: '2026-07-07 23:06:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/grid_transform.test.cpp
documentation_of: utilities/grid_transform.hpp
layout: document
title: Grid Transform
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
