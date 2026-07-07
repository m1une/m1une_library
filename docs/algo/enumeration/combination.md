---
title: Combination Masks
documentation_of: ../../../algo/enumeration/combination.hpp
---

## Overview

This header generates fixed-size subsets as bitmasks. The public namespace is
`m1une::algo`.

`UInt` must be an unsigned integral type other than `bool`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `first_combination_mask<UInt>(bit_count, choose)` | Returns the smallest mask with `choose` bits among `bit_count` bits. | $O(1)$ |
| `next_combination_mask(mask, bit_count)` | Advances `mask` to the next mask with the same popcount; returns false when none exists. | $O(1)$ |
| `for_each_combination_mask<UInt>(bit_count, choose, f)` | Calls `f(mask)` for every `choose`-subset of `[0, bit_count)`. | $O(\binom{B}{K})$ |

Masks are generated in increasing numeric order.

## Example

```cpp
#include "algo/enumeration/combination.hpp"

#include <cstdint>
#include <vector>

int main() {
    std::vector<std::uint64_t> masks;
    m1une::algo::for_each_combination_mask(5, 3, [&](std::uint64_t mask) {
        masks.push_back(mask);
    });
}
```
