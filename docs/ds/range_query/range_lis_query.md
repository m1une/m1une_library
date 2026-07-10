---
title: Static Range LIS Query
documentation_of: ../../../ds/range_query/range_lis_query.hpp
---

## Overview

`RangeLisQuery<T>` preprocesses a static array and returns the length of its
strict longest increasing subsequence in any subarray `[left, right)`.
Equal values cannot both appear in the increasing subsequence.

The implementation converts the array to an equivalent permutation and builds
its semi-local LIS (seaweed) matrix. A wavelet matrix then counts the seaweeds
crossing each query rectangle.

## Requirements

`T` must support `<` as a strict weak ordering. The array is static after
construction. Duplicate values are supported.

## Complexity

| Operation | Time | Memory |
| --- | --- | --- |
| Construction | $O(N\log^2 N)$ | $O(N\log N)$ |
| Query | $O(\log N)$ | $O(1)$ |

## Methods

| Method | Complexity | Description |
| --- | --- | --- |
| `RangeLisQuery()` | $O(1)$ | Constructs an empty structure. |
| `explicit RangeLisQuery(const std::vector<T>& values)` | $O(N\log^2 N)$ | Builds the structure for `values`. |
| `int query(int left, int right) const` | $O(\log N)$ | Returns the strict LIS length in `[left, right)`. |
| `int lis_length(int left, int right) const` | $O(\log N)$ | Alias of `query`. |
| `int size() const` | $O(1)$ | Returns the array size. |
| `bool empty() const` | $O(1)$ | Returns whether the array is empty. |

## Example

```cpp
#include "ds/range_query/range_lis_query.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {3, 1, 2, 2, 4};
    m1une::ds::RangeLisQuery<int> lis(values);

    std::cout << lis.query(0, 5) << "\n"; // 3: 1, 2, 4
    std::cout << lis.query(1, 4) << "\n"; // 2: 1, 2
}
```
