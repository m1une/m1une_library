#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex"

#include <iostream>
#include <vector>

#include "../../../../algo/dp_optimization/monge/min_plus_convolution.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<long long> first(n), second(m);
    for (long long& value : first) std::cin >> value;
    for (long long& value : second) std::cin >> value;

    constexpr long long infinity = 2'000'000'000'000'000'000LL;
    std::vector<long long> result =
        m1une::monge::min_plus_convolution_convex_convex(first, second, infinity);
    for (int i = 0; i < int(result.size()); i++) {
        if (i) std::cout << ' ';
        std::cout << result[i];
    }
    std::cout << '\n';
}
