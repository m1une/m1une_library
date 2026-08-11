---
title: Solve Formal Power Series Equation
documentation_of: ../../../math/fps/solve_fps_equation.hpp
---

## Overview

`solve_fps_equation` finds a formal power series $f$ satisfying

$$
G(f)=0 \pmod{x^n}
$$

by Newton lifting. It starts from a solution at lower precision and doubles the
number of known coefficients after each update.

The public namespace is `m1une::fps`.

## Interface

```cpp
template <class Mint, class Function, class Derivative>
FormalPowerSeries<Mint> solve_fps_equation(
    FormalPowerSeries<Mint> initial,
    int degree,
    Function function,
    Derivative derivative
);

template <class Mint, class Function, class Derivative>
FormalPowerSeries<Mint> solve_fps_equation(
    int degree,
    Mint constant_solution,
    Function function,
    Derivative derivative
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `solve_fps_equation(initial, degree, function, derivative)` | Extends a known solution from `initial.size()` to exactly `degree` coefficients. | $O(C_G(n)+C_{G'}(n)+M(n))$ under the usual geometric-sum assumption |
| `solve_fps_equation(degree, constant_solution, function, derivative)` | Starts with one known coefficient. | $O(C_G(n)+C_{G'}(n)+M(n))$ under the usual geometric-sum assumption |

`function(value, precision)` must return $G(value)$ and
`derivative(value, precision)` must return $G'(value)$, each correct modulo
$x^{precision}$. The explicit precision argument lets the callbacks truncate
expensive intermediate operations.

The first overload requires `initial` to be nonempty and to satisfy
$G(initial)=0\pmod{x^m}$ for `m == initial.size()`. The constant-solution overload
requires $G(constant_solution)=0\pmod{x}$. In both cases, the constant
coefficient of $G'(initial)$ must be nonzero, so its multiplicative FPS inverse
exists. `degree` must be nonnegative; degree zero returns an empty series.

Here $C_G(n)$ and $C_{G'}(n)$ are the costs of evaluating the callbacks at
precision $n$, and $M(n)$ is the cost of FPS multiplication. The stated bound
assumes the costs over geometrically increasing precisions sum to their cost at
the final precision. With NTT multiplication and quasilinear callbacks, the
time is $O(n\log n)$ and auxiliary memory is $O(n)$.

The input is copied and no previous version is mutated. If `initial` already
has at least `degree` coefficients, its prefix is returned without evaluating
the callbacks.

## Example

This computes a square root by solving $G(f)=f^2-a=0$:

```cpp
#include "math/fps/solve_fps_equation.hpp"
#include "math/modint.hpp"

#include <cassert>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    const int degree = 8;
    Fps a = {1, 2, 3, 4};
    a.resize(degree);

    auto function = [&](const Fps& value, int precision) {
        return (value * value).pre(precision) - a.pre(precision);
    };
    auto derivative = [](const Fps& value, int precision) {
        return (value * mint(2)).pre(precision);
    };

    Fps root = m1une::fps::solve_fps_equation(
        degree, mint(1), function, derivative
    );
    assert((root * root).pre(degree) == a);
}
```

The derivative is with respect to the unknown series $f$, not the formal
derivative with respect to $x$. For equations whose derivative is a general
linear operator rather than multiplication by an invertible FPS, use the custom
quotient overload of `m1une::math::newton_method` directly.
