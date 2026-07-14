#ifndef M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP
#define M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP 1

#include <cassert>
#include <deque>
#include <memory>
#include <utility>

namespace m1une {
namespace ds {

// Purely persistent FIFO queue with worst-case O(1) operations.
template <class T>
struct PersistentQueue {
   private:
    struct Link {
        int value_index;
        int next;

        Link(int index, int next_link) : value_index(index), next(next_link) {}
    };

    struct Pool {
        std::deque<T> values;
        std::deque<Link> links;
    };

    enum class RotationPhase {
        idle,
        reversing,
        appending,
        done,
    };

    struct RotationState {
        RotationPhase phase = RotationPhase::idle;
        int valid_count = 0;
        int remaining_front = -1;
        int reversed_front = -1;
        int remaining_rear = -1;
        int reversed_rear = -1;
    };

    int _front_size;
    int _front;
    RotationState _rotation;
    int _rear_size;
    int _rear;
    int _back_value;
    std::shared_ptr<Pool> _pool;

    PersistentQueue(
        int front_size,
        int front,
        RotationState rotation,
        int rear_size,
        int rear,
        int back_value,
        std::shared_ptr<Pool> pool
    )
        : _front_size(front_size),
          _front(front),
          _rotation(rotation),
          _rear_size(rear_size),
          _rear(rear),
          _back_value(back_value),
          _pool(std::move(pool)) {}

    int next_link(int link) const {
        assert(link != -1);
        return _pool->links[link].next;
    }

    int link_value(int link) const {
        assert(link != -1);
        return _pool->links[link].value_index;
    }

    int make_link(int value_index, int next) const {
        _pool->links.emplace_back(value_index, next);
        return int(_pool->links.size()) - 1;
    }

    int store_value(T value) const {
        _pool->values.emplace_back(std::move(value));
        return int(_pool->values.size()) - 1;
    }

    RotationState execute(RotationState state) const {
        if (state.phase == RotationPhase::reversing) {
            assert(state.remaining_rear != -1);
            if (state.remaining_front != -1) {
                state.reversed_front = make_link(
                    link_value(state.remaining_front),
                    state.reversed_front
                );
                state.remaining_front = next_link(state.remaining_front);
                state.reversed_rear = make_link(
                    link_value(state.remaining_rear),
                    state.reversed_rear
                );
                state.remaining_rear = next_link(state.remaining_rear);
                state.valid_count++;
            } else {
                assert(next_link(state.remaining_rear) == -1);
                state.reversed_rear = make_link(
                    link_value(state.remaining_rear),
                    state.reversed_rear
                );
                state.remaining_rear = -1;
                state.phase = RotationPhase::appending;
            }
        } else if (state.phase == RotationPhase::appending) {
            assert(state.valid_count >= 0);
            if (state.valid_count == 0) {
                state.phase = RotationPhase::done;
            } else {
                assert(state.reversed_front != -1);
                state.reversed_rear = make_link(
                    link_value(state.reversed_front),
                    state.reversed_rear
                );
                state.reversed_front = next_link(state.reversed_front);
                state.valid_count--;
            }
        }
        return state;
    }

    RotationState invalidate(RotationState state) const {
        if (state.phase == RotationPhase::reversing) {
            state.valid_count--;
        } else if (state.phase == RotationPhase::appending) {
            if (state.valid_count == 0) {
                assert(state.reversed_rear != -1);
                state.reversed_rear = next_link(state.reversed_rear);
                state.phase = RotationPhase::done;
            } else {
                state.valid_count--;
            }
        }
        return state;
    }

    PersistentQueue execute_twice(
        int front_size,
        int front,
        RotationState rotation,
        int rear_size,
        int rear,
        int back_value
    ) const {
        rotation = execute(std::move(rotation));
        rotation = execute(std::move(rotation));
        if (rotation.phase == RotationPhase::done) {
            front = rotation.reversed_rear;
            rotation = RotationState();
        }
        return PersistentQueue(
            front_size,
            front,
            rotation,
            rear_size,
            rear,
            back_value,
            _pool
        );
    }

    PersistentQueue check(
        int front_size,
        int front,
        RotationState rotation,
        int rear_size,
        int rear,
        int back_value
    ) const {
        if (rear_size <= front_size) {
            return execute_twice(
                front_size,
                front,
                rotation,
                rear_size,
                rear,
                back_value
            );
        }

        RotationState next_rotation;
        next_rotation.phase = RotationPhase::reversing;
        next_rotation.remaining_front = front;
        next_rotation.remaining_rear = rear;
        return execute_twice(
            front_size + rear_size,
            front,
            next_rotation,
            0,
            -1,
            back_value
        );
    }

   public:
    PersistentQueue()
        : _front_size(0),
          _front(-1),
          _rear_size(0),
          _rear(-1),
          _back_value(-1),
          _pool(std::make_shared<Pool>()) {}

    int size() const {
        return _front_size + _rear_size;
    }

    bool empty() const {
        return size() == 0;
    }

    const T& front() const {
        assert(!empty() && _front != -1);
        return _pool->values[link_value(_front)];
    }

    const T& back() const {
        assert(!empty() && _back_value != -1);
        return _pool->values[_back_value];
    }

    PersistentQueue push(T value) const {
        int value_index = store_value(std::move(value));
        int rear = make_link(value_index, _rear);
        return check(
            _front_size,
            _front,
            _rotation,
            _rear_size + 1,
            rear,
            value_index
        );
    }

    PersistentQueue push_back(T value) const {
        return push(std::move(value));
    }

    PersistentQueue pop() const {
        assert(!empty() && _front != -1);
        int back_value = size() == 1 ? -1 : _back_value;
        return check(
            _front_size - 1,
            next_link(_front),
            invalidate(_rotation),
            _rear_size,
            _rear,
            back_value
        );
    }

    PersistentQueue pop_front() const {
        return pop();
    }

    PersistentQueue clear() const {
        return PersistentQueue(
            0,
            -1,
            RotationState(),
            0,
            -1,
            -1,
            _pool
        );
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP
