---
title: Chmin Chmax Add Segment Tree
documentation_of: ../../../ds/segtree/chmin_chmax_add_segtree.hpp
---

## Overview

`m1une::ds::ChminChmaxAddSegtree<T>` is a ready-made numeric Segment
Tree Beats implementation. It maintains an array under range `chmin`, range
`chmax`, and range addition, and answers range sum, minimum, and maximum
queries.

Use this structure when these exact numeric operations are needed. The separate
`SegtreeBeats<ActedMonoid>` class is the generic alternative for defining a
fallible action with an acted monoid.

`T` must be a signed integral type. Values, additions, and sums must remain
representable by `T`; its minimum and maximum values are reserved internally as
sentinels.

## Public interface

All indices are zero-based and all ranges are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `ChminChmaxAddSegtree()` | Constructs an empty array. | $O(1)$ |
| `ChminChmaxAddSegtree(int n)` | Constructs `n` zeroes. | $O(N)$ |
| `ChminChmaxAddSegtree(const std::vector<T>& v)` | Builds from `v`. | $O(N)$ |
| `int size() const` | Returns the array size. | $O(1)$ |
| `bool empty() const` | Returns whether the array is empty. | $O(1)$ |
| `void chmin(int l, int r, T x)` | Replaces each value in `[l, r)` by its minimum with `x`. | Amortized $O(\log N)$ |
| `void range_chmin(int l, int r, T x)` | Alias of `chmin`. | Amortized $O(\log N)$ |
| `void chmax(int l, int r, T x)` | Replaces each value in `[l, r)` by its maximum with `x`. | Amortized $O(\log N)$ |
| `void range_chmax(int l, int r, T x)` | Alias of `chmax`. | Amortized $O(\log N)$ |
| `void add(int l, int r, T x)` | Adds `x` to `[l, r)`. | $O(\log N)$ |
| `void range_add(int l, int r, T x)` | Alias of `add`. | $O(\log N)$ |
| `T sum(int l, int r)` | Returns the sum of `[l, r)`. | $O(\log N)$ |
| `T range_sum(int l, int r)` | Alias of `sum`. | $O(\log N)$ |
| `T min(int l, int r)` | Returns the minimum of nonempty `[l, r)`. | $O(\log N)$ |
| `T range_min(int l, int r)` | Alias of `min`. | $O(\log N)$ |
| `T max(int l, int r)` | Returns the maximum of nonempty `[l, r)`. | $O(\log N)$ |
| `T range_max(int l, int r)` | Alias of `max`. | $O(\log N)$ |
| `T all_sum() const` | Returns the whole-array sum, or zero when empty. | $O(1)$ |
| `T all_min() const` | Returns the whole-array minimum; the array must be nonempty. | $O(1)$ |
| `T all_max() const` | Returns the whole-array maximum; the array must be nonempty. | $O(1)$ |
| `T get(int i)` | Returns element `i`. | $O(\log N)$ |
| `T operator[](int i)` | Returns element `i`. | $O(\log N)$ |
| `void set(int i, T x)` | Assigns `x` to element `i`. | $O(\log N)$ |
| `std::vector<T> to_vector()` | Materializes the array. | $O(N\log N)$ |

`sum(l, l)` is zero. Minimum and maximum queries require a nonempty range.

## Example

```cpp
#include "ds/segtree/chmin_chmax_add_segtree.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {5, 1, 7, 3};
    m1une::ds::ChminChmaxAddSegtree<long long> seg(values);

    seg.chmin(0, 4, 4);  // 4, 1, 4, 3
    seg.chmax(1, 3, 2);  // 4, 2, 4, 3
    seg.add(0, 2, 10);   // 14, 12, 4, 3

    std::cout << seg.sum(0, 4) << '\n';  // 33
}
```
