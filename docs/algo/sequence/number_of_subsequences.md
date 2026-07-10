---
title: Number of Subsequences
documentation_of: ../../../algo/sequence/number_of_subsequences.hpp
---

## Overview

`number_of_distinct_subsequences` counts the distinct nonempty subsequences of
a sequence. Two subsequences are considered equal when their value sequences
are equal, even if they use different source indices.

For example, `[1, 1]` has two distinct nonempty subsequences: `[1]` and
`[1, 1]`.

The dynamic program maintains the number of distinct subsequences including
the empty sequence. Appending a value initially doubles that number. The
subsequences already created when the same value last appeared are subtracted
to remove duplicates.

## Requirements

`T` must support `<` as a strict weak ordering. `Mint` must be constructible
from integers and support addition and subtraction. It is normally a modular
integer type such as `m1une::math::ModInt<998244353>`.

## Interface

| Function | Complexity | Description |
| --- | --- | --- |
| `Mint number_of_distinct_subsequences<Mint>(const std::vector<T>& values)` | $O(N\log N)$ time and $O(N)$ memory | Counts distinct nonempty subsequences. |
| `Mint number_of_subsequences<Mint>(const std::vector<T>& values)` | $O(N\log N)$ time and $O(N)$ memory | Alias matching the Library Checker problem name. |

The empty input has zero nonempty subsequences. The input vector is not
modified.

## Example

```cpp
#include "algo/sequence/number_of_subsequences.hpp"
#include "math/modint.hpp"

#include <iostream>
#include <vector>

int main() {
    using Mint = m1une::math::ModInt<998244353>;
    std::vector<int> values = {1, 2, 1};

    Mint answer = m1une::algo::number_of_subsequences<Mint>(values);
    std::cout << answer << "\n"; // 6
}
```
