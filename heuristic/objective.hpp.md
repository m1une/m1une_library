---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: heuristic/all.hpp
    title: Heuristic Search
  - icon: ':heavy_check_mark:'
    path: heuristic/beam_search.hpp
    title: Beam Search
  - icon: ':heavy_check_mark:'
    path: heuristic/hill_climbing.hpp
    title: Hill Climbing
  - icon: ':heavy_check_mark:'
    path: heuristic/simulated_annealing.hpp
    title: Simulated Annealing
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/heuristic/beam_search.test.cpp
    title: verify/heuristic/beam_search.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/heuristic/hill_climbing.test.cpp
    title: verify/heuristic/hill_climbing.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/heuristic/simulated_annealing.test.cpp
    title: verify/heuristic/simulated_annealing.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"heuristic/objective.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ heuristic {\n\nenum class Objective {\n    minimize,\n    maximize,\n};\n\n\
    template <class Score>\nbool better_score(const Score& first, const Score& second,\n\
    \                  Objective objective) {\n    if (objective == Objective::maximize)\
    \ return second < first;\n    return first < second;\n}\n\n}  // namespace heuristic\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_HEURISTIC_OBJECTIVE_HPP\n#define M1UNE_HEURISTIC_OBJECTIVE_HPP\
    \ 1\n\nnamespace m1une {\nnamespace heuristic {\n\nenum class Objective {\n  \
    \  minimize,\n    maximize,\n};\n\ntemplate <class Score>\nbool better_score(const\
    \ Score& first, const Score& second,\n                  Objective objective) {\n\
    \    if (objective == Objective::maximize) return second < first;\n    return\
    \ first < second;\n}\n\n}  // namespace heuristic\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_HEURISTIC_OBJECTIVE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: heuristic/objective.hpp
  requiredBy:
  - heuristic/hill_climbing.hpp
  - heuristic/all.hpp
  - heuristic/simulated_annealing.hpp
  - heuristic/beam_search.hpp
  timestamp: '2026-08-12 20:17:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/heuristic/simulated_annealing.test.cpp
  - verify/heuristic/hill_climbing.test.cpp
  - verify/heuristic/beam_search.test.cpp
documentation_of: heuristic/objective.hpp
layout: document
title: Heuristic Objective
---

## Overview

Shared minimization and maximization vocabulary for heuristic search policies.
Most users only need to pass an `Objective` when constructing or calling a
search tool:

```cpp
#include "heuristic/hill_climbing.hpp"

using m1une::heuristic::Objective;

m1une::heuristic::HillClimbing climbing(Objective::minimize);
```

The default objective in every heuristic header is `Objective::maximize`.

## Interface

| Interface | Description | Complexity |
| --- | --- | --- |
| `enum class Objective { minimize, maximize };` | Selects whether smaller or larger scores rank first. | $O(1)$ |
| `bool better_score(const Score& first, const Score& second, Objective objective)` | Returns whether `first` is strictly better than `second`. `Score` must support `<`. | $O(1)$ plus one or two score comparisons |

`AnnealingObjective` and `HillClimbingObjective` are aliases of `Objective`, so
one objective value can be reused across local-search policies.

`better_score(first, second, objective)` is mainly a helper for implementing
other heuristic algorithms. It is strict: equal scores return `false` in both
directions.
