---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/circle.hpp
    title: Circles
  - icon: ':heavy_check_mark:'
    path: geometry/convex_hull.hpp
    title: Convex Hull
  - icon: ':heavy_check_mark:'
    path: geometry/convex_polygon.hpp
    title: Convex Polygons
  - icon: ':heavy_check_mark:'
    path: geometry/detail/convex_polygon_normalize.hpp
    title: geometry/detail/convex_polygon_normalize.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/detail/floating_predicate.hpp
    title: geometry/detail/floating_predicate.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/half_plane_intersection.hpp
    title: Half-Plane Intersection
  - icon: ':heavy_check_mark:'
    path: geometry/linear.hpp
    title: Linear Objects
  - icon: ':heavy_check_mark:'
    path: geometry/minkowski_sum.hpp
    title: Minkowski Sum
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/polygon.hpp
    title: Polygons
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
  bundledCode: "#line 1 \"verify/geometry/is_convex_polygon.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B\"\n\n#line\
    \ 1 \"geometry/convex_polygon.hpp\"\n\n\n\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <cmath>\n#include <concepts>\n#include <cstddef>\n\
    #include <deque>\n#include <limits>\n#include <numbers>\n#include <optional>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"geometry/convex_hull.hpp\"\n\
    \n\n\n#line 8 \"geometry/convex_hull.hpp\"\n\n#line 1 \"geometry/point.hpp\"\n\
    \n\n\n#line 7 \"geometry/point.hpp\"\n#include <type_traits>\n\n#line 1 \"geometry/detail/floating_predicate.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace geometry {\nnamespace predicate_detail {\n\
    \ntemplate <typename T>\nconstexpr T absolute(T value) {\n    return value < T(0)\
    \ ? -value : value;\n}\n\ntemplate <typename T>\nconstexpr T max_value(T first,\
    \ T second) {\n    return first < second ? second : first;\n}\n\ntemplate <typename\
    \ T>\nconstexpr T vector_scale(T x, T y) {\n    return max_value(absolute(x),\
    \ absolute(y));\n}\n\ntemplate <bool Exact, typename T>\nconstexpr int scaled_sign(T\
    \ value, T scale, long double eps) {\n    if constexpr (Exact) {\n        return\
    \ (value > T(0)) - (value < T(0));\n    } else {\n        const T tolerance =\
    \ T(eps) * scale;\n        return (value > tolerance) - (value < -tolerance);\n\
    \    }\n}\n\ntemplate <bool Exact, typename T>\nconstexpr T determinant_scale(T\
    \ ax, T ay, T bx, T by) {\n    if constexpr (Exact) {\n        return T(0);\n\
    \    } else {\n        return vector_scale(ax, ay) * vector_scale(bx, by);\n \
    \   }\n}\n\ntemplate <bool Exact, typename T>\nconstexpr int determinant_sign(\n\
    \    T ax,\n    T ay,\n    T bx,\n    T by,\n    long double eps\n) {\n    const\
    \ T determinant = ax * by - ay * bx;\n    return scaled_sign<Exact>(\n       \
    \ determinant,\n        determinant_scale<Exact>(ax, ay, bx, by),\n        eps\n\
    \    );\n}\n\ntemplate <bool Exact, typename T>\nconstexpr int orientation_sign(\n\
    \    T direction_x,\n    T direction_y,\n    T offset_x,\n    T offset_y,\n  \
    \  long double eps\n) {\n    const T determinant =\n        direction_x * offset_y\
    \ - direction_y * offset_x;\n    T scale = T(0);\n    if constexpr (!Exact) {\n\
    \        const T direction_scale =\n            vector_scale(direction_x, direction_y);\n\
    \        scale = direction_scale * max_value(\n            direction_scale,\n\
    \            vector_scale(offset_x, offset_y)\n        );\n    }\n    return scaled_sign<Exact>(determinant,\
    \ scale, eps);\n}\n\ntemplate <bool Exact, typename T>\nconstexpr int dot_sign(\n\
    \    T ax,\n    T ay,\n    T bx,\n    T by,\n    long double eps\n) {\n    const\
    \ T value = ax * bx + ay * by;\n    T scale = T(0);\n    if constexpr (!Exact)\
    \ {\n        scale = vector_scale(ax, ay) * vector_scale(bx, by);\n    }\n   \
    \ return scaled_sign<Exact>(value, scale, eps);\n}\n\n}  // namespace predicate_detail\n\
    }  // namespace geometry\n}  // namespace m1une\n\n\n#line 10 \"geometry/point.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <typename T>\nconcept\
    \ Coordinate = std::is_arithmetic_v<T> && !std::same_as<std::remove_cv_t<T>, bool>;\n\
    \ntemplate <Coordinate T>\nusing wide_type = std::conditional_t<std::integral<T>,\
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
    \ sign(wide_type<T> value, long double eps = 1e-12L) {\n    return predicate_detail::scaled_sign<std::integral<T>>(\n\
    \        value,\n        wide_type<T>(1),\n        eps\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr int orientation(\n    const Point<T>& a,\n    const\
    \ Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n) {\n  \
    \  using W = wide_type<T>;\n    const W first_x = W(b.x) - W(a.x);\n    const\
    \ W first_y = W(b.y) - W(a.y);\n    const W second_x = W(c.x) - W(a.x);\n    const\
    \ W second_y = W(c.y) - W(a.y);\n    return predicate_detail::orientation_sign<std::integral<T>>(\n\
    \        first_x,\n        first_y,\n        second_x,\n        second_y,\n  \
    \      eps\n    );\n}\n\ntemplate <Coordinate T>\nconstexpr bool collinear(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>& c,\n    long\
    \ double eps = 1e-12L\n) {\n    return orientation(a, b, c, eps) == 0;\n}\n\n\
    template <Coordinate T>\nPoint<long double> rotate(const Point<T>& point, long\
    \ double angle) {\n    long double cosine = std::cos(angle);\n    long double\
    \ sine = std::sin(angle);\n    return Point<long double>(\n        static_cast<long\
    \ double>(point.x) * cosine -\n            static_cast<long double>(point.y) *\
    \ sine,\n        static_cast<long double>(point.x) * sine +\n            static_cast<long\
    \ double>(point.y) * cosine\n    );\n}\n\ntemplate <Coordinate T>\nPoint<long\
    \ double> normalized(const Point<T>& point) {\n    long double length = norm(point);\n\
    \    assert(length != 0);\n    return Point<long double>(\n        static_cast<long\
    \ double>(point.x) / length,\n        static_cast<long double>(point.y) / length\n\
    \    );\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 10 \"\
    geometry/convex_hull.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\n// Returns\
    \ the convex hull counterclockwise from its lexicographically smallest\n// point.\
    \ The first point is not repeated at the end.\ntemplate <Coordinate T>\nstd::vector<Point<T>>\
    \ convex_hull(\n    std::vector<Point<T>> points,\n    bool include_collinear\
    \ = false\n) {\n    std::sort(points.begin(), points.end());\n    points.erase(std::unique(points.begin(),\
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
    geometry/half_plane_intersection.hpp\"\n\n\n\n#line 12 \"geometry/half_plane_intersection.hpp\"\
    \n#include <random>\n#line 15 \"geometry/half_plane_intersection.hpp\"\n\n#line\
    \ 1 \"geometry/linear.hpp\"\n\n\n\n#line 7 \"geometry/linear.hpp\"\n\n#line 9\
    \ \"geometry/linear.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate\
    \ <Coordinate T>\nstruct Line {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate\
    \ <Coordinate T>\nstruct Segment {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate\
    \ <Coordinate T>\nstruct Ray {\n    Point<T> origin;\n    Point<T> through;\n\
    };\n\nenum class LinearIntersectionKind {\n    Empty,\n    Point,\n    Segment,\n\
    \    Ray,\n    Line,\n};\n\nstruct LinearIntersection {\n    LinearIntersectionKind\
    \ kind;\n    Point<long double> first;\n    Point<long double> second;\n};\n\n\
    struct ClosestPoints {\n    Point<long double> first;\n    Point<long double>\
    \ second;\n};\n\nnamespace linear_intersection_detail {\n\ninline LinearIntersection\
    \ make_empty() {\n    const Point<long double> zero;\n    return LinearIntersection{\n\
    \        LinearIntersectionKind::Empty,\n        zero,\n        zero,\n    };\n\
    }\n\ntemplate <Coordinate T>\nLinearIntersection make_point(const Point<T>& point)\
    \ {\n    const Point<long double> converted(point);\n    return LinearIntersection{\n\
    \        LinearIntersectionKind::Point,\n        converted,\n        converted,\n\
    \    };\n}\n\ntemplate <Coordinate T>\nLinearIntersection make_object(\n    LinearIntersectionKind\
    \ kind,\n    const Point<T>& first,\n    const Point<T>& second\n) {\n    return\
    \ LinearIntersection{\n        kind,\n        Point<long double>(first),\n   \
    \     Point<long double>(second),\n    };\n}\n\n}  // namespace linear_intersection_detail\n\
    \ntemplate <Coordinate T>\nconstexpr Point<long double> centroid(const Segment<T>&\
    \ segment) {\n    return Point<long double>(\n        (\n            static_cast<long\
    \ double>(segment.a.x) +\n            static_cast<long double>(segment.b.x)\n\
    \        ) / 2,\n        (\n            static_cast<long double>(segment.a.y)\
    \ +\n            static_cast<long double>(segment.b.y)\n        ) / 2\n    );\n\
    }\n\ntemplate <Coordinate T>\nbool on_line(\n    const Line<T>& line,\n    const\
    \ Point<T>& point,\n    long double eps = 1e-12L\n) {\n    assert(line.a != line.b);\n\
    \    return orientation(line.a, line.b, point, eps) == 0;\n}\n\ntemplate <Coordinate\
    \ T>\nbool parallel(const Line<T>& first, const Line<T>& second, long double eps\
    \ = 1e-12L) {\n    using W = wide_type<T>;\n    W first_x = W(first.b.x) - W(first.a.x);\n\
    \    W first_y = W(first.b.y) - W(first.a.y);\n    W second_x = W(second.b.x)\
    \ - W(second.a.x);\n    W second_y = W(second.b.y) - W(second.a.y);\n    return\
    \ predicate_detail::determinant_sign<std::integral<T>>(\n        first_x,\n  \
    \      first_y,\n        second_x,\n        second_y,\n        eps\n    ) == 0;\n\
    }\n\ntemplate <Coordinate T>\nbool orthogonal(const Line<T>& first, const Line<T>&\
    \ second, long double eps = 1e-12L) {\n    using W = wide_type<T>;\n    W first_x\
    \ = W(first.b.x) - W(first.a.x);\n    W first_y = W(first.b.y) - W(first.a.y);\n\
    \    W second_x = W(second.b.x) - W(second.a.x);\n    W second_y = W(second.b.y)\
    \ - W(second.a.y);\n    return predicate_detail::dot_sign<std::integral<T>>(\n\
    \        first_x,\n        first_y,\n        second_x,\n        second_y,\n  \
    \      eps\n    ) == 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double> projection(const\
    \ Line<T>& line, const Point<T>& point) {\n    assert(line.a != line.b);\n   \
    \ Point<long double> a(line.a);\n    Point<long double> direction(\n        static_cast<long\
    \ double>(line.b.x) - static_cast<long double>(line.a.x),\n        static_cast<long\
    \ double>(line.b.y) - static_cast<long double>(line.a.y)\n    );\n    Point<long\
    \ double> offset(\n        static_cast<long double>(point.x) - a.x,\n        static_cast<long\
    \ double>(point.y) - a.y\n    );\n    long double ratio = dot(offset, direction)\
    \ / dot(direction, direction);\n    return a + direction * ratio;\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> reflection(const Line<T>& line, const Point<T>&\
    \ point) {\n    Point<long double> projected = projection(line, point);\n    return\
    \ projected * 2.0L - Point<long double>(point);\n}\n\ntemplate <Coordinate T>\n\
    bool intersects(\n    const Line<T>& first,\n    const Line<T>& second,\n    long\
    \ double eps = 1e-12L\n) {\n    return !parallel(first, second, eps) || on_line(first,\
    \ second.a, eps);\n}\n\ntemplate <Coordinate T>\nbool on_segment(\n    const Segment<T>&\
    \ segment,\n    const Point<T>& point,\n    long double eps = 1e-12L\n) {\n  \
    \  if (orientation(segment.a, segment.b, point, eps) != 0) return false;\n   \
    \ using W = wide_type<T>;\n    const W direction_x = W(segment.b.x) - W(segment.a.x);\n\
    \    const W direction_y = W(segment.b.y) - W(segment.a.y);\n    if (direction_x\
    \ == W(0) && direction_y == W(0)) {\n        if constexpr (std::integral<T>) {\n\
    \            return point == segment.a;\n        } else {\n            return\n\
    \                predicate_detail::absolute(W(point.x) - W(segment.a.x)) <= eps\
    \ &&\n                predicate_detail::absolute(W(point.y) - W(segment.a.y))\
    \ <= eps;\n        }\n    }\n    const W offset_x = W(point.x) - W(segment.a.x);\n\
    \    const W offset_y = W(point.y) - W(segment.a.y);\n    const W projection =\n\
    \        offset_x * direction_x + offset_y * direction_y;\n    const W length_squared\
    \ =\n        direction_x * direction_x + direction_y * direction_y;\n    return\n\
    \        predicate_detail::scaled_sign<std::integral<T>>(\n            projection,\n\
    \            length_squared,\n            eps\n        ) >= 0 &&\n        predicate_detail::scaled_sign<std::integral<T>>(\n\
    \            projection - length_squared,\n            length_squared,\n     \
    \       eps\n        ) <= 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double>\
    \ projection(\n    const Segment<T>& segment,\n    const Point<T>& point\n) {\n\
    \    const Point<long double> first(segment.a);\n    const Point<long double>\
    \ direction =\n        Point<long double>(segment.b) - first;\n    const long\
    \ double length_squared = dot(direction, direction);\n    if (length_squared ==\
    \ 0) return first;\n    const long double ratio = std::clamp(\n        dot(Point<long\
    \ double>(point) - first, direction) / length_squared,\n        0.0L,\n      \
    \  1.0L\n    );\n    return first + direction * ratio;\n}\n\ntemplate <Coordinate\
    \ T>\nbool intersects(\n    const Segment<T>& first,\n    const Segment<T>& second,\n\
    \    long double eps = 1e-12L\n) {\n    int abc = orientation(first.a, first.b,\
    \ second.a, eps);\n    int abd = orientation(first.a, first.b, second.b, eps);\n\
    \    int cda = orientation(second.a, second.b, first.a, eps);\n    int cdb = orientation(second.a,\
    \ second.b, first.b, eps);\n\n    if (abc == 0 && on_segment(first, second.a,\
    \ eps)) return true;\n    if (abd == 0 && on_segment(first, second.b, eps)) return\
    \ true;\n    if (cda == 0 && on_segment(second, first.a, eps)) return true;\n\
    \    if (cdb == 0 && on_segment(second, first.b, eps)) return true;\n    return\
    \ abc * abd < 0 && cda * cdb < 0;\n}\n\ntemplate <Coordinate T>\nbool intersects(\n\
    \    const Line<T>& line,\n    const Segment<T>& segment,\n    long double eps\
    \ = 1e-12L\n) {\n    int first_side = orientation(line.a, line.b, segment.a, eps);\n\
    \    int second_side = orientation(line.a, line.b, segment.b, eps);\n    return\
    \ first_side == 0 || second_side == 0 || first_side != second_side;\n}\n\ntemplate\
    \ <Coordinate T>\nbool intersects(\n    const Segment<T>& segment,\n    const\
    \ Line<T>& line,\n    long double eps = 1e-12L\n) {\n    return intersects(line,\
    \ segment, eps);\n}\n\nnamespace linear_parameter_detail {\n\ntemplate <Coordinate\
    \ T>\nstruct Parameters {\n    wide_type<T> denominator;\n    wide_type<T> denominator_scale;\n\
    \    wide_type<T> first_numerator;\n    wide_type<T> second_numerator;\n};\n\n\
    template <Coordinate T>\nParameters<T> parameters(\n    const Point<T>& first_origin,\n\
    \    const Point<T>& first_through,\n    const Point<T>& second_origin,\n    const\
    \ Point<T>& second_through\n) {\n    using W = wide_type<T>;\n    W first_x =\
    \ W(first_through.x) - W(first_origin.x);\n    W first_y = W(first_through.y)\
    \ - W(first_origin.y);\n    W second_x = W(second_through.x) - W(second_origin.x);\n\
    \    W second_y = W(second_through.y) - W(second_origin.y);\n    W offset_x =\
    \ W(second_origin.x) - W(first_origin.x);\n    W offset_y = W(second_origin.y)\
    \ - W(first_origin.y);\n    return Parameters<T>{\n        first_x * second_y\
    \ - first_y * second_x,\n        predicate_detail::determinant_scale<std::integral<T>>(\n\
    \            first_x,\n            first_y,\n            second_x,\n         \
    \   second_y\n        ),\n        offset_x * second_y - offset_y * second_x,\n\
    \        offset_x * first_y - offset_y * first_x\n    };\n}\n\ntemplate <Coordinate\
    \ T>\nint denominator_sign(const Parameters<T>& values, long double eps) {\n \
    \   return predicate_detail::scaled_sign<std::integral<T>>(\n        values.denominator,\n\
    \        values.denominator_scale,\n        eps\n    );\n}\n\ntemplate <Coordinate\
    \ T>\nbool ratio_nonnegative(\n    wide_type<T> numerator,\n    wide_type<T> denominator,\n\
    \    long double eps\n) {\n    const int numerator_sign =\n        predicate_detail::scaled_sign<std::integral<T>>(\n\
    \            numerator,\n            predicate_detail::absolute(denominator),\n\
    \            eps\n        );\n    const int denominator_direction =\n        (denominator\
    \ > 0) - (denominator < 0);\n    return\n        numerator_sign == 0 ||\n    \
    \    numerator_sign == denominator_direction;\n}\n\ntemplate <Coordinate T>\n\
    bool ratio_in_unit_interval(\n    wide_type<T> numerator,\n    wide_type<T> denominator,\n\
    \    long double eps\n) {\n    const auto scale = predicate_detail::absolute(denominator);\n\
    \    const int start_sign =\n        predicate_detail::scaled_sign<std::integral<T>>(\n\
    \            numerator,\n            scale,\n            eps\n        );\n   \
    \ const int finish_sign =\n        predicate_detail::scaled_sign<std::integral<T>>(\n\
    \            numerator - denominator,\n            scale,\n            eps\n \
    \       );\n    if (denominator > 0) {\n        return start_sign >= 0 && finish_sign\
    \ <= 0;\n    }\n    return start_sign <= 0 && finish_sign >= 0;\n}\n\n}  // namespace\
    \ linear_parameter_detail\n\ntemplate <Coordinate T>\nbool on_ray(\n    const\
    \ Ray<T>& ray,\n    const Point<T>& point,\n    long double eps = 1e-12L\n) {\n\
    \    assert(ray.origin != ray.through);\n    if (orientation(ray.origin, ray.through,\
    \ point, eps) != 0) return false;\n    using W = wide_type<T>;\n    W direction_x\
    \ = W(ray.through.x) - W(ray.origin.x);\n    W direction_y = W(ray.through.y)\
    \ - W(ray.origin.y);\n    W offset_x = W(point.x) - W(ray.origin.x);\n    W offset_y\
    \ = W(point.y) - W(ray.origin.y);\n    const W projection =\n        direction_x\
    \ * offset_x + direction_y * offset_y;\n    const W length_squared =\n       \
    \ direction_x * direction_x + direction_y * direction_y;\n    return predicate_detail::scaled_sign<std::integral<T>>(\n\
    \        projection,\n        length_squared,\n        eps\n    ) >= 0;\n}\n\n\
    template <Coordinate T>\nPoint<long double> projection(const Ray<T>& ray, const\
    \ Point<T>& point) {\n    assert(ray.origin != ray.through);\n    Point<long double>\
    \ origin(ray.origin);\n    Point<long double> direction =\n        Point<long\
    \ double>(ray.through) - origin;\n    Point<long double> offset = Point<long double>(point)\
    \ - origin;\n    long double ratio = dot(offset, direction) / dot(direction, direction);\n\
    \    if (ratio < 0) ratio = 0;\n    return origin + direction * ratio;\n}\n\n\
    template <Coordinate T>\nRay<long double> reflection(const Line<T>& line, const\
    \ Ray<T>& ray) {\n    assert(ray.origin != ray.through);\n    return Ray<long\
    \ double>{\n        reflection(line, ray.origin),\n        reflection(line, ray.through)\n\
    \    };\n}\n\ntemplate <Coordinate T>\nRay<long double> reflected_ray(\n    const\
    \ Ray<T>& incoming,\n    const Point<T>& hit,\n    const Line<T>& mirror,\n  \
    \  long double eps = 1e-12L\n) {\n    assert(incoming.origin != incoming.through);\n\
    \    assert(on_line(mirror, hit, eps));\n    Point<T> translated = hit + (incoming.through\
    \ - incoming.origin);\n    return Ray<long double>{\n        Point<long double>(hit),\n\
    \        reflection(mirror, translated)\n    };\n}\n\ntemplate <Coordinate T>\n\
    bool intersects(\n    const Ray<T>& ray,\n    const Line<T>& line,\n    long double\
    \ eps = 1e-12L\n) {\n    assert(ray.origin != ray.through);\n    assert(line.a\
    \ != line.b);\n    linear_parameter_detail::Parameters<T> values =\n        linear_parameter_detail::parameters(\n\
    \        ray.origin,\n        ray.through,\n        line.a,\n        line.b\n\
    \    );\n    if (linear_parameter_detail::denominator_sign(values, eps) == 0)\
    \ {\n        return on_line(line, ray.origin, eps);\n    }\n    return linear_parameter_detail::ratio_nonnegative<T>(\n\
    \        values.first_numerator,\n        values.denominator,\n        eps\n \
    \   );\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const Line<T>& line,\n\
    \    const Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return intersects(ray,\
    \ line, eps);\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const Ray<T>&\
    \ ray,\n    const Segment<T>& segment,\n    long double eps = 1e-12L\n) {\n  \
    \  assert(ray.origin != ray.through);\n    if (segment.a == segment.b) return\
    \ on_ray(ray, segment.a, eps);\n\n    linear_parameter_detail::Parameters<T> values\
    \ =\n        linear_parameter_detail::parameters(\n        ray.origin,\n     \
    \   ray.through,\n        segment.a,\n        segment.b\n    );\n    if (linear_parameter_detail::denominator_sign(values,\
    \ eps) == 0) {\n        if (orientation(ray.origin, ray.through, segment.a, eps)\
    \ != 0) {\n            return false;\n        }\n        return on_ray(ray, segment.a,\
    \ eps) ||\n               on_ray(ray, segment.b, eps) ||\n               on_segment(segment,\
    \ ray.origin, eps);\n    }\n    return linear_parameter_detail::ratio_nonnegative<T>(\n\
    \               values.first_numerator,\n               values.denominator,\n\
    \               eps\n           ) &&\n           linear_parameter_detail::ratio_in_unit_interval<T>(\n\
    \               values.second_numerator,\n               values.denominator,\n\
    \               eps\n           );\n}\n\ntemplate <Coordinate T>\nbool intersects(\n\
    \    const Segment<T>& segment,\n    const Ray<T>& ray,\n    long double eps =\
    \ 1e-12L\n) {\n    return intersects(ray, segment, eps);\n}\n\ntemplate <Coordinate\
    \ T>\nbool intersects(\n    const Ray<T>& first,\n    const Ray<T>& second,\n\
    \    long double eps = 1e-12L\n) {\n    assert(first.origin != first.through);\n\
    \    assert(second.origin != second.through);\n    linear_parameter_detail::Parameters<T>\
    \ values =\n        linear_parameter_detail::parameters(\n        first.origin,\n\
    \        first.through,\n        second.origin,\n        second.through\n    );\n\
    \    if (linear_parameter_detail::denominator_sign(values, eps) == 0) {\n    \
    \    if (orientation(first.origin, first.through, second.origin, eps) != 0) {\n\
    \            return false;\n        }\n        return on_ray(first, second.origin,\
    \ eps) ||\n               on_ray(second, first.origin, eps);\n    }\n    return\
    \ linear_parameter_detail::ratio_nonnegative<T>(\n               values.first_numerator,\n\
    \               values.denominator,\n               eps\n           ) &&\n   \
    \        linear_parameter_detail::ratio_nonnegative<T>(\n               values.second_numerator,\n\
    \               values.denominator,\n               eps\n           );\n}\n\n\
    namespace linear_intersection_detail {\n\nenum class Domain {\n    Line,\n   \
    \ Segment,\n    Ray,\n};\n\ntemplate <Coordinate T>\nstruct ParametricObject {\n\
    \    Point<T> origin;\n    Point<T> through;\n    Domain domain;\n};\n\ntemplate\
    \ <Coordinate T>\nParametricObject<T> parametric_object(const Line<T>& line) {\n\
    \    assert(line.a != line.b);\n    return ParametricObject<T>{line.a, line.b,\
    \ Domain::Line};\n}\n\ntemplate <Coordinate T>\nParametricObject<T> parametric_object(const\
    \ Segment<T>& segment) {\n    return ParametricObject<T>{segment.a, segment.b,\
    \ Domain::Segment};\n}\n\ntemplate <Coordinate T>\nParametricObject<T> parametric_object(const\
    \ Ray<T>& ray) {\n    assert(ray.origin != ray.through);\n    return ParametricObject<T>{ray.origin,\
    \ ray.through, Domain::Ray};\n}\n\ntemplate <Coordinate T>\nbool contains(\n \
    \   const ParametricObject<T>& object,\n    const Point<T>& point,\n    long double\
    \ eps\n) {\n    if (object.domain == Domain::Line) {\n        return on_line(Line<T>{object.origin,\
    \ object.through}, point, eps);\n    }\n    if (object.domain == Domain::Segment)\
    \ {\n        return on_segment(\n            Segment<T>{object.origin, object.through},\n\
    \            point,\n            eps\n        );\n    }\n    return on_ray(Ray<T>{object.origin,\
    \ object.through}, point, eps);\n}\n\ntemplate <Coordinate T>\nbool accepts_parameter(\n\
    \    Domain domain,\n    wide_type<T> numerator,\n    wide_type<T> denominator,\n\
    \    long double eps\n) {\n    if (domain == Domain::Line) return true;\n    if\
    \ (domain == Domain::Ray) {\n        return linear_parameter_detail::ratio_nonnegative<T>(\n\
    \            numerator,\n            denominator,\n            eps\n        );\n\
    \    }\n    return linear_parameter_detail::ratio_in_unit_interval<T>(\n     \
    \   numerator,\n        denominator,\n        eps\n    );\n}\n\ntemplate <Coordinate\
    \ T>\nPoint<long double> point_at_ratio(\n    const ParametricObject<T>& object,\n\
    \    wide_type<T> numerator,\n    wide_type<T> denominator\n) {\n    const long\
    \ double ratio =\n        static_cast<long double>(numerator) /\n        static_cast<long\
    \ double>(denominator);\n    const Point<long double> origin(object.origin);\n\
    \    const Point<long double> direction =\n        Point<long double>(object.through)\
    \ - origin;\n    return origin + direction * ratio;\n}\n\ntemplate <Coordinate\
    \ T>\nstruct AxisProjection {\n    bool use_x;\n    bool negate;\n\n    wide_type<T>\
    \ operator()(const Point<T>& point) const {\n        const wide_type<T> value\
    \ = use_x\n            ? wide_type<T>(point.x)\n            : wide_type<T>(point.y);\n\
    \        return negate ? -value : value;\n    }\n};\n\ntemplate <Coordinate T>\n\
    AxisProjection<T> axis_projection(const ParametricObject<T>& object) {\n    using\
    \ W = wide_type<T>;\n    const W direction_x = W(object.through.x) - W(object.origin.x);\n\
    \    const W direction_y = W(object.through.y) - W(object.origin.y);\n    const\
    \ bool use_x =\n        predicate_detail::absolute(direction_x) >=\n        predicate_detail::absolute(direction_y);\n\
    \    const W component = use_x ? direction_x : direction_y;\n    assert(component\
    \ != W(0));\n    return AxisProjection<T>{use_x, component < W(0)};\n}\n\ntemplate\
    \ <Coordinate T>\nstruct ParameterInterval {\n    bool has_lower;\n    bool has_upper;\n\
    \    wide_type<T> lower;\n    wide_type<T> upper;\n};\n\ntemplate <Coordinate\
    \ T>\nParameterInterval<T> parameter_interval(\n    const ParametricObject<T>&\
    \ object,\n    const AxisProjection<T>& projection\n) {\n    using W = wide_type<T>;\n\
    \    const W origin = projection(object.origin);\n    const W through = projection(object.through);\n\
    \    if (object.domain == Domain::Line) {\n        return ParameterInterval<T>{false,\
    \ false, W(0), W(0)};\n    }\n    if (object.domain == Domain::Segment) {\n  \
    \      return ParameterInterval<T>{\n            true,\n            true,\n  \
    \          std::min(origin, through),\n            std::max(origin, through),\n\
    \        };\n    }\n    if (origin < through) {\n        return ParameterInterval<T>{true,\
    \ false, origin, W(0)};\n    }\n    return ParameterInterval<T>{false, true, W(0),\
    \ origin};\n}\n\ntemplate <Coordinate T>\nParameterInterval<T> intersect_intervals(\n\
    \    ParameterInterval<T> first,\n    const ParameterInterval<T>& second\n) {\n\
    \    if (\n        second.has_lower &&\n        (!first.has_lower || first.lower\
    \ < second.lower)\n    ) {\n        first.has_lower = true;\n        first.lower\
    \ = second.lower;\n    }\n    if (\n        second.has_upper &&\n        (!first.has_upper\
    \ || second.upper < first.upper)\n    ) {\n        first.has_upper = true;\n \
    \       first.upper = second.upper;\n    }\n    return first;\n}\n\ntemplate <Coordinate\
    \ T>\nPoint<long double> point_at_projection(\n    const ParametricObject<T>&\
    \ object,\n    const AxisProjection<T>& projection,\n    long double target\n\
    ) {\n    const long double origin =\n        static_cast<long double>(projection(object.origin));\n\
    \    const long double through =\n        static_cast<long double>(projection(object.through));\n\
    \    const long double ratio = (target - origin) / (through - origin);\n    const\
    \ Point<long double> point(object.origin);\n    const Point<long double> direction\
    \ =\n        Point<long double>(object.through) - point;\n    return point + direction\
    \ * ratio;\n}\n\ntemplate <Coordinate T>\nLinearIntersection collinear_intersection(\n\
    \    const ParametricObject<T>& first,\n    const ParametricObject<T>& second,\n\
    \    long double eps\n) {\n    using W = wide_type<T>;\n    const AxisProjection<T>\
    \ projection = axis_projection(first);\n    const ParameterInterval<T> first_interval\
    \ =\n        parameter_interval(first, projection);\n    const ParameterInterval<T>\
    \ second_interval =\n        parameter_interval(second, projection);\n    const\
    \ ParameterInterval<T> common =\n        intersect_intervals(first_interval, second_interval);\n\
    \n    W scale = predicate_detail::absolute(\n        projection(first.through)\
    \ - projection(first.origin)\n    );\n    scale = std::max(\n        scale,\n\
    \        predicate_detail::absolute(\n            projection(second.through) -\
    \ projection(second.origin)\n        )\n    );\n\n    if (common.has_lower &&\
    \ common.has_upper) {\n        const int order = predicate_detail::scaled_sign<std::integral<T>>(\n\
    \            common.lower - common.upper,\n            scale,\n            eps\n\
    \        );\n        if (order > 0) return make_empty();\n        if (order ==\
    \ 0) {\n            const long double coordinate =\n                (\n      \
    \              static_cast<long double>(common.lower) +\n                    static_cast<long\
    \ double>(common.upper)\n                ) / 2.0L;\n            return make_point(\n\
    \                point_at_projection(first, projection, coordinate)\n        \
    \    );\n        }\n        return make_object(\n            LinearIntersectionKind::Segment,\n\
    \            point_at_projection(\n                first,\n                projection,\n\
    \                static_cast<long double>(common.lower)\n            ),\n    \
    \        point_at_projection(\n                first,\n                projection,\n\
    \                static_cast<long double>(common.upper)\n            )\n     \
    \   );\n    }\n\n    const Point<long double> direction =\n        Point<long\
    \ double>(first.through) -\n        Point<long double>(first.origin);\n    if\
    \ (common.has_lower) {\n        const Point<long double> origin = point_at_projection(\n\
    \            first,\n            projection,\n            static_cast<long double>(common.lower)\n\
    \        );\n        return make_object(\n            LinearIntersectionKind::Ray,\n\
    \            origin,\n            origin + direction\n        );\n    }\n    if\
    \ (common.has_upper) {\n        const Point<long double> origin = point_at_projection(\n\
    \            first,\n            projection,\n            static_cast<long double>(common.upper)\n\
    \        );\n        return make_object(\n            LinearIntersectionKind::Ray,\n\
    \            origin,\n            origin - direction\n        );\n    }\n    return\
    \ make_object(\n        LinearIntersectionKind::Line,\n        first.origin,\n\
    \        first.through\n    );\n}\n\ntemplate <Coordinate T>\nLinearIntersection\
    \ intersect(\n    const ParametricObject<T>& first,\n    const ParametricObject<T>&\
    \ second,\n    long double eps\n) {\n    const bool first_degenerate = first.origin\
    \ == first.through;\n    const bool second_degenerate = second.origin == second.through;\n\
    \    if (first_degenerate) {\n        assert(first.domain == Domain::Segment);\n\
    \        if (contains(second, first.origin, eps)) {\n            return make_point(first.origin);\n\
    \        }\n        return make_empty();\n    }\n    if (second_degenerate) {\n\
    \        assert(second.domain == Domain::Segment);\n        if (contains(first,\
    \ second.origin, eps)) {\n            return make_point(second.origin);\n    \
    \    }\n        return make_empty();\n    }\n\n    const linear_parameter_detail::Parameters<T>\
    \ values =\n        linear_parameter_detail::parameters(\n        first.origin,\n\
    \        first.through,\n        second.origin,\n        second.through\n    );\n\
    \    if (linear_parameter_detail::denominator_sign(values, eps) != 0) {\n    \
    \    if (\n            !accepts_parameter<T>(\n                first.domain,\n\
    \                values.first_numerator,\n                values.denominator,\n\
    \                eps\n            ) ||\n            !accepts_parameter<T>(\n \
    \               second.domain,\n                values.second_numerator,\n   \
    \             values.denominator,\n                eps\n            )\n      \
    \  ) {\n            return make_empty();\n        }\n        return make_point(\n\
    \            point_at_ratio(\n                first,\n                values.first_numerator,\n\
    \                values.denominator\n            )\n        );\n    }\n    if\
    \ (\n        orientation(\n            first.origin,\n            first.through,\n\
    \            second.origin,\n            eps\n        ) != 0\n    ) {\n      \
    \  return make_empty();\n    }\n    return collinear_intersection(first, second,\
    \ eps);\n}\n\n}  // namespace linear_intersection_detail\n\ntemplate <Coordinate\
    \ T>\nLinearIntersection linear_intersection(\n    const Line<T>& first,\n   \
    \ const Line<T>& second,\n    long double eps = 1e-12L\n) {\n    return linear_intersection_detail::intersect(\n\
    \        linear_intersection_detail::parametric_object(first),\n        linear_intersection_detail::parametric_object(second),\n\
    \        eps\n    );\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Line<T>& line,\n    const Segment<T>& segment,\n    long double eps\
    \ = 1e-12L\n) {\n    return linear_intersection_detail::intersect(\n        linear_intersection_detail::parametric_object(line),\n\
    \        linear_intersection_detail::parametric_object(segment),\n        eps\n\
    \    );\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Segment<T>& segment,\n    const Line<T>& line,\n    long double eps\
    \ = 1e-12L\n) {\n    return linear_intersection_detail::intersect(\n        linear_intersection_detail::parametric_object(segment),\n\
    \        linear_intersection_detail::parametric_object(line),\n        eps\n \
    \   );\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Segment<T>& first,\n    const Segment<T>& second,\n    long double\
    \ eps = 1e-12L\n) {\n    return linear_intersection_detail::intersect(\n     \
    \   linear_intersection_detail::parametric_object(first),\n        linear_intersection_detail::parametric_object(second),\n\
    \        eps\n    );\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Ray<T>& ray,\n    const Line<T>& line,\n    long double eps = 1e-12L\n\
    ) {\n    return linear_intersection_detail::intersect(\n        linear_intersection_detail::parametric_object(ray),\n\
    \        linear_intersection_detail::parametric_object(line),\n        eps\n \
    \   );\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Line<T>& line,\n    const Ray<T>& ray,\n    long double eps = 1e-12L\n\
    ) {\n    return linear_intersection_detail::intersect(\n        linear_intersection_detail::parametric_object(line),\n\
    \        linear_intersection_detail::parametric_object(ray),\n        eps\n  \
    \  );\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Ray<T>& ray,\n    const Segment<T>& segment,\n    long double eps =\
    \ 1e-12L\n) {\n    return linear_intersection_detail::intersect(\n        linear_intersection_detail::parametric_object(ray),\n\
    \        linear_intersection_detail::parametric_object(segment),\n        eps\n\
    \    );\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Segment<T>& segment,\n    const Ray<T>& ray,\n    long double eps =\
    \ 1e-12L\n) {\n    return linear_intersection_detail::intersect(\n        linear_intersection_detail::parametric_object(segment),\n\
    \        linear_intersection_detail::parametric_object(ray),\n        eps\n  \
    \  );\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Ray<T>& first,\n    const Ray<T>& second,\n    long double eps = 1e-12L\n\
    ) {\n    return linear_intersection_detail::intersect(\n        linear_intersection_detail::parametric_object(first),\n\
    \        linear_intersection_detail::parametric_object(second),\n        eps\n\
    \    );\n}\n\nnamespace closest_points_detail {\n\ninline ClosestPoints reversed(const\
    \ ClosestPoints& result) {\n    return ClosestPoints{result.second, result.first};\n\
    }\n\ninline bool point_less(\n    const Point<long double>& first,\n    const\
    \ Point<long double>& second\n) {\n    if (first.x != second.x) return first.x\
    \ < second.x;\n    return first.y < second.y;\n}\n\ninline ClosestPoints common_point(const\
    \ LinearIntersection& intersection) {\n    assert(intersection.kind != LinearIntersectionKind::Empty);\n\
    \    Point<long double> point = intersection.first;\n    if (intersection.kind\
    \ == LinearIntersectionKind::Segment) {\n        if (point_less(intersection.second,\
    \ point)) {\n            point = intersection.second;\n        }\n    } else if\
    \ (intersection.kind == LinearIntersectionKind::Line) {\n        const Line<long\
    \ double> line{\n            intersection.first,\n            intersection.second\n\
    \        };\n        point = projection(line, Point<long double>(0, 0));\n   \
    \ }\n    return ClosestPoints{point, point};\n}\n\ninline long double separation2(const\
    \ ClosestPoints& result) {\n    return distance2(result.first, result.second);\n\
    }\n\ninline bool canonical_less(\n    const ClosestPoints& first,\n    const ClosestPoints&\
    \ second\n) {\n    Point<long double> first_start = first.first;\n    Point<long\
    \ double> first_finish = first.second;\n    if (point_less(first_finish, first_start))\
    \ {\n        std::swap(first_start, first_finish);\n    }\n    Point<long double>\
    \ second_start = second.first;\n    Point<long double> second_finish = second.second;\n\
    \    if (point_less(second_finish, second_start)) {\n        std::swap(second_start,\
    \ second_finish);\n    }\n    if (point_less(first_start, second_start)) return\
    \ true;\n    if (point_less(second_start, first_start)) return false;\n    return\
    \ point_less(first_finish, second_finish);\n}\n\ninline void consider(ClosestPoints&\
    \ best, const ClosestPoints& candidate) {\n    const long double best_distance\
    \ = separation2(best);\n    const long double candidate_distance = separation2(candidate);\n\
    \    if (\n        candidate_distance < best_distance ||\n        (\n        \
    \    candidate_distance == best_distance &&\n            canonical_less(candidate,\
    \ best)\n        )\n    ) {\n        best = candidate;\n    }\n}\n\n}  // namespace\
    \ closest_points_detail\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n\
    \    const Point<T>& first,\n    const Point<T>& second\n) {\n    return ClosestPoints{\n\
    \        Point<long double>(first),\n        Point<long double>(second),\n   \
    \ };\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n    const Line<T>&\
    \ line,\n    const Point<T>& point\n) {\n    return ClosestPoints{\n        projection(line,\
    \ point),\n        Point<long double>(point),\n    };\n}\n\ntemplate <Coordinate\
    \ T>\nClosestPoints closest_points(\n    const Point<T>& point,\n    const Line<T>&\
    \ line\n) {\n    return closest_points_detail::reversed(closest_points(line, point));\n\
    }\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n    const Segment<T>&\
    \ segment,\n    const Point<T>& point\n) {\n    return ClosestPoints{\n      \
    \  projection(segment, point),\n        Point<long double>(point),\n    };\n}\n\
    \ntemplate <Coordinate T>\nClosestPoints closest_points(\n    const Point<T>&\
    \ point,\n    const Segment<T>& segment\n) {\n    return closest_points_detail::reversed(closest_points(segment,\
    \ point));\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n    const\
    \ Ray<T>& ray,\n    const Point<T>& point\n) {\n    return ClosestPoints{\n  \
    \      projection(ray, point),\n        Point<long double>(point),\n    };\n}\n\
    \ntemplate <Coordinate T>\nClosestPoints closest_points(\n    const Point<T>&\
    \ point,\n    const Ray<T>& ray\n) {\n    return closest_points_detail::reversed(closest_points(ray,\
    \ point));\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n    const\
    \ Line<T>& first,\n    const Line<T>& second,\n    long double eps = 1e-12L\n\
    ) {\n    const LinearIntersection intersection =\n        linear_intersection(first,\
    \ second, eps);\n    if (intersection.kind != LinearIntersectionKind::Empty) {\n\
    \        return closest_points_detail::common_point(intersection);\n    }\n  \
    \  ClosestPoints result = closest_points(first, second.a);\n    closest_points_detail::consider(\n\
    \        result,\n        closest_points(first.a, second)\n    );\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n    const\
    \ Line<T>& line,\n    const Segment<T>& segment,\n    long double eps = 1e-12L\n\
    ) {\n    const LinearIntersection intersection =\n        linear_intersection(line,\
    \ segment, eps);\n    if (intersection.kind != LinearIntersectionKind::Empty)\
    \ {\n        return closest_points_detail::common_point(intersection);\n    }\n\
    \    ClosestPoints result = closest_points(line, segment.a);\n    closest_points_detail::consider(\n\
    \        result,\n        closest_points(line, segment.b)\n    );\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n    const\
    \ Segment<T>& segment,\n    const Line<T>& line,\n    long double eps = 1e-12L\n\
    ) {\n    return closest_points_detail::reversed(\n        closest_points(line,\
    \ segment, eps)\n    );\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n\
    \    const Segment<T>& first,\n    const Segment<T>& second,\n    long double\
    \ eps = 1e-12L\n) {\n    const LinearIntersection intersection =\n        linear_intersection(first,\
    \ second, eps);\n    if (intersection.kind != LinearIntersectionKind::Empty) {\n\
    \        return closest_points_detail::common_point(intersection);\n    }\n  \
    \  ClosestPoints result = closest_points(first, second.a);\n    closest_points_detail::consider(\n\
    \        result,\n        closest_points(first, second.b)\n    );\n    closest_points_detail::consider(\n\
    \        result,\n        closest_points(first.a, second)\n    );\n    closest_points_detail::consider(\n\
    \        result,\n        closest_points(first.b, second)\n    );\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n    const\
    \ Line<T>& line,\n    const Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n\
    \    const LinearIntersection intersection =\n        linear_intersection(line,\
    \ ray, eps);\n    if (intersection.kind != LinearIntersectionKind::Empty) {\n\
    \        return closest_points_detail::common_point(intersection);\n    }\n  \
    \  return closest_points(line, ray.origin);\n}\n\ntemplate <Coordinate T>\nClosestPoints\
    \ closest_points(\n    const Ray<T>& ray,\n    const Line<T>& line,\n    long\
    \ double eps = 1e-12L\n) {\n    return closest_points_detail::reversed(closest_points(line,\
    \ ray, eps));\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n \
    \   const Ray<T>& ray,\n    const Segment<T>& segment,\n    long double eps =\
    \ 1e-12L\n) {\n    const LinearIntersection intersection =\n        linear_intersection(ray,\
    \ segment, eps);\n    if (intersection.kind != LinearIntersectionKind::Empty)\
    \ {\n        return closest_points_detail::common_point(intersection);\n    }\n\
    \    ClosestPoints result = closest_points(ray, segment.a);\n    closest_points_detail::consider(\n\
    \        result,\n        closest_points(ray, segment.b)\n    );\n    closest_points_detail::consider(\n\
    \        result,\n        closest_points(ray.origin, segment)\n    );\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n    const\
    \ Segment<T>& segment,\n    const Ray<T>& ray,\n    long double eps = 1e-12L\n\
    ) {\n    return closest_points_detail::reversed(\n        closest_points(ray,\
    \ segment, eps)\n    );\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_points(\n\
    \    const Ray<T>& first,\n    const Ray<T>& second,\n    long double eps = 1e-12L\n\
    ) {\n    const LinearIntersection intersection =\n        linear_intersection(first,\
    \ second, eps);\n    if (intersection.kind != LinearIntersectionKind::Empty) {\n\
    \        return closest_points_detail::common_point(intersection);\n    }\n  \
    \  ClosestPoints result = closest_points(first, second.origin);\n    closest_points_detail::consider(\n\
    \        result,\n        closest_points(first.origin, second)\n    );\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nlong double distance(const Line<T>& line,\
    \ const Point<T>& point) {\n    const ClosestPoints result = closest_points(line,\
    \ point);\n    return geometry::distance(result.first, result.second);\n}\n\n\
    template <Coordinate T>\nlong double distance(const Point<T>& point, const Line<T>&\
    \ line) {\n    return distance(line, point);\n}\n\ntemplate <Coordinate T>\nlong\
    \ double distance(const Segment<T>& segment, const Point<T>& point) {\n    const\
    \ ClosestPoints result = closest_points(segment, point);\n    return geometry::distance(result.first,\
    \ result.second);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Point<T>&\
    \ point, const Segment<T>& segment) {\n    return distance(segment, point);\n\
    }\n\ntemplate <Coordinate T>\nlong double distance(const Ray<T>& ray, const Point<T>&\
    \ point) {\n    const ClosestPoints result = closest_points(ray, point);\n   \
    \ return geometry::distance(result.first, result.second);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Point<T>& point, const Ray<T>& ray) {\n    return\
    \ distance(ray, point);\n}\n\ntemplate <Coordinate T>\nlong double distance(const\
    \ Line<T>& first, const Line<T>& second) {\n    const ClosestPoints result = closest_points(first,\
    \ second);\n    return geometry::distance(result.first, result.second);\n}\n\n\
    template <Coordinate T>\nlong double distance(const Line<T>& line, const Segment<T>&\
    \ segment) {\n    const ClosestPoints result = closest_points(line, segment);\n\
    \    return geometry::distance(result.first, result.second);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Segment<T>& segment, const Line<T>& line) {\n\
    \    return distance(line, segment);\n}\n\ntemplate <Coordinate T>\nlong double\
    \ distance(const Segment<T>& first, const Segment<T>& second) {\n    const ClosestPoints\
    \ result = closest_points(first, second);\n    return geometry::distance(result.first,\
    \ result.second);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Line<T>&\
    \ line, const Ray<T>& ray) {\n    const ClosestPoints result = closest_points(line,\
    \ ray);\n    return geometry::distance(result.first, result.second);\n}\n\ntemplate\
    \ <Coordinate T>\nlong double distance(const Ray<T>& ray, const Line<T>& line)\
    \ {\n    return distance(line, ray);\n}\n\ntemplate <Coordinate T>\nlong double\
    \ distance(const Ray<T>& ray, const Segment<T>& segment) {\n    const ClosestPoints\
    \ result = closest_points(ray, segment);\n    return geometry::distance(result.first,\
    \ result.second);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Segment<T>&\
    \ segment, const Ray<T>& ray) {\n    return distance(ray, segment);\n}\n\ntemplate\
    \ <Coordinate T>\nlong double distance(const Ray<T>& first, const Ray<T>& second)\
    \ {\n    const ClosestPoints result = closest_points(first, second);\n    return\
    \ geometry::distance(result.first, result.second);\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n#line 17 \"geometry/half_plane_intersection.hpp\"\n\
    \nnamespace m1une {\nnamespace geometry {\n\nenum class HalfPlaneIntersectionStatus\
    \ {\n    Empty,\n    Unbounded,\n    Degenerate,\n    Bounded,\n};\n\nstruct HalfPlaneIntersectionResult\
    \ {\n    HalfPlaneIntersectionStatus status;\n    std::vector<Point<long double>>\
    \ polygon;\n};\n\nnamespace half_plane_intersection_detail {\n\nstruct HalfPlane\
    \ {\n    Point<long double> point;\n    Point<long double> direction;\n    long\
    \ double angle;\n\n    HalfPlane(\n        const Point<long double>& point_value,\n\
    \        const Point<long double>& direction_value\n    ) : point(point_value),\
    \ direction(direction_value) {\n        angle = std::atan2(direction.y, direction.x);\n\
    \        if (angle < 0) angle += 2 * std::numbers::pi_v<long double>;\n    }\n\
    };\n\ninline bool direction_less(const HalfPlane& first, const HalfPlane& second)\
    \ {\n    return first.angle < second.angle;\n}\n\ninline bool parallel(\n    const\
    \ HalfPlane& first,\n    const HalfPlane& second,\n    long double eps\n) {\n\
    \    return std::fabs(cross(first.direction, second.direction)) <= eps;\n}\n\n\
    inline bool same_direction(\n    const HalfPlane& first,\n    const HalfPlane&\
    \ second,\n    long double eps\n) {\n    return parallel(first, second, eps) &&\n\
    \           dot(first.direction, second.direction) > 0;\n}\n\ninline bool outside(\n\
    \    const HalfPlane& half_plane,\n    const Point<long double>& point,\n    long\
    \ double eps\n) {\n    return cross(half_plane.direction, point - half_plane.point)\
    \ < -eps;\n}\n\ninline bool more_restrictive(\n    const HalfPlane& candidate,\n\
    \    const HalfPlane& current,\n    long double eps\n) {\n    return cross(\n\
    \        current.direction,\n        candidate.point - current.point\n    ) >\
    \ eps;\n}\n\ninline std::optional<Point<long double>> intersection(\n    const\
    \ HalfPlane& first,\n    const HalfPlane& second,\n    long double eps\n) {\n\
    \    long double denominator = cross(first.direction, second.direction);\n   \
    \ if (std::fabs(denominator) <= eps) return std::nullopt;\n    long double ratio\
    \ = cross(\n        second.point - first.point,\n        second.direction\n  \
    \  ) / denominator;\n    return first.point + first.direction * ratio;\n}\n\n\
    inline void merge_same_direction(\n    std::vector<HalfPlane>& half_planes,\n\
    \    const HalfPlane& half_plane,\n    long double eps\n) {\n    if (\n      \
    \  half_planes.empty() ||\n        !same_direction(half_planes.back(), half_plane,\
    \ eps)\n    ) {\n        half_planes.push_back(half_plane);\n        return;\n\
    \    }\n    if (more_restrictive(half_plane, half_planes.back(), eps)) {\n   \
    \     half_planes.back() = half_plane;\n    }\n}\n\ninline void merge_cyclic_ends(\n\
    \    std::vector<HalfPlane>& half_planes,\n    long double eps\n) {\n    if (\n\
    \        half_planes.size() < 2 ||\n        !same_direction(half_planes.front(),\
    \ half_planes.back(), eps)\n    ) {\n        return;\n    }\n    if (more_restrictive(half_planes.back(),\
    \ half_planes.front(), eps)) {\n        half_planes.front() = half_planes.back();\n\
    \    }\n    half_planes.pop_back();\n}\n\ninline bool has_feasible_point(\n  \
    \  std::vector<HalfPlane> half_planes,\n    long double eps\n) {\n    std::mt19937_64\
    \ generator(0x6a09e667f3bcc909ULL);\n    std::shuffle(half_planes.begin(), half_planes.end(),\
    \ generator);\n\n    Point<long double> feasible(0, 0);\n    for (std::size_t\
    \ index = 0; index < half_planes.size(); ++index) {\n        const HalfPlane&\
    \ current = half_planes[index];\n        if (!outside(current, feasible, eps))\
    \ continue;\n\n        Point<long double> normal(\n            -current.direction.y,\n\
    \            current.direction.x\n        );\n        Point<long double> base\
    \ = normal * dot(normal, current.point);\n        long double lower = -std::numeric_limits<long\
    \ double>::infinity();\n        long double upper = std::numeric_limits<long double>::infinity();\n\
    \        for (std::size_t previous_index = 0;\n             previous_index < index;\n\
    \             ++previous_index) {\n            const HalfPlane& previous = half_planes[previous_index];\n\
    \            long double coefficient = cross(\n                previous.direction,\n\
    \                current.direction\n            );\n            long double constant\
    \ = cross(\n                previous.direction,\n                base - previous.point\n\
    \            );\n            if (std::fabs(coefficient) <= eps) {\n          \
    \      if (constant < -eps) return false;\n                continue;\n       \
    \     }\n\n            long double bound = (-eps - constant) / coefficient;\n\
    \            if (coefficient > 0) {\n                lower = std::max(lower, bound);\n\
    \            } else {\n                upper = std::min(upper, bound);\n     \
    \       }\n            if (lower > upper) return false;\n        }\n\n       \
    \ long double parameter = 0;\n        if (parameter < lower) parameter = lower;\n\
    \        if (parameter > upper) parameter = upper;\n        feasible = base +\
    \ current.direction * parameter;\n    }\n    return true;\n}\n\ninline bool has_bounded_recession_cone(\n\
    \    const std::vector<HalfPlane>& half_planes,\n    long double eps\n) {\n  \
    \  if (half_planes.empty()) return false;\n\n    constexpr long double pi = std::numbers::pi_v<long\
    \ double>;\n    long double maximum_gap =\n        half_planes.front().angle +\
    \ 2 * pi - half_planes.back().angle;\n    for (std::size_t index = 1; index <\
    \ half_planes.size(); ++index) {\n        maximum_gap = std::max(\n          \
    \  maximum_gap,\n            half_planes[index].angle - half_planes[index - 1].angle\n\
    \        );\n    }\n    return maximum_gap < pi - eps;\n}\n\n}  // namespace half_plane_intersection_detail\n\
    \n// Each directed line keeps its closed left half-plane. Returns the vertices\
    \ of\n// a bounded intersection with positive area in counterclockwise order.\
    \ Empty,\n// unbounded, and bounded zero-area intersections have distinct statuses.\n\
    template <Coordinate T>\nHalfPlaneIntersectionResult half_plane_intersection(\n\
    \    const std::vector<Line<T>>& half_planes,\n    long double eps = 1e-12L\n\
    ) {\n    using half_plane_intersection_detail::HalfPlane;\n    namespace detail\
    \ = half_plane_intersection_detail;\n\n    assert(eps >= 0);\n    std::vector<HalfPlane>\
    \ sorted;\n    sorted.reserve(half_planes.size());\n    for (const Line<T>& line\
    \ : half_planes) {\n        assert(line.a != line.b);\n        Point<long double>\
    \ point(line.a);\n        Point<long double> direction = Point<long double>(line.b)\
    \ - point;\n        long double length = norm(direction);\n        direction =\
    \ direction / length;\n        sorted.push_back(HalfPlane{point, direction});\n\
    \    }\n    if (!detail::has_feasible_point(sorted, eps)) {\n        return HalfPlaneIntersectionResult{\n\
    \            HalfPlaneIntersectionStatus::Empty,\n            {},\n        };\n\
    \    }\n    std::sort(sorted.begin(), sorted.end(), detail::direction_less);\n\
    \    if (!detail::has_bounded_recession_cone(sorted, eps)) {\n        return HalfPlaneIntersectionResult{\n\
    \            HalfPlaneIntersectionStatus::Unbounded,\n            {},\n      \
    \  };\n    }\n    if (sorted.size() < 3) {\n        return HalfPlaneIntersectionResult{\n\
    \            HalfPlaneIntersectionStatus::Degenerate,\n            {},\n     \
    \   };\n    }\n\n    std::vector<HalfPlane> unique;\n    unique.reserve(sorted.size());\n\
    \    for (const HalfPlane& half_plane : sorted) {\n        detail::merge_same_direction(unique,\
    \ half_plane, eps);\n    }\n    detail::merge_cyclic_ends(unique, eps);\n    if\
    \ (unique.size() < 3) {\n        return HalfPlaneIntersectionResult{\n       \
    \     HalfPlaneIntersectionStatus::Degenerate,\n            {},\n        };\n\
    \    }\n\n    std::deque<HalfPlane> deque;\n    for (const HalfPlane& half_plane\
    \ : unique) {\n        while (deque.size() >= 2) {\n            auto point = detail::intersection(\n\
    \                deque[deque.size() - 2],\n                deque.back(),\n   \
    \             eps\n            );\n            if (!point.has_value()) {\n   \
    \             return HalfPlaneIntersectionResult{\n                    HalfPlaneIntersectionStatus::Degenerate,\n\
    \                    {},\n                };\n            }\n            if (!detail::outside(half_plane,\
    \ *point, eps)) break;\n            deque.pop_back();\n        }\n        while\
    \ (deque.size() >= 2) {\n            auto point = detail::intersection(deque[0],\
    \ deque[1], eps);\n            if (!point.has_value()) {\n                return\
    \ HalfPlaneIntersectionResult{\n                    HalfPlaneIntersectionStatus::Degenerate,\n\
    \                    {},\n                };\n            }\n            if (!detail::outside(half_plane,\
    \ *point, eps)) break;\n            deque.pop_front();\n        }\n        deque.push_back(half_plane);\n\
    \    }\n\n    while (deque.size() >= 3) {\n        auto point = detail::intersection(\n\
    \            deque[deque.size() - 2],\n            deque.back(),\n           \
    \ eps\n        );\n        if (!point.has_value()) {\n            return HalfPlaneIntersectionResult{\n\
    \                HalfPlaneIntersectionStatus::Degenerate,\n                {},\n\
    \            };\n        }\n        if (!detail::outside(deque.front(), *point,\
    \ eps)) break;\n        deque.pop_back();\n    }\n    while (deque.size() >= 3)\
    \ {\n        auto point = detail::intersection(deque[0], deque[1], eps);\n   \
    \     if (!point.has_value()) {\n            return HalfPlaneIntersectionResult{\n\
    \                HalfPlaneIntersectionStatus::Degenerate,\n                {},\n\
    \            };\n        }\n        if (!detail::outside(deque.back(), *point,\
    \ eps)) break;\n        deque.pop_front();\n    }\n    if (deque.size() < 3) {\n\
    \        return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    std::vector<Point<long double>> polygon;\n\
    \    polygon.reserve(deque.size());\n    for (std::size_t index = 0; index < deque.size();\
    \ ++index) {\n        auto point = detail::intersection(\n            deque[index],\n\
    \            deque[(index + 1) % deque.size()],\n            eps\n        );\n\
    \        if (!point.has_value()) {\n            return HalfPlaneIntersectionResult{\n\
    \                HalfPlaneIntersectionStatus::Degenerate,\n                {},\n\
    \            };\n        }\n        if (\n            polygon.empty() ||\n   \
    \         distance(polygon.back(), *point) > eps\n        ) {\n            polygon.push_back(*point);\n\
    \        }\n    }\n    if (\n        polygon.size() >= 2 &&\n        distance(polygon.front(),\
    \ polygon.back()) <= eps\n    ) {\n        polygon.pop_back();\n    }\n    if\
    \ (polygon.size() < 3) {\n        return HalfPlaneIntersectionResult{\n      \
    \      HalfPlaneIntersectionStatus::Degenerate,\n            {},\n        };\n\
    \    }\n\n    long double signed_area2 = 0;\n    Point<long double> origin = polygon.front();\n\
    \    for (std::size_t index = 1; index + 1 < polygon.size(); ++index) {\n    \
    \    signed_area2 += cross(\n            polygon[index] - origin,\n          \
    \  polygon[index + 1] - origin\n        );\n    }\n    if (signed_area2 <= eps)\
    \ {\n        return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    auto first = std::min_element(polygon.begin(),\
    \ polygon.end());\n    std::rotate(polygon.begin(), first, polygon.end());\n \
    \   return HalfPlaneIntersectionResult{\n        HalfPlaneIntersectionStatus::Bounded,\n\
    \        std::move(polygon),\n    };\n}\n\n}  // namespace geometry\n}  // namespace\
    \ m1une\n\n\n#line 1 \"geometry/minkowski_sum.hpp\"\n\n\n\n#line 8 \"geometry/minkowski_sum.hpp\"\
    \n\n#line 1 \"geometry/detail/convex_polygon_normalize.hpp\"\n\n\n\n#line 8 \"\
    geometry/detail/convex_polygon_normalize.hpp\"\n\n#line 10 \"geometry/detail/convex_polygon_normalize.hpp\"\
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
    }  // namespace m1une\n\n\n#line 1 \"geometry/polygon.hpp\"\n\n\n\n#line 14 \"\
    geometry/polygon.hpp\"\n\n#line 1 \"geometry/circle.hpp\"\n\n\n\n#line 13 \"geometry/circle.hpp\"\
    \n\n#line 15 \"geometry/circle.hpp\"\n\nnamespace m1une {\nnamespace geometry\
    \ {\n\ntemplate <Coordinate T>\nstruct Circle {\n    Point<T> center;\n    T radius;\n\
    \    bool filled = true;\n};\n\nenum class PointInCircle {\n    Outside = 0,\n\
    \    Boundary = 1,\n    Inside = 2,\n};\n\nenum class CircleRelation {\n    Separate,\n\
    \    ExternallyTangent,\n    Intersecting,\n    InternallyTangent,\n    Contained,\n\
    \    Coincident,\n};\n\nenum class AngularCoverageKind {\n    Empty,\n    Point,\n\
    \    Arc,\n    Full,\n};\n\nstruct AngularCoverage {\n    AngularCoverageKind\
    \ kind = AngularCoverageKind::Empty;\n    long double begin = 0.0L;\n    long\
    \ double end = 0.0L;\n};\n\nstruct CircleContact {\n    Point<long double> point;\n\
    \    long double first_argument = 0.0L;\n    long double second_argument = 0.0L;\n\
    };\n\nenum class CircleContactKind {\n    Empty,\n    Point,\n    TwoPoints,\n\
    \    Coincident,\n};\n\nstruct CircleCircleIntersection {\n    CircleRelation\
    \ relation = CircleRelation::Separate;\n    CircleContactKind contact_kind = CircleContactKind::Empty;\n\
    \    std::array<CircleContact, 2> contacts;\n    AngularCoverage first_inside_second;\n\
    \    AngularCoverage second_inside_first;\n\n    constexpr int contact_count()\
    \ const noexcept {\n        if (contact_kind == CircleContactKind::Point) return\
    \ 1;\n        if (contact_kind == CircleContactKind::TwoPoints) return 2;\n  \
    \      return 0;\n    }\n};\n\nstruct CircleLinearContact {\n    Point<long double>\
    \ point;\n    long double circle_argument = 0.0L;\n    long double linear_parameter\
    \ = 0.0L;\n};\n\nstruct CircleLinearIntersection {\n    int contact_count = 0;\n\
    \    std::array<CircleLinearContact, 2> contacts;\n};\n\nnamespace circle_detail\
    \ {\n\ninline int compare(long double first, long double second, long double eps)\
    \ {\n    if (first < second - eps) return -1;\n    if (first > second + eps) return\
    \ 1;\n    return 0;\n}\n\ninline bool close(\n    const Point<long double>& first,\n\
    \    const Point<long double>& second,\n    long double eps\n) {\n    return geometry::distance(first,\
    \ second) <= eps;\n}\n\ninline void push_unique(\n    std::vector<Point<long double>>&\
    \ points,\n    const Point<long double>& point,\n    long double eps\n) {\n  \
    \  for (const Point<long double>& existing : points) {\n        if (close(existing,\
    \ point, eps)) return;\n    }\n    points.push_back(point);\n}\n\ninline bool\
    \ same_line(\n    const Line<long double>& first,\n    const Line<long double>&\
    \ second,\n    long double eps\n) {\n    Point<long double> first_direction =\
    \ first.b - first.a;\n    Point<long double> second_direction = second.b - second.a;\n\
    \    if (std::fabs(cross(first_direction, second_direction)) > eps) {\n      \
    \  return false;\n    }\n    return std::fabs(cross(first_direction, second.a\
    \ - first.a)) <= eps;\n}\n\ninline Line<long double> tangent_line(\n    const\
    \ Point<long double>& contact,\n    Point<long double> normal,\n    long double\
    \ eps\n) {\n    Point<long double> direction(-normal.y, normal.x);\n    if (\n\
    \        direction.x < -eps ||\n        (std::fabs(direction.x) <= eps && direction.y\
    \ < 0)\n    ) {\n        direction = -direction;\n    }\n    return Line<long\
    \ double>{contact, contact + direction};\n}\n\ninline long double circular_segment_angle_term(\n\
    \    long double angle,\n    long double sine,\n    long double cosine\n) {\n\
    \    if (angle >= 0.01L) return angle - sine * cosine;\n    const long double\
    \ squared = angle * angle;\n    return angle * squared * (\n        2.0L / 3.0L\
    \ +\n        squared * (\n            -2.0L / 15.0L +\n            squared * (4.0L\
    \ / 315.0L - squared * 2.0L / 2835.0L)\n        )\n    );\n}\n\ninline long double\
    \ segment_disk_signed_area(\n    const Point<long double>& first,\n    const Point<long\
    \ double>& second,\n    long double radius,\n    long double eps\n) {\n    const\
    \ Point<long double> direction = second - first;\n    const long double quadratic\
    \ = dot(direction, direction);\n    if (quadratic == 0.0L || radius == 0.0L) return\
    \ 0.0L;\n\n    std::vector<long double> cuts = {0.0L, 1.0L};\n    const long double\
    \ linear = 2.0L * dot(first, direction);\n    const long double constant = dot(first,\
    \ first) - radius * radius;\n    const long double discriminant =\n        linear\
    \ * linear - 4.0L * quadratic * constant;\n    const long double tolerance = eps\
    \ * std::max({\n        1.0L,\n        std::fabs(linear * linear),\n        std::fabs(4.0L\
    \ * quadratic * constant)\n    });\n    if (discriminant >= -tolerance) {\n  \
    \      const long double root = std::sqrt(std::max(0.0L, discriminant));\n   \
    \     const long double first_ratio =\n            (-linear - root) / (2.0L *\
    \ quadratic);\n        const long double second_ratio =\n            (-linear\
    \ + root) / (2.0L * quadratic);\n        if (eps < first_ratio && first_ratio\
    \ < 1.0L - eps) {\n            cuts.push_back(first_ratio);\n        }\n     \
    \   if (eps < second_ratio && second_ratio < 1.0L - eps) {\n            cuts.push_back(second_ratio);\n\
    \        }\n    }\n    std::sort(cuts.begin(), cuts.end());\n    cuts.erase(\n\
    \        std::unique(\n            cuts.begin(),\n            cuts.end(),\n  \
    \          [eps](long double left, long double right) {\n                return\
    \ std::fabs(left - right) <= eps;\n            }\n        ),\n        cuts.end()\n\
    \    );\n\n    long double result = 0.0L;\n    for (std::size_t index = 1; index\
    \ < cuts.size(); ++index) {\n        const long double left = cuts[index - 1];\n\
    \        const long double right = cuts[index];\n        const Point<long double>\
    \ a = first + direction * left;\n        const Point<long double> b = first +\
    \ direction * right;\n        const Point<long double> middle =\n            first\
    \ + direction * ((left + right) / 2.0L);\n        if (norm(middle) <= radius +\
    \ eps) {\n            result += cross(a, b) / 2.0L;\n        } else {\n      \
    \      result +=\n                radius * radius * std::atan2(cross(a, b), dot(a,\
    \ b)) /\n                2.0L;\n        }\n    }\n    return result;\n}\n\n} \
    \ // namespace circle_detail\n\ntemplate <Coordinate T>\nconstexpr Point<long\
    \ double> centroid(const Circle<T>& circle) {\n    assert(circle.radius >= 0);\n\
    \    return Point<long double>(circle.center);\n}\n\ntemplate <Coordinate T>\n\
    constexpr long double circle_circumference(const Circle<T>& circle) {\n    assert(circle.radius\
    \ >= 0);\n    return\n        2.0L * std::numbers::pi_v<long double> *\n     \
    \   static_cast<long double>(circle.radius);\n}\n\ntemplate <Coordinate T>\nconstexpr\
    \ long double circle_area(const Circle<T>& circle) {\n    assert(circle.radius\
    \ >= 0);\n    const long double radius = static_cast<long double>(circle.radius);\n\
    \    return std::numbers::pi_v<long double> * radius * radius;\n}\n\ninline long\
    \ double normalize_circle_argument(long double argument) {\n    const long double\
    \ full = 2.0L * std::numbers::pi_v<long double>;\n    argument = std::fmod(argument,\
    \ full);\n    if (argument < 0.0L) argument += full;\n    if (argument == full)\
    \ argument = 0.0L;\n    return argument;\n}\n\ntemplate <Coordinate T>\nPoint<long\
    \ double> circle_point_at(\n    const Circle<T>& circle,\n    long double argument\n\
    ) {\n    assert(circle.radius >= 0);\n    const long double radius = static_cast<long\
    \ double>(circle.radius);\n    return Point<long double>(circle.center) + Point<long\
    \ double>(\n        radius * std::cos(argument),\n        radius * std::sin(argument)\n\
    \    );\n}\n\ninline long double angular_measure(const AngularCoverage& coverage)\
    \ {\n    if (\n        coverage.kind == AngularCoverageKind::Empty ||\n      \
    \  coverage.kind == AngularCoverageKind::Point\n    ) {\n        return 0.0L;\n\
    \    }\n    if (coverage.kind == AngularCoverageKind::Full) {\n        return\
    \ 2.0L * std::numbers::pi_v<long double>;\n    }\n    assert(coverage.kind ==\
    \ AngularCoverageKind::Arc);\n    assert(coverage.begin <= coverage.end);\n  \
    \  return coverage.end - coverage.begin;\n}\n\ntemplate <Coordinate T>\nlong double\
    \ circle_arc_length(\n    const Circle<T>& circle,\n    const AngularCoverage&\
    \ coverage\n) {\n    assert(circle.radius >= 0);\n    return static_cast<long\
    \ double>(circle.radius) * angular_measure(coverage);\n}\n\ntemplate <Coordinate\
    \ C, Coordinate P>\nPointInCircle point_in_circle(\n    const Circle<C>& circle,\n\
    \    const Point<P>& point,\n    long double eps = 1e-12L\n) {\n    assert(circle.radius\
    \ >= 0);\n    assert(eps >= 0.0L);\n    if constexpr (std::integral<C> && std::integral<P>)\
    \ {\n        using W = __int128_t;\n        const W dx = W(point.x) - W(circle.center.x);\n\
    \        const W dy = W(point.y) - W(circle.center.y);\n        const W radius\
    \ = W(circle.radius);\n        const W squared_distance = dx * dx + dy * dy;\n\
    \        const W squared_radius = radius * radius;\n        if (squared_distance\
    \ < squared_radius) return PointInCircle::Inside;\n        if (squared_distance\
    \ > squared_radius) return PointInCircle::Outside;\n        return PointInCircle::Boundary;\n\
    \    } else {\n        const int relation = circle_detail::compare(\n        \
    \    geometry::distance(\n                Point<long double>(circle.center),\n\
    \                Point<long double>(point)\n            ),\n            static_cast<long\
    \ double>(circle.radius),\n            eps\n        );\n        if (relation <\
    \ 0) return PointInCircle::Inside;\n        if (relation > 0) return PointInCircle::Outside;\n\
    \        return PointInCircle::Boundary;\n    }\n}\n\ntemplate <Coordinate C,\
    \ Coordinate P>\nbool contains(\n    const Circle<C>& circle,\n    const Point<P>&\
    \ point,\n    long double eps = 1e-12L\n) {\n    const PointInCircle relation\
    \ = point_in_circle(circle, point, eps);\n    return circle.filled\n        ?\
    \ relation != PointInCircle::Outside\n        : relation == PointInCircle::Boundary;\n\
    }\n\ntemplate <Coordinate C, Coordinate P>\nbool on_circle(\n    const Circle<C>&\
    \ circle,\n    const Point<P>& point,\n    long double eps = 1e-12L\n) {\n   \
    \ assert(circle.radius >= 0);\n    assert(eps >= 0.0L);\n    if constexpr (std::integral<C>\
    \ && std::integral<P>) {\n        using W = __int128_t;\n        const W dx =\
    \ W(point.x) - W(circle.center.x);\n        const W dy = W(point.y) - W(circle.center.y);\n\
    \        const W radius = W(circle.radius);\n        return dx * dx + dy * dy\
    \ == radius * radius;\n    } else {\n        return circle_detail::compare(\n\
    \            geometry::distance(\n                Point<long double>(circle.center),\n\
    \                Point<long double>(point)\n            ),\n            static_cast<long\
    \ double>(circle.radius),\n            eps\n        ) == 0;\n    }\n}\n\ntemplate\
    \ <Coordinate C, Coordinate P>\nlong double circle_argument(\n    const Circle<C>&\
    \ circle,\n    const Point<P>& point\n) {\n    assert(circle.radius >= 0);\n \
    \   return normalize_circle_argument(std::atan2(\n        static_cast<long double>(point.y)\
    \ -\n            static_cast<long double>(circle.center.y),\n        static_cast<long\
    \ double>(point.x) -\n            static_cast<long double>(circle.center.x)\n\
    \    ));\n}\n\ntemplate <Coordinate C, Coordinate P>\nbool intersects(\n    const\
    \ Circle<C>& circle,\n    const Point<P>& point,\n    long double eps = 1e-12L\n\
    ) {\n    return contains(circle, point, eps);\n}\n\ntemplate <Coordinate P, Coordinate\
    \ C>\nbool intersects(\n    const Point<P>& point,\n    const Circle<C>& circle,\n\
    \    long double eps = 1e-12L\n) {\n    return intersects(circle, point, eps);\n\
    }\n\ntemplate <Coordinate A, Coordinate B>\nCircle<long double> circle_from_diameter(\n\
    \    const Point<A>& first,\n    const Point<B>& second\n) {\n    Point<long double>\
    \ a(first);\n    Point<long double> b(second);\n    Point<long double> center\
    \ = (a + b) / 2.0L;\n    return Circle<long double>{center, geometry::distance(a,\
    \ b) / 2.0L};\n}\n\ntemplate <Coordinate T>\nstd::optional<Circle<long double>>\
    \ incircle(\n    const Point<T>& first,\n    const Point<T>& second,\n    const\
    \ Point<T>& third,\n    long double eps = 1e-12L\n) {\n    assert(eps >= 0.0L);\n\
    \    if (orientation(first, second, third, eps) == 0) return std::nullopt;\n\n\
    \    long double opposite_first = geometry::distance(second, third);\n    long\
    \ double opposite_second = geometry::distance(third, first);\n    long double\
    \ opposite_third = geometry::distance(first, second);\n    long double perimeter\
    \ =\n        opposite_first + opposite_second + opposite_third;\n    Point<long\
    \ double> center =\n        (Point<long double>(first) * opposite_first +\n  \
    \       Point<long double>(second) * opposite_second +\n         Point<long double>(third)\
    \ * opposite_third) /\n        perimeter;\n    long double doubled_area = std::fabs(\n\
    \        static_cast<long double>(cross(first, second, third))\n    );\n    return\
    \ Circle<long double>{center, doubled_area / perimeter};\n}\n\ntemplate <Coordinate\
    \ T>\nstd::optional<Circle<long double>> circumcircle(\n    const Point<T>& first,\n\
    \    const Point<T>& second,\n    const Point<T>& third,\n    long double eps\
    \ = 1e-12L\n) {\n    assert(eps >= 0.0L);\n    if (orientation(first, second,\
    \ third, eps) == 0) return std::nullopt;\n\n    Point<long double> origin(first);\n\
    \    Point<long double> u = Point<long double>(second) - origin;\n    Point<long\
    \ double> v = Point<long double>(third) - origin;\n    long double denominator\
    \ = 2.0L * cross(u, v);\n    long double u_norm = norm2(u);\n    long double v_norm\
    \ = norm2(v);\n    Point<long double> offset(\n        (u_norm * v.y - v_norm\
    \ * u.y) / denominator,\n        (u.x * v_norm - v.x * u_norm) / denominator\n\
    \    );\n    Point<long double> center = origin + offset;\n    return Circle<long\
    \ double>{center, norm(offset)};\n}\n\ntemplate <Coordinate A, Coordinate B>\n\
    CircleRelation circle_relation(\n    const Circle<A>& first,\n    const Circle<B>&\
    \ second,\n    long double eps = 1e-12L\n) {\n    assert(first.radius >= 0);\n\
    \    assert(second.radius >= 0);\n    assert(eps >= 0.0L);\n    if constexpr (std::integral<A>\
    \ && std::integral<B>) {\n        using W = __int128_t;\n        W dx = W(second.center.x)\
    \ - W(first.center.x);\n        W dy = W(second.center.y) - W(first.center.y);\n\
    \        W squared_distance = dx * dx + dy * dy;\n        W first_radius = W(first.radius);\n\
    \        W second_radius = W(second.radius);\n        W sum = first_radius + second_radius;\n\
    \        W difference = first_radius - second_radius;\n        if (difference\
    \ < 0) difference = -difference;\n        if (squared_distance == 0 && difference\
    \ == 0) {\n            return CircleRelation::Coincident;\n        }\n       \
    \ if (squared_distance > sum * sum) return CircleRelation::Separate;\n       \
    \ if (squared_distance == sum * sum) {\n            return CircleRelation::ExternallyTangent;\n\
    \        }\n        if (squared_distance < difference * difference) {\n      \
    \      return CircleRelation::Contained;\n        }\n        if (squared_distance\
    \ == difference * difference) {\n            return CircleRelation::InternallyTangent;\n\
    \        }\n        return CircleRelation::Intersecting;\n    } else {\n     \
    \   long double center_distance = geometry::distance(\n            Point<long\
    \ double>(first.center),\n            Point<long double>(second.center)\n    \
    \    );\n        long double first_radius = static_cast<long double>(first.radius);\n\
    \        long double second_radius = static_cast<long double>(second.radius);\n\
    \        long double sum = first_radius + second_radius;\n        long double\
    \ difference = std::fabs(first_radius - second_radius);\n        if (\n      \
    \      center_distance <= eps &&\n            difference <= eps\n        ) {\n\
    \            return CircleRelation::Coincident;\n        }\n        int outer\
    \ = circle_detail::compare(center_distance, sum, eps);\n        if (outer > 0)\
    \ return CircleRelation::Separate;\n        if (outer == 0) return CircleRelation::ExternallyTangent;\n\
    \        int inner = circle_detail::compare(center_distance, difference, eps);\n\
    \        if (inner < 0) return CircleRelation::Contained;\n        if (inner ==\
    \ 0) return CircleRelation::InternallyTangent;\n        return CircleRelation::Intersecting;\n\
    \    }\n}\n\ntemplate <Coordinate C, Coordinate L>\nCircleLinearIntersection circle_boundary_intersection(\n\
    \    const Circle<C>& circle,\n    const Line<L>& line,\n    long double eps =\
    \ 1e-12L\n) {\n    assert(circle.radius >= 0);\n    assert(line.a != line.b);\n\
    \    assert(eps >= 0.0L);\n\n    const Point<long double> center(circle.center);\n\
    \    const Point<long double> origin(line.a);\n    const Point<long double> direction\
    \ =\n        Point<long double>(line.b) - origin;\n    const long double squared_length\
    \ = dot(direction, direction);\n    const long double length = std::sqrt(squared_length);\n\
    \    const long double foot_parameter =\n        dot(center - origin, direction)\
    \ / squared_length;\n    const Point<long double> foot =\n        origin + direction\
    \ * foot_parameter;\n    const long double distance_to_line = geometry::distance(center,\
    \ foot);\n    const long double radius = static_cast<long double>(circle.radius);\n\
    \    const int relation =\n        circle_detail::compare(distance_to_line, radius,\
    \ eps);\n\n    CircleLinearIntersection result;\n    if (relation > 0) return\
    \ result;\n    if (relation == 0) {\n        result.contact_count = 1;\n     \
    \   result.contacts[0] = CircleLinearContact{\n            foot,\n           \
    \ circle_argument(circle, foot),\n            foot_parameter\n        };\n   \
    \     return result;\n    }\n\n    const long double offset = std::sqrt(std::max(\n\
    \        0.0L,\n        radius * radius - distance_to_line * distance_to_line\n\
    \    ));\n    const long double parameter_offset = offset / length;\n    result.contact_count\
    \ = 2;\n    for (int index = 0; index < 2; ++index) {\n        const long double\
    \ parameter = foot_parameter +\n            (index == 0 ? -parameter_offset :\
    \ parameter_offset);\n        const Point<long double> point = origin + direction\
    \ * parameter;\n        result.contacts[index] = CircleLinearContact{\n      \
    \      point,\n            circle_argument(circle, point),\n            parameter\n\
    \        };\n    }\n    return result;\n}\n\ntemplate <Coordinate L, Coordinate\
    \ C>\nCircleLinearIntersection circle_boundary_intersection(\n    const Line<L>&\
    \ line,\n    const Circle<C>& circle,\n    long double eps = 1e-12L\n) {\n   \
    \ return circle_boundary_intersection(circle, line, eps);\n}\n\ntemplate <Coordinate\
    \ C, Coordinate R>\nCircleLinearIntersection circle_boundary_intersection(\n \
    \   const Circle<C>& circle,\n    const Ray<R>& ray,\n    long double eps = 1e-12L\n\
    ) {\n    assert(ray.origin != ray.through);\n    const Line<R> line{ray.origin,\
    \ ray.through};\n    const CircleLinearIntersection line_result =\n        circle_boundary_intersection(circle,\
    \ line, eps);\n    CircleLinearIntersection result;\n    for (int index = 0; index\
    \ < line_result.contact_count; ++index) {\n        CircleLinearContact contact\
    \ = line_result.contacts[index];\n        if (contact.linear_parameter < -eps)\
    \ continue;\n        if (std::fabs(contact.linear_parameter) <= eps) {\n     \
    \       contact.linear_parameter = 0.0L;\n            contact.point = Point<long\
    \ double>(ray.origin);\n            contact.circle_argument = circle_argument(circle,\
    \ contact.point);\n        }\n        result.contacts[result.contact_count++]\
    \ = contact;\n    }\n    return result;\n}\n\ntemplate <Coordinate R, Coordinate\
    \ C>\nCircleLinearIntersection circle_boundary_intersection(\n    const Ray<R>&\
    \ ray,\n    const Circle<C>& circle,\n    long double eps = 1e-12L\n) {\n    return\
    \ circle_boundary_intersection(circle, ray, eps);\n}\n\ntemplate <Coordinate C,\
    \ Coordinate S>\nCircleLinearIntersection circle_boundary_intersection(\n    const\
    \ Circle<C>& circle,\n    const Segment<S>& segment,\n    long double eps = 1e-12L\n\
    ) {\n    assert(circle.radius >= 0);\n    assert(eps >= 0.0L);\n    CircleLinearIntersection\
    \ result;\n    if (segment.a == segment.b) {\n        if (on_circle(circle, segment.a,\
    \ eps)) {\n            const Point<long double> point(segment.a);\n          \
    \  result.contact_count = 1;\n            result.contacts[0] = CircleLinearContact{\n\
    \                point,\n                circle_argument(circle, point),\n   \
    \             0.0L\n            };\n        }\n        return result;\n    }\n\
    \n    const Line<S> line{segment.a, segment.b};\n    const CircleLinearIntersection\
    \ line_result =\n        circle_boundary_intersection(circle, line, eps);\n  \
    \  for (int index = 0; index < line_result.contact_count; ++index) {\n       \
    \ CircleLinearContact contact = line_result.contacts[index];\n        if (\n \
    \           contact.linear_parameter < -eps ||\n            contact.linear_parameter\
    \ > 1.0L + eps\n        ) {\n            continue;\n        }\n        if (std::fabs(contact.linear_parameter)\
    \ <= eps) {\n            contact.linear_parameter = 0.0L;\n            contact.point\
    \ = Point<long double>(segment.a);\n        } else if (std::fabs(contact.linear_parameter\
    \ - 1.0L) <= eps) {\n            contact.linear_parameter = 1.0L;\n          \
    \  contact.point = Point<long double>(segment.b);\n        }\n        contact.circle_argument\
    \ = circle_argument(circle, contact.point);\n        result.contacts[result.contact_count++]\
    \ = contact;\n    }\n    return result;\n}\n\ntemplate <Coordinate S, Coordinate\
    \ C>\nCircleLinearIntersection circle_boundary_intersection(\n    const Segment<S>&\
    \ segment,\n    const Circle<C>& circle,\n    long double eps = 1e-12L\n) {\n\
    \    return circle_boundary_intersection(circle, segment, eps);\n}\n\ntemplate\
    \ <Coordinate A, Coordinate B>\nCircleCircleIntersection circle_boundary_intersection(\n\
    \    const Circle<A>& first,\n    const Circle<B>& second,\n    long double eps\
    \ = 1e-12L\n) {\n    assert(first.radius >= 0);\n    assert(second.radius >= 0);\n\
    \    assert(eps >= 0.0L);\n    const long double full = 2.0L * std::numbers::pi_v<long\
    \ double>;\n    const long double first_radius = static_cast<long double>(first.radius);\n\
    \    const long double second_radius = static_cast<long double>(second.radius);\n\
    \    CircleCircleIntersection result;\n    result.relation = circle_relation(first,\
    \ second, eps);\n\n    auto point_coverage = [](long double argument) {\n    \
    \    return AngularCoverage{\n            AngularCoverageKind::Point,\n      \
    \      argument,\n            argument\n        };\n    };\n    auto full_coverage\
    \ = [full]() {\n        return AngularCoverage{AngularCoverageKind::Full, 0.0L,\
    \ full};\n    };\n\n    if (result.relation == CircleRelation::Coincident) {\n\
    \        if (first_radius == 0.0L) {\n            const Point<long double> point(first.center);\n\
    \            result.contact_kind = CircleContactKind::Point;\n            result.contacts[0]\
    \ = CircleContact{point, 0.0L, 0.0L};\n            result.first_inside_second\
    \ = point_coverage(0.0L);\n            result.second_inside_first = point_coverage(0.0L);\n\
    \        } else {\n            result.contact_kind = CircleContactKind::Coincident;\n\
    \            result.first_inside_second = full_coverage();\n            result.second_inside_first\
    \ = full_coverage();\n        }\n        return result;\n    }\n\n    if (result.relation\
    \ == CircleRelation::Separate) return result;\n    if (result.relation == CircleRelation::Contained)\
    \ {\n        if (first_radius < second_radius) {\n            result.first_inside_second\
    \ = first_radius == 0.0L\n                ? point_coverage(0.0L)\n           \
    \     : full_coverage();\n        } else {\n            result.second_inside_first\
    \ = second_radius == 0.0L\n                ? point_coverage(0.0L)\n          \
    \      : full_coverage();\n        }\n        return result;\n    }\n\n    const\
    \ Point<long double> first_center(first.center);\n    const Point<long double>\
    \ second_center(second.center);\n    const Point<long double> center_direction\
    \ = second_center - first_center;\n    const long double center_distance = norm(center_direction);\n\
    \    const Point<long double> unit = center_direction / center_distance;\n   \
    \ const long double along =\n        (first_radius * first_radius - second_radius\
    \ * second_radius +\n         center_distance * center_distance) /\n        (2.0L\
    \ * center_distance);\n    const Point<long double> base = first_center + unit\
    \ * along;\n\n    if (\n        result.relation == CircleRelation::ExternallyTangent\
    \ ||\n        result.relation == CircleRelation::InternallyTangent\n    ) {\n\
    \        const long double first_argument =\n            circle_argument(first,\
    \ base);\n        const long double second_argument =\n            circle_argument(second,\
    \ base);\n        result.contact_kind = CircleContactKind::Point;\n        result.contacts[0]\
    \ = CircleContact{\n            base,\n            first_argument,\n         \
    \   second_argument\n        };\n        result.first_inside_second = point_coverage(first_argument);\n\
    \        result.second_inside_first = point_coverage(second_argument);\n     \
    \   if (result.relation == CircleRelation::InternallyTangent) {\n            if\
    \ (first_radius < second_radius && first_radius > 0.0L) {\n                result.first_inside_second\
    \ = full_coverage();\n            } else if (\n                second_radius <\
    \ first_radius && second_radius > 0.0L\n            ) {\n                result.second_inside_first\
    \ = full_coverage();\n            }\n        }\n        return result;\n    }\n\
    \n    assert(result.relation == CircleRelation::Intersecting);\n    const long\
    \ double height = std::sqrt(std::max(\n        0.0L,\n        first_radius * first_radius\
    \ - along * along\n    ));\n    const Point<long double> perpendicular(-unit.y,\
    \ unit.x);\n    const Point<long double> first_point = base - perpendicular *\
    \ height;\n    const Point<long double> second_point = base + perpendicular *\
    \ height;\n    result.contact_kind = CircleContactKind::TwoPoints;\n    result.contacts[0]\
    \ = CircleContact{\n        first_point,\n        circle_argument(first, first_point),\n\
    \        circle_argument(second, first_point)\n    };\n    result.contacts[1]\
    \ = CircleContact{\n        second_point,\n        circle_argument(first, second_point),\n\
    \        circle_argument(second, second_point)\n    };\n\n    const long double\
    \ first_begin = result.contacts[0].first_argument;\n    long double first_end\
    \ = result.contacts[1].first_argument;\n    if (first_end <= first_begin) first_end\
    \ += full;\n    result.first_inside_second = AngularCoverage{\n        AngularCoverageKind::Arc,\n\
    \        first_begin,\n        first_end\n    };\n\n    const long double second_begin\
    \ = result.contacts[1].second_argument;\n    long double second_end = result.contacts[0].second_argument;\n\
    \    if (second_end <= second_begin) second_end += full;\n    result.second_inside_first\
    \ = AngularCoverage{\n        AngularCoverageKind::Arc,\n        second_begin,\n\
    \        second_end\n    };\n    return result;\n}\n\ntemplate <Coordinate C,\
    \ Coordinate L>\nbool intersects(\n    const Circle<C>& circle,\n    const Line<L>&\
    \ line,\n    long double eps = 1e-12L\n) {\n    if (circle.filled) {\n       \
    \ const Line<long double> converted{\n            Point<long double>(line.a),\n\
    \            Point<long double>(line.b)\n        };\n        return contains(\n\
    \            circle,\n            projection(converted, Point<long double>(circle.center)),\n\
    \            eps\n        );\n    }\n    return circle_boundary_intersection(circle,\
    \ line, eps).contact_count > 0;\n}\n\ntemplate <Coordinate C, Coordinate L>\n\
    bool intersects(\n    const Line<L>& line,\n    const Circle<C>& circle,\n   \
    \ long double eps = 1e-12L\n) {\n    return intersects(circle, line, eps);\n}\n\
    \ntemplate <Coordinate C, Coordinate R>\nbool intersects(\n    const Circle<C>&\
    \ circle,\n    const Ray<R>& ray,\n    long double eps = 1e-12L\n) {\n    if (circle.filled)\
    \ {\n        const Ray<long double> converted{\n            Point<long double>(ray.origin),\n\
    \            Point<long double>(ray.through)\n        };\n        return contains(\n\
    \            circle,\n            projection(converted, Point<long double>(circle.center)),\n\
    \            eps\n        );\n    }\n    return circle_boundary_intersection(circle,\
    \ ray, eps).contact_count > 0;\n}\n\ntemplate <Coordinate C, Coordinate R>\nbool\
    \ intersects(\n    const Ray<R>& ray,\n    const Circle<C>& circle,\n    long\
    \ double eps = 1e-12L\n) {\n    return intersects(circle, ray, eps);\n}\n\ntemplate\
    \ <Coordinate C, Coordinate S>\nbool intersects(\n    const Circle<C>& circle,\n\
    \    const Segment<S>& segment,\n    long double eps = 1e-12L\n) {\n    if (circle.filled)\
    \ {\n        const Segment<long double> converted{\n            Point<long double>(segment.a),\n\
    \            Point<long double>(segment.b)\n        };\n        return contains(\n\
    \            circle,\n            projection(converted, Point<long double>(circle.center)),\n\
    \            eps\n        );\n    }\n    return\n        circle_boundary_intersection(circle,\
    \ segment, eps).contact_count > 0;\n}\n\ntemplate <Coordinate C, Coordinate S>\n\
    bool intersects(\n    const Segment<S>& segment,\n    const Circle<C>& circle,\n\
    \    long double eps = 1e-12L\n) {\n    return intersects(circle, segment, eps);\n\
    }\n\ntemplate <Coordinate A, Coordinate B>\nbool intersects(\n    const Circle<A>&\
    \ first,\n    const Circle<B>& second,\n    long double eps = 1e-12L\n) {\n  \
    \  assert(first.radius >= 0);\n    assert(second.radius >= 0);\n    assert(eps\
    \ >= 0.0L);\n    if (first.filled && second.filled) {\n        if constexpr (std::integral<A>\
    \ && std::integral<B>) {\n            using W = __int128_t;\n            const\
    \ W dx = W(second.center.x) - W(first.center.x);\n            const W dy = W(second.center.y)\
    \ - W(first.center.y);\n            const W radius = W(first.radius) + W(second.radius);\n\
    \            return dx * dx + dy * dy <= radius * radius;\n        } else {\n\
    \            const long double center_distance = geometry::distance(\n       \
    \         Point<long double>(first.center),\n                Point<long double>(second.center)\n\
    \            );\n            const long double radius_sum =\n                static_cast<long\
    \ double>(first.radius) +\n                static_cast<long double>(second.radius);\n\
    \            return circle_detail::compare(\n                center_distance,\n\
    \                radius_sum,\n                eps\n            ) <= 0;\n     \
    \   }\n    }\n    if (first.filled != second.filled) {\n        const long double\
    \ center_distance = geometry::distance(\n            Point<long double>(first.center),\n\
    \            Point<long double>(second.center)\n        );\n        const long\
    \ double boundary_radius = first.filled\n            ? static_cast<long double>(second.radius)\n\
    \            : static_cast<long double>(first.radius);\n        const long double\
    \ filled_radius = first.filled\n            ? static_cast<long double>(first.radius)\n\
    \            : static_cast<long double>(second.radius);\n        return circle_detail::compare(\n\
    \            std::fabs(center_distance - boundary_radius),\n            filled_radius,\n\
    \            eps\n        ) <= 0;\n    }\n    CircleRelation relation = circle_relation(first,\
    \ second, eps);\n    return\n        relation == CircleRelation::ExternallyTangent\
    \ ||\n        relation == CircleRelation::Intersecting ||\n        relation ==\
    \ CircleRelation::InternallyTangent ||\n        relation == CircleRelation::Coincident;\n\
    }\n\ntemplate <Coordinate R, Coordinate H, Coordinate C>\nRay<long double> reflected_ray(\n\
    \    const Ray<R>& incoming,\n    const Point<H>& hit,\n    const Circle<C>& circle,\n\
    \    long double eps = 1e-12L\n) {\n    assert(incoming.origin != incoming.through);\n\
    \    assert(eps >= 0.0L);\n    assert(static_cast<long double>(circle.radius)\
    \ > eps);\n    assert(\n        std::fabs(\n            geometry::distance(\n\
    \                Point<long double>(hit),\n                Point<long double>(circle.center)\n\
    \            ) -\n            static_cast<long double>(circle.radius)\n      \
    \  ) <= eps\n    );\n\n    Point<long double> hit_point(hit);\n    Point<long\
    \ double> normal = normalized(\n        hit_point - Point<long double>(circle.center)\n\
    \    );\n    Point<long double> incoming_direction =\n        Point<long double>(incoming.through)\
    \ -\n        Point<long double>(incoming.origin);\n    Point<long double> outgoing_direction\
    \ =\n        incoming_direction - normal * (2.0L * dot(incoming_direction, normal));\n\
    \    return Ray<long double>{hit_point, hit_point + outgoing_direction};\n}\n\n\
    template <Coordinate C, Coordinate P>\nstd::vector<Point<long double>> tangent_points(\n\
    \    const Circle<C>& circle,\n    const Point<P>& point,\n    long double eps\
    \ = 1e-12L\n) {\n    assert(circle.radius >= 0);\n    assert(eps >= 0.0L);\n \
    \   Point<long double> center(circle.center);\n    Point<long double> external(point);\n\
    \    Point<long double> direction = external - center;\n    long double squared_distance\
    \ = dot(direction, direction);\n    long double radius = static_cast<long double>(circle.radius);\n\
    \    if (radius == 0.0L) return {center};\n\n    long double center_distance =\
    \ std::sqrt(squared_distance);\n    int relation = circle_detail::compare(center_distance,\
    \ radius, eps);\n    if (relation < 0) return {};\n    if (relation == 0) {\n\
    \        return {center + direction * (radius / center_distance)};\n    }\n\n\
    \    Point<long double> base =\n        center + direction * (radius * radius\
    \ / squared_distance);\n    long double scale =\n        radius * std::sqrt(std::max(\n\
    \            0.0L,\n            squared_distance - radius * radius\n        ))\
    \ /\n        squared_distance;\n    Point<long double> perpendicular(-direction.y,\
    \ direction.x);\n    Point<long double> first = base - perpendicular * scale;\n\
    \    Point<long double> second = base + perpendicular * scale;\n    if (second\
    \ < first) std::swap(first, second);\n    return {first, second};\n}\n\ntemplate\
    \ <Coordinate A, Coordinate B>\nstd::vector<Line<long double>> common_tangents(\n\
    \    const Circle<A>& first,\n    const Circle<B>& second,\n    long double eps\
    \ = 1e-12L\n) {\n    assert(first.radius >= 0);\n    assert(second.radius >= 0);\n\
    \    assert(eps >= 0.0L);\n    Point<long double> first_center(first.center);\n\
    \    Point<long double> second_center(second.center);\n    Point<long double>\
    \ direction = second_center - first_center;\n    long double squared_distance\
    \ = dot(direction, direction);\n    long double center_distance = std::sqrt(squared_distance);\n\
    \    if (center_distance <= eps) return {};\n\n    long double first_radius =\
    \ static_cast<long double>(first.radius);\n    long double second_radius = static_cast<long\
    \ double>(second.radius);\n    std::vector<Line<long double>> result;\n    for\
    \ (int second_side : {1, -1}) {\n        long double difference =\n          \
    \  first_radius - second_side * second_radius;\n        int relation = circle_detail::compare(\n\
    \            std::fabs(difference),\n            center_distance,\n          \
    \  eps\n        );\n        if (relation > 0) continue;\n        long double perpendicular_length\
    \ = relation == 0 ? 0.0L : std::sqrt(\n            std::max(0.0L, squared_distance\
    \ - difference * difference)\n        );\n        int choices = perpendicular_length\
    \ <= eps ? 1 : 2;\n        for (int choice = 0; choice < choices; ++choice) {\n\
    \            long double side = choice == 0 ? -1.0L : 1.0L;\n            Point<long\
    \ double> normal =\n                direction * (difference / squared_distance)\
    \ +\n                Point<long double>(-direction.y, direction.x) *\n       \
    \             (side * perpendicular_length / squared_distance);\n            normal\
    \ = normalized(normal);\n            Point<long double> contact =\n          \
    \      first_center + normal * first_radius;\n            Line<long double> tangent\
    \ =\n                circle_detail::tangent_line(contact, normal, eps);\n    \
    \        bool duplicate = false;\n            for (const Line<long double>& existing\
    \ : result) {\n                if (circle_detail::same_line(existing, tangent,\
    \ eps)) {\n                    duplicate = true;\n                    break;\n\
    \                }\n            }\n            if (!duplicate) result.push_back(tangent);\n\
    \        }\n    }\n    std::sort(\n        result.begin(),\n        result.end(),\n\
    \        [](const Line<long double>& left, const Line<long double>& right) {\n\
    \            if (left.a != right.a) return left.a < right.a;\n            return\
    \ left.b < right.b;\n        }\n    );\n    return result;\n}\n\ntemplate <Coordinate\
    \ A, Coordinate B>\nstd::vector<Point<long double>> common_tangent_points(\n \
    \   const Circle<A>& first,\n    const Circle<B>& second,\n    long double eps\
    \ = 1e-12L\n) {\n    std::vector<Point<long double>> result;\n    for (const Line<long\
    \ double>& line : common_tangents(first, second, eps)) {\n        circle_detail::push_unique(result,\
    \ line.a, eps);\n    }\n    std::sort(result.begin(), result.end());\n    return\
    \ result;\n}\n\n// These area functions use the enclosed disks, independent of\
    \ `filled`.\ntemplate <Coordinate A, Coordinate B>\nlong double circle_circle_intersection_area(\n\
    \    const Circle<A>& first,\n    const Circle<B>& second,\n    long double eps\
    \ = 1e-12L\n) {\n    assert(first.radius >= 0);\n    assert(second.radius >= 0);\n\
    \    assert(eps >= 0.0L);\n    const long double first_radius = static_cast<long\
    \ double>(first.radius);\n    const long double second_radius = static_cast<long\
    \ double>(second.radius);\n    const CircleRelation relation = circle_relation(first,\
    \ second, eps);\n    if (\n        relation == CircleRelation::Separate ||\n \
    \       relation == CircleRelation::ExternallyTangent\n    ) {\n        return\
    \ 0.0L;\n    }\n    if (\n        relation == CircleRelation::Contained ||\n \
    \       relation == CircleRelation::InternallyTangent ||\n        relation ==\
    \ CircleRelation::Coincident\n    ) {\n        const long double radius = std::min(first_radius,\
    \ second_radius);\n        return std::numbers::pi_v<long double> * radius * radius;\n\
    \    }\n\n    const long double center_distance = geometry::distance(\n      \
    \  Point<long double>(first.center),\n        Point<long double>(second.center)\n\
    \    );\n    const long double first_cosine = std::clamp(\n        (\n       \
    \     (center_distance - second_radius) *\n                (center_distance +\
    \ second_radius) +\n            first_radius * first_radius\n        ) / (2.0L\
    \ * center_distance * first_radius),\n        -1.0L,\n        1.0L\n    );\n \
    \   const long double second_cosine = std::clamp(\n        (\n            (center_distance\
    \ - first_radius) *\n                (center_distance + first_radius) +\n    \
    \        second_radius * second_radius\n        ) / (2.0L * center_distance *\
    \ second_radius),\n        -1.0L,\n        1.0L\n    );\n    const long double\
    \ radicand =\n        (-center_distance + first_radius + second_radius) *\n  \
    \      (center_distance + first_radius - second_radius) *\n        (center_distance\
    \ - first_radius + second_radius) *\n        (center_distance + first_radius +\
    \ second_radius);\n    const long double height =\n        std::sqrt(std::max(0.0L,\
    \ radicand)) / (2.0L * center_distance);\n    const long double first_sine =\n\
    \        std::clamp(height / first_radius, 0.0L, 1.0L);\n    const long double\
    \ second_sine =\n        std::clamp(height / second_radius, 0.0L, 1.0L);\n   \
    \ const long double first_angle = std::atan2(first_sine, first_cosine);\n    const\
    \ long double second_angle = std::atan2(second_sine, second_cosine);\n    return\n\
    \        first_radius * first_radius *\n            circle_detail::circular_segment_angle_term(\n\
    \                first_angle,\n                first_sine,\n                first_cosine\n\
    \            ) +\n        second_radius * second_radius *\n            circle_detail::circular_segment_angle_term(\n\
    \                second_angle,\n                second_sine,\n               \
    \ second_cosine\n            );\n}\n\ntemplate <Coordinate C, Coordinate P>\n\
    long double circle_polygon_intersection_area(\n    const Circle<C>& circle,\n\
    \    const std::vector<Point<P>>& polygon,\n    long double eps = 1e-12L\n) {\n\
    \    assert(circle.radius >= 0);\n    assert(eps >= 0.0L);\n    if (polygon.empty()\
    \ || circle.radius == 0) return 0.0L;\n\n    const Point<long double> center(circle.center);\n\
    \    const long double radius = static_cast<long double>(circle.radius);\n   \
    \ long double result = 0.0L;\n    for (std::size_t index = 0; index < polygon.size();\
    \ ++index) {\n        const Point<long double> first =\n            Point<long\
    \ double>(polygon[index]) - center;\n        const Point<long double> second =\n\
    \            Point<long double>(polygon[(index + 1) % polygon.size()]) - center;\n\
    \        result += circle_detail::segment_disk_signed_area(\n            first,\n\
    \            second,\n            radius,\n            eps\n        );\n    }\n\
    \    return std::fabs(result);\n}\n\nnamespace circle_detail {\n\ntemplate <Coordinate\
    \ T>\nPoint<long double> point_toward(\n    const Circle<T>& circle,\n    const\
    \ Point<long double>& target\n) {\n    assert(circle.radius >= 0);\n    const\
    \ Point<long double> center(circle.center);\n    const long double radius = static_cast<long\
    \ double>(circle.radius);\n    const Point<long double> direction = target - center;\n\
    \    const long double length = norm(direction);\n    if (length == 0.0L) {\n\
    \        return center + Point<long double>(-radius, 0.0L);\n    }\n    return\
    \ center + direction * (radius / length);\n}\n\ninline void consider(\n    ClosestPoints&\
    \ best,\n    const ClosestPoints& candidate\n) {\n    closest_points_detail::consider(best,\
    \ candidate);\n}\n\n}  // namespace circle_detail\n\ntemplate <Coordinate C, Coordinate\
    \ P>\nClosestPoints closest_points(\n    const Circle<C>& circle,\n    const Point<P>&\
    \ point,\n    long double eps = 1e-12L\n) {\n    const Point<long double> converted(point);\n\
    \    if (circle.filled && contains(circle, converted, eps)) {\n        return\
    \ ClosestPoints{converted, converted};\n    }\n    return ClosestPoints{\n   \
    \     circle_detail::point_toward(circle, converted),\n        converted\n   \
    \ };\n}\n\ntemplate <Coordinate P, Coordinate C>\nClosestPoints closest_points(\n\
    \    const Point<P>& point,\n    const Circle<C>& circle,\n    long double eps\
    \ = 1e-12L\n) {\n    return closest_points_detail::reversed(\n        closest_points(circle,\
    \ point, eps)\n    );\n}\n\ntemplate <Coordinate C, Coordinate L>\nClosestPoints\
    \ closest_points(\n    const Circle<C>& circle,\n    const Line<L>& line,\n  \
    \  long double eps = 1e-12L\n) {\n    const Line<long double> converted{\n   \
    \     Point<long double>(line.a),\n        Point<long double>(line.b)\n    };\n\
    \    const Point<long double> point = projection(\n        converted,\n      \
    \  Point<long double>(circle.center)\n    );\n    if (circle.filled) return closest_points(circle,\
    \ point, eps);\n\n    const CircleLinearIntersection common =\n        circle_boundary_intersection(circle,\
    \ line, eps);\n    if (common.contact_count > 0) {\n        return ClosestPoints{\n\
    \            common.contacts[0].point,\n            common.contacts[0].point\n\
    \        };\n    }\n    return ClosestPoints{\n        circle_detail::point_toward(circle,\
    \ point),\n        point\n    };\n}\n\ntemplate <Coordinate L, Coordinate C>\n\
    ClosestPoints closest_points(\n    const Line<L>& line,\n    const Circle<C>&\
    \ circle,\n    long double eps = 1e-12L\n) {\n    return closest_points_detail::reversed(closest_points(circle,\
    \ line, eps));\n}\n\ntemplate <Coordinate C, Coordinate R>\nClosestPoints closest_points(\n\
    \    const Circle<C>& circle,\n    const Ray<R>& ray,\n    long double eps = 1e-12L\n\
    ) {\n    const Ray<long double> converted{\n        Point<long double>(ray.origin),\n\
    \        Point<long double>(ray.through)\n    };\n    const Point<long double>\
    \ point = projection(\n        converted,\n        Point<long double>(circle.center)\n\
    \    );\n    if (circle.filled) return closest_points(circle, point, eps);\n\n\
    \    const CircleLinearIntersection common =\n        circle_boundary_intersection(circle,\
    \ ray, eps);\n    if (common.contact_count > 0) {\n        return ClosestPoints{\n\
    \            common.contacts[0].point,\n            common.contacts[0].point\n\
    \        };\n    }\n    return ClosestPoints{\n        circle_detail::point_toward(circle,\
    \ point),\n        point\n    };\n}\n\ntemplate <Coordinate R, Coordinate C>\n\
    ClosestPoints closest_points(\n    const Ray<R>& ray,\n    const Circle<C>& circle,\n\
    \    long double eps = 1e-12L\n) {\n    return closest_points_detail::reversed(closest_points(circle,\
    \ ray, eps));\n}\n\ntemplate <Coordinate C, Coordinate S>\nClosestPoints closest_points(\n\
    \    const Circle<C>& circle,\n    const Segment<S>& segment,\n    long double\
    \ eps = 1e-12L\n) {\n    const Segment<long double> converted{\n        Point<long\
    \ double>(segment.a),\n        Point<long double>(segment.b)\n    };\n    const\
    \ Point<long double> center(circle.center);\n    const Point<long double> projected\
    \ = projection(converted, center);\n    if (circle.filled) return closest_points(circle,\
    \ projected, eps);\n\n    const CircleLinearIntersection common =\n        circle_boundary_intersection(circle,\
    \ segment, eps);\n    if (common.contact_count > 0) {\n        return ClosestPoints{\n\
    \            common.contacts[0].point,\n            common.contacts[0].point\n\
    \        };\n    }\n    ClosestPoints result{\n        circle_detail::point_toward(circle,\
    \ projected),\n        projected\n    };\n    for (const Point<long double>& point\
    \ : {converted.a, converted.b}) {\n        circle_detail::consider(\n        \
    \    result,\n            ClosestPoints{circle_detail::point_toward(circle, point),\
    \ point}\n        );\n    }\n    return result;\n}\n\ntemplate <Coordinate S,\
    \ Coordinate C>\nClosestPoints closest_points(\n    const Segment<S>& segment,\n\
    \    const Circle<C>& circle,\n    long double eps = 1e-12L\n) {\n    return closest_points_detail::reversed(\n\
    \        closest_points(circle, segment, eps)\n    );\n}\n\ntemplate <Coordinate\
    \ A, Coordinate B>\nClosestPoints closest_points(\n    const Circle<A>& first,\n\
    \    const Circle<B>& second,\n    long double eps = 1e-12L\n) {\n    if (first.filled\
    \ && !second.filled) {\n        return closest_points_detail::reversed(\n    \
    \        closest_points(second, first, eps)\n        );\n    }\n\n    if (!first.filled\
    \ && second.filled) {\n        const ClosestPoints center_result =\n         \
    \   closest_points(first, second.center, eps);\n        if (contains(second, center_result.first,\
    \ eps)) {\n            return ClosestPoints{center_result.first, center_result.first};\n\
    \        }\n        const ClosestPoints filled_result =\n            closest_points(second,\
    \ center_result.first, eps);\n        return ClosestPoints{center_result.first,\
    \ filled_result.first};\n    }\n\n    if (first.filled && second.filled) {\n \
    \       assert(first.radius >= 0);\n        assert(second.radius >= 0);\n    \
    \    const Point<long double> first_center(first.center);\n        const Point<long\
    \ double> second_center(second.center);\n        Point<long double> direction\
    \ = second_center - first_center;\n        const long double center_distance =\
    \ norm(direction);\n        if (center_distance == 0.0L) {\n            return\
    \ ClosestPoints{first_center, first_center};\n        }\n        direction = direction\
    \ / center_distance;\n        const long double first_radius =\n            static_cast<long\
    \ double>(first.radius);\n        const long double second_radius =\n        \
    \    static_cast<long double>(second.radius);\n        if (intersects(first, second,\
    \ eps)) {\n            const long double left = std::max(\n                -first_radius,\n\
    \                center_distance - second_radius\n            );\n           \
    \ const long double right = std::min(\n                first_radius,\n       \
    \         center_distance + second_radius\n            );\n            const Point<long\
    \ double> common =\n                first_center + direction * ((left + right)\
    \ / 2.0L);\n            return ClosestPoints{common, common};\n        }\n   \
    \     return ClosestPoints{\n            first_center + direction * first_radius,\n\
    \            second_center - direction * second_radius\n        };\n    }\n\n\
    \    const CircleCircleIntersection common =\n        circle_boundary_intersection(first,\
    \ second, eps);\n    if (common.contact_count() > 0) {\n        return ClosestPoints{\n\
    \            common.contacts[0].point,\n            common.contacts[0].point\n\
    \        };\n    }\n\n    const Point<long double> first_center(first.center);\n\
    \    const Point<long double> second_center(second.center);\n    if (circle_relation(first,\
    \ second, eps) == CircleRelation::Coincident) {\n        const Point<long double>\
    \ point =\n            circle_detail::point_toward(first, first_center);\n   \
    \     return ClosestPoints{point, point};\n    }\n    Point<long double> direction\
    \ = second_center - first_center;\n    const long double center_distance = norm(direction);\n\
    \    if (center_distance == 0.0L) {\n        const Point<long double> first_point\
    \ =\n            circle_detail::point_toward(first, first_center);\n        const\
    \ Point<long double> second_point =\n            circle_detail::point_toward(second,\
    \ second_center);\n        return ClosestPoints{first_point, second_point};\n\
    \    }\n    direction = direction / center_distance;\n    const long double first_radius\
    \ = static_cast<long double>(first.radius);\n    const long double second_radius\
    \ = static_cast<long double>(second.radius);\n    ClosestPoints result{\n    \
    \    first_center + direction * first_radius,\n        second_center + direction\
    \ * second_radius\n    };\n    for (const long double first_sign : {-1.0L, 1.0L})\
    \ {\n        for (const long double second_sign : {-1.0L, 1.0L}) {\n         \
    \   circle_detail::consider(\n                result,\n                ClosestPoints{\n\
    \                    first_center + direction * (first_sign * first_radius),\n\
    \                    second_center + direction * (second_sign * second_radius)\n\
    \                }\n            );\n        }\n    }\n    return result;\n}\n\n\
    template <Coordinate C, Coordinate P>\nlong double distance(const Circle<C>& circle,\
    \ const Point<P>& point) {\n    const ClosestPoints result = closest_points(circle,\
    \ point);\n    return geometry::distance(result.first, result.second);\n}\n\n\
    template <Coordinate P, Coordinate C>\nlong double distance(const Point<P>& point,\
    \ const Circle<C>& circle) {\n    return distance(circle, point);\n}\n\ntemplate\
    \ <Coordinate C, Coordinate L>\nlong double distance(const Circle<C>& circle,\
    \ const Line<L>& line) {\n    const ClosestPoints result = closest_points(circle,\
    \ line);\n    return geometry::distance(result.first, result.second);\n}\n\ntemplate\
    \ <Coordinate L, Coordinate C>\nlong double distance(const Line<L>& line, const\
    \ Circle<C>& circle) {\n    return distance(circle, line);\n}\n\ntemplate <Coordinate\
    \ C, Coordinate R>\nlong double distance(const Circle<C>& circle, const Ray<R>&\
    \ ray) {\n    const ClosestPoints result = closest_points(circle, ray);\n    return\
    \ geometry::distance(result.first, result.second);\n}\n\ntemplate <Coordinate\
    \ R, Coordinate C>\nlong double distance(const Ray<R>& ray, const Circle<C>& circle)\
    \ {\n    return distance(circle, ray);\n}\n\ntemplate <Coordinate C, Coordinate\
    \ S>\nlong double distance(const Circle<C>& circle, const Segment<S>& segment)\
    \ {\n    const ClosestPoints result = closest_points(circle, segment);\n    return\
    \ geometry::distance(result.first, result.second);\n}\n\ntemplate <Coordinate\
    \ S, Coordinate C>\nlong double distance(const Segment<S>& segment, const Circle<C>&\
    \ circle) {\n    return distance(circle, segment);\n}\n\ntemplate <Coordinate\
    \ A, Coordinate B>\nlong double distance(const Circle<A>& first, const Circle<B>&\
    \ second) {\n    const ClosestPoints result = closest_points(first, second);\n\
    \    return geometry::distance(result.first, result.second);\n}\n\n}  // namespace\
    \ geometry\n}  // namespace m1une\n\n\n#line 16 \"geometry/polygon.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\nenum class PointInPolygon {\n    Outside =\
    \ 0,\n    Boundary = 1,\n    Inside = 2,\n};\n\ntemplate <Coordinate T>\nstruct\
    \ Polygon {\n    std::vector<Point<T>> vertices;\n    bool filled = true;\n};\n\
    \nstruct ParameterInterval {\n    long double begin = 0.0L;\n    long double end\
    \ = 0.0L;\n};\n\ntemplate <Coordinate T>\nconstexpr Point<long double> centroid(\n\
    \    const std::array<Point<T>, 3>& triangle\n) {\n    return Point<long double>(\n\
    \        (\n            static_cast<long double>(triangle[0].x) +\n          \
    \  static_cast<long double>(triangle[1].x) +\n            static_cast<long double>(triangle[2].x)\n\
    \        ) / 3,\n        (\n            static_cast<long double>(triangle[0].y)\
    \ +\n            static_cast<long double>(triangle[1].y) +\n            static_cast<long\
    \ double>(triangle[2].y)\n        ) / 3\n    );\n}\n\nnamespace polygon_detail\
    \ {\n\ntemplate <Coordinate T>\nstd::vector<Point<T>> clean_polygon_vertices(\n\
    \    std::vector<Point<T>> polygon,\n    long double eps\n) {\n    if (\n    \
    \    polygon.size() >= 2 &&\n        polygon.front() == polygon.back()\n    )\
    \ {\n        polygon.pop_back();\n    }\n\n    std::vector<Point<T>> deduplicated;\n\
    \    for (const Point<T>& point : polygon) {\n        if (deduplicated.empty()\
    \ || deduplicated.back() != point) {\n            deduplicated.push_back(point);\n\
    \        }\n    }\n    if (\n        deduplicated.size() >= 2 &&\n        deduplicated.front()\
    \ == deduplicated.back()\n    ) {\n        deduplicated.pop_back();\n    }\n\n\
    \    bool changed = true;\n    while (changed && deduplicated.size() >= 3) {\n\
    \        changed = false;\n        std::vector<Point<T>> cleaned;\n        std::size_t\
    \ size = deduplicated.size();\n        for (std::size_t index = 0; index < size;\
    \ ++index) {\n            const Point<T>& previous =\n                deduplicated[(index\
    \ + size - 1) % size];\n            const Point<T>& current = deduplicated[index];\n\
    \            const Point<T>& next =\n                deduplicated[(index + 1)\
    \ % size];\n            if (\n                orientation(previous, current, next,\
    \ eps) == 0 &&\n                sign<T>(dot(current - previous, next - current),\
    \ eps) >= 0\n            ) {\n                changed = true;\n            } else\
    \ {\n                cleaned.push_back(current);\n            }\n        }\n \
    \       deduplicated = std::move(cleaned);\n    }\n    return deduplicated;\n\
    }\n\ntemplate <Coordinate T>\nbool in_ccw_triangle(\n    const Point<T>& point,\n\
    \    const Point<T>& first,\n    const Point<T>& second,\n    const Point<T>&\
    \ third,\n    long double eps\n) {\n    return\n        orientation(first, second,\
    \ point, eps) >= 0 &&\n        orientation(second, third, point, eps) >= 0 &&\n\
    \        orientation(third, first, point, eps) >= 0;\n}\n\n}  // namespace polygon_detail\n\
    \ntemplate <Coordinate T>\nwide_type<T> polygon_area2(const std::vector<Point<T>>&\
    \ polygon) {\n    wide_type<T> result = 0;\n    std::size_t n = polygon.size();\n\
    \    for (std::size_t i = 0; i < n; i++) {\n        result += cross(polygon[i],\
    \ polygon[(i + 1) % n]);\n    }\n    return result;\n}\n\ntemplate <Coordinate\
    \ T>\nlong double polygon_area(const std::vector<Point<T>>& polygon) {\n    return\
    \ std::fabs(static_cast<long double>(polygon_area2(polygon))) / 2;\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> polygon_centroid(\n    const\
    \ std::vector<Point<T>>& polygon,\n    long double eps = 1e-12L\n) {\n    if (polygon.size()\
    \ < 3) return std::nullopt;\n\n    wide_type<T> signed_area2 = polygon_area2(polygon);\n\
    \    if (sign<T>(signed_area2, eps) == 0) return std::nullopt;\n\n    long double\
    \ x_numerator = 0;\n    long double y_numerator = 0;\n    std::size_t size = polygon.size();\n\
    \    for (std::size_t index = 0; index < size; ++index) {\n        const Point<T>&\
    \ current = polygon[index];\n        const Point<T>& next = polygon[(index + 1)\
    \ % size];\n        long double weight = static_cast<long double>(cross(current,\
    \ next));\n        x_numerator +=\n            (static_cast<long double>(current.x)\
    \ +\n             static_cast<long double>(next.x)) *\n            weight;\n \
    \       y_numerator +=\n            (static_cast<long double>(current.y) +\n \
    \            static_cast<long double>(next.y)) *\n            weight;\n    }\n\
    \    long double denominator =\n        3.0L * static_cast<long double>(signed_area2);\n\
    \    return Point<long double>(\n        x_numerator / denominator,\n        y_numerator\
    \ / denominator\n    );\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long\
    \ double>> centroid(\n    const std::vector<Point<T>>& polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    return polygon_centroid(polygon, eps);\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> polygon_center_of_gravity(\n\
    \    const std::vector<Point<T>>& polygon,\n    long double eps = 1e-12L\n) {\n\
    \    return polygon_centroid(polygon, eps);\n}\n\ntemplate <Coordinate T>\nbool\
    \ is_simple_polygon(\n    const std::vector<Point<T>>& polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    if (polygon.size() < 3) return false;\n    std::size_t\
    \ size = polygon.size();\n    for (std::size_t index = 0; index < size; ++index)\
    \ {\n        const Point<T>& previous = polygon[(index + size - 1) % size];\n\
    \        const Point<T>& current = polygon[index];\n        const Point<T>& next\
    \ = polygon[(index + 1) % size];\n        if (current == next) return false;\n\
    \        if (\n            orientation(previous, current, next, eps) == 0 &&\n\
    \            sign<T>(dot(current - previous, next - current), eps) < 0\n     \
    \   ) {\n            return false;\n        }\n    }\n    for (std::size_t first_index\
    \ = 0; first_index < size; ++first_index) {\n        Segment<T> first{\n     \
    \       polygon[first_index],\n            polygon[(first_index + 1) % size]\n\
    \        };\n        for (\n            std::size_t second_index = first_index\
    \ + 1;\n            second_index < size;\n            ++second_index\n       \
    \ ) {\n            bool adjacent =\n                second_index == first_index\
    \ + 1 ||\n                (first_index == 0 && second_index + 1 == size);\n  \
    \          if (adjacent) continue;\n\n            Segment<T> second{\n       \
    \         polygon[second_index],\n                polygon[(second_index + 1) %\
    \ size]\n            };\n            if (intersects(first, second, eps)) return\
    \ false;\n        }\n    }\n    return true;\n}\n\ntemplate <Coordinate T>\nstd::optional<std::vector<std::array<Point<T>,\
    \ 3>>> triangulate_polygon(\n    std::vector<Point<T>> polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    polygon =\n        polygon_detail::clean_polygon_vertices(std::move(polygon),\
    \ eps);\n    if (polygon.size() < 3) return std::nullopt;\n\n    wide_type<T>\
    \ signed_area2 = polygon_area2(polygon);\n    if (sign<T>(signed_area2, eps) ==\
    \ 0) return std::nullopt;\n    if (!is_simple_polygon(polygon, eps)) return std::nullopt;\n\
    \    if (sign<T>(signed_area2, eps) < 0) {\n        std::reverse(polygon.begin(),\
    \ polygon.end());\n    }\n\n    std::vector<std::size_t> remaining(polygon.size());\n\
    \    for (std::size_t index = 0; index < polygon.size(); ++index) {\n        remaining[index]\
    \ = index;\n    }\n\n    std::vector<std::array<Point<T>, 3>> result;\n    result.reserve(polygon.size()\
    \ - 2);\n    while (remaining.size() > 3) {\n        bool found_ear = false;\n\
    \        std::size_t size = remaining.size();\n        for (std::size_t position\
    \ = 0; position < size; ++position) {\n            std::size_t previous_index\
    \ =\n                remaining[(position + size - 1) % size];\n            std::size_t\
    \ current_index = remaining[position];\n            std::size_t next_index =\n\
    \                remaining[(position + 1) % size];\n            const Point<T>&\
    \ previous = polygon[previous_index];\n            const Point<T>& current = polygon[current_index];\n\
    \            const Point<T>& next = polygon[next_index];\n            if (orientation(previous,\
    \ current, next, eps) <= 0) continue;\n\n            bool contains_vertex = false;\n\
    \            for (std::size_t other_index : remaining) {\n                if (\n\
    \                    other_index == previous_index ||\n                    other_index\
    \ == current_index ||\n                    other_index == next_index\n       \
    \         ) {\n                    continue;\n                }\n            \
    \    if (\n                    polygon_detail::in_ccw_triangle(\n            \
    \            polygon[other_index],\n                        previous,\n      \
    \                  current,\n                        next,\n                 \
    \       eps\n                    )\n                ) {\n                    contains_vertex\
    \ = true;\n                    break;\n                }\n            }\n    \
    \        if (contains_vertex) continue;\n\n            std::array<Point<T>, 3>\
    \ triangle;\n            triangle[0] = previous;\n            triangle[1] = current;\n\
    \            triangle[2] = next;\n            result.push_back(std::move(triangle));\n\
    \            remaining.erase(\n                remaining.begin() +\n         \
    \       static_cast<std::ptrdiff_t>(position)\n            );\n            found_ear\
    \ = true;\n            break;\n        }\n        if (!found_ear) return std::nullopt;\n\
    \    }\n\n    std::array<Point<T>, 3> triangle;\n    triangle[0] = polygon[remaining[0]];\n\
    \    triangle[1] = polygon[remaining[1]];\n    triangle[2] = polygon[remaining[2]];\n\
    \    if (orientation(triangle[0], triangle[1], triangle[2], eps) <= 0) {\n   \
    \     return std::nullopt;\n    }\n    result.push_back(std::move(triangle));\n\
    \    return result;\n}\n\ntemplate <Coordinate T>\nPointInPolygon point_in_polygon(\n\
    \    const std::vector<Point<T>>& polygon,\n    const Point<T>& point,\n    long\
    \ double eps = 1e-12L\n) {\n    bool inside = false;\n    std::size_t n = polygon.size();\n\
    \    for (std::size_t i = 0; i < n; i++) {\n        const Point<T>& a = polygon[i];\n\
    \        const Point<T>& b = polygon[(i + 1) % n];\n        if (on_segment(Segment<T>{a,\
    \ b}, point, eps)) {\n            return PointInPolygon::Boundary;\n        }\n\
    \n        if (a.y <= point.y) {\n            if (point.y < b.y && orientation(a,\
    \ b, point, eps) > 0) {\n                inside = !inside;\n            }\n  \
    \      } else if (b.y <= point.y && orientation(a, b, point, eps) < 0) {\n   \
    \         inside = !inside;\n        }\n    }\n    return inside ? PointInPolygon::Inside\
    \ : PointInPolygon::Outside;\n}\n\ntemplate <Coordinate T, Coordinate P>\nPointInPolygon\
    \ point_in_polygon(\n    const Polygon<T>& polygon,\n    const Point<P>& point,\n\
    \    long double eps = 1e-12L\n) {\n    assert(polygon.vertices.size() >= 3);\n\
    \    if constexpr (std::is_same_v<T, P>) {\n        return point_in_polygon(polygon.vertices,\
    \ point, eps);\n    } else {\n        std::vector<Point<long double>> vertices;\n\
    \        vertices.reserve(polygon.vertices.size());\n        for (const Point<T>&\
    \ vertex : polygon.vertices) {\n            vertices.emplace_back(vertex);\n \
    \       }\n        return point_in_polygon(vertices, Point<long double>(point),\
    \ eps);\n    }\n}\n\ntemplate <Coordinate T, Coordinate P>\nbool contains(\n \
    \   const Polygon<T>& polygon,\n    const Point<P>& point,\n    long double eps\
    \ = 1e-12L\n) {\n    const PointInPolygon relation = point_in_polygon(polygon,\
    \ point, eps);\n    return polygon.filled\n        ? relation != PointInPolygon::Outside\n\
    \        : relation == PointInPolygon::Boundary;\n}\n\nnamespace polygon_clip_detail\
    \ {\n\nstruct Event {\n    long double parameter;\n    bool toggle;\n};\n\ninline\
    \ bool close_parameter(\n    long double first,\n    long double second,\n   \
    \ long double eps\n) {\n    return std::fabs(first - second) <= eps * std::max({\n\
    \        1.0L,\n        std::fabs(first),\n        std::fabs(second)\n    });\n\
    }\n\ninline long double parameter_on_line(\n    const Point<long double>& origin,\n\
    \    const Point<long double>& direction,\n    const Point<long double>& point\n\
    ) {\n    return dot(point - origin, direction) / dot(direction, direction);\n\
    }\n\ninline std::vector<Event> grouped_events(\n    std::vector<Event> events,\n\
    \    long double eps\n) {\n    std::sort(\n        events.begin(),\n        events.end(),\n\
    \        [](const Event& first, const Event& second) {\n            return first.parameter\
    \ < second.parameter;\n        }\n    );\n    std::vector<Event> result;\n   \
    \ for (const Event& event : events) {\n        if (\n            result.empty()\
    \ ||\n            !close_parameter(result.back().parameter, event.parameter, eps)\n\
    \        ) {\n            result.push_back(event);\n        } else {\n       \
    \     result.back().toggle = result.back().toggle != event.toggle;\n        }\n\
    \    }\n    return result;\n}\n\ninline std::vector<ParameterInterval> merge_intervals(\n\
    \    std::vector<ParameterInterval> intervals,\n    long double eps\n) {\n   \
    \ for (ParameterInterval& interval : intervals) {\n        if (interval.end <\
    \ interval.begin) {\n            std::swap(interval.begin, interval.end);\n  \
    \      }\n    }\n    std::sort(\n        intervals.begin(),\n        intervals.end(),\n\
    \        [](const ParameterInterval& first, const ParameterInterval& second) {\n\
    \            if (first.begin != second.begin) return first.begin < second.begin;\n\
    \            return first.end < second.end;\n        }\n    );\n    std::vector<ParameterInterval>\
    \ result;\n    for (const ParameterInterval& interval : intervals) {\n       \
    \ if (\n            result.empty() ||\n            interval.begin > result.back().end\
    \ + eps * std::max({\n                1.0L,\n                std::fabs(interval.begin),\n\
    \                std::fabs(result.back().end)\n            })\n        ) {\n \
    \           result.push_back(interval);\n        } else if (result.back().end\
    \ < interval.end) {\n            result.back().end = interval.end;\n        }\n\
    \    }\n    return result;\n}\n\ntemplate <Coordinate T>\nstd::vector<ParameterInterval>\
    \ clip_line(\n    const Point<long double>& origin,\n    const Point<long double>&\
    \ direction,\n    const Polygon<T>& polygon,\n    long double eps\n) {\n    assert(polygon.vertices.size()\
    \ >= 3);\n    assert(direction != Point<long double>());\n    std::vector<Event>\
    \ events;\n    std::vector<ParameterInterval> intervals;\n    events.reserve(polygon.vertices.size()\
    \ * 2);\n    intervals.reserve(polygon.vertices.size());\n\n    const Line<long\
    \ double> line{origin, origin + direction};\n    for (std::size_t index = 0; index\
    \ < polygon.vertices.size(); ++index) {\n        const Point<long double> first(polygon.vertices[index]);\n\
    \        const Point<long double> second(\n            polygon.vertices[(index\
    \ + 1) % polygon.vertices.size()]\n        );\n        assert(first != second);\n\
    \        const Segment<long double> edge{first, second};\n        const LinearIntersection\
    \ intersection =\n            linear_intersection(line, edge, eps);\n        if\
    \ (intersection.kind == LinearIntersectionKind::Empty) continue;\n        if (intersection.kind\
    \ == LinearIntersectionKind::Segment) {\n            intervals.push_back(ParameterInterval{\n\
    \                parameter_on_line(origin, direction, intersection.first),\n \
    \               parameter_on_line(origin, direction, intersection.second)\n  \
    \          });\n            continue;\n        }\n        assert(intersection.kind\
    \ == LinearIntersectionKind::Point);\n        const Point<long double> point =\
    \ intersection.first;\n        const Point<long double> edge_direction = second\
    \ - first;\n        const long double edge_parameter =\n            dot(point\
    \ - first, edge_direction) /\n            dot(edge_direction, edge_direction);\n\
    \        bool toggle = false;\n        if (edge_parameter <= eps) {\n        \
    \    toggle = orientation(line.a, line.b, second, eps) > 0;\n        } else if\
    \ (edge_parameter >= 1.0L - eps) {\n            toggle = orientation(line.a, line.b,\
    \ first, eps) > 0;\n        } else {\n            toggle = true;\n        }\n\
    \        events.push_back(Event{\n            parameter_on_line(origin, direction,\
    \ point),\n            toggle\n        });\n    }\n\n    const std::vector<Event>\
    \ grouped = grouped_events(std::move(events), eps);\n    if (polygon.filled) {\n\
    \        bool inside = false;\n        for (std::size_t index = 0; index < grouped.size();\
    \ ++index) {\n            if (index > 0 && inside) {\n                intervals.push_back(ParameterInterval{\n\
    \                    grouped[index - 1].parameter,\n                    grouped[index].parameter\n\
    \                });\n            }\n            intervals.push_back(ParameterInterval{\n\
    \                grouped[index].parameter,\n                grouped[index].parameter\n\
    \            });\n            inside = inside != grouped[index].toggle;\n    \
    \    }\n    } else {\n        for (const Event& event : grouped) {\n         \
    \   intervals.push_back(ParameterInterval{\n                event.parameter,\n\
    \                event.parameter\n            });\n        }\n    }\n    return\
    \ merge_intervals(std::move(intervals), eps);\n}\n\ninline std::vector<ParameterInterval>\
    \ restrict_domain(\n    const std::vector<ParameterInterval>& intervals,\n   \
    \ long double lower,\n    long double upper,\n    long double eps\n) {\n    std::vector<ParameterInterval>\
    \ result;\n    result.reserve(intervals.size());\n    for (const ParameterInterval&\
    \ interval : intervals) {\n        long double begin = std::max(interval.begin,\
    \ lower);\n        long double end = std::min(interval.end, upper);\n        if\
    \ (\n            end < begin &&\n            !close_parameter(begin, end, eps)\n\
    \        ) {\n            continue;\n        }\n        if (end < begin) {\n \
    \           const long double middle = (begin + end) / 2.0L;\n            begin\
    \ = middle;\n            end = middle;\n        }\n        result.push_back(ParameterInterval{begin,\
    \ end});\n    }\n    return merge_intervals(std::move(result), eps);\n}\n\ninline\
    \ std::vector<Event> grouped_circle_events(\n    std::vector<Event> events,\n\
    \    long double eps\n) {\n    std::vector<Event> result = grouped_events(std::move(events),\
    \ eps);\n    const long double full = 2.0L * std::numbers::pi_v<long double>;\n\
    \    if (\n        result.size() >= 2 &&\n        close_parameter(result.front().parameter\
    \ + full,\n                        result.back().parameter, eps)\n    ) {\n  \
    \      result.front().parameter = 0.0L;\n        result.front().toggle =\n   \
    \         result.front().toggle != result.back().toggle;\n        result.pop_back();\n\
    \    }\n    return result;\n}\n\ntemplate <Coordinate C, Coordinate T>\nstd::vector<AngularCoverage>\
    \ clip_circle(\n    const Circle<C>& circle,\n    const Polygon<T>& polygon,\n\
    \    long double eps\n) {\n    assert(circle.radius >= 0);\n    assert(polygon.vertices.size()\
    \ >= 3);\n    if (circle.radius == 0) {\n        return contains(polygon, circle.center,\
    \ eps)\n            ? std::vector<AngularCoverage>{AngularCoverage{\n        \
    \          AngularCoverageKind::Point,\n                  0.0L,\n            \
    \      0.0L\n              }}\n            : std::vector<AngularCoverage>();\n\
    \    }\n\n    std::vector<Event> events;\n    events.reserve(polygon.vertices.size()\
    \ * 2);\n    for (std::size_t index = 0; index < polygon.vertices.size(); ++index)\
    \ {\n        const Point<long double> first(polygon.vertices[index]);\n      \
    \  const Point<long double> second(\n            polygon.vertices[(index + 1)\
    \ % polygon.vertices.size()]\n        );\n        assert(first != second);\n \
    \       const Point<long double> direction = second - first;\n        const Segment<long\
    \ double> edge{first, second};\n        const CircleLinearIntersection intersection\
    \ =\n            circle_boundary_intersection(circle, edge, eps);\n        for\
    \ (\n            int contact_index = 0;\n            contact_index < intersection.contact_count;\n\
    \            ++contact_index\n        ) {\n            const CircleLinearContact&\
    \ contact =\n                intersection.contacts[contact_index];\n         \
    \   const Point<long double> radial =\n                contact.point - Point<long\
    \ double>(circle.center);\n            bool toggle = false;\n            if (contact.linear_parameter\
    \ <= eps) {\n                toggle = predicate_detail::dot_sign<false>(\n   \
    \                 radial.x,\n                    radial.y,\n                 \
    \   direction.x,\n                    direction.y,\n                    eps\n\
    \                ) < 0;\n            } else if (contact.linear_parameter >= 1.0L\
    \ - eps) {\n                toggle = predicate_detail::dot_sign<false>(\n    \
    \                radial.x,\n                    radial.y,\n                  \
    \  -direction.x,\n                    -direction.y,\n                    eps\n\
    \                ) < 0;\n            } else {\n                toggle = predicate_detail::dot_sign<false>(\n\
    \                    radial.x,\n                    radial.y,\n              \
    \      direction.x,\n                    direction.y,\n                    eps\n\
    \                ) != 0;\n            }\n            events.push_back(Event{contact.circle_argument,\
    \ toggle});\n        }\n    }\n\n    const std::vector<Event> grouped =\n    \
    \    grouped_circle_events(std::move(events), eps);\n    const long double full\
    \ = 2.0L * std::numbers::pi_v<long double>;\n    if (grouped.empty()) {\n    \
    \    return contains(polygon, circle_point_at(circle, 0.0L), eps)\n          \
    \  ? std::vector<AngularCoverage>{AngularCoverage{\n                  AngularCoverageKind::Full,\n\
    \                  0.0L,\n                  full\n              }}\n         \
    \   : std::vector<AngularCoverage>();\n    }\n\n    std::vector<bool> inside_gap(grouped.size(),\
    \ false);\n    if (polygon.filled) {\n        const long double wrap_middle =\
    \ normalize_circle_argument(\n            (grouped.back().parameter + grouped.front().parameter\
    \ + full) /\n            2.0L\n        );\n        bool inside = point_in_polygon(\n\
    \            polygon,\n            circle_point_at(circle, wrap_middle),\n   \
    \         eps\n        ) != PointInPolygon::Outside;\n        for (std::size_t\
    \ index = 0; index < grouped.size(); ++index) {\n            inside = inside !=\
    \ grouped[index].toggle;\n            inside_gap[index] = inside;\n        }\n\
    \    }\n\n    if (\n        polygon.filled &&\n        std::all_of(\n        \
    \    inside_gap.begin(),\n            inside_gap.end(),\n            [](bool inside)\
    \ { return inside; }\n        )\n    ) {\n        return {AngularCoverage{AngularCoverageKind::Full,\
    \ 0.0L, full}};\n    }\n\n    std::vector<AngularCoverage> result;\n    for (std::size_t\
    \ index = 0; index < grouped.size(); ++index) {\n        const std::size_t previous\
    \ =\n            (index + grouped.size() - 1) % grouped.size();\n        if (!inside_gap[previous]\
    \ && !inside_gap[index]) {\n            result.push_back(AngularCoverage{\n  \
    \              AngularCoverageKind::Point,\n                grouped[index].parameter,\n\
    \                grouped[index].parameter\n            });\n        }\n      \
    \  if (!inside_gap[previous] && inside_gap[index]) {\n            std::size_t\
    \ finish = index;\n            while (inside_gap[finish]) {\n                finish\
    \ = (finish + 1) % grouped.size();\n            }\n            long double end\
    \ = grouped[finish].parameter;\n            if (end <= grouped[index].parameter)\
    \ end += full;\n            result.push_back(AngularCoverage{\n              \
    \  AngularCoverageKind::Arc,\n                grouped[index].parameter,\n    \
    \            end\n            });\n        }\n    }\n    std::sort(\n        result.begin(),\n\
    \        result.end(),\n        [](const AngularCoverage& first, const AngularCoverage&\
    \ second) {\n            return first.begin < second.begin;\n        }\n    );\n\
    \    return result;\n}\n\n}  // namespace polygon_clip_detail\n\ntemplate <Coordinate\
    \ L, Coordinate T>\nstd::vector<ParameterInterval> clip(\n    const Line<L>& line,\n\
    \    const Polygon<T>& polygon,\n    long double eps = 1e-12L\n) {\n    assert(line.a\
    \ != line.b);\n    assert(eps >= 0.0L);\n    const Point<long double> origin(line.a);\n\
    \    const Point<long double> direction =\n        Point<long double>(line.b)\
    \ - origin;\n    return polygon_clip_detail::clip_line(\n        origin,\n   \
    \     direction,\n        polygon,\n        eps\n    );\n}\n\ntemplate <Coordinate\
    \ R, Coordinate T>\nstd::vector<ParameterInterval> clip(\n    const Ray<R>& ray,\n\
    \    const Polygon<T>& polygon,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin\
    \ != ray.through);\n    assert(eps >= 0.0L);\n    const Point<long double> origin(ray.origin);\n\
    \    const Point<long double> direction =\n        Point<long double>(ray.through)\
    \ - origin;\n    return polygon_clip_detail::restrict_domain(\n        polygon_clip_detail::clip_line(origin,\
    \ direction, polygon, eps),\n        0.0L,\n        std::numeric_limits<long double>::infinity(),\n\
    \        eps\n    );\n}\n\ntemplate <Coordinate S, Coordinate T>\nstd::vector<ParameterInterval>\
    \ clip(\n    const Segment<S>& segment,\n    const Polygon<T>& polygon,\n    long\
    \ double eps = 1e-12L\n) {\n    assert(eps >= 0.0L);\n    if (segment.a == segment.b)\
    \ {\n        return contains(polygon, segment.a, eps)\n            ? std::vector<ParameterInterval>{ParameterInterval{0.0L,\
    \ 0.0L}}\n            : std::vector<ParameterInterval>();\n    }\n    const Point<long\
    \ double> origin(segment.a);\n    const Point<long double> direction =\n     \
    \   Point<long double>(segment.b) - origin;\n    return polygon_clip_detail::restrict_domain(\n\
    \        polygon_clip_detail::clip_line(origin, direction, polygon, eps),\n  \
    \      0.0L,\n        1.0L,\n        eps\n    );\n}\n\ntemplate <Coordinate C,\
    \ Coordinate T>\nstd::vector<AngularCoverage> clip(\n    const Circle<C>& circle,\n\
    \    const Polygon<T>& polygon,\n    long double eps = 1e-12L\n) {\n    assert(eps\
    \ >= 0.0L);\n    return polygon_clip_detail::clip_circle(circle, polygon, eps);\n\
    }\n\ntemplate <Coordinate T>\nbool intersects(\n    const Ray<T>& ray,\n    const\
    \ std::vector<Point<T>>& polygon,\n    long double eps = 1e-12L\n) {\n    assert(polygon.size()\
    \ >= 3);\n    if (point_in_polygon(polygon, ray.origin, eps) != PointInPolygon::Outside)\
    \ {\n        return true;\n    }\n    Polygon<T> region{polygon};\n    return\
    \ !clip(ray, region, eps).empty();\n}\n\ntemplate <Coordinate T>\nbool intersects(\n\
    \    const std::vector<Point<T>>& polygon,\n    const Ray<T>& ray,\n    long double\
    \ eps = 1e-12L\n) {\n    return intersects(ray, polygon, eps);\n}\n\ntemplate\
    \ <Coordinate T>\nlong double distance(\n    const Ray<T>& ray,\n    const std::vector<Point<T>>&\
    \ polygon\n) {\n    assert(polygon.size() >= 3);\n    if (intersects(ray, polygon))\
    \ return 0;\n    long double result = std::numeric_limits<long double>::infinity();\n\
    \    std::size_t size = polygon.size();\n    for (std::size_t index = 0; index\
    \ < size; ++index) {\n        result = std::min(\n            result,\n      \
    \      distance(\n                ray,\n                Segment<T>{\n        \
    \            polygon[index],\n                    polygon[(index + 1) % size]\n\
    \                }\n            )\n        );\n    }\n    return result;\n}\n\n\
    template <Coordinate T>\nlong double distance(\n    const std::vector<Point<T>>&\
    \ polygon,\n    const Ray<T>& ray\n) {\n    return distance(ray, polygon);\n}\n\
    \ntemplate <Coordinate T>\nbool intersects(\n    const std::vector<Point<T>>&\
    \ first,\n    const std::vector<Point<T>>& second,\n    long double eps = 1e-12L\n\
    ) {\n    assert(first.size() >= 3);\n    assert(second.size() >= 3);\n    std::size_t\
    \ first_size = first.size();\n    std::size_t second_size = second.size();\n \
    \   for (\n        std::size_t first_index = 0;\n        first_index < first_size;\n\
    \        ++first_index\n    ) {\n        Segment<T> first_edge{\n            first[first_index],\n\
    \            first[(first_index + 1) % first_size]\n        };\n        for (\n\
    \            std::size_t second_index = 0;\n            second_index < second_size;\n\
    \            ++second_index\n        ) {\n            Segment<T> second_edge{\n\
    \                second[second_index],\n                second[(second_index +\
    \ 1) % second_size]\n            };\n            if (intersects(first_edge, second_edge,\
    \ eps)) return true;\n        }\n    }\n    return\n        point_in_polygon(first,\
    \ second.front(), eps) !=\n            PointInPolygon::Outside ||\n        point_in_polygon(second,\
    \ first.front(), eps) !=\n            PointInPolygon::Outside;\n}\n\ntemplate\
    \ <Coordinate T>\nlong double distance(\n    const std::vector<Point<T>>& first,\n\
    \    const std::vector<Point<T>>& second\n) {\n    assert(first.size() >= 3);\n\
    \    assert(second.size() >= 3);\n    if (intersects(first, second)) return 0;\n\
    \n    long double result = std::numeric_limits<long double>::infinity();\n   \
    \ std::size_t first_size = first.size();\n    std::size_t second_size = second.size();\n\
    \    for (\n        std::size_t first_index = 0;\n        first_index < first_size;\n\
    \        ++first_index\n    ) {\n        Segment<T> first_edge{\n            first[first_index],\n\
    \            first[(first_index + 1) % first_size]\n        };\n        for (\n\
    \            std::size_t second_index = 0;\n            second_index < second_size;\n\
    \            ++second_index\n        ) {\n            Segment<T> second_edge{\n\
    \                second[second_index],\n                second[(second_index +\
    \ 1) % second_size]\n            };\n            result = std::min(result, distance(first_edge,\
    \ second_edge));\n        }\n    }\n    return result;\n}\n\ntemplate <Coordinate\
    \ T>\nwide_type<T> polygon_area2(const Polygon<T>& polygon) {\n    return polygon_area2(polygon.vertices);\n\
    }\n\ntemplate <Coordinate T>\nlong double polygon_area(const Polygon<T>& polygon)\
    \ {\n    return polygon_area(polygon.vertices);\n}\n\ntemplate <Coordinate T>\n\
    std::optional<Point<long double>> polygon_centroid(\n    const Polygon<T>& polygon,\n\
    \    long double eps = 1e-12L\n) {\n    return polygon_centroid(polygon.vertices,\
    \ eps);\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long double>> centroid(\n\
    \    const Polygon<T>& polygon,\n    long double eps = 1e-12L\n) {\n    return\
    \ polygon_centroid(polygon.vertices, eps);\n}\n\nnamespace polygon_detail {\n\n\
    template <Coordinate T>\nSegment<long double> edge(const Polygon<T>& polygon,\
    \ std::size_t index) {\n    return Segment<long double>{\n        Point<long double>(polygon.vertices[index]),\n\
    \        Point<long double>(\n            polygon.vertices[(index + 1) % polygon.vertices.size()]\n\
    \        )\n    };\n}\n\ntemplate <Coordinate T>\nClosestPoints closest_boundary_point(\n\
    \    const Polygon<T>& polygon,\n    const Point<long double>& point\n) {\n  \
    \  assert(polygon.vertices.size() >= 3);\n    ClosestPoints result = closest_points(edge(polygon,\
    \ 0), point);\n    for (std::size_t index = 1; index < polygon.vertices.size();\
    \ ++index) {\n        closest_points_detail::consider(\n            result,\n\
    \            closest_points(edge(polygon, index), point)\n        );\n    }\n\
    \    return result;\n}\n\ntemplate <Coordinate T, class Object>\nClosestPoints\
    \ closest_boundary_object(\n    const Polygon<T>& polygon,\n    const Object&\
    \ object\n) {\n    assert(polygon.vertices.size() >= 3);\n    ClosestPoints result\
    \ = closest_points(edge(polygon, 0), object);\n    for (std::size_t index = 1;\
    \ index < polygon.vertices.size(); ++index) {\n        closest_points_detail::consider(\n\
    \            result,\n            closest_points(edge(polygon, index), object)\n\
    \        );\n    }\n    return result;\n}\n\ntemplate <Coordinate A, Coordinate\
    \ B>\nClosestPoints closest_boundaries(\n    const Polygon<A>& first,\n    const\
    \ Polygon<B>& second\n) {\n    assert(first.vertices.size() >= 3);\n    assert(second.vertices.size()\
    \ >= 3);\n    ClosestPoints result = closest_points(edge(first, 0), edge(second,\
    \ 0));\n    for (\n        std::size_t first_index = 0;\n        first_index <\
    \ first.vertices.size();\n        ++first_index\n    ) {\n        for (\n    \
    \        std::size_t second_index = 0;\n            second_index < second.vertices.size();\n\
    \            ++second_index\n        ) {\n            closest_points_detail::consider(\n\
    \                result,\n                closest_points(\n                  \
    \  edge(first, first_index),\n                    edge(second, second_index)\n\
    \                )\n            );\n        }\n    }\n    return result;\n}\n\n\
    }  // namespace polygon_detail\n\ntemplate <Coordinate T, Coordinate P>\nClosestPoints\
    \ closest_points(\n    const Polygon<T>& polygon,\n    const Point<P>& point,\n\
    \    long double eps = 1e-12L\n) {\n    assert(polygon.vertices.size() >= 3);\n\
    \    const Point<long double> converted(point);\n    if (polygon.filled && contains(polygon,\
    \ point, eps)) {\n        return ClosestPoints{converted, converted};\n    }\n\
    \    return polygon_detail::closest_boundary_point(polygon, converted);\n}\n\n\
    template <Coordinate P, Coordinate T>\nClosestPoints closest_points(\n    const\
    \ Point<P>& point,\n    const Polygon<T>& polygon,\n    long double eps = 1e-12L\n\
    ) {\n    return closest_points_detail::reversed(\n        closest_points(polygon,\
    \ point, eps)\n    );\n}\n\ntemplate <Coordinate T, Coordinate S>\nClosestPoints\
    \ closest_points(\n    const Polygon<T>& polygon,\n    const Segment<S>& segment,\n\
    \    long double eps = 1e-12L\n) {\n    assert(polygon.vertices.size() >= 3);\n\
    \    const Segment<long double> converted{\n        Point<long double>(segment.a),\n\
    \        Point<long double>(segment.b)\n    };\n    if (polygon.filled) {\n  \
    \      if (contains(polygon, segment.a, eps)) {\n            const Point<long\
    \ double> point(segment.a);\n            return ClosestPoints{point, point};\n\
    \        }\n        if (contains(polygon, segment.b, eps)) {\n            const\
    \ Point<long double> point(segment.b);\n            return ClosestPoints{point,\
    \ point};\n        }\n    }\n    return polygon_detail::closest_boundary_object(polygon,\
    \ converted);\n}\n\ntemplate <Coordinate S, Coordinate T>\nClosestPoints closest_points(\n\
    \    const Segment<S>& segment,\n    const Polygon<T>& polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    return closest_points_detail::reversed(\n        closest_points(polygon,\
    \ segment, eps)\n    );\n}\n\ntemplate <Coordinate T, Coordinate R>\nClosestPoints\
    \ closest_points(\n    const Polygon<T>& polygon,\n    const Ray<R>& ray,\n  \
    \  long double eps = 1e-12L\n) {\n    assert(polygon.vertices.size() >= 3);\n\
    \    const Ray<long double> converted{\n        Point<long double>(ray.origin),\n\
    \        Point<long double>(ray.through)\n    };\n    if (polygon.filled && contains(polygon,\
    \ ray.origin, eps)) {\n        const Point<long double> point(ray.origin);\n \
    \       return ClosestPoints{point, point};\n    }\n    return polygon_detail::closest_boundary_object(polygon,\
    \ converted);\n}\n\ntemplate <Coordinate R, Coordinate T>\nClosestPoints closest_points(\n\
    \    const Ray<R>& ray,\n    const Polygon<T>& polygon,\n    long double eps =\
    \ 1e-12L\n) {\n    return closest_points_detail::reversed(\n        closest_points(polygon,\
    \ ray, eps)\n    );\n}\n\ntemplate <Coordinate A, Coordinate B>\nClosestPoints\
    \ closest_points(\n    const Polygon<A>& first,\n    const Polygon<B>& second,\n\
    \    long double eps = 1e-12L\n) {\n    assert(first.vertices.size() >= 3);\n\
    \    assert(second.vertices.size() >= 3);\n    ClosestPoints result = polygon_detail::closest_boundaries(first,\
    \ second);\n    if (geometry::distance(result.first, result.second) <= eps) return\
    \ result;\n\n    if (first.filled) {\n        for (const Point<B>& vertex : second.vertices)\
    \ {\n            if (contains(first, vertex, eps)) {\n                const Point<long\
    \ double> point(vertex);\n                return ClosestPoints{point, point};\n\
    \            }\n        }\n    }\n    if (second.filled) {\n        for (const\
    \ Point<A>& vertex : first.vertices) {\n            if (contains(second, vertex,\
    \ eps)) {\n                const Point<long double> point(vertex);\n         \
    \       return ClosestPoints{point, point};\n            }\n        }\n    }\n\
    \    return result;\n}\n\ntemplate <Coordinate C, Coordinate T>\nClosestPoints\
    \ closest_points(\n    const Circle<C>& circle,\n    const Polygon<T>& polygon,\n\
    \    long double eps = 1e-12L\n) {\n    assert(polygon.vertices.size() >= 3);\n\
    \    ClosestPoints result = closest_points(\n        circle,\n        polygon_detail::edge(polygon,\
    \ 0),\n        eps\n    );\n    for (std::size_t index = 1; index < polygon.vertices.size();\
    \ ++index) {\n        closest_points_detail::consider(\n            result,\n\
    \            closest_points(circle, polygon_detail::edge(polygon, index), eps)\n\
    \        );\n    }\n    if (geometry::distance(result.first, result.second) <=\
    \ eps) return result;\n\n    if (polygon.filled) {\n        Point<long double>\
    \ member(circle.center);\n        if (!circle.filled) {\n            member =\
    \ circle_detail::point_toward(circle, member);\n        }\n        if (contains(polygon,\
    \ member, eps)) {\n            return ClosestPoints{member, member};\n       \
    \ }\n    }\n    return result;\n}\n\ntemplate <Coordinate T, Coordinate C>\nClosestPoints\
    \ closest_points(\n    const Polygon<T>& polygon,\n    const Circle<C>& circle,\n\
    \    long double eps = 1e-12L\n) {\n    return closest_points_detail::reversed(\n\
    \        closest_points(circle, polygon, eps)\n    );\n}\n\ntemplate <Coordinate\
    \ T, Coordinate P>\nbool intersects(\n    const Polygon<T>& polygon,\n    const\
    \ Point<P>& point,\n    long double eps = 1e-12L\n) {\n    return contains(polygon,\
    \ point, eps);\n}\n\ntemplate <Coordinate P, Coordinate T>\nbool intersects(\n\
    \    const Point<P>& point,\n    const Polygon<T>& polygon,\n    long double eps\
    \ = 1e-12L\n) {\n    return intersects(polygon, point, eps);\n}\n\ntemplate <Coordinate\
    \ T, Coordinate S>\nbool intersects(\n    const Polygon<T>& polygon,\n    const\
    \ Segment<S>& segment,\n    long double eps = 1e-12L\n) {\n    const ClosestPoints\
    \ result = closest_points(polygon, segment, eps);\n    return geometry::distance(result.first,\
    \ result.second) <= eps;\n}\n\ntemplate <Coordinate S, Coordinate T>\nbool intersects(\n\
    \    const Segment<S>& segment,\n    const Polygon<T>& polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    return intersects(polygon, segment, eps);\n}\n\ntemplate\
    \ <Coordinate T, Coordinate R>\nbool intersects(\n    const Polygon<T>& polygon,\n\
    \    const Ray<R>& ray,\n    long double eps = 1e-12L\n) {\n    const ClosestPoints\
    \ result = closest_points(polygon, ray, eps);\n    return geometry::distance(result.first,\
    \ result.second) <= eps;\n}\n\ntemplate <Coordinate R, Coordinate T>\nbool intersects(\n\
    \    const Ray<R>& ray,\n    const Polygon<T>& polygon,\n    long double eps =\
    \ 1e-12L\n) {\n    return intersects(polygon, ray, eps);\n}\n\ntemplate <Coordinate\
    \ A, Coordinate B>\nbool intersects(\n    const Polygon<A>& first,\n    const\
    \ Polygon<B>& second,\n    long double eps = 1e-12L\n) {\n    const ClosestPoints\
    \ result = closest_points(first, second, eps);\n    return geometry::distance(result.first,\
    \ result.second) <= eps;\n}\n\ntemplate <Coordinate C, Coordinate T>\nbool intersects(\n\
    \    const Circle<C>& circle,\n    const Polygon<T>& polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    const ClosestPoints result = closest_points(circle, polygon,\
    \ eps);\n    return geometry::distance(result.first, result.second) <= eps;\n\
    }\n\ntemplate <Coordinate T, Coordinate C>\nbool intersects(\n    const Polygon<T>&\
    \ polygon,\n    const Circle<C>& circle,\n    long double eps = 1e-12L\n) {\n\
    \    return intersects(circle, polygon, eps);\n}\n\ntemplate <Coordinate A, Coordinate\
    \ B>\nlong double distance(\n    const Polygon<A>& first,\n    const Polygon<B>&\
    \ second\n) {\n    const ClosestPoints result = closest_points(first, second);\n\
    \    return geometry::distance(result.first, result.second);\n}\n\ntemplate <Coordinate\
    \ C, Coordinate T>\nlong double distance(\n    const Circle<C>& circle,\n    const\
    \ Polygon<T>& polygon\n) {\n    const ClosestPoints result = closest_points(circle,\
    \ polygon);\n    return geometry::distance(result.first, result.second);\n}\n\n\
    template <Coordinate T, Coordinate C>\nlong double distance(\n    const Polygon<T>&\
    \ polygon,\n    const Circle<C>& circle\n) {\n    return distance(circle, polygon);\n\
    }\n\ntemplate <Coordinate C, Coordinate T>\nlong double circle_polygon_intersection_area(\n\
    \    const Circle<C>& circle,\n    const Polygon<T>& polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    return circle_polygon_intersection_area(circle, polygon.vertices,\
    \ eps);\n}\n\ntemplate <Coordinate T, Coordinate P>\nlong double distance(\n \
    \   const Polygon<T>& polygon,\n    const Point<P>& point\n) {\n    const ClosestPoints\
    \ result = closest_points(polygon, point);\n    return geometry::distance(result.first,\
    \ result.second);\n}\n\ntemplate <Coordinate P, Coordinate T>\nlong double distance(\n\
    \    const Point<P>& point,\n    const Polygon<T>& polygon\n) {\n    return distance(polygon,\
    \ point);\n}\n\ntemplate <Coordinate T, Coordinate S>\nlong double distance(\n\
    \    const Polygon<T>& polygon,\n    const Segment<S>& segment\n) {\n    const\
    \ ClosestPoints result = closest_points(polygon, segment);\n    return geometry::distance(result.first,\
    \ result.second);\n}\n\ntemplate <Coordinate S, Coordinate T>\nlong double distance(\n\
    \    const Segment<S>& segment,\n    const Polygon<T>& polygon\n) {\n    return\
    \ distance(polygon, segment);\n}\n\ntemplate <Coordinate T, Coordinate R>\nlong\
    \ double distance(\n    const Polygon<T>& polygon,\n    const Ray<R>& ray\n) {\n\
    \    const ClosestPoints result = closest_points(polygon, ray);\n    return geometry::distance(result.first,\
    \ result.second);\n}\n\ntemplate <Coordinate R, Coordinate T>\nlong double distance(\n\
    \    const Ray<R>& ray,\n    const Polygon<T>& polygon\n) {\n    return distance(polygon,\
    \ ray);\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 21 \"\
    geometry/convex_polygon.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\nnamespace\
    \ convex_polygon_detail {\n\ninline bool points_close(\n    const Point<long double>&\
    \ first,\n    const Point<long double>& second,\n    long double eps\n) {\n  \
    \  return geometry::distance(first, second) <= eps;\n}\n\ninline std::vector<Point<long\
    \ double>> clean_polygon(\n    std::vector<Point<long double>> polygon,\n    long\
    \ double eps\n) {\n    if (polygon.empty()) return polygon;\n\n    std::vector<Point<long\
    \ double>> deduplicated;\n    for (const Point<long double>& point : polygon)\
    \ {\n        if (\n            deduplicated.empty() ||\n            !points_close(deduplicated.back(),\
    \ point, eps)\n        ) {\n            deduplicated.push_back(point);\n     \
    \   }\n    }\n    if (\n        deduplicated.size() >= 2 &&\n        points_close(\n\
    \            deduplicated.front(),\n            deduplicated.back(),\n       \
    \     eps\n        )\n    ) {\n        deduplicated.pop_back();\n    }\n    if\
    \ (deduplicated.size() <= 2) return deduplicated;\n    std::vector<Point<long\
    \ double>> cleaned;\n    const std::size_t size = deduplicated.size();\n    cleaned.reserve(size);\n\
    \    for (std::size_t index = 0; index < size; ++index) {\n        const Point<long\
    \ double>& previous =\n            deduplicated[(index + size - 1) % size];\n\
    \        const Point<long double>& current = deduplicated[index];\n        const\
    \ Point<long double>& next =\n            deduplicated[(index + 1) % size];\n\
    \        if (\n            orientation(previous, current, next, eps) != 0 ||\n\
    \            dot(current - previous, next - current) < -eps\n        ) {\n   \
    \         cleaned.push_back(current);\n        }\n    }\n    return cleaned;\n\
    }\n\n}  // namespace convex_polygon_detail\n\ntemplate <Coordinate T>\nbool is_convex_polygon(\n\
    \    const std::vector<Point<T>>& polygon,\n    bool strict = false,\n    long\
    \ double eps = 1e-12L\n) {\n    std::size_t size = polygon.size();\n    if (size\
    \ >= 2 && polygon.front() == polygon.back()) size--;\n    if (size < 3) return\
    \ false;\n\n    int direction = 0;\n    for (std::size_t index = 0; index < size;\
    \ ++index) {\n        const Point<T>& current = polygon[index];\n        const\
    \ Point<T>& next = polygon[(index + 1) % size];\n        const Point<T>& after\
    \ = polygon[(index + 2) % size];\n        if (current == next) return false;\n\
    \        const int turn = orientation(current, next, after, eps);\n        if\
    \ (turn == 0) {\n            if (strict) return false;\n            continue;\n\
    \        }\n        if (direction != 0 && direction != turn) return false;\n \
    \       direction = turn;\n    }\n    return !strict || direction != 0;\n}\n\n\
    template <Coordinate T>\nstd::vector<Point<T>> normalize_convex_polygon(\n   \
    \ std::vector<Point<T>> polygon,\n    long double eps = 1e-12L\n) {\n    return\
    \ convex_polygon_detail::normalize_convex_boundary(\n        std::move(polygon),\n\
    \        eps\n    );\n}\n\ntemplate <Coordinate T>\nPointInPolygon point_in_convex_polygon(\n\
    \    const std::vector<Point<T>>& polygon,\n    const Point<T>& point,\n    long\
    \ double eps = 1e-12L\n) {\n    const std::size_t size = polygon.size();\n   \
    \ if (size == 0) return PointInPolygon::Outside;\n    if (size == 1) {\n     \
    \   return distance(polygon[0], point) <= eps\n            ? PointInPolygon::Boundary\n\
    \            : PointInPolygon::Outside;\n    }\n    if (size == 2) {\n       \
    \ return on_segment(Segment<T>{polygon[0], polygon[1]}, point, eps)\n        \
    \    ? PointInPolygon::Boundary\n            : PointInPolygon::Outside;\n    }\n\
    \n    const int order = orientation(\n        polygon[0],\n        polygon[1],\n\
    \        polygon[size - 1],\n        eps\n    );\n    if (order == 0) return point_in_polygon(polygon,\
    \ point, eps);\n    auto vertex = [&](std::size_t index) -> const Point<T>& {\n\
    \        if (order > 0 || index == 0) return polygon[index];\n        return polygon[size\
    \ - index];\n    };\n\n    const int first_side = orientation(vertex(0), vertex(1),\
    \ point, eps);\n    const int last_side =\n        orientation(vertex(0), vertex(size\
    \ - 1), point, eps);\n    if (first_side < 0 || last_side > 0) {\n        return\
    \ PointInPolygon::Outside;\n    }\n    if (first_side == 0) {\n        return\
    \ on_segment(Segment<T>{vertex(0), vertex(1)}, point, eps)\n            ? PointInPolygon::Boundary\n\
    \            : PointInPolygon::Outside;\n    }\n    if (last_side == 0) {\n  \
    \      return on_segment(\n            Segment<T>{vertex(0), vertex(size - 1)},\n\
    \            point,\n            eps\n        )\n            ? PointInPolygon::Boundary\n\
    \            : PointInPolygon::Outside;\n    }\n\n    std::size_t left = 1;\n\
    \    std::size_t right = size - 1;\n    while (right - left >= 2) {\n        const\
    \ std::size_t middle = (left + right) / 2;\n        if (orientation(vertex(0),\
    \ vertex(middle), point, eps) >= 0) {\n            left = middle;\n        } else\
    \ {\n            right = middle;\n        }\n    }\n    const int triangle_side\
    \ =\n        orientation(vertex(left), vertex(right), point, eps);\n    if (triangle_side\
    \ < 0) return PointInPolygon::Outside;\n    if (triangle_side == 0) return PointInPolygon::Boundary;\n\
    \    return PointInPolygon::Inside;\n}\n\ntemplate <Coordinate T>\nclass ConvexPolygon\
    \ {\n   public:\n    using Wide = wide_type<T>;\n\n   private:\n    std::vector<Point<T>>\
    \ points;\n    std::vector<Wide> area_prefix;\n    long double epsilon;\n\n  \
    \  template <class Compare>\n    int periodic_best(Compare better) const {\n \
    \       const int size = int(points.size());\n        int left = 0;\n        int\
    \ middle = size;\n        int right = 2 * size;\n        while (right - left >\
    \ 2) {\n            const int left_middle = (left + middle) / 2;\n           \
    \ const int right_middle = (middle + right + 1) / 2;\n            if (better(left_middle\
    \ % size, middle % size)) {\n                right = middle;\n               \
    \ middle = left_middle;\n            } else if (better(right_middle % size, middle\
    \ % size)) {\n                left = middle;\n                middle = right_middle;\n\
    \            } else {\n                left = left_middle;\n                right\
    \ = right_middle;\n            }\n        }\n        return middle % size;\n \
    \   }\n\n    int previous(int index) const {\n        return index == 0 ? int(points.size())\
    \ - 1 : index - 1;\n    }\n\n    int next(int index) const {\n        return index\
    \ + 1 == int(points.size()) ? 0 : index + 1;\n    }\n\n   public:\n    explicit\
    \ ConvexPolygon(\n        std::vector<Point<T>> polygon,\n        long double\
    \ eps = 1e-12L\n    )\n        : points(normalize_convex_polygon(std::move(polygon),\
    \ eps)),\n          epsilon(eps) {\n        assert(\n            points.size()\
    \ <=\n            static_cast<std::size_t>(\n                std::numeric_limits<int>::max()\
    \ / 2\n            )\n        );\n        assert(\n            points.size() <\
    \ 3 ||\n            is_convex_polygon(points, true, epsilon)\n        );\n   \
    \     area_prefix.resize(2 * points.size() + 1, Wide(0));\n        for (std::size_t\
    \ index = 0; index < 2 * points.size(); ++index) {\n            area_prefix[index\
    \ + 1] =\n                area_prefix[index] +\n                cross(\n     \
    \               points[index % points.size()],\n                    points[(index\
    \ + 1) % points.size()]\n                );\n        }\n    }\n\n    int size()\
    \ const noexcept {\n        return int(points.size());\n    }\n\n    bool empty()\
    \ const noexcept {\n        return points.empty();\n    }\n\n    const std::vector<Point<T>>&\
    \ vertices() const noexcept {\n        return points;\n    }\n\n    const Point<T>&\
    \ operator[](int index) const {\n        assert(0 <= index && index < size());\n\
    \        return points[index];\n    }\n\n    Wide area2() const {\n        if\
    \ (points.empty()) return Wide(0);\n        return area_prefix[points.size()];\n\
    \    }\n\n    Wide chain_area2(int first, int last) const {\n        assert(0\
    \ <= first && first < size());\n        assert(0 <= last && last < size());\n\
    \        int extended_last = last;\n        if (extended_last < first) extended_last\
    \ += size();\n        return\n            area_prefix[extended_last] - area_prefix[first]\
    \ +\n            cross(points[last], points[first]);\n    }\n\n    PointInPolygon\
    \ contains(const Point<T>& point) const {\n        return point_in_convex_polygon(points,\
    \ point, epsilon);\n    }\n\n    std::pair<Wide, int> min_dot(const Point<T>&\
    \ direction) const {\n        assert(!points.empty());\n        const int index\
    \ = periodic_best([&](int first, int second) {\n            return dot(points[first],\
    \ direction) <\n                   dot(points[second], direction);\n        });\n\
    \        return std::pair<Wide, int>(dot(points[index], direction), index);\n\
    \    }\n\n    std::pair<Wide, int> max_dot(const Point<T>& direction) const {\n\
    \        assert(!points.empty());\n        const int index = periodic_best([&](int\
    \ first, int second) {\n            return dot(points[first], direction) >\n \
    \                  dot(points[second], direction);\n        });\n        return\
    \ std::pair<Wide, int>(dot(points[index], direction), index);\n    }\n\n    std::pair<int,\
    \ int> tangent_vertices(const Point<T>& point) const {\n        assert(points.size()\
    \ >= 3);\n        assert(contains(point) == PointInPolygon::Outside);\n      \
    \  int first = periodic_best([&](int left, int right) {\n            return orientation(point,\
    \ points[left], points[right], epsilon) < 0;\n        });\n        int second\
    \ = periodic_best([&](int left, int right) {\n            return orientation(point,\
    \ points[left], points[right], epsilon) > 0;\n        });\n        if (\n    \
    \        orientation(\n                point,\n                points[first],\n\
    \                points[previous(first)],\n                epsilon\n         \
    \   ) == 0\n        ) {\n            first = previous(first);\n        }\n   \
    \     if (\n            orientation(\n                point,\n               \
    \ points[second],\n                points[next(second)],\n                epsilon\n\
    \            ) == 0\n        ) {\n            second = next(second);\n       \
    \ }\n        return std::pair<int, int>(first, second);\n    }\n};\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> centroid(\n    const ConvexPolygon<T>&\
    \ polygon,\n    long double eps = 1e-12L\n) {\n    return polygon_centroid(polygon.vertices(),\
    \ eps);\n}\n\nnamespace convex_polygon_detail {\n\ntemplate <Coordinate T>\nclass\
    \ MinkowskiDifferenceView {\n   private:\n    struct Cycle {\n        const ConvexPolygon<T>*\
    \ polygon;\n        int start;\n        bool negate;\n\n        int edge_count()\
    \ const {\n            return polygon->size() >= 2 ? polygon->size() : 0;\n  \
    \      }\n\n        Point<T> point(int index) const {\n            const int size\
    \ = polygon->size();\n            const Point<T>& result = (*polygon)[(start +\
    \ index) % size];\n            return negate ? -result : result;\n        }\n\n\
    \        Point<T> edge(int index) const {\n            return point((index + 1)\
    \ % polygon->size()) - point(index);\n        }\n    };\n\n    Cycle first;\n\
    \    Cycle second;\n\n    std::pair<int, int> prefixes(int rank) const {\n   \
    \     const int first_size = first.edge_count();\n        const int second_size\
    \ = second.edge_count();\n        if (first_size + second_size == 0) {\n     \
    \       return std::pair<int, int>(0, 0);\n        }\n\n        int low = std::max(0,\
    \ rank - second_size);\n        int high = std::min(rank, first_size);\n     \
    \   while (low <= high) {\n            const int first_prefix = (low + high) /\
    \ 2;\n            const int second_prefix = rank - first_prefix;\n           \
    \ if (\n                first_prefix > 0 &&\n                second_prefix < second_size\
    \ &&\n                entry_less(\n                    second.edge(second_prefix),\n\
    \                    1,\n                    first.edge(first_prefix - 1),\n \
    \                   0\n                )\n            ) {\n                high\
    \ = first_prefix - 1;\n                continue;\n            }\n            if\
    \ (\n                second_prefix > 0 &&\n                first_prefix < first_size\
    \ &&\n                entry_less(\n                    first.edge(first_prefix),\n\
    \                    0,\n                    second.edge(second_prefix - 1),\n\
    \                    1\n                )\n            ) {\n                low\
    \ = first_prefix + 1;\n                continue;\n            }\n            return\
    \ std::pair<int, int>(first_prefix, second_prefix);\n        }\n        assert(false);\n\
    \        return std::pair<int, int>(0, 0);\n    }\n\n    static int direction_half(const\
    \ Point<T>& direction) {\n        return\n            direction.y > 0 ||\n   \
    \         (direction.y == 0 && direction.x >= 0)\n            ? 0\n          \
    \  : 1;\n    }\n\n    static bool entry_less(\n        const Point<T>& left,\n\
    \        int left_cycle,\n        const Point<T>& right,\n        int right_cycle\n\
    \    ) {\n        if constexpr (std::floating_point<T>) {\n            long double\
    \ left_angle = std::atan2(\n                static_cast<long double>(left.y),\n\
    \                static_cast<long double>(left.x)\n            );\n          \
    \  long double right_angle = std::atan2(\n                static_cast<long double>(right.y),\n\
    \                static_cast<long double>(right.x)\n            );\n         \
    \   if (left_angle < 0) {\n                left_angle += 2 * std::numbers::pi_v<long\
    \ double>;\n            }\n            if (right_angle < 0) {\n              \
    \  right_angle += 2 * std::numbers::pi_v<long double>;\n            }\n      \
    \      if (left_angle != right_angle) return left_angle < right_angle;\n     \
    \       return left_cycle < right_cycle;\n        }\n        const int left_half\
    \ = direction_half(left);\n        const int right_half = direction_half(right);\n\
    \        if (left_half != right_half) return left_half < right_half;\n       \
    \ const auto turn = cross(left, right);\n        if (turn != 0) return turn >\
    \ 0;\n        return left_cycle < right_cycle;\n    }\n\n    static int negated_start(const\
    \ ConvexPolygon<T>& polygon) {\n        if (polygon.size() <= 1) return 0;\n \
    \       int result = polygon.max_dot(Point<T>(0, 1)).second;\n        const int\
    \ previous = result == 0 ? polygon.size() - 1 : result - 1;\n        const int\
    \ next = result + 1 == polygon.size() ? 0 : result + 1;\n        for (const int\
    \ candidate : {previous, next}) {\n            if (\n                polygon[candidate].y\
    \ == polygon[result].y &&\n                polygon[candidate].x > polygon[result].x\n\
    \            ) {\n                result = candidate;\n            }\n       \
    \ }\n        return result;\n    }\n\n   public:\n    MinkowskiDifferenceView(\n\
    \        const ConvexPolygon<T>& minuend,\n        const ConvexPolygon<T>& subtrahend\n\
    \    )\n        : first{&minuend, 0, false},\n          second{&subtrahend, negated_start(subtrahend),\
    \ true} {\n        assert(!minuend.empty());\n        assert(!subtrahend.empty());\n\
    \    }\n\n    int size() const {\n        const int edge_count =\n           \
    \ first.edge_count() + second.edge_count();\n        return edge_count == 0 ?\
    \ 1 : edge_count;\n    }\n\n    Point<T> operator[](int rank) const {\n      \
    \  assert(0 <= rank && rank < size());\n        const auto [first_prefix, second_prefix]\
    \ = prefixes(rank);\n        return\n            first.point(first_prefix % first.polygon->size())\
    \ +\n            second.point(second_prefix % second.polygon->size());\n    }\n\
    \n    std::pair<Point<T>, Point<T>> components(int rank) const {\n        assert(0\
    \ <= rank && rank < size());\n        const auto [first_prefix, second_prefix]\
    \ = prefixes(rank);\n        return std::pair<Point<T>, Point<T>>(\n         \
    \   first.point(first_prefix % first.polygon->size()),\n            -second.point(second_prefix\
    \ % second.polygon->size())\n        );\n    }\n};\n\nstruct OriginLocation {\n\
    \    PointInPolygon location;\n    int outside_edge;\n    std::array<int, 3> simplex;\n\
    \    int simplex_size;\n};\n\ntemplate <Coordinate T, class Polygon>\nOriginLocation\
    \ locate_origin(\n    const Polygon& polygon,\n    long double eps\n) {\n    const\
    \ int size = polygon.size();\n    assert(size >= 3);\n    const Point<T> origin;\n\
    \    const Point<T> base = polygon[0];\n    int first = 1;\n    if (\n       \
    \ size >= 4 &&\n        orientation(base, polygon[1], polygon[2], eps) == 0 &&\n\
    \        dot(polygon[1] - base, polygon[2] - polygon[1]) > 0\n    ) {\n      \
    \  first = 2;\n    }\n    const int last = size - 1;\n\n    const int first_side\
    \ = orientation(base, polygon[first], origin, eps);\n    const int last_side =\
    \ orientation(base, polygon[last], origin, eps);\n    if (first_side < 0) {\n\
    \        return OriginLocation{\n            PointInPolygon::Outside,\n      \
    \      0,\n            std::array<int, 3>{0, 0, 0},\n            0,\n        };\n\
    \    }\n    if (last_side > 0) {\n        return OriginLocation{\n           \
    \ PointInPolygon::Outside,\n            last,\n            std::array<int, 3>{0,\
    \ 0, 0},\n            0,\n        };\n    }\n    if (first_side == 0) {\n    \
    \    if (on_segment(Segment<T>{base, polygon[first]}, origin, eps)) {\n      \
    \      return OriginLocation{\n                PointInPolygon::Boundary,\n   \
    \             -1,\n                std::array<int, 3>{0, first, 0},\n        \
    \        2,\n            };\n        }\n        return OriginLocation{\n     \
    \       PointInPolygon::Outside,\n            first,\n            std::array<int,\
    \ 3>{0, 0, 0},\n            0,\n        };\n    }\n    if (last_side == 0) {\n\
    \        if (on_segment(Segment<T>{base, polygon[last]}, origin, eps)) {\n   \
    \         return OriginLocation{\n                PointInPolygon::Boundary,\n\
    \                -1,\n                std::array<int, 3>{0, last, 0},\n      \
    \          2,\n            };\n        }\n        return OriginLocation{\n   \
    \         PointInPolygon::Outside,\n            last - 1,\n            std::array<int,\
    \ 3>{0, 0, 0},\n            0,\n        };\n    }\n\n    int left = first;\n \
    \   int right = last;\n    while (right - left >= 2) {\n        const int middle\
    \ = (left + right) / 2;\n        if (orientation(base, polygon[middle], origin,\
    \ eps) >= 0) {\n            left = middle;\n        } else {\n            right\
    \ = middle;\n        }\n    }\n    const int side = orientation(polygon[left],\
    \ polygon[right], origin, eps);\n    if (side < 0) {\n        return OriginLocation{\n\
    \            PointInPolygon::Outside,\n            left,\n            std::array<int,\
    \ 3>{0, 0, 0},\n            0,\n        };\n    }\n    if (side == 0) {\n    \
    \    const bool boundary = on_segment(\n            Segment<T>{polygon[left],\
    \ polygon[right]},\n            origin,\n            eps\n        );\n       \
    \ return OriginLocation{\n            boundary ? PointInPolygon::Boundary : PointInPolygon::Outside,\n\
    \            boundary ? -1 : left,\n            std::array<int, 3>{left, right,\
    \ 0},\n            boundary ? 2 : 0,\n        };\n    }\n    return OriginLocation{\n\
    \        PointInPolygon::Inside,\n        -1,\n        std::array<int, 3>{0, left,\
    \ right},\n        3,\n    };\n}\n\ntemplate <class Compare>\nint periodic_best(int\
    \ size, Compare better) {\n    int left = 0;\n    int middle = size;\n    int\
    \ right = 2 * size;\n    while (right - left > 2) {\n        const int left_middle\
    \ = (left + middle) / 2;\n        const int right_middle = (middle + right + 1)\
    \ / 2;\n        if (better(left_middle % size, middle % size)) {\n           \
    \ right = middle;\n            middle = left_middle;\n        } else if (better(right_middle\
    \ % size, middle % size)) {\n            left = middle;\n            middle =\
    \ right_middle;\n        } else {\n            left = left_middle;\n         \
    \   right = right_middle;\n        }\n    }\n    return middle % size;\n}\n\n\
    template <Coordinate T, class Polygon>\nstd::pair<int, int> tangent_vertices_from_origin(\n\
    \    const Polygon& polygon,\n    long double eps\n) {\n    const int size = polygon.size();\n\
    \    const Point<T> origin;\n    int first = periodic_best(size, [&](int left,\
    \ int right) {\n        return orientation(origin, polygon[left], polygon[right],\
    \ eps) < 0;\n    });\n    int second = periodic_best(size, [&](int left, int right)\
    \ {\n        return orientation(origin, polygon[left], polygon[right], eps) >\
    \ 0;\n    });\n    const int previous = first == 0 ? size - 1 : first - 1;\n \
    \   if (orientation(origin, polygon[first], polygon[previous], eps) == 0) {\n\
    \        first = previous;\n    }\n    const int next = second + 1 == size ? 0\
    \ : second + 1;\n    if (orientation(origin, polygon[second], polygon[next], eps)\
    \ == 0) {\n        second = next;\n    }\n    return std::pair<int, int>(first,\
    \ second);\n}\n\nstruct ClosestBoundaryFeature {\n    int first;\n    int second;\n\
    \    long double ratio;\n    long double distance;\n};\n\ntemplate <Coordinate\
    \ T, class Polygon>\nClosestBoundaryFeature closest_boundary_feature(\n    const\
    \ Polygon& polygon,\n    const OriginLocation& location,\n    long double eps\n\
    ) {\n    const int size = polygon.size();\n    assert(size >= 3);\n    assert(location.location\
    \ == PointInPolygon::Outside);\n    const Point<T> origin;\n\n    const auto tangents\
    \ = tangent_vertices_from_origin<T>(polygon, eps);\n    auto visible = [&](int\
    \ index) {\n        return orientation(\n            polygon[index],\n       \
    \     polygon[(index + 1) % size],\n            origin,\n            eps\n   \
    \     ) < 0;\n    };\n    auto forward_edges = [&](int start, int finish) {\n\
    \        return finish >= start ? finish - start : finish + size - start;\n  \
    \  };\n\n    int witness = location.outside_edge;\n    if (!visible(witness))\
    \ {\n        const int previous = witness == 0 ? size - 1 : witness - 1;\n   \
    \     const int next = witness + 1 == size ? 0 : witness + 1;\n        if (visible(previous))\
    \ {\n            witness = previous;\n        } else if (visible(next)) {\n  \
    \          witness = next;\n        }\n    }\n\n    int start = tangents.first;\n\
    \    int finish = tangents.second;\n    if (forward_edges(start, witness) >= forward_edges(start,\
    \ finish)) {\n        std::swap(start, finish);\n    }\n    int edge_count = forward_edges(start,\
    \ finish);\n    if (edge_count == 0) {\n        start = location.outside_edge;\n\
    \        finish = (start + 1) % size;\n        edge_count = 1;\n    }\n\n    auto\
    \ vertex = [&](int offset) {\n        return polygon[(start + offset) % size];\n\
    \    };\n    int left = 0;\n    int right = edge_count;\n    while (left < right)\
    \ {\n        const int middle = (left + right) / 2;\n        if (norm2(vertex(middle))\
    \ <= norm2(vertex(middle + 1))) {\n            right = middle;\n        } else\
    \ {\n            left = middle + 1;\n        }\n    }\n\n    ClosestBoundaryFeature\
    \ result{\n        (start + left) % size,\n        (start + left) % size,\n  \
    \      0,\n        norm(vertex(left)),\n    };\n    auto consider_edge = [&](int\
    \ first_offset, int second_offset) {\n        const Point<long double> first_point(vertex(first_offset));\n\
    \        const Point<long double> second_point(vertex(second_offset));\n     \
    \   const Point<long double> direction = second_point - first_point;\n       \
    \ long double ratio =\n            -dot(first_point, direction) / dot(direction,\
    \ direction);\n        ratio = std::clamp(ratio, 0.0L, 1.0L);\n        const long\
    \ double candidate_distance =\n            norm(first_point + direction * ratio);\n\
    \        if (candidate_distance < result.distance) {\n            result = ClosestBoundaryFeature{\n\
    \                (start + first_offset) % size,\n                (start + second_offset)\
    \ % size,\n                ratio,\n                candidate_distance,\n     \
    \       };\n        }\n    };\n    if (left > 0) {\n        consider_edge(left\
    \ - 1, left);\n    }\n    if (left < edge_count) {\n        consider_edge(left,\
    \ left + 1);\n    }\n    return result;\n}\n\ntemplate <Coordinate T, class Polygon>\n\
    long double distance_from_origin(\n    const Polygon& polygon,\n    long double\
    \ eps\n) {\n    const OriginLocation location = locate_origin<T>(polygon, eps);\n\
    \    if (location.location != PointInPolygon::Outside) return 0;\n    return closest_boundary_feature<T>(polygon,\
    \ location, eps).distance;\n}\n\ninline Point<long double> interpolate(\n    const\
    \ Point<long double>& first,\n    const Point<long double>& second,\n    long\
    \ double ratio\n) {\n    return first + (second - first) * ratio;\n}\n\ntemplate\
    \ <Coordinate T>\nClosestPoints\nclosest_points_from_difference(\n    const MinkowskiDifferenceView<T>&\
    \ difference,\n    long double eps\n) {\n    const OriginLocation location = locate_origin<T>(difference,\
    \ eps);\n    if (location.location == PointInPolygon::Outside) {\n        const\
    \ ClosestBoundaryFeature feature =\n            closest_boundary_feature<T>(difference,\
    \ location, eps);\n        const auto first_components = difference.components(feature.first);\n\
    \        const auto second_components = difference.components(feature.second);\n\
    \        return ClosestPoints{\n            interpolate(\n                Point<long\
    \ double>(first_components.first),\n                Point<long double>(second_components.first),\n\
    \                feature.ratio\n            ),\n            interpolate(\n   \
    \             Point<long double>(first_components.second),\n                Point<long\
    \ double>(second_components.second),\n                feature.ratio\n        \
    \    )\n        };\n    }\n\n    assert(location.simplex_size == 2 || location.simplex_size\
    \ == 3);\n    std::array<long double, 3> weight{0, 0, 0};\n    if (location.simplex_size\
    \ == 2) {\n        const Point<long double> first(difference[location.simplex[0]]);\n\
    \        const Point<long double> second(difference[location.simplex[1]]);\n \
    \       const Point<long double> direction = second - first;\n        weight[1]\
    \ = -dot(first, direction) / dot(direction, direction);\n        weight[1] = std::clamp(weight[1],\
    \ 0.0L, 1.0L);\n        weight[0] = 1 - weight[1];\n    } else {\n        const\
    \ Point<long double> first(difference[location.simplex[0]]);\n        const Point<long\
    \ double> second(difference[location.simplex[1]]);\n        const Point<long double>\
    \ third(difference[location.simplex[2]]);\n        const long double denominator\
    \ = cross(\n            second - first,\n            third - first\n        );\n\
    \        weight[0] = cross(second, third) / denominator;\n        weight[1] =\
    \ cross(third, first) / denominator;\n        weight[2] = cross(first, second)\
    \ / denominator;\n    }\n\n    Point<long double> first_result;\n    Point<long\
    \ double> second_result;\n    for (int index = 0; index < location.simplex_size;\
    \ ++index) {\n        const auto components = difference.components(\n       \
    \     location.simplex[index]\n        );\n        first_result += Point<long\
    \ double>(components.first) * weight[index];\n        second_result +=\n     \
    \       Point<long double>(components.second) * weight[index];\n    }\n    return\
    \ ClosestPoints{\n        first_result,\n        second_result\n    };\n}\n\n\
    }  // namespace convex_polygon_detail\n\ntemplate <Coordinate T>\nstd::vector<std::array<Point<T>,\
    \ 3>> triangulate_convex_polygon(\n    std::vector<Point<T>> polygon,\n    long\
    \ double eps = 1e-12L\n) {\n    polygon = normalize_convex_polygon(std::move(polygon),\
    \ eps);\n    if (polygon.size() < 3) return {};\n\n    std::vector<std::array<Point<T>,\
    \ 3>> result;\n    result.reserve(polygon.size() - 2);\n    for (std::size_t index\
    \ = 1; index + 1 < polygon.size(); ++index) {\n        std::array<Point<T>, 3>\
    \ triangle;\n        triangle[0] = polygon[0];\n        triangle[1] = polygon[index];\n\
    \        triangle[2] = polygon[index + 1];\n        result.push_back(std::move(triangle));\n\
    \    }\n    return result;\n}\n\ntemplate <Coordinate T>\nwide_type<T> convex_diameter2(\n\
    \    std::vector<Point<T>> polygon,\n    long double eps = 1e-12L\n) {\n    polygon\
    \ = normalize_convex_polygon(std::move(polygon), eps);\n    const std::size_t\
    \ size = polygon.size();\n    if (size <= 1) return 0;\n    if (size == 2) return\
    \ distance2(polygon[1], polygon[0]);\n\n    wide_type<T> result = 0;\n    std::size_t\
    \ opposite = 1;\n    for (std::size_t index = 0; index < size; ++index) {\n  \
    \      const std::size_t next = (index + 1) % size;\n        while (true) {\n\
    \            const std::size_t candidate = (opposite + 1) % size;\n          \
    \  const auto current_area =\n                cross(polygon[index], polygon[next],\
    \ polygon[opposite]);\n            const auto candidate_area =\n             \
    \   cross(polygon[index], polygon[next], polygon[candidate]);\n            if\
    \ (candidate_area <= current_area) break;\n            opposite = candidate;\n\
    \        }\n        result = std::max(\n            result,\n            distance2(polygon[index],\
    \ polygon[opposite])\n        );\n        result = std::max(\n            result,\n\
    \            distance2(polygon[next], polygon[opposite])\n        );\n    }\n\
    \    return result;\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<long double>>\
    \ convex_cut(\n    const std::vector<Point<T>>& polygon,\n    const Line<T>& boundary,\n\
    \    long double eps = 1e-12L\n) {\n    assert(boundary.a != boundary.b);\n  \
    \  std::vector<Point<long double>> input;\n    input.reserve(polygon.size());\n\
    \    for (const Point<T>& point : polygon) input.emplace_back(point);\n    if\
    \ (input.empty()) return input;\n\n    const Point<long double> line_start(boundary.a);\n\
    \    const Point<long double> line_end(boundary.b);\n    const Line<long double>\
    \ line{line_start, line_end};\n    std::vector<Point<long double>> result;\n \
    \   Point<long double> previous = input.back();\n    int previous_side = orientation(line_start,\
    \ line_end, previous, eps);\n    for (const Point<long double>& current : input)\
    \ {\n        const int current_side =\n            orientation(line_start, line_end,\
    \ current, eps);\n        const bool previous_inside = previous_side >= 0;\n \
    \       const bool current_inside = current_side >= 0;\n        if (previous_inside\
    \ != current_inside) {\n            const Line<long double> crossing{previous,\
    \ current};\n            const LinearIntersection intersection =\n           \
    \     linear_intersection(line, crossing, eps);\n            if (intersection.kind\
    \ == LinearIntersectionKind::Point) {\n                result.push_back(intersection.first);\n\
    \            }\n        }\n        if (current_inside) result.push_back(current);\n\
    \        previous = current;\n        previous_side = current_side;\n    }\n \
    \   return convex_polygon_detail::clean_polygon(std::move(result), eps);\n}\n\n\
    template <Coordinate T>\nbool convex_polygons_intersect(\n    const ConvexPolygon<T>&\
    \ first,\n    const ConvexPolygon<T>& second,\n    long double eps = 1e-12L\n\
    ) {\n    assert(!first.empty());\n    assert(!second.empty());\n    if (first.size()\
    \ <= 2 && second.size() <= 2) {\n        if (first.size() == 1 && second.size()\
    \ == 1) {\n            return distance(first[0], second[0]) <= eps;\n        }\n\
    \        if (first.size() == 1) {\n            return on_segment(\n          \
    \      Segment<T>{second[0], second[1]},\n                first[0],\n        \
    \        eps\n            );\n        }\n        if (second.size() == 1) {\n \
    \           return on_segment(\n                Segment<T>{first[0], first[1]},\n\
    \                second[0],\n                eps\n            );\n        }\n\
    \        return intersects(\n            Segment<T>{first[0], first[1]},\n   \
    \         Segment<T>{second[0], second[1]},\n            eps\n        );\n   \
    \ }\n\n    const convex_polygon_detail::MinkowskiDifferenceView<T> difference(\n\
    \        first,\n        second\n    );\n    return\n        convex_polygon_detail::locate_origin<T>(difference,\
    \ eps).location !=\n        PointInPolygon::Outside;\n}\n\ntemplate <Coordinate\
    \ T>\nbool convex_polygons_intersect(\n    const std::vector<Point<T>>& first,\n\
    \    const std::vector<Point<T>>& second,\n    long double eps = 1e-12L\n) {\n\
    \    assert(!first.empty());\n    assert(!second.empty());\n    std::vector<Point<T>>\
    \ negated;\n    negated.reserve(second.size());\n    for (const Point<T>& point\
    \ : second) negated.push_back(-point);\n    const std::vector<Point<T>> difference\
    \ =\n        minkowski_sum(first, std::move(negated), eps);\n    return\n    \
    \    point_in_convex_polygon(difference, Point<T>(), eps) !=\n        PointInPolygon::Outside;\n\
    }\n\ntemplate <Coordinate T>\nClosestPoints\nconvex_polygons_closest_points(\n\
    \    const ConvexPolygon<T>& first,\n    const ConvexPolygon<T>& second,\n   \
    \ long double eps = 1e-12L\n) {\n    assert(!first.empty());\n    assert(!second.empty());\n\
    \    if (first.size() <= 2 && second.size() <= 2) {\n        return closest_points(\n\
    \            Segment<T>{first[0], first[first.size() - 1]},\n            Segment<T>{second[0],\
    \ second[second.size() - 1]},\n            eps\n        );\n    }\n    const convex_polygon_detail::MinkowskiDifferenceView<T>\
    \ difference(\n        first,\n        second\n    );\n    return convex_polygon_detail::closest_points_from_difference(\n\
    \        difference,\n        eps\n    );\n}\n\ntemplate <Coordinate T>\nClosestPoints\n\
    convex_polygons_closest_points(\n    const std::vector<Point<T>>& first,\n   \
    \ const std::vector<Point<T>>& second,\n    long double eps = 1e-12L\n) {\n  \
    \  assert(!first.empty());\n    assert(!second.empty());\n    const ConvexPolygon<T>\
    \ first_query(first, eps);\n    const ConvexPolygon<T> second_query(second, eps);\n\
    \    return convex_polygons_closest_points(first_query, second_query, eps);\n\
    }\n\ntemplate <Coordinate T>\nlong double convex_polygons_distance(\n    const\
    \ ConvexPolygon<T>& first,\n    const ConvexPolygon<T>& second,\n    long double\
    \ eps = 1e-12L\n) {\n    assert(!first.empty());\n    assert(!second.empty());\n\
    \    if (first.size() <= 2 && second.size() <= 2) {\n        if (convex_polygons_intersect(first,\
    \ second, eps)) return 0;\n        if (first.size() == 1 && second.size() == 1)\
    \ {\n            return distance(first[0], second[0]);\n        }\n        if\
    \ (first.size() == 1) {\n            return distance(\n                Segment<T>{second[0],\
    \ second[1]},\n                first[0]\n            );\n        }\n        if\
    \ (second.size() == 1) {\n            return distance(\n                Segment<T>{first[0],\
    \ first[1]},\n                second[0]\n            );\n        }\n        return\
    \ distance(\n            Segment<T>{first[0], first[1]},\n            Segment<T>{second[0],\
    \ second[1]}\n        );\n    }\n\n    const convex_polygon_detail::MinkowskiDifferenceView<T>\
    \ difference(\n        first,\n        second\n    );\n    return convex_polygon_detail::distance_from_origin<T>(difference,\
    \ eps);\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<long double>> convex_polygon_intersection(\n\
    \    const std::vector<Point<T>>& first,\n    const std::vector<Point<T>>& second,\n\
    \    long double eps = 1e-12L\n) {\n    using HalfPlane = half_plane_intersection_detail::HalfPlane;\n\
    \    namespace detail = half_plane_intersection_detail;\n\n    const std::vector<Point<T>>\
    \ normalized_first =\n        normalize_convex_polygon(first, eps);\n    const\
    \ std::vector<Point<T>> normalized_second =\n        normalize_convex_polygon(second,\
    \ eps);\n    assert(normalized_first.size() >= 3);\n    assert(normalized_second.size()\
    \ >= 3);\n    assert(is_convex_polygon(normalized_first, true, eps));\n    assert(is_convex_polygon(normalized_second,\
    \ true, eps));\n    if (!convex_polygons_intersect(\n            normalized_first,\n\
    \            normalized_second,\n            eps\n        )) {\n        return\
    \ {};\n    }\n\n    auto boundaries = [](const std::vector<Point<T>>& polygon)\
    \ {\n        std::vector<HalfPlane> result;\n        result.reserve(polygon.size());\n\
    \        for (std::size_t index = 0; index < polygon.size(); ++index) {\n    \
    \        const Point<long double> point(polygon[index]);\n            Point<long\
    \ double> direction =\n                Point<long double>(polygon[(index + 1)\
    \ % polygon.size()]) -\n                point;\n            direction = direction\
    \ / norm(direction);\n            result.push_back(HalfPlane{point, direction});\n\
    \        }\n        return result;\n    };\n    const std::vector<HalfPlane> first_boundaries\
    \ =\n        boundaries(normalized_first);\n    const std::vector<HalfPlane> second_boundaries\
    \ =\n        boundaries(normalized_second);\n\n    std::vector<HalfPlane> merged;\n\
    \    merged.reserve(first_boundaries.size() + second_boundaries.size());\n   \
    \ std::size_t first_index = 0;\n    std::size_t second_index = 0;\n    while (\n\
    \        first_index < first_boundaries.size() ||\n        second_index < second_boundaries.size()\n\
    \    ) {\n        const bool take_first =\n            second_index == second_boundaries.size()\
    \ ||\n            (\n                first_index < first_boundaries.size() &&\n\
    \                detail::direction_less(\n                    first_boundaries[first_index],\n\
    \                    second_boundaries[second_index]\n                )\n    \
    \        );\n        if (take_first) {\n            detail::merge_same_direction(\n\
    \                merged,\n                first_boundaries[first_index++],\n \
    \               eps\n            );\n        } else {\n            detail::merge_same_direction(\n\
    \                merged,\n                second_boundaries[second_index++],\n\
    \                eps\n            );\n        }\n    }\n    detail::merge_cyclic_ends(merged,\
    \ eps);\n\n    std::deque<HalfPlane> active;\n    for (const HalfPlane& half_plane\
    \ : merged) {\n        while (active.size() >= 2) {\n            const std::optional<Point<long\
    \ double>> point =\n                detail::intersection(\n                  \
    \  active[active.size() - 2],\n                    active.back(),\n          \
    \          eps\n                );\n            if (\n                !point.has_value()\
    \ ||\n                !detail::outside(half_plane, *point, eps)\n            )\
    \ {\n                break;\n            }\n            active.pop_back();\n \
    \       }\n        while (active.size() >= 2) {\n            const std::optional<Point<long\
    \ double>> point =\n                detail::intersection(active[0], active[1],\
    \ eps);\n            if (\n                !point.has_value() ||\n           \
    \     !detail::outside(half_plane, *point, eps)\n            ) {\n           \
    \     break;\n            }\n            active.pop_front();\n        }\n    \
    \    active.push_back(half_plane);\n    }\n    while (active.size() >= 3) {\n\
    \        const std::optional<Point<long double>> point =\n            detail::intersection(\n\
    \                active[active.size() - 2],\n                active.back(),\n\
    \                eps\n            );\n        if (\n            !point.has_value()\
    \ ||\n            !detail::outside(active.front(), *point, eps)\n        ) {\n\
    \            break;\n        }\n        active.pop_back();\n    }\n    while (active.size()\
    \ >= 3) {\n        const std::optional<Point<long double>> point =\n         \
    \   detail::intersection(active[0], active[1], eps);\n        if (\n         \
    \   !point.has_value() ||\n            !detail::outside(active.back(), *point,\
    \ eps)\n        ) {\n            break;\n        }\n        active.pop_front();\n\
    \    }\n\n    std::vector<Point<long double>> result;\n    result.reserve(active.size());\n\
    \    for (std::size_t index = 0; index < active.size(); ++index) {\n        const\
    \ std::optional<Point<long double>> point =\n            detail::intersection(\n\
    \                active[index],\n                active[(index + 1) % active.size()],\n\
    \                eps\n            );\n        if (point.has_value()) result.push_back(*point);\n\
    \    }\n    return convex_polygon_detail::clean_polygon(std::move(result), eps);\n\
    }\n\ntemplate <Coordinate T>\nlong double convex_polygons_distance(\n    const\
    \ std::vector<Point<T>>& first,\n    const std::vector<Point<T>>& second,\n  \
    \  long double eps = 1e-12L\n) {\n    assert(!first.empty());\n    assert(!second.empty());\n\
    \    std::vector<Point<T>> negated;\n    negated.reserve(second.size());\n   \
    \ for (const Point<T>& point : second) negated.push_back(-point);\n    const std::vector<Point<T>>\
    \ difference =\n        minkowski_sum(first, std::move(negated), eps);\n    const\
    \ Point<T> origin;\n    if (\n        point_in_convex_polygon(difference, origin,\
    \ eps) !=\n        PointInPolygon::Outside\n    ) {\n        return 0;\n    }\n\
    \    if (difference.size() == 1) return distance(difference[0], origin);\n\n \
    \   long double result = std::numeric_limits<long double>::infinity();\n    for\
    \ (std::size_t index = 0; index < difference.size(); ++index) {\n        if (difference.size()\
    \ == 2 && index == 1) break;\n        result = std::min(\n            result,\n\
    \            distance(\n                Segment<T>{\n                    difference[index],\n\
    \                    difference[(index + 1) % difference.size()]\n           \
    \     },\n                origin\n            )\n        );\n    }\n    return\
    \ result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 4 \"\
    verify/geometry/is_convex_polygon.test.cpp\"\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#line 6 \"utilities/fast_io.hpp\"\n#include <cerrno>\n#include <charconv>\n\
    #line 9 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#include\
    \ <cstdint>\n#include <cstring>\n#include <iterator>\n#include <string>\n#include\
    \ <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace\
    \ m1une {\nnamespace utilities {\n\nstruct FastOutput;\n\nnamespace internal {\n\
    \n// Shared with the convenience helpers in template.hpp.\ninline FastOutput*\
    \ standard_output_instance = nullptr;\n\n// Detect std::begin(x), std::end(x).\n\
    template <class T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate\
    \ <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {\n        if (_stream == stdout\n          \
    \  && internal::standard_output_instance == nullptr) {\n            internal::standard_output_instance\
    \ = this;\n        }\n    }\n\n    FastOutput(const FastOutput&) = delete;\n \
    \   FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n        if (internal::standard_output_instance == this) {\n\
    \            internal::standard_output_instance = nullptr;\n        }\n    }\n\
    \n    void flush() {\n        if (_position != 0) {\n            std::fwrite(_buffer,\
    \ 1, _position, _stream);\n            _position = 0;\n        }\n        std::fflush(_stream);\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        std::size_t position = 0;\n        while (position\
    \ < s.size()) {\n            if (_position == buffer_size) flush();\n        \
    \    const std::size_t copied =\n                std::min<std::size_t>(buffer_size\
    \ - _position, s.size() - position);\n            std::memcpy(_buffer + _position,\
    \ s.data() + position, copied);\n            _position += int(copied);\n     \
    \       position += copied;\n        }\n    }\n\n    void write(char c) {\n  \
    \      write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 7 \"verify/geometry/is_convex_polygon.test.cpp\"\
    \n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int size;\n    fast_input >> size;\n    using Point = m1une::geometry::Point<long\
    \ long>;\n    std::vector<Point> polygon(size);\n    for (Point& point : polygon)\
    \ fast_input >> point.x >> point.y;\n    fast_output << m1une::geometry::is_convex_polygon(polygon)\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B\"\
    \n\n#include \"../../geometry/convex_polygon.hpp\"\n\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <vector>\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    int size;\n    fast_input\
    \ >> size;\n    using Point = m1une::geometry::Point<long long>;\n    std::vector<Point>\
    \ polygon(size);\n    for (Point& point : polygon) fast_input >> point.x >> point.y;\n\
    \    fast_output << m1une::geometry::is_convex_polygon(polygon) << '\\n';\n}\n"
  dependsOn:
  - geometry/convex_polygon.hpp
  - geometry/convex_hull.hpp
  - geometry/point.hpp
  - geometry/detail/floating_predicate.hpp
  - geometry/half_plane_intersection.hpp
  - geometry/linear.hpp
  - geometry/minkowski_sum.hpp
  - geometry/detail/convex_polygon_normalize.hpp
  - geometry/point.hpp
  - geometry/polygon.hpp
  - geometry/circle.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/is_convex_polygon.test.cpp
  requiredBy: []
  timestamp: '2026-08-26 23:16:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/is_convex_polygon.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/is_convex_polygon.test.cpp
- /verify/verify/geometry/is_convex_polygon.test.cpp.html
title: verify/geometry/is_convex_polygon.test.cpp
---
