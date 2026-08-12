---
title: Rollback Dynamic Lazy Segment Tree
documentation_of: ../../../ds/segtree/rollback_dynamic_lazy_segtree.hpp
---

## Overview

`RollbackDynamicLazySegtree<ActedMonoid, Index>` is a sparse lazy segment tree
with point assignment, range actions, range products, and rollback over an
integral half-open domain.

## Methods

Constructors and read-only methods follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Resets the logical tree to its initial value. | $O(P)$ without snapshots; $O(1)$ with an active snapshot |
| `void set(Index pos, T value)`, `void set_inplace(Index pos, T value)` | Assigns one point. | $O(\log U)$ |
| `void apply(Index pos, const F& f)`, `void apply(Index left, Index right, const F& f)` | Applies an action to a point or range. | $O(\log U)$ |
| `void apply_inplace(...)` | Aliases of `apply`. | $O(\log U)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all materialized nodes. | $O(F)$ |

$U$ is the domain width, $P$ is the number of materialized nodes, and $F$ is
the number of saved or newly allocated nodes discarded by the operation.

## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a materialized node is saved only before its first mutation; newly allocated nodes are truncated directly by rollback.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/rollback_dynamic_lazy_segtree.hpp"

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::ds::RollbackDynamicLazySegtree<AM> seg(0, 100, AM::id());
int state = seg.snapshot();
seg.set(3, AM::make(2));
seg.apply(3, 4, 5);
seg.rollback(state);
assert(seg.get(3).sum == 0);
```
