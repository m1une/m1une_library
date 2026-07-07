#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"

#include <iostream>
#include <vector>

#include "../../../../algo/dp_optimization/monge/min_plus_convolution.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<long long> convex(n), arbitrary(m);
    for (long long& value : convex) std::cin >> value;
    for (long long& value : arbitrary) std::cin >> value;

    constexpr long long infinity = 2'000'000'000'000'000'000LL;
    std::vector<long long> result =
        m1une::monge::min_plus_convolution_convex(arbitrary, convex, infinity);
    for (int i = 0; i < int(result.size()); i++) {
        if (i) std::cout << ' ';
        std::cout << result[i];
    }
    std::cout << '\n';
}
