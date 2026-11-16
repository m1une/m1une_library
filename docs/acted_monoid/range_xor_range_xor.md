---
title: Range Xor Range Xor
documentation_of: ../../acted_monoid/range_xor_range_xor.hpp
---

## Overview

An acted monoid that supports range bitwise XOR operations and range XOR sum queries.

### Important Usage Note

When a value $f$ is XORed to all elements in a segment, the total XOR sum of the segment changes by $f$ only if the segment's length is odd. Therefore, `value_type` holds the size of the segment. Use the `make(val)` helper function to initialize leaf nodes.

## Interface and Complexity

```cpp
using value_type = RangeXorRangeXorNode<T>;
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
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_xor_range_xor.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeXorRangeXor<long long>;

int main() {
    std::vector<long long> A = {1, 2, 3, 4, 5};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    seg.apply(1, 4, 7);

    std::cout << seg.prod(1, 4).val << "\n";

    return 0;
}
```
