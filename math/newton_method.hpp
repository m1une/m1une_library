#ifndef M1UNE_MATH_NEWTON_METHOD_HPP
#define M1UNE_MATH_NEWTON_METHOD_HPP 1

#include <cassert>

#include "fps/formal_power_series.hpp"

namespace m1une {
namespace math {

namespace newton_method_detail {

template <class T>
struct DefaultQuotient {
    template <class Numerator, class Denominator>
    auto operator()(
        const Numerator& numerator,
        const Denominator& denominator
    ) const {
        return numerator / denominator;
    }
};

template <class Mint>
struct DefaultQuotient<fps::FormalPowerSeries<Mint>> {
    using Fps = fps::FormalPowerSeries<Mint>;

    int degree;

    Fps operator()(const Fps& numerator, const Fps& denominator) const {
        return (numerator.pre(degree) * denominator.inv(degree)).pre(degree);
    }
};

template <class T>
DefaultQuotient<T> make_default_quotient(const T&) {
    return {};
}

template <class Mint>
DefaultQuotient<fps::FormalPowerSeries<Mint>> make_default_quotient(
    const fps::FormalPowerSeries<Mint>& value
) {
    return {int(value.size())};
}

}  // namespace newton_method_detail

template <class T, class F, class Derivative, class Quotient>
T newton_method(
    T initial,
    F function,
    Derivative derivative,
    int iterations,
    Quotient quotient
) {
    assert(iterations >= 0);
    for (int iteration = 0; iteration < iterations; iteration++) {
        auto numerator = function(initial);
        auto denominator = derivative(initial);
        initial -= quotient(numerator, denominator);
    }
    return initial;
}

template <class T, class F, class Derivative>
T newton_method(
    T initial,
    F function,
    Derivative derivative,
    int iterations
) {
    auto quotient = newton_method_detail::make_default_quotient(initial);
    return newton_method(initial, function, derivative, iterations, quotient);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_NEWTON_METHOD_HPP
