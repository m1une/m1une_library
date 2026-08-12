---
title: Rollback Stack
documentation_of: ../../../ds/stack/rollback_stack.hpp
---

## Overview

`RollbackStack<T>` is a mutable LIFO stack that supports registered snapshots and rollback. It
shares nodes between saved states, so `snapshot()` is constant time and only
rollback values are retained only after the first active snapshot.

on the current history path; after rollback, discarded future states cannot be
restored.

## Methods

The constructors and read-only methods `size`, `empty`, `top`, and `node_count`
follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push(T value)` | Pushes `value`. | $O(1)$ |
| `template<class... Args> void emplace(Args&&... args)` | Constructs and pushes a value. | $O(1)$ |
| `void pop()` | Removes the top. Requires a nonempty stack. | $O(1)$ |
| `void clear()` | Removes all values. | $O(N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a snapshot on the current history path. | $O(F)$ total |
| `void clear_history()` | Forgets saved states without changing the stack. | $O(F)$ |
| `void release()` | Releases the stack and its saved states. | $O(F)$ |

Here $H$ is the requested capacity and $F$ is the number of nodes whose final
reference is released.

## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

## Example

```cpp
#include "ds/stack/rollback_stack.hpp"

m1une::ds::RollbackStack<int> stack;
stack.push(1);
int state = stack.snapshot();
stack.push(2);
stack.rollback(state);
assert(stack.top() == 1);
```
