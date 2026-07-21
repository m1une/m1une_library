#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"

#include "../../math/multiplicative_function_prefix_sum.hpp"
#include "../../utilities/fast_io.hpp"

#include <cstdint>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    std::uint64_t n;
    fast_input >> n;
    auto prime_power = [](std::uint64_t, int) -> std::uint64_t {
        return 1;
    };
    using Solver = m1une::math::MultiplicativeFunctionPrefixSum<
        std::uint64_t,
        decltype(prime_power)
    >;
    Solver solver(n, prime_power);
    const auto values = solver.quotient_values();

    fast_output << values.size() - 1 << '\n';
    for (int index = int(values.size()) - 1; index >= 1; index--) {
        if (index != int(values.size()) - 1) fast_output << ' ';
        fast_output << values[index];
    }
    fast_output << '\n';
}
