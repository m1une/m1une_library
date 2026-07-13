---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
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
    path: utilities/bigint.hpp
    title: BigInt
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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

    #include "convex_hull.hpp"

    #include "convex_layers.hpp"

    #include "farthest_pair.hpp"

    #include "half_plane_intersection.hpp"

    #include "lattice_point_count.hpp"

    #include "line.hpp"

    #include "manhattan_mst.hpp"

    #include "minimum_enclosing_circle.hpp"

    #include "point.hpp"

    #include "polygon.hpp"

    #include "ray.hpp"

    #include "rectangle_union_area.hpp"


    #endif  // M1UNE_GEOMETRY_ALL_HPP

    '
  dependsOn:
  - geometry/angle_sort.hpp
  - geometry/point.hpp
  - geometry/circle.hpp
  - geometry/ray.hpp
  - geometry/line.hpp
  - geometry/closest_pair.hpp
  - geometry/convex_hull.hpp
  - geometry/convex_layers.hpp
  - geometry/farthest_pair.hpp
  - geometry/half_plane_intersection.hpp
  - geometry/lattice_point_count.hpp
  - utilities/bigint.hpp
  - geometry/manhattan_mst.hpp
  - ds/dsu/dsu.hpp
  - geometry/minimum_enclosing_circle.hpp
  - geometry/polygon.hpp
  - geometry/rectangle_union_area.hpp
  isVerificationFile: false
  path: geometry/all.hpp
  requiredBy: []
  timestamp: '2026-07-13 20:32:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/geometry/geometry_algorithms.test.cpp
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
| `geometry/point.hpp` | Points, vectors, dot/cross products, exact orientation, distance, and rotation. |
| `geometry/closest_pair.hpp` | Euclidean closest pair with original indices in $O(N\log N)$. |
| `geometry/convex_hull.hpp` | Monotone-chain convex hull with optional boundary-collinear points. |
| `geometry/convex_layers.hpp` | Onion decomposition into successive convex-hull boundaries in $O(N\log^2 N)$. |
| `geometry/farthest_pair.hpp` | Euclidean farthest pair with original indices in $O(N\log N)$. |
| `geometry/half_plane_intersection.hpp` | Bounded intersection polygon of directed closed half-planes in $O(N\log N)$. |
| `geometry/lattice_point_count.hpp` | Exact lattice-point counting in a bounded intersection of integer linear inequalities. |
| `geometry/manhattan_mst.hpp` | Manhattan minimum spanning tree for integral points in $O(N\log N)$. |
| `geometry/minimum_enclosing_circle.hpp` | Randomized linear-time minimum enclosing circle with support indices. |
| `geometry/line.hpp` | Lines, segments, projection, intersection, and distances. |
| `geometry/ray.hpp` | Rays, containment, projection, intersections, and distances with other linear objects. |
| `geometry/rectangle_union_area.hpp` | Exact union area of axis-aligned rectangles in $O(N\log N)$. |
| `geometry/polygon.hpp` | Area, centroids, triangulation, containment, ray queries, intersection, clipping, and Minkowski sums. |
| `geometry/circle.hpp` | Circle relations, line/ray intersections, and ray reflection. |

Integral predicates promote to signed 128-bit arithmetic. Constructions that
may be non-integral return `Point<long double>`.
