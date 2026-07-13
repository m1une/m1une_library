#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include "../../../math/matrix/linear_algebra.hpp"
#include "../../../math/modint.hpp"

#include <iostream>
#include <vector>

namespace {

using mint = m1une::math::modint998244353;

void print_vector(const std::vector<mint>& values) {
    for (int i = 0; i < int(values.size()); i++) {
        if (i != 0) std::cout << ' ';
        std::cout << values[i];
    }
    std::cout << '\n';
}

}  // namespace

int main() {
    int equation_count, variable_count;
    std::cin >> equation_count >> variable_count;
    m1une::matrix::Matrix<mint> coefficients(
        equation_count,
        variable_count
    );
    for (int row = 0; row < equation_count; row++) {
        for (int col = 0; col < variable_count; col++) {
            std::cin >> coefficients[row][col];
        }
    }
    std::vector<mint> constants(equation_count);
    for (mint& value : constants) std::cin >> value;

    auto result = m1une::matrix::solve_linear_system(coefficients, constants);
    if (!result.consistent) {
        std::cout << -1 << '\n';
        return 0;
    }

    std::cout << result.nullity() << '\n';
    print_vector(result.particular_solution);
    for (const auto& basis : result.nullspace_basis) print_vector(basis);
}
