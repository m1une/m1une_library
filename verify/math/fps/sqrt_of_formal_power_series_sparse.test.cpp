#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series_sparse"

#include <iostream>

#include "../../../math/fps/sparse_formal_power_series.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Sparse = m1une::fps::SparseFormalPowerSeries<mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    Sparse f(k);
    for (auto& [degree, coefficient] : f) std::cin >> degree >> coefficient;
    auto result = m1une::fps::sparse_fps_sqrt(f, n);
    if (!result.has_value()) {
        std::cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (i) std::cout << ' ';
        std::cout << (*result)[i];
    }
    std::cout << '\n';
}
