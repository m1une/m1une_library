---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/base64.test.cpp
    title: verify/utilities/base64.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/base64.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <concepts>\n#include <cstddef>\n#include <limits>\n#include\
    \ <optional>\n#include <ranges>\n#include <string>\n#include <string_view>\n#include\
    \ <type_traits>\n#include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\
    \ninline constexpr std::string_view base64_alphabet =\n    \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\"\
    ;\n\nnamespace detail {\n\ninline int base64_digit(char character) noexcept {\n\
    \    if ('A' <= character && character <= 'Z') return character - 'A';\n    if\
    \ ('a' <= character && character <= 'z') return character - 'a' + 26;\n    if\
    \ ('0' <= character && character <= '9') return character - '0' + 52;\n    if\
    \ (character == '+') return 62;\n    if (character == '/') return 63;\n    return\
    \ -1;\n}\n\ntemplate <class Integer>\nconcept Base64Integer =\n    std::integral<Integer>\
    \ &&\n    (!std::same_as<std::remove_cv_t<Integer>, bool>);\n\n}  // namespace\
    \ detail\n\n// Packs fixed-width nonnegative integers, most-significant bit first.\
    \ The last\n// Base64 digit is zero-padded on the right; '=' padding is intentionally\
    \ omitted.\ntemplate <class Sequence>\nrequires std::ranges::input_range<const\
    \ Sequence&> &&\n         detail::Base64Integer<std::ranges::range_value_t<Sequence>>\n\
    std::string to_base64(const Sequence& values, int bit_width) {\n    using Integer\
    \ = std::ranges::range_value_t<Sequence>;\n    using Unsigned = std::make_unsigned_t<Integer>;\n\
    \    constexpr int digits = std::numeric_limits<Integer>::digits;\n\n    assert(1\
    \ <= bit_width && bit_width <= digits);\n    if (bit_width < 1 || bit_width >\
    \ digits) return {};\n\n    std::string encoded;\n    if constexpr (std::ranges::sized_range<const\
    \ Sequence&>) {\n        std::size_t count = static_cast<std::size_t>(std::ranges::size(values));\n\
    \        constexpr std::size_t size_limit =\n            std::numeric_limits<std::size_t>::max();\n\
    \        if (count <= (size_limit - 5) / static_cast<unsigned>(bit_width)) {\n\
    \            encoded.reserve((count * static_cast<unsigned>(bit_width) + 5) /\
    \ 6);\n        }\n    }\n    unsigned buffer = 0;\n    int buffered_bits = 0;\n\
    \n    for (Integer value : values) {\n        if constexpr (std::signed_integral<Integer>)\
    \ {\n            assert(value >= 0);\n            if (value < 0) return {};\n\
    \        }\n        Unsigned unsigned_value = static_cast<Unsigned>(value);\n\
    \        if (bit_width < digits) {\n            assert((unsigned_value >> bit_width)\
    \ == 0);\n            if ((unsigned_value >> bit_width) != 0) return {};\n   \
    \     }\n\n        int remaining_bits = bit_width;\n        while (remaining_bits\
    \ > 0) {\n            int take = std::min(6 - buffered_bits, remaining_bits);\n\
    \            int shift = remaining_bits - take;\n            unsigned mask = (1U\
    \ << take) - 1;\n            unsigned part = static_cast<unsigned>((unsigned_value\
    \ >> shift) & mask);\n            buffer = (buffer << take) | part;\n        \
    \    buffered_bits += take;\n            remaining_bits -= take;\n\n         \
    \   if (buffered_bits == 6) {\n                encoded.push_back(base64_alphabet[buffer]);\n\
    \                buffer = 0;\n                buffered_bits = 0;\n           \
    \ }\n        }\n    }\n\n    if (buffered_bits != 0) {\n        encoded.push_back(base64_alphabet[buffer\
    \ << (6 - buffered_bits)]);\n    }\n    return encoded;\n}\n\n// Returns nullopt\
    \ unless encoded is the canonical encoding of exactly count\n// values with the\
    \ requested bit width.\ntemplate <detail::Base64Integer Integer>\nstd::optional<std::vector<Integer>>\
    \ checked_from_base64(\n    std::string_view encoded, std::size_t count, int bit_width)\
    \ {\n    constexpr int digits = std::numeric_limits<Integer>::digits;\n    if\
    \ (bit_width < 1 || bit_width > digits) return std::nullopt;\n\n    constexpr\
    \ std::size_t size_limit = std::numeric_limits<std::size_t>::max();\n    if (count\
    \ > (size_limit - 5) / static_cast<unsigned>(bit_width)) {\n        return std::nullopt;\n\
    \    }\n    std::size_t total_bits = count * static_cast<unsigned>(bit_width);\n\
    \    if (encoded.size() != (total_bits + 5) / 6) return std::nullopt;\n\n    using\
    \ Unsigned = std::make_unsigned_t<Integer>;\n    std::vector<Integer> values;\n\
    \    values.reserve(count);\n    std::size_t position = 0;\n    unsigned buffer\
    \ = 0;\n    int buffered_bits = 0;\n\n    for (std::size_t index = 0; index <\
    \ count; ++index) {\n        Unsigned value = 0;\n        int remaining_bits =\
    \ bit_width;\n        while (remaining_bits > 0) {\n            if (buffered_bits\
    \ == 0) {\n                int digit = detail::base64_digit(encoded[position++]);\n\
    \                if (digit < 0) return std::nullopt;\n                buffer =\
    \ static_cast<unsigned>(digit);\n                buffered_bits = 6;\n        \
    \    }\n\n            int take = std::min(buffered_bits, remaining_bits);\n  \
    \          int shift = buffered_bits - take;\n            unsigned mask = (1U\
    \ << take) - 1;\n            unsigned part = (buffer >> shift) & mask;\n     \
    \       value = static_cast<Unsigned>((value << take) | part);\n            buffered_bits\
    \ -= take;\n            remaining_bits -= take;\n        }\n        values.push_back(static_cast<Integer>(value));\n\
    \    }\n\n    if (buffered_bits != 0) {\n        unsigned mask = (1U << buffered_bits)\
    \ - 1;\n        if ((buffer & mask) != 0) return std::nullopt;\n    }\n    return\
    \ values;\n}\n\ntemplate <detail::Base64Integer Integer>\nstd::vector<Integer>\
    \ from_base64(std::string_view encoded, std::size_t count,\n                 \
    \                int bit_width) {\n    std::optional<std::vector<Integer>> result\
    \ =\n        checked_from_base64<Integer>(encoded, count, bit_width);\n    assert(result.has_value());\n\
    \    return result.value_or(std::vector<Integer>());\n}\n\n}  // namespace utilities\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_UTILITIES_BASE64_HPP\n#define M1UNE_UTILITIES_BASE64_HPP 1\n\
    \n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n\
    #include <limits>\n#include <optional>\n#include <ranges>\n#include <string>\n\
    #include <string_view>\n#include <type_traits>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace utilities {\n\ninline constexpr std::string_view base64_alphabet\
    \ =\n    \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\"\
    ;\n\nnamespace detail {\n\ninline int base64_digit(char character) noexcept {\n\
    \    if ('A' <= character && character <= 'Z') return character - 'A';\n    if\
    \ ('a' <= character && character <= 'z') return character - 'a' + 26;\n    if\
    \ ('0' <= character && character <= '9') return character - '0' + 52;\n    if\
    \ (character == '+') return 62;\n    if (character == '/') return 63;\n    return\
    \ -1;\n}\n\ntemplate <class Integer>\nconcept Base64Integer =\n    std::integral<Integer>\
    \ &&\n    (!std::same_as<std::remove_cv_t<Integer>, bool>);\n\n}  // namespace\
    \ detail\n\n// Packs fixed-width nonnegative integers, most-significant bit first.\
    \ The last\n// Base64 digit is zero-padded on the right; '=' padding is intentionally\
    \ omitted.\ntemplate <class Sequence>\nrequires std::ranges::input_range<const\
    \ Sequence&> &&\n         detail::Base64Integer<std::ranges::range_value_t<Sequence>>\n\
    std::string to_base64(const Sequence& values, int bit_width) {\n    using Integer\
    \ = std::ranges::range_value_t<Sequence>;\n    using Unsigned = std::make_unsigned_t<Integer>;\n\
    \    constexpr int digits = std::numeric_limits<Integer>::digits;\n\n    assert(1\
    \ <= bit_width && bit_width <= digits);\n    if (bit_width < 1 || bit_width >\
    \ digits) return {};\n\n    std::string encoded;\n    if constexpr (std::ranges::sized_range<const\
    \ Sequence&>) {\n        std::size_t count = static_cast<std::size_t>(std::ranges::size(values));\n\
    \        constexpr std::size_t size_limit =\n            std::numeric_limits<std::size_t>::max();\n\
    \        if (count <= (size_limit - 5) / static_cast<unsigned>(bit_width)) {\n\
    \            encoded.reserve((count * static_cast<unsigned>(bit_width) + 5) /\
    \ 6);\n        }\n    }\n    unsigned buffer = 0;\n    int buffered_bits = 0;\n\
    \n    for (Integer value : values) {\n        if constexpr (std::signed_integral<Integer>)\
    \ {\n            assert(value >= 0);\n            if (value < 0) return {};\n\
    \        }\n        Unsigned unsigned_value = static_cast<Unsigned>(value);\n\
    \        if (bit_width < digits) {\n            assert((unsigned_value >> bit_width)\
    \ == 0);\n            if ((unsigned_value >> bit_width) != 0) return {};\n   \
    \     }\n\n        int remaining_bits = bit_width;\n        while (remaining_bits\
    \ > 0) {\n            int take = std::min(6 - buffered_bits, remaining_bits);\n\
    \            int shift = remaining_bits - take;\n            unsigned mask = (1U\
    \ << take) - 1;\n            unsigned part = static_cast<unsigned>((unsigned_value\
    \ >> shift) & mask);\n            buffer = (buffer << take) | part;\n        \
    \    buffered_bits += take;\n            remaining_bits -= take;\n\n         \
    \   if (buffered_bits == 6) {\n                encoded.push_back(base64_alphabet[buffer]);\n\
    \                buffer = 0;\n                buffered_bits = 0;\n           \
    \ }\n        }\n    }\n\n    if (buffered_bits != 0) {\n        encoded.push_back(base64_alphabet[buffer\
    \ << (6 - buffered_bits)]);\n    }\n    return encoded;\n}\n\n// Returns nullopt\
    \ unless encoded is the canonical encoding of exactly count\n// values with the\
    \ requested bit width.\ntemplate <detail::Base64Integer Integer>\nstd::optional<std::vector<Integer>>\
    \ checked_from_base64(\n    std::string_view encoded, std::size_t count, int bit_width)\
    \ {\n    constexpr int digits = std::numeric_limits<Integer>::digits;\n    if\
    \ (bit_width < 1 || bit_width > digits) return std::nullopt;\n\n    constexpr\
    \ std::size_t size_limit = std::numeric_limits<std::size_t>::max();\n    if (count\
    \ > (size_limit - 5) / static_cast<unsigned>(bit_width)) {\n        return std::nullopt;\n\
    \    }\n    std::size_t total_bits = count * static_cast<unsigned>(bit_width);\n\
    \    if (encoded.size() != (total_bits + 5) / 6) return std::nullopt;\n\n    using\
    \ Unsigned = std::make_unsigned_t<Integer>;\n    std::vector<Integer> values;\n\
    \    values.reserve(count);\n    std::size_t position = 0;\n    unsigned buffer\
    \ = 0;\n    int buffered_bits = 0;\n\n    for (std::size_t index = 0; index <\
    \ count; ++index) {\n        Unsigned value = 0;\n        int remaining_bits =\
    \ bit_width;\n        while (remaining_bits > 0) {\n            if (buffered_bits\
    \ == 0) {\n                int digit = detail::base64_digit(encoded[position++]);\n\
    \                if (digit < 0) return std::nullopt;\n                buffer =\
    \ static_cast<unsigned>(digit);\n                buffered_bits = 6;\n        \
    \    }\n\n            int take = std::min(buffered_bits, remaining_bits);\n  \
    \          int shift = buffered_bits - take;\n            unsigned mask = (1U\
    \ << take) - 1;\n            unsigned part = (buffer >> shift) & mask;\n     \
    \       value = static_cast<Unsigned>((value << take) | part);\n            buffered_bits\
    \ -= take;\n            remaining_bits -= take;\n        }\n        values.push_back(static_cast<Integer>(value));\n\
    \    }\n\n    if (buffered_bits != 0) {\n        unsigned mask = (1U << buffered_bits)\
    \ - 1;\n        if ((buffer & mask) != 0) return std::nullopt;\n    }\n    return\
    \ values;\n}\n\ntemplate <detail::Base64Integer Integer>\nstd::vector<Integer>\
    \ from_base64(std::string_view encoded, std::size_t count,\n                 \
    \                int bit_width) {\n    std::optional<std::vector<Integer>> result\
    \ =\n        checked_from_base64<Integer>(encoded, count, bit_width);\n    assert(result.has_value());\n\
    \    return result.value_or(std::vector<Integer>());\n}\n\n}  // namespace utilities\n\
    }  // namespace m1une\n\n#endif  // M1UNE_UTILITIES_BASE64_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/base64.hpp
  requiredBy: []
  timestamp: '2026-08-11 14:01:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/base64.test.cpp
documentation_of: utilities/base64.hpp
layout: document
title: Base64 Sequence Encoding
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
