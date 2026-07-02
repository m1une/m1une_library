---
title: Polynomial Half-GCD
documentation_of: ../../fps/half_gcd.hpp
---

## Overview

This header accelerates the Euclidean algorithm for polynomials over a field.
`half_gcd(a, b)` batches roughly half of the remaining Euclidean steps into a
unimodular polynomial matrix. The same machinery provides a monic polynomial
GCD, Bézout coefficients, and inversion modulo a polynomial.

Coefficients are stored from the constant term upward. Trailing zero
coefficients are ignored by every public algorithm.

## Requirements

`Mint` must represent a field and provide the interface expected by
`FormalPowerSeries<Mint>`, including `inv()`. The supplied static modular
integer types meet this requirement when their modulus is prime.

For `half_gcd(first, second)`, the normalized degree of `first` must be at least
the normalized degree of `second`. The returned matrix `M` combines several
consecutive steps from the beginning of the polynomial Euclidean algorithm:

\[
(c,d)^T = M (first,second)^T, \qquad \gcd(c,d)=\gcd(first,second).
\]

The recursion chooses the block from the high halves of the inputs. If the
second input is already below the half-size boundary, the result is the
identity; otherwise the block strictly decreases its degree. This convention
lets the full GCD routine alternate half-GCD blocks with single Euclidean steps.

## Public Interface

Let `Fps` denote `FormalPowerSeries<Mint>`.

```cpp
template <class Mint>
struct PolynomialMatrix2x2 {
    Fps a00, a01, a10, a11;

    static PolynomialMatrix2x2 identity();
    std::pair<Fps, Fps> apply(const Fps& first, const Fps& second) const;
    friend PolynomialMatrix2x2 operator*(
        const PolynomialMatrix2x2& lhs, const PolynomialMatrix2x2& rhs);
};

template <class Mint>
PolynomialMatrix2x2<Mint> half_gcd(Fps first, Fps second);

template <class Mint>
struct PolynomialExtendedGcdResult {
    Fps gcd, x, y;
};

template <class Mint>
PolynomialExtendedGcdResult<Mint> polynomial_extended_gcd(
    const Fps& first, const Fps& second);

template <class Mint>
Fps polynomial_gcd(const Fps& first, const Fps& second);

template <class Mint>
std::optional<Fps> polynomial_inv_mod(const Fps& polynomial, Fps modulus);
```

## Methods

Here, `n` is the larger normalized coefficient count and `M(n)` is the cost of
multiplying degree-`n` polynomials. With the supplied NTT convolution,
`M(n) = O(n log n)`.

| Method | Result | Complexity |
| --- | --- | --- |
| `PolynomialMatrix2x2::identity()` | The identity transformation. | $O(1)$ |
| `matrix.apply(a, b)` | Applies the matrix to the polynomial pair. | $O(M(n))$ |
| `lhs * rhs` | Composes two polynomial matrices. | $O(M(n))$ |
| `half_gcd(a, b)` | Combines the first batch of Euclidean-algorithm steps into one matrix. | $O(M(n) \log n)$ |
| `polynomial_extended_gcd(a, b)` | Monic `gcd` and `x`, `y` satisfying `a * x + b * y = gcd`. | $O(M(n) \log n)$ |
| `polynomial_gcd(a, b)` | The monic GCD; returns zero only when both inputs are zero. | $O(M(n) \log n)$ |
| `polynomial_inv_mod(f, g)` | `h` with `f * h = 1 (mod g)`, or `nullopt` when none exists. | $O(M(n) \log n)$ |

`polynomial_inv_mod` requires a nonzero modulus. None of the functions mutate
their arguments.

## Example

```cpp
#include "fps/half_gcd.hpp"
#include "math/modint.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps common = {1, 1};
    Fps a = common * Fps{2, 0, 1};
    Fps b = common * Fps{3, 1};

    Fps gcd = m1une::fps::polynomial_gcd(a, b);
    auto extended = m1une::fps::polynomial_extended_gcd(a, b);
    auto inverse = m1une::fps::polynomial_inv_mod(Fps{1, 1}, Fps{1, 0, 1});
    Fps bezout = extended.x * a + extended.y * b;
    bezout.shrink();

    return gcd == common && bezout == common && inverse.has_value()
               ? 0
               : 1;
}
```
