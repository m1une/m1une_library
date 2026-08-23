---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  - icon: ':heavy_check_mark:'
    path: utilities/dynamic_bitset.hpp
    title: Dynamic Bitset
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/dag.hpp
    title: DAG Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/dag_algorithms.test.cpp
    title: verify/graph/dag_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/dag_reachability.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"utilities/dynamic_bitset.hpp\"\n\n\n\n#line 6 \"utilities/dynamic_bitset.hpp\"\
    \n#include <cstddef>\n#include <cstdint>\n#line 9 \"utilities/dynamic_bitset.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\n\nstruct DynamicBitset {\n   private:\n\
    \    static constexpr int BITS_PER_BLOCK = 64;\n    static constexpr uint64_t\
    \ FULL_BLOCK = ~uint64_t{0};\n\n    int _n;\n    std::vector<uint64_t> blocks;\n\
    \n    static int block_count(int n) {\n        assert(n >= 0);\n        return\
    \ (n + BITS_PER_BLOCK - 1) >> 6;\n    }\n\n    uint64_t tail_mask() const {\n\
    \        const int rem = _n & (BITS_PER_BLOCK - 1);\n        return rem == 0 ?\
    \ FULL_BLOCK : ((uint64_t{1} << rem) - 1);\n    }\n\n    // Keep unused bits in\
    \ the last block equal to zero.\n    void clean() {\n        if (!blocks.empty())\
    \ blocks.back() &= tail_mask();\n    }\n\n   public:\n    DynamicBitset() : _n(0),\
    \ blocks() {}\n\n    explicit DynamicBitset(int n, bool val = false) : _n(n),\
    \ blocks(block_count(n), val ? FULL_BLOCK : 0) {\n        if (val) clean();\n\
    \    }\n\n    // Returns the logical number of bits.\n    int size() const {\n\
    \        return _n;\n    }\n\n    // Returns whether the bit at index i is set.\n\
    \    bool test(int i) const {\n        assert(0 <= i && i < _n);\n        return\
    \ (blocks[i >> 6] >> (i & (BITS_PER_BLOCK - 1))) & 1;\n    }\n\n    // Sets the\
    \ bit at index i to true.\n    void set(int i) {\n        assert(0 <= i && i <\
    \ _n);\n        blocks[i >> 6] |= uint64_t{1} << (i & (BITS_PER_BLOCK - 1));\n\
    \    }\n\n    // Sets all bits to true.\n    void set() {\n        std::fill(blocks.begin(),\
    \ blocks.end(), FULL_BLOCK);\n        clean();\n    }\n\n    // Sets the bit at\
    \ index i to false.\n    void reset(int i) {\n        assert(0 <= i && i < _n);\n\
    \        blocks[i >> 6] &= ~(uint64_t{1} << (i & (BITS_PER_BLOCK - 1)));\n   \
    \ }\n\n    // Sets all bits to false.\n    void reset() {\n        std::fill(blocks.begin(),\
    \ blocks.end(), uint64_t{0});\n    }\n\n    // Flips the bit at index i.\n   \
    \ void flip(int i) {\n        assert(0 <= i && i < _n);\n        blocks[i >> 6]\
    \ ^= uint64_t{1} << (i & (BITS_PER_BLOCK - 1));\n    }\n\n    // Flips all bits.\n\
    \    void flip() {\n        for (uint64_t& block : blocks) block = ~block;\n \
    \       clean();\n    }\n\n    // Returns the number of set bits.\n    int popcount()\
    \ const {\n        int res = 0;\n        for (uint64_t block : blocks) res +=\
    \ __builtin_popcountll(block);\n        return res;\n    }\n\n    // Returns the\
    \ index of the least significant set bit, or -1 if no bit is set.\n    int lowbit()\
    \ const {\n        const int m = static_cast<int>(blocks.size());\n        for\
    \ (int i = 0; i < m; ++i) {\n            if (blocks[i] != 0) return (i << 6) +\
    \ __builtin_ctzll(blocks[i]);\n        }\n        return -1;\n    }\n\n    //\
    \ Returns the index of the most significant set bit, or -1 if no bit is set.\n\
    \    int topbit() const {\n        for (int i = static_cast<int>(blocks.size())\
    \ - 1; i >= 0; --i) {\n            if (blocks[i] != 0) return (i << 6) + (BITS_PER_BLOCK\
    \ - 1 - __builtin_clzll(blocks[i]));\n        }\n        return -1;\n    }\n\n\
    \    // Returns whether at least one bit is set.\n    bool any() const {\n   \
    \     for (uint64_t block : blocks) {\n            if (block != 0) return true;\n\
    \        }\n        return false;\n    }\n\n    // Returns whether every logical\
    \ bit is set.\n    bool all() const {\n        if (_n == 0) return true;\n\n \
    \       const int m = static_cast<int>(blocks.size());\n        for (int i = 0;\
    \ i + 1 < m; ++i) {\n            if (blocks[i] != FULL_BLOCK) return false;\n\
    \        }\n        return blocks.back() == tail_mask();\n    }\n\n    // Returns\
    \ whether no bit is set.\n    bool none() const {\n        return !any();\n  \
    \  }\n\n    DynamicBitset& operator&=(const DynamicBitset& other) {\n        assert(_n\
    \ == other._n);\n        const std::size_t m = blocks.size();\n        for (std::size_t\
    \ i = 0; i < m; ++i) blocks[i] &= other.blocks[i];\n        return *this;\n  \
    \  }\n\n    DynamicBitset& operator|=(const DynamicBitset& other) {\n        assert(_n\
    \ == other._n);\n        const std::size_t m = blocks.size();\n        for (std::size_t\
    \ i = 0; i < m; ++i) blocks[i] |= other.blocks[i];\n        return *this;\n  \
    \  }\n\n    DynamicBitset& operator^=(const DynamicBitset& other) {\n        assert(_n\
    \ == other._n);\n        const std::size_t m = blocks.size();\n        for (std::size_t\
    \ i = 0; i < m; ++i) blocks[i] ^= other.blocks[i];\n        return *this;\n  \
    \  }\n\n    DynamicBitset operator~() const {\n        DynamicBitset res = *this;\n\
    \        res.flip();\n        return res;\n    }\n\n    friend DynamicBitset operator&(DynamicBitset\
    \ lhs, const DynamicBitset& rhs) {\n        lhs &= rhs;\n        return lhs;\n\
    \    }\n\n    friend DynamicBitset operator|(DynamicBitset lhs, const DynamicBitset&\
    \ rhs) {\n        lhs |= rhs;\n        return lhs;\n    }\n\n    friend DynamicBitset\
    \ operator^(DynamicBitset lhs, const DynamicBitset& rhs) {\n        lhs ^= rhs;\n\
    \        return lhs;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include <array>\n#line 8 \"graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
    \ {\n    using cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n   \
    \ int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1),\
    \ alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool\
    \ alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_)\
    \ {}\n\n    int other(int v) const {\n        assert(v == from || v == to);\n\
    \        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    struct EdgePositions {\n        std::array<std::pair<int, int>, 2> value{};\n\
    \        int size = 0;\n\n        void push_back(std::pair<int, int> position)\
    \ {\n            assert(size < 2);\n            value[size++] = position;\n  \
    \      }\n    };\n\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<EdgePositions> _edge_positions;\n\n   public:\n    Graph()\
    \ : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
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
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (int i =\
    \ 0; i < _edge_positions[id].size; ++i) {\n            auto [v, idx] = _edge_positions[id].value[i];\n\
    \            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(_edge_positions[id].size\
    \ != 0);\n        auto [v, idx] = _edge_positions[id].value[0];\n        return\
    \ _g[v][idx].alive;\n    }\n\n    const std::vector<edge_type>& operator[](int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\
    \n    std::vector<edge_type>& operator[](int v) {\n        assert(0 <= v && v\
    \ < _n);\n        return _g[v];\n    }\n\n    const std::vector<std::vector<edge_type>>&\
    \ adjacency() const {\n        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>&\
    \ adjacency() {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool\
    \ include_inactive = false) const {\n        std::vector<edge_type> result;\n\
    \        result.reserve(_edge_count);\n        std::vector<char> used(_edge_count,\
    \ false);\n        for (int v = 0; v < _n; v++) {\n            for (const auto&\
    \ e : _g[v]) {\n                if (!include_inactive && !e.alive) continue;\n\
    \                if (0 <= e.id && e.id < _edge_count) {\n                    if\
    \ (used[e.id]) continue;\n                    used[e.id] = true;\n           \
    \     }\n                result.push_back(e);\n            }\n        }\n    \
    \    return result;\n    }\n\n    Graph reversed() const {\n        Graph result(_n);\n\
    \        result._edge_count = _edge_count;\n        result._edge_positions.assign(_edge_count,\
    \ {});\n        for (int v = 0; v < _n; v++) {\n            for (const auto& e\
    \ : _g[v]) {\n                int idx = int(result._g[e.to].size());\n       \
    \         result._g[e.to].push_back(edge_type(e.to, e.from, e.cost, e.id, e.alive));\n\
    \                if (0 <= e.id && e.id < _edge_count) result._edge_positions[e.id].push_back({e.to,\
    \ idx});\n            }\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/topological_sort.hpp\"\
    \n\n\n\n#line 5 \"graph/topological_sort.hpp\"\n#include <queue>\n#line 7 \"graph/topological_sort.hpp\"\
    \n\n#line 9 \"graph/topological_sort.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstd::optional<std::vector<int>> topological_sort(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> indeg(n, 0);\n \
    \   for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v]) {\n    \
    \        if (!e.alive) continue;\n            indeg[e.to]++;\n        }\n    }\n\
    \n    std::queue<int> que;\n    for (int v = 0; v < n; v++) {\n        if (indeg[v]\
    \ == 0) que.push(v);\n    }\n\n    std::vector<int> order;\n    order.reserve(n);\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        order.push_back(v);\n        for (const auto& e : g[v]) {\n         \
    \   if (!e.alive) continue;\n            indeg[e.to]--;\n            if (indeg[e.to]\
    \ == 0) que.push(e.to);\n        }\n    }\n\n    if (int(order.size()) != n) return\
    \ std::nullopt;\n    return order;\n}\n\ntemplate <class T>\nbool is_dag(const\
    \ Graph<T>& g) {\n    return topological_sort(g).has_value();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 13 \"graph/dag_reachability.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\nstruct DagReachability {\n    std::vector<utilities::DynamicBitset>\
    \ reachable_vertices;\n    std::vector<int> topological_order;\n\n    int size()\
    \ const {\n        return int(reachable_vertices.size());\n    }\n\n    bool reachable(int\
    \ from, int to) const {\n        assert(0 <= from && from < size());\n       \
    \ assert(0 <= to && to < size());\n        return reachable_vertices[from].test(to);\n\
    \    }\n};\n\ntemplate <class T>\nstd::optional<DagReachability> dag_reachability(const\
    \ Graph<T>& g) {\n    const int n = g.size();\n    auto order = topological_sort(g);\n\
    \    if (!order) return std::nullopt;\n\n    DagReachability result;\n    result.reachable_vertices.assign(n,\
    \ utilities::DynamicBitset(n));\n    result.topological_order = *order;\n    for\
    \ (int i = n - 1; i >= 0; i--) {\n        int v = (*order)[i];\n        result.reachable_vertices[v].set(v);\n\
    \        for (const auto& e : g[v]) {\n            if (e.alive) result.reachable_vertices[v]\
    \ |= result.reachable_vertices[e.to];\n        }\n    }\n    return result;\n\
    }\n\ntemplate <class T>\nstruct DagTransitiveReductionResult {\n    Graph<T> graph;\n\
    \    std::vector<int> original_edge_ids;\n};\n\ntemplate <class T>\nstd::optional<DagTransitiveReductionResult<T>>\
    \ dag_transitive_reduction(const Graph<T>& g) {\n    auto reachability = dag_reachability(g);\n\
    \    if (!reachability) return std::nullopt;\n\n    const int n = g.size();\n\
    \    std::vector<int> position(n);\n    for (int i = 0; i < n; i++) position[reachability->topological_order[i]]\
    \ = i;\n\n    std::vector<char> kept(g.edge_count(), false);\n    for (int v =\
    \ 0; v < n; v++) {\n        std::vector<const Edge<T>*> outgoing;\n        outgoing.reserve(g[v].size());\n\
    \        for (const auto& e : g[v]) {\n            if (e.alive) outgoing.push_back(&e);\n\
    \        }\n        std::stable_sort(outgoing.begin(), outgoing.end(), [&](const\
    \ auto* lhs, const auto* rhs) {\n            return position[lhs->to] < position[rhs->to];\n\
    \        });\n\n        utilities::DynamicBitset covered(n);\n        for (const\
    \ auto* e : outgoing) {\n            if (covered.test(e->to)) continue;\n    \
    \        kept[e->id] = true;\n            covered |= reachability->reachable_vertices[e->to];\n\
    \        }\n    }\n\n    DagTransitiveReductionResult<T> result;\n    result.graph\
    \ = Graph<T>(n);\n    for (int v = 0; v < n; v++) {\n        for (const auto&\
    \ e : g[v]) {\n            if (!e.alive || !kept[e.id]) continue;\n          \
    \  result.graph.add_directed_edge(e.from, e.to, e.cost);\n            result.original_edge_ids.push_back(e.id);\n\
    \        }\n    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_DAG_REACHABILITY_HPP\n#define M1UNE_GRAPH_DAG_REACHABILITY_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"../utilities/dynamic_bitset.hpp\"\
    \n#include \"graph.hpp\"\n#include \"topological_sort.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\nstruct DagReachability {\n    std::vector<utilities::DynamicBitset>\
    \ reachable_vertices;\n    std::vector<int> topological_order;\n\n    int size()\
    \ const {\n        return int(reachable_vertices.size());\n    }\n\n    bool reachable(int\
    \ from, int to) const {\n        assert(0 <= from && from < size());\n       \
    \ assert(0 <= to && to < size());\n        return reachable_vertices[from].test(to);\n\
    \    }\n};\n\ntemplate <class T>\nstd::optional<DagReachability> dag_reachability(const\
    \ Graph<T>& g) {\n    const int n = g.size();\n    auto order = topological_sort(g);\n\
    \    if (!order) return std::nullopt;\n\n    DagReachability result;\n    result.reachable_vertices.assign(n,\
    \ utilities::DynamicBitset(n));\n    result.topological_order = *order;\n    for\
    \ (int i = n - 1; i >= 0; i--) {\n        int v = (*order)[i];\n        result.reachable_vertices[v].set(v);\n\
    \        for (const auto& e : g[v]) {\n            if (e.alive) result.reachable_vertices[v]\
    \ |= result.reachable_vertices[e.to];\n        }\n    }\n    return result;\n\
    }\n\ntemplate <class T>\nstruct DagTransitiveReductionResult {\n    Graph<T> graph;\n\
    \    std::vector<int> original_edge_ids;\n};\n\ntemplate <class T>\nstd::optional<DagTransitiveReductionResult<T>>\
    \ dag_transitive_reduction(const Graph<T>& g) {\n    auto reachability = dag_reachability(g);\n\
    \    if (!reachability) return std::nullopt;\n\n    const int n = g.size();\n\
    \    std::vector<int> position(n);\n    for (int i = 0; i < n; i++) position[reachability->topological_order[i]]\
    \ = i;\n\n    std::vector<char> kept(g.edge_count(), false);\n    for (int v =\
    \ 0; v < n; v++) {\n        std::vector<const Edge<T>*> outgoing;\n        outgoing.reserve(g[v].size());\n\
    \        for (const auto& e : g[v]) {\n            if (e.alive) outgoing.push_back(&e);\n\
    \        }\n        std::stable_sort(outgoing.begin(), outgoing.end(), [&](const\
    \ auto* lhs, const auto* rhs) {\n            return position[lhs->to] < position[rhs->to];\n\
    \        });\n\n        utilities::DynamicBitset covered(n);\n        for (const\
    \ auto* e : outgoing) {\n            if (covered.test(e->to)) continue;\n    \
    \        kept[e->id] = true;\n            covered |= reachability->reachable_vertices[e->to];\n\
    \        }\n    }\n\n    DagTransitiveReductionResult<T> result;\n    result.graph\
    \ = Graph<T>(n);\n    for (int v = 0; v < n; v++) {\n        for (const auto&\
    \ e : g[v]) {\n            if (!e.alive || !kept[e.id]) continue;\n          \
    \  result.graph.add_directed_edge(e.from, e.to, e.cost);\n            result.original_edge_ids.push_back(e.id);\n\
    \        }\n    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GRAPH_DAG_REACHABILITY_HPP\n"
  dependsOn:
  - utilities/dynamic_bitset.hpp
  - graph/graph.hpp
  - graph/topological_sort.hpp
  isVerificationFile: false
  path: graph/dag_reachability.hpp
  requiredBy:
  - graph/all.hpp
  - graph/dag.hpp
  - graph/directed.hpp
  timestamp: '2026-08-24 00:41:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/dag_algorithms.test.cpp
  - verify/graph/range_edge_graph.test.cpp
documentation_of: graph/dag_reachability.hpp
layout: document
title: DAG Reachability and Transitive Reduction
---

## Overview

This header provides batched reachability queries and transitive reduction for
a directed acyclic graph. Both use dynamic bitsets propagated in reverse
topological order. A cyclic graph returns `std::nullopt`.

`dag_reachability` includes every zero-edge path, so `reachable(v, v)` is true.
The table is most appropriate when many reachability queries justify quadratic
memory.

`dag_transitive_reduction` removes every edge whose endpoints remain connected
by another directed path. It also reduces parallel edges to one representative.
The returned graph has the same reachability relation as the active input graph;
inactive edges are omitted. Costs do not affect reduction.

## Types

| Type | Member / method | Meaning | Complexity |
| --- | --- | --- | --- |
| `DagReachability` | `reachable_vertices` | Bitset of vertices reachable from each vertex. | Access to a bitset: $O(1)$ |
| `DagReachability` | `topological_order` | Topological order used to build the table. | Access: $O(1)$ |
| `DagReachability` | `int size() const` | Number of vertices. | $O(1)$ |
| `DagReachability` | `bool reachable(int from, int to) const` | Tests directed reachability, including `from == to`. | $O(1)$ |
| `DagTransitiveReductionResult<T>` | `graph` | Reduced graph. Its edge ids are newly assigned. | Access: $O(1)$ |
| `DagTransitiveReductionResult<T>` | `original_edge_ids` | Maps each new edge id to the retained input edge id. | Access: $O(1)$ |

## Functions

| Function | Signature | Complexity |
| --- | --- | --- |
| `dag_reachability` | `template <class T> std::optional<DagReachability> dag_reachability(const Graph<T>& g)` | $O((N + M)\lceil N / 64\rceil)$ time and $O(N\lceil N / 64\rceil)$ memory |
| `dag_transitive_reduction` | `template <class T> std::optional<DagTransitiveReductionResult<T>> dag_transitive_reduction(const Graph<T>& g)` | $O((N + M)\lceil N / 64\rceil + M\log M)$ time and $O(N\lceil N / 64\rceil + M)$ memory |

The sorting term is the sum of sorting outgoing edges at each vertex and is at
most $O(M\log M)$.

## Example

```cpp
#include "graph/dag_reachability.hpp"
#include "graph/graph.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<> g(3);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(1, 2);
    g.add_directed_edge(0, 2);  // Redundant.

    auto reach = m1une::graph::dag_reachability(g);
    if (reach) std::cout << reach->reachable(0, 2) << '\n';

    auto reduction = m1une::graph::dag_transitive_reduction(g);
    if (reduction) std::cout << reduction->graph.edge_count() << '\n';  // 2
}
```
