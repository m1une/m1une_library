---
data:
  _extendedDependsOn:
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
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/steiner_convex_decomposition.test.cpp
    title: verify/geometry/steiner_convex_decomposition.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/steiner_convex_decomposition.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cmath>\n#include <concepts>\n#include <cstddef>\n#include\
    \ <deque>\n#include <limits>\n#include <map>\n#include <optional>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"geometry/polygon.hpp\"\n\n\n\n#line 5 \"geometry/polygon.hpp\"\
    \n#include <array>\n#include <cassert>\n#line 12 \"geometry/polygon.hpp\"\n\n\
    #line 1 \"geometry/ray.hpp\"\n\n\n\n#line 7 \"geometry/ray.hpp\"\n\n#line 1 \"\
    geometry/line.hpp\"\n\n\n\n#line 8 \"geometry/line.hpp\"\n\n#line 1 \"geometry/point.hpp\"\
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
    }  // namespace m1une\n\n\n#line 16 \"geometry/steiner_convex_decomposition.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\nnamespace steiner_convex_decomposition_detail\
    \ {\n\nusing PointType = Point<long double>;\n\ninline int scalar_sign(long double\
    \ value, long double eps) {\n    return (value > eps) - (value < -eps);\n}\n\n\
    inline bool close(\n    const PointType& first,\n    const PointType& second,\n\
    \    long double eps\n) {\n    return distance2(first, second) <= eps * eps;\n\
    }\n\ntemplate <std::floating_point T>\nstd::optional<std::vector<PointType>> prepare_polygon(\n\
    \    const std::vector<Point<T>>& input,\n    long double eps\n) {\n    std::vector<PointType>\
    \ points;\n    points.reserve(input.size());\n    for (const Point<T>& point :\
    \ input) {\n        const PointType converted(point);\n        if (points.empty()\
    \ || !close(points.back(), converted, eps)) {\n            points.push_back(converted);\n\
    \        }\n    }\n    if (points.size() >= 2 && close(points.front(), points.back(),\
    \ eps)) {\n        points.pop_back();\n    }\n    if (points.size() < 3) return\
    \ std::nullopt;\n\n    const int size = static_cast<int>(points.size());\n   \
    \ std::vector<int> previous(size), next(size);\n    std::vector<bool> removed(size,\
    \ false), queued(size, true);\n    std::deque<int> candidates;\n    for (int index\
    \ = 0; index < size; ++index) {\n        previous[index] = (index + size - 1)\
    \ % size;\n        next[index] = (index + 1) % size;\n        candidates.push_back(index);\n\
    \    }\n\n    int remaining = size;\n    while (!candidates.empty() && remaining\
    \ >= 3) {\n        const int index = candidates.front();\n        candidates.pop_front();\n\
    \        queued[index] = false;\n        if (removed[index]) continue;\n     \
    \   const int before = previous[index];\n        const int after = next[index];\n\
    \        if (\n            orientation(points[before], points[index], points[after],\
    \ eps) !=\n                0 ||\n            scalar_sign(\n                dot(\n\
    \                    points[index] - points[before],\n                    points[after]\
    \ - points[index]\n                ),\n                eps\n            ) < 0\n\
    \        ) {\n            continue;\n        }\n        removed[index] = true;\n\
    \        next[before] = after;\n        previous[after] = before;\n        --remaining;\n\
    \        for (const int adjacent : {before, after}) {\n            if (!queued[adjacent])\
    \ {\n                queued[adjacent] = true;\n                candidates.push_back(adjacent);\n\
    \            }\n        }\n    }\n    if (remaining < 3) return std::nullopt;\n\
    \n    std::vector<PointType> polygon;\n    polygon.reserve(static_cast<std::size_t>(remaining));\n\
    \    int first = 0;\n    while (removed[first]) ++first;\n    int index = first;\n\
    \    do {\n        polygon.push_back(points[index]);\n        index = next[index];\n\
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
    \ + 1);\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_STEINER_CONVEX_DECOMPOSITION_HPP\n#define M1UNE_GEOMETRY_STEINER_CONVEX_DECOMPOSITION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cmath>\n#include <concepts>\n#include <cstddef>\n\
    #include <deque>\n#include <limits>\n#include <map>\n#include <optional>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"polygon.hpp\"\n\nnamespace m1une\
    \ {\nnamespace geometry {\n\nnamespace steiner_convex_decomposition_detail {\n\
    \nusing PointType = Point<long double>;\n\ninline int scalar_sign(long double\
    \ value, long double eps) {\n    return (value > eps) - (value < -eps);\n}\n\n\
    inline bool close(\n    const PointType& first,\n    const PointType& second,\n\
    \    long double eps\n) {\n    return distance2(first, second) <= eps * eps;\n\
    }\n\ntemplate <std::floating_point T>\nstd::optional<std::vector<PointType>> prepare_polygon(\n\
    \    const std::vector<Point<T>>& input,\n    long double eps\n) {\n    std::vector<PointType>\
    \ points;\n    points.reserve(input.size());\n    for (const Point<T>& point :\
    \ input) {\n        const PointType converted(point);\n        if (points.empty()\
    \ || !close(points.back(), converted, eps)) {\n            points.push_back(converted);\n\
    \        }\n    }\n    if (points.size() >= 2 && close(points.front(), points.back(),\
    \ eps)) {\n        points.pop_back();\n    }\n    if (points.size() < 3) return\
    \ std::nullopt;\n\n    const int size = static_cast<int>(points.size());\n   \
    \ std::vector<int> previous(size), next(size);\n    std::vector<bool> removed(size,\
    \ false), queued(size, true);\n    std::deque<int> candidates;\n    for (int index\
    \ = 0; index < size; ++index) {\n        previous[index] = (index + size - 1)\
    \ % size;\n        next[index] = (index + 1) % size;\n        candidates.push_back(index);\n\
    \    }\n\n    int remaining = size;\n    while (!candidates.empty() && remaining\
    \ >= 3) {\n        const int index = candidates.front();\n        candidates.pop_front();\n\
    \        queued[index] = false;\n        if (removed[index]) continue;\n     \
    \   const int before = previous[index];\n        const int after = next[index];\n\
    \        if (\n            orientation(points[before], points[index], points[after],\
    \ eps) !=\n                0 ||\n            scalar_sign(\n                dot(\n\
    \                    points[index] - points[before],\n                    points[after]\
    \ - points[index]\n                ),\n                eps\n            ) < 0\n\
    \        ) {\n            continue;\n        }\n        removed[index] = true;\n\
    \        next[before] = after;\n        previous[after] = before;\n        --remaining;\n\
    \        for (const int adjacent : {before, after}) {\n            if (!queued[adjacent])\
    \ {\n                queued[adjacent] = true;\n                candidates.push_back(adjacent);\n\
    \            }\n        }\n    }\n    if (remaining < 3) return std::nullopt;\n\
    \n    std::vector<PointType> polygon;\n    polygon.reserve(static_cast<std::size_t>(remaining));\n\
    \    int first = 0;\n    while (removed[first]) ++first;\n    int index = first;\n\
    \    do {\n        polygon.push_back(points[index]);\n        index = next[index];\n\
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
    \ + 1);\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_STEINER_CONVEX_DECOMPOSITION_HPP\n"
  dependsOn:
  - geometry/polygon.hpp
  - geometry/ray.hpp
  - geometry/line.hpp
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/steiner_convex_decomposition.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-22 13:48:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/steiner_convex_decomposition.test.cpp
  - verify/geometry/centroid.test.cpp
documentation_of: geometry/steiner_convex_decomposition.hpp
layout: document
title: Steiner Convex Decomposition
---

## Overview

`steiner_convex_decomposition` partitions a simple polygon without holes into
non-strictly convex polygons. It may introduce Steiner vertices on the input
boundary or on cuts made earlier in the construction.

The returned geometry is an exact partition in the geometric sense: the pieces
have disjoint interiors and their union is the input polygon. The approximation
guarantee concerns only the number of pieces. This distinction is important;
the polygon itself is not approximated.

The routine applies the reflex-ray decomposition of Chazelle and Dobkin. Each
cut starts at one reflex vertex, lies strictly inside its admissible angular
wedge, and stops at the first edge of the current subdivision. Convex-chain
preprocessing makes ray intersections sensitive to the number of reflex
vertices rather than requiring a scan of the full boundary for every cut.

## Function

```cpp
template <std::floating_point T>
std::optional<std::vector<std::vector<Point<long double>>>>
steiner_convex_decomposition(
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
);
```

| Function | Result | Time | Memory |
| --- | --- | --- | --- |
| `steiner_convex_decomposition(polygon, eps)` | An exact partition into $R+1$ convex pieces. | $O(N + R^2\log(2N/R))$ | $O(N+R)$ |

Here $N$ is the number of vertices after cleanup and $R$ is the number of
reflex vertices. For $R=0$, the function returns the cleaned polygon as its
only piece in $O(N)$ time; the logarithmic expression in the table applies
when $R>0$.

## Piece-count guarantee

Each cut removes one remaining reflex angle and increases the number of pieces
by one, so the result contains exactly $R+1$ pieces unless $R=0$.

Any convex decomposition in the unrestricted Steiner-point model contains at
least $\lceil R/2\rceil+1$ pieces: one new convex piece can remove at most two
reflex angles. Consequently this routine returns strictly fewer than twice the
minimum possible number of pieces.

This is not a minimum-cardinality routine. In particular, it does not implement
the much more involved X/Y-pattern dynamic program required for the optimal
$O(N+R^3)$ Chazelle--Dobkin algorithm. Use
[`minimum_convex_decomposition`](convex_decomposition.md) when minimum
cardinality is required and Steiner points are forbidden.

## Input and output rules

Only floating-point coordinate types are supported. Steiner intersections need
not be integral even when all input coordinates are integers, so an integral
overload is intentionally not provided. All output coordinates use
`long double`.

The input may be clockwise or counterclockwise. A repeated closing point,
consecutive duplicates, and redundant collinear boundary vertices are removed.
The polygon must be simple, have nonzero area, and have no holes. Simplicity is
a precondition so that validation does not add an $O(N^2)$ term to the stated
bound.

The return value is `nullopt` when fewer than three effective vertices remain,
the signed area is zero, or the floating-point construction cannot be completed
consistently. Every returned polygon is counterclockwise and convex in the
non-strict sense. `eps` controls floating-point predicates and degeneracy
handling.

## Example

```cpp
#include "geometry/steiner_convex_decomposition.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<double>;
    std::vector<Point> polygon;
    polygon.emplace_back(0, 0);
    polygon.emplace_back(5, 0);
    polygon.emplace_back(5, 2);
    polygon.emplace_back(2, 2);
    polygon.emplace_back(2, 5);
    polygon.emplace_back(0, 5);

    auto parts =
        m1une::geometry::steiner_convex_decomposition(polygon);
    if (!parts.has_value()) return 0;
    std::cout << parts->size() << "\n";  // 2
}
```
