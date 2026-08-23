---
title: Green Hackenbush
documentation_of: ../../game/green_hackenbush.hpp
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
