#ifndef M1UNE_MATRIX_PFAFFIAN_HPP
#define M1UNE_MATRIX_PFAFFIAN_HPP 1

#include <cassert>
#include <utility>

#include "matrix.hpp"

namespace m1une {
namespace matrix {

// Returns the Pfaffian of an even-dimensional alternating matrix over a field.
template <class T>
T pfaffian(Matrix<T> matrix) {
    assert(matrix.rows() == matrix.cols());
    const int size = matrix.rows();
    assert(size % 2 == 0);

#ifndef NDEBUG
    for (int row = 0; row < size; row++) {
        assert(matrix[row][row] == T());
        for (int col = row + 1; col < size; col++) {
            assert(matrix[row][col] == T() - matrix[col][row]);
        }
    }
#endif

    T result = T(1);
    for (int first = 0; first < size; first += 2) {
        int pivot = first + 1;
        while (pivot < size && matrix[first][pivot] == T()) pivot++;
        if (pivot == size) return T();

        if (pivot != first + 1) {
            matrix.swap_rows(pivot, first + 1);
            for (int row = 0; row < size; row++) {
                std::swap(matrix[row][pivot], matrix[row][first + 1]);
            }
            result = T() - result;
        }

        const int second = first + 1;
        const T pivot_value = matrix[first][second];
        result *= pivot_value;
        const T inverse_pivot = T(1) / pivot_value;

        for (int row = second + 1; row < size; row++) {
            for (int col = row + 1; col < size; col++) {
                matrix[row][col] +=
                    (matrix[second][row] * matrix[first][col] -
                     matrix[first][row] * matrix[second][col]) *
                    inverse_pivot;
                matrix[col][row] = T() - matrix[row][col];
            }
        }
    }
    return result;
}

}  // namespace matrix
}  // namespace m1une

#endif  // M1UNE_MATRIX_PFAFFIAN_HPP
