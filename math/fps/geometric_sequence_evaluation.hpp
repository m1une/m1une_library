#ifndef M1UNE_FPS_GEOMETRIC_SEQUENCE_EVALUATION_HPP
#define M1UNE_FPS_GEOMETRIC_SEQUENCE_EVALUATION_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "formal_power_series.hpp"

namespace m1une {
namespace fps {

namespace internal {

template <class Mint>
std::vector<Mint> geometric_triangular_powers(Mint ratio, int count) {
    assert(count >= 0);
    std::vector<Mint> result(count);
    if (count == 0) return result;
    result[0] = Mint(1);
    Mint power = Mint(1);
    for (int i = 0; i + 1 < count; ++i) {
        result[i + 1] = result[i] * power;
        power *= ratio;
    }
    return result;
}

template <class Mint>
std::vector<Mint> geometric_batch_inverse(const std::vector<Mint>& values) {
    const int count = int(values.size());
    std::vector<Mint> prefix(count + 1, Mint(1));
    for (int i = 0; i < count; ++i) {
        assert(values[i] != Mint(0));
        prefix[i + 1] = prefix[i] * values[i];
    }

    std::vector<Mint> result(count);
    Mint inverse_suffix = prefix[count].inv();
    for (int i = count - 1; i >= 0; --i) {
        result[i] = prefix[i] * inverse_suffix;
        inverse_suffix *= values[i];
    }
    return result;
}

template <class Mint>
std::vector<Mint> geometric_middle_product(const std::vector<Mint>& first,
                                           std::vector<Mint> second) {
    assert(first.size() >= second.size());
    if (second.empty()) return std::vector<Mint>(first.size() + 1);
    std::reverse(second.begin(), second.end());
    const std::vector<Mint> product = convolution(first, second);
    const int result_size = int(first.size() - second.size() + 1);
    return std::vector<Mint>(product.begin() + second.size() - 1,
                             product.begin() + second.size() - 1 + result_size);
}

}  // namespace internal

template <class Mint>
std::vector<Mint> multipoint_evaluate_geometric(
    const FormalPowerSeries<Mint>& polynomial, Mint initial, Mint ratio, int count) {
    assert(count >= 0);
    if (count == 0) return {};
    if (polynomial.empty()) return std::vector<Mint>(count);
    if (initial == Mint(0)) return std::vector<Mint>(count, polynomial[0]);
    if (ratio == Mint(0)) {
        std::vector<Mint> result(count, polynomial[0]);
        result[0] = polynomial.evaluate(initial);
        return result;
    }

    const int coefficient_count = int(polynomial.size());
    std::vector<Mint> scaled(polynomial.begin(), polynomial.end());
    Mint initial_power = Mint(1);
    for (Mint& coefficient : scaled) {
        coefficient *= initial_power;
        initial_power *= initial;
    }

    const std::vector<Mint> chirp = internal::geometric_triangular_powers(
        ratio, coefficient_count + count - 1);
    const std::vector<Mint> inverse_chirp = internal::geometric_triangular_powers(
        ratio.inv(), std::max(coefficient_count, count));
    for (int i = 0; i < coefficient_count; ++i) scaled[i] *= inverse_chirp[i];
    std::reverse(scaled.begin(), scaled.end());

    const std::vector<Mint> product = convolution(scaled, chirp);
    std::vector<Mint> result(count);
    for (int i = 0; i < count; ++i) {
        result[i] = product[coefficient_count - 1 + i] * inverse_chirp[i];
    }
    return result;
}

template <class Mint>
FormalPowerSeries<Mint> polynomial_interpolate_geometric(
    const std::vector<Mint>& values, Mint initial, Mint ratio) {
    using Fps = FormalPowerSeries<Mint>;
    const int count = int(values.size());
    if (count == 0) return {};
    if (count == 1) return Fps(1, values[0]);
    assert(initial != Mint(0));
    assert(ratio != Mint(0));

    std::vector<Mint> ratio_power(2 * count - 1, Mint(1));
    std::vector<Mint> chirp(2 * count - 1, Mint(1));
    for (int i = 0; i + 1 < int(ratio_power.size()); ++i) {
        ratio_power[i + 1] = ratio_power[i] * ratio;
        chirp[i + 1] = chirp[i] * ratio_power[i];
    }
    const std::vector<Mint> inverse_chirp =
        internal::geometric_triangular_powers(ratio.inv(), count);

    std::vector<Mint> difference_product(count, Mint(1));
    for (int i = 1; i < count; ++i) {
        assert(ratio_power[i] != Mint(1));
        difference_product[i] =
            difference_product[i - 1] * (Mint(1) - ratio_power[i]);
    }
    const std::vector<Mint> inverse_difference =
        internal::geometric_batch_inverse(difference_product);
    const Mint complete_product =
        difference_product[count - 1] * (Mint(1) - ratio_power[count]);

    std::vector<Mint> weighted = values;
    for (int i = 0; i < count; ++i) {
        weighted[i] *= chirp[count - 1 - i] * inverse_chirp[count - 1] *
                       inverse_difference[i] * inverse_difference[count - 1 - i];
        if (i & 1) weighted[i] = Mint(0) - weighted[i];
        weighted[i] *= inverse_chirp[i];
    }

    std::vector<Mint> coefficients =
        internal::geometric_middle_product(chirp, weighted);
    for (int i = 0; i < count; ++i) coefficients[i] *= inverse_chirp[i];

    std::vector<Mint> product_polynomial(count);
    product_polynomial[0] = Mint(1);
    for (int i = 1; i < count; ++i) {
        product_polynomial[i] = chirp[i] * complete_product * inverse_difference[i] *
                                inverse_difference[count - i];
        if (i & 1) product_polynomial[i] = Mint(0) - product_polynomial[i];
    }
    coefficients = convolution(coefficients, product_polynomial);
    coefficients.resize(count);

    std::reverse(coefficients.begin(), coefficients.end());
    const Mint inverse_initial = initial.inv();
    Mint inverse_initial_power = Mint(1);
    for (Mint& coefficient : coefficients) {
        coefficient *= inverse_initial_power;
        inverse_initial_power *= inverse_initial;
    }
    return Fps(std::move(coefficients));
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_GEOMETRIC_SEQUENCE_EVALUATION_HPP
