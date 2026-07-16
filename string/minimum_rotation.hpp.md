---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  - icon: ':heavy_check_mark:'
    path: string/lyndon_factorization.hpp
    title: Lyndon Factorization
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/lyndon_factorization.test.cpp
    title: verify/string/lyndon_factorization.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/minimum_rotation.test.cpp
    title: verify/string/minimum_rotation.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/minimum_rotation.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace string {\n\n// Returns the smallest starting index of a lexicographically\
    \ minimum cyclic shift.\ntemplate <class Sequence>\nint minimum_cyclic_shift(const\
    \ Sequence& sequence) {\n    const int size = int(sequence.size());\n    if (size\
    \ == 0) return 0;\n\n    auto less = [&](int left, int right) {\n        return\
    \ sequence[left < size ? left : left - size] <\n               sequence[right\
    \ < size ? right : right - size];\n    };\n\n    int answer = 0;\n    int start\
    \ = 0;\n    while (start < size) {\n        answer = start;\n        int scan\
    \ = start + 1;\n        int matched = start;\n        while (scan < 2 * size &&\
    \ !less(scan, matched)) {\n            if (less(matched, scan)) {\n          \
    \      matched = start;\n            } else {\n                matched++;\n  \
    \          }\n            scan++;\n        }\n\n        const int period = scan\
    \ - matched;\n        while (start <= matched) start += period;\n    }\n    return\
    \ answer;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_MINIMUM_ROTATION_HPP\n#define M1UNE_STRING_MINIMUM_ROTATION_HPP\
    \ 1\n\nnamespace m1une {\nnamespace string {\n\n// Returns the smallest starting\
    \ index of a lexicographically minimum cyclic shift.\ntemplate <class Sequence>\n\
    int minimum_cyclic_shift(const Sequence& sequence) {\n    const int size = int(sequence.size());\n\
    \    if (size == 0) return 0;\n\n    auto less = [&](int left, int right) {\n\
    \        return sequence[left < size ? left : left - size] <\n               sequence[right\
    \ < size ? right : right - size];\n    };\n\n    int answer = 0;\n    int start\
    \ = 0;\n    while (start < size) {\n        answer = start;\n        int scan\
    \ = start + 1;\n        int matched = start;\n        while (scan < 2 * size &&\
    \ !less(scan, matched)) {\n            if (less(matched, scan)) {\n          \
    \      matched = start;\n            } else {\n                matched++;\n  \
    \          }\n            scan++;\n        }\n\n        const int period = scan\
    \ - matched;\n        while (start <= matched) start += period;\n    }\n    return\
    \ answer;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_MINIMUM_ROTATION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/minimum_rotation.hpp
  requiredBy:
  - string/all.hpp
  - string/lyndon_factorization.hpp
  timestamp: '2026-07-13 05:39:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/lyndon_factorization.test.cpp
  - verify/string/string_algorithms.test.cpp
  - verify/string/minimum_rotation.test.cpp
documentation_of: string/minimum_rotation.hpp
layout: document
title: Minimum Rotation
---

## Overview

`minimum_cyclic_shift` finds where the lexicographically smallest rotation of a
sequence begins. If several starting positions produce the same minimum
rotation, it returns the smallest index.

```cpp
#include "string/minimum_rotation.hpp"
```

The function is in `m1une::string` and uses the same Duval-style linear scan as
the previous implementation in `lyndon_factorization.hpp`.

## Interface

```cpp
template <class Sequence>
int minimum_cyclic_shift(const Sequence& sequence);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `minimum_cyclic_shift(sequence)` | Returns the earliest starting index of a lexicographically minimum cyclic shift. | $O(N)$ time and $O(1)$ additional memory |

`Sequence` must provide `size()` and random access through `operator[]`. Its
elements are compared using `operator<`. Strings, vectors, and arrays are
supported.

The empty sequence returns `0`. The function does not construct or modify a
rotation; it only returns its starting index.

`lyndon_factorization.hpp` includes this header, preserving the old include
behavior. New code that only needs minimum rotation can include this smaller
header directly.

## Example

```cpp
#include "string/minimum_rotation.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "banana";
    int start = m1une::string::minimum_cyclic_shift(text);
    std::string rotation = text.substr(start) + text.substr(0, start);

    std::cout << start << '\n';     // 5
    std::cout << rotation << '\n';  // abanan
}
```
