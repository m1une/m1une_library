---
title: Wavelet Matrix 2D
documentation_of: ../../../ds/wavelet_matrix/wavelet_matrix_2d.hpp
---

## Overview

`m1une::ds::WaveletMatrix2D` is a static multidimensional wavelet matrix for a
sequence of pairs:

$$
A_i=(x_i,y_i).
$$

It supports the following queries:

* count indices `i` satisfying simultaneous half-open bounds on `i`, `x_i`,
  and `y_i`, and
* among indices satisfying bounds on `i` and `x_i`, find the `k`-th smallest
  `y_i`.

Thus the structure handles orthogonal count and quantile queries in the three
dimensions `(index, first component, second component)`. This is the
construction described in
[3 次元空間のクエリを処理する Wavelet Matrix](https://noshi91.hatenablog.com/entry/2021/06/02/165408).

An outer wavelet matrix is built on the second components. At every outer
level, the elements routed to the zero side form another wavelet matrix over
their first components. These inner matrices restrict each outer rank step to
the requested first-component interval.

Packed levels are built one machine word at a time and partitioned from their
zero and one masks. Temporary compressed-coordinate buffers are moved into
inner matrices when possible. AVX2 bit extraction and BMI2 rank masking are
used when enabled at compile time, with compact scalar fallbacks.

The sequence is immutable after construction.

## Template Parameters and Types

```cpp
template <class X, class Y = X>
class WaveletMatrix2D;
```

* `X`: first-component type.
* `Y`: second-component type.

Both types must provide a strict weak ordering through `<`. Coordinates are
compressed internally, so signed values and non-integral orderable types are
supported.

The public aliases are:

```cpp
using first_type = X;
using second_type = Y;
using value_type = std::pair<X, Y>;
```

## Construction

```cpp
WaveletMatrix2D();

explicit WaveletMatrix2D(const std::vector<value_type>& values);
explicit WaveletMatrix2D(std::vector<value_type>&& values);

WaveletMatrix2D(
    const std::vector<X>& first,
    const std::vector<Y>& second
);

void build(std::vector<value_type> values);

void build(
    const std::vector<X>& first,
    const std::vector<Y>& second
);
```

The parallel vectors must have equal lengths. Unlike a geometric point-set
structure, equal pairs are not merged: every sequence position remains a
separate element.

Let $N$ be the sequence length, $H_x$ the bit width of the compressed first
component, and $H_y$ the bit width of the compressed second component.
Construction takes $O(N\log N+NH_xH_y)$ time. The packed bitvectors and their
rank metadata use $O(NH_xH_y/w)$ machine words, where $w$ is the word size,
plus $O(N)$ coordinate and sequence storage.

## Methods

All index and component intervals are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the sequence length. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `const value_type& access(int p) const` | Returns `A[p]`. | $O(1)$ |
| `const value_type& operator[](int p) const` | Equivalent to `access(p)`. | $O(1)$ |
| `int count(int l, int r, const X& d, const X& u, const Y& s, const Y& t) const` | Counts `i` with `l <= i < r`, `d <= A[i].first < u`, and `s <= A[i].second < t`. | $O(H_xH_y)$ |
| `Y quantile(int l, int r, const X& d, const X& u, int k) const` | Returns the zero-based `k`-th smallest second component among `i` with `l <= i < r` and `d <= A[i].first < u`. | $O(H_xH_y)$ |

`quantile` requires `0 <= k < c`, where `c` is the number of elements meeting
its index and first-component restrictions. All methods are `const`; queries do
not mutate the structure.

## Example

```cpp
#include "ds/wavelet_matrix/wavelet_matrix_2d.hpp"

#include <cassert>
#include <utility>
#include <vector>

int main() {
    using Matrix = m1une::ds::WaveletMatrix2D<int>;
    std::vector<Matrix::value_type> values;
    values.emplace_back(3, 8);
    values.emplace_back(1, 5);
    values.emplace_back(4, 2);
    values.emplace_back(2, 7);
    values.emplace_back(3, 1);

    Matrix matrix(values);

    // Indices [1, 5), first component [2, 4), second component [1, 8).
    assert(matrix.count(1, 5, 2, 4, 1, 8) == 2);

    // Second components selected by index [0, 5) and first component [2, 4)
    // are 8, 7, 1. Their sorted order is 1, 7, 8.
    assert(matrix.quantile(0, 5, 2, 4, 1) == 7);
}
```
