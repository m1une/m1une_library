---
title: Top K Monoid
documentation_of: ../../monoid/top_k.hpp
---

## Overview

A monoid that maintains the Top $K$ (largest) elements in a range. The underlying `value_type` is `std::vector<T>`. Merging two nodes takes $O(K)$ time, so $K$ should be relatively small (e.g., $K \le 10$).

## Initialization

Since the state is a `std::vector<T>`, you can use the `make(val)` helper to automatically wrap a single array element into a vector of size 1.

## Requirements and Behavior

Use `K >= 1`. Aggregates contain at most `K` entries, including duplicates,
in descending order by default. A custom `Compare` must define a strict weak
ordering consistent with value equality.

## Interface and Complexity

```cpp
using value_type = std::vector<T>;
```

Here $K$ is the template capacity; input vectors must be sorted by `Compare`.

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(K)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/top_k.hpp"
#include <iostream>
#include <vector>

// Define a monoid to keep the Top 3 elements
using Top3M = m1une::monoid::TopK<long long, 3>;

int main() {
    std::vector<long long> A = {10, 50, 20, 40, 30};
    int N = A.size();

    std::vector<Top3M::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = Top3M::make(A[i]);
    }

    m1une::ds::Segtree<Top3M> seg(init_data);

    // Get the top 3 elements in the range [0, 4) -> {50, 40, 20}
    std::vector<long long> top3 = seg.prod(0, 4);

    for (long long x : top3) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
```
