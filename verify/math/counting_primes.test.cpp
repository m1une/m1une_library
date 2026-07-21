#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"

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
    const auto count = solver.prime_count_table();
    fast_output << count[solver.index(n)] << '\n';
}
