#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP 1

#include <utility>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_dual_segtree.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid>
struct RollbackDualSegtree
    : detail::RollbackPersistentBase<PersistentDualSegtree<Monoid>> {
    using T = typename Monoid::value_type;

   private:
    using Persistent = PersistentDualSegtree<Monoid>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void set(int pos, T value) {
        Base::commit(Base::persistent().set(pos, std::move(value)));
    }
    void set_inplace(int pos, T value) { set(pos, std::move(value)); }

    void apply(int pos, const T& value) {
        Base::commit(Base::persistent().apply(pos, value));
    }
    void apply(int left, int right, const T& value) {
        Base::commit(Base::persistent().apply(left, right, value));
    }
    void apply_inplace(int pos, const T& value) { apply(pos, value); }
    void apply_inplace(int left, int right, const T& value) { apply(left, right, value); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP
