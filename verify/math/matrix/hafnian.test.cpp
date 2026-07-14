#define PROBLEM "https://judge.yosupo.jp/problem/hafnian_of_matrix"

#include "../../../math/matrix/hafnian.hpp"
#include "../../../math/modint.hpp"

#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <vector>

namespace {

using mint = m1une::math::modint998244353;
using Matrix = m1une::matrix::Matrix<mint>;

mint naive_hafnian(const Matrix& matrix) {
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
            if (mask >> second & 1) {
                int next = mask ^ (1 << first) ^ (1 << second);
                result += matrix[first][second] * self(self, next);
            }
        }
        return memo[mask] = result;
    };
    return solve(solve, (1 << size) - 1);
}

void test_edge_cases() {
    assert(m1une::matrix::hafnian(Matrix(0, 0)) == mint(1));

    Matrix pair(2, 2);
    pair[0][1] = pair[1][0] = 9;
    assert(m1une::matrix::hafnian(pair) == mint(9));

    Matrix zero(8, 8);
    assert(m1une::matrix::hafnian(zero) == mint(0));
}

void test_randomized() {
    std::uint64_t state = 0x4d595df4d0f33173ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 300; trial++) {
        int size = 2 * int(random() % 6);
        Matrix matrix(size, size);
        for (int row = 0; row < size; row++) {
            for (int col = row + 1; col < size; col++) {
                matrix[row][col] = matrix[col][row] = int(random() % 21) - 10;
            }
        }
        assert(m1une::matrix::hafnian(matrix) == naive_hafnian(matrix));
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_edge_cases();
    test_randomized();

    int size;
    fast_input >> size;
    Matrix matrix(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) fast_input >> matrix[row][col];
    }
    fast_output << m1une::matrix::hafnian(matrix) << '\n';
}
