---
title: Rollback Dynamic Dual Segment Tree
documentation_of: ../../../ds/segtree/rollback_dynamic_dual_segtree.hpp
---

## Overview

`RollbackDynamicDualSegtree<Monoid, Index>` is a sparse dual segment tree with
range action composition, point assignment, point queries, and rollback over an
integral half-open domain.

## Methods

Constructors and read-only methods match
`PersistentDynamicDualSegtree<Monoid, Index>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(Index pos, T value)`, `void set_inplace(Index pos, T value)` | Assigns one point. | $O(\log U)$ |
| `void apply(Index pos, const T& value)`, `void apply(Index left, Index right, const T& value)` | Composes an action on a point or range. | $O(\log U)$ |
| `void apply_inplace(...)` | Rollback-recording aliases of `apply`. | $O(\log U)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all materialized nodes. | $O(F)$ |
| `const PersistentDynamicDualSegtree<Monoid, Index>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$U$ is the domain width; $F$ counts released nodes.

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
