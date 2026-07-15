---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bipartite.hpp
    title: Bipartite Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bipartite_edge_coloring
    links:
    - https://judge.yosupo.jp/problem/bipartite_edge_coloring
  bundledCode: "#line 1 \"verify/graph/bipartite_edge_coloring.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/bipartite_edge_coloring\"\n\n#line\
    \ 1 \"graph/bipartite.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstddef>\n#include <cstdint>\n#include <limits>\n#include <optional>\n\
    #include <queue>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    template <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
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
    \ 4 \"verify/graph/bipartite_edge_coloring.test.cpp\"\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <array>\n#include <charconv>\n#line 7 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\n\
    #include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
    #line 15 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\
    namespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
    \ T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\n\
    struct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n\n    bool prepare_number() {\n       \
    \ if (_length - _position >= 64) return true;\n        const int remaining = _length\
    \ - _position;\n        if (remaining > 0) std::memmove(_buffer, _buffer + _position,\
    \ remaining);\n        const int added = int(std::fread(_buffer + remaining, 1,\
    \ buffer_size - remaining, _stream));\n        _position = 0;\n        _length\
    \ = remaining + added;\n        if (_length < buffer_size) _buffer[_length] =\
    \ '\\0';\n        return _length != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE*\
    \ stream = stdin)\n        : _stream(stream), _position(0), _length(0) {}\n\n\
    \    FastInput(const FastInput&) = delete;\n    FastInput& operator=(const FastInput&)\
    \ = delete;\n\n    int read_char_raw() {\n        if (_position == _length) {\n\
    \            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n  \
    \          _position = 0;\n            if (_length == 0) return EOF;\n       \
    \ }\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces() {\n\
    \        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c = read_char_raw();\n\
    \        if (c == EOF) return false;\n        --_position;\n        return true;\n\
    \    }\n\n    bool read(char& value) {\n        if (!skip_spaces()) return false;\n\
    \        value = char(read_char_raw());\n        return true;\n    }\n\n    bool\
    \ read(std::string& value) {\n        if (!skip_spaces()) return false;\n    \
    \    value.clear();\n        int c = read_char_raw();\n        while (c != EOF\
    \ && c > ' ') {\n            value.push_back(char(c));\n            c = read_char_raw();\n\
    \        }\n        return true;\n    }\n\n    bool read(bool& value) {\n    \
    \    int x;\n        if (!read(x)) return false;\n        value = x != 0;\n  \
    \      return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\n\
    \          _position(0),\n          _precision(6),\n          _float_format(std::chars_format::general)\
    \ {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput& operator=(const\
    \ FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n    }\n\n \
    \   void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>\n\
    \    >\n    write(const Range& range) {\n        using StoredValue = internal::range_stored_value_t<const\
    \ Range>;\n        constexpr bool nested = internal::is_range_v<StoredValue>\n\
    \                                && !internal::is_string_like_v<StoredValue>;\n\
    \n        bool first = true;\n        for (const auto& value : range) {\n    \
    \        if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void set_precision(int\
    \ precision) {\n        _precision = precision;\n    }\n\n    void set_fixed(int\
    \ precision = 6) {\n        _float_format = std::chars_format::fixed;\n      \
    \  _precision = precision;\n    }\n\n    void set_general(int precision = 6) {\n\
    \        _float_format = std::chars_format::general;\n        _precision = precision;\n\
    \    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n\n    template\
    \ <class T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n\
    \        return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 11 \"verify/graph/bipartite_edge_coloring.test.cpp\"\n\nnamespace\
    \ {\n\nvoid check(\n    int left_size,\n    int right_size,\n    const std::vector<std::pair<int,\
    \ int>>& edges\n) {\n    std::vector<int> left_degree(left_size, 0);\n    std::vector<int>\
    \ right_degree(right_size, 0);\n    int maximum_degree = 0;\n    for (auto [left,\
    \ right] : edges) {\n        left_degree[left]++;\n        right_degree[right]++;\n\
    \        maximum_degree = std::max(maximum_degree, left_degree[left]);\n     \
    \   maximum_degree = std::max(maximum_degree, right_degree[right]);\n    }\n\n\
    \    auto result = m1une::graph::bipartite_edge_coloring(left_size, right_size,\
    \ edges);\n    assert(result.color_count == maximum_degree);\n    assert(result.color.size()\
    \ == edges.size());\n    std::vector<std::vector<char>> left_used(\n        left_size,\n\
    \        std::vector<char>(maximum_degree, false)\n    );\n    std::vector<std::vector<char>>\
    \ right_used(\n        right_size,\n        std::vector<char>(maximum_degree,\
    \ false)\n    );\n    for (int edge = 0; edge < int(edges.size()); edge++) {\n\
    \        auto [left, right] = edges[edge];\n        int color = result.color[edge];\n\
    \        assert(0 <= color && color < maximum_degree);\n        assert(!left_used[left][color]);\n\
    \        assert(!right_used[right][color]);\n        left_used[left][color] =\
    \ true;\n        right_used[right][color] = true;\n    }\n}\n\nvoid test_fixed()\
    \ {\n    check(0, 0, std::vector<std::pair<int, int>>());\n\n    std::vector<std::pair<int,\
    \ int>> star;\n    for (int right = 0; right < 20; right++) star.emplace_back(0,\
    \ right);\n    check(1, 20, star);\n\n    std::vector<std::pair<int, int>> parallel;\n\
    \    for (int edge = 0; edge < 15; edge++) parallel.emplace_back(0, 0);\n    check(1,\
    \ 1, parallel);\n\n    std::vector<std::pair<int, int>> complete;\n    for (int\
    \ left = 0; left < 7; left++) {\n        for (int right = 0; right < 7; right++)\
    \ complete.emplace_back(left, right);\n    }\n    check(7, 7, complete);\n}\n\n\
    void test_randomized() {\n    std::uint64_t state = 393393;\n    auto random =\
    \ [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n \
    \       return state;\n    };\n\n    for (int trial = 0; trial < 3000; trial++)\
    \ {\n        int left_size = 1 + int(random() % 10);\n        int right_size =\
    \ 1 + int(random() % 10);\n        int edge_count = int(random() % 50);\n    \
    \    std::vector<std::pair<int, int>> edges;\n        edges.reserve(edge_count);\n\
    \        for (int edge = 0; edge < edge_count; edge++) {\n            edges.emplace_back(\n\
    \                int(random() % left_size),\n                int(random() % right_size)\n\
    \            );\n        }\n        check(left_size, right_size, edges);\n   \
    \ }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n    test_randomized();\n\
    \    int left_size, right_size, edge_count;\n    fast_input >> left_size >> right_size\
    \ >> edge_count;\n    std::vector<std::pair<int, int>> edges(edge_count);\n  \
    \  for (auto& [left, right] : edges) fast_input >> left >> right;\n\n    auto\
    \ result = m1une::graph::bipartite_edge_coloring(left_size, right_size, edges);\n\
    \    fast_output << result.color_count << '\\n';\n    for (int color : result.color)\
    \ fast_output << color << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bipartite_edge_coloring\"\
    \n\n#include \"../../graph/bipartite.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <utility>\n\
    #include <vector>\n\nnamespace {\n\nvoid check(\n    int left_size,\n    int right_size,\n\
    \    const std::vector<std::pair<int, int>>& edges\n) {\n    std::vector<int>\
    \ left_degree(left_size, 0);\n    std::vector<int> right_degree(right_size, 0);\n\
    \    int maximum_degree = 0;\n    for (auto [left, right] : edges) {\n       \
    \ left_degree[left]++;\n        right_degree[right]++;\n        maximum_degree\
    \ = std::max(maximum_degree, left_degree[left]);\n        maximum_degree = std::max(maximum_degree,\
    \ right_degree[right]);\n    }\n\n    auto result = m1une::graph::bipartite_edge_coloring(left_size,\
    \ right_size, edges);\n    assert(result.color_count == maximum_degree);\n   \
    \ assert(result.color.size() == edges.size());\n    std::vector<std::vector<char>>\
    \ left_used(\n        left_size,\n        std::vector<char>(maximum_degree, false)\n\
    \    );\n    std::vector<std::vector<char>> right_used(\n        right_size,\n\
    \        std::vector<char>(maximum_degree, false)\n    );\n    for (int edge =\
    \ 0; edge < int(edges.size()); edge++) {\n        auto [left, right] = edges[edge];\n\
    \        int color = result.color[edge];\n        assert(0 <= color && color <\
    \ maximum_degree);\n        assert(!left_used[left][color]);\n        assert(!right_used[right][color]);\n\
    \        left_used[left][color] = true;\n        right_used[right][color] = true;\n\
    \    }\n}\n\nvoid test_fixed() {\n    check(0, 0, std::vector<std::pair<int, int>>());\n\
    \n    std::vector<std::pair<int, int>> star;\n    for (int right = 0; right <\
    \ 20; right++) star.emplace_back(0, right);\n    check(1, 20, star);\n\n    std::vector<std::pair<int,\
    \ int>> parallel;\n    for (int edge = 0; edge < 15; edge++) parallel.emplace_back(0,\
    \ 0);\n    check(1, 1, parallel);\n\n    std::vector<std::pair<int, int>> complete;\n\
    \    for (int left = 0; left < 7; left++) {\n        for (int right = 0; right\
    \ < 7; right++) complete.emplace_back(left, right);\n    }\n    check(7, 7, complete);\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 393393;\n    auto random\
    \ = [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    for (int trial = 0; trial < 3000; trial++)\
    \ {\n        int left_size = 1 + int(random() % 10);\n        int right_size =\
    \ 1 + int(random() % 10);\n        int edge_count = int(random() % 50);\n    \
    \    std::vector<std::pair<int, int>> edges;\n        edges.reserve(edge_count);\n\
    \        for (int edge = 0; edge < edge_count; edge++) {\n            edges.emplace_back(\n\
    \                int(random() % left_size),\n                int(random() % right_size)\n\
    \            );\n        }\n        check(left_size, right_size, edges);\n   \
    \ }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n    test_randomized();\n\
    \    int left_size, right_size, edge_count;\n    fast_input >> left_size >> right_size\
    \ >> edge_count;\n    std::vector<std::pair<int, int>> edges(edge_count);\n  \
    \  for (auto& [left, right] : edges) fast_input >> left >> right;\n\n    auto\
    \ result = m1une::graph::bipartite_edge_coloring(left_size, right_size, edges);\n\
    \    fast_output << result.color_count << '\\n';\n    for (int color : result.color)\
    \ fast_output << color << '\\n';\n}\n"
  dependsOn:
  - graph/bipartite.hpp
  - graph/graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/bipartite_edge_coloring.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/bipartite_edge_coloring.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/bipartite_edge_coloring.test.cpp
- /verify/verify/graph/bipartite_edge_coloring.test.cpp.html
title: verify/graph/bipartite_edge_coloring.test.cpp
---
