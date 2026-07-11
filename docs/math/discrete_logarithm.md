---
title: Discrete Logarithm
documentation_of: ../../math/discrete_logarithm.hpp
---

## Overview

`discrete_logarithm(base, target, mod)` finds the smallest nonnegative integer
`exponent` satisfying

$$
\text{base}^{\text{exponent}} \equiv \text{target} \pmod {\text{mod}}.
$$

The modulus may be prime or composite, and the base does not need to be
invertible. Common factors are removed first, followed by a baby-step--giant-step
search in the remaining multiplicative group.

## API

```cpp
std::optional<uint64_t> discrete_logarithm(
    uint64_t base,
    uint64_t target,
    uint64_t mod
);
```

| Function | Description | Expected complexity |
| --- | --- | --- |
| `discrete_logarithm(base, target, mod)` | Returns the smallest nonnegative solution, or `std::nullopt` when none exists. | $O(\sqrt m)$ time and memory |

The common-factor reduction takes $O(\log m)$ iterations. The hash-table search
uses $O(\sqrt m)$ modular multiplications and stored residues. Multiplication
uses an unsigned 128-bit intermediate.

`mod` must be positive. Both residues are reduced modulo `mod`. Exponent zero is
checked first, and `0^0` is defined as `1`; therefore a target congruent to `1`
always returns `0`. For `mod == 1`, the result is also `0`.

The function accepts 64-bit inputs, but its square-root memory requirement makes
very large moduli impractical in the usual way for baby-step--giant-step.

## Example

```cpp
#include "math/discrete_logarithm.hpp"

#include <iostream>

int main() {
    auto first = m1une::math::discrete_logarithm(2, 8, 13);
    std::cout << *first << "\n";  // 3

    auto second = m1une::math::discrete_logarithm(4, 3, 14);
    std::cout << second.has_value() << "\n";  // 0

    auto zero = m1une::math::discrete_logarithm(0, 0, 17);
    std::cout << *zero << "\n";  // 1
}
```
