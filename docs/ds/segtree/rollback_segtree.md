---
title: Rollback Segment Tree
documentation_of: ../../../ds/segtree/rollback_segtree.hpp
---

## Overview

`RollbackSegtree<Monoid>` is a mutable segment tree with point assignment,
range products, and registered-snapshot rollback. `Monoid` must satisfy
`m1une::monoid::IsMonoid`. The tree uses one contiguous mutable segment-tree array.

## Methods

Constructors and read-only methods follow `Segtree<Monoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |

$F = O(\log N)$ per undone assignment and counts nodes released.

## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, each assigned position saves its old value only once.

## Example

```cpp
#include "ds/segtree/rollback_segtree.hpp"
#include "monoid/add.hpp"

#include <vector>

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackSegtree<Add> seg(std::vector<long long>{1, 2, 3});
int state = seg.snapshot();
seg.set(1, 8);
seg.rollback(state);
assert(seg.all_prod() == 6);
```
