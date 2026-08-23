---
title: DAG Longest Path
documentation_of: ../../graph/dag_longest_path.hpp
---

## Overview

`dag_longest_path` computes maximum-cost paths from one or more sources in a
directed acyclic graph. Edges are relaxed once in topological order, so negative
costs are supported and one optimal path can be restored.

The graph must be directed and acyclic. A cyclic graph returns `std::nullopt`.
Inactive edges are ignored.

## Requirements

The edge cost type `T` must be ordered and support construction from `0`,
addition, and `std::numeric_limits<T>::lowest()`. The default `neg_inf` is
intended for signed integer or floating-point costs. Pass an explicit sentinel
for another compatible type.

Every source starts with distance `0`. With multiple sources, the result is the
best path beginning at any source, including a zero-edge path. Duplicate source
indices have no additional effect.

## Result

| Member / method | Type / signature | Meaning | Complexity |
| --- | --- | --- | --- |
| `dist` | `std::vector<T>` | Maximum distance to each vertex, or `neg_inf` if unreachable. | Access: $O(1)$ |
| `parent` | `std::vector<int>` | Previous vertex on one maximum path, or `-1`. | Access: $O(1)$ |
| `parent_edge` | `std::vector<int>` | Original edge id entering the vertex, or `-1`. | Access: $O(1)$ |
| `topological_order` | `std::vector<int>` | Order used by the relaxation. | Access: $O(1)$ |
| `neg_inf` | `T` | Unreachable-distance sentinel. | Access: $O(1)$ |
| `reachable` | `bool reachable(int v) const` | Tests whether a source reaches `v`. | $O(1)$ |
| `path` | `std::vector<int> path(int t) const` | Restores one maximum path ending at reachable `t`. | $O(L)$ for path length $L$ |

## Functions

| Function | Signature | Complexity |
| --- | --- | --- |
| `dag_longest_path` | `template <class T> std::optional<DagLongestPathResult<T>> dag_longest_path(const Graph<T>& g, int s, T neg_inf = std::numeric_limits<T>::lowest() / T(4))` | $O(N + M)$ time and $O(N)$ memory |
| `dag_longest_path` | `template <class T> std::optional<DagLongestPathResult<T>> dag_longest_path(const Graph<T>& g, const std::vector<int>& sources, T neg_inf = std::numeric_limits<T>::lowest() / T(4))` | $O(N + M)$ time and $O(N)$ memory |

## Example

```cpp
#include "graph/dag_longest_path.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(4);
    g.add_directed_edge(0, 1, 2);
    g.add_directed_edge(0, 2, 5);
    g.add_directed_edge(1, 3, 7);
    g.add_directed_edge(2, 3, 1);

    auto result = m1une::graph::dag_longest_path(g, 0);
    if (result) std::cout << result->dist[3] << '\n';  // 9
}
```
