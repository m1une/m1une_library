---
title: Cow Game (Difference Constraints)
documentation_of: ../../graph/cow_game.hpp
---

## Overview

`CowGame<T>` solves a system of difference constraints. Each variable is a
number `x[i]`, and the primitive constraint is

$$
x[a] - x[b] \le c.
$$

The arguments use that same order: `add_constraint(a, b, c)` adds exactly the
inequality written above. Internally, it becomes a directed edge from `b` to
`a` with cost `c`.

This family is sometimes called a “cow game” in competitive-programming
slang, after several classic cow-placement problems with distance constraints.
`DifferenceConstraints<T>` is provided as a descriptive alias of
`CowGame<T>`.

The solver can:

- determine whether all constraints are simultaneously feasible;
- return one feasible assignment;
- find the tightest upper bounds relative to one variable;
- find the tightest lower and upper bounds on one difference;
- report when either side of a difference is unbounded.

If every primitive upper bound is nonnegative, the zero assignment proves
feasibility immediately and bound queries use Dijkstra. Otherwise, the first
feasibility check uses Bellman-Ford relaxation. A negative cycle means that the
system is infeasible. A feasible assignment is cached and used as a Johnson
potential, so later bound queries still use Dijkstra with nonnegative reduced
edge costs.

## Adding Constraints

All variable indices are zero-based. Every method keeps `a` first and `b`
second, matching the expression `x[a] - x[b]`.

| Method | Signature | Added condition |
| --- | --- | --- |
| `add_upper_bound` | `int add_upper_bound(int a, int b, T upper_bound)` | `x[a] - x[b] <= upper_bound` |
| `add_constraint` | `int add_constraint(int a, int b, T upper_bound)` | Alias of `add_upper_bound` |
| `add_lower_bound` | `int add_lower_bound(int a, int b, T lower_bound)` | `lower_bound <= x[a] - x[b]` |
| `add_bounds` | `void add_bounds(int a, int b, T lower_bound, T upper_bound)` | `lower_bound <= x[a] - x[b] <= upper_bound` |
| `add_equality` | `void add_equality(int a, int b, T difference)` | `x[a] - x[b] == difference` |

`add_upper_bound` and `add_constraint` return the id of the generated
constraint. A lower bound is represented by reversing the edge and negating
the bound. Bounds and equalities therefore generate two primitive constraints.

## Feasible Assignment

`CowGameSolution<T> solve() const` returns one solution result:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `feasible` | `bool` | Whether the whole system is feasible. |
| `value` | `std::vector<T>` | One assignment satisfying every constraint when feasible. |
| `is_feasible` | `bool is_feasible() const` | Returns `feasible`. |

The system contains only differences, so adding the same constant to every
value preserves feasibility. The assignment returned by `solve()` is one
convenient representative, not a uniquely normalized solution.

`bool is_feasible() const` checks feasibility without returning the assignment.
The feasibility result is cached until another constraint is added, which
avoids repeating the global negative-cycle check across bound queries.

## Tight Difference Bounds

`CowGameUpperBounds<T> tightest_upper_bounds(int source) const` returns all
upper bounds from one reference variable. When the system is feasible,
`upper_bound[v]` is the smallest implied upper bound on `x[v] - x[source]`. It
equals the shortest-path distance from `source` to `v`.

If no directed constraint path exists, the difference is unbounded above:
`bounded(v)` is false and `upper_bound[v]` equals the result's `inf` sentinel.

| `CowGameUpperBounds<T>` member / method | Type / Signature | Meaning |
| --- | --- | --- |
| `feasible` | `bool` | Whether the entire system is feasible. |
| `upper_bound` | `std::vector<T>` | Tight upper bounds relative to `source`. |
| `inf` | `T` | Sentinel used for an unbounded difference. |
| `is_feasible` | `bool is_feasible() const` | Returns `feasible`. |
| `bounded` | `bool bounded(int variable) const` | Whether the selected difference is bounded above. |

`CowGameDifferenceBounds<T> difference_bounds(int a, int b) const` returns the
tight bounds on `x[a] - x[b]`:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `feasible` | `bool` | Whether the whole system is feasible. |
| `lower_bound` | `std::optional<T>` | Tightest lower bound on `x[a] - x[b]`, or empty if unbounded below. |
| `upper_bound` | `std::optional<T>` | Tightest upper bound on `x[a] - x[b]`, or empty if unbounded above. |
| `is_feasible` | `bool is_feasible() const` | Returns `feasible`. |
| `bounded_below` | `bool bounded_below() const` | Whether `lower_bound` exists. |
| `bounded_above` | `bool bounded_above() const` | Whether `upper_bound` exists. |

Check feasibility before interpreting bounds. In an infeasible system, neither
bound is meaningful.

## Constraint Inspection

`CowGameConstraint<T>` stores `a`, `b`, and `upper_bound`, representing
`x[a] - x[b] <= upper_bound`.

| Method | Signature | Meaning |
| --- | --- | --- |
| Default constructor | `CowGame()` | Constructs an empty system. |
| Sized constructor | `explicit CowGame(int variable_count)` | Constructs a system with the requested number of variables. |
| `size` | `int size() const` | Number of variables. |
| `constraint_count` | `int constraint_count() const` | Number of primitive upper-bound constraints. |
| `get_constraint` | `const CowGameConstraint<T>& get_constraint(int id) const` | Returns one primitive constraint. |
| `constraints` | `const std::vector<CowGameConstraint<T>>& constraints() const` | Returns all primitive constraints. |

## Complexity

Let `N` be the number of variables and `M` the number of primitive constraints.

| Operation | Time | Additional working memory |
| --- | --- | --- |
| Construct with `N` variables | $O(N)$ | $O(N)$ |
| Add or inspect one constraint | Amortized $O(1)$ | $O(1)$ |
| First `solve` or `is_feasible` after an addition, all upper bounds nonnegative | $O(N)$ | $O(N)$ |
| First `solve` or `is_feasible` after an addition, negative upper bounds allowed | $O(NM)$ | $O(N)$ |
| Cached `solve` / `is_feasible` | $O(N)$ / $O(1)$ | $O(N)$ returned / $O(1)$ |
| Either bound query after feasibility is cached | $O(N + M \log N)$ | $O(N)$ |

Thus, when the original constraints are nonnegative and Dijkstra is available,
even the first bound query takes $O(N + M \log N)$ time, commonly written
$O(M \log N)$. The indexed heap contains at most one entry per variable. With
mixed signs, the first query after an addition includes the $O(NM)$ feasibility
check; every later bound query is Dijkstra-based.
`difference_bounds` runs Dijkstra twice, which has the same asymptotic bound.
The stored constraints, adjacency lists, cached assignment, and working memory
use $O(N + M)$ total space.

## Numeric Requirements

`T` must be a signed arithmetic type. `long long` is recommended. Negated lower
bounds, potentials, reduced costs, finite path sums, and answers must fit in
`T`. For bound queries, finite path sums must also stay strictly inside the
sentinel range based on `numeric_limits<T>::max() / 4`.

## Example

```cpp
#include "graph/cow_game.hpp"
#include <iostream>

int main() {
    m1une::graph::CowGame<long long> game(3);

    // 2 <= x[1] - x[0] <= 5
    game.add_bounds(1, 0, 2, 5);

    // x[2] - x[1] == 4
    game.add_equality(2, 1, 4);

    auto bounds = game.difference_bounds(2, 0);
    if (!bounds.is_feasible()) {
        std::cout << "infeasible\n";
        return 0;
    }

    std::cout << *bounds.lower_bound << " " << *bounds.upper_bound << "\n";
    // 6 9
}
```
