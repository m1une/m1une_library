---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: Dijkstra
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
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/replacement_paths.test.cpp
    title: verify/graph/replacement_paths.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/replacement_paths.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <limits>\n#include <queue>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"graph/dijkstra.hpp\"\n\n\n\n\
    #line 11 \"graph/dijkstra.hpp\"\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7\
    \ \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
    \ T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int\
    \ to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1),\
    \ cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1),\
    \ int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
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
    \ m1une\n\n\n#line 13 \"graph/dijkstra.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstruct DijkstraResult {\n    std::vector<T> dist;\n\
    \    std::vector<int> parent;\n    std::vector<int> parent_edge;\n    T inf;\n\
    \n    bool reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const\
    \ {\n        assert(reachable(t));\n        std::vector<int> result;\n       \
    \ for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, const std::vector<int>& sources,\n             \
    \              T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n\
    \    DijkstraResult<T> result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n    result.inf = inf;\n\n    using\
    \ P = std::pair<T, int>;\n    std::priority_queue<P, std::vector<P>, std::greater<P>>\
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
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_REPLACEMENT_PATHS_HPP\n#define M1UNE_GRAPH_REPLACEMENT_PATHS_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <limits>\n#include <queue>\n#include <utility>\n#include <vector>\n\n#include\
    \ \"dijkstra.hpp\"\n#include \"graph.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct GraphPath {\n    std::vector<int> vertices;\n    std::vector<int>\
    \ edges;\n};\n\ntemplate <class T>\nstruct EdgeReplacementPathsResult {\n    GraphPath\
    \ path;\n    std::vector<T> replacement_dist;\n    T inf;\n\n    bool reachable(int\
    \ path_edge_index) const {\n        assert(0 <= path_edge_index && path_edge_index\
    \ < int(replacement_dist.size()));\n        return replacement_dist[path_edge_index]\
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
    \ namespace m1une\n\n#endif  // M1UNE_GRAPH_REPLACEMENT_PATHS_HPP\n"
  dependsOn:
  - graph/dijkstra.hpp
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/replacement_paths.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-13 05:03:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/replacement_paths.test.cpp
documentation_of: graph/replacement_paths.hpp
layout: document
title: Replacement Paths
---

## Overview

Replacement paths answer every single-failure shortest-path query along one
fixed shortest path $P=(p_0=s,p_1,\ldots,p_k=t)$. One call computes either the
shortest $s$-$t$ distance after deleting each logical path edge
$(p_i,p_{i+1})$, one edge at a time, or the shortest distance after deleting
each path vertex $p_i$, one vertex at a time.

The graph must be undirected and built with `Graph<T>::add_edge`. Every active
edge must have strictly positive cost. Inactive edges are ignored. The input
graph and its `alive` flags are never changed.

The automatic overloads select one shortest path. The `GraphPath` overloads
preserve the caller's exact shortest path, including its logical edge ids. Edge
ids are necessary because parallel edges may join the same pair of vertices.

## Path and Results

`GraphPath` has the following members:

| Member | Type | Meaning |
| --- | --- | --- |
| `vertices` | `std::vector<int>` | The ordered vertices $p_0,\ldots,p_k$. |
| `edges` | `std::vector<int>` | `edges[i]` is the active logical edge joining `vertices[i]` and `vertices[i + 1]`. |

It satisfies `vertices.size() == edges.size() + 1`. A supplied path must be
nonempty and simple, and its stored total cost must equal the shortest distance
between its endpoints.

`EdgeReplacementPathsResult<T>` contains:

| Member / method | Type / Signature | Meaning |
| --- | --- | --- |
| `path` | `GraphPath` | The selected or supplied fixed path. |
| `replacement_dist` | `std::vector<T>` | Entry `i` is the shortest distance after deleting logical edge `path.edges[i]`. Its size is `path.edges.size()`. |
| `inf` | `T` | The unreachable-distance sentinel. |
| `reachable` | `bool reachable(int path_edge_index) const` | Tests whether the corresponding replacement distance is finite. |

`VertexReplacementPathsResult<T>` contains:

| Member / method | Type / Signature | Meaning |
| --- | --- | --- |
| `path` | `GraphPath` | The selected or supplied fixed path. |
| `replacement_dist` | `std::vector<T>` | Entry `i` is the shortest distance after deleting vertex `path.vertices[i]`. Its size is `path.vertices.size()`. |
| `inf` | `T` | The unreachable-distance sentinel. |
| `reachable` | `bool reachable(int path_vertex_index) const` | Tests whether the corresponding replacement distance is finite. |

Deleting the source or target makes the route unavailable, so the first and
last vertex-replacement entries are `inf`. If `s == t`, the path has one vertex
and no edges, the edge result is empty, and the vertex result contains one
`inf`.

## Functions

Let $N$ be the number of vertices, $M$ the number of logical edges, and $K$ the
number of edges in the fixed path.

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `edge_replacement_paths` | `template <class T> EdgeReplacementPathsResult<T> edge_replacement_paths(const Graph<T>& g, int s, int t, T inf = std::numeric_limits<T>::max() / T(4))` | Selects one shortest path and processes every path-edge failure. | $O((N+M)\log N)$ time, $O(N+M)$ memory. |
| `edge_replacement_paths` | `template <class T> EdgeReplacementPathsResult<T> edge_replacement_paths(const Graph<T>& g, const GraphPath& path, T inf = std::numeric_limits<T>::max() / T(4))` | Processes every edge failure on the exact supplied shortest path. | $O((N+M)\log N)$ time, $O(N+M)$ memory. |
| `vertex_replacement_paths` | `template <class T> VertexReplacementPathsResult<T> vertex_replacement_paths(const Graph<T>& g, int s, int t, T inf = std::numeric_limits<T>::max() / T(4))` | Selects one shortest path and processes every path-vertex failure. | $O(K(N+M)\log N)$ time, $O(N+M)$ memory. |
| `vertex_replacement_paths` | `template <class T> VertexReplacementPathsResult<T> vertex_replacement_paths(const Graph<T>& g, const GraphPath& path, T inf = std::numeric_limits<T>::max() / T(4))` | Processes every vertex failure on the exact supplied shortest path. | $O(K(N+M)\log N)$ time, $O(N+M)$ memory. |

All additions saturate at `inf`. Choose `inf` larger than every finite answer
that must be represented.

## Edge Algorithm and Correctness

The edge solver runs Dijkstra from both endpoints. It constructs a shortest-path
tree rooted at $s$ that contains the exact fixed path: fixed-path parent edges
are forced, and every other reachable vertex receives a tight predecessor.
Strictly positive costs make predecessor distances decrease strictly toward the
root, so the forced tree is acyclic even when shortest paths tie.

Conceptually remove the fixed-path edges from this tree. Each remaining tree
component contains exactly one path vertex. Define `block[v] = i` when `v` lies
in the component containing $p_i$.

Consider an active non-path logical edge joining blocks $a<b$, oriented from
`u` in block $a$ to `v` in block $b$. The tree shortest path from $s$ to `u`
stays on the source side of every fixed-path edge with index in $[a,b)`. Thus

```text
dist_s[u] + cost(u, v) + dist_t[v]
```

is a candidate for every such edge failure. If the chosen shortest suffix from
`v` crosses the failed cut, replacing the offending portion by the appropriate
tree/path suffix gives an available route with no greater length. Conversely,
every replacement path has a first edge that crosses from
the source-side block to the target-side block; its prefix and suffix are no
shorter than the two Dijkstra distances. Taking minima therefore gives the
exact answer. Range `chmin` on $[a,b)$ processes all failures together.

The exact logical ids in `path.edges` are excluded as detour edges: a failed
edge cannot replace itself. A parallel edge has a different id and remains a
valid detour, even when its endpoints and cost are equal.

For a vertex $p_i$, an edge between blocks $a<b$ can similarly participate in
a bypass only for internal indices $a<i<b$, the integer range $[a+1,b)`, when
its prefix and suffix avoid $p_i$. Unlike edge failure, these one-edge ranges
are not complete: an optimal vertex-avoiding route can enter the failed
vertex's tree block through one detour edge and leave through another without
visiting the failed vertex. The current vertex solver therefore uses a proven
Dijkstra run that ignores each path vertex rather than making an incorrect
near-linear claim.

## Preconditions

Assertions check that:

* the graph consists of paired undirected arcs created by `add_edge`;
* all active costs are strictly positive;
* all supplied vertices and logical edge ids are valid;
* every supplied edge is active and joins its two listed vertices;
* supplied vertices are pairwise distinct; and
* the supplied path cost equals the shortest endpoint distance.

Directed graphs, graphs containing active zero-cost edges, and replacement-path
reconstruction are not supported.

## Examples

Automatic path selection:

```cpp
#include "graph/replacement_paths.hpp"

int main() {
    int n = 5;
    m1une::graph::Graph<long long> g(n);
    g.add_edge(0, 1, 2);
    g.add_edge(1, 4, 2);
    g.add_edge(0, 2, 3);
    g.add_edge(2, 4, 3);

    auto edge_result = m1une::graph::edge_replacement_paths(g, 0, 4);
    for (long long distance : edge_result.replacement_dist) {
        (void)distance;
    }
}
```

An exact externally supplied shortest path:

```cpp
#include "graph/replacement_paths.hpp"

int main() {
    m1une::graph::Graph<long long> g(4);
    int e01 = g.add_edge(0, 1, 2);
    int e13 = g.add_edge(1, 3, 2);
    g.add_edge(0, 2, 3);
    g.add_edge(2, 3, 3);

    m1une::graph::GraphPath fixed_path{
        .vertices = {0, 1, 3},
        .edges = {e01, e13},
    };
    auto vertex_result = m1une::graph::vertex_replacement_paths(g, fixed_path);
    (void)vertex_result;
}
```
