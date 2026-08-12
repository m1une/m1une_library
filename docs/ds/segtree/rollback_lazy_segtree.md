---
title: Rollback Lazy Segment Tree
documentation_of: ../../../ds/segtree/rollback_lazy_segtree.hpp
---

## Overview

`RollbackLazySegtree<ActedMonoid>` provides point assignment, range actions,
range products, and registered-snapshot rollback. `ActedMonoid` must satisfy
`m1une::acted_monoid::IsActedMonoid`.

## Methods

Constructors and read-only methods follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const F& f)`, `void apply(int left, int right, const F& f)` | Applies an action to a point or `[left, right)`. | $O(\log N)$ |
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
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/rollback_lazy_segtree.hpp"

#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::ds::RollbackLazySegtree<AM> seg(std::vector<long long>{1, 2, 3});
int state = seg.snapshot();
seg.apply(0, 2, 5);
seg.rollback(state);
assert(seg.all_prod().sum == 6);
```
