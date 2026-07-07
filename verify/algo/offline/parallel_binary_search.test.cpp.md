---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/offline/parallel_binary_search.hpp
    title: Parallel Binary Search
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
  bundledCode: "#line 1 \"verify/algo/offline/parallel_binary_search.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\n\n#line 1 \"algo/offline/parallel_binary_search.hpp\"\
    \n\n\n\n#line 6 \"algo/offline/parallel_binary_search.hpp\"\n\nnamespace m1une\
    \ {\nnamespace algo {\n\ntemplate <class Apply, class Check, class Reset>\nstd::vector<int>\
    \ parallel_binary_search(\n    int query_count,\n    int event_count,\n    Apply\
    \ apply,\n    Check check,\n    Reset reset\n) {\n    assert(0 <= query_count);\n\
    \    assert(0 <= event_count);\n\n    std::vector<int> low(query_count, -1);\n\
    \    std::vector<int> high(query_count, event_count + 1);\n    std::vector<std::vector<int>>\
    \ bucket(event_count + 1);\n\n    while (true) {\n        bool active = false;\n\
    \        for (auto& queries : bucket) queries.clear();\n\n        for (int query\
    \ = 0; query < query_count; ++query) {\n            if (high[query] - low[query]\
    \ <= 1) continue;\n            const int middle = low[query] + (high[query] -\
    \ low[query]) / 2;\n            bucket[middle].push_back(query);\n           \
    \ active = true;\n        }\n        if (!active) break;\n\n        reset();\n\
    \        int applied = 0;\n        for (int middle = 0; middle <= event_count;\
    \ ++middle) {\n            while (applied < middle) {\n                apply(applied);\n\
    \                ++applied;\n            }\n            for (int query : bucket[middle])\
    \ {\n                if (check(query)) {\n                    high[query] = middle;\n\
    \                } else {\n                    low[query] = middle;\n        \
    \        }\n            }\n        }\n    }\n\n    return high;\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 8 \"verify/algo/offline/parallel_binary_search.test.cpp\"\
    \n\nvoid test_parallel_binary_search() {\n    std::vector<int> add = {3, 1, 4};\n\
    \    std::vector<int> need = {0, 3, 4, 8, 9};\n    int current = 0;\n\n    std::vector<int>\
    \ answer = m1une::algo::parallel_binary_search(\n        int(need.size()),\n \
    \       int(add.size()),\n        [&](int event) {\n            current += add[event];\n\
    \        },\n        [&](int query) {\n            return need[query] <= current;\n\
    \        },\n        [&]() {\n            current = 0;\n        }\n    );\n\n\
    \    std::vector<int> expected = {0, 1, 2, 3, 4};\n    assert(answer == expected);\n\
    }\n\nint main() {\n    test_parallel_binary_search();\n\n    long long a, b;\n\
    \    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\n\n#include \"../../../algo/offline/parallel_binary_search.hpp\"\
    \n\nvoid test_parallel_binary_search() {\n    std::vector<int> add = {3, 1, 4};\n\
    \    std::vector<int> need = {0, 3, 4, 8, 9};\n    int current = 0;\n\n    std::vector<int>\
    \ answer = m1une::algo::parallel_binary_search(\n        int(need.size()),\n \
    \       int(add.size()),\n        [&](int event) {\n            current += add[event];\n\
    \        },\n        [&](int query) {\n            return need[query] <= current;\n\
    \        },\n        [&]() {\n            current = 0;\n        }\n    );\n\n\
    \    std::vector<int> expected = {0, 1, 2, 3, 4};\n    assert(answer == expected);\n\
    }\n\nint main() {\n    test_parallel_binary_search();\n\n    long long a, b;\n\
    \    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - algo/offline/parallel_binary_search.hpp
  isVerificationFile: true
  path: verify/algo/offline/parallel_binary_search.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/offline/parallel_binary_search.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/offline/parallel_binary_search.test.cpp
- /verify/verify/algo/offline/parallel_binary_search.test.cpp.html
title: verify/algo/offline/parallel_binary_search.test.cpp
---
