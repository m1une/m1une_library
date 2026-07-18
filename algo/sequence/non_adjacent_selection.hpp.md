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
    path: verify/algo/sequence/non_adjacent_selection.test.cpp
    title: verify/algo/sequence/non_adjacent_selection.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/sequence/non_adjacent_selection.hpp\"\n\n\n\n#include\
    \ <functional>\n#include <queue>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ algo {\n\nnamespace detail {\n\ntemplate <typename T>\nstruct NonAdjacentSelectionEntry\
    \ {\n    T value;\n    int index;\n};\n\ntemplate <typename T, typename Better>\n\
    struct NonAdjacentSelectionCompare {\n    Better better;\n\n    bool operator()(\n\
    \        const NonAdjacentSelectionEntry<T>& lhs,\n        const NonAdjacentSelectionEntry<T>&\
    \ rhs\n    ) const {\n        if (better(lhs.value, rhs.value)) return false;\n\
    \        if (better(rhs.value, lhs.value)) return true;\n        return lhs.index\
    \ > rhs.index;\n    }\n};\n\ntemplate <typename T, typename Better>\nstd::vector<T>\
    \ non_adjacent_selection_sums(const std::vector<T>& values, Better better) {\n\
    \    const int n = int(values.size());\n    std::vector<T> weight = values;\n\
    \    std::vector<int> left(n), right(n);\n    std::vector<char> alive(n, true);\n\
    \    for (int i = 0; i < n; ++i) {\n        left[i] = i - 1;\n        right[i]\
    \ = (i + 1 == n ? -1 : i + 1);\n    }\n\n    using Entry = NonAdjacentSelectionEntry<T>;\n\
    \    using Compare = NonAdjacentSelectionCompare<T, Better>;\n    std::priority_queue<Entry,\
    \ std::vector<Entry>, Compare> heap(Compare{better});\n    for (int i = 0; i <\
    \ n; ++i) heap.push(Entry{weight[i], i});\n\n    std::vector<T> result;\n    result.reserve((n\
    \ + 1) / 2);\n    T sum{};\n    while (int(result.size()) < (n + 1) / 2) {\n \
    \       while (!alive[heap.top().index]) heap.pop();\n        const int current\
    \ = heap.top().index;\n        heap.pop();\n\n        sum += weight[current];\n\
    \        result.push_back(sum);\n\n        const int l = left[current];\n    \
    \    const int r = right[current];\n        if (l != -1 && r != -1) {\n      \
    \      weight[current] = weight[l] + weight[r] - weight[current];\n\n        \
    \    const int ll = left[l];\n            const int rr = right[r];\n         \
    \   alive[l] = false;\n            alive[r] = false;\n            left[current]\
    \ = ll;\n            right[current] = rr;\n            if (ll != -1) right[ll]\
    \ = current;\n            if (rr != -1) left[rr] = current;\n            heap.push(Entry{weight[current],\
    \ current});\n        } else {\n            const int ll = (l == -1 ? -1 : left[l]);\n\
    \            const int rr = (r == -1 ? -1 : right[r]);\n            alive[current]\
    \ = false;\n            if (l != -1) alive[l] = false;\n            if (r != -1)\
    \ alive[r] = false;\n            if (ll != -1) right[ll] = rr;\n            if\
    \ (rr != -1) left[rr] = ll;\n        }\n    }\n    return result;\n}\n\n}  //\
    \ namespace detail\n\n// Entry k - 1 is the maximum sum obtained by selecting\
    \ exactly k values, with\n// no two selected indices adjacent.\ntemplate <typename\
    \ T>\nstd::vector<T> maximum_non_adjacent_selection_sums(const std::vector<T>&\
    \ values) {\n    return detail::non_adjacent_selection_sums(values, std::greater<T>{});\n\
    }\n\n// Entry k - 1 is the minimum sum obtained by selecting exactly k values,\
    \ with\n// no two selected indices adjacent.\ntemplate <typename T>\nstd::vector<T>\
    \ minimum_non_adjacent_selection_sums(const std::vector<T>& values) {\n    return\
    \ detail::non_adjacent_selection_sums(values, std::less<T>{});\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_SEQUENCE_NON_ADJACENT_SELECTION_HPP\n#define M1UNE_ALGO_SEQUENCE_NON_ADJACENT_SELECTION_HPP\
    \ 1\n\n#include <functional>\n#include <queue>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace algo {\n\nnamespace detail {\n\ntemplate <typename T>\nstruct\
    \ NonAdjacentSelectionEntry {\n    T value;\n    int index;\n};\n\ntemplate <typename\
    \ T, typename Better>\nstruct NonAdjacentSelectionCompare {\n    Better better;\n\
    \n    bool operator()(\n        const NonAdjacentSelectionEntry<T>& lhs,\n   \
    \     const NonAdjacentSelectionEntry<T>& rhs\n    ) const {\n        if (better(lhs.value,\
    \ rhs.value)) return false;\n        if (better(rhs.value, lhs.value)) return\
    \ true;\n        return lhs.index > rhs.index;\n    }\n};\n\ntemplate <typename\
    \ T, typename Better>\nstd::vector<T> non_adjacent_selection_sums(const std::vector<T>&\
    \ values, Better better) {\n    const int n = int(values.size());\n    std::vector<T>\
    \ weight = values;\n    std::vector<int> left(n), right(n);\n    std::vector<char>\
    \ alive(n, true);\n    for (int i = 0; i < n; ++i) {\n        left[i] = i - 1;\n\
    \        right[i] = (i + 1 == n ? -1 : i + 1);\n    }\n\n    using Entry = NonAdjacentSelectionEntry<T>;\n\
    \    using Compare = NonAdjacentSelectionCompare<T, Better>;\n    std::priority_queue<Entry,\
    \ std::vector<Entry>, Compare> heap(Compare{better});\n    for (int i = 0; i <\
    \ n; ++i) heap.push(Entry{weight[i], i});\n\n    std::vector<T> result;\n    result.reserve((n\
    \ + 1) / 2);\n    T sum{};\n    while (int(result.size()) < (n + 1) / 2) {\n \
    \       while (!alive[heap.top().index]) heap.pop();\n        const int current\
    \ = heap.top().index;\n        heap.pop();\n\n        sum += weight[current];\n\
    \        result.push_back(sum);\n\n        const int l = left[current];\n    \
    \    const int r = right[current];\n        if (l != -1 && r != -1) {\n      \
    \      weight[current] = weight[l] + weight[r] - weight[current];\n\n        \
    \    const int ll = left[l];\n            const int rr = right[r];\n         \
    \   alive[l] = false;\n            alive[r] = false;\n            left[current]\
    \ = ll;\n            right[current] = rr;\n            if (ll != -1) right[ll]\
    \ = current;\n            if (rr != -1) left[rr] = current;\n            heap.push(Entry{weight[current],\
    \ current});\n        } else {\n            const int ll = (l == -1 ? -1 : left[l]);\n\
    \            const int rr = (r == -1 ? -1 : right[r]);\n            alive[current]\
    \ = false;\n            if (l != -1) alive[l] = false;\n            if (r != -1)\
    \ alive[r] = false;\n            if (ll != -1) right[ll] = rr;\n            if\
    \ (rr != -1) left[rr] = ll;\n        }\n    }\n    return result;\n}\n\n}  //\
    \ namespace detail\n\n// Entry k - 1 is the maximum sum obtained by selecting\
    \ exactly k values, with\n// no two selected indices adjacent.\ntemplate <typename\
    \ T>\nstd::vector<T> maximum_non_adjacent_selection_sums(const std::vector<T>&\
    \ values) {\n    return detail::non_adjacent_selection_sums(values, std::greater<T>{});\n\
    }\n\n// Entry k - 1 is the minimum sum obtained by selecting exactly k values,\
    \ with\n// no two selected indices adjacent.\ntemplate <typename T>\nstd::vector<T>\
    \ minimum_non_adjacent_selection_sums(const std::vector<T>& values) {\n    return\
    \ detail::non_adjacent_selection_sums(values, std::less<T>{});\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_SEQUENCE_NON_ADJACENT_SELECTION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/sequence/non_adjacent_selection.hpp
  requiredBy:
  - algo/sequence/all.hpp
  - algo/all.hpp
  timestamp: '2026-07-18 18:19:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/sequence/non_adjacent_selection.test.cpp
documentation_of: algo/sequence/non_adjacent_selection.hpp
layout: document
title: Non-Adjacent Selection Sums
---

## Overview

For every feasible positive count, this header finds the optimum sum obtained
by selecting exactly that many values from an array while never selecting two
adjacent indices.

The public namespace is `m1une::algo`.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `std::vector<T> maximum_non_adjacent_selection_sums(const std::vector<T>& values)` | Returns the maximum exact-count sums. | $O(N \log N)$ time and $O(N)$ memory |
| `std::vector<T> minimum_non_adjacent_selection_sums(const std::vector<T>& values)` | Returns the minimum exact-count sums. | $O(N \log N)$ time and $O(N)$ memory |

Both functions return a vector of length $\lceil N/2 \rceil$. Entry `k - 1` is
the optimum sum when exactly `k` values are selected, for
$1 \leq k \leq \lceil N/2 \rceil$. An empty input returns an empty vector.

`T` must be default-constructible, copyable, totally ordered, and support
addition, subtraction, and `+=`. Every input sum and intermediate contraction
value must fit in `T`.

## Algorithm

Treat each array position as an edge of a path. A set of non-adjacent positions
is then a matching. The algorithm repeatedly extracts the best edge weight from
a priority queue. If both neighboring edges exist, it contracts the three
weights `left`, `current`, and `right` into

$$
\mathrm{left} + \mathrm{right} - \mathrm{current}.
$$

This contraction preserves the remaining exact-cardinality matching optima.
Each extracted weight is the next marginal optimum, so its prefix sums are the
answers for all cardinalities. Boundary extractions simply remove the selected
edge and its one neighbor.

## Example

```cpp
#include "algo/sequence/non_adjacent_selection.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {4, 1, 7, 3};

    std::vector<long long> maximum =
        m1une::algo::maximum_non_adjacent_selection_sums(values);
    std::vector<long long> minimum =
        m1une::algo::minimum_non_adjacent_selection_sums(values);

    for (long long value : maximum) std::cout << value << ' ';
    std::cout << '\n';  // 7 11

    for (long long value : minimum) std::cout << value << ' ';
    std::cout << '\n';  // 1 4
}
```
