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
  bundledCode: "#line 1 \"convex/monge/check.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class Value>\n\
    bool is_monge(int row_count, int column_count, Value value) {\n    assert(row_count\
    \ >= 0);\n    assert(column_count >= 0);\n    for (int row = 0; row + 1 < row_count;\
    \ row++) {\n        for (int column = 0; column + 1 < column_count; column++)\
    \ {\n            if (value(row, column) + value(row + 1, column + 1) >\n     \
    \           value(row, column + 1) + value(row + 1, column)) {\n             \
    \   return false;\n            }\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class Value>\nbool is_anti_monge(int row_count, int column_count, Value value)\
    \ {\n    assert(row_count >= 0);\n    assert(column_count >= 0);\n    for (int\
    \ row = 0; row + 1 < row_count; row++) {\n        for (int column = 0; column\
    \ + 1 < column_count; column++) {\n            if (value(row, column) + value(row\
    \ + 1, column + 1) <\n                value(row, column + 1) + value(row + 1,\
    \ column)) {\n                return false;\n            }\n        }\n    }\n\
    \    return true;\n}\n\ntemplate <class T>\nbool is_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_monge(row_count, column_count,\n          \
    \          [&](int row, int column) -> const T& { return matrix[row][column];\
    \ });\n}\n\ntemplate <class T>\nbool is_anti_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_anti_monge(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_CHECK_HPP\n#define M1UNE_CONVEX_MONGE_CHECK_HPP\
    \ 1\n\n#include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace convex\
    \ {\n\ntemplate <class Value>\nbool is_monge(int row_count, int column_count,\
    \ Value value) {\n    assert(row_count >= 0);\n    assert(column_count >= 0);\n\
    \    for (int row = 0; row + 1 < row_count; row++) {\n        for (int column\
    \ = 0; column + 1 < column_count; column++) {\n            if (value(row, column)\
    \ + value(row + 1, column + 1) >\n                value(row, column + 1) + value(row\
    \ + 1, column)) {\n                return false;\n            }\n        }\n \
    \   }\n    return true;\n}\n\ntemplate <class Value>\nbool is_anti_monge(int row_count,\
    \ int column_count, Value value) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    for (int row = 0; row + 1 < row_count; row++) {\n        for (int\
    \ column = 0; column + 1 < column_count; column++) {\n            if (value(row,\
    \ column) + value(row + 1, column + 1) <\n                value(row, column +\
    \ 1) + value(row + 1, column)) {\n                return false;\n            }\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nbool is_monge(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return is_monge(row_count,\
    \ column_count,\n                    [&](int row, int column) -> const T& { return\
    \ matrix[row][column]; });\n}\n\ntemplate <class T>\nbool is_anti_monge(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return is_anti_monge(\n\
    \        row_count, column_count,\n        [&](int row, int column) -> const T&\
    \ { return matrix[row][column]; });\n}\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_CONVEX_MONGE_CHECK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: convex/monge/check.hpp
  requiredBy:
  - convex/monge/all.hpp
  - convex/all.hpp
  timestamp: '2026-07-07 18:38:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
documentation_of: convex/monge/check.hpp
layout: document
title: Monge Checks
---

## Overview

This header checks the Monge or anti-Monge quadrangle inequality.

An `H` by `W` matrix `A` is Monge when

$$
A[i][j] + A[k][l] \le A[i][l] + A[k][j]
$$

for every `i < k` and `j < l`. It is enough to test adjacent rows and columns,
which gives an $O(HW)$ checker.

Anti-Monge reverses the inequality. It supports row maxima directly, or row
minima after reversing one axis; see [SMAWK](https://m1une.github.io/m1une_library/convex/monge/smawk.hpp). Transposition alone
does not reverse the inequality. These checks require a full rectangle:
restrict an interval-cost callback to valid ranges rather than querying
undefined intervals. See the [Monge guide](https://m1une.github.io/m1une_library/convex/monge/all.hpp).

## Worked example: check the matrix you intend to search

Use this checker on small instances while deriving a cost model. For example,
the following table is the same three-request, four-choice table used in the
[SMAWK example](https://m1une.github.io/m1une_library/convex/monge/smawk.hpp):

```cpp
#include "convex/monge/check.hpp"
#include <cassert>
#include <vector>

int main() {
    std::vector<std::vector<long long>> cost = {
        {5, 9, 21, 41},
        {6, 2, 6, 18},
        {23, 11, 7, 11}
    };
    assert(m1une::convex::is_monge(cost));
    assert(!m1une::convex::is_anti_monge(cost));

    // Negating every entry reverses the inequality.
    for (auto& row : cost) {
        for (auto& entry : row) entry = -entry;
    }
    assert(m1une::convex::is_anti_monge(cost));

    // For an implicit matrix, pass its dimensions and one-entry callback.
    auto value = [](int row, int column) {
        long long gap = row - column;
        return gap * gap;
    };
    assert(m1une::convex::is_monge(3, 4, value));
}
```

Both overloads return a boolean. For example, the first adjacent check is
`5+2 <= 9+6`, and the remaining adjacent checks must also pass.
A successful check justifies the property for this finite table. To use an
optimization for arbitrary problem inputs, prove the inequality for the cost
rule too. These functions do not check the weaker condition of monotone
argmins, and they do not compute any minima.

## Interface

Implicit matrices:

```cpp
template <class Value>
bool is_monge(int row_count, int column_count, Value value);

template <class Value>
bool is_anti_monge(int row_count, int column_count, Value value);
```

Explicit rectangular matrices:

```cpp
template <class T>
bool is_monge(const std::vector<std::vector<T>>& matrix);

template <class T>
bool is_anti_monge(const std::vector<std::vector<T>>& matrix);
```

Empty matrices and matrices with fewer than two rows or columns satisfy both
properties vacuously.

The element type must support addition and comparison. Intermediate sums must
fit in the element type.

## Complexity

$O(HW)$ time and $O(1)$ additional memory.
