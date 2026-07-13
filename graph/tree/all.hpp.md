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
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/tree_algorithms.test.cpp
    title: verify/graph/tree/tree_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: '#ifndef M1UNE_TREE_ALL_HPP

    #define M1UNE_TREE_ALL_HPP 1


    #include "cartesian_tree.hpp"

    #include "centroid_decomposition.hpp"

    #include "diameter.hpp"

    #include "distance_frequency.hpp"

    #include "dsu_on_tree.hpp"

    #include "euler_tour.hpp"

    #include "heavy_light_decomposition.hpp"

    #include "range_contour_query.hpp"

    #include "rerooting_dp.hpp"

    #include "rerooting_static_top_tree.hpp"

    #include "rooted_tree.hpp"

    #include "sparse_table_lca.hpp"

    #include "static_top_tree.hpp"

    #include "tree.hpp"

    #include "tree_hash.hpp"

    #include "virtual_tree.hpp"

    #include "zero_one_on_tree.hpp"


    #endif  // M1UNE_TREE_ALL_HPP

    '
  dependsOn:
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
  isVerificationFile: false
  path: graph/tree/all.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/tree/tree_algorithms.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/tree/all.hpp
layout: document
title: Tree All
---

## Overview

`graph/tree/all.hpp` includes every tree header in this directory. Most
algorithms use `m1une::graph::Graph<T>` as their input container, and
sequence-derived helpers such as Cartesian tree can convert their result to the
same graph container.

## Included Headers

| Header | Contents |
| --- | --- |
| `graph/tree/cartesian_tree.hpp` | Cartesian tree construction from an array. |
| `graph/tree/tree.hpp` | Core rooted tree and diameter bundle. |
| `graph/tree/euler_tour.hpp` | Lightweight rooted-tree preorder, subtree ranges, and parent/depth metadata. |
| `graph/tree/rooted_tree.hpp` | Rooted metadata, Euler intervals, LCA, jumps, paths, and distances. |
| `graph/tree/sparse_table_lca.hpp` | Euler-tour sparse-table LCA with $O(1)$ queries. |
| `graph/tree/heavy_light_decomposition.hpp` | HLD order, path segments, subtree ranges, LCA, and jumps. |
| `graph/tree/range_contour_query.hpp` | Commutative-group contour products and applications by unweighted tree distance, with additive wrappers. |
| `graph/tree/diameter.hpp` | Weighted tree/forest diameter path. |
| `graph/tree/distance_frequency.hpp` | Counts unordered vertex pairs at every unweighted tree distance. |
| `graph/tree/tree_hash.hpp` | Probabilistic rooted-subtree and unrooted-tree isomorphism hashes. |
| `graph/tree/dsu_on_tree.hpp` | Iterative small-to-large subtree processing with user callbacks. |
| `graph/tree/rerooting_dp.hpp` | Generic rerooting DP helper. |
| `graph/tree/static_top_tree.hpp` | Dynamic one-root tree DP on a fixed tree using static top-tree clusters. |
| `graph/tree/rerooting_static_top_tree.hpp` | Bidirectional static top-tree clusters for dynamic rerooting-DP solutions. |
| `graph/tree/centroid_decomposition.hpp` | Centroid decomposition for trees and forests. |
| `graph/tree/virtual_tree.hpp` | Virtual-tree compression for a selected vertex set. |
| `graph/tree/zero_one_on_tree.hpp` | Minimum inversions in an ancestor-respecting order of binary-labeled vertices. |

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/tree/all.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<int> g(3);
    g.add_edge(0, 1);
    g.add_edge(1, 2);

    auto diameter = m1une::tree::tree_diameter(g);
    std::cout << diameter.edge_count << "\n";
}
```
