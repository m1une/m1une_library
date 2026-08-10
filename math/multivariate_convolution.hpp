#ifndef M1UNE_MATH_MULTIVARIATE_CONVOLUTION_HPP
#define M1UNE_MATH_MULTIVARIATE_CONVOLUTION_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

#include "fps/convolution.hpp"
#include "primitive_root.hpp"

namespace m1une {
namespace math {

namespace internal {

template <class T>
struct nested_vector_traits {
    using scalar_type = T;
    static constexpr int depth = 0;
};

template <class T, class Allocator>
struct nested_vector_traits<std::vector<T, Allocator>> {
    using scalar_type = typename nested_vector_traits<T>::scalar_type;
    static constexpr int depth = nested_vector_traits<T>::depth + 1;
};

template <class Nested>
void nested_vector_shape(const Nested& values, std::vector<int>& shape) {
    if constexpr (nested_vector_traits<Nested>::depth > 0) {
        assert(!values.empty());
        assert(values.size() <= std::size_t(std::numeric_limits<int>::max()));
        shape.push_back(int(values.size()));
        nested_vector_shape(values.front(), shape);
    }
}

template <class Nested, class Mint>
void flatten_nested_vector(
    const Nested& values,
    const std::vector<int>& shape,
    int level,
    std::vector<Mint>& flattened
) {
    if constexpr (nested_vector_traits<Nested>::depth == 0) {
        flattened.push_back(values);
    } else {
        assert(level < int(shape.size()));
        assert(int(values.size()) == shape[level]);
        for (const auto& child : values) {
            flatten_nested_vector(child, shape, level + 1, flattened);
        }
    }
}

template <class Nested, class Mint>
void rebuild_nested_vector(
    Nested& values,
    const std::vector<int>& shape,
    int level,
    const std::vector<Mint>& flattened,
    int& position
) {
    if constexpr (nested_vector_traits<Nested>::depth == 0) {
        assert(position < int(flattened.size()));
        values = flattened[position++];
    } else {
        assert(level < int(shape.size()));
        values.resize(shape[level]);
        for (auto& child : values) {
            rebuild_nested_vector(child, shape, level + 1, flattened, position);
        }
    }
}

template <class Nested>
std::vector<int> flatten_multivariate_inputs(
    const Nested& first,
    const Nested& second,
    std::vector<typename nested_vector_traits<Nested>::scalar_type>& flattened_first,
    std::vector<typename nested_vector_traits<Nested>::scalar_type>& flattened_second
) {
    std::vector<int> shape;
    nested_vector_shape(first, shape);
    assert(int(shape.size()) == nested_vector_traits<Nested>::depth);

    std::vector<int> second_shape;
    nested_vector_shape(second, second_shape);
    assert(second_shape == shape);

    flatten_nested_vector(first, shape, 0, flattened_first);
    flatten_nested_vector(second, shape, 0, flattened_second);
    std::reverse(shape.begin(), shape.end());
    return shape;
}

template <class Nested>
Nested rebuild_multivariate_result(
    std::vector<int> dimensions,
    const std::vector<typename nested_vector_traits<Nested>::scalar_type>& flattened
) {
    std::reverse(dimensions.begin(), dimensions.end());
    Nested result;
    int position = 0;
    rebuild_nested_vector(result, dimensions, 0, flattened, position);
    assert(position == int(flattened.size()));
    return result;
}

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

template <class Mint>
std::vector<Mint> multivariate_convolution_truncated_arbitrary_mod(
    const std::vector<int>& dimensions,
    const std::vector<Mint>& first,
    const std::vector<Mint>& second
) {
    const int variable_count = int(dimensions.size());
    const int coefficient_count = multivariate_coefficient_count(dimensions);
    assert(int(first.size()) == coefficient_count);
    assert(int(second.size()) == coefficient_count);
    if (variable_count == 0) return {first[0] * second[0]};

    const std::vector<int> color = multivariate_colors(dimensions);
    std::vector<std::vector<Mint>> colored_first(
        variable_count, std::vector<Mint>(coefficient_count)
    );
    std::vector<std::vector<Mint>> colored_second(
        variable_count, std::vector<Mint>(coefficient_count)
    );
    for (int i = 0; i < coefficient_count; i++) {
        colored_first[color[i]][i] = first[i];
        colored_second[color[i]][i] = second[i];
    }

    std::vector<std::vector<Mint>> colored_result(
        variable_count, std::vector<Mint>(coefficient_count)
    );
    for (int left = 0; left < variable_count; left++) {
        for (int right = 0; right < variable_count; right++) {
            std::vector<Mint> product =
                fps::convolution(colored_first[left], colored_second[right]);
            std::vector<Mint>& destination =
                colored_result[(left + right) % variable_count];
            for (int i = 0; i < coefficient_count; i++) {
                destination[i] += product[i];
            }
        }
    }

    std::vector<Mint> result(coefficient_count);
    for (int i = 0; i < coefficient_count; i++) {
        result[i] = colored_result[color[i]][i];
    }
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

template <
    class Nested,
    std::enable_if_t<(internal::nested_vector_traits<Nested>::depth > 0), int> = 0
>
Nested multivariate_convolution_truncated(
    const Nested& first,
    const Nested& second
) {
    using Mint = typename internal::nested_vector_traits<Nested>::scalar_type;
    std::vector<Mint> flattened_first, flattened_second;
    std::vector<int> dimensions = internal::flatten_multivariate_inputs(
        first, second, flattened_first, flattened_second
    );
    std::vector<Mint> flattened_result = multivariate_convolution_truncated(
        dimensions, flattened_first, flattened_second
    );
    return internal::rebuild_multivariate_result<Nested>(
        std::move(dimensions), flattened_result
    );
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
    bool has_all_roots = true;
    for (int dimension : dimensions) {
        if ((modulus - 1) % uint32_t(dimension) != 0) has_all_roots = false;
    }
    if (!has_all_roots) {
        std::vector<int> reduced_dimensions;
        for (int dimension : dimensions) {
            if (dimension != 1) reduced_dimensions.push_back(dimension);
        }
        if (reduced_dimensions.empty()) return {first[0] * second[0]};

        std::vector<int> widened_dimensions(reduced_dimensions.size());
        for (int i = 0; i < int(reduced_dimensions.size()); i++) {
            const int64_t widened = 2LL * reduced_dimensions[i] - 1;
            assert(widened <= std::numeric_limits<int>::max());
            widened_dimensions[i] = int(widened);
        }
        const int widened_count =
            internal::multivariate_coefficient_count(widened_dimensions);
        std::vector<Mint> widened_first(widened_count);
        std::vector<Mint> widened_second(widened_count);
        for (int index = 0; index < coefficient_count; index++) {
            int remaining = index;
            int widened_index = 0;
            int widened_stride = 1;
            for (int variable = 0; variable < int(reduced_dimensions.size()); variable++) {
                const int coordinate = remaining % reduced_dimensions[variable];
                remaining /= reduced_dimensions[variable];
                widened_index += coordinate * widened_stride;
                widened_stride *= widened_dimensions[variable];
            }
            widened_first[widened_index] = first[index];
            widened_second[widened_index] = second[index];
        }

        std::vector<Mint> widened_product =
            internal::multivariate_convolution_truncated_arbitrary_mod(
                widened_dimensions, widened_first, widened_second
            );
        std::vector<Mint> result(coefficient_count);
        for (int widened_index = 0; widened_index < widened_count; widened_index++) {
            int remaining = widened_index;
            int index = 0;
            int stride = 1;
            for (int variable = 0; variable < int(reduced_dimensions.size()); variable++) {
                const int coordinate = remaining % widened_dimensions[variable];
                remaining /= widened_dimensions[variable];
                index += (coordinate % reduced_dimensions[variable]) * stride;
                stride *= reduced_dimensions[variable];
            }
            result[index] += widened_product[widened_index];
        }
        return result;
    }

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

template <
    class Nested,
    std::enable_if_t<(internal::nested_vector_traits<Nested>::depth > 0), int> = 0
>
Nested multivariate_convolution_cyclic(
    const Nested& first,
    const Nested& second
) {
    using Mint = typename internal::nested_vector_traits<Nested>::scalar_type;
    std::vector<Mint> flattened_first, flattened_second;
    std::vector<int> dimensions = internal::flatten_multivariate_inputs(
        first, second, flattened_first, flattened_second
    );
    std::vector<Mint> flattened_result = multivariate_convolution_cyclic(
        dimensions, flattened_first, flattened_second
    );
    return internal::rebuild_multivariate_result<Nested>(
        std::move(dimensions), flattened_result
    );
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_MULTIVARIATE_CONVOLUTION_HPP
