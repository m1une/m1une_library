---
title: Persistent Ordered Set
documentation_of: ../../../ds/bst/persistent_ordered_set.hpp
---

## Overview

`PersistentOrderedSet` is a path-copying red-black tree for sets. Updates,
splits, and merges return new versions and leave every input version available.

Its underlying tree uses a specialization-wide indexed, chunked node pool
rather than per-node pointers. The append-only pool is released when the program
exits.

Pointers returned by bound and predecessor/successor methods remain valid for
the remainder of the program.

## Template Parameters

* `T`: The key type.
* `Compare`: Ordering predicate. Defaults to `std::less<T>`.

Trees passed to `merge` must use equivalent comparator state.

## Constructors

* `PersistentOrderedSet()`
  Constructs an empty set. ($O(1)$)

* `PersistentOrderedSet(Compare compare)`
  Constructs an empty set with a custom comparator. ($O(1)$)

* `PersistentOrderedSet(std::initializer_list<T> init)`
  Constructs a set from an initializer list. Duplicate keys are ignored. ($O(N \log N)$)

* `PersistentOrderedSet(Iterator first, Iterator last)`
  Constructs a set from a range. Duplicate keys are ignored. ($O(N \log N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of keys. | $O(1)$ |
| `int unique_size() const` | Alias for `size()`. | $O(1)$ |
| `bool empty() const` | Returns whether the set is empty. | $O(1)$ |
| `PersistentOrderedSet clear() const` | Returns an empty set with the same comparator. | $O(1)$ |
| `PersistentOrderedSet insert(T key) const` | Returns a new set with `key` inserted; if `key` exists, returns an equivalent set. | $O(\log N)$ |
| `PersistentOrderedSet erase(const T& key) const` | Returns a new set with `key` removed if it exists. | $O(\log N)$ |
| `bool contains(const T& key) const` | Returns whether `key` exists. | $O(\log N)$ |
| `int count(const T& key) const` | Returns `1` if `key` exists, otherwise `0`. | $O(\log N)$ |
| `const T* find_by_order(int k) const` | Returns a pointer to the 0-indexed `k`-th smallest key. Requires `0 <= k < size()`. | $O(\log N)$ |
| `T kth(int k) const` | Returns the 0-indexed `k`-th smallest key by value. Requires `0 <= k < size()`. | $O(\log N)$ |
| `int order_of_key(const T& key) const` | Returns the number of keys strictly less than `key`. | $O(\log N)$ |
| `int count_less(const T& key) const` | Alias for `order_of_key(key)`. | $O(\log N)$ |
| `int count_less_equal(const T& key) const` | Returns the number of keys less than or equal to `key`. | $O(\log N)$ |
| `int count_greater(const T& key) const` | Returns the number of keys strictly greater than `key`. | $O(\log N)$ |
| `int count_greater_equal(const T& key) const` | Returns the number of keys greater than or equal to `key`. | $O(\log N)$ |
| `const T* lower_bound(const T& key) const`, `const T* min_ge(const T& key) const` | Returns the smallest key greater than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* upper_bound(const T& key) const`, `const T* min_gt(const T& key) const` | Returns the smallest key strictly greater than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_le(const T& key) const` | Returns the largest key less than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_lt(const T& key) const` | Returns the largest key strictly less than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* min() const`, `const T* max() const` | Returns the minimum or maximum key, or `nullptr` if the set is empty. | $O(1)$ |
| `std::pair<PersistentOrderedSet, PersistentOrderedSet> split(const T& key) const` | Returns `{less, greater_equal}` without changing this version. | $O(\log N)$ |
| `PersistentOrderedSet merge(const PersistentOrderedSet& other) const` | Returns the union without changing either version. Requires every key in `*this` to be smaller than every key in `other`. | $O(\log(N + M))$ |
| `std::vector<T> to_vector() const` | Returns all keys in sorted order. | $O(N)$ |

## Example

```cpp
#include "ds/bst/persistent_ordered_set.hpp"

#include <iostream>

int main() {
    m1une::ds::PersistentOrderedSet<int> a;
    auto b = a.insert(3).insert(1).insert(3);
    auto c = b.erase(3);
    auto [small, large] = b.split(3);
    auto joined = small.merge(large);

    std::cout << a.size() << "\n";  // 0
    std::cout << b.size() << "\n";  // 2
    std::cout << c.size() << "\n";  // 1
}
```
