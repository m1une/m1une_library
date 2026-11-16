---
title: MinMax Monoid
documentation_of: ../../monoid/min_max.hpp
---

## Overview

A monoid for retrieving both the minimum and maximum values of a contiguous subarray in a single query. The underlying `value_type` is `std::pair<T, T>`, where `first` is the minimum value and `second` is the maximum value.

## Initialization

Use the `make(val)` method to construct a leaf node from a single scalar value.

## Requirements

`T` must support ordered comparison. `MinId` must be at least as large as
all valid values and `MaxId` at most as small. The result pair contains the
minimum in `.first` and maximum in `.second`; `make(v)` returns `{v, v}`.

## Interface and Complexity

```cpp
using value_type = std::pair<T, T>;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/min_max.hpp"
#include <iostream>
#include <vector>

using MinMaxM = m1une::monoid::MinMax<long long>;

int main() {
    std::vector<long long> A = {8, 2, 5, 3, 9, 1};
    int N = A.size();

    std::vector<MinMaxM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = MinMaxM::make(A[i]);
    }

    m1une::ds::Segtree<MinMaxM> seg(init_data);

    // Query the range [1, 4) -> {2, 5, 3}
    auto [min_val, max_val] = seg.prod(1, 4);

    std::cout << "Min: " << min_val << ", Max: " << max_val << "\n"; // Output: Min: 2, Max: 5

    return 0;
}
```
