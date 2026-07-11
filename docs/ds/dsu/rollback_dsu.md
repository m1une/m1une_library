---
title: Rollback DSU
documentation_of: ../../../ds/dsu/rollback_dsu.hpp
---

## Overview

`RollbackDsu` maintains a partition under merges and can restore any earlier
snapshot on the current history path. It is useful for divide-and-conquer over
time, segment trees over query intervals, version trees, and offline dynamic
connectivity.

Union by size keeps each parent chain logarithmic. Path compression is
intentionally omitted because it would mutate an unbounded number of entries
that then need to be logged.

Every `merge` call appends exactly one history entry. A redundant merge appends
a no-op entry and returns `false`, so one call to `undo()` always reverses one
call to `merge()`.

## API

```cpp
struct RollbackDsu {
    RollbackDsu();
    explicit RollbackDsu(int n);

    int size() const;
    bool empty() const;
    int component_count() const;
    int history_size() const;
    void reserve_history(int count);

    int leader(int vertex) const;
    bool same(int first, int second) const;
    int group_size(int vertex) const;
    int size(int vertex) const;
    bool merge(int first, int second);

    bool undo();
    int snapshot() const;
    void rollback(int state);
    std::vector<std::vector<int>> groups() const;
};
```

| Method | Description | Complexity |
| --- | --- | --- |
| `RollbackDsu()` | Creates an empty DSU. | $O(1)$ |
| `RollbackDsu(n)` | Creates `n` singleton sets. | $O(N)$ |
| `size()` | Returns the number of elements. | $O(1)$ |
| `empty()` | Returns whether there are no elements. | $O(1)$ |
| `component_count()` | Returns the current number of sets. | $O(1)$ |
| `history_size()` | Returns the number of recorded merge calls. | $O(1)$ |
| `reserve_history(count)` | Reserves history capacity. | $O(H)$ if reallocation occurs |
| `leader(v)` | Returns the representative containing `v`. | $O(\log N)$ |
| `same(u, v)` | Returns whether `u` and `v` are connected. | $O(\log N)$ |
| `group_size(v)`, `size(v)` | Returns the size of the set containing `v`. | $O(\log N)$ |
| `merge(u, v)` | Records one operation and merges the sets if distinct; returns whether the partition changed. | $O(\log N)$ amortized for history growth |
| `undo()` | Reverses the most recent merge call; returns `false` when history is empty. | $O(1)$ |
| `snapshot()` | Returns the current history position. | $O(1)$ |
| `rollback(state)` | Restores a previously returned snapshot on the current history path. | $O(H - state)$ |
| `groups()` | Materializes every current set. | $O(N \log N)$ |

Indices must lie in `[0, size())`. A rollback state must lie between `0` and
the current `history_size()`. Rolling forward to a discarded state is not
supported. Query methods are `const` and never change the represented state.

The DSU stores $O(N + H)$ integers, where `H` is the current history length.

## Example

```cpp
#include "ds/dsu/rollback_dsu.hpp"

#include <iostream>

int main() {
    m1une::ds::RollbackDsu dsu(4);
    dsu.merge(0, 1);
    int checkpoint = dsu.snapshot();

    dsu.merge(1, 2);
    std::cout << dsu.same(0, 2) << "\n";  // 1

    dsu.rollback(checkpoint);
    std::cout << dsu.same(0, 2) << "\n";  // 0
    std::cout << dsu.component_count() << "\n";  // 3
}
```
