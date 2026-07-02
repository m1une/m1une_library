---
title: 01 on Tree
documentation_of: ../../tree/zero_one_on_tree.hpp
---

## Overview

Each vertex of a rooted tree is labeled `0` or `1`. Consider every ordering of
the vertices in which each parent appears before its children. This header
computes the minimum possible number of inversions in the resulting binary
sequence.

The algorithm maintains contracted vertex groups. A non-root group with the
largest ratio

\[
\frac{\text{number of zeros}}{\text{number of ones}}
\]

is appended to its current parent group. A group containing no ones has
infinite ratio. A set maintains the ratios, and a disjoint-set structure finds
the current parent group after contractions.

## Public Interface

```cpp
long long zero_one_on_tree(
    const std::vector<int>& parent,
    const std::vector<int>& value);

template <class T>
long long zero_one_on_tree(
    const m1une::graph::Graph<T>& graph,
    const std::vector<int>& value,
    int root = 0);
```

The parent-array overload uses zero-based vertices. Exactly one vertex must
have parent `-1`; every other entry must be a valid parent and the resulting
directed edges must form a tree. Each entry of `value` must be `0` or `1`.

The graph overload expects a connected undirected tree built with `add_edge`.
Inactive edges are ignored. For an empty graph it returns `0` without using
`root`.

## Complexity

| Function | Time | Extra memory |
| --- | --- | --- |
| `zero_one_on_tree(parent, value)` | $O(N \log N)$ | $O(N)$ |
| `zero_one_on_tree(graph, value, root)` | $O(N \log N)$ | $O(N)$ |

The answer can be quadratic in `N`, so the return type is `long long`. Neither
overload mutates its arguments.

## Example

```cpp
#include "tree/zero_one_on_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> parent = {-1, 0, 0, 1, 2, 2};
    std::vector<int> value = {0, 1, 1, 0, 0, 0};

    std::cout << m1une::tree::zero_one_on_tree(parent, value) << '\n';
}
```
