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
    path: verify/algo/search/bisect.test.cpp
    title: verify/algo/search/bisect.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/search/bisect.hpp\"\n\n\n\n#include <numeric>\n\nnamespace\
    \ m1une {\nnamespace algo {\n\ntemplate <typename F>\nlong long first_true(long\
    \ long ng, long long ok, F pred) {\n    auto distance = [](long long a, long long\
    \ b) {\n        return a > b ? static_cast<__int128_t>(a) - b : static_cast<__int128_t>(b)\
    \ - a;\n    };\n    while (distance(ng, ok) > 1) {\n        long long mid = std::midpoint(ng,\
    \ ok);\n        if (pred(mid)) {\n            ok = mid;\n        } else {\n  \
    \          ng = mid;\n        }\n    }\n    return ok;\n}\n\ntemplate <typename\
    \ F>\nlong long last_true(long long ok, long long ng, F pred) {\n    auto distance\
    \ = [](long long a, long long b) {\n        return a > b ? static_cast<__int128_t>(a)\
    \ - b : static_cast<__int128_t>(b) - a;\n    };\n    while (distance(ok, ng) >\
    \ 1) {\n        long long mid = std::midpoint(ok, ng);\n        if (pred(mid))\
    \ {\n            ok = mid;\n        } else {\n            ng = mid;\n        }\n\
    \    }\n    return ok;\n}\n\ntemplate <typename F>\ndouble real_first_true(double\
    \ ng, double ok, F pred, int iterations = 80) {\n    for (int i = 0; i < iterations;\
    \ ++i) {\n        double mid = (ng + ok) / 2.0;\n        if (pred(mid)) {\n  \
    \          ok = mid;\n        } else {\n            ng = mid;\n        }\n   \
    \ }\n    return ok;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_SEARCH_BISECT_HPP\n#define M1UNE_ALGO_SEARCH_BISECT_HPP\
    \ 1\n\n#include <numeric>\n\nnamespace m1une {\nnamespace algo {\n\ntemplate <typename\
    \ F>\nlong long first_true(long long ng, long long ok, F pred) {\n    auto distance\
    \ = [](long long a, long long b) {\n        return a > b ? static_cast<__int128_t>(a)\
    \ - b : static_cast<__int128_t>(b) - a;\n    };\n    while (distance(ng, ok) >\
    \ 1) {\n        long long mid = std::midpoint(ng, ok);\n        if (pred(mid))\
    \ {\n            ok = mid;\n        } else {\n            ng = mid;\n        }\n\
    \    }\n    return ok;\n}\n\ntemplate <typename F>\nlong long last_true(long long\
    \ ok, long long ng, F pred) {\n    auto distance = [](long long a, long long b)\
    \ {\n        return a > b ? static_cast<__int128_t>(a) - b : static_cast<__int128_t>(b)\
    \ - a;\n    };\n    while (distance(ok, ng) > 1) {\n        long long mid = std::midpoint(ok,\
    \ ng);\n        if (pred(mid)) {\n            ok = mid;\n        } else {\n  \
    \          ng = mid;\n        }\n    }\n    return ok;\n}\n\ntemplate <typename\
    \ F>\ndouble real_first_true(double ng, double ok, F pred, int iterations = 80)\
    \ {\n    for (int i = 0; i < iterations; ++i) {\n        double mid = (ng + ok)\
    \ / 2.0;\n        if (pred(mid)) {\n            ok = mid;\n        } else {\n\
    \            ng = mid;\n        }\n    }\n    return ok;\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_SEARCH_BISECT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/search/bisect.hpp
  requiredBy:
  - algo/search/all.hpp
  - algo/all.hpp
  timestamp: '2026-07-07 21:49:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/search/bisect.test.cpp
documentation_of: algo/search/bisect.hpp
layout: document
title: Bisect
---

## Overview

Binary search helpers for monotone predicates. The integer functions use explicit `ok` and `ng` sentinels, so they work for both increasing and decreasing search directions.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `long long first_true(long long ng, long long ok, F pred)` | Given `pred(ng) == false` and `pred(ok) == true`, returns the boundary `ok`. | $O(\log |ok - ng|)$ |
| `long long last_true(long long ok, long long ng, F pred)` | Given `pred(ok) == true` and `pred(ng) == false`, returns the boundary `ok`. | $O(\log |ok - ng|)$ |
| `double real_first_true(double ng, double ok, F pred, int iterations = 80)` | Floating-point version of `first_true` with a fixed iteration count. | $O(\text{iterations})$ |

## Example

```cpp
#include "algo/search/bisect.hpp"
#include <iostream>

int main() {
    long long n = 100;
    long long x = m1une::algo::first_true(0, n + 1, [&](long long v) {
        return v * v >= n;
    });
    std::cout << x << "\n";
}
```
