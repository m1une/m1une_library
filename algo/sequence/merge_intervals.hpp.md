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
    path: verify/algo/sequence/merge_intervals.test.cpp
    title: verify/algo/sequence/merge_intervals.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/sequence/merge_intervals.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace algo {\n\n// Returns the union of half-open intervals\
    \ as sorted, disjoint intervals.\ntemplate <typename T>\nstd::vector<std::pair<T,\
    \ T>> merge_intervals(\n    std::vector<std::pair<T, T>> intervals\n) {\n    for\
    \ (const auto& [left, right] : intervals) {\n        if (right < left) assert(false);\n\
    \    }\n\n    std::sort(\n        intervals.begin(),\n        intervals.end(),\n\
    \        [](const auto& lhs, const auto& rhs) {\n            if (lhs.first < rhs.first)\
    \ return true;\n            if (rhs.first < lhs.first) return false;\n       \
    \     return lhs.second < rhs.second;\n        }\n    );\n\n    std::size_t result_size\
    \ = 0;\n    for (std::size_t index = 0; index < intervals.size(); ++index) {\n\
    \        auto& [left, right] = intervals[index];\n        if (!(left < right))\
    \ continue;\n        if (result_size == 0 || intervals[result_size - 1].second\
    \ < left) {\n            if (result_size != index) {\n                intervals[result_size]\
    \ = std::move(intervals[index]);\n            }\n            ++result_size;\n\
    \        } else if (intervals[result_size - 1].second < right) {\n           \
    \ intervals[result_size - 1].second = std::move(right);\n        }\n    }\n  \
    \  intervals.erase(intervals.begin() + result_size, intervals.end());\n    return\
    \ intervals;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_SEQUENCE_MERGE_INTERVALS_HPP\n#define M1UNE_ALGO_SEQUENCE_MERGE_INTERVALS_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n// Returns\
    \ the union of half-open intervals as sorted, disjoint intervals.\ntemplate <typename\
    \ T>\nstd::vector<std::pair<T, T>> merge_intervals(\n    std::vector<std::pair<T,\
    \ T>> intervals\n) {\n    for (const auto& [left, right] : intervals) {\n    \
    \    if (right < left) assert(false);\n    }\n\n    std::sort(\n        intervals.begin(),\n\
    \        intervals.end(),\n        [](const auto& lhs, const auto& rhs) {\n  \
    \          if (lhs.first < rhs.first) return true;\n            if (rhs.first\
    \ < lhs.first) return false;\n            return lhs.second < rhs.second;\n  \
    \      }\n    );\n\n    std::size_t result_size = 0;\n    for (std::size_t index\
    \ = 0; index < intervals.size(); ++index) {\n        auto& [left, right] = intervals[index];\n\
    \        if (!(left < right)) continue;\n        if (result_size == 0 || intervals[result_size\
    \ - 1].second < left) {\n            if (result_size != index) {\n           \
    \     intervals[result_size] = std::move(intervals[index]);\n            }\n \
    \           ++result_size;\n        } else if (intervals[result_size - 1].second\
    \ < right) {\n            intervals[result_size - 1].second = std::move(right);\n\
    \        }\n    }\n    intervals.erase(intervals.begin() + result_size, intervals.end());\n\
    \    return intervals;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_ALGO_SEQUENCE_MERGE_INTERVALS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/sequence/merge_intervals.hpp
  requiredBy:
  - algo/all.hpp
  - algo/sequence/all.hpp
  timestamp: '2026-08-21 12:49:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/sequence/merge_intervals.test.cpp
documentation_of: algo/sequence/merge_intervals.hpp
layout: document
title: Merge Intervals
---

## Overview

Computes the union of half-open intervals. The result is sorted by left
endpoint, contains no empty intervals, and has a positive gap between every two
consecutive intervals. In particular, overlapping or touching intervals are
merged.

Every input interval must satisfy `left <= right`. Endpoints must be movable
and support a strict weak ordering through `operator<`; passing an lvalue vector
also requires them to be copyable.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `vector<pair<T, T>> merge_intervals(vector<pair<T, T>> intervals)` | Returns the union of the half-open intervals `[left, right)`. The argument is copied when an lvalue is passed and can be consumed with `std::move`. | $O(N \log N)$ time and $O(1)$ auxiliary space |

## Notes

- Empty intervals `[x, x)` are discarded.
- Touching intervals such as `[1, 3)` and `[3, 5)` become `[1, 5)`.
- A reversed interval violates the function precondition and triggers an
  assertion in debug builds.
- The input vector is not modified unless the caller explicitly passes it with
  `std::move`.

## Example

```cpp
#include "algo/sequence/merge_intervals.hpp"

#include <utility>
#include <vector>

int main() {
    std::vector<std::pair<int, int>> intervals;
    intervals.emplace_back(5, 8);
    intervals.emplace_back(1, 3);
    intervals.emplace_back(3, 6);
    intervals.emplace_back(9, 9);

    auto merged = m1une::algo::merge_intervals(intervals);
    // merged contains [1, 8).
}
```
