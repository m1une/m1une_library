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
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/k_shortest_walk.test.cpp
    title: verify/graph/k_shortest_walk.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/k_shortest_walk.hpp\"\n\n\n\n#include <cassert>\n\
    #include <functional>\n#include <limits>\n#include <queue>\n#include <utility>\n\
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
    \ m1une\n\n\n#line 12 \"graph/k_shortest_walk.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nnamespace internal {\n\ntemplate <class T>\nclass KShortestWalkHeap\
    \ {\n    struct Node {\n        T key;\n        int to;\n        int left;\n \
    \       int right;\n        int rank;\n    };\n\n    std::vector<Node> _nodes;\n\
    \n    int rank(int root) const {\n        return root == -1 ? 0 : _nodes[root].rank;\n\
    \    }\n\n   public:\n    int make_node(T key, int to) {\n        int result =\
    \ int(_nodes.size());\n        _nodes.push_back(Node{key, to, -1, -1, 1});\n \
    \       return result;\n    }\n\n    int meld_mutable(int first, int second) {\n\
    \        if (first == -1) return second;\n        if (second == -1) return first;\n\
    \        if (_nodes[second].key < _nodes[first].key) std::swap(first, second);\n\
    \        _nodes[first].right = meld_mutable(_nodes[first].right, second);\n  \
    \      if (rank(_nodes[first].left) < rank(_nodes[first].right)) {\n         \
    \   std::swap(_nodes[first].left, _nodes[first].right);\n        }\n        _nodes[first].rank\
    \ = rank(_nodes[first].right) + 1;\n        return first;\n    }\n\n    int meld_persistent(int\
    \ first, int second) {\n        if (first == -1) return second;\n        if (second\
    \ == -1) return first;\n        if (_nodes[second].key < _nodes[first].key) std::swap(first,\
    \ second);\n        int result = int(_nodes.size());\n        _nodes.push_back(_nodes[first]);\n\
    \        _nodes[result].right = meld_persistent(_nodes[result].right, second);\n\
    \        if (rank(_nodes[result].left) < rank(_nodes[result].right)) {\n     \
    \       std::swap(_nodes[result].left, _nodes[result].right);\n        }\n   \
    \     _nodes[result].rank = rank(_nodes[result].right) + 1;\n        return result;\n\
    \    }\n\n    const Node& operator[](int index) const {\n        return _nodes[index];\n\
    \    }\n};\n\n}  // namespace internal\n\ntemplate <class T>\nstd::vector<T> k_shortest_walk(\n\
    \    const Graph<T>& g,\n    int s,\n    int t,\n    int k,\n    T inf = std::numeric_limits<T>::max()\
    \ / T(4)\n) {\n    int n = g.size();\n    assert(0 <= s && s < n);\n    assert(0\
    \ <= t && t < n);\n    assert(0 <= k);\n    if (k == 0) return {};\n\n    struct\
    \ ReverseEdge {\n        int from;\n        int index;\n        T cost;\n    };\n\
    \    std::vector<std::vector<ReverseEdge>> reverse_graph(n);\n    for (int from\
    \ = 0; from < n; from++) {\n        for (int index = 0; index < int(g[from].size());\
    \ index++) {\n            const auto& edge = g[from][index];\n            if (!edge.alive)\
    \ continue;\n            assert(T(0) <= edge.cost);\n            reverse_graph[edge.to].push_back(ReverseEdge{from,\
    \ index, edge.cost});\n        }\n    }\n\n    std::vector<T> dist(n, inf);\n\
    \    std::vector<int> tree_edge(n, -1);\n    std::vector<int> order;\n    order.reserve(n);\n\
    \    using QueueEntry = std::pair<T, int>;\n    std::priority_queue<QueueEntry,\
    \ std::vector<QueueEntry>, std::greater<QueueEntry>> queue;\n    dist[t] = T(0);\n\
    \    queue.emplace(T(0), t);\n    while (!queue.empty()) {\n        auto [current_dist,\
    \ vertex] = queue.top();\n        queue.pop();\n        if (dist[vertex] != current_dist)\
    \ continue;\n        order.push_back(vertex);\n        for (const auto& edge :\
    \ reverse_graph[vertex]) {\n            T next_dist = current_dist + edge.cost;\n\
    \            if (dist[edge.from] <= next_dist) continue;\n            dist[edge.from]\
    \ = next_dist;\n            tree_edge[edge.from] = edge.index;\n            queue.emplace(next_dist,\
    \ edge.from);\n        }\n    }\n    if (dist[s] == inf) return {};\n\n    internal::KShortestWalkHeap<T>\
    \ heap_pool;\n    std::vector<int> local_heap(n, -1);\n    for (int vertex : order)\
    \ {\n        for (int index = 0; index < int(g[vertex].size()); index++) {\n \
    \           const auto& edge = g[vertex][index];\n            if (!edge.alive\
    \ || dist[edge.to] == inf || index == tree_edge[vertex]) continue;\n         \
    \   T extra = edge.cost + dist[edge.to] - dist[vertex];\n            assert(T(0)\
    \ <= extra);\n            int node = heap_pool.make_node(extra, edge.to);\n  \
    \          local_heap[vertex] = heap_pool.meld_mutable(local_heap[vertex], node);\n\
    \        }\n    }\n\n    std::vector<int> path_heap(n, -1);\n    for (int vertex\
    \ : order) {\n        int inherited = -1;\n        if (tree_edge[vertex] != -1)\
    \ inherited = path_heap[g[vertex][tree_edge[vertex]].to];\n        path_heap[vertex]\
    \ = heap_pool.meld_persistent(inherited, local_heap[vertex]);\n    }\n\n    std::vector<T>\
    \ result;\n    result.reserve(k);\n    result.push_back(dist[s]);\n    std::priority_queue<QueueEntry,\
    \ std::vector<QueueEntry>, std::greater<QueueEntry>> candidates;\n    if (path_heap[s]\
    \ != -1) {\n        candidates.emplace(dist[s] + heap_pool[path_heap[s]].key,\
    \ path_heap[s]);\n    }\n    while (int(result.size()) < k && !candidates.empty())\
    \ {\n        auto [cost, node_index] = candidates.top();\n        candidates.pop();\n\
    \        result.push_back(cost);\n        const auto& node = heap_pool[node_index];\n\
    \        if (node.left != -1) {\n            candidates.emplace(cost - node.key\
    \ + heap_pool[node.left].key, node.left);\n        }\n        if (node.right !=\
    \ -1) {\n            candidates.emplace(cost - node.key + heap_pool[node.right].key,\
    \ node.right);\n        }\n        int next_heap = path_heap[node.to];\n     \
    \   if (next_heap != -1) {\n            candidates.emplace(cost + heap_pool[next_heap].key,\
    \ next_heap);\n        }\n    }\n    return result;\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_K_SHORTEST_WALK_HPP\n#define M1UNE_GRAPH_K_SHORTEST_WALK_HPP\
    \ 1\n\n#include <cassert>\n#include <functional>\n#include <limits>\n#include\
    \ <queue>\n#include <utility>\n#include <vector>\n\n#include \"graph.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\nnamespace internal {\n\ntemplate <class\
    \ T>\nclass KShortestWalkHeap {\n    struct Node {\n        T key;\n        int\
    \ to;\n        int left;\n        int right;\n        int rank;\n    };\n\n  \
    \  std::vector<Node> _nodes;\n\n    int rank(int root) const {\n        return\
    \ root == -1 ? 0 : _nodes[root].rank;\n    }\n\n   public:\n    int make_node(T\
    \ key, int to) {\n        int result = int(_nodes.size());\n        _nodes.push_back(Node{key,\
    \ to, -1, -1, 1});\n        return result;\n    }\n\n    int meld_mutable(int\
    \ first, int second) {\n        if (first == -1) return second;\n        if (second\
    \ == -1) return first;\n        if (_nodes[second].key < _nodes[first].key) std::swap(first,\
    \ second);\n        _nodes[first].right = meld_mutable(_nodes[first].right, second);\n\
    \        if (rank(_nodes[first].left) < rank(_nodes[first].right)) {\n       \
    \     std::swap(_nodes[first].left, _nodes[first].right);\n        }\n       \
    \ _nodes[first].rank = rank(_nodes[first].right) + 1;\n        return first;\n\
    \    }\n\n    int meld_persistent(int first, int second) {\n        if (first\
    \ == -1) return second;\n        if (second == -1) return first;\n        if (_nodes[second].key\
    \ < _nodes[first].key) std::swap(first, second);\n        int result = int(_nodes.size());\n\
    \        _nodes.push_back(_nodes[first]);\n        _nodes[result].right = meld_persistent(_nodes[result].right,\
    \ second);\n        if (rank(_nodes[result].left) < rank(_nodes[result].right))\
    \ {\n            std::swap(_nodes[result].left, _nodes[result].right);\n     \
    \   }\n        _nodes[result].rank = rank(_nodes[result].right) + 1;\n       \
    \ return result;\n    }\n\n    const Node& operator[](int index) const {\n   \
    \     return _nodes[index];\n    }\n};\n\n}  // namespace internal\n\ntemplate\
    \ <class T>\nstd::vector<T> k_shortest_walk(\n    const Graph<T>& g,\n    int\
    \ s,\n    int t,\n    int k,\n    T inf = std::numeric_limits<T>::max() / T(4)\n\
    ) {\n    int n = g.size();\n    assert(0 <= s && s < n);\n    assert(0 <= t &&\
    \ t < n);\n    assert(0 <= k);\n    if (k == 0) return {};\n\n    struct ReverseEdge\
    \ {\n        int from;\n        int index;\n        T cost;\n    };\n    std::vector<std::vector<ReverseEdge>>\
    \ reverse_graph(n);\n    for (int from = 0; from < n; from++) {\n        for (int\
    \ index = 0; index < int(g[from].size()); index++) {\n            const auto&\
    \ edge = g[from][index];\n            if (!edge.alive) continue;\n           \
    \ assert(T(0) <= edge.cost);\n            reverse_graph[edge.to].push_back(ReverseEdge{from,\
    \ index, edge.cost});\n        }\n    }\n\n    std::vector<T> dist(n, inf);\n\
    \    std::vector<int> tree_edge(n, -1);\n    std::vector<int> order;\n    order.reserve(n);\n\
    \    using QueueEntry = std::pair<T, int>;\n    std::priority_queue<QueueEntry,\
    \ std::vector<QueueEntry>, std::greater<QueueEntry>> queue;\n    dist[t] = T(0);\n\
    \    queue.emplace(T(0), t);\n    while (!queue.empty()) {\n        auto [current_dist,\
    \ vertex] = queue.top();\n        queue.pop();\n        if (dist[vertex] != current_dist)\
    \ continue;\n        order.push_back(vertex);\n        for (const auto& edge :\
    \ reverse_graph[vertex]) {\n            T next_dist = current_dist + edge.cost;\n\
    \            if (dist[edge.from] <= next_dist) continue;\n            dist[edge.from]\
    \ = next_dist;\n            tree_edge[edge.from] = edge.index;\n            queue.emplace(next_dist,\
    \ edge.from);\n        }\n    }\n    if (dist[s] == inf) return {};\n\n    internal::KShortestWalkHeap<T>\
    \ heap_pool;\n    std::vector<int> local_heap(n, -1);\n    for (int vertex : order)\
    \ {\n        for (int index = 0; index < int(g[vertex].size()); index++) {\n \
    \           const auto& edge = g[vertex][index];\n            if (!edge.alive\
    \ || dist[edge.to] == inf || index == tree_edge[vertex]) continue;\n         \
    \   T extra = edge.cost + dist[edge.to] - dist[vertex];\n            assert(T(0)\
    \ <= extra);\n            int node = heap_pool.make_node(extra, edge.to);\n  \
    \          local_heap[vertex] = heap_pool.meld_mutable(local_heap[vertex], node);\n\
    \        }\n    }\n\n    std::vector<int> path_heap(n, -1);\n    for (int vertex\
    \ : order) {\n        int inherited = -1;\n        if (tree_edge[vertex] != -1)\
    \ inherited = path_heap[g[vertex][tree_edge[vertex]].to];\n        path_heap[vertex]\
    \ = heap_pool.meld_persistent(inherited, local_heap[vertex]);\n    }\n\n    std::vector<T>\
    \ result;\n    result.reserve(k);\n    result.push_back(dist[s]);\n    std::priority_queue<QueueEntry,\
    \ std::vector<QueueEntry>, std::greater<QueueEntry>> candidates;\n    if (path_heap[s]\
    \ != -1) {\n        candidates.emplace(dist[s] + heap_pool[path_heap[s]].key,\
    \ path_heap[s]);\n    }\n    while (int(result.size()) < k && !candidates.empty())\
    \ {\n        auto [cost, node_index] = candidates.top();\n        candidates.pop();\n\
    \        result.push_back(cost);\n        const auto& node = heap_pool[node_index];\n\
    \        if (node.left != -1) {\n            candidates.emplace(cost - node.key\
    \ + heap_pool[node.left].key, node.left);\n        }\n        if (node.right !=\
    \ -1) {\n            candidates.emplace(cost - node.key + heap_pool[node.right].key,\
    \ node.right);\n        }\n        int next_heap = path_heap[node.to];\n     \
    \   if (next_heap != -1) {\n            candidates.emplace(cost + heap_pool[next_heap].key,\
    \ next_heap);\n        }\n    }\n    return result;\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n#endif  // M1UNE_GRAPH_K_SHORTEST_WALK_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/k_shortest_walk.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  - graph/directed.hpp
  - graph/shortest_path.hpp
  timestamp: '2026-07-13 04:00:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/k_shortest_walk.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/k_shortest_walk.hpp
layout: document
title: K-Shortest Walk
---

## Overview

`k_shortest_walk` lists the lengths of the shortest walks from one vertex to
another in nondecreasing order. A walk may repeat vertices and edges, and two
different walks are counted separately even when their lengths are equal.

The implementation uses a shortest-path tree toward the target and persistently
melded heaps of Eppstein sidetracks. It is intended for large sparse or dense
directed graphs with non-negative edge costs.

## Requirements and Behavior

- `T` must support construction from integers, addition, subtraction, equality,
  and ordering.
- Every alive edge cost must be non-negative.
- Costs of all relevant walks and intermediate sums must fit in `T` and remain
  below `inf`.
- Inactive edges are ignored.
- If `s == t`, the empty walk of length zero is the first answer.
- If fewer than `k` walks exist, the returned vector is shorter than `k`. No
  sentinel value is appended.

## Function

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `k_shortest_walk` | `template <class T> std::vector<T> k_shortest_walk(const Graph<T>& g, int s, int t, int k, T inf = std::numeric_limits<T>::max() / T(4))` | Returns up to `k` walk lengths from `s` to `t` in nondecreasing order. | $O((N+M)\log N + M\log M + K\log K)$ time and $O(N+M+N\log M+K)$ memory. |

Here `M` counts alive adjacency entries, so an undirected edge stored by
`Graph::add_edge` contributes two entries. The graph itself is not modified.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/k_shortest_walk.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 2);
    g.add_directed_edge(1, 2, 3);
    g.add_directed_edge(0, 2, 8);
    g.add_directed_edge(1, 1, 1);

    auto lengths = m1une::graph::k_shortest_walk(g, 0, 2, 4);
    for (long long length : lengths) std::cout << length << "\n";
    // 5, 6, 7, 8
}
```
