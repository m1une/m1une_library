---
title: Sparse Formal Power Series
documentation_of: ../../../math/fps/sparse_formal_power_series.hpp
---

## Overview

Sparse FPS operations compute a dense truncated result from only the nonzero
terms of the input. They are useful when the requested degree `n` is large but
the input contains only `k` terms.

```cpp
template <class Mint>
using SparseFormalPowerSeries = std::vector<std::pair<int, Mint>>;
```

Each pair is `(degree, coefficient)`. Terms must have strictly increasing
degrees in `[0, n)`, and coefficients must be nonzero.

## Interface

Let `Sparse` denote `SparseFormalPowerSeries<Mint>` and `Fps` denote
`FormalPowerSeries<Mint>`.

```cpp
template <class Mint>
FormalPowerSeries<Mint> sparse_fps_inv(
    const SparseFormalPowerSeries<Mint>& terms, int degree);

template <class Mint>
FormalPowerSeries<Mint> sparse_fps_log(
    const SparseFormalPowerSeries<Mint>& terms, int degree);

template <class Mint>
FormalPowerSeries<Mint> sparse_fps_exp(
    const SparseFormalPowerSeries<Mint>& terms, int degree);

template <class Mint>
FormalPowerSeries<Mint> sparse_fps_pow(
    const SparseFormalPowerSeries<Mint>& terms,
    long long exponent, int degree);

template <class Mint>
std::optional<FormalPowerSeries<Mint>> sparse_fps_sqrt(
    const SparseFormalPowerSeries<Mint>& terms, int degree);
```

| Function | Requirement | Result | Complexity |
| --- | --- | --- | --- |
| `Fps sparse_fps_inv(const Sparse& f, int n)` | `f[0].first == 0`, constant coefficient invertible | $1/f \bmod x^n$ | $O(nk)$ |
| `Fps sparse_fps_log(const Sparse& f, int n)` | Constant term is exactly one | $\log f \bmod x^n$ | $O(nk)$ |
| `Fps sparse_fps_exp(const Sparse& f, int n)` | Constant term is zero and therefore omitted | $\exp f \bmod x^n$ | $O(nk)$ |
| `Fps sparse_fps_pow(const Sparse& f, long long m, int n)` | `m >= 0` | $f^m \bmod x^n$ | $O(nk)$ |
| `std::optional<Fps> sparse_fps_sqrt(const Sparse& f, int n)` | Odd prime field | A square root modulo $x^n$, if one exists | $O(nk)$ |

All functions return exactly `n` coefficients and use $O(n)$ memory. Logarithm,
exponential, power, and square root require `n < Mint::mod()` because their
recurrences divide by coefficient indices. The supplied `math/modint.hpp`
types with a prime modulus satisfy the required field operations.

`sparse_fps_pow(f, 0, n)` returns one, including when `f` is zero. Square root
returns `std::nullopt` when the leading degree is odd or the leading
coefficient is not a quadratic residue. The zero series has the zero series as
its square root.

No operation modifies the sparse input.

## Example

```cpp
#include "math/fps/sparse_formal_power_series.hpp"
#include "math/modint.hpp"
#include <iostream>

using mint = m1une::math::modint998244353;
using Sparse = m1une::fps::SparseFormalPowerSeries<mint>;

int main() {
    Sparse f;
    f.emplace_back(0, 1);
    f.emplace_back(3, 2);

    auto inverse = m1une::fps::sparse_fps_inv(f, 10);
    for (mint coefficient : inverse) std::cout << coefficient << ' ';
    std::cout << '\n';
}
```

## Recurrences

The implementation compares coefficients in standard differential identities:

* $fg=1$ for inverse;
* $(\log f)'=f'/f$;
* $(\exp f)'=f'\exp f$;
* $f(g^a)'=a f'g^a$ for a unit series $f$.

Only the `k` stored terms contribute to each new coefficient, giving the
$O(nk)$ bound.
