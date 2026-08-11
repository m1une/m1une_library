#ifndef M1UNE_FPS_SOLVE_FPS_EQUATION_HPP
#define M1UNE_FPS_SOLVE_FPS_EQUATION_HPP 1

#include <algorithm>
#include <cassert>

#include "../newton_method.hpp"

namespace m1une {
namespace fps {

// Extends a solution modulo x^initial.size() to a solution modulo x^degree.
// Both callbacks receive the precision currently requested by Newton lifting.
template <class Mint, class Function, class Derivative>
FormalPowerSeries<Mint> solve_fps_equation(
    FormalPowerSeries<Mint> initial,
    int degree,
    Function function,
    Derivative derivative
) {
    using Fps = FormalPowerSeries<Mint>;
    assert(degree >= 0);
    if (degree == 0) return {};
    assert(!initial.empty());
    if (int(initial.size()) >= degree) return initial.pre(degree);

    while (int(initial.size()) < degree) {
        const int next_degree = std::min(int(initial.size()) << 1, degree);
        initial.resize(next_degree);

        auto truncated_function = [&](const Fps& value) {
            return function(value, next_degree).pre(next_degree);
        };
        auto truncated_derivative = [&](const Fps& value) {
            return derivative(value, next_degree).pre(next_degree);
        };
        initial = math::newton_method(
            initial, truncated_function, truncated_derivative, 1
        );
    }
    return initial;
}

// Starts Newton lifting from a solution modulo x.
template <class Mint, class Function, class Derivative>
FormalPowerSeries<Mint> solve_fps_equation(
    int degree,
    Mint constant_solution,
    Function function,
    Derivative derivative
) {
    assert(degree >= 0);
    if (degree == 0) return {};
    return solve_fps_equation(
        FormalPowerSeries<Mint>(1, constant_solution),
        degree,
        function,
        derivative
    );
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_SOLVE_FPS_EQUATION_HPP
