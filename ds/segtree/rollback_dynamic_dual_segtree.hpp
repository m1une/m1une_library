#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_DUAL_SEGTREE_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_DUAL_SEGTREE_HPP 1

#include <concepts>
#include <type_traits>
#include <utility>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_dynamic_dual_segtree.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid, std::integral Index = long long>
    requires(!std::same_as<std::remove_cv_t<Index>, bool>)
struct RollbackDynamicDualSegtree
    : detail::RollbackPersistentBase<PersistentDynamicDualSegtree<Monoid, Index>> {
    using T = typename Monoid::value_type;

   private:
    using Persistent = PersistentDynamicDualSegtree<Monoid, Index>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void set(Index pos, T value) {
        Base::commit(Base::persistent().set(pos, std::move(value)));
    }
    void set_inplace(Index pos, T value) { set(pos, std::move(value)); }

    void apply(Index pos, const T& value) {
        Base::commit(Base::persistent().apply(pos, value));
    }
    void apply(Index left, Index right, const T& value) {
        Base::commit(Base::persistent().apply(left, right, value));
    }
    void apply_inplace(Index pos, const T& value) { apply(pos, value); }
    void apply_inplace(Index left, Index right, const T& value) { apply(left, right, value); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_DUAL_SEGTREE_HPP
