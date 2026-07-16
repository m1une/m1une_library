#ifndef M1UNE_MATH_RATIONAL_APPROXIMATION_HPP
#define M1UNE_MATH_RATIONAL_APPROXIMATION_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace m1une {
namespace math {

template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
struct RationalApproximationResult {
    using fraction_type = std::pair<T, T>;

    fraction_type lower;
    fraction_type upper;
};

namespace rational_approximation_detail {

using Wide = __uint128_t;

struct Fraction {
    Wide numerator;
    Wide denominator;
};

inline bool equal(
    const Fraction& fraction,
    Wide numerator,
    Wide denominator
) {
    return fraction.numerator * denominator ==
           numerator * fraction.denominator;
}

inline Wide coordinate_bound(
    Wide maximum,
    Wide offset,
    Wide step
) {
    return step == 0 ? maximum : (maximum - offset) / step;
}

inline Fraction multiply_add(
    const Fraction& first,
    Wide multiplier,
    const Fraction& second
) {
    return {
        first.numerator * multiplier + second.numerator,
        first.denominator * multiplier + second.denominator
    };
}

}  // namespace rational_approximation_detail

// Returns the closest reduced fractions below and above numerator/denominator
// whose positive numerator and denominator are both at most maximum.
template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
RationalApproximationResult<T> rational_approximation(
    T maximum,
    T numerator,
    T denominator
) {
    assert(maximum > 0);
    assert(numerator > 0);
    assert(denominator > 0);
    static_assert(sizeof(T) <= sizeof(uint64_t));

    using rational_approximation_detail::Fraction;
    using rational_approximation_detail::Wide;
    using rational_approximation_detail::coordinate_bound;
    using rational_approximation_detail::equal;
    using rational_approximation_detail::multiply_add;

    const Wide limit = static_cast<std::make_unsigned_t<T>>(maximum);
    const Wide target_numerator =
        static_cast<std::make_unsigned_t<T>>(numerator);
    const Wide target_denominator =
        static_cast<std::make_unsigned_t<T>>(denominator);
    Fraction lower{0, 1};
    Fraction upper{1, 0};

    while (true) {
        Wide lower_multiplier = limit;
        lower_multiplier = std::min(
            lower_multiplier,
            coordinate_bound(limit, lower.numerator, upper.numerator)
        );
        lower_multiplier = std::min(
            lower_multiplier,
            coordinate_bound(limit, lower.denominator, upper.denominator)
        );
        const Wide lower_slack =
            target_numerator * lower.denominator -
            lower.numerator * target_denominator;
        const Wide lower_step =
            upper.numerator * target_denominator -
            target_numerator * upper.denominator;
        assert(lower_step != 0);
        lower_multiplier = std::min(
            lower_multiplier, lower_slack / lower_step
        );
        lower = multiply_add(upper, lower_multiplier, lower);
        if (equal(lower, target_numerator, target_denominator)) {
            upper = lower;
            break;
        }

        Wide upper_multiplier = limit;
        upper_multiplier = std::min(
            upper_multiplier,
            coordinate_bound(limit, upper.numerator, lower.numerator)
        );
        upper_multiplier = std::min(
            upper_multiplier,
            coordinate_bound(limit, upper.denominator, lower.denominator)
        );
        const Wide upper_slack =
            upper.numerator * target_denominator -
            target_numerator * upper.denominator;
        const Wide upper_step =
            target_numerator * lower.denominator -
            lower.numerator * target_denominator;
        assert(upper_step != 0);
        upper_multiplier = std::min(
            upper_multiplier, upper_slack / upper_step
        );
        upper = multiply_add(lower, upper_multiplier, upper);
        if (equal(upper, target_numerator, target_denominator)) {
            lower = upper;
            break;
        }

        if (lower_multiplier == 0 && upper_multiplier == 0) break;
    }

    RationalApproximationResult<T> result;
    result.lower = {
        static_cast<T>(lower.numerator),
        static_cast<T>(lower.denominator)
    };
    result.upper = {
        static_cast<T>(upper.numerator),
        static_cast<T>(upper.denominator)
    };
    return result;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_RATIONAL_APPROXIMATION_HPP
