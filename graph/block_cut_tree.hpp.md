---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/biconnected_components.hpp
    title: Biconnected Components
  - icon: ':question:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/graph/block_cut_tree.test.cpp
    title: verify/graph/block_cut_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/block_cut_tree.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <vector>\n\n#line 1 \"graph/biconnected_components.hpp\"\n\n\n\n#line 6 \"graph/biconnected_components.hpp\"\
    \n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 5 \"graph/graph.hpp\"\n#include <utility>\n\
    #line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate\
    \ <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
    \    int to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1),\
    \ to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_\
    \ = T(1), int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        _g[u].push_back(edge_type(u,\
    \ v, cost, id));\n        int v_idx = int(_g[v].size());\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
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
    \ m1une\n\n\n#line 8 \"graph/biconnected_components.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nstruct BiconnectedComponentsResult {\n    std::vector<std::vector<int>>\
    \ components;\n    std::vector<std::vector<int>> edge_components;\n    std::vector<int>\
    \ component_of_edge;\n    std::vector<std::vector<int>> vertex_components;\n \
    \   std::vector<int> articulation;\n    std::vector<int> ord;\n    std::vector<int>\
    \ low;\n\n    int component_count() const {\n        return int(components.size());\n\
    \    }\n\n    bool is_articulation(int vertex) const {\n        assert(0 <= vertex\
    \ && vertex < int(vertex_components.size()));\n        return vertex_components[vertex].size()\
    \ >= 2;\n    }\n};\n\n// Decomposes an undirected graph into maximal vertex-biconnected\
    \ blocks.\n// Every active edge belongs to exactly one block. Isolated vertices\
    \ form\n// singleton blocks, and articulation vertices occur in multiple blocks.\n\
    template <class T>\nBiconnectedComponentsResult biconnected_components(const Graph<T>&\
    \ graph) {\n    const int n = graph.size();\n    const int edge_count = graph.edge_count();\n\
    \n    BiconnectedComponentsResult result;\n    result.component_of_edge.assign(edge_count,\
    \ -1);\n    result.vertex_components.assign(n, {});\n    result.ord.assign(n,\
    \ -1);\n    result.low.assign(n, -1);\n\n    std::vector<int> edge_from(edge_count,\
    \ -1);\n    std::vector<int> edge_to(edge_count, -1);\n    std::vector<int> incidence_count(edge_count,\
    \ 0);\n    std::vector<int> alive_degree(n, 0);\n    for (int vertex = 0; vertex\
    \ < n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex]) {\n    \
    \        if (!edge.alive) continue;\n            assert(0 <= edge.id && edge.id\
    \ < edge_count);\n            alive_degree[vertex]++;\n            if (incidence_count[edge.id]\
    \ == 0) {\n                edge_from[edge.id] = edge.from;\n                edge_to[edge.id]\
    \ = edge.to;\n            }\n            incidence_count[edge.id]++;\n       \
    \ }\n    }\n#ifndef NDEBUG\n    for (int edge_id = 0; edge_id < edge_count; edge_id++)\
    \ {\n        if (incidence_count[edge_id] == 0) continue;\n        assert(incidence_count[edge_id]\
    \ == 2);\n        assert(edge_from[edge_id] != edge_to[edge_id]);\n    }\n#endif\n\
    \n    std::vector<int> parent(n, -1);\n    std::vector<int> parent_edge(n, -1);\n\
    \    std::vector<int> next_edge(n, 0);\n    std::vector<int> dfs_stack;\n    std::vector<int>\
    \ edge_stack;\n    std::vector<int> vertex_mark(n, -1);\n    int timer = 0;\n\n\
    \    auto add_singleton = [&](int vertex) {\n        const int component = result.component_count();\n\
    \        result.components.push_back(std::vector<int>(1, vertex));\n        result.edge_components.emplace_back();\n\
    \        result.vertex_components[vertex].push_back(component);\n    };\n\n  \
    \  auto extract_component = [&](int stopping_edge) {\n        const int component\
    \ = result.component_count();\n        result.components.emplace_back();\n   \
    \     result.edge_components.emplace_back();\n        std::vector<int>& vertices\
    \ = result.components.back();\n        std::vector<int>& edges = result.edge_components.back();\n\
    \n        while (true) {\n            assert(!edge_stack.empty());\n         \
    \   const int edge_id = edge_stack.back();\n            edge_stack.pop_back();\n\
    \            edges.push_back(edge_id);\n            result.component_of_edge[edge_id]\
    \ = component;\n\n            const int endpoints[2] = {edge_from[edge_id], edge_to[edge_id]};\n\
    \            for (int vertex : endpoints) {\n                if (vertex_mark[vertex]\
    \ == component) continue;\n                vertex_mark[vertex] = component;\n\
    \                vertices.push_back(vertex);\n            }\n            if (edge_id\
    \ == stopping_edge) break;\n        }\n        for (int vertex : vertices) {\n\
    \            result.vertex_components[vertex].push_back(component);\n        }\n\
    \    };\n\n    for (int root = 0; root < n; root++) {\n        if (result.ord[root]\
    \ != -1) continue;\n        if (alive_degree[root] == 0) {\n            result.ord[root]\
    \ = result.low[root] = timer++;\n            add_singleton(root);\n          \
    \  continue;\n        }\n\n        result.ord[root] = result.low[root] = timer++;\n\
    \        dfs_stack.push_back(root);\n        while (!dfs_stack.empty()) {\n  \
    \          const int vertex = dfs_stack.back();\n            if (next_edge[vertex]\
    \ < int(graph[vertex].size())) {\n                const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n\
    \                if (!edge.alive || edge.id == parent_edge[vertex]) continue;\n\
    \                const int to = edge.to;\n                if (result.ord[to] ==\
    \ -1) {\n                    parent[to] = vertex;\n                    parent_edge[to]\
    \ = edge.id;\n                    edge_stack.push_back(edge.id);\n           \
    \         result.ord[to] = result.low[to] = timer++;\n                    dfs_stack.push_back(to);\n\
    \                } else if (result.ord[to] < result.ord[vertex]) {\n         \
    \           edge_stack.push_back(edge.id);\n                    if (result.ord[to]\
    \ < result.low[vertex]) {\n                        result.low[vertex] = result.ord[to];\n\
    \                    }\n                }\n                continue;\n       \
    \     }\n\n            dfs_stack.pop_back();\n            const int parent_vertex\
    \ = parent[vertex];\n            if (parent_vertex == -1) {\n                assert(edge_stack.empty());\n\
    \                continue;\n            }\n            if (result.low[vertex]\
    \ < result.low[parent_vertex]) {\n                result.low[parent_vertex] =\
    \ result.low[vertex];\n            }\n            if (result.ord[parent_vertex]\
    \ <= result.low[vertex]) {\n                extract_component(parent_edge[vertex]);\n\
    \            }\n        }\n    }\n\n    for (int vertex = 0; vertex < n; vertex++)\
    \ {\n        if (result.is_articulation(vertex)) result.articulation.push_back(vertex);\n\
    \    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 8 \"graph/block_cut_tree.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct BlockCutTreeResult {\n    std::vector<std::vector<int>> forest;\n\
    \    std::vector<int> node_of_block;\n    std::vector<int> node_of_articulation;\n\
    \    std::vector<int> node_of_vertex;\n    std::vector<int> block_of_node;\n \
    \   std::vector<int> articulation_of_node;\n\n    int node_count() const {\n \
    \       return int(forest.size());\n    }\n\n    int block_count() const {\n \
    \       return int(node_of_block.size());\n    }\n\n    bool is_block_node(int\
    \ node) const {\n        assert(0 <= node && node < node_count());\n        return\
    \ block_of_node[node] != -1;\n    }\n\n    bool is_articulation_node(int node)\
    \ const {\n        assert(0 <= node && node < node_count());\n        return articulation_of_node[node]\
    \ != -1;\n    }\n};\n\n// Builds the block-cut forest of a biconnected-components\
    \ decomposition.\n// Block nodes have IDs [0, block_count); articulation nodes\
    \ follow them.\ninline BlockCutTreeResult block_cut_tree(\n    const BiconnectedComponentsResult&\
    \ biconnected\n) {\n    const int vertex_count = int(biconnected.vertex_components.size());\n\
    \    const int block_count = biconnected.component_count();\n\n    BlockCutTreeResult\
    \ result;\n    result.node_of_block.resize(block_count);\n    result.node_of_articulation.assign(vertex_count,\
    \ -1);\n    result.node_of_vertex.assign(vertex_count, -1);\n    result.forest.resize(block_count);\n\
    \    result.block_of_node.resize(block_count);\n    result.articulation_of_node.assign(block_count,\
    \ -1);\n    for (int block = 0; block < block_count; block++) {\n        result.node_of_block[block]\
    \ = block;\n        result.block_of_node[block] = block;\n    }\n\n    for (int\
    \ vertex = 0; vertex < vertex_count; vertex++) {\n        const std::vector<int>&\
    \ blocks = biconnected.vertex_components[vertex];\n        assert(!blocks.empty());\n\
    \        if (blocks.size() == 1) {\n            assert(0 <= blocks[0] && blocks[0]\
    \ < block_count);\n            result.node_of_vertex[vertex] = result.node_of_block[blocks[0]];\n\
    \            continue;\n        }\n\n        const int node = result.node_count();\n\
    \        result.node_of_articulation[vertex] = node;\n        result.node_of_vertex[vertex]\
    \ = node;\n        result.forest.emplace_back();\n        result.block_of_node.push_back(-1);\n\
    \        result.articulation_of_node.push_back(vertex);\n        for (int block\
    \ : blocks) {\n            assert(0 <= block && block < block_count);\n      \
    \      const int block_node = result.node_of_block[block];\n            result.forest[node].push_back(block_node);\n\
    \            result.forest[block_node].push_back(node);\n        }\n    }\n  \
    \  return result;\n}\n\ntemplate <class T>\nBlockCutTreeResult block_cut_tree(const\
    \ Graph<T>& graph) {\n    return block_cut_tree(biconnected_components(graph));\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_BLOCK_CUT_TREE_HPP\n#define M1UNE_GRAPH_BLOCK_CUT_TREE_HPP\
    \ 1\n\n#include <cassert>\n#include <vector>\n\n#include \"biconnected_components.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct BlockCutTreeResult {\n    std::vector<std::vector<int>>\
    \ forest;\n    std::vector<int> node_of_block;\n    std::vector<int> node_of_articulation;\n\
    \    std::vector<int> node_of_vertex;\n    std::vector<int> block_of_node;\n \
    \   std::vector<int> articulation_of_node;\n\n    int node_count() const {\n \
    \       return int(forest.size());\n    }\n\n    int block_count() const {\n \
    \       return int(node_of_block.size());\n    }\n\n    bool is_block_node(int\
    \ node) const {\n        assert(0 <= node && node < node_count());\n        return\
    \ block_of_node[node] != -1;\n    }\n\n    bool is_articulation_node(int node)\
    \ const {\n        assert(0 <= node && node < node_count());\n        return articulation_of_node[node]\
    \ != -1;\n    }\n};\n\n// Builds the block-cut forest of a biconnected-components\
    \ decomposition.\n// Block nodes have IDs [0, block_count); articulation nodes\
    \ follow them.\ninline BlockCutTreeResult block_cut_tree(\n    const BiconnectedComponentsResult&\
    \ biconnected\n) {\n    const int vertex_count = int(biconnected.vertex_components.size());\n\
    \    const int block_count = biconnected.component_count();\n\n    BlockCutTreeResult\
    \ result;\n    result.node_of_block.resize(block_count);\n    result.node_of_articulation.assign(vertex_count,\
    \ -1);\n    result.node_of_vertex.assign(vertex_count, -1);\n    result.forest.resize(block_count);\n\
    \    result.block_of_node.resize(block_count);\n    result.articulation_of_node.assign(block_count,\
    \ -1);\n    for (int block = 0; block < block_count; block++) {\n        result.node_of_block[block]\
    \ = block;\n        result.block_of_node[block] = block;\n    }\n\n    for (int\
    \ vertex = 0; vertex < vertex_count; vertex++) {\n        const std::vector<int>&\
    \ blocks = biconnected.vertex_components[vertex];\n        assert(!blocks.empty());\n\
    \        if (blocks.size() == 1) {\n            assert(0 <= blocks[0] && blocks[0]\
    \ < block_count);\n            result.node_of_vertex[vertex] = result.node_of_block[blocks[0]];\n\
    \            continue;\n        }\n\n        const int node = result.node_count();\n\
    \        result.node_of_articulation[vertex] = node;\n        result.node_of_vertex[vertex]\
    \ = node;\n        result.forest.emplace_back();\n        result.block_of_node.push_back(-1);\n\
    \        result.articulation_of_node.push_back(vertex);\n        for (int block\
    \ : blocks) {\n            assert(0 <= block && block < block_count);\n      \
    \      const int block_node = result.node_of_block[block];\n            result.forest[node].push_back(block_node);\n\
    \            result.forest[block_node].push_back(node);\n        }\n    }\n  \
    \  return result;\n}\n\ntemplate <class T>\nBlockCutTreeResult block_cut_tree(const\
    \ Graph<T>& graph) {\n    return block_cut_tree(biconnected_components(graph));\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_BLOCK_CUT_TREE_HPP\n"
  dependsOn:
  - graph/biconnected_components.hpp
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/block_cut_tree.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-13 03:42:12+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/block_cut_tree.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/block_cut_tree.hpp
layout: document
title: Block-Cut Tree
---

## Overview

This header converts a vertex-biconnected-components decomposition into its
block-cut forest. Each block becomes one node, each articulation vertex becomes
one node, and an edge joins a block to every articulation vertex it contains.
For a connected input graph the result is a tree; for a disconnected graph it
is a forest.

Every original vertex has a canonical node. An articulation vertex maps to its
articulation node, while any other vertex maps to its unique block node. This is
useful for reducing vertex-separator path queries to ordinary tree queries.

## Graph Requirements

The same requirements as `biconnected_components` apply: build an undirected
graph with `Graph<T>::add_edge`; self-loops are unsupported, parallel edges are
supported, and inactive edges are ignored. Isolated vertices become isolated
block nodes.

## Node Numbering

Block nodes have IDs in `[0, block_count())`, in the same order as
`BiconnectedComponentsResult::components`. Articulation nodes follow block
nodes, in increasing order of the original vertex ID.

## API

```cpp
struct BlockCutTreeResult {
    std::vector<std::vector<int>> forest;
    std::vector<int> node_of_block;
    std::vector<int> node_of_articulation;
    std::vector<int> node_of_vertex;
    std::vector<int> block_of_node;
    std::vector<int> articulation_of_node;

    int node_count() const;
    int block_count() const;
    bool is_block_node(int node) const;
    bool is_articulation_node(int node) const;
};

BlockCutTreeResult block_cut_tree(
    const BiconnectedComponentsResult& biconnected
);

template <class T>
BlockCutTreeResult block_cut_tree(const Graph<T>& graph);
```

| Member or function | Description | Complexity |
| --- | --- | --- |
| `forest[node]` | Adjacent nodes in the block-cut forest. | -- |
| `node_of_block[block]` | Forest node representing `block`. | $O(1)$ |
| `node_of_articulation[v]` | Articulation node for original vertex `v`, or `-1` if `v` is not an articulation. | $O(1)$ |
| `node_of_vertex[v]` | Canonical forest node representing original vertex `v`. | $O(1)$ |
| `block_of_node[node]` | Original block ID, or `-1` for an articulation node. | $O(1)$ |
| `articulation_of_node[node]` | Original articulation vertex, or `-1` for a block node. | $O(1)$ |
| `node_count()` | Number of block and articulation nodes. | $O(1)$ |
| `block_count()` | Number of block nodes. | $O(1)$ |
| `is_block_node(node)` | Whether `node` represents a block. | $O(1)$ |
| `is_articulation_node(node)` | Whether `node` represents an articulation vertex. | $O(1)$ |
| `block_cut_tree(biconnected)` | Builds the forest from an existing decomposition. | $O(N + M)$ |
| `block_cut_tree(graph)` | Computes the decomposition and builds the forest. | $O(N + M)$ |

The graph overload does not mutate the input. The result owns its vectors and
uses $O(N + M)$ memory. Use the decomposition overload when the blocks are also
needed, so they are not computed twice.

## Example

```cpp
#include "graph/block_cut_tree.hpp"

#include <iostream>

int main() {
    m1une::graph::Graph<> graph(5);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);
    graph.add_edge(1, 3);
    graph.add_edge(3, 4);

    auto biconnected = m1une::graph::biconnected_components(graph);
    auto block_cut = m1une::graph::block_cut_tree(biconnected);
    std::cout << block_cut.node_count() << "\n";  // 5
    std::cout << block_cut.node_of_articulation[1] << "\n";
    std::cout << block_cut.node_of_vertex[0] << "\n";
}
```
