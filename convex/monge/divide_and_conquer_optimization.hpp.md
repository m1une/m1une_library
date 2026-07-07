---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/monge/monotone_minima.hpp
    title: Monotone Minima
  _extendedRequiredBy:
  - icon: ':warning:'
    path: convex/all.hpp
    title: Convex All
  - icon: ':heavy_check_mark:'
    path: convex/monge/all.hpp
    title: Monge All
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
  bundledCode: "#line 1 \"convex/monge/divide_and_conquer_optimization.hpp\"\n\n\n\
    \n#include <type_traits>\n#include <utility>\n#include <vector>\n\n#line 1 \"\
    convex/monge/monotone_minima.hpp\"\n\n\n\n#include <cassert>\n#include <functional>\n\
    #line 7 \"convex/monge/monotone_minima.hpp\"\n\nnamespace m1une {\nnamespace convex\
    \ {\n\nnamespace monotone_minima_detail {\n\ntemplate <class Value, class Compare>\n\
    void solve(int row_left, int row_right, int column_left, int column_right,\n \
    \          const Value& value, const Compare& compare, std::vector<int>& answer)\
    \ {\n    if (row_left == row_right) return;\n    int row = (row_left + row_right)\
    \ / 2;\n    int best = column_left;\n    for (int column = column_left + 1; column\
    \ < column_right; column++) {\n        if (compare(value(row, column), value(row,\
    \ best))) best = column;\n    }\n    answer[row] = best;\n    solve(row_left,\
    \ row, column_left, best + 1, value, compare, answer);\n    solve(row + 1, row_right,\
    \ best, column_right, value, compare, answer);\n}\n\n}  // namespace monotone_minima_detail\n\
    \ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int> monotone_row_optima(int\
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
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 9 \"convex/monge/divide_and_conquer_optimization.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct DivideAndConquerDpResult\
    \ {\n    std::vector<T> value;\n    std::vector<int> argmin;\n};\n\ntemplate <class\
    \ Value>\nauto divide_and_conquer_dp(int state_count, int candidate_count, Value\
    \ value)\n    -> DivideAndConquerDpResult<\n        std::decay_t<std::invoke_result_t<Value,\
    \ int, int>>> {\n    using T = std::decay_t<std::invoke_result_t<Value, int, int>>;\n\
    \    DivideAndConquerDpResult<T> result;\n    result.argmin = monotone_row_argmin(state_count,\
    \ candidate_count, value);\n    result.value.resize(state_count);\n    for (int\
    \ state = 0; state < state_count; state++) {\n        if (result.argmin[state]\
    \ != -1) {\n            result.value[state] = value(state, result.argmin[state]);\n\
    \        }\n    }\n    return result;\n}\n\ntemplate <class T, class Cost>\nauto\
    \ divide_and_conquer_transition(const std::vector<T>& previous, int state_count,\n\
    \                                   Cost cost)\n    -> DivideAndConquerDpResult<\n\
    \        std::decay_t<decltype(std::declval<T>() + cost(0, 0))>> {\n    using\
    \ Result = std::decay_t<decltype(std::declval<T>() + cost(0, 0))>;\n    return\
    \ divide_and_conquer_dp(\n        state_count, int(previous.size()),\n       \
    \ [&](int state, int candidate) -> Result {\n            return previous[candidate]\
    \ + cost(candidate, state);\n        });\n}\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_DIVIDE_AND_CONQUER_OPTIMIZATION_HPP\n#define M1UNE_CONVEX_MONGE_DIVIDE_AND_CONQUER_OPTIMIZATION_HPP\
    \ 1\n\n#include <type_traits>\n#include <utility>\n#include <vector>\n\n#include\
    \ \"monotone_minima.hpp\"\n\nnamespace m1une {\nnamespace convex {\n\ntemplate\
    \ <class T>\nstruct DivideAndConquerDpResult {\n    std::vector<T> value;\n  \
    \  std::vector<int> argmin;\n};\n\ntemplate <class Value>\nauto divide_and_conquer_dp(int\
    \ state_count, int candidate_count, Value value)\n    -> DivideAndConquerDpResult<\n\
    \        std::decay_t<std::invoke_result_t<Value, int, int>>> {\n    using T =\
    \ std::decay_t<std::invoke_result_t<Value, int, int>>;\n    DivideAndConquerDpResult<T>\
    \ result;\n    result.argmin = monotone_row_argmin(state_count, candidate_count,\
    \ value);\n    result.value.resize(state_count);\n    for (int state = 0; state\
    \ < state_count; state++) {\n        if (result.argmin[state] != -1) {\n     \
    \       result.value[state] = value(state, result.argmin[state]);\n        }\n\
    \    }\n    return result;\n}\n\ntemplate <class T, class Cost>\nauto divide_and_conquer_transition(const\
    \ std::vector<T>& previous, int state_count,\n                               \
    \    Cost cost)\n    -> DivideAndConquerDpResult<\n        std::decay_t<decltype(std::declval<T>()\
    \ + cost(0, 0))>> {\n    using Result = std::decay_t<decltype(std::declval<T>()\
    \ + cost(0, 0))>;\n    return divide_and_conquer_dp(\n        state_count, int(previous.size()),\n\
    \        [&](int state, int candidate) -> Result {\n            return previous[candidate]\
    \ + cost(candidate, state);\n        });\n}\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_CONVEX_MONGE_DIVIDE_AND_CONQUER_OPTIMIZATION_HPP\n"
  dependsOn:
  - convex/monge/monotone_minima.hpp
  isVerificationFile: false
  path: convex/monge/divide_and_conquer_optimization.hpp
  requiredBy:
  - convex/monge/all.hpp
  - convex/all.hpp
  timestamp: '2026-07-07 18:38:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/monge_dp_optimization.test.cpp
documentation_of: convex/monge/divide_and_conquer_optimization.hpp
layout: document
title: Divide-and-Conquer DP Optimization
---

## Overview

Divide-and-conquer DP optimization computes

$$
dp[i] = \min_j A(i,j)
$$

when the leftmost minimizing index is nondecreasing with `i`. It evaluates only
a narrowed candidate interval for each recursive subproblem.

This header is the DP-facing wrapper around `monotone_row_argmin`: it returns
both optimum values and their candidate indices.

## Generic Interface

```cpp
template <class Value>
auto divide_and_conquer_dp(
    int state_count,
    int candidate_count,
    Value value
);
```

`value(state, candidate)` returns one transition value. The return type is
`DivideAndConquerDpResult<T>`:

| Member | Meaning |
| --- | --- |
| `value[i]` | Minimum value for state `i`. |
| `argmin[i]` | Leftmost minimizing candidate for state `i`. |

If there are no candidates, every `argmin` is `-1`; the corresponding values
are placeholders.

## Previous-Layer Helper

For the common recurrence

$$
dp_{\mathrm{next}}[i]
= \min_j \left(dp_{\mathrm{previous}}[j] + cost(j,i)\right),
$$

use:

```cpp
template <class T, class Cost>
auto divide_and_conquer_transition(
    const std::vector<T>& previous,
    int state_count,
    Cost cost
);
```

Candidates that are invalid for a state can be represented by a sufficiently
large value, provided arithmetic does not overflow and the remaining leftmost
argmins are still nondecreasing.

## Requirement

The leftmost minimizing candidate indices must be nondecreasing over states.
The implementation does not verify this condition.

Monge transition matrices satisfy the requirement, but the condition also
holds for some matrices that are not Monge.

## Complexity

For `H` states and `W` candidates, the algorithm uses
$O((H+W)\log H)$ transition evaluations and $O(H)$ additional memory.

## Example

```cpp
#include "convex/monge/divide_and_conquer_optimization.hpp"
#include <vector>

int main() {
    std::vector<long long> previous = {0, 4, 7, 9};

    auto result = m1une::convex::divide_and_conquer_transition(
        previous, 6, [](int candidate, int state) {
            long long difference = state - candidate;
            return difference * difference;
        });
}
```
