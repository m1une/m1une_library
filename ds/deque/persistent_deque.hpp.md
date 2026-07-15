---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/deque/persistent_deque.test.cpp
    title: verify/ds/deque/persistent_deque.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/deque/persistent_deque.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <deque>\n#include <memory>\n#include <utility>\n\n\
    namespace m1une {\nnamespace ds {\n\n// Okasaki's purely persistent real-time\
    \ deque.\ntemplate <class T>\nstruct PersistentDeque {\n   private:\n    static\
    \ constexpr int balance_factor = 2;\n\n    enum class StreamKind : std::uint8_t\
    \ {\n        cons,\n        take,\n        rotate_drop,\n        rotate_reverse,\n\
    \    };\n\n    // The three integer fields contain either an evaluated cons cell\
    \ or the\n    // arguments of one incremental stream operation.\n    struct StreamNode\
    \ {\n        mutable StreamKind kind;\n        mutable int first;\n        mutable\
    \ int second;\n        mutable int third;\n\n        StreamNode(\n           \
    \ StreamKind node_kind,\n            int first_argument,\n            int second_argument,\n\
    \            int third_argument = -1\n        )\n            : kind(node_kind),\n\
    \              first(first_argument),\n              second(second_argument),\n\
    \              third(third_argument) {}\n    };\n\n    struct Pool {\n       \
    \ std::deque<T> values;\n        std::deque<StreamNode> streams;\n    };\n\n \
    \   int _front_size;\n    int _front;\n    int _front_schedule;\n    int _rear_size;\n\
    \    int _rear;\n    int _rear_schedule;\n    std::shared_ptr<Pool> _pool;\n\n\
    \    PersistentDeque(\n        int front_size,\n        int front,\n        int\
    \ front_schedule,\n        int rear_size,\n        int rear,\n        int rear_schedule,\n\
    \        std::shared_ptr<Pool> pool\n    )\n        : _front_size(front_size),\n\
    \          _front(front),\n          _front_schedule(front_schedule),\n      \
    \    _rear_size(rear_size),\n          _rear(rear),\n          _rear_schedule(rear_schedule),\n\
    \          _pool(std::move(pool)) {}\n\n    template <class... Args>\n    int\
    \ store_value(Args&&... args) const {\n        _pool->values.emplace_back(std::forward<Args>(args)...);\n\
    \        return int(_pool->values.size()) - 1;\n    }\n\n    int make_stream(\n\
    \        StreamKind kind,\n        int first,\n        int second,\n        int\
    \ third = -1\n    ) const {\n        _pool->streams.emplace_back(kind, first,\
    \ second, third);\n        return int(_pool->streams.size()) - 1;\n    }\n\n \
    \   int make_cons(int value_index, int tail) const {\n        return make_stream(StreamKind::cons,\
    \ value_index, tail);\n    }\n\n    int make_take(int count, int stream) const\
    \ {\n        if (count == 0) return -1;\n        assert(count > 0 && stream !=\
    \ -1);\n        return make_stream(StreamKind::take, stream, count);\n    }\n\n\
    \    int make_rotate_drop(int rear, int count, int front) const {\n        return\
    \ make_stream(StreamKind::rotate_drop, rear, count, front);\n    }\n\n    int\
    \ make_rotate_reverse(int rear, int front, int accumulator) const {\n        return\
    \ make_stream(\n            StreamKind::rotate_reverse,\n            rear,\n \
    \           front,\n            accumulator\n        );\n    }\n\n    void set_cons(int\
    \ stream, int value_index, int tail) const {\n        StreamNode& node = _pool->streams[stream];\n\
    \        node.kind = StreamKind::cons;\n        node.first = value_index;\n  \
    \      node.second = tail;\n        node.third = -1;\n    }\n\n    int stream_head(int\
    \ stream) const {\n        assert(stream != -1);\n        force(stream);\n   \
    \     return _pool->streams[stream].first;\n    }\n\n    int stream_tail(int stream)\
    \ const {\n        assert(stream != -1);\n        force(stream);\n        return\
    \ _pool->streams[stream].second;\n    }\n\n    int drop(int stream, int count)\
    \ const {\n        assert(count >= 0);\n        while (count > 0) {\n        \
    \    assert(stream != -1);\n            stream = stream_tail(stream);\n      \
    \      count--;\n        }\n        return stream;\n    }\n\n    // Reverses a\
    \ bounded prefix onto accumulator and returns the unconsumed\n    // suffix together\
    \ with the new accumulator.\n    std::pair<int, int> reverse_prefix(\n       \
    \ int stream,\n        int count,\n        int accumulator\n    ) const {\n  \
    \      while (count > 0 && stream != -1) {\n            int value_index = stream_head(stream);\n\
    \            stream = stream_tail(stream);\n            accumulator = make_cons(value_index,\
    \ accumulator);\n            count--;\n        }\n        return {stream, accumulator};\n\
    \    }\n\n    void force(int stream) const {\n        assert(stream != -1);\n\
    \        StreamNode node = _pool->streams[stream];\n        if (node.kind == StreamKind::cons)\
    \ return;\n\n        if (node.kind == StreamKind::take) {\n            int source\
    \ = node.first;\n            int count = node.second;\n            assert(source\
    \ != -1 && count > 0);\n            int value_index = stream_head(source);\n \
    \           int tail = make_take(count - 1, stream_tail(source));\n          \
    \  set_cons(stream, value_index, tail);\n            return;\n        }\n\n  \
    \      if (node.kind == StreamKind::rotate_drop) {\n            int rear = node.first;\n\
    \            int count = node.second;\n            int front = node.third;\n \
    \           if (count < balance_factor || rear == -1) {\n                assert(count\
    \ <= balance_factor || rear != -1);\n                int result = make_rotate_reverse(\n\
    \                    rear,\n                    drop(front, count),\n        \
    \            -1\n                );\n                set_cons(stream, stream_head(result),\
    \ stream_tail(result));\n                return;\n            }\n            assert(rear\
    \ != -1);\n            int value_index = stream_head(rear);\n            int tail\
    \ = make_rotate_drop(\n                stream_tail(rear),\n                count\
    \ - balance_factor,\n                drop(front, balance_factor)\n           \
    \ );\n            set_cons(stream, value_index, tail);\n            return;\n\
    \        }\n\n        assert(node.kind == StreamKind::rotate_reverse);\n     \
    \   int rear = node.first;\n        int front = node.second;\n        int accumulator\
    \ = node.third;\n        if (rear == -1) {\n            auto [remaining, result]\
    \ = reverse_prefix(\n                front,\n                balance_factor +\
    \ 1,\n                accumulator\n            );\n            assert(remaining\
    \ == -1 && result != -1);\n            set_cons(stream, stream_head(result), stream_tail(result));\n\
    \            return;\n        }\n\n        int value_index = stream_head(rear);\n\
    \        auto [remaining, next_accumulator] = reverse_prefix(\n            front,\n\
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
    \ {}\n\n    int size() const {\n        return _front_size + _rear_size;\n   \
    \ }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\n    const\
    \ T& front() const {\n        assert(!empty());\n        int stream = _front ==\
    \ -1 ? _rear : _front;\n        return _pool->values[stream_head(stream)];\n \
    \   }\n\n    const T& back() const {\n        assert(!empty());\n        int stream\
    \ = _rear == -1 ? _front : _rear;\n        return _pool->values[stream_head(stream)];\n\
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
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_DS_DEQUE_PERSISTENT_DEQUE_HPP\n#define M1UNE_DS_DEQUE_PERSISTENT_DEQUE_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <deque>\n#include <memory>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace ds {\n\n// Okasaki's purely\
    \ persistent real-time deque.\ntemplate <class T>\nstruct PersistentDeque {\n\
    \   private:\n    static constexpr int balance_factor = 2;\n\n    enum class StreamKind\
    \ : std::uint8_t {\n        cons,\n        take,\n        rotate_drop,\n     \
    \   rotate_reverse,\n    };\n\n    // The three integer fields contain either\
    \ an evaluated cons cell or the\n    // arguments of one incremental stream operation.\n\
    \    struct StreamNode {\n        mutable StreamKind kind;\n        mutable int\
    \ first;\n        mutable int second;\n        mutable int third;\n\n        StreamNode(\n\
    \            StreamKind node_kind,\n            int first_argument,\n        \
    \    int second_argument,\n            int third_argument = -1\n        )\n  \
    \          : kind(node_kind),\n              first(first_argument),\n        \
    \      second(second_argument),\n              third(third_argument) {}\n    };\n\
    \n    struct Pool {\n        std::deque<T> values;\n        std::deque<StreamNode>\
    \ streams;\n    };\n\n    int _front_size;\n    int _front;\n    int _front_schedule;\n\
    \    int _rear_size;\n    int _rear;\n    int _rear_schedule;\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    PersistentDeque(\n        int front_size,\n        int front,\n\
    \        int front_schedule,\n        int rear_size,\n        int rear,\n    \
    \    int rear_schedule,\n        std::shared_ptr<Pool> pool\n    )\n        :\
    \ _front_size(front_size),\n          _front(front),\n          _front_schedule(front_schedule),\n\
    \          _rear_size(rear_size),\n          _rear(rear),\n          _rear_schedule(rear_schedule),\n\
    \          _pool(std::move(pool)) {}\n\n    template <class... Args>\n    int\
    \ store_value(Args&&... args) const {\n        _pool->values.emplace_back(std::forward<Args>(args)...);\n\
    \        return int(_pool->values.size()) - 1;\n    }\n\n    int make_stream(\n\
    \        StreamKind kind,\n        int first,\n        int second,\n        int\
    \ third = -1\n    ) const {\n        _pool->streams.emplace_back(kind, first,\
    \ second, third);\n        return int(_pool->streams.size()) - 1;\n    }\n\n \
    \   int make_cons(int value_index, int tail) const {\n        return make_stream(StreamKind::cons,\
    \ value_index, tail);\n    }\n\n    int make_take(int count, int stream) const\
    \ {\n        if (count == 0) return -1;\n        assert(count > 0 && stream !=\
    \ -1);\n        return make_stream(StreamKind::take, stream, count);\n    }\n\n\
    \    int make_rotate_drop(int rear, int count, int front) const {\n        return\
    \ make_stream(StreamKind::rotate_drop, rear, count, front);\n    }\n\n    int\
    \ make_rotate_reverse(int rear, int front, int accumulator) const {\n        return\
    \ make_stream(\n            StreamKind::rotate_reverse,\n            rear,\n \
    \           front,\n            accumulator\n        );\n    }\n\n    void set_cons(int\
    \ stream, int value_index, int tail) const {\n        StreamNode& node = _pool->streams[stream];\n\
    \        node.kind = StreamKind::cons;\n        node.first = value_index;\n  \
    \      node.second = tail;\n        node.third = -1;\n    }\n\n    int stream_head(int\
    \ stream) const {\n        assert(stream != -1);\n        force(stream);\n   \
    \     return _pool->streams[stream].first;\n    }\n\n    int stream_tail(int stream)\
    \ const {\n        assert(stream != -1);\n        force(stream);\n        return\
    \ _pool->streams[stream].second;\n    }\n\n    int drop(int stream, int count)\
    \ const {\n        assert(count >= 0);\n        while (count > 0) {\n        \
    \    assert(stream != -1);\n            stream = stream_tail(stream);\n      \
    \      count--;\n        }\n        return stream;\n    }\n\n    // Reverses a\
    \ bounded prefix onto accumulator and returns the unconsumed\n    // suffix together\
    \ with the new accumulator.\n    std::pair<int, int> reverse_prefix(\n       \
    \ int stream,\n        int count,\n        int accumulator\n    ) const {\n  \
    \      while (count > 0 && stream != -1) {\n            int value_index = stream_head(stream);\n\
    \            stream = stream_tail(stream);\n            accumulator = make_cons(value_index,\
    \ accumulator);\n            count--;\n        }\n        return {stream, accumulator};\n\
    \    }\n\n    void force(int stream) const {\n        assert(stream != -1);\n\
    \        StreamNode node = _pool->streams[stream];\n        if (node.kind == StreamKind::cons)\
    \ return;\n\n        if (node.kind == StreamKind::take) {\n            int source\
    \ = node.first;\n            int count = node.second;\n            assert(source\
    \ != -1 && count > 0);\n            int value_index = stream_head(source);\n \
    \           int tail = make_take(count - 1, stream_tail(source));\n          \
    \  set_cons(stream, value_index, tail);\n            return;\n        }\n\n  \
    \      if (node.kind == StreamKind::rotate_drop) {\n            int rear = node.first;\n\
    \            int count = node.second;\n            int front = node.third;\n \
    \           if (count < balance_factor || rear == -1) {\n                assert(count\
    \ <= balance_factor || rear != -1);\n                int result = make_rotate_reverse(\n\
    \                    rear,\n                    drop(front, count),\n        \
    \            -1\n                );\n                set_cons(stream, stream_head(result),\
    \ stream_tail(result));\n                return;\n            }\n            assert(rear\
    \ != -1);\n            int value_index = stream_head(rear);\n            int tail\
    \ = make_rotate_drop(\n                stream_tail(rear),\n                count\
    \ - balance_factor,\n                drop(front, balance_factor)\n           \
    \ );\n            set_cons(stream, value_index, tail);\n            return;\n\
    \        }\n\n        assert(node.kind == StreamKind::rotate_reverse);\n     \
    \   int rear = node.first;\n        int front = node.second;\n        int accumulator\
    \ = node.third;\n        if (rear == -1) {\n            auto [remaining, result]\
    \ = reverse_prefix(\n                front,\n                balance_factor +\
    \ 1,\n                accumulator\n            );\n            assert(remaining\
    \ == -1 && result != -1);\n            set_cons(stream, stream_head(result), stream_tail(result));\n\
    \            return;\n        }\n\n        int value_index = stream_head(rear);\n\
    \        auto [remaining, next_accumulator] = reverse_prefix(\n            front,\n\
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
    \ {}\n\n    int size() const {\n        return _front_size + _rear_size;\n   \
    \ }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\n    const\
    \ T& front() const {\n        assert(!empty());\n        int stream = _front ==\
    \ -1 ? _rear : _front;\n        return _pool->values[stream_head(stream)];\n \
    \   }\n\n    const T& back() const {\n        assert(!empty());\n        int stream\
    \ = _rear == -1 ? _front : _rear;\n        return _pool->values[stream_head(stream)];\n\
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
    \ m1une\n\n#endif  // M1UNE_DS_DEQUE_PERSISTENT_DEQUE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/deque/persistent_deque.hpp
  requiredBy: []
  timestamp: '2026-07-15 02:53:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/deque/persistent_deque.test.cpp
documentation_of: ds/deque/persistent_deque.hpp
layout: document
title: Persistent Deque
---

## Overview

`PersistentDeque<T>` is a purely persistent double-ended queue. Every update
returns a new deque while the source version and all earlier branches remain
unchanged.

The implementation is Okasaki's real-time deque with balance factor two. It
keeps front and rear lazy streams balanced and evaluates a fixed number of
scheduled stream cells on every update. Rebalancing is incremental, so no
operation copies or traverses the whole deque.

Indexed access is intentionally not part of this endpoint deque API; adding a
general `operator[]` would not have the same worst-case constant bound.

Values live in a shared append-only pool and stream cells contain value indices.
A push therefore stores its `T` only once, and `T` may be move-only. The pool is
released when the last related deque version is destroyed.

## Behavior

`front()`, `back()`, `pop_front()`, and `pop_back()` require a nonempty deque and
assert otherwise. Update methods are `const` and never change the logical
contents of the source version.

Lazy stream cells are memoized internally when accessed. This physical
memoization is shared by related versions and does not change any version's
logical contents. References returned by `front()` and `back()` remain valid
while any related version keeps the shared pool alive.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `PersistentDeque()` | Constructs an empty deque. | Worst-case $O(1)$ |
| `size` | `int size() const` | Returns the number of elements. | Worst-case $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the deque is empty. | Worst-case $O(1)$ |
| `front` | `const T& front() const` | Returns the first element. | Worst-case $O(1)$ |
| `back` | `const T& back() const` | Returns the last element. | Worst-case $O(1)$ |
| `push_front` | `PersistentDeque push_front(T value) const` | Returns a version with `value` prepended. | Worst-case $O(1)$ |
| `emplace_front` | `template <class... Args> PersistentDeque emplace_front(Args&&... args) const` | Constructs and prepends a value. | Worst-case $O(1)$ |
| `push_back` | `PersistentDeque push_back(T value) const` | Returns a version with `value` appended. | Worst-case $O(1)$ |
| `emplace_back` | `template <class... Args> PersistentDeque emplace_back(Args&&... args) const` | Constructs and appends a value. | Worst-case $O(1)$ |
| `pop_front` | `PersistentDeque pop_front() const` | Returns a version without its first element. | Worst-case $O(1)$ |
| `pop_back` | `PersistentDeque pop_back() const` | Returns a version without its last element. | Worst-case $O(1)$ |
| `clear` | `PersistentDeque clear() const` | Returns an empty related version. | Worst-case $O(1)$ |

Each push stores one `T`. Every operation creates and evaluates only $O(1)$
stream cells, so memory usage is $O(1)$ per update across all branches.

## Example

```cpp
#include "ds/deque/persistent_deque.hpp"

#include <iostream>

int main() {
    m1une::ds::PersistentDeque<int> empty;
    auto middle = empty.push_back(20);
    auto both = middle.push_front(10).push_back(30);
    auto branch = middle.push_front(5);

    std::cout << both.front() << ' ' << both.back() << '\n';  // 10 30
    std::cout << both.pop_front().front() << '\n';             // 20
    std::cout << branch.front() << ' ' << branch.back() << '\n';  // 5 20
}
```
