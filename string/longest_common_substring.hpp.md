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
    path: verify/string/longest_common_substring.test.cpp
    title: verify/string/longest_common_substring.test.cpp
  - icon: ':x:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/longest_common_substring.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"string/suffix_array.hpp\"\n\n\n\n#line 6 \"string/suffix_array.hpp\"\
    \n#include <numeric>\n#include <string>\n#line 10 \"string/suffix_array.hpp\"\n\
    \nnamespace m1une {\nnamespace string {\nnamespace detail {\n\ntemplate <class\
    \ Sequence>\nstd::vector<int> suffix_array_impl(const Sequence& sequence) {\n\
    \    int n = int(sequence.size());\n    if (n == 0) return {};\n\n    using Value\
    \ = std::remove_cv_t<std::remove_reference_t<decltype(sequence[0])>>;\n    std::vector<Value>\
    \ sorted(sequence.begin(), sequence.end());\n    std::sort(sorted.begin(), sorted.end());\n\
    \    sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());\n\n\
    \    int length = n + 1;\n    std::vector<int> order(length);\n    std::vector<int>\
    \ rank(length);\n    std::vector<int> key(length);\n    key[n] = 0;\n    for (int\
    \ i = 0; i < n; i++) {\n        key[i] = int(std::lower_bound(sorted.begin(),\
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
    }  // namespace m1une\n\n\n#line 11 \"string/longest_common_substring.hpp\"\n\n\
    namespace m1une {\nnamespace string {\n\nstruct LongestCommonSubstring {\n   \
    \ int first_left = 0;\n    int first_right = 0;\n    int second_left = 0;\n  \
    \  int second_right = 0;\n\n    int length() const {\n        assert(first_right\
    \ - first_left == second_right - second_left);\n        return first_right - first_left;\n\
    \    }\n\n    bool empty() const {\n        return length() == 0;\n    }\n\n \
    \   std::pair<int, int> first_interval() const {\n        return {first_left,\
    \ first_right};\n    }\n\n    std::pair<int, int> second_interval() const {\n\
    \        return {second_left, second_right};\n    }\n};\n\nnamespace detail {\n\
    \ntemplate <class Sequence>\nstd::vector<int> compressed_join_with_separator(const\
    \ Sequence& first, const Sequence& second) {\n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(first[0])>>;\n\
    \n    std::vector<Value> values;\n    values.reserve(first.size() + second.size());\n\
    \    for (const auto& value : first) values.push_back(value);\n    for (const\
    \ auto& value : second) values.push_back(value);\n    std::sort(values.begin(),\
    \ values.end());\n    values.erase(std::unique(values.begin(), values.end()),\
    \ values.end());\n\n    std::vector<int> joined;\n    joined.reserve(first.size()\
    \ + second.size() + 1);\n    for (const auto& value : first) {\n        joined.push_back(int(std::lower_bound(values.begin(),\
    \ values.end(), value) - values.begin()) + 2);\n    }\n    joined.push_back(1);\n\
    \    for (const auto& value : second) {\n        joined.push_back(int(std::lower_bound(values.begin(),\
    \ values.end(), value) - values.begin()) + 2);\n    }\n    return joined;\n}\n\
    \n}  // namespace detail\n\ntemplate <class Sequence>\nLongestCommonSubstring\
    \ longest_common_substring(const Sequence& first, const Sequence& second) {\n\
    \    int n = int(first.size());\n    int m = int(second.size());\n    std::vector<int>\
    \ joined = detail::compressed_join_with_separator(first, second);\n    std::vector<int>\
    \ suffixes = suffix_array(joined);\n    std::vector<int> lcp = lcp_array(joined,\
    \ suffixes);\n\n    LongestCommonSubstring result;\n    for (int i = 0; i + 1\
    \ < int(suffixes.size()); i++) {\n        int a = suffixes[i];\n        int b\
    \ = suffixes[i + 1];\n        if (a == n || b == n) continue;\n\n        bool\
    \ a_first = a < n;\n        bool b_first = b < n;\n        if (a_first == b_first)\
    \ continue;\n\n        int first_left = a_first ? a : b;\n        int second_left\
    \ = a_first ? b - n - 1 : a - n - 1;\n        int length = lcp[i];\n        length\
    \ = std::min(length, n - first_left);\n        length = std::min(length, m - second_left);\n\
    \        if (length > result.length()) {\n            result.first_left = first_left;\n\
    \            result.first_right = first_left + length;\n            result.second_left\
    \ = second_left;\n            result.second_right = second_left + length;\n  \
    \      }\n    }\n    return result;\n}\n\n}  // namespace string\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_LONGEST_COMMON_SUBSTRING_HPP\n#define M1UNE_STRING_LONGEST_COMMON_SUBSTRING_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"suffix_array.hpp\"\n\nnamespace m1une\
    \ {\nnamespace string {\n\nstruct LongestCommonSubstring {\n    int first_left\
    \ = 0;\n    int first_right = 0;\n    int second_left = 0;\n    int second_right\
    \ = 0;\n\n    int length() const {\n        assert(first_right - first_left ==\
    \ second_right - second_left);\n        return first_right - first_left;\n   \
    \ }\n\n    bool empty() const {\n        return length() == 0;\n    }\n\n    std::pair<int,\
    \ int> first_interval() const {\n        return {first_left, first_right};\n \
    \   }\n\n    std::pair<int, int> second_interval() const {\n        return {second_left,\
    \ second_right};\n    }\n};\n\nnamespace detail {\n\ntemplate <class Sequence>\n\
    std::vector<int> compressed_join_with_separator(const Sequence& first, const Sequence&\
    \ second) {\n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(first[0])>>;\n\
    \n    std::vector<Value> values;\n    values.reserve(first.size() + second.size());\n\
    \    for (const auto& value : first) values.push_back(value);\n    for (const\
    \ auto& value : second) values.push_back(value);\n    std::sort(values.begin(),\
    \ values.end());\n    values.erase(std::unique(values.begin(), values.end()),\
    \ values.end());\n\n    std::vector<int> joined;\n    joined.reserve(first.size()\
    \ + second.size() + 1);\n    for (const auto& value : first) {\n        joined.push_back(int(std::lower_bound(values.begin(),\
    \ values.end(), value) - values.begin()) + 2);\n    }\n    joined.push_back(1);\n\
    \    for (const auto& value : second) {\n        joined.push_back(int(std::lower_bound(values.begin(),\
    \ values.end(), value) - values.begin()) + 2);\n    }\n    return joined;\n}\n\
    \n}  // namespace detail\n\ntemplate <class Sequence>\nLongestCommonSubstring\
    \ longest_common_substring(const Sequence& first, const Sequence& second) {\n\
    \    int n = int(first.size());\n    int m = int(second.size());\n    std::vector<int>\
    \ joined = detail::compressed_join_with_separator(first, second);\n    std::vector<int>\
    \ suffixes = suffix_array(joined);\n    std::vector<int> lcp = lcp_array(joined,\
    \ suffixes);\n\n    LongestCommonSubstring result;\n    for (int i = 0; i + 1\
    \ < int(suffixes.size()); i++) {\n        int a = suffixes[i];\n        int b\
    \ = suffixes[i + 1];\n        if (a == n || b == n) continue;\n\n        bool\
    \ a_first = a < n;\n        bool b_first = b < n;\n        if (a_first == b_first)\
    \ continue;\n\n        int first_left = a_first ? a : b;\n        int second_left\
    \ = a_first ? b - n - 1 : a - n - 1;\n        int length = lcp[i];\n        length\
    \ = std::min(length, n - first_left);\n        length = std::min(length, m - second_left);\n\
    \        if (length > result.length()) {\n            result.first_left = first_left;\n\
    \            result.first_right = first_left + length;\n            result.second_left\
    \ = second_left;\n            result.second_right = second_left + length;\n  \
    \      }\n    }\n    return result;\n}\n\n}  // namespace string\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_STRING_LONGEST_COMMON_SUBSTRING_HPP\n"
  dependsOn:
  - string/suffix_array.hpp
  isVerificationFile: false
  path: string/longest_common_substring.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-09 02:40:33+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/longest_common_substring.test.cpp
documentation_of: string/longest_common_substring.hpp
layout: document
title: Longest Common Substring
---

## Overview

`longest_common_substring(first, second)` finds one longest sequence that occurs
as a contiguous substring of both inputs. It returns the matching half-open
interval in each input.

The implementation builds a suffix array and adjacent LCP array over the two
inputs joined by a unique separator. Input symbols are coordinate-compressed, so
the separator cannot collide with a real symbol.

`Sequence` must provide `size()`, `operator[]`, `begin()`, and `end()`.
Elements must be sortable and equality-comparable.

## Result

| Field or Method | Description | Complexity |
| --- | --- | --- |
| `int first_left`, `int first_right` | Half-open interval in the first sequence. | `O(1)` |
| `int second_left`, `int second_right` | Half-open interval in the second sequence. | `O(1)` |
| `int length() const` | Returns the common substring length. | `O(1)` |
| `bool empty() const` | Returns whether the length is zero. | `O(1)` |
| `pair<int, int> first_interval() const` | Returns `{first_left, first_right}`. | `O(1)` |
| `pair<int, int> second_interval() const` | Returns `{second_left, second_right}`. | `O(1)` |

If there is no common nonempty substring, all endpoints are zero. When several
maximum substrings exist, any one of them may be returned.

## Function

| Function | Description | Complexity |
| --- | --- | --- |
| `LongestCommonSubstring longest_common_substring(const Sequence& first, const Sequence& second)` | Finds one longest common substring. | `O((N + M) \log(N + M))` |

The memory usage is `O(N + M)`.

## Example

```cpp
#include "string/longest_common_substring.hpp"

#include <iostream>
#include <string>

int main() {
    std::string first = "xabxac";
    std::string second = "abcabxabcd";
    auto result = m1une::string::longest_common_substring(first, second);

    std::cout << result.first_left << " " << result.first_right << "\n";
    std::cout << result.second_left << " " << result.second_right << "\n";
}
```
