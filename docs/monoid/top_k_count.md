---
title: Top K Count Monoid
documentation_of: ../../monoid/top_k_count.hpp
---

## Overview

A monoid that maintains the Top $K$ (largest) distinct elements and their frequencies (counts) in a range. The underlying `value_type` is `std::vector<std::pair<T, int>>`. Merging two nodes takes $O(K)$ time.

## Initialization

Use the `make(val)` method to construct a leaf node containing a single value with a count of 1.

## Requirements and Behavior

Use `K >= 1`. Each pair stores `(value, count)`; entries are distinct and
sorted in descending value order by default. `Compare` must be consistent
with `==`. Counts and sums of counts must fit in `int`.

## Interface and Complexity

```cpp
using value_type = std::vector<std::pair<T, int>>;
```

Here $K$ is the template capacity; input vectors must be sorted by `Compare`.

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(K)$ |
| `static constexpr value_type make(const T& val, int count = 1)` | Creates an aggregate containing `count` copies of `val`. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/top_k_count.hpp"
#include <iostream>
#include <vector>

// Define a monoid to keep the Top 2 distinct elements and their counts
using Top2CM = m1une::monoid::TopKCount<long long, 2>;

int main() {
    std::vector<long long> A = {10, 50, 50, 40, 50};
    int N = A.size();

    std::vector<Top2CM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = Top2CM::make(A[i]);
    }

    m1une::ds::Segtree<Top2CM> seg(init_data);

    // Get the top 2 elements in the range [0, 5) -> { (50, 3), (40, 1) }
    auto top2 = seg.prod(0, 5);

    for (auto p : top2) {
        std::cout << "Value: " << p.first << " Count: " << p.second << "\n";
    }

    return 0;
}
```
