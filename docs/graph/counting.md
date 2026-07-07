---
title: Graph Counting
documentation_of: ../../graph/counting.hpp
---

## Overview

`graph/counting.hpp` computes common graph-counting sequences by number of
vertices. The labeled functions count simple graphs on vertex set
`{0, 1, ..., n - 1}`; two labeled graphs are different when some edge choice is
different. The unlabeled tree functions count isomorphism classes.

All functions return a vector `answer` of length `maximum + 1`, where
`answer[n]` is the number of objects on `n` vertices.

This header counts by vertex number only. It does not keep track of the number
of edges.

## Requirements and Conventions

Let `N = maximum`. In the complexity table, `M(N)` means the cost of one
polynomial multiplication where both inputs have length `O(N)`, and only the
first `N + 1` coefficients may be needed. Equivalently, it is the convolution
cost for formal power series truncated to degree at most `N`. With the supplied
convolution over NTT-friendly static modints, `M(N) = O(N log N)`.

`Mint` must support the operations required by
`fps::FormalPowerSeries<Mint>`: addition, subtraction, multiplication,
division by nonzero small integers, `pow`, `inv`, and `Mint::mod()`. In
practice this is intended for prime moduli such as
`m1une::math::modint998244353`.

The code asserts:

* `maximum >= 0`;
* `maximum < Mint::mod()`, because EGF operations divide by factorials and
  small integers;
* the modulus is not `2` for functions that divide by `2`.

Connectivity follows the convention that the empty graph is not connected.
Thus connected counts have value `0` at `n = 0`. A forest has value `1` at
`n = 0`, representing the empty forest.

A labeled tournament is an orientation of the complete graph on labeled
vertices: for every unordered pair of distinct vertices, exactly one of the two
possible directed edges is chosen. A strongly connected labeled tournament is a
labeled tournament in which every ordered pair of vertices `(u, v)` has a
directed path from `u` to `v`.

## Public Interface

All signatures below are in namespace `m1une::graph`.

| Function | Counts | Time |
| --- | --- | --- |
| `template <class Mint> std::vector<Mint> count_labeled_undirected_graphs(int maximum)` | Simple undirected labeled graphs. | `O(N)` |
| `template <class Mint> std::vector<Mint> count_labeled_connected_graphs(int maximum)` | Connected simple undirected labeled graphs. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_trees(int maximum)` | Labeled trees, using Cayley's formula. | `O(N log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_forests(int maximum)` | Labeled forests. | `O(N log N + M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_unicyclic_connected_graphs(int maximum)` | Connected labeled graphs with exactly `n` edges on `n` vertices. | `O(N log N + M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_connected_eulerian_graphs(int maximum)` | Connected undirected labeled graphs where every degree is even. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_connected_bipartite_graphs(int maximum)` | Connected undirected labeled bipartite graphs. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_bipartite_graphs(int maximum)` | Undirected labeled bipartite graphs, not necessarily connected. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_directed_graphs(int maximum)` | Simple directed labeled graphs without loops. | `O(N)` |
| `template <class Mint> std::vector<Mint> count_labeled_dags(int maximum)` | Labeled directed acyclic graphs. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_strongly_connected_digraphs(int maximum)` | Strongly connected simple directed labeled graphs without loops. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_tournaments(int maximum)` | Labeled tournaments. | `O(N)` |
| `template <class Mint> std::vector<Mint> count_labeled_strongly_connected_tournaments(int maximum)` | Strongly connected labeled tournaments. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_unlabeled_rooted_trees(int maximum)` | Unlabeled rooted trees. | `O(N^2)` |
| `template <class Mint> std::vector<Mint> count_unlabeled_trees(int maximum)` | Unlabeled unrooted trees. | `O(N^2 + M(N))` |

All functions use `O(N)` memory, apart from temporary polynomial buffers.

## Example

```cpp
#include "graph/counting.hpp"
#include "math/modint.hpp"
#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;

    auto connected = m1une::graph::count_labeled_connected_graphs<mint>(5);
    auto dags = m1une::graph::count_labeled_dags<mint>(5);

    std::cout << connected[4] << "\n";  // 38
    std::cout << dags[4] << "\n";       // 543
}
```
