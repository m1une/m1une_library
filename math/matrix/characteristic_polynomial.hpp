#ifndef M1UNE_MATRIX_CHARACTERISTIC_POLYNOMIAL_HPP
#define M1UNE_MATRIX_CHARACTERISTIC_POLYNOMIAL_HPP 1

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

#include "matrix.hpp"

namespace m1une {
namespace matrix {

template <class T>
std::vector<T> characteristic_polynomial(Matrix<T> matrix) {
    assert(matrix.rows() == matrix.cols());
    const int size = matrix.rows();

    for (int col = 0; col + 2 < size; col++) {
        int pivot = col + 1;
        while (pivot < size && matrix[pivot][col] == T()) pivot++;
        if (pivot == size) continue;

        if (pivot != col + 1) {
            matrix.swap_rows(pivot, col + 1);
            for (int row = 0; row < size; row++) {
                std::swap(matrix[row][pivot], matrix[row][col + 1]);
            }
        }

        const T inverse_pivot = T(1) / matrix[col + 1][col];
        for (int row = col + 2; row < size; row++) {
            if (matrix[row][col] == T()) continue;
            const T factor = matrix[row][col] * inverse_pivot;
            for (int j = col; j < size; j++) {
                matrix[row][j] -= factor * matrix[col + 1][j];
            }
            for (int i = 0; i < size; i++) {
                matrix[i][col + 1] += factor * matrix[i][row];
            }
        }
    }

    std::vector<std::vector<T>> polynomial(std::size_t(size + 1));
    polynomial[0].assign(1, T(1));
    for (int leading_size = 1; leading_size <= size; leading_size++) {
        const int last = leading_size - 1;
        polynomial[std::size_t(leading_size)].assign(
            std::size_t(leading_size + 1),
            T()
        );
        const std::vector<T>& previous =
            polynomial[std::size_t(leading_size - 1)];
        std::vector<T>& current = polynomial[std::size_t(leading_size)];

        for (int degree = 0; degree < leading_size; degree++) {
            current[std::size_t(degree)] -=
                previous[std::size_t(degree)] * matrix[last][last];
            current[std::size_t(degree + 1)] +=
                previous[std::size_t(degree)];
        }

        T subdiagonal_product = T(1);
        for (int row = last - 1; row >= 0; row--) {
            subdiagonal_product *= matrix[row + 1][row];
            const T factor = subdiagonal_product * matrix[row][last];
            if (factor == T()) continue;
            for (int degree = 0; degree <= row; degree++) {
                current[std::size_t(degree)] -=
                    factor * polynomial[std::size_t(row)][std::size_t(degree)];
            }
        }
    }
    return polynomial[std::size_t(size)];
}

}  // namespace matrix
}  // namespace m1une

#endif  // M1UNE_MATRIX_CHARACTERISTIC_POLYNOMIAL_HPP
