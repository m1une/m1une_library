---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/scc.hpp
    title: Strongly Connected Components
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/scc
    links:
    - https://judge.yosupo.jp/problem/scc
  bundledCode: "#line 1 \"verify/graph/scc.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\
    \n\n#include <iostream>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\
    \n#include <cassert>\n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using\
    \ cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n   \
    \ bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true)\
    \ {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ =\
    \ true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\
    \n    int other(int v) const {\n        assert(v == from || v == to);\n      \
    \  return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph\
    \ {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
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
    \ m1une\n\n\n#line 1 \"graph/scc.hpp\"\n\n\n\n#include <algorithm>\n#line 6 \"\
    graph/scc.hpp\"\n#include <cstddef>\n#line 9 \"graph/scc.hpp\"\n\n#line 11 \"\
    graph/scc.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct SccResult {\n\
    \    int count;\n    std::vector<int> comp;\n    std::vector<std::vector<int>>\
    \ groups;\n\n    bool same(int u, int v) const {\n        assert(0 <= u && u <\
    \ int(comp.size()));\n        assert(0 <= v && v < int(comp.size()));\n      \
    \  return comp[u] == comp[v];\n    }\n\n    template <class T>\n    Graph<int>\
    \ dag(const Graph<T>& g) const {\n        std::vector<std::pair<int, int>> edges;\n\
    \        for (int v = 0; v < g.size(); v++) {\n            for (const auto& e\
    \ : g[v]) {\n                if (!e.alive) continue;\n                int a =\
    \ comp[e.from], b = comp[e.to];\n                if (a != b) edges.emplace_back(a,\
    \ b);\n            }\n        }\n        std::sort(edges.begin(), edges.end());\n\
    \        edges.erase(std::unique(edges.begin(), edges.end()), edges.end());\n\n\
    \        Graph<int> result(count);\n        for (auto [a, b] : edges) result.add_directed_edge(a,\
    \ b);\n        return result;\n    }\n};\n\ntemplate <class T>\nSccResult strongly_connected_components(const\
    \ Graph<T>& g) {\n    const int n = g.size();\n    std::vector<std::vector<int>>\
    \ reverse_graph(n);\n    for (int vertex = 0; vertex < n; vertex++) {\n      \
    \  for (const auto& edge : g[vertex]) {\n            if (edge.alive) reverse_graph[edge.to].push_back(vertex);\n\
    \        }\n    }\n\n    std::vector<char> seen(n, false);\n    std::vector<int>\
    \ order;\n    order.reserve(n);\n    std::vector<std::pair<int, std::size_t>>\
    \ dfs_stack;\n    for (int start = 0; start < n; start++) {\n        if (seen[start])\
    \ continue;\n        seen[start] = true;\n        dfs_stack.emplace_back(start,\
    \ 0);\n        while (!dfs_stack.empty()) {\n            int vertex = dfs_stack.back().first;\n\
    \            std::size_t& edge_index = dfs_stack.back().second;\n            while\
    \ (edge_index < g[vertex].size() &&\n                   !g[vertex][edge_index].alive)\
    \ {\n                edge_index++;\n            }\n            if (edge_index\
    \ == g[vertex].size()) {\n                order.push_back(vertex);\n         \
    \       dfs_stack.pop_back();\n                continue;\n            }\n    \
    \        const int to = g[vertex][edge_index++].to;\n            if (!seen[to])\
    \ {\n                seen[to] = true;\n                dfs_stack.emplace_back(to,\
    \ 0);\n            }\n        }\n    }\n\n    std::vector<int> comp(n, -1);\n\
    \    std::vector<std::vector<int>> groups;\n    std::vector<int> stack;\n    for\
    \ (auto iterator = order.rbegin(); iterator != order.rend(); ++iterator) {\n \
    \       const int start = *iterator;\n        if (comp[start] != -1) continue;\n\
    \        const int component = int(groups.size());\n        groups.emplace_back();\n\
    \        comp[start] = component;\n        stack.push_back(start);\n        while\
    \ (!stack.empty()) {\n            const int vertex = stack.back();\n         \
    \   stack.pop_back();\n            groups.back().push_back(vertex);\n        \
    \    for (int to : reverse_graph[vertex]) {\n                if (comp[to] != -1)\
    \ continue;\n                comp[to] = component;\n                stack.push_back(to);\n\
    \            }\n        }\n    }\n\n    return SccResult{int(groups.size()), std::move(comp),\
    \ std::move(groups)};\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n\
    #line 8 \"verify/graph/scc.test.cpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int vertex_count, edge_count;\n    std::cin\
    \ >> vertex_count >> edge_count;\n    m1une::graph::Graph<int> graph(vertex_count);\n\
    \    for (int i = 0; i < edge_count; i++) {\n        int from, to;\n        std::cin\
    \ >> from >> to;\n        graph.add_directed_edge(from, to);\n    }\n\n    m1une::graph::SccResult\
    \ result =\n        m1une::graph::strongly_connected_components(graph);\n    std::cout\
    \ << result.count << '\\n';\n    for (const std::vector<int>& group : result.groups)\
    \ {\n        std::cout << group.size();\n        for (int vertex : group) std::cout\
    \ << ' ' << vertex;\n        std::cout << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\n\n#include <iostream>\n\
    #include <vector>\n\n#include \"../../graph/graph.hpp\"\n#include \"../../graph/scc.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int vertex_count, edge_count;\n    std::cin >> vertex_count >> edge_count;\n\
    \    m1une::graph::Graph<int> graph(vertex_count);\n    for (int i = 0; i < edge_count;\
    \ i++) {\n        int from, to;\n        std::cin >> from >> to;\n        graph.add_directed_edge(from,\
    \ to);\n    }\n\n    m1une::graph::SccResult result =\n        m1une::graph::strongly_connected_components(graph);\n\
    \    std::cout << result.count << '\\n';\n    for (const std::vector<int>& group\
    \ : result.groups) {\n        std::cout << group.size();\n        for (int vertex\
    \ : group) std::cout << ' ' << vertex;\n        std::cout << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/graph.hpp
  - graph/scc.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/scc.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 20:12:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/scc.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/scc.test.cpp
- /verify/verify/graph/scc.test.cpp.html
title: verify/graph/scc.test.cpp
---
