#ifndef M1UNE_DS_DEQUE_PERSISTENT_DEQUE_HPP
#define M1UNE_DS_DEQUE_PERSISTENT_DEQUE_HPP 1

#include <cassert>
#include <cstdint>
#include <deque>
#include <memory>
#include <utility>

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
        std::deque<T> values;
        std::deque<StreamNode> streams;
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
          _pool(std::move(pool)) {}

    template <class... Args>
    int store_value(Args&&... args) const {
        _pool->values.emplace_back(std::forward<Args>(args)...);
        return int(_pool->values.size()) - 1;
    }

    int make_stream(
        StreamKind kind,
        int first,
        int second,
        int third = -1
    ) const {
        _pool->streams.emplace_back(kind, first, second, third);
        return int(_pool->streams.size()) - 1;
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
        StreamNode& node = _pool->streams[stream];
        node.kind = StreamKind::cons;
        node.first = value_index;
        node.second = tail;
        node.third = -1;
    }

    int stream_head(int stream) const {
        assert(stream != -1);
        force(stream);
        return _pool->streams[stream].first;
    }

    int stream_tail(int stream) const {
        assert(stream != -1);
        force(stream);
        return _pool->streams[stream].second;
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
        StreamNode node = _pool->streams[stream];
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

    int size() const {
        return _front_size + _rear_size;
    }

    bool empty() const {
        return size() == 0;
    }

    const T& front() const {
        assert(!empty());
        int stream = _front == -1 ? _rear : _front;
        return _pool->values[stream_head(stream)];
    }

    const T& back() const {
        assert(!empty());
        int stream = _rear == -1 ? _front : _rear;
        return _pool->values[stream_head(stream)];
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
