---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dual_segtree.hpp
    title: Persistent Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dynamic_dual_segtree.hpp
    title: Persistent Dynamic Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dynamic_lazy_segtree.hpp
    title: Persistent Dynamic Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_dynamic_segtree.hpp
    title: Persistent Dynamic Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_lazy_segtree.hpp
    title: Persistent Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_segtree.hpp
    title: Persistent Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_segtree_beats.hpp
    title: ds/segtree/persistent_segtree_beats.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_cow.test.cpp
    title: verify/ds/persistent_cow.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dual_segtree.test.cpp
    title: verify/ds/segtree/persistent_dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dynamic_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_lazy_segtree.test.cpp
    title: verify/ds/segtree/persistent_lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_segtree.test.cpp
    title: verify/ds/segtree/persistent_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_segtree_beats.test.cpp
    title: verify/ds/segtree/persistent_segtree_beats.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/persistent_node_pool.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\n// Node must have integer\
    \ `left`, `right`, and `references` members.\ntemplate <class Node>\nstruct PersistentNodePool\
    \ {\n    std::vector<Node> nodes;\n    int first_free = 0;\n    std::size_t live_nodes\
    \ = 0;\n\n   private:\n    void release_zero(int node) {\n        int left = nodes[node].left;\n\
    \        int right = nodes[node].right;\n        nodes[node] = Node();\n     \
    \   nodes[node].left = first_free;\n        first_free = node;\n        --live_nodes;\n\
    \        if (left && --nodes[left].references == 0) release_zero(left);\n    \
    \    if (right && --nodes[right].references == 0) release_zero(right);\n    }\n\
    \n   public:\n    PersistentNodePool() { nodes.emplace_back(); }\n\n    void reserve(std::size_t\
    \ capacity) { nodes.reserve(capacity + 1); }\n\n    Node& operator[](int node)\
    \ { return nodes[node]; }\n\n    const Node& operator[](int node) const { return\
    \ nodes[node]; }\n\n    void retain(int node) {\n        if (node) ++nodes[node].references;\n\
    \    }\n\n    void release(int node) {\n        if (!node) return;\n        assert(nodes[node].references\
    \ > 0);\n        if (--nodes[node].references == 0) release_zero(node);\n    }\n\
    \n    template <class... Args>\n    int emplace(Args&&... args) {\n        int\
    \ result;\n        if (!first_free) {\n            assert(nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \            nodes.emplace_back(std::forward<Args>(args)...);\n            result\
    \ = int(nodes.size()) - 1;\n        } else {\n            result = first_free;\n\
    \            first_free = nodes[result].left;\n            nodes[result] = Node(std::forward<Args>(args)...);\n\
    \        }\n        Node& node = nodes[result];\n        node.references = 0;\n\
    \        retain(node.left);\n        retain(node.right);\n        ++live_nodes;\n\
    \        return result;\n    }\n\n    int clone(int node) {\n        assert(node);\n\
    \        Node copy = nodes[node];\n        return emplace(std::move(copy));\n\
    \    }\n\n    bool unique(int node) const {\n        return !node || nodes[node].references\
    \ == 1;\n    }\n\n    // Returns node itself when it has one owner, otherwise\
    \ an unowned clone.\n    // The caller must attach a returned clone with replace()\
    \ before it can be\n    // released or exposed as a root.\n    int clone_if_shared(int\
    \ node) {\n        if (unique(node)) return node;\n        return clone(node);\n\
    \    }\n\n    void replace(int& edge, int node) {\n        if (edge == node) return;\n\
    \        retain(node);\n        int old = edge;\n        edge = node;\n      \
    \  release(old);\n    }\n\n    std::size_t size() const { return live_nodes; }\n\
    };\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_NODE_POOL_HPP\n#define M1UNE_PERSISTENT_NODE_POOL_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\n\
    // Node must have integer `left`, `right`, and `references` members.\ntemplate\
    \ <class Node>\nstruct PersistentNodePool {\n    std::vector<Node> nodes;\n  \
    \  int first_free = 0;\n    std::size_t live_nodes = 0;\n\n   private:\n    void\
    \ release_zero(int node) {\n        int left = nodes[node].left;\n        int\
    \ right = nodes[node].right;\n        nodes[node] = Node();\n        nodes[node].left\
    \ = first_free;\n        first_free = node;\n        --live_nodes;\n        if\
    \ (left && --nodes[left].references == 0) release_zero(left);\n        if (right\
    \ && --nodes[right].references == 0) release_zero(right);\n    }\n\n   public:\n\
    \    PersistentNodePool() { nodes.emplace_back(); }\n\n    void reserve(std::size_t\
    \ capacity) { nodes.reserve(capacity + 1); }\n\n    Node& operator[](int node)\
    \ { return nodes[node]; }\n\n    const Node& operator[](int node) const { return\
    \ nodes[node]; }\n\n    void retain(int node) {\n        if (node) ++nodes[node].references;\n\
    \    }\n\n    void release(int node) {\n        if (!node) return;\n        assert(nodes[node].references\
    \ > 0);\n        if (--nodes[node].references == 0) release_zero(node);\n    }\n\
    \n    template <class... Args>\n    int emplace(Args&&... args) {\n        int\
    \ result;\n        if (!first_free) {\n            assert(nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \            nodes.emplace_back(std::forward<Args>(args)...);\n            result\
    \ = int(nodes.size()) - 1;\n        } else {\n            result = first_free;\n\
    \            first_free = nodes[result].left;\n            nodes[result] = Node(std::forward<Args>(args)...);\n\
    \        }\n        Node& node = nodes[result];\n        node.references = 0;\n\
    \        retain(node.left);\n        retain(node.right);\n        ++live_nodes;\n\
    \        return result;\n    }\n\n    int clone(int node) {\n        assert(node);\n\
    \        Node copy = nodes[node];\n        return emplace(std::move(copy));\n\
    \    }\n\n    bool unique(int node) const {\n        return !node || nodes[node].references\
    \ == 1;\n    }\n\n    // Returns node itself when it has one owner, otherwise\
    \ an unowned clone.\n    // The caller must attach a returned clone with replace()\
    \ before it can be\n    // released or exposed as a root.\n    int clone_if_shared(int\
    \ node) {\n        if (unique(node)) return node;\n        return clone(node);\n\
    \    }\n\n    void replace(int& edge, int node) {\n        if (edge == node) return;\n\
    \        retain(node);\n        int old = edge;\n        edge = node;\n      \
    \  release(old);\n    }\n\n    std::size_t size() const { return live_nodes; }\n\
    };\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_PERSISTENT_NODE_POOL_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/segtree/persistent_node_pool.hpp
  requiredBy:
  - ds/segtree/persistent_lazy_segtree.hpp
  - ds/segtree/persistent_dynamic_dual_segtree.hpp
  - ds/segtree/persistent_dynamic_segtree.hpp
  - ds/segtree/persistent_segtree_beats.hpp
  - ds/segtree/persistent_dynamic_lazy_segtree.hpp
  - ds/segtree/persistent_segtree.hpp
  - ds/segtree/persistent_dual_segtree.hpp
  timestamp: '2026-08-12 03:11:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/persistent_cow.test.cpp
  - verify/ds/segtree/persistent_dual_segtree.test.cpp
  - verify/ds/segtree/persistent_segtree.test.cpp
  - verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
  - verify/ds/segtree/persistent_dynamic_segtree.test.cpp
  - verify/ds/segtree/persistent_lazy_segtree.test.cpp
  - verify/ds/segtree/persistent_segtree_beats.test.cpp
  - verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
documentation_of: ds/segtree/persistent_node_pool.hpp
layout: document
redirect_from:
- /library/ds/segtree/persistent_node_pool.hpp
- /library/ds/segtree/persistent_node_pool.hpp.html
title: ds/segtree/persistent_node_pool.hpp
---
