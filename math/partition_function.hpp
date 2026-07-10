#ifndef M1UNE_MATH_PARTITION_FUNCTION_HPP
#define M1UNE_MATH_PARTITION_FUNCTION_HPP 1

#include "fps/formal_power_series.hpp"

#include <cassert>
#include <vector>

namespace m1une {
namespace math {

// Returns p(0), p(1), ..., p(maximum), where p(n) is the number of integer
// partitions of n.
template <class Mint>
std::vector<Mint> partition_function(int maximum) {
    assert(maximum >= 0);

    using Fps = fps::FormalPowerSeries<Mint>;
    Fps denominator(maximum + 1);
    denominator[0] = 1;
    for (long long k = 1;; k++) {
        long long first = k * (3 * k - 1) / 2;
        long long second = k * (3 * k + 1) / 2;
        if (first > maximum) break;

        Mint sign = (k & 1) ? Mint(-1) : Mint(1);
        denominator[int(first)] += sign;
        if (second <= maximum) denominator[int(second)] += sign;
    }
    return denominator.inv(maximum + 1);
}

template <class Mint>
std::vector<Mint> partition_numbers(int maximum) {
    return partition_function<Mint>(maximum);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_PARTITION_FUNCTION_HPP
