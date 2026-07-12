---
title: Range-Parallel DSU
documentation_of: ../../../ds/dsu/range_parallel_dsu.hpp
---

## Overview

`RangeParallelDsu` maintains connectivity among vertices `0, 1, ..., n - 1`
and efficiently performs a parallel range merge:

```text
merge(first, second, length)
```

adds the equivalences

```text
first + offset == second + offset
```

for every `0 <= offset < length`. Calling an ordinary DSU merge for every
offset can take linear time per query; this structure shares completed work
between queries.

Internally, one DSU is maintained for every relevant power-of-two block size.
Two blocks are equivalent when all corresponding vertices in those blocks have
already been merged. A general range is represented by two overlapping
power-of-two blocks, and a newly merged block recursively activates its two
halves. Each auxiliary state can be activated only once.

`RangeParallelUnionFind` is an alias for `RangeParallelDsu`.

## Merge Callback

The callback overloads invoke

```cpp
callback(new_leader, absorbed_leader);
```

once for every actual merge in the underlying vertex DSU. At that point:

* `new_leader` is the leader of the combined component;
* `absorbed_leader` was the other component's leader immediately before the
  merge;
* `leader(absorbed_leader) == new_leader` already holds.

This makes it possible to maintain component sums or other external aggregate
state. The callback is not invoked for pairs that were already connected.

Store each aggregate at its component leader. Merge the two leader entries in
the callback, and look up the current leader whenever the aggregate is queried:

```cpp
std::vector<long long> sum = initial_values;

auto combine = [&](int new_leader, int absorbed_leader) {
    sum[new_leader] += sum[absorbed_leader];
};

dsu.merge(first, second, length, combine);
long long aggregate = sum[dsu.leader(vertex)];
```

After a merge, the entry at `absorbed_leader` is stale and must not be queried
directly. It does not need to be cleared because that vertex cannot become a
leader again. The callback can run multiple times during one range merge—once
for each pair of previously distinct vertex components that becomes connected.

Every merge function returns the number of callback-producing vertex merges.
The overloads without a callback perform the same connectivity changes and
return the same count.

## Interface

```cpp
class RangeParallelDsu {
public:
    RangeParallelDsu();
    explicit RangeParallelDsu(int size);

    int size() const;
    bool empty() const;
    int component_count() const;

    int leader(int vertex);
    int leader(int vertex) const;
    bool same(int first, int second);
    bool same(int first, int second) const;
    int group_size(int vertex);
    int group_size(int vertex) const;

    template <class Callback>
    int merge(int first, int second, int length, Callback&& callback);
    int merge(int first, int second, int length);

    template <class Callback>
    int merge_ranges(
        int first_left,
        int first_right,
        int second_left,
        int second_right,
        Callback&& callback
    );
    int merge_ranges(
        int first_left,
        int first_right,
        int second_left,
        int second_right
    );

    template <class Callback>
    int merge(int first, int second, Callback&& callback);
    int merge(int first, int second);
};
```

The three-argument `merge(first, second, length)` merges the half-open ranges
`[first, first + length)` and `[second, second + length)`. `merge_ranges`
accepts both half-open ranges explicitly and requires equal lengths. The
two-argument `merge(first, second)` is an ordinary single-pair merge.

## Complexity

Let $N$ be the number of vertices. Let $A$ be the number of previously unseen
auxiliary power-of-two block equivalences activated by one range merge.

| Method | Complexity |
| --- | --- |
| Construction | $O(N\log N)$ time and memory |
| `merge(first, second, length, callback)` | $O((A+1)\alpha(N))$ time |
| `merge_ranges(...)` | Same as the corresponding `merge` |
| Single-pair `merge(first, second)` | Amortized $O(\alpha(N))$ |
| `leader`, `same`, `group_size` | Amortized $O(\alpha(N))$ |
| `size`, `empty`, `component_count` | $O(1)$ |

Across the entire lifetime of the structure, the sum of $A$ is
$O(N\log N)$. Therefore, $Q$ range merges take
$O((N\log N + Q)\alpha(N))$ time in total, in addition to callback work.
There are at most $N-1$ callback invocations over the lifetime of the object.

## Preconditions

* Indices are zero-based.
* Both merged ranges must lie inside `[0, size())`.
* `length` may be zero; such a merge does nothing and returns zero.
* The two ranges may overlap or be identical.
* `merge_ranges` requires equal range lengths.
* Query methods do not allocate memory after construction.

## Example

```cpp
#include "ds/dsu/range_parallel_dsu.hpp"

#include <iostream>
#include <vector>

int main() {
    m1une::ds::RangeParallelDsu dsu(8);
    std::vector<int> sum = {1, 2, 3, 4, 5, 6, 7, 8};

    auto combine = [&](int new_leader, int absorbed_leader) {
        sum[new_leader] += sum[absorbed_leader];
    };
    auto component_sum = [&](int vertex) {
        return sum[dsu.leader(vertex)];
    };

    dsu.merge(0, 4, 4, combine);
    std::cout << dsu.same(2, 6) << '\n';  // 1
    std::cout << dsu.group_size(2) << '\n';  // 2
    std::cout << component_sum(2) << '\n';  // 3 + 7 = 10

    dsu.merge_ranges(0, 2, 2, 4, combine);
    std::cout << dsu.group_size(0) << '\n';  // 4
    std::cout << component_sum(4) << '\n';  // 1 + 3 + 5 + 7 = 16
}
```
