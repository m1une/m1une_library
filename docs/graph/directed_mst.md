---
title: Directed Minimum Spanning Tree
documentation_of: ../../graph/directed_mst.hpp
---

## Overview

`directed_mst` finds a minimum-cost spanning arborescence. It can either use a
specified root or choose the root that minimizes the total cost. Every vertex
must be reachable from the selected root using active directed edges. If no such
arborescence exists, it returns `std::nullopt`.

The implementation uses the Chu-Liu/Edmonds algorithm with lazy meldable heaps,
disjoint-set contraction, and a contraction forest for edge reconstruction.

Use `Graph<T>::add_directed_edge` to add edges. Parallel edges and self-loops are
supported, and inactive edges are ignored.

## Requirements

The cost type `T` must support `T(0)`, addition, subtraction, and comparison with
`<`. All input costs, reduced costs, and the final answer must fit in `T`.
Negative edge costs are supported.

## Interface

```cpp
template <class T>
struct DirectedMinimumSpanningTree {
    T cost;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<Edge<T>> edges;
    int root;
};

template <class T>
std::optional<DirectedMinimumSpanningTree<T>>
directed_mst(const Graph<T>& graph, int root);

template <class T>
std::optional<DirectedMinimumSpanningTree<T>>
directed_mst(const Graph<T>& graph);
```

## Result

| Member | Description |
| --- | --- |
| `cost` | Sum of the selected edge costs. |
| `parent[v]` | Parent of `v`; `parent[root] == root`. |
| `parent_edge[v]` | ID of the selected edge entering `v`; `-1` for the root. |
| `edges` | The `N - 1` selected original edges, ordered by destination vertex except for the root. |
| `root` | The specified root vertex, or the root selected by the root-free overload. |

## Operations

| Function | Description | Complexity |
| --- | --- | --- |
| `directed_mst(const Graph<T>& graph, int root)` | Returns a minimum rooted spanning arborescence, or `std::nullopt` if none exists. It does not mutate `graph`. | Amortized $O((N + M)\log M)$ |
| `directed_mst(const Graph<T>& graph)` | Chooses the root giving the minimum-cost spanning arborescence. Returns `std::nullopt` for an empty graph or if no single root can span every vertex. It does not mutate `graph`. | Amortized $O((N + M)\log (N + M))$ |

## Complexity

For `N` vertices and `M` stored edges, the running time is
`O((N + M) log M)` amortized and the memory usage is `O(N + M)`. The
implementation is iterative.

The root-free overload uses a lexicographic artificial-root cost. It minimizes
the number of artificial edges before the original cost, so it does not require
a numeric infinity or a large penalty value in `T`.

## Example

```cpp
m1une::graph::Graph<long long> graph(3);
graph.add_directed_edge(0, 1, 2);
graph.add_directed_edge(0, 2, 7);
graph.add_directed_edge(1, 2, 3);

auto answer = m1une::graph::directed_mst(graph, 0);
assert(answer.has_value());
assert(answer->cost == 5);
assert(answer->parent[1] == 0);
assert(answer->parent[2] == 1);
```
