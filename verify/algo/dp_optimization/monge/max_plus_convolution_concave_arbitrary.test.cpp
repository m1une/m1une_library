#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"

#include <iostream>
#include <vector>

#include "../../../../algo/dp_optimization/monge/min_plus_convolution.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<long long> concave(n), arbitrary(m);
    for (long long& value : concave) {
        std::cin >> value;
        value = -value;
    }
    for (long long& value : arbitrary) {
        std::cin >> value;
        value = -value;
    }

    constexpr long long negative_infinity = -2'000'000'000'000'000'000LL;
    std::vector<long long> result = m1une::monge::max_plus_convolution_concave(
        arbitrary, concave, negative_infinity);
    for (int i = 0; i < int(result.size()); i++) {
        if (i) std::cout << ' ';
        std::cout << -result[i];
    }
    std::cout << '\n';
}
