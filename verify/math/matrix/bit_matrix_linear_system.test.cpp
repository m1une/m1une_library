#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations_mod_2"

#include <iostream>
#include <string>
#include <vector>

#include "../../../math/matrix/bit_matrix.hpp"

namespace {

void print_vector(const std::vector<bool>& values) {
    for (bool value : values) std::cout << int(value);
    std::cout << '\n';
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int equation_count, variable_count;
    std::cin >> equation_count >> variable_count;
    m1une::matrix::BitMatrix coefficients(equation_count, variable_count);
    std::string bits;
    for (int row = 0; row < equation_count; row++) {
        std::cin >> bits;
        coefficients.set_row(row, bits);
    }
    std::cin >> bits;
    std::vector<bool> constants(std::size_t(equation_count), false);
    for (int row = 0; row < equation_count; row++) {
        constants[std::size_t(row)] = bits[std::size_t(row)] == '1';
    }

    m1une::matrix::BitLinearSystemResult result =
        m1une::matrix::solve_linear_system(coefficients, constants);
    if (!result.consistent) {
        std::cout << -1 << '\n';
        return 0;
    }

    std::cout << result.nullity() << '\n';
    print_vector(result.particular_solution);
    for (const std::vector<bool>& direction : result.nullspace_basis) {
        print_vector(direction);
    }
}
