#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series_sparse"

#include <cassert>
#include <iostream>
#include <limits>
#include <random>

#include "../../../math/fps/sparse_formal_power_series.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Sparse = m1une::fps::SparseFormalPowerSeries<mint>;
using Fps = m1une::fps::FormalPowerSeries<mint>;

Sparse to_sparse(const Fps& f) {
    Sparse result;
    for (int i = 0; i < int(f.size()); i++) {
        if (f[i] != mint(0)) result.emplace_back(i, f[i]);
    }
    return result;
}

void randomized_test() {
    std::mt19937 rng(271828182);
    for (int iteration = 0; iteration < 80; iteration++) {
        const int degree = int(rng() % 28) + 2;
        Fps f(degree);
        f[0] = mint(rng());
        if (f[0] == mint(0)) f[0] = 1;
        for (int i = 1; i < degree; i++) {
            if (rng() % 4 == 0) f[i] = mint(rng());
        }
        Sparse sparse = to_sparse(f);
        assert(m1une::fps::sparse_fps_inv(sparse, degree) == f.inv(degree));

        f[0] = 1;
        sparse = to_sparse(f);
        assert(m1une::fps::sparse_fps_log(sparse, degree) == f.log(degree));

        f[0] = 0;
        sparse = to_sparse(f);
        assert(m1une::fps::sparse_fps_exp(sparse, degree) == f.exp(degree));

        const long long exponent = rng() % 7;
        assert(m1une::fps::sparse_fps_pow(sparse, exponent, degree) ==
               f.pow(exponent, degree));

        Fps root(degree);
        root[rng() % degree] = mint(rng());
        for (int i = 0; i < degree; i++) {
            if (rng() % 7 == 0) root[i] = mint(rng());
        }
        Fps square = (root * root).pre(degree);
        auto sparse_root = m1une::fps::sparse_fps_sqrt(to_sparse(square), degree);
        assert(sparse_root.has_value());
        assert(((*sparse_root) * (*sparse_root)).pre(degree) == square);
    }

    Sparse empty;
    Fps one(8);
    one[0] = 1;
    assert(m1une::fps::sparse_fps_exp(empty, 8) == one);
    assert(m1une::fps::sparse_fps_pow(empty, 0, 8) == one);
    assert(m1une::fps::sparse_fps_sqrt(empty, 8) == Fps(8));

    Sparse shifted;
    shifted.emplace_back(1, 1);
    assert(m1une::fps::sparse_fps_pow(
               shifted, std::numeric_limits<long long>::max(), 8) == Fps(8));
    assert(!m1une::fps::sparse_fps_sqrt(shifted, 8).has_value());
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    randomized_test();

    int n, k;
    std::cin >> n >> k;
    Sparse f(k);
    for (auto& [degree, coefficient] : f) std::cin >> degree >> coefficient;
    auto result = m1une::fps::sparse_fps_inv(f, n);
    for (int i = 0; i < n; i++) {
        if (i) std::cout << ' ';
        std::cout << result[i];
    }
    std::cout << '\n';
}
