---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_persistent_base.hpp
    title: ds/detail/rollback_persistent_base.hpp
  - icon: ':heavy_check_mark:'
    path: ds/stack/persistent_stack.hpp
    title: Persistent Stack
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/stack/rollback_stack.hpp\"\n\n\n\n#include <utility>\n\
    \n#line 1 \"ds/detail/rollback_persistent_base.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <limits>\n#line 8 \"ds/detail/rollback_persistent_base.hpp\"\
    \n#include <vector>\n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\
    \ntemplate <class Persistent>\nstruct RollbackPersistentBase : Persistent {\n\
    \   private:\n    std::vector<Persistent> _history;\n\n   protected:\n    using\
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
    \n\n#line 1 \"ds/stack/persistent_stack.hpp\"\n\n\n\n#line 6 \"ds/stack/persistent_stack.hpp\"\
    \n#include <deque>\n#include <memory>\n#include <optional>\n#line 11 \"ds/stack/persistent_stack.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Purely persistent LIFO stack with\
    \ O(1) operations.\ntemplate <class T>\nstruct PersistentStack {\n   private:\n\
    \    struct Node {\n        T value;\n        int next;\n\n        template <class...\
    \ Args>\n        Node(int next_node, Args&&... args)\n            : value(std::forward<Args>(args)...),\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 8 \"ds/stack/rollback_stack.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct RollbackStack\
    \ : detail::RollbackPersistentBase<PersistentStack<T>> {\n   private:\n    using\
    \ Persistent = PersistentStack<T>;\n    using Base = detail::RollbackPersistentBase<Persistent>;\n\
    \n   public:\n    using Base::Base;\n\n    void push(T value) {\n        Base::commit(Base::persistent().push(std::move(value)));\n\
    \    }\n\n    template <class... Args>\n    void emplace(Args&&... args) {\n \
    \       Base::commit(Base::persistent().emplace(std::forward<Args>(args)...));\n\
    \    }\n\n    void pop() {\n        Base::commit(Base::persistent().pop());\n\
    \    }\n\n    void clear() {\n        Base::commit(Base::persistent().clear());\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_STACK_ROLLBACK_STACK_HPP\n#define M1UNE_DS_STACK_ROLLBACK_STACK_HPP\
    \ 1\n\n#include <utility>\n\n#include \"../detail/rollback_persistent_base.hpp\"\
    \n#include \"persistent_stack.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\ntemplate\
    \ <class T>\nstruct RollbackStack : detail::RollbackPersistentBase<PersistentStack<T>>\
    \ {\n   private:\n    using Persistent = PersistentStack<T>;\n    using Base =\
    \ detail::RollbackPersistentBase<Persistent>;\n\n   public:\n    using Base::Base;\n\
    \n    void push(T value) {\n        Base::commit(Base::persistent().push(std::move(value)));\n\
    \    }\n\n    template <class... Args>\n    void emplace(Args&&... args) {\n \
    \       Base::commit(Base::persistent().emplace(std::forward<Args>(args)...));\n\
    \    }\n\n    void pop() {\n        Base::commit(Base::persistent().pop());\n\
    \    }\n\n    void clear() {\n        Base::commit(Base::persistent().clear());\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_STACK_ROLLBACK_STACK_HPP\n"
  dependsOn:
  - ds/detail/rollback_persistent_base.hpp
  - ds/stack/persistent_stack.hpp
  isVerificationFile: false
  path: ds/stack/rollback_stack.hpp
  requiredBy: []
  timestamp: '2026-08-12 04:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/stack/rollback_stack.hpp
layout: document
title: Rollback Stack
---

## Overview

`RollbackStack<T>` is a mutable LIFO stack whose updates can be undone. It
shares nodes between saved states, so `snapshot()` is constant time and only
new persistent-stack nodes are retained in the history.

Every call to an update method advances history once. Snapshots are valid only
on the current history path; after rollback, discarded future states cannot be
restored.

## Methods

The constructors and read-only methods `size`, `empty`, `top`, and `node_count`
match `PersistentStack<T>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push(T value)` | Pushes `value` and advances history. | $O(1)$ |
| `template<class... Args> void emplace(Args&&... args)` | Constructs and pushes a value, then advances history. | $O(1)$ |
| `void pop()` | Removes the top and advances history. Requires a nonempty stack. | $O(1)$ |
| `void clear()` | Removes all values and advances history. | $O(1)$ |
| `int history_size() const`, `int snapshot() const` | Returns the current history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Restores the state before the latest update. | $O(F)$ |
| `void rollback(int state)` | Restores a snapshot on the current history path. | $O(F)$ total |
| `void clear_history()` | Forgets saved states without changing the stack. | $O(F)$ |
| `void release()` | Releases the stack and its saved states. | $O(F)$ |
| `const PersistentStack<T>& current_version() const` | Returns a read-only persistent handle to the current state. | $O(1)$ |

Here $H$ is the requested capacity and $F$ is the number of nodes whose final
reference is released.

## Example

```cpp
#include "ds/stack/rollback_stack.hpp"

m1une::ds::RollbackStack<int> stack;
stack.push(1);
int state = stack.snapshot();
stack.push(2);
stack.rollback(state);
assert(stack.top() == 1);
```
