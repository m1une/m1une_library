---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/prefix_substring_lcs.test.cpp
    title: verify/string/prefix_substring_lcs.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/prefix_substring_lcs.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace string {\n\n// Answers LCS-length queries between\
    \ a prefix of the first sequence and a\n// substring of the second sequence. Queries\
    \ are evaluated as one offline batch.\ntemplate <class FirstSequence, class SecondSequence>\n\
    class PrefixSubstringLcs {\n   private:\n    struct Query {\n        int first_prefix;\n\
    \        int second_left;\n        int second_right;\n    };\n\n    FirstSequence\
    \ _first;\n    SecondSequence _second;\n    std::vector<Query> _queries;\n\n \
    \  public:\n    PrefixSubstringLcs(FirstSequence first, SecondSequence second)\n\
    \        : _first(std::move(first)), _second(std::move(second)) {}\n\n    int\
    \ first_size() const {\n        return int(_first.size());\n    }\n\n    int second_size()\
    \ const {\n        return int(_second.size());\n    }\n\n    int query_count()\
    \ const {\n        return int(_queries.size());\n    }\n\n    bool empty() const\
    \ {\n        return _queries.empty();\n    }\n\n    void reserve(int query_capacity)\
    \ {\n        assert(0 <= query_capacity);\n        _queries.reserve(query_capacity);\n\
    \    }\n\n    void clear() {\n        _queries.clear();\n    }\n\n    // Adds\
    \ LCS(first[0..first_prefix), second[second_left..second_right)) and\n    // returns\
    \ its insertion-order ID.\n    int add_query(int first_prefix, int second_left,\
    \ int second_right) {\n        assert(0 <= first_prefix && first_prefix <= first_size());\n\
    \        assert(0 <= second_left && second_left <= second_right);\n        assert(second_right\
    \ <= second_size());\n        const int id = query_count();\n        _queries.push_back(Query{first_prefix,\
    \ second_left, second_right});\n        return id;\n    }\n\n    std::vector<int>\
    \ calculate() const {\n        const int first_length = first_size();\n      \
    \  const int second_length = second_size();\n        const int count = query_count();\n\
    \        std::vector<int> answers(count, 0);\n        if (count == 0 || first_length\
    \ == 0 || second_length == 0) {\n            return answers;\n        }\n\n  \
    \      std::vector<std::vector<int>> queries_by_prefix(first_length + 1);\n  \
    \      for (int id = 0; id < count; id++) {\n            const Query& query =\
    \ _queries[id];\n            if (query.first_prefix > 0 &&\n                query.second_left\
    \ < query.second_right) {\n                queries_by_prefix[query.first_prefix].push_back(id);\n\
    \            }\n        }\n\n        // seaweed[j] is the bottom endpoint of the\
    \ seaweed entering at j for\n        // the current prefix of the first sequence.\
    \ -1 denotes the left edge.\n        std::vector<int> seaweed(second_length);\n\
    \        for (int j = 0; j < second_length; j++) seaweed[j] = j;\n\n        std::vector<int>\
    \ heads(second_length + 1, -1);\n        std::vector<int> next(count, -1);\n \
    \       std::vector<int> fenwick(second_length + 1, 0);\n\n        for (int i\
    \ = 0; i < first_length; i++) {\n            int displaced = -1;\n           \
    \ for (int j = 0; j < second_length; j++) {\n                if (_first[i] ==\
    \ _second[j] || seaweed[j] < displaced) {\n                    std::swap(seaweed[j],\
    \ displaced);\n                }\n            }\n\n            const std::vector<int>&\
    \ prefix_queries = queries_by_prefix[i + 1];\n            if (prefix_queries.empty())\
    \ continue;\n\n            std::fill(heads.begin(), heads.end(), -1);\n      \
    \      for (int id : prefix_queries) {\n                const int right = _queries[id].second_right;\n\
    \                next[id] = heads[right];\n                heads[right] = id;\n\
    \            }\n            std::fill(fenwick.begin(), fenwick.end(), 0);\n\n\
    \            int inserted = 0;\n            for (int right = 1; right <= second_length;\
    \ right++) {\n                const int endpoint = seaweed[right - 1];\n     \
    \           if (endpoint >= 0) {\n                    inserted++;\n          \
    \          for (int position = endpoint + 1;\n                         position\
    \ <= second_length;\n                         position += position & -position)\
    \ {\n                        fenwick[position]++;\n                    }\n   \
    \             }\n\n                for (int id = heads[right]; id != -1; id =\
    \ next[id]) {\n                    const int left = _queries[id].second_left;\n\
    \                    int below_left = 0;\n                    for (int position\
    \ = left; position > 0;\n                         position -= position & -position)\
    \ {\n                        below_left += fenwick[position];\n              \
    \      }\n                    const int crossing = inserted - below_left;\n  \
    \                  answers[id] = (right - left) - crossing;\n                }\n\
    \            }\n        }\n        return answers;\n    }\n};\n\ntemplate <class\
    \ FirstSequence, class SecondSequence>\nPrefixSubstringLcs(FirstSequence&&, SecondSequence&&)\n\
    \    -> PrefixSubstringLcs<\n        std::decay_t<FirstSequence>,\n        std::decay_t<SecondSequence>\n\
    \    >;\n\n}  // namespace string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_PREFIX_SUBSTRING_LCS_HPP\n#define M1UNE_STRING_PREFIX_SUBSTRING_LCS_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\n//\
    \ Answers LCS-length queries between a prefix of the first sequence and a\n//\
    \ substring of the second sequence. Queries are evaluated as one offline batch.\n\
    template <class FirstSequence, class SecondSequence>\nclass PrefixSubstringLcs\
    \ {\n   private:\n    struct Query {\n        int first_prefix;\n        int second_left;\n\
    \        int second_right;\n    };\n\n    FirstSequence _first;\n    SecondSequence\
    \ _second;\n    std::vector<Query> _queries;\n\n   public:\n    PrefixSubstringLcs(FirstSequence\
    \ first, SecondSequence second)\n        : _first(std::move(first)), _second(std::move(second))\
    \ {}\n\n    int first_size() const {\n        return int(_first.size());\n   \
    \ }\n\n    int second_size() const {\n        return int(_second.size());\n  \
    \  }\n\n    int query_count() const {\n        return int(_queries.size());\n\
    \    }\n\n    bool empty() const {\n        return _queries.empty();\n    }\n\n\
    \    void reserve(int query_capacity) {\n        assert(0 <= query_capacity);\n\
    \        _queries.reserve(query_capacity);\n    }\n\n    void clear() {\n    \
    \    _queries.clear();\n    }\n\n    // Adds LCS(first[0..first_prefix), second[second_left..second_right))\
    \ and\n    // returns its insertion-order ID.\n    int add_query(int first_prefix,\
    \ int second_left, int second_right) {\n        assert(0 <= first_prefix && first_prefix\
    \ <= first_size());\n        assert(0 <= second_left && second_left <= second_right);\n\
    \        assert(second_right <= second_size());\n        const int id = query_count();\n\
    \        _queries.push_back(Query{first_prefix, second_left, second_right});\n\
    \        return id;\n    }\n\n    std::vector<int> calculate() const {\n     \
    \   const int first_length = first_size();\n        const int second_length =\
    \ second_size();\n        const int count = query_count();\n        std::vector<int>\
    \ answers(count, 0);\n        if (count == 0 || first_length == 0 || second_length\
    \ == 0) {\n            return answers;\n        }\n\n        std::vector<std::vector<int>>\
    \ queries_by_prefix(first_length + 1);\n        for (int id = 0; id < count; id++)\
    \ {\n            const Query& query = _queries[id];\n            if (query.first_prefix\
    \ > 0 &&\n                query.second_left < query.second_right) {\n        \
    \        queries_by_prefix[query.first_prefix].push_back(id);\n            }\n\
    \        }\n\n        // seaweed[j] is the bottom endpoint of the seaweed entering\
    \ at j for\n        // the current prefix of the first sequence. -1 denotes the\
    \ left edge.\n        std::vector<int> seaweed(second_length);\n        for (int\
    \ j = 0; j < second_length; j++) seaweed[j] = j;\n\n        std::vector<int> heads(second_length\
    \ + 1, -1);\n        std::vector<int> next(count, -1);\n        std::vector<int>\
    \ fenwick(second_length + 1, 0);\n\n        for (int i = 0; i < first_length;\
    \ i++) {\n            int displaced = -1;\n            for (int j = 0; j < second_length;\
    \ j++) {\n                if (_first[i] == _second[j] || seaweed[j] < displaced)\
    \ {\n                    std::swap(seaweed[j], displaced);\n                }\n\
    \            }\n\n            const std::vector<int>& prefix_queries = queries_by_prefix[i\
    \ + 1];\n            if (prefix_queries.empty()) continue;\n\n            std::fill(heads.begin(),\
    \ heads.end(), -1);\n            for (int id : prefix_queries) {\n           \
    \     const int right = _queries[id].second_right;\n                next[id] =\
    \ heads[right];\n                heads[right] = id;\n            }\n         \
    \   std::fill(fenwick.begin(), fenwick.end(), 0);\n\n            int inserted\
    \ = 0;\n            for (int right = 1; right <= second_length; right++) {\n \
    \               const int endpoint = seaweed[right - 1];\n                if (endpoint\
    \ >= 0) {\n                    inserted++;\n                    for (int position\
    \ = endpoint + 1;\n                         position <= second_length;\n     \
    \                    position += position & -position) {\n                   \
    \     fenwick[position]++;\n                    }\n                }\n\n     \
    \           for (int id = heads[right]; id != -1; id = next[id]) {\n         \
    \           const int left = _queries[id].second_left;\n                    int\
    \ below_left = 0;\n                    for (int position = left; position > 0;\n\
    \                         position -= position & -position) {\n              \
    \          below_left += fenwick[position];\n                    }\n         \
    \           const int crossing = inserted - below_left;\n                    answers[id]\
    \ = (right - left) - crossing;\n                }\n            }\n        }\n\
    \        return answers;\n    }\n};\n\ntemplate <class FirstSequence, class SecondSequence>\n\
    PrefixSubstringLcs(FirstSequence&&, SecondSequence&&)\n    -> PrefixSubstringLcs<\n\
    \        std::decay_t<FirstSequence>,\n        std::decay_t<SecondSequence>\n\
    \    >;\n\n}  // namespace string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_PREFIX_SUBSTRING_LCS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/prefix_substring_lcs.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-07-16 21:38:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/prefix_substring_lcs.test.cpp
documentation_of: string/prefix_substring_lcs.hpp
layout: document
title: Prefix-Substring LCS
---

## Overview

`PrefixSubstringLcs` records queries for the length of a longest common
subsequence of `first[0..a)` and `second[b..c)`, then evaluates the complete
batch efficiently. Answers are returned in query insertion order.

The structure uses a seaweed permutation for semi-local LCS and processes the
queries offline. It stores copies of both input sequences. Each sequence must
provide `size()` and `operator[]`, and `first[i] == second[j]` must be valid.

Let `N = first.size()`, `M = second.size()`, `Q` be the number of queries, and
`A` be the number of distinct positive prefix lengths that have a nonempty
substring query.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PrefixSubstringLcs(FirstSequence first, SecondSequence second)` | Copies or moves the two sequences. | `O(N + M)` |
| `int first_size() const` | Returns `N`. | `O(1)` |
| `int second_size() const` | Returns `M`. | `O(1)` |
| `int query_count() const` | Returns the number of recorded queries. | `O(1)` |
| `bool empty() const` | Returns whether no queries are recorded. | `O(1)` |
| `void reserve(int query_capacity)` | Reserves storage for queries. | `O(Q)` worst case |
| `void clear()` | Removes all queries while preserving the two sequences. | `O(Q)` |
| `int add_query(int a, int b, int c)` | Records `LCS(first[0..a), second[b..c))` and returns its insertion-order ID. | Amortized `O(1)` |
| `vector<int> calculate() const` | Returns all recorded answers in insertion order. | `O(NM + (AM + Q) log(M + 1))` |

`calculate()` uses `O(N + M + Q)` auxiliary memory. Its worst-case time is
`O((NM + Q) log(M + 1))`. It does not mutate the object, so it may be called more
than once. An empty prefix or empty substring has answer zero.

Indices are zero-based and substring ranges are half-open. A query must satisfy
`0 <= a <= N` and `0 <= b <= c <= M`.

## Example

```cpp
#include "string/prefix_substring_lcs.hpp"

#include <iostream>
#include <string>

int main() {
    std::string first = "abac";
    std::string second = "cababa";
    m1une::string::PrefixSubstringLcs solver(first, second);

    solver.add_query(3, 1, 5);
    solver.add_query(4, 0, 3);
    for (int answer : solver.calculate()) {
        std::cout << answer << "\n";
    }
}
```
