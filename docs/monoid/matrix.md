---
title: Matrix Monoid
documentation_of: ../../monoid/matrix.hpp
---

## Overview

A monoid for range matrix multiplication. The underlying `value_type` is an `N x N` `std::array`. This is extremely useful for Dynamic DP, where state transitions can be represented as matrix multiplications over a segment tree.

Merging two matrices takes $O(N^3)$ time, so $N$ should be small (typically $N \le 4$).

## Interface and Complexity

```cpp
using value_type = std::array<std::array<T, N>, N>;
```

Here $N$ is the matrix dimension, rather than the number of array elements.

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity matrix. | $O(N^2)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Returns the matrix product `a * b`. | $O(N^3)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/matrix.hpp"
#include <iostream>
#include <vector>

// 2x2 Matrix with long long
using Mat = m1une::monoid::Matrix<long long, 2>;

int main() {
    int N = 3;
    std::vector<Mat::value_type> init_data(N);

    // Initialize matrices (e.g., Fibonacci transition matrices)
    for (int i = 0; i < N; ++i) {
        init_data[i][0] = {1, 1};
        init_data[i][1] = {1, 0};
    }

    m1une::ds::Segtree<Mat> seg(init_data);

    auto res = seg.prod(0, N);

    std::cout << res[0][0] << " " << res[0][1] << "\n";
    std::cout << res[1][0] << " " << res[1][1] << "\n";

    return 0;
}
```
