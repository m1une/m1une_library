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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/geometry/centroid.test.cpp
    title: verify/geometry/centroid.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/perpendicular_bisector.test.cpp
    title: verify/geometry/perpendicular_bisector.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/perpendicular_bisector.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <limits>\n#include <numeric>\n\
    \n#line 1 \"geometry/linear.hpp\"\n\n\n\n#line 5 \"geometry/linear.hpp\"\n#include\
    \ <array>\n#line 7 \"geometry/linear.hpp\"\n#include <cmath>\n\n#line 1 \"geometry/point.hpp\"\
    \n\n\n\n#line 7 \"geometry/point.hpp\"\n#include <type_traits>\n\n#line 1 \"geometry/detail/floating_predicate.hpp\"\
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
    }  // namespace m1une\n\n\n#line 11 \"geometry/perpendicular_bisector.hpp\"\n\n\
    namespace m1une {\nnamespace geometry {\n\nnamespace perpendicular_bisector_detail\
    \ {\n\ntemplate <class Integer>\nconstexpr Integer absolute(Integer value) {\n\
    \    return value < 0 ? -value : value;\n}\n\ntemplate <class Integer>\nconstexpr\
    \ Integer gcd(Integer first, Integer second) {\n    first = absolute(first);\n\
    \    second = absolute(second);\n    while (second != 0) {\n        Integer remainder\
    \ = first % second;\n        first = second;\n        second = remainder;\n  \
    \  }\n    return first;\n}\n\ntemplate <class Integer>\nconstexpr Integer floor_div(Integer\
    \ numerator, Integer denominator) {\n    assert(denominator > 0);\n    Integer\
    \ quotient = numerator / denominator;\n    if (numerator % denominator < 0) --quotient;\n\
    \    return quotient;\n}\n\ntemplate <class Integer>\nconstexpr Integer ceil_div(Integer\
    \ numerator, Integer denominator) {\n    assert(denominator > 0);\n    Integer\
    \ quotient = numerator / denominator;\n    if (numerator % denominator > 0) ++quotient;\n\
    \    return quotient;\n}\n\ntemplate <class Integer>\nstruct ParameterBounds {\n\
    \    Integer lower;\n    Integer upper;\n};\n\ntemplate <class Integer>\nconstexpr\
    \ ParameterBounds<Integer> parameter_bounds(\n    Integer value,\n    Integer\
    \ step,\n    Integer minimum,\n    Integer maximum\n) {\n    assert(step != 0);\n\
    \    Integer valid_minimum = std::max(minimum, minimum - step);\n    Integer valid_maximum\
    \ = std::min(maximum, maximum - step);\n    if (step > 0) {\n        return ParameterBounds<Integer>{\n\
    \            ceil_div(valid_minimum - value, step),\n            floor_div(valid_maximum\
    \ - value, step)\n        };\n    }\n    Integer positive_step = -step;\n    return\
    \ ParameterBounds<Integer>{\n        ceil_div(value - valid_maximum, positive_step),\n\
    \        floor_div(value - valid_minimum, positive_step)\n    };\n}\n\ntemplate\
    \ <Coordinate T>\nrequires std::integral<T>\nconstexpr Line<T> integral_perpendicular_bisector(\n\
    \    const Point<T>& first,\n    const Point<T>& second\n) {\n    using W = wide_type<T>;\n\
    \    W first_x = W(first.x);\n    W first_y = W(first.y);\n    W second_x = W(second.x);\n\
    \    W second_y = W(second.y);\n    W difference_x = second_x - first_x;\n   \
    \ W difference_y = second_y - first_y;\n    W divisor = gcd(difference_x, difference_y);\n\
    \    assert(divisor != 0);\n\n    W primitive_x = difference_x / divisor;\n  \
    \  W primitive_y = difference_y / divisor;\n    W sum_x = first_x + second_x;\n\
    \    W sum_y = first_y + second_y;\n\n    W base_x;\n    W base_y;\n    if (sum_x\
    \ % 2 == 0 && sum_y % 2 == 0) {\n        base_x = sum_x / 2;\n        base_y =\
    \ sum_y / 2;\n    } else {\n        assert((sum_x + primitive_y) % 2 == 0);\n\
    \        assert((sum_y - primitive_x) % 2 == 0);\n        base_x = (sum_x + primitive_y)\
    \ / 2;\n        base_y = (sum_y - primitive_x) / 2;\n    }\n\n    W step_x = -primitive_y;\n\
    \    W step_y = primitive_x;\n    W minimum = W(std::numeric_limits<T>::lowest());\n\
    \    W maximum = W(std::numeric_limits<T>::max());\n    W lower = std::numeric_limits<W>::lowest();\n\
    \    W upper = std::numeric_limits<W>::max();\n\n    auto restrict_parameter =\
    \ [&](W value, W step) {\n        if (step == 0) {\n            assert(minimum\
    \ <= value && value <= maximum);\n            return;\n        }\n        ParameterBounds<W>\
    \ bounds =\n            parameter_bounds(value, step, minimum, maximum);\n   \
    \     lower = std::max(lower, bounds.lower);\n        upper = std::min(upper,\
    \ bounds.upper);\n    };\n    restrict_parameter(base_x, step_x);\n    restrict_parameter(base_y,\
    \ step_y);\n    assert(lower <= upper);\n\n    W parameter = std::clamp(W(0),\
    \ lower, upper);\n    W result_x = base_x + step_x * parameter;\n    W result_y\
    \ = base_y + step_y * parameter;\n    W next_x = result_x + step_x;\n    W next_y\
    \ = result_y + step_y;\n    assert(minimum <= result_x && result_x <= maximum);\n\
    \    assert(minimum <= result_y && result_y <= maximum);\n    assert(minimum <=\
    \ next_x && next_x <= maximum);\n    assert(minimum <= next_y && next_y <= maximum);\n\
    \n    Line<T> result;\n    result.a = Point<T>(T(result_x), T(result_y));\n  \
    \  result.b = Point<T>(T(next_x), T(next_y));\n    return result;\n}\n\n}  //\
    \ namespace perpendicular_bisector_detail\n\ntemplate <Coordinate T>\nconstexpr\
    \ Line<T> perpendicular_bisector(\n    const Point<T>& first,\n    const Point<T>&\
    \ second\n) {\n    assert(first != second);\n    if constexpr (std::integral<T>)\
    \ {\n        return perpendicular_bisector_detail::integral_perpendicular_bisector(\n\
    \            first,\n            second\n        );\n    } else {\n        Point<T>\
    \ midpoint(\n            std::midpoint(first.x, second.x),\n            std::midpoint(first.y,\
    \ second.y)\n        );\n        Point<T> direction(first.y - second.y, second.x\
    \ - first.x);\n\n        Line<T> result;\n        result.a = midpoint;\n     \
    \   result.b = midpoint + direction;\n        return result;\n    }\n}\n\n}  //\
    \ namespace geometry\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_PERPENDICULAR_BISECTOR_HPP\n#define M1UNE_GEOMETRY_PERPENDICULAR_BISECTOR_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <limits>\n#include <numeric>\n\n#include \"linear.hpp\"\n\nnamespace m1une {\n\
    namespace geometry {\n\nnamespace perpendicular_bisector_detail {\n\ntemplate\
    \ <class Integer>\nconstexpr Integer absolute(Integer value) {\n    return value\
    \ < 0 ? -value : value;\n}\n\ntemplate <class Integer>\nconstexpr Integer gcd(Integer\
    \ first, Integer second) {\n    first = absolute(first);\n    second = absolute(second);\n\
    \    while (second != 0) {\n        Integer remainder = first % second;\n    \
    \    first = second;\n        second = remainder;\n    }\n    return first;\n\
    }\n\ntemplate <class Integer>\nconstexpr Integer floor_div(Integer numerator,\
    \ Integer denominator) {\n    assert(denominator > 0);\n    Integer quotient =\
    \ numerator / denominator;\n    if (numerator % denominator < 0) --quotient;\n\
    \    return quotient;\n}\n\ntemplate <class Integer>\nconstexpr Integer ceil_div(Integer\
    \ numerator, Integer denominator) {\n    assert(denominator > 0);\n    Integer\
    \ quotient = numerator / denominator;\n    if (numerator % denominator > 0) ++quotient;\n\
    \    return quotient;\n}\n\ntemplate <class Integer>\nstruct ParameterBounds {\n\
    \    Integer lower;\n    Integer upper;\n};\n\ntemplate <class Integer>\nconstexpr\
    \ ParameterBounds<Integer> parameter_bounds(\n    Integer value,\n    Integer\
    \ step,\n    Integer minimum,\n    Integer maximum\n) {\n    assert(step != 0);\n\
    \    Integer valid_minimum = std::max(minimum, minimum - step);\n    Integer valid_maximum\
    \ = std::min(maximum, maximum - step);\n    if (step > 0) {\n        return ParameterBounds<Integer>{\n\
    \            ceil_div(valid_minimum - value, step),\n            floor_div(valid_maximum\
    \ - value, step)\n        };\n    }\n    Integer positive_step = -step;\n    return\
    \ ParameterBounds<Integer>{\n        ceil_div(value - valid_maximum, positive_step),\n\
    \        floor_div(value - valid_minimum, positive_step)\n    };\n}\n\ntemplate\
    \ <Coordinate T>\nrequires std::integral<T>\nconstexpr Line<T> integral_perpendicular_bisector(\n\
    \    const Point<T>& first,\n    const Point<T>& second\n) {\n    using W = wide_type<T>;\n\
    \    W first_x = W(first.x);\n    W first_y = W(first.y);\n    W second_x = W(second.x);\n\
    \    W second_y = W(second.y);\n    W difference_x = second_x - first_x;\n   \
    \ W difference_y = second_y - first_y;\n    W divisor = gcd(difference_x, difference_y);\n\
    \    assert(divisor != 0);\n\n    W primitive_x = difference_x / divisor;\n  \
    \  W primitive_y = difference_y / divisor;\n    W sum_x = first_x + second_x;\n\
    \    W sum_y = first_y + second_y;\n\n    W base_x;\n    W base_y;\n    if (sum_x\
    \ % 2 == 0 && sum_y % 2 == 0) {\n        base_x = sum_x / 2;\n        base_y =\
    \ sum_y / 2;\n    } else {\n        assert((sum_x + primitive_y) % 2 == 0);\n\
    \        assert((sum_y - primitive_x) % 2 == 0);\n        base_x = (sum_x + primitive_y)\
    \ / 2;\n        base_y = (sum_y - primitive_x) / 2;\n    }\n\n    W step_x = -primitive_y;\n\
    \    W step_y = primitive_x;\n    W minimum = W(std::numeric_limits<T>::lowest());\n\
    \    W maximum = W(std::numeric_limits<T>::max());\n    W lower = std::numeric_limits<W>::lowest();\n\
    \    W upper = std::numeric_limits<W>::max();\n\n    auto restrict_parameter =\
    \ [&](W value, W step) {\n        if (step == 0) {\n            assert(minimum\
    \ <= value && value <= maximum);\n            return;\n        }\n        ParameterBounds<W>\
    \ bounds =\n            parameter_bounds(value, step, minimum, maximum);\n   \
    \     lower = std::max(lower, bounds.lower);\n        upper = std::min(upper,\
    \ bounds.upper);\n    };\n    restrict_parameter(base_x, step_x);\n    restrict_parameter(base_y,\
    \ step_y);\n    assert(lower <= upper);\n\n    W parameter = std::clamp(W(0),\
    \ lower, upper);\n    W result_x = base_x + step_x * parameter;\n    W result_y\
    \ = base_y + step_y * parameter;\n    W next_x = result_x + step_x;\n    W next_y\
    \ = result_y + step_y;\n    assert(minimum <= result_x && result_x <= maximum);\n\
    \    assert(minimum <= result_y && result_y <= maximum);\n    assert(minimum <=\
    \ next_x && next_x <= maximum);\n    assert(minimum <= next_y && next_y <= maximum);\n\
    \n    Line<T> result;\n    result.a = Point<T>(T(result_x), T(result_y));\n  \
    \  result.b = Point<T>(T(next_x), T(next_y));\n    return result;\n}\n\n}  //\
    \ namespace perpendicular_bisector_detail\n\ntemplate <Coordinate T>\nconstexpr\
    \ Line<T> perpendicular_bisector(\n    const Point<T>& first,\n    const Point<T>&\
    \ second\n) {\n    assert(first != second);\n    if constexpr (std::integral<T>)\
    \ {\n        return perpendicular_bisector_detail::integral_perpendicular_bisector(\n\
    \            first,\n            second\n        );\n    } else {\n        Point<T>\
    \ midpoint(\n            std::midpoint(first.x, second.x),\n            std::midpoint(first.y,\
    \ second.y)\n        );\n        Point<T> direction(first.y - second.y, second.x\
    \ - first.x);\n\n        Line<T> result;\n        result.a = midpoint;\n     \
    \   result.b = midpoint + direction;\n        return result;\n    }\n}\n\n}  //\
    \ namespace geometry\n}  // namespace m1une\n\n#endif  // M1UNE_GEOMETRY_PERPENDICULAR_BISECTOR_HPP\n"
  dependsOn:
  - geometry/linear.hpp
  - geometry/point.hpp
  - geometry/detail/floating_predicate.hpp
  isVerificationFile: false
  path: geometry/perpendicular_bisector.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-08-20 21:54:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/perpendicular_bisector.test.cpp
  - verify/geometry/centroid.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
documentation_of: geometry/perpendicular_bisector.hpp
layout: document
title: Perpendicular Bisector
---

## Overview

This header constructs the perpendicular bisector of two distinct 2D points.
It returns an infinite `Line<T>` through two points of the same coordinate type
as the input. Floating-point and integral coordinate types are both supported.

For integral coordinates, the returned endpoints are lattice points and all
calculations used to construct them are integral.

## Function

```cpp
template <Coordinate T>
constexpr Line<T> perpendicular_bisector(
    const Point<T>& first,
    const Point<T>& second
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `perpendicular_bisector(first, second)` | Returns the perpendicular bisector using coordinate type `T`. | $O(\log C)$ for integral `T`; $O(1)$ otherwise |

Here $C$ is the magnitude of the coordinate differences. The logarithmic term
comes from computing their greatest common divisor.

The two input points must be distinct. For integral `T`, the bisector must
contain lattice points and two distinct such points must be representable by
`T`. These preconditions are checked with assertions. The lattice-point
condition is exactly

$$
\gcd(2\Delta x,2\Delta y)\mid
x_2^2+y_2^2-x_1^2-y_1^2.
$$

For example, `(0, 0)` and `(1, 0)` do not satisfy the condition because their
bisector is $x=1/2$. Intermediate integral calculations use `wide_type<T>` and
must fit that type. The function does not mutate either input point.

## Example

```cpp
#include "geometry/perpendicular_bisector.hpp"

#include <iostream>

int main() {
    using namespace m1une::geometry;

    Point<long long> first(0, 0);
    Point<long long> second(1, 1);
    Line<long long> bisector = perpendicular_bisector(first, second);

    std::cout << bisector.a.x << ' ' << bisector.a.y << '\n'; // 1 0
    std::cout << bisector.b.x << ' ' << bisector.b.y << '\n'; // 0 1
}
```
