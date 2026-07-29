#ifndef M1UNE_MATROID_LINEAR_MATROID_INTERSECTION_HPP
#define M1UNE_MATROID_LINEAR_MATROID_INTERSECTION_HPP 1

#include <cassert>
#include <chrono>
#include <cstdint>
#include <utility>
#include <vector>

namespace m1une {
namespace matroid {

namespace internal {

inline std::uint64_t linear_matroid_intersection_random() {
    static std::uint64_t state = std::uint64_t(
        std::chrono::steady_clock::now().time_since_epoch().count());
    state += 0x9e3779b97f4a7c15ULL;
    std::uint64_t value = state;
    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
    return value ^ (value >> 31);
}

template <class Field>
int linear_matroid_intersection_matrix_rank(
    std::vector<std::vector<Field>> matrix) {
    const int row_count = int(matrix.size());
    const int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    int rank = 0;
    for (int column = 0; column < column_count && rank < row_count; column++) {
        int pivot = rank;
        while (pivot < row_count && matrix[pivot][column] == Field(0)) pivot++;
        if (pivot == row_count) continue;
        std::swap(matrix[rank], matrix[pivot]);

        Field inverse = Field(1) / matrix[rank][column];
        for (int j = column; j < column_count; j++) matrix[rank][j] *= inverse;
        for (int row = rank + 1; row < row_count; row++) {
            if (matrix[row][column] == Field(0)) continue;
            Field factor = matrix[row][column];
            for (int j = column; j < column_count; j++) {
                matrix[row][j] -= factor * matrix[rank][j];
            }
        }
        rank++;
    }
    return rank;
}

}  // namespace internal

template <class Field>
int linear_matroid_intersection_size_with_weights(
    const std::vector<std::vector<Field>>& first_vectors,
    const std::vector<std::vector<Field>>& second_vectors,
    const std::vector<Field>& weights) {
    const int ground_size = int(first_vectors.size());
    assert(int(second_vectors.size()) == ground_size);
    assert(int(weights.size()) == ground_size);
    if (ground_size == 0) return 0;

    const int first_dimension = int(first_vectors[0].size());
    const int second_dimension = int(second_vectors[0].size());
#ifndef NDEBUG
    for (const auto& vector : first_vectors) {
        assert(int(vector.size()) == first_dimension);
    }
    for (const auto& vector : second_vectors) {
        assert(int(vector.size()) == second_dimension);
    }
#endif

    const bool transpose = second_dimension < first_dimension;
    const int row_count = transpose ? second_dimension : first_dimension;
    const int column_count = transpose ? first_dimension : second_dimension;
    std::vector<std::vector<Field>> matrix(
        row_count, std::vector<Field>(column_count, Field(0)));

    for (int element = 0; element < ground_size; element++) {
        const auto& row_vector =
            transpose ? second_vectors[element] : first_vectors[element];
        const auto& column_vector =
            transpose ? first_vectors[element] : second_vectors[element];
        for (int row = 0; row < row_count; row++) {
            Field coefficient = weights[element] * row_vector[row];
            if (coefficient == Field(0)) continue;
            for (int column = 0; column < column_count; column++) {
                matrix[row][column] += coefficient * column_vector[column];
            }
        }
    }
    return internal::linear_matroid_intersection_matrix_rank(std::move(matrix));
}

template <class Field, class RandomNumberGenerator>
int linear_matroid_intersection_size(
    const std::vector<std::vector<Field>>& first_vectors,
    const std::vector<std::vector<Field>>& second_vectors,
    RandomNumberGenerator& random) {
    assert(first_vectors.size() == second_vectors.size());
    std::vector<Field> weights(first_vectors.size());
    for (Field& weight : weights) weight = Field(random());
    return linear_matroid_intersection_size_with_weights(
        first_vectors, second_vectors, weights);
}

template <class Field>
int linear_matroid_intersection_size(
    const std::vector<std::vector<Field>>& first_vectors,
    const std::vector<std::vector<Field>>& second_vectors) {
    assert(first_vectors.size() == second_vectors.size());
    std::vector<Field> weights(first_vectors.size());
    for (Field& weight : weights) {
        weight = Field(internal::linear_matroid_intersection_random());
    }
    return linear_matroid_intersection_size_with_weights(
        first_vectors, second_vectors, weights);
}

}  // namespace matroid
}  // namespace m1une

#endif  // M1UNE_MATROID_LINEAR_MATROID_INTERSECTION_HPP
