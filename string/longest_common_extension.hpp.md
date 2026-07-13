---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
  _extendedRequiredBy:
  - icon: ':x:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/longest_common_extension.test.cpp
    title: verify/string/longest_common_extension.test.cpp
  - icon: ':x:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/longest_common_extension.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <string>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"string/suffix_array.hpp\"\n\n\n\n#line 6 \"string/suffix_array.hpp\"\
    \n#include <numeric>\n#line 8 \"string/suffix_array.hpp\"\n#include <type_traits>\n\
    #line 10 \"string/suffix_array.hpp\"\n\nnamespace m1une {\nnamespace string {\n\
    namespace detail {\n\ntemplate <class Sequence>\nstd::vector<int> suffix_array_impl(const\
    \ Sequence& sequence) {\n    int n = int(sequence.size());\n    if (n == 0) return\
    \ {};\n\n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(sequence[0])>>;\n\
    \    std::vector<Value> sorted(sequence.begin(), sequence.end());\n    std::sort(sorted.begin(),\
    \ sorted.end());\n    sorted.erase(std::unique(sorted.begin(), sorted.end()),\
    \ sorted.end());\n\n    int length = n + 1;\n    std::vector<int> order(length);\n\
    \    std::vector<int> rank(length);\n    std::vector<int> key(length);\n    key[n]\
    \ = 0;\n    for (int i = 0; i < n; i++) {\n        key[i] = int(std::lower_bound(sorted.begin(),\
    \ sorted.end(), sequence[i]) - sorted.begin()) + 1;\n    }\n\n    int alphabet\
    \ = int(sorted.size()) + 1;\n    std::vector<int> count(std::max(length, alphabet),\
    \ 0);\n    for (int value : key) count[value]++;\n    for (int i = 1; i < alphabet;\
    \ i++) count[i] += count[i - 1];\n    for (int i = length - 1; i >= 0; i--) order[--count[key[i]]]\
    \ = i;\n\n    int classes = 1;\n    rank[order[0]] = 0;\n    for (int i = 1; i\
    \ < length; i++) {\n        if (key[order[i - 1]] != key[order[i]]) classes++;\n\
    \        rank[order[i]] = classes - 1;\n    }\n\n    std::vector<int> shifted(length);\n\
    \    std::vector<int> next_rank(length);\n    for (long long half = 1; half <\
    \ length; half <<= 1) {\n        for (int i = 0; i < length; i++) {\n        \
    \    long long position = order[i] - half;\n            if (position < 0) position\
    \ += length;\n            shifted[i] = int(position);\n        }\n\n        count.assign(classes,\
    \ 0);\n        for (int position : shifted) count[rank[position]]++;\n       \
    \ for (int i = 1; i < classes; i++) count[i] += count[i - 1];\n        for (int\
    \ i = length - 1; i >= 0; i--) {\n            int position = shifted[i];\n   \
    \         order[--count[rank[position]]] = position;\n        }\n\n        int\
    \ next_classes = 1;\n        next_rank[order[0]] = 0;\n        for (int i = 1;\
    \ i < length; i++) {\n            int current = order[i];\n            int previous\
    \ = order[i - 1];\n            int current_second = int((current + half) % length);\n\
    \            int previous_second = int((previous + half) % length);\n        \
    \    if (\n                rank[current] != rank[previous] ||\n              \
    \  rank[current_second] != rank[previous_second]\n            ) {\n          \
    \      next_classes++;\n            }\n            next_rank[current] = next_classes\
    \ - 1;\n        }\n        rank.swap(next_rank);\n        classes = next_classes;\n\
    \        if (classes == length) break;\n    }\n\n    std::vector<int> suffixes(n);\n\
    \    for (int i = 0; i < n; i++) suffixes[i] = order[i + 1];\n    return suffixes;\n\
    }\n\n}  // namespace detail\n\ntemplate <class Sequence>\nstd::vector<int> suffix_array(const\
    \ Sequence& sequence) {\n    return detail::suffix_array_impl(sequence);\n}\n\n\
    inline std::vector<int> suffix_array(const std::string& text) {\n    std::vector<unsigned\
    \ char> values;\n    values.reserve(text.size());\n    for (unsigned char character\
    \ : text) values.push_back(character);\n    return detail::suffix_array_impl(values);\n\
    }\n\ntemplate <class Sequence>\nstd::vector<int> lcp_array(const Sequence& sequence,\
    \ const std::vector<int>& suffixes) {\n    int n = int(sequence.size());\n   \
    \ assert(int(suffixes.size()) == n);\n    if (n == 0) return {};\n\n    std::vector<int>\
    \ rank(n);\n    for (int i = 0; i < n; i++) {\n        assert(0 <= suffixes[i]\
    \ && suffixes[i] < n);\n        rank[suffixes[i]] = i;\n    }\n\n    std::vector<int>\
    \ lcp(n - 1);\n    int common = 0;\n    for (int i = 0; i < n; i++) {\n      \
    \  int position = rank[i];\n        if (position == n - 1) {\n            common\
    \ = 0;\n            continue;\n        }\n        int j = suffixes[position +\
    \ 1];\n        while (\n            i + common < n &&\n            j + common\
    \ < n &&\n            sequence[i + common] == sequence[j + common]\n        )\
    \ {\n            common++;\n        }\n        lcp[position] = common;\n     \
    \   if (common > 0) common--;\n    }\n    return lcp;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 11 \"string/longest_common_extension.hpp\"\n\n\
    namespace m1une {\nnamespace string {\n\ntemplate <class Sequence = std::string>\n\
    struct LongestCommonExtension {\n   private:\n    Sequence _sequence;\n    std::vector<int>\
    \ _suffix_array;\n    std::vector<int> _rank;\n    std::vector<int> _lcp;\n  \
    \  std::vector<int> _log;\n    std::vector<std::vector<int>> _table;\n\n    int\
    \ range_min(int left, int right) const {\n        assert(0 <= left && left < right\
    \ && right <= int(_lcp.size()));\n        int k = _log[right - left];\n      \
    \  return std::min(_table[k][left], _table[k][right - (1 << k)]);\n    }\n\n \
    \   void build() {\n        int n = int(_sequence.size());\n        _suffix_array\
    \ = m1une::string::suffix_array(_sequence);\n        _rank.assign(n, 0);\n   \
    \     for (int i = 0; i < n; i++) {\n            _rank[_suffix_array[i]] = i;\n\
    \        }\n\n        _lcp = m1une::string::lcp_array(_sequence, _suffix_array);\n\
    \        int m = int(_lcp.size());\n        _log.assign(m + 1, 0);\n        for\
    \ (int i = 2; i <= m; i++) {\n            _log[i] = _log[i >> 1] + 1;\n      \
    \  }\n\n        _table.clear();\n        if (m == 0) return;\n        _table.assign(_log[m]\
    \ + 1, std::vector<int>());\n        _table[0] = _lcp;\n        for (int k = 1;\
    \ k < int(_table.size()); k++) {\n            int width = 1 << k;\n          \
    \  int half = width >> 1;\n            _table[k].resize(m - width + 1);\n    \
    \        for (int i = 0; i + width <= m; i++) {\n                _table[k][i]\
    \ = std::min(_table[k - 1][i], _table[k - 1][i + half]);\n            }\n    \
    \    }\n    }\n\n   public:\n    LongestCommonExtension() = default;\n\n    explicit\
    \ LongestCommonExtension(const Sequence& sequence) : _sequence(sequence) {\n \
    \       build();\n    }\n\n    explicit LongestCommonExtension(Sequence&& sequence)\
    \ : _sequence(std::move(sequence)) {\n        build();\n    }\n\n    int size()\
    \ const {\n        return int(_sequence.size());\n    }\n\n    bool empty() const\
    \ {\n        return _sequence.empty();\n    }\n\n    const Sequence& sequence()\
    \ const {\n        return _sequence;\n    }\n\n    const std::vector<int>& suffix_array()\
    \ const {\n        return _suffix_array;\n    }\n\n    const std::vector<int>&\
    \ rank() const {\n        return _rank;\n    }\n\n    const std::vector<int>&\
    \ lcp_array() const {\n        return _lcp;\n    }\n\n    int longest_common_extension(int\
    \ i, int j) const {\n        int n = size();\n        assert(0 <= i && i <= n);\n\
    \        assert(0 <= j && j <= n);\n        if (i == j) return n - i;\n      \
    \  if (i == n || j == n) return 0;\n\n        int left = _rank[i];\n        int\
    \ right = _rank[j];\n        if (left > right) std::swap(left, right);\n     \
    \   return range_min(left, right);\n    }\n\n    int longest_common_extension(int\
    \ i, int j, int limit) const {\n        assert(0 <= limit);\n        return std::min(longest_common_extension(i,\
    \ j), limit);\n    }\n\n    int lcp(int i, int j) const {\n        return longest_common_extension(i,\
    \ j);\n    }\n\n    int operator()(int i, int j) const {\n        return longest_common_extension(i,\
    \ j);\n    }\n\n    int compare_suffix(int i, int j) const {\n        int n =\
    \ size();\n        assert(0 <= i && i <= n);\n        assert(0 <= j && j <= n);\n\
    \        if (i == j) return 0;\n        int common = longest_common_extension(i,\
    \ j);\n        if (i + common == n && j + common == n) return 0;\n        if (i\
    \ + common == n) return -1;\n        if (j + common == n) return 1;\n        return\
    \ _sequence[i + common] < _sequence[j + common] ? -1 : 1;\n    }\n\n    int compare(int\
    \ l1, int r1, int l2, int r2) const {\n        int n = size();\n        assert(0\
    \ <= l1 && l1 <= r1 && r1 <= n);\n        assert(0 <= l2 && l2 <= r2 && r2 <=\
    \ n);\n        int len1 = r1 - l1;\n        int len2 = r2 - l2;\n        int common\
    \ = longest_common_extension(l1, l2, std::min(len1, len2));\n        if (common\
    \ == len1 && common == len2) return 0;\n        if (common == len1) return -1;\n\
    \        if (common == len2) return 1;\n        return _sequence[l1 + common]\
    \ < _sequence[l2 + common] ? -1 : 1;\n    }\n};\n\n}  // namespace string\n} \
    \ // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_LONGEST_COMMON_EXTENSION_HPP\n#define M1UNE_STRING_LONGEST_COMMON_EXTENSION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <string>\n#include <utility>\n\
    #include <vector>\n\n#include \"suffix_array.hpp\"\n\nnamespace m1une {\nnamespace\
    \ string {\n\ntemplate <class Sequence = std::string>\nstruct LongestCommonExtension\
    \ {\n   private:\n    Sequence _sequence;\n    std::vector<int> _suffix_array;\n\
    \    std::vector<int> _rank;\n    std::vector<int> _lcp;\n    std::vector<int>\
    \ _log;\n    std::vector<std::vector<int>> _table;\n\n    int range_min(int left,\
    \ int right) const {\n        assert(0 <= left && left < right && right <= int(_lcp.size()));\n\
    \        int k = _log[right - left];\n        return std::min(_table[k][left],\
    \ _table[k][right - (1 << k)]);\n    }\n\n    void build() {\n        int n =\
    \ int(_sequence.size());\n        _suffix_array = m1une::string::suffix_array(_sequence);\n\
    \        _rank.assign(n, 0);\n        for (int i = 0; i < n; i++) {\n        \
    \    _rank[_suffix_array[i]] = i;\n        }\n\n        _lcp = m1une::string::lcp_array(_sequence,\
    \ _suffix_array);\n        int m = int(_lcp.size());\n        _log.assign(m +\
    \ 1, 0);\n        for (int i = 2; i <= m; i++) {\n            _log[i] = _log[i\
    \ >> 1] + 1;\n        }\n\n        _table.clear();\n        if (m == 0) return;\n\
    \        _table.assign(_log[m] + 1, std::vector<int>());\n        _table[0] =\
    \ _lcp;\n        for (int k = 1; k < int(_table.size()); k++) {\n            int\
    \ width = 1 << k;\n            int half = width >> 1;\n            _table[k].resize(m\
    \ - width + 1);\n            for (int i = 0; i + width <= m; i++) {\n        \
    \        _table[k][i] = std::min(_table[k - 1][i], _table[k - 1][i + half]);\n\
    \            }\n        }\n    }\n\n   public:\n    LongestCommonExtension() =\
    \ default;\n\n    explicit LongestCommonExtension(const Sequence& sequence) :\
    \ _sequence(sequence) {\n        build();\n    }\n\n    explicit LongestCommonExtension(Sequence&&\
    \ sequence) : _sequence(std::move(sequence)) {\n        build();\n    }\n\n  \
    \  int size() const {\n        return int(_sequence.size());\n    }\n\n    bool\
    \ empty() const {\n        return _sequence.empty();\n    }\n\n    const Sequence&\
    \ sequence() const {\n        return _sequence;\n    }\n\n    const std::vector<int>&\
    \ suffix_array() const {\n        return _suffix_array;\n    }\n\n    const std::vector<int>&\
    \ rank() const {\n        return _rank;\n    }\n\n    const std::vector<int>&\
    \ lcp_array() const {\n        return _lcp;\n    }\n\n    int longest_common_extension(int\
    \ i, int j) const {\n        int n = size();\n        assert(0 <= i && i <= n);\n\
    \        assert(0 <= j && j <= n);\n        if (i == j) return n - i;\n      \
    \  if (i == n || j == n) return 0;\n\n        int left = _rank[i];\n        int\
    \ right = _rank[j];\n        if (left > right) std::swap(left, right);\n     \
    \   return range_min(left, right);\n    }\n\n    int longest_common_extension(int\
    \ i, int j, int limit) const {\n        assert(0 <= limit);\n        return std::min(longest_common_extension(i,\
    \ j), limit);\n    }\n\n    int lcp(int i, int j) const {\n        return longest_common_extension(i,\
    \ j);\n    }\n\n    int operator()(int i, int j) const {\n        return longest_common_extension(i,\
    \ j);\n    }\n\n    int compare_suffix(int i, int j) const {\n        int n =\
    \ size();\n        assert(0 <= i && i <= n);\n        assert(0 <= j && j <= n);\n\
    \        if (i == j) return 0;\n        int common = longest_common_extension(i,\
    \ j);\n        if (i + common == n && j + common == n) return 0;\n        if (i\
    \ + common == n) return -1;\n        if (j + common == n) return 1;\n        return\
    \ _sequence[i + common] < _sequence[j + common] ? -1 : 1;\n    }\n\n    int compare(int\
    \ l1, int r1, int l2, int r2) const {\n        int n = size();\n        assert(0\
    \ <= l1 && l1 <= r1 && r1 <= n);\n        assert(0 <= l2 && l2 <= r2 && r2 <=\
    \ n);\n        int len1 = r1 - l1;\n        int len2 = r2 - l2;\n        int common\
    \ = longest_common_extension(l1, l2, std::min(len1, len2));\n        if (common\
    \ == len1 && common == len2) return 0;\n        if (common == len1) return -1;\n\
    \        if (common == len2) return 1;\n        return _sequence[l1 + common]\
    \ < _sequence[l2 + common] ? -1 : 1;\n    }\n};\n\n}  // namespace string\n} \
    \ // namespace m1une\n\n#endif  // M1UNE_STRING_LONGEST_COMMON_EXTENSION_HPP\n"
  dependsOn:
  - string/suffix_array.hpp
  isVerificationFile: false
  path: string/longest_common_extension.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-09 02:40:33+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/longest_common_extension.test.cpp
documentation_of: string/longest_common_extension.hpp
layout: document
title: Longest Common Extension
---

## Overview

`LongestCommonExtension` is a static structure for longest-common-extension
queries on one sequence. It returns the longest common prefix length of suffixes
starting at two positions, which is useful for substring comparison, runs,
repetitions, and suffix-array based string problems.

The implementation builds a suffix array, the adjacent LCP array, and a sparse
table over the LCP array. Queries are deterministic and do not use hashing.

`Sequence` must provide `size()`, `operator[]`, `begin()`, and `end()`.
Elements must be sortable for construction. The comparison helpers also require
element `<`.

## Methods

Let `N = size()`.

| Method | Description | Complexity |
| --- | --- | --- |
| `LongestCommonExtension()` | Creates an empty structure. | `O(1)` |
| `LongestCommonExtension(const Sequence& sequence)` | Copies `sequence` and builds the structure. | `O(N \log N)` |
| `LongestCommonExtension(Sequence&& sequence)` | Moves `sequence` and builds the structure. | `O(N \log N)` |
| `int size() const` | Returns `N`. | `O(1)` |
| `bool empty() const` | Returns whether `N == 0`. | `O(1)` |
| `const Sequence& sequence() const` | Returns the stored sequence. | `O(1)` |
| `const vector<int>& suffix_array() const` | Returns suffix starts in lexicographic order. | `O(1)` |
| `const vector<int>& rank() const` | Returns inverse suffix-array ranks. | `O(1)` |
| `const vector<int>& lcp_array() const` | Returns adjacent suffix LCP lengths. | `O(1)` |
| `int longest_common_extension(int i, int j) const` | Returns `LCP(sequence[i..], sequence[j..])`. | `O(1)` |
| `int longest_common_extension(int i, int j, int limit) const` | Returns `min(longest_common_extension(i, j), limit)`. | `O(1)` |
| `int lcp(int i, int j) const` | Alias of `longest_common_extension(i, j)`. | `O(1)` |
| `int operator()(int i, int j) const` | Alias of `longest_common_extension(i, j)`. | `O(1)` |
| `int compare_suffix(int i, int j) const` | Lexicographically compares suffixes. | `O(1)` |
| `int compare(int l1, int r1, int l2, int r2) const` | Lexicographically compares two half-open substrings. | `O(1)` |

`longest_common_extension(i, i)` returns `N - i`. Positions `i` and `j` may be
`N`, representing the empty suffix. Other indices must be in `[0, N]`.

`compare_suffix` and `compare` return `-1`, `0`, or `1`.

The memory usage is `O(N \log N)`.

## Example

```cpp
#include "string/longest_common_extension.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "banana";
    m1une::string::LongestCommonExtension<> extension(text);

    std::cout << extension.longest_common_extension(1, 3) << "\n"; // 3
    std::cout << extension.compare(1, 4, 3, 6) << "\n";            // 0
}
```
