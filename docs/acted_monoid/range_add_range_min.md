---
title: Range Add Range Min
documentation_of: ../../acted_monoid/range_add_range_min.hpp
---

## Overview

An Acted Monoid representing Range Addition operations and Range Minimum queries. It safely handles the identity element to prevent wrapping or incorrect modifications on uninitialized values.

## Template Parameters

* `T`: The underlying scalar data type (e.g., `long long`, `int`).
* `Id`: The identity element for the value monoid. Defaults to `std::numeric_limits<T>::max()`.

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
#include "acted_monoid/range_add_range_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeMin<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Add -15 to all elements in range [1, 4) -> {10, 5, 15, 25, 50}
    seg.apply(1, 4, -15);

    // Get the minimum in range [0, 3) -> min(10, 5, 15) = 5
    std::cout << seg.prod(0, 3) << "\n";

    return 0;
}
```
