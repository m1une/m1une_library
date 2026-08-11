---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/deque/persistent_deque.hpp
    title: Persistent Deque
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_persistent_base.hpp
    title: ds/detail/rollback_persistent_base.hpp
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
  bundledCode: "#line 1 \"ds/deque/rollback_deque.hpp\"\n\n\n\n#include <utility>\n\
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
    \n\n#line 1 \"ds/deque/persistent_deque.hpp\"\n\n\n\n#line 6 \"ds/deque/persistent_deque.hpp\"\
    \n#include <cstdint>\n#include <deque>\n#include <memory>\n#include <optional>\n\
    #line 12 \"ds/deque/persistent_deque.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\n\n// Okasaki's purely persistent real-time deque.\ntemplate <class T>\nstruct\
    \ PersistentDeque {\n   private:\n    static constexpr int balance_factor = 2;\n\
    \n    enum class StreamKind : std::uint8_t {\n        cons,\n        take,\n \
    \       rotate_drop,\n        rotate_reverse,\n    };\n\n    // The three integer\
    \ fields contain either an evaluated cons cell or the\n    // arguments of one\
    \ incremental stream operation.\n    struct StreamNode {\n        mutable StreamKind\
    \ kind;\n        mutable int first;\n        mutable int second;\n        mutable\
    \ int third;\n\n        StreamNode(\n            StreamKind node_kind,\n     \
    \       int first_argument,\n            int second_argument,\n            int\
    \ third_argument = -1\n        )\n            : kind(node_kind),\n           \
    \   first(first_argument),\n              second(second_argument),\n         \
    \     third(third_argument) {}\n    };\n\n    struct Pool {\n        std::deque<std::optional<T>>\
    \ values;\n        std::deque<std::optional<StreamNode>> streams;\n        std::vector<int>\
    \ value_references, stream_references;\n        std::vector<int> next_free_value,\
    \ next_free_stream;\n        std::vector<int> unowned_values, unowned_streams;\n\
    \        int first_free_value = -1;\n        int first_free_stream = -1;\n   \
    \     std::size_t live_values = 0;\n        std::size_t live_streams = 0;\n\n\
    \        void retain_value(int value) {\n            if (value != -1) ++value_references[value];\n\
    \        }\n\n        void release_value(int value) {\n            if (value ==\
    \ -1) return;\n            assert(values[value].has_value() && value_references[value]\
    \ > 0);\n            if (--value_references[value] != 0) return;\n           \
    \ values[value].reset();\n            next_free_value[value] = first_free_value;\n\
    \            first_free_value = value;\n            --live_values;\n        }\n\
    \n        void retain_stream(int stream) {\n            if (stream != -1) ++stream_references[stream];\n\
    \        }\n\n        void retain_dependencies(const StreamNode& node) {\n   \
    \         if (node.kind == StreamKind::cons) {\n                retain_value(node.first);\n\
    \                retain_stream(node.second);\n            } else if (node.kind\
    \ == StreamKind::take) {\n                retain_stream(node.first);\n       \
    \     } else if (node.kind == StreamKind::rotate_drop) {\n                retain_stream(node.first);\n\
    \                retain_stream(node.third);\n            } else {\n          \
    \      retain_stream(node.first);\n                retain_stream(node.second);\n\
    \                retain_stream(node.third);\n            }\n        }\n\n    \
    \    void release_zero_stream(int stream) {\n            std::vector<int> pending\
    \ = {stream};\n            while (!pending.empty()) {\n                int current\
    \ = pending.back();\n                pending.pop_back();\n                assert(streams[current].has_value()\
    \ && stream_references[current] == 0);\n                StreamNode node = *streams[current];\n\
    \                streams[current].reset();\n                next_free_stream[current]\
    \ = first_free_stream;\n                first_free_stream = current;\n       \
    \         --live_streams;\n\n                auto release_child = [&](int child)\
    \ {\n                    if (child != -1 && --stream_references[child] == 0) pending.push_back(child);\n\
    \                };\n                if (node.kind == StreamKind::cons) {\n  \
    \                  release_value(node.first);\n                    release_child(node.second);\n\
    \                } else if (node.kind == StreamKind::take) {\n               \
    \     release_child(node.first);\n                } else if (node.kind == StreamKind::rotate_drop)\
    \ {\n                    release_child(node.first);\n                    release_child(node.third);\n\
    \                } else {\n                    release_child(node.first);\n  \
    \                  release_child(node.second);\n                    release_child(node.third);\n\
    \                }\n            }\n        }\n\n        void release_stream(int\
    \ stream) {\n            if (stream == -1) return;\n            assert(streams[stream].has_value()\
    \ && stream_references[stream] > 0);\n            if (--stream_references[stream]\
    \ == 0) release_zero_stream(stream);\n        }\n\n        template <class...\
    \ Args>\n        int store_value(Args&&... args) {\n            int result;\n\
    \            if (first_free_value == -1) {\n                result = int(values.size());\n\
    \                values.emplace_back(std::in_place, std::forward<Args>(args)...);\n\
    \                value_references.push_back(0);\n                next_free_value.push_back(-1);\n\
    \            } else {\n                result = first_free_value;\n          \
    \      first_free_value = next_free_value[result];\n                values[result].emplace(std::forward<Args>(args)...);\n\
    \                value_references[result] = 0;\n            }\n            unowned_values.push_back(result);\n\
    \            ++live_values;\n            return result;\n        }\n\n       \
    \ int make_stream(StreamKind kind, int first, int second, int third) {\n     \
    \       int result;\n            if (first_free_stream == -1) {\n            \
    \    result = int(streams.size());\n                streams.emplace_back(std::in_place,\
    \ kind, first, second, third);\n                stream_references.push_back(0);\n\
    \                next_free_stream.push_back(-1);\n            } else {\n     \
    \           result = first_free_stream;\n                first_free_stream = next_free_stream[result];\n\
    \                streams[result].emplace(kind, first, second, third);\n      \
    \          stream_references[result] = 0;\n            }\n            retain_dependencies(*streams[result]);\n\
    \            unowned_streams.push_back(result);\n            ++live_streams;\n\
    \            return result;\n        }\n\n        void set_cons(int stream, int\
    \ value, int tail) {\n            retain_value(value);\n            retain_stream(tail);\n\
    \            StreamNode old = *streams[stream];\n            if (old.kind == StreamKind::take)\
    \ {\n                release_stream(old.first);\n            } else if (old.kind\
    \ == StreamKind::rotate_drop) {\n                release_stream(old.first);\n\
    \                release_stream(old.third);\n            } else if (old.kind ==\
    \ StreamKind::rotate_reverse) {\n                release_stream(old.first);\n\
    \                release_stream(old.second);\n                release_stream(old.third);\n\
    \            } else {\n                release_value(old.first);\n           \
    \     release_stream(old.second);\n            }\n            StreamNode& node\
    \ = *streams[stream];\n            node.kind = StreamKind::cons;\n           \
    \ node.first = value;\n            node.second = tail;\n            node.third\
    \ = -1;\n        }\n\n        void discard_unreferenced() {\n            while\
    \ (!unowned_streams.empty()) {\n                int stream = unowned_streams.back();\n\
    \                unowned_streams.pop_back();\n                if (streams[stream].has_value()\
    \ && stream_references[stream] == 0) release_zero_stream(stream);\n          \
    \  }\n            while (!unowned_values.empty()) {\n                int value\
    \ = unowned_values.back();\n                unowned_values.pop_back();\n     \
    \           if (values[value].has_value() && value_references[value] == 0) {\n\
    \                    values[value].reset();\n                    next_free_value[value]\
    \ = first_free_value;\n                    first_free_value = value;\n       \
    \             --live_values;\n                }\n            }\n        }\n\n\
    \        std::size_t size() const { return live_values + live_streams; }\n   \
    \ };\n\n    int _front_size;\n    int _front;\n    int _front_schedule;\n    int\
    \ _rear_size;\n    int _rear;\n    int _rear_schedule;\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    PersistentDeque(\n        int front_size,\n        int front,\n\
    \        int front_schedule,\n        int rear_size,\n        int rear,\n    \
    \    int rear_schedule,\n        std::shared_ptr<Pool> pool\n    )\n        :\
    \ _front_size(front_size),\n          _front(front),\n          _front_schedule(front_schedule),\n\
    \          _rear_size(rear_size),\n          _rear(rear),\n          _rear_schedule(rear_schedule),\n\
    \          _pool(std::move(pool)) {\n        retain_state();\n        _pool->discard_unreferenced();\n\
    \    }\n\n    void retain_state() const {\n        _pool->retain_stream(_front);\n\
    \        _pool->retain_stream(_front_schedule);\n        _pool->retain_stream(_rear);\n\
    \        _pool->retain_stream(_rear_schedule);\n    }\n\n    void release_state()\
    \ const {\n        _pool->release_stream(_front);\n        _pool->release_stream(_front_schedule);\n\
    \        _pool->release_stream(_rear);\n        _pool->release_stream(_rear_schedule);\n\
    \    }\n\n    template <class... Args>\n    int store_value(Args&&... args) const\
    \ {\n        return _pool->store_value(std::forward<Args>(args)...);\n    }\n\n\
    \    int make_stream(\n        StreamKind kind,\n        int first,\n        int\
    \ second,\n        int third = -1\n    ) const {\n        return _pool->make_stream(kind,\
    \ first, second, third);\n    }\n\n    int make_cons(int value_index, int tail)\
    \ const {\n        return make_stream(StreamKind::cons, value_index, tail);\n\
    \    }\n\n    int make_take(int count, int stream) const {\n        if (count\
    \ == 0) return -1;\n        assert(count > 0 && stream != -1);\n        return\
    \ make_stream(StreamKind::take, stream, count);\n    }\n\n    int make_rotate_drop(int\
    \ rear, int count, int front) const {\n        return make_stream(StreamKind::rotate_drop,\
    \ rear, count, front);\n    }\n\n    int make_rotate_reverse(int rear, int front,\
    \ int accumulator) const {\n        return make_stream(\n            StreamKind::rotate_reverse,\n\
    \            rear,\n            front,\n            accumulator\n        );\n\
    \    }\n\n    void set_cons(int stream, int value_index, int tail) const {\n \
    \       _pool->set_cons(stream, value_index, tail);\n    }\n\n    int stream_head(int\
    \ stream) const {\n        assert(stream != -1);\n        force(stream);\n   \
    \     return (*_pool->streams[stream]).first;\n    }\n\n    int stream_tail(int\
    \ stream) const {\n        assert(stream != -1);\n        force(stream);\n   \
    \     return (*_pool->streams[stream]).second;\n    }\n\n    int drop(int stream,\
    \ int count) const {\n        assert(count >= 0);\n        while (count > 0) {\n\
    \            assert(stream != -1);\n            stream = stream_tail(stream);\n\
    \            count--;\n        }\n        return stream;\n    }\n\n    // Reverses\
    \ a bounded prefix onto accumulator and returns the unconsumed\n    // suffix\
    \ together with the new accumulator.\n    std::pair<int, int> reverse_prefix(\n\
    \        int stream,\n        int count,\n        int accumulator\n    ) const\
    \ {\n        while (count > 0 && stream != -1) {\n            int value_index\
    \ = stream_head(stream);\n            stream = stream_tail(stream);\n        \
    \    accumulator = make_cons(value_index, accumulator);\n            count--;\n\
    \        }\n        return {stream, accumulator};\n    }\n\n    void force(int\
    \ stream) const {\n        assert(stream != -1);\n        StreamNode node = *_pool->streams[stream];\n\
    \        if (node.kind == StreamKind::cons) return;\n\n        if (node.kind ==\
    \ StreamKind::take) {\n            int source = node.first;\n            int count\
    \ = node.second;\n            assert(source != -1 && count > 0);\n           \
    \ int value_index = stream_head(source);\n            int tail = make_take(count\
    \ - 1, stream_tail(source));\n            set_cons(stream, value_index, tail);\n\
    \            return;\n        }\n\n        if (node.kind == StreamKind::rotate_drop)\
    \ {\n            int rear = node.first;\n            int count = node.second;\n\
    \            int front = node.third;\n            if (count < balance_factor ||\
    \ rear == -1) {\n                assert(count <= balance_factor || rear != -1);\n\
    \                int result = make_rotate_reverse(\n                    rear,\n\
    \                    drop(front, count),\n                    -1\n           \
    \     );\n                set_cons(stream, stream_head(result), stream_tail(result));\n\
    \                return;\n            }\n            assert(rear != -1);\n   \
    \         int value_index = stream_head(rear);\n            int tail = make_rotate_drop(\n\
    \                stream_tail(rear),\n                count - balance_factor,\n\
    \                drop(front, balance_factor)\n            );\n            set_cons(stream,\
    \ value_index, tail);\n            return;\n        }\n\n        assert(node.kind\
    \ == StreamKind::rotate_reverse);\n        int rear = node.first;\n        int\
    \ front = node.second;\n        int accumulator = node.third;\n        if (rear\
    \ == -1) {\n            auto [remaining, result] = reverse_prefix(\n         \
    \       front,\n                balance_factor + 1,\n                accumulator\n\
    \            );\n            assert(remaining == -1 && result != -1);\n      \
    \      set_cons(stream, stream_head(result), stream_tail(result));\n         \
    \   return;\n        }\n\n        int value_index = stream_head(rear);\n     \
    \   auto [remaining, next_accumulator] = reverse_prefix(\n            front,\n\
    \            balance_factor,\n            accumulator\n        );\n        int\
    \ tail = make_rotate_reverse(\n            stream_tail(rear),\n            remaining,\n\
    \            next_accumulator\n        );\n        set_cons(stream, value_index,\
    \ tail);\n    }\n\n    int execute_once(int schedule) const {\n        return\
    \ schedule == -1 ? -1 : stream_tail(schedule);\n    }\n\n    int execute_twice(int\
    \ schedule) const {\n        return execute_once(execute_once(schedule));\n  \
    \  }\n\n    PersistentDeque check(\n        int front_size,\n        int front,\n\
    \        int front_schedule,\n        int rear_size,\n        int rear,\n    \
    \    int rear_schedule\n    ) const {\n        if (front_size > balance_factor\
    \ * rear_size + 1) {\n            int next_front_size = (front_size + rear_size)\
    \ / 2;\n            int next_rear_size = front_size + rear_size - next_front_size;\n\
    \            int next_front = make_take(next_front_size, front);\n           \
    \ int next_rear = make_rotate_drop(\n                rear,\n                next_front_size,\n\
    \                front\n            );\n            return PersistentDeque(\n\
    \                next_front_size,\n                next_front,\n             \
    \   next_front,\n                next_rear_size,\n                next_rear,\n\
    \                next_rear,\n                _pool\n            );\n        }\n\
    \n        if (rear_size > balance_factor * front_size + 1) {\n            int\
    \ next_front_size = (front_size + rear_size) / 2;\n            int next_rear_size\
    \ = front_size + rear_size - next_front_size;\n            int next_front = make_rotate_drop(\n\
    \                front,\n                next_rear_size,\n                rear\n\
    \            );\n            int next_rear = make_take(next_rear_size, rear);\n\
    \            return PersistentDeque(\n                next_front_size,\n     \
    \           next_front,\n                next_front,\n                next_rear_size,\n\
    \                next_rear,\n                next_rear,\n                _pool\n\
    \            );\n        }\n\n        return PersistentDeque(\n            front_size,\n\
    \            front,\n            front_schedule,\n            rear_size,\n   \
    \         rear,\n            rear_schedule,\n            _pool\n        );\n \
    \   }\n\n   public:\n    PersistentDeque()\n        : _front_size(0),\n      \
    \    _front(-1),\n          _front_schedule(-1),\n          _rear_size(0),\n \
    \         _rear(-1),\n          _rear_schedule(-1),\n          _pool(std::make_shared<Pool>())\
    \ {}\n\n    PersistentDeque(const PersistentDeque& other)\n        : _front_size(other._front_size),\n\
    \          _front(other._front),\n          _front_schedule(other._front_schedule),\n\
    \          _rear_size(other._rear_size),\n          _rear(other._rear),\n    \
    \      _rear_schedule(other._rear_schedule),\n          _pool(other._pool) {\n\
    \        if (_pool) retain_state();\n    }\n\n    PersistentDeque(PersistentDeque&&\
    \ other) noexcept\n        : _front_size(other._front_size),\n          _front(other._front),\n\
    \          _front_schedule(other._front_schedule),\n          _rear_size(other._rear_size),\n\
    \          _rear(other._rear),\n          _rear_schedule(other._rear_schedule),\n\
    \          _pool(std::move(other._pool)) {\n        other._front_size = other._rear_size\
    \ = 0;\n        other._front = other._front_schedule = other._rear = other._rear_schedule\
    \ = -1;\n    }\n\n    PersistentDeque& operator=(const PersistentDeque& other)\
    \ {\n        if (this == &other) return *this;\n        if (other._pool) other.retain_state();\n\
    \        if (_pool) release_state();\n        _front_size = other._front_size;\n\
    \        _front = other._front;\n        _front_schedule = other._front_schedule;\n\
    \        _rear_size = other._rear_size;\n        _rear = other._rear;\n      \
    \  _rear_schedule = other._rear_schedule;\n        _pool = other._pool;\n    \
    \    return *this;\n    }\n\n    PersistentDeque& operator=(PersistentDeque&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ release_state();\n        _front_size = other._front_size;\n        _front =\
    \ other._front;\n        _front_schedule = other._front_schedule;\n        _rear_size\
    \ = other._rear_size;\n        _rear = other._rear;\n        _rear_schedule =\
    \ other._rear_schedule;\n        _pool = std::move(other._pool);\n        other._front_size\
    \ = other._rear_size = 0;\n        other._front = other._front_schedule = other._rear\
    \ = other._rear_schedule = -1;\n        return *this;\n    }\n\n    ~PersistentDeque()\
    \ {\n        if (_pool) release_state();\n    }\n\n    int size() const {\n  \
    \      return _front_size + _rear_size;\n    }\n\n    bool empty() const {\n \
    \       return size() == 0;\n    }\n\n    void release() {\n        if (_pool)\
    \ release_state();\n        _front_size = _rear_size = 0;\n        _front = _front_schedule\
    \ = _rear = _rear_schedule = -1;\n        _pool = std::make_shared<Pool>();\n\
    \    }\n\n    std::size_t node_count() const { return _pool ? _pool->size() :\
    \ 0; }\n\n    const T& front() const {\n        assert(!empty());\n        int\
    \ stream = _front == -1 ? _rear : _front;\n        int value = stream_head(stream);\n\
    \        _pool->discard_unreferenced();\n        return *_pool->values[value];\n\
    \    }\n\n    const T& back() const {\n        assert(!empty());\n        int\
    \ stream = _rear == -1 ? _front : _rear;\n        int value = stream_head(stream);\n\
    \        _pool->discard_unreferenced();\n        return *_pool->values[value];\n\
    \    }\n\n    PersistentDeque push_front(T value) const {\n        return emplace_front(std::move(value));\n\
    \    }\n\n    template <class... Args>\n    PersistentDeque emplace_front(Args&&...\
    \ args) const {\n        int value_index = store_value(std::forward<Args>(args)...);\n\
    \        return check(\n            _front_size + 1,\n            make_cons(value_index,\
    \ _front),\n            execute_once(_front_schedule),\n            _rear_size,\n\
    \            _rear,\n            execute_once(_rear_schedule)\n        );\n  \
    \  }\n\n    PersistentDeque push_back(T value) const {\n        return emplace_back(std::move(value));\n\
    \    }\n\n    template <class... Args>\n    PersistentDeque emplace_back(Args&&...\
    \ args) const {\n        int value_index = store_value(std::forward<Args>(args)...);\n\
    \        return check(\n            _front_size,\n            _front,\n      \
    \      execute_once(_front_schedule),\n            _rear_size + 1,\n         \
    \   make_cons(value_index, _rear),\n            execute_once(_rear_schedule)\n\
    \        );\n    }\n\n    PersistentDeque pop_front() const {\n        assert(!empty());\n\
    \        if (size() == 1) return clear();\n        assert(_front != -1);\n   \
    \     return check(\n            _front_size - 1,\n            stream_tail(_front),\n\
    \            execute_twice(_front_schedule),\n            _rear_size,\n      \
    \      _rear,\n            execute_twice(_rear_schedule)\n        );\n    }\n\n\
    \    PersistentDeque pop_back() const {\n        assert(!empty());\n        if\
    \ (size() == 1) return clear();\n        assert(_rear != -1);\n        return\
    \ check(\n            _front_size,\n            _front,\n            execute_twice(_front_schedule),\n\
    \            _rear_size - 1,\n            stream_tail(_rear),\n            execute_twice(_rear_schedule)\n\
    \        );\n    }\n\n    PersistentDeque clear() const {\n        return PersistentDeque(0,\
    \ -1, -1, 0, -1, -1, _pool);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 8 \"ds/deque/rollback_deque.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <class T>\nstruct RollbackDeque : detail::RollbackPersistentBase<PersistentDeque<T>>\
    \ {\n   private:\n    using Persistent = PersistentDeque<T>;\n    using Base =\
    \ detail::RollbackPersistentBase<Persistent>;\n\n   public:\n    using Base::Base;\n\
    \n    void push_front(T value) {\n        Base::commit(Base::persistent().push_front(std::move(value)));\n\
    \    }\n\n    template <class... Args>\n    void emplace_front(Args&&... args)\
    \ {\n        Base::commit(Base::persistent().emplace_front(std::forward<Args>(args)...));\n\
    \    }\n\n    void push_back(T value) {\n        Base::commit(Base::persistent().push_back(std::move(value)));\n\
    \    }\n\n    template <class... Args>\n    void emplace_back(Args&&... args)\
    \ {\n        Base::commit(Base::persistent().emplace_back(std::forward<Args>(args)...));\n\
    \    }\n\n    void pop_front() {\n        Base::commit(Base::persistent().pop_front());\n\
    \    }\n\n    void pop_back() {\n        Base::commit(Base::persistent().pop_back());\n\
    \    }\n\n    void clear() {\n        Base::commit(Base::persistent().clear());\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_DEQUE_ROLLBACK_DEQUE_HPP\n#define M1UNE_DS_DEQUE_ROLLBACK_DEQUE_HPP\
    \ 1\n\n#include <utility>\n\n#include \"../detail/rollback_persistent_base.hpp\"\
    \n#include \"persistent_deque.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\ntemplate\
    \ <class T>\nstruct RollbackDeque : detail::RollbackPersistentBase<PersistentDeque<T>>\
    \ {\n   private:\n    using Persistent = PersistentDeque<T>;\n    using Base =\
    \ detail::RollbackPersistentBase<Persistent>;\n\n   public:\n    using Base::Base;\n\
    \n    void push_front(T value) {\n        Base::commit(Base::persistent().push_front(std::move(value)));\n\
    \    }\n\n    template <class... Args>\n    void emplace_front(Args&&... args)\
    \ {\n        Base::commit(Base::persistent().emplace_front(std::forward<Args>(args)...));\n\
    \    }\n\n    void push_back(T value) {\n        Base::commit(Base::persistent().push_back(std::move(value)));\n\
    \    }\n\n    template <class... Args>\n    void emplace_back(Args&&... args)\
    \ {\n        Base::commit(Base::persistent().emplace_back(std::forward<Args>(args)...));\n\
    \    }\n\n    void pop_front() {\n        Base::commit(Base::persistent().pop_front());\n\
    \    }\n\n    void pop_back() {\n        Base::commit(Base::persistent().pop_back());\n\
    \    }\n\n    void clear() {\n        Base::commit(Base::persistent().clear());\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_DEQUE_ROLLBACK_DEQUE_HPP\n"
  dependsOn:
  - ds/detail/rollback_persistent_base.hpp
  - ds/deque/persistent_deque.hpp
  isVerificationFile: false
  path: ds/deque/rollback_deque.hpp
  requiredBy: []
  timestamp: '2026-08-12 04:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/deque/rollback_deque.hpp
layout: document
title: Rollback Deque
---

## Overview

`RollbackDeque<T>` is a mutable real-time double-ended queue with undo and
snapshot support. It retains shared states of `PersistentDeque<T>`. Each update
advances history exactly once.

## Methods

Constructors and the read-only methods `size`, `empty`, `front`, `back`, and
`node_count` match `PersistentDeque<T>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void push_front(T value)`, `void push_back(T value)` | Pushes at one end. | $O(1)$ worst case |
| `template<class... Args> void emplace_front(Args&&... args)`, `template<class... Args> void emplace_back(Args&&... args)` | Constructs a value at one end. | $O(1)$ worst case |
| `void pop_front()`, `void pop_back()` | Pops one end. Requires a nonempty deque. | $O(1)$ worst case |
| `void clear()` | Removes all values. | $O(1)$ |
| `int history_size() const`, `int snapshot() const` | Returns the history position. | $O(1)$ |
| `void reserve_history(int count)` | Reserves history entries. | $O(H)$ |
| `bool undo()` | Undoes one update. | $O(F)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()` | Forgets saved states. | $O(F)$ |
| `void release()` | Releases current and saved states. | $O(F)$ |
| `const PersistentDeque<T>& current_version() const` | Returns the current persistent state. | $O(1)$ |

$F$ counts nodes and delayed stream cells whose final reference is released.

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
