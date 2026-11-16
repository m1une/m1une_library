---
title: Monoid Power
documentation_of: ../../monoid/power.hpp
---

## Overview

A utility function that computes the $n$-th power of an element $a$ in a generic Monoid using binary exponentiation. It uses $O(\log(n + 1))$ monoid operations.
Use it for fast matrix exponentiation, string repetition, or finding the $n$-th composition of a function.

## Template Parameters

* `M`: A struct representing the mathematical monoid, satisfying the `m1une::monoid::IsMonoid` concept.

## Parameters

* `typename M::value_type a`: The base element.
* `long long n`: The exponent (number of times to apply the operation).

## Interface and Complexity

| Function | Description | Complexity |
| --- | --- | --- |
| `template <IsMonoid M> constexpr typename M::value_type power(typename M::value_type a, long long n)` | Combines `n` copies of `a`; returns `M::id()` for `n == 0`. Requires `n >= 0`. | $O(\log(n + 1))$ calls to `M::op`, plus value copies. |

The function does not modify the supplied value. For a matrix monoid with
dimension `D`, the time is $O(D^3 \log(n + 1))$.

## Example

```cpp
#include "monoid/power.hpp"
#include "monoid/matrix.hpp"
#include <iostream>

using Mat = m1une::monoid::Matrix<long long, 2>;

int main() {
    Mat::value_type transition{};
    transition[0] = {1, 1};
    transition[1] = {1, 0};

    // Compute the 10th power of the Fibonacci transition matrix
    auto res = m1une::monoid::power<Mat>(transition, 10);

    std::cout << res[0][0] << "\n";
    return 0;
}
```
