---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/flow/bounded_flow.hpp
    title: Bounded Flow
  - icon: ':heavy_check_mark:'
    path: graph/flow/flow.hpp
    title: Flow
  - icon: ':heavy_check_mark:'
    path: optimization/all.hpp
    title: Optimization All
  - icon: ':heavy_check_mark:'
    path: optimization/project_selection.hpp
    title: Project Selection
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/flow/flow_algorithms.test.cpp
    title: verify/graph/flow/flow_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/flow/max_flow.test.cpp
    title: verify/graph/flow/max_flow.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/integer_lp.test.cpp
    title: verify/optimization/integer_lp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/project_selection.test.cpp
    title: verify/optimization/project_selection.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/simplex.test.cpp
    title: verify/optimization/simplex.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/flow/max_flow.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstddef>\n#include <limits>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct MaxFlow\
    \ {\n    struct Edge {\n        int from;\n        int to;\n        Cap cap;\n\
    \        Cap flow;\n    };\n\n   private:\n    struct InternalEdge {\n       \
    \ int to;\n        int rev;\n        Cap cap;\n    };\n\n    struct Position {\n\
    \        int from;\n        int edge;\n    };\n\n    int _n;\n    std::vector<Position>\
    \ _pos;\n    std::vector<std::vector<InternalEdge>> _g;\n\n   public:\n    MaxFlow()\
    \ : MaxFlow(0) {}\n\n    explicit MaxFlow(int n) : _n(n), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    int\
    \ edge_count() const {\n        return int(_pos.size());\n    }\n\n    void reserve_edges(int\
    \ edge_count) {\n        assert(0 <= edge_count);\n        _pos.reserve(edge_count);\n\
    \        if (_n == 0 || edge_count == 0 ||\n            2 * std::size_t(edge_count)\
    \ < std::size_t(_n)) {\n            return;\n        }\n        const std::size_t\
    \ average_degree =\n            (2 * std::size_t(edge_count) + std::size_t(_n)\
    \ - 1)\n            / std::size_t(_n);\n        for (auto& edges : _g) edges.reserve(average_degree);\n\
    \    }\n\n    int add_edge(int from, int to, Cap cap) {\n        assert(0 <= from\
    \ && from < _n);\n        assert(0 <= to && to < _n);\n        assert(Cap(0) <=\
    \ cap);\n        int id = int(_pos.size());\n        int from_id = int(_g[from].size());\n\
    \        int to_id = int(_g[to].size());\n        if (from == to) to_id++;\n \
    \       _pos.push_back(Position{from, from_id});\n        _g[from].push_back(InternalEdge{to,\
    \ to_id, cap});\n        _g[to].push_back(InternalEdge{from, from_id, Cap(0)});\n\
    \        return id;\n    }\n\n    int add_undirected_edge(int first, int second,\
    \ Cap cap) {\n        static_assert(std::numeric_limits<Cap>::is_signed);\n  \
    \      assert(0 <= first && first < _n);\n        assert(0 <= second && second\
    \ < _n);\n        assert(Cap(0) <= cap);\n        assert(cap <= std::numeric_limits<Cap>::max()\
    \ / Cap(2));\n        int id = int(_pos.size());\n        int first_id = int(_g[first].size());\n\
    \        int second_id = int(_g[second].size());\n        if (first == second)\
    \ second_id++;\n        _pos.push_back(Position{first, ~first_id});\n        _g[first].push_back(InternalEdge{second,\
    \ second_id, cap});\n        _g[second].push_back(InternalEdge{first, first_id,\
    \ cap});\n        return id;\n    }\n\n    Edge get_edge(int i) const {\n    \
    \    assert(0 <= i && i < int(_pos.size()));\n        const auto& position = _pos[i];\n\
    \        int from = position.from;\n        bool undirected = position.edge <\
    \ 0;\n        int idx = undirected ? ~position.edge : position.edge;\n       \
    \ const auto& e = _g[from][idx];\n        const auto& re = _g[e.to][e.rev];\n\
    \        if (undirected) {\n            return Edge{\n                from,\n\
    \                e.to,\n                (e.cap + re.cap) / Cap(2),\n         \
    \       (re.cap - e.cap) / Cap(2)\n            };\n        }\n        return Edge{from,\
    \ e.to, e.cap + re.cap, re.cap};\n    }\n\n    std::vector<Edge> edges() const\
    \ {\n        std::vector<Edge> result;\n        result.reserve(_pos.size());\n\
    \        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));\n\
    \        return result;\n    }\n\n    void change_edge(int i, Cap new_cap, Cap\
    \ new_flow) {\n        assert(0 <= i && i < int(_pos.size()));\n        assert(Cap(0)\
    \ <= new_cap);\n        auto& position = _pos[i];\n        int from = position.from;\n\
    \        bool undirected = position.edge < 0;\n        int idx = undirected ?\
    \ ~position.edge : position.edge;\n        auto& e = _g[from][idx];\n        auto&\
    \ re = _g[e.to][e.rev];\n        if (undirected) {\n            assert(new_cap\
    \ <= std::numeric_limits<Cap>::max() / Cap(2));\n            assert(-new_cap <=\
    \ new_flow && new_flow <= new_cap);\n            e.cap = new_cap - new_flow;\n\
    \            re.cap = new_cap + new_flow;\n        } else {\n            assert(Cap(0)\
    \ <= new_flow && new_flow <= new_cap);\n            e.cap = new_cap - new_flow;\n\
    \            re.cap = new_flow;\n        }\n    }\n\n    Cap max_flow(int s, int\
    \ t) {\n        return max_flow(s, t, std::numeric_limits<Cap>::max());\n    }\n\
    \n    Cap max_flow(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s\
    \ < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\n     \
    \   std::vector<int> work(3 * std::size_t(_n));\n        int* level = work.data();\n\
    \        int* iter = level + _n;\n        int* queue = iter + _n;\n        auto\
    \ bfs = [&]() -> bool {\n            std::fill(level, level + _n, -1);\n     \
    \       int head = 0;\n            int tail = 0;\n            level[s] = 0;\n\
    \            queue[tail++] = s;\n            while (head != tail) {\n        \
    \        int v = queue[head++];\n                for (const auto& e : _g[v]) {\n\
    \                    if (e.cap == Cap(0) || level[e.to] != -1) continue;\n   \
    \                 level[e.to] = level[v] + 1;\n                    if (e.to ==\
    \ t) return true;\n                    queue[tail++] = e.to;\n               \
    \ }\n            }\n            return level[t] != -1;\n        };\n\n       \
    \ auto dfs = [&](auto&& self, int v, Cap up) -> Cap {\n            if (v == s)\
    \ return up;\n            Cap result = Cap(0);\n            const int current_level\
    \ = level[v];\n            for (int& i = iter[v]; i < int(_g[v].size()); i++)\
    \ {\n                auto& e = _g[v][i];\n                if (current_level <=\
    \ level[e.to]) continue;\n                auto& reverse = _g[e.to][e.rev];\n \
    \               if (reverse.cap == Cap(0)) continue;\n                Cap d =\
    \ self(\n                    self,\n                    e.to,\n              \
    \      std::min(up - result, reverse.cap)\n                );\n              \
    \  if (d == Cap(0)) continue;\n                e.cap += d;\n                reverse.cap\
    \ -= d;\n                result += d;\n                if (result == up) return\
    \ result;\n            }\n            level[v] = _n;\n            return result;\n\
    \        };\n\n        Cap flow = 0;\n        while (flow < flow_limit && bfs())\
    \ {\n            std::fill(iter, iter + _n, 0);\n            flow += dfs(dfs,\
    \ t, flow_limit - flow);\n        }\n        return flow;\n    }\n\n    std::vector<bool>\
    \ min_cut(int s) const {\n        assert(0 <= s && s < _n);\n        std::vector<bool>\
    \ visited(_n, false);\n        std::vector<int> queue(_n);\n        int head =\
    \ 0;\n        int tail = 0;\n        visited[s] = true;\n        queue[tail++]\
    \ = s;\n        while (head != tail) {\n            int v = queue[head++];\n \
    \           for (const auto& e : _g[v]) {\n                if (e.cap == Cap(0)\
    \ || visited[e.to]) continue;\n                visited[e.to] = true;\n       \
    \         queue[tail++] = e.to;\n            }\n        }\n        return visited;\n\
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FLOW_MAX_FLOW_HPP\n#define M1UNE_FLOW_MAX_FLOW_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cstddef>\n#include <limits>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct\
    \ MaxFlow {\n    struct Edge {\n        int from;\n        int to;\n        Cap\
    \ cap;\n        Cap flow;\n    };\n\n   private:\n    struct InternalEdge {\n\
    \        int to;\n        int rev;\n        Cap cap;\n    };\n\n    struct Position\
    \ {\n        int from;\n        int edge;\n    };\n\n    int _n;\n    std::vector<Position>\
    \ _pos;\n    std::vector<std::vector<InternalEdge>> _g;\n\n   public:\n    MaxFlow()\
    \ : MaxFlow(0) {}\n\n    explicit MaxFlow(int n) : _n(n), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    int\
    \ edge_count() const {\n        return int(_pos.size());\n    }\n\n    void reserve_edges(int\
    \ edge_count) {\n        assert(0 <= edge_count);\n        _pos.reserve(edge_count);\n\
    \        if (_n == 0 || edge_count == 0 ||\n            2 * std::size_t(edge_count)\
    \ < std::size_t(_n)) {\n            return;\n        }\n        const std::size_t\
    \ average_degree =\n            (2 * std::size_t(edge_count) + std::size_t(_n)\
    \ - 1)\n            / std::size_t(_n);\n        for (auto& edges : _g) edges.reserve(average_degree);\n\
    \    }\n\n    int add_edge(int from, int to, Cap cap) {\n        assert(0 <= from\
    \ && from < _n);\n        assert(0 <= to && to < _n);\n        assert(Cap(0) <=\
    \ cap);\n        int id = int(_pos.size());\n        int from_id = int(_g[from].size());\n\
    \        int to_id = int(_g[to].size());\n        if (from == to) to_id++;\n \
    \       _pos.push_back(Position{from, from_id});\n        _g[from].push_back(InternalEdge{to,\
    \ to_id, cap});\n        _g[to].push_back(InternalEdge{from, from_id, Cap(0)});\n\
    \        return id;\n    }\n\n    int add_undirected_edge(int first, int second,\
    \ Cap cap) {\n        static_assert(std::numeric_limits<Cap>::is_signed);\n  \
    \      assert(0 <= first && first < _n);\n        assert(0 <= second && second\
    \ < _n);\n        assert(Cap(0) <= cap);\n        assert(cap <= std::numeric_limits<Cap>::max()\
    \ / Cap(2));\n        int id = int(_pos.size());\n        int first_id = int(_g[first].size());\n\
    \        int second_id = int(_g[second].size());\n        if (first == second)\
    \ second_id++;\n        _pos.push_back(Position{first, ~first_id});\n        _g[first].push_back(InternalEdge{second,\
    \ second_id, cap});\n        _g[second].push_back(InternalEdge{first, first_id,\
    \ cap});\n        return id;\n    }\n\n    Edge get_edge(int i) const {\n    \
    \    assert(0 <= i && i < int(_pos.size()));\n        const auto& position = _pos[i];\n\
    \        int from = position.from;\n        bool undirected = position.edge <\
    \ 0;\n        int idx = undirected ? ~position.edge : position.edge;\n       \
    \ const auto& e = _g[from][idx];\n        const auto& re = _g[e.to][e.rev];\n\
    \        if (undirected) {\n            return Edge{\n                from,\n\
    \                e.to,\n                (e.cap + re.cap) / Cap(2),\n         \
    \       (re.cap - e.cap) / Cap(2)\n            };\n        }\n        return Edge{from,\
    \ e.to, e.cap + re.cap, re.cap};\n    }\n\n    std::vector<Edge> edges() const\
    \ {\n        std::vector<Edge> result;\n        result.reserve(_pos.size());\n\
    \        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));\n\
    \        return result;\n    }\n\n    void change_edge(int i, Cap new_cap, Cap\
    \ new_flow) {\n        assert(0 <= i && i < int(_pos.size()));\n        assert(Cap(0)\
    \ <= new_cap);\n        auto& position = _pos[i];\n        int from = position.from;\n\
    \        bool undirected = position.edge < 0;\n        int idx = undirected ?\
    \ ~position.edge : position.edge;\n        auto& e = _g[from][idx];\n        auto&\
    \ re = _g[e.to][e.rev];\n        if (undirected) {\n            assert(new_cap\
    \ <= std::numeric_limits<Cap>::max() / Cap(2));\n            assert(-new_cap <=\
    \ new_flow && new_flow <= new_cap);\n            e.cap = new_cap - new_flow;\n\
    \            re.cap = new_cap + new_flow;\n        } else {\n            assert(Cap(0)\
    \ <= new_flow && new_flow <= new_cap);\n            e.cap = new_cap - new_flow;\n\
    \            re.cap = new_flow;\n        }\n    }\n\n    Cap max_flow(int s, int\
    \ t) {\n        return max_flow(s, t, std::numeric_limits<Cap>::max());\n    }\n\
    \n    Cap max_flow(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s\
    \ < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\n     \
    \   std::vector<int> work(3 * std::size_t(_n));\n        int* level = work.data();\n\
    \        int* iter = level + _n;\n        int* queue = iter + _n;\n        auto\
    \ bfs = [&]() -> bool {\n            std::fill(level, level + _n, -1);\n     \
    \       int head = 0;\n            int tail = 0;\n            level[s] = 0;\n\
    \            queue[tail++] = s;\n            while (head != tail) {\n        \
    \        int v = queue[head++];\n                for (const auto& e : _g[v]) {\n\
    \                    if (e.cap == Cap(0) || level[e.to] != -1) continue;\n   \
    \                 level[e.to] = level[v] + 1;\n                    if (e.to ==\
    \ t) return true;\n                    queue[tail++] = e.to;\n               \
    \ }\n            }\n            return level[t] != -1;\n        };\n\n       \
    \ auto dfs = [&](auto&& self, int v, Cap up) -> Cap {\n            if (v == s)\
    \ return up;\n            Cap result = Cap(0);\n            const int current_level\
    \ = level[v];\n            for (int& i = iter[v]; i < int(_g[v].size()); i++)\
    \ {\n                auto& e = _g[v][i];\n                if (current_level <=\
    \ level[e.to]) continue;\n                auto& reverse = _g[e.to][e.rev];\n \
    \               if (reverse.cap == Cap(0)) continue;\n                Cap d =\
    \ self(\n                    self,\n                    e.to,\n              \
    \      std::min(up - result, reverse.cap)\n                );\n              \
    \  if (d == Cap(0)) continue;\n                e.cap += d;\n                reverse.cap\
    \ -= d;\n                result += d;\n                if (result == up) return\
    \ result;\n            }\n            level[v] = _n;\n            return result;\n\
    \        };\n\n        Cap flow = 0;\n        while (flow < flow_limit && bfs())\
    \ {\n            std::fill(iter, iter + _n, 0);\n            flow += dfs(dfs,\
    \ t, flow_limit - flow);\n        }\n        return flow;\n    }\n\n    std::vector<bool>\
    \ min_cut(int s) const {\n        assert(0 <= s && s < _n);\n        std::vector<bool>\
    \ visited(_n, false);\n        std::vector<int> queue(_n);\n        int head =\
    \ 0;\n        int tail = 0;\n        visited[s] = true;\n        queue[tail++]\
    \ = s;\n        while (head != tail) {\n            int v = queue[head++];\n \
    \           for (const auto& e : _g[v]) {\n                if (e.cap == Cap(0)\
    \ || visited[e.to]) continue;\n                visited[e.to] = true;\n       \
    \         queue[tail++] = e.to;\n            }\n        }\n        return visited;\n\
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n#endif  // M1UNE_FLOW_MAX_FLOW_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/flow/max_flow.hpp
  requiredBy:
  - optimization/project_selection.hpp
  - optimization/all.hpp
  - graph/all.hpp
  - graph/flow/flow.hpp
  - graph/flow/bounded_flow.hpp
  timestamp: '2026-07-15 21:34:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/optimization/project_selection.test.cpp
  - verify/optimization/integer_lp.test.cpp
  - verify/optimization/simplex.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/flow/flow_algorithms.test.cpp
  - verify/graph/flow/max_flow.test.cpp
documentation_of: graph/flow/max_flow.hpp
layout: document
title: Max Flow
---

## Overview

`MaxFlow<Cap>` computes the maximum amount of flow that can be sent from a
source vertex `s` to a sink vertex `t` in a directed capacitated graph.

This implementation uses a constant-factor optimized Dinic algorithm. It
repeatedly builds a level graph with an array queue and sends blocking flow by
traversing the level graph backward from the sink. Dead-end pruning and
current-edge pointers avoid revisiting exhausted vertices and edges.

## Graph Orientation

Directed flow network. An edge added by `add_edge(from, to, cap)` can send flow
only from `from` to `to`.

For a bidirectional edge with one shared capacity, use
`add_undirected_edge(first, second, cap)`. It stores only two residual edges,
half as many as two calls to `add_edge`. This is the intended interface for
SPOJ FASTFLOW-style pipe networks.

The graph is stateful. Running `max_flow` changes residual capacities and
stores the resulting flow. Use `get_edge` or `edges` after running it to inspect
how much flow passed through each original edge.

## How to Use It

Create `MaxFlow<Cap> mf(n)`, add directed edges with capacities, and call
`mf.max_flow(s, t)`.

Capacities must be non-negative. `add_undirected_edge` requires a signed `Cap`;
its residual capacity may reach `2 * cap`, which must also fit `Cap`.

When the edge count is known, call `reserve_edges(m)` before adding edges. In
addition to reserving edge metadata, it reserves the average residual degree
for every vertex when the graph is dense enough for that to be useful. This
avoids most small adjacency-list allocations without allocating one buffer per
vertex on extremely sparse graphs.

You can call `max_flow(s, t, flow_limit)` when only up to `flow_limit` units are
needed.

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Original edge source. |
| `to` | `int` | Original edge destination. |
| `cap` | `Cap` | Original capacity currently assigned to this edge. |
| `flow` | `Cap` | Flow from `from` to `to`; it may be negative for an undirected edge. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `MaxFlow()` | Creates an empty flow graph. | $O(1)$ |
| Constructor | `explicit MaxFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of original edges. | $O(1)$ |
| `reserve_edges` | `void reserve_edges(int edge_count)` | Reserves edge metadata and average adjacency capacity. | $O(N + M)$ when reallocation occurs |
| `add_edge` | `int add_edge(int from, int to, Cap cap)` | Adds a directed edge and returns its edge id. | Amortized $O(1)$ |
| `add_undirected_edge` | `int add_undirected_edge(int first, int second, Cap cap)` | Adds a bidirectional edge with shared capacity and returns its id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int i) const` | Returns the current state of original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges with current flow. | $O(M)$ |
| `change_edge` | `void change_edge(int i, Cap new_cap, Cap new_flow)` | Replaces edge `i`'s capacity and current flow; undirected flow may be negative. | $O(1)$ |
| `max_flow` | `Cap max_flow(int s, int t)` | Sends maximum flow from `s` to `t`. | $O(N^2 M)$ in general; see below |
| `max_flow` | `Cap max_flow(int s, int t, Cap flow_limit)` | Sends at most `flow_limit` additional flow. | $O(N^2 M)$ in general; see below |
| `min_cut` | `std::vector<bool> min_cut(int s) const` | Returns vertices reachable from `s` in the residual graph. | $O(N + M)$ |

## Time Complexity of `max_flow`

Here, $N$ is the number of vertices and $M$ is the number of original edges.
The residual graph stores two directed residual edges for each original edge,
including an edge added by `add_undirected_edge`.

Dinic's algorithm works in phases. Each phase first uses BFS to construct a
level graph in $O(N + M)$ time, then uses DFS with current-edge pointers to
find a blocking flow. A blocking-flow computation takes $O(NM)$ time in the
general case. After a blocking flow is found, the shortest residual distance
from `s` to `t` strictly increases, so there are fewer than $N$ phases. This
gives the general bound

$$
O(N^2 M).
$$

This bound counts each `Cap` arithmetic or comparison operation as $O(1)$ and
does not depend on the numerical size of the capacities.

### Bounds for Integer Capacities

When every capacity is an integer, several additional bounds hold for this
current-edge implementation. Let $u_e$ be the capacity of edge $e$, and define

$$
\bar{u} = \frac{1}{M}\sum_e u_e,
\qquad
U = \max_e u_e,
$$

and

$$
\bar{c} = \frac{1}{N}\sum_v
\min\left(\sum_{e\text{ enters }v}u_e,
          \sum_{e\text{ leaves }v}u_e\right).
$$

If $F$ is the amount of flow still sendable from `s` to `t` in the current
residual graph, the following are alternative upper bounds:

| Condition | Complexity |
| --- | --- |
| Integer capacities | $O(FM)$ |
| Average edge capacity $\bar{u}$ | $O(\bar{u}M^{3/2})$ |
| Maximum edge capacity $U$, with no parallel edges | $O(UN^{2/3}M)$ |
| Average vertex throughput $\bar{c}$ as defined above | $O(\bar{c}\sqrt{N}M)$ |

These bounds hold at the same time as the general $O(N^2M)$ bound, so use the
smallest applicable one. As usual, zero-capacity edges and isolated vertices
can be omitted when applying the specialized bounds; if they are retained,
include the $O(N+M)$ initialization and scanning cost.

The $O(FM)$ bound follows because each successful augmentation increases an
integer flow by at least one. The other bounds combine this observation with a
small residual cut after sufficiently many level-graph phases.

If every residual capacity at the start of a call has greatest common divisor
$g$, divide the capacity-dependent quantities $F$, $\bar{u}$, $U$, and
$\bar{c}$ by $g$ in these bounds. When using `flow_limit`, it must be scaled as
well. Scaling all these values by $g$ does not change which paths and edges
Dinic's algorithm processes.

For unit-capacity graphs, $\bar{u}=U=1$. Combining the two edge-capacity bounds
gives the standard result

$$
O\left(M \min\left(N^{2/3}, \sqrt{M}\right)\right).
$$

On unit networks, where every non-terminal vertex has either one incoming edge
or one outgoing edge, $\bar{c}=O(1)$ and the bound improves further to
$O(M\sqrt{N})$. Bipartite matching networks are a common example.

For a detailed derivation of these bounds, see
[Dinic's Algorithm and Its Time Complexity](https://misawa.github.io/others/flow/dinic_time_complexity.html).

The `flow_limit` overload may stop before a complete maximum flow is found, so
it can be faster in practice, but its general worst-case bound remains
$O(N^2 M)$. With integer capacities, let $F_{call}$ be the amount returned by
the call. Its flow-dependent work is $O(F_{call}M)$, and the exact bound
including initialization and a final unsuccessful search is
$O(N+(F_{call}+1)M)$. Here, $F_{call}$ is at most `flow_limit`. Every call
returns only the **additional** flow sent during that call. Since the residual
graph is preserved, calling `max_flow` again continues from the current flow
rather than recomputing it from scratch.

## Minimum Cut

After running max flow, `min_cut(s)` returns the source side of a minimum
`s-t` cut. An original edge crossing from `cut[u] == true` to
`cut[v] == false` is saturated and belongs to some minimum cut boundary.

## Example

```cpp
#include "graph/flow/max_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::MaxFlow<long long> mf(4);
    mf.reserve_edges(5);
    mf.add_edge(0, 1, 2);
    mf.add_edge(0, 2, 1);
    mf.add_edge(1, 2, 1);
    mf.add_edge(1, 3, 1);
    mf.add_edge(2, 3, 2);

    std::cout << mf.max_flow(0, 3) << "\n";  // 3

    for (const auto& e : mf.edges()) {
        std::cout << e.from << " -> " << e.to << ": " << e.flow << "/" << e.cap << "\n";
    }
}
```
