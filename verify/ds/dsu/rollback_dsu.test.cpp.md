---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/rollback_dsu.hpp
    title: Rollback DSU
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_unionfind
    links:
    - https://judge.yosupo.jp/problem/persistent_unionfind
  bundledCode: "#line 1 \"verify/ds/dsu/rollback_dsu.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/persistent_unionfind\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <numeric>\n#include <random>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"ds/dsu/rollback_dsu.hpp\"\n\
    \n\n\n#line 7 \"ds/dsu/rollback_dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \nstruct RollbackDsu {\n   private:\n    struct HistoryEntry {\n        int first;\n\
    \        int first_value;\n        int second;\n        int second_value;\n  \
    \  };\n\n    int _n;\n    int _component_count;\n    std::vector<int> parent_or_size;\n\
    \    std::vector<HistoryEntry> history;\n\n    static int check_size(int n) {\n\
    \        assert(0 <= n);\n        return n;\n    }\n\n   public:\n    RollbackDsu()\
    \ : RollbackDsu(0) {}\n\n    explicit RollbackDsu(int n)\n        : _n(check_size(n)),\
    \ _component_count(_n), parent_or_size(_n, -1) {}\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    int component_count() const {\n        return _component_count;\n\
    \    }\n\n    int history_size() const {\n        return int(history.size());\n\
    \    }\n\n    void reserve_history(int count) {\n        assert(0 <= count);\n\
    \        history.reserve(count);\n    }\n\n    int leader(int vertex) const {\n\
    \        assert(0 <= vertex && vertex < _n);\n        while (parent_or_size[vertex]\
    \ >= 0) vertex = parent_or_size[vertex];\n        return vertex;\n    }\n\n  \
    \  bool same(int first, int second) const {\n        return leader(first) == leader(second);\n\
    \    }\n\n    int group_size(int vertex) const {\n        return -parent_or_size[leader(vertex)];\n\
    \    }\n\n    int size(int vertex) const {\n        return group_size(vertex);\n\
    \    }\n\n    bool merge(int first, int second) {\n        first = leader(first);\n\
    \        second = leader(second);\n        if (first == second) {\n          \
    \  history.push_back(HistoryEntry{-1, 0, -1, 0});\n            return false;\n\
    \        }\n        if (-parent_or_size[first] < -parent_or_size[second]) {\n\
    \            std::swap(first, second);\n        }\n        history.push_back(HistoryEntry{\n\
    \            first, parent_or_size[first], second, parent_or_size[second]\n  \
    \      });\n        parent_or_size[first] += parent_or_size[second];\n       \
    \ parent_or_size[second] = first;\n        _component_count--;\n        return\
    \ true;\n    }\n\n    bool undo() {\n        if (history.empty()) return false;\n\
    \        const HistoryEntry entry = history.back();\n        history.pop_back();\n\
    \        if (entry.first == -1) return true;\n        parent_or_size[entry.first]\
    \ = entry.first_value;\n        parent_or_size[entry.second] = entry.second_value;\n\
    \        _component_count++;\n        return true;\n    }\n\n    int snapshot()\
    \ const {\n        return history_size();\n    }\n\n    void rollback(int state)\
    \ {\n        assert(0 <= state && state <= history_size());\n        while (history_size()\
    \ > state) undo();\n    }\n\n    std::vector<std::vector<int>> groups() const\
    \ {\n        std::vector<int> leader_buffer(_n);\n        std::vector<int> group_sizes(_n,\
    \ 0);\n        for (int vertex = 0; vertex < _n; vertex++) {\n            leader_buffer[vertex]\
    \ = leader(vertex);\n            group_sizes[leader_buffer[vertex]]++;\n     \
    \   }\n        std::vector<std::vector<int>> result(_n);\n        for (int vertex\
    \ = 0; vertex < _n; vertex++) {\n            result[vertex].reserve(group_sizes[vertex]);\n\
    \        }\n        for (int vertex = 0; vertex < _n; vertex++) {\n          \
    \  result[leader_buffer[vertex]].push_back(vertex);\n        }\n        result.erase(\n\
    \            std::remove_if(\n                result.begin(), result.end(),\n\
    \                [](const std::vector<int>& group) { return group.empty(); }\n\
    \            ),\n            result.end()\n        );\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"verify/ds/dsu/rollback_dsu.test.cpp\"\
    \n\nnamespace {\n\n#ifndef NDEBUG\nint naive_leader(std::vector<int>& parent,\
    \ int vertex) {\n    if (parent[vertex] == vertex) return vertex;\n    return\
    \ parent[vertex] = naive_leader(parent, parent[vertex]);\n}\n\nvoid validate(\n\
    \    const m1une::ds::RollbackDsu& dsu,\n    std::vector<int> parent\n) {\n  \
    \  const int n = int(parent.size());\n    int component_count = 0;\n    std::vector<int>\
    \ group_size(n, 0);\n    for (int vertex = 0; vertex < n; vertex++) {\n      \
    \  int root = naive_leader(parent, vertex);\n        group_size[root]++;\n   \
    \     if (root == vertex) component_count++;\n    }\n    assert(dsu.component_count()\
    \ == component_count);\n    assert(int(dsu.groups().size()) == component_count);\n\
    \    for (int first = 0; first < n; first++) {\n        assert(dsu.group_size(first)\
    \ == group_size[naive_leader(parent, first)]);\n        for (int second = 0; second\
    \ < n; second++) {\n            assert(dsu.same(first, second) ==\n          \
    \         (naive_leader(parent, first) == naive_leader(parent, second)));\n  \
    \      }\n    }\n}\n\nvoid randomized_test() {\n    std::mt19937 random(712367);\n\
    \    for (int test = 0; test < 80; test++) {\n        const int n = 1 + int(random()\
    \ % 18);\n        m1une::ds::RollbackDsu dsu(n);\n        dsu.reserve_history(600);\n\
    \        std::vector<std::vector<int>> states(1, std::vector<int>(n));\n     \
    \   std::iota(states[0].begin(), states[0].end(), 0);\n\n        for (int operation\
    \ = 0; operation < 500; operation++) {\n            int type = int(random() %\
    \ 5);\n            if (type <= 2 || states.size() == 1) {\n                int\
    \ first = int(random() % n);\n                int second = int(random() % n);\n\
    \                std::vector<int> next = states.back();\n                int first_root\
    \ = naive_leader(next, first);\n                int second_root = naive_leader(next,\
    \ second);\n                bool changed = first_root != second_root;\n      \
    \          if (changed) next[second_root] = first_root;\n                assert(dsu.merge(first,\
    \ second) == changed);\n                states.push_back(std::move(next));\n \
    \           } else if (type == 3) {\n                assert(dsu.undo());\n   \
    \             states.pop_back();\n            } else {\n                int state\
    \ = int(random() % states.size());\n                dsu.rollback(state);\n   \
    \             states.resize(state + 1);\n            }\n            assert(dsu.snapshot()\
    \ == int(states.size()) - 1);\n            validate(dsu, states.back());\n   \
    \     }\n        dsu.rollback(0);\n        assert(!dsu.undo());\n        assert(dsu.component_count()\
    \ == n);\n    }\n}\n#endif\n\nstruct Operation {\n    int first;\n    int second;\n\
    };\n\nstruct Query {\n    int first;\n    int second;\n    int answer_index;\n\
    };\n\n}  // namespace\n\nint main() {\n#ifndef NDEBUG\n    randomized_test();\n\
    #endif\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n\
    \    int vertex_count, query_count;\n    std::cin >> vertex_count >> query_count;\n\
    \    std::vector<std::vector<int>> children(query_count + 1);\n    std::vector<Operation>\
    \ operation(query_count + 1, Operation{-1, -1});\n    std::vector<std::vector<Query>>\
    \ queries(query_count + 1);\n    int answer_count = 0;\n\n    for (int query =\
    \ 0; query < query_count; query++) {\n        int type, parent, first, second;\n\
    \        std::cin >> type >> parent >> first >> second;\n        const int parent_node\
    \ = parent + 1;\n        if (type == 0) {\n            const int node = query\
    \ + 1;\n            children[parent_node].push_back(node);\n            operation[node]\
    \ = Operation{first, second};\n        } else {\n            queries[parent_node].push_back(Query{first,\
    \ second, answer_count++});\n        }\n    }\n\n    std::vector<int> answer(answer_count);\n\
    \    m1une::ds::RollbackDsu dsu(vertex_count);\n    std::vector<std::pair<int,\
    \ bool>> stack(1, std::make_pair(0, false));\n    while (!stack.empty()) {\n \
    \       auto [node, exiting] = stack.back();\n        stack.pop_back();\n    \
    \    if (exiting) {\n            if (node != 0) dsu.undo();\n            continue;\n\
    \        }\n\n        if (node != 0) dsu.merge(operation[node].first, operation[node].second);\n\
    \        for (const Query& query : queries[node]) {\n            answer[query.answer_index]\
    \ = dsu.same(query.first, query.second);\n        }\n        stack.emplace_back(node,\
    \ true);\n        for (auto it = children[node].rbegin(); it != children[node].rend();\
    \ ++it) {\n            stack.emplace_back(*it, false);\n        }\n    }\n\n \
    \   for (int value : answer) std::cout << value << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\
    \n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <numeric>\n\
    #include <random>\n#include <utility>\n#include <vector>\n\n#include \"../../../ds/dsu/rollback_dsu.hpp\"\
    \n\nnamespace {\n\n#ifndef NDEBUG\nint naive_leader(std::vector<int>& parent,\
    \ int vertex) {\n    if (parent[vertex] == vertex) return vertex;\n    return\
    \ parent[vertex] = naive_leader(parent, parent[vertex]);\n}\n\nvoid validate(\n\
    \    const m1une::ds::RollbackDsu& dsu,\n    std::vector<int> parent\n) {\n  \
    \  const int n = int(parent.size());\n    int component_count = 0;\n    std::vector<int>\
    \ group_size(n, 0);\n    for (int vertex = 0; vertex < n; vertex++) {\n      \
    \  int root = naive_leader(parent, vertex);\n        group_size[root]++;\n   \
    \     if (root == vertex) component_count++;\n    }\n    assert(dsu.component_count()\
    \ == component_count);\n    assert(int(dsu.groups().size()) == component_count);\n\
    \    for (int first = 0; first < n; first++) {\n        assert(dsu.group_size(first)\
    \ == group_size[naive_leader(parent, first)]);\n        for (int second = 0; second\
    \ < n; second++) {\n            assert(dsu.same(first, second) ==\n          \
    \         (naive_leader(parent, first) == naive_leader(parent, second)));\n  \
    \      }\n    }\n}\n\nvoid randomized_test() {\n    std::mt19937 random(712367);\n\
    \    for (int test = 0; test < 80; test++) {\n        const int n = 1 + int(random()\
    \ % 18);\n        m1une::ds::RollbackDsu dsu(n);\n        dsu.reserve_history(600);\n\
    \        std::vector<std::vector<int>> states(1, std::vector<int>(n));\n     \
    \   std::iota(states[0].begin(), states[0].end(), 0);\n\n        for (int operation\
    \ = 0; operation < 500; operation++) {\n            int type = int(random() %\
    \ 5);\n            if (type <= 2 || states.size() == 1) {\n                int\
    \ first = int(random() % n);\n                int second = int(random() % n);\n\
    \                std::vector<int> next = states.back();\n                int first_root\
    \ = naive_leader(next, first);\n                int second_root = naive_leader(next,\
    \ second);\n                bool changed = first_root != second_root;\n      \
    \          if (changed) next[second_root] = first_root;\n                assert(dsu.merge(first,\
    \ second) == changed);\n                states.push_back(std::move(next));\n \
    \           } else if (type == 3) {\n                assert(dsu.undo());\n   \
    \             states.pop_back();\n            } else {\n                int state\
    \ = int(random() % states.size());\n                dsu.rollback(state);\n   \
    \             states.resize(state + 1);\n            }\n            assert(dsu.snapshot()\
    \ == int(states.size()) - 1);\n            validate(dsu, states.back());\n   \
    \     }\n        dsu.rollback(0);\n        assert(!dsu.undo());\n        assert(dsu.component_count()\
    \ == n);\n    }\n}\n#endif\n\nstruct Operation {\n    int first;\n    int second;\n\
    };\n\nstruct Query {\n    int first;\n    int second;\n    int answer_index;\n\
    };\n\n}  // namespace\n\nint main() {\n#ifndef NDEBUG\n    randomized_test();\n\
    #endif\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n\
    \    int vertex_count, query_count;\n    std::cin >> vertex_count >> query_count;\n\
    \    std::vector<std::vector<int>> children(query_count + 1);\n    std::vector<Operation>\
    \ operation(query_count + 1, Operation{-1, -1});\n    std::vector<std::vector<Query>>\
    \ queries(query_count + 1);\n    int answer_count = 0;\n\n    for (int query =\
    \ 0; query < query_count; query++) {\n        int type, parent, first, second;\n\
    \        std::cin >> type >> parent >> first >> second;\n        const int parent_node\
    \ = parent + 1;\n        if (type == 0) {\n            const int node = query\
    \ + 1;\n            children[parent_node].push_back(node);\n            operation[node]\
    \ = Operation{first, second};\n        } else {\n            queries[parent_node].push_back(Query{first,\
    \ second, answer_count++});\n        }\n    }\n\n    std::vector<int> answer(answer_count);\n\
    \    m1une::ds::RollbackDsu dsu(vertex_count);\n    std::vector<std::pair<int,\
    \ bool>> stack(1, std::make_pair(0, false));\n    while (!stack.empty()) {\n \
    \       auto [node, exiting] = stack.back();\n        stack.pop_back();\n    \
    \    if (exiting) {\n            if (node != 0) dsu.undo();\n            continue;\n\
    \        }\n\n        if (node != 0) dsu.merge(operation[node].first, operation[node].second);\n\
    \        for (const Query& query : queries[node]) {\n            answer[query.answer_index]\
    \ = dsu.same(query.first, query.second);\n        }\n        stack.emplace_back(node,\
    \ true);\n        for (auto it = children[node].rbegin(); it != children[node].rend();\
    \ ++it) {\n            stack.emplace_back(*it, false);\n        }\n    }\n\n \
    \   for (int value : answer) std::cout << value << '\\n';\n}\n"
  dependsOn:
  - ds/dsu/rollback_dsu.hpp
  isVerificationFile: true
  path: verify/ds/dsu/rollback_dsu.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 19:52:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dsu/rollback_dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dsu/rollback_dsu.test.cpp
- /verify/verify/ds/dsu/rollback_dsu.test.cpp.html
title: verify/ds/dsu/rollback_dsu.test.cpp
---
