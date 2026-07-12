---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/kmp.hpp
    title: Knuth-Morris-Pratt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
  bundledCode: "#line 1 \"verify/string/kmp.test.cpp\"\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \n\n#line 1 \"string/kmp.hpp\"\n\n\n\n#include <vector>\n\nnamespace m1une {\n\
    namespace string {\n\n// Returns the KMP prefix function.\ntemplate <class Sequence>\n\
    std::vector<int> prefix_function(const Sequence& sequence) {\n    int n = int(sequence.size());\n\
    \    std::vector<int> prefix(n);\n    for (int i = 1; i < n; i++) {\n        int\
    \ j = prefix[i - 1];\n        while (j > 0 && sequence[i] != sequence[j]) {\n\
    \            j = prefix[j - 1];\n        }\n        if (sequence[i] == sequence[j])\
    \ j++;\n        prefix[i] = j;\n    }\n    return prefix;\n}\n\n// Returns every\
    \ starting position where pattern occurs in text.\n// An empty pattern occurs\
    \ at every position from 0 through text.size().\ntemplate <class Text, class Pattern>\n\
    std::vector<int> kmp_search(const Text& text, const Pattern& pattern) {\n    int\
    \ n = int(text.size());\n    int m = int(pattern.size());\n    if (m == 0) {\n\
    \        std::vector<int> occurrences(n + 1);\n        for (int i = 0; i <= n;\
    \ i++) occurrences[i] = i;\n        return occurrences;\n    }\n\n    std::vector<int>\
    \ prefix = prefix_function(pattern);\n    std::vector<int> occurrences;\n    int\
    \ matched = 0;\n    for (int i = 0; i < n; i++) {\n        while (matched > 0\
    \ && text[i] != pattern[matched]) {\n            matched = prefix[matched - 1];\n\
    \        }\n        if (text[i] == pattern[matched]) matched++;\n        if (matched\
    \ == m) {\n            occurrences.push_back(i - m + 1);\n            matched\
    \ = prefix[matched - 1];\n        }\n    }\n    return occurrences;\n}\n\n}  //\
    \ namespace string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/kmp.test.cpp\"\
    \n\n#include <iostream>\n#include <string>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    std::string text;\n    std::string pattern;\n\
    \    std::cin >> text >> pattern;\n\n    for (int position : m1une::string::kmp_search(text,\
    \ pattern)) {\n        std::cout << position << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \n\n#include \"../../string/kmp.hpp\"\n\n#include <iostream>\n#include <string>\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::string text;\n    std::string pattern;\n    std::cin >> text >> pattern;\n\
    \n    for (int position : m1une::string::kmp_search(text, pattern)) {\n      \
    \  std::cout << position << '\\n';\n    }\n}\n"
  dependsOn:
  - string/kmp.hpp
  isVerificationFile: true
  path: verify/string/kmp.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 04:27:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/kmp.test.cpp
layout: document
redirect_from:
- /verify/verify/string/kmp.test.cpp
- /verify/verify/string/kmp.test.cpp.html
title: verify/string/kmp.test.cpp
---
