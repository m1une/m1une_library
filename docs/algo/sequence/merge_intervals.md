---
title: Merge Intervals
documentation_of: ../../../algo/sequence/merge_intervals.hpp
---

## Overview

Computes the union of half-open intervals. The result is sorted by left
endpoint, contains no empty intervals, and has a positive gap between every two
consecutive intervals. In particular, overlapping or touching intervals are
merged.

Every input interval must satisfy `left <= right`. Endpoints must be movable
and support a strict weak ordering through `operator<`; passing an lvalue vector
also requires them to be copyable.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<pair<T, T>> merge_intervals(vector<pair<T, T>> intervals)` | Returns the union of the half-open intervals `[left, right)`. The argument is copied when an lvalue is passed and can be consumed with `std::move`. | $O(N \log N)$ time and $O(1)$ auxiliary space |

## Notes

- Empty intervals `[x, x)` are discarded.
- Touching intervals such as `[1, 3)` and `[3, 5)` become `[1, 5)`.
- A reversed interval violates the function precondition and triggers an
  assertion in debug builds.
- The input vector is not modified unless the caller explicitly passes it with
  `std::move`.

## Example

```cpp
#include "algo/sequence/merge_intervals.hpp"

#include <utility>
#include <vector>

int main() {
    std::vector<std::pair<int, int>> intervals;
    intervals.emplace_back(5, 8);
    intervals.emplace_back(1, 3);
    intervals.emplace_back(3, 6);
    intervals.emplace_back(9, 9);

    auto merged = m1une::algo::merge_intervals(intervals);
    // merged contains [1, 8).
}
```
