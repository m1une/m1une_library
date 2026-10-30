---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/monge/check.hpp
    title: Monge and Anti-Monge Checks
  - icon: ':heavy_check_mark:'
    path: convex/monge/larsch.hpp
    title: LARSCH Online Matrix Minima
  - icon: ':heavy_check_mark:'
    path: convex/monge/monotone_minima.hpp
    title: Monotone Matrix Minima
  - icon: ':heavy_check_mark:'
    path: convex/monge/smawk.hpp
    title: SMAWK
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: convex/all.hpp
    title: Convex All
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
  bundledCode: "#line 1 \"convex/monge/all.hpp\"\n\n\n\n#line 1 \"convex/monge/check.hpp\"\
    \n\n\n\n#include <cassert>\n#include <span>\n#include <vector>\n\nnamespace m1une\
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
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 1 \"convex/monge/larsch.hpp\"\
    \n\n\n\n#line 5 \"convex/monge/larsch.hpp\"\n#include <utility>\n#line 7 \"convex/monge/larsch.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\n// Online minima of a lower-triangular\
    \ totally monotone matrix (column <= row).\n// Leftmost ties. Before answering\
    \ row r, only columns <= r are accessed, even\n// when evaluating future rows.\
    \ Finalize column r+1 after receiving answer r.\n// O(N) total time/evaluations/memory;\
    \ an individual next_argmin can take O(N).\n// Value is stored directly, with\
    \ no type-erased callable. Use CTAD: Larsch q(n,f).\ntemplate <class Value>\n\
    class Larsch {\n    struct Level {\n        int size;\n        int row = 0;\n\
    \        int column_row = 0;\n        int boundary = 0;\n        std::vector<int>\
    \ columns;\n        explicit Level(int n) : size(n) {}\n    };\n\n    int _size;\n\
    \    Value _value;\n    std::vector<Level> _levels;\n\n    auto entry(int depth,\
    \ int row, int column) {\n        for (int d = depth; d > 0; --d) {\n        \
    \    row = row * 2 + 1;\n            column = _levels[d].columns[column];\n  \
    \      }\n        return _value(row, column);\n    }\n\n    int next_column(int\
    \ depth) {\n        auto& level = _levels[depth];\n        int row = level.column_row++;\n\
    \        int first = row == 0 ? 0 : row * 2 - 1;\n        for (int column = first;\
    \ column <= row * 2; ++column) {\n            while (int(level.columns.size())\
    \ != row &&\n                   entry(depth - 1, int(level.columns.size()) * 2\
    \ - 1,\n                         level.columns.back()) >\n                   entry(depth\
    \ - 1, int(level.columns.size()) * 2 - 1, column)) {\n                level.columns.pop_back();\n\
    \            }\n            if (int(level.columns.size()) != level.size) {\n \
    \               level.columns.push_back(column);\n            }\n        }\n \
    \       return level.columns[next_row(depth)];\n    }\n\n    int next_row(int\
    \ depth) {\n        auto& level = _levels[depth];\n        int row = level.row++;\n\
    \        if (row % 2 != 0) {\n            return entry(depth, row, level.boundary)\
    \ <= entry(depth, row, row)\n                       ? level.boundary : row;\n\
    \        }\n        int previous = level.boundary;\n        int next = row + 1\
    \ == level.size ? level.size - 1\n                                        : next_column(depth\
    \ + 1);\n        level.boundary = next;\n        int best = previous;\n      \
    \  for (int column = previous + 1; column <= next; ++column) {\n            if\
    \ (entry(depth, row, column) < entry(depth, row, best)) best = column;\n     \
    \   }\n        return best;\n    }\n\n   public:\n    explicit Larsch(int size,\
    \ Value value) : _size(size), _value(std::move(value)) {\n        assert(size\
    \ >= 0);\n        for (int n = size; n > 0; n /= 2) {\n            _levels.emplace_back(n);\n\
    \            if (_levels.size() > 1) _levels.back().columns.reserve(n);\n    \
    \    }\n    }\n    int size() const { return _size; }\n    int processed_rows()\
    \ const { return _size == 0 ? 0 : _levels[0].row; }\n    bool finished() const\
    \ { return processed_rows() == _size; }\n    int next_argmin() {\n        assert(!finished());\n\
    \        return next_row(0);\n    }\n};\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n\n#line 1 \"convex/monge/monotone_minima.hpp\"\n\n\n\n#line 5 \"convex/monge/monotone_minima.hpp\"\
    \n#include <functional>\n#line 8 \"convex/monge/monotone_minima.hpp\"\n\nnamespace\
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
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 1 \"convex/monge/smawk.hpp\"\
    \n\n\n\n#line 6 \"convex/monge/smawk.hpp\"\n#include <numeric>\n#line 9 \"convex/monge/smawk.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\nnamespace smawk_detail {\n\ntemplate\
    \ <class Select>\nvoid solve(const std::vector<int>& rows, const std::vector<int>&\
    \ columns,\n           const Select& select, std::vector<int>& answer) {\n   \
    \ if (rows.empty()) return;\n\n    std::vector<int> reduced;\n    reduced.reserve(columns.size());\n\
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
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 8 \"convex/monge/all.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_CONVEX_MONGE_ALL_HPP

    #define M1UNE_CONVEX_MONGE_ALL_HPP 1


    #include "check.hpp"

    #include "larsch.hpp"

    #include "monotone_minima.hpp"

    #include "smawk.hpp"


    #endif  // M1UNE_CONVEX_MONGE_ALL_HPP

    '
  dependsOn:
  - convex/monge/check.hpp
  - convex/monge/larsch.hpp
  - convex/monge/monotone_minima.hpp
  - convex/monge/smawk.hpp
  isVerificationFile: false
  path: convex/monge/all.hpp
  requiredBy:
  - convex/all.hpp
  timestamp: '2026-10-30 15:56:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/ordered_matrix.test.cpp
documentation_of: convex/monge/all.hpp
layout: document
title: Monge Matrix Primitives and Algorithm Guide
---

All APIs here use `m1une::convex`, zero-based indices, and half-open ranges.
`convex/monge/all.hpp` includes **only matrix primitives**. Use
`convex/all.hpp` to include the applications too.

## Choose the abstraction

| Problem / assumption | Header and API | Time |
| --- | --- | --- |
| Fixed rectangle, totally monotone optima | [smawk.hpp](https://m1une.github.io/m1une_library/convex/monge/smawk.hpp): `smawk_row_argmin`, `smawk_row_argmax`, `smawk_row_select` | $O(H+W)$ |
| Fixed rectangle, only leftmost argmins are nondecreasing | [monotone_minima.hpp](https://m1une.github.io/m1une_library/convex/monge/monotone_minima.hpp): `monotone_row_argmin` | $O(H+W\log(H+1))$ |
| Online lower-triangular totally monotone matrix | [larsch.hpp](https://m1une.github.io/m1une_library/convex/monge/larsch.hpp): `Larsch` | $O(N)$ total |
| Check Monge / anti-Monge inequalities | [check.hpp](https://m1une.github.io/m1une_library/convex/monge/check.hpp): `is_monge`, `is_anti_monge` | $O(HW)$ |
| Finalized previous layer, monotone minimizing sources | [monge_transition.hpp](https://m1une.github.io/m1une_library/convex/monge_transition.hpp): `monotone_transition` | $O(H+W\log(H+1))$ |
| Finalized previous layer, Monge / anti-Monge costs | Same header: `monge_transition`, `anti_monge_transition` | $O(H+W)$ |
| Same-array forward recurrence, Monge costs, minimum step $D$ | [monge_shortest_path.hpp](https://m1une.github.io/m1une_library/convex/monge_shortest_path.hpp): `monge_shortest_path` | $O(N)$ for every $D$ |
| Same-array forward recurrence, anti-Monge costs, minimum step $D$ | Same header: `anti_monge_shortest_path` | $O(N\log N+ND)$ |
| Structured sequence min-plus / max-plus convolution | [min_plus_convolution.hpp](https://m1une.github.io/m1une_library/convex/min_plus_convolution.hpp) | $O(N+M)$ |
| Interval DP with monotone optimal splits | [algo/dp/knuth_optimization.hpp](https://m1une.github.io/m1une_library/algo/dp/knuth_optimization.hpp), namespace `m1une::algo` | $O(N^2)$ |

All bounds assume constant-time callbacks and arithmetic. See each page for
memory bounds, numeric requirements, and exact signatures.

## Property, ordering, and ties

For ordered rows $r<s$ and columns $c<d$, Monge means
$A(r,c)+A(s,d)\le A(r,d)+A(s,c)$; anti-Monge reverses this inequality.
A Monge matrix is totally monotone for leftmost minima: every submatrix has
nondecreasing leftmost minimizing column positions. Monotonicity of the minima
of the whole matrix alone is weaker; use monotone minima for that case.

Matrix primitives accept either dimensions or explicit `std::span<const int>`
row/column lists (vectors and arrays convert). The virtual matrix is
`value(rows[r], columns[c])`. Lists may be arbitrary permutations or subsets
of distinct nonnegative IDs. Answers are original column IDs, stored compactly
in **row list order**; `-1` means there are no columns. Value-based searches
choose the first column in the supplied order on ties; `smawk_row_select`
instead uses the tie rule specified by its comparison oracle, which must also
preserve total monotonicity. The library neither discovers nor sorts an order.

Reversing one axis turns anti-Monge into Monge. The public anti-Monge checks,
transitions, and shortest paths do this internally where appropriate. Their
minimization APIs select the **largest natural source ID** on ties. Ordered
Monge calls can describe other known permutations without a policy class or
an allocated matrix. An order describes the matrix, not a new graph topology.

## Offline transitions versus same-array shortest paths

For `g[j] = min_i(previous[i] + cost(i,j))`, all `previous` entries are final.
The matrix has **targets as rows**, **sources as columns**. Source constants
preserve Monge, so SMAWK can query any entry in any order.

For `dp[j] = min_{i <= j-D}(dp[i] + cost(i,j))`, the source distances are being
computed. Calling ordinary SMAWK on a callback reading that same unfinished
array is invalid. Use the shortest-path APIs, which enforce the dependency
order. LARSCH is the advanced primitive for managing that order yourself.

Both transition and shortest-path callbacks receive `(source, target)` and
return **only the cost**; the algorithms add the source value. Matrix callbacks
receive `(row, column)` and return the **entire entry**.

## Validity masks

SMAWK searches a complete rectangle. Arbitrary missing edges, triangular masks,
and padding with an infinity sentinel do not automatically preserve total
monotonicity, especially with a specified tie rule. The online primitive handles
its particular lower triangle; the anti-Monge shortest-path solver decomposes
legal edges into complete rectangles and a directly scanned boundary. The
convolution implementation uses a symbolic comparison oracle for its band.

## Migration

`larsch_shortest_path` becomes `monge_shortest_path` in
`convex/monge_shortest_path.hpp`, now with explicit `infinity` and optional
`minimum_step`. Both shortest paths return `MongeShortestPathResult<T>`.
`Larsch` stores the callback type; write `Larsch search(n, value)` using CTAD
instead of `Larsch<T>`.

`divide_and_conquer_transition` becomes `monotone_transition`;
`DivideAndConquerDpResult` becomes `MatrixTransitionResult`. The redundant
`divide_and_conquer_dp` value-and-choice wrapper is removed: call
`monotone_row_argmin` for a raw matrix. All application headers moved out of
`convex/monge/`; Knuth also moved to `m1une::algo`. No forwarding headers remain.
