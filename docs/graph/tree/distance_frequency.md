---
title: Tree Distance Frequency
documentation_of: ../../../graph/tree/distance_frequency.hpp
---

## Overview

`tree_distance_frequency` counts unordered pairs of vertices at every distance
in an unweighted tree. It is useful when a problem asks for the complete
distribution of path lengths rather than individual distance queries.

```cpp
#include "graph/tree/distance_frequency.hpp"
```

The function is in `m1une::tree` and accepts `m1une::graph::Graph<T>`.

## Interface

```cpp
template <class T>
std::vector<long long> tree_distance_frequency(
    const m1une::graph::Graph<T>& tree
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `tree_distance_frequency(tree)` | Returns the number of unordered vertex pairs at each edge distance. | $O(N \log^2 N)$ time and $O(N)$ additional memory |

For a tree with `N` vertices, the result has length `N`:

* `result[0]` is `N`, counting each vertex paired with itself;
* for `distance > 0`, `result[distance]` is the number of pairs `(u, v)` with
  `u < v` whose path contains exactly `distance` edges.

The empty tree produces an empty vector. Otherwise, the graph must be a
connected undirected tree with `N - 1` active edges. Edge costs are ignored.
The result is exact rather than reduced modulo a number.

## Algorithm

At each centroid, depth histograms are collected for the whole current
component and for every component obtained by removing the centroid. Squaring
the whole histogram and subtracting the component squares counts ordered pairs
whose path passes through that centroid. Centroid decomposition makes every
pair appear at exactly one level.

The histogram squares use NTT convolution under two prime moduli. Chinese
remaindering reconstructs the exact ordered-pair counts, which are then divided
by two for positive distances.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/tree/distance_frequency.hpp"

#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<int> tree(4);
    tree.add_edge(0, 1);
    tree.add_edge(1, 2);
    tree.add_edge(2, 3);

    std::vector<long long> frequency =
        m1une::tree::tree_distance_frequency(tree);
    // frequency is {4, 3, 2, 1}.
    std::cout << frequency[2] << '\n';
}
```
