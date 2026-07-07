---
title: Knapsack Helpers
documentation_of: ../../../algo/dp/knapsack.hpp
---

## Overview

This header provides small, explicit helpers for common subset-sum and knapsack
DP patterns. The public namespace is `m1une::algo`.

Weights and capacities are nonnegative. Ranges are indexed by exact sum,
capacity, or value depending on the function.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `subset_sum_reachable(weights, limit)` | Returns a `vector<char>` where `result[s]` says whether sum `s` is reachable. | $O(NL / W)$ time, $O(L / W)$ working memory |
| `zero_one_knapsack_max_value(weights, values, capacity, neg_inf)` | Returns max value for each capacity at most `c`. | $O(NC)$ time, $O(C)$ memory |
| `bounded_knapsack_max_value(weights, values, counts, capacity, neg_inf)` | Returns max value for each capacity at most `c` with item limits. | $O(NC)$ time, $O(C)$ memory |
| `zero_one_knapsack_min_weight_for_value(weights, values, value_limit, inf)` | Returns minimum exact weight for each total value. | $O(NV)$ time, $O(V)$ memory |

Here `L` is `limit`, `C` is `capacity`, `V` is `value_limit`, and `W` is the
number of bits in an unsigned machine word.

The max-value functions return arrays of length `capacity + 1`; entry `c` is
the best value using total weight at most `c`. The min-weight function returns
exact-value costs, so unreachable values contain `inf`.

## Example

```cpp
#include "algo/dp/knapsack.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> weights = {2, 3, 4};
    std::vector<long long> values = {4, 5, 7};

    std::vector<long long> best =
        m1une::algo::zero_one_knapsack_max_value(weights, values, 5);
    std::cout << best[5] << '\n';
}
```
