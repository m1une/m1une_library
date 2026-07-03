---
title: Repunit
documentation_of: ../../math/repunit.hpp
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
