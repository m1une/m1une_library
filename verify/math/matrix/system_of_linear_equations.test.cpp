#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include "../../../math/matrix/linear_algebra.hpp"
#include "../../../math/modint.hpp"

#include "../../../utilities/fast_io.hpp"
#include <vector>

namespace {

using mint = m1une::math::modint998244353;

void print_vector(
    const std::vector<mint>& values,
    m1une::utilities::FastOutput& fast_output
) {
    for (int i = 0; i < int(values.size()); i++) {
        if (i != 0) fast_output << ' ';
        fast_output << values[i];
    }
    fast_output << '\n';
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int equation_count, variable_count;
    fast_input >> equation_count >> variable_count;
    m1une::matrix::Matrix<mint> coefficients(
        equation_count,
        variable_count
    );
    for (int row = 0; row < equation_count; row++) {
        for (int col = 0; col < variable_count; col++) {
            fast_input >> coefficients[row][col];
        }
    }
    std::vector<mint> constants(equation_count);
    for (mint& value : constants) fast_input >> value;

    auto result = m1une::matrix::solve_linear_system(coefficients, constants);
    if (!result.consistent) {
        fast_output << -1 << '\n';
        return 0;
    }

    fast_output << result.nullity() << '\n';
    print_vector(result.particular_solution, fast_output);
    for (const auto& basis : result.nullspace_basis) {
        print_vector(basis, fast_output);
    }
}
