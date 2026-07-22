---
title: Geometry Bundle
documentation_of: ../../geometry/all.hpp
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
