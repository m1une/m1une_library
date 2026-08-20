---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree.hpp
    title: Fenwick Tree (Binary Indexed Tree)
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
    \ namespace ds\n}  // namespace m1une\n\n\n#line 1 \"geometry/linear.hpp\"\n\n\
    \n\n#include <algorithm>\n#line 6 \"geometry/linear.hpp\"\n#include <cmath>\n\n\
    #line 1 \"geometry/point.hpp\"\n\n\n\n#line 5 \"geometry/point.hpp\"\n#include\
    \ <concepts>\n#line 7 \"geometry/point.hpp\"\n#include <type_traits>\n\n#line\
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
    }  // namespace m1une\n\n\n#line 6 \"geometry/manhattan_segment_intersections.hpp\"\
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
    \ 1\n\n#include \"../ds/range_query/fenwick_tree.hpp\"\n#include \"linear.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include <limits>\n\
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
  - geometry/linear.hpp
  - geometry/point.hpp
  - geometry/detail/floating_predicate.hpp
  isVerificationFile: false
  path: geometry/manhattan_segment_intersections.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-08-20 22:35:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/centroid.test.cpp
  - verify/geometry/manhattan_segment_intersections.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
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
