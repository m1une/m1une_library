---
title: Rollback Potentialized DSU
documentation_of: ../../../ds/dsu/rollback_potentialized_dsu.hpp
---

## Overview

`RollbackPotentializedDsu<Group>` is a weighted Union-Find that can undo merge
constraints. It supports possibly noncommutative groups and uses union by size
without path compression, so every tree has logarithmic depth and undo is
constant time.

For `merge(a, b, w)`, the stored constraint is
`diff(a, b) == w`, where
`diff(a, b) = Group::op(Group::inv(potential(a)), potential(b))`.
The group value type must be equality comparable so a constraint inside an
existing component can be checked.

Every merge call adds one history entry, including a redundant or contradictory
constraint. Thus one `undo()` always corresponds to one `merge()` call.
Snapshots are valid only on the current history path.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `RollbackPotentializedDsu()` | Constructs an empty DSU. | $O(1)$ |
| `explicit RollbackPotentializedDsu(int n)` | Constructs `n` singleton components. | $O(N)$ |
| `int size() const`, `bool empty() const` | Returns the element count or whether it is zero. | $O(1)$ |
| `int component_count() const` | Returns the current component count. | $O(1)$ |
| `int leader(int vertex) const` | Returns the component representative. | $O(\log N)$ |
| `bool same(int first, int second) const` | Tests connectivity. | $O(\log N)$ |
| `int group_size(int vertex) const`, `int size(int vertex) const` | Returns the component size. | $O(\log N)$ |
| `T potential(int vertex) const` | Returns the root-relative potential. | $O(\log N)$ |
| `T diff(int first, int second) const` | Returns the potential difference; requires connectivity. | $O(\log N)$ |
| `int parent_or_size(int vertex) const` | Returns the internal parent-or-negative-size entry. | $O(1)$ |
| `bool merge(int first, int second, const T& difference)` | Adds `diff(first, second) == difference`; returns whether the constraints are consistent. | $O(\log N)$ |
| `int history_size() const`, `int snapshot() const` | Returns the current history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves merge history. | $O(H)$ |
| `bool undo()` | Undoes the latest merge call. | $O(1)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(H - state)$ |
| `std::vector<std::vector<int>> groups() const` | Materializes all components. | $O(N \log N)$ |

Indices must lie in `[0, size())`; rollback states must lie in
`[0, history_size()]`.

## Example

```cpp
#include "ds/dsu/rollback_potentialized_dsu.hpp"
#include "monoid/add.hpp"

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackPotentializedDsu<Add> dsu(3);
dsu.merge(0, 1, 3);
int state = dsu.snapshot();
dsu.merge(1, 2, 4);
assert(dsu.diff(0, 2) == 7);
dsu.rollback(state);
assert(!dsu.same(0, 2));
```
