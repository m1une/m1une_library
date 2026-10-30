---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  - icon: ':warning:'
    path: algo/enumeration/all.hpp
    title: Enumeration Algorithms All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/algo/enumeration/combination.test.cpp
    title: verify/algo/enumeration/combination.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/enumeration/combination.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <cstdint>\n#include <limits>\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace algo {\n\nnamespace internal {\n\ntemplate <std::unsigned_integral\
    \ UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nUInt combination_low_bits(int\
    \ bit_count) {\n    constexpr int digits = std::numeric_limits<UInt>::digits;\n\
    \    assert(0 <= bit_count && bit_count <= digits);\n    if (bit_count == digits)\
    \ return ~UInt(0);\n    return (UInt(1) << bit_count) - UInt(1);\n}\n\n}  // namespace\
    \ internal\n\ntemplate <std::unsigned_integral UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nUInt first_combination_mask(int bit_count, int choose) {\n    constexpr\
    \ int digits = std::numeric_limits<UInt>::digits;\n    assert(0 <= choose && choose\
    \ <= bit_count && bit_count <= digits);\n    if (choose == 0) return UInt(0);\n\
    \    if (choose == bit_count) return internal::combination_low_bits<UInt>(bit_count);\n\
    \    return (UInt(1) << choose) - UInt(1);\n}\n\ntemplate <std::unsigned_integral\
    \ UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nbool next_combination_mask(UInt&\
    \ mask, int bit_count) {\n    const UInt universe = internal::combination_low_bits<UInt>(bit_count);\n\
    \    assert((mask & ~universe) == 0);\n    if (mask == 0) return false;\n\n  \
    \  const UInt lowest = mask & (~mask + UInt(1));\n    const UInt ripple = mask\
    \ + lowest;\n    if (ripple == 0 || (ripple & ~universe) != 0) return false;\n\
    \n    const UInt next = (((ripple ^ mask) >> 2) / lowest) | ripple;\n    if ((next\
    \ & ~universe) != 0) return false;\n    mask = next;\n    return true;\n}\n\n\
    template <std::unsigned_integral UInt = std::uint64_t, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_combination_mask(int bit_count, int choose, F f) {\n \
    \   constexpr int digits = std::numeric_limits<UInt>::digits;\n    assert(0 <=\
    \ choose && choose <= bit_count && bit_count <= digits);\n    UInt mask = first_combination_mask<UInt>(bit_count,\
    \ choose);\n    while (true) {\n        f(mask);\n        if (!next_combination_mask(mask,\
    \ bit_count)) break;\n    }\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_ALGO_ENUMERATION_COMBINATION_HPP\n#define M1UNE_ALGO_ENUMERATION_COMBINATION_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n#include <limits>\n\
    #include <type_traits>\n\nnamespace m1une {\nnamespace algo {\n\nnamespace internal\
    \ {\n\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nUInt combination_low_bits(int bit_count) {\n    constexpr int digits\
    \ = std::numeric_limits<UInt>::digits;\n    assert(0 <= bit_count && bit_count\
    \ <= digits);\n    if (bit_count == digits) return ~UInt(0);\n    return (UInt(1)\
    \ << bit_count) - UInt(1);\n}\n\n}  // namespace internal\n\ntemplate <std::unsigned_integral\
    \ UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\n\
    UInt first_combination_mask(int bit_count, int choose) {\n    constexpr int digits\
    \ = std::numeric_limits<UInt>::digits;\n    assert(0 <= choose && choose <= bit_count\
    \ && bit_count <= digits);\n    if (choose == 0) return UInt(0);\n    if (choose\
    \ == bit_count) return internal::combination_low_bits<UInt>(bit_count);\n    return\
    \ (UInt(1) << choose) - UInt(1);\n}\n\ntemplate <std::unsigned_integral UInt>\n\
    requires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nbool next_combination_mask(UInt&\
    \ mask, int bit_count) {\n    const UInt universe = internal::combination_low_bits<UInt>(bit_count);\n\
    \    assert((mask & ~universe) == 0);\n    if (mask == 0) return false;\n\n  \
    \  const UInt lowest = mask & (~mask + UInt(1));\n    const UInt ripple = mask\
    \ + lowest;\n    if (ripple == 0 || (ripple & ~universe) != 0) return false;\n\
    \n    const UInt next = (((ripple ^ mask) >> 2) / lowest) | ripple;\n    if ((next\
    \ & ~universe) != 0) return false;\n    mask = next;\n    return true;\n}\n\n\
    template <std::unsigned_integral UInt = std::uint64_t, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_combination_mask(int bit_count, int choose, F f) {\n \
    \   constexpr int digits = std::numeric_limits<UInt>::digits;\n    assert(0 <=\
    \ choose && choose <= bit_count && bit_count <= digits);\n    UInt mask = first_combination_mask<UInt>(bit_count,\
    \ choose);\n    while (true) {\n        f(mask);\n        if (!next_combination_mask(mask,\
    \ bit_count)) break;\n    }\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n#endif  // M1UNE_ALGO_ENUMERATION_COMBINATION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/enumeration/combination.hpp
  requiredBy:
  - algo/enumeration/all.hpp
  - algo/all.hpp
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/enumeration/combination.test.cpp
documentation_of: algo/enumeration/combination.hpp
layout: document
title: Combination Masks
---

## Overview

This header generates fixed-size subsets as bitmasks. The public namespace is
`m1une::algo`.

`UInt` must be an unsigned integral type other than `bool`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `first_combination_mask<UInt>(bit_count, choose)` | Returns the smallest mask with `choose` bits among `bit_count` bits. | $O(1)$ |
| `next_combination_mask(mask, bit_count)` | Advances `mask` to the next mask with the same popcount; returns false when none exists. | $O(1)$ |
| `for_each_combination_mask<UInt>(bit_count, choose, f)` | Calls `f(mask)` for every `choose`-subset of `[0, bit_count)`. | $O(\binom{B}{K})$ |

Masks are generated in increasing numeric order.

## Example

```cpp
#include "algo/enumeration/combination.hpp"

#include <cstdint>
#include <vector>

int main() {
    std::vector<std::uint64_t> masks;
    m1une::algo::for_each_combination_mask(5, 3, [&](std::uint64_t mask) {
        masks.push_back(mask);
    });
}
```
