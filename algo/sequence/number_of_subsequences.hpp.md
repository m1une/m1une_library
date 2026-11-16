---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  - icon: ':warning:'
    path: algo/sequence/all.hpp
    title: Sequence Algorithms All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/algo/sequence/number_of_subsequences.test.cpp
    title: verify/algo/sequence/number_of_subsequences.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/sequence/number_of_subsequences.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n//\
    \ Returns the number of distinct nonempty subsequences.\ntemplate <class Mint,\
    \ class T>\nMint number_of_distinct_subsequences(const std::vector<T>& values)\
    \ {\n    std::vector<T> compressed = values;\n    std::sort(compressed.begin(),\
    \ compressed.end());\n    compressed.erase(\n        std::unique(compressed.begin(),\
    \ compressed.end()),\n        compressed.end()\n    );\n\n    std::vector<Mint>\
    \ previous_total(compressed.size(), Mint(0));\n    Mint total = 1;\n    for (const\
    \ T& value : values) {\n        int rank = int(\n            std::lower_bound(\n\
    \                compressed.begin(),\n                compressed.end(),\n    \
    \            value\n            ) - compressed.begin()\n        );\n        Mint\
    \ old_total = total;\n        total = total + total - previous_total[rank];\n\
    \        previous_total[rank] = old_total;\n    }\n    return total - Mint(1);\n\
    }\n\ntemplate <class Mint, class T>\nMint number_of_subsequences(const std::vector<T>&\
    \ values) {\n    return number_of_distinct_subsequences<Mint>(values);\n}\n\n\
    }  // namespace algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_SEQUENCE_NUMBER_OF_SUBSEQUENCES_HPP\n#define M1UNE_ALGO_SEQUENCE_NUMBER_OF_SUBSEQUENCES_HPP\
    \ 1\n\n#include <algorithm>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ algo {\n\n// Returns the number of distinct nonempty subsequences.\ntemplate\
    \ <class Mint, class T>\nMint number_of_distinct_subsequences(const std::vector<T>&\
    \ values) {\n    std::vector<T> compressed = values;\n    std::sort(compressed.begin(),\
    \ compressed.end());\n    compressed.erase(\n        std::unique(compressed.begin(),\
    \ compressed.end()),\n        compressed.end()\n    );\n\n    std::vector<Mint>\
    \ previous_total(compressed.size(), Mint(0));\n    Mint total = 1;\n    for (const\
    \ T& value : values) {\n        int rank = int(\n            std::lower_bound(\n\
    \                compressed.begin(),\n                compressed.end(),\n    \
    \            value\n            ) - compressed.begin()\n        );\n        Mint\
    \ old_total = total;\n        total = total + total - previous_total[rank];\n\
    \        previous_total[rank] = old_total;\n    }\n    return total - Mint(1);\n\
    }\n\ntemplate <class Mint, class T>\nMint number_of_subsequences(const std::vector<T>&\
    \ values) {\n    return number_of_distinct_subsequences<Mint>(values);\n}\n\n\
    }  // namespace algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_SEQUENCE_NUMBER_OF_SUBSEQUENCES_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/sequence/number_of_subsequences.hpp
  requiredBy:
  - algo/sequence/all.hpp
  - algo/all.hpp
  timestamp: '2026-07-10 18:48:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/sequence/number_of_subsequences.test.cpp
documentation_of: algo/sequence/number_of_subsequences.hpp
layout: document
title: Number of Subsequences
---

## Overview

`number_of_distinct_subsequences` counts the distinct nonempty subsequences of
a sequence. Two subsequences are considered equal when their value sequences
are equal, even if they use different source indices.

For example, `[1, 1]` has two distinct nonempty subsequences: `[1]` and
`[1, 1]`.

The dynamic program maintains the number of distinct subsequences including
the empty sequence. Appending a value initially doubles that number. The
subsequences already created when the same value last appeared are subtracted
to remove duplicates.

## Requirements

`T` must support `<` as a strict weak ordering. `Mint` must be constructible
from integers and support addition and subtraction. It is normally a modular
integer type such as `m1une::math::ModInt<998244353>`.

## Interface

| Function | Complexity | Description |
| --- | --- | --- |
| `Mint number_of_distinct_subsequences<Mint>(const std::vector<T>& values)` | $O(N\log N)$ time and $O(N)$ memory | Counts distinct nonempty subsequences. |
| `Mint number_of_subsequences<Mint>(const std::vector<T>& values)` | $O(N\log N)$ time and $O(N)$ memory | Alias matching the Library Checker problem name. |

The empty input has zero nonempty subsequences. The input vector is not
modified.

## Example

```cpp
#include "algo/sequence/number_of_subsequences.hpp"
#include "math/modint.hpp"

#include <iostream>
#include <vector>

int main() {
    using Mint = m1une::math::ModInt<998244353>;
    std::vector<int> values = {1, 2, 1};

    Mint answer = m1une::algo::number_of_subsequences<Mint>(values);
    std::cout << answer << "\n"; // 6
}
```
