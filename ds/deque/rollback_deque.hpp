#ifndef M1UNE_DS_DEQUE_ROLLBACK_DEQUE_HPP
#define M1UNE_DS_DEQUE_ROLLBACK_DEQUE_HPP 1

#include <utility>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_deque.hpp"

namespace m1une {
namespace ds {

template <class T>
struct RollbackDeque : detail::RollbackPersistentBase<PersistentDeque<T>> {
   private:
    using Persistent = PersistentDeque<T>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void push_front(T value) {
        Base::commit(Base::persistent().push_front(std::move(value)));
    }

    template <class... Args>
    void emplace_front(Args&&... args) {
        Base::commit(Base::persistent().emplace_front(std::forward<Args>(args)...));
    }

    void push_back(T value) {
        Base::commit(Base::persistent().push_back(std::move(value)));
    }

    template <class... Args>
    void emplace_back(Args&&... args) {
        Base::commit(Base::persistent().emplace_back(std::forward<Args>(args)...));
    }

    void pop_front() {
        Base::commit(Base::persistent().pop_front());
    }

    void pop_back() {
        Base::commit(Base::persistent().pop_back());
    }

    void clear() {
        Base::commit(Base::persistent().clear());
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_DEQUE_ROLLBACK_DEQUE_HPP
