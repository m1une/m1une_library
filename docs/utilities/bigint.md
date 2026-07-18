---
title: BigInt
documentation_of: ../../utilities/bigint.hpp
---

## Overview

An arbitrary-precision signed integer for competitive programming. Digits are
stored in little-endian base-$10^9$ blocks.

Large products split each base-$10^9$ block into 15-bit halves and use a packed
complex FFT. The transform avoids explicit bit-reversal passes and has a
specialized squaring path. Every FFT result is checked modulo $2^{61}-1$;
values outside the conservative accuracy bound, or results that fail the check,
fall back to an exact three-prime NTT with Chinese remainder reconstruction.

Large quotients use a normalized Newton reciprocal and the same fast
multiplication. Small products use schoolbook multiplication, while small
quotients use normalized Knuth division to avoid transform overhead.

## Methods

| Method / Operator | Description | Complexity |
| --- | --- | --- |
| `BigInt()` | Initializes the value to `0`. | $O(1)$ |
| `BigInt(long long value)` | Initializes from a signed 64-bit integer. | $O(1)$ |
| `BigInt(const std::string& text)` | Parses decimal text with optional `+` or `-`. | $O(N)$ |
| `BigInt& operator=(long long value)` | Assigns a signed 64-bit integer. | $O(1)$ |
| `BigInt& operator=(const std::string& text)` | Assigns parsed decimal text. | $O(N)$ |
| `void read(const std::string& text)` | Replaces the value with parsed decimal text. | $O(N)$ |
| `void trim()` | Removes leading zero blocks and canonicalizes zero. | $O(N)$ |
| `std::string to_string() const` | Returns the decimal representation. | $O(N)$ |
| `bool is_zero() const` | Tests whether the value is zero. | $O(1)$ |
| `BigInt operator-() const` | Returns the negated value. | $O(N)$ |
| `BigInt abs() const` | Returns the absolute value. | $O(N)$ |
| `operator+`, `operator+=` | Adds two values. | $O(N+M)$ |
| `operator-`, `operator-=` | Subtracts two values. | $O(N+M)$ |
| `BigInt& operator*=(int value)` | Multiplies by a machine integer. | $O(N)$ |
| `operator*`, `operator*=(const BigInt&)` | Multiplies two values using checked FFT convolution for large inputs, with an exact NTT fallback. | $O((N+M)\log(N+M))$; $O(NM)$ for the small-input fallback |
| `operator/`, `operator/=` | Returns the quotient, truncated toward zero. | $O(N\log N)$ on the Newton path; $O(NM)$ for the bounded fallback |
| `operator%`, `operator%=` | Returns the remainder associated with truncated division. | Same as division |
| `divmod(const BigInt& a, const BigInt& b)` | Returns `std::pair<BigInt, BigInt>` containing `a / b` and `a % b`. | Same as division |
| `<`, `>`, `<=`, `>=`, `==`, `!=` | Compares two values. | $O(N+M)$ |
| `operator<<`, `operator>>` | Writes or reads decimal text through standard streams. | $O(N)$ |

Here, $N$ is the number of base-$10^9$ blocks in the larger or dividend
operand, and $M$ is the number in the other operand. Fast multiplication and
division use $O(N+M)$ auxiliary memory.

For compatibility, `a` (the limb vector) and `sign` remain public. Directly
modified values must keep every limb in `[0, BASE)`, remove high zero limbs,
and use a sign of `1` or `-1`; normal construction and arithmetic maintain
these invariants automatically.

Division is C++-style signed integer division: the quotient is truncated toward
zero, `a == (a / b) * b + a % b`, the nonzero remainder has the sign of `a`,
and its absolute value is smaller than `abs(b)`. Division by zero throws
`std::domain_error`.

## Example

```cpp
#include "utilities/bigint.hpp"
#include <iostream>

using m1une::utilities::BigInt;

int main() {
    BigInt a("12345678901234567890");
    BigInt b = 987654321;

    BigInt sum = a + b;
    BigInt diff = a - b;
    BigInt product = a * b;

    // std::pair<BigInt, BigInt>
    auto [quotient, remainder] = divmod(a, b);

    std::cout << "Sum: " << sum << "\n";
    std::cout << "Difference: " << diff << "\n";
    std::cout << "Product: " << product << "\n";
    std::cout << "Quotient: " << quotient << " R: " << remainder << "\n";

    if (a > b) {
        std::cout << "A is larger!\n";
    }

    return 0;
}
```
