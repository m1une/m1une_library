---
title: Permutation Lexicographical Order
documentation_of: ../../../algo/enumeration/permutation_lexicographical_order.hpp
---

## Overview

This header converts in both directions between a permutation of `[0, N)` and
its zero-based position among all such permutations in lexicographical order.
It uses a Fenwick tree and a Lehmer code, without enumerating earlier
permutations.

```cpp
#include "algo/enumeration/permutation_lexicographical_order.hpp"
```

## Template Requirements

`UInt` must be an unsigned integral type other than `bool`. The default is
`std::uint64_t`.

The rank functions accept a random-access sequence whose `size()` fits in
`int` and whose elements are integral values other than `bool`.

## Functions

Let `N` be the permutation size.

| Function | Description | Complexity |
| --- | --- | --- |
| `optional<UInt> checked_permutation_lexicographical_rank<UInt>(permutation)` | Returns its zero-based rank, or `nullopt` if the input is not a permutation of `[0, N)` or the rank does not fit in `UInt`. | $O(N \log N)$ time and $O(N)$ memory |
| `UInt permutation_lexicographical_rank<UInt>(permutation)` | Returns its zero-based rank. The input and result must be valid. | $O(N \log N)$ time and $O(N)$ memory |
| `optional<vector<int>> checked_kth_lexicographical_permutation(size, rank)` | Returns the permutation at `rank`, or `nullopt` if `size` is negative or `rank` is at least $N!$. | $O(N \log N)$ time and $O(N)$ memory |
| `vector<int> kth_lexicographical_permutation(size, rank)` | Returns the permutation at `rank`. The rank must be less than $N!$. | $O(N \log N)$ time and $O(N)$ memory |

The unchecked functions assert their preconditions. The checked functions do
not rely on computing $N!$, so they remain usable when $N!$ does not fit in
`UInt`. In particular, a small rank of a large permutation can still be ranked
and selected exactly.

The only permutation of size zero is the empty permutation, with rank zero.

## Example

```cpp
#include "algo/enumeration/permutation_lexicographical_order.hpp"

#include <cstdint>
#include <vector>

int main() {
    std::vector<int> permutation = {2, 0, 3, 1};
    std::uint64_t rank =
        m1une::algo::permutation_lexicographical_rank(permutation);

    std::vector<int> restored =
        m1une::algo::kth_lexicographical_permutation(4, rank);
}
```
