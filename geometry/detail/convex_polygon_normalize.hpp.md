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
  - icon: ':heavy_check_mark:'
    path: geometry/convex_polygon.hpp
    title: Convex Polygons
  - icon: ':heavy_check_mark:'
    path: geometry/minkowski_sum.hpp
    title: Minkowski Sum
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
  bundledCode: "#line 1 \"geometry/detail/convex_polygon_normalize.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"geometry/point.hpp\"\n\n\n\n#include <cmath>\n#include <concepts>\n#include\
    \ <cassert>\n#include <type_traits>\n\nnamespace m1une {\nnamespace geometry {\n\
    \ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T> && !std::same_as<std::remove_cv_t<T>,\
    \ bool>;\n\ntemplate <Coordinate T>\nusing wide_type = std::conditional_t<std::integral<T>,\
    \ __int128_t, long double>;\n\ntemplate <Coordinate T>\nstruct Point {\n    T\
    \ x;\n    T y;\n\n    constexpr Point() : x(0), y(0) {}\n    constexpr Point(T\
    \ x_value, T y_value) : x(x_value), y(y_value) {}\n\n    template <Coordinate\
    \ U>\n    explicit constexpr Point(const Point<U>& other)\n        : x(static_cast<T>(other.x)),\
    \ y(static_cast<T>(other.y)) {}\n\n    constexpr Point& operator+=(const Point&\
    \ other) {\n        x += other.x;\n        y += other.y;\n        return *this;\n\
    \    }\n\n    constexpr Point& operator-=(const Point& other) {\n        x -=\
    \ other.x;\n        y -= other.y;\n        return *this;\n    }\n\n    constexpr\
    \ Point operator+() const {\n        return *this;\n    }\n\n    constexpr Point\
    \ operator-() const {\n        return Point(-x, -y);\n    }\n\n    friend constexpr\
    \ Point operator+(Point left, const Point& right) {\n        return left += right;\n\
    \    }\n\n    friend constexpr Point operator-(Point left, const Point& right)\
    \ {\n        return left -= right;\n    }\n\n    friend constexpr bool operator==(const\
    \ Point&, const Point&) = default;\n\n    friend constexpr bool operator<(const\
    \ Point& left, const Point& right) {\n        if (left.x != right.x) return left.x\
    \ < right.x;\n        return left.y < right.y;\n    }\n};\n\ntemplate <Coordinate\
    \ T>\nconstexpr Point<long double> centroid(const Point<T>& point) {\n    return\
    \ Point<long double>(point);\n}\n\ntemplate <Coordinate T, typename Scalar>\n\
    requires std::is_arithmetic_v<Scalar>\nconstexpr auto operator*(const Point<T>&\
    \ point, Scalar scalar) {\n    using Result = std::common_type_t<T, Scalar>;\n\
    \    return Point<Result>(\n        Result(point.x) * Result(scalar),\n      \
    \  Result(point.y) * Result(scalar)\n    );\n}\n\ntemplate <typename Scalar, Coordinate\
    \ T>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr auto operator*(Scalar scalar,\
    \ const Point<T>& point) {\n    return point * scalar;\n}\n\ntemplate <Coordinate\
    \ T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr auto operator/(const\
    \ Point<T>& point, Scalar scalar) {\n    using Result = std::common_type_t<T,\
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
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_DETAIL_CONVEX_POLYGON_NORMALIZE_HPP\n#define M1UNE_GEOMETRY_DETAIL_CONVEX_POLYGON_NORMALIZE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cstddef>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"../point.hpp\"\n\nnamespace m1une {\nnamespace geometry\
    \ {\nnamespace convex_polygon_detail {\n\ntemplate <Coordinate T>\nwide_type<T>\
    \ boundary_area2(const std::vector<Point<T>>& polygon) {\n    wide_type<T> result\
    \ = 0;\n    for (std::size_t index = 0; index < polygon.size(); ++index) {\n \
    \       result += cross(\n            polygon[index],\n            polygon[(index\
    \ + 1) % polygon.size()]\n        );\n    }\n    return result;\n}\n\ntemplate\
    \ <Coordinate T>\nstd::vector<Point<T>> normalize_convex_boundary(\n    std::vector<Point<T>>\
    \ polygon,\n    long double eps\n) {\n    if (polygon.size() >= 2 && polygon.front()\
    \ == polygon.back()) {\n        polygon.pop_back();\n    }\n    polygon.erase(\n\
    \        std::unique(polygon.begin(), polygon.end()),\n        polygon.end()\n\
    \    );\n    if (polygon.size() >= 2 && polygon.front() == polygon.back()) {\n\
    \        polygon.pop_back();\n    }\n    if (polygon.size() <= 1) return polygon;\n\
    \    if (\n        polygon.size() >= 3 &&\n        sign<T>(boundary_area2(polygon),\
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
    }  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_DETAIL_CONVEX_POLYGON_NORMALIZE_HPP\n"
  dependsOn:
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/detail/convex_polygon_normalize.hpp
  requiredBy:
  - geometry/all.hpp
  - geometry/minkowski_sum.hpp
  - geometry/convex_polygon.hpp
  timestamp: '2026-08-08 16:10:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/is_convex_polygon.test.cpp
  - verify/geometry/steiner_convex_decomposition.test.cpp
  - verify/geometry/convex_diameter.test.cpp
  - verify/geometry/centroid.test.cpp
  - verify/geometry/minkowski_sum.test.cpp
  - verify/geometry/polygon_operations.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/convex_decomposition.test.cpp
  - verify/geometry/convex_polygon.test.cpp
documentation_of: geometry/detail/convex_polygon_normalize.hpp
layout: document
redirect_from:
- /library/geometry/detail/convex_polygon_normalize.hpp
- /library/geometry/detail/convex_polygon_normalize.hpp.html
title: geometry/detail/convex_polygon_normalize.hpp
---
