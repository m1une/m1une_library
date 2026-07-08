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
    path: verify/algo/search/golden_section_search.test.cpp
    title: verify/algo/search/golden_section_search.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/search/golden_section_search.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <numeric>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace algo {\n\
    \nnamespace detail {\n\ntemplate <std::integral Int, class F, class Compare>\n\
    Int integer_golden_section_search(Int left, Int right, F f, Compare comp) {\n\
    \    assert(left < right);\n\n    using UInt = std::make_unsigned_t<Int>;\n  \
    \  using Uint128 = unsigned __int128;\n    const Uint128 n = static_cast<Uint128>(static_cast<UInt>(right)\
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
    \ namespace algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_SEARCH_GOLDEN_SECTION_SEARCH_HPP\n#define M1UNE_ALGO_SEARCH_GOLDEN_SECTION_SEARCH_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <numeric>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace algo {\n\
    \nnamespace detail {\n\ntemplate <std::integral Int, class F, class Compare>\n\
    Int integer_golden_section_search(Int left, Int right, F f, Compare comp) {\n\
    \    assert(left < right);\n\n    using UInt = std::make_unsigned_t<Int>;\n  \
    \  using Uint128 = unsigned __int128;\n    const Uint128 n = static_cast<Uint128>(static_cast<UInt>(right)\
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
    \ namespace algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_SEARCH_GOLDEN_SECTION_SEARCH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/search/golden_section_search.hpp
  requiredBy:
  - algo/search/all.hpp
  - algo/all.hpp
  timestamp: '2026-07-09 00:39:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/search/golden_section_search.test.cpp
documentation_of: algo/search/golden_section_search.hpp
layout: document
title: Golden Section Search
---

## Overview

Golden-section search finds an argument of a unimodal function. Integer
overloads search a half-open range `[left, right)` exactly and return the
smallest optimal argument. Real overloads search a closed interval
approximately and return the midpoint of the final bracket.

The integer implementation uses Fibonacci search, which is the finite-grid
version of golden-section search. After the two active points are initialized,
each contraction reuses one function value and needs only one new evaluation.
Previously queried integer points are reused in the final two-point check, so
the same integer argument is not evaluated twice.

The public namespace is `m1une::algo`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `template <std::integral Int, class F> Int golden_section_search_argmin(Int left, Int right, F f)` | Returns an integer argument minimizing `f` on `[left, right)`. | $O(\log N)$ evaluations |
| `template <std::integral Int, class F> Int golden_section_search_argmax(Int left, Int right, F f)` | Returns an integer argument maximizing `f` on `[left, right)`. | $O(\log N)$ evaluations |
| `template <class F> double golden_section_search_argmin(double left, double right, F f, int iterations = 100)` | Returns an approximate argument minimizing `f` on `[left, right]`. | $O(\text{iterations})$ evaluations |
| `template <class F> double golden_section_search_argmax(double left, double right, F f, int iterations = 100)` | Returns an approximate argument maximizing `f` on `[left, right]`. | $O(\text{iterations})$ evaluations |

For integer overloads, `left < right` is required. For real overloads,
`left <= right` and `iterations >= 0` are required. The function must be
unimodal in the requested direction, and its return values must be comparable
with `<`.

For real overloads, when `iterations` is zero, or when the interval has zero
width, the function object is not evaluated. Otherwise the first contraction
uses two evaluations, and each additional contraction uses one new evaluation.
Thus `iterations > 0` uses `iterations + 1` evaluations.

## Example

```cpp
#include "algo/search/golden_section_search.hpp"

#include <iostream>

int main() {
    auto f = [](long long x) {
        return (x - 7) * (x - 7) + 3;
    };
    long long x = m1une::algo::golden_section_search_argmin<long long>(-100, 101, f);
    std::cout << x << '\n';
}
```
