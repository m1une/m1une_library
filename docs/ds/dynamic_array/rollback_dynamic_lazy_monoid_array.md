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

Constructors and read-only methods follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the sequence and recycles its nodes. | $O(N)$ |
| `void insert(...)`, `void push_back(T value)`, `void push_front(T value)`, `void append(...)` | Inserts values. | Expected $O(\log N)$ for one/shared input; $O(M + \log N)$ for a vector or independent input |
| `void erase(int pos)`, `void erase(int left, int right)`, `void pop_back()`, `void pop_front()` | Erases values. | Expected $O(\log N)$ |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Replaces one value. | Expected $O(\log N)$ |
| `void apply(int pos, const F& f)`, `void apply(int left, int right, const F& f)` | Applies an action to one value or `[left, right)`. | Expected $O(\log N)$ |
| `void apply_inplace(...)` | Aliases of the `apply` overloads. | Expected $O(\log N)$ |
| `void reverse(int left, int right)`, `void reverse()` | Reverses a range or the whole sequence. | Expected $O(\log N)$; whole range is $O(1)$ |
| `void rotate(int left, int middle, int right)` | Rotates a range. | Expected $O(\log N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, a treap node is saved only before its first mutation; newly allocated nodes are truncated directly by rollback.

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
