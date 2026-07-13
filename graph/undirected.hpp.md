---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: graph/bellman_ford.hpp
    title: Bellman-Ford
  - icon: ':heavy_check_mark:'
    path: graph/bfs.hpp
    title: BFS
  - icon: ':heavy_check_mark:'
    path: graph/biconnected_components.hpp
    title: Biconnected Components
  - icon: ':heavy_check_mark:'
    path: graph/bipartite.hpp
    title: Bipartite Graph
  - icon: ':heavy_check_mark:'
    path: graph/block_cut_tree.hpp
    title: Block-Cut Tree
  - icon: ':heavy_check_mark:'
    path: graph/chromatic_number.hpp
    title: Chromatic Number
  - icon: ':heavy_check_mark:'
    path: graph/connected_components.hpp
    title: Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/cow_game.hpp
    title: Cow Game (Difference Constraints)
  - icon: ':heavy_check_mark:'
    path: graph/cycle_detection.hpp
    title: Cycle Detection
  - icon: ':heavy_check_mark:'
    path: graph/dag_shortest_path.hpp
    title: DAG Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: Dijkstra
  - icon: ':heavy_check_mark:'
    path: graph/enumerate_triangles.hpp
    title: Enumerate Triangles
  - icon: ':heavy_check_mark:'
    path: graph/eulerian_trail.hpp
    title: Eulerian Trail
  - icon: ':heavy_check_mark:'
    path: graph/general_matching.hpp
    title: General Matching
  - icon: ':heavy_check_mark:'
    path: graph/general_weighted_matching.hpp
    title: General Weighted Matching
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/grid.hpp
    title: Grid
  - icon: ':heavy_check_mark:'
    path: graph/k_shortest_walk.hpp
    title: K-Shortest Walk
  - icon: ':heavy_check_mark:'
    path: graph/kruskal.hpp
    title: Kruskal
  - icon: ':heavy_check_mark:'
    path: graph/lowlink.hpp
    title: LowLink
  - icon: ':heavy_check_mark:'
    path: graph/maximum_clique.hpp
    title: Maximum Clique, Independent Set, and Vertex Cover
  - icon: ':heavy_check_mark:'
    path: graph/minimum_steiner_tree.hpp
    title: Minimum Steiner Tree
  - icon: ':heavy_check_mark:'
    path: graph/namori.hpp
    title: Namori Graph Decomposition
  - icon: ':heavy_check_mark:'
    path: graph/replacement_paths.hpp
    title: Replacement Paths
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  - icon: ':heavy_check_mark:'
    path: graph/two_edge_connected_components.hpp
    title: Two-Edge-Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/warshall_floyd.hpp
    title: Warshall-Floyd
  - icon: ':heavy_check_mark:'
    path: graph/zero_one_bfs.hpp
    title: 0-1 BFS
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/undirected.hpp\"\n\n\n\n#line 1 \"graph/bipartite.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <limits>\n#include <optional>\n#include <queue>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"\
    graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T\
    \ = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int to;\n\
    \    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()),\
    \ id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_\
    \ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_),\
    \ alive(alive_) {}\n\n    int other(int v) const {\n        assert(v == from ||\
    \ v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\n\
    struct Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n \
    \  private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
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
    \ m1une\n\n\n#line 15 \"graph/bipartite.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct BipartiteResult {\n    bool is_bipartite;\n    std::vector<int>\
    \ color;\n    std::vector<int> left_vertices;\n    std::vector<int> right_vertices;\n\
    \    std::vector<int> left_id;\n    std::vector<int> right_id;\n};\n\ntemplate\
    \ <class T>\nBipartiteResult bipartite(const Graph<T>& g) {\n    int n = g.size();\n\
    \    BipartiteResult result;\n    result.is_bipartite = true;\n    result.color.assign(n,\
    \ -1);\n    result.left_id.assign(n, -1);\n    result.right_id.assign(n, -1);\n\
    \n    std::vector<std::vector<int>> adjacency(n);\n    for (const auto& e : g.edges())\
    \ {\n        adjacency[e.from].push_back(e.to);\n        adjacency[e.to].push_back(e.from);\n\
    \    }\n\n    std::queue<int> que;\n    for (int s = 0; s < n; s++) {\n      \
    \  if (result.color[s] != -1) continue;\n        result.color[s] = 0;\n      \
    \  que.push(s);\n        while (!que.empty()) {\n            int v = que.front();\n\
    \            que.pop();\n            for (int to : adjacency[v]) {\n         \
    \       if (result.color[to] == -1) {\n                    result.color[to] =\
    \ result.color[v] ^ 1;\n                    que.push(to);\n                } else\
    \ if (result.color[to] == result.color[v]) {\n                    result.is_bipartite\
    \ = false;\n                    return result;\n                }\n          \
    \  }\n        }\n    }\n\n    for (int v = 0; v < n; v++) {\n        if (result.color[v]\
    \ == 0) {\n            result.left_id[v] = int(result.left_vertices.size());\n\
    \            result.left_vertices.push_back(v);\n        } else {\n          \
    \  result.right_id[v] = int(result.right_vertices.size());\n            result.right_vertices.push_back(v);\n\
    \        }\n    }\n\n    return result;\n}\n\ntemplate <class T>\nbool is_bipartite(const\
    \ Graph<T>& g) {\n    return bipartite(g).is_bipartite;\n}\n\nstruct BipartiteVertexSet\
    \ {\n    std::vector<int> left;\n    std::vector<int> right;\n\n    int size()\
    \ const {\n        return int(left.size() + right.size());\n    }\n};\n\nstruct\
    \ BipartiteMatching {\n    struct Edge {\n        int left;\n        int right;\n\
    \        int id;\n        bool alive;\n    };\n\n    struct Pair {\n        int\
    \ left;\n        int right;\n        int edge_id;\n    };\n\n   private:\n   \
    \ int _left_size;\n    int _right_size;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
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
    \ 1 \"graph/biconnected_components.hpp\"\n\n\n\n#line 6 \"graph/biconnected_components.hpp\"\
    \n\n#line 8 \"graph/biconnected_components.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct BiconnectedComponentsResult {\n    std::vector<std::vector<int>>\
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
    \n\n#line 1 \"graph/block_cut_tree.hpp\"\n\n\n\n#line 6 \"graph/block_cut_tree.hpp\"\
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
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/chromatic_number.hpp\"\
    \n\n\n\n#include <array>\n#include <bit>\n#line 9 \"graph/chromatic_number.hpp\"\
    \n\n#line 11 \"graph/chromatic_number.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nnamespace detail {\n\nstruct ChromaticResidues {\n    static constexpr\
    \ std::array<std::uint32_t, 14> mod = {\n        1000000007, 1000000009, 998244353,\
    \ 985661441, 943718401, 935329793, 918552577,\n        897581057,  880803841,\
    \  754974721, 645922817, 595591169, 469762049, 167772161,\n    };\n\n    std::array<std::uint32_t,\
    \ 14> value;\n\n    explicit ChromaticResidues(std::uint32_t x = 0) {\n      \
    \  value.fill(x);\n    }\n\n    void multiply(std::uint32_t x) {\n        for\
    \ (int i = 0; i < int(mod.size()); i++) {\n            value[i] = std::uint32_t(std::uint64_t(value[i])\
    \ * x % mod[i]);\n        }\n    }\n};\n\n}  // namespace detail\n\ntemplate <class\
    \ T>\nint chromatic_number(const Graph<T>& g) {\n    int n = g.size();\n    assert(n\
    \ <= 20);\n    if (n == 0) return 0;\n\n    std::vector<std::uint32_t> adjacent(n,\
    \ 0);\n    for (const auto& e : g.edges()) {\n        if (e.from == e.to) continue;\n\
    \        adjacent[e.from] |= std::uint32_t(1) << e.to;\n        adjacent[e.to]\
    \ |= std::uint32_t(1) << e.from;\n    }\n\n    std::uint32_t subset_count = std::uint32_t(1)\
    \ << n;\n    std::vector<std::uint32_t> independent_count(subset_count, 0);\n\
    \    independent_count[0] = 1;\n    for (std::uint32_t mask = 1; mask < subset_count;\
    \ mask++) {\n        int v = std::countr_zero(mask);\n        std::uint32_t rest\
    \ = mask ^ (std::uint32_t(1) << v);\n        independent_count[mask] =\n     \
    \       independent_count[rest] + independent_count[rest & ~adjacent[v]];\n  \
    \  }\n\n    std::vector<detail::ChromaticResidues> power(subset_count, detail::ChromaticResidues(1));\n\
    \    for (int colors = 1; colors <= n; colors++) {\n        std::array<std::uint32_t,\
    \ 14> sum = {};\n        for (std::uint32_t mask = 0; mask < subset_count; mask++)\
    \ {\n            power[mask].multiply(independent_count[mask]);\n            bool\
    \ positive = ((n - std::popcount(mask)) & 1) == 0;\n            for (int i = 0;\
    \ i < int(sum.size()); i++) {\n                std::uint32_t x = power[mask].value[i];\n\
    \                if (positive) {\n                    sum[i] += x;\n         \
    \           if (sum[i] >= detail::ChromaticResidues::mod[i]) {\n             \
    \           sum[i] -= detail::ChromaticResidues::mod[i];\n                   \
    \ }\n                } else {\n                    sum[i] = (sum[i] >= x ? sum[i]\
    \ - x\n                                          : sum[i] + detail::ChromaticResidues::mod[i]\
    \ - x);\n                }\n            }\n        }\n        for (std::uint32_t\
    \ x : sum) {\n            if (x != 0) return colors;\n        }\n    }\n    return\
    \ n;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/connected_components.hpp\"\
    \n\n\n\n#line 6 \"graph/connected_components.hpp\"\n\n#line 1 \"ds/dsu/dsu.hpp\"\
    \n\n\n\n#line 5 \"ds/dsu/dsu.hpp\"\n#include <numeric>\n#line 8 \"ds/dsu/dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct Dsu {\n   private:\n    int _n;\n\
    \    // parent_or_size[i] is the parent of i if it's >= 0.\n    // If it's < 0,\
    \ then i is a root and -parent_or_size[i] is the size of the group.\n    std::vector<int>\
    \ parent_or_size;\n\n    // Returns {new leader, absorbed leader}. The absorbed\
    \ leader is -1 when\n    // both vertices already belong to the same component.\n\
    \    std::pair<int, int> merge_leaders(int a, int b) {\n        int x = leader(a),\
    \ y = leader(b);\n        if (x == y) return {x, -1};\n        if (-parent_or_size[x]\
    \ < -parent_or_size[y]) std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n\
    \        parent_or_size[y] = x;\n        return {x, y};\n    }\n\n   public:\n\
    \    Dsu() : _n(0) {}\n    explicit Dsu(int n) : _n(n), parent_or_size(n, -1)\
    \ {}\n\n    // Merges the group containing 'a' with the group containing 'b'.\n\
    \    // Returns the leader of the merged group.\n    int merge(int a, int b) {\n\
    \        return merge_leaders(a, b).first;\n    }\n\n    // Invokes callback(new_leader,\
    \ absorbed_leader) after an actual merge.\n    // Returns the leader of the merged\
    \ group.\n    template <class Callback>\n    int merge(int a, int b, Callback&&\
    \ callback) {\n        std::pair<int, int> merged = merge_leaders(a, b);\n   \
    \     if (merged.second != -1) callback(merged.first, merged.second);\n      \
    \  return merged.first;\n    }\n\n    // Returns true if 'a' and 'b' belong to\
    \ the same group.\n    bool same(int a, int b) {\n        return leader(a) ==\
    \ leader(b);\n    }\n\n    // Returns the leader (representative) of the group\
    \ containing 'a'.\n    int leader(int a) {\n        if (parent_or_size[a] < 0)\
    \ return a;\n        // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    // Returns the size of the group containing 'a'.\n    int size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    // Returns a\
    \ list of all groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 9 \"graph/connected_components.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct ConnectedComponents {\n    int count;\n\
    \    std::vector<int> comp;\n    std::vector<std::vector<int>> groups;\n\n   \
    \ bool same(int u, int v) const {\n        assert(0 <= u && u < int(comp.size()));\n\
    \        assert(0 <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n\
    \    }\n};\n\ntemplate <class T>\nConnectedComponents connected_components(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    m1une::ds::Dsu dsu(n);\n    for (const\
    \ auto& e : g.edges()) dsu.merge(e.from, e.to);\n\n    ConnectedComponents result;\n\
    \    result.comp.assign(n, 0);\n    std::vector<int> leader_to_comp(n, -1);\n\
    \    for (int v = 0; v < n; v++) {\n        int leader = dsu.leader(v);\n    \
    \    if (leader_to_comp[leader] == -1) {\n            leader_to_comp[leader] =\
    \ int(result.groups.size());\n            result.groups.push_back({});\n     \
    \   }\n        int c = leader_to_comp[leader];\n        result.comp[v] = c;\n\
    \        result.groups[c].push_back(v);\n    }\n    result.count = int(result.groups.size());\n\
    \n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n\
    #line 1 \"graph/cycle_detection.hpp\"\n\n\n\n#line 6 \"graph/cycle_detection.hpp\"\
    \n\n#line 8 \"graph/cycle_detection.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct Cycle {\n    std::vector<int> vertices;\n    std::vector<int> edge_ids;\n\
    \n    bool empty() const {\n        return vertices.empty();\n    }\n};\n\ninline\
    \ Cycle restore_cycle(int from, int to, int closing_edge, const std::vector<int>&\
    \ parent,\n                           const std::vector<int>& parent_edge) {\n\
    \    Cycle result;\n    result.vertices.push_back(to);\n\n    std::vector<int>\
    \ middle_vertices;\n    std::vector<int> middle_edges;\n    for (int v = from;\
    \ v != to; v = parent[v]) {\n        middle_vertices.push_back(v);\n        middle_edges.push_back(parent_edge[v]);\n\
    \    }\n    std::reverse(middle_vertices.begin(), middle_vertices.end());\n  \
    \  std::reverse(middle_edges.begin(), middle_edges.end());\n\n    result.vertices.insert(result.vertices.end(),\
    \ middle_vertices.begin(), middle_vertices.end());\n    result.vertices.push_back(to);\n\
    \    result.edge_ids.insert(result.edge_ids.end(), middle_edges.begin(), middle_edges.end());\n\
    \    result.edge_ids.push_back(closing_edge);\n    return result;\n}\n\ntemplate\
    \ <class T>\nCycle find_directed_cycle(const Graph<T>& g) {\n    int n = g.size();\n\
    \    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);\n    Cycle\
    \ result;\n\n    auto dfs = [&](auto self, int v) -> bool {\n        color[v]\
    \ = 1;\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            if (color[e.to] == 0) {\n                parent[e.to] = v;\n    \
    \            parent_edge[e.to] = e.id;\n                if (self(self, e.to))\
    \ return true;\n            } else if (color[e.to] == 1) {\n                result\
    \ = restore_cycle(v, e.to, e.id, parent, parent_edge);\n                return\
    \ true;\n            }\n        }\n        color[v] = 2;\n        return false;\n\
    \    };\n\n    for (int v = 0; v < n; v++) {\n        if (color[v] == 0 && dfs(dfs,\
    \ v)) break;\n    }\n    return result;\n}\n\ntemplate <class T>\nCycle find_undirected_cycle(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> color(n, 0), parent(n,\
    \ -1), parent_edge(n, -1);\n    Cycle result;\n\n    auto dfs = [&](auto self,\
    \ int v, int pe) -> bool {\n        color[v] = 1;\n        for (const auto& e\
    \ : g[v]) {\n            if (!e.alive) continue;\n            if (e.id == pe)\
    \ continue;\n            if (color[e.to] == 0) {\n                parent[e.to]\
    \ = v;\n                parent_edge[e.to] = e.id;\n                if (self(self,\
    \ e.to, e.id)) return true;\n            } else if (color[e.to] == 1) {\n    \
    \            result = restore_cycle(v, e.to, e.id, parent, parent_edge);\n   \
    \             return true;\n            }\n        }\n        color[v] = 2;\n\
    \        return false;\n    };\n\n    for (int v = 0; v < n; v++) {\n        if\
    \ (color[v] == 0 && dfs(dfs, v, -1)) break;\n    }\n    return result;\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/enumerate_triangles.hpp\"\
    \n\n\n\n#line 7 \"graph/enumerate_triangles.hpp\"\n\n#line 9 \"graph/enumerate_triangles.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T, class Callback>\n\
    void enumerate_triangles(const Graph<T>& graph, Callback&& callback) {\n    const\
    \ int n = graph.size();\n    const std::vector<Edge<T>> edges = graph.edges();\n\
    \n    std::vector<int> degree(n, 0);\n    for (const Edge<T>& edge : edges) {\n\
    \        assert(edge.from != edge.to);\n        degree[edge.from]++;\n       \
    \ degree[edge.to]++;\n    }\n\n    std::vector<std::vector<int>> oriented(n);\n\
    \    for (const Edge<T>& edge : edges) {\n        int from = edge.from;\n    \
    \    int to = edge.to;\n        if (degree[from] > degree[to] ||\n           \
    \ (degree[from] == degree[to] && from > to)) {\n            std::swap(from, to);\n\
    \        }\n        oriented[from].push_back(to);\n    }\n\n    std::vector<int>\
    \ marked(n, -1);\n    for (int vertex = 0; vertex < n; vertex++) {\n        for\
    \ (int to : oriented[vertex]) marked[to] = vertex;\n        for (int middle :\
    \ oriented[vertex]) {\n            for (int to : oriented[middle]) {\n       \
    \         if (marked[to] != vertex) continue;\n                int first = vertex;\n\
    \                int second = middle;\n                int third = to;\n     \
    \           if (first > second) std::swap(first, second);\n                if\
    \ (second > third) std::swap(second, third);\n                if (first > second)\
    \ std::swap(first, second);\n                callback(first, second, third);\n\
    \            }\n        }\n    }\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/eulerian_trail.hpp\"\n\n\n\n#line 9 \"graph/eulerian_trail.hpp\"\
    \n\n#line 11 \"graph/eulerian_trail.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct EulerianTrail {\n    std::vector<int> vertices;\n    std::vector<int>\
    \ edge_ids;\n\n    int edge_count() const {\n        return int(edge_ids.size());\n\
    \    }\n\n    bool is_circuit() const {\n        return vertices.empty() || vertices.front()\
    \ == vertices.back();\n    }\n};\n\nnamespace internal {\n\ntemplate <class T>\n\
    std::optional<EulerianTrail> hierholzer(\n    const Graph<T>& graph,\n    int\
    \ start,\n    int active_edge_count\n) {\n    EulerianTrail result;\n    if (active_edge_count\
    \ == 0) {\n        if (start != -1) result.vertices.push_back(start);\n      \
    \  return result;\n    }\n\n    assert(0 <= start && start < graph.size());\n\
    \    std::vector<char> used(graph.edge_count(), false);\n    std::vector<int>\
    \ cursor(graph.size(), 0);\n    std::vector<int> vertex_stack(1, start);\n   \
    \ std::vector<int> incoming_edge_stack(1, -1);\n    std::vector<int> reversed_vertices;\n\
    \    std::vector<int> reversed_edges;\n    reversed_vertices.reserve(active_edge_count\
    \ + 1);\n    reversed_edges.reserve(active_edge_count);\n\n    while (!vertex_stack.empty())\
    \ {\n        const int vertex = vertex_stack.back();\n        while (cursor[vertex]\
    \ < int(graph[vertex].size())) {\n            const Edge<T>& edge = graph[vertex][cursor[vertex]];\n\
    \            if (edge.alive && !used[edge.id]) break;\n            cursor[vertex]++;\n\
    \        }\n\n        if (cursor[vertex] < int(graph[vertex].size())) {\n    \
    \        const Edge<T>& edge = graph[vertex][cursor[vertex]++];\n            used[edge.id]\
    \ = true;\n            vertex_stack.push_back(edge.to);\n            incoming_edge_stack.push_back(edge.id);\n\
    \            continue;\n        }\n\n        reversed_vertices.push_back(vertex);\n\
    \        const int incoming_edge = incoming_edge_stack.back();\n        if (incoming_edge\
    \ != -1) reversed_edges.push_back(incoming_edge);\n        vertex_stack.pop_back();\n\
    \        incoming_edge_stack.pop_back();\n    }\n\n    if (int(reversed_edges.size())\
    \ != active_edge_count) return std::nullopt;\n    std::reverse(reversed_vertices.begin(),\
    \ reversed_vertices.end());\n    std::reverse(reversed_edges.begin(), reversed_edges.end());\n\
    \    result.vertices = std::move(reversed_vertices);\n    result.edge_ids = std::move(reversed_edges);\n\
    \    return result;\n}\n\ntemplate <class T>\nstd::vector<int> edge_incidence_count(const\
    \ Graph<T>& graph) {\n    std::vector<int> count(graph.edge_count(), 0);\n   \
    \ for (int vertex = 0; vertex < graph.size(); vertex++) {\n        for (const\
    \ Edge<T>& edge : graph[vertex]) {\n            if (!edge.alive) continue;\n \
    \           assert(0 <= edge.id && edge.id < graph.edge_count());\n          \
    \  count[edge.id]++;\n        }\n    }\n    return count;\n}\n\n}  // namespace\
    \ internal\n\ntemplate <class T>\nstd::optional<EulerianTrail> directed_eulerian_trail(\n\
    \    const Graph<T>& graph,\n    int start = -1\n) {\n    assert(start == -1 ||\
    \ (0 <= start && start < graph.size()));\n    const int n = graph.size();\n  \
    \  std::vector<int> incidence = internal::edge_incidence_count(graph);\n    std::vector<int>\
    \ in_degree(n, 0);\n    std::vector<int> out_degree(n, 0);\n    int active_edge_count\
    \ = 0;\n    for (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>&\
    \ edge : graph[vertex]) {\n            if (!edge.alive) continue;\n          \
    \  out_degree[vertex]++;\n            in_degree[edge.to]++;\n        }\n    }\n\
    \    for (int count : incidence) {\n        if (count == 0) continue;\n      \
    \  assert(count == 1);\n        active_edge_count++;\n    }\n\n    int required_start\
    \ = -1;\n    int required_end = -1;\n    for (int vertex = 0; vertex < n; vertex++)\
    \ {\n        const int difference = out_degree[vertex] - in_degree[vertex];\n\
    \        if (difference == 1) {\n            if (required_start != -1) return\
    \ std::nullopt;\n            required_start = vertex;\n        } else if (difference\
    \ == -1) {\n            if (required_end != -1) return std::nullopt;\n       \
    \     required_end = vertex;\n        } else if (difference != 0) {\n        \
    \    return std::nullopt;\n        }\n    }\n    if ((required_start == -1) !=\
    \ (required_end == -1)) return std::nullopt;\n\n    int chosen_start = start;\n\
    \    if (active_edge_count == 0) {\n        if (chosen_start == -1 && n > 0) chosen_start\
    \ = 0;\n        return internal::hierholzer(graph, chosen_start, 0);\n    }\n\
    \    if (required_start != -1) {\n        if (chosen_start != -1 && chosen_start\
    \ != required_start) return std::nullopt;\n        chosen_start = required_start;\n\
    \    } else if (chosen_start == -1) {\n        for (int vertex = 0; vertex < n;\
    \ vertex++) {\n            if (out_degree[vertex] > 0) {\n                chosen_start\
    \ = vertex;\n                break;\n            }\n        }\n    } else if (out_degree[chosen_start]\
    \ == 0) {\n        return std::nullopt;\n    }\n    return internal::hierholzer(graph,\
    \ chosen_start, active_edge_count);\n}\n\ntemplate <class T>\nstd::optional<EulerianTrail>\
    \ undirected_eulerian_trail(\n    const Graph<T>& graph,\n    int start = -1\n\
    ) {\n    assert(start == -1 || (0 <= start && start < graph.size()));\n    const\
    \ int n = graph.size();\n    std::vector<int> incidence = internal::edge_incidence_count(graph);\n\
    \    std::vector<int> degree(n, 0);\n    int active_edge_count = 0;\n    for (int\
    \ vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex])\
    \ {\n            if (edge.alive) degree[vertex]++;\n        }\n    }\n    for\
    \ (int count : incidence) {\n        if (count == 0) continue;\n        assert(count\
    \ == 2);\n        active_edge_count++;\n    }\n\n    std::vector<int> odd;\n \
    \   for (int vertex = 0; vertex < n; vertex++) {\n        if (degree[vertex] &\
    \ 1) odd.push_back(vertex);\n    }\n    if (!odd.empty() && odd.size() != 2) return\
    \ std::nullopt;\n\n    int chosen_start = start;\n    if (active_edge_count ==\
    \ 0) {\n        if (chosen_start == -1 && n > 0) chosen_start = 0;\n        return\
    \ internal::hierholzer(graph, chosen_start, 0);\n    }\n    if (odd.size() ==\
    \ 2) {\n        if (chosen_start != -1 && chosen_start != odd[0] && chosen_start\
    \ != odd[1]) {\n            return std::nullopt;\n        }\n        if (chosen_start\
    \ == -1) chosen_start = odd[0];\n    } else if (chosen_start == -1) {\n      \
    \  for (int vertex = 0; vertex < n; vertex++) {\n            if (degree[vertex]\
    \ > 0) {\n                chosen_start = vertex;\n                break;\n   \
    \         }\n        }\n    } else if (degree[chosen_start] == 0) {\n        return\
    \ std::nullopt;\n    }\n    return internal::hierholzer(graph, chosen_start, active_edge_count);\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/general_matching.hpp\"\
    \n\n\n\n#line 9 \"graph/general_matching.hpp\"\n\n#line 11 \"graph/general_matching.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct GeneralMatching {\n    struct\
    \ Edge {\n        int from;\n        int to;\n        int id;\n        bool alive;\n\
    \n        int other(int v) const {\n            assert(v == from || v == to);\n\
    \            return from ^ to ^ v;\n        }\n    };\n\n    struct Pair {\n \
    \       int from;\n        int to;\n        int edge_id;\n    };\n\n   private:\n\
    \    int _n;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
    \ _adj;\n    std::vector<int> _mate;\n    std::vector<int> _mate_edge;\n    bool\
    \ _calculated;\n\n    void invalidate() {\n        _calculated = false;\n    }\n\
    \n    void ensure_matching() {\n        if (!_calculated) max_matching();\n  \
    \  }\n\n    bool is_matched_edge(int id) const {\n        const auto& e = _edges[id];\n\
    \        return _mate[e.from] == e.to && _mate_edge[e.from] == id;\n    }\n\n\
    \    enum MatchingLabel : char {\n        even_label,\n        odd_label,\n  \
    \      unlabeled\n    };\n\n    struct MutablePartition {\n        std::vector<int>\
    \ parent;\n        std::vector<int> rank;\n        std::vector<int> representative;\n\
    \n        MutablePartition() = default;\n\n        explicit MutablePartition(int\
    \ n) {\n            reset(n);\n        }\n\n        void reset(int n) {\n    \
    \        parent.resize(n);\n            rank.assign(n, 0);\n            representative.resize(n);\n\
    \            for (int i = 0; i < n; i++) {\n                parent[i] = i;\n \
    \               representative[i] = i;\n            }\n        }\n\n        int\
    \ root(int v) {\n            if (parent[v] == v) return v;\n            return\
    \ parent[v] = root(parent[v]);\n        }\n\n        int operator()(int v) {\n\
    \            return representative[root(v)];\n        }\n\n        void unite(int\
    \ a, int b) {\n            int ra = root(a);\n            int rb = root(b);\n\
    \            if (ra == rb) return;\n            if (rank[ra] < rank[rb]) std::swap(ra,\
    \ rb);\n            parent[rb] = ra;\n            if (rank[ra] == rank[rb]) rank[ra]++;\n\
    \        }\n\n        void make_rep(int v) {\n            representative[root(v)]\
    \ = v;\n        }\n    };\n\n    struct EdgeBucketQueue {\n        std::vector<std::vector<int>>\
    \ bucket;\n        std::vector<int> head;\n\n        void reset(int n) {\n   \
    \         bucket.assign(n + 3, {});\n            head.assign(n + 3, 0);\n    \
    \    }\n\n        void insert(int edge_id, int key) {\n            if (key < 0\
    \ || int(bucket.size()) <= key) return;\n            bucket[key].push_back(edge_id);\n\
    \        }\n\n        int pop(int key) {\n            if (key < 0 || int(bucket.size())\
    \ <= key) return -1;\n            if (head[key] == int(bucket[key].size())) return\
    \ -1;\n            return bucket[key][head[key]++];\n        }\n    };\n\n   \
    \ struct NewMatchingPair {\n        int from;\n        int to;\n        int edge_id;\n\
    \    };\n\n    // General-graph shortest augmenting path phase solver.\n    struct\
    \ MicaliVaziraniSolver {\n        GeneralMatching& graph;\n        int n;\n  \
    \      int matching_size;\n        int delta;\n        int visit_token;\n    \
    \    int even_time_token;\n        MutablePartition base;\n        MutablePartition\
    \ delayed_base;\n        EdgeBucketQueue queue;\n        std::vector<MatchingLabel>\
    \ label;\n        std::vector<MatchingLabel> h_label;\n        std::vector<int>\
    \ parent;\n        std::vector<int> parent_edge;\n        std::vector<int> source_bridge;\n\
    \        std::vector<int> target_bridge;\n        std::vector<int> bridge_edge;\n\
    \        std::vector<int> lcp;\n        std::vector<int> path_mark_1;\n      \
    \  std::vector<int> path_mark_2;\n        std::vector<int> restore_vertex;\n \
    \       std::vector<int> restore_value;\n        std::vector<int> rep;\n     \
    \   std::vector<int> h_mate;\n        std::vector<char> is_h_edge;\n        std::vector<std::vector<int>>\
    \ contracted_into;\n        std::vector<int> h_parent_edge;\n        std::vector<int>\
    \ h_even_time;\n        std::vector<int> h_bridge_edge;\n        std::vector<int>\
    \ h_bridge_dir;\n\n        explicit MicaliVaziraniSolver(GeneralMatching& graph_)\n\
    \            : graph(graph_),\n              n(graph_._n),\n              matching_size(0),\n\
    \              delta(0),\n              visit_token(0),\n              even_time_token(0),\n\
    \              base(n),\n              delayed_base(n),\n              label(n,\
    \ unlabeled),\n              h_label(n, unlabeled),\n              parent(n, -1),\n\
    \              parent_edge(n, -1),\n              source_bridge(n, -1),\n    \
    \          target_bridge(n, -1),\n              bridge_edge(n, -1),\n        \
    \      lcp(n, 0),\n              path_mark_1(n, 0),\n              path_mark_2(n,\
    \ 0),\n              rep(n, -1),\n              h_mate(n, -1),\n             \
    \ is_h_edge(graph_._edges.size(), false),\n              contracted_into(n),\n\
    \              h_parent_edge(n, -1),\n              h_even_time(n, 0),\n     \
    \         h_bridge_edge(n, -1),\n              h_bridge_dir(n, 0) {}\n\n     \
    \   bool active(int edge_id) const {\n            return graph._edges[edge_id].alive;\n\
    \        }\n\n        int other(int edge_id, int v) const {\n            return\
    \ graph._edges[edge_id].other(v);\n        }\n\n        int edge_weight(int edge_id)\
    \ const {\n            return graph.is_matched_edge(edge_id) ? 2 : 0;\n      \
    \  }\n\n        void set_match(int edge_id) {\n            const auto& e = graph._edges[edge_id];\n\
    \            graph._mate[e.from] = e.to;\n            graph._mate[e.to] = e.from;\n\
    \            graph._mate_edge[e.from] = edge_id;\n            graph._mate_edge[e.to]\
    \ = edge_id;\n        }\n\n        void initialize_greedy_matching() {\n     \
    \       graph._mate.assign(n, -1);\n            graph._mate_edge.assign(n, -1);\n\
    \            matching_size = 0;\n            for (const auto& e : graph._edges)\
    \ {\n                if (!e.alive) continue;\n                if (graph._mate[e.from]\
    \ != -1 || graph._mate[e.to] != -1) continue;\n                set_match(e.id);\n\
    \                matching_size++;\n            }\n        }\n\n        void scan_edge(int\
    \ edge_id, int from) {\n            if (!active(edge_id)) return;\n          \
    \  int to = other(edge_id, from);\n            if (to == from || graph._mate[to]\
    \ == from || label[base(to)] == odd_label) return;\n            if (label[to]\
    \ == unlabeled) {\n                queue.insert(edge_id, lcp[from] + 2);\n   \
    \         } else {\n                queue.insert(edge_id, (lcp[from] + lcp[to])\
    \ / 2 + 1);\n            }\n        }\n\n        void shrink_path(int blossom_base,\
    \ int x, int y, int edge_id,\n                         std::vector<std::pair<int,\
    \ int>>& delayed_unions) {\n            int v = base(x);\n            while (v\
    \ != blossom_base) {\n                base.unite(v, blossom_base);\n         \
    \       delayed_unions.push_back({v, blossom_base});\n\n                v = graph._mate[v];\n\
    \                assert(v != -1);\n                base.unite(v, blossom_base);\n\
    \                delayed_unions.push_back({v, blossom_base});\n              \
    \  base.make_rep(blossom_base);\n\n                source_bridge[v] = x;\n   \
    \             target_bridge[v] = y;\n                bridge_edge[v] = edge_id;\n\
    \                restore_vertex.push_back(v);\n                restore_value.push_back(lcp[v]);\n\
    \                lcp[v] = lcp[x] + lcp[y] - lcp[graph._mate[v]] + 2;\n\n     \
    \           for (int id : graph._adj[v]) scan_edge(id, v);\n                assert(parent[v]\
    \ != -1);\n                v = base(parent[v]);\n            }\n            delayed_unions.push_back({blossom_base,\
    \ blossom_base});\n        }\n\n        void build_phase_graph() {\n         \
    \   std::fill(h_mate.begin(), h_mate.end(), -1);\n            std::fill(is_h_edge.begin(),\
    \ is_h_edge.end(), false);\n            for (auto& vertices : contracted_into)\
    \ vertices.clear();\n\n            for (int v = 0; v < n; v++) contracted_into[delayed_base(v)].push_back(v);\n\
    \n            for (const auto& e : graph._edges) {\n                if (!e.alive)\
    \ continue;\n                int u = e.from;\n                int v = e.to;\n\
    \                int uh = delayed_base(u);\n                int vh = delayed_base(v);\n\
    \                if (uh == vh) continue;\n                if (label[uh] == odd_label\
    \ && label[vh] == odd_label) continue;\n\n                int w = edge_weight(e.id);\n\
    \                bool even_odd =\n                    (label[uh] == even_label\
    \ && label[vh] == odd_label && lcp[v] == lcp[u] + 1 - w) ||\n                \
    \    (label[vh] == even_label && label[uh] == odd_label && lcp[u] == lcp[v] +\
    \ 1 - w);\n                bool unlabeled_unlabeled = label[uh] == unlabeled &&\
    \ label[vh] == unlabeled && w == 2;\n                bool even_unlabeled =\n \
    \                   (label[uh] == even_label && label[vh] == unlabeled && lcp[u]\
    \ == delta - 2) ||\n                    (label[vh] == even_label && label[uh]\
    \ == unlabeled && lcp[v] == delta - 2);\n                bool even_even = label[uh]\
    \ == even_label && label[vh] == even_label;\n                bool tight_even_even\
    \ = even_even && lcp[u] + lcp[v] == 2 * delta + w - 2;\n\n                if (even_odd\
    \ || unlabeled_unlabeled || even_unlabeled || tight_even_even) {\n           \
    \         is_h_edge[e.id] = true;\n                    if (w == 2) {\n       \
    \                 h_mate[uh] = vh;\n                        h_mate[vh] = uh;\n\
    \                    }\n                }\n            }\n        }\n\n      \
    \  bool phase_one() {\n            delta = 0;\n            base.reset(n);\n  \
    \          delayed_base.reset(n);\n            queue.reset(n);\n            std::fill(label.begin(),\
    \ label.end(), unlabeled);\n            std::fill(parent.begin(), parent.end(),\
    \ -1);\n            std::fill(parent_edge.begin(), parent_edge.end(), -1);\n \
    \           std::fill(source_bridge.begin(), source_bridge.end(), -1);\n     \
    \       std::fill(target_bridge.begin(), target_bridge.end(), -1);\n         \
    \   std::fill(bridge_edge.begin(), bridge_edge.end(), -1);\n            std::fill(lcp.begin(),\
    \ lcp.end(), 0);\n\n            for (int v = 0; v < n; v++) {\n              \
    \  if (graph._mate[v] == -1) label[v] = even_label;\n            }\n         \
    \   for (int v = 0; v < n; v++) {\n                if (label[v] != even_label)\
    \ continue;\n                for (int id : graph._adj[v]) scan_edge(id, v);\n\
    \            }\n\n            std::vector<std::pair<int, int>> delayed_unions;\n\
    \            while (delta <= n + 1) {\n                restore_vertex.clear();\n\
    \                restore_value.clear();\n\n                while (true) {\n  \
    \                  int edge_id = queue.pop(delta);\n                    if (edge_id\
    \ == -1) break;\n                    if (!active(edge_id)) continue;\n\n     \
    \               int x = graph._edges[edge_id].from;\n                    int y\
    \ = graph._edges[edge_id].to;\n                    if (label[base(x)] != even_label)\
    \ std::swap(x, y);\n                    if (label[base(x)] != even_label) continue;\n\
    \                    if (graph._mate[x] == y || base(x) == base(y) || label[base(y)]\
    \ == odd_label) continue;\n\n                    if (label[base(y)] == unlabeled)\
    \ {\n                        int z = graph._mate[y];\n                       \
    \ assert(z != -1);\n                        lcp[y] = lcp[x] + 1;\n           \
    \             lcp[z] = lcp[x] + 2;\n                        parent[y] = x;\n \
    \                       parent_edge[y] = edge_id;\n                        parent[z]\
    \ = y;\n                        parent_edge[z] = graph._mate_edge[z];\n      \
    \                  label[y] = odd_label;\n                        label[z] = even_label;\n\
    \                        for (int id : graph._adj[z]) scan_edge(id, z);\n    \
    \                    continue;\n                    }\n\n                    if\
    \ (label[base(y)] != even_label || lcp[x] + lcp[y] != 2 * delta - 2) continue;\n\
    \n                    ++visit_token;\n                    int hx = base(x);\n\
    \                    int hy = base(y);\n                    path_mark_1[hx] =\
    \ visit_token;\n                    path_mark_2[hy] = visit_token;\n         \
    \           while (path_mark_1[hy] != visit_token && path_mark_2[hx] != visit_token\
    \ &&\n                           (graph._mate[hx] != -1 || graph._mate[hy] !=\
    \ -1)) {\n                        if (graph._mate[hx] != -1) {\n             \
    \               assert(parent[graph._mate[hx]] != -1);\n                     \
    \       hx = base(parent[graph._mate[hx]]);\n                            path_mark_1[hx]\
    \ = visit_token;\n                        }\n                        if (graph._mate[hy]\
    \ != -1) {\n                            assert(parent[graph._mate[hy]] != -1);\n\
    \                            hy = base(parent[graph._mate[hy]]);\n           \
    \                 path_mark_2[hy] = visit_token;\n                        }\n\
    \                    }\n\n                    if (path_mark_1[hy] == visit_token\
    \ || path_mark_2[hx] == visit_token) {\n                        int blossom_base\
    \ = path_mark_1[hy] == visit_token ? hy : hx;\n                        shrink_path(blossom_base,\
    \ x, y, edge_id, delayed_unions);\n                        shrink_path(blossom_base,\
    \ y, x, edge_id, delayed_unions);\n                    } else {\n            \
    \            for (int i = int(restore_vertex.size()) - 1; i >= 0; i--) {\n   \
    \                         lcp[restore_vertex[i]] = restore_value[i];\n       \
    \                 }\n                        build_phase_graph();\n          \
    \              return true;\n                    }\n                }\n\n    \
    \            for (auto [a, b] : delayed_unions) {\n                    if (a ==\
    \ b) {\n                        delayed_base.make_rep(a);\n                  \
    \  } else {\n                        delayed_base.unite(a, b);\n             \
    \       }\n                }\n                delayed_unions.clear();\n      \
    \          delta++;\n            }\n            return false;\n        }\n\n \
    \       int next_h_vertex_through_edge(int edge_id, int current_h) const {\n \
    \           const auto& e = graph._edges[edge_id];\n            return rep[rep[e.from]\
    \ == current_h ? e.to : e.from];\n        }\n\n        int find_path_in_h(int\
    \ h_vertex) {\n            for (int v : contracted_into[h_vertex]) {\n       \
    \         for (int edge_id : graph._adj[v]) {\n                    if (!is_h_edge[edge_id])\
    \ continue;\n                    int uh = rep[other(edge_id, v)];\n          \
    \          if (h_mate[h_vertex] == uh) continue;\n\n                    if (h_label[uh]\
    \ == unlabeled) {\n                        int mate_uh = h_mate[uh];\n       \
    \                 h_label[uh] = odd_label;\n                        h_parent_edge[uh]\
    \ = edge_id;\n                        if (mate_uh == -1) return uh;\n\n      \
    \                  h_label[mate_uh] = even_label;\n                        h_even_time[mate_uh]\
    \ = even_time_token++;\n                        int found = find_path_in_h(mate_uh);\n\
    \                        if (found != -1) return found;\n                    }\
    \ else {\n                        int bh = delayed_base(h_vertex);\n         \
    \               int zh = delayed_base(uh);\n                        if (h_even_time[bh]\
    \ >= h_even_time[zh]) continue;\n\n                        std::vector<int> blossom_path;\n\
    \                        std::vector<int> blossom_vertices;\n                \
    \        while (zh != bh) {\n                            blossom_vertices.push_back(zh);\n\
    \                            zh = h_mate[zh];\n                            assert(zh\
    \ != -1);\n                            blossom_vertices.push_back(zh);\n     \
    \                       blossom_path.push_back(zh);\n                        \
    \    assert(h_parent_edge[zh] != -1);\n                            zh = delayed_base(next_h_vertex_through_edge(h_parent_edge[zh],\
    \ zh));\n                        }\n\n                        for (int x : blossom_vertices)\
    \ delayed_base.unite(x, bh);\n                        delayed_base.make_rep(bh);\n\
    \n                        std::reverse(blossom_path.begin(), blossom_path.end());\n\
    \                        for (int x : blossom_path) {\n                      \
    \      h_bridge_edge[x] = edge_id;\n                            h_bridge_dir[x]\
    \ = graph._edges[edge_id].to == v ? 1 : -1;\n                        }\n     \
    \                   for (int x : blossom_path) {\n                           \
    \ int found = find_path_in_h(x);\n                            if (found != -1)\
    \ return found;\n                        }\n                    }\n          \
    \      }\n            }\n            return -1;\n        }\n\n        void collect_path_in_h(std::vector<int>&\
    \ path, int from_h, int to_h) {\n            if (from_h == to_h) return;\n   \
    \         if (h_label[from_h] == even_label) {\n                int mate_from\
    \ = h_mate[from_h];\n                assert(mate_from != -1);\n              \
    \  int edge_id = h_parent_edge[mate_from];\n                assert(edge_id !=\
    \ -1);\n                path.push_back(edge_id);\n                collect_path_in_h(path,\
    \ next_h_vertex_through_edge(edge_id, mate_from), to_h);\n            } else {\n\
    \                int edge_id = h_bridge_edge[from_h];\n                assert(edge_id\
    \ != -1);\n                const auto& e = graph._edges[edge_id];\n          \
    \      int first = rep[h_bridge_dir[from_h] == 1 ? e.from : e.to];\n         \
    \       int second = rep[h_bridge_dir[from_h] == 1 ? e.to : e.from];\n       \
    \         collect_path_in_h(path, first, rep[h_mate[from_h]]);\n             \
    \   path.push_back(edge_id);\n                collect_path_in_h(path, second,\
    \ to_h);\n            }\n        }\n\n        void add_new_pair(std::vector<NewMatchingPair>&\
    \ pairs, int from, int to, int edge_id) const {\n            const auto& e = graph._edges[edge_id];\n\
    \            assert(e.alive);\n            assert((e.from == from && e.to == to)\
    \ || (e.from == to && e.to == from));\n            pairs.push_back(NewMatchingPair{from,\
    \ to, edge_id});\n        }\n\n        void collect_path_in_graph(std::vector<NewMatchingPair>&\
    \ pairs, int from, int to) {\n            if (from == to) return;\n          \
    \  if (label[from] == even_label) {\n                int mate_from = graph._mate[from];\n\
    \                assert(mate_from != -1);\n                int parent_of_mate\
    \ = parent[mate_from];\n                int edge_id = parent_edge[mate_from];\n\
    \                assert(parent_of_mate != -1 && edge_id != -1);\n            \
    \    add_new_pair(pairs, mate_from, parent_of_mate, edge_id);\n              \
    \  collect_path_in_graph(pairs, parent_of_mate, to);\n            } else {\n \
    \               assert(source_bridge[from] != -1 && target_bridge[from] != -1\
    \ && bridge_edge[from] != -1);\n                collect_path_in_graph(pairs, source_bridge[from],\
    \ graph._mate[from]);\n                add_new_pair(pairs, source_bridge[from],\
    \ target_bridge[from], bridge_edge[from]);\n                collect_path_in_graph(pairs,\
    \ target_bridge[from], to);\n            }\n        }\n\n        void augment_path(const\
    \ std::vector<int>& h_path) {\n            std::vector<NewMatchingPair> pairs;\n\
    \            for (int edge_id : h_path) {\n                const auto& e = graph._edges[edge_id];\n\
    \                add_new_pair(pairs, e.from, e.to, edge_id);\n               \
    \ collect_path_in_graph(pairs, e.from, rep[e.from]);\n                collect_path_in_graph(pairs,\
    \ e.to, rep[e.to]);\n            }\n\n            for (const auto& p : pairs)\
    \ {\n                if (graph._mate[p.from] != -1) {\n                    int\
    \ old = graph._mate[p.from];\n                    graph._mate[old] = -1;\n   \
    \                 graph._mate_edge[old] = -1;\n                }\n           \
    \     if (graph._mate[p.to] != -1) {\n                    int old = graph._mate[p.to];\n\
    \                    graph._mate[old] = -1;\n                    graph._mate_edge[old]\
    \ = -1;\n                }\n                graph._mate[p.from] = graph._mate[p.to]\
    \ = -1;\n                graph._mate_edge[p.from] = graph._mate_edge[p.to] = -1;\n\
    \            }\n            for (const auto& p : pairs) {\n                assert(graph._mate[p.from]\
    \ == -1 && graph._mate[p.to] == -1);\n                graph._mate[p.from] = p.to;\n\
    \                graph._mate[p.to] = p.from;\n                graph._mate_edge[p.from]\
    \ = p.edge_id;\n                graph._mate_edge[p.to] = p.edge_id;\n        \
    \    }\n            matching_size++;\n        }\n\n        void phase_two() {\n\
    \            std::fill(h_label.begin(), h_label.end(), unlabeled);\n         \
    \   std::fill(h_parent_edge.begin(), h_parent_edge.end(), -1);\n            std::fill(h_bridge_edge.begin(),\
    \ h_bridge_edge.end(), -1);\n            std::fill(h_bridge_dir.begin(), h_bridge_dir.end(),\
    \ 0);\n            for (int v = 0; v < n; v++) rep[v] = delayed_base(v);\n\n \
    \           std::vector<std::vector<int>> paths;\n            for (int h_vertex\
    \ = 0; h_vertex < n; h_vertex++) {\n                if (rep[h_vertex] != h_vertex)\
    \ continue;\n                if (h_label[h_vertex] != unlabeled || h_mate[h_vertex]\
    \ != -1) continue;\n\n                h_label[h_vertex] = even_label;\n      \
    \          h_even_time[h_vertex] = even_time_token++;\n                int free_h\
    \ = find_path_in_h(h_vertex);\n                if (free_h == -1) continue;\n\n\
    \                std::vector<int> path;\n                int edge_id = h_parent_edge[free_h];\n\
    \                assert(edge_id != -1);\n                path.push_back(edge_id);\n\
    \                collect_path_in_h(path, next_h_vertex_through_edge(edge_id, free_h),\
    \ h_vertex);\n                paths.push_back(path);\n            }\n\n      \
    \      assert(!paths.empty());\n            for (const auto& path : paths) augment_path(path);\n\
    \            for (auto& vertices : contracted_into) vertices.clear();\n      \
    \  }\n\n        int solve() {\n            initialize_greedy_matching();\n   \
    \         while (phase_one()) phase_two();\n            return matching_size;\n\
    \        }\n    };\n\n   public:\n    GeneralMatching() : GeneralMatching(0) {}\n\
    \n    explicit GeneralMatching(int n) : _n(n), _adj(n), _mate(n, -1), _mate_edge(n,\
    \ -1), _calculated(false) {\n        assert(0 <= n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    int edge_count() const {\n       \
    \ return int(_edges.size());\n    }\n\n    int add_edge(int from, int to) {\n\
    \        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(from != to);\n        int id = int(_edges.size());\n        _edges.push_back(Edge{from,\
    \ to, id, true});\n        _adj[from].push_back(id);\n        _adj[to].push_back(id);\n\
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
    \ _edges[id].alive;\n    }\n\n    int max_matching() {\n        MicaliVaziraniSolver\
    \ solver(*this);\n        int result = solver.solve();\n\n        _calculated\
    \ = true;\n        return result;\n    }\n\n    int matching_size() {\n      \
    \  ensure_matching();\n        int result = 0;\n        for (int v = 0; v < _n;\
    \ v++) {\n            if (v < _mate[v]) result++;\n        }\n        return result;\n\
    \    }\n\n    std::vector<int> mate() {\n        ensure_matching();\n        return\
    \ _mate;\n    }\n\n    std::vector<int> mate_edge() {\n        ensure_matching();\n\
    \        return _mate_edge;\n    }\n\n    std::vector<Pair> matching() {\n   \
    \     ensure_matching();\n        std::vector<Pair> result;\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (v < _mate[v]) result.push_back(Pair{v,\
    \ _mate[v], _mate_edge[v]});\n        }\n        return result;\n    }\n\n   \
    \ std::optional<std::vector<int>> minimum_edge_cover() {\n        ensure_matching();\n\
    \n        std::vector<int> result;\n        std::vector<char> covered(_n, false),\
    \ used_edge(_edges.size(), false);\n\n        auto use_edge = [&](int id) {\n\
    \            if (used_edge[id]) return;\n            used_edge[id] = true;\n \
    \           result.push_back(id);\n            covered[_edges[id].from] = true;\n\
    \            covered[_edges[id].to] = true;\n        };\n\n        for (int v\
    \ = 0; v < _n; v++) {\n            if (v < _mate[v]) use_edge(_mate_edge[v]);\n\
    \        }\n\n        for (int v = 0; v < _n; v++) {\n            if (covered[v])\
    \ continue;\n            int id = -1;\n            for (int edge_id : _adj[v])\
    \ {\n                if (_edges[edge_id].alive) {\n                    id = edge_id;\n\
    \                    break;\n                }\n            }\n            if\
    \ (id == -1) return std::nullopt;\n            use_edge(id);\n        }\n\n  \
    \      return result;\n    }\n};\n\nstruct GeneralMatchingGraph {\n    GeneralMatching\
    \ matching;\n    std::vector<int> original_edge_id;\n\n    int original_edge(int\
    \ edge_id) const {\n        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));\n\
    \        return original_edge_id[edge_id];\n    }\n};\n\ntemplate <class T>\n\
    GeneralMatchingGraph make_general_matching(const Graph<T>& g) {\n    GeneralMatchingGraph\
    \ result;\n    result.matching = GeneralMatching(g.size());\n    for (const auto&\
    \ e : g.edges()) {\n        int id = result.matching.add_edge(e.from, e.to);\n\
    \        if (int(result.original_edge_id.size()) <= id) result.original_edge_id.resize(id\
    \ + 1);\n        result.original_edge_id[id] = e.id;\n    }\n    return result;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/general_weighted_matching.hpp\"\
    \n\n\n\n#line 7 \"graph/general_weighted_matching.hpp\"\n#include <functional>\n\
    #line 10 \"graph/general_weighted_matching.hpp\"\n#include <type_traits>\n#line\
    \ 13 \"graph/general_weighted_matching.hpp\"\n\n#line 15 \"graph/general_weighted_matching.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\nnamespace internal {\n\n// Primal-dual\
    \ weighted blossom algorithm using Gabow's event queues.\n// Reference: H. N.\
    \ Gabow, \"Data Structures for Weighted Matching and\n// Extensions to b-matching\
    \ and f-factors\", 2016.\n// Vertices 1..n are atoms; larger indices represent\
    \ contracted blossoms.\ntemplate <class Cost, class TotalCost>\nclass WeightedBlossomSolver\
    \ {\n   public:\n    using cost_type = Cost;\n    using total_type = TotalCost;\n\
    \n   private:\n    enum BlossomLabel : int {\n        separated_label = -2,\n\
    \        inner_label = -1,\n        free_label = 0,\n        outer_label = 1\n\
    \    };\n    static constexpr cost_type infinity = cost_type(1) << (sizeof(cost_type)\
    \ * 8 - 2);\n\n    template <class T>\n    class MutableBinaryHeap {\n       public:\n\
    \        struct Node {\n            bool operator<(const Node& rhs) const {\n\
    \                if (value < rhs.value) {\n                    return true;\n\
    \                }\n                if (rhs.value < value) {\n               \
    \     return false;\n                }\n                return id < rhs.id;\n\
    \            }\n            T value;\n            int id;\n        };\n\n    \
    \    MutableBinaryHeap() = default;\n        explicit MutableBinaryHeap(int capacity)\
    \ : _size(0), _nodes(capacity + 1), _position(capacity, 0) {\n        }\n\n  \
    \      bool empty() const {\n            return _size == 0;\n        }\n     \
    \   void clear() {\n            while (_size > 0) {\n                _position[_nodes[_size].id]\
    \ = 0;\n                _size--;\n            }\n        }\n        T min() const\
    \ {\n            return _nodes[1].value;\n        }\n        int argmin() const\
    \ {\n            return _nodes[1].id;\n        }\n        void pop() {\n     \
    \       if (_size > 0) pop(1);\n        }\n        void erase(int id) {\n    \
    \        if (_position[id]) pop(_position[id]);\n        }\n        bool has(int\
    \ id) const {\n            return _position[id] != 0;\n        }\n        void\
    \ update(int id, T v) {\n            if (!has(id)) return push(id, v);\n     \
    \       bool up = (v < _nodes[_position[id]].value);\n            _nodes[_position[id]].value\
    \ = v;\n            if (up) {\n                up_heap(_position[id]);\n     \
    \       } else {\n                down_heap(_position[id]);\n            }\n \
    \       }\n        void decrease_key(int id, T v) {\n            if (!has(id))\
    \ return push(id, v);\n            if (v < _nodes[_position[id]].value) {\n  \
    \              _nodes[_position[id]].value = v;\n                up_heap(_position[id]);\n\
    \            }\n        }\n        void push(int id, T v) {\n            _position[id]\
    \ = ++_size;\n            _nodes[_size] = {v, id};\n            up_heap(_size);\n\
    \        }\n\n       private:\n        void pop(int pos) {\n            _position[_nodes[pos].id]\
    \ = 0;\n            if (pos == _size) {\n                --_size;\n          \
    \      return;\n            }\n            bool up = (_nodes[_size].value < _nodes[pos].value);\n\
    \            _nodes[pos] = _nodes[_size--];\n            _position[_nodes[pos].id]\
    \ = pos;\n            if (up) {\n                up_heap(pos);\n            }\
    \ else {\n                down_heap(pos);\n            }\n        }\n        void\
    \ swap_node(int a, int b) {\n            std::swap(_nodes[a], _nodes[b]);\n  \
    \          _position[_nodes[a].id] = a;\n            _position[_nodes[b].id] =\
    \ b;\n        }\n        void down_heap(int pos) {\n            for (int current\
    \ = pos;;) {\n                int next = current;\n                if (2 * current\
    \ <= _size && _nodes[2 * current] < _nodes[next]) {\n                    next\
    \ = 2 * current;\n                }\n                if (2 * current + 1 <= _size\
    \ && _nodes[2 * current + 1] < _nodes[next]) {\n                    next = 2 *\
    \ current + 1;\n                }\n                if (next == current) break;\n\
    \                swap_node(current, next);\n                current = next;\n\
    \            }\n        }\n        void up_heap(int pos) {\n            for (int\
    \ current = pos; current > 1 && _nodes[current] < _nodes[current >> 1]; current\
    \ >>= 1) {\n                swap_node(current, current >> 1);\n            }\n\
    \        }\n        int _size;\n        std::vector<Node> _nodes;\n        std::vector<int>\
    \ _position;\n    };\n\n    template <class Key>\n    class DisjointPairingHeaps\
    \ {\n       private:\n        struct Node {\n            Node() : key(), child(0),\
    \ next(0), prev(-1) {\n            }\n            explicit Node(Key value) : key(value),\
    \ child(0), next(0), prev(0) {\n            }\n            Key key;\n        \
    \    int child;\n            int next;\n            int prev;\n        };\n\n\
    \       public:\n        DisjointPairingHeaps(int heap_count, int node_count)\
    \ : _roots(heap_count), _nodes(node_count) {\n        }\n\n        void clear(int\
    \ h) {\n            if (_roots[h]) {\n                clear_rec(_roots[h]);\n\
    \                _roots[h] = 0;\n            }\n        }\n        bool empty(int\
    \ h) const {\n            return !_roots[h];\n        }\n        bool used(int\
    \ v) const {\n            return _nodes[v].prev >= 0;\n        }\n        Key\
    \ min(int h) const {\n            return _nodes[_roots[h]].key;\n        }\n \
    \       void push(int h, int v, Key key) {\n            _nodes[v] = Node(key);\n\
    \            _roots[h] = merge(_roots[h], v);\n        }\n        void erase(int\
    \ h, int v) {\n            if (!used(v)) return;\n            int w = two_pass_pairing(_nodes[v].child);\n\
    \            if (!_nodes[v].prev) {\n                _roots[h] = w;\n        \
    \    } else {\n                cut(v);\n                _roots[h] = merge(_roots[h],\
    \ w);\n            }\n            _nodes[v].prev = -1;\n        }\n        void\
    \ decrease_key(int h, int v, Key key) {\n            if (!used(v)) return push(h,\
    \ v, key);\n            if (!_nodes[v].prev) {\n                _nodes[v].key\
    \ = key;\n            } else {\n                cut(v);\n                _nodes[v].key\
    \ = key;\n                _roots[h] = merge(_roots[h], v);\n            }\n  \
    \      }\n\n       private:\n        void clear_rec(int v) {\n            for\
    \ (; v; v = _nodes[v].next) {\n                if (_nodes[v].child) clear_rec(_nodes[v].child);\n\
    \                _nodes[v].prev = -1;\n            }\n        }\n\n        inline\
    \ void cut(int v) {\n            auto& n = _nodes[v];\n            int previous\
    \ = n.prev;\n            int next = n.next;\n            auto& previous_node =\
    \ _nodes[previous];\n            if (previous_node.child == v) {\n           \
    \     previous_node.child = next;\n            } else {\n                previous_node.next\
    \ = next;\n            }\n            _nodes[next].prev = previous;\n        \
    \    n.next = n.prev = 0;\n        }\n\n        int merge(int l, int r) {\n  \
    \          if (!l) return r;\n            if (!r) return l;\n            if (_nodes[l].key\
    \ > _nodes[r].key) std::swap(l, r);\n            int lc = _nodes[r].next = _nodes[l].child;\n\
    \            _nodes[l].child = _nodes[lc].prev = r;\n            return _nodes[r].prev\
    \ = l;\n        }\n\n        int two_pass_pairing(int root) {\n            if\
    \ (!root) return 0;\n            int a = root;\n            root = 0;\n      \
    \      while (a) {\n                int b = _nodes[a].next;\n                int\
    \ next_a = 0;\n                _nodes[a].prev = _nodes[a].next = 0;\n        \
    \        if (b) {\n                    next_a = _nodes[b].next;\n            \
    \        _nodes[b].prev = _nodes[b].next = 0;\n                }\n           \
    \     a = merge(a, b);\n                _nodes[a].next = root;\n             \
    \   root = a;\n                a = next_a;\n            }\n            int s =\
    \ _nodes[root].next;\n            _nodes[root].next = 0;\n            while (s)\
    \ {\n                int t = _nodes[s].next;\n                _nodes[s].next =\
    \ 0;\n                root = merge(root, s);\n                s = t;\n       \
    \     }\n            return root;\n        }\n\n       private:\n        std::vector<int>\
    \ _roots;\n        std::vector<Node> _nodes;\n    };\n\n    template <class T>\n\
    \    struct ReservablePriorityQueue : public std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>> {\n        ReservablePriorityQueue() = default;\n        explicit\
    \ ReservablePriorityQueue(int capacity) {\n            this->c.reserve(capacity);\n\
    \        }\n        T min() const {\n            return this->top();\n       \
    \ }\n        void clear() {\n            this->c.clear();\n        }\n    };\n\
    \n    template <class T>\n    struct FixedQueue {\n        FixedQueue() = default;\n\
    \        explicit FixedQueue(int capacity) : _head(0), _tail(0), _data(capacity)\
    \ {\n        }\n        void enqueue(int u) {\n            _data[_tail++] = u;\n\
    \        }\n        int dequeue() {\n            return _data[_head++];\n    \
    \    }\n        bool empty() const {\n            return _head == _tail;\n   \
    \     }\n        void clear() {\n            _head = _tail = 0;\n        }\n \
    \       int _head = 0;\n        int _tail = 0;\n        std::vector<T> _data;\n\
    \    };\n\n   public:\n    struct InputEdge {\n        int from;\n        int\
    \ to;\n        cost_type cost;\n    };\n\n   private:\n    struct SolverEdge {\n\
    \        int to;\n        cost_type cost;\n    };\n\n    struct BlossomLink {\n\
    \        int from;\n        int to;\n    };\n\n    struct BlossomNode {\n    \
    \    struct CycleLink {\n            int blossom;\n            int vertex;\n \
    \       };\n\n        BlossomNode() = default;\n        explicit BlossomNode(int\
    \ vertex) : parent(0), size(1) {\n            cycle[0] = cycle[1] = CycleLink{vertex,\
    \ vertex};\n        }\n\n        int next_v() const {\n            return cycle[0].vertex;\n\
    \        }\n        int next_b() const {\n            return cycle[0].blossom;\n\
    \        }\n        int prev_v() const {\n            return cycle[1].vertex;\n\
    \        }\n        int prev_b() const {\n            return cycle[1].blossom;\n\
    \        }\n\n        int parent = 0;\n        int size = 0;\n        CycleLink\
    \ cycle[2];\n    };\n\n    struct VertexEvent {\n        VertexEvent() = default;\n\
    \        VertexEvent(cost_type event_time, int vertex) : time(event_time), id(vertex)\
    \ {\n        }\n\n        bool operator<(const VertexEvent& rhs) const {\n   \
    \         if (time < rhs.time) {\n                return true;\n            }\n\
    \            if (rhs.time < time) {\n                return false;\n         \
    \   }\n            return id < rhs.id;\n        }\n        bool operator>(const\
    \ VertexEvent& rhs) const {\n            return rhs < *this;\n        }\n\n  \
    \      cost_type time = cost_type();\n        int id = 0;\n    };\n\n    struct\
    \ EdgeEvent {\n        EdgeEvent() = default;\n        EdgeEvent(cost_type event_time,\
    \ int from_, int to_) : time(event_time), from(from_), to(to_) {\n        }\n\n\
    \        bool operator<(const EdgeEvent& rhs) const {\n            if (time <\
    \ rhs.time) {\n                return true;\n            }\n            if (time\
    \ > rhs.time) {\n                return false;\n            }\n            return\
    \ std::make_pair(from, to) < std::make_pair(rhs.from, rhs.to);\n        }\n  \
    \      bool operator>(const EdgeEvent& rhs) const {\n            return rhs <\
    \ *this;\n        }\n\n        cost_type time = cost_type();\n        int from\
    \ = 0;\n        int to = 0;\n    };\n\n   public:\n    WeightedBlossomSolver(int\
    \ n, const std::vector<InputEdge>& input_edges)\n        : _vertex_count(n),\n\
    \          _blossom_count((n - 1) / 2),\n          _state_count(n + _blossom_count\
    \ + 1),\n          _offset(n + 2),\n          _edges(input_edges.size() * 2),\n\
    \          _grow_heap(_state_count),\n          _blossom_grow_heaps(_state_count,\
    \ _state_count),\n          _contract_heap(int(_edges.size())),\n          _expand_heap(_state_count)\
    \ {\n        for (const InputEdge& edge : input_edges) {\n            _offset[edge.from\
    \ + 1]++;\n            _offset[edge.to + 1]++;\n        }\n        for (int i\
    \ = 1; i <= _vertex_count + 1; i++) _offset[i] += _offset[i - 1];\n        for\
    \ (const InputEdge& edge : input_edges) {\n            _edges[_offset[edge.from]++]\
    \ = SolverEdge{edge.to, edge.cost * 2};\n            _edges[_offset[edge.to]++]\
    \ = SolverEdge{edge.from, edge.cost * 2};\n        }\n        for (int i = _vertex_count\
    \ + 1; i > 0; i--) _offset[i] = _offset[i - 1];\n        _offset[0] = 0;\n   \
    \ }\n\n    total_type solve(std::vector<std::pair<int, int>>& matching) {\n  \
    \      initialize_state();\n        initialize_potentials();\n        for (int\
    \ vertex = 1; vertex <= _vertex_count; vertex++) {\n            if (_mate[vertex]\
    \ == 0) augment_from(vertex);\n        }\n\n        matching.clear();\n      \
    \  for (int vertex = 1; vertex <= _vertex_count; vertex++) {\n            if (_mate[vertex]\
    \ > vertex) matching.emplace_back(vertex, _mate[vertex]);\n        }\n       \
    \ return compute_matching_weight();\n    }\n\n   private:\n    total_type compute_matching_weight()\
    \ const {\n        total_type result = 0;\n        for (int vertex = 1; vertex\
    \ <= _vertex_count; vertex++) {\n            if (_mate[vertex] > vertex) {\n \
    \               cost_type best_cost = 0;\n                for (int edge_id = _offset[vertex];\
    \ edge_id < _offset[vertex + 1]; edge_id++) {\n                    if (_edges[edge_id].to\
    \ == _mate[vertex]) {\n                        best_cost = std::max(best_cost,\
    \ _edges[edge_id].cost);\n                    }\n                }\n         \
    \       result += best_cost;\n            }\n        }\n        return result\
    \ >> 1;\n    }\n\n    total_type reduced_cost(int from, int to, const SolverEdge&\
    \ edge) const {\n        return total_type(_potential[from]) + _potential[to]\
    \ - edge.cost;\n    }\n\n    void rematch(int vertex, int new_mate) {\n      \
    \  int old_mate = _mate[vertex];\n        _mate[vertex] = new_mate;\n        if\
    \ (_mate[old_mate] != vertex) return;\n        if (_tree_link[vertex].to == _surface[_tree_link[vertex].to])\
    \ {\n            _mate[old_mate] = _tree_link[vertex].from;\n            rematch(_mate[old_mate],\
    \ old_mate);\n        } else {\n            int from = _tree_link[vertex].from;\n\
    \            int to = _tree_link[vertex].to;\n            rematch(from, to);\n\
    \            rematch(to, from);\n        }\n    }\n\n    void repair_matching(int\
    \ blossom) {\n        if (blossom <= _vertex_count) return;\n        int child\
    \ = _base[blossom];\n        int first_vertex = _nodes[child].cycle[0].vertex;\n\
    \        int first_neighbor = _nodes[child].cycle[0].blossom;\n        int direction\
    \ = (_nodes[first_neighbor].cycle[1].vertex == _mate[first_vertex]) ? 0 : 1;\n\
    \        while (true) {\n            int matched_vertex = _nodes[child].cycle[direction].vertex;\n\
    \            int matched_child = _nodes[child].cycle[direction].blossom;\n   \
    \         if (_nodes[matched_child].cycle[1 ^ direction].vertex != _mate[matched_vertex])\
    \ break;\n            repair_matching(child);\n            repair_matching(matched_child);\n\
    \            child = _nodes[matched_child].cycle[direction].blossom;\n       \
    \ }\n        _base[blossom] = child;\n        repair_matching(child);\n      \
    \  _mate[blossom] = _mate[child];\n    }\n\n    void reset_clock() {\n       \
    \ _time = 0;\n        _vertex_event = {infinity, 0};\n    }\n\n    void reset_blossom(int\
    \ blossom) {\n        _label[blossom] = free_label;\n        _tree_link[blossom].from\
    \ = 0;\n        _slack[blossom] = infinity;\n        _lazy[blossom] = 0;\n   \
    \ }\n\n    void reset_search_state() {\n        _label[0] = free_label;\n    \
    \    _tree_link[0].from = 0;\n        for (int vertex = 1; vertex <= _vertex_count;\
    \ vertex++) {\n            if (_label[vertex] == outer_label) {\n            \
    \    _potential[vertex] -= _time;\n            } else {\n                int blossom\
    \ = _surface[vertex];\n                _potential[vertex] += _lazy[blossom];\n\
    \                if (_label[blossom] == inner_label) {\n                    _potential[vertex]\
    \ += _time - _created_at[blossom];\n                }\n            }\n       \
    \     reset_blossom(vertex);\n        }\n        int remaining_blossoms = _blossom_count\
    \ - _unused_count;\n        for (int blossom = _vertex_count + 1; remaining_blossoms\
    \ > 0 && blossom < _state_count; blossom++) {\n            if (_base[blossom]\
    \ != blossom) {\n                if (_surface[blossom] == blossom) {\n       \
    \             repair_matching(blossom);\n                    if (_label[blossom]\
    \ == outer_label) {\n                        _potential[blossom] += (_time - _created_at[blossom])\
    \ << 1;\n                    } else if (_label[blossom] == inner_label) {\n  \
    \                      materialize_potential<inner_label>(blossom);\n        \
    \            } else {\n                        materialize_potential<free_label>(blossom);\n\
    \                    }\n                }\n                _blossom_grow_heaps.clear(blossom);\n\
    \                reset_blossom(blossom);\n                remaining_blossoms--;\n\
    \            }\n        }\n\n        _queue.clear();\n        reset_clock();\n\
    \        _grow_heap.clear();\n        _contract_heap.clear();\n        _expand_heap.clear();\n\
    \    }\n\n    void augment_from(int root) {\n        if (_potential[root] == 0)\
    \ return;\n        link_blossom(_surface[root], {0, 0});\n        make_outer(_surface[root],\
    \ 0);\n        for (bool augmented = false; !augmented;) {\n            augmented\
    \ = scan_tight_edges(root);\n            if (augmented) break;\n            augmented\
    \ = advance_dual(root);\n        }\n        reset_search_state();\n    }\n\n \
    \   template <BlossomLabel target_label>\n    cost_type materialize_potential(int\
    \ blossom) {\n        cost_type delta = _lazy[blossom];\n        _lazy[blossom]\
    \ = 0;\n        if (target_label == inner_label) {\n            cost_type elapsed\
    \ = _time - _created_at[blossom];\n            if (blossom > _vertex_count) _potential[blossom]\
    \ -= elapsed << 1;\n            delta += elapsed;\n        }\n        return delta;\n\
    \    }\n\n    template <BlossomLabel target_label>\n    void update_grow_event(int\
    \ from, int to, int to_blossom, cost_type slack) {\n        if (slack >= _slack[to])\
    \ return;\n        _slack[to] = slack;\n        _best_from[to] = from;\n     \
    \   if (to == to_blossom) {\n            if (target_label != inner_label) {\n\
    \                _grow_heap.decrease_key(to, EdgeEvent(slack + _lazy[to], from,\
    \ to));\n            }\n        } else {\n            int to_group = _group[to];\n\
    \            if (to_group != to) {\n                if (slack >= _slack[to_group])\
    \ return;\n                _slack[to_group] = slack;\n            }\n        \
    \    _blossom_grow_heaps.decrease_key(to_blossom, to_group, EdgeEvent(slack, from,\
    \ to));\n            if (target_label == inner_label) return;\n            EdgeEvent\
    \ event = _blossom_grow_heaps.min(to_blossom);\n            _grow_heap.decrease_key(to_blossom,\n\
    \                                    EdgeEvent(event.time + _lazy[to_blossom],\
    \ event.from, event.to));\n        }\n    }\n\n    void activate_grow_event(int\
    \ blossom) {\n        if (blossom <= _vertex_count) {\n            if (_slack[blossom]\
    \ < infinity) {\n                _grow_heap.push(blossom,\n                  \
    \              EdgeEvent(_slack[blossom] + _lazy[blossom], _best_from[blossom],\
    \ blossom));\n            }\n        } else {\n            if (_blossom_grow_heaps.empty(blossom))\
    \ return;\n            EdgeEvent event = _blossom_grow_heaps.min(blossom);\n \
    \           _grow_heap.push(blossom, EdgeEvent(event.time + _lazy[blossom], event.from,\
    \ event.to));\n        }\n    }\n\n    void swap_blossoms(int a, int b) {\n  \
    \      // b is a maximal blossom.\n        std::swap(_base[a], _base[b]);\n  \
    \      if (_base[a] == a) _base[a] = b;\n        std::swap(_heavy[a], _heavy[b]);\n\
    \        if (_heavy[a] == a) _heavy[a] = b;\n        std::swap(_tree_link[a],\
    \ _tree_link[b]);\n        std::swap(_mate[a], _mate[b]);\n        std::swap(_potential[a],\
    \ _potential[b]);\n        std::swap(_lazy[a], _lazy[b]);\n        std::swap(_created_at[a],\
    \ _created_at[b]);\n        for (int direction = 0; direction < 2; direction++)\
    \ {\n            int child = _nodes[a].cycle[direction].blossom;\n           \
    \ _nodes[child].cycle[1 ^ direction].blossom = b;\n        }\n        std::swap(_nodes[a],\
    \ _nodes[b]);\n    }\n\n    void assign_surface(int blossom, int surface, int\
    \ group) {\n        _surface[blossom] = surface;\n        _group[blossom] = group;\n\
    \        if (blossom <= _vertex_count) return;\n        for (int child = _base[blossom];\
    \ _surface[child] != surface; child = _nodes[child].next_b()) {\n            assign_surface(child,\
    \ surface, group);\n        }\n    }\n\n    void merge_blossom_children(int blossom)\
    \ {\n        int largest_child = blossom;\n        int largest_size = 1;\n   \
    \     int first_child = _base[blossom];\n        for (int child = first_child;;\
    \ child = _nodes[child].next_b()) {\n            if (_nodes[child].size > largest_size)\
    \ {\n                largest_size = _nodes[child].size;\n                largest_child\
    \ = child;\n            }\n            if (_nodes[child].next_b() == first_child)\
    \ break;\n        }\n        for (int child = first_child;; child = _nodes[child].next_b())\
    \ {\n            if (child != largest_child) assign_surface(child, largest_child,\
    \ child);\n            if (_nodes[child].next_b() == first_child) break;\n   \
    \     }\n        _group[largest_child] = largest_child;\n        if (largest_size\
    \ > 1) {\n            _surface[blossom] = _heavy[blossom] = largest_child;\n \
    \           swap_blossoms(largest_child, blossom);\n        } else {\n       \
    \     _heavy[blossom] = 0;\n        }\n    }\n\n    void contract_blossom(int\
    \ x, int y, int edge_id) {\n        int x_blossom = _surface[x];\n        int\
    \ y_blossom = _surface[y];\n        assert(x_blossom != y_blossom);\n        const\
    \ int visit_mark = -(edge_id + 1);\n        _tree_link[_surface[_mate[x_blossom]]].from\
    \ = visit_mark;\n        _tree_link[_surface[_mate[y_blossom]]].from = visit_mark;\n\
    \n        int lca = -1;\n        while (true) {\n            if (_mate[y_blossom]\
    \ != 0) std::swap(x_blossom, y_blossom);\n            x_blossom = lca = _surface[_tree_link[x_blossom].from];\n\
    \            if (_tree_link[_surface[_mate[x_blossom]]].from == visit_mark) break;\n\
    \            _tree_link[_surface[_mate[x_blossom]]].from = visit_mark;\n     \
    \   }\n\n        const int blossom = _unused_blossoms[--_unused_count];\n    \
    \    assert(_unused_count >= 0);\n        int tree_size = 0;\n        for (int\
    \ direction = 0; direction < 2; direction++) {\n            for (int child = _surface[x];\
    \ child != lca;) {\n                int matched_vertex = _mate[child];\n     \
    \           int matched_child = _surface[matched_vertex];\n                int\
    \ vertex = _mate[matched_vertex];\n                int link_from = _tree_link[vertex].from;\n\
    \                int link_to = _tree_link[vertex].to;\n                tree_size\
    \ += _nodes[child].size + _nodes[matched_child].size;\n                _tree_link[matched_vertex]\
    \ = {x, y};\n\n                if (child > _vertex_count) {\n                \
    \    _potential[child] += (_time - _created_at[child]) << 1;\n               \
    \ }\n                if (matched_child > _vertex_count) _expand_heap.erase(matched_child);\n\
    \                make_outer(matched_child, materialize_potential<inner_label>(matched_child));\n\
    \n                _nodes[child].cycle[direction] = {matched_child, matched_vertex};\n\
    \                _nodes[matched_child].cycle[1 ^ direction] = {child, vertex};\n\
    \                child = _surface[link_from];\n                _nodes[matched_child].cycle[direction]\
    \ = {child, link_from};\n                _nodes[child].cycle[1 ^ direction] =\
    \ {matched_child, link_to};\n            }\n            _nodes[_surface[x]].cycle[1\
    \ ^ direction] = {_surface[y], y};\n            std::swap(x, y);\n        }\n\
    \        if (lca > _vertex_count) _potential[lca] += (_time - _created_at[lca])\
    \ << 1;\n        _nodes[blossom].size = tree_size + _nodes[lca].size;\n      \
    \  _base[blossom] = lca;\n        _tree_link[blossom] = _tree_link[lca];\n   \
    \     _mate[blossom] = _mate[lca];\n        _label[blossom] = outer_label;\n \
    \       _surface[blossom] = blossom;\n        _created_at[blossom] = _time;\n\
    \        _potential[blossom] = 0;\n        _lazy[blossom] = 0;\n\n        merge_blossom_children(blossom);\n\
    \    }\n\n    void link_blossom(int blossom, BlossomLink link) {\n        _tree_link[blossom]\
    \ = link;\n        if (blossom <= _vertex_count) return;\n        int first_child\
    \ = _base[blossom];\n        link_blossom(first_child, link);\n        int previous_child\
    \ = _nodes[first_child].prev_b();\n        link = {_nodes[previous_child].next_v(),\
    \ _nodes[first_child].prev_v()};\n        for (int child = first_child;;) {\n\
    \            int next_child = _nodes[child].next_b();\n            if (next_child\
    \ == first_child) break;\n            link_blossom(next_child, link);\n      \
    \      BlossomLink next_link = {_nodes[next_child].prev_v(), _nodes[child].next_v()};\n\
    \            child = _nodes[next_child].next_b();\n            link_blossom(child,\
    \ next_link);\n        }\n    }\n\n    void make_outer(int blossom, cost_type\
    \ delta) {\n        _label[blossom] = outer_label;\n        if (blossom > _vertex_count)\
    \ {\n            for (int child = _base[blossom]; _label[child] != outer_label;\
    \ child = _nodes[child].next_b()) {\n                make_outer(child, delta);\n\
    \            }\n        } else {\n            _potential[blossom] += _time + delta;\n\
    \            if (_potential[blossom] < _vertex_event.time) {\n               \
    \ _vertex_event = {_potential[blossom], blossom};\n            }\n           \
    \ _queue.enqueue(blossom);\n        }\n    }\n\n    bool grow_tree(int from, int\
    \ to) {\n        int inner_blossom = _surface[to];\n        bool visited = (_label[inner_blossom]\
    \ != free_label);\n        if (!visited) link_blossom(inner_blossom, {0, 0});\n\
    \        _label[inner_blossom] = inner_label;\n        _created_at[inner_blossom]\
    \ = _time;\n        _grow_heap.erase(inner_blossom);\n        if (to != inner_blossom)\
    \ {\n            _expand_heap.update(inner_blossom, _time + (_potential[inner_blossom]\
    \ >> 1));\n        }\n        int matched_vertex = _mate[inner_blossom];\n   \
    \     if (matched_vertex == 0) {\n            rematch(from, to);\n           \
    \ rematch(to, from);\n            return true;\n        }\n        int outer_blossom\
    \ = _surface[matched_vertex];\n        if (!visited) {\n            link_blossom(outer_blossom,\
    \ {from, to});\n        } else {\n            _tree_link[outer_blossom] = _tree_link[matched_vertex]\
    \ = {from, to};\n        }\n        make_outer(outer_blossom, materialize_potential<free_label>(outer_blossom));\n\
    \        _created_at[outer_blossom] = _time;\n        _grow_heap.erase(outer_blossom);\n\
    \        return false;\n    }\n\n    void release_blossom(int blossom) {\n   \
    \     _unused_blossoms[_unused_count++] = blossom;\n        _base[blossom] = blossom;\n\
    \    }\n\n    int recompute_slack(int blossom, int group) {\n        if (blossom\
    \ <= _vertex_count) {\n            if (_slack[blossom] >= _slack[group]) return\
    \ 0;\n            _slack[group] = _slack[blossom];\n            _best_from[group]\
    \ = _best_from[blossom];\n            return blossom;\n        }\n        int\
    \ destination = 0;\n        int first_child = _base[blossom];\n        for (int\
    \ child = first_child;; child = _nodes[child].next_b()) {\n            int candidate\
    \ = recompute_slack(child, group);\n            if (candidate != 0) destination\
    \ = candidate;\n            if (_nodes[child].next_b() == first_child) break;\n\
    \        }\n        return destination;\n    }\n\n    void rebuild_components(int\
    \ blossom, int surface, int group) {\n        _surface[blossom] = surface;\n \
    \       _group[blossom] = group;\n        if (blossom <= _vertex_count) return;\n\
    \        for (int child = _base[blossom]; _surface[child] != surface; child =\
    \ _nodes[child].next_b()) {\n            if (child == _heavy[blossom]) {\n   \
    \             rebuild_components(child, surface, group);\n            } else {\n\
    \                assign_surface(child, surface, child);\n                int destination\
    \ = 0;\n                if (child > _vertex_count) {\n                    _slack[child]\
    \ = infinity;\n                    destination = recompute_slack(child, child);\n\
    \                } else if (_slack[child] < infinity) {\n                    destination\
    \ = child;\n                }\n                if (destination > 0) {\n      \
    \              _blossom_grow_heaps.push(surface, child,\n                    \
    \                         EdgeEvent(_slack[child], _best_from[child], destination));\n\
    \                }\n            }\n        }\n    }\n\n    void promote_largest_child(int\
    \ blossom) {\n        int largest_child = _heavy[blossom];\n        cost_type\
    \ delta = (_time - _created_at[blossom]) + _lazy[blossom];\n        _lazy[blossom]\
    \ = 0;\n        int first_child = _base[blossom];\n        for (int child = first_child;;\
    \ child = _nodes[child].next_b()) {\n            _created_at[child] = _time;\n\
    \            _lazy[child] = delta;\n            if (child != largest_child) {\n\
    \                rebuild_components(child, child, child);\n                _blossom_grow_heaps.erase(blossom,\
    \ child);\n            }\n            if (_nodes[child].next_b() == first_child)\
    \ break;\n        }\n        if (largest_child > 0) {\n            swap_blossoms(largest_child,\
    \ blossom);\n            blossom = largest_child;\n        }\n        release_blossom(blossom);\n\
    \    }\n\n    void expand_blossom(int blossom) {\n        int matched_vertex =\
    \ _mate[_base[blossom]];\n        promote_largest_child(blossom);\n        BlossomLink\
    \ old_link = _tree_link[matched_vertex];\n        int old_base = _surface[_mate[matched_vertex]];\n\
    \        int root = _surface[old_link.to];\n        int direction = (_mate[root]\
    \ == _nodes[root].cycle[0].vertex) ? 1 : 0;\n        for (int child = _nodes[old_base].cycle[direction\
    \ ^ 1].blossom; child != root;) {\n            _label[child] = separated_label;\n\
    \            activate_grow_event(child);\n            child = _nodes[child].cycle[direction\
    \ ^ 1].blossom;\n            _label[child] = separated_label;\n            activate_grow_event(child);\n\
    \            child = _nodes[child].cycle[direction ^ 1].blossom;\n        }\n\
    \        for (int child = old_base;; child = _nodes[child].cycle[direction].blossom)\
    \ {\n            _label[child] = inner_label;\n            int next_child = _nodes[child].cycle[direction].blossom;\n\
    \            if (child == root) {\n                _tree_link[_mate[child]] =\
    \ old_link;\n            } else {\n                _tree_link[_mate[child]] =\
    \ {_nodes[child].cycle[direction].vertex,\n                                  \
    \          _nodes[next_child].cycle[direction ^ 1].vertex};\n            }\n \
    \           _tree_link[_surface[_mate[child]]] = _tree_link[_mate[child]];\n \
    \           if (child > _vertex_count) {\n                if (_potential[child]\
    \ == 0) {\n                    expand_blossom(child);\n                } else\
    \ {\n                    _expand_heap.push(child, _time + (_potential[child] >>\
    \ 1));\n                }\n            }\n            if (child == root) break;\n\
    \            child = next_child;\n            make_outer(next_child, materialize_potential<inner_label>(next_child));\n\
    \        }\n    }\n\n    bool scan_tight_edges(int root) {\n        while (!_queue.empty())\
    \ {\n            int from = _queue.dequeue();\n            int from_blossom =\
    \ _surface[from];\n            if (_potential[from] == _time) {\n            \
    \    if (from != root) rematch(from, 0);\n                return true;\n     \
    \       }\n            for (int edge_id = _offset[from]; edge_id < _offset[from\
    \ + 1]; edge_id++) {\n                const SolverEdge& edge = _edges[edge_id];\n\
    \                int to = edge.to;\n                int to_blossom = _surface[to];\n\
    \                if (from_blossom == to_blossom) continue;\n                BlossomLabel\
    \ to_label = _label[to_blossom];\n                if (to_label == outer_label)\
    \ {\n                    cost_type event_time = cost_type(reduced_cost(from, to,\
    \ edge) >> 1);\n                    if (event_time == _time) {\n             \
    \           contract_blossom(from, to, edge_id);\n                        from_blossom\
    \ = _surface[from];\n                    } else if (event_time < _vertex_event.time)\
    \ {\n                        _contract_heap.emplace(event_time, from, edge_id);\n\
    \                    }\n                } else {\n                    total_type\
    \ event_time = reduced_cost(from, to, edge);\n                    if (event_time\
    \ >= infinity) continue;\n                    if (to_label != inner_label) {\n\
    \                        if (cost_type(event_time) + _lazy[to_blossom] == _time)\
    \ {\n                            if (grow_tree(from, to)) return true;\n     \
    \                   } else {\n                            update_grow_event<free_label>(from,\
    \ to, to_blossom, cost_type(event_time));\n                        }\n       \
    \             } else if (_mate[from] != to) {\n                        update_grow_event<inner_label>(from,\
    \ to, to_blossom, cost_type(event_time));\n                    }\n           \
    \     }\n            }\n        }\n        return false;\n    }\n\n    bool advance_dual(int\
    \ root) {\n        cost_type rematch_time = _vertex_event.time;\n        cost_type\
    \ grow_time = infinity;\n        if (!_grow_heap.empty()) grow_time = _grow_heap.min().time;\n\
    \n        cost_type contract_time = infinity;\n        while (!_contract_heap.empty())\
    \ {\n            EdgeEvent event = _contract_heap.min();\n            int from\
    \ = event.from;\n            int to = _edges[event.to].to;\n            if (_surface[from]\
    \ != _surface[to]) {\n                contract_time = event.time;\n          \
    \      break;\n            } else {\n                _contract_heap.pop();\n \
    \           }\n        }\n\n        cost_type expand_time = infinity;\n      \
    \  if (!_expand_heap.empty()) expand_time = _expand_heap.min();\n\n        cost_type\
    \ next_time =\n            std::min(std::min(rematch_time, grow_time), std::min(contract_time,\
    \ expand_time));\n        assert(_time <= next_time && next_time < infinity);\n\
    \        _time = next_time;\n\n        if (_time == _vertex_event.time) {\n  \
    \          int x = _vertex_event.id;\n            if (x != root) rematch(x, 0);\n\
    \            return true;\n        }\n        while (!_grow_heap.empty() && _grow_heap.min().time\
    \ == _time) {\n            int from = _grow_heap.min().from;\n            int\
    \ to = _grow_heap.min().to;\n            if (grow_tree(from, to)) return true;\n\
    \        }\n        while (!_contract_heap.empty() && _contract_heap.min().time\
    \ == _time) {\n            int from = _contract_heap.min().from;\n           \
    \ int edge_id = _contract_heap.min().to;\n            int to = _edges[edge_id].to;\n\
    \            _contract_heap.pop();\n            if (_surface[from] == _surface[to])\
    \ continue;\n            contract_blossom(from, to, edge_id);\n        }\n   \
    \     while (!_expand_heap.empty() && _expand_heap.min() == _time) {\n       \
    \     int blossom = _expand_heap.argmin();\n            _expand_heap.pop();\n\
    \            expand_blossom(blossom);\n        }\n        return false;\n    }\n\
    \n   private:\n    void initialize_state() {\n        _queue = FixedQueue<int>(_vertex_count);\n\
    \        _mate.assign(_state_count, 0);\n        _tree_link.assign(_state_count,\
    \ {0, 0});\n        _label.assign(_state_count, free_label);\n        _base.resize(_state_count);\n\
    \        for (int state = 1; state < _state_count; state++) _base[state] = state;\n\
    \        _surface.resize(_state_count);\n        for (int state = 1; state < _state_count;\
    \ state++) _surface[state] = state;\n\n        _potential.resize(_state_count);\n\
    \        _nodes.resize(_state_count);\n        for (int state = 1; state < _state_count;\
    \ state++) {\n            _nodes[state] = BlossomNode(state);\n        }\n\n \
    \       _unused_blossoms.resize(_blossom_count);\n        for (int i = 0; i <\
    \ _blossom_count; i++) {\n            _unused_blossoms[i] = _vertex_count + _blossom_count\
    \ - i;\n        }\n        _unused_count = _blossom_count;\n\n        reset_clock();\n\
    \        _created_at.resize(_state_count);\n        _slack.assign(_state_count,\
    \ infinity);\n        _best_from.assign(_state_count, 0);\n        _heavy.assign(_state_count,\
    \ 0);\n        _lazy.assign(_state_count, 0);\n        _group.resize(_state_count);\n\
    \        for (int state = 0; state < _state_count; state++) _group[state] = state;\n\
    \    }\n\n    void initialize_potentials() {\n        for (int vertex = 1; vertex\
    \ <= _vertex_count; vertex++) {\n            cost_type maximum_cost = 0;\n   \
    \         for (int edge_id = _offset[vertex]; edge_id < _offset[vertex + 1]; edge_id++)\
    \ {\n                maximum_cost = std::max(maximum_cost, _edges[edge_id].cost);\n\
    \            }\n            _potential[vertex] = maximum_cost >> 1;\n        }\n\
    \    }\n\n    const int _vertex_count;\n    const int _blossom_count;\n    const\
    \ int _state_count;\n    std::vector<int> _offset;\n    std::vector<SolverEdge>\
    \ _edges;\n\n    FixedQueue<int> _queue;\n    std::vector<int> _mate;\n    std::vector<int>\
    \ _surface;\n    std::vector<int> _base;\n    std::vector<BlossomLink> _tree_link;\n\
    \    std::vector<BlossomLabel> _label;\n    std::vector<cost_type> _potential;\n\
    \n    std::vector<int> _unused_blossoms;\n    int _unused_count;\n    std::vector<BlossomNode>\
    \ _nodes;\n\n    // Heavy children and event queues keep each search phase at\
    \ O(m log n).\n    std::vector<int> _heavy;\n    std::vector<int> _group;\n  \
    \  std::vector<cost_type> _created_at;\n    std::vector<cost_type> _lazy;\n  \
    \  std::vector<cost_type> _slack;\n    std::vector<int> _best_from;\n\n    cost_type\
    \ _time;\n    VertexEvent _vertex_event;\n    MutableBinaryHeap<EdgeEvent> _grow_heap;\n\
    \    DisjointPairingHeaps<EdgeEvent> _blossom_grow_heaps;\n    ReservablePriorityQueue<EdgeEvent>\
    \ _contract_heap;\n    MutableBinaryHeap<cost_type> _expand_heap;\n};\n\n}  //\
    \ namespace internal\n\ntemplate <class Cost, class TotalCost = Cost>\nstruct\
    \ GeneralWeightedMatching {\n    static_assert(std::is_integral_v<Cost> && std::is_signed_v<Cost>);\n\
    \    static_assert(std::is_integral_v<TotalCost> && std::is_signed_v<TotalCost>);\n\
    \n    struct Edge {\n        int from;\n        int to;\n        Cost cost;\n\
    \        int id;\n        bool alive;\n\n        int other(int vertex) const {\n\
    \            assert(vertex == from || vertex == to);\n            return from\
    \ ^ to ^ vertex;\n        }\n    };\n\n    struct Pair {\n        int from;\n\
    \        int to;\n        Cost cost;\n        int edge_id;\n    };\n\n   private:\n\
    \    int _n;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
    \ _adj;\n    std::vector<int> _mate;\n    std::vector<int> _mate_edge;\n    TotalCost\
    \ _matching_weight;\n    bool _calculated;\n\n    void invalidate() {\n      \
    \  _calculated = false;\n    }\n\n    void ensure_matching() {\n        if (!_calculated)\
    \ max_weight_matching();\n    }\n\n   public:\n    GeneralWeightedMatching() :\
    \ GeneralWeightedMatching(0) {\n    }\n\n    explicit GeneralWeightedMatching(int\
    \ n)\n        : _n(n), _adj(n), _mate(n, -1), _mate_edge(n, -1), _matching_weight(),\
    \ _calculated(false) {\n        assert(0 <= n);\n    }\n\n    int size() const\
    \ {\n        return _n;\n    }\n\n    int edge_count() const {\n        return\
    \ int(_edges.size());\n    }\n\n    int add_edge(int from, int to, Cost cost)\
    \ {\n        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(from != to);\n        assert(cost <= std::numeric_limits<Cost>::max()\
    \ / Cost(2));\n        int id = int(_edges.size());\n        _edges.push_back(Edge{from,\
    \ to, cost, id, true});\n        _adj[from].push_back(id);\n        _adj[to].push_back(id);\n\
    \        invalidate();\n        return id;\n    }\n\n    Edge get_edge(int id)\
    \ const {\n        assert(0 <= id && id < int(_edges.size()));\n        return\
    \ _edges[id];\n    }\n\n    std::vector<Edge> edges(bool include_inactive = false)\
    \ const {\n        std::vector<Edge> result;\n        result.reserve(_edges.size());\n\
    \        for (const Edge& edge : _edges) {\n            if (include_inactive ||\
    \ edge.alive) result.push_back(edge);\n        }\n        return result;\n   \
    \ }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0 <= id &&\
    \ id < int(_edges.size()));\n        _edges[id].alive = alive;\n        invalidate();\n\
    \    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < int(_edges.size()));\n        return _edges[id].alive;\n    }\n\n    TotalCost\
    \ max_weight_matching() {\n        using Solver = internal::WeightedBlossomSolver<Cost,\
    \ TotalCost>;\n        std::vector<typename Solver::InputEdge> input;\n      \
    \  input.reserve(_edges.size());\n        for (const Edge& edge : _edges) {\n\
    \            if (!edge.alive || edge.cost <= Cost()) continue;\n            input.push_back(typename\
    \ Solver::InputEdge{edge.from + 1, edge.to + 1, edge.cost});\n        }\n\n  \
    \      Solver solver(_n, input);\n        std::vector<std::pair<int, int>> vertex_pairs;\n\
    \        solver.solve(vertex_pairs);\n\n        _mate.assign(_n, -1);\n      \
    \  _mate_edge.assign(_n, -1);\n        _matching_weight = TotalCost();\n     \
    \   for (auto [one_based_from, one_based_to] : vertex_pairs) {\n            int\
    \ from = one_based_from - 1;\n            int to = one_based_to - 1;\n       \
    \     int best_edge = -1;\n            for (int id : _adj[from]) {\n         \
    \       const Edge& edge = _edges[id];\n                if (!edge.alive || edge.other(from)\
    \ != to || edge.cost <= Cost()) continue;\n                if (best_edge == -1\
    \ || _edges[best_edge].cost < edge.cost) best_edge = id;\n            }\n    \
    \        assert(best_edge != -1);\n            _mate[from] = to;\n           \
    \ _mate[to] = from;\n            _mate_edge[from] = best_edge;\n            _mate_edge[to]\
    \ = best_edge;\n            _matching_weight += static_cast<TotalCost>(_edges[best_edge].cost);\n\
    \        }\n\n        _calculated = true;\n        return _matching_weight;\n\
    \    }\n\n    TotalCost matching_weight() {\n        ensure_matching();\n    \
    \    return _matching_weight;\n    }\n\n    int matching_size() {\n        ensure_matching();\n\
    \        int result = 0;\n        for (int vertex = 0; vertex < _n; vertex++)\
    \ {\n            if (vertex < _mate[vertex]) result++;\n        }\n        return\
    \ result;\n    }\n\n    std::vector<int> mate() {\n        ensure_matching();\n\
    \        return _mate;\n    }\n\n    std::vector<int> mate_edge() {\n        ensure_matching();\n\
    \        return _mate_edge;\n    }\n\n    std::vector<Pair> matching() {\n   \
    \     ensure_matching();\n        std::vector<Pair> result;\n        for (int\
    \ vertex = 0; vertex < _n; vertex++) {\n            if (vertex < _mate[vertex])\
    \ {\n                int id = _mate_edge[vertex];\n                result.push_back(Pair{vertex,\
    \ _mate[vertex], _edges[id].cost, id});\n            }\n        }\n        return\
    \ result;\n    }\n};\n\ntemplate <class Cost, class TotalCost = Cost>\nstruct\
    \ GeneralWeightedMatchingGraph {\n    GeneralWeightedMatching<Cost, TotalCost>\
    \ matching;\n    std::vector<int> original_edge_id;\n\n    int original_edge(int\
    \ edge_id) const {\n        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));\n\
    \        return original_edge_id[edge_id];\n    }\n};\n\ntemplate <class T>\n\
    GeneralWeightedMatchingGraph<T> make_general_weighted_matching(const Graph<T>&\
    \ graph) {\n    GeneralWeightedMatchingGraph<T> result;\n    result.matching =\
    \ GeneralWeightedMatching<T>(graph.size());\n    for (const auto& edge : graph.edges())\
    \ {\n        int id = result.matching.add_edge(edge.from, edge.to, edge.cost);\n\
    \        if (int(result.original_edge_id.size()) <= id) {\n            result.original_edge_id.resize(id\
    \ + 1);\n        }\n        result.original_edge_id[id] = edge.id;\n    }\n  \
    \  return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line\
    \ 1 \"graph/grid.hpp\"\n\n\n\n#line 8 \"graph/grid.hpp\"\n\n#line 10 \"graph/grid.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct Grid {\n   private:\n    int\
    \ _h;\n    int _w;\n\n   public:\n    static constexpr std::array<int, 4> di4\
    \ = {-1, 0, 1, 0};\n    static constexpr std::array<int, 4> dj4 = {0, 1, 0, -1};\n\
    \    static constexpr std::array<int, 8> di8 = {-1, -1, -1, 0, 0, 1, 1, 1};\n\
    \    static constexpr std::array<int, 8> dj8 = {-1, 0, 1, -1, 1, -1, 0, 1};\n\n\
    \    Grid() : _h(0), _w(0) {}\n    Grid(int h, int w) : _h(h), _w(w) {\n     \
    \   assert(0 <= h);\n        assert(0 <= w);\n    }\n\n    int height() const\
    \ {\n        return _h;\n    }\n\n    int width() const {\n        return _w;\n\
    \    }\n\n    int size() const {\n        return _h * _w;\n    }\n\n    bool empty()\
    \ const {\n        return size() == 0;\n    }\n\n    bool inside(int i, int j)\
    \ const {\n        return 0 <= i && i < _h && 0 <= j && j < _w;\n    }\n\n   \
    \ int id(int i, int j) const {\n        assert(inside(i, j));\n        return\
    \ i * _w + j;\n    }\n\n    std::pair<int, int> pos(int v) const {\n        assert(0\
    \ <= v && v < size());\n        return {v / _w, v % _w};\n    }\n\n    std::vector<std::pair<int,\
    \ int>> adj4(int i, int j) const {\n        assert(inside(i, j));\n        std::vector<std::pair<int,\
    \ int>> result;\n        result.reserve(4);\n        for (int k = 0; k < 4; k++)\
    \ {\n            int ni = i + di4[k], nj = j + dj4[k];\n            if (inside(ni,\
    \ nj)) result.emplace_back(ni, nj);\n        }\n        return result;\n    }\n\
    \n    std::vector<std::pair<int, int>> adj8(int i, int j) const {\n        assert(inside(i,\
    \ j));\n        std::vector<std::pair<int, int>> result;\n        result.reserve(8);\n\
    \        for (int k = 0; k < 8; k++) {\n            int ni = i + di8[k], nj =\
    \ j + dj8[k];\n            if (inside(ni, nj)) result.emplace_back(ni, nj);\n\
    \        }\n        return result;\n    }\n\n    std::vector<int> adj4_ids(int\
    \ v) const {\n        auto [i, j] = pos(v);\n        std::vector<int> result;\n\
    \        result.reserve(4);\n        for (auto [ni, nj] : adj4(i, j)) result.push_back(id(ni,\
    \ nj));\n        return result;\n    }\n\n    std::vector<int> adj8_ids(int v)\
    \ const {\n        auto [i, j] = pos(v);\n        std::vector<int> result;\n \
    \       result.reserve(8);\n        for (auto [ni, nj] : adj8(i, j)) result.push_back(id(ni,\
    \ nj));\n        return result;\n    }\n\n    Graph<int> graph4() const {\n  \
    \      return graph4([](int, int) { return true; });\n    }\n\n    Graph<int>\
    \ graph8() const {\n        return graph8([](int, int) { return true; });\n  \
    \  }\n\n    template <class Passable>\n    Graph<int> graph4(Passable passable)\
    \ const {\n        Graph<int> g(size());\n        for (int i = 0; i < _h; i++)\
    \ {\n            for (int j = 0; j < _w; j++) {\n                if (!passable(i,\
    \ j)) continue;\n                int v = id(i, j);\n                for (auto\
    \ [ni, nj] : adj4(i, j)) {\n                    if (!passable(ni, nj)) continue;\n\
    \                    int to = id(ni, nj);\n                    if (v < to) g.add_edge(v,\
    \ to);\n                }\n            }\n        }\n        return g;\n    }\n\
    \n    template <class Passable>\n    Graph<int> graph8(Passable passable) const\
    \ {\n        Graph<int> g(size());\n        for (int i = 0; i < _h; i++) {\n \
    \           for (int j = 0; j < _w; j++) {\n                if (!passable(i, j))\
    \ continue;\n                int v = id(i, j);\n                for (auto [ni,\
    \ nj] : adj8(i, j)) {\n                    if (!passable(ni, nj)) continue;\n\
    \                    int to = id(ni, nj);\n                    if (v < to) g.add_edge(v,\
    \ to);\n                }\n            }\n        }\n        return g;\n    }\n\
    };\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/kruskal.hpp\"\
    \n\n\n\n#line 6 \"graph/kruskal.hpp\"\n\n#line 9 \"graph/kruskal.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct MinimumSpanningForest\
    \ {\n    T cost;\n    std::vector<Edge<T>> edges;\n    int components;\n\n   \
    \ bool is_spanning_tree(int n) const {\n        return components <= 1 && int(edges.size())\
    \ == std::max(0, n - 1);\n    }\n};\n\ntemplate <class T>\nMinimumSpanningForest<T>\
    \ kruskal(const Graph<T>& g) {\n    int n = g.size();\n    auto edges = g.edges();\n\
    \    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {\n\
    \        return a.cost < b.cost;\n    });\n\n    m1une::ds::Dsu dsu(n);\n    MinimumSpanningForest<T>\
    \ result;\n    result.cost = T(0);\n    result.components = n;\n\n    for (const\
    \ auto& e : edges) {\n        if (dsu.same(e.from, e.to)) continue;\n        dsu.merge(e.from,\
    \ e.to);\n        result.cost += e.cost;\n        result.edges.push_back(e);\n\
    \        result.components--;\n    }\n\n    return result;\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/lowlink.hpp\"\n\n\n\n#line\
    \ 6 \"graph/lowlink.hpp\"\n\n#line 8 \"graph/lowlink.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T>\nstruct LowLinkResult {\n    std::vector<int>\
    \ ord;\n    std::vector<int> low;\n    std::vector<int> articulation;\n    std::vector<Edge<T>>\
    \ bridges;\n    std::vector<int> bridge_ids;\n};\n\ntemplate <class T>\nLowLinkResult<T>\
    \ lowlink(const Graph<T>& g) {\n    int n = g.size();\n    LowLinkResult<T> result;\n\
    \    result.ord.assign(n, -1);\n    result.low.assign(n, -1);\n    int now = 0;\n\
    \n    auto dfs = [&](auto self, int v, int parent_edge) -> void {\n        result.ord[v]\
    \ = result.low[v] = now++;\n        int child_count = 0;\n        bool is_articulation\
    \ = false;\n\n        for (const auto& e : g[v]) {\n            if (!e.alive)\
    \ continue;\n            if (e.id == parent_edge) continue;\n            int to\
    \ = e.to;\n            if (result.ord[to] == -1) {\n                child_count++;\n\
    \                self(self, to, e.id);\n                result.low[v] = std::min(result.low[v],\
    \ result.low[to]);\n                if (parent_edge != -1 && result.ord[v] <=\
    \ result.low[to]) is_articulation = true;\n                if (result.ord[v] <\
    \ result.low[to]) {\n                    result.bridges.push_back(e);\n      \
    \              result.bridge_ids.push_back(e.id);\n                }\n       \
    \     } else {\n                result.low[v] = std::min(result.low[v], result.ord[to]);\n\
    \            }\n        }\n\n        if (parent_edge == -1 && child_count >= 2)\
    \ is_articulation = true;\n        if (is_articulation) result.articulation.push_back(v);\n\
    \    };\n\n    for (int v = 0; v < n; v++) {\n        if (result.ord[v] == -1)\
    \ dfs(dfs, v, -1);\n    }\n    std::sort(result.articulation.begin(), result.articulation.end());\n\
    \    std::sort(result.bridge_ids.begin(), result.bridge_ids.end());\n    return\
    \ result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/maximum_clique.hpp\"\
    \n\n\n\n#line 7 \"graph/maximum_clique.hpp\"\n\n#line 9 \"graph/maximum_clique.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct MaximumCliqueResult {\n   \
    \ std::vector<int> vertices;\n\n    int size() const {\n        return int(vertices.size());\n\
    \    }\n\n    bool empty() const {\n        return vertices.empty();\n    }\n\
    };\n\nstruct MaximumIndependentSetResult {\n    std::vector<int> vertices;\n\n\
    \    int size() const {\n        return int(vertices.size());\n    }\n\n    bool\
    \ empty() const {\n        return vertices.empty();\n    }\n};\n\nstruct MinimumVertexCoverResult\
    \ {\n    std::vector<int> vertices;\n\n    int size() const {\n        return\
    \ int(vertices.size());\n    }\n\n    bool empty() const {\n        return vertices.empty();\n\
    \    }\n};\n\nnamespace detail {\n\nstruct MaximumIndependentSetBranching {\n\
    \    int n;\n    std::vector<std::vector<char>> adjacent;\n    std::vector<std::vector<int>>\
    \ graph;\n\n    explicit MaximumIndependentSetBranching(const std::vector<std::vector<char>>&\
    \ adjacent_)\n        : n(int(adjacent_.size())), adjacent(adjacent_), graph(n)\
    \ {\n        for (int v = 0; v < n; v++) {\n            for (int to = 0; to <\
    \ n; to++) {\n                if (adjacent[v][to]) graph[v].push_back(to);\n \
    \           }\n        }\n    }\n\n    std::vector<int> solve_path(const std::vector<int>&\
    \ order) const {\n        int m = int(order.size());\n        if (m == 0) return\
    \ {};\n\n        std::vector<int> dp0(m, 0), dp1(m, 0);\n        dp1[0] = 1;\n\
    \        for (int i = 1; i < m; i++) {\n            dp0[i] = std::max(dp0[i -\
    \ 1], dp1[i - 1]);\n            dp1[i] = dp0[i - 1] + 1;\n        }\n\n      \
    \  std::vector<int> result;\n        int state = (dp1[m - 1] > dp0[m - 1] ? 1\
    \ : 0);\n        for (int i = m - 1; i >= 0; i--) {\n            if (state ==\
    \ 1) {\n                result.push_back(order[i]);\n                state = 0;\n\
    \            } else if (i > 0) {\n                state = (dp1[i - 1] > dp0[i\
    \ - 1] ? 1 : 0);\n            }\n        }\n        return result;\n    }\n\n\
    \    std::vector<int> solve_cycle(const std::vector<int>& order) const {\n   \
    \     int m = int(order.size());\n        if (m == 0) return {};\n        if (m\
    \ == 1) return {order[0]};\n\n        std::vector<int> without_first(order.begin()\
    \ + 1, order.end());\n        auto result_without = solve_path(without_first);\n\
    \n        std::vector<int> result_with = {order[0]};\n        if (m >= 4) {\n\
    \            std::vector<int> middle(order.begin() + 2, order.end() - 1);\n  \
    \          auto middle_result = solve_path(middle);\n            result_with.insert(result_with.end(),\
    \ middle_result.begin(), middle_result.end());\n        }\n\n        return (result_with.size()\
    \ > result_without.size() ? result_with : result_without);\n    }\n\n    std::vector<int>\
    \ solve_degree_at_most_two(const std::vector<char>& active,\n                \
    \                              const std::vector<int>& degree) const {\n     \
    \   std::vector<int> result;\n        std::vector<char> visited(n, false);\n\n\
    \        for (int s = 0; s < n; s++) {\n            if (!active[s] || visited[s])\
    \ continue;\n\n            std::vector<int> component;\n            std::vector<int>\
    \ stack = {s};\n            visited[s] = true;\n            for (int it = 0; it\
    \ < int(stack.size()); it++) {\n                int v = stack[it];\n         \
    \       component.push_back(v);\n                for (int to : graph[v]) {\n \
    \                   if (!active[to] || visited[to]) continue;\n              \
    \      visited[to] = true;\n                    stack.push_back(to);\n       \
    \         }\n            }\n\n            if (component.size() == 1) {\n     \
    \           result.push_back(component[0]);\n                continue;\n     \
    \       }\n\n            int endpoint = -1;\n            for (int v : component)\
    \ {\n                if (degree[v] <= 1) {\n                    endpoint = v;\n\
    \                    break;\n                }\n            }\n\n            std::vector<int>\
    \ order;\n            if (endpoint != -1) {\n                int prev = -1, cur\
    \ = endpoint;\n                while (cur != -1) {\n                    order.push_back(cur);\n\
    \                    int next = -1;\n                    for (int to : graph[cur])\
    \ {\n                        if (active[to] && to != prev) {\n               \
    \             next = to;\n                            break;\n               \
    \         }\n                    }\n                    prev = cur;\n        \
    \            cur = next;\n                }\n                auto part = solve_path(order);\n\
    \                result.insert(result.end(), part.begin(), part.end());\n    \
    \        } else {\n                int start = component[0];\n               \
    \ int first = -1;\n                for (int to : graph[start]) {\n           \
    \         if (active[to]) {\n                        first = to;\n           \
    \             break;\n                    }\n                }\n             \
    \   assert(first != -1);\n\n                order.push_back(start);\n        \
    \        int prev = start, cur = first;\n                while (cur != start)\
    \ {\n                    order.push_back(cur);\n                    int next =\
    \ -1;\n                    for (int to : graph[cur]) {\n                     \
    \   if (active[to] && to != prev) {\n                            next = to;\n\
    \                            break;\n                        }\n             \
    \       }\n                    assert(next != -1);\n                    prev =\
    \ cur;\n                    cur = next;\n                }\n                auto\
    \ part = solve_cycle(order);\n                result.insert(result.end(), part.begin(),\
    \ part.end());\n            }\n        }\n\n        return result;\n    }\n\n\
    \    std::vector<int> solve(std::vector<char> active) const {\n        int active_count\
    \ = 0;\n        int max_degree = -1;\n        int branch_vertex = -1;\n      \
    \  std::vector<int> degree(n, 0);\n\n        for (int v = 0; v < n; v++) {\n \
    \           if (!active[v]) continue;\n            active_count++;\n         \
    \   for (int to : graph[v]) {\n                if (active[to]) degree[v]++;\n\
    \            }\n            if (degree[v] > max_degree) {\n                max_degree\
    \ = degree[v];\n                branch_vertex = v;\n            }\n        }\n\
    \n        if (active_count == 0) return {};\n        if (max_degree <= 2) {\n\
    \            auto result = solve_degree_at_most_two(active, degree);\n       \
    \     std::sort(result.begin(), result.end());\n            return result;\n \
    \       }\n\n        auto without = active;\n        without[branch_vertex] =\
    \ false;\n        auto result_without = solve(without);\n\n        auto with =\
    \ active;\n        with[branch_vertex] = false;\n        for (int to : graph[branch_vertex])\
    \ with[to] = false;\n        auto result_with = solve(with);\n        result_with.push_back(branch_vertex);\n\
    \n        auto result = (result_with.size() > result_without.size() ? result_with\
    \ : result_without);\n        std::sort(result.begin(), result.end());\n     \
    \   return result;\n    }\n\n    std::vector<int> solve() const {\n        std::vector<char>\
    \ active(n, true);\n        return solve(active);\n    }\n};\n\ntemplate <class\
    \ T>\nstd::vector<std::vector<char>> undirected_adjacency_matrix(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    std::vector<std::vector<char>> adjacent(n,\
    \ std::vector<char>(n, false));\n    for (const auto& e : g.edges()) {\n     \
    \   if (e.from == e.to) continue;\n        adjacent[e.from][e.to] = true;\n  \
    \      adjacent[e.to][e.from] = true;\n    }\n    return adjacent;\n}\n\nstd::vector<std::vector<char>>\
    \ complement_adjacency_matrix(const std::vector<std::vector<char>>& adjacent)\
    \ {\n    int n = int(adjacent.size());\n    std::vector<std::vector<char>> complement(n,\
    \ std::vector<char>(n, false));\n    for (int i = 0; i < n; i++) {\n        for\
    \ (int j = i + 1; j < n; j++) {\n            if (adjacent[i][j]) continue;\n \
    \           complement[i][j] = true;\n            complement[j][i] = true;\n \
    \       }\n    }\n    return complement;\n}\n\n}  // namespace detail\n\ntemplate\
    \ <class T>\nbool is_clique(const Graph<T>& g, const std::vector<int>& vertices)\
    \ {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n    for (int\
    \ v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n    for (int\
    \ i = 0; i < int(vertices.size()); i++) {\n        for (int j = i + 1; j < int(vertices.size());\
    \ j++) {\n            if (!adjacent[vertices[i]][vertices[j]]) return false;\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nbool is_independent_set(const\
    \ Graph<T>& g, const std::vector<int>& vertices) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    for (int v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n\
    \    for (int i = 0; i < int(vertices.size()); i++) {\n        for (int j = i\
    \ + 1; j < int(vertices.size()); j++) {\n            if (adjacent[vertices[i]][vertices[j]])\
    \ return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class T>\n\
    bool is_vertex_cover(const Graph<T>& g, const std::vector<int>& vertices) {\n\
    \    std::vector<char> selected(g.size(), false);\n    for (int v : vertices)\
    \ {\n        assert(0 <= v && v < g.size());\n        selected[v] = true;\n  \
    \  }\n    for (const auto& e : g.edges()) {\n        if (e.from == e.to) continue;\n\
    \        if (!selected[e.from] && !selected[e.to]) return false;\n    }\n    return\
    \ true;\n}\n\ntemplate <class T>\nMaximumCliqueResult maximum_clique(const Graph<T>&\
    \ g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n    auto\
    \ complement = detail::complement_adjacency_matrix(adjacent);\n    detail::MaximumIndependentSetBranching\
    \ solver(complement);\n    return MaximumCliqueResult{solver.solve()};\n}\n\n\
    template <class T>\nint maximum_clique_size(const Graph<T>& g) {\n    return maximum_clique(g).size();\n\
    }\n\ntemplate <class T>\nMaximumIndependentSetResult maximum_independent_set(const\
    \ Graph<T>& g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    detail::MaximumIndependentSetBranching solver(adjacent);\n    return MaximumIndependentSetResult{solver.solve()};\n\
    }\n\ntemplate <class T>\nint maximum_independent_set_size(const Graph<T>& g) {\n\
    \    return maximum_independent_set(g).size();\n}\n\ntemplate <class T>\nMinimumVertexCoverResult\
    \ minimum_vertex_cover(const Graph<T>& g) {\n    auto independent = maximum_independent_set(g);\n\
    \    std::vector<char> in_independent(g.size(), false);\n    for (int v : independent.vertices)\
    \ in_independent[v] = true;\n\n    MinimumVertexCoverResult result;\n    for (int\
    \ v = 0; v < g.size(); v++) {\n        if (!in_independent[v]) result.vertices.push_back(v);\n\
    \    }\n    return result;\n}\n\ntemplate <class T>\nint minimum_vertex_cover_size(const\
    \ Graph<T>& g) {\n    return minimum_vertex_cover(g).size();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/minimum_steiner_tree.hpp\"\
    \n\n\n\n#line 15 \"graph/minimum_steiner_tree.hpp\"\n\n#line 17 \"graph/minimum_steiner_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class Cost>\nstruct MinimumSteinerTreeResult\
    \ {\n    Cost cost;\n    std::vector<int> edge_ids;\n    std::vector<int> vertices;\n\
    };\n\nnamespace internal {\n\ninline std::vector<int> steiner_terminals(int n,\
    \ std::vector<int> terminals) {\n    for (int v : terminals) assert(0 <= v &&\
    \ v < n);\n    std::sort(terminals.begin(), terminals.end());\n    terminals.erase(std::unique(terminals.begin(),\
    \ terminals.end()), terminals.end());\n    assert(terminals.size() < std::numeric_limits<std::size_t>::digits);\n\
    \    return terminals;\n}\n\ntemplate <class Cost>\nstruct MinimumSteinerTreeDp\
    \ {\n    Cost cost;\n    Cost inf;\n    std::size_t states;\n    std::size_t width;\n\
    \    std::vector<Cost> dp;\n    std::vector<int> terminals;\n};\n\ntemplate <class\
    \ Cost, class GraphCost, class EdgeCost>\nstd::optional<MinimumSteinerTreeDp<Cost>>\
    \ minimum_steiner_tree_dp(\n    const Graph<GraphCost>& g,\n    std::vector<int>\
    \ terminals,\n    const std::vector<Cost>& vertex_cost,\n    EdgeCost edge_cost,\n\
    \    Cost inf\n) {\n    const int n = g.size();\n    assert(vertex_cost.size()\
    \ == std::size_t(n));\n    for (Cost cost : vertex_cost) assert(Cost(0) <= cost);\n\
    \    terminals = steiner_terminals(n, std::move(terminals));\n    const int k\
    \ = int(terminals.size());\n    if (k == 0) return MinimumSteinerTreeDp<Cost>{Cost(0),\
    \ inf, 1, std::size_t(n), {}, {}};\n\n    assert(Cost(0) < inf);\n    for (int\
    \ v = 0; v < n; v++) {\n        for (const auto& edge : g[v]) {\n            if\
    \ (edge.alive) assert(Cost(0) <= edge_cost(edge));\n        }\n    }\n\n    const\
    \ std::size_t states = std::size_t(1) << k;\n    const std::size_t width = std::size_t(n);\n\
    \    assert(width <= std::numeric_limits<std::size_t>::max() / states);\n    std::vector<Cost>\
    \ dp(states * width, inf);\n    for (int i = 0; i < k; i++) {\n        const int\
    \ terminal = terminals[i];\n        if (vertex_cost[terminal] < inf) {\n     \
    \       dp[(std::size_t(1) << i) * width + std::size_t(terminal)] = vertex_cost[terminal];\n\
    \        }\n    }\n\n    using QueueEntry = std::pair<Cost, int>;\n    for (std::size_t\
    \ mask = 1; mask < states; mask++) {\n        const std::size_t mask_offset =\
    \ mask * width;\n        for (std::size_t sub = (mask - 1) & mask; sub != 0; sub\
    \ = (sub - 1) & mask) {\n            const std::size_t other = mask ^ sub;\n \
    \           if (sub > other) continue;\n            const std::size_t sub_offset\
    \ = sub * width;\n            const std::size_t other_offset = other * width;\n\
    \            for (int v = 0; v < n; v++) {\n                const std::size_t\
    \ vertex = std::size_t(v);\n                const Cost left = dp[sub_offset +\
    \ vertex];\n                const Cost right = dp[other_offset + vertex];\n  \
    \              if (left == inf || right == inf) continue;\n                assert(vertex_cost[v]\
    \ <= right);\n                const Cost extra = right - vertex_cost[v];\n   \
    \             if (left > inf - extra) continue;\n                const Cost candidate\
    \ = left + extra;\n                Cost& current = dp[mask_offset + vertex];\n\
    \                if (candidate < current) current = candidate;\n            }\n\
    \        }\n\n        std::priority_queue<QueueEntry, std::vector<QueueEntry>,\
    \ std::greater<QueueEntry>> queue;\n        for (int v = 0; v < n; v++) {\n  \
    \          const Cost distance = dp[mask_offset + std::size_t(v)];\n         \
    \   if (distance != inf) queue.emplace(distance, v);\n        }\n        while\
    \ (!queue.empty()) {\n            auto [distance, v] = queue.top();\n        \
    \    queue.pop();\n            if (distance != dp[mask_offset + std::size_t(v)])\
    \ continue;\n            for (const auto& edge : g[v]) {\n                if (!edge.alive)\
    \ continue;\n                const Cost cost = edge_cost(edge);\n            \
    \    if (cost >= inf || vertex_cost[edge.to] > inf - cost) continue;\n       \
    \         const Cost extra = cost + vertex_cost[edge.to];\n                if\
    \ (distance > inf - extra) continue;\n                const Cost candidate = distance\
    \ + extra;\n                Cost& current = dp[mask_offset + std::size_t(edge.to)];\n\
    \                if (current <= candidate) continue;\n                current\
    \ = candidate;\n                queue.emplace(candidate, edge.to);\n         \
    \   }\n        }\n    }\n\n    const auto answer_begin = dp.begin() + (states\
    \ - 1) * width;\n    const Cost answer = *std::min_element(answer_begin, dp.end());\n\
    \    if (answer == inf) return std::nullopt;\n    return MinimumSteinerTreeDp<Cost>{\n\
    \        answer,\n        inf,\n        states,\n        width,\n        std::move(dp),\n\
    \        std::move(terminals)\n    };\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeDp<int>>\
    \ minimum_steiner_tree_unweighted_dp(\n    const Graph<T>& g,\n    std::vector<int>\
    \ terminals\n) {\n    const int n = g.size();\n    terminals = steiner_terminals(n,\
    \ std::move(terminals));\n    const int k = int(terminals.size());\n    if (k\
    \ == 0) return MinimumSteinerTreeDp<int>{0, n, 1, std::size_t(n), {}, {}};\n\n\
    \    const std::size_t states = std::size_t(1) << k;\n    const std::size_t width\
    \ = std::size_t(n);\n    assert(width <= std::numeric_limits<std::size_t>::max()\
    \ / states);\n    const int inf = n;\n    std::vector<int> dp(states * width,\
    \ inf);\n    for (int i = 0; i < k; i++) {\n        dp[(std::size_t(1) << i) *\
    \ width + std::size_t(terminals[i])] = 0;\n    }\n\n    for (std::size_t mask\
    \ = 1; mask < states; mask++) {\n        const std::size_t mask_offset = mask\
    \ * width;\n        for (std::size_t sub = (mask - 1) & mask; sub != 0; sub =\
    \ (sub - 1) & mask) {\n            const std::size_t other = mask ^ sub;\n   \
    \         if (sub > other) continue;\n            const std::size_t sub_offset\
    \ = sub * width;\n            const std::size_t other_offset = other * width;\n\
    \            for (int v = 0; v < n; v++) {\n                const std::size_t\
    \ vertex = std::size_t(v);\n                const int candidate = dp[sub_offset\
    \ + vertex] + dp[other_offset + vertex];\n                int& current = dp[mask_offset\
    \ + vertex];\n                if (candidate < current) current = candidate;\n\
    \            }\n        }\n\n        std::vector<int> bucket_head(n, -1);\n  \
    \      std::vector<int> entry_vertex;\n        std::vector<int> entry_next;\n\
    \        entry_vertex.reserve(2 * width);\n        entry_next.reserve(2 * width);\n\
    \        auto push = [&](int distance, int v) {\n            entry_vertex.push_back(v);\n\
    \            entry_next.push_back(bucket_head[distance]);\n            bucket_head[distance]\
    \ = int(entry_vertex.size()) - 1;\n        };\n        for (int v = 0; v < n;\
    \ v++) {\n            const int distance = dp[mask_offset + std::size_t(v)];\n\
    \            if (distance != inf) push(distance, v);\n        }\n        for (int\
    \ distance = 0; distance < n; distance++) {\n            for (int entry = bucket_head[distance];\
    \ entry != -1; entry = entry_next[entry]) {\n                const int v = entry_vertex[entry];\n\
    \                if (dp[mask_offset + std::size_t(v)] != distance) continue;\n\
    \                for (const auto& edge : g[v]) {\n                    if (!edge.alive)\
    \ continue;\n                    int& current = dp[mask_offset + std::size_t(edge.to)];\n\
    \                    if (distance + 1 >= current) continue;\n                \
    \    current = distance + 1;\n                    push(current, edge.to);\n  \
    \              }\n            }\n        }\n    }\n\n    const auto answer_begin\
    \ = dp.begin() + (states - 1) * width;\n    const int answer = *std::min_element(answer_begin,\
    \ dp.end());\n    if (answer == inf) return std::nullopt;\n    return MinimumSteinerTreeDp<int>{\n\
    \        answer,\n        inf,\n        states,\n        width,\n        std::move(dp),\n\
    \        std::move(terminals)\n    };\n}\n\ntemplate <class Cost, class GraphCost,\
    \ class EdgeCost>\nMinimumSteinerTreeResult<Cost> restore_minimum_steiner_tree(\n\
    \    const Graph<GraphCost>& g,\n    const MinimumSteinerTreeDp<Cost>& data,\n\
    \    const std::vector<Cost>& vertex_cost,\n    EdgeCost edge_cost\n) {\n    MinimumSteinerTreeResult<Cost>\
    \ result;\n    result.cost = data.cost;\n    if (data.terminals.empty()) return\
    \ result;\n\n    const int n = g.size();\n    const std::size_t cells = data.states\
    \ * data.width;\n    std::vector<char> state(cells, 0);\n    std::vector<char>\
    \ selected_edge(g.edge_count(), false);\n\n    std::function<bool(std::size_t,\
    \ int)> restore = [&](std::size_t mask, int start) {\n        const std::size_t\
    \ position = mask * data.width + std::size_t(start);\n        if (state[position]\
    \ == 2) return true;\n        if (state[position] == 1) return false;\n      \
    \  state[position] = 1;\n\n        std::vector<int> search_parent(n, -2), search_edge(n,\
    \ -1), stack;\n        search_parent[start] = -1;\n        stack.push_back(start);\n\
    \        int seed = -1;\n        std::size_t seed_split = 0;\n\n        while\
    \ (!stack.empty() && seed == -1) {\n            const int v = stack.back();\n\
    \            stack.pop_back();\n            const std::size_t vertex_position\
    \ = mask * data.width + std::size_t(v);\n            const Cost current = data.dp[vertex_position];\n\
    \n            if (v != start && state[vertex_position] == 2) {\n             \
    \   seed = v;\n                break;\n            }\n            if ((mask &\
    \ (mask - 1)) == 0) {\n                const int terminal_index = int(std::countr_zero(mask));\n\
    \                if (v == data.terminals[terminal_index] && current == vertex_cost[v])\
    \ {\n                    seed = v;\n                    break;\n             \
    \   }\n            }\n            for (std::size_t sub = (mask - 1) & mask; sub\
    \ != 0; sub = (sub - 1) & mask) {\n                const std::size_t other = mask\
    \ ^ sub;\n                if (sub > other) continue;\n                const Cost\
    \ left = data.dp[sub * data.width + std::size_t(v)];\n                const Cost\
    \ right = data.dp[other * data.width + std::size_t(v)];\n                if (left\
    \ == data.inf || right == data.inf || right < vertex_cost[v]) continue;\n    \
    \            const Cost extra = right - vertex_cost[v];\n                if (left\
    \ > data.inf - extra || left + extra != current) continue;\n                seed\
    \ = v;\n                seed_split = sub;\n                break;\n          \
    \  }\n            if (seed != -1) break;\n\n            for (const auto& edge\
    \ : g[v]) {\n                if (!edge.alive || search_parent[edge.to] != -2)\
    \ continue;\n                const Cost cost = edge_cost(edge);\n            \
    \    if (cost >= data.inf || vertex_cost[v] > data.inf - cost) continue;\n   \
    \             const Cost extra = cost + vertex_cost[v];\n                const\
    \ Cost previous = data.dp[mask * data.width + std::size_t(edge.to)];\n       \
    \         if (previous == data.inf || previous > data.inf - extra) continue;\n\
    \                if (previous + extra != current) continue;\n                search_parent[edge.to]\
    \ = v;\n                search_edge[edge.to] = edge.id;\n                stack.push_back(edge.to);\n\
    \            }\n        }\n\n        if (seed == -1) {\n            state[position]\
    \ = 0;\n            return false;\n        }\n        if (seed_split != 0) {\n\
    \            const bool restored_left = restore(seed_split, seed);\n         \
    \   const bool restored_right = restore(mask ^ seed_split, seed);\n          \
    \  assert(restored_left && restored_right);\n            if (!restored_left ||\
    \ !restored_right) {\n                state[position] = 0;\n                return\
    \ false;\n            }\n        }\n\n        for (int v = seed; v != -1; v =\
    \ search_parent[v]) {\n            state[mask * data.width + std::size_t(v)] =\
    \ 2;\n            if (search_parent[v] == -1) continue;\n            const int\
    \ id = search_edge[v];\n            assert(0 <= id && id < g.edge_count());\n\
    \            selected_edge[id] = true;\n        }\n        return true;\n    };\n\
    \n    int root = -1;\n    const std::size_t full_mask = data.states - 1;\n   \
    \ for (int v = 0; v < n; v++) {\n        if (data.dp[full_mask * data.width +\
    \ std::size_t(v)] == data.cost) {\n            root = v;\n            break;\n\
    \        }\n    }\n    assert(root != -1);\n    const bool restored = restore(full_mask,\
    \ root);\n    assert(restored);\n    (void)restored;\n\n    std::vector<Edge<GraphCost>>\
    \ edge_by_id(g.edge_count());\n    std::vector<char> has_edge(g.edge_count(),\
    \ false);\n    for (const auto& edge : g.edges()) {\n        edge_by_id[edge.id]\
    \ = edge;\n        has_edge[edge.id] = true;\n    }\n\n    std::vector<int> parent(n),\
    \ component_size(n, 1);\n    for (int v = 0; v < n; v++) parent[v] = v;\n    auto\
    \ leader = [&](auto&& self, int v) -> int {\n        if (parent[v] == v) return\
    \ v;\n        return parent[v] = self(self, parent[v]);\n    };\n\n    std::vector<char>\
    \ tree_edge(g.edge_count(), false);\n    for (int id = 0; id < g.edge_count();\
    \ id++) {\n        if (!selected_edge[id]) continue;\n        assert(has_edge[id]);\n\
    \        const auto& edge = edge_by_id[id];\n        int u = leader(leader, edge.from);\n\
    \        int v = leader(leader, edge.to);\n        if (u == v) continue;\n   \
    \     if (component_size[u] < component_size[v]) std::swap(u, v);\n        parent[v]\
    \ = u;\n        component_size[u] += component_size[v];\n        tree_edge[id]\
    \ = true;\n    }\n\n    std::vector<std::vector<std::pair<int, int>>> tree(n);\n\
    \    std::vector<int> degree(n, 0);\n    std::vector<char> in_tree(n, false),\
    \ is_terminal(n, false);\n    for (int terminal : data.terminals) {\n        in_tree[terminal]\
    \ = true;\n        is_terminal[terminal] = true;\n    }\n    for (int id = 0;\
    \ id < g.edge_count(); id++) {\n        if (!tree_edge[id]) continue;\n      \
    \  const auto& edge = edge_by_id[id];\n        tree[edge.from].emplace_back(edge.to,\
    \ id);\n        tree[edge.to].emplace_back(edge.from, id);\n        degree[edge.from]++;\n\
    \        degree[edge.to]++;\n        in_tree[edge.from] = true;\n        in_tree[edge.to]\
    \ = true;\n    }\n\n    std::queue<int> leaves;\n    for (int v = 0; v < n; v++)\
    \ {\n        if (in_tree[v] && !is_terminal[v] && degree[v] <= 1) leaves.push(v);\n\
    \    }\n    std::vector<char> removed_vertex(n, false), removed_edge(g.edge_count(),\
    \ false);\n    while (!leaves.empty()) {\n        const int v = leaves.front();\n\
    \        leaves.pop();\n        if (removed_vertex[v] || is_terminal[v] || degree[v]\
    \ > 1) continue;\n        removed_vertex[v] = true;\n        for (auto [to, id]\
    \ : tree[v]) {\n            if (removed_edge[id]) continue;\n            removed_edge[id]\
    \ = true;\n            degree[v]--;\n            degree[to]--;\n            if\
    \ (!is_terminal[to] && degree[to] <= 1) leaves.push(to);\n            break;\n\
    \        }\n    }\n\n    Cost restored_cost = Cost(0);\n    for (int id = 0; id\
    \ < g.edge_count(); id++) {\n        if (!tree_edge[id] || removed_edge[id]) continue;\n\
    \        result.edge_ids.push_back(id);\n        restored_cost += edge_cost(edge_by_id[id]);\n\
    \    }\n    for (int v = 0; v < n; v++) {\n        if (!in_tree[v] || removed_vertex[v])\
    \ continue;\n        result.vertices.push_back(v);\n        restored_cost += vertex_cost[v];\n\
    \    }\n    if constexpr (std::is_integral_v<Cost>) assert(restored_cost == result.cost);\n\
    \    result.cost = restored_cost;\n    return result;\n}\n\n}  // namespace internal\n\
    \ntemplate <class T>\nstd::optional<T> minimum_steiner_tree(\n    const Graph<T>&\
    \ g,\n    std::vector<int> terminals,\n    const std::vector<T>& vertex_cost,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    auto result = internal::minimum_steiner_tree_dp(\n\
    \        g,\n        std::move(terminals),\n        vertex_cost,\n        [](const\
    \ Edge<T>& edge) { return edge.cost; },\n        inf\n    );\n    if (!result)\
    \ return std::nullopt;\n    return result->cost;\n}\n\ntemplate <class T>\nstd::optional<T>\
    \ minimum_steiner_tree(\n    const Graph<T>& g,\n    std::vector<int> terminals,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    return minimum_steiner_tree(g,\
    \ std::move(terminals), std::vector<T>(g.size(), T(0)), inf);\n}\n\ntemplate <class\
    \ GraphCost, class Cost>\nstd::optional<Cost> minimum_steiner_tree_unweighted(\n\
    \    const Graph<GraphCost>& g,\n    std::vector<int> terminals,\n    const std::vector<Cost>&\
    \ vertex_cost,\n    Cost inf = std::numeric_limits<Cost>::max() / Cost(4)\n) {\n\
    \    auto result = internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<GraphCost>&) { return Cost(1); },\n\
    \        inf\n    );\n    if (!result) return std::nullopt;\n    return result->cost;\n\
    }\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<T>> build_minimum_steiner_tree(\n\
    \    const Graph<T>& g,\n    std::vector<int> terminals,\n    const std::vector<T>&\
    \ vertex_cost,\n    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    auto\
    \ data = internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<T>& edge) { return edge.cost; },\n\
    \        inf\n    );\n    if (!data) return std::nullopt;\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<T>& edge)\
    \ { return edge.cost; }\n    );\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<T>>\
    \ build_minimum_steiner_tree(\n    const Graph<T>& g,\n    std::vector<int> terminals,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    std::vector<T> vertex_cost(g.size(),\
    \ T(0));\n    return build_minimum_steiner_tree(g, std::move(terminals), vertex_cost,\
    \ inf);\n}\n\ntemplate <class GraphCost, class Cost>\nstd::optional<MinimumSteinerTreeResult<Cost>>\
    \ build_minimum_steiner_tree_unweighted(\n    const Graph<GraphCost>& g,\n   \
    \ std::vector<int> terminals,\n    const std::vector<Cost>& vertex_cost,\n   \
    \ Cost inf = std::numeric_limits<Cost>::max() / Cost(4)\n) {\n    auto data =\
    \ internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<GraphCost>&) { return Cost(1); },\n\
    \        inf\n    );\n    if (!data) return std::nullopt;\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<GraphCost>&)\
    \ { return Cost(1); }\n    );\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<int>>\
    \ build_minimum_steiner_tree_unweighted(\n    const Graph<T>& g,\n    std::vector<int>\
    \ terminals\n) {\n    auto data = internal::minimum_steiner_tree_unweighted_dp(g,\
    \ std::move(terminals));\n    if (!data) return std::nullopt;\n    std::vector<int>\
    \ vertex_cost(g.size(), 0);\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<T>&)\
    \ { return 1; }\n    );\n}\n\ntemplate <class T>\nstd::optional<int> minimum_steiner_tree_unweighted(\n\
    \    const Graph<T>& g,\n    std::vector<int> terminals\n) {\n    auto result\
    \ = internal::minimum_steiner_tree_unweighted_dp(g, std::move(terminals));\n \
    \   if (!result) return std::nullopt;\n    return result->cost;\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/namori.hpp\"\n\n\n\n#line\
    \ 9 \"graph/namori.hpp\"\n\n#line 11 \"graph/namori.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\ntemplate <class T>\nstruct NamoriDecomposition {\n    int\
    \ component_count;\n    std::vector<std::vector<int>> cycles;\n    std::vector<std::vector<int>>\
    \ cycle_edge_ids;\n    std::vector<std::vector<T>> cycle_edge_costs;\n\n    std::vector<bool>\
    \ on_cycle;\n    std::vector<int> component;\n    std::vector<int> cycle_root;\n\
    \    std::vector<int> cycle_position;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> depth;\n    std::vector<T> dist_to_cycle;\n\
    \    std::vector<std::vector<int>> children;\n\n    bool same_component(int u,\
    \ int v) const {\n        assert(0 <= u && u < int(component.size()));\n     \
    \   assert(0 <= v && v < int(component.size()));\n        return component[u]\
    \ == component[v];\n    }\n\n    bool same_tree(int u, int v) const {\n      \
    \  assert(0 <= u && u < int(cycle_root.size()));\n        assert(0 <= v && v <\
    \ int(cycle_root.size()));\n        return cycle_root[u] == cycle_root[v];\n \
    \   }\n};\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> namori_decomposition(const\
    \ Graph<T>& graph) {\n    int n = graph.size();\n    NamoriDecomposition<T> result;\n\
    \    result.component_count = 0;\n    result.on_cycle.assign(n, false);\n    result.component.assign(n,\
    \ -1);\n    result.cycle_root.assign(n, -1);\n    result.cycle_position.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.depth.assign(n, 0);\n    result.dist_to_cycle.assign(n, T(0));\n \
    \   result.children.assign(n, {});\n    if (n == 0) return result;\n\n    std::vector<int>\
    \ degree(n, 0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& edge\
    \ : graph[v]) {\n            if (edge.alive) degree[v]++;\n        }\n    }\n\n\
    \    std::queue<int> queue;\n    std::vector<bool> removed(n, false);\n    for\
    \ (int v = 0; v < n; v++) {\n        if (degree[v] <= 1) queue.push(v);\n    }\n\
    \    while (!queue.empty()) {\n        int v = queue.front();\n        queue.pop();\n\
    \        if (removed[v] || degree[v] > 1) continue;\n        removed[v] = true;\n\
    \        for (const auto& edge : graph[v]) {\n            if (!edge.alive || removed[edge.to])\
    \ continue;\n            degree[edge.to]--;\n            if (degree[edge.to] ==\
    \ 1) queue.push(edge.to);\n        }\n    }\n\n    for (int v = 0; v < n; v++)\
    \ {\n        result.on_cycle[v] = !removed[v];\n    }\n    for (int v = 0; v <\
    \ n; v++) {\n        if (!result.on_cycle[v]) continue;\n        int cycle_degree\
    \ = 0;\n        for (const auto& edge : graph[v]) {\n            if (edge.alive\
    \ && result.on_cycle[edge.to]) cycle_degree++;\n        }\n        if (cycle_degree\
    \ != 2) return std::nullopt;\n    }\n\n    std::vector<bool> cycle_visited(n,\
    \ false);\n    for (int start = 0; start < n; start++) {\n        if (!result.on_cycle[start]\
    \ || cycle_visited[start]) continue;\n        int component_id = int(result.cycles.size());\n\
    \        std::vector<int> vertices;\n        std::vector<int> edge_ids;\n    \
    \    std::vector<T> edge_costs;\n\n        int current = start;\n        int previous_edge\
    \ = -1;\n        while (true) {\n            if (cycle_visited[current]) return\
    \ std::nullopt;\n            cycle_visited[current] = true;\n            vertices.push_back(current);\n\
    \n            int next_vertex = -1;\n            int next_edge = -1;\n       \
    \     T next_cost = T(0);\n            for (const auto& edge : graph[current])\
    \ {\n                if (!edge.alive || !result.on_cycle[edge.to] || edge.id ==\
    \ previous_edge) continue;\n                next_vertex = edge.to;\n         \
    \       next_edge = edge.id;\n                next_cost = edge.cost;\n       \
    \         break;\n            }\n            if (next_edge == -1) return std::nullopt;\n\
    \            edge_ids.push_back(next_edge);\n            edge_costs.push_back(next_cost);\n\
    \            if (next_vertex == start) break;\n            previous_edge = next_edge;\n\
    \            current = next_vertex;\n            if (int(vertices.size()) > n)\
    \ return std::nullopt;\n        }\n\n        for (int position = 0; position <\
    \ int(vertices.size()); position++) {\n            int v = vertices[position];\n\
    \            result.component[v] = component_id;\n            result.cycle_root[v]\
    \ = v;\n            result.cycle_position[v] = position;\n        }\n        result.cycles.push_back(std::move(vertices));\n\
    \        result.cycle_edge_ids.push_back(std::move(edge_ids));\n        result.cycle_edge_costs.push_back(std::move(edge_costs));\n\
    \    }\n    if (result.cycles.empty()) return std::nullopt;\n\n    std::vector<int>\
    \ stack;\n    stack.reserve(n);\n    for (const auto& cycle : result.cycles) {\n\
    \        for (int v : cycle) stack.push_back(v);\n    }\n    while (!stack.empty())\
    \ {\n        int v = stack.back();\n        stack.pop_back();\n        for (const\
    \ auto& edge : graph[v]) {\n            if (!edge.alive || result.on_cycle[edge.to]\
    \ || edge.id == result.parent_edge[v]) continue;\n            int to = edge.to;\n\
    \            if (result.component[to] != -1) continue;\n            result.component[to]\
    \ = result.component[v];\n            result.cycle_root[to] = result.cycle_root[v];\n\
    \            result.cycle_position[to] = result.cycle_position[v];\n         \
    \   result.parent[to] = v;\n            result.parent_edge[to] = edge.id;\n  \
    \          result.depth[to] = result.depth[v] + 1;\n            result.dist_to_cycle[to]\
    \ = result.dist_to_cycle[v] + edge.cost;\n            result.children[v].push_back(to);\n\
    \            stack.push_back(to);\n        }\n    }\n    for (int v = 0; v < n;\
    \ v++) {\n        if (result.component[v] == -1) return std::nullopt;\n    }\n\
    \n    result.component_count = int(result.cycles.size());\n    return result;\n\
    }\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> decompose_namori(const\
    \ Graph<T>& graph) {\n    return namori_decomposition(graph);\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/replacement_paths.hpp\"\n\n\
    \n\n#line 11 \"graph/replacement_paths.hpp\"\n\n#line 1 \"graph/dijkstra.hpp\"\
    \n\n\n\n#line 11 \"graph/dijkstra.hpp\"\n\n#line 13 \"graph/dijkstra.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DijkstraResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    T inf;\n\n    bool reachable(int v) const {\n        assert(0\
    \ <= v && v < int(dist.size()));\n        return dist[v] != inf;\n    }\n\n  \
    \  std::vector<int> path(int t) const {\n        assert(reachable(t));\n     \
    \   std::vector<int> result;\n        for (int v = t; v != -1; v = parent[v])\
    \ result.push_back(v);\n        std::reverse(result.begin(), result.end());\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nDijkstraResult<T> dijkstra(const\
    \ Graph<T>& g, const std::vector<int>& sources,\n                           T\
    \ inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    DijkstraResult<T>\
    \ result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n, -1);\n\
    \    result.parent_edge.assign(n, -1);\n    result.inf = inf;\n\n    using P =\
    \ std::pair<T, int>;\n    std::priority_queue<P, std::vector<P>, std::greater<P>>\
    \ que;\n    for (int s : sources) {\n        assert(0 <= s && s < n);\n      \
    \  if (result.dist[s] == T(0)) continue;\n        result.dist[s] = T(0);\n   \
    \     que.emplace(T(0), s);\n    }\n\n    while (!que.empty()) {\n        auto\
    \ [d, v] = que.top();\n        que.pop();\n        if (result.dist[v] != d) continue;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           T nd = d + e.cost;\n            if (result.dist[e.to] <= nd) continue;\n\
    \            result.dist[e.to] = nd;\n            result.parent[e.to] = v;\n \
    \           result.parent_edge[e.to] = e.id;\n            que.emplace(nd, e.to);\n\
    \        }\n    }\n\n    return result;\n}\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4))\
    \ {\n    return dijkstra(g, std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 14 \"graph/replacement_paths.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct GraphPath {\n    std::vector<int> vertices;\n\
    \    std::vector<int> edges;\n};\n\ntemplate <class T>\nstruct EdgeReplacementPathsResult\
    \ {\n    GraphPath path;\n    std::vector<T> replacement_dist;\n    T inf;\n\n\
    \    bool reachable(int path_edge_index) const {\n        assert(0 <= path_edge_index\
    \ && path_edge_index < int(replacement_dist.size()));\n        return replacement_dist[path_edge_index]\
    \ != inf;\n    }\n};\n\ntemplate <class T>\nstruct VertexReplacementPathsResult\
    \ {\n    GraphPath path;\n    std::vector<T> replacement_dist;\n    T inf;\n\n\
    \    bool reachable(int path_vertex_index) const {\n        assert(0 <= path_vertex_index\
    \ && path_vertex_index < int(replacement_dist.size()));\n        return replacement_dist[path_vertex_index]\
    \ != inf;\n    }\n};\n\nnamespace internal {\n\ntemplate <class T>\nT replacement_paths_safe_add(T\
    \ a, T b, T inf) {\n    if (a >= inf || b >= inf) return inf;\n    if (a > inf\
    \ - b) return inf;\n    return a + b;\n}\n\ntemplate <class T>\nDijkstraResult<T>\
    \ replacement_paths_dijkstra(const Graph<T>& g, int s, T inf) {\n    int n = g.size();\n\
    \    assert(0 <= s && s < n);\n    DijkstraResult<T> result;\n    result.dist.assign(n,\
    \ inf);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.inf = inf;\n\n    using P = std::pair<T, int>;\n    std::priority_queue<P,\
    \ std::vector<P>, std::greater<P>> que;\n    result.dist[s] = T(0);\n    que.emplace(T(0),\
    \ s);\n    while (!que.empty()) {\n        auto [d, v] = que.top();\n        que.pop();\n\
    \        if (result.dist[v] != d) continue;\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            T nd = replacement_paths_safe_add(d,\
    \ e.cost, inf);\n            if (result.dist[e.to] <= nd) continue;\n        \
    \    result.dist[e.to] = nd;\n            result.parent[e.to] = v;\n         \
    \   result.parent_edge[e.to] = e.id;\n            que.emplace(nd, e.to);\n   \
    \     }\n    }\n    return result;\n}\n\ntemplate <class T>\nstd::vector<Edge<T>>\
    \ replacement_paths_validate_graph(const Graph<T>& g, T inf) {\n    assert(T(0)\
    \ < inf);\n    std::vector<int> occurrence(g.edge_count(), 0);\n    std::vector<Edge<T>>\
    \ edge_by_id(g.edge_count());\n    for (int v = 0; v < g.size(); v++) {\n    \
    \    for (const auto& e : g[v]) {\n            assert(e.from == v);\n        \
    \    assert(0 <= e.to && e.to < g.size());\n            assert(0 <= e.id && e.id\
    \ < g.edge_count());\n            if (e.alive) assert(T(0) < e.cost);\n      \
    \      if (occurrence[e.id] == 0) {\n                edge_by_id[e.id] = e;\n \
    \           } else {\n                assert(occurrence[e.id] == 1);\n       \
    \         const auto& other = edge_by_id[e.id];\n                assert(e.from\
    \ == other.to && e.to == other.from);\n                assert(e.cost == other.cost\
    \ && e.alive == other.alive);\n            }\n            occurrence[e.id]++;\n\
    \        }\n    }\n\n    for (int id = 0; id < g.edge_count(); id++) {\n     \
    \   // add_edge creates exactly two mutually reversed arcs with one logical id.\n\
    \        assert(occurrence[id] == 2);\n    }\n    return edge_by_id;\n}\n\ntemplate\
    \ <class T>\nvoid replacement_paths_validate_path(const Graph<T>& g, const GraphPath&\
    \ path,\n                                     const std::vector<Edge<T>>& edge_by_id,\n\
    \                                     const DijkstraResult<T>& from_s) {\n   \
    \ assert(!path.vertices.empty());\n    assert(path.edges.size() + 1 == path.vertices.size());\n\
    \    std::vector<char> used_vertex(g.size(), false);\n    for (int v : path.vertices)\
    \ {\n        assert(0 <= v && v < g.size());\n        assert(!used_vertex[v]);\n\
    \        used_vertex[v] = true;\n    }\n\n    T path_cost = T(0);\n    for (int\
    \ i = 0; i < int(path.edges.size()); i++) {\n        int id = path.edges[i];\n\
    \        assert(0 <= id && id < g.edge_count());\n        assert(g.is_edge_alive(id));\n\
    \        const auto& e = edge_by_id[id];\n        int u = path.vertices[i];\n\
    \        int v = path.vertices[i + 1];\n        assert((e.from == u && e.to ==\
    \ v) || (e.from == v && e.to == u));\n        assert(T(0) < e.cost);\n       \
    \ path_cost = replacement_paths_safe_add(path_cost, e.cost, from_s.inf);\n   \
    \ }\n    assert(from_s.reachable(path.vertices.back()));\n    assert(path_cost\
    \ == from_s.dist[path.vertices.back()]);\n}\n\ntemplate <class T>\nGraphPath replacement_paths_restore_path(const\
    \ DijkstraResult<T>& result, int s, int t) {\n    assert(result.reachable(t));\n\
    \    GraphPath path;\n    for (int v = t; v != s; v = result.parent[v]) {\n  \
    \      assert(v != -1 && result.parent[v] != -1 && result.parent_edge[v] != -1);\n\
    \        path.vertices.push_back(v);\n        path.edges.push_back(result.parent_edge[v]);\n\
    \    }\n    path.vertices.push_back(s);\n    std::reverse(path.vertices.begin(),\
    \ path.vertices.end());\n    std::reverse(path.edges.begin(), path.edges.end());\n\
    \    return path;\n}\n\ntemplate <class T>\nstruct ReplacementPathsData {\n  \
    \  GraphPath path;\n    std::vector<T> dist_s;\n    std::vector<T> dist_t;\n \
    \   std::vector<int> block;\n    std::vector<char> is_path_edge;\n    std::vector<Edge<T>>\
    \ edge_by_id;\n    T inf;\n};\n\ntemplate <class T>\nReplacementPathsData<T> replacement_paths_prepare(const\
    \ Graph<T>& g, const GraphPath& path,\n                                      \
    \             T inf, const DijkstraResult<T>* known_from_s) {\n    auto edge_by_id\
    \ = replacement_paths_validate_graph(g, inf);\n    int s = path.vertices.front();\n\
    \    int t = path.vertices.back();\n    auto computed_from_s = known_from_s ==\
    \ nullptr\n                               ? replacement_paths_dijkstra(g, s, inf)\n\
    \                               : DijkstraResult<T>();\n    const auto& from_s\
    \ = known_from_s == nullptr ? computed_from_s : *known_from_s;\n    replacement_paths_validate_path(g,\
    \ path, edge_by_id, from_s);\n    auto from_t = replacement_paths_dijkstra(g,\
    \ t, inf);\n\n    int n = g.size();\n    std::vector<int> path_position(n, -1);\n\
    \    std::vector<char> is_path_edge(g.edge_count(), false);\n    for (int i =\
    \ 0; i < int(path.vertices.size()); i++) path_position[path.vertices[i]] = i;\n\
    \    for (int id : path.edges) is_path_edge[id] = true;\n\n    std::vector<int>\
    \ parent(n, -1);\n    for (int i = 0; i < int(path.edges.size()); i++) {\n   \
    \     int v = path.vertices[i + 1];\n        parent[v] = path.vertices[i];\n \
    \       const auto& e = edge_by_id[path.edges[i]];\n        assert(replacement_paths_safe_add(from_s.dist[parent[v]],\
    \ e.cost, inf) == from_s.dist[v]);\n    }\n    for (int v = 0; v < n; v++) {\n\
    \        if (!from_s.reachable(v) || v == s || path_position[v] != -1) continue;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive || !from_s.reachable(e.to))\
    \ continue;\n            if (replacement_paths_safe_add(from_s.dist[e.to], e.cost,\
    \ inf) != from_s.dist[v]) {\n                continue;\n            }\n      \
    \      parent[v] = e.to;\n            break;\n        }\n        assert(parent[v]\
    \ != -1);\n        assert(from_s.dist[parent[v]] < from_s.dist[v]);\n    }\n\n\
    \    std::vector<std::vector<int>> children(n);\n    for (int v = 0; v < n; v++)\
    \ {\n        if (parent[v] != -1) children[parent[v]].push_back(v);\n    }\n \
    \   std::vector<int> block(n, -1);\n    block[s] = 0;\n    std::vector<int> stack\
    \ = {s};\n    while (!stack.empty()) {\n        int v = stack.back();\n      \
    \  stack.pop_back();\n        for (int to : children[v]) {\n            block[to]\
    \ = path_position[to] == -1 ? block[v] : path_position[to];\n            stack.push_back(to);\n\
    \        }\n    }\n    for (int v = 0; v < n; v++) assert(!from_s.reachable(v)\
    \ || block[v] != -1);\n\n    return {path, from_s.dist, from_t.dist, block, is_path_edge,\
    \ edge_by_id, inf};\n}\n\ntemplate <class T>\nclass ReplacementPathsRangeChmin\
    \ {\n   private:\n    int _size;\n    std::vector<T> _lazy;\n\n   public:\n  \
    \  ReplacementPathsRangeChmin(int n, T inf) : _size(1) {\n        while (_size\
    \ < n) _size <<= 1;\n        _lazy.assign(2 * _size, inf);\n    }\n\n    void\
    \ apply(int l, int r, T value) {\n        assert(0 <= l && l <= r && r <= _size);\n\
    \        for (l += _size, r += _size; l < r; l >>= 1, r >>= 1) {\n           \
    \ if (l & 1) {\n                _lazy[l] = std::min(_lazy[l], value);\n      \
    \          l++;\n            }\n            if (r & 1) {\n                --r;\n\
    \                _lazy[r] = std::min(_lazy[r], value);\n            }\n      \
    \  }\n    }\n\n    std::vector<T> values(int n) {\n        for (int v = 1; v <\
    \ _size; v++) {\n            _lazy[2 * v] = std::min(_lazy[2 * v], _lazy[v]);\n\
    \            _lazy[2 * v + 1] = std::min(_lazy[2 * v + 1], _lazy[v]);\n      \
    \  }\n        return std::vector<T>(_lazy.begin() + _size, _lazy.begin() + _size\
    \ + n);\n    }\n};\n\ntemplate <class T>\nstd::vector<T> replacement_paths_solve_edges(const\
    \ ReplacementPathsData<T>& data) {\n    int answer_size = int(data.path.edges.size());\n\
    \    ReplacementPathsRangeChmin<T> range_chmin(answer_size, data.inf);\n    for\
    \ (const auto& e : data.edge_by_id) {\n        if (!e.alive || data.is_path_edge[e.id])\
    \ continue;\n        int u = e.from;\n        int v = e.to;\n        if (data.block[u]\
    \ == -1 || data.block[v] == -1 || data.block[u] == data.block[v]) continue;\n\
    \        if (data.block[u] > data.block[v]) std::swap(u, v);\n        int a =\
    \ data.block[u];\n        int b = data.block[v];\n        T candidate = replacement_paths_safe_add(data.dist_s[u],\
    \ e.cost, data.inf);\n        candidate = replacement_paths_safe_add(candidate,\
    \ data.dist_t[v], data.inf);\n        if (candidate == data.inf) continue;\n \
    \       range_chmin.apply(a, b, candidate);\n    }\n    return range_chmin.values(answer_size);\n\
    }\n\ntemplate <class T>\nT replacement_paths_without_vertex(const Graph<T>& g,\
    \ int s, int t, int removed, T inf) {\n    if (s == removed || t == removed) return\
    \ inf;\n    std::vector<T> dist(g.size(), inf);\n    using P = std::pair<T, int>;\n\
    \    std::priority_queue<P, std::vector<P>, std::greater<P>> que;\n    dist[s]\
    \ = T(0);\n    que.emplace(T(0), s);\n    while (!que.empty()) {\n        auto\
    \ [d, v] = que.top();\n        que.pop();\n        if (dist[v] != d) continue;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive || e.to == removed)\
    \ continue;\n            T nd = replacement_paths_safe_add(d, e.cost, inf);\n\
    \            if (dist[e.to] <= nd) continue;\n            dist[e.to] = nd;\n \
    \           que.emplace(nd, e.to);\n        }\n    }\n    return dist[t];\n}\n\
    \ntemplate <class T>\nstd::vector<T> replacement_paths_solve_vertices(const Graph<T>&\
    \ g,\n                                                const ReplacementPathsData<T>&\
    \ data) {\n    // One edge can cross an edge cut, but a vertex-avoiding path may\
    \ enter and\n    // leave the failed vertex's tree block through two different\
    \ detour edges.\n    int path_size = int(data.path.vertices.size());\n    std::vector<T>\
    \ answer(path_size, data.inf);\n    int s = data.path.vertices.front();\n    int\
    \ t = data.path.vertices.back();\n    for (int i = 1; i + 1 < path_size; i++)\
    \ {\n        answer[i] = replacement_paths_without_vertex(g, s, t, data.path.vertices[i],\
    \ data.inf);\n    }\n    return answer;\n}\n\n}  // namespace internal\n\ntemplate\
    \ <class T>\nEdgeReplacementPathsResult<T> edge_replacement_paths(\n    const\
    \ Graph<T>& g, const GraphPath& path, T inf = std::numeric_limits<T>::max() /\
    \ T(4)) {\n    assert(!path.vertices.empty());\n    auto data = internal::replacement_paths_prepare(\n\
    \        g, path, inf, static_cast<const DijkstraResult<T>*>(nullptr));\n    auto\
    \ replacement_dist = internal::replacement_paths_solve_edges(data);\n    return\
    \ {path, replacement_dist, inf};\n}\n\ntemplate <class T>\nEdgeReplacementPathsResult<T>\
    \ edge_replacement_paths(\n    const Graph<T>& g, int s, int t, T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    assert(0 <= s && s < g.size());\n    assert(0 <= t && t < g.size());\n\
    \    auto from_s = internal::replacement_paths_dijkstra(g, s, inf);\n    assert(from_s.reachable(t));\n\
    \    auto path = internal::replacement_paths_restore_path(from_s, s, t);\n   \
    \ auto data = internal::replacement_paths_prepare(g, path, inf, &from_s);\n  \
    \  auto replacement_dist = internal::replacement_paths_solve_edges(data);\n  \
    \  return {path, replacement_dist, inf};\n}\n\ntemplate <class T>\nVertexReplacementPathsResult<T>\
    \ vertex_replacement_paths(\n    const Graph<T>& g, const GraphPath& path, T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    assert(!path.vertices.empty());\n\
    \    auto data = internal::replacement_paths_prepare(\n        g, path, inf, static_cast<const\
    \ DijkstraResult<T>*>(nullptr));\n    auto replacement_dist = internal::replacement_paths_solve_vertices(g,\
    \ data);\n    return {path, replacement_dist, inf};\n}\n\ntemplate <class T>\n\
    VertexReplacementPathsResult<T> vertex_replacement_paths(\n    const Graph<T>&\
    \ g, int s, int t, T inf = std::numeric_limits<T>::max() / T(4)) {\n    assert(0\
    \ <= s && s < g.size());\n    assert(0 <= t && t < g.size());\n    auto from_s\
    \ = internal::replacement_paths_dijkstra(g, s, inf);\n    assert(from_s.reachable(t));\n\
    \    auto path = internal::replacement_paths_restore_path(from_s, s, t);\n   \
    \ auto data = internal::replacement_paths_prepare(g, path, inf, &from_s);\n  \
    \  auto replacement_dist = internal::replacement_paths_solve_vertices(g, data);\n\
    \    return {path, replacement_dist, inf};\n}\n\n}  // namespace graph\n}  //\
    \ namespace m1une\n\n\n#line 1 \"graph/shortest_path.hpp\"\n\n\n\n#line 1 \"graph/bellman_ford.hpp\"\
    \n\n\n\n#line 9 \"graph/bellman_ford.hpp\"\n\n#line 11 \"graph/bellman_ford.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct BellmanFordResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<bool> negative;\n    T inf;\n    bool has_negative_cycle;\n\
    \n    bool reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    bool affected_by_negative_cycle(int\
    \ v) const {\n        assert(0 <= v && v < int(negative.size()));\n        return\
    \ negative[v];\n    }\n\n    std::vector<int> path(int t) const {\n        assert(reachable(t));\n\
    \        assert(!affected_by_negative_cycle(t));\n        std::vector<int> result;\n\
    \        for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n      \
    \  std::reverse(result.begin(), result.end());\n        return result;\n    }\n\
    };\n\ntemplate <class T>\nBellmanFordResult<T> bellman_ford(const Graph<T>& g,\
    \ const std::vector<int>& sources,\n                                  T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    BellmanFordResult<T>\
    \ result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n, -1);\n\
    \    result.parent_edge.assign(n, -1);\n    result.negative.assign(n, false);\n\
    \    result.inf = inf;\n    result.has_negative_cycle = false;\n\n    for (int\
    \ s : sources) {\n        assert(0 <= s && s < n);\n        result.dist[s] = T(0);\n\
    \    }\n\n    std::vector<int> relaxed_vertices;\n    for (int iter = 0; iter\
    \ < n; iter++) {\n        bool updated = false;\n        for (int v = 0; v < n;\
    \ v++) {\n            if (result.dist[v] == inf) continue;\n            for (const\
    \ auto& e : g[v]) {\n                if (!e.alive) continue;\n               \
    \ T nd = result.dist[v] + e.cost;\n                if (result.dist[e.to] <= nd)\
    \ continue;\n                result.dist[e.to] = nd;\n                result.parent[e.to]\
    \ = v;\n                result.parent_edge[e.to] = e.id;\n                updated\
    \ = true;\n                if (iter == n - 1) relaxed_vertices.push_back(e.to);\n\
    \            }\n        }\n        if (!updated) break;\n    }\n\n    std::queue<int>\
    \ que;\n    for (int v : relaxed_vertices) {\n        if (result.negative[v])\
    \ continue;\n        result.negative[v] = true;\n        que.push(v);\n    }\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (result.negative[e.to]) continue;\n            result.negative[e.to]\
    \ = true;\n            que.push(e.to);\n        }\n    }\n\n    for (bool x :\
    \ result.negative) result.has_negative_cycle = result.has_negative_cycle || x;\n\
    \    return result;\n}\n\ntemplate <class T>\nBellmanFordResult<T> bellman_ford(const\
    \ Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4)) {\n    return\
    \ bellman_ford(g, std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n}  //\
    \ namespace m1une\n\n\n#line 1 \"graph/bfs.hpp\"\n\n\n\n#line 8 \"graph/bfs.hpp\"\
    \n\n#line 10 \"graph/bfs.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct\
    \ BfsResult {\n    std::vector<int> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n\n    bool reachable(int v) const {\n        assert(0 <= v &&\
    \ v < int(dist.size()));\n        return dist[v] != -1;\n    }\n\n    std::vector<int>\
    \ path(int t) const {\n        assert(reachable(t));\n        std::vector<int>\
    \ result;\n        for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n\
    \        std::reverse(result.begin(), result.end());\n        return result;\n\
    \    }\n};\n\ntemplate <class T>\nBfsResult bfs(const Graph<T>& g, const std::vector<int>&\
    \ sources) {\n    int n = g.size();\n    BfsResult result;\n    result.dist.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \n    std::queue<int> que;\n    for (int s : sources) {\n        assert(0 <= s\
    \ && s < n);\n        if (result.dist[s] != -1) continue;\n        result.dist[s]\
    \ = 0;\n        que.push(s);\n    }\n\n    while (!que.empty()) {\n        int\
    \ v = que.front();\n        que.pop();\n        for (const auto& e : g[v]) {\n\
    \            if (!e.alive) continue;\n            if (result.dist[e.to] != -1)\
    \ continue;\n            result.dist[e.to] = result.dist[v] + 1;\n           \
    \ result.parent[e.to] = v;\n            result.parent_edge[e.to] = e.id;\n   \
    \         que.push(e.to);\n        }\n    }\n\n    return result;\n}\n\ntemplate\
    \ <class T>\nBfsResult bfs(const Graph<T>& g, int s) {\n    return bfs(g, std::vector<int>{s});\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/cow_game.hpp\"\
    \n\n\n\n#line 10 \"graph/cow_game.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstruct CowGameConstraint {\n    int from;\n    int\
    \ to;\n    T upper_bound;\n};\n\ntemplate <class T>\nstruct CowGameSolution {\n\
    \    bool feasible = false;\n    std::vector<T> value;\n\n    bool is_feasible()\
    \ const {\n        return feasible;\n    }\n};\n\ntemplate <class T>\nstruct CowGameUpperBounds\
    \ {\n    bool feasible;\n    std::vector<T> upper_bound;\n    T inf;\n\n    bool\
    \ is_feasible() const {\n        return feasible;\n    }\n\n    bool bounded(int\
    \ variable) const {\n        assert(0 <= variable && variable < int(upper_bound.size()));\n\
    \        return feasible && upper_bound[variable] != inf;\n    }\n};\n\ntemplate\
    \ <class T>\nstruct CowGameDifferenceBounds {\n    bool feasible;\n    std::optional<T>\
    \ lower_bound;\n    std::optional<T> upper_bound;\n\n    bool is_feasible() const\
    \ {\n        return feasible;\n    }\n\n    bool bounded_below() const {\n   \
    \     return feasible && lower_bound.has_value();\n    }\n\n    bool bounded_above()\
    \ const {\n        return feasible && upper_bound.has_value();\n    }\n};\n\n\
    template <class T>\nclass CowGame {\n    static_assert(std::is_arithmetic_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct RelaxationResult {\n        bool has_negative_cycle;\n\
    \        std::vector<T> dist;\n    };\n\n    int _n;\n    std::vector<CowGameConstraint<T>>\
    \ _constraints;\n    mutable bool _solution_cached = false;\n    mutable CowGameSolution<T>\
    \ _cached_solution;\n\n    void assert_variable(int variable) const {\n      \
    \  (void)variable;\n        assert(0 <= variable && variable < _n);\n    }\n\n\
    \    T negate(T value) const {\n        assert(value != std::numeric_limits<T>::lowest());\n\
    \        return -value;\n    }\n\n    RelaxationResult relax(std::vector<T> dist,\
    \ T inf, bool skip_unreachable) const {\n        for (int iteration = 0; iteration\
    \ < _n; iteration++) {\n            bool updated = false;\n            for (const\
    \ auto& constraint : _constraints) {\n                if (skip_unreachable &&\
    \ dist[constraint.from] == inf) continue;\n                T candidate = dist[constraint.from]\
    \ + constraint.upper_bound;\n                if (dist[constraint.to] <= candidate)\
    \ continue;\n                dist[constraint.to] = candidate;\n              \
    \  updated = true;\n                if (iteration == _n - 1) return RelaxationResult{true,\
    \ std::move(dist)};\n            }\n            if (!updated) break;\n       \
    \ }\n        return RelaxationResult{false, std::move(dist)};\n    }\n\n    RelaxationResult\
    \ check_feasibility() const {\n        return relax(std::vector<T>(_n, T()), T(),\
    \ false);\n    }\n\n    RelaxationResult shortest_paths(int source, T inf) const\
    \ {\n        std::vector<T> dist(_n, inf);\n        dist[source] = T();\n    \
    \    return relax(std::move(dist), inf, true);\n    }\n\n   public:\n    CowGame()\
    \ : CowGame(0) {}\n\n    explicit CowGame(int variable_count) : _n(variable_count)\
    \ {\n        assert(variable_count >= 0);\n    }\n\n    int size() const {\n \
    \       return _n;\n    }\n\n    int constraint_count() const {\n        return\
    \ int(_constraints.size());\n    }\n\n    const CowGameConstraint<T>& get_constraint(int\
    \ id) const {\n        assert(0 <= id && id < int(_constraints.size()));\n   \
    \     return _constraints[id];\n    }\n\n    const std::vector<CowGameConstraint<T>>&\
    \ constraints() const {\n        return _constraints;\n    }\n\n    int add_upper_bound(int\
    \ from, int to, T upper_bound) {\n        assert_variable(from);\n        assert_variable(to);\n\
    \        int id = int(_constraints.size());\n        _constraints.push_back(CowGameConstraint<T>{from,\
    \ to, upper_bound});\n        _solution_cached = false;\n        return id;\n\
    \    }\n\n    int add_constraint(int from, int to, T upper_bound) {\n        return\
    \ add_upper_bound(from, to, upper_bound);\n    }\n\n    int add_lower_bound(int\
    \ from, int to, T lower_bound) {\n        return add_upper_bound(to, from, negate(lower_bound));\n\
    \    }\n\n    void add_bounds(int from, int to, T lower_bound, T upper_bound)\
    \ {\n        assert(lower_bound <= upper_bound);\n        add_lower_bound(from,\
    \ to, lower_bound);\n        add_upper_bound(from, to, upper_bound);\n    }\n\n\
    \    void add_equality(int from, int to, T difference) {\n        add_bounds(from,\
    \ to, difference, difference);\n    }\n\n    CowGameSolution<T> solve() const\
    \ {\n        if (_solution_cached) return _cached_solution;\n\n        auto result\
    \ = check_feasibility();\n        _cached_solution.feasible = !result.has_negative_cycle;\n\
    \        _cached_solution.value.clear();\n        if (_cached_solution.feasible)\
    \ _cached_solution.value = std::move(result.dist);\n        _solution_cached =\
    \ true;\n        return _cached_solution;\n    }\n\n    bool is_feasible() const\
    \ {\n        if (!_solution_cached) (void)solve();\n        return _cached_solution.feasible;\n\
    \    }\n\n    CowGameUpperBounds<T> tightest_upper_bounds(int source) const {\n\
    \        assert_variable(source);\n        T inf = std::numeric_limits<T>::max()\
    \ / T(4);\n        CowGameUpperBounds<T> result;\n        result.feasible = is_feasible();\n\
    \        result.inf = inf;\n        result.upper_bound.assign(_n, inf);\n    \
    \    if (!result.feasible) return result;\n\n        result.upper_bound = shortest_paths(source,\
    \ inf).dist;\n        return result;\n    }\n\n    CowGameDifferenceBounds<T>\
    \ difference_bounds(int from, int to) const {\n        assert_variable(from);\n\
    \        assert_variable(to);\n        T inf = std::numeric_limits<T>::max() /\
    \ T(4);\n        CowGameDifferenceBounds<T> result;\n        result.feasible =\
    \ is_feasible();\n        if (!result.feasible) return result;\n\n        auto\
    \ forward = shortest_paths(from, inf);\n        if (forward.dist[to] != inf) result.upper_bound\
    \ = forward.dist[to];\n\n        auto backward = shortest_paths(to, inf);\n  \
    \      if (backward.dist[from] != inf) result.lower_bound = negate(backward.dist[from]);\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nusing DifferenceConstraints\
    \ = CowGame<T>;\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"\
    graph/dag_shortest_path.hpp\"\n\n\n\n#line 9 \"graph/dag_shortest_path.hpp\"\n\
    \n#line 1 \"graph/topological_sort.hpp\"\n\n\n\n#line 7 \"graph/topological_sort.hpp\"\
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
    \ graph\n}  // namespace m1une\n\n\n#line 12 \"graph/dag_shortest_path.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DagShortestPathResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> topological_order;\n    T inf;\n\n    bool\
    \ reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const\
    \ {\n        assert(reachable(t));\n        std::vector<int> result;\n       \
    \ for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nstd::optional<DagShortestPathResult<T>>\
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
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/k_shortest_walk.hpp\"\
    \n\n\n\n#line 10 \"graph/k_shortest_walk.hpp\"\n\n#line 12 \"graph/k_shortest_walk.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nnamespace internal {\n\ntemplate <class\
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
    }  // namespace m1une\n\n\n#line 1 \"graph/warshall_floyd.hpp\"\n\n\n\n#line 8\
    \ \"graph/warshall_floyd.hpp\"\n\n#line 10 \"graph/warshall_floyd.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T>\nstd::vector<std::vector<T>>\
    \ warshall_floyd(std::vector<std::vector<T>> dist,\n                         \
    \                  T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n\
    \ = int(dist.size());\n    for (int k = 0; k < n; k++) {\n        for (int i =\
    \ 0; i < n; i++) {\n            if (dist[i][k] == inf) continue;\n           \
    \ for (int j = 0; j < n; j++) {\n                if (dist[k][j] == inf) continue;\n\
    \                T nd = dist[i][k] + dist[k][j];\n                if (nd < dist[i][j])\
    \ dist[i][j] = nd;\n            }\n        }\n    }\n    return dist;\n}\n\ntemplate\
    \ <class T>\nstd::vector<std::vector<T>> warshall_floyd(const Graph<T>& g, T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    std::vector<std::vector<T>>\
    \ dist(n, std::vector<T>(n, inf));\n    for (int i = 0; i < n; i++) dist[i][i]\
    \ = T(0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            if (e.cost < dist[e.from][e.to])\
    \ dist[e.from][e.to] = e.cost;\n        }\n    }\n    return warshall_floyd(std::move(dist),\
    \ inf);\n}\n\ntemplate <class T>\nbool warshall_floyd_add_directed_edge(std::vector<std::vector<T>>&\
    \ dist, int from, int to, T cost,\n                                      T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n \
    \   assert(0 <= from && from < n);\n    assert(0 <= to && to < n);\n\n    std::vector<T>\
    \ to_from(n), from_to(n);\n    for (int i = 0; i < n; i++) {\n        to_from[i]\
    \ = dist[i][from];\n        from_to[i] = dist[to][i];\n    }\n\n    bool updated\
    \ = false;\n    for (int i = 0; i < n; i++) {\n        if (to_from[i] == inf)\
    \ continue;\n        for (int j = 0; j < n; j++) {\n            if (from_to[j]\
    \ == inf) continue;\n            T nd = to_from[i] + cost + from_to[j];\n    \
    \        if (nd < dist[i][j]) {\n                dist[i][j] = nd;\n          \
    \      updated = true;\n            }\n        }\n    }\n    return updated;\n\
    }\n\ntemplate <class T>\nbool warshall_floyd_add_undirected_edge(std::vector<std::vector<T>>&\
    \ dist, int u, int v, T cost,\n                                        T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n   \
    \ assert(0 <= u && u < n);\n    assert(0 <= v && v < n);\n\n    std::vector<T>\
    \ to_u(n), from_u(n), to_v(n), from_v(n);\n    for (int i = 0; i < n; i++) {\n\
    \        to_u[i] = dist[i][u];\n        from_u[i] = dist[u][i];\n        to_v[i]\
    \ = dist[i][v];\n        from_v[i] = dist[v][i];\n    }\n\n    bool updated =\
    \ false;\n    for (int i = 0; i < n; i++) {\n        for (int j = 0; j < n; j++)\
    \ {\n            if (to_u[i] != inf && from_v[j] != inf) {\n                T\
    \ nd = to_u[i] + cost + from_v[j];\n                if (nd < dist[i][j]) {\n \
    \                   dist[i][j] = nd;\n                    updated = true;\n  \
    \              }\n            }\n            if (to_v[i] != inf && from_u[j] !=\
    \ inf) {\n                T nd = to_v[i] + cost + from_u[j];\n               \
    \ if (nd < dist[i][j]) {\n                    dist[i][j] = nd;\n             \
    \       updated = true;\n                }\n            }\n        }\n    }\n\
    \    return updated;\n}\n\ntemplate <class T>\nbool has_negative_cycle(const std::vector<std::vector<T>>&\
    \ dist) {\n    int n = int(dist.size());\n    for (int i = 0; i < n; i++) {\n\
    \        if (dist[i][i] < T(0)) return true;\n    }\n    return false;\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/zero_one_bfs.hpp\"\
    \n\n\n\n#line 6 \"graph/zero_one_bfs.hpp\"\n#include <deque>\n#line 9 \"graph/zero_one_bfs.hpp\"\
    \n\n#line 11 \"graph/zero_one_bfs.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct ZeroOneBfsResult {\n    std::vector<int> dist;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    int inf;\n\n    bool reachable(int\
    \ v) const {\n        assert(0 <= v && v < int(dist.size()));\n        return\
    \ dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const {\n       \
    \ assert(reachable(t));\n        std::vector<int> result;\n        for (int v\
    \ = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nZeroOneBfsResult\
    \ zero_one_bfs(const Graph<T>& g, const std::vector<int>& sources,\n         \
    \                     int inf = std::numeric_limits<int>::max() / 2) {\n    int\
    \ n = g.size();\n    ZeroOneBfsResult result;\n    result.dist.assign(n, inf);\n\
    \    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n   \
    \ result.inf = inf;\n\n    std::deque<int> deq;\n    for (int s : sources) {\n\
    \        assert(0 <= s && s < n);\n        if (result.dist[s] == 0) continue;\n\
    \        result.dist[s] = 0;\n        deq.push_back(s);\n    }\n\n    while (!deq.empty())\
    \ {\n        int v = deq.front();\n        deq.pop_front();\n        for (const\
    \ auto& e : g[v]) {\n            if (!e.alive) continue;\n            int w;\n\
    \            if (e.cost == T(0)) {\n                w = 0;\n            } else\
    \ {\n                assert(e.cost == T(1));\n                w = 1;\n       \
    \     }\n            int nd = result.dist[v] + w;\n            if (result.dist[e.to]\
    \ <= nd) continue;\n            result.dist[e.to] = nd;\n            result.parent[e.to]\
    \ = v;\n            result.parent_edge[e.to] = e.id;\n            if (w == 0)\
    \ {\n                deq.push_front(e.to);\n            } else {\n           \
    \     deq.push_back(e.to);\n            }\n        }\n    }\n\n    return result;\n\
    }\n\ntemplate <class T>\nZeroOneBfsResult zero_one_bfs(const Graph<T>& g, int\
    \ s, int inf = std::numeric_limits<int>::max() / 2) {\n    return zero_one_bfs(g,\
    \ std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 12 \"graph/shortest_path.hpp\"\n\n\n#line 1 \"graph/two_edge_connected_components.hpp\"\
    \n\n\n\n#line 6 \"graph/two_edge_connected_components.hpp\"\n\n#line 8 \"graph/two_edge_connected_components.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct TwoEdgeConnectedBridge {\n\
    \    int from;\n    int to;\n    int edge_id;\n};\n\nstruct TwoEdgeConnectedComponentsResult\
    \ {\n    std::vector<std::vector<int>> components;\n    std::vector<int> component_of_vertex;\n\
    \    std::vector<int> bridge_ids;\n    std::vector<char> bridge;\n    std::vector<TwoEdgeConnectedBridge>\
    \ bridge_forest_edges;\n    std::vector<int> ord;\n    std::vector<int> low;\n\
    \n    int component_count() const {\n        return int(components.size());\n\
    \    }\n\n    bool same(int first, int second) const {\n        assert(0 <= first\
    \ && first < int(component_of_vertex.size()));\n        assert(0 <= second &&\
    \ second < int(component_of_vertex.size()));\n        return component_of_vertex[first]\
    \ == component_of_vertex[second];\n    }\n\n    bool is_bridge(int edge_id) const\
    \ {\n        assert(0 <= edge_id && edge_id < int(bridge.size()));\n        return\
    \ bridge[edge_id];\n    }\n};\n\n// Removes every active bridge and returns the\
    \ remaining connected components.\n// The first lowlink traversal and the component\
    \ traversal are both iterative.\ntemplate <class T>\nTwoEdgeConnectedComponentsResult\
    \ two_edge_connected_components(\n    const Graph<T>& graph\n) {\n    const int\
    \ n = graph.size();\n    const int edge_count = graph.edge_count();\n\n    TwoEdgeConnectedComponentsResult\
    \ result;\n    result.component_of_vertex.assign(n, -1);\n    result.bridge.assign(edge_count,\
    \ false);\n    result.ord.assign(n, -1);\n    result.low.assign(n, -1);\n\n  \
    \  std::vector<int> edge_from(edge_count, -1);\n    std::vector<int> edge_to(edge_count,\
    \ -1);\n    std::vector<int> incidence_count(edge_count, 0);\n    for (int vertex\
    \ = 0; vertex < n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex])\
    \ {\n            if (!edge.alive) continue;\n            assert(0 <= edge.id &&\
    \ edge.id < edge_count);\n            if (incidence_count[edge.id] == 0) {\n \
    \               edge_from[edge.id] = edge.from;\n                edge_to[edge.id]\
    \ = edge.to;\n            }\n            incidence_count[edge.id]++;\n       \
    \ }\n    }\n#ifndef NDEBUG\n    for (int edge_id = 0; edge_id < edge_count; edge_id++)\
    \ {\n        if (incidence_count[edge_id] != 0) assert(incidence_count[edge_id]\
    \ == 2);\n    }\n#endif\n\n    std::vector<int> parent(n, -1);\n    std::vector<int>\
    \ parent_edge(n, -1);\n    std::vector<int> next_edge(n, 0);\n    std::vector<int>\
    \ stack;\n    int timer = 0;\n\n    for (int root = 0; root < n; root++) {\n \
    \       if (result.ord[root] != -1) continue;\n        result.ord[root] = result.low[root]\
    \ = timer++;\n        stack.push_back(root);\n        while (!stack.empty()) {\n\
    \            const int vertex = stack.back();\n            if (next_edge[vertex]\
    \ < int(graph[vertex].size())) {\n                const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n\
    \                if (!edge.alive || edge.id == parent_edge[vertex]) continue;\n\
    \                const int to = edge.to;\n                if (result.ord[to] ==\
    \ -1) {\n                    parent[to] = vertex;\n                    parent_edge[to]\
    \ = edge.id;\n                    result.ord[to] = result.low[to] = timer++;\n\
    \                    stack.push_back(to);\n                } else if (result.ord[to]\
    \ < result.low[vertex]) {\n                    result.low[vertex] = result.ord[to];\n\
    \                }\n                continue;\n            }\n\n            stack.pop_back();\n\
    \            const int parent_vertex = parent[vertex];\n            if (parent_vertex\
    \ == -1) continue;\n            if (result.low[vertex] < result.low[parent_vertex])\
    \ {\n                result.low[parent_vertex] = result.low[vertex];\n       \
    \     }\n            if (result.ord[parent_vertex] < result.low[vertex]) {\n \
    \               result.bridge[parent_edge[vertex]] = true;\n            }\n  \
    \      }\n    }\n\n    for (int root = 0; root < n; root++) {\n        if (result.component_of_vertex[root]\
    \ != -1) continue;\n        const int component = result.component_count();\n\
    \        result.components.emplace_back();\n        result.component_of_vertex[root]\
    \ = component;\n        stack.push_back(root);\n        while (!stack.empty())\
    \ {\n            const int vertex = stack.back();\n            stack.pop_back();\n\
    \            result.components.back().push_back(vertex);\n            for (const\
    \ Edge<T>& edge : graph[vertex]) {\n                if (!edge.alive || result.bridge[edge.id])\
    \ continue;\n                if (result.component_of_vertex[edge.to] != -1) continue;\n\
    \                result.component_of_vertex[edge.to] = component;\n          \
    \      stack.push_back(edge.to);\n            }\n        }\n    }\n\n    for (int\
    \ edge_id = 0; edge_id < edge_count; edge_id++) {\n        if (!result.bridge[edge_id])\
    \ continue;\n        result.bridge_ids.push_back(edge_id);\n        const int\
    \ first_component = result.component_of_vertex[edge_from[edge_id]];\n        const\
    \ int second_component = result.component_of_vertex[edge_to[edge_id]];\n     \
    \   assert(first_component != second_component);\n        result.bridge_forest_edges.push_back(\n\
    \            TwoEdgeConnectedBridge{first_component, second_component, edge_id});\n\
    \    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 24 \"graph/undirected.hpp\"\n\n\n"
  code: '#ifndef M1UNE_GRAPH_UNDIRECTED_HPP

    #define M1UNE_GRAPH_UNDIRECTED_HPP 1


    #include "bipartite.hpp"

    #include "biconnected_components.hpp"

    #include "block_cut_tree.hpp"

    #include "chromatic_number.hpp"

    #include "connected_components.hpp"

    #include "cycle_detection.hpp"

    #include "enumerate_triangles.hpp"

    #include "eulerian_trail.hpp"

    #include "general_matching.hpp"

    #include "general_weighted_matching.hpp"

    #include "graph.hpp"

    #include "grid.hpp"

    #include "kruskal.hpp"

    #include "lowlink.hpp"

    #include "maximum_clique.hpp"

    #include "minimum_steiner_tree.hpp"

    #include "namori.hpp"

    #include "replacement_paths.hpp"

    #include "shortest_path.hpp"

    #include "two_edge_connected_components.hpp"


    #endif  // M1UNE_GRAPH_UNDIRECTED_HPP

    '
  dependsOn:
  - graph/bipartite.hpp
  - graph/graph.hpp
  - graph/biconnected_components.hpp
  - graph/block_cut_tree.hpp
  - graph/chromatic_number.hpp
  - graph/connected_components.hpp
  - ds/dsu/dsu.hpp
  - graph/cycle_detection.hpp
  - graph/enumerate_triangles.hpp
  - graph/eulerian_trail.hpp
  - graph/general_matching.hpp
  - graph/general_weighted_matching.hpp
  - graph/grid.hpp
  - graph/kruskal.hpp
  - graph/lowlink.hpp
  - graph/maximum_clique.hpp
  - graph/minimum_steiner_tree.hpp
  - graph/namori.hpp
  - graph/replacement_paths.hpp
  - graph/dijkstra.hpp
  - graph/shortest_path.hpp
  - graph/bellman_ford.hpp
  - graph/bfs.hpp
  - graph/cow_game.hpp
  - graph/dag_shortest_path.hpp
  - graph/topological_sort.hpp
  - graph/k_shortest_walk.hpp
  - graph/warshall_floyd.hpp
  - graph/zero_one_bfs.hpp
  - graph/two_edge_connected_components.hpp
  isVerificationFile: false
  path: graph/undirected.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-07-14 02:19:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/undirected.hpp
layout: document
title: Undirected Graph Algorithms
---

## Overview

`graph/undirected.hpp` includes algorithms whose main interpretation is
undirected, plus the shortest-path bundle. In that bundle, use the
direction-respecting algorithms on graphs built with `add_edge`; the DAG
shortest-path helper is directed-only.

Use this header when edges represent two-way movement or an endpoint constraint
where direction should not matter.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/shortest_path.hpp` | Mixed shortest-path bundle | Use BFS, 0-1 BFS, Dijkstra, Bellman-Ford, and Warshall-Floyd on undirected graphs built with `add_edge`; DAG shortest path is directed-only. |
| `graph/lowlink.hpp` | Undirected only | Articulation points and bridges. |
| `graph/biconnected_components.hpp` | Undirected only | Vertex-biconnected blocks, articulation points, and block incidence. |
| `graph/block_cut_tree.hpp` | Undirected only | Block-cut forest and original-vertex-to-node mappings. |
| `graph/two_edge_connected_components.hpp` | Undirected only | Two-edge-connected components, bridges, and the contracted bridge forest. |
| `graph/kruskal.hpp` | Undirected only | Minimum spanning forest. |
| `graph/bipartite.hpp` | Direction ignored / explicit bipartite sides | Two-colorability, maximum matching, minimum vertex cover, maximum independent set, and minimum edge cover. |
| `graph/general_matching.hpp` | Undirected only | Maximum-cardinality matching and minimum edge cover in general undirected graphs. |
| `graph/general_weighted_matching.hpp` | Undirected only | Maximum-total-weight matching in general undirected graphs. |
| `graph/maximum_clique.hpp` | Direction ignored | Exact maximum clique, maximum independent set, and minimum vertex cover with bitset branch-and-bound. |
| `graph/chromatic_number.hpp` | Direction ignored | Exact chromatic number for graphs with at most 20 vertices. |
| `graph/minimum_steiner_tree.hpp` | Undirected only | Exact edge- and vertex-weighted minimum Steiner-tree costs and reconstruction for a small terminal set. |
| `graph/replacement_paths.hpp` | Undirected positive-weight graphs | Edge- and vertex-failure replacement distances along one fixed shortest path. |
| `graph/namori.hpp` | Undirected Namori graph | Ordered cycles and the trees attached to them. |
| `graph/connected_components.hpp` | Direction ignored | Weak/ordinary connected components. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Use `find_undirected_cycle(g)` for undirected graphs. |
| `graph/enumerate_triangles.hpp` | Direction ignored | Enumerates every triangle through a callback. |
| `graph/eulerian_trail.hpp` | Directed and undirected variants | Use `undirected_eulerian_trail(g)` for undirected graphs. |
| `graph/grid.hpp` | Undirected graph builder | Builds 4/8-neighbor grid graphs. |

## Complexity

This header is an include bundle and provides no runtime operation by itself.
See the included algorithm pages for public interfaces and complexities.
