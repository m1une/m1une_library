#ifndef M1UNE_MATH_DIVISOR_CONVOLUTION_HPP
#define M1UNE_MATH_DIVISOR_CONVOLUTION_HPP 1

#include <cstddef>
#include <vector>

#include "zeta_mobius_transform.hpp"

namespace m1une {
namespace math {

template <typename T>
std::vector<T> gcd_convolution(
    std::vector<T> first,
    std::vector<T> second
) {
    if (first.empty() || second.empty()) return {};
    const std::size_t size = first.size() > second.size()
        ? first.size()
        : second.size();
    first.resize(size);
    second.resize(size);
    first[0] = T{};
    second[0] = T{};

    multiple_zeta_transform(first);
    multiple_zeta_transform(second);
    for (std::size_t index = 1; index < size; ++index) {
        first[index] *= second[index];
    }
    multiple_mobius_transform(first);
    return first;
}

template <typename T>
std::vector<T> lcm_convolution(
    std::vector<T> first,
    std::vector<T> second
) {
    if (first.empty() || second.empty()) return {};
    const std::size_t size = first.size() > second.size()
        ? first.size()
        : second.size();
    first.resize(size);
    second.resize(size);
    first[0] = T{};
    second[0] = T{};

    divisor_zeta_transform(first);
    divisor_zeta_transform(second);
    for (std::size_t index = 1; index < size; ++index) {
        first[index] *= second[index];
    }
    divisor_mobius_transform(first);
    return first;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_DIVISOR_CONVOLUTION_HPP
