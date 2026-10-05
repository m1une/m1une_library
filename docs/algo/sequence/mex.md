---
title: Mex
documentation_of: ../../../algo/sequence/mex.hpp
---

## Overview

`mex(values)` returns the smallest nonnegative integer absent from an integer
vector. For example, the mex of `0, 1, 1, 3` is `2`. The empty vector has mex `0`.

## Interface

| Exact signature | Description | Complexity |
| --- | --- | --- |
| `template <class T> int mex(const std::vector<T>& values)` | Returns the mex without modifying `values`. | $O(N)$ time and $O(N)$ auxiliary space |

`T` must be a standard integral type, signed or unsigned. The vector length `N`
must fit in `int`; this is checked by an assertion. Duplicates, negative values,
and values at least `N` do not affect the answer. The result is always in `[0, N]`.
The implementation uses a byte per candidate and does not sort the input.

For repeated queries with insertions and deletions, use
[`MexMultiset`](../../ds/bst/mex_multiset.md).

## Example

```cpp
#include "algo/sequence/mex.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {3, 0, 1, 1, -5, 1000000000000LL};
    std::cout << m1une::algo::mex(values) << '\n';  // 2
}
```
