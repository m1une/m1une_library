#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_multiplicative_function"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../../math/modint.hpp"
#include "../../math/multiplicative_function_prefix_sum.hpp"

using Mint = m1une::math::ModInt<469762049>;

Mint solve(uint64_t n, Mint a, Mint b) {
    auto prime_power = [a, b](uint64_t prime, int exponent) {
        return a * Mint(exponent) + b * Mint(prime);
    };
    m1une::math::MultiplicativeFunctionPrefixSum<Mint, decltype(prime_power)> solver(n, prime_power);
    std::vector<Mint> prime_prefix = solver.prime_count_table();
    const std::vector<Mint> prime_sum = solver.prime_sum_table();
    for (int i = 0; i < solver.table_size(); i++) {
        prime_prefix[i] = a * prime_prefix[i] + b * prime_sum[i];
    }
    return solver.prefix_sum(prime_prefix);
}

void test_small() {
    for (uint64_t n = 0; n <= 300; n++) {
        for (uint32_t a = 0; a <= 3; a++) {
            for (uint32_t b = 0; b <= 3; b++) {
                std::vector<Mint> function(n + 1, Mint(1));
                std::vector<int> min_prime(n + 1);
                for (uint64_t value = 2; value <= n; value++) {
                    if (min_prime[value] == 0) {
                        for (uint64_t multiple = value; multiple <= n; multiple += value) {
                            if (min_prime[multiple] == 0) min_prime[multiple] = static_cast<int>(value);
                        }
                    }
                    uint64_t reduced = value;
                    int exponent = 0;
                    while (reduced % static_cast<uint64_t>(min_prime[value]) == 0) {
                        reduced /= static_cast<uint64_t>(min_prime[value]);
                        exponent++;
                    }
                    function[value] = function[reduced] *
                                      (Mint(a) * Mint(exponent) + Mint(b) * Mint(min_prime[value]));
                }
                Mint expected = 0;
                for (uint64_t value = 1; value <= n; value++) expected += function[value];
                assert(solve(n, Mint(a), Mint(b)) == expected);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_small();

    int test_count;
    std::cin >> test_count;
    while (test_count--) {
        uint64_t n;
        Mint a, b;
        std::cin >> n >> a >> b;
        std::cout << solve(n, a, b) << '\n';
    }
}
