---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/sequence/lis.hpp
    title: Longest Increasing Subsequence (LIS)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/longest_increasing_subsequence
    links:
    - https://judge.yosupo.jp/problem/longest_increasing_subsequence
  bundledCode: "#line 1 \"verify/algo/sequence/longest_increasing_subsequence.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/longest_increasing_subsequence\"\
    \n\n#line 1 \"algo/sequence/lis.hpp\"\n\n\n\n#include <algorithm>\n#include <iterator>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n// Returns the zero-based\
    \ indices of a longest increasing subsequence.\n// If `strict` is false, equal\
    \ adjacent values are also allowed.\ntemplate <typename T>\nstd::vector<int> lis(const\
    \ std::vector<T>& a, bool strict = true) {\n    const int n = int(a.size());\n\
    \    std::vector<T> tails;\n    std::vector<int> tail_positions;\n    std::vector<int>\
    \ predecessor(n, -1);\n    tails.reserve(n);\n    tail_positions.reserve(n);\n\
    \n    for (int i = 0; i < n; ++i) {\n        auto it = strict ? std::lower_bound(tails.begin(),\
    \ tails.end(), a[i])\n                         : std::upper_bound(tails.begin(),\
    \ tails.end(), a[i]);\n        const int length = int(std::distance(tails.begin(),\
    \ it));\n\n        if (it == tails.end()) {\n            tails.push_back(a[i]);\n\
    \            tail_positions.push_back(i);\n        } else {\n            *it =\
    \ a[i];\n            tail_positions[length] = i;\n        }\n\n        if (length\
    \ > 0) {\n            predecessor[i] = tail_positions[length - 1];\n        }\n\
    \    }\n\n    if (tail_positions.empty()) return {};\n\n    std::vector<int> result;\n\
    \    result.reserve(tail_positions.size());\n    int current = tail_positions.back();\n\
    \    while (current != -1) {\n        result.push_back(current);\n        current\
    \ = predecessor[current];\n    }\n    std::reverse(result.begin(), result.end());\n\
    \    return result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line\
    \ 4 \"verify/algo/sequence/longest_increasing_subsequence.test.cpp\"\n\n#include\
    \ <iostream>\n#line 7 \"verify/algo/sequence/longest_increasing_subsequence.test.cpp\"\
    \n\nint main() {\n    int size;\n    std::cin >> size;\n    std::vector<int> values(size);\n\
    \    for (int& value : values) std::cin >> value;\n\n    std::vector<int> indices\
    \ = m1une::algo::lis(values);\n    std::cout << indices.size() << '\\n';\n   \
    \ for (int i = 0; i < int(indices.size()); i++) {\n        if (i != 0) std::cout\
    \ << ' ';\n        std::cout << indices[i];\n    }\n    std::cout << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/longest_increasing_subsequence\"\
    \n\n#include \"../../../algo/sequence/lis.hpp\"\n\n#include <iostream>\n#include\
    \ <vector>\n\nint main() {\n    int size;\n    std::cin >> size;\n    std::vector<int>\
    \ values(size);\n    for (int& value : values) std::cin >> value;\n\n    std::vector<int>\
    \ indices = m1une::algo::lis(values);\n    std::cout << indices.size() << '\\\
    n';\n    for (int i = 0; i < int(indices.size()); i++) {\n        if (i != 0)\
    \ std::cout << ' ';\n        std::cout << indices[i];\n    }\n    std::cout <<\
    \ '\\n';\n}\n"
  dependsOn:
  - algo/sequence/lis.hpp
  isVerificationFile: true
  path: verify/algo/sequence/longest_increasing_subsequence.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 03:22:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/sequence/longest_increasing_subsequence.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/sequence/longest_increasing_subsequence.test.cpp
- /verify/verify/algo/sequence/longest_increasing_subsequence.test.cpp.html
title: verify/algo/sequence/longest_increasing_subsequence.test.cpp
---
