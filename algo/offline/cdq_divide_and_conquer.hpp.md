---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  - icon: ':warning:'
    path: algo/offline/all.hpp
    title: Offline Algorithms All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/algo/offline/cdq_divide_and_conquer.test.cpp
    title: verify/algo/offline/cdq_divide_and_conquer.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/offline/cdq_divide_and_conquer.hpp\"\n\n\n\n#include\
    \ <cassert>\n\nnamespace m1une {\nnamespace algo {\n\ntemplate <class SolveCross>\n\
    void cdq_divide_and_conquer(int left, int right, SolveCross solve_cross) {\n \
    \   assert(left <= right);\n\n    auto dfs = [&](auto& self, int l, int r) ->\
    \ void {\n        if (r - l <= 1) return;\n        const int middle = l + (r -\
    \ l) / 2;\n        self(self, l, middle);\n        self(self, middle, r);\n  \
    \      solve_cross(l, middle, r);\n    };\n    dfs(dfs, left, right);\n}\n\ntemplate\
    \ <class SolveCross>\nvoid cdq_divide_and_conquer(int n, SolveCross solve_cross)\
    \ {\n    assert(0 <= n);\n    cdq_divide_and_conquer(0, n, solve_cross);\n}\n\n\
    }  // namespace algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_OFFLINE_CDQ_DIVIDE_AND_CONQUER_HPP\n#define M1UNE_ALGO_OFFLINE_CDQ_DIVIDE_AND_CONQUER_HPP\
    \ 1\n\n#include <cassert>\n\nnamespace m1une {\nnamespace algo {\n\ntemplate <class\
    \ SolveCross>\nvoid cdq_divide_and_conquer(int left, int right, SolveCross solve_cross)\
    \ {\n    assert(left <= right);\n\n    auto dfs = [&](auto& self, int l, int r)\
    \ -> void {\n        if (r - l <= 1) return;\n        const int middle = l + (r\
    \ - l) / 2;\n        self(self, l, middle);\n        self(self, middle, r);\n\
    \        solve_cross(l, middle, r);\n    };\n    dfs(dfs, left, right);\n}\n\n\
    template <class SolveCross>\nvoid cdq_divide_and_conquer(int n, SolveCross solve_cross)\
    \ {\n    assert(0 <= n);\n    cdq_divide_and_conquer(0, n, solve_cross);\n}\n\n\
    }  // namespace algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_OFFLINE_CDQ_DIVIDE_AND_CONQUER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/offline/cdq_divide_and_conquer.hpp
  requiredBy:
  - algo/all.hpp
  - algo/offline/all.hpp
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/offline/cdq_divide_and_conquer.test.cpp
documentation_of: algo/offline/cdq_divide_and_conquer.hpp
layout: document
title: CDQ Divide And Conquer
---

## Overview

`cdq_divide_and_conquer` provides the standard recursive shape for offline CDQ
algorithms. It solves the left half, solves the right half, and then calls a
user callback for cross contributions from `[left, middle)` to `[middle, right)`.

The public namespace is `m1une::algo`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `cdq_divide_and_conquer(left, right, solve_cross)` | Runs CDQ on `[left, right)`. | $O(N)$ recursion overhead plus callbacks |
| `cdq_divide_and_conquer(n, solve_cross)` | Runs CDQ on `[0, n)`. | $O(N)$ recursion overhead plus callbacks |

The callback signature is `solve_cross(int left, int middle, int right)`.
Sorting, Fenwick updates, and rollback are intentionally left to the callback,
because those details depend on the offline problem.

## Example

```cpp
#include "algo/offline/cdq_divide_and_conquer.hpp"

#include <vector>

int main() {
    std::vector<int> a = {3, 1, 2};
    long long inversions = 0;

    m1une::algo::cdq_divide_and_conquer(int(a.size()), [&](int l, int m, int r) {
        for (int i = l; i < m; ++i) {
            for (int j = m; j < r; ++j) {
                if (a[j] < a[i]) ++inversions;
            }
        }
    });
}
```
