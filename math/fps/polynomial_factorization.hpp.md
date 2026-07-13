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
  - icon: ':x:'
    path: verify/math/fps/polynomial_factorization.test.cpp
    title: verify/math/fps/polynomial_factorization.test.cpp
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
  code: "#ifndef M1UNE_FPS_POLYNOMIAL_FACTORIZATION_HPP\n#define M1UNE_FPS_POLYNOMIAL_FACTORIZATION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"formal_power_series.hpp\"\n\nnamespace\
    \ m1une {\nnamespace fps {\n\ntemplate <class Mint>\nstruct PolynomialFactor {\n\
    \    FormalPowerSeries<Mint> polynomial;\n    int multiplicity;\n};\n\ntemplate\
    \ <class Mint>\nstruct PolynomialFactorization {\n    Mint leading_coefficient;\n\
    \    std::vector<PolynomialFactor<Mint>> factors;\n};\n\nnamespace internal {\n\
    \ntemplate <class Mint>\nFormalPowerSeries<Mint> factorization_monic(FormalPowerSeries<Mint>\
    \ polynomial) {\n    polynomial.shrink();\n    if (polynomial.empty()) return\
    \ polynomial;\n    polynomial /= polynomial.back();\n    return polynomial;\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> factorization_multiply(\n\
    \    const FormalPowerSeries<Mint>& first,\n    const FormalPowerSeries<Mint>&\
    \ second\n) {\n    if (first.empty() || second.empty()) return {};\n    FormalPowerSeries<Mint>\
    \ result(first.size() + second.size() - 1);\n    for (int i = 0; i < int(first.size());\
    \ i++) {\n        for (int j = 0; j < int(second.size()); j++) {\n           \
    \ result[i + j] += first[i] * second[j];\n        }\n    }\n    result.shrink();\n\
    \    return result;\n}\n\ntemplate <class Mint>\nstd::pair<FormalPowerSeries<Mint>,\
    \ FormalPowerSeries<Mint>> factorization_divmod(\n    FormalPowerSeries<Mint>\
    \ dividend,\n    FormalPowerSeries<Mint> divisor\n) {\n    dividend.shrink();\n\
    \    divisor.shrink();\n    assert(!divisor.empty());\n    if (dividend.size()\
    \ < divisor.size()) return std::make_pair(FormalPowerSeries<Mint>(), dividend);\n\
    \n    FormalPowerSeries<Mint> quotient(dividend.size() - divisor.size() + 1);\n\
    \    const Mint inverse_leading = divisor.back().inv();\n    for (int i = int(dividend.size())\
    \ - 1; i >= int(divisor.size()) - 1; i--) {\n        const Mint coefficient =\
    \ dividend[i] * inverse_leading;\n        const int shift = i - int(divisor.size())\
    \ + 1;\n        quotient[shift] = coefficient;\n        if (coefficient == Mint(0))\
    \ continue;\n        for (int j = 0; j < int(divisor.size()); j++) {\n       \
    \     dividend[shift + j] -= coefficient * divisor[j];\n        }\n    }\n   \
    \ quotient.shrink();\n    dividend.resize(divisor.size() - 1);\n    dividend.shrink();\n\
    \    return std::make_pair(std::move(quotient), std::move(dividend));\n}\n\ntemplate\
    \ <class Mint>\nFormalPowerSeries<Mint> factorization_gcd(\n    FormalPowerSeries<Mint>\
    \ first,\n    FormalPowerSeries<Mint> second\n) {\n    first.shrink();\n    second.shrink();\n\
    \    while (!second.empty()) {\n        FormalPowerSeries<Mint> remainder =\n\
    \            factorization_divmod(std::move(first), second).second;\n        first\
    \ = std::move(second);\n        second = std::move(remainder);\n    }\n    return\
    \ factorization_monic(std::move(first));\n}\n\ntemplate <class Mint>\nFormalPowerSeries<Mint>\
    \ factorization_multiply_mod(\n    const FormalPowerSeries<Mint>& first,\n   \
    \ const FormalPowerSeries<Mint>& second,\n    const FormalPowerSeries<Mint>& modulus\n\
    ) {\n    return factorization_divmod(factorization_multiply(first, second), modulus).second;\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> factorization_power_mod(\n\
    \    FormalPowerSeries<Mint> base,\n    uint64_t exponent,\n    const FormalPowerSeries<Mint>&\
    \ modulus\n) {\n    FormalPowerSeries<Mint> result(1, Mint(1));\n    result =\
    \ factorization_divmod(std::move(result), modulus).second;\n    base = factorization_divmod(std::move(base),\
    \ modulus).second;\n    while (exponent > 0) {\n        if (exponent & 1) result\
    \ = factorization_multiply_mod(result, base, modulus);\n        exponent >>= 1;\n\
    \        if (exponent > 0) base = factorization_multiply_mod(base, base, modulus);\n\
    \    }\n    return result;\n}\n\nstruct PolynomialFactorizationRandom {\n    uint64_t\
    \ state;\n\n    uint64_t operator()() {\n        state ^= state << 7;\n      \
    \  state ^= state >> 9;\n        return state;\n    }\n};\n\ntemplate <class Mint>\n\
    FormalPowerSeries<Mint> factorization_random_polynomial(\n    int coefficient_count,\n\
    \    PolynomialFactorizationRandom& random\n) {\n    FormalPowerSeries<Mint> result(coefficient_count);\n\
    \    const uint64_t mod = Mint::mod();\n    for (Mint& coefficient : result) coefficient\
    \ = Mint(random() % mod);\n    result.shrink();\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nFormalPowerSeries<Mint> equal_degree_separator_odd(\n    const\
    \ FormalPowerSeries<Mint>& random_polynomial,\n    int factor_degree,\n    const\
    \ FormalPowerSeries<Mint>& modulus\n) {\n    FormalPowerSeries<Mint> power = factorization_power_mod(\n\
    \        random_polynomial, (uint64_t(Mint::mod()) - 1) / 2, modulus);\n    FormalPowerSeries<Mint>\
    \ result(1, Mint(1));\n    for (int i = 0; i < factor_degree; i++) {\n       \
    \ result = factorization_multiply_mod(result, power, modulus);\n        if (i\
    \ + 1 < factor_degree) {\n            power = factorization_power_mod(power, Mint::mod(),\
    \ modulus);\n        }\n    }\n    if (result.empty()) result.resize(1);\n   \
    \ result[0] -= Mint(1);\n    result.shrink();\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nFormalPowerSeries<Mint> equal_degree_separator_two(\n    const\
    \ FormalPowerSeries<Mint>& random_polynomial,\n    int factor_degree,\n    const\
    \ FormalPowerSeries<Mint>& modulus\n) {\n    FormalPowerSeries<Mint> power =\n\
    \        factorization_divmod(random_polynomial, modulus).second;\n    FormalPowerSeries<Mint>\
    \ result;\n    for (int i = 0; i < factor_degree; i++) {\n        result += power;\n\
    \        result.shrink();\n        if (i + 1 < factor_degree) {\n            power\
    \ = factorization_multiply_mod(power, power, modulus);\n        }\n    }\n   \
    \ return result;\n}\n\ntemplate <class Mint>\nstd::vector<FormalPowerSeries<Mint>>\
    \ equal_degree_factorization(\n    FormalPowerSeries<Mint> polynomial,\n    int\
    \ factor_degree,\n    PolynomialFactorizationRandom& random\n) {\n    using Fps\
    \ = FormalPowerSeries<Mint>;\n    polynomial = factorization_monic(std::move(polynomial));\n\
    \    std::vector<Fps> queue(1, std::move(polynomial));\n    std::vector<Fps> result;\n\
    \    for (int head = 0; head < int(queue.size()); head++) {\n        Fps current\
    \ = factorization_monic(std::move(queue[head]));\n        const int degree = int(current.size())\
    \ - 1;\n        if (degree == factor_degree) {\n            result.push_back(std::move(current));\n\
    \            continue;\n        }\n\n        Fps divisor;\n        do {\n    \
    \        Fps random_polynomial =\n                factorization_random_polynomial<Mint>(degree,\
    \ random);\n            Fps separator = Mint::mod() == 2\n                ? equal_degree_separator_two(random_polynomial,\
    \ factor_degree, current)\n                : equal_degree_separator_odd(random_polynomial,\
    \ factor_degree, current);\n            divisor = factorization_gcd(current, std::move(separator));\n\
    \        } while (divisor.size() <= 1 || divisor.size() == current.size());\n\n\
    \        Fps quotient = factorization_divmod(current, divisor).first;\n      \
    \  queue.push_back(std::move(divisor));\n        queue.push_back(std::move(quotient));\n\
    \    }\n    return result;\n}\n\n}  // namespace internal\n\ntemplate <class Mint>\n\
    PolynomialFactorization<Mint> polynomial_factorize(\n    FormalPowerSeries<Mint>\
    \ polynomial,\n    uint64_t seed = 88172645463325252ULL\n) {\n    using Fps =\
    \ FormalPowerSeries<Mint>;\n    polynomial.shrink();\n    assert(!polynomial.empty());\n\
    \n    const Mint leading_coefficient = polynomial.back();\n    polynomial /= leading_coefficient;\n\
    \    std::vector<PolynomialFactor<Mint>> factors;\n    if (polynomial.size() ==\
    \ 1) return {leading_coefficient, std::move(factors)};\n\n    if (seed == 0) seed\
    \ = 88172645463325252ULL;\n    internal::PolynomialFactorizationRandom random{seed};\n\
    \    const Fps x = Fps({Mint(0), Mint(1)});\n    Fps frobenius = x;\n    for (int\
    \ degree = 1;\n         polynomial.size() > 1 && 2 * degree <= int(polynomial.size())\
    \ - 1;\n         degree++) {\n        frobenius = internal::factorization_power_mod(\n\
    \            std::move(frobenius), Mint::mod(), polynomial);\n        Fps difference\
    \ = frobenius - x;\n        difference.shrink();\n        Fps product = internal::factorization_gcd(polynomial,\
    \ std::move(difference));\n        if (product.size() <= 1) continue;\n\n    \
    \    std::vector<Fps> distinct = internal::equal_degree_factorization(\n     \
    \       std::move(product), degree, random);\n        for (Fps& factor : distinct)\
    \ {\n            int multiplicity = 0;\n            while (factor.size() <= polynomial.size())\
    \ {\n                auto division = internal::factorization_divmod(polynomial,\
    \ factor);\n                if (!division.second.empty()) break;\n           \
    \     polynomial = std::move(division.first);\n                multiplicity++;\n\
    \            }\n            assert(multiplicity > 0);\n            factors.push_back({std::move(factor),\
    \ multiplicity});\n        }\n    }\n    if (polynomial.size() > 1) {\n      \
    \  factors.push_back({internal::factorization_monic(std::move(polynomial)), 1});\n\
    \    }\n\n    auto less = [](const PolynomialFactor<Mint>& first,\n          \
    \         const PolynomialFactor<Mint>& second) {\n        if (first.polynomial.size()\
    \ != second.polynomial.size()) {\n            return first.polynomial.size() <\
    \ second.polynomial.size();\n        }\n        for (int i = int(first.polynomial.size())\
    \ - 1; i >= 0; i--) {\n            if (first.polynomial[i].val() != second.polynomial[i].val())\
    \ {\n                return first.polynomial[i].val() < second.polynomial[i].val();\n\
    \            }\n        }\n        return false;\n    };\n    std::sort(factors.begin(),\
    \ factors.end(), less);\n\n    std::vector<PolynomialFactor<Mint>> merged;\n \
    \   for (PolynomialFactor<Mint>& factor : factors) {\n        if (!merged.empty()\
    \ && merged.back().polynomial == factor.polynomial) {\n            merged.back().multiplicity\
    \ += factor.multiplicity;\n        } else {\n            merged.push_back(std::move(factor));\n\
    \        }\n    }\n    return {leading_coefficient, std::move(merged)};\n}\n\n\
    }  // namespace fps\n}  // namespace m1une\n\n#endif  // M1UNE_FPS_POLYNOMIAL_FACTORIZATION_HPP\n"
  dependsOn:
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: math/fps/polynomial_factorization.hpp
  requiredBy:
  - math/all.hpp
  - math/fps/all.hpp
  timestamp: '2026-07-13 23:10:39+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/polynomial_factorization.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
documentation_of: math/fps/polynomial_factorization.hpp
layout: document
title: Polynomial Factorization
---

## Overview

This header factors a nonzero polynomial over a prime field into distinct monic
irreducible factors and their multiplicities. It uses distinct-degree
factorization followed by randomized Cantor-Zassenhaus equal-degree splitting.

The original leading coefficient is returned separately, so non-monic and
constant polynomials are supported. For a returned result `result`,

$$
f(x) = \text{result.leading_coefficient}
       \prod_i \text{result.factors[i].polynomial}(x)^{
           \text{result.factors[i].multiplicity}}.
$$

## Requirements

`Mint` must represent a prime field and provide the usual arithmetic operators,
`inv()`, `val()`, and static `mod()`. Both `m1une::math::ModInt` and compatible
runtime-modulus types can be used. The modulus must fit in `uint64_t`.

## API

```cpp
template <class Mint>
struct PolynomialFactor {
    FormalPowerSeries<Mint> polynomial;
    int multiplicity;
};

template <class Mint>
struct PolynomialFactorization {
    Mint leading_coefficient;
    std::vector<PolynomialFactor<Mint>> factors;
};

template <class Mint>
PolynomialFactorization<Mint> polynomial_factorize(
    FormalPowerSeries<Mint> polynomial,
    uint64_t seed = 88172645463325252ULL
);
```

| Interface | Description | Complexity |
| --- | --- | --- |
| `PolynomialFactor` | One monic irreducible factor and its positive multiplicity. | -- |
| `PolynomialFactorization` | Original leading coefficient and all distinct factors. | -- |
| `polynomial_factorize(polynomial, seed)` | Factors a nonzero polynomial over the field represented by `Mint`. | $O(n^4 \log p)$ field operations in the worst case; typically much faster |

The implementation uses quadratic polynomial multiplication and division. It is
intended for the small and medium degrees common in factorization problems; in
particular, it comfortably handles Library Checker's degree-100 target.

The input is copied and is not mutated. The zero polynomial has no finite
factorization and is rejected by an assertion. A nonzero constant returns no
factors and stores that constant in `leading_coefficient`.

Equal-degree splitting is randomized. The default seed makes runs reproducible;
pass another nonzero seed when a different splitting sequence is desired. A
zero seed selects the default. Returned factors are sorted first by degree and
then by coefficients, and identical factors are merged.

## Example

```cpp
#include "math/fps/polynomial_factorization.hpp"
#include "math/modint.hpp"

#include <iostream>

int main() {
    using Mint = m1une::math::ModInt<17>;
    using Fps = m1une::fps::FormalPowerSeries<Mint>;

    Fps polynomial({Mint(2), Mint(11), Mint(12), Mint(1)});
    auto result = m1une::fps::polynomial_factorize(polynomial);

    for (const auto& factor : result.factors) {
        std::cout << factor.multiplicity << " "
                  << factor.polynomial.size() - 1 << "\n";
    }
}
```
