---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/static_range_majority.test.cpp
    title: verify/ds/range_query/static_range_majority.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/static_range_majority.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <optional>\n#include <vector>\n\n\
    namespace m1une {\nnamespace ds {\n\n// Static strict-majority queries in O(log\
    \ N) time.\ntemplate <class T>\nstruct StaticRangeMajority {\n    using result_type\
    \ = std::optional<T>;\n\n   private:\n    struct Vote {\n        int candidate\
    \ = -1;\n        int balance = 0;\n    };\n\n    int _n;\n    int _tree_size;\n\
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
    }  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MAJORITY_HPP\n#define M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MAJORITY_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include\
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
    }  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MAJORITY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/static_range_majority.hpp
  requiredBy: []
  timestamp: '2026-07-15 01:22:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/static_range_majority.test.cpp
documentation_of: ds/range_query/static_range_majority.hpp
layout: document
title: Static Range Majority
---

## Overview

`StaticRangeMajority<T>` preprocesses an immutable array and finds the strict
majority of any nonempty half-open range `[left, right)`. A strict majority is a
value occurring more than `(right - left) / 2` times. It is necessarily unique.
The query returns `std::nullopt` when no strict majority exists.

Each segment-tree node stores the result of Boyer--Moore cancellation. A strict
majority survives every cancellation of two unequal values, so merging the
nodes covering a query produces the only possible candidate. Sorted occurrence
positions then verify the candidate's exact frequency.

The algorithm is deterministic.

## Requirements and Behavior

`T` must be copyable and support `operator<` and equality comparison
consistently. Construction does not modify the input vector.

Queries use zero-based indices and require
`0 <= left < right <= size()`. They do not mutate the structure, and both query
methods are `const`.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `StaticRangeMajority()` | Constructs an empty structure. | $O(1)$ |
| Constructor | `explicit StaticRangeMajority(const std::vector<T>& values)` | Preprocesses `values`. | $O(N\log N)$ time and $O(N)$ memory |
| `size` | `int size() const` | Returns the array length. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the array is empty. | $O(1)$ |
| `query` | `std::optional<T> query(int left, int right) const` | Returns the strict majority of `[left, right)`, or `std::nullopt`. | $O(\log N)$ |
| `majority` | `std::optional<T> majority(int left, int right) const` | Alias of `query`. | $O(\log N)$ |

`result_type` is an alias of `std::optional<T>`.

## Example

```cpp
#include "ds/range_query/static_range_majority.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {2, 1, 2, 2, 3, 3};
    m1une::ds::StaticRangeMajority<int> majority(values);

    auto first = majority.query(0, 4);
    if (first) std::cout << *first << '\n';  // 2

    auto second = majority.query(1, 6);
    std::cout << second.has_value() << '\n'; // 0
}
```
