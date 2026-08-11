#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP 1

#include <concepts>
#include <type_traits>
#include <utility>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_dynamic_segtree.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid, std::integral Index = long long>
    requires(!std::same_as<std::remove_cv_t<Index>, bool>)
struct RollbackDynamicSegtree
    : detail::RollbackPersistentBase<PersistentDynamicSegtree<Monoid, Index>> {
    using T = typename Monoid::value_type;

   private:
    using Persistent = PersistentDynamicSegtree<Monoid, Index>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void set(Index pos, T value) {
        Base::commit(Base::persistent().set(pos, std::move(value)));
    }
    void set_inplace(Index pos, T value) { set(pos, std::move(value)); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP
