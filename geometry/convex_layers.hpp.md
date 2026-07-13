---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/geometry/convex_layers.test.cpp
    title: verify/geometry/convex_layers.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/convex_layers.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"geometry/point.hpp\"\n\n\n\n#include <cmath>\n#include <concepts>\n\
    #line 7 \"geometry/point.hpp\"\n#include <type_traits>\n\nnamespace m1une {\n\
    namespace geometry {\n\ntemplate <typename T>\nconcept Coordinate = std::is_arithmetic_v<T>\
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
    \    }\n};\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator*(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ * Result(scalar),\n        Result(point.y) * Result(scalar)\n    );\n}\n\ntemplate\
    \ <typename Scalar, Coordinate T>\nrequires std::is_arithmetic_v<Scalar>\nconstexpr\
    \ auto operator*(Scalar scalar, const Point<T>& point) {\n    return point * scalar;\n\
    }\n\ntemplate <Coordinate T, typename Scalar>\nrequires std::is_arithmetic_v<Scalar>\n\
    constexpr auto operator/(const Point<T>& point, Scalar scalar) {\n    using Result\
    \ = std::common_type_t<T, Scalar>;\n    return Point<Result>(\n        Result(point.x)\
    \ / Result(scalar),\n        Result(point.y) / Result(scalar)\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr wide_type<T> dot(const Point<T>& a, const Point<T>&\
    \ b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.x) + W(a.y) * W(b.y);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(const Point<T>& a,\
    \ const Point<T>& b) {\n    using W = wide_type<T>;\n    return W(a.x) * W(b.y)\
    \ - W(a.y) * W(b.x);\n}\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> cross(\n\
    \    const Point<T>& origin,\n    const Point<T>& a,\n    const Point<T>& b\n\
    ) {\n    using W = wide_type<T>;\n    W ax = W(a.x) - W(origin.x);\n    W ay =\
    \ W(a.y) - W(origin.y);\n    W bx = W(b.x) - W(origin.x);\n    W by = W(b.y) -\
    \ W(origin.y);\n    return ax * by - ay * bx;\n}\n\ntemplate <Coordinate T>\n\
    constexpr wide_type<T> norm2(const Point<T>& point) {\n    return dot(point, point);\n\
    }\n\ntemplate <Coordinate T>\nconstexpr wide_type<T> distance2(const Point<T>&\
    \ a, const Point<T>& b) {\n    using W = wide_type<T>;\n    W dx = W(a.x) - W(b.x);\n\
    \    W dy = W(a.y) - W(b.y);\n    return dx * dx + dy * dy;\n}\n\ntemplate <Coordinate\
    \ T>\nlong double norm(const Point<T>& point) {\n    return std::hypot(\n    \
    \    static_cast<long double>(point.x),\n        static_cast<long double>(point.y)\n\
    \    );\n}\n\ntemplate <Coordinate T>\nlong double distance(const Point<T>& a,\
    \ const Point<T>& b) {\n    return std::hypot(\n        static_cast<long double>(a.x)\
    \ - static_cast<long double>(b.x),\n        static_cast<long double>(a.y) - static_cast<long\
    \ double>(b.y)\n    );\n}\n\ntemplate <Coordinate T, typename M, typename N>\n\
    requires std::is_arithmetic_v<M> && std::is_arithmetic_v<N>\nconstexpr Point<long\
    \ double> internal_division_point(\n    const Point<T>& a,\n    const Point<T>&\
    \ b,\n    M m,\n    N n\n) {\n    long double first_ratio = static_cast<long double>(m);\n\
    \    long double second_ratio = static_cast<long double>(n);\n    long double\
    \ denominator = first_ratio + second_ratio;\n    assert(denominator != 0);\n \
    \   Point<long double> first(a);\n    Point<long double> direction = Point<long\
    \ double>(b) - first;\n    return first + direction * (first_ratio / denominator);\n\
    }\n\ntemplate <Coordinate T, typename M, typename N>\nrequires std::is_arithmetic_v<M>\
    \ && std::is_arithmetic_v<N>\nconstexpr Point<long double> external_division_point(\n\
    \    const Point<T>& a,\n    const Point<T>& b,\n    M m,\n    N n\n) {\n    long\
    \ double first_ratio = static_cast<long double>(m);\n    long double second_ratio\
    \ = static_cast<long double>(n);\n    long double denominator = first_ratio -\
    \ second_ratio;\n    assert(denominator != 0);\n    Point<long double> first(a);\n\
    \    Point<long double> direction = Point<long double>(b) - first;\n    return\
    \ first + direction * (first_ratio / denominator);\n}\n\ntemplate <Coordinate\
    \ T>\nconstexpr int sign(wide_type<T> value, long double eps = 1e-12L) {\n   \
    \ if constexpr (std::integral<T>) {\n        return (value > 0) - (value < 0);\n\
    \    } else {\n        return (value > eps) - (value < -eps);\n    }\n}\n\ntemplate\
    \ <Coordinate T>\nconstexpr int orientation(\n    const Point<T>& a,\n    const\
    \ Point<T>& b,\n    const Point<T>& c,\n    long double eps = 1e-12L\n) {\n  \
    \  return sign<T>(cross(a, b, c), eps);\n}\n\ntemplate <Coordinate T>\nconstexpr\
    \ bool collinear(\n    const Point<T>& a,\n    const Point<T>& b,\n    const Point<T>&\
    \ c,\n    long double eps = 1e-12L\n) {\n    return orientation(a, b, c, eps)\
    \ == 0;\n}\n\ntemplate <Coordinate T>\nPoint<long double> rotate(const Point<T>&\
    \ point, long double angle) {\n    long double cosine = std::cos(angle);\n   \
    \ long double sine = std::sin(angle);\n    return Point<long double>(\n      \
    \  static_cast<long double>(point.x) * cosine -\n            static_cast<long\
    \ double>(point.y) * sine,\n        static_cast<long double>(point.x) * sine +\n\
    \            static_cast<long double>(point.y) * cosine\n    );\n}\n\ntemplate\
    \ <Coordinate T>\nPoint<long double> normalized(const Point<T>& point) {\n   \
    \ long double length = norm(point);\n    assert(length != 0);\n    return Point<long\
    \ double>(\n        static_cast<long double>(point.x) / length,\n        static_cast<long\
    \ double>(point.y) / length\n    );\n}\n\n}  // namespace geometry\n}  // namespace\
    \ m1une\n\n\n#line 11 \"geometry/convex_layers.hpp\"\n\nnamespace m1une {\nnamespace\
    \ geometry {\n\nnamespace convex_layers_detail {\n\ntemplate <Coordinate T>\n\
    struct LayerPoint {\n    wide_type<T> x;\n    wide_type<T> y;\n};\n\ntemplate\
    \ <Coordinate T>\nwide_type<T> layer_cross(\n    const LayerPoint<T>& first,\n\
    \    const LayerPoint<T>& second,\n    const LayerPoint<T>& third\n) {\n    return\n\
    \        (second.x - first.x) * (third.y - first.y) -\n        (second.y - first.y)\
    \ * (third.x - first.x);\n}\n\ntemplate <Coordinate T>\nclass DecrementalHull\
    \ {\n   private:\n    struct Node {\n        int left_bound;\n        int right_bound;\n\
    \        int bridge_left;\n        int bridge_right;\n        int left_child;\n\
    \        int right_child;\n    };\n\n    std::vector<LayerPoint<T>> points;\n\
    \    std::vector<Node> nodes;\n    int root;\n\n    bool is_leaf(int node) const\
    \ {\n        return nodes[node].left_child == -1 && nodes[node].right_child ==\
    \ -1;\n    }\n\n    void pull(int node) {\n        int left = nodes[node].left_child;\n\
    \        int right = nodes[node].right_child;\n        assert(left != -1 && right\
    \ != -1);\n        using Wide = wide_type<T>;\n        const Wide split_y = points[nodes[right].left_bound].y;\n\
    \n        while (!is_leaf(left) || !is_leaf(right)) {\n            const int a\
    \ = nodes[left].bridge_left;\n            const int b = nodes[left].bridge_right;\n\
    \            const int c = nodes[right].bridge_left;\n            const int d\
    \ = nodes[right].bridge_right;\n\n            if (\n                a != b &&\n\
    \                sign<T>(layer_cross<T>(points[a], points[b], points[c])) > 0\n\
    \            ) {\n                left = nodes[left].left_child;\n           \
    \ } else if (\n                c != d &&\n                sign<T>(layer_cross<T>(points[b],\
    \ points[c], points[d])) > 0\n            ) {\n                right = nodes[right].right_child;\n\
    \            } else if (a == b) {\n                right = nodes[right].left_child;\n\
    \            } else if (c == d) {\n                left = nodes[left].right_child;\n\
    \            } else {\n                const Wide first =\n                  \
    \  layer_cross<T>(points[a], points[b], points[c]);\n                const Wide\
    \ second =\n                    layer_cross<T>(points[b], points[a], points[d]);\n\
    \                const Wide sum = first + second;\n                assert(sign<T>(sum)\
    \ >= 0);\n                const Wide comparison =\n                    first *\
    \ points[d].y + second * points[c].y - split_y * sum;\n                if (sign<T>(sum)\
    \ == 0 || sign<T>(comparison) < 0) {\n                    left = nodes[left].right_child;\n\
    \                } else {\n                    right = nodes[right].left_child;\n\
    \                }\n            }\n        }\n        nodes[node].bridge_left\
    \ = nodes[left].left_bound;\n        nodes[node].bridge_right = nodes[right].left_bound;\n\
    \    }\n\n    void build(int node, int left, int right) {\n        nodes[node].left_bound\
    \ = left;\n        nodes[node].right_bound = right;\n        if (right - left\
    \ == 1) {\n            nodes[node].bridge_left = left;\n            nodes[node].bridge_right\
    \ = left;\n            nodes[node].left_child = -1;\n            nodes[node].right_child\
    \ = -1;\n            return;\n        }\n\n        const int middle = (left +\
    \ right) / 2;\n        nodes[node].left_child = node + 1;\n        nodes[node].right_child\
    \ = node + 2 * (middle - left);\n        build(nodes[node].left_child, left, middle);\n\
    \        build(nodes[node].right_child, middle, right);\n        pull(node);\n\
    \    }\n\n    int erase(int node, int position) {\n        if (\n            position\
    \ < nodes[node].left_bound ||\n            nodes[node].right_bound <= position\n\
    \        ) {\n            return node;\n        }\n        if (nodes[node].right_bound\
    \ - nodes[node].left_bound == 1) return -1;\n\n        nodes[node].left_child\
    \ = erase(nodes[node].left_child, position);\n        nodes[node].right_child\
    \ = erase(nodes[node].right_child, position);\n        if (nodes[node].left_child\
    \ == -1) return nodes[node].right_child;\n        if (nodes[node].right_child\
    \ == -1) return nodes[node].left_child;\n        pull(node);\n        return node;\n\
    \    }\n\n    void collect(\n        int node,\n        int left,\n        int\
    \ right,\n        std::vector<int>& result\n    ) const {\n        if (is_leaf(node))\
    \ {\n            result.push_back(nodes[node].left_bound);\n        } else if\
    \ (right <= nodes[node].bridge_left) {\n            collect(nodes[node].left_child,\
    \ left, right, result);\n        } else if (nodes[node].bridge_right <= left)\
    \ {\n            collect(nodes[node].right_child, left, right, result);\n    \
    \    } else {\n            assert(\n                left <= nodes[node].bridge_left\
    \ &&\n                nodes[node].bridge_right <= right\n            );\n    \
    \        collect(\n                nodes[node].left_child,\n                left,\n\
    \                nodes[node].bridge_left,\n                result\n          \
    \  );\n            collect(\n                nodes[node].right_child,\n      \
    \          nodes[node].bridge_right,\n                right,\n               \
    \ result\n            );\n        }\n    }\n\n   public:\n    explicit DecrementalHull(std::vector<LayerPoint<T>>\
    \ ordered_points)\n        : points(std::move(ordered_points)),\n          nodes(2\
    \ * points.size()),\n          root(points.empty() ? -1 : 0) {\n        if (!points.empty())\
    \ build(0, 0, int(points.size()));\n    }\n\n    std::vector<int> hull() const\
    \ {\n        std::vector<int> result;\n        if (root != -1) collect(root, 0,\
    \ int(points.size()) - 1, result);\n        return result;\n    }\n\n    void\
    \ erase(int position) {\n        assert(root != -1);\n        assert(0 <= position\
    \ && position < int(points.size()));\n        root = erase(root, position);\n\
    \    }\n};\n\n}  // namespace convex_layers_detail\n\ntemplate <Coordinate T>\n\
    std::vector<int> convex_layers(const std::vector<Point<T>>& points) {\n    const\
    \ int n = int(points.size());\n    if (n == 0) return {};\n\n    struct IndexedPoint\
    \ {\n        Point<T> point;\n        int original_index;\n    };\n    std::vector<IndexedPoint>\
    \ indexed;\n    indexed.reserve(n);\n    for (int index = 0; index < n; index++)\
    \ {\n        indexed.push_back(IndexedPoint{points[index], index});\n    }\n \
    \   std::sort(\n        indexed.begin(),\n        indexed.end(),\n        [](const\
    \ IndexedPoint& first, const IndexedPoint& second) {\n            if (first.point.y\
    \ != second.point.y) {\n                return first.point.y < second.point.y;\n\
    \            }\n            if (first.point.x != second.point.x) {\n         \
    \       return first.point.x < second.point.x;\n            }\n            return\
    \ first.original_index < second.original_index;\n        }\n    );\n\n    std::vector<Point<T>>\
    \ ordered;\n    std::vector<int> position(n);\n    ordered.reserve(n);\n    for\
    \ (const IndexedPoint& item : indexed) {\n        if (ordered.empty() || !(ordered.back()\
    \ == item.point)) {\n            ordered.push_back(item.point);\n        }\n \
    \       position[item.original_index] = int(ordered.size()) - 1;\n    }\n\n  \
    \  using LayerPoint = convex_layers_detail::LayerPoint<T>;\n    using Wide = wide_type<T>;\n\
    \    std::vector<LayerPoint> left_points;\n    left_points.reserve(ordered.size());\n\
    \    for (const Point<T>& point : ordered) {\n        left_points.push_back(LayerPoint{Wide(point.x),\
    \ Wide(point.y)});\n    }\n    convex_layers_detail::DecrementalHull<T> left_hull(\n\
    \        std::move(left_points)\n    );\n\n    std::vector<LayerPoint> reversed;\n\
    \    reversed.reserve(ordered.size());\n    for (auto iterator = ordered.rbegin();\
    \ iterator != ordered.rend(); ++iterator) {\n        reversed.push_back(LayerPoint{-Wide(iterator->x),\
    \ -Wide(iterator->y)});\n    }\n    convex_layers_detail::DecrementalHull<T> right_hull(std::move(reversed));\n\
    \n    const int distinct_count = int(ordered.size());\n    std::vector<int> layer_by_position(distinct_count,\
    \ 0);\n    std::vector<int> selected_in_layer(distinct_count, 0);\n    int remaining\
    \ = distinct_count;\n    for (int layer = 1; remaining > 0; layer++) {\n     \
    \   std::vector<int> boundary;\n        auto add_boundary = [&](int ordered_position)\
    \ {\n            if (selected_in_layer[ordered_position] == layer) return;\n \
    \           selected_in_layer[ordered_position] = layer;\n            boundary.push_back(ordered_position);\n\
    \        };\n        for (int ordered_position : left_hull.hull()) {\n       \
    \     add_boundary(ordered_position);\n        }\n        for (int reversed_position\
    \ : right_hull.hull()) {\n            add_boundary(distinct_count - 1 - reversed_position);\n\
    \        }\n\n        assert(!boundary.empty());\n        for (int ordered_position\
    \ : boundary) {\n            layer_by_position[ordered_position] = layer;\n  \
    \          left_hull.erase(ordered_position);\n            right_hull.erase(distinct_count\
    \ - 1 - ordered_position);\n            remaining--;\n        }\n    }\n\n   \
    \ std::vector<int> result(n);\n    for (int index = 0; index < n; index++) {\n\
    \        result[index] = layer_by_position[position[index]];\n    }\n    return\
    \ result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GEOMETRY_CONVEX_LAYERS_HPP\n#define M1UNE_GEOMETRY_CONVEX_LAYERS_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"point.hpp\"\n\nnamespace m1une {\n\
    namespace geometry {\n\nnamespace convex_layers_detail {\n\ntemplate <Coordinate\
    \ T>\nstruct LayerPoint {\n    wide_type<T> x;\n    wide_type<T> y;\n};\n\ntemplate\
    \ <Coordinate T>\nwide_type<T> layer_cross(\n    const LayerPoint<T>& first,\n\
    \    const LayerPoint<T>& second,\n    const LayerPoint<T>& third\n) {\n    return\n\
    \        (second.x - first.x) * (third.y - first.y) -\n        (second.y - first.y)\
    \ * (third.x - first.x);\n}\n\ntemplate <Coordinate T>\nclass DecrementalHull\
    \ {\n   private:\n    struct Node {\n        int left_bound;\n        int right_bound;\n\
    \        int bridge_left;\n        int bridge_right;\n        int left_child;\n\
    \        int right_child;\n    };\n\n    std::vector<LayerPoint<T>> points;\n\
    \    std::vector<Node> nodes;\n    int root;\n\n    bool is_leaf(int node) const\
    \ {\n        return nodes[node].left_child == -1 && nodes[node].right_child ==\
    \ -1;\n    }\n\n    void pull(int node) {\n        int left = nodes[node].left_child;\n\
    \        int right = nodes[node].right_child;\n        assert(left != -1 && right\
    \ != -1);\n        using Wide = wide_type<T>;\n        const Wide split_y = points[nodes[right].left_bound].y;\n\
    \n        while (!is_leaf(left) || !is_leaf(right)) {\n            const int a\
    \ = nodes[left].bridge_left;\n            const int b = nodes[left].bridge_right;\n\
    \            const int c = nodes[right].bridge_left;\n            const int d\
    \ = nodes[right].bridge_right;\n\n            if (\n                a != b &&\n\
    \                sign<T>(layer_cross<T>(points[a], points[b], points[c])) > 0\n\
    \            ) {\n                left = nodes[left].left_child;\n           \
    \ } else if (\n                c != d &&\n                sign<T>(layer_cross<T>(points[b],\
    \ points[c], points[d])) > 0\n            ) {\n                right = nodes[right].right_child;\n\
    \            } else if (a == b) {\n                right = nodes[right].left_child;\n\
    \            } else if (c == d) {\n                left = nodes[left].right_child;\n\
    \            } else {\n                const Wide first =\n                  \
    \  layer_cross<T>(points[a], points[b], points[c]);\n                const Wide\
    \ second =\n                    layer_cross<T>(points[b], points[a], points[d]);\n\
    \                const Wide sum = first + second;\n                assert(sign<T>(sum)\
    \ >= 0);\n                const Wide comparison =\n                    first *\
    \ points[d].y + second * points[c].y - split_y * sum;\n                if (sign<T>(sum)\
    \ == 0 || sign<T>(comparison) < 0) {\n                    left = nodes[left].right_child;\n\
    \                } else {\n                    right = nodes[right].left_child;\n\
    \                }\n            }\n        }\n        nodes[node].bridge_left\
    \ = nodes[left].left_bound;\n        nodes[node].bridge_right = nodes[right].left_bound;\n\
    \    }\n\n    void build(int node, int left, int right) {\n        nodes[node].left_bound\
    \ = left;\n        nodes[node].right_bound = right;\n        if (right - left\
    \ == 1) {\n            nodes[node].bridge_left = left;\n            nodes[node].bridge_right\
    \ = left;\n            nodes[node].left_child = -1;\n            nodes[node].right_child\
    \ = -1;\n            return;\n        }\n\n        const int middle = (left +\
    \ right) / 2;\n        nodes[node].left_child = node + 1;\n        nodes[node].right_child\
    \ = node + 2 * (middle - left);\n        build(nodes[node].left_child, left, middle);\n\
    \        build(nodes[node].right_child, middle, right);\n        pull(node);\n\
    \    }\n\n    int erase(int node, int position) {\n        if (\n            position\
    \ < nodes[node].left_bound ||\n            nodes[node].right_bound <= position\n\
    \        ) {\n            return node;\n        }\n        if (nodes[node].right_bound\
    \ - nodes[node].left_bound == 1) return -1;\n\n        nodes[node].left_child\
    \ = erase(nodes[node].left_child, position);\n        nodes[node].right_child\
    \ = erase(nodes[node].right_child, position);\n        if (nodes[node].left_child\
    \ == -1) return nodes[node].right_child;\n        if (nodes[node].right_child\
    \ == -1) return nodes[node].left_child;\n        pull(node);\n        return node;\n\
    \    }\n\n    void collect(\n        int node,\n        int left,\n        int\
    \ right,\n        std::vector<int>& result\n    ) const {\n        if (is_leaf(node))\
    \ {\n            result.push_back(nodes[node].left_bound);\n        } else if\
    \ (right <= nodes[node].bridge_left) {\n            collect(nodes[node].left_child,\
    \ left, right, result);\n        } else if (nodes[node].bridge_right <= left)\
    \ {\n            collect(nodes[node].right_child, left, right, result);\n    \
    \    } else {\n            assert(\n                left <= nodes[node].bridge_left\
    \ &&\n                nodes[node].bridge_right <= right\n            );\n    \
    \        collect(\n                nodes[node].left_child,\n                left,\n\
    \                nodes[node].bridge_left,\n                result\n          \
    \  );\n            collect(\n                nodes[node].right_child,\n      \
    \          nodes[node].bridge_right,\n                right,\n               \
    \ result\n            );\n        }\n    }\n\n   public:\n    explicit DecrementalHull(std::vector<LayerPoint<T>>\
    \ ordered_points)\n        : points(std::move(ordered_points)),\n          nodes(2\
    \ * points.size()),\n          root(points.empty() ? -1 : 0) {\n        if (!points.empty())\
    \ build(0, 0, int(points.size()));\n    }\n\n    std::vector<int> hull() const\
    \ {\n        std::vector<int> result;\n        if (root != -1) collect(root, 0,\
    \ int(points.size()) - 1, result);\n        return result;\n    }\n\n    void\
    \ erase(int position) {\n        assert(root != -1);\n        assert(0 <= position\
    \ && position < int(points.size()));\n        root = erase(root, position);\n\
    \    }\n};\n\n}  // namespace convex_layers_detail\n\ntemplate <Coordinate T>\n\
    std::vector<int> convex_layers(const std::vector<Point<T>>& points) {\n    const\
    \ int n = int(points.size());\n    if (n == 0) return {};\n\n    struct IndexedPoint\
    \ {\n        Point<T> point;\n        int original_index;\n    };\n    std::vector<IndexedPoint>\
    \ indexed;\n    indexed.reserve(n);\n    for (int index = 0; index < n; index++)\
    \ {\n        indexed.push_back(IndexedPoint{points[index], index});\n    }\n \
    \   std::sort(\n        indexed.begin(),\n        indexed.end(),\n        [](const\
    \ IndexedPoint& first, const IndexedPoint& second) {\n            if (first.point.y\
    \ != second.point.y) {\n                return first.point.y < second.point.y;\n\
    \            }\n            if (first.point.x != second.point.x) {\n         \
    \       return first.point.x < second.point.x;\n            }\n            return\
    \ first.original_index < second.original_index;\n        }\n    );\n\n    std::vector<Point<T>>\
    \ ordered;\n    std::vector<int> position(n);\n    ordered.reserve(n);\n    for\
    \ (const IndexedPoint& item : indexed) {\n        if (ordered.empty() || !(ordered.back()\
    \ == item.point)) {\n            ordered.push_back(item.point);\n        }\n \
    \       position[item.original_index] = int(ordered.size()) - 1;\n    }\n\n  \
    \  using LayerPoint = convex_layers_detail::LayerPoint<T>;\n    using Wide = wide_type<T>;\n\
    \    std::vector<LayerPoint> left_points;\n    left_points.reserve(ordered.size());\n\
    \    for (const Point<T>& point : ordered) {\n        left_points.push_back(LayerPoint{Wide(point.x),\
    \ Wide(point.y)});\n    }\n    convex_layers_detail::DecrementalHull<T> left_hull(\n\
    \        std::move(left_points)\n    );\n\n    std::vector<LayerPoint> reversed;\n\
    \    reversed.reserve(ordered.size());\n    for (auto iterator = ordered.rbegin();\
    \ iterator != ordered.rend(); ++iterator) {\n        reversed.push_back(LayerPoint{-Wide(iterator->x),\
    \ -Wide(iterator->y)});\n    }\n    convex_layers_detail::DecrementalHull<T> right_hull(std::move(reversed));\n\
    \n    const int distinct_count = int(ordered.size());\n    std::vector<int> layer_by_position(distinct_count,\
    \ 0);\n    std::vector<int> selected_in_layer(distinct_count, 0);\n    int remaining\
    \ = distinct_count;\n    for (int layer = 1; remaining > 0; layer++) {\n     \
    \   std::vector<int> boundary;\n        auto add_boundary = [&](int ordered_position)\
    \ {\n            if (selected_in_layer[ordered_position] == layer) return;\n \
    \           selected_in_layer[ordered_position] = layer;\n            boundary.push_back(ordered_position);\n\
    \        };\n        for (int ordered_position : left_hull.hull()) {\n       \
    \     add_boundary(ordered_position);\n        }\n        for (int reversed_position\
    \ : right_hull.hull()) {\n            add_boundary(distinct_count - 1 - reversed_position);\n\
    \        }\n\n        assert(!boundary.empty());\n        for (int ordered_position\
    \ : boundary) {\n            layer_by_position[ordered_position] = layer;\n  \
    \          left_hull.erase(ordered_position);\n            right_hull.erase(distinct_count\
    \ - 1 - ordered_position);\n            remaining--;\n        }\n    }\n\n   \
    \ std::vector<int> result(n);\n    for (int index = 0; index < n; index++) {\n\
    \        result[index] = layer_by_position[position[index]];\n    }\n    return\
    \ result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_GEOMETRY_CONVEX_LAYERS_HPP\n"
  dependsOn:
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/convex_layers.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-13 20:32:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/convex_layers.test.cpp
documentation_of: geometry/convex_layers.hpp
layout: document
title: Convex Layers
---

## Overview

`convex_layers` computes the onion decomposition of a point set. Layer `1`
contains every point on the boundary of the original convex hull. After removing
that boundary, layer `2` contains the next convex-hull boundary, and so on until
no points remain.

The implementation maintains both sides of the convex hull under deletions with
segment-tree-shaped bridge structures. This is substantially faster than
rebuilding a convex hull for every layer when the input has many nested layers.

## Function

```cpp
template <Coordinate T>
std::vector<int> convex_layers(const std::vector<Point<T>>& points);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `convex_layers(points)` | Returns the 1-based removal layer of every point in original input order. Does not mutate `points`. | $O(N\log^2 N)$ time and $O(N)$ memory. |

All collinear points on a hull edge belong to the same layer. An empty input
returns an empty vector. Duplicate coordinates are allowed and receive the same
layer.

Integral calculations use `wide_type<T>`, which is signed 128-bit arithmetic.
Coordinate differences, cross products, and the bridge-comparison intermediate
products must fit that type. Floating-point coordinates use the geometry
module's default orientation tolerance.

## Example

```cpp
#include "geometry/convex_layers.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> points;
    points.emplace_back(0, 0);
    points.emplace_back(4, 0);
    points.emplace_back(4, 4);
    points.emplace_back(0, 4);
    points.emplace_back(2, 2);

    std::vector<int> layer = m1une::geometry::convex_layers(points);
    for (int value : layer) std::cout << value << "\n";
    // 1, 1, 1, 1, 2
}
```
