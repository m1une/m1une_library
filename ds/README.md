# Data structures

Choose a category by the operation you need during a contest. If you construct
an object and then call query methods repeatedly, it belongs here even when the
object is static. For example, cumulative sums are in `ds/range_query/`, while
one-shot sequence computations such as LIS are in `algo/sequence/`.

| Category | Headers |
| --- | --- |
| [`dsu/`](dsu/) | `dsu.hpp`, `rollback_dsu.hpp`, `dsu_monoid.hpp`, `potentialized_dsu.hpp`, `persistent_dsu.hpp`, `persistent_potentialized_dsu.hpp`, `partially_persistent_dsu.hpp` |
| [`segtree/`](segtree/) | Dense, dynamic, lazy, dual, generic Beats, specialized chmin/chmax/add, and persistent variants, including `segtree_2d.hpp` and `dual_segtree_2d.hpp` |
| [`range_query/`](range_query/) | Repeated range-query objects: 1D/2D/3D cumulative sums, static weighted rectangle sums, SWAG, static range inversions/LIS/modes and distinct counting, monoid and custom-state square-root decomposition, Fenwick tree, sqrt/sparse tables, and wavelet matrices |
| [`dynamic_array/`](dynamic_array/) | Dynamic and persistent implicit-treap arrays, with optional monoid or lazy aggregation |
| [`bst/`](bst/) | Ordered sets and multisets implemented with randomized BSTs, plus persistent red-black-tree variants with split and merge |
| [`binary_trie/`](binary_trie/) | Binary tries for integer xor queries and monoid aggregates |
| [`dynamic_tree/`](dynamic_tree/) | Link-cut tree, path-oriented variants, and rake-compress link-cut tree |
| [`dynamic_connectivity/`](dynamic_connectivity/) | Online and offline fully dynamic undirected connectivity |
| [`heap/`](heap/) | Pairing-based meldable priority queue |
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
