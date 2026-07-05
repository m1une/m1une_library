---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monge/min_plus_convolution.hpp
    title: Structured Min-Plus and Max-Plus Convolution
  - icon: ':heavy_check_mark:'
    path: monge/smawk.hpp
    title: SMAWK
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
    links:
    - https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
  bundledCode: "#line 1 \"verify/monge/max_plus_convolution_concave_arbitrary.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary\"\
    \n\n#include <iostream>\n#include <vector>\n\n#line 1 \"monge/min_plus_convolution.hpp\"\
    \n\n\n\n#include <functional>\n#line 6 \"monge/min_plus_convolution.hpp\"\n\n\
    #line 1 \"monge/smawk.hpp\"\n\n\n\n#include <cassert>\n#line 6 \"monge/smawk.hpp\"\
    \n#include <numeric>\n#line 8 \"monge/smawk.hpp\"\n\nnamespace m1une {\nnamespace\
    \ monge {\n\nnamespace smawk_detail {\n\ntemplate <class Select>\nvoid solve(const\
    \ std::vector<int>& rows, const std::vector<int>& columns,\n           const Select&\
    \ select, std::vector<int>& answer) {\n    if (rows.empty()) return;\n\n    std::vector<int>\
    \ reduced;\n    reduced.reserve(columns.size());\n    for (int column : columns)\
    \ {\n        while (!reduced.empty()) {\n            int row = rows[int(reduced.size())\
    \ - 1];\n            if (!select(row, reduced.back(), column)) break;\n      \
    \      reduced.pop_back();\n        }\n        if (reduced.size() < rows.size())\
    \ reduced.push_back(column);\n    }\n\n    std::vector<int> odd_rows;\n    odd_rows.reserve(rows.size()\
    \ / 2);\n    for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);\n\
    \    solve(odd_rows, reduced, select, answer);\n\n    int left = 0;\n    int right\
    \ = 0;\n    for (int i = 0; i < int(rows.size()); i += 2) {\n        if (i + 1\
    \ < int(rows.size())) {\n            while (reduced[right] != answer[rows[i +\
    \ 1]]) right++;\n        } else {\n            right = int(reduced.size()) - 1;\n\
    \        }\n\n        int best = left;\n        for (int j = left + 1; j <= right;\
    \ j++) {\n            if (select(rows[i], reduced[best], reduced[j])) {\n    \
    \            best = j;\n            }\n        }\n        answer[rows[i]] = reduced[best];\n\
    \        left = right;\n    }\n}\n\ntemplate <class Select>\nstd::vector<int>\
    \ row_optima(int row_count, int column_count, const Select& select) {\n    std::vector<int>\
    \ answer(row_count, -1);\n    if (row_count == 0 || column_count == 0) return\
    \ answer;\n\n    std::vector<int> rows(row_count), columns(column_count);\n  \
    \  std::iota(rows.begin(), rows.end(), 0);\n    std::iota(columns.begin(), columns.end(),\
    \ 0);\n    solve(rows, columns, select, answer);\n    return answer;\n}\n\n} \
    \ // namespace smawk_detail\n\ntemplate <class Value, class Compare = std::less<>>\n\
    std::vector<int> smawk_row_optima(int row_count, int column_count, Value value,\n\
    \                                  Compare compare = Compare()) {\n    assert(row_count\
    \ >= 0);\n    assert(column_count >= 0);\n    return smawk_detail::row_optima(\n\
    \        row_count, column_count,\n        [&](int row, int current, int candidate)\
    \ {\n            return compare(value(row, candidate), value(row, current));\n\
    \        });\n}\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmin(int\
    \ row_count, int column_count, Value value) {\n    return smawk_row_optima(row_count,\
    \ column_count, value, std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int>\
    \ smawk_row_argmax(int row_count, int column_count, Value value) {\n    return\
    \ smawk_row_optima(row_count, column_count, value, std::greater<>());\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmin(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n\n#line 8 \"monge/min_plus_convolution.hpp\"\
    \n\nnamespace m1une {\nnamespace monge {\n\nnamespace convolution_detail {\n\n\
    template <class T, class Compare>\nstd::vector<T> structured_convolution(const\
    \ std::vector<T>& arbitrary,\n                                      const std::vector<T>&\
    \ structured,\n                                      Compare compare) {\n    if\
    \ (arbitrary.empty() || structured.empty()) return {};\n\n    int first_size =\
    \ int(arbitrary.size());\n    int second_size = int(structured.size());\n    int\
    \ result_size = first_size + second_size - 1;\n    auto select = [&](int index,\
    \ int current, int candidate) {\n        if (index < candidate) return false;\n\
    \        if (index - current >= second_size) return true;\n        T current_value\
    \ = arbitrary[current] + structured[index - current];\n        T candidate_value\
    \ = arbitrary[candidate] + structured[index - candidate];\n        return !compare(current_value,\
    \ candidate_value);\n    };\n\n    std::vector<int> optima =\n        smawk_detail::row_optima(result_size,\
    \ first_size, select);\n    std::vector<T> result;\n    result.reserve(result_size);\n\
    \    for (int index = 0; index < result_size; index++) {\n        int first_index\
    \ = optima[index];\n        result.emplace_back(arbitrary[first_index] + structured[index\
    \ - first_index]);\n    }\n    return result;\n}\n\n}  // namespace convolution_detail\n\
    \ntemplate <class T>\nbool is_convex_sequence(const std::vector<T>& sequence)\
    \ {\n    for (int i = 1; i + 1 < int(sequence.size()); i++) {\n        if (sequence[i]\
    \ - sequence[i - 1] > sequence[i + 1] - sequence[i]) {\n            return false;\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nbool is_concave_sequence(const\
    \ std::vector<T>& sequence) {\n    for (int i = 1; i + 1 < int(sequence.size());\
    \ i++) {\n        if (sequence[i] - sequence[i - 1] < sequence[i + 1] - sequence[i])\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class T>\nstd::vector<T> min_plus_convolution_convex(const std::vector<T>&\
    \ arbitrary,\n                                           const std::vector<T>&\
    \ convex) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ convex, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave(const\
    \ std::vector<T>& arbitrary,\n                                            const\
    \ std::vector<T>& concave) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ concave, std::greater<>());\n}\n\n}  // namespace monge\n}  // namespace m1une\n\
    \n\n#line 7 \"verify/monge/max_plus_convolution_concave_arbitrary.test.cpp\"\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n    std::vector<long long> concave(n),\
    \ arbitrary(m);\n    for (long long& value : concave) {\n        std::cin >> value;\n\
    \        value = -value;\n    }\n    for (long long& value : arbitrary) {\n  \
    \      std::cin >> value;\n        value = -value;\n    }\n\n    std::vector<long\
    \ long> result =\n        m1une::monge::max_plus_convolution_concave(arbitrary,\
    \ concave);\n    for (int i = 0; i < int(result.size()); i++) {\n        if (i)\
    \ std::cout << ' ';\n        std::cout << -result[i];\n    }\n    std::cout <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary\"\
    \n\n#include <iostream>\n#include <vector>\n\n#include \"../../monge/min_plus_convolution.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n    std::vector<long long> concave(n),\
    \ arbitrary(m);\n    for (long long& value : concave) {\n        std::cin >> value;\n\
    \        value = -value;\n    }\n    for (long long& value : arbitrary) {\n  \
    \      std::cin >> value;\n        value = -value;\n    }\n\n    std::vector<long\
    \ long> result =\n        m1une::monge::max_plus_convolution_concave(arbitrary,\
    \ concave);\n    for (int i = 0; i < int(result.size()); i++) {\n        if (i)\
    \ std::cout << ' ';\n        std::cout << -result[i];\n    }\n    std::cout <<\
    \ '\\n';\n}\n"
  dependsOn:
  - monge/min_plus_convolution.hpp
  - monge/smawk.hpp
  isVerificationFile: true
  path: verify/monge/max_plus_convolution_concave_arbitrary.test.cpp
  requiredBy: []
  timestamp: '2026-07-06 04:27:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/monge/max_plus_convolution_concave_arbitrary.test.cpp
layout: document
redirect_from:
- /verify/verify/monge/max_plus_convolution_concave_arbitrary.test.cpp
- /verify/verify/monge/max_plus_convolution_concave_arbitrary.test.cpp.html
title: verify/monge/max_plus_convolution_concave_arbitrary.test.cpp
---
