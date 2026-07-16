---
title: Enumerate Cliques
documentation_of: ../../graph/enumerate_cliques.hpp
---

## Overview

`enumerate_cliques` visits every nonempty clique of a simple graph exactly once.
Cliques are reported through a callback, allowing their values to be aggregated
without storing every result.

The implementation computes a degeneracy ordering and assigns each clique to
its first vertex in that ordering. It then enumerates cliques inside that
vertex's forward neighborhood. This limits the exponential part to the graph's
degeneracy rather than its total vertex count.

## Graph Requirements

The active edges must form a simple graph: self-loops and parallel edges are not
supported. Each active edge is interpreted as undirected, including edges added
with `add_directed_edge`. Edge costs are ignored and inactive edges are ignored.

## Callback

The callback signature is:

```cpp
callback(const std::vector<int>& clique);
```

It is invoked exactly once for every nonempty clique, including single-vertex
cliques. Vertex and clique order are unspecified. The vector is reused by the
enumerator, so copy it if it must remain available after the callback returns.
The callback must not mutate the graph.

## Function

| Function | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| `enumerate_cliques` | `template <class T, class Callback> void enumerate_cliques(const Graph<T>& graph, Callback&& callback)` | Invokes `callback` once for every nonempty clique without mutating `graph`. | $O(N + M + Md\log N + K(d + F))$ time and $O(N + M + d^2)$ memory |

Here, `d` is the graph degeneracy, `K` is the number of nonempty cliques, and
`F` is the cost of one callback. Since $d = O(\sqrt M)$ for a simple graph, the
bound is practical for sparse graphs whose clique output is manageable.

## Example

```cpp
#include "graph/enumerate_cliques.hpp"
#include "graph/graph.hpp"

#include <cassert>
#include <vector>

int main() {
    m1une::graph::Graph<> graph(3);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);

    int count = 0;
    m1une::graph::enumerate_cliques(
        graph,
        [&](const std::vector<int>&) { count++; }
    );
    assert(count == 7);
}
```
