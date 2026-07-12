#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../../math/binomial_coefficient_mod.hpp"

namespace {

void test_against_pascal_triangle() {
    constexpr int maximum = 60;
    for (uint32_t modulus = 1; modulus <= 100; modulus++) {
        m1une::math::BinomialCoefficientMod combinations(modulus);
        assert(combinations.modulus() == modulus);

        std::vector<std::vector<uint32_t>> binom(maximum + 1);
        for (int n = 0; n <= maximum; n++) {
            binom[n].resize(n + 1);
            binom[n][0] = 1 % modulus;
            binom[n][n] = 1 % modulus;
            for (int k = 1; k < n; k++) {
                binom[n][k] = (binom[n - 1][k - 1] + binom[n - 1][k]) % modulus;
            }
            for (int k = 0; k <= n; k++) {
                assert(combinations.binom(n, k) == binom[n][k]);
                assert(combinations(n, k) == binom[n][k]);
            }
            assert(combinations.binom(n, uint64_t(n) + 1) == 0);
        }
    }
}

void test_large_arguments() {
    constexpr uint64_t n = 1000000000000000000ULL;
    for (uint32_t modulus : {1U, 2U, 8U, 9U, 12U, 999983U, 1000000U}) {
        m1une::math::ArbitraryModBinomialCoefficient combinations(modulus);
        assert(combinations(n, 0) == 1 % modulus);
        assert(combinations(n, 1) == n % modulus);
        assert(combinations(n, n) == 1 % modulus);
        assert(combinations(n, 123456789) ==
               combinations(n, n - 123456789));
    }
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_against_pascal_triangle();
    test_large_arguments();

    int query_count;
    uint32_t modulus;
    std::cin >> query_count >> modulus;
    m1une::math::BinomialCoefficientMod combinations(modulus);
    while (query_count--) {
        uint64_t n, k;
        std::cin >> n >> k;
        std::cout << combinations.binom(n, k) << '\n';
    }
}
