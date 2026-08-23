---
title: Subtraction Game
documentation_of: ../../game/subtraction_game.hpp
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
