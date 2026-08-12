---
title: Beam Search
documentation_of: ../../heuristic/beam_search.hpp
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
