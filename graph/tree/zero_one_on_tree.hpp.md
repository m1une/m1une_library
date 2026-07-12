---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/rooted_tree.hpp
    title: Rooted Tree
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
    path: verify/graph/tree/zero_one_on_tree.test.cpp
    title: verify/graph/tree/zero_one_on_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/tree/zero_one_on_tree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <set>\n#include <vector>\n\n#line 1 \"graph/tree/rooted_tree.hpp\"\n\n\
    \n\n#include <algorithm>\n#line 7 \"graph/tree/rooted_tree.hpp\"\n\n#line 1 \"\
    graph/graph.hpp\"\n\n\n\n#line 5 \"graph/graph.hpp\"\n#include <utility>\n#line\
    \ 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
    \ T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int\
    \ to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1),\
    \ cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1),\
    \ int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
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
    \ m1une\n\n\n#line 9 \"graph/tree/rooted_tree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ tree {\n\ntemplate <class T = int>\nstruct RootedTree {\n    using cost_type\
    \ = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n    int root;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    std::vector<int> depth;\n  \
    \  std::vector<T> dist;\n    std::vector<int> subtree_size;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n    std::vector<std::vector<int>>\
    \ up;\n\n   private:\n    int _n;\n    int _log;\n\n    void check_vertex(int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        assert(tin[v] != -1);\n\
    \    }\n\n   public:\n    RootedTree() : root(-1), _n(0), _log(0) {}\n    explicit\
    \ RootedTree(const m1une::graph::Graph<T>& g, int root_ = 0) {\n        build(g,\
    \ root_);\n    }\n\n    void build(const m1une::graph::Graph<T>& g, int root_\
    \ = 0) {\n        _n = g.size();\n        root = _n == 0 ? -1 : root_;\n     \
    \   _log = 1;\n        while ((1U << _log) <= (unsigned int)(std::max(1, _n)))\
    \ _log++;\n\n        parent.assign(_n, -1);\n        parent_edge.assign(_n, -1);\n\
    \        depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n        subtree_size.assign(_n,\
    \ 0);\n        tin.assign(_n, -1);\n        tout.assign(_n, -1);\n        order.clear();\n\
    \        order.reserve(_n);\n        up.assign(_log, std::vector<int>(_n, -1));\n\
    \n        if (_n == 0) return;\n        assert(0 <= root && root < _n);\n\n  \
    \      struct Frame {\n            int v;\n            int state;\n        };\n\
    \n        std::vector<char> visited(_n, false);\n        std::vector<Frame> stack;\n\
    \        stack.push_back({root, 0});\n        visited[root] = true;\n        int\
    \ timer = 0;\n\n        while (!stack.empty()) {\n            Frame frame = stack.back();\n\
    \            stack.pop_back();\n            int v = frame.v;\n            if (frame.state\
    \ == 0) {\n                tin[v] = timer++;\n                order.push_back(v);\n\
    \                up[0][v] = parent[v];\n                for (int k = 1; k < _log;\
    \ k++) {\n                    int p = up[k - 1][v];\n                    up[k][v]\
    \ = p == -1 ? -1 : up[k - 1][p];\n                }\n\n                stack.push_back({v,\
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
    \    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line 9 \"graph/tree/zero_one_on_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ninline long long zero_one_on_tree(const\
    \ std::vector<int>& parent,\n                                  const std::vector<int>&\
    \ value) {\n    const int n = int(parent.size());\n    assert(int(value.size())\
    \ == n);\n    if (n == 0) return 0;\n\n    int root = -1;\n    std::vector<std::vector<int>>\
    \ children(n);\n    for (int v = 0; v < n; v++) {\n        assert(value[v] ==\
    \ 0 || value[v] == 1);\n        if (parent[v] == -1) {\n            assert(root\
    \ == -1);\n            root = v;\n        } else {\n            assert(0 <= parent[v]\
    \ && parent[v] < n && parent[v] != v);\n            children[parent[v]].push_back(v);\n\
    \        }\n    }\n    assert(root != -1);\n\n    std::vector<int> stack(1, root);\n\
    \    std::vector<char> visited(n, false);\n    visited[root] = true;\n    int\
    \ visited_count = 0;\n    while (!stack.empty()) {\n        const int v = stack.back();\n\
    \        stack.pop_back();\n        visited_count++;\n        for (int child :\
    \ children[v]) {\n            assert(!visited[child]);\n            visited[child]\
    \ = true;\n            stack.push_back(child);\n        }\n    }\n    assert(visited_count\
    \ == n);\n\n    struct Component {\n        long long zeros;\n        long long\
    \ ones;\n        int vertex;\n    };\n    struct Compare {\n        bool operator()(const\
    \ Component& lhs, const Component& rhs) const {\n            const long long lhs_product\
    \ = lhs.zeros * rhs.ones;\n            const long long rhs_product = rhs.zeros\
    \ * lhs.ones;\n            if (lhs_product != rhs_product) return lhs_product\
    \ < rhs_product;\n            return lhs.vertex < rhs.vertex;\n        }\n   \
    \ };\n\n    std::vector<long long> zeros(n), ones(n);\n    std::vector<int> dsu(n);\n\
    \    std::set<Component, Compare> components;\n    for (int v = 0; v < n; v++)\
    \ {\n        zeros[v] = value[v] == 0;\n        ones[v] = value[v] == 1;\n   \
    \     dsu[v] = v;\n        if (v != root) components.insert(Component{zeros[v],\
    \ ones[v], v});\n    }\n\n    auto leader = [&](int v) {\n        int result =\
    \ v;\n        while (dsu[result] != result) result = dsu[result];\n        while\
    \ (dsu[v] != v) {\n            const int next = dsu[v];\n            dsu[v] =\
    \ result;\n            v = next;\n        }\n        return result;\n    };\n\n\
    \    long long answer = 0;\n    while (!components.empty()) {\n        auto it\
    \ = components.end();\n        --it;\n        const Component child = *it;\n \
    \       components.erase(it);\n\n        const int p = leader(parent[child.vertex]);\n\
    \        if (p != root) {\n            const int erased = int(components.erase(Component{zeros[p],\
    \ ones[p], p}));\n            assert(erased == 1);\n        }\n\n        answer\
    \ += ones[p] * zeros[child.vertex];\n        zeros[p] += zeros[child.vertex];\n\
    \        ones[p] += ones[child.vertex];\n        dsu[child.vertex] = p;\n\n  \
    \      if (p != root) components.insert(Component{zeros[p], ones[p], p});\n  \
    \  }\n    return answer;\n}\n\ntemplate <class T>\nlong long zero_one_on_tree(const\
    \ m1une::graph::Graph<T>& graph,\n                           const std::vector<int>&\
    \ value, int root = 0) {\n    const int n = graph.size();\n    assert(int(value.size())\
    \ == n);\n    if (n == 0) return 0;\n    assert(0 <= root && root < n);\n    assert(int(graph.edges().size())\
    \ == n - 1);\n\n    RootedTree<T> rooted_tree(graph, root);\n    assert(int(rooted_tree.order.size())\
    \ == n);\n    return zero_one_on_tree(rooted_tree.parent, value);\n}\n\n}  //\
    \ namespace tree\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_ZERO_ONE_ON_TREE_HPP\n#define M1UNE_TREE_ZERO_ONE_ON_TREE_HPP\
    \ 1\n\n#include <cassert>\n#include <set>\n#include <vector>\n\n#include \"rooted_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ninline long long zero_one_on_tree(const\
    \ std::vector<int>& parent,\n                                  const std::vector<int>&\
    \ value) {\n    const int n = int(parent.size());\n    assert(int(value.size())\
    \ == n);\n    if (n == 0) return 0;\n\n    int root = -1;\n    std::vector<std::vector<int>>\
    \ children(n);\n    for (int v = 0; v < n; v++) {\n        assert(value[v] ==\
    \ 0 || value[v] == 1);\n        if (parent[v] == -1) {\n            assert(root\
    \ == -1);\n            root = v;\n        } else {\n            assert(0 <= parent[v]\
    \ && parent[v] < n && parent[v] != v);\n            children[parent[v]].push_back(v);\n\
    \        }\n    }\n    assert(root != -1);\n\n    std::vector<int> stack(1, root);\n\
    \    std::vector<char> visited(n, false);\n    visited[root] = true;\n    int\
    \ visited_count = 0;\n    while (!stack.empty()) {\n        const int v = stack.back();\n\
    \        stack.pop_back();\n        visited_count++;\n        for (int child :\
    \ children[v]) {\n            assert(!visited[child]);\n            visited[child]\
    \ = true;\n            stack.push_back(child);\n        }\n    }\n    assert(visited_count\
    \ == n);\n\n    struct Component {\n        long long zeros;\n        long long\
    \ ones;\n        int vertex;\n    };\n    struct Compare {\n        bool operator()(const\
    \ Component& lhs, const Component& rhs) const {\n            const long long lhs_product\
    \ = lhs.zeros * rhs.ones;\n            const long long rhs_product = rhs.zeros\
    \ * lhs.ones;\n            if (lhs_product != rhs_product) return lhs_product\
    \ < rhs_product;\n            return lhs.vertex < rhs.vertex;\n        }\n   \
    \ };\n\n    std::vector<long long> zeros(n), ones(n);\n    std::vector<int> dsu(n);\n\
    \    std::set<Component, Compare> components;\n    for (int v = 0; v < n; v++)\
    \ {\n        zeros[v] = value[v] == 0;\n        ones[v] = value[v] == 1;\n   \
    \     dsu[v] = v;\n        if (v != root) components.insert(Component{zeros[v],\
    \ ones[v], v});\n    }\n\n    auto leader = [&](int v) {\n        int result =\
    \ v;\n        while (dsu[result] != result) result = dsu[result];\n        while\
    \ (dsu[v] != v) {\n            const int next = dsu[v];\n            dsu[v] =\
    \ result;\n            v = next;\n        }\n        return result;\n    };\n\n\
    \    long long answer = 0;\n    while (!components.empty()) {\n        auto it\
    \ = components.end();\n        --it;\n        const Component child = *it;\n \
    \       components.erase(it);\n\n        const int p = leader(parent[child.vertex]);\n\
    \        if (p != root) {\n            const int erased = int(components.erase(Component{zeros[p],\
    \ ones[p], p}));\n            assert(erased == 1);\n        }\n\n        answer\
    \ += ones[p] * zeros[child.vertex];\n        zeros[p] += zeros[child.vertex];\n\
    \        ones[p] += ones[child.vertex];\n        dsu[child.vertex] = p;\n\n  \
    \      if (p != root) components.insert(Component{zeros[p], ones[p], p});\n  \
    \  }\n    return answer;\n}\n\ntemplate <class T>\nlong long zero_one_on_tree(const\
    \ m1une::graph::Graph<T>& graph,\n                           const std::vector<int>&\
    \ value, int root = 0) {\n    const int n = graph.size();\n    assert(int(value.size())\
    \ == n);\n    if (n == 0) return 0;\n    assert(0 <= root && root < n);\n    assert(int(graph.edges().size())\
    \ == n - 1);\n\n    RootedTree<T> rooted_tree(graph, root);\n    assert(int(rooted_tree.order.size())\
    \ == n);\n    return zero_one_on_tree(rooted_tree.parent, value);\n}\n\n}  //\
    \ namespace tree\n}  // namespace m1une\n\n#endif  // M1UNE_TREE_ZERO_ONE_ON_TREE_HPP\n"
  dependsOn:
  - graph/tree/rooted_tree.hpp
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/tree/zero_one_on_tree.hpp
  requiredBy:
  - graph/tree/all.hpp
  - graph/all.hpp
  timestamp: '2026-07-11 19:47:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/tree/tree_algorithms.test.cpp
  - verify/graph/tree/zero_one_on_tree.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/tree/zero_one_on_tree.hpp
layout: document
title: 01 on Tree
---

## Overview

Each vertex of a rooted tree is labeled `0` or `1`. Consider every ordering of
the vertices in which each parent appears before its children. This header
computes the minimum possible number of inversions in the resulting binary
sequence.

The algorithm maintains contracted vertex groups. A non-root group with the
largest ratio

\[
\frac{\text{number of zeros}}{\text{number of ones}}
\]

is appended to its current parent group. A group containing no ones has
infinite ratio. A set maintains the ratios, and a disjoint-set structure finds
the current parent group after contractions.

## Public Interface

```cpp
long long zero_one_on_tree(
    const std::vector<int>& parent,
    const std::vector<int>& value);

template <class T>
long long zero_one_on_tree(
    const m1une::graph::Graph<T>& graph,
    const std::vector<int>& value,
    int root = 0);
```

The parent-array overload uses zero-based vertices. Exactly one vertex must
have parent `-1`; every other entry must be a valid parent and the resulting
directed edges must form a tree. Each entry of `value` must be `0` or `1`.

The graph overload expects a connected undirected tree built with `add_edge`.
Inactive edges are ignored. For an empty graph it returns `0` without using
`root`.

## Complexity

| Function | Time | Extra memory |
| --- | --- | --- |
| `zero_one_on_tree(parent, value)` | $O(N \log N)$ | $O(N)$ |
| `zero_one_on_tree(graph, value, root)` | $O(N \log N)$ | $O(N)$ |

The answer can be quadratic in `N`, so the return type is `long long`. Neither
overload mutates its arguments.

## Example

```cpp
#include "graph/tree/zero_one_on_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> parent = {-1, 0, 0, 1, 2, 2};
    std::vector<int> value = {0, 1, 1, 0, 0, 0};

    std::cout << m1une::tree::zero_one_on_tree(parent, value) << '\n';
}
```
