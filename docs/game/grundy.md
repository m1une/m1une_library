---
title: Grundy Numbers
documentation_of: ../../game/grundy.hpp
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
