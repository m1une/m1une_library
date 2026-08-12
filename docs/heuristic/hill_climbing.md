---
title: Hill Climbing
documentation_of: ../../heuristic/hill_climbing.hpp
---

## What It Does

Hill climbing repeatedly proposes a nearby state and keeps it only when its
score is better. `HillClimbing` implements that one acceptance decision; your
solution owns the state and generates the moves.

For maximization with equal scores rejected, the loop is equivalent to:

```cpp
if (current_score < candidate_score) {
    current_state = candidate_state;
    current_score = candidate_score;
}
```

The class is useful because the same code also supports minimization,
equal-score moves, precomputed deltas, and extreme integral scores safely.

## Complete Example

This example searches for the integer maximizing
`score(x) = -(x - 1234)^2`. A move adds a random value from `[-20, 20]`.

```cpp
#include "heuristic/hill_climbing.hpp"
#include "utilities/random.hpp"

#include <algorithm>
#include <iostream>

int main() {
    m1une::heuristic::HillClimbing climbing;
    m1une::utilities::Random random(12345);

    auto evaluate = [](long long x) {
        long long difference = x - 1234;
        return -difference * difference;
    };

    long long current = -5000;
    long long current_score = evaluate(current);
    for (int iteration = 0; iteration < 200000; iteration++) {
        long long candidate = current + random.uniform(-20, 20);
        candidate = std::clamp(candidate, -10000LL, 10000LL);
        long long candidate_score = evaluate(candidate);

        if (climbing.accept(current_score, candidate_score)) {
            current = candidate;
            current_score = candidate_score;
        }
    }

    std::cout << current << " " << current_score << '\n';
}
```

The important ownership rule is that `accept` does not change anything. The
caller updates `current` and `current_score` only when it returns `true`.

## API

| Method | Description | Complexity |
| --- | --- | --- |
| `HillClimbing(Objective objective = Objective::maximize, bool accept_equal = false)` | Creates an acceptance policy. | $O(1)$ |
| `bool accept_delta(long double candidate_minus_current) const` | Tests a score difference already computed by the caller. | $O(1)$ |
| `template <std::convertible_to<long double> CurrentScore, std::convertible_to<long double> CandidateScore> bool accept(CurrentScore current_score, CandidateScore candidate_score) const` | Tests two scores without overflowing integral subtraction. | $O(1)$ |

Use minimization or allow sideways moves as follows:

```cpp
m1une::heuristic::HillClimbing minimize(
    m1une::heuristic::Objective::minimize);

m1une::heuristic::HillClimbing allow_equal(
    m1une::heuristic::Objective::maximize, true);
```

`HillClimbingObjective` is an alias of `Objective`.

## Using Incremental Scores

Re-evaluating a whole state can be expensive. If a move already provides
`delta = candidate_score - current_score`, use:

```cpp
long long delta = evaluate_move();
if (climbing.accept_delta(delta)) {
    apply_move();
    current_score += delta;
}
```

For minimization, an improving delta is negative. Do not reverse its sign; the
policy handles the objective.

## Common Mistakes

- Hill climbing cannot leave a strict local optimum. Try simulated annealing,
  random restarts, or a richer neighborhood when this matters.
- Allowing equal scores can explore plateaus, but it can also cycle. A time or
  iteration limit is still required.
- If a proposal mutates the state before acceptance, undo it when rejected.
- Keep the best state separately if other parts of the search can overwrite it.
