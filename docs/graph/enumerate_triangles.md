---
title: Enumerate Triangles
documentation_of: ../../graph/enumerate_triangles.hpp
---

## Overview

`enumerate_triangles` visits every triangle in a simple graph exactly once.
Triangles are reported through a callback, so you can count them, aggregate
vertex values, or process them online without storing every triple.

The implementation orients edges by `(degree, vertex)` and intersects the
resulting forward neighborhoods. This avoids the cubic scan over all vertex
triples.

## Graph Requirements

The active edges must form a simple graph: self-loops and parallel edges are not
supported. Each active edge is interpreted as undirected, regardless of whether
it was inserted with `add_edge` or `add_directed_edge`. Edge costs are ignored,
and inactive edges are ignored.

## Callback

The callback signature is:

```cpp
callback(int first, int second, int third);
```

It is invoked exactly once per triangle. The vertex indices are always ordered
as `first < second < third`. The order in which different triangles are visited
is unspecified.

## Function

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `enumerate_triangles` | `template <class T, class Callback> void enumerate_triangles(const Graph<T>& graph, Callback&& callback)` | Invokes the callback once for every triangle. Does not mutate `graph`. | $O(N + M\sqrt M + K F)$ time and $O(N + M)$ memory, where $M$ is the number of active edges, $K$ is the number of triangles, and $F$ is the cost of one callback. |

## Example

```cpp
#include "graph/enumerate_triangles.hpp"
#include "graph/graph.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);
    graph.add_edge(2, 3);

    std::vector<long long> value = {2, 3, 5, 7};
    long long sum = 0;
    m1une::graph::enumerate_triangles(
        graph,
        [&](int first, int second, int third) {
            sum += value[first] * value[second] * value[third];
        }
    );
    std::cout << sum << "\n";  // 30
}
```
