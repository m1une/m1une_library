---
title: Predecessor Set
documentation_of: ../../../ds/bst/predecessor_set.hpp
---

## Overview

`PredecessorSet` maintains a set of integers in a fixed universe `[0, U)`.
Besides insertion, erasure, and membership tests, it finds the closest stored
key on either side of a query key.

The structure stores the universe in 64-bit words and recursively records which
words are nonempty. A search skips empty groups one level at a time, giving
small constants and deterministic worst-case bounds. It is most useful when the
universe is dense enough that a tree node per stored key would be wasteful.

## Behavior

Keys passed to membership, update, predecessor, and successor methods must
satisfy `0 <= key < universe_size()`. Invalid keys trigger an assertion.

Every predecessor or successor method returns `-1` when no matching key exists.
The string constructor expects one character per universe key: key `i` is
initially present exactly when `membership[i]` is `'1'`.

The structure uses $O(U / 64)$ machine words. Its query and update bounds are
$O(\log_{64} U)$, which is at most four levels for common contest constraints.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `PredecessorSet()` | Constructs a set with an empty universe. | $O(1)$ |
| Constructor | `explicit PredecessorSet(int universe_size)` | Constructs an empty set over `[0, universe_size)`. | $O(U / 64)$ |
| Constructor | `explicit PredecessorSet(std::string_view membership)` | Constructs the set from a binary membership string. | $O(U)$ |
| `universe_size` | `int universe_size() const` | Returns `U`. | $O(1)$ |
| `size` | `int size() const` | Returns the number of stored keys. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the set has no keys. | $O(1)$ |
| `contains` | `bool contains(int key) const` | Returns whether `key` is stored. | $O(1)$ |
| `insert` | `bool insert(int key)` | Inserts `key` and returns whether the set changed. | $O(\log_{64} U)$ |
| `erase` | `bool erase(int key)` | Erases `key` and returns whether the set changed. | $O(\log_{64} U)$ |
| `successor`, `min_ge` | `int successor(int key) const`, `int min_ge(int key) const` | Returns the smallest stored key greater than or equal to `key`, or `-1`. | $O(\log_{64} U)$ |
| `min_gt` | `int min_gt(int key) const` | Returns the smallest stored key strictly greater than `key`, or `-1`. | $O(\log_{64} U)$ |
| `predecessor`, `max_le` | `int predecessor(int key) const`, `int max_le(int key) const` | Returns the largest stored key less than or equal to `key`, or `-1`. | $O(\log_{64} U)$ |
| `max_lt` | `int max_lt(int key) const` | Returns the largest stored key strictly less than `key`, or `-1`. | $O(\log_{64} U)$ |
| `min` | `int min() const` | Returns the minimum stored key, or `-1`. | $O(\log_{64} U)$ |
| `max` | `int max() const` | Returns the maximum stored key, or `-1`. | $O(\log_{64} U)$ |

## Example

```cpp
#include "ds/bst/predecessor_set.hpp"

#include <iostream>

int main() {
    m1une::ds::PredecessorSet set(10);
    set.insert(2);
    set.insert(7);

    std::cout << set.predecessor(5) << '\n';  // 2
    std::cout << set.successor(5) << '\n';    // 7

    set.erase(2);
    std::cout << set.max_le(5) << '\n';       // -1
}
```
