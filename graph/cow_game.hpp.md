---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/cow_game.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <limits>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\n\
    struct CowGameConstraint {\n    int a;\n    int b;\n    T upper_bound;\n};\n\n\
    template <class T>\nstruct CowGameSolution {\n    bool feasible = false;\n   \
    \ std::vector<T> value;\n\n    bool is_feasible() const {\n        return feasible;\n\
    \    }\n};\n\ntemplate <class T>\nstruct CowGameUpperBounds {\n    bool feasible;\n\
    \    std::vector<T> upper_bound;\n    T inf;\n\n    bool is_feasible() const {\n\
    \        return feasible;\n    }\n\n    bool bounded(int variable) const {\n \
    \       assert(0 <= variable && variable < int(upper_bound.size()));\n       \
    \ return feasible && upper_bound[variable] != inf;\n    }\n};\n\ntemplate <class\
    \ T>\nstruct CowGameDifferenceBounds {\n    bool feasible;\n    std::optional<T>\
    \ lower_bound;\n    std::optional<T> upper_bound;\n\n    bool is_feasible() const\
    \ {\n        return feasible;\n    }\n\n    bool bounded_below() const {\n   \
    \     return feasible && lower_bound.has_value();\n    }\n\n    bool bounded_above()\
    \ const {\n        return feasible && upper_bound.has_value();\n    }\n};\n\n\
    template <class T>\nclass CowGame {\n    static_assert(std::is_arithmetic_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct RelaxationResult {\n        bool has_negative_cycle;\n\
    \        std::vector<T> dist;\n    };\n\n    int _n;\n    std::vector<CowGameConstraint<T>>\
    \ _constraints;\n    std::vector<std::vector<int>> _outgoing_constraints;\n  \
    \  bool _has_negative_upper_bound = false;\n    mutable bool _solution_cached\
    \ = false;\n    mutable CowGameSolution<T> _cached_solution;\n\n    void assert_variable(int\
    \ variable) const {\n        (void)variable;\n        assert(0 <= variable &&\
    \ variable < _n);\n    }\n\n    T negate(T value) const {\n        assert(value\
    \ != std::numeric_limits<T>::lowest());\n        return -value;\n    }\n\n   \
    \ RelaxationResult check_feasibility() const {\n        std::vector<T> dist(_n,\
    \ T());\n        for (int iteration = 0; iteration < _n; iteration++) {\n    \
    \        bool updated = false;\n            for (const auto& constraint : _constraints)\
    \ {\n                T candidate = dist[constraint.b] + constraint.upper_bound;\n\
    \                if (dist[constraint.a] <= candidate) continue;\n            \
    \    dist[constraint.a] = candidate;\n                updated = true;\n      \
    \          if (iteration == _n - 1) return RelaxationResult{true, std::move(dist)};\n\
    \            }\n            if (!updated) break;\n        }\n        return RelaxationResult{false,\
    \ std::move(dist)};\n    }\n\n    std::vector<T> shortest_paths(int source, T\
    \ inf) const {\n        const auto& potential = _cached_solution.value;\n    \
    \    std::vector<T> dist(_n, inf);\n        std::vector<int> heap;\n        //\
    \ -1 is unseen, -2 is fixed, and every other value is a heap index.\n        std::vector<int>\
    \ position(_n, -1);\n        heap.reserve(_n);\n\n        auto swap_heap = [&](int\
    \ i, int j) {\n            std::swap(heap[i], heap[j]);\n            position[heap[i]]\
    \ = i;\n            position[heap[j]] = j;\n        };\n        auto sift_up =\
    \ [&](int i) {\n            while (i > 0) {\n                int parent = (i -\
    \ 1) / 2;\n                if (dist[heap[parent]] <= dist[heap[i]]) break;\n \
    \               swap_heap(parent, i);\n                i = parent;\n         \
    \   }\n        };\n        auto sift_down = [&](int i) {\n            while (2\
    \ * i + 1 < int(heap.size())) {\n                int child = 2 * i + 1;\n    \
    \            if (child + 1 < int(heap.size()) &&\n                    dist[heap[child\
    \ + 1]] < dist[heap[child]]) {\n                    child++;\n               \
    \ }\n                if (dist[heap[i]] <= dist[heap[child]]) break;\n        \
    \        swap_heap(i, child);\n                i = child;\n            }\n   \
    \     };\n\n        dist[source] = T();\n        position[source] = 0;\n     \
    \   heap.push_back(source);\n\n        while (!heap.empty()) {\n            int\
    \ b = heap[0];\n            position[b] = -2;\n            int last = heap.back();\n\
    \            heap.pop_back();\n            if (!heap.empty()) {\n            \
    \    heap[0] = last;\n                position[last] = 0;\n                sift_down(0);\n\
    \            }\n\n            for (int id : _outgoing_constraints[b]) {\n    \
    \            const auto& constraint = _constraints[id];\n                T cost\
    \ = constraint.upper_bound + potential[b] -\n                         potential[constraint.a];\n\
    \                assert(cost >= T());\n                T candidate = dist[b] +\
    \ cost;\n                if (dist[constraint.a] <= candidate) continue;\n    \
    \            dist[constraint.a] = candidate;\n                assert(position[constraint.a]\
    \ != -2);\n                if (position[constraint.a] == -1) {\n             \
    \       position[constraint.a] = int(heap.size());\n                    heap.push_back(constraint.a);\n\
    \                }\n                sift_up(position[constraint.a]);\n       \
    \     }\n        }\n\n        for (int v = 0; v < _n; v++) {\n            if (dist[v]\
    \ == inf) continue;\n            dist[v] = dist[v] - potential[source] + potential[v];\n\
    \        }\n        return dist;\n    }\n\n   public:\n    CowGame() : CowGame(0)\
    \ {}\n\n    explicit CowGame(int variable_count)\n        : _n(variable_count),\n\
    \          _outgoing_constraints(variable_count < 0 ? 0 : variable_count) {\n\
    \        assert(variable_count >= 0);\n    }\n\n    int size() const {\n     \
    \   return _n;\n    }\n\n    int constraint_count() const {\n        return int(_constraints.size());\n\
    \    }\n\n    const CowGameConstraint<T>& get_constraint(int id) const {\n   \
    \     assert(0 <= id && id < int(_constraints.size()));\n        return _constraints[id];\n\
    \    }\n\n    const std::vector<CowGameConstraint<T>>& constraints() const {\n\
    \        return _constraints;\n    }\n\n    bool can_use_dijkstra() const {\n\
    \        return !_has_negative_upper_bound ||\n               (_solution_cached\
    \ && _cached_solution.feasible);\n    }\n\n    int add_upper_bound(int a, int\
    \ b, T upper_bound) {\n        assert_variable(a);\n        assert_variable(b);\n\
    \        int id = int(_constraints.size());\n        _constraints.push_back(CowGameConstraint<T>{a,\
    \ b, upper_bound});\n        _outgoing_constraints[b].push_back(id);\n       \
    \ _has_negative_upper_bound = _has_negative_upper_bound || upper_bound < T();\n\
    \        _solution_cached = false;\n        return id;\n    }\n\n    int add_constraint(int\
    \ a, int b, T upper_bound) {\n        return add_upper_bound(a, b, upper_bound);\n\
    \    }\n\n    int add_lower_bound(int a, int b, T lower_bound) {\n        return\
    \ add_upper_bound(b, a, negate(lower_bound));\n    }\n\n    void add_bounds(int\
    \ a, int b, T lower_bound, T upper_bound) {\n        assert(lower_bound <= upper_bound);\n\
    \        add_lower_bound(a, b, lower_bound);\n        add_upper_bound(a, b, upper_bound);\n\
    \    }\n\n    void add_equality(int a, int b, T difference) {\n        add_bounds(a,\
    \ b, difference, difference);\n    }\n\n    CowGameSolution<T> solve() const {\n\
    \        if (_solution_cached) return _cached_solution;\n\n        _cached_solution.feasible\
    \ = true;\n        _cached_solution.value.assign(_n, T());\n        if (_has_negative_upper_bound)\
    \ {\n            auto result = check_feasibility();\n            _cached_solution.feasible\
    \ = !result.has_negative_cycle;\n            _cached_solution.value.clear();\n\
    \            if (_cached_solution.feasible) {\n                _cached_solution.value\
    \ = std::move(result.dist);\n            }\n        }\n        _solution_cached\
    \ = true;\n        return _cached_solution;\n    }\n\n    bool is_feasible() const\
    \ {\n        if (!_solution_cached) (void)solve();\n        return _cached_solution.feasible;\n\
    \    }\n\n    CowGameUpperBounds<T> tightest_upper_bounds(int source) const {\n\
    \        assert_variable(source);\n        T inf = std::numeric_limits<T>::max()\
    \ / T(4);\n        CowGameUpperBounds<T> result;\n        result.feasible = is_feasible();\n\
    \        result.inf = inf;\n        result.upper_bound.assign(_n, inf);\n    \
    \    if (!result.feasible) return result;\n\n        result.upper_bound = shortest_paths(source,\
    \ inf);\n        return result;\n    }\n\n    CowGameDifferenceBounds<T> difference_bounds(int\
    \ a, int b) const {\n        assert_variable(a);\n        assert_variable(b);\n\
    \        T inf = std::numeric_limits<T>::max() / T(4);\n        CowGameDifferenceBounds<T>\
    \ result;\n        result.feasible = is_feasible();\n        if (!result.feasible)\
    \ return result;\n\n        auto upper = shortest_paths(b, inf);\n        if (upper[a]\
    \ != inf) result.upper_bound = upper[a];\n\n        auto lower = shortest_paths(a,\
    \ inf);\n        if (lower[b] != inf) result.lower_bound = negate(lower[b]);\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nusing DifferenceConstraints\
    \ = CowGame<T>;\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_COW_GAME_HPP\n#define M1UNE_GRAPH_COW_GAME_HPP 1\n\n\
    #include <cassert>\n#include <limits>\n#include <optional>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace graph {\n\
    \ntemplate <class T>\nstruct CowGameConstraint {\n    int a;\n    int b;\n   \
    \ T upper_bound;\n};\n\ntemplate <class T>\nstruct CowGameSolution {\n    bool\
    \ feasible = false;\n    std::vector<T> value;\n\n    bool is_feasible() const\
    \ {\n        return feasible;\n    }\n};\n\ntemplate <class T>\nstruct CowGameUpperBounds\
    \ {\n    bool feasible;\n    std::vector<T> upper_bound;\n    T inf;\n\n    bool\
    \ is_feasible() const {\n        return feasible;\n    }\n\n    bool bounded(int\
    \ variable) const {\n        assert(0 <= variable && variable < int(upper_bound.size()));\n\
    \        return feasible && upper_bound[variable] != inf;\n    }\n};\n\ntemplate\
    \ <class T>\nstruct CowGameDifferenceBounds {\n    bool feasible;\n    std::optional<T>\
    \ lower_bound;\n    std::optional<T> upper_bound;\n\n    bool is_feasible() const\
    \ {\n        return feasible;\n    }\n\n    bool bounded_below() const {\n   \
    \     return feasible && lower_bound.has_value();\n    }\n\n    bool bounded_above()\
    \ const {\n        return feasible && upper_bound.has_value();\n    }\n};\n\n\
    template <class T>\nclass CowGame {\n    static_assert(std::is_arithmetic_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct RelaxationResult {\n        bool has_negative_cycle;\n\
    \        std::vector<T> dist;\n    };\n\n    int _n;\n    std::vector<CowGameConstraint<T>>\
    \ _constraints;\n    std::vector<std::vector<int>> _outgoing_constraints;\n  \
    \  bool _has_negative_upper_bound = false;\n    mutable bool _solution_cached\
    \ = false;\n    mutable CowGameSolution<T> _cached_solution;\n\n    void assert_variable(int\
    \ variable) const {\n        (void)variable;\n        assert(0 <= variable &&\
    \ variable < _n);\n    }\n\n    T negate(T value) const {\n        assert(value\
    \ != std::numeric_limits<T>::lowest());\n        return -value;\n    }\n\n   \
    \ RelaxationResult check_feasibility() const {\n        std::vector<T> dist(_n,\
    \ T());\n        for (int iteration = 0; iteration < _n; iteration++) {\n    \
    \        bool updated = false;\n            for (const auto& constraint : _constraints)\
    \ {\n                T candidate = dist[constraint.b] + constraint.upper_bound;\n\
    \                if (dist[constraint.a] <= candidate) continue;\n            \
    \    dist[constraint.a] = candidate;\n                updated = true;\n      \
    \          if (iteration == _n - 1) return RelaxationResult{true, std::move(dist)};\n\
    \            }\n            if (!updated) break;\n        }\n        return RelaxationResult{false,\
    \ std::move(dist)};\n    }\n\n    std::vector<T> shortest_paths(int source, T\
    \ inf) const {\n        const auto& potential = _cached_solution.value;\n    \
    \    std::vector<T> dist(_n, inf);\n        std::vector<int> heap;\n        //\
    \ -1 is unseen, -2 is fixed, and every other value is a heap index.\n        std::vector<int>\
    \ position(_n, -1);\n        heap.reserve(_n);\n\n        auto swap_heap = [&](int\
    \ i, int j) {\n            std::swap(heap[i], heap[j]);\n            position[heap[i]]\
    \ = i;\n            position[heap[j]] = j;\n        };\n        auto sift_up =\
    \ [&](int i) {\n            while (i > 0) {\n                int parent = (i -\
    \ 1) / 2;\n                if (dist[heap[parent]] <= dist[heap[i]]) break;\n \
    \               swap_heap(parent, i);\n                i = parent;\n         \
    \   }\n        };\n        auto sift_down = [&](int i) {\n            while (2\
    \ * i + 1 < int(heap.size())) {\n                int child = 2 * i + 1;\n    \
    \            if (child + 1 < int(heap.size()) &&\n                    dist[heap[child\
    \ + 1]] < dist[heap[child]]) {\n                    child++;\n               \
    \ }\n                if (dist[heap[i]] <= dist[heap[child]]) break;\n        \
    \        swap_heap(i, child);\n                i = child;\n            }\n   \
    \     };\n\n        dist[source] = T();\n        position[source] = 0;\n     \
    \   heap.push_back(source);\n\n        while (!heap.empty()) {\n            int\
    \ b = heap[0];\n            position[b] = -2;\n            int last = heap.back();\n\
    \            heap.pop_back();\n            if (!heap.empty()) {\n            \
    \    heap[0] = last;\n                position[last] = 0;\n                sift_down(0);\n\
    \            }\n\n            for (int id : _outgoing_constraints[b]) {\n    \
    \            const auto& constraint = _constraints[id];\n                T cost\
    \ = constraint.upper_bound + potential[b] -\n                         potential[constraint.a];\n\
    \                assert(cost >= T());\n                T candidate = dist[b] +\
    \ cost;\n                if (dist[constraint.a] <= candidate) continue;\n    \
    \            dist[constraint.a] = candidate;\n                assert(position[constraint.a]\
    \ != -2);\n                if (position[constraint.a] == -1) {\n             \
    \       position[constraint.a] = int(heap.size());\n                    heap.push_back(constraint.a);\n\
    \                }\n                sift_up(position[constraint.a]);\n       \
    \     }\n        }\n\n        for (int v = 0; v < _n; v++) {\n            if (dist[v]\
    \ == inf) continue;\n            dist[v] = dist[v] - potential[source] + potential[v];\n\
    \        }\n        return dist;\n    }\n\n   public:\n    CowGame() : CowGame(0)\
    \ {}\n\n    explicit CowGame(int variable_count)\n        : _n(variable_count),\n\
    \          _outgoing_constraints(variable_count < 0 ? 0 : variable_count) {\n\
    \        assert(variable_count >= 0);\n    }\n\n    int size() const {\n     \
    \   return _n;\n    }\n\n    int constraint_count() const {\n        return int(_constraints.size());\n\
    \    }\n\n    const CowGameConstraint<T>& get_constraint(int id) const {\n   \
    \     assert(0 <= id && id < int(_constraints.size()));\n        return _constraints[id];\n\
    \    }\n\n    const std::vector<CowGameConstraint<T>>& constraints() const {\n\
    \        return _constraints;\n    }\n\n    bool can_use_dijkstra() const {\n\
    \        return !_has_negative_upper_bound ||\n               (_solution_cached\
    \ && _cached_solution.feasible);\n    }\n\n    int add_upper_bound(int a, int\
    \ b, T upper_bound) {\n        assert_variable(a);\n        assert_variable(b);\n\
    \        int id = int(_constraints.size());\n        _constraints.push_back(CowGameConstraint<T>{a,\
    \ b, upper_bound});\n        _outgoing_constraints[b].push_back(id);\n       \
    \ _has_negative_upper_bound = _has_negative_upper_bound || upper_bound < T();\n\
    \        _solution_cached = false;\n        return id;\n    }\n\n    int add_constraint(int\
    \ a, int b, T upper_bound) {\n        return add_upper_bound(a, b, upper_bound);\n\
    \    }\n\n    int add_lower_bound(int a, int b, T lower_bound) {\n        return\
    \ add_upper_bound(b, a, negate(lower_bound));\n    }\n\n    void add_bounds(int\
    \ a, int b, T lower_bound, T upper_bound) {\n        assert(lower_bound <= upper_bound);\n\
    \        add_lower_bound(a, b, lower_bound);\n        add_upper_bound(a, b, upper_bound);\n\
    \    }\n\n    void add_equality(int a, int b, T difference) {\n        add_bounds(a,\
    \ b, difference, difference);\n    }\n\n    CowGameSolution<T> solve() const {\n\
    \        if (_solution_cached) return _cached_solution;\n\n        _cached_solution.feasible\
    \ = true;\n        _cached_solution.value.assign(_n, T());\n        if (_has_negative_upper_bound)\
    \ {\n            auto result = check_feasibility();\n            _cached_solution.feasible\
    \ = !result.has_negative_cycle;\n            _cached_solution.value.clear();\n\
    \            if (_cached_solution.feasible) {\n                _cached_solution.value\
    \ = std::move(result.dist);\n            }\n        }\n        _solution_cached\
    \ = true;\n        return _cached_solution;\n    }\n\n    bool is_feasible() const\
    \ {\n        if (!_solution_cached) (void)solve();\n        return _cached_solution.feasible;\n\
    \    }\n\n    CowGameUpperBounds<T> tightest_upper_bounds(int source) const {\n\
    \        assert_variable(source);\n        T inf = std::numeric_limits<T>::max()\
    \ / T(4);\n        CowGameUpperBounds<T> result;\n        result.feasible = is_feasible();\n\
    \        result.inf = inf;\n        result.upper_bound.assign(_n, inf);\n    \
    \    if (!result.feasible) return result;\n\n        result.upper_bound = shortest_paths(source,\
    \ inf);\n        return result;\n    }\n\n    CowGameDifferenceBounds<T> difference_bounds(int\
    \ a, int b) const {\n        assert_variable(a);\n        assert_variable(b);\n\
    \        T inf = std::numeric_limits<T>::max() / T(4);\n        CowGameDifferenceBounds<T>\
    \ result;\n        result.feasible = is_feasible();\n        if (!result.feasible)\
    \ return result;\n\n        auto upper = shortest_paths(b, inf);\n        if (upper[a]\
    \ != inf) result.upper_bound = upper[a];\n\n        auto lower = shortest_paths(a,\
    \ inf);\n        if (lower[b] != inf) result.lower_bound = negate(lower[b]);\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nusing DifferenceConstraints\
    \ = CowGame<T>;\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_GRAPH_COW_GAME_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/cow_game.hpp
  requiredBy:
  - graph/directed.hpp
  - graph/shortest_path.hpp
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-17 02:44:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
documentation_of: graph/cow_game.hpp
layout: document
title: Cow Game (Difference Constraints)
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

`bool can_use_dijkstra() const` reports whether a bound query can use Dijkstra
without first running Bellman-Ford. It is immediately true while all primitive
upper bounds are nonnegative. For a mixed-sign system, it becomes true after a
successful `solve()` or `is_feasible()` call caches a Johnson potential. In a
mixed-sign system, adding another constraint invalidates that potential until
feasibility is checked again. An infeasible system reports false.

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
