---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp
    title: Rollback Dynamic Lazy Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_dual_segtree.hpp
    title: Rollback Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_dynamic_dual_segtree.hpp
    title: Rollback Dynamic Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_dynamic_lazy_segtree.hpp
    title: Rollback Dynamic Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_dynamic_segtree.hpp
    title: Rollback Dynamic Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_lazy_segtree.hpp
    title: Rollback Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_segtree_beats.hpp
    title: Rollback Segment Tree Beats
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/detail/rollback_journal.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstddef>\n#include <cstdint>\n#include <limits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\nnamespace\
    \ detail {\n\ntemplate <class Node>\nstruct RollbackJournal {\n    struct Change\
    \ {\n        int index;\n        Node value;\n    };\n\n    struct Checkpoint\
    \ {\n        std::size_t change_size;\n        std::size_t node_size;\n      \
    \  std::uint64_t epoch;\n    };\n\n    std::vector<Node> nodes;\n    std::vector<Change>\
    \ changes;\n    std::vector<Checkpoint> checkpoints;\n    std::vector<std::uint64_t>\
    \ saved_epoch;\n    std::uint64_t next_epoch = 1;\n\n    std::uint64_t new_epoch()\
    \ {\n        if (next_epoch == 0) {\n            std::fill(saved_epoch.begin(),\
    \ saved_epoch.end(), 0);\n            next_epoch = 1;\n        }\n        return\
    \ next_epoch++;\n    }\n\n    int size() const { return int(nodes.size()); }\n\
    \n    Node& operator[](int index) { return nodes[index]; }\n    const Node& operator[](int\
    \ index) const { return nodes[index]; }\n\n    template <class... Args>\n    int\
    \ emplace(Args&&... args) {\n        assert(nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        int index = int(nodes.size());\n        nodes.emplace_back(std::forward<Args>(args)...);\n\
    \        saved_epoch.push_back(0);\n        return index;\n    }\n\n    int snapshot()\
    \ {\n        assert(checkpoints.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        checkpoints.push_back(Checkpoint{changes.size(), nodes.size(), new_epoch()});\n\
    \        return int(checkpoints.size());\n    }\n\n    void touch(int index) {\n\
    \        assert(0 <= index && index < size());\n        if (checkpoints.empty())\
    \ return;\n        const Checkpoint& checkpoint = checkpoints.back();\n      \
    \  if (std::size_t(index) >= checkpoint.node_size) return;\n        if (saved_epoch[index]\
    \ == checkpoint.epoch) return;\n        saved_epoch[index] = checkpoint.epoch;\n\
    \        changes.push_back(Change{index, nodes[index]});\n    }\n\n    int snapshot_count()\
    \ const { return int(checkpoints.size()); }\n\n    void reserve_snapshots(int\
    \ count) {\n        assert(0 <= count);\n        checkpoints.reserve(count);\n\
    \    }\n\n    void reserve_changes(std::size_t count) { changes.reserve(count);\
    \ }\n\n    void rollback(int state) {\n        assert(1 <= state && state <= snapshot_count());\n\
    \        Checkpoint checkpoint = checkpoints[state - 1];\n        while (changes.size()\
    \ > checkpoint.change_size) {\n            Change change = std::move(changes.back());\n\
    \            changes.pop_back();\n            nodes[change.index] = std::move(change.value);\n\
    \        }\n        nodes.erase(nodes.begin() + checkpoint.node_size, nodes.end());\n\
    \        saved_epoch.resize(checkpoint.node_size);\n        checkpoints.resize(state);\n\
    \        checkpoints.back().change_size = changes.size();\n        checkpoints.back().node_size\
    \ = nodes.size();\n        checkpoints.back().epoch = new_epoch();\n    }\n\n\
    \    void clear_history() {\n        changes.clear();\n        checkpoints.clear();\n\
    \        std::fill(saved_epoch.begin(), saved_epoch.end(), 0);\n    }\n\n    void\
    \ clear() {\n        nodes.clear();\n        changes.clear();\n        checkpoints.clear();\n\
    \        saved_epoch.clear();\n        next_epoch = 1;\n    }\n};\n\n}  // namespace\
    \ detail\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_DETAIL_ROLLBACK_JOURNAL_HPP\n#define M1UNE_DS_DETAIL_ROLLBACK_JOURNAL_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <limits>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\nnamespace detail {\n\ntemplate <class Node>\nstruct\
    \ RollbackJournal {\n    struct Change {\n        int index;\n        Node value;\n\
    \    };\n\n    struct Checkpoint {\n        std::size_t change_size;\n       \
    \ std::size_t node_size;\n        std::uint64_t epoch;\n    };\n\n    std::vector<Node>\
    \ nodes;\n    std::vector<Change> changes;\n    std::vector<Checkpoint> checkpoints;\n\
    \    std::vector<std::uint64_t> saved_epoch;\n    std::uint64_t next_epoch = 1;\n\
    \n    std::uint64_t new_epoch() {\n        if (next_epoch == 0) {\n          \
    \  std::fill(saved_epoch.begin(), saved_epoch.end(), 0);\n            next_epoch\
    \ = 1;\n        }\n        return next_epoch++;\n    }\n\n    int size() const\
    \ { return int(nodes.size()); }\n\n    Node& operator[](int index) { return nodes[index];\
    \ }\n    const Node& operator[](int index) const { return nodes[index]; }\n\n\
    \    template <class... Args>\n    int emplace(Args&&... args) {\n        assert(nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        int index = int(nodes.size());\n\
    \        nodes.emplace_back(std::forward<Args>(args)...);\n        saved_epoch.push_back(0);\n\
    \        return index;\n    }\n\n    int snapshot() {\n        assert(checkpoints.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        checkpoints.push_back(Checkpoint{changes.size(),\
    \ nodes.size(), new_epoch()});\n        return int(checkpoints.size());\n    }\n\
    \n    void touch(int index) {\n        assert(0 <= index && index < size());\n\
    \        if (checkpoints.empty()) return;\n        const Checkpoint& checkpoint\
    \ = checkpoints.back();\n        if (std::size_t(index) >= checkpoint.node_size)\
    \ return;\n        if (saved_epoch[index] == checkpoint.epoch) return;\n     \
    \   saved_epoch[index] = checkpoint.epoch;\n        changes.push_back(Change{index,\
    \ nodes[index]});\n    }\n\n    int snapshot_count() const { return int(checkpoints.size());\
    \ }\n\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n\
    \        checkpoints.reserve(count);\n    }\n\n    void reserve_changes(std::size_t\
    \ count) { changes.reserve(count); }\n\n    void rollback(int state) {\n     \
    \   assert(1 <= state && state <= snapshot_count());\n        Checkpoint checkpoint\
    \ = checkpoints[state - 1];\n        while (changes.size() > checkpoint.change_size)\
    \ {\n            Change change = std::move(changes.back());\n            changes.pop_back();\n\
    \            nodes[change.index] = std::move(change.value);\n        }\n     \
    \   nodes.erase(nodes.begin() + checkpoint.node_size, nodes.end());\n        saved_epoch.resize(checkpoint.node_size);\n\
    \        checkpoints.resize(state);\n        checkpoints.back().change_size =\
    \ changes.size();\n        checkpoints.back().node_size = nodes.size();\n    \
    \    checkpoints.back().epoch = new_epoch();\n    }\n\n    void clear_history()\
    \ {\n        changes.clear();\n        checkpoints.clear();\n        std::fill(saved_epoch.begin(),\
    \ saved_epoch.end(), 0);\n    }\n\n    void clear() {\n        nodes.clear();\n\
    \        changes.clear();\n        checkpoints.clear();\n        saved_epoch.clear();\n\
    \        next_epoch = 1;\n    }\n};\n\n}  // namespace detail\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_DETAIL_ROLLBACK_JOURNAL_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/detail/rollback_journal.hpp
  requiredBy:
  - ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp
  - ds/segtree/rollback_lazy_segtree.hpp
  - ds/segtree/rollback_dynamic_lazy_segtree.hpp
  - ds/segtree/rollback_dynamic_segtree.hpp
  - ds/segtree/rollback_dual_segtree.hpp
  - ds/segtree/rollback_dynamic_dual_segtree.hpp
  - ds/segtree/rollback_segtree_beats.hpp
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/detail/rollback_journal.hpp
layout: document
redirect_from:
- /library/ds/detail/rollback_journal.hpp
- /library/ds/detail/rollback_journal.hpp.html
title: ds/detail/rollback_journal.hpp
---
