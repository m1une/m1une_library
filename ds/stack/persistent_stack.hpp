#ifndef M1UNE_DS_STACK_PERSISTENT_STACK_HPP
#define M1UNE_DS_STACK_PERSISTENT_STACK_HPP 1

#include <cassert>
#include <deque>
#include <memory>
#include <utility>

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

    int _size;
    int _top;
    std::shared_ptr<std::deque<Node>> _pool;

    PersistentStack(
        int stack_size,
        int top,
        std::shared_ptr<std::deque<Node>> pool
    )
        : _size(stack_size), _top(top), _pool(std::move(pool)) {}

   public:
    PersistentStack()
        : _size(0),
          _top(-1),
          _pool(std::make_shared<std::deque<Node>>()) {}

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    const T& top() const {
        assert(!empty() && _top != -1);
        return (*_pool)[_top].value;
    }

    PersistentStack push(T value) const {
        return emplace(std::move(value));
    }

    template <class... Args>
    PersistentStack emplace(Args&&... args) const {
        _pool->emplace_back(_top, std::forward<Args>(args)...);
        return PersistentStack(
            _size + 1,
            int(_pool->size()) - 1,
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
