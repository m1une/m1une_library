---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: monge/all.hpp
    title: Monge All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/monge/min_plus_convolution_convex_convex.test.cpp
    title: verify/monge/min_plus_convolution_convex_convex.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_algorithms.test.cpp
    title: verify/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_dp_optimization.test.cpp
    title: verify/monge/monge_dp_optimization.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monge/min_plus_convolution.hpp\"\n\n\n\n#include <functional>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace monge {\n\nnamespace convolution_detail\
    \ {\n\ntemplate <class T, class Compare>\nstd::vector<T> structured_convolution(const\
    \ std::vector<T>& arbitrary,\n                                      const std::vector<T>&\
    \ structured,\n                                      Compare compare) {\n    if\
    \ (arbitrary.empty() || structured.empty()) return {};\n\n    int first_size =\
    \ int(arbitrary.size());\n    int second_size = int(structured.size());\n    int\
    \ result_size = first_size + second_size - 1;\n    std::vector<T> result(result_size);\n\
    \n    auto solve = [&](auto self, int result_left, int result_right, int candidate_left,\n\
    \                     int candidate_right) -> void {\n        if (result_left\
    \ == result_right) return;\n        int index = (result_left + result_right) /\
    \ 2;\n        int left = candidate_left > index - second_size + 1 ? candidate_left\n\
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
    \ std::vector<T>& second) {\n    if (first.empty() || second.empty()) return {};\n\
    \n    int first_size = int(first.size());\n    int second_size = int(second.size());\n\
    \    std::vector<T> result(first_size + second_size - 1);\n    result[0] = first[0]\
    \ + second[0];\n\n    int first_index = 1;\n    int second_index = 1;\n    int\
    \ result_index = 1;\n    while (first_index < first_size && second_index < second_size)\
    \ {\n        T first_difference = first[first_index] - first[first_index - 1];\n\
    \        T second_difference = second[second_index] - second[second_index - 1];\n\
    \        if (second_difference < first_difference) {\n            result[result_index]\
    \ = result[result_index - 1] + second_difference;\n            second_index++;\n\
    \        } else {\n            result[result_index] = result[result_index - 1]\
    \ + first_difference;\n            first_index++;\n        }\n        result_index++;\n\
    \    }\n    while (first_index < first_size) {\n        T difference = first[first_index]\
    \ - first[first_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        first_index++;\n        result_index++;\n    }\n\
    \    while (second_index < second_size) {\n        T difference = second[second_index]\
    \ - second[second_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        second_index++;\n        result_index++;\n    }\n\
    \    return result;\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave(const\
    \ std::vector<T>& arbitrary,\n                                            const\
    \ std::vector<T>& concave) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ concave, std::greater<>());\n}\n\n}  // namespace monge\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP\n#define M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP\
    \ 1\n\n#include <functional>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ monge {\n\nnamespace convolution_detail {\n\ntemplate <class T, class Compare>\n\
    std::vector<T> structured_convolution(const std::vector<T>& arbitrary,\n     \
    \                                 const std::vector<T>& structured,\n        \
    \                              Compare compare) {\n    if (arbitrary.empty() ||\
    \ structured.empty()) return {};\n\n    int first_size = int(arbitrary.size());\n\
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
    \ std::vector<T>& second) {\n    if (first.empty() || second.empty()) return {};\n\
    \n    int first_size = int(first.size());\n    int second_size = int(second.size());\n\
    \    std::vector<T> result(first_size + second_size - 1);\n    result[0] = first[0]\
    \ + second[0];\n\n    int first_index = 1;\n    int second_index = 1;\n    int\
    \ result_index = 1;\n    while (first_index < first_size && second_index < second_size)\
    \ {\n        T first_difference = first[first_index] - first[first_index - 1];\n\
    \        T second_difference = second[second_index] - second[second_index - 1];\n\
    \        if (second_difference < first_difference) {\n            result[result_index]\
    \ = result[result_index - 1] + second_difference;\n            second_index++;\n\
    \        } else {\n            result[result_index] = result[result_index - 1]\
    \ + first_difference;\n            first_index++;\n        }\n        result_index++;\n\
    \    }\n    while (first_index < first_size) {\n        T difference = first[first_index]\
    \ - first[first_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        first_index++;\n        result_index++;\n    }\n\
    \    while (second_index < second_size) {\n        T difference = second[second_index]\
    \ - second[second_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        second_index++;\n        result_index++;\n    }\n\
    \    return result;\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave(const\
    \ std::vector<T>& arbitrary,\n                                            const\
    \ std::vector<T>& concave) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ concave, std::greater<>());\n}\n\n}  // namespace monge\n}  // namespace m1une\n\
    \n#endif  // M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monge/min_plus_convolution.hpp
  requiredBy:
  - monge/all.hpp
  timestamp: '2026-07-05 05:07:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monge/monge_algorithms.test.cpp
  - verify/monge/min_plus_convolution_convex_convex.test.cpp
  - verify/monge/monge_dp_optimization.test.cpp
documentation_of: monge/min_plus_convolution.hpp
layout: document
title: Structured Min-Plus Convolution
---

## Overview

For arrays `a` and `b`, min-plus convolution is

$$
c[k] = \min_{i+j=k}(a[i] + b[j]).
$$

When `b` is a discrete convex sequence, the minimizing index in `a` is
nondecreasing with `k`. `min_plus_convolution_convex` uses this Monge structure
to avoid the naive quadratic algorithm. When both sequences are convex,
`min_plus_convolution_convex_convex` merges their nondecreasing adjacent
differences and runs in linear time.

The header also provides the symmetric max-plus operation when the second
sequence is concave.

## Functions

```cpp
template <class T>
std::vector<T> min_plus_convolution_convex(
    const std::vector<T>& arbitrary,
    const std::vector<T>& convex
);

template <class T>
std::vector<T> min_plus_convolution_convex_convex(
    const std::vector<T>& first,
    const std::vector<T>& second
);

template <class T>
std::vector<T> max_plus_convolution_concave(
    const std::vector<T>& arbitrary,
    const std::vector<T>& concave
);
```

For `min_plus_convolution_convex`, the first sequence is arbitrary and the
second must have nondecreasing adjacent differences. Both arguments to
`min_plus_convolution_convex_convex` must have nondecreasing adjacent
differences. For max-plus, the first sequence is arbitrary and the second must
have nonincreasing adjacent differences.

If either sequence is empty, the result is empty. Otherwise its length is
the sum of the input lengths minus one.

The precondition helpers are:

```cpp
template <class T>
bool is_convex_sequence(const std::vector<T>& sequence);

template <class T>
bool is_concave_sequence(const std::vector<T>& sequence);
```

Sequences of length at most two satisfy both properties. The convolution
functions do not run these checks automatically.

## Complexity

For input lengths `N` and `M`:

| Function | Time | Memory, including the result |
| --- | --- | --- |
| `min_plus_convolution_convex` | $O((N + M)\log(N + M))$ | $O(N + M)$ |
| `min_plus_convolution_convex_convex` | $O(N + M)$ | $O(N + M)$ |
| `max_plus_convolution_concave` | $O((N + M)\log(N + M))$ | $O(N + M)$ |
| `is_convex_sequence` | $O(N)$ | $O(1)$ |
| `is_concave_sequence` | $O(N)$ | $O(1)$ |

The element type must support addition, subtraction, and comparison.
Intermediate values and adjacent differences must fit in the type.

## Example

```cpp
#include "monge/min_plus_convolution.hpp"
#include <vector>

int main() {
    std::vector<long long> first = {0, 2, 7, 15};
    std::vector<long long> second = {1, 2, 5, 10};

    auto result = m1une::monge::min_plus_convolution_convex_convex(first,
                                                                   second);
}
```
