---
title: Sparse Table
documentation_of: ../../../ds/range_query/sparse_table.hpp
---

## Overview

A sparse table preprocesses an immutable array for range queries. It uses
$O(N \log N)$ time and space to build and one monoid operation per nonempty
query.

The operation must be **idempotent**: `Monoid::op(x, x) == x`. Minimum,
maximum, GCD, and bitwise AND/OR satisfy this law. Addition and multiplication
do not; use a disjoint sparse table for those operations.

## Template Parameters

* `Monoid`: A struct representing the mathematical monoid, providing `value_type`, `id()`, and `op(a, b)`. It must be an idempotent monoid.

## Requirements and Behavior

`N` is the array length and `T` is `typename Monoid::value_type`. Ranges satisfy
`0 <= l <= r <= N`; an empty query returns `Monoid::id()`. Products preserve
array order. Queries do not mutate the table.

Bounds assume constant-time monoid operations and copies. In particular, a
GCD query performs one GCD operation, while a matrix query performs one matrix
multiplication. Construction stores $O(N \log N)$ values.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `SparseTable()` | Constructs an empty sparse table. | $O(1)$ |
| `explicit SparseTable(const std::vector<T>& v)` | Builds from `v`. | $O(N \log N)$ |
| `explicit SparseTable(std::vector<T>&& v)` | Builds from moved values. | $O(N \log N)$ |
| `template <typename U> explicit SparseTable(const std::vector<U>& v)` | Converts leaves using `Monoid::make(value)`, then `make(value, index)`, then conversion to `T`, in that priority order. | $O(N \log N)$ |
| `T prod(int l, int r) const` | Returns the monoid product over `[l, r)`. | $O(1)$ |

## Example

```cpp
#include "ds/range_query/sparse_table.hpp"
#include "monoid/min.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> A = {5, 2, 8, 1, 3};

    // Initialize Sparse Table with Min Monoid
    m1une::ds::SparseTable<m1une::monoid::Min<long long>> st(A);

    // Get minimum of range [0, 3) -> min(5, 2, 8) = 2
    std::cout << st.prod(0, 3) << "\n";

    // Get minimum of range [2, 5) -> min(8, 1, 3) = 1
    std::cout << st.prod(2, 5) << "\n";

    return 0;
}
```
