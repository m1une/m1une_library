---
title: Rollback Deque
documentation_of: ../../../ds/deque/rollback_deque.hpp
---

## Overview

`RollbackDeque<T>` is a mutable real-time double-ended queue with
registered-snapshot rollback. Rollback values are retained only while snapshots are active.

## Methods

Constructors and read-only methods follow ordinary double-ended queue semantics.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push_front(T value)`, `void push_back(T value)` | Pushes at one end. | $O(1)$ worst case |
| `template<class... Args> void emplace_front(Args&&... args)`, `template<class... Args> void emplace_back(Args&&... args)` | Constructs a value at one end. | $O(1)$ worst case |
| `void pop_front()`, `void pop_back()` | Pops one end. Requires a nonempty deque. | $O(1)$ worst case |
| `void clear()` | Removes all values. | $O(N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()` | Forgets saved states. | $O(F)$ |
| `void release()` | Releases current and saved states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

## Example

```cpp
#include "ds/deque/rollback_deque.hpp"

m1une::ds::RollbackDeque<int> deque;
deque.push_back(2);
int state = deque.snapshot();
deque.push_front(1);
deque.rollback(state);
assert(deque.front() == 2);
```
