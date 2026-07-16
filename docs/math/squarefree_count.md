---
title: Squarefree Count
documentation_of: ../../math/squarefree_count.hpp
---

## Overview

`count_squarefree(n)` returns the number of square-free positive integers not
greater than `n`. An integer is square-free when it is not divisible by the
square of any prime.

The starting identity is

$$
Q(n)=\sum_{d\leq\sqrt n}\mu(d)
     \left\lfloor\frac{n}{d^2}\right\rfloor.
$$

Evaluating every term would require $O(\sqrt n)$ time. The implementation
chooses a fifth-root split, sieves the Möbius function through
$O(n^{2/5})$, and obtains the remaining grouped terms from selected values of
the Mertens prefix sum.

## Interface

```cpp
uint64_t count_squarefree(uint64_t n);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `count_squarefree(n)` | Counts square-free integers in `[1, n]`. Returns `0` for `n == 0`. | $O(n^{2/5})$ time and memory |

All roots are computed with exact integer arithmetic. The implementation
supports the full `uint64_t` input range for which its internal sieve limit fits
in `int`; in particular, it directly supports the Library Checker bound
$n\leq10^{18}$. The returned count never exceeds `n`.

## Example

```cpp
#include "math/squarefree_count.hpp"

#include <cassert>

int main() {
    assert(m1une::math::count_squarefree(10) == 7);
    assert(m1une::math::count_squarefree(100) == 61);
}
```
