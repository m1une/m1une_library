---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/detail/floating_predicate.hpp
    title: geometry/detail/floating_predicate.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/linear.hpp
    title: Linear Objects
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  - icon: ':heavy_check_mark:'
    path: geometry/convex_decomposition.hpp
    title: Convex Decomposition
  - icon: ':heavy_check_mark:'
    path: geometry/convex_polygon.hpp
    title: Convex Polygons
  - icon: ':heavy_check_mark:'
    path: geometry/steiner_convex_decomposition.hpp
    title: Steiner Convex Decomposition
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
    path: verify/geometry/point_in_polygon.test.cpp
    title: verify/geometry/point_in_polygon.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/polygon_area.test.cpp
    title: verify/geometry/polygon_area.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/polygon_operations.test.cpp
    title: verify/geometry/polygon_operations.test.cpp
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
  bundledCode: "#line 1 \"geometry/polygon.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <cmath>\n#include <cstddef>\n#include\
    \ <limits>\n#include <optional>\n#include <vector>\n\n#line 1 \"geometry/linear.hpp\"\
    \n\n\n\n#line 8 \"geometry/linear.hpp\"\n\n#line 1 \"geometry/point.hpp\"\n\n\n\
    \n#line 5 \"geometry/point.hpp\"\n#include <concepts>\n#line 7 \"geometry/point.hpp\"\
    \n#include <type_traits>\n\n#line 1 \"geometry/detail/floating_predicate.hpp\"\
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
    geometry/linear.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate\
    \ T>\nstruct Line {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate\
    \ T>\nstruct Segment {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate\
    \ T>\nstruct Ray {\n    Point<T> origin;\n    Point<T> through;\n};\n\nenum class\
    \ LinearIntersectionKind {\n    Empty,\n    Point,\n    Segment,\n    Ray,\n \
    \   Line,\n};\n\nstruct LinearIntersection {\n    LinearIntersectionKind kind;\n\
    \    Point<long double> first;\n    Point<long double> second;\n};\n\nnamespace\
    \ linear_intersection_detail {\n\ninline LinearIntersection make_empty() {\n \
    \   const Point<long double> zero;\n    return LinearIntersection{\n        LinearIntersectionKind::Empty,\n\
    \        zero,\n        zero,\n    };\n}\n\ntemplate <Coordinate T>\nLinearIntersection\
    \ make_point(const Point<T>& point) {\n    const Point<long double> converted(point);\n\
    \    return LinearIntersection{\n        LinearIntersectionKind::Point,\n    \
    \    converted,\n        converted,\n    };\n}\n\ntemplate <Coordinate T>\nLinearIntersection\
    \ make_object(\n    LinearIntersectionKind kind,\n    const Point<T>& first,\n\
    \    const Point<T>& second\n) {\n    return LinearIntersection{\n        kind,\n\
    \        Point<long double>(first),\n        Point<long double>(second),\n   \
    \ };\n}\n\ntemplate <Coordinate T>\nPoint<long double> crossing_point(\n    const\
    \ Line<T>& first,\n    const Line<T>& second\n) {\n    using W = wide_type<T>;\n\
    \    const W first_x = W(first.b.x) - W(first.a.x);\n    const W first_y = W(first.b.y)\
    \ - W(first.a.y);\n    const W second_x = W(second.b.x) - W(second.a.x);\n   \
    \ const W second_y = W(second.b.y) - W(second.a.y);\n    const W offset_x = W(second.a.x)\
    \ - W(first.a.x);\n    const W offset_y = W(second.a.y) - W(first.a.y);\n    const\
    \ W denominator =\n        first_x * second_y - first_y * second_x;\n    assert(denominator\
    \ != W(0));\n    const W numerator = offset_x * second_y - offset_y * second_x;\n\
    \    const long double ratio =\n        static_cast<long double>(numerator) /\n\
    \        static_cast<long double>(denominator);\n    return Point<long double>(\n\
    \        static_cast<long double>(first.a.x) +\n            static_cast<long double>(first_x)\
    \ * ratio,\n        static_cast<long double>(first.a.y) +\n            static_cast<long\
    \ double>(first_y) * ratio\n    );\n}\n\n}  // namespace linear_intersection_detail\n\
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
    long double distance(const Line<T>& line, const Point<T>& point) {\n    assert(line.a\
    \ != line.b);\n    Point<long double> direction(\n        static_cast<long double>(line.b.x)\
    \ - static_cast<long double>(line.a.x),\n        static_cast<long double>(line.b.y)\
    \ - static_cast<long double>(line.a.y)\n    );\n    Point<long double> offset(\n\
    \        static_cast<long double>(point.x) - static_cast<long double>(line.a.x),\n\
    \        static_cast<long double>(point.y) - static_cast<long double>(line.a.y)\n\
    \    );\n    return std::fabs(cross(direction, offset)) / norm(direction);\n}\n\
    \ntemplate <Coordinate T>\nlong double distance(const Point<T>& point, const Line<T>&\
    \ line) {\n    return distance(line, point);\n}\n\ntemplate <Coordinate T>\nbool\
    \ intersects(\n    const Line<T>& first,\n    const Line<T>& second,\n    long\
    \ double eps = 1e-12L\n) {\n    return !parallel(first, second, eps) || on_line(first,\
    \ second.a, eps);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Line<T>&\
    \ first, const Line<T>& second) {\n    return intersects(first, second) ? 0 :\
    \ distance(first, second.a);\n}\n\ntemplate <Coordinate T>\nbool on_segment(\n\
    \    const Segment<T>& segment,\n    const Point<T>& point,\n    long double eps\
    \ = 1e-12L\n) {\n    if (orientation(segment.a, segment.b, point, eps) != 0) return\
    \ false;\n    using W = wide_type<T>;\n    const W direction_x = W(segment.b.x)\
    \ - W(segment.a.x);\n    const W direction_y = W(segment.b.y) - W(segment.a.y);\n\
    \    if (direction_x == W(0) && direction_y == W(0)) {\n        if constexpr (std::integral<T>)\
    \ {\n            return point == segment.a;\n        } else {\n            return\n\
    \                predicate_detail::absolute(W(point.x) - W(segment.a.x)) <= eps\
    \ &&\n                predicate_detail::absolute(W(point.y) - W(segment.a.y))\
    \ <= eps;\n        }\n    }\n    const W offset_x = W(point.x) - W(segment.a.x);\n\
    \    const W offset_y = W(point.y) - W(segment.a.y);\n    const W projection =\n\
    \        offset_x * direction_x + offset_y * direction_y;\n    const W length_squared\
    \ =\n        direction_x * direction_x + direction_y * direction_y;\n    return\n\
    \        predicate_detail::scaled_sign<std::integral<T>>(\n            projection,\n\
    \            length_squared,\n            eps\n        ) >= 0 &&\n        predicate_detail::scaled_sign<std::integral<T>>(\n\
    \            projection - length_squared,\n            length_squared,\n     \
    \       eps\n        ) <= 0;\n}\n\ntemplate <Coordinate T>\nbool intersects(\n\
    \    const Segment<T>& first,\n    const Segment<T>& second,\n    long double\
    \ eps = 1e-12L\n) {\n    int abc = orientation(first.a, first.b, second.a, eps);\n\
    \    int abd = orientation(first.a, first.b, second.b, eps);\n    int cda = orientation(second.a,\
    \ second.b, first.a, eps);\n    int cdb = orientation(second.a, second.b, first.b,\
    \ eps);\n\n    if (abc == 0 && on_segment(first, second.a, eps)) return true;\n\
    \    if (abd == 0 && on_segment(first, second.b, eps)) return true;\n    if (cda\
    \ == 0 && on_segment(second, first.a, eps)) return true;\n    if (cdb == 0 &&\
    \ on_segment(second, first.b, eps)) return true;\n    return abc * abd < 0 &&\
    \ cda * cdb < 0;\n}\n\ntemplate <Coordinate T>\nbool intersects(\n    const Line<T>&\
    \ line,\n    const Segment<T>& segment,\n    long double eps = 1e-12L\n) {\n \
    \   int first_side = orientation(line.a, line.b, segment.a, eps);\n    int second_side\
    \ = orientation(line.a, line.b, segment.b, eps);\n    return first_side == 0 ||\
    \ second_side == 0 || first_side != second_side;\n}\n\ntemplate <Coordinate T>\n\
    bool intersects(\n    const Segment<T>& segment,\n    const Line<T>& line,\n \
    \   long double eps = 1e-12L\n) {\n    return intersects(line, segment, eps);\n\
    }\n\ntemplate <Coordinate T>\nlong double distance(const Segment<T>& segment,\
    \ const Point<T>& point) {\n    Point<long double> a(segment.a);\n    Point<long\
    \ double> b(segment.b);\n    Point<long double> p(point);\n    Point<long double>\
    \ direction = b - a;\n    long double length_squared = dot(direction, direction);\n\
    \    if (length_squared == 0) return geometry::distance(segment.a, point);\n \
    \   long double ratio = dot(p - a, direction) / length_squared;\n    ratio = std::clamp(ratio,\
    \ 0.0L, 1.0L);\n    Point<long double> closest = a + direction * ratio;\n    return\
    \ geometry::distance(closest, p);\n}\n\ntemplate <Coordinate T>\nlong double distance(const\
    \ Point<T>& point, const Segment<T>& segment) {\n    return distance(segment,\
    \ point);\n}\n\ntemplate <Coordinate T>\nlong double distance(const Segment<T>&\
    \ first, const Segment<T>& second) {\n    if (intersects(first, second)) return\
    \ 0;\n    return std::min({\n        distance(first, second.a),\n        distance(first,\
    \ second.b),\n        distance(second, first.a),\n        distance(second, first.b),\n\
    \    });\n}\n\ntemplate <Coordinate T>\nlong double distance(const Line<T>& line,\
    \ const Segment<T>& segment) {\n    if (intersects(line, segment)) return 0;\n\
    \    return std::min(distance(line, segment.a), distance(line, segment.b));\n\
    }\n\ntemplate <Coordinate T>\nlong double distance(const Segment<T>& segment,\
    \ const Line<T>& line) {\n    return distance(line, segment);\n}\n\ntemplate <Coordinate\
    \ T>\nLinearIntersection linear_intersection(\n    const Line<T>& first,\n   \
    \ const Line<T>& second,\n    long double eps = 1e-12L\n) {\n    assert(first.a\
    \ != first.b);\n    assert(second.a != second.b);\n    if (parallel(first, second,\
    \ eps)) {\n        if (on_line(first, second.a, eps)) {\n            return linear_intersection_detail::make_object(\n\
    \                LinearIntersectionKind::Line,\n                first.a,\n   \
    \             first.b\n            );\n        }\n        return linear_intersection_detail::make_empty();\n\
    \    }\n    return linear_intersection_detail::make_point(\n        linear_intersection_detail::crossing_point(first,\
    \ second)\n    );\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Line<T>& line,\n    const Segment<T>& segment,\n    long double eps\
    \ = 1e-12L\n) {\n    assert(line.a != line.b);\n    if (!intersects(line, segment,\
    \ eps)) {\n        return linear_intersection_detail::make_empty();\n    }\n \
    \   if (segment.a == segment.b) {\n        return linear_intersection_detail::make_point(segment.a);\n\
    \    }\n\n    const int first_side =\n        orientation(line.a, line.b, segment.a,\
    \ eps);\n    const int second_side =\n        orientation(line.a, line.b, segment.b,\
    \ eps);\n    if (first_side == 0 && second_side == 0) {\n        return linear_intersection_detail::make_object(\n\
    \            LinearIntersectionKind::Segment,\n            segment.a,\n      \
    \      segment.b\n        );\n    }\n    if (first_side == 0) {\n        return\
    \ linear_intersection_detail::make_point(segment.a);\n    }\n    if (second_side\
    \ == 0) {\n        return linear_intersection_detail::make_point(segment.b);\n\
    \    }\n\n    return linear_intersection_detail::make_point(\n        linear_intersection_detail::crossing_point(\n\
    \            line,\n            Line<T>{segment.a, segment.b}\n        )\n   \
    \ );\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Segment<T>& segment,\n    const Line<T>& line,\n    long double eps\
    \ = 1e-12L\n) {\n    return linear_intersection(line, segment, eps);\n}\n\ntemplate\
    \ <Coordinate T>\nLinearIntersection linear_intersection(\n    const Segment<T>&\
    \ first,\n    const Segment<T>& second,\n    long double eps = 1e-12L\n) {\n \
    \   if (!intersects(first, second, eps)) {\n        return linear_intersection_detail::make_empty();\n\
    \    }\n    if (first.a == first.b) {\n        return linear_intersection_detail::make_point(first.a);\n\
    \    }\n    if (second.a == second.b) {\n        return linear_intersection_detail::make_point(second.a);\n\
    \    }\n\n    const int first_a_side =\n        orientation(second.a, second.b,\
    \ first.a, eps);\n    const int first_b_side =\n        orientation(second.a,\
    \ second.b, first.b, eps);\n    const int second_a_side =\n        orientation(first.a,\
    \ first.b, second.a, eps);\n    const int second_b_side =\n        orientation(first.a,\
    \ first.b, second.b, eps);\n    const bool collinear_intersection =\n        first_a_side\
    \ == 0 && first_b_side == 0 &&\n        second_a_side == 0 && second_b_side ==\
    \ 0;\n\n    if (!collinear_intersection) {\n        if (first_a_side == 0 && on_segment(second,\
    \ first.a, eps)) {\n            return linear_intersection_detail::make_point(first.a);\n\
    \        }\n        if (first_b_side == 0 && on_segment(second, first.b, eps))\
    \ {\n            return linear_intersection_detail::make_point(first.b);\n   \
    \     }\n        if (second_a_side == 0 && on_segment(first, second.a, eps)) {\n\
    \            return linear_intersection_detail::make_point(second.a);\n      \
    \  }\n        if (second_b_side == 0 && on_segment(first, second.b, eps)) {\n\
    \            return linear_intersection_detail::make_point(second.b);\n      \
    \  }\n        return linear_intersection_detail::make_point(\n            linear_intersection_detail::crossing_point(\n\
    \                Line<T>{first.a, first.b},\n                Line<T>{second.a,\
    \ second.b}\n            )\n        );\n    }\n\n    std::array<Point<T>, 4> candidates{\n\
    \        first.a,\n        first.b,\n        second.a,\n        second.b,\n  \
    \  };\n    std::array<Point<T>, 4> common;\n    int common_size = 0;\n    long\
    \ double overlap_scale = 0.0L;\n    if constexpr (!std::integral<T>) {\n     \
    \   overlap_scale = std::max(\n            geometry::distance(first.a, first.b),\n\
    \            geometry::distance(second.a, second.b)\n        );\n    }\n    auto\
    \ same_point = [eps, overlap_scale](\n        const Point<T>& left,\n        const\
    \ Point<T>& right\n    ) {\n        if constexpr (std::integral<T>) {\n      \
    \      return left == right;\n        } else {\n            return geometry::distance(left,\
    \ right) <= eps * overlap_scale;\n        }\n    };\n    for (const Point<T>&\
    \ candidate : candidates) {\n        if (\n            !on_segment(first, candidate,\
    \ eps) ||\n            !on_segment(second, candidate, eps)\n        ) {\n    \
    \        continue;\n        }\n        bool duplicate = false;\n        for (int\
    \ index = 0; index < common_size; ++index) {\n            if (same_point(common[index],\
    \ candidate)) {\n                duplicate = true;\n                break;\n \
    \           }\n        }\n        if (!duplicate) common[common_size++] = candidate;\n\
    \    }\n    assert(common_size >= 1);\n\n    using W = wide_type<T>;\n    const\
    \ W direction_x = W(first.b.x) - W(first.a.x);\n    const W direction_y = W(first.b.y)\
    \ - W(first.a.y);\n    const W absolute_x = direction_x >= 0 ? direction_x : -direction_x;\n\
    \    const W absolute_y = direction_y >= 0 ? direction_y : -direction_y;\n   \
    \ const bool use_x = absolute_x >= absolute_y;\n    auto parameter = [&](const\
    \ Point<T>& point) {\n        if (use_x) {\n            return direction_x >=\
    \ 0 ? W(point.x) : -W(point.x);\n        }\n        return direction_y >= 0 ?\
    \ W(point.y) : -W(point.y);\n    };\n    int start_index = 0;\n    int finish_index\
    \ = 0;\n    for (int index = 1; index < common_size; ++index) {\n        if (parameter(common[index])\
    \ < parameter(common[start_index])) {\n            start_index = index;\n    \
    \    }\n        if (parameter(common[finish_index]) < parameter(common[index]))\
    \ {\n            finish_index = index;\n        }\n    }\n\n    if (same_point(common[start_index],\
    \ common[finish_index])) {\n        return linear_intersection_detail::make_point(common[start_index]);\n\
    \    }\n    return linear_intersection_detail::make_object(\n        LinearIntersectionKind::Segment,\n\
    \        common[start_index],\n        common[finish_index]\n    );\n}\n\nnamespace\
    \ ray_detail {\n\ntemplate <Coordinate T>\nstruct Parameters {\n    wide_type<T>\
    \ denominator;\n    wide_type<T> denominator_scale;\n    wide_type<T> first_numerator;\n\
    \    wide_type<T> second_numerator;\n};\n\ntemplate <Coordinate T>\nParameters<T>\
    \ parameters(\n    const Point<T>& first_origin,\n    const Point<T>& first_through,\n\
    \    const Point<T>& second_origin,\n    const Point<T>& second_through\n) {\n\
    \    using W = wide_type<T>;\n    W first_x = W(first_through.x) - W(first_origin.x);\n\
    \    W first_y = W(first_through.y) - W(first_origin.y);\n    W second_x = W(second_through.x)\
    \ - W(second_origin.x);\n    W second_y = W(second_through.y) - W(second_origin.y);\n\
    \    W offset_x = W(second_origin.x) - W(first_origin.x);\n    W offset_y = W(second_origin.y)\
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
    \ <= 0;\n    }\n    return start_sign <= 0 && finish_sign >= 0;\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> point_at(\n    const Ray<T>& ray,\n    wide_type<T>\
    \ numerator,\n    wide_type<T> denominator\n) {\n    long double ratio =\n   \
    \     static_cast<long double>(numerator) /\n        static_cast<long double>(denominator);\n\
    \    Point<long double> origin(ray.origin);\n    Point<long double> direction\
    \ =\n        Point<long double>(ray.through) - origin;\n    return origin + direction\
    \ * ratio;\n}\n\n}  // namespace ray_detail\n\ntemplate <Coordinate T>\nbool on_ray(\n\
    \    const Ray<T>& ray,\n    const Point<T>& point,\n    long double eps = 1e-12L\n\
    ) {\n    assert(ray.origin != ray.through);\n    if (orientation(ray.origin, ray.through,\
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
    \        line.a,\n        line.b\n    );\n    if (ray_detail::denominator_sign(values,\
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
    \    );\n    if (ray_detail::denominator_sign(values, eps) == 0) {\n        if\
    \ (orientation(ray.origin, ray.through, segment.a, eps) != 0) {\n            return\
    \ false;\n        }\n        return on_ray(ray, segment.a, eps) ||\n         \
    \      on_ray(ray, segment.b, eps) ||\n               on_segment(segment, ray.origin,\
    \ eps);\n    }\n    return ray_detail::ratio_nonnegative<T>(\n               values.first_numerator,\n\
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
    \    if (ray_detail::denominator_sign(values, eps) == 0) {\n        if (orientation(first.origin,\
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
    LinearIntersection linear_intersection(\n    const Ray<T>& ray,\n    const Line<T>&\
    \ line,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin != ray.through);\n\
    \    assert(line.a != line.b);\n    const ray_detail::Parameters<T> values = ray_detail::parameters(\n\
    \        ray.origin,\n        ray.through,\n        line.a,\n        line.b\n\
    \    );\n    if (ray_detail::denominator_sign(values, eps) == 0) {\n        if\
    \ (on_line(line, ray.origin, eps)) {\n            return linear_intersection_detail::make_object(\n\
    \                LinearIntersectionKind::Ray,\n                ray.origin,\n \
    \               ray.through\n            );\n        }\n        return linear_intersection_detail::make_empty();\n\
    \    }\n    if (\n        !ray_detail::ratio_nonnegative<T>(\n            values.first_numerator,\n\
    \            values.denominator,\n            eps\n        )\n    ) {\n      \
    \  return linear_intersection_detail::make_empty();\n    }\n    return linear_intersection_detail::make_point(\n\
    \        ray_detail::point_at(\n            ray,\n            values.first_numerator,\n\
    \            values.denominator\n        )\n    );\n}\n\ntemplate <Coordinate\
    \ T>\nLinearIntersection linear_intersection(\n    const Line<T>& line,\n    const\
    \ Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return linear_intersection(ray,\
    \ line, eps);\n}\n\ntemplate <Coordinate T>\nLinearIntersection linear_intersection(\n\
    \    const Ray<T>& ray,\n    const Segment<T>& segment,\n    long double eps =\
    \ 1e-12L\n) {\n    assert(ray.origin != ray.through);\n    if (segment.a == segment.b)\
    \ {\n        if (on_ray(ray, segment.a, eps)) {\n            return linear_intersection_detail::make_point(segment.a);\n\
    \        }\n        return linear_intersection_detail::make_empty();\n    }\n\n\
    \    const ray_detail::Parameters<T> values = ray_detail::parameters(\n      \
    \  ray.origin,\n        ray.through,\n        segment.a,\n        segment.b\n\
    \    );\n    if (ray_detail::denominator_sign(values, eps) != 0) {\n        if\
    \ (\n            !ray_detail::ratio_nonnegative<T>(\n                values.first_numerator,\n\
    \                values.denominator,\n                eps\n            ) ||\n\
    \            !ray_detail::ratio_in_unit_interval<T>(\n                values.second_numerator,\n\
    \                values.denominator,\n                eps\n            )\n   \
    \     ) {\n            return linear_intersection_detail::make_empty();\n    \
    \    }\n        return linear_intersection_detail::make_point(\n            ray_detail::point_at(\n\
    \                ray,\n                values.first_numerator,\n             \
    \   values.denominator\n            )\n        );\n    }\n    if (orientation(ray.origin,\
    \ ray.through, segment.a, eps) != 0) {\n        return linear_intersection_detail::make_empty();\n\
    \    }\n\n    std::array<Point<T>, 3> candidates{\n        ray.origin,\n     \
    \   segment.a,\n        segment.b,\n    };\n    std::array<Point<T>, 3> common;\n\
    \    int common_size = 0;\n    long double object_scale = 0.0L;\n    if constexpr\
    \ (!std::integral<T>) {\n        object_scale = std::max(\n            geometry::distance(ray.origin,\
    \ ray.through),\n            geometry::distance(segment.a, segment.b)\n      \
    \  );\n    }\n    auto same_point = [eps, object_scale](\n        const Point<T>&\
    \ first,\n        const Point<T>& second\n    ) {\n        if constexpr (std::integral<T>)\
    \ {\n            return first == second;\n        } else {\n            return\n\
    \                geometry::distance(first, second) <= eps * object_scale;\n  \
    \      }\n    };\n    for (const Point<T>& candidate : candidates) {\n       \
    \ if (\n            !on_ray(ray, candidate, eps) ||\n            !on_segment(segment,\
    \ candidate, eps)\n        ) {\n            continue;\n        }\n        bool\
    \ duplicate = false;\n        for (int index = 0; index < common_size; ++index)\
    \ {\n            if (same_point(common[index], candidate)) {\n               \
    \ duplicate = true;\n                break;\n            }\n        }\n      \
    \  if (!duplicate) common[common_size++] = candidate;\n    }\n    if (common_size\
    \ == 0) {\n        return linear_intersection_detail::make_empty();\n    }\n\n\
    \    using W = wide_type<T>;\n    const W direction_x = W(ray.through.x) - W(ray.origin.x);\n\
    \    const W direction_y = W(ray.through.y) - W(ray.origin.y);\n    const W absolute_x\
    \ = predicate_detail::absolute(direction_x);\n    const W absolute_y = predicate_detail::absolute(direction_y);\n\
    \    const bool use_x = absolute_x >= absolute_y;\n    auto parameter = [&](const\
    \ Point<T>& point) {\n        if (use_x) {\n            return direction_x >=\
    \ 0 ? W(point.x) : -W(point.x);\n        }\n        return direction_y >= 0 ?\
    \ W(point.y) : -W(point.y);\n    };\n    int start_index = 0;\n    int finish_index\
    \ = 0;\n    for (int index = 1; index < common_size; ++index) {\n        if (parameter(common[index])\
    \ < parameter(common[start_index])) {\n            start_index = index;\n    \
    \    }\n        if (parameter(common[finish_index]) < parameter(common[index]))\
    \ {\n            finish_index = index;\n        }\n    }\n    if (same_point(common[start_index],\
    \ common[finish_index])) {\n        return linear_intersection_detail::make_point(common[start_index]);\n\
    \    }\n    return linear_intersection_detail::make_object(\n        LinearIntersectionKind::Segment,\n\
    \        common[start_index],\n        common[finish_index]\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nLinearIntersection linear_intersection(\n    const Segment<T>&\
    \ segment,\n    const Ray<T>& ray,\n    long double eps = 1e-12L\n) {\n    return\
    \ linear_intersection(ray, segment, eps);\n}\n\ntemplate <Coordinate T>\nLinearIntersection\
    \ linear_intersection(\n    const Ray<T>& first,\n    const Ray<T>& second,\n\
    \    long double eps = 1e-12L\n) {\n    assert(first.origin != first.through);\n\
    \    assert(second.origin != second.through);\n    const ray_detail::Parameters<T>\
    \ values = ray_detail::parameters(\n        first.origin,\n        first.through,\n\
    \        second.origin,\n        second.through\n    );\n    if (ray_detail::denominator_sign(values,\
    \ eps) != 0) {\n        if (\n            !ray_detail::ratio_nonnegative<T>(\n\
    \                values.first_numerator,\n                values.denominator,\n\
    \                eps\n            ) ||\n            !ray_detail::ratio_nonnegative<T>(\n\
    \                values.second_numerator,\n                values.denominator,\n\
    \                eps\n            )\n        ) {\n            return linear_intersection_detail::make_empty();\n\
    \        }\n        return linear_intersection_detail::make_point(\n         \
    \   ray_detail::point_at(\n                first,\n                values.first_numerator,\n\
    \                values.denominator\n            )\n        );\n    }\n    if\
    \ (\n        orientation(\n            first.origin,\n            first.through,\n\
    \            second.origin,\n            eps\n        ) != 0\n    ) {\n      \
    \  return linear_intersection_detail::make_empty();\n    }\n\n    using W = wide_type<T>;\n\
    \    const W first_x = W(first.through.x) - W(first.origin.x);\n    const W first_y\
    \ = W(first.through.y) - W(first.origin.y);\n    const W second_x = W(second.through.x)\
    \ - W(second.origin.x);\n    const W second_y = W(second.through.y) - W(second.origin.y);\n\
    \    const int direction_relation =\n        predicate_detail::dot_sign<std::integral<T>>(\n\
    \            first_x,\n            first_y,\n            second_x,\n         \
    \   second_y,\n            eps\n        );\n\n    bool same_origin;\n    if constexpr\
    \ (std::integral<T>) {\n        same_origin = first.origin == second.origin;\n\
    \    } else {\n        const long double object_scale = std::max(\n          \
    \  geometry::distance(first.origin, first.through),\n            geometry::distance(second.origin,\
    \ second.through)\n        );\n        same_origin =\n            geometry::distance(first.origin,\
    \ second.origin) <=\n            eps * object_scale;\n    }\n    if (same_origin)\
    \ {\n        if (direction_relation < 0) {\n            return linear_intersection_detail::make_point(first.origin);\n\
    \        }\n        return linear_intersection_detail::make_object(\n        \
    \    LinearIntersectionKind::Ray,\n            first.origin,\n            first.through\n\
    \        );\n    }\n\n    const bool first_contains_second =\n        on_ray(first,\
    \ second.origin, eps);\n    const bool second_contains_first =\n        on_ray(second,\
    \ first.origin, eps);\n    if (direction_relation >= 0) {\n        if (first_contains_second)\
    \ {\n            return linear_intersection_detail::make_object(\n           \
    \     LinearIntersectionKind::Ray,\n                second.origin,\n         \
    \       second.through\n            );\n        }\n        if (second_contains_first)\
    \ {\n            return linear_intersection_detail::make_object(\n           \
    \     LinearIntersectionKind::Ray,\n                first.origin,\n          \
    \      first.through\n            );\n        }\n        return linear_intersection_detail::make_empty();\n\
    \    }\n    if (first_contains_second && second_contains_first) {\n        return\
    \ linear_intersection_detail::make_object(\n            LinearIntersectionKind::Segment,\n\
    \            first.origin,\n            second.origin\n        );\n    }\n   \
    \ return linear_intersection_detail::make_empty();\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n#line 14 \"geometry/polygon.hpp\"\n\nnamespace m1une\
    \ {\nnamespace geometry {\n\nenum class PointInPolygon {\n    Outside = 0,\n \
    \   Boundary = 1,\n    Inside = 2,\n};\n\ntemplate <Coordinate T>\nconstexpr Point<long\
    \ double> centroid(\n    const std::array<Point<T>, 3>& triangle\n) {\n    return\
    \ Point<long double>(\n        (\n            static_cast<long double>(triangle[0].x)\
    \ +\n            static_cast<long double>(triangle[1].x) +\n            static_cast<long\
    \ double>(triangle[2].x)\n        ) / 3,\n        (\n            static_cast<long\
    \ double>(triangle[0].y) +\n            static_cast<long double>(triangle[1].y)\
    \ +\n            static_cast<long double>(triangle[2].y)\n        ) / 3\n    );\n\
    }\n\nnamespace polygon_detail {\n\ninline bool close(\n    const Point<long double>&\
    \ first,\n    const Point<long double>& second,\n    long double eps\n) {\n  \
    \  return geometry::distance(first, second) <= eps;\n}\n\ninline void push_unique(\n\
    \    std::vector<Point<long double>>& points,\n    const Point<long double>& point,\n\
    \    long double eps\n) {\n    for (const Point<long double>& existing : points)\
    \ {\n        if (close(existing, point, eps)) return;\n    }\n    points.push_back(point);\n\
    }\n\ntemplate <Coordinate T>\nstd::vector<Point<T>> clean_polygon_vertices(\n\
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
    \ : PointInPolygon::Outside;\n}\n\ntemplate <Coordinate T>\nstd::vector<Point<long\
    \ double>> ray_polygon_intersections(\n    const Ray<T>& ray,\n    const std::vector<Point<T>>&\
    \ polygon,\n    long double eps = 1e-12L\n) {\n    assert(ray.origin != ray.through);\n\
    \    assert(polygon.size() >= 3);\n    std::vector<Point<long double>> result;\n\
    \    std::size_t size = polygon.size();\n    for (std::size_t index = 0; index\
    \ < size; ++index) {\n        Segment<T> edge{\n            polygon[index],\n\
    \            polygon[(index + 1) % size]\n        };\n        const LinearIntersection\
    \ intersection =\n            linear_intersection(ray, edge, eps);\n        if\
    \ (intersection.kind == LinearIntersectionKind::Point) {\n            polygon_detail::push_unique(result,\
    \ intersection.first, eps);\n        } else if (intersection.kind == LinearIntersectionKind::Segment)\
    \ {\n            polygon_detail::push_unique(result, intersection.first, eps);\n\
    \            polygon_detail::push_unique(result, intersection.second, eps);\n\
    \        } else {\n            assert(intersection.kind == LinearIntersectionKind::Empty);\n\
    \        }\n    }\n\n    Point<long double> origin(ray.origin);\n    Point<long\
    \ double> direction =\n        Point<long double>(ray.through) - origin;\n   \
    \ std::sort(\n        result.begin(),\n        result.end(),\n        [&](const\
    \ Point<long double>& first, const Point<long double>& second) {\n           \
    \ return dot(first - origin, direction) <\n                   dot(second - origin,\
    \ direction);\n        }\n    );\n    return result;\n}\n\ntemplate <Coordinate\
    \ T>\nstd::optional<Point<long double>> first_ray_polygon_intersection(\n    const\
    \ Ray<T>& ray,\n    const std::vector<Point<T>>& polygon,\n    long double eps\
    \ = 1e-12L\n) {\n    std::vector<Point<long double>> points =\n        ray_polygon_intersections(ray,\
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
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_POLYGON_HPP\n#define M1UNE_GEOMETRY_POLYGON_HPP 1\n\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <cstddef>\n#include <limits>\n#include <optional>\n#include <vector>\n\
    \n#include \"linear.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\nenum class\
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
    \            polygon[(index + 1) % size]\n        };\n        const LinearIntersection\
    \ intersection =\n            linear_intersection(ray, edge, eps);\n        if\
    \ (intersection.kind == LinearIntersectionKind::Point) {\n            polygon_detail::push_unique(result,\
    \ intersection.first, eps);\n        } else if (intersection.kind == LinearIntersectionKind::Segment)\
    \ {\n            polygon_detail::push_unique(result, intersection.first, eps);\n\
    \            polygon_detail::push_unique(result, intersection.second, eps);\n\
    \        } else {\n            assert(intersection.kind == LinearIntersectionKind::Empty);\n\
    \        }\n    }\n\n    Point<long double> origin(ray.origin);\n    Point<long\
    \ double> direction =\n        Point<long double>(ray.through) - origin;\n   \
    \ std::sort(\n        result.begin(),\n        result.end(),\n        [&](const\
    \ Point<long double>& first, const Point<long double>& second) {\n           \
    \ return dot(first - origin, direction) <\n                   dot(second - origin,\
    \ direction);\n        }\n    );\n    return result;\n}\n\ntemplate <Coordinate\
    \ T>\nstd::optional<Point<long double>> first_ray_polygon_intersection(\n    const\
    \ Ray<T>& ray,\n    const std::vector<Point<T>>& polygon,\n    long double eps\
    \ = 1e-12L\n) {\n    std::vector<Point<long double>> points =\n        ray_polygon_intersections(ray,\
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
    }  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_POLYGON_HPP\n"
  dependsOn:
  - geometry/linear.hpp
  - geometry/point.hpp
  - geometry/detail/floating_predicate.hpp
  isVerificationFile: false
  path: geometry/polygon.hpp
  requiredBy:
  - geometry/all.hpp
  - geometry/steiner_convex_decomposition.hpp
  - geometry/convex_polygon.hpp
  - geometry/convex_decomposition.hpp
  timestamp: '2026-08-20 21:54:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/polygon_operations.test.cpp
  - verify/geometry/polygon_operations.test.cpp
  - verify/geometry/point_in_polygon.test.cpp
  - verify/geometry/convex_polygon.test.cpp
  - verify/geometry/is_convex_polygon.test.cpp
  - verify/geometry/centroid.test.cpp
  - verify/geometry/steiner_convex_decomposition.test.cpp
  - verify/geometry/convex_diameter.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/polygon_area.test.cpp
  - verify/geometry/convex_decomposition.test.cpp
documentation_of: geometry/polygon.hpp
layout: document
title: Polygons
---

## Overview

This header provides polygon area, point containment, ray queries, polygon
intersection and distance, triangulation, and centroids for general simple
polygons.

Polygons are represented by `std::vector<Point<T>>`. The first point must not be
repeated at the end.

## Point Containment

`point_in_polygon` returns:

* `PointInPolygon::Outside`
* `PointInPolygon::Boundary`
* `PointInPolygon::Inside`

The polygon may be clockwise or counterclockwise and may be non-convex.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `centroid(triangle)` | Returns the filled triangle's centroid. The triangle is a `std::array<Point<T>, 3>`. | $O(1)$ |
| `centroid(polygon, eps)` | Returns the uniformly filled polygon's centroid, or `nullopt` for zero area. | $O(N)$ |
| `polygon_area2(polygon)` | Returns signed twice-area. Positive means counterclockwise. | $O(N)$ |
| `polygon_area(polygon)` | Returns absolute area as `long double`. | $O(N)$ |
| `polygon_centroid(polygon, eps)` | Returns the centroid of a uniformly filled polygon, or `nullopt` for zero area. | $O(N)$ |
| `polygon_center_of_gravity(polygon, eps)` | Alias of `polygon_centroid`. | $O(N)$ |
| `is_simple_polygon(polygon, eps)` | Tests whether polygon edges only meet at adjacent endpoints. | $O(N^2)$ |
| `triangulate_polygon(polygon, eps)` | Ear-clips a simple polygon, or returns `nullopt` when triangulation fails. | $O(N^2)$ |
| `point_in_polygon(polygon, point, eps)` | Classifies a point against any simple polygon. | $O(N)$ |
| `ray_polygon_intersections(ray, polygon, eps)` | Returns distinct boundary events ordered from the ray origin. | $O(N \log N)$ |
| `first_ray_polygon_intersection(ray, polygon, eps)` | Returns the first boundary event, or `nullopt`. | $O(N \log N)$ |
| `intersects(ray, polygon, eps)` | Tests intersection with the closed filled polygon. Both argument orders are supported. | $O(N \log N)$ |
| `distance(ray, polygon)` | Minimum distance to the closed filled polygon. Both argument orders are supported. | $O(N \log N)$ |
| `intersects(first, second, eps)` | Tests whether two closed filled simple polygons intersect. | $O(NM)$ |
| `distance(first, second)` | Minimum distance between two closed filled simple polygons. | $O(NM)$ |

Polygon queries require at least three vertices unless stated otherwise.

## Centroid and center of gravity

`centroid(polygon)` and `polygon_centroid` compute the center of gravity of a
lamina with uniform density over the polygon's filled area.
`centroid(polygon)` is the geometry-wide overload and `polygon_centroid` is its
explicitly named equivalent. Both accept clockwise or counterclockwise simple
polygons and return `std::optional<Point<long double>>`.

A polygon with zero signed area has no area centroid, so the function returns
`std::nullopt`. This is different from the arithmetic mean of the vertices,
which generally is not the polygon's center of gravity.

For a triangle represented by `std::array<Point<T>, 3>`, `centroid(triangle)`
returns the arithmetic mean of its three vertices. This formula is also the
usual filled-area centroid for every nondegenerate triangle.

## Triangulation

`triangulate_polygon` uses ear clipping and accepts clockwise or
counterclockwise simple polygons. It removes a repeated closing point,
consecutive duplicate points, and redundant collinear boundary vertices before
triangulation. The result contains counterclockwise triangles whose interiors
are disjoint and whose union is the polygon. An input with $K$ remaining
vertices produces $K-2$ triangles.

The return value is `std::nullopt` for fewer than three effective vertices,
zero area, self-intersection, or another failure to find a valid ear.

## Ray intersections

`ray_polygon_intersections` reports polygon-boundary events, not the whole
filled interval inside the polygon. A collinear boundary overlap contributes
its finite endpoints and the ray origin when the overlap starts there. Shared
polygon vertices are deduplicated.

`intersects(ray, polygon)` instead treats the polygon as a closed filled region,
so a ray whose origin is inside the polygon intersects immediately.

## Polygon intersection and distance

`intersects(first, second)` and `distance(first, second)` accept any simple
polygons, in clockwise or counterclockwise order.

For optimized containment, cuts, diameter, intersection construction,
Minkowski sums, and other convex-only operations, include
[`geometry/convex_polygon.hpp`](convex_polygon.md).

To partition a simple polygon into convex pieces, include
[`geometry/convex_decomposition.hpp`](convex_decomposition.md). It provides a
fast exact partition with a four-approximation guarantee on the piece count,
and an exact minimum-piece dynamic program.

## Example

```cpp
#include "geometry/polygon.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> polygon;
    polygon.emplace_back(0, 0);
    polygon.emplace_back(2, 0);
    polygon.emplace_back(0, 2);

    std::cout << m1une::geometry::polygon_area(polygon) << "\n"; // 2
}
```
