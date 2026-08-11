#ifndef M1UNE_BEATS_ACTED_MONOID_RANGE_BITWISE_AND_OR_RANGE_SUM_HPP
#define M1UNE_BEATS_ACTED_MONOID_RANGE_BITWISE_AND_OR_RANGE_SUM_HPP 1

#include <cassert>
#include <limits>
#include <type_traits>

namespace m1une {
namespace beats_acted_monoid {

template <typename T>
struct RangeBitwiseAndOrRangeSumNode {
    T sum;
    T bitwise_and;
    T bitwise_or;
    long long length;
};

// Beats acted monoid for range bitwise AND/OR updates and range sum queries.
template <typename T, int BITS = 30>
struct RangeBitwiseAndOrRangeSum {
    static_assert(
        std::is_integral_v<T> &&
        !std::is_same_v<std::remove_cv_t<T>, bool>
    );
    static_assert(0 < BITS && BITS <= std::numeric_limits<T>::digits);

    using value_type = RangeBitwiseAndOrRangeSumNode<T>;

    // Represents f(x) = (x & and_mask) | or_mask.
    struct operator_type {
        T and_mask;
        T or_mask;
    };

    static constexpr bool commutative = true;
    static constexpr bool operator_commutative = false;

    static constexpr T bit_mask() {
        if constexpr (
            std::is_unsigned_v<T> &&
            BITS == std::numeric_limits<T>::digits
        ) {
            return ~T(0);
        } else {
            return
                (T(1) << (BITS - 1)) |
                ((T(1) << (BITS - 1)) - 1);
        }
    }

    static constexpr value_type id() {
        return {T(0), bit_mask(), T(0), 0};
    }

    static constexpr value_type op(
        const value_type& left,
        const value_type& right
    ) {
        return {
            left.sum + right.sum,
            left.bitwise_and & right.bitwise_and,
            left.bitwise_or | right.bitwise_or,
            left.length + right.length
        };
    }

    static constexpr operator_type op_id() {
        return {bit_mask(), T(0)};
    }

    // Returns f(g(x)).
    static constexpr operator_type op_comp(
        const operator_type& f,
        const operator_type& g
    ) {
        return {
            (f.and_mask & g.and_mask) & bit_mask(),
            ((g.or_mask & f.and_mask) | f.or_mask) & bit_mask()
        };
    }

    static constexpr bool can_apply(
        const operator_type& f,
        const value_type& value
    ) {
        if (value.length == 0) return true;
        T changed = ((~f.and_mask) | f.or_mask) & bit_mask();
        T mixed = value.bitwise_and ^ value.bitwise_or;
        return (changed & mixed) == T(0);
    }

    static constexpr value_type mapping(
        const operator_type& f,
        const value_type& value
    ) {
        assert(can_apply(f, value));
        if (value.length == 0) return value;
        T changed = ((~f.and_mask) | f.or_mask) & bit_mask();
        T old_uniform = value.bitwise_and & changed;
        T new_uniform =
            ((old_uniform & f.and_mask) | f.or_mask) & changed;

        value_type result = value;
        result.sum +=
            (new_uniform - old_uniform) * T(value.length);
        result.bitwise_and =
            ((value.bitwise_and & f.and_mask) | f.or_mask) & bit_mask();
        result.bitwise_or =
            ((value.bitwise_or & f.and_mask) | f.or_mask) & bit_mask();
        return result;
    }

    static constexpr value_type make(const T& value) {
        assert((value & ~bit_mask()) == T(0));
        return {value, value, value, 1};
    }

    static constexpr operator_type make_and(const T& mask) {
        return {mask & bit_mask(), T(0)};
    }

    static constexpr operator_type make_or(const T& mask) {
        return {bit_mask(), mask & bit_mask()};
    }
};

}  // namespace beats_acted_monoid
}  // namespace m1une

#endif  // M1UNE_BEATS_ACTED_MONOID_RANGE_BITWISE_AND_OR_RANGE_SUM_HPP
