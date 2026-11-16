---
title: Longest True Monoid
documentation_of: ../../monoid/longest_true.hpp
---

## Overview

A monoid for finding the maximum length of a contiguous subarray where all elements satisfy a specific condition (e.g., all elements are `true` or equal to a target value).

## Initialization

Convert your target elements into booleans and use the `make` method to initialize the leaf nodes.

## Interface and Complexity

```cpp
using value_type = LongestTrueNode;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr value_type make(bool val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/longest_true.hpp"
#include <iostream>
#include <vector>

using LTM = m1une::monoid::LongestTrue;

int main() {
    std::vector<long long> A = {1, 3, 3, 4, 3, 3, 3, 1};
    int N = A.size();
    long long target = 3;

    std::vector<LTM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // Only set to true if the element matches the target
        init_data[i] = LTM::make(A[i] == target);
    }

    m1une::ds::Segtree<LTM> seg(init_data);

    auto res = seg.prod(0, N);
    std::cout << "Max Length of " << target << "s: " << res.max_len << "\n"; // Output: 3

    return 0;
}
```
