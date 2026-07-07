---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/monge/smawk.hpp
    title: SMAWK
  _extendedRequiredBy:
  - icon: ':warning:'
    path: convex/all.hpp
    title: Convex All
  - icon: ':heavy_check_mark:'
    path: convex/monge/all.hpp
    title: Monge All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/max_plus_convolution_concave_arbitrary.test.cpp
    title: verify/convex/monge/max_plus_convolution_concave_arbitrary.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/max_plus_convolution_concave_concave.test.cpp
    title: verify/convex/monge/max_plus_convolution_concave_concave.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/min_plus_convolution_convex_arbitrary.test.cpp
    title: verify/convex/monge/min_plus_convolution_convex_arbitrary.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/min_plus_convolution_convex_convex.test.cpp
    title: verify/convex/monge/min_plus_convolution_convex_convex.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_algorithms.test.cpp
    title: verify/convex/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_dp_optimization.test.cpp
    title: verify/convex/monge/monge_dp_optimization.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"convex/monge/min_plus_convolution.hpp\"\n\n\n\n#include\
    \ <functional>\n#include <utility>\n#include <vector>\n\n#line 1 \"convex/monge/smawk.hpp\"\
    \n\n\n\n#include <cassert>\n#line 6 \"convex/monge/smawk.hpp\"\n#include <numeric>\n\
    #line 8 \"convex/monge/smawk.hpp\"\n\nnamespace m1une {\nnamespace convex {\n\n\
    namespace smawk_detail {\n\ntemplate <class Select>\nvoid solve(const std::vector<int>&\
    \ rows, const std::vector<int>& columns,\n           const Select& select, std::vector<int>&\
    \ answer) {\n    if (rows.empty()) return;\n\n    std::vector<int> reduced;\n\
    \    reduced.reserve(columns.size());\n    for (int column : columns) {\n    \
    \    while (!reduced.empty()) {\n            int row = rows[int(reduced.size())\
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
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 9 \"convex/monge/min_plus_convolution.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\nnamespace convolution_detail {\n\n\
    template <class T, class Compare, class Add>\nstd::vector<T> structured_convolution(const\
    \ std::vector<T>& arbitrary,\n                                      const std::vector<T>&\
    \ structured,\n                                      Compare compare, Add add)\
    \ {\n    if (arbitrary.empty() || structured.empty()) return {};\n\n    int first_size\
    \ = int(arbitrary.size());\n    int second_size = int(structured.size());\n  \
    \  int result_size = first_size + second_size - 1;\n    auto select = [&](int\
    \ index, int current, int candidate) {\n        if (index < candidate) return\
    \ false;\n        if (index - current >= second_size) return true;\n        T\
    \ current_value = add(arbitrary[current], structured[index - current]);\n    \
    \    T candidate_value = add(arbitrary[candidate], structured[index - candidate]);\n\
    \        return !compare(current_value, candidate_value);\n    };\n\n    std::vector<int>\
    \ optima =\n        smawk_detail::row_optima(result_size, first_size, select);\n\
    \    std::vector<T> result;\n    result.reserve(result_size);\n    for (int index\
    \ = 0; index < result_size; index++) {\n        int first_index = optima[index];\n\
    \        result.emplace_back(add(arbitrary[first_index],\n                   \
    \             structured[index - first_index]));\n    }\n    return result;\n\
    }\n\ntemplate <class T>\nstd::pair<int, int> finite_interval(const std::vector<T>&\
    \ sequence,\n                                    const T& infinity) {\n    int\
    \ left = 0;\n    while (left < int(sequence.size()) && sequence[left] == infinity)\
    \ left++;\n    int right = int(sequence.size());\n    while (right > left && sequence[right\
    \ - 1] == infinity) right--;\n    return {left, right};\n}\n\ntemplate <class\
    \ T, class Compare>\nstd::vector<T> structured_convolution_with_infinity(\n  \
    \  const std::vector<T>& arbitrary, const std::vector<T>& structured,\n    const\
    \ T& infinity, Compare compare) {\n    if (arbitrary.empty() || structured.empty())\
    \ return {};\n\n    auto [left, right] = finite_interval(structured, infinity);\n\
    \    int result_size = int(arbitrary.size() + structured.size() - 1);\n    std::vector<T>\
    \ result(result_size, infinity);\n    if (left == right) return result;\n\n  \
    \  std::vector<int> columns;\n    columns.reserve(arbitrary.size());\n    for\
    \ (int i = 0; i < int(arbitrary.size()); i++) {\n        if (arbitrary[i] != infinity)\
    \ columns.push_back(i);\n    }\n    if (columns.empty()) return result;\n\n  \
    \  int finite_size = right - left;\n    int middle_size = int(arbitrary.size())\
    \ + finite_size - 1;\n    std::vector<int> rows;\n    rows.reserve(middle_size);\n\
    \    int active = 0;\n    for (int row = 0; row < middle_size; row++) {\n    \
    \    if (row < int(arbitrary.size()) && arbitrary[row] != infinity) active++;\n\
    \        if (row >= finite_size && arbitrary[row - finite_size] != infinity) active--;\n\
    \        if (active > 0) rows.push_back(row);\n    }\n\n    auto select = [&](int\
    \ index, int current, int candidate) {\n        if (index < candidate) return\
    \ false;\n        if (index - current >= finite_size) return true;\n        T\
    \ current_value =\n            arbitrary[current] + structured[left + index -\
    \ current];\n        T candidate_value =\n            arbitrary[candidate] + structured[left\
    \ + index - candidate];\n        return !compare(current_value, candidate_value);\n\
    \    };\n    std::vector<int> optima(middle_size, -1);\n    smawk_detail::solve(rows,\
    \ columns, select, optima);\n    for (int row : rows) {\n        int first_index\
    \ = optima[row];\n        result[left + row] =\n            arbitrary[first_index]\
    \ + structured[left + row - first_index];\n    }\n    return result;\n}\n\ntemplate\
    \ <class T, class Compare>\nstd::vector<T> linear_structured_convolution(const\
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
    }\n\ntemplate <class T, class Compare>\nstd::vector<T> linear_structured_convolution_with_infinity(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ infinity, Compare compare) {\n    if (first.empty() || second.empty()) return\
    \ {};\n\n    auto [first_left, first_right] = finite_interval(first, infinity);\n\
    \    auto [second_left, second_right] = finite_interval(second, infinity);\n \
    \   int result_size = int(first.size() + second.size() - 1);\n    std::vector<T>\
    \ result(result_size, infinity);\n    if (first_left == first_right || second_left\
    \ == second_right) return result;\n\n    int offset = first_left + second_left;\n\
    \    result[offset] = first[first_left] + second[second_left];\n\n    int first_index\
    \ = first_left + 1;\n    int second_index = second_left + 1;\n    int result_index\
    \ = offset + 1;\n    while (first_index < first_right && second_index < second_right)\
    \ {\n        T first_difference = first[first_index] - first[first_index - 1];\n\
    \        T second_difference = second[second_index] - second[second_index - 1];\n\
    \        if (compare(second_difference, first_difference)) {\n            result[result_index]\
    \ = result[result_index - 1] + second_difference;\n            second_index++;\n\
    \        } else {\n            result[result_index] = result[result_index - 1]\
    \ + first_difference;\n            first_index++;\n        }\n        result_index++;\n\
    \    }\n    while (first_index < first_right) {\n        T difference = first[first_index]\
    \ - first[first_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        first_index++;\n        result_index++;\n    }\n\
    \    while (second_index < second_right) {\n        T difference = second[second_index]\
    \ - second[second_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        second_index++;\n        result_index++;\n    }\n\
    \    return result;\n}\n\ntemplate <class T, class Compare>\nbool is_structured_sequence_with_infinity(const\
    \ std::vector<T>& sequence,\n                                          const T&\
    \ infinity, Compare violation) {\n    auto [left, right] = finite_interval(sequence,\
    \ infinity);\n    for (int i = left; i < right; i++) {\n        if (sequence[i]\
    \ == infinity) return false;\n    }\n    for (int i = left + 1; i + 1 < right;\
    \ i++) {\n        T first_difference = sequence[i] - sequence[i - 1];\n      \
    \  T second_difference = sequence[i + 1] - sequence[i];\n        if (violation(first_difference,\
    \ second_difference)) return false;\n    }\n    return true;\n}\n\n}  // namespace\
    \ convolution_detail\n\ntemplate <class T>\nbool is_convex_sequence(const std::vector<T>&\
    \ sequence) {\n    for (int i = 1; i + 1 < int(sequence.size()); i++) {\n    \
    \    if (sequence[i] - sequence[i - 1] > sequence[i + 1] - sequence[i]) {\n  \
    \          return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class\
    \ T>\nbool is_convex_sequence(const std::vector<T>& sequence, const T& infinity)\
    \ {\n    return convolution_detail::is_structured_sequence_with_infinity(\n  \
    \      sequence, infinity, std::greater<>());\n}\n\ntemplate <class T>\nbool is_concave_sequence(const\
    \ std::vector<T>& sequence) {\n    for (int i = 1; i + 1 < int(sequence.size());\
    \ i++) {\n        if (sequence[i] - sequence[i - 1] < sequence[i + 1] - sequence[i])\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class T>\nbool is_concave_sequence(const std::vector<T>& sequence,\n      \
    \                   const T& negative_infinity) {\n    return convolution_detail::is_structured_sequence_with_infinity(\n\
    \        sequence, negative_infinity, std::less<>());\n}\n\ntemplate <class T>\n\
    std::vector<T> min_plus_convolution_convex(const std::vector<T>& arbitrary,\n\
    \                                           const std::vector<T>& convex) {\n\
    \    auto add = [](const T& first, const T& second) { return first + second; };\n\
    \    return convolution_detail::structured_convolution(arbitrary, convex,\n  \
    \                                                    std::less<>(), add);\n}\n\
    \ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex(const std::vector<T>&\
    \ arbitrary,\n                                           const std::vector<T>&\
    \ convex,\n                                           const T& infinity) {\n \
    \   return convolution_detail::structured_convolution_with_infinity(\n       \
    \ arbitrary, convex, infinity, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ min_plus_convolution_convex_convex(const std::vector<T>& first,\n          \
    \                                        const std::vector<T>& second) {\n   \
    \ return convolution_detail::linear_structured_convolution(first, second, std::less<>());\n\
    }\n\ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex_convex(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ infinity) {\n    return convolution_detail::linear_structured_convolution_with_infinity(\n\
    \        first, second, infinity, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ max_plus_convolution_concave(const std::vector<T>& arbitrary,\n            \
    \                                const std::vector<T>& concave) {\n    auto add\
    \ = [](const T& first, const T& second) { return first + second; };\n    return\
    \ convolution_detail::structured_convolution(arbitrary, concave,\n           \
    \                                           std::greater<>(), add);\n}\n\ntemplate\
    \ <class T>\nstd::vector<T> max_plus_convolution_concave(const std::vector<T>&\
    \ arbitrary,\n                                            const std::vector<T>&\
    \ concave,\n                                            const T& negative_infinity)\
    \ {\n    return convolution_detail::structured_convolution_with_infinity(\n  \
    \      arbitrary, concave, negative_infinity, std::greater<>());\n}\n\ntemplate\
    \ <class T>\nstd::vector<T> max_plus_convolution_concave_concave(const std::vector<T>&\
    \ first,\n                                                    const std::vector<T>&\
    \ second) {\n    return convolution_detail::linear_structured_convolution(first,\
    \ second, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave_concave(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ negative_infinity) {\n    return convolution_detail::linear_structured_convolution_with_infinity(\n\
    \        first, second, negative_infinity, std::greater<>());\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_MIN_PLUS_CONVOLUTION_HPP\n#define M1UNE_CONVEX_MONGE_MIN_PLUS_CONVOLUTION_HPP\
    \ 1\n\n#include <functional>\n#include <utility>\n#include <vector>\n\n#include\
    \ \"smawk.hpp\"\n\nnamespace m1une {\nnamespace convex {\n\nnamespace convolution_detail\
    \ {\n\ntemplate <class T, class Compare, class Add>\nstd::vector<T> structured_convolution(const\
    \ std::vector<T>& arbitrary,\n                                      const std::vector<T>&\
    \ structured,\n                                      Compare compare, Add add)\
    \ {\n    if (arbitrary.empty() || structured.empty()) return {};\n\n    int first_size\
    \ = int(arbitrary.size());\n    int second_size = int(structured.size());\n  \
    \  int result_size = first_size + second_size - 1;\n    auto select = [&](int\
    \ index, int current, int candidate) {\n        if (index < candidate) return\
    \ false;\n        if (index - current >= second_size) return true;\n        T\
    \ current_value = add(arbitrary[current], structured[index - current]);\n    \
    \    T candidate_value = add(arbitrary[candidate], structured[index - candidate]);\n\
    \        return !compare(current_value, candidate_value);\n    };\n\n    std::vector<int>\
    \ optima =\n        smawk_detail::row_optima(result_size, first_size, select);\n\
    \    std::vector<T> result;\n    result.reserve(result_size);\n    for (int index\
    \ = 0; index < result_size; index++) {\n        int first_index = optima[index];\n\
    \        result.emplace_back(add(arbitrary[first_index],\n                   \
    \             structured[index - first_index]));\n    }\n    return result;\n\
    }\n\ntemplate <class T>\nstd::pair<int, int> finite_interval(const std::vector<T>&\
    \ sequence,\n                                    const T& infinity) {\n    int\
    \ left = 0;\n    while (left < int(sequence.size()) && sequence[left] == infinity)\
    \ left++;\n    int right = int(sequence.size());\n    while (right > left && sequence[right\
    \ - 1] == infinity) right--;\n    return {left, right};\n}\n\ntemplate <class\
    \ T, class Compare>\nstd::vector<T> structured_convolution_with_infinity(\n  \
    \  const std::vector<T>& arbitrary, const std::vector<T>& structured,\n    const\
    \ T& infinity, Compare compare) {\n    if (arbitrary.empty() || structured.empty())\
    \ return {};\n\n    auto [left, right] = finite_interval(structured, infinity);\n\
    \    int result_size = int(arbitrary.size() + structured.size() - 1);\n    std::vector<T>\
    \ result(result_size, infinity);\n    if (left == right) return result;\n\n  \
    \  std::vector<int> columns;\n    columns.reserve(arbitrary.size());\n    for\
    \ (int i = 0; i < int(arbitrary.size()); i++) {\n        if (arbitrary[i] != infinity)\
    \ columns.push_back(i);\n    }\n    if (columns.empty()) return result;\n\n  \
    \  int finite_size = right - left;\n    int middle_size = int(arbitrary.size())\
    \ + finite_size - 1;\n    std::vector<int> rows;\n    rows.reserve(middle_size);\n\
    \    int active = 0;\n    for (int row = 0; row < middle_size; row++) {\n    \
    \    if (row < int(arbitrary.size()) && arbitrary[row] != infinity) active++;\n\
    \        if (row >= finite_size && arbitrary[row - finite_size] != infinity) active--;\n\
    \        if (active > 0) rows.push_back(row);\n    }\n\n    auto select = [&](int\
    \ index, int current, int candidate) {\n        if (index < candidate) return\
    \ false;\n        if (index - current >= finite_size) return true;\n        T\
    \ current_value =\n            arbitrary[current] + structured[left + index -\
    \ current];\n        T candidate_value =\n            arbitrary[candidate] + structured[left\
    \ + index - candidate];\n        return !compare(current_value, candidate_value);\n\
    \    };\n    std::vector<int> optima(middle_size, -1);\n    smawk_detail::solve(rows,\
    \ columns, select, optima);\n    for (int row : rows) {\n        int first_index\
    \ = optima[row];\n        result[left + row] =\n            arbitrary[first_index]\
    \ + structured[left + row - first_index];\n    }\n    return result;\n}\n\ntemplate\
    \ <class T, class Compare>\nstd::vector<T> linear_structured_convolution(const\
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
    }\n\ntemplate <class T, class Compare>\nstd::vector<T> linear_structured_convolution_with_infinity(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ infinity, Compare compare) {\n    if (first.empty() || second.empty()) return\
    \ {};\n\n    auto [first_left, first_right] = finite_interval(first, infinity);\n\
    \    auto [second_left, second_right] = finite_interval(second, infinity);\n \
    \   int result_size = int(first.size() + second.size() - 1);\n    std::vector<T>\
    \ result(result_size, infinity);\n    if (first_left == first_right || second_left\
    \ == second_right) return result;\n\n    int offset = first_left + second_left;\n\
    \    result[offset] = first[first_left] + second[second_left];\n\n    int first_index\
    \ = first_left + 1;\n    int second_index = second_left + 1;\n    int result_index\
    \ = offset + 1;\n    while (first_index < first_right && second_index < second_right)\
    \ {\n        T first_difference = first[first_index] - first[first_index - 1];\n\
    \        T second_difference = second[second_index] - second[second_index - 1];\n\
    \        if (compare(second_difference, first_difference)) {\n            result[result_index]\
    \ = result[result_index - 1] + second_difference;\n            second_index++;\n\
    \        } else {\n            result[result_index] = result[result_index - 1]\
    \ + first_difference;\n            first_index++;\n        }\n        result_index++;\n\
    \    }\n    while (first_index < first_right) {\n        T difference = first[first_index]\
    \ - first[first_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        first_index++;\n        result_index++;\n    }\n\
    \    while (second_index < second_right) {\n        T difference = second[second_index]\
    \ - second[second_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        second_index++;\n        result_index++;\n    }\n\
    \    return result;\n}\n\ntemplate <class T, class Compare>\nbool is_structured_sequence_with_infinity(const\
    \ std::vector<T>& sequence,\n                                          const T&\
    \ infinity, Compare violation) {\n    auto [left, right] = finite_interval(sequence,\
    \ infinity);\n    for (int i = left; i < right; i++) {\n        if (sequence[i]\
    \ == infinity) return false;\n    }\n    for (int i = left + 1; i + 1 < right;\
    \ i++) {\n        T first_difference = sequence[i] - sequence[i - 1];\n      \
    \  T second_difference = sequence[i + 1] - sequence[i];\n        if (violation(first_difference,\
    \ second_difference)) return false;\n    }\n    return true;\n}\n\n}  // namespace\
    \ convolution_detail\n\ntemplate <class T>\nbool is_convex_sequence(const std::vector<T>&\
    \ sequence) {\n    for (int i = 1; i + 1 < int(sequence.size()); i++) {\n    \
    \    if (sequence[i] - sequence[i - 1] > sequence[i + 1] - sequence[i]) {\n  \
    \          return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class\
    \ T>\nbool is_convex_sequence(const std::vector<T>& sequence, const T& infinity)\
    \ {\n    return convolution_detail::is_structured_sequence_with_infinity(\n  \
    \      sequence, infinity, std::greater<>());\n}\n\ntemplate <class T>\nbool is_concave_sequence(const\
    \ std::vector<T>& sequence) {\n    for (int i = 1; i + 1 < int(sequence.size());\
    \ i++) {\n        if (sequence[i] - sequence[i - 1] < sequence[i + 1] - sequence[i])\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class T>\nbool is_concave_sequence(const std::vector<T>& sequence,\n      \
    \                   const T& negative_infinity) {\n    return convolution_detail::is_structured_sequence_with_infinity(\n\
    \        sequence, negative_infinity, std::less<>());\n}\n\ntemplate <class T>\n\
    std::vector<T> min_plus_convolution_convex(const std::vector<T>& arbitrary,\n\
    \                                           const std::vector<T>& convex) {\n\
    \    auto add = [](const T& first, const T& second) { return first + second; };\n\
    \    return convolution_detail::structured_convolution(arbitrary, convex,\n  \
    \                                                    std::less<>(), add);\n}\n\
    \ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex(const std::vector<T>&\
    \ arbitrary,\n                                           const std::vector<T>&\
    \ convex,\n                                           const T& infinity) {\n \
    \   return convolution_detail::structured_convolution_with_infinity(\n       \
    \ arbitrary, convex, infinity, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ min_plus_convolution_convex_convex(const std::vector<T>& first,\n          \
    \                                        const std::vector<T>& second) {\n   \
    \ return convolution_detail::linear_structured_convolution(first, second, std::less<>());\n\
    }\n\ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex_convex(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ infinity) {\n    return convolution_detail::linear_structured_convolution_with_infinity(\n\
    \        first, second, infinity, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ max_plus_convolution_concave(const std::vector<T>& arbitrary,\n            \
    \                                const std::vector<T>& concave) {\n    auto add\
    \ = [](const T& first, const T& second) { return first + second; };\n    return\
    \ convolution_detail::structured_convolution(arbitrary, concave,\n           \
    \                                           std::greater<>(), add);\n}\n\ntemplate\
    \ <class T>\nstd::vector<T> max_plus_convolution_concave(const std::vector<T>&\
    \ arbitrary,\n                                            const std::vector<T>&\
    \ concave,\n                                            const T& negative_infinity)\
    \ {\n    return convolution_detail::structured_convolution_with_infinity(\n  \
    \      arbitrary, concave, negative_infinity, std::greater<>());\n}\n\ntemplate\
    \ <class T>\nstd::vector<T> max_plus_convolution_concave_concave(const std::vector<T>&\
    \ first,\n                                                    const std::vector<T>&\
    \ second) {\n    return convolution_detail::linear_structured_convolution(first,\
    \ second, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave_concave(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ negative_infinity) {\n    return convolution_detail::linear_structured_convolution_with_infinity(\n\
    \        first, second, negative_infinity, std::greater<>());\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n#endif  // M1UNE_CONVEX_MONGE_MIN_PLUS_CONVOLUTION_HPP\n"
  dependsOn:
  - convex/monge/smawk.hpp
  isVerificationFile: false
  path: convex/monge/min_plus_convolution.hpp
  requiredBy:
  - convex/monge/all.hpp
  - convex/all.hpp
  timestamp: '2026-07-07 18:38:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/max_plus_convolution_concave_concave.test.cpp
  - verify/convex/monge/min_plus_convolution_convex_arbitrary.test.cpp
  - verify/convex/monge/max_plus_convolution_concave_arbitrary.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/min_plus_convolution_convex_convex.test.cpp
  - verify/convex/monge/monge_dp_optimization.test.cpp
documentation_of: convex/monge/min_plus_convolution.hpp
layout: document
title: Structured Min-Plus and Max-Plus Convolution
---

## Overview

For arrays `a` and `b`, min-plus convolution is

$$
c[k] = \min_{i+j=k}(a[i] + b[j]).
$$

When `b` is a discrete convex sequence, the minimizing index in `a` is
nondecreasing with `k`. `min_plus_convolution_convex` applies SMAWK to this
implicit Monge matrix and computes every minimum in linear time. Only the second
sequence must be convex; the first may be arbitrary.

The header also provides the symmetric `max_plus_convolution_concave`. Only its
second sequence must be concave, meaning that its adjacent differences are
nonincreasing.

When both inputs are structured,
`min_plus_convolution_convex_convex` and
`max_plus_convolution_concave_concave` merge their adjacent differences
directly. These specializations have the same linear asymptotic complexity but
smaller constants than the SMAWK-based one-sided functions.

## Functions

```cpp
template <class T>
std::vector<T> min_plus_convolution_convex(
    const std::vector<T>& arbitrary,
    const std::vector<T>& convex
);

template <class T>
std::vector<T> min_plus_convolution_convex(
    const std::vector<T>& arbitrary,
    const std::vector<T>& convex,
    const T& infinity
);

template <class T>
std::vector<T> min_plus_convolution_convex_convex(
    const std::vector<T>& first,
    const std::vector<T>& second
);

template <class T>
std::vector<T> min_plus_convolution_convex_convex(
    const std::vector<T>& first,
    const std::vector<T>& second,
    const T& infinity
);

template <class T>
std::vector<T> max_plus_convolution_concave(
    const std::vector<T>& arbitrary,
    const std::vector<T>& concave
);

template <class T>
std::vector<T> max_plus_convolution_concave(
    const std::vector<T>& arbitrary,
    const std::vector<T>& concave,
    const T& negative_infinity
);

template <class T>
std::vector<T> max_plus_convolution_concave_concave(
    const std::vector<T>& first,
    const std::vector<T>& second
);

template <class T>
std::vector<T> max_plus_convolution_concave_concave(
    const std::vector<T>& first,
    const std::vector<T>& second,
    const T& negative_infinity
);
```

For `min_plus_convolution_convex`, the first sequence is arbitrary and the
second must have nondecreasing adjacent differences. For
`max_plus_convolution_concave`, the first sequence is arbitrary and the second
must have nonincreasing adjacent differences. Both inputs to the specialized
functions must have the corresponding structure.

The three-argument overloads treat the last argument as an absorbing extended
value. For min-plus, `infinity + x` is `infinity`; for max-plus,
`negative_infinity + x` is `negative_infinity`. The finite entries of each
structured input must form one contiguous convex or concave interval. Infinity
may occur before or after that interval, so `{0, 1, infinity, infinity}` is a
valid extended convex sequence. The arbitrary input may contain the sentinel at
any indices; those candidates are omitted from SMAWK, and result indices with no
finite decomposition remain infinite. Values are recognized as infinite by
equality with the supplied sentinel, so no finite input or finite sum may equal
that value. The sentinel does not need to be the numeric maximum or minimum of
`T`.

The two-argument overloads continue to treat every value as an ordinary element
of `T`.

If either sequence is empty, the result is empty. Otherwise its length is
the sum of the input lengths minus one.

The precondition helpers are:

```cpp
template <class T>
bool is_convex_sequence(const std::vector<T>& sequence);

template <class T>
bool is_convex_sequence(
    const std::vector<T>& sequence,
    const T& infinity
);

template <class T>
bool is_concave_sequence(const std::vector<T>& sequence);

template <class T>
bool is_concave_sequence(
    const std::vector<T>& sequence,
    const T& negative_infinity
);
```

The sentinel-aware helpers check that the finite domain is contiguous in
addition to checking its adjacent differences. An all-infinity sequence is
accepted. The convolution functions do not run these checks automatically.

## Complexity

For input lengths `N` and `M`:

| Function | Time | Memory, including the result |
| --- | --- | --- |
| `min_plus_convolution_convex` | $O(N + M)$ | $O(N + M)$ |
| `min_plus_convolution_convex(..., infinity)` | $O(N + M)$ | $O(N + M)$ |
| `min_plus_convolution_convex_convex` | $O(N + M)$ | $O(N + M)$ |
| `min_plus_convolution_convex_convex(..., infinity)` | $O(N + M)$ | $O(N + M)$ |
| `max_plus_convolution_concave` | $O(N + M)$ | $O(N + M)$ |
| `max_plus_convolution_concave(..., negative_infinity)` | $O(N + M)$ | $O(N + M)$ |
| `max_plus_convolution_concave_concave` | $O(N + M)$ | $O(N + M)$ |
| `max_plus_convolution_concave_concave(..., negative_infinity)` | $O(N + M)$ | $O(N + M)$ |
| `is_convex_sequence` | $O(N)$ | $O(1)$ |
| `is_concave_sequence` | $O(N)$ | $O(1)$ |

The convolution element type must support addition and comparison. The
sentinel-aware overloads additionally require equality comparison. The
precondition helpers and two-structured specializations require subtraction.
Finite intermediate sums and adjacent differences must fit in the type.

## Example

```cpp
#include "convex/monge/min_plus_convolution.hpp"
#include <vector>

int main() {
    std::vector<long long> first = {4, -3, 8, 1};
    std::vector<long long> second = {1, 2, 5, 10};

    auto result = m1une::convex::min_plus_convolution_convex(first, second);

    std::vector<long long> another_convex = {0, 3, 8, 15};
    auto structured = m1une::convex::min_plus_convolution_convex_convex(
        another_convex, second);

    constexpr long long infinity = 2'000'000'000'000'000'000LL;
    std::vector<long long> extended_convex = {0, 1, infinity, infinity};
    auto extended = m1une::convex::min_plus_convolution_convex(
        first, extended_convex, infinity);

    std::vector<long long> first_max = {2, 9, -1, 5};
    std::vector<long long> second_concave = {-1, -2, -5, -10};
    auto maximum =
        m1une::convex::max_plus_convolution_concave(first_max, second_concave);
}
```
