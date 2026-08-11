---
title: Persistent Stack
documentation_of: ../../../ds/stack/persistent_stack.hpp
---

## Overview

`PersistentStack<T>` is a purely persistent LIFO stack. `push`, `emplace`,
`pop`, and `clear` return new versions while every source version remains
unchanged and can be branched again.

Nodes live in a recyclable pool shared by related versions. Each node stores
one value and the index of the previous top, so every operation except bulk
release has a deterministic $O(1)$ bound. Reference counting reclaims a node
after the last version or newer stack node that depends on it is released.

## Behavior

`top()` and `pop()` require a nonempty stack and assert otherwise. Update
methods are `const` and do not change the logical contents of their source
version.

References returned by `top()` remain valid while a live version depends on the
pointed-to node. `T` may be move-only.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `PersistentStack()` | Constructs an empty stack. | $O(1)$ |
| `size` | `int size() const` | Returns the number of elements. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the stack is empty. | $O(1)$ |
| `release` | `void release()` | Releases this version immediately and makes this handle empty. | $O(F)$ |
| `node_count` | `std::size_t node_count() const` | Returns live nodes in the shared version family. | $O(1)$ |
| `top` | `const T& top() const` | Returns the top element. Requires a nonempty stack. | $O(1)$ |
| `push` | `PersistentStack push(T value) const` | Returns a version with `value` on top. | $O(1)$ |
| `emplace` | `template <class... Args> PersistentStack emplace(Args&&... args) const` | Constructs a new top element in place and returns the new version. | $O(1)$ |
| `pop` | `PersistentStack pop() const` | Returns a version without its top element. | $O(1)$ |
| `clear` | `PersistentStack clear() const` | Returns an empty related version. | $O(1)$ |

Each `push` or `emplace` creates one node. Live memory is linear in the nodes
reachable from related versions, and reclaimed slots are reused. Here $F$ is
the number of nodes that become unreachable. Destruction and assignment release
versions automatically.

## Example

```cpp
#include "ds/stack/persistent_stack.hpp"

#include <iostream>

int main() {
    m1une::ds::PersistentStack<int> empty;
    auto one = empty.push(10);
    auto two = one.push(20);
    auto branch = one.push(30);

    std::cout << two.top() << '\n';          // 20
    std::cout << two.pop().top() << '\n';    // 10
    std::cout << branch.top() << '\n';       // 30
}
```
