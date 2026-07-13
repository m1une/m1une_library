---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/enumerate_triangles.hpp
    title: Enumerate Triangles
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
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_triangles
    links:
    - https://judge.yosupo.jp/problem/enumerate_triangles
  bundledCode: "#line 1 \"verify/graph/enumerate_triangles.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/enumerate_triangles\"\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n\
    #include <vector>\n\n#line 1 \"graph/enumerate_triangles.hpp\"\n\n\n\n#line 5\
    \ \"graph/enumerate_triangles.hpp\"\n#include <utility>\n#line 7 \"graph/enumerate_triangles.hpp\"\
    \n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
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
    \ m1une\n\n\n#line 9 \"graph/enumerate_triangles.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\ntemplate <class T, class Callback>\nvoid enumerate_triangles(const\
    \ Graph<T>& graph, Callback&& callback) {\n    const int n = graph.size();\n \
    \   const std::vector<Edge<T>> edges = graph.edges();\n\n    std::vector<int>\
    \ degree(n, 0);\n    for (const Edge<T>& edge : edges) {\n        assert(edge.from\
    \ != edge.to);\n        degree[edge.from]++;\n        degree[edge.to]++;\n   \
    \ }\n\n    std::vector<std::vector<int>> oriented(n);\n    for (const Edge<T>&\
    \ edge : edges) {\n        int from = edge.from;\n        int to = edge.to;\n\
    \        if (degree[from] > degree[to] ||\n            (degree[from] == degree[to]\
    \ && from > to)) {\n            std::swap(from, to);\n        }\n        oriented[from].push_back(to);\n\
    \    }\n\n    std::vector<int> marked(n, -1);\n    for (int vertex = 0; vertex\
    \ < n; vertex++) {\n        for (int to : oriented[vertex]) marked[to] = vertex;\n\
    \        for (int middle : oriented[vertex]) {\n            for (int to : oriented[middle])\
    \ {\n                if (marked[to] != vertex) continue;\n                int\
    \ first = vertex;\n                int second = middle;\n                int third\
    \ = to;\n                if (first > second) std::swap(first, second);\n     \
    \           if (second > third) std::swap(second, third);\n                if\
    \ (first > second) std::swap(first, second);\n                callback(first,\
    \ second, third);\n            }\n        }\n    }\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 12 \"verify/graph/enumerate_triangles.test.cpp\"\
    \n\nnamespace {\n\nvoid test_randomized() {\n    std::uint64_t state = 0x123456789abcdef0ULL;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int test = 0; test < 300; test++)\
    \ {\n        const int n = 1 + int(random() % 16);\n        m1une::graph::Graph<>\
    \ graph(n);\n        std::vector<std::vector<char>> adjacent(n, std::vector<char>(n,\
    \ false));\n        for (int first = 0; first < n; first++) {\n            for\
    \ (int second = first + 1; second < n; second++) {\n                if (random()\
    \ % 4 != 0) continue;\n                const int edge = random() % 2 == 0\n  \
    \                                   ? graph.add_edge(first, second)\n        \
    \                             : graph.add_directed_edge(first, second);\n    \
    \            if (random() % 7 == 0) {\n                    graph.erase_edge(edge);\n\
    \                } else {\n                    adjacent[first][second] = true;\n\
    \                    adjacent[second][first] = true;\n                }\n    \
    \        }\n        }\n\n        std::vector<std::array<int, 3>> actual;\n   \
    \     m1une::graph::enumerate_triangles(\n            graph,\n            [&](int\
    \ first, int second, int third) {\n                assert(first < second && second\
    \ < third);\n                std::array<int, 3> triangle;\n                triangle[0]\
    \ = first;\n                triangle[1] = second;\n                triangle[2]\
    \ = third;\n                actual.push_back(triangle);\n            }\n     \
    \   );\n        std::sort(actual.begin(), actual.end());\n\n        std::vector<std::array<int,\
    \ 3>> expected;\n        for (int first = 0; first < n; first++) {\n         \
    \   for (int second = first + 1; second < n; second++) {\n                for\
    \ (int third = second + 1; third < n; third++) {\n                    if (!adjacent[first][second]\
    \ ||\n                        !adjacent[first][third] ||\n                   \
    \     !adjacent[second][third]) {\n                        continue;\n       \
    \             }\n                    std::array<int, 3> triangle;\n          \
    \          triangle[0] = first;\n                    triangle[1] = second;\n \
    \                   triangle[2] = third;\n                    expected.push_back(triangle);\n\
    \                }\n            }\n        }\n        assert(actual == expected);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int vertex_count, edge_count;\n    std::cin\
    \ >> vertex_count >> edge_count;\n    std::vector<long long> value(vertex_count);\n\
    \    for (long long& x : value) std::cin >> x;\n\n    m1une::graph::Graph<> graph(vertex_count);\n\
    \    for (int i = 0; i < edge_count; i++) {\n        int first, second;\n    \
    \    std::cin >> first >> second;\n        graph.add_edge(first, second);\n  \
    \  }\n\n    constexpr long long modulus = 998'244'353;\n    long long answer =\
    \ 0;\n    m1une::graph::enumerate_triangles(\n        graph,\n        [&](int\
    \ first, int second, int third) {\n            const long long product =\n   \
    \             value[first] * value[second] % modulus * value[third] % modulus;\n\
    \            answer += product;\n            if (answer >= modulus) answer -=\
    \ modulus;\n        }\n    );\n    std::cout << answer << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_triangles\"\n\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <vector>\n\n#include \"../../graph/enumerate_triangles.hpp\"\
    \n#include \"../../graph/graph.hpp\"\n\nnamespace {\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x123456789abcdef0ULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int test = 0; test < 300; test++) {\n        const\
    \ int n = 1 + int(random() % 16);\n        m1une::graph::Graph<> graph(n);\n \
    \       std::vector<std::vector<char>> adjacent(n, std::vector<char>(n, false));\n\
    \        for (int first = 0; first < n; first++) {\n            for (int second\
    \ = first + 1; second < n; second++) {\n                if (random() % 4 != 0)\
    \ continue;\n                const int edge = random() % 2 == 0\n            \
    \                         ? graph.add_edge(first, second)\n                  \
    \                   : graph.add_directed_edge(first, second);\n              \
    \  if (random() % 7 == 0) {\n                    graph.erase_edge(edge);\n   \
    \             } else {\n                    adjacent[first][second] = true;\n\
    \                    adjacent[second][first] = true;\n                }\n    \
    \        }\n        }\n\n        std::vector<std::array<int, 3>> actual;\n   \
    \     m1une::graph::enumerate_triangles(\n            graph,\n            [&](int\
    \ first, int second, int third) {\n                assert(first < second && second\
    \ < third);\n                std::array<int, 3> triangle;\n                triangle[0]\
    \ = first;\n                triangle[1] = second;\n                triangle[2]\
    \ = third;\n                actual.push_back(triangle);\n            }\n     \
    \   );\n        std::sort(actual.begin(), actual.end());\n\n        std::vector<std::array<int,\
    \ 3>> expected;\n        for (int first = 0; first < n; first++) {\n         \
    \   for (int second = first + 1; second < n; second++) {\n                for\
    \ (int third = second + 1; third < n; third++) {\n                    if (!adjacent[first][second]\
    \ ||\n                        !adjacent[first][third] ||\n                   \
    \     !adjacent[second][third]) {\n                        continue;\n       \
    \             }\n                    std::array<int, 3> triangle;\n          \
    \          triangle[0] = first;\n                    triangle[1] = second;\n \
    \                   triangle[2] = third;\n                    expected.push_back(triangle);\n\
    \                }\n            }\n        }\n        assert(actual == expected);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int vertex_count, edge_count;\n    std::cin\
    \ >> vertex_count >> edge_count;\n    std::vector<long long> value(vertex_count);\n\
    \    for (long long& x : value) std::cin >> x;\n\n    m1une::graph::Graph<> graph(vertex_count);\n\
    \    for (int i = 0; i < edge_count; i++) {\n        int first, second;\n    \
    \    std::cin >> first >> second;\n        graph.add_edge(first, second);\n  \
    \  }\n\n    constexpr long long modulus = 998'244'353;\n    long long answer =\
    \ 0;\n    m1une::graph::enumerate_triangles(\n        graph,\n        [&](int\
    \ first, int second, int third) {\n            const long long product =\n   \
    \             value[first] * value[second] % modulus * value[third] % modulus;\n\
    \            answer += product;\n            if (answer >= modulus) answer -=\
    \ modulus;\n        }\n    );\n    std::cout << answer << '\\n';\n}\n"
  dependsOn:
  - graph/enumerate_triangles.hpp
  - graph/graph.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/enumerate_triangles.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 20:21:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/enumerate_triangles.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/enumerate_triangles.test.cpp
- /verify/verify/graph/enumerate_triangles.test.cpp.html
title: verify/graph/enumerate_triangles.test.cpp
---
