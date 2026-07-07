---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  - icon: ':warning:'
    path: algo/search/all.hpp
    title: Search Algorithms All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/algo/search/ternary_search.test.cpp
    title: verify/algo/search/ternary_search.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/search/ternary_search.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n\nnamespace m1une {\nnamespace algo {\n\ntemplate <std::integral\
    \ Int, class F>\nInt ternary_search_argmin(Int left, Int right, F f) {\n    assert(left\
    \ < right);\n    while (right - left > 3) {\n        const Int third = (right\
    \ - left) / 3;\n        const Int middle_left = left + third;\n        const Int\
    \ middle_right = right - third;\n        if (f(middle_right) < f(middle_left))\
    \ {\n            left = middle_left + 1;\n        } else {\n            right\
    \ = middle_right;\n        }\n    }\n\n    Int best = left;\n    auto best_value\
    \ = f(best);\n    for (Int x = left + 1; x < right; ++x) {\n        auto value\
    \ = f(x);\n        if (value < best_value) {\n            best = x;\n        \
    \    best_value = value;\n        }\n    }\n    return best;\n}\n\ntemplate <std::integral\
    \ Int, class F>\nInt ternary_search_argmax(Int left, Int right, F f) {\n    assert(left\
    \ < right);\n    while (right - left > 3) {\n        const Int third = (right\
    \ - left) / 3;\n        const Int middle_left = left + third;\n        const Int\
    \ middle_right = right - third;\n        if (f(middle_left) < f(middle_right))\
    \ {\n            left = middle_left + 1;\n        } else {\n            right\
    \ = middle_right;\n        }\n    }\n\n    Int best = left;\n    auto best_value\
    \ = f(best);\n    for (Int x = left + 1; x < right; ++x) {\n        auto value\
    \ = f(x);\n        if (best_value < value) {\n            best = x;\n        \
    \    best_value = value;\n        }\n    }\n    return best;\n}\n\ntemplate <class\
    \ F>\ndouble real_ternary_search_argmin(double left, double right, F f, int iterations\
    \ = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n    for\
    \ (int i = 0; i < iterations; ++i) {\n        const double middle_left = (left\
    \ * 2.0 + right) / 3.0;\n        const double middle_right = (left + right * 2.0)\
    \ / 3.0;\n        if (f(middle_right) < f(middle_left)) {\n            left =\
    \ middle_left;\n        } else {\n            right = middle_right;\n        }\n\
    \    }\n    return (left + right) / 2.0;\n}\n\ntemplate <class F>\ndouble real_ternary_search_argmax(double\
    \ left, double right, F f, int iterations = 100) {\n    assert(left <= right);\n\
    \    assert(0 <= iterations);\n    for (int i = 0; i < iterations; ++i) {\n  \
    \      const double middle_left = (left * 2.0 + right) / 3.0;\n        const double\
    \ middle_right = (left + right * 2.0) / 3.0;\n        if (f(middle_left) < f(middle_right))\
    \ {\n            left = middle_left;\n        } else {\n            right = middle_right;\n\
    \        }\n    }\n    return (left + right) / 2.0;\n}\n\n}  // namespace algo\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_SEARCH_TERNARY_SEARCH_HPP\n#define M1UNE_ALGO_SEARCH_TERNARY_SEARCH_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n\nnamespace m1une {\nnamespace\
    \ algo {\n\ntemplate <std::integral Int, class F>\nInt ternary_search_argmin(Int\
    \ left, Int right, F f) {\n    assert(left < right);\n    while (right - left\
    \ > 3) {\n        const Int third = (right - left) / 3;\n        const Int middle_left\
    \ = left + third;\n        const Int middle_right = right - third;\n        if\
    \ (f(middle_right) < f(middle_left)) {\n            left = middle_left + 1;\n\
    \        } else {\n            right = middle_right;\n        }\n    }\n\n   \
    \ Int best = left;\n    auto best_value = f(best);\n    for (Int x = left + 1;\
    \ x < right; ++x) {\n        auto value = f(x);\n        if (value < best_value)\
    \ {\n            best = x;\n            best_value = value;\n        }\n    }\n\
    \    return best;\n}\n\ntemplate <std::integral Int, class F>\nInt ternary_search_argmax(Int\
    \ left, Int right, F f) {\n    assert(left < right);\n    while (right - left\
    \ > 3) {\n        const Int third = (right - left) / 3;\n        const Int middle_left\
    \ = left + third;\n        const Int middle_right = right - third;\n        if\
    \ (f(middle_left) < f(middle_right)) {\n            left = middle_left + 1;\n\
    \        } else {\n            right = middle_right;\n        }\n    }\n\n   \
    \ Int best = left;\n    auto best_value = f(best);\n    for (Int x = left + 1;\
    \ x < right; ++x) {\n        auto value = f(x);\n        if (best_value < value)\
    \ {\n            best = x;\n            best_value = value;\n        }\n    }\n\
    \    return best;\n}\n\ntemplate <class F>\ndouble real_ternary_search_argmin(double\
    \ left, double right, F f, int iterations = 100) {\n    assert(left <= right);\n\
    \    assert(0 <= iterations);\n    for (int i = 0; i < iterations; ++i) {\n  \
    \      const double middle_left = (left * 2.0 + right) / 3.0;\n        const double\
    \ middle_right = (left + right * 2.0) / 3.0;\n        if (f(middle_right) < f(middle_left))\
    \ {\n            left = middle_left;\n        } else {\n            right = middle_right;\n\
    \        }\n    }\n    return (left + right) / 2.0;\n}\n\ntemplate <class F>\n\
    double real_ternary_search_argmax(double left, double right, F f, int iterations\
    \ = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n    for\
    \ (int i = 0; i < iterations; ++i) {\n        const double middle_left = (left\
    \ * 2.0 + right) / 3.0;\n        const double middle_right = (left + right * 2.0)\
    \ / 3.0;\n        if (f(middle_left) < f(middle_right)) {\n            left =\
    \ middle_left;\n        } else {\n            right = middle_right;\n        }\n\
    \    }\n    return (left + right) / 2.0;\n}\n\n}  // namespace algo\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ALGO_SEARCH_TERNARY_SEARCH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/search/ternary_search.hpp
  requiredBy:
  - algo/search/all.hpp
  - algo/all.hpp
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/search/ternary_search.test.cpp
documentation_of: algo/search/ternary_search.hpp
layout: document
title: Ternary Search
---

## Overview

Ternary-search helpers find an argument of a unimodal function. Integer
functions search a half-open range `[left, right)` and return the smallest
optimal argument. Real functions search a closed interval approximately and
return the midpoint of the final interval.

The public namespace is `m1une::algo`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `ternary_search_argmin(left, right, f)` | Returns an integer argument minimizing `f` on `[left, right)`. | $O(\log N)$ evaluations |
| `ternary_search_argmax(left, right, f)` | Returns an integer argument maximizing `f` on `[left, right)`. | $O(\log N)$ evaluations |
| `real_ternary_search_argmin(left, right, f, iterations = 100)` | Returns an approximate real minimizer. | $O(\text{iterations})$ evaluations |
| `real_ternary_search_argmax(left, right, f, iterations = 100)` | Returns an approximate real maximizer. | $O(\text{iterations})$ evaluations |

The integer range must be nonempty. The function must be unimodal in the
requested direction.

## Example

```cpp
#include "algo/search/ternary_search.hpp"

#include <iostream>

int main() {
    auto f = [](long long x) {
        return (x - 7) * (x - 7) + 3;
    };
    long long x = m1une::algo::ternary_search_argmin<long long>(-100, 101, f);
    std::cout << x << '\n';
}
```
