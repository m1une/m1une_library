---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/offline/cdq_divide_and_conquer.hpp
    title: CDQ Divide And Conquer
  - icon: ':heavy_check_mark:'
    path: algo/offline/mo.hpp
    title: Mo's Algorithm
  - icon: ':heavy_check_mark:'
    path: algo/offline/mo_with_updates.hpp
    title: Mo's Algorithm with Updates
  - icon: ':heavy_check_mark:'
    path: algo/offline/parallel_binary_search.hpp
    title: Parallel Binary Search
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
  bundledCode: "#line 1 \"algo/offline/all.hpp\"\n\n\n\n#line 1 \"algo/offline/cdq_divide_and_conquer.hpp\"\
    \n\n\n\n#include <cassert>\n\nnamespace m1une {\nnamespace algo {\n\ntemplate\
    \ <class SolveCross>\nvoid cdq_divide_and_conquer(int left, int right, SolveCross\
    \ solve_cross) {\n    assert(left <= right);\n\n    auto dfs = [&](auto& self,\
    \ int l, int r) -> void {\n        if (r - l <= 1) return;\n        const int\
    \ middle = l + (r - l) / 2;\n        self(self, l, middle);\n        self(self,\
    \ middle, r);\n        solve_cross(l, middle, r);\n    };\n    dfs(dfs, left,\
    \ right);\n}\n\ntemplate <class SolveCross>\nvoid cdq_divide_and_conquer(int n,\
    \ SolveCross solve_cross) {\n    assert(0 <= n);\n    cdq_divide_and_conquer(0,\
    \ n, solve_cross);\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line\
    \ 1 \"algo/offline/mo.hpp\"\n\n\n\n#include <algorithm>\n#line 6 \"algo/offline/mo.hpp\"\
    \n#include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace m1une {\n\
    namespace algo {\n\n// Offline Mo's algorithm for half-open array ranges.\nstruct\
    \ Mo {\n    struct Query {\n        int left;\n        int right;\n        int\
    \ id;\n    };\n\n   private:\n    int _n;\n    std::vector<Query> _queries;\n\n\
    \   public:\n    Mo() : _n(0) {}\n\n    explicit Mo(int n) : _n(n) {\n       \
    \ assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\
    \n    int query_count() const {\n        return int(_queries.size());\n    }\n\
    \n    bool empty() const {\n        return _queries.empty();\n    }\n\n    const\
    \ std::vector<Query>& queries() const {\n        return _queries;\n    }\n\n \
    \   void reserve(int query_capacity) {\n        assert(0 <= query_capacity);\n\
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
    \   }\n};\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line 1 \"algo/offline/mo_with_updates.hpp\"\
    \n\n\n\n#line 7 \"algo/offline/mo_with_updates.hpp\"\n#include <cstddef>\n#include\
    \ <limits>\n#line 10 \"algo/offline/mo_with_updates.hpp\"\n\nnamespace m1une {\n\
    namespace algo {\n\n// Offline Mo ordering in (left, right, update time). Array\
    \ values and the\n// before/after values of each point update are owned by the\
    \ caller.\nstruct MoWithUpdates {\n    struct Query {\n        int left;\n   \
    \     int right;\n        int time;\n        int id;\n    };\n\n   private:\n\
    \    int _n;\n    int _update_count = 0;\n    std::vector<Query> _queries;\n\n\
    \   public:\n    MoWithUpdates() : _n(0) {}\n\n    explicit MoWithUpdates(int\
    \ n) : _n(n) { assert(0 <= n); }\n\n    int size() const { return _n; }\n\n  \
    \  int query_count() const { return int(_queries.size()); }\n\n    int update_count()\
    \ const { return _update_count; }\n\n    bool empty() const { return _queries.empty();\
    \ }\n\n    const std::vector<Query>& queries() const { return _queries; }\n\n\
    \    void reserve(int query_capacity) {\n        assert(0 <= query_capacity);\n\
    \        _queries.reserve(query_capacity);\n    }\n\n    void clear() {\n    \
    \    _queries.clear();\n        _update_count = 0;\n    }\n\n    // Registers\
    \ one update and returns its zero-based ID. Time t means that\n    // updates\
    \ [0, t) have been applied, including any no-op assignments.\n    int add_update()\
    \ {\n        assert(_update_count < std::numeric_limits<int>::max());\n      \
    \  return _update_count++;\n    }\n\n    int add_query(int left, int right) {\
    \ return add_query(left, right, _update_count); }\n\n    // Historical times are\
    \ allowed, but the updates must already be registered.\n    int add_query(int\
    \ left, int right, int time) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        assert(0 <= time && time <= _update_count);\n        assert(_queries.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        const int id = query_count();\n\
    \        _queries.push_back(Query{left, right, time, id});\n        return id;\n\
    \    }\n\n    std::vector<int> order(int block_size = 0) const {\n        const\
    \ int q = query_count();\n        if (q == 0) return {};\n        auto times =\
    \ std::minmax_element(_queries.begin(), _queries.end(),\n            [](const\
    \ Query& a, const Query& b) { return a.time < b.time; });\n        const int time_span\
    \ = times.second->time - times.first->time;\n        if (block_size <= 0) {\n\
    \            const double n = _n;\n            const double static_size = n /\
    \ std::sqrt(double(q));\n            const double dynamic_size = std::cbrt(n *\
    \ n * double(time_span) / double(q));\n            const double estimate = std::max(static_size,\
    \ dynamic_size);\n            block_size = int(std::clamp(estimate, 1.0, double(std::max(1,\
    \ _n))));\n        }\n\n        struct Entry {\n            int left_block;\n\
    \            int right_block;\n            int time;\n            int id;\n  \
    \      };\n        std::vector<Entry> entries;\n        entries.reserve(q);\n\
    \        for (const Query& query : _queries) {\n            entries.push_back(Entry{\n\
    \                query.left / block_size, query.right / block_size, query.time,\
    \ query.id});\n        }\n        std::sort(entries.begin(), entries.end(), [&](const\
    \ Entry& a, const Entry& b) {\n            if (a.left_block != b.left_block) return\
    \ a.left_block < b.left_block;\n            const bool reverse_right = (a.left_block\
    \ & 1) != 0;\n            if (time_span != 0) {\n                if (a.right_block\
    \ != b.right_block) {\n                    return reverse_right ? a.right_block\
    \ > b.right_block : a.right_block < b.right_block;\n                }\n      \
    \          if (a.time != b.time) {\n                    return ((a.left_block\
    \ ^ a.right_block) & 1) ? a.time > b.time : a.time < b.time;\n               \
    \ }\n            }\n            const int a_right = _queries[a.id].right;\n  \
    \          const int b_right = _queries[b.id].right;\n            if (a_right\
    \ != b_right) return reverse_right ? a_right > b_right : a_right < b_right;\n\
    \            return a.id < b.id;\n        });\n        std::vector<int> result;\n\
    \        result.reserve(q);\n        for (const Entry& entry : entries) result.push_back(entry.id);\n\
    \        return result;\n    }\n\n    // apply(id, left, right) moves time id\
    \ -> id + 1; undo(id, left, right)\n    // reverses that update. Both must update\
    \ the array even outside the active\n    // range, and must repair the maintained\
    \ answer when necessary inside it.\n    template <class AddLeft, class AddRight,\
    \ class RemoveLeft, class RemoveRight,\n              class Apply, class Undo,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right,\n             Apply apply, Undo undo,\
    \ Answer answer, int block_size = 0) const {\n        int left = 0;\n        int\
    \ right = 0;\n        int time = 0;\n        for (int query_index : order(block_size))\
    \ {\n            const Query& query = _queries[query_index];\n            while\
    \ (time < query.time) {\n                apply(time, left, right);\n         \
    \       ++time;\n            }\n            while (query.time < time) {\n    \
    \            --time;\n                undo(time, left, right);\n            }\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    template <class Add, class Remove, class Apply, class\
    \ Undo, class Answer>\n    void run(Add add, Remove remove, Apply apply, Undo\
    \ undo, Answer answer,\n             int block_size = 0) const {\n        run(add,\
    \ add, remove, remove, apply, undo, answer, block_size);\n    }\n};\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 1 \"algo/offline/parallel_binary_search.hpp\"\
    \n\n\n\n#line 6 \"algo/offline/parallel_binary_search.hpp\"\n\nnamespace m1une\
    \ {\nnamespace algo {\n\ntemplate <class Apply, class Check, class Reset>\nstd::vector<int>\
    \ parallel_binary_search(\n    int query_count,\n    int event_count,\n    Apply\
    \ apply,\n    Check check,\n    Reset reset\n) {\n    assert(0 <= query_count);\n\
    \    assert(0 <= event_count);\n\n    std::vector<int> low(query_count, -1);\n\
    \    std::vector<int> high(query_count, event_count + 1);\n    std::vector<std::vector<int>>\
    \ bucket(event_count + 1);\n\n    while (true) {\n        bool active = false;\n\
    \        for (auto& queries : bucket) queries.clear();\n\n        for (int query\
    \ = 0; query < query_count; ++query) {\n            if (high[query] - low[query]\
    \ <= 1) continue;\n            const int middle = low[query] + (high[query] -\
    \ low[query]) / 2;\n            bucket[middle].push_back(query);\n           \
    \ active = true;\n        }\n        if (!active) break;\n\n        reset();\n\
    \        int applied = 0;\n        for (int middle = 0; middle <= event_count;\
    \ ++middle) {\n            while (applied < middle) {\n                apply(applied);\n\
    \                ++applied;\n            }\n            for (int query : bucket[middle])\
    \ {\n                if (check(query)) {\n                    high[query] = middle;\n\
    \                } else {\n                    low[query] = middle;\n        \
    \        }\n            }\n        }\n    }\n\n    return high;\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 8 \"algo/offline/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_OFFLINE_ALL_HPP

    #define M1UNE_ALGO_OFFLINE_ALL_HPP 1


    #include "cdq_divide_and_conquer.hpp"

    #include "mo.hpp"

    #include "mo_with_updates.hpp"

    #include "parallel_binary_search.hpp"


    #endif  // M1UNE_ALGO_OFFLINE_ALL_HPP

    '
  dependsOn:
  - algo/offline/cdq_divide_and_conquer.hpp
  - algo/offline/mo.hpp
  - algo/offline/mo_with_updates.hpp
  - algo/offline/parallel_binary_search.hpp
  isVerificationFile: false
  path: algo/offline/all.hpp
  requiredBy:
  - algo/all.hpp
  timestamp: '2026-11-17 04:04:19+09:00'
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
| `algo/offline/mo_with_updates.hpp` | Mo's algorithm for range queries interleaved with point updates, including historical times and apply/undo callbacks. |
| `algo/offline/parallel_binary_search.hpp` | Parallel binary search for batched monotone prefix decisions. |
| `algo/offline/cdq_divide_and_conquer.hpp` | Generic CDQ divide-and-conquer recursion helper. |
