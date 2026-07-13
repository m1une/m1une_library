---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/repunit.test.cpp
    title: verify/math/repunit.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/repunit.hpp\"\n\n\n\n#include <cassert>\n#include <cstdint>\n\
    #include <numeric>\n#include <optional>\n#include <utility>\n\nnamespace m1une\
    \ {\nnamespace math {\n\ntemplate <class T>\nconstexpr std::pair<T, T> repunit_and_power(\n\
    \    std::uint64_t length,\n    T base = T(10)\n) {\n    T result = T(0);\n  \
    \  T result_power = T(1);\n    T block = T(1);\n    T block_power = base;\n\n\
    \    while (length > 0) {\n        if (length & 1) {\n            result = result\
    \ * block_power + block;\n            result_power = result_power * block_power;\n\
    \        }\n        block = block * block_power + block;\n        block_power\
    \ = block_power * block_power;\n        length >>= 1;\n    }\n    return std::make_pair(result,\
    \ result_power);\n}\n\n// Returns 1 + base + ... + base^(length - 1).\n// The\
    \ arithmetic, including any modular reduction, is performed by T.\ntemplate <class\
    \ T>\nconstexpr T repunit(std::uint64_t length, T base = T(10)) {\n    return\
    \ repunit_and_power<T>(length, base).first;\n}\n\ntemplate <class T>\nconstexpr\
    \ T repdigit(std::uint64_t length, T digit, T base = T(10)) {\n    return digit\
    \ * repunit<T>(length, base);\n}\n\ntemplate <class T>\nconstexpr T concatenate_digits(\n\
    \    T left,\n    T right,\n    std::uint64_t right_length,\n    T base = T(10)\n\
    ) {\n    return left * repunit_and_power<T>(right_length, base).second + right;\n\
    }\n\nnamespace repunit_detail {\n\ninline std::uint64_t multiply_mod(\n    std::uint64_t\
    \ left,\n    std::uint64_t right,\n    std::uint64_t mod\n) {\n    return static_cast<std::uint64_t>(\n\
    \        static_cast<unsigned __int128>(left) * right % mod\n    );\n}\n\ninline\
    \ std::pair<std::uint64_t, std::uint64_t> repunit_and_power_mod(\n    std::uint64_t\
    \ length,\n    std::uint64_t base,\n    std::uint64_t mod\n) {\n    if (mod ==\
    \ 1) return std::make_pair(0, 0);\n\n    std::uint64_t result = 0;\n    std::uint64_t\
    \ result_power = 1;\n    std::uint64_t block = 1;\n    std::uint64_t block_power\
    \ = base % mod;\n    while (length > 0) {\n        if (length & 1) {\n       \
    \     result = (\n                static_cast<unsigned __int128>(result) * block_power\
    \ + block\n            ) % mod;\n            result_power = multiply_mod(result_power,\
    \ block_power, mod);\n        }\n        block = (\n            static_cast<unsigned\
    \ __int128>(block) * block_power + block\n        ) % mod;\n        block_power\
    \ = multiply_mod(block_power, block_power, mod);\n        length >>= 1;\n    }\n\
    \    return std::make_pair(result, result_power);\n}\n\n}  // namespace repunit_detail\n\
    \ninline std::pair<std::uint64_t, std::uint64_t> repunit_and_power_mod(\n    std::uint64_t\
    \ length,\n    std::uint64_t base,\n    std::uint64_t mod\n) {\n    assert(mod\
    \ >= 1);\n    return repunit_detail::repunit_and_power_mod(length, base, mod);\n\
    }\n\ninline std::uint64_t repunit_mod(\n    std::uint64_t length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    return repunit_and_power_mod(length,\
    \ base, mod).first;\n}\n\ninline std::uint64_t repdigit_mod(\n    std::uint64_t\
    \ length,\n    std::uint64_t digit,\n    std::uint64_t base,\n    std::uint64_t\
    \ mod\n) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n    return repunit_detail::multiply_mod(\n\
    \        digit % mod,\n        repunit_mod(length, base, mod),\n        mod\n\
    \    );\n}\n\ninline std::uint64_t concatenate_digits_mod(\n    std::uint64_t\
    \ left,\n    std::uint64_t right,\n    std::uint64_t right_length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    assert(mod >= 1);\n    if (mod == 1)\
    \ return 0;\n    const std::uint64_t power =\n        repunit_and_power_mod(right_length,\
    \ base, mod).second;\n    return (\n        static_cast<unsigned __int128>(left\
    \ % mod) * power + right % mod\n    ) % mod;\n}\n\ninline std::optional<std::uint64_t>\
    \ minimum_repunit_length(\n    std::uint64_t divisor,\n    std::uint64_t base\
    \ = 10\n) {\n    assert(divisor >= 1);\n    assert(base >= 2);\n    if (std::gcd(divisor,\
    \ base) != 1) return std::nullopt;\n\n    std::uint64_t remainder = 0;\n    for\
    \ (std::uint64_t length = 1; length <= divisor; length++) {\n        remainder\
    \ = (\n            static_cast<unsigned __int128>(remainder) * base + 1\n    \
    \    ) % divisor;\n        if (remainder == 0) return length;\n    }\n    return\
    \ std::nullopt;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_REPUNIT_HPP\n#define M1UNE_MATH_REPUNIT_HPP 1\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <numeric>\n#include <optional>\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <class T>\nconstexpr\
    \ std::pair<T, T> repunit_and_power(\n    std::uint64_t length,\n    T base =\
    \ T(10)\n) {\n    T result = T(0);\n    T result_power = T(1);\n    T block =\
    \ T(1);\n    T block_power = base;\n\n    while (length > 0) {\n        if (length\
    \ & 1) {\n            result = result * block_power + block;\n            result_power\
    \ = result_power * block_power;\n        }\n        block = block * block_power\
    \ + block;\n        block_power = block_power * block_power;\n        length >>=\
    \ 1;\n    }\n    return std::make_pair(result, result_power);\n}\n\n// Returns\
    \ 1 + base + ... + base^(length - 1).\n// The arithmetic, including any modular\
    \ reduction, is performed by T.\ntemplate <class T>\nconstexpr T repunit(std::uint64_t\
    \ length, T base = T(10)) {\n    return repunit_and_power<T>(length, base).first;\n\
    }\n\ntemplate <class T>\nconstexpr T repdigit(std::uint64_t length, T digit, T\
    \ base = T(10)) {\n    return digit * repunit<T>(length, base);\n}\n\ntemplate\
    \ <class T>\nconstexpr T concatenate_digits(\n    T left,\n    T right,\n    std::uint64_t\
    \ right_length,\n    T base = T(10)\n) {\n    return left * repunit_and_power<T>(right_length,\
    \ base).second + right;\n}\n\nnamespace repunit_detail {\n\ninline std::uint64_t\
    \ multiply_mod(\n    std::uint64_t left,\n    std::uint64_t right,\n    std::uint64_t\
    \ mod\n) {\n    return static_cast<std::uint64_t>(\n        static_cast<unsigned\
    \ __int128>(left) * right % mod\n    );\n}\n\ninline std::pair<std::uint64_t,\
    \ std::uint64_t> repunit_and_power_mod(\n    std::uint64_t length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    if (mod == 1) return std::make_pair(0,\
    \ 0);\n\n    std::uint64_t result = 0;\n    std::uint64_t result_power = 1;\n\
    \    std::uint64_t block = 1;\n    std::uint64_t block_power = base % mod;\n \
    \   while (length > 0) {\n        if (length & 1) {\n            result = (\n\
    \                static_cast<unsigned __int128>(result) * block_power + block\n\
    \            ) % mod;\n            result_power = multiply_mod(result_power, block_power,\
    \ mod);\n        }\n        block = (\n            static_cast<unsigned __int128>(block)\
    \ * block_power + block\n        ) % mod;\n        block_power = multiply_mod(block_power,\
    \ block_power, mod);\n        length >>= 1;\n    }\n    return std::make_pair(result,\
    \ result_power);\n}\n\n}  // namespace repunit_detail\n\ninline std::pair<std::uint64_t,\
    \ std::uint64_t> repunit_and_power_mod(\n    std::uint64_t length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    assert(mod >= 1);\n    return repunit_detail::repunit_and_power_mod(length,\
    \ base, mod);\n}\n\ninline std::uint64_t repunit_mod(\n    std::uint64_t length,\n\
    \    std::uint64_t base,\n    std::uint64_t mod\n) {\n    return repunit_and_power_mod(length,\
    \ base, mod).first;\n}\n\ninline std::uint64_t repdigit_mod(\n    std::uint64_t\
    \ length,\n    std::uint64_t digit,\n    std::uint64_t base,\n    std::uint64_t\
    \ mod\n) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n    return repunit_detail::multiply_mod(\n\
    \        digit % mod,\n        repunit_mod(length, base, mod),\n        mod\n\
    \    );\n}\n\ninline std::uint64_t concatenate_digits_mod(\n    std::uint64_t\
    \ left,\n    std::uint64_t right,\n    std::uint64_t right_length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    assert(mod >= 1);\n    if (mod == 1)\
    \ return 0;\n    const std::uint64_t power =\n        repunit_and_power_mod(right_length,\
    \ base, mod).second;\n    return (\n        static_cast<unsigned __int128>(left\
    \ % mod) * power + right % mod\n    ) % mod;\n}\n\ninline std::optional<std::uint64_t>\
    \ minimum_repunit_length(\n    std::uint64_t divisor,\n    std::uint64_t base\
    \ = 10\n) {\n    assert(divisor >= 1);\n    assert(base >= 2);\n    if (std::gcd(divisor,\
    \ base) != 1) return std::nullopt;\n\n    std::uint64_t remainder = 0;\n    for\
    \ (std::uint64_t length = 1; length <= divisor; length++) {\n        remainder\
    \ = (\n            static_cast<unsigned __int128>(remainder) * base + 1\n    \
    \    ) % divisor;\n        if (remainder == 0) return length;\n    }\n    return\
    \ std::nullopt;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_MATH_REPUNIT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/repunit.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-03 15:39:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/repunit.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/repunit.hpp
layout: document
title: Repunit
---

## Overview

A length-$n$ repunit in base $b$ consists of $n$ copies of the digit one:

$$
R_n(b) = 1 + b + b^2 + \cdots + b^{n-1}.
$$

For example, $R_3(10)=111$ and $R_4(2)=15$. This header also handles
repdigits, concatenates base-$b$ digit blocks, evaluates these operations under
a runtime modulus, and finds the shortest repunit divisible by an integer.

All evaluation uses binary doubling and avoids division by $b-1$. It therefore
works with composite moduli and when `base - 1` has no inverse.

## Generic Functions

```cpp
template <class T>
constexpr std::pair<T, T> repunit_and_power(
    std::uint64_t length,
    T base = T(10));

template <class T>
constexpr T repunit(std::uint64_t length, T base = T(10));

template <class T>
constexpr T repdigit(
    std::uint64_t length,
    T digit,
    T base = T(10));

template <class T>
constexpr T concatenate_digits(
    T left,
    T right,
    std::uint64_t right_length,
    T base = T(10));
```

`T` must be constructible from `0`, `1`, and, when the default base is used,
`10`. It must provide associative and distributive addition and multiplication.
`repdigit` additionally expects multiplication to commute.

| Function | Description | Complexity |
| --- | --- | --- |
| `repunit_and_power<T>(length, base)` | Returns `{R_length(base), base^length}`. | $O(\log \mathtt{length})$ time, $O(1)$ memory |
| `repunit<T>(length, base)` | Returns $R_{\mathtt{length}}(\mathtt{base})$. | $O(\log \mathtt{length})$ time, $O(1)$ memory |
| `repdigit<T>(length, digit, base)` | Returns the length-`length` numeral whose every digit is `digit`. | $O(\log \mathtt{length})$ time, $O(1)$ memory |
| `concatenate_digits(left, right, right_length, base)` | Appends the `right_length`-digit block `right` to `left`. | $O(\log \mathtt{right_length})$ time, $O(1)$ memory |

A zero-length repunit or repdigit is zero. Concatenating a zero-length right
block returns `left + right`, so `right` should normally be zero in that case.
For a built-in integer type, every intermediate result must fit; use the
runtime-modulus functions, a modular integer, or a big integer otherwise.

## Runtime-Modulus Functions

```cpp
std::pair<std::uint64_t, std::uint64_t> repunit_and_power_mod(
    std::uint64_t length,
    std::uint64_t base,
    std::uint64_t mod);

std::uint64_t repunit_mod(
    std::uint64_t length,
    std::uint64_t base,
    std::uint64_t mod);

std::uint64_t repdigit_mod(
    std::uint64_t length,
    std::uint64_t digit,
    std::uint64_t base,
    std::uint64_t mod);

std::uint64_t concatenate_digits_mod(
    std::uint64_t left,
    std::uint64_t right,
    std::uint64_t right_length,
    std::uint64_t base,
    std::uint64_t mod);
```

`mod` must be positive. These functions use 128-bit intermediate products, so
all unsigned 64-bit arguments are supported without overflow. Each function
runs in logarithmic time in the relevant block length and uses constant memory.
`repunit_and_power_mod` returns `{R_length(base) mod mod, base^length mod mod}`.

## Divisible Repunit

```cpp
std::optional<std::uint64_t> minimum_repunit_length(
    std::uint64_t divisor,
    std::uint64_t base = 10);
```

Returns the smallest positive `length` for which
`repunit_mod(length, base, divisor) == 0`. `divisor` must be positive and
`base` must be at least two. A solution exists exactly when `base` and
`divisor` are coprime; otherwise the function returns `nullopt`.

The function iterates remainders and takes $O(\mathtt{divisor})$ time in the
worst case and $O(1)$ memory.

## Example

```cpp
#include "math/repunit.hpp"

#include <iostream>

int main() {
    std::cout << m1une::math::repunit<unsigned long long>(6) << '\n';
    std::cout << m1une::math::repdigit<unsigned long long>(3, 7) << '\n';
    std::cout << m1une::math::concatenate_digits(12ULL, 34ULL, 2) << '\n';

    std::uint64_t reduced = m1une::math::repunit_mod(
        1000000000000000000ULL,
        10,
        1000
    );
    std::cout << reduced << '\n';

    auto length = m1une::math::minimum_repunit_length(7);
    if (length) std::cout << *length << '\n'; // 6
}
```
