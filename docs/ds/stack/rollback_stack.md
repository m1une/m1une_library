---
title: Rollback Stack
documentation_of: ../../../ds/stack/rollback_stack.hpp
---

## Overview

`RollbackStack<T>` is a mutable LIFO stack whose updates can be undone. It
shares nodes between saved states, so `snapshot()` is constant time and only
new persistent-stack nodes are retained in the history.

Every call to an update method advances history once. Snapshots are valid only
on the current history path; after rollback, discarded future states cannot be
restored.

## Methods

The constructors and read-only methods `size`, `empty`, `top`, and `node_count`
match `PersistentStack<T>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push(T value)` | Pushes `value` and advances history. | $O(1)$ |
| `template<class... Args> void emplace(Args&&... args)` | Constructs and pushes a value, then advances history. | $O(1)$ |
| `void pop()` | Removes the top and advances history. Requires a nonempty stack. | $O(1)$ |
| `void clear()` | Removes all values and advances history. | $O(1)$ |
| `int history_size() const`, `int snapshot() const` | Returns the current history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Restores the state before the latest update. | $O(F)$ |
| `void rollback(int state)` | Restores a snapshot on the current history path. | $O(F)$ total |
| `void clear_history()` | Forgets saved states without changing the stack. | $O(F)$ |
| `void release()` | Releases the stack and its saved states. | $O(F)$ |
| `const PersistentStack<T>& current_version() const` | Returns a read-only persistent handle to the current state. | $O(1)$ |

Here $H$ is the requested capacity and $F$ is the number of nodes whose final
reference is released.

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
