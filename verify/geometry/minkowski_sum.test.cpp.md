---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/convex_hull.hpp
    title: Convex Hull
  - icon: ':heavy_check_mark:'
    path: geometry/detail/convex_polygon_normalize.hpp
    title: geometry/detail/convex_polygon_normalize.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/minkowski_sum.hpp
    title: Minkowski Sum
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/geometry/minkowski_sum.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"geometry/convex_hull.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cstddef>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#include <cmath>\n#include\
    \ <concepts>\n#include <cassert>\n#include <type_traits>\n\nnamespace m1une {\n\
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
    \ geometry\n}  // namespace m1une\n\n\n#line 10 \"geometry/convex_hull.hpp\"\n\
    \nnamespace m1une {\nnamespace geometry {\n\n// Returns the convex hull counterclockwise\
    \ from its lexicographically smallest\n// point. The first point is not repeated\
    \ at the end.\ntemplate <Coordinate T>\nstd::vector<Point<T>> convex_hull(\n \
    \   std::vector<Point<T>> points,\n    bool include_collinear = false\n) {\n \
    \   std::sort(points.begin(), points.end());\n    points.erase(std::unique(points.begin(),\
    \ points.end()), points.end());\n    std::size_t size = points.size();\n    if\
    \ (size <= 1) return points;\n\n    std::vector<Point<T>> hull;\n    hull.reserve(2\
    \ * size);\n    auto should_pop = [include_collinear](\n        const Point<T>&\
    \ first,\n        const Point<T>& second,\n        const Point<T>& third\n   \
    \ ) {\n        int turn = orientation(first, second, third);\n        return include_collinear\
    \ ? turn < 0 : turn <= 0;\n    };\n\n    for (const Point<T>& point : points)\
    \ {\n        while (\n            hull.size() >= 2 &&\n            should_pop(hull[hull.size()\
    \ - 2], hull.back(), point)\n        ) {\n            hull.pop_back();\n     \
    \   }\n        hull.push_back(point);\n    }\n\n    std::size_t lower_size = hull.size();\n\
    \    for (std::size_t index = size - 1; index-- > 0;) {\n        const Point<T>&\
    \ point = points[index];\n        while (\n            hull.size() > lower_size\
    \ &&\n            should_pop(hull[hull.size() - 2], hull.back(), point)\n    \
    \    ) {\n            hull.pop_back();\n        }\n        hull.push_back(point);\n\
    \    }\n    hull.pop_back();\n\n    if (include_collinear && hull.size() == 2\
    \ * points.size() - 2) {\n        hull = std::move(points);\n    }\n    return\
    \ hull;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 1 \"\
    geometry/minkowski_sum.hpp\"\n\n\n\n#line 8 \"geometry/minkowski_sum.hpp\"\n\n\
    #line 1 \"geometry/detail/convex_polygon_normalize.hpp\"\n\n\n\n#line 8 \"geometry/detail/convex_polygon_normalize.hpp\"\
    \n\n#line 10 \"geometry/detail/convex_polygon_normalize.hpp\"\n\nnamespace m1une\
    \ {\nnamespace geometry {\nnamespace convex_polygon_detail {\n\ntemplate <Coordinate\
    \ T>\nwide_type<T> boundary_area2(const std::vector<Point<T>>& polygon) {\n  \
    \  wide_type<T> result = 0;\n    for (std::size_t index = 0; index < polygon.size();\
    \ ++index) {\n        result += cross(\n            polygon[index],\n        \
    \    polygon[(index + 1) % polygon.size()]\n        );\n    }\n    return result;\n\
    }\n\ntemplate <Coordinate T>\nstd::vector<Point<T>> normalize_convex_boundary(\n\
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
    }  // namespace m1une\n\n\n#line 5 \"verify/geometry/minkowski_sum.test.cpp\"\n\
    \n#line 8 \"verify/geometry/minkowski_sum.test.cpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#line 12 \"verify/geometry/minkowski_sum.test.cpp\"\n\nnamespace\
    \ {\n\nusing m1une::geometry::Point;\nusing PointType = Point<long long>;\n\n\
    std::vector<PointType> brute_sum(\n    const std::vector<PointType>& first,\n\
    \    const std::vector<PointType>& second\n) {\n    std::vector<PointType> sums;\n\
    \    sums.reserve(first.size() * second.size());\n    for (const PointType& left\
    \ : first) {\n        for (const PointType& right : second) {\n            sums.push_back(left\
    \ + right);\n        }\n    }\n    return m1une::geometry::convex_hull(std::move(sums));\n\
    }\n\nvoid test_fixed() {\n    std::vector<PointType> square;\n    square.emplace_back(0,\
    \ 0);\n    square.emplace_back(2, 0);\n    square.emplace_back(2, 2);\n    square.emplace_back(0,\
    \ 2);\n\n    std::vector<PointType> triangle;\n    triangle.emplace_back(0, 0);\n\
    \    triangle.emplace_back(3, 0);\n    triangle.emplace_back(0, 1);\n    assert(\n\
    \        m1une::geometry::minkowski_sum(square, triangle) ==\n        brute_sum(square,\
    \ triangle)\n    );\n\n    std::reverse(square.begin(), square.end());\n    triangle.push_back(triangle.front());\n\
    \    assert(\n        m1une::geometry::minkowski_sum(square, triangle) ==\n  \
    \      brute_sum(square, triangle)\n    );\n\n    std::vector<PointType> segment;\n\
    \    segment.emplace_back(3, 0);\n    segment.emplace_back(0, 0);\n    std::vector<PointType>\
    \ point;\n    point.emplace_back(2, 4);\n    std::vector<PointType> expected;\n\
    \    expected.emplace_back(2, 4);\n    expected.emplace_back(5, 4);\n    assert(m1une::geometry::minkowski_sum(segment,\
    \ point) == expected);\n\n    std::vector<PointType> redundant;\n    redundant.emplace_back(0,\
    \ 0);\n    redundant.emplace_back(1, 0);\n    redundant.emplace_back(2, 0);\n\
    \    redundant.emplace_back(2, 2);\n    redundant.emplace_back(0, 2);\n    redundant.emplace_back(0,\
    \ 0);\n    assert(\n        m1une::geometry::minkowski_sum(redundant, point) ==\n\
    \        brute_sum(redundant, point)\n    );\n}\n\nvoid test_randomized() {\n\
    \    std::uint64_t state = 0x243f6a8885a308d3ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 5000; ++trial) {\n       \
    \ std::vector<PointType> first_points;\n        std::vector<PointType> second_points;\n\
    \        const int first_size = 1 + int(random() % 12);\n        const int second_size\
    \ = 1 + int(random() % 12);\n        for (int index = 0; index < first_size; ++index)\
    \ {\n            first_points.emplace_back(\n                static_cast<long\
    \ long>(random() % 31) - 15,\n                static_cast<long long>(random()\
    \ % 31) - 15\n            );\n        }\n        for (int index = 0; index < second_size;\
    \ ++index) {\n            second_points.emplace_back(\n                static_cast<long\
    \ long>(random() % 31) - 15,\n                static_cast<long long>(random()\
    \ % 31) - 15\n            );\n        }\n        std::vector<PointType> first\
    \ =\n            m1une::geometry::convex_hull(first_points);\n        std::vector<PointType>\
    \ second =\n            m1une::geometry::convex_hull(second_points);\n       \
    \ if (random() & 1) std::reverse(first.begin(), first.end());\n        if (random()\
    \ & 1) std::reverse(second.begin(), second.end());\n\n        const std::vector<PointType>\
    \ expected = brute_sum(first, second);\n        const std::vector<PointType> actual\
    \ =\n            m1une::geometry::minkowski_sum(first, second);\n        assert(m1une::geometry::convex_hull(actual)\
    \ == expected);\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n\
    \    test_randomized();\n\n    long long first;\n    long long second;\n    std::cin\
    \ >> first >> second;\n    std::cout << first + second << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../geometry/convex_hull.hpp\"\n#include \"../../geometry/minkowski_sum.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n\
    #include <utility>\n#include <vector>\n\nnamespace {\n\nusing m1une::geometry::Point;\n\
    using PointType = Point<long long>;\n\nstd::vector<PointType> brute_sum(\n   \
    \ const std::vector<PointType>& first,\n    const std::vector<PointType>& second\n\
    ) {\n    std::vector<PointType> sums;\n    sums.reserve(first.size() * second.size());\n\
    \    for (const PointType& left : first) {\n        for (const PointType& right\
    \ : second) {\n            sums.push_back(left + right);\n        }\n    }\n \
    \   return m1une::geometry::convex_hull(std::move(sums));\n}\n\nvoid test_fixed()\
    \ {\n    std::vector<PointType> square;\n    square.emplace_back(0, 0);\n    square.emplace_back(2,\
    \ 0);\n    square.emplace_back(2, 2);\n    square.emplace_back(0, 2);\n\n    std::vector<PointType>\
    \ triangle;\n    triangle.emplace_back(0, 0);\n    triangle.emplace_back(3, 0);\n\
    \    triangle.emplace_back(0, 1);\n    assert(\n        m1une::geometry::minkowski_sum(square,\
    \ triangle) ==\n        brute_sum(square, triangle)\n    );\n\n    std::reverse(square.begin(),\
    \ square.end());\n    triangle.push_back(triangle.front());\n    assert(\n   \
    \     m1une::geometry::minkowski_sum(square, triangle) ==\n        brute_sum(square,\
    \ triangle)\n    );\n\n    std::vector<PointType> segment;\n    segment.emplace_back(3,\
    \ 0);\n    segment.emplace_back(0, 0);\n    std::vector<PointType> point;\n  \
    \  point.emplace_back(2, 4);\n    std::vector<PointType> expected;\n    expected.emplace_back(2,\
    \ 4);\n    expected.emplace_back(5, 4);\n    assert(m1une::geometry::minkowski_sum(segment,\
    \ point) == expected);\n\n    std::vector<PointType> redundant;\n    redundant.emplace_back(0,\
    \ 0);\n    redundant.emplace_back(1, 0);\n    redundant.emplace_back(2, 0);\n\
    \    redundant.emplace_back(2, 2);\n    redundant.emplace_back(0, 2);\n    redundant.emplace_back(0,\
    \ 0);\n    assert(\n        m1une::geometry::minkowski_sum(redundant, point) ==\n\
    \        brute_sum(redundant, point)\n    );\n}\n\nvoid test_randomized() {\n\
    \    std::uint64_t state = 0x243f6a8885a308d3ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 5000; ++trial) {\n       \
    \ std::vector<PointType> first_points;\n        std::vector<PointType> second_points;\n\
    \        const int first_size = 1 + int(random() % 12);\n        const int second_size\
    \ = 1 + int(random() % 12);\n        for (int index = 0; index < first_size; ++index)\
    \ {\n            first_points.emplace_back(\n                static_cast<long\
    \ long>(random() % 31) - 15,\n                static_cast<long long>(random()\
    \ % 31) - 15\n            );\n        }\n        for (int index = 0; index < second_size;\
    \ ++index) {\n            second_points.emplace_back(\n                static_cast<long\
    \ long>(random() % 31) - 15,\n                static_cast<long long>(random()\
    \ % 31) - 15\n            );\n        }\n        std::vector<PointType> first\
    \ =\n            m1une::geometry::convex_hull(first_points);\n        std::vector<PointType>\
    \ second =\n            m1une::geometry::convex_hull(second_points);\n       \
    \ if (random() & 1) std::reverse(first.begin(), first.end());\n        if (random()\
    \ & 1) std::reverse(second.begin(), second.end());\n\n        const std::vector<PointType>\
    \ expected = brute_sum(first, second);\n        const std::vector<PointType> actual\
    \ =\n            m1une::geometry::minkowski_sum(first, second);\n        assert(m1une::geometry::convex_hull(actual)\
    \ == expected);\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n\
    \    test_randomized();\n\n    long long first;\n    long long second;\n    std::cin\
    \ >> first >> second;\n    std::cout << first + second << '\\n';\n}\n"
  dependsOn:
  - geometry/convex_hull.hpp
  - geometry/point.hpp
  - geometry/minkowski_sum.hpp
  - geometry/detail/convex_polygon_normalize.hpp
  - geometry/point.hpp
  isVerificationFile: true
  path: verify/geometry/minkowski_sum.test.cpp
  requiredBy: []
  timestamp: '2026-08-08 16:10:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/minkowski_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/minkowski_sum.test.cpp
- /verify/verify/geometry/minkowski_sum.test.cpp.html
title: verify/geometry/minkowski_sum.test.cpp
---
