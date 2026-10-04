---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/cyclotomic_polynomial.test.cpp
    title: verify/math/cyclotomic_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/cyclotomic_polynomial.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <cstdint>\n#include <limits>\n#include <vector>\n\
    \n#line 1 \"math/prime_factorization.hpp\"\n\n\n\n#include <algorithm>\n#line\
    \ 7 \"math/prime_factorization.hpp\"\n#include <numeric>\n#include <utility>\n\
    #line 10 \"math/prime_factorization.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\nnamespace internal {\n\ninline uint64_t multiply_mod(uint64_t a, uint64_t\
    \ b, uint64_t mod) {\n    return static_cast<uint64_t>(static_cast<unsigned __int128>(a)\
    \ * b % mod);\n}\n\ninline uint64_t power_mod(uint64_t base, uint64_t exponent,\
    \ uint64_t mod) {\n    uint64_t result = 1;\n    while (exponent > 0) {\n    \
    \    if (exponent & 1) result = multiply_mod(result, base, mod);\n        base\
    \ = multiply_mod(base, base, mod);\n        exponent >>= 1;\n    }\n    return\
    \ result;\n}\n\ninline uint64_t pollard_random() {\n    static uint64_t state\
    \ = 0x123456789abcdef0ULL;\n    state += 0x9e3779b97f4a7c15ULL;\n    uint64_t\
    \ value = state;\n    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;\n    return value\
    \ ^ (value >> 31);\n}\n\n}  // namespace internal\n\ninline bool is_prime(uint64_t\
    \ value) {\n    if (value < 2) return false;\n    for (uint64_t prime : {2ULL,\
    \ 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {\n\
    \        if (value % prime == 0) return value == prime;\n    }\n\n    uint64_t\
    \ odd_part = value - 1;\n    int power_of_two = 0;\n    while ((odd_part & 1)\
    \ == 0) {\n        odd_part >>= 1;\n        power_of_two++;\n    }\n\n    for\
    \ (uint64_t base : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL})\
    \ {\n        if (base % value == 0) continue;\n        uint64_t x = internal::power_mod(base\
    \ % value, odd_part, value);\n        if (x == 1 || x == value - 1) continue;\n\
    \n        bool composite = true;\n        for (int i = 1; i < power_of_two; i++)\
    \ {\n            x = internal::multiply_mod(x, x, value);\n            if (x ==\
    \ value - 1) {\n                composite = false;\n                break;\n \
    \           }\n        }\n        if (composite) return false;\n    }\n    return\
    \ true;\n}\n\nnamespace internal {\n\ninline uint64_t pollard_rho(uint64_t value)\
    \ {\n    for (uint64_t prime : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,\
    \ 23ULL, 29ULL, 31ULL, 37ULL}) {\n        if (value % prime == 0) return prime;\n\
    \    }\n\n    while (true) {\n        const uint64_t constant = pollard_random()\
    \ % (value - 1) + 1;\n        uint64_t y = pollard_random() % (value - 1) + 1;\n\
    \        uint64_t x = 0;\n        uint64_t saved_y = 0;\n        uint64_t gcd\
    \ = 1;\n        uint64_t segment_length = 1;\n\n        auto advance = [&](uint64_t\
    \ current) {\n            return static_cast<uint64_t>(\n                (static_cast<unsigned\
    \ __int128>(multiply_mod(current, current, value)) + constant) % value);\n   \
    \     };\n\n        while (gcd == 1) {\n            x = y;\n            for (uint64_t\
    \ i = 0; i < segment_length; i++) y = advance(y);\n\n            for (uint64_t\
    \ offset = 0; offset < segment_length && gcd == 1; offset += 128) {\n        \
    \        saved_y = y;\n                uint64_t product = 1;\n               \
    \ const uint64_t block = std::min<uint64_t>(128, segment_length - offset);\n \
    \               for (uint64_t i = 0; i < block; i++) {\n                    y\
    \ = advance(y);\n                    const uint64_t difference = x > y ? x - y\
    \ : y - x;\n                    product = multiply_mod(product, difference, value);\n\
    \                }\n                gcd = std::gcd(product, value);\n        \
    \    }\n            segment_length <<= 1;\n        }\n\n        if (gcd == value)\
    \ {\n            do {\n                saved_y = advance(saved_y);\n         \
    \       const uint64_t difference = x > saved_y ? x - saved_y : saved_y - x;\n\
    \                gcd = std::gcd(difference, value);\n            } while (gcd\
    \ == 1);\n        }\n        if (gcd != value) return gcd;\n    }\n}\n\ninline\
    \ void factor_recursively(uint64_t value, std::vector<uint64_t>& factors) {\n\
    \    if (value == 1) return;\n    if (is_prime(value)) {\n        factors.push_back(value);\n\
    \        return;\n    }\n    const uint64_t divisor = pollard_rho(value);\n  \
    \  factor_recursively(divisor, factors);\n    factor_recursively(value / divisor,\
    \ factors);\n}\n\n}  // namespace internal\n\ninline std::vector<uint64_t> prime_factors(uint64_t\
    \ value) {\n    assert(value >= 1);\n    std::vector<uint64_t> result;\n    internal::factor_recursively(value,\
    \ result);\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline std::vector<std::pair<uint64_t, int>> prime_factorize(uint64_t value)\
    \ {\n    std::vector<uint64_t> factors = prime_factors(value);\n    std::vector<std::pair<uint64_t,\
    \ int>> result;\n    for (uint64_t prime : factors) {\n        if (result.empty()\
    \ || result.back().first != prime) {\n            result.emplace_back(prime, 1);\n\
    \        } else {\n            result.back().second++;\n        }\n    }\n   \
    \ return result;\n}\n\ninline std::vector<uint64_t> divisors(uint64_t value) {\n\
    \    std::vector<uint64_t> result = {1};\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        const int current_size = int(result.size());\n        uint64_t power\
    \ = 1;\n        for (int exponent = 1; exponent <= factor.second; exponent++)\
    \ {\n            power *= factor.first;\n            for (int i = 0; i < current_size;\
    \ i++) {\n                result.push_back(result[i] * power);\n            }\n\
    \        }\n    }\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline uint64_t euler_phi(uint64_t value) {\n    assert(value >= 1);\n  \
    \  uint64_t result = value;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        result = result / factor.first * (factor.first - 1);\n    }\n   \
    \ return result;\n}\n\ninline int mobius(uint64_t value) {\n    assert(value >=\
    \ 1);\n    int result = 1;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        if (factor.second >= 2) return 0;\n        result = -result;\n  \
    \  }\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 11 \"math/cyclotomic_polynomial.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <class T = long long>\nstd::vector<T> cyclotomic_polynomial(std::uint64_t\
    \ index) {\n    assert(index >= 1);\n    if (index == 1) return {T(-1), T(1)};\n\
    \n    const std::vector<std::pair<std::uint64_t, int>> factors =\n        prime_factorize(index);\n\
    \    std::uint64_t degree = index;\n    for (const auto& factor : factors) {\n\
    \        degree = degree / factor.first * (factor.first - 1);\n    }\n    assert(degree\
    \ < std::numeric_limits<std::size_t>::max());\n\n    std::vector<T> result(static_cast<std::size_t>(degree)\
    \ + 1, T(0));\n    result[0] = T(1);\n\n    const std::size_t subset_count = std::size_t(1)\
    \ << factors.size();\n    for (std::size_t mask = 0; mask < subset_count; mask++)\
    \ {\n        std::uint64_t exponent = index;\n        bool negative_mobius = false;\n\
    \        for (std::size_t i = 0; i < factors.size(); i++) {\n            if ((mask\
    \ >> i) & 1) {\n                exponent /= factors[i].first;\n              \
    \  negative_mobius = !negative_mobius;\n            }\n        }\n        if (exponent\
    \ > degree) continue;\n\n        const std::size_t shift = static_cast<std::size_t>(exponent);\n\
    \        if (negative_mobius) {\n            // Divide by 1 - x^shift as a truncated\
    \ formal power series.\n            for (std::size_t i = shift; i <= degree; i++)\
    \ {\n                result[i] += result[i - shift];\n            }\n        }\
    \ else {\n            // Multiply by 1 - x^shift.\n            for (std::size_t\
    \ i = static_cast<std::size_t>(degree);\n                 i >= shift;\n      \
    \           i--) {\n                result[i] -= result[i - shift];\n        \
    \        if (i == shift) break;\n            }\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_CYCLOTOMIC_POLYNOMIAL_HPP\n#define M1UNE_MATH_CYCLOTOMIC_POLYNOMIAL_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <cstdint>\n#include <limits>\n\
    #include <vector>\n\n#include \"prime_factorization.hpp\"\n\nnamespace m1une {\n\
    namespace math {\n\ntemplate <class T = long long>\nstd::vector<T> cyclotomic_polynomial(std::uint64_t\
    \ index) {\n    assert(index >= 1);\n    if (index == 1) return {T(-1), T(1)};\n\
    \n    const std::vector<std::pair<std::uint64_t, int>> factors =\n        prime_factorize(index);\n\
    \    std::uint64_t degree = index;\n    for (const auto& factor : factors) {\n\
    \        degree = degree / factor.first * (factor.first - 1);\n    }\n    assert(degree\
    \ < std::numeric_limits<std::size_t>::max());\n\n    std::vector<T> result(static_cast<std::size_t>(degree)\
    \ + 1, T(0));\n    result[0] = T(1);\n\n    const std::size_t subset_count = std::size_t(1)\
    \ << factors.size();\n    for (std::size_t mask = 0; mask < subset_count; mask++)\
    \ {\n        std::uint64_t exponent = index;\n        bool negative_mobius = false;\n\
    \        for (std::size_t i = 0; i < factors.size(); i++) {\n            if ((mask\
    \ >> i) & 1) {\n                exponent /= factors[i].first;\n              \
    \  negative_mobius = !negative_mobius;\n            }\n        }\n        if (exponent\
    \ > degree) continue;\n\n        const std::size_t shift = static_cast<std::size_t>(exponent);\n\
    \        if (negative_mobius) {\n            // Divide by 1 - x^shift as a truncated\
    \ formal power series.\n            for (std::size_t i = shift; i <= degree; i++)\
    \ {\n                result[i] += result[i - shift];\n            }\n        }\
    \ else {\n            // Multiply by 1 - x^shift.\n            for (std::size_t\
    \ i = static_cast<std::size_t>(degree);\n                 i >= shift;\n      \
    \           i--) {\n                result[i] -= result[i - shift];\n        \
    \        if (i == shift) break;\n            }\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_CYCLOTOMIC_POLYNOMIAL_HPP\n"
  dependsOn:
  - math/prime_factorization.hpp
  isVerificationFile: false
  path: math/cyclotomic_polynomial.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-03 15:39:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/cyclotomic_polynomial.test.cpp
documentation_of: math/cyclotomic_polynomial.hpp
layout: document
title: Cyclotomic Polynomial
---

## Overview

The $n$-th cyclotomic polynomial $\Phi_n(x)$ is the monic polynomial whose
roots are the primitive $n$-th roots of unity. It is characterized by

$$
x^n - 1 = \prod_{d \mid n} \Phi_d(x).
$$

This header constructs its coefficients using the Möbius product

$$
\Phi_n(x) = \prod_{d \mid n} (1-x^d)^{\mu(n/d)}
$$

as a truncated formal power series. Only sparse multiplication and exact
division by factors of the form $1-x^d$ are needed.

## Function

```cpp
template <class T = long long>
std::vector<T> cyclotomic_polynomial(std::uint64_t index);
```

`index` must be positive. The result stores coefficients in ascending degree
order: element `i` is the coefficient of $x^i$. Its size is
$\varphi(\mathtt{index})+1$.

`T` must be constructible from `-1`, `0`, and `1`, and support addition and
subtraction. The coefficients are integers, so no multiplicative inverse or
prime modulus is required. With the default `long long`, every coefficient
must fit in that type.

| Function | Description | Complexity |
| --- | --- | --- |
| `cyclotomic_polynomial<T>(index)` | Returns the coefficients of $\Phi_{\mathtt{index}}(x)$. | $O(2^{\omega(n)}\varphi(n))$ time and $O(\varphi(n))$ memory, plus 64-bit factorization |

Here $\omega(n)$ is the number of distinct prime factors. Factorization uses
the library's deterministic Miller--Rabin and Pollard--Rho implementation.

For repunits, the defining identity immediately gives

$$
R_n(x) = \frac{x^n-1}{x-1}
       = \prod_{\substack{d \mid n \\ d>1}} \Phi_d(x).
$$

## Example

```cpp
#include "math/cyclotomic_polynomial.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> polynomial =
        m1une::math::cyclotomic_polynomial(12);
    for (long long coefficient : polynomial) {
        std::cout << coefficient << ' ';
    }
    std::cout << '\n'; // 1 0 -1 0 1
}
```
