---
title: Rollback Deque
documentation_of: ../../../ds/deque/rollback_deque.hpp
---

## Overview

`RollbackDeque<T>` is a mutable real-time double-ended queue with undo and
snapshot support. It retains shared states of `PersistentDeque<T>`. Each update
advances history exactly once.

## Methods

Constructors and the read-only methods `size`, `empty`, `front`, `back`, and
`node_count` match `PersistentDeque<T>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push_front(T value)`, `void push_back(T value)` | Pushes at one end. | $O(1)$ worst case |
| `template<class... Args> void emplace_front(Args&&... args)`, `template<class... Args> void emplace_back(Args&&... args)` | Constructs a value at one end. | $O(1)$ worst case |
| `void pop_front()`, `void pop_back()` | Pops one end. Requires a nonempty deque. | $O(1)$ worst case |
| `void clear()` | Removes all values. | $O(1)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()` | Forgets saved states. | $O(F)$ |
| `void release()` | Releases current and saved states. | $O(F)$ |
| `const PersistentDeque<T>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$F$ counts nodes and delayed stream cells whose final reference is released.

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
