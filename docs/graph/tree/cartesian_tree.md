---
title: Cartesian Tree
documentation_of: ../../../graph/tree/cartesian_tree.hpp
---

## Overview

`m1une::tree::CartesianTree` builds the Cartesian tree of an array. With the
default comparator, the minimum element is the root, each parent has value no
greater than its children, and an inorder traversal visits indices in increasing
order.

Use `std::greater<T>` to build the maximum Cartesian tree. More generally,
`comp(x, y)` means that value `x` has higher priority and should be closer to
the root than value `y`. If neither value compares before the other, the smaller
index is kept closer to the root.

The structure stores only vertex indices. It can be converted to
`m1une::graph::Graph<int>` when you want to use the other tree helpers.

## Public Members

| Member | Type | Description |
| --- | --- | --- |
| `root` | `int` | Root index, or `-1` for an empty tree. |
| `parent` | `std::vector<int>` | Parent index, or `-1` at the root. |
| `left` | `std::vector<int>` | Left child index, or `-1`. |
| `right` | `std::vector<int>` | Right child index, or `-1`. |

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `CartesianTree()` | Creates an empty tree. | $O(1)$ |
| `CartesianTree(const std::vector<T>& a, Compare comp = Compare())` | Builds the Cartesian tree of `a`. | $O(N)$ |
| `void build(const std::vector<T>& a, Compare comp = Compare())` | Rebuilds the structure from `a`. | $O(N)$ |
| `int size() const` | Returns the number of vertices. | $O(1)$ |
| `bool empty() const` | Returns whether the tree is empty. | $O(1)$ |
| `int parent_or_self(int v) const` | Returns `parent[v]`, or `v` when `v` is the root. | $O(1)$ |
| `std::vector<int> parent_with_root_self() const` | Returns the parent array with `root` as its own parent. | $O(N)$ |
| `std::vector<std::pair<int, int>> edges() const` | Returns directed `(parent, child)` pairs. | $O(N)$ |
| `m1une::graph::Graph<int> to_graph() const` | Returns an undirected graph with one edge per parent-child relation. | $O(N)$ |

## Notes

The implementation is iterative and uses a monotone stack. It does not mutate
the input array. The comparator must model a strict weak ordering.

Library Checker's `cartesian_tree` problem asks for the root to be printed as
its own parent; use `parent_with_root_self()` for that convention.

## Example

```cpp
#include "graph/tree/cartesian_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a = {3, 1, 4, 0, 2};

    m1une::tree::CartesianTree tree(a);
    std::vector<int> parent = tree.parent_with_root_self();

    for (int i = 0; i < int(parent.size()); i++) {
        if (i) std::cout << ' ';
        std::cout << parent[i];
    }
    std::cout << "\n";
}
```
