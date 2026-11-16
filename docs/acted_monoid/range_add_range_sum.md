---
title: Range Add Range Sum
documentation_of: ../../acted_monoid/range_add_range_sum.hpp
---

## Overview

An acted monoid for adding a constant to every element in a range and querying
the range sum.

### Important Usage Note

When adding a value $f$ to a range of sum $x$, the total sum increases by $f \times (\text{length of the range})$. Therefore, the `value_type` cannot just be an integer; it must keep track of the **size** of the range it currently represents.

The `value_type` is defined as `RangeAddRangeSumNode<T>`, which holds both the `sum` and the `size`.

Initialize from a vector of raw values, which `LazySegtree` converts with
`make(val)`, or construct the leaf aggregates explicitly. Avoid the size-only
constructor for an ordinary array: its identity leaves have size zero.

## Requirements and Behavior

The node stores `T sum` and `long long size`; `make(v)` represents one
element, while `id()` has size zero. The operator is the amount to add.

## Interface and Complexity

```cpp
using value_type = RangeAddRangeSumNode<T>;
using operator_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr value_type inv(const value_type& x)` | Returns the group inverse of `x`. | $O(1)$ |
| `static constexpr operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Composes updates: apply `g` first, then `f`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Returns the aggregate after applying `f`; does not modify `x`. | $O(1)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/lazy_segtree.hpp"
#include <cassert>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    m1une::ds::LazySegtree<AM> seg(std::vector<long long>{1, 2, 3});
    seg.apply(1, 3, 4);  // Values become 1, 6, 7.
    assert(seg.prod(0, 3).sum == 14);
    seg.set(0, AM::make(10));
    assert(seg.all_prod().sum == 23);
}
```
