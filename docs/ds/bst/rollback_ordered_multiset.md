---
title: Rollback Ordered Multiset
documentation_of: ../../../ds/bst/rollback_ordered_multiset.hpp
---

## Overview

`RollbackOrderedMultiset<T, Compare>` is an ordered multiset with order
statistics and registered-snapshot rollback. It shares nodes between saved states.
`Compare` must define a strict weak ordering.

## Methods

Constructors and read-only methods follow `OrderedMultiset<T, Compare>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the multiset. | $O(N)$ |
| `void insert(T key, int multiplicity = 1)`, `void insert_inplace(T key, int multiplicity = 1)` | Inserts positive multiplicity. | $O(\log N)$ |
| `bool erase_one(const T& key)`, `bool erase(const T& key)` | Erases one copy, reports whether one existed,. | $O(\log N)$ |
| `bool erase_one_inplace(const T& key)`, `bool erase_inplace(const T& key)` | Aliases of `erase_one`. | $O(\log N)$ |
| `int erase_all(const T& key)` | Erases every copy and returns the erased multiplicity. | $O(\log N)$ |
| `bool erase_all_inplace(const T& key)` | Erases every copy and reports whether the key existed. | $O(\log N)$ |
| `void merge(const RollbackOrderedMultiset& other)` | Inserts an ordered multiset of size $M$. | $O(M \log(N+M))$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

## Example

```cpp
#include "ds/bst/rollback_ordered_multiset.hpp"

m1une::ds::RollbackOrderedMultiset<int> values;
values.insert(3, 2);
int state = values.snapshot();
values.erase_one(3);
values.rollback(state);
assert(values.count(3) == 2);
```
