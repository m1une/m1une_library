---
title: Rollback Segment Tree Beats
documentation_of: ../../../ds/segtree/rollback_segtree_beats.hpp
---

## Overview

`RollbackSegtreeBeats<ActedMonoid>` is a mutable Segment Tree Beats with registered snapshots. `ActedMonoid` must satisfy
`m1une::beats_acted_monoid::IsBeatsActedMonoid`; failed whole-node actions
descend exactly as in the mutable structure.

## Methods

Constructors and read-only product, materialization, boundary-search, and node-count methods follow `SegtreeBeats<ActedMonoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const F& f)`, `void apply(int left, int right, const F& f)` | Applies a fallible action. | Acted-monoid dependent, amortized as for Segment Tree Beats |
| `void apply_inplace(...)` | Aliases of `apply`. | Same as `apply` |
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
#include "beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp"
#include "ds/segtree/rollback_segtree_beats.hpp"

#include <vector>

using AM = m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long long>;
m1une::ds::RollbackSegtreeBeats<AM> seg(
    std::vector<long long>{1, 5, 3}
);
int state = seg.snapshot();
AM::operator_type add;
add.add = 2;
add.lower = AM::negative_infinity;
add.upper = AM::positive_infinity;
seg.apply(0, 3, add);
seg.rollback(state);
assert(seg.all_prod().sum == 9);
```
