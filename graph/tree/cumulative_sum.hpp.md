---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
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
  - icon: ':heavy_check_mark:'
    path: graph/tree/tree.hpp
    title: Tree
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
    path: verify/graph/tree/tree_cumulative_sum.test.cpp
    title: verify/graph/tree/tree_cumulative_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/tree/cumulative_sum.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n\n#line 1 \"monoid/add.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for addition (Range\
    \ Sum).\ntemplate <typename T>\nstruct Add {\n    using value_type = T;\n    static\
    \ constexpr bool commutative = true;\n\n    // Returns the identity element for\
    \ addition, which is 0.\n    static constexpr T id() {\n        return T(0);\n\
    \    }\n\n    // Returns the sum of a and b.\n    static constexpr T op(const\
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
    \ namespace m1une\n\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#include <array>\n#line\
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
    \ namespace graph\n}  // namespace m1une\n\n\n#line 12 \"graph/tree/cumulative_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\n// Static cumulative products on root\
    \ paths. Values are attached to vertices by\n// default; set EdgeValues to true\
    \ to index them by graph edge id instead.\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Group, bool EdgeValues = false>\nclass TreeCumulativeProduct {\n   public:\n\
    \    using value_type = typename Group::value_type;\n\n   private:\n    int _n\
    \ = 0;\n    int _root = -1;\n    std::vector<int> _parent;\n    std::vector<int>\
    \ _depth;\n    std::vector<int> _head;\n    std::vector<value_type> _prefix;\n\
    \n    void check_vertex(int vertex) const {\n        assert(0 <= vertex && vertex\
    \ < _n);\n    }\n\n   public:\n    TreeCumulativeProduct() = default;\n\n    template\
    \ <class EdgeCost>\n    explicit TreeCumulativeProduct(\n        const m1une::graph::Graph<EdgeCost>&\
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
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_CUMULATIVE_SUM_HPP\n#define M1UNE_TREE_CUMULATIVE_SUM_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"../../monoid/add.hpp\"\n#include \"../../monoid/concept.hpp\"\
    \n#include \"../graph.hpp\"\n\nnamespace m1une {\nnamespace tree {\n\n// Static\
    \ cumulative products on root paths. Values are attached to vertices by\n// default;\
    \ set EdgeValues to true to index them by graph edge id instead.\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Group, bool EdgeValues = false>\nclass TreeCumulativeProduct {\n   public:\n\
    \    using value_type = typename Group::value_type;\n\n   private:\n    int _n\
    \ = 0;\n    int _root = -1;\n    std::vector<int> _parent;\n    std::vector<int>\
    \ _depth;\n    std::vector<int> _head;\n    std::vector<value_type> _prefix;\n\
    \n    void check_vertex(int vertex) const {\n        assert(0 <= vertex && vertex\
    \ < _n);\n    }\n\n   public:\n    TreeCumulativeProduct() = default;\n\n    template\
    \ <class EdgeCost>\n    explicit TreeCumulativeProduct(\n        const m1une::graph::Graph<EdgeCost>&\
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
    }  // namespace m1une\n\n#endif  // M1UNE_TREE_CUMULATIVE_SUM_HPP\n"
  dependsOn:
  - monoid/add.hpp
  - monoid/concept.hpp
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/tree/cumulative_sum.hpp
  requiredBy:
  - graph/all.hpp
  - graph/tree/all.hpp
  - graph/tree/tree.hpp
  timestamp: '2026-08-29 18:27:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/tree/tree_cumulative_sum.test.cpp
  - verify/graph/tree/tree_algorithms.test.cpp
documentation_of: graph/tree/cumulative_sum.hpp
layout: document
title: Tree Cumulative Sum
---

## Overview

`TreeCumulativeSum<T>` preprocesses static values on the vertices of a rooted
tree. It stores the cumulative sum from the root to every vertex, then combines
two root paths at their lowest common ancestor to answer any vertex-path sum.

`TreeEdgeCumulativeSum<T>` is the edge-valued variant. Its input vector is
indexed by graph edge id, and its path sums exclude vertices and include exactly
the edges on the path.

The underlying `TreeCumulativeProduct<Group>` and
`TreeEdgeCumulativeProduct<Group>` types provide the same operations for any
commutative group, such as xor. The additive wrappers use
`m1une::monoid::Add<T>`.

```cpp
#include "graph/graph.hpp"
#include "graph/tree/cumulative_sum.hpp"
```

## Requirements and Behavior

The graph must be an undirected tree consisting of active edges. Vertex values
must have size `graph.size()`. Edge values must have size
`graph.edge_count()` and are looked up using the ids returned by `add_edge`.
Indices are zero-based.

For `TreeCumulativeProduct<Group>`, `Group` must satisfy
`m1une::monoid::IsCommutativeGroup`: it supplies `value_type`, `id()`, `op(a,
b)`, and `inv(a)`. Associativity, commutativity, the identity law, and the
inverse law are semantic requirements.

Construction does not mutate the graph or the input values. The values are
static; rebuild the object after changing them.

## Types

| Type | Values represented |
| --- | --- |
| `TreeCumulativeProduct<Group>` | A group value on every vertex. |
| `TreeEdgeCumulativeProduct<Group>` | A group value for every graph edge id. |
| `TreeCumulativeSum<T>` | A numeric value on every vertex. |
| `TreeEdgeCumulativeSum<T>` | A numeric value for every graph edge id. |

## Interface

The following methods are shared by all four types. `value_type` is `T` for the
sum wrappers and `Group::value_type` for the product types.

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Default constructor | `TreeCumulativeProduct()` or `TreeCumulativeSum()` | Constructs an empty object. | $O(1)$ |
| Constructor | `TreeCumulativeProduct(const Graph<EdgeCost>& graph, const std::vector<value_type>& values, int root = 0)` | Builds cumulative products from `root`. | $O(N)$ time and space |
| Constructor | `TreeCumulativeSum(const Graph<EdgeCost>& graph, const std::vector<T>& values, int root = 0)` | Builds cumulative sums from `root`. | $O(N)$ time and space |
| `build` | `void build(const Graph<EdgeCost>& graph, const std::vector<value_type>& values, int root = 0)` | Rebuilds the object. | $O(N)$ time and space |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether there are no vertices. | $O(1)$ |
| `root` | `int root() const` | Returns the selected root, or `-1` when empty. | $O(1)$ |
| `lca` | `int lca(int first, int second) const` | Returns the lowest common ancestor under the selected root. | $O(\log N)$ |
| `prod` | `value_type prod(int vertex) const` | Returns the product on the root-to-`vertex` path. | $O(1)$ |
| `prod` | `value_type prod(int first, int second) const` | Returns the product on the simple path between the vertices. | $O(\log N)$ |
| `sum` | `T sum(int vertex) const` | Additive wrapper for the root-to-`vertex` sum. | $O(1)$ |
| `sum` | `T sum(int first, int second) const` | Additive wrapper for the simple-path sum. | $O(\log N)$ |

For vertex values, both endpoints of a path are included. In particular,
`sum(v, v)` is the value at `v`. For edge values, `sum(v, v)` is zero, and
`sum(root, v)` contains the edges strictly below the root on that path.

Choose `T` large enough to hold every root-path sum and the intermediate values
formed while combining two prefixes.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/tree/cumulative_sum.hpp"

#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<int> graph(5);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
    graph.add_edge(3, 4);

    std::vector<long long> value = {2, 3, 5, 7, 11};
    m1une::tree::TreeCumulativeSum<long long> sum(graph, value, 0);

    std::cout << sum.sum(4) << '\n';    // 2 + 3 + 7 + 11 = 23
    std::cout << sum.sum(2, 4) << '\n'; // 5 + 3 + 7 + 11 = 26
}
```
