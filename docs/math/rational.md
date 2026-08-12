---
title: Rational Number
documentation_of: ../../math/rational.hpp
---

## Overview

`Rational<T>` represents an exact fraction using either a signed built-in
integral type or an integer-like class such as
[`utilities::BigInt`](../utilities/bigint.md).

Every value is normalized:

* numerator and denominator are coprime,
* the denominator is positive,
* zero is represented as `0/1`.

The default underlying type is `long long`.

## Construction

```cpp
Rational<T>();
Rational<T>(integer);
Rational<T>(numerator, denominator);
```

The denominator must be nonzero. Integer construction is implicit, so ordinary
integers can be mixed with rationals in arithmetic expressions.

Built-in `T` must be signed and no wider than `long long`. A custom `T` must be
copyable, constructible from `0` and `1`, and support signed comparison and the
usual exact integer arithmetic operations (`+`, `-`, `*`, `/`, and `%`).

## Complexity Notation

* `N` is the maximum storage size of a numerator, denominator, or intermediate.
* `C(N)`, `M(N)`, `D(N)`, and `G(N)` are the costs of copying, multiplying,
  dividing, and computing a gcd with `T`, respectively.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `numerator() const` | Returns the normalized numerator. | $O(C(N))$ |
| `denominator() const` | Returns the positive normalized denominator. | $O(C(N))$ |
| `is_integer() const` | Returns whether the denominator is one. | $O(1)$ |
| `sign() const` | Returns `-1`, `0`, or `1`. | $O(1)$ |
| `reciprocal() const` | Returns the reciprocal; requires a nonzero value. | $O(G(N) + D(N))$ |
| `abs() const` | Returns the absolute value. | $O(G(N) + D(N))$ |
| `trunc() const` | Rounds toward zero. | $O(D(N))$ |
| `floor() const` | Returns the mathematical floor. | $O(D(N))$ |
| `ceil() const` | Returns the mathematical ceiling. | $O(D(N))$ |
| `to_long_double() const` | Returns a floating-point approximation. | $O(1)$ for built-ins; $O(N)$ for custom types |

Arithmetic operators `+`, `-`, `*`, and `/`, their compound forms, unary signs,
equality, and three-way comparison are supported.

For built-in types, operations use `__int128_t` intermediates. The final
normalized numerator and denominator, and every intermediate widened
calculation, must be representable. Custom integer-like types are used directly,
so `Rational<BigInt>` provides unbounded exact intermediates. Arithmetic reduces
common or cross factors before multiplication when possible.

Construction takes $O(G(N) + D(N))$. Each arithmetic operation takes
$O(G(N) + M(N) + D(N))$; addition and subtraction also perform linear-time
addition on `T`. Comparison takes $O(M(N))$. For built-in types, Euclidean gcd
is logarithmic in the numeric magnitude and the other primitive operations are
$O(1)$.

## Input and Output

Output uses `numerator/denominator`, omitting `/1` for integers.

Input accepts either an integer or a fraction with no spaces around the slash:

```text
5
-7/12
```

## Example

```cpp
#include "math/rational.hpp"

#include <iostream>

int main() {
    using Fraction = m1une::math::Rational<long long>;

    Fraction first(2, 3);
    Fraction second(5, 6);
    Fraction result = first + second;

    std::cout << result << "\n";        // 3/2
    std::cout << result.floor() << "\n"; // 1
}
```

For unbounded fractions, instantiate the same interface with `BigInt`:

```cpp
#include "math/rational.hpp"
#include "utilities/bigint.hpp"

using BigInt = m1une::utilities::BigInt;
using BigFraction = m1une::math::Rational<BigInt>;

BigFraction value(BigInt("100000000000000000000"), BigInt(3));
BigFraction reciprocal = value.reciprocal();
```
