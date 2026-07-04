---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monge/min_plus_convolution.hpp
    title: Structured Min-Plus and Max-Plus Convolution
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex
    links:
    - https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex
  bundledCode: "#line 1 \"verify/monge/max_plus_convolution_concave_concave.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex\"\
    \n\n#include <iostream>\n#include <vector>\n\n#line 1 \"monge/min_plus_convolution.hpp\"\
    \n\n\n\n#include <functional>\n#line 6 \"monge/min_plus_convolution.hpp\"\n\n\
    namespace m1une {\nnamespace monge {\n\nnamespace convolution_detail {\n\ntemplate\
    \ <class T, class Compare>\nstd::vector<T> structured_convolution(const std::vector<T>&\
    \ arbitrary,\n                                      const std::vector<T>& structured,\n\
    \                                      Compare compare) {\n    if (arbitrary.empty()\
    \ || structured.empty()) return {};\n\n    int first_size = int(arbitrary.size());\n\
    \    int second_size = int(structured.size());\n    int result_size = first_size\
    \ + second_size - 1;\n    std::vector<T> result(result_size);\n\n    auto solve\
    \ = [&](auto self, int result_left, int result_right, int candidate_left,\n  \
    \                   int candidate_right) -> void {\n        if (result_left ==\
    \ result_right) return;\n        int index = (result_left + result_right) / 2;\n\
    \        int left = candidate_left > index - second_size + 1 ? candidate_left\n\
    \                                                            : index - second_size\
    \ + 1;\n        int right = candidate_right < index + 1 ? candidate_right : index\
    \ + 1;\n\n        int best = left;\n        T best_value = arbitrary[best] + structured[index\
    \ - best];\n        for (int candidate = left + 1; candidate < right; candidate++)\
    \ {\n            T current = arbitrary[candidate] + structured[index - candidate];\n\
    \            if (compare(current, best_value)) {\n                best = candidate;\n\
    \                best_value = current;\n            }\n        }\n        result[index]\
    \ = best_value;\n        self(self, result_left, index, candidate_left, best +\
    \ 1);\n        self(self, index + 1, result_right, best, candidate_right);\n \
    \   };\n\n    solve(solve, 0, result_size, 0, first_size);\n    return result;\n\
    }\n\ntemplate <class T, class Compare>\nstd::vector<T> linear_structured_convolution(const\
    \ std::vector<T>& first,\n                                             const std::vector<T>&\
    \ second,\n                                             Compare compare) {\n \
    \   if (first.empty() || second.empty()) return {};\n\n    int first_size = int(first.size());\n\
    \    int second_size = int(second.size());\n    std::vector<T> result(first_size\
    \ + second_size - 1);\n    result[0] = first[0] + second[0];\n\n    int first_index\
    \ = 1;\n    int second_index = 1;\n    int result_index = 1;\n    while (first_index\
    \ < first_size && second_index < second_size) {\n        T first_difference =\
    \ first[first_index] - first[first_index - 1];\n        T second_difference =\
    \ second[second_index] - second[second_index - 1];\n        if (compare(second_difference,\
    \ first_difference)) {\n            result[result_index] = result[result_index\
    \ - 1] + second_difference;\n            second_index++;\n        } else {\n \
    \           result[result_index] = result[result_index - 1] + first_difference;\n\
    \            first_index++;\n        }\n        result_index++;\n    }\n    while\
    \ (first_index < first_size) {\n        T difference = first[first_index] - first[first_index\
    \ - 1];\n        result[result_index] = result[result_index - 1] + difference;\n\
    \        first_index++;\n        result_index++;\n    }\n    while (second_index\
    \ < second_size) {\n        T difference = second[second_index] - second[second_index\
    \ - 1];\n        result[result_index] = result[result_index - 1] + difference;\n\
    \        second_index++;\n        result_index++;\n    }\n    return result;\n\
    }\n\n}  // namespace convolution_detail\n\ntemplate <class T>\nbool is_convex_sequence(const\
    \ std::vector<T>& sequence) {\n    for (int i = 1; i + 1 < int(sequence.size());\
    \ i++) {\n        if (sequence[i] - sequence[i - 1] > sequence[i + 1] - sequence[i])\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class T>\nbool is_concave_sequence(const std::vector<T>& sequence) {\n    for\
    \ (int i = 1; i + 1 < int(sequence.size()); i++) {\n        if (sequence[i] -\
    \ sequence[i - 1] < sequence[i + 1] - sequence[i]) {\n            return false;\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex(const\
    \ std::vector<T>& arbitrary,\n                                           const\
    \ std::vector<T>& convex) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ convex, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex_convex(const\
    \ std::vector<T>& first,\n                                                  const\
    \ std::vector<T>& second) {\n    return convolution_detail::linear_structured_convolution(first,\
    \ second, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave(const\
    \ std::vector<T>& arbitrary,\n                                            const\
    \ std::vector<T>& concave) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ concave, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave_concave(const\
    \ std::vector<T>& first,\n                                                   \
    \ const std::vector<T>& second) {\n    return convolution_detail::linear_structured_convolution(first,\
    \ second, std::greater<>());\n}\n\n}  // namespace monge\n}  // namespace m1une\n\
    \n\n#line 7 \"verify/monge/max_plus_convolution_concave_concave.test.cpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n    std::vector<long long> first(n),\
    \ second(m);\n    for (long long& value : first) {\n        std::cin >> value;\n\
    \        value = -value;\n    }\n    for (long long& value : second) {\n     \
    \   std::cin >> value;\n        value = -value;\n    }\n\n    std::vector<long\
    \ long> result =\n        m1une::monge::max_plus_convolution_concave_concave(first,\
    \ second);\n    for (int i = 0; i < int(result.size()); i++) {\n        if (i)\
    \ std::cout << ' ';\n        std::cout << -result[i];\n    }\n    std::cout <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex\"\
    \n\n#include <iostream>\n#include <vector>\n\n#include \"../../monge/min_plus_convolution.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n    std::vector<long long> first(n),\
    \ second(m);\n    for (long long& value : first) {\n        std::cin >> value;\n\
    \        value = -value;\n    }\n    for (long long& value : second) {\n     \
    \   std::cin >> value;\n        value = -value;\n    }\n\n    std::vector<long\
    \ long> result =\n        m1une::monge::max_plus_convolution_concave_concave(first,\
    \ second);\n    for (int i = 0; i < int(result.size()); i++) {\n        if (i)\
    \ std::cout << ' ';\n        std::cout << -result[i];\n    }\n    std::cout <<\
    \ '\\n';\n}\n"
  dependsOn:
  - monge/min_plus_convolution.hpp
  isVerificationFile: true
  path: verify/monge/max_plus_convolution_concave_concave.test.cpp
  requiredBy: []
  timestamp: '2026-07-05 05:15:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/monge/max_plus_convolution_concave_concave.test.cpp
layout: document
redirect_from:
- /verify/verify/monge/max_plus_convolution_concave_concave.test.cpp
- /verify/verify/monge/max_plus_convolution_concave_concave.test.cpp.html
title: verify/monge/max_plus_convolution_concave_concave.test.cpp
---
