---
title: Rollback Dynamic Dual Segment Tree
documentation_of: ../../../ds/segtree/rollback_dynamic_dual_segtree.hpp
---

## Overview

`RollbackDynamicDualSegtree<Monoid, Index>` is a sparse dual segment tree with
range action composition, point assignment, point queries, and rollback over an
integral half-open domain.

## Methods

Constructors and read-only methods follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(Index pos, T value)`, `void set_inplace(Index pos, T value)` | Assigns one point. | $O(\log U)$ |
| `void apply(Index pos, const T& value)`, `void apply(Index left, Index right, const T& value)` | Composes an action on a point or range. | $O(\log U)$ |
| `void apply_inplace(...)` | Aliases of `apply`. | $O(\log U)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all materialized nodes. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a materialized node is saved only before its first mutation; newly allocated nodes are truncated directly by rollback.

## Example

```cpp
#include "ds/segtree/rollback_dynamic_dual_segtree.hpp"
#include "monoid/add.hpp"

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackDynamicDualSegtree<Add> seg(-100, 100, 0);
int state = seg.snapshot();
seg.apply(-5, 6, 3);
seg.rollback(state);
assert(seg.get(0) == 0);
```
