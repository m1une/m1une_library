---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/search/bisect.hpp
    title: Bisect
  - icon: ':heavy_check_mark:'
    path: algo/search/golden_section_search.hpp
    title: Golden Section Search
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
    \ algo\n}  // namespace m1une\n\n\n#line 1 \"algo/search/golden_section_search.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#line 7 \"algo/search/golden_section_search.hpp\"\
    \n#include <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace algo {\n\nnamespace detail {\n\ntemplate <std::integral Int, class\
    \ F, class Compare>\nInt integer_golden_section_search(Int left, Int right, F\
    \ f, Compare comp) {\n    assert(left < right);\n\n    using UInt = std::make_unsigned_t<Int>;\n\
    \    using Uint128 = unsigned __int128;\n    const Uint128 n = static_cast<Uint128>(static_cast<UInt>(right)\
    \ - static_cast<UInt>(left));\n\n    auto add_offset = [left](Uint128 offset)\
    \ -> Int {\n        if constexpr (std::signed_integral<Int>) {\n            if\
    \ (left < 0) {\n                const Uint128 negative_count = static_cast<Uint128>(-(left\
    \ + 1)) + 1;\n                if (offset < negative_count) {\n               \
    \     return static_cast<Int>(left + static_cast<Int>(offset));\n            \
    \    }\n                return static_cast<Int>(offset - negative_count);\n  \
    \          }\n        }\n        return static_cast<Int>(left + static_cast<Int>(offset));\n\
    \    };\n\n    using Value = std::decay_t<decltype(f(left))>;\n    struct Evaluated\
    \ {\n        Uint128 pos;\n        const Value* value;\n    };\n\n    Uint128\
    \ fib0 = 1;\n    Uint128 fib1 = 1;\n    Uint128 fib2 = 2;\n    int k = 2;\n  \
    \  while (fib2 < n) {\n        fib0 = fib1;\n        fib1 = fib2;\n        fib2\
    \ = fib0 + fib1;\n        ++k;\n    }\n\n    std::vector<std::pair<Uint128, Value>>\
    \ cache;\n    cache.reserve(static_cast<unsigned>(k) + 4);\n\n    auto find_cached\
    \ = [&](Uint128 pos) -> const Value* {\n        for (const auto& [cached_pos,\
    \ value] : cache) {\n            if (cached_pos == pos) return &value;\n     \
    \   }\n        return nullptr;\n    };\n\n    auto advance_fibonacci = [&]() {\n\
    \        const Uint128 old0 = fib0;\n        const Uint128 old1 = fib1;\n    \
    \    fib0 = old1 - old0;\n        fib1 = old0;\n        fib2 = old1;\n       \
    \ --k;\n    };\n\n    auto eval = [&](Uint128 pos) -> Evaluated {\n        if\
    \ (pos >= n) return Evaluated{pos, nullptr};\n        if (const Value* value =\
    \ find_cached(pos)) return Evaluated{pos, value};\n        cache.emplace_back(pos,\
    \ f(add_offset(pos)));\n        return Evaluated{pos, &cache.back().second};\n\
    \    };\n\n    auto get_value = [&](Uint128 pos) -> const Value& {\n        if\
    \ (const Value* value = find_cached(pos)) return *value;\n        cache.emplace_back(pos,\
    \ f(add_offset(pos)));\n        return cache.back().second;\n    };\n\n    auto\
    \ scan = [&](Uint128 scan_left, Uint128 scan_right) -> Int {\n        Int best\
    \ = add_offset(scan_left);\n        const Value* best_value = &get_value(scan_left);\n\
    \        for (Uint128 pos = scan_left + 1; pos <= scan_right; ++pos) {\n     \
    \       Int x = add_offset(pos);\n            const Value& value = get_value(pos);\n\
    \            if (comp(value, *best_value)) {\n                best = x;\n    \
    \            best_value = &value;\n            }\n        }\n        return best;\n\
    \    };\n\n    if (n <= 3) return scan(0, n - 1);\n\n    auto better = [&](const\
    \ Evaluated& a, const Evaluated& b) -> bool {\n        if ((a.value != nullptr)\
    \ != (b.value != nullptr)) return a.value != nullptr;\n        if (a.value ==\
    \ nullptr) return false;\n        return comp(*a.value, *b.value);\n    };\n\n\
    \    Uint128 left_pos = 0;\n    Uint128 right_pos = fib2 - 1;\n    Uint128 x1\
    \ = left_pos + fib0 - 1;\n    Uint128 x2 = left_pos + fib1 - 1;\n    Evaluated\
    \ y1 = eval(x1);\n    Evaluated y2 = eval(x2);\n\n    while (k > 2) {\n      \
    \  if (better(y2, y1)) {\n            left_pos = x1 + 1;\n            x1 = x2;\n\
    \            y1 = y2;\n            advance_fibonacci();\n            if (k ==\
    \ 2) break;\n            x2 = left_pos + fib1 - 1;\n            y2 = eval(x2);\n\
    \        } else {\n            right_pos = x2;\n            x2 = x1;\n       \
    \     y2 = y1;\n            advance_fibonacci();\n            if (k == 2) break;\n\
    \            x1 = left_pos + fib0 - 1;\n            y1 = eval(x1);\n        }\n\
    \    }\n\n    const Uint128 last_valid = n - 1;\n    if (right_pos > last_valid)\
    \ right_pos = last_valid;\n    assert(left_pos <= right_pos);\n    return scan(left_pos,\
    \ right_pos);\n}\n\n}  // namespace detail\n\ntemplate <std::integral Int, class\
    \ F>\nInt golden_section_search_argmin(Int left, Int right, F f) {\n    return\
    \ detail::integer_golden_section_search(left, right, f, [](const auto& a, const\
    \ auto& b) { return a < b; });\n}\n\ntemplate <std::integral Int, class F>\nInt\
    \ golden_section_search_argmax(Int left, Int right, F f) {\n    return detail::integer_golden_section_search(left,\
    \ right, f, [](const auto& a, const auto& b) { return b < a; });\n}\n\ntemplate\
    \ <class F>\ndouble golden_section_search_argmin(double left, double right, F\
    \ f, int iterations = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n\
    \    if (left == right || iterations == 0) return std::midpoint(left, right);\n\
    \n    constexpr double inv_phi = 0.6180339887498948482045868343656381177203;\n\
    \    double x1 = right - (right - left) * inv_phi;\n    double x2 = left + (right\
    \ - left) * inv_phi;\n    auto y1 = f(x1);\n    auto y2 = f(x2);\n\n    for (int\
    \ i = 1; i < iterations; ++i) {\n        if (y2 < y1) {\n            left = x1;\n\
    \            x1 = x2;\n            y1 = std::move(y2);\n            x2 = left\
    \ + (right - left) * inv_phi;\n            y2 = f(x2);\n        } else {\n   \
    \         right = x2;\n            x2 = x1;\n            y2 = std::move(y1);\n\
    \            x1 = right - (right - left) * inv_phi;\n            y1 = f(x1);\n\
    \        }\n    }\n\n    if (y2 < y1) {\n        left = x1;\n    } else {\n  \
    \      right = x2;\n    }\n    return std::midpoint(left, right);\n}\n\ntemplate\
    \ <class F>\ndouble golden_section_search_argmax(double left, double right, F\
    \ f, int iterations = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n\
    \    if (left == right || iterations == 0) return std::midpoint(left, right);\n\
    \n    constexpr double inv_phi = 0.6180339887498948482045868343656381177203;\n\
    \    double x1 = right - (right - left) * inv_phi;\n    double x2 = left + (right\
    \ - left) * inv_phi;\n    auto y1 = f(x1);\n    auto y2 = f(x2);\n\n    for (int\
    \ i = 1; i < iterations; ++i) {\n        if (y1 < y2) {\n            left = x1;\n\
    \            x1 = x2;\n            y1 = std::move(y2);\n            x2 = left\
    \ + (right - left) * inv_phi;\n            y2 = f(x2);\n        } else {\n   \
    \         right = x2;\n            x2 = x1;\n            y2 = std::move(y1);\n\
    \            x1 = right - (right - left) * inv_phi;\n            y1 = f(x1);\n\
    \        }\n    }\n\n    if (y1 < y2) {\n        left = x1;\n    } else {\n  \
    \      right = x2;\n    }\n    return std::midpoint(left, right);\n}\n\n}  //\
    \ namespace algo\n}  // namespace m1une\n\n\n#line 1 \"algo/search/ternary_search.hpp\"\
    \n\n\n\n#line 6 \"algo/search/ternary_search.hpp\"\n\nnamespace m1une {\nnamespace\
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
    \ m1une\n\n\n#line 7 \"algo/search/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_SEARCH_ALL_HPP

    #define M1UNE_ALGO_SEARCH_ALL_HPP 1


    #include "bisect.hpp"

    #include "golden_section_search.hpp"

    #include "ternary_search.hpp"


    #endif  // M1UNE_ALGO_SEARCH_ALL_HPP

    '
  dependsOn:
  - algo/search/bisect.hpp
  - algo/search/golden_section_search.hpp
  - algo/search/ternary_search.hpp
  isVerificationFile: false
  path: algo/search/all.hpp
  requiredBy:
  - algo/all.hpp
  timestamp: '2026-07-09 00:39:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algo/search/all.hpp
layout: document
title: Search Algorithms All
---

## Overview

`algo/search/all.hpp` includes generic search-over-answer and unimodal
optimization helpers. The public namespace is `m1une::algo`.

## Included Headers

| Header | Contents |
| --- | --- |
| `algo/search/bisect.hpp` | Integer and floating-point binary search helpers for monotone predicates. |
| `algo/search/golden_section_search.hpp` | Real golden-section search helpers for unimodal functions. |
| `algo/search/ternary_search.hpp` | Integer and real ternary search helpers for unimodal functions. |
