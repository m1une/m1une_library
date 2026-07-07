---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/search/bisect.hpp
    title: Bisect
  - icon: ':heavy_check_mark:'
    path: algo/search/ternary_search.hpp
    title: Ternary Search
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
    \ algo\n}  // namespace m1une\n\n\n#line 1 \"algo/search/ternary_search.hpp\"\n\
    \n\n\n#include <cassert>\n#include <concepts>\n\nnamespace m1une {\nnamespace\
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
    \ m1une\n\n\n#line 6 \"algo/search/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_SEARCH_ALL_HPP

    #define M1UNE_ALGO_SEARCH_ALL_HPP 1


    #include "bisect.hpp"

    #include "ternary_search.hpp"


    #endif  // M1UNE_ALGO_SEARCH_ALL_HPP

    '
  dependsOn:
  - algo/search/bisect.hpp
  - algo/search/ternary_search.hpp
  isVerificationFile: false
  path: algo/search/all.hpp
  requiredBy:
  - algo/all.hpp
  timestamp: '2026-07-07 22:10:04+09:00'
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
| `algo/search/ternary_search.hpp` | Integer and real ternary search helpers for unimodal functions. |
