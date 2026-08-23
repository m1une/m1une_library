---
title: Game Retrograde Analysis
documentation_of: ../../game/retrograde_analysis.hpp
---

## Overview

Classifies every state of a finite directed normal-play game as winning, losing,
or drawing. Unlike Grundy-number computation, the directed graph may contain
cycles. An edge `v -> u` is a legal move, and a state with no legal move is
losing.

A state is winning if it has a move to a losing state, and losing if every move
goes to a winning state. States that cannot be resolved by these rules are
draws. The result also records an optimal move and game length for resolved
states: a winner finishes as soon as possible, while a loser delays defeat as
long as possible. For a draw, the returned move preserves the draw.

## Types

All types are in namespace `m1une::game`.

`GameOutcome` has the values `Win`, `Lose`, and `Draw`.

`RetrogradeResult` stores:

| Member | Description |
| --- | --- |
| `std::vector<GameOutcome> outcome` | Classification of each state. |
| `std::vector<int> distance` | Moves until termination under optimal play, or `-1` for a draw. |
| `std::vector<int> move` | Chosen successor, or `-1` for a terminal state. |

## Functions

| Function signature | Description | Complexity |
| --- | --- | --- |
| `RetrogradeResult retrograde_analysis(const std::vector<std::vector<int>>& graph)` | Analyzes all states; `graph[v]` lists states reachable from `v`. | `O(V + E)` time and space |

States and edges are zero-based. Every endpoint must be in `[0, V)`, which is
asserted in debug builds. Self-loops and parallel edges are allowed.

## Example

```cpp
#include "game/retrograde_analysis.hpp"
#include <iostream>
#include <vector>

int main() {
    using m1une::game::GameOutcome;

    std::vector<std::vector<int>> moves(4);
    moves[0] = {1};
    moves[1] = {0};
    moves[2] = {3};

    auto result = m1une::game::retrograde_analysis(moves);
    std::cout << (result.outcome[0] == GameOutcome::Draw) << '\n';
    std::cout << (result.outcome[2] == GameOutcome::Win) << '\n';
    std::cout << result.distance[2] << '\n';  // 1
    std::cout << result.move[2] << '\n';      // 3
}
```
