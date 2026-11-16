#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_GCD_HPP
#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_GCD_HPP 1

#include <algorithm>
#include <numeric>
#include <type_traits>

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeAddRangeGcdNode {
    T min;
    T diff_gcd;
    bool empty;
};

// Range addition preserves the GCD of differences from the minimum.
template <typename T>
struct RangeAddRangeGcd {
    static_assert(std::is_integral_v<T> && std::is_signed_v<T>);

    using value_type = RangeAddRangeGcdNode<T>;
    using operator_type = T;
    static constexpr bool commutative = true;
    static constexpr bool operator_commutative = true;

    static constexpr value_type id() {
        return {T(0), T(0), true};
    }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        if (a.empty) return b;
        if (b.empty) return a;
        return {std::min(a.min, b.min),
                std::gcd(std::gcd(a.diff_gcd, b.diff_gcd), T(a.min - b.min)), false};
    }

    static constexpr operator_type op_id() {
        return T(0);
    }
    // Returns f(g(x)).
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f + g;
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (x.empty) return x;
        return {T(x.min + f), x.diff_gcd, false};
    }

    static constexpr value_type make(const T& val) {
        return {val, T(0), false};
    }
    // Returns a nonnegative GCD, or zero for an empty range.
    static constexpr T gcd(const value_type& x) {
        return std::gcd(x.min, x.diff_gcd);
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_GCD_HPP
