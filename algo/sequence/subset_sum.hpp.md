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
    path: verify/algo/sequence/subset_sum.test.cpp
    title: verify/algo/sequence/subset_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/sequence/subset_sum.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace algo {\n\nnamespace internal {\n\ntemplate <typename T>\nstd::vector<T>\
    \ enumerate_sorted_subset_sums(\n    const std::vector<T>& values,\n    int left,\n\
    \    int right\n) {\n    std::vector<T> sums(1, T{});\n    std::vector<T> merged;\n\
    \n    for (int i = left; i < right; ++i) {\n        const std::size_t size = sums.size();\n\
    \        merged.clear();\n        merged.reserve(size * 2);\n\n        std::size_t\
    \ without = 0;\n        std::size_t with = 0;\n        while (without < size &&\
    \ with < size) {\n            const T with_current = sums[with] + values[i];\n\
    \            if (with_current < sums[without]) {\n                merged.push_back(with_current);\n\
    \                ++with;\n            } else {\n                merged.push_back(sums[without]);\n\
    \                ++without;\n            }\n        }\n        while (without\
    \ < size) {\n            merged.push_back(sums[without]);\n            ++without;\n\
    \        }\n        while (with < size) {\n            merged.push_back(sums[with]\
    \ + values[i]);\n            ++with;\n        }\n        sums.swap(merged);\n\
    \    }\n\n    return sums;\n}\n\n}  // namespace internal\n\n// Returns the sorted\
    \ subset sums of values[0, n / 2) and values[n / 2, n).\ntemplate <typename T>\n\
    std::pair<std::vector<T>, std::vector<T>> enumerate_half_subset_sums(\n    const\
    \ std::vector<T>& values\n) {\n    const int n = int(values.size());\n    const\
    \ int middle = n / 2;\n    return {\n        internal::enumerate_sorted_subset_sums(values,\
    \ 0, middle),\n        internal::enumerate_sorted_subset_sums(values, middle,\
    \ n)\n    };\n}\n\n// Returns the maximum subset sum not exceeding limit.\ntemplate\
    \ <typename T>\nT maximum_subset_sum(const std::vector<T>& values, const T& limit)\
    \ {\n    assert(!(limit < T{}));\n    auto [left_sums, right_sums] = enumerate_half_subset_sums(values);\n\
    \n    T answer{};\n    std::size_t right_count = right_sums.size();\n    for (const\
    \ T& left : left_sums) {\n        while (\n            right_count > 0 &&\n  \
    \          limit < left + right_sums[right_count - 1]\n        ) {\n         \
    \   --right_count;\n        }\n        if (right_count == 0) break;\n\n      \
    \  const T candidate = left + right_sums[right_count - 1];\n        if (answer\
    \ < candidate) answer = candidate;\n    }\n    return answer;\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_SEQUENCE_SUBSET_SUM_HPP\n#define M1UNE_ALGO_SEQUENCE_SUBSET_SUM_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace algo {\n\nnamespace internal {\n\ntemplate <typename\
    \ T>\nstd::vector<T> enumerate_sorted_subset_sums(\n    const std::vector<T>&\
    \ values,\n    int left,\n    int right\n) {\n    std::vector<T> sums(1, T{});\n\
    \    std::vector<T> merged;\n\n    for (int i = left; i < right; ++i) {\n    \
    \    const std::size_t size = sums.size();\n        merged.clear();\n        merged.reserve(size\
    \ * 2);\n\n        std::size_t without = 0;\n        std::size_t with = 0;\n \
    \       while (without < size && with < size) {\n            const T with_current\
    \ = sums[with] + values[i];\n            if (with_current < sums[without]) {\n\
    \                merged.push_back(with_current);\n                ++with;\n  \
    \          } else {\n                merged.push_back(sums[without]);\n      \
    \          ++without;\n            }\n        }\n        while (without < size)\
    \ {\n            merged.push_back(sums[without]);\n            ++without;\n  \
    \      }\n        while (with < size) {\n            merged.push_back(sums[with]\
    \ + values[i]);\n            ++with;\n        }\n        sums.swap(merged);\n\
    \    }\n\n    return sums;\n}\n\n}  // namespace internal\n\n// Returns the sorted\
    \ subset sums of values[0, n / 2) and values[n / 2, n).\ntemplate <typename T>\n\
    std::pair<std::vector<T>, std::vector<T>> enumerate_half_subset_sums(\n    const\
    \ std::vector<T>& values\n) {\n    const int n = int(values.size());\n    const\
    \ int middle = n / 2;\n    return {\n        internal::enumerate_sorted_subset_sums(values,\
    \ 0, middle),\n        internal::enumerate_sorted_subset_sums(values, middle,\
    \ n)\n    };\n}\n\n// Returns the maximum subset sum not exceeding limit.\ntemplate\
    \ <typename T>\nT maximum_subset_sum(const std::vector<T>& values, const T& limit)\
    \ {\n    assert(!(limit < T{}));\n    auto [left_sums, right_sums] = enumerate_half_subset_sums(values);\n\
    \n    T answer{};\n    std::size_t right_count = right_sums.size();\n    for (const\
    \ T& left : left_sums) {\n        while (\n            right_count > 0 &&\n  \
    \          limit < left + right_sums[right_count - 1]\n        ) {\n         \
    \   --right_count;\n        }\n        if (right_count == 0) break;\n\n      \
    \  const T candidate = left + right_sums[right_count - 1];\n        if (answer\
    \ < candidate) answer = candidate;\n    }\n    return answer;\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_SEQUENCE_SUBSET_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/sequence/subset_sum.hpp
  requiredBy:
  - algo/all.hpp
  - algo/sequence/all.hpp
  timestamp: '2026-07-07 21:49:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/sequence/subset_sum.test.cpp
documentation_of: algo/sequence/subset_sum.hpp
layout: document
title: Meet-in-the-Middle Subset Sum
---

## Overview

Finds the maximum sum of a subset that does not exceed a given limit. The
array is split in half, the subset sums of both halves are generated in sorted
order, and a two-pointer scan finds the best compatible pair.

The sorted half-sum lists are also exposed for other meet-in-the-middle
algorithms. Every subset sum of the original array can be written as
`left_sums[i] + right_sums[j]`.

## Template Parameters

* `T`: Value and sum type. `T{}` must be the additive identity. Values must
  support `operator+` and `operator<`, and addition by a fixed value must
  preserve ordering. Every subset sum must be representable by `T`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `std::pair<std::vector<T>, std::vector<T>> enumerate_half_subset_sums(const std::vector<T>& values)` | Returns the sorted subset sums of `values[0, N / 2)` and `values[N / 2, N)`. | $O(2^{N/2})$ time and space |
| `T maximum_subset_sum(const std::vector<T>& values, const T& limit)` | Returns the maximum subset sum not exceeding `limit`. Requires `T{} <= limit`. | $O(2^{N/2})$ time and space |

## Behavior

Each half-sum vector is sorted in ascending order, includes the empty-subset
sum `T{}`, and preserves equal sums produced by different subsets. The input
is not modified.

`maximum_subset_sum` includes the empty subset as a candidate, so it returns
`T{}` when no positive subset sum fits. `limit` must not be less than `T{}`.

Materializing all $2^N$ full-array subset sums would require $O(2^N)$ output.
Keeping the halves separate uses only $O(2^{N/2})$ time and memory.

## Example

```cpp
#include "algo/sequence/subset_sum.hpp"
#include <iostream>
#include <vector>

int main() {
    const std::vector<long long> values = {2, 3, 5, 7, 11};
    const long long limit = 17;

    std::cout << m1une::algo::maximum_subset_sum(values, limit) << '\n';

    const auto [left_sums, right_sums] =
        m1une::algo::enumerate_half_subset_sums(values);
}
```
