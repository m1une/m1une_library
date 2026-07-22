---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/circle.hpp
    title: Circles
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: Lines and Segments
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
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
    ERROR: '0.000001'
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B
  bundledCode: "#line 1 \"verify/geometry/incircle.test.cpp\"\n#define PROBLEM \"\
    https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B\"\n#define ERROR\
    \ 0.000001\n\n#line 1 \"geometry/circle.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <cstddef>\n#include <numbers>\n#include\
    \ <optional>\n#include <type_traits>\n#include <vector>\n\n#line 1 \"geometry/ray.hpp\"\
    \n\n\n\n#line 7 \"geometry/ray.hpp\"\n\n#line 1 \"geometry/line.hpp\"\n\n\n\n\
    #line 8 \"geometry/line.hpp\"\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#line 5\
    \ \"geometry/point.hpp\"\n#include <concepts>\n#line 8 \"geometry/point.hpp\"\n\
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
    \n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 9 \"geometry/ray.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct\
    \ Ray {\n    Point<T> origin;\n    Point<T> through;\n};\n\nnamespace ray_detail\
    \ {\n\ntemplate <Coordinate T>\nstruct Parameters {\n    wide_type<T> denominator;\n\
    \    wide_type<T> first_numerator;\n    wide_type<T> second_numerator;\n};\n\n\
    template <Coordinate T>\nParameters<T> parameters(\n    const Point<T>& first_origin,\n\
    \    const Point<T>& first_through,\n    const Point<T>& second_origin,\n    const\
    \ Point<T>& second_through\n) {\n    using W = wide_type<T>;\n    W first_x =\
    \ W(first_through.x) - W(first_origin.x);\n    W first_y = W(first_through.y)\
    \ - W(first_origin.y);\n    W second_x = W(second_through.x) - W(second_origin.x);\n\
    \    W second_y = W(second_through.y) - W(second_origin.y);\n    W offset_x =\
    \ W(second_origin.x) - W(first_origin.x);\n    W offset_y = W(second_origin.y)\
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
    geometry/circle.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate\
    \ T>\nstruct Circle {\n    Point<T> center;\n    T radius;\n};\n\nenum class PointInCircle\
    \ {\n    Outside = 0,\n    Boundary = 1,\n    Inside = 2,\n};\n\nenum class CircleRelation\
    \ {\n    Separate,\n    ExternallyTangent,\n    Intersecting,\n    InternallyTangent,\n\
    \    Contained,\n    Coincident,\n};\n\nnamespace circle_detail {\n\ninline int\
    \ compare(long double first, long double second, long double eps) {\n    if (first\
    \ < second - eps) return -1;\n    if (first > second + eps) return 1;\n    return\
    \ 0;\n}\n\ninline bool close(\n    const Point<long double>& first,\n    const\
    \ Point<long double>& second,\n    long double eps\n) {\n    return geometry::distance(first,\
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
    \    if (angle >= 0.01L) return angle - sine * cosine;\n    long double squared\
    \ = angle * angle;\n    return angle * squared * (\n        2.0L / 3.0L +\n  \
    \      squared * (\n            -2.0L / 15.0L +\n            squared * (4.0L /\
    \ 315.0L - squared * 2.0L / 2835.0L)\n        )\n    );\n}\n\ninline long double\
    \ segment_disk_signed_area(\n    const Point<long double>& first,\n    const Point<long\
    \ double>& second,\n    long double radius,\n    long double eps\n) {\n    Point<long\
    \ double> direction = second - first;\n    long double quadratic = dot(direction,\
    \ direction);\n    if (quadratic == 0.0L || radius == 0.0L) return 0.0L;\n\n \
    \   std::vector<long double> cuts = {0.0L, 1.0L};\n    long double linear = 2.0L\
    \ * dot(first, direction);\n    long double constant = dot(first, first) - radius\
    \ * radius;\n    long double discriminant =\n        linear * linear - 4.0L *\
    \ quadratic * constant;\n    long double tolerance = eps * std::max({\n      \
    \  1.0L,\n        std::fabs(linear * linear),\n        std::fabs(4.0L * quadratic\
    \ * constant)\n    });\n    if (discriminant >= -tolerance) {\n        long double\
    \ root = std::sqrt(std::max(0.0L, discriminant));\n        long double first_ratio\
    \ =\n            (-linear - root) / (2.0L * quadratic);\n        long double second_ratio\
    \ =\n            (-linear + root) / (2.0L * quadratic);\n        if (eps < first_ratio\
    \ && first_ratio < 1.0L - eps) {\n            cuts.push_back(first_ratio);\n \
    \       }\n        if (eps < second_ratio && second_ratio < 1.0L - eps) {\n  \
    \          cuts.push_back(second_ratio);\n        }\n    }\n    std::sort(cuts.begin(),\
    \ cuts.end());\n    cuts.erase(\n        std::unique(\n            cuts.begin(),\n\
    \            cuts.end(),\n            [eps](long double left, long double right)\
    \ {\n                return std::fabs(left - right) <= eps;\n            }\n \
    \       ),\n        cuts.end()\n    );\n\n    long double result = 0.0L;\n   \
    \ for (std::size_t index = 1; index < cuts.size(); ++index) {\n        long double\
    \ left = cuts[index - 1];\n        long double right = cuts[index];\n        Point<long\
    \ double> a = first + direction * left;\n        Point<long double> b = first\
    \ + direction * right;\n        Point<long double> middle =\n            first\
    \ + direction * ((left + right) / 2.0L);\n        if (norm(middle) <= radius +\
    \ eps) {\n            result += cross(a, b) / 2.0L;\n        } else {\n      \
    \      result +=\n                radius * radius * std::atan2(cross(a, b), dot(a,\
    \ b)) /\n                2.0L;\n        }\n    }\n    return result;\n}\n\n} \
    \ // namespace circle_detail\n\ntemplate <Coordinate T>\nconstexpr Point<long\
    \ double> centroid(const Circle<T>& circle) {\n    assert(circle.radius >= 0);\n\
    \    return Point<long double>(circle.center);\n}\n\ntemplate <Coordinate T>\n\
    constexpr long double circle_area(const Circle<T>& circle) {\n    assert(circle.radius\
    \ >= 0);\n    long double radius = static_cast<long double>(circle.radius);\n\
    \    return std::numbers::pi_v<long double> * radius * radius;\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr long double circle_circumference(const Circle<T>&\
    \ circle) {\n    assert(circle.radius >= 0);\n    return\n        2.0L * std::numbers::pi_v<long\
    \ double> *\n        static_cast<long double>(circle.radius);\n}\n\ntemplate <Coordinate\
    \ C, Coordinate P>\nPointInCircle point_in_circle(\n    const Circle<C>& circle,\n\
    \    const Point<P>& point,\n    long double eps = 1e-12L\n) {\n    assert(circle.radius\
    \ >= 0);\n    assert(eps >= 0.0L);\n    if constexpr (std::integral<C> && std::integral<P>)\
    \ {\n        using W = __int128_t;\n        W dx = W(point.x) - W(circle.center.x);\n\
    \        W dy = W(point.y) - W(circle.center.y);\n        W radius = W(circle.radius);\n\
    \        W squared_distance = dx * dx + dy * dy;\n        W squared_radius = radius\
    \ * radius;\n        if (squared_distance < squared_radius) return PointInCircle::Inside;\n\
    \        if (squared_distance > squared_radius) return PointInCircle::Outside;\n\
    \        return PointInCircle::Boundary;\n    } else {\n        long double value\
    \ = geometry::distance(\n            Point<long double>(circle.center),\n    \
    \        Point<long double>(point)\n        );\n        int relation = circle_detail::compare(\n\
    \            value,\n            static_cast<long double>(circle.radius),\n  \
    \          eps\n        );\n        if (relation < 0) return PointInCircle::Inside;\n\
    \        if (relation > 0) return PointInCircle::Outside;\n        return PointInCircle::Boundary;\n\
    \    }\n}\n\ntemplate <Coordinate C, Coordinate P>\nbool on_circle(\n    const\
    \ Circle<C>& circle,\n    const Point<P>& point,\n    long double eps = 1e-12L\n\
    ) {\n    return point_in_circle(circle, point, eps) == PointInCircle::Boundary;\n\
    }\n\ntemplate <Coordinate C, Coordinate P>\nbool contains(\n    const Circle<C>&\
    \ circle,\n    const Point<P>& point,\n    long double eps = 1e-12L\n) {\n   \
    \ return point_in_circle(circle, point, eps) != PointInCircle::Outside;\n}\n\n\
    template <Coordinate A, Coordinate B>\nCircle<long double> circle_from_diameter(\n\
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
    \    }\n}\n\ntemplate <Coordinate C, Coordinate L>\nstd::vector<Point<long double>>\
    \ circle_line_intersections(\n    const Circle<C>& circle,\n    const Line<L>&\
    \ line,\n    long double eps = 1e-12L\n) {\n    assert(circle.radius >= 0);\n\
    \    assert(line.a != line.b);\n    assert(eps >= 0.0L);\n\n    Point<long double>\
    \ center(circle.center);\n    Point<long double> a(line.a);\n    Point<long double>\
    \ direction = Point<long double>(line.b) - a;\n    long double length = norm(direction);\n\
    \    Point<long double> unit = direction / length;\n    Point<long double> foot\
    \ =\n        a + direction * (dot(center - a, direction) / dot(direction, direction));\n\
    \    long double distance_to_line = geometry::distance(center, foot);\n    long\
    \ double radius = static_cast<long double>(circle.radius);\n    int relation =\
    \ circle_detail::compare(distance_to_line, radius, eps);\n    if (relation > 0)\
    \ return {};\n    if (relation == 0) return {foot};\n\n    long double offset\
    \ = std::sqrt(std::max(\n        0.0L,\n        radius * radius - distance_to_line\
    \ * distance_to_line\n    ));\n    Point<long double> first = foot - unit * offset;\n\
    \    Point<long double> second = foot + unit * offset;\n    if (second < first)\
    \ std::swap(first, second);\n    return {first, second};\n}\n\ntemplate <Coordinate\
    \ C, Coordinate L>\nstd::vector<Point<long double>> circle_line_intersections(\n\
    \    const Line<L>& line,\n    const Circle<C>& circle,\n    long double eps =\
    \ 1e-12L\n) {\n    return circle_line_intersections(circle, line, eps);\n}\n\n\
    template <Coordinate C, Coordinate R>\nstd::vector<Point<long double>> circle_ray_intersections(\n\
    \    const Circle<C>& circle,\n    const Ray<R>& ray,\n    long double eps = 1e-12L\n\
    ) {\n    assert(circle.radius >= 0);\n    assert(ray.origin != ray.through);\n\
    \    assert(eps >= 0.0L);\n\n    Point<long double> origin(ray.origin);\n    Point<long\
    \ double> direction = Point<long double>(ray.through) - origin;\n    Point<long\
    \ double> unit = direction / norm(direction);\n    Line<R> line{ray.origin, ray.through};\n\
    \    std::vector<Point<long double>> line_points =\n        circle_line_intersections(circle,\
    \ line, eps);\n    std::vector<Point<long double>> result;\n    for (Point<long\
    \ double> point : line_points) {\n        long double along = dot(point - origin,\
    \ unit);\n        if (along < -eps) continue;\n        if (std::fabs(along) <=\
    \ eps) point = origin;\n        circle_detail::push_unique(result, point, eps);\n\
    \    }\n    std::sort(\n        result.begin(),\n        result.end(),\n     \
    \   [&](const Point<long double>& first, const Point<long double>& second) {\n\
    \            return dot(first - origin, unit) < dot(second - origin, unit);\n\
    \        }\n    );\n    return result;\n}\n\ntemplate <Coordinate C, Coordinate\
    \ R>\nstd::vector<Point<long double>> circle_ray_intersections(\n    const Ray<R>&\
    \ ray,\n    const Circle<C>& circle,\n    long double eps = 1e-12L\n) {\n    return\
    \ circle_ray_intersections(circle, ray, eps);\n}\n\ntemplate <Coordinate C, Coordinate\
    \ S>\nstd::vector<Point<long double>> circle_segment_intersections(\n    const\
    \ Circle<C>& circle,\n    const Segment<S>& segment,\n    long double eps = 1e-12L\n\
    ) {\n    assert(circle.radius >= 0);\n    assert(eps >= 0.0L);\n    if (segment.a\
    \ == segment.b) {\n        if (on_circle(circle, segment.a, eps)) {\n        \
    \    return {Point<long double>(segment.a)};\n        }\n        return {};\n\
    \    }\n\n    Point<long double> first_endpoint(segment.a);\n    Point<long double>\
    \ direction =\n        Point<long double>(segment.b) - first_endpoint;\n    long\
    \ double length = norm(direction);\n    Point<long double> unit = direction /\
    \ length;\n    Line<S> line{segment.a, segment.b};\n    std::vector<Point<long\
    \ double>> line_points =\n        circle_line_intersections(circle, line, eps);\n\
    \    std::vector<Point<long double>> result;\n    for (Point<long double> point\
    \ : line_points) {\n        long double along = dot(point - first_endpoint, unit);\n\
    \        if (along < -eps || along > length + eps) continue;\n        if (std::fabs(along)\
    \ <= eps) point = first_endpoint;\n        if (std::fabs(along - length) <= eps)\
    \ {\n            point = Point<long double>(segment.b);\n        }\n        circle_detail::push_unique(result,\
    \ point, eps);\n    }\n    std::sort(\n        result.begin(),\n        result.end(),\n\
    \        [&](const Point<long double>& first, const Point<long double>& second)\
    \ {\n            return dot(first - first_endpoint, unit) <\n                \
    \   dot(second - first_endpoint, unit);\n        }\n    );\n    return result;\n\
    }\n\ntemplate <Coordinate C, Coordinate S>\nstd::vector<Point<long double>> circle_segment_intersections(\n\
    \    const Segment<S>& segment,\n    const Circle<C>& circle,\n    long double\
    \ eps = 1e-12L\n) {\n    return circle_segment_intersections(circle, segment,\
    \ eps);\n}\n\ntemplate <Coordinate A, Coordinate B>\nstd::vector<Point<long double>>\
    \ circle_intersections(\n    const Circle<A>& first,\n    const Circle<B>& second,\n\
    \    long double eps = 1e-12L\n) {\n    assert(first.radius >= 0);\n    assert(second.radius\
    \ >= 0);\n    assert(eps >= 0.0L);\n    CircleRelation relation = circle_relation(first,\
    \ second, eps);\n    if (\n        relation == CircleRelation::Separate ||\n \
    \       relation == CircleRelation::Contained ||\n        relation == CircleRelation::Coincident\n\
    \    ) {\n        return {};\n    }\n\n    Point<long double> first_center(first.center);\n\
    \    Point<long double> second_center(second.center);\n    Point<long double>\
    \ direction = second_center - first_center;\n    long double center_distance =\
    \ norm(direction);\n    long double first_radius = static_cast<long double>(first.radius);\n\
    \    long double second_radius = static_cast<long double>(second.radius);\n  \
    \  long double along =\n        (first_radius * first_radius - second_radius *\
    \ second_radius +\n         center_distance * center_distance) /\n        (2.0L\
    \ * center_distance);\n    Point<long double> unit = direction / center_distance;\n\
    \    Point<long double> base = first_center + unit * along;\n    if (\n      \
    \  relation == CircleRelation::ExternallyTangent ||\n        relation == CircleRelation::InternallyTangent\n\
    \    ) {\n        return {base};\n    }\n\n    long double height = std::sqrt(std::max(\n\
    \        0.0L,\n        first_radius * first_radius - along * along\n    ));\n\
    \    Point<long double> perpendicular(-unit.y, unit.x);\n    Point<long double>\
    \ a = base - perpendicular * height;\n    Point<long double> b = base + perpendicular\
    \ * height;\n    if (b < a) std::swap(a, b);\n    return {a, b};\n}\n\ntemplate\
    \ <Coordinate C, Coordinate R>\nstd::optional<Point<long double>> first_circle_ray_intersection(\n\
    \    const Circle<C>& circle,\n    const Ray<R>& ray,\n    long double eps = 1e-12L\n\
    ) {\n    std::vector<Point<long double>> points =\n        circle_ray_intersections(circle,\
    \ ray, eps);\n    if (points.empty()) return std::nullopt;\n    return points.front();\n\
    }\n\ntemplate <Coordinate C, Coordinate L>\nbool intersects(\n    const Circle<C>&\
    \ circle,\n    const Line<L>& line,\n    long double eps = 1e-12L\n) {\n    return\
    \ !circle_line_intersections(circle, line, eps).empty();\n}\n\ntemplate <Coordinate\
    \ C, Coordinate L>\nbool intersects(\n    const Line<L>& line,\n    const Circle<C>&\
    \ circle,\n    long double eps = 1e-12L\n) {\n    return intersects(circle, line,\
    \ eps);\n}\n\ntemplate <Coordinate C, Coordinate R>\nbool intersects(\n    const\
    \ Circle<C>& circle,\n    const Ray<R>& ray,\n    long double eps = 1e-12L\n)\
    \ {\n    return !circle_ray_intersections(circle, ray, eps).empty();\n}\n\ntemplate\
    \ <Coordinate C, Coordinate R>\nbool intersects(\n    const Ray<R>& ray,\n   \
    \ const Circle<C>& circle,\n    long double eps = 1e-12L\n) {\n    return intersects(circle,\
    \ ray, eps);\n}\n\ntemplate <Coordinate C, Coordinate S>\nbool intersects(\n \
    \   const Circle<C>& circle,\n    const Segment<S>& segment,\n    long double\
    \ eps = 1e-12L\n) {\n    return !circle_segment_intersections(circle, segment,\
    \ eps).empty();\n}\n\ntemplate <Coordinate C, Coordinate S>\nbool intersects(\n\
    \    const Segment<S>& segment,\n    const Circle<C>& circle,\n    long double\
    \ eps = 1e-12L\n) {\n    return intersects(circle, segment, eps);\n}\n\ntemplate\
    \ <Coordinate A, Coordinate B>\nbool intersects(\n    const Circle<A>& first,\n\
    \    const Circle<B>& second,\n    long double eps = 1e-12L\n) {\n    CircleRelation\
    \ relation = circle_relation(first, second, eps);\n    return\n        relation\
    \ == CircleRelation::ExternallyTangent ||\n        relation == CircleRelation::Intersecting\
    \ ||\n        relation == CircleRelation::InternallyTangent ||\n        relation\
    \ == CircleRelation::Coincident;\n}\n\ntemplate <Coordinate R, Coordinate H, Coordinate\
    \ C>\nRay<long double> reflected_ray(\n    const Ray<R>& incoming,\n    const\
    \ Point<H>& hit,\n    const Circle<C>& circle,\n    long double eps = 1e-12L\n\
    ) {\n    assert(incoming.origin != incoming.through);\n    assert(eps >= 0.0L);\n\
    \    assert(static_cast<long double>(circle.radius) > eps);\n    assert(\n   \
    \     std::fabs(\n            geometry::distance(\n                Point<long\
    \ double>(hit),\n                Point<long double>(circle.center)\n         \
    \   ) -\n            static_cast<long double>(circle.radius)\n        ) <= eps\n\
    \    );\n\n    Point<long double> hit_point(hit);\n    Point<long double> normal\
    \ = normalized(\n        hit_point - Point<long double>(circle.center)\n    );\n\
    \    Point<long double> incoming_direction =\n        Point<long double>(incoming.through)\
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
    \ result;\n}\n\ntemplate <Coordinate A, Coordinate B>\nlong double circle_circle_intersection_area(\n\
    \    const Circle<A>& first,\n    const Circle<B>& second,\n    long double eps\
    \ = 1e-12L\n) {\n    assert(first.radius >= 0);\n    assert(second.radius >= 0);\n\
    \    assert(eps >= 0.0L);\n    long double first_radius = static_cast<long double>(first.radius);\n\
    \    long double second_radius = static_cast<long double>(second.radius);\n  \
    \  CircleRelation relation = circle_relation(first, second, eps);\n    if (\n\
    \        relation == CircleRelation::Separate ||\n        relation == CircleRelation::ExternallyTangent\n\
    \    ) {\n        return 0.0L;\n    }\n    if (\n        relation == CircleRelation::Contained\
    \ ||\n        relation == CircleRelation::InternallyTangent ||\n        relation\
    \ == CircleRelation::Coincident\n    ) {\n        long double radius = std::min(first_radius,\
    \ second_radius);\n        return std::numbers::pi_v<long double> * radius * radius;\n\
    \    }\n\n    long double center_distance = geometry::distance(\n        Point<long\
    \ double>(first.center),\n        Point<long double>(second.center)\n    );\n\
    \    long double first_cosine = std::clamp(\n        (\n            (center_distance\
    \ - second_radius) *\n                (center_distance + second_radius) +\n  \
    \          first_radius * first_radius\n        ) /\n            (2.0L * center_distance\
    \ * first_radius),\n        -1.0L,\n        1.0L\n    );\n    long double second_cosine\
    \ = std::clamp(\n        (\n            (center_distance - first_radius) *\n \
    \               (center_distance + first_radius) +\n            second_radius\
    \ * second_radius\n        ) /\n            (2.0L * center_distance * second_radius),\n\
    \        -1.0L,\n        1.0L\n    );\n    long double radicand =\n        (-center_distance\
    \ + first_radius + second_radius) *\n        (center_distance + first_radius -\
    \ second_radius) *\n        (center_distance - first_radius + second_radius) *\n\
    \        (center_distance + first_radius + second_radius);\n    long double height\
    \ =\n        std::sqrt(std::max(0.0L, radicand)) /\n        (2.0L * center_distance);\n\
    \    long double first_sine = std::clamp(\n        height / first_radius,\n  \
    \      0.0L,\n        1.0L\n    );\n    long double second_sine = std::clamp(\n\
    \        height / second_radius,\n        0.0L,\n        1.0L\n    );\n    long\
    \ double first_angle = std::atan2(first_sine, first_cosine);\n    long double\
    \ second_angle = std::atan2(second_sine, second_cosine);\n    return\n       \
    \ first_radius * first_radius *\n            circle_detail::circular_segment_angle_term(\n\
    \                first_angle,\n                first_sine,\n                first_cosine\n\
    \            ) +\n        second_radius * second_radius *\n            circle_detail::circular_segment_angle_term(\n\
    \                second_angle,\n                second_sine,\n               \
    \ second_cosine\n            );\n}\n\ntemplate <Coordinate C, Coordinate P>\n\
    long double circle_polygon_intersection_area(\n    const Circle<C>& circle,\n\
    \    const std::vector<Point<P>>& polygon,\n    long double eps = 1e-12L\n) {\n\
    \    assert(circle.radius >= 0);\n    assert(eps >= 0.0L);\n    if (polygon.empty()\
    \ || circle.radius == 0) return 0.0L;\n\n    Point<long double> center(circle.center);\n\
    \    long double radius = static_cast<long double>(circle.radius);\n    long double\
    \ result = 0.0L;\n    for (std::size_t index = 0; index < polygon.size(); ++index)\
    \ {\n        Point<long double> first =\n            Point<long double>(polygon[index])\
    \ - center;\n        Point<long double> second =\n            Point<long double>(polygon[(index\
    \ + 1) % polygon.size()]) - center;\n        result += circle_detail::segment_disk_signed_area(\n\
    \            first,\n            second,\n            radius,\n            eps\n\
    \        );\n    }\n    return std::fabs(result);\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n#line 5 \"verify/geometry/incircle.test.cpp\"\n\n#line\
    \ 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include\
    \ <array>\n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 17 \"utilities/fast_io.hpp\"\
    \n#include <utility>\n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities\
    \ {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
    \ T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\n\
    struct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 8 \"verify/geometry/incircle.test.cpp\"\
    \n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n    using namespace m1une::geometry;\n\n    Point<long long> first;\n\
    \    Point<long long> second;\n    Point<long long> third;\n    fast_input >>\
    \ first.x >> first.y;\n    fast_input >> second.x >> second.y;\n    fast_input\
    \ >> third.x >> third.y;\n    auto result = incircle(first, second, third);\n\
    \    assert(result.has_value());\n    fast_output.set_fixed(15);\n    fast_output\
    \ << result->center.x << \" \" << result->center.y << \" \"\n                <<\
    \ result->radius << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B\"\
    \n#define ERROR 0.000001\n\n#include \"../../geometry/circle.hpp\"\n\n#include\
    \ <cassert>\n#include \"../../utilities/fast_io.hpp\"\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n    using namespace\
    \ m1une::geometry;\n\n    Point<long long> first;\n    Point<long long> second;\n\
    \    Point<long long> third;\n    fast_input >> first.x >> first.y;\n    fast_input\
    \ >> second.x >> second.y;\n    fast_input >> third.x >> third.y;\n    auto result\
    \ = incircle(first, second, third);\n    assert(result.has_value());\n    fast_output.set_fixed(15);\n\
    \    fast_output << result->center.x << \" \" << result->center.y << \" \"\n \
    \               << result->radius << '\\n';\n}\n"
  dependsOn:
  - geometry/circle.hpp
  - geometry/ray.hpp
  - geometry/line.hpp
  - geometry/point.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/incircle.test.cpp
  requiredBy: []
  timestamp: '2026-07-22 20:44:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/incircle.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/incircle.test.cpp
- /verify/verify/geometry/incircle.test.cpp.html
title: verify/geometry/incircle.test.cpp
---
