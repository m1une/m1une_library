---
title: Persistent Queue
documentation_of: ../../../ds/queue/persistent_queue.hpp
---

## Overview

`PersistentQueue<T>` is a purely persistent FIFO queue. Every update returns a
new queue while the original version and every earlier branch remain unchanged.

The implementation uses the Hood--Melville real-time rotation schedule. Each
update performs at most a constant amount of pending list rotation, including
when versions branch, so operations have deterministic worst-case bounds rather
than only amortized bounds.

Values are stored once in a shared append-only pool. Rotation links refer to
values by index, so `T` may be move-only. The pool is released when the last
related queue version is destroyed.

## Behavior

`front()`, `back()`, `pop()`, and `pop_front()` require a nonempty queue and
assert otherwise. Update methods are `const` and never change the logical
contents of the source version.

References returned by `front()` and `back()` remain valid while any related
version keeps the shared pool alive.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `PersistentQueue()` | Constructs an empty queue. | $O(1)$ |
| `size` | `int size() const` | Returns the number of elements. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the queue is empty. | $O(1)$ |
| `front` | `const T& front() const` | Returns the first element. Requires a nonempty queue. | $O(1)$ |
| `back` | `const T& back() const` | Returns the last element. Requires a nonempty queue. | $O(1)$ |
| `push` | `PersistentQueue push(T value) const` | Returns a version with `value` appended. | Worst-case $O(1)$ |
| `push_back` | `PersistentQueue push_back(T value) const` | Alias of `push`. | Worst-case $O(1)$ |
| `pop` | `PersistentQueue pop() const` | Returns a version without its first element. | Worst-case $O(1)$ |
| `pop_front` | `PersistentQueue pop_front() const` | Alias of `pop`. | Worst-case $O(1)$ |
| `clear` | `PersistentQueue clear() const` | Returns an empty related version. | $O(1)$ |

Each push stores one `T` and creates $O(1)$ small link nodes. Rotation work also
creates $O(1)$ links per update, so total memory is linear in the number of
updates across all related versions.

## Example

```cpp
#include "ds/queue/persistent_queue.hpp"

#include <iostream>

int main() {
    m1une::ds::PersistentQueue<int> empty;
    auto one = empty.push(10);
    auto two = one.push(20);
    auto branch = one.push(30);

    std::cout << two.front() << ' ' << two.back() << '\n';  // 10 20
    std::cout << two.pop().front() << '\n';                 // 20
    std::cout << branch.pop().front() << '\n';              // 30
}
```
