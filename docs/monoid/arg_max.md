---
title: ArgMax Monoid
documentation_of: ../../monoid/arg_max.hpp
---

## Overview

A monoid for finding both the maximum value and its relative order in a range. If there are multiple maximum values, it returns the earliest one.

This is defined as a type alias of `ArgMin` using `std::greater`. For the minimum counterpart, see `monoid/arg_min.hpp`.

## Requirements and Behavior

`value_type` is `ArgMinNode<T>` with fields `value`, `size`, and `ord`
(the field is named `value` even for maxima). `ord` is relative to the queried
range; add its left endpoint to obtain the array index. Ties choose the earliest
position. The empty identity has `size == 0` and `ord == -1`.

## Interface and Complexity

```cpp
using value_type = ArgMinNode<T>;
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
#include "monoid/arg_max.hpp"
#include <iostream>
#include <vector>

using ArgMaxM = m1une::monoid::ArgMax<long long>;

int main() {
    std::vector<long long> A = {4, 8, 5, 8, 2};
    m1une::ds::Segtree<ArgMaxM> seg(A);

    auto res = seg.prod(0, A.size());

    std::cout << "Max Value: " << res.value << "\n"; // Output: 8
    std::cout << "Order: " << res.ord << "\n";       // Output: 1 (Order 1 is chosen over order 3)

    return 0;
}
```
