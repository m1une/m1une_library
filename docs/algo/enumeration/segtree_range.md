---
title: Segment Tree Range Split
documentation_of: ../../../algo/enumeration/segtree_range.hpp
---

## Overview

`split_segtree_range` decomposes a half-open range into the maximal aligned
power-of-two ranges used by a segment tree. The result is ordered from left to
right, is disjoint, and has union exactly `[left, right)`.

For example, `[3, 13)` is split into `[3, 4)`, `[4, 8)`, `[8, 12)`, and
`[12, 13)`. These are precisely the maximal nodes contained in the query range
of a perfect segment tree whose leaf count is any power of two at least
`right`; the tree size does not need to be passed to the function.

## Function

```cpp
template <std::integral Int>
requires(!std::same_as<std::remove_cv_t<Int>, bool>)
std::vector<std::pair<Int, Int>> split_segtree_range(Int left, Int right);
```

`Int` may be any integral type except `bool`. Both endpoints must be
nonnegative and must satisfy `left <= right`.

| Function | Description | Complexity |
| --- | --- | --- |
| `split_segtree_range(left, right)` | Returns the maximal segment-tree ranges covering `[left, right)`. | $O(K)$ time and memory, where $K = O(\log(right - left + 1))$ is the number of returned ranges. |

Every returned `[a, b)` has positive power-of-two length and `a` is divisible
by `b - a`. No returned range can be replaced by its parent while remaining
inside `[left, right)`. An empty input range returns an empty vector.

The function does not mutate its arguments or any external state.

## Example

```cpp
#include "algo/enumeration/segtree_range.hpp"

#include <iostream>

int main() {
    for (auto [left, right] :
         m1une::algo::split_segtree_range(3, 13)) {
        std::cout << "[" << left << ", " << right << ")\n";
    }
}
```

Output:

```text
[3, 4)
[4, 8)
[8, 12)
[12, 13)
```
