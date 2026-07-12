---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/k_shortest_walk.hpp
    title: K-Shortest Walk
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/k_shortest_walk
    links:
    - https://judge.yosupo.jp/problem/k_shortest_walk
  bundledCode: "#line 1 \"verify/graph/k_shortest_walk.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/k_shortest_walk\"\n\n#line 1 \"graph/k_shortest_walk.hpp\"\
    \n\n\n\n#include <cassert>\n#include <functional>\n#include <limits>\n#include\
    \ <queue>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 12 \"graph/k_shortest_walk.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nnamespace internal {\n\ntemplate <class T>\nclass KShortestWalkHeap\
    \ {\n    struct Node {\n        T key;\n        int to;\n        int left;\n \
    \       int right;\n        int rank;\n    };\n\n    std::vector<Node> _nodes;\n\
    \n    int rank(int root) const {\n        return root == -1 ? 0 : _nodes[root].rank;\n\
    \    }\n\n   public:\n    int make_node(T key, int to) {\n        int result =\
    \ int(_nodes.size());\n        _nodes.push_back(Node{key, to, -1, -1, 1});\n \
    \       return result;\n    }\n\n    int meld_mutable(int first, int second) {\n\
    \        if (first == -1) return second;\n        if (second == -1) return first;\n\
    \        if (_nodes[second].key < _nodes[first].key) std::swap(first, second);\n\
    \        _nodes[first].right = meld_mutable(_nodes[first].right, second);\n  \
    \      if (rank(_nodes[first].left) < rank(_nodes[first].right)) {\n         \
    \   std::swap(_nodes[first].left, _nodes[first].right);\n        }\n        _nodes[first].rank\
    \ = rank(_nodes[first].right) + 1;\n        return first;\n    }\n\n    int meld_persistent(int\
    \ first, int second) {\n        if (first == -1) return second;\n        if (second\
    \ == -1) return first;\n        if (_nodes[second].key < _nodes[first].key) std::swap(first,\
    \ second);\n        int result = int(_nodes.size());\n        _nodes.push_back(_nodes[first]);\n\
    \        _nodes[result].right = meld_persistent(_nodes[result].right, second);\n\
    \        if (rank(_nodes[result].left) < rank(_nodes[result].right)) {\n     \
    \       std::swap(_nodes[result].left, _nodes[result].right);\n        }\n   \
    \     _nodes[result].rank = rank(_nodes[result].right) + 1;\n        return result;\n\
    \    }\n\n    const Node& operator[](int index) const {\n        return _nodes[index];\n\
    \    }\n};\n\n}  // namespace internal\n\ntemplate <class T>\nstd::vector<T> k_shortest_walk(\n\
    \    const Graph<T>& g,\n    int s,\n    int t,\n    int k,\n    T inf = std::numeric_limits<T>::max()\
    \ / T(4)\n) {\n    int n = g.size();\n    assert(0 <= s && s < n);\n    assert(0\
    \ <= t && t < n);\n    assert(0 <= k);\n    if (k == 0) return {};\n\n    struct\
    \ ReverseEdge {\n        int from;\n        int index;\n        T cost;\n    };\n\
    \    std::vector<std::vector<ReverseEdge>> reverse_graph(n);\n    for (int from\
    \ = 0; from < n; from++) {\n        for (int index = 0; index < int(g[from].size());\
    \ index++) {\n            const auto& edge = g[from][index];\n            if (!edge.alive)\
    \ continue;\n            assert(T(0) <= edge.cost);\n            reverse_graph[edge.to].push_back(ReverseEdge{from,\
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
    }  // namespace m1une\n\n\n#line 4 \"verify/graph/k_shortest_walk.test.cpp\"\n\
    \n#line 7 \"verify/graph/k_shortest_walk.test.cpp\"\n#include <iostream>\n#line\
    \ 9 \"verify/graph/k_shortest_walk.test.cpp\"\n#include <random>\n#line 12 \"\
    verify/graph/k_shortest_walk.test.cpp\"\n\nnamespace {\n\nstd::vector<long long>\
    \ naive_k_shortest_walk(\n    const m1une::graph::Graph<long long>& graph,\n \
    \   int source,\n    int target,\n    int k\n) {\n    using Entry = std::pair<long\
    \ long, int>;\n    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>>\
    \ queue;\n    std::vector<int> popped(graph.size(), 0);\n    std::vector<long\
    \ long> result;\n    queue.emplace(0, source);\n    while (!queue.empty() && int(result.size())\
    \ < k) {\n        auto [cost, vertex] = queue.top();\n        queue.pop();\n \
    \       if (popped[vertex] == k) continue;\n        popped[vertex]++;\n      \
    \  if (vertex == target) result.push_back(cost);\n        for (const auto& edge\
    \ : graph[vertex]) {\n            if (edge.alive) queue.emplace(cost + edge.cost,\
    \ edge.to);\n        }\n    }\n    return result;\n}\n\nvoid deterministic_test()\
    \ {\n    m1une::graph::Graph<long long> graph(3);\n    graph.add_directed_edge(0,\
    \ 1, 2);\n    graph.add_directed_edge(1, 2, 3);\n    graph.add_directed_edge(0,\
    \ 2, 8);\n    graph.add_directed_edge(1, 1, 1);\n    std::vector<long long> expected{5,\
    \ 6, 7, 8, 8, 9};\n    assert(m1une::graph::k_shortest_walk(graph, 0, 2, 6) ==\
    \ expected);\n\n    m1une::graph::Graph<long long> loop(1);\n    loop.add_directed_edge(0,\
    \ 0, 0);\n    assert(m1une::graph::k_shortest_walk(loop, 0, 0, 20) == std::vector<long\
    \ long>(20, 0));\n\n    m1une::graph::Graph<long long> unreachable(2);\n    assert(m1une::graph::k_shortest_walk(unreachable,\
    \ 0, 1, 10).empty());\n    assert(m1une::graph::k_shortest_walk(unreachable, 0,\
    \ 0, 0).empty());\n}\n\nvoid randomized_test() {\n    std::mt19937 random(20260713);\n\
    \    for (int test = 0; test < 2000; test++) {\n        int n = std::uniform_int_distribution<int>(1,\
    \ 7)(random);\n        int m = std::uniform_int_distribution<int>(0, 18)(random);\n\
    \        int source = std::uniform_int_distribution<int>(0, n - 1)(random);\n\
    \        int target = std::uniform_int_distribution<int>(0, n - 1)(random);\n\
    \        int k = std::uniform_int_distribution<int>(0, 20)(random);\n        m1une::graph::Graph<long\
    \ long> graph(n);\n        for (int edge = 0; edge < m; edge++) {\n          \
    \  int from = std::uniform_int_distribution<int>(0, n - 1)(random);\n        \
    \    int to = std::uniform_int_distribution<int>(0, n - 1)(random);\n        \
    \    int cost = std::uniform_int_distribution<int>(0, 8)(random);\n          \
    \  int id = graph.add_directed_edge(from, to, cost);\n            if (std::uniform_int_distribution<int>(0,\
    \ 7)(random) == 0) graph.erase_edge(id);\n        }\n        auto expected = naive_k_shortest_walk(graph,\
    \ source, target, k);\n        auto actual = m1une::graph::k_shortest_walk(graph,\
    \ source, target, k);\n        assert(actual == expected);\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    deterministic_test();\n    randomized_test();\n\
    \n    int n, m, source, target, k;\n    std::cin >> n >> m >> source >> target\
    \ >> k;\n    m1une::graph::Graph<long long> graph(n);\n    for (int edge = 0;\
    \ edge < m; edge++) {\n        int from, to;\n        long long cost;\n      \
    \  std::cin >> from >> to >> cost;\n        graph.add_directed_edge(from, to,\
    \ cost);\n    }\n    auto answer = m1une::graph::k_shortest_walk(graph, source,\
    \ target, k);\n    answer.resize(k, -1);\n    for (long long value : answer) std::cout\
    \ << value << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/k_shortest_walk\"\n\n#include\
    \ \"../../graph/k_shortest_walk.hpp\"\n\n#include <cassert>\n#include <functional>\n\
    #include <iostream>\n#include <queue>\n#include <random>\n#include <utility>\n\
    #include <vector>\n\nnamespace {\n\nstd::vector<long long> naive_k_shortest_walk(\n\
    \    const m1une::graph::Graph<long long>& graph,\n    int source,\n    int target,\n\
    \    int k\n) {\n    using Entry = std::pair<long long, int>;\n    std::priority_queue<Entry,\
    \ std::vector<Entry>, std::greater<Entry>> queue;\n    std::vector<int> popped(graph.size(),\
    \ 0);\n    std::vector<long long> result;\n    queue.emplace(0, source);\n   \
    \ while (!queue.empty() && int(result.size()) < k) {\n        auto [cost, vertex]\
    \ = queue.top();\n        queue.pop();\n        if (popped[vertex] == k) continue;\n\
    \        popped[vertex]++;\n        if (vertex == target) result.push_back(cost);\n\
    \        for (const auto& edge : graph[vertex]) {\n            if (edge.alive)\
    \ queue.emplace(cost + edge.cost, edge.to);\n        }\n    }\n    return result;\n\
    }\n\nvoid deterministic_test() {\n    m1une::graph::Graph<long long> graph(3);\n\
    \    graph.add_directed_edge(0, 1, 2);\n    graph.add_directed_edge(1, 2, 3);\n\
    \    graph.add_directed_edge(0, 2, 8);\n    graph.add_directed_edge(1, 1, 1);\n\
    \    std::vector<long long> expected{5, 6, 7, 8, 8, 9};\n    assert(m1une::graph::k_shortest_walk(graph,\
    \ 0, 2, 6) == expected);\n\n    m1une::graph::Graph<long long> loop(1);\n    loop.add_directed_edge(0,\
    \ 0, 0);\n    assert(m1une::graph::k_shortest_walk(loop, 0, 0, 20) == std::vector<long\
    \ long>(20, 0));\n\n    m1une::graph::Graph<long long> unreachable(2);\n    assert(m1une::graph::k_shortest_walk(unreachable,\
    \ 0, 1, 10).empty());\n    assert(m1une::graph::k_shortest_walk(unreachable, 0,\
    \ 0, 0).empty());\n}\n\nvoid randomized_test() {\n    std::mt19937 random(20260713);\n\
    \    for (int test = 0; test < 2000; test++) {\n        int n = std::uniform_int_distribution<int>(1,\
    \ 7)(random);\n        int m = std::uniform_int_distribution<int>(0, 18)(random);\n\
    \        int source = std::uniform_int_distribution<int>(0, n - 1)(random);\n\
    \        int target = std::uniform_int_distribution<int>(0, n - 1)(random);\n\
    \        int k = std::uniform_int_distribution<int>(0, 20)(random);\n        m1une::graph::Graph<long\
    \ long> graph(n);\n        for (int edge = 0; edge < m; edge++) {\n          \
    \  int from = std::uniform_int_distribution<int>(0, n - 1)(random);\n        \
    \    int to = std::uniform_int_distribution<int>(0, n - 1)(random);\n        \
    \    int cost = std::uniform_int_distribution<int>(0, 8)(random);\n          \
    \  int id = graph.add_directed_edge(from, to, cost);\n            if (std::uniform_int_distribution<int>(0,\
    \ 7)(random) == 0) graph.erase_edge(id);\n        }\n        auto expected = naive_k_shortest_walk(graph,\
    \ source, target, k);\n        auto actual = m1une::graph::k_shortest_walk(graph,\
    \ source, target, k);\n        assert(actual == expected);\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    deterministic_test();\n    randomized_test();\n\
    \n    int n, m, source, target, k;\n    std::cin >> n >> m >> source >> target\
    \ >> k;\n    m1une::graph::Graph<long long> graph(n);\n    for (int edge = 0;\
    \ edge < m; edge++) {\n        int from, to;\n        long long cost;\n      \
    \  std::cin >> from >> to >> cost;\n        graph.add_directed_edge(from, to,\
    \ cost);\n    }\n    auto answer = m1une::graph::k_shortest_walk(graph, source,\
    \ target, k);\n    answer.resize(k, -1);\n    for (long long value : answer) std::cout\
    \ << value << \"\\n\";\n}\n"
  dependsOn:
  - graph/k_shortest_walk.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/k_shortest_walk.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 04:00:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/k_shortest_walk.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/k_shortest_walk.test.cpp
- /verify/verify/graph/k_shortest_walk.test.cpp.html
title: verify/graph/k_shortest_walk.test.cpp
---
