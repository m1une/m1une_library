---
title: Polynomial Roots over a Finite Field
documentation_of: ../../../math/fps/polynomial_roots.hpp
---

## Overview

Finds every distinct field element at which a nonzero polynomial vanishes. The
algorithm first computes

$$
\gcd(f(x), x^p-x),
$$

which removes repeated factors and all irreducible factors of degree greater
than one. It then uses randomized quadratic-character splits and fast
polynomial half-GCD until every remaining linear factor is isolated.

## Requirements

`Mint` must represent a prime field, expose static `mod()` and `val()`, and meet
the requirements of `FormalPowerSeries` and `polynomial_gcd`. Characteristic
two is handled directly; odd prime fields use the randomized splitter.

The zero polynomial has every field element as a root and is rejected by an
assertion. A nonzero constant has no roots. Repeated roots are returned once.

## Public Interface

```cpp
template <class Mint>
std::vector<Mint> polynomial_roots(
    FormalPowerSeries<Mint> polynomial,
    uint64_t seed = 88172645463325252ULL
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `polynomial_roots(polynomial, seed)` | Returns all distinct roots, sorted by `val()`. The input is copied and not mutated. | Expected $O(M(N)\log N\log p)$ field operations |

Here $N$ is the normalized degree plus one and $M(N)$ is polynomial
multiplication cost. The deterministic default seed makes output reproducible;
passing zero selects that default. The returned vector has at most
`polynomial.size() - 1` elements and uses $O(N\log N)$ temporary memory.

## Example

```cpp
#include "math/fps/polynomial_roots.hpp"
#include "math/modint.hpp"

using Mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<Mint>;

int main() {
    // (x - 2)^2 (x - 5)
    Fps polynomial = Fps{Mint(0) - Mint(2), Mint(1)} *
                     Fps{Mint(0) - Mint(2), Mint(1)} *
                     Fps{Mint(0) - Mint(5), Mint(1)};
    std::vector<Mint> roots = m1une::fps::polynomial_roots(polynomial);
    return roots == std::vector<Mint>{Mint(2), Mint(5)} ? 0 : 1;
}
```
