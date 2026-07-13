#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "../../../math/matrix/bit_matrix.hpp"

namespace {

using m1une::matrix::BitMatrix;

BitMatrix naive_product(const BitMatrix& first, const BitMatrix& second) {
    assert(first.cols() == second.rows());
    BitMatrix result(first.rows(), second.cols());
    for (int row = 0; row < first.rows(); row++) {
        for (int col = 0; col < second.cols(); col++) {
            bool value = false;
            for (int middle = 0; middle < first.cols(); middle++) {
                value ^= first.get(row, middle) && second.get(middle, col);
            }
            result.set(row, col, value);
        }
    }
    return result;
}

bool satisfies(
    const BitMatrix& matrix,
    const std::vector<bool>& solution,
    const std::vector<bool>& constants
) {
    for (int row = 0; row < matrix.rows(); row++) {
        bool value = false;
        for (int col = 0; col < matrix.cols(); col++) {
            value ^= matrix.get(row, col) && solution[std::size_t(col)];
        }
        if (value != constants[std::size_t(row)]) return false;
    }
    return true;
}

void test_basic() {
    BitMatrix filled(2, 70, true);
    assert(filled.row_string(0) == std::string(70, '1'));
    filled[0][0] = false;
    filled[0][1] = filled[0][0];
    filled.flip(0, 0);
    filled.reset(0, 2);
    assert(filled.get(0, 0));
    assert(!filled.get(0, 1));
    assert(!filled.get(0, 2));

    BitMatrix partial(2, 70);
    partial.set_row(1, std::string(70, '1'));
    partial.xor_rows(0, 1, 65);
    for (int col = 0; col < 70; col++) {
        assert(partial.get(0, col) == (65 <= col));
    }
    partial.clear();
    assert(partial == BitMatrix(2, 70));

    BitMatrix transition(2, 2);
    transition.set_row(0, "11");
    transition.set_row(1, "10");
    BitMatrix repeated = BitMatrix::identity(2);
    for (int i = 0; i < 13; i++) repeated *= transition;
    assert(transition.pow(13) == repeated);
    assert(transition + transition == BitMatrix(2, 2));
    assert(transition - transition == BitMatrix(2, 2));
    assert((transition ^ transition) == BitMatrix(2, 2));
}

void test_randomized() {
    std::uint64_t state = 0x9e3779b97f4a7c15ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int test = 0; test < 300; test++) {
        const int rows = int(random() % 10);
        const int middle = int(random() % 10);
        const int cols = int(random() % 10);
        BitMatrix first(rows, middle);
        BitMatrix second(middle, cols);
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < middle; col++) {
                first[row][col] = (random() & 1) != 0;
            }
        }
        for (int row = 0; row < middle; row++) {
            for (int col = 0; col < cols; col++) {
                second[row][col] = (random() & 1) != 0;
            }
        }
        assert(first * second == naive_product(first, second));
        assert(first.transposed().transposed() == first);

        if (rows == middle) {
            std::optional<BitMatrix> inverse = m1une::matrix::inverse(first);
            assert(inverse.has_value() == m1une::matrix::determinant(first));
            if (inverse) {
                assert(first * *inverse == BitMatrix::identity(rows));
                assert(*inverse * first == BitMatrix::identity(rows));
            }
        }

        std::vector<bool> constants(std::size_t(rows), false);
        for (int row = 0; row < rows; row++) {
            constants[std::size_t(row)] = (random() & 1) != 0;
        }
        m1une::matrix::BitLinearSystemResult solved =
            m1une::matrix::solve_linear_system(first, constants);
        bool brute_consistent = false;
        if (middle <= 9) {
            for (int mask = 0; mask < (1 << middle); mask++) {
                std::vector<bool> candidate(std::size_t(middle), false);
                for (int col = 0; col < middle; col++) {
                    candidate[std::size_t(col)] = (mask >> col) & 1;
                }
                brute_consistent |= satisfies(first, candidate, constants);
            }
        }
        assert(solved.consistent == brute_consistent);
        if (solved.consistent) {
            assert(satisfies(first, solved.particular_solution, constants));
            std::vector<bool> zero(std::size_t(rows), false);
            for (const std::vector<bool>& direction : solved.nullspace_basis) {
                assert(satisfies(first, direction, zero));
            }
            assert(solved.nullity() == middle - solved.rank());
        }
    }
}

BitMatrix read_matrix(int rows, int cols) {
    BitMatrix matrix(rows, cols);
    std::string bits;
    for (int row = 0; row < rows; row++) {
        std::cin >> bits;
        matrix.set_row(row, bits);
    }
    return matrix;
}

}  // namespace

int main() {
    test_basic();
    test_randomized();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int rows, middle, cols;
    std::cin >> rows >> middle >> cols;
    BitMatrix first = read_matrix(rows, middle);
    BitMatrix second = read_matrix(middle, cols);
    BitMatrix result = first * second;
    for (int row = 0; row < rows; row++) {
        std::cout << result.row_string(row) << '\n';
    }
}
