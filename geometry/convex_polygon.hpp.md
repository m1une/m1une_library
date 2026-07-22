---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/convex_hull.hpp
    title: Convex Hull
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
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
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
    path: verify/geometry/polygon_operations.test.cpp
    title: verify/geometry/polygon_operations.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/convex_polygon.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <cmath>\n#include <concepts>\n\
    #include <cstddef>\n#include <deque>\n#include <limits>\n#include <numbers>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\n#line 1 \"geometry/convex_hull.hpp\"\
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
    \ result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_CONVEX_POLYGON_HPP\n#define M1UNE_GEOMETRY_CONVEX_POLYGON_HPP\
    \ 1\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <concepts>\n#include <cstddef>\n#include <deque>\n#include <limits>\n\
    #include <numbers>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \n#include \"convex_hull.hpp\"\n#include \"half_plane_intersection.hpp\"\n#include\
    \ \"polygon.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\nnamespace convex_polygon_detail\
    \ {\n\ninline std::vector<Point<long double>> clean_polygon(\n    std::vector<Point<long\
    \ double>> polygon,\n    long double eps\n) {\n    if (polygon.empty()) return\
    \ polygon;\n\n    std::vector<Point<long double>> deduplicated;\n    for (const\
    \ Point<long double>& point : polygon) {\n        if (\n            deduplicated.empty()\
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
    \ result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_GEOMETRY_CONVEX_POLYGON_HPP\n"
  dependsOn:
  - geometry/convex_hull.hpp
  - geometry/point.hpp
  - geometry/half_plane_intersection.hpp
  - geometry/line.hpp
  - geometry/polygon.hpp
  - geometry/ray.hpp
  isVerificationFile: false
  path: geometry/convex_polygon.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-22 02:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/convex_polygon.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/polygon_operations.test.cpp
  - verify/geometry/convex_decomposition.test.cpp
  - verify/geometry/is_convex_polygon.test.cpp
  - verify/geometry/centroid.test.cpp
  - verify/geometry/convex_diameter.test.cpp
documentation_of: geometry/convex_polygon.hpp
layout: document
title: Convex Polygons
---

## Overview

`convex_polygon.hpp` provides algorithms specialized for convex polygons and a
`ConvexPolygon<T>` query object. The query object normalizes an ordered convex
boundary once, then supports point containment, directional extrema, tangents,
and chain-area queries efficiently.

The free functions cover convexity testing, normalization, triangulation,
diameter, half-plane cuts, intersection construction, Minkowski sums, and
intersection and distance between two convex polygons. Pair queries have both
linear-time vector overloads and sublinear overloads for already-normalized
`ConvexPolygon<T>` objects. They can also return a pair of closest points,
including points in edge interiors.

Polygons are represented by `std::vector<Point<T>>`. Their first point is not
repeated at the end unless a function explicitly accepts and removes a closing
copy.

## Basic Functions

```cpp
template <Coordinate T>
bool is_convex_polygon(
    const std::vector<Point<T>>& polygon,
    bool strict = false,
    long double eps = 1e-12L
);

template <Coordinate T>
std::vector<Point<T>> normalize_convex_polygon(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
);

template <Coordinate T>
PointInPolygon point_in_convex_polygon(
    const std::vector<Point<T>>& polygon,
    const Point<T>& point,
    long double eps = 1e-12L
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `is_convex_polygon(polygon, strict, eps)` | Tests the turns of an ordered simple boundary. With `strict == true`, collinear consecutive edges and all-collinear polygons are rejected. | $O(N)$ |
| `normalize_convex_polygon(polygon, eps)` | Removes a closing copy, consecutive duplicates, and redundant collinear vertices; makes the order counterclockwise; and rotates the lowest `(y, x)` vertex to index `0`. | $O(N)$ |
| `point_in_convex_polygon(polygon, point, eps)` | Classifies a point against a strict convex boundary in clockwise or counterclockwise order. | $O(\log N)$ |

`is_convex_polygon` assumes the vertices describe a simple polygon boundary.
It is not a general self-intersection test. Use `is_simple_polygon` from
`polygon.hpp` when arbitrary input must be validated. In non-strict mode, an
all-collinear boundary with at least three vertices is considered convex.

For predictable logarithmic containment, pass a strict boundary or use
`ConvexPolygon<T>`, which normalizes the input first. Empty polygons, points,
and segments are also classified by `point_in_convex_polygon`.

## Query Object

```cpp
template <Coordinate T>
class ConvexPolygon {
public:
    using Wide = wide_type<T>;

    explicit ConvexPolygon(
        std::vector<Point<T>> polygon,
        long double eps = 1e-12L
    );

    int size() const noexcept;
    bool empty() const noexcept;
    const std::vector<Point<T>>& vertices() const noexcept;
    const Point<T>& operator[](int index) const;
    Wide area2() const;
    Wide chain_area2(int first, int last) const;
    PointInPolygon contains(const Point<T>& point) const;
    std::pair<Wide, int> min_dot(const Point<T>& direction) const;
    std::pair<Wide, int> max_dot(const Point<T>& direction) const;
    std::pair<int, int> tangent_vertices(const Point<T>& point) const;
};

template <Coordinate T>
std::optional<Point<long double>> centroid(
    const ConvexPolygon<T>& polygon,
    long double eps = 1e-12L
);
```

| Operation | Description | Complexity |
| --- | --- | --- |
| `ConvexPolygon(polygon, eps)` | Normalizes an ordered convex boundary and builds doubled prefix areas. | $O(N)$ time and memory |
| `size()`, `empty()`, `vertices()`, `operator[]` | Access the normalized boundary. | $O(1)$ |
| `area2()` | Returns signed twice-area. A nondegenerate normalized polygon has positive area. | $O(1)$ |
| `chain_area2(first, last)` | Returns signed twice-area enclosed by the counterclockwise chain from `first` through `last` and the chord back to `first`. | $O(1)$ |
| `contains(point)` | Classifies a point as `Outside`, `Boundary`, or `Inside`. | $O(\log N)$ |
| `min_dot(direction)`, `max_dot(direction)` | Returns the extreme dot product and one vertex attaining it. | $O(\log N)$ |
| `tangent_vertices(point)` | Returns the two tangent-vertex indices for an external point. | $O(\log N)$ |
| `centroid(polygon, eps)` | Returns the uniformly filled polygon's centroid, or `nullopt` for an empty or zero-area query object. | $O(N)$ |

`min_dot` and `max_dot` require a nonempty polygon. `tangent_vertices`
requires at least three vertices and a point strictly outside the polygon.
Ties may return either endpoint of an extreme edge. No ordering is promised
between the two tangent indices.

`centroid` is a free geometry-wide overload rather than a convex-only member.
The same name also supports points, segments, triangles, circles, and general
simple polygon vectors. The convex overload delegates to the general polygon
area-centroid calculation; preprocessing the query object does not make this
particular operation constant-time.

## Construction and Combination

```cpp
template <Coordinate T>
std::vector<std::array<Point<T>, 3>> triangulate_convex_polygon(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
);

template <Coordinate T>
wide_type<T> convex_diameter2(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
);

template <Coordinate T>
std::vector<Point<long double>> convex_cut(
    const std::vector<Point<T>>& polygon,
    const Line<T>& boundary,
    long double eps = 1e-12L
);

template <Coordinate T>
std::vector<Point<long double>> convex_polygon_intersection(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
std::vector<Point<T>> minkowski_sum(
    std::vector<Point<T>> first,
    std::vector<Point<T>> second,
    long double eps = 1e-12L
);

template <Coordinate T>
bool convex_polygons_intersect(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
long double convex_polygons_distance(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
std::pair<Point<long double>, Point<long double>>
convex_polygons_closest_points(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
bool convex_polygons_intersect(
    const ConvexPolygon<T>& first,
    const ConvexPolygon<T>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
long double convex_polygons_distance(
    const ConvexPolygon<T>& first,
    const ConvexPolygon<T>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
std::pair<Point<long double>, Point<long double>>
convex_polygons_closest_points(
    const ConvexPolygon<T>& first,
    const ConvexPolygon<T>& second,
    long double eps = 1e-12L
);
```

### Vector overloads

| Function | Description | Complexity |
| --- | --- | --- |
| `triangulate_convex_polygon(polygon, eps)` | Returns a counterclockwise fan triangulation after normalization. | $O(N)$ |
| `convex_diameter2(polygon, eps)` | Returns the maximum squared distance between two vertices using rotating calipers. | $O(N)$ |
| `convex_cut(polygon, boundary, eps)` | Intersects the polygon with the closed half-plane to the left of the directed boundary line. | $O(N)$ |
| `convex_polygon_intersection(first, second, eps)` | Constructs the closed intersection, including point or segment degeneracies, by merging the polygons' angle-sorted half-planes. | $O(N+M)$ |
| `minkowski_sum(first, second, eps)` | Constructs the Minkowski sum and returns a normalized boundary. | $O(N+M)$ |
| `convex_polygons_intersect(first, second, eps)` | Tests whether two closed convex polygons intersect. | $O(N+M)$ |
| `convex_polygons_distance(first, second, eps)` | Returns the minimum Euclidean distance between two closed convex polygons. | $O(N+M)$ |
| `convex_polygons_closest_points(first, second, eps)` | Returns one pair of points attaining the minimum distance. | $O(N+M)$ |

The $O(N+M)$ bounds in this table apply when `first` and `second` are
`std::vector<Point<T>>`. These overloads normalize the boundaries on every
call. The intersection and distance queries materialize their Minkowski
difference; the closest-points query constructs two temporary query objects.
All three use $O(N+M)$ temporary memory.

### Preprocessed pair-query overloads

| Function | Description | Complexity |
| --- | --- | --- |
| `convex_polygons_intersect(first, second, eps)` | Tests whether two closed `ConvexPolygon<T>` objects intersect. | $O(\log(N+M)\log(\min(N,M)+1))$ time, $O(1)$ extra memory |
| `convex_polygons_distance(first, second, eps)` | Returns the minimum Euclidean distance between two closed `ConvexPolygon<T>` objects. | $O(\log(N+M)\log(\min(N,M)+1))$ time, $O(1)$ extra memory |
| `convex_polygons_closest_points(first, second, eps)` | Returns one pair of points attaining the minimum distance between two closed `ConvexPolygon<T>` objects. | $O(\log(N+M)\log(\min(N,M)+1))$ time, $O(1)$ extra memory |

These bounds apply only when both arguments are `ConvexPolygon<T>` objects.
Constructing those objects still costs $O(N+M)$ total time and memory. The
overloads are therefore useful when the same polygons participate in multiple
queries, or when the query objects already exist for other operations.

The product of logarithms is intentional: the implementation performs
$O(\log(N+M))$ searches on a virtual Minkowski-difference boundary, and one
random access into that merged boundary costs
$O(\log(\min(N,M)+1))$. It does not build or cache an $N+M$-vertex pairwise
boundary. In particular, this complexity must not be read as
$O(\log N+\log M)$.

Here $N$ and $M$ are the numbers of vertices after each query object's
normalization. Empty query objects are invalid; points and segments are
supported. All pair-query overloads treat the polygons as closed, so sharing
a vertex or edge counts as intersection and makes the distance zero.
`convex_polygons_closest_points` returns `{first_point, second_point}`, where
`first_point` belongs to the first polygon and `second_point` belongs to the
second. The returned points use `long double` because a closest point may lie
inside an edge. If the polygons intersect, both returned points describe one
common point; when several answers exist, any one may be returned. `eps`
controls geometric classification during the pair query; each object's
constructor tolerance has already been applied during its normalization.

`convex_cut` and `convex_polygon_intersection` return `Point<long double>`
because new vertices may be non-integral. A cut boundary is directed and must
contain two distinct points. Intersection construction requires two
nondegenerate convex inputs; the resulting intersection itself may degenerate
to a point or segment.

Minkowski addition is also used for the vector pair queries. `minkowski_sum`,
the three vector pair queries, and the three preprocessed pair-query overloads
require nonempty inputs. Coordinate negation, addition, and edge differences
must fit `T`.
Cross products, dot products, squared distances, and areas must fit
`wide_type<T>`.

## Example

```cpp
#include "geometry/convex_polygon.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> vertices;
    vertices.emplace_back(0, 0);
    vertices.emplace_back(4, 0);
    vertices.emplace_back(4, 4);
    vertices.emplace_back(0, 4);

    m1une::geometry::ConvexPolygon<long long> polygon(vertices);
    std::cout << int(polygon.contains(Point(2, 2))) << "\n";  // 2

    auto maximum = polygon.max_dot(Point(1, 0));
    std::cout << maximum.first << "\n";  // 4

    m1une::geometry::Line<long long> boundary{
        Point(2, -1),
        Point(2, 5)
    };
    auto left_half = m1une::geometry::convex_cut(vertices, boundary);
    std::cout << m1une::geometry::polygon_area(left_half) << "\n";  // 8
}
```
