---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: heuristic/objective.hpp
    title: Heuristic Objective
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: heuristic/all.hpp
    title: Heuristic Search
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/heuristic/simulated_annealing.test.cpp
    title: verify/heuristic/simulated_annealing.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"heuristic/simulated_annealing.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <concepts>\n\n#line 1 \"heuristic/objective.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace heuristic {\n\nenum class Objective {\n \
    \   minimize,\n    maximize,\n};\n\ntemplate <class Score>\nbool better_score(const\
    \ Score& first, const Score& second,\n                  Objective objective) {\n\
    \    if (objective == Objective::maximize) return second < first;\n    return\
    \ first < second;\n}\n\n}  // namespace heuristic\n}  // namespace m1une\n\n\n\
    #line 10 \"heuristic/simulated_annealing.hpp\"\n\nnamespace m1une {\nnamespace\
    \ heuristic {\n\nusing AnnealingObjective = Objective;\n\nenum class AnnealingCooling\
    \ {\n    linear,\n    exponential,\n};\n\nclass SimulatedAnnealing {\n   private:\n\
    \    double _start_temperature;\n    double _end_temperature;\n    AnnealingObjective\
    \ _objective;\n    AnnealingCooling _cooling;\n\n    long double directed_delta(long\
    \ double candidate_minus_current) const {\n        if (_objective == AnnealingObjective::maximize)\
    \ {\n            return candidate_minus_current;\n        }\n        return -candidate_minus_current;\n\
    \    }\n\n   public:\n    SimulatedAnnealing(\n        double start_temperature,\
    \ double end_temperature,\n        AnnealingObjective objective = AnnealingObjective::maximize,\n\
    \        AnnealingCooling cooling = AnnealingCooling::exponential)\n        :\
    \ _start_temperature(start_temperature),\n          _end_temperature(end_temperature),\n\
    \          _objective(objective),\n          _cooling(cooling) {\n        assert(std::isfinite(start_temperature));\n\
    \        assert(std::isfinite(end_temperature));\n        assert(0.0 <= end_temperature);\n\
    \        assert(end_temperature <= start_temperature);\n        assert(cooling\
    \ != AnnealingCooling::exponential ||\n               0.0 < end_temperature);\n\
    \    }\n\n    double temperature(double progress) const {\n        assert(std::isfinite(progress));\n\
    \        assert(0.0 <= progress && progress <= 1.0);\n        progress = std::clamp(progress,\
    \ 0.0, 1.0);\n        if (_cooling == AnnealingCooling::linear) {\n          \
    \  return _start_temperature +\n                   (_end_temperature - _start_temperature)\
    \ * progress;\n        }\n        return _start_temperature *\n              \
    \ std::pow(_end_temperature / _start_temperature, progress);\n    }\n\n    double\
    \ acceptance_probability_delta(\n        long double candidate_minus_current,\
    \ double progress) const {\n        long double improvement = directed_delta(candidate_minus_current);\n\
    \        if (0.0L <= improvement) return 1.0;\n        double current_temperature\
    \ = temperature(progress);\n        if (current_temperature == 0.0) return 0.0;\n\
    \        return std::exp(static_cast<double>(\n            improvement / static_cast<long\
    \ double>(current_temperature)));\n    }\n\n    bool accept_delta(long double\
    \ candidate_minus_current, double progress,\n                      double random01)\
    \ const {\n        assert(std::isfinite(random01));\n        assert(0.0 <= random01\
    \ && random01 < 1.0);\n        return random01 <\n               acceptance_probability_delta(candidate_minus_current,\
    \ progress);\n    }\n\n    template <std::convertible_to<long double> CurrentScore,\n\
    \              std::convertible_to<long double> CandidateScore>\n    double acceptance_probability(CurrentScore\
    \ current_score,\n                                  CandidateScore candidate_score,\n\
    \                                  double progress) const {\n        long double\
    \ delta = static_cast<long double>(candidate_score) -\n                      \
    \      static_cast<long double>(current_score);\n        return acceptance_probability_delta(delta,\
    \ progress);\n    }\n\n    template <std::convertible_to<long double> CurrentScore,\n\
    \              std::convertible_to<long double> CandidateScore>\n    bool accept(CurrentScore\
    \ current_score, CandidateScore candidate_score,\n                double progress,\
    \ double random01) const {\n        long double delta = static_cast<long double>(candidate_score)\
    \ -\n                            static_cast<long double>(current_score);\n  \
    \      return accept_delta(delta, progress, random01);\n    }\n};\n\n}  // namespace\
    \ heuristic\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_HEURISTIC_SIMULATED_ANNEALING_HPP\n#define M1UNE_HEURISTIC_SIMULATED_ANNEALING_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <concepts>\n\
    \n#include \"objective.hpp\"\n\nnamespace m1une {\nnamespace heuristic {\n\nusing\
    \ AnnealingObjective = Objective;\n\nenum class AnnealingCooling {\n    linear,\n\
    \    exponential,\n};\n\nclass SimulatedAnnealing {\n   private:\n    double _start_temperature;\n\
    \    double _end_temperature;\n    AnnealingObjective _objective;\n    AnnealingCooling\
    \ _cooling;\n\n    long double directed_delta(long double candidate_minus_current)\
    \ const {\n        if (_objective == AnnealingObjective::maximize) {\n       \
    \     return candidate_minus_current;\n        }\n        return -candidate_minus_current;\n\
    \    }\n\n   public:\n    SimulatedAnnealing(\n        double start_temperature,\
    \ double end_temperature,\n        AnnealingObjective objective = AnnealingObjective::maximize,\n\
    \        AnnealingCooling cooling = AnnealingCooling::exponential)\n        :\
    \ _start_temperature(start_temperature),\n          _end_temperature(end_temperature),\n\
    \          _objective(objective),\n          _cooling(cooling) {\n        assert(std::isfinite(start_temperature));\n\
    \        assert(std::isfinite(end_temperature));\n        assert(0.0 <= end_temperature);\n\
    \        assert(end_temperature <= start_temperature);\n        assert(cooling\
    \ != AnnealingCooling::exponential ||\n               0.0 < end_temperature);\n\
    \    }\n\n    double temperature(double progress) const {\n        assert(std::isfinite(progress));\n\
    \        assert(0.0 <= progress && progress <= 1.0);\n        progress = std::clamp(progress,\
    \ 0.0, 1.0);\n        if (_cooling == AnnealingCooling::linear) {\n          \
    \  return _start_temperature +\n                   (_end_temperature - _start_temperature)\
    \ * progress;\n        }\n        return _start_temperature *\n              \
    \ std::pow(_end_temperature / _start_temperature, progress);\n    }\n\n    double\
    \ acceptance_probability_delta(\n        long double candidate_minus_current,\
    \ double progress) const {\n        long double improvement = directed_delta(candidate_minus_current);\n\
    \        if (0.0L <= improvement) return 1.0;\n        double current_temperature\
    \ = temperature(progress);\n        if (current_temperature == 0.0) return 0.0;\n\
    \        return std::exp(static_cast<double>(\n            improvement / static_cast<long\
    \ double>(current_temperature)));\n    }\n\n    bool accept_delta(long double\
    \ candidate_minus_current, double progress,\n                      double random01)\
    \ const {\n        assert(std::isfinite(random01));\n        assert(0.0 <= random01\
    \ && random01 < 1.0);\n        return random01 <\n               acceptance_probability_delta(candidate_minus_current,\
    \ progress);\n    }\n\n    template <std::convertible_to<long double> CurrentScore,\n\
    \              std::convertible_to<long double> CandidateScore>\n    double acceptance_probability(CurrentScore\
    \ current_score,\n                                  CandidateScore candidate_score,\n\
    \                                  double progress) const {\n        long double\
    \ delta = static_cast<long double>(candidate_score) -\n                      \
    \      static_cast<long double>(current_score);\n        return acceptance_probability_delta(delta,\
    \ progress);\n    }\n\n    template <std::convertible_to<long double> CurrentScore,\n\
    \              std::convertible_to<long double> CandidateScore>\n    bool accept(CurrentScore\
    \ current_score, CandidateScore candidate_score,\n                double progress,\
    \ double random01) const {\n        long double delta = static_cast<long double>(candidate_score)\
    \ -\n                            static_cast<long double>(current_score);\n  \
    \      return accept_delta(delta, progress, random01);\n    }\n};\n\n}  // namespace\
    \ heuristic\n}  // namespace m1une\n\n#endif  // M1UNE_HEURISTIC_SIMULATED_ANNEALING_HPP\n"
  dependsOn:
  - heuristic/objective.hpp
  isVerificationFile: false
  path: heuristic/simulated_annealing.hpp
  requiredBy:
  - heuristic/all.hpp
  timestamp: '2026-08-12 20:17:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/heuristic/simulated_annealing.test.cpp
documentation_of: heuristic/simulated_annealing.hpp
layout: document
title: Simulated Annealing
---

## What It Does

Simulated annealing is local search that can temporarily accept worse moves.
This helps it escape local optima. Early in the run the temperature is high and
worse moves are accepted more often. Near the end the temperature is low and
the behavior approaches hill climbing.

`SimulatedAnnealing` handles the temperature schedule and the acceptance
probability. It deliberately does not own:

- the current or best state;
- the current score;
- the random generator;
- the timer or iteration limit;
- move generation, application, or rollback.

Keeping these pieces in the solution allows incremental scoring and
problem-specific moves without hidden copies.

## Complete Example

This example searches for the integer maximizing
`score(x) = -(x - 1234)^2`. It uses a fixed iteration count, so a fixed random
seed reproduces the same run.

```cpp
#include "heuristic/simulated_annealing.hpp"
#include "utilities/random.hpp"

#include <algorithm>
#include <iostream>

int main() {
    constexpr int iteration_limit = 200000;
    m1une::heuristic::SimulatedAnnealing annealing(10000.0, 0.01);
    m1une::utilities::Random random(12345);

    auto evaluate = [](long long x) {
        long long difference = x - 1234;
        return -difference * difference;
    };

    long long current = -5000;
    long long current_score = evaluate(current);
    long long best = current;
    long long best_score = current_score;

    for (int iteration = 0; iteration < iteration_limit; iteration++) {
        long long candidate = current + random.uniform(-50, 50);
        candidate = std::clamp(candidate, -10000LL, 10000LL);
        long long candidate_score = evaluate(candidate);
        double progress = double(iteration + 1) / iteration_limit;

        if (annealing.accept(current_score, candidate_score, progress,
                             random.real())) {
            current = candidate;
            current_score = candidate_score;
            if (best_score < current_score) {
                best = current;
                best_score = current_score;
            }
        }
    }

    std::cout << best << " " << best_score << '\n';
}
```

`accept` only returns a decision. It never modifies the state or score. The
current state may become worse after an accepted move, so the example stores a
separate best state.

## How Acceptance Is Computed

Always define:

```text
delta = candidate_score - current_score
```

For maximization, a positive delta is an improvement. For minimization, a
negative delta is an improvement. Improvements and equal scores are always
accepted. A worsening move is accepted with probability:

```text
exp(-worsening_amount / temperature)
```

The `random01` argument must be independently uniform in `[0, 1)`. Pass
`random.real()` when using `m1une::utilities::Random`.

For example, at temperature `10`, a maximization move with delta `-5` has
acceptance probability `exp(-0.5)`, approximately `0.607`. The same move is
almost never accepted when the temperature is near zero.

## Progress and Cooling

`progress` must be in `[0, 1]`:

- `0` means the beginning of the search;
- `1` means the end of the search.

For a deterministic iteration limit:

```cpp
double progress = double(iteration + 1) / iteration_limit;
```

For a time limit:

```cpp
double progress = std::min(timer.elapsed() / time_limit, 1.0);
```

Two schedules are available:

| Schedule | Temperature at progress `p` | Notes |
| --- | --- | --- |
| `AnnealingCooling::exponential` | `start * pow(end / start, p)` | Default; both temperatures must be positive. |
| `AnnealingCooling::linear` | `start + (end - start) * p` | May end at exactly zero for greedy final moves. |

Temperature is measured in the same scale as the score difference. As a
practical starting point, estimate the magnitude `D` of a typical worsening
move and choose a starting temperature that accepts a useful fraction of those
moves. To target probability `p`, use `T = -D / log(p)`. Then tune from observed
acceptance rates and solution quality.

## API

| Method | Description | Complexity |
| --- | --- | --- |
| `SimulatedAnnealing(double start_temperature, double end_temperature, Objective objective = Objective::maximize, AnnealingCooling cooling = AnnealingCooling::exponential)` | Creates an annealing policy. | $O(1)$ |
| `double temperature(double progress) const` | Returns the scheduled temperature. | $O(1)$ |
| `double acceptance_probability_delta(long double delta, double progress) const` | Returns the acceptance probability for `delta = candidate - current`. | $O(1)$ |
| `bool accept_delta(long double delta, double progress, double random01) const` | Tests a precomputed delta against supplied randomness. | $O(1)$ |
| `template <std::convertible_to<long double> CurrentScore, std::convertible_to<long double> CandidateScore> double acceptance_probability(CurrentScore current_score, CandidateScore candidate_score, double progress) const` | Score-based probability calculation. | $O(1)$ |
| `template <std::convertible_to<long double> CurrentScore, std::convertible_to<long double> CandidateScore> bool accept(CurrentScore current_score, CandidateScore candidate_score, double progress, double random01) const` | Score-based acceptance decision. | $O(1)$ |

Construct a minimization policy as follows:

```cpp
m1une::heuristic::SimulatedAnnealing annealing(
    100.0, 0.01, m1une::heuristic::Objective::minimize);
```

`AnnealingObjective` remains an alias of `Objective`.

## Fast Incremental-Move Pattern

When a move's delta can be computed without evaluating the whole state:

```cpp
Move move = propose_move();
long long delta = score_difference(move);
if (annealing.accept_delta(delta, progress, random.real())) {
    apply_move(move);
    current_score += delta;
}
```

If computing the delta requires applying the move first, undo it after a
rejection. `delta` is still `candidate - current`, including for minimization.

## Common Mistakes

- Returning the final current state instead of the best state seen.
- Passing elapsed seconds as `progress`; divide by the time limit first.
- Reversing delta for minimization. The objective already handles the sign.
- Choosing temperatures without considering score scale. Multiplying every
  score by 100 generally requires multiplying temperatures by 100 as well.
- Generating only tiny moves or only huge moves. Neighborhood design is often
  more important than the cooling formula.
