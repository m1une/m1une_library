---
title: Range Add Range ArgMax
documentation_of: ../../acted_monoid/range_add_range_arg_max.hpp
---

## Overview

An acted monoid for range addition and range maximum queries with the position
of the selected maximum.

### Tie-breaking

If there are multiple maximum values in the queried range, the `op` function returns the earliest order.

## Requirements and Behavior

`value_type` stores `max_val`, `size`, and `ord`. `ord` is the zero-based
position within the aggregate, so `prod(l, r)` reports array index `l + ord`.
Ties choose the earliest position. An empty result has `ord == -1`.

## Interface and Complexity

```cpp
using value_type = RangeAddRangeArgMaxNode<T>;
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
#include "acted_monoid/range_add_range_arg_max.hpp"
#include "ds/segtree/lazy_segtree.hpp"
#include <cassert>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeArgMax<long long>;
    m1une::ds::LazySegtree<AM> seg(std::vector<long long>{1, 5, 3, 5});
    seg.apply(1, 3, 2);
    auto result = seg.prod(1, 4);
    assert(result.max_val == 7);
    assert(1 + result.ord == 1);  // Convert query-relative order to array index.
}
```
