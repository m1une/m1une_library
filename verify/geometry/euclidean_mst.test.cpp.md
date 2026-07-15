---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: geometry/euclidean_mst.hpp
    title: Euclidean Minimum Spanning Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/euclidean_mst
    links:
    - https://judge.yosupo.jp/problem/euclidean_mst
  bundledCode: "#line 1 \"verify/geometry/euclidean_mst.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/euclidean_mst\"\n\n#line 1 \"geometry/euclidean_mst.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <concepts>\n\
    #include <cstddef>\n#include <limits>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#line 5 \"ds/dsu/dsu.hpp\"\
    \n#include <numeric>\n#line 8 \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\nstruct Dsu {\n   private:\n    int _n;\n    // parent_or_size[i] is\
    \ the parent of i if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i]\
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
    }  // namespace m1une\n\n\n#line 4 \"verify/geometry/euclidean_mst.test.cpp\"\n\
    \n#line 8 \"verify/geometry/euclidean_mst.test.cpp\"\n#include <cstdint>\n#line\
    \ 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n#line\
    \ 7 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line 10\
    \ \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#line 15 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
    template <class T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate\
    \ <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \    int _position;\n    int _length;\n\n    bool prepare_number() {\n       \
    \ if (_length - _position >= 64) return true;\n        const int remaining = _length\
    \ - _position;\n        if (remaining > 0) std::memmove(_buffer, _buffer + _position,\
    \ remaining);\n        const int added = int(std::fread(_buffer + remaining, 1,\
    \ buffer_size - remaining, _stream));\n        _position = 0;\n        _length\
    \ = remaining + added;\n        if (_length < buffer_size) _buffer[_length] =\
    \ '\\0';\n        return _length != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE*\
    \ stream = stdin)\n        : _stream(stream), _position(0), _length(0) {}\n\n\
    \    FastInput(const FastInput&) = delete;\n    FastInput& operator=(const FastInput&)\
    \ = delete;\n\n    int read_char_raw() {\n        if (_position == _length) {\n\
    \            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n  \
    \          _position = 0;\n            if (_length == 0) return EOF;\n       \
    \ }\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces() {\n\
    \        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c = read_char_raw();\n\
    \        if (c == EOF) return false;\n        --_position;\n        return true;\n\
    \    }\n\n    bool read(char& value) {\n        if (!skip_spaces()) return false;\n\
    \        value = char(read_char_raw());\n        return true;\n    }\n\n    bool\
    \ read(std::string& value) {\n        if (!skip_spaces()) return false;\n    \
    \    value.clear();\n        int c = read_char_raw();\n        while (c != EOF\
    \ && c > ' ') {\n            value.push_back(char(c));\n            c = read_char_raw();\n\
    \        }\n        return true;\n    }\n\n    bool read(bool& value) {\n    \
    \    int x;\n        if (!read(x)) return false;\n        value = x != 0;\n  \
    \      return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
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
    \ template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
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
    \n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\n\
    \          _position(0),\n          _precision(6),\n          _float_format(std::chars_format::general)\
    \ {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput& operator=(const\
    \ FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n    }\n\n \
    \   void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \        write(value.val());\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>\n\
    \    >\n    write(const Range& range) {\n        using StoredValue = internal::range_stored_value_t<const\
    \ Range>;\n        constexpr bool nested = internal::is_range_v<StoredValue>\n\
    \                                && !internal::is_string_like_v<StoredValue>;\n\
    \n        bool first = true;\n        for (const auto& value : range) {\n    \
    \        if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void set_precision(int\
    \ precision) {\n        _precision = precision;\n    }\n\n    void set_fixed(int\
    \ precision = 6) {\n        _float_format = std::chars_format::fixed;\n      \
    \  _precision = precision;\n    }\n\n    void set_general(int precision = 6) {\n\
    \        _float_format = std::chars_format::general;\n        _precision = precision;\n\
    \    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n\n    template\
    \ <class T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n\
    \        return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 11 \"verify/geometry/euclidean_mst.test.cpp\"\n\n#line 13 \"\
    verify/geometry/euclidean_mst.test.cpp\"\n\nnamespace {\n\nusing Point = m1une::geometry::Point<long\
    \ long>;\nusing Wide = __int128_t;\n\nWide squared_distance(const Point& a, const\
    \ Point& b) {\n    return m1une::geometry::distance2(a, b);\n}\n\nstd::vector<Wide>\
    \ brute_force_weights(const std::vector<Point>& points) {\n    struct Edge {\n\
    \        int from;\n        int to;\n        Wide squared_distance;\n    };\n\n\
    \    std::vector<Edge> edges;\n    for (int i = 0; i < int(points.size()); i++)\
    \ {\n        for (int j = 0; j < i; j++) {\n            edges.push_back(Edge{i,\
    \ j, squared_distance(points[i], points[j])});\n        }\n    }\n    std::sort(edges.begin(),\
    \ edges.end(), [](const Edge& left, const Edge& right) {\n        return left.squared_distance\
    \ < right.squared_distance;\n    });\n\n    m1une::ds::Dsu dsu(int(points.size()));\n\
    \    std::vector<Wide> result;\n    for (const auto& edge : edges) {\n       \
    \ if (dsu.same(edge.from, edge.to)) continue;\n        dsu.merge(edge.from, edge.to);\n\
    \        result.push_back(edge.squared_distance);\n    }\n    std::sort(result.begin(),\
    \ result.end());\n    return result;\n}\n\nvoid check(const std::vector<Point>&\
    \ points) {\n    auto candidates = m1une::geometry::euclidean_mst_edges(points);\n\
    \    assert(candidates.size() <= 4 * points.size());\n    for (const auto& edge\
    \ : candidates) {\n        assert(0 <= edge.from && edge.from < int(points.size()));\n\
    \        assert(0 <= edge.to && edge.to < int(points.size()));\n        assert(edge.from\
    \ != edge.to);\n        assert(edge.squared_distance == squared_distance(points[edge.from],\
    \ points[edge.to]));\n    }\n\n    auto mst = m1une::geometry::euclidean_mst(points);\n\
    \    assert(mst.edges.size() == (points.empty() ? 0 : points.size() - 1));\n \
    \   m1une::ds::Dsu dsu(int(points.size()));\n    std::vector<Wide> weights;\n\
    \    long double cost = 0;\n    for (const auto& edge : mst.edges) {\n       \
    \ assert(!dsu.same(edge.from, edge.to));\n        dsu.merge(edge.from, edge.to);\n\
    \        weights.push_back(edge.squared_distance);\n        cost += std::sqrt(static_cast<long\
    \ double>(edge.squared_distance));\n    }\n    std::sort(weights.begin(), weights.end());\n\
    \    assert(weights == brute_force_weights(points));\n    assert(std::abs(mst.cost\
    \ - cost) <= 1e-12L * (1 + cost));\n}\n\nvoid test_fixed() {\n    check({});\n\
    \    check({Point(2, -3)});\n    check({Point(0, 0), Point(0, 0), Point(0, 0)});\n\
    \    check({Point(-5, 0), Point(-2, 0), Point(1, 0), Point(7, 0)});\n    check({Point(0,\
    \ 0), Point(1, 0), Point(1, 1), Point(0, 1)});\n    check({\n        Point(0,\
    \ 0),\n        Point(2, 0),\n        Point(2, 2),\n        Point(0, 2),\n    \
    \    Point(1, 1),\n        Point(1, 1),\n    });\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260714;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 3000; trial++) {\n        int size\
    \ = int(random() % 15);\n        std::vector<Point> points;\n        points.reserve(size);\n\
    \        for (int i = 0; i < size; i++) {\n            points.emplace_back(\n\
    \                static_cast<long long>(random() % 21) - 10,\n               \
    \ static_cast<long long>(random() % 21) - 10\n            );\n        }\n    \
    \    check(points);\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n\
    \    test_randomized();\n\n    int n;\n    fast_input >> n;\n    std::vector<Point>\
    \ points;\n    points.reserve(n);\n    for (int i = 0; i < n; i++) {\n       \
    \ long long x, y;\n        fast_input >> x >> y;\n        points.emplace_back(x,\
    \ y);\n    }\n\n    auto mst = m1une::geometry::euclidean_mst(points);\n    for\
    \ (const auto& edge : mst.edges) {\n        fast_output << edge.from << ' ' <<\
    \ edge.to << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/euclidean_mst\"\n\n#include\
    \ \"../../geometry/euclidean_mst.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cmath>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <vector>\n\n#include \"../../ds/dsu/dsu.hpp\"\n\nnamespace {\n\nusing\
    \ Point = m1une::geometry::Point<long long>;\nusing Wide = __int128_t;\n\nWide\
    \ squared_distance(const Point& a, const Point& b) {\n    return m1une::geometry::distance2(a,\
    \ b);\n}\n\nstd::vector<Wide> brute_force_weights(const std::vector<Point>& points)\
    \ {\n    struct Edge {\n        int from;\n        int to;\n        Wide squared_distance;\n\
    \    };\n\n    std::vector<Edge> edges;\n    for (int i = 0; i < int(points.size());\
    \ i++) {\n        for (int j = 0; j < i; j++) {\n            edges.push_back(Edge{i,\
    \ j, squared_distance(points[i], points[j])});\n        }\n    }\n    std::sort(edges.begin(),\
    \ edges.end(), [](const Edge& left, const Edge& right) {\n        return left.squared_distance\
    \ < right.squared_distance;\n    });\n\n    m1une::ds::Dsu dsu(int(points.size()));\n\
    \    std::vector<Wide> result;\n    for (const auto& edge : edges) {\n       \
    \ if (dsu.same(edge.from, edge.to)) continue;\n        dsu.merge(edge.from, edge.to);\n\
    \        result.push_back(edge.squared_distance);\n    }\n    std::sort(result.begin(),\
    \ result.end());\n    return result;\n}\n\nvoid check(const std::vector<Point>&\
    \ points) {\n    auto candidates = m1une::geometry::euclidean_mst_edges(points);\n\
    \    assert(candidates.size() <= 4 * points.size());\n    for (const auto& edge\
    \ : candidates) {\n        assert(0 <= edge.from && edge.from < int(points.size()));\n\
    \        assert(0 <= edge.to && edge.to < int(points.size()));\n        assert(edge.from\
    \ != edge.to);\n        assert(edge.squared_distance == squared_distance(points[edge.from],\
    \ points[edge.to]));\n    }\n\n    auto mst = m1une::geometry::euclidean_mst(points);\n\
    \    assert(mst.edges.size() == (points.empty() ? 0 : points.size() - 1));\n \
    \   m1une::ds::Dsu dsu(int(points.size()));\n    std::vector<Wide> weights;\n\
    \    long double cost = 0;\n    for (const auto& edge : mst.edges) {\n       \
    \ assert(!dsu.same(edge.from, edge.to));\n        dsu.merge(edge.from, edge.to);\n\
    \        weights.push_back(edge.squared_distance);\n        cost += std::sqrt(static_cast<long\
    \ double>(edge.squared_distance));\n    }\n    std::sort(weights.begin(), weights.end());\n\
    \    assert(weights == brute_force_weights(points));\n    assert(std::abs(mst.cost\
    \ - cost) <= 1e-12L * (1 + cost));\n}\n\nvoid test_fixed() {\n    check({});\n\
    \    check({Point(2, -3)});\n    check({Point(0, 0), Point(0, 0), Point(0, 0)});\n\
    \    check({Point(-5, 0), Point(-2, 0), Point(1, 0), Point(7, 0)});\n    check({Point(0,\
    \ 0), Point(1, 0), Point(1, 1), Point(0, 1)});\n    check({\n        Point(0,\
    \ 0),\n        Point(2, 0),\n        Point(2, 2),\n        Point(0, 2),\n    \
    \    Point(1, 1),\n        Point(1, 1),\n    });\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260714;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 3000; trial++) {\n        int size\
    \ = int(random() % 15);\n        std::vector<Point> points;\n        points.reserve(size);\n\
    \        for (int i = 0; i < size; i++) {\n            points.emplace_back(\n\
    \                static_cast<long long>(random() % 21) - 10,\n               \
    \ static_cast<long long>(random() % 21) - 10\n            );\n        }\n    \
    \    check(points);\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n\
    \    test_randomized();\n\n    int n;\n    fast_input >> n;\n    std::vector<Point>\
    \ points;\n    points.reserve(n);\n    for (int i = 0; i < n; i++) {\n       \
    \ long long x, y;\n        fast_input >> x >> y;\n        points.emplace_back(x,\
    \ y);\n    }\n\n    auto mst = m1une::geometry::euclidean_mst(points);\n    for\
    \ (const auto& edge : mst.edges) {\n        fast_output << edge.from << ' ' <<\
    \ edge.to << '\\n';\n    }\n}\n"
  dependsOn:
  - geometry/euclidean_mst.hpp
  - ds/dsu/dsu.hpp
  - geometry/point.hpp
  - utilities/fast_io.hpp
  - ds/dsu/dsu.hpp
  isVerificationFile: true
  path: verify/geometry/euclidean_mst.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/euclidean_mst.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/euclidean_mst.test.cpp
- /verify/verify/geometry/euclidean_mst.test.cpp.html
title: verify/geometry/euclidean_mst.test.cpp
---
