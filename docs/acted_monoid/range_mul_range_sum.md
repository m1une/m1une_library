---
title: Range Multiply Range Sum
documentation_of: ../../acted_monoid/range_mul_range_sum.hpp
---

## Overview

An Acted Monoid representing Range Multiplication operations and Range Sum queries.

Unlike Range Addition or Range Affine transformations, Range Multiplication distributes perfectly over addition: $C \times (A + B) = C \cdot A + C \cdot B$. Because of this mathematical property, the `value_type` does **not** need to store the `size` of the segment, making this monoid lighter in memory and faster to compute than the full `RangeAffineRangeSum`.

## Template Parameters

* `T`: The underlying numerical type. It is strongly recommended to use a modular arithmetic struct (e.g., `Modint`) to prevent overflow, as repeated multiplications grow exponentially.

## Interface and Complexity

```cpp
using value_type = T;
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
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_mul_range_sum.hpp"
#include <iostream>
#include <vector>

// Assuming a modular arithmetic type or standard long long for small bounds
using AM = m1une::acted_monoid::RangeMulRangeSum<long long>;

int main() {
    std::vector<long long> A = {2, 3, 4, 1};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        // Initializes leaf node
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Sum of range [0, 3) -> 2 + 3 + 4 = 9
    std::cout << "Initial Sum: " << seg.prod(0, 3) << "\n";

    // Multiply range [0, 2) by 5
    // Array becomes: {10, 15, 4, 1}
    seg.apply(0, 2, 5);

    // Sum of range [0, 3) -> 10 + 15 + 4 = 29
    std::cout << "Updated Sum: " << seg.prod(0, 3) << "\n";

    return 0;
}
```
