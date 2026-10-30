---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: convex/all.hpp
    title: Convex All
  - icon: ':heavy_check_mark:'
    path: convex/all.hpp
    title: Convex All
  - icon: ':heavy_check_mark:'
    path: convex/monge/all.hpp
    title: Monge Matrix Primitives and Algorithm Guide
  - icon: ':heavy_check_mark:'
    path: convex/monge_transition.hpp
    title: Finalized-Layer Matrix Transitions
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_algorithms.test.cpp
    title: verify/convex/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_algorithms.test.cpp
    title: verify/convex/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_dp_optimization.test.cpp
    title: verify/convex/monge/monge_dp_optimization.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_dp_optimization.test.cpp
    title: verify/convex/monge/monge_dp_optimization.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/ordered_matrix.test.cpp
    title: verify/convex/monge/ordered_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/ordered_matrix.test.cpp
    title: verify/convex/monge/ordered_matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"convex/monge/monotone_minima.hpp\"\n\n\n\n#include <cassert>\n\
    #include <functional>\n#include <span>\n#include <vector>\n\nnamespace m1une {\n\
    namespace convex {\n\nnamespace monotone_minima_detail {\n\ntemplate <class Value,\
    \ class Compare>\nvoid solve(int row_left, int row_right, int column_left, int\
    \ column_right,\n           const Value& value, const Compare& compare, std::vector<int>&\
    \ answer) {\n    if (row_left == row_right) return;\n    int row = (row_left +\
    \ row_right) / 2;\n    int best = column_left;\n    for (int column = column_left\
    \ + 1; column < column_right; column++) {\n        if (compare(value(row, column),\
    \ value(row, best))) best = column;\n    }\n    answer[row] = best;\n    solve(row_left,\
    \ row, column_left, best + 1, value, compare, answer);\n    solve(row + 1, row_right,\
    \ best, column_right, value, compare, answer);\n}\n\n}  // namespace monotone_minima_detail\n\
    \n// Fixed rectangular matrix; leftmost optimal columns must be nondecreasing.\n\
    // Returns column indices, or -1 when there are no columns. Not an online DP.\n\
    // O(H + W log(H+1)) time, O(H + log(H+1)) memory.\ntemplate <class Value, class\
    \ Compare = std::less<>>\nstd::vector<int> monotone_row_optima(int row_count,\
    \ int column_count, Value value,\n                                     Compare\
    \ compare = Compare()) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    std::vector<int> answer(row_count, -1);\n    if (row_count == 0\
    \ || column_count == 0) return answer;\n    monotone_minima_detail::solve(0, row_count,\
    \ 0, column_count, value, compare, answer);\n    return answer;\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> monotone_row_argmin(int row_count, int column_count,\
    \ Value value) {\n    return monotone_row_optima(row_count, column_count, value,\
    \ std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int> monotone_row_argmax(int\
    \ row_count, int column_count, Value value) {\n    return monotone_row_optima(row_count,\
    \ column_count, value, std::greater<>());\n}\n\n// Ordered matrix value(rows[r],\
    \ columns[c]); return original column IDs in\n// row list order. Leftmost means\
    \ first in columns. IDs are distinct/nonnegative.\ntemplate <class Value, class\
    \ Compare = std::less<>>\nstd::vector<int> monotone_row_optima(std::span<const\
    \ int> rows,\n                                     std::span<const int> columns,\
    \ Value value,\n                                     Compare compare = Compare())\
    \ {\n    auto answer = monotone_row_optima(int(rows.size()), int(columns.size()),\n\
    \        [&](int row, int column) -> decltype(auto) {\n            return value(rows[row],\
    \ columns[column]);\n        }, compare);\n    for (int& column : answer) if (column\
    \ != -1) column = columns[column];\n    return answer;\n}\n\ntemplate <class Value>\n\
    std::vector<int> monotone_row_argmin(std::span<const int> rows,\n            \
    \                         std::span<const int> columns, Value value) {\n    return\
    \ monotone_row_optima(rows, columns, value, std::less<>());\n}\n\ntemplate <class\
    \ Value>\nstd::vector<int> monotone_row_argmax(std::span<const int> rows,\n  \
    \                                   std::span<const int> columns, Value value)\
    \ {\n    return monotone_row_optima(rows, columns, value, std::greater<>());\n\
    }\n\ntemplate <class T>\nstd::vector<int> monotone_row_argmin(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmin(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\ntemplate <class T>\nstd::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_MONOTONE_MINIMA_HPP\n#define M1UNE_CONVEX_MONGE_MONOTONE_MINIMA_HPP\
    \ 1\n\n#include <cassert>\n#include <functional>\n#include <span>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace convex {\n\nnamespace monotone_minima_detail {\n\
    \ntemplate <class Value, class Compare>\nvoid solve(int row_left, int row_right,\
    \ int column_left, int column_right,\n           const Value& value, const Compare&\
    \ compare, std::vector<int>& answer) {\n    if (row_left == row_right) return;\n\
    \    int row = (row_left + row_right) / 2;\n    int best = column_left;\n    for\
    \ (int column = column_left + 1; column < column_right; column++) {\n        if\
    \ (compare(value(row, column), value(row, best))) best = column;\n    }\n    answer[row]\
    \ = best;\n    solve(row_left, row, column_left, best + 1, value, compare, answer);\n\
    \    solve(row + 1, row_right, best, column_right, value, compare, answer);\n\
    }\n\n}  // namespace monotone_minima_detail\n\n// Fixed rectangular matrix; leftmost\
    \ optimal columns must be nondecreasing.\n// Returns column indices, or -1 when\
    \ there are no columns. Not an online DP.\n// O(H + W log(H+1)) time, O(H + log(H+1))\
    \ memory.\ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int>\
    \ monotone_row_optima(int row_count, int column_count, Value value,\n        \
    \                             Compare compare = Compare()) {\n    assert(row_count\
    \ >= 0);\n    assert(column_count >= 0);\n    std::vector<int> answer(row_count,\
    \ -1);\n    if (row_count == 0 || column_count == 0) return answer;\n    monotone_minima_detail::solve(0,\
    \ row_count, 0, column_count, value, compare, answer);\n    return answer;\n}\n\
    \ntemplate <class Value>\nstd::vector<int> monotone_row_argmin(int row_count,\
    \ int column_count, Value value) {\n    return monotone_row_optima(row_count,\
    \ column_count, value, std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int>\
    \ monotone_row_argmax(int row_count, int column_count, Value value) {\n    return\
    \ monotone_row_optima(row_count, column_count, value, std::greater<>());\n}\n\n\
    // Ordered matrix value(rows[r], columns[c]); return original column IDs in\n\
    // row list order. Leftmost means first in columns. IDs are distinct/nonnegative.\n\
    template <class Value, class Compare = std::less<>>\nstd::vector<int> monotone_row_optima(std::span<const\
    \ int> rows,\n                                     std::span<const int> columns,\
    \ Value value,\n                                     Compare compare = Compare())\
    \ {\n    auto answer = monotone_row_optima(int(rows.size()), int(columns.size()),\n\
    \        [&](int row, int column) -> decltype(auto) {\n            return value(rows[row],\
    \ columns[column]);\n        }, compare);\n    for (int& column : answer) if (column\
    \ != -1) column = columns[column];\n    return answer;\n}\n\ntemplate <class Value>\n\
    std::vector<int> monotone_row_argmin(std::span<const int> rows,\n            \
    \                         std::span<const int> columns, Value value) {\n    return\
    \ monotone_row_optima(rows, columns, value, std::less<>());\n}\n\ntemplate <class\
    \ Value>\nstd::vector<int> monotone_row_argmax(std::span<const int> rows,\n  \
    \                                   std::span<const int> columns, Value value)\
    \ {\n    return monotone_row_optima(rows, columns, value, std::greater<>());\n\
    }\n\ntemplate <class T>\nstd::vector<int> monotone_row_argmin(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmin(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\ntemplate <class T>\nstd::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>&\
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
  - convex/monge_transition.hpp
  - convex/all.hpp
  - convex/all.hpp
  timestamp: '2026-10-30 15:56:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/ordered_matrix.test.cpp
  - verify/convex/monge/ordered_matrix.test.cpp
documentation_of: convex/monge/monotone_minima.hpp
layout: document
title: Monotone Matrix Minima
---

Search a fixed complete rectangle whose **leftmost optimum positions are
nondecreasing with row position**. Only this whole-matrix property is needed;
total monotonicity and Monge are stronger sufficient conditions. The callback
must return fixed entries; this routine does not compute an online recurrence.

Use `m1une::convex`. `compare(a,b)` is strict: `a` is better than `b`.
For minima use `<`, for maxima use `>`. Ties select the first column in the
search order. Ordered calls search `value(rows[r],columns[c])` and return
original column IDs compactly in row list order. Lists contain distinct
nonnegative IDs. Empty columns yield `-1` for each row; empty rows yield no
answers. Dense matrix overloads assert rectangular shape. Dimensions must be
nonnegative. The matrix and lists are not changed.

## Interface

| Signature | Time | Memory including answers |
| --- | --- | --- |
| `template<class V, class C = std::less<>> std::vector<int> monotone_row_optima(int row_count, int column_count, V value, C compare = C())` | $O(H+W\log(H+1))$ | $O(H+\log(H+1))$ |
| `template<class V, class C = std::less<>> std::vector<int> monotone_row_optima(std::span<const int> rows, std::span<const int> columns, V value, C compare = C())` | same | same |
| `template<class V> std::vector<int> monotone_row_argmin(int row_count, int column_count, V value)` | same | same |
| `template<class V> std::vector<int> monotone_row_argmin(std::span<const int> rows, std::span<const int> columns, V value)` | same | same |
| `template<class V> std::vector<int> monotone_row_argmax(int row_count, int column_count, V value)` | same | same |
| `template<class V> std::vector<int> monotone_row_argmax(std::span<const int> rows, std::span<const int> columns, V value)` | same | same |
| `template<class T> std::vector<int> monotone_row_argmin(const std::vector<std::vector<T>>& matrix)` | same | same |
| `template<class T> std::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>& matrix)` | same | same |

Bounds assume constant-time entry evaluation and comparison. A middle row is
scanned, then the rows above/below search only the feasible column ranges.
For totally monotone matrices, [SMAWK](https://m1une.github.io/m1une_library/convex/monge/smawk.hpp) gives a linear bound.

```cpp
#include "convex/monge/monotone_minima.hpp"
#include <cassert>
#include <vector>

int main() {
    auto answer = m1une::convex::monotone_row_argmin(4, 5, [](int r, int c) {
        return (r-c)*(r-c);
    });
    assert(answer == std::vector<int>({0, 1, 2, 3}));
}
```

The finalized-layer wrapper is named
[`monotone_transition`](https://m1une.github.io/m1une_library/convex/monge_transition.hpp)
after its actual precondition; the divide-and-conquer implementation is internal.
