#ifndef M1UNE_FPS_COMPOSITION_HPP
#define M1UNE_FPS_COMPOSITION_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

#include "formal_power_series.hpp"

namespace m1une {
namespace fps {

namespace internal {

template <class Mint>
using CompositionMatrix = std::vector<std::vector<Mint>>;

template <class Mint>
CompositionMatrix<Mint> composition_convolution_2d(const CompositionMatrix<Mint>& lhs,
                                                   const CompositionMatrix<Mint>& rhs) {
    const int lhs_height = int(lhs.size());
    const int rhs_height = int(rhs.size());
    const int lhs_width = int(lhs[0].size());
    const int rhs_width = int(rhs[0].size());
    const int height = lhs_height + rhs_height - 1;
    const int width = lhs_width + rhs_width - 1;

    std::vector<Mint> flattened_lhs(std::size_t(lhs_height) * width);
    std::vector<Mint> flattened_rhs(std::size_t(rhs_height) * width);
    for (int i = 0; i < lhs_height; i++) {
        std::copy(lhs[i].begin(), lhs[i].end(),
                  flattened_lhs.begin() + std::size_t(i) * width);
    }
    for (int i = 0; i < rhs_height; i++) {
        std::copy(rhs[i].begin(), rhs[i].end(),
                  flattened_rhs.begin() + std::size_t(i) * width);
    }

    std::vector<Mint> flattened_result = convolution(flattened_lhs, flattened_rhs);
    CompositionMatrix<Mint> result(height, std::vector<Mint>(width));
    for (int i = 0; i < height; i++) {
        std::copy_n(flattened_result.begin() + std::size_t(i) * width, width,
                    result[i].begin());
    }
    return result;
}

// result[i] = sum_j kernel[j] * values[i + j]
template <class Mint>
std::vector<Mint> composition_middle_product(const std::vector<Mint>& values,
                                             const std::vector<Mint>& kernel) {
    assert(values.size() >= kernel.size() && !kernel.empty());
    const int kernel_size = int(kernel.size());
    const int result_size = int(values.size()) - kernel_size + 1;
    if (std::min(kernel_size, result_size) <= 32) {
        std::vector<Mint> result(result_size);
        for (int i = 0; i < result_size; i++) {
            for (int j = 0; j < kernel_size; j++) result[i] += kernel[j] * values[i + j];
        }
        return result;
    }

    int transform_size = 1;
    while ((transform_size << 1) <= int(values.size()) * 2 - 1) transform_size <<= 1;
    if ((Mint::mod() - 1) % uint32_t(transform_size) == 0) {
        std::vector<Mint> transformed_values(transform_size);
        std::vector<Mint> transformed_kernel(transform_size);
        std::copy(values.begin(), values.end(), transformed_values.begin());
        std::reverse_copy(kernel.begin(), kernel.end(), transformed_kernel.begin());
        ntt(transformed_values, false);
        ntt(transformed_kernel, false);
        for (int i = 0; i < transform_size; i++) transformed_values[i] *= transformed_kernel[i];
        ntt(transformed_values, true);
        return std::vector<Mint>(transformed_values.begin() + kernel_size - 1,
                                 transformed_values.begin() + int(values.size()));
    }

    std::vector<Mint> reversed_kernel(kernel.rbegin(), kernel.rend());
    std::vector<Mint> product = convolution(values, reversed_kernel);
    return std::vector<Mint>(product.begin() + kernel_size - 1,
                             product.begin() + int(values.size()));
}

}  // namespace internal

// Returns outer(inner(x)) modulo x^degree. Formal composition requires inner(0) = 0.
template <class Mint>
FormalPowerSeries<Mint> compose(const FormalPowerSeries<Mint>& outer,
                                const FormalPowerSeries<Mint>& inner, int degree = -1) {
    using Matrix = internal::CompositionMatrix<Mint>;
    if (degree < 0) degree = int(outer.size());
    assert(degree >= 0);
    if (degree == 0) return {};
    assert(inner.empty() || inner[0] == Mint(0));

    FormalPowerSeries<Mint> coefficients = outer.pre(degree);
    FormalPowerSeries<Mint> argument = inner.pre(degree);

    auto transpose_power_projection = [&](auto&& self, Matrix denominator) -> Matrix {
        const int x_degree = int(denominator.size()) - 1;
        const int y_degree = int(denominator[0].size()) - 1;
        if (x_degree == 0) {
            Matrix result(1, std::vector<Mint>(y_degree + 1));
            std::copy(coefficients.begin(), coefficients.end(), result[0].begin());
            return result;
        }

        Matrix conjugate = denominator;
        for (int i = 1; i <= x_degree; i += 2) {
            for (Mint& value : conjugate[i]) value = Mint(0) - value;
        }
        Matrix reduced = internal::composition_convolution_2d(denominator, conjugate);
        for (int i = 1; i <= x_degree / 2; i++) reduced[i] = std::move(reduced[i << 1]);
        reduced.resize(x_degree / 2 + 1);
        Matrix().swap(denominator);

        Matrix projected = self(self, std::move(reduced));
        const int block_width = 2 * y_degree + 1;
        std::vector<Mint> expanded(std::size_t(2) * (x_degree + 1) * block_width - 1);
        for (int i = 0; i < int(projected.size()); i++) {
            for (int j = 0; j < int(projected[i].size()); j++) {
                const int row = 2 * i + (x_degree & 1);
                expanded[std::size_t(row) * block_width + j] = projected[i][j];
            }
        }

        std::vector<Mint> flattened_conjugate(std::size_t(x_degree + 1) * block_width);
        for (int i = 0; i <= x_degree; i++) {
            std::copy(conjugate[i].begin(), conjugate[i].end(),
                      flattened_conjugate.begin() + std::size_t(i) * block_width);
        }
        std::vector<Mint> middle =
            internal::composition_middle_product(expanded, flattened_conjugate);

        Matrix result(x_degree + 1, std::vector<Mint>(y_degree + 1));
        for (int i = 0; i <= x_degree; i++) {
            std::copy_n(middle.begin() + std::size_t(i) * block_width, y_degree + 1,
                        result[i].begin());
        }
        return result;
    };

    Matrix denominator(degree, std::vector<Mint>(2));
    denominator[0][0] = Mint(1);
    for (int i = 0; i < degree; i++) denominator[i][1] = Mint(0) - argument[i];
    Matrix transposed =
        transpose_power_projection(transpose_power_projection, std::move(denominator));

    FormalPowerSeries<Mint> result(degree);
    for (int i = 0; i < degree; i++) result[i] = transposed[i][0];
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_COMPOSITION_HPP
