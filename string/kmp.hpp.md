---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/kmp.test.cpp
    title: verify/string/kmp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/kmp.hpp\"\n\n\n\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace string {\n\n// Returns the KMP prefix function.\ntemplate <class\
    \ Sequence>\nstd::vector<int> prefix_function(const Sequence& sequence) {\n  \
    \  int n = int(sequence.size());\n    std::vector<int> prefix(n);\n    for (int\
    \ i = 1; i < n; i++) {\n        int j = prefix[i - 1];\n        while (j > 0 &&\
    \ sequence[i] != sequence[j]) {\n            j = prefix[j - 1];\n        }\n \
    \       if (sequence[i] == sequence[j]) j++;\n        prefix[i] = j;\n    }\n\
    \    return prefix;\n}\n\n// Returns every starting position where pattern occurs\
    \ in text.\n// An empty pattern occurs at every position from 0 through text.size().\n\
    template <class Text, class Pattern>\nstd::vector<int> kmp_search(const Text&\
    \ text, const Pattern& pattern) {\n    int n = int(text.size());\n    int m =\
    \ int(pattern.size());\n    if (m == 0) {\n        std::vector<int> occurrences(n\
    \ + 1);\n        for (int i = 0; i <= n; i++) occurrences[i] = i;\n        return\
    \ occurrences;\n    }\n\n    std::vector<int> prefix = prefix_function(pattern);\n\
    \    std::vector<int> occurrences;\n    int matched = 0;\n    for (int i = 0;\
    \ i < n; i++) {\n        while (matched > 0 && text[i] != pattern[matched]) {\n\
    \            matched = prefix[matched - 1];\n        }\n        if (text[i] ==\
    \ pattern[matched]) matched++;\n        if (matched == m) {\n            occurrences.push_back(i\
    \ - m + 1);\n            matched = prefix[matched - 1];\n        }\n    }\n  \
    \  return occurrences;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_STRING_KMP_HPP\n#define M1UNE_STRING_KMP_HPP 1\n\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace string {\n\n// Returns the KMP prefix\
    \ function.\ntemplate <class Sequence>\nstd::vector<int> prefix_function(const\
    \ Sequence& sequence) {\n    int n = int(sequence.size());\n    std::vector<int>\
    \ prefix(n);\n    for (int i = 1; i < n; i++) {\n        int j = prefix[i - 1];\n\
    \        while (j > 0 && sequence[i] != sequence[j]) {\n            j = prefix[j\
    \ - 1];\n        }\n        if (sequence[i] == sequence[j]) j++;\n        prefix[i]\
    \ = j;\n    }\n    return prefix;\n}\n\n// Returns every starting position where\
    \ pattern occurs in text.\n// An empty pattern occurs at every position from 0\
    \ through text.size().\ntemplate <class Text, class Pattern>\nstd::vector<int>\
    \ kmp_search(const Text& text, const Pattern& pattern) {\n    int n = int(text.size());\n\
    \    int m = int(pattern.size());\n    if (m == 0) {\n        std::vector<int>\
    \ occurrences(n + 1);\n        for (int i = 0; i <= n; i++) occurrences[i] = i;\n\
    \        return occurrences;\n    }\n\n    std::vector<int> prefix = prefix_function(pattern);\n\
    \    std::vector<int> occurrences;\n    int matched = 0;\n    for (int i = 0;\
    \ i < n; i++) {\n        while (matched > 0 && text[i] != pattern[matched]) {\n\
    \            matched = prefix[matched - 1];\n        }\n        if (text[i] ==\
    \ pattern[matched]) matched++;\n        if (matched == m) {\n            occurrences.push_back(i\
    \ - m + 1);\n            matched = prefix[matched - 1];\n        }\n    }\n  \
    \  return occurrences;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n\
    #endif  // M1UNE_STRING_KMP_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/kmp.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-13 04:27:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/kmp.test.cpp
  - verify/string/string_algorithms.test.cpp
documentation_of: string/kmp.hpp
layout: document
title: Knuth-Morris-Pratt
---

## Overview

The prefix function stores, for every prefix ending at position `i`, the length
of its longest proper prefix that is also a suffix. Knuth-Morris-Pratt uses it
to find every occurrence of a pattern without backing up in the text.

Both functions are generic over indexable sequences with comparable elements.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<int> prefix_function(const Sequence& sequence)` | Returns the prefix-function array. | $O(N)$ |
| `vector<int> kmp_search(const Text& text, const Pattern& pattern)` | Returns every occurrence's starting index, including overlapping matches. | $O(N + M)$ |

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
