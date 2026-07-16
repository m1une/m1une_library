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
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/bipartite_edge_coloring.test.cpp
    title: verify/graph/bipartite_edge_coloring.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/bipartite_matching.test.cpp
    title: verify/graph/bipartite_matching.test.cpp
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
  bundledCode: "#line 1 \"graph/bipartite.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstddef>\n#include <cstdint>\n#include <limits>\n#include\
    \ <optional>\n#include <queue>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type\
    \ = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\
    \n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int\
    \ from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ = true)\n        :\
    \ from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\n    int other(int\
    \ v) const {\n        assert(v == from || v == to);\n        return from ^ to\
    \ ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph {\n    using edge_type\
    \ = Edge<T>;\n    using cost_type = T;\n\n   private:\n    int _n;\n    int _edge_count;\n\
    \    std::vector<std::vector<edge_type>> _g;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _edge_positions;\n\n   public:\n    Graph() : _n(0), _edge_count(0) {}\n\
    \    explicit Graph(int n) : _n(n), _edge_count(0), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int edge_count() const\
    \ {\n        return _edge_count;\n    }\n\n    int add_vertex() {\n        _g.emplace_back();\n\
    \        return _n++;\n    }\n\n    int add_directed_edge(int from, int to, T\
    \ cost = T(1)) {\n        assert(0 <= from && from < _n);\n        assert(0 <=\
    \ to && to < _n);\n        int id = _edge_count++;\n        int idx = int(_g[from].size());\n\
    \        _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
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
    \    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_BIPARTITE_HPP\n#define M1UNE_GRAPH_BIPARTITE_HPP 1\n\n\
    #include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include <cstdint>\n\
    #include <limits>\n#include <optional>\n#include <queue>\n#include <utility>\n\
    #include <vector>\n\n#include \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct BipartiteResult {\n    bool is_bipartite;\n    std::vector<int>\
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
    \    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_GRAPH_BIPARTITE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/bipartite.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-14 01:19:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/bipartite_edge_coloring.test.cpp
  - verify/graph/bipartite_matching.test.cpp
  - verify/graph/range_edge_graph.test.cpp
documentation_of: graph/bipartite.hpp
layout: document
title: Bipartite Graph
---

## Overview

This header contains tools for bipartite graphs.

A graph is bipartite if its vertices can be colored with two colors so that
every edge connects vertices of different colors. Equivalently, the graph has
no odd-length cycle.

Use `bipartite(g)` or `is_bipartite(g)` when you have a `Graph<T>` and want to
check whether such a coloring exists.

Use `BipartiteMatching` when the two sides are already known and you want
matching-related algorithms:

* maximum bipartite matching;
* minimum vertex cover;
* maximum independent set;
* minimum edge cover.

Use `bipartite_edge_coloring(left_size, right_size, edges)` when the two sides
are known and you want an optimal proper edge coloring. Parallel edges are
supported.

Use `make_bipartite_matching(g)` when you have a `Graph<T>` and want to build
that matching graph from its two-coloring.

## Graph Orientation

For `bipartite(g)`, direction is ignored. Each edge is treated as an
undirected constraint between its endpoints.

For `BipartiteMatching`, the graph is represented by two index sets:

```cpp
left vertices:  0, 1, ..., left_size - 1
right vertices: 0, 1, ..., right_size - 1
```

Each edge connects one left vertex to one right vertex.

## How to Use It

Call `bipartite(g)` when you need both the yes/no answer and the colors. Call
`is_bipartite(g)` when you only need the boolean.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `is_bipartite` | `bool` | Whether a valid two-coloring exists. |
| `color` | `std::vector<int>` | `color[v]` is `0` or `1` for the assigned color, or `-1` before assignment. |
| `left_vertices` | `std::vector<int>` | Original graph vertices whose color is `0`; valid when `is_bipartite == true`. |
| `right_vertices` | `std::vector<int>` | Original graph vertices whose color is `1`; valid when `is_bipartite == true`. |
| `left_id` | `std::vector<int>` | `left_id[v]` is the index of original vertex `v` inside `left_vertices`, or `-1`. |
| `right_id` | `std::vector<int>` | `right_id[v]` is the index of original vertex `v` inside `right_vertices`, or `-1`. |

For a disconnected graph, every component is colored independently. The chosen
colors are not unique; flipping all colors in a component gives another valid
answer.

If you want to run `BipartiteMatching` on a `Graph<T>`, first call
`bipartite(g)`, then use `left_id` and `right_id` to convert original vertex
ids into side-local ids. Alternatively, call `make_bipartite_matching(g)` to
build the separated matching graph and keep mappings back to the original
vertices and edge ids.

## Bipartite Matching

`BipartiteMatching` stores a bipartite graph whose sides are already separated.
It uses Hopcroft-Karp to compute a maximum matching.

After maximum matching is known, Konig's theorem gives a minimum vertex cover:
in bipartite graphs, the size of a maximum matching equals the size of a
minimum vertex cover. The implementation finds alternating paths from
unmatched left vertices. If `Z` is the set of vertices reached by those
alternating paths, the minimum vertex cover is:

```cpp
(left vertices not in Z) + (right vertices in Z)
```

The maximum independent set is the complement of that minimum vertex cover.

The minimum edge cover starts from a maximum matching, then adds one incident
edge for every still-uncovered vertex. It exists only when every vertex has at
least one incident edge; otherwise the method returns `std::nullopt`.

## Matching Fields

`BipartiteMatching::Edge` contains these fields:

| Field | Type | Meaning |
| --- | --- | --- |
| `left` | `int` | Left-side endpoint. |
| `right` | `int` | Right-side endpoint. |
| `id` | `int` | Edge id returned by `add_edge`. |
| `alive` | `bool` | Whether this edge is currently usable. |

`BipartiteMatching::Pair` contains these fields:

| Field | Type | Meaning |
| --- | --- | --- |
| `left` | `int` | Matched left-side vertex. |
| `right` | `int` | Matched right-side vertex. |
| `edge_id` | `int` | Edge id used by this matched pair. |

`BipartiteVertexSet` contains these fields:

| Field / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `left` | `std::vector<int>` | Selected left-side vertices. |
| `right` | `std::vector<int>` | Selected right-side vertices. |
| `size` | `int size() const` | Returns `left.size() + right.size()`. |

`BipartiteMatchingGraph` contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `parts` | `BipartiteResult` | Two-coloring and side-local id conversion for the original graph. |
| `matching` | `BipartiteMatching` | Matching graph whose left/right ids come from `parts`. |
| `original_edge_id` | `std::vector<int>` | `original_edge_id[e]` is the original `Graph<T>` edge id for matching edge `e`. |
| `left_vertex` | `int left_vertex(int left) const` | Converts a left-side id back to the original graph vertex id. |
| `right_vertex` | `int right_vertex(int right) const` | Converts a right-side id back to the original graph vertex id. |
| `original_edge` | `int original_edge(int edge_id) const` | Converts a matching edge id back to the original graph edge id. |

## Functions

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `bipartite` | `template <class T> BipartiteResult bipartite(const Graph<T>& g)` | Returns a bipartite flag and colors. | $O(N + M)$ |
| `is_bipartite` | `template <class T> bool is_bipartite(const Graph<T>& g)` | Returns only the bipartite flag. | $O(N + M)$ |
| `make_bipartite_matching` | `template <class T> std::optional<BipartiteMatchingGraph> make_bipartite_matching(const Graph<T>& g)` | Builds a `BipartiteMatching` from a bipartite `Graph<T>`, or returns `std::nullopt`. | $O(N + M)$ |
| `bipartite_edge_coloring` | `BipartiteEdgeColoringResult bipartite_edge_coloring(int left_size, int right_size, const std::vector<std::pair<int, int>>& edges)` | Returns an optimal coloring of an explicitly separated bipartite multigraph. | $O(L+R+M\sqrt{M/\Delta+1}\log(\Delta+1))$ |

## Matching Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `BipartiteMatching()` | Creates an empty bipartite graph. | $O(1)$ |
| Constructor | `BipartiteMatching(int left_size, int right_size)` | Creates a bipartite graph with explicit side sizes. | $O(L + R)$ |
| `left_size` | `int left_size() const` | Returns the number of left-side vertices. | $O(1)$ |
| `right_size` | `int right_size() const` | Returns the number of right-side vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of registered edges. | $O(1)$ |
| `add_edge` | `int add_edge(int left, int right)` | Adds an edge and returns its edge id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int i) const` | Returns edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges(bool include_inactive = false) const` | Returns active edges, or all edges if `include_inactive` is true. | $O(M)$ |
| `set_edge_alive` | `void set_edge_alive(int id, bool alive)` | Sets whether edge `id` is usable. | $O(1)$ |
| `erase_edge` | `void erase_edge(int id)` | Marks edge `id` unusable. | $O(1)$ |
| `revive_edge` | `void revive_edge(int id)` | Marks edge `id` usable again. | $O(1)$ |
| `is_edge_alive` | `bool is_edge_alive(int id) const` | Returns whether edge `id` is usable. | $O(1)$ |
| `max_matching` | `int max_matching()` | Computes and stores a maximum matching. | $O(M \sqrt{L + R})$ |
| `matching_size` | `int matching_size()` | Returns the current maximum matching size, computing it if needed. | $O(M \sqrt{L + R})$ if not computed |
| `left_match` | `std::vector<int> left_match()` | Returns `right` matched to each left vertex, or `-1`. | $O(M \sqrt{L + R})$ if not computed |
| `right_match` | `std::vector<int> right_match()` | Returns `left` matched to each right vertex, or `-1`. | $O(M \sqrt{L + R})$ if not computed |
| `matching` | `std::vector<Pair> matching()` | Returns matched pairs and edge ids. | $O(M \sqrt{L + R})$ if not computed |
| `minimum_vertex_cover` | `BipartiteVertexSet minimum_vertex_cover()` | Returns a minimum vertex cover. | $O(M \sqrt{L + R})$ if not computed |
| `maximum_independent_set` | `BipartiteVertexSet maximum_independent_set()` | Returns a maximum independent set. | $O(M \sqrt{L + R})$ if not computed |
| `minimum_edge_cover` | `std::optional<std::vector<int>> minimum_edge_cover()` | Returns edge ids of a minimum edge cover, or `std::nullopt` if an isolated vertex exists. | $O(M \sqrt{L + R})$ if not computed |

## Bipartite Edge Coloring

`bipartite_edge_coloring` assigns colors to the edges of a bipartite multigraph
so incident edges always have different colors. It uses exactly $\Delta$
colors, where $\Delta$ is the maximum vertex degree, and is therefore optimal
by Konig's line-coloring theorem.

The result type is:

```cpp
struct BipartiteEdgeColoringResult {
    int color_count;
    std::vector<int> color;
};
```

For every input edge `i`, `color[i]` lies in `[0, color_count)`. Input and
output edge order are identical. With no edges, `color_count` is zero and
`color` is empty.

The algorithm groups vertices into $O(M/\Delta)$ supervertices and completes
the graph to a balanced $\Delta$-regular bipartite multigraph. Even-degree
regular graphs are halved along alternating Euler circuits. At odd degrees,
Hopcroft-Karp extracts a perfect matching as one color class before recursion.
Dummy-edge colors are discarded. Memory usage is $O(L+R+M)$.

## Example

```cpp
#include "graph/bipartite.hpp"
#include "graph/graph.hpp"
#include <iostream>
#include <utility>
#include <vector>

int main() {
    m1une::graph::Graph<> g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 0);

    auto res = m1une::graph::bipartite(g);
    std::cout << res.is_bipartite << "\n";  // 1
    std::cout << res.color[0] << " " << res.color[1] << "\n";

    auto built = m1une::graph::make_bipartite_matching(g);
    std::cout << built->matching.max_matching() << "\n";  // 2

    m1une::graph::BipartiteMatching bm(2, 2);
    bm.add_edge(0, 0);
    bm.add_edge(0, 1);
    bm.add_edge(1, 1);

    std::cout << bm.max_matching() << "\n";  // 2
    auto cover = bm.minimum_vertex_cover();
    std::cout << cover.size() << "\n";       // 2

    std::vector<std::pair<int, int>> edges;
    edges.emplace_back(0, 0);
    edges.emplace_back(0, 1);
    edges.emplace_back(1, 0);
    auto coloring = m1une::graph::bipartite_edge_coloring(2, 2, edges);
    std::cout << coloring.color_count << "\n";  // 2
}
```
