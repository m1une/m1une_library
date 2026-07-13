---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/cycle_detection.hpp
    title: Cycle Detection
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/cycle_detection
    links:
    - https://judge.yosupo.jp/problem/cycle_detection
  bundledCode: "#line 1 \"verify/graph/cycle_detection.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/cycle_detection\"\n\n#line 1 \"graph/cycle_detection.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cstddef>\n#include <vector>\n\n#line 1\
    \ \"graph/graph.hpp\"\n\n\n\n#include <cassert>\n#include <utility>\n#line 7 \"\
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
    \ m1une\n\n\n#line 9 \"graph/cycle_detection.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct Cycle {\n    std::vector<int> vertices;\n    std::vector<int>\
    \ edge_ids;\n\n    bool empty() const {\n        return vertices.empty();\n  \
    \  }\n};\n\ninline Cycle restore_cycle(int from, int to, int closing_edge, const\
    \ std::vector<int>& parent,\n                           const std::vector<int>&\
    \ parent_edge) {\n    Cycle result;\n    result.vertices.push_back(to);\n\n  \
    \  std::vector<int> middle_vertices;\n    std::vector<int> middle_edges;\n   \
    \ for (int v = from; v != to; v = parent[v]) {\n        middle_vertices.push_back(v);\n\
    \        middle_edges.push_back(parent_edge[v]);\n    }\n    std::reverse(middle_vertices.begin(),\
    \ middle_vertices.end());\n    std::reverse(middle_edges.begin(), middle_edges.end());\n\
    \n    result.vertices.insert(result.vertices.end(), middle_vertices.begin(), middle_vertices.end());\n\
    \    result.vertices.push_back(to);\n    result.edge_ids.insert(result.edge_ids.end(),\
    \ middle_edges.begin(), middle_edges.end());\n    result.edge_ids.push_back(closing_edge);\n\
    \    return result;\n}\n\ntemplate <class T>\nCycle find_directed_cycle(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> color(n, 0), parent(n,\
    \ -1), parent_edge(n, -1);\n    struct Frame {\n        int vertex;\n        std::size_t\
    \ next_edge;\n    };\n\n    std::vector<Frame> stack;\n    stack.reserve(n);\n\
    \    for (int start = 0; start < n; start++) {\n        if (color[start] != 0)\
    \ continue;\n        color[start] = 1;\n        stack.push_back(Frame{start, 0});\n\
    \        while (!stack.empty()) {\n            Frame& frame = stack.back();\n\
    \            const int vertex = frame.vertex;\n            const auto& adjacency\
    \ = g[vertex];\n            while (\n                frame.next_edge < adjacency.size()\
    \ &&\n                !adjacency[frame.next_edge].alive\n            ) {\n   \
    \             frame.next_edge++;\n            }\n            if (frame.next_edge\
    \ == adjacency.size()) {\n                color[vertex] = 2;\n               \
    \ stack.pop_back();\n                continue;\n            }\n\n            const\
    \ auto& edge = adjacency[frame.next_edge++];\n            const int to = edge.to;\n\
    \            const int edge_id = edge.id;\n            if (color[to] == 0) {\n\
    \                parent[to] = vertex;\n                parent_edge[to] = edge_id;\n\
    \                color[to] = 1;\n                stack.push_back(Frame{to, 0});\n\
    \            } else if (color[to] == 1) {\n                return restore_cycle(vertex,\
    \ to, edge_id, parent, parent_edge);\n            }\n        }\n    }\n    return\
    \ Cycle();\n}\n\ntemplate <class T>\nCycle find_undirected_cycle(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    std::vector<int> color(n, 0), parent(n, -1),\
    \ parent_edge(n, -1);\n    struct Frame {\n        int vertex;\n        std::size_t\
    \ next_edge;\n    };\n\n    std::vector<Frame> stack;\n    stack.reserve(n);\n\
    \    for (int start = 0; start < n; start++) {\n        if (color[start] != 0)\
    \ continue;\n        color[start] = 1;\n        stack.push_back(Frame{start, 0});\n\
    \        while (!stack.empty()) {\n            Frame& frame = stack.back();\n\
    \            const int vertex = frame.vertex;\n            const auto& adjacency\
    \ = g[vertex];\n            while (\n                frame.next_edge < adjacency.size()\
    \ &&\n                (\n                    !adjacency[frame.next_edge].alive\
    \ ||\n                    adjacency[frame.next_edge].id == parent_edge[vertex]\n\
    \                )\n            ) {\n                frame.next_edge++;\n    \
    \        }\n            if (frame.next_edge == adjacency.size()) {\n         \
    \       color[vertex] = 2;\n                stack.pop_back();\n              \
    \  continue;\n            }\n\n            const auto& edge = adjacency[frame.next_edge++];\n\
    \            const int to = edge.to;\n            const int edge_id = edge.id;\n\
    \            if (color[to] == 0) {\n                parent[to] = vertex;\n   \
    \             parent_edge[to] = edge_id;\n                color[to] = 1;\n   \
    \             stack.push_back(Frame{to, 0});\n            } else if (color[to]\
    \ == 1) {\n                return restore_cycle(vertex, to, edge_id, parent, parent_edge);\n\
    \            }\n        }\n    }\n    return Cycle();\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 5 \"verify/graph/cycle_detection.test.cpp\"\n\
    \n#include <iostream>\n\nint main() {\n    int vertex_count, edge_count;\n   \
    \ std::cin >> vertex_count >> edge_count;\n    m1une::graph::Graph<> graph(vertex_count);\n\
    \    for (int edge = 0; edge < edge_count; edge++) {\n        int from, to;\n\
    \        std::cin >> from >> to;\n        graph.add_directed_edge(from, to);\n\
    \    }\n\n    m1une::graph::Cycle cycle = m1une::graph::find_directed_cycle(graph);\n\
    \    if (cycle.empty()) {\n        std::cout << -1 << '\\n';\n        return 0;\n\
    \    }\n    std::cout << cycle.edge_ids.size() << '\\n';\n    for (int edge :\
    \ cycle.edge_ids) std::cout << edge << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cycle_detection\"\n\n#include\
    \ \"../../graph/cycle_detection.hpp\"\n#include \"../../graph/graph.hpp\"\n\n\
    #include <iostream>\n\nint main() {\n    int vertex_count, edge_count;\n    std::cin\
    \ >> vertex_count >> edge_count;\n    m1une::graph::Graph<> graph(vertex_count);\n\
    \    for (int edge = 0; edge < edge_count; edge++) {\n        int from, to;\n\
    \        std::cin >> from >> to;\n        graph.add_directed_edge(from, to);\n\
    \    }\n\n    m1une::graph::Cycle cycle = m1une::graph::find_directed_cycle(graph);\n\
    \    if (cycle.empty()) {\n        std::cout << -1 << '\\n';\n        return 0;\n\
    \    }\n    std::cout << cycle.edge_ids.size() << '\\n';\n    for (int edge :\
    \ cycle.edge_ids) std::cout << edge << '\\n';\n}\n"
  dependsOn:
  - graph/cycle_detection.hpp
  - graph/graph.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/cycle_detection.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 03:22:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/cycle_detection.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/cycle_detection.test.cpp
- /verify/verify/graph/cycle_detection.test.cpp.html
title: verify/graph/cycle_detection.test.cpp
---
