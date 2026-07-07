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
    path: verify/algo/enumeration/submask.test.cpp
    title: verify/algo/enumeration/submask.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/enumeration/submask.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <limits>\n#include <type_traits>\n\nnamespace m1une\
    \ {\nnamespace algo {\n\nnamespace internal {\n\ntemplate <std::unsigned_integral\
    \ UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nUInt submask_low_bits(int\
    \ bit_count) {\n    constexpr int digits = std::numeric_limits<UInt>::digits;\n\
    \    assert(0 <= bit_count && bit_count <= digits);\n    if (bit_count == digits)\
    \ return ~UInt(0);\n    return (UInt(1) << bit_count) - UInt(1);\n}\n\n}  // namespace\
    \ internal\n\ntemplate <std::unsigned_integral UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_submask(UInt mask, F f) {\n    UInt submask = mask;\n\
    \    while (true) {\n        f(submask);\n        if (submask == 0) break;\n \
    \       submask = (submask - 1) & mask;\n    }\n}\n\ntemplate <std::unsigned_integral\
    \ UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nvoid\
    \ for_each_nonzero_submask(UInt mask, F f) {\n    for (UInt submask = mask; submask\
    \ != 0; submask = (submask - 1) & mask) {\n        f(submask);\n    }\n}\n\ntemplate\
    \ <std::unsigned_integral UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_supermask(UInt mask, int bit_count, F f) {\n    const\
    \ UInt universe = internal::submask_low_bits<UInt>(bit_count);\n    assert((mask\
    \ & ~universe) == 0);\n    const UInt free_bits = universe ^ mask;\n    for_each_submask(free_bits,\
    \ [&](UInt added_bits) {\n        f(mask | added_bits);\n    });\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_ENUMERATION_SUBMASK_HPP\n#define M1UNE_ALGO_ENUMERATION_SUBMASK_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <limits>\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace algo {\n\nnamespace internal {\n\ntemplate <std::unsigned_integral\
    \ UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nUInt submask_low_bits(int\
    \ bit_count) {\n    constexpr int digits = std::numeric_limits<UInt>::digits;\n\
    \    assert(0 <= bit_count && bit_count <= digits);\n    if (bit_count == digits)\
    \ return ~UInt(0);\n    return (UInt(1) << bit_count) - UInt(1);\n}\n\n}  // namespace\
    \ internal\n\ntemplate <std::unsigned_integral UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_submask(UInt mask, F f) {\n    UInt submask = mask;\n\
    \    while (true) {\n        f(submask);\n        if (submask == 0) break;\n \
    \       submask = (submask - 1) & mask;\n    }\n}\n\ntemplate <std::unsigned_integral\
    \ UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nvoid\
    \ for_each_nonzero_submask(UInt mask, F f) {\n    for (UInt submask = mask; submask\
    \ != 0; submask = (submask - 1) & mask) {\n        f(submask);\n    }\n}\n\ntemplate\
    \ <std::unsigned_integral UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_supermask(UInt mask, int bit_count, F f) {\n    const\
    \ UInt universe = internal::submask_low_bits<UInt>(bit_count);\n    assert((mask\
    \ & ~universe) == 0);\n    const UInt free_bits = universe ^ mask;\n    for_each_submask(free_bits,\
    \ [&](UInt added_bits) {\n        f(mask | added_bits);\n    });\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_ENUMERATION_SUBMASK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/enumeration/submask.hpp
  requiredBy:
  - algo/enumeration/all.hpp
  - algo/all.hpp
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/enumeration/submask.test.cpp
documentation_of: algo/enumeration/submask.hpp
layout: document
title: Submask Enumeration
---

## Overview

This header wraps common bitmask loops for submasks and supermasks. The public
namespace is `m1une::algo`.

`UInt` must be an unsigned integral type other than `bool`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `for_each_submask(mask, f)` | Calls `f(submask)` for every submask of `mask`, including zero. | $O(2^K)$ |
| `for_each_nonzero_submask(mask, f)` | Calls `f(submask)` for every nonzero submask of `mask`. | $O(2^K)$ |
| `for_each_supermask(mask, bit_count, f)` | Calls `f(supermask)` for every supermask within `bit_count` bits. | $O(2^{B-K})$ |

Here $K$ is the popcount of `mask`, and $B$ is `bit_count`.
Submasks are generated in descending numeric order. Supermasks are generated by
descending order of the free added bits.

## Example

```cpp
#include "algo/enumeration/submask.hpp"

#include <cstdint>

int main() {
    std::uint32_t mask = 0b1011;
    int count = 0;
    m1une::algo::for_each_nonzero_submask(mask, [&](std::uint32_t submask) {
        (void)submask;
        ++count;
    });
}
```
