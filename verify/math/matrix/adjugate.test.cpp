#define PROBLEM "https://judge.yosupo.jp/problem/adjugate_matrix"

#include <cassert>
#include <cstdint>

#include "../../../math/matrix/adjugate.hpp"
#include "../../../math/matrix/linear_algebra.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

namespace {

using Mint = m1une::math::modint998244353;
using Matrix = m1une::matrix::Matrix<Mint>;

Matrix naive_adjugate(const Matrix& matrix) {
    const int size = matrix.rows();
    Matrix result(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            Matrix minor(size - 1, size - 1);
            int minor_row = 0;
            for (int source_row = 0; source_row < size; source_row++) {
                if (source_row == col) continue;
                int minor_col = 0;
                for (int source_col = 0; source_col < size; source_col++) {
                    if (source_col == row) continue;
                    minor[minor_row][minor_col++] = matrix[source_row][source_col];
                }
                minor_row++;
            }
            result[row][col] = m1une::matrix::determinant(std::move(minor));
            if ((row + col) & 1) result[row][col] = Mint(0) - result[row][col];
        }
    }
    return result;
}

std::uint64_t next_random(std::uint64_t& state) {
    state ^= state << 7;
    state ^= state >> 9;
    return state;
}

void check(const Matrix& matrix) {
    const Matrix actual = m1une::matrix::adjugate(matrix);
    assert(actual == naive_adjugate(matrix));
    const Mint determinant = m1une::matrix::determinant(matrix);
    const Matrix expected = Matrix::identity(matrix.rows()) * determinant;
    assert(matrix * actual == expected);
    assert(actual * matrix == expected);
}

void focused_tests() {
    check(Matrix(0, 0));
    check(Matrix(1, 1));
    Matrix scalar(1, 1);
    scalar[0][0] = 17;
    check(scalar);

    Matrix rank_one(5, 5);
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) rank_one[row][col] = (row + 1) * (col + 3);
    }
    check(rank_one);

    std::uint64_t random = 0x4c38d91bea75260fULL;
    for (int iteration = 0; iteration < 250; iteration++) {
        const int size = int(next_random(random) % 8);
        Matrix matrix(size, size);
        for (Mint& value : matrix.data()) {
            value = int(next_random(random) % 21) - 10;
        }
        check(matrix);
    }

    for (int size = 2; size <= 7; size++) {
        for (int iteration = 0; iteration < 30; iteration++) {
            Matrix matrix = Matrix::identity(size);
            matrix[size - 1][size - 1] = Mint(0);
            for (int operation = 0; operation < size * 4; operation++) {
                int first = int(next_random(random) % size);
                int second = int(next_random(random) % size);
                if (first == second) second = (second + 1) % size;
                const Mint factor = Mint(1 + next_random(random) % 20);
                for (int col = 0; col < size; col++) {
                    matrix[first][col] += factor * matrix[second][col];
                }

                first = int(next_random(random) % size);
                second = int(next_random(random) % size);
                if (first == second) second = (second + 1) % size;
                for (int row = 0; row < size; row++) {
                    matrix[row][first] += factor * matrix[row][second];
                }
            }
            check(matrix);
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    focused_tests();

    int size;
    input >> size;
    Matrix matrix(size, size);
    for (Mint& value : matrix.data()) input >> value;
    const Matrix result = m1une::matrix::adjugate(std::move(matrix));
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (col != 0) output << ' ';
            output << result[row][col];
        }
        output << '\n';
    }
}
