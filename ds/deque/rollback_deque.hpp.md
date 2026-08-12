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
  bundledCode: "#line 1 \"ds/deque/rollback_deque.hpp\"\n\n\n\n#include <cassert>\n\
    #include <deque>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct RollbackDeque\
    \ {\n   private:\n    enum class Kind { push_front, push_back, pop_front, pop_back,\
    \ clear };\n    struct Entry {\n        Kind kind;\n        std::optional<T> value;\n\
    \        std::deque<T> values;\n    };\n\n    std::deque<T> _values;\n    std::vector<Entry>\
    \ _history;\n    std::vector<std::size_t> _checkpoints;\n    std::size_t _stored_values\
    \ = 0;\n\n    void record_push(Kind kind) {\n        if (!_checkpoints.empty())\
    \ _history.push_back(Entry{kind, std::nullopt, {}});\n        ++_stored_values;\n\
    \    }\n\n   public:\n    RollbackDeque() = default;\n\n    int size() const {\
    \ return int(_values.size()); }\n    bool empty() const { return _values.empty();\
    \ }\n    std::size_t node_count() const { return _stored_values; }\n\n    const\
    \ T& front() const {\n        assert(!empty());\n        return _values.front();\n\
    \    }\n\n    const T& back() const {\n        assert(!empty());\n        return\
    \ _values.back();\n    }\n\n    void push_front(T value) {\n        record_push(Kind::push_front);\n\
    \        _values.push_front(std::move(value));\n    }\n\n    template <class...\
    \ Args>\n    void emplace_front(Args&&... args) {\n        record_push(Kind::push_front);\n\
    \        _values.emplace_front(std::forward<Args>(args)...);\n    }\n\n    void\
    \ push_back(T value) {\n        record_push(Kind::push_back);\n        _values.push_back(std::move(value));\n\
    \    }\n\n    template <class... Args>\n    void emplace_back(Args&&... args)\
    \ {\n        record_push(Kind::push_back);\n        _values.emplace_back(std::forward<Args>(args)...);\n\
    \    }\n\n    void pop_front() {\n        assert(!empty());\n        if (_checkpoints.empty())\
    \ {\n            _values.pop_front();\n            --_stored_values;\n       \
    \ } else {\n            Entry entry{Kind::pop_front, std::nullopt, {}};\n    \
    \        entry.value.emplace(std::move(_values.front()));\n            _values.pop_front();\n\
    \            _history.push_back(std::move(entry));\n        }\n    }\n\n    void\
    \ pop_back() {\n        assert(!empty());\n        if (_checkpoints.empty()) {\n\
    \            _values.pop_back();\n            --_stored_values;\n        } else\
    \ {\n            Entry entry{Kind::pop_back, std::nullopt, {}};\n            entry.value.emplace(std::move(_values.back()));\n\
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
    \        if (entry.kind == Kind::push_front) {\n            _values.pop_front();\n\
    \            --_stored_values;\n        } else if (entry.kind == Kind::push_back)\
    \ {\n            _values.pop_back();\n            --_stored_values;\n        }\
    \ else if (entry.kind == Kind::pop_front) {\n            _values.push_front(std::move(*entry.value));\n\
    \        } else if (entry.kind == Kind::pop_back) {\n            _values.push_back(std::move(*entry.value));\n\
    \        } else {\n            _values = std::move(entry.values);\n        }\n\
    \    }\n\n   public:\n    void rollback(int state) {\n        assert(1 <= state\
    \ && state <= snapshot_count());\n        while (_history.size() > _checkpoints[state\
    \ - 1]) restore_one();\n        _checkpoints.resize(state);\n    }\n\n    void\
    \ clear_history() {\n        for (const Entry& entry : _history) {\n         \
    \   if (entry.value) --_stored_values;\n            _stored_values -= entry.values.size();\n\
    \        }\n        _history.clear();\n        _checkpoints.clear();\n    }\n\n\
    \    void release() {\n        _values.clear();\n        _history.clear();\n \
    \       _checkpoints.clear();\n        _stored_values = 0;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_DEQUE_ROLLBACK_DEQUE_HPP\n#define M1UNE_DS_DEQUE_ROLLBACK_DEQUE_HPP\
    \ 1\n\n#include <cassert>\n#include <deque>\n#include <optional>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T>\n\
    struct RollbackDeque {\n   private:\n    enum class Kind { push_front, push_back,\
    \ pop_front, pop_back, clear };\n    struct Entry {\n        Kind kind;\n    \
    \    std::optional<T> value;\n        std::deque<T> values;\n    };\n\n    std::deque<T>\
    \ _values;\n    std::vector<Entry> _history;\n    std::vector<std::size_t> _checkpoints;\n\
    \    std::size_t _stored_values = 0;\n\n    void record_push(Kind kind) {\n  \
    \      if (!_checkpoints.empty()) _history.push_back(Entry{kind, std::nullopt,\
    \ {}});\n        ++_stored_values;\n    }\n\n   public:\n    RollbackDeque() =\
    \ default;\n\n    int size() const { return int(_values.size()); }\n    bool empty()\
    \ const { return _values.empty(); }\n    std::size_t node_count() const { return\
    \ _stored_values; }\n\n    const T& front() const {\n        assert(!empty());\n\
    \        return _values.front();\n    }\n\n    const T& back() const {\n     \
    \   assert(!empty());\n        return _values.back();\n    }\n\n    void push_front(T\
    \ value) {\n        record_push(Kind::push_front);\n        _values.push_front(std::move(value));\n\
    \    }\n\n    template <class... Args>\n    void emplace_front(Args&&... args)\
    \ {\n        record_push(Kind::push_front);\n        _values.emplace_front(std::forward<Args>(args)...);\n\
    \    }\n\n    void push_back(T value) {\n        record_push(Kind::push_back);\n\
    \        _values.push_back(std::move(value));\n    }\n\n    template <class...\
    \ Args>\n    void emplace_back(Args&&... args) {\n        record_push(Kind::push_back);\n\
    \        _values.emplace_back(std::forward<Args>(args)...);\n    }\n\n    void\
    \ pop_front() {\n        assert(!empty());\n        if (_checkpoints.empty())\
    \ {\n            _values.pop_front();\n            --_stored_values;\n       \
    \ } else {\n            Entry entry{Kind::pop_front, std::nullopt, {}};\n    \
    \        entry.value.emplace(std::move(_values.front()));\n            _values.pop_front();\n\
    \            _history.push_back(std::move(entry));\n        }\n    }\n\n    void\
    \ pop_back() {\n        assert(!empty());\n        if (_checkpoints.empty()) {\n\
    \            _values.pop_back();\n            --_stored_values;\n        } else\
    \ {\n            Entry entry{Kind::pop_back, std::nullopt, {}};\n            entry.value.emplace(std::move(_values.back()));\n\
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
    \        if (entry.kind == Kind::push_front) {\n            _values.pop_front();\n\
    \            --_stored_values;\n        } else if (entry.kind == Kind::push_back)\
    \ {\n            _values.pop_back();\n            --_stored_values;\n        }\
    \ else if (entry.kind == Kind::pop_front) {\n            _values.push_front(std::move(*entry.value));\n\
    \        } else if (entry.kind == Kind::pop_back) {\n            _values.push_back(std::move(*entry.value));\n\
    \        } else {\n            _values = std::move(entry.values);\n        }\n\
    \    }\n\n   public:\n    void rollback(int state) {\n        assert(1 <= state\
    \ && state <= snapshot_count());\n        while (_history.size() > _checkpoints[state\
    \ - 1]) restore_one();\n        _checkpoints.resize(state);\n    }\n\n    void\
    \ clear_history() {\n        for (const Entry& entry : _history) {\n         \
    \   if (entry.value) --_stored_values;\n            _stored_values -= entry.values.size();\n\
    \        }\n        _history.clear();\n        _checkpoints.clear();\n    }\n\n\
    \    void release() {\n        _values.clear();\n        _history.clear();\n \
    \       _checkpoints.clear();\n        _stored_values = 0;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_DEQUE_ROLLBACK_DEQUE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/deque/rollback_deque.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/deque/rollback_deque.hpp
layout: document
title: Rollback Deque
---

## Overview

`RollbackDeque<T>` is a mutable real-time double-ended queue with
registered-snapshot rollback. Rollback values are retained only while snapshots are active.

## Methods

Constructors and read-only methods follow ordinary double-ended queue semantics.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push_front(T value)`, `void push_back(T value)` | Pushes at one end. | $O(1)$ worst case |
| `template<class... Args> void emplace_front(Args&&... args)`, `template<class... Args> void emplace_back(Args&&... args)` | Constructs a value at one end. | $O(1)$ worst case |
| `void pop_front()`, `void pop_back()` | Pops one end. Requires a nonempty deque. | $O(1)$ worst case |
| `void clear()` | Removes all values. | $O(N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()` | Forgets saved states. | $O(F)$ |
| `void release()` | Releases current and saved states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

## Example

```cpp
#include "ds/deque/rollback_deque.hpp"

m1une::ds::RollbackDeque<int> deque;
deque.push_back(2);
int state = deque.snapshot();
deque.push_front(1);
deque.rollback(state);
assert(deque.front() == 2);
```
