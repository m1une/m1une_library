# Data structures

Choose a category by the operation you need during a contest. If you construct
an object and then call query methods repeatedly, it belongs here even when the
object is static. For example, cumulative sums are in `ds/range_query/`, while
one-shot sequence computations such as LIS are in `algo/sequence/`.

| Category | Headers |
| --- | --- |
| [`dsu/`](dsu/) | Ordinary, rollback, aggregate, potentialized, persistent, partially persistent, and range-parallel union-find variants |
| [`segtree/`](segtree/) | Dense, dynamic, lazy, dual, generic Beats, specialized chmin/chmax/add, and persistent variants, including `segtree_2d.hpp` and `dual_segtree_2d.hpp` |
| [`range_query/`](range_query/) | Repeated range-query objects: cumulative sums, Fenwick trees, SWAG, static and offline rectangle sums, static inversions/LIS/modes/majorities, sqrt and merge-sort trees, and range-sort range-product queries |
| [`wavelet_matrix/`](wavelet_matrix/) | `wavelet_matrix.hpp`, `dynamic_wavelet_matrix.hpp`, weighted `wavelet_matrix_sum.hpp` and update-optimized `dynamic_wavelet_matrix_sum.hpp` with configurable key width, plus `wavelet_matrix_2d.hpp` for multidimensional orthogonal queries |
| [`dynamic_array/`](dynamic_array/) | Dynamic and persistent implicit-treap arrays, with optional monoid or lazy aggregation |
| [`bst/`](bst/) | Weight-balanced ordered sets and multisets, a fixed-universe predecessor set, and persistent red-black-tree variants with split and merge |
| [`binary_trie/`](binary_trie/) | Binary tries for integer xor queries and monoid aggregates |
| [`dynamic_tree/`](dynamic_tree/) | Link-cut tree, path-oriented variants, and rake-compress link-cut tree |
| [`dynamic_connectivity/`](dynamic_connectivity/) | Online and offline fully dynamic undirected connectivity |
| [`heap/`](heap/) | Array-based double-ended priority queue and pairing-based meldable priority queue |
| [`deque/`](deque/) | Purely persistent real-time double-ended queue |
| [`queue/`](queue/) | Purely persistent real-time FIFO queue |
| [`stack/`](stack/) | Purely persistent constant-time LIFO stack |
| [`interval_set/`](interval_set/) | Disjoint interval set with insertion, deletion, and covered-point queries |
| [`hash_table/`](hash_table/) | `hash_map.hpp`, `hash_set.hpp`, and their shared implementation |

Include headers from the repository root:

```cpp
#include "ds/segtree/segtree.hpp"
```

Convex structures such as CHT, Li Chao tree, and slope trick live under
`convex/`.

Offline query-ordering techniques such as Mo's algorithm live under
`algo/offline/`.

The lazy and Beats variants differ as follows:

| Structure | Purpose |
| --- | --- |
| `LazySegtree<ActedMonoid>` | Ordinary monoid action that always applies directly |
| `SegtreeBeats<ActedMonoid>` | Generic fallible monoid action that descends on failure |
| `ChminChmaxAddSegtree<T>` | Ready-made numeric chmin/chmax/add implementation |
