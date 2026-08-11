#ifndef M1UNE_BEATS_ACTED_MONOID_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM_HPP
#define M1UNE_BEATS_ACTED_MONOID_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <limits>

namespace m1une {
namespace beats_acted_monoid {

template <std::signed_integral T>
struct RangeChminChmaxAddRangeSumNode {
    T sum;
    T maximum;
    T second_maximum;
    T minimum;
    T second_minimum;
    int maximum_count;
    int minimum_count;
    int length;
};

// Beats acted monoid for range chmin/chmax/add updates and range sum queries.
template <std::signed_integral T = long long>
struct RangeChminChmaxAddRangeSum {
    using value_type = RangeChminChmaxAddRangeSumNode<T>;

    // Represents f(x) = clamp(x + add, lower, upper).
    struct operator_type {
        T add;
        T lower;
        T upper;
    };

    static constexpr bool commutative = true;
    static constexpr bool operator_commutative = false;
    static constexpr T negative_infinity = std::numeric_limits<T>::lowest();
    static constexpr T positive_infinity = std::numeric_limits<T>::max();

   private:
    static constexpr T shift_lower_bound(T bound, T add) {
        return bound == negative_infinity ? bound : bound + add;
    }

    static constexpr T shift_upper_bound(T bound, T add) {
        return bound == positive_infinity ? bound : bound + add;
    }

    static constexpr void apply_add(value_type& value, T add) {
        if (value.length == 0 || add == T(0)) return;
        value.sum += add * T(value.length);
        value.maximum += add;
        value.minimum += add;
        if (value.maximum_count != value.length) {
            value.second_maximum += add;
        }
        if (value.minimum_count != value.length) {
            value.second_minimum += add;
        }
    }

    static constexpr bool can_apply_chmin(
        const value_type& value,
        T upper
    ) {
        return value.maximum <= upper ||
            value.maximum_count == value.length ||
            value.second_maximum < upper;
    }

    static constexpr void apply_chmin(value_type& value, T upper) {
        if (value.maximum <= upper) return;
        assert(can_apply_chmin(value, upper));
        value.sum +=
            (upper - value.maximum) * T(value.maximum_count);
        if (value.minimum == value.maximum) {
            value.minimum = upper;
        } else if (value.second_minimum == value.maximum) {
            value.second_minimum = upper;
        }
        value.maximum = upper;
    }

    static constexpr bool can_apply_chmax(
        const value_type& value,
        T lower
    ) {
        return lower <= value.minimum ||
            value.minimum_count == value.length ||
            lower < value.second_minimum;
    }

    static constexpr void apply_chmax(value_type& value, T lower) {
        if (lower <= value.minimum) return;
        assert(can_apply_chmax(value, lower));
        value.sum +=
            (lower - value.minimum) * T(value.minimum_count);
        if (value.maximum == value.minimum) {
            value.maximum = lower;
        } else if (value.second_maximum == value.minimum) {
            value.second_maximum = lower;
        }
        value.minimum = lower;
    }

    static constexpr value_type constant_value(T value, int length) {
        return {
            value * T(length),
            value,
            negative_infinity,
            value,
            positive_infinity,
            length,
            length,
            length
        };
    }

   public:
    static constexpr value_type id() {
        return {
            T(0),
            negative_infinity,
            negative_infinity,
            positive_infinity,
            positive_infinity,
            0,
            0,
            0
        };
    }

    static constexpr value_type op(
        const value_type& left,
        const value_type& right
    ) {
        if (left.length == 0) return right;
        if (right.length == 0) return left;

        value_type result;
        result.sum = left.sum + right.sum;
        result.length = left.length + right.length;

        result.maximum = std::max(left.maximum, right.maximum);
        result.maximum_count = 0;
        result.second_maximum = negative_infinity;
        if (left.maximum == result.maximum) {
            result.maximum_count += left.maximum_count;
            result.second_maximum = std::max(
                result.second_maximum,
                left.second_maximum
            );
        } else {
            result.second_maximum = std::max(
                result.second_maximum,
                left.maximum
            );
        }
        if (right.maximum == result.maximum) {
            result.maximum_count += right.maximum_count;
            result.second_maximum = std::max(
                result.second_maximum,
                right.second_maximum
            );
        } else {
            result.second_maximum = std::max(
                result.second_maximum,
                right.maximum
            );
        }

        result.minimum = std::min(left.minimum, right.minimum);
        result.minimum_count = 0;
        result.second_minimum = positive_infinity;
        if (left.minimum == result.minimum) {
            result.minimum_count += left.minimum_count;
            result.second_minimum = std::min(
                result.second_minimum,
                left.second_minimum
            );
        } else {
            result.second_minimum = std::min(
                result.second_minimum,
                left.minimum
            );
        }
        if (right.minimum == result.minimum) {
            result.minimum_count += right.minimum_count;
            result.second_minimum = std::min(
                result.second_minimum,
                right.second_minimum
            );
        } else {
            result.second_minimum = std::min(
                result.second_minimum,
                right.minimum
            );
        }
        return result;
    }

    static constexpr operator_type op_id() {
        return {T(0), negative_infinity, positive_infinity};
    }

    // Returns f(g(x)).
    static constexpr operator_type op_comp(
        const operator_type& f,
        const operator_type& g
    ) {
        T lower = shift_lower_bound(g.lower, f.add);
        T upper = shift_upper_bound(g.upper, f.add);
        return {
            g.add + f.add,
            std::clamp(lower, f.lower, f.upper),
            std::clamp(upper, f.lower, f.upper)
        };
    }

    static constexpr bool can_apply(
        const operator_type& f,
        const value_type& value
    ) {
        if (value.length == 0 || f.lower == f.upper) return true;
        value_type mapped = value;
        apply_add(mapped, f.add);
        if (
            mapped.maximum <= f.lower ||
            f.upper <= mapped.minimum
        ) {
            return true;
        }
        if (!can_apply_chmax(mapped, f.lower)) return false;
        apply_chmax(mapped, f.lower);
        return can_apply_chmin(mapped, f.upper);
    }

    static constexpr value_type mapping(
        const operator_type& f,
        const value_type& value
    ) {
        assert(can_apply(f, value));
        if (value.length == 0) return value;
        if (f.lower == f.upper) {
            return constant_value(f.lower, value.length);
        }
        value_type result = value;
        apply_add(result, f.add);
        if (result.maximum <= f.lower) {
            return constant_value(f.lower, result.length);
        }
        if (f.upper <= result.minimum) {
            return constant_value(f.upper, result.length);
        }
        apply_chmax(result, f.lower);
        apply_chmin(result, f.upper);
        return result;
    }

    static constexpr value_type make(const T& value) {
        return constant_value(value, 1);
    }

    static constexpr operator_type make_chmin(const T& upper) {
        return {T(0), negative_infinity, upper};
    }

    static constexpr operator_type make_chmax(const T& lower) {
        return {T(0), lower, positive_infinity};
    }

    static constexpr operator_type make_add(const T& add) {
        return {add, negative_infinity, positive_infinity};
    }
};

}  // namespace beats_acted_monoid
}  // namespace m1une

#endif  // M1UNE_BEATS_ACTED_MONOID_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM_HPP
