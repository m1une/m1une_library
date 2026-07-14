#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "../../../math/modint.hpp"
#include "../../../math/matrix/matrix.hpp"

#include "../../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using mint = m1une::math::modint998244353;
    int n, m, k;
    fast_input >> n >> m >> k;
    m1une::matrix::Matrix<mint> first(n, m);
    m1une::matrix::Matrix<mint> second(m, k);
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) fast_input >> first[row][col];
    }
    for (int row = 0; row < m; row++) {
        for (int col = 0; col < k; col++) fast_input >> second[row][col];
    }

    auto product = first * second;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < k; col++) {
            if (col > 0) fast_output << ' ';
            fast_output << product[row][col];
        }
        fast_output << '\n';
    }
}
