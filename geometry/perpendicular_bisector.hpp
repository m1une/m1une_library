#ifndef M1UNE_GEOMETRY_PERPENDICULAR_BISECTOR_HPP
#define M1UNE_GEOMETRY_PERPENDICULAR_BISECTOR_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <limits>
#include <numeric>

#include "line.hpp"

namespace m1une {
namespace geometry {

namespace perpendicular_bisector_detail {

template <class Integer>
constexpr Integer absolute(Integer value) {
    return value < 0 ? -value : value;
}

template <class Integer>
constexpr Integer gcd(Integer first, Integer second) {
    first = absolute(first);
    second = absolute(second);
    while (second != 0) {
        Integer remainder = first % second;
        first = second;
        second = remainder;
    }
    return first;
}

template <class Integer>
constexpr Integer floor_div(Integer numerator, Integer denominator) {
    assert(denominator > 0);
    Integer quotient = numerator / denominator;
    if (numerator % denominator < 0) --quotient;
    return quotient;
}

template <class Integer>
constexpr Integer ceil_div(Integer numerator, Integer denominator) {
    assert(denominator > 0);
    Integer quotient = numerator / denominator;
    if (numerator % denominator > 0) ++quotient;
    return quotient;
}

template <class Integer>
struct ParameterBounds {
    Integer lower;
    Integer upper;
};

template <class Integer>
constexpr ParameterBounds<Integer> parameter_bounds(
    Integer value,
    Integer step,
    Integer minimum,
    Integer maximum
) {
    assert(step != 0);
    Integer valid_minimum = std::max(minimum, minimum - step);
    Integer valid_maximum = std::min(maximum, maximum - step);
    if (step > 0) {
        return ParameterBounds<Integer>{
            ceil_div(valid_minimum - value, step),
            floor_div(valid_maximum - value, step)
        };
    }
    Integer positive_step = -step;
    return ParameterBounds<Integer>{
        ceil_div(value - valid_maximum, positive_step),
        floor_div(value - valid_minimum, positive_step)
    };
}

template <Coordinate T>
requires std::integral<T>
constexpr Line<T> integral_perpendicular_bisector(
    const Point<T>& first,
    const Point<T>& second
) {
    using W = wide_type<T>;
    W first_x = W(first.x);
    W first_y = W(first.y);
    W second_x = W(second.x);
    W second_y = W(second.y);
    W difference_x = second_x - first_x;
    W difference_y = second_y - first_y;
    W divisor = gcd(difference_x, difference_y);
    assert(divisor != 0);

    W primitive_x = difference_x / divisor;
    W primitive_y = difference_y / divisor;
    W sum_x = first_x + second_x;
    W sum_y = first_y + second_y;

    W base_x;
    W base_y;
    if (sum_x % 2 == 0 && sum_y % 2 == 0) {
        base_x = sum_x / 2;
        base_y = sum_y / 2;
    } else {
        assert((sum_x + primitive_y) % 2 == 0);
        assert((sum_y - primitive_x) % 2 == 0);
        base_x = (sum_x + primitive_y) / 2;
        base_y = (sum_y - primitive_x) / 2;
    }

    W step_x = -primitive_y;
    W step_y = primitive_x;
    W minimum = W(std::numeric_limits<T>::lowest());
    W maximum = W(std::numeric_limits<T>::max());
    W lower = std::numeric_limits<W>::lowest();
    W upper = std::numeric_limits<W>::max();

    auto restrict_parameter = [&](W value, W step) {
        if (step == 0) {
            assert(minimum <= value && value <= maximum);
            return;
        }
        ParameterBounds<W> bounds =
            parameter_bounds(value, step, minimum, maximum);
        lower = std::max(lower, bounds.lower);
        upper = std::min(upper, bounds.upper);
    };
    restrict_parameter(base_x, step_x);
    restrict_parameter(base_y, step_y);
    assert(lower <= upper);

    W parameter = std::clamp(W(0), lower, upper);
    W result_x = base_x + step_x * parameter;
    W result_y = base_y + step_y * parameter;
    W next_x = result_x + step_x;
    W next_y = result_y + step_y;
    assert(minimum <= result_x && result_x <= maximum);
    assert(minimum <= result_y && result_y <= maximum);
    assert(minimum <= next_x && next_x <= maximum);
    assert(minimum <= next_y && next_y <= maximum);

    Line<T> result;
    result.a = Point<T>(T(result_x), T(result_y));
    result.b = Point<T>(T(next_x), T(next_y));
    return result;
}

}  // namespace perpendicular_bisector_detail

template <Coordinate T>
constexpr Line<T> perpendicular_bisector(
    const Point<T>& first,
    const Point<T>& second
) {
    assert(first != second);
    if constexpr (std::integral<T>) {
        return perpendicular_bisector_detail::integral_perpendicular_bisector(
            first,
            second
        );
    } else {
        Point<T> midpoint(
            std::midpoint(first.x, second.x),
            std::midpoint(first.y, second.y)
        );
        Point<T> direction(first.y - second.y, second.x - first.x);

        Line<T> result;
        result.a = midpoint;
        result.b = midpoint + direction;
        return result;
    }
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_PERPENDICULAR_BISECTOR_HPP
