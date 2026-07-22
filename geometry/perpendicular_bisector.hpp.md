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
    \n#line 1 \"geometry/line.hpp\"\n\n\n\n#line 6 \"geometry/line.hpp\"\n#include\
    \ <cmath>\n#include <optional>\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#line\
    \ 7 \"geometry/point.hpp\"\n#include <type_traits>\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T>\
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
    \n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 11 \"geometry/perpendicular_bisector.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\nnamespace perpendicular_bisector_detail\
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
    \ <limits>\n#include <numeric>\n\n#include \"line.hpp\"\n\nnamespace m1une {\n\
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
  - geometry/line.hpp
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/perpendicular_bisector.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-22 02:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/perpendicular_bisector.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/centroid.test.cpp
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
