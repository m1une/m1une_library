---
title: Persistent Deque
documentation_of: ../../../ds/deque/persistent_deque.hpp
---

## Overview

`PersistentDeque<T>` is a purely persistent double-ended queue. Every update
returns a new deque while the source version and all earlier branches remain
unchanged.

The implementation is Okasaki's real-time deque with balance factor two. It
keeps front and rear lazy streams balanced and evaluates a fixed number of
scheduled stream cells on every update. Rebalancing is incremental, so no
operation copies or traverses the whole deque.

Indexed access is intentionally not part of this endpoint deque API; adding a
general `operator[]` would not have the same worst-case constant bound.

Values live in a shared append-only pool and stream cells contain value indices.
A push therefore stores its `T` only once, and `T` may be move-only. The pool is
released when the last related deque version is destroyed.

## Behavior

`front()`, `back()`, `pop_front()`, and `pop_back()` require a nonempty deque and
assert otherwise. Update methods are `const` and never change the logical
contents of the source version.

Lazy stream cells are memoized internally when accessed. This physical
memoization is shared by related versions and does not change any version's
logical contents. References returned by `front()` and `back()` remain valid
while any related version keeps the shared pool alive.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `PersistentDeque()` | Constructs an empty deque. | Worst-case $O(1)$ |
| `size` | `int size() const` | Returns the number of elements. | Worst-case $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the deque is empty. | Worst-case $O(1)$ |
| `front` | `const T& front() const` | Returns the first element. | Worst-case $O(1)$ |
| `back` | `const T& back() const` | Returns the last element. | Worst-case $O(1)$ |
| `push_front` | `PersistentDeque push_front(T value) const` | Returns a version with `value` prepended. | Worst-case $O(1)$ |
| `emplace_front` | `template <class... Args> PersistentDeque emplace_front(Args&&... args) const` | Constructs and prepends a value. | Worst-case $O(1)$ |
| `push_back` | `PersistentDeque push_back(T value) const` | Returns a version with `value` appended. | Worst-case $O(1)$ |
| `emplace_back` | `template <class... Args> PersistentDeque emplace_back(Args&&... args) const` | Constructs and appends a value. | Worst-case $O(1)$ |
| `pop_front` | `PersistentDeque pop_front() const` | Returns a version without its first element. | Worst-case $O(1)$ |
| `pop_back` | `PersistentDeque pop_back() const` | Returns a version without its last element. | Worst-case $O(1)$ |
| `clear` | `PersistentDeque clear() const` | Returns an empty related version. | Worst-case $O(1)$ |

Each push stores one `T`. Every operation creates and evaluates only $O(1)$
stream cells, so memory usage is $O(1)$ per update across all branches.

## Example

```cpp
#include "ds/deque/persistent_deque.hpp"

#include <iostream>

int main() {
    m1une::ds::PersistentDeque<int> empty;
    auto middle = empty.push_back(20);
    auto both = middle.push_front(10).push_back(30);
    auto branch = middle.push_front(5);

    std::cout << both.front() << ' ' << both.back() << '\n';  // 10 30
    std::cout << both.pop_front().front() << '\n';             // 20
    std::cout << branch.front() << ' ' << branch.back() << '\n';  // 5 20
}
```
