---
title: Rollback Dynamic Array
documentation_of: ../../../ds/dynamic_array/rollback_dynamic_array.hpp
---

## Overview

`RollbackDynamicArray<T>` is a mutable implicit-treap sequence with insertion, erasure, assignment, reversal, rotation, and registered snapshots.

## Methods

Its constructors and read-only methods follow `DynamicArray<T>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the sequence. | $O(N)$ |
| `void insert(int pos, T value)` | Inserts one value. | Expected $O(\log N)$ |
| `void insert(int pos, const std::vector<T>& values)`, `void insert(int pos, std::vector<T>&& values)`, `void insert(int pos, std::initializer_list<T> values)` | Inserts $M$ values. | Expected $O(M + \log N)$ |
| `void insert(int pos, const RollbackDynamicArray& other)`, `void insert(int pos, const DynamicArray<T>& other)` | Inserts another sequence. | Expected $O(M + \log N)$ |
| `void push_back(T value)`, `void push_front(T value)` | Inserts at one end. | Expected $O(\log N)$ |
| `void append(...)` | Appends a vector, rollback array, or ordinary array. | Same as `insert` |
| `void erase(int pos)`, `void erase(int left, int right)` | Erases one value or `[left, right)`. | Expected $O(\log N)$ |
| `void pop_back()`, `void pop_front()` | Erases one end. | Expected $O(\log N)$ |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Replaces one value. | Expected $O(\log N)$ |
| `void reverse(int left, int right)` | Reverses `[left, right)`. | Expected $O(\log N)$ |
| `void reverse()` | Reverses the entire sequence. | $O(1)$ |
| `void rotate(int left, int middle, int right)` | Applies `std::rotate` semantics to the range. | Expected $O(\log N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

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
