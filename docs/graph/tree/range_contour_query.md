---
title: Range Contour Query on Tree
documentation_of: ../../../graph/tree/range_contour_query.hpp
---

## Overview

This header supports commutative-group operations selected by an unweighted
distance interval from a vertex. Its generic interfaces are:

* `VertexApplyRangeContourProduct<Group>` applies a group element at one vertex
  and returns the group product over vertices at distances in `[left, right)`.
* `VertexGetRangeContourApply<Group>` applies a group element to every vertex at
  distances in `[left, right)` and retrieves one vertex value.

The additive convenience wrappers preserve the familiar problem-specific API:

* `VertexAddRangeContourSum<T>` supports vertex additions and sums over all
  vertices at distances in `[left, right)`.
* `VertexGetRangeContourAdd<T>` adds to all vertices at distances in
  `[left, right)` and retrieves one vertex value.

Both structures use centroid decomposition, inclusion-exclusion, and Fenwick
trees. The input must be a connected undirected tree built with `add_edge`.
Edge costs are ignored; distance means the number of edges. Inactive edges are
ignored when validating and building the tree.

## Requirements

`Group` must satisfy `m1une::monoid::IsCommutativeGroup`:

* `using value_type = T;`
* `static T id();`
* `static T op(const T&, const T&);`
* `static T inv(const T&);`

The operation must be associative and commutative, `id()` must be its identity,
and `inv(x)` must return the group inverse. `m1une::monoid::Add<T>` and
`m1une::monoid::Xor<T>` are ready-made policies. Non-invertible operations such
as minimum, maximum, GCD, AND, and OR are not supported because centroid
inclusion-exclusion requires inverses.

## Interfaces

```cpp
template <m1une::monoid::IsCommutativeGroup Group>
class VertexApplyRangeContourProduct {
public:
    using T = typename Group::value_type;

    VertexApplyRangeContourProduct();

    template <class EdgeCost>
    explicit VertexApplyRangeContourProduct(
        const Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    );

    template <class EdgeCost>
    void build(
        const Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    );

    int size() const;
    bool empty() const;
    T get(int vertex) const;
    void apply(int vertex, const T& value);
    void set(int vertex, const T& value);
    T prod(int vertex, int left_distance, int right_distance) const;
};

template <m1une::monoid::IsCommutativeGroup Group>
class VertexGetRangeContourApply {
public:
    using T = typename Group::value_type;

    VertexGetRangeContourApply();

    template <class EdgeCost>
    explicit VertexGetRangeContourApply(
        const Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    );

    template <class EdgeCost>
    void build(
        const Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    );

    int size() const;
    bool empty() const;
    T get(int vertex) const;
    void point_apply(int vertex, const T& value);
    void set(int vertex, const T& value);
    void apply(
        int vertex,
        int left_distance,
        int right_distance,
        const T& value
    );
};

template <class T>
class VertexAddRangeContourSum;

template <class T>
class VertexGetRangeContourAdd;
```

`VertexAddRangeContourSum<T>` is the additive wrapper around
`VertexApplyRangeContourProduct<m1une::monoid::Add<T>>`. It adds `add` and `sum`
as names for `apply` and `prod`. `VertexGetRangeContourAdd<T>` wraps
`VertexGetRangeContourApply<m1une::monoid::Add<T>>` and adds the point method
`add` as a name for `point_apply`.

An omitted `initial` vector initializes every value to `T{}`. An explicitly
provided vector must have one value per vertex. Empty trees are supported.
Distance bounds must satisfy `0 <= left_distance <= right_distance`; bounds
beyond the tree diameter are allowed and are clipped naturally.

## Operations

| Method | Description | Complexity |
| --- | --- | --- |
| `VertexApplyRangeContourProduct()` / `VertexGetRangeContourApply()` | Constructs an empty generic object. | $O(1)$ |
| `template <class EdgeCost> explicit VertexApplyRangeContourProduct(const Graph<EdgeCost>& graph, const std::vector<T>& initial = {})` | Builds the point-apply/range-product structure. | $O(N\log^2 N)$ |
| `template <class EdgeCost> explicit VertexGetRangeContourApply(const Graph<EdgeCost>& graph, const std::vector<T>& initial = {})` | Builds the range-apply/point-get structure. | $O(N\log^2 N)$ |
| `template <class EdgeCost> void build(const Graph<EdgeCost>& graph, const std::vector<T>& initial = {})` | Replaces the current tree and values; available on both classes. | $O(N\log^2 N)$ |
| `int size() const` | Returns the number of vertices. | $O(1)$ |
| `bool empty() const` | Returns whether the structure has no vertices. | $O(1)$ |
| `T VertexApplyRangeContourProduct::get(int vertex) const` | Returns the current vertex value. | $O(1)$ |
| `void VertexApplyRangeContourProduct::apply(int vertex, const T& value)` | Combines one vertex with `value`. | $O(\log^2 N)$ |
| `void VertexApplyRangeContourProduct::set(int vertex, const T& value)` | Replaces one vertex value. | $O(\log^2 N)$ |
| `T VertexApplyRangeContourProduct::prod(int vertex, int left_distance, int right_distance) const` | Returns the group product at distances in `[left_distance, right_distance)`. | $O(\log^2 N)$ |
| `T VertexGetRangeContourApply::get(int vertex) const` | Returns one current vertex value. | $O(\log^2 N)$ |
| `void VertexGetRangeContourApply::point_apply(int vertex, const T& value)` | Combines one vertex with `value`. | $O(1)$ |
| `void VertexGetRangeContourApply::set(int vertex, const T& value)` | Replaces one current vertex value. | $O(\log^2 N)$ |
| `void VertexGetRangeContourApply::apply(int vertex, int left_distance, int right_distance, const T& value)` | Combines every value at distances in `[left_distance, right_distance)` with `value`. | $O(\log^2 N)$ |
| `void VertexAddRangeContourSum::add(int vertex, const T& delta)` | Additive alias of point `apply`. | $O(\log^2 N)$ |
| `T VertexAddRangeContourSum::sum(int vertex, int left_distance, int right_distance) const` | Additive alias of `prod`. | $O(\log^2 N)$ |
| `void VertexGetRangeContourAdd::add(int vertex, const T& delta)` | Additive alias of `point_apply`. | $O(1)$ |

Both structures use $O(N\log N)$ memory. Operations mutate the structure;
queries do not.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/tree/range_contour_query.hpp"
#include "monoid/xor.hpp"

#include <cassert>
#include <vector>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);

    std::vector<long long> values = {1, 2, 3, 4};
    m1une::tree::VertexAddRangeContourSum<long long> sums(graph, values);
    assert(sums.sum(0, 1, 3) == 9);
    sums.add(2, 5);
    assert(sums.sum(0, 2, 3) == 12);

    m1une::tree::VertexGetRangeContourAdd<long long> additions(graph, values);
    additions.apply(0, 1, 3, 10);
    assert(additions.get(0) == 1);
    assert(additions.get(3) == 14);

    using Xor = m1une::monoid::Xor<unsigned>;
    m1une::tree::VertexApplyRangeContourProduct<Xor> xor_query(
        graph,
        std::vector<unsigned>{1, 2, 4, 8}
    );
    assert(xor_query.prod(0, 1, 3) == (2U ^ 4U ^ 8U));
}
```
