#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <numeric>
#include <vector>

#include "../../../math/matrix/determinant_mod.hpp"
#include "../../../utilities/fast_io.hpp"

namespace {

template <class Integer>
std::uint64_t naive_determinant_mod(const m1une::matrix::Matrix<Integer>& matrix,
                                    std::uint64_t modulus) {
    const int size = matrix.rows();
    std::vector<int> permutation(size);
    std::iota(permutation.begin(), permutation.end(), 0);
    std::uint64_t result = 0;
    do {
        std::uint64_t product = std::uint64_t(1) % modulus;
        int inversions = 0;
        for (int row = 0; row < size; row++) {
            product = std::uint64_t(
                static_cast<unsigned __int128>(product) *
                m1une::matrix::detail::determinant_normalize(
                    matrix[row][permutation[row]], modulus) %
                modulus);
            for (int previous = 0; previous < row; previous++) {
                inversions += permutation[previous] > permutation[row];
            }
        }
        if (inversions & 1) {
            result = std::uint64_t(
                (static_cast<unsigned __int128>(result) + modulus - product) %
                modulus);
        } else {
            result = std::uint64_t(
                (static_cast<unsigned __int128>(result) + product) % modulus);
        }
    } while (std::next_permutation(permutation.begin(), permutation.end()));
    return result;
}

std::uint64_t next_random(std::uint64_t& state) {
    state ^= state << 7;
    state ^= state >> 9;
    return state;
}

void focused_tests() {
    using Matrix = m1une::matrix::Matrix<long long>;
    assert(m1une::matrix::determinant_mod(Matrix(0, 0), 12) == 1);
    assert(m1une::matrix::determinant_mod(Matrix(0, 0), 1) == 0);

    Matrix nonunit(2, 2);
    nonunit[0][0] = 2;
    nonunit[0][1] = 3;
    nonunit[1][0] = 4;
    nonunit[1][1] = 5;
    assert(m1une::matrix::determinant_mod(nonunit, 12) == 10);

    m1une::matrix::Matrix<std::uint64_t> wide(2, 2);
    wide[0][0] = std::numeric_limits<std::uint64_t>::max();
    wide[0][1] = std::numeric_limits<std::uint64_t>::max() - 1;
    wide[1][0] = std::numeric_limits<std::uint64_t>::max() - 2;
    wide[1][1] = std::numeric_limits<std::uint64_t>::max() - 3;
    constexpr std::uint64_t wide_modulus = 18446744073709551557ULL;
    assert(m1une::matrix::determinant_mod(wide, wide_modulus) ==
           naive_determinant_mod(wide, wide_modulus));

    std::uint64_t random = 0xa7b4c39580ed162fULL;
    for (int iteration = 0; iteration < 400; iteration++) {
        const int size = int(next_random(random) % 7);
        const std::uint64_t modulus = 1 + next_random(random) % 200;
        Matrix matrix(size, size);
        for (long long& value : matrix.data()) {
            value = static_cast<long long>(next_random(random) % 201) - 100;
        }
        assert(m1une::matrix::determinant_mod(matrix, modulus) ==
               naive_determinant_mod(matrix, modulus));
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    focused_tests();

    int size;
    std::uint64_t modulus;
    input >> size >> modulus;
    m1une::matrix::Matrix<std::uint64_t> matrix(size, size);
    for (std::uint64_t& value : matrix.data()) input >> value;
    output << m1une::matrix::determinant_mod(matrix, modulus) << '\n';
}
