---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: game/all.hpp
    title: Game Library
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/game/classic_games.test.cpp
    title: verify/game/classic_games.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/game/game_algorithms.test.cpp
    title: verify/game/game_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"game/green_hackenbush.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <vector>\n\nnamespace m1une {\nnamespace game {\n\
    \n// Every vertex represents one green edge. parent[v] == -1 attaches that edge\n\
    // to the ground; otherwise it attaches it above the edge parent[v].\ninline uint64_t\
    \ green_hackenbush_grundy(const std::vector<int>& parent) {\n    const int size\
    \ = int(parent.size());\n    std::vector<std::vector<int>> children(size);\n \
    \   std::vector<int> roots;\n    for (int edge = 0; edge < size; ++edge) {\n \
    \       assert(-1 <= parent[edge] && parent[edge] < size);\n        assert(parent[edge]\
    \ != edge);\n        if (parent[edge] == -1) {\n            roots.push_back(edge);\n\
    \        } else {\n            children[parent[edge]].push_back(edge);\n     \
    \   }\n    }\n\n    std::vector<int> order = roots;\n    order.reserve(size);\n\
    \    for (int position = 0; position < int(order.size()); ++position) {\n    \
    \    const int edge = order[position];\n        for (int child : children[edge])\
    \ order.push_back(child);\n    }\n    assert(int(order.size()) == size);\n\n \
    \   std::vector<uint64_t> branch(size);\n    for (int position = size - 1; position\
    \ >= 0; --position) {\n        const int edge = order[position];\n        uint64_t\
    \ children_grundy = 0;\n        for (int child : children[edge]) children_grundy\
    \ ^= branch[child];\n        branch[edge] = children_grundy + 1;\n    }\n\n  \
    \  uint64_t result = 0;\n    for (int root : roots) result ^= branch[root];\n\
    \    return result;\n}\n\ninline bool green_hackenbush_first_player_wins(\n  \
    \  const std::vector<int>& parent\n) {\n    return green_hackenbush_grundy(parent)\
    \ != 0;\n}\n\n}  // namespace game\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GAME_GREEN_HACKENBUSH_HPP\n#define M1UNE_GAME_GREEN_HACKENBUSH_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace game {\n\n// Every vertex represents one green edge. parent[v]\
    \ == -1 attaches that edge\n// to the ground; otherwise it attaches it above the\
    \ edge parent[v].\ninline uint64_t green_hackenbush_grundy(const std::vector<int>&\
    \ parent) {\n    const int size = int(parent.size());\n    std::vector<std::vector<int>>\
    \ children(size);\n    std::vector<int> roots;\n    for (int edge = 0; edge <\
    \ size; ++edge) {\n        assert(-1 <= parent[edge] && parent[edge] < size);\n\
    \        assert(parent[edge] != edge);\n        if (parent[edge] == -1) {\n  \
    \          roots.push_back(edge);\n        } else {\n            children[parent[edge]].push_back(edge);\n\
    \        }\n    }\n\n    std::vector<int> order = roots;\n    order.reserve(size);\n\
    \    for (int position = 0; position < int(order.size()); ++position) {\n    \
    \    const int edge = order[position];\n        for (int child : children[edge])\
    \ order.push_back(child);\n    }\n    assert(int(order.size()) == size);\n\n \
    \   std::vector<uint64_t> branch(size);\n    for (int position = size - 1; position\
    \ >= 0; --position) {\n        const int edge = order[position];\n        uint64_t\
    \ children_grundy = 0;\n        for (int child : children[edge]) children_grundy\
    \ ^= branch[child];\n        branch[edge] = children_grundy + 1;\n    }\n\n  \
    \  uint64_t result = 0;\n    for (int root : roots) result ^= branch[root];\n\
    \    return result;\n}\n\ninline bool green_hackenbush_first_player_wins(\n  \
    \  const std::vector<int>& parent\n) {\n    return green_hackenbush_grundy(parent)\
    \ != 0;\n}\n\n}  // namespace game\n}  // namespace m1une\n\n#endif  // M1UNE_GAME_GREEN_HACKENBUSH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: game/green_hackenbush.hpp
  requiredBy:
  - game/all.hpp
  timestamp: '2026-08-24 02:07:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/game_algorithms.test.cpp
  - verify/game/classic_games.test.cpp
documentation_of: game/green_hackenbush.hpp
layout: document
title: Green Hackenbush
---

## Overview

Computes the Grundy number of a finite Green Hackenbush forest. Every edge is
available to both players. Cutting an edge removes that edge and every edge no
longer connected to the ground.

The forest is represented by one vertex per edge. `parent[v] = -1` means edge
`v` touches the ground; otherwise edge `v` is attached immediately above edge
`parent[v]`. This representation handles several grounded components without a
separate virtual root.

The implementation applies the colon principle bottom-up: the nimber of an edge
and everything above it is one plus the xor of its child branches. Grounded
branches are combined with xor.

## Functions

All functions are in namespace `m1une::game`.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `uint64_t green_hackenbush_grundy(const std::vector<int>& parent)` | Returns the forest's Grundy number. | `O(N)` time and space |
| `bool green_hackenbush_first_player_wins(const std::vector<int>& parent)` | Whether the first player wins under normal play. | `O(N)` time and space |

The parent relation must form a rooted forest, and each parent must be `-1` or a
zero-based edge index. These conditions are asserted in debug builds.

## Example

```cpp
#include "game/green_hackenbush.hpp"
#include <iostream>
#include <vector>

int main() {
    // A grounded edge with two edges attached above it.
    std::vector<int> parent = {-1, 0, 0};
    std::cout << m1une::game::green_hackenbush_grundy(parent) << '\n';  // 1
}
```
