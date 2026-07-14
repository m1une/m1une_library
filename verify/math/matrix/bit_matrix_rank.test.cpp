#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank_mod_2"

#include "../../../utilities/fast_io.hpp"
#include <string>
#include <utility>

#include "../../../math/matrix/bit_matrix.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int rows, cols;
    fast_input >> rows >> cols;
    m1une::matrix::BitMatrix matrix(rows, cols);
    std::string bits;
    for (int row = 0; row < rows; row++) {
        fast_input >> bits;
        matrix.set_row(row, bits);
    }
    fast_output << m1une::matrix::matrix_rank(std::move(matrix)) << '\n';
}
