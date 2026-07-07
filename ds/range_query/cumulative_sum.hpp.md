---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/cumulative_sum.test.cpp
    title: verify/ds/range_query/cumulative_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/cumulative_sum.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    // Static one-dimensional cumulative sums.\ntemplate <typename T>\nstruct CumulativeSum1D\
    \ {\n   private:\n    std::vector<T> _prefix;\n\n   public:\n    CumulativeSum1D()\
    \ : _prefix(1, T{}) {}\n\n    explicit CumulativeSum1D(const std::vector<T>& values)\n\
    \        : _prefix(values.size() + 1, T{}) {\n        for (std::size_t i = 0;\
    \ i < values.size(); ++i) {\n            _prefix[i + 1] = _prefix[i] + values[i];\n\
    \        }\n    }\n\n    int size() const {\n        return int(_prefix.size())\
    \ - 1;\n    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\
    \n    // Returns the sum of [0, r).\n    T sum(int r) const {\n        assert(0\
    \ <= r && r <= size());\n        return _prefix[r];\n    }\n\n    // Returns the\
    \ sum of [l, r).\n    T sum(int l, int r) const {\n        assert(0 <= l && l\
    \ <= r && r <= size());\n        return _prefix[r] - _prefix[l];\n    }\n};\n\n\
    // The unsuffixed name is an alias for the one-dimensional structure.\ntemplate\
    \ <typename T>\nusing CumulativeSum = CumulativeSum1D<T>;\n\n// Static two-dimensional\
    \ cumulative sums over a rectangular row-major grid.\ntemplate <typename T>\n\
    struct CumulativeSum2D {\n   private:\n    int _height;\n    int _width;\n   \
    \ std::vector<T> _prefix;\n\n    std::size_t index(int y, int x) const {\n   \
    \     return std::size_t(y) * std::size_t(_width + 1) + std::size_t(x);\n    }\n\
    \n   public:\n    CumulativeSum2D() : _height(0), _width(0), _prefix(1, T{}) {}\n\
    \n    explicit CumulativeSum2D(const std::vector<std::vector<T>>& values)\n  \
    \      : _height(int(values.size())),\n          _width(values.empty() ? 0 : int(values.front().size())),\n\
    \          _prefix(\n              std::size_t(_height + 1) * std::size_t(_width\
    \ + 1), T{}\n          ) {\n        for (const auto& row : values) {\n       \
    \     assert(int(row.size()) == _width);\n        }\n\n        for (int y = 1;\
    \ y <= _height; ++y) {\n            for (int x = 1; x <= _width; ++x) {\n    \
    \            _prefix[index(y, x)] =\n                    values[y - 1][x - 1]\
    \ + _prefix[index(y - 1, x)]\n                    + _prefix[index(y, x - 1)] -\
    \ _prefix[index(y - 1, x - 1)];\n            }\n        }\n    }\n\n    int height()\
    \ const {\n        return _height;\n    }\n\n    int width() const {\n       \
    \ return _width;\n    }\n\n    bool empty() const {\n        return _height ==\
    \ 0 || _width == 0;\n    }\n\n    // Returns the sum of [0, y) x [0, x).\n   \
    \ T sum(int y, int x) const {\n        assert(0 <= y && y <= _height);\n     \
    \   assert(0 <= x && x <= _width);\n        return _prefix[index(y, x)];\n   \
    \ }\n\n    // Returns the sum of [y1, y2) x [x1, x2).\n    T sum(int y1, int y2,\
    \ int x1, int x2) const {\n        assert(0 <= y1 && y1 <= y2 && y2 <= _height);\n\
    \        assert(0 <= x1 && x1 <= x2 && x2 <= _width);\n        return _prefix[index(y2,\
    \ x2)] - _prefix[index(y1, x2)]\n               - _prefix[index(y2, x1)] + _prefix[index(y1,\
    \ x1)];\n    }\n};\n\n// Static three-dimensional cumulative sums over a rectangular\
    \ z-y-x grid.\ntemplate <typename T>\nstruct CumulativeSum3D {\n   private:\n\
    \    int _depth;\n    int _height;\n    int _width;\n    std::vector<T> _prefix;\n\
    \n    std::size_t index(int z, int y, int x) const {\n        return (std::size_t(z)\
    \ * std::size_t(_height + 1) + std::size_t(y))\n                   * std::size_t(_width\
    \ + 1)\n               + std::size_t(x);\n    }\n\n   public:\n    CumulativeSum3D()\n\
    \        : _depth(0), _height(0), _width(0), _prefix(1, T{}) {}\n\n    explicit\
    \ CumulativeSum3D(\n        const std::vector<std::vector<std::vector<T>>>& values\n\
    \    )\n        : _depth(int(values.size())),\n          _height(values.empty()\
    \ ? 0 : int(values.front().size())),\n          _width(\n              values.empty()\
    \ || values.front().empty()\n                  ? 0\n                  : int(values.front().front().size())\n\
    \          ),\n          _prefix(\n              std::size_t(_depth + 1) * std::size_t(_height\
    \ + 1)\n                  * std::size_t(_width + 1),\n              T{}\n    \
    \      ) {\n        for (const auto& plane : values) {\n            assert(int(plane.size())\
    \ == _height);\n            for (const auto& row : plane) {\n                assert(int(row.size())\
    \ == _width);\n            }\n        }\n\n        for (int z = 1; z <= _depth;\
    \ ++z) {\n            for (int y = 1; y <= _height; ++y) {\n                for\
    \ (int x = 1; x <= _width; ++x) {\n                    _prefix[index(z, y, x)]\
    \ =\n                        values[z - 1][y - 1][x - 1]\n                   \
    \     + _prefix[index(z - 1, y, x)]\n                        + _prefix[index(z,\
    \ y - 1, x)]\n                        + _prefix[index(z, y, x - 1)]\n        \
    \                - _prefix[index(z - 1, y - 1, x)]\n                        -\
    \ _prefix[index(z - 1, y, x - 1)]\n                        - _prefix[index(z,\
    \ y - 1, x - 1)]\n                        + _prefix[index(z - 1, y - 1, x - 1)];\n\
    \                }\n            }\n        }\n    }\n\n    int depth() const {\n\
    \        return _depth;\n    }\n\n    int height() const {\n        return _height;\n\
    \    }\n\n    int width() const {\n        return _width;\n    }\n\n    bool empty()\
    \ const {\n        return _depth == 0 || _height == 0 || _width == 0;\n    }\n\
    \n    // Returns the sum of [0, z) x [0, y) x [0, x).\n    T sum(int z, int y,\
    \ int x) const {\n        assert(0 <= z && z <= _depth);\n        assert(0 <=\
    \ y && y <= _height);\n        assert(0 <= x && x <= _width);\n        return\
    \ _prefix[index(z, y, x)];\n    }\n\n    // Returns the sum of [z1, z2) x [y1,\
    \ y2) x [x1, x2).\n    T sum(int z1, int z2, int y1, int y2, int x1, int x2) const\
    \ {\n        assert(0 <= z1 && z1 <= z2 && z2 <= _depth);\n        assert(0 <=\
    \ y1 && y1 <= y2 && y2 <= _height);\n        assert(0 <= x1 && x1 <= x2 && x2\
    \ <= _width);\n        return _prefix[index(z2, y2, x2)] - _prefix[index(z1, y2,\
    \ x2)]\n               - _prefix[index(z2, y1, x2)] - _prefix[index(z2, y2, x1)]\n\
    \               + _prefix[index(z1, y1, x2)] + _prefix[index(z1, y2, x1)]\n  \
    \             + _prefix[index(z2, y1, x1)] - _prefix[index(z1, y1, x1)];\n   \
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_CUMULATIVE_SUM_HPP\n#define M1UNE_DS_CUMULATIVE_SUM_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// Static one-dimensional cumulative sums.\ntemplate\
    \ <typename T>\nstruct CumulativeSum1D {\n   private:\n    std::vector<T> _prefix;\n\
    \n   public:\n    CumulativeSum1D() : _prefix(1, T{}) {}\n\n    explicit CumulativeSum1D(const\
    \ std::vector<T>& values)\n        : _prefix(values.size() + 1, T{}) {\n     \
    \   for (std::size_t i = 0; i < values.size(); ++i) {\n            _prefix[i +\
    \ 1] = _prefix[i] + values[i];\n        }\n    }\n\n    int size() const {\n \
    \       return int(_prefix.size()) - 1;\n    }\n\n    bool empty() const {\n \
    \       return size() == 0;\n    }\n\n    // Returns the sum of [0, r).\n    T\
    \ sum(int r) const {\n        assert(0 <= r && r <= size());\n        return _prefix[r];\n\
    \    }\n\n    // Returns the sum of [l, r).\n    T sum(int l, int r) const {\n\
    \        assert(0 <= l && l <= r && r <= size());\n        return _prefix[r] -\
    \ _prefix[l];\n    }\n};\n\n// The unsuffixed name is an alias for the one-dimensional\
    \ structure.\ntemplate <typename T>\nusing CumulativeSum = CumulativeSum1D<T>;\n\
    \n// Static two-dimensional cumulative sums over a rectangular row-major grid.\n\
    template <typename T>\nstruct CumulativeSum2D {\n   private:\n    int _height;\n\
    \    int _width;\n    std::vector<T> _prefix;\n\n    std::size_t index(int y,\
    \ int x) const {\n        return std::size_t(y) * std::size_t(_width + 1) + std::size_t(x);\n\
    \    }\n\n   public:\n    CumulativeSum2D() : _height(0), _width(0), _prefix(1,\
    \ T{}) {}\n\n    explicit CumulativeSum2D(const std::vector<std::vector<T>>& values)\n\
    \        : _height(int(values.size())),\n          _width(values.empty() ? 0 :\
    \ int(values.front().size())),\n          _prefix(\n              std::size_t(_height\
    \ + 1) * std::size_t(_width + 1), T{}\n          ) {\n        for (const auto&\
    \ row : values) {\n            assert(int(row.size()) == _width);\n        }\n\
    \n        for (int y = 1; y <= _height; ++y) {\n            for (int x = 1; x\
    \ <= _width; ++x) {\n                _prefix[index(y, x)] =\n                \
    \    values[y - 1][x - 1] + _prefix[index(y - 1, x)]\n                    + _prefix[index(y,\
    \ x - 1)] - _prefix[index(y - 1, x - 1)];\n            }\n        }\n    }\n\n\
    \    int height() const {\n        return _height;\n    }\n\n    int width() const\
    \ {\n        return _width;\n    }\n\n    bool empty() const {\n        return\
    \ _height == 0 || _width == 0;\n    }\n\n    // Returns the sum of [0, y) x [0,\
    \ x).\n    T sum(int y, int x) const {\n        assert(0 <= y && y <= _height);\n\
    \        assert(0 <= x && x <= _width);\n        return _prefix[index(y, x)];\n\
    \    }\n\n    // Returns the sum of [y1, y2) x [x1, x2).\n    T sum(int y1, int\
    \ y2, int x1, int x2) const {\n        assert(0 <= y1 && y1 <= y2 && y2 <= _height);\n\
    \        assert(0 <= x1 && x1 <= x2 && x2 <= _width);\n        return _prefix[index(y2,\
    \ x2)] - _prefix[index(y1, x2)]\n               - _prefix[index(y2, x1)] + _prefix[index(y1,\
    \ x1)];\n    }\n};\n\n// Static three-dimensional cumulative sums over a rectangular\
    \ z-y-x grid.\ntemplate <typename T>\nstruct CumulativeSum3D {\n   private:\n\
    \    int _depth;\n    int _height;\n    int _width;\n    std::vector<T> _prefix;\n\
    \n    std::size_t index(int z, int y, int x) const {\n        return (std::size_t(z)\
    \ * std::size_t(_height + 1) + std::size_t(y))\n                   * std::size_t(_width\
    \ + 1)\n               + std::size_t(x);\n    }\n\n   public:\n    CumulativeSum3D()\n\
    \        : _depth(0), _height(0), _width(0), _prefix(1, T{}) {}\n\n    explicit\
    \ CumulativeSum3D(\n        const std::vector<std::vector<std::vector<T>>>& values\n\
    \    )\n        : _depth(int(values.size())),\n          _height(values.empty()\
    \ ? 0 : int(values.front().size())),\n          _width(\n              values.empty()\
    \ || values.front().empty()\n                  ? 0\n                  : int(values.front().front().size())\n\
    \          ),\n          _prefix(\n              std::size_t(_depth + 1) * std::size_t(_height\
    \ + 1)\n                  * std::size_t(_width + 1),\n              T{}\n    \
    \      ) {\n        for (const auto& plane : values) {\n            assert(int(plane.size())\
    \ == _height);\n            for (const auto& row : plane) {\n                assert(int(row.size())\
    \ == _width);\n            }\n        }\n\n        for (int z = 1; z <= _depth;\
    \ ++z) {\n            for (int y = 1; y <= _height; ++y) {\n                for\
    \ (int x = 1; x <= _width; ++x) {\n                    _prefix[index(z, y, x)]\
    \ =\n                        values[z - 1][y - 1][x - 1]\n                   \
    \     + _prefix[index(z - 1, y, x)]\n                        + _prefix[index(z,\
    \ y - 1, x)]\n                        + _prefix[index(z, y, x - 1)]\n        \
    \                - _prefix[index(z - 1, y - 1, x)]\n                        -\
    \ _prefix[index(z - 1, y, x - 1)]\n                        - _prefix[index(z,\
    \ y - 1, x - 1)]\n                        + _prefix[index(z - 1, y - 1, x - 1)];\n\
    \                }\n            }\n        }\n    }\n\n    int depth() const {\n\
    \        return _depth;\n    }\n\n    int height() const {\n        return _height;\n\
    \    }\n\n    int width() const {\n        return _width;\n    }\n\n    bool empty()\
    \ const {\n        return _depth == 0 || _height == 0 || _width == 0;\n    }\n\
    \n    // Returns the sum of [0, z) x [0, y) x [0, x).\n    T sum(int z, int y,\
    \ int x) const {\n        assert(0 <= z && z <= _depth);\n        assert(0 <=\
    \ y && y <= _height);\n        assert(0 <= x && x <= _width);\n        return\
    \ _prefix[index(z, y, x)];\n    }\n\n    // Returns the sum of [z1, z2) x [y1,\
    \ y2) x [x1, x2).\n    T sum(int z1, int z2, int y1, int y2, int x1, int x2) const\
    \ {\n        assert(0 <= z1 && z1 <= z2 && z2 <= _depth);\n        assert(0 <=\
    \ y1 && y1 <= y2 && y2 <= _height);\n        assert(0 <= x1 && x1 <= x2 && x2\
    \ <= _width);\n        return _prefix[index(z2, y2, x2)] - _prefix[index(z1, y2,\
    \ x2)]\n               - _prefix[index(z2, y1, x2)] - _prefix[index(z2, y2, x1)]\n\
    \               + _prefix[index(z1, y1, x2)] + _prefix[index(z1, y2, x1)]\n  \
    \             + _prefix[index(z2, y1, x1)] - _prefix[index(z1, y1, x1)];\n   \
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_CUMULATIVE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/cumulative_sum.hpp
  requiredBy: []
  timestamp: '2026-07-03 14:46:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/cumulative_sum.test.cpp
documentation_of: ds/range_query/cumulative_sum.hpp
layout: document
title: Cumulative Sum (1D, 2D, 3D)
---

## Overview

`CumulativeSum1D`, `CumulativeSum2D`, and `CumulativeSum3D` preprocess static
arrays so that interval, rectangle, and cuboid sums can be answered in constant
time. Indices are zero-based and every range is half-open.

This header lives in `ds/range_query/` because it constructs a reusable query
object. One-shot sequence algorithms live in `algo/sequence/`, and small contest
helpers live in `utilities/`.

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
