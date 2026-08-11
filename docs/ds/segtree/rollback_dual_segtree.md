---
title: Rollback Dual Segment Tree
documentation_of: ../../../ds/segtree/rollback_dual_segtree.hpp
---

## Overview

`RollbackDualSegtree<Monoid>` supports range monoid actions, point assignment,
point queries, and rollback. `Monoid` must satisfy
`m1une::monoid::IsMonoid`; composition order matches `PersistentDualSegtree`.

## Methods

Constructors and read-only methods (`size`, `empty`, `get`, `operator[]`, and
`node_count`) match `PersistentDualSegtree<Monoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `void apply(int pos, const T& value)`, `void apply(int left, int right, const T& value)` | Composes an action at a point or on `[left, right)`. | $O(\log N)$ |
| `void apply_inplace(...)` | Rollback-recording aliases of `apply`. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentDualSegtree<Monoid>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$F$ counts nodes released.

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
