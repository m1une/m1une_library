---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: game/all.hpp
    title: Game Library
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/game/game_algorithms.test.cpp
    title: verify/game/game_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/game/nim_product.test.cpp
    title: verify/game/nim_product.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"game/nim_product.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <limits>\n\nnamespace m1une {\nnamespace\
    \ game {\nnamespace internal {\n\ninline uint64_t nim_product_small(uint64_t x,\
    \ uint64_t y) {\n    if (x < 2 || y < 2) return x * y;\n\n    int shift = 1;\n\
    \    const uint64_t largest = x | y;\n    while ((uint64_t(1) << (shift * 2))\
    \ <= largest) shift *= 2;\n    const uint64_t mask = (uint64_t(1) << shift) -\
    \ 1;\n    const uint64_t x_high = x >> shift;\n    const uint64_t x_low = x &\
    \ mask;\n    const uint64_t y_high = y >> shift;\n    const uint64_t y_low = y\
    \ & mask;\n\n    const uint64_t high_product = nim_product_small(x_high, y_high);\n\
    \    const uint64_t low_product = nim_product_small(x_low, y_low);\n    const\
    \ uint64_t mixed_product =\n        nim_product_small(x_high ^ x_low, y_high ^\
    \ y_low);\n    return ((mixed_product ^ low_product) << shift) ^ low_product\n\
    \           ^ nim_product_small(high_product, uint64_t(1) << (shift - 1));\n}\n\
    \ninline const std::array<uint8_t, 1 << 16>& nim_product_8_table() {\n    static\
    \ const auto table = [] {\n        std::array<uint8_t, 1 << 16> result{};\n  \
    \      for (int x = 0; x < 256; ++x) {\n            for (int y = 0; y < 256; ++y)\
    \ {\n                result[(x << 8) | y] = uint8_t(nim_product_small(x, y));\n\
    \            }\n        }\n        return result;\n    }();\n    return table;\n\
    }\n\ninline uint64_t nim_product_8(uint64_t x, uint64_t y) {\n    return nim_product_8_table()[(x\
    \ << 8) | y];\n}\n\ntemplate <int Bits>\ninline uint64_t nim_product_fixed(uint64_t\
    \ x, uint64_t y) {\n    if constexpr (Bits == 8) {\n        return nim_product_8(x,\
    \ y);\n    } else {\n        constexpr int shift = Bits / 2;\n        constexpr\
    \ uint64_t mask = (uint64_t(1) << shift) - 1;\n        const uint64_t x_high =\
    \ x >> shift;\n        const uint64_t x_low = x & mask;\n        const uint64_t\
    \ y_high = y >> shift;\n        const uint64_t y_low = y & mask;\n\n        const\
    \ uint64_t high_product =\n            nim_product_fixed<shift>(x_high, y_high);\n\
    \        const uint64_t low_product = nim_product_fixed<shift>(x_low, y_low);\n\
    \        const uint64_t mixed_product = nim_product_fixed<shift>(\n          \
    \  x_high ^ x_low,\n            y_high ^ y_low\n        );\n        return ((mixed_product\
    \ ^ low_product) << shift) ^ low_product\n               ^ nim_product_fixed<shift>(\n\
    \                   high_product,\n                   uint64_t(1) << (shift -\
    \ 1)\n               );\n    }\n}\n\n}  // namespace internal\n\ninline uint64_t\
    \ nim_product(uint64_t x, uint64_t y) {\n    return internal::nim_product_fixed<64>(x,\
    \ y);\n}\n\ninline uint64_t nim_power(uint64_t base, uint64_t exponent) {\n  \
    \  uint64_t result = 1;\n    while (exponent != 0) {\n        if (exponent & 1)\
    \ result = nim_product(result, base);\n        base = nim_product(base, base);\n\
    \        exponent >>= 1;\n    }\n    return result;\n}\n\ninline uint64_t nim_inverse(uint64_t\
    \ value) {\n    assert(value != 0);\n    return nim_power(value, std::numeric_limits<uint64_t>::max()\
    \ - 1);\n}\n\ninline uint64_t nim_quotient(uint64_t numerator, uint64_t denominator)\
    \ {\n    assert(denominator != 0);\n    return nim_product(numerator, nim_inverse(denominator));\n\
    }\n\n}  // namespace game\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GAME_NIM_PRODUCT_HPP\n#define M1UNE_GAME_NIM_PRODUCT_HPP 1\n\
    \n#include <array>\n#include <cassert>\n#include <cstdint>\n#include <limits>\n\
    \nnamespace m1une {\nnamespace game {\nnamespace internal {\n\ninline uint64_t\
    \ nim_product_small(uint64_t x, uint64_t y) {\n    if (x < 2 || y < 2) return\
    \ x * y;\n\n    int shift = 1;\n    const uint64_t largest = x | y;\n    while\
    \ ((uint64_t(1) << (shift * 2)) <= largest) shift *= 2;\n    const uint64_t mask\
    \ = (uint64_t(1) << shift) - 1;\n    const uint64_t x_high = x >> shift;\n   \
    \ const uint64_t x_low = x & mask;\n    const uint64_t y_high = y >> shift;\n\
    \    const uint64_t y_low = y & mask;\n\n    const uint64_t high_product = nim_product_small(x_high,\
    \ y_high);\n    const uint64_t low_product = nim_product_small(x_low, y_low);\n\
    \    const uint64_t mixed_product =\n        nim_product_small(x_high ^ x_low,\
    \ y_high ^ y_low);\n    return ((mixed_product ^ low_product) << shift) ^ low_product\n\
    \           ^ nim_product_small(high_product, uint64_t(1) << (shift - 1));\n}\n\
    \ninline const std::array<uint8_t, 1 << 16>& nim_product_8_table() {\n    static\
    \ const auto table = [] {\n        std::array<uint8_t, 1 << 16> result{};\n  \
    \      for (int x = 0; x < 256; ++x) {\n            for (int y = 0; y < 256; ++y)\
    \ {\n                result[(x << 8) | y] = uint8_t(nim_product_small(x, y));\n\
    \            }\n        }\n        return result;\n    }();\n    return table;\n\
    }\n\ninline uint64_t nim_product_8(uint64_t x, uint64_t y) {\n    return nim_product_8_table()[(x\
    \ << 8) | y];\n}\n\ntemplate <int Bits>\ninline uint64_t nim_product_fixed(uint64_t\
    \ x, uint64_t y) {\n    if constexpr (Bits == 8) {\n        return nim_product_8(x,\
    \ y);\n    } else {\n        constexpr int shift = Bits / 2;\n        constexpr\
    \ uint64_t mask = (uint64_t(1) << shift) - 1;\n        const uint64_t x_high =\
    \ x >> shift;\n        const uint64_t x_low = x & mask;\n        const uint64_t\
    \ y_high = y >> shift;\n        const uint64_t y_low = y & mask;\n\n        const\
    \ uint64_t high_product =\n            nim_product_fixed<shift>(x_high, y_high);\n\
    \        const uint64_t low_product = nim_product_fixed<shift>(x_low, y_low);\n\
    \        const uint64_t mixed_product = nim_product_fixed<shift>(\n          \
    \  x_high ^ x_low,\n            y_high ^ y_low\n        );\n        return ((mixed_product\
    \ ^ low_product) << shift) ^ low_product\n               ^ nim_product_fixed<shift>(\n\
    \                   high_product,\n                   uint64_t(1) << (shift -\
    \ 1)\n               );\n    }\n}\n\n}  // namespace internal\n\ninline uint64_t\
    \ nim_product(uint64_t x, uint64_t y) {\n    return internal::nim_product_fixed<64>(x,\
    \ y);\n}\n\ninline uint64_t nim_power(uint64_t base, uint64_t exponent) {\n  \
    \  uint64_t result = 1;\n    while (exponent != 0) {\n        if (exponent & 1)\
    \ result = nim_product(result, base);\n        base = nim_product(base, base);\n\
    \        exponent >>= 1;\n    }\n    return result;\n}\n\ninline uint64_t nim_inverse(uint64_t\
    \ value) {\n    assert(value != 0);\n    return nim_power(value, std::numeric_limits<uint64_t>::max()\
    \ - 1);\n}\n\ninline uint64_t nim_quotient(uint64_t numerator, uint64_t denominator)\
    \ {\n    assert(denominator != 0);\n    return nim_product(numerator, nim_inverse(denominator));\n\
    }\n\n}  // namespace game\n}  // namespace m1une\n\n#endif  // M1UNE_GAME_NIM_PRODUCT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: game/nim_product.hpp
  requiredBy:
  - game/all.hpp
  timestamp: '2026-08-24 02:00:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/nim_product.test.cpp
  - verify/game/game_algorithms.test.cpp
documentation_of: game/nim_product.hpp
layout: document
title: Nim Product
---

## Overview

Arithmetic on 64-bit nimbers. Nim addition is bitwise xor; `nim_product`
implements Conway's recursively defined nim multiplication. Together these
operations form the finite field with `2^64` elements.

The implementation recursively views a nimber as a quadratic extension and
uses a 256-by-256 byte lookup table at the leaves. This avoids a large
per-query table while keeping the fixed 64-bit multiplication fast enough for
batched queries.

## Functions

All functions are in namespace `m1une::game` and use `uint64_t`.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `uint64_t nim_product(uint64_t x, uint64_t y)` | Returns `x` nim-multiplied by `y`. | `O(1)` time and `O(1)` extra space per call |
| `uint64_t nim_power(uint64_t base, uint64_t exponent)` | Returns the nim-product power of `base`. The zeroth power is one. | `O(log exponent)` nim products |
| `uint64_t nim_inverse(uint64_t value)` | Returns the nonzero value's multiplicative inverse. | `O(64)` nim products |
| `uint64_t nim_quotient(uint64_t numerator, uint64_t denominator)` | Returns the nim-field quotient. | `O(64)` nim products |

The first operation that uses this header initializes a 64 KiB lookup table.
`nim_inverse` asserts that `value != 0`, and `nim_quotient` asserts that the
denominator is nonzero.

## Example

```cpp
#include "game/nim_product.hpp"
#include <cstdint>
#include <iostream>

int main() {
    uint64_t product = m1une::game::nim_product(4, 4);
    std::cout << product << '\n';  // 6

    uint64_t inverse = m1une::game::nim_inverse(7);
    std::cout << m1une::game::nim_product(7, inverse) << '\n';  // 1
}
```
