---
title: Rollback Segment Tree Beats
documentation_of: ../../../ds/segtree/rollback_segtree_beats.hpp
---

## Overview

`RollbackSegtreeBeats<ActedMonoid>` is the rollback counterpart of
`PersistentSegtreeBeats`. `ActedMonoid` must satisfy
`m1une::beats_acted_monoid::IsBeatsActedMonoid`; failed whole-node actions
descend exactly as in the persistent structure.

## Methods

Constructors and read-only product, materialization, boundary-search, and
node-count methods match `PersistentSegtreeBeats<ActedMonoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const F& f)`, `void apply(int left, int right, const F& f)` | Applies a fallible action. | Acted-monoid dependent, amortized as for Segment Tree Beats |
| `void apply_inplace(...)` | Rollback-recording aliases of `apply`. | Same as `apply` |
| `void copy_range_from(const RollbackSegtreeBeats& source, int left, int right)` | Copies a same-pool range. | $O(\log N)$ |
| `void copy_range_from(const PersistentSegtreeBeats<ActedMonoid>& source, int left, int right)` | Persistent-handle overload. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentSegtreeBeats<ActedMonoid>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$F$ counts nodes created only for the abandoned updates.

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
