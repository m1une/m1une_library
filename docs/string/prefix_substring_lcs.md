---
title: Prefix-Substring LCS
documentation_of: ../../string/prefix_substring_lcs.hpp
---

## Overview

`PrefixSubstringLcs` records queries for the length of a longest common
subsequence of `first[0..a)` and `second[b..c)`, then evaluates the complete
batch efficiently. Answers are returned in query insertion order.

The structure uses a seaweed permutation for semi-local LCS and processes the
queries offline. It stores copies of both input sequences. Each sequence must
provide `size()` and `operator[]`, and `first[i] == second[j]` must be valid.

Let `N = first.size()`, `M = second.size()`, `Q` be the number of queries, and
`A` be the number of distinct positive prefix lengths that have a nonempty
substring query.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PrefixSubstringLcs(FirstSequence first, SecondSequence second)` | Copies or moves the two sequences. | `O(N + M)` |
| `int first_size() const` | Returns `N`. | `O(1)` |
| `int second_size() const` | Returns `M`. | `O(1)` |
| `int query_count() const` | Returns the number of recorded queries. | `O(1)` |
| `bool empty() const` | Returns whether no queries are recorded. | `O(1)` |
| `void reserve(int query_capacity)` | Reserves storage for queries. | `O(Q)` worst case |
| `void clear()` | Removes all queries while preserving the two sequences. | `O(Q)` |
| `int add_query(int a, int b, int c)` | Records `LCS(first[0..a), second[b..c))` and returns its insertion-order ID. | Amortized `O(1)` |
| `vector<int> calculate() const` | Returns all recorded answers in insertion order. | `O(NM + (AM + Q) log(M + 1))` |

`calculate()` uses `O(N + M + Q)` auxiliary memory. Its worst-case time is
`O((NM + Q) log(M + 1))`. It does not mutate the object, so it may be called more
than once. An empty prefix or empty substring has answer zero.

Indices are zero-based and substring ranges are half-open. A query must satisfy
`0 <= a <= N` and `0 <= b <= c <= M`.

## Example

```cpp
#include "string/prefix_substring_lcs.hpp"

#include <iostream>
#include <string>

int main() {
    std::string first = "abac";
    std::string second = "cababa";
    m1une::string::PrefixSubstringLcs solver(first, second);

    solver.add_query(3, 1, 5);
    solver.add_query(4, 0, 3);
    for (int answer : solver.calculate()) {
        std::cout << answer << "\n";
    }
}
```
