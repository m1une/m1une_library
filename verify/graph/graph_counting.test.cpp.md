---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/counting.hpp
    title: Graph Counting
  - icon: ':question:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':question:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <numeric>\n#include <vector>\n\
    \n#include \"../../graph/counting.hpp\"\n#include \"../../math/modint.hpp\"\n\n\
    using mint = m1une::math::modint998244353;\n\nvoid assert_prefix(const std::vector<mint>&\
    \ actual, const std::vector<long long>& expected) {\n    assert(int(actual.size())\
    \ >= int(expected.size()));\n    for (int i = 0; i < int(expected.size()); i++)\
    \ {\n        assert(actual[i] == mint(expected[i]));\n    }\n}\n\nstruct Dsu {\n\
    \    std::vector<int> parent;\n\n    explicit Dsu(int n) : parent(n) {\n     \
    \   std::iota(parent.begin(), parent.end(), 0);\n    }\n\n    int leader(int v)\
    \ {\n        if (parent[v] == v) return v;\n        return parent[v] = leader(parent[v]);\n\
    \    }\n\n    bool merge(int a, int b) {\n        a = leader(a);\n        b =\
    \ leader(b);\n        if (a == b) return false;\n        parent[b] = a;\n    \
    \    return true;\n    }\n};\n\nstruct UndirectedBrute {\n    long long all =\
    \ 0;\n    long long connected = 0;\n    long long tree = 0;\n    long long forest\
    \ = 0;\n    long long unicyclic_connected = 0;\n    long long connected_eulerian\
    \ = 0;\n    long long bipartite = 0;\n    long long connected_bipartite = 0;\n\
    };\n\nbool is_bipartite(int n, const std::vector<std::vector<int>>& adjacency)\
    \ {\n    std::vector<int> color(n, -1);\n    for (int start = 0; start < n; start++)\
    \ {\n        if (color[start] != -1) continue;\n        color[start] = 0;\n  \
    \      std::vector<int> stack;\n        stack.push_back(start);\n        while\
    \ (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            for (int to : adjacency[v]) {\n                if (color[to] == -1)\
    \ {\n                    color[to] = color[v] ^ 1;\n                    stack.push_back(to);\n\
    \                } else if (color[to] == color[v]) {\n                    return\
    \ false;\n                }\n            }\n        }\n    }\n    return true;\n\
    }\n\nUndirectedBrute brute_undirected(int n) {\n    std::vector<std::pair<int,\
    \ int>> edges;\n    for (int i = 0; i < n; i++) {\n        for (int j = i + 1;\
    \ j < n; j++) edges.emplace_back(i, j);\n    }\n\n    UndirectedBrute result;\n\
    \    const int total = 1 << int(edges.size());\n    for (int mask = 0; mask <\
    \ total; mask++) {\n        result.all++;\n\n        Dsu dsu(n);\n        std::vector<int>\
    \ degree(n);\n        std::vector<std::vector<int>> adjacency(n);\n        bool\
    \ acyclic = true;\n        int edge_count = 0;\n        for (int bit = 0; bit\
    \ < int(edges.size()); bit++) {\n            if (((mask >> bit) & 1) == 0) continue;\n\
    \            const auto [u, v] = edges[bit];\n            edge_count++;\n    \
    \        degree[u]++;\n            degree[v]++;\n            adjacency[u].push_back(v);\n\
    \            adjacency[v].push_back(u);\n            if (!dsu.merge(u, v)) acyclic\
    \ = false;\n        }\n\n        int components = n;\n        for (int i = 0;\
    \ i < n; i++) {\n            if (dsu.leader(i) != i) components--;\n        }\n\
    \        const bool connected = n > 0 && components == 1;\n        const bool\
    \ bipartite = is_bipartite(n, adjacency);\n        const bool all_even =\n   \
    \         std::all_of(degree.begin(), degree.end(), [](int x) { return x % 2 ==\
    \ 0; });\n\n        if (connected) result.connected++;\n        if (n > 0 && connected\
    \ && edge_count == n - 1) result.tree++;\n        if (acyclic) result.forest++;\n\
    \        if (connected && edge_count == n) result.unicyclic_connected++;\n   \
    \     if (connected && all_even) result.connected_eulerian++;\n        if (bipartite)\
    \ result.bipartite++;\n        if (connected && bipartite) result.connected_bipartite++;\n\
    \    }\n    return result;\n}\n\nstruct DirectedBrute {\n    long long all = 0;\n\
    \    long long dag = 0;\n    long long strongly_connected = 0;\n};\n\nDirectedBrute\
    \ brute_directed(int n) {\n    std::vector<std::pair<int, int>> edges;\n    for\
    \ (int i = 0; i < n; i++) {\n        for (int j = 0; j < n; j++) {\n         \
    \   if (i != j) edges.emplace_back(i, j);\n        }\n    }\n\n    DirectedBrute\
    \ result;\n    const int total = 1 << int(edges.size());\n    for (int mask =\
    \ 0; mask < total; mask++) {\n        result.all++;\n        std::vector<std::vector<int>>\
    \ reach(n, std::vector<int>(n));\n        for (int bit = 0; bit < int(edges.size());\
    \ bit++) {\n            if (((mask >> bit) & 1) == 0) continue;\n            const\
    \ auto [from, to] = edges[bit];\n            reach[from][to] = 1;\n        }\n\
    \n        for (int k = 0; k < n; k++) {\n            for (int i = 0; i < n; i++)\
    \ {\n                if (!reach[i][k]) continue;\n                for (int j =\
    \ 0; j < n; j++) reach[i][j] = reach[i][j] || reach[k][j];\n            }\n  \
    \      }\n\n        bool dag = true;\n        for (int i = 0; i < n; i++) dag\
    \ = dag && !reach[i][i];\n\n        bool strongly_connected = n > 0;\n       \
    \ for (int i = 0; i < n; i++) {\n            for (int j = 0; j < n; j++) {\n \
    \               if (i != j && !reach[i][j]) strongly_connected = false;\n    \
    \        }\n        }\n\n        if (dag) result.dag++;\n        if (strongly_connected)\
    \ result.strongly_connected++;\n    }\n    return result;\n}\n\nstruct TournamentBrute\
    \ {\n    long long all = 0;\n    long long strongly_connected = 0;\n};\n\nTournamentBrute\
    \ brute_tournament(int n) {\n    std::vector<std::pair<int, int>> pairs;\n   \
    \ for (int i = 0; i < n; i++) {\n        for (int j = i + 1; j < n; j++) pairs.emplace_back(i,\
    \ j);\n    }\n\n    TournamentBrute result;\n    const int total = 1 << int(pairs.size());\n\
    \    for (int mask = 0; mask < total; mask++) {\n        result.all++;\n     \
    \   std::vector<std::vector<int>> reach(n, std::vector<int>(n));\n        for\
    \ (int bit = 0; bit < int(pairs.size()); bit++) {\n            const auto [u,\
    \ v] = pairs[bit];\n            if ((mask >> bit) & 1) {\n                reach[u][v]\
    \ = 1;\n            } else {\n                reach[v][u] = 1;\n            }\n\
    \        }\n        for (int k = 0; k < n; k++) {\n            for (int i = 0;\
    \ i < n; i++) {\n                if (!reach[i][k]) continue;\n               \
    \ for (int j = 0; j < n; j++) reach[i][j] = reach[i][j] || reach[k][j];\n    \
    \        }\n        }\n\n        bool strongly_connected = n > 0;\n        for\
    \ (int i = 0; i < n; i++) {\n            for (int j = 0; j < n; j++) {\n     \
    \           if (i != j && !reach[i][j]) strongly_connected = false;\n        \
    \    }\n        }\n        if (strongly_connected) result.strongly_connected++;\n\
    \    }\n    return result;\n}\n\nvoid test_undirected_counts() {\n    const int\
    \ maximum = 5;\n    const auto all = m1une::graph::count_labeled_undirected_graphs<mint>(maximum);\n\
    \    const auto connected = m1une::graph::count_labeled_connected_graphs<mint>(maximum);\n\
    \    const auto trees = m1une::graph::count_labeled_trees<mint>(maximum);\n  \
    \  const auto forests = m1une::graph::count_labeled_forests<mint>(maximum);\n\
    \    const auto unicyclic =\n        m1une::graph::count_labeled_unicyclic_connected_graphs<mint>(maximum);\n\
    \    const auto eulerian =\n        m1une::graph::count_labeled_connected_eulerian_graphs<mint>(maximum);\n\
    \    const auto bipartite = m1une::graph::count_labeled_bipartite_graphs<mint>(maximum);\n\
    \    const auto connected_bipartite =\n        m1une::graph::count_labeled_connected_bipartite_graphs<mint>(maximum);\n\
    \n    for (int n = 0; n <= maximum; n++) {\n        const UndirectedBrute brute\
    \ = brute_undirected(n);\n        assert(all[n] == mint(brute.all));\n       \
    \ assert(connected[n] == mint(brute.connected));\n        assert(trees[n] == mint(brute.tree));\n\
    \        assert(forests[n] == mint(brute.forest));\n        assert(unicyclic[n]\
    \ == mint(brute.unicyclic_connected));\n        assert(eulerian[n] == mint(brute.connected_eulerian));\n\
    \        assert(bipartite[n] == mint(brute.bipartite));\n        assert(connected_bipartite[n]\
    \ == mint(brute.connected_bipartite));\n    }\n\n    assert_prefix(connected,\
    \ std::vector<long long>{0, 1, 1, 4, 38, 728});\n    assert_prefix(forests, std::vector<long\
    \ long>{1, 1, 2, 7, 38, 291});\n    assert_prefix(unicyclic, std::vector<long\
    \ long>{0, 0, 0, 1, 15, 222});\n    assert_prefix(eulerian, std::vector<long long>{0,\
    \ 1, 0, 1, 3, 38});\n    assert_prefix(bipartite, std::vector<long long>{1, 1,\
    \ 2, 7, 41, 376});\n    assert_prefix(connected_bipartite, std::vector<long long>{0,\
    \ 1, 1, 3, 19, 195});\n}\n\nvoid test_directed_counts() {\n    const int maximum\
    \ = 4;\n    const auto all = m1une::graph::count_labeled_directed_graphs<mint>(maximum);\n\
    \    const auto dags = m1une::graph::count_labeled_dags<mint>(maximum);\n    const\
    \ auto strongly_connected =\n        m1une::graph::count_labeled_strongly_connected_digraphs<mint>(maximum);\n\
    \n    for (int n = 0; n <= maximum; n++) {\n        const DirectedBrute brute\
    \ = brute_directed(n);\n        assert(all[n] == mint(brute.all));\n        assert(dags[n]\
    \ == mint(brute.dag));\n        assert(strongly_connected[n] == mint(brute.strongly_connected));\n\
    \    }\n\n    assert_prefix(all, std::vector<long long>{1, 1, 4, 64, 4096});\n\
    \    assert_prefix(dags, std::vector<long long>{1, 1, 3, 25, 543});\n    assert_prefix(strongly_connected,\
    \ std::vector<long long>{0, 1, 1, 18, 1606});\n}\n\nvoid test_tournament_counts()\
    \ {\n    const int maximum = 5;\n    const auto all = m1une::graph::count_labeled_tournaments<mint>(maximum);\n\
    \    const auto strongly_connected =\n        m1une::graph::count_labeled_strongly_connected_tournaments<mint>(maximum);\n\
    \n    for (int n = 0; n <= maximum; n++) {\n        const TournamentBrute brute\
    \ = brute_tournament(n);\n        assert(all[n] == mint(brute.all));\n       \
    \ assert(strongly_connected[n] == mint(brute.strongly_connected));\n    }\n\n\
    \    assert_prefix(all, std::vector<long long>{1, 1, 2, 8, 64, 1024});\n    assert_prefix(strongly_connected,\
    \ std::vector<long long>{0, 1, 0, 2, 24, 544});\n}\n\nvoid test_unlabeled_trees()\
    \ {\n    const auto rooted = m1une::graph::count_unlabeled_rooted_trees<mint>(12);\n\
    \    const auto unrooted = m1une::graph::count_unlabeled_trees<mint>(12);\n\n\
    \    assert_prefix(rooted, std::vector<long long>{0, 1, 1, 2, 4, 9, 20, 48, 115});\n\
    \    assert_prefix(unrooted, std::vector<long long>{0, 1, 1, 1, 2, 3, 6, 11, 23,\
    \ 47, 106});\n}\n\nint main() {\n    test_undirected_counts();\n    test_directed_counts();\n\
    \    test_tournament_counts();\n    test_unlabeled_trees();\n\n    long long a,\
    \ b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n    return 0;\n\
    }\n\n"
  dependsOn:
  - graph/counting.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/combinatorics.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/graph/graph_counting.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/graph_counting.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/graph_counting.test.cpp
- /verify/verify/graph/graph_counting.test.cpp.html
title: verify/graph/graph_counting.test.cpp
---
