#ifndef M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP 1

#include <utility>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_segtree.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid>
struct RollbackSegtree
    : detail::RollbackPersistentBase<PersistentSegtree<Monoid>> {
    using T = typename Monoid::value_type;

   private:
    using Persistent = PersistentSegtree<Monoid>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void set(int pos, T value) {
        Base::commit(Base::persistent().set(pos, std::move(value)));
    }
    void set_inplace(int pos, T value) { set(pos, std::move(value)); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP
