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
    title: Monge Optimization Guide
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/anti_monge_shortest_path.test.cpp
    title: verify/convex/monge/anti_monge_shortest_path.test.cpp
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
  bundledCode: "#line 1 \"convex/monge/anti_monge_shortest_path.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <vector>\n\n#line 1 \"convex/monge/smawk.hpp\"\
    \n\n\n\n#line 5 \"convex/monge/smawk.hpp\"\n#include <functional>\n#include <numeric>\n\
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
    \ // namespace smawk_detail\n\n// Search a fixed H x W rectangle, returning column\
    \ indices (leftmost on ties).\n// Requires total monotonicity under Compare; Monge\
    \ suffices for minima.\n// For anti-Monge minima, reverse columns in value and\
    \ map indices back.\n// O(H + W) evaluations; callbacks may be queried out of\
    \ row order.\ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int>\
    \ smawk_row_optima(int row_count, int column_count, Value value,\n           \
    \                       Compare compare = Compare()) {\n    assert(row_count >=\
    \ 0);\n    assert(column_count >= 0);\n    return smawk_detail::row_optima(\n\
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
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 9 \"convex/monge/anti_monge_shortest_path.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct AntiMongeShortestPathResult\
    \ {\n    std::vector<T> distance;\n    std::vector<int> parent;\n};\n\n// dist[j]\
    \ = min(dist[i] + cost(i, j)), where j - i >= minimum_step.\n// cost must be finite\
    \ and anti-Monge on valid rectangles; see the docs.\n// O(N log N + N * minimum_step)\
    \ time for O(1) cost evaluations.\n// In particular, minimum_step = 1 or 2 gives\
    \ O(N log N) time.\ntemplate <class T, class Cost>\nAntiMongeShortestPathResult<T>\
    \ anti_monge_shortest_path(\n    int vertex_count, Cost cost, T infinity, int\
    \ minimum_step = 1) {\n    assert(vertex_count >= 0);\n    assert(minimum_step\
    \ >= 1);\n    assert(T() < infinity);\n\n    AntiMongeShortestPathResult<T> result;\n\
    \    result.distance.assign(vertex_count, infinity);\n    result.parent.assign(vertex_count,\
    \ -1);\n    if (vertex_count == 0) return result;\n    result.distance[0] = T();\n\
    \    if (minimum_step >= vertex_count) return result;\n\n    auto relax = [&](int\
    \ from, int to) {\n        if (result.distance[from] == infinity) return;\n  \
    \      T candidate = result.distance[from] + cost(from, to);\n        if (candidate\
    \ < result.distance[to] ||\n            (candidate == result.distance[to] && from\
    \ > result.parent[to])) {\n            result.distance[to] = candidate;\n    \
    \        result.parent[to] = from;\n        }\n    };\n\n    // All pairs in this\
    \ rectangle are valid. Remove unreachable columns,\n    // then reverse the remaining\
    \ columns to turn anti-Monge into Monge.\n    auto rectangle = [&](int first,\
    \ int last, int top, int bottom) {\n        if (first == last || top == bottom)\
    \ return;\n        std::vector<int> sources;\n        for (int from = last; from\
    \ > first;) {\n            --from;\n            if (result.distance[from] != infinity)\
    \ sources.push_back(from);\n        }\n        if (sources.empty()) return;\n\
    \        if (sources.size() == 1) {\n            for (int to = top; to < bottom;\
    \ to++) relax(sources[0], to);\n            return;\n        }\n        auto argmin\
    \ = smawk_row_argmin(\n            bottom - top, int(sources.size()), [&](int\
    \ row, int column) -> T {\n                int from = sources[column];\n     \
    \           return result.distance[from] + cost(from, top + row);\n          \
    \  });\n        for (int row = 0; row < bottom - top; row++) {\n            relax(sources[argmin[row]],\
    \ top + row);\n        }\n    };\n\n    auto solve = [&](auto& self, int left,\
    \ int right) -> void {\n        // Such a block contains no valid internal edge.\n\
    \        if (right - left <= minimum_step) return;\n        int middle = left\
    \ + (right - left) / 2;\n        self(self, left, middle);\n\n        // Two valid\
    \ rectangles and a small corner partition the cross edges.\n        int source_end\
    \ = std::max(left, middle - (minimum_step - 1));\n        int target_begin = middle\
    \ + std::min(right - middle, minimum_step - 1);\n        rectangle(left, middle,\
    \ target_begin, right);\n        rectangle(left, source_end, middle, target_begin);\n\
    \        for (int from = source_end; from < middle; from++) {\n            //\
    \ Subtraction avoids overflow when minimum_step is large.\n            if (minimum_step\
    \ >= target_begin - from) continue;\n            for (int to = std::max(middle,\
    \ from + minimum_step);\n                 to < target_begin; to++) {\n       \
    \         relax(from, to);\n            }\n        }\n\n        // Incoming transitions\
    \ must be applied BEFORE solving the right half.\n        self(self, middle, right);\n\
    \    };\n    solve(solve, 0, vertex_count);\n    return result;\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_ANTI_MONGE_SHORTEST_PATH_HPP\n#define M1UNE_CONVEX_MONGE_ANTI_MONGE_SHORTEST_PATH_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#include\
    \ \"smawk.hpp\"\n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\n\
    struct AntiMongeShortestPathResult {\n    std::vector<T> distance;\n    std::vector<int>\
    \ parent;\n};\n\n// dist[j] = min(dist[i] + cost(i, j)), where j - i >= minimum_step.\n\
    // cost must be finite and anti-Monge on valid rectangles; see the docs.\n// O(N\
    \ log N + N * minimum_step) time for O(1) cost evaluations.\n// In particular,\
    \ minimum_step = 1 or 2 gives O(N log N) time.\ntemplate <class T, class Cost>\n\
    AntiMongeShortestPathResult<T> anti_monge_shortest_path(\n    int vertex_count,\
    \ Cost cost, T infinity, int minimum_step = 1) {\n    assert(vertex_count >= 0);\n\
    \    assert(minimum_step >= 1);\n    assert(T() < infinity);\n\n    AntiMongeShortestPathResult<T>\
    \ result;\n    result.distance.assign(vertex_count, infinity);\n    result.parent.assign(vertex_count,\
    \ -1);\n    if (vertex_count == 0) return result;\n    result.distance[0] = T();\n\
    \    if (minimum_step >= vertex_count) return result;\n\n    auto relax = [&](int\
    \ from, int to) {\n        if (result.distance[from] == infinity) return;\n  \
    \      T candidate = result.distance[from] + cost(from, to);\n        if (candidate\
    \ < result.distance[to] ||\n            (candidate == result.distance[to] && from\
    \ > result.parent[to])) {\n            result.distance[to] = candidate;\n    \
    \        result.parent[to] = from;\n        }\n    };\n\n    // All pairs in this\
    \ rectangle are valid. Remove unreachable columns,\n    // then reverse the remaining\
    \ columns to turn anti-Monge into Monge.\n    auto rectangle = [&](int first,\
    \ int last, int top, int bottom) {\n        if (first == last || top == bottom)\
    \ return;\n        std::vector<int> sources;\n        for (int from = last; from\
    \ > first;) {\n            --from;\n            if (result.distance[from] != infinity)\
    \ sources.push_back(from);\n        }\n        if (sources.empty()) return;\n\
    \        if (sources.size() == 1) {\n            for (int to = top; to < bottom;\
    \ to++) relax(sources[0], to);\n            return;\n        }\n        auto argmin\
    \ = smawk_row_argmin(\n            bottom - top, int(sources.size()), [&](int\
    \ row, int column) -> T {\n                int from = sources[column];\n     \
    \           return result.distance[from] + cost(from, top + row);\n          \
    \  });\n        for (int row = 0; row < bottom - top; row++) {\n            relax(sources[argmin[row]],\
    \ top + row);\n        }\n    };\n\n    auto solve = [&](auto& self, int left,\
    \ int right) -> void {\n        // Such a block contains no valid internal edge.\n\
    \        if (right - left <= minimum_step) return;\n        int middle = left\
    \ + (right - left) / 2;\n        self(self, left, middle);\n\n        // Two valid\
    \ rectangles and a small corner partition the cross edges.\n        int source_end\
    \ = std::max(left, middle - (minimum_step - 1));\n        int target_begin = middle\
    \ + std::min(right - middle, minimum_step - 1);\n        rectangle(left, middle,\
    \ target_begin, right);\n        rectangle(left, source_end, middle, target_begin);\n\
    \        for (int from = source_end; from < middle; from++) {\n            //\
    \ Subtraction avoids overflow when minimum_step is large.\n            if (minimum_step\
    \ >= target_begin - from) continue;\n            for (int to = std::max(middle,\
    \ from + minimum_step);\n                 to < target_begin; to++) {\n       \
    \         relax(from, to);\n            }\n        }\n\n        // Incoming transitions\
    \ must be applied BEFORE solving the right half.\n        self(self, middle, right);\n\
    \    };\n    solve(solve, 0, vertex_count);\n    return result;\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n#endif  // M1UNE_CONVEX_MONGE_ANTI_MONGE_SHORTEST_PATH_HPP\n"
  dependsOn:
  - convex/monge/smawk.hpp
  isVerificationFile: false
  path: convex/monge/anti_monge_shortest_path.hpp
  requiredBy:
  - convex/monge/all.hpp
  - convex/all.hpp
  timestamp: '2026-10-24 20:27:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/anti_monge_shortest_path.test.cpp
documentation_of: convex/monge/anti_monge_shortest_path.hpp
layout: document
title: Anti-Monge DAG Shortest Paths
---

## Overview

Compute a single forward DP with a minimum edge length `D = minimum_step`:

$$
dist[0]=0,\qquad dist[j]=\min_{0\le i\le j-D}(dist[i]+cost(i,j)).
$$

For sequence partitioning, vertex `j` represents prefix `[0,j)`; use
`vertex_count = sequence_length + 1`. The cost must be **anti-Monge**.
For Monge costs, see [LARSCH](https://m1une.github.io/m1une_library/convex/monge/larsch.hpp). For transitions from a known
previous DP layer, see [divide-and-conquer optimization](https://m1une.github.io/m1une_library/convex/monge/divide_and_conquer_optimization.hpp).
The [Monge guide](https://m1une.github.io/m1une_library/convex/monge/all.hpp) explains how to identify the recurrence and choose
between matrix search, previous-layer transitions, and forward DP.

All names are in `m1une::convex`.

## Worked example: forward jumps with an anti-Monge cost

Use four ordered stations `x={0,2,5,9}` and start at station 0. A forward jump
has the signed cost `-(x[to]-x[from])^2 - 20`. Find the minimum total cost
to each station. Negative costs are permitted because every jump moves
forward; there are no cycles.

Write the ordinary quadratic DP first:

```cpp
std::vector<long long> dp(x.size(), infinity);
dp[0] = 0;
for (int to = 1; to < int(x.size()); ++to) {
    for (int from = 0; from < to; ++from) {
        dp[to] = std::min(dp[to], dp[from] + jump_cost(from, to));
    }
}
```

For these inputs it computes:

| Destination `to` | Total costs through earlier stations | Minimum | Parent |
| --- | --- | --- | --- |
| 0 | Starting station | 0 | -1 |
| 1 | Through 0: `0-24=-24` | -24 | 0 |
| 2 | Through 0: `0-45=-45`; through 1: `-24-29=-53` | -53 | 1 |
| 3 | Through 0: `0-101=-101`; through 1: `-24-69=-93`; through 2: `-53-36=-89` | -101 | 0 |

Negated squared gap is anti-Monge. Use the helper to compute the same DP:

```cpp
#include "convex/monge/anti_monge_shortest_path.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> x = {0, 2, 5, 9};
    auto jump_cost = [&](int from, int to) {
        long long gap = x[to] - x[from];
        return -gap * gap - 20;
    };
    constexpr long long infinity = 1LL << 60;
    auto result = m1une::convex::anti_monge_shortest_path(
        int(x.size()), jump_cost, infinity);
    assert(result.distance == std::vector<long long>({0, -24, -53, -101}));
    assert(result.parent == std::vector<int>({-1, 0, 1, 0}));
    for (int to = 0; to < int(x.size()); ++to) {
        std::cout << result.distance[to] << ' ' << result.parent[to] << '\n';
    }

    // To recover a path, first check that the destination is reachable.
    if (result.distance[3] != infinity) {
        std::vector<int> path;
        for (int v = 3; v != -1; v = result.parent[v]) path.push_back(v);
        std::reverse(path.begin(), path.end());
        assert(path == std::vector<int>({0, 3}));
    }

    // Optional fourth argument: allow only jumps advancing >=2 station indices.
    auto restricted = m1une::convex::anti_monge_shortest_path(
        int(x.size()), jump_cost, infinity, 2);
    assert(restricted.distance ==
           std::vector<long long>({0, infinity, -45, -101}));
    assert(restricted.parent[1] == -1);  // Station 1 is unreachable.
}
```

Output (minimum cost, previous station on an optimal path):

```text
0 -1
-24 0
-53 1
-101 0
```

Pass the number of vertices, an **edge-cost** callback, and an unreachable
sentinel. The callback receives source and destination **indices**, and
returns only their edge cost. The helper manages all source distances. Read
`.distance[to]` for the minimum and `.parent[to]` for a chosen predecessor.

For your own problem, replace `jump_cost` after proving it is anti-Monge on
valid rectangles. Adding source- or destination-dependent costs preserves
that inequality. The optional minimum step is measured in **indices**;
it is unrelated to coordinate distance. The default `1` permits every forward
edge. The helper's time is $O(V\log V+VD)$ and memory is $O(V)$, where `D`
is the minimum step. Exact graph and numeric restrictions follow below.

## Interface

| Signature | Meaning | Complexity |
| --- | --- | --- |
| `template <class T, class Cost> AntiMongeShortestPathResult<T> anti_monge_shortest_path(int vertex_count, Cost cost, T infinity, int minimum_step = 1)` | Compute distances from vertex `0` and optimal predecessors. | $O(V\log V + VD)$ time, $O(V)$ additional memory, for constant-time cost evaluations. |

`AntiMongeShortestPathResult<T>` contains:

| Member | Meaning |
| --- | --- |
| `std::vector<T> distance` | Distances; unreachable vertices have value `infinity`. |
| `std::vector<int> parent` | Largest predecessor attaining the minimum, or `-1` for the source and unreachable vertices. |

Inputs are not modified. An empty graph returns empty vectors; one vertex
returns distance `0` and parent `-1`. If `D >= V`, only vertex `0` is
reachable. Preconditions: `vertex_count >= 0`, `minimum_step >= 1`.

## Requirements

For `a < b`, `c < d`, and `b + D <= c`, require

$$
cost(a,c)+cost(b,d)\ge cost(a,d)+cost(b,c).
$$

Every fully valid rectangle of the source/destination matrix must be
anti-Monge. The implementation does not check this. All edges satisfying
`to - from >= D` exist and have finite costs. Other missing edges or a maximum
edge length are not supported.

`cost(from,to)` is called only for a reachable source and
`0 <= from < to < vertex_count`, `to - from >= D`. It must return a fixed
cost convertible to `T`; repeated evaluations in arbitrary order are allowed.
Negative costs are allowed because edges always go forward.

`T()` represents zero. `T` must support addition, equality, and ordering.
Choose `infinity > 0` strictly larger than every finite path value and
transition sum encountered. Those sums must fit in `T`. The helper never
adds to `infinity`: it removes unreachable sources before matrix search.
The sentinel does not permit infinite edge costs.

## Algorithm and complexity

For a block `[l,r)`, split at `m`: solve `[l,m)`, relax all valid cross edges,
then solve `[m,r)`. Incoming transitions must precede solving the right half.
The generic `algo::cdq_divide_and_conquer` uses a different callback order
and cannot replace this recursion directly.

For each valid cross rectangle, rows are destinations and columns are reachable
sources **in decreasing order**. Transposing preserves anti-Monge, reversing
columns makes it Monge, and adding finalized source distances as column
constants preserves Monge. SMAWK finds all row minima with linear work.
Its leftmost tie rule selects the largest original source index.

Let `p = max(l,m-D+1)` and `q = min(r,m+D-1)`. The cross edges partition into
two valid rectangles, `[l,m) -> [q,r)` and `[l,p) -> [m,q)`, and valid pairs
in the small corner `[p,m) -> [m,q)`. Scan the corner directly. No invalid
cells are padded with infinity.

Rectangle work totals $O(V\log V)$. Recursion stops at blocks of size at most
`D`; there are $O(V/D)$ larger blocks, each with at most $O(D^2)$ corner
pairs, giving $O(VD)$ corner work. For `D = 1` or `2`, the corner has no
valid edges and total time is $O(V\log V)$. For large `D`, the $VD$ term
matters: this interface does not guarantee $O(V\log V)$ independently of `D`.
