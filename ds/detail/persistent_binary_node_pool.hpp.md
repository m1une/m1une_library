---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_multiset.hpp
    title: Persistent Ordered Multiset
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_set.hpp
    title: Persistent Ordered Set
  - icon: ':heavy_check_mark:'
    path: ds/dsu/persistent_dsu.hpp
    title: Persistent DSU
  - icon: ':heavy_check_mark:'
    path: ds/dsu/persistent_potentialized_dsu.hpp
    title: Persistent Potentialized DSU
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_array.hpp
    title: Persistent Dynamic Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
    title: Persistent Dynamic Lazy Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_monoid_array.hpp
    title: Persistent Dynamic Monoid Array
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/bst/persistent_ordered_multiset.test.cpp
    title: verify/ds/bst/persistent_ordered_multiset.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/bst/persistent_ordered_set.test.cpp
    title: verify/ds/bst/persistent_ordered_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/persistent_dsu.test.cpp
    title: verify/ds/dsu/persistent_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/persistent_dsu_library_checker.test.cpp
    title: verify/ds/dsu/persistent_dsu_library_checker.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
    title: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
    title: verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp
    title: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
    title: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp
    title: verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_release.test.cpp
    title: verify/ds/persistent_release.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_release.test.cpp
    title: verify/ds/persistent_release.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_release.test.cpp
    title: verify/ds/persistent_release.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/detail/persistent_binary_node_pool.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <deque>\n#include <limits>\n#include\
    \ <optional>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ ds {\nnamespace detail {\n\n// Node must have integer `l` and `r` members. New\
    \ nodes initially have no\n// owner; discard_unreferenced() removes temporary\
    \ path-copy nodes after the\n// result roots have been retained.\ntemplate <class\
    \ Node, int null_node = -1>\nstruct PersistentBinaryNodePool {\n   private:\n\
    \    std::deque<std::optional<Node>> _nodes;\n    std::vector<int> _references;\n\
    \    std::vector<int> _next_free;\n    std::vector<int> _unowned;\n    int _first_free\
    \ = -1;\n    std::size_t _live_nodes = 0;\n\n    void release_zero(int node) {\n\
    \        assert(node != null_node && _nodes[node].has_value());\n        int left\
    \ = (*_nodes[node]).l;\n        int right = (*_nodes[node]).r;\n        _nodes[node].reset();\n\
    \        _next_free[node] = _first_free;\n        _first_free = node;\n      \
    \  --_live_nodes;\n        if (left != null_node && --_references[left] == 0)\
    \ release_zero(left);\n        if (right != null_node && --_references[right]\
    \ == 0) release_zero(right);\n    }\n\n   public:\n    PersistentBinaryNodePool()\
    \ {\n        if constexpr (null_node == 0) {\n            _nodes.emplace_back();\n\
    \            _references.push_back(0);\n            _next_free.push_back(-1);\n\
    \        }\n    }\n\n    Node& operator[](int node) {\n        assert(node !=\
    \ null_node && _nodes[node].has_value());\n        return *_nodes[node];\n   \
    \ }\n\n    const Node& operator[](int node) const {\n        assert(node != null_node\
    \ && _nodes[node].has_value());\n        return *_nodes[node];\n    }\n\n    template\
    \ <class... Args>\n    int emplace(Args&&... args) {\n        int result;\n  \
    \      if (_first_free == -1) {\n            assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \            result = int(_nodes.size());\n            _nodes.emplace_back(std::in_place,\
    \ std::forward<Args>(args)...);\n            _references.push_back(0);\n     \
    \       _next_free.push_back(-1);\n        } else {\n            result = _first_free;\n\
    \            _first_free = _next_free[result];\n            _nodes[result].emplace(std::forward<Args>(args)...);\n\
    \            _references[result] = 0;\n        }\n        retain((*_nodes[result]).l);\n\
    \        retain((*_nodes[result]).r);\n        _unowned.push_back(result);\n \
    \       ++_live_nodes;\n        return result;\n    }\n\n    void retain(int node)\
    \ {\n        if (node != null_node) {\n            assert(_nodes[node].has_value());\n\
    \            ++_references[node];\n        }\n    }\n\n    void release(int node)\
    \ {\n        if (node == null_node) return;\n        assert(_nodes[node].has_value()\
    \ && _references[node] > 0);\n        if (--_references[node] == 0) release_zero(node);\n\
    \    }\n\n    void discard_unreferenced() {\n        while (!_unowned.empty())\
    \ {\n            int node = _unowned.back();\n            _unowned.pop_back();\n\
    \            if (_nodes[node].has_value() && _references[node] == 0) release_zero(node);\n\
    \        }\n    }\n\n    void reserve(std::size_t) {}\n\n    int next_index()\
    \ const { return _first_free == -1 ? int(_nodes.size()) : _first_free; }\n\n \
    \   std::size_t size() const { return _live_nodes; }\n};\n\n}  // namespace detail\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_DETAIL_PERSISTENT_BINARY_NODE_POOL_HPP\n#define M1UNE_DS_DETAIL_PERSISTENT_BINARY_NODE_POOL_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <deque>\n#include <limits>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\nnamespace detail {\n\n// Node must have integer `l` and `r`\
    \ members. New nodes initially have no\n// owner; discard_unreferenced() removes\
    \ temporary path-copy nodes after the\n// result roots have been retained.\ntemplate\
    \ <class Node, int null_node = -1>\nstruct PersistentBinaryNodePool {\n   private:\n\
    \    std::deque<std::optional<Node>> _nodes;\n    std::vector<int> _references;\n\
    \    std::vector<int> _next_free;\n    std::vector<int> _unowned;\n    int _first_free\
    \ = -1;\n    std::size_t _live_nodes = 0;\n\n    void release_zero(int node) {\n\
    \        assert(node != null_node && _nodes[node].has_value());\n        int left\
    \ = (*_nodes[node]).l;\n        int right = (*_nodes[node]).r;\n        _nodes[node].reset();\n\
    \        _next_free[node] = _first_free;\n        _first_free = node;\n      \
    \  --_live_nodes;\n        if (left != null_node && --_references[left] == 0)\
    \ release_zero(left);\n        if (right != null_node && --_references[right]\
    \ == 0) release_zero(right);\n    }\n\n   public:\n    PersistentBinaryNodePool()\
    \ {\n        if constexpr (null_node == 0) {\n            _nodes.emplace_back();\n\
    \            _references.push_back(0);\n            _next_free.push_back(-1);\n\
    \        }\n    }\n\n    Node& operator[](int node) {\n        assert(node !=\
    \ null_node && _nodes[node].has_value());\n        return *_nodes[node];\n   \
    \ }\n\n    const Node& operator[](int node) const {\n        assert(node != null_node\
    \ && _nodes[node].has_value());\n        return *_nodes[node];\n    }\n\n    template\
    \ <class... Args>\n    int emplace(Args&&... args) {\n        int result;\n  \
    \      if (_first_free == -1) {\n            assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \            result = int(_nodes.size());\n            _nodes.emplace_back(std::in_place,\
    \ std::forward<Args>(args)...);\n            _references.push_back(0);\n     \
    \       _next_free.push_back(-1);\n        } else {\n            result = _first_free;\n\
    \            _first_free = _next_free[result];\n            _nodes[result].emplace(std::forward<Args>(args)...);\n\
    \            _references[result] = 0;\n        }\n        retain((*_nodes[result]).l);\n\
    \        retain((*_nodes[result]).r);\n        _unowned.push_back(result);\n \
    \       ++_live_nodes;\n        return result;\n    }\n\n    void retain(int node)\
    \ {\n        if (node != null_node) {\n            assert(_nodes[node].has_value());\n\
    \            ++_references[node];\n        }\n    }\n\n    void release(int node)\
    \ {\n        if (node == null_node) return;\n        assert(_nodes[node].has_value()\
    \ && _references[node] > 0);\n        if (--_references[node] == 0) release_zero(node);\n\
    \    }\n\n    void discard_unreferenced() {\n        while (!_unowned.empty())\
    \ {\n            int node = _unowned.back();\n            _unowned.pop_back();\n\
    \            if (_nodes[node].has_value() && _references[node] == 0) release_zero(node);\n\
    \        }\n    }\n\n    void reserve(std::size_t) {}\n\n    int next_index()\
    \ const { return _first_free == -1 ? int(_nodes.size()) : _first_free; }\n\n \
    \   std::size_t size() const { return _live_nodes; }\n};\n\n}  // namespace detail\n\
    }  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_DETAIL_PERSISTENT_BINARY_NODE_POOL_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/detail/persistent_binary_node_pool.hpp
  requiredBy:
  - ds/dynamic_array/persistent_dynamic_monoid_array.hpp
  - ds/dynamic_array/persistent_dynamic_array.hpp
  - ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
  - ds/dsu/persistent_dsu.hpp
  - ds/dsu/persistent_potentialized_dsu.hpp
  - ds/bst/persistent_ordered_set.hpp
  - ds/bst/persistent_ordered_multiset.hpp
  timestamp: '2026-08-11 13:59:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp
  - verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
  - verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
  - verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp
  - verify/ds/dsu/persistent_dsu.test.cpp
  - verify/ds/dsu/persistent_potentialized_dsu.test.cpp
  - verify/ds/dsu/persistent_dsu_library_checker.test.cpp
  - verify/ds/persistent_release.test.cpp
  - verify/ds/persistent_release.test.cpp
  - verify/ds/persistent_release.test.cpp
  - verify/ds/bst/persistent_ordered_multiset.test.cpp
  - verify/ds/bst/persistent_ordered_set.test.cpp
documentation_of: ds/detail/persistent_binary_node_pool.hpp
layout: document
redirect_from:
- /library/ds/detail/persistent_binary_node_pool.hpp
- /library/ds/detail/persistent_binary_node_pool.hpp.html
title: ds/detail/persistent_binary_node_pool.hpp
---
