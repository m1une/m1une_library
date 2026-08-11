#ifndef M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP
#define M1UNE_DS_QUEUE_PERSISTENT_QUEUE_HPP 1

#include <cassert>
#include <cstddef>
#include <deque>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

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
        std::deque<std::optional<T>> values;
        std::deque<std::optional<Link>> links;
        std::vector<int> value_references, link_references;
        std::vector<int> next_free_value, next_free_link;
        std::vector<int> unowned_values, unowned_links;
        int first_free_value = -1;
        int first_free_link = -1;
        std::size_t live_values = 0;
        std::size_t live_links = 0;

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

        void retain_link(int link) {
            if (link != -1) ++link_references[link];
        }

        void release_zero_link(int link) {
            while (link != -1) {
                assert(links[link].has_value() && link_references[link] == 0);
                int value = links[link]->value_index;
                int next = links[link]->next;
                links[link].reset();
                next_free_link[link] = first_free_link;
                first_free_link = link;
                --live_links;
                release_value(value);
                if (next == -1 || --link_references[next] != 0) return;
                link = next;
            }
        }

        void release_link(int link) {
            if (link == -1) return;
            assert(links[link].has_value() && link_references[link] > 0);
            if (--link_references[link] == 0) release_zero_link(link);
        }

        int store_value(T value) {
            int result;
            if (first_free_value == -1) {
                result = int(values.size());
                values.emplace_back(std::in_place, std::move(value));
                value_references.push_back(0);
                next_free_value.push_back(-1);
            } else {
                result = first_free_value;
                first_free_value = next_free_value[result];
                values[result].emplace(std::move(value));
                value_references[result] = 0;
            }
            unowned_values.push_back(result);
            ++live_values;
            return result;
        }

        int make_link(int value, int next) {
            int result;
            if (first_free_link == -1) {
                result = int(links.size());
                links.emplace_back(std::in_place, value, next);
                link_references.push_back(0);
                next_free_link.push_back(-1);
            } else {
                result = first_free_link;
                first_free_link = next_free_link[result];
                links[result].emplace(value, next);
                link_references[result] = 0;
            }
            retain_value(value);
            retain_link(next);
            unowned_links.push_back(result);
            ++live_links;
            return result;
        }

        void discard_unreferenced() {
            while (!unowned_links.empty()) {
                int link = unowned_links.back();
                unowned_links.pop_back();
                if (links[link].has_value() && link_references[link] == 0) release_zero_link(link);
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

        std::size_t size() const { return live_values + live_links; }
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
          _pool(std::move(pool)) {
        retain_state();
        _pool->discard_unreferenced();
    }

    void retain_state() const {
        _pool->retain_link(_front);
        _pool->retain_link(_rotation.remaining_front);
        _pool->retain_link(_rotation.reversed_front);
        _pool->retain_link(_rotation.remaining_rear);
        _pool->retain_link(_rotation.reversed_rear);
        _pool->retain_link(_rear);
        _pool->retain_value(_back_value);
    }

    void release_state() const {
        _pool->release_link(_front);
        _pool->release_link(_rotation.remaining_front);
        _pool->release_link(_rotation.reversed_front);
        _pool->release_link(_rotation.remaining_rear);
        _pool->release_link(_rotation.reversed_rear);
        _pool->release_link(_rear);
        _pool->release_value(_back_value);
    }

    int next_link(int link) const {
        assert(link != -1);
        return (*_pool->links[link]).next;
    }

    int link_value(int link) const {
        assert(link != -1);
        return (*_pool->links[link]).value_index;
    }

    int make_link(int value_index, int next) const {
        return _pool->make_link(value_index, next);
    }

    int store_value(T value) const {
        return _pool->store_value(std::move(value));
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

    PersistentQueue(const PersistentQueue& other)
        : _front_size(other._front_size),
          _front(other._front),
          _rotation(other._rotation),
          _rear_size(other._rear_size),
          _rear(other._rear),
          _back_value(other._back_value),
          _pool(other._pool) {
        if (_pool) retain_state();
    }

    PersistentQueue(PersistentQueue&& other) noexcept
        : _front_size(other._front_size),
          _front(other._front),
          _rotation(other._rotation),
          _rear_size(other._rear_size),
          _rear(other._rear),
          _back_value(other._back_value),
          _pool(std::move(other._pool)) {
        other._front_size = other._rear_size = 0;
        other._front = other._rear = other._back_value = -1;
        other._rotation = RotationState();
    }

    PersistentQueue& operator=(const PersistentQueue& other) {
        if (this == &other) return *this;
        if (other._pool) other.retain_state();
        if (_pool) release_state();
        _front_size = other._front_size;
        _front = other._front;
        _rotation = other._rotation;
        _rear_size = other._rear_size;
        _rear = other._rear;
        _back_value = other._back_value;
        _pool = other._pool;
        return *this;
    }

    PersistentQueue& operator=(PersistentQueue&& other) noexcept {
        if (this == &other) return *this;
        if (_pool) release_state();
        _front_size = other._front_size;
        _front = other._front;
        _rotation = other._rotation;
        _rear_size = other._rear_size;
        _rear = other._rear;
        _back_value = other._back_value;
        _pool = std::move(other._pool);
        other._front_size = other._rear_size = 0;
        other._front = other._rear = other._back_value = -1;
        other._rotation = RotationState();
        return *this;
    }

    ~PersistentQueue() {
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
        _front = _rear = _back_value = -1;
        _rotation = RotationState();
        _pool = std::make_shared<Pool>();
    }

    std::size_t node_count() const { return _pool ? _pool->size() : 0; }

    const T& front() const {
        assert(!empty() && _front != -1);
        return *_pool->values[link_value(_front)];
    }

    const T& back() const {
        assert(!empty() && _back_value != -1);
        return *_pool->values[_back_value];
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
