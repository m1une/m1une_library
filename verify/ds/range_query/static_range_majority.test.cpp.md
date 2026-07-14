---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/static_range_majority.hpp
    title: Static Range Majority
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
  bundledCode: "#line 1 \"verify/ds/range_query/static_range_majority.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/range_query/static_range_majority.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Static strict-majority queries\
    \ in O(log N) time.\ntemplate <class T>\nstruct StaticRangeMajority {\n    using\
    \ result_type = std::optional<T>;\n\n   private:\n    struct Vote {\n        int\
    \ candidate = -1;\n        int balance = 0;\n    };\n\n    int _n;\n    int _tree_size;\n\
    \    std::vector<T> _values;\n    std::vector<std::vector<int>> _positions;\n\
    \    std::vector<Vote> _tree;\n\n    static Vote combine(Vote first, Vote second)\
    \ {\n        if (first.balance == 0) return second;\n        if (second.balance\
    \ == 0) return first;\n        if (first.candidate == second.candidate) {\n  \
    \          return Vote{first.candidate, first.balance + second.balance};\n   \
    \     }\n        if (first.balance > second.balance) {\n            return Vote{first.candidate,\
    \ first.balance - second.balance};\n        }\n        if (second.balance > first.balance)\
    \ {\n            return Vote{second.candidate, second.balance - first.balance};\n\
    \        }\n        return Vote();\n    }\n\n    Vote range_vote(int left, int\
    \ right) const {\n        Vote left_vote;\n        Vote right_vote;\n        left\
    \ += _tree_size;\n        right += _tree_size;\n        while (left < right) {\n\
    \            if (left & 1) left_vote = combine(left_vote, _tree[left++]);\n  \
    \          if (right & 1) right_vote = combine(_tree[--right], right_vote);\n\
    \            left >>= 1;\n            right >>= 1;\n        }\n        return\
    \ combine(left_vote, right_vote);\n    }\n\n   public:\n    StaticRangeMajority()\
    \ : _n(0), _tree_size(1), _tree(2) {}\n\n    explicit StaticRangeMajority(const\
    \ std::vector<T>& values)\n        : _n(int(values.size())), _tree_size(1), _values(values)\
    \ {\n        std::sort(_values.begin(), _values.end());\n        _values.erase(\n\
    \            std::unique(_values.begin(), _values.end()),\n            _values.end()\n\
    \        );\n        _positions.resize(_values.size());\n\n        while (_tree_size\
    \ < _n) _tree_size <<= 1;\n        _tree.assign(2 * _tree_size, Vote());\n   \
    \     for (int index = 0; index < _n; index++) {\n            int rank = int(\n\
    \                std::lower_bound(\n                    _values.begin(), _values.end(),\
    \ values[index]\n                ) - _values.begin()\n            );\n       \
    \     _positions[rank].push_back(index);\n            _tree[_tree_size + index]\
    \ = Vote{rank, 1};\n        }\n        for (int node = _tree_size - 1; node >\
    \ 0; node--) {\n            _tree[node] = combine(_tree[node << 1], _tree[(node\
    \ << 1) | 1]);\n        }\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    // Returns\
    \ the unique value occurring more than half the time in\n    // [left, right),\
    \ or nullopt when no such value exists.\n    result_type query(int left, int right)\
    \ const {\n        assert(0 <= left && left < right && right <= _n);\n       \
    \ Vote vote = range_vote(left, right);\n        if (vote.balance == 0) return\
    \ std::nullopt;\n\n        const std::vector<int>& positions = _positions[vote.candidate];\n\
    \        int frequency = int(\n            std::lower_bound(positions.begin(),\
    \ positions.end(), right)\n            - std::lower_bound(positions.begin(), positions.end(),\
    \ left)\n        );\n        if (2LL * frequency <= right - left) return std::nullopt;\n\
    \        return _values[vote.candidate];\n    }\n\n    result_type majority(int\
    \ left, int right) const {\n        return query(left, right);\n    }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/static_range_majority.test.cpp\"\
    \n\n#line 6 \"verify/ds/range_query/static_range_majority.test.cpp\"\n#include\
    \ <cstdint>\n#include <iostream>\n#include <map>\n#line 11 \"verify/ds/range_query/static_range_majority.test.cpp\"\
    \n\nnamespace {\n\nstd::optional<int> brute(\n    const std::vector<int>& values,\n\
    \    int left,\n    int right\n) {\n    std::map<int, int> frequency;\n    for\
    \ (int index = left; index < right; index++) {\n        int count = ++frequency[values[index]];\n\
    \        if (count * 2 > right - left) return values[index];\n    }\n    return\
    \ std::nullopt;\n}\n\nvoid test_randomized() {\n    m1une::ds::StaticRangeMajority<int>\
    \ empty;\n    assert(empty.empty());\n    assert(empty.size() == 0);\n\n    std::uint64_t\
    \ state = 1414213562ULL;\n    auto random = [&]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 1000; trial++) {\n        int n = int(random() % 80) + 1;\n\
    \        std::vector<int> values(n);\n        for (int& value : values) value\
    \ = int(random() % 15) - 7;\n\n        m1une::ds::StaticRangeMajority<int> structure(values);\n\
    \        assert(structure.size() == n);\n        assert(!structure.empty());\n\
    \        for (int left = 0; left < n; left++) {\n            for (int right =\
    \ left + 1; right <= n; right++) {\n                std::optional<int> expected\
    \ = brute(values, left, right);\n                assert(structure.query(left,\
    \ right) == expected);\n                assert(structure.majority(left, right)\
    \ == expected);\n            }\n        }\n    }\n}\n\n}  // namespace\n\nint\
    \ main() {\n    test_randomized();\n\n    long long first, second;\n    std::cin\
    \ >> first >> second;\n    std::cout << first + second << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/range_query/static_range_majority.hpp\"\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <map>\n#include <optional>\n#include\
    \ <vector>\n\nnamespace {\n\nstd::optional<int> brute(\n    const std::vector<int>&\
    \ values,\n    int left,\n    int right\n) {\n    std::map<int, int> frequency;\n\
    \    for (int index = left; index < right; index++) {\n        int count = ++frequency[values[index]];\n\
    \        if (count * 2 > right - left) return values[index];\n    }\n    return\
    \ std::nullopt;\n}\n\nvoid test_randomized() {\n    m1une::ds::StaticRangeMajority<int>\
    \ empty;\n    assert(empty.empty());\n    assert(empty.size() == 0);\n\n    std::uint64_t\
    \ state = 1414213562ULL;\n    auto random = [&]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 1000; trial++) {\n        int n = int(random() % 80) + 1;\n\
    \        std::vector<int> values(n);\n        for (int& value : values) value\
    \ = int(random() % 15) - 7;\n\n        m1une::ds::StaticRangeMajority<int> structure(values);\n\
    \        assert(structure.size() == n);\n        assert(!structure.empty());\n\
    \        for (int left = 0; left < n; left++) {\n            for (int right =\
    \ left + 1; right <= n; right++) {\n                std::optional<int> expected\
    \ = brute(values, left, right);\n                assert(structure.query(left,\
    \ right) == expected);\n                assert(structure.majority(left, right)\
    \ == expected);\n            }\n        }\n    }\n}\n\n}  // namespace\n\nint\
    \ main() {\n    test_randomized();\n\n    long long first, second;\n    std::cin\
    \ >> first >> second;\n    std::cout << first + second << '\\n';\n}\n"
  dependsOn:
  - ds/range_query/static_range_majority.hpp
  isVerificationFile: true
  path: verify/ds/range_query/static_range_majority.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 01:22:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/static_range_majority.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/static_range_majority.test.cpp
- /verify/verify/ds/range_query/static_range_majority.test.cpp.html
title: verify/ds/range_query/static_range_majority.test.cpp
---
