---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/cumulative_sum.hpp
    title: Tree Cumulative Sum
  - icon: ':heavy_check_mark:'
    path: graph/tree/rooted_tree.hpp
    title: Rooted Tree
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
    PROBLEM: https://judge.yosupo.jp/problem/tree_diameter
    links:
    - https://judge.yosupo.jp/problem/tree_diameter
  bundledCode: "#line 1 \"verify/graph/tree/tree_cumulative_sum.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/tree_diameter\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <random>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#include <array>\n#line 6 \"graph/graph.hpp\"\n#include <utility>\n#line\
    \ 8 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
    \ T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int\
    \ to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1),\
    \ cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1),\
    \ int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    struct EdgePositions {\n        std::array<std::pair<int,\
    \ int>, 2> value{};\n        int size = 0;\n\n        void push_back(std::pair<int,\
    \ int> position) {\n            assert(size < 2);\n            value[size++] =\
    \ position;\n        }\n    };\n\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<EdgePositions> _edge_positions;\n\n   public:\n    Graph()\
    \ : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
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
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (int i =\
    \ 0; i < _edge_positions[id].size; ++i) {\n            auto [v, idx] = _edge_positions[id].value[i];\n\
    \            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(_edge_positions[id].size\
    \ != 0);\n        auto [v, idx] = _edge_positions[id].value[0];\n        return\
    \ _g[v][idx].alive;\n    }\n\n    const std::vector<edge_type>& operator[](int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\
    \n    std::vector<edge_type>& operator[](int v) {\n        assert(0 <= v && v\
    \ < _n);\n        return _g[v];\n    }\n\n    const std::vector<std::vector<edge_type>>&\
    \ adjacency() const {\n        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>&\
    \ adjacency() {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool\
    \ include_inactive = false) const {\n        std::vector<edge_type> result;\n\
    \        result.reserve(_edge_count);\n        std::vector<char> used(_edge_count,\
    \ false);\n        for (int v = 0; v < _n; v++) {\n            for (const auto&\
    \ e : _g[v]) {\n                if (!include_inactive && !e.alive) continue;\n\
    \                if (0 <= e.id && e.id < _edge_count) {\n                    if\
    \ (used[e.id]) continue;\n                    used[e.id] = true;\n           \
    \     }\n                result.push_back(e);\n            }\n        }\n    \
    \    return result;\n    }\n\n    Graph reversed() const {\n        Graph result(_n);\n\
    \        result._edge_count = _edge_count;\n        result._edge_positions.assign(_edge_count,\
    \ {});\n        for (int v = 0; v < _n; v++) {\n            for (const auto& e\
    \ : _g[v]) {\n                int idx = int(result._g[e.to].size());\n       \
    \         result._g[e.to].push_back(edge_type(e.to, e.from, e.cost, e.id, e.alive));\n\
    \                if (0 <= e.id && e.id < _edge_count) result._edge_positions[e.id].push_back({e.to,\
    \ idx});\n            }\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/tree/cumulative_sum.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 8 \"graph/tree/cumulative_sum.hpp\"\n\n#line\
    \ 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid\
    \ for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n    using value_type\
    \ = T;\n    static constexpr bool commutative = true;\n\n    // Returns the identity\
    \ element for addition, which is 0.\n    static constexpr T id() {\n        return\
    \ T(0);\n    }\n\n    // Returns the sum of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) {\n        return a + b;\n    }\n\n    static constexpr T\
    \ inv(const T& x) {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\
    \nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 12 \"graph/tree/cumulative_sum.hpp\"\n\nnamespace\
    \ m1une {\nnamespace tree {\n\n// Static cumulative products on root paths. Values\
    \ are attached to vertices by\n// default; set EdgeValues to true to index them\
    \ by graph edge id instead.\ntemplate <m1une::monoid::IsCommutativeGroup Group,\
    \ bool EdgeValues = false>\nclass TreeCumulativeProduct {\n   public:\n    using\
    \ value_type = typename Group::value_type;\n\n   private:\n    int _n = 0;\n \
    \   int _root = -1;\n    std::vector<int> _parent;\n    std::vector<int> _depth;\n\
    \    std::vector<int> _head;\n    std::vector<value_type> _prefix;\n\n    void\
    \ check_vertex(int vertex) const {\n        assert(0 <= vertex && vertex < _n);\n\
    \    }\n\n   public:\n    TreeCumulativeProduct() = default;\n\n    template <class\
    \ EdgeCost>\n    explicit TreeCumulativeProduct(\n        const m1une::graph::Graph<EdgeCost>&\
    \ graph,\n        const std::vector<value_type>& values,\n        int root = 0\n\
    \    ) {\n        build(graph, values, root);\n    }\n\n    template <class EdgeCost>\n\
    \    void build(\n        const m1une::graph::Graph<EdgeCost>& graph,\n      \
    \  const std::vector<value_type>& values,\n        int root = 0\n    ) {\n   \
    \     _n = graph.size();\n        _root = _n == 0 ? -1 : root;\n        assert(\n\
    \            int(values.size())\n            == (EdgeValues ? graph.edge_count()\
    \ : graph.size())\n        );\n\n        _parent.assign(_n, -2);\n        _depth.assign(_n,\
    \ 0);\n        _head.assign(_n, -1);\n        _prefix.assign(_n, Group::id());\n\
    \        if (_n == 0) return;\n        assert(0 <= root && root < _n);\n\n   \
    \     std::vector<int> parent_edge(_n, -1);\n        std::vector<int> order;\n\
    \        order.reserve(_n);\n        std::vector<int> stack = {root};\n      \
    \  _parent[root] = -1;\n        while (!stack.empty()) {\n            int vertex\
    \ = stack.back();\n            stack.pop_back();\n            order.push_back(vertex);\n\
    \            for (const auto& edge : graph[vertex]) {\n                if (!edge.alive\
    \ || _parent[edge.to] != -2) continue;\n                _parent[edge.to] = vertex;\n\
    \                parent_edge[edge.to] = edge.id;\n                _depth[edge.to]\
    \ = _depth[vertex] + 1;\n                stack.push_back(edge.to);\n         \
    \   }\n        }\n        assert(int(order.size()) == _n);\n\n        std::vector<int>\
    \ subtree_size(_n, 1);\n        std::vector<int> heavy(_n, -1);\n        for (int\
    \ index = _n - 1; index > 0; index--) {\n            int vertex = order[index];\n\
    \            int parent = _parent[vertex];\n            subtree_size[parent] +=\
    \ subtree_size[vertex];\n            if (\n                heavy[parent] == -1\n\
    \                || subtree_size[heavy[parent]] < subtree_size[vertex]\n     \
    \       ) {\n                heavy[parent] = vertex;\n            }\n        }\n\
    \n        std::vector<std::pair<int, int>> starts;\n        starts.emplace_back(root,\
    \ root);\n        while (!starts.empty()) {\n            auto [start, head] =\
    \ starts.back();\n            starts.pop_back();\n            for (\n        \
    \        int vertex = start;\n                vertex != -1;\n                vertex\
    \ = heavy[vertex]\n            ) {\n                _head[vertex] = head;\n  \
    \              for (const auto& edge : graph[vertex]) {\n                    if\
    \ (\n                        edge.alive && _parent[edge.to] == vertex\n      \
    \                  && edge.to != heavy[vertex]\n                    ) {\n    \
    \                    starts.emplace_back(edge.to, edge.to);\n                \
    \    }\n                }\n            }\n        }\n\n        if constexpr (!EdgeValues)\
    \ _prefix[root] = values[root];\n        for (int vertex : order) {\n        \
    \    if (vertex == root) continue;\n            if constexpr (EdgeValues) {\n\
    \                assert(0 <= parent_edge[vertex]);\n                _prefix[vertex]\
    \ = Group::op(\n                    _prefix[_parent[vertex]],\n              \
    \      values[parent_edge[vertex]]\n                );\n            } else {\n\
    \                _prefix[vertex] = Group::op(\n                    _prefix[_parent[vertex]],\n\
    \                    values[vertex]\n                );\n            }\n     \
    \   }\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int root() const {\n\
    \        return _root;\n    }\n\n    int lca(int first, int second) const {\n\
    \        check_vertex(first);\n        check_vertex(second);\n        while (_head[first]\
    \ != _head[second]) {\n            if (_depth[_head[first]] < _depth[_head[second]])\
    \ {\n                std::swap(first, second);\n            }\n            first\
    \ = _parent[_head[first]];\n        }\n        return _depth[first] < _depth[second]\
    \ ? first : second;\n    }\n\n    // Product on the root-to-vertex path. The root\
    \ vertex is included for\n    // vertex values; no edge lies above it in edge-value\
    \ mode.\n    value_type prod(int vertex) const {\n        check_vertex(vertex);\n\
    \        return _prefix[vertex];\n    }\n\n    // Product on the simple path from\
    \ first to second. Both endpoints are\n    // included for vertex values.\n  \
    \  value_type prod(int first, int second) const {\n        int ancestor = lca(first,\
    \ second);\n        value_type result = Group::op(_prefix[first], _prefix[second]);\n\
    \        result = Group::op(result, Group::inv(_prefix[ancestor]));\n        if\
    \ constexpr (EdgeValues) {\n            result = Group::op(result, Group::inv(_prefix[ancestor]));\n\
    \        } else if (_parent[ancestor] != -1) {\n            result = Group::op(\n\
    \                result,\n                Group::inv(_prefix[_parent[ancestor]])\n\
    \            );\n        }\n        return result;\n    }\n};\n\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Group>\nusing TreeEdgeCumulativeProduct = TreeCumulativeProduct<Group, true>;\n\
    \ntemplate <class T, bool EdgeValues = false>\nclass TreeCumulativeSum\n    :\
    \ public TreeCumulativeProduct<m1une::monoid::Add<T>, EdgeValues> {\n   private:\n\
    \    using Base =\n        TreeCumulativeProduct<m1une::monoid::Add<T>, EdgeValues>;\n\
    \n   public:\n    using Base::Base;\n\n    T sum(int vertex) const {\n       \
    \ return Base::prod(vertex);\n    }\n\n    T sum(int first, int second) const\
    \ {\n        return Base::prod(first, second);\n    }\n};\n\ntemplate <class T>\n\
    using TreeEdgeCumulativeSum = TreeCumulativeSum<T, true>;\n\n}  // namespace tree\n\
    }  // namespace m1une\n\n\n#line 1 \"graph/tree/rooted_tree.hpp\"\n\n\n\n#line\
    \ 7 \"graph/tree/rooted_tree.hpp\"\n\n#line 9 \"graph/tree/rooted_tree.hpp\"\n\
    \nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct RootedTree\
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
    \    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#line 6 \"utilities/fast_io.hpp\"\n#include <cerrno>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n\
    #include <type_traits>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\
    \nnamespace m1une {\nnamespace utilities {\n\nstruct FastOutput;\n\nnamespace\
    \ internal {\n\n// Shared with the convenience helpers in template.hpp.\ninline\
    \ FastOutput* standard_output_instance = nullptr;\n\n// Detect std::begin(x),\
    \ std::end(x).\ntemplate <class T, class = void>\nstruct is_range : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \          _range_separator(' ') {\n        if (_stream == stdout\n          \
    \  && internal::standard_output_instance == nullptr) {\n            internal::standard_output_instance\
    \ = this;\n        }\n    }\n\n    FastOutput(const FastOutput&) = delete;\n \
    \   FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n        if (internal::standard_output_instance == this) {\n\
    \            internal::standard_output_instance = nullptr;\n        }\n    }\n\
    \n    void flush() {\n        if (_position != 0) {\n            std::fwrite(_buffer,\
    \ 1, _position, _stream);\n            _position = 0;\n        }\n        std::fflush(_stream);\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        std::size_t position = 0;\n        while (position\
    \ < s.size()) {\n            if (_position == buffer_size) flush();\n        \
    \    const std::size_t copied =\n                std::min<std::size_t>(buffer_size\
    \ - _position, s.size() - position);\n            std::memcpy(_buffer + _position,\
    \ s.data() + position, copied);\n            _position += int(copied);\n     \
    \       position += copied;\n        }\n    }\n\n    void write(char c) {\n  \
    \      write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 12 \"verify/graph/tree/tree_cumulative_sum.test.cpp\"\
    \n\nstruct XorGroup {\n    using value_type = std::uint64_t;\n\n    static value_type\
    \ id() {\n        return 0;\n    }\n\n    static value_type op(value_type first,\
    \ value_type second) {\n        return first ^ second;\n    }\n\n    static value_type\
    \ inv(value_type value) {\n        return value;\n    }\n};\n\nvoid test_random()\
    \ {\n    std::mt19937_64 random(123456789);\n    for (int test = 0; test < 100;\
    \ test++) {\n        int n = 1 + int(random() % 50);\n        m1une::graph::Graph<int>\
    \ graph(n);\n        std::vector<long long> edge_value;\n        edge_value.reserve(n\
    \ - 1);\n        for (int vertex = 1; vertex < n; vertex++) {\n            int\
    \ parent = int(random() % vertex);\n            int edge = graph.add_edge(parent,\
    \ vertex);\n            assert(edge == int(edge_value.size()));\n            edge_value.push_back(static_cast<long\
    \ long>(random() % 201) - 100);\n        }\n\n        std::vector<long long> vertex_value(n);\n\
    \        std::vector<std::uint64_t> xor_value(n);\n        for (int vertex = 0;\
    \ vertex < n; vertex++) {\n            vertex_value[vertex] =\n              \
    \  static_cast<long long>(random() % 201) - 100;\n            xor_value[vertex]\
    \ = random();\n        }\n\n        int root = int(random() % n);\n        m1une::tree::RootedTree<int>\
    \ rooted(graph, root);\n        m1une::tree::TreeCumulativeSum<long long> vertex_sum(\n\
    \            graph,\n            vertex_value,\n            root\n        );\n\
    \        m1une::tree::TreeEdgeCumulativeSum<long long> edge_sum(\n           \
    \ graph,\n            edge_value,\n            root\n        );\n        m1une::tree::TreeCumulativeProduct<XorGroup>\
    \ vertex_xor(\n            graph,\n            xor_value,\n            root\n\
    \        );\n\n        assert(vertex_sum.size() == n);\n        assert(vertex_sum.root()\
    \ == root);\n        for (int vertex = 0; vertex < n; vertex++) {\n          \
    \  long long expected_vertex_sum = 0;\n            long long expected_edge_sum\
    \ = 0;\n            std::uint64_t expected_xor = 0;\n            for (\n     \
    \           int current = vertex;\n                current != -1;\n          \
    \      current = rooted.parent[current]\n            ) {\n                expected_vertex_sum\
    \ += vertex_value[current];\n                expected_xor ^= xor_value[current];\n\
    \                if (rooted.parent[current] != -1) {\n                    expected_edge_sum\
    \ +=\n                        edge_value[rooted.parent_edge[current]];\n     \
    \           }\n            }\n            assert(vertex_sum.sum(vertex) == expected_vertex_sum);\n\
    \            assert(edge_sum.sum(vertex) == expected_edge_sum);\n            assert(vertex_xor.prod(vertex)\
    \ == expected_xor);\n        }\n\n        for (int query = 0; query < 200; query++)\
    \ {\n            int first = int(random() % n);\n            int second = int(random()\
    \ % n);\n            std::vector<int> path = rooted.path(first, second);\n   \
    \         std::vector<int> path_edges = rooted.path_edges(first, second);\n\n\
    \            long long expected_vertex_sum = 0;\n            std::uint64_t expected_xor\
    \ = 0;\n            for (int vertex : path) {\n                expected_vertex_sum\
    \ += vertex_value[vertex];\n                expected_xor ^= xor_value[vertex];\n\
    \            }\n            long long expected_edge_sum = 0;\n            for\
    \ (int edge : path_edges) expected_edge_sum += edge_value[edge];\n\n         \
    \   assert(\n                vertex_sum.lca(first, second) == rooted.lca(first,\
    \ second)\n            );\n            assert(vertex_sum.sum(first, second) ==\
    \ expected_vertex_sum);\n            assert(edge_sum.sum(first, second) == expected_edge_sum);\n\
    \            assert(vertex_xor.prod(first, second) == expected_xor);\n       \
    \ }\n    }\n\n    m1une::graph::Graph<int> graph;\n    std::vector<long long>\
    \ values;\n    m1une::tree::TreeCumulativeSum<long long> empty(graph, values);\n\
    \    assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.root()\
    \ == -1);\n}\n\nint main() {\n    test_random();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n\n    int n;\n    input >>\
    \ n;\n    m1une::graph::Graph<long long> graph(n);\n    std::vector<long long>\
    \ edge_value(n - 1);\n    for (int edge = 0; edge < n - 1; edge++) {\n       \
    \ int first, second;\n        long long weight;\n        input >> first >> second\
    \ >> weight;\n        int id = graph.add_edge(first, second, weight);\n      \
    \  edge_value[id] = weight;\n    }\n\n    m1une::tree::TreeEdgeCumulativeSum<long\
    \ long> from_zero(\n        graph,\n        edge_value,\n        0\n    );\n \
    \   int first = 0;\n    for (int vertex = 1; vertex < n; vertex++) {\n       \
    \ if (from_zero.sum(first) < from_zero.sum(vertex)) first = vertex;\n    }\n\n\
    \    m1une::tree::TreeEdgeCumulativeSum<long long> from_first(\n        graph,\n\
    \        edge_value,\n        first\n    );\n    int second = first;\n    for\
    \ (int vertex = 0; vertex < n; vertex++) {\n        if (from_first.sum(second)\
    \ < from_first.sum(vertex)) second = vertex;\n    }\n\n    m1une::tree::RootedTree<long\
    \ long> rooted(graph, first);\n    std::vector<int> path = rooted.path(first,\
    \ second);\n    output << from_first.sum(first, second) << ' ' << path.size()\
    \ << '\\n';\n    for (int index = 0; index < int(path.size()); index++) {\n  \
    \      if (index != 0) output << ' ';\n        output << path[index];\n    }\n\
    \    output << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_diameter\"\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <random>\n#include <vector>\n\n#include\
    \ \"../../../graph/graph.hpp\"\n#include \"../../../graph/tree/cumulative_sum.hpp\"\
    \n#include \"../../../graph/tree/rooted_tree.hpp\"\n#include \"../../../utilities/fast_io.hpp\"\
    \n\nstruct XorGroup {\n    using value_type = std::uint64_t;\n\n    static value_type\
    \ id() {\n        return 0;\n    }\n\n    static value_type op(value_type first,\
    \ value_type second) {\n        return first ^ second;\n    }\n\n    static value_type\
    \ inv(value_type value) {\n        return value;\n    }\n};\n\nvoid test_random()\
    \ {\n    std::mt19937_64 random(123456789);\n    for (int test = 0; test < 100;\
    \ test++) {\n        int n = 1 + int(random() % 50);\n        m1une::graph::Graph<int>\
    \ graph(n);\n        std::vector<long long> edge_value;\n        edge_value.reserve(n\
    \ - 1);\n        for (int vertex = 1; vertex < n; vertex++) {\n            int\
    \ parent = int(random() % vertex);\n            int edge = graph.add_edge(parent,\
    \ vertex);\n            assert(edge == int(edge_value.size()));\n            edge_value.push_back(static_cast<long\
    \ long>(random() % 201) - 100);\n        }\n\n        std::vector<long long> vertex_value(n);\n\
    \        std::vector<std::uint64_t> xor_value(n);\n        for (int vertex = 0;\
    \ vertex < n; vertex++) {\n            vertex_value[vertex] =\n              \
    \  static_cast<long long>(random() % 201) - 100;\n            xor_value[vertex]\
    \ = random();\n        }\n\n        int root = int(random() % n);\n        m1une::tree::RootedTree<int>\
    \ rooted(graph, root);\n        m1une::tree::TreeCumulativeSum<long long> vertex_sum(\n\
    \            graph,\n            vertex_value,\n            root\n        );\n\
    \        m1une::tree::TreeEdgeCumulativeSum<long long> edge_sum(\n           \
    \ graph,\n            edge_value,\n            root\n        );\n        m1une::tree::TreeCumulativeProduct<XorGroup>\
    \ vertex_xor(\n            graph,\n            xor_value,\n            root\n\
    \        );\n\n        assert(vertex_sum.size() == n);\n        assert(vertex_sum.root()\
    \ == root);\n        for (int vertex = 0; vertex < n; vertex++) {\n          \
    \  long long expected_vertex_sum = 0;\n            long long expected_edge_sum\
    \ = 0;\n            std::uint64_t expected_xor = 0;\n            for (\n     \
    \           int current = vertex;\n                current != -1;\n          \
    \      current = rooted.parent[current]\n            ) {\n                expected_vertex_sum\
    \ += vertex_value[current];\n                expected_xor ^= xor_value[current];\n\
    \                if (rooted.parent[current] != -1) {\n                    expected_edge_sum\
    \ +=\n                        edge_value[rooted.parent_edge[current]];\n     \
    \           }\n            }\n            assert(vertex_sum.sum(vertex) == expected_vertex_sum);\n\
    \            assert(edge_sum.sum(vertex) == expected_edge_sum);\n            assert(vertex_xor.prod(vertex)\
    \ == expected_xor);\n        }\n\n        for (int query = 0; query < 200; query++)\
    \ {\n            int first = int(random() % n);\n            int second = int(random()\
    \ % n);\n            std::vector<int> path = rooted.path(first, second);\n   \
    \         std::vector<int> path_edges = rooted.path_edges(first, second);\n\n\
    \            long long expected_vertex_sum = 0;\n            std::uint64_t expected_xor\
    \ = 0;\n            for (int vertex : path) {\n                expected_vertex_sum\
    \ += vertex_value[vertex];\n                expected_xor ^= xor_value[vertex];\n\
    \            }\n            long long expected_edge_sum = 0;\n            for\
    \ (int edge : path_edges) expected_edge_sum += edge_value[edge];\n\n         \
    \   assert(\n                vertex_sum.lca(first, second) == rooted.lca(first,\
    \ second)\n            );\n            assert(vertex_sum.sum(first, second) ==\
    \ expected_vertex_sum);\n            assert(edge_sum.sum(first, second) == expected_edge_sum);\n\
    \            assert(vertex_xor.prod(first, second) == expected_xor);\n       \
    \ }\n    }\n\n    m1une::graph::Graph<int> graph;\n    std::vector<long long>\
    \ values;\n    m1une::tree::TreeCumulativeSum<long long> empty(graph, values);\n\
    \    assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.root()\
    \ == -1);\n}\n\nint main() {\n    test_random();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n\n    int n;\n    input >>\
    \ n;\n    m1une::graph::Graph<long long> graph(n);\n    std::vector<long long>\
    \ edge_value(n - 1);\n    for (int edge = 0; edge < n - 1; edge++) {\n       \
    \ int first, second;\n        long long weight;\n        input >> first >> second\
    \ >> weight;\n        int id = graph.add_edge(first, second, weight);\n      \
    \  edge_value[id] = weight;\n    }\n\n    m1une::tree::TreeEdgeCumulativeSum<long\
    \ long> from_zero(\n        graph,\n        edge_value,\n        0\n    );\n \
    \   int first = 0;\n    for (int vertex = 1; vertex < n; vertex++) {\n       \
    \ if (from_zero.sum(first) < from_zero.sum(vertex)) first = vertex;\n    }\n\n\
    \    m1une::tree::TreeEdgeCumulativeSum<long long> from_first(\n        graph,\n\
    \        edge_value,\n        first\n    );\n    int second = first;\n    for\
    \ (int vertex = 0; vertex < n; vertex++) {\n        if (from_first.sum(second)\
    \ < from_first.sum(vertex)) second = vertex;\n    }\n\n    m1une::tree::RootedTree<long\
    \ long> rooted(graph, first);\n    std::vector<int> path = rooted.path(first,\
    \ second);\n    output << from_first.sum(first, second) << ' ' << path.size()\
    \ << '\\n';\n    for (int index = 0; index < int(path.size()); index++) {\n  \
    \      if (index != 0) output << ' ';\n        output << path[index];\n    }\n\
    \    output << '\\n';\n}\n"
  dependsOn:
  - graph/graph.hpp
  - graph/tree/cumulative_sum.hpp
  - monoid/add.hpp
  - monoid/concept.hpp
  - graph/graph.hpp
  - graph/tree/rooted_tree.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/tree/tree_cumulative_sum.test.cpp
  requiredBy: []
  timestamp: '2026-08-29 18:27:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/tree/tree_cumulative_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/tree/tree_cumulative_sum.test.cpp
- /verify/verify/graph/tree/tree_cumulative_sum.test.cpp.html
title: verify/graph/tree/tree_cumulative_sum.test.cpp
---
