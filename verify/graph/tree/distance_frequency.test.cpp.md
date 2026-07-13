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
    path: graph/tree/centroid_decomposition.hpp
    title: Centroid Decomposition
  - icon: ':heavy_check_mark:'
    path: graph/tree/distance_frequency.hpp
    title: Tree Distance Frequency
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
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
    links:
    - https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
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
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#include \"../../../graph/graph.hpp\"\n#include \"../../../graph/tree/distance_frequency.hpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <queue>\n\
    #include <vector>\n\nnamespace {\n\nusing Graph = m1une::graph::Graph<int>;\n\n\
    std::vector<long long> naive_distance_frequency(const Graph& tree) {\n    const\
    \ int size = tree.size();\n    std::vector<long long> result(static_cast<std::size_t>(size));\n\
    \    if (size == 0) return result;\n    result[0] = size;\n    for (int source\
    \ = 0; source < size; source++) {\n        std::vector<int> distance(static_cast<std::size_t>(size),\
    \ -1);\n        std::queue<int> queue;\n        distance[static_cast<std::size_t>(source)]\
    \ = 0;\n        queue.push(source);\n        while (!queue.empty()) {\n      \
    \      const int vertex = queue.front();\n            queue.pop();\n         \
    \   for (const auto& edge : tree[vertex]) {\n                if (!edge.alive ||\
    \ distance[static_cast<std::size_t>(edge.to)] != -1) {\n                    continue;\n\
    \                }\n                distance[static_cast<std::size_t>(edge.to)]\
    \ =\n                    distance[static_cast<std::size_t>(vertex)] + 1;\n   \
    \             queue.push(edge.to);\n            }\n        }\n        for (int\
    \ target = source + 1; target < size; target++) {\n            result[static_cast<std::size_t>(\n\
    \                distance[static_cast<std::size_t>(target)]\n            )]++;\n\
    \        }\n    }\n    return result;\n}\n\nvoid test_edge_cases() {\n    Graph\
    \ empty;\n    assert(m1une::tree::tree_distance_frequency(empty).empty());\n\n\
    \    Graph single(1);\n    std::vector<long long> one{1};\n    assert(m1une::tree::tree_distance_frequency(single)\
    \ == one);\n\n    Graph path(100);\n    for (int vertex = 1; vertex < 100; vertex++)\
    \ {\n        path.add_edge(vertex - 1, vertex);\n    }\n    const std::vector<long\
    \ long> path_frequency =\n        m1une::tree::tree_distance_frequency(path);\n\
    \    for (int distance = 0; distance < 100; distance++) {\n        assert(path_frequency[static_cast<std::size_t>(distance)]\
    \ == 100 - distance);\n    }\n\n    Graph star(100);\n    for (int vertex = 1;\
    \ vertex < 100; vertex++) star.add_edge(0, vertex);\n    const std::vector<long\
    \ long> star_frequency =\n        m1une::tree::tree_distance_frequency(star);\n\
    \    assert(star_frequency[0] == 100);\n    assert(star_frequency[1] == 99);\n\
    \    assert(star_frequency[2] == 99LL * 98 / 2);\n    for (int distance = 3; distance\
    \ < 100; distance++) {\n        assert(star_frequency[static_cast<std::size_t>(distance)]\
    \ == 0);\n    }\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0xa93e72c16b40d5f8ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 500; trial++) {\n        const int size = int(random() % 40) + 1;\n      \
    \  Graph tree(size);\n        for (int vertex = 1; vertex < size; vertex++) {\n\
    \            tree.add_edge(vertex, int(random() % std::uint64_t(vertex)));\n \
    \       }\n        assert(\n            m1une::tree::tree_distance_frequency(tree)\
    \ ==\n            naive_distance_frequency(tree)\n        );\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    test_edge_cases();\n    test_randomized();\n\n\
    \    int size;\n    std::cin >> size;\n    Graph tree(size);\n    for (int edge\
    \ = 0; edge + 1 < size; edge++) {\n        int first, second;\n        std::cin\
    \ >> first >> second;\n        tree.add_edge(first, second);\n    }\n\n    const\
    \ std::vector<long long> frequency =\n        m1une::tree::tree_distance_frequency(tree);\n\
    \    for (int distance = 1; distance < size; distance++) {\n        if (distance\
    \ != 1) std::cout << ' ';\n        std::cout << frequency[static_cast<std::size_t>(distance)];\n\
    \    }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - graph/graph.hpp
  - graph/tree/distance_frequency.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/modint.hpp
  - graph/tree/centroid_decomposition.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/tree/distance_frequency.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 23:10:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/tree/distance_frequency.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/tree/distance_frequency.test.cpp
- /verify/verify/graph/tree/distance_frequency.test.cpp.html
title: verify/graph/tree/distance_frequency.test.cpp
---
