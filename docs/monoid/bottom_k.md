---
title: Bottom K Monoid
documentation_of: ../../monoid/bottom_k.hpp
---

## Overview

A monoid that maintains the Bottom $K$ (smallest) elements in a range, stored in ascending order. The underlying `value_type` is `std::vector<T>`. Merging two nodes takes $O(K)$ time, so $K$ should be relatively small (e.g., $K \le 10$).

This is defined as a type alias of `TopK` using `std::less`. For the maximum counterpart, see `monoid/top_k.hpp`.

## Initialization

Since the state is a `std::vector<T>`, you can use the `make(val)` helper to automatically wrap a single array element into a vector of size 1.

## Requirements and Behavior

Use `K >= 1`. Aggregates contain at most `K` entries in ascending order,
including duplicates; the identity is an empty vector.

## Interface and Complexity

```cpp
using value_type = std::vector<T>;
```

Here $K$ is the template capacity; input vectors must be sorted in ascending order.

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(K)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/bottom_k.hpp"
#include <iostream>
#include <vector>

// Define a monoid to keep the Bottom 3 elements
using Bottom3M = m1une::monoid::BottomK<long long, 3>;

int main() {
    std::vector<long long> A = {50, 10, 40, 20, 30};
    int N = A.size();

    std::vector<Bottom3M::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = Bottom3M::make(A[i]);
    }

    m1une::ds::Segtree<Bottom3M> seg(init_data);

    // Get the bottom 3 elements in the range [0, 4) -> {10, 20, 40}
    std::vector<long long> bottom3 = seg.prod(0, 4);

    for (long long x : bottom3) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
```
