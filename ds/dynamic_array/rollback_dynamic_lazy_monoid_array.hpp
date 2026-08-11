#ifndef M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_LAZY_MONOID_ARRAY_HPP
#define M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_LAZY_MONOID_ARRAY_HPP 1

#include <initializer_list>
#include <utility>
#include <vector>

#include "../detail/rollback_persistent_base.hpp"
#include "persistent_dynamic_lazy_monoid_array.hpp"

namespace m1une {
namespace ds {

template <class ActedMonoid>
struct RollbackDynamicLazyMonoidArray
    : detail::RollbackPersistentBase<PersistentDynamicLazyMonoidArray<ActedMonoid>> {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    using Persistent = PersistentDynamicLazyMonoidArray<ActedMonoid>;
    using Base = detail::RollbackPersistentBase<Persistent>;

   public:
    using Base::Base;

    void clear() { Base::commit(Base::persistent().clear()); }

    void insert(int pos, T value) {
        Base::commit(Base::persistent().insert(pos, std::move(value)));
    }
    void insert(int pos, const std::vector<T>& values) {
        Base::commit(Base::persistent().insert(pos, values));
    }
    void insert(int pos, std::vector<T>&& values) {
        Base::commit(Base::persistent().insert(pos, std::move(values)));
    }
    void insert(int pos, std::initializer_list<T> values) {
        Base::commit(Base::persistent().insert(pos, values));
    }
    void insert(int pos, const RollbackDynamicLazyMonoidArray& other) {
        Base::commit(Base::persistent().insert(pos, other.current_version()));
    }
    void insert(int pos, const Persistent& other) {
        Base::commit(Base::persistent().insert(pos, other));
    }

    void push_back(T value) { insert(this->size(), std::move(value)); }
    void push_front(T value) { insert(0, std::move(value)); }
    void append(const std::vector<T>& values) { insert(this->size(), values); }
    void append(std::vector<T>&& values) { insert(this->size(), std::move(values)); }
    void append(const RollbackDynamicLazyMonoidArray& other) { insert(this->size(), other); }
    void append(const Persistent& other) { insert(this->size(), other); }

    void erase(int pos) { Base::commit(Base::persistent().erase(pos)); }
    void erase(int left, int right) { Base::commit(Base::persistent().erase(left, right)); }
    void pop_back() { Base::commit(Base::persistent().pop_back()); }
    void pop_front() { Base::commit(Base::persistent().pop_front()); }

    void set(int pos, T value) {
        Base::commit(Base::persistent().set(pos, std::move(value)));
    }
    void set_inplace(int pos, T value) { set(pos, std::move(value)); }

    void reverse(int left, int right) {
        Base::commit(Base::persistent().reverse(left, right));
    }
    void reverse() { Base::commit(Base::persistent().reverse()); }
    void rotate(int left, int middle, int right) {
        Base::commit(Base::persistent().rotate(left, middle, right));
    }

    void apply(int pos, const F& f) {
        Base::commit(Base::persistent().apply(pos, f));
    }
    void apply(int left, int right, const F& f) {
        Base::commit(Base::persistent().apply(left, right, f));
    }
    void apply_inplace(int pos, const F& f) { apply(pos, f); }
    void apply_inplace(int left, int right, const F& f) { apply(left, right, f); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_DYNAMIC_ARRAY_ROLLBACK_DYNAMIC_LAZY_MONOID_ARRAY_HPP
