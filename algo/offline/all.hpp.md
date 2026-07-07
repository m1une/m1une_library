---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/offline/mo.hpp
    title: Mo's Algorithm
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/offline/all.hpp\"\n\n\n\n#line 1 \"algo/offline/mo.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <numeric>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n// Offline Mo's algorithm\
    \ for half-open array ranges.\nstruct Mo {\n    struct Query {\n        int left;\n\
    \        int right;\n        int id;\n    };\n\n   private:\n    int _n;\n   \
    \ std::vector<Query> _queries;\n\n   public:\n    Mo() : _n(0) {}\n\n    explicit\
    \ Mo(int n) : _n(n) {\n        assert(0 <= n);\n    }\n\n    int size() const\
    \ {\n        return _n;\n    }\n\n    int query_count() const {\n        return\
    \ int(_queries.size());\n    }\n\n    bool empty() const {\n        return _queries.empty();\n\
    \    }\n\n    const std::vector<Query>& queries() const {\n        return _queries;\n\
    \    }\n\n    void reserve(int query_capacity) {\n        assert(0 <= query_capacity);\n\
    \        _queries.reserve(query_capacity);\n    }\n\n    void clear() {\n    \
    \    _queries.clear();\n    }\n\n    // Adds [left, right) and returns its insertion-order\
    \ ID.\n    int add_query(int left, int right) {\n        assert(0 <= left && left\
    \ <= right && right <= _n);\n        int id = query_count();\n        _queries.push_back(Query{left,\
    \ right, id});\n        return id;\n    }\n\n    // Returns query IDs in Mo order.\
    \ A non-positive block size selects one\n    // automatically.\n    std::vector<int>\
    \ order(int block_size = 0) const {\n        int query_size = query_count();\n\
    \        std::vector<int> result(query_size);\n        std::iota(result.begin(),\
    \ result.end(), 0);\n        if (query_size == 0) return result;\n\n        if\
    \ (block_size <= 0) {\n            block_size = std::max(1, int(_n / std::sqrt(static_cast<double>(query_size))));\n\
    \        }\n\n        std::sort(result.begin(), result.end(), [&](int first, int\
    \ second) {\n            const Query& a = _queries[first];\n            const\
    \ Query& b = _queries[second];\n            int first_block = a.left / block_size;\n\
    \            int second_block = b.left / block_size;\n            if (first_block\
    \ != second_block) {\n                return first_block < second_block;\n   \
    \         }\n            if (first_block & 1) return a.right > b.right;\n    \
    \        return a.right < b.right;\n        });\n        return result;\n    }\n\
    \n    // Maintains [left, right). Each movement callback receives the array index\n\
    \    // being inserted or erased. `answer(query_id)` stores or reports a result.\n\
    \    template <class AddLeft, class AddRight, class RemoveLeft, class RemoveRight,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right, Answer answer,\n             int block_size\
    \ = 0) const {\n        int left = 0;\n        int right = 0;\n        for (int\
    \ query_index : order(block_size)) {\n            const Query& query = _queries[query_index];\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    // Convenience overload for statistics whose update is\
    \ independent of\n    // which side moves.\n    template <class Add, class Remove,\
    \ class Answer>\n    void run(Add add, Remove remove, Answer answer, int block_size\
    \ = 0) const {\n        run(add, add, remove, remove, answer, block_size);\n \
    \   }\n};\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line 5 \"algo/offline/all.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_ALGO_OFFLINE_ALL_HPP

    #define M1UNE_ALGO_OFFLINE_ALL_HPP 1


    #include "mo.hpp"


    #endif  // M1UNE_ALGO_OFFLINE_ALL_HPP

    '
  dependsOn:
  - algo/offline/mo.hpp
  isVerificationFile: false
  path: algo/offline/all.hpp
  requiredBy:
  - algo/all.hpp
  timestamp: '2026-07-07 21:49:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algo/offline/all.hpp
layout: document
title: Offline Algorithms All
---

## Overview

`algo/offline/all.hpp` includes offline query-processing techniques. The public
namespace is `m1une::algo`.

## Included Headers

| Header | Contents |
| --- | --- |
| `algo/offline/mo.hpp` | Mo's algorithm for reordering static range queries. |
