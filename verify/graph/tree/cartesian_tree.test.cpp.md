---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/cartesian_tree.hpp
    title: Cartesian Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 1 \"verify/graph/tree/cartesian_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <iostream>\n#include <random>\n\
    #include <vector>\n\n#line 1 \"graph/tree/cartesian_tree.hpp\"\n\n\n\n#line 5\
    \ \"graph/tree/cartesian_tree.hpp\"\n#include <cstddef>\n#line 7 \"graph/tree/cartesian_tree.hpp\"\
    \n#include <limits>\n#include <utility>\n#line 10 \"graph/tree/cartesian_tree.hpp\"\
    \n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using\
    \ cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n   \
    \ bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true)\
    \ {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ =\
    \ true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\
    \n    int other(int v) const {\n        assert(v == from || v == to);\n      \
    \  return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph\
    \ {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
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
    \ m1une\n\n\n#line 12 \"graph/tree/cartesian_tree.hpp\"\n\nnamespace m1une {\n\
    namespace tree {\n\nstruct CartesianTree {\n    int root;\n    std::vector<int>\
    \ parent;\n    std::vector<int> left;\n    std::vector<int> right;\n\n   private:\n\
    \    int _n;\n\n    void check_vertex(int v) const {\n        assert(0 <= v &&\
    \ v < _n);\n    }\n\n   public:\n    CartesianTree() : root(-1), _n(0) {}\n\n\
    \    template <class T, class Compare = std::less<T>>\n    explicit CartesianTree(const\
    \ std::vector<T>& a, Compare comp = Compare()) : root(-1), _n(0) {\n        build(a,\
    \ comp);\n    }\n\n    template <class T, class Compare = std::less<T>>\n    void\
    \ build(const std::vector<T>& a, Compare comp = Compare()) {\n        assert(a.size()\
    \ <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n        _n =\
    \ int(a.size());\n        root = -1;\n        parent.assign(_n, -1);\n       \
    \ left.assign(_n, -1);\n        right.assign(_n, -1);\n\n        std::vector<int>\
    \ stack;\n        stack.reserve(_n);\n        for (int i = 0; i < _n; i++) {\n\
    \            int last = -1;\n            while (!stack.empty() && comp(a[i], a[stack.back()]))\
    \ {\n                last = stack.back();\n                stack.pop_back();\n\
    \            }\n            if (last != -1) {\n                left[i] = last;\n\
    \                parent[last] = i;\n            }\n            if (!stack.empty())\
    \ {\n                right[stack.back()] = i;\n                parent[i] = stack.back();\n\
    \            }\n            stack.push_back(i);\n        }\n\n        if (!stack.empty())\
    \ root = stack.front();\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    int\
    \ parent_or_self(int v) const {\n        check_vertex(v);\n        return parent[v]\
    \ == -1 ? v : parent[v];\n    }\n\n    std::vector<int> parent_with_root_self()\
    \ const {\n        std::vector<int> result = parent;\n        if (root != -1)\
    \ result[root] = root;\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> edges() const {\n        std::vector<std::pair<int, int>> result;\n  \
    \      if (_n == 0) return result;\n        result.reserve(_n - 1);\n        for\
    \ (int v = 0; v < _n; v++) {\n            if (parent[v] != -1) result.emplace_back(parent[v],\
    \ v);\n        }\n        return result;\n    }\n\n    m1une::graph::Graph<int>\
    \ to_graph() const {\n        m1une::graph::Graph<int> g(_n);\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (parent[v] != -1) g.add_edge(parent[v],\
    \ v);\n        }\n        return g;\n    }\n};\n\ntemplate <class T, class Compare\
    \ = std::less<T>>\nCartesianTree cartesian_tree(const std::vector<T>& a, Compare\
    \ comp = Compare()) {\n    CartesianTree result;\n    result.build(a, comp);\n\
    \    return result;\n}\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line\
    \ 11 \"verify/graph/tree/cartesian_tree.test.cpp\"\n\nstruct ExpectedCartesianTree\
    \ {\n    int root;\n    std::vector<int> parent;\n    std::vector<int> left;\n\
    \    std::vector<int> right;\n};\n\ntemplate <class T, class Compare>\nint build_naive_cartesian_tree(\n\
    \    const std::vector<T>& a,\n    int l,\n    int r,\n    int p,\n    Compare\
    \ comp,\n    ExpectedCartesianTree& result\n) {\n    if (l == r) return -1;\n\
    \    int best = l;\n    for (int i = l + 1; i < r; i++) {\n        if (comp(a[i],\
    \ a[best])) best = i;\n    }\n    result.parent[best] = p;\n    result.left[best]\
    \ = build_naive_cartesian_tree(a, l, best, best, comp, result);\n    result.right[best]\
    \ = build_naive_cartesian_tree(a, best + 1, r, best, comp, result);\n    return\
    \ best;\n}\n\ntemplate <class T, class Compare>\nExpectedCartesianTree naive_cartesian_tree(const\
    \ std::vector<T>& a, Compare comp) {\n    ExpectedCartesianTree result;\n    int\
    \ n = int(a.size());\n    result.root = -1;\n    result.parent.assign(n, -1);\n\
    \    result.left.assign(n, -1);\n    result.right.assign(n, -1);\n    result.root\
    \ = build_naive_cartesian_tree(a, 0, n, -1, comp, result);\n    return result;\n\
    }\n\nvoid collect_inorder(const m1une::tree::CartesianTree& tree, int v, std::vector<int>&\
    \ order) {\n    if (v == -1) return;\n    collect_inorder(tree, tree.left[v],\
    \ order);\n    order.push_back(v);\n    collect_inorder(tree, tree.right[v], order);\n\
    }\n\ntemplate <class T, class Compare>\nvoid assert_cartesian_tree(const std::vector<T>&\
    \ a, Compare comp) {\n    const int n = int(a.size());\n    m1une::tree::CartesianTree\
    \ tree(a, comp);\n    ExpectedCartesianTree expected = naive_cartesian_tree(a,\
    \ comp);\n\n    assert(tree.size() == n);\n    assert(tree.empty() == (n == 0));\n\
    \    assert(tree.root == expected.root);\n    assert(tree.parent == expected.parent);\n\
    \    assert(tree.left == expected.left);\n    assert(tree.right == expected.right);\n\
    \n    std::vector<int> inorder;\n    inorder.reserve(n);\n    collect_inorder(tree,\
    \ tree.root, inorder);\n    assert(int(inorder.size()) == n);\n    for (int i\
    \ = 0; i < n; i++) assert(inorder[i] == i);\n\n    std::vector<int> parent_self\
    \ = tree.parent_with_root_self();\n    assert(int(parent_self.size()) == n);\n\
    \    for (int v = 0; v < n; v++) {\n        if (tree.parent[v] == -1) {\n    \
    \        assert(v == tree.root);\n            assert(parent_self[v] == v);\n \
    \           assert(tree.parent_or_self(v) == v);\n        } else {\n         \
    \   assert(parent_self[v] == tree.parent[v]);\n            assert(tree.parent_or_self(v)\
    \ == tree.parent[v]);\n            assert(!comp(a[v], a[tree.parent[v]]));\n \
    \       }\n        if (tree.left[v] != -1) {\n            assert(tree.left[v]\
    \ < v);\n            assert(tree.parent[tree.left[v]] == v);\n        }\n    \
    \    if (tree.right[v] != -1) {\n            assert(v < tree.right[v]);\n    \
    \        assert(tree.parent[tree.right[v]] == v);\n        }\n    }\n\n    std::vector<std::pair<int,\
    \ int>> edges = tree.edges();\n    assert(int(edges.size()) == std::max(0, n -\
    \ 1));\n    auto graph = tree.to_graph();\n    assert(graph.size() == n);\n  \
    \  assert(graph.edge_count() == std::max(0, n - 1));\n}\n\nvoid run_local_tests()\
    \ {\n    assert_cartesian_tree(std::vector<int>(), std::less<int>());\n    assert_cartesian_tree(std::vector<int>{3,\
    \ 1, 4, 0, 2}, std::less<int>());\n    assert_cartesian_tree(std::vector<int>{3,\
    \ 1, 4, 0, 2}, std::greater<int>());\n    assert_cartesian_tree(std::vector<int>{2,\
    \ 2, 2, 1, 1, 3}, std::less<int>());\n\n    std::mt19937 rng(123456789);\n   \
    \ for (int n = 0; n <= 60; n++) {\n        for (int test = 0; test < 100; test++)\
    \ {\n            std::vector<int> values(n);\n            for (int& x : values)\
    \ x = int(rng() % 11) - 5;\n            assert_cartesian_tree(values, std::less<int>());\n\
    \            assert_cartesian_tree(values, std::greater<int>());\n        }\n\
    \    }\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    run_local_tests();\n\n    int n;\n    std::cin >> n;\n    std::vector<long\
    \ long> a(n);\n    for (int i = 0; i < n; i++) std::cin >> a[i];\n\n    m1une::tree::CartesianTree\
    \ tree(a);\n    std::vector<int> parent = tree.parent_with_root_self();\n    for\
    \ (int i = 0; i < n; i++) {\n        if (i) std::cout << ' ';\n        std::cout\
    \ << parent[i];\n    }\n    std::cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <functional>\n#include <iostream>\n\
    #include <random>\n#include <vector>\n\n#include \"../../../graph/tree/cartesian_tree.hpp\"\
    \n\nstruct ExpectedCartesianTree {\n    int root;\n    std::vector<int> parent;\n\
    \    std::vector<int> left;\n    std::vector<int> right;\n};\n\ntemplate <class\
    \ T, class Compare>\nint build_naive_cartesian_tree(\n    const std::vector<T>&\
    \ a,\n    int l,\n    int r,\n    int p,\n    Compare comp,\n    ExpectedCartesianTree&\
    \ result\n) {\n    if (l == r) return -1;\n    int best = l;\n    for (int i =\
    \ l + 1; i < r; i++) {\n        if (comp(a[i], a[best])) best = i;\n    }\n  \
    \  result.parent[best] = p;\n    result.left[best] = build_naive_cartesian_tree(a,\
    \ l, best, best, comp, result);\n    result.right[best] = build_naive_cartesian_tree(a,\
    \ best + 1, r, best, comp, result);\n    return best;\n}\n\ntemplate <class T,\
    \ class Compare>\nExpectedCartesianTree naive_cartesian_tree(const std::vector<T>&\
    \ a, Compare comp) {\n    ExpectedCartesianTree result;\n    int n = int(a.size());\n\
    \    result.root = -1;\n    result.parent.assign(n, -1);\n    result.left.assign(n,\
    \ -1);\n    result.right.assign(n, -1);\n    result.root = build_naive_cartesian_tree(a,\
    \ 0, n, -1, comp, result);\n    return result;\n}\n\nvoid collect_inorder(const\
    \ m1une::tree::CartesianTree& tree, int v, std::vector<int>& order) {\n    if\
    \ (v == -1) return;\n    collect_inorder(tree, tree.left[v], order);\n    order.push_back(v);\n\
    \    collect_inorder(tree, tree.right[v], order);\n}\n\ntemplate <class T, class\
    \ Compare>\nvoid assert_cartesian_tree(const std::vector<T>& a, Compare comp)\
    \ {\n    const int n = int(a.size());\n    m1une::tree::CartesianTree tree(a,\
    \ comp);\n    ExpectedCartesianTree expected = naive_cartesian_tree(a, comp);\n\
    \n    assert(tree.size() == n);\n    assert(tree.empty() == (n == 0));\n    assert(tree.root\
    \ == expected.root);\n    assert(tree.parent == expected.parent);\n    assert(tree.left\
    \ == expected.left);\n    assert(tree.right == expected.right);\n\n    std::vector<int>\
    \ inorder;\n    inorder.reserve(n);\n    collect_inorder(tree, tree.root, inorder);\n\
    \    assert(int(inorder.size()) == n);\n    for (int i = 0; i < n; i++) assert(inorder[i]\
    \ == i);\n\n    std::vector<int> parent_self = tree.parent_with_root_self();\n\
    \    assert(int(parent_self.size()) == n);\n    for (int v = 0; v < n; v++) {\n\
    \        if (tree.parent[v] == -1) {\n            assert(v == tree.root);\n  \
    \          assert(parent_self[v] == v);\n            assert(tree.parent_or_self(v)\
    \ == v);\n        } else {\n            assert(parent_self[v] == tree.parent[v]);\n\
    \            assert(tree.parent_or_self(v) == tree.parent[v]);\n            assert(!comp(a[v],\
    \ a[tree.parent[v]]));\n        }\n        if (tree.left[v] != -1) {\n       \
    \     assert(tree.left[v] < v);\n            assert(tree.parent[tree.left[v]]\
    \ == v);\n        }\n        if (tree.right[v] != -1) {\n            assert(v\
    \ < tree.right[v]);\n            assert(tree.parent[tree.right[v]] == v);\n  \
    \      }\n    }\n\n    std::vector<std::pair<int, int>> edges = tree.edges();\n\
    \    assert(int(edges.size()) == std::max(0, n - 1));\n    auto graph = tree.to_graph();\n\
    \    assert(graph.size() == n);\n    assert(graph.edge_count() == std::max(0,\
    \ n - 1));\n}\n\nvoid run_local_tests() {\n    assert_cartesian_tree(std::vector<int>(),\
    \ std::less<int>());\n    assert_cartesian_tree(std::vector<int>{3, 1, 4, 0, 2},\
    \ std::less<int>());\n    assert_cartesian_tree(std::vector<int>{3, 1, 4, 0, 2},\
    \ std::greater<int>());\n    assert_cartesian_tree(std::vector<int>{2, 2, 2, 1,\
    \ 1, 3}, std::less<int>());\n\n    std::mt19937 rng(123456789);\n    for (int\
    \ n = 0; n <= 60; n++) {\n        for (int test = 0; test < 100; test++) {\n \
    \           std::vector<int> values(n);\n            for (int& x : values) x =\
    \ int(rng() % 11) - 5;\n            assert_cartesian_tree(values, std::less<int>());\n\
    \            assert_cartesian_tree(values, std::greater<int>());\n        }\n\
    \    }\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    run_local_tests();\n\n    int n;\n    std::cin >> n;\n    std::vector<long\
    \ long> a(n);\n    for (int i = 0; i < n; i++) std::cin >> a[i];\n\n    m1une::tree::CartesianTree\
    \ tree(a);\n    std::vector<int> parent = tree.parent_with_root_self();\n    for\
    \ (int i = 0; i < n; i++) {\n        if (i) std::cout << ' ';\n        std::cout\
    \ << parent[i];\n    }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - graph/tree/cartesian_tree.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/tree/cartesian_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 19:47:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/tree/cartesian_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/tree/cartesian_tree.test.cpp
- /verify/verify/graph/tree/cartesian_tree.test.cpp.html
title: verify/graph/tree/cartesian_tree.test.cpp
---
