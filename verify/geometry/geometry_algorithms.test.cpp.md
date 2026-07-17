---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
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
    path: geometry/closest_pair.hpp
    title: Closest Pair of Points
  - icon: ':heavy_check_mark:'
    path: geometry/convex_hull.hpp
    title: Convex Hull
  - icon: ':heavy_check_mark:'
    path: geometry/convex_layers.hpp
    title: Convex Layers
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
    path: geometry/line.hpp
    title: Lines and Segments
  - icon: ':heavy_check_mark:'
    path: geometry/manhattan_mst.hpp
    title: Manhattan Minimum Spanning Tree
  - icon: ':heavy_check_mark:'
    path: geometry/minimum_enclosing_circle.hpp
    title: Minimum Enclosing Circle
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: 2D Point and Predicates
  - icon: ':heavy_check_mark:'
    path: geometry/polygon.hpp
    title: Polygons
  - icon: ':heavy_check_mark:'
    path: geometry/ray.hpp
    title: Rays
  - icon: ':heavy_check_mark:'
    path: geometry/rectangle_union_area.hpp
    title: Area of Union of Rectangles
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
    path: utilities/bigint.hpp
    title: BigInt
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
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
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../geometry/all.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cmath>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include\
    \ <vector>\n\nnamespace {\n\nbool close(long double a, long double b) {\n    return\
    \ std::fabs(a - b) <= 1e-10L;\n}\n\nvoid test_basic() {\n    using namespace m1une::geometry;\n\
    \    using P = Point<long long>;\n\n    P a(0, 0);\n    P b(3, 0);\n    P c(1,\
    \ 2);\n    assert(cross(a, b, c) == 6);\n    assert(orientation(a, b, c) == 1);\n\
    \    assert(orientation(a, c, b) == -1);\n    assert(collinear(a, P(1, 0), b));\n\
    \n    P division_start(0, 2);\n    P division_end(10, 12);\n    Point<long double>\
    \ internal =\n        internal_division_point(division_start, division_end, 2,\
    \ 3);\n    assert(close(internal.x, 4));\n    assert(close(internal.y, 6));\n\n\
    \    Point<long double> external_after =\n        external_division_point(division_start,\
    \ division_end, 2, 1);\n    assert(close(external_after.x, 20));\n    assert(close(external_after.y,\
    \ 22));\n\n    Point<long double> external_before =\n        external_division_point(division_start,\
    \ division_end, 1, 2);\n    assert(close(external_before.x, -10));\n    assert(close(external_before.y,\
    \ -8));\n\n    Segment<long long> first;\n    first.a = P(0, 0);\n    first.b\
    \ = P(4, 4);\n    Segment<long long> second;\n    second.a = P(0, 4);\n    second.b\
    \ = P(4, 0);\n    assert(intersects(first, second));\n    assert(close(distance(first,\
    \ second), 0));\n\n    Line<long long> horizontal;\n    horizontal.a = P(0, 0);\n\
    \    horizontal.b = P(4, 0);\n    [[maybe_unused]] Point<long double> projected\
    \ = projection(horizontal, P(2, 3));\n    assert(close(projected.x, 2));\n   \
    \ assert(close(projected.y, 0));\n\n    Line<long long> diagonal1;\n    diagonal1.a\
    \ = P(0, 0);\n    diagonal1.b = P(2, 2);\n    Line<long long> diagonal2;\n   \
    \ diagonal2.a = P(0, 2);\n    diagonal2.b = P(2, 0);\n    [[maybe_unused]] auto\
    \ crossing = line_intersection(diagonal1, diagonal2);\n    assert(crossing.has_value());\n\
    \    assert(close(crossing->x, 1));\n    assert(close(crossing->y, 1));\n\n  \
    \  std::vector<P> square;\n    square.emplace_back(0, 0);\n    square.emplace_back(2,\
    \ 0);\n    square.emplace_back(2, 2);\n    square.emplace_back(0, 2);\n    assert(polygon_area2(square)\
    \ == 8);\n    assert(point_in_polygon(square, P(1, 1)) == PointInPolygon::Inside);\n\
    \    assert(point_in_polygon(square, P(0, 1)) == PointInPolygon::Boundary);\n\
    \    assert(point_in_polygon(square, P(3, 1)) == PointInPolygon::Outside);\n \
    \   assert(convex_diameter2(square) == 8);\n\n    Circle<long double> circle;\n\
    \    circle.center = Point<long double>(0, 0);\n    circle.radius = 2;\n    Line<long\
    \ double> line;\n    line.a = Point<long double>(-3, 0);\n    line.b = Point<long\
    \ double>(3, 0);\n    auto intersections = circle_line_intersections(circle, line);\n\
    \    assert(intersections.size() == 2);\n    assert(close(intersections[0].x,\
    \ -2));\n    assert(close(intersections[1].x, 2));\n\n    Circle<long double>\
    \ other;\n    other.center = Point<long double>(3, 0);\n    other.radius = 2;\n\
    \    assert(circle_relation(circle, other) == CircleRelation::Intersecting);\n\
    \    auto circle_points = circle_intersections(circle, other);\n    assert(circle_points.size()\
    \ == 2);\n    for ([[maybe_unused]] const auto& point : circle_points) {\n   \
    \     assert(close(distance(point, circle.center), circle.radius));\n        assert(close(distance(point,\
    \ other.center), other.radius));\n    }\n\n    std::vector<P> collinear_points;\n\
    \    collinear_points.emplace_back(2, 0);\n    collinear_points.emplace_back(0,\
    \ 0);\n    collinear_points.emplace_back(1, 0);\n    assert(convex_hull(collinear_points).size()\
    \ == 2);\n    assert(convex_hull(collinear_points, true) == std::vector<P>({P(0,\
    \ 0), P(1, 0), P(2, 0)}));\n}\n\nvoid test_randomized_hulls() {\n    using namespace\
    \ m1une::geometry;\n    using P = Point<long long>;\n    std::uint64_t state =\
    \ 41;\n    auto random = [&state]() {\n        state ^= state << 7;\n        state\
    \ ^= state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 3000; trial++) {\n        int n = int(random() % 30);\n        std::vector<P>\
    \ points;\n        for (int i = 0; i < n; i++) {\n            points.emplace_back(\n\
    \                static_cast<long long>(random() % 31) - 15,\n               \
    \ static_cast<long long>(random() % 31) - 15\n            );\n        }\n    \
    \    std::vector<P> hull = convex_hull(points);\n        if (hull.size() >= 3)\
    \ {\n            assert(polygon_area2(hull) > 0);\n            for (std::size_t\
    \ i = 0; i < hull.size(); i++) {\n                assert(orientation(\n      \
    \              hull[i],\n                    hull[(i + 1) % hull.size()],\n  \
    \                  hull[(i + 2) % hull.size()]\n                ) > 0);\n    \
    \        }\n\n            auto expected_diameter = wide_type<long long>(0);\n\
    \            for (const P& a : hull) {\n                for (const P& b : hull)\
    \ {\n                    expected_diameter = std::max(expected_diameter, distance2(a,\
    \ b));\n                }\n            }\n            assert(convex_diameter2(hull)\
    \ == expected_diameter);\n        }\n\n        for ([[maybe_unused]] const P&\
    \ point : points) {\n            if (hull.size() >= 3) {\n                assert(point_in_polygon(hull,\
    \ point) != PointInPolygon::Outside);\n            } else if (hull.size() == 2)\
    \ {\n                Segment<long long> segment;\n                segment.a =\
    \ hull[0];\n                segment.b = hull[1];\n                assert(on_segment(segment,\
    \ point));\n            } else if (hull.size() == 1) {\n                assert(point\
    \ == hull[0]);\n            }\n        }\n    }\n}\n\n}  // namespace\n\nint main()\
    \ {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_basic();\n    test_randomized_hulls();\n\n    long\
    \ long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n\
    }\n"
  dependsOn:
  - geometry/all.hpp
  - geometry/angle_sort.hpp
  - geometry/point.hpp
  - geometry/circle.hpp
  - geometry/ray.hpp
  - geometry/line.hpp
  - geometry/closest_pair.hpp
  - geometry/convex_hull.hpp
  - geometry/convex_layers.hpp
  - geometry/euclidean_mst.hpp
  - ds/dsu/dsu.hpp
  - geometry/farthest_pair.hpp
  - geometry/half_plane_intersection.hpp
  - geometry/lattice_point_count.hpp
  - utilities/bigint.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - geometry/manhattan_mst.hpp
  - geometry/minimum_enclosing_circle.hpp
  - geometry/polygon.hpp
  - geometry/rectangle_union_area.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/geometry_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 04:56:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/geometry_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/geometry_algorithms.test.cpp
- /verify/verify/geometry/geometry_algorithms.test.cpp.html
title: verify/geometry/geometry_algorithms.test.cpp
---
