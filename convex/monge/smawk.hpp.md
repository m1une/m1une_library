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
    path: convex/monge/anti_monge_shortest_path.hpp
    title: Anti-Monge DAG Shortest Paths
  - icon: ':heavy_check_mark:'
    path: convex/monge/min_plus_convolution.hpp
    title: Structured Min-Plus and Max-Plus Convolution
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/anti_monge_shortest_path.test.cpp
    title: verify/convex/monge/anti_monge_shortest_path.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/max_plus_convolution_concave_arbitrary.test.cpp
    title: verify/convex/monge/max_plus_convolution_concave_arbitrary.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/max_plus_convolution_concave_concave.test.cpp
    title: verify/convex/monge/max_plus_convolution_concave_concave.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/min_plus_convolution_convex_arbitrary.test.cpp
    title: verify/convex/monge/min_plus_convolution_convex_arbitrary.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/min_plus_convolution_convex_convex.test.cpp
    title: verify/convex/monge/min_plus_convolution_convex_convex.test.cpp
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
  bundledCode: "#line 1 \"convex/monge/smawk.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <functional>\n#include <numeric>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ convex {\n\nnamespace smawk_detail {\n\ntemplate <class Select>\nvoid solve(const\
    \ std::vector<int>& rows, const std::vector<int>& columns,\n           const Select&\
    \ select, std::vector<int>& answer) {\n    if (rows.empty()) return;\n\n    std::vector<int>\
    \ reduced;\n    reduced.reserve(columns.size());\n    for (int column : columns)\
    \ {\n        while (!reduced.empty()) {\n            int row = rows[int(reduced.size())\
    \ - 1];\n            if (!select(row, reduced.back(), column)) break;\n      \
    \      reduced.pop_back();\n        }\n        if (reduced.size() < rows.size())\
    \ reduced.push_back(column);\n    }\n\n    std::vector<int> odd_rows;\n    odd_rows.reserve(rows.size()\
    \ / 2);\n    for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);\n\
    \    solve(odd_rows, reduced, select, answer);\n\n    int left = 0;\n    int right\
    \ = 0;\n    for (int i = 0; i < int(rows.size()); i += 2) {\n        if (i + 1\
    \ < int(rows.size())) {\n            while (reduced[right] != answer[rows[i +\
    \ 1]]) right++;\n        } else {\n            right = int(reduced.size()) - 1;\n\
    \        }\n\n        int best = left;\n        for (int j = left + 1; j <= right;\
    \ j++) {\n            if (select(rows[i], reduced[best], reduced[j])) {\n    \
    \            best = j;\n            }\n        }\n        answer[rows[i]] = reduced[best];\n\
    \        left = right;\n    }\n}\n\ntemplate <class Select>\nstd::vector<int>\
    \ row_optima(int row_count, int column_count, const Select& select) {\n    std::vector<int>\
    \ answer(row_count, -1);\n    if (row_count == 0 || column_count == 0) return\
    \ answer;\n\n    std::vector<int> rows(row_count), columns(column_count);\n  \
    \  std::iota(rows.begin(), rows.end(), 0);\n    std::iota(columns.begin(), columns.end(),\
    \ 0);\n    solve(rows, columns, select, answer);\n    return answer;\n}\n\n} \
    \ // namespace smawk_detail\n\n// Search a fixed H x W rectangle, returning column\
    \ indices (leftmost on ties).\n// Requires total monotonicity under Compare; Monge\
    \ suffices for minima.\n// For anti-Monge minima, reverse columns in value and\
    \ map indices back.\n// O(H + W) evaluations; callbacks may be queried out of\
    \ row order.\ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int>\
    \ smawk_row_optima(int row_count, int column_count, Value value,\n           \
    \                       Compare compare = Compare()) {\n    assert(row_count >=\
    \ 0);\n    assert(column_count >= 0);\n    return smawk_detail::row_optima(\n\
    \        row_count, column_count,\n        [&](int row, int current, int candidate)\
    \ {\n            return compare(value(row, candidate), value(row, current));\n\
    \        });\n}\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmin(int\
    \ row_count, int column_count, Value value) {\n    return smawk_row_optima(row_count,\
    \ column_count, value, std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int>\
    \ smawk_row_argmax(int row_count, int column_count, Value value) {\n    return\
    \ smawk_row_optima(row_count, column_count, value, std::greater<>());\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmin(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_SMAWK_HPP\n#define M1UNE_CONVEX_MONGE_SMAWK_HPP\
    \ 1\n\n#include <cassert>\n#include <functional>\n#include <numeric>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace convex {\n\nnamespace smawk_detail\
    \ {\n\ntemplate <class Select>\nvoid solve(const std::vector<int>& rows, const\
    \ std::vector<int>& columns,\n           const Select& select, std::vector<int>&\
    \ answer) {\n    if (rows.empty()) return;\n\n    std::vector<int> reduced;\n\
    \    reduced.reserve(columns.size());\n    for (int column : columns) {\n    \
    \    while (!reduced.empty()) {\n            int row = rows[int(reduced.size())\
    \ - 1];\n            if (!select(row, reduced.back(), column)) break;\n      \
    \      reduced.pop_back();\n        }\n        if (reduced.size() < rows.size())\
    \ reduced.push_back(column);\n    }\n\n    std::vector<int> odd_rows;\n    odd_rows.reserve(rows.size()\
    \ / 2);\n    for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);\n\
    \    solve(odd_rows, reduced, select, answer);\n\n    int left = 0;\n    int right\
    \ = 0;\n    for (int i = 0; i < int(rows.size()); i += 2) {\n        if (i + 1\
    \ < int(rows.size())) {\n            while (reduced[right] != answer[rows[i +\
    \ 1]]) right++;\n        } else {\n            right = int(reduced.size()) - 1;\n\
    \        }\n\n        int best = left;\n        for (int j = left + 1; j <= right;\
    \ j++) {\n            if (select(rows[i], reduced[best], reduced[j])) {\n    \
    \            best = j;\n            }\n        }\n        answer[rows[i]] = reduced[best];\n\
    \        left = right;\n    }\n}\n\ntemplate <class Select>\nstd::vector<int>\
    \ row_optima(int row_count, int column_count, const Select& select) {\n    std::vector<int>\
    \ answer(row_count, -1);\n    if (row_count == 0 || column_count == 0) return\
    \ answer;\n\n    std::vector<int> rows(row_count), columns(column_count);\n  \
    \  std::iota(rows.begin(), rows.end(), 0);\n    std::iota(columns.begin(), columns.end(),\
    \ 0);\n    solve(rows, columns, select, answer);\n    return answer;\n}\n\n} \
    \ // namespace smawk_detail\n\n// Search a fixed H x W rectangle, returning column\
    \ indices (leftmost on ties).\n// Requires total monotonicity under Compare; Monge\
    \ suffices for minima.\n// For anti-Monge minima, reverse columns in value and\
    \ map indices back.\n// O(H + W) evaluations; callbacks may be queried out of\
    \ row order.\ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int>\
    \ smawk_row_optima(int row_count, int column_count, Value value,\n           \
    \                       Compare compare = Compare()) {\n    assert(row_count >=\
    \ 0);\n    assert(column_count >= 0);\n    return smawk_detail::row_optima(\n\
    \        row_count, column_count,\n        [&](int row, int current, int candidate)\
    \ {\n            return compare(value(row, candidate), value(row, current));\n\
    \        });\n}\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmin(int\
    \ row_count, int column_count, Value value) {\n    return smawk_row_optima(row_count,\
    \ column_count, value, std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int>\
    \ smawk_row_argmax(int row_count, int column_count, Value value) {\n    return\
    \ smawk_row_optima(row_count, column_count, value, std::greater<>());\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmin(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n#endif  // M1UNE_CONVEX_MONGE_SMAWK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: convex/monge/smawk.hpp
  requiredBy:
  - convex/monge/anti_monge_shortest_path.hpp
  - convex/monge/min_plus_convolution.hpp
  - convex/monge/all.hpp
  - convex/all.hpp
  timestamp: '2026-10-24 20:27:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/max_plus_convolution_concave_arbitrary.test.cpp
  - verify/convex/monge/max_plus_convolution_concave_concave.test.cpp
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/anti_monge_shortest_path.test.cpp
  - verify/convex/monge/min_plus_convolution_convex_arbitrary.test.cpp
  - verify/convex/monge/min_plus_convolution_convex_convex.test.cpp
documentation_of: convex/monge/smawk.hpp
layout: document
title: SMAWK
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

See the [Monge guide](all.md) for algorithm selection, recurrence-to-matrix
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
