#ifndef M1UNE_MATRIX_HAFNIAN_HPP
#define M1UNE_MATRIX_HAFNIAN_HPP 1

#include <cassert>
#include <utility>
#include <vector>

#include "matrix.hpp"

namespace m1une {
namespace matrix {
namespace internal {

template <class T>
class HafnianSolver {
    using Polynomial = std::vector<T>;
    using PolynomialMatrix = std::vector<std::vector<Polynomial>>;

    int _degree;

    void add_shifted_product(Polynomial& result, const Polynomial& first,
                             const Polynomial& second) const {
        for (int first_degree = 0; first_degree < _degree; first_degree++) {
            for (int second_degree = 0;
                 first_degree + second_degree + 1 < _degree;
                 second_degree++) {
                result[first_degree + second_degree + 1] +=
                    first[first_degree] * second[second_degree];
            }
        }
    }

    Polynomial solve(PolynomialMatrix matrix) const {
        if (matrix.empty()) {
            Polynomial result(_degree);
            result[0] = T(1);
            return result;
        }

        std::vector<Polynomial> first = std::move(matrix.back());
        matrix.pop_back();
        std::vector<Polynomial> second = std::move(matrix.back());
        matrix.pop_back();
        const int remaining = int(matrix.size());
        Polynomial first_to_pair = std::move(first[remaining]);

        Polynomial result = solve(matrix);
        for (T& coefficient : result) coefficient = T() - coefficient;

        for (int row = 0; row < remaining; row++) {
            for (int col = 0; col < row; col++) {
                add_shifted_product(matrix[row][col], first[row], second[col]);
                add_shifted_product(matrix[row][col], second[row], first[col]);
            }
        }

        Polynomial with_connections = solve(std::move(matrix));
        add_shifted_product(result, first_to_pair, with_connections);
        for (int degree = 0; degree < _degree; degree++) {
            result[degree] += with_connections[degree];
        }
        return result;
    }

   public:
    explicit HafnianSolver(int size) : _degree(size / 2 + 1) {}

    T operator()(const Matrix<T>& matrix) const {
        const int size = matrix.rows();
        PolynomialMatrix polynomial_matrix(size);
        for (int row = 0; row < size; row++) {
            polynomial_matrix[row].assign(row, Polynomial(_degree));
            for (int col = 0; col < row; col++) {
                polynomial_matrix[row][col][0] = matrix[row][col];
            }
        }
        return solve(std::move(polynomial_matrix)).back();
    }
};

}  // namespace internal

// Returns the hafnian of an even-dimensional symmetric zero-diagonal matrix.
template <class T>
T hafnian(const Matrix<T>& matrix) {
    assert(matrix.rows() == matrix.cols());
    const int size = matrix.rows();
    assert(size % 2 == 0);

#ifndef NDEBUG
    for (int row = 0; row < size; row++) {
        assert(matrix[row][row] == T());
        for (int col = row + 1; col < size; col++) {
            assert(matrix[row][col] == matrix[col][row]);
        }
    }
#endif

    return internal::HafnianSolver<T>(size)(matrix);
}

}  // namespace matrix
}  // namespace m1une

#endif  // M1UNE_MATRIX_HAFNIAN_HPP
