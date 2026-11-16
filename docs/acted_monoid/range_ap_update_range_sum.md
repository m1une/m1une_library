---
title: Range AP Update Range Sum
documentation_of: ../../acted_monoid/range_ap_update_range_sum.hpp
---

## Overview

An Acted Monoid that supports overwriting a range with an arithmetic progression, alongside range sum queries.

The operator replaces existing elements with $f(i) = a \cdot i + b$, where $i$ is the zero-based order inside the updated range.

### Important Usage Note

Similar to `RangeApAddRangeSum`, the node state (`value_type`) tracks `size` and the sum of relative orders (`ord_sum`), enabling $O(1)$ block updates.

To apply a global formula on `[l, r)`, convert it to range-local form first: `a * global_i + b` becomes `a * local_i + (a * l + b)`. The `operator_type` relies on `std::optional` to safely designate the "no operation" state.

## Interface and Complexity

```cpp
using value_type = RangeApUpdateRangeSumNode<T>;
using operator_type = std::optional<std::pair<T, T>>;
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
#include "acted_monoid/range_ap_update_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeApUpdateRangeSum<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Overwrite the range [0, 3) with f(i) = 3 * i + 1, where i is local to [0, 3)
    // Array becomes: {1, 4, 7, 40, 50}
    seg.apply(0, 3, std::optional<std::pair<long long, long long>>({3, 1}));

    // Query sum of range [0, 3) -> 1 + 4 + 7 = 12
    std::cout << seg.prod(0, 3).sum << "\n";

    return 0;
}
```
