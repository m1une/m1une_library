---
title: Heuristic Search
documentation_of: ../../heuristic/all.hpp
---

## Start Here

The heuristic headers provide reusable search decisions. They do **not** know
your problem's state, moves, or score. In most solutions you still write:

1. a state representation;
2. a function that evaluates the state, or computes a move's score difference;
3. a way to generate neighboring or child states;
4. the stopping condition, usually an iteration count or `Timer`.

The library handles the general part: deciding whether to accept a local move,
or deciding which states survive to the next beam-search layer.

## Which Search Should I Use?

| Situation | Recommended tool | Why |
| --- | --- | --- |
| Every state has nearby moves and greedy improvement works well | `HillClimbing` | Smallest overhead and simplest behavior. |
| Greedy search becomes trapped in local optima | `SimulatedAnnealing` | Sometimes accepts worse moves early, then becomes increasingly greedy. |
| A solution is constructed in a fixed sequence of decisions | `beam_search` | Keeps several promising partial solutions at every depth. |

A useful starting progression is hill climbing, then simulated annealing if
local optima are a problem. Use beam search when the problem naturally looks
like a branching decision tree rather than repeated modification of one state.

## Shared Terms

- A **state** is one candidate solution.
- A **score** is the value used to compare states.
- A **move** changes one state into a nearby state.
- `Objective::maximize` means larger scores are better.
- `Objective::minimize` means smaller scores are better.
- `delta` always means `candidate_score - current_score`, even when minimizing.

[`utilities/Timer`](../utilities/timer.md) and
[`utilities/Random`](../utilities/random.md) provide the usual time limit and
randomness for local search.

## Included Headers

| Header | Contents |
| --- | --- |
| [`heuristic/objective.hpp`](objective.md) | Shared minimization/maximization score ordering. |
| [`heuristic/hill_climbing.hpp`](hill_climbing.md) | Greedy local-search acceptance with optional equal-score moves. |
| [`heuristic/simulated_annealing.hpp`](simulated_annealing.md) | Temperature schedules and probabilistic acceptance. |
| [`heuristic/beam_search.hpp`](beam_search.md) | Memory-bounded layered search with simple and allocation-conscious child generation. |

Include `heuristic/all.hpp` to use every heuristic header, or include only the
specific header needed by the solution.
