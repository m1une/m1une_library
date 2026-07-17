[![verify](https://github.com/m1une/m1une_library/actions/workflows/verify.yml/badge.svg?branch=main)](https://github.com/m1une/m1une_library/actions/workflows/verify.yml)  [![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=m1une's+library+&color=brightgreen&logo=github)](https://m1une.github.io/m1une_library/)

# m1une's library

C++20 library for competitive programming by [m1une](https://atcoder.jp/users/m1une).

This repository is organized as header-only building blocks. Convex tools such
as Li Chao tree, CHT, slope trick, Alien Trick, and Monge optimizations live
under `convex/`. Use `ds/` for non-convex stateful query/update objects, and
`algo/` for one-shot, domain-neutral techniques such as sequence algorithms,
search-over-answer helpers, offline query ordering, and enumeration. A header
that builds an object and answers repeated queries, even with no updates, belongs
to `ds/`; for example, cumulative sums stay in `ds/range_query/`.
Graph-specialized algorithms, including tree and flow routines, live under
`graph/`; algebraic and numeric
tools, including FPS and matrices, live under `math/`. Reusable algebraic
definitions live in `monoid/` and `acted_monoid/` so they can be combined
without rewriting boilerplate during a contest.

## Structure

| Directory | Contents |
| --- | --- |
| `convex/` | Convex-structure and convex-optimization tools, including CHT, Li Chao tree, slope trick, Alien Trick, Monge/SMAWK/Knuth/D&C optimization, and structured min-plus/max-plus convolution. |
| `algo/` | One-shot algorithms that are not tied to a graph/string/geometry/convex domain, including sequence, search, offline, and enumeration helpers. |
| `graph/` | General graph algorithms and builders, plus `graph/tree/` for Euler tours, rooted-tree tools, Cartesian tree construction, and `graph/flow/` for flow networks. |
| `optimization/` | Combinatorial and numeric optimization solvers such as project selection, Hungarian assignment, simplex LP, and integer LP. |
| `matroid/` | Uniform, partition, graphic, and linear matroids, plus weighted and unweighted matroid intersection. |
| `geometry/` | 2D points, lines, rays, segments, polygons, rectangle-union area, convex hulls, half-plane intersection, lattice-point counting, and circles. |
| `ds/` | Categorized data structures for range queries, online/offline dynamic connectivity, dynamic sequences and trees, ordered sets, heaps, intervals, and hash tables. |
| `monoid/` | Reusable monoids for generic data structures such as `Segtree`. |
| `acted_monoid/` | Acted monoids for lazy propagation structures such as `LazySegtree` and generic `SegtreeBeats`, including generic range assignment/range product. |
| `math/` | Number theory, modular arithmetic, combinatorics and partition functions, set power series and FPS/polynomials, XOR bases and bitwise transforms, matrices, exact rationals, and integer arithmetic. |
| `string/` | Z/KMP, wildcard matching, edit distance, Manacher, minimum rotation, Lyndon factorization, run enumeration, longest common extension/subsequence/substring, eertrees, suffix automata/arrays, tries, Aho-Corasick, and string hashes. |
| `utilities/` | Fast I/O, convolution-backed arbitrary-precision integers, parsing, dice, 2D grid transforms, integer helpers, compression, random generation, stress testing, and general contest utilities. |
| `verify/` | Online Judge Verify Helper tests. |
| `docs/` | Markdown documentation for the public headers. |

### Namespace map

Namespaces intentionally do not mirror nested directories. Public APIs use one
short namespace segment after `m1une::`; nested directories are for browsing.

| Directory | Namespace |
| --- | --- |
| `convex/` | `m1une::convex` |
| `algo/` | `m1une::algo` |
| `ds/` | `m1une::ds` |
| `graph/` | `m1une::graph` |
| `graph/flow/` | `m1une::flow` |
| `graph/tree/` | `m1une::tree` |
| `math/` | `m1une::math` |
| `math/fps/` | `m1une::fps` |
| `math/matrix/` | `m1une::matrix` |
| `optimization/` | `m1une::opt` |
| `geometry/`, `string/`, `matroid/`, `monoid/` | Matching short top-level namespaces. |

### Algorithm categories

| Directory | Use it for |
| --- | --- |
| `algo/sequence/` | Array and sequence algorithms such as LIS, inversion count, distinct-subsequence counting, run-length encoding, and meet-in-the-middle subset sum. |
| `algo/search/` | Search-over-answer and unimodal optimization helpers. |
| `algo/offline/` | Offline query processing such as Mo's algorithm. |
| `algo/enumeration/` | Enumeration helpers for combinations, bitmasks, Gray codes, and aligned segment-tree ranges. |
| `algo/dp/` | Domain-neutral DP helpers such as knapsack routines. |

Rule of thumb: if you call a function once and use its returned result directly,
look in `algo/`. If you construct an object and then call query methods such as
`sum`, `prod`, `fold`, or `get`, look in `ds/`. Small syntax helpers and contest
plumbing live in `utilities/`.

### Convex categories

| Directory | Use it for |
| --- | --- |
| `convex/convex_hull_trick.hpp` | Monotone-slope CHT for adding lines and querying an optimum at `x`. |
| `convex/li_chao_tree.hpp` | Dynamic Li Chao tree for arbitrary line and line-segment insertion. |
| `convex/monge/` | Monge/SMAWK/Knuth/D&C optimization, LARSCH, checks, and structured min-plus/max-plus convolution. |
| `convex/slope_trick.hpp` | Slope trick for maintaining convex piecewise-linear functions. |
| `convex/alien_trick.hpp` | Exact-count optimization through Lagrangian relaxation. |

### Data structure categories

| Directory | Use it for |
| --- | --- |
| `ds/dsu/` | Connectivity, component aggregation, potentials, range-parallel merging, and persistent union-find. |
| `ds/segtree/` | Dense and dynamic segment trees, lazy propagation, dual segment trees, and persistent variants. |
| `ds/range_query/` | Objects built for repeated range queries, including cumulative sums, range LIS/modes/majorities and distinct counting, Fenwick trees, and static sparse-table queries. |
| `ds/wavelet_matrix/` | Static and dynamic wavelet matrices for range order statistics, frequencies, weighted range sums, and multidimensional orthogonal queries. |
| `ds/dynamic_array/` | Implicit-treap sequences with insertion, deletion, reversal, aggregation, or persistence. |
| `ds/bst/` | Weight-balanced ordered sets and multisets, a fixed-universe predecessor set, and persistent red-black-tree variants with split/merge APIs. |
| `ds/binary_trie/` | Binary tries for integer xor queries and optional monoid aggregates. |
| `ds/dynamic_tree/` | Link-cut trees and rake-compress trees for changing forests. |
| `ds/dynamic_connectivity/` | Online and offline connectivity under edge insertions and deletions. |
| `ds/heap/` | Double-ended and meldable priority queues. |
| `ds/deque/` | Purely persistent real-time double-ended queues. |
| `ds/queue/` | Purely persistent real-time FIFO queues. |
| `ds/stack/` | Purely persistent constant-time LIFO stacks. |
| `ds/interval_set/` | Disjoint interval maintenance. |
| `ds/hash_table/` | Hash maps and hash sets. |

See [`ds/README.md`](ds/README.md) for the complete header index.

## Usage

Include headers directly from the repository root and compile with C++20:

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/add.hpp"
```

Most generic data structures are parameterized by a monoid or acted monoid, so prefer the ready-made definitions in `monoid/` and `acted_monoid/` when possible.

```cpp
using Sum = m1une::monoid::Add<long long>;
m1une::ds::Segtree<Sum> seg(std::vector<long long>{1, 2, 3, 4});

seg.set(1, 10);
long long answer = seg.prod(0, 3);  // 1 + 10 + 3
```

To shrink an expanded submission, run the dependency-free compressor. It removes
comments and redundant whitespace, shortens file-owned variables, fields, types,
namespaces, and unqualified functions, and introduces profitable short aliases
for builtin types, namespaces, and standard templates such as `std::vector` and
`std::pair`:

```sh
python3 compressor.py bundled.cpp -o submission.cpp --stats
```

The default aggressive mode assumes the input is a self-contained translation
unit whose names are not consumed by another file. Pass `--no-rename` to keep all
identifiers unchanged and disable generated aliases. Line-control directives
(`#line` and compiler line markers) and duplicate unconditional direct includes
are removed in both modes. The compressor
preserves the C++ preprocessing-token stream across removed whitespace, handles
comments and escaped newlines in translation-phase order, and preserves other
preprocessor directives, user-defined literals, string and character literals,
and raw strings.

## Documentation Conventions

* Ranges are half-open: `[l, r)` includes `l` and excludes `r`.
* Indices are zero-based.
* `prod(l, r)` means "fold the values in `[l, r)` with the selected monoid".
* Lazy segment trees use acted monoids: the value monoid describes queries, and
  the operator monoid describes updates.
* Some monoids store metadata in their `value_type`. When a monoid provides
  `make(value)` or `make(value, index)`, the data structures use it automatically
  while building from a vector of another type.

## Verification

The repository is configured for `online-judge-verify-helper`. Locally, the core verification files can also be compiled with:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -I. verify/ds/segtree/segtree.test.cpp
```
