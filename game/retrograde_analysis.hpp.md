---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: game/all.hpp
    title: Game Library
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/game/game_algorithms.test.cpp
    title: verify/game/game_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"game/retrograde_analysis.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <queue>\n#include <utility>\n#include <vector>\n\n\
    namespace m1une {\nnamespace game {\n\nenum class GameOutcome { Win, Lose, Draw\
    \ };\n\nstruct RetrogradeResult {\n    std::vector<GameOutcome> outcome;\n   \
    \ std::vector<int> distance;\n};\n\n// graph[v] contains the states reachable\
    \ from v in one move.\ninline RetrogradeResult retrograde_analysis(\n    const\
    \ std::vector<std::vector<int>>& graph\n) {\n    const int size = int(graph.size());\n\
    \    std::vector<std::vector<int>> reverse_graph(size);\n    std::vector<int>\
    \ remaining(size);\n    for (int vertex = 0; vertex < size; ++vertex) {\n    \
    \    remaining[vertex] = int(graph[vertex].size());\n        for (int next : graph[vertex])\
    \ {\n            assert(0 <= next && next < size);\n            reverse_graph[next].push_back(vertex);\n\
    \        }\n    }\n\n    std::vector<GameOutcome> outcome(size, GameOutcome::Draw);\n\
    \    std::vector<int> distance(size, -1);\n    std::vector<int> longest_win_successor(size);\n\
    \    std::vector<bool> decided(size);\n    std::queue<int> queue;\n    for (int\
    \ vertex = 0; vertex < size; ++vertex) {\n        if (remaining[vertex] == 0)\
    \ {\n            outcome[vertex] = GameOutcome::Lose;\n            distance[vertex]\
    \ = 0;\n            decided[vertex] = true;\n            queue.push(vertex);\n\
    \        }\n    }\n\n    while (!queue.empty()) {\n        const int vertex =\
    \ queue.front();\n        queue.pop();\n        for (int previous : reverse_graph[vertex])\
    \ {\n            if (decided[previous]) continue;\n            if (outcome[vertex]\
    \ == GameOutcome::Lose) {\n                outcome[previous] = GameOutcome::Win;\n\
    \                distance[previous] = distance[vertex] + 1;\n                decided[previous]\
    \ = true;\n                queue.push(previous);\n            } else {\n     \
    \           longest_win_successor[previous] = std::max(\n                    longest_win_successor[previous],\n\
    \                    distance[vertex]\n                );\n                if\
    \ (--remaining[previous] == 0) {\n                    outcome[previous] = GameOutcome::Lose;\n\
    \                    distance[previous] = longest_win_successor[previous] + 1;\n\
    \                    decided[previous] = true;\n                    queue.push(previous);\n\
    \                }\n            }\n        }\n    }\n    return {std::move(outcome),\
    \ std::move(distance)};\n}\n\n}  // namespace game\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GAME_RETROGRADE_ANALYSIS_HPP\n#define M1UNE_GAME_RETROGRADE_ANALYSIS_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <queue>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace game {\n\nenum class GameOutcome\
    \ { Win, Lose, Draw };\n\nstruct RetrogradeResult {\n    std::vector<GameOutcome>\
    \ outcome;\n    std::vector<int> distance;\n};\n\n// graph[v] contains the states\
    \ reachable from v in one move.\ninline RetrogradeResult retrograde_analysis(\n\
    \    const std::vector<std::vector<int>>& graph\n) {\n    const int size = int(graph.size());\n\
    \    std::vector<std::vector<int>> reverse_graph(size);\n    std::vector<int>\
    \ remaining(size);\n    for (int vertex = 0; vertex < size; ++vertex) {\n    \
    \    remaining[vertex] = int(graph[vertex].size());\n        for (int next : graph[vertex])\
    \ {\n            assert(0 <= next && next < size);\n            reverse_graph[next].push_back(vertex);\n\
    \        }\n    }\n\n    std::vector<GameOutcome> outcome(size, GameOutcome::Draw);\n\
    \    std::vector<int> distance(size, -1);\n    std::vector<int> longest_win_successor(size);\n\
    \    std::vector<bool> decided(size);\n    std::queue<int> queue;\n    for (int\
    \ vertex = 0; vertex < size; ++vertex) {\n        if (remaining[vertex] == 0)\
    \ {\n            outcome[vertex] = GameOutcome::Lose;\n            distance[vertex]\
    \ = 0;\n            decided[vertex] = true;\n            queue.push(vertex);\n\
    \        }\n    }\n\n    while (!queue.empty()) {\n        const int vertex =\
    \ queue.front();\n        queue.pop();\n        for (int previous : reverse_graph[vertex])\
    \ {\n            if (decided[previous]) continue;\n            if (outcome[vertex]\
    \ == GameOutcome::Lose) {\n                outcome[previous] = GameOutcome::Win;\n\
    \                distance[previous] = distance[vertex] + 1;\n                decided[previous]\
    \ = true;\n                queue.push(previous);\n            } else {\n     \
    \           longest_win_successor[previous] = std::max(\n                    longest_win_successor[previous],\n\
    \                    distance[vertex]\n                );\n                if\
    \ (--remaining[previous] == 0) {\n                    outcome[previous] = GameOutcome::Lose;\n\
    \                    distance[previous] = longest_win_successor[previous] + 1;\n\
    \                    decided[previous] = true;\n                    queue.push(previous);\n\
    \                }\n            }\n        }\n    }\n    return {std::move(outcome),\
    \ std::move(distance)};\n}\n\n}  // namespace game\n}  // namespace m1une\n\n\
    #endif  // M1UNE_GAME_RETROGRADE_ANALYSIS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: game/retrograde_analysis.hpp
  requiredBy:
  - game/all.hpp
  timestamp: '2026-08-24 02:00:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/game_algorithms.test.cpp
documentation_of: game/retrograde_analysis.hpp
layout: document
title: Game Retrograde Analysis
---

## Overview

Classifies every state of a finite directed normal-play game as winning, losing,
or drawing. Unlike Grundy-number computation, the directed graph may contain
cycles. An edge `v -> u` is a legal move, and a state with no legal move is
losing.

A state is winning if it has a move to a losing state, and losing if every move
goes to a winning state. States that cannot be resolved by these rules are
draws. The result also records optimal game length for resolved states: a winner
finishes as soon as possible, while a loser delays defeat as long as possible.

## Types

All types are in namespace `m1une::game`.

`GameOutcome` has the values `Win`, `Lose`, and `Draw`.

`RetrogradeResult` stores:

| Member | Description |
| --- | --- |
| `std::vector<GameOutcome> outcome` | Classification of each state. |
| `std::vector<int> distance` | Moves until termination under optimal play, or `-1` for a draw. |

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
}
```
