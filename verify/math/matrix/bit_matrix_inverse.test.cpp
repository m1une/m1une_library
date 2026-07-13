#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix_mod_2"

#include <iostream>
#include <optional>
#include <string>

#include "../../../math/matrix/bit_matrix.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;
    m1une::matrix::BitMatrix matrix(size, size);
    std::string bits;
    for (int row = 0; row < size; row++) {
        std::cin >> bits;
        matrix.set_row(row, bits);
    }

    std::optional<m1une::matrix::BitMatrix> result =
        m1une::matrix::inverse(matrix);
    if (!result) {
        std::cout << -1 << '\n';
        return 0;
    }
    for (int row = 0; row < size; row++) {
        std::cout << result->row_string(row) << '\n';
    }
}
