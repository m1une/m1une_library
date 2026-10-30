---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: convex/all.hpp
    title: Convex All
  - icon: ':heavy_check_mark:'
    path: convex/monge/all.hpp
    title: Monge Matrix Primitives and Algorithm Guide
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_algorithms.test.cpp
    title: verify/convex/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_dp_optimization.test.cpp
    title: verify/convex/monge/monge_dp_optimization.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/ordered_matrix.test.cpp
    title: verify/convex/monge/ordered_matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"convex/monge/check.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <span>\n#include <vector>\n\nnamespace m1une {\nnamespace convex {\n\ntemplate\
    \ <class Value>\nbool is_monge(int row_count, int column_count, Value value) {\n\
    \    assert(row_count >= 0);\n    assert(column_count >= 0);\n    if (row_count\
    \ < 2 || column_count < 2) return true;\n    for (int row = 0; row + 1 < row_count;\
    \ row++) {\n        for (int column = 0; column + 1 < column_count; column++)\
    \ {\n            if (value(row, column) + value(row + 1, column + 1) >\n     \
    \           value(row, column + 1) + value(row + 1, column)) {\n             \
    \   return false;\n            }\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class Value>\nbool is_anti_monge(int row_count, int column_count, Value value)\
    \ {\n    return is_monge(row_count, column_count,\n        [&](int row, int column)\
    \ -> decltype(auto) {\n            return value(row, column_count - 1 - column);\n\
    \        });\n}\n\n// Check adjacent 2x2 inequalities in the supplied orders,\
    \ O(HW) time,\n// O(1) extra memory. Distinct nonnegative IDs; arithmetic must\
    \ not overflow.\ntemplate <class Value>\nbool is_monge(std::span<const int> rows,\
    \ std::span<const int> columns, Value value) {\n    return is_monge(int(rows.size()),\
    \ int(columns.size()),\n        [&](int row, int column) -> decltype(auto) {\n\
    \            return value(rows[row], columns[column]);\n        });\n}\n\ntemplate\
    \ <class Value>\nbool is_anti_monge(std::span<const int> rows, std::span<const\
    \ int> columns,\n                   Value value) {\n    return is_anti_monge(int(rows.size()),\
    \ int(columns.size()),\n        [&](int row, int column) -> decltype(auto) {\n\
    \            return value(rows[row], columns[column]);\n        });\n}\n\ntemplate\
    \ <class T>\nbool is_monge(const std::vector<std::vector<T>>& matrix) {\n    int\
    \ row_count = int(matrix.size());\n    int column_count = row_count == 0 ? 0 :\
    \ int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_monge(row_count, column_count,\n          \
    \          [&](int row, int column) -> const T& { return matrix[row][column];\
    \ });\n}\n\ntemplate <class T>\nbool is_anti_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_anti_monge(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_CHECK_HPP\n#define M1UNE_CONVEX_MONGE_CHECK_HPP\
    \ 1\n\n#include <cassert>\n#include <span>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace convex {\n\ntemplate <class Value>\nbool is_monge(int row_count,\
    \ int column_count, Value value) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    if (row_count < 2 || column_count < 2) return true;\n    for (int\
    \ row = 0; row + 1 < row_count; row++) {\n        for (int column = 0; column\
    \ + 1 < column_count; column++) {\n            if (value(row, column) + value(row\
    \ + 1, column + 1) >\n                value(row, column + 1) + value(row + 1,\
    \ column)) {\n                return false;\n            }\n        }\n    }\n\
    \    return true;\n}\n\ntemplate <class Value>\nbool is_anti_monge(int row_count,\
    \ int column_count, Value value) {\n    return is_monge(row_count, column_count,\n\
    \        [&](int row, int column) -> decltype(auto) {\n            return value(row,\
    \ column_count - 1 - column);\n        });\n}\n\n// Check adjacent 2x2 inequalities\
    \ in the supplied orders, O(HW) time,\n// O(1) extra memory. Distinct nonnegative\
    \ IDs; arithmetic must not overflow.\ntemplate <class Value>\nbool is_monge(std::span<const\
    \ int> rows, std::span<const int> columns, Value value) {\n    return is_monge(int(rows.size()),\
    \ int(columns.size()),\n        [&](int row, int column) -> decltype(auto) {\n\
    \            return value(rows[row], columns[column]);\n        });\n}\n\ntemplate\
    \ <class Value>\nbool is_anti_monge(std::span<const int> rows, std::span<const\
    \ int> columns,\n                   Value value) {\n    return is_anti_monge(int(rows.size()),\
    \ int(columns.size()),\n        [&](int row, int column) -> decltype(auto) {\n\
    \            return value(rows[row], columns[column]);\n        });\n}\n\ntemplate\
    \ <class T>\nbool is_monge(const std::vector<std::vector<T>>& matrix) {\n    int\
    \ row_count = int(matrix.size());\n    int column_count = row_count == 0 ? 0 :\
    \ int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_monge(row_count, column_count,\n          \
    \          [&](int row, int column) -> const T& { return matrix[row][column];\
    \ });\n}\n\ntemplate <class T>\nbool is_anti_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_anti_monge(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n#endif  // M1UNE_CONVEX_MONGE_CHECK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: convex/monge/check.hpp
  requiredBy:
  - convex/monge/all.hpp
  - convex/all.hpp
  timestamp: '2026-10-30 15:56:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/ordered_matrix.test.cpp
documentation_of: convex/monge/check.hpp
layout: document
title: Monge and Anti-Monge Checks
---

Check adjacent $2\times2$ inequalities of a complete rectangle. Monge means
$A(r,c)+A(r+1,c+1)\le A(r,c+1)+A(r+1,c)$; anti-Monge uses $\ge$.
For finite ordered arithmetic these local conditions imply all rectangle
inequalities by summation. Neither function checks total monotonicity alone.

All APIs use `m1une::convex`. `V` receives `(row,column)` and returns a finite
value supporting addition and comparison. Sums must fit in the value type;
NaNs and arithmetic with infinity are not supported. These are offline
checks and do not mutate their inputs. No optimum is returned, so ties are
irrelevant and equality satisfies both properties.

## Interface

| Signature | Time | Extra memory |
| --- | --- | --- |
| `template<class V> bool is_monge(int row_count, int column_count, V value)` | $O(HW)$ | $O(1)$ |
| `template<class V> bool is_anti_monge(int row_count, int column_count, V value)` | $O(HW)$ | $O(1)$ |
| `template<class V> bool is_monge(std::span<const int> rows, std::span<const int> columns, V value)` | $O(HW)$ | $O(1)$ |
| `template<class V> bool is_anti_monge(std::span<const int> rows, std::span<const int> columns, V value)` | $O(HW)$ | $O(1)$ |
| `template<class T> bool is_monge(const std::vector<std::vector<T>>& matrix)` | $O(H+HW)$ | $O(1)$ |
| `template<class T> bool is_anti_monge(const std::vector<std::vector<T>>& matrix)` | $O(H+HW)$ | $O(1)$ |

Dimensions must be nonnegative; dense overloads assert rectangular shape.
A dimension below two makes the inequality vacuous and returns `true`.
The ordered forms check `value(rows[r],columns[c])`, with distinct nonnegative
IDs in each list. Anti-Monge is implemented through reversed virtual column
order and is directly callable without building a reverse permutation.

```cpp
#include "convex/monge/check.hpp"
#include <cassert>

int main() {
    auto squared_gap = [](int r, int c) { return (r-c)*(r-c); };
    assert(m1une::convex::is_monge(4, 6, squared_gap));
    assert(m1une::convex::is_anti_monge(4, 6,
        [&](int r, int c) { return -squared_gap(r,c); }));
}
```
