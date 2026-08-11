---
title: Rollback Dynamic Array
documentation_of: ../../../ds/dynamic_array/rollback_dynamic_array.hpp
---

## Overview

`RollbackDynamicArray<T>` is a mutable implicit-treap sequence with linear
history. Saved states share persistent nodes; insertions, erasures, assignments,
reversals, and rotations can be undone.

## Methods

Its constructors and read-only methods (`size`, `empty`, element access,
`to_vector`, `split`, `split_off`, and `node_count`) match
`PersistentDynamicArray<T>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the sequence and advances history. | $O(1)$ |
| `void insert(int pos, T value)` | Inserts one value. | Expected $O(\log N)$ |
| `void insert(int pos, const std::vector<T>& values)`, `void insert(int pos, std::vector<T>&& values)`, `void insert(int pos, std::initializer_list<T> values)` | Inserts $M$ values. | Expected $O(M + \log N)$ |
| `void insert(int pos, const RollbackDynamicArray& other)`, `void insert(int pos, const PersistentDynamicArray<T>& other)` | Inserts another sequence. | Expected $O(\log N)$ with a shared pool; $O(M + \log N)$ otherwise |
| `void push_back(T value)`, `void push_front(T value)` | Inserts at one end. | Expected $O(\log N)$ |
| `void append(...)` | Appends a vector, rollback array, or persistent array. | Same as `insert` |
| `void erase(int pos)`, `void erase(int left, int right)` | Erases one value or `[left, right)`. | Expected $O(\log N)$ |
| `void pop_back()`, `void pop_front()` | Erases one end. | Expected $O(\log N)$ |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Replaces one value. | Expected $O(\log N)$ |
| `void reverse(int left, int right)` | Reverses `[left, right)`. | Expected $O(\log N)$ |
| `void reverse()` | Reverses the entire sequence. | $O(1)$ |
| `void rotate(int left, int middle, int right)` | Applies `std::rotate` semantics to the range. | Expected $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentDynamicArray<T>& current_version() const` | Returns the current persistent state. | $O(1)$ |

Each update call advances history once, including empty-range updates. $F$
counts nodes whose final reference is released.

## Example

```cpp
#include "ds/dynamic_array/rollback_dynamic_array.hpp"

m1une::ds::RollbackDynamicArray<int> a({1, 2, 3});
int state = a.snapshot();
a.insert(1, 7);
a.reverse();
a.rollback(state);
assert(a.to_vector() == std::vector<int>({1, 2, 3}));
```
