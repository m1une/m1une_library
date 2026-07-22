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
    path: verify/geometry/centroid.test.cpp
    title: verify/geometry/centroid.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/rectangle_union_area.test.cpp
    title: verify/geometry/rectangle_union_area.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/rectangle_union_area.hpp\"\n\n\n\n#line 1 \"geometry/point.hpp\"\
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
    \ geometry\n}  // namespace m1une\n\n\n#line 5 \"geometry/rectangle_union_area.hpp\"\
    \n\n#include <algorithm>\n#line 8 \"geometry/rectangle_union_area.hpp\"\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate\
    \ T>\nstruct AxisAlignedRectangle {\n    T left;\n    T bottom;\n    T right;\n\
    \    T top;\n\n    constexpr AxisAlignedRectangle()\n        : left(0), bottom(0),\
    \ right(0), top(0) {}\n\n    constexpr AxisAlignedRectangle(\n        T left_value,\n\
    \        T bottom_value,\n        T right_value,\n        T top_value\n    )\n\
    \        : left(left_value),\n          bottom(bottom_value),\n          right(right_value),\n\
    \          top(top_value) {}\n\n    friend constexpr bool operator==(\n      \
    \  const AxisAlignedRectangle&,\n        const AxisAlignedRectangle&\n    ) =\
    \ default;\n};\n\nnamespace rectangle_union_area_detail {\n\ntemplate <Coordinate\
    \ T>\nstruct Event {\n    T x;\n    T bottom;\n    T top;\n    int delta;\n\n\
    \    Event(T x_value, T bottom_value, T top_value, int delta_value)\n        :\
    \ x(x_value),\n          bottom(bottom_value),\n          top(top_value),\n  \
    \        delta(delta_value) {}\n};\n\ntemplate <Coordinate T>\nstruct CoveredLengthTree\
    \ {\n    using Wide = wide_type<T>;\n\n    int interval_count;\n    const std::vector<T>&\
    \ coordinates;\n    std::vector<int> cover;\n    std::vector<Wide> covered;\n\n\
    \    explicit CoveredLengthTree(const std::vector<T>& values)\n        : interval_count(std::max(0,\
    \ int(values.size()) - 1)),\n          coordinates(values),\n          cover(std::max(1,\
    \ 4 * interval_count), 0),\n          covered(std::max(1, 4 * interval_count),\
    \ Wide(0)) {}\n\n    void pull(int node, int left, int right) {\n        if (cover[node]\
    \ > 0) {\n            covered[node] =\n                Wide(coordinates[right])\
    \ - Wide(coordinates[left]);\n        } else if (right - left == 1) {\n      \
    \      covered[node] = 0;\n        } else {\n            covered[node] = covered[2\
    \ * node] + covered[2 * node + 1];\n        }\n    }\n\n    void add(\n      \
    \  int query_left,\n        int query_right,\n        int delta,\n        int\
    \ node,\n        int left,\n        int right\n    ) {\n        if (query_right\
    \ <= left || right <= query_left) return;\n        if (query_left <= left && right\
    \ <= query_right) {\n            cover[node] += delta;\n            assert(cover[node]\
    \ >= 0);\n            pull(node, left, right);\n            return;\n        }\n\
    \        int middle = (left + right) / 2;\n        add(query_left, query_right,\
    \ delta, 2 * node, left, middle);\n        add(\n            query_left,\n   \
    \         query_right,\n            delta,\n            2 * node + 1,\n      \
    \      middle,\n            right\n        );\n        pull(node, left, right);\n\
    \    }\n\n    void add(int left, int right, int delta) {\n        if (left >=\
    \ right) return;\n        assert(0 <= left && left < right && right <= interval_count);\n\
    \        add(left, right, delta, 1, 0, interval_count);\n    }\n\n    Wide length()\
    \ const {\n        return interval_count == 0 ? Wide(0) : covered[1];\n    }\n\
    };\n\n}  // namespace rectangle_union_area_detail\n\ntemplate <Coordinate T>\n\
    wide_type<T> rectangle_union_area(\n    const std::vector<AxisAlignedRectangle<T>>&\
    \ rectangles\n) {\n    using Wide = wide_type<T>;\n    using Event = rectangle_union_area_detail::Event<T>;\n\
    \n    std::vector<Event> events;\n    std::vector<T> y_coordinates;\n    events.reserve(2\
    \ * rectangles.size());\n    y_coordinates.reserve(2 * rectangles.size());\n \
    \   for (const AxisAlignedRectangle<T>& rectangle : rectangles) {\n        assert(rectangle.left\
    \ <= rectangle.right);\n        assert(rectangle.bottom <= rectangle.top);\n \
    \       if (\n            rectangle.left == rectangle.right ||\n            rectangle.bottom\
    \ == rectangle.top\n        ) {\n            continue;\n        }\n        events.emplace_back(\n\
    \            rectangle.left,\n            rectangle.bottom,\n            rectangle.top,\n\
    \            1\n        );\n        events.emplace_back(\n            rectangle.right,\n\
    \            rectangle.bottom,\n            rectangle.top,\n            -1\n \
    \       );\n        y_coordinates.push_back(rectangle.bottom);\n        y_coordinates.push_back(rectangle.top);\n\
    \    }\n    if (events.empty()) return Wide(0);\n\n    std::sort(y_coordinates.begin(),\
    \ y_coordinates.end());\n    y_coordinates.erase(\n        std::unique(y_coordinates.begin(),\
    \ y_coordinates.end()),\n        y_coordinates.end()\n    );\n    std::sort(events.begin(),\
    \ events.end(), [](const Event& a, const Event& b) {\n        return a.x < b.x;\n\
    \    });\n\n    rectangle_union_area_detail::CoveredLengthTree<T> tree(y_coordinates);\n\
    \    Wide area = 0;\n    T previous_x = events.front().x;\n    int event_index\
    \ = 0;\n    while (event_index < int(events.size())) {\n        T x = events[event_index].x;\n\
    \        area += tree.length() * (Wide(x) - Wide(previous_x));\n\n        int\
    \ next = event_index;\n        while (next < int(events.size()) && events[next].x\
    \ == x) {\n            int bottom = int(\n                std::lower_bound(\n\
    \                    y_coordinates.begin(),\n                    y_coordinates.end(),\n\
    \                    events[next].bottom\n                ) - y_coordinates.begin()\n\
    \            );\n            int top = int(\n                std::lower_bound(\n\
    \                    y_coordinates.begin(),\n                    y_coordinates.end(),\n\
    \                    events[next].top\n                ) - y_coordinates.begin()\n\
    \            );\n            tree.add(bottom, top, events[next].delta);\n    \
    \        next++;\n        }\n        previous_x = x;\n        event_index = next;\n\
    \    }\n    return area;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_GEOMETRY_RECTANGLE_UNION_AREA_HPP\n#define M1UNE_GEOMETRY_RECTANGLE_UNION_AREA_HPP\
    \ 1\n\n#include \"point.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate\
    \ T>\nstruct AxisAlignedRectangle {\n    T left;\n    T bottom;\n    T right;\n\
    \    T top;\n\n    constexpr AxisAlignedRectangle()\n        : left(0), bottom(0),\
    \ right(0), top(0) {}\n\n    constexpr AxisAlignedRectangle(\n        T left_value,\n\
    \        T bottom_value,\n        T right_value,\n        T top_value\n    )\n\
    \        : left(left_value),\n          bottom(bottom_value),\n          right(right_value),\n\
    \          top(top_value) {}\n\n    friend constexpr bool operator==(\n      \
    \  const AxisAlignedRectangle&,\n        const AxisAlignedRectangle&\n    ) =\
    \ default;\n};\n\nnamespace rectangle_union_area_detail {\n\ntemplate <Coordinate\
    \ T>\nstruct Event {\n    T x;\n    T bottom;\n    T top;\n    int delta;\n\n\
    \    Event(T x_value, T bottom_value, T top_value, int delta_value)\n        :\
    \ x(x_value),\n          bottom(bottom_value),\n          top(top_value),\n  \
    \        delta(delta_value) {}\n};\n\ntemplate <Coordinate T>\nstruct CoveredLengthTree\
    \ {\n    using Wide = wide_type<T>;\n\n    int interval_count;\n    const std::vector<T>&\
    \ coordinates;\n    std::vector<int> cover;\n    std::vector<Wide> covered;\n\n\
    \    explicit CoveredLengthTree(const std::vector<T>& values)\n        : interval_count(std::max(0,\
    \ int(values.size()) - 1)),\n          coordinates(values),\n          cover(std::max(1,\
    \ 4 * interval_count), 0),\n          covered(std::max(1, 4 * interval_count),\
    \ Wide(0)) {}\n\n    void pull(int node, int left, int right) {\n        if (cover[node]\
    \ > 0) {\n            covered[node] =\n                Wide(coordinates[right])\
    \ - Wide(coordinates[left]);\n        } else if (right - left == 1) {\n      \
    \      covered[node] = 0;\n        } else {\n            covered[node] = covered[2\
    \ * node] + covered[2 * node + 1];\n        }\n    }\n\n    void add(\n      \
    \  int query_left,\n        int query_right,\n        int delta,\n        int\
    \ node,\n        int left,\n        int right\n    ) {\n        if (query_right\
    \ <= left || right <= query_left) return;\n        if (query_left <= left && right\
    \ <= query_right) {\n            cover[node] += delta;\n            assert(cover[node]\
    \ >= 0);\n            pull(node, left, right);\n            return;\n        }\n\
    \        int middle = (left + right) / 2;\n        add(query_left, query_right,\
    \ delta, 2 * node, left, middle);\n        add(\n            query_left,\n   \
    \         query_right,\n            delta,\n            2 * node + 1,\n      \
    \      middle,\n            right\n        );\n        pull(node, left, right);\n\
    \    }\n\n    void add(int left, int right, int delta) {\n        if (left >=\
    \ right) return;\n        assert(0 <= left && left < right && right <= interval_count);\n\
    \        add(left, right, delta, 1, 0, interval_count);\n    }\n\n    Wide length()\
    \ const {\n        return interval_count == 0 ? Wide(0) : covered[1];\n    }\n\
    };\n\n}  // namespace rectangle_union_area_detail\n\ntemplate <Coordinate T>\n\
    wide_type<T> rectangle_union_area(\n    const std::vector<AxisAlignedRectangle<T>>&\
    \ rectangles\n) {\n    using Wide = wide_type<T>;\n    using Event = rectangle_union_area_detail::Event<T>;\n\
    \n    std::vector<Event> events;\n    std::vector<T> y_coordinates;\n    events.reserve(2\
    \ * rectangles.size());\n    y_coordinates.reserve(2 * rectangles.size());\n \
    \   for (const AxisAlignedRectangle<T>& rectangle : rectangles) {\n        assert(rectangle.left\
    \ <= rectangle.right);\n        assert(rectangle.bottom <= rectangle.top);\n \
    \       if (\n            rectangle.left == rectangle.right ||\n            rectangle.bottom\
    \ == rectangle.top\n        ) {\n            continue;\n        }\n        events.emplace_back(\n\
    \            rectangle.left,\n            rectangle.bottom,\n            rectangle.top,\n\
    \            1\n        );\n        events.emplace_back(\n            rectangle.right,\n\
    \            rectangle.bottom,\n            rectangle.top,\n            -1\n \
    \       );\n        y_coordinates.push_back(rectangle.bottom);\n        y_coordinates.push_back(rectangle.top);\n\
    \    }\n    if (events.empty()) return Wide(0);\n\n    std::sort(y_coordinates.begin(),\
    \ y_coordinates.end());\n    y_coordinates.erase(\n        std::unique(y_coordinates.begin(),\
    \ y_coordinates.end()),\n        y_coordinates.end()\n    );\n    std::sort(events.begin(),\
    \ events.end(), [](const Event& a, const Event& b) {\n        return a.x < b.x;\n\
    \    });\n\n    rectangle_union_area_detail::CoveredLengthTree<T> tree(y_coordinates);\n\
    \    Wide area = 0;\n    T previous_x = events.front().x;\n    int event_index\
    \ = 0;\n    while (event_index < int(events.size())) {\n        T x = events[event_index].x;\n\
    \        area += tree.length() * (Wide(x) - Wide(previous_x));\n\n        int\
    \ next = event_index;\n        while (next < int(events.size()) && events[next].x\
    \ == x) {\n            int bottom = int(\n                std::lower_bound(\n\
    \                    y_coordinates.begin(),\n                    y_coordinates.end(),\n\
    \                    events[next].bottom\n                ) - y_coordinates.begin()\n\
    \            );\n            int top = int(\n                std::lower_bound(\n\
    \                    y_coordinates.begin(),\n                    y_coordinates.end(),\n\
    \                    events[next].top\n                ) - y_coordinates.begin()\n\
    \            );\n            tree.add(bottom, top, events[next].delta);\n    \
    \        next++;\n        }\n        previous_x = x;\n        event_index = next;\n\
    \    }\n    return area;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\
    \n#endif  // M1UNE_GEOMETRY_RECTANGLE_UNION_AREA_HPP\n"
  dependsOn:
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/rectangle_union_area.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-22 02:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/rectangle_union_area.test.cpp
  - verify/geometry/centroid.test.cpp
documentation_of: geometry/rectangle_union_area.hpp
layout: document
title: Area of Union of Rectangles
---

## Overview

`rectangle_union_area` returns the area covered by at least one axis-aligned
rectangle. Overlaps are counted once. Coordinates may be negative, rectangles
may touch, and zero-width or zero-height rectangles contribute no area.

The implementation sweeps rectangle edges from left to right. A segment tree
over compressed y-coordinates maintains the total y-length currently covered.
Between consecutive x-events, that length is multiplied by the x-distance.

## Interface

```cpp
template <Coordinate T>
struct AxisAlignedRectangle {
    T left;
    T bottom;
    T right;
    T top;
};

template <Coordinate T>
wide_type<T> rectangle_union_area(
    const std::vector<AxisAlignedRectangle<T>>& rectangles
);
```

| Member / Function | Complexity | Description |
| --- | --- | --- |
| `AxisAlignedRectangle<T>()` | $O(1)$ | Constructs a zero-area rectangle at the origin. |
| `AxisAlignedRectangle<T>(left, bottom, right, top)` | $O(1)$ | Constructs `[left, right]` by `[bottom, top]`. |
| `rectangle_union_area(rectangles)` | $O(N\log N)$ time and $O(N)$ memory | Returns the union area without modifying the input. |

The constructor coordinates must satisfy `left <= right` and `bottom <= top`.
This is checked when the area is calculated. Boundary inclusion does not affect
area; the implementation treats rectangles as half-open during the sweep.

For integral `T`, `wide_type<T>` is signed `__int128_t`, preventing overflow
in coordinate subtraction and multiplication. For floating-point `T`, the
return type is `long double`.

## Example

```cpp
#include "geometry/rectangle_union_area.hpp"

#include <iostream>
#include <vector>

int main() {
    using Rectangle = m1une::geometry::AxisAlignedRectangle<long long>;
    std::vector<Rectangle> rectangles;
    rectangles.emplace_back(0, 0, 4, 3);
    rectangles.emplace_back(2, 1, 6, 5);

    long long area = static_cast<long long>(
        m1une::geometry::rectangle_union_area(rectangles)
    );
    std::cout << area << "\n"; // 24
}
```
