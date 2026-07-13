---
title: Multidimensional Convolution
documentation_of: ../../math/multivariate_convolution.hpp
---

## Overview

Fast convolution of flattened multidimensional arrays. The first dimension is
contiguous: for dimensions `n`, coordinates `(i[0], ..., i[k - 1])` are stored
at

`i[0] + i[1] * n[0] + ... + i[k - 1] * n[0] * ... * n[k - 2]`.

Two products are available:

* truncated convolution discards every term whose exponent reaches the bound
  in any variable, corresponding to reduction modulo
  $(x_0^{n_0}, \ldots, x_{k-1}^{n_{k-1}})$;
* cyclic convolution wraps every exponent in each variable, corresponding to
  reduction modulo
  $(1-x_0^{n_0}, \ldots, 1-x_{k-1}^{n_{k-1}})$.

## API

| Function | Description | Complexity |
| --- | --- | --- |
| `template <class Mint> std::vector<Mint> multivariate_convolution_truncated(const std::vector<int>& dimensions, const std::vector<Mint>& first, const std::vector<Mint>& second)` | Returns the truncated product. | $O(kN\log N+k^2N)$ time and $O(kN)$ memory. |
| `template <class Mint> std::vector<Mint> multivariate_convolution_cyclic(const std::vector<int>& dimensions, const std::vector<Mint>& first, const std::vector<Mint>& second)` | Returns the cyclic product. | $O(N\sum_i \log n_i + P(M))$ time and $O(N+\max_i n_i)$ memory. |

Here, `k = dimensions.size()`, $n_i$ is the size of dimension `i`, and
$N=\prod_i n_i$, $M$ is the modulus, and $P(M)$ is the cost of one
`primitive_root(M)` call. Both input arrays and the returned array have length
$N$.

## Requirements and Behavior

Every dimension must be positive. An empty dimension vector represents a
zero-variable polynomial, so both arrays must contain one scalar.

`multivariate_convolution_truncated` requires a static-modulus `Mint`. If `S`
is the smallest power of two with $S \geq 2N-1$, then `S` must divide
`Mint::mod() - 1`. In particular, `m1une::math::modint998244353` supports all
sizes up to the usual $2^{22}$ coefficient limit for this routine.

`multivariate_convolution_cyclic` accepts either `ModInt<mod>` or
`DynamicModInt<id>`. Its modulus must admit a primitive root, and every $n_i$
must divide `Mint::mod() - 1`. Library Checker's circular version supplies a
prime modulus, which satisfies the first condition. For a dynamic modint, call
`set_mod` before constructing or reading coefficients.

Neither function modifies its arguments.

## Example

```cpp
#include "math/modint.hpp"
#include "math/multivariate_convolution.hpp"

#include <vector>

using mint = m1une::math::modint998244353;

int main() {
    // Shape 2 by 2. Indices are (0,0), (1,0), (0,1), (1,1).
    std::vector<int> dimensions = {2, 2};
    std::vector<mint> first = {1, 2, 3, 4};
    std::vector<mint> second = {5, 6, 7, 8};

    std::vector<mint> truncated =
        m1une::math::multivariate_convolution_truncated(
            dimensions, first, second
        );
    std::vector<mint> cyclic =
        m1une::math::multivariate_convolution_cyclic(
            dimensions, first, second
        );
    // truncated is 5, 16, 22, 60.
    // cyclic is 70, 68, 62, 60.
}
```
