#define PROBLEM "https://yukicoder.me/problems/no/2206"

#include "../../math/modint.hpp"
#include "../../math/prefix_sum_of_binom.hpp"

#include <iostream>
#include <utility>
#include <vector>

using Mint = m1une::math::modint998244353;

int main() {
    int test_count;
    std::cin >> test_count;
    std::vector<std::pair<int, int>> queries(test_count);
    for (auto& query : queries) {
        std::cin >> query.first >> query.second;
    }

    m1une::math::OfflinePrefixSumOfBinom<Mint> prefix;
    prefix.reserve(test_count);
    for (const auto& query : queries) {
        prefix.add_query(query.first - 1, query.second);
    }
    const std::vector<Mint> answers = prefix.calculate();

    for (int i = 0; i < test_count; i++) {
        const int n = queries[i].first;
        std::cout << answers[i] * (Mint(2).pow(n) - Mint(1)) << '\n';
    }
}
