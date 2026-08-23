---
title: DAG Minimax
documentation_of: ../../game/minimax.hpp
---

## Overview

Evaluates a finite scoring game represented by a directed acyclic graph. Each
nonterminal state is controlled by either a maximizing or minimizing player.
Terminal states carry values, and backward induction determines both the value
and one optimal move for every state.

This representation supports transpositions directly: several states may lead
to the same successor, which is evaluated only once.

## Types

`MinimaxResult<T>` stores:

| Member | Description |
| --- | --- |
| `std::vector<T> value` | Minimax value of every state. |
| `std::vector<int> move` | Chosen zero-based successor, or `-1` at a terminal state. |

## Functions

All APIs are in namespace `m1une::game`. Values must be copyable and comparable
with `<`.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `template<class T>`<br>`MinimaxResult<T> dag_minimax(const std::vector<std::vector<int>>& graph, const std::vector<T>& terminal_value, const std::vector<bool>& maximize)` | Evaluates every state and recovers one optimal move. | `O(V + E)` time, `O(V)` extra space |

All three arrays must have size `V`. `terminal_value[v]` is used only when
`graph[v]` is empty. At a nonterminal state, `maximize[v]` selects maximum or
minimum play. On equal values, the first optimal successor listed in `graph[v]`
is returned. Endpoints must lie in `[0, V)`, and the graph must be acyclic;
these conditions are asserted in debug builds.

## Example

```cpp
#include "game/minimax.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> graph(5);
    graph[0] = {1, 2};
    graph[1] = {3, 4};
    graph[2] = {3, 4};
    std::vector<int> terminal_value = {0, 0, 0, -4, 7};
    std::vector<bool> maximize = {true, false, false, false, false};

    auto result = m1une::game::dag_minimax(
        graph,
        terminal_value,
        maximize
    );
    std::cout << result.value[0] << '\n';
    std::cout << result.move[0] << '\n';
}
```
