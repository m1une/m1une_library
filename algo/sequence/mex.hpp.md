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
    path: verify/ds/bst/mex_multiset.test.cpp
    title: verify/ds/bst/mex_multiset.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/sequence/mex.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <limits>\n#include <type_traits>\n#include <vector>\n\n\
    namespace m1une {\nnamespace algo {\n\n// Returns the smallest nonnegative integer\
    \ absent from values.\ntemplate <class T>\nint mex(const std::vector<T>& values)\
    \ {\n    static_assert(\n        std::is_integral_v<T> && sizeof(T) <= sizeof(std::uintmax_t),\n\
    \        \"mex requires standard integral values\"\n    );\n    assert(values.size()\
    \ <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n    const int\
    \ n = int(values.size());\n    std::vector<unsigned char> present(n, 0);\n   \
    \ for (T value : values) {\n        if constexpr (std::is_signed_v<T>) {\n   \
    \         if (value < 0) continue;\n        }\n        if (static_cast<std::uintmax_t>(value)\
    \ < static_cast<std::uintmax_t>(n)) {\n            present[int(value)] = 1;\n\
    \        }\n    }\n    int answer = 0;\n    while (answer < n && present[answer])\
    \ ++answer;\n    return answer;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_ALGO_SEQUENCE_MEX_HPP\n#define M1UNE_ALGO_SEQUENCE_MEX_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <limits>\n#include <type_traits>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n// Returns the smallest\
    \ nonnegative integer absent from values.\ntemplate <class T>\nint mex(const std::vector<T>&\
    \ values) {\n    static_assert(\n        std::is_integral_v<T> && sizeof(T) <=\
    \ sizeof(std::uintmax_t),\n        \"mex requires standard integral values\"\n\
    \    );\n    assert(values.size() <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n\
    \    const int n = int(values.size());\n    std::vector<unsigned char> present(n,\
    \ 0);\n    for (T value : values) {\n        if constexpr (std::is_signed_v<T>)\
    \ {\n            if (value < 0) continue;\n        }\n        if (static_cast<std::uintmax_t>(value)\
    \ < static_cast<std::uintmax_t>(n)) {\n            present[int(value)] = 1;\n\
    \        }\n    }\n    int answer = 0;\n    while (answer < n && present[answer])\
    \ ++answer;\n    return answer;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n#endif  // M1UNE_ALGO_SEQUENCE_MEX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/sequence/mex.hpp
  requiredBy:
  - algo/sequence/all.hpp
  - algo/all.hpp
  timestamp: '2026-10-06 02:15:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/bst/mex_multiset.test.cpp
documentation_of: algo/sequence/mex.hpp
layout: document
title: Mex
---

## Overview

`mex(values)` returns the smallest nonnegative integer absent from an integer
vector. For example, the mex of `0, 1, 1, 3` is `2`. The empty vector has mex `0`.

## Interface

| Exact signature | Description | Complexity |
| --- | --- | --- |
| `template <class T> int mex(const std::vector<T>& values)` | Returns the mex without modifying `values`. | $O(N)$ time and $O(N)$ auxiliary space |

`T` must be a standard integral type, signed or unsigned. The vector length `N`
must fit in `int`; this is checked by an assertion. Duplicates, negative values,
and values at least `N` do not affect the answer. The result is always in `[0, N]`.
The implementation uses a byte per candidate and does not sort the input.

For repeated queries with insertions and deletions, use
[`MexMultiset`](../../ds/bst/mex_multiset.md).

## Example

```cpp
#include "algo/sequence/mex.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {3, 0, 1, 1, -5, 1000000000000LL};
    std::cout << m1une::algo::mex(values) << '\n';  // 2
}
```
