---
title: Compositional Inverse of Formal Power Series
documentation_of: ../../../math/fps/compositional_inverse.hpp
---

## Overview

`compositional_inverse` computes the formal power series $g$ satisfying
$f(g(x)) = g(f(x)) = x$. This is function inversion under composition, not the
multiplicative inverse returned by `f.inv()`.

## Interface

```cpp
template <class Mint>
FormalPowerSeries<Mint> compositional_inverse(
    const FormalPowerSeries<Mint>& f,
    int degree = -1);
```

`Mint` must satisfy the static modular-integer interface required by
`FormalPowerSeries` and `compose`, and its coefficients must form a field. The
modular integer types in `math/modint.hpp` with a prime modulus satisfy these
requirements.

| Function | Result | Complexity |
| --- | --- | --- |
| `compositional_inverse(f, n)` | $f^{\langle-1\rangle}(x) \bmod x^n$ as exactly `n` coefficients. | $O(M(n) \log n)$ time and $O(n \log n)$ memory |
| `compositional_inverse(f)` | The same result with `n = f.size()`. | $O(M(n) \log n)$ time and $O(n \log n)$ memory |

Here $M(n)$ is the cost of multiplying degree-$n$ polynomials. With NTT
convolution, the time is $O(n \log^2 n)$.

The series must satisfy `f[0] == 0` and `f[1] != 0`; these conditions guarantee
that the compositional inverse exists and is unique. The function asserts the
conditions and does not modify `f`.

## Example

```cpp
#include "math/fps/compositional_inverse.hpp"
#include "math/modint.hpp"
#include <iostream>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps f = {0, 1, 1};
    Fps g = m1une::fps::compositional_inverse(f, 6);
    Fps identity = m1une::fps::compose(f, g, 6);

    for (mint coefficient : identity) std::cout << coefficient << ' ';
    std::cout << '\n';
}
```

## Algorithm

Suppose $g$ is already correct modulo $x^m$. Newton's method doubles the known
precision with

$$
g \leftarrow g - \frac{f(g)-x}{f'(g)}.
$$

The correction begins at degree $m$, so its square cannot affect terms below
degree $2m$. The implementation computes only one composition per step. If
$h=f(g)$, differentiating gives $h'=f'(g)g'$, hence
$1/f'(g)=g'/h'$. All remaining operations are ordinary FPS multiplication and
inversion.
