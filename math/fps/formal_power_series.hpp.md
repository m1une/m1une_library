---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
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
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/counting.hpp
    title: Graph Counting
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  - icon: ':question:'
    path: math/bernoulli.hpp
    title: Bernoulli Numbers and Power Sums
  - icon: ':question:'
    path: math/combinatorial_sequences.hpp
    title: Combinatorial Sequences
  - icon: ':question:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  - icon: ':question:'
    path: math/fps/composition.hpp
    title: Formal Power Series Composition
  - icon: ':question:'
    path: math/fps/half_gcd.hpp
    title: Polynomial Half-GCD
  - icon: ':question:'
    path: math/fps/lagrange_inversion.hpp
    title: Lagrange Inversion Formula
  - icon: ':question:'
    path: math/fps/linear_recurrence.hpp
    title: Linear Recurrence and Bostan-Mori
  - icon: ':question:'
    path: math/fps/multipoint_evaluation.hpp
    title: Multipoint Evaluation and Interpolation
  - icon: ':question:'
    path: math/fps/polynomial_factorization.hpp
    title: Polynomial Factorization
  - icon: ':question:'
    path: math/partition_function.hpp
    title: Partition Function
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_counting.test.cpp
    title: verify/graph/graph_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
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
    path: verify/math/fps/composition.test.cpp
    title: verify/math/fps/composition.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/exp_of_formal_power_series.test.cpp
    title: verify/math/fps/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/fps_algorithms.test.cpp
    title: verify/math/fps/fps_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/half_gcd.test.cpp
    title: verify/math/fps/half_gcd.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/inv_of_formal_power_series.test.cpp
    title: verify/math/fps/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
    title: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/lagrange_inversion.test.cpp
    title: verify/math/fps/lagrange_inversion.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/multipoint_evaluation.test.cpp
    title: verify/math/fps/multipoint_evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/polynomial_factorization.test.cpp
    title: verify/math/fps/polynomial_factorization.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/polynomial_interpolation.test.cpp
    title: verify/math/fps/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/polynomial_taylor_shift.test.cpp
    title: verify/math/fps/polynomial_taylor_shift.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/pow_of_formal_power_series.test.cpp
    title: verify/math/fps/pow_of_formal_power_series.test.cpp
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':x:'
    path: verify/math/partition_function.test.cpp
    title: verify/math/partition_function.test.cpp
  - icon: ':x:'
    path: verify/math/stirling_number_of_the_second_kind.test.cpp
    title: verify/math/stirling_number_of_the_second_kind.test.cpp
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_FPS_FORMAL_POWER_SERIES_HPP\n#define M1UNE_FPS_FORMAL_POWER_SERIES_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <optional>\n#include <utility>\n#include <vector>\n\n#include \"../modular_square_root.hpp\"\
    \n#include \"convolution.hpp\"\n\nnamespace m1une {\nnamespace fps {\n\ntemplate\
    \ <class Mint>\nstruct FormalPowerSeries : std::vector<Mint> {\n    using std::vector<Mint>::vector;\n\
    \    using Fps = FormalPowerSeries;\n\n    FormalPowerSeries() = default;\n  \
    \  FormalPowerSeries(const std::vector<Mint>& values) : std::vector<Mint>(values)\
    \ {}\n    FormalPowerSeries(std::vector<Mint>&& values) : std::vector<Mint>(std::move(values))\
    \ {}\n\n    Fps& shrink() {\n        while (!this->empty() && this->back() ==\
    \ Mint(0)) this->pop_back();\n        return *this;\n    }\n\n    Fps pre(int\
    \ degree) const {\n        assert(degree >= 0);\n        Fps result(this->begin(),\
    \ this->begin() + std::min<int>(degree, this->size()));\n        result.resize(degree);\n\
    \        return result;\n    }\n\n    Fps reversed(int size = -1) const {\n  \
    \      Fps result = *this;\n        if (size >= 0) result.resize(size);\n    \
    \    std::reverse(result.begin(), result.end());\n        return result;\n   \
    \ }\n\n    Fps& operator+=(const Fps& rhs) {\n        if (this->size() < rhs.size())\
    \ this->resize(rhs.size());\n        for (int i = 0; i < int(rhs.size()); i++)\
    \ (*this)[i] += rhs[i];\n        return *this;\n    }\n\n    Fps& operator-=(const\
    \ Fps& rhs) {\n        if (this->size() < rhs.size()) this->resize(rhs.size());\n\
    \        for (int i = 0; i < int(rhs.size()); i++) (*this)[i] -= rhs[i];\n   \
    \     return *this;\n    }\n\n    Fps& operator*=(const Fps& rhs) {\n        std::vector<Mint>\
    \ lhs(this->begin(), this->end());\n        *this = convolution(lhs, rhs);\n \
    \       return *this;\n    }\n\n    Fps& operator*=(Mint rhs) {\n        for (Mint&\
    \ value : *this) value *= rhs;\n        return *this;\n    }\n\n    Fps& operator/=(Mint\
    \ rhs) {\n        return *this *= rhs.inv();\n    }\n\n    Fps& operator<<=(int\
    \ shift) {\n        assert(shift >= 0);\n        this->insert(this->begin(), shift,\
    \ Mint(0));\n        return *this;\n    }\n\n    Fps& operator>>=(int shift) {\n\
    \        assert(shift >= 0);\n        if (shift >= int(this->size())) {\n    \
    \        this->clear();\n        } else {\n            this->erase(this->begin(),\
    \ this->begin() + shift);\n        }\n        return *this;\n    }\n\n    Fps\
    \ operator+() const {\n        return *this;\n    }\n\n    Fps operator-() const\
    \ {\n        Fps result = *this;\n        for (Mint& value : result) value = Mint(0)\
    \ - value;\n        return result;\n    }\n\n    friend Fps operator+(Fps lhs,\
    \ const Fps& rhs) {\n        return lhs += rhs;\n    }\n\n    friend Fps operator-(Fps\
    \ lhs, const Fps& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Fps\
    \ operator*(Fps lhs, const Fps& rhs) {\n        return lhs *= rhs;\n    }\n\n\
    \    friend Fps operator*(Fps lhs, Mint rhs) {\n        return lhs *= rhs;\n \
    \   }\n\n    friend Fps operator*(Mint lhs, Fps rhs) {\n        return rhs *=\
    \ lhs;\n    }\n\n    friend Fps operator/(Fps lhs, Mint rhs) {\n        return\
    \ lhs /= rhs;\n    }\n\n    friend Fps operator<<(Fps lhs, int shift) {\n    \
    \    return lhs <<= shift;\n    }\n\n    friend Fps operator>>(Fps lhs, int shift)\
    \ {\n        return lhs >>= shift;\n    }\n\n    Fps derivative() const {\n  \
    \      if (this->empty()) return {};\n        Fps result(this->size() - 1);\n\
    \        for (int i = 1; i < int(this->size()); i++) result[i - 1] = (*this)[i]\
    \ * Mint(i);\n        return result;\n    }\n\n    Fps integral() const {\n  \
    \      Fps result(this->size() + 1);\n        if (this->empty()) return result;\n\
    \        assert(this->size() < Mint::mod());\n\n        std::vector<Mint> inverse(this->size()\
    \ + 1);\n        inverse[1] = 1;\n        for (int i = 2; i <= int(this->size());\
    \ i++) {\n            inverse[i] = Mint(0) - Mint(Mint::mod() / uint32_t(i)) *\
    \ inverse[Mint::mod() % uint32_t(i)];\n        }\n        for (int i = 0; i <\
    \ int(this->size()); i++) result[i + 1] = (*this)[i] * inverse[i + 1];\n     \
    \   return result;\n    }\n\n    Mint evaluate(Mint x) const {\n        Mint result\
    \ = 0;\n        for (auto it = this->rbegin(); it != this->rend(); ++it) result\
    \ = result * x + *it;\n        return result;\n    }\n\n    Fps inv(int degree\
    \ = -1) const {\n        if (degree < 0) degree = int(this->size());\n       \
    \ assert(degree >= 0);\n        if (degree == 0) return {};\n        assert(!this->empty()\
    \ && (*this)[0] != Mint(0));\n\n        Fps result(1, (*this)[0].inv());\n   \
    \     for (int size = 1; size < degree; size <<= 1) {\n            const int next_size\
    \ = std::min(size << 1, degree);\n            const int transform_size = size\
    \ << 1;\n            if (size >= 32 && (Mint::mod() - 1) % uint32_t(transform_size)\
    \ == 0) {\n                // Newton's g <- g(2-fg), restricted to the newly determined\n\
    \                // half.  Keeping g in the frequency domain avoids two general\n\
    \                // convolutions and their 2x larger padding.\n              \
    \  std::vector<Mint> transformed_f(transform_size);\n                std::copy_n(this->begin(),\
    \ std::min<int>(this->size(), next_size),\n                            transformed_f.begin());\n\
    \                std::vector<Mint> transformed_g(transform_size);\n          \
    \      std::copy(result.begin(), result.end(), transformed_g.begin());\n     \
    \           internal::ntt(transformed_f, false);\n                internal::ntt(transformed_g,\
    \ false);\n\n                std::vector<Mint> error(transform_size);\n      \
    \          for (int i = 0; i < transform_size; i++)\n                    error[i]\
    \ = transformed_f[i] * transformed_g[i];\n                internal::ntt(error,\
    \ true);\n                std::fill(error.begin(), error.begin() + size, Mint(0));\n\
    \                internal::ntt(error, false);\n                for (int i = 0;\
    \ i < transform_size; i++) error[i] *= transformed_g[i];\n                internal::ntt(error,\
    \ true);\n\n                result.resize(next_size);\n                for (int\
    \ i = size; i < next_size; i++) result[i] = Mint(0) - error[i];\n            \
    \    continue;\n            }\n            Fps product = this->pre(next_size)\
    \ * result;\n            product.resize(next_size);\n            for (Mint& value\
    \ : product) value = Mint(0) - value;\n            product[0] += Mint(2);\n  \
    \          result = (result * product).pre(next_size);\n        }\n        return\
    \ result.pre(degree);\n    }\n\n    Fps log(int degree = -1) const {\n       \
    \ if (degree < 0) degree = int(this->size());\n        assert(degree >= 0);\n\
    \        if (degree == 0) return {};\n        assert(!this->empty() && (*this)[0]\
    \ == Mint(1));\n        return (derivative() * inv(degree)).pre(degree - 1).integral();\n\
    \    }\n\n    Fps exp(int degree = -1) const {\n        if (degree < 0) degree\
    \ = int(this->size());\n        assert(degree >= 0);\n        if (degree == 0)\
    \ return {};\n        assert(this->empty() || (*this)[0] == Mint(0));\n\n    \
    \    Fps result(1, Mint(1));\n        for (int size = 1; size < degree; size <<=\
    \ 1) {\n            const int next_size = std::min(size << 1, degree);\n     \
    \       Fps correction = this->pre(next_size) - result.log(next_size);\n     \
    \       correction[0] += Mint(1);\n            result = (result * correction).pre(next_size);\n\
    \        }\n        return result.pre(degree);\n    }\n\n    Fps pow(long long\
    \ exponent, int degree = -1) const {\n        if (degree < 0) degree = int(this->size());\n\
    \        assert(exponent >= 0 && degree >= 0);\n        if (degree == 0) return\
    \ {};\n        if (exponent == 0) {\n            Fps result(degree);\n       \
    \     result[0] = 1;\n            return result;\n        }\n\n        int first\
    \ = 0;\n        while (first < int(this->size()) && (*this)[first] == Mint(0))\
    \ first++;\n        if (first == int(this->size()) || first > (degree - 1) / exponent)\
    \ return Fps(degree);\n\n        const int shift = int(first * exponent);\n  \
    \      const Mint leading = (*this)[first];\n        Fps normalized = (*this >>\
    \ first) / leading;\n        Fps result = (normalized.log(degree - shift) * Mint(exponent)).exp(degree\
    \ - shift);\n        result *= leading.pow(exponent);\n        result <<= shift;\n\
    \        result.resize(degree);\n        return result;\n    }\n\n    std::optional<Fps>\
    \ sqrt(int degree = -1) const {\n        if (degree < 0) degree = int(this->size());\n\
    \        assert(degree >= 0);\n        if (degree == 0) return Fps();\n\n    \
    \    int first = 0;\n        while (first < int(this->size()) && (*this)[first]\
    \ == Mint(0)) first++;\n        if (first == int(this->size())) return Fps(degree);\n\
    \        if (first >= degree) return Fps(degree);\n        if (first & 1) return\
    \ std::nullopt;\n\n        const int shift = first / 2;\n        auto leading_root\
    \ = m1une::math::modular_square_root((*this)[first]);\n        if (!leading_root.has_value())\
    \ return std::nullopt;\n\n        const int result_degree = degree - shift;\n\
    \        Fps normalized = (*this >> first) / (*this)[first];\n        Fps result\
    \ = (normalized.log(result_degree) / Mint(2)).exp(result_degree);\n        result\
    \ *= *leading_root;\n        result <<= shift;\n        result.resize(degree);\n\
    \        return result;\n    }\n\n    std::pair<Fps, Fps> divmod(const Fps& divisor)\
    \ const {\n        Fps dividend = *this;\n        Fps normalized_divisor = divisor;\n\
    \        dividend.shrink();\n        normalized_divisor.shrink();\n        assert(!normalized_divisor.empty());\n\
    \n        if (dividend.size() < normalized_divisor.size()) return std::make_pair(Fps(),\
    \ dividend);\n        const int quotient_size = int(dividend.size() - normalized_divisor.size()\
    \ + 1);\n        Fps quotient =\n            (dividend.reversed().pre(quotient_size)\
    \ * normalized_divisor.reversed().inv(quotient_size))\n                .pre(quotient_size)\n\
    \                .reversed();\n        quotient.shrink();\n        Fps remainder\
    \ = dividend - normalized_divisor * quotient;\n        remainder.resize(normalized_divisor.size()\
    \ - 1);\n        remainder.shrink();\n        return std::make_pair(std::move(quotient),\
    \ std::move(remainder));\n    }\n\n    Fps& operator/=(const Fps& rhs) {\n   \
    \     *this = divmod(rhs).first;\n        return *this;\n    }\n\n    Fps& operator%=(const\
    \ Fps& rhs) {\n        *this = divmod(rhs).second;\n        return *this;\n  \
    \  }\n\n    friend Fps operator/(Fps lhs, const Fps& rhs) {\n        return lhs\
    \ /= rhs;\n    }\n\n    friend Fps operator%(Fps lhs, const Fps& rhs) {\n    \
    \    return lhs %= rhs;\n    }\n\n    Fps taylor_shift(Mint shift) const {\n \
    \       const int n = int(this->size());\n        if (n == 0) return {};\n   \
    \     assert(uint32_t(n) < Mint::mod());\n\n        std::vector<Mint> factorial(n,\
    \ Mint(1));\n        std::vector<Mint> inverse_factorial(n, Mint(1));\n      \
    \  for (int i = 1; i < n; i++) factorial[i] = factorial[i - 1] * Mint(i);\n  \
    \      inverse_factorial[n - 1] = factorial[n - 1].inv();\n        for (int i\
    \ = n - 1; i > 0; i--) inverse_factorial[i - 1] = inverse_factorial[i] * Mint(i);\n\
    \n        Fps left(n);\n        Fps right(n);\n        Mint power = 1;\n     \
    \   for (int i = 0; i < n; i++) {\n            left[n - 1 - i] = (*this)[i] *\
    \ factorial[i];\n            right[i] = power * inverse_factorial[i];\n      \
    \      power *= shift;\n        }\n        Fps product = left * right;\n     \
    \   Fps result(n);\n        for (int i = 0; i < n; i++) result[i] = product[n\
    \ - 1 - i] * inverse_factorial[i];\n        return result;\n    }\n};\n\n}  //\
    \ namespace fps\n}  // namespace m1une\n\n#endif  // M1UNE_FPS_FORMAL_POWER_SERIES_HPP\n"
  dependsOn:
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: math/fps/formal_power_series.hpp
  requiredBy:
  - math/partition_function.hpp
  - math/combinatorial_sequences.hpp
  - math/all.hpp
  - math/all.hpp
  - math/bernoulli.hpp
  - math/fps/half_gcd.hpp
  - math/fps/composition.hpp
  - math/fps/all.hpp
  - math/fps/lagrange_inversion.hpp
  - math/fps/multipoint_evaluation.hpp
  - math/fps/linear_recurrence.hpp
  - math/fps/polynomial_factorization.hpp
  - graph/all.hpp
  - graph/counting.hpp
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/math/bernoulli_utilities.test.cpp
  - verify/math/bell_number.test.cpp
  - verify/math/partition_function.test.cpp
  - verify/math/math_algorithms.test.cpp
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/inv_of_formal_power_series.test.cpp
  - verify/math/fps/half_gcd.test.cpp
  - verify/math/fps/pow_of_formal_power_series.test.cpp
  - verify/math/fps/polynomial_interpolation.test.cpp
  - verify/math/fps/polynomial_factorization.test.cpp
  - verify/math/fps/exp_of_formal_power_series.test.cpp
  - verify/math/fps/multipoint_evaluation.test.cpp
  - verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
  - verify/math/fps/polynomial_taylor_shift.test.cpp
  - verify/math/fps/composition.test.cpp
  - verify/math/fps/lagrange_inversion.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
  - verify/math/stirling_number_of_the_second_kind.test.cpp
  - verify/math/bernoulli_number.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/graph_counting.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: math/fps/formal_power_series.hpp
layout: document
title: Formal Power Series
---

## Overview

`FormalPowerSeries<Mint>` is a vector-like polynomial and formal power
series type. Coefficients are stored from the constant term upward.

It provides the operations most often needed in polynomial problems:

* addition, subtraction, scalar multiplication, and fast multiplication;
* multiplication or division by a power of `x`;
* derivative, integral, and point evaluation;
* formal inverse, logarithm, exponential, integer power, and square root;
* polynomial quotient and remainder;
* Taylor shift from `f(x)` to `f(x + c)`.

## Type

```cpp
template <class Mint>
struct FormalPowerSeries : std::vector<Mint>;
```

`Mint` should be a static modular integer type with `mod()`, `val()`, `raw()`,
`pow()`, and `inv()`. The supplied `math/modint.hpp` types satisfy this
interface. Series functions assume a prime modulus, and degrees used by
integration must be smaller than the modulus.

## Basic Operations

Let `Fps` denote `FormalPowerSeries<Mint>`.
Here, `n` is the number of coefficients involved in the operation.

| Operation | Description | Complexity |
| --- | --- | --- |
| `f.shrink()` | Removes trailing zero coefficients. | $O(n)$ |
| `f.pre(n)` | Returns exactly the first `n` coefficients, padding with zero. | $O(n)$ |
| `f.reversed(n)` | Resizes to `n` when specified, then reverses coefficients. | $O(n)$ |
| `f + g`, `f - g` | Coefficient-wise addition or subtraction. | $O(n)$ |
| `f * g` | Polynomial convolution. | $O(n \log n)$ |
| `f * c`, `f / c` | Scalar multiplication or division. | $O(n)$ |
| `f << k` | Multiplies by $x^k$. | $O(n + k)$ |
| `f >> k` | Divides by $x^k$, discarding lower terms. | $O(n)$ |
| `f.derivative()` | Formal derivative. | $O(n)$ |
| `f.integral()` | Formal integral with constant term zero. | $O(n)$ |
| `f.evaluate(x)` | Evaluates by Horner's method. | $O(n)$ |

## Series Functions

| Method | Requirement | Result | Complexity |
| --- | --- | --- | --- |
| `f.inv(n)` | `f[0] != 0` | $1/f \pmod{x^n}$ | $O(n \log n)$ |
| `f.log(n)` | `f[0] == 1` | $\log f \pmod{x^n}$ | $O(n \log n)$ |
| `f.exp(n)` | `f[0] == 0` | $\exp f \pmod{x^n}$ | $O(n \log n)$ |
| `f.pow(k, n)` | `k >= 0` | $f^k \pmod{x^n}$ | $O(n \log n)$ |
| `f.sqrt(n)` | A square root exists | An optional $g$ with $g^2=f \pmod{x^n}$ | $O(n \log n)$ |

When `n` is omitted, the current series size is used. `sqrt` returns
`std::nullopt` if the leading degree is odd or its coefficient is not a
quadratic residue.

## Polynomial Operations

| Method | Description | Complexity |
| --- | --- | --- |
| `f.divmod(g)` | Returns the quotient and remainder of polynomial division. | $O(n \log n)$ |
| `f / g`, `f % g` | Returns only the quotient or remainder. | $O(n \log n)$ |
| `f.taylor_shift(c)` | Returns coefficients of `f(x + c)`. | $O(n \log n)$ |

The divisor must be nonzero. Taylor shift requires `f.size() < Mint::mod()`.

## Example

```cpp
#include "math/fps/formal_power_series.hpp"
#include "math/modint.hpp"
#include <iostream>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps f = {1, 2, 3};

    Fps inverse = f.inv(5);
    Fps logarithm = f.log(5);
    Fps cube = f.pow(3, 7);
    Fps shifted = f.taylor_shift(10);

    mint value = f.evaluate(4);
    std::cout << value << "\n";
}
```
