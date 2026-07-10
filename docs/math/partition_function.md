---
title: Partition Function
documentation_of: ../../math/partition_function.hpp
---

## Overview

The partition function $p(n)$ counts the ways to write the nonnegative integer
$n$ as a sum of positive integers when order does not matter. By convention,
$p(0)=1$.

For example, $p(5)=7$:

```text
5
4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1
```

Its generating function is

$$
\sum_{n=0}^{\infty}p(n)x^n
=
\prod_{k=1}^{\infty}\frac{1}{1-x^k}.
$$

Euler's pentagonal number theorem makes the denominator sparse. The
implementation constructs that denominator through degree `maximum`, then
inverts it as a formal power series.

## Requirements

`Mint` must satisfy the requirements of `FormalPowerSeries`, including modular
addition, multiplication, and inversion. The usual choice is
`m1une::math::modint998244353`.

## Interface

| Function | Complexity | Description |
| --- | --- | --- |
| `std::vector<Mint> partition_function<Mint>(int maximum)` | $O(N\log N)$ time and $O(N)$ memory | Returns `p(0)` through `p(maximum)`. |
| `std::vector<Mint> partition_numbers<Mint>(int maximum)` | $O(N\log N)$ time and $O(N)$ memory | Compatibility alias of `partition_function`. |

`maximum` must be nonnegative. The returned vector has size `maximum + 1`.

## Example

```cpp
#include "math/modint.hpp"
#include "math/partition_function.hpp"

#include <iostream>

int main() {
    using Mint = m1une::math::modint998244353;
    std::vector<Mint> values =
        m1une::math::partition_function<Mint>(10);

    std::cout << values[5] << "\n"; // 7
}
```
