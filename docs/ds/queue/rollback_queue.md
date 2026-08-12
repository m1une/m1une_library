---
title: Rollback Queue
documentation_of: ../../../ds/queue/rollback_queue.hpp
---

## Overview

`RollbackQueue<T>` is a mutable real-time FIFO queue with registered snapshots and rollback
support. Rollback values are retained only while snapshots are active.

## Methods

Constructors and read-only methods follow ordinary FIFO queue semantics.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push(T value)`, `void push_back(T value)` | Adds a value at the back. | $O(1)$ worst case |
| `void pop()`, `void pop_front()` | Removes the front. Requires a nonempty queue. | $O(1)$ worst case |
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
#include "ds/queue/rollback_queue.hpp"

m1une::ds::RollbackQueue<int> queue;
queue.push(1);
int state = queue.snapshot();
queue.push(2);
queue.pop();
queue.rollback(state);
assert(queue.front() == 1);
```
