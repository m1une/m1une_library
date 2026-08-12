---
title: Heuristic Objective
documentation_of: ../../heuristic/objective.hpp
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
