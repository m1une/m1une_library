---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/search/bisect.hpp
    title: Bisect
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/search/all.hpp\"\n\n\n\n#line 1 \"algo/search/bisect.hpp\"\
    \n\n\n\n#include <numeric>\n\nnamespace m1une {\nnamespace algo {\n\ntemplate\
    \ <typename F>\nlong long first_true(long long ng, long long ok, F pred) {\n \
    \   auto distance = [](long long a, long long b) {\n        return a > b ? static_cast<__int128_t>(a)\
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
    \ algo\n}  // namespace m1une\n\n\n#line 5 \"algo/search/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_SEARCH_ALL_HPP

    #define M1UNE_ALGO_SEARCH_ALL_HPP 1


    #include "bisect.hpp"


    #endif  // M1UNE_ALGO_SEARCH_ALL_HPP

    '
  dependsOn:
  - algo/search/bisect.hpp
  isVerificationFile: false
  path: algo/search/all.hpp
  requiredBy:
  - algo/all.hpp
  timestamp: '2026-07-07 21:49:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algo/search/all.hpp
layout: document
title: Search Algorithms All
---

## Overview

`algo/search/all.hpp` includes generic search-over-answer helpers. The public
namespace is `m1une::algo`.

## Included Headers

| Header | Contents |
| --- | --- |
| `algo/search/bisect.hpp` | Integer and floating-point binary search helpers for monotone predicates. |
