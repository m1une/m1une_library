---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: Dijkstra
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/graph/dijkstra_custom_cost.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include <iostream>\n\
    #include <vector>\n\n#line 1 \"graph/dijkstra.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 6 \"graph/dijkstra.hpp\"\n#include <utility>\n#line 8 \"graph/dijkstra.hpp\"\
    \n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include <array>\n#line 8 \"graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
    \ {\n    using cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n   \
    \ int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1),\
    \ alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool\
    \ alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_)\
    \ {}\n\n    int other(int v) const {\n        assert(v == from || v == to);\n\
    \        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    struct EdgePositions {\n        std::array<std::pair<int, int>, 2> value{};\n\
    \        int size = 0;\n\n        void push_back(std::pair<int, int> position)\
    \ {\n            assert(size < 2);\n            value[size++] = position;\n  \
    \      }\n    };\n\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
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
    \ namespace graph\n}  // namespace m1une\n\n\n#line 10 \"graph/dijkstra.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DijkstraResult\
    \ {\n    std::vector<T> dist;\n    std::vector<char> reached;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    T inf = T();\n\n    bool reachable(int\
    \ v) const {\n        assert(0 <= v && v < int(dist.size()));\n        return\
    \ reached[v];\n    }\n\n    std::vector<int> path(int t) const {\n        assert(reachable(t));\n\
    \        std::vector<int> result;\n        for (int v = t; v != -1; v = parent[v])\
    \ result.push_back(v);\n        std::reverse(result.begin(), result.end());\n\
    \        return result;\n    }\n};\n\nnamespace internal {\n\ntemplate <class\
    \ T>\nclass DijkstraHeap {\n   private:\n    const std::vector<T>& dist_;\n  \
    \  std::vector<int> heap_;\n    std::vector<int> position_;\n\n    bool less(int\
    \ first, int second) const {\n        return dist_[heap_[first]] < dist_[heap_[second]];\n\
    \    }\n\n    void swap_nodes(int first, int second) {\n        std::swap(heap_[first],\
    \ heap_[second]);\n        position_[heap_[first]] = first;\n        position_[heap_[second]]\
    \ = second;\n    }\n\n    void sift_up(int index) {\n        while (index != 0)\
    \ {\n            const int parent = (index - 1) / 2;\n            if (!less(index,\
    \ parent)) break;\n            swap_nodes(index, parent);\n            index =\
    \ parent;\n        }\n    }\n\n    void sift_down(int index) {\n        while\
    \ (2 * index + 1 < int(heap_.size())) {\n            int child = 2 * index + 1;\n\
    \            if (child + 1 < int(heap_.size()) && less(child + 1, child)) {\n\
    \                ++child;\n            }\n            if (!less(child, index))\
    \ break;\n            swap_nodes(index, child);\n            index = child;\n\
    \        }\n    }\n\n   public:\n    DijkstraHeap(const std::vector<T>& dist,\
    \ int size)\n        : dist_(dist), position_(size, -1) {\n        heap_.reserve(size);\n\
    \    }\n\n    bool empty() const {\n        return heap_.empty();\n    }\n\n \
    \   void push_or_decrease(int vertex) {\n        int& position = position_[vertex];\n\
    \        if (position == -1) {\n            position = int(heap_.size());\n  \
    \          heap_.push_back(vertex);\n        }\n        sift_up(position);\n \
    \   }\n\n    int pop_min() {\n        const int result = heap_.front();\n    \
    \    position_[result] = -1;\n        if (heap_.size() == 1) {\n            heap_.pop_back();\n\
    \            return result;\n        }\n        heap_.front() = heap_.back();\n\
    \        position_[heap_.front()] = 0;\n        heap_.pop_back();\n        sift_down(0);\n\
    \        return result;\n    }\n};\n\n}  // namespace internal\n\ntemplate <class\
    \ T>\nDijkstraResult<T> dijkstra(const Graph<T>& g,\n                        \
    \   const std::vector<int>& sources) {\n    int n = g.size();\n    DijkstraResult<T>\
    \ result;\n    result.dist.resize(n);\n    result.reached.assign(n, false);\n\
    \    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\n \
    \   internal::DijkstraHeap<T> que(result.dist, n);\n    for (int s : sources)\
    \ {\n        assert(0 <= s && s < n);\n        if (result.reached[s]) continue;\n\
    \        result.reached[s] = true;\n        result.dist[s] = T();\n        que.push_or_decrease(s);\n\
    \    }\n\n    while (!que.empty()) {\n        const int current = que.pop_min();\n\
    \        for (const auto& e : g[current]) {\n            if (!e.alive) continue;\n\
    \            T nd = result.dist[current] + e.cost;\n            if (result.reached[e.to]\
    \ && !(nd < result.dist[e.to])) continue;\n            result.reached[e.to] =\
    \ true;\n            result.dist[e.to] = std::move(nd);\n            result.parent[e.to]\
    \ = current;\n            result.parent_edge[e.to] = e.id;\n            que.push_or_decrease(e.to);\n\
    \        }\n    }\n\n    return result;\n}\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, int s) {\n    return dijkstra(g, std::vector<int>{s});\n\
    }\n\n// Compatibility overload: unreachable distances are replaced by inf after\
    \ the\n// search. Reachability itself never depends on this sentinel.\ntemplate\
    \ <class T>\nDijkstraResult<T> dijkstra(const Graph<T>& g,\n                 \
    \          const std::vector<int>& sources, const T& inf) {\n    DijkstraResult<T>\
    \ result = dijkstra(g, sources);\n    result.inf = inf;\n    for (int v = 0; v\
    \ < int(result.dist.size()); v++) {\n        if (!result.reachable(v)) result.dist[v]\
    \ = inf;\n    }\n    return result;\n}\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, int s, const T& inf) {\n    return dijkstra(g, std::vector<int>{s},\
    \ inf);\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 9 \"verify/graph/dijkstra_custom_cost.test.cpp\"\
    \n\nstruct Cost {\n    long long value = 0;\n\n    Cost operator+(const Cost&\
    \ other) const {\n        return Cost{value + other.value};\n    }\n\n    friend\
    \ bool operator<(const Cost& first, const Cost& second) {\n        return first.value\
    \ < second.value;\n    }\n};\n\nvoid test_custom_cost() {\n    m1une::graph::Graph<Cost>\
    \ graph(6);\n    graph.add_directed_edge(0, 1, Cost{8});\n    graph.add_directed_edge(0,\
    \ 2, Cost{2});\n    graph.add_directed_edge(2, 1, Cost{3});\n    graph.add_directed_edge(1,\
    \ 3, Cost{4});\n    graph.add_directed_edge(2, 3, Cost{20});\n    graph.add_directed_edge(4,\
    \ 3, Cost{1});\n\n    auto result = m1une::graph::dijkstra(graph, 0);\n    assert(result.reachable(0));\n\
    \    assert(result.reachable(3));\n    assert(!result.reachable(4));\n    assert(!result.reachable(5));\n\
    \    assert(result.dist[0].value == 0);\n    assert(result.dist[1].value == 5);\n\
    \    assert(result.dist[3].value == 9);\n    assert((result.path(3) == std::vector<int>{0,\
    \ 2, 1, 3}));\n\n    auto multi = m1une::graph::dijkstra(\n        graph, std::vector<int>{0,\
    \ 4, 0});\n    assert(multi.reachable(4));\n    assert(multi.dist[3].value ==\
    \ 1);\n    assert((multi.path(3) == std::vector<int>{4, 3}));\n}\n\nvoid test_explicit_sentinel_is_not_reachability()\
    \ {\n    m1une::graph::Graph<Cost> graph(3);\n    graph.add_directed_edge(0, 1,\
    \ Cost{99});\n\n    auto result = m1une::graph::dijkstra(graph, 0, Cost{99});\n\
    \    assert(result.inf.value == 99);\n    assert(result.reachable(1));\n    assert(result.dist[1].value\
    \ == 99);\n    assert(!result.reachable(2));\n    assert(result.dist[2].value\
    \ == 99);\n}\n\nint main() {\n    test_custom_cost();\n    test_explicit_sentinel_is_not_reachability();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\n\n#include \"../../graph/dijkstra.hpp\"\
    \n#include \"../../graph/graph.hpp\"\n\nstruct Cost {\n    long long value = 0;\n\
    \n    Cost operator+(const Cost& other) const {\n        return Cost{value + other.value};\n\
    \    }\n\n    friend bool operator<(const Cost& first, const Cost& second) {\n\
    \        return first.value < second.value;\n    }\n};\n\nvoid test_custom_cost()\
    \ {\n    m1une::graph::Graph<Cost> graph(6);\n    graph.add_directed_edge(0, 1,\
    \ Cost{8});\n    graph.add_directed_edge(0, 2, Cost{2});\n    graph.add_directed_edge(2,\
    \ 1, Cost{3});\n    graph.add_directed_edge(1, 3, Cost{4});\n    graph.add_directed_edge(2,\
    \ 3, Cost{20});\n    graph.add_directed_edge(4, 3, Cost{1});\n\n    auto result\
    \ = m1une::graph::dijkstra(graph, 0);\n    assert(result.reachable(0));\n    assert(result.reachable(3));\n\
    \    assert(!result.reachable(4));\n    assert(!result.reachable(5));\n    assert(result.dist[0].value\
    \ == 0);\n    assert(result.dist[1].value == 5);\n    assert(result.dist[3].value\
    \ == 9);\n    assert((result.path(3) == std::vector<int>{0, 2, 1, 3}));\n\n  \
    \  auto multi = m1une::graph::dijkstra(\n        graph, std::vector<int>{0, 4,\
    \ 0});\n    assert(multi.reachable(4));\n    assert(multi.dist[3].value == 1);\n\
    \    assert((multi.path(3) == std::vector<int>{4, 3}));\n}\n\nvoid test_explicit_sentinel_is_not_reachability()\
    \ {\n    m1une::graph::Graph<Cost> graph(3);\n    graph.add_directed_edge(0, 1,\
    \ Cost{99});\n\n    auto result = m1une::graph::dijkstra(graph, 0, Cost{99});\n\
    \    assert(result.inf.value == 99);\n    assert(result.reachable(1));\n    assert(result.dist[1].value\
    \ == 99);\n    assert(!result.reachable(2));\n    assert(result.dist[2].value\
    \ == 99);\n}\n\nint main() {\n    test_custom_cost();\n    test_explicit_sentinel_is_not_reachability();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - graph/dijkstra.hpp
  - graph/graph.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/dijkstra_custom_cost.test.cpp
  requiredBy: []
  timestamp: '2026-08-13 01:41:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/dijkstra_custom_cost.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/dijkstra_custom_cost.test.cpp
- /verify/verify/graph/dijkstra_custom_cost.test.cpp.html
title: verify/graph/dijkstra_custom_cost.test.cpp
---
