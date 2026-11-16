---
title: Longest Same Monoid
documentation_of: ../../monoid/longest_same.hpp
---

## Overview

A monoid for finding the maximum length of a contiguous subarray where all elements have the same value.

## Initialization

When initializing a segment tree from an array of elements, you should use the `make` helper method to correctly build the leaf nodes.

## Interface and Complexity

```cpp
using value_type = LongestSameNode<T>;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/longest_same.hpp"
#include <iostream>
#include <vector>

using LSM = m1une::monoid::LongestSame<long long>;

int main() {
    std::vector<long long> A = {2, 2, 5, 5, 5, 2, 2};
    int N = A.size();

    std::vector<LSM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = LSM::make(A[i]);
    }

    m1une::ds::Segtree<LSM> seg(init_data);

    // Get the maximum length of consecutive identical elements in range [0, 7)
    auto res = seg.prod(0, N);
    std::cout << "Max Length: " << res.max_len << "\n"; // Output: 3 (because of "5, 5, 5")

    return 0;
}
```
