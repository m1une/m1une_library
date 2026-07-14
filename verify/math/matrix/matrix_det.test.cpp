#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include "../../../math/matrix/linear_algebra.hpp"
#include "../../../math/modint.hpp"

#include "../../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using mint = m1une::math::modint998244353;
    int size;
    fast_input >> size;
    m1une::matrix::Matrix<mint> matrix(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) fast_input >> matrix[row][col];
    }
    fast_output << m1une::matrix::determinant(std::move(matrix)) << '\n';
}
