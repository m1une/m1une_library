---
title: Range Update Range Product
documentation_of: ../../acted_monoid/range_update_range_product.hpp
---

## Overview

`m1une::acted_monoid::RangeUpdateRangeProduct<Monoid>` adapts any monoid for
range assignment and range product queries. It works for noncommutative monoids:
the product keeps the original left-to-right order defined by `Monoid::op`.

Assigning `value` to a segment of length $k$ changes its aggregate to
$value^k$. The adapter computes this power with binary exponentiation.

## Requirements and behavior

`Monoid` must satisfy `m1une::monoid::IsMonoid`. In particular, it provides:

* `using value_type = ...;`
* `static value_type id();`
* `static value_type op(const value_type&, const value_type&);`

The operator type is `std::optional<Monoid::value_type>`. `std::nullopt` means
no assignment, and a present value overwrites every element of the segment.
When lazy assignments are composed, the newer present assignment wins.

The aggregate node stores both `product` and `size`. Initialize a lazy segment
tree from `std::vector<Monoid::value_type>` so that its adapting constructor
calls `make(value)`, or call `make(value)` yourself. The size-only
`LazySegtree<AM>(n)` constructor creates identity nodes of length zero and is not
suitable until every leaf has been replaced with a node returned by `make`.

## Interface

For `using AM = m1une::acted_monoid::RangeUpdateRangeProduct<Monoid>;`:

| Member | Signature | Meaning | Complexity |
| --- | --- | --- | --- |
| Base value | `using base_type = typename Monoid::value_type;` | One array element. | -- |
| Aggregate | `using value_type = RangeUpdateRangeProductNode<Monoid>;` | Stores `base_type product` and `long long size`. | -- |
| Lazy operator | `using operator_type = std::optional<base_type>;` | A range assignment, or no operation. | -- |
| Identity | `static constexpr value_type id();` | Empty product with size zero. | One `Monoid::id()` call. |
| Product | `static constexpr value_type op(const value_type& a, const value_type& b);` | Concatenates `a` followed by `b`. | One `Monoid::op()` call. |
| Operator identity | `static constexpr operator_type op_id();` | Returns `std::nullopt`. | $O(1)$ |
| Operator composition | `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g);` | Returns `f` when present, otherwise `g`; `f` is newer. | $O(1)$ plus copying one operator. |
| Apply assignment | `static constexpr value_type mapping(const operator_type& f, const value_type& x);` | Replaces `x.product` by the assigned value to the power `x.size`. | $O(\log x.size)$ monoid operations for an assignment; otherwise one node copy. |
| Make leaf | `static constexpr value_type make(const base_type& value);` | Returns `{value, 1}`. | One value copy. |

With `m1une::ds::LazySegtree<AM>` on $N$ elements, construction and range
product take $O(N)$ and $O(\log N)$ monoid operations respectively. A range
assignment takes $O(\log^2 N)$ monoid operations in the worst case because up
to $O(\log N)$ segment-tree nodes each compute a power. Memory use is $O(N)$.

## Example

```cpp
#include "acted_monoid/range_update_range_product.hpp"
#include "ds/segtree/lazy_segtree.hpp"

#include <iostream>
#include <string>
#include <vector>

struct Concat {
    using value_type = std::string;

    static value_type id() {
        return "";
    }

    static value_type op(const value_type& left, const value_type& right) {
        return left + right;
    }
};

int main() {
    using AM = m1une::acted_monoid::RangeUpdateRangeProduct<Concat>;

    std::vector<std::string> values = {"a", "b", "c", "d"};
    m1une::ds::LazySegtree<AM> seg(values);

    seg.apply(1, 3, std::string("x"));
    std::cout << seg.prod(0, 4).product << '\n';  // axxd
}
```
