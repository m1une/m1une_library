---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: convex/all.hpp
    title: Convex All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/alien_trick.test.cpp
    title: verify/convex/alien_trick.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"convex/alien_trick.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <concepts>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace convex {\n\nnamespace detail {\n\ntemplate <std::integral\
    \ Penalty, std::integral Count, class Oracle>\nPenalty alien_trick_penalty(Penalty\
    \ lower, Penalty upper, Count target_count, Oracle& oracle) {\n    assert(lower\
    \ <= upper);\n    assert(oracle(lower).second >= target_count);\n    assert(oracle(upper).second\
    \ <= target_count);\n\n    while (lower < upper) {\n        Penalty middle = std::midpoint(lower,\
    \ upper);\n        if (middle == lower) ++middle;\n        if (oracle(middle).second\
    \ >= target_count) {\n            lower = middle;\n        } else {\n        \
    \    upper = middle - 1;\n        }\n    }\n    return lower;\n}\n\n}  // namespace\
    \ detail\n\n// Recovers the minimum value among solutions using exactly `target_count`\n\
    // items. The oracle minimizes value + penalty * count and breaks ties in favor\n\
    // of the larger count.\ntemplate <std::integral Penalty, std::integral Count,\
    \ class Oracle>\nauto alien_trick_minimize(Penalty lower, Penalty upper, Count\
    \ target_count, Oracle oracle) {\n    Penalty penalty = detail::alien_trick_penalty(lower,\
    \ upper, target_count, oracle);\n    auto result = oracle(penalty);\n    using\
    \ Value = std::remove_cvref_t<decltype(result.first)>;\n    return result.first\
    \ - static_cast<Value>(penalty) * static_cast<Value>(target_count);\n}\n\n// Recovers\
    \ the maximum value among solutions using exactly `target_count`\n// items. The\
    \ oracle maximizes value - penalty * count and breaks ties in favor\n// of the\
    \ larger count.\ntemplate <std::integral Penalty, std::integral Count, class Oracle>\n\
    auto alien_trick_maximize(Penalty lower, Penalty upper, Count target_count, Oracle\
    \ oracle) {\n    Penalty penalty = detail::alien_trick_penalty(lower, upper, target_count,\
    \ oracle);\n    auto result = oracle(penalty);\n    using Value = std::remove_cvref_t<decltype(result.first)>;\n\
    \    return result.first + static_cast<Value>(penalty) * static_cast<Value>(target_count);\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_ALIEN_TRICK_HPP\n#define M1UNE_CONVEX_ALIEN_TRICK_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <numeric>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace convex {\n\nnamespace detail\
    \ {\n\ntemplate <std::integral Penalty, std::integral Count, class Oracle>\nPenalty\
    \ alien_trick_penalty(Penalty lower, Penalty upper, Count target_count, Oracle&\
    \ oracle) {\n    assert(lower <= upper);\n    assert(oracle(lower).second >= target_count);\n\
    \    assert(oracle(upper).second <= target_count);\n\n    while (lower < upper)\
    \ {\n        Penalty middle = std::midpoint(lower, upper);\n        if (middle\
    \ == lower) ++middle;\n        if (oracle(middle).second >= target_count) {\n\
    \            lower = middle;\n        } else {\n            upper = middle - 1;\n\
    \        }\n    }\n    return lower;\n}\n\n}  // namespace detail\n\n// Recovers\
    \ the minimum value among solutions using exactly `target_count`\n// items. The\
    \ oracle minimizes value + penalty * count and breaks ties in favor\n// of the\
    \ larger count.\ntemplate <std::integral Penalty, std::integral Count, class Oracle>\n\
    auto alien_trick_minimize(Penalty lower, Penalty upper, Count target_count, Oracle\
    \ oracle) {\n    Penalty penalty = detail::alien_trick_penalty(lower, upper, target_count,\
    \ oracle);\n    auto result = oracle(penalty);\n    using Value = std::remove_cvref_t<decltype(result.first)>;\n\
    \    return result.first - static_cast<Value>(penalty) * static_cast<Value>(target_count);\n\
    }\n\n// Recovers the maximum value among solutions using exactly `target_count`\n\
    // items. The oracle maximizes value - penalty * count and breaks ties in favor\n\
    // of the larger count.\ntemplate <std::integral Penalty, std::integral Count,\
    \ class Oracle>\nauto alien_trick_maximize(Penalty lower, Penalty upper, Count\
    \ target_count, Oracle oracle) {\n    Penalty penalty = detail::alien_trick_penalty(lower,\
    \ upper, target_count, oracle);\n    auto result = oracle(penalty);\n    using\
    \ Value = std::remove_cvref_t<decltype(result.first)>;\n    return result.first\
    \ + static_cast<Value>(penalty) * static_cast<Value>(target_count);\n}\n\n}  //\
    \ namespace convex\n}  // namespace m1une\n\n#endif  // M1UNE_CONVEX_ALIEN_TRICK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: convex/alien_trick.hpp
  requiredBy:
  - convex/all.hpp
  timestamp: '2026-07-07 18:38:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/alien_trick.test.cpp
documentation_of: convex/alien_trick.hpp
layout: document
title: Alien Trick
---

## Overview

The Alien Trick, also called Lagrangian relaxation or WQS binary search,
converts an optimization problem with an exact-count constraint into a sequence
of unconstrained penalized problems.

This header provides:

* `alien_trick_minimize(lower, upper, target_count, oracle)`
* `alien_trick_maximize(lower, upper, target_count, oracle)`

Both functions return the optimum among solutions whose count is exactly
`target_count`.

The public namespace is `m1une::convex`.

## Oracle Contract

For minimization, `oracle(penalty)` must return a pair
`{penalized_value, count}` minimizing

$$
\mathrm{original\ value} + \mathrm{penalty} \cdot \mathrm{count}.
$$

For maximization, it must return a pair maximizing

$$
\mathrm{original\ value} - \mathrm{penalty} \cdot \mathrm{count}.
$$

If several solutions have the same penalized value, the oracle must choose the
one with the larger count. Consequently, the returned count is non-increasing
as the penalty increases.

The exact-count optimum must be discrete convex for minimization or discrete
concave for maximization. Without this condition, the relaxed problem can skip
the requested count and the Alien Trick cannot recover its optimum.

## Penalty Bounds

`lower` and `upper` are inclusive integral penalty bounds. They must satisfy:

* `lower <= upper`
* `oracle(lower).second >= target_count`
* `oracle(upper).second <= target_count`

All values, penalties, products, and intermediate oracle calculations must fit
their respective types.

## Complexity

If one oracle call takes $O(D)$ time, the helper takes
$O(D \log(\mathrm{upper}-\mathrm{lower}+1))$ time and $O(1)$ additional space,
excluding the oracle.

## Example

```cpp
#include "convex/alien_trick.hpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::vector<long long> exact = {25, 12, 5, 2, 3, 8};

    auto oracle = [&exact](long long penalty) {
        std::pair<long long, int> best;
        best.first = exact[0];
        best.second = 0;
        for (int count = 1; count < int(exact.size()); count++) {
            long long value = exact[count] + penalty * count;
            if (value < best.first || (value == best.first && best.second < count)) {
                best.first = value;
                best.second = count;
            }
        }
        return best;
    };

    std::cout << m1une::convex::alien_trick_minimize(
        -100LL,
        100LL,
        3,
        oracle
    ) << "\n";
}
```
