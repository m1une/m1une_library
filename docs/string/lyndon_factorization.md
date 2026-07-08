---
title: Lyndon Factorization
documentation_of: ../../string/lyndon_factorization.hpp
---

## Overview

The Lyndon factorization decomposes a sequence into a lexicographically
non-increasing sequence of Lyndon words. It is useful in string ordering,
minimal rotations, runs, and suffix-related algorithms.

The implementation uses Duval's algorithm. The minimum cyclic shift helper uses
the same idea and returns the earliest starting position among equal minimum
rotations.

All functions are generic over indexable sequences such as `std::string` and
`std::vector<int>`. Elements are compared with `operator<`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<int> lyndon_factor_boundaries(const Sequence& sequence)` | Returns boundaries `0 = a[0] < a[1] < ... < a[k] = N`. | $O(N)$ |
| `vector<pair<int, int>> lyndon_factorization(const Sequence& sequence)` | Returns the factor intervals as half-open ranges `[left, right)`. | $O(N)$ |
| `int minimum_cyclic_shift(const Sequence& sequence)` | Returns the smallest starting index of a lexicographically minimum cyclic shift. | $O(N)$ |

For an empty sequence, `lyndon_factor_boundaries` returns `{0}`,
`lyndon_factorization` returns an empty vector, and `minimum_cyclic_shift`
returns `0`.

## Example

```cpp
#include "string/lyndon_factorization.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "banana";
    auto factors = m1une::string::lyndon_factorization(text);

    for (auto [left, right] : factors) {
        std::cout << text.substr(left, right - left) << "\n";
    }

    int start = m1une::string::minimum_cyclic_shift(text);
    std::cout << text.substr(start) + text.substr(0, start) << "\n";
}
```
