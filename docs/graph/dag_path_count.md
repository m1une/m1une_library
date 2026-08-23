---
title: DAG Path Count
documentation_of: ../../graph/dag_path_count.hpp
---

## Overview

`dag_path_count` counts directed paths from one or more sources to every vertex
of a DAG. It is useful for dependency counting and standard DAG dynamic
programming.

Each source contributes one zero-edge path to itself. Parallel active edges
describe distinct paths, inactive edges are ignored, and duplicate source
indices are counted once. A cyclic graph returns `std::nullopt`.

`Count` defaults to `long long`. It only needs construction from `0` and `1`
and addition, so a modular integer type can be supplied when counts are large.
Overflow follows the behavior of `Count`.

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `dag_path_count` | `template <class Count = long long, class T> std::optional<std::vector<Count>> dag_path_count(const Graph<T>& g, int s)` | Counts paths beginning at `s`. | $O(N + M)$ time and $O(N)$ memory |
| `dag_path_count` | `template <class Count = long long, class T> std::optional<std::vector<Count>> dag_path_count(const Graph<T>& g, const std::vector<int>& sources)` | Counts paths beginning at any source. | $O(N + M)$ time and $O(N)$ memory |

## Example

```cpp
#include "graph/dag_path_count.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(0, 2);
    g.add_directed_edge(1, 3);
    g.add_directed_edge(2, 3);

    auto ways = m1une::graph::dag_path_count(g, 0);
    if (ways) std::cout << (*ways)[3] << '\n';  // 2
}
```
