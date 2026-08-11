#ifndef M1UNE_DS_DEQUE_PERSISTENT_DEQUE_HPP
#define M1UNE_DS_DEQUE_PERSISTENT_DEQUE_HPP 1

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// Okasaki's purely persistent real-time deque.
template <class T>
struct PersistentDeque {
   private:
    static constexpr int balance_factor = 2;

    enum class StreamKind : std::uint8_t {
        cons,
        take,
        rotate_drop,
        rotate_reverse,
    };

    // The three integer fields contain either an evaluated cons cell or the
    // arguments of one incremental stream operation.
    struct StreamNode {
        mutable StreamKind kind;
        mutable int first;
        mutable int second;
        mutable int third;

        StreamNode(
            StreamKind node_kind,
            int first_argument,
            int second_argument,
            int third_argument = -1
        )
            : kind(node_kind),
              first(first_argument),
              second(second_argument),
              third(third_argument) {}
    };

    struct Pool {
        std::deque<std::optional<T>> values;
        std::deque<std::optional<StreamNode>> streams;
        std::vector<int> value_references, stream_references;
        std::vector<int> next_free_value, next_free_stream;
        std::vector<int> unowned_values, unowned_streams;
        int first_free_value = -1;
        int first_free_stream = -1;
        std::size_t live_values = 0;
        std::size_t live_streams = 0;

        void retain_value(int value) {
            if (value != -1) ++value_references[value];
        }

        void release_value(int value) {
            if (value == -1) return;
            assert(values[value].has_value() && value_references[value] > 0);
            if (--value_references[value] != 0) return;
            values[value].reset();
            next_free_value[value] = first_free_value;
            first_free_value = value;
            --live_values;
        }

        void retain_stream(int stream) {
            if (stream != -1) ++stream_references[stream];
        }

        void retain_dependencies(const StreamNode& node) {
            if (node.kind == StreamKind::cons) {
                retain_value(node.first);
                retain_stream(node.second);
            } else if (node.kind == StreamKind::take) {
                retain_stream(node.first);
            } else if (node.kind == StreamKind::rotate_drop) {
                retain_stream(node.first);
                retain_stream(node.third);
            } else {
                retain_stream(node.first);
                retain_stream(node.second);
                retain_stream(node.third);
            }
        }

        void release_zero_stream(int stream) {
            std::vector<int> pending = {stream};
            while (!pending.empty()) {
                int current = pending.back();
                pending.pop_back();
                assert(streams[current].has_value() && stream_references[current] == 0);
                StreamNode node = *streams[current];
                streams[current].reset();
                next_free_stream[current] = first_free_stream;
                first_free_stream = current;
                --live_streams;

                auto release_child = [&](int child) {
                    if (child != -1 && --stream_references[child] == 0) pending.push_back(child);
                };
                if (node.kind == StreamKind::cons) {
                    release_value(node.first);
                    release_child(node.second);
                } else if (node.kind == StreamKind::take) {
                    release_child(node.first);
                } else if (node.kind == StreamKind::rotate_drop) {
                    release_child(node.first);
                    release_child(node.third);
                } else {
                    release_child(node.first);
                    release_child(node.second);
                    release_child(node.third);
                }
            }
        }

        void release_stream(int stream) {
            if (stream == -1) return;
            assert(streams[stream].has_value() && stream_references[stream] > 0);
            if (--stream_references[stream] == 0) release_zero_stream(stream);
        }

        template <class... Args>
        int store_value(Args&&... args) {
            int result;
            if (first_free_value == -1) {
                result = int(values.size());
                values.emplace_back(std::in_place, std::forward<Args>(args)...);
                value_references.push_back(0);
                next_free_value.push_back(-1);
            } else {
                result = first_free_value;
                first_free_value = next_free_value[result];
                values[result].emplace(std::forward<Args>(args)...);
                value_references[result] = 0;
            }
            unowned_values.push_back(result);
            ++live_values;
            return result;
        }

        int make_stream(StreamKind kind, int first, int second, int third) {
            int result;
            if (first_free_stream == -1) {
                result = int(streams.size());
                streams.emplace_back(std::in_place, kind, first, second, third);
                stream_references.push_back(0);
                next_free_stream.push_back(-1);
            } else {
                result = first_free_stream;
                first_free_stream = next_free_stream[result];
                streams[result].emplace(kind, first, second, third);
                stream_references[result] = 0;
            }
            retain_dependencies(*streams[result]);
            unowned_streams.push_back(result);
            ++live_streams;
            return result;
        }

        void set_cons(int stream, int value, int tail) {
            retain_value(value);
            retain_stream(tail);
            StreamNode old = *streams[stream];
            if (old.kind == StreamKind::take) {
                release_stream(old.first);
            } else if (old.kind == StreamKind::rotate_drop) {
                release_stream(old.first);
                release_stream(old.third);
            } else if (old.kind == StreamKind::rotate_reverse) {
                release_stream(old.first);
                release_stream(old.second);
                release_stream(old.third);
            } else {
                release_value(old.first);
                release_stream(old.second);
            }
            StreamNode& node = *streams[stream];
            node.kind = StreamKind::cons;
            node.first = value;
            node.second = tail;
            node.third = -1;
        }

        void discard_unreferenced() {
            while (!unowned_streams.empty()) {
                int stream = unowned_streams.back();
                unowned_streams.pop_back();
                if (streams[stream].has_value() && stream_references[stream] == 0) release_zero_stream(stream);
            }
            while (!unowned_values.empty()) {
                int value = unowned_values.back();
                unowned_values.pop_back();
                if (values[value].has_value() && value_references[value] == 0) {
                    values[value].reset();
                    next_free_value[value] = first_free_value;
                    first_free_value = value;
                    --live_values;
                }
            }
        }

        std::size_t size() const { return live_values + live_streams; }
    };

    int _front_size;
    int _front;
    int _front_schedule;
    int _rear_size;
    int _rear;
    int _rear_schedule;
    std::shared_ptr<Pool> _pool;

    PersistentDeque(
        int front_size,
        int front,
        int front_schedule,
        int rear_size,
        int rear,
        int rear_schedule,
        std::shared_ptr<Pool> pool
    )
        : _front_size(front_size),
          _front(front),
          _front_schedule(front_schedule),
          _rear_size(rear_size),
          _rear(rear),
          _rear_schedule(rear_schedule),
          _pool(std::move(pool)) {
        retain_state();
        _pool->discard_unreferenced();
    }

    void retain_state() const {
        _pool->retain_stream(_front);
        _pool->retain_stream(_front_schedule);
        _pool->retain_stream(_rear);
        _pool->retain_stream(_rear_schedule);
    }

    void release_state() const {
        _pool->release_stream(_front);
        _pool->release_stream(_front_schedule);
        _pool->release_stream(_rear);
        _pool->release_stream(_rear_schedule);
    }

    template <class... Args>
    int store_value(Args&&... args) const {
        return _pool->store_value(std::forward<Args>(args)...);
    }

    int make_stream(
        StreamKind kind,
        int first,
        int second,
        int third = -1
    ) const {
        return _pool->make_stream(kind, first, second, third);
    }

    int make_cons(int value_index, int tail) const {
        return make_stream(StreamKind::cons, value_index, tail);
    }

    int make_take(int count, int stream) const {
        if (count == 0) return -1;
        assert(count > 0 && stream != -1);
        return make_stream(StreamKind::take, stream, count);
    }

    int make_rotate_drop(int rear, int count, int front) const {
        return make_stream(StreamKind::rotate_drop, rear, count, front);
    }

    int make_rotate_reverse(int rear, int front, int accumulator) const {
        return make_stream(
            StreamKind::rotate_reverse,
            rear,
            front,
            accumulator
        );
    }

    void set_cons(int stream, int value_index, int tail) const {
        _pool->set_cons(stream, value_index, tail);
    }

    int stream_head(int stream) const {
        assert(stream != -1);
        force(stream);
        return (*_pool->streams[stream]).first;
    }

    int stream_tail(int stream) const {
        assert(stream != -1);
        force(stream);
        return (*_pool->streams[stream]).second;
    }

    int drop(int stream, int count) const {
        assert(count >= 0);
        while (count > 0) {
            assert(stream != -1);
            stream = stream_tail(stream);
            count--;
        }
        return stream;
    }

    // Reverses a bounded prefix onto accumulator and returns the unconsumed
    // suffix together with the new accumulator.
    std::pair<int, int> reverse_prefix(
        int stream,
        int count,
        int accumulator
    ) const {
        while (count > 0 && stream != -1) {
            int value_index = stream_head(stream);
            stream = stream_tail(stream);
            accumulator = make_cons(value_index, accumulator);
            count--;
        }
        return {stream, accumulator};
    }

    void force(int stream) const {
        assert(stream != -1);
        StreamNode node = *_pool->streams[stream];
        if (node.kind == StreamKind::cons) return;

        if (node.kind == StreamKind::take) {
            int source = node.first;
            int count = node.second;
            assert(source != -1 && count > 0);
            int value_index = stream_head(source);
            int tail = make_take(count - 1, stream_tail(source));
            set_cons(stream, value_index, tail);
            return;
        }

        if (node.kind == StreamKind::rotate_drop) {
            int rear = node.first;
            int count = node.second;
            int front = node.third;
            if (count < balance_factor || rear == -1) {
                assert(count <= balance_factor || rear != -1);
                int result = make_rotate_reverse(
                    rear,
                    drop(front, count),
                    -1
                );
                set_cons(stream, stream_head(result), stream_tail(result));
                return;
            }
            assert(rear != -1);
            int value_index = stream_head(rear);
            int tail = make_rotate_drop(
                stream_tail(rear),
                count - balance_factor,
                drop(front, balance_factor)
            );
            set_cons(stream, value_index, tail);
            return;
        }

        assert(node.kind == StreamKind::rotate_reverse);
        int rear = node.first;
        int front = node.second;
        int accumulator = node.third;
        if (rear == -1) {
            auto [remaining, result] = reverse_prefix(
                front,
                balance_factor + 1,
                accumulator
            );
            assert(remaining == -1 && result != -1);
            set_cons(stream, stream_head(result), stream_tail(result));
            return;
        }

        int value_index = stream_head(rear);
        auto [remaining, next_accumulator] = reverse_prefix(
            front,
            balance_factor,
            accumulator
        );
        int tail = make_rotate_reverse(
            stream_tail(rear),
            remaining,
            next_accumulator
        );
        set_cons(stream, value_index, tail);
    }

    int execute_once(int schedule) const {
        return schedule == -1 ? -1 : stream_tail(schedule);
    }

    int execute_twice(int schedule) const {
        return execute_once(execute_once(schedule));
    }

    PersistentDeque check(
        int front_size,
        int front,
        int front_schedule,
        int rear_size,
        int rear,
        int rear_schedule
    ) const {
        if (front_size > balance_factor * rear_size + 1) {
            int next_front_size = (front_size + rear_size) / 2;
            int next_rear_size = front_size + rear_size - next_front_size;
            int next_front = make_take(next_front_size, front);
            int next_rear = make_rotate_drop(
                rear,
                next_front_size,
                front
            );
            return PersistentDeque(
                next_front_size,
                next_front,
                next_front,
                next_rear_size,
                next_rear,
                next_rear,
                _pool
            );
        }

        if (rear_size > balance_factor * front_size + 1) {
            int next_front_size = (front_size + rear_size) / 2;
            int next_rear_size = front_size + rear_size - next_front_size;
            int next_front = make_rotate_drop(
                front,
                next_rear_size,
                rear
            );
            int next_rear = make_take(next_rear_size, rear);
            return PersistentDeque(
                next_front_size,
                next_front,
                next_front,
                next_rear_size,
                next_rear,
                next_rear,
                _pool
            );
        }

        return PersistentDeque(
            front_size,
            front,
            front_schedule,
            rear_size,
            rear,
            rear_schedule,
            _pool
        );
    }

   public:
    PersistentDeque()
        : _front_size(0),
          _front(-1),
          _front_schedule(-1),
          _rear_size(0),
          _rear(-1),
          _rear_schedule(-1),
          _pool(std::make_shared<Pool>()) {}

    PersistentDeque(const PersistentDeque& other)
        : _front_size(other._front_size),
          _front(other._front),
          _front_schedule(other._front_schedule),
          _rear_size(other._rear_size),
          _rear(other._rear),
          _rear_schedule(other._rear_schedule),
          _pool(other._pool) {
        if (_pool) retain_state();
    }

    PersistentDeque(PersistentDeque&& other) noexcept
        : _front_size(other._front_size),
          _front(other._front),
          _front_schedule(other._front_schedule),
          _rear_size(other._rear_size),
          _rear(other._rear),
          _rear_schedule(other._rear_schedule),
          _pool(std::move(other._pool)) {
        other._front_size = other._rear_size = 0;
        other._front = other._front_schedule = other._rear = other._rear_schedule = -1;
    }

    PersistentDeque& operator=(const PersistentDeque& other) {
        if (this == &other) return *this;
        if (other._pool) other.retain_state();
        if (_pool) release_state();
        _front_size = other._front_size;
        _front = other._front;
        _front_schedule = other._front_schedule;
        _rear_size = other._rear_size;
        _rear = other._rear;
        _rear_schedule = other._rear_schedule;
        _pool = other._pool;
        return *this;
    }

    PersistentDeque& operator=(PersistentDeque&& other) noexcept {
        if (this == &other) return *this;
        if (_pool) release_state();
        _front_size = other._front_size;
        _front = other._front;
        _front_schedule = other._front_schedule;
        _rear_size = other._rear_size;
        _rear = other._rear;
        _rear_schedule = other._rear_schedule;
        _pool = std::move(other._pool);
        other._front_size = other._rear_size = 0;
        other._front = other._front_schedule = other._rear = other._rear_schedule = -1;
        return *this;
    }

    ~PersistentDeque() {
        if (_pool) release_state();
    }

    int size() const {
        return _front_size + _rear_size;
    }

    bool empty() const {
        return size() == 0;
    }

    void release() {
        if (_pool) release_state();
        _front_size = _rear_size = 0;
        _front = _front_schedule = _rear = _rear_schedule = -1;
        _pool = std::make_shared<Pool>();
    }

    std::size_t node_count() const { return _pool ? _pool->size() : 0; }

    const T& front() const {
        assert(!empty());
        int stream = _front == -1 ? _rear : _front;
        int value = stream_head(stream);
        _pool->discard_unreferenced();
        return *_pool->values[value];
    }

    const T& back() const {
        assert(!empty());
        int stream = _rear == -1 ? _front : _rear;
        int value = stream_head(stream);
        _pool->discard_unreferenced();
        return *_pool->values[value];
    }

    PersistentDeque push_front(T value) const {
        return emplace_front(std::move(value));
    }

    template <class... Args>
    PersistentDeque emplace_front(Args&&... args) const {
        int value_index = store_value(std::forward<Args>(args)...);
        return check(
            _front_size + 1,
            make_cons(value_index, _front),
            execute_once(_front_schedule),
            _rear_size,
            _rear,
            execute_once(_rear_schedule)
        );
    }

    PersistentDeque push_back(T value) const {
        return emplace_back(std::move(value));
    }

    template <class... Args>
    PersistentDeque emplace_back(Args&&... args) const {
        int value_index = store_value(std::forward<Args>(args)...);
        return check(
            _front_size,
            _front,
            execute_once(_front_schedule),
            _rear_size + 1,
            make_cons(value_index, _rear),
            execute_once(_rear_schedule)
        );
    }

    PersistentDeque pop_front() const {
        assert(!empty());
        if (size() == 1) return clear();
        assert(_front != -1);
        return check(
            _front_size - 1,
            stream_tail(_front),
            execute_twice(_front_schedule),
            _rear_size,
            _rear,
            execute_twice(_rear_schedule)
        );
    }

    PersistentDeque pop_back() const {
        assert(!empty());
        if (size() == 1) return clear();
        assert(_rear != -1);
        return check(
            _front_size,
            _front,
            execute_twice(_front_schedule),
            _rear_size - 1,
            stream_tail(_rear),
            execute_twice(_rear_schedule)
        );
    }

    PersistentDeque clear() const {
        return PersistentDeque(0, -1, -1, 0, -1, -1, _pool);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_DEQUE_PERSISTENT_DEQUE_HPP
