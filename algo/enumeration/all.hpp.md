---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/gray_code.hpp
    title: Gray Code
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
  bundledCode: "#line 1 \"algo/enumeration/all.hpp\"\n\n\n\n#line 1 \"algo/enumeration/gray_code.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <limits>\n#include <type_traits>\n#include <vector>\n\n\
    namespace m1une {\nnamespace algo {\n\n// Converts a binary value to its binary-reflected\
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
    \n\n#line 5 \"algo/enumeration/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_ENUMERATION_ALL_HPP

    #define M1UNE_ALGO_ENUMERATION_ALL_HPP 1


    #include "gray_code.hpp"


    #endif  // M1UNE_ALGO_ENUMERATION_ALL_HPP

    '
  dependsOn:
  - algo/enumeration/gray_code.hpp
  isVerificationFile: false
  path: algo/enumeration/all.hpp
  requiredBy:
  - algo/all.hpp
  timestamp: '2026-07-07 21:49:48+09:00'
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
