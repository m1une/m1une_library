---
title: DSU (Disjoint Set Union)
documentation_of: ../../../ds/dsu/dsu.hpp
---

## Overview

A Disjoint Set Union (also known as Union-Find) data structure. It manages a set of elements partitioned into a number of disjoint (non-overlapping) subsets. It provides near constant time operations to merge sets and find the representative of a set.

It is implemented using **Path Compression** and **Union by Size**, achieving an amortized time complexity of $O(\alpha(N))$ per operation, where $\alpha$ is the inverse Ackermann function.

## Complexity Notation

* `N` is the number of elements.

## Interface

```cpp
struct Dsu {
    Dsu();
    explicit Dsu(int n);

    int merge(int a, int b);

    template <class Callback>
    int merge(int a, int b, Callback&& callback);

    bool same(int a, int b);
    int leader(int a);
    int size(int a);
    std::vector<std::vector<int>> groups();
};
```

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `Dsu()` | Creates an empty DSU. | $O(1)$ |
| `explicit Dsu(int n)` | Creates `n` singleton sets. | $O(N)$ |
| `int merge(int a, int b)` | Merges the sets containing `a` and `b`; returns the leader of the merged set. | Amortized $O(\alpha(N))$ |
| `int merge(int a, int b, Callback&& callback)` | Merges two sets, invokes the callback after an actual merge, and returns the new leader. | Amortized $O(\alpha(N))$ plus callback work |
| `bool same(int a, int b)` | Returns whether `a` and `b` are in the same set. | Amortized $O(\alpha(N))$ |
| `int leader(int a)` | Returns the representative of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `int size(int a)` | Returns the size of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `std::vector<std::vector<int>> groups()` | Returns all sets as vectors of element indices. | $O(N \alpha(N))$ |

## Merge Callback

The callback overload invokes

```cpp
callback(new_leader, absorbed_leader);
```

after two previously distinct components have been merged. At callback time,
`new_leader` is already the combined component's leader and
`leader(absorbed_leader) == new_leader`. If the vertices were already
connected, the callback is not invoked.

This is useful for external component aggregates. Store each aggregate at its
leader, merge the two entries in the callback, and query through the current
leader:

```cpp
std::vector<long long> sum = initial_values;

auto combine = [&](int new_leader, int absorbed_leader) {
    sum[new_leader] += sum[absorbed_leader];
};

dsu.merge(a, b, combine);
long long component_sum = sum[dsu.leader(vertex)];
```

The entry at `absorbed_leader` becomes stale and does not need to be cleared,
because that vertex cannot become a leader again.

## Example

```cpp
#include "ds/dsu/dsu.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::ds::Dsu dsu(5);
    std::vector<int> sum = {1, 2, 3, 4, 5};

    auto combine = [&](int new_leader, int absorbed_leader) {
        sum[new_leader] += sum[absorbed_leader];
    };

    dsu.merge(0, 1, combine);
    dsu.merge(2, 3, combine);
    dsu.merge(1, 2, combine);

    std::cout << dsu.same(0, 3) << '\n';  // 1
    std::cout << dsu.size(0) << '\n';  // 4
    std::cout << sum[dsu.leader(3)] << '\n';  // 1 + 2 + 3 + 4 = 10
}
```
