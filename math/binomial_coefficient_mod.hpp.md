---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/number_theory.hpp
    title: Number Theory
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/binomial_coefficient_mod.test.cpp
    title: verify/math/binomial_coefficient_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/binomial_coefficient_mod.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <cstdint>\n#include <vector>\n\n#line 1 \"math/number_theory.hpp\"\
    \n\n\n\n#line 6 \"math/number_theory.hpp\"\n#include <limits>\n#include <tuple>\n\
    #include <utility>\n#line 10 \"math/number_theory.hpp\"\n\nnamespace m1une {\n\
    namespace math {\n\nnamespace internal {\n\ninline long long safe_mod(long long\
    \ x, long long mod) {\n    x %= mod;\n    if (x < 0) x += mod;\n    return x;\n\
    }\n\ninline unsigned __int128 floor_sum_unsigned(unsigned long long n, unsigned\
    \ long long mod, unsigned long long a,\n                                     \
    \       unsigned long long b) {\n    unsigned __int128 answer = 0;\n    while\
    \ (true) {\n        if (a >= mod) {\n            answer += static_cast<unsigned\
    \ __int128>(n) * (n - 1) / 2 * (a / mod);\n            a %= mod;\n        }\n\
    \        if (b >= mod) {\n            answer += static_cast<unsigned __int128>(n)\
    \ * (b / mod);\n            b %= mod;\n        }\n\n        const unsigned __int128\
    \ y_max = static_cast<unsigned __int128>(a) * n + b;\n        if (y_max < mod)\
    \ break;\n        n = static_cast<unsigned long long>(y_max / mod);\n        b\
    \ = static_cast<unsigned long long>(y_max % mod);\n        unsigned long long\
    \ tmp = mod;\n        mod = a;\n        a = tmp;\n    }\n    return answer;\n\
    }\n\n}  // namespace internal\n\n// Returns (g, x, y), where g = gcd(a, b) is\
    \ nonnegative and\n// a * x + b * y = g. Returns (0, 0, 0) when a = b = 0.\ninline\
    \ std::tuple<long long, long long, long long> extended_gcd(long long a,\n    \
    \                                                           long long b) {\n \
    \   using i128 = __int128;\n    if (a == 0 && b == 0) return {0, 0, 0};\n\n  \
    \  i128 old_remainder = a;\n    i128 remainder = b;\n    if (old_remainder < 0)\
    \ old_remainder = -old_remainder;\n    if (remainder < 0) remainder = -remainder;\n\
    \    i128 old_x = 1;\n    i128 x = 0;\n    i128 old_y = 0;\n    i128 y = 1;\n\n\
    \    while (remainder != 0) {\n        i128 quotient = old_remainder / remainder;\n\
    \n        i128 next = old_remainder - quotient * remainder;\n        old_remainder\
    \ = remainder;\n        remainder = next;\n\n        next = old_x - quotient *\
    \ x;\n        old_x = x;\n        x = next;\n\n        next = old_y - quotient\
    \ * y;\n        old_y = y;\n        y = next;\n    }\n\n    if (a < 0) old_x =\
    \ -old_x;\n    if (b < 0) old_y = -old_y;\n\n#ifndef NDEBUG\n    const i128 minimum\
    \ = std::numeric_limits<long long>::min();\n    const i128 maximum = std::numeric_limits<long\
    \ long>::max();\n    assert(old_remainder <= maximum);\n    assert(minimum <=\
    \ old_x && old_x <= maximum);\n    assert(minimum <= old_y && old_y <= maximum);\n\
    #endif\n    return {static_cast<long long>(old_remainder), static_cast<long long>(old_x),\n\
    \            static_cast<long long>(old_y)};\n}\n\ninline long long pow_mod(long\
    \ long x, unsigned long long exponent, long long mod) {\n    assert(mod >= 1);\n\
    \    if (mod == 1) return 0;\n\n    unsigned long long base = static_cast<unsigned\
    \ long long>(internal::safe_mod(x, mod));\n    unsigned long long result = 1;\n\
    \    const unsigned long long unsigned_mod = static_cast<unsigned long long>(mod);\n\
    \    while (exponent > 0) {\n        if (exponent & 1) {\n            result =\
    \ static_cast<unsigned long long>(static_cast<unsigned __int128>(result) * base\
    \ % unsigned_mod);\n        }\n        base = static_cast<unsigned long long>(static_cast<unsigned\
    \ __int128>(base) * base % unsigned_mod);\n        exponent >>= 1;\n    }\n  \
    \  return static_cast<long long>(result);\n}\n\n// Returns gcd(a, mod) and x such\
    \ that a * x is congruent to gcd(a, mod)\n// modulo mod. The returned x is in\
    \ [0, mod / gcd(a, mod)).\ninline std::pair<long long, long long> inv_gcd(long\
    \ long a, long long mod) {\n    assert(mod >= 1);\n    a = internal::safe_mod(a,\
    \ mod);\n    if (a == 0) return {mod, 0};\n\n    long long s = mod;\n    long\
    \ long t = a;\n    long long m0 = 0;\n    long long m1 = 1;\n    while (t > 0)\
    \ {\n        const long long quotient = s / t;\n        s -= t * quotient;\n \
    \       m0 -= m1 * quotient;\n\n        long long tmp = s;\n        s = t;\n \
    \       t = tmp;\n        tmp = m0;\n        m0 = m1;\n        m1 = tmp;\n   \
    \ }\n    if (m0 < 0) m0 += mod / s;\n    return {s, m0};\n}\n\ninline long long\
    \ inv_mod(long long x, long long mod) {\n    const auto result = inv_gcd(x, mod);\n\
    \    assert(result.first == 1);\n    return result.second;\n}\n\n// Returns the\
    \ smallest nonnegative solution and the least common multiple of\n// the moduli.\
    \ Returns {0, 0} when the system is inconsistent.\ninline std::pair<long long,\
    \ long long> crt(const std::vector<long long>& remainders,\n                 \
    \                          const std::vector<long long>& moduli) {\n    assert(remainders.size()\
    \ == moduli.size());\n\n    long long r0 = 0;\n    long long m0 = 1;\n    for\
    \ (int i = 0; i < int(remainders.size()); i++) {\n        assert(moduli[i] >=\
    \ 1);\n        long long r1 = internal::safe_mod(remainders[i], moduli[i]);\n\
    \        long long m1 = moduli[i];\n\n        if (m0 < m1) {\n            long\
    \ long tmp = r0;\n            r0 = r1;\n            r1 = tmp;\n            tmp\
    \ = m0;\n            m0 = m1;\n            m1 = tmp;\n        }\n        if (m0\
    \ % m1 == 0) {\n            if (r0 % m1 != r1) return {0, 0};\n            continue;\n\
    \        }\n\n        const auto inverse = inv_gcd(m0, m1);\n        const long\
    \ long gcd = inverse.first;\n        const long long reduced_modulus = m1 / gcd;\n\
    \        const __int128 difference = static_cast<__int128>(r1) - r0;\n       \
    \ if (difference % gcd != 0) return {0, 0};\n\n        __int128 multiplier = difference\
    \ / gcd % reduced_modulus;\n        multiplier = multiplier * inverse.second %\
    \ reduced_modulus;\n        if (multiplier < 0) multiplier += reduced_modulus;\n\
    \n        const __int128 new_modulus = static_cast<__int128>(m0) * reduced_modulus;\n\
    \        assert(new_modulus <= std::numeric_limits<long long>::max());\n     \
    \   __int128 new_remainder = static_cast<__int128>(r0) + multiplier * m0;\n  \
    \      new_remainder %= new_modulus;\n        if (new_remainder < 0) new_remainder\
    \ += new_modulus;\n        r0 = static_cast<long long>(new_remainder);\n     \
    \   m0 = static_cast<long long>(new_modulus);\n    }\n    return {r0, m0};\n}\n\
    \n// Returns sum_{i=0}^{n-1} floor((a * i + b) / mod).\ninline long long floor_sum(long\
    \ long n, long long mod, long long a, long long b) {\n    assert(n >= 0);\n  \
    \  assert(mod >= 1);\n\n    const long long normalized_a = internal::safe_mod(a,\
    \ mod);\n    const long long normalized_b = internal::safe_mod(b, mod);\n    __int128\
    \ answer = (static_cast<__int128>(a) - normalized_a) / mod * n * (n - 1) / 2;\n\
    \    answer += (static_cast<__int128>(b) - normalized_b) / mod * n;\n    answer\
    \ += internal::floor_sum_unsigned(static_cast<unsigned long long>(n), static_cast<unsigned\
    \ long long>(mod),\n                                           static_cast<unsigned\
    \ long long>(normalized_a),\n                                           static_cast<unsigned\
    \ long long>(normalized_b));\n\n    assert(answer >= std::numeric_limits<long\
    \ long>::min());\n    assert(answer <= std::numeric_limits<long long>::max());\n\
    \    return static_cast<long long>(answer);\n}\n\n}  // namespace math\n}  //\
    \ namespace m1une\n\n\n#line 10 \"math/binomial_coefficient_mod.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\n// Binomial coefficients modulo a fixed, not necessarily\
    \ prime, modulus.\nclass BinomialCoefficientMod {\n   private:\n    struct PrimePower\
    \ {\n        uint32_t prime;\n        int exponent;\n        uint32_t modulus;\n\
    \        uint32_t crt_multiplier;\n        std::vector<uint32_t> unit_factorial_prefix;\n\
    \n        uint32_t multiply(uint32_t lhs, uint32_t rhs) const {\n            return\
    \ uint32_t(uint64_t(lhs) * rhs % modulus);\n        }\n\n        uint32_t power(uint32_t\
    \ base, uint64_t exponent_) const {\n            uint32_t result = 1 % modulus;\n\
    \            while (exponent_ > 0) {\n                if (exponent_ & 1) result\
    \ = multiply(result, base);\n                base = multiply(base, base);\n  \
    \              exponent_ >>= 1;\n            }\n            return result;\n \
    \       }\n\n        uint64_t factorial_valuation(uint64_t n) const {\n      \
    \      uint64_t result = 0;\n            while (n > 0) {\n                n /=\
    \ prime;\n                result += n;\n            }\n            return result;\n\
    \        }\n\n        uint32_t unit_factorial(uint64_t n) const {\n          \
    \  if (n == 0) return 1 % modulus;\n            const uint32_t block_product =\
    \ unit_factorial_prefix.back();\n            uint32_t result = power(block_product,\
    \ n / modulus);\n            result = multiply(result, unit_factorial_prefix[std::size_t(n\
    \ % modulus)]);\n            return multiply(result, unit_factorial(n / prime));\n\
    \        }\n\n        uint32_t binom(uint64_t n, uint64_t k) const {\n       \
    \     if (k > n) return 0;\n            const uint64_t valuation = factorial_valuation(n)\
    \ - factorial_valuation(k) -\n                                       factorial_valuation(n\
    \ - k);\n            if (valuation >= uint64_t(exponent)) return 0;\n\n      \
    \      const uint32_t numerator = unit_factorial(n);\n            const uint32_t\
    \ denominator =\n                multiply(unit_factorial(k), unit_factorial(n\
    \ - k));\n            const uint32_t inverse_denominator =\n                uint32_t(inv_mod(denominator,\
    \ modulus));\n            uint32_t result = multiply(numerator, inverse_denominator);\n\
    \            result = multiply(result, power(prime, valuation));\n           \
    \ return result;\n        }\n    };\n\n    uint32_t _modulus;\n    std::vector<PrimePower>\
    \ _prime_powers;\n\n   public:\n    explicit BinomialCoefficientMod(uint32_t modulus)\
    \ : _modulus(modulus) {\n        assert(modulus >= 1);\n        uint32_t remaining\
    \ = modulus;\n        for (uint32_t prime = 2; uint64_t(prime) * prime <= remaining;\
    \ prime++) {\n            if (remaining % prime != 0) continue;\n            int\
    \ exponent = 0;\n            uint32_t prime_power = 1;\n            do {\n   \
    \             remaining /= prime;\n                prime_power *= prime;\n   \
    \             exponent++;\n            } while (remaining % prime == 0);\n   \
    \         _prime_powers.push_back(\n                PrimePower{prime, exponent,\
    \ prime_power, 0, {}});\n        }\n        if (remaining > 1) {\n           \
    \ _prime_powers.push_back(PrimePower{remaining, 1, remaining, 0, {}});\n     \
    \   }\n\n        for (PrimePower& component : _prime_powers) {\n            component.unit_factorial_prefix.resize(std::size_t(component.modulus));\n\
    \            component.unit_factorial_prefix[0] = 1;\n            for (uint32_t\
    \ value = 1; value < component.modulus; value++) {\n                component.unit_factorial_prefix[value]\
    \ =\n                    component.unit_factorial_prefix[value - 1];\n       \
    \         if (value % component.prime != 0) {\n                    component.unit_factorial_prefix[value]\
    \ = component.multiply(\n                        component.unit_factorial_prefix[value],\
    \ value);\n                }\n            }\n\n            const uint32_t other\
    \ = modulus / component.modulus;\n            const uint32_t inverse =\n     \
    \           uint32_t(inv_mod(other, component.modulus));\n            component.crt_multiplier\
    \ =\n                uint32_t(uint64_t(other) * inverse % modulus);\n        }\n\
    \    }\n\n    uint32_t modulus() const {\n        return _modulus;\n    }\n\n\
    \    uint32_t binom(uint64_t n, uint64_t k) const {\n        if (k > n || _modulus\
    \ == 1) return 0;\n        uint64_t result = 0;\n        for (const PrimePower&\
    \ component : _prime_powers) {\n            const uint32_t residue = component.binom(n,\
    \ k);\n            result += uint64_t(residue) * component.crt_multiplier % _modulus;\n\
    \            result %= _modulus;\n        }\n        return uint32_t(result);\n\
    \    }\n\n    uint32_t operator()(uint64_t n, uint64_t k) const {\n        return\
    \ binom(n, k);\n    }\n};\n\nusing ArbitraryModBinomialCoefficient = BinomialCoefficientMod;\n\
    \n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_BINOMIAL_COEFFICIENT_MOD_HPP\n#define M1UNE_MATH_BINOMIAL_COEFFICIENT_MOD_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <cstdint>\n#include <vector>\n\
    \n#include \"number_theory.hpp\"\n\nnamespace m1une {\nnamespace math {\n\n//\
    \ Binomial coefficients modulo a fixed, not necessarily prime, modulus.\nclass\
    \ BinomialCoefficientMod {\n   private:\n    struct PrimePower {\n        uint32_t\
    \ prime;\n        int exponent;\n        uint32_t modulus;\n        uint32_t crt_multiplier;\n\
    \        std::vector<uint32_t> unit_factorial_prefix;\n\n        uint32_t multiply(uint32_t\
    \ lhs, uint32_t rhs) const {\n            return uint32_t(uint64_t(lhs) * rhs\
    \ % modulus);\n        }\n\n        uint32_t power(uint32_t base, uint64_t exponent_)\
    \ const {\n            uint32_t result = 1 % modulus;\n            while (exponent_\
    \ > 0) {\n                if (exponent_ & 1) result = multiply(result, base);\n\
    \                base = multiply(base, base);\n                exponent_ >>= 1;\n\
    \            }\n            return result;\n        }\n\n        uint64_t factorial_valuation(uint64_t\
    \ n) const {\n            uint64_t result = 0;\n            while (n > 0) {\n\
    \                n /= prime;\n                result += n;\n            }\n  \
    \          return result;\n        }\n\n        uint32_t unit_factorial(uint64_t\
    \ n) const {\n            if (n == 0) return 1 % modulus;\n            const uint32_t\
    \ block_product = unit_factorial_prefix.back();\n            uint32_t result =\
    \ power(block_product, n / modulus);\n            result = multiply(result, unit_factorial_prefix[std::size_t(n\
    \ % modulus)]);\n            return multiply(result, unit_factorial(n / prime));\n\
    \        }\n\n        uint32_t binom(uint64_t n, uint64_t k) const {\n       \
    \     if (k > n) return 0;\n            const uint64_t valuation = factorial_valuation(n)\
    \ - factorial_valuation(k) -\n                                       factorial_valuation(n\
    \ - k);\n            if (valuation >= uint64_t(exponent)) return 0;\n\n      \
    \      const uint32_t numerator = unit_factorial(n);\n            const uint32_t\
    \ denominator =\n                multiply(unit_factorial(k), unit_factorial(n\
    \ - k));\n            const uint32_t inverse_denominator =\n                uint32_t(inv_mod(denominator,\
    \ modulus));\n            uint32_t result = multiply(numerator, inverse_denominator);\n\
    \            result = multiply(result, power(prime, valuation));\n           \
    \ return result;\n        }\n    };\n\n    uint32_t _modulus;\n    std::vector<PrimePower>\
    \ _prime_powers;\n\n   public:\n    explicit BinomialCoefficientMod(uint32_t modulus)\
    \ : _modulus(modulus) {\n        assert(modulus >= 1);\n        uint32_t remaining\
    \ = modulus;\n        for (uint32_t prime = 2; uint64_t(prime) * prime <= remaining;\
    \ prime++) {\n            if (remaining % prime != 0) continue;\n            int\
    \ exponent = 0;\n            uint32_t prime_power = 1;\n            do {\n   \
    \             remaining /= prime;\n                prime_power *= prime;\n   \
    \             exponent++;\n            } while (remaining % prime == 0);\n   \
    \         _prime_powers.push_back(\n                PrimePower{prime, exponent,\
    \ prime_power, 0, {}});\n        }\n        if (remaining > 1) {\n           \
    \ _prime_powers.push_back(PrimePower{remaining, 1, remaining, 0, {}});\n     \
    \   }\n\n        for (PrimePower& component : _prime_powers) {\n            component.unit_factorial_prefix.resize(std::size_t(component.modulus));\n\
    \            component.unit_factorial_prefix[0] = 1;\n            for (uint32_t\
    \ value = 1; value < component.modulus; value++) {\n                component.unit_factorial_prefix[value]\
    \ =\n                    component.unit_factorial_prefix[value - 1];\n       \
    \         if (value % component.prime != 0) {\n                    component.unit_factorial_prefix[value]\
    \ = component.multiply(\n                        component.unit_factorial_prefix[value],\
    \ value);\n                }\n            }\n\n            const uint32_t other\
    \ = modulus / component.modulus;\n            const uint32_t inverse =\n     \
    \           uint32_t(inv_mod(other, component.modulus));\n            component.crt_multiplier\
    \ =\n                uint32_t(uint64_t(other) * inverse % modulus);\n        }\n\
    \    }\n\n    uint32_t modulus() const {\n        return _modulus;\n    }\n\n\
    \    uint32_t binom(uint64_t n, uint64_t k) const {\n        if (k > n || _modulus\
    \ == 1) return 0;\n        uint64_t result = 0;\n        for (const PrimePower&\
    \ component : _prime_powers) {\n            const uint32_t residue = component.binom(n,\
    \ k);\n            result += uint64_t(residue) * component.crt_multiplier % _modulus;\n\
    \            result %= _modulus;\n        }\n        return uint32_t(result);\n\
    \    }\n\n    uint32_t operator()(uint64_t n, uint64_t k) const {\n        return\
    \ binom(n, k);\n    }\n};\n\nusing ArbitraryModBinomialCoefficient = BinomialCoefficientMod;\n\
    \n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_BINOMIAL_COEFFICIENT_MOD_HPP\n"
  dependsOn:
  - math/number_theory.hpp
  isVerificationFile: false
  path: math/binomial_coefficient_mod.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-13 05:49:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/binomial_coefficient_mod.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/binomial_coefficient_mod.hpp
layout: document
title: Binomial Coefficient Modulo an Arbitrary Modulus
---

## Overview

`BinomialCoefficientMod` computes binomial coefficients modulo one fixed
positive integer. The modulus may be prime, a prime power, composite, or `1`,
and `n` may be as large as an unsigned 64-bit integer.

The constructor factors the modulus into pairwise coprime prime powers. For
each prime power, it precomputes factorial products with factors of that prime
removed. A query evaluates the factorials recursively, restores the correct
prime exponent, and combines all prime-power residues with the Chinese
remainder theorem.

This structure is intended for many queries using the same moderate modulus.
Its preprocessing is linear in the sum of the prime-power factors, so it is a
good fit for moduli up to roughly a few million. It should not be constructed
with a modulus near `10^9` unless that memory and preprocessing cost are
acceptable.

`ArbitraryModBinomialCoefficient` is an alias for
`BinomialCoefficientMod`.

## Interface

```cpp
class BinomialCoefficientMod {
public:
    explicit BinomialCoefficientMod(uint32_t modulus);

    uint32_t modulus() const;
    uint32_t binom(uint64_t n, uint64_t k) const;
    uint32_t operator()(uint64_t n, uint64_t k) const;
};

using ArbitraryModBinomialCoefficient = BinomialCoefficientMod;
```

Let

$$
m = \prod_{i=1}^s p_i^{e_i}
$$

be the prime-power factorization of the modulus, and write
$q_i = p_i^{e_i}$. The complexities are:

| Method | Description | Complexity |
| --- | --- | --- |
| `BinomialCoefficientMod(modulus)` | Factors the modulus and prepares the unit-factorial tables. | $O(\sqrt m + \sum_i q_i)$ time and $O(\sum_i q_i)$ memory |
| `modulus()` | Returns the fixed modulus. | $O(1)$ |
| `binom(n, k)` | Returns $\binom{n}{k} \bmod m$; invalid `k` returns zero. | $O(\sum_i \log_{p_i}(n+1))$ |
| `operator()(n, k)` | Alias for `binom(n, k)`. | $O(\sum_i \log_{p_i}(n+1))$ |

## Behavioral Notes

* `modulus` must be positive.
* When `modulus == 1`, every query returns `0`.
* When `k > n`, the answer is `0`.
* Construction performs all allocation and preprocessing. Queries are `const`
  and allocate no dynamic memory.
* The implementation does not assume that the modulus is prime and never
  divides by a value that is not invertible modulo a prime power.
* Use `Combinatorics<Mint>` instead when the modulus is a large prime, all
  arguments are smaller than it, and factorial preprocessing through the
  maximum `n` is affordable.
* Use `Lucas<Mint>` for huge arguments modulo a small prime. This structure
  generalizes that use case to prime powers and composite moduli.

## Example

```cpp
#include "math/binomial_coefficient_mod.hpp"

#include <iostream>

int main() {
    m1une::math::BinomialCoefficientMod combinations(12);

    std::cout << combinations.binom(5, 2) << '\n';  // 10
    std::cout << combinations(10, 3) << '\n';       // 0
    std::cout << combinations(1000000000000000000ULL, 1) << '\n';  // 4
}
```

The object can be reused for any number of queries as long as the modulus
remains `12`.
