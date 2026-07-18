---
title: Non-Adjacent Selection Sums
documentation_of: ../../../algo/sequence/non_adjacent_selection.hpp
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
