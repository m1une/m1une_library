---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bellman_ford.hpp
    title: Bellman-Ford
  - icon: ':heavy_check_mark:'
    path: graph/bfs.hpp
    title: BFS
  - icon: ':heavy_check_mark:'
    path: graph/cow_game.hpp
    title: Cow Game (Difference Constraints)
  - icon: ':heavy_check_mark:'
    path: graph/cycle_detection.hpp
    title: Cycle Detection
  - icon: ':heavy_check_mark:'
    path: graph/dag_shortest_path.hpp
    title: DAG Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: Dijkstra
  - icon: ':heavy_check_mark:'
    path: graph/directed_mst.hpp
    title: Directed Minimum Spanning Tree
  - icon: ':heavy_check_mark:'
    path: graph/eulerian_trail.hpp
    title: Eulerian Trail
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/k_shortest_walk.hpp
    title: K-Shortest Walk
  - icon: ':heavy_check_mark:'
    path: graph/scc.hpp
    title: Strongly Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  - icon: ':heavy_check_mark:'
    path: graph/two_sat.hpp
    title: Two-Satisfiability
  - icon: ':heavy_check_mark:'
    path: graph/warshall_floyd.hpp
    title: Warshall-Floyd
  - icon: ':heavy_check_mark:'
    path: graph/zero_one_bfs.hpp
    title: 0-1 BFS
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/directed.hpp\"\n\n\n\n#line 1 \"graph/cycle_detection.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#include <cassert>\n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
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
    \ m1une\n\n\n#line 8 \"graph/cycle_detection.hpp\"\n\nnamespace m1une {\nnamespace\
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
    \ -1), parent_edge(n, -1);\n    Cycle result;\n\n    auto dfs = [&](auto self,\
    \ int v) -> bool {\n        color[v] = 1;\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            if (color[e.to] == 0) {\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to)) return true;\n            } else if (color[e.to]\
    \ == 1) {\n                result = restore_cycle(v, e.to, e.id, parent, parent_edge);\n\
    \                return true;\n            }\n        }\n        color[v] = 2;\n\
    \        return false;\n    };\n\n    for (int v = 0; v < n; v++) {\n        if\
    \ (color[v] == 0 && dfs(dfs, v)) break;\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nCycle find_undirected_cycle(const Graph<T>& g) {\n    int n = g.size();\n\
    \    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);\n    Cycle\
    \ result;\n\n    auto dfs = [&](auto self, int v, int pe) -> bool {\n        color[v]\
    \ = 1;\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            if (e.id == pe) continue;\n            if (color[e.to] == 0) {\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to, e.id)) return true;\n            } else\
    \ if (color[e.to] == 1) {\n                result = restore_cycle(v, e.to, e.id,\
    \ parent, parent_edge);\n                return true;\n            }\n       \
    \ }\n        color[v] = 2;\n        return false;\n    };\n\n    for (int v =\
    \ 0; v < n; v++) {\n        if (color[v] == 0 && dfs(dfs, v, -1)) break;\n   \
    \ }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\
    \n#line 1 \"graph/directed_mst.hpp\"\n\n\n\n#line 5 \"graph/directed_mst.hpp\"\
    \n#include <optional>\n#line 8 \"graph/directed_mst.hpp\"\n\n#line 10 \"graph/directed_mst.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DirectedMinimumSpanningTree\
    \ {\n    T cost;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<Edge<T>> edges;\n    int root;\n};\n\nnamespace internal {\n\n\
    template <class T>\nstruct DirectedMstEdge {\n    int from = -1;\n    int to =\
    \ -1;\n    T cost = T(0);\n    int id = -1;\n};\n\ntemplate <class T>\nstruct\
    \ DirectedMstHeapPool {\n    using StoredEdge = DirectedMstEdge<T>;\n\n    struct\
    \ Node {\n        StoredEdge edge;\n        T offset = T(0);\n        int child\
    \ = -1;\n        int sibling = -1;\n    };\n\n    struct Heap {\n        int root\
    \ = -1;\n        int size = 0;\n    };\n\n    std::vector<Node> nodes;\n\n   \
    \ explicit DirectedMstHeapPool(int capacity = 0) {\n        nodes.reserve(capacity);\n\
    \    }\n\n    T key(int node) const {\n        return nodes[node].edge.cost +\
    \ nodes[node].offset;\n    }\n\n    int meld_roots(int first, int second) {\n\
    \        if (first == -1) return second;\n        if (second == -1) return first;\n\
    \        if (key(second) < key(first)) std::swap(first, second);\n        nodes[second].offset\
    \ -= nodes[first].offset;\n        nodes[second].sibling = nodes[first].child;\n\
    \        nodes[first].child = second;\n        return first;\n    }\n\n    void\
    \ push(Heap& heap, const StoredEdge& edge) {\n        const int node = int(nodes.size());\n\
    \        nodes.push_back(Node{edge, T(0), -1, -1});\n        heap.root = meld_roots(heap.root,\
    \ node);\n        heap.size++;\n    }\n\n    void meld(Heap& destination, Heap&\
    \ source) {\n        destination.root = meld_roots(destination.root, source.root);\n\
    \        destination.size += source.size;\n        source.root = -1;\n       \
    \ source.size = 0;\n    }\n\n    const StoredEdge& top(const Heap& heap) const\
    \ {\n        assert(heap.root != -1);\n        return nodes[heap.root].edge;\n\
    \    }\n\n    T top_key(const Heap& heap) const {\n        assert(heap.root !=\
    \ -1);\n        return key(heap.root);\n    }\n\n    void add_all(Heap& heap,\
    \ const T& delta) {\n        assert(heap.root != -1);\n        nodes[heap.root].offset\
    \ += delta;\n    }\n\n    void pop(Heap& heap) {\n        assert(heap.root !=\
    \ -1 && heap.size > 0);\n        const int old_root = heap.root;\n        int\
    \ child = nodes[old_root].child;\n        std::vector<int> pairs;\n        while\
    \ (child != -1) {\n            int first = child;\n            child = nodes[first].sibling;\n\
    \            nodes[first].sibling = -1;\n            nodes[first].offset += nodes[old_root].offset;\n\
    \n            if (child != -1) {\n                int second = child;\n      \
    \          child = nodes[second].sibling;\n                nodes[second].sibling\
    \ = -1;\n                nodes[second].offset += nodes[old_root].offset;\n   \
    \             first = meld_roots(first, second);\n            }\n            pairs.push_back(first);\n\
    \        }\n\n        heap.root = -1;\n        for (auto it = pairs.rbegin();\
    \ it != pairs.rend(); ++it) {\n            heap.root = meld_roots(*it, heap.root);\n\
    \        }\n        heap.size--;\n    }\n};\n\nstruct DirectedMstDsu {\n    std::vector<int>\
    \ parent;\n\n    explicit DirectedMstDsu(int n) : parent(n, -1) {}\n\n    int\
    \ leader(int vertex) {\n        int root = vertex;\n        while (parent[root]\
    \ != -1) root = parent[root];\n        while (vertex != root) {\n            int\
    \ next = parent[vertex];\n            parent[vertex] = root;\n            vertex\
    \ = next;\n        }\n        return root;\n    }\n};\n\ntemplate <class T>\n\
    struct DirectedMstRootlessCost {\n    int artificial_edges;\n    T original_cost;\n\
    \n    DirectedMstRootlessCost() : artificial_edges(0), original_cost(T(0)) {}\n\
    \    explicit DirectedMstRootlessCost(int zero)\n        : artificial_edges(zero),\
    \ original_cost(T(0)) {\n        assert(zero == 0);\n    }\n    DirectedMstRootlessCost(int\
    \ artificial_edges_, const T& original_cost_)\n        : artificial_edges(artificial_edges_),\
    \ original_cost(original_cost_) {}\n\n    DirectedMstRootlessCost& operator+=(const\
    \ DirectedMstRootlessCost& other) {\n        artificial_edges += other.artificial_edges;\n\
    \        original_cost += other.original_cost;\n        return *this;\n    }\n\
    \n    DirectedMstRootlessCost& operator-=(const DirectedMstRootlessCost& other)\
    \ {\n        artificial_edges -= other.artificial_edges;\n        original_cost\
    \ -= other.original_cost;\n        return *this;\n    }\n\n    friend DirectedMstRootlessCost\
    \ operator+(\n        DirectedMstRootlessCost first,\n        const DirectedMstRootlessCost&\
    \ second\n    ) {\n        return first += second;\n    }\n\n    friend DirectedMstRootlessCost\
    \ operator-(\n        DirectedMstRootlessCost first,\n        const DirectedMstRootlessCost&\
    \ second\n    ) {\n        return first -= second;\n    }\n\n    friend bool operator<(\n\
    \        const DirectedMstRootlessCost& first,\n        const DirectedMstRootlessCost&\
    \ second\n    ) {\n        if (first.artificial_edges != second.artificial_edges)\
    \ {\n            return first.artificial_edges < second.artificial_edges;\n  \
    \      }\n        return first.original_cost < second.original_cost;\n    }\n\
    };\n\n}  // namespace internal\n\n// Returns a minimum-cost spanning arborescence\
    \ rooted at root, or nullopt when\n// some vertex is unreachable from the root\
    \ using active directed edges.\ntemplate <class T>\nstd::optional<DirectedMinimumSpanningTree<T>>\
    \ directed_mst(\n    const Graph<T>& graph,\n    int root\n) {\n    const int\
    \ n = graph.size();\n    assert(0 <= root && root < n);\n    const int maximum_node_count\
    \ = 2 * n;\n\n    int active_edge_count = 0;\n#ifndef NDEBUG\n    std::vector<int>\
    \ incidence(graph.edge_count(), 0);\n#endif\n    for (int vertex = 0; vertex <\
    \ n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex]) {\n      \
    \      if (!edge.alive) continue;\n            assert(0 <= edge.id && edge.id\
    \ < graph.edge_count());\n#ifndef NDEBUG\n            incidence[edge.id]++;\n\
    #endif\n            active_edge_count++;\n        }\n    }\n#ifndef NDEBUG\n \
    \   for (int count : incidence) {\n        if (count != 0) assert(count == 1);\n\
    \    }\n#endif\n\n    using StoredEdge = internal::DirectedMstEdge<T>;\n    using\
    \ HeapPool = internal::DirectedMstHeapPool<T>;\n    HeapPool pool(active_edge_count);\n\
    \    std::vector<typename HeapPool::Heap> heaps(maximum_node_count);\n    for\
    \ (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>& edge :\
    \ graph[vertex]) {\n            if (!edge.alive) continue;\n            pool.push(heaps[edge.to],\
    \ StoredEdge{edge.from, edge.to, edge.cost, edge.id});\n        }\n    }\n\n \
    \   internal::DirectedMstDsu dsu(maximum_node_count);\n    std::vector<int> contraction_parent(maximum_node_count,\
    \ -1);\n    std::vector<int> visited(maximum_node_count, 0);\n    std::vector<StoredEdge>\
    \ selected(maximum_node_count);\n    int node_count = n;\n    int visit_token\
    \ = 1;\n    visited[root] = 1;\n\n    for (int start = 0; start < n; start++)\
    \ {\n        if (visited[start] != 0) continue;\n        visit_token++;\n    \
    \    int component = start;\n        while (visited[component] == 0 || visited[component]\
    \ == visit_token) {\n            if (visited[component] == visit_token) {\n  \
    \              if (node_count == maximum_node_count) return std::nullopt;\n  \
    \              const int contracted = node_count++;\n                int current\
    \ = component;\n                do {\n                    const T reduction =\
    \ T(0) - pool.top_key(heaps[current]);\n                    pool.add_all(heaps[current],\
    \ reduction);\n                    pool.meld(heaps[contracted], heaps[current]);\n\
    \                    contraction_parent[current] = contracted;\n             \
    \       dsu.parent[current] = contracted;\n                    current = dsu.leader(selected[current].from);\n\
    \                } while (current != contracted);\n                component =\
    \ contracted;\n            }\n\n            assert(visited[component] == 0);\n\
    \            visited[component] = visit_token;\n            while (heaps[component].size\
    \ > 0 &&\n                   dsu.leader(pool.top(heaps[component]).from) == component)\
    \ {\n                pool.pop(heaps[component]);\n            }\n            if\
    \ (heaps[component].size == 0) return std::nullopt;\n            selected[component]\
    \ = pool.top(heaps[component]);\n            component = dsu.leader(selected[component].from);\n\
    \        }\n    }\n\n    DirectedMinimumSpanningTree<T> result;\n    result.cost\
    \ = T(0);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n,\
    \ -1);\n    result.root = root;\n    result.parent[root] = root;\n\n    std::vector<char>\
    \ expanded(node_count, false);\n    std::vector<StoredEdge> chosen(n);\n    for\
    \ (int component = node_count - 1; component >= 0; component--) {\n        if\
    \ (component == root || expanded[component]) continue;\n        const StoredEdge&\
    \ edge = selected[component];\n        if (edge.id == -1) return std::nullopt;\n\
    \        int vertex = edge.to;\n        while (vertex != -1 && !expanded[vertex])\
    \ {\n            expanded[vertex] = true;\n            vertex = contraction_parent[vertex];\n\
    \        }\n        result.cost += edge.cost;\n        result.parent[edge.to]\
    \ = edge.from;\n        result.parent_edge[edge.to] = edge.id;\n        chosen[edge.to]\
    \ = edge;\n    }\n\n    result.edges.reserve(n - 1);\n    for (int vertex = 0;\
    \ vertex < n; vertex++) {\n        if (vertex == root) continue;\n        if (result.parent[vertex]\
    \ == -1) return std::nullopt;\n        const StoredEdge& edge = chosen[vertex];\n\
    \        result.edges.emplace_back(edge.from, edge.to, edge.cost, edge.id, true);\n\
    \    }\n    return result;\n}\n\n// Chooses the root that gives a minimum-cost\
    \ spanning arborescence.\ntemplate <class T>\nstd::optional<DirectedMinimumSpanningTree<T>>\
    \ directed_mst(\n    const Graph<T>& graph\n) {\n    const int n = graph.size();\n\
    \    if (n == 0) return std::nullopt;\n\n    using Cost = internal::DirectedMstRootlessCost<T>;\n\
    \    Graph<Cost> augmented(n + 1);\n    std::vector<int> original_edge_id;\n \
    \   original_edge_id.reserve(graph.edge_count() + n);\n\n#ifndef NDEBUG\n    std::vector<int>\
    \ incidence(graph.edge_count(), 0);\n#endif\n    for (int vertex = 0; vertex <\
    \ n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex]) {\n      \
    \      if (!edge.alive) continue;\n#ifndef NDEBUG\n            assert(0 <= edge.id\
    \ && edge.id < graph.edge_count());\n            incidence[edge.id]++;\n#endif\n\
    \            augmented.add_directed_edge(\n                edge.from,\n      \
    \          edge.to,\n                Cost(0, edge.cost)\n            );\n    \
    \        original_edge_id.push_back(edge.id);\n        }\n    }\n#ifndef NDEBUG\n\
    \    for (int count : incidence) {\n        if (count != 0) assert(count == 1);\n\
    \    }\n#endif\n\n    const int artificial_root = n;\n    for (int vertex = 0;\
    \ vertex < n; vertex++) {\n        augmented.add_directed_edge(\n            artificial_root,\n\
    \            vertex,\n            Cost(1, T(0))\n        );\n        original_edge_id.push_back(-1);\n\
    \    }\n\n    auto augmented_result = directed_mst(augmented, artificial_root);\n\
    \    if (!augmented_result || augmented_result->cost.artificial_edges != 1) {\n\
    \        return std::nullopt;\n    }\n\n    DirectedMinimumSpanningTree<T> result;\n\
    \    result.cost = augmented_result->cost.original_cost;\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n    result.root = -1;\n    result.edges.reserve(n\
    \ - 1);\n\n    for (int vertex = 0; vertex < n; vertex++) {\n        int augmented_edge_id\
    \ = augmented_result->parent_edge[vertex];\n        assert(0 <= augmented_edge_id\
    \ &&\n               augmented_edge_id < int(original_edge_id.size()));\n    \
    \    int edge_id = original_edge_id[augmented_edge_id];\n        if (edge_id ==\
    \ -1) {\n            assert(result.root == -1);\n            result.root = vertex;\n\
    \            result.parent[vertex] = vertex;\n            continue;\n        }\n\
    \n        result.parent[vertex] = augmented_result->parent[vertex];\n        result.parent_edge[vertex]\
    \ = edge_id;\n        result.edges.emplace_back(\n            result.parent[vertex],\n\
    \            vertex,\n            augmented_result->edges[vertex].cost.original_cost,\n\
    \            edge_id,\n            true\n        );\n    }\n    assert(result.root\
    \ != -1);\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 1 \"graph/eulerian_trail.hpp\"\n\n\n\n#line 9 \"graph/eulerian_trail.hpp\"\
    \n\n#line 11 \"graph/eulerian_trail.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct EulerianTrail {\n    std::vector<int> vertices;\n    std::vector<int>\
    \ edge_ids;\n\n    int edge_count() const {\n        return int(edge_ids.size());\n\
    \    }\n\n    bool is_circuit() const {\n        return vertices.empty() || vertices.front()\
    \ == vertices.back();\n    }\n};\n\nnamespace internal {\n\ntemplate <class T>\n\
    std::optional<EulerianTrail> hierholzer(\n    const Graph<T>& graph,\n    int\
    \ start,\n    int active_edge_count\n) {\n    EulerianTrail result;\n    if (active_edge_count\
    \ == 0) {\n        if (start != -1) result.vertices.push_back(start);\n      \
    \  return result;\n    }\n\n    assert(0 <= start && start < graph.size());\n\
    \    std::vector<char> used(graph.edge_count(), false);\n    std::vector<int>\
    \ cursor(graph.size(), 0);\n    std::vector<int> vertex_stack(1, start);\n   \
    \ std::vector<int> incoming_edge_stack(1, -1);\n    std::vector<int> reversed_vertices;\n\
    \    std::vector<int> reversed_edges;\n    reversed_vertices.reserve(active_edge_count\
    \ + 1);\n    reversed_edges.reserve(active_edge_count);\n\n    while (!vertex_stack.empty())\
    \ {\n        const int vertex = vertex_stack.back();\n        while (cursor[vertex]\
    \ < int(graph[vertex].size())) {\n            const Edge<T>& edge = graph[vertex][cursor[vertex]];\n\
    \            if (edge.alive && !used[edge.id]) break;\n            cursor[vertex]++;\n\
    \        }\n\n        if (cursor[vertex] < int(graph[vertex].size())) {\n    \
    \        const Edge<T>& edge = graph[vertex][cursor[vertex]++];\n            used[edge.id]\
    \ = true;\n            vertex_stack.push_back(edge.to);\n            incoming_edge_stack.push_back(edge.id);\n\
    \            continue;\n        }\n\n        reversed_vertices.push_back(vertex);\n\
    \        const int incoming_edge = incoming_edge_stack.back();\n        if (incoming_edge\
    \ != -1) reversed_edges.push_back(incoming_edge);\n        vertex_stack.pop_back();\n\
    \        incoming_edge_stack.pop_back();\n    }\n\n    if (int(reversed_edges.size())\
    \ != active_edge_count) return std::nullopt;\n    std::reverse(reversed_vertices.begin(),\
    \ reversed_vertices.end());\n    std::reverse(reversed_edges.begin(), reversed_edges.end());\n\
    \    result.vertices = std::move(reversed_vertices);\n    result.edge_ids = std::move(reversed_edges);\n\
    \    return result;\n}\n\ntemplate <class T>\nstd::vector<int> edge_incidence_count(const\
    \ Graph<T>& graph) {\n    std::vector<int> count(graph.edge_count(), 0);\n   \
    \ for (int vertex = 0; vertex < graph.size(); vertex++) {\n        for (const\
    \ Edge<T>& edge : graph[vertex]) {\n            if (!edge.alive) continue;\n \
    \           assert(0 <= edge.id && edge.id < graph.edge_count());\n          \
    \  count[edge.id]++;\n        }\n    }\n    return count;\n}\n\n}  // namespace\
    \ internal\n\ntemplate <class T>\nstd::optional<EulerianTrail> directed_eulerian_trail(\n\
    \    const Graph<T>& graph,\n    int start = -1\n) {\n    assert(start == -1 ||\
    \ (0 <= start && start < graph.size()));\n    const int n = graph.size();\n  \
    \  std::vector<int> incidence = internal::edge_incidence_count(graph);\n    std::vector<int>\
    \ in_degree(n, 0);\n    std::vector<int> out_degree(n, 0);\n    int active_edge_count\
    \ = 0;\n    for (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>&\
    \ edge : graph[vertex]) {\n            if (!edge.alive) continue;\n          \
    \  out_degree[vertex]++;\n            in_degree[edge.to]++;\n        }\n    }\n\
    \    for (int count : incidence) {\n        if (count == 0) continue;\n      \
    \  assert(count == 1);\n        active_edge_count++;\n    }\n\n    int required_start\
    \ = -1;\n    int required_end = -1;\n    for (int vertex = 0; vertex < n; vertex++)\
    \ {\n        const int difference = out_degree[vertex] - in_degree[vertex];\n\
    \        if (difference == 1) {\n            if (required_start != -1) return\
    \ std::nullopt;\n            required_start = vertex;\n        } else if (difference\
    \ == -1) {\n            if (required_end != -1) return std::nullopt;\n       \
    \     required_end = vertex;\n        } else if (difference != 0) {\n        \
    \    return std::nullopt;\n        }\n    }\n    if ((required_start == -1) !=\
    \ (required_end == -1)) return std::nullopt;\n\n    int chosen_start = start;\n\
    \    if (active_edge_count == 0) {\n        if (chosen_start == -1 && n > 0) chosen_start\
    \ = 0;\n        return internal::hierholzer(graph, chosen_start, 0);\n    }\n\
    \    if (required_start != -1) {\n        if (chosen_start != -1 && chosen_start\
    \ != required_start) return std::nullopt;\n        chosen_start = required_start;\n\
    \    } else if (chosen_start == -1) {\n        for (int vertex = 0; vertex < n;\
    \ vertex++) {\n            if (out_degree[vertex] > 0) {\n                chosen_start\
    \ = vertex;\n                break;\n            }\n        }\n    } else if (out_degree[chosen_start]\
    \ == 0) {\n        return std::nullopt;\n    }\n    return internal::hierholzer(graph,\
    \ chosen_start, active_edge_count);\n}\n\ntemplate <class T>\nstd::optional<EulerianTrail>\
    \ undirected_eulerian_trail(\n    const Graph<T>& graph,\n    int start = -1\n\
    ) {\n    assert(start == -1 || (0 <= start && start < graph.size()));\n    const\
    \ int n = graph.size();\n    std::vector<int> incidence = internal::edge_incidence_count(graph);\n\
    \    std::vector<int> degree(n, 0);\n    int active_edge_count = 0;\n    for (int\
    \ vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>& edge : graph[vertex])\
    \ {\n            if (edge.alive) degree[vertex]++;\n        }\n    }\n    for\
    \ (int count : incidence) {\n        if (count == 0) continue;\n        assert(count\
    \ == 2);\n        active_edge_count++;\n    }\n\n    std::vector<int> odd;\n \
    \   for (int vertex = 0; vertex < n; vertex++) {\n        if (degree[vertex] &\
    \ 1) odd.push_back(vertex);\n    }\n    if (!odd.empty() && odd.size() != 2) return\
    \ std::nullopt;\n\n    int chosen_start = start;\n    if (active_edge_count ==\
    \ 0) {\n        if (chosen_start == -1 && n > 0) chosen_start = 0;\n        return\
    \ internal::hierholzer(graph, chosen_start, 0);\n    }\n    if (odd.size() ==\
    \ 2) {\n        if (chosen_start != -1 && chosen_start != odd[0] && chosen_start\
    \ != odd[1]) {\n            return std::nullopt;\n        }\n        if (chosen_start\
    \ == -1) chosen_start = odd[0];\n    } else if (chosen_start == -1) {\n      \
    \  for (int vertex = 0; vertex < n; vertex++) {\n            if (degree[vertex]\
    \ > 0) {\n                chosen_start = vertex;\n                break;\n   \
    \         }\n        }\n    } else if (degree[chosen_start] == 0) {\n        return\
    \ std::nullopt;\n    }\n    return internal::hierholzer(graph, chosen_start, active_edge_count);\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/scc.hpp\"\
    \n\n\n\n#line 6 \"graph/scc.hpp\"\n#include <cstddef>\n#line 9 \"graph/scc.hpp\"\
    \n\n#line 11 \"graph/scc.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct\
    \ SccResult {\n    int count;\n    std::vector<int> comp;\n    std::vector<std::vector<int>>\
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
    #line 1 \"graph/shortest_path.hpp\"\n\n\n\n#line 1 \"graph/bellman_ford.hpp\"\n\
    \n\n\n#line 6 \"graph/bellman_ford.hpp\"\n#include <limits>\n#include <queue>\n\
    #line 9 \"graph/bellman_ford.hpp\"\n\n#line 11 \"graph/bellman_ford.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct BellmanFordResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<bool> negative;\n    T inf;\n    bool has_negative_cycle;\n\
    \n    bool reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    bool affected_by_negative_cycle(int\
    \ v) const {\n        assert(0 <= v && v < int(negative.size()));\n        return\
    \ negative[v];\n    }\n\n    std::vector<int> path(int t) const {\n        assert(reachable(t));\n\
    \        assert(!affected_by_negative_cycle(t));\n        std::vector<int> result;\n\
    \        for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n      \
    \  std::reverse(result.begin(), result.end());\n        return result;\n    }\n\
    };\n\ntemplate <class T>\nBellmanFordResult<T> bellman_ford(const Graph<T>& g,\
    \ const std::vector<int>& sources,\n                                  T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    BellmanFordResult<T>\
    \ result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n, -1);\n\
    \    result.parent_edge.assign(n, -1);\n    result.negative.assign(n, false);\n\
    \    result.inf = inf;\n    result.has_negative_cycle = false;\n\n    for (int\
    \ s : sources) {\n        assert(0 <= s && s < n);\n        result.dist[s] = T(0);\n\
    \    }\n\n    std::vector<int> relaxed_vertices;\n    for (int iter = 0; iter\
    \ < n; iter++) {\n        bool updated = false;\n        for (int v = 0; v < n;\
    \ v++) {\n            if (result.dist[v] == inf) continue;\n            for (const\
    \ auto& e : g[v]) {\n                if (!e.alive) continue;\n               \
    \ T nd = result.dist[v] + e.cost;\n                if (result.dist[e.to] <= nd)\
    \ continue;\n                result.dist[e.to] = nd;\n                result.parent[e.to]\
    \ = v;\n                result.parent_edge[e.to] = e.id;\n                updated\
    \ = true;\n                if (iter == n - 1) relaxed_vertices.push_back(e.to);\n\
    \            }\n        }\n        if (!updated) break;\n    }\n\n    std::queue<int>\
    \ que;\n    for (int v : relaxed_vertices) {\n        if (result.negative[v])\
    \ continue;\n        result.negative[v] = true;\n        que.push(v);\n    }\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (result.negative[e.to]) continue;\n            result.negative[e.to]\
    \ = true;\n            que.push(e.to);\n        }\n    }\n\n    for (bool x :\
    \ result.negative) result.has_negative_cycle = result.has_negative_cycle || x;\n\
    \    return result;\n}\n\ntemplate <class T>\nBellmanFordResult<T> bellman_ford(const\
    \ Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4)) {\n    return\
    \ bellman_ford(g, std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n}  //\
    \ namespace m1une\n\n\n#line 1 \"graph/bfs.hpp\"\n\n\n\n#line 8 \"graph/bfs.hpp\"\
    \n\n#line 10 \"graph/bfs.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct\
    \ BfsResult {\n    std::vector<int> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n\n    bool reachable(int v) const {\n        assert(0 <= v &&\
    \ v < int(dist.size()));\n        return dist[v] != -1;\n    }\n\n    std::vector<int>\
    \ path(int t) const {\n        assert(reachable(t));\n        std::vector<int>\
    \ result;\n        for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n\
    \        std::reverse(result.begin(), result.end());\n        return result;\n\
    \    }\n};\n\ntemplate <class T>\nBfsResult bfs(const Graph<T>& g, const std::vector<int>&\
    \ sources) {\n    int n = g.size();\n    BfsResult result;\n    result.dist.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \n    std::queue<int> que;\n    for (int s : sources) {\n        assert(0 <= s\
    \ && s < n);\n        if (result.dist[s] != -1) continue;\n        result.dist[s]\
    \ = 0;\n        que.push(s);\n    }\n\n    while (!que.empty()) {\n        int\
    \ v = que.front();\n        que.pop();\n        for (const auto& e : g[v]) {\n\
    \            if (!e.alive) continue;\n            if (result.dist[e.to] != -1)\
    \ continue;\n            result.dist[e.to] = result.dist[v] + 1;\n           \
    \ result.parent[e.to] = v;\n            result.parent_edge[e.to] = e.id;\n   \
    \         que.push(e.to);\n        }\n    }\n\n    return result;\n}\n\ntemplate\
    \ <class T>\nBfsResult bfs(const Graph<T>& g, int s) {\n    return bfs(g, std::vector<int>{s});\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/cow_game.hpp\"\
    \n\n\n\n#line 7 \"graph/cow_game.hpp\"\n#include <type_traits>\n#line 10 \"graph/cow_game.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct CowGameConstraint\
    \ {\n    int from;\n    int to;\n    T upper_bound;\n};\n\ntemplate <class T>\n\
    struct CowGameSolution {\n    bool feasible = false;\n    std::vector<T> value;\n\
    \n    bool is_feasible() const {\n        return feasible;\n    }\n};\n\ntemplate\
    \ <class T>\nstruct CowGameUpperBounds {\n    bool feasible;\n    std::vector<T>\
    \ upper_bound;\n    T inf;\n\n    bool is_feasible() const {\n        return feasible;\n\
    \    }\n\n    bool bounded(int variable) const {\n        assert(0 <= variable\
    \ && variable < int(upper_bound.size()));\n        return feasible && upper_bound[variable]\
    \ != inf;\n    }\n};\n\ntemplate <class T>\nstruct CowGameDifferenceBounds {\n\
    \    bool feasible;\n    std::optional<T> lower_bound;\n    std::optional<T> upper_bound;\n\
    \n    bool is_feasible() const {\n        return feasible;\n    }\n\n    bool\
    \ bounded_below() const {\n        return feasible && lower_bound.has_value();\n\
    \    }\n\n    bool bounded_above() const {\n        return feasible && upper_bound.has_value();\n\
    \    }\n};\n\ntemplate <class T>\nclass CowGame {\n    static_assert(std::is_arithmetic_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct RelaxationResult {\n        bool has_negative_cycle;\n\
    \        std::vector<T> dist;\n    };\n\n    int _n;\n    std::vector<CowGameConstraint<T>>\
    \ _constraints;\n    mutable bool _solution_cached = false;\n    mutable CowGameSolution<T>\
    \ _cached_solution;\n\n    void assert_variable(int variable) const {\n      \
    \  (void)variable;\n        assert(0 <= variable && variable < _n);\n    }\n\n\
    \    T negate(T value) const {\n        assert(value != std::numeric_limits<T>::lowest());\n\
    \        return -value;\n    }\n\n    RelaxationResult relax(std::vector<T> dist,\
    \ T inf, bool skip_unreachable) const {\n        for (int iteration = 0; iteration\
    \ < _n; iteration++) {\n            bool updated = false;\n            for (const\
    \ auto& constraint : _constraints) {\n                if (skip_unreachable &&\
    \ dist[constraint.from] == inf) continue;\n                T candidate = dist[constraint.from]\
    \ + constraint.upper_bound;\n                if (dist[constraint.to] <= candidate)\
    \ continue;\n                dist[constraint.to] = candidate;\n              \
    \  updated = true;\n                if (iteration == _n - 1) return RelaxationResult{true,\
    \ std::move(dist)};\n            }\n            if (!updated) break;\n       \
    \ }\n        return RelaxationResult{false, std::move(dist)};\n    }\n\n    RelaxationResult\
    \ check_feasibility() const {\n        return relax(std::vector<T>(_n, T()), T(),\
    \ false);\n    }\n\n    RelaxationResult shortest_paths(int source, T inf) const\
    \ {\n        std::vector<T> dist(_n, inf);\n        dist[source] = T();\n    \
    \    return relax(std::move(dist), inf, true);\n    }\n\n   public:\n    CowGame()\
    \ : CowGame(0) {}\n\n    explicit CowGame(int variable_count) : _n(variable_count)\
    \ {\n        assert(variable_count >= 0);\n    }\n\n    int size() const {\n \
    \       return _n;\n    }\n\n    int constraint_count() const {\n        return\
    \ int(_constraints.size());\n    }\n\n    const CowGameConstraint<T>& get_constraint(int\
    \ id) const {\n        assert(0 <= id && id < int(_constraints.size()));\n   \
    \     return _constraints[id];\n    }\n\n    const std::vector<CowGameConstraint<T>>&\
    \ constraints() const {\n        return _constraints;\n    }\n\n    int add_upper_bound(int\
    \ from, int to, T upper_bound) {\n        assert_variable(from);\n        assert_variable(to);\n\
    \        int id = int(_constraints.size());\n        _constraints.push_back(CowGameConstraint<T>{from,\
    \ to, upper_bound});\n        _solution_cached = false;\n        return id;\n\
    \    }\n\n    int add_constraint(int from, int to, T upper_bound) {\n        return\
    \ add_upper_bound(from, to, upper_bound);\n    }\n\n    int add_lower_bound(int\
    \ from, int to, T lower_bound) {\n        return add_upper_bound(to, from, negate(lower_bound));\n\
    \    }\n\n    void add_bounds(int from, int to, T lower_bound, T upper_bound)\
    \ {\n        assert(lower_bound <= upper_bound);\n        add_lower_bound(from,\
    \ to, lower_bound);\n        add_upper_bound(from, to, upper_bound);\n    }\n\n\
    \    void add_equality(int from, int to, T difference) {\n        add_bounds(from,\
    \ to, difference, difference);\n    }\n\n    CowGameSolution<T> solve() const\
    \ {\n        if (_solution_cached) return _cached_solution;\n\n        auto result\
    \ = check_feasibility();\n        _cached_solution.feasible = !result.has_negative_cycle;\n\
    \        _cached_solution.value.clear();\n        if (_cached_solution.feasible)\
    \ _cached_solution.value = std::move(result.dist);\n        _solution_cached =\
    \ true;\n        return _cached_solution;\n    }\n\n    bool is_feasible() const\
    \ {\n        if (!_solution_cached) (void)solve();\n        return _cached_solution.feasible;\n\
    \    }\n\n    CowGameUpperBounds<T> tightest_upper_bounds(int source) const {\n\
    \        assert_variable(source);\n        T inf = std::numeric_limits<T>::max()\
    \ / T(4);\n        CowGameUpperBounds<T> result;\n        result.feasible = is_feasible();\n\
    \        result.inf = inf;\n        result.upper_bound.assign(_n, inf);\n    \
    \    if (!result.feasible) return result;\n\n        result.upper_bound = shortest_paths(source,\
    \ inf).dist;\n        return result;\n    }\n\n    CowGameDifferenceBounds<T>\
    \ difference_bounds(int from, int to) const {\n        assert_variable(from);\n\
    \        assert_variable(to);\n        T inf = std::numeric_limits<T>::max() /\
    \ T(4);\n        CowGameDifferenceBounds<T> result;\n        result.feasible =\
    \ is_feasible();\n        if (!result.feasible) return result;\n\n        auto\
    \ forward = shortest_paths(from, inf);\n        if (forward.dist[to] != inf) result.upper_bound\
    \ = forward.dist[to];\n\n        auto backward = shortest_paths(to, inf);\n  \
    \      if (backward.dist[from] != inf) result.lower_bound = negate(backward.dist[from]);\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nusing DifferenceConstraints\
    \ = CowGame<T>;\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"\
    graph/dag_shortest_path.hpp\"\n\n\n\n#line 9 \"graph/dag_shortest_path.hpp\"\n\
    \n#line 1 \"graph/topological_sort.hpp\"\n\n\n\n#line 7 \"graph/topological_sort.hpp\"\
    \n\n#line 9 \"graph/topological_sort.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstd::optional<std::vector<int>> topological_sort(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> indeg(n, 0);\n \
    \   for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v]) {\n    \
    \        if (!e.alive) continue;\n            indeg[e.to]++;\n        }\n    }\n\
    \n    std::queue<int> que;\n    for (int v = 0; v < n; v++) {\n        if (indeg[v]\
    \ == 0) que.push(v);\n    }\n\n    std::vector<int> order;\n    order.reserve(n);\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        order.push_back(v);\n        for (const auto& e : g[v]) {\n         \
    \   if (!e.alive) continue;\n            indeg[e.to]--;\n            if (indeg[e.to]\
    \ == 0) que.push(e.to);\n        }\n    }\n\n    if (int(order.size()) != n) return\
    \ std::nullopt;\n    return order;\n}\n\ntemplate <class T>\nbool is_dag(const\
    \ Graph<T>& g) {\n    return topological_sort(g).has_value();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 12 \"graph/dag_shortest_path.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DagShortestPathResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> topological_order;\n    T inf;\n\n    bool\
    \ reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const\
    \ {\n        assert(reachable(t));\n        std::vector<int> result;\n       \
    \ for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nstd::optional<DagShortestPathResult<T>>\
    \ dag_shortest_path(\n    const Graph<T>& g, const std::vector<int>& sources,\
    \ T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n   \
    \ auto order = topological_sort(g);\n    if (!order) return std::nullopt;\n\n\
    \    DagShortestPathResult<T> result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n    result.topological_order =\
    \ *order;\n    result.inf = inf;\n\n    for (int s : sources) {\n        assert(0\
    \ <= s && s < n);\n        if (result.dist[s] == T(0)) continue;\n        result.dist[s]\
    \ = T(0);\n    }\n\n    for (int v : *order) {\n        if (result.dist[v] ==\
    \ inf) continue;\n        for (const auto& e : g[v]) {\n            if (!e.alive)\
    \ continue;\n            T nd = result.dist[v] + e.cost;\n            if (result.dist[e.to]\
    \ <= nd) continue;\n            result.dist[e.to] = nd;\n            result.parent[e.to]\
    \ = v;\n            result.parent_edge[e.to] = e.id;\n        }\n    }\n\n   \
    \ return result;\n}\n\ntemplate <class T>\nstd::optional<DagShortestPathResult<T>>\
    \ dag_shortest_path(\n    const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    return dag_shortest_path(g, std::vector<int>{s}, inf);\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/dijkstra.hpp\"\
    \n\n\n\n#line 6 \"graph/dijkstra.hpp\"\n#include <functional>\n#line 11 \"graph/dijkstra.hpp\"\
    \n\n#line 13 \"graph/dijkstra.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    template <class T>\nstruct DijkstraResult {\n    std::vector<T> dist;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    T inf;\n\n    bool reachable(int\
    \ v) const {\n        assert(0 <= v && v < int(dist.size()));\n        return\
    \ dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const {\n       \
    \ assert(reachable(t));\n        std::vector<int> result;\n        for (int v\
    \ = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, const std::vector<int>& sources,\n             \
    \              T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n\
    \    DijkstraResult<T> result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n    result.inf = inf;\n\n    using\
    \ P = std::pair<T, int>;\n    std::priority_queue<P, std::vector<P>, std::greater<P>>\
    \ que;\n    for (int s : sources) {\n        assert(0 <= s && s < n);\n      \
    \  if (result.dist[s] == T(0)) continue;\n        result.dist[s] = T(0);\n   \
    \     que.emplace(T(0), s);\n    }\n\n    while (!que.empty()) {\n        auto\
    \ [d, v] = que.top();\n        que.pop();\n        if (result.dist[v] != d) continue;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           T nd = d + e.cost;\n            if (result.dist[e.to] <= nd) continue;\n\
    \            result.dist[e.to] = nd;\n            result.parent[e.to] = v;\n \
    \           result.parent_edge[e.to] = e.id;\n            que.emplace(nd, e.to);\n\
    \        }\n    }\n\n    return result;\n}\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4))\
    \ {\n    return dijkstra(g, std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 1 \"graph/k_shortest_walk.hpp\"\n\n\n\n#line\
    \ 10 \"graph/k_shortest_walk.hpp\"\n\n#line 12 \"graph/k_shortest_walk.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\nnamespace internal {\n\ntemplate <class\
    \ T>\nclass KShortestWalkHeap {\n    struct Node {\n        T key;\n        int\
    \ to;\n        int left;\n        int right;\n        int rank;\n    };\n\n  \
    \  std::vector<Node> _nodes;\n\n    int rank(int root) const {\n        return\
    \ root == -1 ? 0 : _nodes[root].rank;\n    }\n\n   public:\n    int make_node(T\
    \ key, int to) {\n        int result = int(_nodes.size());\n        _nodes.push_back(Node{key,\
    \ to, -1, -1, 1});\n        return result;\n    }\n\n    int meld_mutable(int\
    \ first, int second) {\n        if (first == -1) return second;\n        if (second\
    \ == -1) return first;\n        if (_nodes[second].key < _nodes[first].key) std::swap(first,\
    \ second);\n        _nodes[first].right = meld_mutable(_nodes[first].right, second);\n\
    \        if (rank(_nodes[first].left) < rank(_nodes[first].right)) {\n       \
    \     std::swap(_nodes[first].left, _nodes[first].right);\n        }\n       \
    \ _nodes[first].rank = rank(_nodes[first].right) + 1;\n        return first;\n\
    \    }\n\n    int meld_persistent(int first, int second) {\n        if (first\
    \ == -1) return second;\n        if (second == -1) return first;\n        if (_nodes[second].key\
    \ < _nodes[first].key) std::swap(first, second);\n        int result = int(_nodes.size());\n\
    \        _nodes.push_back(_nodes[first]);\n        _nodes[result].right = meld_persistent(_nodes[result].right,\
    \ second);\n        if (rank(_nodes[result].left) < rank(_nodes[result].right))\
    \ {\n            std::swap(_nodes[result].left, _nodes[result].right);\n     \
    \   }\n        _nodes[result].rank = rank(_nodes[result].right) + 1;\n       \
    \ return result;\n    }\n\n    const Node& operator[](int index) const {\n   \
    \     return _nodes[index];\n    }\n};\n\n}  // namespace internal\n\ntemplate\
    \ <class T>\nstd::vector<T> k_shortest_walk(\n    const Graph<T>& g,\n    int\
    \ s,\n    int t,\n    int k,\n    T inf = std::numeric_limits<T>::max() / T(4)\n\
    ) {\n    int n = g.size();\n    assert(0 <= s && s < n);\n    assert(0 <= t &&\
    \ t < n);\n    assert(0 <= k);\n    if (k == 0) return {};\n\n    struct ReverseEdge\
    \ {\n        int from;\n        int index;\n        T cost;\n    };\n    std::vector<std::vector<ReverseEdge>>\
    \ reverse_graph(n);\n    for (int from = 0; from < n; from++) {\n        for (int\
    \ index = 0; index < int(g[from].size()); index++) {\n            const auto&\
    \ edge = g[from][index];\n            if (!edge.alive) continue;\n           \
    \ assert(T(0) <= edge.cost);\n            reverse_graph[edge.to].push_back(ReverseEdge{from,\
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
    }  // namespace m1une\n\n\n#line 1 \"graph/warshall_floyd.hpp\"\n\n\n\n#line 8\
    \ \"graph/warshall_floyd.hpp\"\n\n#line 10 \"graph/warshall_floyd.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T>\nstd::vector<std::vector<T>>\
    \ warshall_floyd(std::vector<std::vector<T>> dist,\n                         \
    \                  T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n\
    \ = int(dist.size());\n    for (int k = 0; k < n; k++) {\n        for (int i =\
    \ 0; i < n; i++) {\n            if (dist[i][k] == inf) continue;\n           \
    \ for (int j = 0; j < n; j++) {\n                if (dist[k][j] == inf) continue;\n\
    \                T nd = dist[i][k] + dist[k][j];\n                if (nd < dist[i][j])\
    \ dist[i][j] = nd;\n            }\n        }\n    }\n    return dist;\n}\n\ntemplate\
    \ <class T>\nstd::vector<std::vector<T>> warshall_floyd(const Graph<T>& g, T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    std::vector<std::vector<T>>\
    \ dist(n, std::vector<T>(n, inf));\n    for (int i = 0; i < n; i++) dist[i][i]\
    \ = T(0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            if (e.cost < dist[e.from][e.to])\
    \ dist[e.from][e.to] = e.cost;\n        }\n    }\n    return warshall_floyd(std::move(dist),\
    \ inf);\n}\n\ntemplate <class T>\nbool warshall_floyd_add_directed_edge(std::vector<std::vector<T>>&\
    \ dist, int from, int to, T cost,\n                                      T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n \
    \   assert(0 <= from && from < n);\n    assert(0 <= to && to < n);\n\n    std::vector<T>\
    \ to_from(n), from_to(n);\n    for (int i = 0; i < n; i++) {\n        to_from[i]\
    \ = dist[i][from];\n        from_to[i] = dist[to][i];\n    }\n\n    bool updated\
    \ = false;\n    for (int i = 0; i < n; i++) {\n        if (to_from[i] == inf)\
    \ continue;\n        for (int j = 0; j < n; j++) {\n            if (from_to[j]\
    \ == inf) continue;\n            T nd = to_from[i] + cost + from_to[j];\n    \
    \        if (nd < dist[i][j]) {\n                dist[i][j] = nd;\n          \
    \      updated = true;\n            }\n        }\n    }\n    return updated;\n\
    }\n\ntemplate <class T>\nbool warshall_floyd_add_undirected_edge(std::vector<std::vector<T>>&\
    \ dist, int u, int v, T cost,\n                                        T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n   \
    \ assert(0 <= u && u < n);\n    assert(0 <= v && v < n);\n\n    std::vector<T>\
    \ to_u(n), from_u(n), to_v(n), from_v(n);\n    for (int i = 0; i < n; i++) {\n\
    \        to_u[i] = dist[i][u];\n        from_u[i] = dist[u][i];\n        to_v[i]\
    \ = dist[i][v];\n        from_v[i] = dist[v][i];\n    }\n\n    bool updated =\
    \ false;\n    for (int i = 0; i < n; i++) {\n        for (int j = 0; j < n; j++)\
    \ {\n            if (to_u[i] != inf && from_v[j] != inf) {\n                T\
    \ nd = to_u[i] + cost + from_v[j];\n                if (nd < dist[i][j]) {\n \
    \                   dist[i][j] = nd;\n                    updated = true;\n  \
    \              }\n            }\n            if (to_v[i] != inf && from_u[j] !=\
    \ inf) {\n                T nd = to_v[i] + cost + from_u[j];\n               \
    \ if (nd < dist[i][j]) {\n                    dist[i][j] = nd;\n             \
    \       updated = true;\n                }\n            }\n        }\n    }\n\
    \    return updated;\n}\n\ntemplate <class T>\nbool has_negative_cycle(const std::vector<std::vector<T>>&\
    \ dist) {\n    int n = int(dist.size());\n    for (int i = 0; i < n; i++) {\n\
    \        if (dist[i][i] < T(0)) return true;\n    }\n    return false;\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/zero_one_bfs.hpp\"\
    \n\n\n\n#line 6 \"graph/zero_one_bfs.hpp\"\n#include <deque>\n#line 9 \"graph/zero_one_bfs.hpp\"\
    \n\n#line 11 \"graph/zero_one_bfs.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct ZeroOneBfsResult {\n    std::vector<int> dist;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    int inf;\n\n    bool reachable(int\
    \ v) const {\n        assert(0 <= v && v < int(dist.size()));\n        return\
    \ dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const {\n       \
    \ assert(reachable(t));\n        std::vector<int> result;\n        for (int v\
    \ = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nZeroOneBfsResult\
    \ zero_one_bfs(const Graph<T>& g, const std::vector<int>& sources,\n         \
    \                     int inf = std::numeric_limits<int>::max() / 2) {\n    int\
    \ n = g.size();\n    ZeroOneBfsResult result;\n    result.dist.assign(n, inf);\n\
    \    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n   \
    \ result.inf = inf;\n\n    std::deque<int> deq;\n    for (int s : sources) {\n\
    \        assert(0 <= s && s < n);\n        if (result.dist[s] == 0) continue;\n\
    \        result.dist[s] = 0;\n        deq.push_back(s);\n    }\n\n    while (!deq.empty())\
    \ {\n        int v = deq.front();\n        deq.pop_front();\n        for (const\
    \ auto& e : g[v]) {\n            if (!e.alive) continue;\n            int w;\n\
    \            if (e.cost == T(0)) {\n                w = 0;\n            } else\
    \ {\n                assert(e.cost == T(1));\n                w = 1;\n       \
    \     }\n            int nd = result.dist[v] + w;\n            if (result.dist[e.to]\
    \ <= nd) continue;\n            result.dist[e.to] = nd;\n            result.parent[e.to]\
    \ = v;\n            result.parent_edge[e.to] = e.id;\n            if (w == 0)\
    \ {\n                deq.push_front(e.to);\n            } else {\n           \
    \     deq.push_back(e.to);\n            }\n        }\n    }\n\n    return result;\n\
    }\n\ntemplate <class T>\nZeroOneBfsResult zero_one_bfs(const Graph<T>& g, int\
    \ s, int inf = std::numeric_limits<int>::max() / 2) {\n    return zero_one_bfs(g,\
    \ std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 12 \"graph/shortest_path.hpp\"\n\n\n#line 1 \"graph/two_sat.hpp\"\n\n\
    \n\n#line 9 \"graph/two_sat.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    // A 2-SAT solver using iterative strongly connected components.\nstruct TwoSat\
    \ {\n   private:\n    struct Csr {\n        std::vector<int> start;\n        std::vector<int>\
    \ to;\n    };\n\n    int _n;\n    std::vector<std::pair<int, int>> _edges;\n \
    \   bool _solved;\n    bool _satisfiable;\n    std::vector<bool> _answer;\n\n\
    \    int node(int variable, bool value) const {\n        assert(0 <= variable\
    \ && variable < _n);\n        return 2 * variable + int(value);\n    }\n\n   \
    \ void add_edge(int from, int to) {\n        _edges.emplace_back(from, to);\n\
    \        _solved = false;\n        _answer.clear();\n    }\n\n    Csr build_csr(bool\
    \ reverse) const {\n        int vertices = 2 * _n;\n        Csr graph;\n     \
    \   graph.start.assign(vertices + 1, 0);\n        graph.to.resize(_edges.size());\n\
    \n        for (auto [from, to] : _edges) {\n            int source = reverse ?\
    \ to : from;\n            graph.start[source + 1]++;\n        }\n        for (int\
    \ v = 0; v < vertices; v++) {\n            graph.start[v + 1] += graph.start[v];\n\
    \        }\n\n        std::vector<int> cursor = graph.start;\n        for (auto\
    \ [from, to] : _edges) {\n            int source = reverse ? to : from;\n    \
    \        int target = reverse ? from : to;\n            graph.to[cursor[source]++]\
    \ = target;\n        }\n        return graph;\n    }\n\n   public:\n    TwoSat()\
    \ : TwoSat(0) {}\n\n    explicit TwoSat(int n)\n        : _n(n), _solved(false),\
    \ _satisfiable(false) {\n        assert(0 <= n);\n        assert(n <= std::numeric_limits<int>::max()\
    \ / 2);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Reserves space for\
    \ approximately `clause_count` two-literal clauses.\n    void reserve(std::size_t\
    \ clause_count) {\n        assert(clause_count <= std::size_t(std::numeric_limits<int>::max())\
    \ / 2);\n        _edges.reserve(2 * clause_count);\n    }\n\n    // Adds (variable\
    \ i == f) OR (variable j == g).\n    void add_clause(int i, bool f, int j, bool\
    \ g) {\n        int a = node(i, f);\n        int b = node(j, g);\n        add_edge(a\
    \ ^ 1, b);\n        add_edge(b ^ 1, a);\n    }\n\n    // Adds (variable i == f)\
    \ => (variable j == g).\n    void add_implication(int i, bool f, int j, bool g)\
    \ {\n        add_clause(i, !f, j, g);\n    }\n\n    // Forces variable i to equal\
    \ value.\n    void set_value(int i, bool value) {\n        add_clause(i, value,\
    \ i, value);\n    }\n\n    // Forces variables i and j to have equal values.\n\
    \    void add_equal(int i, int j) {\n        add_clause(i, false, j, true);\n\
    \        add_clause(i, true, j, false);\n    }\n\n    // Forces variables i and\
    \ j to have different values.\n    void add_not_equal(int i, int j) {\n      \
    \  add_clause(i, true, j, true);\n        add_clause(i, false, j, false);\n  \
    \  }\n\n    bool satisfiable() {\n        if (_solved) return _satisfiable;\n\
    \        assert(_edges.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n        int vertices = 2 * _n;\n        Csr graph = build_csr(false);\n    \
    \    Csr reverse_graph = build_csr(true);\n\n        std::vector<char> seen(vertices,\
    \ false);\n        std::vector<int> order;\n        order.reserve(vertices);\n\
    \        std::vector<std::pair<int, int>> stack;\n        stack.reserve(vertices);\n\
    \n        for (int start = 0; start < vertices; start++) {\n            if (seen[start])\
    \ continue;\n            seen[start] = true;\n            stack.emplace_back(start,\
    \ graph.start[start]);\n\n            while (!stack.empty()) {\n             \
    \   int v = stack.back().first;\n                int& edge = stack.back().second;\n\
    \                if (edge == graph.start[v + 1]) {\n                    order.push_back(v);\n\
    \                    stack.pop_back();\n                    continue;\n      \
    \          }\n\n                int to = graph.to[edge++];\n                if\
    \ (!seen[to]) {\n                    seen[to] = true;\n                    stack.emplace_back(to,\
    \ graph.start[to]);\n                }\n            }\n        }\n\n        std::vector<int>\
    \ component(vertices, -1);\n        std::vector<int> vertices_stack;\n       \
    \ vertices_stack.reserve(vertices);\n        int component_count = 0;\n      \
    \  for (int index = vertices - 1; index >= 0; index--) {\n            int start\
    \ = order[index];\n            if (component[start] != -1) continue;\n\n     \
    \       component[start] = component_count;\n            vertices_stack.push_back(start);\n\
    \            while (!vertices_stack.empty()) {\n                int v = vertices_stack.back();\n\
    \                vertices_stack.pop_back();\n                for (int edge = reverse_graph.start[v];\n\
    \                     edge < reverse_graph.start[v + 1];\n                   \
    \  edge++) {\n                    int to = reverse_graph.to[edge];\n         \
    \           if (component[to] == -1) {\n                        component[to]\
    \ = component_count;\n                        vertices_stack.push_back(to);\n\
    \                    }\n                }\n            }\n            component_count++;\n\
    \        }\n\n        _answer.assign(_n, false);\n        _satisfiable = true;\n\
    \        for (int i = 0; i < _n; i++) {\n            if (component[2 * i] == component[2\
    \ * i + 1]) {\n                _satisfiable = false;\n                _answer.clear();\n\
    \                break;\n            }\n            _answer[i] = component[2 *\
    \ i] < component[2 * i + 1];\n        }\n        _solved = true;\n        return\
    \ _satisfiable;\n    }\n\n    const std::vector<bool>& answer() const {\n    \
    \    assert(_solved && _satisfiable);\n        return _answer;\n    }\n\n    bool\
    \ value(int variable) const {\n        assert(_solved && _satisfiable);\n    \
    \    assert(0 <= variable && variable < _n);\n        return _answer[variable];\n\
    \    }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 12 \"graph/directed.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_GRAPH_DIRECTED_HPP

    #define M1UNE_GRAPH_DIRECTED_HPP 1


    #include "cycle_detection.hpp"

    #include "directed_mst.hpp"

    #include "eulerian_trail.hpp"

    #include "graph.hpp"

    #include "scc.hpp"

    #include "shortest_path.hpp"

    #include "topological_sort.hpp"

    #include "two_sat.hpp"


    #endif  // M1UNE_GRAPH_DIRECTED_HPP

    '
  dependsOn:
  - graph/cycle_detection.hpp
  - graph/graph.hpp
  - graph/directed_mst.hpp
  - graph/eulerian_trail.hpp
  - graph/scc.hpp
  - graph/shortest_path.hpp
  - graph/bellman_ford.hpp
  - graph/bfs.hpp
  - graph/cow_game.hpp
  - graph/dag_shortest_path.hpp
  - graph/topological_sort.hpp
  - graph/dijkstra.hpp
  - graph/k_shortest_walk.hpp
  - graph/warshall_floyd.hpp
  - graph/zero_one_bfs.hpp
  - graph/two_sat.hpp
  isVerificationFile: false
  path: graph/directed.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-07-13 20:12:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/directed.hpp
layout: document
title: Directed Graph Algorithms
---

## Overview

`graph/directed.hpp` includes algorithms whose main interpretation is directed,
plus direction-respecting shortest paths.

Use this header when the input edges are one-way, or when reachability/order
depends on edge direction.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/shortest_path.hpp` | Direction-respecting / DAG-specific | BFS, 0-1 BFS, DAG shortest path, Dijkstra, Bellman-Ford, and Warshall-Floyd. |
| `graph/topological_sort.hpp` | Directed only | DAG ordering and directed cycle check. |
| `graph/directed_mst.hpp` | Directed rooted graph | Minimum-cost spanning arborescence with edge reconstruction. |
| `graph/scc.hpp` | Directed only | Strongly connected components and condensation DAG. |
| `graph/two_sat.hpp` | Implication graph | 2-SAT clauses, satisfiability, and one assignment. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Use `find_directed_cycle(g)` for directed graphs. |
| `graph/eulerian_trail.hpp` | Directed and undirected variants | Use `directed_eulerian_trail(g)` for directed graphs. |

## Complexity

This header is an include bundle and provides no runtime operation by itself.
See the included algorithm pages for public interfaces and complexities.
