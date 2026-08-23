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
  - icon: ':heavy_check_mark:'
    path: verify/game/partisan_minimax.test.cpp
    title: verify/game/partisan_minimax.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"game/partisan_game.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <queue>\n#include <vector>\n\nnamespace m1une {\nnamespace game {\n\nenum class\
    \ PartisanOutcome { Left, Right, Next, Previous };\n\ninline std::vector<PartisanOutcome>\
    \ partisan_outcomes(\n    const std::vector<std::vector<int>>& left_moves,\n \
    \   const std::vector<std::vector<int>>& right_moves\n) {\n    const int size\
    \ = int(left_moves.size());\n    assert(int(right_moves.size()) == size);\n\n\
    \    std::vector<int> indegree(size);\n    for (int vertex = 0; vertex < size;\
    \ ++vertex) {\n        for (int next : left_moves[vertex]) {\n            assert(0\
    \ <= next && next < size);\n            indegree[next]++;\n        }\n       \
    \ for (int next : right_moves[vertex]) {\n            assert(0 <= next && next\
    \ < size);\n            indegree[next]++;\n        }\n    }\n\n    std::queue<int>\
    \ queue;\n    for (int vertex = 0; vertex < size; ++vertex) {\n        if (indegree[vertex]\
    \ == 0) queue.push(vertex);\n    }\n    std::vector<int> order;\n    order.reserve(size);\n\
    \    while (!queue.empty()) {\n        const int vertex = queue.front();\n   \
    \     queue.pop();\n        order.push_back(vertex);\n        for (int next :\
    \ left_moves[vertex]) {\n            if (--indegree[next] == 0) queue.push(next);\n\
    \        }\n        for (int next : right_moves[vertex]) {\n            if (--indegree[next]\
    \ == 0) queue.push(next);\n        }\n    }\n    assert(int(order.size()) == size);\n\
    \n    std::vector<bool> left_wins_moving(size);\n    std::vector<bool> left_wins_waiting(size);\n\
    \    std::vector<PartisanOutcome> outcome(size);\n    for (int position = size\
    \ - 1; position >= 0; --position) {\n        const int vertex = order[position];\n\
    \        for (int next : left_moves[vertex]) {\n            if (left_wins_waiting[next])\
    \ left_wins_moving[vertex] = true;\n        }\n        left_wins_waiting[vertex]\
    \ = true;\n        for (int next : right_moves[vertex]) {\n            if (!left_wins_moving[next])\
    \ left_wins_waiting[vertex] = false;\n        }\n\n        if (left_wins_moving[vertex]\
    \ && left_wins_waiting[vertex]) {\n            outcome[vertex] = PartisanOutcome::Left;\n\
    \        } else if (!left_wins_moving[vertex] && !left_wins_waiting[vertex]) {\n\
    \            outcome[vertex] = PartisanOutcome::Right;\n        } else if (left_wins_moving[vertex])\
    \ {\n            outcome[vertex] = PartisanOutcome::Next;\n        } else {\n\
    \            outcome[vertex] = PartisanOutcome::Previous;\n        }\n    }\n\
    \    return outcome;\n}\n\n}  // namespace game\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GAME_PARTISAN_GAME_HPP\n#define M1UNE_GAME_PARTISAN_GAME_HPP\
    \ 1\n\n#include <cassert>\n#include <queue>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace game {\n\nenum class PartisanOutcome { Left, Right, Next, Previous\
    \ };\n\ninline std::vector<PartisanOutcome> partisan_outcomes(\n    const std::vector<std::vector<int>>&\
    \ left_moves,\n    const std::vector<std::vector<int>>& right_moves\n) {\n   \
    \ const int size = int(left_moves.size());\n    assert(int(right_moves.size())\
    \ == size);\n\n    std::vector<int> indegree(size);\n    for (int vertex = 0;\
    \ vertex < size; ++vertex) {\n        for (int next : left_moves[vertex]) {\n\
    \            assert(0 <= next && next < size);\n            indegree[next]++;\n\
    \        }\n        for (int next : right_moves[vertex]) {\n            assert(0\
    \ <= next && next < size);\n            indegree[next]++;\n        }\n    }\n\n\
    \    std::queue<int> queue;\n    for (int vertex = 0; vertex < size; ++vertex)\
    \ {\n        if (indegree[vertex] == 0) queue.push(vertex);\n    }\n    std::vector<int>\
    \ order;\n    order.reserve(size);\n    while (!queue.empty()) {\n        const\
    \ int vertex = queue.front();\n        queue.pop();\n        order.push_back(vertex);\n\
    \        for (int next : left_moves[vertex]) {\n            if (--indegree[next]\
    \ == 0) queue.push(next);\n        }\n        for (int next : right_moves[vertex])\
    \ {\n            if (--indegree[next] == 0) queue.push(next);\n        }\n   \
    \ }\n    assert(int(order.size()) == size);\n\n    std::vector<bool> left_wins_moving(size);\n\
    \    std::vector<bool> left_wins_waiting(size);\n    std::vector<PartisanOutcome>\
    \ outcome(size);\n    for (int position = size - 1; position >= 0; --position)\
    \ {\n        const int vertex = order[position];\n        for (int next : left_moves[vertex])\
    \ {\n            if (left_wins_waiting[next]) left_wins_moving[vertex] = true;\n\
    \        }\n        left_wins_waiting[vertex] = true;\n        for (int next :\
    \ right_moves[vertex]) {\n            if (!left_wins_moving[next]) left_wins_waiting[vertex]\
    \ = false;\n        }\n\n        if (left_wins_moving[vertex] && left_wins_waiting[vertex])\
    \ {\n            outcome[vertex] = PartisanOutcome::Left;\n        } else if (!left_wins_moving[vertex]\
    \ && !left_wins_waiting[vertex]) {\n            outcome[vertex] = PartisanOutcome::Right;\n\
    \        } else if (left_wins_moving[vertex]) {\n            outcome[vertex] =\
    \ PartisanOutcome::Next;\n        } else {\n            outcome[vertex] = PartisanOutcome::Previous;\n\
    \        }\n    }\n    return outcome;\n}\n\n}  // namespace game\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GAME_PARTISAN_GAME_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: game/partisan_game.hpp
  requiredBy:
  - game/all.hpp
  timestamp: '2026-08-24 02:13:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/partisan_minimax.test.cpp
  - verify/game/game_algorithms.test.cpp
documentation_of: game/partisan_game.hpp
layout: document
title: Partisan Game Outcomes
---

## Overview

Classifies every position of a finite short partisan game. Left and Right may
have different legal moves, and the player with no legal move loses. The union
of both move graphs must be acyclic, so every play terminates.

Unlike an ordinary win/lose result, a partisan position belongs to one of four
outcome classes because the identity of the starting player matters.

## Types

`PartisanOutcome` has four values:

| Value | Meaning |
| --- | --- |
| `Left` | Left wins regardless of who starts. |
| `Right` | Right wins regardless of who starts. |
| `Next` | The next player wins. |
| `Previous` | The second player wins. |

## Functions

All APIs are in namespace `m1une::game`.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `std::vector<PartisanOutcome> partisan_outcomes(const std::vector<std::vector<int>>& left_moves, const std::vector<std::vector<int>>& right_moves)` | Returns the outcome class of every state. | `O(V + E_left + E_right)` time, `O(V)` extra space |

`left_moves[v]` and `right_moves[v]` list the states available to the respective
player from state `v`. Both arrays must have the same size, all endpoints must
be zero-based indices in `[0, V)`, and their combined graph must be acyclic.
These conditions are asserted in debug builds.

## Example

```cpp
#include "game/partisan_game.hpp"
#include <iostream>
#include <vector>

int main() {
    using m1une::game::PartisanOutcome;

    std::vector<std::vector<int>> left(2), right(2);
    left[0].push_back(1);
    auto outcome = m1une::game::partisan_outcomes(left, right);
    std::cout << (outcome[0] == PartisanOutcome::Left) << '\n';
    std::cout << (outcome[1] == PartisanOutcome::Previous) << '\n';
}
```
