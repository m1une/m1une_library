---
title: Rollback Dual Segment Tree
documentation_of: ../../../ds/segtree/rollback_dual_segtree.hpp
---

## Overview

`RollbackDualSegtree<Monoid>` supports range monoid actions, point assignment,
point queries, and rollback. `Monoid` must satisfy
`m1une::monoid::IsMonoid`; composition order matches `DualSegtree`.

## Methods

Constructors and read-only methods follow `DualSegtree<Monoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const T& value)`, `void apply(int left, int right, const T& value)` | Composes an action at a point or on `[left, right)`. | $O(\log N)$ |
| `void apply_inplace(...)` | Aliases of `apply`. | $O(\log N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a tree node is saved only before its first mutation.

## Example

```cpp
#include "ds/segtree/rollback_dual_segtree.hpp"
#include "monoid/add.hpp"

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackDualSegtree<Add> seg(4);
int state = seg.snapshot();
seg.apply(0, 3, 5);
seg.rollback(state);
assert(seg.get(1) == 0);
```
