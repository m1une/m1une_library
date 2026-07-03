#ifndef M1UNE_MATH_CYCLOTOMIC_POLYNOMIAL_HPP
#define M1UNE_MATH_CYCLOTOMIC_POLYNOMIAL_HPP 1

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

#include "prime_factorization.hpp"

namespace m1une {
namespace math {

template <class T = long long>
std::vector<T> cyclotomic_polynomial(std::uint64_t index) {
    assert(index >= 1);
    if (index == 1) return {T(-1), T(1)};

    const std::vector<std::pair<std::uint64_t, int>> factors =
        prime_factorize(index);
    std::uint64_t degree = index;
    for (const auto& factor : factors) {
        degree = degree / factor.first * (factor.first - 1);
    }
    assert(degree < std::numeric_limits<std::size_t>::max());

    std::vector<T> result(static_cast<std::size_t>(degree) + 1, T(0));
    result[0] = T(1);

    const std::size_t subset_count = std::size_t(1) << factors.size();
    for (std::size_t mask = 0; mask < subset_count; mask++) {
        std::uint64_t exponent = index;
        bool negative_mobius = false;
        for (std::size_t i = 0; i < factors.size(); i++) {
            if ((mask >> i) & 1) {
                exponent /= factors[i].first;
                negative_mobius = !negative_mobius;
            }
        }
        if (exponent > degree) continue;

        const std::size_t shift = static_cast<std::size_t>(exponent);
        if (negative_mobius) {
            // Divide by 1 - x^shift as a truncated formal power series.
            for (std::size_t i = shift; i <= degree; i++) {
                result[i] += result[i - shift];
            }
        } else {
            // Multiply by 1 - x^shift.
            for (std::size_t i = static_cast<std::size_t>(degree);
                 i >= shift;
                 i--) {
                result[i] -= result[i - shift];
                if (i == shift) break;
            }
        }
    }
    return result;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_CYCLOTOMIC_POLYNOMIAL_HPP
