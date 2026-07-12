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
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
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
    path: verify/graph/tree/distance_frequency.test.cpp
    title: verify/graph/tree/distance_frequency.test.cpp
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_TREE_DISTANCE_FREQUENCY_HPP\n#define M1UNE_TREE_DISTANCE_FREQUENCY_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <utility>\n#include <vector>\n\n#include \"../../math/fps/convolution.hpp\"\
    \n#include \"../../math/modint.hpp\"\n#include \"centroid_decomposition.hpp\"\n\
    \nnamespace m1une {\nnamespace tree {\n\nnamespace distance_frequency_detail {\n\
    \ntemplate <class Mint, class T>\nstd::vector<Mint> count_ordered_pairs(\n   \
    \ const m1une::graph::Graph<T>& tree,\n    const CentroidDecomposition<T>& decomposition\n\
    ) {\n    const int size = tree.size();\n    std::vector<Mint> count(static_cast<std::size_t>(size));\n\
    \    std::vector<char> removed(std::size_t(size), false);\n    std::vector<Mint>\
    \ histogram;\n    std::vector<std::pair<int, int>> stack;\n    std::vector<int>\
    \ parent(std::size_t(size), -1);\n\n    for (int centroid : decomposition.order)\
    \ {\n        std::vector<Mint> total(1, Mint(1));\n        for (const auto& edge\
    \ : tree[centroid]) {\n            if (!edge.alive || removed[std::size_t(edge.to)])\
    \ continue;\n\n            histogram.clear();\n            stack.clear();\n  \
    \          stack.emplace_back(edge.to, 1);\n            parent[std::size_t(edge.to)]\
    \ = centroid;\n            while (!stack.empty()) {\n                const auto\
    \ [vertex, distance] = stack.back();\n                stack.pop_back();\n    \
    \            if (int(histogram.size()) <= distance) {\n                    histogram.resize(std::size_t(distance\
    \ + 1));\n                }\n                histogram[std::size_t(distance)]\
    \ += Mint(1);\n\n                for (const auto& next : tree[vertex]) {\n   \
    \                 if (!next.alive || removed[std::size_t(next.to)]) continue;\n\
    \                    if (next.to == parent[std::size_t(vertex)]) continue;\n \
    \                   parent[std::size_t(next.to)] = vertex;\n                 \
    \   stack.emplace_back(next.to, distance + 1);\n                }\n          \
    \  }\n\n            if (total.size() < histogram.size()) {\n                total.resize(histogram.size());\n\
    \            }\n            for (std::size_t distance = 0; distance < histogram.size();\
    \ distance++) {\n                total[distance] += histogram[distance];\n   \
    \         }\n\n            const std::vector<Mint> within_component =\n      \
    \          m1une::fps::convolution(histogram, histogram);\n            const std::size_t\
    \ limit = std::min(count.size(), within_component.size());\n            for (std::size_t\
    \ distance = 0; distance < limit; distance++) {\n                count[distance]\
    \ -= within_component[distance];\n            }\n        }\n\n        const std::vector<Mint>\
    \ through_centroid =\n            m1une::fps::convolution(total, total);\n   \
    \     const std::size_t limit = std::min(count.size(), through_centroid.size());\n\
    \        for (std::size_t distance = 0; distance < limit; distance++) {\n    \
    \        count[distance] += through_centroid[distance];\n        }\n        removed[std::size_t(centroid)]\
    \ = true;\n    }\n    return count;\n}\n\ninline std::uint64_t combine_residues(std::uint32_t\
    \ first, std::uint32_t second) {\n    using First = m1une::math::ModInt<998244353>;\n\
    \    using Second = m1une::math::ModInt<924844033>;\n    static const std::uint64_t\
    \ inverse = Second(First::mod()).inv().val();\n    const std::uint64_t offset\
    \ =\n        (std::uint64_t(second) + Second::mod() - first % Second::mod()) %\n\
    \        Second::mod();\n    const std::uint64_t multiplier = offset * inverse\
    \ % Second::mod();\n    return std::uint64_t(first) + std::uint64_t(First::mod())\
    \ * multiplier;\n}\n\n}  // namespace distance_frequency_detail\n\ntemplate <class\
    \ T>\nstd::vector<long long> tree_distance_frequency(\n    const m1une::graph::Graph<T>&\
    \ tree\n) {\n    const int size = tree.size();\n    assert(tree.edge_count() ==\
    \ std::max(0, size - 1));\n    if (size == 0) return {};\n\n    const CentroidDecomposition<T>\
    \ decomposition(tree);\n    assert(decomposition.roots.size() == 1);\n\n    using\
    \ First = m1une::math::ModInt<998244353>;\n    using Second = m1une::math::ModInt<924844033>;\n\
    \    assert(\n        std::uint64_t(size) * std::uint64_t(size - 1) <\n      \
    \  std::uint64_t(First::mod()) * Second::mod()\n    );\n    const std::vector<First>\
    \ first =\n        distance_frequency_detail::count_ordered_pairs<First>(\n  \
    \          tree,\n            decomposition\n        );\n    const std::vector<Second>\
    \ second =\n        distance_frequency_detail::count_ordered_pairs<Second>(\n\
    \            tree,\n            decomposition\n        );\n\n    std::vector<long\
    \ long> result(static_cast<std::size_t>(size));\n    result[0] = size;\n    for\
    \ (int distance = 1; distance < size; distance++) {\n        const std::uint64_t\
    \ ordered =\n            distance_frequency_detail::combine_residues(\n      \
    \          first[std::size_t(distance)].val(),\n                second[std::size_t(distance)].val()\n\
    \            );\n        assert((ordered & 1) == 0);\n        result[std::size_t(distance)]\
    \ = static_cast<long long>(ordered / 2);\n    }\n    return result;\n}\n\n}  //\
    \ namespace tree\n}  // namespace m1une\n\n#endif  // M1UNE_TREE_DISTANCE_FREQUENCY_HPP\n"
  dependsOn:
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/modint.hpp
  - graph/tree/centroid_decomposition.hpp
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/tree/distance_frequency.hpp
  requiredBy:
  - graph/tree/all.hpp
  - graph/all.hpp
  timestamp: '2026-07-13 05:31:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/tree/tree_algorithms.test.cpp
  - verify/graph/tree/distance_frequency.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/tree/distance_frequency.hpp
layout: document
title: Tree Distance Frequency
---

## Overview

`tree_distance_frequency` counts unordered pairs of vertices at every distance
in an unweighted tree. It is useful when a problem asks for the complete
distribution of path lengths rather than individual distance queries.

```cpp
#include "graph/tree/distance_frequency.hpp"
```

The function is in `m1une::tree` and accepts `m1une::graph::Graph<T>`.

## Interface

```cpp
template <class T>
std::vector<long long> tree_distance_frequency(
    const m1une::graph::Graph<T>& tree
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `tree_distance_frequency(tree)` | Returns the number of unordered vertex pairs at each edge distance. | $O(N \log^2 N)$ time and $O(N)$ additional memory |

For a tree with `N` vertices, the result has length `N`:

* `result[0]` is `N`, counting each vertex paired with itself;
* for `distance > 0`, `result[distance]` is the number of pairs `(u, v)` with
  `u < v` whose path contains exactly `distance` edges.

The empty tree produces an empty vector. Otherwise, the graph must be a
connected undirected tree with `N - 1` active edges. Edge costs are ignored.
The result is exact rather than reduced modulo a number.

## Algorithm

At each centroid, depth histograms are collected for the whole current
component and for every component obtained by removing the centroid. Squaring
the whole histogram and subtracting the component squares counts ordered pairs
whose path passes through that centroid. Centroid decomposition makes every
pair appear at exactly one level.

The histogram squares use NTT convolution under two prime moduli. Chinese
remaindering reconstructs the exact ordered-pair counts, which are then divided
by two for positive distances.

## Example

```cpp
#include "graph/graph.hpp"
#include "graph/tree/distance_frequency.hpp"

#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<int> tree(4);
    tree.add_edge(0, 1);
    tree.add_edge(1, 2);
    tree.add_edge(2, 3);

    std::vector<long long> frequency =
        m1une::tree::tree_distance_frequency(tree);
    // frequency is {4, 3, 2, 1}.
    std::cout << frequency[2] << '\n';
}
```
