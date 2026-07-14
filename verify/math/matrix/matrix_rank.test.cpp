#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"

#include "../../../math/matrix/linear_algebra.hpp"
#include "../../../math/modint.hpp"

#include "../../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using mint = m1une::math::modint998244353;
    int row_count, column_count;
    fast_input >> row_count >> column_count;
    m1une::matrix::Matrix<mint> matrix(row_count, column_count);
    for (int row = 0; row < row_count; row++) {
        for (int col = 0; col < column_count; col++) {
            fast_input >> matrix[row][col];
        }
    }
    fast_output << m1une::matrix::matrix_rank(std::move(matrix)) << '\n';
}
