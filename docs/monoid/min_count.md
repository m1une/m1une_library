---
title: MinCount Monoid
documentation_of: ../../monoid/min_count.hpp
---

## Overview

A monoid for finding both the **minimum value** and **the frequency (count) of that minimum value** in a range. The underlying `value_type` is `std::pair<T, int>`, where `first` is the value and `second` is the count.

## Initialization

When initializing a segment tree from an array of elements, use the `make(val)` method to construct a leaf node with a default count of 1.

## Requirements

`T` must support comparison; `Compare` (when available) must define a strict
weak ordering. `Id` must be no better than any real element under that ordering.
Counts are nonnegative and their sums must fit in `int`. The identity has count
zero, so an empty query is distinguishable from a real occurrence of `Id`.

## Interface and Complexity

```cpp
using value_type = std::pair<T, int>;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr value_type make(const T& val, int count = 1)` | Creates an aggregate containing `count` copies of `val`. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/min_count.hpp"
#include <iostream>
#include <vector>

using MinCountM = m1une::monoid::MinCount<long long>;

int main() {
    std::vector<long long> A = {3, 1, 4, 1, 5, 1, 9};
    int N = A.size();

    std::vector<MinCountM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = MinCountM::make(A[i]);
    }

    m1une::ds::Segtree<MinCountM> seg(init_data);

    // Query the range [0, 5) -> Elements: {3, 1, 4, 1, 5}
    // Minimum is 1, it appears 2 times.
    auto [min_val, count] = seg.prod(0, 5);
    std::cout << "Min: " << min_val << ", Count: " << count << "\n"; // Output: Min: 1, Count: 2

    return 0;
}
```
