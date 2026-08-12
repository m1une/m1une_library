---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_release.test.cpp
    title: verify/ds/persistent_release.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/queue/persistent_queue.test.cpp
    title: verify/ds/queue/persistent_queue.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/queue/persistent_queue.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <deque>\n#include <memory>\n#include <optional>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    // Purely persistent FIFO queue with worst-case O(1) operations.\ntemplate <class\
    \ T>\nstruct PersistentQueue {\n   private:\n    struct Link {\n        int value_index;\n\
    \        int next;\n\n        Link(int index, int next_link) : value_index(index),\
    \ next(next_link) {}\n    };\n\n    struct Pool {\n        std::deque<std::optional<T>>\
    \ values;\n        std::deque<std::optional<Link>> links;\n        std::vector<int>\
    \ value_references, link_references;\n        std::vector<int> next_free_value,\
    \ next_free_link;\n        std::vector<int> unowned_values, unowned_links;\n \
    \       int first_free_value = -1;\n        int first_free_link = -1;\n      \
    \  std::size_t live_values = 0;\n        std::size_t live_links = 0;\n\n     \
    \   void retain_value(int value) {\n            if (value != -1) ++value_references[value];\n\
    \        }\n\n        void release_value(int value) {\n            if (value ==\
    \ -1) return;\n            assert(values[value].has_value() && value_references[value]\
    \ > 0);\n            if (--value_references[value] != 0) return;\n           \
    \ values[value].reset();\n            next_free_value[value] = first_free_value;\n\
    \            first_free_value = value;\n            --live_values;\n        }\n\
    \n        void retain_link(int link) {\n            if (link != -1) ++link_references[link];\n\
    \        }\n\n        void release_zero_link(int link) {\n            while (link\
    \ != -1) {\n                assert(links[link].has_value() && link_references[link]\
    \ == 0);\n                int value = links[link]->value_index;\n            \
    \    int next = links[link]->next;\n                links[link].reset();\n   \
    \             next_free_link[link] = first_free_link;\n                first_free_link\
    \ = link;\n                --live_links;\n                release_value(value);\n\
    \                if (next == -1 || --link_references[next] != 0) return;\n   \
    \             link = next;\n            }\n        }\n\n        void release_link(int\
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
    \n\n"
  code: "#ifndef M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP\n#define M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <deque>\n#include <memory>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// Purely persistent FIFO queue with worst-case O(1) operations.\n\
    template <class T>\nstruct PersistentQueue {\n   private:\n    struct Link {\n\
    \        int value_index;\n        int next;\n\n        Link(int index, int next_link)\
    \ : value_index(index), next(next_link) {}\n    };\n\n    struct Pool {\n    \
    \    std::deque<std::optional<T>> values;\n        std::deque<std::optional<Link>>\
    \ links;\n        std::vector<int> value_references, link_references;\n      \
    \  std::vector<int> next_free_value, next_free_link;\n        std::vector<int>\
    \ unowned_values, unowned_links;\n        int first_free_value = -1;\n       \
    \ int first_free_link = -1;\n        std::size_t live_values = 0;\n        std::size_t\
    \ live_links = 0;\n\n        void retain_value(int value) {\n            if (value\
    \ != -1) ++value_references[value];\n        }\n\n        void release_value(int\
    \ value) {\n            if (value == -1) return;\n            assert(values[value].has_value()\
    \ && value_references[value] > 0);\n            if (--value_references[value]\
    \ != 0) return;\n            values[value].reset();\n            next_free_value[value]\
    \ = first_free_value;\n            first_free_value = value;\n            --live_values;\n\
    \        }\n\n        void retain_link(int link) {\n            if (link != -1)\
    \ ++link_references[link];\n        }\n\n        void release_zero_link(int link)\
    \ {\n            while (link != -1) {\n                assert(links[link].has_value()\
    \ && link_references[link] == 0);\n                int value = links[link]->value_index;\n\
    \                int next = links[link]->next;\n                links[link].reset();\n\
    \                next_free_link[link] = first_free_link;\n                first_free_link\
    \ = link;\n                --live_links;\n                release_value(value);\n\
    \                if (next == -1 || --link_references[next] != 0) return;\n   \
    \             link = next;\n            }\n        }\n\n        void release_link(int\
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
    \n#endif  // M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/queue/persistent_queue.hpp
  requiredBy: []
  timestamp: '2026-08-11 13:59:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/persistent_release.test.cpp
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

Values are stored once in a shared recyclable pool. Rotation links refer to
values by index, so `T` may be move-only. Reference counting reclaims both links
and values after their final dependent version or link is released.

## Behavior

`front()`, `back()`, `pop()`, and `pop_front()` require a nonempty queue and
assert otherwise. Update methods are `const` and never change the logical
contents of the source version.

References returned by `front()` and `back()` remain valid while any related
version depends on the pointed-to value.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `PersistentQueue()` | Constructs an empty queue. | $O(1)$ |
| `size` | `int size() const` | Returns the number of elements. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the queue is empty. | $O(1)$ |
| `release` | `void release()` | Releases this version immediately and makes this handle empty. | $O(F)$ |
| `node_count` | `std::size_t node_count() const` | Returns live values and internal links in the shared version family. | $O(1)$ |
| `front` | `const T& front() const` | Returns the first element. Requires a nonempty queue. | $O(1)$ |
| `back` | `const T& back() const` | Returns the last element. Requires a nonempty queue. | $O(1)$ |
| `push` | `PersistentQueue push(T value) const` | Returns a version with `value` appended. | Worst-case $O(1)$ |
| `push_back` | `PersistentQueue push_back(T value) const` | Alias of `push`. | Worst-case $O(1)$ |
| `pop` | `PersistentQueue pop() const` | Returns a version without its first element. | Worst-case $O(1)$ |
| `pop_front` | `PersistentQueue pop_front() const` | Alias of `pop`. | Worst-case $O(1)$ |
| `clear` | `PersistentQueue clear() const` | Returns an empty related version. | $O(1)$ |

Each push stores one `T` and creates $O(1)$ small link nodes. Rotation work also
creates $O(1)$ links per update, so total memory is linear in the number of
updates across all related versions. Here $F$ is the number of values and links
that become unreachable. Destruction and assignment release versions
automatically.

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
