---
title: Range Bitwise AND/OR Range Sum
documentation_of: ../../beats_acted_monoid/range_bitwise_and_or_range_sum.hpp
---

## Overview

`m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<T, BITS>` is a Beats
acted monoid for range bitwise AND and OR updates with range-sum queries.

Unlike the ordinary acted monoid that stores a count for every bit, this Beats
version stores only the sum, aggregate bitwise AND, aggregate bitwise OR, and
segment length. An update applies directly when every bit it changes is uniform
throughout the node. If a changed bit is mixed, `can_apply` returns `false` and
the Beats tree descends.

The lazy `operator_type` represents

```cpp
f(x) = (x & and_mask) | or_mask;
```

Use `make_and` and `make_or` instead of constructing an operator directly.

## Template requirements

* `T` must be a non-boolean integral type. Values are nonnegative, occupy only
  the lowest `BITS` bits, and have range sums representable by `T`.
* `BITS` defaults to `30` and must be between `1` and
  `std::numeric_limits<T>::digits`, inclusive.

`value_type` is `RangeBitwiseAndOrRangeSumNode<T>` and has these public members:

```cpp
T sum;
T bitwise_and;
T bitwise_or;
long long length;
```

`operator_type` has public members `T and_mask` and `T or_mask`.

## Interface and complexity

Every acted-monoid operation takes $O(1)$ time, independently of `BITS`.

| Member | Description | Complexity |
| --- | --- | --- |
| `static T bit_mask()` | Returns a mask with its lowest `BITS` bits set. | $O(1)$ |
| `static value_type id()` | Returns the empty aggregate. | $O(1)$ |
| `static value_type op(const value_type& x, const value_type& y)` | Concatenates two aggregates. | $O(1)$ |
| `static operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static operator_type op_comp(const operator_type& f, const operator_type& g)` | Returns $f \circ g$. | $O(1)$ |
| `static bool can_apply(const operator_type& f, const value_type& x)` | Reports whether every changed bit is uniform in `x`. | $O(1)$ |
| `static value_type mapping(const operator_type& f, const value_type& x)` | Applies an update after `can_apply` succeeds. | $O(1)$ |
| `static value_type make(const T& value)` | Constructs a one-element aggregate. | $O(1)$ |
| `static operator_type make_and(const T& mask)` | Constructs `x = x & mask`. | $O(1)$ |
| `static operator_type make_or(const T& mask)` | Constructs `x = x | mask`. | $O(1)$ |

With `SegtreeBeats`, an operation takes $O(\log N+D)$, where $D$ is the number
of extra nodes visited because a changed bit is mixed. Read a query result from
the returned node's `sum` member.

## Example

```cpp
#include "beats_acted_monoid/range_bitwise_and_or_range_sum.hpp"
#include "ds/segtree/segtree_beats.hpp"

#include <iostream>
#include <vector>

using AM =
    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<long long, 30>;

int main() {
    std::vector<long long> values = {1, 2, 3, 4};
    m1une::ds::SegtreeBeats<AM> seg(values);

    seg.apply(0, 3, AM::make_or(4));
    seg.apply(1, 4, AM::make_and(6));

    std::cout << seg.prod(0, 4).sum << '\n';
}
```
