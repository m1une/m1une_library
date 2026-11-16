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
  bundledCode: "#line 1 \"game/minimax.hpp\"\n\n\n\n#include <cassert>\n#include <queue>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace game {\n\
    \ntemplate <typename T>\nstruct MinimaxResult {\n    std::vector<T> value;\n \
    \   std::vector<int> move;\n};\n\ntemplate <typename T>\nMinimaxResult<T> dag_minimax(\n\
    \    const std::vector<std::vector<int>>& graph,\n    const std::vector<T>& terminal_value,\n\
    \    const std::vector<bool>& maximize\n) {\n    const int size = int(graph.size());\n\
    \    assert(int(terminal_value.size()) == size);\n    assert(int(maximize.size())\
    \ == size);\n\n    std::vector<int> indegree(size);\n    for (int vertex = 0;\
    \ vertex < size; ++vertex) {\n        for (int next : graph[vertex]) {\n     \
    \       assert(0 <= next && next < size);\n            indegree[next]++;\n   \
    \     }\n    }\n\n    std::queue<int> queue;\n    for (int vertex = 0; vertex\
    \ < size; ++vertex) {\n        if (indegree[vertex] == 0) queue.push(vertex);\n\
    \    }\n    std::vector<int> order;\n    order.reserve(size);\n    while (!queue.empty())\
    \ {\n        const int vertex = queue.front();\n        queue.pop();\n       \
    \ order.push_back(vertex);\n        for (int next : graph[vertex]) {\n       \
    \     if (--indegree[next] == 0) queue.push(next);\n        }\n    }\n    assert(int(order.size())\
    \ == size);\n\n    std::vector<T> value = terminal_value;\n    std::vector<int>\
    \ move(size, -1);\n    for (int position = size - 1; position >= 0; --position)\
    \ {\n        const int vertex = order[position];\n        if (graph[vertex].empty())\
    \ {\n            value[vertex] = terminal_value[vertex];\n            continue;\n\
    \        }\n\n        move[vertex] = graph[vertex][0];\n        value[vertex]\
    \ = value[move[vertex]];\n        for (int next : graph[vertex]) {\n         \
    \   const bool improves = maximize[vertex]\n                                 \
    \     ? value[vertex] < value[next]\n                                      : value[next]\
    \ < value[vertex];\n            if (improves) {\n                value[vertex]\
    \ = value[next];\n                move[vertex] = next;\n            }\n      \
    \  }\n    }\n    return {std::move(value), std::move(move)};\n}\n\n}  // namespace\
    \ game\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GAME_MINIMAX_HPP\n#define M1UNE_GAME_MINIMAX_HPP 1\n\n#include\
    \ <cassert>\n#include <queue>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace game {\n\ntemplate <typename T>\nstruct MinimaxResult {\n\
    \    std::vector<T> value;\n    std::vector<int> move;\n};\n\ntemplate <typename\
    \ T>\nMinimaxResult<T> dag_minimax(\n    const std::vector<std::vector<int>>&\
    \ graph,\n    const std::vector<T>& terminal_value,\n    const std::vector<bool>&\
    \ maximize\n) {\n    const int size = int(graph.size());\n    assert(int(terminal_value.size())\
    \ == size);\n    assert(int(maximize.size()) == size);\n\n    std::vector<int>\
    \ indegree(size);\n    for (int vertex = 0; vertex < size; ++vertex) {\n     \
    \   for (int next : graph[vertex]) {\n            assert(0 <= next && next < size);\n\
    \            indegree[next]++;\n        }\n    }\n\n    std::queue<int> queue;\n\
    \    for (int vertex = 0; vertex < size; ++vertex) {\n        if (indegree[vertex]\
    \ == 0) queue.push(vertex);\n    }\n    std::vector<int> order;\n    order.reserve(size);\n\
    \    while (!queue.empty()) {\n        const int vertex = queue.front();\n   \
    \     queue.pop();\n        order.push_back(vertex);\n        for (int next :\
    \ graph[vertex]) {\n            if (--indegree[next] == 0) queue.push(next);\n\
    \        }\n    }\n    assert(int(order.size()) == size);\n\n    std::vector<T>\
    \ value = terminal_value;\n    std::vector<int> move(size, -1);\n    for (int\
    \ position = size - 1; position >= 0; --position) {\n        const int vertex\
    \ = order[position];\n        if (graph[vertex].empty()) {\n            value[vertex]\
    \ = terminal_value[vertex];\n            continue;\n        }\n\n        move[vertex]\
    \ = graph[vertex][0];\n        value[vertex] = value[move[vertex]];\n        for\
    \ (int next : graph[vertex]) {\n            const bool improves = maximize[vertex]\n\
    \                                      ? value[vertex] < value[next]\n       \
    \                               : value[next] < value[vertex];\n            if\
    \ (improves) {\n                value[vertex] = value[next];\n               \
    \ move[vertex] = next;\n            }\n        }\n    }\n    return {std::move(value),\
    \ std::move(move)};\n}\n\n}  // namespace game\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_GAME_MINIMAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: game/minimax.hpp
  requiredBy:
  - game/all.hpp
  timestamp: '2026-08-24 02:13:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/partisan_minimax.test.cpp
  - verify/game/game_algorithms.test.cpp
documentation_of: game/minimax.hpp
layout: document
title: DAG Minimax
---

## Overview

Evaluates a finite scoring game represented by a directed acyclic graph. Each
nonterminal state is controlled by either a maximizing or minimizing player.
Terminal states carry values, and backward induction determines both the value
and one optimal move for every state.

This representation supports transpositions directly: several states may lead
to the same successor, which is evaluated only once.

## Types

`MinimaxResult<T>` stores:

| Member | Description |
| --- | --- |
| `std::vector<T> value` | Minimax value of every state. |
| `std::vector<int> move` | Chosen zero-based successor, or `-1` at a terminal state. |

## Functions

All APIs are in namespace `m1une::game`. Values must be copyable and comparable
with `<`.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `template<class T>`<br>`MinimaxResult<T> dag_minimax(const std::vector<std::vector<int>>& graph, const std::vector<T>& terminal_value, const std::vector<bool>& maximize)` | Evaluates every state and recovers one optimal move. | `O(V + E)` time, `O(V)` extra space |

All three arrays must have size `V`. `terminal_value[v]` is used only when
`graph[v]` is empty. At a nonterminal state, `maximize[v]` selects maximum or
minimum play. On equal values, the first optimal successor listed in `graph[v]`
is returned. Endpoints must lie in `[0, V)`, and the graph must be acyclic;
these conditions are asserted in debug builds.

## Example

```cpp
#include "game/minimax.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> graph(5);
    graph[0] = {1, 2};
    graph[1] = {3, 4};
    graph[2] = {3, 4};
    std::vector<int> terminal_value = {0, 0, 0, -4, 7};
    std::vector<bool> maximize = {true, false, false, false, false};

    auto result = m1une::game::dag_minimax(
        graph,
        terminal_value,
        maximize
    );
    std::cout << result.value[0] << '\n';
    std::cout << result.move[0] << '\n';
}
```
