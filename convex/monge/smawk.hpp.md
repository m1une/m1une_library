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
    path: convex/min_plus_convolution.hpp
    title: Structured Min-Plus and Max-Plus Convolution
  - icon: ':heavy_check_mark:'
    path: convex/monge/all.hpp
    title: Monge Matrix Primitives and Algorithm Guide
  - icon: ':heavy_check_mark:'
    path: convex/monge_shortest_path.hpp
    title: Monge and Anti-Monge Forward DAG Shortest Paths
  - icon: ':heavy_check_mark:'
    path: convex/monge_transition.hpp
    title: Finalized-Layer Matrix Transitions
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/max_plus_convolution_concave_arbitrary.test.cpp
    title: verify/convex/max_plus_convolution_concave_arbitrary.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/max_plus_convolution_concave_concave.test.cpp
    title: verify/convex/max_plus_convolution_concave_concave.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/min_plus_convolution_convex_arbitrary.test.cpp
    title: verify/convex/min_plus_convolution_convex_arbitrary.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/min_plus_convolution_convex_convex.test.cpp
    title: verify/convex/min_plus_convolution_convex_convex.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/anti_monge_shortest_path.test.cpp
    title: verify/convex/monge/anti_monge_shortest_path.test.cpp
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
    path: verify/convex/monge/monge_shortest_path.test.cpp
    title: verify/convex/monge/monge_shortest_path.test.cpp
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
  bundledCode: "#line 1 \"convex/monge/smawk.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <functional>\n#include <numeric>\n#include <span>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace convex {\n\nnamespace smawk_detail {\n\ntemplate <class Select>\n\
    void solve(const std::vector<int>& rows, const std::vector<int>& columns,\n  \
    \         const Select& select, std::vector<int>& answer) {\n    if (rows.empty())\
    \ return;\n\n    std::vector<int> reduced;\n    reduced.reserve(columns.size());\n\
    \    for (int column : columns) {\n        while (!reduced.empty()) {\n      \
    \      int row = rows[int(reduced.size()) - 1];\n            if (!select(row,\
    \ reduced.back(), column)) break;\n            reduced.pop_back();\n        }\n\
    \        if (reduced.size() < rows.size()) reduced.push_back(column);\n    }\n\
    \n    std::vector<int> odd_rows;\n    odd_rows.reserve(rows.size() / 2);\n   \
    \ for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);\n\
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
    \ // namespace smawk_detail\n\n// Comparison-oracle SMAWK. prefer(row, current,\
    \ candidate) says whether to\n// replace current. The induced ordered matrix must\
    \ be totally monotone with\n// this tie rule. This also permits symbolic invalid\
    \ entries without sentinels.\n// O(H + W) oracle calls and memory. Entries must\
    \ be fixed (offline search).\ntemplate <class Prefer>\nstd::vector<int> smawk_row_select(int\
    \ row_count, int column_count, Prefer prefer) {\n    assert(row_count >= 0);\n\
    \    assert(column_count >= 0);\n    return smawk_detail::row_optima(row_count,\
    \ column_count, prefer);\n}\n\n// Search value(rows[r], columns[c]); answers are\
    \ original column IDs, in row\n// list order. Lists contain distinct nonnegative\
    \ IDs; prefer defines the tie\n// rule with respect to the supplied order.\ntemplate\
    \ <class Prefer>\nstd::vector<int> smawk_row_select(std::span<const int> rows,\n\
    \                                  std::span<const int> columns, Prefer prefer)\
    \ {\n    auto answer = smawk_row_select(int(rows.size()), int(columns.size()),\n\
    \        [&](int row, int current, int candidate) {\n            return prefer(rows[row],\
    \ columns[current], columns[candidate]);\n        });\n    for (int& column :\
    \ answer) if (column != -1) column = columns[column];\n    return answer;\n}\n\
    \n// Fixed rectangle, leftmost on ties. Requires total monotonicity for leftmost\n\
    // optima under Compare (Monge suffices for minima). O(H + W) time and memory.\n\
    // Callback evaluations may be out of row order; this is not an online DP.\ntemplate\
    \ <class Value, class Compare = std::less<>>\nstd::vector<int> smawk_row_optima(int\
    \ row_count, int column_count, Value value,\n                                \
    \  Compare compare = Compare()) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    return smawk_row_select(\n        row_count, column_count,\n   \
    \     [&](int row, int current, int candidate) {\n            return compare(value(row,\
    \ candidate), value(row, current));\n        });\n}\n\ntemplate <class Value>\n\
    std::vector<int> smawk_row_argmin(int row_count, int column_count, Value value)\
    \ {\n    return smawk_row_optima(row_count, column_count, value, std::less<>());\n\
    }\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmax(int row_count,\
    \ int column_count, Value value) {\n    return smawk_row_optima(row_count, column_count,\
    \ value, std::greater<>());\n}\n\n// Ordered variants use supplied positions for\
    \ total monotonicity and ties.\ntemplate <class Value, class Compare = std::less<>>\n\
    std::vector<int> smawk_row_optima(std::span<const int> rows,\n               \
    \                   std::span<const int> columns, Value value,\n             \
    \                     Compare compare = Compare()) {\n    return smawk_row_select(rows,\
    \ columns,\n        [&](int row, int current, int candidate) {\n            return\
    \ compare(value(row, candidate), value(row, current));\n        });\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> smawk_row_argmin(std::span<const int> rows,\n\
    \                                  std::span<const int> columns, Value value)\
    \ {\n    return smawk_row_optima(rows, columns, value, std::less<>());\n}\n\n\
    template <class Value>\nstd::vector<int> smawk_row_argmax(std::span<const int>\
    \ rows,\n                                  std::span<const int> columns, Value\
    \ value) {\n    return smawk_row_optima(rows, columns, value, std::greater<>());\n\
    }\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>&\
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
    \ <span>\n#include <vector>\n\nnamespace m1une {\nnamespace convex {\n\nnamespace\
    \ smawk_detail {\n\ntemplate <class Select>\nvoid solve(const std::vector<int>&\
    \ rows, const std::vector<int>& columns,\n           const Select& select, std::vector<int>&\
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
    \ // namespace smawk_detail\n\n// Comparison-oracle SMAWK. prefer(row, current,\
    \ candidate) says whether to\n// replace current. The induced ordered matrix must\
    \ be totally monotone with\n// this tie rule. This also permits symbolic invalid\
    \ entries without sentinels.\n// O(H + W) oracle calls and memory. Entries must\
    \ be fixed (offline search).\ntemplate <class Prefer>\nstd::vector<int> smawk_row_select(int\
    \ row_count, int column_count, Prefer prefer) {\n    assert(row_count >= 0);\n\
    \    assert(column_count >= 0);\n    return smawk_detail::row_optima(row_count,\
    \ column_count, prefer);\n}\n\n// Search value(rows[r], columns[c]); answers are\
    \ original column IDs, in row\n// list order. Lists contain distinct nonnegative\
    \ IDs; prefer defines the tie\n// rule with respect to the supplied order.\ntemplate\
    \ <class Prefer>\nstd::vector<int> smawk_row_select(std::span<const int> rows,\n\
    \                                  std::span<const int> columns, Prefer prefer)\
    \ {\n    auto answer = smawk_row_select(int(rows.size()), int(columns.size()),\n\
    \        [&](int row, int current, int candidate) {\n            return prefer(rows[row],\
    \ columns[current], columns[candidate]);\n        });\n    for (int& column :\
    \ answer) if (column != -1) column = columns[column];\n    return answer;\n}\n\
    \n// Fixed rectangle, leftmost on ties. Requires total monotonicity for leftmost\n\
    // optima under Compare (Monge suffices for minima). O(H + W) time and memory.\n\
    // Callback evaluations may be out of row order; this is not an online DP.\ntemplate\
    \ <class Value, class Compare = std::less<>>\nstd::vector<int> smawk_row_optima(int\
    \ row_count, int column_count, Value value,\n                                \
    \  Compare compare = Compare()) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    return smawk_row_select(\n        row_count, column_count,\n   \
    \     [&](int row, int current, int candidate) {\n            return compare(value(row,\
    \ candidate), value(row, current));\n        });\n}\n\ntemplate <class Value>\n\
    std::vector<int> smawk_row_argmin(int row_count, int column_count, Value value)\
    \ {\n    return smawk_row_optima(row_count, column_count, value, std::less<>());\n\
    }\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmax(int row_count,\
    \ int column_count, Value value) {\n    return smawk_row_optima(row_count, column_count,\
    \ value, std::greater<>());\n}\n\n// Ordered variants use supplied positions for\
    \ total monotonicity and ties.\ntemplate <class Value, class Compare = std::less<>>\n\
    std::vector<int> smawk_row_optima(std::span<const int> rows,\n               \
    \                   std::span<const int> columns, Value value,\n             \
    \                     Compare compare = Compare()) {\n    return smawk_row_select(rows,\
    \ columns,\n        [&](int row, int current, int candidate) {\n            return\
    \ compare(value(row, candidate), value(row, current));\n        });\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> smawk_row_argmin(std::span<const int> rows,\n\
    \                                  std::span<const int> columns, Value value)\
    \ {\n    return smawk_row_optima(rows, columns, value, std::less<>());\n}\n\n\
    template <class Value>\nstd::vector<int> smawk_row_argmax(std::span<const int>\
    \ rows,\n                                  std::span<const int> columns, Value\
    \ value) {\n    return smawk_row_optima(rows, columns, value, std::greater<>());\n\
    }\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>&\
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
  - convex/monge_shortest_path.hpp
  - convex/monge/all.hpp
  - convex/min_plus_convolution.hpp
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
  - verify/convex/monge/anti_monge_shortest_path.test.cpp
  - verify/convex/monge/monge_shortest_path.test.cpp
  - verify/convex/monge/ordered_matrix.test.cpp
  - verify/convex/monge/ordered_matrix.test.cpp
  - verify/convex/max_plus_convolution_concave_arbitrary.test.cpp
  - verify/convex/max_plus_convolution_concave_concave.test.cpp
  - verify/convex/min_plus_convolution_convex_arbitrary.test.cpp
  - verify/convex/min_plus_convolution_convex_convex.test.cpp
documentation_of: convex/monge/smawk.hpp
layout: document
title: SMAWK
---

Find row optima of a **fixed complete rectangle**. The matrix must be totally
monotone for the requested comparison and tie rule; Monge suffices for minima,
anti-Monge suffices for maxima. Every submatrix's selected optimum positions
must be nondecreasing in row order, using the same comparison and tie rule.
The property is assumed, not checked.

## Interface

The value-based APIs choose the first column in search order on ties; the
comparison-oracle API lets `prefer` decide. Dimensions mean
natural indices; list overloads mean `value(rows[r], columns[c])` and return
original column IDs in row list order. Lists contain distinct nonnegative IDs;
caller-owned IDs need not be dense. Vectors and arrays convert to spans.

In the signatures below, `V` is a callable and `C` is a strict comparator.
Every function returns `std::vector<int>`.

| Signature | Time / additional memory |
| --- | --- |
| `template<class V, class C = std::less<>> std::vector<int> smawk_row_optima(int row_count, int column_count, V value, C compare = C())` | $O(H+W)$ / $O(H+W)$ |
| `template<class V, class C = std::less<>> std::vector<int> smawk_row_optima(std::span<const int> rows, std::span<const int> columns, V value, C compare = C())` | $O(H+W)$ / $O(H+W)$ |
| `template<class V> std::vector<int> smawk_row_argmin(int row_count, int column_count, V value)` | $O(H+W)$ / $O(H+W)$ |
| `template<class V> std::vector<int> smawk_row_argmin(std::span<const int> rows, std::span<const int> columns, V value)` | $O(H+W)$ / $O(H+W)$ |
| `template<class V> std::vector<int> smawk_row_argmax(int row_count, int column_count, V value)` | $O(H+W)$ / $O(H+W)$ |
| `template<class V> std::vector<int> smawk_row_argmax(std::span<const int> rows, std::span<const int> columns, V value)` | $O(H+W)$ / $O(H+W)$ |
| `template<class T> std::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>& matrix)` | $O(H+W)$ / $O(H+W)$ |
| `template<class T> std::vector<int> smawk_row_argmax(const std::vector<std::vector<T>>& matrix)` | $O(H+W)$ / $O(H+W)$ |
| `template<class P> std::vector<int> smawk_row_select(int row_count, int column_count, P prefer)` | $O(H+W)$ / $O(H+W)$ |
| `template<class P> std::vector<int> smawk_row_select(std::span<const int> rows, std::span<const int> columns, P prefer)` | $O(H+W)$ / $O(H+W)$ |

`compare(a,b)` means `a` is strictly better. `prefer(row,current,candidate)`
means replace `current` by `candidate`, including any desired tie decision.
This lower-level comparison oracle supports symbolic invalid entries without
numeric infinity. Its comparisons must describe consistent ordered optima,
and total monotonicity must hold **including the tie rule**. It does not make
arbitrary validity masks safe. For example, strict `<` selects the first
minimum, while `<=` selects the last, under their respective preconditions.

The oracle is independently useful when two entries can be compared directly
without constructing their values: for example, by cancelling common terms in
an implicit cost expression, or comparing valid and symbolic invalid entries
without evaluating an undefined cost. It is a public algorithmic primitive;
convolution is one user, not its defining purpose. Recursive row reduction and
scratch storage remain private in `smawk_detail`.

Only pairs with `current` earlier than `candidate` in the supplied column
order are queried (their original numeric IDs may be reversed). The oracle
must describe a fixed, consistent ordering for each row, with its tie rule
included. In particular, for ordered rows `r < s` and column positions `a < b`,
if the later column is preferred in row `r`, it must remain preferred in row
`s`. This requirement is on positions in the supplied lists, not numeric IDs.

`row_count` and `column_count` must be nonnegative. Matrix overloads assert
rectangular shape. With no columns return `H` copies of `-1`; with no rows
return an empty vector. Callback values may be references and need only the
selected comparison. Inputs are not modified. Complexity counts callback
calls, assuming constant-time comparison and evaluation.

## Ordered example

```cpp
#include "convex/monge/smawk.hpp"
#include <cassert>
#include <vector>

int main() {
    std::vector<int> rows = {2, 0, 1};
    std::vector<int> columns = {1, 2, 0};
    std::vector<int> row_rank = {1, 2, 0};
    std::vector<int> column_rank = {2, 0, 1};
    auto value = [&](int row, int column) {
        int gap = row_rank[row] - column_rank[column];
        return gap * gap;
    };
    auto answer = m1une::convex::smawk_row_argmin(rows, columns, value);
    assert(answer == std::vector<int>({1, 2, 0}));
}
```

The callback may be evaluated out of row order and all entries must already be
fixed. For a previous layer use [transitions](https://m1une.github.io/m1une_library/convex/monge_transition.hpp);
for a same-array recurrence use [shortest paths](https://m1une.github.io/m1une_library/convex/monge_shortest_path.hpp).
Direct anti-Monge minimization is available through `anti_monge_transition`;
when using explicit orders, the first column in a reversed list is the
rightmost natural column. See the [guide](https://m1une.github.io/m1une_library/convex/monge/all.hpp).
