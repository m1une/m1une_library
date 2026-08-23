---
title: K-Value Project Selection
documentation_of: ../../optimization/k_project_selection.hpp
---

## Overview

`KProjectSelection<T>` assigns one ordered value to every project and maximizes
the sum of unary gains and graph-cut-representable pairwise gains. Project `i`
has values `0, 1, ..., value_count(i) - 1`; different projects may have
different numbers of values.

This is the ordered, k-valued generalization of binary project selection. It is
useful for labeling and discrete optimization problems whose pairwise terms
prefer coordinated increases. The model is reduced to one minimum `s-t` cut.

## Objective Terms

All calls are additive: calling `add_gain` several times adds every supplied
term to the same objective.

| Method | Contribution |
| --- | --- |
| `void add_gain(int i, const std::vector<T>& gains)` | Adds `gains[x]` when project `i` takes value `x`. The vector must have `value_count(i)` entries. |
| `void add_gain(int i, int j, const std::vector<std::vector<T>>& gains)` | Adds `gains[x][y]` when distinct projects `i` and `j` take values `x` and `y`. The matrix must have shape `value_count(i)` by `value_count(j)`. |

## Domain of Gains

Every entry in a unary gain vector or pairwise gain matrix may be **negative,
zero, or positive**, as long as it is representable by `T`. A negative entry
represents a cost for the corresponding value or pair of values. Consequently,
the optimal `result.max_gain` may also be negative.

Unary gain vectors have no further algebraic restriction. Pairwise matrix
entries do not need to be non-negative, but their discrete mixed differences
must be non-negative. Equivalently, a pairwise gain matrix `g` must be
**supermodular** on the ordered values:

$$
g(x,y) + g(x+1,y+1) \ge g(x+1,y) + g(x,y+1)
$$

for every adjacent pair of rows and columns. The implementation checks this
condition with assertions. Each mixed difference, every accumulated value, and
the final answer must also fit the numeric requirements stated below.

Equivalently, if the problem is written using costs `c = -g`, every pairwise
cost matrix must be Monge. An arbitrary pairwise table cannot generally be
optimized by one minimum cut.

To minimize costs, negate every cost table before adding it, maximize the
resulting gain, and negate `result.max_gain`.

## Construction and Bounds

| Method | Signature / Meaning |
| --- | --- |
| Default constructor | Creates a model with no projects. |
| Heterogeneous constructor | `explicit KProjectSelection(std::vector<int> value_counts)` creates one project for every entry. Every count must be positive. |
| Uniform constructor | `KProjectSelection(int project_count, int value_count)` gives every project the same positive number of values. |
| `size` | `int size() const` returns the number of projects. |
| `value_count` | `int value_count(int i) const` returns the number of values of project `i`. |
| `force_value` | `void force_value(int i, int x)` requires value `x`. |
| `force_value_at_least` | `void force_value_at_least(int i, int lower_bound)` requires the value to be at least the bound. |
| `force_value_at_most` | `void force_value_at_most(int i, int upper_bound)` requires the value to be at most the bound. |

Bounds are inclusive. Contradictory bounds make the model infeasible rather
than silently choosing a value.

## Result

`KProjectSelectionResult<T>` contains:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `feasible` | `bool` | Whether all forced-value constraints can be satisfied. |
| `max_gain` | `T` | Maximum total gain; meaningful only when feasible. |
| `values` | `std::vector<int>` | One optimal value for each project. |
| `is_feasible` | `bool is_feasible() const` | Returns `feasible`. |

`solve()` has signature `KProjectSelectionResult<T> solve() const`. It does not
mutate the model, and it may return any optimum when several assignments tie.

## Reduction and Complexity

For every project value boundary `d`, the reduction creates a Boolean threshold
vertex representing `value >= d`. Hard implications ensure that the selected
thresholds form a prefix. Unary tables become gains on these thresholds.

For a pairwise table, each non-negative discrete mixed difference becomes a
reward for selecting two threshold vertices. Supermodularity is exactly the
condition that makes all such rewards graph-cut-representable.

Let

- `S` be the sum of `value_count(i) - 1` over all projects,
- `P` be the sum of `value_count(i) * value_count(j)` over all added pairwise
  terms, and
- `M = O(S + P)` be the number of generated flow edges.

| Method | Time | Extra stored memory |
| --- | --- | --- |
| Heterogeneous or uniform constructor | $O(N + S)$ | $O(N + S)$ |
| `size`, `value_count` | $O(1)$ | $O(1)$ |
| Unary `add_gain` | $O(K_i)$ | $O(K_i)$ |
| Pairwise `add_gain` | $O(K_i K_j)$ | $O(K_i K_j)$ in the worst case |
| Forced-value or bound method | $O(1)$ | $O(1)$ |
| `solve` | General-case $O((S+2)^2 M)$ | $O(S + M)$ |

The solve bound follows the underlying `MaxFlow<T>` implementation. Threshold
reconstruction takes an additional $O(S)$ time.

## Numeric Requirements

`T` must be a signed integral type no wider than 64 bits; `long long` is
recommended. Every adjacent gain difference, discrete mixed difference, sum of
finite cut capacities, accumulated constant, and final answer must fit in `T`.
The implementation uses a wider intermediate for checking individual table
differences and assertions for the remaining range requirements.

## Example

The following model has three values for project `0` and two for project `1`.
Its pairwise table is supermodular.

```cpp
#include "optimization/k_project_selection.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::opt::KProjectSelection<long long> solver(
        std::vector<int>{3, 2}
    );
    solver.add_gain(0, std::vector<long long>{1, 4, 2});
    solver.add_gain(1, std::vector<long long>{-2, 3});

    std::vector<std::vector<long long>> together(
        3,
        std::vector<long long>(2)
    );
    together[0] = std::vector<long long>{0, 1};
    together[1] = std::vector<long long>{-1, 3};
    together[2] = std::vector<long long>{1, 7};
    solver.add_gain(0, 1, together);

    auto result = solver.solve();
    if (!result.is_feasible()) return 0;
    std::cout << result.max_gain << '\n';  // 12
    std::cout << result.values[0] << ' ' << result.values[1] << '\n';  // 2 1
}
```
