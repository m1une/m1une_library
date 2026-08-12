---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: heuristic/beam_search.hpp
    title: Beam Search
  - icon: ':heavy_check_mark:'
    path: heuristic/hill_climbing.hpp
    title: Hill Climbing
  - icon: ':heavy_check_mark:'
    path: heuristic/objective.hpp
    title: Heuristic Objective
  - icon: ':heavy_check_mark:'
    path: heuristic/simulated_annealing.hpp
    title: Simulated Annealing
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/heuristic/simulated_annealing.test.cpp
    title: verify/heuristic/simulated_annealing.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"heuristic/all.hpp\"\n\n\n\n#line 1 \"heuristic/beam_search.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <cstddef>\n#include <functional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"heuristic/objective.hpp\"\n\n\n\nnamespace m1une\
    \ {\nnamespace heuristic {\n\nenum class Objective {\n    minimize,\n    maximize,\n\
    };\n\ntemplate <class Score>\nbool better_score(const Score& first, const Score&\
    \ second,\n                  Objective objective) {\n    if (objective == Objective::maximize)\
    \ return second < first;\n    return first < second;\n}\n\n}  // namespace heuristic\n\
    }  // namespace m1une\n\n\n#line 14 \"heuristic/beam_search.hpp\"\n\nnamespace\
    \ m1une {\nnamespace heuristic {\n\ntemplate <class State, class Score>\nstruct\
    \ BeamSearchResult {\n    State state;\n    Score score;\n    int depth;\n   \
    \ std::size_t expanded_states;\n    std::size_t generated_states;\n};\n\nnamespace\
    \ beam_search_detail {\n\ntemplate <class State, class Score>\nstruct Node {\n\
    \    State state;\n    Score score;\n    std::size_t order;\n};\n\ntemplate <class\
    \ State, class Score>\nstruct BetterNode {\n    Objective objective;\n\n    bool\
    \ operator()(const Node<State, Score>& first,\n                    const Node<State,\
    \ Score>& second) const {\n        if (better_score(first.score, second.score,\
    \ objective)) return true;\n        if (better_score(second.score, first.score,\
    \ objective)) return false;\n        return first.order < second.order;\n    }\n\
    };\n\n}  // namespace beam_search_detail\n\n// expand(state, next_depth) may return\
    \ a range of children. For allocation-free\n// generation, expand(state, next_depth,\
    \ emit) may instead call emit(child).\n// evaluate(state) returns its score. The\
    \ best beam_width states are retained at\n// every depth, and the best state in\
    \ the last non-empty layer is returned.\ntemplate <class State, class Expand,\
    \ class Evaluate>\nauto beam_search(State initial_state, int depth_limit, int\
    \ beam_width,\n                 Expand expand, Evaluate evaluate,\n          \
    \       Objective objective = Objective::maximize) {\n    assert(0 <= depth_limit);\n\
    \    assert(0 < beam_width);\n\n    using Score = std::remove_cvref_t<\n     \
    \   std::invoke_result_t<Evaluate&, const State&>>;\n    using Node = beam_search_detail::Node<State,\
    \ Score>;\n    using Better = beam_search_detail::BetterNode<State, Score>;\n\n\
    \    Score initial_score = std::invoke(evaluate, initial_state);\n    std::vector<Node>\
    \ beam;\n    beam.push_back(Node{std::move(initial_state),\n                 \
    \       std::move(initial_score), 0});\n\n    std::size_t expanded_states = 0;\n\
    \    std::size_t generated_states = 0;\n    int reached_depth = 0;\n    if (depth_limit\
    \ < 0 || beam_width <= 0) depth_limit = 0;\n\n    Better better{objective};\n\
    \    for (int next_depth = 1; next_depth <= depth_limit; next_depth++) {\n   \
    \     std::vector<Node> candidates;\n        candidates.reserve(static_cast<std::size_t>(beam_width));\n\
    \        std::size_t order = 0;\n\n        for (const Node& node : beam) {\n \
    \           expanded_states++;\n            auto emit = [&](auto&& candidate_state)\
    \ {\n                using Candidate = decltype(candidate_state);\n          \
    \      static_assert(std::is_constructible_v<State, Candidate>);\n           \
    \     State state(std::forward<Candidate>(candidate_state));\n               \
    \ Score candidate_score = std::invoke(evaluate, state);\n                Node\
    \ candidate{std::move(state), std::move(candidate_score),\n                  \
    \             order++};\n                generated_states++;\n               \
    \ if (int(candidates.size()) < beam_width) {\n                    candidates.push_back(std::move(candidate));\n\
    \                    std::push_heap(candidates.begin(), candidates.end(), better);\n\
    \                } else if (better(candidate, candidates.front())) {\n       \
    \             std::pop_heap(candidates.begin(), candidates.end(), better);\n \
    \                   candidates.back() = std::move(candidate);\n              \
    \      std::push_heap(candidates.begin(), candidates.end(), better);\n       \
    \         }\n            };\n            if constexpr (std::invocable<Expand&,\
    \ const State&, int>) {\n                auto next_states =\n                \
    \    std::invoke(expand, node.state, next_depth);\n                for (auto&\
    \ candidate_state : next_states) {\n                    emit(std::move(candidate_state));\n\
    \                }\n            } else if constexpr (std::invocable<Expand&, const\
    \ State&>) {\n                auto next_states = std::invoke(expand, node.state);\n\
    \                for (auto& candidate_state : next_states) {\n               \
    \     emit(std::move(candidate_state));\n                }\n            } else\
    \ {\n                std::invoke(expand, node.state, next_depth, emit);\n    \
    \        }\n        }\n\n        if (candidates.empty()) break;\n        beam\
    \ = std::move(candidates);\n        reached_depth = next_depth;\n    }\n\n   \
    \ int best = 0;\n    for (int index = 1; index < int(beam.size()); index++) {\n\
    \        if (better(beam[index], beam[best])) best = index;\n    }\n    return\
    \ BeamSearchResult<State, Score>{\n        std::move(beam[best].state), std::move(beam[best].score),\n\
    \        reached_depth, expanded_states, generated_states};\n}\n\n}  // namespace\
    \ heuristic\n}  // namespace m1une\n\n\n#line 1 \"heuristic/hill_climbing.hpp\"\
    \n\n\n\n#line 5 \"heuristic/hill_climbing.hpp\"\n\n#line 7 \"heuristic/hill_climbing.hpp\"\
    \n\nnamespace m1une {\nnamespace heuristic {\n\nusing HillClimbingObjective =\
    \ Objective;\n\nclass HillClimbing {\n   private:\n    Objective _objective;\n\
    \    bool _accept_equal;\n\n   public:\n    explicit HillClimbing(Objective objective\
    \ = Objective::maximize,\n                          bool accept_equal = false)\n\
    \        : _objective(objective), _accept_equal(accept_equal) {}\n\n    bool accept_delta(long\
    \ double candidate_minus_current) const {\n        if (_objective == Objective::maximize)\
    \ {\n            return _accept_equal ? 0.0L <= candidate_minus_current\n    \
    \                             : 0.0L < candidate_minus_current;\n        }\n \
    \       return _accept_equal ? candidate_minus_current <= 0.0L\n             \
    \                : candidate_minus_current < 0.0L;\n    }\n\n    template <std::convertible_to<long\
    \ double> CurrentScore,\n              std::convertible_to<long double> CandidateScore>\n\
    \    bool accept(CurrentScore current_score,\n                CandidateScore candidate_score)\
    \ const {\n        long double delta = static_cast<long double>(candidate_score)\
    \ -\n                            static_cast<long double>(current_score);\n  \
    \      return accept_delta(delta);\n    }\n};\n\n}  // namespace heuristic\n}\
    \  // namespace m1une\n\n\n#line 1 \"heuristic/simulated_annealing.hpp\"\n\n\n\
    \n#line 6 \"heuristic/simulated_annealing.hpp\"\n#include <cmath>\n#line 8 \"\
    heuristic/simulated_annealing.hpp\"\n\n#line 10 \"heuristic/simulated_annealing.hpp\"\
    \n\nnamespace m1une {\nnamespace heuristic {\n\nusing AnnealingObjective = Objective;\n\
    \nenum class AnnealingCooling {\n    linear,\n    exponential,\n};\n\nclass SimulatedAnnealing\
    \ {\n   private:\n    double _start_temperature;\n    double _end_temperature;\n\
    \    AnnealingObjective _objective;\n    AnnealingCooling _cooling;\n\n    long\
    \ double directed_delta(long double candidate_minus_current) const {\n       \
    \ if (_objective == AnnealingObjective::maximize) {\n            return candidate_minus_current;\n\
    \        }\n        return -candidate_minus_current;\n    }\n\n   public:\n  \
    \  SimulatedAnnealing(\n        double start_temperature, double end_temperature,\n\
    \        AnnealingObjective objective = AnnealingObjective::maximize,\n      \
    \  AnnealingCooling cooling = AnnealingCooling::exponential)\n        : _start_temperature(start_temperature),\n\
    \          _end_temperature(end_temperature),\n          _objective(objective),\n\
    \          _cooling(cooling) {\n        assert(std::isfinite(start_temperature));\n\
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
    \ heuristic\n}  // namespace m1une\n\n\n#line 8 \"heuristic/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_HEURISTIC_ALL_HPP

    #define M1UNE_HEURISTIC_ALL_HPP 1


    #include "beam_search.hpp"

    #include "hill_climbing.hpp"

    #include "objective.hpp"

    #include "simulated_annealing.hpp"


    #endif  // M1UNE_HEURISTIC_ALL_HPP

    '
  dependsOn:
  - heuristic/beam_search.hpp
  - heuristic/objective.hpp
  - heuristic/hill_climbing.hpp
  - heuristic/simulated_annealing.hpp
  isVerificationFile: false
  path: heuristic/all.hpp
  requiredBy: []
  timestamp: '2026-08-12 20:17:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/heuristic/simulated_annealing.test.cpp
documentation_of: heuristic/all.hpp
layout: document
title: Heuristic Search
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
