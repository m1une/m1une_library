---
title: Modular Kth Root
documentation_of: ../../math/modular_kth_root.hpp
---

## Overview

`modular_kth_root` solves

$$
x^k \equiv a \pmod p
$$

for a prime modulus $p$. It returns any valid root, or `std::nullopt` when no
root exists. The implementation reduces the exponent by
$\gcd(k,p-1)$ and extracts its prime-power factors with a generalized
Tonelli--Shanks algorithm.

## Interface

```cpp
std::optional<uint64_t> modular_kth_root(
    uint64_t value,
    uint64_t degree,
    uint64_t prime
);

template <class Mint>
std::optional<Mint> modular_kth_root(
    Mint value,
    uint64_t degree
);
```

| Function | Description |
| --- | --- |
| `modular_kth_root(value, degree, prime)` | Reduces `value` modulo `prime` and returns any kth root. |
| `modular_kth_root(value, degree)` | Uses `Mint::mod()` and returns the root as `Mint`. |

`prime` must be at least `2` and prime; primality is not tested. The modular
integer overload requires `val()`, static `mod()`, and construction from an
integer.

For `degree == 0`, exponentiation follows the convention $x^0=1$, including
$0^0=1$. The function therefore returns `0` when `value` is congruent to `1`
and no result otherwise. For positive degree, zero has root zero.

The answer is not canonical when several roots exist.

## Complexity

Let $g=\gcd(k,p-1)$. Factoring $g$ by trial division takes $O(\sqrt g)$
integer operations. For a prime factor $q^e$ of $g$, write
$p-1=mq^s$. Its generalized Tonelli--Shanks correction uses
$O(\sqrt{(s-e)q})$ stored group elements and $s-e$ correction rounds, plus a
search for a q-th non-residue. Every modular exponentiation costs $O(\log p)$
modular multiplications.

This is designed for the common competitive-programming regime of many prime
moduli up to about $10^9$ and avoids a full discrete logarithm per query.

## Example

```cpp
#include "math/modular_kth_root.hpp"

#include <cassert>

int main() {
    auto root = m1une::math::modular_kth_root(8, 3, 13);
    assert(root.has_value());
    assert(*root * *root % 13 * *root % 13 == 8);

    assert(!m1une::math::modular_kth_root(3, 2, 7).has_value());
}
```
