---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/sequence/inversion_count.hpp
    title: Inversion Count
  - icon: ':heavy_check_mark:'
    path: algo/sequence/lis.hpp
    title: Longest Increasing Subsequence (LIS)
  - icon: ':heavy_check_mark:'
    path: algo/sequence/number_of_subsequences.hpp
    title: Number of Subsequences
  - icon: ':heavy_check_mark:'
    path: algo/sequence/run_length_encoding.hpp
    title: Run Length Encoding
  - icon: ':heavy_check_mark:'
    path: algo/sequence/subset_sum.hpp
    title: Meet-in-the-Middle Subset Sum
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/sequence/all.hpp\"\n\n\n\n#line 1 \"algo/sequence/inversion_count.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n// Returns\
    \ the number of pairs (i, j) with i < j and a[i] > a[j].\n// The vector is taken\
    \ by value because merge sort rearranges it.\ntemplate <typename T>\nlong long\
    \ inversion_count(std::vector<T> a) {\n    const int n = int(a.size());\n    std::vector<T>\
    \ temp = a;\n\n    auto merge_sort = [&](auto& self, int l, int r) -> long long\
    \ {\n        if (r - l <= 1) return 0;\n\n        const int m = l + (r - l) /\
    \ 2;\n        long long inv = self(self, l, m) + self(self, m, r);\n\n       \
    \ int i = l;\n        int j = m;\n        int k = l;\n        while (i < m &&\
    \ j < r) {\n            if (!(a[j] < a[i])) {\n                temp[k++] = a[i++];\n\
    \            } else {\n                temp[k++] = a[j++];\n                inv\
    \ += m - i;\n            }\n        }\n\n        while (i < m) temp[k++] = a[i++];\n\
    \        while (j < r) temp[k++] = a[j++];\n\n        for (int p = l; p < r; ++p)\
    \ {\n            a[p] = temp[p];\n        }\n\n        return inv;\n    };\n\n\
    \    return merge_sort(merge_sort, 0, n);\n}\n\n}  // namespace algo\n}  // namespace\
    \ m1une\n\n\n#line 1 \"algo/sequence/lis.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <iterator>\n#line 7 \"algo/sequence/lis.hpp\"\n\nnamespace m1une {\nnamespace\
    \ algo {\n\n// Returns the zero-based indices of a longest increasing subsequence.\n\
    // If `strict` is false, equal adjacent values are also allowed.\ntemplate <typename\
    \ T>\nstd::vector<int> lis(const std::vector<T>& a, bool strict = true) {\n  \
    \  const int n = int(a.size());\n    std::vector<T> tails;\n    std::vector<int>\
    \ tail_positions;\n    std::vector<int> predecessor(n, -1);\n    tails.reserve(n);\n\
    \    tail_positions.reserve(n);\n\n    for (int i = 0; i < n; ++i) {\n       \
    \ auto it = strict ? std::lower_bound(tails.begin(), tails.end(), a[i])\n    \
    \                     : std::upper_bound(tails.begin(), tails.end(), a[i]);\n\
    \        const int length = int(std::distance(tails.begin(), it));\n\n       \
    \ if (it == tails.end()) {\n            tails.push_back(a[i]);\n            tail_positions.push_back(i);\n\
    \        } else {\n            *it = a[i];\n            tail_positions[length]\
    \ = i;\n        }\n\n        if (length > 0) {\n            predecessor[i] = tail_positions[length\
    \ - 1];\n        }\n    }\n\n    if (tail_positions.empty()) return {};\n\n  \
    \  std::vector<int> result;\n    result.reserve(tail_positions.size());\n    int\
    \ current = tail_positions.back();\n    while (current != -1) {\n        result.push_back(current);\n\
    \        current = predecessor[current];\n    }\n    std::reverse(result.begin(),\
    \ result.end());\n    return result;\n}\n\n}  // namespace algo\n}  // namespace\
    \ m1une\n\n\n#line 1 \"algo/sequence/number_of_subsequences.hpp\"\n\n\n\n#line\
    \ 6 \"algo/sequence/number_of_subsequences.hpp\"\n\nnamespace m1une {\nnamespace\
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
    }  // namespace algo\n}  // namespace m1une\n\n\n#line 1 \"algo/sequence/run_length_encoding.hpp\"\
    \n\n\n\n#line 5 \"algo/sequence/run_length_encoding.hpp\"\n#include <utility>\n\
    #line 7 \"algo/sequence/run_length_encoding.hpp\"\n\nnamespace m1une {\nnamespace\
    \ algo {\n\ntemplate <typename Container>\nauto run_length_encoding(const Container&\
    \ values) {\n    using T = typename Container::value_type;\n    std::vector<std::pair<T,\
    \ long long>> result;\n\n    auto it = std::begin(values);\n    auto last = std::end(values);\n\
    \    if (it == last) {\n        return result;\n    }\n\n    T current = *it;\n\
    \    long long count = 0;\n    for (; it != last; ++it) {\n        if (*it ==\
    \ current) {\n            ++count;\n        } else {\n            result.emplace_back(current,\
    \ count);\n            current = *it;\n            count = 1;\n        }\n   \
    \ }\n    result.emplace_back(current, count);\n    return result;\n}\n\n}  //\
    \ namespace algo\n}  // namespace m1une\n\n\n#line 1 \"algo/sequence/subset_sum.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#line 8 \"algo/sequence/subset_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\nnamespace internal {\n\ntemplate <typename\
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
    \ algo\n}  // namespace m1une\n\n\n#line 9 \"algo/sequence/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_SEQUENCE_ALL_HPP

    #define M1UNE_ALGO_SEQUENCE_ALL_HPP 1


    #include "inversion_count.hpp"

    #include "lis.hpp"

    #include "number_of_subsequences.hpp"

    #include "run_length_encoding.hpp"

    #include "subset_sum.hpp"


    #endif  // M1UNE_ALGO_SEQUENCE_ALL_HPP

    '
  dependsOn:
  - algo/sequence/inversion_count.hpp
  - algo/sequence/lis.hpp
  - algo/sequence/number_of_subsequences.hpp
  - algo/sequence/run_length_encoding.hpp
  - algo/sequence/subset_sum.hpp
  isVerificationFile: false
  path: algo/sequence/all.hpp
  requiredBy:
  - algo/all.hpp
  timestamp: '2026-07-10 18:48:41+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algo/sequence/all.hpp
layout: document
title: Sequence Algorithms All
---

## Overview

`algo/sequence/all.hpp` includes one-shot algorithms over arrays and sequences.
The public namespace is `m1une::algo`.

## Included Headers

| Header | Contents |
| --- | --- |
| `algo/sequence/lis.hpp` | Longest increasing subsequence indices. |
| `algo/sequence/inversion_count.hpp` | Inversion count by merge sort. |
| `algo/sequence/number_of_subsequences.hpp` | Number of distinct nonempty subsequences. |
| `algo/sequence/run_length_encoding.hpp` | Run-length encoding for consecutive equal values. |
| `algo/sequence/subset_sum.hpp` | Meet-in-the-middle subset-sum helpers. |
