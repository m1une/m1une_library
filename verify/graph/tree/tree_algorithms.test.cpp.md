---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sparse_table.hpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/all.hpp
    title: Tree All
  - icon: ':heavy_check_mark:'
    path: graph/tree/cartesian_tree.hpp
    title: Cartesian Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/centroid_decomposition.hpp
    title: Centroid Decomposition
  - icon: ':heavy_check_mark:'
    path: graph/tree/diameter.hpp
    title: Tree Diameter
  - icon: ':heavy_check_mark:'
    path: graph/tree/distance_frequency.hpp
    title: Tree Distance Frequency
  - icon: ':heavy_check_mark:'
    path: graph/tree/dsu_on_tree.hpp
    title: DSU on Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/euler_tour.hpp
    title: Euler Tour
  - icon: ':heavy_check_mark:'
    path: graph/tree/heavy_light_decomposition.hpp
    title: Heavy Light Decomposition
  - icon: ':heavy_check_mark:'
    path: graph/tree/range_contour_query.hpp
    title: Range Contour Query on Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/rerooting_dp.hpp
    title: Rerooting DP
  - icon: ':heavy_check_mark:'
    path: graph/tree/rerooting_static_top_tree.hpp
    title: Rerooting Static Top Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/rooted_tree.hpp
    title: Rooted Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/sparse_table_lca.hpp
    title: Sparse Table LCA
  - icon: ':heavy_check_mark:'
    path: graph/tree/static_top_tree.hpp
    title: Static Top Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/tree.hpp
    title: Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/tree_hash.hpp
    title: Hash of Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/virtual_tree.hpp
    title: Virtual Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/zero_one_on_tree.hpp
    title: 01 on Tree
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <iostream>\n#include <numeric>\n\
    #include <random>\n#include <set>\n#include <vector>\n\n#include \"../../../graph/graph.hpp\"\
    \n#include \"../../../graph/tree/all.hpp\"\n\nusing m1une::graph::Graph;\n\ntemplate\
    \ <class Hld>\nstd::vector<int> expand_segments(const Hld& hld, const std::vector<m1une::tree::HldPathSegment>&\
    \ segments) {\n    std::vector<int> result;\n    for (auto seg : segments) {\n\
    \        if (seg.reversed) {\n            for (int i = seg.r - 1; i >= seg.l;\
    \ i--) result.push_back(hld.order[i]);\n        } else {\n            for (int\
    \ i = seg.l; i < seg.r; i++) result.push_back(hld.order[i]);\n        }\n    }\n\
    \    return result;\n}\n\nGraph<long long> sample_tree() {\n    Graph<long long>\
    \ g(7);\n    g.add_edge(0, 1, 3);\n    g.add_edge(0, 2, 2);\n    g.add_edge(1,\
    \ 3, 4);\n    g.add_edge(1, 4, 1);\n    g.add_edge(2, 5, 6);\n    g.add_edge(5,\
    \ 6, 2);\n    return g;\n}\n\nvoid test_rooted_tree() {\n    auto g = sample_tree();\n\
    \    m1une::tree::RootedTree<long long> tree(g, 0);\n\n    assert(tree.size()\
    \ == 7);\n    assert(!tree.empty());\n    assert(tree.root == 0);\n    assert(tree.parent[0]\
    \ == -1);\n    assert(tree.parent[3] == 1);\n    assert(tree.depth[6] == 3);\n\
    \    assert(tree.dist[6] == 10);\n    assert(tree.subtree_size[0] == 7);\n   \
    \ assert(tree.subtree_size[1] == 3);\n    assert(tree.is_ancestor(1, 4));\n  \
    \  assert(!tree.is_ancestor(2, 4));\n    assert(tree.in_subtree(4, 1));\n\n  \
    \  assert(tree.kth_ancestor(6, 0) == 6);\n    assert(tree.kth_ancestor(6, 1) ==\
    \ 5);\n    assert(tree.kth_ancestor(6, 3) == 0);\n    assert(tree.kth_ancestor(6,\
    \ 4) == -1);\n    assert(tree.lca(3, 4) == 1);\n    assert(tree.lca(3, 6) == 0);\n\
    \    assert(tree.dist_edges(3, 6) == 5);\n    assert(tree.dist_cost(3, 6) == 17);\n\
    \    assert(tree.jump(3, 6, 0) == 3);\n    assert(tree.jump(3, 6, 1) == 1);\n\
    \    assert(tree.jump(3, 6, 2) == 0);\n    assert(tree.jump(3, 6, 3) == 2);\n\
    \    assert(tree.jump(3, 6, 5) == 6);\n    assert(tree.jump(3, 6, 6) == -1);\n\
    \n    std::vector<int> expected_path = {3, 1, 0, 2, 5, 6};\n    assert(tree.path(3,\
    \ 6) == expected_path);\n    std::vector<int> expected_edges = {2, 0, 1, 4, 5};\n\
    \    assert(tree.path_edges(3, 6) == expected_edges);\n\n    auto [l, r] = tree.subtree_range(1);\n\
    \    assert(r - l == 3);\n    auto sub = tree.subtree_vertices(1);\n    std::sort(sub.begin(),\
    \ sub.end());\n    assert((sub == std::vector<int>{1, 3, 4}));\n}\n\nvoid test_euler_tour()\
    \ {\n    auto g = sample_tree();\n    m1une::tree::EulerTour<long long> tour(g,\
    \ 0);\n\n    std::vector<int> expected_order = {0, 1, 3, 4, 2, 5, 6};\n    assert(tour.size()\
    \ == 7);\n    assert(tour.visited_size() == 7);\n    assert(tour.root == 0);\n\
    \    assert(tour.order == expected_order);\n    assert(tour.parent[6] == 5);\n\
    \    assert(tour.parent_edge[6] == 5);\n    assert(tour.depth[6] == 3);\n    assert(tour.dist[6]\
    \ == 10);\n    assert(tour.subtree_size[1] == 3);\n    assert(tour.is_ancestor(1,\
    \ 4));\n    assert(!tour.is_ancestor(2, 4));\n\n    auto [l, r] = tour.subtree_range(1);\n\
    \    assert(l == 1);\n    assert(r == 4);\n    auto [el, er] = tour.subtree_range(1,\
    \ true);\n    assert(el == 2);\n    assert(er == 4);\n\n    std::vector<int> subtree\
    \ = tour.subtree_vertices(1);\n    std::sort(subtree.begin(), subtree.end());\n\
    \    std::vector<int> expected_subtree = {1, 3, 4};\n    assert(subtree == expected_subtree);\n\
    }\n\nvoid test_sparse_table_lca() {\n    auto g = sample_tree();\n    m1une::tree::RootedTree<long\
    \ long> tree(g, 0);\n    m1une::tree::SparseTableLca<long long> lca(g, 0);\n\n\
    \    assert(lca.size() == 7);\n    assert(!lca.empty());\n    assert(lca.root\
    \ == 0);\n    assert(lca.parent[0] == -1);\n    assert(lca.parent[6] == 5);\n\
    \    assert(lca.depth[6] == 3);\n    assert(lca.dist[6] == 10);\n    assert(lca.euler.size()\
    \ == 13);\n    assert(lca.first[0] == 0);\n    assert(lca.is_ancestor(2, 6));\n\
    \    assert(!lca.is_ancestor(1, 6));\n    assert(lca.in_subtree(6, 2));\n\n  \
    \  for (int u = 0; u < 7; u++) {\n        for (int v = 0; v < 7; v++) {\n    \
    \        assert(lca.lca(u, v) == tree.lca(u, v));\n            assert(lca.dist_edges(u,\
    \ v) == tree.dist_edges(u, v));\n            assert(lca.dist_cost(u, v) == tree.dist_cost(u,\
    \ v));\n        }\n    }\n\n    auto [l, r] = lca.subtree_range(2);\n    assert(r\
    \ - l == 3);\n    std::vector<int> subtree;\n    for (int i = l; i < r; i++) subtree.push_back(lca.order[i]);\n\
    \    std::sort(subtree.begin(), subtree.end());\n    assert((subtree == std::vector<int>{2,\
    \ 5, 6}));\n}\n\nvoid test_virtual_tree() {\n    auto graph = sample_tree();\n\
    \    m1une::tree::VirtualTree<long long> builder(graph, 0);\n\n    auto virtual_tree\
    \ = builder.build(std::vector<int>{3, 4, 6, 3});\n    std::vector<int> expected_vertices\
    \ = {0, 1, 3, 4, 6};\n    assert(virtual_tree.vertex == expected_vertices);\n\
    \    assert(virtual_tree.parent == std::vector<int>({-1, 0, 1, 1, 0}));\n    assert(virtual_tree.parent_edge_count\
    \ == std::vector<int>({0, 1, 1, 1, 3}));\n    assert(virtual_tree.parent_cost\
    \ == std::vector<long long>({0, 3, 4, 1, 10}));\n    assert(virtual_tree.is_key\
    \ == std::vector<bool>({false, false, true, true, true}));\n    assert(virtual_tree.children[0]\
    \ == std::vector<int>({1, 4}));\n    assert(virtual_tree.children[1] == std::vector<int>({2,\
    \ 3}));\n    assert(virtual_tree.root() == 0);\n    assert(virtual_tree.root_vertex()\
    \ == 0);\n    assert(virtual_tree.edge_count() == 4);\n\n    auto singleton =\
    \ builder.build(std::vector<int>{5, 5});\n    assert(singleton.size() == 1);\n\
    \    assert(singleton.vertex[0] == 5);\n    assert(singleton.parent[0] == -1);\n\
    \    assert(singleton.is_key[0]);\n\n    auto empty = builder.build({});\n   \
    \ assert(empty.empty());\n    assert(empty.root() == -1);\n    assert(empty.root_vertex()\
    \ == -1);\n    assert(empty.edge_count() == 0);\n\n    std::mt19937 random(123456789);\n\
    \    for (int test = 0; test < 100; test++) {\n        int n = 1 + random() %\
    \ 200;\n        Graph<long long> random_graph(n);\n        for (int v = 1; v <\
    \ n; v++) {\n            int parent = random() % v;\n            long long cost\
    \ = 1 + random() % 1000000;\n            random_graph.add_edge(parent, v, cost);\n\
    \        }\n        m1une::tree::VirtualTree<long long> random_builder(random_graph,\
    \ 0);\n        const auto& lca = random_builder.lca_data();\n        for (int\
    \ query = 0; query < 100; query++) {\n            int k = random() % (2 * n +\
    \ 1);\n            std::vector<int> keys(k);\n            for (int& v : keys)\
    \ v = random() % n;\n            auto result = random_builder.build(keys);\n\n\
    \            std::sort(keys.begin(), keys.end(), [&](int u, int v) {\n       \
    \         return lca.tin[u] < lca.tin[v];\n            });\n            keys.erase(std::unique(keys.begin(),\
    \ keys.end()), keys.end());\n            std::vector<int> expected = keys;\n \
    \           for (int i = 1; i < int(keys.size()); i++) expected.push_back(lca.lca(keys[i\
    \ - 1], keys[i]));\n            std::sort(expected.begin(), expected.end(), [&](int\
    \ u, int v) {\n                return lca.tin[u] < lca.tin[v];\n            });\n\
    \            expected.erase(std::unique(expected.begin(), expected.end()), expected.end());\n\
    \            assert(result.vertex == expected);\n\n            int key_index =\
    \ 0;\n            for (int i = 0; i < result.size(); i++) {\n                while\
    \ (key_index < int(keys.size()) && lca.tin[keys[key_index]] < lca.tin[result.vertex[i]])\
    \ {\n                    key_index++;\n                }\n                bool\
    \ is_key = key_index < int(keys.size()) && keys[key_index] == result.vertex[i];\n\
    \                assert(result.is_key[i] == is_key);\n                if (i ==\
    \ 0) {\n                    assert(result.parent[i] == -1);\n                \
    \    continue;\n                }\n                int parent = result.parent[i];\n\
    \                assert(0 <= parent && parent < i);\n                assert(lca.is_ancestor(result.vertex[parent],\
    \ result.vertex[i]));\n                assert(result.parent_edge_count[i] == lca.dist_edges(result.vertex[parent],\
    \ result.vertex[i]));\n                assert(result.parent_cost[i] == lca.dist_cost(result.vertex[parent],\
    \ result.vertex[i]));\n                for (int j = parent + 1; j < i; j++) {\n\
    \                    assert(!lca.is_ancestor(result.vertex[j], result.vertex[i]));\n\
    \                }\n            }\n        }\n    }\n}\n\nvoid test_hld() {\n\
    \    auto g = sample_tree();\n    m1une::tree::HeavyLightDecomposition<long long>\
    \ hld(g, 0);\n\n    assert(hld.size() == 7);\n    assert(hld.root == 0);\n   \
    \ assert(hld.lca(3, 4) == 1);\n    assert(hld.lca(3, 6) == 0);\n    assert(hld.dist_edges(3,\
    \ 6) == 5);\n    assert(hld.dist_cost(3, 6) == 17);\n    assert(hld.kth_ancestor(6,\
    \ 2) == 2);\n    assert(hld.kth_ancestor(6, 4) == -1);\n    assert(hld.jump(3,\
    \ 6, 4) == 5);\n\n    std::vector<int> expected_path = {3, 1, 0, 2, 5, 6};\n \
    \   assert(expand_segments(hld, hld.path_segments(3, 6)) == expected_path);\n\
    \    std::vector<int> expected_edge_vertices = {3, 1, 2, 5, 6};\n    assert(expand_segments(hld,\
    \ hld.path_segments(3, 6, true)) == expected_edge_vertices);\n\n    int segment_count\
    \ = 0;\n    hld.for_each_path(3, 6, [&](int l, int r, bool) {\n        assert(l\
    \ < r);\n        segment_count++;\n    });\n    assert(segment_count == int(hld.path_segments(3,\
    \ 6).size()));\n\n    auto [vl, vr] = hld.subtree_range(1);\n    std::vector<int>\
    \ subtree;\n    for (int i = vl; i < vr; i++) subtree.push_back(hld.order[i]);\n\
    \    std::sort(subtree.begin(), subtree.end());\n    assert((subtree == std::vector<int>{1,\
    \ 3, 4}));\n\n    auto [el, er] = hld.subtree_range(1, true);\n    std::vector<int>\
    \ edge_subtree;\n    for (int i = el; i < er; i++) edge_subtree.push_back(hld.order[i]);\n\
    \    std::sort(edge_subtree.begin(), edge_subtree.end());\n    assert((edge_subtree\
    \ == std::vector<int>{3, 4}));\n}\n\nvoid test_diameter() {\n    auto g = sample_tree();\n\
    \    auto diameter = m1une::tree::tree_diameter(g);\n\n    assert(!diameter.empty());\n\
    \    assert(diameter.cost == 17);\n    assert(diameter.edge_count == 5);\n   \
    \ assert(diameter.from == diameter.vertices.front());\n    assert(diameter.to\
    \ == diameter.vertices.back());\n    std::set<int> endpoints = {diameter.from,\
    \ diameter.to};\n    assert((endpoints == std::set<int>{3, 6}));\n\n    g.erase_edge(1);\n\
    \    auto split = m1une::tree::tree_diameter(g);\n    assert(split.cost == 8);\n\
    \    assert(split.edge_count == 2);\n}\n\nvoid test_rerooting() {\n    auto g\
    \ = sample_tree();\n    auto component_size = m1une::tree::rerooting_dp(\n   \
    \     g,\n        0,\n        [](int a, int b) { return a + b; },\n        [](int\
    \ acc, int) { return acc + 1; },\n        [](int dp, const auto&) { return dp;\
    \ });\n    assert(component_size == std::vector<int>(7, 7));\n\n    auto eccentricity_edges\
    \ = m1une::tree::rerooting_dp(\n        g,\n        0,\n        [](int a, int\
    \ b) { return std::max(a, b); },\n        [](int acc, int) { return acc; },\n\
    \        [](int dp, const auto&) { return dp + 1; });\n    assert(eccentricity_edges[0]\
    \ == 3);\n    assert(eccentricity_edges[3] == 5);\n    assert(eccentricity_edges[6]\
    \ == 5);\n\n    auto eccentricity_cost = m1une::tree::rerooting_dp(\n        g,\n\
    \        0LL,\n        [](long long a, long long b) { return std::max(a, b); },\n\
    \        [](long long acc, int) { return acc; },\n        [](long long dp, const\
    \ auto& e) { return dp + e.cost; });\n    assert(eccentricity_cost[0] == 10);\n\
    \    assert(eccentricity_cost[3] == 17);\n    assert(eccentricity_cost[6] == 17);\n\
    }\n\nstruct DistancePath {\n    long long count;\n    long long sum;\n    long\
    \ long length;\n};\n\nstruct DistancePoint {\n    long long count;\n    long long\
    \ sum;\n};\n\nstruct ColorVertex {\n    long long weight;\n    int color;\n};\n\
    \nstruct ColorPath {\n    int first_color;\n    int last_color;\n    long long\
    \ first_sum;\n    long long last_sum;\n    bool connected;\n};\n\nstruct ColorPoint\
    \ {\n    std::array<long long, 2> sum;\n};\n\nvoid test_static_top_tree() {\n\
    \    auto g = sample_tree();\n    std::vector<long long> values = {1, 2, 3, 4,\
    \ 5, 6, 7};\n\n    auto vertex_sum = m1une::tree::StaticTopTree(\n        g,\n\
    \        values,\n        0LL,\n        [](long long top, long long bottom, const\
    \ auto&) {\n            return top + bottom;\n        },\n        [](long long\
    \ a, long long b) {\n            return a + b;\n        },\n        [](long long\
    \ path, const auto&) {\n            return path;\n        },\n        [](long\
    \ long side, long long value, int) {\n            return side + value;\n     \
    \   });\n\n    assert(vertex_sum.size() == 7);\n    assert(vertex_sum.root() ==\
    \ 0);\n    assert(vertex_sum.all_prod() == 28);\n    assert(vertex_sum.query()\
    \ == 28);\n    assert(vertex_sum.get(3) == 4);\n    assert(vertex_sum.height()\
    \ > 0);\n    vertex_sum.set(3, 100);\n    assert(vertex_sum[3] == 100);\n    assert(vertex_sum.all_prod()\
    \ == 124);\n\n    auto root_distance_sum = m1une::tree::StaticTopTree(\n     \
    \   g,\n        std::vector<int>(7, 0),\n        DistancePoint{0, 0},\n      \
    \  [](DistancePath top, DistancePath bottom, const auto& e) {\n            long\
    \ long shift = top.length + e.cost;\n            return DistancePath{top.count\
    \ + bottom.count, top.sum + bottom.sum + bottom.count * shift,\n             \
    \                   top.length + e.cost + bottom.length};\n        },\n      \
    \  [](DistancePoint a, DistancePoint b) {\n            return DistancePoint{a.count\
    \ + b.count, a.sum + b.sum};\n        },\n        [](DistancePath path, const\
    \ auto& e) {\n            return DistancePoint{path.count, path.sum + path.count\
    \ * e.cost};\n        },\n        [](DistancePoint side, int, int) {\n       \
    \     return DistancePath{side.count + 1, side.sum, 0};\n        });\n\n    assert(root_distance_sum.all_prod().count\
    \ == 7);\n    assert(root_distance_sum.all_prod().sum == 34);\n    root_distance_sum.set_edge_cost(0,\
    \ 10);\n    assert(root_distance_sum.all_prod().sum == 55);\n    root_distance_sum.set_edge_cost(1,\
    \ 10);\n    assert(root_distance_sum.all_prod().sum == 79);\n}\n\nvoid test_rerooting_static_top_tree()\
    \ {\n    Graph<long long> g(3);\n    int e01 = g.add_edge(0, 1, 2);\n    int e12\
    \ = g.add_edge(1, 2, 5);\n    std::vector<long long> weights = {1, 1, 1};\n\n\
    \    auto stt = m1une::tree::RerootingStaticTopTree(\n        g,\n        weights,\n\
    \        DistancePoint{0, 0},\n        [](DistancePath upper, DistancePath lower,\
    \ const auto& e) {\n            long long shift = upper.length + e.cost;\n   \
    \         return DistancePath{upper.count + lower.count, upper.sum + lower.sum\
    \ + lower.count * shift,\n                                upper.length + e.cost\
    \ + lower.length};\n        },\n        [](DistancePath lower, DistancePath upper,\
    \ const auto& e) {\n            long long shift = lower.length + e.cost;\n   \
    \         return DistancePath{lower.count + upper.count, lower.sum + upper.sum\
    \ + upper.count * shift,\n                                lower.length + e.cost\
    \ + upper.length};\n        },\n        [](DistancePoint a, DistancePoint b) {\n\
    \            return DistancePoint{a.count + b.count, a.sum + b.sum};\n       \
    \ },\n        [](DistancePath path, const auto& e) {\n            return DistancePoint{path.count,\
    \ path.sum + path.count * e.cost};\n        },\n        [](DistancePath path,\
    \ const auto& e) {\n            return DistancePoint{path.count, path.sum + path.count\
    \ * e.cost};\n        },\n        [](DistancePoint side, long long weight, int)\
    \ {\n            return DistancePath{side.count + weight, side.sum, 0};\n    \
    \    });\n\n    assert(stt.size() == 3);\n    assert(stt.root() == 0);\n    assert(stt.node_count()\
    \ >= 3);\n    assert(stt.height() > 0);\n    assert(stt.all_prod_down().count\
    \ == 3);\n    assert(stt.all_prod_down().sum == 9);\n    assert(stt.all_prod_down().length\
    \ == 7);\n    assert(stt.all_prod_up().count == 3);\n    assert(stt.all_prod_up().sum\
    \ == 12);\n    assert(stt.all_prod_up().length == 7);\n\n    int root_node = stt.root_node();\n\
    \    assert(stt.path_down(root_node).sum == stt.all_prod_down().sum);\n    assert(stt.path_up(root_node).sum\
    \ == stt.all_prod_up().sum);\n    int one_node = stt.vertex_node(1);\n    assert(stt.node(one_node).type\
    \ == m1une::tree::internal::RerootingStaticTopTreeNodeType::AddVertex);\n    assert(stt.parent_node(root_node)\
    \ == -1);\n    assert(stt.point_id().count == 0);\n    assert(stt.local_point_node(1)\
    \ == -1);\n    assert(stt.local_point(1).count == 0);\n\n    using RerootingStepType\
    \ = decltype(stt)::step_type;\n    using RerootingNodeType = decltype(stt)::node_type;\n\
    \    auto steps = stt.rerooting_steps(1);\n    std::vector<decltype(stt)::RerootingStep>\
    \ streamed_steps;\n    stt.for_each_rerooting_step(1, [&](const auto& step) {\n\
    \        streamed_steps.push_back(step);\n    });\n    assert(streamed_steps.size()\
    \ == steps.size());\n    int cur = one_node;\n    for (int i = 0; i < int(steps.size());\
    \ i++) {\n        const auto& step = steps[i];\n        const auto& streamed =\
    \ streamed_steps[i];\n        assert(streamed.type == step.type);\n        assert(streamed.node\
    \ == step.node);\n        assert(streamed.sibling == step.sibling);\n        assert(streamed.vertex\
    \ == step.vertex);\n        assert(streamed.edge.from == step.edge.from);\n  \
    \      assert(streamed.edge.to == step.edge.to);\n        assert(streamed.edge.id\
    \ == step.edge.id);\n\n        assert(stt.parent_node(cur) == step.node);\n  \
    \      const auto& parent = stt.node(step.node);\n        if (step.type == RerootingStepType::CompressLower)\
    \ {\n            assert(parent.type == RerootingNodeType::Compress);\n       \
    \     assert(parent.left == cur);\n            assert(parent.right == step.sibling);\n\
    \            assert(stt.node(step.sibling).path_down.has_value());\n        }\
    \ else if (step.type == RerootingStepType::CompressUpper) {\n            assert(parent.type\
    \ == RerootingNodeType::Compress);\n            assert(parent.right == cur);\n\
    \            assert(parent.left == step.sibling);\n            assert(stt.node(step.sibling).path_up.has_value());\n\
    \        } else if (step.type == RerootingStepType::RakeLeft) {\n            assert(parent.type\
    \ == RerootingNodeType::Rake);\n            assert(parent.right == cur);\n   \
    \         assert(parent.left == step.sibling);\n            assert(stt.node(step.sibling).point.has_value());\n\
    \        } else if (step.type == RerootingStepType::RakeRight) {\n           \
    \ assert(parent.type == RerootingNodeType::Rake);\n            assert(parent.left\
    \ == cur);\n            assert(parent.right == step.sibling);\n            assert(stt.node(step.sibling).point.has_value());\n\
    \        } else if (step.type == RerootingStepType::AddEdge) {\n            assert(parent.type\
    \ == RerootingNodeType::AddEdge);\n            assert(parent.left == cur);\n \
    \       } else {\n            assert(step.type == RerootingStepType::AddVertex);\n\
    \            assert(parent.type == RerootingNodeType::AddVertex);\n          \
    \  assert(parent.left == cur);\n            assert(parent.vertex == step.vertex);\n\
    \        }\n        cur = step.node;\n    }\n    assert(cur == stt.root_node());\n\
    \n    auto edge = m1une::graph::Edge<long long>(0, 1, 2, e01);\n    auto reversed\
    \ = decltype(stt)::reverse_edge(edge);\n    assert(reversed.from == 1);\n    assert(reversed.to\
    \ == 0);\n    DistancePath one = stt.add_vertex(stt.point_id(), 1LL, 0);\n   \
    \ assert(one.count == 1);\n    assert(one.sum == 0);\n    auto down_point = stt.add_edge_down(one,\
    \ edge);\n    auto up_point = stt.add_edge_up(one, reversed);\n    assert(down_point.sum\
    \ == 2);\n    assert(up_point.sum == 2);\n    auto raked = stt.rake(down_point,\
    \ up_point);\n    assert(raked.count == 2);\n    assert(raked.sum == 4);\n   \
    \ assert(stt.compress_down(one, one, edge).sum == 2);\n    assert(stt.compress_up(one,\
    \ one, reversed).sum == 2);\n\n    stt.set_edge_cost(e01, 10);\n    assert(stt.all_prod_down().count\
    \ == 3);\n    assert(stt.all_prod_down().sum == 25);\n    assert(stt.all_prod_down().length\
    \ == 15);\n    assert(stt.all_prod_up().sum == 20);\n    assert(stt.all_prod_up().length\
    \ == 15);\n\n    stt.set(0, 3);\n    assert(stt[0] == 3);\n    assert(stt.all_prod_down().count\
    \ == 5);\n    assert(stt.all_prod_down().sum == 25);\n    assert(stt.all_prod_up().count\
    \ == 5);\n    assert(stt.all_prod_up().sum == 50);\n\n    stt.set_edge_cost(e12,\
    \ 1);\n    assert(stt.all_prod_down().sum == 21);\n    assert(stt.all_prod_up().sum\
    \ == 34);\n}\n\nvoid test_rerooting_static_top_tree_vertex_component() {\n   \
    \ auto g = sample_tree();\n    std::vector<ColorVertex> values = {\n        ColorVertex{1,\
    \ 0},      ColorVertex{10, 0},     ColorVertex{100, 1},    ColorVertex{1000, 0},\n\
    \        ColorVertex{10000, 1},  ColorVertex{100000, 1}, ColorVertex{1000000,\
    \ 1},\n    };\n\n    auto compress = [](ColorPath a, ColorPath b, const auto&)\
    \ {\n        bool join = a.last_color == b.first_color;\n        ColorPath res{a.first_color,\
    \ b.last_color, a.first_sum, b.last_sum, false};\n        if (join && a.connected)\
    \ res.first_sum += b.first_sum;\n        if (join && b.connected) res.last_sum\
    \ += a.last_sum;\n        res.connected = a.connected && b.connected && join;\n\
    \        return res;\n    };\n    auto rake = [](ColorPoint a, ColorPoint b) {\n\
    \        return ColorPoint{a.sum[0] + b.sum[0], a.sum[1] + b.sum[1]};\n    };\n\
    \    auto add_edge = [](ColorPath path, const auto&) {\n        ColorPoint res{};\n\
    \        res.sum[path.first_color] = path.first_sum;\n        return res;\n  \
    \  };\n    auto add_vertex = [](ColorPoint side, ColorVertex value, int) {\n \
    \       long long sum = value.weight + side.sum[value.color];\n        return\
    \ ColorPath{value.color, value.color, sum, sum, true};\n    };\n\n    auto stt\
    \ = m1une::tree::RerootingStaticTopTree(\n        g, values, ColorPoint{0, 0},\
    \ compress, compress, rake, add_edge, add_edge, add_vertex);\n\n    using ColorStt\
    \ = decltype(stt);\n    struct QueryFolder {\n        const ColorStt& stt;\n \
    \       const std::vector<ColorVertex>& values;\n        int color = 0;\n    \
    \    long long answer = 0;\n        bool touches_top = false;\n        bool touches_bottom\
    \ = false;\n        bool pending_open = false;\n        ColorPoint pending{};\n\
    \n        void start(int v, const ColorVertex& value, const ColorPoint& local)\
    \ {\n            color = value.color;\n            answer = value.weight + local.sum[color];\n\
    \            touches_top = true;\n            touches_bottom = true;\n       \
    \     pending_open = false;\n            pending = stt.point_id();\n         \
    \   assert(values[v].color == color);\n        }\n\n        void compress_lower(const\
    \ ColorPath& lower, ColorStt::edge_type) {\n            bool connect = touches_bottom\
    \ && lower.first_color == color;\n            if (connect) answer += lower.first_sum;\n\
    \            touches_bottom = connect && lower.connected;\n        }\n\n     \
    \   void compress_upper(const ColorPath& upper, ColorStt::edge_type) {\n     \
    \       bool connect = touches_top && upper.first_color == color;\n          \
    \  if (connect) answer += upper.first_sum;\n            touches_top = connect\
    \ && upper.connected;\n        }\n\n        void add_edge(ColorStt::edge_type)\
    \ {\n            pending_open = touches_top;\n            pending = stt.point_id();\n\
    \        }\n\n        void rake_left(const ColorPoint& point) {\n            if\
    \ (pending_open) pending = stt.rake(point, pending);\n        }\n\n        void\
    \ rake_right(const ColorPoint& point) {\n            if (pending_open) pending\
    \ = stt.rake(pending, point);\n        }\n\n        void add_vertex(int, const\
    \ ColorVertex& value) {\n            if (pending_open && value.color == color)\
    \ {\n                answer += value.weight + pending.sum[color];\n          \
    \      touches_top = true;\n                touches_bottom = true;\n         \
    \   } else {\n                touches_top = false;\n                touches_bottom\
    \ = false;\n            }\n            pending_open = false;\n            pending\
    \ = stt.point_id();\n        }\n\n        long long result() const {\n       \
    \     return answer;\n        }\n    };\n\n    auto query = [&](int v) {\n   \
    \     return stt.fold_rerooting(v, QueryFolder{stt, values});\n    };\n\n    auto\
    \ brute = [&](int start) {\n        int color = values[start].color;\n       \
    \ long long answer = 0;\n        std::vector<char> seen(g.size(), false);\n  \
    \      std::vector<int> stack = {start};\n        seen[start] = true;\n      \
    \  while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            answer += values[v].weight;\n            for (const auto& e : g[v])\
    \ {\n                if (seen[e.to] || values[e.to].color != color) continue;\n\
    \                seen[e.to] = true;\n                stack.push_back(e.to);\n\
    \            }\n        }\n        return answer;\n    };\n\n    auto check_all\
    \ = [&]() {\n        for (int v = 0; v < g.size(); v++) assert(query(v) == brute(v));\n\
    \    };\n\n    check_all();\n    values[2].color ^= 1;\n    stt.set(2, values[2]);\n\
    \    check_all();\n    values[5].weight += 7;\n    stt.set(5, values[5]);\n  \
    \  check_all();\n    values[1].color ^= 1;\n    stt.set(1, values[1]);\n    check_all();\n\
    \    values[4].weight += 11;\n    stt.set(4, values[4]);\n    check_all();\n}\n\
    \nvoid test_centroid_decomposition() {\n    auto g = sample_tree();\n    m1une::tree::CentroidDecomposition<long\
    \ long> cd(g);\n\n    assert(cd.size() == 7);\n    assert(!cd.empty());\n    assert(cd.root()\
    \ == 0);\n    assert(cd.roots == std::vector<int>{0});\n    assert(cd.parent[cd.root()]\
    \ == -1);\n    assert(cd.depth[cd.root()] == 0);\n    assert(cd.order.size() ==\
    \ 7);\n\n    int child_count = 0;\n    for (const auto& ch : cd.children) child_count\
    \ += int(ch.size());\n    assert(child_count == 6);\n    for (int v = 0; v < 7;\
    \ v++) {\n        if (v == cd.root()) continue;\n        assert(cd.parent[v] !=\
    \ -1);\n        assert(cd.depth[v] == cd.depth[cd.parent[v]] + 1);\n    }\n}\n\
    \nvoid test_forest() {\n    Graph<int> g(4);\n    g.add_edge(0, 1, 5);\n    g.add_edge(2,\
    \ 3, 7);\n\n    auto diameter = m1une::tree::tree_diameter(g);\n    assert(diameter.cost\
    \ == 7);\n    assert(diameter.edge_count == 1);\n\n    auto component_size = m1une::tree::rerooting_dp(\n\
    \        g,\n        0,\n        [](int a, int b) { return a + b; },\n       \
    \ [](int acc, int) { return acc + 1; },\n        [](int dp, const auto&) { return\
    \ dp; });\n    assert(component_size == std::vector<int>(4, 2));\n\n    m1une::tree::CentroidDecomposition<int>\
    \ cd(g);\n    assert(cd.roots.size() == 2);\n    assert(cd.order.size() == 4);\n\
    }\n\nint main() {\n    test_rooted_tree();\n    test_euler_tour();\n    test_sparse_table_lca();\n\
    \    test_virtual_tree();\n    test_hld();\n    test_diameter();\n    test_rerooting();\n\
    \    test_static_top_tree();\n    test_rerooting_static_top_tree();\n    test_rerooting_static_top_tree_vertex_component();\n\
    \    test_centroid_decomposition();\n    test_forest();\n\n    long long a = 0,\
    \ b = 0;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - graph/graph.hpp
  - graph/tree/all.hpp
  - graph/tree/cartesian_tree.hpp
  - graph/graph.hpp
  - graph/tree/centroid_decomposition.hpp
  - graph/tree/diameter.hpp
  - graph/tree/distance_frequency.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/modint.hpp
  - graph/tree/dsu_on_tree.hpp
  - graph/tree/euler_tour.hpp
  - graph/tree/heavy_light_decomposition.hpp
  - graph/tree/range_contour_query.hpp
  - monoid/add.hpp
  - monoid/concept.hpp
  - graph/tree/rooted_tree.hpp
  - graph/tree/rerooting_dp.hpp
  - graph/tree/rerooting_static_top_tree.hpp
  - graph/tree/sparse_table_lca.hpp
  - ds/range_query/sparse_table.hpp
  - monoid/concept.hpp
  - graph/tree/static_top_tree.hpp
  - graph/tree/tree.hpp
  - graph/tree/tree_hash.hpp
  - graph/tree/virtual_tree.hpp
  - graph/tree/zero_one_on_tree.hpp
  isVerificationFile: true
  path: verify/graph/tree/tree_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/tree/tree_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/tree/tree_algorithms.test.cpp
- /verify/verify/graph/tree/tree_algorithms.test.cpp.html
title: verify/graph/tree/tree_algorithms.test.cpp
---
