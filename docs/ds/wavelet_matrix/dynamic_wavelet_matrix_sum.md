---
title: Dynamic Wavelet Matrix with Sums
documentation_of: ../../../ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp
---

## Overview

`m1une::ds::DynamicWaveletMatrixSum<T, Sum, BitWidth>` maintains an integral
key and an additive weight at every position of a dynamic sequence. It supports
indexed insertion, erasure, key and weight updates, range order statistics, and
sums selected by an index interval and a key interval. `BitWidth` defaults to
the full width of `T`, so existing one- and two-argument uses are unchanged.

Passing only a key uses that key as its weight, which gives ordinary sums of
the stored values. The overloads taking a separate `Sum` can instead maintain
costs, frequencies, or other additive data.

Each wavelet level uses one implicit treap of 64-element chunks. A chunk stores
packed routing bits, contiguous weights, and 16-element group aggregates
together. Fused updates and prefix-statistics queries therefore traverse one
tree per level instead of separate bit and weight trees. Signed full-width keys
are ordered by an internal sign-bit transform; coordinate compression is not
required.

## Requirements

`T` must be an integral type other than `bool`. `Sum{}` must be the additive
identity, and `Sum` must support copying, addition, and subtraction. The
key-only constructor and update overloads additionally require `T` to be
convertible to `Sum`. Arithmetic overflow is not checked.

`BitWidth` must be between one and the number of value bits in the unsigned
version of `T`. A reduced `BitWidth` is supported only for unsigned `T`; every
stored key must be less than `2^BitWidth`, which is asserted in debug builds.
Query bounds may equal or exceed `2^BitWidth` and then naturally include the
entire reduced-width key universe. Full-width signed keys preserve ordinary
signed ordering, including the minimum and maximum values.

Let `B = BitWidth` and let `N` be the current sequence length. Treap complexity
is expected, and insertion and erasure are amortized because fixed-size chunks
occasionally split or merge.

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
| `template <class Predicate> int max_count_smallest(int left, int right, Predicate predicate) const` | Returns the largest `k` for which `predicate(sum_k_smallest(left, right, k))` is true. | Expected $O(B\log N)$ |
| `template <class Predicate> int max_count_largest(int left, int right, Predicate predicate) const` | Returns the largest `k` for which `predicate(sum_k_largest(left, right, k))` is true. | Expected $O(B\log N)$ |

The order-statistic methods require `0 <= k < right - left`. The sum methods
allow `0 <= k <= right - left`. Equal keys are selected in current sequence
order by `sum_k_smallest` and in reverse current sequence order by
`sum_k_largest`.

For `max_count_smallest` and `max_count_largest`, `predicate(Sum{})` must be
true. Over `k = 0, 1, ..., right - left`, the predicate results for the
corresponding sums must consist of zero or more `true` values followed by zero
or more `false` values. The predicate must not have side effects. Tie ordering
is the same as for the corresponding `sum_k` method.

The structure uses $O(BN)$ memory. Queries do not allocate. Point-weight
replacement updates only the affected element, group sum, chunk sum, and
ancestor sums. Insertion and erasure may shift and rebuild one 64-element local
chunk. Index, range, and `k` bounds are asserted.

## Example

```cpp
#include "ds/wavelet_matrix/dynamic_wavelet_matrix_sum.hpp"

#include <cassert>
#include <vector>

int main() {
    using Matrix = m1une::ds::DynamicWaveletMatrixSum<
        unsigned int,
        long long,
        18
    >;
    std::vector<unsigned int> keys = {4, 1, 4, 2};
    std::vector<long long> weights = {10, 20, 30, 40};
    Matrix matrix(
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

Here the keys can be coordinate-compressed ranks while the weights remain the
original numeric values. The key controls ordering; selected sums use the
weight. See the standalone local benchmark and its measured results under
`benchmark/ds/wavelet_matrix/`. They are performance measurements, not formal
verification.
