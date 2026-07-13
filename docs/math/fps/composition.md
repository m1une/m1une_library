---
title: Formal Power Series Composition
documentation_of: ../../../math/fps/composition.hpp
---

## Overview

`compose` computes the truncated composition $f(g(x))$. It uses a transposed
power-projection algorithm, reducing composition to a logarithmic number of
one-dimensional convolutions.

## Interface

```cpp
template <class Mint>
FormalPowerSeries<Mint> compose(
    const FormalPowerSeries<Mint>& outer,
    const FormalPowerSeries<Mint>& inner,
    int degree = -1);
```

`Mint` must satisfy the static modular-integer interface required by
`convolution`; the modular integer types in `math/modint.hpp` do so. Let `Fps`
denote `FormalPowerSeries<Mint>`.

| Function | Result | Complexity |
| --- | --- | --- |
| `compose(f, g, n)` | $f(g(x)) \bmod x^n$ as exactly `n` coefficients. | $O(M(n) \log n)$ time and $O(n \log n)$ memory |
| `compose(f, g)` | The same result with `n = f.size()`. | $O(M(n) \log n)$ time and $O(n \log n)$ memory |

Here $M(n)$ is the cost of multiplying degree-$n$ polynomials, so the time is
$O(n \log^2 n)$ when NTT convolution is available.

Formal power series composition requires `g.empty()` or `g[0] == 0`; the
function asserts this condition. Missing coefficients in either input are
treated as zero. The function does not modify either input.

## Example

```cpp
#include "math/fps/composition.hpp"
#include "math/modint.hpp"
#include <iostream>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps f = {1, 2, 3};
    Fps g = {0, 1, 1};
    Fps h = m1une::fps::compose(f, g, 5);

    for (mint coefficient : h) std::cout << coefficient << ' ';
    std::cout << '\n';
}
```

The result is the first five coefficients of $1 + 2g(x) + 3g(x)^2$.

## Algorithm

The map taking the coefficients of $f$ to those of $f(g(x))$ is linear.
Transposing it turns composition into power projection: extracting one fixed
coefficient from successive powers of $g$. A bivariate Bostan--Mori reduction
halves the $x$-degree at each level. Reversing those reductions evaluates the
transposed map with 2D convolutions and middle products, both encoded as 1D
convolutions. There are $O(\log n)$ levels and $O(M(n))$ work per level.
