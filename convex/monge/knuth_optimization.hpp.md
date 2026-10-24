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
  bundledCode: "#line 1 \"convex/monge/knuth_optimization.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <type_traits>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace convex {\n\ntemplate <class T>\nstruct KnuthOptimizationResult\
    \ {\n    std::vector<std::vector<T>> value;\n    std::vector<std::vector<int>>\
    \ split;\n\n    T optimum() const {\n        return value[0].back();\n    }\n\
    };\n\ntemplate <class IntervalCost>\nauto knuth_optimization(int element_count,\
    \ IntervalCost interval_cost)\n    -> KnuthOptimizationResult<\n        std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>> {\n    assert(element_count >= 0);\n    using T = std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>;\n\n    KnuthOptimizationResult<T> result;\n    result.value.assign(element_count\
    \ + 1, std::vector<T>(element_count + 1, T()));\n    result.split.assign(element_count\
    \ + 1, std::vector<int>(element_count + 1, -1));\n\n    for (int left = 0; left\
    \ <= element_count; left++) result.split[left][left] = left;\n    for (int left\
    \ = 0; left < element_count; left++) result.split[left][left + 1] = left + 1;\n\
    \n    for (int length = 2; length <= element_count; length++) {\n        for (int\
    \ left = 0; left + length <= element_count; left++) {\n            int right =\
    \ left + length;\n            int first = std::max(left + 1, result.split[left][right\
    \ - 1]);\n            int last = std::min(right - 1, result.split[left + 1][right]);\n\
    \            assert(first <= last);\n\n            int best = first;\n       \
    \     T best_value = result.value[left][best] + result.value[best][right];\n \
    \           for (int split = first + 1; split <= last; split++) {\n          \
    \      T candidate = result.value[left][split] + result.value[split][right];\n\
    \                if (candidate < best_value) {\n                    best = split;\n\
    \                    best_value = candidate;\n                }\n            }\n\
    \            result.value[left][right] = best_value + interval_cost(left, right);\n\
    \            result.split[left][right] = best;\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_KNUTH_OPTIMIZATION_HPP\n#define M1UNE_CONVEX_MONGE_KNUTH_OPTIMIZATION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <type_traits>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct\
    \ KnuthOptimizationResult {\n    std::vector<std::vector<T>> value;\n    std::vector<std::vector<int>>\
    \ split;\n\n    T optimum() const {\n        return value[0].back();\n    }\n\
    };\n\ntemplate <class IntervalCost>\nauto knuth_optimization(int element_count,\
    \ IntervalCost interval_cost)\n    -> KnuthOptimizationResult<\n        std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>> {\n    assert(element_count >= 0);\n    using T = std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>;\n\n    KnuthOptimizationResult<T> result;\n    result.value.assign(element_count\
    \ + 1, std::vector<T>(element_count + 1, T()));\n    result.split.assign(element_count\
    \ + 1, std::vector<int>(element_count + 1, -1));\n\n    for (int left = 0; left\
    \ <= element_count; left++) result.split[left][left] = left;\n    for (int left\
    \ = 0; left < element_count; left++) result.split[left][left + 1] = left + 1;\n\
    \n    for (int length = 2; length <= element_count; length++) {\n        for (int\
    \ left = 0; left + length <= element_count; left++) {\n            int right =\
    \ left + length;\n            int first = std::max(left + 1, result.split[left][right\
    \ - 1]);\n            int last = std::min(right - 1, result.split[left + 1][right]);\n\
    \            assert(first <= last);\n\n            int best = first;\n       \
    \     T best_value = result.value[left][best] + result.value[best][right];\n \
    \           for (int split = first + 1; split <= last; split++) {\n          \
    \      T candidate = result.value[left][split] + result.value[split][right];\n\
    \                if (candidate < best_value) {\n                    best = split;\n\
    \                    best_value = candidate;\n                }\n            }\n\
    \            result.value[left][right] = best_value + interval_cost(left, right);\n\
    \            result.split[left][right] = best;\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n#endif  // M1UNE_CONVEX_MONGE_KNUTH_OPTIMIZATION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: convex/monge/knuth_optimization.hpp
  requiredBy:
  - convex/monge/all.hpp
  - convex/all.hpp
  timestamp: '2026-07-07 18:38:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
documentation_of: convex/monge/knuth_optimization.hpp
layout: document
title: Knuth Optimization
---

## Overview

Knuth optimization accelerates interval dynamic programming of the form

$$
dp[l][r]
= w(l,r) + \min_{l < k < r}\left(dp[l][k] + dp[k][r]\right).
$$

All intervals are half-open. Singleton and empty intervals have value zero.
The implementation returns every interval value and its optimal split.

The optimization originates in Knuth's
[Optimum binary search trees](https://doi.org/10.1007/BF00288690).

## Worked example: merge adjacent piles

Three piles have weights `{2,3,4}`. Merge adjacent groups until one pile
remains. Each merge costs the total weight of the two groups being merged.

There are two plans: merge `2+3` first, costing `5+9=14`, or merge `3+4`
first, costing `7+9=16`. The answer is `14`.

A straightforward interval DP tries every final split `k`:

```cpp
for (int length = 2; length <= n; ++length) {
    for (int l = 0; l + length <= n; ++l) {
        int r = l + length;
        dp[l][r] = infinity;
        for (int k = l + 1; k < r; ++k) {
            dp[l][r] = std::min(dp[l][r],
                dp[l][k] + dp[k][r] + prefix[r] - prefix[l]);
        }
    }
}
```

Knuth optimization performs that DP with fewer candidate splits:

```cpp
#include "convex/monge/knuth_optimization.hpp"
#include <cassert>
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> weight = {2, 3, 4};
    int n = int(weight.size());
    std::vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + weight[i];
    auto merge_cost = [&](int l, int r) {
        return prefix[r] - prefix[l];  // Weight of [l,r), excluding r.
    };
    auto result = m1une::convex::knuth_optimization(n, merge_cost);
    assert(result.value[0][2] == 5);  // Merge the first two piles.
    assert(result.value[1][3] == 7);  // Merge the last two piles.
    assert(result.split[0][3] == 2);  // Final split: [0,2) and [2,3).
    assert(result.optimum() == 14);
    std::cout << result.optimum() << '\n';
}
```

Output:

```text
14
```

The first argument counts **piles**, and the callback receives a half-open
interval of pile indices. Return only its merge cost; the helper adds the
optimal costs of both subintervals. `.value[l][r]` gives an interval answer,
`.split[l][r]` gives its final split, and `.optimum()` gives the whole answer.

Nonnegative interval sums satisfy both of Knuth's sufficient conditions below.
For a different merge cost, prove those conditions or split monotonicity;
not every interval DP permits this optimization. Work drops from $O(N^3)$
to $O(N^2)$ while retaining all interval answers.

## Interface

```cpp
template <class IntervalCost>
auto knuth_optimization(
    int element_count,
    IntervalCost interval_cost
);
```

`interval_cost(left, right)` returns `w(left, right)` for `[left, right)`.

The result is `KnuthOptimizationResult<T>`:

| Member / Method | Meaning |
| --- | --- |
| `value[l][r]` | Optimal value for `[l, r)`. |
| `split[l][r]` | Leftmost optimal split `k`. |
| `optimum()` | Returns `value[0][element_count]`. |

For intervals of length at least two, the split is strictly inside the
interval.

## Requirement

The recurrence must satisfy Knuth's monotonicity:

$$
opt[l][r-1] \le opt[l][r] \le opt[l+1][r].
$$

A standard sufficient condition is that `w` obeys the quadrangle inequality
and interval monotonicity. For `a <= b <= c <= d`:

$$
w(a,c) + w(b,d) \le w(a,d) + w(b,c)
$$

and

$$
w(b,c) \le w(a,d).
$$

Nonnegative interval sums are a common example. The implementation assumes the
condition and does not verify it.

## Complexity

$O(N^2)$ time and $O(N^2)$ memory, improving the unrestricted cubic recurrence.
