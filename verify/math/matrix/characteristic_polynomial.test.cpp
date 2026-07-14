#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include "../../../math/matrix/characteristic_polynomial.hpp"
#include "../../../math/matrix/linear_algebra.hpp"
#include "../../../math/modint.hpp"

#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <utility>
#include <vector>

namespace {

using mint = m1une::math::modint998244353;
using Matrix = m1une::matrix::Matrix<mint>;

mint evaluate(const std::vector<mint>& polynomial, mint point) {
    mint result = 0;
    for (auto iterator = polynomial.rbegin(); iterator != polynomial.rend(); ++iterator) {
        result = result * point + *iterator;
    }
    return result;
}

void check_by_evaluation(const Matrix& matrix, const std::vector<mint>& polynomial) {
    assert(polynomial.size() == std::size_t(matrix.rows() + 1));
    assert(polynomial.back() == mint(1));
    for (int value = -3; value <= 3; value++) {
        Matrix shifted = Matrix::identity(matrix.rows()) * mint(value) - matrix;
        assert(
            evaluate(polynomial, mint(value)) ==
            m1une::matrix::determinant(shifted)
        );
    }
}

void test_edge_cases() {
    Matrix empty(0, 0);
    std::vector<mint> one{mint(1)};
    assert(m1une::matrix::characteristic_polynomial(empty) == one);

    Matrix single(1, 1);
    single[0][0] = 7;
    std::vector<mint> expected{mint(-7), mint(1)};
    assert(m1une::matrix::characteristic_polynomial(single) == expected);

    Matrix zero(5, 5);
    std::vector<mint> zero_polynomial(6);
    zero_polynomial[5] = 1;
    assert(
        m1une::matrix::characteristic_polynomial(zero) == zero_polynomial
    );
}

void test_randomized() {
    std::uint64_t state = 0xb4ca731d9e6205f8ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; trial++) {
        const int size = int(random() % 7);
        Matrix matrix(size, size);
        for (mint& value : matrix.data()) {
            value = int(random() % 15) - 7;
        }
        const std::vector<mint> polynomial =
            m1une::matrix::characteristic_polynomial(matrix);
        check_by_evaluation(matrix, polynomial);
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
        for (int col = 0; col < size; col++) {
            fast_input >> matrix[row][col];
        }
    }

    const std::vector<mint> polynomial =
        m1une::matrix::characteristic_polynomial(std::move(matrix));
    for (int degree = 0; degree <= size; degree++) {
        if (degree != 0) fast_output << ' ';
        fast_output << polynomial[std::size_t(degree)];
    }
    fast_output << '\n';
}
