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
    path: verify/algo/offline/parallel_binary_search.test.cpp
    title: verify/algo/offline/parallel_binary_search.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/offline/parallel_binary_search.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace algo {\n\ntemplate\
    \ <class Apply, class Check, class Reset>\nstd::vector<int> parallel_binary_search(\n\
    \    int query_count,\n    int event_count,\n    Apply apply,\n    Check check,\n\
    \    Reset reset\n) {\n    assert(0 <= query_count);\n    assert(0 <= event_count);\n\
    \n    std::vector<int> low(query_count, -1);\n    std::vector<int> high(query_count,\
    \ event_count + 1);\n    std::vector<std::vector<int>> bucket(event_count + 1);\n\
    \n    while (true) {\n        bool active = false;\n        for (auto& queries\
    \ : bucket) queries.clear();\n\n        for (int query = 0; query < query_count;\
    \ ++query) {\n            if (high[query] - low[query] <= 1) continue;\n     \
    \       const int middle = low[query] + (high[query] - low[query]) / 2;\n    \
    \        bucket[middle].push_back(query);\n            active = true;\n      \
    \  }\n        if (!active) break;\n\n        reset();\n        int applied = 0;\n\
    \        for (int middle = 0; middle <= event_count; ++middle) {\n           \
    \ while (applied < middle) {\n                apply(applied);\n              \
    \  ++applied;\n            }\n            for (int query : bucket[middle]) {\n\
    \                if (check(query)) {\n                    high[query] = middle;\n\
    \                } else {\n                    low[query] = middle;\n        \
    \        }\n            }\n        }\n    }\n\n    return high;\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_OFFLINE_PARALLEL_BINARY_SEARCH_HPP\n#define M1UNE_ALGO_OFFLINE_PARALLEL_BINARY_SEARCH_HPP\
    \ 1\n\n#include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace algo\
    \ {\n\ntemplate <class Apply, class Check, class Reset>\nstd::vector<int> parallel_binary_search(\n\
    \    int query_count,\n    int event_count,\n    Apply apply,\n    Check check,\n\
    \    Reset reset\n) {\n    assert(0 <= query_count);\n    assert(0 <= event_count);\n\
    \n    std::vector<int> low(query_count, -1);\n    std::vector<int> high(query_count,\
    \ event_count + 1);\n    std::vector<std::vector<int>> bucket(event_count + 1);\n\
    \n    while (true) {\n        bool active = false;\n        for (auto& queries\
    \ : bucket) queries.clear();\n\n        for (int query = 0; query < query_count;\
    \ ++query) {\n            if (high[query] - low[query] <= 1) continue;\n     \
    \       const int middle = low[query] + (high[query] - low[query]) / 2;\n    \
    \        bucket[middle].push_back(query);\n            active = true;\n      \
    \  }\n        if (!active) break;\n\n        reset();\n        int applied = 0;\n\
    \        for (int middle = 0; middle <= event_count; ++middle) {\n           \
    \ while (applied < middle) {\n                apply(applied);\n              \
    \  ++applied;\n            }\n            for (int query : bucket[middle]) {\n\
    \                if (check(query)) {\n                    high[query] = middle;\n\
    \                } else {\n                    low[query] = middle;\n        \
    \        }\n            }\n        }\n    }\n\n    return high;\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_OFFLINE_PARALLEL_BINARY_SEARCH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/offline/parallel_binary_search.hpp
  requiredBy:
  - algo/all.hpp
  - algo/offline/all.hpp
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/offline/parallel_binary_search.test.cpp
documentation_of: algo/offline/parallel_binary_search.hpp
layout: document
title: Parallel Binary Search
---

## Overview

`parallel_binary_search` solves many monotone prefix-decision queries at once.
It repeatedly resets a mutable state, applies events in increasing order, and
checks the queries whose current midpoint is that prefix length.

The public namespace is `m1une::algo`.

## Function

```cpp
template <class Apply, class Check, class Reset>
std::vector<int> parallel_binary_search(
    int query_count,
    int event_count,
    Apply apply,
    Check check,
    Reset reset
);
```

For each query, the return value is the minimum `k` such that the query is true
after applying events `[0, k)`. If a query is never true, its answer is
`event_count + 1`.

Callbacks:

| Callback | Meaning |
| --- | --- |
| `reset()` | Clears the mutable state to the zero-event state. |
| `apply(event)` | Applies event `event`; events are passed in increasing order inside each round. |
| `check(query)` | Returns whether query `query` is true in the current state. |

The complexity is $O((E + Q)\log(E + 1))$ callback invocations, where $E$ is
`event_count` and $Q$ is `query_count`.

## Example

```cpp
#include "algo/offline/parallel_binary_search.hpp"

#include <vector>

int main() {
    std::vector<int> add = {3, 1, 4};
    std::vector<int> need = {0, 4, 9};
    int current = 0;

    std::vector<int> answer = m1une::algo::parallel_binary_search(
        int(need.size()),
        int(add.size()),
        [&](int event) {
            current += add[event];
        },
        [&](int query) {
            return need[query] <= current;
        },
        [&]() {
            current = 0;
        }
    );
}
```
