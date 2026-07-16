---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/geometry/closest_pair.test.cpp
    title: verify/geometry/closest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/closest_pair.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\n#line 1 \"geometry/point.hpp\"\
    \n\n\n\n#include <cmath>\n#include <concepts>\n#include <cassert>\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace geometry {\n\ntemplate <typename T>\nconcept Coordinate\
    \ = std::is_arithmetic_v<T> && !std::same_as<std::remove_cv_t<T>, bool>;\n\ntemplate\
    \ <Coordinate T>\nusing wide_type = std::conditional_t<std::integral<T>, __int128_t,\
    \ long double>;\n\ntemplate <Coordinate T>\nstruct Point {\n    T x;\n    T y;\n\
    \n    constexpr Point() : x(0), y(0) {}\n    constexpr Point(T x_value, T y_value)\
    \ : x(x_value), y(y_value) {}\n\n    template <Coordinate U>\n    explicit constexpr\
    \ Point(const Point<U>& other)\n        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))\
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
    \    }\n};\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator*(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ * Result(scalar),\n        Result(point.y) * Result(scalar)\n    );\n}\n\ntemplate\
    \ <typename Scalar, Coordinate T>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr\
    \ auto operator*(Scalar scalar, const Point<T>& point) {\n    return point * scalar;\n\
    }\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator/(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ / Result(scalar),\n        Result(point.y) / Result(scalar)\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr wide_type<T> dot(const Point<T>& a, const Point<T>&\
    \ b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.x) + W(a.y) * W(b.y);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(const Point<T>& a,\
    \ const Point<T>& b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.y)\
    \ - W(a.y) * W(b.x);\n}\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(\n\
    \    const Point<T>& origin,\n    const Point<T>& a,\n    const Point<T>& b\n\
    ) {\n    using W = wide_type<T>;\n    W ax = W(a.x) - W(origin.x);\n    W ay =\
    \ W(a.y) - W(origin.y);\n    W bx = W(b.x) - W(origin.x);\n    W by = W(b.y) -\
    \ W(origin.y);\n    return ax * by - ay * bx;\n}\n\ntemplate <Coordinate T>\n\
    constexpr wide_type<T> norm2(const Point<T>& point) {\n    return dot(point, point);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> distance2(const Point<T>&\
    \ a, const Point<T>& b) {\n    using W = wide_type<T>;\n    W dx = W(a.x) - W(b.x);\n\
    \    W dy = W(a.y) - W(b.y);\n    return dx * dx + dy * dy;\n}\n\ntemplate <Coordinate\
    \ T>\nlong double norm(const Point<T>& point) {\n    return std::hypot(\n    \
    \    static_cast<long double>(point.x),\n        static_cast<long double>(point.y)\n\
    \    );\n}\n\ntemplate <Coordinate T>\nlong double distance(const Point<T>& a,\
    \ const Point<T>& b) {\n    return std::hypot(\n        static_cast<long double>(a.x)\
    \ - static_cast<long double>(b.x),\n        static_cast<long double>(a.y) - static_cast<long\
    \ double>(b.y)\n    );\n}\n\ntemplate <Coordinate T, typename M, typename N>\n\
    requires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>\nconstexpr Point<long\
    \ double> internal_division_point(\n    const Point<T>& a,\n    const Point<T>&\
    \ b,\n    M m,\n    N n\n) {\n    long double first_ratio = static_cast<long double>(m);\n\
    \    long double second_ratio = static_cast<long double>(n);\n    long double\
    \ denominator = first_ratio + second_ratio;\n    assert(denominator != 0);\n \
    \   Point<long double> first(a);\n    Point<long double> direction = Point<long\
    \ double>(b) - first;\n    return first + direction * (first_ratio / denominator);\n\
    }\n\ntemplate <Coordinate T, typename M, typename N>\nrequires std::is_arithmetic_v<M>\
    \ && std::is_arithmetic_v<N>\nconstexpr Point<long double> external_division_point(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    M m,\n    N n\n) {\n    long\
    \ double first_ratio = static_cast<long double>(m);\n    long double second_ratio\
    \ = static_cast<long double>(n);\n    long double denominator = first_ratio -\
    \ second_ratio;\n    assert(denominator != 0);\n    Point<long double> first(a);\n\
    \    Point<long double> direction = Point<long double>(b) - first;\n    return\
    \ first + direction * (first_ratio / denominator);\n}\n\ntemplate <Coordinate\
    \ T>\nconstexpr int sign(wide_type<T> value, long double eps = 1e-12L) {\n   \
    \ if constexpr (std::integral<T>) {\n        return (value > 0) - (value < 0);\n\
    \    } else {\n        return (value > eps) - (value < -eps);\n    }\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr int orientation(\n    const Point<T>& a,\n    const\
    \ Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n) {\n  \
    \  return sign<T>(cross(a, b, c), eps);\n}\n\ntemplate <Coordinate T>\nconstexpr\
    \ bool collinear(\n    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>&\
    \ c,\n    long double eps = 1e-12L\n) {\n    return orientation(a, b, c, eps)\
    \ == 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double> rotate(const Point<T>&\
    \ point, long double angle) {\n    long double cosine = std::cos(angle);\n   \
    \ long double sine = std::sin(angle);\n    return Point<long double>(\n      \
    \  static_cast<long double>(point.x) * cosine -\n            static_cast<long\
    \ double>(point.y) * sine,\n        static_cast<long double>(point.x) * sine +\n\
    \            static_cast<long double>(point.y) * cosine\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> normalized(const Point<T>& point) {\n   \
    \ long double length = norm(point);\n    assert(length != 0);\n    return Point<long\
    \ double>(\n        static_cast<long double>(point.x) / length,\n        static_cast<long\
    \ double>(point.y) / length\n    );\n}\n\n}  // namespace geometry\n}  // namespace\
    \ m1une\n\n\n#line 10 \"geometry/closest_pair.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\ntemplate <Coordinate T>\nstruct ClosestPair {\n    int first;\n\
    \    int second;\n    wide_type<T> distance_squared;\n};\n\n// Returns two distinct\
    \ original indices with minimum Euclidean distance.\ntemplate <Coordinate T>\n\
    std::optional<ClosestPair<T>> closest_pair(\n    const std::vector<Point<T>>&\
    \ points\n) {\n    const int n = int(points.size());\n    if (n < 2) return std::nullopt;\n\
    \n    struct IndexedPoint {\n        Point<T> point;\n        int index;\n   \
    \ };\n\n    std::vector<IndexedPoint> ordered;\n    ordered.reserve(n);\n    for\
    \ (int index = 0; index < n; index++) {\n        ordered.push_back(IndexedPoint{points[index],\
    \ index});\n    }\n    std::sort(\n        ordered.begin(),\n        ordered.end(),\n\
    \        [](const IndexedPoint& first, const IndexedPoint& second) {\n       \
    \     if (first.point < second.point) return true;\n            if (second.point\
    \ < first.point) return false;\n            return first.index < second.index;\n\
    \        }\n    );\n\n    std::optional<ClosestPair<T>> duplicate_result;\n  \
    \  for (int first = 0; first < n;) {\n        int last = first + 1;\n        while\
    \ (last < n && ordered[last].point == ordered[first].point) last++;\n        if\
    \ (last - first >= 2) {\n            int first_index = ordered[first].index;\n\
    \            int second_index = ordered[first + 1].index;\n            std::pair<int,\
    \ int> candidate(first_index, second_index);\n            if (\n             \
    \   !duplicate_result ||\n                candidate < std::pair(\n           \
    \         duplicate_result->first,\n                    duplicate_result->second\n\
    \                )\n            ) {\n                duplicate_result = ClosestPair<T>{\n\
    \                    first_index,\n                    second_index,\n       \
    \             wide_type<T>(0)\n                };\n            }\n        }\n\
    \        first = last;\n    }\n    if (duplicate_result) return duplicate_result;\n\
    \n    std::optional<ClosestPair<T>> result;\n    auto consider = [&result, &points](int\
    \ first, int second) {\n        if (second < first) std::swap(first, second);\n\
    \        wide_type<T> squared = distance2(points[first], points[second]);\n  \
    \      std::pair<int, int> candidate(first, second);\n        if (\n         \
    \   !result ||\n            squared < result->distance_squared ||\n          \
    \  (\n                squared == result->distance_squared &&\n               \
    \ candidate < std::pair(result->first, result->second)\n            )\n      \
    \  ) {\n            result = ClosestPair<T>{first, second, squared};\n       \
    \ }\n    };\n    consider(ordered[0].index, ordered[1].index);\n\n    auto by_y\
    \ = [](const IndexedPoint& first, const IndexedPoint& second) {\n        if (first.point.y\
    \ != second.point.y) {\n            return first.point.y < second.point.y;\n \
    \       }\n        if (first.point.x != second.point.x) {\n            return\
    \ first.point.x < second.point.x;\n        }\n        return first.index < second.index;\n\
    \    };\n\n    std::vector<IndexedPoint> buffer(n);\n    auto solve = [&](auto&&\
    \ self, int left, int right) -> void {\n        if (right - left <= 3) {\n   \
    \         for (int first = left; first < right; first++) {\n                for\
    \ (int second = first + 1; second < right; second++) {\n                    consider(ordered[first].index,\
    \ ordered[second].index);\n                }\n            }\n            std::sort(ordered.begin()\
    \ + left, ordered.begin() + right, by_y);\n            return;\n        }\n\n\
    \        int middle = (left + right) / 2;\n        T middle_x = ordered[middle].point.x;\n\
    \        self(self, left, middle);\n        self(self, middle, right);\n     \
    \   std::merge(\n            ordered.begin() + left,\n            ordered.begin()\
    \ + middle,\n            ordered.begin() + middle,\n            ordered.begin()\
    \ + right,\n            buffer.begin() + left,\n            by_y\n        );\n\
    \        std::copy(\n            buffer.begin() + left,\n            buffer.begin()\
    \ + right,\n            ordered.begin() + left\n        );\n\n        int strip_size\
    \ = 0;\n        for (int index = left; index < right; index++) {\n           \
    \ using W = wide_type<T>;\n            W dx = W(ordered[index].point.x) - W(middle_x);\n\
    \            if (result->distance_squared < dx * dx) continue;\n\n           \
    \ for (int previous = strip_size - 1; previous >= 0; previous--) {\n         \
    \       W dy = W(ordered[index].point.y) - W(buffer[previous].point.y);\n    \
    \            if (result->distance_squared < dy * dy) break;\n                consider(ordered[index].index,\
    \ buffer[previous].index);\n            }\n            buffer[strip_size++] =\
    \ ordered[index];\n        }\n    };\n    solve(solve, 0, n);\n    return result;\n\
    }\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_CLOSEST_PAIR_HPP\n#define M1UNE_GEOMETRY_CLOSEST_PAIR_HPP\
    \ 1\n\n#include <algorithm>\n#include <optional>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"point.hpp\"\n\nnamespace m1une {\nnamespace geometry\
    \ {\n\ntemplate <Coordinate T>\nstruct ClosestPair {\n    int first;\n    int\
    \ second;\n    wide_type<T> distance_squared;\n};\n\n// Returns two distinct original\
    \ indices with minimum Euclidean distance.\ntemplate <Coordinate T>\nstd::optional<ClosestPair<T>>\
    \ closest_pair(\n    const std::vector<Point<T>>& points\n) {\n    const int n\
    \ = int(points.size());\n    if (n < 2) return std::nullopt;\n\n    struct IndexedPoint\
    \ {\n        Point<T> point;\n        int index;\n    };\n\n    std::vector<IndexedPoint>\
    \ ordered;\n    ordered.reserve(n);\n    for (int index = 0; index < n; index++)\
    \ {\n        ordered.push_back(IndexedPoint{points[index], index});\n    }\n \
    \   std::sort(\n        ordered.begin(),\n        ordered.end(),\n        [](const\
    \ IndexedPoint& first, const IndexedPoint& second) {\n            if (first.point\
    \ < second.point) return true;\n            if (second.point < first.point) return\
    \ false;\n            return first.index < second.index;\n        }\n    );\n\n\
    \    std::optional<ClosestPair<T>> duplicate_result;\n    for (int first = 0;\
    \ first < n;) {\n        int last = first + 1;\n        while (last < n && ordered[last].point\
    \ == ordered[first].point) last++;\n        if (last - first >= 2) {\n       \
    \     int first_index = ordered[first].index;\n            int second_index =\
    \ ordered[first + 1].index;\n            std::pair<int, int> candidate(first_index,\
    \ second_index);\n            if (\n                !duplicate_result ||\n   \
    \             candidate < std::pair(\n                    duplicate_result->first,\n\
    \                    duplicate_result->second\n                )\n           \
    \ ) {\n                duplicate_result = ClosestPair<T>{\n                  \
    \  first_index,\n                    second_index,\n                    wide_type<T>(0)\n\
    \                };\n            }\n        }\n        first = last;\n    }\n\
    \    if (duplicate_result) return duplicate_result;\n\n    std::optional<ClosestPair<T>>\
    \ result;\n    auto consider = [&result, &points](int first, int second) {\n \
    \       if (second < first) std::swap(first, second);\n        wide_type<T> squared\
    \ = distance2(points[first], points[second]);\n        std::pair<int, int> candidate(first,\
    \ second);\n        if (\n            !result ||\n            squared < result->distance_squared\
    \ ||\n            (\n                squared == result->distance_squared &&\n\
    \                candidate < std::pair(result->first, result->second)\n      \
    \      )\n        ) {\n            result = ClosestPair<T>{first, second, squared};\n\
    \        }\n    };\n    consider(ordered[0].index, ordered[1].index);\n\n    auto\
    \ by_y = [](const IndexedPoint& first, const IndexedPoint& second) {\n       \
    \ if (first.point.y != second.point.y) {\n            return first.point.y < second.point.y;\n\
    \        }\n        if (first.point.x != second.point.x) {\n            return\
    \ first.point.x < second.point.x;\n        }\n        return first.index < second.index;\n\
    \    };\n\n    std::vector<IndexedPoint> buffer(n);\n    auto solve = [&](auto&&\
    \ self, int left, int right) -> void {\n        if (right - left <= 3) {\n   \
    \         for (int first = left; first < right; first++) {\n                for\
    \ (int second = first + 1; second < right; second++) {\n                    consider(ordered[first].index,\
    \ ordered[second].index);\n                }\n            }\n            std::sort(ordered.begin()\
    \ + left, ordered.begin() + right, by_y);\n            return;\n        }\n\n\
    \        int middle = (left + right) / 2;\n        T middle_x = ordered[middle].point.x;\n\
    \        self(self, left, middle);\n        self(self, middle, right);\n     \
    \   std::merge(\n            ordered.begin() + left,\n            ordered.begin()\
    \ + middle,\n            ordered.begin() + middle,\n            ordered.begin()\
    \ + right,\n            buffer.begin() + left,\n            by_y\n        );\n\
    \        std::copy(\n            buffer.begin() + left,\n            buffer.begin()\
    \ + right,\n            ordered.begin() + left\n        );\n\n        int strip_size\
    \ = 0;\n        for (int index = left; index < right; index++) {\n           \
    \ using W = wide_type<T>;\n            W dx = W(ordered[index].point.x) - W(middle_x);\n\
    \            if (result->distance_squared < dx * dx) continue;\n\n           \
    \ for (int previous = strip_size - 1; previous >= 0; previous--) {\n         \
    \       W dy = W(ordered[index].point.y) - W(buffer[previous].point.y);\n    \
    \            if (result->distance_squared < dy * dy) break;\n                consider(ordered[index].index,\
    \ buffer[previous].index);\n            }\n            buffer[strip_size++] =\
    \ ordered[index];\n        }\n    };\n    solve(solve, 0, n);\n    return result;\n\
    }\n\n}  // namespace geometry\n}  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_CLOSEST_PAIR_HPP\n"
  dependsOn:
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/closest_pair.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-11 20:28:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/closest_pair.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
documentation_of: geometry/closest_pair.hpp
layout: document
title: Closest Pair of Points
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
