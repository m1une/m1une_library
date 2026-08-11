---
title: Rollback Lazy Segment Tree
documentation_of: ../../../ds/segtree/rollback_lazy_segtree.hpp
---

## Overview

`RollbackLazySegtree<ActedMonoid>` provides point assignment, range actions,
range products, and linear-history rollback. `ActedMonoid` must satisfy
`m1une::acted_monoid::IsActedMonoid`.

## Methods

Constructors and read-only methods match
`PersistentLazySegtree<ActedMonoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const F& f)`, `void apply(int left, int right, const F& f)` | Applies an action to a point or `[left, right)`. | $O(\log N)$ |
| `void apply_inplace(...)` | Rollback-recording aliases of `apply`. | $O(\log N)$ |
| `void copy_range_from(const RollbackLazySegtree& source, int left, int right)` | Copies a range from a version in the same pool. | $O(\log N)$ |
| `void copy_range_from(const PersistentLazySegtree<ActedMonoid>& source, int left, int right)` | Persistent-handle overload. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentLazySegtree<ActedMonoid>& current_version() const` | Returns the current persistent state. | $O(1)$ |

Each update call advances history, including an empty-range action. $F$ is at
most the number of nodes created by the undone updates.

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
