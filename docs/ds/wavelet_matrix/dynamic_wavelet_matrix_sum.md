---
title: Dynamic Wavelet Matrix with Sums
documentation_of: ../../../ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp
---

## Overview

`m1une::ds::DynamicWaveletMatrixSum<T, Sum>` maintains an integral key and an
additive weight at every position of a dynamic sequence. It supports indexed
insertion, erasure, key and weight updates, range order statistics, and sums
selected by an index interval and a key interval.

Passing only a key uses that key as its weight, which gives ordinary sums of
the stored values. The overloads taking a separate `Sum` can instead maintain
costs, frequencies, or other additive data.

Routing bits use packed dynamic bitvectors. Parallel implicit treaps store
weights in 256-element chunks, so the structure avoids allocating one tree node
for every element at every wavelet level. Signed keys are ordered across their
full type range by an internal sign-bit transform; coordinate compression is
not required.

## Requirements

`T` must be an integral type other than `bool`. `Sum{}` must be the additive
identity, and `Sum` must support copying, addition, and subtraction. The
key-only constructor and update overloads additionally require `T` to be
convertible to `Sum`. Arithmetic overflow is not checked.

Let `B = numeric_limits<make_unsigned_t<T>>::digits` and let `N` be the current
sequence length. Treap complexity is expected, and insertion and erasure are
amortized because fixed-size chunks occasionally split or merge.

## Construction

| Constructor | Description | Complexity |
| --- | --- | --- |
| `DynamicWaveletMatrixSum()` | Constructs an empty sequence. | $O(B)$ |
| `explicit DynamicWaveletMatrixSum(const vector<T>& values)` | Builds keys from `values` and uses each key as its weight. | $O(BN)$ |
| `DynamicWaveletMatrixSum(const vector<T>& values, const vector<Sum>& weights)` | Builds separate keys and weights; the vector lengths must match. | $O(BN)$ |

## Sequence Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the sequence length. | $O(1)$ |
| `bool empty() const` | Tests whether the sequence is empty. | $O(1)$ |
| `void clear()` | Removes every element. | $O(B)$ |
| `T access(int position) const` | Returns the key at `position`. | Expected $O(B\log N)$ |
| `T operator[](int position) const` | Equivalent to `access(position)`. | Expected $O(B\log N)$ |
| `Sum weight(int position) const` | Returns the weight at `position`. | Expected $O(\log N)$ |
| `pair<T, Sum> get(int position) const` | Returns the key and weight at `position`. | Expected $O(B\log N)$ |
| `void insert(int position, T value)` | Inserts `value` as both key and weight before `position`. | Expected amortized $O(B\log N)$ |
| `void insert(int position, T value, const Sum& weight)` | Inserts a separate key and weight before `position`. | Expected amortized $O(B\log N)$ |
| `void push_back(T value)` | Appends `value` as both key and weight. | Expected amortized $O(B\log N)$ |
| `void push_back(T value, const Sum& weight)` | Appends a separate key and weight. | Expected amortized $O(B\log N)$ |
| `pair<T, Sum> erase(int position)` | Erases and returns the key and weight at `position`. | Expected amortized $O(B\log N)$ |
| `void set(int position, T value)` | Replaces both the key and weight with `value`. | Expected amortized $O(B\log N)$ |
| `void set(int position, T value, const Sum& weight)` | Replaces both the key and weight. | Expected amortized $O(B\log N)$ |
| `void set_value(int position, T value)` | Replaces the key and preserves the weight. | Expected amortized $O(B\log N)$ |
| `void set_weight(int position, const Sum& weight)` | Replaces the weight and preserves the key. | Expected $O(B\log N)$ |
| `void add_weight(int position, const Sum& delta)` | Adds `delta` to the weight and preserves the key. | Expected $O(B\log N)$ |

`position == size()` is allowed for insertion. All other positions must refer
to an existing element.

## Query Methods

All index and key intervals are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `int rank(T value, int right) const` | Counts `value` in `[0, right)`. | Expected $O(B\log N)$ |
| `int rank(T value, int left, int right) const` | Counts `value` in `[left, right)`. | Expected $O(B\log N)$ |
| `T kth_smallest(int left, int right, int k) const` | Returns the zero-based `k`-th smallest key. | Expected $O(B\log N)$ |
| `T kth_largest(int left, int right, int k) const` | Returns the zero-based `k`-th largest key. | Expected $O(B\log N)$ |
| `int range_freq(int left, int right, T upper) const` | Counts keys less than `upper`. | Expected $O(B\log N)$ |
| `int range_freq(int left, int right, T lower, T upper) const` | Counts keys in `[lower, upper)`. | Expected $O(B\log N)$ |
| `optional<T> prev_value(int left, int right, T upper) const` | Returns the greatest key below `upper`, or `nullopt`. | Expected $O(B\log N)$ |
| `optional<T> next_value(int left, int right, T lower) const` | Returns the smallest key at least `lower`, or `nullopt`. | Expected $O(B\log N)$ |
| `Sum range_sum(int left, int right) const` | Sums every weight in the index interval. | Expected $O(\log N)$ |
| `Sum range_sum(int left, int right, T upper) const` | Sums weights whose keys are less than `upper`. | Expected $O(B\log N)$ |
| `Sum range_sum(int left, int right, T lower, T upper) const` | Sums weights whose keys are in `[lower, upper)`. | Expected $O(B\log N)$ |
| `Sum sum_k_smallest(int left, int right, int k) const` | Sums the weights of the smallest `k` keys. | Expected $O(B\log N)$ |
| `Sum sum_k_largest(int left, int right, int k) const` | Sums the weights of the largest `k` keys. | Expected $O(B\log N)$ |

The order-statistic methods require `0 <= k < right - left`. The sum methods
allow `0 <= k <= right - left`. Equal keys are selected in current sequence
order by `sum_k_smallest` and in reverse current sequence order by
`sum_k_largest`.

The structure uses $O(BN)$ memory. Index, range, and `k` bounds are asserted.

## Example

```cpp
#include "ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp"

#include <cassert>
#include <vector>

int main() {
    std::vector<int> keys = {4, 1, 4, 2};
    std::vector<long long> weights = {10, 20, 30, 40};
    m1une::ds::DynamicWaveletMatrixSum<int, long long> matrix(
        keys,
        weights
    );

    assert(matrix.range_sum(0, 4, 2, 5) == 80);
    matrix.add_weight(0, 5);
    matrix.insert(2, 3, 7);
    assert(matrix.sum_k_smallest(0, 5, 3) == 67);

    matrix.set_value(1, 5);  // The weight at index 1 remains 20.
    assert(matrix.range_sum(0, 5, 4, 6) == 65);
}
```
