---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  - icon: ':warning:'
    path: algo/enumeration/all.hpp
    title: Enumeration Algorithms All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/algo/enumeration/segtree_range.test.cpp
    title: verify/algo/enumeration/segtree_range.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/enumeration/segtree_range.hpp\"\n\n\n\n#include <bit>\n\
    #include <cassert>\n#include <concepts>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n// Splits [left, right)\
    \ into maximal segment-tree ranges from left to right.\ntemplate <std::integral\
    \ Int>\nrequires(!std::same_as<std::remove_cv_t<Int>, bool>)\nstd::vector<std::pair<Int,\
    \ Int>> split_segtree_range(Int left, Int right) {\n    if constexpr (std::signed_integral<Int>)\
    \ assert(Int(0) <= left);\n    assert(left <= right);\n    if constexpr (std::signed_integral<Int>)\
    \ {\n        if (left < 0) return {};\n    }\n    if (right < left) return {};\n\
    \n    using UInt = std::make_unsigned_t<Int>;\n    UInt position = static_cast<UInt>(left);\n\
    \    const UInt end = static_cast<UInt>(right);\n    std::vector<std::pair<Int,\
    \ Int>> result;\n    if (position == end) return result;\n    result.reserve(2\
    \ * std::bit_width(end - position));\n\n    while (position < end) {\n       \
    \ UInt length = std::bit_floor(end - position);\n        if (position != 0) {\n\
    \            const UInt alignment = position & (~position + UInt(1));\n      \
    \      if (alignment < length) length = alignment;\n        }\n        const UInt\
    \ next = position + length;\n        result.emplace_back(\n            static_cast<Int>(position),\
    \ static_cast<Int>(next)\n        );\n        position = next;\n    }\n    return\
    \ result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_ENUMERATION_SEGTREE_RANGE_HPP\n#define M1UNE_ALGO_ENUMERATION_SEGTREE_RANGE_HPP\
    \ 1\n\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace algo {\n\
    \n// Splits [left, right) into maximal segment-tree ranges from left to right.\n\
    template <std::integral Int>\nrequires(!std::same_as<std::remove_cv_t<Int>, bool>)\n\
    std::vector<std::pair<Int, Int>> split_segtree_range(Int left, Int right) {\n\
    \    if constexpr (std::signed_integral<Int>) assert(Int(0) <= left);\n    assert(left\
    \ <= right);\n    if constexpr (std::signed_integral<Int>) {\n        if (left\
    \ < 0) return {};\n    }\n    if (right < left) return {};\n\n    using UInt =\
    \ std::make_unsigned_t<Int>;\n    UInt position = static_cast<UInt>(left);\n \
    \   const UInt end = static_cast<UInt>(right);\n    std::vector<std::pair<Int,\
    \ Int>> result;\n    if (position == end) return result;\n    result.reserve(2\
    \ * std::bit_width(end - position));\n\n    while (position < end) {\n       \
    \ UInt length = std::bit_floor(end - position);\n        if (position != 0) {\n\
    \            const UInt alignment = position & (~position + UInt(1));\n      \
    \      if (alignment < length) length = alignment;\n        }\n        const UInt\
    \ next = position + length;\n        result.emplace_back(\n            static_cast<Int>(position),\
    \ static_cast<Int>(next)\n        );\n        position = next;\n    }\n    return\
    \ result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_ENUMERATION_SEGTREE_RANGE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/enumeration/segtree_range.hpp
  requiredBy:
  - algo/enumeration/all.hpp
  - algo/all.hpp
  timestamp: '2026-07-14 01:43:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/enumeration/segtree_range.test.cpp
documentation_of: algo/enumeration/segtree_range.hpp
layout: document
title: Segment Tree Range Split
---

## Overview

`split_segtree_range` decomposes a half-open range into the maximal aligned
power-of-two ranges used by a segment tree. The result is ordered from left to
right, is disjoint, and has union exactly `[left, right)`.

For example, `[3, 13)` is split into `[3, 4)`, `[4, 8)`, `[8, 12)`, and
`[12, 13)`. These are precisely the maximal nodes contained in the query range
of a perfect segment tree whose leaf count is any power of two at least
`right`; the tree size does not need to be passed to the function.

## Function

```cpp
template <std::integral Int>
requires(!std::same_as<std::remove_cv_t<Int>, bool>)
std::vector<std::pair<Int, Int>> split_segtree_range(Int left, Int right);
```

`Int` may be any integral type except `bool`. Both endpoints must be
nonnegative and must satisfy `left <= right`.

| Function | Description | Complexity |
| --- | --- | --- |
| `split_segtree_range(left, right)` | Returns the maximal segment-tree ranges covering `[left, right)`. | $O(K)$ time and memory, where $K = O(\log(right - left + 1))$ is the number of returned ranges. |

Every returned `[a, b)` has positive power-of-two length and `a` is divisible
by `b - a`. No returned range can be replaced by its parent while remaining
inside `[left, right)`. An empty input range returns an empty vector.

The function does not mutate its arguments or any external state.

## Example

```cpp
#include "algo/enumeration/segtree_range.hpp"

#include <iostream>

int main() {
    for (auto [left, right] :
         m1une::algo::split_segtree_range(3, 13)) {
        std::cout << "[" << left << ", " << right << ")\n";
    }
}
```

Output:

```text
[3, 4)
[4, 8)
[8, 12)
[12, 13)
```
