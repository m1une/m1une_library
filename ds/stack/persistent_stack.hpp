#ifndef M1UNE_DS_STACK_PERSISTENT_STACK_HPP
#define M1UNE_DS_STACK_PERSISTENT_STACK_HPP 1

#include <cassert>
#include <cstddef>
#include <deque>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// Purely persistent LIFO stack with O(1) operations.
template <class T>
struct PersistentStack {
   private:
    struct Node {
        T value;
        int next;

        template <class... Args>
        Node(int next_node, Args&&... args)
            : value(std::forward<Args>(args)...), next(next_node) {}
    };

    struct Pool {
        std::deque<std::optional<Node>> nodes;
        std::vector<int> references;
        std::vector<int> next_free;
        int first_free = -1;
        std::size_t live_nodes = 0;

        template <class... Args>
        int emplace(int next, Args&&... args) {
            int result;
            if (first_free == -1) {
                result = int(nodes.size());
                nodes.emplace_back(std::in_place, next, std::forward<Args>(args)...);
                references.push_back(0);
                next_free.push_back(-1);
            } else {
                result = first_free;
                first_free = next_free[result];
                nodes[result].emplace(next, std::forward<Args>(args)...);
                references[result] = 0;
            }
            retain(next);
            ++live_nodes;
            return result;
        }

        Node& operator[](int node) { return *nodes[node]; }
        const Node& operator[](int node) const { return *nodes[node]; }

        void retain(int node) {
            if (node != -1) ++references[node];
        }

        void release(int node) {
            while (node != -1) {
                assert(nodes[node].has_value() && references[node] > 0);
                if (--references[node] != 0) return;
                int next = nodes[node]->next;
                nodes[node].reset();
                next_free[node] = first_free;
                first_free = node;
                --live_nodes;
                node = next;
            }
        }
    };

    int _size;
    int _top;
    std::shared_ptr<Pool> _pool;

    PersistentStack(
        int stack_size,
        int top,
        std::shared_ptr<Pool> pool
    )
        : _size(stack_size), _top(top), _pool(std::move(pool)) {
        _pool->retain(_top);
    }

   public:
    PersistentStack()
        : _size(0),
          _top(-1),
          _pool(std::make_shared<Pool>()) {}

    PersistentStack(const PersistentStack& other)
        : _size(other._size), _top(other._top), _pool(other._pool) {
        if (_pool) _pool->retain(_top);
    }

    PersistentStack(PersistentStack&& other) noexcept
        : _size(other._size), _top(other._top), _pool(std::move(other._pool)) {
        other._size = 0;
        other._top = -1;
    }

    PersistentStack& operator=(const PersistentStack& other) {
        if (this == &other) return *this;
        if (other._pool) other._pool->retain(other._top);
        if (_pool) _pool->release(_top);
        _size = other._size;
        _top = other._top;
        _pool = other._pool;
        return *this;
    }

    PersistentStack& operator=(PersistentStack&& other) noexcept {
        if (this == &other) return *this;
        if (_pool) _pool->release(_top);
        _size = other._size;
        _top = other._top;
        _pool = std::move(other._pool);
        other._size = 0;
        other._top = -1;
        return *this;
    }

    ~PersistentStack() {
        if (_pool) _pool->release(_top);
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    void release() {
        if (_pool) _pool->release(_top);
        _size = 0;
        _top = -1;
        _pool = std::make_shared<Pool>();
    }

    std::size_t node_count() const { return _pool ? _pool->live_nodes : 0; }

    const T& top() const {
        assert(!empty() && _top != -1);
        return (*_pool)[_top].value;
    }

    PersistentStack push(T value) const {
        return emplace(std::move(value));
    }

    template <class... Args>
    PersistentStack emplace(Args&&... args) const {
        int top = _pool->emplace(_top, std::forward<Args>(args)...);
        return PersistentStack(
            _size + 1,
            top,
            _pool
        );
    }

    PersistentStack pop() const {
        assert(!empty() && _top != -1);
        return PersistentStack(_size - 1, (*_pool)[_top].next, _pool);
    }

    PersistentStack clear() const {
        return PersistentStack(0, -1, _pool);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_STACK_PERSISTENT_STACK_HPP
