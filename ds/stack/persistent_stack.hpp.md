---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_release.test.cpp
    title: verify/ds/persistent_release.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/stack/persistent_stack.test.cpp
    title: verify/ds/stack/persistent_stack.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/stack/persistent_stack.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <deque>\n#include <memory>\n#include <optional>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    // Purely persistent LIFO stack with O(1) operations.\ntemplate <class T>\nstruct\
    \ PersistentStack {\n   private:\n    struct Node {\n        T value;\n      \
    \  int next;\n\n        template <class... Args>\n        Node(int next_node,\
    \ Args&&... args)\n            : value(std::forward<Args>(args)...), next(next_node)\
    \ {}\n    };\n\n    struct Pool {\n        std::deque<std::optional<Node>> nodes;\n\
    \        std::vector<int> references;\n        std::vector<int> next_free;\n \
    \       int first_free = -1;\n        std::size_t live_nodes = 0;\n\n        template\
    \ <class... Args>\n        int emplace(int next, Args&&... args) {\n         \
    \   int result;\n            if (first_free == -1) {\n                result =\
    \ int(nodes.size());\n                nodes.emplace_back(std::in_place, next,\
    \ std::forward<Args>(args)...);\n                references.push_back(0);\n  \
    \              next_free.push_back(-1);\n            } else {\n              \
    \  result = first_free;\n                first_free = next_free[result];\n   \
    \             nodes[result].emplace(next, std::forward<Args>(args)...);\n    \
    \            references[result] = 0;\n            }\n            retain(next);\n\
    \            ++live_nodes;\n            return result;\n        }\n\n        Node&\
    \ operator[](int node) { return *nodes[node]; }\n        const Node& operator[](int\
    \ node) const { return *nodes[node]; }\n\n        void retain(int node) {\n  \
    \          if (node != -1) ++references[node];\n        }\n\n        void release(int\
    \ node) {\n            while (node != -1) {\n                assert(nodes[node].has_value()\
    \ && references[node] > 0);\n                if (--references[node] != 0) return;\n\
    \                int next = nodes[node]->next;\n                nodes[node].reset();\n\
    \                next_free[node] = first_free;\n                first_free = node;\n\
    \                --live_nodes;\n                node = next;\n            }\n\
    \        }\n    };\n\n    int _size;\n    int _top;\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    PersistentStack(\n        int stack_size,\n        int top,\n\
    \        std::shared_ptr<Pool> pool\n    )\n        : _size(stack_size), _top(top),\
    \ _pool(std::move(pool)) {\n        _pool->retain(_top);\n    }\n\n   public:\n\
    \    PersistentStack()\n        : _size(0),\n          _top(-1),\n          _pool(std::make_shared<Pool>())\
    \ {}\n\n    PersistentStack(const PersistentStack& other)\n        : _size(other._size),\
    \ _top(other._top), _pool(other._pool) {\n        if (_pool) _pool->retain(_top);\n\
    \    }\n\n    PersistentStack(PersistentStack&& other) noexcept\n        : _size(other._size),\
    \ _top(other._top), _pool(std::move(other._pool)) {\n        other._size = 0;\n\
    \        other._top = -1;\n    }\n\n    PersistentStack& operator=(const PersistentStack&\
    \ other) {\n        if (this == &other) return *this;\n        if (other._pool)\
    \ other._pool->retain(other._top);\n        if (_pool) _pool->release(_top);\n\
    \        _size = other._size;\n        _top = other._top;\n        _pool = other._pool;\n\
    \        return *this;\n    }\n\n    PersistentStack& operator=(PersistentStack&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ _pool->release(_top);\n        _size = other._size;\n        _top = other._top;\n\
    \        _pool = std::move(other._pool);\n        other._size = 0;\n        other._top\
    \ = -1;\n        return *this;\n    }\n\n    ~PersistentStack() {\n        if\
    \ (_pool) _pool->release(_top);\n    }\n\n    int size() const {\n        return\
    \ _size;\n    }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\
    \n    void release() {\n        if (_pool) _pool->release(_top);\n        _size\
    \ = 0;\n        _top = -1;\n        _pool = std::make_shared<Pool>();\n    }\n\
    \n    std::size_t node_count() const { return _pool ? _pool->live_nodes : 0; }\n\
    \n    const T& top() const {\n        assert(!empty() && _top != -1);\n      \
    \  return (*_pool)[_top].value;\n    }\n\n    PersistentStack push(T value) const\
    \ {\n        return emplace(std::move(value));\n    }\n\n    template <class...\
    \ Args>\n    PersistentStack emplace(Args&&... args) const {\n        int top\
    \ = _pool->emplace(_top, std::forward<Args>(args)...);\n        return PersistentStack(\n\
    \            _size + 1,\n            top,\n            _pool\n        );\n   \
    \ }\n\n    PersistentStack pop() const {\n        assert(!empty() && _top != -1);\n\
    \        return PersistentStack(_size - 1, (*_pool)[_top].next, _pool);\n    }\n\
    \n    PersistentStack clear() const {\n        return PersistentStack(0, -1, _pool);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_STACK_PERSISTENT_STACK_HPP\n#define M1UNE_DS_STACK_PERSISTENT_STACK_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <deque>\n#include <memory>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// Purely persistent LIFO stack with O(1) operations.\n\
    template <class T>\nstruct PersistentStack {\n   private:\n    struct Node {\n\
    \        T value;\n        int next;\n\n        template <class... Args>\n   \
    \     Node(int next_node, Args&&... args)\n            : value(std::forward<Args>(args)...),\
    \ next(next_node) {}\n    };\n\n    struct Pool {\n        std::deque<std::optional<Node>>\
    \ nodes;\n        std::vector<int> references;\n        std::vector<int> next_free;\n\
    \        int first_free = -1;\n        std::size_t live_nodes = 0;\n\n       \
    \ template <class... Args>\n        int emplace(int next, Args&&... args) {\n\
    \            int result;\n            if (first_free == -1) {\n              \
    \  result = int(nodes.size());\n                nodes.emplace_back(std::in_place,\
    \ next, std::forward<Args>(args)...);\n                references.push_back(0);\n\
    \                next_free.push_back(-1);\n            } else {\n            \
    \    result = first_free;\n                first_free = next_free[result];\n \
    \               nodes[result].emplace(next, std::forward<Args>(args)...);\n  \
    \              references[result] = 0;\n            }\n            retain(next);\n\
    \            ++live_nodes;\n            return result;\n        }\n\n        Node&\
    \ operator[](int node) { return *nodes[node]; }\n        const Node& operator[](int\
    \ node) const { return *nodes[node]; }\n\n        void retain(int node) {\n  \
    \          if (node != -1) ++references[node];\n        }\n\n        void release(int\
    \ node) {\n            while (node != -1) {\n                assert(nodes[node].has_value()\
    \ && references[node] > 0);\n                if (--references[node] != 0) return;\n\
    \                int next = nodes[node]->next;\n                nodes[node].reset();\n\
    \                next_free[node] = first_free;\n                first_free = node;\n\
    \                --live_nodes;\n                node = next;\n            }\n\
    \        }\n    };\n\n    int _size;\n    int _top;\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    PersistentStack(\n        int stack_size,\n        int top,\n\
    \        std::shared_ptr<Pool> pool\n    )\n        : _size(stack_size), _top(top),\
    \ _pool(std::move(pool)) {\n        _pool->retain(_top);\n    }\n\n   public:\n\
    \    PersistentStack()\n        : _size(0),\n          _top(-1),\n          _pool(std::make_shared<Pool>())\
    \ {}\n\n    PersistentStack(const PersistentStack& other)\n        : _size(other._size),\
    \ _top(other._top), _pool(other._pool) {\n        if (_pool) _pool->retain(_top);\n\
    \    }\n\n    PersistentStack(PersistentStack&& other) noexcept\n        : _size(other._size),\
    \ _top(other._top), _pool(std::move(other._pool)) {\n        other._size = 0;\n\
    \        other._top = -1;\n    }\n\n    PersistentStack& operator=(const PersistentStack&\
    \ other) {\n        if (this == &other) return *this;\n        if (other._pool)\
    \ other._pool->retain(other._top);\n        if (_pool) _pool->release(_top);\n\
    \        _size = other._size;\n        _top = other._top;\n        _pool = other._pool;\n\
    \        return *this;\n    }\n\n    PersistentStack& operator=(PersistentStack&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ _pool->release(_top);\n        _size = other._size;\n        _top = other._top;\n\
    \        _pool = std::move(other._pool);\n        other._size = 0;\n        other._top\
    \ = -1;\n        return *this;\n    }\n\n    ~PersistentStack() {\n        if\
    \ (_pool) _pool->release(_top);\n    }\n\n    int size() const {\n        return\
    \ _size;\n    }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\
    \n    void release() {\n        if (_pool) _pool->release(_top);\n        _size\
    \ = 0;\n        _top = -1;\n        _pool = std::make_shared<Pool>();\n    }\n\
    \n    std::size_t node_count() const { return _pool ? _pool->live_nodes : 0; }\n\
    \n    const T& top() const {\n        assert(!empty() && _top != -1);\n      \
    \  return (*_pool)[_top].value;\n    }\n\n    PersistentStack push(T value) const\
    \ {\n        return emplace(std::move(value));\n    }\n\n    template <class...\
    \ Args>\n    PersistentStack emplace(Args&&... args) const {\n        int top\
    \ = _pool->emplace(_top, std::forward<Args>(args)...);\n        return PersistentStack(\n\
    \            _size + 1,\n            top,\n            _pool\n        );\n   \
    \ }\n\n    PersistentStack pop() const {\n        assert(!empty() && _top != -1);\n\
    \        return PersistentStack(_size - 1, (*_pool)[_top].next, _pool);\n    }\n\
    \n    PersistentStack clear() const {\n        return PersistentStack(0, -1, _pool);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_STACK_PERSISTENT_STACK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/stack/persistent_stack.hpp
  requiredBy: []
  timestamp: '2026-08-11 13:59:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/persistent_release.test.cpp
  - verify/ds/stack/persistent_stack.test.cpp
documentation_of: ds/stack/persistent_stack.hpp
layout: document
title: Persistent Stack
---

## Overview

`PersistentStack<T>` is a purely persistent LIFO stack. `push`, `emplace`,
`pop`, and `clear` return new versions while every source version remains
unchanged and can be branched again.

Nodes live in a recyclable pool shared by related versions. Each node stores
one value and the index of the previous top, so every operation except bulk
release has a deterministic $O(1)$ bound. Reference counting reclaims a node
after the last version or newer stack node that depends on it is released.

## Behavior

`top()` and `pop()` require a nonempty stack and assert otherwise. Update
methods are `const` and do not change the logical contents of their source
version.

References returned by `top()` remain valid while a live version depends on the
pointed-to node. `T` may be move-only.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `PersistentStack()` | Constructs an empty stack. | $O(1)$ |
| `size` | `int size() const` | Returns the number of elements. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the stack is empty. | $O(1)$ |
| `release` | `void release()` | Releases this version immediately and makes this handle empty. | $O(F)$ |
| `node_count` | `std::size_t node_count() const` | Returns live nodes in the shared version family. | $O(1)$ |
| `top` | `const T& top() const` | Returns the top element. Requires a nonempty stack. | $O(1)$ |
| `push` | `PersistentStack push(T value) const` | Returns a version with `value` on top. | $O(1)$ |
| `emplace` | `template <class... Args> PersistentStack emplace(Args&&... args) const` | Constructs a new top element in place and returns the new version. | $O(1)$ |
| `pop` | `PersistentStack pop() const` | Returns a version without its top element. | $O(1)$ |
| `clear` | `PersistentStack clear() const` | Returns an empty related version. | $O(1)$ |

Each `push` or `emplace` creates one node. Live memory is linear in the nodes
reachable from related versions, and reclaimed slots are reused. Here $F$ is
the number of nodes that become unreachable. Destruction and assignment release
versions automatically.

## Example

```cpp
#include "ds/stack/persistent_stack.hpp"

#include <iostream>

int main() {
    m1une::ds::PersistentStack<int> empty;
    auto one = empty.push(10);
    auto two = one.push(20);
    auto branch = one.push(30);

    std::cout << two.top() << '\n';          // 20
    std::cout << two.pop().top() << '\n';    // 10
    std::cout << branch.top() << '\n';       // 30
}
```
