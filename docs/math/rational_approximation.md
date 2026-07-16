---
title: Rational Approximation
documentation_of: ../../math/rational_approximation.hpp
---

## Overview

`rational_approximation` brackets a positive rational number by the closest
reduced fractions whose numerators and denominators are both bounded.

For positive `maximum`, `numerator`, and `denominator`, it returns:

* the largest reduced $a/b\leq numerator/denominator$ with
  $1\leq a,b\leq maximum$, or `0/1` if none exists;
* the smallest reduced $c/d\geq numerator/denominator$ with
  $1\leq c,d\leq maximum$, or `1/0` if none exists.

The algorithm walks the Stern--Brocot interval with maximal run lengths. It
uses only exact unsigned 128-bit intermediate arithmetic and does not use
floating point.

## Interface

```cpp
template <std::integral T>
struct RationalApproximationResult {
    using fraction_type = std::pair<T, T>;

    fraction_type lower;
    fraction_type upper;
};

template <std::integral T>
RationalApproximationResult<T> rational_approximation(
    T maximum,
    T numerator,
    T denominator
);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `result.lower` | Pair `(numerator, denominator)` for the lower bound. | $O(1)$ access |
| `result.upper` | Pair `(numerator, denominator)` for the upper bound. | $O(1)$ access |
| `rational_approximation(maximum, numerator, denominator)` | Computes both closest bounded fractions. | $O(\log \max(maximum,numerator,denominator))$ time and $O(1)$ memory |

`T` may be a signed or unsigned integral type other than `bool`, with at most 64
bits. All three arguments must be positive. Returned ordinary fractions are
reduced; `0/1` and `1/0` are boundary sentinels and are not members of the
positive bounded set.

## Example

```cpp
#include "math/rational_approximation.hpp"

#include <cassert>
#include <utility>

int main() {
    auto result = m1une::math::rational_approximation(5LL, 7LL, 10LL);

    assert(result.lower == std::pair<long long, long long>(2, 3));
    assert(result.upper == std::pair<long long, long long>(3, 4));
}
```
