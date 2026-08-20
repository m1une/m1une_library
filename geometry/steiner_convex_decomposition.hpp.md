---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/circle.hpp
    title: Circles
  - icon: ':heavy_check_mark:'
    path: geometry/detail/floating_predicate.hpp
    title: geometry/detail/floating_predicate.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/linear.hpp
    title: Linear Objects
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/polygon.hpp
    title: Polygons
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
    \n#include <array>\n#include <cassert>\n#line 11 \"geometry/polygon.hpp\"\n#include\
    \ <type_traits>\n#line 13 \"geometry/polygon.hpp\"\n\n#line 1 \"geometry/circle.hpp\"\
    \n\n\n\n#line 9 \"geometry/circle.hpp\"\n#include <numbers>\n#line 13 \"geometry/circle.hpp\"\
    \n\n#line 1 \"geometry/linear.hpp\"\n\n\n\n#line 7 \"geometry/linear.hpp\"\n\n\
    #line 1 \"geometry/point.hpp\"\n\n\n\n#line 8 \"geometry/point.hpp\"\n\n#line\
    \ 1 \"geometry/detail/floating_predicate.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ geometry {\nnamespace predicate_detail {\n\ntemplate <typename T>\nconstexpr\
    \ T absolute(T value) {\n    return value < T(0) ? -value : value;\n}\n\ntemplate\
    \ <typename T>\nconstexpr T max_value(T first, T second) {\n    return first <\
    \ second ? second : first;\n}\n\ntemplate <typename T>\nconstexpr T vector_scale(T\
    \ x, T y) {\n    return max_value(absolute(x), absolute(y));\n}\n\ntemplate <bool\
    \ Exact, typename T>\nconstexpr int scaled_sign(T value, T scale, long double\
    \ eps) {\n    if constexpr (Exact) {\n        return (value > T(0)) - (value <\
    \ T(0));\n    } else {\n        const T tolerance = T(eps) * scale;\n        return\
    \ (value > tolerance) - (value < -tolerance);\n    }\n}\n\ntemplate <bool Exact,\
    \ typename T>\nconstexpr T determinant_scale(T ax, T ay, T bx, T by) {\n    if\
    \ constexpr (Exact) {\n        return T(0);\n    } else {\n        return vector_scale(ax,\
    \ ay) * vector_scale(bx, by);\n    }\n}\n\ntemplate <bool Exact, typename T>\n\
    constexpr int determinant_sign(\n    T ax,\n    T ay,\n    T bx,\n    T by,\n\
    \    long double eps\n) {\n    const T determinant = ax * by - ay * bx;\n    return\
    \ scaled_sign<Exact>(\n        determinant,\n        determinant_scale<Exact>(ax,\
    \ ay, bx, by),\n        eps\n    );\n}\n\ntemplate <bool Exact, typename T>\n\
    constexpr int orientation_sign(\n    T direction_x,\n    T direction_y,\n    T\
    \ offset_x,\n    T offset_y,\n    long double eps\n) {\n    const T determinant\
    \ =\n        direction_x * offset_y - direction_y * offset_x;\n    T scale = T(0);\n\
    \    if constexpr (!Exact) {\n        const T direction_scale =\n            vector_scale(direction_x,\
    \ direction_y);\n        scale = direction_scale * max_value(\n            direction_scale,\n\
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
    \    );\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 9 \"\
    geometry/linear.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <Coordinate\
    \ T>\nstruct Line {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate\
    \ T>\nstruct Segment {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate <Coordinate\
    \ T>\nstruct Ray {\n    Point<T> origin;\n    Point<T> through;\n};\n\nenum class\
    \ LinearIntersectionKind {\n    Empty,\n    Point,\n    Segment,\n    Ray,\n \
    \   Line,\n};\n\nstruct LinearIntersection {\n    LinearIntersectionKind kind;\n\
    \    Point<long double> first;\n    Point<long double> second;\n};\n\nstruct ClosestPoints\
    \ {\n    Point<long double> first;\n    Point<long double> second;\n};\n\nnamespace\
    \ linear_intersection_detail {\n\ninline LinearIntersection make_empty() {\n \
    \   const Point<long double> zero;\n    return LinearIntersection{\n        LinearIntersectionKind::Empty,\n\
    \        zero,\n        zero,\n    };\n}\n\ntemplate <Coordinate T>\nLinearIntersection\
    \ make_point(const Point<T>& point) {\n    const Point<long double> converted(point);\n\
    \    return LinearIntersection{\n        LinearIntersectionKind::Point,\n    \
    \    converted,\n        converted,\n    };\n}\n\ntemplate <Coordinate T>\nLinearIntersection\
    \ make_object(\n    LinearIntersectionKind kind,\n    const Point<T>& first,\n\
    \    const Point<T>& second\n) {\n    return LinearIntersection{\n        kind,\n\
    \        Point<long double>(first),\n        Point<long double>(second),\n   \
    \ };\n}\n\n}  // namespace linear_intersection_detail\n\ntemplate <Coordinate\
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
    \    W second_y = W(second.b.y) - W(second.a.y);\n    return predicate_detail::determinant_sign<std::integral<T>>(\n\
    \        first_x,\n        first_y,\n        second_x,\n        second_y,\n  \
    \      eps\n    ) == 0;\n}\n\ntemplate <Coordinate T>\nbool orthogonal(const Line<T>&\
    \ first, const Line<T>& second, long double eps = 1e-12L) {\n    using W = wide_type<T>;\n\
    \    W first_x = W(first.b.x) - W(first.a.x);\n    W first_y = W(first.b.y) -\
    \ W(first.a.y);\n    W second_x = W(second.b.x) - W(second.a.x);\n    W second_y\
    \ = W(second.b.y) - W(second.a.y);\n    return predicate_detail::dot_sign<std::integral<T>>(\n\
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
    }  // namespace m1une\n\n\n#line 15 \"geometry/circle.hpp\"\n\nnamespace m1une\
    \ {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct Circle {\n    Point<T>\
    \ center;\n    T radius;\n    bool filled = true;\n};\n\nenum class PointInCircle\
    \ {\n    Outside = 0,\n    Boundary = 1,\n    Inside = 2,\n};\n\nenum class CircleRelation\
    \ {\n    Separate,\n    ExternallyTangent,\n    Intersecting,\n    InternallyTangent,\n\
    \    Contained,\n    Coincident,\n};\n\nenum class AngularCoverageKind {\n   \
    \ Empty,\n    Point,\n    Arc,\n    Full,\n};\n\nstruct AngularCoverage {\n  \
    \  AngularCoverageKind kind = AngularCoverageKind::Empty;\n    long double begin\
    \ = 0.0L;\n    long double end = 0.0L;\n};\n\nstruct CircleContact {\n    Point<long\
    \ double> point;\n    long double first_argument = 0.0L;\n    long double second_argument\
    \ = 0.0L;\n};\n\nenum class CircleContactKind {\n    Empty,\n    Point,\n    TwoPoints,\n\
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
    \ geometry\n}  // namespace m1une\n\n\n#line 15 \"geometry/polygon.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\nenum class PointInPolygon {\n    Outside =\
    \ 0,\n    Boundary = 1,\n    Inside = 2,\n};\n\ntemplate <Coordinate T>\nstruct\
    \ Polygon {\n    std::vector<Point<T>> vertices;\n    bool filled = true;\n};\n\
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
    \        : relation == PointInPolygon::Boundary;\n}\n\ntemplate <Coordinate T>\n\
    std::vector<Point<long double>> ray_polygon_intersections(\n    const Ray<T>&\
    \ ray,\n    const std::vector<Point<T>>& polygon,\n    long double eps = 1e-12L\n\
    ) {\n    assert(ray.origin != ray.through);\n    assert(polygon.size() >= 3);\n\
    \    std::vector<Point<long double>> result;\n    std::size_t size = polygon.size();\n\
    \    for (std::size_t index = 0; index < size; ++index) {\n        Segment<T>\
    \ edge{\n            polygon[index],\n            polygon[(index + 1) % size]\n\
    \        };\n        const LinearIntersection intersection =\n            linear_intersection(ray,\
    \ edge, eps);\n        if (intersection.kind == LinearIntersectionKind::Point)\
    \ {\n            polygon_detail::push_unique(result, intersection.first, eps);\n\
    \        } else if (intersection.kind == LinearIntersectionKind::Segment) {\n\
    \            polygon_detail::push_unique(result, intersection.first, eps);\n \
    \           polygon_detail::push_unique(result, intersection.second, eps);\n \
    \       } else {\n            assert(intersection.kind == LinearIntersectionKind::Empty);\n\
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
    \ ray);\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 16 \"\
    geometry/steiner_convex_decomposition.hpp\"\n\nnamespace m1une {\nnamespace geometry\
    \ {\n\nnamespace steiner_convex_decomposition_detail {\n\nusing PointType = Point<long\
    \ double>;\n\ninline int scalar_sign(long double value, long double eps) {\n \
    \   return (value > eps) - (value < -eps);\n}\n\ninline bool close(\n    const\
    \ PointType& first,\n    const PointType& second,\n    long double eps\n) {\n\
    \    return distance2(first, second) <= eps * eps;\n}\n\ntemplate <std::floating_point\
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
  - geometry/circle.hpp
  - geometry/linear.hpp
  - geometry/point.hpp
  - geometry/detail/floating_predicate.hpp
  isVerificationFile: false
  path: geometry/steiner_convex_decomposition.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-08-21 00:43:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/centroid.test.cpp
  - verify/geometry/steiner_convex_decomposition.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
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
