---
title: Silver Dollar Game
documentation_of: ../../game/silver_dollar_game.hpp
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
