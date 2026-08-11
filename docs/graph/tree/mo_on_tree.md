---
title: Mo on Tree
documentation_of: ../../../graph/tree/mo_on_tree.hpp
---

## Overview

`MoOnTree<T>` reorders static path queries on a tree and maintains the current
path through user-defined insertion and deletion callbacks. It is useful for
path statistics such as the number of distinct colors, value frequencies, and
other set-like aggregates whose one-vertex update is fast.

The structure uses a doubled Euler tour. Every vertex occurs once on entry and
once on exit, so the parity of an Euler interval describes one tree path. A
lowest common ancestor outside that interval is inserted temporarily while its
query is answered.

The graph must be a connected undirected tree built with `Graph<T>::add_edge`.
Inactive edges are ignored by the underlying tree traversal. All indices are
zero-based.

## Construction

```cpp
MoOnTree();
MoOnTree(const m1une::graph::Graph<T>& graph, int root = 0);
void build(const m1une::graph::Graph<T>& graph, int root = 0);
```

Construction roots the tree, builds heavy-light LCA metadata, and creates a
doubled Euler tour in $O(N)$ time and memory. `build` discards all registered
queries.

The chosen root does not change which vertices or edges belong to a path. It
only determines the child vertex used to represent each edge.

## Registering Queries

```cpp
int add_query(int from, int to);
int add_edge_query(int from, int to);
```

`add_query` registers the inclusive vertex path from `from` to `to`.
`add_edge_query` registers the edges on that path. Both return an
insertion-order query ID and take $O(\log N)$ time for an LCA query.

For an edge query, callbacks receive the endpoint farther from the chosen root.
Thus the corresponding original edge ID is `parent_edge(vertex)`. The empty
path registered by `add_edge_query(v, v)` contains no edge.

Vertex queries and edge queries cannot be mixed in one collection. Use two
`MoOnTree` objects if both kinds are needed. `clear()` removes all queries and
allows either kind to be selected again.

## Running the Algorithm

```cpp
mo.run(add, remove, answer);
mo.run(add, remove, answer, block_size);
```

The callbacks have these meanings:

* `add(vertex)` inserts one vertex, or its represented edge in edge mode.
* `remove(vertex)` erases the same item and must undo `add`.
* `answer(query_id)` observes the maintained state for that query.

In edge mode, every callback vertex has a valid nonnegative
`parent_edge(vertex)`; transitions involving the dummy root item are suppressed.

Callbacks can be invoked many times for one item. After `run` returns, the
maintained state is not guaranteed to be empty. For a query whose LCA needed a
temporary insertion, that insertion is removed immediately after `answer`.

With callback cost $O(F)$, the automatic block size gives the usual
$O((N\sqrt Q+Q)F+Q\log Q)$ time bound. A positive explicit block size can be
used for problem-specific tuning.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `MoOnTree()` | Creates an empty object. | $O(1)$ |
| `MoOnTree(graph, root)` | Builds the rooted tree and doubled tour. | $O(N)$ |
| `build(graph, root)` | Rebuilds and clears all queries. | $O(N)$ |
| `size()` | Returns the number of vertices. | $O(1)$ |
| `empty()` | Returns whether the tree is empty. | $O(1)$ |
| `query_count()` | Returns the number of registered queries. | $O(1)$ |
| `queries()` | Returns registered queries in insertion order. | $O(1)$ |
| `parent(v)` | Returns the rooted parent, or `-1` at the root. | $O(1)$ |
| `parent_edge(v)` | Returns the edge to the parent, or `-1` at the root. | $O(1)$ |
| `depth(v)` | Returns the unweighted rooted depth. | $O(1)$ |
| `lca(u, v)` | Returns the lowest common ancestor. | $O(\log N)$ |
| `reserve(q)` | Reserves space for `q` queries. | $O(Q)$ |
| `clear()` | Removes registered queries. | $O(Q)$ |
| `add_query(u, v)` | Adds the inclusive vertex path. | Amortized $O(\log N)$ |
| `add_edge_query(u, v)` | Adds the edge path. | Amortized $O(\log N)$ |
| `order(block_size)` | Returns query IDs in Mo order. | $O(Q\log Q)$ |
| `run(...)` | Processes all queries. | See above |

Public `root`, `entry`, `exit`, and `tour` expose the chosen root and doubled
Euler tour. For every vertex `v`, `tour[entry[v]]` and `tour[exit[v]]` both
equal `v`.

Each public `Query` stores `from`, `to`, transformed half-open interval
`[left, right)`, optional `extra` LCA, insertion-order `id`, and the `edge` mode
flag.

## Example

This computes the number of distinct colors on every vertex path:

```cpp
#include "graph/graph.hpp"
#include "graph/tree/mo_on_tree.hpp"

#include <vector>

int main() {
    m1une::graph::Graph<int> graph(5);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(1, 4);

    std::vector<int> color = {0, 1, 0, 2, 1};
    m1une::tree::MoOnTree<int> mo(graph);
    mo.add_query(3, 2);
    mo.add_query(3, 4);

    std::vector<int> frequency(3);
    std::vector<int> result(mo.query_count());
    int distinct = 0;
    mo.run(
        [&](int vertex) {
            if (frequency[color[vertex]]++ == 0) distinct++;
        },
        [&](int vertex) {
            if (--frequency[color[vertex]] == 0) distinct--;
        },
        [&](int query_id) {
            result[query_id] = distinct;
        }
    );
}
```
