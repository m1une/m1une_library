---
title: Range AP Add Range Sum
documentation_of: ../../acted_monoid/range_ap_add_range_sum.hpp
---

## Overview

An Acted Monoid that supports adding an arithmetic progression to a range, alongside range sum queries.

The operator is represented as a function $f(i) = a \cdot i + b$, where $i$ is the zero-based order inside the updated range.

### Important Usage Note

The node state (`value_type`) stores `size` and the sum of relative orders (`ord_sum`) it covers. This makes it usable in dynamic arrays where global indices change after insertions, deletions, and reversals.

To apply a global formula on `[l, r)`, convert it to range-local form first: `a * global_i + b` becomes `a * local_i + (a * l + b)`.

## Interface and Complexity

```cpp
using value_type = RangeApAddRangeSumNode<T>;
using operator_type = std::pair<T, T>;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Composes updates: apply `g` first, then `f`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Returns the aggregate after applying `f`; does not modify `x`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x, long long ord)` | Applies `f` starting at offset `ord` within the updated range. | $O(1)$ |
| `static constexpr operator_type op_shift(const operator_type& f, long long ord)` | Shifts the update origin forward by `ord` positions. | $O(1)$ |
| `static constexpr operator_type op_reverse(const operator_type& f, long long size)` | Rewrites the update for a reversed segment of length `size`. | $O(1)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_ap_add_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;

int main() {
    std::vector<long long> A = {0, 0, 0, 0, 0};
    m1une::ds::LazySegtree<AM> seg(A);

    // Add f(i) = 2 * i + 5 to the range [1, 4), where i is local to [1, 4)
    // Array becomes: {0, 5, 7, 9, 0}
    seg.apply(1, 4, {2, 5});

    // Query sum of range [0, 5) -> 0 + 5 + 7 + 9 + 0 = 21
    std::cout << seg.prod(0, 5).sum << "\n";

    return 0;
}
```
