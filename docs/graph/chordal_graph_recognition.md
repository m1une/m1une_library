---
title: Chordal Graph Recognition
documentation_of: ../../graph/chordal_graph_recognition.hpp
---

## Overview

A graph is chordal when every cycle of length at least four has a chord.
Equivalently, it has a perfect elimination ordering: for each vertex, its
neighbors appearing later in the ordering form a clique.

`chordal_graph_recognition` recognizes a chordal graph and returns a certificate
in either case. A chordal graph gets a perfect elimination ordering; a
non-chordal graph gets an induced cycle of length at least four.

The implementation uses bucketed maximum-cardinality search, verifies the
resulting ordering, and performs one BFS only when it must construct a cycle.

## Returned Certificates

### Perfect Elimination Ordering

Let `order` be a permutation of all vertices. For each vertex `order[i]`, look
at only its neighbors in the suffix
`order[i + 1], order[i + 2], ..., order[N - 1]`. The ordering is a perfect
elimination ordering when those later neighbors are pairwise adjacent, and
therefore form a clique, for every `i`.

The name comes from eliminating the vertices from left to right. Removing
`order[i]` cannot create a missing connection between its remaining neighbors,
because those neighbors already form a clique.

For example, consider the path `0 - 1 - 2`. The ordering `[0, 2, 1]` is a
perfect elimination ordering:

* The only later neighbor of `0` is `1`.
* The only later neighbor of `2` is `1`.
* Vertex `1` has no later neighbors.

A set with zero or one vertex is always a clique, so all three conditions hold.
Every chordal graph has such an ordering, and every graph with such an ordering
is chordal.

### Induced Cycle

An induced cycle is a sequence of distinct vertices
`cycle[0], cycle[1], ..., cycle[K - 1]`, with `K >= 4`, satisfying both of the
following:

* Consecutive vertices are adjacent, including `cycle[K - 1]` and `cycle[0]`.
* No other pair of vertices in the sequence is adjacent.

The second condition says that the cycle has no chord: an edge joining two
non-consecutive cycle vertices. For example, the four-cycle
`0 - 1 - 2 - 3 - 0` is induced if neither `0 - 2` nor `1 - 3` is an edge.
Adding either edge gives the cycle a chord, so that four-vertex sequence is no
longer an induced cycle.

An induced cycle of length at least four is a direct certificate that the graph
is not chordal. The returned vector does not repeat its first vertex at the end;
the closing edge from `cycle.back()` to `cycle.front()` is implicit.

## Graph Interpretation

Every active edge of `Graph<T>` is treated as an undirected edge, regardless of
how it was inserted. Self-loops are ignored. Parallel edges are treated as one
edge, so they do not change the result.

Edge costs are ignored. The graph is not mutated.

## API

```cpp
struct ChordalGraphResult {
    bool is_chordal;
    std::vector<int> perfect_elimination_order;
    std::vector<int> induced_cycle;
};

template <class T>
ChordalGraphResult chordal_graph_recognition(const Graph<T>& graph);

template <class T>
bool is_chordal(const Graph<T>& graph);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `is_chordal` | Whether the input graph is chordal. | -- |
| `perfect_elimination_order` | A permutation in which the later neighbors of every vertex form a clique when the graph is chordal; empty otherwise. | -- |
| `induced_cycle` | Distinct vertices of a chordless cycle in cyclic order when the graph is not chordal; empty otherwise. The first vertex is not repeated. | -- |
| `chordal_graph_recognition(graph)` | Recognizes the graph and constructs the appropriate certificate. | $O(N+M)$ time and memory |
| `is_chordal(graph)` | Returns only whether the graph is chordal. | $O(N+M)$ time and memory |

## Example

```cpp
#include "graph/chordal_graph_recognition.hpp"
#include "graph/graph.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 0);

    auto result = m1une::graph::chordal_graph_recognition(graph);
    std::cout << result.is_chordal << "\n";         // 0
    std::cout << result.induced_cycle.size() << "\n";  // 4
}
```
