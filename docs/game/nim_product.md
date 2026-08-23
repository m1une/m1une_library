---
title: Nim Product
documentation_of: ../../game/nim_product.hpp
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
