---
title: Cyclotomic Polynomial
documentation_of: ../../math/cyclotomic_polynomial.hpp
---

## Overview

The $n$-th cyclotomic polynomial $\Phi_n(x)$ is the monic polynomial whose
roots are the primitive $n$-th roots of unity. It is characterized by

$$
x^n - 1 = \prod_{d \mid n} \Phi_d(x).
$$

This header constructs its coefficients using the Möbius product

$$
\Phi_n(x) = \prod_{d \mid n} (1-x^d)^{\mu(n/d)}
$$

as a truncated formal power series. Only sparse multiplication and exact
division by factors of the form $1-x^d$ are needed.

## Function

```cpp
template <class T = long long>
std::vector<T> cyclotomic_polynomial(std::uint64_t index);
```

`index` must be positive. The result stores coefficients in ascending degree
order: element `i` is the coefficient of $x^i$. Its size is
$\varphi(\mathtt{index})+1$.

`T` must be constructible from `-1`, `0`, and `1`, and support addition and
subtraction. The coefficients are integers, so no multiplicative inverse or
prime modulus is required. With the default `long long`, every coefficient
must fit in that type.

| Function | Description | Complexity |
| --- | --- | --- |
| `cyclotomic_polynomial<T>(index)` | Returns the coefficients of $\Phi_{\mathtt{index}}(x)$. | $O(2^{\omega(n)}\varphi(n))$ time and $O(\varphi(n))$ memory, plus 64-bit factorization |

Here $\omega(n)$ is the number of distinct prime factors. Factorization uses
the library's deterministic Miller--Rabin and Pollard--Rho implementation.

For repunits, the defining identity immediately gives

$$
R_n(x) = \frac{x^n-1}{x-1}
       = \prod_{\substack{d \mid n \\ d>1}} \Phi_d(x).
$$

## Example

```cpp
#include "math/cyclotomic_polynomial.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> polynomial =
        m1une::math::cyclotomic_polynomial(12);
    for (long long coefficient : polynomial) {
        std::cout << coefficient << ' ';
    }
    std::cout << '\n'; // 1 0 -1 0 1
}
```
