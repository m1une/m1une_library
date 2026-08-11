---
title: Rollback Ordered Multiset
documentation_of: ../../../ds/bst/rollback_ordered_multiset.hpp
---

## Overview

`RollbackOrderedMultiset<T, Compare>` is an ordered multiset with order
statistics and linear-history rollback. It shares nodes between saved states.
`Compare` must define a strict weak ordering.

## Methods

Constructors and all read-only methods and `split` match
`PersistentOrderedMultiset<T, Compare>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the multiset. | $O(1)$ |
| `void insert(T key, int multiplicity = 1)`, `void insert_inplace(T key, int multiplicity = 1)` | Inserts positive multiplicity and advances history. | $O(\log N)$ |
| `bool erase_one(const T& key)`, `bool erase(const T& key)` | Erases one copy, reports whether one existed, and advances history. | $O(\log N)$ |
| `bool erase_one_inplace(const T& key)`, `bool erase_inplace(const T& key)` | Aliases of `erase_one`. | $O(\log N)$ |
| `int erase_all(const T& key)` | Erases every copy and returns the erased multiplicity. | $O(\log N)$ |
| `bool erase_all_inplace(const T& key)` | Erases every copy and reports whether the key existed. | $O(\log N)$ |
| `void merge(const RollbackOrderedMultiset& other)` | Appends an ordered multiset. | $O(\log N)$ |
| `void merge(const PersistentOrderedMultiset<T, Compare>& other)` | Persistent-handle overload. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentOrderedMultiset<T, Compare>& current_version() const` | Returns the current persistent state. | $O(1)$ |

Every attempted update advances history. $F$ counts nodes released.

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
