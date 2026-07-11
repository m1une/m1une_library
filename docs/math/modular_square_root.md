---
title: Modular Square Root
documentation_of: ../../math/modular_square_root.hpp
---

## Overview

`modular_square_root` solves

$$
x^2 \equiv a \pmod p
$$

for a prime modulus `p`. It uses the Tonelli-Shanks algorithm and returns no
value when `a` is a quadratic non-residue.

The runtime-modulus overload is useful when each query has a different prime.
The one-argument overload works with modular integer types that provide
`val()`, static `mod()`, and construction from an integer, including
`m1une::math::ModInt`.

## API

```cpp
std::optional<uint64_t> modular_square_root(
    uint64_t value,
    uint64_t prime
);

template <class Mint>
std::optional<Mint> modular_square_root(Mint value);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `modular_square_root(value, prime)` | Returns a square root modulo the prime, or `std::nullopt` if none exists. | $O(\log^2 p)$ modular multiplications |
| `modular_square_root(value)` | Uses `Mint::mod()` and returns the result as `Mint`. | $O(\log^2 p)$ modular multiplications |

`prime` must be at least `2` and prime. The function does not perform a
primality test. `value` is reduced modulo `prime`, and either square root may be
returned. In particular, the result is not guaranteed to be the smaller root.

Multiplication uses an unsigned 128-bit intermediate, so the runtime overload
supports the full `uint64_t` range of prime moduli.

## Example

```cpp
#include "math/modint.hpp"
#include "math/modular_square_root.hpp"

#include <iostream>

int main() {
    auto root = m1une::math::modular_square_root(10, 13);
    if (root.has_value()) {
        std::cout << *root << "\n";  // 6 or 7
    }

    using Mint = m1une::math::modint998244353;
    auto mint_root = m1une::math::modular_square_root(Mint(4));
    std::cout << mint_root->val() << "\n";  // 2 or 998244351
}
```
