---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/persistent_binary_node_pool.hpp
    title: ds/detail/persistent_binary_node_pool.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/persistent_dsu.test.cpp
    title: verify/ds/dsu/persistent_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/persistent_dsu_library_checker.test.cpp
    title: verify/ds/dsu/persistent_dsu_library_checker.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_cow.test.cpp
    title: verify/ds/persistent_cow.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_release.test.cpp
    title: verify/ds/persistent_release.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/persistent_dsu.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstddef>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"ds/detail/persistent_binary_node_pool.hpp\"\n\n\
    \n\n#line 6 \"ds/detail/persistent_binary_node_pool.hpp\"\n#include <deque>\n\
    #include <limits>\n#include <optional>\n#line 11 \"ds/detail/persistent_binary_node_pool.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\n// Node must have\
    \ integer `l` and `r` members. New nodes initially have no\n// owner; discard_unreferenced()\
    \ removes temporary path-copy nodes after the\n// result roots have been retained.\n\
    template <class Node, int null_node = -1>\nstruct PersistentBinaryNodePool {\n\
    \   private:\n    std::deque<std::optional<Node>> _nodes;\n    std::vector<int>\
    \ _references;\n    std::vector<int> _next_free;\n    std::vector<int> _unowned;\n\
    \    int _first_free = -1;\n    std::size_t _live_nodes = 0;\n\n    void release_zero(int\
    \ node) {\n        assert(node != null_node && _nodes[node].has_value());\n  \
    \      int left = (*_nodes[node]).l;\n        int right = (*_nodes[node]).r;\n\
    \        _nodes[node].reset();\n        _next_free[node] = _first_free;\n    \
    \    _first_free = node;\n        --_live_nodes;\n        if (left != null_node\
    \ && --_references[left] == 0) release_zero(left);\n        if (right != null_node\
    \ && --_references[right] == 0) release_zero(right);\n    }\n\n   public:\n  \
    \  PersistentBinaryNodePool() {\n        if constexpr (null_node == 0) {\n   \
    \         _nodes.emplace_back();\n            _references.push_back(0);\n    \
    \        _next_free.push_back(-1);\n        }\n    }\n\n    Node& operator[](int\
    \ node) {\n        assert(node != null_node && _nodes[node].has_value());\n  \
    \      return *_nodes[node];\n    }\n\n    const Node& operator[](int node) const\
    \ {\n        assert(node != null_node && _nodes[node].has_value());\n        return\
    \ *_nodes[node];\n    }\n\n    template <class... Args>\n    int emplace(Args&&...\
    \ args) {\n        int result;\n        if (_first_free == -1) {\n           \
    \ assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n    \
    \        result = int(_nodes.size());\n            _nodes.emplace_back(std::in_place,\
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
    \    }\n\n    bool unique(int node) const {\n        return node == null_node\
    \ || _references[node] == 1;\n    }\n\n    int clone(int node) {\n        assert(node\
    \ != null_node && _nodes[node].has_value());\n        return emplace(*_nodes[node]);\n\
    \    }\n\n    // Returns node itself when it has one owner, otherwise an unowned\
    \ clone.\n    // A returned clone becomes owned when a root or parent edge retains\
    \ it.\n    int clone_if_shared(int node) {\n        if (unique(node)) return node;\n\
    \        return clone(node);\n    }\n\n    void replace(int& edge, int node) {\n\
    \        if (edge == node) return;\n        retain(node);\n        int old = edge;\n\
    \        edge = node;\n        release(old);\n    }\n\n    void discard_unreferenced()\
    \ {\n        while (!_unowned.empty()) {\n            int node = _unowned.back();\n\
    \            _unowned.pop_back();\n            if (_nodes[node].has_value() &&\
    \ _references[node] == 0) release_zero(node);\n        }\n    }\n\n    void reserve(std::size_t)\
    \ {}\n\n    int next_index() const { return _first_free == -1 ? int(_nodes.size())\
    \ : _first_free; }\n\n    std::size_t size() const { return _live_nodes; }\n};\n\
    \n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\n\n#line\
    \ 12 \"ds/dsu/persistent_dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\nstruct\
    \ PersistentDsu {\n   private:\n    struct Node {\n        int val;\n        int\
    \ l, r;\n\n        Node() : val(0), l(0), r(0) {}\n        explicit Node(int value)\
    \ : val(value), l(0), r(0) {}\n        Node(int value, int left, int right) :\
    \ val(value), l(left), r(right) {}\n    };\n\n    int _n;\n    int _root;\n  \
    \  using Pool = detail::PersistentBinaryNodePool<Node, 0>;\n\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    explicit PersistentDsu(int n, int root, std::shared_ptr<Pool>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {\n        _pool->retain(_root);\n\
    \    }\n\n    int new_node(const Node& node) const {\n        return _pool->emplace(node);\n\
    \    }\n\n    int new_node(Node&& node) const {\n        return _pool->emplace(std::move(node));\n\
    \    }\n\n    int build(int l, int r) const {\n        if (l == r) return 0;\n\
    \        if (r - l == 1) return new_node(Node(-1));\n        int m = (l + r) >>\
    \ 1;\n        int left = build(l, m);\n        int right = build(m, r);\n    \
    \    return new_node(Node(0, left, right));\n    }\n\n    int set_node(int t,\
    \ int l, int r, int p, int value, bool copy_on_write = false) const {\n      \
    \  if (copy_on_write) t = _pool->clone_if_shared(t);\n        if (r - l == 1)\
    \ {\n            if (copy_on_write) {\n                (*_pool)[t].val = value;\n\
    \                return t;\n            }\n            return new_node(Node(value));\n\
    \        }\n        int m = (l + r) >> 1;\n        int left = (*_pool)[t].l;\n\
    \        int right = (*_pool)[t].r;\n        if (p < m) {\n            left =\
    \ set_node(left, l, m, p, value, copy_on_write);\n        } else {\n         \
    \   right = set_node(right, m, r, p, value, copy_on_write);\n        }\n     \
    \   if (copy_on_write) {\n            _pool->replace((*_pool)[t].l, left);\n \
    \           _pool->replace((*_pool)[t].r, right);\n            return t;\n   \
    \     }\n        return new_node(Node(0, left, right));\n    }\n\n    PersistentDsu\
    \ make_version(int root) const {\n        PersistentDsu result(_n, root, _pool);\n\
    \        _pool->discard_unreferenced();\n        return result;\n    }\n\n   \
    \ int get_node(int t, int l, int r, int p) const {\n        while (r - l > 1)\
    \ {\n            int m = (l + r) >> 1;\n            if (p < m) {\n           \
    \     t = (*_pool)[t].l;\n                r = m;\n            } else {\n     \
    \           t = (*_pool)[t].r;\n                l = m;\n            }\n      \
    \  }\n        return (*_pool)[t].val;\n    }\n\n   public:\n    PersistentDsu()\
    \ : PersistentDsu(0) {}\n\n    explicit PersistentDsu(int n) : _n(n), _root(0),\
    \ _pool(std::make_shared<Pool>()) {\n        assert(0 <= n);\n        _pool->reserve(n\
    \ * 2 + 1);\n        if (_n > 0) _root = build(0, _n);\n        _pool->retain(_root);\n\
    \        _pool->discard_unreferenced();\n    }\n\n    PersistentDsu(const PersistentDsu&\
    \ other) : _n(other._n), _root(other._root), _pool(other._pool) {\n        if\
    \ (_pool) _pool->retain(_root);\n    }\n\n    PersistentDsu(PersistentDsu&& other)\
    \ noexcept\n        : _n(other._n), _root(other._root), _pool(std::move(other._pool))\
    \ {\n        other._n = 0;\n        other._root = 0;\n    }\n\n    PersistentDsu&\
    \ operator=(const PersistentDsu& other) {\n        if (this == &other) return\
    \ *this;\n        if (other._pool) other._pool->retain(other._root);\n       \
    \ if (_pool) _pool->release(_root);\n        _n = other._n;\n        _root = other._root;\n\
    \        _pool = other._pool;\n        return *this;\n    }\n\n    PersistentDsu&\
    \ operator=(PersistentDsu&& other) noexcept {\n        if (this == &other) return\
    \ *this;\n        if (_pool) _pool->release(_root);\n        _n = other._n;\n\
    \        _root = other._root;\n        _pool = std::move(other._pool);\n     \
    \   other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\n\
    \    ~PersistentDsu() {\n        if (_pool) _pool->release(_root);\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    void release() {\n        if (_pool) _pool->release(_root);\n\
    \        _n = 0;\n        _root = 0;\n        _pool = std::make_shared<Pool>();\n\
    \    }\n\n    std::size_t node_count() const { return _pool ? _pool->size() :\
    \ 0; }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       int x = a;\n        int p = get(x);\n        while (p >= 0) {\n      \
    \      x = p;\n            p = get(x);\n        }\n        return x;\n    }\n\n\
    \    bool same(int a, int b) const {\n        assert(0 <= a && a < _n);\n    \
    \    assert(0 <= b && b < _n);\n        return leader(a) == leader(b);\n    }\n\
    \n    int group_size(int a) const {\n        assert(0 <= a && a < _n);\n     \
    \   return -get(leader(a));\n    }\n\n    int size(int a) const {\n        return\
    \ group_size(a);\n    }\n\n    int get(int p) const {\n        assert(0 <= p &&\
    \ p < _n);\n        return get_node(_root, 0, _n, p);\n    }\n\n    PersistentDsu\
    \ merge(int a, int b) const {\n        assert(0 <= a && a < _n);\n        assert(0\
    \ <= b && b < _n);\n        int x = leader(a), y = leader(b);\n        if (x ==\
    \ y) return *this;\n        int sx = -get(x), sy = -get(y);\n        if (sx <\
    \ sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n      \
    \  }\n        int root = set_node(_root, 0, _n, x, -(sx + sy));\n        root\
    \ = set_node(root, 0, _n, y, x);\n        return make_version(root);\n    }\n\n\
    \    bool merge_inplace(int a, int b) {\n        assert(0 <= a && a < _n);\n \
    \       assert(0 <= b && b < _n);\n        int x = leader(a), y = leader(b);\n\
    \        if (x == y) return false;\n        int sx = -get(x), sy = -get(y);\n\
    \        if (sx < sy) {\n            std::swap(x, y);\n            std::swap(sx,\
    \ sy);\n        }\n        int root = set_node(_root, 0, _n, x, -(sx + sy), true);\n\
    \        _pool->replace(_root, root);\n        root = set_node(_root, 0, _n, y,\
    \ x, true);\n        _pool->replace(_root, root);\n        _pool->discard_unreferenced();\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups() const\
    \ {\n        std::vector<int> leader_buf(_n), group_size(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_DSU_HPP\n#define M1UNE_PERSISTENT_DSU_HPP 1\n\n\
    #include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include <memory>\n\
    #include <utility>\n#include <vector>\n\n#include \"../detail/persistent_binary_node_pool.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct PersistentDsu {\n   private:\n\
    \    struct Node {\n        int val;\n        int l, r;\n\n        Node() : val(0),\
    \ l(0), r(0) {}\n        explicit Node(int value) : val(value), l(0), r(0) {}\n\
    \        Node(int value, int left, int right) : val(value), l(left), r(right)\
    \ {}\n    };\n\n    int _n;\n    int _root;\n    using Pool = detail::PersistentBinaryNodePool<Node,\
    \ 0>;\n\n    std::shared_ptr<Pool> _pool;\n\n    explicit PersistentDsu(int n,\
    \ int root, std::shared_ptr<Pool> pool)\n        : _n(n), _root(root), _pool(std::move(pool))\
    \ {\n        _pool->retain(_root);\n    }\n\n    int new_node(const Node& node)\
    \ const {\n        return _pool->emplace(node);\n    }\n\n    int new_node(Node&&\
    \ node) const {\n        return _pool->emplace(std::move(node));\n    }\n\n  \
    \  int build(int l, int r) const {\n        if (l == r) return 0;\n        if\
    \ (r - l == 1) return new_node(Node(-1));\n        int m = (l + r) >> 1;\n   \
    \     int left = build(l, m);\n        int right = build(m, r);\n        return\
    \ new_node(Node(0, left, right));\n    }\n\n    int set_node(int t, int l, int\
    \ r, int p, int value, bool copy_on_write = false) const {\n        if (copy_on_write)\
    \ t = _pool->clone_if_shared(t);\n        if (r - l == 1) {\n            if (copy_on_write)\
    \ {\n                (*_pool)[t].val = value;\n                return t;\n   \
    \         }\n            return new_node(Node(value));\n        }\n        int\
    \ m = (l + r) >> 1;\n        int left = (*_pool)[t].l;\n        int right = (*_pool)[t].r;\n\
    \        if (p < m) {\n            left = set_node(left, l, m, p, value, copy_on_write);\n\
    \        } else {\n            right = set_node(right, m, r, p, value, copy_on_write);\n\
    \        }\n        if (copy_on_write) {\n            _pool->replace((*_pool)[t].l,\
    \ left);\n            _pool->replace((*_pool)[t].r, right);\n            return\
    \ t;\n        }\n        return new_node(Node(0, left, right));\n    }\n\n   \
    \ PersistentDsu make_version(int root) const {\n        PersistentDsu result(_n,\
    \ root, _pool);\n        _pool->discard_unreferenced();\n        return result;\n\
    \    }\n\n    int get_node(int t, int l, int r, int p) const {\n        while\
    \ (r - l > 1) {\n            int m = (l + r) >> 1;\n            if (p < m) {\n\
    \                t = (*_pool)[t].l;\n                r = m;\n            } else\
    \ {\n                t = (*_pool)[t].r;\n                l = m;\n            }\n\
    \        }\n        return (*_pool)[t].val;\n    }\n\n   public:\n    PersistentDsu()\
    \ : PersistentDsu(0) {}\n\n    explicit PersistentDsu(int n) : _n(n), _root(0),\
    \ _pool(std::make_shared<Pool>()) {\n        assert(0 <= n);\n        _pool->reserve(n\
    \ * 2 + 1);\n        if (_n > 0) _root = build(0, _n);\n        _pool->retain(_root);\n\
    \        _pool->discard_unreferenced();\n    }\n\n    PersistentDsu(const PersistentDsu&\
    \ other) : _n(other._n), _root(other._root), _pool(other._pool) {\n        if\
    \ (_pool) _pool->retain(_root);\n    }\n\n    PersistentDsu(PersistentDsu&& other)\
    \ noexcept\n        : _n(other._n), _root(other._root), _pool(std::move(other._pool))\
    \ {\n        other._n = 0;\n        other._root = 0;\n    }\n\n    PersistentDsu&\
    \ operator=(const PersistentDsu& other) {\n        if (this == &other) return\
    \ *this;\n        if (other._pool) other._pool->retain(other._root);\n       \
    \ if (_pool) _pool->release(_root);\n        _n = other._n;\n        _root = other._root;\n\
    \        _pool = other._pool;\n        return *this;\n    }\n\n    PersistentDsu&\
    \ operator=(PersistentDsu&& other) noexcept {\n        if (this == &other) return\
    \ *this;\n        if (_pool) _pool->release(_root);\n        _n = other._n;\n\
    \        _root = other._root;\n        _pool = std::move(other._pool);\n     \
    \   other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\n\
    \    ~PersistentDsu() {\n        if (_pool) _pool->release(_root);\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    void release() {\n        if (_pool) _pool->release(_root);\n\
    \        _n = 0;\n        _root = 0;\n        _pool = std::make_shared<Pool>();\n\
    \    }\n\n    std::size_t node_count() const { return _pool ? _pool->size() :\
    \ 0; }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       int x = a;\n        int p = get(x);\n        while (p >= 0) {\n      \
    \      x = p;\n            p = get(x);\n        }\n        return x;\n    }\n\n\
    \    bool same(int a, int b) const {\n        assert(0 <= a && a < _n);\n    \
    \    assert(0 <= b && b < _n);\n        return leader(a) == leader(b);\n    }\n\
    \n    int group_size(int a) const {\n        assert(0 <= a && a < _n);\n     \
    \   return -get(leader(a));\n    }\n\n    int size(int a) const {\n        return\
    \ group_size(a);\n    }\n\n    int get(int p) const {\n        assert(0 <= p &&\
    \ p < _n);\n        return get_node(_root, 0, _n, p);\n    }\n\n    PersistentDsu\
    \ merge(int a, int b) const {\n        assert(0 <= a && a < _n);\n        assert(0\
    \ <= b && b < _n);\n        int x = leader(a), y = leader(b);\n        if (x ==\
    \ y) return *this;\n        int sx = -get(x), sy = -get(y);\n        if (sx <\
    \ sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n      \
    \  }\n        int root = set_node(_root, 0, _n, x, -(sx + sy));\n        root\
    \ = set_node(root, 0, _n, y, x);\n        return make_version(root);\n    }\n\n\
    \    bool merge_inplace(int a, int b) {\n        assert(0 <= a && a < _n);\n \
    \       assert(0 <= b && b < _n);\n        int x = leader(a), y = leader(b);\n\
    \        if (x == y) return false;\n        int sx = -get(x), sy = -get(y);\n\
    \        if (sx < sy) {\n            std::swap(x, y);\n            std::swap(sx,\
    \ sy);\n        }\n        int root = set_node(_root, 0, _n, x, -(sx + sy), true);\n\
    \        _pool->replace(_root, root);\n        root = set_node(_root, 0, _n, y,\
    \ x, true);\n        _pool->replace(_root, root);\n        _pool->discard_unreferenced();\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups() const\
    \ {\n        std::vector<int> leader_buf(_n), group_size(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n#endif  // M1UNE_PERSISTENT_DSU_HPP\n"
  dependsOn:
  - ds/detail/persistent_binary_node_pool.hpp
  isVerificationFile: false
  path: ds/dsu/persistent_dsu.hpp
  requiredBy: []
  timestamp: '2026-08-12 03:11:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dsu/persistent_dsu.test.cpp
  - verify/ds/dsu/persistent_dsu_library_checker.test.cpp
  - verify/ds/persistent_release.test.cpp
  - verify/ds/persistent_cow.test.cpp
documentation_of: ds/dsu/persistent_dsu.hpp
layout: document
title: Persistent DSU
---

## Overview

`PersistentDsu` is a persistent Union-Find data structure. Merge operations return a new version and leave the old version available.

It uses union by size without path compression, because path compression mutates the search path. Parent and size values are stored in a persistent array, so each merge shares most nodes with older versions. Reference counting recycles internal array nodes after their final dependent version and parent are released.

`merge` returns a new version. `merge_inplace` mutates this handle with
copy-on-write and returns whether two previously separate components were
joined. Other live versions remain unchanged, and uniquely owned persistent
array paths are reused.

## Complexity Notation

* `N` is the number of elements.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentDsu()` | Creates an empty DSU. | $O(1)$ |
| `explicit PersistentDsu(int n)` | Creates `n` singleton sets. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the DSU has no elements. | $O(1)$ |
| `void release()` | Releases this version immediately and makes this handle empty. | $O(F)$ |
| `std::size_t node_count() const` | Returns live internal nodes in the shared version family. | $O(1)$ |
| `PersistentDsu merge(int a, int b) const` | Returns a new version where the sets containing `a` and `b` are merged. | $O(\log^2 N)$ |
| `bool merge_inplace(int a, int b)` | Merges in this version using copy-on-write and returns whether a merge occurred. | $O(\log^2 N)$ |
| `bool same(int a, int b) const` | Returns whether `a` and `b` are in the same set. | $O(\log^2 N)$ |
| `int leader(int a) const` | Returns the representative of the set containing `a`. | $O(\log^2 N)$ |
| `int group_size(int a) const`, `int size(int a) const` | Returns the size of the set containing `a`. | $O(\log^2 N)$ |
| `int get(int p) const` | Returns the internal parent-or-size value at index `p`. Roots store negative component sizes; non-roots store parent indices. | $O(\log N)$ |
| `std::vector<std::vector<int>> groups() const` | Returns all sets as vectors of element indices. | $O(N \log^2 N)$ |

Here $F$ is the number of internal nodes that become unreachable. Destruction
and assignment release roots automatically.

## Example

```cpp
#include "ds/dsu/persistent_dsu.hpp"

#include <iostream>

using namespace m1une::ds;

int main() {
    PersistentDsu dsu(5);

    PersistentDsu a = dsu.merge(0, 1);
    PersistentDsu b = a.merge(1, 2);

    std::cout << dsu.same(0, 2) << "\n"; // 0
    std::cout << a.same(0, 2) << "\n";   // 0
    std::cout << b.same(0, 2) << "\n";   // 1
    std::cout << b.size(0) << "\n";       // 3
}
```
