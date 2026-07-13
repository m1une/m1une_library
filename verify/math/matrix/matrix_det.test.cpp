#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include "../../../math/matrix/linear_algebra.hpp"
#include "../../../math/modint.hpp"

#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;
    int size;
    std::cin >> size;
    m1une::matrix::Matrix<mint> matrix(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) std::cin >> matrix[row][col];
    }
    std::cout << m1une::matrix::determinant(std::move(matrix)) << '\n';
}
