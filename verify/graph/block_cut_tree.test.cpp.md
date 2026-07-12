---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/biconnected_components.hpp
    title: Biconnected Components
  - icon: ':question:'
    path: graph/block_cut_tree.hpp
    title: Block-Cut Tree
  - icon: ':question:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/biconnected_components
    links:
    - https://judge.yosupo.jp/problem/biconnected_components
  bundledCode: "#line 1 \"verify/graph/block_cut_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/biconnected_components\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <random>\n#include <vector>\n\
    \n#line 1 \"graph/block_cut_tree.hpp\"\n\n\n\n#line 6 \"graph/block_cut_tree.hpp\"\
    \n\n#line 1 \"graph/biconnected_components.hpp\"\n\n\n\n#line 6 \"graph/biconnected_components.hpp\"\
    \n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 5 \"graph/graph.hpp\"\n#include <utility>\n\
    #line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate\
    \ <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
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
    \ m1une\n\n\n#line 8 \"graph/biconnected_components.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nstruct BiconnectedComponentsResult {\n    std::vector<std::vector<int>>\
    \ components;\n    std::vector<std::vector<int>> edge_components;\n    std::vector<int>\
    \ component_of_edge;\n    std::vector<std::vector<int>> vertex_components;\n \
    \   std::vector<int> articulation;\n    std::vector<int> ord;\n    std::vector<int>\
    \ low;\n\n    int component_count() const {\n        return int(components.size());\n\
    \    }\n\n    bool is_articulation(int vertex) const {\n        assert(0 <= vertex\
    \ && vertex < int(vertex_components.size()));\n        return vertex_components[vertex].size()\
    \ >= 2;\n    }\n};\n\n// Decomposes an undirected graph into maximal vertex-biconnected\
    \ blocks.\n// Every active edge belongs to exactly one block. Isolated vertices\
    \ form\n// singleton blocks, and articulation vertices occur in multiple blocks.\n\
    template <class T>\nBiconnectedComponentsResult biconnected_components(const Graph<T>&\
    \ graph) {\n    const int n = graph.size();\n    const int edge_count = graph.edge_count();\n\
    \n    BiconnectedComponentsResult result;\n    result.component_of_edge.assign(edge_count,\
    \ -1);\n    result.vertex_components.assign(n, {});\n    result.ord.assign(n,\
    \ -1);\n    result.low.assign(n, -1);\n\n    std::vector<int> edge_from(edge_count,\
    \ -1);\n    std::vector<int> edge_to(edge_count, -1);\n    std::vector<int> incidence_count(edge_count,\
    \ 0);\n    std::vector<int> alive_degree(n, 0);\n    for (int vertex = 0; vertex\
    \ < n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex]) {\n    \
    \        if (!edge.alive) continue;\n            assert(0 <= edge.id && edge.id\
    \ < edge_count);\n            alive_degree[vertex]++;\n            if (incidence_count[edge.id]\
    \ == 0) {\n                edge_from[edge.id] = edge.from;\n                edge_to[edge.id]\
    \ = edge.to;\n            }\n            incidence_count[edge.id]++;\n       \
    \ }\n    }\n#ifndef NDEBUG\n    for (int edge_id = 0; edge_id < edge_count; edge_id++)\
    \ {\n        if (incidence_count[edge_id] == 0) continue;\n        assert(incidence_count[edge_id]\
    \ == 2);\n        assert(edge_from[edge_id] != edge_to[edge_id]);\n    }\n#endif\n\
    \n    std::vector<int> parent(n, -1);\n    std::vector<int> parent_edge(n, -1);\n\
    \    std::vector<int> next_edge(n, 0);\n    std::vector<int> dfs_stack;\n    std::vector<int>\
    \ edge_stack;\n    std::vector<int> vertex_mark(n, -1);\n    int timer = 0;\n\n\
    \    auto add_singleton = [&](int vertex) {\n        const int component = result.component_count();\n\
    \        result.components.push_back(std::vector<int>(1, vertex));\n        result.edge_components.emplace_back();\n\
    \        result.vertex_components[vertex].push_back(component);\n    };\n\n  \
    \  auto extract_component = [&](int stopping_edge) {\n        const int component\
    \ = result.component_count();\n        result.components.emplace_back();\n   \
    \     result.edge_components.emplace_back();\n        std::vector<int>& vertices\
    \ = result.components.back();\n        std::vector<int>& edges = result.edge_components.back();\n\
    \n        while (true) {\n            assert(!edge_stack.empty());\n         \
    \   const int edge_id = edge_stack.back();\n            edge_stack.pop_back();\n\
    \            edges.push_back(edge_id);\n            result.component_of_edge[edge_id]\
    \ = component;\n\n            const int endpoints[2] = {edge_from[edge_id], edge_to[edge_id]};\n\
    \            for (int vertex : endpoints) {\n                if (vertex_mark[vertex]\
    \ == component) continue;\n                vertex_mark[vertex] = component;\n\
    \                vertices.push_back(vertex);\n            }\n            if (edge_id\
    \ == stopping_edge) break;\n        }\n        for (int vertex : vertices) {\n\
    \            result.vertex_components[vertex].push_back(component);\n        }\n\
    \    };\n\n    for (int root = 0; root < n; root++) {\n        if (result.ord[root]\
    \ != -1) continue;\n        if (alive_degree[root] == 0) {\n            result.ord[root]\
    \ = result.low[root] = timer++;\n            add_singleton(root);\n          \
    \  continue;\n        }\n\n        result.ord[root] = result.low[root] = timer++;\n\
    \        dfs_stack.push_back(root);\n        while (!dfs_stack.empty()) {\n  \
    \          const int vertex = dfs_stack.back();\n            if (next_edge[vertex]\
    \ < int(graph[vertex].size())) {\n                const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n\
    \                if (!edge.alive || edge.id == parent_edge[vertex]) continue;\n\
    \                const int to = edge.to;\n                if (result.ord[to] ==\
    \ -1) {\n                    parent[to] = vertex;\n                    parent_edge[to]\
    \ = edge.id;\n                    edge_stack.push_back(edge.id);\n           \
    \         result.ord[to] = result.low[to] = timer++;\n                    dfs_stack.push_back(to);\n\
    \                } else if (result.ord[to] < result.ord[vertex]) {\n         \
    \           edge_stack.push_back(edge.id);\n                    if (result.ord[to]\
    \ < result.low[vertex]) {\n                        result.low[vertex] = result.ord[to];\n\
    \                    }\n                }\n                continue;\n       \
    \     }\n\n            dfs_stack.pop_back();\n            const int parent_vertex\
    \ = parent[vertex];\n            if (parent_vertex == -1) {\n                assert(edge_stack.empty());\n\
    \                continue;\n            }\n            if (result.low[vertex]\
    \ < result.low[parent_vertex]) {\n                result.low[parent_vertex] =\
    \ result.low[vertex];\n            }\n            if (result.ord[parent_vertex]\
    \ <= result.low[vertex]) {\n                extract_component(parent_edge[vertex]);\n\
    \            }\n        }\n    }\n\n    for (int vertex = 0; vertex < n; vertex++)\
    \ {\n        if (result.is_articulation(vertex)) result.articulation.push_back(vertex);\n\
    \    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 8 \"graph/block_cut_tree.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct BlockCutTreeResult {\n    std::vector<std::vector<int>> forest;\n\
    \    std::vector<int> node_of_block;\n    std::vector<int> node_of_articulation;\n\
    \    std::vector<int> node_of_vertex;\n    std::vector<int> block_of_node;\n \
    \   std::vector<int> articulation_of_node;\n\n    int node_count() const {\n \
    \       return int(forest.size());\n    }\n\n    int block_count() const {\n \
    \       return int(node_of_block.size());\n    }\n\n    bool is_block_node(int\
    \ node) const {\n        assert(0 <= node && node < node_count());\n        return\
    \ block_of_node[node] != -1;\n    }\n\n    bool is_articulation_node(int node)\
    \ const {\n        assert(0 <= node && node < node_count());\n        return articulation_of_node[node]\
    \ != -1;\n    }\n};\n\n// Builds the block-cut forest of a biconnected-components\
    \ decomposition.\n// Block nodes have IDs [0, block_count); articulation nodes\
    \ follow them.\ninline BlockCutTreeResult block_cut_tree(\n    const BiconnectedComponentsResult&\
    \ biconnected\n) {\n    const int vertex_count = int(biconnected.vertex_components.size());\n\
    \    const int block_count = biconnected.component_count();\n\n    BlockCutTreeResult\
    \ result;\n    result.node_of_block.resize(block_count);\n    result.node_of_articulation.assign(vertex_count,\
    \ -1);\n    result.node_of_vertex.assign(vertex_count, -1);\n    result.forest.resize(block_count);\n\
    \    result.block_of_node.resize(block_count);\n    result.articulation_of_node.assign(block_count,\
    \ -1);\n    for (int block = 0; block < block_count; block++) {\n        result.node_of_block[block]\
    \ = block;\n        result.block_of_node[block] = block;\n    }\n\n    for (int\
    \ vertex = 0; vertex < vertex_count; vertex++) {\n        const std::vector<int>&\
    \ blocks = biconnected.vertex_components[vertex];\n        assert(!blocks.empty());\n\
    \        if (blocks.size() == 1) {\n            assert(0 <= blocks[0] && blocks[0]\
    \ < block_count);\n            result.node_of_vertex[vertex] = result.node_of_block[blocks[0]];\n\
    \            continue;\n        }\n\n        const int node = result.node_count();\n\
    \        result.node_of_articulation[vertex] = node;\n        result.node_of_vertex[vertex]\
    \ = node;\n        result.forest.emplace_back();\n        result.block_of_node.push_back(-1);\n\
    \        result.articulation_of_node.push_back(vertex);\n        for (int block\
    \ : blocks) {\n            assert(0 <= block && block < block_count);\n      \
    \      const int block_node = result.node_of_block[block];\n            result.forest[node].push_back(block_node);\n\
    \            result.forest[block_node].push_back(node);\n        }\n    }\n  \
    \  return result;\n}\n\ntemplate <class T>\nBlockCutTreeResult block_cut_tree(const\
    \ Graph<T>& graph) {\n    return block_cut_tree(biconnected_components(graph));\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 10 \"verify/graph/block_cut_tree.test.cpp\"\
    \n\nnamespace {\n\n#ifndef NDEBUG\nvoid verify_block_cut_tree(const m1une::graph::BiconnectedComponentsResult&\
    \ bcc) {\n    const auto actual = m1une::graph::block_cut_tree(bcc);\n    const\
    \ int n = int(bcc.vertex_components.size());\n    const int block_count = bcc.component_count();\n\
    \    assert(actual.block_count() == block_count);\n    assert(actual.node_count()\
    \ == block_count + int(bcc.articulation.size()));\n\n    int degree_sum = 0;\n\
    \    for (int node = 0; node < actual.node_count(); node++) {\n        assert(actual.is_block_node(node)\
    \ != actual.is_articulation_node(node));\n        degree_sum += int(actual.forest[node].size());\n\
    \        for (int to : actual.forest[node]) {\n            assert(0 <= to && to\
    \ < actual.node_count());\n            assert(actual.is_block_node(node) != actual.is_block_node(to));\n\
    \            assert(std::count(actual.forest[to].begin(), actual.forest[to].end(),\
    \ node) == 1);\n        }\n    }\n\n    int incidence_count = 0;\n    for (int\
    \ vertex = 0; vertex < n; vertex++) {\n        const bool articulation = bcc.is_articulation(vertex);\n\
    \        const int node = actual.node_of_vertex[vertex];\n        assert(0 <=\
    \ node && node < actual.node_count());\n        if (articulation) {\n        \
    \    assert(actual.node_of_articulation[vertex] == node);\n            assert(actual.articulation_of_node[node]\
    \ == vertex);\n            assert(actual.forest[node].size() == bcc.vertex_components[vertex].size());\n\
    \            for (int block : bcc.vertex_components[vertex]) {\n             \
    \   assert(std::count(actual.forest[node].begin(), actual.forest[node].end(),\
    \ block) == 1);\n                incidence_count++;\n            }\n        }\
    \ else {\n            assert(actual.node_of_articulation[vertex] == -1);\n   \
    \         assert(bcc.vertex_components[vertex].size() == 1);\n            assert(node\
    \ == actual.node_of_block[bcc.vertex_components[vertex][0]]);\n        }\n   \
    \ }\n    assert(degree_sum == 2 * incidence_count);\n\n    std::vector<int> parent(actual.node_count(),\
    \ -1);\n    std::vector<int> stack;\n    for (int root = 0; root < actual.node_count();\
    \ root++) {\n        if (parent[root] != -1) continue;\n        parent[root] =\
    \ root;\n        stack.push_back(root);\n        while (!stack.empty()) {\n  \
    \          const int node = stack.back();\n            stack.pop_back();\n   \
    \         for (int to : actual.forest[node]) {\n                if (to == parent[node])\
    \ continue;\n                assert(parent[to] == -1);\n                parent[to]\
    \ = node;\n                stack.push_back(to);\n            }\n        }\n  \
    \  }\n}\n\nvoid randomized_test() {\n    m1une::graph::Graph<> empty_graph(0);\n\
    \    verify_block_cut_tree(m1une::graph::biconnected_components(empty_graph));\n\
    \n    m1une::graph::Graph<> inactive_graph(3);\n    int erased = inactive_graph.add_edge(0,\
    \ 1);\n    inactive_graph.erase_edge(erased);\n    verify_block_cut_tree(m1une::graph::biconnected_components(inactive_graph));\n\
    \n    std::mt19937 random(294631);\n    for (int iteration = 0; iteration < 500;\
    \ iteration++) {\n        const int n = 1 + int(random() % 20);\n        m1une::graph::Graph<>\
    \ graph(n);\n        for (int first = 0; first < n; first++) {\n            for\
    \ (int second = first + 1; second < n; second++) {\n                if (random()\
    \ % 6 == 0) graph.add_edge(first, second);\n            }\n        }\n       \
    \ if (n >= 2 && random() % 2 == 0) {\n            graph.add_edge(0, 1);\n    \
    \        graph.add_edge(0, 1);\n        }\n        auto bcc = m1une::graph::biconnected_components(graph);\n\
    \        verify_block_cut_tree(bcc);\n        const auto from_graph = m1une::graph::block_cut_tree(graph);\n\
    \        const auto from_bcc = m1une::graph::block_cut_tree(bcc);\n        assert(from_graph.forest\
    \ == from_bcc.forest);\n        assert(from_graph.node_of_vertex == from_bcc.node_of_vertex);\n\
    \    }\n}\n#endif\n\n}  // namespace\n\nint main() {\n#ifndef NDEBUG\n    randomized_test();\n\
    #endif\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n\
    \    int vertex_count, edge_count;\n    std::cin >> vertex_count >> edge_count;\n\
    \    m1une::graph::Graph<> graph(vertex_count);\n    for (int i = 0; i < edge_count;\
    \ i++) {\n        int first, second;\n        std::cin >> first >> second;\n \
    \       graph.add_edge(first, second);\n    }\n\n    auto bcc = m1une::graph::biconnected_components(graph);\n\
    #ifndef NDEBUG\n    verify_block_cut_tree(bcc);\n#endif\n    std::cout << bcc.component_count()\
    \ << '\\n';\n    for (const std::vector<int>& component : bcc.components) {\n\
    \        std::cout << component.size();\n        for (int vertex : component)\
    \ std::cout << ' ' << vertex;\n        std::cout << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/biconnected_components\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <random>\n\
    #include <vector>\n\n#include \"../../graph/block_cut_tree.hpp\"\n\nnamespace\
    \ {\n\n#ifndef NDEBUG\nvoid verify_block_cut_tree(const m1une::graph::BiconnectedComponentsResult&\
    \ bcc) {\n    const auto actual = m1une::graph::block_cut_tree(bcc);\n    const\
    \ int n = int(bcc.vertex_components.size());\n    const int block_count = bcc.component_count();\n\
    \    assert(actual.block_count() == block_count);\n    assert(actual.node_count()\
    \ == block_count + int(bcc.articulation.size()));\n\n    int degree_sum = 0;\n\
    \    for (int node = 0; node < actual.node_count(); node++) {\n        assert(actual.is_block_node(node)\
    \ != actual.is_articulation_node(node));\n        degree_sum += int(actual.forest[node].size());\n\
    \        for (int to : actual.forest[node]) {\n            assert(0 <= to && to\
    \ < actual.node_count());\n            assert(actual.is_block_node(node) != actual.is_block_node(to));\n\
    \            assert(std::count(actual.forest[to].begin(), actual.forest[to].end(),\
    \ node) == 1);\n        }\n    }\n\n    int incidence_count = 0;\n    for (int\
    \ vertex = 0; vertex < n; vertex++) {\n        const bool articulation = bcc.is_articulation(vertex);\n\
    \        const int node = actual.node_of_vertex[vertex];\n        assert(0 <=\
    \ node && node < actual.node_count());\n        if (articulation) {\n        \
    \    assert(actual.node_of_articulation[vertex] == node);\n            assert(actual.articulation_of_node[node]\
    \ == vertex);\n            assert(actual.forest[node].size() == bcc.vertex_components[vertex].size());\n\
    \            for (int block : bcc.vertex_components[vertex]) {\n             \
    \   assert(std::count(actual.forest[node].begin(), actual.forest[node].end(),\
    \ block) == 1);\n                incidence_count++;\n            }\n        }\
    \ else {\n            assert(actual.node_of_articulation[vertex] == -1);\n   \
    \         assert(bcc.vertex_components[vertex].size() == 1);\n            assert(node\
    \ == actual.node_of_block[bcc.vertex_components[vertex][0]]);\n        }\n   \
    \ }\n    assert(degree_sum == 2 * incidence_count);\n\n    std::vector<int> parent(actual.node_count(),\
    \ -1);\n    std::vector<int> stack;\n    for (int root = 0; root < actual.node_count();\
    \ root++) {\n        if (parent[root] != -1) continue;\n        parent[root] =\
    \ root;\n        stack.push_back(root);\n        while (!stack.empty()) {\n  \
    \          const int node = stack.back();\n            stack.pop_back();\n   \
    \         for (int to : actual.forest[node]) {\n                if (to == parent[node])\
    \ continue;\n                assert(parent[to] == -1);\n                parent[to]\
    \ = node;\n                stack.push_back(to);\n            }\n        }\n  \
    \  }\n}\n\nvoid randomized_test() {\n    m1une::graph::Graph<> empty_graph(0);\n\
    \    verify_block_cut_tree(m1une::graph::biconnected_components(empty_graph));\n\
    \n    m1une::graph::Graph<> inactive_graph(3);\n    int erased = inactive_graph.add_edge(0,\
    \ 1);\n    inactive_graph.erase_edge(erased);\n    verify_block_cut_tree(m1une::graph::biconnected_components(inactive_graph));\n\
    \n    std::mt19937 random(294631);\n    for (int iteration = 0; iteration < 500;\
    \ iteration++) {\n        const int n = 1 + int(random() % 20);\n        m1une::graph::Graph<>\
    \ graph(n);\n        for (int first = 0; first < n; first++) {\n            for\
    \ (int second = first + 1; second < n; second++) {\n                if (random()\
    \ % 6 == 0) graph.add_edge(first, second);\n            }\n        }\n       \
    \ if (n >= 2 && random() % 2 == 0) {\n            graph.add_edge(0, 1);\n    \
    \        graph.add_edge(0, 1);\n        }\n        auto bcc = m1une::graph::biconnected_components(graph);\n\
    \        verify_block_cut_tree(bcc);\n        const auto from_graph = m1une::graph::block_cut_tree(graph);\n\
    \        const auto from_bcc = m1une::graph::block_cut_tree(bcc);\n        assert(from_graph.forest\
    \ == from_bcc.forest);\n        assert(from_graph.node_of_vertex == from_bcc.node_of_vertex);\n\
    \    }\n}\n#endif\n\n}  // namespace\n\nint main() {\n#ifndef NDEBUG\n    randomized_test();\n\
    #endif\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n\
    \    int vertex_count, edge_count;\n    std::cin >> vertex_count >> edge_count;\n\
    \    m1une::graph::Graph<> graph(vertex_count);\n    for (int i = 0; i < edge_count;\
    \ i++) {\n        int first, second;\n        std::cin >> first >> second;\n \
    \       graph.add_edge(first, second);\n    }\n\n    auto bcc = m1une::graph::biconnected_components(graph);\n\
    #ifndef NDEBUG\n    verify_block_cut_tree(bcc);\n#endif\n    std::cout << bcc.component_count()\
    \ << '\\n';\n    for (const std::vector<int>& component : bcc.components) {\n\
    \        std::cout << component.size();\n        for (int vertex : component)\
    \ std::cout << ' ' << vertex;\n        std::cout << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/block_cut_tree.hpp
  - graph/biconnected_components.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/block_cut_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 03:42:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/graph/block_cut_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/block_cut_tree.test.cpp
- /verify/verify/graph/block_cut_tree.test.cpp.html
title: verify/graph/block_cut_tree.test.cpp
---
