---
title: Dijkstra
documentation_of: ../../graph/dijkstra.hpp
---

## Overview

Dijkstra's algorithm computes shortest paths from one or more sources when all
edge costs are non-negative. It repeatedly fixes the unreached vertex with the
smallest tentative distance, using a priority queue.

Use it for typical weighted shortest path problems with costs like time,
distance, or price. Do not use it if a reachable edge can have a negative cost;
use Bellman-Ford in that case.

## Graph Orientation

Direction is respected. `dijkstra` works on directed graphs as written, and
also on undirected graphs built with `add_edge`.

## How to Use It

Use `Graph<T>` with a cost type such as `long long` or a small user-defined
class. Dijkstra does not use `std::numeric_limits<T>` and does not need an
infinity value. Reachability is stored separately from distances.

`T` must be default-constructible, with `T()` representing zero. It must also
be copyable/movable and support `a + b` and strict comparison `a < b`. Equality,
`>`, `<=`, subtraction, conversion to a built-in number, and a
`std::numeric_limits` specialization are not required.

Every reachable path sum must be representable by `T`. For built-in signed
integers, choose a sufficiently wide type so `a + b` does not overflow.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `dist` | `std::vector<T>` | `dist[v]` is the shortest distance from the nearest source when `reachable(v)` is true. Without an explicit sentinel argument, unreachable entries contain `T()`. |
| `reached` | `std::vector<char>` | Stores whether each vertex was reached. Prefer `reachable(v)` over accessing this directly. |
| `parent` | `std::vector<int>` | `parent[v]` is the previous vertex on one shortest path, or `-1`. |
| `parent_edge` | `std::vector<int>` | `parent_edge[v]` is the edge id used to enter `v`, or `-1`. |
| `inf` | `T` | Stores the explicit sentinel argument when one was passed, and `T()` otherwise. Kept for source compatibility; `reachable(v)` does not use it. |
| `reachable` | `bool reachable(int v) const` | Returns whether `v` was reached. |
| `path` | `std::vector<int> path(int t) const` | Restores one shortest path from a source to `t`. Requires `reachable(t)`. |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `dijkstra` | `template <class T> DijkstraResult<T> dijkstra(const Graph<T>& g, int s)` | Runs from one source. | $O((N + M) \log N)$ |
| `dijkstra` | `template <class T> DijkstraResult<T> dijkstra(const Graph<T>& g, const std::vector<int>& sources)` | Runs from multiple sources. | $O((N + M) \log N)$ |
| `dijkstra` | `template <class T> DijkstraResult<T> dijkstra(const Graph<T>& g, int s, const T& inf)` | Compatibility overload that writes `inf` into unreachable `dist` entries after the search. | $O((N + M) \log N)$ |
| `dijkstra` | `template <class T> DijkstraResult<T> dijkstra(const Graph<T>& g, const std::vector<int>& sources, const T& inf)` | Multi-source compatibility overload with an unreachable display value. | $O((N + M) \log N)$ |

## Example

```cpp
#include "graph/dijkstra.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 10);
    g.add_directed_edge(0, 2, 3);
    g.add_directed_edge(2, 1, 4);

    auto res = m1une::graph::dijkstra(g, 0);
    if (res.reachable(1)) {
        std::cout << res.dist[1] << "\n";  // 7
    }
}
```

Do not determine reachability by comparing `dist[v]` with a sentinel. Always
call `reachable(v)`. This remains correct even when a finite shortest distance
happens to equal the `inf` value passed to a compatibility overload.

## User-Defined Cost Example

Only zero construction, addition, and `<` are needed:

```cpp
struct Cost {
    long long value = 0;

    Cost operator+(const Cost& other) const {
        return Cost{value + other.value};
    }

    friend bool operator<(const Cost& first, const Cost& second) {
        return first.value < second.value;
    }
};

m1une::graph::Graph<Cost> graph(3);
graph.add_directed_edge(0, 1, Cost{4});
graph.add_directed_edge(1, 2, Cost{7});
auto result = m1une::graph::dijkstra(graph, 0);
// result.reachable(2) is true and result.dist[2].value is 11.
```

No `std::numeric_limits<Cost>` specialization is necessary.
