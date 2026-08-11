---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_persistent_base.hpp
    title: ds/detail/rollback_persistent_base.hpp
  - icon: ':heavy_check_mark:'
    path: ds/queue/persistent_queue.hpp
    title: Persistent Queue
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
  bundledCode: "#line 1 \"ds/queue/rollback_queue.hpp\"\n\n\n\n#include <utility>\n\
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
    \n\n#line 1 \"ds/queue/persistent_queue.hpp\"\n\n\n\n#line 6 \"ds/queue/persistent_queue.hpp\"\
    \n#include <deque>\n#include <memory>\n#include <optional>\n#line 11 \"ds/queue/persistent_queue.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Purely persistent FIFO queue with\
    \ worst-case O(1) operations.\ntemplate <class T>\nstruct PersistentQueue {\n\
    \   private:\n    struct Link {\n        int value_index;\n        int next;\n\
    \n        Link(int index, int next_link) : value_index(index), next(next_link)\
    \ {}\n    };\n\n    struct Pool {\n        std::deque<std::optional<T>> values;\n\
    \        std::deque<std::optional<Link>> links;\n        std::vector<int> value_references,\
    \ link_references;\n        std::vector<int> next_free_value, next_free_link;\n\
    \        std::vector<int> unowned_values, unowned_links;\n        int first_free_value\
    \ = -1;\n        int first_free_link = -1;\n        std::size_t live_values =\
    \ 0;\n        std::size_t live_links = 0;\n\n        void retain_value(int value)\
    \ {\n            if (value != -1) ++value_references[value];\n        }\n\n  \
    \      void release_value(int value) {\n            if (value == -1) return;\n\
    \            assert(values[value].has_value() && value_references[value] > 0);\n\
    \            if (--value_references[value] != 0) return;\n            values[value].reset();\n\
    \            next_free_value[value] = first_free_value;\n            first_free_value\
    \ = value;\n            --live_values;\n        }\n\n        void retain_link(int\
    \ link) {\n            if (link != -1) ++link_references[link];\n        }\n\n\
    \        void release_zero_link(int link) {\n            while (link != -1) {\n\
    \                assert(links[link].has_value() && link_references[link] == 0);\n\
    \                int value = links[link]->value_index;\n                int next\
    \ = links[link]->next;\n                links[link].reset();\n               \
    \ next_free_link[link] = first_free_link;\n                first_free_link = link;\n\
    \                --live_links;\n                release_value(value);\n      \
    \          if (next == -1 || --link_references[next] != 0) return;\n         \
    \       link = next;\n            }\n        }\n\n        void release_link(int\
    \ link) {\n            if (link == -1) return;\n            assert(links[link].has_value()\
    \ && link_references[link] > 0);\n            if (--link_references[link] == 0)\
    \ release_zero_link(link);\n        }\n\n        int store_value(T value) {\n\
    \            int result;\n            if (first_free_value == -1) {\n        \
    \        result = int(values.size());\n                values.emplace_back(std::in_place,\
    \ std::move(value));\n                value_references.push_back(0);\n       \
    \         next_free_value.push_back(-1);\n            } else {\n             \
    \   result = first_free_value;\n                first_free_value = next_free_value[result];\n\
    \                values[result].emplace(std::move(value));\n                value_references[result]\
    \ = 0;\n            }\n            unowned_values.push_back(result);\n       \
    \     ++live_values;\n            return result;\n        }\n\n        int make_link(int\
    \ value, int next) {\n            int result;\n            if (first_free_link\
    \ == -1) {\n                result = int(links.size());\n                links.emplace_back(std::in_place,\
    \ value, next);\n                link_references.push_back(0);\n             \
    \   next_free_link.push_back(-1);\n            } else {\n                result\
    \ = first_free_link;\n                first_free_link = next_free_link[result];\n\
    \                links[result].emplace(value, next);\n                link_references[result]\
    \ = 0;\n            }\n            retain_value(value);\n            retain_link(next);\n\
    \            unowned_links.push_back(result);\n            ++live_links;\n   \
    \         return result;\n        }\n\n        void discard_unreferenced() {\n\
    \            while (!unowned_links.empty()) {\n                int link = unowned_links.back();\n\
    \                unowned_links.pop_back();\n                if (links[link].has_value()\
    \ && link_references[link] == 0) release_zero_link(link);\n            }\n   \
    \         while (!unowned_values.empty()) {\n                int value = unowned_values.back();\n\
    \                unowned_values.pop_back();\n                if (values[value].has_value()\
    \ && value_references[value] == 0) {\n                    values[value].reset();\n\
    \                    next_free_value[value] = first_free_value;\n            \
    \        first_free_value = value;\n                    --live_values;\n     \
    \           }\n            }\n        }\n\n        std::size_t size() const {\
    \ return live_values + live_links; }\n    };\n\n    enum class RotationPhase {\n\
    \        idle,\n        reversing,\n        appending,\n        done,\n    };\n\
    \n    struct RotationState {\n        RotationPhase phase = RotationPhase::idle;\n\
    \        int valid_count = 0;\n        int remaining_front = -1;\n        int\
    \ reversed_front = -1;\n        int remaining_rear = -1;\n        int reversed_rear\
    \ = -1;\n    };\n\n    int _front_size;\n    int _front;\n    RotationState _rotation;\n\
    \    int _rear_size;\n    int _rear;\n    int _back_value;\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    PersistentQueue(\n        int front_size,\n        int front,\n\
    \        RotationState rotation,\n        int rear_size,\n        int rear,\n\
    \        int back_value,\n        std::shared_ptr<Pool> pool\n    )\n        :\
    \ _front_size(front_size),\n          _front(front),\n          _rotation(rotation),\n\
    \          _rear_size(rear_size),\n          _rear(rear),\n          _back_value(back_value),\n\
    \          _pool(std::move(pool)) {\n        retain_state();\n        _pool->discard_unreferenced();\n\
    \    }\n\n    void retain_state() const {\n        _pool->retain_link(_front);\n\
    \        _pool->retain_link(_rotation.remaining_front);\n        _pool->retain_link(_rotation.reversed_front);\n\
    \        _pool->retain_link(_rotation.remaining_rear);\n        _pool->retain_link(_rotation.reversed_rear);\n\
    \        _pool->retain_link(_rear);\n        _pool->retain_value(_back_value);\n\
    \    }\n\n    void release_state() const {\n        _pool->release_link(_front);\n\
    \        _pool->release_link(_rotation.remaining_front);\n        _pool->release_link(_rotation.reversed_front);\n\
    \        _pool->release_link(_rotation.remaining_rear);\n        _pool->release_link(_rotation.reversed_rear);\n\
    \        _pool->release_link(_rear);\n        _pool->release_value(_back_value);\n\
    \    }\n\n    int next_link(int link) const {\n        assert(link != -1);\n \
    \       return (*_pool->links[link]).next;\n    }\n\n    int link_value(int link)\
    \ const {\n        assert(link != -1);\n        return (*_pool->links[link]).value_index;\n\
    \    }\n\n    int make_link(int value_index, int next) const {\n        return\
    \ _pool->make_link(value_index, next);\n    }\n\n    int store_value(T value)\
    \ const {\n        return _pool->store_value(std::move(value));\n    }\n\n   \
    \ RotationState execute(RotationState state) const {\n        if (state.phase\
    \ == RotationPhase::reversing) {\n            assert(state.remaining_rear != -1);\n\
    \            if (state.remaining_front != -1) {\n                state.reversed_front\
    \ = make_link(\n                    link_value(state.remaining_front),\n     \
    \               state.reversed_front\n                );\n                state.remaining_front\
    \ = next_link(state.remaining_front);\n                state.reversed_rear = make_link(\n\
    \                    link_value(state.remaining_rear),\n                    state.reversed_rear\n\
    \                );\n                state.remaining_rear = next_link(state.remaining_rear);\n\
    \                state.valid_count++;\n            } else {\n                assert(next_link(state.remaining_rear)\
    \ == -1);\n                state.reversed_rear = make_link(\n                \
    \    link_value(state.remaining_rear),\n                    state.reversed_rear\n\
    \                );\n                state.remaining_rear = -1;\n            \
    \    state.phase = RotationPhase::appending;\n            }\n        } else if\
    \ (state.phase == RotationPhase::appending) {\n            assert(state.valid_count\
    \ >= 0);\n            if (state.valid_count == 0) {\n                state.phase\
    \ = RotationPhase::done;\n            } else {\n                assert(state.reversed_front\
    \ != -1);\n                state.reversed_rear = make_link(\n                \
    \    link_value(state.reversed_front),\n                    state.reversed_rear\n\
    \                );\n                state.reversed_front = next_link(state.reversed_front);\n\
    \                state.valid_count--;\n            }\n        }\n        return\
    \ state;\n    }\n\n    RotationState invalidate(RotationState state) const {\n\
    \        if (state.phase == RotationPhase::reversing) {\n            state.valid_count--;\n\
    \        } else if (state.phase == RotationPhase::appending) {\n            if\
    \ (state.valid_count == 0) {\n                assert(state.reversed_rear != -1);\n\
    \                state.reversed_rear = next_link(state.reversed_rear);\n     \
    \           state.phase = RotationPhase::done;\n            } else {\n       \
    \         state.valid_count--;\n            }\n        }\n        return state;\n\
    \    }\n\n    PersistentQueue execute_twice(\n        int front_size,\n      \
    \  int front,\n        RotationState rotation,\n        int rear_size,\n     \
    \   int rear,\n        int back_value\n    ) const {\n        rotation = execute(std::move(rotation));\n\
    \        rotation = execute(std::move(rotation));\n        if (rotation.phase\
    \ == RotationPhase::done) {\n            front = rotation.reversed_rear;\n   \
    \         rotation = RotationState();\n        }\n        return PersistentQueue(\n\
    \            front_size,\n            front,\n            rotation,\n        \
    \    rear_size,\n            rear,\n            back_value,\n            _pool\n\
    \        );\n    }\n\n    PersistentQueue check(\n        int front_size,\n  \
    \      int front,\n        RotationState rotation,\n        int rear_size,\n \
    \       int rear,\n        int back_value\n    ) const {\n        if (rear_size\
    \ <= front_size) {\n            return execute_twice(\n                front_size,\n\
    \                front,\n                rotation,\n                rear_size,\n\
    \                rear,\n                back_value\n            );\n        }\n\
    \n        RotationState next_rotation;\n        next_rotation.phase = RotationPhase::reversing;\n\
    \        next_rotation.remaining_front = front;\n        next_rotation.remaining_rear\
    \ = rear;\n        return execute_twice(\n            front_size + rear_size,\n\
    \            front,\n            next_rotation,\n            0,\n            -1,\n\
    \            back_value\n        );\n    }\n\n   public:\n    PersistentQueue()\n\
    \        : _front_size(0),\n          _front(-1),\n          _rear_size(0),\n\
    \          _rear(-1),\n          _back_value(-1),\n          _pool(std::make_shared<Pool>())\
    \ {}\n\n    PersistentQueue(const PersistentQueue& other)\n        : _front_size(other._front_size),\n\
    \          _front(other._front),\n          _rotation(other._rotation),\n    \
    \      _rear_size(other._rear_size),\n          _rear(other._rear),\n        \
    \  _back_value(other._back_value),\n          _pool(other._pool) {\n        if\
    \ (_pool) retain_state();\n    }\n\n    PersistentQueue(PersistentQueue&& other)\
    \ noexcept\n        : _front_size(other._front_size),\n          _front(other._front),\n\
    \          _rotation(other._rotation),\n          _rear_size(other._rear_size),\n\
    \          _rear(other._rear),\n          _back_value(other._back_value),\n  \
    \        _pool(std::move(other._pool)) {\n        other._front_size = other._rear_size\
    \ = 0;\n        other._front = other._rear = other._back_value = -1;\n       \
    \ other._rotation = RotationState();\n    }\n\n    PersistentQueue& operator=(const\
    \ PersistentQueue& other) {\n        if (this == &other) return *this;\n     \
    \   if (other._pool) other.retain_state();\n        if (_pool) release_state();\n\
    \        _front_size = other._front_size;\n        _front = other._front;\n  \
    \      _rotation = other._rotation;\n        _rear_size = other._rear_size;\n\
    \        _rear = other._rear;\n        _back_value = other._back_value;\n    \
    \    _pool = other._pool;\n        return *this;\n    }\n\n    PersistentQueue&\
    \ operator=(PersistentQueue&& other) noexcept {\n        if (this == &other) return\
    \ *this;\n        if (_pool) release_state();\n        _front_size = other._front_size;\n\
    \        _front = other._front;\n        _rotation = other._rotation;\n      \
    \  _rear_size = other._rear_size;\n        _rear = other._rear;\n        _back_value\
    \ = other._back_value;\n        _pool = std::move(other._pool);\n        other._front_size\
    \ = other._rear_size = 0;\n        other._front = other._rear = other._back_value\
    \ = -1;\n        other._rotation = RotationState();\n        return *this;\n \
    \   }\n\n    ~PersistentQueue() {\n        if (_pool) release_state();\n    }\n\
    \n    int size() const {\n        return _front_size + _rear_size;\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void release()\
    \ {\n        if (_pool) release_state();\n        _front_size = _rear_size = 0;\n\
    \        _front = _rear = _back_value = -1;\n        _rotation = RotationState();\n\
    \        _pool = std::make_shared<Pool>();\n    }\n\n    std::size_t node_count()\
    \ const { return _pool ? _pool->size() : 0; }\n\n    const T& front() const {\n\
    \        assert(!empty() && _front != -1);\n        return *_pool->values[link_value(_front)];\n\
    \    }\n\n    const T& back() const {\n        assert(!empty() && _back_value\
    \ != -1);\n        return *_pool->values[_back_value];\n    }\n\n    PersistentQueue\
    \ push(T value) const {\n        int value_index = store_value(std::move(value));\n\
    \        int rear = make_link(value_index, _rear);\n        return check(\n  \
    \          _front_size,\n            _front,\n            _rotation,\n       \
    \     _rear_size + 1,\n            rear,\n            value_index\n        );\n\
    \    }\n\n    PersistentQueue push_back(T value) const {\n        return push(std::move(value));\n\
    \    }\n\n    PersistentQueue pop() const {\n        assert(!empty() && _front\
    \ != -1);\n        int back_value = size() == 1 ? -1 : _back_value;\n        return\
    \ check(\n            _front_size - 1,\n            next_link(_front),\n     \
    \       invalidate(_rotation),\n            _rear_size,\n            _rear,\n\
    \            back_value\n        );\n    }\n\n    PersistentQueue pop_front()\
    \ const {\n        return pop();\n    }\n\n    PersistentQueue clear() const {\n\
    \        return PersistentQueue(\n            0,\n            -1,\n          \
    \  RotationState(),\n            0,\n            -1,\n            -1,\n      \
    \      _pool\n        );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 8 \"ds/queue/rollback_queue.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\n\ntemplate <class T>\nstruct RollbackQueue : detail::RollbackPersistentBase<PersistentQueue<T>>\
    \ {\n   private:\n    using Persistent = PersistentQueue<T>;\n    using Base =\
    \ detail::RollbackPersistentBase<Persistent>;\n\n   public:\n    using Base::Base;\n\
    \n    void push(T value) {\n        Base::commit(Base::persistent().push(std::move(value)));\n\
    \    }\n\n    void push_back(T value) {\n        push(std::move(value));\n   \
    \ }\n\n    void pop() {\n        Base::commit(Base::persistent().pop());\n   \
    \ }\n\n    void pop_front() {\n        pop();\n    }\n\n    void clear() {\n \
    \       Base::commit(Base::persistent().clear());\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_QUEUE_ROLLBACK_QUEUE_HPP\n#define M1UNE_DS_QUEUE_ROLLBACK_QUEUE_HPP\
    \ 1\n\n#include <utility>\n\n#include \"../detail/rollback_persistent_base.hpp\"\
    \n#include \"persistent_queue.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\ntemplate\
    \ <class T>\nstruct RollbackQueue : detail::RollbackPersistentBase<PersistentQueue<T>>\
    \ {\n   private:\n    using Persistent = PersistentQueue<T>;\n    using Base =\
    \ detail::RollbackPersistentBase<Persistent>;\n\n   public:\n    using Base::Base;\n\
    \n    void push(T value) {\n        Base::commit(Base::persistent().push(std::move(value)));\n\
    \    }\n\n    void push_back(T value) {\n        push(std::move(value));\n   \
    \ }\n\n    void pop() {\n        Base::commit(Base::persistent().pop());\n   \
    \ }\n\n    void pop_front() {\n        pop();\n    }\n\n    void clear() {\n \
    \       Base::commit(Base::persistent().clear());\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_QUEUE_ROLLBACK_QUEUE_HPP\n"
  dependsOn:
  - ds/detail/rollback_persistent_base.hpp
  - ds/queue/persistent_queue.hpp
  isVerificationFile: false
  path: ds/queue/rollback_queue.hpp
  requiredBy: []
  timestamp: '2026-08-12 04:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/queue/rollback_queue.hpp
layout: document
title: Rollback Queue
---

## Overview

`RollbackQueue<T>` is a mutable real-time FIFO queue with undo and snapshot
support. Saved states share the nodes of `PersistentQueue<T>`. Every update,
including an update that leaves an equivalent value, advances history once.

## Methods

Constructors and the read-only methods `size`, `empty`, `front`, `back`, and
`node_count` match `PersistentQueue<T>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push(T value)`, `void push_back(T value)` | Adds a value at the back. | $O(1)$ worst case |
| `void pop()`, `void pop_front()` | Removes the front. Requires a nonempty queue. | $O(1)$ worst case |
| `void clear()` | Removes all values. | $O(1)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()` | Forgets saved states. | $O(F)$ |
| `void release()` | Releases current and saved states. | $O(F)$ |
| `const PersistentQueue<T>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$F$ counts nodes whose final reference is released.

## Example

```cpp
#include "ds/queue/rollback_queue.hpp"

m1une::ds::RollbackQueue<int> queue;
queue.push(1);
int state = queue.snapshot();
queue.push(2);
queue.pop();
queue.rollback(state);
assert(queue.front() == 1);
```
