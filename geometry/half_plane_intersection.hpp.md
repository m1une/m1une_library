---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: Lines and Segments
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
    path: verify/geometry/half_plane_intersection.test.cpp
    title: verify/geometry/half_plane_intersection.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/half_plane_intersection_random.test.cpp
    title: verify/geometry/half_plane_intersection_random.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/is_convex_polygon.test.cpp
    title: verify/geometry/is_convex_polygon.test.cpp
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
  bundledCode: "#line 1 \"geometry/half_plane_intersection.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <cstddef>\n#include <deque>\n#include\
    \ <limits>\n#include <numbers>\n#include <optional>\n#include <random>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"geometry/line.hpp\"\n\n\n\n#line 8\
    \ \"geometry/line.hpp\"\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#line 5 \"geometry/point.hpp\"\
    \n#include <concepts>\n#line 7 \"geometry/point.hpp\"\n#include <type_traits>\n\
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
    \ geometry\n}  // namespace m1une\n\n\n#line 10 \"geometry/line.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct Line {\n  \
    \  Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate T>\nstruct Segment\
    \ {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate T>\nconstexpr\
    \ Point<long double> centroid(const Segment<T>& segment) {\n    return Point<long\
    \ double>(\n        (\n            static_cast<long double>(segment.a.x) +\n \
    \           static_cast<long double>(segment.b.x)\n        ) / 2,\n        (\n\
    \            static_cast<long double>(segment.a.y) +\n            static_cast<long\
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
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_HALF_PLANE_INTERSECTION_HPP\n#define M1UNE_GEOMETRY_HALF_PLANE_INTERSECTION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <cstddef>\n\
    #include <deque>\n#include <limits>\n#include <numbers>\n#include <optional>\n\
    #include <random>\n#include <utility>\n#include <vector>\n\n#include \"line.hpp\"\
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
    \ m1une\n\n#endif  // M1UNE_GEOMETRY_HALF_PLANE_INTERSECTION_HPP\n"
  dependsOn:
  - geometry/line.hpp
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/half_plane_intersection.hpp
  requiredBy:
  - geometry/all.hpp
  - geometry/convex_polygon.hpp
  timestamp: '2026-07-22 02:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/convex_polygon.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/steiner_convex_decomposition.test.cpp
  - verify/geometry/polygon_operations.test.cpp
  - verify/geometry/convex_decomposition.test.cpp
  - verify/geometry/is_convex_polygon.test.cpp
  - verify/geometry/centroid.test.cpp
  - verify/geometry/half_plane_intersection.test.cpp
  - verify/geometry/convex_diameter.test.cpp
  - verify/geometry/half_plane_intersection_random.test.cpp
documentation_of: geometry/half_plane_intersection.hpp
layout: document
title: Half-Plane Intersection
---

## Overview

`half_plane_intersection` constructs the bounded convex polygon common to a
collection of closed half-planes. A half-plane is represented by a directed
`Line<T>`: the legal side is the boundary line and everything to its left.

For a line from `a` to `b`, a point `p` is legal exactly when

$$
\operatorname{cross}(b-a,p-a) \geq 0.
$$

The result reports whether the intersection is empty, unbounded, bounded with
zero area, or a bounded positive-area polygon. Polygon vertices use
`long double` because intersections need not have integral coordinates.

## Result

```cpp
enum class HalfPlaneIntersectionStatus {
    Empty,
    Unbounded,
    Degenerate,
    Bounded,
};

struct HalfPlaneIntersectionResult {
    HalfPlaneIntersectionStatus status;
    std::vector<Point<long double>> polygon;
};
```

| Status | Meaning |
| --- | --- |
| `Empty` | No point satisfies every half-plane. |
| `Unbounded` | The intersection is nonempty and unbounded, including an unbounded line or ray. |
| `Degenerate` | The intersection is bounded but has zero area, so it is a point or segment. |
| `Bounded` | The intersection has positive area; `polygon` contains its boundary. |

`polygon` is empty for every status except `Bounded`.

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `half_plane_intersection(half_planes, eps)` | Classifies the intersection and returns its polygon when it is bounded with positive area. | Expected $O(N\log N)$ time, $O(N^2)$ worst-case time, and $O(N)$ memory |

The exact signature is:

```cpp
template <Coordinate T>
HalfPlaneIntersectionResult half_plane_intersection(
    const std::vector<Line<T>>& half_planes,
    long double eps = 1e-12L
);
```

Every boundary line must have distinct endpoints. For `Bounded`, the returned
polygon is counterclockwise, starts at its lexicographically smallest vertex,
and does not repeat that vertex at the end. Closed boundaries are included.
The empty collection of constraints has status `Unbounded` because its
intersection is the entire plane.

Feasibility is checked by randomized incremental two-dimensional linear
programming, which gives the expected time bound above. The tolerance is
applied after boundary directions are normalized, so it acts as both an
angular and a signed-distance tolerance.

## Example

```cpp
#include "geometry/half_plane_intersection.hpp"

#include <iostream>
#include <vector>

int main() {
    using namespace m1une::geometry;
    using P = Point<long double>;

    std::vector<Line<long double>> half_planes;
    half_planes.push_back(Line<long double>{P(0, 0), P(2, 0)});
    half_planes.push_back(Line<long double>{P(2, 0), P(2, 2)});
    half_planes.push_back(Line<long double>{P(2, 2), P(0, 2)});
    half_planes.push_back(Line<long double>{P(0, 2), P(0, 0)});

    auto result = half_plane_intersection(half_planes);
    if (result.status == HalfPlaneIntersectionStatus::Bounded) {
        std::cout << result.polygon.size() << "\n";  // 4
    }
}
```
