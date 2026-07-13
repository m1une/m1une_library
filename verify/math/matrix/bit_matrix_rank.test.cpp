#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank_mod_2"

#include <iostream>
#include <string>
#include <utility>

#include "../../../math/matrix/bit_matrix.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int rows, cols;
    std::cin >> rows >> cols;
    m1une::matrix::BitMatrix matrix(rows, cols);
    std::string bits;
    for (int row = 0; row < rows; row++) {
        std::cin >> bits;
        matrix.set_row(row, bits);
    }
    std::cout << m1une::matrix::matrix_rank(std::move(matrix)) << '\n';
}
