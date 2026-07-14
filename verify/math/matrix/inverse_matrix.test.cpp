#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include "../../../math/modint.hpp"
#include "../../../math/matrix/linear_algebra.hpp"

#include "../../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using mint = m1une::math::modint998244353;
    int n;
    fast_input >> n;
    m1une::matrix::Matrix<mint> matrix(n, n);
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) fast_input >> matrix[row][col];
    }

    auto result = m1une::matrix::inverse(matrix);
    if (!result.has_value()) {
        fast_output << -1 << '\n';
        return 0;
    }
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (col > 0) fast_output << ' ';
            fast_output << (*result)[row][col];
        }
        fast_output << '\n';
    }
}
