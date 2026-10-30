---
data:
  _extendedDependsOn:
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
  bundledCode: "#line 1 \"convex/monge_transition.hpp\"\n\n\n\n#include <cassert>\n\
    #include <span>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"convex/monge/monotone_minima.hpp\"\n\n\n\n#line 5 \"convex/monge/monotone_minima.hpp\"\
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
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 12 \"convex/monge_transition.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct MatrixTransitionResult\
    \ {\n    std::vector<T> value;\n    std::vector<int> argmin;\n};\n\nnamespace\
    \ monge_transition_detail {\n\ntemplate <class T, class Cost, class Source, class\
    \ Target, class Search>\nauto solve(const std::vector<T>& previous, int targets,\
    \ int sources, Cost cost,\n           Source source, Target target, Search search)\
    \ {\n    using R = std::decay_t<decltype(previous[0] + cost(0, 0))>;\n    auto\
    \ value = [&](int row, int column) -> R {\n        return previous[source(column)]\
    \ + cost(source(column), target(row));\n    };\n    MatrixTransitionResult<R>\
    \ result;\n    result.argmin = search(targets, sources, value);\n    result.value.resize(targets);\n\
    \    for (int row = 0; row < targets; ++row) {\n        int& column = result.argmin[row];\n\
    \        if (column == -1) continue;\n        result.value[row] = value(row, column);\n\
    \        column = source(column);\n    }\n    return result;\n}\n\n}  // namespace\
    \ monge_transition_detail\n\n// Offline layer: g[j] = min_i(previous[i] + cost(i,j));\
    \ previous is finalized.\n// Leftmost minimizing sources must be nondecreasing\
    \ with target index. This is\n// weaker than total monotonicity. O(H + W log(H+1))\
    \ time, O(H) result memory.\n// Ties select smallest source. Empty sources give\
    \ argmin=-1, value=R().\ntemplate <class T, class Cost>\nauto monotone_transition(const\
    \ std::vector<T>& previous, int state_count, Cost cost) {\n    auto identity =\
    \ [](int i) { return i; };\n    return monge_transition_detail::solve(previous,\
    \ state_count, int(previous.size()),\n        cost, identity, identity, [](int\
    \ h, int w, auto value) {\n            return monotone_row_argmin(h, w, value);\n\
    \        });\n}\n\n// Same offline recurrence, with finite Monge cost(source,target).\
    \ Adding source\n// constants preserves Monge. O(H+W) time/memory; smallest source\
    \ on ties.\ntemplate <class T, class Cost>\nauto monge_transition(const std::vector<T>&\
    \ previous, int state_count, Cost cost) {\n    auto identity = [](int i) { return\
    \ i; };\n    return monge_transition_detail::solve(previous, state_count, int(previous.size()),\n\
    \        cost, identity, identity, [](int h, int w, auto value) {\n          \
    \  return smawk_row_argmin(h, w, value);\n        });\n}\n\n// Anti-Monge specialization:\
    \ reverse source order internally. Largest source\n// on ties; O(H+W) time/memory.\
    \ All source-target pairs must be legal and finite.\ntemplate <class T, class\
    \ Cost>\nauto anti_monge_transition(const std::vector<T>& previous, int state_count,\
    \ Cost cost) {\n    int width = int(previous.size());\n    return monge_transition_detail::solve(previous,\
    \ state_count, width, cost,\n        [=](int i) { return width - 1 - i; }, [](int\
    \ i) { return i; },\n        [](int h, int w, auto value) { return smawk_row_argmin(h,\
    \ w, value); });\n}\n\n// Ordered variants: the virtual matrix is previous[sources[c]]\
    \ +\n// cost(sources[c], targets[r]). Return original source IDs, in target list\
    \ order.\n// IDs must be distinct/nonnegative; sources must index previous. Ties\
    \ choose the\n// first source in the supplied order. No same-array recurrence\
    \ is computed.\ntemplate <class T, class Cost>\nauto monotone_transition(const\
    \ std::vector<T>& previous,\n                         std::span<const int> targets,\
    \ std::span<const int> sources,\n                         Cost cost) {\n    for\
    \ (int i : sources) { assert(0 <= i && i < int(previous.size())); (void)i; }\n\
    \    for (int j : targets) { assert(j >= 0); (void)j; }\n    return monge_transition_detail::solve(previous,\
    \ int(targets.size()),\n        int(sources.size()), cost, [&](int i) { return\
    \ sources[i]; },\n        [&](int i) { return targets[i]; },\n        [](int h,\
    \ int w, auto value) { return monotone_row_argmin(h, w, value); });\n}\n\ntemplate\
    \ <class T, class Cost>\nauto monge_transition(const std::vector<T>& previous,\n\
    \                      std::span<const int> targets, std::span<const int> sources,\n\
    \                      Cost cost) {\n    for (int i : sources) { assert(0 <= i\
    \ && i < int(previous.size())); (void)i; }\n    for (int j : targets) { assert(j\
    \ >= 0); (void)j; }\n    return monge_transition_detail::solve(previous, int(targets.size()),\n\
    \        int(sources.size()), cost, [&](int i) { return sources[i]; },\n     \
    \   [&](int i) { return targets[i]; },\n        [](int h, int w, auto value) {\
    \ return smawk_row_argmin(h, w, value); });\n}\n\n}  // namespace convex\n}  //\
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_TRANSITION_HPP\n#define M1UNE_CONVEX_MONGE_TRANSITION_HPP\
    \ 1\n\n#include <cassert>\n#include <span>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#include \"monge/monotone_minima.hpp\"\n#include \"monge/smawk.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct MatrixTransitionResult\
    \ {\n    std::vector<T> value;\n    std::vector<int> argmin;\n};\n\nnamespace\
    \ monge_transition_detail {\n\ntemplate <class T, class Cost, class Source, class\
    \ Target, class Search>\nauto solve(const std::vector<T>& previous, int targets,\
    \ int sources, Cost cost,\n           Source source, Target target, Search search)\
    \ {\n    using R = std::decay_t<decltype(previous[0] + cost(0, 0))>;\n    auto\
    \ value = [&](int row, int column) -> R {\n        return previous[source(column)]\
    \ + cost(source(column), target(row));\n    };\n    MatrixTransitionResult<R>\
    \ result;\n    result.argmin = search(targets, sources, value);\n    result.value.resize(targets);\n\
    \    for (int row = 0; row < targets; ++row) {\n        int& column = result.argmin[row];\n\
    \        if (column == -1) continue;\n        result.value[row] = value(row, column);\n\
    \        column = source(column);\n    }\n    return result;\n}\n\n}  // namespace\
    \ monge_transition_detail\n\n// Offline layer: g[j] = min_i(previous[i] + cost(i,j));\
    \ previous is finalized.\n// Leftmost minimizing sources must be nondecreasing\
    \ with target index. This is\n// weaker than total monotonicity. O(H + W log(H+1))\
    \ time, O(H) result memory.\n// Ties select smallest source. Empty sources give\
    \ argmin=-1, value=R().\ntemplate <class T, class Cost>\nauto monotone_transition(const\
    \ std::vector<T>& previous, int state_count, Cost cost) {\n    auto identity =\
    \ [](int i) { return i; };\n    return monge_transition_detail::solve(previous,\
    \ state_count, int(previous.size()),\n        cost, identity, identity, [](int\
    \ h, int w, auto value) {\n            return monotone_row_argmin(h, w, value);\n\
    \        });\n}\n\n// Same offline recurrence, with finite Monge cost(source,target).\
    \ Adding source\n// constants preserves Monge. O(H+W) time/memory; smallest source\
    \ on ties.\ntemplate <class T, class Cost>\nauto monge_transition(const std::vector<T>&\
    \ previous, int state_count, Cost cost) {\n    auto identity = [](int i) { return\
    \ i; };\n    return monge_transition_detail::solve(previous, state_count, int(previous.size()),\n\
    \        cost, identity, identity, [](int h, int w, auto value) {\n          \
    \  return smawk_row_argmin(h, w, value);\n        });\n}\n\n// Anti-Monge specialization:\
    \ reverse source order internally. Largest source\n// on ties; O(H+W) time/memory.\
    \ All source-target pairs must be legal and finite.\ntemplate <class T, class\
    \ Cost>\nauto anti_monge_transition(const std::vector<T>& previous, int state_count,\
    \ Cost cost) {\n    int width = int(previous.size());\n    return monge_transition_detail::solve(previous,\
    \ state_count, width, cost,\n        [=](int i) { return width - 1 - i; }, [](int\
    \ i) { return i; },\n        [](int h, int w, auto value) { return smawk_row_argmin(h,\
    \ w, value); });\n}\n\n// Ordered variants: the virtual matrix is previous[sources[c]]\
    \ +\n// cost(sources[c], targets[r]). Return original source IDs, in target list\
    \ order.\n// IDs must be distinct/nonnegative; sources must index previous. Ties\
    \ choose the\n// first source in the supplied order. No same-array recurrence\
    \ is computed.\ntemplate <class T, class Cost>\nauto monotone_transition(const\
    \ std::vector<T>& previous,\n                         std::span<const int> targets,\
    \ std::span<const int> sources,\n                         Cost cost) {\n    for\
    \ (int i : sources) { assert(0 <= i && i < int(previous.size())); (void)i; }\n\
    \    for (int j : targets) { assert(j >= 0); (void)j; }\n    return monge_transition_detail::solve(previous,\
    \ int(targets.size()),\n        int(sources.size()), cost, [&](int i) { return\
    \ sources[i]; },\n        [&](int i) { return targets[i]; },\n        [](int h,\
    \ int w, auto value) { return monotone_row_argmin(h, w, value); });\n}\n\ntemplate\
    \ <class T, class Cost>\nauto monge_transition(const std::vector<T>& previous,\n\
    \                      std::span<const int> targets, std::span<const int> sources,\n\
    \                      Cost cost) {\n    for (int i : sources) { assert(0 <= i\
    \ && i < int(previous.size())); (void)i; }\n    for (int j : targets) { assert(j\
    \ >= 0); (void)j; }\n    return monge_transition_detail::solve(previous, int(targets.size()),\n\
    \        int(sources.size()), cost, [&](int i) { return sources[i]; },\n     \
    \   [&](int i) { return targets[i]; },\n        [](int h, int w, auto value) {\
    \ return smawk_row_argmin(h, w, value); });\n}\n\n}  // namespace convex\n}  //\
    \ namespace m1une\n\n#endif  // M1UNE_CONVEX_MONGE_TRANSITION_HPP\n"
  dependsOn:
  - convex/monge/monotone_minima.hpp
  - convex/monge/smawk.hpp
  isVerificationFile: false
  path: convex/monge_transition.hpp
  requiredBy:
  - convex/all.hpp
  timestamp: '2026-10-30 15:56:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/ordered_matrix.test.cpp
documentation_of: convex/monge_transition.hpp
layout: document
title: Finalized-Layer Matrix Transitions
---

Compute the **offline** rectangular recurrence
$g[j]=\min_i(f[i]+C(i,j))$, where every `f[i]` is already finalized.
All source-target pairs exist and have finite costs. `cost(source,target)`
returns only `C`; the helper adds `previous[source]`. Rows are targets and
columns are sources. Source constants preserve Monge but do not necessarily
preserve mere argmin monotonicity.

All APIs use `m1une::convex`. `R` below denotes
`std::decay_t<decltype(previous[0] + cost(0,0))>`. The actual return signatures
use `auto`, deduced as `MatrixTransitionResult<R>`. `R` must be default
constructible and support comparison; addition must be defined with `T` and
the cost type. Values are ordinary finite values, without sentinel semantics;
intermediate sums must fit. Callbacks must be fixed and may be evaluated in
any order. Inputs are not modified.

## Interface

Let `H` be the target count and `W` the source count.

| Exact signature (deduced return type as above) | Required property | Time |
| --- | --- | --- |
| `template<class T, class Cost> auto monotone_transition(const std::vector<T>& previous, int state_count, Cost cost)` | Leftmost minimizing sources of the **full matrix including previous** are nondecreasing. | $O(H+W\log(H+1))$ |
| `template<class T, class Cost> auto monotone_transition(const std::vector<T>& previous, std::span<const int> targets, std::span<const int> sources, Cost cost)` | Same property in supplied target/source orders. | $O(H+W\log(H+1))$ |
| `template<class T, class Cost> auto monge_transition(const std::vector<T>& previous, int state_count, Cost cost)` | `cost(source,target)` is Monge in natural orders. | $O(H+W)$ |
| `template<class T, class Cost> auto monge_transition(const std::vector<T>& previous, std::span<const int> targets, std::span<const int> sources, Cost cost)` | `cost(sources[c],targets[r])` is Monge in those orders. | $O(H+W)$ |
| `template<class T, class Cost> auto anti_monge_transition(const std::vector<T>& previous, int state_count, Cost cost)` | Anti-Monge in natural orders; reverses sources internally. | $O(H+W)$ |

Total monotonicity of the full matrix is a weaker sufficient condition for
either SMAWK-based function. `monotone_transition` needs only whole-matrix
argmin monotonicity and uses monotone minima internally. `state_count >= 0`.
Ordered lists contain distinct nonnegative IDs, with every source indexing
`previous`; source bounds and target nonnegativity are asserted. Subsets and
permutations are both allowed. No ordering is inferred or sorted.

SMAWK versions use $O(H+W)$ memory including results. The monotone versions
use $O(H+\log(H+1))$ memory. Ordered argument validation adds $O(H+W)$ time,
including the degenerate empty-target case. All times assume constant-time
costs, addition, and comparison.

`MatrixTransitionResult<R>` has `std::vector<R> value` and
`std::vector<int> argmin`. Results are compact in target order; `argmin` holds
original source IDs. Ties choose the first supplied source, the smallest
natural source for the count-based Monge/monotone calls, and the largest
natural source for the anti-Monge call. Empty source lists yield `argmin=-1`
and `value=R()` (a placeholder, **not** an optimum or infinity). Empty target
lists return empty vectors. Always inspect `argmin` before using a value when
sources may be empty.

## Example

```cpp
#include "convex/monge_transition.hpp"
#include <cassert>
#include <vector>

int main() {
    std::vector<long long> previous = {7, 1, 9};
    auto result = m1une::convex::monge_transition(previous, 4, [](int i, int j) {
        return (i-j)*1LL*(i-j);
    });
    assert(result.value == std::vector<long long>({2, 1, 2, 5}));
    auto anti = m1une::convex::anti_monge_transition(previous, 4, [](int i, int j) {
        return -(i-j)*1LL*(i-j);
    });
    assert(anti.value == std::vector<long long>({0, 1, 0, -3}));

    std::vector<int> targets = {0, 1, 2, 3};
    std::vector<int> sources = {2, 1, 0};
    auto ordered = m1une::convex::monge_transition(previous, targets, sources,
        [](int i, int j) { return -(i-j)*1LL*(i-j); });
    assert(ordered.value == anti.value && ordered.argmin == anti.argmin);
}
```

The direct anti-Monge call requires no user permutation. The ordered example
shows its relationship to the general abstraction. More complicated known
orders use the same list overload. Arbitrary partial or triangular validity
masks are not accepted; for `dp[j]` depending on its own earlier entries use
[Monge shortest paths](https://m1une.github.io/m1une_library/convex/monge_shortest_path.hpp).
