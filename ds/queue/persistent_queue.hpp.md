---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/queue/persistent_queue.test.cpp
    title: verify/ds/queue/persistent_queue.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/queue/persistent_queue.hpp\"\n\n\n\n#include <cassert>\n\
    #include <deque>\n#include <memory>\n#include <utility>\n\nnamespace m1une {\n\
    namespace ds {\n\n// Purely persistent FIFO queue with worst-case O(1) operations.\n\
    template <class T>\nstruct PersistentQueue {\n   private:\n    struct Link {\n\
    \        int value_index;\n        int next;\n\n        Link(int index, int next_link)\
    \ : value_index(index), next(next_link) {}\n    };\n\n    struct Pool {\n    \
    \    std::deque<T> values;\n        std::deque<Link> links;\n    };\n\n    enum\
    \ class RotationPhase {\n        idle,\n        reversing,\n        appending,\n\
    \        done,\n    };\n\n    struct RotationState {\n        RotationPhase phase\
    \ = RotationPhase::idle;\n        int valid_count = 0;\n        int remaining_front\
    \ = -1;\n        int reversed_front = -1;\n        int remaining_rear = -1;\n\
    \        int reversed_rear = -1;\n    };\n\n    int _front_size;\n    int _front;\n\
    \    RotationState _rotation;\n    int _rear_size;\n    int _rear;\n    int _back_value;\n\
    \    std::shared_ptr<Pool> _pool;\n\n    PersistentQueue(\n        int front_size,\n\
    \        int front,\n        RotationState rotation,\n        int rear_size,\n\
    \        int rear,\n        int back_value,\n        std::shared_ptr<Pool> pool\n\
    \    )\n        : _front_size(front_size),\n          _front(front),\n       \
    \   _rotation(rotation),\n          _rear_size(rear_size),\n          _rear(rear),\n\
    \          _back_value(back_value),\n          _pool(std::move(pool)) {}\n\n \
    \   int next_link(int link) const {\n        assert(link != -1);\n        return\
    \ _pool->links[link].next;\n    }\n\n    int link_value(int link) const {\n  \
    \      assert(link != -1);\n        return _pool->links[link].value_index;\n \
    \   }\n\n    int make_link(int value_index, int next) const {\n        _pool->links.emplace_back(value_index,\
    \ next);\n        return int(_pool->links.size()) - 1;\n    }\n\n    int store_value(T\
    \ value) const {\n        _pool->values.emplace_back(std::move(value));\n    \
    \    return int(_pool->values.size()) - 1;\n    }\n\n    RotationState execute(RotationState\
    \ state) const {\n        if (state.phase == RotationPhase::reversing) {\n   \
    \         assert(state.remaining_rear != -1);\n            if (state.remaining_front\
    \ != -1) {\n                state.reversed_front = make_link(\n              \
    \      link_value(state.remaining_front),\n                    state.reversed_front\n\
    \                );\n                state.remaining_front = next_link(state.remaining_front);\n\
    \                state.reversed_rear = make_link(\n                    link_value(state.remaining_rear),\n\
    \                    state.reversed_rear\n                );\n               \
    \ state.remaining_rear = next_link(state.remaining_rear);\n                state.valid_count++;\n\
    \            } else {\n                assert(next_link(state.remaining_rear)\
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
    \ {}\n\n    int size() const {\n        return _front_size + _rear_size;\n   \
    \ }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\n    const\
    \ T& front() const {\n        assert(!empty() && _front != -1);\n        return\
    \ _pool->values[link_value(_front)];\n    }\n\n    const T& back() const {\n \
    \       assert(!empty() && _back_value != -1);\n        return _pool->values[_back_value];\n\
    \    }\n\n    PersistentQueue push(T value) const {\n        int value_index =\
    \ store_value(std::move(value));\n        int rear = make_link(value_index, _rear);\n\
    \        return check(\n            _front_size,\n            _front,\n      \
    \      _rotation,\n            _rear_size + 1,\n            rear,\n          \
    \  value_index\n        );\n    }\n\n    PersistentQueue push_back(T value) const\
    \ {\n        return push(std::move(value));\n    }\n\n    PersistentQueue pop()\
    \ const {\n        assert(!empty() && _front != -1);\n        int back_value =\
    \ size() == 1 ? -1 : _back_value;\n        return check(\n            _front_size\
    \ - 1,\n            next_link(_front),\n            invalidate(_rotation),\n \
    \           _rear_size,\n            _rear,\n            back_value\n        );\n\
    \    }\n\n    PersistentQueue pop_front() const {\n        return pop();\n   \
    \ }\n\n    PersistentQueue clear() const {\n        return PersistentQueue(\n\
    \            0,\n            -1,\n            RotationState(),\n            0,\n\
    \            -1,\n            -1,\n            _pool\n        );\n    }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP\n#define M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP\
    \ 1\n\n#include <cassert>\n#include <deque>\n#include <memory>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Purely persistent FIFO queue with worst-case\
    \ O(1) operations.\ntemplate <class T>\nstruct PersistentQueue {\n   private:\n\
    \    struct Link {\n        int value_index;\n        int next;\n\n        Link(int\
    \ index, int next_link) : value_index(index), next(next_link) {}\n    };\n\n \
    \   struct Pool {\n        std::deque<T> values;\n        std::deque<Link> links;\n\
    \    };\n\n    enum class RotationPhase {\n        idle,\n        reversing,\n\
    \        appending,\n        done,\n    };\n\n    struct RotationState {\n   \
    \     RotationPhase phase = RotationPhase::idle;\n        int valid_count = 0;\n\
    \        int remaining_front = -1;\n        int reversed_front = -1;\n       \
    \ int remaining_rear = -1;\n        int reversed_rear = -1;\n    };\n\n    int\
    \ _front_size;\n    int _front;\n    RotationState _rotation;\n    int _rear_size;\n\
    \    int _rear;\n    int _back_value;\n    std::shared_ptr<Pool> _pool;\n\n  \
    \  PersistentQueue(\n        int front_size,\n        int front,\n        RotationState\
    \ rotation,\n        int rear_size,\n        int rear,\n        int back_value,\n\
    \        std::shared_ptr<Pool> pool\n    )\n        : _front_size(front_size),\n\
    \          _front(front),\n          _rotation(rotation),\n          _rear_size(rear_size),\n\
    \          _rear(rear),\n          _back_value(back_value),\n          _pool(std::move(pool))\
    \ {}\n\n    int next_link(int link) const {\n        assert(link != -1);\n   \
    \     return _pool->links[link].next;\n    }\n\n    int link_value(int link) const\
    \ {\n        assert(link != -1);\n        return _pool->links[link].value_index;\n\
    \    }\n\n    int make_link(int value_index, int next) const {\n        _pool->links.emplace_back(value_index,\
    \ next);\n        return int(_pool->links.size()) - 1;\n    }\n\n    int store_value(T\
    \ value) const {\n        _pool->values.emplace_back(std::move(value));\n    \
    \    return int(_pool->values.size()) - 1;\n    }\n\n    RotationState execute(RotationState\
    \ state) const {\n        if (state.phase == RotationPhase::reversing) {\n   \
    \         assert(state.remaining_rear != -1);\n            if (state.remaining_front\
    \ != -1) {\n                state.reversed_front = make_link(\n              \
    \      link_value(state.remaining_front),\n                    state.reversed_front\n\
    \                );\n                state.remaining_front = next_link(state.remaining_front);\n\
    \                state.reversed_rear = make_link(\n                    link_value(state.remaining_rear),\n\
    \                    state.reversed_rear\n                );\n               \
    \ state.remaining_rear = next_link(state.remaining_rear);\n                state.valid_count++;\n\
    \            } else {\n                assert(next_link(state.remaining_rear)\
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
    \ {}\n\n    int size() const {\n        return _front_size + _rear_size;\n   \
    \ }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\n    const\
    \ T& front() const {\n        assert(!empty() && _front != -1);\n        return\
    \ _pool->values[link_value(_front)];\n    }\n\n    const T& back() const {\n \
    \       assert(!empty() && _back_value != -1);\n        return _pool->values[_back_value];\n\
    \    }\n\n    PersistentQueue push(T value) const {\n        int value_index =\
    \ store_value(std::move(value));\n        int rear = make_link(value_index, _rear);\n\
    \        return check(\n            _front_size,\n            _front,\n      \
    \      _rotation,\n            _rear_size + 1,\n            rear,\n          \
    \  value_index\n        );\n    }\n\n    PersistentQueue push_back(T value) const\
    \ {\n        return push(std::move(value));\n    }\n\n    PersistentQueue pop()\
    \ const {\n        assert(!empty() && _front != -1);\n        int back_value =\
    \ size() == 1 ? -1 : _back_value;\n        return check(\n            _front_size\
    \ - 1,\n            next_link(_front),\n            invalidate(_rotation),\n \
    \           _rear_size,\n            _rear,\n            back_value\n        );\n\
    \    }\n\n    PersistentQueue pop_front() const {\n        return pop();\n   \
    \ }\n\n    PersistentQueue clear() const {\n        return PersistentQueue(\n\
    \            0,\n            -1,\n            RotationState(),\n            0,\n\
    \            -1,\n            -1,\n            _pool\n        );\n    }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/queue/persistent_queue.hpp
  requiredBy: []
  timestamp: '2026-07-15 02:08:30+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/queue/persistent_queue.test.cpp
documentation_of: ds/queue/persistent_queue.hpp
layout: document
title: Persistent Queue
---

## Overview

`PersistentQueue<T>` is a purely persistent FIFO queue. Every update returns a
new queue while the original version and every earlier branch remain unchanged.

The implementation uses the Hood--Melville real-time rotation schedule. Each
update performs at most a constant amount of pending list rotation, including
when versions branch, so operations have deterministic worst-case bounds rather
than only amortized bounds.

Values are stored once in a shared append-only pool. Rotation links refer to
values by index, so `T` may be move-only. The pool is released when the last
related queue version is destroyed.

## Behavior

`front()`, `back()`, `pop()`, and `pop_front()` require a nonempty queue and
assert otherwise. Update methods are `const` and never change the logical
contents of the source version.

References returned by `front()` and `back()` remain valid while any related
version keeps the shared pool alive.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `PersistentQueue()` | Constructs an empty queue. | $O(1)$ |
| `size` | `int size() const` | Returns the number of elements. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the queue is empty. | $O(1)$ |
| `front` | `const T& front() const` | Returns the first element. Requires a nonempty queue. | $O(1)$ |
| `back` | `const T& back() const` | Returns the last element. Requires a nonempty queue. | $O(1)$ |
| `push` | `PersistentQueue push(T value) const` | Returns a version with `value` appended. | Worst-case $O(1)$ |
| `push_back` | `PersistentQueue push_back(T value) const` | Alias of `push`. | Worst-case $O(1)$ |
| `pop` | `PersistentQueue pop() const` | Returns a version without its first element. | Worst-case $O(1)$ |
| `pop_front` | `PersistentQueue pop_front() const` | Alias of `pop`. | Worst-case $O(1)$ |
| `clear` | `PersistentQueue clear() const` | Returns an empty related version. | $O(1)$ |

Each push stores one `T` and creates $O(1)$ small link nodes. Rotation work also
creates $O(1)$ links per update, so total memory is linear in the number of
updates across all related versions.

## Example

```cpp
#include "ds/queue/persistent_queue.hpp"

#include <iostream>

int main() {
    m1une::ds::PersistentQueue<int> empty;
    auto one = empty.push(10);
    auto two = one.push(20);
    auto branch = one.push(30);

    std::cout << two.front() << ' ' << two.back() << '\n';  // 10 20
    std::cout << two.pop().front() << '\n';                 // 20
    std::cout << branch.pop().front() << '\n';              // 30
}
```
