---
data:
  _extendedDependsOn:
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
    path: geometry/half_plane_intersection.hpp
    title: Half-Plane Intersection
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: Lines and Segments
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
    path: geometry/polygon.hpp
    title: Polygons
  - icon: ':heavy_check_mark:'
    path: geometry/ray.hpp
    title: Rays
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/geometry/polygon_operations.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"geometry/convex_polygon.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <concepts>\n#include <cstddef>\n#include <deque>\n#include <limits>\n\
    #include <numbers>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"geometry/convex_hull.hpp\"\n\n\n\n#line 8 \"geometry/convex_hull.hpp\"\
    \n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#line 7 \"geometry/point.hpp\"\n#include\
    \ <type_traits>\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <typename\
    \ T>\nconcept Coordinate = std::is_arithmetic_v<T> && !std::same_as<std::remove_cv_t<T>,\
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
    geometry/half_plane_intersection.hpp\"\n\n\n\n#line 12 \"geometry/half_plane_intersection.hpp\"\
    \n#include <random>\n#line 15 \"geometry/half_plane_intersection.hpp\"\n\n#line\
    \ 1 \"geometry/line.hpp\"\n\n\n\n#line 9 \"geometry/line.hpp\"\n\n#line 11 \"\
    geometry/line.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate\
    \ T>\nstruct Line {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate\
    \ T>\nstruct Segment {\n    Point<T> a;\n    Point<T> b;\n};\n\nenum class SegmentIntersectionKind\
    \ {\n    Empty,\n    Point,\n    Overlap,\n};\n\nstruct SegmentIntersection {\n\
    \    SegmentIntersectionKind kind;\n    Point<long double> first;\n    Point<long\
    \ double> second;\n};\n\ntemplate <Coordinate T>\nconstexpr Point<long double>\
    \ centroid(const Segment<T>& segment) {\n    return Point<long double>(\n    \
    \    (\n            static_cast<long double>(segment.a.x) +\n            static_cast<long\
    \ double>(segment.b.x)\n        ) / 2,\n        (\n            static_cast<long\
    \ double>(segment.a.y) +\n            static_cast<long double>(segment.b.y)\n\
    \        ) / 2\n    );\n}\n\ntemplate <Coordinate T>\nbool on_line(\n    const\
    \ Line<T>& line,\n    const Point<T>& point,\n    long double eps = 1e-12L\n)\
    \ {\n    assert(line.a != line.b);\n    return orientation(line.a, line.b, point,\
    \ eps) == 0;\n}\n\ntemplate <Coordinate T>\nbool parallel(const Line<T>& first,\
    \ const Line<T>& second, long double eps = 1e-12L) {\n    using W = wide_type<T>;\n\
    \    W first_x = W(first.b.x) - W(first.a.x);\n    W first_y = W(first.b.y) -\
    \ W(first.a.y);\n    W second_x = W(second.b.x) - W(second.a.x);\n    W second_y\
    \ = W(second.b.y) - W(second.a.y);\n    return sign<T>(first_x * second_y - first_y\
    \ * second_x, eps) == 0;\n}\n\ntemplate <Coordinate T>\nbool orthogonal(const\
    \ Line<T>& first, const Line<T>& second, long double eps = 1e-12L) {\n    using\
    \ W = wide_type<T>;\n    W first_x = W(first.b.x) - W(first.a.x);\n    W first_y\
    \ = W(first.b.y) - W(first.a.y);\n    W second_x = W(second.b.x) - W(second.a.x);\n\
    \    W second_y = W(second.b.y) - W(second.a.y);\n    return sign<T>(first_x *\
    \ second_x + first_y * second_y, eps) == 0;\n}\n\ntemplate <Coordinate T>\nPoint<long\
    \ double> projection(const Line<T>& line, const Point<T>& point) {\n    assert(line.a\
    \ != line.b);\n    Point<long double> a(line.a);\n    Point<long double> direction(\n\
    \        static_cast<long double>(line.b.x) - static_cast<long double>(line.a.x),\n\
    \        static_cast<long double>(line.b.y) - static_cast<long double>(line.a.y)\n\
    \    );\n    Point<long double> offset(\n        static_cast<long double>(point.x)\
    \ - a.x,\n        static_cast<long double>(point.y) - a.y\n    );\n    long double\
    \ ratio = dot(offset, direction) / dot(direction, direction);\n    return a +\
    \ direction * ratio;\n}\n\ntemplate <Coordinate T>\nPoint<long double> reflection(const\
    \ Line<T>& line, const Point<T>& point) {\n    Point<long double> projected =\
    \ projection(line, point);\n    return projected * 2.0L - Point<long double>(point);\n\
    }\n\ntemplate <Coordinate T>\nlong double distance(const Line<T>& line, const\
    \ Point<T>& point) {\n    assert(line.a != line.b);\n    Point<long double> direction(\n\
    \        static_cast<long double>(line.b.x) - static_cast<long double>(line.a.x),\n\
    \        static_cast<long double>(line.b.y) - static_cast<long double>(line.a.y)\n\
    \    );\n    Point<long double> offset(\n        static_cast<long double>(point.x)\
    \ - static_cast<long double>(line.a.x),\n        static_cast<long double>(point.y)\
    \ - static_cast<long double>(line.a.y)\n    );\n    return std::fabs(cross(direction,\
    \ offset)) / norm(direction);\n}\n\ntemplate <Coordinate T>\nlong double distance(const\
    \ Point<T>& point, const Line<T>& line) {\n    return distance(line, point);\n\
    }\n\ntemplate <Coordinate T>\nbool intersects(\n    const Line<T>& first,\n  \
    \  const Line<T>& second,\n    long double eps = 1e-12L\n) {\n    return !parallel(first,\
    \ second, eps) || on_line(first, second.a, eps);\n}\n\ntemplate <Coordinate T>\n\
    long double distance(const Line<T>& first, const Line<T>& second) {\n    return\
    \ intersects(first, second) ? 0 : distance(first, second.a);\n}\n\ntemplate <Coordinate\
    \ T>\nbool on_segment(\n    const Segment<T>& segment,\n    const Point<T>& point,\n\
    \    long double eps = 1e-12L\n) {\n    if (orientation(segment.a, segment.b,\
    \ point, eps) != 0) return false;\n    using W = wide_type<T>;\n    W px = W(point.x);\n\
    \    W py = W(point.y);\n    W min_x = std::min(W(segment.a.x), W(segment.b.x));\n\
    \    W max_x = std::max(W(segment.a.x), W(segment.b.x));\n    W min_y = std::min(W(segment.a.y),\
    \ W(segment.b.y));\n    W max_y = std::max(W(segment.a.y), W(segment.b.y));\n\
    \    if constexpr (std::integral<T>) {\n        return min_x <= px && px <= max_x\
    \ && min_y <= py && py <= max_y;\n    } else {\n        return min_x - eps <=\
    \ px && px <= max_x + eps &&\n               min_y - eps <= py && py <= max_y\
    \ + eps;\n    }\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const Segment<T>&\
    \ first,\n    const Segment<T>& second,\n    long double eps = 1e-12L\n) {\n \
    \   int abc = orientation(first.a, first.b, second.a, eps);\n    int abd = orientation(first.a,\
    \ first.b, second.b, eps);\n    int cda = orientation(second.a, second.b, first.a,\
    \ eps);\n    int cdb = orientation(second.a, second.b, first.b, eps);\n\n    if\
    \ (abc == 0 && on_segment(first, second.a, eps)) return true;\n    if (abd ==\
    \ 0 && on_segment(first, second.b, eps)) return true;\n    if (cda == 0 && on_segment(second,\
    \ first.a, eps)) return true;\n    if (cdb == 0 && on_segment(second, first.b,\
    \ eps)) return true;\n    return abc * abd < 0 && cda * cdb < 0;\n}\n\ntemplate\
    \ <Coordinate T>\nbool intersects(\n    const Line<T>& line,\n    const Segment<T>&\
    \ segment,\n    long double eps = 1e-12L\n) {\n    int first_side = orientation(line.a,\
    \ line.b, segment.a, eps);\n    int second_side = orientation(line.a, line.b,\
    \ segment.b, eps);\n    return first_side == 0 || second_side == 0 || first_side\
    \ != second_side;\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const Segment<T>&\
    \ segment,\n    const Line<T>& line,\n    long double eps = 1e-12L\n) {\n    return\
    \ intersects(line, segment, eps);\n}\n\ntemplate <Coordinate T>\nlong double distance(const\
    \ Segment<T>& segment, const Point<T>& point) {\n    Point<long double> a(segment.a);\n\
    \    Point<long double> b(segment.b);\n    Point<long double> p(point);\n    Point<long\
    \ double> direction = b - a;\n    long double length_squared = dot(direction,\
    \ direction);\n    if (length_squared == 0) return geometry::distance(segment.a,\
    \ point);\n    long double ratio = dot(p - a, direction) / length_squared;\n \
    \   ratio = std::clamp(ratio, 0.0L, 1.0L);\n    Point<long double> closest = a\
    \ + direction * ratio;\n    return geometry::distance(closest, p);\n}\n\ntemplate\
    \ <Coordinate T>\nlong double distance(const Point<T>& point, const Segment<T>&\
    \ segment) {\n    return distance(segment, point);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Segment<T>& first, const Segment<T>& second)\
    \ {\n    if (intersects(first, second)) return 0;\n    return std::min({\n   \
    \     distance(first, second.a),\n        distance(first, second.b),\n       \
    \ distance(second, first.a),\n        distance(second, first.b),\n    });\n}\n\
    \ntemplate <Coordinate T>\nlong double distance(const Line<T>& line, const Segment<T>&\
    \ segment) {\n    if (intersects(line, segment)) return 0;\n    return std::min(distance(line,\
    \ segment.a), distance(line, segment.b));\n}\n\ntemplate <Coordinate T>\nlong\
    \ double distance(const Segment<T>& segment, const Line<T>& line) {\n    return\
    \ distance(line, segment);\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long\
    \ double>> line_intersection(\n    const Line<T>& first,\n    const Line<T>& second,\n\
    \    long double eps = 1e-12L\n) {\n    assert(first.a != first.b);\n    assert(second.a\
    \ != second.b);\n    using W = wide_type<T>;\n    const W first_x = W(first.b.x)\
    \ - W(first.a.x);\n    const W first_y = W(first.b.y) - W(first.a.y);\n    const\
    \ W second_x = W(second.b.x) - W(second.a.x);\n    const W second_y = W(second.b.y)\
    \ - W(second.a.y);\n    const W offset_x = W(second.a.x) - W(first.a.x);\n   \
    \ const W offset_y = W(second.a.y) - W(first.a.y);\n    const W denominator =\n\
    \        first_x * second_y - first_y * second_x;\n    if (sign<T>(denominator,\
    \ eps) == 0) return std::nullopt;\n    const W numerator = offset_x * second_y\
    \ - offset_y * second_x;\n    const long double ratio =\n        static_cast<long\
    \ double>(numerator) /\n        static_cast<long double>(denominator);\n    return\
    \ Point<long double>(\n        static_cast<long double>(first.a.x) +\n       \
    \     static_cast<long double>(first_x) * ratio,\n        static_cast<long double>(first.a.y)\
    \ +\n            static_cast<long double>(first_y) * ratio\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nSegmentIntersection segment_intersection(\n    const Segment<T>&\
    \ first,\n    const Segment<T>& second,\n    long double eps = 1e-12L\n) {\n \
    \   const Point<long double> zero;\n    if (!intersects(first, second, eps)) {\n\
    \        return SegmentIntersection{\n            SegmentIntersectionKind::Empty,\n\
    \            zero,\n            zero,\n        };\n    }\n    if (first.a == first.b)\
    \ {\n        const Point<long double> point(first.a);\n        return SegmentIntersection{\n\
    \            SegmentIntersectionKind::Point,\n            point,\n           \
    \ point,\n        };\n    }\n    if (second.a == second.b) {\n        const Point<long\
    \ double> point(second.a);\n        return SegmentIntersection{\n            SegmentIntersectionKind::Point,\n\
    \            point,\n            point,\n        };\n    }\n\n    const int first_a_side\
    \ =\n        orientation(second.a, second.b, first.a, eps);\n    const int first_b_side\
    \ =\n        orientation(second.a, second.b, first.b, eps);\n    const int second_a_side\
    \ =\n        orientation(first.a, first.b, second.a, eps);\n    const int second_b_side\
    \ =\n        orientation(first.a, first.b, second.b, eps);\n    const bool collinear_intersection\
    \ =\n        first_a_side == 0 && first_b_side == 0 &&\n        second_a_side\
    \ == 0 && second_b_side == 0;\n\n    if (!collinear_intersection) {\n        const\
    \ auto point = line_intersection(\n            Line<T>{first.a, first.b},\n  \
    \          Line<T>{second.a, second.b},\n            0.0L\n        );\n      \
    \  assert(point.has_value());\n        return SegmentIntersection{\n         \
    \   SegmentIntersectionKind::Point,\n            *point,\n            *point,\n\
    \        };\n    }\n\n    std::array<Point<T>, 4> candidates{\n        first.a,\n\
    \        first.b,\n        second.a,\n        second.b,\n    };\n    std::array<Point<T>,\
    \ 4> common;\n    int common_size = 0;\n    auto same_point = [eps](const Point<T>&\
    \ left, const Point<T>& right) {\n        if constexpr (std::integral<T>) {\n\
    \            return left == right;\n        } else {\n            return geometry::distance(left,\
    \ right) <= eps;\n        }\n    };\n    for (const Point<T>& candidate : candidates)\
    \ {\n        if (\n            !on_segment(first, candidate, eps) ||\n       \
    \     !on_segment(second, candidate, eps)\n        ) {\n            continue;\n\
    \        }\n        bool duplicate = false;\n        for (int index = 0; index\
    \ < common_size; ++index) {\n            if (same_point(common[index], candidate))\
    \ {\n                duplicate = true;\n                break;\n            }\n\
    \        }\n        if (!duplicate) common[common_size++] = candidate;\n    }\n\
    \    assert(common_size >= 1);\n\n    using W = wide_type<T>;\n    const W direction_x\
    \ = W(first.b.x) - W(first.a.x);\n    const W direction_y = W(first.b.y) - W(first.a.y);\n\
    \    const W absolute_x = direction_x >= 0 ? direction_x : -direction_x;\n   \
    \ const W absolute_y = direction_y >= 0 ? direction_y : -direction_y;\n    const\
    \ bool use_x = absolute_x >= absolute_y;\n    auto parameter = [&](const Point<T>&\
    \ point) {\n        if (use_x) {\n            return direction_x >= 0 ? W(point.x)\
    \ : -W(point.x);\n        }\n        return direction_y >= 0 ? W(point.y) : -W(point.y);\n\
    \    };\n    int start_index = 0;\n    int finish_index = 0;\n    for (int index\
    \ = 1; index < common_size; ++index) {\n        if (parameter(common[index]) <\
    \ parameter(common[start_index])) {\n            start_index = index;\n      \
    \  }\n        if (parameter(common[finish_index]) < parameter(common[index]))\
    \ {\n            finish_index = index;\n        }\n    }\n\n    const Point<long\
    \ double> start(common[start_index]);\n    const Point<long double> finish(common[finish_index]);\n\
    \    if (same_point(common[start_index], common[finish_index])) {\n        return\
    \ SegmentIntersection{\n            SegmentIntersectionKind::Point,\n        \
    \    start,\n            start,\n        };\n    }\n    return SegmentIntersection{\n\
    \        SegmentIntersectionKind::Overlap,\n        start,\n        finish,\n\
    \    };\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long double>> line_segment_intersection(\n\
    \    const Line<T>& line,\n    const Segment<T>& segment,\n    long double eps\
    \ = 1e-12L\n) {\n    assert(line.a != line.b);\n    if (segment.a == segment.b)\
    \ {\n        if (on_line(line, segment.a, eps)) {\n            return Point<long\
    \ double>(segment.a);\n        }\n        return std::nullopt;\n    }\n    if\
    \ (!intersects(line, segment, eps)) return std::nullopt;\n    Line<T> supporting_line{segment.a,\
    \ segment.b};\n    return line_intersection(line, supporting_line, eps);\n}\n\n\
    template <Coordinate T>\nstd::optional<Point<long double>> line_segment_intersection(\n\
    \    const Segment<T>& segment,\n    const Line<T>& line,\n    long double eps\
    \ = 1e-12L\n) {\n    return line_segment_intersection(line, segment, eps);\n}\n\
    \n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 17 \"geometry/half_plane_intersection.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\nenum class HalfPlaneIntersectionStatus\
    \ {\n    Empty,\n    Unbounded,\n    Degenerate,\n    Bounded,\n};\n\nstruct HalfPlaneIntersectionResult\
    \ {\n    HalfPlaneIntersectionStatus status;\n    std::vector<Point<long double>>\
    \ polygon;\n};\n\nnamespace half_plane_intersection_detail {\n\nstruct HalfPlane\
    \ {\n    Point<long double> point;\n    Point<long double> direction;\n};\n\n\
    inline int direction_half(const Point<long double>& direction) {\n    return direction.y\
    \ > 0 || (direction.y == 0 && direction.x >= 0) ? 0 : 1;\n}\n\ninline bool direction_less(const\
    \ HalfPlane& first, const HalfPlane& second) {\n    int first_half = direction_half(first.direction);\n\
    \    int second_half = direction_half(second.direction);\n    if (first_half !=\
    \ second_half) return first_half < second_half;\n    return cross(first.direction,\
    \ second.direction) > 0;\n}\n\ninline bool parallel(\n    const HalfPlane& first,\n\
    \    const HalfPlane& second,\n    long double eps\n) {\n    return std::fabs(cross(first.direction,\
    \ second.direction)) <= eps;\n}\n\ninline bool same_direction(\n    const HalfPlane&\
    \ first,\n    const HalfPlane& second,\n    long double eps\n) {\n    return parallel(first,\
    \ second, eps) &&\n           dot(first.direction, second.direction) > 0;\n}\n\
    \ninline bool outside(\n    const HalfPlane& half_plane,\n    const Point<long\
    \ double>& point,\n    long double eps\n) {\n    return cross(half_plane.direction,\
    \ point - half_plane.point) < -eps;\n}\n\ninline bool more_restrictive(\n    const\
    \ HalfPlane& candidate,\n    const HalfPlane& current,\n    long double eps\n\
    ) {\n    return cross(\n        current.direction,\n        candidate.point -\
    \ current.point\n    ) > eps;\n}\n\ninline std::optional<Point<long double>> intersection(\n\
    \    const HalfPlane& first,\n    const HalfPlane& second,\n    long double eps\n\
    ) {\n    long double denominator = cross(first.direction, second.direction);\n\
    \    if (std::fabs(denominator) <= eps) return std::nullopt;\n    long double\
    \ ratio = cross(\n        second.point - first.point,\n        second.direction\n\
    \    ) / denominator;\n    return first.point + first.direction * ratio;\n}\n\n\
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
    \ double>;\n    std::vector<long double> angles;\n    angles.reserve(half_planes.size());\n\
    \    for (const HalfPlane& half_plane : half_planes) {\n        long double angle\
    \ = std::atan2(\n            half_plane.direction.y,\n            half_plane.direction.x\n\
    \        );\n        if (angle < 0) angle += 2 * pi;\n        angles.push_back(angle);\n\
    \    }\n\n    long double maximum_gap = angles.front() + 2 * pi - angles.back();\n\
    \    for (std::size_t index = 1; index < angles.size(); ++index) {\n        maximum_gap\
    \ = std::max(\n            maximum_gap,\n            angles[index] - angles[index\
    \ - 1]\n        );\n    }\n    return maximum_gap < pi - eps;\n}\n\n}  // namespace\
    \ half_plane_intersection_detail\n\n// Each directed line keeps its closed left\
    \ half-plane. Returns the vertices of\n// a bounded intersection with positive\
    \ area in counterclockwise order. Empty,\n// unbounded, and bounded zero-area\
    \ intersections have distinct statuses.\ntemplate <Coordinate T>\nHalfPlaneIntersectionResult\
    \ half_plane_intersection(\n    const std::vector<Line<T>>& half_planes,\n   \
    \ long double eps = 1e-12L\n) {\n    using half_plane_intersection_detail::HalfPlane;\n\
    \    namespace detail = half_plane_intersection_detail;\n\n    assert(eps >= 0);\n\
    \    std::vector<HalfPlane> sorted;\n    sorted.reserve(half_planes.size());\n\
    \    for (const Line<T>& line : half_planes) {\n        assert(line.a != line.b);\n\
    \        Point<long double> point(line.a);\n        Point<long double> direction\
    \ = Point<long double>(line.b) - point;\n        long double length = norm(direction);\n\
    \        direction = direction / length;\n        sorted.push_back(HalfPlane{point,\
    \ direction});\n    }\n    if (!detail::has_feasible_point(sorted, eps)) {\n \
    \       return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Empty,\n\
    \            {},\n        };\n    }\n    std::sort(sorted.begin(), sorted.end(),\
    \ detail::direction_less);\n    if (!detail::has_bounded_recession_cone(sorted,\
    \ eps)) {\n        return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Unbounded,\n\
    \            {},\n        };\n    }\n    if (sorted.size() < 3) {\n        return\
    \ HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    std::vector<HalfPlane> unique;\n  \
    \  unique.reserve(sorted.size());\n    for (const HalfPlane& half_plane : sorted)\
    \ {\n        detail::merge_same_direction(unique, half_plane, eps);\n    }\n \
    \   detail::merge_cyclic_ends(unique, eps);\n    if (unique.size() < 3) {\n  \
    \      return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    std::deque<HalfPlane> deque;\n    for\
    \ (const HalfPlane& half_plane : unique) {\n        while (deque.size() >= 2)\
    \ {\n            auto point = detail::intersection(\n                deque[deque.size()\
    \ - 2],\n                deque.back(),\n                eps\n            );\n\
    \            if (!point.has_value()) {\n                return HalfPlaneIntersectionResult{\n\
    \                    HalfPlaneIntersectionStatus::Degenerate,\n              \
    \      {},\n                };\n            }\n            if (!detail::outside(half_plane,\
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
    }  // namespace m1une\n\n\n#line 1 \"geometry/polygon.hpp\"\n\n\n\n#line 12 \"\
    geometry/polygon.hpp\"\n\n#line 1 \"geometry/ray.hpp\"\n\n\n\n#line 7 \"geometry/ray.hpp\"\
    \n\n#line 9 \"geometry/ray.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\n\
    template <Coordinate T>\nstruct Ray {\n    Point<T> origin;\n    Point<T> through;\n\
    };\n\nnamespace ray_detail {\n\ntemplate <Coordinate T>\nstruct Parameters {\n\
    \    wide_type<T> denominator;\n    wide_type<T> first_numerator;\n    wide_type<T>\
    \ second_numerator;\n};\n\ntemplate <Coordinate T>\nParameters<T> parameters(\n\
    \    const Point<T>& first_origin,\n    const Point<T>& first_through,\n    const\
    \ Point<T>& second_origin,\n    const Point<T>& second_through\n) {\n    using\
    \ W = wide_type<T>;\n    W first_x = W(first_through.x) - W(first_origin.x);\n\
    \    W first_y = W(first_through.y) - W(first_origin.y);\n    W second_x = W(second_through.x)\
    \ - W(second_origin.x);\n    W second_y = W(second_through.y) - W(second_origin.y);\n\
    \    W offset_x = W(second_origin.x) - W(first_origin.x);\n    W offset_y = W(second_origin.y)\
    \ - W(first_origin.y);\n    return Parameters<T>{\n        first_x * second_y\
    \ - first_y * second_x,\n        offset_x * second_y - offset_y * second_x,\n\
    \        offset_x * first_y - offset_y * first_x\n    };\n}\n\ntemplate <Coordinate\
    \ T>\nbool ratio_nonnegative(\n    wide_type<T> numerator,\n    wide_type<T> denominator,\n\
    \    long double eps\n) {\n    int numerator_sign = sign<T>(numerator, eps);\n\
    \    int denominator_sign = sign<T>(denominator, eps);\n    return numerator_sign\
    \ == 0 || numerator_sign == denominator_sign;\n}\n\ntemplate <Coordinate T>\n\
    bool ratio_in_unit_interval(\n    wide_type<T> numerator,\n    wide_type<T> denominator,\n\
    \    long double eps\n) {\n    if (sign<T>(denominator, eps) > 0) {\n        return\
    \ sign<T>(numerator, eps) >= 0 &&\n               sign<T>(numerator - denominator,\
    \ eps) <= 0;\n    }\n    return sign<T>(numerator, eps) <= 0 &&\n           sign<T>(numerator\
    \ - denominator, eps) >= 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double>\
    \ point_at(\n    const Ray<T>& ray,\n    wide_type<T> numerator,\n    wide_type<T>\
    \ denominator\n) {\n    long double ratio =\n        static_cast<long double>(numerator)\
    \ /\n        static_cast<long double>(denominator);\n    Point<long double> origin(ray.origin);\n\
    \    Point<long double> direction =\n        Point<long double>(ray.through) -\
    \ origin;\n    return origin + direction * ratio;\n}\n\n}  // namespace ray_detail\n\
    \ntemplate <Coordinate T>\nbool on_ray(\n    const Ray<T>& ray,\n    const Point<T>&\
    \ point,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin != ray.through);\n\
    \    if (orientation(ray.origin, ray.through, point, eps) != 0) return false;\n\
    \    using W = wide_type<T>;\n    W direction_x = W(ray.through.x) - W(ray.origin.x);\n\
    \    W direction_y = W(ray.through.y) - W(ray.origin.y);\n    W offset_x = W(point.x)\
    \ - W(ray.origin.x);\n    W offset_y = W(point.y) - W(ray.origin.y);\n    return\
    \ sign<T>(direction_x * offset_x + direction_y * offset_y, eps) >= 0;\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> projection(const Ray<T>& ray, const Point<T>&\
    \ point) {\n    assert(ray.origin != ray.through);\n    Point<long double> origin(ray.origin);\n\
    \    Point<long double> direction =\n        Point<long double>(ray.through) -\
    \ origin;\n    Point<long double> offset = Point<long double>(point) - origin;\n\
    \    long double ratio = dot(offset, direction) / dot(direction, direction);\n\
    \    if (ratio < 0) ratio = 0;\n    return origin + direction * ratio;\n}\n\n\
    template <Coordinate T>\nlong double distance(const Ray<T>& ray, const Point<T>&\
    \ point) {\n    return geometry::distance(projection(ray, point), Point<long double>(point));\n\
    }\n\ntemplate <Coordinate T>\nlong double distance(const Point<T>& point, const\
    \ Ray<T>& ray) {\n    return distance(ray, point);\n}\n\ntemplate <Coordinate\
    \ T>\nRay<long double> reflection(const Line<T>& line, const Ray<T>& ray) {\n\
    \    assert(ray.origin != ray.through);\n    return Ray<long double>{\n      \
    \  reflection(line, ray.origin),\n        reflection(line, ray.through)\n    };\n\
    }\n\ntemplate <Coordinate T>\nRay<long double> reflected_ray(\n    const Ray<T>&\
    \ incoming,\n    const Point<T>& hit,\n    const Line<T>& mirror,\n    long double\
    \ eps = 1e-12L\n) {\n    assert(incoming.origin != incoming.through);\n    assert(on_line(mirror,\
    \ hit, eps));\n    Point<T> translated = hit + (incoming.through - incoming.origin);\n\
    \    return Ray<long double>{\n        Point<long double>(hit),\n        reflection(mirror,\
    \ translated)\n    };\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const\
    \ Ray<T>& ray,\n    const Line<T>& line,\n    long double eps = 1e-12L\n) {\n\
    \    assert(ray.origin != ray.through);\n    assert(line.a != line.b);\n    ray_detail::Parameters<T>\
    \ values = ray_detail::parameters(\n        ray.origin,\n        ray.through,\n\
    \        line.a,\n        line.b\n    );\n    if (sign<T>(values.denominator,\
    \ eps) == 0) {\n        return on_line(line, ray.origin, eps);\n    }\n    return\
    \ ray_detail::ratio_nonnegative<T>(\n        values.first_numerator,\n       \
    \ values.denominator,\n        eps\n    );\n}\n\ntemplate <Coordinate T>\nbool\
    \ intersects(\n    const Line<T>& line,\n    const Ray<T>& ray,\n    long double\
    \ eps = 1e-12L\n) {\n    return intersects(ray, line, eps);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Ray<T>& ray, const Line<T>& line) {\n    return\
    \ intersects(ray, line) ? 0 : distance(line, ray.origin);\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Line<T>& line, const Ray<T>& ray) {\n    return\
    \ distance(ray, line);\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const\
    \ Ray<T>& ray,\n    const Segment<T>& segment,\n    long double eps = 1e-12L\n\
    ) {\n    assert(ray.origin != ray.through);\n    if (segment.a == segment.b) return\
    \ on_ray(ray, segment.a, eps);\n\n    ray_detail::Parameters<T> values = ray_detail::parameters(\n\
    \        ray.origin,\n        ray.through,\n        segment.a,\n        segment.b\n\
    \    );\n    if (sign<T>(values.denominator, eps) == 0) {\n        if (orientation(ray.origin,\
    \ ray.through, segment.a, eps) != 0) {\n            return false;\n        }\n\
    \        return on_ray(ray, segment.a, eps) ||\n               on_ray(ray, segment.b,\
    \ eps) ||\n               on_segment(segment, ray.origin, eps);\n    }\n    return\
    \ ray_detail::ratio_nonnegative<T>(\n               values.first_numerator,\n\
    \               values.denominator,\n               eps\n           ) &&\n   \
    \        ray_detail::ratio_in_unit_interval<T>(\n               values.second_numerator,\n\
    \               values.denominator,\n               eps\n           );\n}\n\n\
    template <Coordinate T>\nbool intersects(\n    const Segment<T>& segment,\n  \
    \  const Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return intersects(ray,\
    \ segment, eps);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Ray<T>&\
    \ ray, const Segment<T>& segment) {\n    if (intersects(ray, segment)) return\
    \ 0;\n    return std::min({\n        distance(ray, segment.a),\n        distance(ray,\
    \ segment.b),\n        distance(segment, ray.origin)\n    });\n}\n\ntemplate <Coordinate\
    \ T>\nlong double distance(const Segment<T>& segment, const Ray<T>& ray) {\n \
    \   return distance(ray, segment);\n}\n\ntemplate <Coordinate T>\nbool intersects(\n\
    \    const Ray<T>& first,\n    const Ray<T>& second,\n    long double eps = 1e-12L\n\
    ) {\n    assert(first.origin != first.through);\n    assert(second.origin != second.through);\n\
    \    ray_detail::Parameters<T> values = ray_detail::parameters(\n        first.origin,\n\
    \        first.through,\n        second.origin,\n        second.through\n    );\n\
    \    if (sign<T>(values.denominator, eps) == 0) {\n        if (orientation(first.origin,\
    \ first.through, second.origin, eps) != 0) {\n            return false;\n    \
    \    }\n        return on_ray(first, second.origin, eps) ||\n               on_ray(second,\
    \ first.origin, eps);\n    }\n    return ray_detail::ratio_nonnegative<T>(\n \
    \              values.first_numerator,\n               values.denominator,\n \
    \              eps\n           ) &&\n           ray_detail::ratio_nonnegative<T>(\n\
    \               values.second_numerator,\n               values.denominator,\n\
    \               eps\n           );\n}\n\ntemplate <Coordinate T>\nlong double\
    \ distance(const Ray<T>& first, const Ray<T>& second) {\n    if (intersects(first,\
    \ second)) return 0;\n    return std::min(\n        distance(first, second.origin),\n\
    \        distance(second, first.origin)\n    );\n}\n\ntemplate <Coordinate T>\n\
    std::optional<Point<long double>> ray_line_intersection(\n    const Ray<T>& ray,\n\
    \    const Line<T>& line,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin\
    \ != ray.through);\n    assert(line.a != line.b);\n    ray_detail::Parameters<T>\
    \ values = ray_detail::parameters(\n        ray.origin,\n        ray.through,\n\
    \        line.a,\n        line.b\n    );\n    if (\n        sign<T>(values.denominator,\
    \ eps) == 0 ||\n        !ray_detail::ratio_nonnegative<T>(\n            values.first_numerator,\n\
    \            values.denominator,\n            eps\n        )\n    ) {\n      \
    \  return std::nullopt;\n    }\n    return ray_detail::point_at(\n        ray,\n\
    \        values.first_numerator,\n        values.denominator\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> ray_line_intersection(\n \
    \   const Line<T>& line,\n    const Ray<T>& ray,\n    long double eps = 1e-12L\n\
    ) {\n    return ray_line_intersection(ray, line, eps);\n}\n\ntemplate <Coordinate\
    \ T>\nstd::optional<Point<long double>> ray_segment_intersection(\n    const Ray<T>&\
    \ ray,\n    const Segment<T>& segment,\n    long double eps = 1e-12L\n) {\n  \
    \  assert(ray.origin != ray.through);\n    if (segment.a == segment.b) {\n   \
    \     if (on_ray(ray, segment.a, eps)) {\n            return Point<long double>(segment.a);\n\
    \        }\n        return std::nullopt;\n    }\n\n    ray_detail::Parameters<T>\
    \ values = ray_detail::parameters(\n        ray.origin,\n        ray.through,\n\
    \        segment.a,\n        segment.b\n    );\n    if (sign<T>(values.denominator,\
    \ eps) == 0) {\n        if (orientation(ray.origin, ray.through, segment.a, eps)\
    \ != 0) {\n            return std::nullopt;\n        }\n        if (\n       \
    \     segment.a == ray.origin &&\n            !on_ray(ray, segment.b, eps)\n \
    \       ) {\n            return Point<long double>(ray.origin);\n        }\n \
    \       if (\n            segment.b == ray.origin &&\n            !on_ray(ray,\
    \ segment.a, eps)\n        ) {\n            return Point<long double>(ray.origin);\n\
    \        }\n        return std::nullopt;\n    }\n    if (\n        !ray_detail::ratio_nonnegative<T>(\n\
    \            values.first_numerator,\n            values.denominator,\n      \
    \      eps\n        ) ||\n        !ray_detail::ratio_in_unit_interval<T>(\n  \
    \          values.second_numerator,\n            values.denominator,\n       \
    \     eps\n        )\n    ) {\n        return std::nullopt;\n    }\n    return\
    \ ray_detail::point_at(\n        ray,\n        values.first_numerator,\n     \
    \   values.denominator\n    );\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long\
    \ double>> ray_segment_intersection(\n    const Segment<T>& segment,\n    const\
    \ Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return ray_segment_intersection(ray,\
    \ segment, eps);\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long double>>\
    \ ray_intersection(\n    const Ray<T>& first,\n    const Ray<T>& second,\n   \
    \ long double eps = 1e-12L\n) {\n    assert(first.origin != first.through);\n\
    \    assert(second.origin != second.through);\n    ray_detail::Parameters<T> values\
    \ = ray_detail::parameters(\n        first.origin,\n        first.through,\n \
    \       second.origin,\n        second.through\n    );\n    if (sign<T>(values.denominator,\
    \ eps) == 0) {\n        if (\n            first.origin != second.origin ||\n \
    \           orientation(\n                first.origin,\n                first.through,\n\
    \                second.through,\n                eps\n            ) != 0\n  \
    \      ) {\n            return std::nullopt;\n        }\n        using W = wide_type<T>;\n\
    \        W first_x = W(first.through.x) - W(first.origin.x);\n        W first_y\
    \ = W(first.through.y) - W(first.origin.y);\n        W second_x = W(second.through.x)\
    \ - W(second.origin.x);\n        W second_y = W(second.through.y) - W(second.origin.y);\n\
    \        if (sign<T>(first_x * second_x + first_y * second_y, eps) < 0) {\n  \
    \          return Point<long double>(first.origin);\n        }\n        return\
    \ std::nullopt;\n    }\n    if (\n        !ray_detail::ratio_nonnegative<T>(\n\
    \            values.first_numerator,\n            values.denominator,\n      \
    \      eps\n        ) ||\n        !ray_detail::ratio_nonnegative<T>(\n       \
    \     values.second_numerator,\n            values.denominator,\n            eps\n\
    \        )\n    ) {\n        return std::nullopt;\n    }\n    return ray_detail::point_at(\n\
    \        first,\n        values.first_numerator,\n        values.denominator\n\
    \    );\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 14 \"\
    geometry/polygon.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\nenum class\
    \ PointInPolygon {\n    Outside = 0,\n    Boundary = 1,\n    Inside = 2,\n};\n\
    \ntemplate <Coordinate T>\nconstexpr Point<long double> centroid(\n    const std::array<Point<T>,\
    \ 3>& triangle\n) {\n    return Point<long double>(\n        (\n            static_cast<long\
    \ double>(triangle[0].x) +\n            static_cast<long double>(triangle[1].x)\
    \ +\n            static_cast<long double>(triangle[2].x)\n        ) / 3,\n   \
    \     (\n            static_cast<long double>(triangle[0].y) +\n            static_cast<long\
    \ double>(triangle[1].y) +\n            static_cast<long double>(triangle[2].y)\n\
    \        ) / 3\n    );\n}\n\nnamespace polygon_detail {\n\ninline bool close(\n\
    \    const Point<long double>& first,\n    const Point<long double>& second,\n\
    \    long double eps\n) {\n    return geometry::distance(first, second) <= eps;\n\
    }\n\ninline void push_unique(\n    std::vector<Point<long double>>& points,\n\
    \    const Point<long double>& point,\n    long double eps\n) {\n    for (const\
    \ Point<long double>& existing : points) {\n        if (close(existing, point,\
    \ eps)) return;\n    }\n    points.push_back(point);\n}\n\ntemplate <Coordinate\
    \ T>\nstd::vector<Point<T>> clean_polygon_vertices(\n    std::vector<Point<T>>\
    \ polygon,\n    long double eps\n) {\n    if (\n        polygon.size() >= 2 &&\n\
    \        polygon.front() == polygon.back()\n    ) {\n        polygon.pop_back();\n\
    \    }\n\n    std::vector<Point<T>> deduplicated;\n    for (const Point<T>& point\
    \ : polygon) {\n        if (deduplicated.empty() || deduplicated.back() != point)\
    \ {\n            deduplicated.push_back(point);\n        }\n    }\n    if (\n\
    \        deduplicated.size() >= 2 &&\n        deduplicated.front() == deduplicated.back()\n\
    \    ) {\n        deduplicated.pop_back();\n    }\n\n    bool changed = true;\n\
    \    while (changed && deduplicated.size() >= 3) {\n        changed = false;\n\
    \        std::vector<Point<T>> cleaned;\n        std::size_t size = deduplicated.size();\n\
    \        for (std::size_t index = 0; index < size; ++index) {\n            const\
    \ Point<T>& previous =\n                deduplicated[(index + size - 1) % size];\n\
    \            const Point<T>& current = deduplicated[index];\n            const\
    \ Point<T>& next =\n                deduplicated[(index + 1) % size];\n      \
    \      if (\n                orientation(previous, current, next, eps) == 0 &&\n\
    \                sign<T>(dot(current - previous, next - current), eps) >= 0\n\
    \            ) {\n                changed = true;\n            } else {\n    \
    \            cleaned.push_back(current);\n            }\n        }\n        deduplicated\
    \ = std::move(cleaned);\n    }\n    return deduplicated;\n}\n\ntemplate <Coordinate\
    \ T>\nbool in_ccw_triangle(\n    const Point<T>& point,\n    const Point<T>& first,\n\
    \    const Point<T>& second,\n    const Point<T>& third,\n    long double eps\n\
    ) {\n    return\n        orientation(first, second, point, eps) >= 0 &&\n    \
    \    orientation(second, third, point, eps) >= 0 &&\n        orientation(third,\
    \ first, point, eps) >= 0;\n}\n\n}  // namespace polygon_detail\n\ntemplate <Coordinate\
    \ T>\nwide_type<T> polygon_area2(const std::vector<Point<T>>& polygon) {\n   \
    \ wide_type<T> result = 0;\n    std::size_t n = polygon.size();\n    for (std::size_t\
    \ i = 0; i < n; i++) {\n        result += cross(polygon[i], polygon[(i + 1) %\
    \ n]);\n    }\n    return result;\n}\n\ntemplate <Coordinate T>\nlong double polygon_area(const\
    \ std::vector<Point<T>>& polygon) {\n    return std::fabs(static_cast<long double>(polygon_area2(polygon)))\
    \ / 2;\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long double>> polygon_centroid(\n\
    \    const std::vector<Point<T>>& polygon,\n    long double eps = 1e-12L\n) {\n\
    \    if (polygon.size() < 3) return std::nullopt;\n\n    wide_type<T> signed_area2\
    \ = polygon_area2(polygon);\n    if (sign<T>(signed_area2, eps) == 0) return std::nullopt;\n\
    \n    long double x_numerator = 0;\n    long double y_numerator = 0;\n    std::size_t\
    \ size = polygon.size();\n    for (std::size_t index = 0; index < size; ++index)\
    \ {\n        const Point<T>& current = polygon[index];\n        const Point<T>&\
    \ next = polygon[(index + 1) % size];\n        long double weight = static_cast<long\
    \ double>(cross(current, next));\n        x_numerator +=\n            (static_cast<long\
    \ double>(current.x) +\n             static_cast<long double>(next.x)) *\n   \
    \         weight;\n        y_numerator +=\n            (static_cast<long double>(current.y)\
    \ +\n             static_cast<long double>(next.y)) *\n            weight;\n \
    \   }\n    long double denominator =\n        3.0L * static_cast<long double>(signed_area2);\n\
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
    \ : PointInPolygon::Outside;\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<long\
    \ double>> ray_polygon_intersections(\n    const Ray<T>& ray,\n    const std::vector<Point<T>>&\
    \ polygon,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin != ray.through);\n\
    \    assert(polygon.size() >= 3);\n    std::vector<Point<long double>> result;\n\
    \    std::size_t size = polygon.size();\n    for (std::size_t index = 0; index\
    \ < size; ++index) {\n        Segment<T> edge{\n            polygon[index],\n\
    \            polygon[(index + 1) % size]\n        };\n        std::optional<Point<long\
    \ double>> point =\n            ray_segment_intersection(ray, edge, eps);\n  \
    \      if (point.has_value()) {\n            polygon_detail::push_unique(result,\
    \ *point, eps);\n            continue;\n        }\n        if (\n            orientation(ray.origin,\
    \ ray.through, edge.a, eps) == 0 &&\n            orientation(ray.origin, ray.through,\
    \ edge.b, eps) == 0\n        ) {\n            if (on_ray(ray, edge.a, eps)) {\n\
    \                polygon_detail::push_unique(\n                    result,\n \
    \                   Point<long double>(edge.a),\n                    eps\n   \
    \             );\n            }\n            if (on_ray(ray, edge.b, eps)) {\n\
    \                polygon_detail::push_unique(\n                    result,\n \
    \                   Point<long double>(edge.b),\n                    eps\n   \
    \             );\n            }\n            if (on_segment(edge, ray.origin,\
    \ eps)) {\n                polygon_detail::push_unique(\n                    result,\n\
    \                    Point<long double>(ray.origin),\n                    eps\n\
    \                );\n            }\n        }\n    }\n\n    Point<long double>\
    \ origin(ray.origin);\n    Point<long double> direction =\n        Point<long\
    \ double>(ray.through) - origin;\n    std::sort(\n        result.begin(),\n  \
    \      result.end(),\n        [&](const Point<long double>& first, const Point<long\
    \ double>& second) {\n            return dot(first - origin, direction) <\n  \
    \                 dot(second - origin, direction);\n        }\n    );\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nstd::optional<Point<long double>> first_ray_polygon_intersection(\n\
    \    const Ray<T>& ray,\n    const std::vector<Point<T>>& polygon,\n    long double\
    \ eps = 1e-12L\n) {\n    std::vector<Point<long double>> points =\n        ray_polygon_intersections(ray,\
    \ polygon, eps);\n    if (points.empty()) return std::nullopt;\n    return points.front();\n\
    }\n\ntemplate <Coordinate T>\nbool intersects(\n    const Ray<T>& ray,\n    const\
    \ std::vector<Point<T>>& polygon,\n    long double eps = 1e-12L\n) {\n    assert(polygon.size()\
    \ >= 3);\n    if (point_in_polygon(polygon, ray.origin, eps) != PointInPolygon::Outside)\
    \ {\n        return true;\n    }\n    return !ray_polygon_intersections(ray, polygon,\
    \ eps).empty();\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const std::vector<Point<T>>&\
    \ polygon,\n    const Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return\
    \ intersects(ray, polygon, eps);\n}\n\ntemplate <Coordinate T>\nlong double distance(\n\
    \    const Ray<T>& ray,\n    const std::vector<Point<T>>& polygon\n) {\n    assert(polygon.size()\
    \ >= 3);\n    if (intersects(ray, polygon)) return 0;\n    long double result\
    \ = std::numeric_limits<long double>::infinity();\n    std::size_t size = polygon.size();\n\
    \    for (std::size_t index = 0; index < size; ++index) {\n        result = std::min(\n\
    \            result,\n            distance(\n                ray,\n          \
    \      Segment<T>{\n                    polygon[index],\n                    polygon[(index\
    \ + 1) % size]\n                }\n            )\n        );\n    }\n    return\
    \ result;\n}\n\ntemplate <Coordinate T>\nlong double distance(\n    const std::vector<Point<T>>&\
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
    \ second_edge));\n        }\n    }\n    return result;\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n#line 21 \"geometry/convex_polygon.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\nnamespace convex_polygon_detail {\n\ninline\
    \ std::vector<Point<long double>> clean_polygon(\n    std::vector<Point<long double>>\
    \ polygon,\n    long double eps\n) {\n    if (polygon.empty()) return polygon;\n\
    \n    std::vector<Point<long double>> deduplicated;\n    for (const Point<long\
    \ double>& point : polygon) {\n        if (\n            deduplicated.empty()\
    \ ||\n            !polygon_detail::close(deduplicated.back(), point, eps)\n  \
    \      ) {\n            deduplicated.push_back(point);\n        }\n    }\n   \
    \ if (\n        deduplicated.size() >= 2 &&\n        polygon_detail::close(\n\
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
    \ <Coordinate T>\nstd::pair<Point<long double>, Point<long double>>\nclosest_points_from_difference(\n\
    \    const MinkowskiDifferenceView<T>& difference,\n    long double eps\n) {\n\
    \    const OriginLocation location = locate_origin<T>(difference, eps);\n    if\
    \ (location.location == PointInPolygon::Outside) {\n        const ClosestBoundaryFeature\
    \ feature =\n            closest_boundary_feature<T>(difference, location, eps);\n\
    \        const auto first_components = difference.components(feature.first);\n\
    \        const auto second_components = difference.components(feature.second);\n\
    \        return std::pair<Point<long double>, Point<long double>>(\n         \
    \   interpolate(\n                Point<long double>(first_components.first),\n\
    \                Point<long double>(second_components.first),\n              \
    \  feature.ratio\n            ),\n            interpolate(\n                Point<long\
    \ double>(first_components.second),\n                Point<long double>(second_components.second),\n\
    \                feature.ratio\n            )\n        );\n    }\n\n    assert(location.simplex_size\
    \ == 2 || location.simplex_size == 3);\n    std::array<long double, 3> weight{0,\
    \ 0, 0};\n    if (location.simplex_size == 2) {\n        const Point<long double>\
    \ first(difference[location.simplex[0]]);\n        const Point<long double> second(difference[location.simplex[1]]);\n\
    \        const Point<long double> direction = second - first;\n        weight[1]\
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
    \ std::pair<Point<long double>, Point<long double>>(\n        first_result,\n\
    \        second_result\n    );\n}\n\ntemplate <Coordinate T>\nPoint<long double>\
    \ closest_point_on_segment(\n    const Segment<T>& segment,\n    const Point<T>&\
    \ point\n) {\n    const Point<long double> first(segment.a);\n    const Point<long\
    \ double> direction =\n        Point<long double>(segment.b) - first;\n    const\
    \ long double length2 = dot(direction, direction);\n    if (length2 == 0) return\
    \ first;\n    const long double ratio = std::clamp(\n        dot(Point<long double>(point)\
    \ - first, direction) / length2,\n        0.0L,\n        1.0L\n    );\n    return\
    \ first + direction * ratio;\n}\n\ntemplate <Coordinate T>\nstd::pair<Point<long\
    \ double>, Point<long double>>\nclosest_points_between_segments(\n    const Segment<T>&\
    \ first,\n    const Segment<T>& second,\n    long double eps\n) {\n    if (intersects(first,\
    \ second, eps)) {\n        for (const Point<T>& point : {first.a, first.b}) {\n\
    \            if (on_segment(second, point, eps)) {\n                const Point<long\
    \ double> common(point);\n                return std::pair<Point<long double>,\
    \ Point<long double>>(\n                    common,\n                    common\n\
    \                );\n            }\n        }\n        for (const Point<T>& point\
    \ : {second.a, second.b}) {\n            if (on_segment(first, point, eps)) {\n\
    \                const Point<long double> common(point);\n                return\
    \ std::pair<Point<long double>, Point<long double>>(\n                    common,\n\
    \                    common\n                );\n            }\n        }\n  \
    \      const auto common = line_intersection(\n            Line<T>{first.a, first.b},\n\
    \            Line<T>{second.a, second.b},\n            eps\n        );\n     \
    \   assert(common.has_value());\n        return std::pair<Point<long double>,\
    \ Point<long double>>(\n            *common,\n            *common\n        );\n\
    \    }\n\n    std::pair<Point<long double>, Point<long double>> result(\n    \
    \    Point<long double>(first.a),\n        closest_point_on_segment(second, first.a)\n\
    \    );\n    long double result_distance = distance(result.first, result.second);\n\
    \    auto consider = [&](const Point<long double>& first_point,\n            \
    \            const Point<long double>& second_point) {\n        const long double\
    \ candidate_distance =\n            distance(first_point, second_point);\n   \
    \     if (candidate_distance < result_distance) {\n            result = std::pair<Point<long\
    \ double>, Point<long double>>(\n                first_point,\n              \
    \  second_point\n            );\n            result_distance = candidate_distance;\n\
    \        }\n    };\n    consider(\n        Point<long double>(first.b),\n    \
    \    closest_point_on_segment(second, first.b)\n    );\n    consider(\n      \
    \  closest_point_on_segment(first, second.a),\n        Point<long double>(second.a)\n\
    \    );\n    consider(\n        closest_point_on_segment(first, second.b),\n \
    \       Point<long double>(second.b)\n    );\n    return result;\n}\n\n}  // namespace\
    \ convex_polygon_detail\n\ntemplate <Coordinate T>\nstd::vector<std::array<Point<T>,\
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
    \ current};\n            const std::optional<Point<long double>> intersection\
    \ =\n                line_intersection(line, crossing, eps);\n            if (intersection.has_value())\
    \ result.push_back(*intersection);\n        }\n        if (current_inside) result.push_back(current);\n\
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
    }\n\ntemplate <Coordinate T>\nstd::pair<Point<long double>, Point<long double>>\n\
    convex_polygons_closest_points(\n    const ConvexPolygon<T>& first,\n    const\
    \ ConvexPolygon<T>& second,\n    long double eps = 1e-12L\n) {\n    assert(!first.empty());\n\
    \    assert(!second.empty());\n    if (first.size() <= 2 && second.size() <= 2)\
    \ {\n        return convex_polygon_detail::closest_points_between_segments(\n\
    \            Segment<T>{first[0], first[first.size() - 1]},\n            Segment<T>{second[0],\
    \ second[second.size() - 1]},\n            eps\n        );\n    }\n    const convex_polygon_detail::MinkowskiDifferenceView<T>\
    \ difference(\n        first,\n        second\n    );\n    return convex_polygon_detail::closest_points_from_difference(\n\
    \        difference,\n        eps\n    );\n}\n\ntemplate <Coordinate T>\nstd::pair<Point<long\
    \ double>, Point<long double>>\nconvex_polygons_closest_points(\n    const std::vector<Point<T>>&\
    \ first,\n    const std::vector<Point<T>>& second,\n    long double eps = 1e-12L\n\
    ) {\n    assert(!first.empty());\n    assert(!second.empty());\n    const ConvexPolygon<T>\
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
    \ result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 5 \"\
    verify/geometry/polygon_operations.test.cpp\"\n\n#line 10 \"verify/geometry/polygon_operations.test.cpp\"\
    \n#include <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 6 \"utilities/fast_io.hpp\"\
    \n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\n\
    #include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include\
    \ <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n#line\
    \ 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\nnamespace\
    \ utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
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
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 13 \"verify/geometry/polygon_operations.test.cpp\"\
    \n\nnamespace {\n\nusing namespace m1une::geometry;\nusing P = Point<long long>;\n\
    \nbool close(long double first, long double second) {\n    return std::fabs(first\
    \ - second) <= 1e-9L;\n}\n\nstd::vector<P> square(\n    long long left,\n    long\
    \ long bottom,\n    long long right,\n    long long top\n) {\n    std::vector<P>\
    \ result;\n    result.emplace_back(left, bottom);\n    result.emplace_back(right,\
    \ bottom);\n    result.emplace_back(right, top);\n    result.emplace_back(left,\
    \ top);\n    return result;\n}\n\ntemplate <typename T>\nstd::vector<Point<long\
    \ double>> clipping_intersection(\n    std::vector<Point<T>> first,\n    std::vector<Point<T>>\
    \ second\n) {\n    first = normalize_convex_polygon(std::move(first));\n    second\
    \ = normalize_convex_polygon(std::move(second));\n    std::vector<Point<long double>>\
    \ result;\n    result.reserve(first.size());\n    for (const Point<T>& point :\
    \ first) result.emplace_back(point);\n    for (std::size_t index = 0; index <\
    \ second.size(); ++index) {\n        const Line<T> boundary{\n            second[index],\n\
    \            second[(index + 1) % second.size()]\n        };\n        result =\
    \ convex_cut(result, Line<long double>{\n            Point<long double>(boundary.a),\n\
    \            Point<long double>(boundary.b)\n        });\n        if (result.empty())\
    \ break;\n    }\n    return result;\n}\n\ntemplate <typename T>\nPointInPolygon\
    \ contains_closed(\n    const std::vector<Point<T>>& polygon,\n    const Point<T>&\
    \ point\n) {\n    if (polygon.empty()) return PointInPolygon::Outside;\n    if\
    \ (polygon.size() == 1) {\n        return distance(polygon[0], point) <= 1e-8L\n\
    \            ? PointInPolygon::Boundary\n            : PointInPolygon::Outside;\n\
    \    }\n    if (polygon.size() == 2) {\n        return on_segment(Segment<T>{polygon[0],\
    \ polygon[1]}, point, 1e-8L)\n            ? PointInPolygon::Boundary\n       \
    \     : PointInPolygon::Outside;\n    }\n    return point_in_polygon(polygon,\
    \ point, 1e-8L);\n}\n\nvoid assert_same_closed_polygon(\n    const std::vector<Point<long\
    \ double>>& first,\n    const std::vector<Point<long double>>& second\n) {\n \
    \   assert(first.empty() == second.empty());\n    assert(close(polygon_area(first),\
    \ polygon_area(second)));\n    for (const auto& point : first) {\n        assert(contains_closed(second,\
    \ point) != PointInPolygon::Outside);\n    }\n    for (const auto& point : second)\
    \ {\n        assert(contains_closed(first, point) != PointInPolygon::Outside);\n\
    \    }\n}\n\ntemplate <typename T>\nlong double triangle_area(\n    const std::array<Point<T>,\
    \ 3>& triangle\n) {\n    return std::fabs(\n        static_cast<long double>(\n\
    \            cross(triangle[0], triangle[1], triangle[2])\n        )\n    ) /\
    \ 2;\n}\n\nvoid test_centroid_and_triangulation() {\n    std::vector<P> rectangle\
    \ = square(0, 0, 4, 2);\n    auto rectangle_centroid = polygon_centroid(rectangle);\n\
    \    assert(rectangle_centroid.has_value());\n    assert(close(rectangle_centroid->x,\
    \ 2));\n    assert(close(rectangle_centroid->y, 1));\n    auto same_centroid =\
    \ polygon_center_of_gravity(rectangle);\n    assert(same_centroid.has_value());\n\
    \    assert(close(same_centroid->x, 2));\n    assert(close(same_centroid->y, 1));\n\
    \n    std::vector<P> concave;\n    concave.emplace_back(0, 0);\n    concave.emplace_back(5,\
    \ 0);\n    concave.emplace_back(5, 1);\n    concave.emplace_back(1, 1);\n    concave.emplace_back(1,\
    \ 5);\n    concave.emplace_back(0, 5);\n    assert(is_simple_polygon(concave));\n\
    \n    auto centroid = polygon_centroid(concave);\n    assert(centroid.has_value());\n\
    \    assert(close(centroid->x, 14.5L / 9));\n    assert(close(centroid->y, 14.5L\
    \ / 9));\n\n    auto triangulation = triangulate_polygon(concave);\n    assert(triangulation.has_value());\n\
    \    assert(triangulation->size() == 4);\n    long double area_sum = 0;\n    for\
    \ (const auto& triangle : *triangulation) {\n        assert(orientation(triangle[0],\
    \ triangle[1], triangle[2]) > 0);\n        area_sum += triangle_area(triangle);\n\
    \    }\n    assert(close(area_sum, polygon_area(concave)));\n\n    std::reverse(concave.begin(),\
    \ concave.end());\n    auto clockwise = triangulate_polygon(concave);\n    assert(clockwise.has_value());\n\
    \    assert(clockwise->size() == 4);\n\n    std::vector<P> redundant;\n    redundant.emplace_back(0,\
    \ 0);\n    redundant.emplace_back(2, 0);\n    redundant.emplace_back(4, 0);\n\
    \    redundant.emplace_back(4, 3);\n    redundant.emplace_back(0, 3);\n    redundant.emplace_back(0,\
    \ 0);\n    auto cleaned = triangulate_polygon(redundant);\n    assert(cleaned.has_value());\n\
    \    assert(cleaned->size() == 2);\n\n    auto convex = triangulate_convex_polygon(rectangle);\n\
    \    assert(convex.size() == 2);\n\n    std::vector<P> bow_tie;\n    bow_tie.emplace_back(0,\
    \ 0);\n    bow_tie.emplace_back(3, 3);\n    bow_tie.emplace_back(0, 3);\n    bow_tie.emplace_back(3,\
    \ 0);\n    assert(!is_simple_polygon(bow_tie));\n    assert(!triangulate_polygon(bow_tie).has_value());\n\
    \n    std::vector<P> backtracking;\n    backtracking.emplace_back(0, 0);\n   \
    \ backtracking.emplace_back(4, 0);\n    backtracking.emplace_back(2, 0);\n   \
    \ backtracking.emplace_back(2, 3);\n    backtracking.emplace_back(0, 3);\n   \
    \ assert(!is_simple_polygon(backtracking));\n    assert(!triangulate_polygon(backtracking).has_value());\n\
    \n    std::vector<P> zero_area;\n    zero_area.emplace_back(0, 0);\n    zero_area.emplace_back(1,\
    \ 0);\n    zero_area.emplace_back(2, 0);\n    assert(!polygon_centroid(zero_area).has_value());\n\
    \    assert(!triangulate_polygon(zero_area).has_value());\n}\n\nvoid test_reflection()\
    \ {\n    Line<long long> mirror;\n    mirror.a = P(-10, 0);\n    mirror.b = P(10,\
    \ 0);\n\n    Ray<long long> incoming;\n    incoming.origin = P(-2, 3);\n    incoming.through\
    \ = P(0, 0);\n    Ray<long double> outgoing =\n        reflected_ray(incoming,\
    \ P(0, 0), mirror);\n    assert(close(outgoing.origin.x, 0));\n    assert(close(outgoing.origin.y,\
    \ 0));\n    assert(close(outgoing.through.x, 2));\n    assert(close(outgoing.through.y,\
    \ 3));\n\n    Ray<long double> mirrored = reflection(mirror, incoming);\n    assert(close(mirrored.origin.x,\
    \ -2));\n    assert(close(mirrored.origin.y, -3));\n    assert(close(mirrored.through.x,\
    \ 0));\n    assert(close(mirrored.through.y, 0));\n}\n\nvoid test_ray_polygon()\
    \ {\n    std::vector<P> polygon = square(0, 0, 4, 4);\n    Ray<long long> crossing;\n\
    \    crossing.origin = P(-2, 2);\n    crossing.through = P(-1, 2);\n    auto hits\
    \ = ray_polygon_intersections(crossing, polygon);\n    assert(hits.size() == 2);\n\
    \    assert(close(hits[0].x, 0));\n    assert(close(hits[1].x, 4));\n    assert(intersects(crossing,\
    \ polygon));\n    assert(close(distance(crossing, polygon), 0));\n\n    Ray<long\
    \ long> inside;\n    inside.origin = P(2, 2);\n    inside.through = P(3, 2);\n\
    \    auto first = first_ray_polygon_intersection(inside, polygon);\n    assert(first.has_value());\n\
    \    assert(close(first->x, 4));\n    assert(intersects(inside, polygon));\n\n\
    \    Ray<long long> collinear;\n    collinear.origin = P(-2, 0);\n    collinear.through\
    \ = P(-1, 0);\n    auto boundary = ray_polygon_intersections(collinear, polygon);\n\
    \    assert(boundary.size() == 2);\n    assert(close(boundary[0].x, 0));\n   \
    \ assert(close(boundary[1].x, 4));\n\n    Ray<long long> through_vertices;\n \
    \   through_vertices.origin = P(-1, -1);\n    through_vertices.through = P(0,\
    \ 0);\n    auto vertex_hits =\n        ray_polygon_intersections(through_vertices,\
    \ polygon);\n    assert(vertex_hits.size() == 2);\n    assert(close(vertex_hits[0].x,\
    \ 0));\n    assert(close(vertex_hits[1].x, 4));\n\n    Ray<long long> missing;\n\
    \    missing.origin = P(-2, 7);\n    missing.through = P(-1, 7);\n    assert(!intersects(missing,\
    \ polygon));\n    assert(close(distance(missing, polygon), 3));\n}\n\nvoid test_polygon_polygon()\
    \ {\n    std::vector<P> first = square(0, 0, 4, 4);\n    std::vector<P> overlap\
    \ = square(2, 1, 6, 3);\n    std::vector<P> contained = square(1, 1, 2, 2);\n\
    \    std::vector<P> touching = square(4, 1, 7, 2);\n    std::vector<P> separate\
    \ = square(7, 0, 9, 2);\n\n    assert(intersects(first, overlap));\n    assert(intersects(first,\
    \ contained));\n    assert(intersects(first, touching));\n    assert(!intersects(first,\
    \ separate));\n    assert(close(distance(first, separate), 3));\n\n    std::vector<P>\
    \ concave;\n    concave.emplace_back(0, 0);\n    concave.emplace_back(5, 0);\n\
    \    concave.emplace_back(5, 1);\n    concave.emplace_back(1, 1);\n    concave.emplace_back(1,\
    \ 5);\n    concave.emplace_back(0, 5);\n    std::vector<P> in_arm = square(0,\
    \ 3, 1, 4);\n    std::vector<P> in_notch = square(2, 2, 3, 3);\n    assert(intersects(concave,\
    \ in_arm));\n    assert(!intersects(concave, in_notch));\n    assert(close(distance(concave,\
    \ in_notch), 1));\n\n    auto clipped = convex_polygon_intersection(first, overlap);\n\
    \    assert(clipped.size() == 4);\n    assert(close(polygon_area(clipped), 4));\n\
    \    std::reverse(first.begin(), first.end());\n    auto clockwise_clip = convex_polygon_intersection(first,\
    \ overlap);\n    assert(close(polygon_area(clockwise_clip), 4));\n    assert(polygon_area2(clockwise_clip)\
    \ > 0);\n    std::reverse(first.begin(), first.end());\n\n    auto contained_clip\
    \ = convex_polygon_intersection(first, contained);\n    assert(close(polygon_area(contained_clip),\
    \ 1));\n\n    auto touching_clip = convex_polygon_intersection(first, touching);\n\
    \    assert(touching_clip.size() == 2);\n    assert(close(polygon_area(touching_clip),\
    \ 0));\n\n    auto empty_clip = convex_polygon_intersection(first, separate);\n\
    \    assert(empty_clip.empty());\n\n    std::vector<P> corner_touching = square(4,\
    \ 4, 7, 7);\n    auto corner_clip = convex_polygon_intersection(first, corner_touching);\n\
    \    assert(corner_clip.size() == 1);\n    assert(close(corner_clip[0].x, 4));\n\
    \    assert(close(corner_clip[0].y, 4));\n}\n\nvoid test_minkowski_examples()\
    \ {\n    std::vector<P> first = square(0, 0, 2, 2);\n    std::vector<P> second;\n\
    \    second.emplace_back(0, 0);\n    second.emplace_back(2, 0);\n    second.emplace_back(0,\
    \ 1);\n\n    std::vector<P> sum = minkowski_sum(first, second);\n    std::vector<P>\
    \ brute;\n    for (const P& a : first) {\n        for (const P& b : second) brute.push_back(a\
    \ + b);\n    }\n    assert(convex_hull(sum) == convex_hull(brute));\n\n    std::reverse(first.begin(),\
    \ first.end());\n    std::reverse(second.begin(), second.end());\n    assert(\n\
    \        convex_hull(minkowski_sum(first, second)) ==\n        convex_hull(brute)\n\
    \    );\n\n    std::vector<P> segment;\n    segment.emplace_back(0, 0);\n    segment.emplace_back(3,\
    \ 0);\n    std::vector<P> point;\n    point.emplace_back(2, 4);\n    std::vector<P>\
    \ translated = minkowski_sum(segment, point);\n    std::vector<P> expected;\n\
    \    expected.emplace_back(2, 4);\n    expected.emplace_back(5, 4);\n    assert(translated\
    \ == expected);\n\n    std::vector<P> diagonal_segment;\n    diagonal_segment.emplace_back(2,\
    \ -1);\n    diagonal_segment.emplace_back(-1, 2);\n    std::vector<P> segment_sum\
    \ = minkowski_sum(diagonal_segment, first);\n    brute.clear();\n    for (const\
    \ P& a : diagonal_segment) {\n        for (const P& b : first) brute.push_back(a\
    \ + b);\n    }\n    assert(convex_hull(segment_sum) == convex_hull(brute));\n\
    }\n\nvoid test_randomized_minkowski_and_clipping() {\n    std::uint64_t state\
    \ = 0x314159265358979ULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for\
    \ (int trial = 0; trial < 5000; ++trial) {\n        std::vector<P> first_points;\n\
    \        std::vector<P> second_points;\n        int first_count = 3 + static_cast<int>(random()\
    \ % 8);\n        int second_count = 3 + static_cast<int>(random() % 8);\n    \
    \    for (int index = 0; index < first_count; ++index) {\n            first_points.emplace_back(\n\
    \                static_cast<long long>(random() % 21) - 10,\n               \
    \ static_cast<long long>(random() % 21) - 10\n            );\n        }\n    \
    \    for (int index = 0; index < second_count; ++index) {\n            second_points.emplace_back(\n\
    \                static_cast<long long>(random() % 21) - 10,\n               \
    \ static_cast<long long>(random() % 21) - 10\n            );\n        }\n    \
    \    std::vector<P> first = convex_hull(first_points);\n        std::vector<P>\
    \ second = convex_hull(second_points);\n        if (first.size() < 3 || second.size()\
    \ < 3) continue;\n        const P translation(\n            static_cast<long long>(random()\
    \ % 41) - 20,\n            static_cast<long long>(random() % 41) - 20\n      \
    \  );\n        for (P& point : second) point += translation;\n\n        auto ear_triangles\
    \ = triangulate_polygon(first);\n        assert(ear_triangles.has_value());\n\
    \        auto fan_triangles = triangulate_convex_polygon(first);\n        assert(ear_triangles->size()\
    \ == first.size() - 2);\n        assert(fan_triangles.size() == first.size() -\
    \ 2);\n        long double ear_area = 0;\n        long double fan_area = 0;\n\
    \        for (const auto& triangle : *ear_triangles) {\n            ear_area +=\
    \ triangle_area(triangle);\n        }\n        for (const auto& triangle : fan_triangles)\
    \ {\n            fan_area += triangle_area(triangle);\n        }\n        assert(close(ear_area,\
    \ polygon_area(first)));\n        assert(close(fan_area, polygon_area(first)));\n\
    \n        std::vector<P> brute_sums;\n        for (const P& a : first) {\n   \
    \         for (const P& b : second) brute_sums.push_back(a + b);\n        }\n\
    \        assert(\n            convex_hull(minkowski_sum(first, second)) ==\n \
    \           convex_hull(brute_sums)\n        );\n\n        auto forward = convex_polygon_intersection(first,\
    \ second);\n        auto backward = convex_polygon_intersection(second, first);\n\
    \        assert(close(polygon_area(forward), polygon_area(backward)));\n     \
    \   assert_same_closed_polygon(\n            forward,\n            clipping_intersection(first,\
    \ second)\n        );\n        for (const Point<long double>& point : forward)\
    \ {\n            assert(\n                point_in_polygon(\n                \
    \    std::vector<Point<long double>>(\n                        first.begin(),\n\
    \                        first.end()\n                    ),\n               \
    \     point\n                ) != PointInPolygon::Outside\n            );\n  \
    \          assert(\n                point_in_polygon(\n                    std::vector<Point<long\
    \ double>>(\n                        second.begin(),\n                       \
    \ second.end()\n                    ),\n                    point\n          \
    \      ) != PointInPolygon::Outside\n            );\n        }\n\n        const\
    \ auto rightmost = std::max_element(\n            first.begin(),\n           \
    \ first.end(),\n            [](const P& left, const P& right) {\n            \
    \    return left.x < right.x;\n            }\n        );\n        const auto leftmost\
    \ = std::min_element(\n            second.begin(),\n            second.end(),\n\
    \            [](const P& left, const P& right) {\n                return left.x\
    \ < right.x;\n            }\n        );\n        std::vector<P> touching = second;\n\
    \        const P touching_translation = *rightmost - *leftmost;\n        for (P&\
    \ point : touching) point += touching_translation;\n        const auto degenerate\
    \ =\n            convex_polygon_intersection(first, touching);\n        assert(!degenerate.empty());\n\
    \        assert(close(polygon_area(degenerate), 0));\n        assert_same_closed_polygon(\n\
    \            degenerate,\n            clipping_intersection(first, touching)\n\
    \        );\n    }\n}\n\nvoid test_randomized_floating_intersection() {\n    std::uint64_t\
    \ state = 0xbb67ae8584caa73bULL;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \    constexpr long double pi = 3.141592653589793238462643383279L;\n\n    for\
    \ (int trial = 0; trial < 2000; ++trial) {\n        const int first_size = 3 +\
    \ int(random() % 20);\n        const int second_size = 3 + int(random() % 20);\n\
    \        const long double first_phase =\n            2 * pi * static_cast<long\
    \ double>(random() % 1000000) / 1000000;\n        const long double second_phase\
    \ =\n            2 * pi * static_cast<long double>(random() % 1000000) / 1000000;\n\
    \        const Point<long double> first_center(\n            static_cast<long\
    \ double>(random() % 2001) / 100 - 10,\n            static_cast<long double>(random()\
    \ % 2001) / 100 - 10\n        );\n        const Point<long double> second_center(\n\
    \            static_cast<long double>(random() % 4001) / 100 - 20,\n         \
    \   static_cast<long double>(random() % 4001) / 100 - 20\n        );\n\n     \
    \   std::vector<Point<long double>> first;\n        std::vector<Point<long double>>\
    \ second;\n        for (int index = 0; index < first_size; ++index) {\n      \
    \      const long double angle =\n                first_phase + 2 * pi * index\
    \ / first_size;\n            first.emplace_back(\n                first_center.x\
    \ + 12 * std::cos(angle),\n                first_center.y + 7 * std::sin(angle)\n\
    \            );\n        }\n        for (int index = 0; index < second_size; ++index)\
    \ {\n            const long double angle =\n                second_phase + 2 *\
    \ pi * index / second_size;\n            second.emplace_back(\n              \
    \  second_center.x + 9 * std::cos(angle),\n                second_center.y + 14\
    \ * std::sin(angle)\n            );\n        }\n\n        assert_same_closed_polygon(\n\
    \            convex_polygon_intersection(first, second),\n            clipping_intersection(first,\
    \ second)\n        );\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_centroid_and_triangulation();\n\
    \    test_reflection();\n    test_ray_polygon();\n    test_polygon_polygon();\n\
    \    test_minkowski_examples();\n    test_randomized_minkowski_and_clipping();\n\
    \    test_randomized_floating_intersection();\n\n    long long a, b;\n    fast_input\
    \ >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../geometry/convex_polygon.hpp\"\n#include \"../../geometry/polygon.hpp\"\n\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <vector>\n\
    \nnamespace {\n\nusing namespace m1une::geometry;\nusing P = Point<long long>;\n\
    \nbool close(long double first, long double second) {\n    return std::fabs(first\
    \ - second) <= 1e-9L;\n}\n\nstd::vector<P> square(\n    long long left,\n    long\
    \ long bottom,\n    long long right,\n    long long top\n) {\n    std::vector<P>\
    \ result;\n    result.emplace_back(left, bottom);\n    result.emplace_back(right,\
    \ bottom);\n    result.emplace_back(right, top);\n    result.emplace_back(left,\
    \ top);\n    return result;\n}\n\ntemplate <typename T>\nstd::vector<Point<long\
    \ double>> clipping_intersection(\n    std::vector<Point<T>> first,\n    std::vector<Point<T>>\
    \ second\n) {\n    first = normalize_convex_polygon(std::move(first));\n    second\
    \ = normalize_convex_polygon(std::move(second));\n    std::vector<Point<long double>>\
    \ result;\n    result.reserve(first.size());\n    for (const Point<T>& point :\
    \ first) result.emplace_back(point);\n    for (std::size_t index = 0; index <\
    \ second.size(); ++index) {\n        const Line<T> boundary{\n            second[index],\n\
    \            second[(index + 1) % second.size()]\n        };\n        result =\
    \ convex_cut(result, Line<long double>{\n            Point<long double>(boundary.a),\n\
    \            Point<long double>(boundary.b)\n        });\n        if (result.empty())\
    \ break;\n    }\n    return result;\n}\n\ntemplate <typename T>\nPointInPolygon\
    \ contains_closed(\n    const std::vector<Point<T>>& polygon,\n    const Point<T>&\
    \ point\n) {\n    if (polygon.empty()) return PointInPolygon::Outside;\n    if\
    \ (polygon.size() == 1) {\n        return distance(polygon[0], point) <= 1e-8L\n\
    \            ? PointInPolygon::Boundary\n            : PointInPolygon::Outside;\n\
    \    }\n    if (polygon.size() == 2) {\n        return on_segment(Segment<T>{polygon[0],\
    \ polygon[1]}, point, 1e-8L)\n            ? PointInPolygon::Boundary\n       \
    \     : PointInPolygon::Outside;\n    }\n    return point_in_polygon(polygon,\
    \ point, 1e-8L);\n}\n\nvoid assert_same_closed_polygon(\n    const std::vector<Point<long\
    \ double>>& first,\n    const std::vector<Point<long double>>& second\n) {\n \
    \   assert(first.empty() == second.empty());\n    assert(close(polygon_area(first),\
    \ polygon_area(second)));\n    for (const auto& point : first) {\n        assert(contains_closed(second,\
    \ point) != PointInPolygon::Outside);\n    }\n    for (const auto& point : second)\
    \ {\n        assert(contains_closed(first, point) != PointInPolygon::Outside);\n\
    \    }\n}\n\ntemplate <typename T>\nlong double triangle_area(\n    const std::array<Point<T>,\
    \ 3>& triangle\n) {\n    return std::fabs(\n        static_cast<long double>(\n\
    \            cross(triangle[0], triangle[1], triangle[2])\n        )\n    ) /\
    \ 2;\n}\n\nvoid test_centroid_and_triangulation() {\n    std::vector<P> rectangle\
    \ = square(0, 0, 4, 2);\n    auto rectangle_centroid = polygon_centroid(rectangle);\n\
    \    assert(rectangle_centroid.has_value());\n    assert(close(rectangle_centroid->x,\
    \ 2));\n    assert(close(rectangle_centroid->y, 1));\n    auto same_centroid =\
    \ polygon_center_of_gravity(rectangle);\n    assert(same_centroid.has_value());\n\
    \    assert(close(same_centroid->x, 2));\n    assert(close(same_centroid->y, 1));\n\
    \n    std::vector<P> concave;\n    concave.emplace_back(0, 0);\n    concave.emplace_back(5,\
    \ 0);\n    concave.emplace_back(5, 1);\n    concave.emplace_back(1, 1);\n    concave.emplace_back(1,\
    \ 5);\n    concave.emplace_back(0, 5);\n    assert(is_simple_polygon(concave));\n\
    \n    auto centroid = polygon_centroid(concave);\n    assert(centroid.has_value());\n\
    \    assert(close(centroid->x, 14.5L / 9));\n    assert(close(centroid->y, 14.5L\
    \ / 9));\n\n    auto triangulation = triangulate_polygon(concave);\n    assert(triangulation.has_value());\n\
    \    assert(triangulation->size() == 4);\n    long double area_sum = 0;\n    for\
    \ (const auto& triangle : *triangulation) {\n        assert(orientation(triangle[0],\
    \ triangle[1], triangle[2]) > 0);\n        area_sum += triangle_area(triangle);\n\
    \    }\n    assert(close(area_sum, polygon_area(concave)));\n\n    std::reverse(concave.begin(),\
    \ concave.end());\n    auto clockwise = triangulate_polygon(concave);\n    assert(clockwise.has_value());\n\
    \    assert(clockwise->size() == 4);\n\n    std::vector<P> redundant;\n    redundant.emplace_back(0,\
    \ 0);\n    redundant.emplace_back(2, 0);\n    redundant.emplace_back(4, 0);\n\
    \    redundant.emplace_back(4, 3);\n    redundant.emplace_back(0, 3);\n    redundant.emplace_back(0,\
    \ 0);\n    auto cleaned = triangulate_polygon(redundant);\n    assert(cleaned.has_value());\n\
    \    assert(cleaned->size() == 2);\n\n    auto convex = triangulate_convex_polygon(rectangle);\n\
    \    assert(convex.size() == 2);\n\n    std::vector<P> bow_tie;\n    bow_tie.emplace_back(0,\
    \ 0);\n    bow_tie.emplace_back(3, 3);\n    bow_tie.emplace_back(0, 3);\n    bow_tie.emplace_back(3,\
    \ 0);\n    assert(!is_simple_polygon(bow_tie));\n    assert(!triangulate_polygon(bow_tie).has_value());\n\
    \n    std::vector<P> backtracking;\n    backtracking.emplace_back(0, 0);\n   \
    \ backtracking.emplace_back(4, 0);\n    backtracking.emplace_back(2, 0);\n   \
    \ backtracking.emplace_back(2, 3);\n    backtracking.emplace_back(0, 3);\n   \
    \ assert(!is_simple_polygon(backtracking));\n    assert(!triangulate_polygon(backtracking).has_value());\n\
    \n    std::vector<P> zero_area;\n    zero_area.emplace_back(0, 0);\n    zero_area.emplace_back(1,\
    \ 0);\n    zero_area.emplace_back(2, 0);\n    assert(!polygon_centroid(zero_area).has_value());\n\
    \    assert(!triangulate_polygon(zero_area).has_value());\n}\n\nvoid test_reflection()\
    \ {\n    Line<long long> mirror;\n    mirror.a = P(-10, 0);\n    mirror.b = P(10,\
    \ 0);\n\n    Ray<long long> incoming;\n    incoming.origin = P(-2, 3);\n    incoming.through\
    \ = P(0, 0);\n    Ray<long double> outgoing =\n        reflected_ray(incoming,\
    \ P(0, 0), mirror);\n    assert(close(outgoing.origin.x, 0));\n    assert(close(outgoing.origin.y,\
    \ 0));\n    assert(close(outgoing.through.x, 2));\n    assert(close(outgoing.through.y,\
    \ 3));\n\n    Ray<long double> mirrored = reflection(mirror, incoming);\n    assert(close(mirrored.origin.x,\
    \ -2));\n    assert(close(mirrored.origin.y, -3));\n    assert(close(mirrored.through.x,\
    \ 0));\n    assert(close(mirrored.through.y, 0));\n}\n\nvoid test_ray_polygon()\
    \ {\n    std::vector<P> polygon = square(0, 0, 4, 4);\n    Ray<long long> crossing;\n\
    \    crossing.origin = P(-2, 2);\n    crossing.through = P(-1, 2);\n    auto hits\
    \ = ray_polygon_intersections(crossing, polygon);\n    assert(hits.size() == 2);\n\
    \    assert(close(hits[0].x, 0));\n    assert(close(hits[1].x, 4));\n    assert(intersects(crossing,\
    \ polygon));\n    assert(close(distance(crossing, polygon), 0));\n\n    Ray<long\
    \ long> inside;\n    inside.origin = P(2, 2);\n    inside.through = P(3, 2);\n\
    \    auto first = first_ray_polygon_intersection(inside, polygon);\n    assert(first.has_value());\n\
    \    assert(close(first->x, 4));\n    assert(intersects(inside, polygon));\n\n\
    \    Ray<long long> collinear;\n    collinear.origin = P(-2, 0);\n    collinear.through\
    \ = P(-1, 0);\n    auto boundary = ray_polygon_intersections(collinear, polygon);\n\
    \    assert(boundary.size() == 2);\n    assert(close(boundary[0].x, 0));\n   \
    \ assert(close(boundary[1].x, 4));\n\n    Ray<long long> through_vertices;\n \
    \   through_vertices.origin = P(-1, -1);\n    through_vertices.through = P(0,\
    \ 0);\n    auto vertex_hits =\n        ray_polygon_intersections(through_vertices,\
    \ polygon);\n    assert(vertex_hits.size() == 2);\n    assert(close(vertex_hits[0].x,\
    \ 0));\n    assert(close(vertex_hits[1].x, 4));\n\n    Ray<long long> missing;\n\
    \    missing.origin = P(-2, 7);\n    missing.through = P(-1, 7);\n    assert(!intersects(missing,\
    \ polygon));\n    assert(close(distance(missing, polygon), 3));\n}\n\nvoid test_polygon_polygon()\
    \ {\n    std::vector<P> first = square(0, 0, 4, 4);\n    std::vector<P> overlap\
    \ = square(2, 1, 6, 3);\n    std::vector<P> contained = square(1, 1, 2, 2);\n\
    \    std::vector<P> touching = square(4, 1, 7, 2);\n    std::vector<P> separate\
    \ = square(7, 0, 9, 2);\n\n    assert(intersects(first, overlap));\n    assert(intersects(first,\
    \ contained));\n    assert(intersects(first, touching));\n    assert(!intersects(first,\
    \ separate));\n    assert(close(distance(first, separate), 3));\n\n    std::vector<P>\
    \ concave;\n    concave.emplace_back(0, 0);\n    concave.emplace_back(5, 0);\n\
    \    concave.emplace_back(5, 1);\n    concave.emplace_back(1, 1);\n    concave.emplace_back(1,\
    \ 5);\n    concave.emplace_back(0, 5);\n    std::vector<P> in_arm = square(0,\
    \ 3, 1, 4);\n    std::vector<P> in_notch = square(2, 2, 3, 3);\n    assert(intersects(concave,\
    \ in_arm));\n    assert(!intersects(concave, in_notch));\n    assert(close(distance(concave,\
    \ in_notch), 1));\n\n    auto clipped = convex_polygon_intersection(first, overlap);\n\
    \    assert(clipped.size() == 4);\n    assert(close(polygon_area(clipped), 4));\n\
    \    std::reverse(first.begin(), first.end());\n    auto clockwise_clip = convex_polygon_intersection(first,\
    \ overlap);\n    assert(close(polygon_area(clockwise_clip), 4));\n    assert(polygon_area2(clockwise_clip)\
    \ > 0);\n    std::reverse(first.begin(), first.end());\n\n    auto contained_clip\
    \ = convex_polygon_intersection(first, contained);\n    assert(close(polygon_area(contained_clip),\
    \ 1));\n\n    auto touching_clip = convex_polygon_intersection(first, touching);\n\
    \    assert(touching_clip.size() == 2);\n    assert(close(polygon_area(touching_clip),\
    \ 0));\n\n    auto empty_clip = convex_polygon_intersection(first, separate);\n\
    \    assert(empty_clip.empty());\n\n    std::vector<P> corner_touching = square(4,\
    \ 4, 7, 7);\n    auto corner_clip = convex_polygon_intersection(first, corner_touching);\n\
    \    assert(corner_clip.size() == 1);\n    assert(close(corner_clip[0].x, 4));\n\
    \    assert(close(corner_clip[0].y, 4));\n}\n\nvoid test_minkowski_examples()\
    \ {\n    std::vector<P> first = square(0, 0, 2, 2);\n    std::vector<P> second;\n\
    \    second.emplace_back(0, 0);\n    second.emplace_back(2, 0);\n    second.emplace_back(0,\
    \ 1);\n\n    std::vector<P> sum = minkowski_sum(first, second);\n    std::vector<P>\
    \ brute;\n    for (const P& a : first) {\n        for (const P& b : second) brute.push_back(a\
    \ + b);\n    }\n    assert(convex_hull(sum) == convex_hull(brute));\n\n    std::reverse(first.begin(),\
    \ first.end());\n    std::reverse(second.begin(), second.end());\n    assert(\n\
    \        convex_hull(minkowski_sum(first, second)) ==\n        convex_hull(brute)\n\
    \    );\n\n    std::vector<P> segment;\n    segment.emplace_back(0, 0);\n    segment.emplace_back(3,\
    \ 0);\n    std::vector<P> point;\n    point.emplace_back(2, 4);\n    std::vector<P>\
    \ translated = minkowski_sum(segment, point);\n    std::vector<P> expected;\n\
    \    expected.emplace_back(2, 4);\n    expected.emplace_back(5, 4);\n    assert(translated\
    \ == expected);\n\n    std::vector<P> diagonal_segment;\n    diagonal_segment.emplace_back(2,\
    \ -1);\n    diagonal_segment.emplace_back(-1, 2);\n    std::vector<P> segment_sum\
    \ = minkowski_sum(diagonal_segment, first);\n    brute.clear();\n    for (const\
    \ P& a : diagonal_segment) {\n        for (const P& b : first) brute.push_back(a\
    \ + b);\n    }\n    assert(convex_hull(segment_sum) == convex_hull(brute));\n\
    }\n\nvoid test_randomized_minkowski_and_clipping() {\n    std::uint64_t state\
    \ = 0x314159265358979ULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for\
    \ (int trial = 0; trial < 5000; ++trial) {\n        std::vector<P> first_points;\n\
    \        std::vector<P> second_points;\n        int first_count = 3 + static_cast<int>(random()\
    \ % 8);\n        int second_count = 3 + static_cast<int>(random() % 8);\n    \
    \    for (int index = 0; index < first_count; ++index) {\n            first_points.emplace_back(\n\
    \                static_cast<long long>(random() % 21) - 10,\n               \
    \ static_cast<long long>(random() % 21) - 10\n            );\n        }\n    \
    \    for (int index = 0; index < second_count; ++index) {\n            second_points.emplace_back(\n\
    \                static_cast<long long>(random() % 21) - 10,\n               \
    \ static_cast<long long>(random() % 21) - 10\n            );\n        }\n    \
    \    std::vector<P> first = convex_hull(first_points);\n        std::vector<P>\
    \ second = convex_hull(second_points);\n        if (first.size() < 3 || second.size()\
    \ < 3) continue;\n        const P translation(\n            static_cast<long long>(random()\
    \ % 41) - 20,\n            static_cast<long long>(random() % 41) - 20\n      \
    \  );\n        for (P& point : second) point += translation;\n\n        auto ear_triangles\
    \ = triangulate_polygon(first);\n        assert(ear_triangles.has_value());\n\
    \        auto fan_triangles = triangulate_convex_polygon(first);\n        assert(ear_triangles->size()\
    \ == first.size() - 2);\n        assert(fan_triangles.size() == first.size() -\
    \ 2);\n        long double ear_area = 0;\n        long double fan_area = 0;\n\
    \        for (const auto& triangle : *ear_triangles) {\n            ear_area +=\
    \ triangle_area(triangle);\n        }\n        for (const auto& triangle : fan_triangles)\
    \ {\n            fan_area += triangle_area(triangle);\n        }\n        assert(close(ear_area,\
    \ polygon_area(first)));\n        assert(close(fan_area, polygon_area(first)));\n\
    \n        std::vector<P> brute_sums;\n        for (const P& a : first) {\n   \
    \         for (const P& b : second) brute_sums.push_back(a + b);\n        }\n\
    \        assert(\n            convex_hull(minkowski_sum(first, second)) ==\n \
    \           convex_hull(brute_sums)\n        );\n\n        auto forward = convex_polygon_intersection(first,\
    \ second);\n        auto backward = convex_polygon_intersection(second, first);\n\
    \        assert(close(polygon_area(forward), polygon_area(backward)));\n     \
    \   assert_same_closed_polygon(\n            forward,\n            clipping_intersection(first,\
    \ second)\n        );\n        for (const Point<long double>& point : forward)\
    \ {\n            assert(\n                point_in_polygon(\n                \
    \    std::vector<Point<long double>>(\n                        first.begin(),\n\
    \                        first.end()\n                    ),\n               \
    \     point\n                ) != PointInPolygon::Outside\n            );\n  \
    \          assert(\n                point_in_polygon(\n                    std::vector<Point<long\
    \ double>>(\n                        second.begin(),\n                       \
    \ second.end()\n                    ),\n                    point\n          \
    \      ) != PointInPolygon::Outside\n            );\n        }\n\n        const\
    \ auto rightmost = std::max_element(\n            first.begin(),\n           \
    \ first.end(),\n            [](const P& left, const P& right) {\n            \
    \    return left.x < right.x;\n            }\n        );\n        const auto leftmost\
    \ = std::min_element(\n            second.begin(),\n            second.end(),\n\
    \            [](const P& left, const P& right) {\n                return left.x\
    \ < right.x;\n            }\n        );\n        std::vector<P> touching = second;\n\
    \        const P touching_translation = *rightmost - *leftmost;\n        for (P&\
    \ point : touching) point += touching_translation;\n        const auto degenerate\
    \ =\n            convex_polygon_intersection(first, touching);\n        assert(!degenerate.empty());\n\
    \        assert(close(polygon_area(degenerate), 0));\n        assert_same_closed_polygon(\n\
    \            degenerate,\n            clipping_intersection(first, touching)\n\
    \        );\n    }\n}\n\nvoid test_randomized_floating_intersection() {\n    std::uint64_t\
    \ state = 0xbb67ae8584caa73bULL;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \    constexpr long double pi = 3.141592653589793238462643383279L;\n\n    for\
    \ (int trial = 0; trial < 2000; ++trial) {\n        const int first_size = 3 +\
    \ int(random() % 20);\n        const int second_size = 3 + int(random() % 20);\n\
    \        const long double first_phase =\n            2 * pi * static_cast<long\
    \ double>(random() % 1000000) / 1000000;\n        const long double second_phase\
    \ =\n            2 * pi * static_cast<long double>(random() % 1000000) / 1000000;\n\
    \        const Point<long double> first_center(\n            static_cast<long\
    \ double>(random() % 2001) / 100 - 10,\n            static_cast<long double>(random()\
    \ % 2001) / 100 - 10\n        );\n        const Point<long double> second_center(\n\
    \            static_cast<long double>(random() % 4001) / 100 - 20,\n         \
    \   static_cast<long double>(random() % 4001) / 100 - 20\n        );\n\n     \
    \   std::vector<Point<long double>> first;\n        std::vector<Point<long double>>\
    \ second;\n        for (int index = 0; index < first_size; ++index) {\n      \
    \      const long double angle =\n                first_phase + 2 * pi * index\
    \ / first_size;\n            first.emplace_back(\n                first_center.x\
    \ + 12 * std::cos(angle),\n                first_center.y + 7 * std::sin(angle)\n\
    \            );\n        }\n        for (int index = 0; index < second_size; ++index)\
    \ {\n            const long double angle =\n                second_phase + 2 *\
    \ pi * index / second_size;\n            second.emplace_back(\n              \
    \  second_center.x + 9 * std::cos(angle),\n                second_center.y + 14\
    \ * std::sin(angle)\n            );\n        }\n\n        assert_same_closed_polygon(\n\
    \            convex_polygon_intersection(first, second),\n            clipping_intersection(first,\
    \ second)\n        );\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_centroid_and_triangulation();\n\
    \    test_reflection();\n    test_ray_polygon();\n    test_polygon_polygon();\n\
    \    test_minkowski_examples();\n    test_randomized_minkowski_and_clipping();\n\
    \    test_randomized_floating_intersection();\n\n    long long a, b;\n    fast_input\
    \ >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - geometry/convex_polygon.hpp
  - geometry/convex_hull.hpp
  - geometry/point.hpp
  - geometry/half_plane_intersection.hpp
  - geometry/line.hpp
  - geometry/minkowski_sum.hpp
  - geometry/detail/convex_polygon_normalize.hpp
  - geometry/point.hpp
  - geometry/polygon.hpp
  - geometry/ray.hpp
  - geometry/polygon.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/polygon_operations.test.cpp
  requiredBy: []
  timestamp: '2026-08-20 20:51:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/polygon_operations.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/polygon_operations.test.cpp
- /verify/verify/geometry/polygon_operations.test.cpp.html
title: verify/geometry/polygon_operations.test.cpp
---
