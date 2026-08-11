---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/offline/mo.hpp
    title: Mo's Algorithm
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/heavy_light_decomposition.hpp
    title: Heavy Light Decomposition
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/tree/all.hpp
    title: Tree All
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
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/mo_on_tree.test.cpp
    title: verify/graph/tree/mo_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/tree_algorithms.test.cpp
    title: verify/graph/tree/tree_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/tree/mo_on_tree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n#line 1 \"algo/offline/mo.hpp\"\n\n\n\
    \n#line 6 \"algo/offline/mo.hpp\"\n#include <cmath>\n#include <numeric>\n#line\
    \ 9 \"algo/offline/mo.hpp\"\n\nnamespace m1une {\nnamespace algo {\n\n// Offline\
    \ Mo's algorithm for half-open array ranges.\nstruct Mo {\n    struct Query {\n\
    \        int left;\n        int right;\n        int id;\n    };\n\n   private:\n\
    \    int _n;\n    std::vector<Query> _queries;\n\n   public:\n    Mo() : _n(0)\
    \ {}\n\n    explicit Mo(int n) : _n(n) {\n        assert(0 <= n);\n    }\n\n \
    \   int size() const {\n        return _n;\n    }\n\n    int query_count() const\
    \ {\n        return int(_queries.size());\n    }\n\n    bool empty() const {\n\
    \        return _queries.empty();\n    }\n\n    const std::vector<Query>& queries()\
    \ const {\n        return _queries;\n    }\n\n    void reserve(int query_capacity)\
    \ {\n        assert(0 <= query_capacity);\n        _queries.reserve(query_capacity);\n\
    \    }\n\n    void clear() {\n        _queries.clear();\n    }\n\n    // Adds\
    \ [left, right) and returns its insertion-order ID.\n    int add_query(int left,\
    \ int right) {\n        assert(0 <= left && left <= right && right <= _n);\n \
    \       int id = query_count();\n        _queries.push_back(Query{left, right,\
    \ id});\n        return id;\n    }\n\n    // Returns query IDs in Mo order. A\
    \ non-positive block size selects one\n    // automatically.\n    std::vector<int>\
    \ order(int block_size = 0) const {\n        int query_size = query_count();\n\
    \        std::vector<int> result(query_size);\n        std::iota(result.begin(),\
    \ result.end(), 0);\n        if (query_size == 0) return result;\n\n        if\
    \ (block_size <= 0) {\n            block_size = std::max(1, int(_n / std::sqrt(static_cast<double>(query_size))));\n\
    \        }\n\n        std::sort(result.begin(), result.end(), [&](int first, int\
    \ second) {\n            const Query& a = _queries[first];\n            const\
    \ Query& b = _queries[second];\n            int first_block = a.left / block_size;\n\
    \            int second_block = b.left / block_size;\n            if (first_block\
    \ != second_block) {\n                return first_block < second_block;\n   \
    \         }\n            if (first_block & 1) return a.right > b.right;\n    \
    \        return a.right < b.right;\n        });\n        return result;\n    }\n\
    \n    // Maintains [left, right). Each movement callback receives the array index\n\
    \    // being inserted or erased. `answer(query_id)` stores or reports a result.\n\
    \    template <class AddLeft, class AddRight, class RemoveLeft, class RemoveRight,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right, Answer answer,\n             int block_size\
    \ = 0) const {\n        int left = 0;\n        int right = 0;\n        for (int\
    \ query_index : order(block_size)) {\n            const Query& query = _queries[query_index];\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    // Convenience overload for statistics whose update is\
    \ independent of\n    // which side moves.\n    template <class Add, class Remove,\
    \ class Answer>\n    void run(Add add, Remove remove, Answer answer, int block_size\
    \ = 0) const {\n        run(add, add, remove, remove, answer, block_size);\n \
    \   }\n};\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line 1 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 1 \"graph/tree/heavy_light_decomposition.hpp\"\n\n\n\n#line\
    \ 8 \"graph/tree/heavy_light_decomposition.hpp\"\n\n#line 10 \"graph/tree/heavy_light_decomposition.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nstruct HldPathSegment {\n    int l;\n\
    \    int r;\n    bool reversed;\n};\n\ntemplate <class T = int>\nstruct HeavyLightDecomposition\
    \ {\n    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n\
    \    int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> heavy;\n    std::vector<int> head;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\n   private:\n\
    \    int _n;\n\n    void check_vertex(int v) const {\n        assert(0 <= v &&\
    \ v < _n);\n        assert(tin[v] != -1);\n    }\n\n    static void add_segment(std::vector<HldPathSegment>&\
    \ result, int l, int r, bool reversed) {\n        if (l < r) result.push_back({l,\
    \ r, reversed});\n    }\n\n   public:\n    HeavyLightDecomposition() : root(-1),\
    \ _n(0) {}\n    explicit HeavyLightDecomposition(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        build(g, root_);\n    }\n\n    void build(const\
    \ m1une::graph::Graph<T>& g, int root_ = 0) {\n        _n = g.size();\n      \
    \  root = _n == 0 ? -1 : root_;\n        parent.assign(_n, -2);\n        parent_edge.assign(_n,\
    \ -1);\n        depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n       \
    \ subtree_size.assign(_n, 1);\n        heavy.assign(_n, -1);\n        head.assign(_n,\
    \ -1);\n        tin.assign(_n, -1);\n        tout.assign(_n, -1);\n        order.clear();\n\
    \        order.reserve(_n);\n        if (_n == 0) return;\n        assert(0 <=\
    \ root && root < _n);\n\n        std::vector<int> dfs_order;\n        dfs_order.reserve(_n);\n\
    \        std::vector<int> stack = {root};\n        parent[root] = -1;\n      \
    \  while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            dfs_order.push_back(v);\n            for (const auto& e : g[v]) {\n\
    \                if (!e.alive) continue;\n                if (parent[e.to] !=\
    \ -2) continue;\n                parent[e.to] = v;\n                parent_edge[e.to]\
    \ = e.id;\n                depth[e.to] = depth[v] + 1;\n                dist[e.to]\
    \ = dist[v] + e.cost;\n                stack.push_back(e.to);\n            }\n\
    \        }\n\n        for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {\n\
    \            int v = dfs_order[i];\n            if (parent[v] == -1) continue;\n\
    \            int p = parent[v];\n            subtree_size[p] += subtree_size[v];\n\
    \            if (heavy[p] == -1 || subtree_size[heavy[p]] < subtree_size[v]) heavy[p]\
    \ = v;\n        }\n\n        order.assign(dfs_order.size(), -1);\n        int\
    \ timer = 0;\n        std::vector<std::pair<int, int>> starts = {std::pair<int,\
    \ int>{root, root}};\n        while (!starts.empty()) {\n            auto [start,\
    \ h] = starts.back();\n            starts.pop_back();\n            for (int v\
    \ = start; v != -1; v = heavy[v]) {\n                head[v] = h;\n          \
    \      tin[v] = timer;\n                order[timer++] = v;\n                for\
    \ (auto it = g[v].rbegin(); it != g[v].rend(); ++it) {\n                    if\
    \ (!it->alive) continue;\n                    int to = it->to;\n             \
    \       if (parent[to] != v || to == heavy[v]) continue;\n                   \
    \ starts.push_back({to, to});\n                }\n            }\n        }\n \
    \       for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {\n            int\
    \ v = dfs_order[i];\n            tout[v] = tin[v] + subtree_size[v];\n       \
    \ }\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    bool is_ancestor(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    int lca(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        while (head[u]\
    \ != head[v]) {\n            if (depth[head[u]] < depth[head[v]]) std::swap(u,\
    \ v);\n            u = parent[head[u]];\n        }\n        return depth[u] <\
    \ depth[v] ? u : v;\n    }\n\n    int dist_edges(int u, int v) const {\n     \
    \   int w = lca(u, v);\n        return depth[u] + depth[v] - 2 * depth[w];\n \
    \   }\n\n    T dist_cost(int u, int v) const {\n        int w = lca(u, v);\n \
    \       return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\n    int kth_ancestor(int\
    \ v, int k) const {\n        check_vertex(v);\n        assert(0 <= k);\n     \
    \   while (v != -1) {\n            int h = head[v];\n            int len = depth[v]\
    \ - depth[h];\n            if (k <= len) return order[tin[v] - k];\n         \
    \   k -= len + 1;\n            v = parent[h];\n        }\n        return -1;\n\
    \    }\n\n    int jump(int from, int to, int k) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        assert(0 <= k);\n        int w = lca(from,\
    \ to);\n        int up_len = depth[from] - depth[w];\n        int down_len = depth[to]\
    \ - depth[w];\n        if (up_len + down_len < k) return -1;\n        if (k <=\
    \ up_len) return kth_ancestor(from, k);\n        return kth_ancestor(to, down_len\
    \ - (k - up_len));\n    }\n\n    std::pair<int, int> subtree_range(int v, bool\
    \ edge = false) const {\n        check_vertex(v);\n        return {tin[v] + (edge\
    \ ? 1 : 0), tout[v]};\n    }\n\n    std::vector<HldPathSegment> path_segments(int\
    \ u, int v, bool edge = false) const {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        std::vector<HldPathSegment> result, down;\n        while (head[u] !=\
    \ head[v]) {\n            if (depth[head[u]] >= depth[head[v]]) {\n          \
    \      add_segment(result, tin[head[u]], tin[u] + 1, true);\n                u\
    \ = parent[head[u]];\n            } else {\n                add_segment(down,\
    \ tin[head[v]], tin[v] + 1, false);\n                v = parent[head[v]];\n  \
    \          }\n        }\n\n        if (depth[u] >= depth[v]) {\n            add_segment(result,\
    \ tin[v] + (edge ? 1 : 0), tin[u] + 1, true);\n        } else {\n            add_segment(down,\
    \ tin[u] + (edge ? 1 : 0), tin[v] + 1, false);\n        }\n        std::reverse(down.begin(),\
    \ down.end());\n        result.insert(result.end(), down.begin(), down.end());\n\
    \        return result;\n    }\n\n    template <class F>\n    void for_each_path(int\
    \ u, int v, F f, bool edge = false) const {\n        for (auto seg : path_segments(u,\
    \ v, edge)) f(seg.l, seg.r, seg.reversed);\n    }\n};\n\n}  // namespace tree\n\
    }  // namespace m1une\n\n\n#line 11 \"graph/tree/mo_on_tree.hpp\"\n\nnamespace\
    \ m1une {\nnamespace tree {\n\n// Offline Mo's algorithm for static paths in a\
    \ tree.\ntemplate <class T = int>\nstruct MoOnTree {\n    struct Query {\n   \
    \     int from;\n        int to;\n        int left;\n        int right;\n    \
    \    int extra;\n        int id;\n        bool edge;\n    };\n\n    int root;\n\
    \    std::vector<int> entry;\n    std::vector<int> exit;\n    std::vector<int>\
    \ tour;\n\n   private:\n    int _n;\n    HeavyLightDecomposition<T> _hld;\n  \
    \  m1une::algo::Mo _mo;\n    std::vector<Query> _queries;\n\n    void check_vertex(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < _n);\n        assert(entry[vertex]\
    \ != -1);\n    }\n\n    int add_path_query(int from, int to, bool edge) {\n  \
    \      check_vertex(from);\n        check_vertex(to);\n        assert(_queries.empty()\
    \ || _queries.front().edge == edge);\n        int original_from = from;\n    \
    \    int original_to = to;\n        if (entry[from] > entry[to]) std::swap(from,\
    \ to);\n\n        int ancestor = _hld.lca(from, to);\n        int left;\n    \
    \    int right = entry[to] + 1;\n        int extra = -1;\n        if (ancestor\
    \ == from) {\n            left = entry[from] + int(edge);\n        } else {\n\
    \            left = exit[from];\n            if (!edge) extra = ancestor;\n  \
    \      }\n\n        int id = _mo.add_query(left, right);\n        _queries.push_back(Query{\n\
    \            original_from,\n            original_to,\n            left,\n   \
    \         right,\n            extra,\n            id,\n            edge,\n   \
    \     });\n        return id;\n    }\n\n   public:\n    MoOnTree() : root(-1),\
    \ _n(0), _mo(0) {}\n\n    explicit MoOnTree(\n        const m1une::graph::Graph<T>&\
    \ graph,\n        int root_vertex = 0\n    ) : root(-1), _n(0), _mo(0) {\n   \
    \     build(graph, root_vertex);\n    }\n\n    void build(\n        const m1une::graph::Graph<T>&\
    \ graph,\n        int root_vertex = 0\n    ) {\n        _n = graph.size();\n \
    \       root = _n == 0 ? -1 : root_vertex;\n        entry.assign(_n, -1);\n  \
    \      exit.assign(_n, -1);\n        tour.clear();\n        tour.reserve(2 * _n);\n\
    \        _queries.clear();\n        _mo = m1une::algo::Mo(2 * _n);\n        _hld.build(graph,\
    \ root_vertex);\n        if (_n == 0) return;\n\n        assert(0 <= root && root\
    \ < _n);\n        for (int vertex = 0; vertex < _n; ++vertex) {\n            assert(_hld.parent[vertex]\
    \ != -2);\n        }\n\n        std::vector<std::vector<int>> children(_n);\n\
    \        for (int vertex = 0; vertex < _n; ++vertex) {\n            int parent\
    \ = _hld.parent[vertex];\n            if (parent != -1) children[parent].push_back(vertex);\n\
    \        }\n\n        struct Event {\n            int vertex;\n            bool\
    \ leaving;\n        };\n        std::vector<Event> stack;\n        stack.reserve(2\
    \ * _n);\n        stack.push_back(Event{root, false});\n        while (!stack.empty())\
    \ {\n            Event event = stack.back();\n            stack.pop_back();\n\
    \            int vertex = event.vertex;\n            if (event.leaving) {\n  \
    \              exit[vertex] = int(tour.size());\n                tour.push_back(vertex);\n\
    \                continue;\n            }\n\n            entry[vertex] = int(tour.size());\n\
    \            tour.push_back(vertex);\n            stack.push_back(Event{vertex,\
    \ true});\n            const auto& child_list = children[vertex];\n          \
    \  for (int index = int(child_list.size()) - 1; index >= 0; --index) {\n     \
    \           stack.push_back(Event{child_list[index], false});\n            }\n\
    \        }\n        assert(int(tour.size()) == 2 * _n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    int query_count() const {\n        return int(_queries.size());\n\
    \    }\n\n    const std::vector<Query>& queries() const {\n        return _queries;\n\
    \    }\n\n    int parent(int vertex) const {\n        check_vertex(vertex);\n\
    \        return _hld.parent[vertex];\n    }\n\n    int parent_edge(int vertex)\
    \ const {\n        check_vertex(vertex);\n        return _hld.parent_edge[vertex];\n\
    \    }\n\n    int depth(int vertex) const {\n        check_vertex(vertex);\n \
    \       return _hld.depth[vertex];\n    }\n\n    int lca(int first, int second)\
    \ const {\n        check_vertex(first);\n        check_vertex(second);\n     \
    \   return _hld.lca(first, second);\n    }\n\n    void reserve(int query_capacity)\
    \ {\n        assert(0 <= query_capacity);\n        _queries.reserve(query_capacity);\n\
    \        _mo.reserve(query_capacity);\n    }\n\n    void clear() {\n        _queries.clear();\n\
    \        _mo.clear();\n    }\n\n    // Adds an inclusive vertex-path query and\
    \ returns its insertion-order ID.\n    // Vertex and edge queries cannot be mixed\
    \ in one collection.\n    int add_query(int from, int to) {\n        return add_path_query(from,\
    \ to, false);\n    }\n\n    // Adds an edge-path query. Each edge is represented\
    \ by its child vertex.\n    int add_edge_query(int from, int to) {\n        return\
    \ add_path_query(from, to, true);\n    }\n\n    std::vector<int> order(int block_size\
    \ = 0) const {\n        return _mo.order(block_size);\n    }\n\n    // `add(v)`\
    \ and `remove(v)` maintain the current path. In edge mode, v\n    // always represents\
    \ the real edge parent_edge(v).\n    template <class Add, class Remove, class\
    \ Answer>\n    void run(\n        Add add,\n        Remove remove,\n        Answer\
    \ answer,\n        int block_size = 0\n    ) const {\n        bool edge_mode =\
    \ !_queries.empty() && _queries.front().edge;\n        std::vector<char> active(_n,\
    \ false);\n        auto toggle = [&](int tour_index) {\n            int vertex\
    \ = tour[tour_index];\n            if (!edge_mode || vertex != root) {\n     \
    \           if (active[vertex]) {\n                    remove(vertex);\n     \
    \           } else {\n                    add(vertex);\n                }\n  \
    \          }\n            active[vertex] = !active[vertex];\n        };\n\n  \
    \      _mo.run(\n            toggle,\n            toggle,\n            [&](int\
    \ query_id) {\n                int extra = _queries[query_id].extra;\n       \
    \         if (extra != -1) {\n                    assert(!active[extra]);\n  \
    \                  add(extra);\n                }\n                answer(query_id);\n\
    \                if (extra != -1) remove(extra);\n            },\n           \
    \ block_size\n        );\n    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_TREE_MO_ON_TREE_HPP\n#define M1UNE_TREE_MO_ON_TREE_HPP 1\n\n\
    #include <algorithm>\n#include <cassert>\n#include <vector>\n\n#include \"../../algo/offline/mo.hpp\"\
    \n#include \"../graph.hpp\"\n#include \"heavy_light_decomposition.hpp\"\n\nnamespace\
    \ m1une {\nnamespace tree {\n\n// Offline Mo's algorithm for static paths in a\
    \ tree.\ntemplate <class T = int>\nstruct MoOnTree {\n    struct Query {\n   \
    \     int from;\n        int to;\n        int left;\n        int right;\n    \
    \    int extra;\n        int id;\n        bool edge;\n    };\n\n    int root;\n\
    \    std::vector<int> entry;\n    std::vector<int> exit;\n    std::vector<int>\
    \ tour;\n\n   private:\n    int _n;\n    HeavyLightDecomposition<T> _hld;\n  \
    \  m1une::algo::Mo _mo;\n    std::vector<Query> _queries;\n\n    void check_vertex(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < _n);\n        assert(entry[vertex]\
    \ != -1);\n    }\n\n    int add_path_query(int from, int to, bool edge) {\n  \
    \      check_vertex(from);\n        check_vertex(to);\n        assert(_queries.empty()\
    \ || _queries.front().edge == edge);\n        int original_from = from;\n    \
    \    int original_to = to;\n        if (entry[from] > entry[to]) std::swap(from,\
    \ to);\n\n        int ancestor = _hld.lca(from, to);\n        int left;\n    \
    \    int right = entry[to] + 1;\n        int extra = -1;\n        if (ancestor\
    \ == from) {\n            left = entry[from] + int(edge);\n        } else {\n\
    \            left = exit[from];\n            if (!edge) extra = ancestor;\n  \
    \      }\n\n        int id = _mo.add_query(left, right);\n        _queries.push_back(Query{\n\
    \            original_from,\n            original_to,\n            left,\n   \
    \         right,\n            extra,\n            id,\n            edge,\n   \
    \     });\n        return id;\n    }\n\n   public:\n    MoOnTree() : root(-1),\
    \ _n(0), _mo(0) {}\n\n    explicit MoOnTree(\n        const m1une::graph::Graph<T>&\
    \ graph,\n        int root_vertex = 0\n    ) : root(-1), _n(0), _mo(0) {\n   \
    \     build(graph, root_vertex);\n    }\n\n    void build(\n        const m1une::graph::Graph<T>&\
    \ graph,\n        int root_vertex = 0\n    ) {\n        _n = graph.size();\n \
    \       root = _n == 0 ? -1 : root_vertex;\n        entry.assign(_n, -1);\n  \
    \      exit.assign(_n, -1);\n        tour.clear();\n        tour.reserve(2 * _n);\n\
    \        _queries.clear();\n        _mo = m1une::algo::Mo(2 * _n);\n        _hld.build(graph,\
    \ root_vertex);\n        if (_n == 0) return;\n\n        assert(0 <= root && root\
    \ < _n);\n        for (int vertex = 0; vertex < _n; ++vertex) {\n            assert(_hld.parent[vertex]\
    \ != -2);\n        }\n\n        std::vector<std::vector<int>> children(_n);\n\
    \        for (int vertex = 0; vertex < _n; ++vertex) {\n            int parent\
    \ = _hld.parent[vertex];\n            if (parent != -1) children[parent].push_back(vertex);\n\
    \        }\n\n        struct Event {\n            int vertex;\n            bool\
    \ leaving;\n        };\n        std::vector<Event> stack;\n        stack.reserve(2\
    \ * _n);\n        stack.push_back(Event{root, false});\n        while (!stack.empty())\
    \ {\n            Event event = stack.back();\n            stack.pop_back();\n\
    \            int vertex = event.vertex;\n            if (event.leaving) {\n  \
    \              exit[vertex] = int(tour.size());\n                tour.push_back(vertex);\n\
    \                continue;\n            }\n\n            entry[vertex] = int(tour.size());\n\
    \            tour.push_back(vertex);\n            stack.push_back(Event{vertex,\
    \ true});\n            const auto& child_list = children[vertex];\n          \
    \  for (int index = int(child_list.size()) - 1; index >= 0; --index) {\n     \
    \           stack.push_back(Event{child_list[index], false});\n            }\n\
    \        }\n        assert(int(tour.size()) == 2 * _n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    int query_count() const {\n        return int(_queries.size());\n\
    \    }\n\n    const std::vector<Query>& queries() const {\n        return _queries;\n\
    \    }\n\n    int parent(int vertex) const {\n        check_vertex(vertex);\n\
    \        return _hld.parent[vertex];\n    }\n\n    int parent_edge(int vertex)\
    \ const {\n        check_vertex(vertex);\n        return _hld.parent_edge[vertex];\n\
    \    }\n\n    int depth(int vertex) const {\n        check_vertex(vertex);\n \
    \       return _hld.depth[vertex];\n    }\n\n    int lca(int first, int second)\
    \ const {\n        check_vertex(first);\n        check_vertex(second);\n     \
    \   return _hld.lca(first, second);\n    }\n\n    void reserve(int query_capacity)\
    \ {\n        assert(0 <= query_capacity);\n        _queries.reserve(query_capacity);\n\
    \        _mo.reserve(query_capacity);\n    }\n\n    void clear() {\n        _queries.clear();\n\
    \        _mo.clear();\n    }\n\n    // Adds an inclusive vertex-path query and\
    \ returns its insertion-order ID.\n    // Vertex and edge queries cannot be mixed\
    \ in one collection.\n    int add_query(int from, int to) {\n        return add_path_query(from,\
    \ to, false);\n    }\n\n    // Adds an edge-path query. Each edge is represented\
    \ by its child vertex.\n    int add_edge_query(int from, int to) {\n        return\
    \ add_path_query(from, to, true);\n    }\n\n    std::vector<int> order(int block_size\
    \ = 0) const {\n        return _mo.order(block_size);\n    }\n\n    // `add(v)`\
    \ and `remove(v)` maintain the current path. In edge mode, v\n    // always represents\
    \ the real edge parent_edge(v).\n    template <class Add, class Remove, class\
    \ Answer>\n    void run(\n        Add add,\n        Remove remove,\n        Answer\
    \ answer,\n        int block_size = 0\n    ) const {\n        bool edge_mode =\
    \ !_queries.empty() && _queries.front().edge;\n        std::vector<char> active(_n,\
    \ false);\n        auto toggle = [&](int tour_index) {\n            int vertex\
    \ = tour[tour_index];\n            if (!edge_mode || vertex != root) {\n     \
    \           if (active[vertex]) {\n                    remove(vertex);\n     \
    \           } else {\n                    add(vertex);\n                }\n  \
    \          }\n            active[vertex] = !active[vertex];\n        };\n\n  \
    \      _mo.run(\n            toggle,\n            toggle,\n            [&](int\
    \ query_id) {\n                int extra = _queries[query_id].extra;\n       \
    \         if (extra != -1) {\n                    assert(!active[extra]);\n  \
    \                  add(extra);\n                }\n                answer(query_id);\n\
    \                if (extra != -1) remove(extra);\n            },\n           \
    \ block_size\n        );\n    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\
    \n#endif  // M1UNE_TREE_MO_ON_TREE_HPP\n"
  dependsOn:
  - algo/offline/mo.hpp
  - graph/graph.hpp
  - graph/tree/heavy_light_decomposition.hpp
  isVerificationFile: false
  path: graph/tree/mo_on_tree.hpp
  requiredBy:
  - graph/all.hpp
  - graph/tree/all.hpp
  timestamp: '2026-08-11 13:51:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/tree/mo_on_tree.test.cpp
  - verify/graph/tree/tree_algorithms.test.cpp
documentation_of: graph/tree/mo_on_tree.hpp
layout: document
title: Mo on Tree
---

## Overview

`MoOnTree<T>` reorders static path queries on a tree and maintains the current
path through user-defined insertion and deletion callbacks. It is useful for
path statistics such as the number of distinct colors, value frequencies, and
other set-like aggregates whose one-vertex update is fast.

The structure uses a doubled Euler tour. Every vertex occurs once on entry and
once on exit, so the parity of an Euler interval describes one tree path. A
lowest common ancestor outside that interval is inserted temporarily while its
query is answered.

The graph must be a connected undirected tree built with `Graph<T>::add_edge`.
Inactive edges are ignored by the underlying tree traversal. All indices are
zero-based.

## Construction

```cpp
MoOnTree();
MoOnTree(const m1une::graph::Graph<T>& graph, int root = 0);
void build(const m1une::graph::Graph<T>& graph, int root = 0);
```

Construction roots the tree, builds heavy-light LCA metadata, and creates a
doubled Euler tour in $O(N)$ time and memory. `build` discards all registered
queries.

The chosen root does not change which vertices or edges belong to a path. It
only determines the child vertex used to represent each edge.

## Registering Queries

```cpp
int add_query(int from, int to);
int add_edge_query(int from, int to);
```

`add_query` registers the inclusive vertex path from `from` to `to`.
`add_edge_query` registers the edges on that path. Both return an
insertion-order query ID and take $O(\log N)$ time for an LCA query.

For an edge query, callbacks receive the endpoint farther from the chosen root.
Thus the corresponding original edge ID is `parent_edge(vertex)`. The empty
path registered by `add_edge_query(v, v)` contains no edge.

Vertex queries and edge queries cannot be mixed in one collection. Use two
`MoOnTree` objects if both kinds are needed. `clear()` removes all queries and
allows either kind to be selected again.

## Running the Algorithm

```cpp
mo.run(add, remove, answer);
mo.run(add, remove, answer, block_size);
```

The callbacks have these meanings:

* `add(vertex)` inserts one vertex, or its represented edge in edge mode.
* `remove(vertex)` erases the same item and must undo `add`.
* `answer(query_id)` observes the maintained state for that query.

In edge mode, every callback vertex has a valid nonnegative
`parent_edge(vertex)`; transitions involving the dummy root item are suppressed.

Callbacks can be invoked many times for one item. After `run` returns, the
maintained state is not guaranteed to be empty. For a query whose LCA needed a
temporary insertion, that insertion is removed immediately after `answer`.

With callback cost $O(F)$, the automatic block size gives the usual
$O((N\sqrt Q+Q)F+Q\log Q)$ time bound. A positive explicit block size can be
used for problem-specific tuning.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `MoOnTree()` | Creates an empty object. | $O(1)$ |
| `MoOnTree(graph, root)` | Builds the rooted tree and doubled tour. | $O(N)$ |
| `build(graph, root)` | Rebuilds and clears all queries. | $O(N)$ |
| `size()` | Returns the number of vertices. | $O(1)$ |
| `empty()` | Returns whether the tree is empty. | $O(1)$ |
| `query_count()` | Returns the number of registered queries. | $O(1)$ |
| `queries()` | Returns registered queries in insertion order. | $O(1)$ |
| `parent(v)` | Returns the rooted parent, or `-1` at the root. | $O(1)$ |
| `parent_edge(v)` | Returns the edge to the parent, or `-1` at the root. | $O(1)$ |
| `depth(v)` | Returns the unweighted rooted depth. | $O(1)$ |
| `lca(u, v)` | Returns the lowest common ancestor. | $O(\log N)$ |
| `reserve(q)` | Reserves space for `q` queries. | $O(Q)$ |
| `clear()` | Removes registered queries. | $O(Q)$ |
| `add_query(u, v)` | Adds the inclusive vertex path. | Amortized $O(\log N)$ |
| `add_edge_query(u, v)` | Adds the edge path. | Amortized $O(\log N)$ |
| `order(block_size)` | Returns query IDs in Mo order. | $O(Q\log Q)$ |
| `run(...)` | Processes all queries. | See above |

Public `root`, `entry`, `exit`, and `tour` expose the chosen root and doubled
Euler tour. For every vertex `v`, `tour[entry[v]]` and `tour[exit[v]]` both
equal `v`.

Each public `Query` stores `from`, `to`, transformed half-open interval
`[left, right)`, optional `extra` LCA, insertion-order `id`, and the `edge` mode
flag.

## Example

This computes the number of distinct colors on every vertex path:

```cpp
#include "graph/graph.hpp"
#include "graph/tree/mo_on_tree.hpp"

#include <vector>

int main() {
    m1une::graph::Graph<int> graph(5);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(1, 4);

    std::vector<int> color = {0, 1, 0, 2, 1};
    m1une::tree::MoOnTree<int> mo(graph);
    mo.add_query(3, 2);
    mo.add_query(3, 4);

    std::vector<int> frequency(3);
    std::vector<int> result(mo.query_count());
    int distinct = 0;
    mo.run(
        [&](int vertex) {
            if (frequency[color[vertex]]++ == 0) distinct++;
        },
        [&](int vertex) {
            if (--frequency[color[vertex]] == 0) distinct--;
        },
        [&](int query_id) {
            result[query_id] = distinct;
        }
    );
}
```
