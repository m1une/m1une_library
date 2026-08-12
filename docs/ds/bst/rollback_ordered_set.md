---
title: Rollback Ordered Set
documentation_of: ../../../ds/bst/rollback_ordered_set.hpp
---

## Overview

`RollbackOrderedSet<T, Compare>` is an ordered set with order statistics and
registered-snapshot rollback. It stores its mutable ordered tree independently of any versioned structure.
`Compare` must define a strict weak ordering, as for `std::set`.

## Methods

Constructors and read-only search, order-statistic, conversion, and split
methods follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the set. | $O(N)$ |
| `bool insert(T key)` | Inserts a key, reports whether it was new. | $O(\log N)$ |
| `bool erase(const T& key)` | Erases a key, reports whether it existed. | $O(\log N)$ |
| `void merge(const RollbackOrderedSet& other)` | Inserts an ordered, disjoint set of size $M$. | $O(M \log(N+M))$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

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
