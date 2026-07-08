---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/lyndon_factorization.test.cpp
    title: verify/string/lyndon_factorization.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/lyndon_factorization.hpp\"\n\n\n\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace string {\n\n// Returns boundaries\
    \ 0 = a[0] < a[1] < ... < a[k] = sequence.size()\n// of the Lyndon factorization.\n\
    template <class Sequence>\nstd::vector<int> lyndon_factor_boundaries(const Sequence&\
    \ sequence) {\n    int n = int(sequence.size());\n    std::vector<int> boundaries;\n\
    \    boundaries.push_back(0);\n\n    int i = 0;\n    while (i < n) {\n       \
    \ int j = i + 1;\n        int k = i;\n        while (j < n && !(sequence[j] <\
    \ sequence[k])) {\n            if (sequence[k] < sequence[j]) {\n            \
    \    k = i;\n            } else {\n                k++;\n            }\n     \
    \       j++;\n        }\n\n        int length = j - k;\n        while (i <= k)\
    \ {\n            i += length;\n            boundaries.push_back(i);\n        }\n\
    \    }\n    return boundaries;\n}\n\n// Returns half-open intervals [left, right)\
    \ of the Lyndon factorization.\ntemplate <class Sequence>\nstd::vector<std::pair<int,\
    \ int>> lyndon_factorization(const Sequence& sequence) {\n    std::vector<int>\
    \ boundaries = lyndon_factor_boundaries(sequence);\n    std::vector<std::pair<int,\
    \ int>> factors;\n    factors.reserve(boundaries.size() - 1);\n    for (int i\
    \ = 0; i + 1 < int(boundaries.size()); i++) {\n        factors.emplace_back(boundaries[i],\
    \ boundaries[i + 1]);\n    }\n    return factors;\n}\n\n// Returns the smallest\
    \ starting index of a lexicographically minimum cyclic shift.\ntemplate <class\
    \ Sequence>\nint minimum_cyclic_shift(const Sequence& sequence) {\n    int n =\
    \ int(sequence.size());\n    if (n == 0) return 0;\n\n    auto less = [&](int\
    \ left, int right) {\n        return sequence[left < n ? left : left - n] <\n\
    \               sequence[right < n ? right : right - n];\n    };\n\n    int answer\
    \ = 0;\n    int i = 0;\n    while (i < n) {\n        answer = i;\n        int\
    \ j = i + 1;\n        int k = i;\n        while (j < 2 * n && !less(j, k)) {\n\
    \            if (less(k, j)) {\n                k = i;\n            } else {\n\
    \                k++;\n            }\n            j++;\n        }\n\n        int\
    \ length = j - k;\n        while (i <= k) i += length;\n    }\n    return answer;\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_LYNDON_FACTORIZATION_HPP\n#define M1UNE_STRING_LYNDON_FACTORIZATION_HPP\
    \ 1\n\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace string\
    \ {\n\n// Returns boundaries 0 = a[0] < a[1] < ... < a[k] = sequence.size()\n\
    // of the Lyndon factorization.\ntemplate <class Sequence>\nstd::vector<int> lyndon_factor_boundaries(const\
    \ Sequence& sequence) {\n    int n = int(sequence.size());\n    std::vector<int>\
    \ boundaries;\n    boundaries.push_back(0);\n\n    int i = 0;\n    while (i <\
    \ n) {\n        int j = i + 1;\n        int k = i;\n        while (j < n && !(sequence[j]\
    \ < sequence[k])) {\n            if (sequence[k] < sequence[j]) {\n          \
    \      k = i;\n            } else {\n                k++;\n            }\n   \
    \         j++;\n        }\n\n        int length = j - k;\n        while (i <=\
    \ k) {\n            i += length;\n            boundaries.push_back(i);\n     \
    \   }\n    }\n    return boundaries;\n}\n\n// Returns half-open intervals [left,\
    \ right) of the Lyndon factorization.\ntemplate <class Sequence>\nstd::vector<std::pair<int,\
    \ int>> lyndon_factorization(const Sequence& sequence) {\n    std::vector<int>\
    \ boundaries = lyndon_factor_boundaries(sequence);\n    std::vector<std::pair<int,\
    \ int>> factors;\n    factors.reserve(boundaries.size() - 1);\n    for (int i\
    \ = 0; i + 1 < int(boundaries.size()); i++) {\n        factors.emplace_back(boundaries[i],\
    \ boundaries[i + 1]);\n    }\n    return factors;\n}\n\n// Returns the smallest\
    \ starting index of a lexicographically minimum cyclic shift.\ntemplate <class\
    \ Sequence>\nint minimum_cyclic_shift(const Sequence& sequence) {\n    int n =\
    \ int(sequence.size());\n    if (n == 0) return 0;\n\n    auto less = [&](int\
    \ left, int right) {\n        return sequence[left < n ? left : left - n] <\n\
    \               sequence[right < n ? right : right - n];\n    };\n\n    int answer\
    \ = 0;\n    int i = 0;\n    while (i < n) {\n        answer = i;\n        int\
    \ j = i + 1;\n        int k = i;\n        while (j < 2 * n && !less(j, k)) {\n\
    \            if (less(k, j)) {\n                k = i;\n            } else {\n\
    \                k++;\n            }\n            j++;\n        }\n\n        int\
    \ length = j - k;\n        while (i <= k) i += length;\n    }\n    return answer;\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_LYNDON_FACTORIZATION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/lyndon_factorization.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-09 01:38:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/lyndon_factorization.test.cpp
  - verify/string/string_algorithms.test.cpp
documentation_of: string/lyndon_factorization.hpp
layout: document
title: Lyndon Factorization
---

## Overview

The Lyndon factorization decomposes a sequence into a lexicographically
non-increasing sequence of Lyndon words. It is useful in string ordering,
minimal rotations, runs, and suffix-related algorithms.

The implementation uses Duval's algorithm. The minimum cyclic shift helper uses
the same idea and returns the earliest starting position among equal minimum
rotations.

All functions are generic over indexable sequences such as `std::string` and
`std::vector<int>`. Elements are compared with `operator<`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<int> lyndon_factor_boundaries(const Sequence& sequence)` | Returns boundaries `0 = a[0] < a[1] < ... < a[k] = N`. | $O(N)$ |
| `vector<pair<int, int>> lyndon_factorization(const Sequence& sequence)` | Returns the factor intervals as half-open ranges `[left, right)`. | $O(N)$ |
| `int minimum_cyclic_shift(const Sequence& sequence)` | Returns the smallest starting index of a lexicographically minimum cyclic shift. | $O(N)$ |

For an empty sequence, `lyndon_factor_boundaries` returns `{0}`,
`lyndon_factorization` returns an empty vector, and `minimum_cyclic_shift`
returns `0`.

## Example

```cpp
#include "string/lyndon_factorization.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "banana";
    auto factors = m1une::string::lyndon_factorization(text);

    for (auto [left, right] : factors) {
        std::cout << text.substr(left, right - left) << "\n";
    }

    int start = m1une::string::minimum_cyclic_shift(text);
    std::cout << text.substr(start) + text.substr(0, start) << "\n";
}
```
