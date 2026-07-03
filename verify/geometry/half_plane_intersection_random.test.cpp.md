---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/half_plane_intersection.hpp
    title: Half-Plane Intersection
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: Lines and Segments
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
  bundledCode: "#line 1 \"verify/geometry/half_plane_intersection_random.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"geometry/half_plane_intersection.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <cstddef>\n\
    #include <deque>\n#include <optional>\n#include <vector>\n\n#line 1 \"geometry/line.hpp\"\
    \n\n\n\n#line 8 \"geometry/line.hpp\"\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n\
    #line 5 \"geometry/point.hpp\"\n#include <concepts>\n#line 7 \"geometry/point.hpp\"\
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
    \ {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate T>\nbool on_line(\n\
    \    const Line<T>& line,\n    const Point<T>& point,\n    long double eps = 1e-12L\n\
    ) {\n    assert(line.a != line.b);\n    return orientation(line.a, line.b, point,\
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
    \n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 13 \"geometry/half_plane_intersection.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\nnamespace half_plane_intersection_detail\
    \ {\n\nstruct HalfPlane {\n    Point<long double> point;\n    Point<long double>\
    \ direction;\n};\n\ninline int direction_half(const Point<long double>& direction)\
    \ {\n    return direction.y > 0 || (direction.y == 0 && direction.x >= 0) ? 0\
    \ : 1;\n}\n\ninline bool direction_less(const HalfPlane& first, const HalfPlane&\
    \ second) {\n    int first_half = direction_half(first.direction);\n    int second_half\
    \ = direction_half(second.direction);\n    if (first_half != second_half) return\
    \ first_half < second_half;\n    return cross(first.direction, second.direction)\
    \ > 0;\n}\n\ninline bool parallel(\n    const HalfPlane& first,\n    const HalfPlane&\
    \ second,\n    long double eps\n) {\n    return std::fabs(cross(first.direction,\
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
    \    }\n    half_planes.pop_back();\n}\n\n}  // namespace half_plane_intersection_detail\n\
    \n// Each directed line keeps its closed left half-plane. Returns the vertices\
    \ of\n// a bounded intersection with positive area in counterclockwise order.\n\
    // Returns an empty vector if the intersection is empty, unbounded, or has zero\n\
    // area; these cases are not distinguished.\ntemplate <Coordinate T>\nstd::vector<Point<long\
    \ double>> half_plane_intersection(\n    const std::vector<Line<T>>& half_planes,\n\
    \    long double eps = 1e-12L\n) {\n    using half_plane_intersection_detail::HalfPlane;\n\
    \    namespace detail = half_plane_intersection_detail;\n\n    assert(eps >= 0);\n\
    \    std::vector<HalfPlane> sorted;\n    sorted.reserve(half_planes.size());\n\
    \    for (const Line<T>& line : half_planes) {\n        assert(line.a != line.b);\n\
    \        Point<long double> point(line.a);\n        Point<long double> direction\
    \ = Point<long double>(line.b) - point;\n        long double length = norm(direction);\n\
    \        direction = direction / length;\n        sorted.push_back(HalfPlane{point,\
    \ direction});\n    }\n    if (sorted.size() < 3) return {};\n\n    std::sort(sorted.begin(),\
    \ sorted.end(), detail::direction_less);\n    std::vector<HalfPlane> unique;\n\
    \    unique.reserve(sorted.size());\n    for (const HalfPlane& half_plane : sorted)\
    \ {\n        detail::merge_same_direction(unique, half_plane, eps);\n    }\n \
    \   detail::merge_cyclic_ends(unique, eps);\n    if (unique.size() < 3) return\
    \ {};\n\n    std::deque<HalfPlane> deque;\n    for (const HalfPlane& half_plane\
    \ : unique) {\n        while (deque.size() >= 2) {\n            auto point = detail::intersection(\n\
    \                deque[deque.size() - 2],\n                deque.back(),\n   \
    \             eps\n            );\n            if (!point.has_value()) return\
    \ {};\n            if (!detail::outside(half_plane, *point, eps)) break;\n   \
    \         deque.pop_back();\n        }\n        while (deque.size() >= 2) {\n\
    \            auto point = detail::intersection(deque[0], deque[1], eps);\n   \
    \         if (!point.has_value()) return {};\n            if (!detail::outside(half_plane,\
    \ *point, eps)) break;\n            deque.pop_front();\n        }\n        deque.push_back(half_plane);\n\
    \    }\n\n    while (deque.size() >= 3) {\n        auto point = detail::intersection(\n\
    \            deque[deque.size() - 2],\n            deque.back(),\n           \
    \ eps\n        );\n        if (!point.has_value()) return {};\n        if (!detail::outside(deque.front(),\
    \ *point, eps)) break;\n        deque.pop_back();\n    }\n    while (deque.size()\
    \ >= 3) {\n        auto point = detail::intersection(deque[0], deque[1], eps);\n\
    \        if (!point.has_value()) return {};\n        if (!detail::outside(deque.back(),\
    \ *point, eps)) break;\n        deque.pop_front();\n    }\n    if (deque.size()\
    \ < 3) return {};\n\n    std::vector<Point<long double>> polygon;\n    polygon.reserve(deque.size());\n\
    \    for (std::size_t index = 0; index < deque.size(); ++index) {\n        auto\
    \ point = detail::intersection(\n            deque[index],\n            deque[(index\
    \ + 1) % deque.size()],\n            eps\n        );\n        if (!point.has_value())\
    \ return {};\n        if (\n            polygon.empty() ||\n            distance(polygon.back(),\
    \ *point) > eps\n        ) {\n            polygon.push_back(*point);\n       \
    \ }\n    }\n    if (\n        polygon.size() >= 2 &&\n        distance(polygon.front(),\
    \ polygon.back()) <= eps\n    ) {\n        polygon.pop_back();\n    }\n    if\
    \ (polygon.size() < 3) return {};\n\n    long double signed_area2 = 0;\n    Point<long\
    \ double> origin = polygon.front();\n    for (std::size_t index = 1; index + 1\
    \ < polygon.size(); ++index) {\n        signed_area2 += cross(\n            polygon[index]\
    \ - origin,\n            polygon[index + 1] - origin\n        );\n    }\n    if\
    \ (signed_area2 <= eps) return {};\n\n    auto first = std::min_element(polygon.begin(),\
    \ polygon.end());\n    std::rotate(polygon.begin(), first, polygon.end());\n \
    \   return polygon;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n\
    #line 4 \"verify/geometry/half_plane_intersection_random.test.cpp\"\n\n#line 9\
    \ \"verify/geometry/half_plane_intersection_random.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#include <random>\n#line 13 \"verify/geometry/half_plane_intersection_random.test.cpp\"\
    \n\nnamespace {\n\nusing m1une::geometry::Line;\nusing m1une::geometry::Point;\n\
    using PointType = Point<long double>;\n\nstd::vector<PointType> clip(\n    const\
    \ std::vector<PointType>& polygon,\n    const Line<long double>& half_plane\n\
    ) {\n    std::vector<PointType> result;\n    PointType direction = half_plane.b\
    \ - half_plane.a;\n    for (std::size_t index = 0; index < polygon.size(); ++index)\
    \ {\n        PointType first = polygon[index];\n        PointType second = polygon[(index\
    \ + 1) % polygon.size()];\n        long double first_side = cross(direction, first\
    \ - half_plane.a);\n        long double second_side = cross(direction, second\
    \ - half_plane.a);\n        bool first_inside = first_side >= -1e-12L;\n     \
    \   bool second_inside = second_side >= -1e-12L;\n        if (first_inside) result.push_back(first);\n\
    \        if (first_inside != second_inside) {\n            long double ratio =\
    \ first_side / (first_side - second_side);\n            result.push_back(first\
    \ + (second - first) * ratio);\n        }\n    }\n    return result;\n}\n\nlong\
    \ double area(const std::vector<PointType>& polygon) {\n    long double result\
    \ = 0;\n    for (std::size_t index = 0; index < polygon.size(); ++index) {\n \
    \       result += cross(\n            polygon[index],\n            polygon[(index\
    \ + 1) % polygon.size()]\n        );\n    }\n    return std::fabs(result) / 2;\n\
    }\n\nvoid add_bounding_square(std::vector<Line<long double>>& half_planes) {\n\
    \    PointType lower_left(-50, -50);\n    PointType lower_right(50, -50);\n  \
    \  PointType upper_right(50, 50);\n    PointType upper_left(-50, 50);\n    half_planes.push_back(Line<long\
    \ double>{lower_left, lower_right});\n    half_planes.push_back(Line<long double>{lower_right,\
    \ upper_right});\n    half_planes.push_back(Line<long double>{upper_right, upper_left});\n\
    \    half_planes.push_back(Line<long double>{upper_left, lower_left});\n}\n\n\
    void test_special_cases() {\n    using IntegerPoint = Point<long long>;\n    std::vector<Line<long\
    \ long>> integer_square;\n    integer_square.push_back(Line<long long>{IntegerPoint(0,\
    \ 0), IntegerPoint(2, 0)});\n    integer_square.push_back(Line<long long>{IntegerPoint(2,\
    \ 0), IntegerPoint(2, 2)});\n    integer_square.push_back(Line<long long>{IntegerPoint(2,\
    \ 2), IntegerPoint(0, 2)});\n    integer_square.push_back(Line<long long>{IntegerPoint(0,\
    \ 2), IntegerPoint(0, 0)});\n    auto integer_polygon =\n        m1une::geometry::half_plane_intersection(integer_square);\n\
    \    assert(integer_polygon.size() == 4);\n    assert(std::fabs(area(integer_polygon)\
    \ - 4) <= 1e-12L);\n\n    std::vector<Line<long double>> square;\n    add_bounding_square(square);\n\
    \    square.push_back(Line<long double>{PointType(-4, -5), PointType(4, -5)});\n\
    \    square.push_back(Line<long double>{PointType(-4, -3), PointType(4, -3)});\n\
    \    auto polygon = m1une::geometry::half_plane_intersection(square);\n    assert(polygon.size()\
    \ == 4);\n    assert(std::fabs(area(polygon) - 5300) <= 1e-8L);\n\n    std::vector<Line<long\
    \ double>> impossible;\n    impossible.push_back(Line<long double>{PointType(1,\
    \ 1), PointType(1, 0)});\n    impossible.push_back(Line<long double>{PointType(0,\
    \ 0), PointType(0, 1)});\n    impossible.push_back(Line<long double>{PointType(0,\
    \ 0), PointType(1, 0)});\n    impossible.push_back(Line<long double>{PointType(1,\
    \ 1), PointType(0, 1)});\n    assert(m1une::geometry::half_plane_intersection(impossible).empty());\n\
    \n    std::vector<Line<long double>> unbounded;\n    unbounded.push_back(Line<long\
    \ double>{PointType(0, 0), PointType(1, 0)});\n    unbounded.push_back(Line<long\
    \ double>{PointType(0, 0), PointType(0, -1)});\n    unbounded.push_back(Line<long\
    \ double>{PointType(0, 1), PointType(1, 0)});\n    assert(m1une::geometry::half_plane_intersection(unbounded).empty());\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 0x5f3759dfULL;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 3000;\
    \ ++trial) {\n        std::vector<Line<long double>> half_planes;\n        add_bounding_square(half_planes);\n\
    \        int count = 1 + int(random() % 30);\n        for (int index = 0; index\
    \ < count; ++index) {\n            long long dx;\n            long long dy;\n\
    \            do {\n                dx = static_cast<long long>(random() % 21)\
    \ - 10;\n                dy = static_cast<long long>(random() % 21) - 10;\n  \
    \          } while (dx == 0 && dy == 0);\n            long long offset = 1 + static_cast<long\
    \ long>(random() % 8);\n            PointType first(dy * offset, -dx * offset);\n\
    \            PointType second(first.x + dx, first.y + dy);\n            half_planes.push_back(Line<long\
    \ double>{first, second});\n        }\n\n        std::vector<PointType> expected;\n\
    \        expected.emplace_back(-50, -50);\n        expected.emplace_back(50, -50);\n\
    \        expected.emplace_back(50, 50);\n        expected.emplace_back(-50, 50);\n\
    \        for (const auto& half_plane : half_planes) {\n            expected =\
    \ clip(expected, half_plane);\n        }\n\n        std::shuffle(\n          \
    \  half_planes.begin(),\n            half_planes.end(),\n            std::mt19937_64(random())\n\
    \        );\n        auto actual = m1une::geometry::half_plane_intersection(half_planes);\n\
    \        assert(!actual.empty());\n        long double expected_area = area(expected);\n\
    \        long double actual_area = area(actual);\n        assert(\n          \
    \  std::fabs(expected_area - actual_area) <=\n            1e-8L * std::max(1.0L,\
    \ expected_area)\n        );\n        for (const PointType& point : actual) {\n\
    \            for (const auto& half_plane : half_planes) {\n                assert(cross(\n\
    \                    half_plane.b - half_plane.a,\n                    point -\
    \ half_plane.a\n                ) >= -1e-8L);\n            }\n        }\n    }\n\
    \n    for (int trial = 0; trial < 3000; ++trial) {\n        std::vector<Line<long\
    \ double>> half_planes;\n        add_bounding_square(half_planes);\n        int\
    \ count = 1 + int(random() % 20);\n        for (int index = 0; index < count;\
    \ ++index) {\n            long long dx;\n            long long dy;\n         \
    \   do {\n                dx = static_cast<long long>(random() % 21) - 10;\n \
    \               dy = static_cast<long long>(random() % 21) - 10;\n           \
    \ } while (dx == 0 && dy == 0);\n            PointType first(\n              \
    \  static_cast<long long>(random() % 121) - 60,\n                static_cast<long\
    \ long>(random() % 121) - 60\n            );\n            PointType second(first.x\
    \ + dx, first.y + dy);\n            half_planes.push_back(Line<long double>{first,\
    \ second});\n        }\n\n        std::vector<PointType> expected;\n        expected.emplace_back(-50,\
    \ -50);\n        expected.emplace_back(50, -50);\n        expected.emplace_back(50,\
    \ 50);\n        expected.emplace_back(-50, 50);\n        for (const auto& half_plane\
    \ : half_planes) {\n            expected = clip(expected, half_plane);\n     \
    \   }\n        std::shuffle(\n            half_planes.begin(),\n            half_planes.end(),\n\
    \            std::mt19937_64(random())\n        );\n        auto actual = m1une::geometry::half_plane_intersection(half_planes);\n\
    \        long double expected_area = area(expected);\n        if (expected_area\
    \ <= 1e-10L) {\n            assert(actual.empty());\n        } else {\n      \
    \      assert(!actual.empty());\n            assert(\n                std::fabs(expected_area\
    \ - area(actual)) <=\n                1e-8L * std::max(1.0L, expected_area)\n\
    \            );\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_special_cases();\n\
    \    test_randomized();\n\n    long long a;\n    long long b;\n    std::cin >>\
    \ a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../geometry/half_plane_intersection.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <cstddef>\n#include <cstdint>\n#include\
    \ <iostream>\n#include <random>\n#include <vector>\n\nnamespace {\n\nusing m1une::geometry::Line;\n\
    using m1une::geometry::Point;\nusing PointType = Point<long double>;\n\nstd::vector<PointType>\
    \ clip(\n    const std::vector<PointType>& polygon,\n    const Line<long double>&\
    \ half_plane\n) {\n    std::vector<PointType> result;\n    PointType direction\
    \ = half_plane.b - half_plane.a;\n    for (std::size_t index = 0; index < polygon.size();\
    \ ++index) {\n        PointType first = polygon[index];\n        PointType second\
    \ = polygon[(index + 1) % polygon.size()];\n        long double first_side = cross(direction,\
    \ first - half_plane.a);\n        long double second_side = cross(direction, second\
    \ - half_plane.a);\n        bool first_inside = first_side >= -1e-12L;\n     \
    \   bool second_inside = second_side >= -1e-12L;\n        if (first_inside) result.push_back(first);\n\
    \        if (first_inside != second_inside) {\n            long double ratio =\
    \ first_side / (first_side - second_side);\n            result.push_back(first\
    \ + (second - first) * ratio);\n        }\n    }\n    return result;\n}\n\nlong\
    \ double area(const std::vector<PointType>& polygon) {\n    long double result\
    \ = 0;\n    for (std::size_t index = 0; index < polygon.size(); ++index) {\n \
    \       result += cross(\n            polygon[index],\n            polygon[(index\
    \ + 1) % polygon.size()]\n        );\n    }\n    return std::fabs(result) / 2;\n\
    }\n\nvoid add_bounding_square(std::vector<Line<long double>>& half_planes) {\n\
    \    PointType lower_left(-50, -50);\n    PointType lower_right(50, -50);\n  \
    \  PointType upper_right(50, 50);\n    PointType upper_left(-50, 50);\n    half_planes.push_back(Line<long\
    \ double>{lower_left, lower_right});\n    half_planes.push_back(Line<long double>{lower_right,\
    \ upper_right});\n    half_planes.push_back(Line<long double>{upper_right, upper_left});\n\
    \    half_planes.push_back(Line<long double>{upper_left, lower_left});\n}\n\n\
    void test_special_cases() {\n    using IntegerPoint = Point<long long>;\n    std::vector<Line<long\
    \ long>> integer_square;\n    integer_square.push_back(Line<long long>{IntegerPoint(0,\
    \ 0), IntegerPoint(2, 0)});\n    integer_square.push_back(Line<long long>{IntegerPoint(2,\
    \ 0), IntegerPoint(2, 2)});\n    integer_square.push_back(Line<long long>{IntegerPoint(2,\
    \ 2), IntegerPoint(0, 2)});\n    integer_square.push_back(Line<long long>{IntegerPoint(0,\
    \ 2), IntegerPoint(0, 0)});\n    auto integer_polygon =\n        m1une::geometry::half_plane_intersection(integer_square);\n\
    \    assert(integer_polygon.size() == 4);\n    assert(std::fabs(area(integer_polygon)\
    \ - 4) <= 1e-12L);\n\n    std::vector<Line<long double>> square;\n    add_bounding_square(square);\n\
    \    square.push_back(Line<long double>{PointType(-4, -5), PointType(4, -5)});\n\
    \    square.push_back(Line<long double>{PointType(-4, -3), PointType(4, -3)});\n\
    \    auto polygon = m1une::geometry::half_plane_intersection(square);\n    assert(polygon.size()\
    \ == 4);\n    assert(std::fabs(area(polygon) - 5300) <= 1e-8L);\n\n    std::vector<Line<long\
    \ double>> impossible;\n    impossible.push_back(Line<long double>{PointType(1,\
    \ 1), PointType(1, 0)});\n    impossible.push_back(Line<long double>{PointType(0,\
    \ 0), PointType(0, 1)});\n    impossible.push_back(Line<long double>{PointType(0,\
    \ 0), PointType(1, 0)});\n    impossible.push_back(Line<long double>{PointType(1,\
    \ 1), PointType(0, 1)});\n    assert(m1une::geometry::half_plane_intersection(impossible).empty());\n\
    \n    std::vector<Line<long double>> unbounded;\n    unbounded.push_back(Line<long\
    \ double>{PointType(0, 0), PointType(1, 0)});\n    unbounded.push_back(Line<long\
    \ double>{PointType(0, 0), PointType(0, -1)});\n    unbounded.push_back(Line<long\
    \ double>{PointType(0, 1), PointType(1, 0)});\n    assert(m1une::geometry::half_plane_intersection(unbounded).empty());\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 0x5f3759dfULL;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 3000;\
    \ ++trial) {\n        std::vector<Line<long double>> half_planes;\n        add_bounding_square(half_planes);\n\
    \        int count = 1 + int(random() % 30);\n        for (int index = 0; index\
    \ < count; ++index) {\n            long long dx;\n            long long dy;\n\
    \            do {\n                dx = static_cast<long long>(random() % 21)\
    \ - 10;\n                dy = static_cast<long long>(random() % 21) - 10;\n  \
    \          } while (dx == 0 && dy == 0);\n            long long offset = 1 + static_cast<long\
    \ long>(random() % 8);\n            PointType first(dy * offset, -dx * offset);\n\
    \            PointType second(first.x + dx, first.y + dy);\n            half_planes.push_back(Line<long\
    \ double>{first, second});\n        }\n\n        std::vector<PointType> expected;\n\
    \        expected.emplace_back(-50, -50);\n        expected.emplace_back(50, -50);\n\
    \        expected.emplace_back(50, 50);\n        expected.emplace_back(-50, 50);\n\
    \        for (const auto& half_plane : half_planes) {\n            expected =\
    \ clip(expected, half_plane);\n        }\n\n        std::shuffle(\n          \
    \  half_planes.begin(),\n            half_planes.end(),\n            std::mt19937_64(random())\n\
    \        );\n        auto actual = m1une::geometry::half_plane_intersection(half_planes);\n\
    \        assert(!actual.empty());\n        long double expected_area = area(expected);\n\
    \        long double actual_area = area(actual);\n        assert(\n          \
    \  std::fabs(expected_area - actual_area) <=\n            1e-8L * std::max(1.0L,\
    \ expected_area)\n        );\n        for (const PointType& point : actual) {\n\
    \            for (const auto& half_plane : half_planes) {\n                assert(cross(\n\
    \                    half_plane.b - half_plane.a,\n                    point -\
    \ half_plane.a\n                ) >= -1e-8L);\n            }\n        }\n    }\n\
    \n    for (int trial = 0; trial < 3000; ++trial) {\n        std::vector<Line<long\
    \ double>> half_planes;\n        add_bounding_square(half_planes);\n        int\
    \ count = 1 + int(random() % 20);\n        for (int index = 0; index < count;\
    \ ++index) {\n            long long dx;\n            long long dy;\n         \
    \   do {\n                dx = static_cast<long long>(random() % 21) - 10;\n \
    \               dy = static_cast<long long>(random() % 21) - 10;\n           \
    \ } while (dx == 0 && dy == 0);\n            PointType first(\n              \
    \  static_cast<long long>(random() % 121) - 60,\n                static_cast<long\
    \ long>(random() % 121) - 60\n            );\n            PointType second(first.x\
    \ + dx, first.y + dy);\n            half_planes.push_back(Line<long double>{first,\
    \ second});\n        }\n\n        std::vector<PointType> expected;\n        expected.emplace_back(-50,\
    \ -50);\n        expected.emplace_back(50, -50);\n        expected.emplace_back(50,\
    \ 50);\n        expected.emplace_back(-50, 50);\n        for (const auto& half_plane\
    \ : half_planes) {\n            expected = clip(expected, half_plane);\n     \
    \   }\n        std::shuffle(\n            half_planes.begin(),\n            half_planes.end(),\n\
    \            std::mt19937_64(random())\n        );\n        auto actual = m1une::geometry::half_plane_intersection(half_planes);\n\
    \        long double expected_area = area(expected);\n        if (expected_area\
    \ <= 1e-10L) {\n            assert(actual.empty());\n        } else {\n      \
    \      assert(!actual.empty());\n            assert(\n                std::fabs(expected_area\
    \ - area(actual)) <=\n                1e-8L * std::max(1.0L, expected_area)\n\
    \            );\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_special_cases();\n\
    \    test_randomized();\n\n    long long a;\n    long long b;\n    std::cin >>\
    \ a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - geometry/half_plane_intersection.hpp
  - geometry/line.hpp
  - geometry/point.hpp
  isVerificationFile: true
  path: verify/geometry/half_plane_intersection_random.test.cpp
  requiredBy: []
  timestamp: '2026-07-04 02:22:30+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/half_plane_intersection_random.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/half_plane_intersection_random.test.cpp
- /verify/verify/geometry/half_plane_intersection_random.test.cpp.html
title: verify/geometry/half_plane_intersection_random.test.cpp
---
