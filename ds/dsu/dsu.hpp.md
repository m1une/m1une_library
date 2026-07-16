---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/all.hpp
    title: Geometry Bundle
  - icon: ':heavy_check_mark:'
    path: geometry/euclidean_mst.hpp
    title: Euclidean Minimum Spanning Tree
  - icon: ':heavy_check_mark:'
    path: geometry/manhattan_mst.hpp
    title: Manhattan Minimum Spanning Tree
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/complement_connected_components.hpp
    title: Complement-Graph Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/connected_components.hpp
    title: Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/kruskal.hpp
    title: Kruskal
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/dsu.test.cpp
    title: verify/ds/dsu/dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/range_parallel_dsu.test.cpp
    title: verify/ds/dsu/range_parallel_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/euclidean_mst.test.cpp
    title: verify/geometry/euclidean_mst.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/euclidean_mst.test.cpp
    title: verify/geometry/euclidean_mst.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/geometry_algorithms.test.cpp
    title: verify/geometry/geometry_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/manhattan_mst.test.cpp
    title: verify/geometry/manhattan_mst.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/manhattan_mst.test.cpp
    title: verify/geometry/manhattan_mst.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/complement_connected_components.test.cpp
    title: verify/graph/complement_connected_components.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/incremental_scc.test.cpp
    title: verify/graph/incremental_scc.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/minimum_spanning_tree.test.cpp
    title: verify/graph/minimum_spanning_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#include <algorithm>\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    struct Dsu {\n   private:\n    int _n;\n    // parent_or_size[i] is the parent\
    \ of i if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i]\
    \ is the size of the group.\n    std::vector<int> parent_or_size;\n\n    // Returns\
    \ {new leader, absorbed leader}. The absorbed leader is -1 when\n    // both vertices\
    \ already belong to the same component.\n    std::pair<int, int> merge_leaders(int\
    \ a, int b) {\n        int x = leader(a), y = leader(b);\n        if (x == y)\
    \ return {x, -1};\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return {x, y};\n    }\n\n   public:\n    Dsu() : _n(0) {}\n  \
    \  explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\n    // Merges the\
    \ group containing 'a' with the group containing 'b'.\n    // Returns the leader\
    \ of the merged group.\n    int merge(int a, int b) {\n        return merge_leaders(a,\
    \ b).first;\n    }\n\n    // Invokes callback(new_leader, absorbed_leader) after\
    \ an actual merge.\n    // Returns the leader of the merged group.\n    template\
    \ <class Callback>\n    int merge(int a, int b, Callback&& callback) {\n     \
    \   std::pair<int, int> merged = merge_leaders(a, b);\n        if (merged.second\
    \ != -1) callback(merged.first, merged.second);\n        return merged.first;\n\
    \    }\n\n    // Returns true if 'a' and 'b' belong to the same group.\n    bool\
    \ same(int a, int b) {\n        return leader(a) == leader(b);\n    }\n\n    //\
    \ Returns the leader (representative) of the group containing 'a'.\n    int leader(int\
    \ a) {\n        if (parent_or_size[a] < 0) return a;\n        // Path compression\n\
    \        return parent_or_size[a] = leader(parent_or_size[a]);\n    }\n\n    //\
    \ Returns the size of the group containing 'a'.\n    int size(int a) {\n     \
    \   return -parent_or_size[leader(a)];\n    }\n\n    // Returns a list of all\
    \ groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DSU_HPP\n#define M1UNE_DSU_HPP 1\n\n#include <algorithm>\n\
    #include <numeric>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace ds {\n\nstruct Dsu {\n   private:\n    int _n;\n    // parent_or_size[i]\
    \ is the parent of i if it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i]\
    \ is the size of the group.\n    std::vector<int> parent_or_size;\n\n    // Returns\
    \ {new leader, absorbed leader}. The absorbed leader is -1 when\n    // both vertices\
    \ already belong to the same component.\n    std::pair<int, int> merge_leaders(int\
    \ a, int b) {\n        int x = leader(a), y = leader(b);\n        if (x == y)\
    \ return {x, -1};\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return {x, y};\n    }\n\n   public:\n    Dsu() : _n(0) {}\n  \
    \  explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\n    // Merges the\
    \ group containing 'a' with the group containing 'b'.\n    // Returns the leader\
    \ of the merged group.\n    int merge(int a, int b) {\n        return merge_leaders(a,\
    \ b).first;\n    }\n\n    // Invokes callback(new_leader, absorbed_leader) after\
    \ an actual merge.\n    // Returns the leader of the merged group.\n    template\
    \ <class Callback>\n    int merge(int a, int b, Callback&& callback) {\n     \
    \   std::pair<int, int> merged = merge_leaders(a, b);\n        if (merged.second\
    \ != -1) callback(merged.first, merged.second);\n        return merged.first;\n\
    \    }\n\n    // Returns true if 'a' and 'b' belong to the same group.\n    bool\
    \ same(int a, int b) {\n        return leader(a) == leader(b);\n    }\n\n    //\
    \ Returns the leader (representative) of the group containing 'a'.\n    int leader(int\
    \ a) {\n        if (parent_or_size[a] < 0) return a;\n        // Path compression\n\
    \        return parent_or_size[a] = leader(parent_or_size[a]);\n    }\n\n    //\
    \ Returns the size of the group containing 'a'.\n    int size(int a) {\n     \
    \   return -parent_or_size[leader(a)];\n    }\n\n    // Returns a list of all\
    \ groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n#endif  // M1UNE_DSU_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/dsu/dsu.hpp
  requiredBy:
  - graph/all.hpp
  - graph/kruskal.hpp
  - graph/connected_components.hpp
  - graph/undirected.hpp
  - graph/complement_connected_components.hpp
  - geometry/euclidean_mst.hpp
  - geometry/all.hpp
  - geometry/manhattan_mst.hpp
  timestamp: '2026-07-13 06:09:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dsu/dsu.test.cpp
  - verify/ds/dsu/range_parallel_dsu.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/minimum_spanning_tree.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/complement_connected_components.test.cpp
  - verify/graph/incremental_scc.test.cpp
  - verify/geometry/geometry_algorithms.test.cpp
  - verify/geometry/euclidean_mst.test.cpp
  - verify/geometry/euclidean_mst.test.cpp
  - verify/geometry/manhattan_mst.test.cpp
  - verify/geometry/manhattan_mst.test.cpp
documentation_of: ds/dsu/dsu.hpp
layout: document
title: DSU (Disjoint Set Union)
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
