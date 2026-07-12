#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/combinatorics.hpp"
#include "../../math/modint.hpp"
#include "../../math/prefix_sum_of_binom.hpp"

#include <cassert>
#include <iostream>
#include <vector>

using Mint = m1une::math::modint998244353;

int main() {
    constexpr int maximum = 300;
    m1une::math::Combinatorics<Mint> combinations(maximum);
    m1une::math::PrefixSumOfBinom<Mint> online(maximum);
    m1une::math::OfflinePrefixSumOfBinom<Mint> offline;
    std::vector<Mint> expected;
    assert(online.maximum() == maximum);
    assert(offline.empty());

    for (int n = 0; n <= maximum; n++) {
        Mint sum = 0;
        for (int m = 0; m <= n + 5; m++) {
            expected.push_back(sum);
            assert(online.query(n, m) == sum);
            assert(offline.add_query(n, m) == int(expected.size()) - 1);
            sum += combinations.binom(n, m);
        }
    }
    assert(offline.query_count() == int(expected.size()));
    assert(offline.calculate() == expected);
    assert(offline.calculate() == expected);
    offline.clear();
    assert(offline.empty());

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
