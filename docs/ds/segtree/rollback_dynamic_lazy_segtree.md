---
title: Rollback Dynamic Lazy Segment Tree
documentation_of: ../../../ds/segtree/rollback_dynamic_lazy_segtree.hpp
---

## Overview

`RollbackDynamicLazySegtree<ActedMonoid, Index>` is a sparse lazy segment tree
with point assignment, range actions, range products, and rollback over an
integral half-open domain.

## Methods

Constructors and read-only methods match
`PersistentDynamicLazySegtree<ActedMonoid, Index>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(Index pos, T value)`, `void set_inplace(Index pos, T value)` | Assigns one point. | $O(\log U)$ |
| `void apply(Index pos, const F& f)`, `void apply(Index left, Index right, const F& f)` | Applies an action to a point or range. | $O(\log U)$ |
| `void apply_inplace(...)` | Rollback-recording aliases of `apply`. | $O(\log U)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all materialized nodes. | $O(F)$ |
| `const PersistentDynamicLazySegtree<ActedMonoid, Index>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$U$ is the domain width; $F$ counts released nodes.

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
