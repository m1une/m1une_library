---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/detail/convex_polygon_normalize.hpp
    title: geometry/detail/convex_polygon_normalize.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  - icon: ':heavy_check_mark:'
    path: geometry/convex_polygon.hpp
    title: Convex Polygons
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/geometry/centroid.test.cpp
    title: verify/geometry/centroid.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/convex_decomposition.test.cpp
    title: verify/geometry/convex_decomposition.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/convex_diameter.test.cpp
    title: verify/geometry/convex_diameter.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/convex_polygon.test.cpp
    title: verify/geometry/convex_polygon.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/is_convex_polygon.test.cpp
    title: verify/geometry/is_convex_polygon.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/minkowski_sum.test.cpp
    title: verify/geometry/minkowski_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/polygon_operations.test.cpp
    title: verify/geometry/polygon_operations.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/steiner_convex_decomposition.test.cpp
    title: verify/geometry/steiner_convex_decomposition.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/minkowski_sum.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <utility>\n#include <vector>\n\n#line 1 \"geometry/detail/convex_polygon_normalize.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 8 \"geometry/detail/convex_polygon_normalize.hpp\"\
    \n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#include <cmath>\n#include <concepts>\n\
    #line 7 \"geometry/point.hpp\"\n#include <type_traits>\n\nnamespace m1une {\n\
    namespace geometry {\n\ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T>\
    \ && !std::same_as<std::remove_cv_t<T>, bool>;\n\ntemplate <Coordinate T>\nusing\
    \ wide_type = std::conditional_t<std::integral<T>, __int128_t, long double>;\n\
    \ntemplate <Coordinate T>\nstruct Point {\n    T x;\n    T y;\n\n    constexpr\
    \ Point() : x(0), y(0) {}\n    constexpr Point(T x_value, T y_value) : x(x_value),\
    \ y(y_value) {}\n\n    template <Coordinate U>\n    explicit constexpr Point(const\
    \ Point<U>& other)\n        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
    \ {}\n\n    constexpr Point& operator+=(const Point& other) {\n        x += other.x;\n\
    \        y += other.y;\n        return *this;\n    }\n\n    constexpr Point& operator-=(const\
    \ Point& other) {\n        x -= other.x;\n        y -= other.y;\n        return\
    \ *this;\n    }\n\n    constexpr Point operator+() const {\n        return *this;\n\
    \    }\n\n    constexpr Point operator-() const {\n        return Point(-x, -y);\n\
    \    }\n\n    friend constexpr Point operator+(Point left, const Point& right)\
    \ {\n        return left += right;\n    }\n\n    friend constexpr Point operator-(Point\
    \ left, const Point& right) {\n        return left -= right;\n    }\n\n    friend\
    \ constexpr bool operator==(const Point&, const Point&) = default;\n\n    friend\
    \ constexpr bool operator<(const Point& left, const Point& right) {\n        if\
    \ (left.x != right.x) return left.x < right.x;\n        return left.y < right.y;\n\
    \    }\n};\n\ntemplate <Coordinate T>\nconstexpr Point<long double> centroid(const\
    \ Point<T>& point) {\n    return Point<long double>(point);\n}\n\ntemplate <Coordinate\
    \ T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr auto operator*(const\
    \ Point<T>& point, Scalar scalar) {\n    using Result = std::common_type_t<T,\
    \ Scalar>;\n    return Point<Result>(\n        Result(point.x) * Result(scalar),\n\
    \        Result(point.y) * Result(scalar)\n    );\n}\n\ntemplate <typename Scalar,\
    \ Coordinate T>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr auto operator*(Scalar\
    \ scalar, const Point<T>& point) {\n    return point * scalar;\n}\n\ntemplate\
    \ <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr\
    \ auto operator/(const Point<T>& point, Scalar scalar) {\n    using Result = std::common_type_t<T,\
    \ Scalar>;\n    return Point<Result>(\n        Result(point.x) / Result(scalar),\n\
    \        Result(point.y) / Result(scalar)\n    );\n}\n\ntemplate <Coordinate T>\n\
    constexpr wide_type<T> dot(const Point<T>& a, const Point<T>& b) {\n    using\
    \ W = wide_type<T>;\n    return W(a.x) * W(b.x) + W(a.y) * W(b.y);\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr wide_type<T> cross(const Point<T>& a, const Point<T>&\
    \ b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.y) - W(a.y) * W(b.x);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(\n    const Point<T>&\
    \ origin,\n    const Point<T>& a,\n    const Point<T>& b\n) {\n    using W = wide_type<T>;\n\
    \    W ax = W(a.x) - W(origin.x);\n    W ay = W(a.y) - W(origin.y);\n    W bx\
    \ = W(b.x) - W(origin.x);\n    W by = W(b.y) - W(origin.y);\n    return ax * by\
    \ - ay * bx;\n}\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> norm2(const\
    \ Point<T>& point) {\n    return dot(point, point);\n}\n\ntemplate <Coordinate\
    \ T>\nconstexpr wide_type<T> distance2(const Point<T>& a, const Point<T>& b) {\n\
    \    using W = wide_type<T>;\n    W dx = W(a.x) - W(b.x);\n    W dy = W(a.y) -\
    \ W(b.y);\n    return dx * dx + dy * dy;\n}\n\ntemplate <Coordinate T>\nlong double\
    \ norm(const Point<T>& point) {\n    return std::hypot(\n        static_cast<long\
    \ double>(point.x),\n        static_cast<long double>(point.y)\n    );\n}\n\n\
    template <Coordinate T>\nlong double distance(const Point<T>& a, const Point<T>&\
    \ b) {\n    return std::hypot(\n        static_cast<long double>(a.x) - static_cast<long\
    \ double>(b.x),\n        static_cast<long double>(a.y) - static_cast<long double>(b.y)\n\
    \    );\n}\n\ntemplate <Coordinate T, typename M, typename N>\nrequires std::is_arithmetic_v<M>\
    \ && std::is_arithmetic_v<N>\nconstexpr Point<long double> internal_division_point(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    M m,\n    N n\n) {\n    long\
    \ double first_ratio = static_cast<long double>(m);\n    long double second_ratio\
    \ = static_cast<long double>(n);\n    long double denominator = first_ratio +\
    \ second_ratio;\n    assert(denominator != 0);\n    Point<long double> first(a);\n\
    \    Point<long double> direction = Point<long double>(b) - first;\n    return\
    \ first + direction * (first_ratio / denominator);\n}\n\ntemplate <Coordinate\
    \ T, typename M, typename N>\nrequires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>\n\
    constexpr Point<long double> external_division_point(\n    const Point<T>& a,\n\
    \    const Point<T>& b,\n    M m,\n    N n\n) {\n    long double first_ratio =\
    \ static_cast<long double>(m);\n    long double second_ratio = static_cast<long\
    \ double>(n);\n    long double denominator = first_ratio - second_ratio;\n   \
    \ assert(denominator != 0);\n    Point<long double> first(a);\n    Point<long\
    \ double> direction = Point<long double>(b) - first;\n    return first + direction\
    \ * (first_ratio / denominator);\n}\n\ntemplate <Coordinate T>\nconstexpr int\
    \ sign(wide_type<T> value, long double eps = 1e-12L) {\n    if constexpr (std::integral<T>)\
    \ {\n        return (value > 0) - (value < 0);\n    } else {\n        return (value\
    \ > eps) - (value < -eps);\n    }\n}\n\ntemplate <Coordinate T>\nconstexpr int\
    \ orientation(\n    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>&\
    \ c,\n    long double eps = 1e-12L\n) {\n    return sign<T>(cross(a, b, c), eps);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr bool collinear(\n    const Point<T>& a,\n\
    \    const Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n\
    ) {\n    return orientation(a, b, c, eps) == 0;\n}\n\ntemplate <Coordinate T>\n\
    Point<long double> rotate(const Point<T>& point, long double angle) {\n    long\
    \ double cosine = std::cos(angle);\n    long double sine = std::sin(angle);\n\
    \    return Point<long double>(\n        static_cast<long double>(point.x) * cosine\
    \ -\n            static_cast<long double>(point.y) * sine,\n        static_cast<long\
    \ double>(point.x) * sine +\n            static_cast<long double>(point.y) * cosine\n\
    \    );\n}\n\ntemplate <Coordinate T>\nPoint<long double> normalized(const Point<T>&\
    \ point) {\n    long double length = norm(point);\n    assert(length != 0);\n\
    \    return Point<long double>(\n        static_cast<long double>(point.x) / length,\n\
    \        static_cast<long double>(point.y) / length\n    );\n}\n\n}  // namespace\
    \ geometry\n}  // namespace m1une\n\n\n#line 10 \"geometry/detail/convex_polygon_normalize.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\nnamespace convex_polygon_detail {\n\
    \ntemplate <Coordinate T>\nwide_type<T> boundary_area2(const std::vector<Point<T>>&\
    \ polygon) {\n    wide_type<T> result = 0;\n    for (std::size_t index = 0; index\
    \ < polygon.size(); ++index) {\n        result += cross(\n            polygon[index],\n\
    \            polygon[(index + 1) % polygon.size()]\n        );\n    }\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<T>> normalize_convex_boundary(\n\
    \    std::vector<Point<T>> polygon,\n    long double eps\n) {\n    if (polygon.size()\
    \ >= 2 && polygon.front() == polygon.back()) {\n        polygon.pop_back();\n\
    \    }\n    polygon.erase(\n        std::unique(polygon.begin(), polygon.end()),\n\
    \        polygon.end()\n    );\n    if (polygon.size() >= 2 && polygon.front()\
    \ == polygon.back()) {\n        polygon.pop_back();\n    }\n    if (polygon.size()\
    \ <= 1) return polygon;\n    if (\n        polygon.size() >= 3 &&\n        sign<T>(boundary_area2(polygon),\
    \ eps) < 0\n    ) {\n        std::reverse(polygon.begin(), polygon.end());\n \
    \   }\n\n    const auto start = std::min_element(\n        polygon.begin(),\n\
    \        polygon.end(),\n        [](const Point<T>& first, const Point<T>& second)\
    \ {\n            if (first.y != second.y) return first.y < second.y;\n       \
    \     return first.x < second.x;\n        }\n    );\n    std::rotate(polygon.begin(),\
    \ start, polygon.end());\n\n    if (polygon.size() >= 3) {\n        std::vector<Point<T>>\
    \ cleaned;\n        const std::size_t size = polygon.size();\n        cleaned.reserve(size);\n\
    \        for (std::size_t index = 0; index < size; ++index) {\n            const\
    \ Point<T>& previous = polygon[(index + size - 1) % size];\n            const\
    \ Point<T>& current = polygon[index];\n            const Point<T>& next = polygon[(index\
    \ + 1) % size];\n            if (\n                orientation(previous, current,\
    \ next, eps) != 0 ||\n                sign<T>(dot(current - previous, next - current),\
    \ eps) < 0\n            ) {\n                cleaned.push_back(current);\n   \
    \         }\n        }\n        polygon = std::move(cleaned);\n    }\n    return\
    \ polygon;\n}\n\n}  // namespace convex_polygon_detail\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n#line 10 \"geometry/minkowski_sum.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\n// Returns the normalized boundary of the Minkowski\
    \ sum of two nonempty\n// ordered convex polygons.\ntemplate <Coordinate T>\n\
    std::vector<Point<T>> minkowski_sum(\n    std::vector<Point<T>> first,\n    std::vector<Point<T>>\
    \ second,\n    long double eps = 1e-12L\n) {\n    assert(!first.empty());\n  \
    \  assert(!second.empty());\n    first = convex_polygon_detail::normalize_convex_boundary(\n\
    \        std::move(first),\n        eps\n    );\n    second = convex_polygon_detail::normalize_convex_boundary(\n\
    \        std::move(second),\n        eps\n    );\n\n    if (first.size() == 1\
    \ || second.size() == 1) {\n        if (second.size() == 1) std::swap(first, second);\n\
    \        for (Point<T>& point : second) point += first[0];\n        return convex_polygon_detail::normalize_convex_boundary(\n\
    \            std::move(second),\n            eps\n        );\n    }\n\n    std::vector<Point<T>>\
    \ first_edges;\n    std::vector<Point<T>> second_edges;\n    first_edges.reserve(first.size());\n\
    \    second_edges.reserve(second.size());\n    for (std::size_t index = 0; index\
    \ < first.size(); ++index) {\n        first_edges.push_back(\n            first[(index\
    \ + 1) % first.size()] - first[index]\n        );\n    }\n    for (std::size_t\
    \ index = 0; index < second.size(); ++index) {\n        second_edges.push_back(\n\
    \            second[(index + 1) % second.size()] - second[index]\n        );\n\
    \    }\n\n    Point<T> current = first.front() + second.front();\n    std::vector<Point<T>>\
    \ result;\n    result.reserve(first.size() + second.size());\n    result.push_back(current);\n\
    \    std::size_t first_index = 0;\n    std::size_t second_index = 0;\n    while\
    \ (\n        first_index < first_edges.size() ||\n        second_index < second_edges.size()\n\
    \    ) {\n        Point<T> step;\n        if (first_index == first_edges.size())\
    \ {\n            step = second_edges[second_index++];\n        } else if (second_index\
    \ == second_edges.size()) {\n            step = first_edges[first_index++];\n\
    \        } else {\n            const auto turn = cross(\n                first_edges[first_index],\n\
    \                second_edges[second_index]\n            );\n            if (turn\
    \ > 0) {\n                step = first_edges[first_index++];\n            } else\
    \ if (turn < 0) {\n                step = second_edges[second_index++];\n    \
    \        } else {\n                step = first_edges[first_index++] +\n     \
    \                  second_edges[second_index++];\n            }\n        }\n \
    \       current += step;\n        if (\n            first_index < first_edges.size()\
    \ ||\n            second_index < second_edges.size()\n        ) {\n          \
    \  result.push_back(current);\n        }\n    }\n    return convex_polygon_detail::normalize_convex_boundary(\n\
    \        std::move(result),\n        eps\n    );\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_MINKOWSKI_SUM_HPP\n#define M1UNE_GEOMETRY_MINKOWSKI_SUM_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \n#include \"detail/convex_polygon_normalize.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\n// Returns the normalized boundary of the Minkowski sum of two\
    \ nonempty\n// ordered convex polygons.\ntemplate <Coordinate T>\nstd::vector<Point<T>>\
    \ minkowski_sum(\n    std::vector<Point<T>> first,\n    std::vector<Point<T>>\
    \ second,\n    long double eps = 1e-12L\n) {\n    assert(!first.empty());\n  \
    \  assert(!second.empty());\n    first = convex_polygon_detail::normalize_convex_boundary(\n\
    \        std::move(first),\n        eps\n    );\n    second = convex_polygon_detail::normalize_convex_boundary(\n\
    \        std::move(second),\n        eps\n    );\n\n    if (first.size() == 1\
    \ || second.size() == 1) {\n        if (second.size() == 1) std::swap(first, second);\n\
    \        for (Point<T>& point : second) point += first[0];\n        return convex_polygon_detail::normalize_convex_boundary(\n\
    \            std::move(second),\n            eps\n        );\n    }\n\n    std::vector<Point<T>>\
    \ first_edges;\n    std::vector<Point<T>> second_edges;\n    first_edges.reserve(first.size());\n\
    \    second_edges.reserve(second.size());\n    for (std::size_t index = 0; index\
    \ < first.size(); ++index) {\n        first_edges.push_back(\n            first[(index\
    \ + 1) % first.size()] - first[index]\n        );\n    }\n    for (std::size_t\
    \ index = 0; index < second.size(); ++index) {\n        second_edges.push_back(\n\
    \            second[(index + 1) % second.size()] - second[index]\n        );\n\
    \    }\n\n    Point<T> current = first.front() + second.front();\n    std::vector<Point<T>>\
    \ result;\n    result.reserve(first.size() + second.size());\n    result.push_back(current);\n\
    \    std::size_t first_index = 0;\n    std::size_t second_index = 0;\n    while\
    \ (\n        first_index < first_edges.size() ||\n        second_index < second_edges.size()\n\
    \    ) {\n        Point<T> step;\n        if (first_index == first_edges.size())\
    \ {\n            step = second_edges[second_index++];\n        } else if (second_index\
    \ == second_edges.size()) {\n            step = first_edges[first_index++];\n\
    \        } else {\n            const auto turn = cross(\n                first_edges[first_index],\n\
    \                second_edges[second_index]\n            );\n            if (turn\
    \ > 0) {\n                step = first_edges[first_index++];\n            } else\
    \ if (turn < 0) {\n                step = second_edges[second_index++];\n    \
    \        } else {\n                step = first_edges[first_index++] +\n     \
    \                  second_edges[second_index++];\n            }\n        }\n \
    \       current += step;\n        if (\n            first_index < first_edges.size()\
    \ ||\n            second_index < second_edges.size()\n        ) {\n          \
    \  result.push_back(current);\n        }\n    }\n    return convex_polygon_detail::normalize_convex_boundary(\n\
    \        std::move(result),\n        eps\n    );\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_MINKOWSKI_SUM_HPP\n"
  dependsOn:
  - geometry/detail/convex_polygon_normalize.hpp
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/minkowski_sum.hpp
  requiredBy:
  - geometry/all.hpp
  - geometry/convex_polygon.hpp
  timestamp: '2026-08-08 16:10:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/polygon_operations.test.cpp
  - verify/geometry/convex_polygon.test.cpp
  - verify/geometry/is_convex_polygon.test.cpp
  - verify/geometry/centroid.test.cpp
  - verify/geometry/steiner_convex_decomposition.test.cpp
  - verify/geometry/convex_diameter.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/convex_decomposition.test.cpp
  - verify/geometry/minkowski_sum.test.cpp
documentation_of: geometry/minkowski_sum.hpp
layout: document
title: Minkowski Sum
---

## Overview

`minkowski_sum` constructs the Minkowski sum of two ordered convex polygons:
the set of all points `a + b` for a point `a` in the first polygon and a point
`b` in the second polygon.

The input boundaries may be clockwise or counterclockwise and may contain a
repeated closing point, consecutive duplicates, or redundant collinear
vertices. Points and segments are supported as degenerate convex polygons.

## Function

```cpp
template <Coordinate T>
std::vector<Point<T>> minkowski_sum(
    std::vector<Point<T>> first,
    std::vector<Point<T>> second,
    long double eps = 1e-12L
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `minkowski_sum(first, second, eps)` | Returns the normalized boundary of the Minkowski sum. | $O(N+M)$ time and memory |

Both inputs must be nonempty and must describe convex boundaries in cyclic
order. The result is counterclockwise, starts at its lowest `(y, x)` vertex,
has no repeated closing point, and omits redundant collinear vertices.

The return type keeps the input coordinate type. Coordinate addition and edge
subtraction must therefore fit `T`. Geometric predicates use `wide_type<T>`;
integral coordinates consequently use signed 128-bit cross products. For
floating-point coordinates, `eps` controls normalization of collinear points.

## Example

```cpp
#include "geometry/minkowski_sum.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> square;
    square.emplace_back(0, 0);
    square.emplace_back(2, 0);
    square.emplace_back(2, 2);
    square.emplace_back(0, 2);

    std::vector<Point> segment;
    segment.emplace_back(0, 0);
    segment.emplace_back(3, 0);

    const auto sum = m1une::geometry::minkowski_sum(square, segment);
    for (const Point& point : sum) {
        std::cout << point.x << " " << point.y << "\n";
    }
}
```
