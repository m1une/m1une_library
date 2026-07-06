---
title: Generalized Floor Sum
documentation_of: ../../math/generalized_floor_sum.hpp
---

## Overview

The generalized floor sum is

$$
F_{p,q}(n,m,a,b)=
\sum_{x=0}^{n-1}
x^p\left\lfloor\frac{ax+b}{m}\right\rfloor^q.
$$

`generalized_floor_sum_table` calculates every $F_{p,q}$ for
$0\le p\le P$ and $0\le q\le Q$. It follows the lattice path below the line
$y=(ax+b)/m$ and composes path fragments with a monoid. Consequently, the
answer type needs addition, subtraction, and multiplication, but no division.
This is useful for polynomially weighted lattice-point counts and sums of
quotient or remainder moments.

## Interface

```cpp
template <class T, int MaxPower, int MaxFloorPower>
using GeneralizedFloorSumTable =
    std::array<std::array<T, MaxFloorPower + 1>, MaxPower + 1>;

template <class T, int MaxPower, int MaxFloorPower, class I>
GeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>
generalized_floor_sum_table(I n, I mod, I a, I b);

template <class T, int Power, int FloorPower, class I>
T generalized_floor_sum(I n, I mod, I a, I b);
```

| Interface | Description | Complexity |
| --- | --- | --- |
| `GeneralizedFloorSumTable<T, P, Q>` | The table type whose entry `[p][q]` stores $F_{p,q}$. | $O((P+1)(Q+1))$ memory |
| `generalized_floor_sum_table<T, P, Q>(n, mod, a, b)` | Returns all moments with $0\le p\le P$ and $0\le q\le Q$. | $O((P+1)(Q+1)(P+Q+1)\log C)$ time and $O((P+1)(Q+1))$ memory |
| `generalized_floor_sum<T, P, Q>(n, mod, a, b)` | Returns only $F_{P,Q}$; internally computes the same table. | $O((P+1)(Q+1)(P+Q+1)\log C)$ time and $O((P+1)(Q+1))$ memory |

Here $C=\max(n,|a|,|b|,m)+2$. `P` and `Q` are compile-time nonnegative
integers.

## Requirements and Behavior

`I` must be a signed integer type of at most 64 bits. The function requires
`n >= 0` and `mod > 0`; `a` and `b` may be negative. Products involving the
integer arguments are promoted to 128 bits.

`T` is the answer type. It must support construction from `0` and `1`, and the
operators `+`, `-`, and `*`. Typical choices are `ModInt`, an unsigned integer
when intentional wraparound is useful, or a sufficiently wide exact integer
type. All arithmetic in the table is performed in `T`, so it must not overflow
unless wraparound is intended.

Powers with exponent zero are treated as one, including $0^0$. Thus entry
`[0][0]` is always `n`. The input arguments are not modified.

## Example

```cpp
#include "math/generalized_floor_sum.hpp"
#include "math/modint.hpp"

#include <iostream>

int main() {
    using Mint = m1une::math::modint998244353;

    // table[p][q] = sum x^p * floor((3*x + 2) / 7)^q, 0 <= x < 10.
    auto table =
        m1une::math::generalized_floor_sum_table<Mint, 2, 2>(
            10,
            7,
            3,
            2
        );
    std::cout << table[1][2] << "\n";

    Mint same = m1une::math::generalized_floor_sum<Mint, 1, 2>(
        10,
        7,
        3,
        2
    );
    std::cout << same << "\n";
}
```
