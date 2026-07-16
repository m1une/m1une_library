---
title: Wavelet Matrix
documentation_of: ../../../ds/wavelet_matrix/wavelet_matrix.hpp
---

## Overview

`m1une::ds::WaveletMatrix` is a static data structure for integral sequences.
It supports access, occurrence counting, range order statistics, range
frequency queries, and predecessor/successor searches.

Each level uses a packed bitvector with constant-time prefix rank. Signed values
are ordered by flipping their sign bit internally, so negative values and the
full range of the selected integer type work without coordinate compression.
Leading bits shared by every value are omitted.

Construction packs each level one machine word at a time and performs stable
partitioning by iterating the packed zero and one masks. This avoids an
unpredictable branch for every input value. AVX2 is used for bit extraction and
BMI2 for rank masking when those instruction sets are enabled at compile time;
otherwise the same compact bit and prefix arrays use portable scalar
operations.

## Template Parameter

* `T`: A non-`bool` integral type.

Let $B$ be the bit width of `T`, such as 32 for `int` or 64 for `long long`.
Let $L$ be the bit width of the exclusive-or of the minimum and maximum
internally encoded values. Thus $0 \le L \le B$; equal values have $L = 0$.

## Construction

* `WaveletMatrix()`: creates an empty matrix.
* `WaveletMatrix(const std::vector<T>& values)`: builds from `values`.

Construction takes $O(NL + N)$ time and $O(NL)$ bits for level bitvectors,
plus rank metadata and $O(N)$ temporary storage.

## Methods

All index ranges are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the sequence length. | $O(1)$ |
| `bool empty()` | Returns whether the sequence is empty. | $O(1)$ |
| `T access(int p)` | Returns the value at index `p`. | $O(L)$ |
| `T operator[](int p)` | Equivalent to `access(p)`. | $O(L)$ |
| `int rank(T x, int r)` | Counts occurrences of `x` in `[0, r)`. | $O(L)$ |
| `int rank(T x, int l, int r)` | Counts occurrences of `x` in `[l, r)`. | $O(L)$ |
| `T kth_smallest(int l, int r, int k)` | Returns the zero-based `k`-th smallest value in `[l, r)`. | $O(L)$ |
| `T kth_largest(int l, int r, int k)` | Returns the zero-based `k`-th largest value in `[l, r)`. | $O(L)$ |
| `int range_freq(int l, int r, T upper)` | Counts values less than `upper` in `[l, r)`. | $O(L)$ |
| `int range_freq(int l, int r, T lower, T upper)` | Counts values in `[lower, upper)` within `[l, r)`. | $O(L)$ |
| `optional<T> prev_value(int l, int r, T upper)` | Returns the greatest value less than `upper`, or `nullopt`. | $O(L)$ |
| `optional<T> next_value(int l, int r, T lower)` | Returns the smallest value at least `lower`, or `nullopt`. | $O(L)$ |

`kth_smallest` and `kth_largest` require `0 <= k < r - l`.

For range sums or weights attached to values, use `WaveletMatrixSum`.

## Example

```cpp
#include "ds/wavelet_matrix/wavelet_matrix.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {5, -2, 8, 5, 1};
    m1une::ds::WaveletMatrix<long long> matrix(values);

    std::cout << matrix.kth_smallest(0, 5, 1) << "\n";  // 1
    std::cout << matrix.rank(5, 0, 4) << "\n";          // 2
    std::cout << matrix.range_freq(1, 5, 0, 6) << "\n"; // 3

    auto predecessor = matrix.prev_value(0, 5, 5);
    if (predecessor) std::cout << *predecessor << "\n"; // 1
}
```
