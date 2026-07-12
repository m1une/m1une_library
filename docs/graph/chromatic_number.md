---
title: Chromatic Number
documentation_of: ../../graph/chromatic_number.hpp
---

## Overview

Computes the chromatic number of a graph: the minimum number of colors needed
to color all vertices so that adjacent vertices have different colors.

The algorithm is intended for small general graphs. It uses inclusion-exclusion
over vertex subsets and supports at most `20` vertices.

## Graph Interpretation

Every active edge of `Graph<T>` is treated as an undirected edge, regardless of
how it was inserted. Parallel edges do not change the answer. Self-loops are
ignored, matching the conventions of the other exact vertex-set algorithms in
this library.

## Function

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `chromatic_number` | `template <class T> int chromatic_number(const Graph<T>& g)` | Returns the chromatic number. The empty graph has chromatic number `0`. | $O(N2^N)$ time and $O(2^N)$ memory |

The function asserts that `g.size() <= 20`.

## Algorithm

For every vertex subset `S`, the implementation first counts the independent
subsets contained in `S`. Inclusion-exclusion then counts ordered covers of all
vertices by `k` independent sets. Such a cover exists exactly when the graph is
`k`-colorable.

The count is evaluated modulo 14 pairwise coprime numbers. For `N, k <= 20`,
the number of covers is less than `2^(N k) <= 2^400`, while the product of the
moduli is greater than `2^412`. Thus a positive count cannot vanish modulo all
of them, and the result is deterministic.

## Example

```cpp
#include "graph/chromatic_number.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(5);
    for (int v = 0; v < 5; v++) g.add_edge(v, (v + 1) % 5);

    std::cout << m1une::graph::chromatic_number(g) << "\n";  // 3
}
```
