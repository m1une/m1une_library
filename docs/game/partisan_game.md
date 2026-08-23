---
title: Partisan Game Outcomes
documentation_of: ../../game/partisan_game.hpp
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
