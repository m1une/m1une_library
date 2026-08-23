---
title: Gaussian Integer
documentation_of: ../../math/gaussian_integer.hpp
---

## Overview

`GaussianInteger<T>` represents an exact number `a + b i` with integral real
and imaginary parts. Gaussian integers form a Euclidean domain under the norm

$$
N(a + b i) = a^2 + b^2.
$$

The type provides ordinary arithmetic, conjugation, exact nearest-quotient
Euclidean division, canonical associates, divisibility tests, GCD, and extended
GCD. All calculations are integral; division never uses floating point.

```cpp
#include "math/gaussian_integer.hpp"
```

## Template Requirements

`T` must be a standard signed integral type no wider than `long long`. The
default is `long long`. Coordinates returned by arithmetic and extended GCD
must remain representable by `T`; debug builds assert this condition.

Products, norms, and division numerators use exact 128-bit intermediates. The
public `norm_type` is `__uint128_t`, so the norm of every pair of 64-bit
coordinates is representable.

## Representation and Fields

| Member | Meaning |
| --- | --- |
| `value_type` | Alias for `T`. |
| `norm_type` | Unsigned 128-bit norm type. |
| `real` | Real coordinate `a`. |
| `imag` | Imaginary coordinate `b`. |

Equality compares both coordinates exactly.

## Euclidean Division

For a nonzero divisor `d`, `z.divmod(d)` returns `(q, r)` satisfying

$$
z = qd + r, \qquad N(r) < N(d).
$$

The real and imaginary coordinates of the exact complex quotient are rounded
to their nearest integers. Exact half-integer ties are rounded away from zero;
any consistent nearest choice gives a valid Euclidean remainder.

Consequently, `/` is Euclidean nearest-quotient division, not division in the
complex field. `%` returns its matching remainder. Division by zero is invalid
and asserted.

## Canonical Associates

The units are `1`, `-1`, `i`, and `-i`. Multiplying by a unit does not change
divisibility, so a nonzero Gaussian GCD has four associates.

`normalized()` chooses the unique associate with positive real part and
nonnegative imaginary part. Zero remains zero. `gaussian_gcd` and
`extended_gaussian_gcd` return this canonical associate, making their output
deterministic.

## Interface

All members and free functions are in `m1une::math`.

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Default constructor | `GaussianInteger()` | Constructs zero. | $O(1)$ |
| Real constructor | `GaussianInteger(T real)` | Constructs a real Gaussian integer. | $O(1)$ |
| Coordinate constructor | `GaussianInteger(T real, T imag)` | Constructs `real + imag * i`. | $O(1)$ |
| `is_zero` | `bool is_zero() const` | Tests equality with zero. | $O(1)$ |
| `is_unit` | `bool is_unit() const` | Tests whether the norm is one. | $O(1)$ |
| `norm` | `norm_type norm() const` | Returns `real * real + imag * imag`. | $O(1)$ |
| `conjugate` | `GaussianInteger conjugate() const` | Returns `real - imag * i`. | $O(1)$ |
| `normalizing_unit` | `GaussianInteger normalizing_unit() const` | Returns the unit that moves the value to its canonical associate. | $O(1)$ |
| `normalized` | `GaussianInteger normalized() const` | Returns the canonical associate. | $O(1)$ |
| `divmod` | `std::pair<GaussianInteger, GaussianInteger> divmod(const GaussianInteger& divisor) const` | Returns the Euclidean quotient and remainder. | $O(1)$ |
| Unary plus | `GaussianInteger operator+() const` | Returns the unchanged value. | $O(1)$ |
| Unary minus | `GaussianInteger operator-() const` | Negates both coordinates. | $O(1)$ |
| Compound addition | `GaussianInteger& operator+=(const GaussianInteger& other)` | Adds `other`. | $O(1)$ |
| Compound subtraction | `GaussianInteger& operator-=(const GaussianInteger& other)` | Subtracts `other`. | $O(1)$ |
| Compound multiplication | `GaussianInteger& operator*=(const GaussianInteger& other)` | Multiplies by `other`. | $O(1)$ |
| Compound division | `GaussianInteger& operator/=(const GaussianInteger& other)` | Replaces the value by its Euclidean quotient by `other`. | $O(1)$ |
| Compound remainder | `GaussianInteger& operator%=(const GaussianInteger& other)` | Replaces the value by its Euclidean remainder modulo `other`. | $O(1)$ |
| Binary addition | `friend GaussianInteger operator+(GaussianInteger left, const GaussianInteger& right)` | Returns `left + right`. | $O(1)$ |
| Binary subtraction | `friend GaussianInteger operator-(GaussianInteger left, const GaussianInteger& right)` | Returns `left - right`. | $O(1)$ |
| Binary multiplication | `friend GaussianInteger operator*(GaussianInteger left, const GaussianInteger& right)` | Returns `left * right`. | $O(1)$ |
| Binary division | `friend GaussianInteger operator/(GaussianInteger left, const GaussianInteger& right)` | Returns the Euclidean quotient. | $O(1)$ |
| Binary remainder | `friend GaussianInteger operator%(GaussianInteger left, const GaussianInteger& right)` | Returns the Euclidean remainder. | $O(1)$ |
| Equality | `friend bool operator==(const GaussianInteger& first, const GaussianInteger& second)` | Compares both coordinates. | $O(1)$ |

| Free function | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| `gaussian_divides` | `bool gaussian_divides(const GaussianInteger<T>& divisor, const GaussianInteger<T>& value)` | Tests `divisor` dividing `value`; zero divides only zero. | $O(1)$ |
| `gaussian_associates` | `bool gaussian_associates(const GaussianInteger<T>& first, const GaussianInteger<T>& second)` | Tests equality up to multiplication by a unit. | $O(1)$ |
| `gaussian_gcd` | `GaussianInteger<T> gaussian_gcd(GaussianInteger<T> first, GaussianInteger<T> second)` | Returns the canonical greatest common divisor. | $O(\log(\min(N(first), N(second)) + 1))$ |
| `extended_gaussian_gcd` | `std::tuple<GaussianInteger<T>, GaussianInteger<T>, GaussianInteger<T>> extended_gaussian_gcd(GaussianInteger<T> first, GaussianInteger<T> second)` | Returns `(g, x, y)` with `first * x + second * y == g`, where `g` is canonical. | $O(\log(\min(N(first), N(second)) + 1))$ |

The zero pair has GCD zero. For `gaussian_divides`, the convention that zero
divides zero follows directly from the existence of a Gaussian integer `z`
with `0 = 0 * z`.

## Example

```cpp
#include "math/gaussian_integer.hpp"

#include <iostream>

int main() {
    using G = m1une::math::GaussianInteger<long long>;

    G first(5, 7);
    G second(2, -1);
    auto [quotient, remainder] = first.divmod(second);

    G gcd = m1une::math::gaussian_gcd(first, second);
    std::cout << quotient.real << ' ' << quotient.imag << '\n';
    std::cout << remainder.real << ' ' << remainder.imag << '\n';
    std::cout << gcd.real << ' ' << gcd.imag << '\n';
}
```
