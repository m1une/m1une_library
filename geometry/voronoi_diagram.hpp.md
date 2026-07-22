---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: geometry/euclidean_mst.hpp
    title: Euclidean Minimum Spanning Tree
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
    path: verify/geometry/voronoi_diagram.test.cpp
    title: verify/geometry/voronoi_diagram.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/voronoi_diagram.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <cmath>\n#include <concepts>\n\
    #include <cstddef>\n#include <limits>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"geometry/euclidean_mst.hpp\"\n\n\n\n#line 10 \"\
    geometry/euclidean_mst.hpp\"\n#include <tuple>\n#line 13 \"geometry/euclidean_mst.hpp\"\
    \n\n#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#line 8 \"ds/dsu/dsu.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\nstruct Dsu {\n   private:\n    int _n;\n    // parent_or_size[i]\
    \ is the parent of i if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i]\
    \ is the size of the group.\n    std::vector<int> parent_or_size;\n\n    // Returns\
    \ {new leader, absorbed leader}. The absorbed leader is -1 when\n    // both vertices\
    \ already belong to the same component.\n    std::pair<int, int> merge_leaders(int\
    \ a, int b) {\n        int x = leader(a), y = leader(b);\n        if (x == y)\
    \ return {x, -1};\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return {x, y};\n    }\n\n   public:\n    Dsu() : _n(0) {}\n  \
    \  explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\n    // Merges the\
    \ group containing 'a' with the group containing 'b'.\n    // Returns the leader\
    \ of the merged group.\n    int merge(int a, int b) {\n        return merge_leaders(a,\
    \ b).first;\n    }\n\n    // Invokes callback(new_leader, absorbed_leader) after\
    \ an actual merge.\n    // Returns the leader of the merged group.\n    template\
    \ <class Callback>\n    int merge(int a, int b, Callback&& callback) {\n     \
    \   std::pair<int, int> merged = merge_leaders(a, b);\n        if (merged.second\
    \ != -1) callback(merged.first, merged.second);\n        return merged.first;\n\
    \    }\n\n    // Returns true if 'a' and 'b' belong to the same group.\n    bool\
    \ same(int a, int b) {\n        return leader(a) == leader(b);\n    }\n\n    //\
    \ Returns the leader (representative) of the group containing 'a'.\n    int leader(int\
    \ a) {\n        if (parent_or_size[a] < 0) return a;\n        // Path compression\n\
    \        return parent_or_size[a] = leader(parent_or_size[a]);\n    }\n\n    //\
    \ Returns the size of the group containing 'a'.\n    int size(int a) {\n     \
    \   return -parent_or_size[leader(a)];\n    }\n\n    // Returns a list of all\
    \ groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"geometry/point.hpp\"\n\n\n\n#line 7 \"geometry/point.hpp\"\
    \n#include <type_traits>\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate\
    \ <typename T>\nconcept Coordinate = std::is_arithmetic_v<T> && !std::same_as<std::remove_cv_t<T>,\
    \ bool>;\n\ntemplate <Coordinate T>\nusing wide_type = std::conditional_t<std::integral<T>,\
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
    \ geometry\n}  // namespace m1une\n\n\n#line 16 \"geometry/euclidean_mst.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\ntemplate <class T>\nstruct EuclideanMstEdge\
    \ {\n    int from;\n    int to;\n    T squared_distance;\n};\n\ntemplate <class\
    \ T>\nstruct EuclideanMst {\n    long double cost;\n    std::vector<EuclideanMstEdge<T>>\
    \ edges;\n};\n\nnamespace detail {\n\ntemplate <std::integral T>\nclass EuclideanDelaunay\
    \ {\n   private:\n    using W = wide_type<T>;\n\n    struct InternalPoint {\n\
    \        W x;\n        W y;\n\n        friend bool operator==(const InternalPoint&,\
    \ const InternalPoint&) = default;\n    };\n\n    struct Edge {\n        int to;\n\
    \        int ccw;\n        int cw;\n        int reverse;\n        bool enabled\
    \ = false;\n    };\n\n    std::vector<int> open_addresses;\n    std::vector<InternalPoint>\
    \ points;\n    std::vector<Edge> edges;\n    std::vector<int> duplicate_representative;\n\
    \n    static InternalPoint subtract(const InternalPoint& a, const InternalPoint&\
    \ b) {\n        return InternalPoint{a.x - b.x, a.y - b.y};\n    }\n\n    static\
    \ W cross_product(const InternalPoint& a, const InternalPoint& b) {\n        return\
    \ a.x * b.y - a.y * b.x;\n    }\n\n    static W squared_norm(const InternalPoint&\
    \ point) {\n        return point.x * point.x + point.y * point.y;\n    }\n\n \
    \   static bool inside_circumcircle(\n        InternalPoint a,\n        InternalPoint\
    \ b,\n        InternalPoint c,\n        const InternalPoint& d\n    ) {\n    \
    \    a = subtract(a, d);\n        b = subtract(b, d);\n        c = subtract(c,\
    \ d);\n        W determinant = cross_product(b, c) * squared_norm(a)\n       \
    \               + cross_product(c, a) * squared_norm(b)\n                    \
    \  + cross_product(a, b) * squared_norm(c);\n        return determinant > 0;\n\
    \    }\n\n    int get_open_address() {\n        if (open_addresses.empty()) {\n\
    \            edges.push_back(Edge());\n            return int(edges.size()) -\
    \ 1;\n        }\n        int result = open_addresses.back();\n        open_addresses.pop_back();\n\
    \        return result;\n    }\n\n    std::pair<int, int> add_edge(int from, int\
    \ to) {\n        int forward = get_open_address();\n        int backward = get_open_address();\n\
    \        edges[forward].to = to;\n        edges[forward].ccw = forward;\n    \
    \    edges[forward].cw = forward;\n        edges[forward].reverse = backward;\n\
    \        edges[forward].enabled = true;\n        edges[backward].to = from;\n\
    \        edges[backward].ccw = backward;\n        edges[backward].cw = backward;\n\
    \        edges[backward].reverse = forward;\n        edges[backward].enabled =\
    \ true;\n        return {forward, backward};\n    }\n\n    void erase_directed_edge(int\
    \ edge) {\n        int ccw = edges[edge].ccw;\n        int cw = edges[edge].cw;\n\
    \        edges[ccw].cw = cw;\n        edges[cw].ccw = ccw;\n        edges[edge].enabled\
    \ = false;\n    }\n\n    void erase_edge(int edge) {\n        int reverse = edges[edge].reverse;\n\
    \        erase_directed_edge(edge);\n        erase_directed_edge(reverse);\n \
    \       open_addresses.push_back(edge);\n        open_addresses.push_back(reverse);\n\
    \    }\n\n    void insert_ccw_after(int edge, int position) {\n        int next\
    \ = edges[position].ccw;\n        edges[edge].ccw = next;\n        edges[next].cw\
    \ = edge;\n        edges[edge].cw = position;\n        edges[position].ccw = edge;\n\
    \    }\n\n    void insert_cw_after(int edge, int position) {\n        int next\
    \ = edges[position].cw;\n        edges[edge].cw = next;\n        edges[next].ccw\
    \ = edge;\n        edges[edge].ccw = position;\n        edges[position].cw = edge;\n\
    \    }\n\n    int orientation(int a, int b, int c) const {\n        InternalPoint\
    \ ab = subtract(points[b], points[a]);\n        InternalPoint ac = subtract(points[c],\
    \ points[a]);\n        W value = cross_product(ab, ac);\n        return (value\
    \ > 0) - (value < 0);\n    }\n\n    std::pair<int, int> go_next(int edge) const\
    \ {\n        int vertex = edges[edge].to;\n        int next_edge = edges[edges[edge].reverse].ccw;\n\
    \        return {vertex, next_edge};\n    }\n\n    std::pair<int, int> go_previous(int\
    \ edge) const {\n        int vertex = edges[edges[edge].cw].to;\n        int next_edge\
    \ = edges[edges[edge].cw].reverse;\n        return {vertex, next_edge};\n    }\n\
    \n    std::tuple<int, int, int, int> lower_tangent(\n        int left_vertex,\n\
    \        int left_edge,\n        int right_vertex,\n        int right_edge\n \
    \   ) const {\n        while (true) {\n            auto [next_left_vertex, next_left_edge]\
    \ = go_previous(left_edge);\n            if (orientation(right_vertex, left_vertex,\
    \ next_left_vertex) > 0) {\n                left_vertex = next_left_vertex;\n\
    \                left_edge = next_left_edge;\n                continue;\n    \
    \        }\n            auto [next_right_vertex, next_right_edge] = go_next(right_edge);\n\
    \            if (orientation(left_vertex, right_vertex, next_right_vertex) < 0)\
    \ {\n                right_vertex = next_right_vertex;\n                right_edge\
    \ = next_right_edge;\n                continue;\n            }\n            break;\n\
    \        }\n        return {left_vertex, left_edge, right_vertex, right_edge};\n\
    \    }\n\n    std::pair<int, int> extreme_vertex(int vertex, int edge, bool minimum)\
    \ const {\n        std::pair<int, int> result = {vertex, edge};\n        int current_vertex\
    \ = vertex;\n        int current_edge = edge;\n        do {\n            std::tie(current_vertex,\
    \ current_edge) = go_next(current_edge);\n            std::pair<int, int> candidate\
    \ = {current_vertex, current_edge};\n            if ((minimum && candidate < result)\
    \ || (!minimum && result < candidate)) {\n                result = candidate;\n\
    \            }\n        } while (current_edge != edge);\n        return result;\n\
    \    }\n\n    bool inside_circumcircle(int a, int b, int c, int d) const {\n \
    \       return inside_circumcircle(points[a], points[b], points[c], points[d]);\n\
    \    }\n\n    std::pair<int, int> merge_triangulations(\n        int left_vertex,\n\
    \        int left_edge,\n        int right_vertex,\n        int right_edge\n \
    \   ) {\n        std::tie(left_vertex, left_edge) = extreme_vertex(left_vertex,\
    \ left_edge, false);\n        std::tie(right_vertex, right_edge) = extreme_vertex(right_vertex,\
    \ right_edge, true);\n\n        auto [lower_left, lower_left_edge, lower_right,\
    \ lower_right_edge]\n            = lower_tangent(left_vertex, left_edge, right_vertex,\
    \ right_edge);\n        auto [upper_right, upper_right_edge, upper_left, upper_left_edge]\n\
    \            = lower_tangent(right_vertex, right_edge, left_vertex, left_edge);\n\
    \        lower_right_edge = edges[lower_right_edge].cw;\n        upper_right_edge\
    \ = edges[upper_right_edge].cw;\n\n        auto [base, reverse_base] = add_edge(lower_left,\
    \ lower_right);\n        insert_cw_after(base, lower_left_edge);\n        insert_ccw_after(reverse_base,\
    \ lower_right_edge);\n        if (lower_left == upper_left) upper_left_edge =\
    \ base;\n        if (lower_right == upper_right) upper_right_edge = reverse_base;\n\
    \n        int left = lower_left;\n        int left_candidate = lower_left_edge;\n\
    \        int right = lower_right;\n        int right_candidate = lower_right_edge;\n\
    \        while (left != upper_left || right != upper_right) {\n            int\
    \ next_left = edges[left_candidate].to;\n            int next_right = edges[right_candidate].to;\n\
    \            int next_left_candidate = edges[left_candidate].ccw;\n          \
    \  int next_right_candidate = edges[right_candidate].cw;\n\n            if (left_candidate\
    \ != upper_left_edge && next_left_candidate != base) {\n                int second_left\
    \ = edges[next_left_candidate].to;\n                if (inside_circumcircle(left,\
    \ right, next_left, second_left)) {\n                    erase_edge(left_candidate);\n\
    \                    left_candidate = next_left_candidate;\n                 \
    \   continue;\n                }\n            }\n\n            if (right_candidate\
    \ != upper_right_edge && next_right_candidate != reverse_base) {\n           \
    \     int second_right = edges[next_right_candidate].to;\n                if (inside_circumcircle(next_right,\
    \ left, right, second_right)) {\n                    erase_edge(right_candidate);\n\
    \                    right_candidate = next_right_candidate;\n               \
    \     continue;\n                }\n            }\n\n            bool choose_left\
    \ = right_candidate == upper_right_edge;\n            if (left_candidate != upper_left_edge\
    \ && right_candidate != upper_right_edge) {\n                if (orientation(left,\
    \ right, next_right) < 0) {\n                    choose_left = true;\n       \
    \         } else if (orientation(next_left, left, right) < 0) {\n            \
    \        choose_left = false;\n                } else {\n                    choose_left\
    \ = inside_circumcircle(left, right, next_right, next_left);\n               \
    \ }\n            }\n\n            if (choose_left) {\n                next_left_candidate\
    \ = edges[edges[left_candidate].reverse].ccw;\n                auto [new_base,\
    \ new_reverse_base] = add_edge(next_left, right);\n                insert_cw_after(new_base,\
    \ next_left_candidate);\n                insert_ccw_after(new_reverse_base, right_candidate);\n\
    \                left_candidate = next_left_candidate;\n                left =\
    \ next_left;\n            } else {\n                next_right_candidate = edges[edges[right_candidate].reverse].cw;\n\
    \                auto [new_reverse_base, new_base] = add_edge(next_right, left);\n\
    \                insert_ccw_after(new_reverse_base, next_right_candidate);\n \
    \               insert_cw_after(new_base, left_candidate);\n                right_candidate\
    \ = next_right_candidate;\n                right = next_right;\n            }\n\
    \        }\n        return {lower_left, base};\n    }\n\n    std::pair<int, int>\
    \ solve_range(int left, int right) {\n        if (right - left == 2) {\n     \
    \       auto [forward, backward] = add_edge(left, left + 1);\n            (void)backward;\n\
    \            return {left, forward};\n        }\n        if (right - left == 3)\
    \ {\n            int middle = left + 1;\n            int last = left + 2;\n  \
    \          auto [first_middle, middle_first] = add_edge(left, middle);\n     \
    \       auto [middle_last, last_middle] = add_edge(middle, last);\n          \
    \  int direction = orientation(left, middle, last);\n            if (direction\
    \ == 0) {\n                insert_ccw_after(middle_first, middle_last);\n    \
    \            return {left, first_middle};\n            }\n\n            auto [first_last,\
    \ last_first] = add_edge(left, last);\n            if (direction > 0) {\n    \
    \            insert_cw_after(first_middle, first_last);\n                insert_cw_after(middle_last,\
    \ middle_first);\n                insert_cw_after(last_first, last_middle);\n\
    \                return {left, first_middle};\n            }\n            insert_ccw_after(first_middle,\
    \ first_last);\n            insert_ccw_after(middle_last, middle_first);\n   \
    \         insert_ccw_after(last_first, last_middle);\n            return {middle,\
    \ middle_first};\n        }\n\n        int middle = (left + right) / 2;\n    \
    \    auto [left_vertex, left_edge] = solve_range(left, middle);\n        auto\
    \ [right_vertex, right_edge] = solve_range(middle, right);\n        return merge_triangulations(left_vertex,\
    \ left_edge, right_vertex, right_edge);\n    }\n\n    void solve() {\n       \
    \ int size = int(points.size());\n        if (size <= 1) return;\n\n        std::vector<int>\
    \ order(size);\n        for (int i = 0; i < size; i++) order[i] = i;\n       \
    \ std::stable_sort(order.begin(), order.end(), [&](int left, int right) {\n  \
    \          if (points[left].x != points[right].x) {\n                return points[left].x\
    \ < points[right].x;\n            }\n            return points[left].y < points[right].y;\n\
    \        });\n\n        std::vector<InternalPoint> original_points = points;\n\
    \        duplicate_representative.assign(size, 0);\n        int unique_size =\
    \ 0;\n        for (int i = 0; i < size; i++) {\n            int vertex = order[i];\n\
    \            if (i == 0 || !(original_points[order[unique_size - 1]] == original_points[vertex]))\
    \ {\n                order[unique_size] = vertex;\n                points[unique_size]\
    \ = original_points[vertex];\n                unique_size++;\n               \
    \ duplicate_representative[vertex] = vertex;\n            } else {\n         \
    \       duplicate_representative[vertex] = order[unique_size - 1];\n         \
    \   }\n        }\n\n        if (unique_size >= 2) solve_range(0, unique_size);\n\
    \        points.swap(original_points);\n        for (auto& edge : edges) edge.to\
    \ = order[edge.to];\n    }\n\n   public:\n    explicit EuclideanDelaunay(const\
    \ std::vector<Point<T>>& input_points) {\n        assert(input_points.size() <=\
    \ std::size_t(std::numeric_limits<int>::max()));\n        points.reserve(input_points.size());\n\
    \        edges.reserve(std::size_t(6) * input_points.size());\n        for (const\
    \ auto& point : input_points) {\n            points.push_back(InternalPoint{W(point.x),\
    \ W(point.y)});\n        }\n        solve();\n    }\n\n    bool has_duplicates()\
    \ const {\n        for (\n            int vertex = 0;\n            vertex < int(duplicate_representative.size());\n\
    \            ++vertex\n        ) {\n            if (duplicate_representative[vertex]\
    \ != vertex) return true;\n        }\n        return false;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> get_edges() const {\n        std::vector<std::pair<int, int>> result;\n\
    \        result.reserve(edges.size() / 2 + duplicate_representative.size());\n\
    \        for (int edge = 0; edge < int(edges.size()); edge++) {\n            if\
    \ (!edges[edge].enabled) continue;\n            int reverse = edges[edge].reverse;\n\
    \            if (edge < reverse) continue;\n            result.emplace_back(edges[edge].to,\
    \ edges[reverse].to);\n        }\n        for (int vertex = 0; vertex < int(duplicate_representative.size());\
    \ vertex++) {\n            if (duplicate_representative[vertex] != vertex) {\n\
    \                result.emplace_back(vertex, duplicate_representative[vertex]);\n\
    \            }\n        }\n        return result;\n    }\n};\n\n}  // namespace\
    \ detail\n\n// Returns O(n) Delaunay edges containing a Euclidean minimum spanning\
    \ tree.\ntemplate <std::integral T>\nstd::vector<EuclideanMstEdge<wide_type<T>>>\
    \ euclidean_mst_edges(\n    const std::vector<Point<T>>& points\n) {\n    using\
    \ W = wide_type<T>;\n    auto delaunay_edges = detail::EuclideanDelaunay<T>(points).get_edges();\n\
    \    std::vector<EuclideanMstEdge<W>> result;\n    result.reserve(delaunay_edges.size());\n\
    \    for (auto [from, to] : delaunay_edges) {\n        result.push_back(EuclideanMstEdge<W>{from,\
    \ to, distance2(points[from], points[to])});\n    }\n    return result;\n}\n\n\
    // Returns a Euclidean minimum spanning tree.\ntemplate <std::integral T>\nEuclideanMst<wide_type<T>>\
    \ euclidean_mst(const std::vector<Point<T>>& points) {\n    using W = wide_type<T>;\n\
    \    auto candidates = euclidean_mst_edges(points);\n    std::sort(candidates.begin(),\
    \ candidates.end(), [](const auto& left, const auto& right) {\n        if (left.squared_distance\
    \ != right.squared_distance) {\n            return left.squared_distance < right.squared_distance;\n\
    \        }\n        if (left.from != right.from) return left.from < right.from;\n\
    \        return left.to < right.to;\n    });\n\n    m1une::ds::Dsu dsu(int(points.size()));\n\
    \    EuclideanMst<W> result;\n    result.cost = 0;\n    result.edges.reserve(points.empty()\
    \ ? 0 : points.size() - 1);\n    for (const auto& edge : candidates) {\n     \
    \   if (dsu.same(edge.from, edge.to)) continue;\n        dsu.merge(edge.from,\
    \ edge.to);\n        result.cost += std::sqrt(static_cast<long double>(edge.squared_distance));\n\
    \        result.edges.push_back(edge);\n        if (result.edges.size() + 1 ==\
    \ points.size()) break;\n    }\n    assert(points.empty() || result.edges.size()\
    \ + 1 == points.size());\n    return result;\n}\n\n}  // namespace geometry\n\
    }  // namespace m1une\n\n\n#line 16 \"geometry/voronoi_diagram.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\nenum class VoronoiEdgeKind {\n    Segment,\n\
    \    Ray,\n    Line,\n};\n\nstruct VoronoiEdge {\n    VoronoiEdgeKind kind;\n\
    \    int first_site;\n    int second_site;\n    int first_vertex;\n    int second_vertex;\n\
    \    Point<long double> point;\n    Point<long double> direction;\n};\n\nstruct\
    \ VoronoiDiagram {\n    std::vector<Point<long double>> vertices;\n    std::vector<VoronoiEdge>\
    \ edges;\n    std::vector<std::vector<int>> cell_edges;\n};\n\nnamespace voronoi_diagram_detail\
    \ {\n\ntemplate <std::integral T>\nint direction_half(\n    const Point<T>& origin,\n\
    \    const Point<T>& destination\n) {\n    using W = wide_type<T>;\n    W x =\
    \ W(destination.x) - W(origin.x);\n    W y = W(destination.y) - W(origin.y);\n\
    \    return y > 0 || (y == 0 && x >= 0) ? 0 : 1;\n}\n\ntemplate <std::integral\
    \ T>\nbool direction_less(\n    const std::vector<Point<T>>& sites,\n    int origin,\n\
    \    int first,\n    int second\n) {\n    int first_half = direction_half(sites[origin],\
    \ sites[first]);\n    int second_half = direction_half(sites[origin], sites[second]);\n\
    \    if (first_half != second_half) return first_half < second_half;\n\n    using\
    \ W = wide_type<T>;\n    W first_x = W(sites[first].x) - W(sites[origin].x);\n\
    \    W first_y = W(sites[first].y) - W(sites[origin].y);\n    W second_x = W(sites[second].x)\
    \ - W(sites[origin].x);\n    W second_y = W(sites[second].y) - W(sites[origin].y);\n\
    \    W product = first_x * second_y - first_y * second_x;\n    if (product !=\
    \ 0) return product > 0;\n\n    W first_norm = first_x * first_x + first_y * first_y;\n\
    \    W second_norm = second_x * second_x + second_y * second_y;\n    if (first_norm\
    \ != second_norm) return first_norm < second_norm;\n    return first < second;\n\
    }\n\ntemplate <std::integral T>\nbool cocircular(\n    const Point<T>& first,\n\
    \    const Point<T>& second,\n    const Point<T>& third,\n    const Point<T>&\
    \ fourth\n) {\n    using W = wide_type<T>;\n    W ax = W(first.x) - W(fourth.x);\n\
    \    W ay = W(first.y) - W(fourth.y);\n    W bx = W(second.x) - W(fourth.x);\n\
    \    W by = W(second.y) - W(fourth.y);\n    W cx = W(third.x) - W(fourth.x);\n\
    \    W cy = W(third.y) - W(fourth.y);\n    W a_norm = ax * ax + ay * ay;\n   \
    \ W b_norm = bx * bx + by * by;\n    W c_norm = cx * cx + cy * cy;\n    W determinant\
    \ =\n        (bx * cy - by * cx) * a_norm +\n        (cx * ay - cy * ax) * b_norm\
    \ +\n        (ax * by - ay * bx) * c_norm;\n    return determinant == 0;\n}\n\n\
    template <std::integral T>\nPoint<long double> circumcenter(\n    const Point<T>&\
    \ first,\n    const Point<T>& second,\n    const Point<T>& third\n) {\n    long\
    \ double ax = static_cast<long double>(first.x);\n    long double ay = static_cast<long\
    \ double>(first.y);\n    long double bx = static_cast<long double>(second.x);\n\
    \    long double by = static_cast<long double>(second.y);\n    long double cx\
    \ = static_cast<long double>(third.x);\n    long double cy = static_cast<long\
    \ double>(third.y);\n    long double denominator = 2 * (\n        ax * (by - cy)\
    \ +\n        bx * (cy - ay) +\n        cx * (ay - by)\n    );\n    assert(denominator\
    \ != 0);\n    long double first_norm = ax * ax + ay * ay;\n    long double second_norm\
    \ = bx * bx + by * by;\n    long double third_norm = cx * cx + cy * cy;\n    return\
    \ Point<long double>(\n        (first_norm * (by - cy) +\n         second_norm\
    \ * (cy - ay) +\n         third_norm * (ay - by)) /\n            denominator,\n\
    \        (first_norm * (cx - bx) +\n         second_norm * (ax - cx) +\n     \
    \    third_norm * (bx - ax)) /\n            denominator\n    );\n}\n\ninline Point<long\
    \ double> unit(Point<long double> direction) {\n    long double length = norm(direction);\n\
    \    assert(length != 0);\n    return direction / length;\n}\n\ninline int other_site(const\
    \ VoronoiEdge& edge, int site) {\n    assert(edge.first_site == site || edge.second_site\
    \ == site);\n    return edge.first_site == site ? edge.second_site : edge.first_site;\n\
    }\n\n}  // namespace voronoi_diagram_detail\n\n// Constructs the ordinary Euclidean\
    \ Voronoi diagram of distinct integral sites.\ntemplate <std::integral T>\nVoronoiDiagram\
    \ voronoi_diagram(const std::vector<Point<T>>& sites) {\n    namespace detail\
    \ = voronoi_diagram_detail;\n    assert(sites.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n    const int size = int(sites.size());\n    std::vector<int> site_order(size);\n\
    \    std::iota(site_order.begin(), site_order.end(), 0);\n    std::sort(site_order.begin(),\
    \ site_order.end(), [&](int first, int second) {\n        return sites[first]\
    \ < sites[second];\n    });\n    for (int index = 1; index < size; ++index) {\n\
    \        assert(sites[site_order[index - 1]] != sites[site_order[index]]);\n \
    \   }\n\n    std::vector<std::pair<int, int>> delaunay_edges =\n        geometry::detail::EuclideanDelaunay<T>(sites).get_edges();\n\
    \    for (auto& [first, second] : delaunay_edges) {\n        if (first > second)\
    \ std::swap(first, second);\n    }\n    std::sort(delaunay_edges.begin(), delaunay_edges.end());\n\
    \    delaunay_edges.erase(\n        std::unique(delaunay_edges.begin(), delaunay_edges.end()),\n\
    \        delaunay_edges.end()\n    );\n\n    auto find_edge_index = [&](int first,\
    \ int second) {\n        if (first > second) std::swap(first, second);\n     \
    \   auto iterator = std::lower_bound(\n            delaunay_edges.begin(),\n \
    \           delaunay_edges.end(),\n            std::pair(first, second)\n    \
    \    );\n        if (\n            iterator == delaunay_edges.end() ||\n     \
    \       *iterator != std::pair(first, second)\n        ) {\n            return\
    \ -1;\n        }\n        return int(iterator - delaunay_edges.begin());\n   \
    \ };\n    std::vector<std::vector<int>> neighbors(size);\n    for (int index =\
    \ 0; index < int(delaunay_edges.size()); ++index) {\n        auto [first, second]\
    \ = delaunay_edges[index];\n        neighbors[first].push_back(second);\n    \
    \    neighbors[second].push_back(first);\n    }\n    for (int site = 0; site <\
    \ size; ++site) {\n        std::sort(\n            neighbors[site].begin(),\n\
    \            neighbors[site].end(),\n            [&](int first, int second) {\n\
    \                return detail::direction_less(sites, site, first, second);\n\
    \            }\n        );\n    }\n\n    std::vector<std::array<int, 3>> triangles;\n\
    \    for (int site = 0; site < size; ++site) {\n        int degree = int(neighbors[site].size());\n\
    \        for (int index = 0; index < degree; ++index) {\n            int first\
    \ = neighbors[site][index];\n            int second = neighbors[site][(index +\
    \ 1) % degree];\n            if (orientation(sites[site], sites[first], sites[second])\
    \ <= 0) {\n                continue;\n            }\n            if (find_edge_index(first,\
    \ second) == -1) continue;\n            std::array<int, 3> triangle{site, first,\
    \ second};\n            std::sort(triangle.begin(), triangle.end());\n       \
    \     triangles.push_back(triangle);\n        }\n    }\n    std::sort(triangles.begin(),\
    \ triangles.end());\n    triangles.erase(\n        std::unique(triangles.begin(),\
    \ triangles.end()),\n        triangles.end()\n    );\n    for (auto& triangle\
    \ : triangles) {\n        if (orientation(\n                sites[triangle[0]],\n\
    \                sites[triangle[1]],\n                sites[triangle[2]]\n   \
    \         ) < 0) {\n            std::swap(triangle[1], triangle[2]);\n       \
    \ }\n    }\n\n    std::vector<std::array<int, 2>> incident_triangles(\n      \
    \  delaunay_edges.size(),\n        std::array<int, 2>{-1, -1}\n    );\n    std::vector<int>\
    \ incident_count(delaunay_edges.size(), 0);\n    for (int triangle = 0; triangle\
    \ < int(triangles.size()); ++triangle) {\n        for (int side = 0; side < 3;\
    \ ++side) {\n            int first = triangles[triangle][side];\n            int\
    \ second = triangles[triangle][(side + 1) % 3];\n            int edge = find_edge_index(first,\
    \ second);\n            assert(edge != -1);\n            assert(incident_count[edge]\
    \ < 2);\n            incident_triangles[edge][incident_count[edge]++] = triangle;\n\
    \        }\n    }\n\n    std::vector<int> parent(triangles.size());\n    std::vector<int>\
    \ component_size(triangles.size(), 1);\n    std::iota(parent.begin(), parent.end(),\
    \ 0);\n    auto find_root = [&](auto&& self, int vertex) -> int {\n        if\
    \ (parent[vertex] == vertex) return vertex;\n        return parent[vertex] = self(self,\
    \ parent[vertex]);\n    };\n    auto merge = [&](int first, int second) {\n  \
    \      first = find_root(find_root, first);\n        second = find_root(find_root,\
    \ second);\n        if (first == second) return;\n        if (component_size[first]\
    \ < component_size[second]) {\n            std::swap(first, second);\n       \
    \ }\n        parent[second] = first;\n        component_size[first] += component_size[second];\n\
    \    };\n    for (int edge = 0; edge < int(delaunay_edges.size()); ++edge) {\n\
    \        if (incident_count[edge] != 2) continue;\n        int first_triangle\
    \ = incident_triangles[edge][0];\n        int second_triangle = incident_triangles[edge][1];\n\
    \        const auto& first = triangles[first_triangle];\n        const auto& second\
    \ = triangles[second_triangle];\n        int fourth = second[0];\n        if (fourth\
    \ == first[0] || fourth == first[1] || fourth == first[2]) {\n            fourth\
    \ = second[1];\n        }\n        if (fourth == first[0] || fourth == first[1]\
    \ || fourth == first[2]) {\n            fourth = second[2];\n        }\n     \
    \   assert(\n            fourth != first[0] &&\n            fourth != first[1]\
    \ &&\n            fourth != first[2]\n        );\n        if (detail::cocircular(\n\
    \                sites[first[0]],\n                sites[first[1]],\n        \
    \        sites[first[2]],\n                sites[fourth]\n            )) {\n \
    \           merge(first_triangle, second_triangle);\n        }\n    }\n\n    VoronoiDiagram\
    \ result;\n    result.cell_edges.resize(size);\n    std::vector<int> root_vertex(triangles.size(),\
    \ -1);\n    std::vector<int> triangle_vertex(triangles.size(), -1);\n    for (int\
    \ triangle = 0; triangle < int(triangles.size()); ++triangle) {\n        int root\
    \ = find_root(find_root, triangle);\n        if (root_vertex[root] == -1) {\n\
    \            const auto& sites_on_circle = triangles[triangle];\n            root_vertex[root]\
    \ = int(result.vertices.size());\n            result.vertices.push_back(detail::circumcenter(\n\
    \                sites[sites_on_circle[0]],\n                sites[sites_on_circle[1]],\n\
    \                sites[sites_on_circle[2]]\n            ));\n        }\n     \
    \   triangle_vertex[triangle] = root_vertex[root];\n    }\n\n    result.edges.reserve(delaunay_edges.size());\n\
    \    for (int edge = 0; edge < int(delaunay_edges.size()); ++edge) {\n       \
    \ auto [first_site, second_site] = delaunay_edges[edge];\n        VoronoiEdge\
    \ voronoi_edge;\n        voronoi_edge.first_site = first_site;\n        voronoi_edge.second_site\
    \ = second_site;\n        voronoi_edge.first_vertex = -1;\n        voronoi_edge.second_vertex\
    \ = -1;\n\n        if (incident_count[edge] == 2) {\n            int first_vertex\
    \ =\n                triangle_vertex[incident_triangles[edge][0]];\n         \
    \   int second_vertex =\n                triangle_vertex[incident_triangles[edge][1]];\n\
    \            if (first_vertex == second_vertex) continue;\n            if (first_vertex\
    \ > second_vertex) {\n                std::swap(first_vertex, second_vertex);\n\
    \            }\n            voronoi_edge.kind = VoronoiEdgeKind::Segment;\n  \
    \          voronoi_edge.first_vertex = first_vertex;\n            voronoi_edge.second_vertex\
    \ = second_vertex;\n            voronoi_edge.point = result.vertices[first_vertex];\n\
    \            voronoi_edge.direction =\n                result.vertices[second_vertex]\
    \ - result.vertices[first_vertex];\n        } else if (incident_count[edge] ==\
    \ 1) {\n            int triangle = incident_triangles[edge][0];\n            int\
    \ third_site = triangles[triangle][0];\n            if (third_site == first_site\
    \ || third_site == second_site) {\n                third_site = triangles[triangle][1];\n\
    \            }\n            if (third_site == first_site || third_site == second_site)\
    \ {\n                third_site = triangles[triangle][2];\n            }\n   \
    \         assert(third_site != first_site && third_site != second_site);\n\n \
    \           Point<long double> first(sites[first_site]);\n            Point<long\
    \ double> second(sites[second_site]);\n            Point<long double> edge_direction\
    \ = second - first;\n            Point<long double> outward;\n            if (orientation(\n\
    \                    sites[first_site],\n                    sites[second_site],\n\
    \                    sites[third_site]\n                ) > 0) {\n           \
    \     outward = Point<long double>(\n                    edge_direction.y,\n \
    \                   -edge_direction.x\n                );\n            } else\
    \ {\n                outward = Point<long double>(\n                    -edge_direction.y,\n\
    \                    edge_direction.x\n                );\n            }\n   \
    \         voronoi_edge.kind = VoronoiEdgeKind::Ray;\n            voronoi_edge.first_vertex\
    \ = triangle_vertex[triangle];\n            voronoi_edge.point = result.vertices[voronoi_edge.first_vertex];\n\
    \            voronoi_edge.direction = detail::unit(outward);\n        } else {\n\
    \            assert(incident_count[edge] == 0);\n            Point<long double>\
    \ first(sites[first_site]);\n            Point<long double> second(sites[second_site]);\n\
    \            Point<long double> edge_direction = second - first;\n           \
    \ voronoi_edge.kind = VoronoiEdgeKind::Line;\n            voronoi_edge.point =\
    \ (first + second) / 2.0L;\n            voronoi_edge.direction = detail::unit(Point<long\
    \ double>(\n                edge_direction.y,\n                -edge_direction.x\n\
    \            ));\n        }\n\n        int voronoi_edge_index = int(result.edges.size());\n\
    \        result.edges.push_back(voronoi_edge);\n        result.cell_edges[first_site].push_back(voronoi_edge_index);\n\
    \        result.cell_edges[second_site].push_back(voronoi_edge_index);\n    }\n\
    \n    for (int site = 0; site < size; ++site) {\n        std::sort(\n        \
    \    result.cell_edges[site].begin(),\n            result.cell_edges[site].end(),\n\
    \            [&](int first_edge, int second_edge) {\n                int first_other\
    \ =\n                    detail::other_site(result.edges[first_edge], site);\n\
    \                int second_other =\n                    detail::other_site(result.edges[second_edge],\
    \ site);\n                return detail::direction_less(\n                   \
    \ sites,\n                    site,\n                    first_other,\n      \
    \              second_other\n                );\n            }\n        );\n \
    \   }\n    return result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_GEOMETRY_VORONOI_DIAGRAM_HPP\n#define M1UNE_GEOMETRY_VORONOI_DIAGRAM_HPP\
    \ 1\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <concepts>\n#include <cstddef>\n#include <limits>\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\n#include \"euclidean_mst.hpp\"\n\nnamespace\
    \ m1une {\nnamespace geometry {\n\nenum class VoronoiEdgeKind {\n    Segment,\n\
    \    Ray,\n    Line,\n};\n\nstruct VoronoiEdge {\n    VoronoiEdgeKind kind;\n\
    \    int first_site;\n    int second_site;\n    int first_vertex;\n    int second_vertex;\n\
    \    Point<long double> point;\n    Point<long double> direction;\n};\n\nstruct\
    \ VoronoiDiagram {\n    std::vector<Point<long double>> vertices;\n    std::vector<VoronoiEdge>\
    \ edges;\n    std::vector<std::vector<int>> cell_edges;\n};\n\nnamespace voronoi_diagram_detail\
    \ {\n\ntemplate <std::integral T>\nint direction_half(\n    const Point<T>& origin,\n\
    \    const Point<T>& destination\n) {\n    using W = wide_type<T>;\n    W x =\
    \ W(destination.x) - W(origin.x);\n    W y = W(destination.y) - W(origin.y);\n\
    \    return y > 0 || (y == 0 && x >= 0) ? 0 : 1;\n}\n\ntemplate <std::integral\
    \ T>\nbool direction_less(\n    const std::vector<Point<T>>& sites,\n    int origin,\n\
    \    int first,\n    int second\n) {\n    int first_half = direction_half(sites[origin],\
    \ sites[first]);\n    int second_half = direction_half(sites[origin], sites[second]);\n\
    \    if (first_half != second_half) return first_half < second_half;\n\n    using\
    \ W = wide_type<T>;\n    W first_x = W(sites[first].x) - W(sites[origin].x);\n\
    \    W first_y = W(sites[first].y) - W(sites[origin].y);\n    W second_x = W(sites[second].x)\
    \ - W(sites[origin].x);\n    W second_y = W(sites[second].y) - W(sites[origin].y);\n\
    \    W product = first_x * second_y - first_y * second_x;\n    if (product !=\
    \ 0) return product > 0;\n\n    W first_norm = first_x * first_x + first_y * first_y;\n\
    \    W second_norm = second_x * second_x + second_y * second_y;\n    if (first_norm\
    \ != second_norm) return first_norm < second_norm;\n    return first < second;\n\
    }\n\ntemplate <std::integral T>\nbool cocircular(\n    const Point<T>& first,\n\
    \    const Point<T>& second,\n    const Point<T>& third,\n    const Point<T>&\
    \ fourth\n) {\n    using W = wide_type<T>;\n    W ax = W(first.x) - W(fourth.x);\n\
    \    W ay = W(first.y) - W(fourth.y);\n    W bx = W(second.x) - W(fourth.x);\n\
    \    W by = W(second.y) - W(fourth.y);\n    W cx = W(third.x) - W(fourth.x);\n\
    \    W cy = W(third.y) - W(fourth.y);\n    W a_norm = ax * ax + ay * ay;\n   \
    \ W b_norm = bx * bx + by * by;\n    W c_norm = cx * cx + cy * cy;\n    W determinant\
    \ =\n        (bx * cy - by * cx) * a_norm +\n        (cx * ay - cy * ax) * b_norm\
    \ +\n        (ax * by - ay * bx) * c_norm;\n    return determinant == 0;\n}\n\n\
    template <std::integral T>\nPoint<long double> circumcenter(\n    const Point<T>&\
    \ first,\n    const Point<T>& second,\n    const Point<T>& third\n) {\n    long\
    \ double ax = static_cast<long double>(first.x);\n    long double ay = static_cast<long\
    \ double>(first.y);\n    long double bx = static_cast<long double>(second.x);\n\
    \    long double by = static_cast<long double>(second.y);\n    long double cx\
    \ = static_cast<long double>(third.x);\n    long double cy = static_cast<long\
    \ double>(third.y);\n    long double denominator = 2 * (\n        ax * (by - cy)\
    \ +\n        bx * (cy - ay) +\n        cx * (ay - by)\n    );\n    assert(denominator\
    \ != 0);\n    long double first_norm = ax * ax + ay * ay;\n    long double second_norm\
    \ = bx * bx + by * by;\n    long double third_norm = cx * cx + cy * cy;\n    return\
    \ Point<long double>(\n        (first_norm * (by - cy) +\n         second_norm\
    \ * (cy - ay) +\n         third_norm * (ay - by)) /\n            denominator,\n\
    \        (first_norm * (cx - bx) +\n         second_norm * (ax - cx) +\n     \
    \    third_norm * (bx - ax)) /\n            denominator\n    );\n}\n\ninline Point<long\
    \ double> unit(Point<long double> direction) {\n    long double length = norm(direction);\n\
    \    assert(length != 0);\n    return direction / length;\n}\n\ninline int other_site(const\
    \ VoronoiEdge& edge, int site) {\n    assert(edge.first_site == site || edge.second_site\
    \ == site);\n    return edge.first_site == site ? edge.second_site : edge.first_site;\n\
    }\n\n}  // namespace voronoi_diagram_detail\n\n// Constructs the ordinary Euclidean\
    \ Voronoi diagram of distinct integral sites.\ntemplate <std::integral T>\nVoronoiDiagram\
    \ voronoi_diagram(const std::vector<Point<T>>& sites) {\n    namespace detail\
    \ = voronoi_diagram_detail;\n    assert(sites.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n    const int size = int(sites.size());\n    std::vector<int> site_order(size);\n\
    \    std::iota(site_order.begin(), site_order.end(), 0);\n    std::sort(site_order.begin(),\
    \ site_order.end(), [&](int first, int second) {\n        return sites[first]\
    \ < sites[second];\n    });\n    for (int index = 1; index < size; ++index) {\n\
    \        assert(sites[site_order[index - 1]] != sites[site_order[index]]);\n \
    \   }\n\n    std::vector<std::pair<int, int>> delaunay_edges =\n        geometry::detail::EuclideanDelaunay<T>(sites).get_edges();\n\
    \    for (auto& [first, second] : delaunay_edges) {\n        if (first > second)\
    \ std::swap(first, second);\n    }\n    std::sort(delaunay_edges.begin(), delaunay_edges.end());\n\
    \    delaunay_edges.erase(\n        std::unique(delaunay_edges.begin(), delaunay_edges.end()),\n\
    \        delaunay_edges.end()\n    );\n\n    auto find_edge_index = [&](int first,\
    \ int second) {\n        if (first > second) std::swap(first, second);\n     \
    \   auto iterator = std::lower_bound(\n            delaunay_edges.begin(),\n \
    \           delaunay_edges.end(),\n            std::pair(first, second)\n    \
    \    );\n        if (\n            iterator == delaunay_edges.end() ||\n     \
    \       *iterator != std::pair(first, second)\n        ) {\n            return\
    \ -1;\n        }\n        return int(iterator - delaunay_edges.begin());\n   \
    \ };\n    std::vector<std::vector<int>> neighbors(size);\n    for (int index =\
    \ 0; index < int(delaunay_edges.size()); ++index) {\n        auto [first, second]\
    \ = delaunay_edges[index];\n        neighbors[first].push_back(second);\n    \
    \    neighbors[second].push_back(first);\n    }\n    for (int site = 0; site <\
    \ size; ++site) {\n        std::sort(\n            neighbors[site].begin(),\n\
    \            neighbors[site].end(),\n            [&](int first, int second) {\n\
    \                return detail::direction_less(sites, site, first, second);\n\
    \            }\n        );\n    }\n\n    std::vector<std::array<int, 3>> triangles;\n\
    \    for (int site = 0; site < size; ++site) {\n        int degree = int(neighbors[site].size());\n\
    \        for (int index = 0; index < degree; ++index) {\n            int first\
    \ = neighbors[site][index];\n            int second = neighbors[site][(index +\
    \ 1) % degree];\n            if (orientation(sites[site], sites[first], sites[second])\
    \ <= 0) {\n                continue;\n            }\n            if (find_edge_index(first,\
    \ second) == -1) continue;\n            std::array<int, 3> triangle{site, first,\
    \ second};\n            std::sort(triangle.begin(), triangle.end());\n       \
    \     triangles.push_back(triangle);\n        }\n    }\n    std::sort(triangles.begin(),\
    \ triangles.end());\n    triangles.erase(\n        std::unique(triangles.begin(),\
    \ triangles.end()),\n        triangles.end()\n    );\n    for (auto& triangle\
    \ : triangles) {\n        if (orientation(\n                sites[triangle[0]],\n\
    \                sites[triangle[1]],\n                sites[triangle[2]]\n   \
    \         ) < 0) {\n            std::swap(triangle[1], triangle[2]);\n       \
    \ }\n    }\n\n    std::vector<std::array<int, 2>> incident_triangles(\n      \
    \  delaunay_edges.size(),\n        std::array<int, 2>{-1, -1}\n    );\n    std::vector<int>\
    \ incident_count(delaunay_edges.size(), 0);\n    for (int triangle = 0; triangle\
    \ < int(triangles.size()); ++triangle) {\n        for (int side = 0; side < 3;\
    \ ++side) {\n            int first = triangles[triangle][side];\n            int\
    \ second = triangles[triangle][(side + 1) % 3];\n            int edge = find_edge_index(first,\
    \ second);\n            assert(edge != -1);\n            assert(incident_count[edge]\
    \ < 2);\n            incident_triangles[edge][incident_count[edge]++] = triangle;\n\
    \        }\n    }\n\n    std::vector<int> parent(triangles.size());\n    std::vector<int>\
    \ component_size(triangles.size(), 1);\n    std::iota(parent.begin(), parent.end(),\
    \ 0);\n    auto find_root = [&](auto&& self, int vertex) -> int {\n        if\
    \ (parent[vertex] == vertex) return vertex;\n        return parent[vertex] = self(self,\
    \ parent[vertex]);\n    };\n    auto merge = [&](int first, int second) {\n  \
    \      first = find_root(find_root, first);\n        second = find_root(find_root,\
    \ second);\n        if (first == second) return;\n        if (component_size[first]\
    \ < component_size[second]) {\n            std::swap(first, second);\n       \
    \ }\n        parent[second] = first;\n        component_size[first] += component_size[second];\n\
    \    };\n    for (int edge = 0; edge < int(delaunay_edges.size()); ++edge) {\n\
    \        if (incident_count[edge] != 2) continue;\n        int first_triangle\
    \ = incident_triangles[edge][0];\n        int second_triangle = incident_triangles[edge][1];\n\
    \        const auto& first = triangles[first_triangle];\n        const auto& second\
    \ = triangles[second_triangle];\n        int fourth = second[0];\n        if (fourth\
    \ == first[0] || fourth == first[1] || fourth == first[2]) {\n            fourth\
    \ = second[1];\n        }\n        if (fourth == first[0] || fourth == first[1]\
    \ || fourth == first[2]) {\n            fourth = second[2];\n        }\n     \
    \   assert(\n            fourth != first[0] &&\n            fourth != first[1]\
    \ &&\n            fourth != first[2]\n        );\n        if (detail::cocircular(\n\
    \                sites[first[0]],\n                sites[first[1]],\n        \
    \        sites[first[2]],\n                sites[fourth]\n            )) {\n \
    \           merge(first_triangle, second_triangle);\n        }\n    }\n\n    VoronoiDiagram\
    \ result;\n    result.cell_edges.resize(size);\n    std::vector<int> root_vertex(triangles.size(),\
    \ -1);\n    std::vector<int> triangle_vertex(triangles.size(), -1);\n    for (int\
    \ triangle = 0; triangle < int(triangles.size()); ++triangle) {\n        int root\
    \ = find_root(find_root, triangle);\n        if (root_vertex[root] == -1) {\n\
    \            const auto& sites_on_circle = triangles[triangle];\n            root_vertex[root]\
    \ = int(result.vertices.size());\n            result.vertices.push_back(detail::circumcenter(\n\
    \                sites[sites_on_circle[0]],\n                sites[sites_on_circle[1]],\n\
    \                sites[sites_on_circle[2]]\n            ));\n        }\n     \
    \   triangle_vertex[triangle] = root_vertex[root];\n    }\n\n    result.edges.reserve(delaunay_edges.size());\n\
    \    for (int edge = 0; edge < int(delaunay_edges.size()); ++edge) {\n       \
    \ auto [first_site, second_site] = delaunay_edges[edge];\n        VoronoiEdge\
    \ voronoi_edge;\n        voronoi_edge.first_site = first_site;\n        voronoi_edge.second_site\
    \ = second_site;\n        voronoi_edge.first_vertex = -1;\n        voronoi_edge.second_vertex\
    \ = -1;\n\n        if (incident_count[edge] == 2) {\n            int first_vertex\
    \ =\n                triangle_vertex[incident_triangles[edge][0]];\n         \
    \   int second_vertex =\n                triangle_vertex[incident_triangles[edge][1]];\n\
    \            if (first_vertex == second_vertex) continue;\n            if (first_vertex\
    \ > second_vertex) {\n                std::swap(first_vertex, second_vertex);\n\
    \            }\n            voronoi_edge.kind = VoronoiEdgeKind::Segment;\n  \
    \          voronoi_edge.first_vertex = first_vertex;\n            voronoi_edge.second_vertex\
    \ = second_vertex;\n            voronoi_edge.point = result.vertices[first_vertex];\n\
    \            voronoi_edge.direction =\n                result.vertices[second_vertex]\
    \ - result.vertices[first_vertex];\n        } else if (incident_count[edge] ==\
    \ 1) {\n            int triangle = incident_triangles[edge][0];\n            int\
    \ third_site = triangles[triangle][0];\n            if (third_site == first_site\
    \ || third_site == second_site) {\n                third_site = triangles[triangle][1];\n\
    \            }\n            if (third_site == first_site || third_site == second_site)\
    \ {\n                third_site = triangles[triangle][2];\n            }\n   \
    \         assert(third_site != first_site && third_site != second_site);\n\n \
    \           Point<long double> first(sites[first_site]);\n            Point<long\
    \ double> second(sites[second_site]);\n            Point<long double> edge_direction\
    \ = second - first;\n            Point<long double> outward;\n            if (orientation(\n\
    \                    sites[first_site],\n                    sites[second_site],\n\
    \                    sites[third_site]\n                ) > 0) {\n           \
    \     outward = Point<long double>(\n                    edge_direction.y,\n \
    \                   -edge_direction.x\n                );\n            } else\
    \ {\n                outward = Point<long double>(\n                    -edge_direction.y,\n\
    \                    edge_direction.x\n                );\n            }\n   \
    \         voronoi_edge.kind = VoronoiEdgeKind::Ray;\n            voronoi_edge.first_vertex\
    \ = triangle_vertex[triangle];\n            voronoi_edge.point = result.vertices[voronoi_edge.first_vertex];\n\
    \            voronoi_edge.direction = detail::unit(outward);\n        } else {\n\
    \            assert(incident_count[edge] == 0);\n            Point<long double>\
    \ first(sites[first_site]);\n            Point<long double> second(sites[second_site]);\n\
    \            Point<long double> edge_direction = second - first;\n           \
    \ voronoi_edge.kind = VoronoiEdgeKind::Line;\n            voronoi_edge.point =\
    \ (first + second) / 2.0L;\n            voronoi_edge.direction = detail::unit(Point<long\
    \ double>(\n                edge_direction.y,\n                -edge_direction.x\n\
    \            ));\n        }\n\n        int voronoi_edge_index = int(result.edges.size());\n\
    \        result.edges.push_back(voronoi_edge);\n        result.cell_edges[first_site].push_back(voronoi_edge_index);\n\
    \        result.cell_edges[second_site].push_back(voronoi_edge_index);\n    }\n\
    \n    for (int site = 0; site < size; ++site) {\n        std::sort(\n        \
    \    result.cell_edges[site].begin(),\n            result.cell_edges[site].end(),\n\
    \            [&](int first_edge, int second_edge) {\n                int first_other\
    \ =\n                    detail::other_site(result.edges[first_edge], site);\n\
    \                int second_other =\n                    detail::other_site(result.edges[second_edge],\
    \ site);\n                return detail::direction_less(\n                   \
    \ sites,\n                    site,\n                    first_other,\n      \
    \              second_other\n                );\n            }\n        );\n \
    \   }\n    return result;\n}\n\n}  // namespace geometry\n}  // namespace m1une\n\
    \n#endif  // M1UNE_GEOMETRY_VORONOI_DIAGRAM_HPP\n"
  dependsOn:
  - geometry/euclidean_mst.hpp
  - ds/dsu/dsu.hpp
  - geometry/point.hpp
  isVerificationFile: false
  path: geometry/voronoi_diagram.hpp
  requiredBy:
  - geometry/all.hpp
  timestamp: '2026-07-22 14:57:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/voronoi_diagram.test.cpp
  - verify/geometry/centroid.test.cpp
documentation_of: geometry/voronoi_diagram.hpp
layout: document
title: Voronoi Diagram
---

## Overview

`voronoi_diagram` constructs the ordinary Euclidean Voronoi diagram of a set
of distinct integral sites. The diagram is the geometric dual of an exact
Delaunay triangulation, so it contains finite segments, unbounded rays, and,
when every site is collinear, full lines.

Combinatorial decisions use exact integral predicates. Finite vertices and
parametric edge geometry use `long double` because circumcenters need not be
integral.

## Types

```cpp
enum class VoronoiEdgeKind {
    Segment,
    Ray,
    Line,
};

struct VoronoiEdge {
    VoronoiEdgeKind kind;
    int first_site;
    int second_site;
    int first_vertex;
    int second_vertex;
    Point<long double> point;
    Point<long double> direction;
};

struct VoronoiDiagram {
    std::vector<Point<long double>> vertices;
    std::vector<VoronoiEdge> edges;
    std::vector<std::vector<int>> cell_edges;
};
```

Each edge is the shared one-dimensional boundary of the cells belonging to
`first_site` and `second_site`, with `first_site < second_site`. Its points are
described by

$$
\mathtt{point} + t\,\mathtt{direction}.
$$

| Kind | Parameter range | Vertex indices | Direction |
| --- | --- | --- | --- |
| `Segment` | $0 \leq t \leq 1$ | Both indices are valid; `point` is `vertices[first_vertex]`. | The displacement from `first_vertex` to `second_vertex`. |
| `Ray` | $0 \leq t$ | `first_vertex` is the finite endpoint and `second_vertex == -1`. | A unit vector pointing toward infinity. |
| `Line` | $-\infty < t < \infty$ | Both indices are `-1`. | A unit vector along the perpendicular bisector. |

`cell_edges[site]` contains the indices of all one-dimensional boundary edges
of that site's cell. They are ordered counterclockwise by the direction from
`site` to the neighboring site. Two cells that meet only at one Voronoi vertex
do not share an edge and therefore do not appear in each other's lists.

## Function

The exact signature is:

```cpp
template <std::integral T>
VoronoiDiagram voronoi_diagram(
    const std::vector<Point<T>>& sites
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `voronoi_diagram(sites)` | Returns all finite vertices, parametric edges, and per-site boundary-edge lists. | $O(N\log N)$ time and $O(N)$ memory |

Site indices are their zero-based positions in `sites`. All sites must be
pairwise distinct. Empty and one-site inputs have no vertices or edges. Two
sites produce one `Line`. A larger collinear input produces one line between
each consecutive pair of sites.

Cocircular Delaunay triangles are merged into one Voronoi vertex. Consequently,
the result does not expose artificial zero-length edges introduced by a choice
of Delaunay triangulation.

The degree-four incircle expressions must fit in signed 128-bit arithmetic.
This is satisfied, for example, by signed 32-bit input coordinates. As with the
other floating-point geometry constructions, callers should use an appropriate
tolerance when comparing returned coordinates.

## Example

```cpp
#include "geometry/voronoi_diagram.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> sites;
    sites.emplace_back(0, 0);
    sites.emplace_back(6, 0);
    sites.emplace_back(0, 8);

    auto diagram = m1une::geometry::voronoi_diagram(sites);
    std::cout << diagram.vertices.size() << '\n';  // 1
    std::cout << diagram.edges.size() << '\n';     // 3 rays

    for (int edge_index : diagram.cell_edges[0]) {
        const auto& edge = diagram.edges[edge_index];
        std::cout << edge.first_site << ' ' << edge.second_site << '\n';
    }
}
```
