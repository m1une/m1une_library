---
title: Range Update Range Min
documentation_of: ../../acted_monoid/range_update_range_min.hpp
---

## Overview

An Acted Monoid representing Range Update (overwrite/assignment) operations and Range Minimum queries.

### Important Usage Note

This implementation uses `std::optional<T>` as the `operator_type` to safely represent the state of "no operation" (the identity element of the operator monoid).

- A valid update operation with value $v$ is represented as `std::optional<T>(v)`.
- The identity operator (no operation) is represented as `std::nullopt`.

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element for the value monoid. Defaults to `std::numeric_limits<T>::max()`.

## Requirements and Behavior

`Id` is reserved for empty or uninitialized values: `mapping` leaves it
unchanged. Do not use it as a real element value, and ensure updates do not
produce it. All arithmetic must remain representable by `T`.

A present optional update assigns a constant; `std::nullopt` is a no-op.

## Interface and Complexity

```cpp
using value_type = T;
using operator_type = std::optional<T>;
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
#include "acted_monoid/range_update_range_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeUpdateRangeMin<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Overwrite range [1, 4) with 5 -> {10, 5, 5, 5, 50}
    seg.apply(1, 4, std::optional<long long>(5));

    // Get the minimum in range [0, 5) -> min(10, 5, 5, 5, 50) = 5
    std::cout << seg.prod(0, 5) << "\n";

    return 0;
}
```
