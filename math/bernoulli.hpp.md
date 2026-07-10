---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':question:'
    path: math/fps/internal/ntt998_fast.hpp
    title: math/fps/internal/ntt998_fast.hpp
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/combinatorial_sequences.hpp
    title: Combinatorial Sequences
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/bell_number.test.cpp
    title: verify/math/bell_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/bernoulli_number.test.cpp
    title: verify/math/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/bernoulli_utilities.test.cpp
    title: verify/math/bernoulli_utilities.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/stirling_number_of_the_second_kind.test.cpp
    title: verify/math/stirling_number_of_the_second_kind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 17: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_MATH_BERNOULLI_HPP\n#define M1UNE_MATH_BERNOULLI_HPP 1\n\n\
    #include <cassert>\n#include <cstdint>\n#include <vector>\n\n#include \"fps/formal_power_series.hpp\"\
    \n#include \"combinatorics.hpp\"\n\nnamespace m1une {\nnamespace math {\n\nnamespace\
    \ bernoulli_detail {\n\ntemplate <class Mint>\nstd::vector<Mint> numbers(\n  \
    \  int maximum,\n    const Combinatorics<Mint>& combinations\n) {\n    using Fps\
    \ = fps::FormalPowerSeries<Mint>;\n    Fps denominator(maximum + 1);\n    for\
    \ (int index = 0; index <= maximum; ++index) {\n        denominator[index] = combinations.inverse_factorial(index\
    \ + 1);\n    }\n\n    Fps generating_function = denominator.inv(maximum + 1);\n\
    \    std::vector<Mint> result(maximum + 1);\n    for (int index = 0; index <=\
    \ maximum; ++index) {\n        result[index] =\n            generating_function[index]\
    \ * combinations.factorial(index);\n    }\n    return result;\n}\n\ntemplate <class\
    \ Mint>\nMint evaluate_polynomial(const std::vector<Mint>& coefficients, Mint\
    \ x) {\n    Mint result = 0;\n    for (int index = int(coefficients.size()) -\
    \ 1; index >= 0; --index) {\n        result = result * x + coefficients[index];\n\
    \    }\n    return result;\n}\n\n}  // namespace bernoulli_detail\n\n// Uses x\
    \ / (exp(x) - 1), so B_1 = -1/2.\ntemplate <class Mint>\nstd::vector<Mint> bernoulli_numbers(int\
    \ maximum) {\n    assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum)\
    \ + 1 < Mint::mod());\n    Combinatorics<Mint> combinations(maximum + 1);\n  \
    \  return bernoulli_detail::numbers(maximum, combinations);\n}\n\ntemplate <class\
    \ Mint>\nclass Bernoulli {\n   public:\n    explicit Bernoulli(int maximum)\n\
    \        : combinations_(checked_maximum(maximum) + 1),\n          numbers_(bernoulli_detail::numbers(maximum,\
    \ combinations_)) {}\n\n    int maximum() const {\n        return int(numbers_.size())\
    \ - 1;\n    }\n\n    const std::vector<Mint>& numbers() const {\n        return\
    \ numbers_;\n    }\n\n    Mint number(int degree) const {\n        assert(0 <=\
    \ degree && degree <= maximum());\n        return numbers_[degree];\n    }\n\n\
    \    // Coefficients of B_degree(x), in increasing order of powers of x.\n   \
    \ std::vector<Mint> polynomial_coefficients(int degree) const {\n        assert(0\
    \ <= degree && degree <= maximum());\n        std::vector<Mint> result(degree\
    \ + 1);\n        for (int power = 0; power <= degree; ++power) {\n           \
    \ result[power] =\n                combinations_.binom(degree, power) *\n    \
    \            numbers_[degree - power];\n        }\n        return result;\n  \
    \  }\n\n    Mint polynomial(int degree, Mint x) const {\n        assert(0 <= degree\
    \ && degree <= maximum());\n        std::vector<Mint> powers(degree + 1, Mint(1));\n\
    \        for (int power = 0; power < degree; ++power) {\n            powers[power\
    \ + 1] = powers[power] * x;\n        }\n\n        Mint result = 0;\n        for\
    \ (int index = 0; index <= degree; ++index) {\n            result += combinations_.binom(degree,\
    \ index) * numbers_[index] *\n                      powers[degree - index];\n\
    \        }\n        return result;\n    }\n\n    // Returns sum_{i=0}^{n-1} i^degree,\
    \ evaluated as a polynomial in n.\n    Mint power_sum(Mint n, int degree) const\
    \ {\n        assert(0 <= degree && degree <= maximum());\n        std::vector<Mint>\
    \ powers(degree + 2, Mint(1));\n        for (int power = 0; power <= degree; ++power)\
    \ {\n            powers[power + 1] = powers[power] * n;\n        }\n\n       \
    \ Mint result = 0;\n        for (int index = 0; index <= degree; ++index) {\n\
    \            result += combinations_.binom(degree + 1, index) *\n            \
    \          numbers_[index] * powers[degree + 1 - index];\n        }\n        return\
    \ result * combinations_.inverse(degree + 1);\n    }\n\n    // Returns sum_{i=left}^{right-1}\
    \ i^degree.\n    Mint power_sum(Mint left, Mint right, int degree) const {\n \
    \       return power_sum(right, degree) - power_sum(left, degree);\n    }\n\n\
    \    // Coefficients of sum_{i=0}^{n-1} i^degree as a polynomial in n.\n    std::vector<Mint>\
    \ power_sum_polynomial(int degree) const {\n        assert(0 <= degree && degree\
    \ <= maximum());\n        std::vector<Mint> result(degree + 2);\n        Mint\
    \ inverse = combinations_.inverse(degree + 1);\n        for (int index = 0; index\
    \ <= degree; ++index) {\n            result[degree + 1 - index] +=\n         \
    \       combinations_.binom(degree + 1, index) * numbers_[index] *\n         \
    \       inverse;\n        }\n        return result;\n    }\n\n    // If P is given\
    \ by coefficients, returns coefficients of the unique Q\n    // with Q(0) = 0\
    \ and Q(n) = sum_{i=0}^{n-1} P(i).\n    std::vector<Mint> polynomial_prefix_sum(\n\
    \        const std::vector<Mint>& coefficients\n    ) const {\n        if (coefficients.empty())\
    \ return std::vector<Mint>{Mint(0)};\n        int degree = int(coefficients.size())\
    \ - 1;\n        assert(degree <= maximum());\n\n        std::vector<Mint> result(degree\
    \ + 2);\n        for (int source_degree = 0;\n             source_degree <= degree;\n\
    \             ++source_degree) {\n            Mint inverse = combinations_.inverse(source_degree\
    \ + 1);\n            for (int index = 0; index <= source_degree; ++index) {\n\
    \                result[source_degree + 1 - index] +=\n                    coefficients[source_degree]\
    \ *\n                    combinations_.binom(source_degree + 1, index) *\n   \
    \                 numbers_[index] * inverse;\n            }\n        }\n     \
    \   return result;\n    }\n\n    // Returns sum_{i=left}^{right-1} P(i).\n   \
    \ Mint polynomial_sum(\n        const std::vector<Mint>& coefficients,\n     \
    \   Mint left,\n        Mint right\n    ) const {\n        std::vector<Mint> prefix\
    \ = polynomial_prefix_sum(coefficients);\n        return bernoulli_detail::evaluate_polynomial(prefix,\
    \ right) -\n               bernoulli_detail::evaluate_polynomial(prefix, left);\n\
    \    }\n\n    // Returns sum_{i=0}^{count-1} (start + step*i)^degree.\n    Mint\
    \ arithmetic_progression_power_sum(\n        Mint start,\n        Mint step,\n\
    \        Mint count,\n        int degree\n    ) const {\n        assert(0 <= degree\
    \ && degree <= maximum());\n        std::vector<Mint> start_powers(degree + 1,\
    \ Mint(1));\n        std::vector<Mint> step_powers(degree + 1, Mint(1));\n   \
    \     for (int power = 0; power < degree; ++power) {\n            start_powers[power\
    \ + 1] = start_powers[power] * start;\n            step_powers[power + 1] = step_powers[power]\
    \ * step;\n        }\n\n        Mint result = 0;\n        for (int power = 0;\
    \ power <= degree; ++power) {\n            result += combinations_.binom(degree,\
    \ power) *\n                      start_powers[degree - power] * step_powers[power]\
    \ *\n                      power_sum(count, power);\n        }\n        return\
    \ result;\n    }\n\n   private:\n    static int checked_maximum(int maximum) {\n\
    \        assert(maximum >= 0);\n        assert(static_cast<uint64_t>(maximum)\
    \ + 1 < Mint::mod());\n        return maximum;\n    }\n\n    Combinatorics<Mint>\
    \ combinations_;\n    std::vector<Mint> numbers_;\n};\n\n}  // namespace math\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MATH_BERNOULLI_HPP\n"
  dependsOn:
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_fast.hpp
  - math/modint.hpp
  - math/combinatorics.hpp
  isVerificationFile: false
  path: math/bernoulli.hpp
  requiredBy:
  - math/combinatorial_sequences.hpp
  - math/all.hpp
  timestamp: '2026-07-11 02:52:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/bernoulli_utilities.test.cpp
  - verify/math/bell_number.test.cpp
  - verify/math/math_algorithms.test.cpp
  - verify/math/stirling_number_of_the_second_kind.test.cpp
  - verify/math/bernoulli_number.test.cpp
documentation_of: math/bernoulli.hpp
layout: document
title: Bernoulli Numbers and Power Sums
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
