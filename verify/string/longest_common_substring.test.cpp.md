---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: string/longest_common_substring.hpp
    title: Longest Common Substring
  - icon: ':question:'
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/longest_common_substring
    links:
    - https://judge.yosupo.jp/problem/longest_common_substring
  bundledCode: "#line 1 \"verify/string/longest_common_substring.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/longest_common_substring\"\n\n#line\
    \ 1 \"string/longest_common_substring.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\n\
    #line 1 \"string/suffix_array.hpp\"\n\n\n\n#line 6 \"string/suffix_array.hpp\"\
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
    \ m1une\n\n\n#line 4 \"verify/string/longest_common_substring.test.cpp\"\n\n#line\
    \ 7 \"verify/string/longest_common_substring.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#line 11 \"verify/string/longest_common_substring.test.cpp\"\
    \n\nnamespace {\n\ntemplate <class Sequence>\nbool equal_substring(\n    const\
    \ Sequence& first,\n    int first_left,\n    const Sequence& second,\n    int\
    \ second_left,\n    int length\n) {\n    for (int i = 0; i < length; i++) {\n\
    \        if (first[first_left + i] != second[second_left + i]) return false;\n\
    \    }\n    return true;\n}\n\ntemplate <class Sequence>\nint naive_length(const\
    \ Sequence& first, const Sequence& second) {\n    int n = int(first.size());\n\
    \    int m = int(second.size());\n    int result = 0;\n    for (int i = 0; i <\
    \ n; i++) {\n        for (int j = 0; j < m; j++) {\n            int length = 0;\n\
    \            while (\n                i + length < n &&\n                j + length\
    \ < m &&\n                first[i + length] == second[j + length]\n          \
    \  ) {\n                length++;\n            }\n            result = std::max(result,\
    \ length);\n        }\n    }\n    return result;\n}\n\ntemplate <class Sequence>\n\
    void check_result(const Sequence& first, const Sequence& second) {\n    auto result\
    \ = m1une::string::longest_common_substring(first, second);\n    int n = int(first.size());\n\
    \    int m = int(second.size());\n    int length = result.length();\n    assert(0\
    \ <= result.first_left && result.first_left <= result.first_right && result.first_right\
    \ <= n);\n    assert(0 <= result.second_left && result.second_left <= result.second_right\
    \ && result.second_right <= m);\n    assert(result.second_right - result.second_left\
    \ == length);\n    assert(equal_substring(first, result.first_left, second, result.second_left,\
    \ length));\n    assert(length == naive_length(first, second));\n    if (length\
    \ == 0) {\n        assert(result.first_left == 0);\n        assert(result.first_right\
    \ == 0);\n        assert(result.second_left == 0);\n        assert(result.second_right\
    \ == 0);\n        assert(result.empty());\n    }\n}\n\nvoid test_fixed() {\n \
    \   check_result(std::string(), std::string());\n    check_result(std::string(\"\
    abc\"), std::string());\n    check_result(std::string(), std::string(\"abc\"));\n\
    \    check_result(std::string(\"abc\"), std::string(\"def\"));\n    check_result(std::string(\"\
    xabxac\"), std::string(\"abcabxabcd\"));\n    check_result(std::string(\"banana\"\
    ), std::string(\"ananas\"));\n\n    auto result = m1une::string::longest_common_substring(\n\
    \        std::string(\"xabxac\"),\n        std::string(\"abcabxabcd\")\n    );\n\
    \    assert(result.length() == 4);\n    assert((result.first_interval() == std::make_pair(result.first_left,\
    \ result.first_right)));\n    assert((result.second_interval() == std::make_pair(result.second_left,\
    \ result.second_right)));\n\n    std::vector<int> first;\n    first.push_back(3);\n\
    \    first.push_back(-1);\n    first.push_back(4);\n    first.push_back(-1);\n\
    \    first.push_back(5);\n    std::vector<int> second;\n    second.push_back(9);\n\
    \    second.push_back(4);\n    second.push_back(-1);\n    second.push_back(5);\n\
    \    second.push_back(9);\n    check_result(first, second);\n    auto vector_result\
    \ = m1une::string::longest_common_substring(first, second);\n    assert(vector_result.length()\
    \ == 3);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 20260709;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 2000; trial++) {\n        int n = int(random() % 35);\n        int m = int(random()\
    \ % 35);\n        std::string first(n, 'a');\n        std::string second(m, 'a');\n\
    \        for (char& character : first) character = char('a' + random() % 5);\n\
    \        for (char& character : second) character = char('a' + random() % 5);\n\
    \        check_result(first, second);\n\n        std::vector<int> first_values(n);\n\
    \        std::vector<int> second_values(m);\n        for (int& value : first_values)\
    \ value = int(random() % 7) - 3;\n        for (int& value : second_values) value\
    \ = int(random() % 7) - 3;\n        check_result(first_values, second_values);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    std::string\
    \ first, second;\n    std::cin >> first >> second;\n\n    auto result = m1une::string::longest_common_substring(first,\
    \ second);\n    std::cout << result.first_left << ' ' << result.first_right <<\
    \ ' '\n              << result.second_left << ' ' << result.second_right << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/longest_common_substring\"\
    \n\n#include \"../../string/longest_common_substring.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <string>\n\
    #include <vector>\n\nnamespace {\n\ntemplate <class Sequence>\nbool equal_substring(\n\
    \    const Sequence& first,\n    int first_left,\n    const Sequence& second,\n\
    \    int second_left,\n    int length\n) {\n    for (int i = 0; i < length; i++)\
    \ {\n        if (first[first_left + i] != second[second_left + i]) return false;\n\
    \    }\n    return true;\n}\n\ntemplate <class Sequence>\nint naive_length(const\
    \ Sequence& first, const Sequence& second) {\n    int n = int(first.size());\n\
    \    int m = int(second.size());\n    int result = 0;\n    for (int i = 0; i <\
    \ n; i++) {\n        for (int j = 0; j < m; j++) {\n            int length = 0;\n\
    \            while (\n                i + length < n &&\n                j + length\
    \ < m &&\n                first[i + length] == second[j + length]\n          \
    \  ) {\n                length++;\n            }\n            result = std::max(result,\
    \ length);\n        }\n    }\n    return result;\n}\n\ntemplate <class Sequence>\n\
    void check_result(const Sequence& first, const Sequence& second) {\n    auto result\
    \ = m1une::string::longest_common_substring(first, second);\n    int n = int(first.size());\n\
    \    int m = int(second.size());\n    int length = result.length();\n    assert(0\
    \ <= result.first_left && result.first_left <= result.first_right && result.first_right\
    \ <= n);\n    assert(0 <= result.second_left && result.second_left <= result.second_right\
    \ && result.second_right <= m);\n    assert(result.second_right - result.second_left\
    \ == length);\n    assert(equal_substring(first, result.first_left, second, result.second_left,\
    \ length));\n    assert(length == naive_length(first, second));\n    if (length\
    \ == 0) {\n        assert(result.first_left == 0);\n        assert(result.first_right\
    \ == 0);\n        assert(result.second_left == 0);\n        assert(result.second_right\
    \ == 0);\n        assert(result.empty());\n    }\n}\n\nvoid test_fixed() {\n \
    \   check_result(std::string(), std::string());\n    check_result(std::string(\"\
    abc\"), std::string());\n    check_result(std::string(), std::string(\"abc\"));\n\
    \    check_result(std::string(\"abc\"), std::string(\"def\"));\n    check_result(std::string(\"\
    xabxac\"), std::string(\"abcabxabcd\"));\n    check_result(std::string(\"banana\"\
    ), std::string(\"ananas\"));\n\n    auto result = m1une::string::longest_common_substring(\n\
    \        std::string(\"xabxac\"),\n        std::string(\"abcabxabcd\")\n    );\n\
    \    assert(result.length() == 4);\n    assert((result.first_interval() == std::make_pair(result.first_left,\
    \ result.first_right)));\n    assert((result.second_interval() == std::make_pair(result.second_left,\
    \ result.second_right)));\n\n    std::vector<int> first;\n    first.push_back(3);\n\
    \    first.push_back(-1);\n    first.push_back(4);\n    first.push_back(-1);\n\
    \    first.push_back(5);\n    std::vector<int> second;\n    second.push_back(9);\n\
    \    second.push_back(4);\n    second.push_back(-1);\n    second.push_back(5);\n\
    \    second.push_back(9);\n    check_result(first, second);\n    auto vector_result\
    \ = m1une::string::longest_common_substring(first, second);\n    assert(vector_result.length()\
    \ == 3);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 20260709;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 2000; trial++) {\n        int n = int(random() % 35);\n        int m = int(random()\
    \ % 35);\n        std::string first(n, 'a');\n        std::string second(m, 'a');\n\
    \        for (char& character : first) character = char('a' + random() % 5);\n\
    \        for (char& character : second) character = char('a' + random() % 5);\n\
    \        check_result(first, second);\n\n        std::vector<int> first_values(n);\n\
    \        std::vector<int> second_values(m);\n        for (int& value : first_values)\
    \ value = int(random() % 7) - 3;\n        for (int& value : second_values) value\
    \ = int(random() % 7) - 3;\n        check_result(first_values, second_values);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    std::string\
    \ first, second;\n    std::cin >> first >> second;\n\n    auto result = m1une::string::longest_common_substring(first,\
    \ second);\n    std::cout << result.first_left << ' ' << result.first_right <<\
    \ ' '\n              << result.second_left << ' ' << result.second_right << '\\\
    n';\n}\n"
  dependsOn:
  - string/longest_common_substring.hpp
  - string/suffix_array.hpp
  isVerificationFile: true
  path: verify/string/longest_common_substring.test.cpp
  requiredBy: []
  timestamp: '2026-07-09 02:40:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/longest_common_substring.test.cpp
layout: document
redirect_from:
- /verify/verify/string/longest_common_substring.test.cpp
- /verify/verify/string/longest_common_substring.test.cpp.html
title: verify/string/longest_common_substring.test.cpp
---
