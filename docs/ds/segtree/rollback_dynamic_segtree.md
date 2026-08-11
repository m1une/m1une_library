---
title: Rollback Dynamic Segment Tree
documentation_of: ../../../ds/segtree/rollback_dynamic_segtree.hpp
---

## Overview

`RollbackDynamicSegtree<Monoid, Index>` is a sparse segment tree over an
integral half-open domain with point assignment and rollback. Unvisited ranges
retain the configured initial value.

## Methods

Constructors and read-only domain, product, boundary-search, and node-count
methods match `PersistentDynamicSegtree<Monoid, Index>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(Index pos, T value)`, `void set_inplace(Index pos, T value)` | Assigns one point. | $O(\log U)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one assignment. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all materialized nodes. | $O(F)$ |
| `const PersistentDynamicSegtree<Monoid, Index>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$U$ is the domain width and $F = O(\log U)$ per assignment.

## Example

```cpp
#include "ds/segtree/rollback_dynamic_segtree.hpp"
#include "monoid/add.hpp"

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackDynamicSegtree<Add> seg(-100, 100);
int state = seg.snapshot();
seg.set(-4, 7);
seg.rollback(state);
assert(seg.all_prod() == 0);
```
