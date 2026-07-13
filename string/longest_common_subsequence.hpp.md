---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/longest_common_subsequence.test.cpp
    title: verify/string/longest_common_subsequence.test.cpp
  - icon: ':x:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/longest_common_subsequence.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace string {\n\nstruct LongestCommonSubsequence\
    \ {\n    std::vector<std::pair<int, int>> matches;\n\n    int length() const {\n\
    \        return int(matches.size());\n    }\n\n    bool empty() const {\n    \
    \    return matches.empty();\n    }\n\n    std::vector<int> first_indices() const\
    \ {\n        std::vector<int> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)j;\n            result.push_back(i);\n\
    \        }\n        return result;\n    }\n\n    std::vector<int> second_indices()\
    \ const {\n        std::vector<int> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)i;\n            result.push_back(j);\n\
    \        }\n        return result;\n    }\n\n    template <class Sequence>\n \
    \   std::vector<std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>>\n    values_from_first(const Sequence& first) const {\n\
    \        using Value = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>;\n        std::vector<Value> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)j;\n            result.push_back(first[i]);\n\
    \        }\n        return result;\n    }\n\n    template <class Sequence>\n \
    \   std::vector<std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>>\n    values_from_second(const Sequence& second) const {\n\
    \        using Value = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>;\n        std::vector<Value> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)i;\n            result.push_back(second[j]);\n\
    \        }\n        return result;\n    }\n};\n\ntemplate <class FirstSequence,\
    \ class SecondSequence>\nint longest_common_subsequence_length(const FirstSequence&\
    \ first, const SecondSequence& second) {\n    int n = int(first.size());\n   \
    \ int m = int(second.size());\n    if (m <= n) {\n        std::vector<int> dp(m\
    \ + 1, 0);\n        for (int i = 0; i < n; i++) {\n            int diagonal =\
    \ 0;\n            for (int j = 0; j < m; j++) {\n                int up = dp[j\
    \ + 1];\n                if (first[i] == second[j]) {\n                    dp[j\
    \ + 1] = diagonal + 1;\n                } else {\n                    dp[j + 1]\
    \ = std::max(dp[j + 1], dp[j]);\n                }\n                diagonal =\
    \ up;\n            }\n        }\n        return dp[m];\n    } else {\n       \
    \ std::vector<int> dp(n + 1, 0);\n        for (int j = 0; j < m; j++) {\n    \
    \        int diagonal = 0;\n            for (int i = 0; i < n; i++) {\n      \
    \          int up = dp[i + 1];\n                if (first[i] == second[j]) {\n\
    \                    dp[i + 1] = diagonal + 1;\n                } else {\n   \
    \                 dp[i + 1] = std::max(dp[i + 1], dp[i]);\n                }\n\
    \                diagonal = up;\n            }\n        }\n        return dp[n];\n\
    \    }\n}\n\ntemplate <class FirstSequence, class SecondSequence>\nLongestCommonSubsequence\
    \ longest_common_subsequence(\n    const FirstSequence& first,\n    const SecondSequence&\
    \ second\n) {\n    int n = int(first.size());\n    int m = int(second.size());\n\
    \    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));\n  \
    \  for (int i = 0; i < n; i++) {\n        for (int j = 0; j < m; j++) {\n    \
    \        if (first[i] == second[j]) {\n                dp[i + 1][j + 1] = dp[i][j]\
    \ + 1;\n            } else {\n                dp[i + 1][j + 1] = std::max(dp[i][j\
    \ + 1], dp[i + 1][j]);\n            }\n        }\n    }\n\n    LongestCommonSubsequence\
    \ result;\n    result.matches.reserve(dp[n][m]);\n    int i = n;\n    int j =\
    \ m;\n    while (i > 0 && j > 0) {\n        if (first[i - 1] == second[j - 1])\
    \ {\n            result.matches.emplace_back(i - 1, j - 1);\n            i--;\n\
    \            j--;\n        } else if (dp[i - 1][j] >= dp[i][j - 1]) {\n      \
    \      i--;\n        } else {\n            j--;\n        }\n    }\n    std::reverse(result.matches.begin(),\
    \ result.matches.end());\n    return result;\n}\n\n}  // namespace string\n} \
    \ // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_LONGEST_COMMON_SUBSEQUENCE_HPP\n#define M1UNE_STRING_LONGEST_COMMON_SUBSEQUENCE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\nstruct\
    \ LongestCommonSubsequence {\n    std::vector<std::pair<int, int>> matches;\n\n\
    \    int length() const {\n        return int(matches.size());\n    }\n\n    bool\
    \ empty() const {\n        return matches.empty();\n    }\n\n    std::vector<int>\
    \ first_indices() const {\n        std::vector<int> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)j;\n            result.push_back(i);\n\
    \        }\n        return result;\n    }\n\n    std::vector<int> second_indices()\
    \ const {\n        std::vector<int> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)i;\n            result.push_back(j);\n\
    \        }\n        return result;\n    }\n\n    template <class Sequence>\n \
    \   std::vector<std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>>\n    values_from_first(const Sequence& first) const {\n\
    \        using Value = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>;\n        std::vector<Value> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)j;\n            result.push_back(first[i]);\n\
    \        }\n        return result;\n    }\n\n    template <class Sequence>\n \
    \   std::vector<std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>>\n    values_from_second(const Sequence& second) const {\n\
    \        using Value = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>;\n        std::vector<Value> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)i;\n            result.push_back(second[j]);\n\
    \        }\n        return result;\n    }\n};\n\ntemplate <class FirstSequence,\
    \ class SecondSequence>\nint longest_common_subsequence_length(const FirstSequence&\
    \ first, const SecondSequence& second) {\n    int n = int(first.size());\n   \
    \ int m = int(second.size());\n    if (m <= n) {\n        std::vector<int> dp(m\
    \ + 1, 0);\n        for (int i = 0; i < n; i++) {\n            int diagonal =\
    \ 0;\n            for (int j = 0; j < m; j++) {\n                int up = dp[j\
    \ + 1];\n                if (first[i] == second[j]) {\n                    dp[j\
    \ + 1] = diagonal + 1;\n                } else {\n                    dp[j + 1]\
    \ = std::max(dp[j + 1], dp[j]);\n                }\n                diagonal =\
    \ up;\n            }\n        }\n        return dp[m];\n    } else {\n       \
    \ std::vector<int> dp(n + 1, 0);\n        for (int j = 0; j < m; j++) {\n    \
    \        int diagonal = 0;\n            for (int i = 0; i < n; i++) {\n      \
    \          int up = dp[i + 1];\n                if (first[i] == second[j]) {\n\
    \                    dp[i + 1] = diagonal + 1;\n                } else {\n   \
    \                 dp[i + 1] = std::max(dp[i + 1], dp[i]);\n                }\n\
    \                diagonal = up;\n            }\n        }\n        return dp[n];\n\
    \    }\n}\n\ntemplate <class FirstSequence, class SecondSequence>\nLongestCommonSubsequence\
    \ longest_common_subsequence(\n    const FirstSequence& first,\n    const SecondSequence&\
    \ second\n) {\n    int n = int(first.size());\n    int m = int(second.size());\n\
    \    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));\n  \
    \  for (int i = 0; i < n; i++) {\n        for (int j = 0; j < m; j++) {\n    \
    \        if (first[i] == second[j]) {\n                dp[i + 1][j + 1] = dp[i][j]\
    \ + 1;\n            } else {\n                dp[i + 1][j + 1] = std::max(dp[i][j\
    \ + 1], dp[i + 1][j]);\n            }\n        }\n    }\n\n    LongestCommonSubsequence\
    \ result;\n    result.matches.reserve(dp[n][m]);\n    int i = n;\n    int j =\
    \ m;\n    while (i > 0 && j > 0) {\n        if (first[i - 1] == second[j - 1])\
    \ {\n            result.matches.emplace_back(i - 1, j - 1);\n            i--;\n\
    \            j--;\n        } else if (dp[i - 1][j] >= dp[i][j - 1]) {\n      \
    \      i--;\n        } else {\n            j--;\n        }\n    }\n    std::reverse(result.matches.begin(),\
    \ result.matches.end());\n    return result;\n}\n\n}  // namespace string\n} \
    \ // namespace m1une\n\n#endif  // M1UNE_STRING_LONGEST_COMMON_SUBSEQUENCE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/longest_common_subsequence.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-09 02:44:58+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/longest_common_subsequence.test.cpp
documentation_of: string/longest_common_subsequence.hpp
layout: document
title: Longest Common Subsequence
---

## Overview

`longest_common_subsequence(first, second)` finds one longest sequence that is
a subsequence of both inputs. The returned object stores matched index pairs,
so the values can be recovered from either input.

Use `longest_common_subsequence_length(first, second)` when only the length is
needed. It avoids storing the full DP table.

`FirstSequence` and `SecondSequence` must provide `size()` and `operator[]`.
The expressions `first[i] == second[j]` must be valid.

## Result

| Field or Method | Description | Complexity |
| --- | --- | --- |
| `vector<pair<int, int>> matches` | Matched index pairs in increasing order. | `O(1)` |
| `int length() const` | Returns the LCS length. | `O(1)` |
| `bool empty() const` | Returns whether the length is zero. | `O(1)` |
| `vector<int> first_indices() const` | Returns matched indices in the first sequence. | `O(L)` |
| `vector<int> second_indices() const` | Returns matched indices in the second sequence. | `O(L)` |
| `vector<T> values_from_first(first) const` | Returns the matched values from the first sequence. | `O(L)` |
| `vector<T> values_from_second(second) const` | Returns the matched values from the second sequence. | `O(L)` |

Here `L` is the LCS length. If several longest subsequences exist, any one of
them may be returned.

## Functions

Let `N = first.size()` and `M = second.size()`.

| Function | Description | Complexity |
| --- | --- | --- |
| `int longest_common_subsequence_length(const FirstSequence& first, const SecondSequence& second)` | Returns the LCS length. | `O(NM)` time, `O(min(N, M))` memory |
| `LongestCommonSubsequence longest_common_subsequence(const FirstSequence& first, const SecondSequence& second)` | Returns one LCS as matched index pairs. | `O(NM)` time and memory |

## Example

```cpp
#include "string/longest_common_subsequence.hpp"

#include <iostream>
#include <string>

int main() {
    std::string first = "abcbdab";
    std::string second = "bdcaba";
    auto result = m1une::string::longest_common_subsequence(first, second);

    std::cout << result.length() << "\n"; // 4
    for (char value : result.values_from_first(first)) {
        std::cout << value;
    }
    std::cout << "\n";
}
```
