---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/centroid_decomposition.hpp
    title: Centroid Decomposition
  - icon: ':heavy_check_mark:'
    path: graph/tree/rooted_tree.hpp
    title: Rooted Tree
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
    path: verify/graph/tree/tree_algorithms.test.cpp
    title: verify/graph/tree/tree_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/vertex_add_range_contour_sum_on_tree.test.cpp
    title: verify/graph/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/vertex_get_range_contour_add_on_tree.test.cpp
    title: verify/graph/tree/vertex_get_range_contour_add_on_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/tree/range_contour_query.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for addition (Range Sum).\ntemplate\
    \ <typename T>\nstruct Add {\n    using value_type = T;\n\n    // Returns the\
    \ identity element for addition, which is 0.\n    static constexpr T id() {\n\
    \        return T(0);\n    }\n\n    // Returns the sum of a and b.\n    static\
    \ constexpr T op(const T& a, const T& b) {\n        return a + b;\n    }\n\n \
    \   static constexpr T inv(const T& x) {\n        return -x;\n    }\n};\n\n} \
    \ // namespace monoid\n}  // namespace m1une\n\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#include <concepts>\n\nnamespace m1une {\nnamespace monoid {\n\n// Concept\
    \ to check if a type satisfies the requirements of a Monoid.\n// A Monoid must\
    \ have a `value_type`, an identity element `id()`, and an associative binary operation\
    \ `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename M::value_type\
    \ a, typename M::value_type b) {\n    // 1. Must define `value_type`\n    typename\
    \ M::value_type;\n\n    // 2. Must have a static method `id()` returning `value_type`\n\
    \    { M::id() } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have\
    \ a static method `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 1 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 1 \"graph/tree/centroid_decomposition.hpp\"\n\n\n\n#line 6\
    \ \"graph/tree/centroid_decomposition.hpp\"\n\n#line 8 \"graph/tree/centroid_decomposition.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct CentroidDecomposition\
    \ {\n    int n;\n    std::vector<int> parent;\n    std::vector<int> depth;\n \
    \   std::vector<int> order;\n    std::vector<int> roots;\n    std::vector<std::vector<int>>\
    \ children;\n\n   private:\n    std::vector<int> _subtree_size;\n    std::vector<int>\
    \ _work_parent;\n    std::vector<char> _removed;\n\n    void build_component(const\
    \ m1une::graph::Graph<T>& g, int start, int p, int d) {\n        std::vector<int>\
    \ nodes;\n        std::vector<int> stack = {start};\n        _work_parent[start]\
    \ = -2;\n        while (!stack.empty()) {\n            int v = stack.back();\n\
    \            stack.pop_back();\n            nodes.push_back(v);\n            for\
    \ (const auto& e : g[v]) {\n                if (!e.alive || _removed[e.to]) continue;\n\
    \                if (_work_parent[e.to] != -1) continue;\n                _work_parent[e.to]\
    \ = v;\n                stack.push_back(e.to);\n            }\n        }\n\n \
    \       for (int v : nodes) _subtree_size[v] = 1;\n        for (int i = int(nodes.size())\
    \ - 1; i >= 0; i--) {\n            int v = nodes[i];\n            if (_work_parent[v]\
    \ >= 0) _subtree_size[_work_parent[v]] += _subtree_size[v];\n        }\n\n   \
    \     int total = int(nodes.size());\n        int centroid = start;\n        int\
    \ best = total + 1;\n        for (int v : nodes) {\n            int largest =\
    \ total - _subtree_size[v];\n            for (const auto& e : g[v]) {\n      \
    \          if (!e.alive || _removed[e.to]) continue;\n                if (_work_parent[e.to]\
    \ == v) largest = std::max(largest, _subtree_size[e.to]);\n            }\n   \
    \         if (largest < best) {\n                best = largest;\n           \
    \     centroid = v;\n            }\n        }\n\n        for (int v : nodes) _work_parent[v]\
    \ = -1;\n\n        parent[centroid] = p;\n        depth[centroid] = d;\n     \
    \   order.push_back(centroid);\n        if (p == -1) {\n            roots.push_back(centroid);\n\
    \        } else {\n            children[p].push_back(centroid);\n        }\n \
    \       _removed[centroid] = true;\n\n        for (const auto& e : g[centroid])\
    \ {\n            if (!e.alive || _removed[e.to]) continue;\n            build_component(g,\
    \ e.to, centroid, d + 1);\n        }\n    }\n\n   public:\n    CentroidDecomposition()\
    \ : n(0) {}\n    explicit CentroidDecomposition(const m1une::graph::Graph<T>&\
    \ g) {\n        build(g);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g) {\n        n = g.size();\n        parent.assign(n, -1);\n        depth.assign(n,\
    \ -1);\n        order.clear();\n        order.reserve(n);\n        roots.clear();\n\
    \        children.assign(n, {});\n        _subtree_size.assign(n, 0);\n      \
    \  _work_parent.assign(n, -1);\n        _removed.assign(n, false);\n\n       \
    \ for (int v = 0; v < n; v++) {\n            if (depth[v] == -1) build_component(g,\
    \ v, -1, 0);\n        }\n    }\n\n    int size() const {\n        return n;\n\
    \    }\n\n    bool empty() const {\n        return n == 0;\n    }\n\n    int root()\
    \ const {\n        return roots.empty() ? -1 : roots[0];\n    }\n};\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n\n#line 1 \"graph/tree/rooted_tree.hpp\"\n\n\n\
    \n#line 7 \"graph/tree/rooted_tree.hpp\"\n\n#line 9 \"graph/tree/rooted_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct RootedTree\
    \ {\n    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n\
    \    int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\
    \    std::vector<std::vector<int>> up;\n\n   private:\n    int _n;\n    int _log;\n\
    \n    void check_vertex(int v) const {\n        assert(0 <= v && v < _n);\n  \
    \      assert(tin[v] != -1);\n    }\n\n   public:\n    RootedTree() : root(-1),\
    \ _n(0), _log(0) {}\n    explicit RootedTree(const m1une::graph::Graph<T>& g,\
    \ int root_ = 0) {\n        build(g, root_);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        _n = g.size();\n        root = _n == 0 ? -1 : root_;\n\
    \        _log = 1;\n        while ((1U << _log) <= (unsigned int)(std::max(1,\
    \ _n))) _log++;\n\n        parent.assign(_n, -1);\n        parent_edge.assign(_n,\
    \ -1);\n        depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n       \
    \ subtree_size.assign(_n, 0);\n        tin.assign(_n, -1);\n        tout.assign(_n,\
    \ -1);\n        order.clear();\n        order.reserve(_n);\n        up.assign(_log,\
    \ std::vector<int>(_n, -1));\n\n        if (_n == 0) return;\n        assert(0\
    \ <= root && root < _n);\n\n        struct Frame {\n            int v;\n     \
    \       int state;\n        };\n\n        std::vector<char> visited(_n, false);\n\
    \        std::vector<Frame> stack;\n        stack.push_back({root, 0});\n    \
    \    visited[root] = true;\n        int timer = 0;\n\n        while (!stack.empty())\
    \ {\n            Frame frame = stack.back();\n            stack.pop_back();\n\
    \            int v = frame.v;\n            if (frame.state == 0) {\n         \
    \       tin[v] = timer++;\n                order.push_back(v);\n             \
    \   up[0][v] = parent[v];\n                for (int k = 1; k < _log; k++) {\n\
    \                    int p = up[k - 1][v];\n                    up[k][v] = p ==\
    \ -1 ? -1 : up[k - 1][p];\n                }\n\n                stack.push_back({v,\
    \ 1});\n                const auto& adj = g[v];\n                for (int i =\
    \ int(adj.size()) - 1; i >= 0; i--) {\n                    const auto& e = adj[i];\n\
    \                    if (!e.alive) continue;\n                    if (visited[e.to])\
    \ continue;\n                    visited[e.to] = true;\n                    parent[e.to]\
    \ = v;\n                    parent_edge[e.to] = e.id;\n                    depth[e.to]\
    \ = depth[v] + 1;\n                    dist[e.to] = dist[v] + e.cost;\n      \
    \              stack.push_back({e.to, 0});\n                }\n            } else\
    \ {\n                subtree_size[v]++;\n                if (parent[v] != -1)\
    \ subtree_size[parent[v]] += subtree_size[v];\n                tout[v] = timer;\n\
    \            }\n        }\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    int\
    \ log() const {\n        return _log;\n    }\n\n    bool is_ancestor(int u, int\
    \ v) const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    bool in_subtree(int v,\
    \ int u) const {\n        return is_ancestor(u, v);\n    }\n\n    int kth_ancestor(int\
    \ v, int k) const {\n        check_vertex(v);\n        assert(0 <= k);\n     \
    \   int bit = 0;\n        while (k > 0 && v != -1) {\n            if (k & 1) {\n\
    \                if (_log <= bit) return -1;\n                v = up[bit][v];\n\
    \            }\n            k >>= 1;\n            bit++;\n        }\n        return\
    \ v;\n    }\n\n    int lca(int u, int v) const {\n        check_vertex(u);\n \
    \       check_vertex(v);\n        if (depth[u] < depth[v]) std::swap(u, v);\n\
    \        u = kth_ancestor(u, depth[u] - depth[v]);\n        if (u == v) return\
    \ u;\n        for (int k = _log - 1; k >= 0; k--) {\n            if (up[k][u]\
    \ != up[k][v]) {\n                u = up[k][u];\n                v = up[k][v];\n\
    \            }\n        }\n        return parent[u];\n    }\n\n    int dist_edges(int\
    \ u, int v) const {\n        int w = lca(u, v);\n        return depth[u] + depth[v]\
    \ - 2 * depth[w];\n    }\n\n    T dist_cost(int u, int v) const {\n        int\
    \ w = lca(u, v);\n        return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\
    \n    int jump(int from, int to, int k) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        assert(0 <= k);\n        int w = lca(from,\
    \ to);\n        int up_len = depth[from] - depth[w];\n        int down_len = depth[to]\
    \ - depth[w];\n        if (up_len + down_len < k) return -1;\n        if (k <=\
    \ up_len) return kth_ancestor(from, k);\n        return kth_ancestor(to, down_len\
    \ - (k - up_len));\n    }\n\n    std::vector<int> path(int u, int v) const {\n\
    \        check_vertex(u);\n        check_vertex(v);\n        int w = lca(u, v);\n\
    \        std::vector<int> a, b;\n        for (int x = u; x != w; x = parent[x])\
    \ a.push_back(x);\n        a.push_back(w);\n        for (int x = v; x != w; x\
    \ = parent[x]) b.push_back(x);\n        std::reverse(b.begin(), b.end());\n  \
    \      a.insert(a.end(), b.begin(), b.end());\n        return a;\n    }\n\n  \
    \  std::vector<int> path_edges(int u, int v) const {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        int w = lca(u, v);\n        std::vector<int>\
    \ a, b;\n        for (int x = u; x != w; x = parent[x]) a.push_back(parent_edge[x]);\n\
    \        for (int x = v; x != w; x = parent[x]) b.push_back(parent_edge[x]);\n\
    \        std::reverse(b.begin(), b.end());\n        a.insert(a.end(), b.begin(),\
    \ b.end());\n        return a;\n    }\n\n    std::pair<int, int> subtree_range(int\
    \ v) const {\n        check_vertex(v);\n        return {tin[v], tout[v]};\n  \
    \  }\n\n    std::vector<int> subtree_vertices(int v) const {\n        check_vertex(v);\n\
    \        return std::vector<int>(order.begin() + tin[v], order.begin() + tout[v]);\n\
    \    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line 13 \"graph/tree/range_contour_query.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nnamespace internal {\n\nstruct RangeContourPathEntry\
    \ {\n    int centroid;\n    int distance;\n    int subtree;\n};\n\nstruct RangeContourLayout\
    \ {\n    int n = 0;\n    std::vector<std::vector<RangeContourPathEntry>> path;\n\
    \    std::vector<int> all_size;\n    std::vector<int> subtree_size;\n\n    template\
    \ <class EdgeCost>\n    void build(const m1une::graph::Graph<EdgeCost>& graph)\
    \ {\n        n = graph.size();\n        path.assign(n, {});\n        all_size.assign(n,\
    \ 0);\n        subtree_size.assign(n, 0);\n        if (n == 0) return;\n\n#ifndef\
    \ NDEBUG\n        std::vector<int> incidence(graph.edge_count(), 0);\n       \
    \ for (int vertex = 0; vertex < n; vertex++) {\n            for (const auto& edge\
    \ : graph[vertex]) {\n                if (!edge.alive) continue;\n           \
    \     assert(0 <= edge.id && edge.id < graph.edge_count());\n                incidence[edge.id]++;\n\
    \            }\n        }\n        int active_edges = 0;\n        for (int count\
    \ : incidence) {\n            if (count == 0) continue;\n            assert(count\
    \ == 2);\n            active_edges++;\n        }\n        assert(active_edges\
    \ == n - 1);\n#endif\n\n        RootedTree<EdgeCost> rooted(graph, 0);\n     \
    \   assert(int(rooted.order.size()) == n);\n        CentroidDecomposition<EdgeCost>\
    \ decomposition(graph);\n\n        for (int vertex = 0; vertex < n; vertex++)\
    \ {\n            int previous = -1;\n            for (\n                int centroid\
    \ = vertex;\n                centroid != -1;\n                centroid = decomposition.parent[centroid]\n\
    \            ) {\n                int distance = rooted.dist_edges(vertex, centroid);\n\
    \                path[vertex].push_back(\n                    RangeContourPathEntry{centroid,\
    \ distance, previous}\n                );\n                all_size[centroid]\
    \ = std::max(\n                    all_size[centroid],\n                    distance\
    \ + 1\n                );\n                if (previous != -1) {\n           \
    \         subtree_size[previous] = std::max(\n                        subtree_size[previous],\n\
    \                        distance + 1\n                    );\n              \
    \  }\n                previous = centroid;\n            }\n        }\n    }\n\
    };\n\ntemplate <m1une::monoid::IsCommutativeGroup Group>\nclass RangeContourFenwick\
    \ {\n   public:\n    using T = typename Group::value_type;\n\n   private:\n  \
    \  int _n = 0;\n    std::vector<T> _data;\n\n    T prefix_product(int right) const\
    \ {\n        T result = Group::id();\n        while (right > 0) {\n          \
    \  result = Group::op(result, _data[right]);\n            right -= right & -right;\n\
    \        }\n        return result;\n    }\n\n   public:\n    RangeContourFenwick()\
    \ : _data(1, Group::id()) {}\n\n    explicit RangeContourFenwick(int n)\n    \
    \    : _n(n), _data(n + 1, Group::id()) {\n        assert(0 <= n);\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    void apply(int index,\
    \ const T& value) {\n        assert(0 <= index && index < _n);\n        for (index++;\
    \ index <= _n; index += index & -index) {\n            _data[index] = Group::op(_data[index],\
    \ value);\n        }\n    }\n\n    T product(int left, int right) const {\n  \
    \      left = std::max(left, 0);\n        right = std::min(right, _n);\n     \
    \   if (right <= left) return Group::id();\n        return Group::op(\n      \
    \      Group::inv(prefix_product(left)),\n            prefix_product(right)\n\
    \        );\n    }\n\n    void range_apply(int left, int right, const T& value)\
    \ {\n        left = std::max(left, 0);\n        right = std::min(right, _n);\n\
    \        if (right <= left) return;\n        apply(left, value);\n        if (right\
    \ < _n) apply(right, Group::inv(value));\n    }\n\n    T get(int index) const\
    \ {\n        assert(0 <= index && index < _n);\n        return prefix_product(index\
    \ + 1);\n    }\n};\n\n}  // namespace internal\n\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Group>\nclass VertexApplyRangeContourProduct {\n   public:\n    using T = typename\
    \ Group::value_type;\n\n   private:\n    internal::RangeContourLayout _layout;\n\
    \    std::vector<T> _value;\n    std::vector<internal::RangeContourFenwick<Group>>\
    \ _all;\n    std::vector<internal::RangeContourFenwick<Group>> _subtree;\n\n \
    \   void check_vertex(int vertex) const {\n        assert(0 <= vertex && vertex\
    \ < size());\n    }\n\n   public:\n    VertexApplyRangeContourProduct() = default;\n\
    \n    template <class EdgeCost>\n    explicit VertexApplyRangeContourProduct(\n\
    \        const m1une::graph::Graph<EdgeCost>& graph,\n        const std::vector<T>&\
    \ initial = {}\n    ) {\n        build(graph, initial);\n    }\n\n    template\
    \ <class EdgeCost>\n    void build(\n        const m1une::graph::Graph<EdgeCost>&\
    \ graph,\n        const std::vector<T>& initial = {}\n    ) {\n        assert(initial.empty()\
    \ || int(initial.size()) == graph.size());\n        _layout.build(graph);\n  \
    \      const int n = _layout.n;\n        _value.assign(n, Group::id());\n    \
    \    _all.assign(n, internal::RangeContourFenwick<Group>());\n        _subtree.assign(n,\
    \ internal::RangeContourFenwick<Group>());\n        for (int index = 0; index\
    \ < n; index++) {\n            _all[index] =\n                internal::RangeContourFenwick<Group>(_layout.all_size[index]);\n\
    \            _subtree[index] =\n                internal::RangeContourFenwick<Group>(\n\
    \                    _layout.subtree_size[index]\n                );\n       \
    \ }\n        if (!initial.empty()) {\n            for (int vertex = 0; vertex\
    \ < n; vertex++) {\n                apply(vertex, initial[vertex]);\n        \
    \    }\n        }\n    }\n\n    int size() const {\n        return _layout.n;\n\
    \    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\n   \
    \ T get(int vertex) const {\n        check_vertex(vertex);\n        return _value[vertex];\n\
    \    }\n\n    void apply(int vertex, const T& value) {\n        check_vertex(vertex);\n\
    \        _value[vertex] = Group::op(_value[vertex], value);\n        for (const\
    \ auto& entry : _layout.path[vertex]) {\n            _all[entry.centroid].apply(entry.distance,\
    \ value);\n            if (entry.subtree != -1) {\n                _subtree[entry.subtree].apply(entry.distance,\
    \ value);\n            }\n        }\n    }\n\n    void set(int vertex, const T&\
    \ value) {\n        check_vertex(vertex);\n        apply(vertex, Group::op(Group::inv(_value[vertex]),\
    \ value));\n    }\n\n    T prod(int vertex, int left_distance, int right_distance)\
    \ const {\n        check_vertex(vertex);\n        assert(0 <= left_distance &&\
    \ left_distance <= right_distance);\n        T result = Group::id();\n       \
    \ for (const auto& entry : _layout.path[vertex]) {\n            int left = left_distance\
    \ - entry.distance;\n            int right = right_distance - entry.distance;\n\
    \            result = Group::op(\n                result,\n                _all[entry.centroid].product(left,\
    \ right)\n            );\n            if (entry.subtree != -1) {\n           \
    \     result = Group::op(\n                    result,\n                    Group::inv(\n\
    \                        _subtree[entry.subtree].product(left, right)\n      \
    \              )\n                );\n            }\n        }\n        return\
    \ result;\n    }\n};\n\ntemplate <m1une::monoid::IsCommutativeGroup Group>\nclass\
    \ VertexGetRangeContourApply {\n   public:\n    using T = typename Group::value_type;\n\
    \n   private:\n    internal::RangeContourLayout _layout;\n    std::vector<T> _base;\n\
    \    std::vector<internal::RangeContourFenwick<Group>> _all;\n    std::vector<internal::RangeContourFenwick<Group>>\
    \ _subtree;\n\n    void check_vertex(int vertex) const {\n        assert(0 <=\
    \ vertex && vertex < size());\n    }\n\n   public:\n    VertexGetRangeContourApply()\
    \ = default;\n\n    template <class EdgeCost>\n    explicit VertexGetRangeContourApply(\n\
    \        const m1une::graph::Graph<EdgeCost>& graph,\n        const std::vector<T>&\
    \ initial = {}\n    ) {\n        build(graph, initial);\n    }\n\n    template\
    \ <class EdgeCost>\n    void build(\n        const m1une::graph::Graph<EdgeCost>&\
    \ graph,\n        const std::vector<T>& initial = {}\n    ) {\n        assert(initial.empty()\
    \ || int(initial.size()) == graph.size());\n        _layout.build(graph);\n  \
    \      const int n = _layout.n;\n        _base = initial.empty() ? std::vector<T>(n,\
    \ Group::id()) : initial;\n        _all.assign(n, internal::RangeContourFenwick<Group>());\n\
    \        _subtree.assign(n, internal::RangeContourFenwick<Group>());\n       \
    \ for (int index = 0; index < n; index++) {\n            _all[index] =\n     \
    \           internal::RangeContourFenwick<Group>(_layout.all_size[index]);\n \
    \           _subtree[index] =\n                internal::RangeContourFenwick<Group>(\n\
    \                    _layout.subtree_size[index]\n                );\n       \
    \ }\n    }\n\n    int size() const {\n        return _layout.n;\n    }\n\n   \
    \ bool empty() const {\n        return size() == 0;\n    }\n\n    T get(int vertex)\
    \ const {\n        check_vertex(vertex);\n        T result = _base[vertex];\n\
    \        for (const auto& entry : _layout.path[vertex]) {\n            result\
    \ = Group::op(\n                result,\n                _all[entry.centroid].get(entry.distance)\n\
    \            );\n            if (entry.subtree != -1) {\n                result\
    \ = Group::op(\n                    result,\n                    Group::inv(\n\
    \                        _subtree[entry.subtree].get(entry.distance)\n       \
    \             )\n                );\n            }\n        }\n        return\
    \ result;\n    }\n\n    void point_apply(int vertex, const T& value) {\n     \
    \   check_vertex(vertex);\n        _base[vertex] = Group::op(_base[vertex], value);\n\
    \    }\n\n    void set(int vertex, const T& value) {\n        check_vertex(vertex);\n\
    \        _base[vertex] = Group::op(\n            _base[vertex],\n            Group::op(Group::inv(get(vertex)),\
    \ value)\n        );\n    }\n\n    void apply(\n        int vertex,\n        int\
    \ left_distance,\n        int right_distance,\n        const T& value\n    ) {\n\
    \        check_vertex(vertex);\n        assert(0 <= left_distance && left_distance\
    \ <= right_distance);\n        for (const auto& entry : _layout.path[vertex])\
    \ {\n            int left = left_distance - entry.distance;\n            int right\
    \ = right_distance - entry.distance;\n            _all[entry.centroid].range_apply(left,\
    \ right, value);\n            if (entry.subtree != -1) {\n                _subtree[entry.subtree].range_apply(left,\
    \ right, value);\n            }\n        }\n    }\n};\n\ntemplate <class T>\n\
    class VertexAddRangeContourSum\n    : public VertexApplyRangeContourProduct<m1une::monoid::Add<T>>\
    \ {\n   private:\n    using Base = VertexApplyRangeContourProduct<m1une::monoid::Add<T>>;\n\
    \n   public:\n    using Base::Base;\n\n    void add(int vertex, const T& delta)\
    \ {\n        Base::apply(vertex, delta);\n    }\n\n    T sum(int vertex, int left_distance,\
    \ int right_distance) const {\n        return Base::prod(vertex, left_distance,\
    \ right_distance);\n    }\n};\n\ntemplate <class T>\nclass VertexGetRangeContourAdd\n\
    \    : public VertexGetRangeContourApply<m1une::monoid::Add<T>> {\n   private:\n\
    \    using Base = VertexGetRangeContourApply<m1une::monoid::Add<T>>;\n\n   public:\n\
    \    using Base::Base;\n\n    void add(int vertex, const T& delta) {\n       \
    \ Base::point_apply(vertex, delta);\n    }\n};\n\n}  // namespace tree\n}  //\
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_RANGE_CONTOUR_QUERY_HPP\n#define M1UNE_TREE_RANGE_CONTOUR_QUERY_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#include\
    \ \"../../monoid/add.hpp\"\n#include \"../../monoid/concept.hpp\"\n#include \"\
    ../graph.hpp\"\n#include \"centroid_decomposition.hpp\"\n#include \"rooted_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nnamespace internal {\n\nstruct RangeContourPathEntry\
    \ {\n    int centroid;\n    int distance;\n    int subtree;\n};\n\nstruct RangeContourLayout\
    \ {\n    int n = 0;\n    std::vector<std::vector<RangeContourPathEntry>> path;\n\
    \    std::vector<int> all_size;\n    std::vector<int> subtree_size;\n\n    template\
    \ <class EdgeCost>\n    void build(const m1une::graph::Graph<EdgeCost>& graph)\
    \ {\n        n = graph.size();\n        path.assign(n, {});\n        all_size.assign(n,\
    \ 0);\n        subtree_size.assign(n, 0);\n        if (n == 0) return;\n\n#ifndef\
    \ NDEBUG\n        std::vector<int> incidence(graph.edge_count(), 0);\n       \
    \ for (int vertex = 0; vertex < n; vertex++) {\n            for (const auto& edge\
    \ : graph[vertex]) {\n                if (!edge.alive) continue;\n           \
    \     assert(0 <= edge.id && edge.id < graph.edge_count());\n                incidence[edge.id]++;\n\
    \            }\n        }\n        int active_edges = 0;\n        for (int count\
    \ : incidence) {\n            if (count == 0) continue;\n            assert(count\
    \ == 2);\n            active_edges++;\n        }\n        assert(active_edges\
    \ == n - 1);\n#endif\n\n        RootedTree<EdgeCost> rooted(graph, 0);\n     \
    \   assert(int(rooted.order.size()) == n);\n        CentroidDecomposition<EdgeCost>\
    \ decomposition(graph);\n\n        for (int vertex = 0; vertex < n; vertex++)\
    \ {\n            int previous = -1;\n            for (\n                int centroid\
    \ = vertex;\n                centroid != -1;\n                centroid = decomposition.parent[centroid]\n\
    \            ) {\n                int distance = rooted.dist_edges(vertex, centroid);\n\
    \                path[vertex].push_back(\n                    RangeContourPathEntry{centroid,\
    \ distance, previous}\n                );\n                all_size[centroid]\
    \ = std::max(\n                    all_size[centroid],\n                    distance\
    \ + 1\n                );\n                if (previous != -1) {\n           \
    \         subtree_size[previous] = std::max(\n                        subtree_size[previous],\n\
    \                        distance + 1\n                    );\n              \
    \  }\n                previous = centroid;\n            }\n        }\n    }\n\
    };\n\ntemplate <m1une::monoid::IsCommutativeGroup Group>\nclass RangeContourFenwick\
    \ {\n   public:\n    using T = typename Group::value_type;\n\n   private:\n  \
    \  int _n = 0;\n    std::vector<T> _data;\n\n    T prefix_product(int right) const\
    \ {\n        T result = Group::id();\n        while (right > 0) {\n          \
    \  result = Group::op(result, _data[right]);\n            right -= right & -right;\n\
    \        }\n        return result;\n    }\n\n   public:\n    RangeContourFenwick()\
    \ : _data(1, Group::id()) {}\n\n    explicit RangeContourFenwick(int n)\n    \
    \    : _n(n), _data(n + 1, Group::id()) {\n        assert(0 <= n);\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    void apply(int index,\
    \ const T& value) {\n        assert(0 <= index && index < _n);\n        for (index++;\
    \ index <= _n; index += index & -index) {\n            _data[index] = Group::op(_data[index],\
    \ value);\n        }\n    }\n\n    T product(int left, int right) const {\n  \
    \      left = std::max(left, 0);\n        right = std::min(right, _n);\n     \
    \   if (right <= left) return Group::id();\n        return Group::op(\n      \
    \      Group::inv(prefix_product(left)),\n            prefix_product(right)\n\
    \        );\n    }\n\n    void range_apply(int left, int right, const T& value)\
    \ {\n        left = std::max(left, 0);\n        right = std::min(right, _n);\n\
    \        if (right <= left) return;\n        apply(left, value);\n        if (right\
    \ < _n) apply(right, Group::inv(value));\n    }\n\n    T get(int index) const\
    \ {\n        assert(0 <= index && index < _n);\n        return prefix_product(index\
    \ + 1);\n    }\n};\n\n}  // namespace internal\n\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Group>\nclass VertexApplyRangeContourProduct {\n   public:\n    using T = typename\
    \ Group::value_type;\n\n   private:\n    internal::RangeContourLayout _layout;\n\
    \    std::vector<T> _value;\n    std::vector<internal::RangeContourFenwick<Group>>\
    \ _all;\n    std::vector<internal::RangeContourFenwick<Group>> _subtree;\n\n \
    \   void check_vertex(int vertex) const {\n        assert(0 <= vertex && vertex\
    \ < size());\n    }\n\n   public:\n    VertexApplyRangeContourProduct() = default;\n\
    \n    template <class EdgeCost>\n    explicit VertexApplyRangeContourProduct(\n\
    \        const m1une::graph::Graph<EdgeCost>& graph,\n        const std::vector<T>&\
    \ initial = {}\n    ) {\n        build(graph, initial);\n    }\n\n    template\
    \ <class EdgeCost>\n    void build(\n        const m1une::graph::Graph<EdgeCost>&\
    \ graph,\n        const std::vector<T>& initial = {}\n    ) {\n        assert(initial.empty()\
    \ || int(initial.size()) == graph.size());\n        _layout.build(graph);\n  \
    \      const int n = _layout.n;\n        _value.assign(n, Group::id());\n    \
    \    _all.assign(n, internal::RangeContourFenwick<Group>());\n        _subtree.assign(n,\
    \ internal::RangeContourFenwick<Group>());\n        for (int index = 0; index\
    \ < n; index++) {\n            _all[index] =\n                internal::RangeContourFenwick<Group>(_layout.all_size[index]);\n\
    \            _subtree[index] =\n                internal::RangeContourFenwick<Group>(\n\
    \                    _layout.subtree_size[index]\n                );\n       \
    \ }\n        if (!initial.empty()) {\n            for (int vertex = 0; vertex\
    \ < n; vertex++) {\n                apply(vertex, initial[vertex]);\n        \
    \    }\n        }\n    }\n\n    int size() const {\n        return _layout.n;\n\
    \    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\n   \
    \ T get(int vertex) const {\n        check_vertex(vertex);\n        return _value[vertex];\n\
    \    }\n\n    void apply(int vertex, const T& value) {\n        check_vertex(vertex);\n\
    \        _value[vertex] = Group::op(_value[vertex], value);\n        for (const\
    \ auto& entry : _layout.path[vertex]) {\n            _all[entry.centroid].apply(entry.distance,\
    \ value);\n            if (entry.subtree != -1) {\n                _subtree[entry.subtree].apply(entry.distance,\
    \ value);\n            }\n        }\n    }\n\n    void set(int vertex, const T&\
    \ value) {\n        check_vertex(vertex);\n        apply(vertex, Group::op(Group::inv(_value[vertex]),\
    \ value));\n    }\n\n    T prod(int vertex, int left_distance, int right_distance)\
    \ const {\n        check_vertex(vertex);\n        assert(0 <= left_distance &&\
    \ left_distance <= right_distance);\n        T result = Group::id();\n       \
    \ for (const auto& entry : _layout.path[vertex]) {\n            int left = left_distance\
    \ - entry.distance;\n            int right = right_distance - entry.distance;\n\
    \            result = Group::op(\n                result,\n                _all[entry.centroid].product(left,\
    \ right)\n            );\n            if (entry.subtree != -1) {\n           \
    \     result = Group::op(\n                    result,\n                    Group::inv(\n\
    \                        _subtree[entry.subtree].product(left, right)\n      \
    \              )\n                );\n            }\n        }\n        return\
    \ result;\n    }\n};\n\ntemplate <m1une::monoid::IsCommutativeGroup Group>\nclass\
    \ VertexGetRangeContourApply {\n   public:\n    using T = typename Group::value_type;\n\
    \n   private:\n    internal::RangeContourLayout _layout;\n    std::vector<T> _base;\n\
    \    std::vector<internal::RangeContourFenwick<Group>> _all;\n    std::vector<internal::RangeContourFenwick<Group>>\
    \ _subtree;\n\n    void check_vertex(int vertex) const {\n        assert(0 <=\
    \ vertex && vertex < size());\n    }\n\n   public:\n    VertexGetRangeContourApply()\
    \ = default;\n\n    template <class EdgeCost>\n    explicit VertexGetRangeContourApply(\n\
    \        const m1une::graph::Graph<EdgeCost>& graph,\n        const std::vector<T>&\
    \ initial = {}\n    ) {\n        build(graph, initial);\n    }\n\n    template\
    \ <class EdgeCost>\n    void build(\n        const m1une::graph::Graph<EdgeCost>&\
    \ graph,\n        const std::vector<T>& initial = {}\n    ) {\n        assert(initial.empty()\
    \ || int(initial.size()) == graph.size());\n        _layout.build(graph);\n  \
    \      const int n = _layout.n;\n        _base = initial.empty() ? std::vector<T>(n,\
    \ Group::id()) : initial;\n        _all.assign(n, internal::RangeContourFenwick<Group>());\n\
    \        _subtree.assign(n, internal::RangeContourFenwick<Group>());\n       \
    \ for (int index = 0; index < n; index++) {\n            _all[index] =\n     \
    \           internal::RangeContourFenwick<Group>(_layout.all_size[index]);\n \
    \           _subtree[index] =\n                internal::RangeContourFenwick<Group>(\n\
    \                    _layout.subtree_size[index]\n                );\n       \
    \ }\n    }\n\n    int size() const {\n        return _layout.n;\n    }\n\n   \
    \ bool empty() const {\n        return size() == 0;\n    }\n\n    T get(int vertex)\
    \ const {\n        check_vertex(vertex);\n        T result = _base[vertex];\n\
    \        for (const auto& entry : _layout.path[vertex]) {\n            result\
    \ = Group::op(\n                result,\n                _all[entry.centroid].get(entry.distance)\n\
    \            );\n            if (entry.subtree != -1) {\n                result\
    \ = Group::op(\n                    result,\n                    Group::inv(\n\
    \                        _subtree[entry.subtree].get(entry.distance)\n       \
    \             )\n                );\n            }\n        }\n        return\
    \ result;\n    }\n\n    void point_apply(int vertex, const T& value) {\n     \
    \   check_vertex(vertex);\n        _base[vertex] = Group::op(_base[vertex], value);\n\
    \    }\n\n    void set(int vertex, const T& value) {\n        check_vertex(vertex);\n\
    \        _base[vertex] = Group::op(\n            _base[vertex],\n            Group::op(Group::inv(get(vertex)),\
    \ value)\n        );\n    }\n\n    void apply(\n        int vertex,\n        int\
    \ left_distance,\n        int right_distance,\n        const T& value\n    ) {\n\
    \        check_vertex(vertex);\n        assert(0 <= left_distance && left_distance\
    \ <= right_distance);\n        for (const auto& entry : _layout.path[vertex])\
    \ {\n            int left = left_distance - entry.distance;\n            int right\
    \ = right_distance - entry.distance;\n            _all[entry.centroid].range_apply(left,\
    \ right, value);\n            if (entry.subtree != -1) {\n                _subtree[entry.subtree].range_apply(left,\
    \ right, value);\n            }\n        }\n    }\n};\n\ntemplate <class T>\n\
    class VertexAddRangeContourSum\n    : public VertexApplyRangeContourProduct<m1une::monoid::Add<T>>\
    \ {\n   private:\n    using Base = VertexApplyRangeContourProduct<m1une::monoid::Add<T>>;\n\
    \n   public:\n    using Base::Base;\n\n    void add(int vertex, const T& delta)\
    \ {\n        Base::apply(vertex, delta);\n    }\n\n    T sum(int vertex, int left_distance,\
    \ int right_distance) const {\n        return Base::prod(vertex, left_distance,\
    \ right_distance);\n    }\n};\n\ntemplate <class T>\nclass VertexGetRangeContourAdd\n\
    \    : public VertexGetRangeContourApply<m1une::monoid::Add<T>> {\n   private:\n\
    \    using Base = VertexGetRangeContourApply<m1une::monoid::Add<T>>;\n\n   public:\n\
    \    using Base::Base;\n\n    void add(int vertex, const T& delta) {\n       \
    \ Base::point_apply(vertex, delta);\n    }\n};\n\n}  // namespace tree\n}  //\
    \ namespace m1une\n\n#endif  // M1UNE_TREE_RANGE_CONTOUR_QUERY_HPP\n"
  dependsOn:
  - monoid/add.hpp
  - monoid/concept.hpp
  - graph/graph.hpp
  - graph/tree/centroid_decomposition.hpp
  - graph/tree/rooted_tree.hpp
  isVerificationFile: false
  path: graph/tree/range_contour_query.hpp
  requiredBy:
  - graph/tree/all.hpp
  - graph/all.hpp
  timestamp: '2026-07-12 04:12:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - verify/graph/tree/vertex_get_range_contour_add_on_tree.test.cpp
  - verify/graph/tree/tree_algorithms.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/tree/range_contour_query.hpp
layout: document
title: Range Contour Query on Tree
---

## Overview

This header supports commutative-group operations selected by an unweighted
distance interval from a vertex. Its generic interfaces are:

* `VertexApplyRangeContourProduct<Group>` applies a group element at one vertex
  and returns the group product over vertices at distances in `[left, right)`.
* `VertexGetRangeContourApply<Group>` applies a group element to every vertex at
  distances in `[left, right)` and retrieves one vertex value.

The additive convenience wrappers preserve the familiar problem-specific API:

* `VertexAddRangeContourSum<T>` supports vertex additions and sums over all
  vertices at distances in `[left, right)`.
* `VertexGetRangeContourAdd<T>` adds to all vertices at distances in
  `[left, right)` and retrieves one vertex value.

Both structures use centroid decomposition, inclusion-exclusion, and Fenwick
trees. The input must be a connected undirected tree built with `add_edge`.
Edge costs are ignored; distance means the number of edges. Inactive edges are
ignored when validating and building the tree.

## Requirements

`Group` must satisfy `m1une::monoid::IsCommutativeGroup`:

* `using value_type = T;`
* `static T id();`
* `static T op(const T&, const T&);`
* `static T inv(const T&);`

The operation must be associative and commutative, `id()` must be its identity,
and `inv(x)` must return the group inverse. `m1une::monoid::Add<T>` and
`m1une::monoid::Xor<T>` are ready-made policies. Non-invertible operations such
as minimum, maximum, GCD, AND, and OR are not supported because centroid
inclusion-exclusion requires inverses.

## Interfaces

```cpp
template <m1une::monoid::IsCommutativeGroup Group>
class VertexApplyRangeContourProduct {
public:
    using T = typename Group::value_type;

    VertexApplyRangeContourProduct();

    template <class EdgeCost>
    explicit VertexApplyRangeContourProduct(
        const Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    );

    template <class EdgeCost>
    void build(
        const Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    );

    int size() const;
    bool empty() const;
    T get(int vertex) const;
    void apply(int vertex, const T& value);
    void set(int vertex, const T& value);
    T prod(int vertex, int left_distance, int right_distance) const;
};

template <m1une::monoid::IsCommutativeGroup Group>
class VertexGetRangeContourApply {
public:
    using T = typename Group::value_type;

    VertexGetRangeContourApply();

    template <class EdgeCost>
    explicit VertexGetRangeContourApply(
        const Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    );

    template <class EdgeCost>
    void build(
        const Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    );

    int size() const;
    bool empty() const;
    T get(int vertex) const;
    void point_apply(int vertex, const T& value);
    void set(int vertex, const T& value);
    void apply(
        int vertex,
        int left_distance,
        int right_distance,
        const T& value
    );
};

template <class T>
class VertexAddRangeContourSum;

template <class T>
class VertexGetRangeContourAdd;
```

`VertexAddRangeContourSum<T>` is the additive wrapper around
`VertexApplyRangeContourProduct<m1une::monoid::Add<T>>`. It adds `add` and `sum`
as names for `apply` and `prod`. `VertexGetRangeContourAdd<T>` wraps
`VertexGetRangeContourApply<m1une::monoid::Add<T>>` and adds the point method
`add` as a name for `point_apply`.

An omitted `initial` vector initializes every value to `T{}`. An explicitly
provided vector must have one value per vertex. Empty trees are supported.
Distance bounds must satisfy `0 <= left_distance <= right_distance`; bounds
beyond the tree diameter are allowed and are clipped naturally.

## Operations

| Method | Description | Complexity |
| --- | --- | --- |
| `VertexApplyRangeContourProduct()` / `VertexGetRangeContourApply()` | Constructs an empty generic object. | $O(1)$ |
| `template <class EdgeCost> explicit VertexApplyRangeContourProduct(const Graph<EdgeCost>& graph, const std::vector<T>& initial = {})` | Builds the point-apply/range-product structure. | $O(N\log^2 N)$ |
| `template <class EdgeCost> explicit VertexGetRangeContourApply(const Graph<EdgeCost>& graph, const std::vector<T>& initial = {})` | Builds the range-apply/point-get structure. | $O(N\log^2 N)$ |
| `template <class EdgeCost> void build(const Graph<EdgeCost>& graph, const std::vector<T>& initial = {})` | Replaces the current tree and values; available on both classes. | $O(N\log^2 N)$ |
| `int size() const` | Returns the number of vertices. | $O(1)$ |
| `bool empty() const` | Returns whether the structure has no vertices. | $O(1)$ |
| `T VertexApplyRangeContourProduct::get(int vertex) const` | Returns the current vertex value. | $O(1)$ |
| `void VertexApplyRangeContourProduct::apply(int vertex, const T& value)` | Combines one vertex with `value`. | $O(\log^2 N)$ |
| `void VertexApplyRangeContourProduct::set(int vertex, const T& value)` | Replaces one vertex value. | $O(\log^2 N)$ |
| `T VertexApplyRangeContourProduct::prod(int vertex, int left_distance, int right_distance) const` | Returns the group product at distances in `[left_distance, right_distance)`. | $O(\log^2 N)$ |
| `T VertexGetRangeContourApply::get(int vertex) const` | Returns one current vertex value. | $O(\log^2 N)$ |
| `void VertexGetRangeContourApply::point_apply(int vertex, const T& value)` | Combines one vertex with `value`. | $O(1)$ |
| `void VertexGetRangeContourApply::set(int vertex, const T& value)` | Replaces one current vertex value. | $O(\log^2 N)$ |
| `void VertexGetRangeContourApply::apply(int vertex, int left_distance, int right_distance, const T& value)` | Combines every value at distances in `[left_distance, right_distance)` with `value`. | $O(\log^2 N)$ |
| `void VertexAddRangeContourSum::add(int vertex, const T& delta)` | Additive alias of point `apply`. | $O(\log^2 N)$ |
| `T VertexAddRangeContourSum::sum(int vertex, int left_distance, int right_distance) const` | Additive alias of `prod`. | $O(\log^2 N)$ |
| `void VertexGetRangeContourAdd::add(int vertex, const T& delta)` | Additive alias of `point_apply`. | $O(1)$ |

Both structures use $O(N\log N)$ memory. Operations mutate the structure;
queries do not.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/tree/range_contour_query.hpp"
#include "monoid/xor.hpp"

#include <cassert>
#include <vector>

int main() {
    m1une::graph::Graph<> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);

    std::vector<long long> values = {1, 2, 3, 4};
    m1une::tree::VertexAddRangeContourSum<long long> sums(graph, values);
    assert(sums.sum(0, 1, 3) == 9);
    sums.add(2, 5);
    assert(sums.sum(0, 2, 3) == 12);

    m1une::tree::VertexGetRangeContourAdd<long long> additions(graph, values);
    additions.apply(0, 1, 3, 10);
    assert(additions.get(0) == 1);
    assert(additions.get(3) == 14);

    using Xor = m1une::monoid::Xor<unsigned>;
    m1une::tree::VertexApplyRangeContourProduct<Xor> xor_query(
        graph,
        std::vector<unsigned>{1, 2, 4, 8}
    );
    assert(xor_query.prod(0, 1, 3) == (2U ^ 4U ^ 8U));
}
```
