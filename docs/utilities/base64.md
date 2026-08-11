---
title: Base64 Sequence Encoding
documentation_of: ../../utilities/base64.hpp
---

## Overview

This header packs a sequence of fixed-width nonnegative integers into a compact
Base64 string. It is intended for embedding precomputed tables, test data, or
other numeric constants directly in competitive-programming source code.

```cpp
#include "utilities/base64.hpp"
```

All names are in `m1une::utilities`. The alphabet is the RFC 4648 alphabet
`A-Z`, `a-z`, `0-9`, `+`, `/`, exposed as `base64_alphabet`. Bits are written
most-significant first. The final Base64 digit is padded with zero bits, but `=`
characters are omitted to keep the result short. Consequently, encoding bytes
with `bit_width = 8` produces ordinary unpadded Base64.

## Interface

```cpp
template <class Sequence>
std::string to_base64(const Sequence& values, int bit_width);

template <std::integral Integer>
std::optional<std::vector<Integer>> checked_from_base64(
    std::string_view encoded,
    std::size_t count,
    int bit_width);

template <std::integral Integer>
std::vector<Integer> from_base64(
    std::string_view encoded,
    std::size_t count,
    int bit_width);
```

The sequence value type and `Integer` may be any standard integral type except
`bool`. Values must be nonnegative and fit in `bit_width` bits. The width must be
between 1 and the number of non-sign bits in the integer type.

| Function | Description | Complexity |
| --- | --- | --- |
| `to_base64(values, bit_width)` | Packs all values and returns the unpadded Base64 text. | $O(N\lceil B/6\rceil)$ time and $O(\lceil NB / 6\rceil)$ output memory. |
| `checked_from_base64<Integer>(text, count, bit_width)` | Decodes exactly `count` values, or returns `nullopt` if the text has an invalid character, wrong length, or nonzero padding bits. | $O(N\lceil B/6\rceil)$ time and $O(N)$ output memory. |
| `from_base64<Integer>(text, count, bit_width)` | Decodes a known-valid embedded string; validity is asserted. | $O(N\lceil B/6\rceil)$ time and $O(N)$ output memory. |

Here $N$ is the sequence length and $B$ is `bit_width`. The implementation
processes up to six bits per inner-loop iteration, so its running time is also
linear in the encoded size.

The decoder needs `count` because an unpadded final character does not uniquely
identify how many data bits it contains. For example, both a one-value sequence
with width 5 and one with width 6 occupy one Base64 character.

## Example

For values below 64, use six bits per value. Each number then occupies exactly
one character:

```cpp
#include "utilities/base64.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> original = {3, 1, 4, 1, 5, 9};
    std::string embedded = m1une::utilities::to_base64(original, 6);
    // embedded is "DBEBFJ"; paste that string into the submitted program.

    std::vector<int> restored =
        m1une::utilities::from_base64<int>("DBEBFJ", 6, 6);
    for (int value : restored) std::cout << value << ' ';
}
```

Choose the smallest fixed width that contains every value. For example, values
in `[0, 1024)` need 10 bits each, so every three values occupy exactly five
Base64 characters.
