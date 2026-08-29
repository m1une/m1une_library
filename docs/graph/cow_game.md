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
feasibility immediately and bound queries can run Dijkstra on the original
edge costs. Otherwise, the first feasibility check uses Bellman-Ford
relaxation. A negative edge alone does not make the system infeasible; a
negative cycle does. If there is no negative cycle, the resulting feasible
assignment is cached and used as a Johnson potential, so the actual bound
search can run Dijkstra on nonnegative reduced edge costs.

## Exactly When Dijkstra Can Be Used

Each primitive constraint `x[a] - x[b] <= c` is the directed edge
`b -> a` of cost `c`. The shortest-path distance from `source` to `v` is the
tightest implied upper bound on `x[v] - x[source]`.

`CowGame` runs Dijkstra directly on the original costs if and only if every
primitive edge cost is nonnegative. This is the standard condition that
guarantees Dijkstra's correctness; for this class, it means every stored
`upper_bound` is at least zero. Be careful with the convenience methods:
`add_lower_bound(a, b, l)` stores the reversed edge `a -> b` with cost `-l`.
Therefore, a positive lower bound creates a negative edge even though the
argument `l` itself is positive. Similarly, a nonzero equality creates one
negative edge.

If any primitive edge cost is negative, Dijkstra on the original costs is not
guaranteed to be correct and `CowGame` does not use it. It could coincidentally
produce the right answer for a particular source, but that is not a condition
on which the solver relies. The negative edge does **not** by itself prove
infeasibility, and it is not enough that the final shortest distance happens to
be nonnegative. Dijkstra's correctness is instead guaranteed by nonnegative
costs on the graph on which it is run. `CowGame` handles this case as follows:

1. It runs Bellman-Ford relaxation from an implicit super-source connected to
   every variable by a zero-cost edge. This checks the entire constraint system,
   including components unreachable from the requested query source.
2. If a negative cycle exists, the constraints are infeasible, so there are no
   meaningful difference bounds and Dijkstra is not run.
3. Otherwise, Bellman-Ford produces a feasible assignment `p`. For every edge
   `b -> a` of cost `c`, feasibility gives `p[a] <= p[b] + c`, hence the reduced
   cost

   $$
   c' = c + p[b] - p[a]
   $$

   is nonnegative. Dijkstra is then valid on these reduced costs. The original
   distance is recovered by

   $$
   d(source, v) = d'(source, v) - p[source] + p[v].
   $$

Thus a bound query uses Dijkstra in either of two states:

| State | What the next bound query does |
| --- | --- |
| All stored primitive costs are nonnegative | Uses Dijkstra immediately; the all-zero assignment already proves feasibility. |
| Some primitive cost is negative, and a feasible assignment is cached | Uses Dijkstra immediately on Johnson-reweighted costs. |
| Some primitive cost is negative, and no feasibility result is cached | Runs Bellman-Ford first; if feasible, then runs reweighted Dijkstra. |
| The cached feasibility result is infeasible | Returns an infeasible result; it does not run Dijkstra. |

Adding any constraint invalidates a cached feasible assignment. Consequently,
in a mixed-sign system the next bound query must repeat the feasibility check,
even if the newly added constraint would happen to preserve the old potential.
The public bound-query methods perform all of this automatically; callers do
not need to invoke `solve()` first.

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

`bool can_use_dijkstra() const` reports whether a bound query can start its
shortest-path phase without first running Bellman-Ford. It does not mean that a
query is forbidden when the result is false: the query performs the required
feasibility check itself. The result is immediately true while all primitive
upper bounds are nonnegative. For a mixed-sign system, it becomes true after a
successful `solve()` or `is_feasible()` call caches a Johnson potential. Adding
another constraint invalidates that potential until feasibility is checked
again. An infeasible system reports false because no difference bound is
meaningful.

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
| `can_use_dijkstra` | `bool can_use_dijkstra() const` | Whether a bound query can skip Bellman-Ford and use Dijkstra. |

## Complexity

Let `N` be the number of variables and `M` the number of primitive constraints.

| Operation | Time | Additional working memory |
| --- | --- | --- |
| Construct with `N` variables | $O(N)$ | $O(N)$ |
| Add or inspect one constraint | Amortized $O(1)$ | $O(1)$ |
| `can_use_dijkstra` | $O(1)$ | $O(1)$ |
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
