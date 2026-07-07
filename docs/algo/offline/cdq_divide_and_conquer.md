---
title: CDQ Divide And Conquer
documentation_of: ../../../algo/offline/cdq_divide_and_conquer.hpp
---

## Overview

`cdq_divide_and_conquer` provides the standard recursive shape for offline CDQ
algorithms. It solves the left half, solves the right half, and then calls a
user callback for cross contributions from `[left, middle)` to `[middle, right)`.

The public namespace is `m1une::algo`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `cdq_divide_and_conquer(left, right, solve_cross)` | Runs CDQ on `[left, right)`. | $O(N)$ recursion overhead plus callbacks |
| `cdq_divide_and_conquer(n, solve_cross)` | Runs CDQ on `[0, n)`. | $O(N)$ recursion overhead plus callbacks |

The callback signature is `solve_cross(int left, int middle, int right)`.
Sorting, Fenwick updates, and rollback are intentionally left to the callback,
because those details depend on the offline problem.

## Example

```cpp
#include "algo/offline/cdq_divide_and_conquer.hpp"

#include <vector>

int main() {
    std::vector<int> a = {3, 1, 2};
    long long inversions = 0;

    m1une::algo::cdq_divide_and_conquer(int(a.size()), [&](int l, int m, int r) {
        for (int i = l; i < m; ++i) {
            for (int j = m; j < r; ++j) {
                if (a[j] < a[i]) ++inversions;
            }
        }
    });
}
```
