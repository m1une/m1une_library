---
title: Rollback Queue
documentation_of: ../../../ds/queue/rollback_queue.hpp
---

## Overview

`RollbackQueue<T>` is a mutable real-time FIFO queue with undo and snapshot
support. Saved states share the nodes of `PersistentQueue<T>`. Every update,
including an update that leaves an equivalent value, advances history once.

## Methods

Constructors and the read-only methods `size`, `empty`, `front`, `back`, and
`node_count` match `PersistentQueue<T>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push(T value)`, `void push_back(T value)` | Adds a value at the back. | $O(1)$ worst case |
| `void pop()`, `void pop_front()` | Removes the front. Requires a nonempty queue. | $O(1)$ worst case |
| `void clear()` | Removes all values. | $O(1)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()` | Forgets saved states. | $O(F)$ |
| `void release()` | Releases current and saved states. | $O(F)$ |
| `const PersistentQueue<T>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$F$ counts nodes whose final reference is released.

## Example

```cpp
#include "ds/queue/rollback_queue.hpp"

m1une::ds::RollbackQueue<int> queue;
queue.push(1);
int state = queue.snapshot();
queue.push(2);
queue.pop();
queue.rollback(state);
assert(queue.front() == 1);
```
