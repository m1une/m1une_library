---
title: Longest Common Extension
documentation_of: ../../string/lce.hpp
---

## Overview

`LCE` is a static structure for longest-common-extension queries on one
sequence. It returns the longest common prefix length of suffixes starting at
two positions, which is useful for substring comparison, runs, repetitions, and
suffix-array based string problems.

The implementation builds a suffix array, the adjacent LCP array, and a sparse
table over the LCP array. Queries are deterministic and do not use hashing.

`Sequence` must provide `size()`, `operator[]`, `begin()`, and `end()`.
Elements must be sortable for construction. The comparison helpers also require
element `<`.

## Methods

Let `N = size()`.

| Method | Description | Complexity |
| --- | --- | --- |
| `LCE()` | Creates an empty structure. | `O(1)` |
| `LCE(const Sequence& sequence)` | Copies `sequence` and builds the structure. | `O(N \log N)` |
| `LCE(Sequence&& sequence)` | Moves `sequence` and builds the structure. | `O(N \log N)` |
| `int size() const` | Returns `N`. | `O(1)` |
| `bool empty() const` | Returns whether `N == 0`. | `O(1)` |
| `const Sequence& sequence() const` | Returns the stored sequence. | `O(1)` |
| `const vector<int>& suffix_array() const` | Returns suffix starts in lexicographic order. | `O(1)` |
| `const vector<int>& rank() const` | Returns inverse suffix-array ranks. | `O(1)` |
| `const vector<int>& lcp_array() const` | Returns adjacent suffix LCP lengths. | `O(1)` |
| `int lce(int i, int j) const` | Returns `LCP(sequence[i..], sequence[j..])`. | `O(1)` |
| `int lce(int i, int j, int limit) const` | Returns `min(lce(i, j), limit)`. | `O(1)` |
| `int lcp(int i, int j) const` | Alias of `lce(i, j)`. | `O(1)` |
| `int operator()(int i, int j) const` | Alias of `lce(i, j)`. | `O(1)` |
| `int compare_suffix(int i, int j) const` | Lexicographically compares suffixes. | `O(1)` |
| `int compare(int l1, int r1, int l2, int r2) const` | Lexicographically compares two half-open substrings. | `O(1)` |

`lce(i, i)` returns `N - i`. Positions `i` and `j` may be `N`, representing
the empty suffix. Other indices must be in `[0, N]`.

`compare_suffix` and `compare` return `-1`, `0`, or `1`.

The memory usage is `O(N \log N)`.

## Example

```cpp
#include "string/lce.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "banana";
    m1une::string::LCE<> lce(text);

    std::cout << lce.lce(1, 3) << "\n";          // 3: "anana" and "ana"
    std::cout << lce.compare(1, 4, 3, 6) << "\n"; // 0: both are "ana"
}
```
