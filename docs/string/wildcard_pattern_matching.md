---
title: Wildcard Pattern Matching
documentation_of: ../../string/wildcard_pattern_matching.hpp
---

## Overview

Wildcard pattern matching checks every alignment of a pattern within a text.
By default, `*` matches any character, whether it occurs in the text or the
pattern. A different wildcard byte can be selected explicitly.

The implementation uses exact NTT convolutions rather than randomized hashing.

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<bool> wildcard_pattern_matching(const string& text, const string& pattern, char wildcard = '*')` | Returns one flag for each alignment; result `i` describes `text[i, i + pattern.size())`. | $O((N + M) \log(N + M))$ time and $O(N + M)$ memory |

An empty pattern matches at all `N + 1` positions. If the pattern is longer
than the text, the result is empty. Characters are treated as bytes, so this
function does not perform Unicode decoding.

## Example

```cpp
#include "string/wildcard_pattern_matching.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "abacaba";
    std::string pattern = "a*a";
    std::vector<bool> matches =
        m1une::string::wildcard_pattern_matching(text, pattern);

    for (int i = 0; i < int(matches.size()); i++) {
        if (matches[i]) std::cout << i << '\n';
    }
}
```
