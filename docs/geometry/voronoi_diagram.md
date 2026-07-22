---
title: Voronoi Diagram
documentation_of: ../../geometry/voronoi_diagram.hpp
---

## Overview

`voronoi_diagram` constructs the ordinary Euclidean Voronoi diagram of a set
of distinct integral sites. The diagram is the geometric dual of an exact
Delaunay triangulation, so it contains finite segments, unbounded rays, and,
when every site is collinear, full lines.

Combinatorial decisions use exact integral predicates. Finite vertices and
parametric edge geometry use `long double` because circumcenters need not be
integral.

## Types

```cpp
enum class VoronoiEdgeKind {
    Segment,
    Ray,
    Line,
};

struct VoronoiEdge {
    VoronoiEdgeKind kind;
    int first_site;
    int second_site;
    int first_vertex;
    int second_vertex;
    Point<long double> point;
    Point<long double> direction;
};

struct VoronoiDiagram {
    std::vector<Point<long double>> vertices;
    std::vector<VoronoiEdge> edges;
    std::vector<std::vector<int>> cell_edges;
};
```

Each edge is the shared one-dimensional boundary of the cells belonging to
`first_site` and `second_site`, with `first_site < second_site`. Its points are
described by

$$
\mathtt{point} + t\,\mathtt{direction}.
$$

| Kind | Parameter range | Vertex indices | Direction |
| --- | --- | --- | --- |
| `Segment` | $0 \leq t \leq 1$ | Both indices are valid; `point` is `vertices[first_vertex]`. | The displacement from `first_vertex` to `second_vertex`. |
| `Ray` | $0 \leq t$ | `first_vertex` is the finite endpoint and `second_vertex == -1`. | A unit vector pointing toward infinity. |
| `Line` | $-\infty < t < \infty$ | Both indices are `-1`. | A unit vector along the perpendicular bisector. |

`cell_edges[site]` contains the indices of all one-dimensional boundary edges
of that site's cell. They are ordered counterclockwise by the direction from
`site` to the neighboring site. Two cells that meet only at one Voronoi vertex
do not share an edge and therefore do not appear in each other's lists.

## Function

The exact signature is:

```cpp
template <std::integral T>
VoronoiDiagram voronoi_diagram(
    const std::vector<Point<T>>& sites
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `voronoi_diagram(sites)` | Returns all finite vertices, parametric edges, and per-site boundary-edge lists. | $O(N\log N)$ time and $O(N)$ memory |

Site indices are their zero-based positions in `sites`. All sites must be
pairwise distinct. Empty and one-site inputs have no vertices or edges. Two
sites produce one `Line`. A larger collinear input produces one line between
each consecutive pair of sites.

Cocircular Delaunay triangles are merged into one Voronoi vertex. Consequently,
the result does not expose artificial zero-length edges introduced by a choice
of Delaunay triangulation.

The degree-four incircle expressions must fit in signed 128-bit arithmetic.
This is satisfied, for example, by signed 32-bit input coordinates. As with the
other floating-point geometry constructions, callers should use an appropriate
tolerance when comparing returned coordinates.

## Example

```cpp
#include "geometry/voronoi_diagram.hpp"

#include <iostream>
#include <vector>

int main() {
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> sites;
    sites.emplace_back(0, 0);
    sites.emplace_back(6, 0);
    sites.emplace_back(0, 8);

    auto diagram = m1une::geometry::voronoi_diagram(sites);
    std::cout << diagram.vertices.size() << '\n';  // 1
    std::cout << diagram.edges.size() << '\n';     // 3 rays

    for (int edge_index : diagram.cell_edges[0]) {
        const auto& edge = diagram.edges[edge_index];
        std::cout << edge.first_site << ' ' << edge.second_site << '\n';
    }
}
```
