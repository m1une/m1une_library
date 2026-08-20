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
    path: verify/geometry/minimum_enclosing_circle.test.cpp
    title: verify/geometry/minimum_enclosing_circle.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/minimum_enclosing_circle.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n#include\
    \ <cstdint>\n#include <numeric>\n#include <optional>\n#include <type_traits>\n\
    #include <vector>\n\n#line 1 \"geometry/circle.hpp\"\n\n\n\n#line 7 \"geometry/circle.hpp\"\
    \n#include <cstddef>\n#include <numbers>\n#line 12 \"geometry/circle.hpp\"\n\n\
    #line 1 \"geometry/linear.hpp\"\n\n\n\n#line 7 \"geometry/linear.hpp\"\n\n#line\
    \ 1 \"geometry/point.hpp\"\n\n\n\n#line 5 \"geometry/point.hpp\"\n#include <concepts>\n\
    #line 8 \"geometry/point.hpp\"\n\n#line 1 \"geometry/detail/floating_predicate.hpp\"\
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
    }  // namespace m1une\n\n\n#line 14 \"geometry/circle.hpp\"\n\nnamespace m1une\
    \ {\nnamespace geometry {\n\ntemplate <Coordinate T>\nstruct Circle {\n    Point<T>\
    \ center;\n    T radius;\n    bool filled = true;\n};\n\nenum class PointInCircle\
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
    \    return std::numbers::pi_v<long double> * radius * radius;\n}\n\ntemplate\
    \ <Coordinate C, Coordinate P>\nPointInCircle point_in_circle(\n    const Circle<C>&\
    \ circle,\n    const Point<P>& point,\n    long double eps = 1e-12L\n) {\n   \
    \ assert(circle.radius >= 0);\n    assert(eps >= 0.0L);\n    if constexpr (std::integral<C>\
    \ && std::integral<P>) {\n        using W = __int128_t;\n        const W dx =\
    \ W(point.x) - W(circle.center.x);\n        const W dy = W(point.y) - W(circle.center.y);\n\
    \        const W radius = W(circle.radius);\n        const W squared_distance\
    \ = dx * dx + dy * dy;\n        const W squared_radius = radius * radius;\n  \
    \      if (squared_distance < squared_radius) return PointInCircle::Inside;\n\
    \        if (squared_distance > squared_radius) return PointInCircle::Outside;\n\
    \        return PointInCircle::Boundary;\n    } else {\n        const int relation\
    \ = circle_detail::compare(\n            geometry::distance(\n               \
    \ Point<long double>(circle.center),\n                Point<long double>(point)\n\
    \            ),\n            static_cast<long double>(circle.radius),\n      \
    \      eps\n        );\n        if (relation < 0) return PointInCircle::Inside;\n\
    \        if (relation > 0) return PointInCircle::Outside;\n        return PointInCircle::Boundary;\n\
    \    }\n}\n\ntemplate <Coordinate C, Coordinate P>\nbool contains(\n    const\
    \ Circle<C>& circle,\n    const Point<P>& point,\n    long double eps = 1e-12L\n\
    ) {\n    const PointInCircle relation = point_in_circle(circle, point, eps);\n\
    \    return circle.filled\n        ? relation != PointInCircle::Outside\n    \
    \    : relation == PointInCircle::Boundary;\n}\n\ntemplate <Coordinate C, Coordinate\
    \ P>\nbool on_circle(\n    const Circle<C>& circle,\n    const Point<P>& point,\n\
    \    long double eps = 1e-12L\n) {\n    assert(circle.radius >= 0);\n    assert(eps\
    \ >= 0.0L);\n    if constexpr (std::integral<C> && std::integral<P>) {\n     \
    \   using W = __int128_t;\n        const W dx = W(point.x) - W(circle.center.x);\n\
    \        const W dy = W(point.y) - W(circle.center.y);\n        const W radius\
    \ = W(circle.radius);\n        return dx * dx + dy * dy == radius * radius;\n\
    \    } else {\n        return circle_detail::compare(\n            geometry::distance(\n\
    \                Point<long double>(circle.center),\n                Point<long\
    \ double>(point)\n            ),\n            static_cast<long double>(circle.radius),\n\
    \            eps\n        ) == 0;\n    }\n}\n\ntemplate <Coordinate C, Coordinate\
    \ P>\nbool intersects(\n    const Circle<C>& circle,\n    const Point<P>& point,\n\
    \    long double eps = 1e-12L\n) {\n    return contains(circle, point, eps);\n\
    }\n\ntemplate <Coordinate P, Coordinate C>\nbool intersects(\n    const Point<P>&\
    \ point,\n    const Circle<C>& circle,\n    long double eps = 1e-12L\n) {\n  \
    \  return intersects(circle, point, eps);\n}\n\ntemplate <Coordinate A, Coordinate\
    \ B>\nCircle<long double> circle_from_diameter(\n    const Point<A>& first,\n\
    \    const Point<B>& second\n) {\n    Point<long double> a(first);\n    Point<long\
    \ double> b(second);\n    Point<long double> center = (a + b) / 2.0L;\n    return\
    \ Circle<long double>{center, geometry::distance(a, b) / 2.0L};\n}\n\ntemplate\
    \ <Coordinate T>\nstd::optional<Circle<long double>> incircle(\n    const Point<T>&\
    \ first,\n    const Point<T>& second,\n    const Point<T>& third,\n    long double\
    \ eps = 1e-12L\n) {\n    assert(eps >= 0.0L);\n    if (orientation(first, second,\
    \ third, eps) == 0) return std::nullopt;\n\n    long double opposite_first = geometry::distance(second,\
    \ third);\n    long double opposite_second = geometry::distance(third, first);\n\
    \    long double opposite_third = geometry::distance(first, second);\n    long\
    \ double perimeter =\n        opposite_first + opposite_second + opposite_third;\n\
    \    Point<long double> center =\n        (Point<long double>(first) * opposite_first\
    \ +\n         Point<long double>(second) * opposite_second +\n         Point<long\
    \ double>(third) * opposite_third) /\n        perimeter;\n    long double doubled_area\
    \ = std::fabs(\n        static_cast<long double>(cross(first, second, third))\n\
    \    );\n    return Circle<long double>{center, doubled_area / perimeter};\n}\n\
    \ntemplate <Coordinate T>\nstd::optional<Circle<long double>> circumcircle(\n\
    \    const Point<T>& first,\n    const Point<T>& second,\n    const Point<T>&\
    \ third,\n    long double eps = 1e-12L\n) {\n    assert(eps >= 0.0L);\n    if\
    \ (orientation(first, second, third, eps) == 0) return std::nullopt;\n\n    Point<long\
    \ double> origin(first);\n    Point<long double> u = Point<long double>(second)\
    \ - origin;\n    Point<long double> v = Point<long double>(third) - origin;\n\
    \    long double denominator = 2.0L * cross(u, v);\n    long double u_norm = norm2(u);\n\
    \    long double v_norm = norm2(v);\n    Point<long double> offset(\n        (u_norm\
    \ * v.y - v_norm * u.y) / denominator,\n        (u.x * v_norm - v.x * u_norm)\
    \ / denominator\n    );\n    Point<long double> center = origin + offset;\n  \
    \  return Circle<long double>{center, norm(offset)};\n}\n\ntemplate <Coordinate\
    \ A, Coordinate B>\nCircleRelation circle_relation(\n    const Circle<A>& first,\n\
    \    const Circle<B>& second,\n    long double eps = 1e-12L\n) {\n    assert(first.radius\
    \ >= 0);\n    assert(second.radius >= 0);\n    assert(eps >= 0.0L);\n    if constexpr\
    \ (std::integral<A> && std::integral<B>) {\n        using W = __int128_t;\n  \
    \      W dx = W(second.center.x) - W(first.center.x);\n        W dy = W(second.center.y)\
    \ - W(first.center.y);\n        W squared_distance = dx * dx + dy * dy;\n    \
    \    W first_radius = W(first.radius);\n        W second_radius = W(second.radius);\n\
    \        W sum = first_radius + second_radius;\n        W difference = first_radius\
    \ - second_radius;\n        if (difference < 0) difference = -difference;\n  \
    \      if (squared_distance == 0 && difference == 0) {\n            return CircleRelation::Coincident;\n\
    \        }\n        if (squared_distance > sum * sum) return CircleRelation::Separate;\n\
    \        if (squared_distance == sum * sum) {\n            return CircleRelation::ExternallyTangent;\n\
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
    \ circle,\n    const Line<L>& line,\n    long double eps = 1e-12L\n) {\n    if\
    \ (circle.filled) {\n        const Line<long double> converted{\n            Point<long\
    \ double>(line.a),\n            Point<long double>(line.b)\n        };\n     \
    \   return contains(\n            circle,\n            projection(converted, Point<long\
    \ double>(circle.center)),\n            eps\n        );\n    }\n    return !circle_line_intersections(circle,\
    \ line, eps).empty();\n}\n\ntemplate <Coordinate C, Coordinate L>\nbool intersects(\n\
    \    const Line<L>& line,\n    const Circle<C>& circle,\n    long double eps =\
    \ 1e-12L\n) {\n    return intersects(circle, line, eps);\n}\n\ntemplate <Coordinate\
    \ C, Coordinate R>\nbool intersects(\n    const Circle<C>& circle,\n    const\
    \ Ray<R>& ray,\n    long double eps = 1e-12L\n) {\n    if (circle.filled) {\n\
    \        const Ray<long double> converted{\n            Point<long double>(ray.origin),\n\
    \            Point<long double>(ray.through)\n        };\n        return contains(\n\
    \            circle,\n            projection(converted, Point<long double>(circle.center)),\n\
    \            eps\n        );\n    }\n    return !circle_ray_intersections(circle,\
    \ ray, eps).empty();\n}\n\ntemplate <Coordinate C, Coordinate R>\nbool intersects(\n\
    \    const Ray<R>& ray,\n    const Circle<C>& circle,\n    long double eps = 1e-12L\n\
    ) {\n    return intersects(circle, ray, eps);\n}\n\ntemplate <Coordinate C, Coordinate\
    \ S>\nbool intersects(\n    const Circle<C>& circle,\n    const Segment<S>& segment,\n\
    \    long double eps = 1e-12L\n) {\n    if (circle.filled) {\n        const Segment<long\
    \ double> converted{\n            Point<long double>(segment.a),\n           \
    \ Point<long double>(segment.b)\n        };\n        return contains(\n      \
    \      circle,\n            projection(converted, Point<long double>(circle.center)),\n\
    \            eps\n        );\n    }\n    return !circle_segment_intersections(circle,\
    \ segment, eps).empty();\n}\n\ntemplate <Coordinate C, Coordinate S>\nbool intersects(\n\
    \    const Segment<S>& segment,\n    const Circle<C>& circle,\n    long double\
    \ eps = 1e-12L\n) {\n    return intersects(circle, segment, eps);\n}\n\ntemplate\
    \ <Coordinate A, Coordinate B>\nbool intersects(\n    const Circle<A>& first,\n\
    \    const Circle<B>& second,\n    long double eps = 1e-12L\n) {\n    assert(first.radius\
    \ >= 0);\n    assert(second.radius >= 0);\n    assert(eps >= 0.0L);\n    if (first.filled\
    \ && second.filled) {\n        if constexpr (std::integral<A> && std::integral<B>)\
    \ {\n            using W = __int128_t;\n            const W dx = W(second.center.x)\
    \ - W(first.center.x);\n            const W dy = W(second.center.y) - W(first.center.y);\n\
    \            const W radius = W(first.radius) + W(second.radius);\n          \
    \  return dx * dx + dy * dy <= radius * radius;\n        } else {\n          \
    \  const long double center_distance = geometry::distance(\n                Point<long\
    \ double>(first.center),\n                Point<long double>(second.center)\n\
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
    \ point, eps);\n\n    const std::vector<Point<long double>> common =\n       \
    \ circle_line_intersections(circle, line, eps);\n    if (!common.empty()) return\
    \ ClosestPoints{common.front(), common.front()};\n    return ClosestPoints{\n\
    \        circle_detail::point_toward(circle, point),\n        point\n    };\n\
    }\n\ntemplate <Coordinate L, Coordinate C>\nClosestPoints closest_points(\n  \
    \  const Line<L>& line,\n    const Circle<C>& circle,\n    long double eps = 1e-12L\n\
    ) {\n    return closest_points_detail::reversed(closest_points(circle, line, eps));\n\
    }\n\ntemplate <Coordinate C, Coordinate R>\nClosestPoints closest_points(\n  \
    \  const Circle<C>& circle,\n    const Ray<R>& ray,\n    long double eps = 1e-12L\n\
    ) {\n    const Ray<long double> converted{\n        Point<long double>(ray.origin),\n\
    \        Point<long double>(ray.through)\n    };\n    const Point<long double>\
    \ point = projection(\n        converted,\n        Point<long double>(circle.center)\n\
    \    );\n    if (circle.filled) return closest_points(circle, point, eps);\n\n\
    \    const std::vector<Point<long double>> common =\n        circle_ray_intersections(circle,\
    \ ray, eps);\n    if (!common.empty()) return ClosestPoints{common.front(), common.front()};\n\
    \    return ClosestPoints{\n        circle_detail::point_toward(circle, point),\n\
    \        point\n    };\n}\n\ntemplate <Coordinate R, Coordinate C>\nClosestPoints\
    \ closest_points(\n    const Ray<R>& ray,\n    const Circle<C>& circle,\n    long\
    \ double eps = 1e-12L\n) {\n    return closest_points_detail::reversed(closest_points(circle,\
    \ ray, eps));\n}\n\ntemplate <Coordinate C, Coordinate S>\nClosestPoints closest_points(\n\
    \    const Circle<C>& circle,\n    const Segment<S>& segment,\n    long double\
    \ eps = 1e-12L\n) {\n    const Segment<long double> converted{\n        Point<long\
    \ double>(segment.a),\n        Point<long double>(segment.b)\n    };\n    const\
    \ Point<long double> center(circle.center);\n    const Point<long double> projected\
    \ = projection(converted, center);\n    if (circle.filled) return closest_points(circle,\
    \ projected, eps);\n\n    const std::vector<Point<long double>> common =\n   \
    \     circle_segment_intersections(circle, segment, eps);\n    if (!common.empty())\
    \ return ClosestPoints{common.front(), common.front()};\n    ClosestPoints result{\n\
    \        circle_detail::point_toward(circle, projected),\n        projected\n\
    \    };\n    for (const Point<long double>& point : {converted.a, converted.b})\
    \ {\n        circle_detail::consider(\n            result,\n            ClosestPoints{circle_detail::point_toward(circle,\
    \ point), point}\n        );\n    }\n    return result;\n}\n\ntemplate <Coordinate\
    \ S, Coordinate C>\nClosestPoints closest_points(\n    const Segment<S>& segment,\n\
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
    \    const std::vector<Point<long double>> common =\n        circle_intersections(first,\
    \ second, eps);\n    if (!common.empty()) return ClosestPoints{common.front(),\
    \ common.front()};\n\n    const Point<long double> first_center(first.center);\n\
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
    \ geometry\n}  // namespace m1une\n\n\n#line 15 \"geometry/minimum_enclosing_circle.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\nstruct MinimumEnclosingCircle {\n\
    \    Circle<long double> circle;\n    std::vector<int> support;\n};\n\nnamespace\
    \ internal {\n\nstruct MinimumEnclosingCircleSupport {\n    int size = 0;\n  \
    \  std::array<int, 3> index = {-1, -1, -1};\n};\n\ntemplate <Coordinate T>\nCircle<long\
    \ double> circle_from_support(\n    const std::vector<Point<T>>& points,\n   \
    \ const MinimumEnclosingCircleSupport& support\n) {\n    assert(1 <= support.size\
    \ && support.size <= 3);\n    Point<long double> first(points[support.index[0]]);\n\
    \    if (support.size == 1) return Circle<long double>{first, 0.0L};\n\n    Point<long\
    \ double> second(points[support.index[1]]);\n    if (support.size == 2) {\n  \
    \      Point<long double> center = (first + second) / 2.0L;\n        return Circle<long\
    \ double>{center, distance(first, second) / 2.0L};\n    }\n\n    Point<long double>\
    \ third(points[support.index[2]]);\n    long double denominator = 2.0L * cross(first,\
    \ second, third);\n    assert(denominator != 0.0L);\n    long double first_norm\
    \ = norm2(first);\n    long double second_norm = norm2(second);\n    long double\
    \ third_norm = norm2(third);\n    Point<long double> center(\n        (\n    \
    \        first_norm * (second.y - third.y) +\n            second_norm * (third.y\
    \ - first.y) +\n            third_norm * (first.y - second.y)\n        ) / denominator,\n\
    \        (\n            first_norm * (third.x - second.x) +\n            second_norm\
    \ * (first.x - third.x) +\n            third_norm * (second.x - first.x)\n   \
    \     ) / denominator\n    );\n    return Circle<long double>{center, distance(center,\
    \ first)};\n}\n\ntemplate <Coordinate T>\nvoid reduce_collinear_support(\n   \
    \ const std::vector<Point<T>>& points,\n    MinimumEnclosingCircleSupport& support\n\
    ) {\n    if (support.size != 3) return;\n    const Point<T>& first = points[support.index[0]];\n\
    \    const Point<T>& second = points[support.index[1]];\n    const Point<T>& third\
    \ = points[support.index[2]];\n    if (cross(first, second, third) != 0) return;\n\
    \n    wide_type<T> first_second = distance2(first, second);\n    wide_type<T>\
    \ second_third = distance2(second, third);\n    wide_type<T> first_third = distance2(first,\
    \ third);\n    if (first_second >= second_third && first_second >= first_third)\
    \ {\n        support.size = 2;\n    } else if (second_third >= first_second &&\
    \ second_third >= first_third) {\n        support.size = 2;\n        support.index[0]\
    \ = support.index[1];\n        support.index[1] = support.index[2];\n    } else\
    \ {\n        support.size = 2;\n        support.index[1] = support.index[2];\n\
    \    }\n}\n\ntemplate <Coordinate T>\nbool support_contains(\n    const std::vector<Point<T>>&\
    \ points,\n    const MinimumEnclosingCircleSupport& support,\n    int point_index,\n\
    \    long double eps\n) {\n    if (support.size == 0) return false;\n    const\
    \ Point<T>& point = points[point_index];\n    const Point<T>& first = points[support.index[0]];\n\
    \    if (support.size == 1) return point == first;\n\n    if constexpr (std::integral<T>)\
    \ {\n        using W = wide_type<T>;\n        const Point<T>& second = points[support.index[1]];\n\
    \        if (support.size == 2) {\n            W ux = W(2) * W(point.x) - W(first.x)\
    \ - W(second.x);\n            W uy = W(2) * W(point.y) - W(first.y) - W(second.y);\n\
    \            W dx = W(first.x) - W(second.x);\n            W dy = W(first.y) -\
    \ W(second.y);\n            return ux * ux + uy * uy <= dx * dx + dy * dy;\n \
    \       }\n\n        const Point<T>& third = points[support.index[2]];\n     \
    \   W ax = W(first.x) - W(point.x);\n        W ay = W(first.y) - W(point.y);\n\
    \        W bx = W(second.x) - W(point.x);\n        W by = W(second.y) - W(point.y);\n\
    \        W cx = W(third.x) - W(point.x);\n        W cy = W(third.y) - W(point.y);\n\
    \        W a_norm = ax * ax + ay * ay;\n        W b_norm = bx * bx + by * by;\n\
    \        W c_norm = cx * cx + cy * cy;\n        W determinant =\n            ax\
    \ * (by * c_norm - cy * b_norm) -\n            ay * (bx * c_norm - cx * b_norm)\
    \ +\n            a_norm * (bx * cy - by * cx);\n        W direction = cross(first,\
    \ second, third);\n        return direction > 0 ? determinant >= 0 : determinant\
    \ <= 0;\n    } else {\n        Circle<long double> circle = circle_from_support(points,\
    \ support);\n        long double squared = distance2(Point<long double>(point),\
    \ circle.center);\n        long double radius_squared = circle.radius * circle.radius;\n\
    \        long double tolerance = eps * std::max(1.0L, radius_squared);\n     \
    \   return squared <= radius_squared + tolerance;\n    }\n}\n\ninline std::uint64_t\
    \ minimum_enclosing_circle_random(std::uint64_t& state) {\n    state ^= state\
    \ << 7;\n    state ^= state >> 9;\n    return state;\n}\n\n}  // namespace internal\n\
    \n// Returns the unique minimum circle containing every input point.\ntemplate\
    \ <Coordinate T>\nstd::optional<MinimumEnclosingCircle> minimum_enclosing_circle(\n\
    \    const std::vector<Point<T>>& points,\n    long double eps = 1e-12L\n) {\n\
    \    if (points.empty()) return std::nullopt;\n    assert(eps >= 0.0L);\n\n  \
    \  const int n = int(points.size());\n    std::vector<int> order(n);\n    std::iota(order.begin(),\
    \ order.end(), 0);\n    std::uint64_t state = 0x9e3779b97f4a7c15ULL;\n    for\
    \ (int index = n - 1; index >= 1; index--) {\n        int other = int(\n     \
    \       internal::minimum_enclosing_circle_random(state) %\n            std::uint64_t(index\
    \ + 1)\n        );\n        std::swap(order[index], order[other]);\n    }\n\n\
    \    internal::MinimumEnclosingCircleSupport support;\n    for (int first = 0;\
    \ first < n; first++) {\n        if (internal::support_contains(points, support,\
    \ order[first], eps)) {\n            continue;\n        }\n        support.size\
    \ = 1;\n        support.index[0] = order[first];\n        for (int second = 0;\
    \ second < first; second++) {\n            if (internal::support_contains(points,\
    \ support, order[second], eps)) {\n                continue;\n            }\n\
    \            support.size = 2;\n            support.index[0] = order[first];\n\
    \            support.index[1] = order[second];\n            for (int third = 0;\
    \ third < second; third++) {\n                if (internal::support_contains(\n\
    \                        points,\n                        support,\n         \
    \               order[third],\n                        eps\n                 \
    \   )) {\n                    continue;\n                }\n                support.size\
    \ = 3;\n                support.index[0] = order[first];\n                support.index[1]\
    \ = order[second];\n                support.index[2] = order[third];\n       \
    \         internal::reduce_collinear_support(points, support);\n            }\n\
    \        }\n    }\n\n    MinimumEnclosingCircle result;\n    result.circle = internal::circle_from_support(points,\
    \ support);\n    result.support.assign(\n        support.index.begin(),\n    \
    \    support.index.begin() + support.size\n    );\n    std::sort(result.support.begin(),\
    \ result.support.end());\n    return result;\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_MINIMUM_ENCLOSING_CIRCLE_HPP\n#define M1UNE_GEOMETRY_MINIMUM_ENCLOSING_CIRCLE_HPP\
    \ 1\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <cstdint>\n#include <numeric>\n#include <optional>\n#include <type_traits>\n\
    #include <vector>\n\n#include \"circle.hpp\"\n\nnamespace m1une {\nnamespace geometry\
    \ {\n\nstruct MinimumEnclosingCircle {\n    Circle<long double> circle;\n    std::vector<int>\
    \ support;\n};\n\nnamespace internal {\n\nstruct MinimumEnclosingCircleSupport\
    \ {\n    int size = 0;\n    std::array<int, 3> index = {-1, -1, -1};\n};\n\ntemplate\
    \ <Coordinate T>\nCircle<long double> circle_from_support(\n    const std::vector<Point<T>>&\
    \ points,\n    const MinimumEnclosingCircleSupport& support\n) {\n    assert(1\
    \ <= support.size && support.size <= 3);\n    Point<long double> first(points[support.index[0]]);\n\
    \    if (support.size == 1) return Circle<long double>{first, 0.0L};\n\n    Point<long\
    \ double> second(points[support.index[1]]);\n    if (support.size == 2) {\n  \
    \      Point<long double> center = (first + second) / 2.0L;\n        return Circle<long\
    \ double>{center, distance(first, second) / 2.0L};\n    }\n\n    Point<long double>\
    \ third(points[support.index[2]]);\n    long double denominator = 2.0L * cross(first,\
    \ second, third);\n    assert(denominator != 0.0L);\n    long double first_norm\
    \ = norm2(first);\n    long double second_norm = norm2(second);\n    long double\
    \ third_norm = norm2(third);\n    Point<long double> center(\n        (\n    \
    \        first_norm * (second.y - third.y) +\n            second_norm * (third.y\
    \ - first.y) +\n            third_norm * (first.y - second.y)\n        ) / denominator,\n\
    \        (\n            first_norm * (third.x - second.x) +\n            second_norm\
    \ * (first.x - third.x) +\n            third_norm * (second.x - first.x)\n   \
    \     ) / denominator\n    );\n    return Circle<long double>{center, distance(center,\
    \ first)};\n}\n\ntemplate <Coordinate T>\nvoid reduce_collinear_support(\n   \
    \ const std::vector<Point<T>>& points,\n    MinimumEnclosingCircleSupport& support\n\
    ) {\n    if (support.size != 3) return;\n    const Point<T>& first = points[support.index[0]];\n\
    \    const Point<T>& second = points[support.index[1]];\n    const Point<T>& third\
    \ = points[support.index[2]];\n    if (cross(first, second, third) != 0) return;\n\
    \n    wide_type<T> first_second = distance2(first, second);\n    wide_type<T>\
    \ second_third = distance2(second, third);\n    wide_type<T> first_third = distance2(first,\
    \ third);\n    if (first_second >= second_third && first_second >= first_third)\
    \ {\n        support.size = 2;\n    } else if (second_third >= first_second &&\
    \ second_third >= first_third) {\n        support.size = 2;\n        support.index[0]\
    \ = support.index[1];\n        support.index[1] = support.index[2];\n    } else\
    \ {\n        support.size = 2;\n        support.index[1] = support.index[2];\n\
    \    }\n}\n\ntemplate <Coordinate T>\nbool support_contains(\n    const std::vector<Point<T>>&\
    \ points,\n    const MinimumEnclosingCircleSupport& support,\n    int point_index,\n\
    \    long double eps\n) {\n    if (support.size == 0) return false;\n    const\
    \ Point<T>& point = points[point_index];\n    const Point<T>& first = points[support.index[0]];\n\
    \    if (support.size == 1) return point == first;\n\n    if constexpr (std::integral<T>)\
    \ {\n        using W = wide_type<T>;\n        const Point<T>& second = points[support.index[1]];\n\
    \        if (support.size == 2) {\n            W ux = W(2) * W(point.x) - W(first.x)\
    \ - W(second.x);\n            W uy = W(2) * W(point.y) - W(first.y) - W(second.y);\n\
    \            W dx = W(first.x) - W(second.x);\n            W dy = W(first.y) -\
    \ W(second.y);\n            return ux * ux + uy * uy <= dx * dx + dy * dy;\n \
    \       }\n\n        const Point<T>& third = points[support.index[2]];\n     \
    \   W ax = W(first.x) - W(point.x);\n        W ay = W(first.y) - W(point.y);\n\
    \        W bx = W(second.x) - W(point.x);\n        W by = W(second.y) - W(point.y);\n\
    \        W cx = W(third.x) - W(point.x);\n        W cy = W(third.y) - W(point.y);\n\
    \        W a_norm = ax * ax + ay * ay;\n        W b_norm = bx * bx + by * by;\n\
    \        W c_norm = cx * cx + cy * cy;\n        W determinant =\n            ax\
    \ * (by * c_norm - cy * b_norm) -\n            ay * (bx * c_norm - cx * b_norm)\
    \ +\n            a_norm * (bx * cy - by * cx);\n        W direction = cross(first,\
    \ second, third);\n        return direction > 0 ? determinant >= 0 : determinant\
    \ <= 0;\n    } else {\n        Circle<long double> circle = circle_from_support(points,\
    \ support);\n        long double squared = distance2(Point<long double>(point),\
    \ circle.center);\n        long double radius_squared = circle.radius * circle.radius;\n\
    \        long double tolerance = eps * std::max(1.0L, radius_squared);\n     \
    \   return squared <= radius_squared + tolerance;\n    }\n}\n\ninline std::uint64_t\
    \ minimum_enclosing_circle_random(std::uint64_t& state) {\n    state ^= state\
    \ << 7;\n    state ^= state >> 9;\n    return state;\n}\n\n}  // namespace internal\n\
    \n// Returns the unique minimum circle containing every input point.\ntemplate\
    \ <Coordinate T>\nstd::optional<MinimumEnclosingCircle> minimum_enclosing_circle(\n\
    \    const std::vector<Point<T>>& points,\n    long double eps = 1e-12L\n) {\n\
    \    if (points.empty()) return std::nullopt;\n    assert(eps >= 0.0L);\n\n  \
    \  const int n = int(points.size());\n    std::vector<int> order(n);\n    std::iota(order.begin(),\
    \ order.end(), 0);\n    std::uint64_t state = 0x9e3779b97f4a7c15ULL;\n    for\
    \ (int index = n - 1; index >= 1; index--) {\n        int other = int(\n     \
    \       internal::minimum_enclosing_circle_random(state) %\n            std::uint64_t(index\
    \ + 1)\n        );\n        std::swap(order[index], order[other]);\n    }\n\n\
    \    internal::MinimumEnclosingCircleSupport support;\n    for (int first = 0;\
    \ first < n; first++) {\n        if (internal::support_contains(points, support,\
    \ order[first], eps)) {\n            continue;\n        }\n        support.size\
    \ = 1;\n        support.index[0] = order[first];\n        for (int second = 0;\
    \ second < first; second++) {\n            if (internal::support_contains(points,\
    \ support, order[second], eps)) {\n                continue;\n            }\n\
    \            support.size = 2;\n            support.index[0] = order[first];\n\
    \            support.index[1] = order[second];\n            for (int third = 0;\
    \ third < second; third++) {\n                if (internal::support_contains(\n\
    \                        points,\n                        support,\n         \
    \               order[third],\n                        eps\n                 \
    \   )) {\n                    continue;\n                }\n                support.size\
    \ = 3;\n                support.index[0] = order[first];\n                support.index[1]\
    \ = order[second];\n                support.index[2] = order[third];\n       \
    \         internal::reduce_collinear_support(points, support);\n            }\n\
    \        }\n    }\n\n    MinimumEnclosingCircle result;\n    result.circle = internal::circle_from_support(points,\
    \ support);\n    result.support.assign(\n        support.index.begin(),\n    \
    \    support.index.begin() + support.size\n    );\n    std::sort(result.support.begin(),\
    \ result.support.end());\n    return result;\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_MINIMUM_ENCLOSING_CIRCLE_HPP\n"
  dependsOn:
  - geometry/circle.hpp
  - geometry/linear.hpp
  - geometry/point.hpp
  - geometry/detail/floating_predicate.hpp
  isVerificationFile: false
  path: geometry/minimum_enclosing_circle.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-08-21 00:19:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/centroid.test.cpp
  - verify/geometry/minimum_enclosing_circle.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
documentation_of: geometry/minimum_enclosing_circle.hpp
layout: document
title: Minimum Enclosing Circle
---

## Overview

`minimum_enclosing_circle(points)` finds the unique smallest circle containing
every input point. It uses the randomized incremental algorithm and returns the
circle together with one support set of at most three original points that
defines it.

Duplicate and collinear points are supported.

## Interface

```cpp
struct MinimumEnclosingCircle {
    Circle<long double> circle;
    std::vector<int> support;
};

template <Coordinate T>
std::optional<MinimumEnclosingCircle> minimum_enclosing_circle(
    const std::vector<Point<T>>& points,
    long double eps = 1e-12L
);
```

## Result

| Member | Description |
| --- | --- |
| `circle` | The minimum enclosing `Circle<long double>`. |
| `support` | One to three sorted original indices whose points define the circle. |

The function returns `std::nullopt` for an empty input. For one or more points,
`support` is nonempty. It may omit other input points that also lie on the
boundary. The returned circle has `filled == true`.

For integral coordinates, containment decisions use signed 128-bit arithmetic;
all predicate intermediates must fit in that type. The returned center and
radius are still `long double`. For floating-point coordinates, `eps` controls
containment comparisons relative to the squared radius.

The shuffle is deterministic, so repeated calls on the same input produce the
same support set.

## Operations

| Function | Description | Complexity |
| --- | --- | --- |
| `minimum_enclosing_circle(points, eps)` | Returns the smallest circle containing all points without modifying the input. | Expected $O(N)$ time and $O(N)$ memory |

## Example

```cpp
#include "geometry/minimum_enclosing_circle.hpp"

#include <cassert>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(4, 0);
    points.emplace_back(2, 1);

    auto answer = m1une::geometry::minimum_enclosing_circle(points);
    assert(answer.has_value());
    assert(answer->circle.center.x == 2.0L);
    assert(answer->circle.center.y == 0.0L);
    assert(answer->circle.radius == 2.0L);
}
```
