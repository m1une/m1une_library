---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree.hpp
    title: Fenwick Tree (Binary Indexed Tree)
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
    path: verify/geometry/manhattan_segment_intersections.test.cpp
    title: verify/geometry/manhattan_segment_intersections.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/manhattan_segment_intersections.hpp\"\n\n\n\n#line\
    \ 1 \"ds/range_query/fenwick_tree.hpp\"\n\n\n\n#include <cassert>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct FenwickTree\
    \ {\n   private:\n    int _n;\n    int _max_power;\n    std::vector<T> _data;\n\
    \n    static int max_power_leq(int n) {\n        int result = 1;\n        while\
    \ (result <= n / 2) result <<= 1;\n        return result;\n    }\n\n    T prefix_sum(int\
    \ r) const {\n        T result{};\n        const T* data = _data.data();\n   \
    \     while (r > 0) {\n            result += data[r];\n            r -= r & -r;\n\
    \        }\n        return result;\n    }\n\n   public:\n    FenwickTree() : _n(0),\
    \ _max_power(0) {}\n\n    explicit FenwickTree(int n)\n        : _n(n), _max_power(max_power_leq(n\
    \ > 0 ? n : 1)), _data(n + 1, T{}) {}\n\n    explicit FenwickTree(const std::vector<T>&\
    \ a)\n        : _n(int(a.size())),\n          _max_power(max_power_leq(_n > 0\
    \ ? _n : 1)),\n          _data(a.size() + 1, T{}) {\n        for (int i = 1; i\
    \ <= _n; ++i) {\n            _data[i] += a[i - 1];\n            const int p =\
    \ i + (i & -i);\n            if (p <= _n) {\n                _data[p] += _data[i];\n\
    \            }\n        }\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    // Adds\
    \ `x` to the element at zero-based index `p`.\n    void add(int p, const T& x)\
    \ {\n        assert(0 <= p && p < _n);\n        ++p;\n        T* data = _data.data();\n\
    \        while (p <= _n) {\n            data[p] += x;\n            p += p & -p;\n\
    \        }\n    }\n\n    // Returns the sum of elements in the range [0, r).\n\
    \    T sum(int r) const {\n        assert(0 <= r && r <= _n);\n        return\
    \ prefix_sum(r);\n    }\n\n    // Returns the sum of elements in the range [l,\
    \ r).\n    T sum(int l, int r) const {\n        assert(0 <= l && l <= r && r <=\
    \ _n);\n        return prefix_sum(r) - prefix_sum(l);\n    }\n\n    // Returns\
    \ the minimum index `r` such that the sum of [0, r) >= w.\n    // Requires all\
    \ elements in the tree to be non-negative.\n    int lower_bound(T w) const {\n\
    \        if (w <= 0) return 0;\n        int x = 0;\n        const T* data = _data.data();\n\
    \        for (int k = _max_power; k > 0; k >>= 1) {\n            if (x + k <=\
    \ _n && data[x + k] < w) {\n                w -= data[x + k];\n              \
    \  x += k;\n            }\n        }\n        return x + 1;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 1 \"geometry/line.hpp\"\n\n\n\
    \n#include <algorithm>\n#line 6 \"geometry/line.hpp\"\n#include <cmath>\n#include\
    \ <optional>\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#line 5 \"geometry/point.hpp\"\
    \n#include <concepts>\n#line 7 \"geometry/point.hpp\"\n#include <type_traits>\n\
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
    \n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 6 \"geometry/manhattan_segment_intersections.hpp\"\
    \n\n#line 10 \"geometry/manhattan_segment_intersections.hpp\"\n#include <limits>\n\
    #include <set>\n#line 13 \"geometry/manhattan_segment_intersections.hpp\"\n\n\
    namespace m1une {\nnamespace geometry {\n\nnamespace manhattan_segment_intersections_detail\
    \ {\n\nenum class EventKind {\n    add,\n    query,\n    remove,\n};\n\ntemplate\
    \ <std::integral T>\nstruct Event {\n    T y;\n    T left;\n    T right;\n   \
    \ EventKind kind;\n\n    Event(T y_value, T left_value, T right_value, EventKind\
    \ kind_value)\n        : y(y_value),\n          left(left_value),\n          right(right_value),\n\
    \          kind(kind_value) {}\n};\n\ntemplate <std::integral T>\nstd::vector<Event<T>>\
    \ make_events(\n    const std::vector<Segment<T>>& segments,\n    std::vector<T>*\
    \ vertical_x_coordinates = nullptr\n) {\n    assert(segments.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n    std::vector<Event<T>> events;\n    events.reserve(2 * segments.size());\n\
    \    if (vertical_x_coordinates != nullptr) {\n        vertical_x_coordinates->reserve(segments.size());\n\
    \    }\n\n    for (const Segment<T>& segment : segments) {\n        assert(segment.a\
    \ != segment.b);\n        assert(segment.a.x == segment.b.x || segment.a.y ==\
    \ segment.b.y);\n\n        if (segment.a.x == segment.b.x) {\n            T bottom\
    \ = std::min(segment.a.y, segment.b.y);\n            T top = std::max(segment.a.y,\
    \ segment.b.y);\n            events.emplace_back(\n                bottom,\n \
    \               segment.a.x,\n                segment.a.x,\n                EventKind::add\n\
    \            );\n            events.emplace_back(\n                top,\n    \
    \            segment.a.x,\n                segment.a.x,\n                EventKind::remove\n\
    \            );\n            if (vertical_x_coordinates != nullptr) {\n      \
    \          vertical_x_coordinates->push_back(segment.a.x);\n            }\n  \
    \      } else {\n            T left = std::min(segment.a.x, segment.b.x);\n  \
    \          T right = std::max(segment.a.x, segment.b.x);\n            events.emplace_back(\n\
    \                segment.a.y,\n                left,\n                right,\n\
    \                EventKind::query\n            );\n        }\n    }\n\n    std::sort(\n\
    \        events.begin(),\n        events.end(),\n        [](const Event<T>& a,\
    \ const Event<T>& b) {\n            if (a.y != b.y) return a.y < b.y;\n      \
    \      if (a.kind != b.kind) return a.kind < b.kind;\n            if (a.left !=\
    \ b.left) return a.left < b.left;\n            return a.right < b.right;\n   \
    \     }\n    );\n    return events;\n}\n\n}  // namespace manhattan_segment_intersections_detail\n\
    \n// Counts intersecting horizontal-vertical pairs of closed segments.\ntemplate\
    \ <std::integral T>\nlong long manhattan_segment_intersections(\n    const std::vector<Segment<T>>&\
    \ segments\n) {\n    using Event = manhattan_segment_intersections_detail::Event<T>;\n\
    \    using EventKind =\n        manhattan_segment_intersections_detail::EventKind;\n\
    \n    std::vector<T> vertical_x_coordinates;\n    std::vector<Event> events =\n\
    \        manhattan_segment_intersections_detail::make_events(\n            segments,\n\
    \            &vertical_x_coordinates\n        );\n\n    std::sort(\n        vertical_x_coordinates.begin(),\n\
    \        vertical_x_coordinates.end()\n    );\n    vertical_x_coordinates.erase(\n\
    \        std::unique(\n            vertical_x_coordinates.begin(),\n         \
    \   vertical_x_coordinates.end()\n        ),\n        vertical_x_coordinates.end()\n\
    \    );\n    m1une::ds::FenwickTree<long long> active(\n        int(vertical_x_coordinates.size())\n\
    \    );\n    long long result = 0;\n    for (const Event& event : events) {\n\
    \        if (event.kind == EventKind::query) {\n            int left = int(\n\
    \                std::lower_bound(\n                    vertical_x_coordinates.begin(),\n\
    \                    vertical_x_coordinates.end(),\n                    event.left\n\
    \                ) - vertical_x_coordinates.begin()\n            );\n        \
    \    int right = int(\n                std::upper_bound(\n                   \
    \ vertical_x_coordinates.begin(),\n                    vertical_x_coordinates.end(),\n\
    \                    event.right\n                ) - vertical_x_coordinates.begin()\n\
    \            );\n            result += active.sum(left, right);\n            continue;\n\
    \        }\n\n        int x = int(\n            std::lower_bound(\n          \
    \      vertical_x_coordinates.begin(),\n                vertical_x_coordinates.end(),\n\
    \                event.left\n            ) - vertical_x_coordinates.begin()\n\
    \        );\n        active.add(x, event.kind == EventKind::add ? 1 : -1);\n \
    \   }\n    return result;\n}\n\n// Returns one point per intersecting horizontal-vertical\
    \ pair.\ntemplate <std::integral T>\nstd::vector<Point<T>> manhattan_segment_intersection_points(\n\
    \    const std::vector<Segment<T>>& segments\n) {\n    using Event = manhattan_segment_intersections_detail::Event<T>;\n\
    \    using EventKind =\n        manhattan_segment_intersections_detail::EventKind;\n\
    \n    std::vector<Event> events =\n        manhattan_segment_intersections_detail::make_events(segments);\n\
    \    std::multiset<T> active;\n    std::vector<Point<T>> result;\n\n    for (const\
    \ Event& event : events) {\n        if (event.kind == EventKind::add) {\n    \
    \        active.insert(event.left);\n        } else if (event.kind == EventKind::remove)\
    \ {\n            auto iterator = active.find(event.left);\n            assert(iterator\
    \ != active.end());\n            active.erase(iterator);\n        } else {\n \
    \           auto iterator = active.lower_bound(event.left);\n            while\
    \ (iterator != active.end() && *iterator <= event.right) {\n                result.emplace_back(*iterator,\
    \ event.y);\n                ++iterator;\n            }\n        }\n    }\n  \
    \  return result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_MANHATTAN_SEGMENT_INTERSECTIONS_HPP\n#define M1UNE_GEOMETRY_MANHATTAN_SEGMENT_INTERSECTIONS_HPP\
    \ 1\n\n#include \"../ds/range_query/fenwick_tree.hpp\"\n#include \"line.hpp\"\n\
    \n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include <limits>\n\
    #include <set>\n#include <vector>\n\nnamespace m1une {\nnamespace geometry {\n\
    \nnamespace manhattan_segment_intersections_detail {\n\nenum class EventKind {\n\
    \    add,\n    query,\n    remove,\n};\n\ntemplate <std::integral T>\nstruct Event\
    \ {\n    T y;\n    T left;\n    T right;\n    EventKind kind;\n\n    Event(T y_value,\
    \ T left_value, T right_value, EventKind kind_value)\n        : y(y_value),\n\
    \          left(left_value),\n          right(right_value),\n          kind(kind_value)\
    \ {}\n};\n\ntemplate <std::integral T>\nstd::vector<Event<T>> make_events(\n \
    \   const std::vector<Segment<T>>& segments,\n    std::vector<T>* vertical_x_coordinates\
    \ = nullptr\n) {\n    assert(segments.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n    std::vector<Event<T>> events;\n    events.reserve(2 * segments.size());\n\
    \    if (vertical_x_coordinates != nullptr) {\n        vertical_x_coordinates->reserve(segments.size());\n\
    \    }\n\n    for (const Segment<T>& segment : segments) {\n        assert(segment.a\
    \ != segment.b);\n        assert(segment.a.x == segment.b.x || segment.a.y ==\
    \ segment.b.y);\n\n        if (segment.a.x == segment.b.x) {\n            T bottom\
    \ = std::min(segment.a.y, segment.b.y);\n            T top = std::max(segment.a.y,\
    \ segment.b.y);\n            events.emplace_back(\n                bottom,\n \
    \               segment.a.x,\n                segment.a.x,\n                EventKind::add\n\
    \            );\n            events.emplace_back(\n                top,\n    \
    \            segment.a.x,\n                segment.a.x,\n                EventKind::remove\n\
    \            );\n            if (vertical_x_coordinates != nullptr) {\n      \
    \          vertical_x_coordinates->push_back(segment.a.x);\n            }\n  \
    \      } else {\n            T left = std::min(segment.a.x, segment.b.x);\n  \
    \          T right = std::max(segment.a.x, segment.b.x);\n            events.emplace_back(\n\
    \                segment.a.y,\n                left,\n                right,\n\
    \                EventKind::query\n            );\n        }\n    }\n\n    std::sort(\n\
    \        events.begin(),\n        events.end(),\n        [](const Event<T>& a,\
    \ const Event<T>& b) {\n            if (a.y != b.y) return a.y < b.y;\n      \
    \      if (a.kind != b.kind) return a.kind < b.kind;\n            if (a.left !=\
    \ b.left) return a.left < b.left;\n            return a.right < b.right;\n   \
    \     }\n    );\n    return events;\n}\n\n}  // namespace manhattan_segment_intersections_detail\n\
    \n// Counts intersecting horizontal-vertical pairs of closed segments.\ntemplate\
    \ <std::integral T>\nlong long manhattan_segment_intersections(\n    const std::vector<Segment<T>>&\
    \ segments\n) {\n    using Event = manhattan_segment_intersections_detail::Event<T>;\n\
    \    using EventKind =\n        manhattan_segment_intersections_detail::EventKind;\n\
    \n    std::vector<T> vertical_x_coordinates;\n    std::vector<Event> events =\n\
    \        manhattan_segment_intersections_detail::make_events(\n            segments,\n\
    \            &vertical_x_coordinates\n        );\n\n    std::sort(\n        vertical_x_coordinates.begin(),\n\
    \        vertical_x_coordinates.end()\n    );\n    vertical_x_coordinates.erase(\n\
    \        std::unique(\n            vertical_x_coordinates.begin(),\n         \
    \   vertical_x_coordinates.end()\n        ),\n        vertical_x_coordinates.end()\n\
    \    );\n    m1une::ds::FenwickTree<long long> active(\n        int(vertical_x_coordinates.size())\n\
    \    );\n    long long result = 0;\n    for (const Event& event : events) {\n\
    \        if (event.kind == EventKind::query) {\n            int left = int(\n\
    \                std::lower_bound(\n                    vertical_x_coordinates.begin(),\n\
    \                    vertical_x_coordinates.end(),\n                    event.left\n\
    \                ) - vertical_x_coordinates.begin()\n            );\n        \
    \    int right = int(\n                std::upper_bound(\n                   \
    \ vertical_x_coordinates.begin(),\n                    vertical_x_coordinates.end(),\n\
    \                    event.right\n                ) - vertical_x_coordinates.begin()\n\
    \            );\n            result += active.sum(left, right);\n            continue;\n\
    \        }\n\n        int x = int(\n            std::lower_bound(\n          \
    \      vertical_x_coordinates.begin(),\n                vertical_x_coordinates.end(),\n\
    \                event.left\n            ) - vertical_x_coordinates.begin()\n\
    \        );\n        active.add(x, event.kind == EventKind::add ? 1 : -1);\n \
    \   }\n    return result;\n}\n\n// Returns one point per intersecting horizontal-vertical\
    \ pair.\ntemplate <std::integral T>\nstd::vector<Point<T>> manhattan_segment_intersection_points(\n\
    \    const std::vector<Segment<T>>& segments\n) {\n    using Event = manhattan_segment_intersections_detail::Event<T>;\n\
    \    using EventKind =\n        manhattan_segment_intersections_detail::EventKind;\n\
    \n    std::vector<Event> events =\n        manhattan_segment_intersections_detail::make_events(segments);\n\
    \    std::multiset<T> active;\n    std::vector<Point<T>> result;\n\n    for (const\
    \ Event& event : events) {\n        if (event.kind == EventKind::add) {\n    \
    \        active.insert(event.left);\n        } else if (event.kind == EventKind::remove)\
    \ {\n            auto iterator = active.find(event.left);\n            assert(iterator\
    \ != active.end());\n            active.erase(iterator);\n        } else {\n \
    \           auto iterator = active.lower_bound(event.left);\n            while\
    \ (iterator != active.end() && *iterator <= event.right) {\n                result.emplace_back(*iterator,\
    \ event.y);\n                ++iterator;\n            }\n        }\n    }\n  \
    \  return result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_GEOMETRY_MANHATTAN_SEGMENT_INTERSECTIONS_HPP\n"
  dependsOn:
  - ds/range_query/fenwick_tree.hpp
  - geometry/line.hpp
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/manhattan_segment_intersections.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-22 15:13:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/centroid.test.cpp
  - verify/geometry/manhattan_segment_intersections.test.cpp
documentation_of: geometry/manhattan_segment_intersections.hpp
layout: document
title: Manhattan Segment Intersections
---

## Overview

`manhattan_segment_intersections` counts pairs formed by one horizontal and one
vertical closed segment that intersect. `manhattan_segment_intersection_points`
returns their exact integral intersection points. Segment endpoints are
included, so a perpendicular pair touching at an endpoint contributes one.

The implementation sweeps upward through the endpoint and query events. A
Fenwick tree over compressed x-coordinates stores the active vertical segments.
At the same y-coordinate, vertical segments are added before horizontal queries
and removed afterward, which gives the closed-endpoint behavior.

If parallel segments do not overlap or touch, the result is the total number of
intersections among the input segments. This is the condition used by AOJ
CGL_6_A. Otherwise, the function still counts all horizontal-vertical pairs but
does not count parallel pairs.

## Interface

```cpp
template <std::integral T>
long long manhattan_segment_intersections(
    const std::vector<Segment<T>>& segments
);

template <std::integral T>
std::vector<Point<T>> manhattan_segment_intersection_points(
    const std::vector<Segment<T>>& segments
);
```

| Function | Complexity | Description |
| --- | --- | --- |
| `manhattan_segment_intersections(segments)` | $O(N\log N)$ time and $O(N)$ memory | Returns the number of intersecting horizontal-vertical pairs without modifying the input. |
| `manhattan_segment_intersection_points(segments)` | $O(N\log N+K)$ time and $O(N+K)$ memory | Returns one exact point for each of the $K$ intersecting horizontal-vertical pairs. |

Every segment must be nondegenerate and parallel to one coordinate axis. These
requirements and the conversion of the input size to `int` are checked by
assertions. Coordinates must be integral. The count is returned as `long long`.
The point order follows the sweep and should not be treated as sorted. If
several segment pairs meet at the same coordinate, that point occurs once per
pair, so the point-vector size always equals the counting result.

## Example

```cpp
#include "geometry/manhattan_segment_intersections.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    using Segment = m1une::geometry::Segment<long long>;

    std::vector<Segment> segments;
    segments.push_back(Segment{Point(0, 0), Point(0, 4)});
    segments.push_back(Segment{Point(-2, 2), Point(3, 2)});
    segments.push_back(Segment{Point(2, 1), Point(2, 3)});

    auto intersections =
        m1une::geometry::manhattan_segment_intersection_points(segments);
    for (const Point& point : intersections) {
        std::cout << point.x << " " << point.y << "\n";
    }
}
```
