#define PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series_large"

#include <cassert>
#include <iostream>
#include <random>

#include "../../../math/fps/composition.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using mint1e9 = m1une::math::modint1000000007;
using Fps = m1une::fps::FormalPowerSeries<mint>;

template <class Mint>
m1une::fps::FormalPowerSeries<Mint> naive_compose(
    const m1une::fps::FormalPowerSeries<Mint>& outer,
    const m1une::fps::FormalPowerSeries<Mint>& inner, int degree) {
    using Series = m1une::fps::FormalPowerSeries<Mint>;
    Series result(degree);
    Series power(degree);
    if (degree > 0) power[0] = 1;
    for (int i = 0; i < int(outer.size()) && i < degree; i++) {
        for (int j = 0; j < degree; j++) result[j] += outer[i] * power[j];
        power = (power * inner).pre(degree);
    }
    return result;
}

void randomized_test() {
    std::mt19937 rng(918273645);
    assert(m1une::fps::compose(Fps(), Fps()).empty());
    for (int iteration = 0; iteration < 100; iteration++) {
        const int degree = int(rng() % 24) + 1;
        Fps outer(rng() % (degree + 1));
        Fps inner(rng() % (degree + 1));
        for (mint& value : outer) value = mint(rng());
        for (mint& value : inner) value = mint(rng());
        if (!inner.empty()) inner[0] = 0;
        assert(m1une::fps::compose(outer, inner, degree) ==
               naive_compose(outer, inner, degree));
    }

    using Fps1e9 = m1une::fps::FormalPowerSeries<mint1e9>;
    Fps1e9 outer(48), inner(48);
    for (mint1e9& value : outer) value = mint1e9(rng());
    for (mint1e9& value : inner) value = mint1e9(rng());
    inner[0] = 0;
    assert(m1une::fps::compose(outer, inner) == naive_compose(outer, inner, 48));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    randomized_test();

    int n;
    std::cin >> n;
    Fps f(n), g(n);
    for (mint& value : f) std::cin >> value;
    for (mint& value : g) std::cin >> value;

    Fps result = m1une::fps::compose(f, g, n);
    for (int i = 0; i < n; i++) {
        if (i) std::cout << ' ';
        std::cout << result[i];
    }
    std::cout << '\n';
}
