---
title: Linear Recurrences and Bostan-Mori
documentation_of: ../../../math/fps/linear_recurrence.hpp
---

## Overview

This header discovers a shortest linear recurrence from observed terms with
the Berlekamp--Massey algorithm. It also computes distant coefficients of
rational generating functions with Bostan--Mori and provides a convenience
wrapper for evaluating a known recurrence without constructing all preceding
terms.

`Mint` must represent a field and support construction from integers,
arithmetic operations, division by a nonzero value, and equality comparison.
The algorithms are primarily intended for modular arithmetic over a prime
modulus.

## Methods

| Signature | Description | Time |
| --- | --- | --- |
| `template <class Mint> std::vector<Mint> berlekamp_massey(const std::vector<Mint>& sequence)` | Returns a minimum-order recurrence fitting the observed sequence. | $O(N^2)$ |
| `template <class Mint> Mint coefficient_of_rational(FormalPowerSeries<Mint> numerator, FormalPowerSeries<Mint> denominator, uint64_t index)` | Returns the coefficient of $x^\mathrm{index}$ in `numerator / denominator`. | $O(M(D) \log \mathrm{index})$ |
| `template <class Mint> Mint linear_recurrence_kth(const std::vector<Mint>& initial, const std::vector<Mint>& recurrence, uint64_t index)` | Returns the indexed term of a known recurrence. | $O(M(D) \log \mathrm{index})$ |

All recurrence interfaces use the following convention for order `d`:

```text
a[n] = recurrence[0] * a[n - 1]
     + recurrence[1] * a[n - 2]
     + ...
     + recurrence[d - 1] * a[n - d]
```

`berlekamp_massey(sequence)` returns a recurrence of minimum order that
reproduces every applicable term of the finite observed sequence. It returns
an empty vector for an empty or all-zero sequence. When several minimum-order
recurrences fit the observations, it may return any one of them.

`coefficient_of_rational(numerator, denominator, index)` returns the
coefficient of $x^\mathrm{index}$ in `numerator / denominator`. The
denominator's constant term must be nonzero.

`linear_recurrence_kth(initial, recurrence, index)` returns `a[index]`.
`initial` must contain exactly `a[0]` through `a[d - 1]`, where `d` is the
recurrence order, and must be nonempty.

Here $N$ is the number of observed terms, $D$ is the maximum polynomial or
recurrence degree, and $M(D)$ is the cost of multiplying degree-$D$
polynomials. Berlekamp--Massey uses $O(N)$ extra memory. The other functions
use $O(D)$ extra memory apart from convolution buffers.

## Example

```cpp
#include "math/fps/linear_recurrence.hpp"
#include "math/modint.hpp"

#include <iostream>
#include <vector>

using mint = m1une::math::modint998244353;

int main() {
    std::vector<mint> observed = {0, 1, 1, 2, 3, 5, 8, 13};
    std::vector<mint> recurrence = m1une::fps::berlekamp_massey(observed);
    std::vector<mint> initial(observed.begin(),
                              observed.begin() + recurrence.size());
    mint fibonacci_100 = m1une::fps::linear_recurrence_kth(
        initial, recurrence, 100);
    std::cout << fibonacci_100 << "\n";
}
```
