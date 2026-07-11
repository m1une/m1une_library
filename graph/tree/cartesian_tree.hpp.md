---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/tree/all.hpp
    title: Tree All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/cartesian_tree.test.cpp
    title: verify/graph/tree/cartesian_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/tree_algorithms.test.cpp
    title: verify/graph/tree/tree_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/tree/cartesian_tree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <functional>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
    \ {\n    using cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n   \
    \ int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1),\
    \ alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool\
    \ alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_)\
    \ {}\n\n    int other(int v) const {\n        assert(v == from || v == to);\n\
    \        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>> _g;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n   public:\n\
    \    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
    \ _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int edge_count() const {\n        return _edge_count;\n    }\n\n    int add_vertex()\
    \ {\n        _g.emplace_back();\n        return _n++;\n    }\n\n    int add_directed_edge(int\
    \ from, int to, T cost = T(1)) {\n        assert(0 <= from && from < _n);\n  \
    \      assert(0 <= to && to < _n);\n        int id = _edge_count++;\n        int\
    \ idx = int(_g[from].size());\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({from,\
    \ idx});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost =\
    \ T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     _g[u].push_back(edge_type(u, v, cost, id));\n        int v_idx = int(_g[v].size());\n\
    \        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({u, u_idx});\n        _edge_positions.back().push_back({v,\
    \ v_idx});\n        return id;\n    }\n\n    void set_edge_alive(int id, bool\
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (auto [v,\
    \ idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n     \
    \   }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < _edge_count);\n        assert(!_edge_positions[id].empty());\n        auto\
    \ [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n    }\n\
    \n    const std::vector<edge_type>& operator[](int v) const {\n        assert(0\
    \ <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 12 \"graph/tree/cartesian_tree.hpp\"\n\nnamespace m1une {\n\
    namespace tree {\n\nstruct CartesianTree {\n    int root;\n    std::vector<int>\
    \ parent;\n    std::vector<int> left;\n    std::vector<int> right;\n\n   private:\n\
    \    int _n;\n\n    void check_vertex(int v) const {\n        assert(0 <= v &&\
    \ v < _n);\n    }\n\n   public:\n    CartesianTree() : root(-1), _n(0) {}\n\n\
    \    template <class T, class Compare = std::less<T>>\n    explicit CartesianTree(const\
    \ std::vector<T>& a, Compare comp = Compare()) : root(-1), _n(0) {\n        build(a,\
    \ comp);\n    }\n\n    template <class T, class Compare = std::less<T>>\n    void\
    \ build(const std::vector<T>& a, Compare comp = Compare()) {\n        assert(a.size()\
    \ <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n        _n =\
    \ int(a.size());\n        root = -1;\n        parent.assign(_n, -1);\n       \
    \ left.assign(_n, -1);\n        right.assign(_n, -1);\n\n        std::vector<int>\
    \ stack;\n        stack.reserve(_n);\n        for (int i = 0; i < _n; i++) {\n\
    \            int last = -1;\n            while (!stack.empty() && comp(a[i], a[stack.back()]))\
    \ {\n                last = stack.back();\n                stack.pop_back();\n\
    \            }\n            if (last != -1) {\n                left[i] = last;\n\
    \                parent[last] = i;\n            }\n            if (!stack.empty())\
    \ {\n                right[stack.back()] = i;\n                parent[i] = stack.back();\n\
    \            }\n            stack.push_back(i);\n        }\n\n        if (!stack.empty())\
    \ root = stack.front();\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    int\
    \ parent_or_self(int v) const {\n        check_vertex(v);\n        return parent[v]\
    \ == -1 ? v : parent[v];\n    }\n\n    std::vector<int> parent_with_root_self()\
    \ const {\n        std::vector<int> result = parent;\n        if (root != -1)\
    \ result[root] = root;\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> edges() const {\n        std::vector<std::pair<int, int>> result;\n  \
    \      if (_n == 0) return result;\n        result.reserve(_n - 1);\n        for\
    \ (int v = 0; v < _n; v++) {\n            if (parent[v] != -1) result.emplace_back(parent[v],\
    \ v);\n        }\n        return result;\n    }\n\n    m1une::graph::Graph<int>\
    \ to_graph() const {\n        m1une::graph::Graph<int> g(_n);\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (parent[v] != -1) g.add_edge(parent[v],\
    \ v);\n        }\n        return g;\n    }\n};\n\ntemplate <class T, class Compare\
    \ = std::less<T>>\nCartesianTree cartesian_tree(const std::vector<T>& a, Compare\
    \ comp = Compare()) {\n    CartesianTree result;\n    result.build(a, comp);\n\
    \    return result;\n}\n\n}  // namespace tree\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_CARTESIAN_TREE_HPP\n#define M1UNE_TREE_CARTESIAN_TREE_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <functional>\n#include\
    \ <limits>\n#include <utility>\n#include <vector>\n\n#include \"../graph.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nstruct CartesianTree {\n    int root;\n\
    \    std::vector<int> parent;\n    std::vector<int> left;\n    std::vector<int>\
    \ right;\n\n   private:\n    int _n;\n\n    void check_vertex(int v) const {\n\
    \        assert(0 <= v && v < _n);\n    }\n\n   public:\n    CartesianTree() :\
    \ root(-1), _n(0) {}\n\n    template <class T, class Compare = std::less<T>>\n\
    \    explicit CartesianTree(const std::vector<T>& a, Compare comp = Compare())\
    \ : root(-1), _n(0) {\n        build(a, comp);\n    }\n\n    template <class T,\
    \ class Compare = std::less<T>>\n    void build(const std::vector<T>& a, Compare\
    \ comp = Compare()) {\n        assert(a.size() <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n\
    \        _n = int(a.size());\n        root = -1;\n        parent.assign(_n, -1);\n\
    \        left.assign(_n, -1);\n        right.assign(_n, -1);\n\n        std::vector<int>\
    \ stack;\n        stack.reserve(_n);\n        for (int i = 0; i < _n; i++) {\n\
    \            int last = -1;\n            while (!stack.empty() && comp(a[i], a[stack.back()]))\
    \ {\n                last = stack.back();\n                stack.pop_back();\n\
    \            }\n            if (last != -1) {\n                left[i] = last;\n\
    \                parent[last] = i;\n            }\n            if (!stack.empty())\
    \ {\n                right[stack.back()] = i;\n                parent[i] = stack.back();\n\
    \            }\n            stack.push_back(i);\n        }\n\n        if (!stack.empty())\
    \ root = stack.front();\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    int\
    \ parent_or_self(int v) const {\n        check_vertex(v);\n        return parent[v]\
    \ == -1 ? v : parent[v];\n    }\n\n    std::vector<int> parent_with_root_self()\
    \ const {\n        std::vector<int> result = parent;\n        if (root != -1)\
    \ result[root] = root;\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> edges() const {\n        std::vector<std::pair<int, int>> result;\n  \
    \      if (_n == 0) return result;\n        result.reserve(_n - 1);\n        for\
    \ (int v = 0; v < _n; v++) {\n            if (parent[v] != -1) result.emplace_back(parent[v],\
    \ v);\n        }\n        return result;\n    }\n\n    m1une::graph::Graph<int>\
    \ to_graph() const {\n        m1une::graph::Graph<int> g(_n);\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (parent[v] != -1) g.add_edge(parent[v],\
    \ v);\n        }\n        return g;\n    }\n};\n\ntemplate <class T, class Compare\
    \ = std::less<T>>\nCartesianTree cartesian_tree(const std::vector<T>& a, Compare\
    \ comp = Compare()) {\n    CartesianTree result;\n    result.build(a, comp);\n\
    \    return result;\n}\n\n}  // namespace tree\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_TREE_CARTESIAN_TREE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/tree/cartesian_tree.hpp
  requiredBy:
  - graph/tree/all.hpp
  - graph/all.hpp
  timestamp: '2026-07-11 19:47:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/tree/cartesian_tree.test.cpp
  - verify/graph/tree/tree_algorithms.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/tree/cartesian_tree.hpp
layout: document
title: Cartesian Tree
---

## Overview

`m1une::tree::CartesianTree` builds the Cartesian tree of an array. With the
default comparator, the minimum element is the root, each parent has value no
greater than its children, and an inorder traversal visits indices in increasing
order.

Use `std::greater<T>` to build the maximum Cartesian tree. More generally,
`comp(x, y)` means that value `x` has higher priority and should be closer to
the root than value `y`. If neither value compares before the other, the smaller
index is kept closer to the root.

The structure stores only vertex indices. It can be converted to
`m1une::graph::Graph<int>` when you want to use the other tree helpers.

## Public Members

| Member | Type | Description |
| --- | --- | --- |
| `root` | `int` | Root index, or `-1` for an empty tree. |
| `parent` | `std::vector<int>` | Parent index, or `-1` at the root. |
| `left` | `std::vector<int>` | Left child index, or `-1`. |
| `right` | `std::vector<int>` | Right child index, or `-1`. |

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `CartesianTree()` | Creates an empty tree. | $O(1)$ |
| `CartesianTree(const std::vector<T>& a, Compare comp = Compare())` | Builds the Cartesian tree of `a`. | $O(N)$ |
| `void build(const std::vector<T>& a, Compare comp = Compare())` | Rebuilds the structure from `a`. | $O(N)$ |
| `int size() const` | Returns the number of vertices. | $O(1)$ |
| `bool empty() const` | Returns whether the tree is empty. | $O(1)$ |
| `int parent_or_self(int v) const` | Returns `parent[v]`, or `v` when `v` is the root. | $O(1)$ |
| `std::vector<int> parent_with_root_self() const` | Returns the parent array with `root` as its own parent. | $O(N)$ |
| `std::vector<std::pair<int, int>> edges() const` | Returns directed `(parent, child)` pairs. | $O(N)$ |
| `m1une::graph::Graph<int> to_graph() const` | Returns an undirected graph with one edge per parent-child relation. | $O(N)$ |

## Notes

The implementation is iterative and uses a monotone stack. It does not mutate
the input array. The comparator must model a strict weak ordering.

Library Checker's `cartesian_tree` problem asks for the root to be printed as
its own parent; use `parent_with_root_self()` for that convention.

## Example

```cpp
#include "graph/tree/cartesian_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a = {3, 1, 4, 0, 2};

    m1une::tree::CartesianTree tree(a);
    std::vector<int> parent = tree.parent_with_root_self();

    for (int i = 0; i < int(parent.size()); i++) {
        if (i) std::cout << ' ';
        std::cout << parent[i];
    }
    std::cout << "\n";
}
```
