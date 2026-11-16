---
title: Strict Max 2 Monoid
documentation_of: ../../monoid/strict_max2.hpp
---

## Overview

A monoid that maintains the strictly largest (`opt1`) and strictly second-largest (`opt2`) values in a contiguous subarray. If all elements in the range are the same, `opt2` will remain the identity element.

This is the maximum counterpart to `monoid/strict_min2.hpp`.

## Requirements and Behavior

`opt1` and `opt2` are the two largest distinct values. A missing entry
is `Id`; reserve that sentinel and do not store it as a real value.

## Interface and Complexity

```cpp
using value_type = StrictOpt2Node<T>;
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
#include "monoid/strict_max2.hpp"
#include <iostream>
#include <vector>

using StrictMax2M = m1une::monoid::StrictMax2<long long>;

int main() {
    std::vector<long long> A = {8, 8, 5, 3, 8, 6};
    int N = A.size();

    std::vector<StrictMax2M::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = StrictMax2M::make(A[i]);
    }

    m1une::ds::Segtree<StrictMax2M> seg(init_data);

    auto res = seg.prod(2, 6); // Range: [5, 3, 8, 6]

    std::cout << "1st Max: " << res.opt1 << "\n"; // Output: 8
    std::cout << "2nd Max: " << res.opt2 << "\n"; // Output: 6

    return 0;
}
```
