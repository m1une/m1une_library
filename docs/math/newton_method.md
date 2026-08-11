---
title: Newton Method
documentation_of: ../../math/newton_method.hpp
---

## Overview

`newton_method` applies a fixed number of Newton updates

$$
x \leftarrow x - \frac{f(x)}{f'(x)}.
$$

It works with ordinary numeric types and with `FormalPowerSeries`. Fixed
iteration counts make the routine predictable and also cover algebraic settings
where a floating-point stopping tolerance is not meaningful.

The public namespace is `m1une::math`.

## Interface

```cpp
template <class T, class F, class Derivative>
T newton_method(
    T initial,
    F function,
    Derivative derivative,
    int iterations
);

template <class T, class F, class Derivative, class Quotient>
T newton_method(
    T initial,
    F function,
    Derivative derivative,
    int iterations,
    Quotient quotient
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `newton_method(initial, function, derivative, iterations)` | Performs `iterations` Newton updates using the default quotient operation. | $O(k(C_f+C_{f'}+C_q))$ |
| `newton_method(initial, function, derivative, iterations, quotient)` | Uses `quotient(function(x), derivative(x))` as the correction. | $O(k(C_f+C_{f'}+C_q))$ |

Here $k$ is `iterations`, $C_f$ and $C_{f'}$ are the costs of the two function
evaluations, and $C_q$ is the quotient cost. Memory use is the maximum required
by one update. Ordinary scalar division has $C_q=O(1)$. For an $n$-coefficient
FPS with NTT multiplication, the default quotient costs $O(n\log n)$ time and
$O(n)$ auxiliary memory.

For ordinary types, the default quotient is `numerator / denominator`. The type
`T` must support subtraction assignment and the operations used by the supplied
callables. The derivative must be invertible at every iterate. Newton's method
does not guarantee convergence from an arbitrary initial value.
`iterations` must be nonnegative. The initial value is copied, and the caller's
object is not modified.

For `FormalPowerSeries<Mint>`, the default quotient is formal-series division
modulo $x^n$, where `n == initial.size()`. In particular, it does not use the FPS
`operator/`, which represents polynomial long division. The denominator's
constant coefficient must be nonzero. The result keeps exactly `n`
coefficients. If the initial value solves the equation modulo $x$ and the root
is simple, each update doubles the number of correct coefficients, so
`ceil(log2(n))` iterations suffice when only the constant coefficient is known
initially. Truncate expensive intermediate FPS operations to `n` coefficients.

For a complete precision-doubling solver for $G(f)=0\pmod{x^n}$, use
`math/fps/solve_fps_equation.hpp`. It evaluates `G` and its derivative only at
geometrically increasing precisions.

The custom `quotient` overload is useful when division means solving a linear
system or needs domain-specific truncation.

## Example

```cpp
#include "math/newton_method.hpp"

#include <cmath>
#include <iostream>

int main() {
    auto function = [](double x) { return x * x - 2.0; };
    auto derivative = [](double x) { return 2.0 * x; };

    double root = m1une::math::newton_method(
        1.0, function, derivative, 8
    );
    std::cout << root << '\n';
}
```

For an FPS square root, give the initial series the desired result length and a
valid constant root:

```cpp
#include "math/modint.hpp"
#include "math/newton_method.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    const int n = 8;
    Fps target = {1, 2, 3, 4};
    target.resize(n);

    Fps initial(n);
    initial[0] = 1;
    auto function = [&](const Fps& value) {
        return (value * value).pre(n) - target;
    };
    auto derivative = [](const Fps& value) {
        return value * mint(2);
    };

    Fps root = m1une::math::newton_method(
        initial, function, derivative, 3
    );
}
```
