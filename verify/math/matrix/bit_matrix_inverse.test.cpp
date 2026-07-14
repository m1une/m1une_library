#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix_mod_2"

#include "../../../utilities/fast_io.hpp"
#include <optional>
#include <string>

#include "../../../math/matrix/bit_matrix.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int size;
    fast_input >> size;
    m1une::matrix::BitMatrix matrix(size, size);
    std::string bits;
    for (int row = 0; row < size; row++) {
        fast_input >> bits;
        matrix.set_row(row, bits);
    }

    std::optional<m1une::matrix::BitMatrix> result =
        m1une::matrix::inverse(matrix);
    if (!result) {
        fast_output << -1 << '\n';
        return 0;
    }
    for (int row = 0; row < size; row++) {
        fast_output << result->row_string(row) << '\n';
    }
}
