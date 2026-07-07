---
title: Parallel Binary Search
documentation_of: ../../../algo/offline/parallel_binary_search.hpp
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
