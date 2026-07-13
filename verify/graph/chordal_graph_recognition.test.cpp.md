---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/chordal_graph_recognition.hpp
    title: Chordal Graph Recognition
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
    PROBLEM: https://judge.yosupo.jp/problem/chordal_graph_recognition
    links:
    - https://judge.yosupo.jp/problem/chordal_graph_recognition
  bundledCode: "#line 1 \"verify/graph/chordal_graph_recognition.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/chordal_graph_recognition\"\n\n#line\
    \ 1 \"graph/chordal_graph_recognition.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <queue>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type\
    \ = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\
    \n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int\
    \ from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ = true)\n        :\
    \ from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\n    int other(int\
    \ v) const {\n        assert(v == from || v == to);\n        return from ^ to\
    \ ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph {\n    using edge_type\
    \ = Edge<T>;\n    using cost_type = T;\n\n   private:\n    int _n;\n    int _edge_count;\n\
    \    std::vector<std::vector<edge_type>> _g;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _edge_positions;\n\n   public:\n    Graph() : _n(0), _edge_count(0) {}\n\
    \    explicit Graph(int n) : _n(n), _edge_count(0), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int edge_count() const\
    \ {\n        return _edge_count;\n    }\n\n    int add_vertex() {\n        _g.emplace_back();\n\
    \        return _n++;\n    }\n\n    int add_directed_edge(int from, int to, T\
    \ cost = T(1)) {\n        assert(0 <= from && from < _n);\n        assert(0 <=\
    \ to && to < _n);\n        int id = _edge_count++;\n        int idx = int(_g[from].size());\n\
    \        _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
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
    \ m1une\n\n\n#line 11 \"graph/chordal_graph_recognition.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\nstruct ChordalGraphResult {\n    bool is_chordal;\n\
    \    std::vector<int> perfect_elimination_order;\n    std::vector<int> induced_cycle;\n\
    };\n\nnamespace internal {\n\nclass MaximumCardinalitySearch {\n    std::vector<int>\
    \ _head;\n    std::vector<int> _next;\n    std::vector<int> _previous;\n    std::vector<int>\
    \ _weight;\n\n    void erase(int vertex) {\n        const int weight = _weight[vertex];\n\
    \        if (_previous[vertex] == -1) {\n            _head[weight] = _next[vertex];\n\
    \        } else {\n            _next[_previous[vertex]] = _next[vertex];\n   \
    \     }\n        if (_next[vertex] != -1) _previous[_next[vertex]] = _previous[vertex];\n\
    \    }\n\n    void insert(int vertex) {\n        const int weight = _weight[vertex];\n\
    \        _previous[vertex] = -1;\n        _next[vertex] = _head[weight];\n   \
    \     if (_head[weight] != -1) _previous[_head[weight]] = vertex;\n        _head[weight]\
    \ = vertex;\n    }\n\n   public:\n    explicit MaximumCardinalitySearch(int size)\n\
    \        : _head(size + 1, -1),\n          _next(size, -1),\n          _previous(size,\
    \ -1),\n          _weight(size, 0) {\n        for (int vertex = 0; vertex < size;\
    \ vertex++) insert(vertex);\n    }\n\n    std::vector<int> run(const std::vector<std::vector<int>>&\
    \ adjacency) {\n        const int size = int(adjacency.size());\n        std::vector<int>\
    \ order;\n        order.reserve(size);\n        std::vector<char> selected(size,\
    \ false);\n        std::vector<int> seen_neighbor(size, -1);\n        int maximum_weight\
    \ = 0;\n\n        while (int(order.size()) < size) {\n            while (_head[maximum_weight]\
    \ == -1) maximum_weight--;\n            const int vertex = _head[maximum_weight];\n\
    \            erase(vertex);\n            selected[vertex] = true;\n          \
    \  order.push_back(vertex);\n\n            for (int to : adjacency[vertex]) {\n\
    \                if (to == vertex || selected[to] || seen_neighbor[to] == vertex)\
    \ continue;\n                seen_neighbor[to] = vertex;\n                erase(to);\n\
    \                _weight[to]++;\n                insert(to);\n               \
    \ maximum_weight = std::max(maximum_weight, _weight[to]);\n            }\n   \
    \     }\n        return order;\n    }\n};\n\ninline std::vector<int> chordless_cycle(\n\
    \    const std::vector<std::vector<int>>& adjacency, int vertex, int first,\n\
    \    int second\n) {\n    const int size = int(adjacency.size());\n    std::vector<char>\
    \ forbidden(size, false);\n    for (int to : adjacency[vertex]) forbidden[to]\
    \ = true;\n    forbidden[vertex] = true;\n    forbidden[first] = false;\n    forbidden[second]\
    \ = false;\n\n    std::vector<int> parent(size, -1);\n    std::queue<int> queue;\n\
    \    parent[first] = first;\n    queue.push(first);\n    while (!queue.empty()\
    \ && parent[second] == -1) {\n        const int current = queue.front();\n   \
    \     queue.pop();\n        for (int to : adjacency[current]) {\n            if\
    \ (forbidden[to] || parent[to] != -1) continue;\n            parent[to] = current;\n\
    \            queue.push(to);\n        }\n    }\n    assert(parent[second] != -1);\n\
    \n    std::vector<int> path;\n    for (int current = second; current != first;\
    \ current = parent[current]) {\n        path.push_back(current);\n    }\n    path.push_back(first);\n\
    \    std::reverse(path.begin(), path.end());\n\n    std::vector<int> cycle;\n\
    \    cycle.reserve(path.size() + 1);\n    cycle.push_back(vertex);\n    cycle.insert(cycle.end(),\
    \ path.begin(), path.end());\n    return cycle;\n}\n\n}  // namespace internal\n\
    \n// Recognizes a chordal graph. On success, returns a perfect elimination\n//\
    \ ordering; on failure, returns an induced cycle of length at least four.\ntemplate\
    \ <class T>\nChordalGraphResult chordal_graph_recognition(const Graph<T>& graph)\
    \ {\n    const int size = graph.size();\n    std::vector<std::vector<int>> adjacency(size);\n\
    \    for (const Edge<T>& edge : graph.edges()) {\n        if (edge.from == edge.to)\
    \ continue;\n        adjacency[edge.from].push_back(edge.to);\n        adjacency[edge.to].push_back(edge.from);\n\
    \    }\n\n    std::vector<int> order = internal::MaximumCardinalitySearch(size).run(adjacency);\n\
    \    std::vector<int> position(size);\n    for (int index = 0; index < size; index++)\
    \ position[order[index]] = index;\n\n    std::vector<int> parent(size, -1);\n\
    \    std::vector<std::vector<int>> children(size);\n    for (int vertex = 0; vertex\
    \ < size; vertex++) {\n        for (int to : adjacency[vertex]) {\n          \
    \  if (position[to] < position[vertex] &&\n                (parent[vertex] ==\
    \ -1 || position[parent[vertex]] < position[to])) {\n                parent[vertex]\
    \ = to;\n            }\n        }\n        if (parent[vertex] != -1) children[parent[vertex]].push_back(vertex);\n\
    \    }\n\n    std::vector<int> adjacent_stamp(size, -1);\n    for (int center\
    \ = 0; center < size; center++) {\n        for (int to : adjacency[center]) adjacent_stamp[to]\
    \ = center;\n        for (int vertex : children[center]) {\n            for (int\
    \ to : adjacency[vertex]) {\n                if (position[to] >= position[center]\
    \ || adjacent_stamp[to] == center) continue;\n                return ChordalGraphResult{\n\
    \                    false,\n                    {},\n                    internal::chordless_cycle(adjacency,\
    \ vertex, to, center),\n                };\n            }\n        }\n    }\n\n\
    \    std::reverse(order.begin(), order.end());\n    return ChordalGraphResult{true,\
    \ std::move(order), {}};\n}\n\ntemplate <class T>\nbool is_chordal(const Graph<T>&\
    \ graph) {\n    return chordal_graph_recognition(graph).is_chordal;\n}\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n\n#line 4 \"verify/graph/chordal_graph_recognition.test.cpp\"\
    \n\n#line 6 \"verify/graph/chordal_graph_recognition.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#line 9 \"verify/graph/chordal_graph_recognition.test.cpp\"\
    \n\nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\nusing Result = m1une::graph::ChordalGraphResult;\n\
    \nstd::vector<std::vector<char>> adjacency_matrix(const Graph& graph) {\n    const\
    \ int size = graph.size();\n    std::vector<std::vector<char>> adjacent(size,\
    \ std::vector<char>(size, false));\n    for (const auto& edge : graph.edges())\
    \ {\n        if (edge.from == edge.to) continue;\n        adjacent[edge.from][edge.to]\
    \ = true;\n        adjacent[edge.to][edge.from] = true;\n    }\n    return adjacent;\n\
    }\n\nvoid validate(const Graph& graph) {\n    const int size = graph.size();\n\
    \    const auto adjacent = adjacency_matrix(graph);\n    Result result = m1une::graph::chordal_graph_recognition(graph);\n\
    \    assert(m1une::graph::is_chordal(graph) == result.is_chordal);\n\n    if (result.is_chordal)\
    \ {\n        assert(result.induced_cycle.empty());\n        assert(int(result.perfect_elimination_order.size())\
    \ == size);\n        std::vector<int> position(size, -1);\n        for (int index\
    \ = 0; index < size; index++) {\n            int vertex = result.perfect_elimination_order[index];\n\
    \            assert(0 <= vertex && vertex < size);\n            assert(position[vertex]\
    \ == -1);\n            position[vertex] = index;\n        }\n        for (int\
    \ vertex = 0; vertex < size; vertex++) {\n            std::vector<int> later_neighbors;\n\
    \            for (int to = 0; to < size; to++) {\n                if (adjacent[vertex][to]\
    \ && position[vertex] < position[to]) {\n                    later_neighbors.push_back(to);\n\
    \                }\n            }\n            for (int first : later_neighbors)\
    \ {\n                for (int second : later_neighbors) {\n                  \
    \  if (first != second) assert(adjacent[first][second]);\n                }\n\
    \            }\n        }\n        return;\n    }\n\n    assert(result.perfect_elimination_order.empty());\n\
    \    const int cycle_size = int(result.induced_cycle.size());\n    assert(cycle_size\
    \ >= 4);\n    std::vector<char> used(size, false);\n    for (int index = 0; index\
    \ < cycle_size; index++) {\n        const int vertex = result.induced_cycle[index];\n\
    \        assert(0 <= vertex && vertex < size);\n        assert(!used[vertex]);\n\
    \        used[vertex] = true;\n        for (int other = index + 1; other < cycle_size;\
    \ other++) {\n            const int distance = other - index;\n            const\
    \ bool consecutive = distance == 1 || distance == cycle_size - 1;\n          \
    \  assert(bool(adjacent[vertex][result.induced_cycle[other]]) == consecutive);\n\
    \        }\n    }\n}\n\nvoid test_fixed() {\n    validate(Graph());\n    validate(Graph(1));\n\
    \n    Graph tree(8);\n    for (int vertex = 1; vertex < 8; vertex++) tree.add_edge(vertex\
    \ / 2, vertex);\n    validate(tree);\n    assert(m1une::graph::is_chordal(tree));\n\
    \n    Graph complete(9);\n    for (int first = 0; first < 9; first++) {\n    \
    \    for (int second = first + 1; second < 9; second++) {\n            complete.add_edge(first,\
    \ second);\n        }\n    }\n    validate(complete);\n\n    for (int size = 4;\
    \ size <= 12; size++) {\n        Graph cycle(size);\n        for (int vertex =\
    \ 0; vertex < size; vertex++) {\n            cycle.add_edge(vertex, (vertex +\
    \ 1) % size);\n        }\n        validate(cycle);\n        assert(!m1une::graph::is_chordal(cycle));\n\
    \    }\n\n    Graph parallel(4);\n    parallel.add_edge(0, 1);\n    parallel.add_edge(0,\
    \ 1);\n    parallel.add_directed_edge(1, 2);\n    int inactive = parallel.add_edge(0,\
    \ 2);\n    parallel.erase_edge(inactive);\n    parallel.add_edge(2, 3);\n    validate(parallel);\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 0xd1b54a32d192ed03ULL;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 1000;\
    \ trial++) {\n        const int size = int(random() % 11);\n        Graph graph(size);\n\
    \        for (int first = 0; first < size; first++) {\n            for (int second\
    \ = first + 1; second < size; second++) {\n                if (random() % 3 ==\
    \ 0) continue;\n                if (random() & 1) {\n                    graph.add_edge(first,\
    \ second);\n                } else {\n                    graph.add_directed_edge(first,\
    \ second);\n                }\n                if (random() % 13 == 0) graph.add_edge(first,\
    \ second);\n            }\n        }\n        validate(graph);\n    }\n}\n\nvoid\
    \ test_deep_graph() {\n    const int size = 50000;\n    Graph graph(size);\n \
    \   for (int vertex = 1; vertex < size; vertex++) graph.add_edge(vertex - 1, vertex);\n\
    \    Result result = m1une::graph::chordal_graph_recognition(graph);\n    assert(result.is_chordal);\n\
    \    assert(int(result.perfect_elimination_order.size()) == size);\n}\n\n}  //\
    \ namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n    test_deep_graph();\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ size, edge_count;\n    std::cin >> size >> edge_count;\n    Graph graph(size);\n\
    \    while (edge_count--) {\n        int first, second;\n        std::cin >> first\
    \ >> second;\n        graph.add_edge(first, second);\n    }\n\n    Result result\
    \ = m1une::graph::chordal_graph_recognition(graph);\n    if (result.is_chordal)\
    \ {\n        std::cout << \"YES\\n\";\n        for (int index = 0; index < size;\
    \ index++) {\n            if (index != 0) std::cout << ' ';\n            std::cout\
    \ << result.perfect_elimination_order[index];\n        }\n        std::cout <<\
    \ '\\n';\n    } else {\n        std::cout << \"NO\\n\" << result.induced_cycle.size()\
    \ << '\\n';\n        for (int index = 0; index < int(result.induced_cycle.size());\
    \ index++) {\n            if (index != 0) std::cout << ' ';\n            std::cout\
    \ << result.induced_cycle[index];\n        }\n        std::cout << '\\n';\n  \
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/chordal_graph_recognition\"\
    \n\n#include \"../../graph/chordal_graph_recognition.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <vector>\n\nnamespace {\n\n\
    using Graph = m1une::graph::Graph<>;\nusing Result = m1une::graph::ChordalGraphResult;\n\
    \nstd::vector<std::vector<char>> adjacency_matrix(const Graph& graph) {\n    const\
    \ int size = graph.size();\n    std::vector<std::vector<char>> adjacent(size,\
    \ std::vector<char>(size, false));\n    for (const auto& edge : graph.edges())\
    \ {\n        if (edge.from == edge.to) continue;\n        adjacent[edge.from][edge.to]\
    \ = true;\n        adjacent[edge.to][edge.from] = true;\n    }\n    return adjacent;\n\
    }\n\nvoid validate(const Graph& graph) {\n    const int size = graph.size();\n\
    \    const auto adjacent = adjacency_matrix(graph);\n    Result result = m1une::graph::chordal_graph_recognition(graph);\n\
    \    assert(m1une::graph::is_chordal(graph) == result.is_chordal);\n\n    if (result.is_chordal)\
    \ {\n        assert(result.induced_cycle.empty());\n        assert(int(result.perfect_elimination_order.size())\
    \ == size);\n        std::vector<int> position(size, -1);\n        for (int index\
    \ = 0; index < size; index++) {\n            int vertex = result.perfect_elimination_order[index];\n\
    \            assert(0 <= vertex && vertex < size);\n            assert(position[vertex]\
    \ == -1);\n            position[vertex] = index;\n        }\n        for (int\
    \ vertex = 0; vertex < size; vertex++) {\n            std::vector<int> later_neighbors;\n\
    \            for (int to = 0; to < size; to++) {\n                if (adjacent[vertex][to]\
    \ && position[vertex] < position[to]) {\n                    later_neighbors.push_back(to);\n\
    \                }\n            }\n            for (int first : later_neighbors)\
    \ {\n                for (int second : later_neighbors) {\n                  \
    \  if (first != second) assert(adjacent[first][second]);\n                }\n\
    \            }\n        }\n        return;\n    }\n\n    assert(result.perfect_elimination_order.empty());\n\
    \    const int cycle_size = int(result.induced_cycle.size());\n    assert(cycle_size\
    \ >= 4);\n    std::vector<char> used(size, false);\n    for (int index = 0; index\
    \ < cycle_size; index++) {\n        const int vertex = result.induced_cycle[index];\n\
    \        assert(0 <= vertex && vertex < size);\n        assert(!used[vertex]);\n\
    \        used[vertex] = true;\n        for (int other = index + 1; other < cycle_size;\
    \ other++) {\n            const int distance = other - index;\n            const\
    \ bool consecutive = distance == 1 || distance == cycle_size - 1;\n          \
    \  assert(bool(adjacent[vertex][result.induced_cycle[other]]) == consecutive);\n\
    \        }\n    }\n}\n\nvoid test_fixed() {\n    validate(Graph());\n    validate(Graph(1));\n\
    \n    Graph tree(8);\n    for (int vertex = 1; vertex < 8; vertex++) tree.add_edge(vertex\
    \ / 2, vertex);\n    validate(tree);\n    assert(m1une::graph::is_chordal(tree));\n\
    \n    Graph complete(9);\n    for (int first = 0; first < 9; first++) {\n    \
    \    for (int second = first + 1; second < 9; second++) {\n            complete.add_edge(first,\
    \ second);\n        }\n    }\n    validate(complete);\n\n    for (int size = 4;\
    \ size <= 12; size++) {\n        Graph cycle(size);\n        for (int vertex =\
    \ 0; vertex < size; vertex++) {\n            cycle.add_edge(vertex, (vertex +\
    \ 1) % size);\n        }\n        validate(cycle);\n        assert(!m1une::graph::is_chordal(cycle));\n\
    \    }\n\n    Graph parallel(4);\n    parallel.add_edge(0, 1);\n    parallel.add_edge(0,\
    \ 1);\n    parallel.add_directed_edge(1, 2);\n    int inactive = parallel.add_edge(0,\
    \ 2);\n    parallel.erase_edge(inactive);\n    parallel.add_edge(2, 3);\n    validate(parallel);\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 0xd1b54a32d192ed03ULL;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 1000;\
    \ trial++) {\n        const int size = int(random() % 11);\n        Graph graph(size);\n\
    \        for (int first = 0; first < size; first++) {\n            for (int second\
    \ = first + 1; second < size; second++) {\n                if (random() % 3 ==\
    \ 0) continue;\n                if (random() & 1) {\n                    graph.add_edge(first,\
    \ second);\n                } else {\n                    graph.add_directed_edge(first,\
    \ second);\n                }\n                if (random() % 13 == 0) graph.add_edge(first,\
    \ second);\n            }\n        }\n        validate(graph);\n    }\n}\n\nvoid\
    \ test_deep_graph() {\n    const int size = 50000;\n    Graph graph(size);\n \
    \   for (int vertex = 1; vertex < size; vertex++) graph.add_edge(vertex - 1, vertex);\n\
    \    Result result = m1une::graph::chordal_graph_recognition(graph);\n    assert(result.is_chordal);\n\
    \    assert(int(result.perfect_elimination_order.size()) == size);\n}\n\n}  //\
    \ namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n    test_deep_graph();\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ size, edge_count;\n    std::cin >> size >> edge_count;\n    Graph graph(size);\n\
    \    while (edge_count--) {\n        int first, second;\n        std::cin >> first\
    \ >> second;\n        graph.add_edge(first, second);\n    }\n\n    Result result\
    \ = m1une::graph::chordal_graph_recognition(graph);\n    if (result.is_chordal)\
    \ {\n        std::cout << \"YES\\n\";\n        for (int index = 0; index < size;\
    \ index++) {\n            if (index != 0) std::cout << ' ';\n            std::cout\
    \ << result.perfect_elimination_order[index];\n        }\n        std::cout <<\
    \ '\\n';\n    } else {\n        std::cout << \"NO\\n\" << result.induced_cycle.size()\
    \ << '\\n';\n        for (int index = 0; index < int(result.induced_cycle.size());\
    \ index++) {\n            if (index != 0) std::cout << ' ';\n            std::cout\
    \ << result.induced_cycle[index];\n        }\n        std::cout << '\\n';\n  \
    \  }\n}\n"
  dependsOn:
  - graph/chordal_graph_recognition.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/chordal_graph_recognition.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 02:59:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/chordal_graph_recognition.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/chordal_graph_recognition.test.cpp
- /verify/verify/graph/chordal_graph_recognition.test.cpp.html
title: verify/graph/chordal_graph_recognition.test.cpp
---
