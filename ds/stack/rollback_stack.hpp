#ifndef M1UNE_DS_STACK_ROLLBACK_STACK_HPP
#define M1UNE_DS_STACK_ROLLBACK_STACK_HPP 1

#include <utility>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_stack.hpp"

namespace m1une {
namespace ds {

template <class T>
struct RollbackStack : detail::RollbackPersistentBase<PersistentStack<T>> {
   private:
    using Persistent = PersistentStack<T>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void push(T value) {
        Base::commit(Base::persistent().push(std::move(value)));
    }

    template <class... Args>
    void emplace(Args&&... args) {
        Base::commit(Base::persistent().emplace(std::forward<Args>(args)...));
    }

    void pop() {
        Base::commit(Base::persistent().pop());
    }

    void clear() {
        Base::commit(Base::persistent().clear());
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_STACK_ROLLBACK_STACK_HPP
