---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/dp/knuth_optimization.hpp
    title: Knuth Optimization
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    ERROR: 1e-7
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_D
  bundledCode: "#line 1 \"verify/algo/dp/knuth_optimization.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_D\"\n#define ERROR 1e-7\n\
    \n#include <algorithm>\n#include <cassert>\n#include <iomanip>\n#include <iostream>\n\
    #include <limits>\n#include <vector>\n#line 1 \"algo/dp/knuth_optimization.hpp\"\
    \n\n\n\n#line 6 \"algo/dp/knuth_optimization.hpp\"\n#include <type_traits>\n#line\
    \ 8 \"algo/dp/knuth_optimization.hpp\"\n\nnamespace m1une {\nnamespace algo {\n\
    \ntemplate <class T>\nstruct KnuthOptimizationResult {\n    std::vector<std::vector<T>>\
    \ value;\n    std::vector<std::vector<int>> split;\n\n    T optimum() const {\n\
    \        return value[0].back();\n    }\n};\n\ntemplate <class IntervalCost>\n\
    auto knuth_optimization(int element_count, IntervalCost interval_cost)\n    ->\
    \ KnuthOptimizationResult<\n        std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>> {\n    assert(element_count >= 0);\n    using T = std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>;\n\n    KnuthOptimizationResult<T> result;\n    result.value.assign(element_count\
    \ + 1, std::vector<T>(element_count + 1, T()));\n    result.split.assign(element_count\
    \ + 1, std::vector<int>(element_count + 1, -1));\n\n    for (int left = 0; left\
    \ <= element_count; left++) result.split[left][left] = left;\n    for (int left\
    \ = 0; left < element_count; left++) result.split[left][left + 1] = left + 1;\n\
    \n    for (int length = 2; length <= element_count; length++) {\n        for (int\
    \ left = 0; left + length <= element_count; left++) {\n            int right =\
    \ left + length;\n            int first = std::max(left + 1, result.split[left][right\
    \ - 1]);\n            int last = std::min(right - 1, result.split[left + 1][right]);\n\
    \            assert(first <= last);\n\n            int best = first;\n       \
    \     T best_value = result.value[left][best] + result.value[best][right];\n \
    \           for (int split = first + 1; split <= last; split++) {\n          \
    \      T candidate = result.value[left][split] + result.value[split][right];\n\
    \                if (candidate < best_value) {\n                    best = split;\n\
    \                    best_value = candidate;\n                }\n            }\n\
    \            result.value[left][right] = best_value + interval_cost(left, right);\n\
    \            result.split[left][right] = best;\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line 11 \"verify/algo/dp/knuth_optimization.test.cpp\"\
    \n\nvoid test_knuth_optimization() {\n    for (int n = 0; n <= 45; n++) {\n  \
    \      for (int test = 0; test < 20; test++) {\n            std::vector<long long>\
    \ weight(n);\n            for (int i = 0; i < n; i++) weight[i] = (test * 7 +\
    \ i * 11 + n) % 13;\n            std::vector<long long> prefix(n + 1);\n     \
    \       for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + weight[i];\n \
    \           auto interval_cost = [&](int left, int right) {\n                return\
    \ prefix[right] - prefix[left];\n            };\n\n            auto result = m1une::algo::knuth_optimization(n,\
    \ interval_cost);\n            std::vector<std::vector<long long>> expected(\n\
    \                n + 1, std::vector<long long>(n + 1));\n            for (int\
    \ length = 2; length <= n; length++) {\n                for (int left = 0; left\
    \ + length <= n; left++) {\n                    int right = left + length;\n \
    \                   expected[left][right] = std::numeric_limits<long long>::max();\n\
    \                    for (int split = left + 1; split < right; split++) {\n  \
    \                      expected[left][right] =\n                            std::min(expected[left][right],\n\
    \                                     expected[left][split] + expected[split][right]\
    \ +\n                                         interval_cost(left, right));\n \
    \                   }\n                }\n            }\n            assert(result.value\
    \ == expected);\n            assert(result.optimum() == expected[0][n]);\n\n \
    \           for (int length = 2; length <= n; length++) {\n                for\
    \ (int left = 0; left + length <= n; left++) {\n                    int right\
    \ = left + length;\n                    int split = result.split[left][right];\n\
    \                    assert(result.split[left][right - 1] <= split);\n       \
    \             assert(split <= result.split[left + 1][right]);\n              \
    \      assert(result.value[left][right] ==\n                           result.value[left][split]\
    \ + result.value[split][right] +\n                               interval_cost(left,\
    \ right));\n                }\n            }\n        }\n    }\n}\n\nint main()\
    \ {\n    test_knuth_optimization();\n    int n;\n    std::cin >> n;\n    std::vector<double>\
    \ p(n + 1), q(n + 2);\n    for (int i = 0; i < n; ++i) std::cin >> p[i + 1];\n\
    \    for (int i = 0; i <= n; ++i) std::cin >> q[i + 1];\n    for (int i = 0; i\
    \ < n; ++i) p[i + 1] += p[i];\n    for (int i = 0; i <= n; ++i) q[i + 1] += q[i];\n\
    \    // Leaves are the n+1 unsuccessful-search gaps; a split selects a key.\n\
    \    auto result = m1une::algo::knuth_optimization(n + 1, [&](int l, int r) {\n\
    \        return q[r] - q[l] + p[r - 1] - p[l];\n    });\n    std::cout << std::fixed\
    \ << std::setprecision(12) << result.optimum() + q[n + 1] << '\\n';\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_D\"\n\
    #define ERROR 1e-7\n\n#include <algorithm>\n#include <cassert>\n#include <iomanip>\n\
    #include <iostream>\n#include <limits>\n#include <vector>\n#include \"../../../algo/dp/knuth_optimization.hpp\"\
    \n\nvoid test_knuth_optimization() {\n    for (int n = 0; n <= 45; n++) {\n  \
    \      for (int test = 0; test < 20; test++) {\n            std::vector<long long>\
    \ weight(n);\n            for (int i = 0; i < n; i++) weight[i] = (test * 7 +\
    \ i * 11 + n) % 13;\n            std::vector<long long> prefix(n + 1);\n     \
    \       for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + weight[i];\n \
    \           auto interval_cost = [&](int left, int right) {\n                return\
    \ prefix[right] - prefix[left];\n            };\n\n            auto result = m1une::algo::knuth_optimization(n,\
    \ interval_cost);\n            std::vector<std::vector<long long>> expected(\n\
    \                n + 1, std::vector<long long>(n + 1));\n            for (int\
    \ length = 2; length <= n; length++) {\n                for (int left = 0; left\
    \ + length <= n; left++) {\n                    int right = left + length;\n \
    \                   expected[left][right] = std::numeric_limits<long long>::max();\n\
    \                    for (int split = left + 1; split < right; split++) {\n  \
    \                      expected[left][right] =\n                            std::min(expected[left][right],\n\
    \                                     expected[left][split] + expected[split][right]\
    \ +\n                                         interval_cost(left, right));\n \
    \                   }\n                }\n            }\n            assert(result.value\
    \ == expected);\n            assert(result.optimum() == expected[0][n]);\n\n \
    \           for (int length = 2; length <= n; length++) {\n                for\
    \ (int left = 0; left + length <= n; left++) {\n                    int right\
    \ = left + length;\n                    int split = result.split[left][right];\n\
    \                    assert(result.split[left][right - 1] <= split);\n       \
    \             assert(split <= result.split[left + 1][right]);\n              \
    \      assert(result.value[left][right] ==\n                           result.value[left][split]\
    \ + result.value[split][right] +\n                               interval_cost(left,\
    \ right));\n                }\n            }\n        }\n    }\n}\n\nint main()\
    \ {\n    test_knuth_optimization();\n    int n;\n    std::cin >> n;\n    std::vector<double>\
    \ p(n + 1), q(n + 2);\n    for (int i = 0; i < n; ++i) std::cin >> p[i + 1];\n\
    \    for (int i = 0; i <= n; ++i) std::cin >> q[i + 1];\n    for (int i = 0; i\
    \ < n; ++i) p[i + 1] += p[i];\n    for (int i = 0; i <= n; ++i) q[i + 1] += q[i];\n\
    \    // Leaves are the n+1 unsuccessful-search gaps; a split selects a key.\n\
    \    auto result = m1une::algo::knuth_optimization(n + 1, [&](int l, int r) {\n\
    \        return q[r] - q[l] + p[r - 1] - p[l];\n    });\n    std::cout << std::fixed\
    \ << std::setprecision(12) << result.optimum() + q[n + 1] << '\\n';\n}\n"
  dependsOn:
  - algo/dp/knuth_optimization.hpp
  isVerificationFile: true
  path: verify/algo/dp/knuth_optimization.test.cpp
  requiredBy: []
  timestamp: '2026-10-30 15:56:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/dp/knuth_optimization.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/dp/knuth_optimization.test.cpp
- /verify/verify/algo/dp/knuth_optimization.test.cpp.html
title: verify/algo/dp/knuth_optimization.test.cpp
---
