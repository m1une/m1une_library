#ifndef M1UNE_FPS_COMPOSITIONAL_INVERSE_HPP
#define M1UNE_FPS_COMPOSITIONAL_INVERSE_HPP 1

#include <algorithm>
#include <cassert>

#include "composition.hpp"

namespace m1une {
namespace fps {

template <class Mint>
FormalPowerSeries<Mint> compositional_inverse(const FormalPowerSeries<Mint>& f,
                                              int degree = -1) {
    using Fps = FormalPowerSeries<Mint>;
    if (degree < 0) degree = int(f.size());
    assert(degree >= 0);
    if (degree == 0) return {};
    assert(f.size() >= 2 && f[0] == Mint(0) && f[1] != Mint(0));

    Fps result(2);
    result[1] = f[1].inv();
    if (degree == 1) return result.pre(1);

    for (int size = 2; size < degree;) {
        const int next_size = std::min(size << 1, degree);
        Fps composed = compose(f.pre(next_size), result, next_size);
        const int correction_size = next_size - size;
        Fps inverse_derivative = composed.derivative().inv(correction_size);
        composed[1] -= Mint(1);
        Fps inverse_jacobian =
            (result.derivative().pre(correction_size) * inverse_derivative)
                .pre(correction_size);
        Fps correction = ((composed >> size) * inverse_jacobian).pre(correction_size);
        correction <<= size;

        result = result.pre(next_size) - correction;
        result.resize(next_size);
        size = next_size;
    }
    return result.pre(degree);
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_COMPOSITIONAL_INVERSE_HPP
