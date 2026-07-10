#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include <cassert>
#include <iostream>
#include <vector>

#include "../../math/modint.hpp"
#include "../../math/partition_function.hpp"

using Mint = m1une::math::modint998244353;

void test_against_naive() {
    for (int maximum = 0; maximum <= 100; maximum++) {
        std::vector<Mint> expected(maximum + 1);
        expected[0] = 1;
        for (int part = 1; part <= maximum; part++) {
            for (int sum = part; sum <= maximum; sum++) {
                expected[sum] += expected[sum - part];
            }
        }
        assert(
            m1une::math::partition_function<Mint>(maximum) == expected
        );
        assert(m1une::math::partition_numbers<Mint>(maximum) == expected);
    }
}

int main() {
    test_against_naive();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    const std::vector<Mint> values =
        m1une::math::partition_function<Mint>(n);
    for (int i = 0; i <= n; i++) {
        if (i) std::cout << ' ';
        std::cout << values[i];
    }
    std::cout << '\n';
}
