#ifndef M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP 1

#include <utility>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_lazy_segtree.hpp"

namespace m1une {
namespace ds {

template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct RollbackLazySegtree
    : detail::RollbackPersistentBase<PersistentLazySegtree<ActedMonoid>> {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    using Persistent = PersistentLazySegtree<ActedMonoid>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void set(int pos, T value) {
        Base::commit(Base::persistent().set(pos, std::move(value)));
    }
    void set_inplace(int pos, T value) { set(pos, std::move(value)); }

    void apply(int pos, const F& f) {
        Base::commit(Base::persistent().apply(pos, f));
    }
    void apply(int left, int right, const F& f) {
        Base::commit(Base::persistent().apply(left, right, f));
    }
    void apply_inplace(int pos, const F& f) { apply(pos, f); }
    void apply_inplace(int left, int right, const F& f) { apply(left, right, f); }

    void copy_range_from(const RollbackLazySegtree& source, int left, int right) {
        Base::commit(Base::persistent().copy_range_from(source.current_version(), left, right));
    }
    void copy_range_from(const Persistent& source, int left, int right) {
        Base::commit(Base::persistent().copy_range_from(source, left, right));
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP
