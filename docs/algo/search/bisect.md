---
title: Bisect
documentation_of: ../../../algo/search/bisect.hpp
---

## Overview

Binary search helpers for monotone predicates. The integer functions use explicit `ok` and `ng` sentinels, so they work for both increasing and decreasing search directions.

## Requirements and Behavior

The predicate must change truth value at most once between the two endpoints.
`ok` is a known true boundary and `ng` is a known false boundary; either may
be an artificial sentinel outside the domain. The functions evaluate only
interior points, never the supplied endpoints.

With `ng < ok`, `first_true` finds the smallest true integer. With `ok < ng`,
`last_true` finds the largest true integer. Reversing either direction still
works: the result is always the true point nearest the false region.
Adjacent integer sentinels return `ok` without a predicate call.

Let $D$ be the initial distance between the sentinels. Complexities below count
predicate calls; multiply by the predicate's evaluation cost. The real-valued
helper performs `iterations` midpoint refinements and returns the true-side
endpoint of the final bracket, rather than guaranteeing a fixed absolute error.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `long long first_true(long long ng, long long ok, F pred)` | Given `pred(ng) == false` and `pred(ok) == true`, returns the boundary `ok`. | $O(\log(D + 1))$ |
| `long long last_true(long long ok, long long ng, F pred)` | Given `pred(ok) == true` and `pred(ng) == false`, returns the boundary `ok`. | $O(\log(D + 1))$ |
| `double real_first_true(double ng, double ok, F pred, int iterations = 80)` | Floating-point version of `first_true` with a fixed iteration count. | $O(\text{iterations})$ |

## Example

```cpp
#include "algo/search/bisect.hpp"
#include <iostream>

int main() {
    long long n = 100;
    long long x = m1une::algo::first_true(0, n + 1, [&](long long v) {
        return v * v >= n;
    });
    std::cout << x << "\n";
}
```
