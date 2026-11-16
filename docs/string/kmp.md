---
title: Knuth-Morris-Pratt
documentation_of: ../../string/kmp.hpp
---

## Overview

The prefix function stores, for every prefix ending at position `i`, the length
of its longest proper prefix that is also a suffix. Knuth-Morris-Pratt uses it
to find every occurrence of a pattern without backing up in the text.

Both functions are generic over indexable sequences with comparable elements.

## Requirements

`N` is the text length (the sequence length for `prefix_function`), and `M` is
the pattern length. Elements must support equality comparison; the sequences
must support `size()` and indexed access. Returned positions are zero-based.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `std::vector<int> prefix_function(const Sequence& sequence)` | Returns the prefix-function array. | $O(N)$ |
| `std::vector<int> kmp_search(const Text& text, const Pattern& pattern)` | Returns every occurrence's starting index, including overlapping matches. | $O(N + M)$ |

An empty pattern occurs at every position from `0` through `text.size()`.

## Example

```cpp
#include "string/kmp.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "ababa";
    std::string pattern = "aba";

    for (int position : m1une::string::kmp_search(text, pattern)) {
        std::cout << position << "\n"; // 0, then 2
    }
}
```
