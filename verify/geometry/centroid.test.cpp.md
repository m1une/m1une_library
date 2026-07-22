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
    path: geometry/perpendicular_bisector.hpp
    title: Perpendicular Bisector
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
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
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A\"\
    \n\n#include \"../../geometry/all.hpp\"\n\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <cmath>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <vector>\n\nnamespace {\n\nusing namespace m1une::geometry;\nusing\
    \ P = Point<long long>;\n\nbool close(long double first, long double second) {\n\
    \    return std::fabs(first - second) <= 1e-10L;\n}\n\nvoid test_fixed() {\n \
    \   const Point<long double> point_center = centroid(P(3, -5));\n    assert(close(point_center.x,\
    \ 3));\n    assert(close(point_center.y, -5));\n\n    const Segment<long long>\
    \ segment{P(0, 2), P(6, 8)};\n    const Point<long double> segment_center = centroid(segment);\n\
    \    assert(close(segment_center.x, 3));\n    assert(close(segment_center.y, 5));\n\
    \    const Segment<long long> degenerate{P(4, 7), P(4, 7)};\n    assert(centroid(degenerate)\
    \ == Point<long double>(4, 7));\n\n    std::array<P, 3> triangle;\n    triangle[0]\
    \ = P(0, 0);\n    triangle[1] = P(6, 0);\n    triangle[2] = P(0, 3);\n    const\
    \ Point<long double> triangle_center = centroid(triangle);\n    assert(close(triangle_center.x,\
    \ 2));\n    assert(close(triangle_center.y, 1));\n\n    const Circle<long long>\
    \ circle{P(-3, 9), 5};\n    assert(centroid(circle) == Point<long double>(-3,\
    \ 9));\n\n    std::vector<P> concave;\n    concave.emplace_back(0, 0);\n    concave.emplace_back(5,\
    \ 0);\n    concave.emplace_back(5, 1);\n    concave.emplace_back(1, 1);\n    concave.emplace_back(1,\
    \ 5);\n    concave.emplace_back(0, 5);\n    const auto concave_center = centroid(concave);\n\
    \    assert(concave_center.has_value());\n    assert(close(concave_center->x,\
    \ 14.5L / 9));\n    assert(close(concave_center->y, 14.5L / 9));\n    std::reverse(concave.begin(),\
    \ concave.end());\n    const auto clockwise_center = centroid(concave);\n    assert(clockwise_center.has_value());\n\
    \    assert(close(clockwise_center->x, concave_center->x));\n    assert(close(clockwise_center->y,\
    \ concave_center->y));\n\n    std::vector<P> square;\n    square.emplace_back(0,\
    \ 0);\n    square.emplace_back(4, 0);\n    square.emplace_back(4, 2);\n    square.emplace_back(0,\
    \ 2);\n    const ConvexPolygon<long long> convex(square);\n    const auto convex_center\
    \ = centroid(convex);\n    assert(convex_center.has_value());\n    assert(close(convex_center->x,\
    \ 2));\n    assert(close(convex_center->y, 1));\n\n    std::vector<P> collinear;\n\
    \    collinear.emplace_back(0, 0);\n    collinear.emplace_back(2, 0);\n    collinear.emplace_back(7,\
    \ 0);\n    assert(!centroid(collinear).has_value());\n}\n\nvoid test_randomized_concave_polygons()\
    \ {\n    std::uint64_t state = 0x243f6a8885a308d3ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 3000; ++trial) {\n       \
    \ const long long width = 2 + static_cast<long long>(random() % 100);\n      \
    \  const long long height = 2 + static_cast<long long>(random() % 100);\n    \
    \    const long long inner_x =\n            1 + static_cast<long long>(random()\
    \ % (width - 1));\n        const long long inner_y =\n            1 + static_cast<long\
    \ long>(random() % (height - 1));\n        const long long translate_x =\n   \
    \         static_cast<long long>(random() % 201) - 100;\n        const long long\
    \ translate_y =\n            static_cast<long long>(random() % 201) - 100;\n\n\
    \        std::vector<P> polygon;\n        polygon.emplace_back(translate_x, translate_y);\n\
    \        polygon.emplace_back(translate_x + width, translate_y);\n        polygon.emplace_back(\n\
    \            translate_x + width,\n            translate_y + inner_y\n       \
    \ );\n        polygon.emplace_back(\n            translate_x + inner_x,\n    \
    \        translate_y + inner_y\n        );\n        polygon.emplace_back(\n  \
    \          translate_x + inner_x,\n            translate_y + height\n        );\n\
    \        polygon.emplace_back(translate_x, translate_y + height);\n        if\
    \ (random() % 2 != 0) std::reverse(polygon.begin(), polygon.end());\n\n      \
    \  const long double w = static_cast<long double>(width);\n        const long\
    \ double h = static_cast<long double>(height);\n        const long double x =\
    \ static_cast<long double>(inner_x);\n        const long double y = static_cast<long\
    \ double>(inner_y);\n        const long double tx = static_cast<long double>(translate_x);\n\
    \        const long double ty = static_cast<long double>(translate_y);\n     \
    \   const long double full_area = w * h;\n        const long double removed_area\
    \ = (w - x) * (h - y);\n        const long double area = full_area - removed_area;\n\
    \        const long double expected_x = tx +\n            (\n                full_area\
    \ * w / 2 -\n                removed_area * (x + w) / 2\n            ) / area;\n\
    \        const long double expected_y = ty +\n            (\n                full_area\
    \ * h / 2 -\n                removed_area * (y + h) / 2\n            ) / area;\n\
    \n        const auto result = centroid(polygon);\n        assert(result.has_value());\n\
    \        assert(close(result->x, expected_x));\n        assert(close(result->y,\
    \ expected_y));\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n\
    \    test_randomized_concave_polygons();\n\n    int size;\n    fast_input >> size;\n\
    \    std::vector<P> polygon(size);\n    for (P& point : polygon) fast_input >>\
    \ point.x >> point.y;\n    fast_output.set_fixed(1);\n    fast_output << polygon_area(polygon)\
    \ << '\\n';\n}\n"
  dependsOn:
  - geometry/all.hpp
  - geometry/angle_sort.hpp
  - geometry/point.hpp
  - geometry/circle.hpp
  - geometry/ray.hpp
  - geometry/line.hpp
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
  - geometry/minimum_enclosing_circle.hpp
  - geometry/perpendicular_bisector.hpp
  - geometry/rectangle_union_area.hpp
  - geometry/steiner_convex_decomposition.hpp
  - geometry/voronoi_diagram.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/centroid.test.cpp
  requiredBy: []
  timestamp: '2026-07-22 14:57:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/centroid.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/centroid.test.cpp
- /verify/verify/geometry/centroid.test.cpp.html
title: verify/geometry/centroid.test.cpp
---
