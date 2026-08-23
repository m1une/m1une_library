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
  bundledCode: "#line 1 \"game/subtraction_game.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace game {\n\
    \ninline std::vector<int> subtraction_game_grundy(\n    int max_heap,\n    const\
    \ std::vector<int>& moves\n) {\n    assert(max_heap >= 0);\n    for (int move\
    \ : moves) assert(move > 0);\n\n    std::vector<int> grundy(max_heap + 1);\n \
    \   std::vector<int> seen(moves.size() + 1, -1);\n    for (int heap = 1; heap\
    \ <= max_heap; ++heap) {\n        for (int move : moves) {\n            if (move\
    \ > heap) continue;\n            const int value = grundy[heap - move];\n    \
    \        if (value < int(seen.size())) seen[value] = heap;\n        }\n      \
    \  while (\n            grundy[heap] < int(seen.size())\n            && seen[grundy[heap]]\
    \ == heap\n        ) {\n            grundy[heap]++;\n        }\n    }\n    return\
    \ grundy;\n}\n\ninline int subtraction_game_nim_sum(\n    const std::vector<int>&\
    \ heaps,\n    const std::vector<int>& moves\n) {\n    int max_heap = 0;\n    for\
    \ (int heap : heaps) {\n        assert(heap >= 0);\n        max_heap = std::max(max_heap,\
    \ heap);\n    }\n    const std::vector<int> grundy = subtraction_game_grundy(max_heap,\
    \ moves);\n    int result = 0;\n    for (int heap : heaps) result ^= grundy[heap];\n\
    \    return result;\n}\n\ninline bool subtraction_game_first_player_wins(\n  \
    \  const std::vector<int>& heaps,\n    const std::vector<int>& moves\n) {\n  \
    \  return subtraction_game_nim_sum(heaps, moves) != 0;\n}\n\n}  // namespace game\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GAME_SUBTRACTION_GAME_HPP\n#define M1UNE_GAME_SUBTRACTION_GAME_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace game {\n\ninline std::vector<int> subtraction_game_grundy(\n\
    \    int max_heap,\n    const std::vector<int>& moves\n) {\n    assert(max_heap\
    \ >= 0);\n    for (int move : moves) assert(move > 0);\n\n    std::vector<int>\
    \ grundy(max_heap + 1);\n    std::vector<int> seen(moves.size() + 1, -1);\n  \
    \  for (int heap = 1; heap <= max_heap; ++heap) {\n        for (int move : moves)\
    \ {\n            if (move > heap) continue;\n            const int value = grundy[heap\
    \ - move];\n            if (value < int(seen.size())) seen[value] = heap;\n  \
    \      }\n        while (\n            grundy[heap] < int(seen.size())\n     \
    \       && seen[grundy[heap]] == heap\n        ) {\n            grundy[heap]++;\n\
    \        }\n    }\n    return grundy;\n}\n\ninline int subtraction_game_nim_sum(\n\
    \    const std::vector<int>& heaps,\n    const std::vector<int>& moves\n) {\n\
    \    int max_heap = 0;\n    for (int heap : heaps) {\n        assert(heap >= 0);\n\
    \        max_heap = std::max(max_heap, heap);\n    }\n    const std::vector<int>\
    \ grundy = subtraction_game_grundy(max_heap, moves);\n    int result = 0;\n  \
    \  for (int heap : heaps) result ^= grundy[heap];\n    return result;\n}\n\ninline\
    \ bool subtraction_game_first_player_wins(\n    const std::vector<int>& heaps,\n\
    \    const std::vector<int>& moves\n) {\n    return subtraction_game_nim_sum(heaps,\
    \ moves) != 0;\n}\n\n}  // namespace game\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_GAME_SUBTRACTION_GAME_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: game/subtraction_game.hpp
  requiredBy:
  - game/all.hpp
  timestamp: '2026-08-24 02:07:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/game_algorithms.test.cpp
  - verify/game/classic_games.test.cpp
documentation_of: game/subtraction_game.hpp
layout: document
title: Subtraction Game
---

## Overview

Solves impartial subtraction games. From one heap, a move removes any positive
amount in a fixed move set without making the heap negative. Multiple heaps are
played as a disjoint sum, so their Grundy numbers combine with xor.

The implementation builds all Grundy numbers from heap size zero through a
requested maximum. It is useful when many heaps share the same move set or when
the full Grundy sequence is needed for later queries.

## Functions

All functions are in namespace `m1une::game`.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `std::vector<int> subtraction_game_grundy(int max_heap, const std::vector<int>& moves)` | Returns Grundy numbers for heap sizes in `[0, max_heap]`. | `O(max_heap * moves.size())` time, `O(max_heap + moves.size())` space |
| `int subtraction_game_nim_sum(const std::vector<int>& heaps, const std::vector<int>& moves)` | Returns the xor of the heaps' Grundy numbers. | `O(max(heaps) * moves.size() + heaps.size())` time |
| `bool subtraction_game_first_player_wins(const std::vector<int>& heaps, const std::vector<int>& moves)` | Whether the first player wins the disjoint sum under normal play. | `O(max(heaps) * moves.size() + heaps.size())` time |

`max_heap` and every heap size must be nonnegative. Every move must be positive.
These conditions are asserted in debug builds. Duplicate moves are allowed.

## Example

```cpp
#include "game/subtraction_game.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> moves = {1, 3, 4};
    auto grundy = m1une::game::subtraction_game_grundy(10, moves);
    std::cout << grundy[10] << '\n';

    std::vector<int> heaps = {7, 10};
    std::cout << m1une::game::subtraction_game_first_player_wins(heaps, moves)
              << '\n';
}
```
