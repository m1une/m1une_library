---
title: Tree Cumulative Sum
documentation_of: ../../../graph/tree/cumulative_sum.hpp
---

## Overview

`TreeCumulativeSum<T>` preprocesses static values on the vertices of a rooted
tree. It stores the cumulative sum from the root to every vertex, then combines
two root paths at their lowest common ancestor to answer any vertex-path sum.

`TreeEdgeCumulativeSum<T>` is the edge-valued variant. Its input vector is
indexed by graph edge id, and its path sums exclude vertices and include exactly
the edges on the path.

The underlying `TreeCumulativeProduct<Group>` and
`TreeEdgeCumulativeProduct<Group>` types provide the same operations for any
commutative group, such as xor. The additive wrappers use
`m1une::monoid::Add<T>`.

```cpp
#include "graph/graph.hpp"
#include "graph/tree/cumulative_sum.hpp"
```

## Requirements and Behavior

The graph must be an undirected tree consisting of active edges. Vertex values
must have size `graph.size()`. Edge values must have size
`graph.edge_count()` and are looked up using the ids returned by `add_edge`.
Indices are zero-based.

For `TreeCumulativeProduct<Group>`, `Group` must satisfy
`m1une::monoid::IsCommutativeGroup`: it supplies `value_type`, `id()`, `op(a,
b)`, and `inv(a)`. Associativity, commutativity, the identity law, and the
inverse law are semantic requirements.

Construction does not mutate the graph or the input values. The values are
static; rebuild the object after changing them.

## Types

| Type | Values represented |
| --- | --- |
| `TreeCumulativeProduct<Group>` | A group value on every vertex. |
| `TreeEdgeCumulativeProduct<Group>` | A group value for every graph edge id. |
| `TreeCumulativeSum<T>` | A numeric value on every vertex. |
| `TreeEdgeCumulativeSum<T>` | A numeric value for every graph edge id. |

## Interface

The following methods are shared by all four types. `value_type` is `T` for the
sum wrappers and `Group::value_type` for the product types.

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Default constructor | `TreeCumulativeProduct()` or `TreeCumulativeSum()` | Constructs an empty object. | $O(1)$ |
| Constructor | `TreeCumulativeProduct(const Graph<EdgeCost>& graph, const std::vector<value_type>& values, int root = 0)` | Builds cumulative products from `root`. | $O(N)$ time and space |
| Constructor | `TreeCumulativeSum(const Graph<EdgeCost>& graph, const std::vector<T>& values, int root = 0)` | Builds cumulative sums from `root`. | $O(N)$ time and space |
| `build` | `void build(const Graph<EdgeCost>& graph, const std::vector<value_type>& values, int root = 0)` | Rebuilds the object. | $O(N)$ time and space |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether there are no vertices. | $O(1)$ |
| `root` | `int root() const` | Returns the selected root, or `-1` when empty. | $O(1)$ |
| `lca` | `int lca(int first, int second) const` | Returns the lowest common ancestor under the selected root. | $O(\log N)$ |
| `prod` | `value_type prod(int vertex) const` | Returns the product on the root-to-`vertex` path. | $O(1)$ |
| `prod` | `value_type prod(int first, int second) const` | Returns the product on the simple path between the vertices. | $O(\log N)$ |
| `sum` | `T sum(int vertex) const` | Additive wrapper for the root-to-`vertex` sum. | $O(1)$ |
| `sum` | `T sum(int first, int second) const` | Additive wrapper for the simple-path sum. | $O(\log N)$ |

For vertex values, both endpoints of a path are included. In particular,
`sum(v, v)` is the value at `v`. For edge values, `sum(v, v)` is zero, and
`sum(root, v)` contains the edges strictly below the root on that path.

Choose `T` large enough to hold every root-path sum and the intermediate values
formed while combining two prefixes.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/tree/cumulative_sum.hpp"

#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<int> graph(5);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
    graph.add_edge(3, 4);

    std::vector<long long> value = {2, 3, 5, 7, 11};
    m1une::tree::TreeCumulativeSum<long long> sum(graph, value, 0);

    std::cout << sum.sum(4) << '\n';    // 2 + 3 + 7 + 11 = 23
    std::cout << sum.sum(2, 4) << '\n'; // 5 + 3 + 7 + 11 = 26
}
```
