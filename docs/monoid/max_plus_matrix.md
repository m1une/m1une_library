---
title: Max-Plus Matrix Monoid
documentation_of: ../../monoid/max_plus_matrix.hpp
---

## Overview

A monoid for range matrix multiplication over the Max-Plus semiring.
In this algebra, the standard addition operation is replaced by `std::max`, and the standard multiplication operation is replaced by regular addition `+`.

This is highly effective for solving **Dynamic DP** problems (where state transitions involve taking the maximum of sums) or finding longest paths over dynamic edge weights on a Segment Tree.

## Requirements

`MaxPlusMatrix<T, N, MinInf>` uses a fixed dimension `N >= 0`. `T` must support
addition and ordered comparison. The sentinel defaults to
`std::numeric_limits<T>::lowest() / 2` and represents an unreachable transition;
it must be reserved and lie beyond every finite result in the optimization
direction. All finite intermediate sums must fit in `T`.

The product is `a * b`. With column-vector states, `b` acts first, then `a`;
a left-to-right segment-tree product applies the rightmost transition first.

## Interface and Complexity

```cpp
using value_type = std::array<std::array<T, N>, N>;
```

Here $N$ is the matrix dimension, rather than the number of array elements.

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns zero on the diagonal and `MinInf` elsewhere. | $O(N^2)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Returns `res[i][j] = max_k(a[i][k] + b[k][j])`, skipping infinity entries. | $O(N^3)$ |
| `static constexpr value_type make_inf()` | Returns a matrix with every entry set to the infinity sentinel. | $O(N^2)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/max_plus_matrix.hpp"
#include <iostream>
#include <vector>

using MaxMat = m1une::monoid::MaxPlusMatrix<long long, 2>;

int main() {
    int N = 3;
    std::vector<MaxMat::value_type> init_data(N);

    for (int i = 0; i < N; ++i) {
        auto mat = MaxMat::make_inf();
        mat[0][0] = 5;
        mat[0][1] = 2;
        mat[1][0] = 3;
        mat[1][1] = 0;
        init_data[i] = mat;
    }

    m1une::ds::Segtree<MaxMat> seg(init_data);

    auto res = seg.prod(0, N);

    std::cout << "Max Cost 0 -> 0: " << res[0][0] << "\n";
    return 0;
}
```
