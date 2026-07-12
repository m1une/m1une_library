---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/range_parallel_dsu.test.cpp
    title: verify/ds/dsu/range_parallel_dsu.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/range_parallel_dsu.hpp\"\n\n\n\n#include <bit>\n\
    #include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Merges corresponding vertices of two\
    \ equal-length ranges.\nclass RangeParallelDsu {\n   private:\n    struct LevelDsu\
    \ {\n        std::vector<int> parent_or_size;\n        int component_count;\n\n\
    \        explicit LevelDsu(int size = 0)\n            : parent_or_size(std::size_t(size),\
    \ -1), component_count(size) {}\n\n        int leader(int vertex) {\n        \
    \    if (parent_or_size[vertex] < 0) return vertex;\n            return parent_or_size[vertex]\
    \ = leader(parent_or_size[vertex]);\n        }\n\n        int leader(int vertex)\
    \ const {\n            while (parent_or_size[vertex] >= 0) {\n               \
    \ vertex = parent_or_size[vertex];\n            }\n            return vertex;\n\
    \        }\n\n        std::pair<int, int> merge(int first, int second) {\n   \
    \         first = leader(first);\n            second = leader(second);\n     \
    \       if (first == second) return {first, -1};\n            if (-parent_or_size[first]\
    \ < -parent_or_size[second]) {\n                std::swap(first, second);\n  \
    \          }\n            parent_or_size[first] += parent_or_size[second];\n \
    \           parent_or_size[second] = first;\n            component_count--;\n\
    \            return {first, second};\n        }\n    };\n\n    int _size;\n  \
    \  std::vector<LevelDsu> _levels;\n\n    static int check_size(int size) {\n \
    \       assert(size >= 0);\n        return size;\n    }\n\n    void check_vertex(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < _size);\n    }\n\n \
    \   void check_range(int first, int length) const {\n        assert(0 <= first\
    \ && 0 <= length);\n        assert(length <= _size);\n        assert(first <=\
    \ _size - length);\n    }\n\n    template <class Callback>\n    int merge_block(int\
    \ level, int first, int second, Callback& callback) {\n        std::pair<int,\
    \ int> merged = _levels[level].merge(first, second);\n        if (merged.second\
    \ == -1) return 0;\n        if (level == 0) {\n            callback(merged.first,\
    \ merged.second);\n            return 1;\n        }\n\n        const int half\
    \ = 1 << (level - 1);\n        int result = merge_block(level - 1, first, second,\
    \ callback);\n        result += merge_block(level - 1, first + half, second +\
    \ half, callback);\n        return result;\n    }\n\n   public:\n    RangeParallelDsu()\
    \ : RangeParallelDsu(0) {}\n\n    explicit RangeParallelDsu(int size) : _size(check_size(size))\
    \ {\n        _levels.emplace_back(_size);\n        for (int block_size = 2; block_size\
    \ < _size; block_size *= 2) {\n            _levels.emplace_back(_size - block_size\
    \ + 1);\n            if (block_size > _size / 2) break;\n        }\n    }\n\n\
    \    int size() const {\n        return _size;\n    }\n\n    bool empty() const\
    \ {\n        return _size == 0;\n    }\n\n    int component_count() const {\n\
    \        return _levels[0].component_count;\n    }\n\n    int leader(int vertex)\
    \ {\n        check_vertex(vertex);\n        return _levels[0].leader(vertex);\n\
    \    }\n\n    int leader(int vertex) const {\n        check_vertex(vertex);\n\
    \        return _levels[0].leader(vertex);\n    }\n\n    bool same(int first,\
    \ int second) {\n        return leader(first) == leader(second);\n    }\n\n  \
    \  bool same(int first, int second) const {\n        return leader(first) == leader(second);\n\
    \    }\n\n    int group_size(int vertex) {\n        return -_levels[0].parent_or_size[leader(vertex)];\n\
    \    }\n\n    int group_size(int vertex) const {\n        return -_levels[0].parent_or_size[leader(vertex)];\n\
    \    }\n\n    template <class Callback>\n    int merge(int first, int second,\
    \ int length, Callback&& callback) {\n        check_range(first, length);\n  \
    \      check_range(second, length);\n        if (length == 0) return 0;\n    \
    \    if (length == 1) {\n            return merge_block(0, first, second, callback);\n\
    \        }\n\n        const int level = int(std::bit_width(unsigned(length - 1)))\
    \ - 1;\n        const int block_size = 1 << level;\n        int result = merge_block(level,\
    \ first, second, callback);\n        result += merge_block(level, first + length\
    \ - block_size,\n                              second + length - block_size, callback);\n\
    \        return result;\n    }\n\n    int merge(int first, int second, int length)\
    \ {\n        auto ignore = [](int, int) {};\n        return merge(first, second,\
    \ length, ignore);\n    }\n\n    template <class Callback>\n    int merge_ranges(int\
    \ first_left, int first_right, int second_left,\n                     int second_right,\
    \ Callback&& callback) {\n        assert(first_right - first_left == second_right\
    \ - second_left);\n        return merge(first_left, second_left, first_right -\
    \ first_left,\n                     std::forward<Callback>(callback));\n    }\n\
    \n    int merge_ranges(int first_left, int first_right, int second_left,\n   \
    \                  int second_right) {\n        auto ignore = [](int, int) {};\n\
    \        return merge_ranges(first_left, first_right, second_left, second_right,\n\
    \                            ignore);\n    }\n\n    template <class Callback>\n\
    \    int merge(int first, int second, Callback&& callback) {\n        check_vertex(first);\n\
    \        check_vertex(second);\n        return merge_block(0, first, second, callback);\n\
    \    }\n\n    int merge(int first, int second) {\n        auto ignore = [](int,\
    \ int) {};\n        return merge(first, second, ignore);\n    }\n};\n\nusing RangeParallelUnionFind\
    \ = RangeParallelDsu;\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_DSU_RANGE_PARALLEL_DSU_HPP\n#define M1UNE_DS_DSU_RANGE_PARALLEL_DSU_HPP\
    \ 1\n\n#include <bit>\n#include <cassert>\n#include <cstddef>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Merges corresponding\
    \ vertices of two equal-length ranges.\nclass RangeParallelDsu {\n   private:\n\
    \    struct LevelDsu {\n        std::vector<int> parent_or_size;\n        int\
    \ component_count;\n\n        explicit LevelDsu(int size = 0)\n            : parent_or_size(std::size_t(size),\
    \ -1), component_count(size) {}\n\n        int leader(int vertex) {\n        \
    \    if (parent_or_size[vertex] < 0) return vertex;\n            return parent_or_size[vertex]\
    \ = leader(parent_or_size[vertex]);\n        }\n\n        int leader(int vertex)\
    \ const {\n            while (parent_or_size[vertex] >= 0) {\n               \
    \ vertex = parent_or_size[vertex];\n            }\n            return vertex;\n\
    \        }\n\n        std::pair<int, int> merge(int first, int second) {\n   \
    \         first = leader(first);\n            second = leader(second);\n     \
    \       if (first == second) return {first, -1};\n            if (-parent_or_size[first]\
    \ < -parent_or_size[second]) {\n                std::swap(first, second);\n  \
    \          }\n            parent_or_size[first] += parent_or_size[second];\n \
    \           parent_or_size[second] = first;\n            component_count--;\n\
    \            return {first, second};\n        }\n    };\n\n    int _size;\n  \
    \  std::vector<LevelDsu> _levels;\n\n    static int check_size(int size) {\n \
    \       assert(size >= 0);\n        return size;\n    }\n\n    void check_vertex(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < _size);\n    }\n\n \
    \   void check_range(int first, int length) const {\n        assert(0 <= first\
    \ && 0 <= length);\n        assert(length <= _size);\n        assert(first <=\
    \ _size - length);\n    }\n\n    template <class Callback>\n    int merge_block(int\
    \ level, int first, int second, Callback& callback) {\n        std::pair<int,\
    \ int> merged = _levels[level].merge(first, second);\n        if (merged.second\
    \ == -1) return 0;\n        if (level == 0) {\n            callback(merged.first,\
    \ merged.second);\n            return 1;\n        }\n\n        const int half\
    \ = 1 << (level - 1);\n        int result = merge_block(level - 1, first, second,\
    \ callback);\n        result += merge_block(level - 1, first + half, second +\
    \ half, callback);\n        return result;\n    }\n\n   public:\n    RangeParallelDsu()\
    \ : RangeParallelDsu(0) {}\n\n    explicit RangeParallelDsu(int size) : _size(check_size(size))\
    \ {\n        _levels.emplace_back(_size);\n        for (int block_size = 2; block_size\
    \ < _size; block_size *= 2) {\n            _levels.emplace_back(_size - block_size\
    \ + 1);\n            if (block_size > _size / 2) break;\n        }\n    }\n\n\
    \    int size() const {\n        return _size;\n    }\n\n    bool empty() const\
    \ {\n        return _size == 0;\n    }\n\n    int component_count() const {\n\
    \        return _levels[0].component_count;\n    }\n\n    int leader(int vertex)\
    \ {\n        check_vertex(vertex);\n        return _levels[0].leader(vertex);\n\
    \    }\n\n    int leader(int vertex) const {\n        check_vertex(vertex);\n\
    \        return _levels[0].leader(vertex);\n    }\n\n    bool same(int first,\
    \ int second) {\n        return leader(first) == leader(second);\n    }\n\n  \
    \  bool same(int first, int second) const {\n        return leader(first) == leader(second);\n\
    \    }\n\n    int group_size(int vertex) {\n        return -_levels[0].parent_or_size[leader(vertex)];\n\
    \    }\n\n    int group_size(int vertex) const {\n        return -_levels[0].parent_or_size[leader(vertex)];\n\
    \    }\n\n    template <class Callback>\n    int merge(int first, int second,\
    \ int length, Callback&& callback) {\n        check_range(first, length);\n  \
    \      check_range(second, length);\n        if (length == 0) return 0;\n    \
    \    if (length == 1) {\n            return merge_block(0, first, second, callback);\n\
    \        }\n\n        const int level = int(std::bit_width(unsigned(length - 1)))\
    \ - 1;\n        const int block_size = 1 << level;\n        int result = merge_block(level,\
    \ first, second, callback);\n        result += merge_block(level, first + length\
    \ - block_size,\n                              second + length - block_size, callback);\n\
    \        return result;\n    }\n\n    int merge(int first, int second, int length)\
    \ {\n        auto ignore = [](int, int) {};\n        return merge(first, second,\
    \ length, ignore);\n    }\n\n    template <class Callback>\n    int merge_ranges(int\
    \ first_left, int first_right, int second_left,\n                     int second_right,\
    \ Callback&& callback) {\n        assert(first_right - first_left == second_right\
    \ - second_left);\n        return merge(first_left, second_left, first_right -\
    \ first_left,\n                     std::forward<Callback>(callback));\n    }\n\
    \n    int merge_ranges(int first_left, int first_right, int second_left,\n   \
    \                  int second_right) {\n        auto ignore = [](int, int) {};\n\
    \        return merge_ranges(first_left, first_right, second_left, second_right,\n\
    \                            ignore);\n    }\n\n    template <class Callback>\n\
    \    int merge(int first, int second, Callback&& callback) {\n        check_vertex(first);\n\
    \        check_vertex(second);\n        return merge_block(0, first, second, callback);\n\
    \    }\n\n    int merge(int first, int second) {\n        auto ignore = [](int,\
    \ int) {};\n        return merge(first, second, ignore);\n    }\n};\n\nusing RangeParallelUnionFind\
    \ = RangeParallelDsu;\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif \
    \ // M1UNE_DS_DSU_RANGE_PARALLEL_DSU_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/dsu/range_parallel_dsu.hpp
  requiredBy: []
  timestamp: '2026-07-13 06:05:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dsu/range_parallel_dsu.test.cpp
documentation_of: ds/dsu/range_parallel_dsu.hpp
layout: document
title: Range-Parallel DSU
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
