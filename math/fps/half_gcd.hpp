#ifndef M1UNE_FPS_HALF_GCD_HPP
#define M1UNE_FPS_HALF_GCD_HPP 1

#include <cassert>
#include <optional>
#include <utility>

#include "formal_power_series.hpp"

namespace m1une {
namespace fps {

template <class Mint>
struct PolynomialMatrix2x2 {
    using Fps = FormalPowerSeries<Mint>;

    Fps a00;
    Fps a01;
    Fps a10;
    Fps a11;

    static PolynomialMatrix2x2 identity() {
        return PolynomialMatrix2x2{Fps(1, Mint(1)), Fps(), Fps(), Fps(1, Mint(1))};
    }

    std::pair<Fps, Fps> apply(const Fps& first, const Fps& second) const {
        Fps result_first = a00 * first + a01 * second;
        Fps result_second = a10 * first + a11 * second;
        result_first.shrink();
        result_second.shrink();
        return std::make_pair(std::move(result_first), std::move(result_second));
    }

    friend PolynomialMatrix2x2 operator*(const PolynomialMatrix2x2& lhs,
                                          const PolynomialMatrix2x2& rhs) {
        PolynomialMatrix2x2 result;
        result.a00 = lhs.a00 * rhs.a00 + lhs.a01 * rhs.a10;
        result.a01 = lhs.a00 * rhs.a01 + lhs.a01 * rhs.a11;
        result.a10 = lhs.a10 * rhs.a00 + lhs.a11 * rhs.a10;
        result.a11 = lhs.a10 * rhs.a01 + lhs.a11 * rhs.a11;
        result.a00.shrink();
        result.a01.shrink();
        result.a10.shrink();
        result.a11.shrink();
        return result;
    }
};

namespace internal {

template <class Mint>
void polynomial_euclidean_step(PolynomialMatrix2x2<Mint>& matrix,
                               std::pair<FormalPowerSeries<Mint>,
                                         FormalPowerSeries<Mint>>& values) {
    using Fps = FormalPowerSeries<Mint>;
    assert(!values.second.empty());

    auto division = values.first.divmod(values.second);
    Fps next_a10 = matrix.a00 - matrix.a10 * division.first;
    Fps next_a11 = matrix.a01 - matrix.a11 * division.first;
    next_a10.shrink();
    next_a11.shrink();

    matrix.a00 = std::move(matrix.a10);
    matrix.a01 = std::move(matrix.a11);
    matrix.a10 = std::move(next_a10);
    matrix.a11 = std::move(next_a11);
    values.first = std::move(values.second);
    values.second = std::move(division.second);
}

template <class Mint>
PolynomialMatrix2x2<Mint> half_gcd_impl(
    std::pair<FormalPowerSeries<Mint>, FormalPowerSeries<Mint>> values) {
    using Matrix = PolynomialMatrix2x2<Mint>;

    const int first_size = int(values.first.size());
    const int half_size = (first_size + 1) / 2;
    if (int(values.second.size()) <= half_size) return Matrix::identity();

    Matrix first_matrix =
        half_gcd_impl<Mint>(std::make_pair(values.first >> half_size, values.second >> half_size));
    values = first_matrix.apply(values.first, values.second);
    if (int(values.second.size()) <= half_size) return first_matrix;

    polynomial_euclidean_step(first_matrix, values);
    if (int(values.second.size()) <= half_size) return first_matrix;

    const int first_degree = int(values.first.size()) - 1;
    const int shift = 2 * half_size - first_degree;
    assert(shift >= 0);
    values.first >>= shift;
    values.second >>= shift;
    return half_gcd_impl<Mint>(std::move(values)) * first_matrix;
}

template <class Mint>
PolynomialMatrix2x2<Mint> polynomial_gcd_matrix(FormalPowerSeries<Mint> first,
                                                FormalPowerSeries<Mint> second) {
    using Matrix = PolynomialMatrix2x2<Mint>;
    first.shrink();
    second.shrink();

    if (first.size() < second.size()) {
        Matrix result = polynomial_gcd_matrix(std::move(second), std::move(first));
        std::swap(result.a00, result.a01);
        std::swap(result.a10, result.a11);
        return result;
    }

    std::pair<FormalPowerSeries<Mint>, FormalPowerSeries<Mint>> values(
        std::move(first), std::move(second));
    Matrix result = Matrix::identity();
    while (true) {
        Matrix block = half_gcd_impl<Mint>(values);
        values = block.apply(values.first, values.second);
        if (values.second.empty()) return block * result;

        polynomial_euclidean_step(block, values);
        if (values.second.empty()) return block * result;
        result = block * result;
    }
}

}  // namespace internal

template <class Mint>
PolynomialMatrix2x2<Mint> half_gcd(FormalPowerSeries<Mint> first,
                                   FormalPowerSeries<Mint> second) {
    first.shrink();
    second.shrink();
    assert(first.size() >= second.size());
    return internal::half_gcd_impl<Mint>(std::make_pair(std::move(first), std::move(second)));
}

template <class Mint>
struct PolynomialExtendedGcdResult {
    FormalPowerSeries<Mint> gcd;
    FormalPowerSeries<Mint> x;
    FormalPowerSeries<Mint> y;
};

template <class Mint>
PolynomialExtendedGcdResult<Mint> polynomial_extended_gcd(
    const FormalPowerSeries<Mint>& first, const FormalPowerSeries<Mint>& second) {
    PolynomialMatrix2x2<Mint> matrix = internal::polynomial_gcd_matrix(first, second);
    auto values = matrix.apply(first, second);

    if (!values.first.empty()) {
        const Mint inverse_leading = values.first.back().inv();
        values.first *= inverse_leading;
        matrix.a00 *= inverse_leading;
        matrix.a01 *= inverse_leading;
    }
    return PolynomialExtendedGcdResult<Mint>{std::move(values.first), std::move(matrix.a00),
                                             std::move(matrix.a01)};
}

template <class Mint>
FormalPowerSeries<Mint> polynomial_gcd(const FormalPowerSeries<Mint>& first,
                                       const FormalPowerSeries<Mint>& second) {
    return polynomial_extended_gcd(first, second).gcd;
}

template <class Mint>
std::optional<FormalPowerSeries<Mint>> polynomial_inv_mod(
    const FormalPowerSeries<Mint>& polynomial, FormalPowerSeries<Mint> modulus) {
    modulus.shrink();
    assert(!modulus.empty());
    auto result = polynomial_extended_gcd(polynomial, modulus);
    if (result.gcd.size() != 1) return std::nullopt;
    return result.x % modulus;
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_HALF_GCD_HPP
