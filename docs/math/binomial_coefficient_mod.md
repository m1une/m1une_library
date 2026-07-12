---
title: Binomial Coefficient Modulo an Arbitrary Modulus
documentation_of: ../../math/binomial_coefficient_mod.hpp
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
