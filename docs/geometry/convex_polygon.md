---
title: Convex Polygons
documentation_of: ../../geometry/convex_polygon.hpp
---

## Overview

`convex_polygon.hpp` provides algorithms specialized for convex polygons and a
`ConvexPolygon<T>` query object. The query object normalizes an ordered convex
boundary once, then supports point containment, directional extrema, tangents,
and chain-area queries efficiently.

The free functions cover convexity testing, normalization, triangulation,
diameter, half-plane cuts, intersection construction, Minkowski sums, and
intersection and distance between two convex polygons. Pair queries have both
linear-time vector overloads and sublinear overloads for already-normalized
`ConvexPolygon<T>` objects. They can also return a pair of closest points,
including points in edge interiors.

Polygons are represented by `std::vector<Point<T>>`. Their first point is not
repeated at the end unless a function explicitly accepts and removes a closing
copy.

## Basic Functions

```cpp
template <Coordinate T>
bool is_convex_polygon(
    const std::vector<Point<T>>& polygon,
    bool strict = false,
    long double eps = 1e-12L
);

template <Coordinate T>
std::vector<Point<T>> normalize_convex_polygon(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
);

template <Coordinate T>
PointInPolygon point_in_convex_polygon(
    const std::vector<Point<T>>& polygon,
    const Point<T>& point,
    long double eps = 1e-12L
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `is_convex_polygon(polygon, strict, eps)` | Tests the turns of an ordered simple boundary. With `strict == true`, collinear consecutive edges and all-collinear polygons are rejected. | $O(N)$ |
| `normalize_convex_polygon(polygon, eps)` | Removes a closing copy, consecutive duplicates, and redundant collinear vertices; makes the order counterclockwise; and rotates the lowest `(y, x)` vertex to index `0`. | $O(N)$ |
| `point_in_convex_polygon(polygon, point, eps)` | Classifies a point against a strict convex boundary in clockwise or counterclockwise order. | $O(\log N)$ |

`is_convex_polygon` assumes the vertices describe a simple polygon boundary.
It is not a general self-intersection test. Use `is_simple_polygon` from
`polygon.hpp` when arbitrary input must be validated. In non-strict mode, an
all-collinear boundary with at least three vertices is considered convex.

For predictable logarithmic containment, pass a strict boundary or use
`ConvexPolygon<T>`, which normalizes the input first. Empty polygons, points,
and segments are also classified by `point_in_convex_polygon`.

## Query Object

```cpp
template <Coordinate T>
class ConvexPolygon {
public:
    using Wide = wide_type<T>;

    explicit ConvexPolygon(
        std::vector<Point<T>> polygon,
        long double eps = 1e-12L
    );

    int size() const noexcept;
    bool empty() const noexcept;
    const std::vector<Point<T>>& vertices() const noexcept;
    const Point<T>& operator[](int index) const;
    Wide area2() const;
    Wide chain_area2(int first, int last) const;
    PointInPolygon contains(const Point<T>& point) const;
    std::pair<Wide, int> min_dot(const Point<T>& direction) const;
    std::pair<Wide, int> max_dot(const Point<T>& direction) const;
    std::pair<int, int> tangent_vertices(const Point<T>& point) const;
};

template <Coordinate T>
std::optional<Point<long double>> centroid(
    const ConvexPolygon<T>& polygon,
    long double eps = 1e-12L
);
```

| Operation | Description | Complexity |
| --- | --- | --- |
| `ConvexPolygon(polygon, eps)` | Normalizes an ordered convex boundary and builds doubled prefix areas. | $O(N)$ time and memory |
| `size()`, `empty()`, `vertices()`, `operator[]` | Access the normalized boundary. | $O(1)$ |
| `area2()` | Returns signed twice-area. A nondegenerate normalized polygon has positive area. | $O(1)$ |
| `chain_area2(first, last)` | Returns signed twice-area enclosed by the counterclockwise chain from `first` through `last` and the chord back to `first`. | $O(1)$ |
| `contains(point)` | Classifies a point as `Outside`, `Boundary`, or `Inside`. | $O(\log N)$ |
| `min_dot(direction)`, `max_dot(direction)` | Returns the extreme dot product and one vertex attaining it. | $O(\log N)$ |
| `tangent_vertices(point)` | Returns the two tangent-vertex indices for an external point. | $O(\log N)$ |
| `centroid(polygon, eps)` | Returns the uniformly filled polygon's centroid, or `nullopt` for an empty or zero-area query object. | $O(N)$ |

`min_dot` and `max_dot` require a nonempty polygon. `tangent_vertices`
requires at least three vertices and a point strictly outside the polygon.
Ties may return either endpoint of an extreme edge. No ordering is promised
between the two tangent indices.

`centroid` is a free geometry-wide overload rather than a convex-only member.
The same name also supports points, segments, triangles, circles, and general
simple polygon vectors. The convex overload delegates to the general polygon
area-centroid calculation; preprocessing the query object does not make this
particular operation constant-time.

## Construction and Combination

```cpp
template <Coordinate T>
std::vector<std::array<Point<T>, 3>> triangulate_convex_polygon(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
);

template <Coordinate T>
wide_type<T> convex_diameter2(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
);

template <Coordinate T>
std::vector<Point<long double>> convex_cut(
    const std::vector<Point<T>>& polygon,
    const Line<T>& boundary,
    long double eps = 1e-12L
);

template <Coordinate T>
std::vector<Point<long double>> convex_polygon_intersection(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
std::vector<Point<T>> minkowski_sum(
    std::vector<Point<T>> first,
    std::vector<Point<T>> second,
    long double eps = 1e-12L
);

template <Coordinate T>
bool convex_polygons_intersect(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
long double convex_polygons_distance(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
std::pair<Point<long double>, Point<long double>>
convex_polygons_closest_points(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
bool convex_polygons_intersect(
    const ConvexPolygon<T>& first,
    const ConvexPolygon<T>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
long double convex_polygons_distance(
    const ConvexPolygon<T>& first,
    const ConvexPolygon<T>& second,
    long double eps = 1e-12L
);

template <Coordinate T>
std::pair<Point<long double>, Point<long double>>
convex_polygons_closest_points(
    const ConvexPolygon<T>& first,
    const ConvexPolygon<T>& second,
    long double eps = 1e-12L
);
```

### Vector overloads

| Function | Description | Complexity |
| --- | --- | --- |
| `triangulate_convex_polygon(polygon, eps)` | Returns a counterclockwise fan triangulation after normalization. | $O(N)$ |
| `convex_diameter2(polygon, eps)` | Returns the maximum squared distance between two vertices using rotating calipers. | $O(N)$ |
| `convex_cut(polygon, boundary, eps)` | Intersects the polygon with the closed half-plane to the left of the directed boundary line. | $O(N)$ |
| `convex_polygon_intersection(first, second, eps)` | Constructs the closed intersection, including point or segment degeneracies, by merging the polygons' angle-sorted half-planes. | $O(N+M)$ |
| `minkowski_sum(first, second, eps)` | Constructs the Minkowski sum and returns a normalized boundary. | $O(N+M)$ |
| `convex_polygons_intersect(first, second, eps)` | Tests whether two closed convex polygons intersect. | $O(N+M)$ |
| `convex_polygons_distance(first, second, eps)` | Returns the minimum Euclidean distance between two closed convex polygons. | $O(N+M)$ |
| `convex_polygons_closest_points(first, second, eps)` | Returns one pair of points attaining the minimum distance. | $O(N+M)$ |

The $O(N+M)$ bounds in this table apply when `first` and `second` are
`std::vector<Point<T>>`. These overloads normalize the boundaries on every
call. The intersection and distance queries materialize their Minkowski
difference; the closest-points query constructs two temporary query objects.
All three use $O(N+M)$ temporary memory.

### Preprocessed pair-query overloads

| Function | Description | Complexity |
| --- | --- | --- |
| `convex_polygons_intersect(first, second, eps)` | Tests whether two closed `ConvexPolygon<T>` objects intersect. | $O(\log(N+M)\log(\min(N,M)+1))$ time, $O(1)$ extra memory |
| `convex_polygons_distance(first, second, eps)` | Returns the minimum Euclidean distance between two closed `ConvexPolygon<T>` objects. | $O(\log(N+M)\log(\min(N,M)+1))$ time, $O(1)$ extra memory |
| `convex_polygons_closest_points(first, second, eps)` | Returns one pair of points attaining the minimum distance between two closed `ConvexPolygon<T>` objects. | $O(\log(N+M)\log(\min(N,M)+1))$ time, $O(1)$ extra memory |

These bounds apply only when both arguments are `ConvexPolygon<T>` objects.
Constructing those objects still costs $O(N+M)$ total time and memory. The
overloads are therefore useful when the same polygons participate in multiple
queries, or when the query objects already exist for other operations.

The product of logarithms is intentional: the implementation performs
$O(\log(N+M))$ searches on a virtual Minkowski-difference boundary, and one
random access into that merged boundary costs
$O(\log(\min(N,M)+1))$. It does not build or cache an $N+M$-vertex pairwise
boundary. In particular, this complexity must not be read as
$O(\log N+\log M)$.

Here $N$ and $M$ are the numbers of vertices after each query object's
normalization. Empty query objects are invalid; points and segments are
supported. All pair-query overloads treat the polygons as closed, so sharing
a vertex or edge counts as intersection and makes the distance zero.
`convex_polygons_closest_points` returns `{first_point, second_point}`, where
`first_point` belongs to the first polygon and `second_point` belongs to the
second. The returned points use `long double` because a closest point may lie
inside an edge. If the polygons intersect, both returned points describe one
common point; when several answers exist, any one may be returned. `eps`
controls geometric classification during the pair query; each object's
constructor tolerance has already been applied during its normalization.

`convex_cut` and `convex_polygon_intersection` return `Point<long double>`
because new vertices may be non-integral. A cut boundary is directed and must
contain two distinct points. Intersection construction requires two
nondegenerate convex inputs; the resulting intersection itself may degenerate
to a point or segment.

Minkowski addition is also used for the vector pair queries. `minkowski_sum`,
the three vector pair queries, and the three preprocessed pair-query overloads
require nonempty inputs. Coordinate negation, addition, and edge differences
must fit `T`.
Cross products, dot products, squared distances, and areas must fit
`wide_type<T>`.

## Example

```cpp
#include "geometry/convex_polygon.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> vertices;
    vertices.emplace_back(0, 0);
    vertices.emplace_back(4, 0);
    vertices.emplace_back(4, 4);
    vertices.emplace_back(0, 4);

    m1une::geometry::ConvexPolygon<long long> polygon(vertices);
    std::cout << int(polygon.contains(Point(2, 2))) << "\n";  // 2

    auto maximum = polygon.max_dot(Point(1, 0));
    std::cout << maximum.first << "\n";  // 4

    m1une::geometry::Line<long long> boundary{
        Point(2, -1),
        Point(2, 5)
    };
    auto left_half = m1une::geometry::convex_cut(vertices, boundary);
    std::cout << m1une::geometry::polygon_area(left_half) << "\n";  // 8
}
```
