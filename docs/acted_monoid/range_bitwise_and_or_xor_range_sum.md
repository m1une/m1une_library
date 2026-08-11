---
title: Range Bitwise AND/OR/XOR Range Sum
documentation_of: ../../acted_monoid/range_bitwise_and_or_xor_range_sum.hpp
---

## Overview

`RangeBitwiseAndOrXorRangeSum<T, BITS>` is an acted monoid for range bitwise
AND, OR, and XOR updates and range sum queries. It is intended for lazy data
structures such as `LazySegtree`.

Each value node stores the segment sum, size, and set-bit count at every tracked
bit. A lazy operator represents

$$
f(x) = (x \mathbin{\&} a) \mathbin{\hat{}} b.
$$

This form represents AND, OR, XOR, and every composition of those operations.
The order of lazy operators matters.

`value_type` has members `T sum`, `std::array<long long, BITS> bit_count`, and
`long long size`. `operator_type` has members `T and_mask` and `T xor_mask`.
Prefer the three update factories below instead of constructing an operator
directly.

## Template Parameters

* `T`: A non-boolean integral type used for values, masks, and sums. Values must
  be nonnegative and fit in the lowest `BITS` bits. The sum must fit in `T`.
* `BITS`: Number of low bits to track. It defaults to `30` and must not exceed
  `std::numeric_limits<T>::digits`. For values below $2^{60}$, use
  `RangeBitwiseAndOrXorRangeSum<long long, 60>`.

## Interface and Complexity

Let $B = \mathtt{BITS}$.

| Member | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(B)$ |
| `static constexpr value_type op(const value_type& x, const value_type& y)` | Concatenates two aggregates. | $O(B)$ |
| `static constexpr T bit_mask()` | Returns a mask whose lowest `BITS` bits are set. | $O(1)$ |
| `static constexpr operator_type op_id()` | Returns the identity lazy operator. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Returns the composition $f \circ g$. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Applies `f` to an aggregate. | $O(B)$ |
| `static constexpr value_type make(const T& value)` | Constructs a one-element aggregate. | $O(B)$ |
| `static constexpr operator_type make_and(const T& mask)` | Constructs the update $x \gets x \mathbin{\&} \mathtt{mask}$. | $O(1)$ |
| `static constexpr operator_type make_or(const T& mask)` | Constructs the update $x \gets x \mathbin{|} \mathtt{mask}$. | $O(1)$ |
| `static constexpr operator_type make_xor(const T& mask)` | Constructs the update $x \gets x \mathbin{\hat{}} \mathtt{mask}$. | $O(1)$ |

With `LazySegtree`, construction takes $O(NB)$, a range update takes
$O(B \log N)$, and a range-sum query takes $O(B \log N)$. Read the answer from
the returned node's `sum` member.

## Example

```cpp
#include "acted_monoid/range_bitwise_and_or_xor_range_sum.hpp"
#include "ds/segtree/lazy_segtree.hpp"

#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<long long, 30>;

int main() {
    std::vector<long long> values = {1, 2, 3, 4};
    m1une::ds::LazySegtree<AM> seg(values);

    seg.apply(0, 3, AM::make_or(4));
    seg.apply(1, 4, AM::make_xor(1));
    seg.apply(0, 2, AM::make_and(6));

    std::cout << seg.prod(0, 4).sum << '\n';
}
```
