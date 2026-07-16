---
title: Wavelet Matrix with Sums
documentation_of: ../../../ds/wavelet_matrix/wavelet_matrix_sum.hpp
---

## Overview

`m1une::ds::WaveletMatrixSum` is a static wavelet matrix that stores an
additive weight for every value. It supports range order statistics together
with:

* total weight in an index range,
* total weight for values below a bound or inside a value interval, and
* total weight of the smallest or largest `k` values.

By default, each value is also its weight, producing ordinary sums of selected
values. A separate weight vector can instead represent costs, counts, or other
additive data.

Signed values are ordered across their full type range by an internal sign-bit
transform. No coordinate compression is required.

Levels are packed and stable-partitioned one machine word at a time, avoiding
an unpredictable branch for every value. AVX2 bit extraction and BMI2 rank
masking are selected when the corresponding instruction sets are enabled at
compile time, with compact scalar fallbacks otherwise.

## Template Parameters

* `T`: A non-`bool` integral value type used for ordering.
* `Sum`: The weight and sum type. It defaults to `T`.

`Sum{}` must be the additive identity, and `Sum` must support addition and
subtraction. Choose a sufficiently wide type because arithmetic overflow is not
checked.

Let $B$ be the bit width of `T`. Let $L$ be the bit width of the exclusive-or
of the minimum and maximum internally encoded values. Leading bits shared by
all values are omitted, so $0 \le L \le B$ and equal values have $L = 0$.

## Construction

* `WaveletMatrixSum()`: creates an empty matrix.
* `WaveletMatrixSum(const vector<T>& values)`: uses each value as its own
  weight. This requires `T` to be convertible to `Sum`.
* `WaveletMatrixSum(const vector<T>& values, const vector<Sum>& weights)`:
  associates `weights[i]` with `values[i]`.

The value and weight vectors must have equal lengths. Construction takes
$O(NL + N)$ time and $O(NL + N)$ storage.

## Methods

All index and value intervals are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the sequence length. | $O(1)$ |
| `bool empty()` | Returns whether the sequence is empty. | $O(1)$ |
| `T access(int p)` | Returns the value at index `p`. | $O(L)$ |
| `T operator[](int p)` | Equivalent to `access(p)`. | $O(L)$ |
| `int rank(T x, int r)` | Counts occurrences of `x` in `[0, r)`. | $O(L)$ |
| `int rank(T x, int l, int r)` | Counts occurrences of `x` in `[l, r)`. | $O(L)$ |
| `T kth_smallest(int l, int r, int k)` | Returns the zero-based `k`-th smallest value. | $O(L)$ |
| `T kth_largest(int l, int r, int k)` | Returns the zero-based `k`-th largest value. | $O(L)$ |
| `int range_freq(int l, int r, T upper)` | Counts values less than `upper`. | $O(L)$ |
| `int range_freq(int l, int r, T lower, T upper)` | Counts values in `[lower, upper)`. | $O(L)$ |
| `optional<T> prev_value(int l, int r, T upper)` | Returns the greatest value less than `upper`, or `nullopt`. | $O(L)$ |
| `optional<T> next_value(int l, int r, T lower)` | Returns the smallest value at least `lower`, or `nullopt`. | $O(L)$ |
| `Sum range_sum(int l, int r)` | Returns the total weight in `[l, r)`. | $O(1)$ |
| `Sum range_sum(int l, int r, T upper)` | Sums weights whose values are less than `upper`. | $O(L)$ |
| `Sum range_sum(int l, int r, T lower, T upper)` | Sums weights whose values are in `[lower, upper)`. | $O(L)$ |
| `Sum sum_k_smallest(int l, int r, int k)` | Sums the weights of the smallest `k` values. | $O(L)$ |
| `Sum sum_k_largest(int l, int r, int k)` | Sums the weights of the largest `k` values. | $O(L)$ |

The `k` used by sum methods may range from `0` through `r - l`, inclusive. If
equal values have different weights, `sum_k_smallest` selects ties in original
index order, while `sum_k_largest` selects them in reverse original index order.

## Example

```cpp
#include "ds/wavelet_matrix/wavelet_matrix_sum.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {5, -2, 8, 5, 1};
    m1une::ds::WaveletMatrixSum<long long> matrix(values);

    std::cout << matrix.range_sum(0, 5, 0, 6) << "\n"; // 11
    std::cout << matrix.sum_k_smallest(0, 5, 3) << "\n"; // 4

    std::vector<int> keys = {4, 1, 4, 2};
    std::vector<long long> weights = {10, 20, 30, 40};
    m1une::ds::WaveletMatrixSum<int, long long> weighted(keys, weights);

    std::cout << weighted.range_sum(0, 4, 2, 5) << "\n"; // 80
}
```
