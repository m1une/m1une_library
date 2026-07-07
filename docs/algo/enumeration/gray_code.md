---
title: Gray Code
documentation_of: ../../../algo/enumeration/gray_code.hpp
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
#include "algo/enumeration/gray_code.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::uint64_t> codes =
        m1une::algo::gray_code_sequence(3);
    for (std::uint64_t code : codes) std::cout << code << " ";
    std::cout << "\n"; // 0 1 3 2 6 7 5 4

    std::cout << m1une::algo::gray_decode(std::uint64_t(6)) << "\n"; // 4
}
```
