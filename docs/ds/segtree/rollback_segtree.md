---
title: Rollback Segment Tree
documentation_of: ../../../ds/segtree/rollback_segtree.hpp
---

## Overview

`RollbackSegtree<Monoid>` is a mutable segment tree with point assignment,
range products, and linear-history rollback. `Monoid` must satisfy
`m1une::monoid::IsMonoid`. Saved roots share persistent nodes.

## Methods

Constructors and read-only methods (`size`, `empty`, `get`, `operator[]`,
`prod`, `all_prod`, `to_vector`, `max_right`, `min_left`, and `node_count`)
match `PersistentSegtree<Monoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point and advances history. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one assignment. | $O(F)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentSegtree<Monoid>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$F = O(\log N)$ per undone assignment and counts nodes released.

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
