---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/bst/rollback_ordered_multiset.hpp
    title: Rollback Ordered Multiset
  - icon: ':heavy_check_mark:'
    path: ds/bst/rollback_ordered_set.hpp
    title: Rollback Ordered Set
  - icon: ':heavy_check_mark:'
    path: ds/deque/rollback_deque.hpp
    title: Rollback Deque
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/rollback_dynamic_array.hpp
    title: Rollback Dynamic Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp
    title: Rollback Dynamic Lazy Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/rollback_dynamic_monoid_array.hpp
    title: Rollback Dynamic Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/queue/rollback_queue.hpp
    title: Rollback Queue
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
    path: ds/segtree/rollback_segtree.hpp
    title: Rollback Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_segtree_beats.hpp
    title: Rollback Segment Tree Beats
  - icon: ':heavy_check_mark:'
    path: ds/stack/rollback_stack.hpp
    title: Rollback Stack
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
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
  bundledCode: "#line 1 \"ds/detail/rollback_persistent_base.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <limits>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\ntemplate\
    \ <class Persistent>\nstruct RollbackPersistentBase : Persistent {\n   private:\n\
    \    std::vector<Persistent> _history;\n\n   protected:\n    using Persistent::Persistent;\n\
    \n    const Persistent& persistent() const {\n        return *this;\n    }\n\n\
    \    void commit(Persistent next) {\n        assert(_history.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _history.emplace_back(persistent());\n        Persistent::operator=(std::move(next));\n\
    \    }\n\n   public:\n    RollbackPersistentBase() = default;\n\n    explicit\
    \ RollbackPersistentBase(Persistent initial)\n        : Persistent(std::move(initial))\
    \ {}\n\n    int history_size() const {\n        return int(_history.size());\n\
    \    }\n\n    void reserve_history(int count) {\n        assert(0 <= count);\n\
    \        _history.reserve(count);\n    }\n\n    bool undo() {\n        if (_history.empty())\
    \ return false;\n        Persistent::operator=(std::move(_history.back()));\n\
    \        _history.pop_back();\n        return true;\n    }\n\n    int snapshot()\
    \ const {\n        return history_size();\n    }\n\n    void rollback(int state)\
    \ {\n        assert(0 <= state && state <= history_size());\n        while (history_size()\
    \ > state) undo();\n    }\n\n    void clear_history() {\n        _history.clear();\n\
    \    }\n\n    void release() {\n        _history.clear();\n        Persistent::release();\n\
    \    }\n\n    const Persistent& current_version() const {\n        return persistent();\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_DS_DETAIL_ROLLBACK_PERSISTENT_BASE_HPP\n#define M1UNE_DS_DETAIL_ROLLBACK_PERSISTENT_BASE_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\n\
    template <class Persistent>\nstruct RollbackPersistentBase : Persistent {\n  \
    \ private:\n    std::vector<Persistent> _history;\n\n   protected:\n    using\
    \ Persistent::Persistent;\n\n    const Persistent& persistent() const {\n    \
    \    return *this;\n    }\n\n    void commit(Persistent next) {\n        assert(_history.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _history.emplace_back(persistent());\n\
    \        Persistent::operator=(std::move(next));\n    }\n\n   public:\n    RollbackPersistentBase()\
    \ = default;\n\n    explicit RollbackPersistentBase(Persistent initial)\n    \
    \    : Persistent(std::move(initial)) {}\n\n    int history_size() const {\n \
    \       return int(_history.size());\n    }\n\n    void reserve_history(int count)\
    \ {\n        assert(0 <= count);\n        _history.reserve(count);\n    }\n\n\
    \    bool undo() {\n        if (_history.empty()) return false;\n        Persistent::operator=(std::move(_history.back()));\n\
    \        _history.pop_back();\n        return true;\n    }\n\n    int snapshot()\
    \ const {\n        return history_size();\n    }\n\n    void rollback(int state)\
    \ {\n        assert(0 <= state && state <= history_size());\n        while (history_size()\
    \ > state) undo();\n    }\n\n    void clear_history() {\n        _history.clear();\n\
    \    }\n\n    void release() {\n        _history.clear();\n        Persistent::release();\n\
    \    }\n\n    const Persistent& current_version() const {\n        return persistent();\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\
    \n#endif  // M1UNE_DS_DETAIL_ROLLBACK_PERSISTENT_BASE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/detail/rollback_persistent_base.hpp
  requiredBy:
  - ds/dynamic_array/rollback_dynamic_array.hpp
  - ds/dynamic_array/rollback_dynamic_monoid_array.hpp
  - ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp
  - ds/deque/rollback_deque.hpp
  - ds/segtree/rollback_lazy_segtree.hpp
  - ds/segtree/rollback_dual_segtree.hpp
  - ds/segtree/rollback_segtree_beats.hpp
  - ds/segtree/rollback_dynamic_lazy_segtree.hpp
  - ds/segtree/rollback_dynamic_dual_segtree.hpp
  - ds/segtree/rollback_dynamic_segtree.hpp
  - ds/segtree/rollback_segtree.hpp
  - ds/bst/rollback_ordered_multiset.hpp
  - ds/bst/rollback_ordered_set.hpp
  - ds/stack/rollback_stack.hpp
  - ds/queue/rollback_queue.hpp
  timestamp: '2026-08-12 04:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
  - verify/ds/rollback_counterparts.test.cpp
  - verify/ds/rollback_counterparts.test.cpp
  - verify/ds/rollback_counterparts.test.cpp
  - verify/ds/rollback_counterparts.test.cpp
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/detail/rollback_persistent_base.hpp
layout: document
redirect_from:
- /library/ds/detail/rollback_persistent_base.hpp
- /library/ds/detail/rollback_persistent_base.hpp.html
title: ds/detail/rollback_persistent_base.hpp
---
