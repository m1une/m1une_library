---
title: Longest Common Substring
documentation_of: ../../string/longest_common_substring.hpp
---

## Overview

`longest_common_substring(first, second)` finds one longest sequence that occurs
as a contiguous substring of both inputs. It returns the matching half-open
interval in each input.

The implementation builds a suffix array and adjacent LCP array over the two
inputs joined by a unique separator. Input symbols are coordinate-compressed, so
the separator cannot collide with a real symbol.

`Sequence` must provide `size()`, `operator[]`, `begin()`, and `end()`.
Elements must be sortable and equality-comparable.

## Result

| Field or Method | Description | Complexity |
| --- | --- | --- |
| `int first_left`, `int first_right` | Half-open interval in the first sequence. | `O(1)` |
| `int second_left`, `int second_right` | Half-open interval in the second sequence. | `O(1)` |
| `int length() const` | Returns the common substring length. | `O(1)` |
| `bool empty() const` | Returns whether the length is zero. | `O(1)` |
| `pair<int, int> first_interval() const` | Returns `{first_left, first_right}`. | `O(1)` |
| `pair<int, int> second_interval() const` | Returns `{second_left, second_right}`. | `O(1)` |

If there is no common nonempty substring, all endpoints are zero. When several
maximum substrings exist, any one of them may be returned.

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `LongestCommonSubstring longest_common_substring(const Sequence& first, const Sequence& second)` | Finds one longest common substring. | `O((N + M) \log(N + M))` |

The memory usage is `O(N + M)`.

## Example

```cpp
#include "string/longest_common_substring.hpp"

#include <iostream>
#include <string>

int main() {
    std::string first = "xabxac";
    std::string second = "abcabxabcd";
    auto result = m1une::string::longest_common_substring(first, second);

    std::cout << result.first_left << " " << result.first_right << "\n";
    std::cout << result.second_left << " " << result.second_right << "\n";
}
```
