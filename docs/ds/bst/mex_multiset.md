---
title: Mex Multiset
documentation_of: ../../../ds/bst/mex_multiset.hpp
---

## Overview

`MexMultiset` maintains multiplicities of integers in a fixed universe `[0, U)`
and answers mex queries in constant time. It stores counts and uses a
[`PredecessorSet`](predecessor_set.md) to find the first missing value after
updates, with deterministic bounds and $O(U)$ space.

## Behavior

The returned answer is the smallest missing integer in `[0, U)`, or `U` if all
tracked values are present. It equals the actual mex whenever the actual mex is
at most `U`. In particular, choosing `U` at least the maximum number of elements
in the maintained collection always suffices. There is no automatic resizing.

Negative values and values at least `U` are ignored: insertion has no effect,
`erase` returns `false`, and `count` returns `0`. They are not stored. Repeated
insertions increment multiplicity; erasure removes one occurrence. The mex can
decrease only when the last occurrence of a tracked value is removed.

The vector constructor chooses `U = values.size()`. `T` must be a standard
integral type, signed or unsigned, and the vector length must fit in `int`.
The integer constructor asserts `U >= 0`. Each tracked multiplicity must fit
in `int`; insertion asserts before overflowing it. Updates mutate the object;
const queries do not mutate it.

## Interface

Let $L = 1 + \lceil\log_{64}(U + 1)\rceil$.

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `MexMultiset()` | Constructs an empty universe (`U = 0`). | $O(1)$ |
| Constructor | `explicit MexMultiset(int universe_size)` | Constructs an empty multiset over `[0, U)`. | $O(U + 1)$ |
| Constructor | `template <class T> explicit MexMultiset(const std::vector<T>& values)` | Constructs from `values`, with `U = values.size()`. | $O(U + 1)$ |
| `universe_size` | `int universe_size() const` | Returns `U`. | $O(1)$ |
| `count` | `int count(long long value) const` | Returns the tracked multiplicity, or `0` outside `[0, U)`. | $O(1)$ |
| `insert` | `void insert(long long value)` | Adds one occurrence, or ignores an untracked value. | $O(L)$ worst case; $O(1)$ for duplicates or untracked values |
| `erase` | `bool erase(long long value)` | Removes one occurrence and returns whether removal succeeded. | $O(L)$ worst case; $O(1)$ unless the last occurrence is removed |
| `mex` | `int mex() const` | Returns the smallest missing value, capped at `U`. | $O(1)$ |

## Example

```cpp
#include "ds/bst/mex_multiset.hpp"

#include <iostream>

int main() {
    m1une::ds::MexMultiset values(5);
    values.insert(0);
    values.insert(1);
    values.insert(1);
    values.insert(3);
    std::cout << values.mex() << '\n';  // 2

    values.erase(1);
    std::cout << values.mex() << '\n';  // 2: one copy of 1 remains
    values.erase(1);
    std::cout << values.mex() << '\n';  // 1
    values.insert(1);
    values.insert(2);
    std::cout << values.mex() << '\n';  // 4
}
```
