---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/directed_mst.hpp
    title: Directed Minimum Spanning Tree
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
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
    \n\n#line 4 \"verify/graph/directed_mst.test.cpp\"\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cerrno>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n\
    #include <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n\
    #include <type_traits>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 8 \"verify/graph/directed_mst.test.cpp\"\
    \n#include <queue>\n#include <random>\n#line 11 \"verify/graph/directed_mst.test.cpp\"\
    \n\nnamespace {\n\nstruct TestEdge {\n    int from;\n    int to;\n    long long\
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
    \        );\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    randomized_test();\n\
    \    int n, m, root;\n    fast_input >> n >> m >> root;\n    m1une::graph::Graph<long\
    \ long> graph(n);\n    for (int index = 0; index < m; index++) {\n        int\
    \ from, to;\n        long long cost;\n        fast_input >> from >> to >> cost;\n\
    \        graph.add_directed_edge(from, to, cost);\n    }\n\n    auto answer =\
    \ m1une::graph::directed_mst(graph, root);\n    assert(answer.has_value());\n\
    \    fast_output << answer->cost << '\\n';\n    for (int vertex = 0; vertex <\
    \ n; vertex++) {\n        if (vertex) fast_output << ' ';\n        fast_output\
    \ << answer->parent[vertex];\n    }\n    fast_output << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/directedmst\"\n\n#include\
    \ \"../../graph/directed_mst.hpp\"\n\n#include <cassert>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <optional>\n#include <queue>\n#include <random>\n#include <vector>\n\
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
    \        );\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    randomized_test();\n\
    \    int n, m, root;\n    fast_input >> n >> m >> root;\n    m1une::graph::Graph<long\
    \ long> graph(n);\n    for (int index = 0; index < m; index++) {\n        int\
    \ from, to;\n        long long cost;\n        fast_input >> from >> to >> cost;\n\
    \        graph.add_directed_edge(from, to, cost);\n    }\n\n    auto answer =\
    \ m1une::graph::directed_mst(graph, root);\n    assert(answer.has_value());\n\
    \    fast_output << answer->cost << '\\n';\n    for (int vertex = 0; vertex <\
    \ n; vertex++) {\n        if (vertex) fast_output << ' ';\n        fast_output\
    \ << answer->parent[vertex];\n    }\n    fast_output << '\\n';\n}\n"
  dependsOn:
  - graph/directed_mst.hpp
  - graph/graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/directed_mst.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/directed_mst.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/directed_mst.test.cpp
- /verify/verify/graph/directed_mst.test.cpp.html
title: verify/graph/directed_mst.test.cpp
---
