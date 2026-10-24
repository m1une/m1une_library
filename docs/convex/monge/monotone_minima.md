---
title: Monotone Minima
documentation_of: ../../../convex/monge/monotone_minima.hpp
---

## Overview

The divide-and-conquer monotone-minima algorithm finds one optimum in every
row when the leftmost optimal columns are known to be nondecreasing.

Its precondition is weaker and sometimes easier to establish than total
monotonicity, although its asymptotic complexity is slightly worse than SMAWK.
It is commonly used for divide-and-conquer DP optimization.

## Worked example: search ordered candidate ranges

For each of three requests, choose the cheapest of four choices. The costs
are known in advance:

| Request / row | Choice 0 | Choice 1 | Choice 2 | Choice 3 | Best choice | Minimum cost |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 5 | 9 | 21 | 41 | 0 | 5 |
| 1 | 6 | 2 | 6 | 18 | 1 | 2 |
| 2 | 23 | 11 | 7 | 11 | 2 | 7 |

The straightforward search examines every choice in each row:

```cpp
for (int row = 0; row < rows; ++row) {
    int best = 0;
    for (int column = 1; column < columns; ++column) {
        if (cost[row][column] < cost[row][best]) best = column;
    }
    // best is the choice index; cost[row][best] is the minimum cost.
}
```

Suppose you can prove that the best choice indices never decrease from one
row to the next. Here they are `0,1,2`. The monotone-minima call replaces the
nested search:

```cpp
#include "convex/monge/monotone_minima.hpp"
#include <cassert>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<long long>> cost = {
        {5, 9, 21, 41},
        {6, 2, 6, 18},
        {23, 11, 7, 11}
    };
    int rows = int(cost.size());          // 3 answers to compute.
    int columns = int(cost[0].size());    // 4 choices for each answer.
    auto value = [&](int row, int column) {
        return cost[row][column];         // Return one cost, without minimizing.
    };
    auto best_choice = m1une::convex::monotone_row_argmin(rows, columns, value);
    assert(best_choice == std::vector<int>({0, 1, 2}));
    for (int row = 0; row < rows; ++row) {
        int choice = best_choice[row];
        std::cout << choice << ' ' << cost[row][choice] << '\n';
    }
}
```

Output (choice index, minimum cost):

```text
0 5
1 2
2 7
```

`value(row,column)` supplies one table entry, and the result supplies the
column index to use for each row. Replace the table lookup with your own
cost calculation when the matrix is implicit.

This example's squared-distance table is also Monge, so SMAWK is available.
Use monotone minima when you have established only nondecreasing leftmost
optimal indices, without the stronger total-monotonicity guarantee needed by
SMAWK. Finding monotone indices on one sample is not a proof for all inputs.

## Interface

```cpp
template <class Value>
std::vector<int> monotone_row_argmin(
    int row_count,
    int column_count,
    Value value
);

template <class Value>
std::vector<int> monotone_row_argmax(
    int row_count,
    int column_count,
    Value value
);
```

`value(row, column)` returns one implicit matrix entry. The result stores the
optimal column for each row, choosing the leftmost optimum on ties.

Both functions also have convenience overloads accepting a rectangular
`std::vector<std::vector<T>>`.

`monotone_row_optima` is the generic overload accepting a strict comparator.

If there are no columns, every answer is `-1`.

## Requirements

The leftmost optimal columns under the chosen comparison must form a
nondecreasing sequence. The implementation does not verify this condition.

Unlike SMAWK, this function does not require every submatrix to preserve
monotonicity.

For anti-Monge minima, reverse columns and map the returned indices back,
as shown in the [SMAWK documentation](smawk.md). Without reversal, anti-Monge
does not provide the required direction. Callbacks must describe fixed entries;
this routine is not an online DP solver. See the [Monge guide](all.md) for
recurrence-to-matrix mapping and DP dependency rules.

## Complexity

For an `H` by `W` implicit matrix, the algorithm uses
$O((H + W)\log H)$ callback evaluations in the general case and $O(H)$
additional memory including the result and recursion stack.
