---
title: Library Guide and Conventions
layout: page
permalink: /guide.html
---

## Getting Started

Add the repository root to your include path and compile with C++20 or later.
Include the headers you use; a category's `all.hpp` includes its public headers
for convenience. Public names are under `m1une`; each header's example shows
the namespace to use.

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/add.hpp"
#include <cassert>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::ds::Segtree<Sum> seg(std::vector<long long>{2, 4, 6});
    seg.set(1, 10);
    assert(seg.prod(0, 2) == 12);
}
```

Compile a solution and optionally expand its library includes for submission:

```sh
g++ -std=c++20 -O2 -I /path/to/m1une_library main.cpp -o main
python3 /path/to/m1une_library/expander.py main.cpp > bundled.cpp
```

## Indices and Ranges

Array indices and graph vertex IDs are zero-based unless a page explicitly
specifies otherwise. A range `[l, r)` includes `l` and excludes `r`; its length
is `r - l`. For an array of length `N`, valid range endpoints satisfy
`0 <= l <= r <= N`, and a valid element index satisfies `0 <= p < N`.
Whether an empty range is accepted is part of each function's contract.

A monoid range product on an empty range is the identity. On a nonempty range,
`prod(l, r)` combines elements in array order, from `l` through `r - 1`.
Here, “product” means the monoid operation: it may be a sum, minimum,
concatenation, or composition rather than ordinary multiplication.

An `ord` returned by an argmin/argmax aggregate is relative to the queried
range. If `ord >= 0`, its array index is `l + ord`. Arithmetic-progression
updates also use a local index: in `apply(l, r, {a, b})`, the first element
uses index zero, so the progression is `b, a + b, 2 * a + b, ...`.

## Complexity Notation

Each page defines additional symbols or overrides these defaults when needed.

| Symbol | Default meaning |
| --- | --- |
| `N` | Number of elements or graph vertices; for one sequence, its length. |
| `M` | Number of logical graph edges; for two sequences, the second length. |
| `Q` | Number of queries or updates. |
| `K`, `B`, `H` | A page-specific capacity, bit width, or history size; see that page. |

Bounds are worst-case unless marked **amortized** (averaged over a sequence of
operations) or **expected** (averaged over randomness). Construction includes
initializing the data structure. Outputting a vector also takes time and space
for its returned elements.

Generic data-structure bounds assume constant-time operations and copies on
their stored values. For a matrix monoid with dimension `D`, for example, each
matrix product costs $O(D^3)$, so a segment-tree range product costs
$O(D^3 \log N)$. Bit-count aggregates similarly introduce a factor of `BITS`.
Callback and predicate costs must also be included when they are not constant.

For small inputs, logarithmic bounds use $1 + \log_2(\max(1, N))$ implicitly.
Numeric types must represent all intermediate values; choosing `long long`
does not itself guarantee that sums or products cannot overflow.

## Choosing a Range Data Structure

| Workload | Start with | Requirement |
| --- | --- | --- |
| Point addition and range sum | [Fenwick tree](https://m1une.github.io/m1une_library/ds/range_query/fenwick_tree.hpp) | Addition and subtraction. |
| Point assignment and range aggregate | [Segment tree](https://m1une.github.io/m1une_library/ds/segtree/segtree.hpp) | A monoid. |
| Range update and range aggregate | [Lazy segment tree](https://m1une.github.io/m1une_library/ds/segtree/lazy_segtree.hpp) | An acted monoid whose updates apply to each aggregate. |
| Range update and point query | [Dual segment tree](https://m1une.github.io/m1une_library/ds/segtree/dual_segtree.hpp) | A monoid that composes the updates. |
| Static range minimum/maximum | [Sparse table](https://m1une.github.io/m1une_library/ds/range_query/sparse_table.hpp) | An idempotent monoid: `op(x, x) == x`. |
| Static range aggregate | [Disjoint sparse table](https://m1une.github.io/m1une_library/ds/range_query/disjoint_sparse_table.hpp) | Any monoid. |
| Queue with an aggregate | [Sliding window aggregation](https://m1une.github.io/m1une_library/ds/range_query/sliding_window_aggregation.hpp) | Any monoid. |

## Monoids and Updates

A [monoid](https://m1une.github.io/m1une_library/monoid/concept.hpp) supplies
`value_type`, `id()`, and associative `op(a, b)`. The identity is neutral on both
sides. Commutativity is optional: array order still matters for matrices,
strings, and functions.

An [acted monoid](https://m1une.github.io/m1une_library/acted_monoid/concept.hpp)
also supplies `operator_type`, `op_id()`, `op_comp(f, g)`, and `mapping(f, x)`.
`op_comp(f, g)` always means **apply `g` first, then `f`**. A mapping returns a
new aggregate; the containing data structure performs the update.

Do not infer function-composition order from array order. In
[`Affine`](https://m1une.github.io/m1une_library/monoid/affine.hpp), `op(f, g)`
is `f(g(x))`; in
[`Permutation`](https://m1une.github.io/m1une_library/monoid/permutation.hpp),
`op(a, b)[i]` is `b[a[i]]`. Each page states its convention.

For length-aware aggregates, `id()` represents **zero elements**.
`LazySegtree<AM>(n)` fills the leaves with that identity; it does not create
`n` ordinary zero-valued elements. Initialize from a vector of raw elements
when `make(value)` is available, or build a vector of `AM::make(value)` nodes.
Point assignment with `set(p, x)` expects the aggregate type itself.

The C++ concepts check signatures, not mathematical laws. For custom operations,
verify associativity, identities, composition order, and the mapping laws
described on the concept page.

## Versions and Rollback

| Structure | Update behavior | How to read an older state |
| --- | --- | --- |
| Ordinary mutable structure | Changes the current object. | No history is retained. |
| Persistent structure | An update such as `set` returns a new version. Store the return value. An explicitly named `_inplace` method changes the current handle while preserving other versions. | Keep and query the old handle. |
| Partially persistent DSU | Each `merge`, even a redundant one, advances time. Updates apply to the latest state. | Pass the requested time to a query. |
| Rollback structure | Changes the current object and records history according to that structure's rules. | Save `snapshot()`, then use `rollback(state)` on the current history path. |

Snapshot tokens are specific to an object and its current history path. The
rollback DSUs use history positions and support `undo()`; many other rollback
containers require registered snapshots and invalidate newer tokens after a
rollback. Check the relevant page before reusing a token or clearing history.

## Graph Conventions

[`Graph<T>`](https://m1une.github.io/m1une_library/graph/graph.hpp) stores directed
edges with `add_directed_edge` and undirected edges with `add_edge`. One
undirected logical edge has two adjacency arcs sharing an edge ID. Unless
specified otherwise, `M` counts logical edges, including inactive edges that
remain stored and must be scanned. The graph's `edge_count()` includes them.

Algorithm pages specify graph orientation, cost restrictions, unreachable
results, and failure behavior. For example, Dijkstra requires nonnegative
costs and its `reachable(v)` method distinguishes an unreachable vertex from a
finite distance equal to a sentinel.
