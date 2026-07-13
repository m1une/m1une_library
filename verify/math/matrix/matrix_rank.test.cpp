#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"

#include "../../../math/matrix/linear_algebra.hpp"
#include "../../../math/modint.hpp"

#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;
    int row_count, column_count;
    std::cin >> row_count >> column_count;
    m1une::matrix::Matrix<mint> matrix(row_count, column_count);
    for (int row = 0; row < row_count; row++) {
        for (int col = 0; col < column_count; col++) {
            std::cin >> matrix[row][col];
        }
    }
    std::cout << m1une::matrix::matrix_rank(std::move(matrix)) << '\n';
}
