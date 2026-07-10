---
title: Static Range Count Distinct
documentation_of: ../../../ds/range_query/static_range_count_distinct.hpp
---

## Overview

`StaticRangeCountDistinct<T>` counts the number of distinct values in any
half-open subarray `[left, right)` of a static array.

For every position, the structure records the previous position containing the
same value. A position is the first occurrence of its value inside a query
exactly when its previous occurrence is before `left`. These two-dimensional
counting queries are answered by a wavelet matrix.

## Requirements

`T` must support `<` as a strict weak ordering. Duplicate values and empty
ranges are supported. The input array is not modified.

## Complexity

| Operation | Time | Memory |
| --- | --- | --- |
| Construction | $O(N\log N)$ | $O(N\log N)$ bits |
| Query | $O(\log N)$ | $O(1)$ |

## Methods

| Method | Complexity | Description |
| --- | --- | --- |
| `StaticRangeCountDistinct()` | $O(1)$ | Constructs an empty structure. |
| `explicit StaticRangeCountDistinct(const std::vector<T>& values)` | $O(N\log N)$ | Builds the static structure. |
| `int query(int left, int right) const` | $O(\log N)$ | Counts distinct values in `[left, right)`. |
| `int count_distinct(int left, int right) const` | $O(\log N)$ | Alias of `query`. |
| `int size() const` | $O(1)$ | Returns the array size. |
| `bool empty() const` | $O(1)$ | Returns whether the array is empty. |

## Example

```cpp
#include "ds/range_query/static_range_count_distinct.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {1, 2, 1, 3, 2};
    m1une::ds::StaticRangeCountDistinct<int> distinct(values);

    std::cout << distinct.query(0, 5) << "\n"; // 3
    std::cout << distinct.query(1, 4) << "\n"; // 3
    std::cout << distinct.query(2, 2) << "\n"; // 0
}
```
