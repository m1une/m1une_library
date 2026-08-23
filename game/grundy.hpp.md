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
  bundledCode: "#line 1 \"game/grundy.hpp\"\n\n\n\n#include <cassert>\n#include <queue>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace game {\n\n// graph[v] contains\
    \ the states reachable from v in one move.\n// The graph must be a DAG.\ntemplate\
    \ <typename Graph>\nstd::vector<int> grundy_numbers(const Graph& graph) {\n  \
    \  const int size = int(graph.size());\n    std::vector<int> indegree(size);\n\
    \    for (int vertex = 0; vertex < size; ++vertex) {\n        for (int next :\
    \ graph[vertex]) {\n            assert(0 <= next && next < size);\n          \
    \  indegree[next]++;\n        }\n    }\n\n    std::queue<int> queue;\n    for\
    \ (int vertex = 0; vertex < size; ++vertex) {\n        if (indegree[vertex] ==\
    \ 0) queue.push(vertex);\n    }\n    std::vector<int> order;\n    order.reserve(size);\n\
    \    while (!queue.empty()) {\n        const int vertex = queue.front();\n   \
    \     queue.pop();\n        order.push_back(vertex);\n        for (int next :\
    \ graph[vertex]) {\n            if (--indegree[next] == 0) queue.push(next);\n\
    \        }\n    }\n    assert(int(order.size()) == size);\n\n    std::vector<int>\
    \ grundy(size);\n    std::vector<int> seen(size + 1, -1);\n    for (int position\
    \ = size - 1; position >= 0; --position) {\n        const int vertex = order[position];\n\
    \        for (int next : graph[vertex]) {\n            const int value = grundy[next];\n\
    \            if (value <= size) seen[value] = vertex;\n        }\n        while\
    \ (grundy[vertex] <= size && seen[grundy[vertex]] == vertex) {\n            grundy[vertex]++;\n\
    \        }\n    }\n    return grundy;\n}\n\n}  // namespace game\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_GAME_GRUNDY_HPP\n#define M1UNE_GAME_GRUNDY_HPP 1\n\n#include\
    \ <cassert>\n#include <queue>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ game {\n\n// graph[v] contains the states reachable from v in one move.\n//\
    \ The graph must be a DAG.\ntemplate <typename Graph>\nstd::vector<int> grundy_numbers(const\
    \ Graph& graph) {\n    const int size = int(graph.size());\n    std::vector<int>\
    \ indegree(size);\n    for (int vertex = 0; vertex < size; ++vertex) {\n     \
    \   for (int next : graph[vertex]) {\n            assert(0 <= next && next < size);\n\
    \            indegree[next]++;\n        }\n    }\n\n    std::queue<int> queue;\n\
    \    for (int vertex = 0; vertex < size; ++vertex) {\n        if (indegree[vertex]\
    \ == 0) queue.push(vertex);\n    }\n    std::vector<int> order;\n    order.reserve(size);\n\
    \    while (!queue.empty()) {\n        const int vertex = queue.front();\n   \
    \     queue.pop();\n        order.push_back(vertex);\n        for (int next :\
    \ graph[vertex]) {\n            if (--indegree[next] == 0) queue.push(next);\n\
    \        }\n    }\n    assert(int(order.size()) == size);\n\n    std::vector<int>\
    \ grundy(size);\n    std::vector<int> seen(size + 1, -1);\n    for (int position\
    \ = size - 1; position >= 0; --position) {\n        const int vertex = order[position];\n\
    \        for (int next : graph[vertex]) {\n            const int value = grundy[next];\n\
    \            if (value <= size) seen[value] = vertex;\n        }\n        while\
    \ (grundy[vertex] <= size && seen[grundy[vertex]] == vertex) {\n            grundy[vertex]++;\n\
    \        }\n    }\n    return grundy;\n}\n\n}  // namespace game\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GAME_GRUNDY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: game/grundy.hpp
  requiredBy:
  - game/all.hpp
  timestamp: '2026-08-24 02:00:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/game_algorithms.test.cpp
documentation_of: game/grundy.hpp
layout: document
title: Grundy Numbers
---

## Overview

Computes the Sprague-Grundy number of every state in a finite directed acyclic
impartial game. An edge `v -> u` means that a player may move from state `v` to
state `u`. Terminal states receive Grundy number zero, and every other state
receives the minimum excluded Grundy number of its successors.

The xor of the Grundy numbers of independent components is nonzero exactly when
their disjoint sum is winning under normal play.

## Functions

All functions are in namespace `m1une::game`.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `template<class Graph>`<br>`std::vector<int> grundy_numbers(const Graph& graph)` | Returns one Grundy number per state. `graph[v]` lists states reachable from `v`. | `O(V + E)` time, `O(V)` extra space |

States and edges are zero-based. Every endpoint must be in `[0, V)`, and the
graph must be acyclic; both conditions are asserted in debug builds. Parallel
edges are allowed and do not affect the result.

## Example

```cpp
#include "game/grundy.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> moves(4);
    moves[0] = {1, 2};
    moves[1] = {3};
    moves[2] = {3};

    auto grundy = m1une::game::grundy_numbers(moves);
    std::cout << grundy[0] << '\n';  // 0
}
```
