---
title: Rollback Ordered Set
documentation_of: ../../../ds/bst/rollback_ordered_set.hpp
---

## Overview

`RollbackOrderedSet<T, Compare>` is an ordered set with order statistics and
linear-history rollback. It reuses the persistent red-black-tree node pool.
`Compare` must define a strict weak ordering, as for `std::set`.

## Methods

Constructors and all read-only search, order-statistic, conversion, and split
methods match `PersistentOrderedSet<T, Compare>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the set and advances history. | $O(1)$ |
| `bool insert(T key)` | Inserts a key, reports whether it was new, and advances history. | $O(\log N)$ |
| `bool erase(const T& key)` | Erases a key, reports whether it existed, and advances history. | $O(\log N)$ |
| `void merge(const RollbackOrderedSet& other)` | Appends an ordered, disjoint set and advances history. | $O(\log N)$ |
| `void merge(const PersistentOrderedSet<T, Compare>& other)` | Persistent-handle overload of `merge`. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentOrderedSet<T, Compare>& current_version() const` | Returns the current persistent state. | $O(1)$ |

Each attempted update advances history, even if it does not change membership.
$F$ counts nodes whose final reference is released.

## Example

```cpp
#include "ds/bst/rollback_ordered_set.hpp"

m1une::ds::RollbackOrderedSet<int> set;
set.insert(4);
int state = set.snapshot();
set.insert(2);
set.rollback(state);
assert(!set.contains(2));
```
