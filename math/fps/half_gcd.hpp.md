---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':question:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  - icon: ':question:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/fps_algorithms.test.cpp
    title: verify/math/fps/fps_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/half_gcd.test.cpp
    title: verify/math/fps/half_gcd.test.cpp
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
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
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_FPS_HALF_GCD_HPP\n#define M1UNE_FPS_HALF_GCD_HPP 1\n\n#include\
    \ <cassert>\n#include <optional>\n#include <utility>\n\n#include \"formal_power_series.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nstruct PolynomialMatrix2x2\
    \ {\n    using Fps = FormalPowerSeries<Mint>;\n\n    Fps a00;\n    Fps a01;\n\
    \    Fps a10;\n    Fps a11;\n\n    static PolynomialMatrix2x2 identity() {\n \
    \       return PolynomialMatrix2x2{Fps(1, Mint(1)), Fps(), Fps(), Fps(1, Mint(1))};\n\
    \    }\n\n    std::pair<Fps, Fps> apply(const Fps& first, const Fps& second) const\
    \ {\n        Fps result_first = a00 * first + a01 * second;\n        Fps result_second\
    \ = a10 * first + a11 * second;\n        result_first.shrink();\n        result_second.shrink();\n\
    \        return std::make_pair(std::move(result_first), std::move(result_second));\n\
    \    }\n\n    friend PolynomialMatrix2x2 operator*(const PolynomialMatrix2x2&\
    \ lhs,\n                                          const PolynomialMatrix2x2& rhs)\
    \ {\n        PolynomialMatrix2x2 result;\n        result.a00 = lhs.a00 * rhs.a00\
    \ + lhs.a01 * rhs.a10;\n        result.a01 = lhs.a00 * rhs.a01 + lhs.a01 * rhs.a11;\n\
    \        result.a10 = lhs.a10 * rhs.a00 + lhs.a11 * rhs.a10;\n        result.a11\
    \ = lhs.a10 * rhs.a01 + lhs.a11 * rhs.a11;\n        result.a00.shrink();\n   \
    \     result.a01.shrink();\n        result.a10.shrink();\n        result.a11.shrink();\n\
    \        return result;\n    }\n};\n\nnamespace internal {\n\ntemplate <class\
    \ Mint>\nvoid polynomial_euclidean_step(PolynomialMatrix2x2<Mint>& matrix,\n \
    \                              std::pair<FormalPowerSeries<Mint>,\n          \
    \                               FormalPowerSeries<Mint>>& values) {\n    using\
    \ Fps = FormalPowerSeries<Mint>;\n    assert(!values.second.empty());\n\n    auto\
    \ division = values.first.divmod(values.second);\n    Fps next_a10 = matrix.a00\
    \ - matrix.a10 * division.first;\n    Fps next_a11 = matrix.a01 - matrix.a11 *\
    \ division.first;\n    next_a10.shrink();\n    next_a11.shrink();\n\n    matrix.a00\
    \ = std::move(matrix.a10);\n    matrix.a01 = std::move(matrix.a11);\n    matrix.a10\
    \ = std::move(next_a10);\n    matrix.a11 = std::move(next_a11);\n    values.first\
    \ = std::move(values.second);\n    values.second = std::move(division.second);\n\
    }\n\ntemplate <class Mint>\nPolynomialMatrix2x2<Mint> half_gcd_impl(\n    std::pair<FormalPowerSeries<Mint>,\
    \ FormalPowerSeries<Mint>> values) {\n    using Matrix = PolynomialMatrix2x2<Mint>;\n\
    \n    const int first_size = int(values.first.size());\n    const int half_size\
    \ = (first_size + 1) / 2;\n    if (int(values.second.size()) <= half_size) return\
    \ Matrix::identity();\n\n    Matrix first_matrix =\n        half_gcd_impl<Mint>(std::make_pair(values.first\
    \ >> half_size, values.second >> half_size));\n    values = first_matrix.apply(values.first,\
    \ values.second);\n    if (int(values.second.size()) <= half_size) return first_matrix;\n\
    \n    polynomial_euclidean_step(first_matrix, values);\n    if (int(values.second.size())\
    \ <= half_size) return first_matrix;\n\n    const int first_degree = int(values.first.size())\
    \ - 1;\n    const int shift = 2 * half_size - first_degree;\n    assert(shift\
    \ >= 0);\n    values.first >>= shift;\n    values.second >>= shift;\n    return\
    \ half_gcd_impl<Mint>(std::move(values)) * first_matrix;\n}\n\ntemplate <class\
    \ Mint>\nPolynomialMatrix2x2<Mint> polynomial_gcd_matrix(FormalPowerSeries<Mint>\
    \ first,\n                                                FormalPowerSeries<Mint>\
    \ second) {\n    using Matrix = PolynomialMatrix2x2<Mint>;\n    first.shrink();\n\
    \    second.shrink();\n\n    if (first.size() < second.size()) {\n        Matrix\
    \ result = polynomial_gcd_matrix(std::move(second), std::move(first));\n     \
    \   std::swap(result.a00, result.a01);\n        std::swap(result.a10, result.a11);\n\
    \        return result;\n    }\n\n    std::pair<FormalPowerSeries<Mint>, FormalPowerSeries<Mint>>\
    \ values(\n        std::move(first), std::move(second));\n    Matrix result =\
    \ Matrix::identity();\n    while (true) {\n        Matrix block = half_gcd_impl<Mint>(values);\n\
    \        values = block.apply(values.first, values.second);\n        if (values.second.empty())\
    \ return block * result;\n\n        polynomial_euclidean_step(block, values);\n\
    \        if (values.second.empty()) return block * result;\n        result = block\
    \ * result;\n    }\n}\n\n}  // namespace internal\n\ntemplate <class Mint>\nPolynomialMatrix2x2<Mint>\
    \ half_gcd(FormalPowerSeries<Mint> first,\n                                  \
    \ FormalPowerSeries<Mint> second) {\n    first.shrink();\n    second.shrink();\n\
    \    assert(first.size() >= second.size());\n    return internal::half_gcd_impl<Mint>(std::make_pair(std::move(first),\
    \ std::move(second)));\n}\n\ntemplate <class Mint>\nstruct PolynomialExtendedGcdResult\
    \ {\n    FormalPowerSeries<Mint> gcd;\n    FormalPowerSeries<Mint> x;\n    FormalPowerSeries<Mint>\
    \ y;\n};\n\ntemplate <class Mint>\nPolynomialExtendedGcdResult<Mint> polynomial_extended_gcd(\n\
    \    const FormalPowerSeries<Mint>& first, const FormalPowerSeries<Mint>& second)\
    \ {\n    PolynomialMatrix2x2<Mint> matrix = internal::polynomial_gcd_matrix(first,\
    \ second);\n    auto values = matrix.apply(first, second);\n\n    if (!values.first.empty())\
    \ {\n        const Mint inverse_leading = values.first.back().inv();\n       \
    \ values.first *= inverse_leading;\n        matrix.a00 *= inverse_leading;\n \
    \       matrix.a01 *= inverse_leading;\n    }\n    return PolynomialExtendedGcdResult<Mint>{std::move(values.first),\
    \ std::move(matrix.a00),\n                                             std::move(matrix.a01)};\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> polynomial_gcd(const FormalPowerSeries<Mint>&\
    \ first,\n                                       const FormalPowerSeries<Mint>&\
    \ second) {\n    return polynomial_extended_gcd(first, second).gcd;\n}\n\ntemplate\
    \ <class Mint>\nstd::optional<FormalPowerSeries<Mint>> polynomial_inv_mod(\n \
    \   const FormalPowerSeries<Mint>& polynomial, FormalPowerSeries<Mint> modulus)\
    \ {\n    modulus.shrink();\n    assert(!modulus.empty());\n    auto result = polynomial_extended_gcd(polynomial,\
    \ modulus);\n    if (result.gcd.size() != 1) return std::nullopt;\n    return\
    \ result.x % modulus;\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_FPS_HALF_GCD_HPP\n"
  dependsOn:
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: math/fps/half_gcd.hpp
  requiredBy:
  - math/all.hpp
  - math/fps/all.hpp
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/half_gcd.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
documentation_of: math/fps/half_gcd.hpp
layout: document
title: Polynomial Half-GCD
---

## Overview

This header accelerates the Euclidean algorithm for polynomials over a field.
`half_gcd(a, b)` batches roughly half of the remaining Euclidean steps into a
unimodular polynomial matrix. The same machinery provides a monic polynomial
GCD, Bézout coefficients, and inversion modulo a polynomial.

Coefficients are stored from the constant term upward. Trailing zero
coefficients are ignored by every public algorithm.

## Requirements

`Mint` must represent a field and provide the interface expected by
`FormalPowerSeries<Mint>`, including `inv()`. The supplied static modular
integer types meet this requirement when their modulus is prime.

For `half_gcd(first, second)`, the normalized degree of `first` must be at least
the normalized degree of `second`. The returned matrix `M` combines several
consecutive steps from the beginning of the polynomial Euclidean algorithm:

\[
(c,d)^T = M (first,second)^T, \qquad \gcd(c,d)=\gcd(first,second).
\]

The recursion chooses the block from the high halves of the inputs. If the
second input is already below the half-size boundary, the result is the
identity; otherwise the block strictly decreases its degree. This convention
lets the full GCD routine alternate half-GCD blocks with single Euclidean steps.

## Public Interface

Let `Fps` denote `FormalPowerSeries<Mint>`.

```cpp
template <class Mint>
struct PolynomialMatrix2x2 {
    Fps a00, a01, a10, a11;

    static PolynomialMatrix2x2 identity();
    std::pair<Fps, Fps> apply(const Fps& first, const Fps& second) const;
    friend PolynomialMatrix2x2 operator*(
        const PolynomialMatrix2x2& lhs, const PolynomialMatrix2x2& rhs);
};

template <class Mint>
PolynomialMatrix2x2<Mint> half_gcd(Fps first, Fps second);

template <class Mint>
struct PolynomialExtendedGcdResult {
    Fps gcd, x, y;
};

template <class Mint>
PolynomialExtendedGcdResult<Mint> polynomial_extended_gcd(
    const Fps& first, const Fps& second);

template <class Mint>
Fps polynomial_gcd(const Fps& first, const Fps& second);

template <class Mint>
std::optional<Fps> polynomial_inv_mod(const Fps& polynomial, Fps modulus);
```

## Methods

Here, `n` is the larger normalized coefficient count and `M(n)` is the cost of
multiplying degree-`n` polynomials. With the supplied NTT convolution,
`M(n) = O(n log n)`.

| Method | Result | Complexity |
| --- | --- | --- |
| `PolynomialMatrix2x2::identity()` | The identity transformation. | $O(1)$ |
| `matrix.apply(a, b)` | Applies the matrix to the polynomial pair. | $O(M(n))$ |
| `lhs * rhs` | Composes two polynomial matrices. | $O(M(n))$ |
| `half_gcd(a, b)` | Combines the first batch of Euclidean-algorithm steps into one matrix. | $O(M(n) \log n)$ |
| `polynomial_extended_gcd(a, b)` | Monic `gcd` and `x`, `y` satisfying `a * x + b * y = gcd`. | $O(M(n) \log n)$ |
| `polynomial_gcd(a, b)` | The monic GCD; returns zero only when both inputs are zero. | $O(M(n) \log n)$ |
| `polynomial_inv_mod(f, g)` | `h` with `f * h = 1 (mod g)`, or `nullopt` when none exists. | $O(M(n) \log n)$ |

`polynomial_inv_mod` requires a nonzero modulus. None of the functions mutate
their arguments.

## Example

```cpp
#include "math/fps/half_gcd.hpp"
#include "math/modint.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps common = {1, 1};
    Fps a = common * Fps{2, 0, 1};
    Fps b = common * Fps{3, 1};

    Fps gcd = m1une::fps::polynomial_gcd(a, b);
    auto extended = m1une::fps::polynomial_extended_gcd(a, b);
    auto inverse = m1une::fps::polynomial_inv_mod(Fps{1, 1}, Fps{1, 0, 1});
    Fps bezout = extended.x * a + extended.y * b;
    bezout.shrink();

    return gcd == common && bezout == common && inverse.has_value()
               ? 0
               : 1;
}
```
