---
title: Nim
documentation_of: ../../game/nim.hpp
---

## Overview

Helpers for ordinary Nim and misere Nim. A position is given as a range of
nonnegative heap sizes. An empty or all-zero position is losing in ordinary Nim
and winning under the misere convention, where the player with no move wins.

In ordinary Nim, the first player wins exactly when the xor of all heap sizes is
nonzero. In misere Nim, the same rule applies while some heap has size at least
two; if every nonempty heap has size one, the first player wins exactly when
their count is even.

## Functions

All functions are in namespace `m1une::game`. Heap values must support default
construction, `^=`, comparison with zero, and, for misere Nim, comparison with
one.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `template<class Iterator>`<br>`auto nim_sum(Iterator first, Iterator last)` | Returns the xor of the heap sizes in `[first, last)`. | `O(N)` time, `O(1)` space |
| `template<class Range>`<br>`auto nim_sum(const Range& heaps)` | Range overload of `nim_sum`. | `O(N)` time, `O(1)` space |
| `template<class Range>`<br>`bool nim_first_player_wins(const Range& heaps)` | Whether the first player wins ordinary Nim under normal play. | `O(N)` time, `O(1)` space |
| `template<class Range>`<br>`bool misere_nim_first_player_wins(const Range& heaps)` | Whether the first player wins Nim when taking the last object loses. | `O(N)` time, `O(1)` space |

## Example

```cpp
#include "game/nim.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> heaps = {1, 4, 5};
    std::cout << m1une::game::nim_sum(heaps) << '\n';
    std::cout << m1une::game::nim_first_player_wins(heaps) << '\n';

    std::vector<int> misere_heaps = {1, 1};
    std::cout << m1une::game::misere_nim_first_player_wins(misere_heaps) << '\n';
}
```
