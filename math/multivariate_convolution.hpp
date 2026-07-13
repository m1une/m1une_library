#ifndef M1UNE_MATH_MULTIVARIATE_CONVOLUTION_HPP
#define M1UNE_MATH_MULTIVARIATE_CONVOLUTION_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <vector>

#include "fps/convolution.hpp"
#include "primitive_root.hpp"

namespace m1une {
namespace math {

namespace internal {

inline int multivariate_coefficient_count(const std::vector<int>& dimensions) {
    int64_t count = 1;
    for (int dimension : dimensions) {
        assert(dimension > 0);
        count *= dimension;
        assert(count <= std::numeric_limits<int>::max());
    }
    return int(count);
}

inline std::vector<int> multivariate_colors(const std::vector<int>& dimensions) {
    const int variable_count = int(dimensions.size());
    const int coefficient_count = multivariate_coefficient_count(dimensions);
    std::vector<int> color(coefficient_count);
    if (variable_count == 0) return color;

    for (int index = 0; index < coefficient_count; index++) {
        int sum = 0;
        int stride = 1;
        for (int variable = 0; variable + 1 < variable_count; variable++) {
            stride *= dimensions[variable];
            sum += index / stride;
        }
        color[index] = sum % variable_count;
    }
    return color;
}

template <class Mint>
std::vector<Mint> geometric_evaluation(
    const std::vector<Mint>& polynomial, Mint ratio
) {
    const int size = int(polynomial.size());
    if (size <= 64) {
        std::vector<Mint> result(size);
        Mint point = 1;
        for (int i = 0; i < size; i++) {
            Mint power = 1;
            for (const Mint& coefficient : polynomial) {
                result[i] += coefficient * power;
                power *= point;
            }
            point *= ratio;
        }
        return result;
    }

    auto triangular_powers = [](Mint base, int length) {
        std::vector<Mint> result(length);
        if (length == 0) return result;
        result[0] = 1;
        Mint power = 1;
        for (int i = 0; i + 1 < length; i++) {
            result[i + 1] = result[i] * power;
            power *= base;
        }
        return result;
    };

    std::vector<Mint> positive = triangular_powers(ratio, 2 * size - 1);
    std::vector<Mint> negative = triangular_powers(ratio.inv(), size);
    std::vector<Mint> scaled(polynomial);
    for (int i = 0; i < size; i++) scaled[i] *= negative[i];
    std::reverse(scaled.begin(), scaled.end());
    std::vector<Mint> product = fps::convolution(scaled, positive);

    std::vector<Mint> result(size);
    for (int i = 0; i < size; i++) result[i] = product[size - 1 + i] * negative[i];
    return result;
}

}  // namespace internal

template <class Mint>
std::vector<Mint> multivariate_convolution_truncated(
    const std::vector<int>& dimensions,
    const std::vector<Mint>& first,
    const std::vector<Mint>& second
) {
    static_assert(
        fps::internal::has_static_modulus<Mint>::value,
        "truncated multivariate convolution requires a static-modulus type"
    );
    const int variable_count = int(dimensions.size());
    const int coefficient_count = internal::multivariate_coefficient_count(dimensions);
    assert(int(first.size()) == coefficient_count);
    assert(int(second.size()) == coefficient_count);
    if (variable_count == 0) return {first[0] * second[0]};

    int64_t transform_size_64 = 1;
    while (transform_size_64 < 2LL * coefficient_count - 1) transform_size_64 <<= 1;
    assert(transform_size_64 <= std::numeric_limits<int>::max());
    const int transform_size = int(transform_size_64);
    assert((Mint::mod() - 1) % uint32_t(transform_size) == 0);

    const std::vector<int> color = internal::multivariate_colors(dimensions);
    std::vector<std::vector<Mint>> transformed_first(
        variable_count, std::vector<Mint>(transform_size)
    );
    std::vector<std::vector<Mint>> transformed_second(
        variable_count, std::vector<Mint>(transform_size)
    );
    for (int i = 0; i < coefficient_count; i++) {
        transformed_first[color[i]][i] = first[i];
        transformed_second[color[i]][i] = second[i];
    }
    for (int group = 0; group < variable_count; group++) {
        fps::internal::ntt(transformed_first[group], false);
        fps::internal::ntt(transformed_second[group], false);
    }

    std::vector<std::vector<Mint>> transformed_result(
        variable_count, std::vector<Mint>(transform_size)
    );
    for (int left = 0; left < variable_count; left++) {
        for (int right = 0; right < variable_count; right++) {
            std::vector<Mint>& destination =
                transformed_result[(left + right) % variable_count];
            const std::vector<Mint>& left_values = transformed_first[left];
            const std::vector<Mint>& right_values = transformed_second[right];
            for (int i = 0; i < transform_size; i++) {
                destination[i] += left_values[i] * right_values[i];
            }
        }
    }
    for (int group = 0; group < variable_count; group++) {
        fps::internal::ntt(transformed_result[group], true);
    }

    std::vector<Mint> result(coefficient_count);
    for (int i = 0; i < coefficient_count; i++) {
        result[i] = transformed_result[color[i]][i];
    }
    return result;
}

template <class Mint>
std::vector<Mint> multivariate_convolution_cyclic(
    const std::vector<int>& dimensions,
    const std::vector<Mint>& first,
    const std::vector<Mint>& second
) {
    const int coefficient_count = internal::multivariate_coefficient_count(dimensions);
    assert(int(first.size()) == coefficient_count);
    assert(int(second.size()) == coefficient_count);
    if (dimensions.empty()) return {first[0] * second[0]};

    const uint32_t modulus = Mint::mod();
    const uint64_t generator = primitive_root(modulus);
    assert(generator != 0);

    std::vector<Mint> transformed_first(first);
    std::vector<Mint> transformed_second(second);
    int stride = 1;
    for (int dimension : dimensions) {
        assert((modulus - 1) % uint32_t(dimension) == 0);
        const Mint root = Mint(generator).pow((modulus - 1) / dimension);
        for (int block = 0; block < coefficient_count; block += stride * dimension) {
            for (int offset = 0; offset < stride; offset++) {
                std::vector<Mint> first_line(dimension);
                std::vector<Mint> second_line(dimension);
                for (int i = 0; i < dimension; i++) {
                    first_line[i] = transformed_first[block + offset + stride * i];
                    second_line[i] = transformed_second[block + offset + stride * i];
                }
                first_line = internal::geometric_evaluation(first_line, root);
                second_line = internal::geometric_evaluation(second_line, root);
                for (int i = 0; i < dimension; i++) {
                    transformed_first[block + offset + stride * i] = first_line[i];
                    transformed_second[block + offset + stride * i] = second_line[i];
                }
            }
        }
        stride *= dimension;
    }

    for (int i = 0; i < coefficient_count; i++) {
        transformed_first[i] *= transformed_second[i];
    }

    stride = 1;
    for (int dimension : dimensions) {
        const Mint inverse_root =
            Mint(generator).pow((modulus - 1) / dimension).inv();
        for (int block = 0; block < coefficient_count; block += stride * dimension) {
            for (int offset = 0; offset < stride; offset++) {
                std::vector<Mint> line(dimension);
                for (int i = 0; i < dimension; i++) {
                    line[i] = transformed_first[block + offset + stride * i];
                }
                line = internal::geometric_evaluation(line, inverse_root);
                for (int i = 0; i < dimension; i++) {
                    transformed_first[block + offset + stride * i] = line[i];
                }
            }
        }
        stride *= dimension;
    }

    const Mint inverse_size = Mint(coefficient_count).inv();
    for (Mint& value : transformed_first) value *= inverse_size;
    return transformed_first;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_MULTIVARIATE_CONVOLUTION_HPP
