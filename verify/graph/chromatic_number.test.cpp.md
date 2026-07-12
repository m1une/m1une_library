---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/chromatic_number.hpp
    title: Chromatic Number
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
    PROBLEM: https://judge.yosupo.jp/problem/chromatic_number
    links:
    - https://judge.yosupo.jp/problem/chromatic_number
  bundledCode: "#line 1 \"verify/graph/chromatic_number.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/chromatic_number\"\n\n#include <iostream>\n\
    \n#line 1 \"graph/chromatic_number.hpp\"\n\n\n\n#include <array>\n#include <bit>\n\
    #include <cassert>\n#include <cstdint>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#line 5 \"graph/graph.hpp\"\n#include <utility>\n#line 7 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 11 \"graph/chromatic_number.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nnamespace detail {\n\nstruct ChromaticResidues {\n    static constexpr\
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
    \ n;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 7 \"verify/graph/chromatic_number.test.cpp\"\
    \n\nint main() {\n    int n, m;\n    std::cin >> n >> m;\n    m1une::graph::Graph<>\
    \ g(n);\n    while (m--) {\n        int u, v;\n        std::cin >> u >> v;\n \
    \       g.add_edge(u, v);\n    }\n    std::cout << m1une::graph::chromatic_number(g)\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/chromatic_number\"\n\n\
    #include <iostream>\n\n#include \"../../graph/chromatic_number.hpp\"\n#include\
    \ \"../../graph/graph.hpp\"\n\nint main() {\n    int n, m;\n    std::cin >> n\
    \ >> m;\n    m1une::graph::Graph<> g(n);\n    while (m--) {\n        int u, v;\n\
    \        std::cin >> u >> v;\n        g.add_edge(u, v);\n    }\n    std::cout\
    \ << m1une::graph::chromatic_number(g) << '\\n';\n}\n"
  dependsOn:
  - graph/chromatic_number.hpp
  - graph/graph.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/chromatic_number.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 03:53:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/chromatic_number.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/chromatic_number.test.cpp
- /verify/verify/graph/chromatic_number.test.cpp.html
title: verify/graph/chromatic_number.test.cpp
---
