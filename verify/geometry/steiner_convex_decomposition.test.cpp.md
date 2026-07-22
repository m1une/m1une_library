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
    path: geometry/half_plane_intersection.hpp
    title: Half-Plane Intersection
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: Lines and Segments
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/polygon.hpp
    title: Polygons
  - icon: ':heavy_check_mark:'
    path: geometry/ray.hpp
    title: Rays
  - icon: ':heavy_check_mark:'
    path: geometry/steiner_convex_decomposition.hpp
    title: Steiner Convex Decomposition
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
  bundledCode: "#line 1 \"verify/geometry/steiner_convex_decomposition.test.cpp\"\n\
    #define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B\"\
    \n\n#line 1 \"geometry/convex_polygon.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <cmath>\n#include <concepts>\n#include\
    \ <cstddef>\n#include <deque>\n#include <limits>\n#include <numbers>\n#include\
    \ <optional>\n#include <utility>\n#include <vector>\n\n#line 1 \"geometry/convex_hull.hpp\"\
    \n\n\n\n#line 8 \"geometry/convex_hull.hpp\"\n\n#line 1 \"geometry/point.hpp\"\
    \n\n\n\n#line 7 \"geometry/point.hpp\"\n#include <type_traits>\n\nnamespace m1une\
    \ {\nnamespace geometry {\n\ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T>\
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
    geometry/half_plane_intersection.hpp\"\n\n\n\n#line 12 \"geometry/half_plane_intersection.hpp\"\
    \n#include <random>\n#line 15 \"geometry/half_plane_intersection.hpp\"\n\n#line\
    \ 1 \"geometry/line.hpp\"\n\n\n\n#line 8 \"geometry/line.hpp\"\n\n#line 10 \"\
    geometry/line.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate\
    \ T>\nstruct Line {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate\
    \ T>\nstruct Segment {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate\
    \ T>\nconstexpr Point<long double> centroid(const Segment<T>& segment) {\n   \
    \ return Point<long double>(\n        (\n            static_cast<long double>(segment.a.x)\
    \ +\n            static_cast<long double>(segment.b.x)\n        ) / 2,\n     \
    \   (\n            static_cast<long double>(segment.a.y) +\n            static_cast<long\
    \ double>(segment.b.y)\n        ) / 2\n    );\n}\n\ntemplate <Coordinate T>\n\
    bool on_line(\n    const Line<T>& line,\n    const Point<T>& point,\n    long\
    \ double eps = 1e-12L\n) {\n    assert(line.a != line.b);\n    return orientation(line.a,\
    \ line.b, point, eps) == 0;\n}\n\ntemplate <Coordinate T>\nbool parallel(const\
    \ Line<T>& first, const Line<T>& second, long double eps = 1e-12L) {\n    using\
    \ W = wide_type<T>;\n    W first_x = W(first.b.x) - W(first.a.x);\n    W first_y\
    \ = W(first.b.y) - W(first.a.y);\n    W second_x = W(second.b.x) - W(second.a.x);\n\
    \    W second_y = W(second.b.y) - W(second.a.y);\n    return sign<T>(first_x *\
    \ second_y - first_y * second_x, eps) == 0;\n}\n\ntemplate <Coordinate T>\nbool\
    \ orthogonal(const Line<T>& first, const Line<T>& second, long double eps = 1e-12L)\
    \ {\n    using W = wide_type<T>;\n    W first_x = W(first.b.x) - W(first.a.x);\n\
    \    W first_y = W(first.b.y) - W(first.a.y);\n    W second_x = W(second.b.x)\
    \ - W(second.a.x);\n    W second_y = W(second.b.y) - W(second.a.y);\n    return\
    \ sign<T>(first_x * second_x + first_y * second_y, eps) == 0;\n}\n\ntemplate <Coordinate\
    \ T>\nPoint<long double> projection(const Line<T>& line, const Point<T>& point)\
    \ {\n    assert(line.a != line.b);\n    Point<long double> a(line.a);\n    Point<long\
    \ double> direction(\n        static_cast<long double>(line.b.x) - static_cast<long\
    \ double>(line.a.x),\n        static_cast<long double>(line.b.y) - static_cast<long\
    \ double>(line.a.y)\n    );\n    Point<long double> offset(\n        static_cast<long\
    \ double>(point.x) - a.x,\n        static_cast<long double>(point.y) - a.y\n \
    \   );\n    long double ratio = dot(offset, direction) / dot(direction, direction);\n\
    \    return a + direction * ratio;\n}\n\ntemplate <Coordinate T>\nPoint<long double>\
    \ reflection(const Line<T>& line, const Point<T>& point) {\n    Point<long double>\
    \ projected = projection(line, point);\n    return projected * 2.0L - Point<long\
    \ double>(point);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Line<T>&\
    \ line, const Point<T>& point) {\n    assert(line.a != line.b);\n    Point<long\
    \ double> direction(\n        static_cast<long double>(line.b.x) - static_cast<long\
    \ double>(line.a.x),\n        static_cast<long double>(line.b.y) - static_cast<long\
    \ double>(line.a.y)\n    );\n    Point<long double> offset(\n        static_cast<long\
    \ double>(point.x) - static_cast<long double>(line.a.x),\n        static_cast<long\
    \ double>(point.y) - static_cast<long double>(line.a.y)\n    );\n    return std::fabs(cross(direction,\
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
    \ != second.b);\n    Point<long double> p(first.a);\n    Point<long double> q(second.a);\n\
    \    Point<long double> r = Point<long double>(first.b) - p;\n    Point<long double>\
    \ s = Point<long double>(second.b) - q;\n    long double denominator = cross(r,\
    \ s);\n    if (std::fabs(denominator) <= eps) return std::nullopt;\n    long double\
    \ ratio = cross(q - p, s) / denominator;\n    return p + r * ratio;\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Point<long double>> line_segment_intersection(\n\
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
    \ m1une\n\n\n#line 1 \"geometry/polygon.hpp\"\n\n\n\n#line 12 \"geometry/polygon.hpp\"\
    \n\n#line 1 \"geometry/ray.hpp\"\n\n\n\n#line 7 \"geometry/ray.hpp\"\n\n#line\
    \ 9 \"geometry/ray.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate\
    \ <Coordinate T>\nstruct Ray {\n    Point<T> origin;\n    Point<T> through;\n\
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
    }  // namespace m1une\n\n\n#line 20 \"geometry/convex_polygon.hpp\"\n\nnamespace\
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
    }\n\ntemplate <Coordinate T>\nstd::vector<Point<T>> without_closing_point(std::vector<Point<T>>\
    \ polygon) {\n    if (\n        polygon.size() >= 2 &&\n        polygon.front()\
    \ == polygon.back()\n    ) {\n        polygon.pop_back();\n    }\n    return polygon;\n\
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
    \ std::vector<Point<T>> polygon,\n    long double eps = 1e-12L\n) {\n    polygon\
    \ = convex_polygon_detail::without_closing_point(\n        std::move(polygon)\n\
    \    );\n    polygon.erase(\n        std::unique(polygon.begin(), polygon.end()),\n\
    \        polygon.end()\n    );\n    if (\n        polygon.size() >= 2 &&\n   \
    \     polygon.front() == polygon.back()\n    ) {\n        polygon.pop_back();\n\
    \    }\n    if (polygon.size() <= 1) return polygon;\n    if (\n        polygon.size()\
    \ >= 3 &&\n        sign<T>(polygon_area2(polygon), eps) < 0\n    ) {\n       \
    \ std::reverse(polygon.begin(), polygon.end());\n    }\n\n    auto start = std::min_element(\n\
    \        polygon.begin(),\n        polygon.end(),\n        [](const Point<T>&\
    \ first, const Point<T>& second) {\n            if (first.y != second.y) return\
    \ first.y < second.y;\n            return first.x < second.x;\n        }\n   \
    \ );\n    std::rotate(polygon.begin(), start, polygon.end());\n\n    if (polygon.size()\
    \ >= 3) {\n        std::vector<Point<T>> cleaned;\n        const std::size_t size\
    \ = polygon.size();\n        cleaned.reserve(size);\n        for (std::size_t\
    \ index = 0; index < size; ++index) {\n            const Point<T>& previous =\
    \ polygon[(index + size - 1) % size];\n            const Point<T>& current = polygon[index];\n\
    \            const Point<T>& next = polygon[(index + 1) % size];\n           \
    \ if (\n                orientation(previous, current, next, eps) != 0 ||\n  \
    \              sign<T>(dot(current - previous, next - current), eps) < 0\n   \
    \         ) {\n                cleaned.push_back(current);\n            }\n  \
    \      }\n        polygon = std::move(cleaned);\n    }\n    return polygon;\n\
    }\n\ntemplate <Coordinate T>\nPointInPolygon point_in_convex_polygon(\n    const\
    \ std::vector<Point<T>>& polygon,\n    const Point<T>& point,\n    long double\
    \ eps = 1e-12L\n) {\n    const std::size_t size = polygon.size();\n    if (size\
    \ == 0) return PointInPolygon::Outside;\n    if (size == 1) {\n        return\
    \ distance(polygon[0], point) <= eps\n            ? PointInPolygon::Boundary\n\
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
    template <Coordinate T>\nstd::vector<Point<T>> minkowski_sum(\n    std::vector<Point<T>>\
    \ first,\n    std::vector<Point<T>> second,\n    long double eps = 1e-12L\n) {\n\
    \    assert(!first.empty());\n    assert(!second.empty());\n    first = normalize_convex_polygon(std::move(first),\
    \ eps);\n    second = normalize_convex_polygon(std::move(second), eps);\n\n  \
    \  if (first.size() == 1 || second.size() == 1) {\n        if (second.size() ==\
    \ 1) std::swap(first, second);\n        for (Point<T>& point : second) {\n   \
    \         point += first[0];\n        }\n        return normalize_convex_polygon(std::move(second),\
    \ eps);\n    }\n\n    std::vector<Point<T>> first_edges;\n    std::vector<Point<T>>\
    \ second_edges;\n    first_edges.reserve(first.size());\n    second_edges.reserve(second.size());\n\
    \    for (std::size_t index = 0; index < first.size(); ++index) {\n        first_edges.push_back(\n\
    \            first[(index + 1) % first.size()] - first[index]\n        );\n  \
    \  }\n    for (std::size_t index = 0; index < second.size(); ++index) {\n    \
    \    second_edges.push_back(\n            second[(index + 1) % second.size()]\
    \ - second[index]\n        );\n    }\n\n    Point<T> current = first.front() +\
    \ second.front();\n    std::vector<Point<T>> result;\n    result.reserve(first.size()\
    \ + second.size());\n    result.push_back(current);\n    std::size_t first_index\
    \ = 0;\n    std::size_t second_index = 0;\n    while (\n        first_index <\
    \ first_edges.size() ||\n        second_index < second_edges.size()\n    ) {\n\
    \        Point<T> step;\n        if (first_index == first_edges.size()) {\n  \
    \          step = second_edges[second_index++];\n        } else if (second_index\
    \ == second_edges.size()) {\n            step = first_edges[first_index++];\n\
    \        } else {\n            const auto turn = cross(\n                first_edges[first_index],\n\
    \                second_edges[second_index]\n            );\n            if (turn\
    \ > 0) {\n                step = first_edges[first_index++];\n            } else\
    \ if (turn < 0) {\n                step = second_edges[second_index++];\n    \
    \        } else {\n                step =\n                    first_edges[first_index++]\
    \ +\n                    second_edges[second_index++];\n            }\n      \
    \  }\n        current += step;\n        if (\n            first_index < first_edges.size()\
    \ ||\n            second_index < second_edges.size()\n        ) {\n          \
    \  result.push_back(current);\n        }\n    }\n    return normalize_convex_polygon(std::move(result),\
    \ eps);\n}\n\ntemplate <Coordinate T>\nbool convex_polygons_intersect(\n    const\
    \ ConvexPolygon<T>& first,\n    const ConvexPolygon<T>& second,\n    long double\
    \ eps = 1e-12L\n) {\n    assert(!first.empty());\n    assert(!second.empty());\n\
    \    if (first.size() <= 2 && second.size() <= 2) {\n        if (first.size()\
    \ == 1 && second.size() == 1) {\n            return distance(first[0], second[0])\
    \ <= eps;\n        }\n        if (first.size() == 1) {\n            return on_segment(\n\
    \                Segment<T>{second[0], second[1]},\n                first[0],\n\
    \                eps\n            );\n        }\n        if (second.size() ==\
    \ 1) {\n            return on_segment(\n                Segment<T>{first[0], first[1]},\n\
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
    \ result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 1 \"\
    geometry/steiner_convex_decomposition.hpp\"\n\n\n\n#line 10 \"geometry/steiner_convex_decomposition.hpp\"\
    \n#include <map>\n#line 14 \"geometry/steiner_convex_decomposition.hpp\"\n\n#line\
    \ 16 \"geometry/steiner_convex_decomposition.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\nnamespace steiner_convex_decomposition_detail {\n\nusing PointType\
    \ = Point<long double>;\n\ninline int scalar_sign(long double value, long double\
    \ eps) {\n    return (value > eps) - (value < -eps);\n}\n\ninline bool close(\n\
    \    const PointType& first,\n    const PointType& second,\n    long double eps\n\
    ) {\n    return distance2(first, second) <= eps * eps;\n}\n\ntemplate <std::floating_point\
    \ T>\nstd::optional<std::vector<PointType>> prepare_polygon(\n    const std::vector<Point<T>>&\
    \ input,\n    long double eps\n) {\n    std::vector<PointType> points;\n    points.reserve(input.size());\n\
    \    for (const Point<T>& point : input) {\n        const PointType converted(point);\n\
    \        if (points.empty() || !close(points.back(), converted, eps)) {\n    \
    \        points.push_back(converted);\n        }\n    }\n    if (points.size()\
    \ >= 2 && close(points.front(), points.back(), eps)) {\n        points.pop_back();\n\
    \    }\n    if (points.size() < 3) return std::nullopt;\n\n    const int size\
    \ = static_cast<int>(points.size());\n    std::vector<int> previous(size), next(size);\n\
    \    std::vector<bool> removed(size, false), queued(size, true);\n    std::deque<int>\
    \ candidates;\n    for (int index = 0; index < size; ++index) {\n        previous[index]\
    \ = (index + size - 1) % size;\n        next[index] = (index + 1) % size;\n  \
    \      candidates.push_back(index);\n    }\n\n    int remaining = size;\n    while\
    \ (!candidates.empty() && remaining >= 3) {\n        const int index = candidates.front();\n\
    \        candidates.pop_front();\n        queued[index] = false;\n        if (removed[index])\
    \ continue;\n        const int before = previous[index];\n        const int after\
    \ = next[index];\n        if (\n            orientation(points[before], points[index],\
    \ points[after], eps) !=\n                0 ||\n            scalar_sign(\n   \
    \             dot(\n                    points[index] - points[before],\n    \
    \                points[after] - points[index]\n                ),\n         \
    \       eps\n            ) < 0\n        ) {\n            continue;\n        }\n\
    \        removed[index] = true;\n        next[before] = after;\n        previous[after]\
    \ = before;\n        --remaining;\n        for (const int adjacent : {before,\
    \ after}) {\n            if (!queued[adjacent]) {\n                queued[adjacent]\
    \ = true;\n                candidates.push_back(adjacent);\n            }\n  \
    \      }\n    }\n    if (remaining < 3) return std::nullopt;\n\n    std::vector<PointType>\
    \ polygon;\n    polygon.reserve(static_cast<std::size_t>(remaining));\n    int\
    \ first = 0;\n    while (removed[first]) ++first;\n    int index = first;\n  \
    \  do {\n        polygon.push_back(points[index]);\n        index = next[index];\n\
    \    } while (index != first);\n\n    const int area_sign = scalar_sign(polygon_area2(polygon),\
    \ eps);\n    if (area_sign == 0) return std::nullopt;\n    if (area_sign < 0)\
    \ std::reverse(polygon.begin(), polygon.end());\n    return polygon;\n}\n\nclass\
    \ BoundaryRayShooter {\n   private:\n    struct Chain {\n        int first_edge;\n\
    \        int edge_count;\n    };\n\n   public:\n    struct Hit {\n        long\
    \ double parameter;\n        PointType point;\n        std::vector<int> edges;\n\
    \    };\n\n    BoundaryRayShooter(\n        const std::vector<PointType>& polygon,\n\
    \        long double eps\n    )\n        : polygon_(polygon),\n          size_(static_cast<int>(polygon.size())),\n\
    \          eps_(eps) {\n        build_chains();\n    }\n\n    std::optional<Hit>\
    \ shoot(\n        int origin_index,\n        const PointType& direction\n    )\
    \ const {\n        std::vector<int> candidates;\n        for (const Chain& chain\
    \ : chains_) {\n            chain_candidates(\n                chain, polygon_[origin_index],\
    \ direction, candidates\n            );\n        }\n        // Adjacent chains\
    \ may report the same edge. Testing that constant\n        // duplication directly\
    \ keeps the query linear in the chain count.\n\n        long double best = std::numeric_limits<long\
    \ double>::infinity();\n        std::vector<int> best_edges;\n        for (int\
    \ edge : candidates) {\n            edge %= size_;\n            const PointType\
    \ offset = polygon_[edge] - polygon_[origin_index];\n            const PointType\
    \ edge_direction =\n                polygon_[(edge + 1) % size_] - polygon_[edge];\n\
    \            const long double denominator = cross(direction, edge_direction);\n\
    \            long double parameter = -1;\n            if (std::fabs(denominator)\
    \ <= eps_) {\n                if (std::fabs(cross(direction, offset)) > eps_)\
    \ continue;\n                const long double norm2 = dot(direction, direction);\n\
    \                const long double first = dot(offset, direction) / norm2;\n \
    \               const long double second = dot(\n                    polygon_[(edge\
    \ + 1) % size_] - polygon_[origin_index],\n                    direction\n   \
    \             ) / norm2;\n                if (first > eps_) parameter = first;\n\
    \                if (\n                    second > eps_ &&\n                \
    \    (parameter < 0 || second < parameter)\n                ) {\n            \
    \        parameter = second;\n                }\n            } else {\n      \
    \          parameter = cross(offset, edge_direction) / denominator;\n        \
    \        const long double edge_parameter =\n                    cross(offset,\
    \ direction) / denominator;\n                if (\n                    parameter\
    \ <= eps_ || edge_parameter < -eps_ ||\n                    edge_parameter > 1\
    \ + eps_\n                ) {\n                    continue;\n               \
    \ }\n            }\n            if (parameter < 0) continue;\n            if (parameter\
    \ + eps_ < best) {\n                best = parameter;\n                best_edges.assign(1,\
    \ edge);\n            } else if (std::fabs(parameter - best) <= eps_) {\n    \
    \            best_edges.push_back(edge);\n            }\n        }\n        if\
    \ (best_edges.empty()) return std::nullopt;\n        return Hit{\n           \
    \ best,\n            polygon_[origin_index] + direction * best,\n            std::move(best_edges)\n\
    \        };\n    }\n\n   private:\n    const std::vector<PointType>& polygon_;\n\
    \    int size_;\n    long double eps_;\n    std::vector<Chain> chains_;\n\n  \
    \  int quadrant(const PointType& direction) const {\n        const int x_sign\
    \ = scalar_sign(direction.x, eps_);\n        const int y_sign = scalar_sign(direction.y,\
    \ eps_);\n        if (y_sign >= 0) return x_sign >= 0 ? 0 : 1;\n        return\
    \ x_sign < 0 ? 2 : 3;\n    }\n\n    void build_chains() {\n        int first_edge\
    \ = 0;\n        PointType previous_direction = polygon_[1] - polygon_[0];\n  \
    \      int current_quadrant = quadrant(previous_direction);\n        for (int\
    \ edge = 1; edge < size_; ++edge) {\n            const PointType direction =\n\
    \                polygon_[(edge + 1) % size_] - polygon_[edge];\n            const\
    \ int direction_quadrant = quadrant(direction);\n            if (\n          \
    \      scalar_sign(cross(previous_direction, direction), eps_) < 0 ||\n      \
    \          direction_quadrant != current_quadrant\n            ) {\n         \
    \       chains_.push_back(Chain{first_edge, edge - first_edge});\n           \
    \     first_edge = edge;\n                current_quadrant = direction_quadrant;\n\
    \            }\n            previous_direction = direction;\n        }\n     \
    \   chains_.push_back(Chain{first_edge, size_ - first_edge});\n    }\n\n    int\
    \ vertex_side(\n        const PointType& origin,\n        const PointType& direction,\n\
    \        int vertex\n    ) const {\n        return scalar_sign(\n            cross(direction,\
    \ polygon_[vertex % size_] - origin), eps_\n        );\n    }\n\n    int edge_side(const\
    \ PointType& direction, int edge) const {\n        return scalar_sign(\n     \
    \       cross(\n                direction,\n                polygon_[(edge + 1)\
    \ % size_] - polygon_[edge]\n            ),\n            eps_\n        );\n  \
    \  }\n\n    void crossing_on_monotone_part(\n        const Chain& chain,\n   \
    \     const PointType& origin,\n        const PointType& direction,\n        int\
    \ first_position,\n        int last_position,\n        std::vector<int>& candidates\n\
    \    ) const {\n        if (first_position >= last_position) return;\n       \
    \ const int first_sign = vertex_side(\n            origin, direction, chain.first_edge\
    \ + first_position\n        );\n        const int last_sign = vertex_side(\n \
    \           origin, direction, chain.first_edge + last_position\n        );\n\
    \        if (first_sign == 0) {\n            candidates.push_back(chain.first_edge\
    \ + first_position);\n        }\n        if (last_sign == 0) {\n            candidates.push_back(chain.first_edge\
    \ + last_position - 1);\n        }\n        if (\n            first_sign == 0\
    \ || last_sign == 0 ||\n            first_sign == last_sign\n        ) {\n   \
    \         return;\n        }\n        int low = first_position;\n        int high\
    \ = last_position;\n        while (high - low > 1) {\n            const int middle\
    \ = (low + high) / 2;\n            const int middle_sign = vertex_side(\n    \
    \            origin, direction, chain.first_edge + middle\n            );\n  \
    \          if (middle_sign == 0 || middle_sign != first_sign) {\n            \
    \    high = middle;\n            } else {\n                low = middle;\n   \
    \         }\n        }\n        candidates.push_back(chain.first_edge + high -\
    \ 1);\n    }\n\n    void chain_candidates(\n        const Chain& chain,\n    \
    \    const PointType& origin,\n        const PointType& direction,\n        std::vector<int>&\
    \ candidates\n    ) const {\n        int split = 0;\n        const int first_derivative\
    \ =\n            edge_side(direction, chain.first_edge);\n        const int last_derivative\
    \ = edge_side(\n            direction, chain.first_edge + chain.edge_count - 1\n\
    \        );\n        if (\n            first_derivative != 0 && last_derivative\
    \ != 0 &&\n            first_derivative != last_derivative\n        ) {\n    \
    \        int low = 0;\n            int high = chain.edge_count - 1;\n        \
    \    while (high - low > 1) {\n                const int middle = (low + high)\
    \ / 2;\n                const int middle_sign = edge_side(\n                 \
    \   direction, chain.first_edge + middle\n                );\n               \
    \ if (\n                    middle_sign == 0 ||\n                    middle_sign\
    \ != first_derivative\n                ) {\n                    high = middle;\n\
    \                } else {\n                    low = middle;\n               \
    \ }\n            }\n            split = high;\n        }\n        if (split ==\
    \ 0) {\n            crossing_on_monotone_part(\n                chain,\n     \
    \           origin,\n                direction,\n                0,\n        \
    \        chain.edge_count,\n                candidates\n            );\n     \
    \   } else {\n            crossing_on_monotone_part(\n                chain, origin,\
    \ direction, 0, split, candidates\n            );\n            crossing_on_monotone_part(\n\
    \                chain,\n                origin,\n                direction,\n\
    \                split,\n                chain.edge_count,\n                candidates\n\
    \            );\n        }\n    }\n};\n\nclass DecompositionGraph {\n   private:\n\
    \    struct Edge {\n        int first;\n        int second;\n        int boundary_source;\n\
    \        bool active;\n    };\n\n    struct CutHit {\n        long double parameter;\n\
    \        PointType point;\n        int edge;\n        long double edge_parameter;\n\
    \    };\n\n   public:\n    DecompositionGraph(\n        const std::vector<PointType>&\
    \ polygon,\n        const std::vector<int>& reflex_vertices,\n        long double\
    \ eps\n    )\n        : original_size_(static_cast<int>(polygon.size())),\n  \
    \        eps_(eps),\n          vertices_(polygon),\n          boundary_splits_(polygon.size()),\n\
    \          special_(polygon.size(), false) {\n        for (int index = 0; index\
    \ + 1 < original_size_; ++index) {\n            const int edge = static_cast<int>(edges_.size());\n\
    \            edges_.push_back(Edge{index, index + 1, index, true});\n        \
    \    active_edges_.emplace_hint(\n                active_edges_.end(), edge_key(index,\
    \ index + 1), edge\n            );\n        }\n        const int closing_edge\
    \ = static_cast<int>(edges_.size());\n        edges_.push_back(Edge{\n       \
    \     original_size_ - 1, 0, original_size_ - 1, true\n        });\n        active_edges_.emplace(\n\
    \            edge_key(original_size_ - 1, 0), closing_edge\n        );\n     \
    \   for (int index = 0; index < original_size_; ++index) {\n            boundary_splits_[index].emplace(0,\
    \ index);\n            boundary_splits_[index].emplace(\n                1, (index\
    \ + 1) % original_size_\n            );\n        }\n        for (const int reflex\
    \ : reflex_vertices) {\n            special_[reflex] = true;\n            special_vertices_.push_back(reflex);\n\
    \        }\n    }\n\n    std::vector<long double> candidate_alphas(int origin)\
    \ const {\n        const int previous = (origin + original_size_ - 1) % original_size_;\n\
    \        const int next = (origin + 1) % original_size_;\n        const PointType\
    \ left = normalized(\n            vertices_[origin] - vertices_[previous]\n  \
    \      );\n        const PointType right = normalized(\n            vertices_[origin]\
    \ - vertices_[next]\n        );\n        const PointType difference = left - right;\n\
    \n        std::vector<long double> forbidden;\n        for (const int vertex :\
    \ special_vertices_) {\n            if (vertex == origin) continue;\n        \
    \    const PointType offset = vertices_[vertex] - vertices_[origin];\n       \
    \     const long double coefficient = cross(difference, offset);\n           \
    \ if (std::fabs(coefficient) <= eps_) continue;\n            const long double\
    \ alpha = -cross(right, offset) / coefficient;\n            if (eps_ < alpha &&\
    \ alpha < 1 - eps_) forbidden.push_back(alpha);\n        }\n        const int\
    \ candidate_count =\n            static_cast<int>(forbidden.size()) + 5;\n   \
    \     const long double denominator = candidate_count + 1;\n        std::vector<int>\
    \ blocked_delta(candidate_count + 1, 0);\n        for (const long double value\
    \ : forbidden) {\n            int first = static_cast<int>(std::ceil(\n      \
    \          (value - eps_) * denominator - 1\n            ));\n            int\
    \ last = static_cast<int>(std::floor(\n                (value + eps_) * denominator\
    \ - 1\n            ));\n            first = std::max(first, 0);\n            last\
    \ = std::min(last, candidate_count - 1);\n            if (first > last) continue;\n\
    \            ++blocked_delta[first];\n            --blocked_delta[last + 1];\n\
    \        }\n        std::vector<bool> blocked(candidate_count, false);\n     \
    \   int active_blocks = 0;\n        for (int index = 0; index < candidate_count;\
    \ ++index) {\n            active_blocks += blocked_delta[index];\n           \
    \ blocked[index] = active_blocks > 0;\n        }\n\n        std::vector<long double>\
    \ result;\n        result.reserve(4);\n        const int middle = (candidate_count\
    \ - 1) / 2;\n        for (int distance = 0;\n             distance < candidate_count\
    \ && result.size() < 4;\n             ++distance) {\n            for (const int\
    \ index : {middle - distance, middle + distance}) {\n                if (\n  \
    \                  index < 0 || index >= candidate_count ||\n                \
    \    blocked[index]\n                ) {\n                    continue;\n    \
    \            }\n                const long double candidate = (index + 1) / denominator;\n\
    \                if (\n                    result.empty() ||\n               \
    \     std::fabs(candidate - result.back()) > eps_\n                ) {\n     \
    \               result.push_back(candidate);\n                }\n            \
    \    if (result.size() == 4) break;\n            }\n        }\n        return\
    \ result;\n    }\n\n    PointType direction(int origin, long double alpha) const\
    \ {\n        const int previous = (origin + original_size_ - 1) % original_size_;\n\
    \        const int next = (origin + 1) % original_size_;\n        const PointType\
    \ left = normalized(\n            vertices_[origin] - vertices_[previous]\n  \
    \      );\n        const PointType right = normalized(\n            vertices_[origin]\
    \ - vertices_[next]\n        );\n        return left * alpha + right * (1 - alpha);\n\
    \    }\n\n    bool add_cut(\n        int origin,\n        const PointType& direction,\n\
    \        const BoundaryRayShooter::Hit& boundary_hit\n    ) {\n        const std::optional<CutHit>\
    \ cut_hit = closest_cut_hit(\n            vertices_[origin], direction\n     \
    \   );\n        if (\n            cut_hit.has_value() &&\n            cut_hit->parameter\
    \ + eps_ < boundary_hit.parameter\n        ) {\n            const int target =\
    \ split_cut_edge(*cut_hit);\n            if (\n                target < 0 || target\
    \ == origin || special_[target]\n            ) {\n                return false;\n\
    \            }\n            special_[target] = true;\n            special_vertices_.push_back(target);\n\
    \            add_edge(origin, target, -1);\n            return true;\n       \
    \ }\n\n        const int target = boundary_target(boundary_hit);\n        if (target\
    \ < 0 || target == origin || special_[target]) return false;\n        special_[target]\
    \ = true;\n        special_vertices_.push_back(target);\n        add_edge(origin,\
    \ target, -1);\n        return true;\n    }\n\n    std::optional<std::vector<std::vector<PointType>>>\
    \ faces(\n        std::size_t expected_faces\n    ) const {\n        std::vector<std::vector<int>>\
    \ adjacency(vertices_.size());\n        for (const Edge& edge : edges_) {\n  \
    \          if (!edge.active) continue;\n            adjacency[edge.first].push_back(edge.second);\n\
    \            adjacency[edge.second].push_back(edge.first);\n        }\n      \
    \  for (int vertex = 0;\n             vertex < static_cast<int>(vertices_.size());\n\
    \             ++vertex) {\n            auto angle = [&](int neighbor) {\n    \
    \            const PointType offset =\n                    vertices_[neighbor]\
    \ - vertices_[vertex];\n                return std::atan2(offset.y, offset.x);\n\
    \            };\n            std::sort(\n                adjacency[vertex].begin(),\n\
    \                adjacency[vertex].end(),\n                [&](int first, int\
    \ second) {\n                    return angle(first) < angle(second);\n      \
    \          }\n            );\n        }\n\n        std::vector<std::vector<bool>>\
    \ visited(vertices_.size());\n        for (std::size_t vertex = 0; vertex < adjacency.size();\
    \ ++vertex) {\n            visited[vertex].assign(adjacency[vertex].size(), false);\n\
    \        }\n        std::vector<std::vector<PointType>> result;\n        for (int\
    \ first = 0;\n             first < static_cast<int>(vertices_.size());\n     \
    \        ++first) {\n            for (int first_position = 0;\n              \
    \   first_position < static_cast<int>(adjacency[first].size());\n            \
    \     ++first_position) {\n                if (visited[first][first_position])\
    \ continue;\n                const int second = adjacency[first][first_position];\n\
    \                std::vector<PointType> face;\n                int from = first;\n\
    \                int to = second;\n                int from_position = first_position;\n\
    \                while (!visited[from][from_position]) {\n                   \
    \ visited[from][from_position] = true;\n                    face.push_back(vertices_[from]);\n\
    \                    const auto found = std::find(\n                        adjacency[to].begin(),\
    \ adjacency[to].end(), from\n                    );\n                    if (found\
    \ == adjacency[to].end()) return std::nullopt;\n                    const int\
    \ position = static_cast<int>(\n                        found - adjacency[to].begin()\n\
    \                    );\n                    const int degree =\n            \
    \            static_cast<int>(adjacency[to].size());\n                    const\
    \ int next_position =\n                        (position + degree - 1) % degree;\n\
    \                    const int next = adjacency[to][next_position];\n        \
    \            from = to;\n                    to = next;\n                    from_position\
    \ = next_position;\n                }\n                if (from != first || to\
    \ != second) return std::nullopt;\n                if (scalar_sign(polygon_area2(face),\
    \ eps_) <= 0) continue;\n                if (!weakly_convex(face)) return std::nullopt;\n\
    \                result.push_back(std::move(face));\n            }\n        }\n\
    \        if (result.size() != expected_faces) return std::nullopt;\n        return\
    \ result;\n    }\n\n   private:\n    int original_size_;\n    long double eps_;\n\
    \    std::vector<PointType> vertices_;\n    std::vector<Edge> edges_;\n    std::map<std::pair<int,\
    \ int>, int> active_edges_;\n    std::vector<std::map<long double, int>> boundary_splits_;\n\
    \    std::vector<bool> special_;\n    std::vector<int> special_vertices_;\n\n\
    \    static std::pair<int, int> edge_key(int first, int second) {\n        if\
    \ (first > second) std::swap(first, second);\n        return {first, second};\n\
    \    }\n\n    int add_edge(int first, int second, int boundary_source) {\n   \
    \     const int index = static_cast<int>(edges_.size());\n        edges_.push_back(Edge{first,\
    \ second, boundary_source, true});\n        active_edges_[edge_key(first, second)]\
    \ = index;\n        return index;\n    }\n\n    bool remove_edge(int first, int\
    \ second) {\n        const auto found = active_edges_.find(edge_key(first, second));\n\
    \        if (found == active_edges_.end()) return false;\n        edges_[found->second].active\
    \ = false;\n        active_edges_.erase(found);\n        return true;\n    }\n\
    \n    int add_vertex(const PointType& point) {\n        const int index = static_cast<int>(vertices_.size());\n\
    \        vertices_.push_back(point);\n        special_.push_back(false);\n   \
    \     return index;\n    }\n\n    std::optional<CutHit> closest_cut_hit(\n   \
    \     const PointType& origin,\n        const PointType& direction\n    ) const\
    \ {\n        std::optional<CutHit> result;\n        for (int index = 0; index\
    \ < static_cast<int>(edges_.size()); ++index) {\n            const Edge& edge\
    \ = edges_[index];\n            if (!edge.active || edge.boundary_source >= 0)\
    \ continue;\n            const PointType offset = vertices_[edge.first] - origin;\n\
    \            const PointType edge_direction =\n                vertices_[edge.second]\
    \ - vertices_[edge.first];\n            const long double denominator = cross(direction,\
    \ edge_direction);\n            if (std::fabs(denominator) <= eps_) continue;\n\
    \            const long double parameter =\n                cross(offset, edge_direction)\
    \ / denominator;\n            const long double edge_parameter =\n           \
    \     cross(offset, direction) / denominator;\n            if (\n            \
    \    parameter <= eps_ || edge_parameter < -eps_ ||\n                edge_parameter\
    \ > 1 + eps_\n            ) {\n                continue;\n            }\n    \
    \        if (\n                !result.has_value() ||\n                parameter\
    \ + eps_ < result->parameter\n            ) {\n                result = CutHit{\n\
    \                    parameter,\n                    origin + direction * parameter,\n\
    \                    index,\n                    edge_parameter\n            \
    \    };\n            } else if (\n                std::fabs(parameter - result->parameter)\
    \ <= eps_ &&\n                !close(result->point, origin + direction * parameter,\
    \ eps_)\n            ) {\n                return std::nullopt;\n            }\n\
    \        }\n        return result;\n    }\n\n    int split_cut_edge(const CutHit&\
    \ hit) {\n        Edge& edge = edges_[hit.edge];\n        if (!edge.active) return\
    \ -1;\n        if (hit.edge_parameter <= eps_) return edge.first;\n        if\
    \ (hit.edge_parameter >= 1 - eps_) return edge.second;\n        const int first\
    \ = edge.first;\n        const int second = edge.second;\n        const int source\
    \ = edge.boundary_source;\n        if (!remove_edge(first, second)) return -1;\n\
    \        const int vertex = add_vertex(hit.point);\n        add_edge(first, vertex,\
    \ source);\n        add_edge(vertex, second, source);\n        return vertex;\n\
    \    }\n\n    int boundary_target(const BoundaryRayShooter::Hit& hit) {\n    \
    \    int vertex_target = -1;\n        for (const int source : hit.edges) {\n \
    \           const PointType edge =\n                vertices_[(source + 1) % original_size_]\
    \ - vertices_[source];\n            const long double parameter = dot(\n     \
    \           hit.point - vertices_[source], edge\n            ) / dot(edge, edge);\n\
    \            int candidate = -1;\n            if (parameter <= eps_) candidate\
    \ = source;\n            if (parameter >= 1 - eps_) {\n                candidate\
    \ = (source + 1) % original_size_;\n            }\n            if (candidate <\
    \ 0) continue;\n            if (vertex_target >= 0 && vertex_target != candidate)\
    \ return -1;\n            vertex_target = candidate;\n        }\n        if (vertex_target\
    \ >= 0) return vertex_target;\n        if (hit.edges.size() != 1) return -1;\n\
    \n        const int source = hit.edges.front();\n        const PointType edge\
    \ =\n            vertices_[(source + 1) % original_size_] - vertices_[source];\n\
    \        const long double parameter = dot(\n            hit.point - vertices_[source],\
    \ edge\n        ) / dot(edge, edge);\n        auto& splits = boundary_splits_[source];\n\
    \        auto after = splits.lower_bound(parameter);\n        if (\n         \
    \   after != splits.end() &&\n            std::fabs(after->first - parameter)\
    \ <= eps_\n        ) {\n            return after->second;\n        }\n       \
    \ if (after == splits.begin() || after == splits.end()) return -1;\n        const\
    \ auto before = std::prev(after);\n        if (!remove_edge(before->second, after->second))\
    \ return -1;\n        const int vertex = add_vertex(hit.point);\n        add_edge(before->second,\
    \ vertex, source);\n        add_edge(vertex, after->second, source);\n       \
    \ splits.emplace(parameter, vertex);\n        return vertex;\n    }\n\n    bool\
    \ weakly_convex(const std::vector<PointType>& polygon) const {\n        for (std::size_t\
    \ index = 0; index < polygon.size(); ++index) {\n            if (\n          \
    \      orientation(\n                    polygon[index],\n                   \
    \ polygon[(index + 1) % polygon.size()],\n                    polygon[(index +\
    \ 2) % polygon.size()],\n                    eps_\n                ) < 0\n   \
    \         ) {\n                return false;\n            }\n        }\n     \
    \   return true;\n    }\n};\n\n}  // namespace steiner_convex_decomposition_detail\n\
    \ntemplate <std::floating_point T>\nstd::optional<std::vector<std::vector<Point<long\
    \ double>>>>\nsteiner_convex_decomposition(\n    const std::vector<Point<T>>&\
    \ input,\n    long double eps = 1e-12L\n) {\n    using namespace steiner_convex_decomposition_detail;\n\
    \    auto prepared = prepare_polygon(input, eps);\n    if (!prepared.has_value())\
    \ return std::nullopt;\n    const std::vector<PointType>& polygon = *prepared;\n\
    \    const int size = static_cast<int>(polygon.size());\n\n    std::vector<int>\
    \ reflex_vertices;\n    for (int index = 0; index < size; ++index) {\n       \
    \ if (\n            orientation(\n                polygon[(index + size - 1) %\
    \ size],\n                polygon[index],\n                polygon[(index + 1)\
    \ % size],\n                eps\n            ) < 0\n        ) {\n            reflex_vertices.push_back(index);\n\
    \        }\n    }\n    if (reflex_vertices.empty()) {\n        return std::vector<std::vector<PointType>>(1,\
    \ polygon);\n    }\n\n    BoundaryRayShooter boundary(polygon, eps);\n    DecompositionGraph\
    \ graph(polygon, reflex_vertices, eps);\n    for (const int reflex : reflex_vertices)\
    \ {\n        bool added = false;\n        for (const long double alpha : graph.candidate_alphas(reflex))\
    \ {\n            const PointType direction = graph.direction(reflex, alpha);\n\
    \            const auto hit = boundary.shoot(reflex, direction);\n           \
    \ if (!hit.has_value()) continue;\n            if (graph.add_cut(reflex, direction,\
    \ *hit)) {\n                added = true;\n                break;\n          \
    \  }\n        }\n        if (!added) return std::nullopt;\n    }\n    return graph.faces(reflex_vertices.size()\
    \ + 1);\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 5 \"\
    verify/geometry/steiner_convex_decomposition.test.cpp\"\n\n#line 12 \"verify/geometry/steiner_convex_decomposition.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 6 \"utilities/fast_io.hpp\"\
    \n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\n\
    #include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 14 \"verify/geometry/steiner_convex_decomposition.test.cpp\"\
    \n\nnamespace {\n\nusing namespace m1une::geometry;\nusing P = Point<long double>;\n\
    \nint reflex_count(const std::vector<P>& polygon) {\n    int result = 0;\n   \
    \ for (std::size_t index = 0; index < polygon.size(); ++index) {\n        if (\n\
    \            orientation(\n                polygon[(index + polygon.size() - 1)\
    \ % polygon.size()],\n                polygon[index],\n                polygon[(index\
    \ + 1) % polygon.size()]\n            ) < 0\n        ) {\n            ++result;\n\
    \        }\n    }\n    return result;\n}\n\nvoid assert_valid(const std::vector<P>&\
    \ polygon) {\n    const auto decomposition = steiner_convex_decomposition(polygon);\n\
    \    assert(decomposition.has_value());\n    assert(\n        decomposition->size()\
    \ ==\n        static_cast<std::size_t>(reflex_count(polygon) + 1)\n    );\n\n\
    \    long double area_sum = 0;\n    for (const std::vector<P>& part : *decomposition)\
    \ {\n        assert(part.size() >= 3);\n        assert(polygon_area2(part) > 0);\n\
    \        assert(is_convex_polygon(part));\n        area_sum += polygon_area(part);\n\
    \        for (const P& point : part) {\n            assert(\n                point_in_polygon(polygon,\
    \ point, 1e-9L) !=\n                PointInPolygon::Outside\n            );\n\
    \        }\n        for (std::size_t index = 0; index < part.size(); ++index)\
    \ {\n            const P midpoint =\n                (part[index] + part[(index\
    \ + 1) % part.size()]) / 2;\n            assert(\n                point_in_polygon(polygon,\
    \ midpoint, 1e-9L) !=\n                PointInPolygon::Outside\n            );\n\
    \        }\n    }\n    const long double expected = polygon_area(polygon);\n \
    \   assert(\n        std::fabs(area_sum - expected) <=\n        1e-8L * std::max(1.0L,\
    \ expected)\n    );\n}\n\nvoid test_fixed() {\n    std::vector<P> convex;\n  \
    \  convex.emplace_back(0, 0);\n    convex.emplace_back(6, 0);\n    convex.emplace_back(6,\
    \ 4);\n    convex.emplace_back(0, 4);\n    assert_valid(convex);\n\n    std::vector<P>\
    \ l_shape;\n    l_shape.emplace_back(0, 0);\n    l_shape.emplace_back(5, 0);\n\
    \    l_shape.emplace_back(5, 2);\n    l_shape.emplace_back(2, 2);\n    l_shape.emplace_back(2,\
    \ 5);\n    l_shape.emplace_back(0, 5);\n    assert_valid(l_shape);\n\n    std::vector<P>\
    \ u_shape;\n    u_shape.emplace_back(0, 0);\n    u_shape.emplace_back(6, 0);\n\
    \    u_shape.emplace_back(6, 6);\n    u_shape.emplace_back(4, 6);\n    u_shape.emplace_back(4,\
    \ 2);\n    u_shape.emplace_back(2, 2);\n    u_shape.emplace_back(2, 6);\n    u_shape.emplace_back(0,\
    \ 6);\n    assert_valid(u_shape);\n\n    std::vector<P> crossing_cuts;\n    crossing_cuts.emplace_back(0,\
    \ 0);\n    crossing_cuts.emplace_back(6, 0);\n    crossing_cuts.emplace_back(6,\
    \ 2);\n    crossing_cuts.emplace_back(4, 2);\n    crossing_cuts.emplace_back(4,\
    \ 4);\n    crossing_cuts.emplace_back(6, 4);\n    crossing_cuts.emplace_back(6,\
    \ 6);\n    crossing_cuts.emplace_back(0, 6);\n    crossing_cuts.emplace_back(0,\
    \ 4);\n    crossing_cuts.emplace_back(2, 4);\n    crossing_cuts.emplace_back(2,\
    \ 2);\n    crossing_cuts.emplace_back(0, 2);\n    assert_valid(crossing_cuts);\n\
    \n    std::vector<P> few_reflex;\n    few_reflex.emplace_back(10, 0);\n    few_reflex.emplace_back(8,\
    \ 6);\n    few_reflex.emplace_back(3, 10);\n    few_reflex.emplace_back(0, 0);\n\
    \    few_reflex.emplace_back(-8, 6);\n    few_reflex.emplace_back(-10, 0);\n \
    \   few_reflex.emplace_back(-8, -6);\n    few_reflex.emplace_back(-3, -10);\n\
    \    few_reflex.emplace_back(3, -10);\n    few_reflex.emplace_back(8, -6);\n \
    \   assert(reflex_count(few_reflex) == 1);\n    assert_valid(few_reflex);\n\n\
    \    std::vector<P> one_reflex_many_vertices;\n    constexpr int many_size = 256;\n\
    \    one_reflex_many_vertices.reserve(many_size);\n    for (int index = 0; index\
    \ < many_size; ++index) {\n        const long double angle =\n            2 *\
    \ std::numbers::pi_v<long double> * index / many_size;\n        const long double\
    \ radius = index == 0 ? 1.0L : 10.0L;\n        one_reflex_many_vertices.emplace_back(\n\
    \            radius * std::cos(angle), radius * std::sin(angle)\n        );\n\
    \    }\n    assert(reflex_count(one_reflex_many_vertices) == 1);\n    assert_valid(one_reflex_many_vertices);\n\
    \n    std::reverse(l_shape.begin(), l_shape.end());\n    const auto clockwise\
    \ = steiner_convex_decomposition(l_shape);\n    assert(clockwise.has_value() &&\
    \ clockwise->size() == 2);\n\n    std::vector<P> redundant;\n    redundant.emplace_back(0,\
    \ 0);\n    redundant.emplace_back(3, 0);\n    redundant.emplace_back(6, 0);\n\
    \    redundant.emplace_back(6, 2);\n    redundant.emplace_back(2, 2);\n    redundant.emplace_back(2,\
    \ 6);\n    redundant.emplace_back(0, 6);\n    redundant.emplace_back(0, 0);\n\
    \    const auto cleaned = steiner_convex_decomposition(redundant);\n    assert(cleaned.has_value()\
    \ && cleaned->size() == 2);\n\n    std::vector<P> degenerate;\n    degenerate.emplace_back(0,\
    \ 0);\n    degenerate.emplace_back(1, 0);\n    degenerate.emplace_back(2, 0);\n\
    \    assert(!steiner_convex_decomposition(degenerate).has_value());\n}\n\nvoid\
    \ test_random_radial_polygons() {\n    std::mt19937_64 generator(0x57e1deULL);\n\
    \    std::uniform_real_distribution<long double> jitter(-0.08L, 0.08L);\n    std::uniform_real_distribution<long\
    \ double> radius(3.0L, 12.0L);\n    for (int iteration = 0; iteration < 300; ++iteration)\
    \ {\n        const int size = 5 + static_cast<int>(generator() % 20);\n      \
    \  std::vector<P> polygon;\n        polygon.reserve(size);\n        for (int index\
    \ = 0; index < size; ++index) {\n            const long double angle =\n     \
    \           2 * std::numbers::pi_v<long double> * index / size +\n           \
    \     jitter(generator) / size;\n            const long double length = radius(generator);\n\
    \            polygon.emplace_back(\n                length * std::cos(angle),\
    \ length * std::sin(angle)\n            );\n        }\n        if (!is_simple_polygon(polygon))\
    \ {\n            --iteration;\n            continue;\n        }\n        assert_valid(polygon);\n\
    \    }\n}\n\nvoid test_random_monotone_polygons() {\n    std::mt19937_64 generator(0xc0ffee57ULL);\n\
    \    std::uniform_real_distribution<long double> height(1.0L, 20.0L);\n    for\
    \ (int iteration = 0; iteration < 300; ++iteration) {\n        const int half\
    \ = 3 + static_cast<int>(generator() % 15);\n        std::vector<P> polygon;\n\
    \        polygon.reserve(2 * half);\n        for (int index = 0; index < half;\
    \ ++index) {\n            polygon.emplace_back(index, -height(generator));\n \
    \       }\n        for (int index = half - 1; index >= 0; --index) {\n       \
    \     polygon.emplace_back(index, height(generator));\n        }\n        assert(is_simple_polygon(polygon));\n\
    \        assert(polygon_area2(polygon) > 0);\n        assert_valid(polygon);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_random_radial_polygons();\n\
    \    test_random_monotone_polygons();\n\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n    int size;\n    fast_input\
    \ >> size;\n    std::vector<Point<long long>> polygon(size);\n    for (auto& point\
    \ : polygon) fast_input >> point.x >> point.y;\n    fast_output << (is_convex_polygon(polygon)\
    \ ? 1 : 0) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B\"\
    \n\n#include \"../../geometry/convex_polygon.hpp\"\n#include \"../../geometry/steiner_convex_decomposition.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <numbers>\n\
    #include <random>\n#include <vector>\n\n#include \"../../utilities/fast_io.hpp\"\
    \n\nnamespace {\n\nusing namespace m1une::geometry;\nusing P = Point<long double>;\n\
    \nint reflex_count(const std::vector<P>& polygon) {\n    int result = 0;\n   \
    \ for (std::size_t index = 0; index < polygon.size(); ++index) {\n        if (\n\
    \            orientation(\n                polygon[(index + polygon.size() - 1)\
    \ % polygon.size()],\n                polygon[index],\n                polygon[(index\
    \ + 1) % polygon.size()]\n            ) < 0\n        ) {\n            ++result;\n\
    \        }\n    }\n    return result;\n}\n\nvoid assert_valid(const std::vector<P>&\
    \ polygon) {\n    const auto decomposition = steiner_convex_decomposition(polygon);\n\
    \    assert(decomposition.has_value());\n    assert(\n        decomposition->size()\
    \ ==\n        static_cast<std::size_t>(reflex_count(polygon) + 1)\n    );\n\n\
    \    long double area_sum = 0;\n    for (const std::vector<P>& part : *decomposition)\
    \ {\n        assert(part.size() >= 3);\n        assert(polygon_area2(part) > 0);\n\
    \        assert(is_convex_polygon(part));\n        area_sum += polygon_area(part);\n\
    \        for (const P& point : part) {\n            assert(\n                point_in_polygon(polygon,\
    \ point, 1e-9L) !=\n                PointInPolygon::Outside\n            );\n\
    \        }\n        for (std::size_t index = 0; index < part.size(); ++index)\
    \ {\n            const P midpoint =\n                (part[index] + part[(index\
    \ + 1) % part.size()]) / 2;\n            assert(\n                point_in_polygon(polygon,\
    \ midpoint, 1e-9L) !=\n                PointInPolygon::Outside\n            );\n\
    \        }\n    }\n    const long double expected = polygon_area(polygon);\n \
    \   assert(\n        std::fabs(area_sum - expected) <=\n        1e-8L * std::max(1.0L,\
    \ expected)\n    );\n}\n\nvoid test_fixed() {\n    std::vector<P> convex;\n  \
    \  convex.emplace_back(0, 0);\n    convex.emplace_back(6, 0);\n    convex.emplace_back(6,\
    \ 4);\n    convex.emplace_back(0, 4);\n    assert_valid(convex);\n\n    std::vector<P>\
    \ l_shape;\n    l_shape.emplace_back(0, 0);\n    l_shape.emplace_back(5, 0);\n\
    \    l_shape.emplace_back(5, 2);\n    l_shape.emplace_back(2, 2);\n    l_shape.emplace_back(2,\
    \ 5);\n    l_shape.emplace_back(0, 5);\n    assert_valid(l_shape);\n\n    std::vector<P>\
    \ u_shape;\n    u_shape.emplace_back(0, 0);\n    u_shape.emplace_back(6, 0);\n\
    \    u_shape.emplace_back(6, 6);\n    u_shape.emplace_back(4, 6);\n    u_shape.emplace_back(4,\
    \ 2);\n    u_shape.emplace_back(2, 2);\n    u_shape.emplace_back(2, 6);\n    u_shape.emplace_back(0,\
    \ 6);\n    assert_valid(u_shape);\n\n    std::vector<P> crossing_cuts;\n    crossing_cuts.emplace_back(0,\
    \ 0);\n    crossing_cuts.emplace_back(6, 0);\n    crossing_cuts.emplace_back(6,\
    \ 2);\n    crossing_cuts.emplace_back(4, 2);\n    crossing_cuts.emplace_back(4,\
    \ 4);\n    crossing_cuts.emplace_back(6, 4);\n    crossing_cuts.emplace_back(6,\
    \ 6);\n    crossing_cuts.emplace_back(0, 6);\n    crossing_cuts.emplace_back(0,\
    \ 4);\n    crossing_cuts.emplace_back(2, 4);\n    crossing_cuts.emplace_back(2,\
    \ 2);\n    crossing_cuts.emplace_back(0, 2);\n    assert_valid(crossing_cuts);\n\
    \n    std::vector<P> few_reflex;\n    few_reflex.emplace_back(10, 0);\n    few_reflex.emplace_back(8,\
    \ 6);\n    few_reflex.emplace_back(3, 10);\n    few_reflex.emplace_back(0, 0);\n\
    \    few_reflex.emplace_back(-8, 6);\n    few_reflex.emplace_back(-10, 0);\n \
    \   few_reflex.emplace_back(-8, -6);\n    few_reflex.emplace_back(-3, -10);\n\
    \    few_reflex.emplace_back(3, -10);\n    few_reflex.emplace_back(8, -6);\n \
    \   assert(reflex_count(few_reflex) == 1);\n    assert_valid(few_reflex);\n\n\
    \    std::vector<P> one_reflex_many_vertices;\n    constexpr int many_size = 256;\n\
    \    one_reflex_many_vertices.reserve(many_size);\n    for (int index = 0; index\
    \ < many_size; ++index) {\n        const long double angle =\n            2 *\
    \ std::numbers::pi_v<long double> * index / many_size;\n        const long double\
    \ radius = index == 0 ? 1.0L : 10.0L;\n        one_reflex_many_vertices.emplace_back(\n\
    \            radius * std::cos(angle), radius * std::sin(angle)\n        );\n\
    \    }\n    assert(reflex_count(one_reflex_many_vertices) == 1);\n    assert_valid(one_reflex_many_vertices);\n\
    \n    std::reverse(l_shape.begin(), l_shape.end());\n    const auto clockwise\
    \ = steiner_convex_decomposition(l_shape);\n    assert(clockwise.has_value() &&\
    \ clockwise->size() == 2);\n\n    std::vector<P> redundant;\n    redundant.emplace_back(0,\
    \ 0);\n    redundant.emplace_back(3, 0);\n    redundant.emplace_back(6, 0);\n\
    \    redundant.emplace_back(6, 2);\n    redundant.emplace_back(2, 2);\n    redundant.emplace_back(2,\
    \ 6);\n    redundant.emplace_back(0, 6);\n    redundant.emplace_back(0, 0);\n\
    \    const auto cleaned = steiner_convex_decomposition(redundant);\n    assert(cleaned.has_value()\
    \ && cleaned->size() == 2);\n\n    std::vector<P> degenerate;\n    degenerate.emplace_back(0,\
    \ 0);\n    degenerate.emplace_back(1, 0);\n    degenerate.emplace_back(2, 0);\n\
    \    assert(!steiner_convex_decomposition(degenerate).has_value());\n}\n\nvoid\
    \ test_random_radial_polygons() {\n    std::mt19937_64 generator(0x57e1deULL);\n\
    \    std::uniform_real_distribution<long double> jitter(-0.08L, 0.08L);\n    std::uniform_real_distribution<long\
    \ double> radius(3.0L, 12.0L);\n    for (int iteration = 0; iteration < 300; ++iteration)\
    \ {\n        const int size = 5 + static_cast<int>(generator() % 20);\n      \
    \  std::vector<P> polygon;\n        polygon.reserve(size);\n        for (int index\
    \ = 0; index < size; ++index) {\n            const long double angle =\n     \
    \           2 * std::numbers::pi_v<long double> * index / size +\n           \
    \     jitter(generator) / size;\n            const long double length = radius(generator);\n\
    \            polygon.emplace_back(\n                length * std::cos(angle),\
    \ length * std::sin(angle)\n            );\n        }\n        if (!is_simple_polygon(polygon))\
    \ {\n            --iteration;\n            continue;\n        }\n        assert_valid(polygon);\n\
    \    }\n}\n\nvoid test_random_monotone_polygons() {\n    std::mt19937_64 generator(0xc0ffee57ULL);\n\
    \    std::uniform_real_distribution<long double> height(1.0L, 20.0L);\n    for\
    \ (int iteration = 0; iteration < 300; ++iteration) {\n        const int half\
    \ = 3 + static_cast<int>(generator() % 15);\n        std::vector<P> polygon;\n\
    \        polygon.reserve(2 * half);\n        for (int index = 0; index < half;\
    \ ++index) {\n            polygon.emplace_back(index, -height(generator));\n \
    \       }\n        for (int index = half - 1; index >= 0; --index) {\n       \
    \     polygon.emplace_back(index, height(generator));\n        }\n        assert(is_simple_polygon(polygon));\n\
    \        assert(polygon_area2(polygon) > 0);\n        assert_valid(polygon);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_random_radial_polygons();\n\
    \    test_random_monotone_polygons();\n\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n    int size;\n    fast_input\
    \ >> size;\n    std::vector<Point<long long>> polygon(size);\n    for (auto& point\
    \ : polygon) fast_input >> point.x >> point.y;\n    fast_output << (is_convex_polygon(polygon)\
    \ ? 1 : 0) << '\\n';\n}\n"
  dependsOn:
  - geometry/convex_polygon.hpp
  - geometry/convex_hull.hpp
  - geometry/point.hpp
  - geometry/half_plane_intersection.hpp
  - geometry/line.hpp
  - geometry/polygon.hpp
  - geometry/ray.hpp
  - geometry/steiner_convex_decomposition.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/steiner_convex_decomposition.test.cpp
  requiredBy: []
  timestamp: '2026-07-22 13:48:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/steiner_convex_decomposition.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/steiner_convex_decomposition.test.cpp
- /verify/verify/geometry/steiner_convex_decomposition.test.cpp.html
title: verify/geometry/steiner_convex_decomposition.test.cpp
---
