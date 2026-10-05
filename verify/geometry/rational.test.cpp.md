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
    path: math/matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: Dense Matrix
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
    // Include geometry first to check that support does not depend on include order.\n\
    #include \"../../geometry/all.hpp\"\n#include \"../../math/rational.hpp\"\n#include\
    \ \"../../math/matrix/linear_algebra.hpp\"\n#include \"../../utilities/bigint.hpp\"\
    \n#include \"../../utilities/fast_io.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cmath>\n#include <cstdint>\n#include <string>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace {\n\nusing namespace m1une::geometry;\n\
    using Fraction = m1une::math::Rational<>;\nusing BigInt = m1une::utilities::BigInt;\n\
    using BigFraction = m1une::math::Rational<BigInt>;\n\nstatic_assert(Coordinate<Fraction>\
    \ && ExactCoordinate<Fraction>);\nstatic_assert(Coordinate<BigFraction> && ExactCoordinate<BigFraction>);\n\
    static_assert(!Coordinate<bool> && !Coordinate<std::string>);\nstatic_assert(!ExactCoordinate<double>);\n\
    static_assert(std::same_as<wide_type<Fraction>, Fraction>);\nstatic_assert(std::same_as<wide_type<BigFraction>,\
    \ BigFraction>);\nstatic_assert(std::same_as<wide_type<long long>, __int128_t>);\n\
    static_assert(std::same_as<wide_type<float>, long double>);\nstatic_assert(std::same_as<std::common_type_t<Fraction,\
    \ int>, Fraction>);\nstatic_assert(std::same_as<std::common_type_t<Fraction, double>,\
    \ long double>);\nstatic_assert(std::same_as<std::common_type_t<float, BigFraction>,\
    \ long double>);\nstatic_assert(!std::convertible_to<Fraction, double>);\nstatic_assert(static_cast<float>(Fraction(1,\
    \ 2)) == 0.5F);\nstatic_assert(static_cast<double>(Fraction(1, 2)) == 0.5);\n\
    static_assert(orientation(Point<Fraction>(0, 0), Point<Fraction>(1, 0),\n    \
    \                      Point<Fraction>(0, Fraction(1, 1000000000000000LL))) ==\
    \ 1);\n\ntemplate <class R>\nvoid fixed_test() {\n    using P = Point<R>;\n  \
    \  const P origin;\n    const P half(R(1, 2), R(1, 2));\n    assert(dot(half,\
    \ half) == R(1, 2));\n    assert(cross(P(R(1, 2), 0), P(0, R(1, 3))) == R(1, 6));\n\
    \    assert(distance2(origin, half) == R(1, 2));\n    assert(half * 2 == P(1,\
    \ 1));\n    assert(2 * half == P(1, 1));\n    assert(half / 2 == P(R(1, 4), R(1,\
    \ 4)));\n    assert(half * R(2, 3) == P(R(1, 3), R(1, 3)));\n    assert(R(2, 3)\
    \ * half == P(R(1, 3), R(1, 3)));\n    assert(half / R(2, 3) == P(R(3, 4), R(3,\
    \ 4)));\n    assert((half * 0.5L == Point<long double>(0.25L, 0.25L)));\n    assert((Point<int>(1,\
    \ 2) * R(1, 2) == P(R(1, 2), 1)));\n    assert((Point<float>(half) == Point<float>(0.5F,\
    \ 0.5F)));\n    assert((Point<double>(half) == Point<double>(0.5, 0.5)));\n  \
    \  assert((internal_division_point(origin, P(1, 1), R(1, 2), R(1, 2)) ==\n   \
    \         Point<long double>(0.5L, 0.5L)));\n    assert((external_division_point(origin,\
    \ P(1, 1), R(1, 2), R(1, 4)) ==\n            Point<long double>(2, 2)));\n\n \
    \   const Segment<R> singleton{half, half};\n    assert(on_segment(singleton,\
    \ half));\n    assert(!on_segment(singleton, half + P(R(1, 1000000), 0), 1));\n\
    \    const Segment<R> diagonal{origin, P(1, 1)};\n    const Segment<R> other{P(0,\
    \ 1), P(1, 0)};\n    assert(intersects(diagonal, other));\n    assert(linear_intersection(diagonal,\
    \ other).kind == LinearIntersectionKind::Point);\n    const Ray<R> ray{origin,\
    \ half};\n    assert(on_ray(ray, P(1, 1)) && !on_ray(ray, P(-1, -1)));\n    assert(intersects(ray,\
    \ other));\n    const Line<R> horizontal{origin, P(1, 0)};\n    const Line<R>\
    \ vertical{origin, P(0, 1)};\n    assert(orthogonal(horizontal, vertical));\n\
    \    assert(parallel(horizontal, Line<R>{P(0, 1), P(1, 1)}));\n    const Line<R>\
    \ bisector = perpendicular_bisector(origin, P(1, 0));\n    assert(on_line(bisector,\
    \ P(R(1, 2), 0)));\n    assert(on_line(bisector, half));\n\n    const std::vector<P>\
    \ square{origin, P(1, 0), P(1, 1), P(0, 1)};\n    const std::vector<P> points{origin,\
    \ P(1, 0), P(1, 1), P(0, 1), half};\n    assert(convex_hull(points) == square);\n\
    \    assert(polygon_area2(square) == 2);\n    assert(point_in_polygon(square,\
    \ half) == PointInPolygon::Inside);\n    const ConvexPolygon<R> polygon(square);\n\
    \    assert(polygon.contains(half) == PointInPolygon::Inside);\n    assert(convex_layers(points)\
    \ == std::vector<int>({1, 1, 1, 1, 2}));\n    assert(minkowski_sum(square, square).size()\
    \ == 4);\n    assert(convex_decomposition(square)->size() == 1);\n    assert(steiner_convex_decomposition(square)->size()\
    \ == 1);\n    const std::vector<P> concave{\n        origin, P(1, 0), P(1, R(1,\
    \ 2)), P(R(1, 2), R(1, 2)),\n        P(R(1, 2), 1), P(0, 1)\n    };\n    const\
    \ auto minimum_decomposition = minimum_convex_decomposition(concave);\n    assert(minimum_decomposition.has_value()\
    \ && minimum_decomposition->size() == 2);\n    R total_area = 0;\n    for (const\
    \ auto& piece : *minimum_decomposition) {\n        assert(is_convex_polygon(piece));\n\
    \        total_area += polygon_area2(piece);\n    }\n    assert(total_area ==\
    \ polygon_area2(concave));\n    const CountPointsInTriangle<R> counter(square,\
    \ std::vector<P>{P(R(3, 4), R(1, 4))});\n    assert(counter.query(0, 1, 2) ==\
    \ 1);\n    assert(manhattan_mst(square).cost == 3);\n    assert(euclidean_mst(square).cost\
    \ == 3);\n    assert(delaunay_triangulation(square).triangles.size() == 2);\n\
    \    assert(voronoi_diagram(square).edges.size() > 0);\n    assert(minimum_enclosing_circle(square)->support.size()\
    \ == 2);\n    std::vector<P> fractional_square = square;\n    for (P& point :\
    \ fractional_square) point = point / R(3);\n    assert(manhattan_mst(fractional_square).cost\
    \ == 1);\n    assert(std::fabs(euclidean_mst(fractional_square).cost - 1) < 1e-12L);\n\
    \    assert(delaunay_triangulation(fractional_square).triangles.size() == 2);\n\
    \    assert(!voronoi_diagram(fractional_square).edges.empty());\n\n    const std::vector<Segment<R>>\
    \ segments{\n        Segment<R>{P(R(1, 2), 0), P(R(1, 2), 1)},\n        Segment<R>{P(0,\
    \ R(1, 2)), P(1, R(1, 2))}\n    };\n    assert(manhattan_segment_intersections(segments)\
    \ == 1);\n    assert(manhattan_segment_intersection_points(segments) == std::vector<P>{half});\n\
    \    const std::vector<AxisAlignedRectangle<R>> rectangles{\n        AxisAlignedRectangle<R>(0,\
    \ R(1, 2), 0, 1),\n        AxisAlignedRectangle<R>(R(1, 4), 1, 0, 1)\n    };\n\
    \    assert(rectangle_union_area(rectangles) == 1);\n\n    const Circle<R> circle{origin,\
    \ R(1, 2)};\n    assert(point_in_circle(circle, P(R(1, 2), 0)) == PointInCircle::Boundary);\n\
    \    assert(point_in_circle(circle, P(R(1, 2) + R(1, 1000000), 0), 1) ==\n   \
    \        PointInCircle::Outside);\n    assert(on_circle(circle, P(R(1, 2), 0)));\n\
    \    assert(on_circle(circle, Point<int>(0, 0)) == false);\n    assert(circle_relation(circle,\
    \ Circle<R>{P(1, 0), R(1, 2)}) ==\n           CircleRelation::ExternallyTangent);\n\
    \    assert(intersects(circle, circle));\n\n    m1une::matrix::Matrix<R> matrix(2,\
    \ 2);\n    matrix[0][0] = R(1, 2); matrix[0][1] = R(1, 3);\n    matrix[1][0] =\
    \ 1; matrix[1][1] = -1;\n    const auto inverse = m1une::matrix::inverse(matrix);\n\
    \    assert(inverse.has_value());\n    assert(matrix * *inverse == m1une::matrix::Matrix<R>::identity(2));\n\
    }\n\n// Gift wrapping is an independent quadratic hull oracle on scaled integers.\n\
    std::vector<Point<long long>> naive_hull(std::vector<Point<long long>> points)\
    \ {\n    std::sort(points.begin(), points.end());\n    points.erase(std::unique(points.begin(),\
    \ points.end()), points.end());\n    if (points.size() < 2) return points;\n \
    \   std::vector<Point<long long>> hull;\n    int current = 0;\n    do {\n    \
    \    hull.push_back(points[current]);\n        int next = (current + 1) % int(points.size());\n\
    \        for (int i = 0; i < int(points.size()); ++i) {\n            const auto\
    \ turn = cross(points[current], points[next], points[i]);\n            if (turn\
    \ < 0 || (turn == 0 && distance2(points[current], points[next]) <\n          \
    \                              distance2(points[current], points[i]))) next =\
    \ i;\n        }\n        current = next;\n    } while (current != 0);\n    return\
    \ hull;\n}\n\ntemplate <class R>\nvoid randomized_test(int trials) {\n    using\
    \ P = Point<R>;\n    std::uint64_t state = 1307;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n    for (int trial = 0; trial < trials; ++trial) {\n       \
    \ std::vector<P> points;\n        std::vector<Point<long long>> scaled;\n    \
    \    const int size = int(random() % 20);\n        for (int i = 0; i < size; ++i)\
    \ {\n            const long long x = static_cast<long long>(random() % 41) - 20;\n\
    \            const long long y = static_cast<long long>(random() % 41) - 20;\n\
    \            const int dx = 1 + int(random() % 5), dy = 1 + int(random() % 5);\n\
    \            points.emplace_back(R(x, dx), R(y, dy));\n            scaled.emplace_back(x\
    \ * (60 / dx), y * (60 / dy));\n        }\n        const auto expected_hull =\
    \ naive_hull(scaled);\n        const auto hull = convex_hull(points);\n      \
    \  assert(hull.size() == expected_hull.size());\n        for (std::size_t i =\
    \ 0; i < hull.size(); ++i) {\n            assert(hull[i].x * 60 == expected_hull[i].x);\n\
    \            assert(hull[i].y * 60 == expected_hull[i].y);\n        }\n      \
    \  const auto nearest = closest_pair(points);\n        const auto farthest = farthest_pair(points);\n\
    \        assert(nearest.has_value() == (size >= 2));\n        assert(farthest.has_value()\
    \ == (size >= 2));\n        if (size >= 2) {\n            auto minimum = distance2(scaled[0],\
    \ scaled[1]);\n            auto maximum = minimum;\n            std::pair<int,\
    \ int> nearest_indices(0, 1);\n            for (int i = 0; i < size; ++i) {\n\
    \                for (int j = i + 1; j < size; ++j) {\n                    const\
    \ auto squared = distance2(scaled[i], scaled[j]);\n                    if (squared\
    \ < minimum) {\n                        minimum = squared;\n                 \
    \       nearest_indices = std::pair(i, j);\n                    }\n          \
    \          maximum = std::max(maximum, squared);\n                }\n        \
    \    }\n            assert(nearest->distance_squared * 3600 == static_cast<long\
    \ long>(minimum));\n            assert(std::pair(nearest->first, nearest->second)\
    \ == nearest_indices);\n            assert(farthest->distance_squared * 3600 ==\
    \ static_cast<long long>(maximum));\n        }\n        if (size >= 3) {\n   \
    \         assert(orientation(points[0], points[1], points[2], 1) ==\n        \
    \           orientation(scaled[0], scaled[1], scaled[2]));\n        }\n    }\n\
    }\n\nvoid bigint_precision_test() {\n    const BigInt power(\"1000000000000000000000000000000000000000000000000000000000000\"\
    );\n    const BigFraction base(power);\n    const BigFraction tiny(1, power);\n\
    \    using P = Point<BigFraction>;\n    const P a(base, base), b(base + 1, base),\
    \ c(base, base + tiny);\n    assert(cross(a, b, c) == tiny);\n    assert(orientation(a,\
    \ b, c) == 1);\n    assert(convex_hull(std::vector<P>{a, b, c}).size() == 3);\n\
    \    assert(sign<BigFraction>(tiny, 1) == 1);\n    const Segment<BigFraction>\
    \ singleton{a, a};\n    assert(!on_segment(singleton, c));\n    const Circle<BigFraction>\
    \ circle{P(), 1};\n    assert(!on_circle(circle, P(1 + tiny, 0)));\n    assert(point_in_circle(circle,\
    \ P(1 + tiny, 0)) == PointInCircle::Outside);\n    assert(static_cast<float>(BigFraction(1,\
    \ 2)) == 0.5F);\n    assert(static_cast<double>(BigFraction(1, 2)) == 0.5);\n\
    }\n\n}  // namespace\n\nint main() {\n    fixed_test<Fraction>();\n    fixed_test<BigFraction>();\n\
    \    randomized_test<Fraction>(1000);\n    randomized_test<BigFraction>(100);\n\
    \    bigint_precision_test();\n\n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput\
    \ output;\n    int test_count;\n    input >> test_count;\n    while (test_count--)\
    \ {\n        int size;\n        input >> size;\n        std::vector<Point<Fraction>>\
    \ points;\n        points.reserve(size);\n        for (int i = 0; i < size; ++i)\
    \ {\n            long long x, y;\n            input >> x >> y;\n            points.emplace_back(Fraction(x,\
    \ 2), Fraction(y, 2));\n        }\n        const auto hull = convex_hull(std::move(points));\n\
    \        output << hull.size() << '\\n';\n        for (const auto& point : hull)\
    \ {\n            output << (point.x * 2).numerator() << ' ' << (point.y * 2).numerator()\
    \ << '\\n';\n        }\n    }\n}\n"
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
  - math/matrix/linear_algebra.hpp
  - math/matrix/matrix.hpp
  - utilities/bigint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/geometry/rational.test.cpp
  requiredBy: []
  timestamp: '2026-10-06 02:48:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/geometry/rational.test.cpp
layout: document
redirect_from:
- /verify/verify/geometry/rational.test.cpp
- /verify/verify/geometry/rational.test.cpp.html
title: verify/geometry/rational.test.cpp
---
