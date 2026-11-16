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
    path: verify/heuristic/beam_search.test.cpp
    title: verify/heuristic/beam_search.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/heuristic/simulated_annealing.test.cpp
    title: verify/heuristic/simulated_annealing.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"heuristic/beam_search.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <functional>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\n#line 1 \"heuristic/objective.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace heuristic {\n\nenum class Objective {\n \
    \   minimize,\n    maximize,\n};\n\ntemplate <class Score>\nbool better_score(const\
    \ Score& first, const Score& second,\n                  Objective objective) {\n\
    \    if (objective == Objective::maximize) return second < first;\n    return\
    \ first < second;\n}\n\n}  // namespace heuristic\n}  // namespace m1une\n\n\n\
    #line 14 \"heuristic/beam_search.hpp\"\n\nnamespace m1une {\nnamespace heuristic\
    \ {\n\ntemplate <class State, class Score>\nstruct BeamSearchResult {\n    State\
    \ state;\n    Score score;\n    int depth;\n    std::size_t expanded_states;\n\
    \    std::size_t generated_states;\n};\n\nnamespace beam_search_detail {\n\ntemplate\
    \ <class State, class Score>\nstruct Node {\n    State state;\n    Score score;\n\
    \    std::size_t order;\n};\n\ntemplate <class State, class Score>\nstruct BetterNode\
    \ {\n    Objective objective;\n\n    bool operator()(const Node<State, Score>&\
    \ first,\n                    const Node<State, Score>& second) const {\n    \
    \    if (better_score(first.score, second.score, objective)) return true;\n  \
    \      if (better_score(second.score, first.score, objective)) return false;\n\
    \        return first.order < second.order;\n    }\n};\n\n}  // namespace beam_search_detail\n\
    \n// expand(state, next_depth) may return a range of children. For allocation-free\n\
    // generation, expand(state, next_depth, emit) may instead call emit(child).\n\
    // evaluate(state) returns its score. The best beam_width states are retained\
    \ at\n// every depth, and the best state in the last non-empty layer is returned.\n\
    template <class State, class Expand, class Evaluate>\nauto beam_search(State initial_state,\
    \ int depth_limit, int beam_width,\n                 Expand expand, Evaluate evaluate,\n\
    \                 Objective objective = Objective::maximize) {\n    assert(0 <=\
    \ depth_limit);\n    assert(0 < beam_width);\n\n    using Score = std::remove_cvref_t<\n\
    \        std::invoke_result_t<Evaluate&, const State&>>;\n    using Node = beam_search_detail::Node<State,\
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
    \ heuristic\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_HEURISTIC_BEAM_SEARCH_HPP\n#define M1UNE_HEURISTIC_BEAM_SEARCH_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <cstddef>\n#include <functional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#include \"objective.hpp\"\n\nnamespace m1une {\nnamespace\
    \ heuristic {\n\ntemplate <class State, class Score>\nstruct BeamSearchResult\
    \ {\n    State state;\n    Score score;\n    int depth;\n    std::size_t expanded_states;\n\
    \    std::size_t generated_states;\n};\n\nnamespace beam_search_detail {\n\ntemplate\
    \ <class State, class Score>\nstruct Node {\n    State state;\n    Score score;\n\
    \    std::size_t order;\n};\n\ntemplate <class State, class Score>\nstruct BetterNode\
    \ {\n    Objective objective;\n\n    bool operator()(const Node<State, Score>&\
    \ first,\n                    const Node<State, Score>& second) const {\n    \
    \    if (better_score(first.score, second.score, objective)) return true;\n  \
    \      if (better_score(second.score, first.score, objective)) return false;\n\
    \        return first.order < second.order;\n    }\n};\n\n}  // namespace beam_search_detail\n\
    \n// expand(state, next_depth) may return a range of children. For allocation-free\n\
    // generation, expand(state, next_depth, emit) may instead call emit(child).\n\
    // evaluate(state) returns its score. The best beam_width states are retained\
    \ at\n// every depth, and the best state in the last non-empty layer is returned.\n\
    template <class State, class Expand, class Evaluate>\nauto beam_search(State initial_state,\
    \ int depth_limit, int beam_width,\n                 Expand expand, Evaluate evaluate,\n\
    \                 Objective objective = Objective::maximize) {\n    assert(0 <=\
    \ depth_limit);\n    assert(0 < beam_width);\n\n    using Score = std::remove_cvref_t<\n\
    \        std::invoke_result_t<Evaluate&, const State&>>;\n    using Node = beam_search_detail::Node<State,\
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
    \ heuristic\n}  // namespace m1une\n\n#endif  // M1UNE_HEURISTIC_BEAM_SEARCH_HPP\n"
  dependsOn:
  - heuristic/objective.hpp
  isVerificationFile: false
  path: heuristic/beam_search.hpp
  requiredBy:
  - heuristic/all.hpp
  timestamp: '2026-08-12 20:17:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/heuristic/simulated_annealing.test.cpp
  - verify/heuristic/beam_search.test.cpp
documentation_of: heuristic/beam_search.hpp
layout: document
title: Beam Search
---

## What It Does

Beam search constructs solutions one decision at a time. At each depth:

1. every state in the current beam generates children;
2. every child receives a score;
3. only the best `beam_width` children survive.

Unlike local search, beam search holds several states at once. Unlike exhaustive
search, its memory stays bounded. A larger beam usually explores more choices
but costs more time and memory.

The easiest interface lets `expand` return a vector of children:

```cpp
auto expand = [](const State& state, int next_depth) {
    std::vector<State> children;
    // Add every possible one-step continuation to children.
    return children;
};
```

`next_depth` is `1` while expanding the initial state, then `2`, and so on.
An overload without the depth parameter is also accepted:

```cpp
auto expand = [](const State& state) {
    std::vector<State> children;
    return children;
};
```

## Complete Example

This example chooses exactly three distinct values while maximizing their sum.
The state stores which index may be chosen next, the chosen indices, and the
incrementally maintained score.

```cpp
#include "heuristic/beam_search.hpp"

#include <iostream>
#include <utility>
#include <vector>

struct State {
    int next_index = 0;
    std::vector<int> chosen_indices;
    int score = 0;
};

int main() {
    const std::vector<int> values = {7, -2, 10, 5, 8, 4};

    auto expand = [&](const State& state, int) {
        std::vector<State> children;
        for (int index = state.next_index;
             index < int(values.size()); index++) {
            State child = state;
            child.next_index = index + 1;
            child.chosen_indices.push_back(index);
            child.score += values[index];
            children.push_back(std::move(child));
        }
        return children;
    };

    auto evaluate = [](const State& state) {
        return state.score;
    };

    State initial;
    auto result = m1une::heuristic::beam_search(
        std::move(initial), 3, 100, expand, evaluate,
        m1une::heuristic::Objective::maximize);

    std::cout << result.score << '\n';
    for (int index : result.state.chosen_indices) {
        std::cout << index << ' ';
    }
    std::cout << '\n';
}
```

Here `depth_limit = 3` means three indices are selected. `beam_width = 100` is
large enough to retain every partial combination in this small example. On a
real problem, reduce the width until time and memory fit the contest limit.

## Function Contract

```cpp
template <class State, class Expand, class Evaluate>
auto beam_search(
    State initial_state,
    int depth_limit,
    int beam_width,
    Expand expand,
    Evaluate evaluate,
    Objective objective = Objective::maximize
);
```

| Argument | Meaning |
| --- | --- |
| `initial_state` | State at depth zero. It is moved into the search. |
| `depth_limit` | Maximum number of construction steps; must be nonnegative. |
| `beam_width` | Maximum states retained after each step; must be positive. |
| `expand` | Returns or emits all one-step children of a state. |
| `evaluate` | Returns the score used to rank states at the same depth. |
| `objective` | Chooses whether smaller or larger scores are better. |

The returned type is `BeamSearchResult<State, Score>`:

| Member | Meaning |
| --- | --- |
| `State state` | Best state in the last non-empty layer. |
| `Score score` | `evaluate(state)`. |
| `int depth` | Depth of the returned layer. |
| `size_t expanded_states` | Number of calls to `expand`. |
| `size_t generated_states` | Number of children generated before pruning. |

If no state generates a child, search stops early and returns the best state in
the previous non-empty layer. The function returns the best state from the
final layer, not the best score seen across incomparable depths.

If `C_d` children are generated at depth `d` and `B` is the beam width, time is
$O(\sum_d C_d \log(B+1))$ plus expansion and evaluation. Extra memory is
$O(B)$ states, excluding temporary vectors returned by the simple interface.

## Allocation-Conscious Expansion

Returning a vector is easiest, but it temporarily stores all children of one
state. For large branching factors, use the emitter interface. Instead of
returning a vector, accept a third argument and call it once per child:

```cpp
auto expand = [&](const State& state, int next_depth, auto emit) {
    for (int move = 0; move < move_count(state); move++) {
        State child = make_child(state, move, next_depth);
        emit(std::move(child));
    }
};
```

The call to `beam_search` is otherwise identical. Each emitted state is scored
immediately, and rejected states are discarded without building a child vector.
This form also supports move-only state types.

## Designing the Score

`evaluate` ranks **partial states at the same depth**. A useful beam score often
combines the value already obtained with an estimate of future potential. For
maximization, a typical pattern is:

```text
beam_score = current_value + estimated_remaining_value
```

A final-answer score alone may rank partial states poorly. If a promising path
starts slowly, a narrow beam can delete it before its later benefit appears.
Improving the estimate or increasing `beam_width` can help.

## Common Mistakes

- Using minimization scores without passing `Objective::minimize`.
- Setting the width so small that all diverse partial solutions disappear.
- Comparing scores whose meaning changes unpredictably between states at the
  same depth.
- Forgetting that duplicate states consume separate beam slots. Deduplicate
  during expansion when multiple paths often reach the same state.
- Expecting an exact answer. Beam search becomes exhaustive only when the width
  is large enough to retain every relevant state.
- Storing a huge history inside every state. Prefer compact states or parent
  reconstruction when copying dominates runtime.
