---
title: Replacement Paths
documentation_of: ../../graph/replacement_paths.hpp
---

## Overview

Replacement paths answer every single-failure shortest-path query along one
fixed shortest path $P=(p_0=s,p_1,\ldots,p_k=t)$. One call computes either the
shortest $s$-$t$ distance after deleting each logical path edge
$(p_i,p_{i+1})$, one edge at a time, or the shortest distance after deleting
each path vertex $p_i$, one vertex at a time.

The graph must be undirected and built with `Graph<T>::add_edge`. Every active
edge must have strictly positive cost. Inactive edges are ignored. The input
graph and its `alive` flags are never changed.

The automatic overloads select one shortest path. The `GraphPath` overloads
preserve the caller's exact shortest path, including its logical edge ids. Edge
ids are necessary because parallel edges may join the same pair of vertices.

## Path and Results

`GraphPath` has the following members:

| Member | Type | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | The ordered vertices $p_0,\ldots,p_k$. |
| `edges` | `std::vector<int>` | `edges[i]` is the active logical edge joining `vertices[i]` and `vertices[i + 1]`. |

It satisfies `vertices.size() == edges.size() + 1`. A supplied path must be
nonempty and simple, and its stored total cost must equal the shortest distance
between its endpoints.

`EdgeReplacementPathsResult<T>` contains:

| Member / method | Type / Signature | Meaning |
| --- | --- | --- |
| `path` | `GraphPath` | The selected or supplied fixed path. |
| `replacement_dist` | `std::vector<T>` | Entry `i` is the shortest distance after deleting logical edge `path.edges[i]`. Its size is `path.edges.size()`. |
| `inf` | `T` | The unreachable-distance sentinel. |
| `reachable` | `bool reachable(int path_edge_index) const` | Tests whether the corresponding replacement distance is finite. |

`VertexReplacementPathsResult<T>` contains:

| Member / method | Type / Signature | Meaning |
| --- | --- | --- |
| `path` | `GraphPath` | The selected or supplied fixed path. |
| `replacement_dist` | `std::vector<T>` | Entry `i` is the shortest distance after deleting vertex `path.vertices[i]`. Its size is `path.vertices.size()`. |
| `inf` | `T` | The unreachable-distance sentinel. |
| `reachable` | `bool reachable(int path_vertex_index) const` | Tests whether the corresponding replacement distance is finite. |

Deleting the source or target makes the route unavailable, so the first and
last vertex-replacement entries are `inf`. If `s == t`, the path has one vertex
and no edges, the edge result is empty, and the vertex result contains one
`inf`.

## Functions

Let $N$ be the number of vertices, $M$ the number of logical edges, and $K$ the
number of edges in the fixed path.

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `edge_replacement_paths` | `template <class T> EdgeReplacementPathsResult<T> edge_replacement_paths(const Graph<T>& g, int s, int t, T inf = std::numeric_limits<T>::max() / T(4))` | Selects one shortest path and processes every path-edge failure. | $O((N+M)\log N)$ time, $O(N+M)$ memory. |
| `edge_replacement_paths` | `template <class T> EdgeReplacementPathsResult<T> edge_replacement_paths(const Graph<T>& g, const GraphPath& path, T inf = std::numeric_limits<T>::max() / T(4))` | Processes every edge failure on the exact supplied shortest path. | $O((N+M)\log N)$ time, $O(N+M)$ memory. |
| `vertex_replacement_paths` | `template <class T> VertexReplacementPathsResult<T> vertex_replacement_paths(const Graph<T>& g, int s, int t, T inf = std::numeric_limits<T>::max() / T(4))` | Selects one shortest path and processes every path-vertex failure. | $O(K(N+M)\log N)$ time, $O(N+M)$ memory. |
| `vertex_replacement_paths` | `template <class T> VertexReplacementPathsResult<T> vertex_replacement_paths(const Graph<T>& g, const GraphPath& path, T inf = std::numeric_limits<T>::max() / T(4))` | Processes every vertex failure on the exact supplied shortest path. | $O(K(N+M)\log N)$ time, $O(N+M)$ memory. |

All additions saturate at `inf`. Choose `inf` larger than every finite answer
that must be represented.

## Edge Algorithm and Correctness

The edge solver runs Dijkstra from both endpoints. It constructs a shortest-path
tree rooted at $s$ that contains the exact fixed path: fixed-path parent edges
are forced, and every other reachable vertex receives a tight predecessor.
Strictly positive costs make predecessor distances decrease strictly toward the
root, so the forced tree is acyclic even when shortest paths tie.

Conceptually remove the fixed-path edges from this tree. Each remaining tree
component contains exactly one path vertex. Define `block[v] = i` when `v` lies
in the component containing $p_i$.

Consider an active non-path logical edge joining blocks $a<b$, oriented from
`u` in block $a$ to `v` in block $b$. The tree shortest path from $s$ to `u`
stays on the source side of every fixed-path edge with index in $[a,b)`. Thus

```text
dist_s[u] + cost(u, v) + dist_t[v]
```

is a candidate for every such edge failure. If the chosen shortest suffix from
`v` crosses the failed cut, replacing the offending portion by the appropriate
tree/path suffix gives an available route with no greater length. Conversely,
every replacement path has a first edge that crosses from
the source-side block to the target-side block; its prefix and suffix are no
shorter than the two Dijkstra distances. Taking minima therefore gives the
exact answer. Range `chmin` on $[a,b)$ processes all failures together.

The exact logical ids in `path.edges` are excluded as detour edges: a failed
edge cannot replace itself. A parallel edge has a different id and remains a
valid detour, even when its endpoints and cost are equal.

For a vertex $p_i$, an edge between blocks $a<b$ can similarly participate in
a bypass only for internal indices $a<i<b$, the integer range $[a+1,b)`, when
its prefix and suffix avoid $p_i$. Unlike edge failure, these one-edge ranges
are not complete: an optimal vertex-avoiding route can enter the failed
vertex's tree block through one detour edge and leave through another without
visiting the failed vertex. The current vertex solver therefore uses a proven
Dijkstra run that ignores each path vertex rather than making an incorrect
near-linear claim.

## Preconditions

Assertions check that:

* the graph consists of paired undirected arcs created by `add_edge`;
* all active costs are strictly positive;
* all supplied vertices and logical edge ids are valid;
* every supplied edge is active and joins its two listed vertices;
* supplied vertices are pairwise distinct; and
* the supplied path cost equals the shortest endpoint distance.

Directed graphs, graphs containing active zero-cost edges, and replacement-path
reconstruction are not supported.

## Examples

Automatic path selection:

```cpp
#include "graph/replacement_paths.hpp"

int main() {
    int n = 5;
    m1une::graph::Graph<long long> g(n);
    g.add_edge(0, 1, 2);
    g.add_edge(1, 4, 2);
    g.add_edge(0, 2, 3);
    g.add_edge(2, 4, 3);

    auto edge_result = m1une::graph::edge_replacement_paths(g, 0, 4);
    for (long long distance : edge_result.replacement_dist) {
        (void)distance;
    }
}
```

An exact externally supplied shortest path:

```cpp
#include "graph/replacement_paths.hpp"

int main() {
    m1une::graph::Graph<long long> g(4);
    int e01 = g.add_edge(0, 1, 2);
    int e13 = g.add_edge(1, 3, 2);
    g.add_edge(0, 2, 3);
    g.add_edge(2, 3, 3);

    m1une::graph::GraphPath fixed_path{
        .vertices = {0, 1, 3},
        .edges = {e01, e13},
    };
    auto vertex_result = m1une::graph::vertex_replacement_paths(g, fixed_path);
    (void)vertex_result;
}
```
