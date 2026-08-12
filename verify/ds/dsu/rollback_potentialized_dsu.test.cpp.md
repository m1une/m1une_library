---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/rollback_potentialized_dsu.hpp
    title: Rollback Potentialized DSU
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
  bundledCode: "#line 1 \"verify/ds/dsu/rollback_potentialized_dsu.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#line 1 \"ds/dsu/rollback_potentialized_dsu.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
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
    \ namespace m1une\n\n\n#line 12 \"ds/dsu/rollback_potentialized_dsu.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsGroup Group>\n\
    \    requires std::equality_comparable<typename Group::value_type>\nstruct RollbackPotentializedDsu\
    \ {\n    using T = typename Group::value_type;\n\n   private:\n    struct HistoryEntry\
    \ {\n        int first;\n        int first_value;\n        int second;\n     \
    \   int second_value;\n        T second_diff;\n\n        HistoryEntry(int first_index,\
    \ int first_parent, int second_index,\n                     int second_parent,\
    \ T diff)\n            : first(first_index),\n              first_value(first_parent),\n\
    \              second(second_index),\n              second_value(second_parent),\n\
    \              second_diff(std::move(diff)) {}\n    };\n\n    int _n;\n    int\
    \ _component_count;\n    std::vector<int> _parent_or_size;\n    std::vector<T>\
    \ _diff_to_parent;\n    std::vector<HistoryEntry> _history;\n    std::vector<std::size_t>\
    \ _checkpoints;\n\n    static int check_size(int n) {\n        assert(0 <= n);\n\
    \        return n;\n    }\n\n    std::pair<int, T> leader_and_potential(int vertex)\
    \ const {\n        assert(0 <= vertex && vertex < _n);\n        T result = Group::id();\n\
    \        while (_parent_or_size[vertex] >= 0) {\n            result = Group::op(_diff_to_parent[vertex],\
    \ result);\n            vertex = _parent_or_size[vertex];\n        }\n       \
    \ return {vertex, std::move(result)};\n    }\n\n   public:\n    RollbackPotentializedDsu()\
    \ : RollbackPotentializedDsu(0) {}\n\n    explicit RollbackPotentializedDsu(int\
    \ n)\n        : _n(check_size(n)),\n          _component_count(_n),\n        \
    \  _parent_or_size(_n, -1),\n          _diff_to_parent(_n, Group::id()) {}\n\n\
    \    int size() const { return _n; }\n    bool empty() const { return _n == 0;\
    \ }\n    int component_count() const { return _component_count; }\n    int snapshot_count()\
    \ const { return int(_checkpoints.size()); }\n\n    void reserve_snapshots(int\
    \ count) {\n        assert(0 <= count);\n        _checkpoints.reserve(count);\n\
    \    }\n\n    int leader(int vertex) const {\n        return leader_and_potential(vertex).first;\n\
    \    }\n\n    bool same(int first, int second) const {\n        return leader(first)\
    \ == leader(second);\n    }\n\n    int group_size(int vertex) const {\n      \
    \  return -_parent_or_size[leader(vertex)];\n    }\n\n    int size(int vertex)\
    \ const { return group_size(vertex); }\n\n    T potential(int vertex) const {\n\
    \        return leader_and_potential(vertex).second;\n    }\n\n    T diff(int\
    \ first, int second) const {\n        assert(same(first, second));\n        return\
    \ Group::op(Group::inv(potential(first)), potential(second));\n    }\n\n    int\
    \ parent_or_size(int vertex) const {\n        assert(0 <= vertex && vertex < _n);\n\
    \        return _parent_or_size[vertex];\n    }\n\n    bool merge(int first, int\
    \ second, const T& difference) {\n        auto [first_root, first_potential] =\
    \ leader_and_potential(first);\n        auto [second_root, second_potential] =\
    \ leader_and_potential(second);\n        if (first_root == second_root) {\n  \
    \          return Group::op(Group::inv(first_potential), second_potential) ==\
    \ difference;\n        }\n\n        T second_from_first = Group::op(\n       \
    \     Group::op(first_potential, difference),\n            Group::inv(second_potential)\n\
    \        );\n        if (-_parent_or_size[first_root] < -_parent_or_size[second_root])\
    \ {\n            std::swap(first_root, second_root);\n            second_from_first\
    \ = Group::inv(second_from_first);\n        }\n\n        if (!_checkpoints.empty())\
    \ {\n            _history.emplace_back(\n                first_root, _parent_or_size[first_root],\
    \ second_root,\n                _parent_or_size[second_root], _diff_to_parent[second_root]\n\
    \            );\n        }\n        _parent_or_size[first_root] += _parent_or_size[second_root];\n\
    \        _parent_or_size[second_root] = first_root;\n        _diff_to_parent[second_root]\
    \ = std::move(second_from_first);\n        --_component_count;\n        return\
    \ true;\n    }\n\n   private:\n    void restore_one() {\n        HistoryEntry\
    \ entry = std::move(_history.back());\n        _history.pop_back();\n        _parent_or_size[entry.first]\
    \ = entry.first_value;\n        _parent_or_size[entry.second] = entry.second_value;\n\
    \        _diff_to_parent[entry.second] = std::move(entry.second_diff);\n     \
    \   ++_component_count;\n    }\n\n   public:\n    int snapshot() { _checkpoints.push_back(_history.size());\
    \ return int(_checkpoints.size()); }\n\n    void rollback(int state) {\n     \
    \   assert(1 <= state && state <= snapshot_count());\n        while (_history.size()\
    \ > _checkpoints[state - 1]) restore_one();\n        _checkpoints.resize(state);\n\
    \    }\n\n    void clear_history() { _history.clear(); _checkpoints.clear(); }\n\
    \n    std::vector<std::vector<int>> groups() const {\n        std::vector<int>\
    \ leaders(_n);\n        std::vector<int> sizes(_n);\n        for (int vertex =\
    \ 0; vertex < _n; ++vertex) {\n            leaders[vertex] = leader(vertex);\n\
    \            ++sizes[leaders[vertex]];\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int vertex = 0; vertex < _n; ++vertex) {\n       \
    \     result[vertex].reserve(sizes[vertex]);\n        }\n        for (int vertex\
    \ = 0; vertex < _n; ++vertex) {\n            result[leaders[vertex]].push_back(vertex);\n\
    \        }\n        result.erase(\n            std::remove_if(\n             \
    \   result.begin(), result.end(),\n                [](const std::vector<int>&\
    \ group) { return group.empty(); }\n            ),\n            result.end()\n\
    \        );\n        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/ds/dsu/rollback_potentialized_dsu.test.cpp\"\n\n\
    #include <array>\n#line 7 \"verify/ds/dsu/rollback_potentialized_dsu.test.cpp\"\
    \n#include <iostream>\n#include <random>\n#include <tuple>\n#line 11 \"verify/ds/dsu/rollback_potentialized_dsu.test.cpp\"\
    \n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n   \
    \ using value_type = T;\n    static constexpr bool commutative = true;\n\n   \
    \ // Returns the identity element for addition, which is 0.\n    static constexpr\
    \ T id() {\n        return T(0);\n    }\n\n    // Returns the sum of a and b.\n\
    \    static constexpr T op(const T& a, const T& b) {\n        return a + b;\n\
    \    }\n\n    static constexpr T inv(const T& x) {\n        return -x;\n    }\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 13 \"verify/ds/dsu/rollback_potentialized_dsu.test.cpp\"\
    \n\nnamespace {\n\nusing Add = m1une::monoid::Add<long long>;\nusing Dsu = m1une::ds::RollbackPotentializedDsu<Add>;\n\
    \nstruct PermutationGroup {\n    using value_type = std::array<int, 3>;\n\n  \
    \  static value_type id() { return {0, 1, 2}; }\n\n    static value_type op(const\
    \ value_type& first, const value_type& second) {\n        value_type result;\n\
    \        for (int index = 0; index < 3; ++index) {\n            result[index]\
    \ = second[first[index]];\n        }\n        return result;\n    }\n\n    static\
    \ value_type inv(const value_type& value) {\n        value_type result;\n    \
    \    for (int index = 0; index < 3; ++index) result[value[index]] = index;\n \
    \       return result;\n    }\n};\n\nvoid noncommutative_test() {\n    using Permutation\
    \ = PermutationGroup::value_type;\n    m1une::ds::RollbackPotentializedDsu<PermutationGroup>\
    \ dsu(4);\n    Permutation rotate = {1, 2, 0};\n    Permutation swap_last = {0,\
    \ 2, 1};\n    assert(dsu.merge(0, 1, rotate));\n    int state = dsu.snapshot();\n\
    \    assert(dsu.merge(1, 2, swap_last));\n    Permutation composed = PermutationGroup::op(rotate,\
    \ swap_last);\n    assert(dsu.diff(0, 2) == composed);\n    assert(!dsu.merge(0,\
    \ 2, PermutationGroup::op(swap_last, rotate)));\n    dsu.rollback(state);\n  \
    \  assert(!dsu.same(0, 2));\n}\n\nvoid randomized_test() {\n    constexpr int\
    \ size = 18;\n    Dsu dsu(size);\n    std::vector<std::vector<long long>> graph(size,\
    \ std::vector<long long>(size));\n    std::vector<std::vector<bool>> edge(size,\
    \ std::vector<bool>(size));\n    std::vector<std::tuple<int, int, long long>>\
    \ history;\n    std::mt19937 random(0);\n\n    auto rebuild = [&] {\n        graph.assign(size,\
    \ std::vector<long long>(size));\n        edge.assign(size, std::vector<bool>(size));\n\
    \        for (const auto& [first, second, difference] : history) {\n         \
    \   edge[first][second] = edge[second][first] = true;\n            graph[first][second]\
    \ = difference;\n            graph[second][first] = -difference;\n        }\n\
    \    };\n\n    auto naive_potential = [&](int start) {\n        std::vector<bool>\
    \ seen(size);\n        std::vector<long long> potential(size);\n        std::vector<int>\
    \ stack = {start};\n        seen[start] = true;\n        while (!stack.empty())\
    \ {\n            int vertex = stack.back();\n            stack.pop_back();\n \
    \           for (int next = 0; next < size; ++next) {\n                if (!edge[vertex][next]\
    \ || seen[next]) continue;\n                seen[next] = true;\n             \
    \   potential[next] = potential[vertex] + graph[vertex][next];\n             \
    \   stack.push_back(next);\n            }\n        }\n        return std::pair(std::move(seen),\
    \ std::move(potential));\n    };\n\n    auto validate = [&] {\n        for (int\
    \ first = 0; first < size; ++first) {\n            auto [seen, potential] = naive_potential(first);\n\
    \            for (int second = 0; second < size; ++second) {\n               \
    \ assert(dsu.same(first, second) == seen[second]);\n                if (seen[second])\
    \ {\n                    assert(dsu.diff(first, second) == potential[second]);\n\
    \                }\n            }\n        }\n    };\n\n    for (int round = 0;\
    \ round < 120; ++round) {\n        int state = dsu.snapshot();\n        std::size_t\
    \ history_size = history.size();\n        int update_count = 1 + int(random()\
    \ % 8);\n        for (int step = 0; step < update_count; ++step) {\n         \
    \   int first = int(random() % size);\n            int second = int(random() %\
    \ size);\n            auto [seen, potential] = naive_potential(first);\n     \
    \       long long difference = seen[second]\n                ? potential[second]\n\
    \                : static_cast<long long>(int(random() % 41) - 20);\n        \
    \    bool consistent = dsu.merge(first, second, difference);\n            assert(consistent);\n\
    \            if (!seen[second]) history.emplace_back(first, second, difference);\n\
    \            rebuild();\n            validate();\n        }\n\n        dsu.rollback(state);\n\
    \        history.resize(history_size);\n        rebuild();\n        validate();\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    noncommutative_test();\n   \
    \ randomized_test();\n\n    int vertex_count, query_count;\n    std::cin >> vertex_count\
    \ >> query_count;\n    Dsu dsu(vertex_count);\n    for (int query = 0; query <\
    \ query_count; ++query) {\n        int type, first, second;\n        std::cin\
    \ >> type >> first >> second;\n        if (type == 0) {\n            long long\
    \ difference;\n            std::cin >> difference;\n            dsu.merge(first,\
    \ second, difference);\n        } else if (dsu.same(first, second)) {\n      \
    \      std::cout << dsu.diff(first, second) << '\\n';\n        } else {\n    \
    \        std::cout << \"?\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#include \"../../../ds/dsu/rollback_potentialized_dsu.hpp\"\n\n#include <array>\n\
    #include <cassert>\n#include <iostream>\n#include <random>\n#include <tuple>\n\
    #include <vector>\n\n#include \"../../../monoid/add.hpp\"\n\nnamespace {\n\nusing\
    \ Add = m1une::monoid::Add<long long>;\nusing Dsu = m1une::ds::RollbackPotentializedDsu<Add>;\n\
    \nstruct PermutationGroup {\n    using value_type = std::array<int, 3>;\n\n  \
    \  static value_type id() { return {0, 1, 2}; }\n\n    static value_type op(const\
    \ value_type& first, const value_type& second) {\n        value_type result;\n\
    \        for (int index = 0; index < 3; ++index) {\n            result[index]\
    \ = second[first[index]];\n        }\n        return result;\n    }\n\n    static\
    \ value_type inv(const value_type& value) {\n        value_type result;\n    \
    \    for (int index = 0; index < 3; ++index) result[value[index]] = index;\n \
    \       return result;\n    }\n};\n\nvoid noncommutative_test() {\n    using Permutation\
    \ = PermutationGroup::value_type;\n    m1une::ds::RollbackPotentializedDsu<PermutationGroup>\
    \ dsu(4);\n    Permutation rotate = {1, 2, 0};\n    Permutation swap_last = {0,\
    \ 2, 1};\n    assert(dsu.merge(0, 1, rotate));\n    int state = dsu.snapshot();\n\
    \    assert(dsu.merge(1, 2, swap_last));\n    Permutation composed = PermutationGroup::op(rotate,\
    \ swap_last);\n    assert(dsu.diff(0, 2) == composed);\n    assert(!dsu.merge(0,\
    \ 2, PermutationGroup::op(swap_last, rotate)));\n    dsu.rollback(state);\n  \
    \  assert(!dsu.same(0, 2));\n}\n\nvoid randomized_test() {\n    constexpr int\
    \ size = 18;\n    Dsu dsu(size);\n    std::vector<std::vector<long long>> graph(size,\
    \ std::vector<long long>(size));\n    std::vector<std::vector<bool>> edge(size,\
    \ std::vector<bool>(size));\n    std::vector<std::tuple<int, int, long long>>\
    \ history;\n    std::mt19937 random(0);\n\n    auto rebuild = [&] {\n        graph.assign(size,\
    \ std::vector<long long>(size));\n        edge.assign(size, std::vector<bool>(size));\n\
    \        for (const auto& [first, second, difference] : history) {\n         \
    \   edge[first][second] = edge[second][first] = true;\n            graph[first][second]\
    \ = difference;\n            graph[second][first] = -difference;\n        }\n\
    \    };\n\n    auto naive_potential = [&](int start) {\n        std::vector<bool>\
    \ seen(size);\n        std::vector<long long> potential(size);\n        std::vector<int>\
    \ stack = {start};\n        seen[start] = true;\n        while (!stack.empty())\
    \ {\n            int vertex = stack.back();\n            stack.pop_back();\n \
    \           for (int next = 0; next < size; ++next) {\n                if (!edge[vertex][next]\
    \ || seen[next]) continue;\n                seen[next] = true;\n             \
    \   potential[next] = potential[vertex] + graph[vertex][next];\n             \
    \   stack.push_back(next);\n            }\n        }\n        return std::pair(std::move(seen),\
    \ std::move(potential));\n    };\n\n    auto validate = [&] {\n        for (int\
    \ first = 0; first < size; ++first) {\n            auto [seen, potential] = naive_potential(first);\n\
    \            for (int second = 0; second < size; ++second) {\n               \
    \ assert(dsu.same(first, second) == seen[second]);\n                if (seen[second])\
    \ {\n                    assert(dsu.diff(first, second) == potential[second]);\n\
    \                }\n            }\n        }\n    };\n\n    for (int round = 0;\
    \ round < 120; ++round) {\n        int state = dsu.snapshot();\n        std::size_t\
    \ history_size = history.size();\n        int update_count = 1 + int(random()\
    \ % 8);\n        for (int step = 0; step < update_count; ++step) {\n         \
    \   int first = int(random() % size);\n            int second = int(random() %\
    \ size);\n            auto [seen, potential] = naive_potential(first);\n     \
    \       long long difference = seen[second]\n                ? potential[second]\n\
    \                : static_cast<long long>(int(random() % 41) - 20);\n        \
    \    bool consistent = dsu.merge(first, second, difference);\n            assert(consistent);\n\
    \            if (!seen[second]) history.emplace_back(first, second, difference);\n\
    \            rebuild();\n            validate();\n        }\n\n        dsu.rollback(state);\n\
    \        history.resize(history_size);\n        rebuild();\n        validate();\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    noncommutative_test();\n   \
    \ randomized_test();\n\n    int vertex_count, query_count;\n    std::cin >> vertex_count\
    \ >> query_count;\n    Dsu dsu(vertex_count);\n    for (int query = 0; query <\
    \ query_count; ++query) {\n        int type, first, second;\n        std::cin\
    \ >> type >> first >> second;\n        if (type == 0) {\n            long long\
    \ difference;\n            std::cin >> difference;\n            dsu.merge(first,\
    \ second, difference);\n        } else if (dsu.same(first, second)) {\n      \
    \      std::cout << dsu.diff(first, second) << '\\n';\n        } else {\n    \
    \        std::cout << \"?\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - ds/dsu/rollback_potentialized_dsu.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/dsu/rollback_potentialized_dsu.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dsu/rollback_potentialized_dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dsu/rollback_potentialized_dsu.test.cpp
- /verify/verify/ds/dsu/rollback_potentialized_dsu.test.cpp.html
title: verify/ds/dsu/rollback_potentialized_dsu.test.cpp
---
