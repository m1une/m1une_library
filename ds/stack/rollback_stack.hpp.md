---
data:
  _extendedDependsOn: []
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
  bundledCode: "#line 1 \"ds/stack/rollback_stack.hpp\"\n\n\n\n#include <cassert>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <class T>\nstruct RollbackStack {\n   private:\n\
    \    enum class Kind { push, pop, clear };\n    struct Entry {\n        Kind kind;\n\
    \        std::optional<T> value;\n        std::vector<T> values;\n    };\n\n \
    \   std::vector<T> _values;\n    std::vector<Entry> _history;\n    std::vector<std::size_t>\
    \ _checkpoints;\n    std::size_t _stored_values = 0;\n\n   public:\n    RollbackStack()\
    \ = default;\n\n    int size() const { return int(_values.size()); }\n    bool\
    \ empty() const { return _values.empty(); }\n    std::size_t node_count() const\
    \ { return _stored_values; }\n\n    const T& top() const {\n        assert(!empty());\n\
    \        return _values.back();\n    }\n\n    void push(T value) {\n        if\
    \ (!_checkpoints.empty()) _history.push_back(Entry{Kind::push, std::nullopt, {}});\n\
    \        _values.push_back(std::move(value));\n        ++_stored_values;\n   \
    \ }\n\n    template <class... Args>\n    void emplace(Args&&... args) {\n    \
    \    if (!_checkpoints.empty()) _history.push_back(Entry{Kind::push, std::nullopt,\
    \ {}});\n        _values.emplace_back(std::forward<Args>(args)...);\n        ++_stored_values;\n\
    \    }\n\n    void pop() {\n        assert(!empty());\n        if (_checkpoints.empty())\
    \ {\n            _values.pop_back();\n            --_stored_values;\n        }\
    \ else {\n            Entry entry{Kind::pop, std::nullopt, {}};\n            entry.value.emplace(std::move(_values.back()));\n\
    \            _values.pop_back();\n            _history.push_back(std::move(entry));\n\
    \        }\n    }\n\n    void clear() {\n        if (_checkpoints.empty()) {\n\
    \            _stored_values -= _values.size();\n            _values.clear();\n\
    \        } else {\n            Entry entry{Kind::clear, std::nullopt, {}};\n \
    \           entry.values = std::move(_values);\n            _values.clear();\n\
    \            _history.push_back(std::move(entry));\n        }\n    }\n\n    int\
    \ snapshot() {\n        _checkpoints.push_back(_history.size());\n        return\
    \ int(_checkpoints.size());\n    }\n    int snapshot_count() const { return int(_checkpoints.size());\
    \ }\n\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n\
    \        _checkpoints.reserve(count);\n    }\n\n   private:\n    void restore_one()\
    \ {\n        Entry entry = std::move(_history.back());\n        _history.pop_back();\n\
    \        if (entry.kind == Kind::push) {\n            _values.pop_back();\n  \
    \          --_stored_values;\n        } else if (entry.kind == Kind::pop) {\n\
    \            _values.push_back(std::move(*entry.value));\n        } else {\n \
    \           _values = std::move(entry.values);\n        }\n    }\n\n   public:\n\
    \    void rollback(int state) {\n        assert(1 <= state && state <= snapshot_count());\n\
    \        while (_history.size() > _checkpoints[state - 1]) restore_one();\n  \
    \      _checkpoints.resize(state);\n    }\n\n    void clear_history() {\n    \
    \    for (const Entry& entry : _history) {\n            if (entry.value) --_stored_values;\n\
    \            _stored_values -= entry.values.size();\n        }\n        _history.clear();\n\
    \        _checkpoints.clear();\n    }\n\n    void release() {\n        _values.clear();\n\
    \        _history.clear();\n        _checkpoints.clear();\n        _stored_values\
    \ = 0;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_STACK_ROLLBACK_STACK_HPP\n#define M1UNE_DS_STACK_ROLLBACK_STACK_HPP\
    \ 1\n\n#include <cassert>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct RollbackStack\
    \ {\n   private:\n    enum class Kind { push, pop, clear };\n    struct Entry\
    \ {\n        Kind kind;\n        std::optional<T> value;\n        std::vector<T>\
    \ values;\n    };\n\n    std::vector<T> _values;\n    std::vector<Entry> _history;\n\
    \    std::vector<std::size_t> _checkpoints;\n    std::size_t _stored_values =\
    \ 0;\n\n   public:\n    RollbackStack() = default;\n\n    int size() const { return\
    \ int(_values.size()); }\n    bool empty() const { return _values.empty(); }\n\
    \    std::size_t node_count() const { return _stored_values; }\n\n    const T&\
    \ top() const {\n        assert(!empty());\n        return _values.back();\n \
    \   }\n\n    void push(T value) {\n        if (!_checkpoints.empty()) _history.push_back(Entry{Kind::push,\
    \ std::nullopt, {}});\n        _values.push_back(std::move(value));\n        ++_stored_values;\n\
    \    }\n\n    template <class... Args>\n    void emplace(Args&&... args) {\n \
    \       if (!_checkpoints.empty()) _history.push_back(Entry{Kind::push, std::nullopt,\
    \ {}});\n        _values.emplace_back(std::forward<Args>(args)...);\n        ++_stored_values;\n\
    \    }\n\n    void pop() {\n        assert(!empty());\n        if (_checkpoints.empty())\
    \ {\n            _values.pop_back();\n            --_stored_values;\n        }\
    \ else {\n            Entry entry{Kind::pop, std::nullopt, {}};\n            entry.value.emplace(std::move(_values.back()));\n\
    \            _values.pop_back();\n            _history.push_back(std::move(entry));\n\
    \        }\n    }\n\n    void clear() {\n        if (_checkpoints.empty()) {\n\
    \            _stored_values -= _values.size();\n            _values.clear();\n\
    \        } else {\n            Entry entry{Kind::clear, std::nullopt, {}};\n \
    \           entry.values = std::move(_values);\n            _values.clear();\n\
    \            _history.push_back(std::move(entry));\n        }\n    }\n\n    int\
    \ snapshot() {\n        _checkpoints.push_back(_history.size());\n        return\
    \ int(_checkpoints.size());\n    }\n    int snapshot_count() const { return int(_checkpoints.size());\
    \ }\n\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n\
    \        _checkpoints.reserve(count);\n    }\n\n   private:\n    void restore_one()\
    \ {\n        Entry entry = std::move(_history.back());\n        _history.pop_back();\n\
    \        if (entry.kind == Kind::push) {\n            _values.pop_back();\n  \
    \          --_stored_values;\n        } else if (entry.kind == Kind::pop) {\n\
    \            _values.push_back(std::move(*entry.value));\n        } else {\n \
    \           _values = std::move(entry.values);\n        }\n    }\n\n   public:\n\
    \    void rollback(int state) {\n        assert(1 <= state && state <= snapshot_count());\n\
    \        while (_history.size() > _checkpoints[state - 1]) restore_one();\n  \
    \      _checkpoints.resize(state);\n    }\n\n    void clear_history() {\n    \
    \    for (const Entry& entry : _history) {\n            if (entry.value) --_stored_values;\n\
    \            _stored_values -= entry.values.size();\n        }\n        _history.clear();\n\
    \        _checkpoints.clear();\n    }\n\n    void release() {\n        _values.clear();\n\
    \        _history.clear();\n        _checkpoints.clear();\n        _stored_values\
    \ = 0;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_STACK_ROLLBACK_STACK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/stack/rollback_stack.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/stack/rollback_stack.hpp
layout: document
title: Rollback Stack
---

## Overview

`RollbackStack<T>` is a mutable LIFO stack that supports registered snapshots and rollback. It
shares nodes between saved states, so `snapshot()` is constant time and only
rollback values are retained only after the first active snapshot.

on the current history path; after rollback, discarded future states cannot be
restored.

## Methods

The constructors and read-only methods `size`, `empty`, `top`, and `node_count`
follow the corresponding mutable structure.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push(T value)` | Pushes `value`. | $O(1)$ |
| `template<class... Args> void emplace(Args&&... args)` | Constructs and pushes a value. | $O(1)$ |
| `void pop()` | Removes the top. Requires a nonempty stack. | $O(1)$ |
| `void clear()` | Removes all values. | $O(N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a snapshot on the current history path. | $O(F)$ total |
| `void clear_history()` | Forgets saved states without changing the stack. | $O(F)$ |
| `void release()` | Releases the stack and its saved states. | $O(F)$ |

Here $H$ is the requested capacity and $F$ is the number of nodes whose final
reference is released.

## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

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
