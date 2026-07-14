#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations_mod_2"

#include "../../../utilities/fast_io.hpp"
#include <string>
#include <vector>

#include "../../../math/matrix/bit_matrix.hpp"

namespace {

void print_vector(
    const std::vector<bool>& values,
    m1une::utilities::FastOutput& fast_output
) {
    for (bool value : values) fast_output << int(value);
    fast_output << '\n';
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int equation_count, variable_count;
    fast_input >> equation_count >> variable_count;
    m1une::matrix::BitMatrix coefficients(equation_count, variable_count);
    std::string bits;
    for (int row = 0; row < equation_count; row++) {
        fast_input >> bits;
        coefficients.set_row(row, bits);
    }
    fast_input >> bits;
    std::vector<bool> constants(std::size_t(equation_count), false);
    for (int row = 0; row < equation_count; row++) {
        constants[std::size_t(row)] = bits[std::size_t(row)] == '1';
    }

    m1une::matrix::BitLinearSystemResult result =
        m1une::matrix::solve_linear_system(coefficients, constants);
    if (!result.consistent) {
        fast_output << -1 << '\n';
        return 0;
    }

    fast_output << result.nullity() << '\n';
    print_vector(result.particular_solution, fast_output);
    for (const std::vector<bool>& direction : result.nullspace_basis) {
        print_vector(direction, fast_output);
    }
}
