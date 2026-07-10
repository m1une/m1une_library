---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
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
    path: verify/graph/graph_counting.test.cpp
    title: verify/graph/graph_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
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
  code: "#ifndef M1UNE_GRAPH_COUNTING_HPP\n#define M1UNE_GRAPH_COUNTING_HPP 1\n\n\
    #include <cassert>\n#include <cstdint>\n#include <optional>\n#include <utility>\n\
    #include <vector>\n\n#include \"../math/fps/convolution.hpp\"\n#include \"../math/fps/formal_power_series.hpp\"\
    \n#include \"../math/combinatorics.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nnamespace graph_counting_detail {\n\ntemplate <class Mint>\nusing Fps =\
    \ fps::FormalPowerSeries<Mint>;\n\ntemplate <class Mint>\nvoid assert_maximum(int\
    \ maximum) {\n    assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum)\
    \ < Mint::mod());\n}\n\ntemplate <class Mint>\nMint inverse_two() {\n    assert(Mint::mod()\
    \ != 2);\n    return Mint(2).inv();\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ to_egf(\n    std::vector<Mint> values,\n    const math::Combinatorics<Mint>&\
    \ combinations\n) {\n    for (int i = 0; i < int(values.size()); i++) {\n    \
    \    values[i] *= combinations.inverse_factorial(i);\n    }\n    return values;\n\
    }\n\ntemplate <class Mint>\nstd::vector<Mint> from_egf(\n    std::vector<Mint>\
    \ coefficients,\n    const math::Combinatorics<Mint>& combinations\n) {\n    for\
    \ (int i = 0; i < int(coefficients.size()); i++) {\n        coefficients[i] *=\
    \ combinations.factorial(i);\n    }\n    return coefficients;\n}\n\ntemplate <class\
    \ Mint>\nstd::vector<Mint> two_to_binom2(int maximum) {\n    std::vector<Mint>\
    \ result(maximum + 1);\n    result[0] = 1;\n    Mint multiplier = 1;\n    for\
    \ (int n = 1; n <= maximum; n++) {\n        result[n] = result[n - 1] * multiplier;\n\
    \        multiplier += multiplier;\n    }\n    return result;\n}\n\ntemplate <class\
    \ Mint>\nFps<Mint> colored_bipartite_egf(\n    int maximum,\n    const math::Combinatorics<Mint>&\
    \ combinations\n) {\n    const Mint half = inverse_two<Mint>();\n\n    Fps<Mint>\
    \ kernel(maximum + 1);\n    kernel[0] = 1;\n    Mint multiplier = 1;\n    for\
    \ (int i = 1; i <= maximum; i++) {\n        kernel[i] = kernel[i - 1] * multiplier;\n\
    \        multiplier *= half;\n    }\n    for (int i = 0; i <= maximum; i++) {\n\
    \        kernel[i] *= combinations.inverse_factorial(i);\n    }\n\n    Fps<Mint>\
    \ result = (kernel * kernel).pre(maximum + 1);\n    std::vector<Mint> edge_powers\
    \ = two_to_binom2<Mint>(maximum);\n    for (int i = 0; i <= maximum; i++) result[i]\
    \ *= edge_powers[i];\n    return result;\n}\n\n}  // namespace graph_counting_detail\n\
    \ntemplate <class Mint>\nstd::vector<Mint> count_labeled_undirected_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    return\
    \ graph_counting_detail::two_to_binom2<Mint>(maximum);\n}\n\ntemplate <class Mint>\n\
    std::vector<Mint> count_labeled_connected_graphs(int maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\
    \    math::Combinatorics<Mint> combinations(maximum);\n\n    graph_counting_detail::Fps<Mint>\
    \ egf =\n        graph_counting_detail::to_egf(count_labeled_undirected_graphs<Mint>(maximum),\
    \ combinations);\n    egf = egf.log(maximum + 1);\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_trees(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\n  \
    \  std::vector<Mint> result(maximum + 1);\n    for (int n = 1; n <= maximum; n++)\
    \ {\n        result[n] = (n == 1 ? Mint(1) : Mint(n).pow(n - 2));\n    }\n   \
    \ return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_forests(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    graph_counting_detail::Fps<Mint> egf =\n     \
    \   graph_counting_detail::to_egf(count_labeled_trees<Mint>(maximum), combinations);\n\
    \    egf = egf.exp(maximum + 1);\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_unicyclic_connected_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n    using Fps = graph_counting_detail::Fps<Mint>;\n\n\
    \    Fps rooted_tree_egf(maximum + 1);\n    for (int n = 1; n <= maximum; n++)\
    \ {\n        rooted_tree_egf[n] =\n            Mint(n).pow(n - 1) * combinations.inverse_factorial(n);\n\
    \    }\n\n    Fps one_minus_rooted(maximum + 1);\n    one_minus_rooted[0] = 1;\n\
    \    for (int i = 1; i <= maximum; i++) {\n        one_minus_rooted[i] = Mint(0)\
    \ - rooted_tree_egf[i];\n    }\n\n    Fps egf = one_minus_rooted.log(maximum +\
    \ 1);\n    for (Mint& coefficient : egf) coefficient = Mint(0) - coefficient;\n\
    \    egf -= rooted_tree_egf;\n    egf -= ((rooted_tree_egf * rooted_tree_egf).pre(maximum\
    \ + 1) *\n            graph_counting_detail::inverse_two<Mint>());\n    egf *=\
    \ graph_counting_detail::inverse_two<Mint>();\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_connected_eulerian_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    std::vector<Mint> all_even(maximum + 1);\n   \
    \ all_even[0] = 1;\n    if (maximum >= 1) {\n        std::vector<Mint> shifted\
    \ = count_labeled_undirected_graphs<Mint>(maximum - 1);\n        for (int n =\
    \ 1; n <= maximum; n++) all_even[n] = shifted[n - 1];\n    }\n\n    graph_counting_detail::Fps<Mint>\
    \ egf =\n        graph_counting_detail::to_egf(std::move(all_even), combinations);\n\
    \    egf = egf.log(maximum + 1);\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_connected_bipartite_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    graph_counting_detail::Fps<Mint> egf =\n     \
    \   graph_counting_detail::colored_bipartite_egf(maximum, combinations).log(maximum\
    \ + 1);\n    egf *= graph_counting_detail::inverse_two<Mint>();\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_bipartite_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    std::optional<graph_counting_detail::Fps<Mint>>\
    \ egf =\n        graph_counting_detail::colored_bipartite_egf(maximum, combinations).sqrt(maximum\
    \ + 1);\n    assert(egf.has_value());\n    return graph_counting_detail::from_egf(std::move(*egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_directed_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\n  \
    \  std::vector<Mint> result(maximum + 1);\n    result[0] = 1;\n    Mint multiplier\
    \ = 1;\n    const Mint four = 4;\n    for (int n = 1; n <= maximum; n++) {\n \
    \       result[n] = result[n - 1] * multiplier;\n        multiplier *= four;\n\
    \    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_dags(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n    using Fps = graph_counting_detail::Fps<Mint>;\n\n\
    \    Fps denominator(maximum + 1);\n    Mint multiplier = 1;\n    const Mint half\
    \ = graph_counting_detail::inverse_two<Mint>();\n    denominator[0] = 1;\n   \
    \ for (int n = 1; n <= maximum; n++) {\n        denominator[n] = denominator[n\
    \ - 1] * multiplier;\n        multiplier *= half;\n    }\n    for (int n = 0;\
    \ n <= maximum; n++) {\n        denominator[n] *= combinations.inverse_factorial(n);\n\
    \        if (n & 1) denominator[n] = Mint(0) - denominator[n];\n    }\n\n    Fps\
    \ egf = denominator.inv(maximum + 1);\n    std::vector<Mint> edge_powers = graph_counting_detail::two_to_binom2<Mint>(maximum);\n\
    \    for (int n = 0; n <= maximum; n++) {\n        egf[n] *= combinations.factorial(n)\
    \ * edge_powers[n];\n    }\n    return egf;\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ count_labeled_strongly_connected_digraphs(int maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\
    \    math::Combinatorics<Mint> combinations(maximum);\n\n    graph_counting_detail::Fps<Mint>\
    \ egf(maximum + 1);\n    std::vector<Mint> edge_powers = graph_counting_detail::two_to_binom2<Mint>(maximum);\n\
    \    for (int n = 0; n <= maximum; n++) {\n        egf[n] = edge_powers[n] * combinations.inverse_factorial(n);\n\
    \    }\n\n    egf = egf.inv(maximum + 1);\n    for (int n = 0; n <= maximum; n++)\
    \ egf[n] *= edge_powers[n];\n    egf = egf.log(maximum + 1);\n    for (int n =\
    \ 0; n <= maximum; n++) {\n        egf[n] = Mint(0) - egf[n] * combinations.factorial(n);\n\
    \    }\n    return egf;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_tournaments(int\
    \ maximum) {\n    return count_labeled_undirected_graphs<Mint>(maximum);\n}\n\n\
    template <class Mint>\nstd::vector<Mint> count_labeled_strongly_connected_tournaments(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    graph_counting_detail::Fps<Mint> egf =\n     \
    \   graph_counting_detail::to_egf(count_labeled_tournaments<Mint>(maximum), combinations);\n\
    \    egf = egf.inv(maximum + 1);\n    if (!egf.empty()) egf[0] = 0;\n    for (int\
    \ n = 0; n <= maximum; n++) {\n        egf[n] = Mint(0) - egf[n] * combinations.factorial(n);\n\
    \    }\n    return egf;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_unlabeled_rooted_trees(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\n  \
    \  std::vector<Mint> result(maximum + 1);\n    if (maximum == 0) return result;\n\
    \n    std::vector<Mint> divisor_sum(maximum + 1);\n    result[1] = 1;\n    for\
    \ (int multiple = 1; multiple <= maximum; multiple++) {\n        divisor_sum[multiple]\
    \ += result[1];\n    }\n\n    for (int n = 1; n < maximum; n++) {\n        Mint\
    \ sum = 0;\n        for (int i = 1; i <= n; i++) {\n            sum += divisor_sum[i]\
    \ * result[n - i + 1];\n        }\n        result[n + 1] = sum / Mint(n);\n\n\
    \        const int size = n + 1;\n        const Mint contribution = Mint(size)\
    \ * result[size];\n        for (int multiple = size; multiple <= maximum; multiple\
    \ += size) {\n            divisor_sum[multiple] += contribution;\n        }\n\
    \    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_unlabeled_trees(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    using\
    \ Fps = graph_counting_detail::Fps<Mint>;\n\n    Fps rooted = count_unlabeled_rooted_trees<Mint>(maximum);\n\
    \    Fps rooted_square = (rooted * rooted).pre(maximum + 1);\n    const Mint half\
    \ = graph_counting_detail::inverse_two<Mint>();\n\n    std::vector<Mint> result(maximum\
    \ + 1);\n    for (int n = 1; n <= maximum; n++) {\n        result[n] = rooted[n]\
    \ - rooted_square[n] * half;\n        if ((n & 1) == 0) result[n] += rooted[n\
    \ / 2] * half;\n    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GRAPH_COUNTING_HPP\n"
  dependsOn:
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/combinatorics.hpp
  isVerificationFile: false
  path: graph/counting.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-07-11 03:19:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/graph_counting.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/counting.hpp
layout: document
title: Graph Counting
---

## Overview

`graph/counting.hpp` computes common graph-counting sequences by number of
vertices. The labeled functions count simple graphs on vertex set
`{0, 1, ..., n - 1}`; two labeled graphs are different when some edge choice is
different. The unlabeled tree functions count isomorphism classes.

All functions return a vector `answer` of length `maximum + 1`, where
`answer[n]` is the number of objects on `n` vertices.

This header counts by vertex number only. It does not keep track of the number
of edges.

## Requirements and Conventions

Let `N = maximum`. In the complexity table, `M(N)` means the cost of one
polynomial multiplication where both inputs have length `O(N)`, and only the
first `N + 1` coefficients may be needed. Equivalently, it is the convolution
cost for formal power series truncated to degree at most `N`. With the supplied
convolution over NTT-friendly static modints, `M(N) = O(N log N)`.

`Mint` must support the operations required by
`fps::FormalPowerSeries<Mint>`: addition, subtraction, multiplication,
division by nonzero small integers, `pow`, `inv`, and `Mint::mod()`. In
practice this is intended for prime moduli such as
`m1une::math::modint998244353`.

The code asserts:

* `maximum >= 0`;
* `maximum < Mint::mod()`, because EGF operations divide by factorials and
  small integers;
* the modulus is not `2` for functions that divide by `2`.

Connectivity follows the convention that the empty graph is not connected.
Thus connected counts have value `0` at `n = 0`. A forest has value `1` at
`n = 0`, representing the empty forest.

A labeled tournament is an orientation of the complete graph on labeled
vertices: for every unordered pair of distinct vertices, exactly one of the two
possible directed edges is chosen. A strongly connected labeled tournament is a
labeled tournament in which every ordered pair of vertices `(u, v)` has a
directed path from `u` to `v`.

## Public Interface

All signatures below are in namespace `m1une::graph`.

| Function | Counts | Time |
| --- | --- | --- |
| `template <class Mint> std::vector<Mint> count_labeled_undirected_graphs(int maximum)` | Simple undirected labeled graphs. | `O(N)` |
| `template <class Mint> std::vector<Mint> count_labeled_connected_graphs(int maximum)` | Connected simple undirected labeled graphs. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_trees(int maximum)` | Labeled trees, using Cayley's formula. | `O(N log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_forests(int maximum)` | Labeled forests. | `O(N log N + M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_unicyclic_connected_graphs(int maximum)` | Connected labeled graphs with exactly `n` edges on `n` vertices. | `O(N log N + M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_connected_eulerian_graphs(int maximum)` | Connected undirected labeled graphs where every degree is even. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_connected_bipartite_graphs(int maximum)` | Connected undirected labeled bipartite graphs. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_bipartite_graphs(int maximum)` | Undirected labeled bipartite graphs, not necessarily connected. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_directed_graphs(int maximum)` | Simple directed labeled graphs without loops. | `O(N)` |
| `template <class Mint> std::vector<Mint> count_labeled_dags(int maximum)` | Labeled directed acyclic graphs. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_strongly_connected_digraphs(int maximum)` | Strongly connected simple directed labeled graphs without loops. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_tournaments(int maximum)` | Labeled tournaments. | `O(N)` |
| `template <class Mint> std::vector<Mint> count_labeled_strongly_connected_tournaments(int maximum)` | Strongly connected labeled tournaments. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_unlabeled_rooted_trees(int maximum)` | Unlabeled rooted trees. | `O(N^2)` |
| `template <class Mint> std::vector<Mint> count_unlabeled_trees(int maximum)` | Unlabeled unrooted trees. | `O(N^2 + M(N))` |

All functions use `O(N)` memory, apart from temporary polynomial buffers.

## Example

```cpp
#include "graph/counting.hpp"
#include "math/modint.hpp"
#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;

    auto connected = m1une::graph::count_labeled_connected_graphs<mint>(5);
    auto dags = m1une::graph::count_labeled_dags<mint>(5);

    std::cout << connected[4] << "\n";  // 38
    std::cout << dags[4] << "\n";       // 543
}
```
