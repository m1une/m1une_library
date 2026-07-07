---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/gray_code.test.cpp
    title: verify/math/gray_code.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/gray_code.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <concepts>\n#include <cstddef>\n#include <cstdint>\n#include <limits>\n#include\
    \ <type_traits>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\n\
    // Converts a binary value to its binary-reflected Gray code.\ntemplate <std::unsigned_integral\
    \ UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nconstexpr UInt\
    \ gray_encode(UInt value) noexcept {\n    return value ^ (value >> 1);\n}\n\n\
    // Converts a binary-reflected Gray code to the corresponding binary value.\n\
    template <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
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
    \    }\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_MATH_GRAY_CODE_HPP\n#define M1UNE_MATH_GRAY_CODE_HPP 1\n\n\
    #include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <cstdint>\n\
    #include <limits>\n#include <type_traits>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace math {\n\n// Converts a binary value to its binary-reflected Gray\
    \ code.\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
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
    \    }\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\
    \n#endif  // M1UNE_MATH_GRAY_CODE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/gray_code.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-03 14:55:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/gray_code.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/gray_code.hpp
layout: document
title: Gray Code
---

## Overview

This header converts between nonnegative binary integers and binary-reflected
Gray codes. Consecutive values in Gray-code order differ in exactly one bit,
which is useful for subset enumeration when an update can be applied one bit at
a time.

## Functions

```cpp
template <std::unsigned_integral UInt>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
constexpr UInt gray_encode(UInt value) noexcept;

template <std::unsigned_integral UInt>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
constexpr UInt gray_decode(UInt code) noexcept;

template <std::unsigned_integral UInt = std::uint64_t>
requires(!std::same_as<std::remove_cv_t<UInt>, bool>)
std::vector<UInt> gray_code_sequence(int bit_count);
```

`UInt` may be any standard unsigned integral type except `bool`.
The conversion functions do not mutate their arguments.

| Function | Description | Complexity |
| --- | --- | --- |
| `gray_encode(value)` | Returns the binary-reflected Gray code of `value`. | $O(1)$ time and memory. |
| `gray_decode(code)` | Returns the binary value represented by `code`. | $O(\log W)$ time and $O(1)$ memory. |
| `gray_code_sequence<UInt>(bit_count)` | Returns all $2^\text{bit_count}$ codes in traversal order. | $O(2^\text{bit_count})$ time and memory. |

Here $W$ is the number of value bits in `UInt`. For sequence generation,
`bit_count` must be nonnegative, must fit in `UInt`, and must be smaller than
the number of value bits in `std::size_t`. The zero-bit sequence contains one
value: zero. For every positive valid bit count, the sequence is cyclic: its
last and first values also differ in exactly one bit.

## Example

```cpp
#include "math/gray_code.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::uint64_t> codes =
        m1une::math::gray_code_sequence(3);
    for (std::uint64_t code : codes) std::cout << code << " ";
    std::cout << "\n"; // 0 1 3 2 6 7 5 4

    std::cout << m1une::math::gray_decode(std::uint64_t(6)) << "\n"; // 4
}
```
