---
title: Polynomial Factorization
documentation_of: ../../../math/fps/polynomial_factorization.hpp
---

## Overview

This header factors a nonzero polynomial over a prime field into distinct monic
irreducible factors and their multiplicities. It uses distinct-degree
factorization followed by randomized Cantor-Zassenhaus equal-degree splitting.

The original leading coefficient is returned separately, so non-monic and
constant polynomials are supported. For a returned result `result`,

$$
f(x) = \text{result.leading_coefficient}
       \prod_i \text{result.factors[i].polynomial}(x)^{
           \text{result.factors[i].multiplicity}}.
$$

## Requirements

`Mint` must represent a prime field and provide the usual arithmetic operators,
`inv()`, `val()`, and static `mod()`. Both `m1une::math::ModInt` and compatible
runtime-modulus types can be used. The modulus must fit in `uint64_t`.

## API

```cpp
template <class Mint>
struct PolynomialFactor {
    FormalPowerSeries<Mint> polynomial;
    int multiplicity;
};

template <class Mint>
struct PolynomialFactorization {
    Mint leading_coefficient;
    std::vector<PolynomialFactor<Mint>> factors;
};

template <class Mint>
PolynomialFactorization<Mint> polynomial_factorize(
    FormalPowerSeries<Mint> polynomial,
    uint64_t seed = 88172645463325252ULL
);
```

| Interface | Description | Complexity |
| --- | --- | --- |
| `PolynomialFactor` | One monic irreducible factor and its positive multiplicity. | -- |
| `PolynomialFactorization` | Original leading coefficient and all distinct factors. | -- |
| `polynomial_factorize(polynomial, seed)` | Factors a nonzero polynomial over the field represented by `Mint`. | $O(n^4 \log p)$ field operations in the worst case; typically much faster |

The implementation uses quadratic polynomial multiplication and division. It is
intended for the small and medium degrees common in factorization problems; in
particular, it comfortably handles Library Checker's degree-100 target.

The input is copied and is not mutated. The zero polynomial has no finite
factorization and is rejected by an assertion. A nonzero constant returns no
factors and stores that constant in `leading_coefficient`.

Equal-degree splitting is randomized. The default seed makes runs reproducible;
pass another nonzero seed when a different splitting sequence is desired. A
zero seed selects the default. Returned factors are sorted first by degree and
then by coefficients, and identical factors are merged.

## Example

```cpp
#include "math/fps/polynomial_factorization.hpp"
#include "math/modint.hpp"

#include <iostream>

int main() {
    using Mint = m1une::math::ModInt<17>;
    using Fps = m1une::fps::FormalPowerSeries<Mint>;

    Fps polynomial({Mint(2), Mint(11), Mint(12), Mint(1)});
    auto result = m1une::fps::polynomial_factorize(polynomial);

    for (const auto& factor : result.factors) {
        std::cout << factor.multiplicity << " "
                  << factor.polynomial.size() - 1 << "\n";
    }
}
```
