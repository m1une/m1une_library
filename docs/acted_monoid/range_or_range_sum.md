---
title: Range OR Range Sum
documentation_of: ../../acted_monoid/range_or_range_sum.hpp
---

## Overview

An Acted Monoid representing Range Bitwise OR operations and Range Sum queries.

### Mathematical Mechanism

Because Bitwise OR does not distribute directly over addition, the node must track how many times each individual bit is set within its range. When a Range OR is applied with a value $f$, any bit set to `1` in $f$ forces that specific bit to become `1` for *every* element in the segment. Its bit count immediately becomes equal to `size`.

## Template Parameters

* `T`: The underlying numerical type.
* `BITS`: Max bit length (default 30). Set to 60 for `long long` bounds.

## Requirements and Behavior

The node stores `T sum`, `std::array<int, BITS> bit_count`, and
`long long size`. Read the range sum from `.sum`; `.bit_count[i]` is the number
of elements with bit `i` set. `op_id()` is zero and composition is bitwise OR.

## Interface and Complexity

```cpp
using value_type = RangeOrRangeSumNode<T, BITS>;
using operator_type = T;
```

Let $B = \mathtt{BITS}$. Values and masks must be nonnegative and fit in the lowest `BITS` bits. Choose `T` wide enough for the segment sum and keep segment lengths within `int` for the per-bit counts.

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(B)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(B)$ |
| `static constexpr operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Composes updates: apply `g` first, then `f`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Returns the aggregate after applying `f`; does not modify `x`. | $O(B)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(B)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.
With `LazySegtree`, construction uses $O(NB)$ time and space, and range updates and queries take $O(B \log N)$ time.

## Example

```cpp
#include "acted_monoid/range_or_range_sum.hpp"
#include "ds/segtree/lazy_segtree.hpp"
#include <cassert>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeOrRangeSum<long long, 4>;
    m1une::ds::LazySegtree<AM> seg(std::vector<long long>{1, 2, 3});
    seg.apply(0, 2, 4);  // Values become 5, 6, 3.
    assert(seg.prod(0, 3).sum == 14);
}
```
