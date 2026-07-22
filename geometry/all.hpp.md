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
    path: geometry/manhattan_segment_intersections.hpp
    title: Manhattan Segment Intersections
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
    path: utilities/int256.hpp
    title: Int256
  - icon: ':heavy_check_mark:'
    path: utilities/int512.hpp
    title: Int512
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/geometry/centroid.test.cpp
    title: verify/geometry/centroid.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ geometry/lattice_point_count.hpp: line 28: unable to process #include in #if\
    \ / #ifdef / #ifndef other than include guards\n"
  code: '#ifndef M1UNE_GEOMETRY_ALL_HPP

    #define M1UNE_GEOMETRY_ALL_HPP 1


    #include "angle_sort.hpp"

    #include "circle.hpp"

    #include "closest_pair.hpp"

    #include "convex_decomposition.hpp"

    #include "convex_hull.hpp"

    #include "convex_layers.hpp"

    #include "convex_polygon.hpp"

    #include "count_points_in_triangle.hpp"

    #include "delaunay_triangulation.hpp"

    #include "euclidean_mst.hpp"

    #include "farthest_pair.hpp"

    #include "half_plane_intersection.hpp"

    #include "lattice_point_count.hpp"

    #include "line.hpp"

    #include "manhattan_mst.hpp"

    #include "manhattan_segment_intersections.hpp"

    #include "minimum_enclosing_circle.hpp"

    #include "perpendicular_bisector.hpp"

    #include "point.hpp"

    #include "polygon.hpp"

    #include "ray.hpp"

    #include "rectangle_union_area.hpp"

    #include "steiner_convex_decomposition.hpp"

    #include "voronoi_diagram.hpp"


    #endif  // M1UNE_GEOMETRY_ALL_HPP

    '
  dependsOn:
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
  - geometry/manhattan_segment_intersections.hpp
  - ds/range_query/fenwick_tree.hpp
  - geometry/minimum_enclosing_circle.hpp
  - geometry/perpendicular_bisector.hpp
  - geometry/rectangle_union_area.hpp
  - geometry/steiner_convex_decomposition.hpp
  - geometry/voronoi_diagram.hpp
  isVerificationFile: false
  path: geometry/all.hpp
  requiredBy: []
  timestamp: '2026-07-22 15:13:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/centroid.test.cpp
documentation_of: geometry/all.hpp
layout: document
title: Geometry Bundle
---

## Overview

`geometry/all.hpp` includes the complete 2D geometry module.

## Included Headers

| Header | Contents |
| --- | --- |
| `geometry/angle_sort.hpp` | Atan-free counterclockwise angle sorting around an arbitrary origin. |
| `geometry/point.hpp` | Points, vectors, dot/cross products, exact orientation, distance, centroid, and rotation. |
| `geometry/closest_pair.hpp` | Euclidean closest pair with original indices in $O(N\log N)$. |
| `geometry/convex_decomposition.hpp` | Hertel--Mehlhorn approximate and Keil--Snoeyink minimum convex decompositions of a simple polygon. |
| `geometry/convex_hull.hpp` | Monotone-chain convex hull with optional boundary-collinear points. |
| `geometry/convex_layers.hpp` | Onion decomposition into successive convex-hull boundaries in $O(N\log^2 N)$. |
| `geometry/convex_polygon.hpp` | Normalized convex-polygon queries, centroid, cuts, diameter, intersections, distance, triangulation, and Minkowski sums. |
| `geometry/count_points_in_triangle.hpp` | Preprocessed strict point counts for indexed triangle queries in $O(1)$ per query. |
| `geometry/delaunay_triangulation.hpp` | Exact Delaunay edges and counterclockwise triangular faces for integral points in $O(N\log N)$. |
| `geometry/euclidean_mst.hpp` | Euclidean minimum spanning tree for integral points in $O(N\log N)$. |
| `geometry/farthest_pair.hpp` | Euclidean farthest pair with original indices in $O(N\log N)$. |
| `geometry/half_plane_intersection.hpp` | Bounded intersection polygon of directed closed half-planes in $O(N\log N)$. |
| `geometry/lattice_point_count.hpp` | Exact lattice-point counting in a bounded intersection of integer linear inequalities. |
| `geometry/manhattan_mst.hpp` | Manhattan minimum spanning tree for integral points in $O(N\log N)$. |
| `geometry/manhattan_segment_intersections.hpp` | Counts or enumerates intersections of axis-aligned integral segments. |
| `geometry/minimum_enclosing_circle.hpp` | Randomized linear-time minimum enclosing circle with support indices. |
| `geometry/line.hpp` | Lines, segments, segment centroid, projection, intersection, and distances. |
| `geometry/perpendicular_bisector.hpp` | Floating-point and lattice-point perpendicular bisectors of two distinct points. |
| `geometry/ray.hpp` | Rays, containment, projection, intersections, and distances with other linear objects. |
| `geometry/rectangle_union_area.hpp` | Exact union area of axis-aligned rectangles in $O(N\log N)$. |
| `geometry/steiner_convex_decomposition.hpp` | Floating-point Steiner convex decomposition with an exact union and a strict 2-approximation piece count. |
| `geometry/voronoi_diagram.hpp` | Exact-topology Euclidean Voronoi diagrams with segments, rays, lines, and per-site boundary edges in $O(N\log N)$. |
| `geometry/polygon.hpp` | General polygon area, centroids, triangulation, containment, ray queries, intersection, and distance. |
| `geometry/circle.hpp` | Circle centroid, relations, line/ray intersections, and ray reflection. |

Integral predicates promote to signed 128-bit arithmetic. Constructions that
may be non-integral return `Point<long double>`.

## Centroid overloads

The bounded geometry types share the free function name `centroid`:

```cpp
template <Coordinate T>
Point<long double> centroid(const Point<T>& point);

template <Coordinate T>
Point<long double> centroid(const Segment<T>& segment);

template <Coordinate T>
Point<long double> centroid(
    const std::array<Point<T>, 3>& triangle
);

template <Coordinate T>
Point<long double> centroid(const Circle<T>& circle);

template <Coordinate T>
std::optional<Point<long double>> centroid(
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
);

template <Coordinate T>
std::optional<Point<long double>> centroid(
    const ConvexPolygon<T>& polygon,
    long double eps = 1e-12L
);
```

Point, segment, triangle, and circle centroids take $O(1)$ time. Polygon
centroids take $O(N)$ and use uniform filled-area density. The vector overload
accepts any simple polygon, including concave and clockwise boundaries. It
returns `nullopt` for zero signed area; the convex query-object overload has
the same behavior for empty, point, or segment objects.

Infinite lines and rays are unbounded, so they intentionally have no centroid
overload.
