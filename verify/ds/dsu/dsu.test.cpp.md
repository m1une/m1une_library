---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"verify/ds/dsu/dsu.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\
    \n\n#include <bits/stdc++.h>\n#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#line 8 \"ds/dsu/dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct Dsu {\n   private:\n    int _n;\n\
    \    // parent_or_size[i] is the parent of i if it's >= 0.\n    // If it's < 0,\
    \ then i is a root and -parent_or_size[i] is the size of the group.\n    std::vector<int>\
    \ parent_or_size;\n\n    // Returns {new leader, absorbed leader}. The absorbed\
    \ leader is -1 when\n    // both vertices already belong to the same component.\n\
    \    std::pair<int, int> merge_leaders(int a, int b) {\n        int x = leader(a),\
    \ y = leader(b);\n        if (x == y) return {x, -1};\n        if (-parent_or_size[x]\
    \ < -parent_or_size[y]) std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n\
    \        parent_or_size[y] = x;\n        return {x, y};\n    }\n\n   public:\n\
    \    Dsu() : _n(0) {}\n    explicit Dsu(int n) : _n(n), parent_or_size(n, -1)\
    \ {}\n\n    // Merges the group containing 'a' with the group containing 'b'.\n\
    \    // Returns the leader of the merged group.\n    int merge(int a, int b) {\n\
    \        return merge_leaders(a, b).first;\n    }\n\n    // Invokes callback(new_leader,\
    \ absorbed_leader) after an actual merge.\n    // Returns the leader of the merged\
    \ group.\n    template <class Callback>\n    int merge(int a, int b, Callback&&\
    \ callback) {\n        std::pair<int, int> merged = merge_leaders(a, b);\n   \
    \     if (merged.second != -1) callback(merged.first, merged.second);\n      \
    \  return merged.first;\n    }\n\n    // Returns true if 'a' and 'b' belong to\
    \ the same group.\n    bool same(int a, int b) {\n        return leader(a) ==\
    \ leader(b);\n    }\n\n    // Returns the leader (representative) of the group\
    \ containing 'a'.\n    int leader(int a) {\n        if (parent_or_size[a] < 0)\
    \ return a;\n        // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    // Returns the size of the group containing 'a'.\n    int size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    // Returns a\
    \ list of all groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 6 \"verify/ds/dsu/dsu.test.cpp\"\nusing namespace\
    \ std;\n\nnamespace {\n\nvoid test_callback() {\n    m1une::ds::Dsu dsu(6);\n\
    \    vector<long long> sum = {1, 2, 3, 4, 5, 6};\n    int callback_count = 0;\n\
    \    auto combine = [&](int new_leader, int absorbed_leader) {\n        assert(dsu.leader(new_leader)\
    \ == new_leader);\n        assert(dsu.leader(absorbed_leader) == new_leader);\n\
    \        sum[new_leader] += sum[absorbed_leader];\n        callback_count++;\n\
    \    };\n\n    assert(dsu.merge(0, 1, combine) == 0);\n    assert(dsu.merge(2,\
    \ 3, combine) == 2);\n    assert(dsu.merge(0, 2, combine) == 0);\n    assert(sum[dsu.leader(3)]\
    \ == 10);\n    assert(callback_count == 3);\n\n    assert(dsu.merge(1, 3, combine)\
    \ == 0);\n    assert(callback_count == 3);\n\n    assert(dsu.merge(4, 0, combine)\
    \ == 0);\n    assert(sum[dsu.leader(4)] == 15);\n    assert(callback_count ==\
    \ 4);\n}\n\n}  // namespace\n\nint main() {\n    ios_base::sync_with_stdio(false);\n\
    \    cin.tie(nullptr);\n    test_callback();\n\n    int N, Q;\n    cin >> N >>\
    \ Q;\n    m1une::ds::Dsu dsu(N);\n    for (int q = 0; q < Q; ++q) {\n        int\
    \ t, u, v;\n        cin >> t >> u >> v;\n        if (t == 0) {\n            dsu.merge(u,\
    \ v);\n        } else {\n            cout << (int)dsu.same(u, v) << '\\n';\n \
    \       }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ <bits/stdc++.h>\n#include <cassert>\n#include \"../../../ds/dsu/dsu.hpp\"\n\
    using namespace std;\n\nnamespace {\n\nvoid test_callback() {\n    m1une::ds::Dsu\
    \ dsu(6);\n    vector<long long> sum = {1, 2, 3, 4, 5, 6};\n    int callback_count\
    \ = 0;\n    auto combine = [&](int new_leader, int absorbed_leader) {\n      \
    \  assert(dsu.leader(new_leader) == new_leader);\n        assert(dsu.leader(absorbed_leader)\
    \ == new_leader);\n        sum[new_leader] += sum[absorbed_leader];\n        callback_count++;\n\
    \    };\n\n    assert(dsu.merge(0, 1, combine) == 0);\n    assert(dsu.merge(2,\
    \ 3, combine) == 2);\n    assert(dsu.merge(0, 2, combine) == 0);\n    assert(sum[dsu.leader(3)]\
    \ == 10);\n    assert(callback_count == 3);\n\n    assert(dsu.merge(1, 3, combine)\
    \ == 0);\n    assert(callback_count == 3);\n\n    assert(dsu.merge(4, 0, combine)\
    \ == 0);\n    assert(sum[dsu.leader(4)] == 15);\n    assert(callback_count ==\
    \ 4);\n}\n\n}  // namespace\n\nint main() {\n    ios_base::sync_with_stdio(false);\n\
    \    cin.tie(nullptr);\n    test_callback();\n\n    int N, Q;\n    cin >> N >>\
    \ Q;\n    m1une::ds::Dsu dsu(N);\n    for (int q = 0; q < Q; ++q) {\n        int\
    \ t, u, v;\n        cin >> t >> u >> v;\n        if (t == 0) {\n            dsu.merge(u,\
    \ v);\n        } else {\n            cout << (int)dsu.same(u, v) << '\\n';\n \
    \       }\n    }\n}\n"
  dependsOn:
  - ds/dsu/dsu.hpp
  isVerificationFile: true
  path: verify/ds/dsu/dsu.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 06:09:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dsu/dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dsu/dsu.test.cpp
- /verify/verify/ds/dsu/dsu.test.cpp.html
title: verify/ds/dsu/dsu.test.cpp
---
