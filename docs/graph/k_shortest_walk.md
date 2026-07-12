---
title: K-Shortest Walk
documentation_of: ../../graph/k_shortest_walk.hpp
---

## Overview

`k_shortest_walk` lists the lengths of the shortest walks from one vertex to
another in nondecreasing order. A walk may repeat vertices and edges, and two
different walks are counted separately even when their lengths are equal.

The implementation uses a shortest-path tree toward the target and persistently
melded heaps of Eppstein sidetracks. It is intended for large sparse or dense
directed graphs with non-negative edge costs.

## Requirements and Behavior

- `T` must support construction from integers, addition, subtraction, equality,
  and ordering.
- Every alive edge cost must be non-negative.
- Costs of all relevant walks and intermediate sums must fit in `T` and remain
  below `inf`.
- Inactive edges are ignored.
- If `s == t`, the empty walk of length zero is the first answer.
- If fewer than `k` walks exist, the returned vector is shorter than `k`. No
  sentinel value is appended.

## Function

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `k_shortest_walk` | `template <class T> std::vector<T> k_shortest_walk(const Graph<T>& g, int s, int t, int k, T inf = std::numeric_limits<T>::max() / T(4))` | Returns up to `k` walk lengths from `s` to `t` in nondecreasing order. | $O((N+M)\log N + M\log M + K\log K)$ time and $O(N+M+N\log M+K)$ memory. |

Here `M` counts alive adjacency entries, so an undirected edge stored by
`Graph::add_edge` contributes two entries. The graph itself is not modified.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/k_shortest_walk.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 2);
    g.add_directed_edge(1, 2, 3);
    g.add_directed_edge(0, 2, 8);
    g.add_directed_edge(1, 1, 1);

    auto lengths = m1une::graph::k_shortest_walk(g, 0, 2, 4);
    for (long long length : lengths) std::cout << length << "\n";
    // 5, 6, 7, 8
}
```
