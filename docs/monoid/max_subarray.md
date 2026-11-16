---
title: Max Subarray Monoid
documentation_of: ../../monoid/max_subarray.hpp
---

## Overview

A monoid for finding the maximum contiguous subarray sum within a range.
The underlying state is `m1une::monoid::SubarrayNode<T>`, which holds 4 values:
1. `sum`: The sum of the entire segment.
2. `pre`: The maximum prefix sum.
3. `suf`: The maximum suffix sum.
4. `opt`: The maximum subarray sum inside the segment.

## Initialization

To initialize a leaf node for a single value $x$, use the `make(val, allow_empty)` method.

* **If empty subarrays are NOT allowed (Standard):**
  Use `make(x)` or `make(x, false)`. At least 1 element must be chosen.
* **If empty subarrays ARE allowed (Max is bounded below by 0):**
  Use `make(x, true)`.

## Requirements and Behavior

Choose the same `allow_empty` policy for every leaf. The empty aggregate
has `opt == Id`; reserve `Id` so no real best subarray sum equals it, and keep
every intermediate sum representable.

## Interface and Complexity

```cpp
using value_type = SubarrayNode<T>;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr value_type make(const T& val, bool allow_empty = false)` | Creates a leaf; `allow_empty` permits a subarray of sum zero. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/max_subarray.hpp"
#include <iostream>
#include <vector>

using MaxSubM = m1une::monoid::MaxSubarray<long long>;

int main() {
    std::vector<long long> A = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int N = A.size();

    std::vector<MaxSubM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // Standard initialization (At least 1 element must be chosen)
        init_data[i] = MaxSubM::make(A[i]);
    }

    m1une::ds::Segtree<MaxSubM> seg(init_data);

    // Max subarray sum in the whole array is 6 (from "4, -1, 2, 1")
    auto node = seg.prod(0, N);
    std::cout << "Max Subarray Sum: " << node.opt << "\n";

    return 0;
}
```
