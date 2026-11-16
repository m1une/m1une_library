---
title: Bracket Monoid
documentation_of: ../../monoid/bracket.hpp
---

## Overview

A monoid for processing bracket sequences (parentheses matching). It maintains the number of successfully matched pairs, as well as the count of unmatched closing `)` and opening `(` brackets.

A sequence is considered a "valid bracket sequence" if both `unmatched_right` and `unmatched_left` are `0`.

## Interface and Complexity

```cpp
using value_type = BracketNode;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr value_type make(char c)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/bracket.hpp"
#include <iostream>
#include <string>
#include <vector>

using BracketM = m1une::monoid::Bracket;

int main() {
    std::string S = "())(()()";
    int N = S.size();

    std::vector<BracketM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = BracketM::make(S[i]);
    }

    m1une::ds::Segtree<BracketM> seg(init_data);

    // Query range [3, 8) -> "(()()"
    auto res = seg.prod(3, 8);

    std::cout << "Matched Pairs: " << res.matched << "\n"; // Output: 2
    std::cout << "Unmatched '(': " << res.unmatched_left << "\n"; // Output: 1
    std::cout << "Unmatched ')': " << res.unmatched_right << "\n"; // Output: 0

    return 0;
}
```
