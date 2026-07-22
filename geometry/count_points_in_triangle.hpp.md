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
    path: verify/geometry/count_points_in_triangle.test.cpp
    title: verify/geometry/count_points_in_triangle.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/count_points_in_triangle.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include\
    \ <limits>\n#include <numeric>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"geometry/point.hpp\"\n\n\n\n#include <cmath>\n#line 7 \"geometry/point.hpp\"\
    \n#include <type_traits>\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate\
    \ <typename T>\nconcept Coordinate = std::is_arithmetic_v<T> && !std::same_as<std::remove_cv_t<T>,\
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
    \ geometry\n}  // namespace m1une\n\n\n#line 14 \"geometry/count_points_in_triangle.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\nnamespace count_points_in_triangle_detail\
    \ {\n\nclass FenwickTree {\n   private:\n    std::vector<int> values;\n\n   public:\n\
    \    explicit FenwickTree(std::size_t size) : values(size, 0) {}\n\n    void add(std::size_t\
    \ position) {\n        for (\n            ++position;\n            position <=\
    \ values.size();\n            position += position & -position\n        ) {\n\
    \            values[position - 1]++;\n        }\n    }\n\n    int prefix_sum(std::size_t\
    \ right) const {\n        int result = 0;\n        for (; right > 0; right -=\
    \ right & -right) {\n            result += values[right - 1];\n        }\n   \
    \     return result;\n    }\n};\n\ntemplate <std::integral T>\nstruct SweepItem\
    \ {\n    using Wide = wide_type<T>;\n\n    Wide x;\n    Wide y;\n    int index;\n\
    \    int kind;\n};\n\n}  // namespace count_points_in_triangle_detail\n\ntemplate\
    \ <std::integral T>\nclass CountPointsInTriangle {\n   private:\n    using Wide\
    \ = wide_type<T>;\n    using SweepItem = count_points_in_triangle_detail::SweepItem<T>;\n\
    \n    static constexpr int before_counted_points = 0;\n    static constexpr int\
    \ counted_point = 1;\n    static constexpr int after_counted_points = 2;\n\n \
    \   std::vector<Point<T>> vertices;\n    std::vector<int> horizontal_left;\n \
    \   std::vector<int> horizontal_equal;\n    std::vector<std::vector<int>> edge_left;\n\
    \    std::vector<std::vector<int>> edge_equal;\n\n    static bool yx_less(const\
    \ Point<T>& first, const Point<T>& second) {\n        if (first.y != second.y)\
    \ return first.y < second.y;\n        return first.x < second.x;\n    }\n\n  \
    \  SweepItem make_item(\n        const Point<T>& origin,\n        const Point<T>&\
    \ point,\n        int index,\n        int kind\n    ) const {\n        return\
    \ SweepItem{\n            Wide(point.x) - Wide(origin.x),\n            Wide(point.y)\
    \ - Wide(origin.y),\n            index,\n            kind\n        };\n    }\n\
    \n    void build(const std::vector<Point<T>>& counted_points) {\n        const\
    \ int vertex_count = int(vertices.size());\n        const int counted_point_count\
    \ = int(counted_points.size());\n        for (int anchor = 0; anchor < vertex_count;\
    \ ++anchor) {\n            for (const Point<T>& point : counted_points) {\n  \
    \              if (point.y != vertices[anchor].y) continue;\n                if\
    \ (point.x < vertices[anchor].x) {\n                    horizontal_left[anchor]++;\n\
    \                } else if (point.x == vertices[anchor].x) {\n               \
    \     horizontal_equal[anchor]++;\n                }\n            }\n\n      \
    \      std::vector<SweepItem> items;\n            items.reserve(2 * vertices.size()\
    \ + counted_points.size());\n            for (int index = 0; index < vertex_count;\
    \ ++index) {\n                if (vertices[anchor].y < vertices[index].y) {\n\
    \                    items.push_back(make_item(\n                        vertices[anchor],\n\
    \                        vertices[index],\n                        index,\n  \
    \                      before_counted_points\n                    ));\n      \
    \          }\n            }\n            for (int index = 0; index < counted_point_count;\
    \ ++index) {\n                if (vertices[anchor].y < counted_points[index].y)\
    \ {\n                    items.push_back(make_item(\n                        vertices[anchor],\n\
    \                        counted_points[index],\n                        index,\n\
    \                        counted_point\n                    ));\n            \
    \    }\n            }\n            for (int index = 0; index < vertex_count; ++index)\
    \ {\n                if (vertices[anchor].y < vertices[index].y) {\n         \
    \           items.push_back(make_item(\n                        vertices[anchor],\n\
    \                        vertices[index],\n                        index,\n  \
    \                      after_counted_points\n                    ));\n       \
    \         }\n            }\n\n            std::sort(\n                items.begin(),\n\
    \                items.end(),\n                [](const SweepItem& first, const\
    \ SweepItem& second) {\n                    const Wide determinant =\n       \
    \                 first.x * second.y - first.y * second.x;\n                 \
    \   if (determinant != 0) return determinant < 0;\n                    return\
    \ first.kind < second.kind;\n                }\n            );\n\n           \
    \ std::vector<std::size_t> height_order(items.size());\n            std::iota(height_order.begin(),\
    \ height_order.end(), 0);\n            std::sort(\n                height_order.begin(),\n\
    \                height_order.end(),\n                [&items](std::size_t first,\
    \ std::size_t second) {\n                    if (items[first].y != items[second].y)\
    \ {\n                        return items[first].y < items[second].y;\n      \
    \              }\n                    return items[first].kind % 2 < items[second].kind\
    \ % 2;\n                }\n            );\n\n            count_points_in_triangle_detail::FenwickTree\
    \ fenwick(items.size());\n            for (std::size_t position : height_order)\
    \ {\n                const SweepItem& item = items[position];\n              \
    \  if (item.kind == before_counted_points) {\n                    edge_left[anchor][item.index]\
    \ =\n                        fenwick.prefix_sum(position + 1);\n             \
    \   } else if (item.kind == counted_point) {\n                    fenwick.add(position);\n\
    \                } else {\n                    edge_equal[anchor][item.index]\
    \ =\n                        fenwick.prefix_sum(position + 1);\n             \
    \   }\n            }\n            for (int index = 0; index < vertex_count; ++index)\
    \ {\n                edge_equal[anchor][index] -= edge_left[anchor][index];\n\
    \            }\n        }\n    }\n\n   public:\n    CountPointsInTriangle(\n \
    \       const std::vector<Point<T>>& triangle_vertices,\n        const std::vector<Point<T>>&\
    \ counted_points\n    )\n        : vertices(triangle_vertices),\n          horizontal_left(vertices.size(),\
    \ 0),\n          horizontal_equal(vertices.size(), 0),\n          edge_left(vertices.size(),\
    \ std::vector<int>(vertices.size(), 0)),\n          edge_equal(vertices.size(),\
    \ std::vector<int>(vertices.size(), 0)) {\n        assert(\n            vertices.size()\
    \ <=\n            static_cast<std::size_t>(std::numeric_limits<int>::max())\n\
    \        );\n        assert(\n            counted_points.size() <=\n         \
    \   static_cast<std::size_t>(std::numeric_limits<int>::max())\n        );\n  \
    \      build(counted_points);\n    }\n\n    int query(int first, int second, int\
    \ third) const {\n        const int size = int(vertices.size());\n        assert(0\
    \ <= first && first < size);\n        assert(0 <= second && second < size);\n\
    \        assert(0 <= third && third < size);\n\n        if (yx_less(vertices[second],\
    \ vertices[first])) {\n            std::swap(first, second);\n        }\n    \
    \    if (yx_less(vertices[third], vertices[second])) {\n            std::swap(second,\
    \ third);\n        }\n        if (yx_less(vertices[second], vertices[first]))\
    \ {\n            std::swap(first, second);\n        }\n\n        const Wide determinant\
    \ = cross(\n            vertices[first],\n            vertices[second],\n    \
    \        vertices[third]\n        );\n        if (determinant == 0) return 0;\n\
    \n        long long result;\n        if (vertices[first].y == vertices[second].y)\
    \ {\n            result =\n                static_cast<long long>(edge_left[second][third])\
    \ -\n                edge_left[first][third] -\n                edge_equal[first][third];\n\
    \        } else if (vertices[second].y == vertices[third].y) {\n            result\
    \ =\n                static_cast<long long>(edge_left[first][third]) -\n     \
    \           edge_left[first][second] -\n                edge_equal[first][second];\n\
    \        } else if (determinant < 0) {\n            result =\n               \
    \ static_cast<long long>(edge_left[first][third]) -\n                edge_left[second][third]\
    \ -\n                edge_equal[second][third] -\n                edge_left[first][second]\
    \ -\n                edge_equal[first][second] -\n                horizontal_left[second]\
    \ -\n                horizontal_equal[second];\n        } else {\n           \
    \ result =\n                static_cast<long long>(edge_left[first][second]) +\n\
    \                edge_left[second][third] +\n                horizontal_left[second]\
    \ -\n                edge_left[first][third] -\n                edge_equal[first][third];\n\
    \        }\n        assert(\n            0 <= result &&\n            result <=\
    \ std::numeric_limits<int>::max()\n        );\n        return int(result);\n \
    \   }\n};\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_COUNT_POINTS_IN_TRIANGLE_HPP\n#define M1UNE_GEOMETRY_COUNT_POINTS_IN_TRIANGLE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <cstddef>\n#include <limits>\n#include <numeric>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"point.hpp\"\n\nnamespace m1une {\nnamespace geometry\
    \ {\n\nnamespace count_points_in_triangle_detail {\n\nclass FenwickTree {\n  \
    \ private:\n    std::vector<int> values;\n\n   public:\n    explicit FenwickTree(std::size_t\
    \ size) : values(size, 0) {}\n\n    void add(std::size_t position) {\n       \
    \ for (\n            ++position;\n            position <= values.size();\n   \
    \         position += position & -position\n        ) {\n            values[position\
    \ - 1]++;\n        }\n    }\n\n    int prefix_sum(std::size_t right) const {\n\
    \        int result = 0;\n        for (; right > 0; right -= right & -right) {\n\
    \            result += values[right - 1];\n        }\n        return result;\n\
    \    }\n};\n\ntemplate <std::integral T>\nstruct SweepItem {\n    using Wide =\
    \ wide_type<T>;\n\n    Wide x;\n    Wide y;\n    int index;\n    int kind;\n};\n\
    \n}  // namespace count_points_in_triangle_detail\n\ntemplate <std::integral T>\n\
    class CountPointsInTriangle {\n   private:\n    using Wide = wide_type<T>;\n \
    \   using SweepItem = count_points_in_triangle_detail::SweepItem<T>;\n\n    static\
    \ constexpr int before_counted_points = 0;\n    static constexpr int counted_point\
    \ = 1;\n    static constexpr int after_counted_points = 2;\n\n    std::vector<Point<T>>\
    \ vertices;\n    std::vector<int> horizontal_left;\n    std::vector<int> horizontal_equal;\n\
    \    std::vector<std::vector<int>> edge_left;\n    std::vector<std::vector<int>>\
    \ edge_equal;\n\n    static bool yx_less(const Point<T>& first, const Point<T>&\
    \ second) {\n        if (first.y != second.y) return first.y < second.y;\n   \
    \     return first.x < second.x;\n    }\n\n    SweepItem make_item(\n        const\
    \ Point<T>& origin,\n        const Point<T>& point,\n        int index,\n    \
    \    int kind\n    ) const {\n        return SweepItem{\n            Wide(point.x)\
    \ - Wide(origin.x),\n            Wide(point.y) - Wide(origin.y),\n           \
    \ index,\n            kind\n        };\n    }\n\n    void build(const std::vector<Point<T>>&\
    \ counted_points) {\n        const int vertex_count = int(vertices.size());\n\
    \        const int counted_point_count = int(counted_points.size());\n       \
    \ for (int anchor = 0; anchor < vertex_count; ++anchor) {\n            for (const\
    \ Point<T>& point : counted_points) {\n                if (point.y != vertices[anchor].y)\
    \ continue;\n                if (point.x < vertices[anchor].x) {\n           \
    \         horizontal_left[anchor]++;\n                } else if (point.x == vertices[anchor].x)\
    \ {\n                    horizontal_equal[anchor]++;\n                }\n    \
    \        }\n\n            std::vector<SweepItem> items;\n            items.reserve(2\
    \ * vertices.size() + counted_points.size());\n            for (int index = 0;\
    \ index < vertex_count; ++index) {\n                if (vertices[anchor].y < vertices[index].y)\
    \ {\n                    items.push_back(make_item(\n                        vertices[anchor],\n\
    \                        vertices[index],\n                        index,\n  \
    \                      before_counted_points\n                    ));\n      \
    \          }\n            }\n            for (int index = 0; index < counted_point_count;\
    \ ++index) {\n                if (vertices[anchor].y < counted_points[index].y)\
    \ {\n                    items.push_back(make_item(\n                        vertices[anchor],\n\
    \                        counted_points[index],\n                        index,\n\
    \                        counted_point\n                    ));\n            \
    \    }\n            }\n            for (int index = 0; index < vertex_count; ++index)\
    \ {\n                if (vertices[anchor].y < vertices[index].y) {\n         \
    \           items.push_back(make_item(\n                        vertices[anchor],\n\
    \                        vertices[index],\n                        index,\n  \
    \                      after_counted_points\n                    ));\n       \
    \         }\n            }\n\n            std::sort(\n                items.begin(),\n\
    \                items.end(),\n                [](const SweepItem& first, const\
    \ SweepItem& second) {\n                    const Wide determinant =\n       \
    \                 first.x * second.y - first.y * second.x;\n                 \
    \   if (determinant != 0) return determinant < 0;\n                    return\
    \ first.kind < second.kind;\n                }\n            );\n\n           \
    \ std::vector<std::size_t> height_order(items.size());\n            std::iota(height_order.begin(),\
    \ height_order.end(), 0);\n            std::sort(\n                height_order.begin(),\n\
    \                height_order.end(),\n                [&items](std::size_t first,\
    \ std::size_t second) {\n                    if (items[first].y != items[second].y)\
    \ {\n                        return items[first].y < items[second].y;\n      \
    \              }\n                    return items[first].kind % 2 < items[second].kind\
    \ % 2;\n                }\n            );\n\n            count_points_in_triangle_detail::FenwickTree\
    \ fenwick(items.size());\n            for (std::size_t position : height_order)\
    \ {\n                const SweepItem& item = items[position];\n              \
    \  if (item.kind == before_counted_points) {\n                    edge_left[anchor][item.index]\
    \ =\n                        fenwick.prefix_sum(position + 1);\n             \
    \   } else if (item.kind == counted_point) {\n                    fenwick.add(position);\n\
    \                } else {\n                    edge_equal[anchor][item.index]\
    \ =\n                        fenwick.prefix_sum(position + 1);\n             \
    \   }\n            }\n            for (int index = 0; index < vertex_count; ++index)\
    \ {\n                edge_equal[anchor][index] -= edge_left[anchor][index];\n\
    \            }\n        }\n    }\n\n   public:\n    CountPointsInTriangle(\n \
    \       const std::vector<Point<T>>& triangle_vertices,\n        const std::vector<Point<T>>&\
    \ counted_points\n    )\n        : vertices(triangle_vertices),\n          horizontal_left(vertices.size(),\
    \ 0),\n          horizontal_equal(vertices.size(), 0),\n          edge_left(vertices.size(),\
    \ std::vector<int>(vertices.size(), 0)),\n          edge_equal(vertices.size(),\
    \ std::vector<int>(vertices.size(), 0)) {\n        assert(\n            vertices.size()\
    \ <=\n            static_cast<std::size_t>(std::numeric_limits<int>::max())\n\
    \        );\n        assert(\n            counted_points.size() <=\n         \
    \   static_cast<std::size_t>(std::numeric_limits<int>::max())\n        );\n  \
    \      build(counted_points);\n    }\n\n    int query(int first, int second, int\
    \ third) const {\n        const int size = int(vertices.size());\n        assert(0\
    \ <= first && first < size);\n        assert(0 <= second && second < size);\n\
    \        assert(0 <= third && third < size);\n\n        if (yx_less(vertices[second],\
    \ vertices[first])) {\n            std::swap(first, second);\n        }\n    \
    \    if (yx_less(vertices[third], vertices[second])) {\n            std::swap(second,\
    \ third);\n        }\n        if (yx_less(vertices[second], vertices[first]))\
    \ {\n            std::swap(first, second);\n        }\n\n        const Wide determinant\
    \ = cross(\n            vertices[first],\n            vertices[second],\n    \
    \        vertices[third]\n        );\n        if (determinant == 0) return 0;\n\
    \n        long long result;\n        if (vertices[first].y == vertices[second].y)\
    \ {\n            result =\n                static_cast<long long>(edge_left[second][third])\
    \ -\n                edge_left[first][third] -\n                edge_equal[first][third];\n\
    \        } else if (vertices[second].y == vertices[third].y) {\n            result\
    \ =\n                static_cast<long long>(edge_left[first][third]) -\n     \
    \           edge_left[first][second] -\n                edge_equal[first][second];\n\
    \        } else if (determinant < 0) {\n            result =\n               \
    \ static_cast<long long>(edge_left[first][third]) -\n                edge_left[second][third]\
    \ -\n                edge_equal[second][third] -\n                edge_left[first][second]\
    \ -\n                edge_equal[first][second] -\n                horizontal_left[second]\
    \ -\n                horizontal_equal[second];\n        } else {\n           \
    \ result =\n                static_cast<long long>(edge_left[first][second]) +\n\
    \                edge_left[second][third] +\n                horizontal_left[second]\
    \ -\n                edge_left[first][third] -\n                edge_equal[first][third];\n\
    \        }\n        assert(\n            0 <= result &&\n            result <=\
    \ std::numeric_limits<int>::max()\n        );\n        return int(result);\n \
    \   }\n};\n\n}  // namespace geometry\n}  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_COUNT_POINTS_IN_TRIANGLE_HPP\n"
  dependsOn:
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/count_points_in_triangle.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-22 02:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/count_points_in_triangle.test.cpp
  - verify/geometry/centroid.test.cpp
documentation_of: geometry/count_points_in_triangle.hpp
layout: document
title: Count Points in Triangle
---

## Overview

`CountPointsInTriangle` preprocesses two integral point sets. Each query chooses
three points from the first set and returns how many points from the second set
lie strictly inside their triangle.

Queries take constant time after preprocessing, making the structure useful
when the same candidate vertices are used for many triangles. Counted points on
an edge or vertex are excluded.

## Interface

```cpp
template <std::integral T>
class CountPointsInTriangle {
public:
    CountPointsInTriangle(
        const std::vector<Point<T>>& triangle_vertices,
        const std::vector<Point<T>>& counted_points
    );

    int query(int first, int second, int third) const;
};
```

| Member | Description | Complexity |
| --- | --- | --- |
| `CountPointsInTriangle(triangle_vertices, counted_points)` | Precomputes the counts needed by every triangle. Neither input is mutated. | $O(N(N+M)\log(N+M))$ time and $O(N^2+N+M)$ memory |
| `query(first, second, third)` | Counts points strictly inside the triangle formed by the three indexed vertices. | $O(1)$ |

Here, $N$ is the number of `triangle_vertices` and $M$ is the number of
`counted_points`.

## Behavior and Requirements

* `T` must be an integral coordinate type.
* Query indices are zero-based and must refer to `triangle_vertices`.
* The order of the three query indices does not matter.
* A query with repeated or collinear triangle vertices returns `0`.
* Duplicate counted points are counted with multiplicity. Duplicate triangle
  vertices are also allowed.
* The triangle boundary is excluded exactly; no floating-point tolerance is
  used.
* Coordinate differences and products used by orientation tests must fit
  signed `__int128`.

## Algorithm

For every candidate vertex, the constructor performs an angular sweep of the
other candidate vertices and counted points above it. A Fenwick tree records
how many counted points lie strictly to one side of each upward edge and how
many lie on the edge. Counts on the same horizontal line are stored separately.

A query orders its three vertices by y-coordinate and expresses the open
triangle as a signed combination of these precomputed edge regions. Separate
strict and collinear counts ensure that every boundary point is excluded.

## Example

```cpp
#include "geometry/count_points_in_triangle.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;

    std::vector<Point> vertices;
    vertices.emplace_back(0, 0);
    vertices.emplace_back(4, 0);
    vertices.emplace_back(0, 4);

    std::vector<Point> points;
    points.emplace_back(1, 1);
    points.emplace_back(2, 1);
    points.emplace_back(0, 1);  // Boundary: excluded.
    points.emplace_back(4, 4);
    points.emplace_back(1, 1);  // Duplicate: counted again.

    m1une::geometry::CountPointsInTriangle<long long> counter(
        vertices,
        points
    );
    std::cout << counter.query(0, 1, 2) << "\n";  // 3
}
```
