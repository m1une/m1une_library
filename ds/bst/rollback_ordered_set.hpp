#ifndef M1UNE_DS_BST_ROLLBACK_ORDERED_SET_HPP
#define M1UNE_DS_BST_ROLLBACK_ORDERED_SET_HPP 1

#include <functional>
#include <utility>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_ordered_set.hpp"

namespace m1une {
namespace ds {

template <class T, class Compare = std::less<T>>
struct RollbackOrderedSet
    : detail::RollbackPersistentBase<PersistentOrderedSet<T, Compare>> {
   private:
    using Persistent = PersistentOrderedSet<T, Compare>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void clear() {
        Base::commit(Base::persistent().clear());
    }

    bool insert(T key) {
        bool inserted = !Base::persistent().contains(key);
        Base::commit(Base::persistent().insert(std::move(key)));
        return inserted;
    }

    bool erase(const T& key) {
        bool erased = Base::persistent().contains(key);
        Base::commit(Base::persistent().erase(key));
        return erased;
    }

    void merge(const RollbackOrderedSet& other) {
        Base::commit(Base::persistent().merge(other.current_version()));
    }

    void merge(const Persistent& other) {
        Base::commit(Base::persistent().merge(other));
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_BST_ROLLBACK_ORDERED_SET_HPP
