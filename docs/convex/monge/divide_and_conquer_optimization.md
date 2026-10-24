---
title: Divide-and-Conquer DP Optimization
documentation_of: ../../../convex/monge/divide_and_conquer_optimization.hpp
---

## Overview

Divide-and-conquer DP optimization computes

$$
dp[i] = \min_j A(i,j)
$$

when the leftmost minimizing index is nondecreasing with `i`. It evaluates only
a narrowed candidate interval for each recursive subproblem.

This header is the DP-facing wrapper around `monotone_row_argmin`: it returns
both optimum values and their candidate indices.

This is a **fixed-matrix / previous-layer** optimization. It does not solve
`dp[j] = min_{i<j}(dp[i] + cost(i,j))` by reading unfinished values in the
same array. Use [LARSCH](https://m1une.github.io/m1une_library/convex/monge/larsch.hpp) for Monge costs, or
[anti-Monge shortest paths](https://m1une.github.io/m1une_library/convex/monge/anti_monge_shortest_path.hpp) for anti-Monge costs.
The [Monge guide](https://m1une.github.io/m1une_library/convex/monge/all.hpp) explains how to distinguish these recurrences.

## Worked example: make one more move from known costs

There are three possible starting positions `0,1,2`. You already know the
cheapest cost to reach them: `previous = {0,2,1}`. Now make one more move to
each of four positions `0,1,2,3`. Moving from position `i` to position `j`
costs `(j-i)^2`; every start can move to every destination.

You want `next[j] = min_i(previous[i] + (j-i)^2)`. For these inputs:

| Destination `j` | Start 0: `0+j^2` | Start 1: `2+(j-1)^2` | Start 2: `1+(j-2)^2` | Best start | `next[j]` |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 3 | 5 | 0 | 0 |
| 1 | 1 | 2 | 2 | 0 | 1 |
| 2 | 4 | 3 | 1 | 2 | 1 |
| 3 | 9 | 6 | 2 | 2 | 2 |

The straightforward implementation is:

```cpp
for (int to = 0; to < state_count; ++to) {
    next[to] = previous[0] + move_cost(0, to);
    for (int from = 1; from < int(previous.size()); ++from) {
        next[to] = std::min(next[to], previous[from] + move_cost(from, to));
    }
}
```

Replace the search with `divide_and_conquer_transition`:

```cpp
#include "convex/monge/divide_and_conquer_optimization.hpp"
#include <cassert>
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> previous = {0, 2, 1};
    int state_count = 4;  // Compute costs for destinations 0,1,2,3.
    auto move_cost = [](int from, int to) {
        long long gap = to - from;
        return gap * gap;
    };
    auto result = m1une::convex::divide_and_conquer_transition(
        previous, state_count, move_cost);
    assert(result.value == std::vector<long long>({0, 1, 1, 2}));
    assert(result.argmin == std::vector<int>({0, 0, 2, 2}));
    for (int to = 0; to < state_count; ++to) {
        std::cout << result.value[to] << ' ' << result.argmin[to] << '\n';
    }

    // Equivalent lower-level call: value(state,candidate) includes previous.
    auto same = m1une::convex::divide_and_conquer_dp(
        state_count, int(previous.size()), [&](int state, int candidate) {
            return previous[candidate] + move_cost(candidate, state);
        });
    assert(same.value == result.value);
    assert(same.argmin == result.argmin);
}
```

Output (new cost, chosen starting position):

```text
0 0
1 0
1 2
2 2
```

`previous.size()` determines the candidate count. `state_count` determines
the number of answers. The `move_cost(from,to)` callback returns **only the
move cost**; the helper adds `previous[from]`. The lower-level
`divide_and_conquer_dp` instead takes `(state,candidate)` and the full value.

Why is the optimization valid? Squared movement cost is Monge; adding the
known previous costs as column constants preserves it. Hence leftmost best
starts are nondecreasing. For your own recurrence, replace `previous` and
`move_cost`, set the destination count, and prove the same ordering property.
To take another step, finish this call before assigning `previous=result.value`.
The work per layer drops from $O(HW)$ to $O((H+W)\log(H+1))$.

## Generic Interface

```cpp
template <class Value>
auto divide_and_conquer_dp(
    int state_count,
    int candidate_count,
    Value value
);
```

`value(state, candidate)` returns one transition value. The return type is
`DivideAndConquerDpResult<T>`:

| Member | Meaning |
| --- | --- |
| `value[i]` | Minimum value for state `i`. |
| `argmin[i]` | Leftmost minimizing candidate for state `i`. |

If there are no candidates, every `argmin` is `-1`; the corresponding values
are placeholders.

## Previous-Layer Helper

For the common recurrence

$$
dp_{\mathrm{next}}[i]
= \min_j \left(dp_{\mathrm{previous}}[j] + cost(j,i)\right),
$$

use:

```cpp
template <class T, class Cost>
auto divide_and_conquer_transition(
    const std::vector<T>& previous,
    int state_count,
    Cost cost
);
```

Candidates that are invalid for a state can be represented by a sufficiently
large value, provided arithmetic does not overflow and the remaining leftmost
argmins are still nondecreasing.

## Requirement

The leftmost minimizing candidate indices must be nondecreasing over states.
The implementation does not verify this condition.

Monge transition matrices satisfy the requirement, but the condition also
holds for some matrices that are not Monge.

## Complexity

For `H` states and `W` candidates, the algorithm uses
$O((H+W)\log H)$ transition evaluations and $O(H)$ additional memory.
