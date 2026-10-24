---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree.hpp
    title: Fenwick Tree (Binary Indexed Tree)
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  - icon: ':heavy_check_mark:'
    path: geometry/angle_sort.hpp
    title: Angle Sort
  - icon: ':heavy_check_mark:'
    path: geometry/circle.hpp
    title: Circles
  - icon: ':heavy_check_mark:'
    path: geometry/circle_coverage_areas.hpp
    title: Circle Coverage Areas
  - icon: ':heavy_check_mark:'
    path: geometry/circle_union_area.hpp
    title: Area of Union of Circles
  - icon: ':heavy_check_mark:'
    path: geometry/closest_pair.hpp
    title: Closest Pair of Points
  - icon: ':heavy_check_mark:'
    path: geometry/convex_decomposition.hpp
    title: Convex Decomposition
  - icon: ':heavy_check_mark:'
    path: geometry/convex_hull.hpp
    title: Convex Hull
  - icon: ':heavy_check_mark:'
    path: geometry/convex_layers.hpp
    title: Convex Layers
  - icon: ':heavy_check_mark:'
    path: geometry/convex_polygon.hpp
    title: Convex Polygons
  - icon: ':heavy_check_mark:'
    path: geometry/count_points_in_triangle.hpp
    title: Count Points in Triangle
  - icon: ':heavy_check_mark:'
    path: geometry/delaunay_triangulation.hpp
    title: Delaunay Triangulation
  - icon: ':heavy_check_mark:'
    path: geometry/detail/convex_polygon_normalize.hpp
    title: geometry/detail/convex_polygon_normalize.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/detail/floating_predicate.hpp
    title: geometry/detail/floating_predicate.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/euclidean_mst.hpp
    title: Euclidean Minimum Spanning Tree
  - icon: ':heavy_check_mark:'
    path: geometry/farthest_pair.hpp
    title: Farthest Pair of Points
  - icon: ':heavy_check_mark:'
    path: geometry/half_plane_intersection.hpp
    title: Half-Plane Intersection
  - icon: ':heavy_check_mark:'
    path: geometry/lattice_point_count.hpp
    title: Lattice-Point Count
  - icon: ':heavy_check_mark:'
    path: geometry/linear.hpp
    title: Linear Objects
  - icon: ':heavy_check_mark:'
    path: geometry/manhattan_mst.hpp
    title: Manhattan Minimum Spanning Tree
  - icon: ':heavy_check_mark:'
    path: geometry/manhattan_segment_intersections.hpp
    title: Manhattan Segment Intersections
  - icon: ':heavy_check_mark:'
    path: geometry/minimum_enclosing_circle.hpp
    title: Minimum Enclosing Circle
  - icon: ':heavy_check_mark:'
    path: geometry/minkowski_sum.hpp
    title: Minkowski Sum
  - icon: ':heavy_check_mark:'
    path: geometry/perpendicular_bisector.hpp
    title: Perpendicular Bisector
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/polygon.hpp
    title: Polygons
  - icon: ':heavy_check_mark:'
    path: geometry/rectangle_union_area.hpp
    title: Area of Union of Rectangles
  - icon: ':heavy_check_mark:'
    path: geometry/steiner_convex_decomposition.hpp
    title: Steiner Convex Decomposition
  - icon: ':heavy_check_mark:'
    path: geometry/voronoi_diagram.hpp
    title: Voronoi Diagram
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/rational.hpp
    title: Rational Number
  - icon: ':heavy_check_mark:'
    path: utilities/bigint.hpp
    title: BigInt
  - icon: ':heavy_check_mark:'
    path: utilities/detail/fixed_int.hpp
    title: utilities/detail/fixed_int.hpp
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  - icon: ':heavy_check_mark:'
    path: utilities/int256.hpp
    title: Int256
  - icon: ':heavy_check_mark:'
    path: utilities/int512.hpp
    title: Int512
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_convex_hull
    links:
    - https://judge.yosupo.jp/problem/static_convex_hull
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ geometry/lattice_point_count.hpp: line 28: unable to process #include in #if\
    \ / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_convex_hull\"\n\n\
    #include \"../../geometry/all.hpp\"\n#include \"../../math/rational.hpp\"\n#include\
    \ \"../../utilities/fast_io.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cmath>\n#include <memory>\n#include <random>\n#include <string>\n#include\
    \ <type_traits>\n#include <vector>\n\nnamespace {\nusing namespace m1une::geometry;\n\
    using P = Point<long long>;\n\nstruct Data {\n    int index;\n    std::string\
    \ color;\n    Data() = delete;\n    Data(int index, std::string color) : index(index),\
    \ color(std::move(color)) {}\n};\nusing Record = PointWithData<long long, Data>;\n\
    \n// Deliberately order and compare metadata: geometric algorithms must ignore\
    \ it.\nstruct Vertex : P {\n    int index;\n    explicit Vertex(long long x, long\
    \ long y, int index)\n        : P(x, y), index(index) {}\n    bool operator==(const\
    \ Vertex&) const = default;\n    bool operator<(const Vertex& other) const { return\
    \ index < other.index; }\n};\n\nstatic_assert(PointRecord<P> && PointRecord<Record>\
    \ && PointRecord<Vertex>);\nstatic_assert(!PointRecord<int>);\nstatic_assert(!std::default_initializable<Record>);\n\
    static_assert(std::same_as<decltype(Record(1, 2, Data(0, \"red\")) * 2), P>);\n\
    \nvoid test_records() {\n    std::vector<Record> points;\n    points.emplace_back(0,\
    \ 0, Data(7, \"red\"));\n    points.emplace_back(2, 0, Data(3, \"green\"));\n\
    \    points.emplace_back(0, 2, Data(5, \"blue\"));\n    points.emplace_back(0,\
    \ 0, Data(1, \"yellow\"));\n    const auto hull = convex_hull(points);\n    static_assert(std::same_as<std::remove_cv_t<decltype(hull)>,\
    \ std::vector<Record>>);\n    assert(hull.size() == 3);\n    assert(hull[0].data.index\
    \ == 7 && hull[0].data.color == \"red\");\n    assert(hull[1].data.index == 3\
    \ && hull[2].data.index == 5);\n    assert(points[3].data.color == \"yellow\"\
    );\n    assert(points[0] == points[3]);\n    assert(orientation(points[0], points[1],\
    \ points[2]) == 1);\n    assert(distance2(points[1], points[2]) == 8);\n    assert(Point<long\
    \ double>(points[1]) == Point<long double>(2, 0));\n    const auto closest = closest_pair(points);\n\
    \    assert(closest && closest->first == 0 && closest->second == 3);\n    assert(polygon_area2(hull)\
    \ == 4);\n    assert(is_simple_polygon(hull));\n    assert(is_convex_polygon(hull));\n\
    \    assert(convex_diameter2(hull) == 8);\n    assert(point_in_polygon(hull, P(1,\
    \ 0)) == PointInPolygon::Boundary);\n    assert(point_in_convex_polygon(hull,\
    \ points[0]) == PointInPolygon::Boundary);\n    const auto center = centroid(hull);\n\
    \    assert(center && std::fabs(center->x - 2.0L / 3) < 1e-12L);\n    assert(polygon_center_of_gravity(hull)\
    \ == center);\n    assert(polygon_area(hull) == 2);\n    const auto normalized\
    \ = normalize_convex_polygon(hull);\n    assert(normalized[0].data.index == 7);\n\
    \    std::vector<Vertex> custom_triangle;\n    custom_triangle.emplace_back(0,\
    \ 0, 8);\n    custom_triangle.emplace_back(2, 0, 2);\n    custom_triangle.emplace_back(0,\
    \ 2, 5);\n    assert(delaunay_triangulation(custom_triangle).triangles.size()\
    \ == 1);\n    const auto triangulation = delaunay_triangulation(hull);\n    assert(triangulation.triangles.size()\
    \ == 1);\n    // Other object-building APIs can explicitly discard metadata.\n\
    \    assert(triangulate_polygon(to_points(hull))->size() == 1);\n    assert(convex_hull<long\
    \ long>(to_points(hull)).size() == 3);\n    assert(closest_pair<long long>(to_points(hull))->distance_squared\
    \ == 4);\n    assert(minimum_enclosing_circle<long long>(to_points(hull)));\n\n\
    \    PointWithData<long long, int> zero;\n    assert(zero.x == 0 && zero.y ==\
    \ 0 && zero.data == 0);\n    PointWithData<long long, int> positioned(3, 4);\n\
    \    assert(positioned.data == 0);\n    PointWithData<long long, int> from_point(P(3,\
    \ 4), 12);\n    from_point += P(1, 2);\n    assert(from_point.x == 4 && from_point.y\
    \ == 6 && from_point.data == 12);\n\n    // Index-producing queries do not require\
    \ copying or defaulting payloads.\n    std::vector<PointWithData<long long, std::unique_ptr<int>>>\
    \ owning;\n    owning.emplace_back(0, 0, std::make_unique<int>(4));\n    owning.emplace_back(2,\
    \ 0, std::make_unique<int>(9));\n    assert(closest_pair(owning)->distance_squared\
    \ == 4);\n    assert(farthest_pair(owning)->distance_squared == 4);\n    assert(convex_layers(owning)\
    \ == std::vector<int>(2, 1));\n    assert(manhattan_mst(owning).cost == 2);\n\
    \    assert(euclidean_mst(owning).cost == 2);\n    assert(minimum_enclosing_circle(owning)->circle.radius\
    \ == 1);\n    assert(*owning[0].data == 4 && *owning[1].data == 9);\n\n    using\
    \ Fraction = m1une::math::Rational<>;\n    std::vector<PointWithData<Fraction,\
    \ int>> rational;\n    rational.emplace_back(0, 0, 10);\n    rational.emplace_back(Fraction(1,\
    \ 2), 0, 20);\n    rational.emplace_back(0, Fraction(1, 3), 30);\n    const auto\
    \ rational_hull = convex_hull(rational);\n    assert(rational_hull[1].data ==\
    \ 20);\n    assert(polygon_area2(rational_hull) == Fraction(1, 6));\n    assert(closest_pair(rational)->distance_squared\
    \ == Fraction(1, 9));\n\n    std::vector<PointWithData<double, int>> floating;\n\
    \    floating.emplace_back(0, 0, 1);\n    floating.emplace_back(2, 0, 2);\n  \
    \  assert(minimum_enclosing_circle(floating)->circle.radius == 1);\n    assert(convex_layers(floating)\
    \ == std::vector<int>(2, 1));\n}\n\nvoid test_random() {\n    std::mt19937 random(712367);\n\
    \    for (int trial = 0; trial < 250; ++trial) {\n        std::vector<Vertex>\
    \ records;\n        const int n = int(random() % 25);\n        for (int i = 0;\
    \ i < n; ++i) {\n            records.emplace_back(int(random() % 13) - 6, int(random()\
    \ % 13) - 6, i);\n        }\n        const auto plain = to_points(records);\n\
    \        for (bool collinear : {false, true}) {\n            const auto hull =\
    \ convex_hull(records, collinear);\n            assert(to_points(hull) == convex_hull(plain,\
    \ collinear));\n            for (const auto& point : hull) {\n               \
    \ auto first = std::find(plain.begin(), plain.end(), static_cast<const P&>(point));\n\
    \                assert(point.index == first - plain.begin());\n            }\n\
    \            assert(convex_diameter2(hull) == convex_diameter2(to_points(hull)));\n\
    \            assert(to_points(normalize_convex_polygon(hull)) ==\n           \
    \     normalize_convex_polygon(to_points(hull)));\n        }\n        assert(convex_layers(records)\
    \ == convex_layers(plain));\n        const auto sorted = angle_sorted(records,\
    \ P(1, 2));\n        assert(to_points(sorted) == angle_sorted(plain, P(1, 2)));\n\
    \        for (const auto& point : sorted) {\n            assert(static_cast<const\
    \ P&>(point) == plain[point.index]);\n        }\n        const auto near = closest_pair(records);\n\
    \        const auto far = farthest_pair(records);\n        assert(bool(near) ==\
    \ (n >= 2) && bool(far) == (n >= 2));\n        if (n >= 2) {\n            __int128_t\
    \ minimum = distance2(plain[0], plain[1]);\n            __int128_t maximum = minimum;\n\
    \            std::pair<int, int> nearest(0, 1), farthest(0, 1);\n            for\
    \ (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {\n                auto\
    \ squared = distance2(plain[i], plain[j]);\n                if (squared < minimum)\
    \ { minimum = squared; nearest = {i, j}; }\n                if (maximum < squared)\
    \ { maximum = squared; farthest = {i, j}; }\n            }\n            assert(near->distance_squared\
    \ == minimum);\n            assert(std::pair(near->first, near->second) == nearest);\n\
    \            assert(far->distance_squared == maximum);\n            assert(std::pair(far->first,\
    \ far->second) == farthest);\n            assert(furthest_pair(records)->distance_squared\
    \ == maximum);\n        }\n        assert(manhattan_mst(records).cost == manhattan_mst(plain).cost);\n\
    \        assert(euclidean_mst(records).cost == euclidean_mst(plain).cost);\n \
    \       const auto circle = minimum_enclosing_circle(records);\n        const\
    \ auto reference = minimum_enclosing_circle(plain);\n        assert(bool(circle)\
    \ == bool(reference));\n        if (circle) {\n            assert(circle->circle.center\
    \ == reference->circle.center);\n            assert(circle->circle.radius == reference->circle.radius);\n\
    \            assert(circle->support == reference->support);\n        }\n    }\n\
    }\n}  // namespace\n\nint main() {\n    test_records();\n    test_random();\n\
    \    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \    int test_count;\n    input >> test_count;\n    while (test_count--) {\n \
    \       int n;\n        input >> n;\n        std::vector<Record> points;\n   \
    \     for (int i = 0; i < n; ++i) {\n            long long x, y;\n           \
    \ input >> x >> y;\n            points.emplace_back(x, y, Data(i, \"red\"));\n\
    \        }\n        const auto hull = convex_hull(std::move(points));\n      \
    \  output << hull.size() << '\\n';\n        for (const auto& point : hull) output\
    \ << point.x << ' ' << point.y << '\\n';\n    }\n}\n"
  dependsOn:
  - geometry/all.hpp
  - geometry/angle_sort.hpp
  - geometry/point.hpp
  - geometry/detail/floating_predicate.hpp
  - geometry/circle.hpp
  - geometry/linear.hpp
  - geometry/circle_coverage_areas.hpp
  - geometry/circle_union_area.hpp
  - geometry/closest_pair.hpp
  - geometry/convex_decomposition.hpp
  - utilities/int256.hpp
  - utilities/detail/fixed_int.hpp
  - utilities/int512.hpp
  - geometry/polygon.hpp
  - geometry/convex_hull.hpp
  - geometry/convex_layers.hpp
  - geometry/convex_polygon.hpp
  - geometry/half_plane_intersection.hpp
  - geometry/minkowski_sum.hpp
  - geometry/detail/convex_polygon_normalize.hpp
  - geometry/point.hpp
  - geometry/count_points_in_triangle.hpp
  - geometry/delaunay_triangulation.hpp
  - geometry/euclidean_mst.hpp
  - ds/dsu/dsu.hpp
  - geometry/farthest_pair.hpp
  - geometry/lattice_point_count.hpp
  - utilities/bigint.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - geometry/manhattan_mst.hpp
  - geometry/manhattan_segment_intersections.hpp
  - ds/range_query/fenwick_tree.hpp
  - geometry/minimum_enclosing_circle.hpp
  - geometry/perpendicular_bisector.hpp
  - geometry/rectangle_union_area.hpp
  - geometry/steiner_convex_decomposition.hpp
  - geometry/voronoi_diagram.hpp
  - math/rational.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/point_data.test.cpp
  requiredBy: []
  timestamp: '2026-10-24 23:29:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/point_data.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/point_data.test.cpp
- /verify/verify/geometry/point_data.test.cpp.html
title: verify/geometry/point_data.test.cpp
---
