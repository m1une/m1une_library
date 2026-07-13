---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: graph/complement_connected_components.hpp
    title: Complement-Graph Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/connected_components.hpp
    title: Connected Components
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
    PROBLEM: https://judge.yosupo.jp/problem/connected_components_of_complement_graph
    links:
    - https://judge.yosupo.jp/problem/connected_components_of_complement_graph
  bundledCode: "#line 1 \"verify/graph/complement_connected_components.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/connected_components_of_complement_graph\"\
    \n\n#line 1 \"graph/complement_connected_components.hpp\"\n\n\n\n#include <queue>\n\
    #include <vector>\n\n#line 1 \"graph/connected_components.hpp\"\n\n\n\n#include\
    \ <cassert>\n#line 6 \"graph/connected_components.hpp\"\n\n#line 1 \"ds/dsu/dsu.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <numeric>\n#include <utility>\n#line 8\
    \ \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\nstruct Dsu {\n  \
    \ private:\n    int _n;\n    // parent_or_size[i] is the parent of i if it's >=\
    \ 0.\n    // If it's < 0, then i is a root and -parent_or_size[i] is the size\
    \ of the group.\n    std::vector<int> parent_or_size;\n\n    // Returns {new leader,\
    \ absorbed leader}. The absorbed leader is -1 when\n    // both vertices already\
    \ belong to the same component.\n    std::pair<int, int> merge_leaders(int a,\
    \ int b) {\n        int x = leader(a), y = leader(b);\n        if (x == y) return\
    \ {x, -1};\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return {x, y};\n    }\n\n   public:\n    Dsu() : _n(0) {}\n  \
    \  explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\n    // Merges the\
    \ group containing 'a' with the group containing 'b'.\n    // Returns the leader\
    \ of the merged group.\n    int merge(int a, int b) {\n        return merge_leaders(a,\
    \ b).first;\n    }\n\n    // Invokes callback(new_leader, absorbed_leader) after\
    \ an actual merge.\n    // Returns the leader of the merged group.\n    template\
    \ <class Callback>\n    int merge(int a, int b, Callback&& callback) {\n     \
    \   std::pair<int, int> merged = merge_leaders(a, b);\n        if (merged.second\
    \ != -1) callback(merged.first, merged.second);\n        return merged.first;\n\
    \    }\n\n    // Returns true if 'a' and 'b' belong to the same group.\n    bool\
    \ same(int a, int b) {\n        return leader(a) == leader(b);\n    }\n\n    //\
    \ Returns the leader (representative) of the group containing 'a'.\n    int leader(int\
    \ a) {\n        if (parent_or_size[a] < 0) return a;\n        // Path compression\n\
    \        return parent_or_size[a] = leader(parent_or_size[a]);\n    }\n\n    //\
    \ Returns the size of the group containing 'a'.\n    int size(int a) {\n     \
    \   return -parent_or_size[leader(a)];\n    }\n\n    // Returns a list of all\
    \ groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 9 \"graph/connected_components.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nstruct ConnectedComponents {\n    int count;\n    std::vector<int>\
    \ comp;\n    std::vector<std::vector<int>> groups;\n\n    bool same(int u, int\
    \ v) const {\n        assert(0 <= u && u < int(comp.size()));\n        assert(0\
    \ <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n    }\n\
    };\n\ntemplate <class T>\nConnectedComponents connected_components(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    m1une::ds::Dsu dsu(n);\n    for (const auto&\
    \ e : g.edges()) dsu.merge(e.from, e.to);\n\n    ConnectedComponents result;\n\
    \    result.comp.assign(n, 0);\n    std::vector<int> leader_to_comp(n, -1);\n\
    \    for (int v = 0; v < n; v++) {\n        int leader = dsu.leader(v);\n    \
    \    if (leader_to_comp[leader] == -1) {\n            leader_to_comp[leader] =\
    \ int(result.groups.size());\n            result.groups.push_back({});\n     \
    \   }\n        int c = leader_to_comp[leader];\n        result.comp[v] = c;\n\
    \        result.groups[c].push_back(v);\n    }\n    result.count = int(result.groups.size());\n\
    \n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n\
    #line 8 \"graph/complement_connected_components.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\n// Computes connected components after complementing the underlying\
    \ simple\n// undirected graph, without constructing the complement graph.\ntemplate\
    \ <class T>\nConnectedComponents complement_connected_components(const Graph<T>&\
    \ graph) {\n    const int size = graph.size();\n    std::vector<std::vector<int>>\
    \ adjacency(size);\n    for (const Edge<T>& edge : graph.edges()) {\n        if\
    \ (edge.from == edge.to) continue;\n        adjacency[edge.from].push_back(edge.to);\n\
    \        adjacency[edge.to].push_back(edge.from);\n    }\n\n    const int sentinel\
    \ = size;\n    std::vector<int> next(size + 1);\n    std::vector<int> previous(size\
    \ + 1);\n    if (size == 0) {\n        next[sentinel] = previous[sentinel] = sentinel;\n\
    \    } else {\n        next[sentinel] = 0;\n        previous[sentinel] = size\
    \ - 1;\n        for (int vertex = 0; vertex < size; vertex++) {\n            next[vertex]\
    \ = (vertex + 1 == size ? sentinel : vertex + 1);\n            previous[vertex]\
    \ = (vertex == 0 ? sentinel : vertex - 1);\n        }\n    }\n\n    auto erase\
    \ = [&](int vertex) {\n        next[previous[vertex]] = next[vertex];\n      \
    \  previous[next[vertex]] = previous[vertex];\n    };\n\n    ConnectedComponents\
    \ result;\n    result.comp.assign(size, -1);\n    std::vector<int> neighbor_stamp(size,\
    \ -1);\n    std::queue<int> queue;\n\n    while (next[sentinel] != sentinel) {\n\
    \        const int root = next[sentinel];\n        erase(root);\n        const\
    \ int component = int(result.groups.size());\n        result.groups.emplace_back();\n\
    \        result.groups.back().push_back(root);\n        result.comp[root] = component;\n\
    \        queue.push(root);\n\n        while (!queue.empty()) {\n            const\
    \ int vertex = queue.front();\n            queue.pop();\n            for (int\
    \ to : adjacency[vertex]) neighbor_stamp[to] = vertex;\n\n            int candidate\
    \ = next[sentinel];\n            while (candidate != sentinel) {\n           \
    \     const int following = next[candidate];\n                if (neighbor_stamp[candidate]\
    \ != vertex) {\n                    erase(candidate);\n                    result.comp[candidate]\
    \ = component;\n                    result.groups.back().push_back(candidate);\n\
    \                    queue.push(candidate);\n                }\n             \
    \   candidate = following;\n            }\n        }\n    }\n    result.count\
    \ = int(result.groups.size());\n    return result;\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 4 \"verify/graph/complement_connected_components.test.cpp\"\
    \n\n#line 6 \"verify/graph/complement_connected_components.test.cpp\"\n#include\
    \ <cstdint>\n#include <iostream>\n#line 10 \"verify/graph/complement_connected_components.test.cpp\"\
    \n\nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\nusing Result = m1une::graph::ConnectedComponents;\n\
    \nstd::vector<int> naive_components(const Graph& graph) {\n    const int size\
    \ = graph.size();\n    std::vector<std::vector<char>> adjacent(size, std::vector<char>(size,\
    \ false));\n    for (const auto& edge : graph.edges()) {\n        if (edge.from\
    \ == edge.to) continue;\n        adjacent[edge.from][edge.to] = true;\n      \
    \  adjacent[edge.to][edge.from] = true;\n    }\n\n    std::vector<int> component(size,\
    \ -1);\n    std::queue<int> queue;\n    int component_count = 0;\n    for (int\
    \ root = 0; root < size; root++) {\n        if (component[root] != -1) continue;\n\
    \        component[root] = component_count;\n        queue.push(root);\n     \
    \   while (!queue.empty()) {\n            const int vertex = queue.front();\n\
    \            queue.pop();\n            for (int to = 0; to < size; to++) {\n \
    \               if (to == vertex || adjacent[vertex][to] || component[to] != -1)\
    \ continue;\n                component[to] = component_count;\n              \
    \  queue.push(to);\n            }\n        }\n        component_count++;\n   \
    \ }\n    return component;\n}\n\nvoid validate(const Graph& graph) {\n    Result\
    \ result = m1une::graph::complement_connected_components(graph);\n    std::vector<int>\
    \ expected = naive_components(graph);\n    assert(int(result.comp.size()) == graph.size());\n\
    \    assert(result.count == int(result.groups.size()));\n\n    std::vector<int>\
    \ occurrence(graph.size(), 0);\n    for (int component = 0; component < result.count;\
    \ component++) {\n        assert(!result.groups[component].empty());\n       \
    \ for (int vertex : result.groups[component]) {\n            assert(0 <= vertex\
    \ && vertex < graph.size());\n            assert(result.comp[vertex] == component);\n\
    \            occurrence[vertex]++;\n        }\n    }\n    for (int vertex = 0;\
    \ vertex < graph.size(); vertex++) {\n        assert(occurrence[vertex] == 1);\n\
    \        for (int other = 0; other < graph.size(); other++) {\n            assert(result.same(vertex,\
    \ other) == (expected[vertex] == expected[other]));\n        }\n    }\n}\n\nvoid\
    \ test_fixed() {\n    validate(Graph());\n    validate(Graph(1));\n\n    Graph\
    \ no_edges(10);\n    validate(no_edges);\n    assert(m1une::graph::complement_connected_components(no_edges).count\
    \ == 1);\n\n    Graph complete(9);\n    for (int first = 0; first < 9; first++)\
    \ {\n        for (int second = first + 1; second < 9; second++) {\n          \
    \  complete.add_edge(first, second);\n        }\n    }\n    validate(complete);\n\
    \    assert(m1une::graph::complement_connected_components(complete).count == 9);\n\
    \n    Graph star(8);\n    for (int vertex = 1; vertex < 8; vertex++) star.add_edge(0,\
    \ vertex);\n    validate(star);\n    assert(m1une::graph::complement_connected_components(star).count\
    \ == 2);\n\n    Graph mixed(5);\n    mixed.add_directed_edge(0, 1);\n    mixed.add_edge(0,\
    \ 1);\n    int inactive = mixed.add_edge(1, 2);\n    mixed.erase_edge(inactive);\n\
    \    mixed.add_edge(3, 3);\n    validate(mixed);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x8cb92baa3f3d8dd7ULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 1000; trial++) {\n       \
    \ const int size = int(random() % 13);\n        Graph graph(size);\n        for\
    \ (int first = 0; first < size; first++) {\n            for (int second = first\
    \ + 1; second < size; second++) {\n                if (random() % 2 == 0) continue;\n\
    \                if (random() & 1) {\n                    graph.add_edge(first,\
    \ second);\n                } else {\n                    graph.add_directed_edge(first,\
    \ second);\n                }\n                if (random() % 11 == 0) graph.add_edge(first,\
    \ second);\n            }\n        }\n        validate(graph);\n    }\n}\n\nvoid\
    \ test_large_sparse_graph() {\n    const int size = 100000;\n    Graph graph(size);\n\
    \    for (int vertex = 1; vertex < size; vertex++) graph.add_edge(vertex - 1,\
    \ vertex);\n    Result result = m1une::graph::complement_connected_components(graph);\n\
    \    assert(result.count == 1);\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n\
    \    test_randomized();\n    test_large_sparse_graph();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int size, edge_count;\n    std::cin >> size\
    \ >> edge_count;\n    Graph graph(size);\n    while (edge_count--) {\n       \
    \ int first, second;\n        std::cin >> first >> second;\n        graph.add_edge(first,\
    \ second);\n    }\n\n    Result result = m1une::graph::complement_connected_components(graph);\n\
    \    std::cout << result.count << '\\n';\n    for (const auto& component : result.groups)\
    \ {\n        std::cout << component.size();\n        for (int vertex : component)\
    \ std::cout << ' ' << vertex;\n        std::cout << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/connected_components_of_complement_graph\"\
    \n\n#include \"../../graph/complement_connected_components.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <queue>\n#include <vector>\n\
    \nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\nusing Result = m1une::graph::ConnectedComponents;\n\
    \nstd::vector<int> naive_components(const Graph& graph) {\n    const int size\
    \ = graph.size();\n    std::vector<std::vector<char>> adjacent(size, std::vector<char>(size,\
    \ false));\n    for (const auto& edge : graph.edges()) {\n        if (edge.from\
    \ == edge.to) continue;\n        adjacent[edge.from][edge.to] = true;\n      \
    \  adjacent[edge.to][edge.from] = true;\n    }\n\n    std::vector<int> component(size,\
    \ -1);\n    std::queue<int> queue;\n    int component_count = 0;\n    for (int\
    \ root = 0; root < size; root++) {\n        if (component[root] != -1) continue;\n\
    \        component[root] = component_count;\n        queue.push(root);\n     \
    \   while (!queue.empty()) {\n            const int vertex = queue.front();\n\
    \            queue.pop();\n            for (int to = 0; to < size; to++) {\n \
    \               if (to == vertex || adjacent[vertex][to] || component[to] != -1)\
    \ continue;\n                component[to] = component_count;\n              \
    \  queue.push(to);\n            }\n        }\n        component_count++;\n   \
    \ }\n    return component;\n}\n\nvoid validate(const Graph& graph) {\n    Result\
    \ result = m1une::graph::complement_connected_components(graph);\n    std::vector<int>\
    \ expected = naive_components(graph);\n    assert(int(result.comp.size()) == graph.size());\n\
    \    assert(result.count == int(result.groups.size()));\n\n    std::vector<int>\
    \ occurrence(graph.size(), 0);\n    for (int component = 0; component < result.count;\
    \ component++) {\n        assert(!result.groups[component].empty());\n       \
    \ for (int vertex : result.groups[component]) {\n            assert(0 <= vertex\
    \ && vertex < graph.size());\n            assert(result.comp[vertex] == component);\n\
    \            occurrence[vertex]++;\n        }\n    }\n    for (int vertex = 0;\
    \ vertex < graph.size(); vertex++) {\n        assert(occurrence[vertex] == 1);\n\
    \        for (int other = 0; other < graph.size(); other++) {\n            assert(result.same(vertex,\
    \ other) == (expected[vertex] == expected[other]));\n        }\n    }\n}\n\nvoid\
    \ test_fixed() {\n    validate(Graph());\n    validate(Graph(1));\n\n    Graph\
    \ no_edges(10);\n    validate(no_edges);\n    assert(m1une::graph::complement_connected_components(no_edges).count\
    \ == 1);\n\n    Graph complete(9);\n    for (int first = 0; first < 9; first++)\
    \ {\n        for (int second = first + 1; second < 9; second++) {\n          \
    \  complete.add_edge(first, second);\n        }\n    }\n    validate(complete);\n\
    \    assert(m1une::graph::complement_connected_components(complete).count == 9);\n\
    \n    Graph star(8);\n    for (int vertex = 1; vertex < 8; vertex++) star.add_edge(0,\
    \ vertex);\n    validate(star);\n    assert(m1une::graph::complement_connected_components(star).count\
    \ == 2);\n\n    Graph mixed(5);\n    mixed.add_directed_edge(0, 1);\n    mixed.add_edge(0,\
    \ 1);\n    int inactive = mixed.add_edge(1, 2);\n    mixed.erase_edge(inactive);\n\
    \    mixed.add_edge(3, 3);\n    validate(mixed);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x8cb92baa3f3d8dd7ULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 1000; trial++) {\n       \
    \ const int size = int(random() % 13);\n        Graph graph(size);\n        for\
    \ (int first = 0; first < size; first++) {\n            for (int second = first\
    \ + 1; second < size; second++) {\n                if (random() % 2 == 0) continue;\n\
    \                if (random() & 1) {\n                    graph.add_edge(first,\
    \ second);\n                } else {\n                    graph.add_directed_edge(first,\
    \ second);\n                }\n                if (random() % 11 == 0) graph.add_edge(first,\
    \ second);\n            }\n        }\n        validate(graph);\n    }\n}\n\nvoid\
    \ test_large_sparse_graph() {\n    const int size = 100000;\n    Graph graph(size);\n\
    \    for (int vertex = 1; vertex < size; vertex++) graph.add_edge(vertex - 1,\
    \ vertex);\n    Result result = m1une::graph::complement_connected_components(graph);\n\
    \    assert(result.count == 1);\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n\
    \    test_randomized();\n    test_large_sparse_graph();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int size, edge_count;\n    std::cin >> size\
    \ >> edge_count;\n    Graph graph(size);\n    while (edge_count--) {\n       \
    \ int first, second;\n        std::cin >> first >> second;\n        graph.add_edge(first,\
    \ second);\n    }\n\n    Result result = m1une::graph::complement_connected_components(graph);\n\
    \    std::cout << result.count << '\\n';\n    for (const auto& component : result.groups)\
    \ {\n        std::cout << component.size();\n        for (int vertex : component)\
    \ std::cout << ' ' << vertex;\n        std::cout << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/complement_connected_components.hpp
  - graph/connected_components.hpp
  - ds/dsu/dsu.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/complement_connected_components.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 02:59:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/complement_connected_components.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/complement_connected_components.test.cpp
- /verify/verify/graph/complement_connected_components.test.cpp.html
title: verify/graph/complement_connected_components.test.cpp
---
