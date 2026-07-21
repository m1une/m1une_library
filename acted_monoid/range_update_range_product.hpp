#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_PRODUCT_HPP
#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_PRODUCT_HPP 1

#include <optional>

#include "../monoid/concept.hpp"
#include "../monoid/power.hpp"

namespace m1une {
namespace acted_monoid {

template <m1une::monoid::IsMonoid Monoid>
struct RangeUpdateRangeProductNode {
    using base_type = typename Monoid::value_type;

    base_type product;
    long long size;
};

// Range assignment and range product for an arbitrary, possibly
// noncommutative, monoid.
template <m1une::monoid::IsMonoid Monoid>
struct RangeUpdateRangeProduct {
    using base_type = typename Monoid::value_type;
    using value_type = RangeUpdateRangeProductNode<Monoid>;
    using operator_type = std::optional<base_type>;
    static constexpr bool commutative = [] {
        if constexpr (requires { Monoid::commutative; }) {
            return bool(Monoid::commutative);
        } else {
            return false;
        }
    }();
    static constexpr bool operator_commutative = false;

    static constexpr value_type id() {
        return {Monoid::id(), 0};
    }

    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {Monoid::op(a.product, b.product), a.size + b.size};
    }

    static constexpr operator_type op_id() {
        return std::nullopt;
    }

    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f.has_value() ? f : g;
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (!f.has_value() || x.size == 0) return x;
        return {m1une::monoid::power<Monoid>(f.value(), x.size), x.size};
    }

    static constexpr value_type make(const base_type& value) {
        return {value, 1};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_PRODUCT_HPP
