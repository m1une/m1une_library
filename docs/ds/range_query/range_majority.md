---
title: Range Majority
documentation_of: ../../../ds/range_query/range_majority.hpp
---

## Overview

`RangeMajority<T>` maintains a fixed-length array under point assignments
and finds the strict majority of any nonempty half-open range `[left, right)`.
A strict majority is a value occurring more than `(right - left) / 2` times. It
is necessarily unique. The query returns `std::nullopt` when no strict majority
exists.

Each segment-tree node stores the result of Boyer--Moore cancellation. A strict
majority survives every cancellation of two unequal values, so merging the
nodes covering a query produces the only possible candidate. An order-statistics
set of current positions for each value verifies the candidate's exact
frequency and supports point assignments.

The algorithm is deterministic.

## Requirements and Behavior

`T` must be copyable and provide a strict weak ordering through `operator<`.
Construction does not modify the input vector. `set` accepts values that were
not present during construction.

Let $D$ be the number of distinct values seen by the constructor and all calls
to `set`. The structure uses $O(N + D)$ memory. It retains bookkeeping for a
value after its final occurrence is replaced.

Queries use zero-based indices and require
`0 <= left < right <= size()`. Point assignments require
`0 <= index < size()` and mutate the structure. Both query methods are `const`.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `RangeMajority()` | Constructs an empty structure. | $O(1)$ |
| Constructor | `explicit RangeMajority(const std::vector<T>& values)` | Preprocesses `values`. | $O(N\log N)$ time |
| `size` | `int size() const` | Returns the array length. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the array is empty. | $O(1)$ |
| `set` | `void set(int index, T value)` | Assigns `value` to position `index`. | Amortized $O(\log N + \log D)$ |
| `query` | `std::optional<T> query(int left, int right) const` | Returns the strict majority of `[left, right)`, or `std::nullopt`. | $O(\log N)$ |
| `majority` | `std::optional<T> majority(int left, int right) const` | Alias of `query`. | $O(\log N)$ |

`result_type` is an alias of `std::optional<T>`.

## Example

```cpp
#include "ds/range_query/range_majority.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {2, 1, 2, 2, 3, 3};
    m1une::ds::RangeMajority<int> majority(values);

    auto first = majority.query(0, 4);
    if (first) std::cout << *first << '\n';  // 2

    majority.set(1, 3);
    auto second = majority.query(1, 6);
    if (second) std::cout << *second << '\n';  // 3
}
```
