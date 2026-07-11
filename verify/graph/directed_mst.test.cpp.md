---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/directed_mst.hpp
    title: Directed Minimum Spanning Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/directedmst
    links:
    - https://judge.yosupo.jp/problem/directedmst
  bundledCode: "#line 1 \"verify/graph/directed_mst.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/directedmst\"\n\n#line 1 \"graph/directed_mst.hpp\"\
    \n\n\n\n#include <cassert>\n#include <optional>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
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
    \ m1une\n\n\n#line 10 \"graph/directed_mst.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\ntemplate <class T>\nstruct DirectedMinimumSpanningTree {\n    T cost;\n\
    \    std::vector<int> parent;\n    std::vector<int> parent_edge;\n    std::vector<Edge<T>>\
    \ edges;\n    int root;\n};\n\nnamespace internal {\n\ntemplate <class T>\nstruct\
    \ DirectedMstEdge {\n    int from = -1;\n    int to = -1;\n    T cost = T(0);\n\
    \    int id = -1;\n};\n\ntemplate <class T>\nstruct DirectedMstHeapPool {\n  \
    \  using StoredEdge = DirectedMstEdge<T>;\n\n    struct Node {\n        StoredEdge\
    \ edge;\n        T offset = T(0);\n        int child = -1;\n        int sibling\
    \ = -1;\n    };\n\n    struct Heap {\n        int root = -1;\n        int size\
    \ = 0;\n    };\n\n    std::vector<Node> nodes;\n\n    explicit DirectedMstHeapPool(int\
    \ capacity = 0) {\n        nodes.reserve(capacity);\n    }\n\n    T key(int node)\
    \ const {\n        return nodes[node].edge.cost + nodes[node].offset;\n    }\n\
    \n    int meld_roots(int first, int second) {\n        if (first == -1) return\
    \ second;\n        if (second == -1) return first;\n        if (key(second) <\
    \ key(first)) std::swap(first, second);\n        nodes[second].offset -= nodes[first].offset;\n\
    \        nodes[second].sibling = nodes[first].child;\n        nodes[first].child\
    \ = second;\n        return first;\n    }\n\n    void push(Heap& heap, const StoredEdge&\
    \ edge) {\n        const int node = int(nodes.size());\n        nodes.push_back(Node{edge,\
    \ T(0), -1, -1});\n        heap.root = meld_roots(heap.root, node);\n        heap.size++;\n\
    \    }\n\n    void meld(Heap& destination, Heap& source) {\n        destination.root\
    \ = meld_roots(destination.root, source.root);\n        destination.size += source.size;\n\
    \        source.root = -1;\n        source.size = 0;\n    }\n\n    const StoredEdge&\
    \ top(const Heap& heap) const {\n        assert(heap.root != -1);\n        return\
    \ nodes[heap.root].edge;\n    }\n\n    T top_key(const Heap& heap) const {\n \
    \       assert(heap.root != -1);\n        return key(heap.root);\n    }\n\n  \
    \  void add_all(Heap& heap, const T& delta) {\n        assert(heap.root != -1);\n\
    \        nodes[heap.root].offset += delta;\n    }\n\n    void pop(Heap& heap)\
    \ {\n        assert(heap.root != -1 && heap.size > 0);\n        const int old_root\
    \ = heap.root;\n        int child = nodes[old_root].child;\n        std::vector<int>\
    \ pairs;\n        while (child != -1) {\n            int first = child;\n    \
    \        child = nodes[first].sibling;\n            nodes[first].sibling = -1;\n\
    \            nodes[first].offset += nodes[old_root].offset;\n\n            if\
    \ (child != -1) {\n                int second = child;\n                child\
    \ = nodes[second].sibling;\n                nodes[second].sibling = -1;\n    \
    \            nodes[second].offset += nodes[old_root].offset;\n               \
    \ first = meld_roots(first, second);\n            }\n            pairs.push_back(first);\n\
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
    \n\n#line 4 \"verify/graph/directed_mst.test.cpp\"\n\n#line 6 \"verify/graph/directed_mst.test.cpp\"\
    \n#include <iostream>\n#line 8 \"verify/graph/directed_mst.test.cpp\"\n#include\
    \ <queue>\n#include <random>\n#line 11 \"verify/graph/directed_mst.test.cpp\"\n\
    \nnamespace {\n\nstruct TestEdge {\n    int from;\n    int to;\n    long long\
    \ cost;\n    bool alive;\n};\n\nstd::optional<long long> brute_directed_mst(\n\
    \    int n,\n    int root,\n    const std::vector<TestEdge>& edges\n) {\n    std::vector<std::vector<int>>\
    \ incoming(n);\n    for (int index = 0; index < int(edges.size()); index++) {\n\
    \        if (edges[index].alive && edges[index].from != edges[index].to) {\n \
    \           incoming[edges[index].to].push_back(index);\n        }\n    }\n  \
    \  for (int vertex = 0; vertex < n; vertex++) {\n        if (vertex != root &&\
    \ incoming[vertex].empty()) return std::nullopt;\n    }\n\n    std::vector<int>\
    \ vertices;\n    for (int vertex = 0; vertex < n; vertex++) {\n        if (vertex\
    \ != root) vertices.push_back(vertex);\n    }\n\n    std::optional<long long>\
    \ answer;\n    std::vector<int> chosen(n, -1);\n    auto search = [&](auto&& self,\
    \ int index, long long cost) -> void {\n        if (index == int(vertices.size()))\
    \ {\n            std::vector<std::vector<int>> tree(n);\n            for (int\
    \ vertex : vertices) {\n                tree[edges[chosen[vertex]].from].push_back(vertex);\n\
    \            }\n            std::vector<char> reached(n, false);\n           \
    \ std::queue<int> queue;\n            reached[root] = true;\n            queue.push(root);\n\
    \            while (!queue.empty()) {\n                int vertex = queue.front();\n\
    \                queue.pop();\n                for (int to : tree[vertex]) {\n\
    \                    if (reached[to]) continue;\n                    reached[to]\
    \ = true;\n                    queue.push(to);\n                }\n          \
    \  }\n            for (char value : reached) {\n                if (!value) return;\n\
    \            }\n            if (!answer || cost < *answer) answer = cost;\n  \
    \          return;\n        }\n\n        int vertex = vertices[index];\n     \
    \   for (int edge_index : incoming[vertex]) {\n            chosen[vertex] = edge_index;\n\
    \            self(self, index + 1, cost + edges[edge_index].cost);\n        }\n\
    \    };\n    search(search, 0, 0);\n    return answer;\n}\n\nstd::optional<long\
    \ long> brute_rootless_directed_mst(\n    int n,\n    const std::vector<TestEdge>&\
    \ edges\n) {\n    std::optional<long long> answer;\n    for (int root = 0; root\
    \ < n; root++) {\n        auto candidate = brute_directed_mst(n, root, edges);\n\
    \        if (candidate && (!answer || *candidate < *answer)) answer = candidate;\n\
    \    }\n    return answer;\n}\n\nvoid validate_result(\n    const m1une::graph::DirectedMinimumSpanningTree<long\
    \ long>& result,\n    int n,\n    int root,\n    const std::vector<TestEdge>&\
    \ edges\n) {\n    assert(result.root == root);\n    assert(int(result.parent.size())\
    \ == n);\n    assert(int(result.parent_edge.size()) == n);\n    assert(int(result.edges.size())\
    \ == n - 1);\n    assert(result.parent[root] == root);\n    assert(result.parent_edge[root]\
    \ == -1);\n\n    long long total = 0;\n    std::vector<std::vector<int>> tree(n);\n\
    \    for (int vertex = 0; vertex < n; vertex++) {\n        if (vertex == root)\
    \ continue;\n        int edge_id = result.parent_edge[vertex];\n        assert(0\
    \ <= edge_id && edge_id < int(edges.size()));\n        const auto& edge = edges[edge_id];\n\
    \        assert(edge.alive);\n        assert(edge.to == vertex);\n        assert(edge.from\
    \ == result.parent[vertex]);\n        total += edge.cost;\n        tree[edge.from].push_back(vertex);\n\
    \    }\n    assert(total == result.cost);\n\n    std::vector<char> reached(n,\
    \ false);\n    std::queue<int> queue;\n    reached[root] = true;\n    queue.push(root);\n\
    \    while (!queue.empty()) {\n        int vertex = queue.front();\n        queue.pop();\n\
    \        for (int to : tree[vertex]) {\n            assert(!reached[to]);\n  \
    \          reached[to] = true;\n            queue.push(to);\n        }\n    }\n\
    \    for (char value : reached) assert(value);\n}\n\nvoid randomized_test() {\n\
    \    std::mt19937 random(20260711);\n    for (int test = 0; test < 500; test++)\
    \ {\n        int n = std::uniform_int_distribution<int>(1, 5)(random);\n     \
    \   int root = std::uniform_int_distribution<int>(0, n - 1)(random);\n       \
    \ int m = std::uniform_int_distribution<int>(0, 10)(random);\n\n        m1une::graph::Graph<long\
    \ long> graph(n);\n        std::vector<TestEdge> edges;\n        for (int index\
    \ = 0; index < m; index++) {\n            int from = std::uniform_int_distribution<int>(0,\
    \ n - 1)(random);\n            int to = std::uniform_int_distribution<int>(0,\
    \ n - 1)(random);\n            long long cost = std::uniform_int_distribution<int>(-5,\
    \ 10)(random);\n            int id = graph.add_directed_edge(from, to, cost);\n\
    \            bool alive = std::uniform_int_distribution<int>(0, 8)(random) !=\
    \ 0;\n            graph.set_edge_alive(id, alive);\n            edges.push_back(TestEdge{from,\
    \ to, cost, alive});\n        }\n\n        auto expected = brute_directed_mst(n,\
    \ root, edges);\n        auto actual = m1une::graph::directed_mst(graph, root);\n\
    \        assert(expected.has_value() == actual.has_value());\n        if (actual)\
    \ {\n            assert(actual->cost == *expected);\n            validate_result(*actual,\
    \ n, root, edges);\n        }\n\n        auto rootless_expected = brute_rootless_directed_mst(n,\
    \ edges);\n        auto rootless_actual = m1une::graph::directed_mst(graph);\n\
    \        assert(rootless_expected.has_value() == rootless_actual.has_value());\n\
    \        if (rootless_actual) {\n            assert(rootless_actual->cost == *rootless_expected);\n\
    \            validate_result(\n                *rootless_actual,\n           \
    \     n,\n                rootless_actual->root,\n                edges\n    \
    \        );\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    randomized_test();\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n, m, root;\n    std::cin >> n >> m >> root;\n    m1une::graph::Graph<long long>\
    \ graph(n);\n    for (int index = 0; index < m; index++) {\n        int from,\
    \ to;\n        long long cost;\n        std::cin >> from >> to >> cost;\n    \
    \    graph.add_directed_edge(from, to, cost);\n    }\n\n    auto answer = m1une::graph::directed_mst(graph,\
    \ root);\n    assert(answer.has_value());\n    std::cout << answer->cost << '\\\
    n';\n    for (int vertex = 0; vertex < n; vertex++) {\n        if (vertex) std::cout\
    \ << ' ';\n        std::cout << answer->parent[vertex];\n    }\n    std::cout\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/directedmst\"\n\n#include\
    \ \"../../graph/directed_mst.hpp\"\n\n#include <cassert>\n#include <iostream>\n\
    #include <optional>\n#include <queue>\n#include <random>\n#include <vector>\n\n\
    namespace {\n\nstruct TestEdge {\n    int from;\n    int to;\n    long long cost;\n\
    \    bool alive;\n};\n\nstd::optional<long long> brute_directed_mst(\n    int\
    \ n,\n    int root,\n    const std::vector<TestEdge>& edges\n) {\n    std::vector<std::vector<int>>\
    \ incoming(n);\n    for (int index = 0; index < int(edges.size()); index++) {\n\
    \        if (edges[index].alive && edges[index].from != edges[index].to) {\n \
    \           incoming[edges[index].to].push_back(index);\n        }\n    }\n  \
    \  for (int vertex = 0; vertex < n; vertex++) {\n        if (vertex != root &&\
    \ incoming[vertex].empty()) return std::nullopt;\n    }\n\n    std::vector<int>\
    \ vertices;\n    for (int vertex = 0; vertex < n; vertex++) {\n        if (vertex\
    \ != root) vertices.push_back(vertex);\n    }\n\n    std::optional<long long>\
    \ answer;\n    std::vector<int> chosen(n, -1);\n    auto search = [&](auto&& self,\
    \ int index, long long cost) -> void {\n        if (index == int(vertices.size()))\
    \ {\n            std::vector<std::vector<int>> tree(n);\n            for (int\
    \ vertex : vertices) {\n                tree[edges[chosen[vertex]].from].push_back(vertex);\n\
    \            }\n            std::vector<char> reached(n, false);\n           \
    \ std::queue<int> queue;\n            reached[root] = true;\n            queue.push(root);\n\
    \            while (!queue.empty()) {\n                int vertex = queue.front();\n\
    \                queue.pop();\n                for (int to : tree[vertex]) {\n\
    \                    if (reached[to]) continue;\n                    reached[to]\
    \ = true;\n                    queue.push(to);\n                }\n          \
    \  }\n            for (char value : reached) {\n                if (!value) return;\n\
    \            }\n            if (!answer || cost < *answer) answer = cost;\n  \
    \          return;\n        }\n\n        int vertex = vertices[index];\n     \
    \   for (int edge_index : incoming[vertex]) {\n            chosen[vertex] = edge_index;\n\
    \            self(self, index + 1, cost + edges[edge_index].cost);\n        }\n\
    \    };\n    search(search, 0, 0);\n    return answer;\n}\n\nstd::optional<long\
    \ long> brute_rootless_directed_mst(\n    int n,\n    const std::vector<TestEdge>&\
    \ edges\n) {\n    std::optional<long long> answer;\n    for (int root = 0; root\
    \ < n; root++) {\n        auto candidate = brute_directed_mst(n, root, edges);\n\
    \        if (candidate && (!answer || *candidate < *answer)) answer = candidate;\n\
    \    }\n    return answer;\n}\n\nvoid validate_result(\n    const m1une::graph::DirectedMinimumSpanningTree<long\
    \ long>& result,\n    int n,\n    int root,\n    const std::vector<TestEdge>&\
    \ edges\n) {\n    assert(result.root == root);\n    assert(int(result.parent.size())\
    \ == n);\n    assert(int(result.parent_edge.size()) == n);\n    assert(int(result.edges.size())\
    \ == n - 1);\n    assert(result.parent[root] == root);\n    assert(result.parent_edge[root]\
    \ == -1);\n\n    long long total = 0;\n    std::vector<std::vector<int>> tree(n);\n\
    \    for (int vertex = 0; vertex < n; vertex++) {\n        if (vertex == root)\
    \ continue;\n        int edge_id = result.parent_edge[vertex];\n        assert(0\
    \ <= edge_id && edge_id < int(edges.size()));\n        const auto& edge = edges[edge_id];\n\
    \        assert(edge.alive);\n        assert(edge.to == vertex);\n        assert(edge.from\
    \ == result.parent[vertex]);\n        total += edge.cost;\n        tree[edge.from].push_back(vertex);\n\
    \    }\n    assert(total == result.cost);\n\n    std::vector<char> reached(n,\
    \ false);\n    std::queue<int> queue;\n    reached[root] = true;\n    queue.push(root);\n\
    \    while (!queue.empty()) {\n        int vertex = queue.front();\n        queue.pop();\n\
    \        for (int to : tree[vertex]) {\n            assert(!reached[to]);\n  \
    \          reached[to] = true;\n            queue.push(to);\n        }\n    }\n\
    \    for (char value : reached) assert(value);\n}\n\nvoid randomized_test() {\n\
    \    std::mt19937 random(20260711);\n    for (int test = 0; test < 500; test++)\
    \ {\n        int n = std::uniform_int_distribution<int>(1, 5)(random);\n     \
    \   int root = std::uniform_int_distribution<int>(0, n - 1)(random);\n       \
    \ int m = std::uniform_int_distribution<int>(0, 10)(random);\n\n        m1une::graph::Graph<long\
    \ long> graph(n);\n        std::vector<TestEdge> edges;\n        for (int index\
    \ = 0; index < m; index++) {\n            int from = std::uniform_int_distribution<int>(0,\
    \ n - 1)(random);\n            int to = std::uniform_int_distribution<int>(0,\
    \ n - 1)(random);\n            long long cost = std::uniform_int_distribution<int>(-5,\
    \ 10)(random);\n            int id = graph.add_directed_edge(from, to, cost);\n\
    \            bool alive = std::uniform_int_distribution<int>(0, 8)(random) !=\
    \ 0;\n            graph.set_edge_alive(id, alive);\n            edges.push_back(TestEdge{from,\
    \ to, cost, alive});\n        }\n\n        auto expected = brute_directed_mst(n,\
    \ root, edges);\n        auto actual = m1une::graph::directed_mst(graph, root);\n\
    \        assert(expected.has_value() == actual.has_value());\n        if (actual)\
    \ {\n            assert(actual->cost == *expected);\n            validate_result(*actual,\
    \ n, root, edges);\n        }\n\n        auto rootless_expected = brute_rootless_directed_mst(n,\
    \ edges);\n        auto rootless_actual = m1une::graph::directed_mst(graph);\n\
    \        assert(rootless_expected.has_value() == rootless_actual.has_value());\n\
    \        if (rootless_actual) {\n            assert(rootless_actual->cost == *rootless_expected);\n\
    \            validate_result(\n                *rootless_actual,\n           \
    \     n,\n                rootless_actual->root,\n                edges\n    \
    \        );\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    randomized_test();\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n, m, root;\n    std::cin >> n >> m >> root;\n    m1une::graph::Graph<long long>\
    \ graph(n);\n    for (int index = 0; index < m; index++) {\n        int from,\
    \ to;\n        long long cost;\n        std::cin >> from >> to >> cost;\n    \
    \    graph.add_directed_edge(from, to, cost);\n    }\n\n    auto answer = m1une::graph::directed_mst(graph,\
    \ root);\n    assert(answer.has_value());\n    std::cout << answer->cost << '\\\
    n';\n    for (int vertex = 0; vertex < n; vertex++) {\n        if (vertex) std::cout\
    \ << ' ';\n        std::cout << answer->parent[vertex];\n    }\n    std::cout\
    \ << '\\n';\n}\n"
  dependsOn:
  - graph/directed_mst.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/directed_mst.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 20:23:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/directed_mst.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/directed_mst.test.cpp
- /verify/verify/graph/directed_mst.test.cpp.html
title: verify/graph/directed_mst.test.cpp
---
