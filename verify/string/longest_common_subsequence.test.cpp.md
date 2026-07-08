---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/longest_common_subsequence.hpp
    title: Longest Common Subsequence
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C
  bundledCode: "#line 1 \"verify/string/longest_common_subsequence.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C\"\
    \n\n#line 1 \"string/longest_common_subsequence.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace string {\n\nstruct LongestCommonSubsequence {\n\
    \    std::vector<std::pair<int, int>> matches;\n\n    int length() const {\n \
    \       return int(matches.size());\n    }\n\n    bool empty() const {\n     \
    \   return matches.empty();\n    }\n\n    std::vector<int> first_indices() const\
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
    \ // namespace m1une\n\n\n#line 4 \"verify/string/longest_common_subsequence.test.cpp\"\
    \n\n#line 7 \"verify/string/longest_common_subsequence.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#include <string>\n#line 11 \"verify/string/longest_common_subsequence.test.cpp\"\
    \n\nnamespace {\n\ntemplate <class FirstSequence, class SecondSequence>\nint independent_lcs_length(const\
    \ FirstSequence& first, const SecondSequence& second) {\n    int n = int(first.size());\n\
    \    int m = int(second.size());\n    std::vector<std::vector<int>> dp(n + 1,\
    \ std::vector<int>(m + 1, 0));\n    for (int i = n - 1; i >= 0; i--) {\n     \
    \   for (int j = m - 1; j >= 0; j--) {\n            if (first[i] == second[j])\
    \ {\n                dp[i][j] = dp[i + 1][j + 1] + 1;\n            } else {\n\
    \                dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]);\n          \
    \  }\n        }\n    }\n    return dp[0][0];\n}\n\ntemplate <class FirstSequence,\
    \ class SecondSequence>\nvoid check_result(const FirstSequence& first, const SecondSequence&\
    \ second) {\n    auto result = m1une::string::longest_common_subsequence(first,\
    \ second);\n    int expected = independent_lcs_length(first, second);\n    assert(result.length()\
    \ == expected);\n    assert(result.empty() == (expected == 0));\n    assert(\n\
    \        m1une::string::longest_common_subsequence_length(first, second) ==\n\
    \        expected\n    );\n\n    std::vector<int> first_indices = result.first_indices();\n\
    \    std::vector<int> second_indices = result.second_indices();\n    assert(int(first_indices.size())\
    \ == expected);\n    assert(int(second_indices.size()) == expected);\n\n    for\
    \ (int k = 0; k < expected; k++) {\n        int i = result.matches[k].first;\n\
    \        int j = result.matches[k].second;\n        assert(i == first_indices[k]);\n\
    \        assert(j == second_indices[k]);\n        assert(0 <= i && i < int(first.size()));\n\
    \        assert(0 <= j && j < int(second.size()));\n        assert(first[i] ==\
    \ second[j]);\n        if (k > 0) {\n            assert(result.matches[k - 1].first\
    \ < i);\n            assert(result.matches[k - 1].second < j);\n        }\n  \
    \  }\n}\n\nvoid test_fixed() {\n    check_result(std::string(), std::string());\n\
    \    check_result(std::string(\"abc\"), std::string());\n    check_result(std::string(),\
    \ std::string(\"abc\"));\n    check_result(std::string(\"abc\"), std::string(\"\
    def\"));\n    check_result(std::string(\"abcbdab\"), std::string(\"bdcaba\"));\n\
    \    check_result(std::string(\"aaaa\"), std::string(\"aa\"));\n\n    std::string\
    \ first = \"abcbdab\";\n    std::string second = \"bdcaba\";\n    auto result\
    \ = m1une::string::longest_common_subsequence(first, second);\n    assert(result.length()\
    \ == 4);\n    assert(result.values_from_first(first) == result.values_from_second(second));\n\
    \n    std::vector<int> first_values;\n    first_values.push_back(1);\n    first_values.push_back(3);\n\
    \    first_values.push_back(2);\n    first_values.push_back(4);\n    first_values.push_back(3);\n\
    \    std::vector<int> second_values;\n    second_values.push_back(3);\n    second_values.push_back(1);\n\
    \    second_values.push_back(2);\n    second_values.push_back(3);\n    check_result(first_values,\
    \ second_values);\n    auto vector_result = m1une::string::longest_common_subsequence(first_values,\
    \ second_values);\n    assert(vector_result.values_from_first(first_values) ==\
    \ vector_result.values_from_second(second_values));\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260709;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 2000; trial++) {\n        int n = int(random()\
    \ % 30);\n        int m = int(random() % 30);\n        std::string first(n, 'a');\n\
    \        std::string second(m, 'a');\n        for (char& character : first) character\
    \ = char('a' + random() % 5);\n        for (char& character : second) character\
    \ = char('a' + random() % 5);\n        check_result(first, second);\n\n      \
    \  std::vector<int> first_values(n);\n        std::vector<int> second_values(m);\n\
    \        for (int& value : first_values) value = int(random() % 7) - 3;\n    \
    \    for (int& value : second_values) value = int(random() % 7) - 3;\n       \
    \ check_result(first_values, second_values);\n    }\n}\n\n}  // namespace\n\n\
    int main() {\n    test_fixed();\n    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int q;\n    std::cin >> q;\n    while (q--)\
    \ {\n        std::string first, second;\n        std::cin >> first >> second;\n\
    \        std::cout << m1une::string::longest_common_subsequence_length(first,\
    \ second) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C\"\
    \n\n#include \"../../string/longest_common_subsequence.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <string>\n\
    #include <vector>\n\nnamespace {\n\ntemplate <class FirstSequence, class SecondSequence>\n\
    int independent_lcs_length(const FirstSequence& first, const SecondSequence& second)\
    \ {\n    int n = int(first.size());\n    int m = int(second.size());\n    std::vector<std::vector<int>>\
    \ dp(n + 1, std::vector<int>(m + 1, 0));\n    for (int i = n - 1; i >= 0; i--)\
    \ {\n        for (int j = m - 1; j >= 0; j--) {\n            if (first[i] == second[j])\
    \ {\n                dp[i][j] = dp[i + 1][j + 1] + 1;\n            } else {\n\
    \                dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]);\n          \
    \  }\n        }\n    }\n    return dp[0][0];\n}\n\ntemplate <class FirstSequence,\
    \ class SecondSequence>\nvoid check_result(const FirstSequence& first, const SecondSequence&\
    \ second) {\n    auto result = m1une::string::longest_common_subsequence(first,\
    \ second);\n    int expected = independent_lcs_length(first, second);\n    assert(result.length()\
    \ == expected);\n    assert(result.empty() == (expected == 0));\n    assert(\n\
    \        m1une::string::longest_common_subsequence_length(first, second) ==\n\
    \        expected\n    );\n\n    std::vector<int> first_indices = result.first_indices();\n\
    \    std::vector<int> second_indices = result.second_indices();\n    assert(int(first_indices.size())\
    \ == expected);\n    assert(int(second_indices.size()) == expected);\n\n    for\
    \ (int k = 0; k < expected; k++) {\n        int i = result.matches[k].first;\n\
    \        int j = result.matches[k].second;\n        assert(i == first_indices[k]);\n\
    \        assert(j == second_indices[k]);\n        assert(0 <= i && i < int(first.size()));\n\
    \        assert(0 <= j && j < int(second.size()));\n        assert(first[i] ==\
    \ second[j]);\n        if (k > 0) {\n            assert(result.matches[k - 1].first\
    \ < i);\n            assert(result.matches[k - 1].second < j);\n        }\n  \
    \  }\n}\n\nvoid test_fixed() {\n    check_result(std::string(), std::string());\n\
    \    check_result(std::string(\"abc\"), std::string());\n    check_result(std::string(),\
    \ std::string(\"abc\"));\n    check_result(std::string(\"abc\"), std::string(\"\
    def\"));\n    check_result(std::string(\"abcbdab\"), std::string(\"bdcaba\"));\n\
    \    check_result(std::string(\"aaaa\"), std::string(\"aa\"));\n\n    std::string\
    \ first = \"abcbdab\";\n    std::string second = \"bdcaba\";\n    auto result\
    \ = m1une::string::longest_common_subsequence(first, second);\n    assert(result.length()\
    \ == 4);\n    assert(result.values_from_first(first) == result.values_from_second(second));\n\
    \n    std::vector<int> first_values;\n    first_values.push_back(1);\n    first_values.push_back(3);\n\
    \    first_values.push_back(2);\n    first_values.push_back(4);\n    first_values.push_back(3);\n\
    \    std::vector<int> second_values;\n    second_values.push_back(3);\n    second_values.push_back(1);\n\
    \    second_values.push_back(2);\n    second_values.push_back(3);\n    check_result(first_values,\
    \ second_values);\n    auto vector_result = m1une::string::longest_common_subsequence(first_values,\
    \ second_values);\n    assert(vector_result.values_from_first(first_values) ==\
    \ vector_result.values_from_second(second_values));\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260709;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 2000; trial++) {\n        int n = int(random()\
    \ % 30);\n        int m = int(random() % 30);\n        std::string first(n, 'a');\n\
    \        std::string second(m, 'a');\n        for (char& character : first) character\
    \ = char('a' + random() % 5);\n        for (char& character : second) character\
    \ = char('a' + random() % 5);\n        check_result(first, second);\n\n      \
    \  std::vector<int> first_values(n);\n        std::vector<int> second_values(m);\n\
    \        for (int& value : first_values) value = int(random() % 7) - 3;\n    \
    \    for (int& value : second_values) value = int(random() % 7) - 3;\n       \
    \ check_result(first_values, second_values);\n    }\n}\n\n}  // namespace\n\n\
    int main() {\n    test_fixed();\n    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int q;\n    std::cin >> q;\n    while (q--)\
    \ {\n        std::string first, second;\n        std::cin >> first >> second;\n\
    \        std::cout << m1une::string::longest_common_subsequence_length(first,\
    \ second) << '\\n';\n    }\n}\n"
  dependsOn:
  - string/longest_common_subsequence.hpp
  isVerificationFile: true
  path: verify/string/longest_common_subsequence.test.cpp
  requiredBy: []
  timestamp: '2026-07-09 02:44:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/longest_common_subsequence.test.cpp
layout: document
redirect_from:
- /verify/verify/string/longest_common_subsequence.test.cpp
- /verify/verify/string/longest_common_subsequence.test.cpp.html
title: verify/string/longest_common_subsequence.test.cpp
---
