---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  - icon: ':warning:'
    path: algo/sequence/all.hpp
    title: Sequence Algorithms All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/algo/sequence/sequence_algorithms.test.cpp
    title: verify/algo/sequence/sequence_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/sequence/run_length_encoding.hpp\"\n\n\n\n#include\
    \ <iterator>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ algo {\n\ntemplate <typename Container>\nauto run_length_encoding(const Container&\
    \ values) {\n    using T = typename Container::value_type;\n    std::vector<std::pair<T,\
    \ long long>> result;\n\n    auto it = std::begin(values);\n    auto last = std::end(values);\n\
    \    if (it == last) {\n        return result;\n    }\n\n    T current = *it;\n\
    \    long long count = 0;\n    for (; it != last; ++it) {\n        if (*it ==\
    \ current) {\n            ++count;\n        } else {\n            result.emplace_back(current,\
    \ count);\n            current = *it;\n            count = 1;\n        }\n   \
    \ }\n    result.emplace_back(current, count);\n    return result;\n}\n\n}  //\
    \ namespace algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_SEQUENCE_RUN_LENGTH_ENCODING_HPP\n#define M1UNE_ALGO_SEQUENCE_RUN_LENGTH_ENCODING_HPP\
    \ 1\n\n#include <iterator>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace algo {\n\ntemplate <typename Container>\nauto run_length_encoding(const\
    \ Container& values) {\n    using T = typename Container::value_type;\n    std::vector<std::pair<T,\
    \ long long>> result;\n\n    auto it = std::begin(values);\n    auto last = std::end(values);\n\
    \    if (it == last) {\n        return result;\n    }\n\n    T current = *it;\n\
    \    long long count = 0;\n    for (; it != last; ++it) {\n        if (*it ==\
    \ current) {\n            ++count;\n        } else {\n            result.emplace_back(current,\
    \ count);\n            current = *it;\n            count = 1;\n        }\n   \
    \ }\n    result.emplace_back(current, count);\n    return result;\n}\n\n}  //\
    \ namespace algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_SEQUENCE_RUN_LENGTH_ENCODING_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/sequence/run_length_encoding.hpp
  requiredBy:
  - algo/all.hpp
  - algo/sequence/all.hpp
  timestamp: '2026-07-07 21:49:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/sequence/sequence_algorithms.test.cpp
documentation_of: algo/sequence/run_length_encoding.hpp
layout: document
title: Run Length Encoding
---

## Overview

Compresses consecutive equal values into `(value, count)` pairs. It works with containers such as `std::vector` and `std::string`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `run_length_encoding(container)` | Returns `vector<pair<T, long long>>` for consecutive runs. | $O(N)$ |

## Example

```cpp
#include "algo/sequence/run_length_encoding.hpp"
#include <string>

int main() {
    std::string s = "aaabbc";
    auto runs = m1une::algo::run_length_encoding(s);
    // ('a', 3), ('b', 2), ('c', 1)
}
```
