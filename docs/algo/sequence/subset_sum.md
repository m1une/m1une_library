---
title: Meet-in-the-Middle Subset Sum
documentation_of: ../../../algo/sequence/subset_sum.hpp
---

## Overview

Finds the maximum sum of a subset that does not exceed a given limit. The
array is split in half, the subset sums of both halves are generated in sorted
order, and a two-pointer scan finds the best compatible pair.

The sorted half-sum lists are also exposed for other meet-in-the-middle
algorithms. Every subset sum of the original array can be written as
`left_sums[i] + right_sums[j]`.

## Template Parameters

* `T`: Value and sum type. `T{}` must be the additive identity. Values must
  support `operator+` and `operator<`, and addition by a fixed value must
  preserve ordering. Every subset sum must be representable by `T`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `std::pair<std::vector<T>, std::vector<T>> enumerate_half_subset_sums(const std::vector<T>& values)` | Returns the sorted subset sums of `values[0, N / 2)` and `values[N / 2, N)`. | $O(2^{N/2})$ time and space |
| `T maximum_subset_sum(const std::vector<T>& values, const T& limit)` | Returns the maximum subset sum not exceeding `limit`. Requires `T{} <= limit`. | $O(2^{N/2})$ time and space |

## Behavior

Each half-sum vector is sorted in ascending order, includes the empty-subset
sum `T{}`, and preserves equal sums produced by different subsets. The input
is not modified.

`maximum_subset_sum` includes the empty subset as a candidate, so it returns
`T{}` when no positive subset sum fits. `limit` must not be less than `T{}`.

Materializing all $2^N$ full-array subset sums would require $O(2^N)$ output.
Keeping the halves separate uses only $O(2^{N/2})$ time and memory.

## Example

```cpp
#include "algo/sequence/subset_sum.hpp"
#include <iostream>
#include <vector>

int main() {
    const std::vector<long long> values = {2, 3, 5, 7, 11};
    const long long limit = 17;

    std::cout << m1une::algo::maximum_subset_sum(values, limit) << '\n';

    const auto [left_sums, right_sums] =
        m1une::algo::enumerate_half_subset_sums(values);
}
```
