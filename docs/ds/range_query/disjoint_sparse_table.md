---
title: Disjoint Sparse Table
documentation_of: ../../../ds/range_query/disjoint_sparse_table.hpp
---

## Overview

A Disjoint Sparse Table that answers static range queries in $O(1)$ time after an $O(N \log N)$ preprocessing step. It operates on any Monoid structure satisfying the `m1une::monoid::IsMonoid` concept.

Unlike a normal Sparse Table, the monoid operation does not need to be idempotent. It can be used for operations like addition, multiplication, matrix multiplication, and other associative operations.

## Template Parameters

* `Monoid`: A struct representing the mathematical monoid, providing `value_type`, `id()`, and `op(a, b)`.

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
| `DisjointSparseTable()` | Constructs an empty disjoint sparse table. | $O(1)$ |
| `explicit DisjointSparseTable(const std::vector<T>& v)` | Builds from `v`. | $O(N \log N)$ |
| `explicit DisjointSparseTable(std::vector<T>&& v)` | Builds from moved values. | $O(N \log N)$ |
| `template <typename U> explicit DisjointSparseTable(const std::vector<U>& v)` | Converts leaves using `Monoid::make(value)`, then `make(value, index)`, then conversion to `T`, in that priority order. | $O(N \log N)$ |
| `T prod(int l, int r) const` | Returns the monoid product over `[l, r)`. | $O(1)$ |

## Example

```cpp
#include "ds/range_query/disjoint_sparse_table.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> A = {5, 2, 8, 1, 3};

    m1une::ds::DisjointSparseTable<m1une::monoid::Add<long long>> dst(A);

    // Get sum of range [0, 3) -> 5 + 2 + 8 = 15
    std::cout << dst.prod(0, 3) << "\n";

    // Get sum of range [2, 5) -> 8 + 1 + 3 = 12
    std::cout << dst.prod(2, 5) << "\n";

    return 0;
}
```
