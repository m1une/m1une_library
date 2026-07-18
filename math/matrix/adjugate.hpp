#ifndef M1UNE_MATRIX_ADJUGATE_HPP
#define M1UNE_MATRIX_ADJUGATE_HPP 1

#include <cassert>
#include <vector>

#include "matrix.hpp"

namespace m1une {
namespace matrix {

template <class T>
Matrix<T> adjugate(Matrix<T> matrix) {
    assert(matrix.rows() == matrix.cols());
    const int size = matrix.rows();
    Matrix<T> augmented(size, size * 2);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            augmented[row][col] = matrix[row][col];
        }
        augmented[row][size + row] = T(1);
    }

    std::vector<int> pivot_columns;
    T pivot_product = T(1);
    bool negate = false;
    for (int col = 0; col < size && int(pivot_columns.size()) < size; col++) {
        const int pivot_row = int(pivot_columns.size());
        int pivot = pivot_row;
        while (pivot < size && augmented[pivot][col] == T()) pivot++;
        if (pivot == size) continue;
        if (pivot != pivot_row) {
            augmented.swap_rows(pivot, pivot_row);
            negate = !negate;
        }

        const T pivot_value = augmented[pivot_row][col];
        pivot_product *= pivot_value;
        const T inverse_pivot = T(1) / pivot_value;
        for (int index = col; index < size; index++) {
            augmented[pivot_row][index] *= inverse_pivot;
        }
        for (int index = size; index < size * 2; index++) {
            augmented[pivot_row][index] *= inverse_pivot;
        }

        for (int row = 0; row < size; row++) {
            if (row == pivot_row || augmented[row][col] == T()) continue;
            const T factor = augmented[row][col];
            augmented[row][col] = T();
            for (int index = col + 1; index < size; index++) {
                augmented[row][index] -= factor * augmented[pivot_row][index];
            }
            for (int index = size; index < size * 2; index++) {
                augmented[row][index] -= factor * augmented[pivot_row][index];
            }
        }
        pivot_columns.push_back(col);
    }

    const int rank = int(pivot_columns.size());
    Matrix<T> result(size, size);
    if (rank + 1 < size) return result;

    if (rank == size) {
        const T determinant = negate ? T() - pivot_product : pivot_product;
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                result[row][col] = determinant * augmented[row][size + col];
            }
        }
        return result;
    }

    int free_column = 0;
    while (free_column < rank && pivot_columns[free_column] == free_column) {
        free_column++;
    }
    std::vector<T> right_null(size);
    right_null[free_column] = T(1);
    for (int row = 0; row < rank; row++) {
        right_null[pivot_columns[row]] = T() - augmented[row][free_column];
    }

    T scale = pivot_product;
    if (negate != bool((size - 1 + free_column) & 1)) scale = T() - scale;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            result[row][col] =
                scale * right_null[row] * augmented[size - 1][size + col];
        }
    }
    return result;
}

}  // namespace matrix
}  // namespace m1une

#endif  // M1UNE_MATRIX_ADJUGATE_HPP
