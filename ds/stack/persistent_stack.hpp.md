---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/stack/persistent_stack.test.cpp
    title: verify/ds/stack/persistent_stack.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/stack/persistent_stack.hpp\"\n\n\n\n#include <cassert>\n\
    #include <deque>\n#include <memory>\n#include <utility>\n\nnamespace m1une {\n\
    namespace ds {\n\n// Purely persistent LIFO stack with O(1) operations.\ntemplate\
    \ <class T>\nstruct PersistentStack {\n   private:\n    struct Node {\n      \
    \  T value;\n        int next;\n\n        template <class... Args>\n        Node(int\
    \ next_node, Args&&... args)\n            : value(std::forward<Args>(args)...),\
    \ next(next_node) {}\n    };\n\n    int _size;\n    int _top;\n    std::shared_ptr<std::deque<Node>>\
    \ _pool;\n\n    PersistentStack(\n        int stack_size,\n        int top,\n\
    \        std::shared_ptr<std::deque<Node>> pool\n    )\n        : _size(stack_size),\
    \ _top(top), _pool(std::move(pool)) {}\n\n   public:\n    PersistentStack()\n\
    \        : _size(0),\n          _top(-1),\n          _pool(std::make_shared<std::deque<Node>>())\
    \ {}\n\n    int size() const {\n        return _size;\n    }\n\n    bool empty()\
    \ const {\n        return _size == 0;\n    }\n\n    const T& top() const {\n \
    \       assert(!empty() && _top != -1);\n        return (*_pool)[_top].value;\n\
    \    }\n\n    PersistentStack push(T value) const {\n        return emplace(std::move(value));\n\
    \    }\n\n    template <class... Args>\n    PersistentStack emplace(Args&&...\
    \ args) const {\n        _pool->emplace_back(_top, std::forward<Args>(args)...);\n\
    \        return PersistentStack(\n            _size + 1,\n            int(_pool->size())\
    \ - 1,\n            _pool\n        );\n    }\n\n    PersistentStack pop() const\
    \ {\n        assert(!empty() && _top != -1);\n        return PersistentStack(_size\
    \ - 1, (*_pool)[_top].next, _pool);\n    }\n\n    PersistentStack clear() const\
    \ {\n        return PersistentStack(0, -1, _pool);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_STACK_PERSISTENT_STACK_HPP\n#define M1UNE_DS_STACK_PERSISTENT_STACK_HPP\
    \ 1\n\n#include <cassert>\n#include <deque>\n#include <memory>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Purely persistent LIFO stack with O(1)\
    \ operations.\ntemplate <class T>\nstruct PersistentStack {\n   private:\n   \
    \ struct Node {\n        T value;\n        int next;\n\n        template <class...\
    \ Args>\n        Node(int next_node, Args&&... args)\n            : value(std::forward<Args>(args)...),\
    \ next(next_node) {}\n    };\n\n    int _size;\n    int _top;\n    std::shared_ptr<std::deque<Node>>\
    \ _pool;\n\n    PersistentStack(\n        int stack_size,\n        int top,\n\
    \        std::shared_ptr<std::deque<Node>> pool\n    )\n        : _size(stack_size),\
    \ _top(top), _pool(std::move(pool)) {}\n\n   public:\n    PersistentStack()\n\
    \        : _size(0),\n          _top(-1),\n          _pool(std::make_shared<std::deque<Node>>())\
    \ {}\n\n    int size() const {\n        return _size;\n    }\n\n    bool empty()\
    \ const {\n        return _size == 0;\n    }\n\n    const T& top() const {\n \
    \       assert(!empty() && _top != -1);\n        return (*_pool)[_top].value;\n\
    \    }\n\n    PersistentStack push(T value) const {\n        return emplace(std::move(value));\n\
    \    }\n\n    template <class... Args>\n    PersistentStack emplace(Args&&...\
    \ args) const {\n        _pool->emplace_back(_top, std::forward<Args>(args)...);\n\
    \        return PersistentStack(\n            _size + 1,\n            int(_pool->size())\
    \ - 1,\n            _pool\n        );\n    }\n\n    PersistentStack pop() const\
    \ {\n        assert(!empty() && _top != -1);\n        return PersistentStack(_size\
    \ - 1, (*_pool)[_top].next, _pool);\n    }\n\n    PersistentStack clear() const\
    \ {\n        return PersistentStack(0, -1, _pool);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_STACK_PERSISTENT_STACK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/stack/persistent_stack.hpp
  requiredBy: []
  timestamp: '2026-07-15 02:11:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/stack/persistent_stack.test.cpp
documentation_of: ds/stack/persistent_stack.hpp
layout: document
title: Persistent Stack
---

## Overview

`PersistentStack<T>` is a purely persistent LIFO stack. `push`, `emplace`,
`pop`, and `clear` return new versions while every source version remains
unchanged and can be branched again.

Nodes live in an append-only pool shared by related versions. Each node stores
one value and the index of the previous top, so every public operation has a
deterministic $O(1)$ bound. The pool is released when the last related stack
version is destroyed.

## Behavior

`top()` and `pop()` require a nonempty stack and assert otherwise. Update
methods are `const` and do not change the logical contents of their source
version.

References returned by `top()` remain valid while any related version keeps the
shared pool alive. `T` may be move-only.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `PersistentStack()` | Constructs an empty stack. | $O(1)$ |
| `size` | `int size() const` | Returns the number of elements. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the stack is empty. | $O(1)$ |
| `top` | `const T& top() const` | Returns the top element. Requires a nonempty stack. | $O(1)$ |
| `push` | `PersistentStack push(T value) const` | Returns a version with `value` on top. | $O(1)$ |
| `emplace` | `template <class... Args> PersistentStack emplace(Args&&... args) const` | Constructs a new top element in place and returns the new version. | $O(1)$ |
| `pop` | `PersistentStack pop() const` | Returns a version without its top element. | $O(1)$ |
| `clear` | `PersistentStack clear() const` | Returns an empty related version. | $O(1)$ |

Each `push` or `emplace` creates one node, so memory use is linear in the total
number of inserted elements across all related versions.

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
