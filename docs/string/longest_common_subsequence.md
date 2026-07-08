---
title: Longest Common Subsequence
documentation_of: ../../string/longest_common_subsequence.hpp
---

## Overview

`longest_common_subsequence(first, second)` finds one longest sequence that is
a subsequence of both inputs. The returned object stores matched index pairs,
so the values can be recovered from either input.

Use `longest_common_subsequence_length(first, second)` when only the length is
needed. It avoids storing the full DP table.

`FirstSequence` and `SecondSequence` must provide `size()` and `operator[]`.
The expressions `first[i] == second[j]` must be valid.

## Result

| Field or Method | Description | Complexity |
| --- | --- | --- |
| `vector<pair<int, int>> matches` | Matched index pairs in increasing order. | `O(1)` |
| `int length() const` | Returns the LCS length. | `O(1)` |
| `bool empty() const` | Returns whether the length is zero. | `O(1)` |
| `vector<int> first_indices() const` | Returns matched indices in the first sequence. | `O(L)` |
| `vector<int> second_indices() const` | Returns matched indices in the second sequence. | `O(L)` |
| `vector<T> values_from_first(first) const` | Returns the matched values from the first sequence. | `O(L)` |
| `vector<T> values_from_second(second) const` | Returns the matched values from the second sequence. | `O(L)` |

Here `L` is the LCS length. If several longest subsequences exist, any one of
them may be returned.

## Functions

Let `N = first.size()` and `M = second.size()`.

| Function | Description | Complexity |
| --- | --- | --- |
| `int longest_common_subsequence_length(const FirstSequence& first, const SecondSequence& second)` | Returns the LCS length. | `O(NM)` time, `O(min(N, M))` memory |
| `LongestCommonSubsequence longest_common_subsequence(const FirstSequence& first, const SecondSequence& second)` | Returns one LCS as matched index pairs. | `O(NM)` time and memory |

## Example

```cpp
#include "string/longest_common_subsequence.hpp"

#include <iostream>
#include <string>

int main() {
    std::string first = "abcbdab";
    std::string second = "bdcaba";
    auto result = m1une::string::longest_common_subsequence(first, second);

    std::cout << result.length() << "\n"; // 4
    for (char value : result.values_from_first(first)) {
        std::cout << value;
    }
    std::cout << "\n";
}
```
