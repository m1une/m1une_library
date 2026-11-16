---
title: Range Update Range Max Subarray
documentation_of: ../../acted_monoid/range_update_range_max_subarray.hpp
---

## Overview

An acted monoid for range assignment and maximum contiguous subarray sums.

Each aggregate stores the whole-segment sum, best prefix and suffix sums, and
best subarray sum. Combining adjacent segments also considers a subarray that
crosses their boundary.

### Usage Notes

* `operator_type` uses `std::optional<T>`, where `std::nullopt` represents no operation.
* It always allows an empty subarray, so the answer is at least zero.

## Requirements and Behavior

The node stores `sum`, `pref`, `suff`, `max_sub`, and `size`. Empty
subarrays are allowed, so `max_sub` is at least zero even when every element is
negative. A present optional update assigns a constant; `std::nullopt` is a no-op.

## Interface and Complexity

```cpp
using value_type = RangeUpdateRangeMaxSubarrayNode<T>;
using operator_type = std::optional<T>;
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
#include "acted_monoid/range_update_range_max_subarray.hpp"
#include "ds/segtree/lazy_segtree.hpp"
#include <cassert>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeUpdateRangeMaxSubarray<long long>;
    m1une::ds::LazySegtree<AM> seg(std::vector<long long>{-2, 3, -1, 4});
    assert(seg.prod(0, 4).max_sub == 6);
    seg.apply(1, 3, -5);  // Values become -2, -5, -5, 4.
    assert(seg.prod(0, 4).max_sub == 4);
    assert(seg.prod(0, 3).max_sub == 0);  // Choose the empty subarray.
}
```
