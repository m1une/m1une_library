---
title: Rollback Dynamic Lazy Monoid Array
documentation_of: ../../../ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp
---

## Overview

`RollbackDynamicLazyMonoidArray<ActedMonoid>` is a rollback implicit treap with
range actions and range products. `ActedMonoid` must satisfy
`m1une::acted_monoid::IsActedMonoid`. Saved states preserve lazy and reversal
tags without mutating earlier history.

## Methods

Constructors and read-only methods (`size`, `empty`, `get`, element access,
`prod`, `all_prod`, `to_vector`, persistent splits, and `node_count`) match
`PersistentDynamicLazyMonoidArray<ActedMonoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the sequence. | $O(1)$ |
| `void insert(...)`, `void push_back(T value)`, `void push_front(T value)`, `void append(...)` | Inserts values. | Expected $O(\log N)$ for one/shared input; $O(M + \log N)$ for a vector or independent input |
| `void erase(int pos)`, `void erase(int left, int right)`, `void pop_back()`, `void pop_front()` | Erases values. | Expected $O(\log N)$ |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Replaces one value. | Expected $O(\log N)$ |
| `void apply(int pos, const F& f)`, `void apply(int left, int right, const F& f)` | Applies an action to one value or `[left, right)`. | Expected $O(\log N)$ |
| `void apply_inplace(...)` | Aliases of the rollback-recording `apply` overloads. | Expected $O(\log N)$ |
| `void reverse(int left, int right)`, `void reverse()` | Reverses a range or the whole sequence. | Expected $O(\log N)$; whole range is $O(1)$ |
| `void rotate(int left, int middle, int right)` | Rotates a range. | Expected $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |
| `const PersistentDynamicLazyMonoidArray<ActedMonoid>& current_version() const` | Returns the current persistent state. | $O(1)$ |

Every update call advances history once. $F$ counts nodes released.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp"

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
m1une::ds::RollbackDynamicLazyMonoidArray<AM> a({1, 2, 3});
int state = a.snapshot();
a.apply(0, 2, 5);
a.rollback(state);
assert(a.all_prod().sum == 6);
```
