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
    path: geometry/half_plane_intersection.hpp
    title: Half-Plane Intersection
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: Lines and Segments
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/voronoi_diagram.hpp
    title: Voronoi Diagram
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    ERROR: 1e-4
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/2160
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2160
  bundledCode: "#line 1 \"verify/geometry/voronoi_diagram.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/2160\"\n#define ERROR \"1e-4\"\n\
    \n#line 1 \"geometry/voronoi_diagram.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <cmath>\n#include <concepts>\n#include\
    \ <cstddef>\n#include <limits>\n#include <numeric>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"geometry/euclidean_mst.hpp\"\n\n\n\n#line 10 \"geometry/euclidean_mst.hpp\"\
    \n#include <tuple>\n#line 13 \"geometry/euclidean_mst.hpp\"\n\n#line 1 \"ds/dsu/dsu.hpp\"\
    \n\n\n\n#line 8 \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\nstruct\
    \ Dsu {\n   private:\n    int _n;\n    // parent_or_size[i] is the parent of i\
    \ if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i] is\
    \ the size of the group.\n    std::vector<int> parent_or_size;\n\n    // Returns\
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
    \ W(point.y)});\n        }\n        solve();\n    }\n\n    std::vector<std::pair<int,\
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
    \n\n#line 1 \"geometry/half_plane_intersection.hpp\"\n\n\n\n#line 8 \"geometry/half_plane_intersection.hpp\"\
    \n#include <deque>\n#line 10 \"geometry/half_plane_intersection.hpp\"\n#include\
    \ <numbers>\n#include <optional>\n#include <random>\n#line 15 \"geometry/half_plane_intersection.hpp\"\
    \n\n#line 1 \"geometry/line.hpp\"\n\n\n\n#line 8 \"geometry/line.hpp\"\n\n#line\
    \ 10 \"geometry/line.hpp\"\n\nnamespace m1une {\nnamespace geometry {\n\ntemplate\
    \ <Coordinate T>\nstruct Line {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate\
    \ <Coordinate T>\nstruct Segment {\n    Point<T> a;\n    Point<T> b;\n};\n\ntemplate\
    \ <Coordinate T>\nconstexpr Point<long double> centroid(const Segment<T>& segment)\
    \ {\n    return Point<long double>(\n        (\n            static_cast<long double>(segment.a.x)\
    \ +\n            static_cast<long double>(segment.b.x)\n        ) / 2,\n     \
    \   (\n            static_cast<long double>(segment.a.y) +\n            static_cast<long\
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
    \n}  // namespace geometry\n}  // namespace m1une\n\n\n#line 17 \"geometry/half_plane_intersection.hpp\"\
    \n\nnamespace m1une {\nnamespace geometry {\n\nenum class HalfPlaneIntersectionStatus\
    \ {\n    Empty,\n    Unbounded,\n    Degenerate,\n    Bounded,\n};\n\nstruct HalfPlaneIntersectionResult\
    \ {\n    HalfPlaneIntersectionStatus status;\n    std::vector<Point<long double>>\
    \ polygon;\n};\n\nnamespace half_plane_intersection_detail {\n\nstruct HalfPlane\
    \ {\n    Point<long double> point;\n    Point<long double> direction;\n};\n\n\
    inline int direction_half(const Point<long double>& direction) {\n    return direction.y\
    \ > 0 || (direction.y == 0 && direction.x >= 0) ? 0 : 1;\n}\n\ninline bool direction_less(const\
    \ HalfPlane& first, const HalfPlane& second) {\n    int first_half = direction_half(first.direction);\n\
    \    int second_half = direction_half(second.direction);\n    if (first_half !=\
    \ second_half) return first_half < second_half;\n    return cross(first.direction,\
    \ second.direction) > 0;\n}\n\ninline bool parallel(\n    const HalfPlane& first,\n\
    \    const HalfPlane& second,\n    long double eps\n) {\n    return std::fabs(cross(first.direction,\
    \ second.direction)) <= eps;\n}\n\ninline bool same_direction(\n    const HalfPlane&\
    \ first,\n    const HalfPlane& second,\n    long double eps\n) {\n    return parallel(first,\
    \ second, eps) &&\n           dot(first.direction, second.direction) > 0;\n}\n\
    \ninline bool outside(\n    const HalfPlane& half_plane,\n    const Point<long\
    \ double>& point,\n    long double eps\n) {\n    return cross(half_plane.direction,\
    \ point - half_plane.point) < -eps;\n}\n\ninline bool more_restrictive(\n    const\
    \ HalfPlane& candidate,\n    const HalfPlane& current,\n    long double eps\n\
    ) {\n    return cross(\n        current.direction,\n        candidate.point -\
    \ current.point\n    ) > eps;\n}\n\ninline std::optional<Point<long double>> intersection(\n\
    \    const HalfPlane& first,\n    const HalfPlane& second,\n    long double eps\n\
    ) {\n    long double denominator = cross(first.direction, second.direction);\n\
    \    if (std::fabs(denominator) <= eps) return std::nullopt;\n    long double\
    \ ratio = cross(\n        second.point - first.point,\n        second.direction\n\
    \    ) / denominator;\n    return first.point + first.direction * ratio;\n}\n\n\
    inline void merge_same_direction(\n    std::vector<HalfPlane>& half_planes,\n\
    \    const HalfPlane& half_plane,\n    long double eps\n) {\n    if (\n      \
    \  half_planes.empty() ||\n        !same_direction(half_planes.back(), half_plane,\
    \ eps)\n    ) {\n        half_planes.push_back(half_plane);\n        return;\n\
    \    }\n    if (more_restrictive(half_plane, half_planes.back(), eps)) {\n   \
    \     half_planes.back() = half_plane;\n    }\n}\n\ninline void merge_cyclic_ends(\n\
    \    std::vector<HalfPlane>& half_planes,\n    long double eps\n) {\n    if (\n\
    \        half_planes.size() < 2 ||\n        !same_direction(half_planes.front(),\
    \ half_planes.back(), eps)\n    ) {\n        return;\n    }\n    if (more_restrictive(half_planes.back(),\
    \ half_planes.front(), eps)) {\n        half_planes.front() = half_planes.back();\n\
    \    }\n    half_planes.pop_back();\n}\n\ninline bool has_feasible_point(\n  \
    \  std::vector<HalfPlane> half_planes,\n    long double eps\n) {\n    std::mt19937_64\
    \ generator(0x6a09e667f3bcc909ULL);\n    std::shuffle(half_planes.begin(), half_planes.end(),\
    \ generator);\n\n    Point<long double> feasible(0, 0);\n    for (std::size_t\
    \ index = 0; index < half_planes.size(); ++index) {\n        const HalfPlane&\
    \ current = half_planes[index];\n        if (!outside(current, feasible, eps))\
    \ continue;\n\n        Point<long double> normal(\n            -current.direction.y,\n\
    \            current.direction.x\n        );\n        Point<long double> base\
    \ = normal * dot(normal, current.point);\n        long double lower = -std::numeric_limits<long\
    \ double>::infinity();\n        long double upper = std::numeric_limits<long double>::infinity();\n\
    \        for (std::size_t previous_index = 0;\n             previous_index < index;\n\
    \             ++previous_index) {\n            const HalfPlane& previous = half_planes[previous_index];\n\
    \            long double coefficient = cross(\n                previous.direction,\n\
    \                current.direction\n            );\n            long double constant\
    \ = cross(\n                previous.direction,\n                base - previous.point\n\
    \            );\n            if (std::fabs(coefficient) <= eps) {\n          \
    \      if (constant < -eps) return false;\n                continue;\n       \
    \     }\n\n            long double bound = (-eps - constant) / coefficient;\n\
    \            if (coefficient > 0) {\n                lower = std::max(lower, bound);\n\
    \            } else {\n                upper = std::min(upper, bound);\n     \
    \       }\n            if (lower > upper) return false;\n        }\n\n       \
    \ long double parameter = 0;\n        if (parameter < lower) parameter = lower;\n\
    \        if (parameter > upper) parameter = upper;\n        feasible = base +\
    \ current.direction * parameter;\n    }\n    return true;\n}\n\ninline bool has_bounded_recession_cone(\n\
    \    const std::vector<HalfPlane>& half_planes,\n    long double eps\n) {\n  \
    \  if (half_planes.empty()) return false;\n\n    constexpr long double pi = std::numbers::pi_v<long\
    \ double>;\n    std::vector<long double> angles;\n    angles.reserve(half_planes.size());\n\
    \    for (const HalfPlane& half_plane : half_planes) {\n        long double angle\
    \ = std::atan2(\n            half_plane.direction.y,\n            half_plane.direction.x\n\
    \        );\n        if (angle < 0) angle += 2 * pi;\n        angles.push_back(angle);\n\
    \    }\n\n    long double maximum_gap = angles.front() + 2 * pi - angles.back();\n\
    \    for (std::size_t index = 1; index < angles.size(); ++index) {\n        maximum_gap\
    \ = std::max(\n            maximum_gap,\n            angles[index] - angles[index\
    \ - 1]\n        );\n    }\n    return maximum_gap < pi - eps;\n}\n\n}  // namespace\
    \ half_plane_intersection_detail\n\n// Each directed line keeps its closed left\
    \ half-plane. Returns the vertices of\n// a bounded intersection with positive\
    \ area in counterclockwise order. Empty,\n// unbounded, and bounded zero-area\
    \ intersections have distinct statuses.\ntemplate <Coordinate T>\nHalfPlaneIntersectionResult\
    \ half_plane_intersection(\n    const std::vector<Line<T>>& half_planes,\n   \
    \ long double eps = 1e-12L\n) {\n    using half_plane_intersection_detail::HalfPlane;\n\
    \    namespace detail = half_plane_intersection_detail;\n\n    assert(eps >= 0);\n\
    \    std::vector<HalfPlane> sorted;\n    sorted.reserve(half_planes.size());\n\
    \    for (const Line<T>& line : half_planes) {\n        assert(line.a != line.b);\n\
    \        Point<long double> point(line.a);\n        Point<long double> direction\
    \ = Point<long double>(line.b) - point;\n        long double length = norm(direction);\n\
    \        direction = direction / length;\n        sorted.push_back(HalfPlane{point,\
    \ direction});\n    }\n    if (!detail::has_feasible_point(sorted, eps)) {\n \
    \       return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Empty,\n\
    \            {},\n        };\n    }\n    std::sort(sorted.begin(), sorted.end(),\
    \ detail::direction_less);\n    if (!detail::has_bounded_recession_cone(sorted,\
    \ eps)) {\n        return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Unbounded,\n\
    \            {},\n        };\n    }\n    if (sorted.size() < 3) {\n        return\
    \ HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    std::vector<HalfPlane> unique;\n  \
    \  unique.reserve(sorted.size());\n    for (const HalfPlane& half_plane : sorted)\
    \ {\n        detail::merge_same_direction(unique, half_plane, eps);\n    }\n \
    \   detail::merge_cyclic_ends(unique, eps);\n    if (unique.size() < 3) {\n  \
    \      return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    std::deque<HalfPlane> deque;\n    for\
    \ (const HalfPlane& half_plane : unique) {\n        while (deque.size() >= 2)\
    \ {\n            auto point = detail::intersection(\n                deque[deque.size()\
    \ - 2],\n                deque.back(),\n                eps\n            );\n\
    \            if (!point.has_value()) {\n                return HalfPlaneIntersectionResult{\n\
    \                    HalfPlaneIntersectionStatus::Degenerate,\n              \
    \      {},\n                };\n            }\n            if (!detail::outside(half_plane,\
    \ *point, eps)) break;\n            deque.pop_back();\n        }\n        while\
    \ (deque.size() >= 2) {\n            auto point = detail::intersection(deque[0],\
    \ deque[1], eps);\n            if (!point.has_value()) {\n                return\
    \ HalfPlaneIntersectionResult{\n                    HalfPlaneIntersectionStatus::Degenerate,\n\
    \                    {},\n                };\n            }\n            if (!detail::outside(half_plane,\
    \ *point, eps)) break;\n            deque.pop_front();\n        }\n        deque.push_back(half_plane);\n\
    \    }\n\n    while (deque.size() >= 3) {\n        auto point = detail::intersection(\n\
    \            deque[deque.size() - 2],\n            deque.back(),\n           \
    \ eps\n        );\n        if (!point.has_value()) {\n            return HalfPlaneIntersectionResult{\n\
    \                HalfPlaneIntersectionStatus::Degenerate,\n                {},\n\
    \            };\n        }\n        if (!detail::outside(deque.front(), *point,\
    \ eps)) break;\n        deque.pop_back();\n    }\n    while (deque.size() >= 3)\
    \ {\n        auto point = detail::intersection(deque[0], deque[1], eps);\n   \
    \     if (!point.has_value()) {\n            return HalfPlaneIntersectionResult{\n\
    \                HalfPlaneIntersectionStatus::Degenerate,\n                {},\n\
    \            };\n        }\n        if (!detail::outside(deque.back(), *point,\
    \ eps)) break;\n        deque.pop_front();\n    }\n    if (deque.size() < 3) {\n\
    \        return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    std::vector<Point<long double>> polygon;\n\
    \    polygon.reserve(deque.size());\n    for (std::size_t index = 0; index < deque.size();\
    \ ++index) {\n        auto point = detail::intersection(\n            deque[index],\n\
    \            deque[(index + 1) % deque.size()],\n            eps\n        );\n\
    \        if (!point.has_value()) {\n            return HalfPlaneIntersectionResult{\n\
    \                HalfPlaneIntersectionStatus::Degenerate,\n                {},\n\
    \            };\n        }\n        if (\n            polygon.empty() ||\n   \
    \         distance(polygon.back(), *point) > eps\n        ) {\n            polygon.push_back(*point);\n\
    \        }\n    }\n    if (\n        polygon.size() >= 2 &&\n        distance(polygon.front(),\
    \ polygon.back()) <= eps\n    ) {\n        polygon.pop_back();\n    }\n    if\
    \ (polygon.size() < 3) {\n        return HalfPlaneIntersectionResult{\n      \
    \      HalfPlaneIntersectionStatus::Degenerate,\n            {},\n        };\n\
    \    }\n\n    long double signed_area2 = 0;\n    Point<long double> origin = polygon.front();\n\
    \    for (std::size_t index = 1; index + 1 < polygon.size(); ++index) {\n    \
    \    signed_area2 += cross(\n            polygon[index] - origin,\n          \
    \  polygon[index + 1] - origin\n        );\n    }\n    if (signed_area2 <= eps)\
    \ {\n        return HalfPlaneIntersectionResult{\n            HalfPlaneIntersectionStatus::Degenerate,\n\
    \            {},\n        };\n    }\n\n    auto first = std::min_element(polygon.begin(),\
    \ polygon.end());\n    std::rotate(polygon.begin(), first, polygon.end());\n \
    \   return HalfPlaneIntersectionResult{\n        HalfPlaneIntersectionStatus::Bounded,\n\
    \        std::move(polygon),\n    };\n}\n\n}  // namespace geometry\n}  // namespace\
    \ m1une\n\n\n#line 6 \"verify/geometry/voronoi_diagram.test.cpp\"\n\n#line 11\
    \ \"verify/geometry/voronoi_diagram.test.cpp\"\n#include <cstdint>\n#include <iomanip>\n\
    #include <iostream>\n#line 15 \"verify/geometry/voronoi_diagram.test.cpp\"\n#include\
    \ <set>\n#line 18 \"verify/geometry/voronoi_diagram.test.cpp\"\n\nnamespace {\n\
    \nusing m1une::geometry::Point;\nusing m1une::geometry::VoronoiDiagram;\nusing\
    \ m1une::geometry::VoronoiEdge;\nusing m1une::geometry::VoronoiEdgeKind;\nusing\
    \ Site = Point<long long>;\nusing RealPoint = Point<long double>;\n\nlong double\
    \ squared_distance(const RealPoint& first, const RealPoint& second) {\n    long\
    \ double x = first.x - second.x;\n    long double y = first.y - second.y;\n  \
    \  return x * x + y * y;\n}\n\nbool close(long double first, long double second,\
    \ long double eps = 1e-8L) {\n    return std::fabs(first - second) <=\n      \
    \     eps * std::max(\n               1.0L,\n               std::max(std::fabs(first),\
    \ std::fabs(second))\n           );\n}\n\nvoid check_boundary_point(\n    const\
    \ std::vector<Site>& sites,\n    const VoronoiEdge& edge,\n    const RealPoint&\
    \ point\n) {\n    RealPoint first(sites[edge.first_site]);\n    RealPoint second(sites[edge.second_site]);\n\
    \    long double first_distance = squared_distance(point, first);\n    long double\
    \ second_distance = squared_distance(point, second);\n    assert(close(first_distance,\
    \ second_distance, 1e-7L));\n    for (const Site& site : sites) {\n        long\
    \ double candidate = squared_distance(point, RealPoint(site));\n        long double\
    \ tolerance =\n            1e-7L * std::max(1.0L, std::max(first_distance, candidate));\n\
    \        assert(first_distance <= candidate + tolerance);\n    }\n}\n\nbool naive_has_voronoi_edge(\n\
    \    const std::vector<Site>& sites,\n    int first_site,\n    int second_site\n\
    ) {\n    RealPoint first(sites[first_site]);\n    RealPoint second(sites[second_site]);\n\
    \    RealPoint midpoint = (first + second) / 2.0L;\n    RealPoint difference =\
    \ second - first;\n    RealPoint direction(difference.y, -difference.x);\n   \
    \ long double lower = -std::numeric_limits<long double>::infinity();\n    long\
    \ double upper = std::numeric_limits<long double>::infinity();\n\n    for (const\
    \ Site& integer_site : sites) {\n        RealPoint site(integer_site);\n     \
    \   long double constant =\n            squared_distance(midpoint, first) - squared_distance(midpoint,\
    \ site);\n        RealPoint shifted = midpoint + direction;\n        long double\
    \ coefficient =\n            squared_distance(shifted, first) - squared_distance(shifted,\
    \ site) -\n            constant;\n        if (std::fabs(coefficient) <= 1e-14L)\
    \ {\n            if (constant > 1e-12L) return false;\n        } else {\n    \
    \        long double bound = -constant / coefficient;\n            if (coefficient\
    \ > 0) {\n                upper = std::min(upper, bound);\n            } else\
    \ {\n                lower = std::max(lower, bound);\n            }\n        }\n\
    \    }\n    return lower + 1e-10L < upper;\n}\n\nvoid check_diagram(const std::vector<Site>&\
    \ sites) {\n    VoronoiDiagram diagram = m1une::geometry::voronoi_diagram(sites);\n\
    \    assert(diagram.cell_edges.size() == sites.size());\n\n    std::set<std::pair<int,\
    \ int>> actual_pairs;\n    std::vector<int> cell_occurrences(diagram.edges.size(),\
    \ 0);\n    for (int site = 0; site < int(sites.size()); ++site) {\n        for\
    \ (int edge_index : diagram.cell_edges[site]) {\n            assert(0 <= edge_index\
    \ && edge_index < int(diagram.edges.size()));\n            const VoronoiEdge&\
    \ edge = diagram.edges[edge_index];\n            assert(edge.first_site == site\
    \ || edge.second_site == site);\n            ++cell_occurrences[edge_index];\n\
    \        }\n    }\n\n    for (int edge_index = 0; edge_index < int(diagram.edges.size());\
    \ ++edge_index) {\n        const VoronoiEdge& edge = diagram.edges[edge_index];\n\
    \        assert(cell_occurrences[edge_index] == 2);\n        assert(0 <= edge.first_site\
    \ && edge.first_site < int(sites.size()));\n        assert(0 <= edge.second_site\
    \ && edge.second_site < int(sites.size()));\n        assert(edge.first_site <\
    \ edge.second_site);\n        assert(actual_pairs.emplace(edge.first_site, edge.second_site).second);\n\
    \n        if (edge.kind == VoronoiEdgeKind::Segment) {\n            assert(0 <=\
    \ edge.first_vertex);\n            assert(edge.first_vertex < int(diagram.vertices.size()));\n\
    \            assert(0 <= edge.second_vertex);\n            assert(edge.second_vertex\
    \ < int(diagram.vertices.size()));\n            assert(edge.first_vertex < edge.second_vertex);\n\
    \            assert(close(edge.point.x, diagram.vertices[edge.first_vertex].x));\n\
    \            assert(close(edge.point.y, diagram.vertices[edge.first_vertex].y));\n\
    \            RealPoint expected_direction =\n                diagram.vertices[edge.second_vertex]\
    \ -\n                diagram.vertices[edge.first_vertex];\n            assert(close(edge.direction.x,\
    \ expected_direction.x));\n            assert(close(edge.direction.y, expected_direction.y));\n\
    \            for (long double parameter : std::array<long double, 3>{0, 0.5L,\
    \ 1}) {\n                check_boundary_point(\n                    sites,\n \
    \                   edge,\n                    edge.point + edge.direction * parameter\n\
    \                );\n            }\n        } else if (edge.kind == VoronoiEdgeKind::Ray)\
    \ {\n            assert(0 <= edge.first_vertex);\n            assert(edge.first_vertex\
    \ < int(diagram.vertices.size()));\n            assert(edge.second_vertex == -1);\n\
    \            assert(close(edge.point.x, diagram.vertices[edge.first_vertex].x));\n\
    \            assert(close(edge.point.y, diagram.vertices[edge.first_vertex].y));\n\
    \            assert(close(m1une::geometry::norm(edge.direction), 1));\n      \
    \      for (long double parameter : std::array<long double, 3>{0, 1, 100}) {\n\
    \                check_boundary_point(\n                    sites,\n         \
    \           edge,\n                    edge.point + edge.direction * parameter\n\
    \                );\n            }\n        } else {\n            assert(edge.kind\
    \ == VoronoiEdgeKind::Line);\n            assert(edge.first_vertex == -1);\n \
    \           assert(edge.second_vertex == -1);\n            assert(close(m1une::geometry::norm(edge.direction),\
    \ 1));\n            for (long double parameter : std::array<long double, 3>{-100,\
    \ 0, 100}) {\n                check_boundary_point(\n                    sites,\n\
    \                    edge,\n                    edge.point + edge.direction *\
    \ parameter\n                );\n            }\n        }\n    }\n\n    for (int\
    \ first = 0; first < int(sites.size()); ++first) {\n        for (int second =\
    \ first + 1; second < int(sites.size()); ++second) {\n            bool actual\
    \ = actual_pairs.contains(std::pair(first, second));\n            bool expected\
    \ = naive_has_voronoi_edge(sites, first, second);\n            assert(actual ==\
    \ expected);\n        }\n    }\n}\n\nint count_kind(const VoronoiDiagram& diagram,\
    \ VoronoiEdgeKind kind) {\n    return int(std::count_if(\n        diagram.edges.begin(),\n\
    \        diagram.edges.end(),\n        [&](const VoronoiEdge& edge) { return edge.kind\
    \ == kind; }\n    ));\n}\n\nvoid test_fixed() {\n    check_diagram({});\n    check_diagram(std::vector<Site>{Site(4,\
    \ -2)});\n\n    std::vector<Site> two_sites{Site(0, 0), Site(4, 0)};\n    check_diagram(two_sites);\n\
    \    VoronoiDiagram two = m1une::geometry::voronoi_diagram(two_sites);\n    assert(two.vertices.empty());\n\
    \    assert(two.edges.size() == 1);\n    assert(two.edges[0].kind == VoronoiEdgeKind::Line);\n\
    \    assert(close(two.edges[0].point.x, 2));\n    assert(close(two.edges[0].point.y,\
    \ 0));\n\n    std::vector<Site> triangle{\n        Site(0, 0),\n        Site(6,\
    \ 0),\n        Site(0, 8),\n    };\n    check_diagram(triangle);\n    VoronoiDiagram\
    \ three = m1une::geometry::voronoi_diagram(triangle);\n    assert(three.vertices.size()\
    \ == 1);\n    assert(three.edges.size() == 3);\n    assert(count_kind(three, VoronoiEdgeKind::Ray)\
    \ == 3);\n    assert(close(three.vertices[0].x, 3));\n    assert(close(three.vertices[0].y,\
    \ 4));\n\n    std::vector<Site> square{\n        Site(0, 0),\n        Site(2,\
    \ 0),\n        Site(2, 2),\n        Site(0, 2),\n    };\n    check_diagram(square);\n\
    \    VoronoiDiagram four = m1une::geometry::voronoi_diagram(square);\n    assert(four.vertices.size()\
    \ == 1);\n    assert(four.edges.size() == 4);\n    assert(count_kind(four, VoronoiEdgeKind::Ray)\
    \ == 4);\n\n    std::vector<Site> cocircular{\n        Site(5, 0),\n        Site(3,\
    \ 4),\n        Site(0, 5),\n        Site(-3, 4),\n        Site(-5, 0),\n     \
    \   Site(-3, -4),\n        Site(0, -5),\n        Site(3, -4),\n    };\n    check_diagram(cocircular);\n\
    \    VoronoiDiagram eight = m1une::geometry::voronoi_diagram(cocircular);\n  \
    \  assert(eight.vertices.size() == 1);\n    assert(eight.edges.size() == 8);\n\
    \    assert(count_kind(eight, VoronoiEdgeKind::Ray) == 8);\n\n    std::vector<Site>\
    \ square_with_center = square;\n    square_with_center.emplace_back(1, 1);\n \
    \   check_diagram(square_with_center);\n    VoronoiDiagram five =\n        m1une::geometry::voronoi_diagram(square_with_center);\n\
    \    assert(five.vertices.size() == 4);\n    assert(five.edges.size() == 8);\n\
    \    assert(count_kind(five, VoronoiEdgeKind::Segment) == 4);\n    assert(count_kind(five,\
    \ VoronoiEdgeKind::Ray) == 4);\n\n    std::vector<Site> collinear{\n        Site(-5,\
    \ 3),\n        Site(-1, 3),\n        Site(2, 3),\n        Site(9, 3),\n    };\n\
    \    check_diagram(collinear);\n    VoronoiDiagram line = m1une::geometry::voronoi_diagram(collinear);\n\
    \    assert(line.vertices.empty());\n    assert(line.edges.size() == 3);\n   \
    \ assert(count_kind(line, VoronoiEdgeKind::Line) == 3);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x243f6a8885a308d3ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 1500; ++trial) {\n       \
    \ int size = int(random() % 11);\n        std::set<std::pair<long long, long long>>\
    \ used;\n        std::vector<Site> sites;\n        sites.reserve(size);\n    \
    \    while (int(sites.size()) < size) {\n            long long x = static_cast<long\
    \ long>(random() % 21) - 10;\n            long long y = static_cast<long long>(random()\
    \ % 21) - 10;\n            if (used.emplace(x, y).second) sites.emplace_back(x,\
    \ y);\n        }\n        check_diagram(sites);\n    }\n}\n\nlong double polygon_area(const\
    \ std::vector<RealPoint>& polygon) {\n    long double twice_area = 0;\n    for\
    \ (int index = 0; index < int(polygon.size()); ++index) {\n        twice_area\
    \ += m1une::geometry::cross(\n            polygon[index],\n            polygon[(index\
    \ + 1) % polygon.size()]\n        );\n    }\n    return std::fabs(twice_area)\
    \ / 2;\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    std::cout << std::fixed << std::setprecision(10);\n    while (true) {\n\
    \        int island_size, site_count;\n        std::cin >> island_size >> site_count;\n\
    \        if (island_size == 0 && site_count == 0) break;\n\n        std::vector<Site>\
    \ island(island_size);\n        for (Site& point : island) std::cin >> point.x\
    \ >> point.y;\n        std::vector<Site> sites(site_count);\n        for (Site&\
    \ point : sites) std::cin >> point.x >> point.y;\n\n        VoronoiDiagram diagram\
    \ = m1une::geometry::voronoi_diagram(sites);\n        for (int site = 0; site\
    \ < site_count; ++site) {\n            std::vector<m1une::geometry::Line<long\
    \ double>> half_planes;\n            half_planes.reserve(island_size + diagram.cell_edges[site].size());\n\
    \            for (int index = 0; index < island_size; ++index) {\n           \
    \     half_planes.push_back(m1une::geometry::Line<long double>{\n            \
    \        RealPoint(island[index]),\n                    RealPoint(island[(index\
    \ + 1) % island_size]),\n                });\n            }\n            for (int\
    \ edge_index : diagram.cell_edges[site]) {\n                const VoronoiEdge&\
    \ edge = diagram.edges[edge_index];\n                int other = edge.first_site\
    \ == site\n                    ? edge.second_site\n                    : edge.first_site;\n\
    \                RealPoint first(sites[site]);\n                RealPoint second(sites[other]);\n\
    \                RealPoint midpoint = (first + second) / 2.0L;\n             \
    \   RealPoint difference = second - first;\n                RealPoint direction(-difference.y,\
    \ difference.x);\n                half_planes.push_back(m1une::geometry::Line<long\
    \ double>{\n                    midpoint,\n                    midpoint + direction,\n\
    \                });\n            }\n\n            auto intersection =\n     \
    \           m1une::geometry::half_plane_intersection(half_planes);\n         \
    \   long double area = 0;\n            if (\n                intersection.status\
    \ ==\n                m1une::geometry::HalfPlaneIntersectionStatus::Bounded\n\
    \            ) {\n                area = polygon_area(intersection.polygon);\n\
    \            }\n            std::cout << area << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2160\"\n#define\
    \ ERROR \"1e-4\"\n\n#include \"../../geometry/voronoi_diagram.hpp\"\n#include\
    \ \"../../geometry/half_plane_intersection.hpp\"\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <cmath>\n#include <cstdint>\n#include\
    \ <iomanip>\n#include <iostream>\n#include <limits>\n#include <set>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace {\n\nusing m1une::geometry::Point;\n\
    using m1une::geometry::VoronoiDiagram;\nusing m1une::geometry::VoronoiEdge;\n\
    using m1une::geometry::VoronoiEdgeKind;\nusing Site = Point<long long>;\nusing\
    \ RealPoint = Point<long double>;\n\nlong double squared_distance(const RealPoint&\
    \ first, const RealPoint& second) {\n    long double x = first.x - second.x;\n\
    \    long double y = first.y - second.y;\n    return x * x + y * y;\n}\n\nbool\
    \ close(long double first, long double second, long double eps = 1e-8L) {\n  \
    \  return std::fabs(first - second) <=\n           eps * std::max(\n         \
    \      1.0L,\n               std::max(std::fabs(first), std::fabs(second))\n \
    \          );\n}\n\nvoid check_boundary_point(\n    const std::vector<Site>& sites,\n\
    \    const VoronoiEdge& edge,\n    const RealPoint& point\n) {\n    RealPoint\
    \ first(sites[edge.first_site]);\n    RealPoint second(sites[edge.second_site]);\n\
    \    long double first_distance = squared_distance(point, first);\n    long double\
    \ second_distance = squared_distance(point, second);\n    assert(close(first_distance,\
    \ second_distance, 1e-7L));\n    for (const Site& site : sites) {\n        long\
    \ double candidate = squared_distance(point, RealPoint(site));\n        long double\
    \ tolerance =\n            1e-7L * std::max(1.0L, std::max(first_distance, candidate));\n\
    \        assert(first_distance <= candidate + tolerance);\n    }\n}\n\nbool naive_has_voronoi_edge(\n\
    \    const std::vector<Site>& sites,\n    int first_site,\n    int second_site\n\
    ) {\n    RealPoint first(sites[first_site]);\n    RealPoint second(sites[second_site]);\n\
    \    RealPoint midpoint = (first + second) / 2.0L;\n    RealPoint difference =\
    \ second - first;\n    RealPoint direction(difference.y, -difference.x);\n   \
    \ long double lower = -std::numeric_limits<long double>::infinity();\n    long\
    \ double upper = std::numeric_limits<long double>::infinity();\n\n    for (const\
    \ Site& integer_site : sites) {\n        RealPoint site(integer_site);\n     \
    \   long double constant =\n            squared_distance(midpoint, first) - squared_distance(midpoint,\
    \ site);\n        RealPoint shifted = midpoint + direction;\n        long double\
    \ coefficient =\n            squared_distance(shifted, first) - squared_distance(shifted,\
    \ site) -\n            constant;\n        if (std::fabs(coefficient) <= 1e-14L)\
    \ {\n            if (constant > 1e-12L) return false;\n        } else {\n    \
    \        long double bound = -constant / coefficient;\n            if (coefficient\
    \ > 0) {\n                upper = std::min(upper, bound);\n            } else\
    \ {\n                lower = std::max(lower, bound);\n            }\n        }\n\
    \    }\n    return lower + 1e-10L < upper;\n}\n\nvoid check_diagram(const std::vector<Site>&\
    \ sites) {\n    VoronoiDiagram diagram = m1une::geometry::voronoi_diagram(sites);\n\
    \    assert(diagram.cell_edges.size() == sites.size());\n\n    std::set<std::pair<int,\
    \ int>> actual_pairs;\n    std::vector<int> cell_occurrences(diagram.edges.size(),\
    \ 0);\n    for (int site = 0; site < int(sites.size()); ++site) {\n        for\
    \ (int edge_index : diagram.cell_edges[site]) {\n            assert(0 <= edge_index\
    \ && edge_index < int(diagram.edges.size()));\n            const VoronoiEdge&\
    \ edge = diagram.edges[edge_index];\n            assert(edge.first_site == site\
    \ || edge.second_site == site);\n            ++cell_occurrences[edge_index];\n\
    \        }\n    }\n\n    for (int edge_index = 0; edge_index < int(diagram.edges.size());\
    \ ++edge_index) {\n        const VoronoiEdge& edge = diagram.edges[edge_index];\n\
    \        assert(cell_occurrences[edge_index] == 2);\n        assert(0 <= edge.first_site\
    \ && edge.first_site < int(sites.size()));\n        assert(0 <= edge.second_site\
    \ && edge.second_site < int(sites.size()));\n        assert(edge.first_site <\
    \ edge.second_site);\n        assert(actual_pairs.emplace(edge.first_site, edge.second_site).second);\n\
    \n        if (edge.kind == VoronoiEdgeKind::Segment) {\n            assert(0 <=\
    \ edge.first_vertex);\n            assert(edge.first_vertex < int(diagram.vertices.size()));\n\
    \            assert(0 <= edge.second_vertex);\n            assert(edge.second_vertex\
    \ < int(diagram.vertices.size()));\n            assert(edge.first_vertex < edge.second_vertex);\n\
    \            assert(close(edge.point.x, diagram.vertices[edge.first_vertex].x));\n\
    \            assert(close(edge.point.y, diagram.vertices[edge.first_vertex].y));\n\
    \            RealPoint expected_direction =\n                diagram.vertices[edge.second_vertex]\
    \ -\n                diagram.vertices[edge.first_vertex];\n            assert(close(edge.direction.x,\
    \ expected_direction.x));\n            assert(close(edge.direction.y, expected_direction.y));\n\
    \            for (long double parameter : std::array<long double, 3>{0, 0.5L,\
    \ 1}) {\n                check_boundary_point(\n                    sites,\n \
    \                   edge,\n                    edge.point + edge.direction * parameter\n\
    \                );\n            }\n        } else if (edge.kind == VoronoiEdgeKind::Ray)\
    \ {\n            assert(0 <= edge.first_vertex);\n            assert(edge.first_vertex\
    \ < int(diagram.vertices.size()));\n            assert(edge.second_vertex == -1);\n\
    \            assert(close(edge.point.x, diagram.vertices[edge.first_vertex].x));\n\
    \            assert(close(edge.point.y, diagram.vertices[edge.first_vertex].y));\n\
    \            assert(close(m1une::geometry::norm(edge.direction), 1));\n      \
    \      for (long double parameter : std::array<long double, 3>{0, 1, 100}) {\n\
    \                check_boundary_point(\n                    sites,\n         \
    \           edge,\n                    edge.point + edge.direction * parameter\n\
    \                );\n            }\n        } else {\n            assert(edge.kind\
    \ == VoronoiEdgeKind::Line);\n            assert(edge.first_vertex == -1);\n \
    \           assert(edge.second_vertex == -1);\n            assert(close(m1une::geometry::norm(edge.direction),\
    \ 1));\n            for (long double parameter : std::array<long double, 3>{-100,\
    \ 0, 100}) {\n                check_boundary_point(\n                    sites,\n\
    \                    edge,\n                    edge.point + edge.direction *\
    \ parameter\n                );\n            }\n        }\n    }\n\n    for (int\
    \ first = 0; first < int(sites.size()); ++first) {\n        for (int second =\
    \ first + 1; second < int(sites.size()); ++second) {\n            bool actual\
    \ = actual_pairs.contains(std::pair(first, second));\n            bool expected\
    \ = naive_has_voronoi_edge(sites, first, second);\n            assert(actual ==\
    \ expected);\n        }\n    }\n}\n\nint count_kind(const VoronoiDiagram& diagram,\
    \ VoronoiEdgeKind kind) {\n    return int(std::count_if(\n        diagram.edges.begin(),\n\
    \        diagram.edges.end(),\n        [&](const VoronoiEdge& edge) { return edge.kind\
    \ == kind; }\n    ));\n}\n\nvoid test_fixed() {\n    check_diagram({});\n    check_diagram(std::vector<Site>{Site(4,\
    \ -2)});\n\n    std::vector<Site> two_sites{Site(0, 0), Site(4, 0)};\n    check_diagram(two_sites);\n\
    \    VoronoiDiagram two = m1une::geometry::voronoi_diagram(two_sites);\n    assert(two.vertices.empty());\n\
    \    assert(two.edges.size() == 1);\n    assert(two.edges[0].kind == VoronoiEdgeKind::Line);\n\
    \    assert(close(two.edges[0].point.x, 2));\n    assert(close(two.edges[0].point.y,\
    \ 0));\n\n    std::vector<Site> triangle{\n        Site(0, 0),\n        Site(6,\
    \ 0),\n        Site(0, 8),\n    };\n    check_diagram(triangle);\n    VoronoiDiagram\
    \ three = m1une::geometry::voronoi_diagram(triangle);\n    assert(three.vertices.size()\
    \ == 1);\n    assert(three.edges.size() == 3);\n    assert(count_kind(three, VoronoiEdgeKind::Ray)\
    \ == 3);\n    assert(close(three.vertices[0].x, 3));\n    assert(close(three.vertices[0].y,\
    \ 4));\n\n    std::vector<Site> square{\n        Site(0, 0),\n        Site(2,\
    \ 0),\n        Site(2, 2),\n        Site(0, 2),\n    };\n    check_diagram(square);\n\
    \    VoronoiDiagram four = m1une::geometry::voronoi_diagram(square);\n    assert(four.vertices.size()\
    \ == 1);\n    assert(four.edges.size() == 4);\n    assert(count_kind(four, VoronoiEdgeKind::Ray)\
    \ == 4);\n\n    std::vector<Site> cocircular{\n        Site(5, 0),\n        Site(3,\
    \ 4),\n        Site(0, 5),\n        Site(-3, 4),\n        Site(-5, 0),\n     \
    \   Site(-3, -4),\n        Site(0, -5),\n        Site(3, -4),\n    };\n    check_diagram(cocircular);\n\
    \    VoronoiDiagram eight = m1une::geometry::voronoi_diagram(cocircular);\n  \
    \  assert(eight.vertices.size() == 1);\n    assert(eight.edges.size() == 8);\n\
    \    assert(count_kind(eight, VoronoiEdgeKind::Ray) == 8);\n\n    std::vector<Site>\
    \ square_with_center = square;\n    square_with_center.emplace_back(1, 1);\n \
    \   check_diagram(square_with_center);\n    VoronoiDiagram five =\n        m1une::geometry::voronoi_diagram(square_with_center);\n\
    \    assert(five.vertices.size() == 4);\n    assert(five.edges.size() == 8);\n\
    \    assert(count_kind(five, VoronoiEdgeKind::Segment) == 4);\n    assert(count_kind(five,\
    \ VoronoiEdgeKind::Ray) == 4);\n\n    std::vector<Site> collinear{\n        Site(-5,\
    \ 3),\n        Site(-1, 3),\n        Site(2, 3),\n        Site(9, 3),\n    };\n\
    \    check_diagram(collinear);\n    VoronoiDiagram line = m1une::geometry::voronoi_diagram(collinear);\n\
    \    assert(line.vertices.empty());\n    assert(line.edges.size() == 3);\n   \
    \ assert(count_kind(line, VoronoiEdgeKind::Line) == 3);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x243f6a8885a308d3ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 1500; ++trial) {\n       \
    \ int size = int(random() % 11);\n        std::set<std::pair<long long, long long>>\
    \ used;\n        std::vector<Site> sites;\n        sites.reserve(size);\n    \
    \    while (int(sites.size()) < size) {\n            long long x = static_cast<long\
    \ long>(random() % 21) - 10;\n            long long y = static_cast<long long>(random()\
    \ % 21) - 10;\n            if (used.emplace(x, y).second) sites.emplace_back(x,\
    \ y);\n        }\n        check_diagram(sites);\n    }\n}\n\nlong double polygon_area(const\
    \ std::vector<RealPoint>& polygon) {\n    long double twice_area = 0;\n    for\
    \ (int index = 0; index < int(polygon.size()); ++index) {\n        twice_area\
    \ += m1une::geometry::cross(\n            polygon[index],\n            polygon[(index\
    \ + 1) % polygon.size()]\n        );\n    }\n    return std::fabs(twice_area)\
    \ / 2;\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    std::cout << std::fixed << std::setprecision(10);\n    while (true) {\n\
    \        int island_size, site_count;\n        std::cin >> island_size >> site_count;\n\
    \        if (island_size == 0 && site_count == 0) break;\n\n        std::vector<Site>\
    \ island(island_size);\n        for (Site& point : island) std::cin >> point.x\
    \ >> point.y;\n        std::vector<Site> sites(site_count);\n        for (Site&\
    \ point : sites) std::cin >> point.x >> point.y;\n\n        VoronoiDiagram diagram\
    \ = m1une::geometry::voronoi_diagram(sites);\n        for (int site = 0; site\
    \ < site_count; ++site) {\n            std::vector<m1une::geometry::Line<long\
    \ double>> half_planes;\n            half_planes.reserve(island_size + diagram.cell_edges[site].size());\n\
    \            for (int index = 0; index < island_size; ++index) {\n           \
    \     half_planes.push_back(m1une::geometry::Line<long double>{\n            \
    \        RealPoint(island[index]),\n                    RealPoint(island[(index\
    \ + 1) % island_size]),\n                });\n            }\n            for (int\
    \ edge_index : diagram.cell_edges[site]) {\n                const VoronoiEdge&\
    \ edge = diagram.edges[edge_index];\n                int other = edge.first_site\
    \ == site\n                    ? edge.second_site\n                    : edge.first_site;\n\
    \                RealPoint first(sites[site]);\n                RealPoint second(sites[other]);\n\
    \                RealPoint midpoint = (first + second) / 2.0L;\n             \
    \   RealPoint difference = second - first;\n                RealPoint direction(-difference.y,\
    \ difference.x);\n                half_planes.push_back(m1une::geometry::Line<long\
    \ double>{\n                    midpoint,\n                    midpoint + direction,\n\
    \                });\n            }\n\n            auto intersection =\n     \
    \           m1une::geometry::half_plane_intersection(half_planes);\n         \
    \   long double area = 0;\n            if (\n                intersection.status\
    \ ==\n                m1une::geometry::HalfPlaneIntersectionStatus::Bounded\n\
    \            ) {\n                area = polygon_area(intersection.polygon);\n\
    \            }\n            std::cout << area << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - geometry/voronoi_diagram.hpp
  - geometry/euclidean_mst.hpp
  - ds/dsu/dsu.hpp
  - geometry/point.hpp
  - geometry/half_plane_intersection.hpp
  - geometry/line.hpp
  isVerificationFile: true
  path: verify/geometry/voronoi_diagram.test.cpp
  requiredBy: []
  timestamp: '2026-07-22 14:17:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/voronoi_diagram.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/voronoi_diagram.test.cpp
- /verify/verify/geometry/voronoi_diagram.test.cpp.html
title: verify/geometry/voronoi_diagram.test.cpp
---
