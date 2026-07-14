#define PROBLEM "https://judge.yosupo.jp/problem/pfaffian_of_matrix"

#include "../../../math/matrix/linear_algebra.hpp"
#include "../../../math/matrix/pfaffian.hpp"
#include "../../../math/modint.hpp"

#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <vector>

namespace {

using mint = m1une::math::modint998244353;
using Matrix = m1une::matrix::Matrix<mint>;

mint naive_pfaffian(const Matrix& matrix) {
    const int size = matrix.rows();
    std::vector<mint> memo(std::size_t(1 << size));
    std::vector<char> calculated(std::size_t(1 << size), false);
    auto solve = [&](auto&& self, int mask) -> mint {
        if (mask == 0) return mint(1);
        if (calculated[mask]) return memo[mask];
        calculated[mask] = true;
        const int first = __builtin_ctz(unsigned(mask));
        mint result = 0;
        for (int second = first + 1; second < size; second++) {
            if ((mask >> second & 1) == 0) continue;
            int next = mask ^ (1 << first) ^ (1 << second);
            mint term = matrix[first][second] * self(self, next);
            int position = __builtin_popcount(unsigned(mask & ((1 << second) - 1)));
            if (position % 2 == 1) {
                result += term;
            } else {
                result -= term;
            }
        }
        return memo[mask] = result;
    };
    return solve(solve, (1 << size) - 1);
}

void test_edge_cases() {
    assert(m1une::matrix::pfaffian(Matrix(0, 0)) == mint(1));

    Matrix pair(2, 2);
    pair[0][1] = 7;
    pair[1][0] = mint() - pair[0][1];
    assert(m1une::matrix::pfaffian(pair) == mint(7));

    Matrix zero(6, 6);
    assert(m1une::matrix::pfaffian(zero) == mint(0));
}

void test_randomized() {
    std::uint64_t state = 0x8aed2a6bb7e15162ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        int size = 2 * int(random() % 6);
        Matrix matrix(size, size);
        for (int row = 0; row < size; row++) {
            for (int col = row + 1; col < size; col++) {
                matrix[row][col] = int(random() % 21) - 10;
                matrix[col][row] = mint() - matrix[row][col];
            }
        }
        mint actual = m1une::matrix::pfaffian(matrix);
        assert(actual == naive_pfaffian(matrix));
        assert(actual * actual == m1une::matrix::determinant(matrix));
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_edge_cases();
    test_randomized();

    int half_size;
    fast_input >> half_size;
    const int size = 2 * half_size;
    Matrix matrix(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) fast_input >> matrix[row][col];
    }
    fast_output << m1une::matrix::pfaffian(std::move(matrix)) << '\n';
}
