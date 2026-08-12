---
title: Rollback Potentialized DSU
documentation_of: ../../../ds/dsu/rollback_potentialized_dsu.hpp
---

## Overview

`RollbackPotentializedDsu<Group>` is a weighted Union-Find with registered snapshots. It supports possibly noncommutative groups and uses union by size without path compression, so every tree has logarithmic depth.

For `merge(a, b, w)`, the stored constraint is
`diff(a, b) == w`, where
`diff(a, b) = Group::op(Group::inv(potential(a)), potential(b))`.
The group value type must be equality comparable so a constraint inside an
existing component can be checked.

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
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(M)$ for $M$ reverted successful merges |
| `void clear_history()` | Commits the current state and invalidates snapshots. | $O(H)$ |
| `std::vector<std::vector<int>> groups() const` | Materializes all components. | $O(N \log N)$ |

Indices must lie in `[0, size())`. A rollback token must be active.

## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

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
