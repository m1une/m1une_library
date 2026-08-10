---
title: Multidimensional Convolution
documentation_of: ../../math/multivariate_convolution.hpp
---

## Overview

Fast convolution of multidimensional arrays. Inputs may use a flat vector plus
explicit dimensions, or nested `std::vector`s whose dimensions are inferred.
In the flat representation, the first dimension is contiguous: for dimensions
`n`, coordinates `(i[0], ..., i[k - 1])` are stored at

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
| `template <class Mint> std::vector<Mint> multivariate_convolution_truncated(const std::vector<int>& dimensions, const std::vector<Mint>& first, const std::vector<Mint>& second)` | Returns the first $n_i$ coefficients in every dimension of the ordinary multidimensional convolution, in flat form. | $O(kN\log N+k^2N)$ time and $O(kN)$ memory. |
| `template <class Nested> Nested multivariate_convolution_truncated(const Nested& first, const Nested& second)` | Returns the same truncated convolution as a nested vector with the same shape as the inputs. | $O(kN\log N+k^2N)$ time and $O(kN)$ memory. |
| `template <class Mint> std::vector<Mint> multivariate_convolution_cyclic(const std::vector<int>& dimensions, const std::vector<Mint>& first, const std::vector<Mint>& second)` | Returns the multidimensional convolution with indices wrapping around each dimension, in flat form. | $O(N\sum_i \log n_i + P(M))$ time and $O(N+\max_i n_i)$ memory when every $n_i$ divides $M-1$; otherwise $O(k^2L\log L)$ time and $O(kL)$ memory. |
| `template <class Nested> Nested multivariate_convolution_cyclic(const Nested& first, const Nested& second)` | Returns the same cyclic convolution as a nested vector with the same shape as the inputs. | $O(N\sum_i \log n_i + P(M))$ time and $O(N+\max_i n_i)$ memory when every $n_i$ divides $M-1$; otherwise $O(k^2L\log L)$ time and $O(kL)$ memory. |

Here, `k = dimensions.size()`, $n_i$ is the size of dimension `i`, and
$N=\prod_i n_i$, $M$ is the modulus, $L=\prod_{i:n_i>1}(2n_i-1)$, and $P(M)$
is the cost of one `primitive_root(M)` call. Both input arrays and the returned
array have length $N$.

## Returned Values

Let `first[p]` mean the coefficient at multidimensional index
$p=(p_0,\ldots,p_{k-1})$, and define `second[q]` similarly. Every coordinate is
in the range $0\leq p_i,q_i<n_i$.

For `multivariate_convolution_truncated`, the returned coefficient at index $t$
is

$$
\operatorname{result}[t]
=\sum_{p+q=t}\operatorname{first}[p]\operatorname{second}[q].
$$

Thus, terms with $p_i+q_i\geq n_i$ in any dimension do not appear in the
returned array. The result has the original dimensions, rather than the full
convolution dimensions $(2n_0-1,\ldots,2n_{k-1}-1)$.

For `multivariate_convolution_cyclic`, the returned coefficient at index $t$ is

$$
\operatorname{result}[t]
=\sum_{(p+q)\bmod n=t}
\operatorname{first}[p]\operatorname{second}[q].
$$

The modulo is applied independently in every dimension, so overflowing indices
wrap around instead of being discarded.

The flat overloads return a vector of length $N$ using the index order described
in the overview. The nested overloads return the same coefficients in a nested
vector with the same type and shape as the inputs. In particular,
`result[i2][i1][i0]` is the coefficient at index $(i_0,i_1,i_2)$.

## Requirements and Behavior

Every dimension must be positive. An empty dimension vector represents a
zero-variable polynomial, so both arrays must contain one scalar.

`multivariate_convolution_truncated` requires a static-modulus `Mint`. If `S`
is the smallest power of two with $S \geq 2N-1$, then `S` must divide
`Mint::mod() - 1`. In particular, `m1une::math::modint998244353` supports all
sizes up to the usual $2^{22}$ coefficient limit for this routine.

`multivariate_convolution_cyclic` accepts either `ModInt<mod>` or
`DynamicModInt<id>`. When every $n_i$ divides `Mint::mod() - 1`, it uses a
multidimensional DFT and the modulus must admit a primitive root. Otherwise it
works for arbitrary positive dimensions by zero-extending each nontrivial
dimension from $n_i$ to $2n_i-1$, taking a truncated product, and folding the
result modulo the original dimensions. The fallback uses ordinary convolution,
so its supported transform length and coefficient bound are those of
`fps::convolution`. For a dynamic modint, call `set_mod` before constructing or
reading coefficients.

No overload modifies its arguments.

For a nested input, `Nested` must be one or more levels of `std::vector` with a
modint scalar type. Both inputs must be nonempty, rectangular, and have the same
shape. The innermost vector is the first, contiguous dimension: for example,
`values[i2][i1][i0]` represents coordinate `(i0, i1, i2)`. Flattening and
rebuilding the nested vectors take an additional $O(N)$ time and memory.

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

    std::vector<std::vector<mint>> nested_first(2, std::vector<mint>(2));
    nested_first[0][0] = 1;
    nested_first[0][1] = 2;
    nested_first[1][0] = 3;
    nested_first[1][1] = 4;
    std::vector<std::vector<mint>> nested_second(2, std::vector<mint>(2));
    nested_second[0][0] = 5;
    nested_second[0][1] = 6;
    nested_second[1][0] = 7;
    nested_second[1][1] = 8;

    auto nested_truncated = m1une::math::multivariate_convolution_truncated(
        nested_first, nested_second
    );
    auto nested_cyclic = m1une::math::multivariate_convolution_cyclic(
        nested_first, nested_second
    );
    // nested_truncated has rows (5, 16) and (22, 60).
    // nested_cyclic has rows (70, 68) and (62, 60).
}
```
