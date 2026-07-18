---
title: Geometric-Sequence Polynomial Evaluation and Interpolation
documentation_of: ../../../math/fps/geometric_sequence_evaluation.hpp
---

## Overview

Evaluates a polynomial at all points

$$
a, ar, ar^2, \ldots, ar^{m-1}
$$

or reconstructs a degree-less-than-$n$ polynomial from its values at the first
$n$ such points. Both operations convert the geometric powers into one
convolution using triangular exponents, often called the chirp transform.

Coefficients are stored from the constant term upward. Evaluation preserves the
requested number of values, and interpolation returns exactly `values.size()`
coefficients, including high zero coefficients.

## Requirements

`Mint` must be a field type accepted by `FormalPowerSeries`, and its convolution
must support the required output size. Evaluation accepts every `initial` and
`ratio`; when `ratio == 0`, it returns `f(initial)` followed by copies of
`f(0)`.

For interpolation with at least two values, `initial` and `ratio` must be
nonzero and the points must be distinct. Equivalently, `ratio.pow(k) != 1` for
every `1 <= k < values.size()`. These conditions are asserted. It is valid for
`ratio.pow(values.size()) == 1`.

## Public Interface

```cpp
template <class Mint>
std::vector<Mint> multipoint_evaluate_geometric(
    const FormalPowerSeries<Mint>& polynomial,
    Mint initial,
    Mint ratio,
    int count
);

template <class Mint>
FormalPowerSeries<Mint> polynomial_interpolate_geometric(
    const std::vector<Mint>& values,
    Mint initial,
    Mint ratio
);
```

Let $N$ be the coefficient or value count, $M$ the requested evaluation count,
and $C(K)$ the cost of a length-$K$ convolution.

| Function | Description | Complexity |
| --- | --- | --- |
| `multipoint_evaluate_geometric(f, a, r, m)` | Returns `f(a * r.pow(i))` for `0 <= i < m`. | $O(N+M+C(N+M))$ time, $O(N+M)$ memory |
| `polynomial_interpolate_geometric(y, a, r)` | Returns the unique polynomial of degree less than `y.size()` with `f(a * r.pow(i)) == y[i]`. | $O(N+C(N))$ time, $O(N)$ memory |

With NTT convolution, both bounds are $O(K\log K)$ for their respective total
size. A zero evaluation count and an empty interpolation both return an empty
vector or polynomial.

## Example

```cpp
#include "math/fps/geometric_sequence_evaluation.hpp"
#include "math/modint.hpp"

using Mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<Mint>;

int main() {
    Fps polynomial = {1, 2, 3};
    auto values = m1une::fps::multipoint_evaluate_geometric(
        polynomial, Mint(5), Mint(3), 3);
    Fps restored = m1une::fps::polynomial_interpolate_geometric(
        values, Mint(5), Mint(3));
    return restored == polynomial ? 0 : 1;
}
```
