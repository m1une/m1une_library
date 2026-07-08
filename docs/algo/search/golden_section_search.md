---
title: Golden Section Search
documentation_of: ../../../algo/search/golden_section_search.hpp
---

## Overview

Golden-section search finds an argument of a unimodal function. Integer
overloads search a half-open range `[left, right)` exactly and return the
smallest optimal argument. Real overloads search a closed interval
approximately and return the midpoint of the final bracket.

The integer implementation uses Fibonacci search, which is the finite-grid
version of golden-section search. After the two active points are initialized,
each contraction reuses one function value and needs only one new evaluation.
Previously queried integer points are reused in the final two-point check, so
the same integer argument is not evaluated twice.

The public namespace is `m1une::algo`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `template <std::integral Int, class F> Int golden_section_search_argmin(Int left, Int right, F f)` | Returns an integer argument minimizing `f` on `[left, right)`. | $O(\log N)$ evaluations |
| `template <std::integral Int, class F> Int golden_section_search_argmax(Int left, Int right, F f)` | Returns an integer argument maximizing `f` on `[left, right)`. | $O(\log N)$ evaluations |
| `template <class F> double golden_section_search_argmin(double left, double right, F f, int iterations = 100)` | Returns an approximate argument minimizing `f` on `[left, right]`. | $O(\text{iterations})$ evaluations |
| `template <class F> double golden_section_search_argmax(double left, double right, F f, int iterations = 100)` | Returns an approximate argument maximizing `f` on `[left, right]`. | $O(\text{iterations})$ evaluations |

For integer overloads, `left < right` is required. For real overloads,
`left <= right` and `iterations >= 0` are required. The function must be
unimodal in the requested direction, and its return values must be comparable
with `<`.

For real overloads, when `iterations` is zero, or when the interval has zero
width, the function object is not evaluated. Otherwise the first contraction
uses two evaluations, and each additional contraction uses one new evaluation.
Thus `iterations > 0` uses `iterations + 1` evaluations.

## Example

```cpp
#include "algo/search/golden_section_search.hpp"

#include <iostream>

int main() {
    auto f = [](long long x) {
        return (x - 7) * (x - 7) + 3;
    };
    long long x = m1une::algo::golden_section_search_argmin<long long>(-100, 101, f);
    std::cout << x << '\n';
}
```
