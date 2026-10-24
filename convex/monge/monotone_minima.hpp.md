---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: convex/all.hpp
    title: Convex All
  - icon: ':heavy_check_mark:'
    path: convex/monge/all.hpp
    title: Monge Optimization Guide
  - icon: ':heavy_check_mark:'
    path: convex/monge/divide_and_conquer_optimization.hpp
    title: Divide-and-Conquer DP Optimization
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_algorithms.test.cpp
    title: verify/convex/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_dp_optimization.test.cpp
    title: verify/convex/monge/monge_dp_optimization.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"convex/monge/monotone_minima.hpp\"\n\n\n\n#include <cassert>\n\
    #include <functional>\n#include <vector>\n\nnamespace m1une {\nnamespace convex\
    \ {\n\nnamespace monotone_minima_detail {\n\ntemplate <class Value, class Compare>\n\
    void solve(int row_left, int row_right, int column_left, int column_right,\n \
    \          const Value& value, const Compare& compare, std::vector<int>& answer)\
    \ {\n    if (row_left == row_right) return;\n    int row = (row_left + row_right)\
    \ / 2;\n    int best = column_left;\n    for (int column = column_left + 1; column\
    \ < column_right; column++) {\n        if (compare(value(row, column), value(row,\
    \ best))) best = column;\n    }\n    answer[row] = best;\n    solve(row_left,\
    \ row, column_left, best + 1, value, compare, answer);\n    solve(row + 1, row_right,\
    \ best, column_right, value, compare, answer);\n}\n\n}  // namespace monotone_minima_detail\n\
    \n// Fixed rectangular matrix; leftmost optimal columns must be nondecreasing.\n\
    // Returns column indices, or -1 when there are no columns. Not an online DP.\n\
    // Anti-Monge minima require reversing one axis before using this routine.\ntemplate\
    \ <class Value, class Compare = std::less<>>\nstd::vector<int> monotone_row_optima(int\
    \ row_count, int column_count, Value value,\n                                \
    \     Compare compare = Compare()) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    std::vector<int> answer(row_count, -1);\n    if (row_count == 0\
    \ || column_count == 0) return answer;\n    monotone_minima_detail::solve(0, row_count,\
    \ 0, column_count, value, compare, answer);\n    return answer;\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> monotone_row_argmin(int row_count, int column_count,\
    \ Value value) {\n    return monotone_row_optima(row_count, column_count, value,\
    \ std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int> monotone_row_argmax(int\
    \ row_count, int column_count, Value value) {\n    return monotone_row_optima(row_count,\
    \ column_count, value, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ monotone_row_argmin(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return monotone_row_argmin(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_MONOTONE_MINIMA_HPP\n#define M1UNE_CONVEX_MONGE_MONOTONE_MINIMA_HPP\
    \ 1\n\n#include <cassert>\n#include <functional>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace convex {\n\nnamespace monotone_minima_detail {\n\ntemplate\
    \ <class Value, class Compare>\nvoid solve(int row_left, int row_right, int column_left,\
    \ int column_right,\n           const Value& value, const Compare& compare, std::vector<int>&\
    \ answer) {\n    if (row_left == row_right) return;\n    int row = (row_left +\
    \ row_right) / 2;\n    int best = column_left;\n    for (int column = column_left\
    \ + 1; column < column_right; column++) {\n        if (compare(value(row, column),\
    \ value(row, best))) best = column;\n    }\n    answer[row] = best;\n    solve(row_left,\
    \ row, column_left, best + 1, value, compare, answer);\n    solve(row + 1, row_right,\
    \ best, column_right, value, compare, answer);\n}\n\n}  // namespace monotone_minima_detail\n\
    \n// Fixed rectangular matrix; leftmost optimal columns must be nondecreasing.\n\
    // Returns column indices, or -1 when there are no columns. Not an online DP.\n\
    // Anti-Monge minima require reversing one axis before using this routine.\ntemplate\
    \ <class Value, class Compare = std::less<>>\nstd::vector<int> monotone_row_optima(int\
    \ row_count, int column_count, Value value,\n                                \
    \     Compare compare = Compare()) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    std::vector<int> answer(row_count, -1);\n    if (row_count == 0\
    \ || column_count == 0) return answer;\n    monotone_minima_detail::solve(0, row_count,\
    \ 0, column_count, value, compare, answer);\n    return answer;\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> monotone_row_argmin(int row_count, int column_count,\
    \ Value value) {\n    return monotone_row_optima(row_count, column_count, value,\
    \ std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int> monotone_row_argmax(int\
    \ row_count, int column_count, Value value) {\n    return monotone_row_optima(row_count,\
    \ column_count, value, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ monotone_row_argmin(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return monotone_row_argmin(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n#endif  // M1UNE_CONVEX_MONGE_MONOTONE_MINIMA_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: convex/monge/monotone_minima.hpp
  requiredBy:
  - convex/monge/all.hpp
  - convex/monge/divide_and_conquer_optimization.hpp
  - convex/all.hpp
  timestamp: '2026-10-24 20:27:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
documentation_of: convex/monge/monotone_minima.hpp
layout: document
title: Monotone Minima
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
as shown in the [SMAWK documentation](https://m1une.github.io/m1une_library/convex/monge/smawk.hpp). Without reversal, anti-Monge
does not provide the required direction. Callbacks must describe fixed entries;
this routine is not an online DP solver. See the [Monge guide](https://m1une.github.io/m1une_library/convex/monge/all.hpp) for
recurrence-to-matrix mapping and DP dependency rules.

## Complexity

For an `H` by `W` implicit matrix, the algorithm uses
$O((H + W)\log H)$ callback evaluations in the general case and $O(H)$
additional memory including the result and recursion stack.
