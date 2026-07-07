---
title: Ternary Search
documentation_of: ../../../algo/search/ternary_search.hpp
---

## Overview

Ternary-search helpers find an argument of a unimodal function. Integer
functions search a half-open range `[left, right)` and return the smallest
optimal argument. Real functions search a closed interval approximately and
return the midpoint of the final interval.

The public namespace is `m1une::algo`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `ternary_search_argmin(left, right, f)` | Returns an integer argument minimizing `f` on `[left, right)`. | $O(\log N)$ evaluations |
| `ternary_search_argmax(left, right, f)` | Returns an integer argument maximizing `f` on `[left, right)`. | $O(\log N)$ evaluations |
| `real_ternary_search_argmin(left, right, f, iterations = 100)` | Returns an approximate real minimizer. | $O(\text{iterations})$ evaluations |
| `real_ternary_search_argmax(left, right, f, iterations = 100)` | Returns an approximate real maximizer. | $O(\text{iterations})$ evaluations |

The integer range must be nonempty. The function must be unimodal in the
requested direction.

## Example

```cpp
#include "algo/search/ternary_search.hpp"

#include <iostream>

int main() {
    auto f = [](long long x) {
        return (x - 7) * (x - 7) + 3;
    };
    long long x = m1une::algo::ternary_search_argmin<long long>(-100, 101, f);
    std::cout << x << '\n';
}
```
