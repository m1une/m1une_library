---
title: Dynamic Wavelet Matrix
documentation_of: ../../../ds/wavelet_matrix/dynamic_wavelet_matrix.hpp
---

## Overview

`m1une::ds::DynamicWaveletMatrix<T>` maintains an integral sequence while
supporting insertion, erasure, point assignment, frequency queries, and range
order statistics. It is the updateable counterpart of `WaveletMatrix` and uses
zero-based indices and half-open ranges.

Each wavelet level stores its routing bits in a dynamic rank bit vector. The bit
vector is an implicit randomized treap of packed 256-bit chunks, keeping memory
usage substantially below a one-node-per-bit representation.

## Requirements

`T` must be an integral type other than `bool`. Signed values are ordered by
their usual numeric order, and the full range of `T` is supported. Treap bounds
are expected and insertion and erasure bounds are amortized because packed
chunks occasionally split or merge.

Let `B = numeric_limits<make_unsigned_t<T>>::digits` and let `N` be the current
sequence length.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `DynamicWaveletMatrix()` | Constructs an empty sequence. | $O(B)$ |
| `explicit DynamicWaveletMatrix(const std::vector<T>& values)` | Builds from `values`. | $O(BN)$ |
| `int size() const` | Returns the sequence length. | $O(1)$ |
| `bool empty() const` | Tests whether the sequence is empty. | $O(1)$ |
| `void clear()` | Removes every value. | $O(B)$ |
| `T access(int position) const` | Returns the value at `position`. | Expected $O(B\log N)$ |
| `T operator[](int position) const` | Equivalent to `access(position)`. | Expected $O(B\log N)$ |
| `void insert(int position, T value)` | Inserts before `position`; `position == size()` is allowed. | Expected amortized $O(B\log N)$ |
| `void push_back(T value)` | Appends `value`. | Expected amortized $O(B\log N)$ |
| `T erase(int position)` | Erases and returns the value at `position`. | Expected amortized $O(B\log N)$ |
| `void set(int position, T value)` | Assigns `value` at `position`. | Expected amortized $O(B\log N)$ |
| `int rank(T value, int right) const` | Counts `value` in `[0, right)`. | Expected $O(B\log N)$ |
| `int rank(T value, int left, int right) const` | Counts `value` in `[left, right)`. | Expected $O(B\log N)$ |
| `T kth_smallest(int left, int right, int k) const` | Returns the zero-based `k`-th smallest value in `[left, right)`. | Expected $O(B\log N)$ |
| `T kth_largest(int left, int right, int k) const` | Returns the zero-based `k`-th largest value in `[left, right)`. | Expected $O(B\log N)$ |
| `int range_freq(int left, int right, T upper) const` | Counts values less than `upper` in `[left, right)`. | Expected $O(B\log N)$ |
| `int range_freq(int left, int right, T lower, T upper) const` | Counts values in `[lower, upper)` within `[left, right)`. | Expected $O(B\log N)$ |
| `std::optional<T> prev_value(int left, int right, T upper) const` | Returns the largest value below `upper`, or `nullopt`. | Expected $O(B\log N)$ |
| `std::optional<T> next_value(int left, int right, T lower) const` | Returns the smallest value at least `lower`, or `nullopt`. | Expected $O(B\log N)$ |

The structure uses $O(BN)$ memory. Query indices and update positions are
asserted. `kth_smallest` and `kth_largest` require
`0 <= k < right - left`.

## Example

```cpp
#include "ds/wavelet_matrix/dynamic_wavelet_matrix.hpp"

#include <cassert>
#include <vector>

int main() {
    std::vector<int> values = {5, 1, 4, 1, 3};
    m1une::ds::DynamicWaveletMatrix<int> matrix(values);

    assert(matrix.kth_smallest(0, 5, 2) == 3);
    matrix.set(0, 0);
    matrix.insert(2, 7);
    assert(matrix.rank(1, 0, matrix.size()) == 2);
    assert(matrix.erase(2) == 7);
}
```
