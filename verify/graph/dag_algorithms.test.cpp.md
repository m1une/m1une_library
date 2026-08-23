---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bipartite.hpp
    title: Bipartite Graph
  - icon: ':heavy_check_mark:'
    path: graph/dag.hpp
    title: DAG Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/dag_longest_path.hpp
    title: DAG Longest Path
  - icon: ':heavy_check_mark:'
    path: graph/dag_path_count.hpp
    title: DAG Path Count
  - icon: ':heavy_check_mark:'
    path: graph/dag_path_cover.hpp
    title: Minimum DAG Path Cover
  - icon: ':heavy_check_mark:'
    path: graph/dag_reachability.hpp
    title: DAG Reachability and Transitive Reduction
  - icon: ':heavy_check_mark:'
    path: graph/dag_shortest_path.hpp
    title: DAG Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  - icon: ':heavy_check_mark:'
    path: utilities/dynamic_bitset.hpp
    title: Dynamic Bitset
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A
  bundledCode: "#line 1 \"verify/graph/dag_algorithms.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <iostream>\n#include <limits>\n\
    #include <random>\n#include <vector>\n\n#line 1 \"graph/dag.hpp\"\n\n\n\n#line\
    \ 1 \"graph/dag_longest_path.hpp\"\n\n\n\n#line 7 \"graph/dag_longest_path.hpp\"\
    \n#include <optional>\n#line 9 \"graph/dag_longest_path.hpp\"\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#include <array>\n#line 6 \"graph/graph.hpp\"\n#include <utility>\n#line\
    \ 8 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
    \ T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int\
    \ to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1),\
    \ cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1),\
    \ int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    struct EdgePositions {\n        std::array<std::pair<int,\
    \ int>, 2> value{};\n        int size = 0;\n\n        void push_back(std::pair<int,\
    \ int> position) {\n            assert(size < 2);\n            value[size++] =\
    \ position;\n        }\n    };\n\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
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
    \ graph\n}  // namespace m1une\n\n\n#line 12 \"graph/dag_longest_path.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DagLongestPathResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> topological_order;\n    T neg_inf;\n\n  \
    \  bool reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != neg_inf;\n    }\n\n    std::vector<int> path(int t)\
    \ const {\n        assert(reachable(t));\n        std::vector<int> result;\n \
    \       for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n       \
    \ std::reverse(result.begin(), result.end());\n        return result;\n    }\n\
    };\n\ntemplate <class T>\nstd::optional<DagLongestPathResult<T>> dag_longest_path(\n\
    \    const Graph<T>& g,\n    const std::vector<int>& sources,\n    T neg_inf =\
    \ std::numeric_limits<T>::lowest() / T(4)\n) {\n    const int n = g.size();\n\
    \    auto order = topological_sort(g);\n    if (!order) return std::nullopt;\n\
    \n    DagLongestPathResult<T> result;\n    result.dist.assign(n, neg_inf);\n \
    \   result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n    result.topological_order\
    \ = *order;\n    result.neg_inf = neg_inf;\n\n    for (int s : sources) {\n  \
    \      assert(0 <= s && s < n);\n        result.dist[s] = T(0);\n    }\n\n   \
    \ for (int v : *order) {\n        if (result.dist[v] == neg_inf) continue;\n \
    \       for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n  \
    \          T nd = result.dist[v] + e.cost;\n            if (result.dist[e.to]\
    \ >= nd) continue;\n            result.dist[e.to] = nd;\n            result.parent[e.to]\
    \ = v;\n            result.parent_edge[e.to] = e.id;\n        }\n    }\n\n   \
    \ return result;\n}\n\ntemplate <class T>\nstd::optional<DagLongestPathResult<T>>\
    \ dag_longest_path(\n    const Graph<T>& g,\n    int s,\n    T neg_inf = std::numeric_limits<T>::lowest()\
    \ / T(4)\n) {\n    return dag_longest_path(g, std::vector<int>{s}, neg_inf);\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/dag_path_count.hpp\"\
    \n\n\n\n#line 7 \"graph/dag_path_count.hpp\"\n\n#line 10 \"graph/dag_path_count.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class Count = long long,\
    \ class T>\nstd::optional<std::vector<Count>> dag_path_count(\n    const Graph<T>&\
    \ g,\n    const std::vector<int>& sources\n) {\n    const int n = g.size();\n\
    \    auto order = topological_sort(g);\n    if (!order) return std::nullopt;\n\
    \n    std::vector<Count> ways(n, Count(0));\n    std::vector<char> used_source(n,\
    \ false);\n    for (int s : sources) {\n        assert(0 <= s && s < n);\n   \
    \     if (used_source[s]) continue;\n        used_source[s] = true;\n        ways[s]\
    \ += Count(1);\n    }\n\n    for (int v : *order) {\n        for (const auto&\
    \ e : g[v]) {\n            if (e.alive) ways[e.to] += ways[v];\n        }\n  \
    \  }\n    return ways;\n}\n\ntemplate <class Count = long long, class T>\nstd::optional<std::vector<Count>>\
    \ dag_path_count(const Graph<T>& g, int s) {\n    return dag_path_count<Count>(g,\
    \ std::vector<int>{s});\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\
    \n#line 1 \"graph/dag_path_cover.hpp\"\n\n\n\n#line 7 \"graph/dag_path_cover.hpp\"\
    \n\n#line 1 \"graph/bipartite.hpp\"\n\n\n\n#line 6 \"graph/bipartite.hpp\"\n#include\
    \ <cstddef>\n#include <cstdint>\n#line 13 \"graph/bipartite.hpp\"\n\n#line 15\
    \ \"graph/bipartite.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct BipartiteResult\
    \ {\n    bool is_bipartite;\n    std::vector<int> color;\n    std::vector<int>\
    \ left_vertices;\n    std::vector<int> right_vertices;\n    std::vector<int> left_id;\n\
    \    std::vector<int> right_id;\n};\n\ntemplate <class T>\nBipartiteResult bipartite(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    BipartiteResult result;\n    result.is_bipartite\
    \ = true;\n    result.color.assign(n, -1);\n    result.left_id.assign(n, -1);\n\
    \    result.right_id.assign(n, -1);\n\n    std::vector<std::vector<int>> adjacency(n);\n\
    \    for (const auto& e : g.edges()) {\n        adjacency[e.from].push_back(e.to);\n\
    \        adjacency[e.to].push_back(e.from);\n    }\n\n    std::queue<int> que;\n\
    \    for (int s = 0; s < n; s++) {\n        if (result.color[s] != -1) continue;\n\
    \        result.color[s] = 0;\n        que.push(s);\n        while (!que.empty())\
    \ {\n            int v = que.front();\n            que.pop();\n            for\
    \ (int to : adjacency[v]) {\n                if (result.color[to] == -1) {\n \
    \                   result.color[to] = result.color[v] ^ 1;\n                \
    \    que.push(to);\n                } else if (result.color[to] == result.color[v])\
    \ {\n                    result.is_bipartite = false;\n                    return\
    \ result;\n                }\n            }\n        }\n    }\n\n    for (int\
    \ v = 0; v < n; v++) {\n        if (result.color[v] == 0) {\n            result.left_id[v]\
    \ = int(result.left_vertices.size());\n            result.left_vertices.push_back(v);\n\
    \        } else {\n            result.right_id[v] = int(result.right_vertices.size());\n\
    \            result.right_vertices.push_back(v);\n        }\n    }\n\n    return\
    \ result;\n}\n\ntemplate <class T>\nbool is_bipartite(const Graph<T>& g) {\n \
    \   return bipartite(g).is_bipartite;\n}\n\nstruct BipartiteVertexSet {\n    std::vector<int>\
    \ left;\n    std::vector<int> right;\n\n    int size() const {\n        return\
    \ int(left.size() + right.size());\n    }\n};\n\nstruct BipartiteMatching {\n\
    \    struct Edge {\n        int left;\n        int right;\n        int id;\n \
    \       bool alive;\n    };\n\n    struct Pair {\n        int left;\n        int\
    \ right;\n        int edge_id;\n    };\n\n   private:\n    int _left_size;\n \
    \   int _right_size;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
    \ _adj;\n    std::vector<std::vector<int>> _radj;\n    std::vector<int> _left_match;\n\
    \    std::vector<int> _right_match;\n    std::vector<int> _left_match_edge;\n\
    \    std::vector<int> _right_match_edge;\n    bool _calculated;\n\n    void invalidate()\
    \ {\n        _calculated = false;\n    }\n\n    void ensure_matching() {\n   \
    \     if (!_calculated) max_matching();\n    }\n\n   public:\n    BipartiteMatching()\
    \ : BipartiteMatching(0, 0) {}\n\n    BipartiteMatching(int left_size, int right_size)\n\
    \        : _left_size(left_size),\n          _right_size(right_size),\n      \
    \    _adj(left_size),\n          _radj(right_size),\n          _left_match(left_size,\
    \ -1),\n          _right_match(right_size, -1),\n          _left_match_edge(left_size,\
    \ -1),\n          _right_match_edge(right_size, -1),\n          _calculated(false)\
    \ {\n        assert(0 <= left_size);\n        assert(0 <= right_size);\n    }\n\
    \n    int left_size() const {\n        return _left_size;\n    }\n\n    int right_size()\
    \ const {\n        return _right_size;\n    }\n\n    int edge_count() const {\n\
    \        return int(_edges.size());\n    }\n\n    int add_edge(int left, int right)\
    \ {\n        assert(0 <= left && left < _left_size);\n        assert(0 <= right\
    \ && right < _right_size);\n        int id = int(_edges.size());\n        _edges.push_back(Edge{left,\
    \ right, id, true});\n        _adj[left].push_back(id);\n        _radj[right].push_back(id);\n\
    \        invalidate();\n        return id;\n    }\n\n    Edge get_edge(int i)\
    \ const {\n        assert(0 <= i && i < int(_edges.size()));\n        return _edges[i];\n\
    \    }\n\n    std::vector<Edge> edges(bool include_inactive = false) const {\n\
    \        std::vector<Edge> result;\n        result.reserve(_edges.size());\n \
    \       for (const auto& e : _edges) {\n            if (include_inactive || e.alive)\
    \ result.push_back(e);\n        }\n        return result;\n    }\n\n    void set_edge_alive(int\
    \ id, bool alive) {\n        assert(0 <= id && id < int(_edges.size()));\n   \
    \     _edges[id].alive = alive;\n        invalidate();\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < int(_edges.size()));\n        return\
    \ _edges[id].alive;\n    }\n\n    int max_matching() {\n        _left_match.assign(_left_size,\
    \ -1);\n        _right_match.assign(_right_size, -1);\n        _left_match_edge.assign(_left_size,\
    \ -1);\n        _right_match_edge.assign(_right_size, -1);\n\n        std::vector<int>\
    \ dist(_left_size);\n        auto bfs = [&]() -> bool {\n            std::queue<int>\
    \ que;\n            bool found = false;\n            for (int l = 0; l < _left_size;\
    \ l++) {\n                if (_left_match[l] == -1) {\n                    dist[l]\
    \ = 0;\n                    que.push(l);\n                } else {\n         \
    \           dist[l] = -1;\n                }\n            }\n\n            while\
    \ (!que.empty()) {\n                int l = que.front();\n                que.pop();\n\
    \                for (int id : _adj[l]) {\n                    const auto& e =\
    \ _edges[id];\n                    if (!e.alive) continue;\n                 \
    \   int next_left = _right_match[e.right];\n                    if (next_left\
    \ == -1) {\n                        found = true;\n                    } else\
    \ if (dist[next_left] == -1) {\n                        dist[next_left] = dist[l]\
    \ + 1;\n                        que.push(next_left);\n                    }\n\
    \                }\n            }\n            return found;\n        };\n\n \
    \       auto dfs = [&](auto self, int l) -> bool {\n            for (int id :\
    \ _adj[l]) {\n                const auto& e = _edges[id];\n                if\
    \ (!e.alive) continue;\n                int next_left = _right_match[e.right];\n\
    \                if (next_left != -1 && (dist[next_left] != dist[l] + 1 || !self(self,\
    \ next_left))) {\n                    continue;\n                }\n         \
    \       _left_match[l] = e.right;\n                _right_match[e.right] = l;\n\
    \                _left_match_edge[l] = id;\n                _right_match_edge[e.right]\
    \ = id;\n                return true;\n            }\n            dist[l] = -1;\n\
    \            return false;\n        };\n\n        int result = 0;\n        while\
    \ (bfs()) {\n            for (int l = 0; l < _left_size; l++) {\n            \
    \    if (_left_match[l] == -1 && dfs(dfs, l)) result++;\n            }\n     \
    \   }\n\n        _calculated = true;\n        return result;\n    }\n\n    int\
    \ matching_size() {\n        ensure_matching();\n        int result = 0;\n   \
    \     for (int right : _left_match) {\n            if (right != -1) result++;\n\
    \        }\n        return result;\n    }\n\n    std::vector<int> left_match()\
    \ {\n        ensure_matching();\n        return _left_match;\n    }\n\n    std::vector<int>\
    \ right_match() {\n        ensure_matching();\n        return _right_match;\n\
    \    }\n\n    std::vector<Pair> matching() {\n        ensure_matching();\n   \
    \     std::vector<Pair> result;\n        for (int l = 0; l < _left_size; l++)\
    \ {\n            if (_left_match[l] != -1) result.push_back(Pair{l, _left_match[l],\
    \ _left_match_edge[l]});\n        }\n        return result;\n    }\n\n    BipartiteVertexSet\
    \ minimum_vertex_cover() {\n        ensure_matching();\n\n        std::vector<char>\
    \ visited_left(_left_size, false), visited_right(_right_size, false);\n      \
    \  std::queue<int> que;\n        for (int l = 0; l < _left_size; l++) {\n    \
    \        if (_left_match[l] == -1) {\n                visited_left[l] = true;\n\
    \                que.push(l);\n            }\n        }\n\n        while (!que.empty())\
    \ {\n            int l = que.front();\n            que.pop();\n            for\
    \ (int id : _adj[l]) {\n                const auto& e = _edges[id];\n        \
    \        if (!e.alive || _left_match_edge[l] == id || visited_right[e.right])\
    \ continue;\n                visited_right[e.right] = true;\n                int\
    \ next_left = _right_match[e.right];\n                if (next_left != -1 && !visited_left[next_left])\
    \ {\n                    visited_left[next_left] = true;\n                   \
    \ que.push(next_left);\n                }\n            }\n        }\n\n      \
    \  BipartiteVertexSet result;\n        for (int l = 0; l < _left_size; l++) {\n\
    \            if (!visited_left[l]) result.left.push_back(l);\n        }\n    \
    \    for (int r = 0; r < _right_size; r++) {\n            if (visited_right[r])\
    \ result.right.push_back(r);\n        }\n        return result;\n    }\n\n   \
    \ BipartiteVertexSet maximum_independent_set() {\n        auto cover = minimum_vertex_cover();\n\
    \        std::vector<char> in_left_cover(_left_size, false), in_right_cover(_right_size,\
    \ false);\n        for (int l : cover.left) in_left_cover[l] = true;\n       \
    \ for (int r : cover.right) in_right_cover[r] = true;\n\n        BipartiteVertexSet\
    \ result;\n        for (int l = 0; l < _left_size; l++) {\n            if (!in_left_cover[l])\
    \ result.left.push_back(l);\n        }\n        for (int r = 0; r < _right_size;\
    \ r++) {\n            if (!in_right_cover[r]) result.right.push_back(r);\n   \
    \     }\n        return result;\n    }\n\n    std::optional<std::vector<int>>\
    \ minimum_edge_cover() {\n        ensure_matching();\n\n        std::vector<int>\
    \ result;\n        std::vector<char> covered_left(_left_size, false), covered_right(_right_size,\
    \ false);\n        std::vector<char> used_edge(_edges.size(), false);\n\n    \
    \    auto use_edge = [&](int id) {\n            if (used_edge[id]) return;\n \
    \           used_edge[id] = true;\n            result.push_back(id);\n       \
    \     covered_left[_edges[id].left] = true;\n            covered_right[_edges[id].right]\
    \ = true;\n        };\n\n        for (int l = 0; l < _left_size; l++) {\n    \
    \        if (_left_match_edge[l] != -1) use_edge(_left_match_edge[l]);\n     \
    \   }\n\n        for (int l = 0; l < _left_size; l++) {\n            if (covered_left[l])\
    \ continue;\n            int id = -1;\n            for (int edge_id : _adj[l])\
    \ {\n                if (_edges[edge_id].alive) {\n                    id = edge_id;\n\
    \                    break;\n                }\n            }\n            if\
    \ (id == -1) return std::nullopt;\n            use_edge(id);\n        }\n\n  \
    \      for (int r = 0; r < _right_size; r++) {\n            if (covered_right[r])\
    \ continue;\n            int id = -1;\n            for (int edge_id : _radj[r])\
    \ {\n                if (_edges[edge_id].alive) {\n                    id = edge_id;\n\
    \                    break;\n                }\n            }\n            if\
    \ (id == -1) return std::nullopt;\n            use_edge(id);\n        }\n\n  \
    \      return result;\n    }\n};\n\nstruct BipartiteMatchingGraph {\n    BipartiteResult\
    \ parts;\n    BipartiteMatching matching;\n    std::vector<int> original_edge_id;\n\
    \n    int left_vertex(int left) const {\n        assert(0 <= left && left < int(parts.left_vertices.size()));\n\
    \        return parts.left_vertices[left];\n    }\n\n    int right_vertex(int\
    \ right) const {\n        assert(0 <= right && right < int(parts.right_vertices.size()));\n\
    \        return parts.right_vertices[right];\n    }\n\n    int original_edge(int\
    \ edge_id) const {\n        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));\n\
    \        return original_edge_id[edge_id];\n    }\n};\n\ntemplate <class T>\n\
    std::optional<BipartiteMatchingGraph> make_bipartite_matching(const Graph<T>&\
    \ g) {\n    auto parts = bipartite(g);\n    if (!parts.is_bipartite) return std::nullopt;\n\
    \n    BipartiteMatchingGraph result;\n    result.parts = parts;\n    result.matching\
    \ = BipartiteMatching(int(parts.left_vertices.size()), int(parts.right_vertices.size()));\n\
    \n    for (const auto& e : g.edges()) {\n        int left, right;\n        if\
    \ (parts.color[e.from] == 0) {\n            left = parts.left_id[e.from];\n  \
    \          right = parts.right_id[e.to];\n        } else {\n            left =\
    \ parts.left_id[e.to];\n            right = parts.right_id[e.from];\n        }\n\
    \        int id = result.matching.add_edge(left, right);\n        if (int(result.original_edge_id.size())\
    \ <= id) result.original_edge_id.resize(id + 1);\n        result.original_edge_id[id]\
    \ = e.id;\n    }\n\n    return result;\n}\n\nstruct BipartiteEdgeColoringResult\
    \ {\n    int color_count;\n    std::vector<int> color;\n};\n\nnamespace detail\
    \ {\n\nstruct BipartiteEdgeColoringGroups {\n    int count;\n    std::vector<int>\
    \ group;\n};\n\ninline BipartiteEdgeColoringGroups group_vertices(\n    const\
    \ std::vector<int>& degree,\n    int maximum_degree\n) {\n    BipartiteEdgeColoringGroups\
    \ result;\n    result.count = 0;\n    result.group.assign(degree.size(), -1);\n\
    \    int current_degree = 0;\n    for (int vertex = 0; vertex < int(degree.size());\
    \ vertex++) {\n        if (degree[vertex] == 0) continue;\n        if (result.count\
    \ == 0 || current_degree + degree[vertex] > maximum_degree) {\n            result.count++;\n\
    \            current_degree = 0;\n        }\n        result.group[vertex] = result.count\
    \ - 1;\n        current_degree += degree[vertex];\n    }\n    return result;\n\
    }\n\nclass BipartiteEdgeColoringSolver {\n   private:\n    int _side_size;\n \
    \   int _original_edge_count;\n    std::vector<int> _left;\n    std::vector<int>\
    \ _right;\n    std::vector<int> _color;\n    std::vector<int> _used_stamp;\n \
    \   int _stamp;\n\n    int other_endpoint(int vertex, int edge) const {\n    \
    \    if (vertex < _side_size) return _side_size + _right[edge];\n        return\
    \ _left[edge];\n    }\n\n    std::vector<int> perfect_matching(const std::vector<int>&\
    \ edge_ids) const {\n        std::vector<std::vector<int>> adjacency(_side_size);\n\
    \        for (int edge : edge_ids) adjacency[_left[edge]].push_back(edge);\n\n\
    \        std::vector<int> right_match(_side_size, -1);\n        std::vector<int>\
    \ left_match_edge(_side_size, -1);\n        int matching_size = 0;\n        for\
    \ (int left = 0; left < _side_size; left++) {\n            for (int edge : adjacency[left])\
    \ {\n                int right = _right[edge];\n                if (right_match[right]\
    \ != -1) continue;\n                right_match[right] = left;\n             \
    \   left_match_edge[left] = edge;\n                matching_size++;\n        \
    \        break;\n            }\n        }\n\n        std::vector<int> distance(_side_size);\n\
    \        std::vector<int> next_edge(_side_size);\n        std::vector<int> left_stack;\n\
    \        std::vector<int> path_edges;\n        left_stack.reserve(_side_size);\n\
    \        path_edges.reserve(_side_size);\n\n        while (matching_size < _side_size)\
    \ {\n            std::queue<int> queue;\n            std::fill(distance.begin(),\
    \ distance.end(), -1);\n            for (int left = 0; left < _side_size; left++)\
    \ {\n                if (left_match_edge[left] != -1) continue;\n            \
    \    distance[left] = 0;\n                queue.push(left);\n            }\n\n\
    \            bool reachable_free_right = false;\n            while (!queue.empty())\
    \ {\n                int left = queue.front();\n                queue.pop();\n\
    \                for (int edge : adjacency[left]) {\n                    int next_left\
    \ = right_match[_right[edge]];\n                    if (next_left == -1) {\n \
    \                       reachable_free_right = true;\n                    } else\
    \ if (distance[next_left] == -1) {\n                        distance[next_left]\
    \ = distance[left] + 1;\n                        queue.push(next_left);\n    \
    \                }\n                }\n            }\n            assert(reachable_free_right);\n\
    \n            std::fill(next_edge.begin(), next_edge.end(), 0);\n            int\
    \ augmented = 0;\n            for (int root = 0; root < _side_size; root++) {\n\
    \                if (left_match_edge[root] != -1 || distance[root] == -1) continue;\n\
    \                left_stack.clear();\n                path_edges.clear();\n  \
    \              left_stack.push_back(root);\n                bool found = false;\n\
    \n                while (!left_stack.empty() && !found) {\n                  \
    \  int left = left_stack.back();\n                    bool advanced = false;\n\
    \                    while (next_edge[left] < int(adjacency[left].size())) {\n\
    \                        int edge = adjacency[left][next_edge[left]++];\n    \
    \                    int right = _right[edge];\n                        int next_left\
    \ = right_match[right];\n                        if (next_left == -1) {\n    \
    \                        left_match_edge[left] = edge;\n                     \
    \       right_match[right] = left;\n                            for (int index\
    \ = int(path_edges.size()) - 1; index >= 0; index--) {\n                     \
    \           int path_edge = path_edges[index];\n                             \
    \   int path_left = left_stack[index];\n                                left_match_edge[path_left]\
    \ = path_edge;\n                                right_match[_right[path_edge]]\
    \ = path_left;\n                            }\n                            found\
    \ = true;\n                            break;\n                        }\n   \
    \                     if (distance[next_left] != distance[left] + 1) continue;\n\
    \                        path_edges.push_back(edge);\n                       \
    \ left_stack.push_back(next_left);\n                        advanced = true;\n\
    \                        break;\n                    }\n                    if\
    \ (found || advanced) continue;\n                    distance[left] = -1;\n  \
    \                  left_stack.pop_back();\n                    if (path_edges.size()\
    \ == left_stack.size() && !path_edges.empty()) {\n                        path_edges.pop_back();\n\
    \                    }\n                }\n                if (found) augmented++;\n\
    \            }\n            assert(augmented > 0);\n            matching_size\
    \ += augmented;\n        }\n\n        return left_match_edge;\n    }\n\n    std::pair<std::vector<int>,\
    \ std::vector<int>> split_even(\n        const std::vector<int>& edge_ids\n  \
    \  ) {\n        std::vector<std::vector<int>> incidence(std::size_t(2) * _side_size);\n\
    \        for (int edge : edge_ids) {\n            incidence[_left[edge]].push_back(edge);\n\
    \            incidence[_side_size + _right[edge]].push_back(edge);\n        }\n\
    \n        _stamp++;\n        assert(_stamp > 0);\n        std::vector<int> next_edge(std::size_t(2)\
    \ * _side_size, 0);\n        std::vector<int> first;\n        std::vector<int>\
    \ second;\n        first.reserve(edge_ids.size() / 2);\n        second.reserve(edge_ids.size()\
    \ / 2);\n\n        for (int start = 0; start < 2 * _side_size; start++) {\n  \
    \          while (true) {\n                while (next_edge[start] < int(incidence[start].size())\
    \ &&\n                       _used_stamp[incidence[start][next_edge[start]]] ==\
    \ _stamp) {\n                    next_edge[start]++;\n                }\n    \
    \            if (next_edge[start] == int(incidence[start].size())) break;\n\n\
    \                int vertex = start;\n                bool parity = false;\n \
    \               do {\n                    while (next_edge[vertex] < int(incidence[vertex].size())\
    \ &&\n                           _used_stamp[incidence[vertex][next_edge[vertex]]]\
    \ == _stamp) {\n                        next_edge[vertex]++;\n               \
    \     }\n                    assert(next_edge[vertex] < int(incidence[vertex].size()));\n\
    \                    int edge = incidence[vertex][next_edge[vertex]++];\n    \
    \                _used_stamp[edge] = _stamp;\n                    if (!parity)\
    \ {\n                        first.push_back(edge);\n                    } else\
    \ {\n                        second.push_back(edge);\n                    }\n\
    \                    parity = !parity;\n                    vertex = other_endpoint(vertex,\
    \ edge);\n                } while (vertex != start);\n                assert(!parity);\n\
    \            }\n        }\n        assert(first.size() == second.size());\n  \
    \      return {std::move(first), std::move(second)};\n    }\n\n    void color_regular(const\
    \ std::vector<int>& edge_ids, int degree, int offset) {\n        assert(std::size_t(_side_size)\
    \ * std::size_t(degree) == edge_ids.size());\n        if (degree == 0) return;\n\
    \        if (degree == 1) {\n            for (int edge : edge_ids) {\n       \
    \         if (edge < _original_edge_count) _color[edge] = offset;\n          \
    \  }\n            return;\n        }\n\n        if (degree % 2 == 1) {\n     \
    \       std::vector<int> matching = perfect_matching(edge_ids);\n            _stamp++;\n\
    \            assert(_stamp > 0);\n            for (int edge : matching) {\n  \
    \              _used_stamp[edge] = _stamp;\n                if (edge < _original_edge_count)\
    \ _color[edge] = offset;\n            }\n            std::vector<int> remaining;\n\
    \            remaining.reserve(edge_ids.size() - matching.size());\n         \
    \   for (int edge : edge_ids) {\n                if (_used_stamp[edge] != _stamp)\
    \ remaining.push_back(edge);\n            }\n            color_regular(remaining,\
    \ degree - 1, offset + 1);\n            return;\n        }\n\n        auto [first,\
    \ second] = split_even(edge_ids);\n        color_regular(first, degree / 2, offset);\n\
    \        color_regular(second, degree / 2, offset + degree / 2);\n    }\n\n  \
    \ public:\n    BipartiteEdgeColoringSolver(\n        int side_size,\n        int\
    \ original_edge_count,\n        std::vector<int> left,\n        std::vector<int>\
    \ right\n    )\n        : _side_size(side_size),\n          _original_edge_count(original_edge_count),\n\
    \          _left(std::move(left)),\n          _right(std::move(right)),\n    \
    \      _color(original_edge_count, -1),\n          _used_stamp(_left.size(), 0),\n\
    \          _stamp(0) {}\n\n    std::vector<int> solve(int degree) {\n        std::vector<int>\
    \ edge_ids(_left.size());\n        for (int edge = 0; edge < int(edge_ids.size());\
    \ edge++) edge_ids[edge] = edge;\n        color_regular(edge_ids, degree, 0);\n\
    \        for (int color : _color) assert(0 <= color && color < degree);\n    \
    \    return _color;\n    }\n};\n\n}  // namespace detail\n\n// Returns an optimal\
    \ edge coloring of a bipartite multigraph.\ninline BipartiteEdgeColoringResult\
    \ bipartite_edge_coloring(\n    int left_size,\n    int right_size,\n    const\
    \ std::vector<std::pair<int, int>>& edges\n) {\n    assert(left_size >= 0);\n\
    \    assert(right_size >= 0);\n    assert(edges.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n    std::vector<int> left_degree(left_size, 0);\n    std::vector<int> right_degree(right_size,\
    \ 0);\n    int maximum_degree = 0;\n    for (auto [left, right] : edges) {\n \
    \       assert(0 <= left && left < left_size);\n        assert(0 <= right && right\
    \ < right_size);\n        left_degree[left]++;\n        right_degree[right]++;\n\
    \        maximum_degree = std::max(maximum_degree, left_degree[left]);\n     \
    \   maximum_degree = std::max(maximum_degree, right_degree[right]);\n    }\n\n\
    \    BipartiteEdgeColoringResult result;\n    result.color_count = maximum_degree;\n\
    \    if (edges.empty()) return result;\n\n    detail::BipartiteEdgeColoringGroups\
    \ left_groups =\n        detail::group_vertices(left_degree, maximum_degree);\n\
    \    detail::BipartiteEdgeColoringGroups right_groups =\n        detail::group_vertices(right_degree,\
    \ maximum_degree);\n    int side_size = std::max(left_groups.count, right_groups.count);\n\
    \n    std::vector<int> contracted_left;\n    std::vector<int> contracted_right;\n\
    \    contracted_left.reserve(std::size_t(3) * edges.size());\n    contracted_right.reserve(std::size_t(3)\
    \ * edges.size());\n    std::vector<int> contracted_left_degree(side_size, 0);\n\
    \    std::vector<int> contracted_right_degree(side_size, 0);\n    for (auto [left,\
    \ right] : edges) {\n        int contracted_left_vertex = left_groups.group[left];\n\
    \        int contracted_right_vertex = right_groups.group[right];\n        contracted_left.push_back(contracted_left_vertex);\n\
    \        contracted_right.push_back(contracted_right_vertex);\n        contracted_left_degree[contracted_left_vertex]++;\n\
    \        contracted_right_degree[contracted_right_vertex]++;\n    }\n\n    int\
    \ left = 0;\n    int right = 0;\n    while (true) {\n        while (left < side_size\
    \ && contracted_left_degree[left] == maximum_degree) left++;\n        while (right\
    \ < side_size && contracted_right_degree[right] == maximum_degree) right++;\n\
    \        if (left == side_size || right == side_size) break;\n        contracted_left.push_back(left);\n\
    \        contracted_right.push_back(right);\n        contracted_left_degree[left]++;\n\
    \        contracted_right_degree[right]++;\n    }\n    assert(left == side_size\
    \ && right == side_size);\n    assert(contracted_left.size() == std::size_t(side_size)\
    \ * std::size_t(maximum_degree));\n\n    detail::BipartiteEdgeColoringSolver solver(\n\
    \        side_size,\n        int(edges.size()),\n        std::move(contracted_left),\n\
    \        std::move(contracted_right)\n    );\n    result.color = solver.solve(maximum_degree);\n\
    \    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line\
    \ 11 \"graph/dag_path_cover.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    struct DagPathCoverResult {\n    std::vector<std::vector<int>> paths;\n    std::vector<std::vector<int>>\
    \ path_edge_ids;\n    std::vector<int> predecessor;\n    std::vector<int> successor;\n\
    \    std::vector<int> predecessor_edge;\n    std::vector<int> successor_edge;\n\
    \n    int size() const {\n        return int(paths.size());\n    }\n};\n\ntemplate\
    \ <class T>\nstd::optional<DagPathCoverResult> minimum_dag_path_cover(const Graph<T>&\
    \ g) {\n    const int n = g.size();\n    if (!topological_sort(g)) return std::nullopt;\n\
    \n    BipartiteMatching matching(n, n);\n    std::vector<int> original_edge_id;\n\
    \    for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v]) {\n   \
    \         if (!e.alive) continue;\n            matching.add_edge(v, e.to);\n \
    \           original_edge_id.push_back(e.id);\n        }\n    }\n\n    DagPathCoverResult\
    \ result;\n    result.predecessor.assign(n, -1);\n    result.successor.assign(n,\
    \ -1);\n    result.predecessor_edge.assign(n, -1);\n    result.successor_edge.assign(n,\
    \ -1);\n    for (const auto& pair : matching.matching()) {\n        const int\
    \ edge_id = original_edge_id[pair.edge_id];\n        result.successor[pair.left]\
    \ = pair.right;\n        result.successor_edge[pair.left] = edge_id;\n       \
    \ result.predecessor[pair.right] = pair.left;\n        result.predecessor_edge[pair.right]\
    \ = edge_id;\n    }\n\n    int covered = 0;\n    for (int s = 0; s < n; s++) {\n\
    \        if (result.predecessor[s] != -1) continue;\n        result.paths.emplace_back();\n\
    \        result.path_edge_ids.emplace_back();\n        for (int v = s; v != -1;\
    \ v = result.successor[v]) {\n            result.paths.back().push_back(v);\n\
    \            covered++;\n            if (result.successor_edge[v] != -1) {\n \
    \               result.path_edge_ids.back().push_back(result.successor_edge[v]);\n\
    \            }\n        }\n    }\n    assert(covered == n);\n    return result;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/dag_reachability.hpp\"\
    \n\n\n\n#line 9 \"graph/dag_reachability.hpp\"\n\n#line 1 \"utilities/dynamic_bitset.hpp\"\
    \n\n\n\n#line 9 \"utilities/dynamic_bitset.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\nstruct DynamicBitset {\n   private:\n    static constexpr int\
    \ BITS_PER_BLOCK = 64;\n    static constexpr uint64_t FULL_BLOCK = ~uint64_t{0};\n\
    \n    int _n;\n    std::vector<uint64_t> blocks;\n\n    static int block_count(int\
    \ n) {\n        assert(n >= 0);\n        return (n + BITS_PER_BLOCK - 1) >> 6;\n\
    \    }\n\n    uint64_t tail_mask() const {\n        const int rem = _n & (BITS_PER_BLOCK\
    \ - 1);\n        return rem == 0 ? FULL_BLOCK : ((uint64_t{1} << rem) - 1);\n\
    \    }\n\n    // Keep unused bits in the last block equal to zero.\n    void clean()\
    \ {\n        if (!blocks.empty()) blocks.back() &= tail_mask();\n    }\n\n   public:\n\
    \    DynamicBitset() : _n(0), blocks() {}\n\n    explicit DynamicBitset(int n,\
    \ bool val = false) : _n(n), blocks(block_count(n), val ? FULL_BLOCK : 0) {\n\
    \        if (val) clean();\n    }\n\n    // Returns the logical number of bits.\n\
    \    int size() const {\n        return _n;\n    }\n\n    // Returns whether the\
    \ bit at index i is set.\n    bool test(int i) const {\n        assert(0 <= i\
    \ && i < _n);\n        return (blocks[i >> 6] >> (i & (BITS_PER_BLOCK - 1))) &\
    \ 1;\n    }\n\n    // Sets the bit at index i to true.\n    void set(int i) {\n\
    \        assert(0 <= i && i < _n);\n        blocks[i >> 6] |= uint64_t{1} << (i\
    \ & (BITS_PER_BLOCK - 1));\n    }\n\n    // Sets all bits to true.\n    void set()\
    \ {\n        std::fill(blocks.begin(), blocks.end(), FULL_BLOCK);\n        clean();\n\
    \    }\n\n    // Sets the bit at index i to false.\n    void reset(int i) {\n\
    \        assert(0 <= i && i < _n);\n        blocks[i >> 6] &= ~(uint64_t{1} <<\
    \ (i & (BITS_PER_BLOCK - 1)));\n    }\n\n    // Sets all bits to false.\n    void\
    \ reset() {\n        std::fill(blocks.begin(), blocks.end(), uint64_t{0});\n \
    \   }\n\n    // Flips the bit at index i.\n    void flip(int i) {\n        assert(0\
    \ <= i && i < _n);\n        blocks[i >> 6] ^= uint64_t{1} << (i & (BITS_PER_BLOCK\
    \ - 1));\n    }\n\n    // Flips all bits.\n    void flip() {\n        for (uint64_t&\
    \ block : blocks) block = ~block;\n        clean();\n    }\n\n    // Returns the\
    \ number of set bits.\n    int popcount() const {\n        int res = 0;\n    \
    \    for (uint64_t block : blocks) res += __builtin_popcountll(block);\n     \
    \   return res;\n    }\n\n    // Returns the index of the least significant set\
    \ bit, or -1 if no bit is set.\n    int lowbit() const {\n        const int m\
    \ = static_cast<int>(blocks.size());\n        for (int i = 0; i < m; ++i) {\n\
    \            if (blocks[i] != 0) return (i << 6) + __builtin_ctzll(blocks[i]);\n\
    \        }\n        return -1;\n    }\n\n    // Returns the index of the most\
    \ significant set bit, or -1 if no bit is set.\n    int topbit() const {\n   \
    \     for (int i = static_cast<int>(blocks.size()) - 1; i >= 0; --i) {\n     \
    \       if (blocks[i] != 0) return (i << 6) + (BITS_PER_BLOCK - 1 - __builtin_clzll(blocks[i]));\n\
    \        }\n        return -1;\n    }\n\n    // Returns whether at least one bit\
    \ is set.\n    bool any() const {\n        for (uint64_t block : blocks) {\n \
    \           if (block != 0) return true;\n        }\n        return false;\n \
    \   }\n\n    // Returns whether every logical bit is set.\n    bool all() const\
    \ {\n        if (_n == 0) return true;\n\n        const int m = static_cast<int>(blocks.size());\n\
    \        for (int i = 0; i + 1 < m; ++i) {\n            if (blocks[i] != FULL_BLOCK)\
    \ return false;\n        }\n        return blocks.back() == tail_mask();\n   \
    \ }\n\n    // Returns whether no bit is set.\n    bool none() const {\n      \
    \  return !any();\n    }\n\n    DynamicBitset& operator&=(const DynamicBitset&\
    \ other) {\n        assert(_n == other._n);\n        const std::size_t m = blocks.size();\n\
    \        for (std::size_t i = 0; i < m; ++i) blocks[i] &= other.blocks[i];\n \
    \       return *this;\n    }\n\n    DynamicBitset& operator|=(const DynamicBitset&\
    \ other) {\n        assert(_n == other._n);\n        const std::size_t m = blocks.size();\n\
    \        for (std::size_t i = 0; i < m; ++i) blocks[i] |= other.blocks[i];\n \
    \       return *this;\n    }\n\n    DynamicBitset& operator^=(const DynamicBitset&\
    \ other) {\n        assert(_n == other._n);\n        const std::size_t m = blocks.size();\n\
    \        for (std::size_t i = 0; i < m; ++i) blocks[i] ^= other.blocks[i];\n \
    \       return *this;\n    }\n\n    DynamicBitset operator~() const {\n      \
    \  DynamicBitset res = *this;\n        res.flip();\n        return res;\n    }\n\
    \n    friend DynamicBitset operator&(DynamicBitset lhs, const DynamicBitset& rhs)\
    \ {\n        lhs &= rhs;\n        return lhs;\n    }\n\n    friend DynamicBitset\
    \ operator|(DynamicBitset lhs, const DynamicBitset& rhs) {\n        lhs |= rhs;\n\
    \        return lhs;\n    }\n\n    friend DynamicBitset operator^(DynamicBitset\
    \ lhs, const DynamicBitset& rhs) {\n        lhs ^= rhs;\n        return lhs;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 13 \"\
    graph/dag_reachability.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct\
    \ DagReachability {\n    std::vector<utilities::DynamicBitset> reachable_vertices;\n\
    \    std::vector<int> topological_order;\n\n    int size() const {\n        return\
    \ int(reachable_vertices.size());\n    }\n\n    bool reachable(int from, int to)\
    \ const {\n        assert(0 <= from && from < size());\n        assert(0 <= to\
    \ && to < size());\n        return reachable_vertices[from].test(to);\n    }\n\
    };\n\ntemplate <class T>\nstd::optional<DagReachability> dag_reachability(const\
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
    \ m1une\n\n\n#line 1 \"graph/dag_shortest_path.hpp\"\n\n\n\n#line 9 \"graph/dag_shortest_path.hpp\"\
    \n\n#line 12 \"graph/dag_shortest_path.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstruct DagShortestPathResult {\n    std::vector<T>\
    \ dist;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n   \
    \ std::vector<int> topological_order;\n    T inf;\n\n    bool reachable(int v)\
    \ const {\n        assert(0 <= v && v < int(dist.size()));\n        return dist[v]\
    \ != inf;\n    }\n\n    std::vector<int> path(int t) const {\n        assert(reachable(t));\n\
    \        std::vector<int> result;\n        for (int v = t; v != -1; v = parent[v])\
    \ result.push_back(v);\n        std::reverse(result.begin(), result.end());\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nstd::optional<DagShortestPathResult<T>>\
    \ dag_shortest_path(\n    const Graph<T>& g, const std::vector<int>& sources,\
    \ T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n   \
    \ auto order = topological_sort(g);\n    if (!order) return std::nullopt;\n\n\
    \    DagShortestPathResult<T> result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n    result.topological_order =\
    \ *order;\n    result.inf = inf;\n\n    for (int s : sources) {\n        assert(0\
    \ <= s && s < n);\n        if (result.dist[s] == T(0)) continue;\n        result.dist[s]\
    \ = T(0);\n    }\n\n    for (int v : *order) {\n        if (result.dist[v] ==\
    \ inf) continue;\n        for (const auto& e : g[v]) {\n            if (!e.alive)\
    \ continue;\n            T nd = result.dist[v] + e.cost;\n            if (result.dist[e.to]\
    \ <= nd) continue;\n            result.dist[e.to] = nd;\n            result.parent[e.to]\
    \ = v;\n            result.parent_edge[e.to] = e.id;\n        }\n    }\n\n   \
    \ return result;\n}\n\ntemplate <class T>\nstd::optional<DagShortestPathResult<T>>\
    \ dag_shortest_path(\n    const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    return dag_shortest_path(g, std::vector<int>{s}, inf);\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 10 \"graph/dag.hpp\"\n\
    \n\n#line 12 \"verify/graph/dag_algorithms.test.cpp\"\n\nusing m1une::graph::Graph;\n\
    \nstd::vector<std::vector<char>> naive_reachability(const Graph<int>& g) {\n \
    \   const int n = g.size();\n    std::vector<std::vector<char>> reach(n, std::vector<char>(n,\
    \ false));\n    for (int v = 0; v < n; v++) reach[v][v] = true;\n    for (int\
    \ v = 0; v < n; v++) {\n        for (const auto& e : g[v]) {\n            if (e.alive)\
    \ reach[v][e.to] = true;\n        }\n    }\n    for (int k = 0; k < n; k++) {\n\
    \        for (int i = 0; i < n; i++) {\n            for (int j = 0; j < n; j++)\
    \ {\n                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);\n\
    \            }\n        }\n    }\n    return reach;\n}\n\nint naive_maximum_matching(const\
    \ Graph<int>& g) {\n    const int n = g.size();\n    std::vector<std::vector<int>>\
    \ adjacency(n);\n    for (int v = 0; v < n; v++) {\n        for (const auto& e\
    \ : g[v]) {\n            if (e.alive && std::find(adjacency[v].begin(), adjacency[v].end(),\
    \ e.to) == adjacency[v].end()) {\n                adjacency[v].push_back(e.to);\n\
    \            }\n        }\n    }\n\n    std::vector<int> dp(1 << n, -1);\n   \
    \ dp[0] = 0;\n    for (int left = 0; left < n; left++) {\n        std::vector<int>\
    \ next = dp;\n        for (int mask = 0; mask < (1 << n); mask++) {\n        \
    \    if (dp[mask] < 0) continue;\n            for (int right : adjacency[left])\
    \ {\n                if ((mask >> right) & 1) continue;\n                int next_mask\
    \ = mask | (1 << right);\n                next[next_mask] = std::max(next[next_mask],\
    \ dp[mask] + 1);\n            }\n        }\n        dp.swap(next);\n    }\n  \
    \  return *std::max_element(dp.begin(), dp.end());\n}\n\nvoid test_randomized()\
    \ {\n    std::mt19937 rng(123456789);\n    for (int iteration = 0; iteration <\
    \ 1000; iteration++) {\n        const int n = int(rng() % 8);\n        std::vector<int>\
    \ order(n);\n        for (int i = 0; i < n; i++) order[i] = i;\n        std::shuffle(order.begin(),\
    \ order.end(), rng);\n\n        Graph<int> g(n);\n        for (int i = 0; i <\
    \ n; i++) {\n            for (int j = i + 1; j < n; j++) {\n                if\
    \ (rng() % 3 != 0) continue;\n                g.add_directed_edge(order[i], order[j],\
    \ int(rng() % 11) - 5);\n                if (rng() % 8 == 0) {\n             \
    \       int id = g.add_directed_edge(order[i], order[j], int(rng() % 11) - 5);\n\
    \                    if (rng() % 3 == 0) g.erase_edge(id);\n                }\n\
    \            }\n        }\n\n        std::vector<int> sources;\n        for (int\
    \ v = 0; v < n; v++) {\n            if (rng() % 3 == 0) sources.push_back(v);\n\
    \        }\n        if (n > 0 && sources.empty()) sources.push_back(int(rng()\
    \ % n));\n\n        const int neg_inf = std::numeric_limits<int>::lowest() / 4;\n\
    \        std::vector<int> longest(n, neg_inf);\n        std::vector<long long>\
    \ path_count(n, 0);\n        std::function<void(int, int)> enumerate = [&](int\
    \ v, int distance) {\n            longest[v] = std::max(longest[v], distance);\n\
    \            path_count[v]++;\n            for (const auto& e : g[v]) {\n    \
    \            if (e.alive) enumerate(e.to, distance + e.cost);\n            }\n\
    \        };\n        for (int s : sources) enumerate(s, 0);\n\n        auto longest_result\
    \ = m1une::graph::dag_longest_path(g, sources);\n        assert(longest_result.has_value());\n\
    \        assert(longest_result->dist == longest);\n        for (int v = 0; v <\
    \ n; v++) {\n            if (!longest_result->reachable(v)) continue;\n      \
    \      std::vector<int> path = longest_result->path(v);\n            assert(!path.empty()\
    \ && path.back() == v);\n            assert(std::find(sources.begin(), sources.end(),\
    \ path.front()) != sources.end());\n        }\n\n        auto count_result = m1une::graph::dag_path_count<long\
    \ long>(g, sources);\n        assert(count_result.has_value());\n        assert(*count_result\
    \ == path_count);\n\n        auto reachability = m1une::graph::dag_reachability(g);\n\
    \        assert(reachability.has_value());\n        auto expected_reachability\
    \ = naive_reachability(g);\n        for (int from = 0; from < n; from++) {\n \
    \           for (int to = 0; to < n; to++) {\n                assert(reachability->reachable(from,\
    \ to) == bool(expected_reachability[from][to]));\n            }\n        }\n\n\
    \        auto reduction = m1une::graph::dag_transitive_reduction(g);\n       \
    \ assert(reduction.has_value());\n        assert(naive_reachability(reduction->graph)\
    \ == expected_reachability);\n        assert(reduction->graph.edge_count() ==\
    \ int(reduction->original_edge_ids.size()));\n        std::vector<m1une::graph::Edge<int>>\
    \ reduced_edges = reduction->graph.edges();\n        for (int removed = 0; removed\
    \ < reduction->graph.edge_count(); removed++) {\n            Graph<int> without_edge(n);\n\
    \            for (const auto& e : reduced_edges) {\n                if (e.id !=\
    \ removed) without_edge.add_directed_edge(e.from, e.to, e.cost);\n           \
    \ }\n            const auto& edge = reduced_edges[removed];\n            assert(!naive_reachability(without_edge)[edge.from][edge.to]);\n\
    \        }\n\n        auto cover = m1une::graph::minimum_dag_path_cover(g);\n\
    \        assert(cover.has_value());\n        assert(cover->size() == n - naive_maximum_matching(g));\n\
    \        std::vector<int> occurrence(n, 0);\n        for (int i = 0; i < cover->size();\
    \ i++) {\n            assert(cover->path_edge_ids[i].size() + 1 == cover->paths[i].size());\n\
    \            for (int v : cover->paths[i]) occurrence[v]++;\n            for (int\
    \ j = 0; j + 1 < int(cover->paths[i].size()); j++) {\n                int from\
    \ = cover->paths[i][j];\n                int to = cover->paths[i][j + 1];\n  \
    \              int edge_id = cover->path_edge_ids[i][j];\n                bool\
    \ found = false;\n                for (const auto& e : g[from]) {\n          \
    \          if (e.alive && e.to == to && e.id == edge_id) found = true;\n     \
    \           }\n                assert(found);\n            }\n        }\n    \
    \    for (int count : occurrence) assert(count == 1);\n    }\n}\n\nvoid test_cycle_rejection()\
    \ {\n    Graph<int> g(3);\n    g.add_directed_edge(0, 1);\n    g.add_directed_edge(1,\
    \ 2);\n    g.add_directed_edge(2, 0);\n    assert(!m1une::graph::dag_longest_path(g,\
    \ 0));\n    assert(!m1une::graph::dag_path_count(g, 0));\n    assert(!m1une::graph::dag_reachability(g));\n\
    \    assert(!m1une::graph::dag_transitive_reduction(g));\n    assert(!m1une::graph::minimum_dag_path_cover(g));\n\
    }\n\nint main() {\n    test_randomized();\n    test_cycle_rejection();\n\n   \
    \ int vertex_count, edge_count;\n    std::cin >> vertex_count >> edge_count;\n\
    \    Graph<int> g(vertex_count);\n    for (int i = 0; i < edge_count; i++) {\n\
    \        int from, to;\n        std::cin >> from >> to;\n        g.add_directed_edge(from,\
    \ to);\n    }\n    std::cout << !m1une::graph::is_dag(g) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A\"\n\n\
    #include <algorithm>\n#include <cassert>\n#include <functional>\n#include <iostream>\n\
    #include <limits>\n#include <random>\n#include <vector>\n\n#include \"../../graph/dag.hpp\"\
    \n\nusing m1une::graph::Graph;\n\nstd::vector<std::vector<char>> naive_reachability(const\
    \ Graph<int>& g) {\n    const int n = g.size();\n    std::vector<std::vector<char>>\
    \ reach(n, std::vector<char>(n, false));\n    for (int v = 0; v < n; v++) reach[v][v]\
    \ = true;\n    for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v])\
    \ {\n            if (e.alive) reach[v][e.to] = true;\n        }\n    }\n    for\
    \ (int k = 0; k < n; k++) {\n        for (int i = 0; i < n; i++) {\n         \
    \   for (int j = 0; j < n; j++) {\n                reach[i][j] = reach[i][j] ||\
    \ (reach[i][k] && reach[k][j]);\n            }\n        }\n    }\n    return reach;\n\
    }\n\nint naive_maximum_matching(const Graph<int>& g) {\n    const int n = g.size();\n\
    \    std::vector<std::vector<int>> adjacency(n);\n    for (int v = 0; v < n; v++)\
    \ {\n        for (const auto& e : g[v]) {\n            if (e.alive && std::find(adjacency[v].begin(),\
    \ adjacency[v].end(), e.to) == adjacency[v].end()) {\n                adjacency[v].push_back(e.to);\n\
    \            }\n        }\n    }\n\n    std::vector<int> dp(1 << n, -1);\n   \
    \ dp[0] = 0;\n    for (int left = 0; left < n; left++) {\n        std::vector<int>\
    \ next = dp;\n        for (int mask = 0; mask < (1 << n); mask++) {\n        \
    \    if (dp[mask] < 0) continue;\n            for (int right : adjacency[left])\
    \ {\n                if ((mask >> right) & 1) continue;\n                int next_mask\
    \ = mask | (1 << right);\n                next[next_mask] = std::max(next[next_mask],\
    \ dp[mask] + 1);\n            }\n        }\n        dp.swap(next);\n    }\n  \
    \  return *std::max_element(dp.begin(), dp.end());\n}\n\nvoid test_randomized()\
    \ {\n    std::mt19937 rng(123456789);\n    for (int iteration = 0; iteration <\
    \ 1000; iteration++) {\n        const int n = int(rng() % 8);\n        std::vector<int>\
    \ order(n);\n        for (int i = 0; i < n; i++) order[i] = i;\n        std::shuffle(order.begin(),\
    \ order.end(), rng);\n\n        Graph<int> g(n);\n        for (int i = 0; i <\
    \ n; i++) {\n            for (int j = i + 1; j < n; j++) {\n                if\
    \ (rng() % 3 != 0) continue;\n                g.add_directed_edge(order[i], order[j],\
    \ int(rng() % 11) - 5);\n                if (rng() % 8 == 0) {\n             \
    \       int id = g.add_directed_edge(order[i], order[j], int(rng() % 11) - 5);\n\
    \                    if (rng() % 3 == 0) g.erase_edge(id);\n                }\n\
    \            }\n        }\n\n        std::vector<int> sources;\n        for (int\
    \ v = 0; v < n; v++) {\n            if (rng() % 3 == 0) sources.push_back(v);\n\
    \        }\n        if (n > 0 && sources.empty()) sources.push_back(int(rng()\
    \ % n));\n\n        const int neg_inf = std::numeric_limits<int>::lowest() / 4;\n\
    \        std::vector<int> longest(n, neg_inf);\n        std::vector<long long>\
    \ path_count(n, 0);\n        std::function<void(int, int)> enumerate = [&](int\
    \ v, int distance) {\n            longest[v] = std::max(longest[v], distance);\n\
    \            path_count[v]++;\n            for (const auto& e : g[v]) {\n    \
    \            if (e.alive) enumerate(e.to, distance + e.cost);\n            }\n\
    \        };\n        for (int s : sources) enumerate(s, 0);\n\n        auto longest_result\
    \ = m1une::graph::dag_longest_path(g, sources);\n        assert(longest_result.has_value());\n\
    \        assert(longest_result->dist == longest);\n        for (int v = 0; v <\
    \ n; v++) {\n            if (!longest_result->reachable(v)) continue;\n      \
    \      std::vector<int> path = longest_result->path(v);\n            assert(!path.empty()\
    \ && path.back() == v);\n            assert(std::find(sources.begin(), sources.end(),\
    \ path.front()) != sources.end());\n        }\n\n        auto count_result = m1une::graph::dag_path_count<long\
    \ long>(g, sources);\n        assert(count_result.has_value());\n        assert(*count_result\
    \ == path_count);\n\n        auto reachability = m1une::graph::dag_reachability(g);\n\
    \        assert(reachability.has_value());\n        auto expected_reachability\
    \ = naive_reachability(g);\n        for (int from = 0; from < n; from++) {\n \
    \           for (int to = 0; to < n; to++) {\n                assert(reachability->reachable(from,\
    \ to) == bool(expected_reachability[from][to]));\n            }\n        }\n\n\
    \        auto reduction = m1une::graph::dag_transitive_reduction(g);\n       \
    \ assert(reduction.has_value());\n        assert(naive_reachability(reduction->graph)\
    \ == expected_reachability);\n        assert(reduction->graph.edge_count() ==\
    \ int(reduction->original_edge_ids.size()));\n        std::vector<m1une::graph::Edge<int>>\
    \ reduced_edges = reduction->graph.edges();\n        for (int removed = 0; removed\
    \ < reduction->graph.edge_count(); removed++) {\n            Graph<int> without_edge(n);\n\
    \            for (const auto& e : reduced_edges) {\n                if (e.id !=\
    \ removed) without_edge.add_directed_edge(e.from, e.to, e.cost);\n           \
    \ }\n            const auto& edge = reduced_edges[removed];\n            assert(!naive_reachability(without_edge)[edge.from][edge.to]);\n\
    \        }\n\n        auto cover = m1une::graph::minimum_dag_path_cover(g);\n\
    \        assert(cover.has_value());\n        assert(cover->size() == n - naive_maximum_matching(g));\n\
    \        std::vector<int> occurrence(n, 0);\n        for (int i = 0; i < cover->size();\
    \ i++) {\n            assert(cover->path_edge_ids[i].size() + 1 == cover->paths[i].size());\n\
    \            for (int v : cover->paths[i]) occurrence[v]++;\n            for (int\
    \ j = 0; j + 1 < int(cover->paths[i].size()); j++) {\n                int from\
    \ = cover->paths[i][j];\n                int to = cover->paths[i][j + 1];\n  \
    \              int edge_id = cover->path_edge_ids[i][j];\n                bool\
    \ found = false;\n                for (const auto& e : g[from]) {\n          \
    \          if (e.alive && e.to == to && e.id == edge_id) found = true;\n     \
    \           }\n                assert(found);\n            }\n        }\n    \
    \    for (int count : occurrence) assert(count == 1);\n    }\n}\n\nvoid test_cycle_rejection()\
    \ {\n    Graph<int> g(3);\n    g.add_directed_edge(0, 1);\n    g.add_directed_edge(1,\
    \ 2);\n    g.add_directed_edge(2, 0);\n    assert(!m1une::graph::dag_longest_path(g,\
    \ 0));\n    assert(!m1une::graph::dag_path_count(g, 0));\n    assert(!m1une::graph::dag_reachability(g));\n\
    \    assert(!m1une::graph::dag_transitive_reduction(g));\n    assert(!m1une::graph::minimum_dag_path_cover(g));\n\
    }\n\nint main() {\n    test_randomized();\n    test_cycle_rejection();\n\n   \
    \ int vertex_count, edge_count;\n    std::cin >> vertex_count >> edge_count;\n\
    \    Graph<int> g(vertex_count);\n    for (int i = 0; i < edge_count; i++) {\n\
    \        int from, to;\n        std::cin >> from >> to;\n        g.add_directed_edge(from,\
    \ to);\n    }\n    std::cout << !m1une::graph::is_dag(g) << '\\n';\n}\n"
  dependsOn:
  - graph/dag.hpp
  - graph/dag_longest_path.hpp
  - graph/graph.hpp
  - graph/topological_sort.hpp
  - graph/dag_path_count.hpp
  - graph/dag_path_cover.hpp
  - graph/bipartite.hpp
  - graph/dag_reachability.hpp
  - utilities/dynamic_bitset.hpp
  - graph/dag_shortest_path.hpp
  isVerificationFile: true
  path: verify/graph/dag_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-08-24 00:41:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/dag_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/dag_algorithms.test.cpp
- /verify/verify/graph/dag_algorithms.test.cpp.html
title: verify/graph/dag_algorithms.test.cpp
---
