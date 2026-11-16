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
  bundledCode: "#line 1 \"game/silver_dollar_game.hpp\"\n\n\n\n#include <cassert>\n\
    #include <type_traits>\n#include <vector>\n\nnamespace m1une {\nnamespace game\
    \ {\n\ntemplate <typename T>\nT silver_dollar_grundy(const std::vector<T>& coins)\
    \ {\n    for (int index = 0; index < int(coins.size()); ++index) {\n        if\
    \ constexpr (std::is_signed_v<T>) assert(coins[index] >= 0);\n        if (index\
    \ != 0) assert(coins[index - 1] < coins[index]);\n    }\n\n    T result{};\n \
    \   int index = int(coins.size()) % 2;\n    if (index == 1) result ^= coins[0];\n\
    \    for (; index + 1 < int(coins.size()); index += 2) {\n        result ^= coins[index\
    \ + 1] - coins[index] - 1;\n    }\n    return result;\n}\n\ntemplate <typename\
    \ T>\nbool silver_dollar_first_player_wins(const std::vector<T>& coins) {\n  \
    \  return silver_dollar_grundy(coins) != 0;\n}\n\n}  // namespace game\n}  //\
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GAME_SILVER_DOLLAR_GAME_HPP\n#define M1UNE_GAME_SILVER_DOLLAR_GAME_HPP\
    \ 1\n\n#include <cassert>\n#include <type_traits>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace game {\n\ntemplate <typename T>\nT silver_dollar_grundy(const\
    \ std::vector<T>& coins) {\n    for (int index = 0; index < int(coins.size());\
    \ ++index) {\n        if constexpr (std::is_signed_v<T>) assert(coins[index] >=\
    \ 0);\n        if (index != 0) assert(coins[index - 1] < coins[index]);\n    }\n\
    \n    T result{};\n    int index = int(coins.size()) % 2;\n    if (index == 1)\
    \ result ^= coins[0];\n    for (; index + 1 < int(coins.size()); index += 2) {\n\
    \        result ^= coins[index + 1] - coins[index] - 1;\n    }\n    return result;\n\
    }\n\ntemplate <typename T>\nbool silver_dollar_first_player_wins(const std::vector<T>&\
    \ coins) {\n    return silver_dollar_grundy(coins) != 0;\n}\n\n}  // namespace\
    \ game\n}  // namespace m1une\n\n#endif  // M1UNE_GAME_SILVER_DOLLAR_GAME_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: game/silver_dollar_game.hpp
  requiredBy:
  - game/all.hpp
  timestamp: '2026-08-24 02:07:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/game_algorithms.test.cpp
  - verify/game/classic_games.test.cpp
documentation_of: game/silver_dollar_game.hpp
layout: document
title: Silver Dollar Game
---

## Overview

Solves the Silver Dollar Game on the nonnegative integer strip. Coins occupy
distinct cells. A move slides one coin left by a positive distance without
jumping over or landing on another coin.

Pairing coins from the right reduces the position to independent Nim heaps. For
an odd number of coins, the unpaired leftmost coin contributes its distance
from cell zero. Each remaining pair contributes the number of empty cells
between its coins.

## Functions

All functions are in namespace `m1une::game`. Template parameter `T` must be a
nonnegative integer-like type supporting comparison, subtraction, and xor.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `template<class T>`<br>`T silver_dollar_grundy(const std::vector<T>& coins)` | Returns the position's Grundy number. | `O(N)` time, `O(1)` extra space |
| `template<class T>`<br>`bool silver_dollar_first_player_wins(const std::vector<T>& coins)` | Whether the first player wins under normal play. | `O(N)` time, `O(1)` extra space |

`coins` must be strictly increasing and nonnegative. This is asserted in debug
builds. The empty position has Grundy number zero.

## Example

```cpp
#include "game/silver_dollar_game.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> coins = {1, 3, 7};
    std::cout << m1une::game::silver_dollar_grundy(coins) << '\n';
    std::cout << m1une::game::silver_dollar_first_player_wins(coins) << '\n';
}
```
