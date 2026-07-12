---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/fenwick_tree_2d.test.cpp
    title: verify/ds/range_query/fenwick_tree_2d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/fenwick_tree_2d.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstddef>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T, class\
    \ X = int, class Y = X>\nclass FenwickTree2D {\n   public:\n    using value_type\
    \ = T;\n    using point_type = std::pair<X, Y>;\n    using weighted_point_type\
    \ = std::tuple<X, Y, T>;\n\n   private:\n    std::vector<point_type> _points;\n\
    \    std::vector<X> _xs;\n    std::vector<std::vector<Y>> _ys;\n    std::vector<std::vector<T>>\
    \ _data;\n\n    static std::vector<point_type> normalize_points(\n        std::vector<point_type>\
    \ points\n    ) {\n        std::sort(points.begin(), points.end());\n        points.erase(std::unique(points.begin(),\
    \ points.end()), points.end());\n        return points;\n    }\n\n    T prefix_sum_by_x_count(int\
    \ x_count, const Y& y_upper) const {\n        T result{};\n        for (int x_index\
    \ = x_count; x_index > 0; x_index -= x_index & -x_index) {\n            const\
    \ std::vector<Y>& ys = _ys[std::size_t(x_index)];\n            int y_index = int(\n\
    \                std::lower_bound(ys.begin(), ys.end(), y_upper) - ys.begin()\n\
    \            );\n            const std::vector<T>& data = _data[std::size_t(x_index)];\n\
    \            while (y_index > 0) {\n                result += data[std::size_t(y_index)];\n\
    \                y_index -= y_index & -y_index;\n            }\n        }\n  \
    \      return result;\n    }\n\n    T prefix_sum(const X& x_upper, const Y& y_upper)\
    \ const {\n        const int x_count = int(\n            std::lower_bound(_xs.begin(),\
    \ _xs.end(), x_upper) - _xs.begin()\n        );\n        return prefix_sum_by_x_count(x_count,\
    \ y_upper);\n    }\n\n   public:\n    FenwickTree2D() : _ys(1), _data(1) {}\n\n\
    \    explicit FenwickTree2D(std::vector<point_type> points) {\n        build(std::move(points));\n\
    \    }\n\n    explicit FenwickTree2D(\n        const std::vector<weighted_point_type>&\
    \ points\n    ) {\n        build(points);\n    }\n\n    void build(std::vector<point_type>\
    \ points) {\n        _points = normalize_points(std::move(points));\n        _xs.clear();\n\
    \        _xs.reserve(_points.size());\n        for (const auto& [x, y] : _points)\
    \ {\n            (void)y;\n            if (_xs.empty() || _xs.back() != x) _xs.push_back(x);\n\
    \        }\n\n        const int x_size = int(_xs.size());\n        _ys.assign(std::size_t(x_size\
    \ + 1), {});\n        for (const auto& [x, y] : _points) {\n            int x_index\
    \ = int(\n                std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin()\n\
    \            ) + 1;\n            while (x_index <= x_size) {\n               \
    \ _ys[std::size_t(x_index)].push_back(y);\n                x_index += x_index\
    \ & -x_index;\n            }\n        }\n\n        _data.assign(std::size_t(x_size\
    \ + 1), {});\n        for (int x_index = 1; x_index <= x_size; x_index++) {\n\
    \            std::vector<Y>& ys = _ys[std::size_t(x_index)];\n            std::sort(ys.begin(),\
    \ ys.end());\n            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n\
    \            _data[std::size_t(x_index)].assign(ys.size() + 1, T{});\n       \
    \ }\n    }\n\n    void build(const std::vector<weighted_point_type>& points) {\n\
    \        std::vector<point_type> coordinates;\n        coordinates.reserve(points.size());\n\
    \        for (const auto& [x, y, value] : points) {\n            (void)value;\n\
    \            coordinates.emplace_back(x, y);\n        }\n        build(std::move(coordinates));\n\
    \        for (const auto& [x, y, value] : points) add(x, y, value);\n    }\n\n\
    \    int size() const {\n        return int(_points.size());\n    }\n\n    bool\
    \ empty() const {\n        return _points.empty();\n    }\n\n    int x_size()\
    \ const {\n        return int(_xs.size());\n    }\n\n    const std::vector<X>&\
    \ xs() const {\n        return _xs;\n    }\n\n    bool contains_point(const X&\
    \ x, const Y& y) const {\n        return std::binary_search(_points.begin(), _points.end(),\
    \ point_type(x, y));\n    }\n\n    void add(const X& x, const Y& y, const T& value)\
    \ {\n        assert(contains_point(x, y));\n        int x_index = int(\n     \
    \       std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin()\n        ) +\
    \ 1;\n        while (x_index <= int(_xs.size())) {\n            const std::vector<Y>&\
    \ ys = _ys[std::size_t(x_index)];\n            int y_index = int(\n          \
    \      std::lower_bound(ys.begin(), ys.end(), y) - ys.begin()\n            ) +\
    \ 1;\n            std::vector<T>& data = _data[std::size_t(x_index)];\n      \
    \      while (y_index < int(data.size())) {\n                data[std::size_t(y_index)]\
    \ += value;\n                y_index += y_index & -y_index;\n            }\n \
    \           x_index += x_index & -x_index;\n        }\n    }\n\n    T sum(const\
    \ X& x_upper, const Y& y_upper) const {\n        return prefix_sum(x_upper, y_upper);\n\
    \    }\n\n    T sum(\n        const X& x_lower,\n        const X& x_upper,\n \
    \       const Y& y_lower,\n        const Y& y_upper\n    ) const {\n        assert(!(x_upper\
    \ < x_lower));\n        assert(!(y_upper < y_lower));\n        return prefix_sum(x_upper,\
    \ y_upper) -\n               prefix_sum(x_lower, y_upper) -\n               prefix_sum(x_upper,\
    \ y_lower) +\n               prefix_sum(x_lower, y_lower);\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_FENWICK_TREE_2D_HPP\n#define M1UNE_DS_FENWICK_TREE_2D_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <class T, class X = int, class Y = X>\nclass FenwickTree2D\
    \ {\n   public:\n    using value_type = T;\n    using point_type = std::pair<X,\
    \ Y>;\n    using weighted_point_type = std::tuple<X, Y, T>;\n\n   private:\n \
    \   std::vector<point_type> _points;\n    std::vector<X> _xs;\n    std::vector<std::vector<Y>>\
    \ _ys;\n    std::vector<std::vector<T>> _data;\n\n    static std::vector<point_type>\
    \ normalize_points(\n        std::vector<point_type> points\n    ) {\n       \
    \ std::sort(points.begin(), points.end());\n        points.erase(std::unique(points.begin(),\
    \ points.end()), points.end());\n        return points;\n    }\n\n    T prefix_sum_by_x_count(int\
    \ x_count, const Y& y_upper) const {\n        T result{};\n        for (int x_index\
    \ = x_count; x_index > 0; x_index -= x_index & -x_index) {\n            const\
    \ std::vector<Y>& ys = _ys[std::size_t(x_index)];\n            int y_index = int(\n\
    \                std::lower_bound(ys.begin(), ys.end(), y_upper) - ys.begin()\n\
    \            );\n            const std::vector<T>& data = _data[std::size_t(x_index)];\n\
    \            while (y_index > 0) {\n                result += data[std::size_t(y_index)];\n\
    \                y_index -= y_index & -y_index;\n            }\n        }\n  \
    \      return result;\n    }\n\n    T prefix_sum(const X& x_upper, const Y& y_upper)\
    \ const {\n        const int x_count = int(\n            std::lower_bound(_xs.begin(),\
    \ _xs.end(), x_upper) - _xs.begin()\n        );\n        return prefix_sum_by_x_count(x_count,\
    \ y_upper);\n    }\n\n   public:\n    FenwickTree2D() : _ys(1), _data(1) {}\n\n\
    \    explicit FenwickTree2D(std::vector<point_type> points) {\n        build(std::move(points));\n\
    \    }\n\n    explicit FenwickTree2D(\n        const std::vector<weighted_point_type>&\
    \ points\n    ) {\n        build(points);\n    }\n\n    void build(std::vector<point_type>\
    \ points) {\n        _points = normalize_points(std::move(points));\n        _xs.clear();\n\
    \        _xs.reserve(_points.size());\n        for (const auto& [x, y] : _points)\
    \ {\n            (void)y;\n            if (_xs.empty() || _xs.back() != x) _xs.push_back(x);\n\
    \        }\n\n        const int x_size = int(_xs.size());\n        _ys.assign(std::size_t(x_size\
    \ + 1), {});\n        for (const auto& [x, y] : _points) {\n            int x_index\
    \ = int(\n                std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin()\n\
    \            ) + 1;\n            while (x_index <= x_size) {\n               \
    \ _ys[std::size_t(x_index)].push_back(y);\n                x_index += x_index\
    \ & -x_index;\n            }\n        }\n\n        _data.assign(std::size_t(x_size\
    \ + 1), {});\n        for (int x_index = 1; x_index <= x_size; x_index++) {\n\
    \            std::vector<Y>& ys = _ys[std::size_t(x_index)];\n            std::sort(ys.begin(),\
    \ ys.end());\n            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n\
    \            _data[std::size_t(x_index)].assign(ys.size() + 1, T{});\n       \
    \ }\n    }\n\n    void build(const std::vector<weighted_point_type>& points) {\n\
    \        std::vector<point_type> coordinates;\n        coordinates.reserve(points.size());\n\
    \        for (const auto& [x, y, value] : points) {\n            (void)value;\n\
    \            coordinates.emplace_back(x, y);\n        }\n        build(std::move(coordinates));\n\
    \        for (const auto& [x, y, value] : points) add(x, y, value);\n    }\n\n\
    \    int size() const {\n        return int(_points.size());\n    }\n\n    bool\
    \ empty() const {\n        return _points.empty();\n    }\n\n    int x_size()\
    \ const {\n        return int(_xs.size());\n    }\n\n    const std::vector<X>&\
    \ xs() const {\n        return _xs;\n    }\n\n    bool contains_point(const X&\
    \ x, const Y& y) const {\n        return std::binary_search(_points.begin(), _points.end(),\
    \ point_type(x, y));\n    }\n\n    void add(const X& x, const Y& y, const T& value)\
    \ {\n        assert(contains_point(x, y));\n        int x_index = int(\n     \
    \       std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin()\n        ) +\
    \ 1;\n        while (x_index <= int(_xs.size())) {\n            const std::vector<Y>&\
    \ ys = _ys[std::size_t(x_index)];\n            int y_index = int(\n          \
    \      std::lower_bound(ys.begin(), ys.end(), y) - ys.begin()\n            ) +\
    \ 1;\n            std::vector<T>& data = _data[std::size_t(x_index)];\n      \
    \      while (y_index < int(data.size())) {\n                data[std::size_t(y_index)]\
    \ += value;\n                y_index += y_index & -y_index;\n            }\n \
    \           x_index += x_index & -x_index;\n        }\n    }\n\n    T sum(const\
    \ X& x_upper, const Y& y_upper) const {\n        return prefix_sum(x_upper, y_upper);\n\
    \    }\n\n    T sum(\n        const X& x_lower,\n        const X& x_upper,\n \
    \       const Y& y_lower,\n        const Y& y_upper\n    ) const {\n        assert(!(x_upper\
    \ < x_lower));\n        assert(!(y_upper < y_lower));\n        return prefix_sum(x_upper,\
    \ y_upper) -\n               prefix_sum(x_lower, y_upper) -\n               prefix_sum(x_upper,\
    \ y_lower) +\n               prefix_sum(x_lower, y_lower);\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_FENWICK_TREE_2D_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/fenwick_tree_2d.hpp
  requiredBy: []
  timestamp: '2026-07-13 05:35:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/fenwick_tree_2d.test.cpp
documentation_of: ds/range_query/fenwick_tree_2d.hpp
layout: document
title: Fenwick Tree 2D
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
