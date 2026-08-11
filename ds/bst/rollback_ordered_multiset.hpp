#ifndef M1UNE_DS_BST_ROLLBACK_ORDERED_MULTISET_HPP
#define M1UNE_DS_BST_ROLLBACK_ORDERED_MULTISET_HPP 1

#include <functional>
#include <utility>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_ordered_multiset.hpp"

namespace m1une {
namespace ds {

template <class T, class Compare = std::less<T>>
struct RollbackOrderedMultiset
    : detail::RollbackPersistentBase<PersistentOrderedMultiset<T, Compare>> {
   private:
    using Persistent = PersistentOrderedMultiset<T, Compare>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void clear() {
        Base::commit(Base::persistent().clear());
    }

    void insert(T key, int multiplicity = 1) {
        Base::commit(Base::persistent().insert(std::move(key), multiplicity));
    }

    void insert_inplace(T key, int multiplicity = 1) {
        insert(std::move(key), multiplicity);
    }

    bool erase_one(const T& key) {
        bool erased = Base::persistent().contains(key);
        Base::commit(Base::persistent().erase_one(key));
        return erased;
    }

    bool erase(const T& key) {
        return erase_one(key);
    }

    bool erase_one_inplace(const T& key) {
        return erase_one(key);
    }

    bool erase_inplace(const T& key) {
        return erase_one(key);
    }

    int erase_all(const T& key) {
        int erased = Base::persistent().count(key);
        Base::commit(Base::persistent().erase_all(key));
        return erased;
    }

    bool erase_all_inplace(const T& key) {
        return erase_all(key) != 0;
    }

    void merge(const RollbackOrderedMultiset& other) {
        Base::commit(Base::persistent().merge(other.current_version()));
    }

    void merge(const Persistent& other) {
        Base::commit(Base::persistent().merge(other));
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_BST_ROLLBACK_ORDERED_MULTISET_HPP
