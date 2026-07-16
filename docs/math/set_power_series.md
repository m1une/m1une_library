---
title: Set Power Series
documentation_of: ../../math/set_power_series.hpp
---

## Overview

A set power series stores one coefficient for every subset of an `n`-element
ground set. Subsets are represented by masks, so a series has exactly `2^n`
coefficients. Multiplication is subset convolution:

$$
(fg)[S] = \sum_{T \subseteq S} f[T]g[S \setminus T].
$$

This header provides division, inverse, exponential, logarithm, integer power,
and normalized square root under that multiplication. The exponential and
logarithm are mutually inverse on series with constant coefficients zero and
one, respectively.

## Requirements and Behavior

Every input vector must be nonempty and have power-of-two size. Invalid sizes
assert.

`T` must provide ordinary construction, equality, addition, subtraction, and
multiplication. Division and inverse additionally require division in `T` and a
nonzero denominator constant. `set_power_series_sqrt` requires that `2` be
invertible.

The normalized operations have these constant-term requirements:

* `set_power_series_exp(f)` requires `f[0] == 0`.
* `set_power_series_log(f)`, `set_power_series_pow(f, k)`, and
  `set_power_series_sqrt(f)` require `f[0] == 1`.

`set_power_series_sqrt` returns the square root whose constant coefficient is
one. `set_power_series_pow` accepts negative exponents because a series with
constant coefficient one is invertible.

## Interface

| Function | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Division | `template <class T> std::vector<T> set_power_series_divide(const std::vector<T>& numerator, const std::vector<T>& denominator)` | Returns `numerator / denominator` under subset convolution. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |
| Inverse | `template <class T> std::vector<T> set_power_series_inverse(const std::vector<T>& series)` | Returns the subset-convolution inverse. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |
| Exponential | `template <class T> std::vector<T> set_power_series_exp(const std::vector<T>& series)` | Returns the normalized set-series exponential. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |
| Logarithm | `template <class T> std::vector<T> set_power_series_log(const std::vector<T>& series)` | Returns the normalized set-series logarithm. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |
| Integer power | `template <class T> std::vector<T> set_power_series_pow(const std::vector<T>& series, long long exponent)` | Returns the integer power under subset convolution. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |
| Square root | `template <class T> std::vector<T> set_power_series_sqrt(const std::vector<T>& series)` | Returns the normalized square root. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |

The implementation uses ranked subset-zeta transforms for division. The
exponential builds one variable at a time, and the logarithm solves the inverse
subset-convolution problem at each level. Geometrically increasing levels keep
the total bound at $O(n^2 2^n)$.

## Example

```cpp
#include "math/modint.hpp"
#include "math/set_power_series.hpp"

#include <cassert>
#include <vector>

int main() {
    using Mint = m1une::math::modint998244353;

    std::vector<Mint> logarithm(8);
    logarithm[1] = 2;
    logarithm[2] = 3;
    logarithm[4] = 5;

    auto series = m1une::math::set_power_series_exp(logarithm);
    auto restored = m1une::math::set_power_series_log(series);
    assert(restored == logarithm);
}
```
