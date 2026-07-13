---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/three_edge_connected_components.hpp
    title: Three-Edge-Connected Components
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/three_edge_connected_components
    links:
    - https://judge.yosupo.jp/problem/three_edge_connected_components
  bundledCode: "#line 1 \"verify/graph/three_edge_connected_components.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/three_edge_connected_components\"\
    \n\n#line 1 \"graph/three_edge_connected_components.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
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
    \ m1une\n\n\n#line 11 \"graph/three_edge_connected_components.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct ThreeEdgeConnectedComponentsResult {\n\
    \    std::vector<std::vector<int>> components;\n    std::vector<int> component_of_vertex;\n\
    \n    int component_count() const {\n        return int(components.size());\n\
    \    }\n\n    bool same(int first, int second) const {\n        assert(0 <= first\
    \ && first < int(component_of_vertex.size()));\n        assert(0 <= second &&\
    \ second < int(component_of_vertex.size()));\n        return component_of_vertex[first]\
    \ == component_of_vertex[second];\n    }\n};\n\nnamespace internal {\n\n// Maintains\
    \ every component as a circular linked list. Swapping two successors\n// concatenates\
    \ two different lists in O(1) time.\nstruct ThreeEdgeComponentCycles {\n    std::vector<int>\
    \ next;\n\n    explicit ThreeEdgeComponentCycles(int n) : next(n) {\n        std::iota(next.begin(),\
    \ next.end(), 0);\n    }\n\n    void unite(int first, int second) {\n        std::swap(next[first],\
    \ next[second]);\n    }\n\n    ThreeEdgeConnectedComponentsResult build_result()\
    \ const {\n        const int n = int(next.size());\n        ThreeEdgeConnectedComponentsResult\
    \ result;\n        result.component_of_vertex.assign(n, -1);\n        for (int\
    \ first = 0; first < n; first++) {\n            if (result.component_of_vertex[first]\
    \ != -1) continue;\n            const int component = result.component_count();\n\
    \            result.components.emplace_back();\n            int vertex = first;\n\
    \            do {\n                result.component_of_vertex[vertex] = component;\n\
    \                result.components.back().push_back(vertex);\n               \
    \ vertex = next[vertex];\n            } while (vertex != first);\n        }\n\
    \        return result;\n    }\n};\n\n}  // namespace internal\n\n// Decomposes\
    \ an undirected multigraph into maximal vertex sets joined by at\n// least three\
    \ edge-disjoint paths. This is an iterative form of Tsin's\n// one-pass contraction\
    \ algorithm.\ntemplate <class T>\nThreeEdgeConnectedComponentsResult three_edge_connected_components(\n\
    \    const Graph<T>& graph\n) {\n    const int n = graph.size();\n    const int\
    \ edge_count = graph.edge_count();\n\n#ifndef NDEBUG\n    std::vector<int> incidence_count(edge_count,\
    \ 0);\n    for (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>&\
    \ edge : graph[vertex]) {\n            if (!edge.alive) continue;\n          \
    \  assert(edge.from == vertex);\n            assert(0 <= edge.to && edge.to <\
    \ n);\n            assert(0 <= edge.id && edge.id < edge_count);\n           \
    \ incidence_count[edge.id]++;\n        }\n    }\n    for (int edge_id = 0; edge_id\
    \ < edge_count; edge_id++) {\n        if (incidence_count[edge_id] != 0) assert(incidence_count[edge_id]\
    \ == 2);\n    }\n#endif\n\n    const int none = n;\n    std::vector<int> enter(n,\
    \ -1);\n    std::vector<int> leave(n, 0);\n    std::vector<int> low(n, none);\n\
    \    std::vector<int> degree(n, 0);\n    std::vector<int> path(n, none);\n   \
    \ std::vector<int> parent(n, -1);\n    std::vector<int> parent_edge(n, -1);\n\
    \    std::vector<int> next_edge(n, 0);\n    std::vector<int> dfs_stack;\n    internal::ThreeEdgeComponentCycles\
    \ component_cycles(n);\n    int timer = 0;\n\n    auto absorb = [&](int vertex,\
    \ int other) {\n        component_cycles.unite(vertex, other);\n        degree[vertex]\
    \ += degree[other];\n    };\n\n    auto process_visited_edge = [&](int vertex,\
    \ int to) {\n        if (enter[to] < enter[vertex]) {\n            degree[vertex]++;\n\
    \            low[vertex] = std::min(low[vertex], enter[to]);\n            return;\n\
    \        }\n\n        degree[vertex]--;\n        int current = path[vertex];\n\
    \        while (current != none && enter[current] <= enter[to] && enter[to] <\
    \ leave[current]) {\n            absorb(vertex, current);\n            current\
    \ = path[current];\n        }\n        path[vertex] = current;\n    };\n\n   \
    \ auto process_child = [&](int vertex, int child) {\n        if (path[child] ==\
    \ none && degree[child] <= 1) {\n            degree[vertex] += degree[child];\n\
    \            low[vertex] = std::min(low[vertex], low[child]);\n            return;\n\
    \        }\n\n        int current = child;\n        if (degree[child] == 0) current\
    \ = path[child];\n        assert(current != none);\n        if (low[current] <\
    \ low[vertex]) {\n            low[vertex] = low[current];\n            std::swap(current,\
    \ path[vertex]);\n        }\n        while (current != none) {\n            absorb(vertex,\
    \ current);\n            current = path[current];\n        }\n    };\n\n    for\
    \ (int root = 0; root < n; root++) {\n        if (enter[root] != -1) continue;\n\
    \        enter[root] = timer++;\n        dfs_stack.push_back(root);\n\n      \
    \  while (!dfs_stack.empty()) {\n            const int vertex = dfs_stack.back();\n\
    \            if (next_edge[vertex] < int(graph[vertex].size())) {\n          \
    \      const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n           \
    \     if (!edge.alive || edge.from == edge.to || edge.id == parent_edge[vertex])\
    \ continue;\n                const int to = edge.to;\n                if (enter[to]\
    \ == -1) {\n                    parent[to] = vertex;\n                    parent_edge[to]\
    \ = edge.id;\n                    enter[to] = timer++;\n                    dfs_stack.push_back(to);\n\
    \                } else {\n                    process_visited_edge(vertex, to);\n\
    \                }\n                continue;\n            }\n\n            leave[vertex]\
    \ = timer;\n            dfs_stack.pop_back();\n            if (parent[vertex]\
    \ != -1) process_child(parent[vertex], vertex);\n        }\n    }\n\n    return\
    \ component_cycles.build_result();\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/graph/three_edge_connected_components.test.cpp\"\
    \n\n#line 7 \"verify/graph/three_edge_connected_components.test.cpp\"\n#include\
    \ <cstdint>\n#include <iostream>\n#include <queue>\n#line 11 \"verify/graph/three_edge_connected_components.test.cpp\"\
    \n\nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\nusing Result = m1une::graph::ThreeEdgeConnectedComponentsResult;\n\
    \nint naive_edge_connectivity(const Graph& graph, int source, int sink) {\n  \
    \  const int n = graph.size();\n    std::vector<std::vector<int>> capacity(n,\
    \ std::vector<int>(n, 0));\n    for (const auto& edge : graph.edges()) {\n   \
    \     if (edge.from == edge.to) continue;\n        capacity[edge.from][edge.to]++;\n\
    \        capacity[edge.to][edge.from]++;\n    }\n\n    int flow = 0;\n    while\
    \ (flow < 3) {\n        std::vector<int> parent(n, -1);\n        std::queue<int>\
    \ queue;\n        parent[source] = source;\n        queue.push(source);\n    \
    \    while (!queue.empty() && parent[sink] == -1) {\n            int vertex =\
    \ queue.front();\n            queue.pop();\n            for (int to = 0; to <\
    \ n; to++) {\n                if (capacity[vertex][to] == 0 || parent[to] != -1)\
    \ continue;\n                parent[to] = vertex;\n                queue.push(to);\n\
    \            }\n        }\n        if (parent[sink] == -1) break;\n        for\
    \ (int vertex = sink; vertex != source; vertex = parent[vertex]) {\n         \
    \   capacity[parent[vertex]][vertex]--;\n            capacity[vertex][parent[vertex]]++;\n\
    \        }\n        flow++;\n    }\n    return flow;\n}\n\nvoid validate(const\
    \ Graph& graph) {\n    Result result = m1une::graph::three_edge_connected_components(graph);\n\
    \    assert(result.component_of_vertex.size() == std::size_t(graph.size()));\n\
    \n    std::vector<int> occurrence(graph.size(), 0);\n    for (int component =\
    \ 0; component < result.component_count(); component++) {\n        assert(!result.components[component].empty());\n\
    \        for (int vertex : result.components[component]) {\n            assert(0\
    \ <= vertex && vertex < graph.size());\n            assert(result.component_of_vertex[vertex]\
    \ == component);\n            occurrence[vertex]++;\n        }\n    }\n    for\
    \ (int count : occurrence) assert(count == 1);\n\n    for (int first = 0; first\
    \ < graph.size(); first++) {\n        for (int second = 0; second < graph.size();\
    \ second++) {\n            bool expected = first == second || naive_edge_connectivity(graph,\
    \ first, second) >= 3;\n            assert(result.same(first, second) == expected);\n\
    \        }\n    }\n}\n\nvoid test_fixed() {\n    validate(Graph());\n    validate(Graph(1));\n\
    \n    Graph parallel(2);\n    parallel.add_edge(0, 1);\n    parallel.add_edge(0,\
    \ 1);\n    int third = parallel.add_edge(0, 1);\n    validate(parallel);\n   \
    \ assert(m1une::graph::three_edge_connected_components(parallel).same(0, 1));\n\
    \    parallel.erase_edge(third);\n    validate(parallel);\n    assert(!m1une::graph::three_edge_connected_components(parallel).same(0,\
    \ 1));\n    parallel.revive_edge(third);\n    validate(parallel);\n\n    Graph\
    \ complete(4);\n    for (int from = 0; from < 4; from++) {\n        for (int to\
    \ = from + 1; to < 4; to++) complete.add_edge(from, to);\n    }\n    complete.add_edge(0,\
    \ 0);\n    validate(complete);\n    assert(m1une::graph::three_edge_connected_components(complete).component_count()\
    \ == 1);\n\n    Graph joined(8);\n    for (int offset : {0, 4}) {\n        for\
    \ (int from = offset; from < offset + 4; from++) {\n            for (int to =\
    \ from + 1; to < offset + 4; to++) joined.add_edge(from, to);\n        }\n   \
    \ }\n    joined.add_edge(0, 4);\n    joined.add_edge(1, 5);\n    validate(joined);\n\
    \    auto joined_result = m1une::graph::three_edge_connected_components(joined);\n\
    \    assert(joined_result.component_count() == 2);\n    assert(joined_result.same(0,\
    \ 3));\n    assert(joined_result.same(4, 7));\n    assert(!joined_result.same(0,\
    \ 4));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 123456789;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 500;\
    \ trial++) {\n        int n = int(random() % 9);\n        Graph graph(n);\n  \
    \      int edge_count = int(random() % 26);\n        for (int i = 0; i < edge_count\
    \ && n > 0; i++) {\n            int id = graph.add_edge(int(random() % n), int(random()\
    \ % n));\n            if (random() % 7 == 0) graph.erase_edge(id);\n        }\n\
    \        validate(graph);\n    }\n}\n\nvoid test_deep_graph() {\n    const int\
    \ n = 50000;\n    Graph graph(n);\n    for (int vertex = 1; vertex < n; vertex++)\
    \ graph.add_edge(vertex - 1, vertex);\n    Result result = m1une::graph::three_edge_connected_components(graph);\n\
    \    assert(result.component_count() == n);\n}\n\n}  // namespace\n\nint main()\
    \ {\n    test_fixed();\n    test_randomized();\n    test_deep_graph();\n\n   \
    \ std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int n,\
    \ edge_count;\n    std::cin >> n >> edge_count;\n    Graph graph(n);\n    while\
    \ (edge_count--) {\n        int from, to;\n        std::cin >> from >> to;\n \
    \       graph.add_edge(from, to);\n    }\n\n    Result result = m1une::graph::three_edge_connected_components(graph);\n\
    \    std::cout << result.component_count() << '\\n';\n    for (const auto& component\
    \ : result.components) {\n        std::cout << component.size();\n        for\
    \ (int vertex : component) std::cout << ' ' << vertex;\n        std::cout << '\\\
    n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/three_edge_connected_components\"\
    \n\n#include \"../../graph/three_edge_connected_components.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <queue>\n\
    #include <vector>\n\nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\nusing\
    \ Result = m1une::graph::ThreeEdgeConnectedComponentsResult;\n\nint naive_edge_connectivity(const\
    \ Graph& graph, int source, int sink) {\n    const int n = graph.size();\n   \
    \ std::vector<std::vector<int>> capacity(n, std::vector<int>(n, 0));\n    for\
    \ (const auto& edge : graph.edges()) {\n        if (edge.from == edge.to) continue;\n\
    \        capacity[edge.from][edge.to]++;\n        capacity[edge.to][edge.from]++;\n\
    \    }\n\n    int flow = 0;\n    while (flow < 3) {\n        std::vector<int>\
    \ parent(n, -1);\n        std::queue<int> queue;\n        parent[source] = source;\n\
    \        queue.push(source);\n        while (!queue.empty() && parent[sink] ==\
    \ -1) {\n            int vertex = queue.front();\n            queue.pop();\n \
    \           for (int to = 0; to < n; to++) {\n                if (capacity[vertex][to]\
    \ == 0 || parent[to] != -1) continue;\n                parent[to] = vertex;\n\
    \                queue.push(to);\n            }\n        }\n        if (parent[sink]\
    \ == -1) break;\n        for (int vertex = sink; vertex != source; vertex = parent[vertex])\
    \ {\n            capacity[parent[vertex]][vertex]--;\n            capacity[vertex][parent[vertex]]++;\n\
    \        }\n        flow++;\n    }\n    return flow;\n}\n\nvoid validate(const\
    \ Graph& graph) {\n    Result result = m1une::graph::three_edge_connected_components(graph);\n\
    \    assert(result.component_of_vertex.size() == std::size_t(graph.size()));\n\
    \n    std::vector<int> occurrence(graph.size(), 0);\n    for (int component =\
    \ 0; component < result.component_count(); component++) {\n        assert(!result.components[component].empty());\n\
    \        for (int vertex : result.components[component]) {\n            assert(0\
    \ <= vertex && vertex < graph.size());\n            assert(result.component_of_vertex[vertex]\
    \ == component);\n            occurrence[vertex]++;\n        }\n    }\n    for\
    \ (int count : occurrence) assert(count == 1);\n\n    for (int first = 0; first\
    \ < graph.size(); first++) {\n        for (int second = 0; second < graph.size();\
    \ second++) {\n            bool expected = first == second || naive_edge_connectivity(graph,\
    \ first, second) >= 3;\n            assert(result.same(first, second) == expected);\n\
    \        }\n    }\n}\n\nvoid test_fixed() {\n    validate(Graph());\n    validate(Graph(1));\n\
    \n    Graph parallel(2);\n    parallel.add_edge(0, 1);\n    parallel.add_edge(0,\
    \ 1);\n    int third = parallel.add_edge(0, 1);\n    validate(parallel);\n   \
    \ assert(m1une::graph::three_edge_connected_components(parallel).same(0, 1));\n\
    \    parallel.erase_edge(third);\n    validate(parallel);\n    assert(!m1une::graph::three_edge_connected_components(parallel).same(0,\
    \ 1));\n    parallel.revive_edge(third);\n    validate(parallel);\n\n    Graph\
    \ complete(4);\n    for (int from = 0; from < 4; from++) {\n        for (int to\
    \ = from + 1; to < 4; to++) complete.add_edge(from, to);\n    }\n    complete.add_edge(0,\
    \ 0);\n    validate(complete);\n    assert(m1une::graph::three_edge_connected_components(complete).component_count()\
    \ == 1);\n\n    Graph joined(8);\n    for (int offset : {0, 4}) {\n        for\
    \ (int from = offset; from < offset + 4; from++) {\n            for (int to =\
    \ from + 1; to < offset + 4; to++) joined.add_edge(from, to);\n        }\n   \
    \ }\n    joined.add_edge(0, 4);\n    joined.add_edge(1, 5);\n    validate(joined);\n\
    \    auto joined_result = m1une::graph::three_edge_connected_components(joined);\n\
    \    assert(joined_result.component_count() == 2);\n    assert(joined_result.same(0,\
    \ 3));\n    assert(joined_result.same(4, 7));\n    assert(!joined_result.same(0,\
    \ 4));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 123456789;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 500;\
    \ trial++) {\n        int n = int(random() % 9);\n        Graph graph(n);\n  \
    \      int edge_count = int(random() % 26);\n        for (int i = 0; i < edge_count\
    \ && n > 0; i++) {\n            int id = graph.add_edge(int(random() % n), int(random()\
    \ % n));\n            if (random() % 7 == 0) graph.erase_edge(id);\n        }\n\
    \        validate(graph);\n    }\n}\n\nvoid test_deep_graph() {\n    const int\
    \ n = 50000;\n    Graph graph(n);\n    for (int vertex = 1; vertex < n; vertex++)\
    \ graph.add_edge(vertex - 1, vertex);\n    Result result = m1une::graph::three_edge_connected_components(graph);\n\
    \    assert(result.component_count() == n);\n}\n\n}  // namespace\n\nint main()\
    \ {\n    test_fixed();\n    test_randomized();\n    test_deep_graph();\n\n   \
    \ std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int n,\
    \ edge_count;\n    std::cin >> n >> edge_count;\n    Graph graph(n);\n    while\
    \ (edge_count--) {\n        int from, to;\n        std::cin >> from >> to;\n \
    \       graph.add_edge(from, to);\n    }\n\n    Result result = m1une::graph::three_edge_connected_components(graph);\n\
    \    std::cout << result.component_count() << '\\n';\n    for (const auto& component\
    \ : result.components) {\n        std::cout << component.size();\n        for\
    \ (int vertex : component) std::cout << ' ' << vertex;\n        std::cout << '\\\
    n';\n    }\n}\n"
  dependsOn:
  - graph/three_edge_connected_components.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/three_edge_connected_components.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 02:26:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/three_edge_connected_components.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/three_edge_connected_components.test.cpp
- /verify/verify/graph/three_edge_connected_components.test.cpp.html
title: verify/graph/three_edge_connected_components.test.cpp
---
