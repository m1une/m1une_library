---
title: Bernoulli Numbers and Power Sums
documentation_of: ../../math/bernoulli.hpp
---

## Overview

Bernoulli numbers are defined by

$$
\frac{x}{e^x-1}
=\sum_{n=0}^{\infty}B_n\frac{x^n}{n!}.
$$

This header uses the convention $B_1=-1/2$. Besides generating the numbers,
`Bernoulli<Mint>` provides their common contest applications:

* Bernoulli polynomials;
* Faulhaber sums over prefixes and half-open ranges;
* coefficients of power-sum polynomials;
* discrete integration and range summation of a polynomial;
* power sums over an arithmetic progression.

All values are represented in `Mint`. For example, $B_1$ is
`-1 * inverse(2)` modulo `Mint::mod()`.

## Bernoulli Numbers

```cpp
template <class Mint>
std::vector<Mint> bernoulli_numbers(int maximum);
```

This returns $B_0,B_1,\ldots,B_{\text{maximum}}$. It inverts the formal power
series

$$
\frac{e^x-1}{x}
=\sum_{n=0}^{\infty}\frac{x^n}{(n+1)!}
$$

and therefore takes $O(N\log N)$ time and $O(N)$ memory, where
$N=\text{maximum}+1$.

The first values are

```text
B_0 = 1
B_1 = -1/2
B_2 = 1/6
B_3 = 0
B_4 = -1/30
B_5 = 0
B_6 = 1/42
```

## Reusable Table

```cpp
template <class Mint>
class Bernoulli;
```

Constructing `Bernoulli<Mint>(maximum)` computes and stores all Bernoulli
numbers through that degree, together with the factorial data used by later
queries.

### Bernoulli Polynomials

The Bernoulli polynomial is

$$
B_n(x)=\sum_{k=0}^{n}\binom{n}{k}B_kx^{n-k}.
$$

`polynomial(n, x)` evaluates it, while `polynomial_coefficients(n)` returns
its coefficients in increasing order of powers. They satisfy

$$
B_n(x+1)-B_n(x)=n x^{n-1}.
$$

### Sums of Powers

`power_sum(n, degree)` evaluates Faulhaber's formula

$$
\sum_{i=0}^{n-1}i^d
=\frac{B_{d+1}(n)-B_{d+1}}{d+1}.
$$

The overload `power_sum(left, right, degree)` returns

$$
\sum_{i=\text{left}}^{\text{right}-1}i^d.
$$

Both bounds are `Mint`, so the formulas may be evaluated at a very large
integer after converting it to `Mint`.

`power_sum_polynomial(degree)` returns the coefficients of the prefix sum as
a polynomial in `n`. Coefficients are ordered from the constant term upward.

### Polynomial and Arithmetic-Progression Sums

For a coefficient vector representing

$$
P(x)=\sum_{k=0}^{d}c_kx^k,
$$

`polynomial_prefix_sum(coefficients)` returns coefficients of the unique
polynomial $Q$ such that

$$
Q(0)=0,
\qquad
Q(n)=\sum_{i=0}^{n-1}P(i).
$$

`polynomial_sum(coefficients, left, right)` evaluates
$Q(\text{right})-Q(\text{left})$ directly.

`arithmetic_progression_power_sum(start, step, count, degree)` returns

$$
\sum_{i=0}^{\text{count}-1}(\text{start}+\text{step}\,i)^{\text{degree}}.
$$

It uses binomial expansion, so `step` may be zero and does not need to be
invertible.

## Interface and Complexity

| Member / Function | Result | Complexity |
| --- | --- | --- |
| `bernoulli_numbers<Mint>(maximum)` | All Bernoulli numbers from degree `0` through `maximum`. | $O(N\log N)$ time, $O(N)$ memory |
| `Bernoulli<Mint>(maximum)` | Precomputes the reusable table. | $O(N\log N)$ time, $O(N)$ memory |
| `maximum()` | Largest available degree. | $O(1)$ |
| `numbers()` | Const reference to all stored numbers. | $O(1)$ |
| `number(degree)` | $B_{\text{degree}}$. | $O(1)$ |
| `polynomial_coefficients(degree)` | Coefficients of $B_{\text{degree}}(x)$. | $O(d)$ time and memory |
| `polynomial(degree, x)` | $B_{\text{degree}}(x)$. | $O(d)$ time and memory |
| `power_sum(n, degree)` | $\sum_{i=0}^{n-1}i^d$. | $O(d)$ time and memory |
| `power_sum(left, right, degree)` | $\sum_{i=\text{left}}^{\text{right}-1}i^d$. | $O(d)$ time and memory |
| `power_sum_polynomial(degree)` | Coefficients of the power-sum polynomial. | $O(d)$ time and memory |
| `polynomial_prefix_sum(coefficients)` | Coefficients of the discrete integral of a degree-$d$ polynomial. | $O(d^2)$ time, $O(d)$ memory |
| `polynomial_sum(coefficients, left, right)` | Sum of a polynomial over the half-open integer range. | $O(d^2)$ time, $O(d)$ memory |
| `arithmetic_progression_power_sum(start, step, count, degree)` | Sum of `degree`-th powers over an arithmetic progression. | $O(d^2)$ time, $O(d)$ memory |

Here $N=\text{maximum}+1$ and $d=\text{degree}$. Every requested degree, and
the degree of an input polynomial, must not exceed `maximum`.

`Mint::mod()` should be prime, and `maximum + 1` must be smaller than the
modulus so that every required factorial and denominator is invertible.

## Example

```cpp
#include "math/bernoulli.hpp"
#include "math/modint.hpp"

#include <iostream>
#include <vector>

int main() {
    using Mint = m1une::math::modint998244353;
    m1une::math::Bernoulli<Mint> bernoulli(10);

    // 0^3 + 1^3 + ... + 99^3.
    std::cout << bernoulli.power_sum(Mint(100), 3) << "\n";

    // P(x) = 2 + 3x + x^2, summed for 5 <= x < 20.
    std::vector<Mint> polynomial{Mint(2), Mint(3), Mint(1)};
    std::cout << bernoulli.polynomial_sum(
        polynomial,
        Mint(5),
        Mint(20)
    ) << "\n";

    // 4^5 + 7^5 + ... for 12 terms.
    std::cout << bernoulli.arithmetic_progression_power_sum(
        Mint(4),
        Mint(3),
        Mint(12),
        5
    ) << "\n";
}
```
