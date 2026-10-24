---
title: SMAWK
documentation_of: ../../../convex/monge/smawk.hpp
---

## Overview

SMAWK finds an optimum in every row of an implicit totally monotone matrix.
The matrix is supplied as a callback, so the full rectangular matrix never
needs to be stored or evaluated.

The algorithm was introduced by Aggarwal, Klawe, Moran, Shor, and Wilber in
[Geometric applications of a matrix-searching algorithm](https://doi.org/10.1007/BF01840359).

For minima, total monotonicity means that the leftmost minimizing columns stay
nondecreasing after selecting any subset of rows and columns. Every Monge
matrix is totally monotone, so SMAWK is the standard linear-time row-minimum
primitive for Monge optimization.

All names are in `m1une::convex`.

See the [Monge guide](https://m1une.github.io/m1une_library/convex/monge/all.hpp) for algorithm selection, recurrence-to-matrix
mapping, and examples of previous-layer and forward DP.

## Worked example: replace a row-by-row search

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

SMAWK replaces that nested search with the following call:

```cpp
#include "convex/monge/smawk.hpp"
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
    auto best_choice = m1une::convex::smawk_row_argmin(rows, columns, value);
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

The three arguments are the number of rows, number of columns, and a function
that answers "what is the cost at this row and column?" The return value is
one **column index per row**, so you read the minimum value yourself.

Why is SMAWK applicable? This table has the form
`cost[row][column] = base[row] + 4*(row-column)^2`, where
`base = {5,2,7}`. Squared distance is Monge, and adding a row constant preserves
Monge. For your own cost rule, establish total monotonicity before using SMAWK;
an arbitrary cost table does not qualify.

For a large implicit matrix, keep the same call and replace
`cost[row][column]` in `value` with your formula or query. The callback must
return one fixed entry; SMAWK performs the search. With no columns, the
returned indices are `-1` and must be checked before accessing an array.

## Interface

```cpp
template <class Value>
std::vector<int> smawk_row_argmin(
    int row_count,
    int column_count,
    Value value
);

template <class Value>
std::vector<int> smawk_row_argmax(
    int row_count,
    int column_count,
    Value value
);
```

`value(row, column)` returns the matrix entry at that position. The result
contains the selected column for every row. Ties choose the leftmost optimum.

Explicit rectangular matrices have convenience overloads:

```cpp
template <class T>
std::vector<int> smawk_row_argmin(
    const std::vector<std::vector<T>>& matrix
);

template <class T>
std::vector<int> smawk_row_argmax(
    const std::vector<std::vector<T>>& matrix
);
```

The generic form accepts a strict comparator:

```cpp
template <class Value, class Compare = std::less<>>
std::vector<int> smawk_row_optima(
    int row_count,
    int column_count,
    Value value,
    Compare compare = Compare()
);
```

`compare(a, b)` must return whether `a` is strictly better than `b`.

If there are no columns, every answer is `-1`. If there are no rows, the result
is empty.

## Requirements

For `smawk_row_argmin`, the implicit matrix must be totally monotone for
leftmost minima. For `smawk_row_argmax`, it must be totally monotone under the
reversed comparison. The implementation does not verify this precondition.

The callback may return values by value or by reference. Values only need to
support the selected comparison.

Entries must remain fixed during the search. Rows can be evaluated out of
order; a callback reading unfinished entries from the DP being computed is
invalid. Use a forward-DP helper or finalize predecessor values first.

This API searches a full rectangle. Filling invalid cells of a triangular
or staircase matrix with infinity does not automatically preserve total
monotonicity. Prove the property for the padded matrix, or split transitions
into valid rectangles and handle boundary pairs separately.

## Minimizing an anti-Monge matrix

Reverse columns before calling the minimum routine:

```cpp
auto argmin = m1une::convex::smawk_row_argmin(H, W,
    [&](int row, int column) { return value(row, W - 1 - column); });
for (int row = 0; row < H; ++row) {
    if (argmin[row] != -1) argmin[row] = W - 1 - argmin[row];
}
```

The mapped indices choose the **rightmost** original minimum on ties.
Reversing one axis changes anti-Monge to Monge; transposing alone does not.
`smawk_row_argmax` still computes maxima and cannot replace this transformation.

## Complexity

SMAWK uses $O(H + W)$ callback evaluations and $O(H + W)$ additional memory for
an `H` by `W` matrix. This assumes each callback evaluation and comparison take
$O(1)$ time.
