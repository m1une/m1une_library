---
title: Static Range Majority
documentation_of: ../../../ds/range_query/static_range_majority.hpp
---

## Overview

`StaticRangeMajority<T>` preprocesses an immutable array and finds the strict
majority of any nonempty half-open range `[left, right)`. A strict majority is a
value occurring more than `(right - left) / 2` times. It is necessarily unique.
The query returns `std::nullopt` when no strict majority exists.

Each segment-tree node stores the result of Boyer--Moore cancellation. A strict
majority survives every cancellation of two unequal values, so merging the
nodes covering a query produces the only possible candidate. Sorted occurrence
positions then verify the candidate's exact frequency.

The algorithm is deterministic.

## Requirements and Behavior

`T` must be copyable and support `operator<` and equality comparison
consistently. Construction does not modify the input vector.

Queries use zero-based indices and require
`0 <= left < right <= size()`. They do not mutate the structure, and both query
methods are `const`.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `StaticRangeMajority()` | Constructs an empty structure. | $O(1)$ |
| Constructor | `explicit StaticRangeMajority(const std::vector<T>& values)` | Preprocesses `values`. | $O(N\log N)$ time and $O(N)$ memory |
| `size` | `int size() const` | Returns the array length. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the array is empty. | $O(1)$ |
| `query` | `std::optional<T> query(int left, int right) const` | Returns the strict majority of `[left, right)`, or `std::nullopt`. | $O(\log N)$ |
| `majority` | `std::optional<T> majority(int left, int right) const` | Alias of `query`. | $O(\log N)$ |

`result_type` is an alias of `std::optional<T>`.

## Example

```cpp
#include "ds/range_query/static_range_majority.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {2, 1, 2, 2, 3, 3};
    m1une::ds::StaticRangeMajority<int> majority(values);

    auto first = majority.query(0, 4);
    if (first) std::cout << *first << '\n';  // 2

    auto second = majority.query(1, 6);
    std::cout << second.has_value() << '\n'; // 0
}
```
