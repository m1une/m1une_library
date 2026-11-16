---
title: Range Add Range Max
documentation_of: ../../acted_monoid/range_add_range_max.hpp
---

## Overview

An Acted Monoid representing Range Addition operations and Range Maximum queries.

It uses `std::numeric_limits<T>::lowest()` as the default identity element for the Value Monoid to correctly handle negative maximum values.

## Requirements and Behavior

`Id` is reserved for empty or uninitialized values: `mapping` leaves it
unchanged. Do not use it as a real element value, and ensure updates do not
produce it. All arithmetic must remain representable by `T`.

## Interface and Complexity

```cpp
using value_type = T;
using operator_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Composes updates: apply `g` first, then `f`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Returns the aggregate after applying `f`; does not modify `x`. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_max.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeMax<long long>;

int main() {
    std::vector<long long> A = {1, 5, 2, 8, 3};
    m1une::ds::LazySegtree<AM> seg(A);

    // Get the maximum value in [1, 4) -> max(5, 2, 8) = 8
    std::cout << seg.prod(1, 4) << "\n";

    // Add 10 to range [1, 3) -> {1, 15, 12, 8, 3}
    seg.apply(1, 3, 10);

    // Get the maximum value in [1, 4) -> max(15, 12, 8) = 15
    std::cout << seg.prod(1, 4) << "\n";

    return 0;
}
```
