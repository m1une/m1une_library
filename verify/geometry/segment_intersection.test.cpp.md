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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B
  bundledCode: "#line 1 \"verify/geometry/segment_intersection.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B\"\
    \n\n#line 1 \"geometry/linear.hpp\"\n\n\n\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <cmath>\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n\
    #line 5 \"geometry/point.hpp\"\n#include <concepts>\n#line 7 \"geometry/point.hpp\"\
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
    }  // namespace m1une\n\n\n#line 4 \"verify/geometry/segment_intersection.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 6 \"utilities/fast_io.hpp\"\
    \n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#include <cstdint>\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <sys/stat.h>\n#line 17 \"utilities/fast_io.hpp\"\n\
    #include <utility>\n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 6 \"verify/geometry/segment_intersection.test.cpp\"\
    \n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    using namespace m1une::geometry;\n    int q;\n    fast_input\
    \ >> q;\n    while (q--) {\n        Segment<long long> first;\n        Segment<long\
    \ long> second;\n        fast_input >> first.a.x >> first.a.y >> first.b.x >>\
    \ first.b.y;\n        fast_input >> second.a.x >> second.a.y >> second.b.x >>\
    \ second.b.y;\n        fast_output << intersects(first, second) << '\\n';\n  \
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B\"\
    \n\n#include \"../../geometry/linear.hpp\"\n\n#include \"../../utilities/fast_io.hpp\"\
    \n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    using namespace m1une::geometry;\n    int q;\n    fast_input\
    \ >> q;\n    while (q--) {\n        Segment<long long> first;\n        Segment<long\
    \ long> second;\n        fast_input >> first.a.x >> first.a.y >> first.b.x >>\
    \ first.b.y;\n        fast_input >> second.a.x >> second.a.y >> second.b.x >>\
    \ second.b.y;\n        fast_output << intersects(first, second) << '\\n';\n  \
    \  }\n}\n"
  dependsOn:
  - geometry/linear.hpp
  - geometry/point.hpp
  - geometry/detail/floating_predicate.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/segment_intersection.test.cpp
  requiredBy: []
  timestamp: '2026-08-20 21:54:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/segment_intersection.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/segment_intersection.test.cpp
- /verify/verify/geometry/segment_intersection.test.cpp.html
title: verify/geometry/segment_intersection.test.cpp
---
