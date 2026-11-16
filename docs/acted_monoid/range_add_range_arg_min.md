---
title: Range Add Range ArgMin
documentation_of: ../../acted_monoid/range_add_range_arg_min.hpp
---

## Overview

An Acted Monoid that supports range addition queries and can dynamically track both the **minimum value** and its **relative order** in a range.

Adding a uniform constant to a range shifts all elements by the same amount, meaning the relative ordering remains unchanged.

By reusing `m1une::monoid::ArgMin`, this structure resolves ties by prioritizing the earlier order.

## Template Parameters

* `T`: The underlying scalar type (e.g., `long long`).
* `Id`: The identity element for the value. Defaults to `std::numeric_limits<T>::max()`.
* `Compare`: The comparison functor. Defaults to `std::less<T>`. To build a **Range Add Range ArgMax**, simply pass `std::greater<T>`.

## Requirements and Behavior

The node stores `value`, `size`, and query-relative `ord`. For
`prod(l, r)`, add `l` to a nonnegative `ord` to obtain the array index. Ties
choose the earliest position. An empty result has `ord == -1`.

## Interface and Complexity

```cpp
using value_type = m1une::monoid::ArgMinNode<T>;
using operator_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Composes updates: apply `g` first, then `f`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Returns the aggregate after applying `f`; does not modify `x`. | $O(1)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_arg_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeArgMin<long long>;

int main() {
    std::vector<long long> A = {8, 4, 9, 4, 7};
    m1une::ds::LazySegtree<AM> seg(A);

    // Initial min is 4 at order 1 (ties broken by earlier order)
    auto q1 = seg.prod(0, A.size());
    std::cout << "Min: " << q1.value << ", Order: " << q1.ord << "\n"; // Output: Min: 4, Order: 1

    // Add 10 to range [0, 3) -> {18, 14, 19, 4, 7}
    seg.apply(0, 3, 10);

    // New min is 4 at order 3
    auto q2 = seg.prod(0, A.size());
    std::cout << "Min: " << q2.value << ", Order: " << q2.ord << "\n"; // Output: Min: 4, Order: 3

    return 0;
}
```
