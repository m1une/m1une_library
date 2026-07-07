---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/combination.hpp
    title: Combination Masks
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/gray_code.hpp
    title: Gray Code
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/submask.hpp
    title: Submask Enumeration
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
  bundledCode: "#line 1 \"algo/enumeration/all.hpp\"\n\n\n\n#line 1 \"algo/enumeration/combination.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace m1une {\nnamespace algo {\n\n\
    namespace internal {\n\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
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
    \n\n#line 1 \"algo/enumeration/gray_code.hpp\"\n\n\n\n#line 6 \"algo/enumeration/gray_code.hpp\"\
    \n#include <cstddef>\n#line 10 \"algo/enumeration/gray_code.hpp\"\n#include <vector>\n\
    \nnamespace m1une {\nnamespace algo {\n\n// Converts a binary value to its binary-reflected\
    \ Gray code.\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nconstexpr UInt gray_encode(UInt value) noexcept {\n    return value\
    \ ^ (value >> 1);\n}\n\n// Converts a binary-reflected Gray code to the corresponding\
    \ binary value.\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nconstexpr UInt gray_decode(UInt code) noexcept {\n    for (int shift\
    \ = 1; shift < std::numeric_limits<UInt>::digits;\n         shift <<= 1) {\n \
    \       code ^= code >> shift;\n    }\n    return code;\n}\n\n// Returns all bit_count-bit\
    \ binary-reflected Gray codes in traversal order.\ntemplate <std::unsigned_integral\
    \ UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\n\
    std::vector<UInt> gray_code_sequence(int bit_count) {\n    constexpr int uint_digits\
    \ = std::numeric_limits<UInt>::digits;\n    constexpr int size_digits = std::numeric_limits<std::size_t>::digits;\n\
    \    assert(0 <= bit_count);\n    assert(bit_count <= uint_digits);\n    assert(bit_count\
    \ < size_digits);\n    if (bit_count < 0 || uint_digits < bit_count || size_digits\
    \ <= bit_count) {\n        return {};\n    }\n\n    const std::size_t size = std::size_t(1)\
    \ << bit_count;\n    std::vector<UInt> result(size);\n    for (std::size_t index\
    \ = 0; index < size; ++index) {\n        result[index] = gray_encode(static_cast<UInt>(index));\n\
    \    }\n    return result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n\n#line 1 \"algo/enumeration/submask.hpp\"\n\n\n\n#line 8 \"algo/enumeration/submask.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\nnamespace internal {\n\ntemplate <std::unsigned_integral\
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
    \ algo\n}  // namespace m1une\n\n\n#line 7 \"algo/enumeration/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_ENUMERATION_ALL_HPP

    #define M1UNE_ALGO_ENUMERATION_ALL_HPP 1


    #include "combination.hpp"

    #include "gray_code.hpp"

    #include "submask.hpp"


    #endif  // M1UNE_ALGO_ENUMERATION_ALL_HPP

    '
  dependsOn:
  - algo/enumeration/combination.hpp
  - algo/enumeration/gray_code.hpp
  - algo/enumeration/submask.hpp
  isVerificationFile: false
  path: algo/enumeration/all.hpp
  requiredBy:
  - algo/all.hpp
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algo/enumeration/all.hpp
layout: document
title: Enumeration Algorithms All
---

## Overview

`algo/enumeration/all.hpp` includes helpers for traversing combinatorial state
spaces. The public namespace is `m1une::algo`.

## Included Headers

| Header | Contents |
| --- | --- |
| `algo/enumeration/gray_code.hpp` | Binary-reflected Gray-code encoding, decoding, and enumeration. |
| `algo/enumeration/submask.hpp` | Submask and supermask enumeration helpers. |
| `algo/enumeration/combination.hpp` | Fixed-size subset mask generation helpers. |
