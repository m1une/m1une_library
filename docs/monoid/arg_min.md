---
title: ArgMin Monoid
documentation_of: ../../monoid/arg_min.hpp
---

## Overview

A monoid for finding both the minimum value and its relative order in a range. If there are multiple minimum values, it returns the earliest one.

For the maximum counterpart, see `monoid/arg_max.hpp`.

## Requirements and Behavior

`value_type` stores `T value`, `long long size`, and `long long ord`.
`ord` is relative to the aggregate: for `prod(l, r)`, the array position is
`l + ord`. Ties choose the earliest position; the empty identity has `size == 0`
and `ord == -1`. `Compare` must be a strict weak ordering.

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
#include "monoid/arg_min.hpp"
#include <iostream>
#include <vector>

using ArgMinM = m1une::monoid::ArgMin<long long>;

int main() {
    std::vector<long long> A = {4, 2, 5, 2, 8};
    m1une::ds::Segtree<ArgMinM> seg(A);

    auto res = seg.prod(0, A.size());

    std::cout << "Min Value: " << res.value << "\n"; // Output: 2
    std::cout << "Order: " << res.ord << "\n";       // Output: 1 (Order 1 is chosen over order 3)

    return 0;
}
```
