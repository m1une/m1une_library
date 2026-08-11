#ifndef M1UNE_DS_QUEUE_ROLLBACK_QUEUE_HPP
#define M1UNE_DS_QUEUE_ROLLBACK_QUEUE_HPP 1

#include <utility>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_queue.hpp"

namespace m1une {
namespace ds {

template <class T>
struct RollbackQueue : detail::RollbackPersistentBase<PersistentQueue<T>> {
   private:
    using Persistent = PersistentQueue<T>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void push(T value) {
        Base::commit(Base::persistent().push(std::move(value)));
    }

    void push_back(T value) {
        push(std::move(value));
    }

    void pop() {
        Base::commit(Base::persistent().pop());
    }

    void pop_front() {
        pop();
    }

    void clear() {
        Base::commit(Base::persistent().clear());
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_QUEUE_ROLLBACK_QUEUE_HPP
