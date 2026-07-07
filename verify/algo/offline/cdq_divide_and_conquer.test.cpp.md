---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/offline/cdq_divide_and_conquer.hpp
    title: CDQ Divide And Conquer
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/algo/offline/cdq_divide_and_conquer.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\n\n#line 1 \"algo/offline/cdq_divide_and_conquer.hpp\"\
    \n\n\n\n#line 5 \"algo/offline/cdq_divide_and_conquer.hpp\"\n\nnamespace m1une\
    \ {\nnamespace algo {\n\ntemplate <class SolveCross>\nvoid cdq_divide_and_conquer(int\
    \ left, int right, SolveCross solve_cross) {\n    assert(left <= right);\n\n \
    \   auto dfs = [&](auto& self, int l, int r) -> void {\n        if (r - l <= 1)\
    \ return;\n        const int middle = l + (r - l) / 2;\n        self(self, l,\
    \ middle);\n        self(self, middle, r);\n        solve_cross(l, middle, r);\n\
    \    };\n    dfs(dfs, left, right);\n}\n\ntemplate <class SolveCross>\nvoid cdq_divide_and_conquer(int\
    \ n, SolveCross solve_cross) {\n    assert(0 <= n);\n    cdq_divide_and_conquer(0,\
    \ n, solve_cross);\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line\
    \ 8 \"verify/algo/offline/cdq_divide_and_conquer.test.cpp\"\n\nlong long naive_inversion_count(const\
    \ std::vector<int>& a) {\n    long long result = 0;\n    for (int i = 0; i < int(a.size());\
    \ ++i) {\n        for (int j = i + 1; j < int(a.size()); ++j) {\n            if\
    \ (a[j] < a[i]) ++result;\n        }\n    }\n    return result;\n}\n\nlong long\
    \ cdq_inversion_count(const std::vector<int>& a) {\n    long long result = 0;\n\
    \    m1une::algo::cdq_divide_and_conquer(int(a.size()), [&](int left, int middle,\
    \ int right) {\n        for (int i = left; i < middle; ++i) {\n            for\
    \ (int j = middle; j < right; ++j) {\n                if (a[j] < a[i]) ++result;\n\
    \            }\n        }\n    });\n    return result;\n}\n\nvoid test_cdq_divide_and_conquer()\
    \ {\n    for (int n = 0; n <= 8; ++n) {\n        std::vector<int> a(n);\n    \
    \    for (int seed = 0; seed < 100; ++seed) {\n            for (int i = 0; i <\
    \ n; ++i) {\n                a[i] = (seed * 17 + i * i * 5 + i) % 7;\n       \
    \     }\n            assert(cdq_inversion_count(a) == naive_inversion_count(a));\n\
    \        }\n    }\n}\n\nint main() {\n    test_cdq_divide_and_conquer();\n\n \
    \   long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\n\n#include \"../../../algo/offline/cdq_divide_and_conquer.hpp\"\
    \n\nlong long naive_inversion_count(const std::vector<int>& a) {\n    long long\
    \ result = 0;\n    for (int i = 0; i < int(a.size()); ++i) {\n        for (int\
    \ j = i + 1; j < int(a.size()); ++j) {\n            if (a[j] < a[i]) ++result;\n\
    \        }\n    }\n    return result;\n}\n\nlong long cdq_inversion_count(const\
    \ std::vector<int>& a) {\n    long long result = 0;\n    m1une::algo::cdq_divide_and_conquer(int(a.size()),\
    \ [&](int left, int middle, int right) {\n        for (int i = left; i < middle;\
    \ ++i) {\n            for (int j = middle; j < right; ++j) {\n               \
    \ if (a[j] < a[i]) ++result;\n            }\n        }\n    });\n    return result;\n\
    }\n\nvoid test_cdq_divide_and_conquer() {\n    for (int n = 0; n <= 8; ++n) {\n\
    \        std::vector<int> a(n);\n        for (int seed = 0; seed < 100; ++seed)\
    \ {\n            for (int i = 0; i < n; ++i) {\n                a[i] = (seed *\
    \ 17 + i * i * 5 + i) % 7;\n            }\n            assert(cdq_inversion_count(a)\
    \ == naive_inversion_count(a));\n        }\n    }\n}\n\nint main() {\n    test_cdq_divide_and_conquer();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - algo/offline/cdq_divide_and_conquer.hpp
  isVerificationFile: true
  path: verify/algo/offline/cdq_divide_and_conquer.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/offline/cdq_divide_and_conquer.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/offline/cdq_divide_and_conquer.test.cpp
- /verify/verify/algo/offline/cdq_divide_and_conquer.test.cpp.html
title: verify/algo/offline/cdq_divide_and_conquer.test.cpp
---
