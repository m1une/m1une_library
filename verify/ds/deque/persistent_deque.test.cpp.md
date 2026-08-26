---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/deque/persistent_deque.hpp
    title: Persistent Deque
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_queue
    links:
    - https://judge.yosupo.jp/problem/persistent_queue
  bundledCode: "#line 1 \"verify/ds/deque/persistent_deque.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/persistent_queue\"\n\n#line 1 \"ds/deque/persistent_deque.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#include <cstdint>\n#include <deque>\n\
    #include <memory>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Okasaki's purely persistent real-time\
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
    \ std::deque<std::optional<T>> values;\n        std::deque<std::optional<StreamNode>>\
    \ streams;\n        std::vector<int> value_references, stream_references;\n  \
    \      std::vector<int> next_free_value, next_free_stream;\n        std::vector<int>\
    \ unowned_values, unowned_streams;\n        int first_free_value = -1;\n     \
    \   int first_free_stream = -1;\n        std::size_t live_values = 0;\n      \
    \  std::size_t live_streams = 0;\n\n        void retain_value(int value) {\n \
    \           if (value != -1) ++value_references[value];\n        }\n\n       \
    \ void release_value(int value) {\n            if (value == -1) return;\n    \
    \        assert(values[value].has_value() && value_references[value] > 0);\n \
    \           if (--value_references[value] != 0) return;\n            values[value].reset();\n\
    \            next_free_value[value] = first_free_value;\n            first_free_value\
    \ = value;\n            --live_values;\n        }\n\n        void retain_stream(int\
    \ stream) {\n            if (stream != -1) ++stream_references[stream];\n    \
    \    }\n\n        void retain_dependencies(const StreamNode& node) {\n       \
    \     if (node.kind == StreamKind::cons) {\n                retain_value(node.first);\n\
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
    \ m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n\
    #include <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n\
    #include <type_traits>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\
    \nnamespace m1une {\nnamespace utilities {\n\nstruct FastOutput;\n\nnamespace\
    \ internal {\n\n// Shared with the convenience helpers in template.hpp.\ninline\
    \ FastOutput* standard_output_instance = nullptr;\n\n// Detect std::begin(x),\
    \ std::end(x).\ntemplate <class T, class = void>\nstruct is_range : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {\n        if (_stream == stdout\n          \
    \  && internal::standard_output_instance == nullptr) {\n            internal::standard_output_instance\
    \ = this;\n        }\n    }\n\n    FastOutput(const FastOutput&) = delete;\n \
    \   FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n        if (internal::standard_output_instance == this) {\n\
    \            internal::standard_output_instance = nullptr;\n        }\n    }\n\
    \n    void flush() {\n        if (_position != 0) {\n            std::fwrite(_buffer,\
    \ 1, _position, _stream);\n            _position = 0;\n        }\n        std::fflush(_stream);\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        std::size_t position = 0;\n        while (position\
    \ < s.size()) {\n            if (_position == buffer_size) flush();\n        \
    \    const std::size_t copied =\n                std::min<std::size_t>(buffer_size\
    \ - _position, s.size() - position);\n            std::memcpy(_buffer + _position,\
    \ s.data() + position, copied);\n            _position += int(copied);\n     \
    \       position += copied;\n        }\n    }\n\n    void write(char c) {\n  \
    \      write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 5 \"verify/ds/deque/persistent_deque.test.cpp\"\
    \n\n#line 12 \"verify/ds/deque/persistent_deque.test.cpp\"\n\nnamespace {\n\n\
    using Deque = m1une::ds::PersistentDeque<int>;\n\nvoid assert_ends(const Deque&\
    \ actual, const std::deque<int>& expected) {\n    assert(actual.size() == int(expected.size()));\n\
    \    assert(actual.empty() == expected.empty());\n    if (expected.empty()) return;\n\
    \    assert(actual.front() == expected.front());\n    assert(actual.back() ==\
    \ expected.back());\n}\n\nvoid assert_all(Deque actual, std::deque<int> expected)\
    \ {\n    assert_ends(actual, expected);\n    while (!expected.empty()) {\n   \
    \     assert(actual.front() == expected.front());\n        actual = actual.pop_front();\n\
    \        expected.pop_front();\n    }\n    assert(actual.empty());\n}\n\nvoid\
    \ test_randomized() {\n    std::uint64_t state = 49979687ULL;\n    auto random\
    \ = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n    \
    \    return state;\n    };\n\n    std::vector<std::pair<Deque, std::deque<int>>>\
    \ versions;\n    versions.emplace_back();\n    for (int step = 0; step < 10000;\
    \ step++) {\n        int version = int(random() % versions.size());\n        const\
    \ Deque& current = versions[version].first;\n        const std::deque<int>& expected\
    \ = versions[version].second;\n        assert_ends(current, expected);\n\n   \
    \     Deque next = current;\n        std::deque<int> next_expected = expected;\n\
    \        int operation = expected.empty() ? int(random() % 2) : int(random() %\
    \ 4);\n        if (operation == 0) {\n            int value = int(random() % 1000000);\n\
    \            next = current.push_front(value);\n            next_expected.push_front(value);\n\
    \        } else if (operation == 1) {\n            int value = int(random() %\
    \ 1000000);\n            next = current.push_back(value);\n            next_expected.push_back(value);\n\
    \        } else if (operation == 2) {\n            next = current.pop_front();\n\
    \            next_expected.pop_front();\n        } else {\n            next =\
    \ current.pop_back();\n            next_expected.pop_back();\n        }\n\n  \
    \      assert_ends(current, expected);\n        assert_ends(next, next_expected);\n\
    \        if (step % 127 == 0) assert_all(next, next_expected);\n        versions.emplace_back(std::move(next),\
    \ std::move(next_expected));\n    }\n}\n\nvoid test_adversarial() {\n    Deque\
    \ deque;\n    std::deque<int> expected;\n    for (int value = 0; value < 50000;\
    \ value++) {\n        if (value % 2 == 0) {\n            deque = deque.push_front(value);\n\
    \            expected.push_front(value);\n        } else {\n            deque\
    \ = deque.push_back(value);\n            expected.push_back(value);\n        }\n\
    \        assert_ends(deque, expected);\n    }\n    for (int step = 0; step < 50000;\
    \ step++) {\n        if (step % 2 == 0) {\n            deque = deque.pop_back();\n\
    \            expected.pop_back();\n        } else {\n            deque = deque.pop_front();\n\
    \            expected.pop_front();\n        }\n        assert_ends(deque, expected);\n\
    \    }\n    assert(deque.empty());\n\n    Deque one_sided;\n    for (int value\
    \ = 0; value < 50000; value++) {\n        one_sided = one_sided.push_front(value);\n\
    \    }\n    for (int value = 0; value < 50000; value++) {\n        assert(one_sided.back()\
    \ == value);\n        one_sided = one_sided.pop_back();\n    }\n    assert(one_sided.empty());\n\
    \n    Deque stable = Deque().push_back(4);\n    const int& reference = stable.front();\n\
    \    Deque growing = stable;\n    for (int value = 5; value <= 10000; value++)\
    \ {\n        growing = growing.push_front(value).push_back(-value);\n    }\n \
    \   assert(reference == 4);\n    assert(growing.front() == 10000);\n    assert(growing.back()\
    \ == -10000);\n    assert(stable.front() == 4);\n    assert(growing.clear().empty());\n\
    \n    m1une::ds::PersistentDeque<std::unique_ptr<int>> move_only;\n    auto first\
    \ = move_only.push_front(std::make_unique<int>(7));\n    auto second = first.push_back(std::make_unique<int>(11));\n\
    \    auto branch = first.push_front(std::make_unique<int>(3));\n    assert(*first.front()\
    \ == 7);\n    assert(*second.back() == 11);\n    assert(*second.pop_front().front()\
    \ == 11);\n    assert(*branch.front() == 3);\n    assert(*branch.back() == 7);\n\
    }\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n   \
    \ test_adversarial();\n\n    int query_count = 0;\n    fast_input >> query_count;\n\
    \    Deque empty;\n    std::vector<Deque> versions(query_count + 1, empty);\n\
    \    for (int query = 0; query < query_count; query++) {\n        int type = 0,\
    \ base = 0;\n        fast_input >> type >> base;\n        const Deque& source\
    \ = versions[base + 1];\n        if (type == 0) {\n            int value = 0;\n\
    \            fast_input >> value;\n            versions[query + 1] = source.push_back(value);\n\
    \        } else {\n            fast_output << source.front() << '\\n';\n     \
    \       versions[query + 1] = source.pop_front();\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\n\n\
    #include \"../../../ds/deque/persistent_deque.hpp\"\n#include \"../../../utilities/fast_io.hpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <deque>\n#include <memory>\n\
    #include <utility>\n#include <vector>\n\nnamespace {\n\nusing Deque = m1une::ds::PersistentDeque<int>;\n\
    \nvoid assert_ends(const Deque& actual, const std::deque<int>& expected) {\n \
    \   assert(actual.size() == int(expected.size()));\n    assert(actual.empty()\
    \ == expected.empty());\n    if (expected.empty()) return;\n    assert(actual.front()\
    \ == expected.front());\n    assert(actual.back() == expected.back());\n}\n\n\
    void assert_all(Deque actual, std::deque<int> expected) {\n    assert_ends(actual,\
    \ expected);\n    while (!expected.empty()) {\n        assert(actual.front() ==\
    \ expected.front());\n        actual = actual.pop_front();\n        expected.pop_front();\n\
    \    }\n    assert(actual.empty());\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 49979687ULL;\n    auto random = [&]() {\n        state ^= state << 7;\n\
    \        state ^= state >> 9;\n        return state;\n    };\n\n    std::vector<std::pair<Deque,\
    \ std::deque<int>>> versions;\n    versions.emplace_back();\n    for (int step\
    \ = 0; step < 10000; step++) {\n        int version = int(random() % versions.size());\n\
    \        const Deque& current = versions[version].first;\n        const std::deque<int>&\
    \ expected = versions[version].second;\n        assert_ends(current, expected);\n\
    \n        Deque next = current;\n        std::deque<int> next_expected = expected;\n\
    \        int operation = expected.empty() ? int(random() % 2) : int(random() %\
    \ 4);\n        if (operation == 0) {\n            int value = int(random() % 1000000);\n\
    \            next = current.push_front(value);\n            next_expected.push_front(value);\n\
    \        } else if (operation == 1) {\n            int value = int(random() %\
    \ 1000000);\n            next = current.push_back(value);\n            next_expected.push_back(value);\n\
    \        } else if (operation == 2) {\n            next = current.pop_front();\n\
    \            next_expected.pop_front();\n        } else {\n            next =\
    \ current.pop_back();\n            next_expected.pop_back();\n        }\n\n  \
    \      assert_ends(current, expected);\n        assert_ends(next, next_expected);\n\
    \        if (step % 127 == 0) assert_all(next, next_expected);\n        versions.emplace_back(std::move(next),\
    \ std::move(next_expected));\n    }\n}\n\nvoid test_adversarial() {\n    Deque\
    \ deque;\n    std::deque<int> expected;\n    for (int value = 0; value < 50000;\
    \ value++) {\n        if (value % 2 == 0) {\n            deque = deque.push_front(value);\n\
    \            expected.push_front(value);\n        } else {\n            deque\
    \ = deque.push_back(value);\n            expected.push_back(value);\n        }\n\
    \        assert_ends(deque, expected);\n    }\n    for (int step = 0; step < 50000;\
    \ step++) {\n        if (step % 2 == 0) {\n            deque = deque.pop_back();\n\
    \            expected.pop_back();\n        } else {\n            deque = deque.pop_front();\n\
    \            expected.pop_front();\n        }\n        assert_ends(deque, expected);\n\
    \    }\n    assert(deque.empty());\n\n    Deque one_sided;\n    for (int value\
    \ = 0; value < 50000; value++) {\n        one_sided = one_sided.push_front(value);\n\
    \    }\n    for (int value = 0; value < 50000; value++) {\n        assert(one_sided.back()\
    \ == value);\n        one_sided = one_sided.pop_back();\n    }\n    assert(one_sided.empty());\n\
    \n    Deque stable = Deque().push_back(4);\n    const int& reference = stable.front();\n\
    \    Deque growing = stable;\n    for (int value = 5; value <= 10000; value++)\
    \ {\n        growing = growing.push_front(value).push_back(-value);\n    }\n \
    \   assert(reference == 4);\n    assert(growing.front() == 10000);\n    assert(growing.back()\
    \ == -10000);\n    assert(stable.front() == 4);\n    assert(growing.clear().empty());\n\
    \n    m1une::ds::PersistentDeque<std::unique_ptr<int>> move_only;\n    auto first\
    \ = move_only.push_front(std::make_unique<int>(7));\n    auto second = first.push_back(std::make_unique<int>(11));\n\
    \    auto branch = first.push_front(std::make_unique<int>(3));\n    assert(*first.front()\
    \ == 7);\n    assert(*second.back() == 11);\n    assert(*second.pop_front().front()\
    \ == 11);\n    assert(*branch.front() == 3);\n    assert(*branch.back() == 7);\n\
    }\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n   \
    \ test_adversarial();\n\n    int query_count = 0;\n    fast_input >> query_count;\n\
    \    Deque empty;\n    std::vector<Deque> versions(query_count + 1, empty);\n\
    \    for (int query = 0; query < query_count; query++) {\n        int type = 0,\
    \ base = 0;\n        fast_input >> type >> base;\n        const Deque& source\
    \ = versions[base + 1];\n        if (type == 0) {\n            int value = 0;\n\
    \            fast_input >> value;\n            versions[query + 1] = source.push_back(value);\n\
    \        } else {\n            fast_output << source.front() << '\\n';\n     \
    \       versions[query + 1] = source.pop_front();\n        }\n    }\n}\n"
  dependsOn:
  - ds/deque/persistent_deque.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/deque/persistent_deque.test.cpp
  requiredBy: []
  timestamp: '2026-08-26 23:16:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/deque/persistent_deque.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/deque/persistent_deque.test.cpp
- /verify/verify/ds/deque/persistent_deque.test.cpp.html
title: verify/ds/deque/persistent_deque.test.cpp
---
