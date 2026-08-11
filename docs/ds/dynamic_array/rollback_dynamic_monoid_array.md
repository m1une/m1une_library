---
title: Rollback Dynamic Monoid Array
documentation_of: ../../../ds/dynamic_array/rollback_dynamic_monoid_array.hpp
---

## Overview

`RollbackDynamicMonoidArray<Monoid>` adds monoid range products to a rollback
implicit-treap sequence. `Monoid` must satisfy `m1une::monoid::IsMonoid`.

## Methods

Constructors and read-only methods (`size`, `empty`, `get`, element access,
`prod`, `all_prod`, `to_vector`, persistent splits, and `node_count`) match
`PersistentDynamicMonoidArray<Monoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the sequence. | $O(1)$ |
| `void insert(...)`, `void push_back(T value)`, `void push_front(T value)`, `void append(...)` | Inserts values and advances history. | Expected $O(\log N)$ for one/shared input; $O(M + \log N)$ for a vector or independent input |
| `void erase(int pos)`, `void erase(int left, int right)`, `void pop_back()`, `void pop_front()` | Erases values. | Expected $O(\log N)$ |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Replaces one value. | Expected $O(\log N)$ |
| `void reverse(int left, int right)`, `void reverse()` | Reverses a range or the entire sequence. | Expected $O(\log N)$; whole range is $O(1)$ |
| `void rotate(int left, int middle, int right)` | Rotates a range. | Expected $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentDynamicMonoidArray<Monoid>& current_version() const` | Returns the current persistent state. | $O(1)$ |

All overloads are the mutable-return counterparts of the persistent structure:
vector, initializer-list, rollback-array, and persistent-array insertion are
supported. Each call advances history once. $F$ counts nodes released.

## Example

```cpp
#include "ds/dynamic_array/rollback_dynamic_monoid_array.hpp"
#include "monoid/add.hpp"

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackDynamicMonoidArray<Add> a({1, 2, 3});
int state = a.snapshot();
a.set(1, 8);
a.rollback(state);
assert(a.all_prod() == 6);
```
